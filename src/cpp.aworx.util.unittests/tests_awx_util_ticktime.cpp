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


#define TESTCLASSNAME       CPP_Ticks
#include "awx_unittests.hpp"

using namespace std;
using namespace aworx::util;

namespace tests_aworx_util {


A_TEST_CLASS()

//---------------------------------------------------------------------------------------------------------
//--- Basics
//---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------
//--- MeasureIncreasingDoublingLoop
//---------------------------------------------------------------------------------------------------------

void dateFormatCheck( AWXUnitTesting& ut, TicksCalendarTime& ct,  const char * fmt, const char * expected )
{
    AString32 res;
    ct.Format( fmt, res );
    PRINT( (AString64("TicksCalendarTime.Format: ") << fmt << " ->").Tab(20) << res );
    EXPECT_STREQ( res.Buffer(), expected );
}


A_TEST_METHOD(Basics)

    //Log.RemoveLoggers( );
    //Log.AddLogger( new ConsoleLogger() );
    //Log.RegDomain( "Ticks", true );
    PRINT("") PRINT( "### TicksBasics ###" );

    // check times
    {
        Ticks t;
        int_fast64_t i64;
        int          i;
        t.FromSeconds( 42 );    i64= t.InNanos  (); EXPECT_TRUE( i64 ==   42000000000L );
                                i64= t.InMicros (); EXPECT_TRUE( i64 ==      42000000L );
                                i64= t.InMillis (); EXPECT_TRUE( i64 ==         42000L );
                                i  = t.InSeconds(); EXPECT_TRUE( i   ==            42L );
        t.FromMillis( 42 );     i64= t.InNanos  (); EXPECT_TRUE( i64 ==      42000000L );
                                i64= t.InMicros (); EXPECT_TRUE( i64 ==         42000L );
                                i64= t.InMillis (); EXPECT_TRUE( i64 ==            42L );
                                i  = t.InSeconds(); EXPECT_TRUE( i   ==             0L );
        t.FromMicros( 42 );     i64= t.InNanos  (); EXPECT_TRUE( i64 ==         42000L );
                                i64= t.InMicros (); EXPECT_TRUE( i64 ==            42L );
                                i64= t.InMillis (); EXPECT_TRUE( i64 ==             0L );
                                i  = t.InSeconds(); EXPECT_TRUE( i   ==             0L );
        t.FromNanos( 42 );      i64= t.InNanos  (); EXPECT_TRUE( i64 ==            42L );
                                i64= t.InMicros (); EXPECT_TRUE( i64 ==             0L );
                                i64= t.InMillis (); EXPECT_TRUE( i64 ==             0L );
                                i  = t.InSeconds(); EXPECT_TRUE( i   ==             0L );
        Ticks diff;
        diff.FromMillis( 100 );
        t.FromSeconds( 42 );
        t.Add( diff );          i64= t.InNanos  (); EXPECT_TRUE( i64 ==   42100000000L );
                                i64= t.InMicros (); EXPECT_TRUE( i64 ==      42100000L );
                                i64= t.InMillis (); EXPECT_TRUE( i64 ==         42100L );
                                i  = t.InSeconds(); EXPECT_TRUE( i  ==            42L  );
        t.Sub( diff );          i64= t.InNanos  (); EXPECT_TRUE( i64 ==   42000000000L );
                                i64= t.InMicros (); EXPECT_TRUE( i64 ==      42000000L );
                                i64= t.InMillis (); EXPECT_TRUE( i64 ==         42000L );
                                i  = t.InSeconds(); EXPECT_TRUE( i   ==            42L );

        t.FromMillis( 100 );    EXPECT_EQ( t.InHertz()  ,    10.0    );
        t.FromMillis( 300 );    EXPECT_EQ( t.InHertz(0) ,    3.0     );
                                EXPECT_EQ( t.InHertz(1) ,    3.3     );
                                EXPECT_EQ( t.InHertz(2) ,    3.33    );
                                EXPECT_EQ( t.InHertz(5) ,    3.33333 );
    }

    // check internal frequency
    {
        auto freq= Ticks::InternalFrequency();
        PRINT( "Ticks InternalFrequency:   " << freq );
        EXPECT_TRUE ( freq >= 1000000.0 );
    }

