// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "scopeinfo.hpp"
#include <iostream>

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif
#if !defined (HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif

// conditional expression is constant (which is a great thing for the compiler by the way ;-)
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4127 )
#endif

using namespace std;
namespace aworx {
    namespace lox   {
        namespace core   {



// #################################################################################################
// Static
// #################################################################################################

std::vector<ScopeInfo::SourcePathTrimRule>  ScopeInfo::GlobalSPTRs;
int                                         ScopeInfo::DefaultCacheSize                         = 5;

bool                                        ScopeInfo::GlobalSPTRsReadFromConfig       = false;

ScopeInfo::ScopeInfo( const TString& name, const std::map<int, String32>&  threadDictionary )
: loxName( name )
, threadDictionary(threadDictionary)
{
    loxName.ToUpper();
    ALIB_ASSERT_ERROR( !loxName.Equals( "GLOBAL" ), "Name \"GLOBAL\" not allowed for Lox instances" );
    cache= new SourceFile[cacheSize= DefaultCacheSize];
    actual= &cache[0];

    // read trim rules from config
    // do 2 times, 0== local list, 1== global list
    std::vector<SourcePathTrimRule>* trimInfoList;
    for( int trimInfoNo= 0; trimInfoNo < 2 ; trimInfoNo++ )
    {
        String64 variableName;;
        // check if done... or set list
        if ( trimInfoNo == 0 )
        {
            trimInfoList= &LocalSPTRs;
            variableName._( loxName );
        }
        else
        {
            if ( GlobalSPTRsReadFromConfig )
                continue;
            GlobalSPTRsReadFromConfig= true;
            trimInfoList= &GlobalSPTRs;
            variableName._( "GLOBAL" );
        }
        variableName._( "_SOURCE_PATH_TRIM_RULES" );

        // get auto sizes from last session
        String512 rules;
        if( ALIB::Config.Get( ALox::ConfigCategoryName, variableName, rules ) != 0 )
        {
            Tokenizer rulesTok( rules, ';' );
            Substring ruleStr;
            while( (ruleStr= rulesTok.Next()).IsNotEmpty() )
            {
                Tokenizer ruleTok( ruleStr, ',' );
                trimInfoList->emplace_back();
                SourcePathTrimRule& rule=trimInfoList->back();

                ruleTok.Next();
                if( ! ( rule.IsPrefix= !ruleTok.Actual.StartsWith( "*" ) ) )
                    ruleTok.Actual.Consume(1);
                rule.Path._( ruleTok.Actual );
                if ( rule.Path.CharAtEnd() == '*' )
                    rule.Path.DeleteEnd( 1 );
                if ( rule.Path.IsEmpty() )
                {
                    trimInfoList->pop_back();
                    continue;
                }

                if( PathSeparator == '/' )
                    rule.Path.SearchAndReplaceAll( "\\", "/"  );
                else
                    rule.Path.SearchAndReplaceAll( "/" , "\\" );

                rule.IncludeString = lib::enums::ReadInclusion( ruleTok.Next() );
                ruleTok.Next().ConsumeInteger( rule.TrimOffset );
                rule.Sensitivity = lib::enums::ReadCase( ruleTok.Next() );
            }
        }

    }

}

ScopeInfo::~ScopeInfo()
{
    delete[] cache;
}


void ScopeInfo::Set ( const TString& sourceFileName, int lineNumber, const TString& methodName,
                      Thread* thread )
{
    // only the first call will store the values
    timeStamp.Set();
    this->thread=   thread;
    threadName= nullptr;

    // if different file than before, search file in cache
    if ( actual->origFile.Buffer() != sourceFileName.Buffer() )
    {
        int           oldestIdx= -1;
        uint_fast64_t oldestTime= ++cacheRun;

        actual= nullptr;
        for( int i= 0; i< cacheSize; i++ )
        {
            if ( cache[i].origFile.Buffer() == sourceFileName.Buffer() )
            {
                actual= &cache[i];
                break;
            }

            if( oldestTime > cache[i].timeStamp )
            {
                oldestTime= cache[i].timeStamp;
                oldestIdx= i;
            }
        }

        // not found? Use the oldest
        if ( actual == nullptr )
        {
            actual= &cache[oldestIdx];

            actual->origFile=    sourceFileName;
            actual->origFilePathSeparator= -2;
            actual->fullPath=       nullptr;
            actual->trimmedPath=    nullptr;
            actual->name=       nullptr;
            actual->nameWOExt=  nullptr;
        }

        // mark as used
        actual->timeStamp= cacheRun;
    }

    this->origLine=    lineNumber;
    this->origMethod=  methodName;
}

void  ScopeInfo::SetSourcePathTrimRule( const TString& path, Inclusion includeString, int trimOffset,
                                         Case sensitivity, Inclusion global )
{
    // clear cache to have lazy variables reset with the next invocation
    for ( int i= 0; i< cacheSize; i++ )
        cache[i].origFile= nullptr;

    // clear command
    if ( trimOffset == 999999 )
    {
        LocalSPTRs.clear();
        if ( global == Inclusion::Include )
            GlobalSPTRs.clear();
        AutoDetectTrimableSourcePath=  (includeString == Inclusion::Include);

        // reset config read flag. This is done for unit testing. Not really useful/needed in real life.
        GlobalSPTRsReadFromConfig=  false;
        return;
    }

    // choosel local or global list
    std::vector<SourcePathTrimRule>* trimInfoList=
                   global == Inclusion::Include  ? &GlobalSPTRs
                                                 : &LocalSPTRs;

    // add new entry
    trimInfoList->emplace_back();
    SourcePathTrimRule& rule= trimInfoList->back();

    // if path starts with '*', it is not a prefix. We store without *
    rule.Path._(path, (rule.IsPrefix= (path.CharAtStart() != '*') ) ? 0 : 1 );
    if ( rule.Path.CharAtEnd() == '*' )
        rule.Path.DeleteEnd( 1 );
    if ( rule.Path.IsEmpty() )
    {
        trimInfoList->pop_back();
        return;
    }

    if( PathSeparator == '/' )
        rule.Path.SearchAndReplaceAll( "\\", "/"  );
    else
        rule.Path.SearchAndReplaceAll( "/" , "\\" );

    rule.IncludeString=   includeString;
    rule.TrimOffset=      trimOffset;
    rule.Sensitivity=     sensitivity;
}


void ScopeInfo::trimPath()
{
    bool trimmed= false;

    int idx= getPathSeparator();
    if( idx < 0 )
    {
        actual->trimmedPath= "";
        return;
    }
    actual->trimmedPath= String( actual->origFile.Buffer(), idx );


    // do 2 times, 0== local list, 1== global list
    for( int trimInfoNo= 0; trimInfoNo < 2 ; trimInfoNo++ )
    {
        // choosel local or global list
        std::vector<SourcePathTrimRule>* trimInfoList=
                   trimInfoNo == 0   ? &LocalSPTRs
                                     : &GlobalSPTRs;

        // loop over trimInfo
        for ( auto& ti : *trimInfoList )
        {
            if( ti.IsPrefix )
                idx= actual->trimmedPath.StartsWith( ti.Path, ti.Sensitivity ) ? 0 : -1;
            else
                idx= actual->trimmedPath.IndexOfSubstring( ti.Path, 0, ti.Sensitivity );
            if ( idx >= 0 )
            {
                int startIdx= idx + ( ti.IncludeString == Inclusion::Include ? ti.Path.Length() : 0 ) + ti.TrimOffset;
                actual->trimmedPath= String( actual->trimmedPath.Buffer(), startIdx, actual->trimmedPath.Length() - startIdx );
                trimmed= true;
                break;
            }
        }

        if (trimmed)
            break;
    }

    // if nothing was found and the flag is still set, try once to auto-detect rule
    // from the 'difference' of source path and current working directory
    if( !trimmed && AutoDetectTrimableSourcePath )
    {
        AutoDetectTrimableSourcePath= false; // do this only once

        // get system execution path and compare to file path
        String256 currentDir;
        ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( currentDir,  ReplaceExternalBuffer );

        Directory::CurrentDirectory( currentDir );

        // Get the prefix that is the same in both paths
        int i= 0;
        int maxIdx= currentDir.Length();
        if ( maxIdx > actual->trimmedPath.Length() )
            maxIdx= actual->trimmedPath.Length();

        while (  i < maxIdx &&  tolower( currentDir[i] ) == tolower( actual->trimmedPath[i] )  )
            i++;

        if ( i > 1 )
        {
            currentDir.SetLength<false>( i );
            TString origFile= actual->origFile;
                SetSourcePathTrimRule( currentDir, Inclusion::Include, 0, Case::Ignore, Inclusion::Exclude );
            actual->origFile= origFile;
            trimPath(); // one recursive call
        }
    }
}


}}}// namespace aworx::lox::core

#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
