// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALIB_STRINGS_SUBSTRING)
    #include "alib/strings/substring.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif

#if !defined (_GLIBCXX_OSTREAM)
    #include <ostream>
#endif


// Windows.h might bring in max/min macros
#if defined( max )
    #undef max
    #undef min
#endif

using namespace std;

namespace aworx { namespace lib { namespace strings
{

bool   Substring::consumeDecDigitsImpl( uint64_t& result )
{
    integer idx= 0;
    result=  NumberFormat::ParseDecDigits( *this, idx );
    if( idx > 0 )
    {
        ConsumeChars<false>( idx );
        return true;
    }
    return false;
}

bool   Substring::consumeIntImpl( int64_t& result, NumberFormat* numberFormat )
{
    if ( numberFormat == nullptr )
        numberFormat= &NumberFormat::Computational;

    integer idx= 0;
    result=  numberFormat->ParseInt( *this, idx );
    if( idx > 0 )
    {
        ConsumeChars<false>( idx );
        return true;
    }
    return false;
}

bool   Substring::consumeDecImpl( uint64_t& result, NumberFormat* numberFormat )
{
    if ( numberFormat == nullptr )
        numberFormat= &NumberFormat::Computational;

    integer idx= 0;
    result=  numberFormat->ParseDec( *this, idx );
    if( idx > 0 )
    {
        ConsumeChars<false>( idx );
        return true;
    }
    return false;
}

bool   Substring::consumeBinImpl( uint64_t& result, NumberFormat* numberFormat )
{
    if ( numberFormat == nullptr )
        numberFormat= &NumberFormat::Computational;

    integer idx= 0;
    result=  numberFormat->ParseBin( *this, idx );
    if( idx > 0 )
    {
        ConsumeChars<false>( idx );
        return true;
    }
    return false;
}

bool   Substring::consumeHexImpl( uint64_t& result, NumberFormat* numberFormat )
{
    if ( numberFormat == nullptr )
        numberFormat= &NumberFormat::Computational;

    integer idx= 0;
    result=  numberFormat->ParseHex( *this, idx );
    if( idx > 0 )
    {
        ConsumeChars<false>( idx );
        return true;
    }
    return false;
}

bool   Substring::consumeOctImpl( uint64_t& result, NumberFormat* numberFormat )
{
    if ( numberFormat == nullptr )
        numberFormat= &NumberFormat::Computational;

    integer idx= 0;
    result=  numberFormat->ParseOct( *this, idx );
    if( idx > 0 )
    {
        ConsumeChars<false>( idx );
        return true;
    }
    return false;
}

bool   Substring::ConsumeFloat( double&          result,
                                NumberFormat*    numberFormat   )
{
    if ( numberFormat == nullptr )
        numberFormat= &NumberFormat::Computational;

    integer idx= 0;
    result=  numberFormat->ParseFloat( *this, idx );
    if( idx > 0 )
    {
        ConsumeChars<false>( idx );
        return true;
    }
    return false;
}

integer  Substring::ConsumePartOf(  const String&     consumable,
                                    int               minChars,
                                    lang::Case        sensitivity,
                                    lang::Whitespaces trimBeforeConsume )
{
    if ( trimBeforeConsume == lang::Whitespaces::Trim )
        TrimStart();

    if ( minChars == 0 || minChars > consumable.Length() )
        return 0;

    integer diff= IndexOfFirstDifference( consumable, sensitivity );
    if( diff < static_cast<integer>( minChars ) )
        return 0;
    ConsumeChars( diff );
    return diff;
}


}}}// namespace aworx::lib::strings