    // check Ticks creation time
    {
        Ticks creationTimeDiff;
        creationTimeDiff.Sub( Ticks::CreationTime() );
        PRINT( "Ticks library creation was: " << creationTimeDiff.InNanos()  <<    "ns ago" );
        PRINT( "Ticks library creation was: " << creationTimeDiff.InMicros() << "\xB5s ago" );
        PRINT( "Ticks library creation was: " << creationTimeDiff.InMillis() <<    "ms ago" );
        PRINT( "Ticks library creation was: " << creationTimeDiff.InSeconds()<<    "s  ago"  );
        EXPECT_TRUE ( creationTimeDiff.InNanos  () > 100  ); // It should really take 100 nanoseconds to get here!
        EXPECT_TRUE ( creationTimeDiff.InSeconds() < 3600 ); // these tests will probably not last an hour
    }

    // check if we could sleep for 100ms
    {
        Ticks start;
            AWXU::SleepMillis( 30 );
        Ticks sleepTime;
        sleepTime.Sub( start );
        PRINT( "Ticks diff after 30ms sleep: " << sleepTime.InMicros() << " \xB5s" );
        EXPECT_TRUE ( sleepTime.InMillis() > 25 );
        EXPECT_TRUE ( sleepTime.InMillis() < 150 ); // should work even on heavily loaded machines
    }
}


//---------------------------------------------------------------------------------------------------------
//--- SpeedTest
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD(SpeedTest)

    //Log.RemoveLoggers( );
    //Log.AddLogger( new ConsoleLogger() );
    //Log.RegDomain( "Ticks", true );
    PRINT(""); PRINT( "### TicksSpeedTest ###" );
    for (int runs= 0; runs < 5; runs ++ )
    {
        int aLotOf= 100;
        PRINT(  "Doing " << aLotOf << " Ticks::Set() calls... " );

        Ticks t;
        Ticks tkMeasure;
        for (int i= 0; i < aLotOf; i++ )
            t.Set();

        auto nanos= tkMeasure.Age().InNanos();
        auto averageNanos= nanos/ aLotOf ;
        PRINT(  "  This took " << nanos << " ns. This is an average of " << averageNanos << " nanoseconds per call" );
        #if defined (WIN32)
            EXPECT_TRUE ( averageNanos < 10000 ); // Windows QueryPerformanceCounter is really slow!
                                                  // Intrinsics should do much better  
        #else
            EXPECT_TRUE ( averageNanos <   500 );
        #endif
    }
}

