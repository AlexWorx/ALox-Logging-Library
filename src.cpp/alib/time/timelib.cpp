// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

#include "alib/alib.hpp"

#if !defined (HPP_ALIB_TIME_CALENDARTIME)
    #include "alib/time/calendartime.hpp"
#endif

#if !defined (HPP_ALIB_TIME_TIMESTAMP)
    #include "alib/time/timestamp.hpp"
#endif

#if ALIB_MODULE_STRINGS
    #if !defined (HPP_ALIB_STRINGS_SUBSTRING)
        #include "alib/strings/substring.hpp"
    #endif

    #if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
        #include "alib/strings/numberformat.hpp"
    #endif
#endif

#if !defined (_GLIBCXX_CMATH) && !defined (_CMATH_)
    #include <cmath>
#endif


namespace aworx { namespace lib {

// The singleton of the library class located in namespace aworx::lib.
time::TimeLib TIME;

String   time::TimeLib::months[12];
String   time::TimeLib::days  [ 7];

namespace time {



// #################################################################################################
// glibc specific: library init, InEpochSeconds(), SetFromEpochSeconds()
// #################################################################################################
//! @cond NO_DOX
#if defined( _WIN32 )
namespace {
    int64_t         mscCreationFileTime;
    int64_t         mscFileTimeNowMinusTicksNow;
    double          mscTicksToFileTime;
}
#endif
//! @endcond

void TimeLib::init( Phases phase )
{
    if( phase == Phases::resourceset )
    {
        #if ALIB_MODULE_BOXING
            boxing::DefineInterface<time::Ticks    , false, time::IFormat_TTicks   >();
            boxing::DefineInterface<time::TimeStamp, false, time::IFormat_TimeStamp>();
            ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE(time::TimeStamp)
            ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE(time::TimeSpan )
        #endif

        Res->AddBulk( ResourceCategory.ToCString()
        , "Months", "January,February,March,April,May,June,July,August,September,October,November,December"
        , "Days",   "Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,"

        , "TS_ZERO" , "zero time"
        , "DayP"    , " days"
        , "DayS"    , " day"
        , "HourP"   , " hours"
        , "HourS"   , " hour"
        , "MinP"    , " minutes"
        , "MinS"    , " minute"
        , "SecP"    , " seconds"
        , "SecS"    , " second"
        , "MlSecP"  , " ms"
        , "MlSecS"  , " ms"
        , "McSecP"  , " \xC2\xB5s"
        , "McSecS"  , " \xC2\xB5s"
        , "NSecP"   , " ns"
        , "NSecS"   , " ns"
            ,nullptr );


        #if defined (__GLIBCXX__) || defined(__APPLE__)

            // get the timers resolution. On workstations, the result should be seconds= 0, nanoseconds= 1
            // which means 1 tick per nanosecond
            struct timespec t;
            ALIB_ASSERT_RESULT_EQUALS ( clock_getres(CLOCK_MONOTONIC, &t), 0 );

            // convert the resolution into frequency (measured in 1/s)
            inaccuracy= t.tv_sec * TimeLib::NanosPerSecond   +   t.tv_nsec;

            // create a ticks object that marks the time of creation of ALIB
            creationTime= new Ticks();

        #elif defined( _WIN32 )
            // get system's timer frequency
            LARGE_INTEGER   frequency;
            QueryPerformanceFrequency( &frequency );
            inaccuracy=     TimeLib::NanosPerSecond / frequency.QuadPart;
            ticksPerSecond= frequency.QuadPart << 1;

            mscTicksToFileTime= 10000000.0 / (double)ticksPerSecond;

            // create a ticks object that marks the time of creation of ALib
            creationTime= new Ticks();

            // get creation time as file time
            FILETIME  ftNow;
            GetSystemTimeAsFileTime( &ftNow );

            ULARGE_INTEGER converter;
            converter.HighPart= ftNow.dwHighDateTime;
            converter.LowPart=  ftNow.dwLowDateTime;
            mscCreationFileTime= converter.QuadPart;
        #else
            #pragma message ("Unknown Platform in file: " __FILE__ )
        #endif

        // synchronize monotonic clock with system clock
        SyncClock();
    }

    else if( phase == Phases::final )
    {
        Substring parser;
        parser= Get( "Months" ); for( int i= 0 ; i < 12 ; ++i ) months[i]= parser.ConsumeToken(',');
        parser= Get( "Days"   ); for( int i= 0 ; i <  7 ; ++i )   days[i]= parser.ConsumeToken(',');
    }
}

void TimeLib::terminationCleanUp()
{
    delete creationTime;
}

void TimeLib::SyncClock()
{
    // We are measuring the difference between the clock and the monotonic clock twice and
    // use the smaller result. Longer results indicates that the measurement got interrupted.
    // At the end of the day, the accuracy is not too important here. The impact is only on
    // converting ticks to clock times.
    #if defined (__GLIBCXX__) || defined(__APPLE__)
        struct timespec t;
        ALIB_ASSERT_RESULT_EQUALS ( clock_gettime(CLOCK_REALTIME, &t), 0 );
        TimeLib::TRaw diff1=  ( t.tv_sec * TimeLib::NanosPerSecond  + t.tv_nsec)  - Ticks().Raw();
        ALIB_ASSERT_RESULT_EQUALS ( clock_gettime(CLOCK_REALTIME, &t), 0 );
        TimeLib::TRaw diff2=  ( t.tv_sec * TimeLib::NanosPerSecond  + t.tv_nsec)  - Ticks().Raw();

        diffOfMonotonicClockAndNow= diff1 < diff2 ? diff1 : diff2;
    #elif defined( _WIN32 )
        FILETIME        ftNow;
        ULARGE_INTEGER  converter;

        // 1st measure
        GetSystemTimeAsFileTime( &ftNow );
        converter.HighPart= ftNow.dwHighDateTime;
        converter.LowPart=  ftNow.dwLowDateTime;
        int64_t diff1 = converter.QuadPart -  ( Ticks().Raw() * 10000000 / ticksPerSecond );

        // 2nd measure
        GetSystemTimeAsFileTime( &ftNow );
        converter.HighPart= ftNow.dwHighDateTime;
        converter.LowPart=  ftNow.dwLowDateTime;
        int64_t diff2 = converter.QuadPart -  ( Ticks().Raw() * 10000000 / ticksPerSecond );

        mscFileTimeNowMinusTicksNow= diff1 < diff2 ? diff1 : diff2;
    #endif
}



// #################################################################################################
// system specific: epoch, file time, system time
// #################################################################################################
#if defined (__GLIBCXX__) || defined(__APPLE__)

time_t    TimeStamp::InEpochSeconds ()
const
{
    return    static_cast<time_t>( ( ticks + TIME.diffOfMonotonicClockAndNow  ) / TimeLib::NanosPerSecond );
}

TimeStamp& TimeStamp::SetFromEpochSeconds ( time_t epochSeconds )
{
    ticks=  epochSeconds  * TimeLib::NanosPerSecond - TIME.diffOfMonotonicClockAndNow;
    return *this;
}


#elif defined( _WIN32 )

// InFileTime()
void  TimeStamp::InFileTime( LPFILETIME result )
const
{
    int64_t me=    (int64_t) ( ((double)ticks)  * mscTicksToFileTime );
    ULARGE_INTEGER ftNowX;
    ftNowX.QuadPart= (ULONGLONG) ( me + mscFileTimeNowMinusTicksNow  );


    result->dwLowDateTime=  ftNowX.LowPart;
    result->dwHighDateTime= ftNowX.HighPart;
}

void  TimeStamp::InFileTime( ULARGE_INTEGER& result )
const
{
    FILETIME ft;
    InFileTime( &ft );
    result.HighPart= ft.dwHighDateTime;
    result.LowPart=  ft.dwLowDateTime;
}

//  SetFromFileTime
void TimeStamp::SetFromFileTime( const FILETIME& ft )
{
    ULARGE_INTEGER converter;
    converter.HighPart= ft.dwHighDateTime;
    converter.LowPart=  ft.dwLowDateTime;
    SetFromFileTime( converter );
}

void TimeStamp::SetFromFileTime( const ULARGE_INTEGER& ft )
{
    ticks=  (int64_t) (  ( ((int64_t) ft.QuadPart) - mscFileTimeNowMinusTicksNow) / mscTicksToFileTime  );
}

//  InSystemTime
void  TimeStamp::InSystemTime( LPSYSTEMTIME result, Timezone timezone )
const
{
    FILETIME ft;
    InFileTime( &ft );
    if ( timezone == Timezone::UTC )
        FileTimeToSystemTime( &ft, result );
    else
    {
        SYSTEMTIME utc;
        FileTimeToSystemTime( &ft, &utc );
        SystemTimeToTzSpecificLocalTime( NULL, &utc, result );
    }

}

//  SetFromSystemTime
void TimeStamp::SetFromSystemTime( const SYSTEMTIME& st, Timezone timezone )
{
    FILETIME ft;
    if ( timezone == Timezone::UTC )
        SystemTimeToFileTime( &st, &ft );
    else
    {
        SYSTEMTIME utc;
        TzSpecificLocalTimeToSystemTime( NULL, &st, &utc);
        SystemTimeToFileTime( &utc, &ft );
    }
    SetFromFileTime( ft );
}

#endif



// #################################################################################################
// TimeStamp
// #################################################################################################
AString&  TimeStamp::Format( const String& format,  AString& target )
{
    CalendarTime ct(*this);
    return ct.Format( format, target );
}


#if ALIB_MODULE_BOXING  && !defined(DOX_PARSER)

//! [DOX_ALIB_BOXING_IFORMAT_TIMESTAMP]
void IFormat_TimeStamp::Invoke( const Box& box, const String& formatSpec, AString& target )
{
    CalendarTime tct( (box.Unbox<TimeStamp>()) );
    tct.Format( formatSpec, target );
}
//! [DOX_ALIB_BOXING_IFORMAT_TIMESTAMP]

#endif

// #################################################################################################
// TimeSpan
// #################################################################################################
double TimeSpan::InHertz( int nDigitsPrec ) const
{
    // check
    if ( ticks == 0)
        return 0.0;

    // calc hertz
    double hz;
    #if defined (__GLIBCXX__) || defined(__APPLE__)
        hz= static_cast<double>(TimeLib::NanosPerSecond) /  ticks;
    #elif defined( _WIN32 )
        hz=  ((double) TIME.ticksPerSecond ) / ((double) ticks );
    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif

    // no rounding? that's it
    if ( nDigitsPrec < 0 )
        return hz;

    // round
    double mag= pow( 10, nDigitsPrec );
    return static_cast<int>( hz * mag + ( hz < 0 ? -0.5 : 0.5 ) )
           / mag;
}



// #################################################################################################
// glibc specific: library init, InEpochSeconds(), SetFromEpochSeconds()
// #################################################################################################

#if defined (__GLIBCXX__) || defined(__APPLE__)

time_t    Ticks::InEpochSeconds ()
const
{
    return    static_cast<time_t>( ( ticks + TIME.diffOfMonotonicClockAndNow  ) / TimeLib::NanosPerSecond );
}

void Ticks::SetFromEpochSeconds ( time_t epochSeconds )
{
    ticks=  epochSeconds  * TimeLib::NanosPerSecond - TIME.diffOfMonotonicClockAndNow;
}



// #################################################################################################
// MSC (Windows) specific: library init, InEpochSeconds()/SetFromEpochSeconds()
// #################################################################################################
#elif defined( _WIN32 )

// InFileTime()
void  Ticks::InFileTime( LPFILETIME result )
const
{
    int64_t me=    (int64_t) ( ((double)ticks)  * mscTicksToFileTime );
    ULARGE_INTEGER ftNowX;
    ftNowX.QuadPart= (ULONGLONG) ( me + mscFileTimeNowMinusTicksNow  );


    result->dwLowDateTime=  ftNowX.LowPart;
    result->dwHighDateTime= ftNowX.HighPart;
}

void  Ticks::InFileTime( ULARGE_INTEGER& result )
const
{
    FILETIME ft;
    InFileTime( &ft );
    result.HighPart= ft.dwHighDateTime;
    result.LowPart=  ft.dwLowDateTime;
}

//  SetFromFileTime
void Ticks::SetFromFileTime( const FILETIME& ft )
{
    ULARGE_INTEGER converter;
    converter.HighPart= ft.dwHighDateTime;
    converter.LowPart=  ft.dwLowDateTime;
    SetFromFileTime( converter );
}

void Ticks::SetFromFileTime( const ULARGE_INTEGER& ft )
{
    ticks=  (int64_t) (  ( ((int64_t) ft.QuadPart) - mscFileTimeNowMinusTicksNow) / mscTicksToFileTime  );
}

//  InSystemTime
void  Ticks::InSystemTime( LPSYSTEMTIME result, Timezone timezone )
const
{
    FILETIME ft;
    InFileTime( &ft );
    if ( timezone == Timezone::UTC )
        FileTimeToSystemTime( &ft, result );
    else
    {
        SYSTEMTIME utc;
        FileTimeToSystemTime( &ft, &utc );
        SystemTimeToTzSpecificLocalTime( NULL, &utc, result );
    }

}

//  SetFromSystemTime
void Ticks::SetFromSystemTime( const SYSTEMTIME& st, Timezone timezone )
{
    FILETIME ft;
    if ( timezone == Timezone::UTC )
        SystemTimeToFileTime( &st, &ft );
    else
    {
        SYSTEMTIME utc;
        TzSpecificLocalTimeToSystemTime( NULL, &st, &utc);
        SystemTimeToFileTime( &utc, &ft );
    }
    SetFromFileTime( ft );
}

#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif





}}}// namespace [aworx::lib::time]

