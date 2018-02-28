// #################################################################################################
//  cs.aworx.unittests - AWorx Util
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using ut_cs_aworx;

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
    public class CS_Ticks    : AWorxUnitTesting
    {
        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_Ticks")]
            #endif
        #endif
        public void Basics()
        {
            UT_INIT();

            Log.SetVerbosity( new ConsoleLogger(), Verbosity.Verbose, "/" );
            Log.MapThreadName( "UnitTest" );
            Log.SetDomain( "TickWatch", Scope.Method );

            Log.Info( "\n### TicksBasics ###" );

            // check times
            {
                Ticks t= new Ticks();
                t.FromNanos( 42 );    // beyond resolution in C#:  UT_EQ( t.InNanos(),        42L);
                                        UT_EQ( t.InMicros(),        0L );
                                        UT_EQ( t.InMillis(),        0L );
                                        UT_EQ( t.InSeconds(),        0L );
                t.FromMicros( 42 );    UT_EQ( t.InNanos(),        42000L );
                                        UT_EQ( t.InMicros(),        42L );
                                        UT_EQ( t.InMillis(),        0L );
                                        UT_EQ( t.InSeconds(),        0L );
                t.FromMillis( 42 );    UT_EQ( t.InNanos(),        42000000L );
                                        UT_EQ( t.InMicros(),        42000L );
                                        UT_EQ( t.InMillis(),        42L );
                                        UT_EQ( t.InSeconds(),        0L );
                t.FromSeconds( 42 );    UT_EQ( t.InNanos(),        42000000000L );
                                        UT_EQ( t.InMicros(),        42000000L );
                                        UT_EQ( t.InMillis(),        42000L );
                                        UT_EQ( t.InSeconds(),        42L );
                Ticks diff= new Ticks();
                diff.FromMillis( 100 );
                t.Add( diff );            UT_EQ( t.InNanos(),        42100000000L );
                                        UT_EQ( t.InMicros(),        42100000L );
                                        UT_EQ( t.InMillis(),        42100L );
                                        UT_EQ( t.InSeconds(),        42L );
                t.Sub( diff );            UT_EQ( t.InNanos(),        42000000000L );
                                        UT_EQ( t.InMicros(),        42000000L );
                                        UT_EQ( t.InMillis(),        42000L );
                                        UT_EQ( t.InSeconds(),        42L );

                t.FromMillis( 100 ); UT_EQ( t.InHertz()  ,    10.0 );
                t.FromMillis( 300 ); UT_EQ( t.InHertz(0) ,    3.0 );
                                        UT_EQ( t.InHertz(1) ,    3.3 );
                                        UT_EQ( t.InHertz(2) ,    3.33 );
                                        UT_EQ( t.InHertz(5) ,    3.33333 );
            }

            // check internal frequency
            {
                double freq= Ticks.InternalFrequency;
                Log.Info( "TickWatch InternalFrequency:   " + freq );
                UT_TRUE ( freq >= 1000000.0 );
            }

            // check TickWatch creation time
            {
                Ticks creationTimeDiff=  new Ticks();
                creationTimeDiff.Sub( Ticks.CreationTime );
                Log.Info( "TickWatch library creation was: " + creationTimeDiff.InNanos  () + "ns ago" );
                Log.Info( "TickWatch library creation was: " + creationTimeDiff.InMicros () + "µs ago" );
                Log.Info( "TickWatch library creation was: " + creationTimeDiff.InMillis () + "ms ago" );
                Log.Info( "TickWatch library creation was: " + creationTimeDiff.InSeconds() + "s ago"  );
                UT_TRUE ( creationTimeDiff.InNanos  () > 100  ); // It should really take 100 nanoseconds to get here!
                UT_TRUE ( creationTimeDiff.InSeconds() < 3600 ); // these test will probably not last an hour
            }

            // check if we could sleep for 100ms
            {
                Ticks start= new Ticks();
                ALIB.SleepMillis( 30 );
                Ticks sleepTime= new Ticks();
                sleepTime.Sub( start );
                Log.Info( "TickWatch diff after 100ms sleep: " + sleepTime.InMillis() +" ms" );
                UT_TRUE ( sleepTime.InMillis() > 28 );
                UT_TRUE ( sleepTime.InMillis() < 150 ); // should work even on heavily loaded machines
            }
        }

        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_Ticks")]
            #endif
        #endif
        public void SpeedTest()
        {
            UT_INIT();

            Log.SetVerbosity( new ConsoleLogger(), Verbosity.Verbose, "/" );
            Log.MapThreadName( "UnitTest" );
            Log.SetDomain( "TickWatch", Scope.Method );

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
                UT_TRUE ( averageNanos < 20000 ); // this is much slower on Windows than on mono/linux.
            }
        }


        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_Ticks")]
            #endif
        #endif
        public void DateTimeConversion()
        {
            UT_INIT();

            Log.SetVerbosity( new ConsoleLogger(), Verbosity.Verbose, "/" );
            Log.MapThreadName( "UnitTest" );
            Log.SetDomain( "TickWatch", Scope.Method );

            Log.Info( "DateTime.MinValue(): "    + ( DateTime.MinValue.ToString() )     );
            Log.Info( "DateTime.MaxValue(): "    + ( DateTime.MaxValue.ToString() )     );

            Ticks ticksNow= new Ticks();

            // roundtrip 1
            long millisEpochNow=    ticksNow.InEpochMillis();
            ticksNow.SetFromEpochMillis( millisEpochNow );
            long ticksNowFromEpoch= ticksNow.Raw();

            UT_TRUE( Math.Abs( ticksNow.Raw() - ticksNowFromEpoch ) < 50000 );

            // roundtrip 2
            long millis5_1_70_3_51=           0
                                      +       (  4L * 24L * 60L * 60L * 1000L )
                                      +       (  3L       * 60L * 60L * 1000L )
                                      +       ( 51L             * 60L * 1000L );


            long millis5_1_71_3_51=            millis5_1_70_3_51
                                      +      ( 365L * 24L * 60L * 60L * 1000L );

            Ticks  ticks5_1_70_3_51= new Ticks(); ticks5_1_70_3_51.SetFromEpochMillis( millis5_1_70_3_51 );
            Ticks  ticks5_1_71_3_51= new Ticks(); ticks5_1_71_3_51.SetFromEpochMillis( millis5_1_71_3_51 );
            UT_TRUE( ticks5_1_70_3_51.Raw() < ticks5_1_71_3_51.Raw() );


            long millis5_1_70_3_51_back= ticks5_1_70_3_51.InEpochMillis();
            long millis5_1_71_3_51_back= ticks5_1_71_3_51.InEpochMillis();


            UT_TRUE( millis5_1_70_3_51_back == millis5_1_70_3_51 );
            UT_TRUE( millis5_1_71_3_51_back == millis5_1_71_3_51 );

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

        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_Ticks")]
            #endif
        #endif
        public void Ages()
        {
            UT_INIT();

            Log.SetVerbosity( new ConsoleLogger(), Verbosity.Verbose, "/" );
            Log.MapThreadName( "UnitTest" );
            Log.SetDomain( "TickWatch", Scope.Method );

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
                UT_TRUE( ttAverageInNanos  < 5000 );
                UT_TRUE( ttAverageInMicros <= 5 );
                UT_TRUE( ttAverageInMillis == 0 );
            }

            // minimum sleep time measuring
            {
                tt.Reset();
                for (int i= 0 ; i< 100 ; i++)
                {
                    ALIB.SleepNanos( 1 );
                    tt.Sample();
                }
                Ticks avg= tt.GetAverage();
                Log.Info(  "100 probes of 1 ns of sleep leads to average sleep time of " + avg.InNanos() + " ns");
            }


            // sleep two times 20 ms and probe it to an average
            {
                tt.Reset();
                tt.Start();
                ALIB.SleepMillis( 20 );
                tt.Sample();


                ALIB.SleepMillis( 80 );

                tt.Start();
                ALIB.SleepMillis( 20 );
                tt.Sample();

                long    cnt=tt.GetSampleCnt();
                long    avg=tt.GetAverage().InMillis();
                double    hertz=tt.GetAverage().InHertz( 1 );
                Log.Info( "TickWatch sum is " + tt.GetCumulated().InMillis() + " after " + cnt + " times 20 ms sleep" );
                Log.Info( "  average is: "    + avg + " ms" );
                Log.Info( "  in Hertz:   "    + hertz );
                UT_TRUE( hertz < 53 );
                UT_TRUE( hertz > 30 ); // should work even on heavily loaded machines
                UT_EQ( 2, cnt );
                UT_TRUE( avg >= 18 );
                UT_TRUE( avg < 45 ); // should work even on heavily loaded machines
            }

            // Ticks Since
            {
                Ticks tt1= new Ticks(); tt1.FromSeconds( 1000 );
                Ticks tt2= new Ticks(); tt2.FromSeconds( 1001 );

                UT_TRUE ( tt2.Since( tt1 ).InMillis() == 1000L );
                UT_TRUE ( tt2.Since( tt1 ).InMicros() == 1000L * 1000L );
                UT_TRUE ( tt2.Since( tt1 ).InNanos () == 1000L * 1000L * 1000L );
            }
        }

        #if ALIB_NUNIT
            [Test ()]
        #endif
        #if ALIB_IDE_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_Ticks")]
            #endif
        #endif
        public void MeasureIncreasingDoublingLoop()
        {

            UT_INIT();

            Log.SetVerbosity( new ConsoleLogger(), Verbosity.Verbose, "/" );
            Log.MapThreadName( "UnitTest" );
            Log.SetDomain( "TickWatch", Scope.Method );

            Log.Info( "This test shows quite nicely, how the just in time compiler steps in when we are looping heavily!" );

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

                Log.Info( new Object[] {  "Search loops {:6}:  time needed: {:8} / {:8}.   Ratio String/AString: {:%.2}",
                                qtyLoops,sSample.InNanos(), aSample.InNanos(), ( ((double) sSample.Raw()) / ((double) aSample.Raw()) )  }  );
            }

        }

    }
}
