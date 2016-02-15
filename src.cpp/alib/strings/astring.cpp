// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"

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

// #################################################################################################
//  globals
// #################################################################################################

// *************************************************************************************************
// AString::_dbgCheck()
// *************************************************************************************************
#if defined(ALIB_DEBUG_STRINGS) && !defined( IS_DOXYGEN_PARSER )

    #if !defined(ALIB_DEBUG)
        #pragma message "Compiler symbol ALIB_DEBUG_STRINGS_ON set, while ALIB_DEBUG is off. Is this really wanted?"
    #endif

    void AString::_dbgCheck() const
    {
        TString::_dbgCheck();
        int capacity= Capacity();

        ALIB_ASSERT_ERROR(      buffer != nullptr
                                ||  length  == 0
                                ,"No buffer but length != 0" );

        ALIB_ASSERT_ERROR(      capacity      == 0
                                ||  debugIsTerminated != 0
                                ||  buffer[length]   == '\1'
                                ,"Not terminated but dbg-terminator char '\\1' not present" );

        ALIB_ASSERT_ERROR(      debugLastAllocRequest == 0
                                ||  length <= debugLastAllocRequest
                                ,"Error: Previous allocation request was too short"         );

        ALIB_ASSERT_ERROR(      length <= capacity
                                ,"Error: Length greater than allocation size"               );

        if( buffer && debugBufferWithMagicBytePadding )
        {
            for (int aworx_astring_dbg_i= -16 ; aworx_astring_dbg_i < 0 ; aworx_astring_dbg_i++)
                if ( buffer[aworx_astring_dbg_i] != 2 )
                {
                    ALIB_ERROR_AS( "Magic byte not found at start (buffer[" << aworx_astring_dbg_i << "])." );
                    break;
                }
            for (int aworx_astring_dbg_i= 1 ; aworx_astring_dbg_i <= 16 ; aworx_astring_dbg_i++)
                if ( buffer[ capacity + aworx_astring_dbg_i] != 3 )
                {
                    ALIB_ERROR_AS( "Magic byte not found at end (buffer[" << capacity + aworx_astring_dbg_i << "])." );
                    break;
                }
        }
    }

#endif



// ####################################################################################################
// Allocation
// ####################################################################################################

void AString::SetBuffer( int newSize )
{
    ALIB_STRING_DBG_CHK(this)

    ALIB_ASSERT( newSize >= 0 );

    // do nothing if life-cycle is managed by us and same size,
    if ( capacity >= 0 && capacity == newSize )
        return;

    #if defined(ALIB_DEBUG_STRINGS)
        debugLastAllocRequest= newSize;
    #endif

    // set uninitialized
    if ( newSize == 0 )
    {
        if ( capacity > 0 )
            #if !defined(ALIB_DEBUG_STRINGS)
                delete[] buffer;
            #else
                delete[] (buffer - (debugBufferWithMagicBytePadding ? 16 : 0) );
            #endif

        buffer=        nullptr;
        capacity=
        length=         0;
        return;
    }

    ALIB_WARN_ONCE_IF( capacity < 0,
                      "AString::SetAllocation(): replacing an external buffer. This may not be wanted.",
                      *this, ReplaceExternalBuffer )

    // create new Buffer
    #if !defined(ALIB_DEBUG_STRINGS)
        char* newBuffer=    new char[ newSize  + 1 ];
    #else
        // add 16 bytes of padding at start/end
        char* newBuffer=    new char[ newSize  + 1 + 32 ] + 16;

        // write 2 to start, 3 to end (0= termination byte, 1= untermination byte )
        memset( newBuffer - 16,         (char) 2, 16 );
        memset( newBuffer + newSize + 1, (char) 3, 16 );
    #endif

    // if we had a buffer before
    if ( buffer != nullptr)
    {
        // copy data and delete old buffer
        memcpy( newBuffer, buffer, min( length + 1, newSize + 1) );
        if ( capacity > 0 )
        #if !defined(ALIB_DEBUG_STRINGS)
            delete[] buffer;
        #else
            delete[] (buffer - (debugBufferWithMagicBytePadding ? 16 : 0) );
        #endif
    }
    else
    {
        ALIB_ASSERT( length == 0 );
    }

    // set new Buffer and adjust length
    buffer=     newBuffer;
    capacity=   newSize;
    if ( length > capacity )
        length= capacity;

    ALIB_STRING_DBG_UNTERMINATE(*this, 0)
    #if defined(ALIB_DEBUG_STRINGS)
        debugBufferWithMagicBytePadding= true;
    #endif
}



