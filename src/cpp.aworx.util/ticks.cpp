// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#include "stdafx_awxu.h"

#if !defined (HPP_AWORX_UTIL_TICKS)
    #include "ticks.hpp"
#endif


#if !defined (_GLIBCXX_CMATH) && !defined (_CMATH_)
    #include <cmath>
#endif


using namespace std;

namespace aworx {
namespace       util {

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
    // static library initialization code ( invoked by AWXU::Init() )
    void Ticks::_awxu_init_lib_ticks()
    {
        // get the timers resolution. On workstations, the result should be secs= 0, nanosecs= 1
        // which means 1 tick per nanosec
        struct timespec t;
        AWXU_ASSERT_RESULT_EQUALS ( clock_getres(CLOCK_MONOTONIC, &t), 0 );

        // convert the resolution into frequency (measured in 1/s)
        Ticks::frequency= ( (double) AWXU_NANOS_PER_SECOND ) / ( t.tv_sec * AWXU_NANOS_PER_SECOND + t.tv_nsec );

        // create a ticks object that marks the time of creation of AWXU
        creationTime= new Ticks();
    }

    // static library destruction code ( invoked by AWXU::TerminationCleanUp() )
    void Ticks::_awxu_destruct_lib_ticks()
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
        AWXU_ASSERT_RESULT_EQUALS ( clock_gettime(CLOCK_REALTIME, &t), 0 );
        int_fast64_t nowReal=   ( t.tv_sec * AWXU_NANOS_PER_SECOND  ) + t.tv_nsec ;

        return    ( ticks + (nowReal - now.ticks)  ) / AWXU_NANOS_PER_SECOND;
    }

    //  SetFromEpochSeconds
    void Ticks::SetFromEpochSeconds ( time_t epochSeconds )
    {
        // get Ticks clocks now in ticks
        Ticks now;

        // get real clock now in ticks
        struct timespec t;
        AWXU_ASSERT_RESULT_EQUALS ( clock_gettime(CLOCK_REALTIME, &t), 0 );
        int_fast64_t nowReal=    t.tv_sec;

        ticks= ( epochSeconds - (nowReal  - now.InSeconds())  ) * AWXU_NANOS_PER_SECOND;
    }


// #################################################################################################
// MSC (Windows) specific: library init, InEpochSeconds()/SetFromEpochSeconds()
// #################################################################################################
#elif defined( _MSC_VER )

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

