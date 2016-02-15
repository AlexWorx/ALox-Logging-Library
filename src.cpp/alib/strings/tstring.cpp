// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"


#if !defined (HPP_ALIB_STRINGS_ASSUBSTRING)
    #include "alib/strings/substring.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif


#if !defined (_GLIBCXX_CSTRING)  && !defined(_CSTRING_)
    #include <cstring>
#endif
#if !defined (_STRING_H)         && !defined(_INC_STRING)
    #include <string.h>
#endif
#if !defined (_GLIBCXX_CSTDLIB)  && !defined(_CSTDLIB_)
    #include <cstdlib>
#endif
#if !defined (_MATH_H)           && !defined(_INC_MATH)
    #include <math.h>
#endif

#if !defined (_GLIBCXX_IOSTREAM ) && !defined(_IOSTREAM_)
    #include <iostream>
#endif

using namespace std;


namespace aworx {
namespace           lib {
namespace                   strings {



// *************************************************************************************************
// String::_dbgCheck()
// *************************************************************************************************
#if defined(ALIB_DEBUG_STRINGS) && !defined( IS_DOXYGEN_PARSER )

    #if !defined(ALIB_DEBUG)
        #pragma message "Compiler symbol ALIB_DEBUG_STRINGS_ON set, while ALIB_DEBUG is off. Is this really wanted?"
    #endif

    void TString::_dbgCheck() const
    {
        String::_dbgCheck();

        ALIB_ASSERT_ERROR(      buffer == nullptr
                                ||  debugIsTerminated <= 0
                                ||  buffer[length] == '\0'
                                ,"Terminated but terminator char '\\0' not present"         );
    }

#endif



int64_t    TString::ToLong( int  startIdx, int* newIdx, const TString* whitespaces )
const
{
    // initialize output variable newIdx
    if ( newIdx != nullptr )
        *newIdx= startIdx;

    if ( startIdx < 0 || startIdx >= length )
        return 0;

    // get index, read whitespaces and store start index after white spaces
    if( whitespaces == nullptr )
        whitespaces= &DefaultWhitespaces;
    if ( ( startIdx= IndexOfAny<false>( *whitespaces, Inclusion::Exclude, startIdx ) ) == -1 )
        return 0;

    int oldIdx= startIdx;

    int64_t retval= NumberFormat::Global.StringToInteger( this, startIdx );

    // was an index pointer given? If yes, we move it
    if ( newIdx != nullptr && oldIdx != startIdx )
        *newIdx= startIdx;

    return retval;
}

double    TString::ToFloat(  int              startIdx,
                             int*             newIdx,
                             NumberFormat*    numberFormat,
                             const TString*   whitespaces        )
const
{
    // initialize output variable newIdx
    if ( newIdx != nullptr )
        *newIdx= startIdx;

    if ( startIdx < 0 || startIdx >= length )
        return 0;

    if ( numberFormat == nullptr )
        numberFormat= &NumberFormat::Global;

    // get index, read whitespaces and store start index after white spaces
    if( whitespaces == nullptr )
        whitespaces= &DefaultWhitespaces;
    if ( ( startIdx= IndexOfAny<false>( whitespaces, Inclusion::Exclude, startIdx ) ) == -1 )
        return 0;

    int oldIdx= startIdx;
    double retval= numberFormat->StringToFloat( this, startIdx );

    // was an index pointer given? If yes, we move it
    if ( newIdx != nullptr && oldIdx != startIdx )
        *newIdx= startIdx;

    return retval;

}




}}}// namespace aworx::lib::strings
