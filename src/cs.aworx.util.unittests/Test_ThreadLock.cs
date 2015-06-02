// #################################################################################################
//  com.aworx.util.unittests - AWorx Util
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;

#if AWORX_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if AWORX_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using System.Text;
using com.aworx.util;
using com.aworx.lox;
using com.aworx.lox.loggers;

namespace com.aworx.util.unittests
{
    #if AWORX_MONO_DEVELOP
        [TestFixture ()]
    #endif
    #if AWORX_VSTUDIO
        [TestClass]
    #endif
    public class Test_ThreadLock
    {
        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ThreadLock")]
            #endif
        #endif
        public void ThreadLock_SimpleTests()
        {
            AWXU.HaltOnError=
            AWXU.HaltOnWarning=  false;

            Log.Reset();
            Log.AddLogger( new ConsoleLogger() );
            Log.MapThreadName( "UnitTest" );
            Log.RegDomain( "TestTLock", Log.Scope.Method );
            Log.SetDomain( "AWXU", Log.DomainLevel.All );

            // lock a recursive lock
            ThreadLock aLock= new ThreadLock();

            aLock.Acquire();
            aLock.Release();

            aLock.Acquire();                                Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
            aLock.Acquire();                                Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
            aLock.Release();                                Assert.IsTrue ( !aLock.ToString().StartsWith("null") );

            aLock.Acquire();                                Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
            aLock.Release();                                Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
            aLock.Release();                                Assert.IsTrue (  aLock.ToString().StartsWith("null") );

            // set unsafe
            aLock.SetUnsafe( true );                        Assert.IsTrue ( aLock.ToString().StartsWith("null") );
            aLock.SetUnsafe( false );                       Assert.IsTrue ( aLock.ToString().StartsWith("null") );

            aLock.SetUnsafe( true );                        Assert.IsTrue ( aLock.ToString().StartsWith("null") );
            aLock.Acquire();                                Assert.IsTrue ( aLock.ToString().StartsWith("null") );
            aLock.Release();                                Assert.IsTrue ( aLock.ToString().StartsWith("null") );

            // unsafe
            aLock.Acquire();                                Assert.IsTrue ( aLock.ToString().StartsWith("null") );
            Log.Info("One warning should come now: ");
            aLock.SetUnsafe( false );                       Assert.IsTrue ( aLock.ToString().StartsWith("null") );

            // safe (new lock)
            aLock= new ThreadLock();
            aLock.Acquire();                                Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
            Log.Info("One warning should come now: ");
            aLock.SetUnsafe( true );                        Assert.IsTrue ( !aLock.ToString().StartsWith("null") );


            // test warnings (10) locks:
            aLock= new ThreadLock();
            Log.Info("Two warnings should come now: ");
            for (int i= 0; i<20; i++)
                aLock.Acquire();
            Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
            for (int i= 0; i<20; i++)
                aLock.Release();
            Assert.IsTrue ( aLock.ToString().StartsWith("null") );

            // test a non-recursive lock
            aLock= new ThreadLock( false );
            aLock.Acquire();                Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
            aLock.Acquire();                Assert.IsTrue ( !aLock.ToString().StartsWith("null") );
            aLock.Release();                Assert.IsTrue ( aLock.ToString().StartsWith("null") );

            Log.Info("One warning should come now: ");
            aLock.Release();                Assert.IsTrue ( aLock.ToString().StartsWith("null") );
        }

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ThreadLock")]
            #endif
        #endif
        public void ThreadLock_Threaded()
        {
            Log.Reset();

            Log.AddLogger( new ConsoleLogger() );
            Log.MapThreadName( "UnitTest" );
            Log.RegDomain( "TestTLock", Log.Scope.SourceFile );
            Log.SetDomain( "AWXU", Log.DomainLevel.All );

            ThreadLock aLock= new ThreadLock();

            Test_ThreadLock_SharedInt shared= new Test_ThreadLock_SharedInt();

            Log.Info("starting thread locked");
            aLock.Acquire();
            Test_ThreadLock_TestThreadParams tParam= new Test_ThreadLock_TestThreadParams( aLock, 10, 1, true, shared );

            Thread thread = new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
            thread.Name= "A Thread";
            thread.Start( tParam );

            Log.Info("We wait 1100 ms. This should give a warning! ");
            AWXU.SleepMillis( 1100 );
            aLock.Release();

            // wait until t ended
            while (thread.IsAlive)
                AWXU.SleepMillis( 1 );

            // now we do the same with a higher wait limit, no erro should come
            aLock.waitWarningTimeLimitInMillis= 5;
            aLock.Acquire();
            tParam= new Test_ThreadLock_TestThreadParams( aLock, 10, 1, true, shared );
            thread = new Thread( new ParameterizedThreadStart( Test_ThreadLock_Test_run ) );
            thread.Start( tParam );
            Log.Info("We wait 1 ms. This should NOT give a warning! ");
            AWXU.SleepMillis( 1 );
            aLock.Release();

            // wait until t ended
            while (thread.IsAlive)
                AWXU.SleepMillis( 1 );

        }

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ThreadLock")]
            #endif
        #endif
        public void ThreadLock_HeavyLoad()
        {
            Log.Reset();
            Log.AddLogger( new ConsoleLogger() );
            Log.MapThreadName( "UnitTest" );
            Log.RegDomain( "TestTLock", Log.Scope.SourceFile );
            Log.SetDomain( "AWXU", Log.DomainLevel.All );

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
                AWXU.SleepMillis( 1 );

            Log.Info("All threads ended. Shared value=" + shared.val );

            Assert.IsTrue( shared.val == 0 );

        }

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ThreadLock")]
            #endif
        #endif
        public void ThreadLock_SpeedTest()
        {
            Log.Reset();

            Log.AddLogger( new ConsoleLogger() );
            Log.MapThreadName( "UnitTest" );
            Log.RegDomain( "TestTLock", Log.Scope.Method );
            Log.SetDomain( "AWXU", Log.DomainLevel.All );

            ThreadLock aLock= new ThreadLock();

            int        repeats=    100000;
            int        rrepeats=    5;

            Ticks stopwatch= new Ticks();
            for ( int r= 0; r < rrepeats; r ++)
            {
                Log.Info("Run " + rrepeats );

                aLock.SetUnsafe( false );
                stopwatch.Set();
                for ( int i= 0; i < repeats; i++ )
                {
                    aLock.Acquire();
                    aLock.Release();
                }
                long time= stopwatch.Age().InMillis();
                Log.Info("Safe mode, " + repeats + " lock/unlock ops: " + time + " ms" );

                aLock.SetUnsafe( true );
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
            public        ThreadLock    aLock;
            public        int         holdTime;
            public        int            repeats;
            public        bool        verbose;
            public         int         result= 1;
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

                    AWXU.SleepMillis( p.holdTime );

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
