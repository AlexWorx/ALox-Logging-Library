// #################################################################################################
//  Alox - precompiled headers
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#ifndef _HPP_COM_ALIB_ALIB_PRECOMP
#define _HPP_COM_ALIB_ALIB_PRECOMP


// to check if includes are still rightfully set, uncomment this
// #define  HPP_COM_ALIB_TEST_INCLUDES 1

#if !defined( HPP_COM_ALIB_TEST_INCLUDES )
  // stdlib headers
  #include <iostream>
  #include <cstring>
  #include <vector>
  #include <algorithm>
  #include <map>
  #include <cmath>
#endif

// ALib headers
#include "alib/alib.hpp"

#if !defined( HPP_COM_ALIB_TEST_INCLUDES )
  // additional alib headers
  #include "alib/system/system.hpp"
  #include "alib/time/ticks.hpp"
  #include "alib/threads/thread.hpp"
  #include "alib/threads/threadlock.hpp"
#endif

#endif // _HPP_COM_ALIB_ALIB_PRECOMP
