// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "domain.hpp"

#if !defined (HPP_ALIB_STRINGS_ASSUBSTRING)
    #include "alib/strings/substring.hpp"
#endif

#if !defined(_GLIBCXX_IOSTREAM) && !defined(_IOSTREAM_)
    #include <iostream>
#endif

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif


using namespace aworx;
using namespace aworx::lox::core;


// #################################################################################################
// static fields
// #################################################################################################
TString            Domain::DomainSeparatorChars("\\|/");

// #################################################################################################
// Constructor/Destructor
// #################################################################################################

Domain::Domain( Domain* parent, const String& name )
{
    // store parameters
    this->Parent=   parent;
    Name=           name;

    // set log level to Off, if we have no parent, else we inherit from parent
    level= ( parent == nullptr )    ?  Log::DomainLevel::Off
                                    :  Log::DomainLevel::Inherit;
}

Domain::~Domain()
{
    for ( Domain* sub : SubDomains )
        delete sub;
}

// #################################################################################################
// Methods
// #################################################################################################

Log::DomainLevel Domain::GetLevel()
{
    // recursively find a defined level
    Domain*       parent=  this->Parent;
    Log::DomainLevel level=   this->level;
    while (level == Log::DomainLevel::Inherit && parent != nullptr )
    {
        level=   parent->level;
        parent=  parent->Parent;
    }

    ALIB_ASSERT_ERROR( level != Log::DomainLevel::Inherit, "Root domain level must not be DomainLevel::Inherit" );

    // return result
    return level;
}

// #################################################################################################
// Methods
// #################################################################################################
void Domain::SetLevel( Log::DomainLevel level, Propagation propagation )
{
    // set it for myself
    if ( Parent != nullptr || level != Log::DomainLevel::Inherit )
        this->level= level;

    // recursively set level for sub domains
    if ( propagation == Propagation::ToDescendants )
        for ( Domain* domain : SubDomains )
            domain->SetLevel ( level, Propagation::ToDescendants );
}

bool Domain::IsActive( Log::Level level )
{
    Log::DomainLevel domainLevel= GetLevel();

    ALIB_ASSERT ( domainLevel != Log::DomainLevel::Inherit );

    //    Level / DomainLevel        |   Verbose  Info     Warning     Error
    //  ---------------------------------------------------------------------
    //    Off                        |     -        -        -           -
    //    Errors                     |     -        -        -           Y
    //    WarningsAndErrors          |     -        -        Y           Y
    //    InfoWarningsAndErrors      |     -        Y        Y           Y
    //    All                        |     Y        Y        Y           Y
    return        ( domainLevel == Log::DomainLevel::Errors                   &&        level == Log::Level::Error   )
            ||    ( domainLevel == Log::DomainLevel::WarningsAndErrors        &&    (   level == Log::Level::Warning || level == Log::Level::Error ) )
            ||    ( domainLevel == Log::DomainLevel::InfoWarningsAndErrors    &&        level != Log::Level::Verbose )
            ||      domainLevel == Log::DomainLevel::All;
}

Domain* Domain::Find( Substring domainPath, bool* wasCreated )
{
    // set optional output parameter as default to false
    if ( wasCreated != nullptr )
        *wasCreated= false;

    int lenBeforeTrim= domainPath.Length();

    // if string is empty (resp. contains only separator characters), return ourselves
    if( domainPath.TrimStart( DomainSeparatorChars ) )
    {
        return this;
    }

    // Trailing domain separator found: call find on root domain
    Domain* startDomain= this;
    if ( lenBeforeTrim > domainPath.Length() )
    {
        while (startDomain->Parent != nullptr )
            startDomain= startDomain->Parent;
    }

    // call find
    return startDomain->findRecursive( domainPath, wasCreated );
}

Domain* Domain::findRecursive( Substring& domainPath, bool* wasCreated )
{
    // invariant: domainPath is never empty (might be just path separators though)

    //--- get act sub-name and rest of path
    domainPath.TrimStart( DomainSeparatorChars );
    int endSubName= domainPath.IndexOfAny( DomainSeparatorChars, Inclusion::Include );

    ALIB_ASSERT_ERROR( endSubName != 0, "Internal Error" );

    // find start of rest, mark as negative pos if empty

    Substring restOfDomainPath;
    if ( endSubName > 0 )
        domainPath.Split<false>( endSubName, restOfDomainPath, 1 );

    // search act domain
    int  comparison=   -1;
    auto subDomainIt=  SubDomains.begin();
    while ( subDomainIt != SubDomains.end() )
    {
        comparison= (*subDomainIt)->Name.CompareTo<false>( domainPath, Case::Sensitive );

        if( comparison >= 0 )
            break;

        subDomainIt++;
    }

    // domain not found? then create.
    if ( comparison != 0 )
    {
        subDomainIt= SubDomains.insert( subDomainIt, new Domain( this,  domainPath) );
        if ( wasCreated != nullptr )
            *wasCreated= true;
    }

    // recursion?
    if ( restOfDomainPath.IsNotEmpty() )
        return (*subDomainIt)->findRecursive( restOfDomainPath, wasCreated );

    // that's it
    return *subDomainIt;
}




