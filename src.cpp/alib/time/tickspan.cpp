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


namespace aworx { namespace lib { namespace time
{
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

void TickSpan::Set( rawtime ticks )
{
    Clear();


    #if defined( _WIN32 )
        Ticks toNanos( ticks );
        ticks= toNanos.InNanos();
    #endif

    rawtime fract=    0;
    if ( ticks > ALIB_NANOS_PER_DAY )          { fract= ticks / ALIB_NANOS_PER_DAY;         Days=         static_cast<int>( fract ); ticks-= fract * ALIB_NANOS_PER_DAY;         }
    if ( ticks > ALIB_NANOS_PER_HOUR )         { fract= ticks / ALIB_NANOS_PER_HOUR;        Hours=        static_cast<int>( fract ); ticks-= fract * ALIB_NANOS_PER_HOUR;        }
    if ( ticks > ALIB_NANOS_PER_MINUTE )       { fract= ticks / ALIB_NANOS_PER_MINUTE;      Minutes=      static_cast<int>( fract ); ticks-= fract * ALIB_NANOS_PER_MINUTE;      }
    if ( ticks > ALIB_NANOS_PER_SECOND )       { fract= ticks / ALIB_NANOS_PER_SECOND;      Seconds=      static_cast<int>( fract ); ticks-= fract * ALIB_NANOS_PER_SECOND;      }
    if ( ticks > ALIB_NANOS_PER_MILLISECOND )  { fract= ticks / ALIB_NANOS_PER_MILLISECOND; Milliseconds= static_cast<int>( fract ); ticks-= fract * ALIB_NANOS_PER_MILLISECOND; }
    if ( ticks > ALIB_NANOS_PER_MICROSECOND )  { fract= ticks / ALIB_NANOS_PER_MICROSECOND; Microseconds= static_cast<int>( fract );                                             }
}

rawtime        TickSpan::Get()
{
    rawtime ticks=     Days          * ALIB_NANOS_PER_DAY
                    +  Hours         * ALIB_NANOS_PER_HOUR
                    +  Minutes       * ALIB_NANOS_PER_MINUTE
                    +  Seconds       * ALIB_NANOS_PER_SECOND
                    +  Milliseconds  * ALIB_NANOS_PER_MILLISECOND
                    +  Microseconds  * ALIB_NANOS_PER_MICROSECOND
                    +  Nanoseconds;

    #if defined( _WIN32 )
        Ticks toTicks( 0 );
        toTicks.FromNanos( ticks );
        ticks= toTicks.Raw();
    #endif
    return ticks;
}



}}}// namespace aworx::lib::time

