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
    public class Test_Ticks
    {
        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_Ticks")]
            #endif
        #endif
        public void Basics()
        {
            Log.Reset();

            Log.AddLogger( new ConsoleLogger() );
            Log.MapThreadName( "UnitTest" );
            Log.RegDomain( "TickWatch", Log.Scope.Method );

            Log.Info( "\n### TicksBasics ###" );

            // check times
            {
                Ticks t= new Ticks();
                t.FromNanos( 42 );    // beyond resolution in C#:  Assert.AreEqual( t.InNanos(),        42L);
                                        Assert.AreEqual( t.InMicros(),        0L );
                                        Assert.AreEqual( t.InMillis(),        0L );
                                        Assert.AreEqual( t.InSeconds(),        0L );
                t.FromMicros( 42 );    Assert.AreEqual( t.InNanos(),        42000L );
                                        Assert.AreEqual( t.InMicros(),        42L );
                                        Assert.AreEqual( t.InMillis(),        0L );
                                        Assert.AreEqual( t.InSeconds(),        0L );
                t.FromMillis( 42 );    Assert.AreEqual( t.InNanos(),        42000000L );
                                        Assert.AreEqual( t.InMicros(),        42000L );
                                        Assert.AreEqual( t.InMillis(),        42L );
                                        Assert.AreEqual( t.InSeconds(),        0L );
                t.FromSeconds( 42 );    Assert.AreEqual( t.InNanos(),        42000000000L );
                                        Assert.AreEqual( t.InMicros(),        42000000L );
                                        Assert.AreEqual( t.InMillis(),        42000L );
                                        Assert.AreEqual( t.InSeconds(),        42L );
                Ticks diff= new Ticks();
                diff.FromMillis( 100 );
                t.Add( diff );            Assert.AreEqual( t.InNanos(),        42100000000L );
                                        Assert.AreEqual( t.InMicros(),        42100000L );
                                        Assert.AreEqual( t.InMillis(),        42100L );
                                        Assert.AreEqual( t.InSeconds(),        42L );
                t.Sub( diff );            Assert.AreEqual( t.InNanos(),        42000000000L );
                                        Assert.AreEqual( t.InMicros(),        42000000L );
                                        Assert.AreEqual( t.InMillis(),        42000L );
                                        Assert.AreEqual( t.InSeconds(),        42L );

                t.FromMillis( 100 ); Assert.AreEqual( t.InHertz()  ,    10.0 );
                t.FromMillis( 300 ); Assert.AreEqual( t.InHertz(0) ,    3.0 );
                                        Assert.AreEqual( t.InHertz(1) ,    3.3 );
                                        Assert.AreEqual( t.InHertz(2) ,    3.33 );
                                        Assert.AreEqual( t.InHertz(5) ,    3.33333 );
            }

            // check internal frequency
            {
                double freq= Ticks.InternalFrequency;
                Log.Info( "TickWatch InternalFrequency:   " + freq );
                Assert.IsTrue ( freq >= 1000000.0 );
            }

            // check TickWatch creation time
            {
                Ticks creationTimeDiff=  new Ticks();
                creationTimeDiff.Sub( Ticks.CreationTime );
                Log.Info( "TickWatch library creation was: " + creationTimeDiff.InNanos  () + "ns ago" );
                Log.Info( "TickWatch library creation was: " + creationTimeDiff.InMicros () + "µs ago" );
                Log.Info( "TickWatch library creation was: " + creationTimeDiff.InMillis () + "ms ago" );
                Log.Info( "TickWatch library creation was: " + creationTimeDiff.InSeconds() + "s ago"  );
                Assert.IsTrue ( creationTimeDiff.InNanos  () > 100  ); // It should really take 100 nanoseconds to get here!
                Assert.IsTrue ( creationTimeDiff.InSeconds() < 3600 ); // these test will probably not last an hour
            }

            // check if we could sleep for 100ms
            {
                Ticks start= new Ticks();
                AWXU.SleepMillis( 30 );
                Ticks sleepTime= new Ticks();
                sleepTime.Sub( start );
                Log.Info( "TickWatch diff after 100ms sleep: " + sleepTime.InMillis() +" ms" );
                Assert.IsTrue ( sleepTime.InMillis() > 28 );
                Assert.IsTrue ( sleepTime.InMillis() < 150 ); // should work even on heavily loaded machines
            }
        }

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_Ticks")]
            #endif
        #endif
        public void SpeedTest()
        {
            Log.Reset();

            Log.AddLogger( new ConsoleLogger() );
            Log.MapThreadName( "UnitTest" );
            Log.RegDomain( "TickWatch", Log.Scope.Method );

            Log.Info(  "\n### TicksSpeedTest ###" );
            for (int runs= 0; runs < 5; runs ++ )
            {
                int aLotOf= 100;
                Ticks t= new Ticks();
                Ticks tkMeasure= new Ticks();
                for (int i= 0; i < aLotOf; i++ )
                    t.Set();

                long nanos= tkMeasure.Age().InNanos();
                long averageNanos= nanos/ aLotOf ;
                Log.Info(   "Doing " + aLotOf + " Ticks.Set() calls took " + nanos + " ns. This is an average of " + averageNanos + " nanoseconds per call" );
                Assert.IsTrue ( averageNanos < 20000 ); // this is much slower on Windows than on mono/linux.
            }
        }


        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_Ticks")]
            #endif
        #endif
        public void DateTimeConversion()
        {
            Log.Reset();

            Log.AddLogger( new ConsoleLogger() );
            Log.MapThreadName( "UnitTest" );
            Log.RegDomain( "TickWatch", Log.Scope.Method );

            Log.Info( "DateTime.MinValue(): "    + ( DateTime.MinValue.ToString() )     );
            Log.Info( "DateTime.MaxValue(): "    + ( DateTime.MaxValue.ToString() )     );

            Ticks ticksNow= new Ticks();

            // roundtrip 1
            long millisEpochNow=    ticksNow.InEpochMillis();
            ticksNow.SetFromEpochMillis( millisEpochNow );
            long ticksNowFromEpoch= ticksNow.Raw();

            Assert.IsTrue( Math.Abs( ticksNow.Raw() - ticksNowFromEpoch ) < 50000 );

            // roundtrip 2
            long millis5_1_70_3_51=           0
                                      +       (  4L * 24L * 60L * 60L * 1000L )
                                      +       (  3L       * 60L * 60L * 1000L )
                                      +       ( 51L             * 60L * 1000L );


            long millis5_1_71_3_51=            millis5_1_70_3_51
                                      +      ( 365L * 24L * 60L * 60L * 1000L );

            Ticks  ticks5_1_70_3_51= new Ticks(); ticks5_1_70_3_51.SetFromEpochMillis( millis5_1_70_3_51 );
            Ticks  ticks5_1_71_3_51= new Ticks(); ticks5_1_71_3_51.SetFromEpochMillis( millis5_1_71_3_51 );
            Assert.IsTrue( ticks5_1_70_3_51.Raw() < ticks5_1_71_3_51.Raw() );


            long millis5_1_70_3_51_back= ticks5_1_70_3_51.InEpochMillis();
            long millis5_1_71_3_51_back= ticks5_1_71_3_51.InEpochMillis();


            Assert.IsTrue( millis5_1_70_3_51_back == millis5_1_70_3_51 );
            Assert.IsTrue( millis5_1_71_3_51_back == millis5_1_71_3_51 );

            // add 1 day, 2h, 3min and 4sec  days:

            Ticks tomorrow= new Ticks( ticksNow );
            Ticks span= new Ticks();
            span.FromMillis( (long) (new TimeSpan( 1,2,3,4 )).TotalMilliseconds);
            tomorrow.Add ( span );

            Log.Info( "Today: is:        "    +  ( DateTime.Now.ToString()                                 ) );
            Log.Info( "Today: is:        "    +  ( ticksNow                         .InDotNetDateTime().ToString() ) );
            Log.Info( "Today: is:        "    +  ( (new Ticks(ticksNowFromEpoch))   .InDotNetDateTime().ToString() ) );
            Log.Info( "+1d, 2h,3m,4s:    "    +  ( tomorrow                         .InDotNetDateTime().ToString() ) );
            Log.Info( "5.1.70 3:51:00:   "    +  ( ticks5_1_70_3_51                 .InDotNetDateTime().ToString() ) );
            Log.Info( "5.1.71 3:51:00:   "    +  ( ticks5_1_71_3_51                 .InDotNetDateTime().ToString() ) );
        }

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_Ticks")]
            #endif
        #endif
        public void Ages()
        {
            Log.Reset();

            Log.AddLogger( new ConsoleLogger() );
            Log.MapThreadName( "UnitTest" );
            Log.RegDomain( "TickWatch", Log.Scope.Method );

            TickWatch tt=new TickWatch();
            // minimum time measuring
            {
                tt.Start();
                tt.Sample();
                tt.Reset(); // we need to do this once before, otherwise C# might be
                // very slow. Obviously the optimizer...
                tt.Start();
                tt.Sample();

                long ttAverageInNanos=tt.GetAverage().InNanos();
                long ttAverageInMicros=tt.GetAverage().InMicros();
                long ttAverageInMillis=tt.GetAverage().InMillis();

                Log.Info( "TickWatch minimum measurement nanos:    "    + ttAverageInNanos );
                Log.Info( "TickWatch minimum measurement micros:   "    + ttAverageInMicros );
                Log.Info( "TickWatch minimum measurement millis:   "    + ttAverageInMillis );
                Assert.IsTrue( ttAverageInNanos  < 5000 );
                Assert.IsTrue( ttAverageInMicros <= 5 );
                Assert.IsTrue( ttAverageInMillis == 0 );
            }

            // minimum sleep time measuring
            {
                tt.Reset();
                for (int i= 0 ; i< 100 ; i++)
                {
                    AWXU.SleepNanos( 1 );
                    tt.Sample();
                }
                Ticks avg= tt.GetAverage();
                Log.Info(  "100 probes of 1 ns of sleep leads to average sleep time of " + avg.InNanos() + " ns");
            }


            // sleep two times 20 ms and probe it to an average
            {
                tt.Reset();
                tt.Start();
                AWXU.SleepMillis( 20 );
                tt.Sample();


                AWXU.SleepMillis( 80 );

                tt.Start();
                AWXU.SleepMillis( 20 );
                tt.Sample();

                long    cnt=tt.GetSampleCnt();
                long    avg=tt.GetAverage().InMillis();
                double    hertz=tt.GetAverage().InHertz( 1 );
                Log.Info( "TickWatch sum is " + tt.GetCumulated().InMillis() + " after " + cnt + " times 20 ms sleep" );
                Log.Info( "  average is: "    + avg + " ms" );
                Log.Info( "  in Hertz:   "    + hertz );
                Assert.IsTrue( hertz < 53 );
                Assert.IsTrue( hertz > 30 ); // should work even on heavily loaded machines
                Assert.AreEqual( 2, cnt );
                Assert.IsTrue( avg >= 18 );
                Assert.IsTrue( avg < 45 ); // should work even on heavily loaded machines
            }

            // Ticks Since
            {
                Ticks tt1= new Ticks(); tt1.FromSeconds( 1000 );
                Ticks tt2= new Ticks(); tt2.FromSeconds( 1001 );

                Assert.IsTrue ( tt2.Since( tt1 ).InMillis() == 1000L );
                Assert.IsTrue ( tt2.Since( tt1 ).InMicros() == 1000L * 1000L );
                Assert.IsTrue ( tt2.Since( tt1 ).InNanos () == 1000L * 1000L * 1000L );
            }
        }

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_Ticks")]
            #endif
        #endif
        public void MeasureIncreasingDoublingLoop()
        {

            Log.Reset();

            Log.AddLogger( new ConsoleLogger() );
            Log.MapThreadName( "UnitTest" );
            Log.RegDomain( "TickWatch", Log.Scope.Method );

            Log.Info( "This test shows quite nicely, how the just in time compiler steps in when we are looping heavily!" );

            #if ALOX_DEBUG
                #if AWORX_VSTUDIO
                    ((ConsoleLogger) Log.GetLogger( "Console" )).EnableVSDebugConsole=
                #endif
                ((ConsoleLogger) Log.GetLogger( "Console" )).EnableAppConsole=        true;
            #endif

            String testString= "-------------------------------------------------------------------------------------------#";
            AString testAString= new AString( testString );

            TickWatch ttString= new TickWatch();
            TickWatch ttAString= new TickWatch();
            for (int run= 4; run < 20; run++ )
            {
                int qtyLoops= (run == 0)  ? 0 : (1 << (run -1));

                // use String.IndexOf()
                ttString.Reset();
                    int nonOptimizableUsedResultValue= 0;
                    for (int i= 0; i < qtyLoops; i++ )
                        nonOptimizableUsedResultValue+= testString.IndexOf( '#' );
                Ticks sSample= ttString.Sample();


                // use AString.IndexOf()
                ttAString.Reset();
                    for (int i= 0; i < qtyLoops; i++ )
                        nonOptimizableUsedResultValue+= testAString.IndexOf( '#' );
                Ticks aSample= ttAString.Sample();


                if ( nonOptimizableUsedResultValue > -1 ) // this is always true, just for the sake that the compiler does not optimize the whole code!
                    Log.Info(  Log.Buf().Append( "Search loops " )     .Field().Append( qtyLoops.ToString() )       .Field( 6 )
                                        .Append( ":  time needed: " )  .Field().Append( (int)    sSample.InNanos() ).Field( 8 )
                                        .Append(  " / "  )             .Field().Append( (int)    aSample.InNanos() ).Field( 8 )
                                        .Append( "   Ratio String/AString: " ) .Append( ((double) sSample.Raw()) / ((double) aSample.Raw()) )
                            );
            }

            #if ALOX_DEBUG
                #if AWORX_VSTUDIO
                    ((ConsoleLogger) Log.GetLogger( "Console" )).EnableVSDebugConsole=
                #endif
                ((ConsoleLogger) Log.GetLogger( "Console" )).EnableAppConsole=        true;
            #endif
        }

    }
}
