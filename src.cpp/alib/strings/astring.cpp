// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"


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
                    ALIB_ERROR_S512( "Magic byte not found at start (buffer[" << aworx_astring_dbg_i << "])." );
                    break;
                }
            for (int aworx_astring_dbg_i= 1 ; aworx_astring_dbg_i <= 16 ; aworx_astring_dbg_i++)
                if ( buffer[ capacity + aworx_astring_dbg_i] != 3 )
                {
                    ALIB_ERROR_S512( "Magic byte not found at end (buffer[" << capacity + aworx_astring_dbg_i << "])." );
                    break;
                }
        }
    }

#endif



// ####################################################################################################
// Allocation
// ####################################################################################################

void AString::SetBuffer( int newCapacity )
{
    ALIB_STRING_DBG_CHK(this)

    ALIB_ASSERT( newCapacity >= 0 );

    // do nothing if life-cycle is managed by us and same size,
    if ( capacity >= 0 && capacity == newCapacity )
        return;

    #if defined(ALIB_DEBUG_STRINGS)
        debugLastAllocRequest= newSize;
    #endif

    // set uninitialized
    if ( newCapacity == 0 )
    {
        if ( capacity > 0 )
            #if !defined(ALIB_DEBUG_STRINGS)
                delete[] buffer;
            #else
                delete[] (buffer - (debugBufferWithMagicBytePadding ? 16 : 0) );
            #endif

        capacity=
        length=     0;
        buffer=     nullptr;
        return;
    }

    ALIB_WARN_ONCE_IF( capacity < 0,
                      "AString::SetAllocation(): replacing an external buffer. This may not be wanted.",
                      *this, ReplaceExternalBuffer )

    // create new Buffer
    #if !defined(ALIB_DEBUG_STRINGS)
        char* newBuffer=    new char[ newCapacity  + 1 ];
    #else
        // add 16 bytes of padding at start/end
        char* newBuffer=    new char[ newSize  + 1 + 32 ] + 16;

        // write 2 to start, 3 to end (0= termination byte, 1= untermination byte )
        memset( newBuffer - 16,          (char) 2, 16 );
        memset( newBuffer + newSize + 1, (char) 3, 16 );
    #endif

    // if we had a buffer before
    if ( capacity != 0 )
    {
        // copy data and delete old buffer
        memcpy( newBuffer, buffer, min( length + 1, newCapacity + 1) );
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
    capacity=   newCapacity;
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
// Append wchar_t strings
// #################################################################################################
AString& AString::Append( const wchar_t* src, int srcLength )
{
    ALIB_STRING_DBG_CHK( this )

    if ( src == nullptr ||  srcLength <= 0 )
    {
        if ( IsNull() )
        {
            // special treatment if currently nothing is allocated and a blank string ("") is added:
            // we allocate, which means, we are not a nulled object anymore!
            // (...also, in this case we check the src parameter)
            SetBuffer( 15 );
            ALIB_STRING_DBG_UNTERMINATE(*this, 0);
        }

        return *this;
    }

    //--------- __GLIBCXX__ Version ---------
    #if defined (__GLIBCXX__)

        int maxConversionSize= MB_CUR_MAX * srcLength;
        mbstate_t ps;
        EnsureRemainingCapacity( maxConversionSize );
        memset( &ps, 0, sizeof(mbstate_t) );
        const wchar_t* srcp= src;
        size_t conversionSize= wcsnrtombs( vbuffer + length, &srcp, srcLength, maxConversionSize,  &ps);
        if ( conversionSize == (size_t) -1 )
        {
            ALIB_WARNING( "Cannot convert WCS to MBCS." );
            return *this;
        }

        if ( conversionSize < 1 )
        {
            ALIB_ERROR( "Error converting WCS to MBCS." );
            return *this;
        }

        SetLength<false>( length + conversionSize );
        return *this;

    //--------- Windows Version ---------
    #elif defined( _WIN32 )

        // loop until reserved size is big enough
        EnsureRemainingCapacity( srcLength * 2 );
        for(;;)
        {
            int conversionSize= WideCharToMultiByte( CP_UTF8, NULL, src, srcLength,  vbuffer + length, Capacity() - length , NULL, NULL );
            if ( conversionSize > 0 )
            {
                SetLength<false>( length + conversionSize );
                return *this;
            }

            // not enough space?
            int error= GetLastError();
            if (error == ERROR_INSUFFICIENT_BUFFER )
            {
                EnsureRemainingCapacity( srcLength );
                continue;
            }

            // quit on other errors
            ALIB_WARNING_S512(
                     "AString: Cannot convert wide character string to UTF-8. (Error: "
                      << ( error == ERROR_INVALID_FLAGS          ? "ERROR_INVALID_FLAGS."
                        :  error == ERROR_INVALID_PARAMETER      ? "ERROR_INVALID_PARAMETER"
                        :  error == ERROR_NO_UNICODE_TRANSLATION ? "ERROR_NO_UNICODE_TRANSLATION"
                                                                 : (String32()._( error )).ToCString())
                    << ')'   )

            return *this;
        }

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
        return *this;
    #endif
}




// #############################################################################################
// Trim
// #############################################################################################

int AString::TrimAt( int index, const TString& trimChars )
{
    if ( index < 0 || index >= length || trimChars.IsEmpty() )
         return length;

    int regionStart= LastIndexOfAny<false>( trimChars, Inclusion::Exclude, index ) + 1;
    int idx=         IndexOfAny    <false>( trimChars, Inclusion::Exclude, index );
    int regionEnd=   idx >=0 ? idx
                             : length;
    int regionLength= regionEnd - regionStart;
    if ( regionLength > 0 )
    {
        Delete<false>( regionStart, regionLength );
        return regionStart;
    }

    return index;
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
