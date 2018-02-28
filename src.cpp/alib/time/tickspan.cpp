// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

#include "alib/alib.hpp"

#if !defined (HPP_ALIB_TIME_TICKSPAN)
    #include "alib/time/tickspan.hpp"
#endif


#if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif


namespace aworx { namespace lib { namespace time {
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

void TickSpan::Set( TimeLib::TRaw ticks )
{
    Clear();


    #if defined( _WIN32 )
        Ticks toNanos( ticks );
        ticks= toNanos.InNanos();
    #endif

    TimeLib::TRaw fract=    0;
    if ( ticks > TimeLib::NanosPerDay )          { fract= ticks / TimeLib::NanosPerDay;         Days=         static_cast<int>( fract ); ticks-= fract * TimeLib::NanosPerDay;         }
    if ( ticks > TimeLib::NanosPerHour )         { fract= ticks / TimeLib::NanosPerHour;        Hours=        static_cast<int>( fract ); ticks-= fract * TimeLib::NanosPerHour;        }
    if ( ticks > TimeLib::NanosPerMinute )       { fract= ticks / TimeLib::NanosPerMinute;      Minutes=      static_cast<int>( fract ); ticks-= fract * TimeLib::NanosPerMinute;      }
    if ( ticks > TimeLib::NanosPerSecond )       { fract= ticks / TimeLib::NanosPerSecond;      Seconds=      static_cast<int>( fract ); ticks-= fract * TimeLib::NanosPerSecond;      }
    if ( ticks > TimeLib::NanosPerMillisecond )  { fract= ticks / TimeLib::NanosPerMillisecond; Milliseconds= static_cast<int>( fract ); ticks-= fract * TimeLib::NanosPerMillisecond; }
    if ( ticks > TimeLib::NanosPerMicrosecond )  { fract= ticks / TimeLib::NanosPerMicrosecond; Microseconds= static_cast<int>( fract );                                             }
}

TimeLib::TRaw        TickSpan::Get()
{
    TimeLib::TRaw ticks=     Days          * TimeLib::NanosPerDay
                    +  Hours         * TimeLib::NanosPerHour
                    +  Minutes       * TimeLib::NanosPerMinute
                    +  Seconds       * TimeLib::NanosPerSecond
                    +  Milliseconds  * TimeLib::NanosPerMillisecond
                    +  Microseconds  * TimeLib::NanosPerMicrosecond
                    +  Nanoseconds;

    #if defined( _WIN32 )
        Ticks toTicks( 0 );
        toTicks.FromNanos( ticks );
        ticks= toTicks.Raw();
    #endif
    return ticks;
}



}}}// namespace [aworx::lib::time]

