// #################################################################################################
//  aworx::util - Unit Tests
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"

#include "awxu.hpp"

#if !defined (HPP_AWORX_UTIL_TICKS)
    #include "ticks.hpp"
#endif

#if !defined (HPP_AWORX_UTIL_ASTRING)
    #include "astring.hpp"
#endif

#if !defined (HPP_AWORX_UTIL_THREADLOCK)
    #include "threadlock.hpp"
#endif

#include <iostream>

#define TESTCLASSNAME       CPP_Threads
#include "awx_unittests.hpp"

using namespace std;
using namespace aworx::util;

namespace tests_aworx_util {


A_TEST_CLASS()

//---------------------------------------------------------------------------------------------------------
//--- helper classes
//---------------------------------------------------------------------------------------------------------

class Test_ThreadLock_SharedInt
{
    public:        int val= 0;
};

class Test_ThreadLock_TestThread : public Thread
{
    public:        AWXUnitTesting* pUT;
    public:        ThreadLock*     mutex;
    public:        int             holdTime;
    public:        int             repeats;
    public:        bool            verbose;
    public:        int             result= 1;
    public:        Test_ThreadLock_SharedInt* shared;

    public:        Test_ThreadLock_TestThread( AWXUnitTesting* pUT, const char* name, ThreadLock* lock, int holdTime, int repeats, bool verbose, Test_ThreadLock_SharedInt* shared )
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
        AWXUnitTesting &ut= *pUT;
        EXPECT_EQ( GetId(), Thread::CurrentThread()->GetId() );

        for ( int i= 0; i < repeats ; i++ )
        {
            if (verbose) { PRINT( AString64("Thread: ") << GetName() << " acquiring lock..." ); }
            mutex->Acquire();
            if (verbose) { PRINT( AString64("Thread: ") << GetName() << " has lock." ); }

                int sVal= ++shared->val;

                AWXU::SleepMillis( holdTime );

                shared->val= sVal -1;

            if (verbose) { PRINT( AString64("Thread: ") << GetName() << " releasing lock." ); }
            mutex->Release();
            if (verbose) { PRINT( AString64("Thread: ") << GetName() << " released lock." ); }
        }

        result= 0;
        PRINT( AString64("Thread: ") << GetName() << " terminates." );

    }
};

//---------------------------------------------------------------------------------------------------------
//--- ThreadSimple
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( ThreadSimple )

    // create and delete
    {
        Thread t;
        PRINT( "Non started thread object on stack. Alive= " << t.IsAlive() );
    }
    {
        Thread* t= new Thread();
        PRINT( "Non started thread object on heap. Alive= " << t->IsAlive() );
        delete t;
    }
    {
        Thread* t= new Thread();
        t->Start();
        PRINT( "Empty Thread object, started. Alive= " << t->IsAlive() );
        delete t;
    }

    // simple runnable
    class runner: public Runnable
    {
        public:
        AWXUnitTesting *pUT;
        int a= 0;
        runner(AWXUnitTesting *pUT) { this->pUT= pUT; }
        virtual void Run()
        {
            AWXUnitTesting& ut= *pUT;
            PRINT( "Runnable running in thread " << Thread::CurrentThread()->GetId() );  AWXU::SleepMillis(1); a++;
        }
    };

    #ifdef AWXU_FEAT_THREADS
    {
        runner r(&ut);
        {
            Thread t(&r);
            t.Start();
        }

        EXPECT_EQ( 1, r.a ); // thread is deleted, runner should have executed here

        {
            Thread t(&r);
            t.Start();
            EXPECT_EQ( 1, r.a ); // runner waits a millisec, we should be quicker
            int cntWait= 0;
            while( t.IsAlive() )
            {
                PRINT( "  " << Thread::CurrentThread()->GetId() << " waiting for " << t.GetId() <<" to finish"  );
                AWXU::SleepMicros(250);
                cntWait++;
            }
            EXPECT_TRUE( cntWait < 5 );
            PRINT( "  Result should be 2: " << r.a  );
            EXPECT_EQ( 2, r.a );
        }
    }
    #endif
}

