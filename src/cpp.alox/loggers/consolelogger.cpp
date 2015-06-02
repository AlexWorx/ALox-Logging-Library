// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"

#if !defined (HPP_AWORX_UTIL_AWXU)
    #include "awxu.hpp"
#endif

#include "loggers/consolelogger.hpp"

#if !defined (_GLIBCXX_IOSTREAM) && !defined(_IOSTREAM_)
    #include <iostream>
#endif
#if !defined (_STRING_H) && !defined(_INC_STRING)
    #include <string.h>
#endif


using namespace std;
using namespace aworx::util;
using namespace aworx::lox;
using namespace aworx::lox::core;
using namespace aworx::lox::loggers;

// #################################################################################################
// Constructor
// #################################################################################################
ConsoleLogger::ConsoleLogger( const char*  name )
:    TextLogger( name )
{
    // set default domain level to all: As a app console logger/IDE logger we want to fetch all we can
    RootDomain.SetLevel( Log::DomainLevel::ALL, false );
}


// #################################################################################################
// Methods
// #################################################################################################

void ConsoleLogger::doTextLog( const    AString&           ,    Log::Level  ,
                                        AString&        msg,    int         ,
                                        CallerInfo*        ,    int            )
{
    // write to console(s)
    if ( EnableCout )
    {
        cout << msg.Buffer() << endl;                
    }

//  if ( EnableVSDebugConsole )
    #if defined(AWORX_VSTUDIO)
        if ( EnableVSDebugConsole )
        {
            msg.NewLine(); 
            OutputDebugStringA( msg.Buffer() );  
        }
    #endif
}