void AString::SetBuffer( char* extBuffer, int extBufferSize, int extLength,
                         Responsibility responsibility  )
{
    ALIB_ASSERT_ERROR(       !(extBufferSize == 0 && extBuffer != nullptr)
                           &&    !(extBufferSize != 0 && extBuffer == nullptr) ,
                      "AString::SetBuffer(): Given buffer is nullptr while given alloc size is not 0 (or vice versa)" );

    // delete any existing
    if ( capacity > 0 )
        #if !defined(ALIB_DEBUG_STRINGS)
            delete[] buffer;
        #else
            delete[] (buffer - (debugBufferWithMagicBytePadding ? 16 : 0) );
        #endif

    #if defined(ALIB_DEBUG_STRINGS)
        debugBufferWithMagicBytePadding= false;
    #endif

    // too small? treat as if a nullptr was given.
    if ( extBufferSize < 1 )
    {
        ALIB_ERROR( "allocation size < 1" );
        extBuffer= nullptr;
    }

    // nullbuffer?
    if ( (buffer= extBuffer) == nullptr )
    {
        capacity=
        length=       0;
        return;
    }

    if ( extLength >= extBufferSize  )
    {
        ALIB_ERROR( "ext length >= ext allocation size" );
        extLength= extBufferSize -1;
    }

    // save given buffer
    extBufferSize--;     // we count one less
    capacity=   responsibility==Responsibility::Transfer ?  extBufferSize
                                                         : -extBufferSize;
    length=     extLength;

    ALIB_STRING_DBG_UNTERMINATE(*this, 0)
}





// #################################################################################################
// _() - strings
// #################################################################################################


// #############################################################################################
// Trim
// #############################################################################################

AString& AString::TrimAt( int index, const TString& trimChars )
{
    if ( index < 0 || index >= length || trimChars.IsEmpty() )
         return *this;

    int regionStart= LastIndexOfAny<false>( trimChars, Inclusion::Exclude, index ) + 1;
    int idx=         IndexOfAny<false>        ( trimChars, Inclusion::Exclude, index );
    int regionEnd=   idx >=0 ? idx
                             : length;
    int regionLength= regionEnd - regionStart;
    if ( regionLength > 0 )
        Delete<false>( regionStart, regionLength );

    return *this;
}

AString& AString::Trim( const TString& trimChars )
{
    // check
    if (length == 0 || trimChars.IsEmpty() )
        return *this;

    // trim end
    int idx= LastIndexOfAny<false>( trimChars, Inclusion::Exclude, length - 1 ) + 1;
    if ( (length= idx) > 0 )
    {
        // trim front
        idx= IndexOfAny<false>( trimChars, Inclusion::Exclude);
        if ( idx > 0 )
            Delete<false>( 0, idx );
    }
    else
        length= 0;

    ALIB_STRING_DBG_UNTERMINATE(*this, 0)
    return *this;
}


// #################################################################################################
//  Replace()
// #################################################################################################
int AString::SearchAndReplace(  const TString&  needle,
                                const String&   replacement,
                                int             startIdx,
                                int             maxReplacements,
                                Case            sensitivity        )
{
    ALIB_STRING_DBG_CHK(this)

    // check null arguments
    if ( needle.IsEmpty() )
        return 0;

    int nLen=    needle.Length();
    int rLen=    replacement.Length();
    int lenDiff= rLen - nLen;

    // terminate needle
    needle.Terminate();

    // replacement loop
    int cntReplacements=    0;
    int idx= -1;
    while ( cntReplacements < maxReplacements && startIdx < length)
    {
        // search  next occurrence

        if ( ( idx= IndexOf<false>( needle, startIdx, sensitivity ) ) < 0 )
            break;

        // copy rest up or down
        if ( lenDiff != 0 )
        {
            if ( lenDiff > 0 )
                EnsureRemainingCapacity( lenDiff );

            memmove( vbuffer + idx + nLen + lenDiff,
                     vbuffer + idx + nLen,
                     length  - idx - nLen );
            length+= lenDiff;
            Terminate();
        }

        // fill replacement in
        if( rLen > 0 )
            memcpy( vbuffer + idx, replacement.Buffer(), rLen );

        // set start index to first character behind current replacement
        startIdx= idx+ rLen;

        // next
        cntReplacements++;
    }

    // that's it
    return cntReplacements;
}


}}}// namespace aworx::lib::strings
