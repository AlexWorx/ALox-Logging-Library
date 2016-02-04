// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#include "alib/stdafx_alib.h"
#include "alib/strings/assubstring.hpp"

#if !defined (HPP_AWORX_LIB_TIME)
    #include "alib/time/ticks.hpp"
#endif

#if !defined (_GLIBCXX_CMATH) && !defined (_CMATH_)
    #include <cmath>
#endif

// For code compatibility with ALox Java/C++
#define _NC _<false>


using namespace std;
using namespace aworx::lib::strings;
using namespace aworx::lib::enums;

namespace aworx {
namespace           lib {
namespace                   time {

// #################################################################################################
// Ticks
// #################################################################################################

// #################################################################################################
// glibc specific: library init, InEpochSeconds(), SetFromEpochSeconds()
// #################################################################################################
//
// static members
int_fast64_t    Ticks::frequency;
Ticks*          Ticks::creationTime;

#if defined (__GLIBCXX__)
    // static library initialization code ( invoked by ALIB::Init() )
    void Ticks::_Init_ALib()
    {
        // get the timers resolution. On workstations, the result should be secs= 0, nanosecs= 1
        // which means 1 tick per nanosec
        struct timespec t;
        ALIB_ASSERT_RESULT_EQUALS ( clock_getres(CLOCK_MONOTONIC, &t), 0 );

        // convert the resolution into frequency (measured in 1/s)
        Ticks::frequency= ( (double) ALIB_NANOS_PER_SECOND ) / ( t.tv_sec * ALIB_NANOS_PER_SECOND + t.tv_nsec );

        // create a ticks object that marks the time of creation of ALIB
        creationTime= new Ticks();
    }

    // static library destruction code ( invoked by ALIB::TerminationCleanUp() )
    void Ticks::_Terminate_ALib()
    {
        delete Ticks::creationTime;
    }


    // InEpochSeconds
    time_t    Ticks::InEpochSeconds ()
    const
    {
        // get Ticks clocks now in ticks
        Ticks now;

        // get real clock now in ticks
        struct timespec t;
        ALIB_ASSERT_RESULT_EQUALS ( clock_gettime(CLOCK_REALTIME, &t), 0 );
        int_fast64_t nowReal=   ( t.tv_sec * ALIB_NANOS_PER_SECOND  ) + t.tv_nsec ;

        return    ( ticks + (nowReal - now.ticks)  ) / ALIB_NANOS_PER_SECOND;
    }

    //  SetFromEpochSeconds
    void Ticks::SetFromEpochSeconds ( time_t epochSeconds )
    {
        // get Ticks clocks now in ticks
        Ticks now;

        // get real clock now in ticks
        struct timespec t;
        ALIB_ASSERT_RESULT_EQUALS ( clock_gettime(CLOCK_REALTIME, &t), 0 );
        int_fast64_t nowReal=    t.tv_sec;

        ticks= ( epochSeconds - (nowReal  - now.InSeconds())  ) * ALIB_NANOS_PER_SECOND;
    }


// #################################################################################################
// MSC (Windows) specific: library init, InEpochSeconds()/SetFromEpochSeconds()
// #################################################################################################
#elif defined( _WIN32 )

    // static members
    int_fast64_t    Ticks::mscResFactor;
    double          Ticks::mscTicksPerDay;
    double          Ticks::mscTicksPerHour;
    double          Ticks::mscTicksPerMinute;
    double          Ticks::mscTicksPerSecond;
    double          Ticks::mscTicksPerMillisecond;
    double          Ticks::mscTicksPerMicrosecond;
    double          Ticks::mscTicksPerNanosecond;
    double          Ticks::mscTicksPerFileTimeTick;


    ULARGE_INTEGER  mscCreationFileTime;
    double          mscFileTimeNowMinusTicksNow;
    int_fast64_t    mscCreationTimeInMicros;