    // static library initialization code ( invoked by AWXU::Init() )
    void Ticks::_awxu_init_lib_ticks()
    {
        // get system's timer frequency
        LARGE_INTEGER   frequency;
        QueryPerformanceFrequency( &frequency );
        Ticks::frequency= frequency.QuadPart;

        // calculate the factor that we need to apply to system ticks, to get into
        // the magnitude of 1 digit nanoseconds per tick
        int_fast64_t fr=  Ticks::frequency;
        Ticks::mscResFactor=     1;
        while ( fr < AWXU_NANOS_PER_SECOND  ) //10 * (1sec in nanos)
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

        // create a ticks object that marks the time of creation of AWXU
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

    // static library destruction code ( invoked by AWXU::TerminationCleanUp() )
    void Ticks::_awxu_destruct_lib_ticks()
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
    void  Ticks::InSystemTime( LPSYSTEMTIME result, bool inUTC )
    const
    {
        FILETIME ft;
        InFileTime( &ft );
        if ( inUTC )
            FileTimeToSystemTime( &ft, result );
        else
        {
            SYSTEMTIME utc;
            FileTimeToSystemTime( &ft, &utc );
            SystemTimeToTzSpecificLocalTime( NULL, &utc, result );
        }

    }

    //  SetFromSystemTime
    void Ticks::SetFromSystemTime( const SYSTEMTIME& st, bool fromUTC )
    {
        FILETIME ft;
        if ( fromUTC )
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
        hz= ((double) AWXU_NANOS_PER_SECOND) / ticks;
    #elif defined( _MSC_VER )
        hz=  Ticks::mscTicksPerSecond / ((double) ticks );
    #else
        #pragma message ("Uknown Platform in file: " __FILE__ )
    #endif

    // no rounding? that's it
    if ( nDigitsPrec < 0 )
        return hz;

    // round
    double mag= pow( 10, nDigitsPrec );
    return ( (int) ( hz * mag + ( hz < 0 ? -0.5 : 0.5 )) ) / mag;
}

AString  Ticks::Format( const char* format )
{
    TicksCalendarTime ct(*this);
    AString64 retval;
    ct.Format( format, retval );
    return retval;
}


// #################################################################################################
// TicksSpan
// #################################################################################################

void TicksSpan::Clear()
{
    Days=
    Hours=
    Minutes=
    Seconds=
    Milliseconds=
    Microseconds=
    Nanoseconds=    0;
}

void TicksSpan::Set( int_fast64_t ticks )
{
    Clear();

    #if defined( _MSC_VER )
        Ticks toNanos( ticks );
        ticks= toNanos.InNanos();
    #endif

    int_fast64_t fract=    0;
    if ( ticks > AWXU_NANOS_PER_DAY )            {    fract= ticks / AWXU_NANOS_PER_DAY;            Days=           (int) fract;        ticks-= fract * AWXU_NANOS_PER_DAY;           }
    if ( ticks > AWXU_NANOS_PER_HOUR )           {    fract= ticks / AWXU_NANOS_PER_HOUR;           Hours=          (int) fract;        ticks-= fract * AWXU_NANOS_PER_HOUR;          }
    if ( ticks > AWXU_NANOS_PER_MINUTE )         {    fract= ticks / AWXU_NANOS_PER_MINUTE;         Minutes=        (int) fract;        ticks-= fract * AWXU_NANOS_PER_MINUTE;        }
    if ( ticks > AWXU_NANOS_PER_SECOND )         {    fract= ticks / AWXU_NANOS_PER_SECOND;         Seconds=        (int) fract;        ticks-= fract * AWXU_NANOS_PER_SECOND;        }
    if ( ticks > AWXU_NANOS_PER_MILLISECOND )    {    fract= ticks / AWXU_NANOS_PER_MILLISECOND;    Milliseconds=   (int) fract;        ticks-= fract * AWXU_NANOS_PER_MILLISECOND;   }
    if ( ticks > AWXU_NANOS_PER_MICROSECOND )    {    fract= ticks / AWXU_NANOS_PER_MICROSECOND;    Microseconds=   (int) fract;        ticks-= fract * AWXU_NANOS_PER_MICROSECOND;   }
}

int_fast64_t        TicksSpan::Get()
{
    int_fast64_t ticks=     Days          * AWXU_NANOS_PER_DAY
                         +  Hours         * AWXU_NANOS_PER_HOUR
                         +  Minutes       * AWXU_NANOS_PER_MINUTE
                         +  Seconds       * AWXU_NANOS_PER_SECOND
                         +  Milliseconds  * AWXU_NANOS_PER_MILLISECOND
                         +  Microseconds  * AWXU_NANOS_PER_MICROSECOND
                         +  Nanoseconds   * AWXU_NANOS_PER_NANOSECOND  ;

    #if defined( _MSC_VER )
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
}

void TicksCalendarTime::Set( int_fast64_t ticks, bool toUTC )
{
    Clear();
    Ticks t(ticks);

    #if defined (__GLIBCXX__)
        struct tm  tm;
        time_t tt= t.InEpochSeconds();
        if ( toUTC )
            gmtime_r( &tt, &tm );
        else
            localtime_r( &tt, &tm );

        Year=       tm.tm_year + 1900;
        Day=        tm.tm_mday;
        DayOfWeek=  tm.tm_wday;
        Month=      tm.tm_mon;
        Hour=       tm.tm_hour;
        Minute=     tm.tm_min;
        Second=     tm.tm_sec;


    #elif defined( _MSC_VER )
        SYSTEMTIME st;
        t.InSystemTime( &st, toUTC );

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

int_fast64_t  TicksCalendarTime::Get( bool isUTC )
{
    Ticks t(0);

    #if defined (__GLIBCXX__)
        struct tm  tm;
        tm.tm_year=       Year - 1900;
        tm.tm_mday=       Day;
        tm.tm_mon=        Month;
        tm.tm_hour=       Hour;
        tm.tm_min=        Minute;
        tm.tm_sec=        Second;


        time_t tt;
        if ( isUTC )
            tt= timegm( &tm );
        else
            tt= mktime( &tm );

        t.SetFromEpochSeconds( tt );


    #elif defined( _MSC_VER )

        SYSTEMTIME st;
        st.wYear=           (WORD) Year;
        st.wDay=            (WORD) Day;
        st.wDayOfWeek=      (WORD) DayOfWeek;
        st.wMonth=          (WORD) Month;
        st.wHour=           (WORD) Hour;
        st.wMinute=         (WORD) Minute;
        st.wSecond=         (WORD) Second;
        st.wMilliseconds=   0;

        t.SetFromSystemTime( st, isUTC );

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
    #endif

    return t.Raw();
}



#if !defined( DOXYGEN_OMIT_THIS_PLEASE )
const char* months[]= { "January", "February", "March", "April", "May", "June",
                        "July", "August",  "September", "October", "November", "December"   };
const char*   days[]= { "Sunday", "Monday", "Tuesday", "Wednesday",
                        "Thursday", "Friday", "Saturday"                                    };
#endif

void TicksCalendarTime::Format(const char* format, AString& destination)
{
    int i=  0;
    while ( format[i] != '\0' )
    {
        // read n equal characters
        int  n=  i;
        char c=  format[i++];
        while ( format[i] == c )
            i++;
        n= i-n;

        switch (c)
        {
            case '\'':
            {
                // one or more pairs of single quotes?
                if ( n > 1 )
                {
                    int pairs= n >> 1;
                    destination.Append( '\'', pairs );
                    n-= (pairs << 1);
                }

                // one single quote?
                if ( n == 1 )
                {
                    // search end
                    int s= i;
                    while ( format[i] != '\0' && format[i] != '\'' )
                        i++;
                    destination.Append( format, s, i-s );
                    if ( format[i] == '\'' )
                        i++;
                }

            } break;

            case 's':
            {
                if ( n == 1 )            destination.Append( Second    );
                else                   { destination.Append( Second, 2 );  i-= (n-2);  }

            } break;

            case 'm':
            {
                if ( n == 1 )            destination.Append( Minute    );
                else                   { destination.Append( Minute, 2 );  i-= (n-2);  }

            } break;

            case 'K':
            {
                if ( n  > 2 )
                {
                    i-= (n - 2);
                    n= 2;
                }
                destination.Append( Hour % 12, n  );
                destination.Append( Hour < 12 ? " am" : " pm" );
            } break;

            case 'H':
            {
                if ( n == 1 )          destination.Append( Hour      );
                else                 { destination.Append( Hour,   2 );  i-= (n-2);  }
            } break;

            case 'd':
            {
                     if ( n == 1 )     destination.Append( Day          );
                else if ( n == 2 )     destination.Append( Day,       2 );
                else if ( n == 3 )     destination.Append( days[DayOfWeek], 0, 3 );
                else                   destination.Append( days[DayOfWeek]       );
            } break;

            case 'M':
            {
                     if ( n == 1 )     destination.Append( Month        );
                else if ( n == 2 )     destination.Append( Month,     2 );
                else if ( n == 3 )     destination.Append( months[Month-1], 0, 3 );
                else                   destination.Append( months[Month-1]       );
            } break;

            case 'y':
            {
                     if ( n == 1 )     destination.Append( Year           );
                else if ( n == 2 )     destination.Append( Year %  100, 2 );
                else                   destination.Append( Year,        n );
            } break;


            default: destination.Append( c, n );
            break;
        }

    }
}




}}// namespace aworx::util

