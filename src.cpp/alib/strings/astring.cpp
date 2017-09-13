// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if defined(_MSC_VER)
    #include <algorithm>
#endif


namespace aworx { namespace lib { namespace strings
{
// #################################################################################################
//  globals
// #################################################################################################

//! @cond NO_DOX
ALIB_DEBUG_CODE( void appendErrorToAString( AString& target ) { target._("T_Apply<Unknown Type>");} )
//! @endcond NO_DOX

// *************************************************************************************************
// AString::_dbgCheck()
// *************************************************************************************************
//! @cond NO_DOX
#if ALIB_DEBUG_STRINGS

    #if !ALIB_DEBUG
        #pragma message "Compiler symbol ALIB_DEBUG_STRINGS_ON set, while ALIB_DEBUG is off. Is this really wanted?"
    #endif

    void AString::_dbgCheck() const
    {
        TString::_dbgCheck();
        integer cap= Capacity();

        ALIB_ASSERT_ERROR(      buffer != nullptr
                                ||  length  == 0
                                ,"No buffer but length != 0" );

        ALIB_ASSERT_ERROR(      cap      == 0
                                ||  debugIsTerminated != 0
                                ||  buffer[length]   == '\1'
                                ,"Not terminated but dbg-terminator char '\\1' not present" );

        ALIB_ASSERT_ERROR(      debugLastAllocRequest == 0
                                ||  length <= debugLastAllocRequest
                                ,"Error: Previous allocation request was too short"         );

        ALIB_ASSERT_ERROR(      length <= cap
                                ,"Error: Length greater than allocation size"               );

        if( buffer && debugBufferWithMagicBytePadding )
        {
            for (integer aworx_astring_dbg_i= -16 ; aworx_astring_dbg_i < 0 ; aworx_astring_dbg_i++)
                if ( buffer[aworx_astring_dbg_i] != 2 )
                {
                    ALIB_ERROR( "Magic byte not found at start of buffer." );
                    break;
                }
            for (integer aworx_astring_dbg_i= 1 ; aworx_astring_dbg_i <= 16 ; aworx_astring_dbg_i++)
                if ( buffer[ cap + aworx_astring_dbg_i] != 3 )
                {
                    ALIB_ERROR( "Magic byte not found at end of buffer." );
                    break;
                }
        }
    }

#endif
//! @endcond NO_DOX



// ####################################################################################################
// Allocation
// ####################################################################################################

void AString::SetBuffer( integer newCapacity )
{
    ALIB_STRING_DBG_CHK(this)

    ALIB_ASSERT( newCapacity >= 0 );

    // do nothing if life-cycle is managed by us and same size,
    if ( capacity >= 0 && capacity == newCapacity )
        return;

    #if ALIB_DEBUG_STRINGS
        debugLastAllocRequest= newCapacity;
    #endif

    // set uninitialized
    if ( newCapacity == 0 )
    {
        if ( capacity > 0 )
            #if !ALIB_DEBUG_STRINGS
                delete[] buffer;
            #else
                delete[] (buffer - (debugBufferWithMagicBytePadding ? 16 : 0) );
            #endif

        capacity=
        length=     0;
        buffer=     nullptr;
        return;
    }

    ALIB_WARN_ONCE_IF( *this, ReplaceExternalBuffer, capacity < 0,
                      "AString::SetAllocation(): replacing an external buffer. This may not be wanted." )

    // create new Buffer
    #if !ALIB_DEBUG_STRINGS
        char* newBuffer=    new char[ newCapacity  + 1 ];
    #else
        // add 16 bytes of padding at start/end
        char* newBuffer=    new char[ newCapacity  + 1 + 32 ] + 16;

        // write 2 to start, 3 to end (0= termination byte, 1= untermination byte )
        memset( newBuffer - 16,              2, 16 );
        memset( newBuffer + newCapacity + 1, 3, 16 );
    #endif

    // if we had a buffer before
    if ( capacity != 0 )
    {
        // copy data and delete old buffer
        memcpy( newBuffer, buffer, static_cast<size_t>((std::min)( length + 1, newCapacity + 1)) );
        if ( capacity > 0 )
          #if !ALIB_DEBUG_STRINGS
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
    #if ALIB_DEBUG_STRINGS
        debugBufferWithMagicBytePadding= true;
    #endif
}



void AString::SetBuffer( char* extBuffer, integer extBufferSize, integer extLength,
                         Responsibility responsibility  )
{
    ALIB_ASSERT_ERROR(       !(extBufferSize == 0 && extBuffer != nullptr)
                           &&    !(extBufferSize != 0 && extBuffer == nullptr) ,
                      "AString::SetBuffer(): Given buffer is nullptr while given alloc size is not 0 (or vice versa)" );

    // delete any existing
    if ( capacity > 0 )
        #if !ALIB_DEBUG_STRINGS
            delete[] buffer;
        #else
            delete[] (buffer - (debugBufferWithMagicBytePadding ? 16 : 0) );
        #endif

    #if ALIB_DEBUG_STRINGS
        debugBufferWithMagicBytePadding= false;
    #endif

    // too small? treat as if a nullptr was given.
    if ( extBufferSize < 1 )
    {
        ALIB_ERROR( "allocation size < 1" );
        extBuffer= nullptr;
    }

    // null buffer?
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
AString& AString::Append( const wchar_t* src, integer srcLength )
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
    #if defined (__GLIBCXX__) || defined(__APPLE__)

        integer maxConversionSize= static_cast<integer>(MB_CUR_MAX) * srcLength;
        mbstate_t ps;
        EnsureRemainingCapacity( maxConversionSize );
        memset( &ps, 0, sizeof(mbstate_t) );
        const wchar_t* srcp= src;
        size_t conversionSize= wcsnrtombs( vbuffer + length, &srcp, static_cast<size_t>(srcLength), static_cast<size_t>(maxConversionSize),  &ps);
        if ( conversionSize == static_cast<size_t>( -1 ) )
        {
            ALIB_WARNING( "Cannot convert WCS to MBCS." );
            return *this;
        }

        if ( conversionSize < 1 )
        {
            ALIB_ERROR( "Error converting WCS to MBCS." );
            return *this;
        }

        SetLength<false>( length + static_cast<integer>(conversionSize) );
        return *this;

    //--------- Windows Version ---------
    #elif defined( _WIN32 )

        // loop until reserved size is big enough
        EnsureRemainingCapacity( srcLength * 2 );
        for(;;)
        {
            int conversionSize= WideCharToMultiByte( CP_UTF8, NULL,
                                                     src, static_cast<int>( srcLength),
                                                     vbuffer + length, static_cast<int>( Capacity() - length ),
                                                     NULL, NULL );
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
            ALIB_WARNING(
                     "AString: Cannot convert wide character string to UTF-8. Error: ",
                        ( error == ERROR_INVALID_FLAGS          ? "ERROR_INVALID_FLAGS."
                        :  error == ERROR_INVALID_PARAMETER      ? "ERROR_INVALID_PARAMETER"
                        :  error == ERROR_NO_UNICODE_TRANSLATION ? "ERROR_NO_UNICODE_TRANSLATION"
                                                                 : (String32()._( error )).ToCString())
                    )

            return *this;
        }

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
        return *this;
    #endif
}


#if ALIB_SIZEOF_WCHAR_T == 4

    AString& AString::Append( const char16_t* src, integer srcLength )
    {
        // already checked, but who knows..
        static_assert( sizeof(char16_t) != sizeof(wchar_t), "Error: Mismatch in code selection symbols." );

        // if possible, use a local buffer of fixed size
        wchar_t stackBuffer[2048];
        wchar_t* buffer;
        buffer= ( srcLength > 2048 ) ?  new wchar_t[srcLength]
                                     :  reinterpret_cast<wchar_t*>( &stackBuffer );

        // copy data and invoke wchar_t version
        for(integer i= 0; i < srcLength; ++i )
            buffer[ i ]= src[i];
        Append( buffer, srcLength );


        if( srcLength > 2048 )
            delete buffer;

        return *this;
    }

#else

    AString& AString::Append( const char32_t* src, integer srcLength )
    {
        // already checked, but who knows..
        static_assert( sizeof(char32_t) != sizeof(wchar_t), "Error: Mismatch in code selection symbols." );

        // if possible, use a local buffer of fixed size
        wchar_t stackBuffer[2048];
        wchar_t* buffer;
        buffer= ( srcLength > 2048 ) ?  new wchar_t[srcLength]
                                     :  reinterpret_cast<wchar_t*>( &stackBuffer );

        // copy data and invoke wchar_t version
        for(integer i= 0; i < srcLength; ++i )
            buffer[ i ]= static_cast<wchar_t>( src[i] );
        Append( buffer, srcLength );


        if( srcLength > 2048 )
            delete buffer;

        return *this;
    }

#endif
// #############################################################################################
// Trim
// #############################################################################################

integer AString::TrimAt( integer idx, const TString& trimChars )
{
    if ( idx < 0 )
         return 0;
    if ( idx >= length )
         return length;

    integer regionStart=  LastIndexOfAny<false>( trimChars, Inclusion::Exclude, idx ) + 1;
    if (regionStart < 0 )
        regionStart= 0;

    integer regionEnd=    IndexOfAny    <false>( trimChars, Inclusion::Exclude, idx );
    if (regionEnd < 0 )
        regionEnd= length;

    integer regionLength= regionEnd - regionStart;
    if ( regionLength > 0 )
        Delete<false>( regionStart, regionLength );

    return regionStart;
}

AString& AString::Trim( const TString& trimChars )
{
    // check
    if (length == 0 || trimChars.IsEmpty() )
        return *this;

    // trim end
    integer idx= LastIndexOfAny<false>( trimChars, Inclusion::Exclude, length - 1 ) + 1;
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
integer AString::SearchAndReplace(  char       needle,
                                    char       replacement,
                                    integer    startIdx        )
{
    ALIB_STRING_DBG_CHK(this)
         if ( startIdx < 0  )       startIdx= 0;
    else if ( startIdx >= length )  return 0;

    // replacement loop
    integer cntReplacements=    0;
    for(;;)
    {
        startIdx= IndexOfOrLength<false>( needle, startIdx  );
        if ( startIdx >= length  )
            return cntReplacements;
        vbuffer[ startIdx ]= replacement;
        cntReplacements++;
    }
}

integer AString::SearchAndReplace(  const TString&  needle,
                                    const String&   replacement,
                                    integer         startIdx,
                                    integer         maxReplacements,
                                    Case            sensitivity        )
{
    ALIB_STRING_DBG_CHK(this)

    // check null arguments
    if ( needle.IsEmpty() )
        return 0;

    integer nLen=    needle.Length();
    integer rLen=    replacement.Length();
    integer lenDiff= rLen - nLen;

    // terminate needle
    needle.Terminate();

    // replacement loop
    integer cntReplacements=    0;
    while ( cntReplacements < maxReplacements && startIdx < length)
    {
        // search  next occurrence
        ALIB_STRING_DBG_UNTERMINATE(*this, 0);
        integer    idx= IndexOf<false>( needle, startIdx, sensitivity );
        if ( idx < 0 )
            break;

        // copy rest up or down
        if ( lenDiff != 0 )
        {
            if ( lenDiff > 0 )
                EnsureRemainingCapacity( lenDiff );

            memmove( vbuffer + idx + nLen + lenDiff,
                     vbuffer + idx + nLen,
                     static_cast<size_t>(length  - idx - nLen) );
            length+= lenDiff;
            ALIB_STRING_DBG_UNTERMINATE(*this, 0);
        }

        // fill replacement in
        if( rLen > 0 )
            memcpy( vbuffer + idx, replacement.Buffer(), static_cast<size_t>(rLen) );

        // set start index to first character behind current replacement
        startIdx= idx + rLen;

        // next
        cntReplacements++;
    }


    // that's it
    return cntReplacements;
}

} // aworx::lib[::strings]

#if ALIB_DEBUG
    namespace debug {

    AString&  RemoveALibNamespaces( AString& target, bool remove )
    {
        if( remove )
        {
            target.SearchAndReplace("aworx::lib::lang::"               , "" );
            target.SearchAndReplace("aworx::lib::boxing::ftypes::"     , "" );
            target.SearchAndReplace("aworx::lib::boxing::"             , "" );
            target.SearchAndReplace("aworx::lib::strings::boxing::"    , "" );
            target.SearchAndReplace("aworx::lib::strings::util::"      , "" );
            target.SearchAndReplace("aworx::lib::strings::format::"    , "" );
            target.SearchAndReplace("aworx::lib::strings::"            , "" );
            target.SearchAndReplace("aworx::lib::threads::"            , "" );
            target.SearchAndReplace("aworx::lib::system::"             , "" );
            target.SearchAndReplace("aworx::lib::config::"             , "" );
            target.SearchAndReplace("aworx::lib::time::"               , "" );
            target.SearchAndReplace("aworx::lib::containers::"         , "" );

            ALIB_ASSERT_ERROR( target.IndexOf("aworx::lib") < 0,
                               "Not all namespaces were fetched"    );

            target.SearchAndReplace("aworx::lox::"                     , "" );
        }
        return target;
    }

    #if ALIB_FEAT_SINGLETON_MAPPED
        int GetSingletons( strings::AString& target )
        {
            auto types= GetSingletons();
            for( auto it : types )
                target << it.first <<  " = 0x" << Format::Hex(reinterpret_cast<uint64_t>(it.second) ) << NewLine;

            return static_cast<int>( types.size() );
        }
    #endif
    }
#endif

}}// namespace [aworx::lib]
