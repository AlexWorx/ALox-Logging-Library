// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "logger.hpp"


#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif

using namespace std;
using namespace aworx;
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

bool Logger::Line(  const AString&  domain,     Log::Level      level,
                    const void*     msgObject,  int             typeInfo,
                    int             indent,     CallerInfo*     caller)
{
    // do nothing if we are disabled or domain is not active
    if ( IsDisabled )
        return true;

    bool retVal;
    Domain* domainObject= RootDomain.Find( domain, &retVal );
    if ( !domainObject->IsActive( level ) )
        return !retVal;

    CntLogs++;
    doLog( domain, level, msgObject, typeInfo, indent, caller);
    TimeOfLastLog.Set();
    return !retVal;
}


