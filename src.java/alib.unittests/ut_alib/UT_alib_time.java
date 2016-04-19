// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_alib;
import java.util.*;

import org.junit.Test;

import ut_com_aworx_uttools.AUnitTest;

import com.aworx.lib.ALIB;
import com.aworx.lib.strings.AString;
import com.aworx.lib.time.TickSpan;
import com.aworx.lib.time.TickWatch;
import com.aworx.lib.time.Ticks;
import com.aworx.lox.*;


public class UT_alib_time  extends AUnitTest
{
    @SuppressWarnings("static-method")
    @Test
    public void Basics()
    {
        UT_INIT();
        
        Log.setDomain( "Basics", Scope.METHOD );
        Log.info( "\n### TicksBasics ###" );

        // check times
        {
            Ticks t= new Ticks();
            t.fromNanos( 42 );    UT_EQ( t.inNanos(),             42L);
                                  UT_EQ( t.inMicros(),             0L );
                                  UT_EQ( t.inMillis(),             0L );
                                  UT_EQ( t.inSeconds(),            0L );
            t.fromMicros( 42 );   UT_EQ( t.inNanos(),          42000L );
                                  UT_EQ( t.inMicros(),            42L );
                                  UT_EQ( t.inMillis(),             0L );
                                  UT_EQ( t.inSeconds(),            0L );
            t.fromMillis( 42 );   UT_EQ( t.inNanos(),       42000000L );
                                  UT_EQ( t.inMicros(),         42000L );
                                  UT_EQ( t.inMillis(),            42L );
                                  UT_EQ( t.inSeconds(),            0L );
            t.fromSeconds( 42 );  UT_EQ( t.inNanos(),    42000000000L );
                                  UT_EQ( t.inMicros(),      42000000L );
                                  UT_EQ( t.inMillis(),         42000L );
                                  UT_EQ( t.inSeconds(),           42L );
            Ticks diff= new Ticks();
            diff.fromMillis( 100 );
            t.add( diff );        UT_EQ( t.inNanos(),     42100000000L );
                                  UT_EQ( t.inMicros(),       42100000L );
                                  UT_EQ( t.inMillis(),          42100L );
                                  UT_EQ( t.inSeconds(),            42L );
            t.sub( diff );        UT_EQ( t.inNanos(),     42000000000L );
                                  UT_EQ( t.inMicros(),       42000000L );
                                  UT_EQ( t.inMillis(),          42000L );
                                  UT_EQ( t.inSeconds(),            42L );

            t.fromMillis( 100 );  UT_TRUE  ( t.inHertz()  ==   10.0      );
            t.fromMillis( 300 );  UT_TRUE  ( t.inHertz(0) ==    3.0      );
                                  UT_TRUE  ( t.inHertz(1) ==    3.3      );
                                  UT_TRUE  ( t.inHertz(2) ==    3.33     );
                                  UT_TRUE  ( t.inHertz(5) ==    3.33333  );
        }

        // check internal frequency
        {
            double freq= Ticks.internalFrequency();
            Log.info( "Ticks InternalFrequency:   " + freq );
            UT_TRUE ( freq >= 1000000.0 );
        }

        // check Ticks creation time
        {
            Ticks creationTimeDiff=  new Ticks();
            creationTimeDiff.sub( Ticks.creationTime() );
            Log.info( "Tick library creation was: " + creationTimeDiff.inNanos  () + "ns ago" );
            Log.info( "Tick library creation was: " + creationTimeDiff.inMicros () + "µs ago" );
            Log.info( "Tick library creation was: " + creationTimeDiff.inMillis () + "ms ago" );
            Log.info( "Tick library creation was: " + creationTimeDiff.inSeconds() + "s ago"  );
            UT_TRUE ( creationTimeDiff.inNanos  () > 100  ); // It should really take 100 nanoseconds to get here!
            UT_TRUE ( creationTimeDiff.inSeconds() < 3600 ); // these test will probably not last an hour
        }

        // check if we could sleep for 30ms
        {
            Ticks start= new Ticks();
                ALIB.sleepMillis( 30 );
            Ticks sleepTime= new Ticks();
            sleepTime.sub( start );
            Log.info( "Tick diff after 100ms sleep: " + sleepTime.inMillis() +" ms" );
            UT_TRUE ( sleepTime.inMillis() > 28 );
            UT_TRUE ( sleepTime.inMillis() < 150 ); // should work even on heavily loaded machines
        }
    }

