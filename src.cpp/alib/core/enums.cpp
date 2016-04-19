// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif


using namespace std;

namespace aworx {
namespace           lib {
namespace               enums {


bool ReadBoolean( const String& src )
{
    int idx= src.IndexOfAny( DefaultWhitespaces, Inclusion::Exclude );
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
    int idx= src.IndexOfAny( DefaultWhitespaces, Inclusion::Exclude );
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
    int idx= src.IndexOfAny( DefaultWhitespaces, Inclusion::Exclude );
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



}}}// namespace aworx::lib::enums

