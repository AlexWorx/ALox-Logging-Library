// #################################################################################################
//  cs.aworx.unittests - AWorx Util
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;
using cs.aworx.lib.threads;
using cs.aworx.lib.time;
using ut_cs_aworx;
using cs.aworx.lib.lang;

#if ALIB_NUNIT
    using NUnit.Framework;
#endif
#if ALIB_IDE_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using System.Text;
using cs.aworx.lib;
using cs.aworx.lox;
using cs.aworx.lox.loggers;

namespace ut_cs_aworx_lib
{
    #if ALIB_NUNIT
        [TestFixture ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestClass]
    #endif
    public class CS_ThreadLock    : AWorxUnitTesting
    {
        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ThreadLock")]
            #endif
        #endif
        public void ThreadLock_Simple()
        {
            UT_INIT();
            Report.GetDefault().PushHaltFlags( false, false );

            Log.AddDebugLogger();
            Log.MapThreadName( "UnitTest" );
            Log.SetDomain( "TestTLock", Scope.Method );
            Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "ALIB" );

            // lock a recursive lock
            ThreadLock aLock= new ThreadLock();

            aLock.Acquire();
            aLock.Release();

            aLock.Acquire();                                UT_TRUE (  aLock.ToString().StartsWith("Locked")   );
            aLock.Acquire();                                UT_TRUE (  aLock.ToString().StartsWith("Locked")   );
            aLock.Release();                                UT_TRUE (  aLock.ToString().StartsWith("Locked")   );

            aLock.Acquire();                                UT_TRUE (  aLock.ToString().StartsWith("Locked")   );
            aLock.Release();                                UT_TRUE (  aLock.ToString().StartsWith("Locked")   );
            aLock.Release();                                UT_TRUE (  aLock.ToString().StartsWith("Unlocked") );

            // set unsafe
            aLock.SetSafeness( Safeness.Unsafe );           UT_TRUE (  aLock.ToString().StartsWith("Unlocked") );
                                                            UT_TRUE (  aLock.ToString().Contains  ("Unsafe")   );
            aLock.SetSafeness( Safeness.Safe );             UT_TRUE ( !aLock.ToString().Contains  ("Unsafe")   );

            aLock.SetSafeness( Safeness.Unsafe );           UT_TRUE (  aLock.ToString().StartsWith("Unlocked") );
                                                            UT_TRUE (  aLock.ToString().Contains  ("Unsafe")   );
            aLock.Acquire();                                UT_TRUE (  aLock.ToString().StartsWith("Locked")   );
            aLock.Release();                                UT_TRUE (  aLock.ToString().StartsWith("Unlocked") );
                                                            UT_TRUE (  aLock.ToString().Contains  ("Unsafe")   );

            // unsafe
            aLock.Acquire();                                UT_TRUE (  aLock.ToString().StartsWith("Locked")   );
            Log.Info("One warning should come now: ");
            aLock.SetSafeness( Safeness.Safe );             UT_TRUE (  aLock.ToString().StartsWith("Locked")   );
                                                            UT_TRUE (  aLock.ToString().Contains  ("Unsafe")   );

            // safe (new lock)
            aLock= new ThreadLock();
            aLock.Acquire();                                UT_TRUE (  aLock.ToString().StartsWith("Locked")   );
                                                            UT_TRUE ( !aLock.ToString().Contains  ("Unsafe")   );
            Log.Info("One warning should come now: ");
            aLock.SetSafeness( Safeness.Unsafe );           UT_TRUE ( !aLock.ToString().StartsWith("null")     );
                                                            UT_TRUE ( !aLock.ToString().Contains  ("Unsafe")   );


            // test warnings (10) locks:
            aLock= new ThreadLock();
            Log.Info("Two warnings should come now: ");
            for (int i= 0; i<20; i++)
                aLock.Acquire();
            UT_TRUE (  aLock.ToString().StartsWith("Locked") );
            for (int i= 0; i<20; i++)
                aLock.Release();
            UT_TRUE (  aLock.ToString().StartsWith("Unlocked") );

            // test a non-recursive lock
            aLock= new ThreadLock( LockMode.SingleLocks );
            aLock.Acquire();                UT_TRUE (  aLock.ToString().StartsWith("Locked")   );
            aLock.Acquire();                UT_TRUE (  aLock.ToString().StartsWith("Locked")   );
            aLock.Release();                UT_TRUE (  aLock.ToString().StartsWith("Unlocked") );

