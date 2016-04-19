// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"

#if !defined (HPP_ALIB_TIME)
    #include "alib/time/ticks.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_ASTRING)
    #include "alib/strings/asalloc.hpp"
#endif

#if !defined (HPP_ALIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
#endif


using namespace aworx;

#include <iostream>

#define TESTCLASSNAME       CPP_ALib_Threads
#include "aworx_unittests.hpp"

using namespace std;

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
            mutex->Acquire(ALIB_DBG_SRC_INFO_PARAMS);
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
{
    UT_INIT();

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
{
    UT_INIT();

    lib::Report::GetDefault().PushHaltFlags( false, false );

    // lock a recursive lock
    {
        ThreadLock aLock;
        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);    UT_EQ ( 1, aLock.DbgCountAcquirements() );
        aLock.Release();                UT_EQ ( 0, aLock.DbgCountAcquirements() );

        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);    UT_EQ ( 1, aLock.DbgCountAcquirements() );
        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);    UT_EQ ( 2, aLock.DbgCountAcquirements() );
        aLock.Release();                            UT_EQ ( 1, aLock.DbgCountAcquirements() );

        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);    UT_EQ ( 2, aLock.DbgCountAcquirements() );
        aLock.Release();                            UT_EQ ( 1, aLock.DbgCountAcquirements() );
        aLock.Release();                            UT_EQ ( 0, aLock.DbgCountAcquirements() );

        // set unsafe
        aLock.SetSafeness( Safeness::Unsafe );      UT_EQ ( 0, aLock.DbgCountAcquirements() );
        aLock.SetSafeness( Safeness::Safe   );      UT_EQ ( 0, aLock.DbgCountAcquirements() );

        aLock.SetSafeness( Safeness::Unsafe );      UT_EQ ( 0, aLock.DbgCountAcquirements() );
        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);    UT_EQ ( 1, aLock.DbgCountAcquirements() );
        aLock.Release();                            UT_EQ ( 0, aLock.DbgCountAcquirements() );

        // unsafe
        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);    UT_EQ ( 1, aLock.DbgCountAcquirements() );
        UT_PRINT( "Expecting error: set unsafe when already locked" );
        aLock.SetSafeness( Safeness::Safe   );      UT_EQ ( 1, aLock.DbgCountAcquirements() );
        UT_PRINT( "Expecting error: destruction while locked" );
    }

    // safe (new lock)
    {
        ThreadLock aLock;
        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS); UT_EQ ( 1, aLock.DbgCountAcquirements() );
        UT_PRINT( "Expecting error: set unsafe when already locked" );
        aLock.SetSafeness( Safeness::Unsafe );   UT_EQ ( 1, aLock.DbgCountAcquirements() );
        aLock.Release();                         UT_EQ ( 0, aLock.DbgCountAcquirements() );
        UT_PRINT( "Expecting error: release whithout lock" );
        aLock.Release();                         UT_EQ (-1, aLock.DbgCountAcquirements() );
    }

    // test warnings (10) locks:
    {
        ThreadLock aLock;
        UT_PRINT( "Two warnings should come now: " );
        for (int i= 0; i<20; i++)
            aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
        UT_TRUE ( aLock.DbgCountAcquirements() > 0 );
        for (int i= 0; i<20; i++)
            aLock.Release();
        UT_EQ ( 0, aLock.DbgCountAcquirements() );
    }

    // test a non-recursive lock
    {
        ThreadLock aLock( LockMode::SingleLocks );
        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);    UT_EQ ( 1, aLock.DbgCountAcquirements() );
        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);    UT_EQ ( 1, aLock.DbgCountAcquirements() );
        aLock.Release();                            UT_EQ ( 0, aLock.DbgCountAcquirements() );

        UT_PRINT( "One Error should come now: " );
        aLock.Release();                            UT_EQ ( 0, aLock.DbgCountAcquirements() );
    }

    lib::Report::GetDefault().PopHaltFlags();
}

//---------------------------------------------------------------------------------------------------------
//--- ThreadLockThreaded
//---------------------------------------------------------------------------------------------------------
UT_METHOD( ThreadLockThreaded )
{
    UT_INIT();

    lib::Report::GetDefault().PushHaltFlags( false, false );

        ThreadLock aLock;
        Test_ThreadLock_SharedInt* shared= new Test_ThreadLock_SharedInt();
        UT_PRINT( "starting thread locked" );
        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
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
        aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
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

    lib::Report::GetDefault().PopHaltFlags();
}

//---------------------------------------------------------------------------------------------------------
//--- SmartLockTest
//---------------------------------------------------------------------------------------------------------
#if defined (ALOX_DBG_LOG) // in release, no ALIB report is sent.
UT_METHOD( SmartLockTest )
{
    UT_INIT();

    lib::Report::GetDefault().PushHaltFlags( false, false );
    ut.lox.CntLogCalls= 0;

    // SmartLock with null-users
    {
        SmartLock sl;                          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 1 ); ut.lox.CntLogCalls= 0;
    }

    // SmartLock with threadlocks
    {
        ThreadLock tl1, tl2, tl3;
        SmartLock  sl;                         UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( &tl1    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( &tl2    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( &tl3    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( &tl3    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( &tl3    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 1 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( &tl2    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( &tl1    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( &tl1    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 1 ); ut.lox.CntLogCalls= 0;
    }

    // mixed
    {
        ThreadLock tl1, tl2, tl3;
        SmartLock  sl;                         UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( &tl1    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( &tl2    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( &tl2    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 1 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.AddAcquirer   ( &tl3    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( &tl1    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( &tl1    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 1 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( &tl3    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Safe   );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 1 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 1 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( &tl3    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 1 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( &tl2    );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 0 ); ut.lox.CntLogCalls= 0;
        sl.RemoveAcquirer( nullptr );          UT_TRUE( ((ThreadLock&) sl).GetSafeness() == Safeness::Unsafe );  UT_TRUE( ut.lox.CntLogCalls== 1 ); ut.lox.CntLogCalls= 0;
    }
    lib::Report::GetDefault().PopHaltFlags();
}
#endif

//---------------------------------------------------------------------------------------------------------
//--- HeavyLoad
//---------------------------------------------------------------------------------------------------------
UT_METHOD( HeavyLoad )
{
    UT_INIT();

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
{
    UT_INIT();

    ThreadLock aLock;

    int        repeats=    10000;
    int        rrepeats=       3;


    Ticks stopwatch;
    for ( int run= 1; run <= rrepeats; run ++)
    {
        UT_PRINT( "Run " << run << '/' << rrepeats );

        aLock.SetSafeness( Safeness::Safe );
        stopwatch.Set();
        for ( int i= 0; i < repeats; i++ )
        {
            aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
            aLock.Release();
        }
        auto time= stopwatch.Age().InMicros();
        UT_PRINT( "  Safe mode:   " << repeats << " lock/unlock ops: " << time << "\xC2\xB5s" ); // UTF-8 encoding of the greek 'm' letter;

        aLock.SetSafeness( Safeness::Unsafe );
        stopwatch.Set();
        volatile int ii= 0;
        for ( int i= 0; i < repeats; i++ )
        {
            aLock.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
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
            tNR.Acquire(ALIB_DBG_SRC_INFO_PARAMS);
            tNR.Release();
        }
        time= stopwatch.Age().InMicros();
        UT_PRINT( "  std::mutex:  " << repeats << " lock/unlock ops: " << time << "\xC2\xB5s" ); // UTF-8 encoding of the greek 'm' letter;
    }

}

UT_CLASS_END

}; //namespace