//---------------------------------------------------------------------------------------------------------
//--- DateTimeConversion
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD(DateTimeConversion)

    //Log.RemoveLoggers( );
    //Log.AddLogger( new ConsoleLogger() );
    //Log.RegDomain( "Ticks", true );

    PRINT("")  PRINT( "### TickSpeedTest ###" );

    #if defined (__GLIBCXX__)

        // check epoc seconds
        {
            Ticks ticksNowOrig;

            // first we get time_t from system and from ticks and compare
            time_t timetNowFromTicks=    ticksNowOrig.InEpochSeconds();
            time_t timetNowFromTime;     time(&timetNowFromTime);
            PRINT( "time_t from Ticks:  " << timetNowFromTicks      << " (seconds after 1/1/1970 GMT)" );
            PRINT( "time_t from system: " << timetNowFromTime       << " -> Diff: " << (timetNowFromTicks - timetNowFromTime) );
            PRINT( "Today from Ticks:   " << ctime( &timetNowFromTicks )  );
            PRINT( "Today from System:  " << ctime( &timetNowFromTime )   );
            EXPECT_TRUE ( abs ( timetNowFromTicks - timetNowFromTime ) <= 1 );

            // now we convert time_t back to ticks
            {
                Ticks ticksNowRoundtrip( 0L );
                ticksNowRoundtrip.SetFromEpochSeconds( timetNowFromTicks );

                PRINT( "Ticks original:  "  << ticksNowOrig        .Raw() );
                PRINT( "Ticks roundtrip: "  << ticksNowRoundtrip   .Raw() );

                EXPECT_EQ ( ticksNowOrig.InSeconds() ,  ticksNowRoundtrip.InSeconds() );
            }

            // now we add a day
            {
                time_t    timetTomorrowTime= timetNowFromTicks + 3600*24 + 2*3600 + 3*60 + 4;
                Ticks    ticksTomorrow( ticksNowOrig );
                TicksSpan span;
                span.Days=       1;
                span.Hours=      2;
                span.Minutes=    3;
                span.Seconds=    4;
                        ticksTomorrow.Add(span.Get());

                time_t  timetTomorrowTicks= ticksTomorrow.InEpochSeconds();
                PRINT( "Tomorrow time_t from Ticks:  " << timetTomorrowTicks               );
                PRINT( "Tomorrow time_t from system: " << timetTomorrowTime                << " Diff: " << (timetTomorrowTicks - timetTomorrowTime) );
                PRINT( "Tomorrow from Ticks:         "    << ctime( &timetTomorrowTicks ) );
                PRINT( "Tomorrow from System:        "    << ctime( &timetTomorrowTime )  );

                EXPECT_EQ ( timetTomorrowTicks ,  timetTomorrowTime );
            }
        }

    #elif defined(_MSC_VER)
        // check epoch seconds
        {
            // get ticks now and system now
            Ticks ticksNow;
            FILETIME        timetNowFromTime;      GetSystemTimeAsFileTime( &timetNowFromTime );

            ULARGE_INTEGER  timetNowFromTicks;     ticksNow.InFileTime( timetNowFromTicks );

            // first we check that they are not too far apart
            ULARGE_INTEGER timeNowFromTimeX;
            timeNowFromTimeX.HighPart= timetNowFromTime.dwHighDateTime;
            timeNowFromTimeX.LowPart=  timetNowFromTime.dwLowDateTime;


            PRINT( "FILETIME from Ticks:  " << timetNowFromTicks.QuadPart   )  ;
            PRINT( "FILETIME from system: " << timeNowFromTimeX.QuadPart     << " -> Diff: " << (timeNowFromTimeX.QuadPart - timetNowFromTicks.QuadPart) );
            EXPECT_TRUE ( abs ( (__int64) (timeNowFromTimeX.QuadPart - timetNowFromTicks.QuadPart ) ) <= 100000L );


            // now, we convert back to ticks
            {
                Ticks nowBack;
                nowBack.SetFromFileTime( timetNowFromTicks );
                auto a= ticksNow.InMicros();
                auto b= nowBack.InMicros();
                PRINT("Back to Ticks. Diff: " << a-b ) 
                EXPECT_TRUE( abs( a - b ) < 10 );
            }


            // now we convert to system time
            {
                SYSTEMTIME st;
                ticksNow.InSystemTime( &st );

                PRINT( "Year/M/D  HH:MM:SS "  << st.wYear << '/' << st.wMonth  << '/' << st.wDay
                                     << "  "  << st.wHour << ':' << st.wMinute << ':' << st.wSecond );
            }


            // Test TimeSpan
            {
                Ticks     ticksTomorrow( ticksNow );
                TicksSpan span;
                span.Days=       1;
                span.Hours=      2;
                span.Minutes=    3;
                span.Seconds=    4;
                ticksTomorrow.Add(span.Get());

                ULARGE_INTEGER timeTomorrow;
                ticksTomorrow.InFileTime( timeTomorrow );


                timeNowFromTimeX.QuadPart+=   937840000000L;//  (3600*24 + 2*3600 + 3*60 + 4) * 10000000L; //* 100 ns

                auto x= timeTomorrow.QuadPart     / 10000000L; // in seconds
                auto y= timeNowFromTimeX.QuadPart / 10000000L;
                EXPECT_NEAR( x, y, 10 ); // This whole thing is not very precise :-/
            }
        }

    #else
        #warning "Warning: Unknown Platform"
    #endif


    // TicksCalendarTime
    {
        Ticks               tNow;
        TicksCalendarTime   cNow( tNow );

        PRINT( "Today local is: " << cNow.Year << '/' <<  cNow.Month  << '/' << cNow.Day << ' '
                                  << cNow.Hour << ':' <<  cNow.Minute << ':' << cNow.Second     );

        Ticks               tNowBack( cNow.Get() );

        auto a= tNow    .InSeconds();
        auto b= tNowBack.InSeconds();
        #if defined(_MSC_VER) // currently, this does not do better than this!
            EXPECT_NEAR( a, b, 1 );
        #else
            EXPECT_EQ( a, b );
        #endif
    }

    // TicksCalendarTime UTC
    {
        Ticks               tNow;
        TicksCalendarTime   cNow( tNow, true );

        PRINT( "Today UTC is:   " << cNow.Year << '/' <<  cNow.Month  << '/' << cNow.Day << ' '
                                  << cNow.Hour << ':' <<  cNow.Minute << ':' << cNow.Second     );

        Ticks               tNowBack( cNow.Get( true ) );

        auto a= tNow    .InSeconds();
        auto b= tNowBack.InSeconds();
        #if defined(_MSC_VER) // currently, this does not do better than this!
            EXPECT_NEAR( a, b, 1 );
        #else
            EXPECT_EQ( a, b );
        #endif

    }
}

