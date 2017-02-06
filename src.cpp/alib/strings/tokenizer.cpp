// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
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

Substring&    Tokenizer::Next( lang::Whitespaces trimming, char newDelim )
{
    if ( Rest.IsNull() )
    {
        Actual.SetNull();
        return Actual;
    }

    // change of delim?
    if ( newDelim != '\0' )
        delim= newDelim;

    do
    {
        integer nextDelimiter= Rest.IndexOf( delim );

        if ( nextDelimiter >= 0 )
        {
            Actual.Set<false>( Rest, 0   , nextDelimiter  );
            Rest  .Set<false>( Rest,       nextDelimiter + 1, Rest.Length() - (nextDelimiter + 1) );
        }
        else
        {
            Actual.Set( Rest );
            Rest  .SetNull();
        }

        // trim
        if ( trimming == lang::Whitespaces::Trim )
            Actual.Trim( Whitespaces );
    }
    while( skipEmpty && Actual.IsEmpty() && Rest.IsNotNull() );

    return Actual;
}

}}}// namespace aworx::lib::strings
