// #################################################################################################
//  Unit Tests - aworx::util
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package unittests.com.aworx.util;

import static org.junit.Assert.*;

import java.util.*;

import org.junit.Test;

import com.aworx.util.*;
import com.aworx.lox.*;
import com.aworx.lox.loggers.*;;


public class Test_Ticks
{
    @SuppressWarnings("static-method")
    @Test
    public void Basics()
    {
        Log.reset();

        Log.addLogger( new ConsoleLogger() );
        Log.mapThreadName( "UnitTest" );
        Log.regDomain( "Ticks", Log.Scope.METHOD );

        Log.info( "\n### TicksBasics ###" );

        // check times
        {
            Ticks t= new Ticks();
            t.fromNanos( 42 );    assertEquals( t.inNanos(),             42L);
                                  assertEquals( t.inMicros(),             0L );
                                  assertEquals( t.inMillis(),             0L );
                                  assertEquals( t.inSeconds(),            0L );
            t.fromMicros( 42 );   assertEquals( t.inNanos(),          42000L );
                                  assertEquals( t.inMicros(),            42L );
                                  assertEquals( t.inMillis(),             0L );
                                  assertEquals( t.inSeconds(),            0L );
            t.fromMillis( 42 );   assertEquals( t.inNanos(),       42000000L );
                                  assertEquals( t.inMicros(),         42000L );
                                  assertEquals( t.inMillis(),            42L );
                                  assertEquals( t.inSeconds(),            0L );
            t.fromSeconds( 42 );  assertEquals( t.inNanos(),    42000000000L );
                                  assertEquals( t.inMicros(),      42000000L );
                                  assertEquals( t.inMillis(),         42000L );
                                  assertEquals( t.inSeconds(),           42L );
            Ticks diff= new Ticks();
            diff.fromMillis( 100 );
            t.add( diff );        assertEquals( t.inNanos(),     42100000000L );
                                  assertEquals( t.inMicros(),       42100000L );
                                  assertEquals( t.inMillis(),          42100L );
                                  assertEquals( t.inSeconds(),            42L );
            t.sub( diff );        assertEquals( t.inNanos(),     42000000000L );
                                  assertEquals( t.inMicros(),       42000000L );
                                  assertEquals( t.inMillis(),          42000L );
                                  assertEquals( t.inSeconds(),            42L );

            t.fromMillis( 100 );  assertTrue  ( t.inHertz()  ==   10.0      );
            t.fromMillis( 300 );  assertTrue  ( t.inHertz(0) ==    3.0      );
                                  assertTrue  ( t.inHertz(1) ==    3.3      );
                                  assertTrue  ( t.inHertz(2) ==    3.33     );
                                  assertTrue  ( t.inHertz(5) ==    3.33333  );
        }

        // check internal frequency
        {
            double freq= Ticks.internalFrequency();
            Log.info( "Ticks InternalFrequency:   " + freq );
            assertTrue ( freq >= 1000000.0 );
        }

        // check Ticks creation time
        {
            Ticks creationTimeDiff=  new Ticks();
            creationTimeDiff.sub( Ticks.creationTime() );
            Log.info( "Tick library creation was: " + creationTimeDiff.inNanos  () + "ns ago" );
            Log.info( "Tick library creation was: " + creationTimeDiff.inMicros () + "µs ago" );
            Log.info( "Tick library creation was: " + creationTimeDiff.inMillis () + "ms ago" );
            Log.info( "Tick library creation was: " + creationTimeDiff.inSeconds() + "s ago"  );
            assertTrue ( creationTimeDiff.inNanos  () > 100  ); // It should really take 100 nanoseconds to get here!
            assertTrue ( creationTimeDiff.inSeconds() < 3600 ); // these test will probably not last an hour
        }

        // check if we could sleep for 30ms
        {
            Ticks start= new Ticks();
                AWXU.sleepMillis( 30 );
            Ticks sleepTime= new Ticks();
            sleepTime.sub( start );
            Log.info( "Tick diff after 100ms sleep: " + sleepTime.inMillis() +" ms" );
            assertTrue ( sleepTime.inMillis() > 28 );
            assertTrue ( sleepTime.inMillis() < 150 ); // should work even on heavily loaded machines
        }
    }