//---------------------------------------------------------------------------------------------------------
//--- Ages
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD(Ages)

    //PRINT( "Nanos per 2013 years:    "                << (nanosPerYear*2013) );

    TickWatch tt;

    // minimum time measuring
    {
        tt.Start();
        tt.Sample();
        auto ttAverageInNanos=    tt.GetAverage().InNanos();
        auto ttAverageInMicros=   tt.GetAverage().InMicros();
        auto ttAverageInMillis=   tt.GetAverage().InMillis();
        PRINT( "Ticks minimum measurement nanos:    "    << ttAverageInNanos    );
        PRINT( "Ticks minimum measurement micros:   "    << ttAverageInMicros   );
        PRINT( "Ticks minimum measurement millis:   "    << ttAverageInMillis   );
        EXPECT_TRUE ( ttAverageInNanos  < 10000    );
        EXPECT_TRUE ( ttAverageInMicros < 10    );
        EXPECT_TRUE ( ttAverageInMillis == 0    );
    }
    // minimum sleep time measuring
    {
        tt.Reset();
        for (int i= 0 ; i< 100 ; i++)
        {
            AWXU::SleepNanos( 1 );
            tt.Sample();
        }
        Ticks avg= tt.GetAverage();
        PRINT( "100 probes of 1 ns of sleep leads to average sleep time of " << avg.InNanos() << " ns");
    }

    // sleep two times 20 ms and probe it to an average
    {
        tt.Reset();
            AWXU::SleepMillis( 20 );
        tt.Sample();

                AWXU::SleepMillis( 80 );

        tt.Start();
            AWXU::SleepMillis( 20 );
        tt.Sample();

        auto cum=    tt.GetCumulated().InMillis();
        auto cnt=    tt.GetSampleCnt();
        auto avg=    tt.GetAverage().InMillis();
        auto hertz=  tt.GetAverage().InHertz(1);
        PRINT(  "Tick sum is " << cum << "ms after " << cnt << " times 20 ms sleep" );
        PRINT(  "  average is: "    << avg << " ms" );
        PRINT(  "  in Hertz:   "    << hertz );
        EXPECT_TRUE ( hertz < 53 );
        EXPECT_TRUE ( hertz > 40 ); // should work even on heavily loaded machines
        EXPECT_EQ   ( 2, cnt );
        EXPECT_TRUE ( avg >= 18 );
        EXPECT_TRUE ( avg <  45 ); // should work even on heavily loaded machines
    }

    // Ticks Since
    {
        Ticks tt1;
        Ticks secs;
        secs.FromSeconds( 1000 );
        tt1.Set( secs );
        Ticks tt2;
        secs.FromSeconds( 1001 );
        tt2.Set( secs );

        EXPECT_TRUE ( tt2.Since( tt1 ).InMillis() == 1000L );
        EXPECT_TRUE ( tt2.Since( tt1 ).InMicros() == 1000L * 1000L );
        EXPECT_TRUE ( tt2.Since( tt1 ).InNanos () == 1000L * 1000L * 1000L);
    }
}