//---------------------------------------------------------------------------------------------------------
//--- ThreadLockSimple
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( ThreadLockSimple )

    bool oldHaltOnError=    AWXU::HaltOnError;
    bool oldHaltOnWarning=  AWXU::HaltOnWarning;
    AWXU::HaltOnError=
    AWXU::HaltOnWarning=    false;

    // lock a recursive lock
    {
        ThreadLock aLock;
        aLock.Acquire();                EXPECT_TRUE (  aLock.IsAcquired() );
        aLock.Release();                EXPECT_TRUE ( !aLock.IsAcquired() );

        aLock.Acquire();                EXPECT_TRUE (  aLock.IsAcquired() );
        aLock.Acquire();                EXPECT_TRUE (  aLock.IsAcquired() );
        aLock.Release();                EXPECT_TRUE (  aLock.IsAcquired() );

        aLock.Acquire();                EXPECT_TRUE (  aLock.IsAcquired() );
        aLock.Release();                EXPECT_TRUE (  aLock.IsAcquired() );
        aLock.Release();                EXPECT_TRUE ( !aLock.IsAcquired() );

        // set unsafe
        aLock.SetUnsafe( true );        EXPECT_TRUE ( !aLock.IsAcquired() );
        aLock.SetUnsafe( false );       EXPECT_TRUE ( !aLock.IsAcquired() );

        aLock.SetUnsafe( true );        EXPECT_TRUE ( !aLock.IsAcquired() );
        aLock.Acquire();                EXPECT_TRUE (  aLock.IsAcquired() );
        aLock.Release();                EXPECT_TRUE ( !aLock.IsAcquired() );

        // unsafe
        aLock.Acquire();                EXPECT_TRUE (  aLock.IsAcquired() );
        PRINT( "Expecting error: set unsafe when already locked" );
        aLock.SetUnsafe( false );       EXPECT_TRUE (  !aLock.IsAcquired() );
    }

    // safe (new lock)
    {
        ThreadLock aLock;
        aLock.Acquire();                EXPECT_TRUE ( aLock.IsAcquired() );
        PRINT( "Expecting error: set unsafe when already locked" );
        aLock.SetUnsafe( true );        EXPECT_TRUE ( aLock.IsAcquired() );
    }

    // test warnings (10) locks:
    {
        ThreadLock aLock;
        PRINT( "Two warnings should come now: " );
        for (int i= 0; i<20; i++)
            aLock.Acquire();
        EXPECT_TRUE ( aLock.IsAcquired() );
        for (int i= 0; i<20; i++)
            aLock.Release();
        EXPECT_TRUE ( !aLock.IsAcquired() );
    }

    // test a non-recursive lock
    {
        ThreadLock aLock( false );
        aLock.Acquire();                EXPECT_TRUE ( aLock.IsAcquired() );
        aLock.Acquire();                EXPECT_TRUE ( aLock.IsAcquired() );
        aLock.Release();                EXPECT_TRUE ( !aLock.IsAcquired() );

        PRINT( "One warning should come now: " );
        aLock.Release();                EXPECT_TRUE ( !aLock.IsAcquired() );
    }

    AWXU::HaltOnError=      oldHaltOnError;
    AWXU::HaltOnWarning=    oldHaltOnWarning;
}

//---------------------------------------------------------------------------------------------------------
//--- ThreadLockThreaded
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( ThreadLockThreaded )

    bool oldHaltOnError=    AWXU::HaltOnError;
    bool oldHaltOnWarning=  AWXU::HaltOnWarning;
    AWXU::HaltOnError=
    AWXU::HaltOnWarning=    false;

        ThreadLock aLock;
        Test_ThreadLock_SharedInt* shared= new Test_ThreadLock_SharedInt();
        PRINT( "starting thread locked" );
        aLock.Acquire();
        Test_ThreadLock_TestThread* t= new Test_ThreadLock_TestThread( &ut, "A Thread", &aLock, 10, 1, true, shared );
        t->Start();
        PRINT( "We wait 1100 ms. This should give a warning! " );
        AWXU::SleepMillis( 1100 );
        aLock.Release();

        // wait until t ended
        while (t->IsAlive())
            AWXU::SleepMillis( 1 );

        // now we do the same with a lower wait limit, no error should come
        aLock.WaitWarningTimeLimitInMillis= 5;
        aLock.Acquire();
        delete t;
        t= new Test_ThreadLock_TestThread( &ut, "A Thread", &aLock, 10, 1, true, shared );
        t->Start();
        PRINT( "We wait 1 ms. This should NOT give a warning! " );
        AWXU::SleepMillis( 1 );
        aLock.Release();

        // wait until t ended
        while (t->IsAlive())
            AWXU::SleepMillis( 1 );
        delete t;
        delete shared;

    AWXU::HaltOnError=      oldHaltOnError;
    AWXU::HaltOnWarning=    oldHaltOnWarning;
}



//---------------------------------------------------------------------------------------------------------
//--- HeavyLoad
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( HeavyLoad )

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
    PRINT( "starting three threads" );
    t1->Start();
    t2->Start();
    t3->Start();

    // wait until all ended
    while ( t1->IsAlive() || t2->IsAlive() || t3->IsAlive() )
        AWXU::SleepMillis( 1 );

    PRINT( "All threads ended. Shared value=" << shared.val );
    EXPECT_TRUE( shared.val == 0 );
    delete t1;
    delete t2;
    delete t3;

}

//---------------------------------------------------------------------------------------------------------
//--- SpeedTest
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( LockSpeedTest )

    ThreadLock aLock;

    int        repeats=    10000;
    int        rrepeats=       3;


    Ticks stopwatch;
    for ( int r= 0; r < rrepeats; r ++)
    {
        PRINT( AString::NEWLINE << "Run " << r << "/" << rrepeats );

        aLock.SetUnsafe( false );
        stopwatch.Set();
        for ( int i= 0; i < repeats; i++ )
        {
            aLock.Acquire();
            aLock.Release();
        }
        auto time= stopwatch.Age().InMicros();
        PRINT( "Safe mode:   " << repeats << " lock/unlock ops: " << time << " \xB5s" ); //µs

        aLock.SetUnsafe( true );
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
            for ( int tt= 0; tt < 80; tt++ )    ii+= tt; // in release it is rather 20. Strange enaugh!
            for ( int tt= 0; tt < 80; tt++ )    ii-= tt; // in release it is rather 20. Strange enaugh!
        }
        time= stopwatch.Age().InMicros();
        PRINT( "Unsafe mode: " << repeats << " lock/unlock ops: " << time << " \xB5s" ); //µs
        if (ii != 0 )
            PRINT( "Never true! Just to stop compiler from pruning ii" ); //µs


        ThreadLockNR tNR;
        stopwatch.Set();
        for ( int i= 0; i < repeats; i++ )
        {
            tNR.Acquire();
            tNR.Release();
        }
        time= stopwatch.Age().InMicros();
        PRINT( "std::mutex:  " << repeats << " lock/unlock ops: " << time << " \xB5s" ); //µs
    }

}

A_TEST_CLASS_END

}; //namespace