    // static library initialization code ( invoked by ALIB::Init() )
    void Ticks::_Init_ALib()
    {
        // get system's timer frequency
        LARGE_INTEGER   frequency;
        QueryPerformanceFrequency( &frequency );
        Ticks::frequency= frequency.QuadPart;

        // calculate the factor that we need to apply to system ticks, to get into
        // the magnitude of 1 digit nanoseconds per tick
        int_fast64_t fr=  Ticks::frequency;
        Ticks::mscResFactor=     1;
        while ( fr < ALIB_NANOS_PER_SECOND  ) //10 * (1sec in nanos)
        {
            fr*= 10;
            Ticks::mscResFactor*= 10;
        }

        // calculate various conversion factors
        double ticksPerSec=  (double) (Ticks::frequency * Ticks::mscResFactor);
        Ticks::mscTicksPerSecond=       ticksPerSec;
        Ticks::mscTicksPerMinute=       ticksPerSec *  60.0;
        Ticks::mscTicksPerHour=         ticksPerSec * (60.0 * 60.0);
        Ticks::mscTicksPerDay=          ticksPerSec * (60.0 * 60.0 * 24.0 );
        Ticks::mscTicksPerMillisecond=  ticksPerSec /        1000.0;
        Ticks::mscTicksPerMicrosecond=  ticksPerSec /     1000000.0;
        Ticks::mscTicksPerNanosecond=   ticksPerSec /  1000000000.0;
        Ticks::mscTicksPerFileTimeTick= ticksPerSec /    10000000.0;

        // create a ticks object that marks the time of creation of ALib
        creationTime= new Ticks();

        // get file time clock
        FILETIME  ftNow;
        GetSystemTimeAsFileTime( &ftNow );

        // calculate the difference between the two. This is what we will use to convert
        // (Hopefully, we have not been interrupted between the two calls above! The
        // effect would be, that converting between ticks to filetime we have gap as huge
        // as the interruption was (plus some floating point precision loss...) )
        mscCreationFileTime.HighPart= ftNow.dwHighDateTime;
        mscCreationFileTime.LowPart=  ftNow.dwLowDateTime;

        double ftNowD= (double) mscCreationFileTime.QuadPart;
        double tNowD=  creationTime->ticks / mscTicksPerFileTimeTick;
        mscFileTimeNowMinusTicksNow= ftNowD - tNowD;

        // also needed for conversion:
        mscCreationTimeInMicros= creationTime->InMicros();
    }

    // static library destruction code ( invoked by ALIB::TerminationCleanUp() )
    void Ticks::_Terminate_ALib()
    {
        delete Ticks::creationTime;
    }


