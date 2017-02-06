// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

using namespace std;

#if ALIB_MODULE_STRINGS

namespace aworx { namespace lib { namespace lang
{

bool ReadBoolean( const String& src )
{
    integer idx= src.IndexOfAny( DefaultWhitespaces, Inclusion::Exclude );
    if ( idx >= 0 )
    {
        int c= tolower( src[idx] );
        int trueValues[]= { 't', '1', 'y' };
        for ( auto v : trueValues )
            if ( c == v )
                return true;

        int c2= tolower( src.CharAt( idx + 1 ) );
        if ( c == 'o' &&  ( c2 == 'n' || c2 == 'k' ) )
            return true;
    }
    return false;
}

Case ReadCase( const String& src )
{
    integer idx= src.IndexOfAny( DefaultWhitespaces, Inclusion::Exclude );
    if ( idx >= 0 )
    {
        int c= tolower( src[idx] );
        int trueValues[]= { 's', 't', '1', 'y' };
        for ( auto v : trueValues )
            if ( c == v )
                return Case::Sensitive;
    }
    return Case::Ignore;
}

Inclusion ReadInclusion( const String& src )
{
    integer idx= src.IndexOfAny( DefaultWhitespaces, Inclusion::Exclude );
    if ( idx >= 0 )
    {
        int c= tolower( src[idx] );
        int trueValues[]= { 'i', 't', '1', 'y' };
        for ( auto v : trueValues )
            if ( c == v )
                return Inclusion::Include;
    }
    return Inclusion::Exclude;
}

}}}// namespace aworx::lib::lang
#endif // ALIB_MODULE_STRINGS

