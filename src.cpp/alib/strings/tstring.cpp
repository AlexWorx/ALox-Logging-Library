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


#if !defined (_GLIBCXX_CSTRING)  && !defined(_CSTRING_)
    #include <cstring>
#endif
#if !defined (_STRING_H)         && !defined(_INC_STRING)
    #include <string.h>
#endif
#if !defined (_GLIBCXX_CSTDLIB)  && !defined(_CSTDLIB_)
    #include <cstdlib>
#endif
#if !defined (_GLIBCXX_IOSTREAM ) && !defined(_IOSTREAM_)
    #include <iostream>
#endif

using namespace std;


namespace aworx { namespace lib { namespace strings
{


// *************************************************************************************************
// String::_dbgCheck()
// *************************************************************************************************
//! @cond NO_DOX
#if ALIB_DEBUG_STRINGS

    #if !ALIB_DEBUG
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
//! @endcond NO_DOX

uint64_t    TString::ParseDecDigits( integer  startIdx, integer* newIdx )
const
{
    // we need an index pointer reference. So if none was given in parameter newIdx
    // then we just use parameter startIdx!
    integer* indexPointer;
    if ( newIdx == nullptr )
        indexPointer= &startIdx;
    else
    {
        indexPointer=  newIdx;
        *indexPointer= startIdx;
    }

    return NumberFormat::ParseDecDigits( *this, *indexPointer );
}


int64_t    TString::ParseInt( integer  startIdx, NumberFormat* numberFormat, integer* newIdx )
const
{
    // we need an index pointer reference. So if none was given in parameter newIdx
    // then we just use parameter startIdx!
    integer* indexPointer;
    if ( newIdx == nullptr )
        indexPointer= &startIdx;
    else
    {
        indexPointer=  newIdx;
        *indexPointer= startIdx;
    }

    return (numberFormat == nullptr ? &NumberFormat::Computational
                                    : numberFormat )
           ->ParseInt( *this, *indexPointer );
}

uint64_t    TString::ParseDec( integer  startIdx, NumberFormat* numberFormat, integer* newIdx )
const
{
    // we need an index pointer reference. So if none was given in parameter newIdx
    // then we just use parameter startIdx!
    integer* indexPointer;
    if ( newIdx == nullptr )
        indexPointer= &startIdx;
    else
    {
        indexPointer=  newIdx;
        *indexPointer= startIdx;
    }

    return (numberFormat == nullptr ? &NumberFormat::Computational
                                    : numberFormat )
           ->ParseDec( *this, *indexPointer );
}

uint64_t    TString::ParseBin( integer startIdx, NumberFormat* numberFormat, integer* newIdx  )
const
{
    // we need an index pointer reference. So if none was given in parameter newIdx
    // then we just use parameter startIdx!
    integer* indexPointer;
    if ( newIdx == nullptr )
        indexPointer= &startIdx;
    else
    {
        indexPointer=  newIdx;
        *indexPointer= startIdx;
    }

    return (numberFormat == nullptr ? &NumberFormat::Computational
                                    : numberFormat )
           ->ParseBin( *this, *indexPointer );
}

uint64_t    TString::ParseHex( integer startIdx, NumberFormat* numberFormat, integer* newIdx  )
const
{
    // we need an index pointer reference. So if none was given in parameter newIdx
    // then we just use parameter startIdx!
    integer* indexPointer;
    if ( newIdx == nullptr )
        indexPointer= &startIdx;
    else
    {
        indexPointer=  newIdx;
        *indexPointer= startIdx;
    }

    return (numberFormat == nullptr ? &NumberFormat::Computational
                                    : numberFormat )
           ->ParseHex( *this, *indexPointer );
}

uint64_t    TString::ParseOct( integer startIdx, NumberFormat* numberFormat, integer* newIdx  )
const
{
    // we need an index pointer reference. So if none was given in parameter newIdx
    // then we just use parameter startIdx!
    integer* indexPointer;
    if ( newIdx == nullptr )
        indexPointer= &startIdx;
    else
    {
        indexPointer=  newIdx;
        *indexPointer= startIdx;
    }

    return (numberFormat == nullptr ? &NumberFormat::Computational
                                    : numberFormat )
           ->ParseOct( *this, *indexPointer );
}

double    TString::ParseFloat( integer startIdx, NumberFormat* numberFormat, integer* newIdx )
const
{
    // we need an index pointer reference. So if none was given in parameter newIdx
    // then we just use parameter startIdx!
    integer* indexPointer;
    if ( newIdx == nullptr )
        indexPointer= &startIdx;
    else
    {
        indexPointer=  newIdx;
        *indexPointer= startIdx;
    }

    return (numberFormat == nullptr ? &NumberFormat::Computational
                                    : numberFormat )
           ->ParseFloat( *this, *indexPointer );
}



}}}// namespace aworx::lib::strings
