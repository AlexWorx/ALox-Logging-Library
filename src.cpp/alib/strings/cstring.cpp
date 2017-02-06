// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (_GLIBCXX_CCTYPE) && !defined(_CCTYPE_)
    #include <cctype>
#endif

using namespace std;


namespace aworx { namespace lib { namespace strings
{

integer  CString::LengthWhenConvertedToWChar( const char* cs, integer  csLength )
{
    if ( csLength <= 0 )
        return 0;

    //--------- __GLIBCXX__ Version ---------
    #if defined (__GLIBCXX__) || defined(__APPLE__)

        size_t conversionSize=  mbsnrtowcs( nullptr, &cs, static_cast<size_t>(csLength), 0, nullptr );
        if ( conversionSize ==  static_cast<size_t>(-1) )
        {
            ALIB_WARNING( "MBCS to WCS conversion failed. Illegal MBC sequence" );
            return -1;
        }

        ALIB_ASSERT_ERROR( conversionSize <= static_cast<size_t>( csLength ),
                           "MBCS to WCS conversion failed. Conversion length=", conversionSize );

        return static_cast<integer>(conversionSize);

    //--------- Windows Version ----------
    #elif defined( _WIN32 )

        int conversionSize= MultiByteToWideChar( CP_UTF8, NULL, cs, static_cast<int>( csLength ), nullptr, 0 );

        // check for errors
        #if ALIB_DEBUG
            if ( conversionSize == 0 )
            {
                // not enough space?
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
                ALIB_ERROR( "MBCS to WCS conversion failed. Conversion length=", conversionSize );
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

integer CString::IndexOfAny( const char* haystack,  integer  length,
                              const char* needles,   integer  needlesLength,
                              Inclusion inclusion                                )
{
    if ( length        == -1 )    length=        static_cast<integer>( strlen( haystack ) );
    if ( needlesLength == -1 )    needlesLength= static_cast<integer>( strlen( needles  ) );

    const char* end=    haystack + length;

    if ( inclusion == Inclusion::Include )
    {
        const char* s=      haystack;
        while( s != end )
        {
            for( int i= 0; i < needlesLength ; ++i )
                if( *(needles + i) == *s )
                    return s - haystack;
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
                return s - haystack;
        }
    }

    return -1;
}

integer CString::LastIndexOfAny( const char* haystack,  integer startPos,
                                  const char* needles,   integer  needlesLength,
                                  Inclusion   inclusion                                  )
{
    if ( needlesLength == -1 )    needlesLength= static_cast<integer>( strlen( needles  ) );

    const char* s= haystack + startPos;

    if ( inclusion == Inclusion::Include )
    {
        while( s >= haystack )
        {
            ALIB_ASSERT_ERROR( *s != '\0', "AString::LastIndexOfAny(): found '\\0' in source");
            for( int i= 0; i < needlesLength ; ++i )
                if( *(needles + i) == *s )
                    return s - haystack;

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
                    return s - haystack;
            }

            s--;
        }
    }
    return -1;
}

integer CString::IndexOfFirstDifference( const char* haystack,  integer haystackLength,
                                          const char* needle,    integer needleLength,
                                          lang::Case  sensitivity                             )
{
    if ( haystackLength == -1 )    haystackLength= static_cast<integer>( strlen( haystack ) );
    if ( needleLength   == -1 )    needleLength=   static_cast<integer>( strlen( needle   ) );

    integer idx= 0;

    if ( sensitivity == Case::Sensitive )
    {
        while(    idx < haystackLength
               && idx < needleLength
               && haystack[idx] == needle[idx] )
            idx++;
    }
    else
    {
        while(    idx < haystackLength
               && idx < needleLength
               && toupper( haystack[idx] ) == toupper( needle[idx] ) )
            idx++;
    }
    return idx;
}



}}}// namespace aworx::lib::strings