    @SuppressWarnings("static-method")
    @Test
    public void SpeedTest()
    {
        Log.reset();

        Log.addLogger( new ConsoleLogger() );
        Log.mapThreadName( "UnitTest" );
        Log.regDomain( "Ticks", Log.Scope.METHOD );

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
            assertTrue ( averageNanos < 500 ); // should work even on heavily loaded machines
        }
    }



    @SuppressWarnings("static-method")
    @Test
    public void DateTimeConversion()
    {
        //Log.RemoveLoggers( );
        //Log.addLogger( new ConsoleLogger() );
        //Log.regDomain( "Ticks", true );

        Ticks ticksNow= new Ticks();

        // roundtrip 1
        long millisEpochNow=    ticksNow.inEpochMillis();
        assertTrue ( Math.abs(millisEpochNow - (new Date()).getTime() ) <= 1);
        Ticks ticksNowFromEpoch= new Ticks();  ticksNowFromEpoch.setFromEpochMillis    ( millisEpochNow );


        // roundtrip 2
        Ticks ticksTodayFromDate=    new Ticks(0L);
        ticksTodayFromDate.setFromEpochMillis( (new Date()).getTime() );
        ticksNow.set();
        assertTrue ( Math.abs( ticksTodayFromDate.inMillis() - ticksNow.inMillis() ) <= 1 );


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

        TicksSpan span= new TicksSpan();
        span.days=        1;
        span.hours=        2;
        span.minutes=    3;
        span.seconds=    4;
        tomorrow.add( span.get() );



        System.out.println( "Java Date conversion:    ");
        System.out.println( "Today: is:         "     +  ( (new Date()).toString() ) );
        System.out.println( "Today: is:         "     +  ( ticksNow.inJavaDate( null ).toString() ) );
        System.out.println( "Today: is:         "     +  (  ( new Date          ( millisEpochNow)             ).toString() ) );
        System.out.println( "Today: is:         "     +  ( ticksNowFromEpoch.inJavaDate( null ).toString() ) );
        System.out.println( "+1d, 2h,3m,4s:     "     +  ( tomorrow.inJavaDate( null ).toString() ) );
        System.out.println( "5.1.70 3:51:00:    "     +  ( ticks5_1_70_3_51.inJavaDate( null ).toString() ) );
        System.out.println( "5.1.71 3:51:00:    "     +  ( ticks5_1_71_3_51.inJavaDate( null ).toString() ) );
        System.out.println( "14.5.69 8:30:00:   "     +  ( ticks_14_05_69_8_30.inJavaDate( null ).toString() ) );

        GregorianCalendar cal= new GregorianCalendar();
        System.out.println( "Java Calendar conversion:    ");
        System.out.println( "Today: is:         "    +  ( ticksNow.inJavaCalendar( null ).getTime().toString() ) );
        cal.setTimeInMillis( millisEpochNow );
        System.out.println( "Today: is:         "    +  (  cal                                              .toString() ) );
        System.out.println( "Today: is:         "    +  ( ticksNowFromEpoch.inJavaCalendar( null ).getTime().toString() ) );
        System.out.println( "+1d, 2h,3m,4s:     "    +  ( tomorrow.inJavaCalendar( null ).getTime().toString() ) );
        System.out.println( "5.1.70 3:51:00:    "    +  ( ticks5_1_70_3_51.inJavaCalendar( null ).getTime().toString() ) );
        System.out.println( "5.1.71 3:51:00:    "    +  ( ticks5_1_71_3_51.inJavaCalendar( null ).getTime().toString() ) );
        System.out.println( "14.5.69 8:30:00:   "    +  ( ticks_14_05_69_8_30.inJavaCalendar( null ).getTime().toString() ) );
    }


    @SuppressWarnings("static-method")
    @Test
    public void Ages()
    {
        Log.reset();

        Log.addLogger( new ConsoleLogger() );
        Log.mapThreadName( "UnitTest" );
        Log.regDomain( "Ticks", Log.Scope.METHOD );

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
            assertTrue( ttAverageInNanos < 5000    );
            assertTrue ( ttAverageInMicros ==    0    );
            assertTrue ( ttAverageInMillis ==    0    );
        }

        // minimum sleep time measuring
        {
            tt.reset();
            for (int i= 0 ; i< 100 ; i++)
            {
                AWXU.sleepNanos( 1 );
                tt.sample();
            }
            Ticks avg= tt.getAverage();
            Log.info(  "100 probes of 1 ns of sleep leads to average sleep time of " + avg.inNanos() + " ns");
        }

        // sleep two times 20 ms and probe it to an average
        {
            tt.reset();
            AWXU.sleepMillis( 20 );
            tt.sample();


            AWXU.sleepMillis( 80 );

            tt.start();
            AWXU.sleepMillis( 20 );
            tt.sample();

            long    cnt=    tt.getSampleCnt();
            long    avg=    tt.getAverage().inMillis();
            double  hertz=  tt.getAverage().inHertz(1);
            Log.info(  "Ticks sum is " + tt.getCumulated().inMillis() + " after " + cnt + " times 20 ms sleep" );
            Log.info(  "  average is: "    + avg + " ms" );
            Log.info(  "  in Hertz:   "    + hertz );
            assertTrue  ( hertz < 53 );
            assertTrue  ( hertz > 40 ); // should work even on heavily loaded machines
            assertTrue  ( 2 == cnt );
            assertTrue  ( avg >= 18 );
            assertTrue  ( avg <  45 ); // should work even on heavily loaded machines
        }

        // Ticks Since
        {
            Ticks tt1= new Ticks(); tt1.fromSeconds( 1000 );
            Ticks tt2= new Ticks(); tt2.fromSeconds( 1001 );

            assertTrue ( tt2.since( tt1 ).inMillis() == 1000L );
            assertTrue ( tt2.since( tt1 ).inMicros() == 1000L * 1000L );
            assertTrue ( tt2.since( tt1 ).inNanos()  == 1000L * 1000L * 1000L);
        }
    }


    @SuppressWarnings("static-method")
    @Test
    public void MeasureIncreasingDoublingLoop()
    {
        Log.reset();

        Log.addLogger( new ConsoleLogger() );
        Log.mapThreadName( "UnitTest" );
        Log.regDomain( "Ticks", Log.Scope.METHOD );

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
                Log.info(  Log.buf().append( "Search loops " )     .field().append(       qtyLoops )                                .field( 6 )
                                    .append( ":  time needed: " ).field().append( (int)   sSample.inNanos() )    .field( 8 )
                                    .append(  " / "  )             .field().append( (int) aSample.inNanos() )    .field( 6 )
                                    .append( "   Ratio String/AString: " )    .append( ((double) sSample.raw()) / ((double) aSample.raw()) )
                        );
        }
    }

}