            Log.Info("One warning should come now: ");
            aLock.Release();                UT_TRUE (  aLock.ToString().StartsWith("Unlocked") );

            Report.GetDefault().PopHaltFlags();
        }

        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ThreadLock")]
            #endif
        #endif
        public void ThreadLock_Threaded()
        {
            UT_INIT();

            Log.SetVerbosity( new ConsoleLogger(),Verbosity.Verbose, "/" );
            Log.MapThreadName( "UnitTest" );
            Log.SetDomain( "TestTLock", Scope.Filename );
            Log.SetVerbosity( "CONSOLE", Verbosity.Verbose, "ALIB" );

            ThreadLock aLock= new ThreadLock();

            Test_ThreadLock_SharedInt shared= new Test_ThreadLock_SharedInt();

            Log.Info("starting thread locked");
            aLock.Acquire();
            Test_ThreadLock_TestThreadParams tParam= new Test_ThreadLock_TestThreadParams( aLock, 10, 1, true, shared );

            Thread thread = new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
            thread.Name= "A Thread";
            thread.Start( tParam );

            Log.Info("We wait 1100 ms. This should give a warning! ");
            ALIB.SleepMillis( 1100 );
            aLock.Release();

            // wait until t ended
            while (thread.IsAlive)
                ALIB.SleepMillis( 1 );

            // now we do the same with a higher wait limit, no erro should come
            aLock.waitWarningTimeLimitInMillis= 5;
            aLock.Acquire();
            tParam= new Test_ThreadLock_TestThreadParams( aLock, 10, 1, true, shared );
            thread = new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
            thread.Start( tParam );
            Log.Info("We wait 1 ms. This should NOT give a warning! ");
            ALIB.SleepMillis( 1 );
            aLock.Release();

            // wait until t ended
            while (thread.IsAlive)
                ALIB.SleepMillis( 1 );

        }


    #if ALOX_DBG_LOG
        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ThreadLock")]
            #endif
        #endif
        public void SmartLock()
        {
            UT_INIT();

            Report.GetDefault().PushHaltFlags( false, false );

                // SmartLock with null-users
                {
                                                                                                                                                  utWriter.lox.CntLogCalls= 0;
                    SmartLock sl= new SmartLock();      UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( null );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( null );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( null );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 1 ); utWriter.lox.CntLogCalls= 0;
                }

