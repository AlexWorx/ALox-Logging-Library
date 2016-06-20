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

// #################################################################################################
// Constructor/Destructor
// #################################################################################################

Domain::Domain( Domain* parent, const String& name )
: SubDomains()
, Data()
{
    // store parameters
    this->Parent=   parent;
    Name=           name;

    SubDomains.reserve(3);
    Data      .reserve( parent == nullptr ? (size_t) 2 : parent->Data.size() );

    // if we have a parent, we inherit all loggers' verbosities
    if( parent != nullptr )
    {
        Data= parent->Data;
    }

    // assemble the full path once
    const Domain* dom= this;
    do
    {
        if ( dom != this || dom->Parent == nullptr )
            FullPath.InsertAt( "/"      , 0 );
        FullPath.InsertAt( dom->Name, 0 );
        dom= dom->Parent;
    }
    while( dom != nullptr );
}

Domain::~Domain()
{
    for ( Domain* sub : SubDomains )
        delete sub;
    for ( auto& it : PrefixLogables )
        if ( it.first.Type == 0 )
            delete (AString*) it.first.Object;
}

// #################################################################################################
// Methods
// #################################################################################################
Domain* Domain::Find( Substring domainPath, Case sensitivity, int maxCreate, bool* wasCreated )
{
    // set optional output parameter as default to false
    bool dummy;
    if ( wasCreated == nullptr )
        wasCreated= &dummy;
    *wasCreated= false;

    int lenBeforeTrim= domainPath.Length();

    // if string is empty (resp. contains only separator characters), return ourselves
    while ( domainPath.Consume( Domain::Separator() ) )
        ;
    if( domainPath.IsEmpty() )
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
    return startDomain->findRecursive( domainPath, sensitivity, maxCreate, wasCreated );
}

Domain* Domain::findRecursive( Substring& domainPath, Case sensitivity, int maxCreate, bool* wasCreated )
{
    //--- get act sub-name and rest of path
    domainPath.Consume( Domain::Separator() );
    int endSubName= domainPath.IndexOf( Domain::Separator() );

    ALIB_ASSERT_ERROR( endSubName != 0, "Internal Error" );

    // find end of actual domain name and save rest
    Substring restOfDomainPath;
    if ( endSubName > 0 )
        domainPath.Split<false>( endSubName, restOfDomainPath, 1 );

    // search sub-domain
    Domain* subDomain= nullptr;

    // "."
    if( domainPath.Equals( "." ) )
        subDomain= this;

    // ".."
    else if( domainPath.Equals( ".." ) )
        subDomain= Parent != nullptr ? Parent : this;


    // search in sub-domain
    else
    {
        std::vector<Domain*>::iterator subDomainIt;
        bool fixedOnce= false;
        for(;;)
        {
            subDomainIt=  SubDomains.begin();
            while ( subDomainIt != SubDomains.end() )
            {
                int comparison= (*subDomainIt)->Name.CompareTo<false>( domainPath, sensitivity );

                if( comparison >= 0 )
                {
                    if ( comparison == 0 )
                        subDomain=    *subDomainIt;
                    break;
                }
                subDomainIt++;
            }

            // domain found?
            if ( subDomain != nullptr )
                break;

            // try and fix name
            if( !fixedOnce )
            {
                fixedOnce= true;

                bool illegalCharacterFound= false;
                for( int i= 0; i< domainPath.Length() ; ++i )
                {
                    char c= (int) domainPath[i];
                    if (     c <  '-' || c > 'z'
                          || c == '<' || c == '>'
                          || c == '[' || c == ']'
                          || c == '=' || c == '?' || c == ';' || c == ':'
                          || c == '\\'|| c == '\''|| c == '.' || c == ','
                       )
                    {
                        illegalCharacterFound= true;
                        // ohdear: modifying const buffer...but this is definitely from an AString!
                        *(char*) (domainPath.Buffer() + i)= '#';
                    }
                }

                if ( illegalCharacterFound )
                    continue;
             }

            // create
            if ( maxCreate == 0 )
                return nullptr;

            *wasCreated= true;
            subDomainIt= SubDomains.insert( subDomainIt, subDomain= new Domain( this,  domainPath) );
            maxCreate--;
            if ( maxCreate == 0 )
                return *subDomainIt;
            break;
        }
    }

    // recursion?
    return  restOfDomainPath.IsNotEmpty()
            ? subDomain->findRecursive( restOfDomainPath, sensitivity, maxCreate, wasCreated )
            : subDomain;
}

void Domain::ToString( AString& tAString )
{
    tAString << FullPath;
    tAString._('[')._( Format::Int32( CntLogCalls,3 ) )._("] ");

    // get verbosities
    tAString._(" { ");
        for( size_t i= 0; i < Data.size() ; i++ )
        {
            LoggerData& ld= Data[i];
            tAString._(i!=0 ? ", " : "" )
                    ._('(')
                        ._('[')._( Format::Int32(ld.CntLogCalls, 3) )._( "], " );
                        aworx::lox::ToString( ld.LoggerVerbosity, ld.Priority, tAString )
                    ._( ')' );
        }
    tAString._(" }");
}




