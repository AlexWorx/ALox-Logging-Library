// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"
#include "logdomain.hpp"

#if !defined(_GLIBCXX_IOSTREAM) && !defined(_IOSTREAM_)
    #include <iostream>
#endif

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif


using namespace std;
using namespace aworx::util;
using namespace aworx::lox;
using namespace aworx::lox::core;


// #################################################################################################
// static fields
// #################################################################################################
string            LogDomain::DomainSeparatorChars("\\|/");

// #################################################################################################
// Constructor/Destructor
// #################################################################################################

LogDomain::LogDomain( LogDomain* parent, const AString& name )
{
    // store parameters
    this->Parent=   parent;
    Name=           name;

    // set log level to Off, if we have no parent, else we inherit from parent
    level= ( parent == nullptr )    ?  Log::DomainLevel::OFF
                                    :  Log::DomainLevel::INHERIT;
}

LogDomain::~LogDomain()
{
    for ( LogDomain* sub : SubDomains )
        delete sub;
}

// #################################################################################################
// Methods
// #################################################################################################

Log::DomainLevel LogDomain::GetLevel()
{
    // recursively find a defined level
    LogDomain*       parent=  this->Parent;
    Log::DomainLevel level=   this->level;
    while (level == Log::DomainLevel::INHERIT && parent != nullptr )
    {
        level=   parent->level;
        parent=  parent->Parent;
    }

    // return result
    return level;
}

// #################################################################################################
// Methods
// #################################################################################################
void LogDomain::SetLevel( Log::DomainLevel level, bool recursive )
{
    // set it for myself (only if I am not root domain)
    this->level= level;

    // recursively set level for sub domains
    if ( recursive )
        for ( LogDomain* domain : SubDomains )
            domain->SetLevel ( level, true );
}

bool LogDomain::IsActive( Log::Level level )
{
    Log::DomainLevel domainLevel= GetLevel();

    AWXU_ASSERT ( domainLevel != Log::DomainLevel::INHERIT );

    //    Level / DomainLevel        |   Verbose  Info     Warning     Error
    //  ---------------------------------------------------------------------
    //    Off                        |     -        -        -           -
    //    Errors                     |     -        -        -           Y
    //    WarningsAndErrors          |     -        -        Y           Y
    //    InfoWarningsAndErrors      |     -        Y        Y           Y
    //    All                        |     Y        Y        Y           Y
    return        ( domainLevel == Log::DomainLevel::ERRORS                     &&        level == Log::Level::ERROR   )
            ||    ( domainLevel == Log::DomainLevel::WARNINGS_AND_ERRORS        &&    (   level == Log::Level::WARNING || level == Log::Level::ERROR ) )
            ||    ( domainLevel == Log::DomainLevel::INFO_WARNINGS_AND_ERRORS   &&        level != Log::Level::VERBOSE )
            ||      domainLevel == Log::DomainLevel::ALL;
}

LogDomain* LogDomain::FindOrCreate( const AString& domainPath, bool createIfNotExistant)
{
    // check if given domain path starts with domain separators
    int startIdx= 0;
    int len=    domainPath.Length();
    {
        const char*    domainPathBuffer=    domainPath.Buffer();
        while (startIdx < len && ( DomainSeparatorChars.find( domainPathBuffer[ startIdx ] ) != string::npos ) )
            startIdx++;
    }

    // if string is empty (resp. contains only separator characters), return ourselves
    if ( startIdx == len )
        return this;

    // Trailing domain separator found: call find on root domain
    LogDomain* ld= this;
    if ( startIdx > 0 )
    {
        while (ld->Parent != nullptr )
            ld= ld->Parent;
    }

    // call find
    return ld->findOrCreateInternal( domainPath, startIdx, createIfNotExistant );
}

LogDomain* LogDomain::findOrCreateInternal( const AString& domainPath, int dpStartIdx, bool createIfNotExistant)
{
    //--- get act sub-name and rest of path
    int dsLen=    domainPath.Length();
    int pEnd;
    int pNext;
    {
        const char*    domainPathBuffer=    domainPath.Buffer();

        // adjust start pos (remove trailing "/")
        while (dpStartIdx < dsLen && ( DomainSeparatorChars.find( domainPathBuffer[ dpStartIdx ] ) != string::npos ) )
            dpStartIdx++;

        // find end of act name
        pEnd= dpStartIdx + 1;
        while (pEnd < dsLen &&   ( DomainSeparatorChars.find( domainPathBuffer[ pEnd ] ) == string::npos ) )
            pEnd++;

        // check
        if ( dpStartIdx >= dsLen )
        {
            // we can not even create a domain
            return nullptr;
        }

        // find start of rest, mark as negative pos if empty
        pNext= pEnd + 1;
        while (pNext < dsLen &&  ( DomainSeparatorChars.find( domainPathBuffer[ pNext ] ) != string::npos ) )
            pNext++;

        if ( pNext >= dsLen )
            pNext= -1;
    }

    // search act domain
    int  comparison=   -1;
    auto subDomainIt=  SubDomains.begin();
    while ( subDomainIt != SubDomains.end() )
    {
        comparison= (*subDomainIt)->Name.CompareTo( domainPath, false, dpStartIdx, pEnd - dpStartIdx );

        if( comparison >= 0 )
            break;

        subDomainIt++;
    }

    // domain not found
    if ( comparison != 0 )
    {
        // return nullptr if we are not asked to create
        if ( !createIfNotExistant )
            return nullptr;

        // create domain
        subDomainIt= SubDomains.insert( subDomainIt, new LogDomain( this, AString( domainPath, dpStartIdx, pEnd-dpStartIdx ) ) );
    }

    // recursion?
    if ( pNext > 0 )
        return (*subDomainIt)->findOrCreateInternal( domainPath, pNext, createIfNotExistant );

    // that's it
    return *subDomainIt;
}




