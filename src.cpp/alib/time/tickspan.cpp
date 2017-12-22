// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
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

void TickSpan::Set( Time::TRaw ticks )
{
    Clear();


    #if defined( _WIN32 )
        Ticks toNanos( ticks );
        ticks= toNanos.InNanos();
    #endif

    Time::TRaw fract=    0;
    if ( ticks > Time::NanosPerDay )          { fract= ticks / Time::NanosPerDay;         Days=         static_cast<int>( fract ); ticks-= fract * Time::NanosPerDay;         }
    if ( ticks > Time::NanosPerHour )         { fract= ticks / Time::NanosPerHour;        Hours=        static_cast<int>( fract ); ticks-= fract * Time::NanosPerHour;        }
    if ( ticks > Time::NanosPerMinute )       { fract= ticks / Time::NanosPerMinute;      Minutes=      static_cast<int>( fract ); ticks-= fract * Time::NanosPerMinute;      }
    if ( ticks > Time::NanosPerSecond )       { fract= ticks / Time::NanosPerSecond;      Seconds=      static_cast<int>( fract ); ticks-= fract * Time::NanosPerSecond;      }
    if ( ticks > Time::NanosPerMillisecond )  { fract= ticks / Time::NanosPerMillisecond; Milliseconds= static_cast<int>( fract ); ticks-= fract * Time::NanosPerMillisecond; }
    if ( ticks > Time::NanosPerMicrosecond )  { fract= ticks / Time::NanosPerMicrosecond; Microseconds= static_cast<int>( fract );                                             }
}

Time::TRaw        TickSpan::Get()
{
    Time::TRaw ticks=     Days          * Time::NanosPerDay
                    +  Hours         * Time::NanosPerHour
                    +  Minutes       * Time::NanosPerMinute
                    +  Seconds       * Time::NanosPerSecond
                    +  Milliseconds  * Time::NanosPerMillisecond
                    +  Microseconds  * Time::NanosPerMicrosecond
                    +  Nanoseconds;

    #if defined( _WIN32 )
        Ticks toTicks( 0 );
        toTicks.FromNanos( ticks );
        ticks= toTicks.Raw();
    #endif
    return ticks;
}



}}}// namespace [aworx::lib::time]

