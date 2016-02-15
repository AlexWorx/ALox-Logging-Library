// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

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

namespace aworx {
namespace           lib {
namespace                   strings {


Substring&    Tokenizer::Next( enums::Whitespaces trimming, char newDelim )
{
    if ( Rest.IsNull() )
    {
        Actual.SetNull();
        return Actual;
    }

    // change of delim?
    if ( newDelim != '\0' )
        delim= newDelim;

    int nextDelimiter= Rest.IndexOf( delim );

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
    if ( trimming == enums::Whitespaces::Trim )
        Actual.Trim( Whitespaces );

    return Actual;
}

}}}// namespace aworx::lib::strings
