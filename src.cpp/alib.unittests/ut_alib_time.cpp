// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"

#include "alib/compatibility/std_string.hpp"

#if !defined (HPP_ALIB_TIME_TICKSPAN)
    #include "alib/time/tickspan.hpp"
#endif
#if !defined (HPP_ALIB_TIME_TICKWATCH)
    #include "alib/time/tickwatch.hpp"
#endif

#define TESTCLASSNAME       CPP_ALib_Time
#include "aworx_unittests.hpp"

using namespace std;
using namespace aworx;

namespace ut_aworx {


UT_CLASS()

//--------------------------------------------------------------------------------------------------
//--- Basics
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//--- MeasureIncreasingDoublingLoop
//--------------------------------------------------------------------------------------------------

void dateFormatCheck( AWorxUnitTesting& ut, TicksCalendarTime& ct,  const char * fmt, const char * expected )
{
    String32 res;
    ct.Format( fmt, res );
    UT_PRINT( (String128("TicksCalendarTime.Format: ") << fmt << " ->")._(Format::Tab(20)) << res );
    UT_EQ( expected, res );
}


UT_METHOD(Basics)
{
    UT_INIT();

    UT_PRINT("") UT_PRINT( "### TicksBasics ###" );

    // check times
    {
        Ticks t;
        int64_t i64;
        int          i;
        t.FromSeconds( 42 );       i64= t.InNanos  (); UT_NEAR( 42000000000LL, i64,  500LL );
                                   i64= t.InMicros (); UT_EQ(    42000000LL, i64 );
                                   i64= t.InMillis (); UT_EQ(       42000LL, i64 );
                                   i  = t.InSeconds(); UT_EQ(          42LL, i   );
        t.FromMillis( 42 );        i64= t.InNanos  (); UT_NEAR(  42000000LL, i64, 500LL );
                                   i64= t.InMicros (); UT_EQ( 42000LL, i64 );
                                   i64= t.InMillis (); UT_EQ(    42LL, i64 );
                                   i  = t.InSeconds(); UT_EQ(     0LL, i   );
        t.FromMicros( 42 );        i64= t.InNanos  (); UT_NEAR(  42000LL, i64, 500LL );
                                   i64= t.InMicros (); UT_EQ(    42LL, i64 );
                                   i64= t.InMillis (); UT_EQ(     0LL, i64 );
                                   i  = t.InSeconds(); UT_EQ(     0LL, i   );
        t.FromNanos( 42 );         i64= t.InNanos  (); UT_NEAR(  42LL, i64, 500LL );
                                   i64= t.InMicros (); UT_EQ(     0LL, i64 );
                                   i64= t.InMillis (); UT_EQ(     0LL, i64 );
                                   i  = t.InSeconds(); UT_EQ(     0LL, i   );
        t.FromNanos( 123456789 );  i64= t.InNanos  (); UT_NEAR(  123456789LL, i64, 500LL );
                                   i64= t.InMicros (); UT_EQ( 123456LL, i64 );
                                   i64= t.InMillis (); UT_EQ( 123LL, i64 );
                                   i  = t.InSeconds(); UT_EQ( 0LL, i   );


        Ticks diff;
        diff.FromMillis( 100 );
        t.FromSeconds( 42 );
        t.Add( diff );          i64= t.InNanos  (); UT_NEAR(  42100000000LL, i64,  500LL );
                                i64= t.InMicros (); UT_EQ(    42100000LL, i64 );
                                i64= t.InMillis (); UT_EQ(       42100LL, i64 );
                                i  = t.InSeconds(); UT_EQ(          42LL, i   );
        t.Sub( diff );          i64= t.InNanos  (); UT_NEAR(  42000000000LL, i64,  500LL );
                                i64= t.InMicros (); UT_EQ(    42000000LL, i64 );
                                i64= t.InMillis (); UT_EQ(       42000LL, i64 );
                                i  = t.InSeconds(); UT_EQ(          42LL, i   );

        t.FromMillis( 100 );    UT_NEAR( t.InHertz()  ,    10.0  ,0.0001  );
        t.FromMillis( 300 );    UT_EQ( t.InHertz(0) ,    3.0     );
                                UT_EQ( t.InHertz(1) ,    3.3     );
                                UT_EQ( t.InHertz(2) ,    3.33    );
                                UT_EQ( t.InHertz(5) ,    3.33333 );
    }

    // check internal frequency
    {
        auto inaccuracy= Ticks::Inaccuracy();
        UT_PRINT( "Ticks Inaccuracy: {} ns", inaccuracy );
        UT_FALSE ( inaccuracy > 1000 ); // on macOS 10.12 (Sierra), 1000 was observed
    }

    // check Ticks creation time
    {
        Ticks creationTimeDiff;
        creationTimeDiff.Sub( Ticks::CreationTime() );
        UT_PRINT( "Ticks library creation was: {} ns ago"        , creationTimeDiff.InNanos()  );
        UT_PRINT( "Ticks library creation was: {} \xC2\xB5s ago" , creationTimeDiff.InMicros() ); // UTF-8 encoding of the greek 'm' letter;
        UT_PRINT( "Ticks library creation was: {} ms ago"        , creationTimeDiff.InMillis() );
        UT_PRINT( "Ticks library creation was: {} s  ago"        , creationTimeDiff.InSeconds());
        UT_TRUE ( creationTimeDiff.InNanos  () > 100  ); // It should really take 100 nanoseconds to get here!
        UT_TRUE ( creationTimeDiff.InSeconds() < 3600 ); // these tests will probably not last an hour
    }

    // check if we could sleep for 100ms
    {
        Ticks start;
            ALIB::SleepMillis( 30 );
        Ticks sleepTime;
        sleepTime.Sub( start );
        UT_PRINT( "Ticks diff after 30ms sleep: {}\xC2\xB5s ago", sleepTime.InMicros() ); // UTF-8 encoding of the greek 'm' letter;
        UT_TRUE ( sleepTime.InMillis() > 25 );
        UT_TRUE ( sleepTime.InMillis() < 150 ); // should work even on heavily loaded machines
    }
}


//--------------------------------------------------------------------------------------------------
//--- SpeedTest
//--------------------------------------------------------------------------------------------------
UT_METHOD(SpeedTest)
{
    UT_INIT();

    UT_PRINT(""); UT_PRINT( "### TicksSpeedTest ###" );
    for (int runs= 0; runs < 5; runs ++ )
    {
        int aLotOf= 100;
        UT_PRINT(  "Doing {} Ticks::Set() calls... ", aLotOf );

        Ticks t;
        Ticks tkMeasure;
        for (int i= 0; i < aLotOf; i++ )
            t.Set();

        auto nanos= tkMeasure.Age().InNanos();
        auto averageNanos= nanos/ aLotOf ;
        UT_PRINT(  "  This took {} ns. This is an average of {} nanoseconds per call", nanos, averageNanos );
        #if defined (_WIN32) || ALIB_AVOID_ANALYZER_WARNINGS
            UT_TRUE ( averageNanos < 10000 ); // Windows QueryPerformanceCounter is really slow!
                                                  // Intrinsics should do much better
        #else
            UT_TRUE ( averageNanos <   500 );
        #endif
    }
}

//--------------------------------------------------------------------------------------------------
//--- DateTimeConversion
//--------------------------------------------------------------------------------------------------
UT_METHOD(DateTimeConversion)
{
    UT_INIT();
    UT_PRINT("")  UT_PRINT( "### TickSpeedTest ###" );

    #if defined (__GLIBCXX__) || defined(__APPLE__)

        // check epoc seconds
        {
            Ticks ticksNowOrig;

            // first we get time_t from system and from ticks and compare
            time_t timetNowFromTicks=    ticksNowOrig.InEpochSeconds();
            time_t timetNowFromSystem;     std::time(&timetNowFromSystem);
            UT_PRINT( "time_t from Ticks:  {} (seconds after 1/1/1970 GMT)", timetNowFromTicks );
            UT_PRINT( "time_t from system: {} -> Diff: {}", timetNowFromSystem, (timetNowFromTicks - timetNowFromSystem) );
            UT_PRINT( "Today from Ticks:   ", ctime( &timetNowFromTicks )  );
            UT_PRINT( "Today from System:  ", ctime( &timetNowFromSystem )   );
            UT_TRUE ( abs ( timetNowFromTicks - timetNowFromSystem ) <= 1 );

            // now we convert time_t back to ticks
            {
                Ticks ticksNowRoundtrip( 0L );
                ticksNowRoundtrip.SetFromEpochSeconds( timetNowFromTicks );

                UT_PRINT( "Ticks original:  ", ticksNowOrig     .Raw() );
                UT_PRINT( "Ticks roundtrip: ", ticksNowRoundtrip.Raw() );

                #if ALIB_AVOID_ANALYZER_WARNINGS
                    UT_EQ( ticksNowOrig.InSeconds() ,  ticksNowRoundtrip.InSeconds() );
                #endif
            }

            // now we add a day
            {
                time_t   timetTomorrowTime= timetNowFromTicks + 3600*24 + 2*3600 + 3*60 + 4;
                Ticks    ticksTomorrow( ticksNowOrig );
                TickSpan span;
                span.Days=       1;
                span.Hours=      2;
                span.Minutes=    3;
                span.Seconds=    4;
                ticksTomorrow.Add(span.Get());

                time_t  timetTomorrowTicks= ticksTomorrow.InEpochSeconds();
                UT_PRINT( "Tomorrow time_t from Ticks:  ", timetTomorrowTicks           );
                UT_PRINT( "Tomorrow time_t from system: {}  Diff: {}", timetTomorrowTime, (timetTomorrowTicks - timetTomorrowTime) );
                UT_PRINT( "Tomorrow from Ticks:         ", ctime( &timetTomorrowTicks ) );
                UT_PRINT( "Tomorrow from System:        ", ctime( &timetTomorrowTime )  );

                UT_EQ( timetTomorrowTicks ,  timetTomorrowTime );
            }
        }

    #elif defined(_WIN32)
        // check epoch seconds
        {
            // get ticks now and system now
            Ticks ticksNow;
            FILETIME        timetNowFromSystem;      GetSystemTimeAsFileTime( &timetNowFromSystem );

            ULARGE_INTEGER  timetNowFromTicks;     ticksNow.InFileTime( timetNowFromTicks );

            // first we check that they are not too far apart
            ULARGE_INTEGER timetNowFromSystemUL;
            timetNowFromSystemUL.HighPart= timetNowFromSystem.dwHighDateTime;
            timetNowFromSystemUL.LowPart=  timetNowFromSystem.dwLowDateTime;
            int64_t diff= timetNowFromSystemUL.QuadPart >= timetNowFromTicks.QuadPart ? (int64_t) timetNowFromSystemUL.QuadPart - timetNowFromTicks.QuadPart
                                                                                      : (int64_t) timetNowFromTicks.QuadPart - timetNowFromSystemUL.QuadPart;


            UT_PRINT( "FILETIME from Ticks:  ", timetNowFromTicks.QuadPart   );
            UT_PRINT( "FILETIME from system: {} -> Diff: {}", timetNowFromSystemUL.QuadPart, diff );
            UT_TRUE ( diff <= 100000L );


            // now, we convert back to ticks
            {
                Ticks nowBack;
                nowBack.SetFromFileTime( timetNowFromTicks );
                auto a= ticksNow.InMicros();
                auto b= nowBack.InMicros();
                UT_PRINT("Back to Ticks. Diff: ", a-b )
                UT_TRUE( abs( a - b ) < 10 );
            }


            // now we convert to system time
            {
                SYSTEMTIME st;
                ticksNow.InSystemTime( &st );

                UT_PRINT( "Year/M/D  HH:MM:SS {}/{}/{}  {}:{}:{}",
                          st.wYear,st.wMonth,st.wDay, st.wHour,st.wMinute,st.wSecond );
            }


            // Test TimeSpan
            {
                Ticks     ticksTomorrow( ticksNow );
                TickSpan  span;
                span.Days=       1;
                span.Hours=      2;
                span.Minutes=    3;
                span.Seconds=    4;
                ticksTomorrow.Add(span.Get());
                ULARGE_INTEGER timeTomorrowFromTicks;
                ticksTomorrow.InFileTime( timeTomorrowFromTicks );


                timetNowFromSystemUL.QuadPart+=  static_cast<int64_t>( (24 + 2) * 3600   +   3 * 60   + 4) * 10000000L;

                auto x= timeTomorrowFromTicks.QuadPart ;
                auto y= timetNowFromSystemUL.QuadPart  ;
                UT_NEAR( (int64_t) x, (int64_t) y, (int64_t) 100000 );
            }
        }

    #else
        #pragma message ( "Warning: Warning: Unknown Platform" )
    #endif


    // TicksCalendarTime
    {
        Ticks               tNow;

        // cut fractional part (below seconds). Otherwise a rounding error might occur
        #if defined (__GLIBCXX__) || defined(__APPLE__)
            tNow.SetFromEpochSeconds( tNow.InEpochSeconds() );
        #elif defined( _WIN32 )
            SYSTEMTIME st;
            tNow.InSystemTime     ( &st, Timezone::Local );
            tNow.SetFromSystemTime(  st, Timezone::Local );
        #endif
        TicksCalendarTime   cNow( tNow );

        UT_PRINT( "Today local is: {}/{}/{} {}:{}:{}", cNow.Year, cNow.Month, cNow.Day,
                                                       cNow.Hour, cNow.Minute, cNow.Second     );

        Ticks               tNowBack( cNow.Get() );

        auto a= tNow    .InSeconds();
        auto b= tNowBack.InSeconds();
        #if defined(_WIN32) // currently, this does not do better than this!
            UT_NEAR( a, b, 1 );
        #else
            UT_EQ( a, b );
        #endif
    }

    // TicksCalendarTime UTC
    {
        Ticks               tNow;
        // cut fractional part (below seconds). Otherwise a rounding error might occur
        #if defined (__GLIBCXX__) || defined(__APPLE__)
            tNow.SetFromEpochSeconds( tNow.InEpochSeconds() );
        #elif defined( _WIN32 )
            SYSTEMTIME st;
            tNow.InSystemTime     ( &st, Timezone::Local );
            tNow.SetFromSystemTime(  st, Timezone::Local );
        #endif
        TicksCalendarTime   cNow( tNow, Timezone::UTC );

        UT_PRINT( "Today UTC is:  {}/{}/{} {}:{}:{}", cNow.Year, cNow.Month, cNow.Day,
                                                      cNow.Hour, cNow.Minute, cNow.Second     );

        Ticks               tNowBack( cNow.Get( Timezone::UTC ) );

        auto a= tNow    .InSeconds();
        auto b= tNowBack.InSeconds();
        #if defined(_WIN32) // currently, this does not do better than this!
            UT_NEAR( a, b, 1 );
        #else
            UT_EQ( a, b );
        #endif
    }
}

//--------------------------------------------------------------------------------------------------
//--- Ages
//--------------------------------------------------------------------------------------------------
UT_METHOD(Ages)
{
    UT_INIT();
    //UT_PRINT( "Nanos per 2013 years:    "                << (nanosPerYear*2013) );

    TickWatch tt;

    // minimum time measuring
    {
        tt.Start();
        tt.Sample();
        auto ttAverageInNanos=    tt.GetAverage().InNanos();
        auto ttAverageInMicros=   tt.GetAverage().InMicros();
        auto ttAverageInMillis=   tt.GetAverage().InMillis();
        UT_PRINT( "Ticks minimum measurement nanos:    ", ttAverageInNanos    );
        UT_PRINT( "Ticks minimum measurement micros:   ", ttAverageInMicros   );
        UT_PRINT( "Ticks minimum measurement millis:   ", ttAverageInMillis   );

        #if !ALIB_AVOID_ANALYZER_WARNINGS
        UT_TRUE ( ttAverageInNanos  < 10000    );
        UT_TRUE ( ttAverageInMicros < 10    );
        UT_TRUE ( ttAverageInMillis == 0    );
        #endif
    }
    // minimum sleep time measuring
    {
        tt.Reset();
        for (int i= 0 ; i< 100 ; i++)
        {
            ALIB::SleepNanos( 1 );
            tt.Sample();
        }
        Ticks avg= tt.GetAverage();
        UT_PRINT( "100 probes of 1 ns of sleep leads to average sleep time of {} ns", avg.InNanos());
    }

    // sleep two times 20 ms and probe it to an average
    {
        tt.Reset();
            ALIB::SleepMillis( 20 );
        tt.Sample();

                ALIB::SleepMillis( 80 );

        tt.Start();
            ALIB::SleepMillis( 20 );
        tt.Sample();

        auto cum=    tt.GetCumulated().InMillis();
        auto cnt=    tt.GetSampleCnt();
        auto avg=    tt.GetAverage().InMillis();
        auto hertz=  tt.GetAverage().InHertz(1);
        UT_PRINT(  "Tick sum is {}ms after {} times 20 ms sleep", cum, cnt );
        UT_PRINT(  "  average is: {} ms", avg  );
        UT_PRINT(  "  in Hertz  : {}", hertz );
        UT_TRUE ( hertz < 53 );
        UT_TRUE ( hertz > 40 ); // should work even on heavily loaded machines
        UT_EQ( 2, cnt );
        UT_TRUE ( avg >= 18 );
        UT_TRUE ( avg <  45 ); // should work even on heavily loaded machines
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

        UT_TRUE ( tt2.Since( tt1 ).InMillis() == 1000L );
        UT_TRUE ( tt2.Since( tt1 ).InMicros() == 1000L * 1000L );
        UT_TRUE ( tt2.Since( tt1 ).InNanos () == 1000L * 1000L * 1000L);
    }
}


//--------------------------------------------------------------------------------------------------
//--- MeasureIncreasingDoublingLoop
//--------------------------------------------------------------------------------------------------
UT_METHOD(MeasureIncreasingDoublingLoop)
{
    UT_INIT();

    string      testString("-------------------------------------------------------------------------------------------#");
    AString     testAString( testString );

    TickWatch   ttString;
    TickWatch   ttAString;
    AString        output;
    for (int run= 4; run < 20; run++ )
    {
        int qtyLoops= (run == 0)  ? 0 : (1 << (run -1));
        integer nonOptimizableUsedResultValue= 0;

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
            output  ._( "Search loops " )            ._( Format::Field( String32( qtyLoops                  ), 6 ) )
                    ._( ":  time needed: " )         ._( Format::Field( String32( stringSample.InNanos()    ), 8 ) )
                    ._( " / "  )                     ._( Format::Field( String32( aStringSample.InNanos()   ), 8 ) )
                    ._( "   Ratio String/AString: " )._( static_cast<double>(stringSample.Raw()) / static_cast<double>(aStringSample.Raw()) );

            UT_PRINT( output );
        }
    }
}

