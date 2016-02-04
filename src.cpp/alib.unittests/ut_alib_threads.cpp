// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"

#if !defined (HPP_AWORX_LIB_TIME)
    #include "alib/time/ticks.hpp"
#endif

#if !defined (HPP_AWORX_LIB_STRINGS_ASTRING)
    #include "alib/strings/asalloc.hpp"
#endif

#if !defined (HPP_AWORX_LIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
#endif

#include <iostream>

#define TESTCLASSNAME       CPP_ALib_Threads
#include "aworx_unittests.hpp"

using namespace std;
using namespace aworx;
using namespace aworx::lib;
using namespace aworx::lib::enums;
using namespace aworx::lib::strings;
using namespace aworx::lib::threads;

namespace ut_aworx {


UT_CLASS()

//---------------------------------------------------------------------------------------------------------
//--- helper classes
//---------------------------------------------------------------------------------------------------------

class Test_ThreadLock_SharedInt
{
    public:        int val= 0;
};

class Test_ThreadLock_TestThread : public Thread
{
    public:        ALIBUnitTesting* pUT;
    public:        ThreadLock*      mutex;
    public:        int              holdTime;
    public:        int              repeats;
    public:        bool             verbose;
    public:        int              result= 1;
    public:        Test_ThreadLock_SharedInt* shared;

    public:        Test_ThreadLock_TestThread( ALIBUnitTesting* pUT, const String& name, ThreadLock* lock, int holdTime, int repeats, bool verbose, Test_ThreadLock_SharedInt* shared )
    :Thread( name )
    {
        this->pUT=        pUT;
        this->mutex=     lock;
        this->holdTime=  holdTime;
        this->repeats=   repeats;
        this->verbose=   verbose;
        this->shared=    shared;
    }

    public: void Run()
    {
        ALIBUnitTesting &ut= *pUT;
        UT_EQ( GetId(), Thread::CurrentThread()->GetId() );

        for ( int i= 0; i < repeats ; i++ )
        {
            if (verbose) { UT_PRINT( "Thread: " << GetName() << " acquiring lock..." ); }
            mutex->Acquire();
            if (verbose) { UT_PRINT( "Thread: " << GetName() << " has lock." ); }

                int sVal= ++shared->val;

                ALIB::SleepMillis( holdTime );

                shared->val= sVal -1;

            if (verbose) { UT_PRINT( "Thread: " << GetName() << " releasing lock." ); }
            mutex->Release();
            if (verbose) { UT_PRINT( "Thread: " << GetName() << " released lock." ); }
        }

        result= 0;
        UT_PRINT( "Thread: " << GetName() << " terminates." );

    }
};

//---------------------------------------------------------------------------------------------------------
//--- ThreadSimple
//---------------------------------------------------------------------------------------------------------
UT_METHOD( ThreadSimple )

    // create and delete
    {
        Thread t;
        UT_PRINT( "Thread object on stack, not started. Alive= " << t.IsAlive() );
    }
    {
        Thread* t= new Thread();
        UT_PRINT( "Thread object on heap, not started. Alive= " << t->IsAlive() );
        delete t;
    }
    {
        Thread* t= new Thread();
        t->Start();
        UT_PRINT( "Empty Thread object, started. Alive= " << t->IsAlive() );
        delete t;
    }

    // simple runnable
    class runner: public Runnable
    {
        public:
        ALIBUnitTesting *pUT;
        int a= 0;
        runner(ALIBUnitTesting *pUT) { this->pUT= pUT; }
        virtual void Run()
        {
            ALIBUnitTesting& ut= *pUT;
            UT_PRINT( "Runnable running in thread " << Thread::CurrentThread()->GetId() );  ALIB::SleepMillis(1); a++;
        }
    };

    #ifdef ALIB_FEAT_THREADS
    {
        runner r(&ut);
        {
            Thread t(&r);
            t.Start();
        }

        UT_EQ( 1, r.a ); // thread is deleted, runner should have executed here

        {
            Thread t(&r);
            t.Start();
            UT_EQ( 1, r.a ); // runner waits a millisec, we should be quicker
            int cntWait= 0;
            while( t.IsAlive() )
            {
                UT_PRINT( "  " << Thread::CurrentThread()->GetId() << " waiting for " << t.GetId() <<" to finish"  );
                ALIB::SleepMicros(250);
                cntWait++;
            }
            UT_TRUE( cntWait < 5 );
            UT_PRINT( "  Result should be 2: " << r.a  );
            UT_EQ( 2, r.a );
        }
    }
    #endif
}