    @SuppressWarnings("static-method")
    @Test
    public void SpeedTest()
    {
        UT_INIT();
        
        Log.setDomain( "SpeedTest", Scope.METHOD );

        Log.info(  "\n### TicksSpeedTest ###" );
        for (int runs= 0; runs < 5; runs ++ )
        {
            int aLotOf= 100;
            Ticks t= new Ticks();
            Ticks tkMeasure= new Ticks();
            for (int i= 0; i < aLotOf; i++ )
                t.set();

            long nanos= tkMeasure.age().inNanos();
            long averageNanos= nanos/ aLotOf ;
            Log.info(   "Doing " + aLotOf + " Ticks.set() calls took " + nanos + " ns. This is an average of " + averageNanos + " nanoseconds per call" );
            UT_TRUE ( averageNanos < 500 ); // should work even on heavily loaded machines
        }
    }



    @SuppressWarnings("static-method")
    @Test
    public void DateTimeConversion()
    {
        UT_INIT();
        
        Log.setDomain( "DtTmConv", Scope.METHOD );

        Ticks ticksNow= new Ticks();

        // roundtrip 1
        long millisEpochNow=    ticksNow.inEpochMillis();
        UT_TRUE ( Math.abs(millisEpochNow - (new Date()).getTime() ) <= 1);
        Ticks ticksNowFromEpoch= new Ticks();  ticksNowFromEpoch.setFromEpochMillis    ( millisEpochNow );


        // roundtrip 2
        Ticks ticksTodayFromDate=    new Ticks(0L);
        ticksTodayFromDate.setFromEpochMillis( (new Date()).getTime() );
        ticksNow.set();
        UT_TRUE ( Math.abs( ticksTodayFromDate.inMillis() - ticksNow.inMillis() ) <= 1 );


        long millis5_1_70_3_51=        0
                                  +    (  4L * 24L * 60L * 60L * 1000L )
                                  +    (  3L       * 60L * 60L * 1000L )
                                  +    ( 51L             * 60L * 1000L );


        long millis5_1_71_3_51=            millis5_1_70_3_51
                                  +    ( 365L * 24L * 60L * 60L * 1000L );

        Ticks  ticks5_1_70_3_51= new Ticks(); ticks5_1_70_3_51.setFromEpochMillis( millis5_1_70_3_51 );
        Ticks  ticks5_1_71_3_51= new Ticks(); ticks5_1_71_3_51.setFromEpochMillis( millis5_1_71_3_51 );


        Calendar calendar= new GregorianCalendar();
        calendar.set(1969, 4, 14, 8, 30);
        long millis_14_05_69_8_30= calendar.getTimeInMillis();

        Ticks ticks_14_05_69_8_30=  new Ticks(); ticks_14_05_69_8_30.setFromEpochMillis( millis_14_05_69_8_30 );

        // add 1 day, 2h, 3min and 4sec  days:
        Ticks tomorrow= new Ticks( ticksNow );

        TickSpan span= new TickSpan();
        span.days=        1;
        span.hours=        2;
        span.minutes=    3;
        span.seconds=    4;
        tomorrow.add( span.get() );



        Log.info( "Java Date conversion:    ");
        Log.info( "Today: is:         "     +  ( (new Date()).toString() ) );
        Log.info( "Today: is:         "     +  ( ticksNow.inJavaDate( null ).toString() ) );
        Log.info( "Today: is:         "     +  (  ( new Date          ( millisEpochNow)             ).toString() ) );
        Log.info( "Today: is:         "     +  ( ticksNowFromEpoch.inJavaDate( null ).toString() ) );
        Log.info( "+1d, 2h,3m,4s:     "     +  ( tomorrow.inJavaDate( null ).toString() ) );
        Log.info( "5.1.70 3:51:00:    "     +  ( ticks5_1_70_3_51.inJavaDate( null ).toString() ) );
        Log.info( "5.1.71 3:51:00:    "     +  ( ticks5_1_71_3_51.inJavaDate( null ).toString() ) );
        Log.info( "14.5.69 8:30:00:   "     +  ( ticks_14_05_69_8_30.inJavaDate( null ).toString() ) );

        GregorianCalendar cal= new GregorianCalendar();
        Log.info( "Java Calendar conversion:    ");
        Log.info( "Today: is:         "    +  ( ticksNow.inJavaCalendar( null ).getTime().toString() ) );
        cal.setTimeInMillis( millisEpochNow );
        Log.info( "Today: is:         "    +  (  cal                                              .toString() ) );
        Log.info( "Today: is:         "    +  ( ticksNowFromEpoch.inJavaCalendar( null ).getTime().toString() ) );
        Log.info( "+1d, 2h,3m,4s:     "    +  ( tomorrow.inJavaCalendar( null ).getTime().toString() ) );
        Log.info( "5.1.70 3:51:00:    "    +  ( ticks5_1_70_3_51.inJavaCalendar( null ).getTime().toString() ) );
        Log.info( "5.1.71 3:51:00:    "    +  ( ticks5_1_71_3_51.inJavaCalendar( null ).getTime().toString() ) );
        Log.info( "14.5.69 8:30:00:   "    +  ( ticks_14_05_69_8_30.inJavaCalendar( null ).getTime().toString() ) );
    }


