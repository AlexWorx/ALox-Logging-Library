// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"

#if !defined (HPP_AWORX_LIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif


using namespace std;

namespace aworx {
namespace           lib {
namespace                   strings {


// #################################################################################################
// Wide Characters
// #################################################################################################

template<>  int ApplyTo( AString& target, const wchar_t* src)
{
    int srcLength= -1;
    ALIB_STRING_DBG_CHK( &target )

    if ( src == nullptr )
        srcLength= 0;

    if ( srcLength < 0 )
        srcLength= (int) wcslen( src );

    if ( srcLength == 0 )
    {
        return 0;
    }

    //--------- __GLIBCXX__ Version ---------
    #if defined (__GLIBCXX__)

        // get conversion size
        size_t conversionSize;

        mbstate_t ps;
        memset( &ps, 0, sizeof(mbstate_t) );
        const wchar_t* srcp= src;
        conversionSize=  wcsnrtombs( nullptr, &srcp, srcLength, 0,  &ps);

        if ( conversionSize == (size_t) -1 )
        {
            ALIB_WARNING( "Cannot convert WCS to MBCS." );
            return 0;
        }

        if ( conversionSize < 1 )
        {
            ALIB_ERROR( "Error converting WCS to MBCS." );
            return 0;
        }

        // check capacity
        target.EnsureRemainingCapacity( (int) conversionSize );
        memset( &ps, 0, sizeof(mbstate_t) );
        srcp= src;
        wcsnrtombs( target.VBuffer() + target.Length(), &srcp, srcLength, conversionSize,  &ps);

        target.SetLength<false>( target.Length() + conversionSize );

        return conversionSize;


    //--------- Windows Version ---------
    #elif defined( _WIN32 )

        // loop until reserved size is big enough
        int     length= target.Length();
        target.EnsureRemainingCapacity( srcLength * 2 );
        char*   buffer= target.VBuffer();

        for(;;)
        {
            int conversionSize= WideCharToMultiByte( CP_UTF8, NULL, src, srcLength,  buffer + length, target.Capacity() - length , NULL, NULL );
            if ( conversionSize > 0 )
            {
                target.SetLength<false>( length + conversionSize );
                return length;
            }

            // not enaugh space?
            int error= GetLastError();
            if (error == ERROR_INSUFFICIENT_BUFFER )
            {
                target.EnsureRemainingCapacity( srcLength );
                buffer= target.VBuffer();
                continue;
            }

            // quit on other errors
            ALIB_WARNING_AS(
                     "AString: Cannot convert wide character string to UTF-8. (Error: "
                      << ( error == ERROR_INVALID_FLAGS          ? "ERROR_INVALID_FLAGS."
                        :  error == ERROR_INVALID_PARAMETER      ? "ERROR_INVALID_PARAMETER"
                        :  error == ERROR_NO_UNICODE_TRANSLATION ? "ERROR_NO_UNICODE_TRANSLATION"
                                                                 : (String32()._( error )).ToCString())
                    << ')'   )

            return 0;
        }

    #else
        #pragma message ("Unknown Platform in file: " __FILE__ )
        return 0;
    #endif
}


}}}// namespace aworx::lib::strings
