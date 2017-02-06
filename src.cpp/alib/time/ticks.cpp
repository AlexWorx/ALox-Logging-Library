// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

#include "alib/alib.hpp"

#if !defined (HPP_ALIB_TIME_CALENDARTIME)
    #include "alib/time/calendartime.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_SUBSTRING)
    #include "alib/strings/substring.hpp"
#endif
#if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif


#if !defined (_GLIBCXX_CMATH) && !defined (_CMATH_)
    #include <cmath>
#endif

using namespace std;


namespace aworx { namespace lib { namespace time
{
// static members
int64_t    Ticks::inaccuracy;
Ticks*     Ticks::creationTime;


// #################################################################################################
// glibc specific: library init, InEpochSeconds(), SetFromEpochSeconds()
// #################################################################################################

#if defined (__GLIBCXX__) || defined(__APPLE__)

    rawtime    Ticks::diffOfMonotonicClockAndNow;


    void Init()
    {
        // get the timers resolution. On workstations, the result should be seconds= 0, nanoseconds= 1
        // which means 1 tick per nanosecond
        struct timespec t;
        ALIB_ASSERT_RESULT_EQUALS ( clock_getres(CLOCK_MONOTONIC, &t), 0 );

        // convert the resolution into frequency (measured in 1/s)
        Ticks::inaccuracy= t.tv_sec * ALIB_NANOS_PER_SECOND   +   t.tv_nsec;

        // create a ticks object that marks the time of creation of ALIB
        Ticks::creationTime= new Ticks();

        SyncClock();
    }

    void SyncClock()
    {
        // We are measuring the difference between the clock and the monotonic clock twice and
        // use the smaller result. Longer results indicates that the measurement got interrupted.
        // At the end of the day, the accuracy is not too important here. The impact is only on
        // converting ticks to clock times.
        struct timespec t;
        ALIB_ASSERT_RESULT_EQUALS ( clock_gettime(CLOCK_REALTIME, &t), 0 );
        rawtime diff1=  ( t.tv_sec * ALIB_NANOS_PER_SECOND  + t.tv_nsec)  - Ticks().Raw();
        ALIB_ASSERT_RESULT_EQUALS ( clock_gettime(CLOCK_REALTIME, &t), 0 );
        rawtime diff2=  ( t.tv_sec * ALIB_NANOS_PER_SECOND  + t.tv_nsec)  - Ticks().Raw();

        Ticks::diffOfMonotonicClockAndNow= diff1 < diff2 ? diff1 : diff2;
    }


    void TerminationCleanUp()
    {
        delete Ticks::creationTime;
    }


    time_t    Ticks::InEpochSeconds ()
    const
    {
        return    static_cast<time_t>( ( ticks + diffOfMonotonicClockAndNow  ) / ALIB_NANOS_PER_SECOND );
    }

    void Ticks::SetFromEpochSeconds ( time_t epochSeconds )
    {
        ticks=  epochSeconds  * ALIB_NANOS_PER_SECOND - diffOfMonotonicClockAndNow;
    }



// #################################################################################################
// MSC (Windows) specific: library init, InEpochSeconds()/SetFromEpochSeconds()
// #################################################################################################
#elif defined( _WIN32 )

    // static members
    int64_t        Ticks::ticksPerSecond;


    int64_t         mscCreationFileTime;
    int64_t         mscFileTimeNowMinusTicksNow;
    double          mscTicksToFileTime;

    // static library initialization code ( invoked by ALIB::Init() )
    void Init()
    {
        // get system's timer frequency
        LARGE_INTEGER   frequency;
        QueryPerformanceFrequency( &frequency );
        Ticks::inaccuracy=     ALIB_NANOS_PER_SECOND / frequency.QuadPart;
        Ticks::ticksPerSecond= frequency.QuadPart << 1;

        mscTicksToFileTime= 10000000.0 / (double)Ticks::ticksPerSecond;

        // create a ticks object that marks the time of creation of ALib
        Ticks::creationTime= new Ticks();

        // get creation time as file time
        FILETIME  ftNow;
        GetSystemTimeAsFileTime( &ftNow );

        ULARGE_INTEGER converter;
        converter.HighPart= ftNow.dwHighDateTime;
        converter.LowPart=  ftNow.dwLowDateTime;
        mscCreationFileTime= converter.QuadPart;

        // synchronize monotonic clock with system clock
        SyncClock();
    }
    void SyncClock()
    {
        // We are measuring the difference between the clock and the monotonic clock twice and
        // use the smaller result. Longer results indicates that the measurement got interrupted.
        // At the end of the day, the accuracy is not too important here. The impact is only on
        // converting ticks to clock times.
        FILETIME        ftNow;
        ULARGE_INTEGER  converter;

        // 1st measure
        GetSystemTimeAsFileTime( &ftNow );
        converter.HighPart= ftNow.dwHighDateTime;
        converter.LowPart=  ftNow.dwLowDateTime;
        int64_t diff1 = converter.QuadPart -  ( Ticks().Raw() * 10000000 / Ticks::ticksPerSecond );

        // 2nd measure
        GetSystemTimeAsFileTime( &ftNow );
        converter.HighPart= ftNow.dwHighDateTime;
        converter.LowPart=  ftNow.dwLowDateTime;
        int64_t diff2 = converter.QuadPart -  ( Ticks().Raw() * 10000000 / Ticks::ticksPerSecond );

        mscFileTimeNowMinusTicksNow= diff1 < diff2 ? diff1 : diff2;
    }

    // static library destruction code ( invoked by ALIB::TerminationCleanUp() )
    void TerminationCleanUp()
    {
        delete Ticks::creationTime;
    }


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


// #################################################################################################
// platform independent methods
// #################################################################################################

double Ticks::InHertz( int nDigitsPrec ) const
{
    // check
    if ( ticks == 0)
        return 0.0;

    // calc hertz
    double hz;
    #if defined (__GLIBCXX__) || defined(__APPLE__)
        hz= static_cast<double>(ALIB_NANOS_PER_SECOND) /  ticks;
    #elif defined( _WIN32 )
        hz=  ((double) Ticks::ticksPerSecond ) / ((double) ticks );
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

AString&  Ticks::Format( const String& format,  AString& target )
{
    TicksCalendarTime ct(*this);
    return ct.Format( format, target );
}


#if ALIB_MODULE_BOXING  && !defined(DOX_PARSER)

//! [DOX_ALIB_BOXING_IFORMAT_TTICKS]
void IFormat_TTicks::Invoke( const Box& box, const String& formatSpec, AString& target )
{
    TicksCalendarTime tct( *(box.Unbox<Ticks*>()) );
    tct.Format( formatSpec, target );
}
//! [DOX_ALIB_BOXING_IFORMAT_TTICKS]

#endif



}}}// namespace aworx::lib::time