//---------------------------------------------------------------------------------------------------------
//--- MeasureIncreasingDoublingLoop
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD(MeasureIncreasingDoublingLoop)

    //Log.RemoveLoggers( );
    //Log.AddLogger( new ConsoleLogger() );
    //Log.RegDomain( "Ticks", true );

    //((ConsoleLogger) Log.GetLogger( "Console" )).EnableVSDebugConsole=
    //((ConsoleLogger) Log.GetLogger( "Console" )).EnableAppConsole=        false;




    string      testString("-------------------------------------------------------------------------------------------#");
    AString     testAString( testString );

    TickWatch   ttString;
    TickWatch   ttAString;
    AString        output;
    for (int run= 4; run < 20; run++ )
    {
        int qtyLoops= (run == 0)  ? 0 : (1 << (run -1));
        int nonOptimizableUsedResultValue= 0;

        // use String.IndexOf()
        ttString.Reset();
            for (int i= 0; i < qtyLoops; i++ )
                nonOptimizableUsedResultValue+= testString.find( '#' );
        Ticks stringSample= ttString.Sample();


        // use AString.IndexOf()
        ttAString.Reset();
            for (int i= 0; i < qtyLoops; i++ )
                nonOptimizableUsedResultValue+= testAString.IndexOf( '#' );
        Ticks aStringSample= ttAString.Sample();


        if ( nonOptimizableUsedResultValue > -1 ) // this is always true, just for the sake that the compiler does not optimize the whole code!
        {
            output.Clear();
            output  .Append( "Search loops " )            .Field().Append( qtyLoops                         ).Field( 6 )
                    .Append( ":  time needed: " )         .Field().Append( (int)  stringSample.InNanos()    ).Field( 8 )
                    .Append(  " / "  )                    .Field().Append( (int) aStringSample.InNanos()    ).Field( 8 )
                    .Append( "   Ratio String/AString: " ).Append( ((double) stringSample.Raw()) / ((double) aStringSample.Raw()) );
            PRINT( output.Buffer() );
        }
    }
}

A_TEST_METHOD(DateFormat)

    TicksCalendarTime ct;
    ct.Year     = 2015;
    ct.Day      =    3;
    ct.Month    =    4;
    ct.Hour     =    5;
    ct.Minute   =    6;
    ct.Second   =    7;
    ct.DayOfWeek=    2;

    AString32 res;
    dateFormatCheck( ut, ct,     "y"        ,        "2015" );
    dateFormatCheck( ut, ct,    "yy"        ,          "15" );
    dateFormatCheck( ut, ct,   "yyy"        ,        "2015" );
    dateFormatCheck( ut, ct,  "yyyy"        ,        "2015" );
    dateFormatCheck( ut, ct, "yyyyy"        ,       "02015" );

    dateFormatCheck( ut, ct,    "M"         ,           "4" );
    dateFormatCheck( ut, ct,   "MM"         ,          "04" );
    dateFormatCheck( ut, ct,  "MMM"         ,         "Apr" );
    dateFormatCheck( ut, ct, "MMMM"         ,        "April" );

    dateFormatCheck( ut, ct, "d"            ,           "3" );
    dateFormatCheck( ut, ct, "dd"           ,          "03" );
    dateFormatCheck( ut, ct, "ddd"          ,         "Tue" );
    dateFormatCheck( ut, ct, "dddd"         ,     "Tuesday" );

    dateFormatCheck( ut, ct, "H"            ,           "5" );
    dateFormatCheck( ut, ct, "HH"           ,          "05" );
    dateFormatCheck( ut, ct, "HHH"          ,         "055" );
    dateFormatCheck( ut, ct, "HHHH"         ,        "0505" );

    dateFormatCheck( ut, ct, "m"            ,           "6" );
    dateFormatCheck( ut, ct, "mm"           ,          "06" );
    dateFormatCheck( ut, ct, "mmm"          ,         "066" );
    dateFormatCheck( ut, ct, "mmmm"         ,        "0606" );

    dateFormatCheck( ut, ct, "s"            ,           "7" );
    dateFormatCheck( ut, ct, "ss"           ,          "07" );
    dateFormatCheck( ut, ct, "sss"          ,         "077" );
    dateFormatCheck( ut, ct, "ssss"         ,        "0707" );

    dateFormatCheck( ut, ct, "'"            ,           "" );
    dateFormatCheck( ut, ct, "'msH"         ,        "msH" );
    dateFormatCheck( ut, ct, "''"           ,          "'" );
    dateFormatCheck( ut, ct, "''''"         ,         "''" );
    dateFormatCheck( ut, ct, "''m''"        ,        "'6'" );
    dateFormatCheck( ut, ct, "'''m'''"        ,      "'m'" );
    dateFormatCheck( ut, ct, "s'msH's"      ,     "7msH7" );
    dateFormatCheck( ut, ct, "'someone''''s quote'",  "someone's quote" );

    dateFormatCheck( ut, ct, "yyyy-MM-dd HH:mm:ss",  "2015-04-03 05:06:07" );
}


A_TEST_CLASS_END

}; //namespace
