﻿// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
#   include "alib/config/configuration.hpp"
#endif


#if !defined(HPP_ALIB_COMPATIBILITY_STD_IOSTREAM)
#   include "alib/compatibility/std_iostream.hpp"
#endif
#if !defined(HPP_ALOX_CONSOLE_LOGGER)
#   include "alox/loggers/consolelogger.hpp"
#endif


using namespace std;
using namespace aworx;

bool ConsoleLogger::notifyLogOp( Phase phase )
{
    if ( phase == Phase::End )
        cout << endl;
    return true;
}

aworx::integer ConsoleLogger::logSubstring( const String& buffer, integer start, integer length )
{
    cout << String( buffer, start, length );
    return lib::strings::CString::LengthWhenConvertedToWChar( buffer.Buffer() + start, length );
}
