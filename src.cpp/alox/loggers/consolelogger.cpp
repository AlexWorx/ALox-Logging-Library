// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

#include "alib/config/configuration.hpp"
#include "alib/strings/tokenizer.hpp"
#include "alib/compatibility/std_iostream.hpp"
#include "alox/loggers/consolelogger.hpp"


using namespace std;
using namespace aworx;
using namespace aworx::lib::enums;
using namespace aworx::lib::strings;
using namespace aworx::lox::loggers;


bool ConsoleLogger::notifyLogOp( Phase phase )
{
    if ( phase == Phase::End )
        cout << endl;
    return true;
}

int ConsoleLogger::doLogSubstring( const AString& buffer, int start, int length )
{
    cout << AS( buffer, start, length );
    return lib::strings::CString::LengthWhenConvertedToWChar( buffer.Buffer() + start, length );
}
