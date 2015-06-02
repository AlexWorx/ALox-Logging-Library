// #################################################################################################
//  aworx::util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"

#if !defined (HPP_AWORX_UTIL_ENVIRONMENT)
    #include "environment.hpp"
#endif

#if !defined(_STDIO_H) && !defined(_INC_STDIO)
    #include <stdio.h>  /* defines FILENAME_MAX */
#endif

#if   defined( _MSC_VER )
    #include <direct.h>
    #define GetCurrentDir _getcwd
#elif defined (__GLIBCXX__)
    #include <unistd.h>
    #define GetCurrentDir getcwd
#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif


using namespace std;

namespace aworx {
namespace       util {

// #################################################################################################
// Interface
// #################################################################################################

string Environment::CurrentDirectory()
{
    char charbuf[FILENAME_MAX];

    if ( !GetCurrentDir( charbuf, sizeof(charbuf ) ) )
        return string();
    charbuf[ sizeof(charbuf) - 1 ] = '\0'; // not really required

    return string( charbuf );
}





}}// namespace aworx::util