//---------------------------------------------------------------------------------------------------------
//--- ThreadLockSimple
//---------------------------------------------------------------------------------------------------------
UT_METHOD( ThreadLockSimple )

    bool oldHaltOnError=    Report::GetDefault().HaltOnError;
    bool oldHaltOnWarning=  Report::GetDefault().HaltOnWarning;
    Report::GetDefault().HaltOnError=
    Report::GetDefault().HaltOnWarning=    false;

    // lock a recursive lock
    {
        ThreadLock aLock;
        aLock.Acquire();                UT_EQ ( 1, aLock.IsAcquired() );
        aLock.Release();                UT_EQ ( 0, aLock.IsAcquired() );

        aLock.Acquire();                UT_EQ ( 1, aLock.IsAcquired() );
        aLock.Acquire();                UT_EQ ( 2, aLock.IsAcquired() );
        aLock.Release();                UT_EQ ( 1, aLock.IsAcquired() );

        aLock.Acquire();                UT_EQ ( 2, aLock.IsAcquired() );
        aLock.Release();                UT_EQ ( 1, aLock.IsAcquired() );
        aLock.Release();                UT_EQ ( 0, aLock.IsAcquired() );

        // set unsafe
        aLock.SetMode( Safeness::Unsafe );   UT_EQ ( 0, aLock.IsAcquired() );
        aLock.SetMode( Safeness::Safe   );   UT_EQ ( 0, aLock.IsAcquired() );

        aLock.SetMode( Safeness::Unsafe );   UT_EQ ( 0, aLock.IsAcquired() );
        aLock.Acquire();                     UT_EQ ( 1, aLock.IsAcquired() );
        aLock.Release();                     UT_EQ ( 0, aLock.IsAcquired() );

        // unsafe
        aLock.Acquire();                     UT_EQ ( 1, aLock.IsAcquired() );
        UT_PRINT( "Expecting error: set unsafe when already locked" );
        aLock.SetMode( Safeness::Safe   );   UT_EQ ( 1, aLock.IsAcquired() );
        UT_PRINT( "Expecting error: destruction while locked" );
    }

    // safe (new lock)
    {
        ThreadLock aLock;
        aLock.Acquire();                     UT_EQ ( 1, aLock.IsAcquired() );
        UT_PRINT( "Expecting error: set unsafe when already locked" );
        aLock.SetMode( Safeness::Unsafe );   UT_EQ ( 1, aLock.IsAcquired() );
        aLock.Release();                     UT_EQ ( 0, aLock.IsAcquired() );
        UT_PRINT( "Expecting error: release whithout lock" );
        aLock.Release();                     UT_EQ (-1, aLock.IsAcquired() );
    }

    // test warnings (10) locks:
    {
        ThreadLock aLock;
        UT_PRINT( "Two warnings should come now: " );
        for (int i= 0; i<20; i++)
            aLock.Acquire();
        UT_TRUE ( aLock.IsAcquired() > 0 );
        for (int i= 0; i<20; i++)
            aLock.Release();
        UT_EQ ( 0, aLock.IsAcquired() );
    }

    // test a non-recursive lock
    {
        ThreadLock aLock( LockMode::SingleLocks );
        aLock.Acquire();                UT_EQ ( 1, aLock.IsAcquired() );
        aLock.Acquire();                UT_EQ ( 1, aLock.IsAcquired() );
        aLock.Release();                UT_EQ ( 0, aLock.IsAcquired() );

        UT_PRINT( "One Error should come now: " );
        aLock.Release();                UT_EQ ( 0, aLock.IsAcquired() );
    }

    Report::GetDefault().HaltOnError=      oldHaltOnError;
    Report::GetDefault().HaltOnWarning=    oldHaltOnWarning;
}

//---------------------------------------------------------------------------------------------------------
//--- ThreadLockThreaded
//---------------------------------------------------------------------------------------------------------
UT_METHOD( ThreadLockThreaded )

    bool oldHaltOnError=    Report::GetDefault().HaltOnError;
    bool oldHaltOnWarning=  Report::GetDefault().HaltOnWarning;
    Report::GetDefault().HaltOnError=
    Report::GetDefault().HaltOnWarning=    false;

        ThreadLock aLock;
        Test_ThreadLock_SharedInt* shared= new Test_ThreadLock_SharedInt();
        UT_PRINT( "starting thread locked" );
        aLock.Acquire();
        Test_ThreadLock_TestThread* t= new Test_ThreadLock_TestThread( &ut, "A Thread", &aLock, 10, 1, true, shared );
        t->Start();
        UT_PRINT( "We wait 1100 ms. This should give a warning! " );
        ALIB::SleepMillis( 1100 );
        aLock.Release();

        // wait until t ended
        while (t->IsAlive())
            ALIB::SleepMillis( 1 );

        // now we do the same with a lower wait limit, no error should come
        aLock.WaitWarningTimeLimitInMillis= 5;
        aLock.Acquire();
        delete t;
        t= new Test_ThreadLock_TestThread( &ut, "A Thread", &aLock, 10, 1, true, shared );
        t->Start();
        UT_PRINT( "We wait 1 ms. This should NOT give a warning! " );
        ALIB::SleepMillis( 1 );
        aLock.Release();

        // wait until t ended
        while (t->IsAlive())
            ALIB::SleepMillis( 1 );
        delete t;
        delete shared;

    Report::GetDefault().HaltOnError=      oldHaltOnError;
    Report::GetDefault().HaltOnWarning=    oldHaltOnWarning;
}



