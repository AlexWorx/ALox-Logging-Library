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

namespace time {



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

AString&  Ticks::Format( const String& format,  AString& target )
{
    TicksCalendarTime ct(*this);
    return ct.Format( format, target );
}


#if ALIB_MODULE_BOXING  && !defined(DOX_PARSER)

void IFormat_TTicks::Invoke( const Box& box, const String& formatSpec, AString& target )
{
    TicksCalendarTime tct( (box.Unbox<Ticks>()) );
    tct.Format( formatSpec, target );
}

#endif



}}}// namespace [aworx::lib::time]

