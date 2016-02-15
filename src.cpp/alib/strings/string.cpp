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

// Windows.h might bring in max/min macros
#if defined( max )
    #undef max
    #undef min
#endif


namespace aworx {
namespace           lib {
namespace                   strings {



// #################################################################################################
//  globals/statics
// #################################################################################################

#if !defined( IS_DOXYGEN_PARSER )

    ALIB_WARN_ONCE_PER_TYPE_DEFINE( String, SetLengthLonger , true);

    // *********************************************************************************************
    // _alibWarning/Error (we can't use ALib macros in String header, yet)
    // *********************************************************************************************
    #if defined(ALIB_DEBUG)
        void dbgAStringAlibWarning( const char* msg ) { ALIB_WARNING( msg ); }
        void dbgAStringAlibError  ( const char* msg ) { ALIB_ERROR  ( msg ); }
    #endif
#endif // IS_DOXYGEN_PARSER

// *************************************************************************************************
// String::_dbgCheck()
// *************************************************************************************************
#if defined(ALIB_DEBUG_STRINGS) && !defined( IS_DOXYGEN_PARSER )

    #if !defined(ALIB_DEBUG)
        #pragma message "Compiler symbol ALIB_DEBUG_STRINGS_ON set, while ALIB_DEBUG is off. Is this really wanted?"
    #endif

    bool _astringCheckReported= false;

    void String::_dbgCheck() const
    {
        // write to the console once that we are debugging AString
        if ( !_astringCheckReported)
        {
            _astringCheckReported= true;
            ALIB_WARNING( "ALIB_DEBUG_STRINGS is ON! To switch off, "
                          "unset ALIB_DEBUG_STRINGS_ON at compile time." );
        }

        ALIB_ASSERT_ERROR(      length  == 0
                            ||  buffer != nullptr   ,"Not allocated but length >0" );

        for (int aworx_astring_dbg_i= length -1 ; aworx_astring_dbg_i >= 0 ; aworx_astring_dbg_i--)
            if ( buffer[aworx_astring_dbg_i] == '\0' )
            {
                ALIB_ERROR_AS( "Found termination character '\\0' in buffer[" << aworx_astring_dbg_i << "]." );
                break;
            }
    }

#endif



// ####################################################################################################
// Conversion
// ####################################################################################################

int  String::ToWString( wchar_t*  destBuffer,    int  destCapacity,
                    int       regionStart,   int  regionLength        )
const
{
    ALIB_STRING_DBG_CHK(this)
    ALIB_ASSERT_ERROR( destBuffer != nullptr , "Destination buffer is nullptr." );

    if ( AdjustRegion( regionStart, regionLength ) )
        return 0;

    if ( destCapacity < regionLength + 1 )
        return -2;

    //--------- __GLIBCXX__ Version ---------
    #if defined (__GLIBCXX__)

        mbstate_t ps;        memset( &ps, 0, sizeof(mbstate_t) );
        const char* srcp=    buffer + regionStart;
        int conversionSize=  (int)  mbsnrtowcs( destBuffer, &srcp, regionLength, destCapacity, &ps );
        ALIB_ASSERT_WARNING( conversionSize !=  -1, "MBCS to WCS conversion failed. Illegal mb sequence." )
        ALIB_ASSERT_ERROR_AS( srcp == buffer + regionStart + regionLength,
                                   "MBCS to WCS failed. Region length=" << regionLength
                                << ", conversion length=" << ( buffer + regionStart + regionLength - srcp )  )

        // terminate wchar buffer
        if ( conversionSize != -1 )
            *(destBuffer + conversionSize)= L'\0';

        return conversionSize;

    //--------- Windows Version ----------
    #elif defined( _WIN32 )
        int conversionSize= MultiByteToWideChar( CP_UTF8, NULL, buffer + regionStart, regionLength, destBuffer, destCapacity );

        // check for errors
        #if defined( ALIB_DEBUG )
            if ( conversionSize == 0 )
            {
                // not enaugh space?
                int error= GetLastError();

                ALIB_WARNING(
                    ( String128( "MBCS to WCS conversion failed (Error: " )._(
                          ( error == ERROR_INSUFFICIENT_BUFFER      ?  "ERROR_INSUFFICIENT_BUFFER."
                          : error == ERROR_INVALID_FLAGS            ?  "ERROR_INVALID_FLAGS."
                          : error == ERROR_INVALID_PARAMETER        ?  "ERROR_INVALID_PARAMETER"
                          : error == ERROR_NO_UNICODE_TRANSLATION   ?  "ERROR_NO_UNICODE_TRANSLATION"
                                                                    : ( String32()._( error ) ).ToCString() ) )
                        ._( ')' ) ) )

                *destBuffer= L'\0';
                return error == ERROR_INSUFFICIENT_BUFFER ? -2 : 1;
            }

            ALIB_ASSERT_ERROR( conversionSize <= regionLength,
                              String128( "MBCS to WCS conversion failed. Region length=" )._( regionLength )
                                 ._( ", conversion length=" )._(conversionSize)
                            )
        #endif

        // terminate destination buffer
        *(destBuffer + conversionSize)= L'\0';

        return conversionSize;

    #else

        #pragma message ("Unknown Platform in file: " __FILE__ )
        return 0;

    #endif
}

}}}// namespace aworx::lib::strings
