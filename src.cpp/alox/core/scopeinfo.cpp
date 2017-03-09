// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"
#include "alox/alox.hpp"
#include <iostream>

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif
#if !defined (HPP_ALIB_STRINGS_UTIL_TOKENIZER)
    #include "alib/strings/util/tokenizer.hpp"
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

ScopeInfo::ScopeInfo( const TString& pName, const std::map<int, String32>&  pThreadDictionary )
: loxName( pName )
, threadDictionary(pThreadDictionary)
{
    loxName.ToUpper();
    ALIB_ASSERT_ERROR( !loxName.Equals( "GLOBAL" ), "Name \"GLOBAL\" not allowed for Lox instances" );
    cache= new SourceFile[cacheSize= DefaultCacheSize];
    lastSourceFile= &cache[0];

    // read trim rules from config
    // do 2 times, 0== local list, 1== global list
    std::vector<SourcePathTrimRule>* trimInfoList;
    for( int trimInfoNo= 0; trimInfoNo < 2 ; trimInfoNo++ )
    {
        // check if done... or set list
        Variable variable;
        if ( trimInfoNo == 0 )
        {
            trimInfoList= &LocalSPTRs;
            variable.Define( ALox::SPTR_LOX, loxName ).Load();
        }
        else
        {
            if ( GlobalSPTRsReadFromConfig )
                continue;
            GlobalSPTRsReadFromConfig= true;

            trimInfoList= &GlobalSPTRs;
            variable.Define( ALox::SPTR_GLOBAL ).Load();
        }

        if( variable.Priority != 0 )
        {
            for( int ruleNo= 0; ruleNo< variable.Size(); ruleNo++ )
            {
                Tokenizer ruleTknzr( variable.GetString( ruleNo ), ',' );
                trimInfoList->emplace_back();
                SourcePathTrimRule& rule=trimInfoList->back();
                rule.Priority=  variable.Priority;

                ruleTknzr.Next();
                if( ( rule.IsPrefix= !ruleTknzr.Actual.StartsWith( "*" ) ) == false )
                    ruleTknzr.Actual.ConsumeChars(1);
                rule.Path._( ruleTknzr.Actual );
                if ( rule.Path.CharAtEnd() == '*' )
                    rule.Path.DeleteEnd( 1 );

                if ( rule.Path.IsEmpty() )
                {
                    trimInfoList->pop_back();
                    continue;
                }

                if( DirectorySeparator == '/' )
                    rule.Path.SearchAndReplaceAll( "\\", "/"  );
                else
                    rule.Path.SearchAndReplaceAll( "/" , "\\" );

                rule.IncludeString =    lib::lang::ReadInclusion( ruleTknzr.Next() );
                ruleTknzr.Next().ConsumeInt( rule.TrimOffset );
                rule.Sensitivity=       lib::lang::ReadCase( ruleTknzr.Next() );
                rule.TrimReplacement=   ruleTknzr.Next();
            }
        }
    }
}

ScopeInfo::~ScopeInfo()
{
    delete[] cache;
}


void ScopeInfo::Set ( const TString& sourceFileName, int lineNumber, const TString& methodName,
                      Thread* pThread )
{
    //scopes.push( std::forward<Scope>(Scope()) );
    actScopeDepth++;
    ALIB_ASSERT( actScopeDepth < 8)
    if( scopes.size() == static_cast<size_t>( actScopeDepth ) )
        scopes.emplace_back();
    Scope& s= scopes[static_cast<size_t>(actScopeDepth)];


    s.timeStamp.Set();
    s.origLine=     lineNumber;
    s.origMethod=   methodName;
    s.sourceFile=   lastSourceFile;

    this->thread=   pThread;
    threadName=     nullptr;

    // if different file than before, search file in cache
    if ( s.sourceFile->origFile.Buffer() != sourceFileName.Buffer() )
    {
        int           oldestIdx= -1;
        uint64_t  oldestTime= ++cacheRun;

        s.sourceFile= nullptr;
        for( int i= 0; i< cacheSize; i++ )
        {
            if ( cache[i].origFile.Buffer() == sourceFileName.Buffer() )
            {
                s.sourceFile= &cache[i];
                break;
            }

            if( oldestTime > cache[i].timeStamp )
            {
                oldestTime= cache[i].timeStamp;
                oldestIdx= i;
            }
        }

        // not found? Use the oldest
        if ( s.sourceFile == nullptr )
        {
            s.sourceFile= &cache[oldestIdx];
            s.sourceFile->Clear();
            s.sourceFile->origFile= sourceFileName;
        }

        // mark as used
        s.sourceFile->timeStamp= cacheRun;
    }

}

