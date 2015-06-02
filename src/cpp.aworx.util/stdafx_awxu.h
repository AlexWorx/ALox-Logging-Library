// #################################################################################################
//  Alox - precompiled headers
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#ifndef _HPP_COM_AWORX_AWXU_PRECOMP
#define _HPP_COM_AWORX_AWXU_PRECOMP

// GNU/GLIBC specific includes
#if defined( __GNUC__ )

// Windows specific includes
#elif defined ( _MSC_VER )

    // Windows Header Files:
    #include "targetver.h"
    #define WIN32_LEAN_AND_MEAN         // Exclude rarely-used stuff from Windows headers
    #define NOMINMAX                    // Avoid problems with std lib
    #define NOGDI                       // conflict: gdi defines ERROR

    #include <windows.h>
    #include <stdint.h>

#else
    #pragma message ("Uknown Platform in file: " __FILE__ )
#endif


// ALox headers
#include "awxu.hpp"
#include "astring.hpp"
#include "environment.hpp"
#include "thread.hpp"
#include "threadlock.hpp"
#include "ticks.hpp"

// std:: headers
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>


#endif // _HPP_COM_AWORX_AWXU_PRECOMP