//---------------------------------------------------------------------------------------------------------
//--- HeavyLoad
//---------------------------------------------------------------------------------------------------------
UT_METHOD( HeavyLoad )

    ThreadLock aLock;

    // uncomment this for unsafe mode
    //aLock.SetUnsafe( true ); aLock.UseAssertions= false;

    Test_ThreadLock_SharedInt   shared;
    int                         holdTime=    0;
    int                         repeats=    5000;
    bool                        verbose=    false;

    Test_ThreadLock_TestThread* t1= new Test_ThreadLock_TestThread( &ut, "A", &aLock, holdTime, repeats, verbose, &shared );
    Test_ThreadLock_TestThread* t2= new Test_ThreadLock_TestThread( &ut, "B", &aLock, holdTime, repeats, verbose, &shared );
    Test_ThreadLock_TestThread* t3= new Test_ThreadLock_TestThread( &ut, "C", &aLock, holdTime, repeats, verbose, &shared );
    UT_PRINT( "starting three threads" );
    t1->Start();
    t2->Start();
    t3->Start();

    // wait until all ended
    while ( t1->IsAlive() || t2->IsAlive() || t3->IsAlive() )
        ALIB::SleepMillis( 1 );

    UT_PRINT( "All threads ended. Shared value=" << shared.val );
    UT_EQ( 0, shared.val );
    delete t1;
    delete t2;
    delete t3;
}

//---------------------------------------------------------------------------------------------------------
//--- SpeedTest
//---------------------------------------------------------------------------------------------------------
UT_METHOD( LockSpeedTest )

    ThreadLock aLock;

    int        repeats=    10000;
    int        rrepeats=       3;


    time::Ticks stopwatch;
    for ( int run= 1; run <= rrepeats; run ++)
    {
        UT_PRINT( "Run " << run << '/' << rrepeats );

        aLock.SetMode( Safeness::Safe );
        stopwatch.Set();
        for ( int i= 0; i < repeats; i++ )
        {
            aLock.Acquire();
            aLock.Release();
        }
        auto time= stopwatch.Age().InMicros();
        UT_PRINT( "  Safe mode:   " << repeats << " lock/unlock ops: " << time << "\xC2\xB5s" ); // UTF-8 encoding of the greek 'm' letter;

        aLock.SetMode( Safeness::Unsafe );
        stopwatch.Set();
        volatile int ii= 0;
        for ( int i= 0; i < repeats; i++ )
        {
            aLock.Acquire();
            aLock.Release();

            // in java, adding the following two loops, results in similar execution speed
            //for ( int tt= 0; tt < 70; tt++ )        i+= tt;
            //for ( int tt= 0; tt < 70; tt++ )        i-= tt;

            // in c++, adding the following two loops, results in similar execution speed
            for ( int tt= 0; tt < 80; tt++ )    ii+= tt; // in release it is rather 20. Strange enough!
            for ( int tt= 0; tt < 80; tt++ )    ii-= tt; // in release it is rather 20. Strange enough!
        }
        time= stopwatch.Age().InMicros();
        UT_PRINT( "  Unsafe mode: " << repeats << " lock/unlock ops: " << time << "\xC2\xB5s" ); // UTF-8 encoding of the greek 'm' letter;
        if (ii != 0 )
            UT_PRINT( "Never true! Just to stop compiler from pruning ii" ); //µs


        ThreadLockNR tNR;
        stopwatch.Set();
        for ( int i= 0; i < repeats; i++ )
        {
            tNR.Acquire();
            tNR.Release();
        }
        time= stopwatch.Age().InMicros();
        UT_PRINT( "  std::mutex:  " << repeats << " lock/unlock ops: " << time << "\xC2\xB5s" ); // UTF-8 encoding of the greek 'm' letter;
    }

}

UT_CLASS_END

}; //namespace