void  ScopeInfo::SetSourcePathTrimRule( const TString&  path,
                                        Inclusion       includeString,
                                        int             trimOffset,
                                        Case            sensitivity,
                                        const String&   trimReplacement,
                                        Reach           reach,
                                        int             priority )
{
    // clear cache to have lazy variables reset with the next invocation
    for ( int i= 0; i< cacheSize; i++ )
        cache[i].Clear();

    // clear command
    if ( trimOffset == 999999 )
    {
        LocalSPTRs.clear();
        if ( reach == Reach::Global )
            GlobalSPTRs.clear();
        AutoDetectTrimableSourcePath=  (includeString == Inclusion::Include);

        // reset config read flag. This is done for unit testing. Not really useful/needed in real life.
        GlobalSPTRsReadFromConfig=  false;
        return;
    }

    // choose local or global list
    std::vector<SourcePathTrimRule>* trimInfoList=
                   reach == Reach::Global  ? &GlobalSPTRs
                                           : &LocalSPTRs;

    // insert sorted by priority
    auto it= trimInfoList->begin();
    while( it != trimInfoList->end() && priority < it->Priority  )
        it++;

    it= trimInfoList->insert(it, SourcePathTrimRule() );
    SourcePathTrimRule& rule= *it;
    rule.Priority= priority;

    // if path starts with '*', it is not a prefix. We store without *
    rule.Path._(path, (rule.IsPrefix= (path.CharAtStart() != '*') ) == true  ? 0 : 1 );
    if ( rule.Path.CharAtEnd() == '*' )
        rule.Path.DeleteEnd( 1 );
    if ( rule.Path.IsEmpty() )
    {
        trimInfoList->erase( it );
        return;
    }

    if( DirectorySeparator == '/' )
        rule.Path.SearchAndReplaceAll( "\\", "/"  );
    else
        rule.Path.SearchAndReplaceAll( "/" , "\\" );

    rule.IncludeString=   includeString;
    rule.TrimOffset=      trimOffset;
    rule.Sensitivity=     sensitivity;
    rule.TrimReplacement= trimReplacement;
    if( DirectorySeparator == '/' )
        rule.TrimReplacement.SearchAndReplaceAll( "\\", "/"  );
    else
        rule.TrimReplacement.SearchAndReplaceAll( "/" , "\\" );
}


void ScopeInfo::trimPath()
{
    bool trimmed= false;

    SourceFile* actual= scopes[static_cast<size_t>(actScopeDepth)].sourceFile;
    integer idx= getPathLength();
    if( idx < 0 )
    {
        actual->trimmedPath= "";
        return;
    }
    actual->trimmedPath= String( actual->origFile.Buffer(), idx );


    // do 2 times, 0== local list, 1== global list
    for( int trimInfoNo= 0; trimInfoNo < 2 ; trimInfoNo++ )
    {
        // choose local or global list
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
                integer startIdx= idx + ( ti.IncludeString == Inclusion::Include ? ti.Path.Length() : 0 ) + ti.TrimOffset;
                actual->trimmedPath=        String( actual->trimmedPath.Buffer(), startIdx, actual->trimmedPath.Length() - startIdx );
                actual->trimmedPathPrefix=  ti.TrimReplacement;

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
        integer i= 0;
        integer maxIdx= currentDir.Length();
        if ( maxIdx > actual->trimmedPath.Length() )
            maxIdx= actual->trimmedPath.Length();

        while (  i < maxIdx &&  tolower( currentDir[i] ) == tolower( actual->trimmedPath[i] )  )
            i++;

        if ( i > 1 )
        {
            currentDir.SetLength<false>( i );
            TString origFile= actual->origFile;
                SetSourcePathTrimRule( currentDir, Inclusion::Include, 0, Case::Ignore, NullString,
                                       Reach::Local, Configuration::PrioAutodetect );
            actual->origFile= origFile;
            trimPath(); // one recursive call
        }
    }
}


}}}// namespace aworx::lox::core

#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