    @SuppressWarnings("static-method")
    @Test
    public void Ages()
    {
        UT_INIT();
        
        Log.setDomain( "Ages", Scope.METHOD );

        TickWatch tt= new TickWatch();

        // minimum time measuring
        {
            tt.start();  tt.sample();    tt.reset(); // we need to do this once before, otherwise C# might be
                                                     // very slow. Obviously the optimizer...
            tt.start();  tt.sample();

            long ttAverageInNanos=    tt.getAverage().inNanos();
            long ttAverageInMicros=   tt.getAverage().inMicros();
            long ttAverageInMillis=   tt.getAverage().inMillis();

            Log.info( "Ticks minimum measurement nanos:    "    + ttAverageInNanos        );
            Log.info( "Ticks minimum measurement micros:   "    + ttAverageInMicros     );
            Log.info( "Ticks minimum measurement millis:   "    + ttAverageInMillis        );
            UT_TRUE( ttAverageInNanos < 5000    );
            UT_TRUE ( ttAverageInMicros ==    0    );
            UT_TRUE ( ttAverageInMillis ==    0    );
        }

        // minimum sleep time measuring
        {
            tt.reset();
            for (int i= 0 ; i< 100 ; i++)
            {
                ALIB.sleepNanos( 1 );
                tt.sample();
            }
            Ticks avg= tt.getAverage();
            Log.info(  "100 probes of 1 ns of sleep leads to average sleep time of " + avg.inNanos() + " ns");
        }

        // sleep two times 20 ms and probe it to an average
        {
            tt.reset();
            ALIB.sleepMillis( 20 );
            tt.sample();


            ALIB.sleepMillis( 80 );

            tt.start();
            ALIB.sleepMillis( 20 );
            tt.sample();

            long    cnt=    tt.getSampleCnt();
            long    avg=    tt.getAverage().inMillis();
            double  hertz=  tt.getAverage().inHertz(1);
            Log.info(  "Ticks sum is " + tt.getCumulated().inMillis() + " after " + cnt + " times 20 ms sleep" );
            Log.info(  "  average is: "    + avg + " ms" );
            Log.info(  "  in Hertz:   "    + hertz );
            UT_TRUE  ( hertz < 53 );
            UT_TRUE  ( hertz > 40 ); // should work even on heavily loaded machines
            UT_TRUE  ( 2 == cnt );
            UT_TRUE  ( avg >= 18 );
            UT_TRUE  ( avg <  45 ); // should work even on heavily loaded machines
        }

        // Ticks Since
        {
            Ticks tt1= new Ticks(); tt1.fromSeconds( 1000 );
            Ticks tt2= new Ticks(); tt2.fromSeconds( 1001 );

            UT_TRUE ( tt2.since( tt1 ).inMillis() == 1000L );
            UT_TRUE ( tt2.since( tt1 ).inMicros() == 1000L * 1000L );
            UT_TRUE ( tt2.since( tt1 ).inNanos()  == 1000L * 1000L * 1000L);
        }
    }


    @SuppressWarnings("static-method")
    @Test
    public void MeasureIncreasingDoublingLoop()
    {
        UT_INIT();
        
        Log.setDomain( "Measure", Scope.METHOD );

        Log.info( "This test shows quite nicely, how the just in time compiler steps in when we are looping heavily!" );

        String testString= "-------------------------------------------------------------------------------------------#";
        AString testAString= new AString( testString );

        TickWatch ttString= new TickWatch();
        TickWatch ttAString= new TickWatch();
        for (int run= 4; run < 20; run++ )
        {
            int qtyLoops= (run == 0)  ? 0 : (1 << (run -1));

            // use String.IndexOf()
            ttString.reset();
                int nonOptimizableUsedResultValue= 0;
                for (int i= 0; i < qtyLoops; i++ )
                    nonOptimizableUsedResultValue+= testString.indexOf( '#' );
            Ticks sSample= ttString.sample();


            // use AString.IndexOf()
            ttAString.reset();
                for (int i= 0; i < qtyLoops; i++ )
                    nonOptimizableUsedResultValue+= testAString.indexOf( '#' );
            Ticks aSample= ttAString.sample();


            if ( nonOptimizableUsedResultValue > -1 ) // this is always true, just for the sake that the compiler does not optimize the whole code!
                Log.info(  Log.buf()._( "Search loops " )        .field()._(       qtyLoops )             .field( 6 )
                                    ._( ":  time needed: " )     .field()._( (int)   sSample.inNanos() )  .field( 8 )
                                    ._(  " / "  )                .field()._( (int) aSample.inNanos() )    .field( 6 )
                                    ._( "   Ratio String/AString: " )    ._( ((double) sSample.raw()) / ((double) aSample.raw()) )
                        );
        }
    }

}