UT_METHOD(DateFormat)
{
    UT_INIT();

    TicksCalendarTime ct;
    ct.Year     = 2015;
    ct.Day      =    3;
    ct.Month    =    4;
    ct.Hour     =    5;
    ct.Minute   =    6;
    ct.Second   =    7;
    ct.DayOfWeek=    2;

    String32 res;
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
    dateFormatCheck( ut, ct, "HHH"          ,         "005" );
    dateFormatCheck( ut, ct, "HHHH"         ,        "0005" );

    dateFormatCheck( ut, ct, "m"            ,           "6" );
    dateFormatCheck( ut, ct, "mm"           ,          "06" );
    dateFormatCheck( ut, ct, "mmm"          ,         "006" );
    dateFormatCheck( ut, ct, "mmmm"         ,        "0006" );

    dateFormatCheck( ut, ct, "s"            ,           "7" );
    dateFormatCheck( ut, ct, "ss"           ,          "07" );
    dateFormatCheck( ut, ct, "sss"          ,         "007" );
    dateFormatCheck( ut, ct, "ssss"         ,        "0007" );

    //error: dateFormatCheck( ut, ct, "'"            ,           "" );
    //error: dateFormatCheck( ut, ct, "'msH"         ,        "msH" );
    dateFormatCheck( ut, ct, "''"           ,          "'" );
    dateFormatCheck( ut, ct, "''''"         ,         "''" );
    dateFormatCheck( ut, ct, "''m''"        ,        "'6'" );
    dateFormatCheck( ut, ct, "'''m'''"        ,      "'m'" );
    dateFormatCheck( ut, ct, "s'msH's"      ,     "7msH7" );
    dateFormatCheck( ut, ct, "'someone''''s quote'",  "someone's quote" );

    dateFormatCheck( ut, ct, "yyyy-MM-dd HH:mm:ss",  "2015-04-03 05:06:07" );
}


UT_CLASS_END

}; //namespace