                // SmartLock with threadlocks
                {
                    ThreadLock tl1 = new ThreadLock();
                    ThreadLock tl2 = new ThreadLock();
                    ThreadLock tl3 = new ThreadLock();
                    SmartLock  sl= new SmartLock();    UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( tl1 );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( tl2 );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( tl3 );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( tl3 );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( tl3 );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 1 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( tl2 );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( tl1 );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( tl1 );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 1 ); utWriter.lox.CntLogCalls= 0;
                }

                // mixed
                {
                    ThreadLock tl1 = new ThreadLock();
                    ThreadLock tl2 = new ThreadLock();
                    ThreadLock tl3 = new ThreadLock();
                    SmartLock  sl= new SmartLock();     UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( tl1  );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( null );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( null );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( tl2  );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( null );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( tl2  );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 1 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( null );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.AddAcquirer   ( tl3  );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( tl1  );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( tl1  );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 1 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( tl3  );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Safe   );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 1 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 1 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( tl3  );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 1 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( tl2  );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 0 ); utWriter.lox.CntLogCalls= 0;
                    sl.RemoveAcquirer( null );          UT_TRUE( sl.GetSafeness() == Safeness.Unsafe );  UT_TRUE( utWriter.lox.CntLogCalls== 1 ); utWriter.lox.CntLogCalls= 0;
                }
                Report.GetDefault().PopHaltFlags();
        }
    #endif

        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ThreadLock")]
            #endif
        #endif
        public void ThreadLock_HeavyLoad()
        {
            UT_INIT();
            Log.SetVerbosity( new ConsoleLogger(), Verbosity.Verbose, "/" );
            Log.MapThreadName( "UnitTest" );
            Log.SetDomain( "TestTLock", Scope.Filename );

            ThreadLock aLock= new ThreadLock();

            // uncomment this for unsafe mode
            // lock.setUnsafe( true );

            Test_ThreadLock_SharedInt    shared=        new Test_ThreadLock_SharedInt();
            int                            holdTime=    0;
            int                            repeats=    5000;
            bool                        verbose=    false;

            Test_ThreadLock_TestThreadParams p1= new Test_ThreadLock_TestThreadParams( aLock, holdTime, repeats, verbose, shared );
            Test_ThreadLock_TestThreadParams p2= new Test_ThreadLock_TestThreadParams( aLock, holdTime, repeats, verbose, shared );
            Test_ThreadLock_TestThreadParams p3= new Test_ThreadLock_TestThreadParams( aLock, holdTime, repeats, verbose, shared );
            Log.Info("starting three threads");

            Thread t1= new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
            Thread t2= new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
            Thread t3= new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
            t1.Start( p1 );
            t2.Start( p2 );
            t3.Start( p3 );

            // wait until all ended
            while ( t1.IsAlive || t2.IsAlive || t3.IsAlive )
                ALIB.SleepMillis( 1 );

            Log.Info("All threads ended. Shared value=" + shared.val );

            UT_TRUE( shared.val == 0 );

        }

        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ThreadLock")]
            #endif
        #endif
        public void ThreadLock_SpeedTest()
        {
            UT_INIT();

            Log.SetVerbosity( new ConsoleLogger(), Verbosity.Verbose, "/" );
            Log.MapThreadName( "UnitTest" );
            Log.SetDomain( "TestTLock", Scope.Method );

            ThreadLock aLock= new ThreadLock();

            int        repeats=    100000;
            int        rrepeats=    5;

            Ticks stopwatch= new Ticks();
            for ( int r= 0; r < rrepeats; r ++)
            {
                Log.Info("Run " + rrepeats );

                aLock.SetSafeness( Safeness.Unsafe );
                stopwatch.Set();
                for ( int i= 0; i < repeats; i++ )
                {
                    aLock.Acquire();
                    aLock.Release();
                }
                long time= stopwatch.Age().InMillis();
                Log.Info("Safe mode, " + repeats + " lock/unlock ops: " + time + " ms" );

                aLock.SetSafeness( Safeness.Safe );
                stopwatch.Set();
                for ( int i= 0; i < repeats; i++ )
                {
                    //aLock.acquire();
                    //aLock.release();

                    // in java, adding the following two loops, results in similar execution speed
                    for ( int tt= 0; tt < 70; tt++ )
                        i+= tt;
                    for ( int tt= 0; tt < 70; tt++ )
                        i-= tt;
                }
                time= stopwatch.Age().InMillis();
                Log.Info("Unsafe mode, " + repeats + " lock/unlock ops: " + time + " ms" );
            }
        }

        public class Test_ThreadLock_SharedInt
        {
            public int val= 0;
        }

        public class Test_ThreadLock_TestThreadParams
        {
            public        ThreadLock  aLock;
            public        int         holdTime;
            public        int         repeats;
            public        bool        verbose;
            public        int         result= 1;
            public        Test_ThreadLock_SharedInt shared;

            public Test_ThreadLock_TestThreadParams( ThreadLock aLock, int holdTime, int repeats, bool verbose, Test_ThreadLock_SharedInt shared )
            {
                this.aLock=        aLock;
                this.holdTime=  holdTime;
                this.repeats=    repeats;
                this.verbose=    verbose;
                this.shared=    shared;
            }
        }

        public void Test_ThreadLock_Test_run( Object o)
        {
            Test_ThreadLock_TestThreadParams p= o as Test_ThreadLock_TestThreadParams;
            for ( int i= 0; i < p.repeats ; i++ )
            {
                if (p.verbose) { Log.Info("Thread: "+ Thread.CurrentThread.Name +" acuiring lock..."); }
                p.aLock.Acquire();
                if (p.verbose) { Log.Info("Thread: "+ Thread.CurrentThread.Name +" has lock."); }

                    int sVal= ++p.shared.val;

                    ALIB.SleepMillis( p.holdTime );

                    p.shared.val= sVal -1;

                if (p.verbose) { Log.Info("Thread: "+ Thread.CurrentThread.Name +" releasing lock."); }
                p.aLock.Release();
                if (p.verbose) { Log.Info("Thread: "+ Thread.CurrentThread.Name +" released lock."); }
            }

            p.result= 0;
            Log.Info("Thread: "+ Thread.CurrentThread.Name +" terminates.");
        }

    }
}
