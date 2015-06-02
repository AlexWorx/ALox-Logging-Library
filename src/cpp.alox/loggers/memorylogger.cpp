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

#include "loggers/memorylogger.hpp"

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
MemoryLogger::MemoryLogger( const char* name )
:    TextLogger( name )
,    Buffer(256)
{
    // set default domain level to all: As a app console logger/IDE logger we want to fetch all we can
    RootDomain.SetLevel( Log::DomainLevel::ALL, false );
}


// #################################################################################################
// Methods
// #################################################################################################

void MemoryLogger::doTextLog( const    AString&        ,            Log::Level    ,
                                        AString&        msg,        int            ,
                                        CallerInfo*        ,            int            )
{
    // append new line if buffer has already lines stored
    if ( Buffer.Length() > 0 )
        Buffer.NewLine();

    // append message
    Buffer.Append( msg );
}