#include "alib/strings/numberformat.hpp"
using namespace aworx;
using namespace aworx::lib::time;

integer aworx::lib::strings::T_Apply<TimeSpan>::Apply(AString& target, const TimeSpan pSrc)
{
    TimeSpan src= pSrc;
    if( src == 0 )
    {
        target << aworx::lib::TIME.Get( "TS_ZERO"   );
        return 1;
    }

    if( src < 0 )
    {
        target << "- ";
        src.Set( - src.Raw() );
    }

    NumberFormat nf( NumberFormat::Global );
    nf.FractionalPartWidth= 2;
    integer v= src.InAbsoluteDays();
    if( v >= 10 )
    {
        target << Format( src.InDays(), &nf ) << aworx::lib::TIME.Get( "DayP"   );
        return 1;
    }

    if( v >  0 )
    {
        target << v << ( v != 1 ?  aworx::lib::TIME.Get( "DayP" )
                                :  aworx::lib::TIME.Get( "DayS" ) );

        TimeSpan cpy= src - ( TimeSpan::FromAbsoluteDays(v) );

        target << ' ' << Format( cpy.InHours(), &nf ) << aworx::lib::TIME.Get( "HourP"   );
        return 1;
    }

    v= src.InAbsoluteHours();
    if( v >  0 )
    {
        target << v << ( v != 1 ?  aworx::lib::TIME.Get( "HourP" )
                                :  aworx::lib::TIME.Get( "HourS" ) );

        TimeSpan cpy= src - ( TimeSpan::FromAbsoluteHours(v) );

        auto minutes= cpy.InAbsoluteMinutes();
        target << ' ' << minutes <<  (minutes!= 1 ?  aworx::lib::TIME.Get( "MinP" )
                                                  :  aworx::lib::TIME.Get( "MinS" ) );
        return 1;
    }

    v= src.InAbsoluteMinutes();
    if( v > 0 )
    {
        target << v << ( v != 1 ?  aworx::lib::TIME.Get( "MinP" )
                                :  aworx::lib::TIME.Get( "MinS" ) );

        TimeSpan cpy= src - ( TimeSpan::FromAbsoluteMinutes(v) );

        auto seconds= cpy.InAbsoluteSeconds();
        target << ' ' << seconds <<  (seconds!= 1 ?  aworx::lib::TIME.Get( "SecP" )
                                                  :  aworx::lib::TIME.Get( "SecS" ) );
        return 1;
    }


    v= src.InAbsoluteSeconds();
    if( v > 0 )
    {
        target << Format( src.InSeconds(), &nf ) << aworx::lib::TIME.Get( "SecP"   );
        return 1;
    }

    nf.DecMinimumFieldWidth= 3;

    auto val= src.InAbsoluteMilliseconds();
    if( val >= 1 )
    {
        target << Format(val,&nf) << ( val!= 1  ?  aworx::lib::TIME.Get( "MlSecP" )
                                                :  aworx::lib::TIME.Get( "MlSecS" ) );
        return 1;
    }

    val= src.InAbsoluteMicroseconds();
    if( val >= 1 )
    {
        target << Format(val,&nf) << ( val!= 1  ?  aworx::lib::TIME.Get( "McSecP" )
                                                :  aworx::lib::TIME.Get( "McSecS" ) );
        return 1;
    }

    val= src.InNanoseconds();
    target << Format(val,&nf) << ( val!= 1  ?  aworx::lib::TIME.Get( "NSecP" )
                                            :  aworx::lib::TIME.Get( "NSecS" ) );
    return 1;
}

integer aworx::lib::strings::T_Apply<TimeStamp>::Apply(AString& target, const TimeStamp src)
{
    CalendarTime ct( src );

    target << "TimeStamp( " << ct.Year         << ','
                            << ct.Month        << ','
                            << ct.Day          << ','
                            << ct.Hour         << ','
                            << ct.Minute       << ','
                            << ct.Second       << ','
                            << ct.Millisecond  << ')' ;
    return 1;
}
