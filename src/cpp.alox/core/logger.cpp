// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"
#include "logger.hpp"

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif

using namespace std;
using namespace aworx::util;
using namespace aworx::lox;
using namespace aworx::lox::core;

// #################################################################################################
// Constructor/Destructor
// #################################################################################################

Logger::~Logger()
{

}

// #################################################################################################
// Methods
// #################################################################################################

LogDomain* Logger::CreateDomain( const AString& domainPath )
{
    // add the domain
    AString128 pathUpper( domainPath );
    pathUpper.ConvertCase( true );
    return RootDomain.FindOrCreate( pathUpper, true);
}

LogDomain* Logger::FindDomain( const AString& domainPath )
{
    // add the domain
    AString128 pathUpper( domainPath );
    pathUpper.ConvertCase( true );
    return RootDomain.FindOrCreate( pathUpper, false );
}

void Logger::Line(  const AString&  domain,     Log::Level      level,
                    const void*     msgObject,  int             typeInfo,
                    int             indent,     CallerInfo*     caller)
{
    // do nothing if we are disabled or domain is not active
    if ( IsDisabled )
        return;

    // search domain
    AString128 domUpper( domain );
    domUpper.ConvertCase( true );
    LogDomain* logDomain= RootDomain.FindOrCreate( domUpper, false );

    // not found?
    if ( logDomain == nullptr )
    {
        // add domain with default domain level
        logDomain= CreateDomain( domain );

        // inform the if default is All
        if ( logDomain->GetLevel() == Log::DomainLevel::ALL )
        {
            AString    msg( 128 );
            msg << "Logger '" << Name  << "': log domain '"  << domain << "' not found. Created. Inherited domain level is: All ";
            doLog( domain, Log::Level::VERBOSE, msg.Buffer(), msg.Length(), 0, caller);
        }
    }

    // not active?
    if ( !logDomain->IsActive( level ) )
        return;

    // increase log line counter
    CntLogs++;

    // log the line
    doLog( domain, level, msgObject, typeInfo, indent, caller);

    // get current time    as time of last log (we do this at the end of our log operation!)
    TimeOfLastLog.Set();
}