    // InFileTime()
    void  Ticks::InFileTime( LPFILETIME result )
    const
    {
        double me=     ticks      / mscTicksPerFileTimeTick;
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
    void Ticks::SetFromFileTime( const LPFILETIME ft )
    {
        ULARGE_INTEGER ftX;
        ftX.HighPart= ft->dwHighDateTime;
        ftX.LowPart=  ft->dwLowDateTime;

        FromMicros(  ( ftX.QuadPart  / 10 )   - ( mscCreationFileTime.QuadPart / 10  - mscCreationTimeInMicros  ) );
    }

    void Ticks::SetFromFileTime( const ULARGE_INTEGER& ft )
    {
        FILETIME ftft;
        ftft.dwHighDateTime=  ft.HighPart;
        ftft.dwLowDateTime=   ft.LowPart;
        SetFromFileTime( &ftft );
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
        SetFromFileTime( &ft );
    }


#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif


// #################################################################################################
// platform independent methods
// #################################################################################################

// InternalFrequency()
int_fast64_t Ticks::InternalFrequency()
{
    return frequency;
}


const Ticks& Ticks::CreationTime()
{
    return *creationTime;
}

double Ticks::InHertz( int nDigitsPrec ) const
{
    // check
    if ( ticks == 0)
        return 0.0;

    // calc hertz
    double hz;
    #if defined (__GLIBCXX__)
        hz= ((double) ALIB_NANOS_PER_SECOND) / ticks;
    #elif defined( _WIN32 )
        hz=  Ticks::mscTicksPerSecond / ((double) ticks );
    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif

    // no rounding? that's it
    if ( nDigitsPrec < 0 )
        return hz;

    // round
    double mag= pow( 10, nDigitsPrec );
    return ( (int) ( hz * mag + ( hz < 0 ? -0.5 : 0.5 )) ) / mag;
}

AString&  Ticks::Format( const String& format,  AString& target )
{
    TicksCalendarTime ct(*this);
    return ct.Format( format, target );
}


// #################################################################################################
// TickSpan
// #################################################################################################

void TickSpan::Clear()
{
    Days=
    Hours=
    Minutes=
    Seconds=
    Milliseconds=
    Microseconds=
    Nanoseconds=    0;
}

void TickSpan::Set( int_fast64_t ticks )
{
    Clear();

    #if defined( _WIN32 )
        Ticks toNanos( ticks );
        ticks= toNanos.InNanos();
    #endif

    int_fast64_t fract=    0;
    if ( ticks > ALIB_NANOS_PER_DAY )            {    fract= ticks / ALIB_NANOS_PER_DAY;            Days=           (int) fract;        ticks-= fract * ALIB_NANOS_PER_DAY;           }
    if ( ticks > ALIB_NANOS_PER_HOUR )           {    fract= ticks / ALIB_NANOS_PER_HOUR;           Hours=          (int) fract;        ticks-= fract * ALIB_NANOS_PER_HOUR;          }
    if ( ticks > ALIB_NANOS_PER_MINUTE )         {    fract= ticks / ALIB_NANOS_PER_MINUTE;         Minutes=        (int) fract;        ticks-= fract * ALIB_NANOS_PER_MINUTE;        }
    if ( ticks > ALIB_NANOS_PER_SECOND )         {    fract= ticks / ALIB_NANOS_PER_SECOND;         Seconds=        (int) fract;        ticks-= fract * ALIB_NANOS_PER_SECOND;        }
    if ( ticks > ALIB_NANOS_PER_MILLISECOND )    {    fract= ticks / ALIB_NANOS_PER_MILLISECOND;    Milliseconds=   (int) fract;        ticks-= fract * ALIB_NANOS_PER_MILLISECOND;   }
    if ( ticks > ALIB_NANOS_PER_MICROSECOND )    {    fract= ticks / ALIB_NANOS_PER_MICROSECOND;    Microseconds=   (int) fract;        ticks-= fract * ALIB_NANOS_PER_MICROSECOND;   }
}

int_fast64_t        TickSpan::Get()
{
    int_fast64_t ticks=     Days          * ALIB_NANOS_PER_DAY
                         +  Hours         * ALIB_NANOS_PER_HOUR
                         +  Minutes       * ALIB_NANOS_PER_MINUTE
                         +  Seconds       * ALIB_NANOS_PER_SECOND
                         +  Milliseconds  * ALIB_NANOS_PER_MILLISECOND
                         +  Microseconds  * ALIB_NANOS_PER_MICROSECOND
                         +  Nanoseconds   * ALIB_NANOS_PER_NANOSECOND  ;

    #if defined( _WIN32 )
        Ticks toTicks( 0 );
        toTicks.FromNanos( ticks );
        ticks= toTicks.Raw();
    #endif

    return ticks;
}




// #################################################################################################
// TicksCalendarTime
// #################################################################################################

void TicksCalendarTime::Clear()
{
    Year=
    Month=
    Day=
    DayOfWeek=
    Hour=
    Minute=
    Second=
    Millisecond=    0;

    #if defined (__GLIBCXX__)
        tm_isdst= -1; // auto detect
    #endif

}

void TicksCalendarTime::Set( int_fast64_t ticks, Timezone timezone )
{
    Clear();
    Ticks t(ticks);

    #if defined (__GLIBCXX__)
        struct tm  tm;
        time_t tt= t.InEpochSeconds();
        if ( timezone == Timezone::UTC )
            gmtime_r( &tt, &tm );
        else
            localtime_r( &tt, &tm );

        Year=       tm.tm_year + 1900;
        Day=        tm.tm_mday;
        DayOfWeek=  tm.tm_wday;
        Month=      tm.tm_mon + 1;
        Second=     tm.tm_sec;
        Hour=       tm.tm_hour;
        Minute=     tm.tm_min;
        tm_isdst=   tm.tm_isdst;


    #elif defined( _WIN32 )
        SYSTEMTIME st;
        t.InSystemTime( &st, timezone );

        Year=       st.wYear;
        Day=        st.wDay;
        DayOfWeek=  st.wDayOfWeek;
        Month=      st.wMonth;
        Hour=       st.wHour;
        Minute=     st.wMinute;
        Second=     st.wSecond;

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif
}

int_fast64_t  TicksCalendarTime::Get( Timezone timezone )
{
    Ticks t(0);

    #if defined (__GLIBCXX__)
        struct tm  tm;
        tm.tm_year=       Year - 1900;
        tm.tm_mday=       Day;
        tm.tm_mon=        Month -1;
        tm.tm_hour=       Hour;
        tm.tm_min=        Minute;
        tm.tm_sec=        Second;
        tm.tm_isdst=      tm_isdst;

        time_t tt;
        if ( timezone == Timezone::UTC )
            tt= timegm( &tm );
        else
            tt= mktime( &tm );

        t.SetFromEpochSeconds( tt );


    #elif defined( _WIN32 )

        SYSTEMTIME st;
        st.wYear=           (WORD) Year;
        st.wDay=            (WORD) Day;
        st.wDayOfWeek=      (WORD) DayOfWeek;
        st.wMonth=          (WORD) Month;
        st.wHour=           (WORD) Hour;
        st.wMinute=         (WORD) Minute;
        st.wSecond=         (WORD) Second;
        st.wMilliseconds=   0;

        t.SetFromSystemTime( st, timezone );

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif

    return t.Raw();
}



#if !defined( IS_DOXYGEN_PARSER )
const TString months[]= { "January", "February", "March", "April", "May", "June",
                          "July", "August",  "September", "October", "November", "December"   };
const TString   days[]= { "Sunday", "Monday", "Tuesday", "Wednesday",
                          "Thursday", "Friday", "Saturday"                                    };
#endif

AString& TicksCalendarTime::Format( Substring format, AString& target, CurrentData targetData )
{
    if ( targetData == CurrentData::Clear )
        target.Clear();

    // this ensures that target is not nulled, as all other appends are NC-versions
    target._("");

    while ( format.IsNotEmpty() )
    {
        // read n equal characters
        int  n=  1;
        char c=  format.Consume();
        while (  format.Consume(c) )
            n++;

        switch (c)
        {
            case '\'': // single quotes
            {
                // one or more pairs of single quotes?
                if ( n > 1 )
                {
                    int pairs= n >> 1;
                    target.InsertChars<false>( '\'', pairs );
                    n-= (pairs << 1);
                }

                // one single quote?
                if ( n == 1 )
                {
                    // search end
                    int end= format.IndexOf( '\'' );
                    if ( end < 1 )
                    {
                        ALIB_WARNING( "Format Error: Missing single Quote" );
                        target << "Format Error: Missing single Quote";
                        return target;
                    }

                    target._NC( format, 0, end );
                    format.Consume<false>( end + 1 );
                }

            } break;

            case 's': // second
                target._NC( Format::Int32( Second, n ) );
                break;

            case 'm': //minute
                target._NC( Format::Int32( Minute, n ) );
                break;

            case 'K': // hour 0..11
                target._NC( Format::Int32( Hour % 12, n ) );
                target._NC( Hour < 12 ? " am" : " pm" );
                break;

            case 'H': // hour 0..23
                target._NC( Format::Int32( Hour,   n ) );
                break;

            case 'd': // day
                     if ( n <= 2 )     target._NC( Format::Int32( Day, n) );
                else if ( n == 3 )     target._NC( days[DayOfWeek], 0, 3 );
                else                   target._NC( days[DayOfWeek]    );
                break;

            case 'M': // month
                     if ( n <= 2 )     target._NC( Format::Int32( Month, n ) );
                else if ( n == 3 )     target._NC( months[Month-1], 0, 3 );
                else                   target._NC( months[Month-1]     );
                break;

            case 'y': // year
                     if ( n == 1 )     target._NC( Format::Int32(Year,        1) );
                else if ( n == 2 )     target._NC( Format::Int32(Year %  100, 2) );
                else                   target._NC( Format::Int32(Year,        n) );
                break;

            default: // otherwise: copy what was in
                target.InsertChars<false>( c, n );
                break;
        }

    }

    return target;
}


}}}// namespace aworx::lib::system

