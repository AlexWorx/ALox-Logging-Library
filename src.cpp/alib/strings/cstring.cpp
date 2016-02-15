// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/alib.hpp"

#if !defined (_GLIBCXX_CCTYPE) && !defined(_CCTYPE_)
    #include <cctype>
#endif

using namespace std;


namespace aworx {
namespace           lib {
namespace                   strings {


// #################################################################################################
//  String helpers
// #################################################################################################

int  CString::LengthWhenConvertedToWChar( const char* cs, int  csLength )
{
    if ( csLength <= 0 )
        return 0;

    //--------- __GLIBCXX__ Version ---------
    #if defined (__GLIBCXX__)

        size_t conversionSize=  mbsnrtowcs( nullptr, &cs, csLength, 0, nullptr );
        if ( conversionSize ==  (size_t) -1 )
        {
            ALIB_WARNING( "MBCS to WCS conversion failed. Illegal MBC sequence" );
            return -1;
        }

        ALIB_ASSERT_ERROR_AS( conversionSize <= (size_t) csLength,
              "MBCS to WCS conversion failed. Region length=" << csLength
           << ", conversion length=" << conversionSize                    );

        return conversionSize;

    //--------- Windows Version ----------
    #elif defined( _WIN32 )

        int conversionSize= MultiByteToWideChar( CP_UTF8, NULL, cs, csLength, nullptr, 0 );

        // check for errors
        #if defined( ALIB_DEBUG )
            if ( conversionSize == 0 )
            {
                // not enaugh space?
                int error= GetLastError();

                String128 msg( "AString: Conversion to wide character string failed (Error: " );
                     if ( error == ERROR_INSUFFICIENT_BUFFER      ) msg._( "ERROR_INSUFFICIENT_BUFFER."   );
                else if ( error == ERROR_INVALID_FLAGS            ) msg._( "ERROR_INVALID_FLAGS."         );
                else if ( error == ERROR_INVALID_PARAMETER        ) msg._( "ERROR_INVALID_PARAMETER"      );
                else if ( error == ERROR_NO_UNICODE_TRANSLATION   ) msg._( "ERROR_NO_UNICODE_TRANSLATION" );
                else                                                msg._( error );
                msg._(')');

                ALIB_WARNING( msg );
                return -1;
            }

            if( conversionSize > csLength )
            {
                ALIB_ERROR_AS( "MBCS to WCS conversion failed. Region length=" << csLength
                               << ", conversion length=" << conversionSize );
                return -1;
            }
        #endif

        return conversionSize;

    #else

        #pragma message ("Unknown Platform in file: " __FILE__ )
        return 0;

    #endif
}



// #################################################################################################
//  IndexOf
// #################################################################################################

int CString::IndexOfAny( const char* haystack,  int  length,
                         const char* needles,   int  needlesLength,
                         Inclusion inclusion                             )
{
    if ( length        == -1 )    length=        (int) strlen( haystack );
    if ( needlesLength == -1 )    needlesLength= (int) strlen( needles  );

    const char* end=    haystack + length;

    if ( inclusion == Inclusion::Include )
    {
        const char* s=      haystack;
        while( s != end )
        {
            for( int i= 0; i < needlesLength ; ++i )
                if( *(needles + i) == *s )
                    return (int) (s - haystack);
            s++;
        }
    }
    else
    {
        const char* s=   haystack - 1;
        while( ++s != end )
        {
            int i;
            for( i= 0; i < needlesLength ; ++i )
                if( needles[i] == *s )
                    break;
            if ( i == needlesLength )
                return (int) (s - haystack);
        }
    }

    return -1;
}

int CString::LastIndexOfAny( const char* haystack,  int startPos,
                                 const char* needles,   int  needlesLength,
                                 Inclusion   inclusion                                  )
{
    if ( needlesLength == -1 )    needlesLength= (int) strlen( needles  );

    const char* s= haystack + startPos;

    if ( inclusion == Inclusion::Include )
    {
        while( s >= haystack )
        {
            ALIB_ASSERT_ERROR( *s != '\0', "AString::LastIndexOfAny(): found '\\0' in source");
            for( int i= 0; i < needlesLength ; ++i )
                if( *(needles + i) == *s )
                    return (int) (s - haystack);

            s--;
        }
    }
    else
    {
        while( s >= haystack )
        {
            ALIB_ASSERT_ERROR( *s != '\0', "AString::LastIndexOfAny(): found '\\0' in source");
            {
                int i;
                for( i= 0; i < needlesLength ; ++i )
                    if( needles[i] == *s )
                        break;
                if ( i == needlesLength )
                    return (int) (s - haystack);
            }

            s--;
        }
    }
    return -1;
}


}}}// namespace aworx::lib::strings
