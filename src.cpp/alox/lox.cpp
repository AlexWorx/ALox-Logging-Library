// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

#if !defined (HPP_ALOX_CONSOLE_LOGGERS)
    #include "alox/alox_console_loggers.hpp"
#endif
#if !defined (HPP_ALOX_CORE_SCOPEDUMP)
    #include "core/scopedump.hpp"
#endif
#if !defined (HPP_ALIB_CONTAINERS_PATHMAP)
    #include "alib/containers/pathmap.hpp"
#endif


#if !defined (_GLIBCXX_ALGORITHM) && !defined(_ALGORITHM_)
    #include <algorithm>
#endif

// For code compatibility with ALox Java/C++
// We have to use underscore as the start of the name and for this have to disable a compiler
// warning. But this is a local code (cpp file) anyhow.
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif

    #define _NC _<false>

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif


using namespace std;

namespace aworx {
    namespace lox   {

    using namespace core;



// #################################################################################################
// Constructors/destructor
// #################################################################################################

Lox::Lox(const String& name, bool doRegister )
       : ThreadLock( lib::lang::LockMode::Recursive, lib::lang::Safeness::Safe)
       , scopeInfo( name, threadDictionary )
       , domains        ( nullptr, ""  )
       , internalDomains( nullptr, "$" )
       , scopeDomains ( scopeInfo, false )
       , scopeLogOnce ( scopeInfo, true )
       , scopePrefixes( scopeInfo, false )
       , scopeLogData ( scopeInfo, true )
{
    // create internal sub-domains
    const char* internalDomainList[]= {"LGR", "DMN", "PFX", "THR", "LGD", "VAR" };
    for ( auto it : internalDomainList )
        internalDomains.Find( it, 1, nullptr );
    maxDomainPathLength=  ALox::InternalDomains.Length() + 3;

    // register with ALox
    if( doRegister )
        ALox::Register( this, ContainerOp::Insert );

    // read domain substitution rules from configuration
    Variable variable( ALox::DOMAIN_SUBSTITUTION, GetName() );
    if ( variable.Load() != 0 )
    {
        for( int ruleNo= 0; ruleNo< variable.Size(); ruleNo++ )
        {
            AString* rule= variable.GetString( ruleNo );

            integer idx= rule->IndexOfSubstring( "->" );
            if ( idx > 0 )
            {
                String64 domainPath ( rule, 0, idx  ); domainPath .Trim();
                String64 replacement( rule, idx + 2 ); replacement.Trim();
                SetDomainSubstitutionRule( domainPath, replacement );
            }
            else
            {
                // using alib warning here as we can't do internal logging in the constructor
                ALIB_WARNING( "Syntax error in variable {!Q}.", variable.Fullname );
            }
        }
    }
}

Lox::~Lox()
{
    if( IsRegistered() )
        ALox::Register( this, ContainerOp::Remove );
    clear();
}

void  Lox::clear()
{
    // deregister each logger in std domains and remove it in internals
    for ( int i= static_cast<int>(domains.CountLoggers()) - 1  ; i >= 0  ; i-- )
    {
        Logger* logger= domains.GetLogger( i );
        int ii= internalDomains.GetLoggerNo( logger );
        if ( ii >= 0 )
            internalDomains.RemoveLogger( ii );
        logger->RemoveAcquirer( this );
    }

    // deregister remaining loggers in internal domains
    for ( int i= static_cast<int>(internalDomains.CountLoggers()) - 1  ; i >= 0  ; i-- )
    {
        Logger* logger= internalDomains.GetLogger( i );
        logger->RemoveAcquirer( this );
    }

    // clear domain trees
    domains.Data.clear();
    while( domains.SubDomains.size() > 0 )
    {
        delete domains.SubDomains.back();
        domains.SubDomains.pop_back();
    }
    domains.CntLogCalls= 0;

    internalDomains.Data.clear();
    while( internalDomains.SubDomains.size() > 0 )
    {
        delete internalDomains.SubDomains.back();
        internalDomains.SubDomains.pop_back();
    }
    internalDomains.CntLogCalls= 0;


    // the following would be a good exercise for TMP (to move this into ~ScopeStore)
    // The problem is, we are storing
    // a) AString*
    // b) std::map<AString, int>*
    // c) std::map<AString, Box>
    // This means, a) and b) are 'the same', c) needs an inner iteration everywhere.
    // If we had a map<int, XYZ*>, then a next, separated loop needed to be added.

    // clear scope domains
    if ( scopeDomains.globalStore )
        delete scopeDomains.globalStore;

    for ( auto& it : *scopeDomains.languageStore )
        delete it.Value;

    scopeDomains.languageStore->Clear();

    for ( auto& thread : scopeDomains.threadOuterStore )
        for ( auto& it : thread.second )
            delete it;

    for ( auto& thread : scopeDomains.threadInnerStore )
        for ( auto& it : thread.second )
            delete it;
    scopeDomains.Clear();

    // clear scopePrefixes
    if ( scopePrefixes.globalStore )
        delete static_cast<PrefixLogable*>( scopePrefixes.globalStore );

    for ( auto& it : *scopePrefixes.languageStore )
        delete static_cast<PrefixLogable*>( it.Value );

    scopePrefixes.languageStore->Clear();


    for ( auto& thread : scopePrefixes.threadOuterStore )
        for ( auto& it : thread.second )
            delete static_cast<PrefixLogable*>(it);

    for ( auto& thread : scopePrefixes.threadInnerStore )
        for ( auto& it : thread.second )
            delete static_cast<PrefixLogable*>(it);

    scopePrefixes.Clear();

    // clear log once information
    if ( scopeLogOnce.globalStore )
        delete scopeLogOnce.globalStore;


    for ( auto& it : *scopeLogOnce.languageStore )
        delete it.Value;
    scopeLogOnce.languageStore->Clear();


    for ( auto& thread : scopeLogOnce.threadOuterStore )
        for ( auto& it : thread.second )
            delete it;

    for ( auto& thread : scopeLogOnce.threadInnerStore )
        for ( auto& it : thread.second )
            delete it;
    scopeLogOnce.Clear();

    // delete LogData objects
    if ( scopeLogData.globalStore )
    {
        delete scopeLogData.globalStore;
    }

    for ( auto& map : *scopeLogData.languageStore )
    {
        delete map.Value;
    }
    scopeLogData.languageStore->Clear();


    for ( auto& thread : scopeLogData.threadOuterStore )
        for ( auto& vec : (thread.second) )
        {
            delete vec;
        }
    for ( auto& thread : scopeLogData.threadInnerStore )
        for ( auto& vec : (thread.second) )
        {
            delete vec;
        }
    scopeLogData.Clear();

    // other things
    domainSubstitutions.clear();
    threadDictionary.clear();
    for( Boxes* boxes: logableContainers )
        delete boxes;
    logableContainers.clear();
    for( Boxes* boxes: internalLogables )
        delete boxes;
    internalLogables.clear();
    CntLogCalls=            0;

}

void  Lox::Reset()
{
    clear();

    ClearSourcePathTrimRules( Reach::Global, true );
}

// #################################################################################################
// Methods
// #################################################################################################

TextLogger* Lox::CreateConsoleLogger(const String& name)
{
    //--- check configuration setting "CONSOLE_TYPE"  ---

    Variable variable( ALox::CONSOLE_TYPE );
    variable.Load();
    AString& val= variable.GetString()->Trim();
    if( val.IsEmpty() ||
        val.Equals( "default"  , Case::Ignore ) ) goto DEFAULT;

    if( val.Equals( "plain"    , Case::Ignore ) ) return new ConsoleLogger    ( name );
    if( val.Equals( "Ansi"     , Case::Ignore ) ) return new AnsiConsoleLogger( name );

    if( val.Equals( "WINDOWS"  , Case::Ignore ) )
                                                    #if defined( _WIN32 )
                                                        return new WindowsConsoleLogger( name );
                                                    #else
                                                        goto DEFAULT;
                                                    #endif


    ALIB_WARNING( "Unrecognized value in config variable {!Q} = {!Q}.",
                   variable.Fullname, variable.GetString() );

    DEFAULT:

    #if defined( _WIN32 )
        // if there is no console window we do not do colors
        if ( !ALIB::HasConsoleWindow() )
            return new ConsoleLogger( name );
        else
            return new WindowsConsoleLogger( name );
    #else
        return new AnsiConsoleLogger( name );
    #endif

}

Logger* Lox::GetLogger( const String& loggerName )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // search logger
    Logger* logger;
    if ( (logger= domains        .GetLogger( loggerName ) ) != nullptr )    return logger;
    if ( (logger= internalDomains.GetLogger( loggerName ) ) != nullptr )    return logger;

    // not found
    Boxes& logables= acquireInternalLogables();
    logables.Add( "No logger named {!Q} found.", loggerName );
    logInternal( Verbosity::Warning, "LGR", logables );
    return nullptr;
}

//! @cond NO_DOX
void verbositySettingToVariable( Domain& domain, int loggerNo, Variable& var );
void verbositySettingToVariable( Domain& domain, int loggerNo, Variable& var )
{
    var.Add()._( domain.FullPath )
             ._('=')
             ._( ToString( domain.GetVerbosity( loggerNo ) ) );

    // loop over all sub domains (recursion)
    for ( Domain* subDomain : domain.SubDomains )
        verbositySettingToVariable( *subDomain, loggerNo, var );
}
//! @endcond NO_DOX

void Lox::writeVerbositiesOnLoggerRemoval( Logger* logger )
{
    // When writing back we will use this priority as the maximum to write. This way, if this was
    // an automatic default value, we will not write back into the user's variable store.
    // As always, only if the app fetches new variables on termination, this is entry is copied.
    Variable variable( ALox::VERBOSITY, GetName(), logger->GetName() );

    // first token is "writeback" ?
    variable.Load();
    if ( variable.Size() == 0 )
        return;
    Substring firstArg( variable.GetString() );
    if ( !firstArg.ConsumeString( "writeback", Case::Ignore, Whitespaces::Trim ) )
        return;

    // optionally read a destination variable name
    Substring destVarCategory;
    Substring destVarName;

    if( firstArg.Trim().IsNotEmpty() )
    {
        // separate category from variable name
        integer catSeparatorIdx= firstArg.IndexOf( '_' );
        if (catSeparatorIdx >= 0 )
        {
            destVarCategory.Set( firstArg, 0                   , catSeparatorIdx );
            destVarName    .Set( firstArg, catSeparatorIdx + 1);
        }
        else
            destVarName.Set( firstArg );

        if ( destVarName.IsEmpty() )
        {
            Boxes& logables= acquireInternalLogables();
            logables.Add( "Argument 'writeback' in variable {!Q}.\\n  Error: Wrong destination variable name format: {!Q}"
                          , variable.Fullname, firstArg );
            logInternal( Verbosity::Error, "VAR", logables );
            return;
        }
    }

    // either write directly into LOX_LOGGER_VERBOSITY variable...
    Variable  destVarLocalObject;
    Variable* destVar;
    if( destVarName.IsEmpty() )
    {
        variable.ClearValues( 1 );
        destVar= &variable;
    }
    // ...or into a new given variable
    else
    {
        destVar= &destVarLocalObject;
        destVar->Define( destVarCategory, destVarName, ALox::VERBOSITY.Delim );
        destVar->FormatHints=         variable.FormatHints;
        destVar->FormatAttrAlignment= variable.FormatAttrAlignment;
        destVar->Comments._("Created at runtime through config option 'writeback' in variable \"")._(variable.Fullname)._("\".");
    }

    // collect verbosities
    {
        int loggerNoMainDom= domains        .GetLoggerNo( logger );
        int loggerNoIntDom=  internalDomains.GetLoggerNo( logger );

        if ( loggerNoMainDom >= 0 ) verbositySettingToVariable( domains        , loggerNoMainDom, *destVar );
        if ( loggerNoIntDom  >= 0 ) verbositySettingToVariable( internalDomains, loggerNoIntDom , *destVar );
    }

    // now store using the same plug-in as original variable has
    destVar->Priority= variable.Priority;
    destVar->Store();

    // internal logging
    Boxes& logables= acquireInternalLogables();
    logables.Add( "Argument 'writeback' in variable {!Q}:\\n  Verbosities for logger {!Q} written ",
                  variable.Fullname, logger->GetName() );

    if( destVarName.IsEmpty() )
        logables.Add( "(to source variable)." );
    else
        logables.Add( "to variable {!Q}.", destVar->Fullname );
    logInternal( Verbosity::Info, "VAR", logables );

    // verbose logging of the value written
    String512 intMsg;
    ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( intMsg,  ReplaceExternalBuffer );
    intMsg._("  Value:");
    for( int i= 0; i< destVar->Size() ; i++ )
        intMsg._( "\n    " )._( destVar->GetString(i) );
    logables= acquireInternalLogables();
    logables.Add( intMsg );
    logInternal( Verbosity::Verbose, "VAR", logables );
}

void Lox::dumpStateOnLoggerRemoval()
{
    if( !loggerAddedSinceLastDebugState )
        return;
    loggerAddedSinceLastDebugState= false;

    Variable variable( ALox::DUMP_STATE_ON_EXIT, GetName() );
    variable.Load();

    String64   domain;
    Verbosity  verbosity= Verbosity::Info;

    int flags= 0;
    for( int tokNo= 0; tokNo< variable.Size(); tokNo++ )
    {
        Substring tok( variable.GetString( tokNo ) );
        if( tok.IsEmpty() )
            continue;

        // state flags
             if( tok.Equals( "NONE"            , Case::Ignore ) )  { flags= 0; break; }
        else if( tok.Equals( "Basic"           , Case::Ignore ) )  flags|= Lox::StateInfo_Basic           ;
        else if( tok.Equals( "Version"         , Case::Ignore ) )  flags|= Lox::StateInfo_Version         ;
        else if( tok.Equals( "Loggers"         , Case::Ignore ) )  flags|= Lox::StateInfo_Loggers         ;

        else if( tok.Equals( "Domains"         , Case::Ignore ) )  flags|= Lox::StateInfo_Domains         ;
        else if( tok.Equals( "InternalDomains" , Case::Ignore ) )  flags|= Lox::StateInfo_InternalDomains ;
        else if( tok.Equals( "ScopeDomains"    , Case::Ignore ) )  flags|= Lox::StateInfo_ScopeDomains    ;
        else if( tok.Equals( "DSR"             , Case::Ignore ) )  flags|= Lox::StateInfo_DSR             ;
        else if( tok.Equals( "PrefixLogables"  , Case::Ignore ) )  flags|= Lox::StateInfo_PrefixLogables  ;
        else if( tok.Equals( "Once"            , Case::Ignore ) )  flags|= Lox::StateInfo_Once            ;
        else if( tok.Equals( "LogData"         , Case::Ignore ) )  flags|= Lox::StateInfo_LogData         ;
        else if( tok.Equals( "ThreadMappings"  , Case::Ignore ) )  flags|= Lox::StateInfo_ThreadMappings  ;

        else if( tok.Equals( "SPTR"            , Case::Ignore ) )  flags|= Lox::StateInfo_SPTR            ;
        else if( tok.Equals( "CompilationFlags", Case::Ignore ) )  flags|= Lox::StateInfo_CompilationFlags;

        else if( tok.Equals( "All"             , Case::Ignore ) )  flags|= Lox::StateInfo_All             ;

        // domain and verbosity
        else if( tok.ConsumeString( "domain", Case::Ignore, Whitespaces::Trim ) )
        {
            if( tok.ConsumeChar( '=', Case::Sensitive, Whitespaces::Trim ) )
                domain= tok.Trim();
        }
        else if( tok.ConsumeString( "verbosity", Case::Ignore, Whitespaces::Trim ) )
        {
            if( tok.ConsumeChar( '=', Case::Sensitive, Whitespaces::Trim ) )
                verbosity= ReadVerbosity( tok.Trim() );
        }

        // unknown argument
        else
        {
            Boxes& logables= acquireInternalLogables();
            logables.Add( "Unknown argument {!Q} in variable {} = {!Q}.",
                          tok, variable.Fullname, variable.GetString() );
            logInternal( Verbosity::Error, "VAR", logables);

        }
    }


    if ( flags != 0 )
    {
        State( domain, verbosity, "Auto dump state on exit requested: ", flags );
    }
}


bool Lox::RemoveLogger( Logger* logger )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    int noMainDom=  domains        .GetLoggerNo( logger );
    int noIntDom=   internalDomains.GetLoggerNo( logger );

    if( noMainDom >= 0 || noIntDom >= 0 )
    {
        dumpStateOnLoggerRemoval();
        writeVerbositiesOnLoggerRemoval( logger );

        if( noMainDom >= 0 )
            domains.RemoveLogger( noMainDom );

        if( noIntDom >= 0 )
            internalDomains.RemoveLogger( noIntDom );

        logger->RemoveAcquirer( this );

        return true;
    }

    // not found
    Boxes& logables= acquireInternalLogables();
    logables.Add( "Logger {!Q} not found. Nothing removed.", logger );
    logInternal( Verbosity::Warning, "LGR", logables );
    return false;
}

Logger* Lox::RemoveLogger( const String& loggerName )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    int noMainDom=  domains        .GetLoggerNo( loggerName );
    int noIntDom=   internalDomains.GetLoggerNo( loggerName );

    if( noMainDom >= 0 || noIntDom >= 0 )
    {
        Logger*                 logger=         domains.GetLogger( noMainDom );
        if( logger == nullptr ) logger= internalDomains.GetLogger( noIntDom );

        dumpStateOnLoggerRemoval();
        writeVerbositiesOnLoggerRemoval( logger );

        if( noMainDom >= 0 )
            domains.RemoveLogger( noMainDom );

        if( noIntDom >= 0 )
            internalDomains.RemoveLogger( noIntDom );

        logger->RemoveAcquirer( this );

        Boxes& logables= acquireInternalLogables();
        logables.Add( "Logger {!Q} removed.", logger );
        logInternal( Verbosity::Info, "LGR", logables );
        return logger;
    }

    // not found
    Boxes& logables= acquireInternalLogables();
    logables.Add( "Logger {!Q} not found. Nothing removed.", loggerName );
    logInternal( Verbosity::Warning, "LGR", logables );

    return nullptr;
}

void Lox::SetVerbosity( Logger* logger, Verbosity verbosity, const String& domain, int priority )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // check
    if ( logger == nullptr )
    {
        Boxes& logables= acquireInternalLogables();
        logables.Add( "Given Logger is \"null\". Verbosity not set." );
        logInternal( Verbosity::Error, "LGR", logables );
        return;
    }

    // this might create the (path of) domain(s) and set the \e Loggers' verbosities like their
    // first parent's or as given in configuration
    Domain* dom= evaluateResultDomain( domain );

    // search logger, insert if not found
    bool isNewLogger= false;
    int no= dom->GetLoggerNo( logger );
    if( no < 0 )
    {
        no= dom->AddLogger( logger );

        // error, logger with same name already exists
        if( no < 0 )
        {
            Boxes& logables= acquireInternalLogables();
            logables.Add( "Unable to add logger {!Q}. Logger with same name exists.", logger );
            logInternal( Verbosity::Error, "LGR", logables );


            logables= acquireInternalLogables();
            logables.Add( "  Request was: SetVerbosity({!Q}, {!Q}, Verbosity::{}, {}). ",
                          logger, dom->FullPath, ToString( verbosity ), priority           );
            logInternal( Verbosity::Verbose, "LGR", logables );

            Logger* existingLogger= dom->GetLogger( logger->GetName() );
            logables= acquireInternalLogables();
            logables.Add( "  Existing Logger: {!Q}.", existingLogger );
            logInternal( Verbosity::Verbose, "LGR",  logables );

            return;
        }

        // We have to register with the SmartLock facility of the \e Logger.
        // But only if we have not done this yet, via the 'other' root domain tree
        if ( ( dom->GetRoot() == &domains ? internalDomains.GetLoggerNo( logger )
                                          :         domains.GetLoggerNo( logger ) ) < 0 )
        {
            logger->AddAcquirer( this );
        }

        // store size of name to support tabular internal log output
        if ( maxLoggerNameLength < logger->GetName().Length() )
             maxLoggerNameLength=  logger->GetName().Length();

        // for internal log
        isNewLogger= true;

        // remember that a logger was set after the last removal
        // (for variable LOXNAME_DUMP_STATE_ON_EXIT)
        loggerAddedSinceLastDebugState= true;
    }

    // do
    dom->SetVerbosity( no, verbosity, priority );

    // get verbosities from configuration
    if( isNewLogger )
    {
        Boxes& logables= acquireInternalLogables();
        logables.Add( "Logger {!Q}.", logger );
        if( domain.StartsWith(ALox::InternalDomains) )
            logables.Add(" added for internal log messages.");
        else
            logables.Add(" added.");
        logInternal( Verbosity::Info, "LGR",  logables );

        // we have to get all verbosities of already existing domains
        Variable variable( ALox::VERBOSITY, GetName(), logger->GetName() );
        if( variable.Load() != 0 )
        {
            getAllVerbosities( logger, &domains         , variable );
            getAllVerbosities( logger, &internalDomains , variable );
        }
    }

    String128 msg;  msg._("Logger \"")._( logger->GetName() )._NC( "\":")._(Format::Tab(11 + maxLoggerNameLength))
                       ._('\'')._NC( dom->FullPath )
                       ._( '\'' ).InsertChars(' ', maxDomainPathLength - dom->FullPath.Length() + 1 )
                       ._( "= Verbosity::" );
                       ToString( verbosity, priority, msg ).TrimEnd()._('.');

    Boxes& logables= acquireInternalLogables();
    logables.Add( msg );

    Verbosity actVerbosity= dom->GetVerbosity( no );
    if( actVerbosity != verbosity )
        logables.Add( " Lower priority ({} < {}). Remains {}.",
                      priority, dom->GetPriority(no), ToString( actVerbosity ) );

    logInternal( Verbosity::Info, "LGR", logables );
}

void Lox::SetVerbosity( const String& loggerName, Verbosity verbosity, const String& domain, int priority )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // get domain
    Domain* dom= evaluateResultDomain( domain );

    // get logger
    int no= dom->GetLoggerNo( loggerName );
    if( no < 0 )
    {
        // we have to check if the logger was added in the 'other' tree
        Domain* actualTree= dom->GetRoot();
        Domain* otherTree=  actualTree == &domains ? &internalDomains
                                                   : &domains;
        no= otherTree->GetLoggerNo( loggerName );
        if ( no >= 0 )
        {
            // register the logger with us
            SetVerbosity( otherTree->GetLogger( no ), Verbosity::Off, actualTree->FullPath, Configuration::PrioDefault );
            no= dom->GetLoggerNo( loggerName );
            ALIB_ASSERT( no >= 0 );
        }
        else
        {
            Boxes& logables= acquireInternalLogables();
            logables.Add( "Logger not found. Request was: SetVerbosity({!Q}, {!Q}, Verbosity::{}, {}).",
                          loggerName, dom->FullPath, ToString( verbosity ), priority );
            logInternal( Verbosity::Warning, "LGR",  logables );
            return;
        }
    }

    // do
    dom->SetVerbosity( no, verbosity, priority );

    // log info on this
    Boxes& logables= acquireInternalLogables();
    String128 msg;  msg._("Logger \"")._( dom->GetLogger(no) )._NC( "\":")._(Format::Tab(11 + maxLoggerNameLength))
                       ._('\'')._NC( dom->FullPath )
                       ._( '\'' ).InsertChars(' ', maxDomainPathLength - dom->FullPath.Length() + 1 )
                       ._( "= Verbosity::" );
                       ToString( verbosity, priority, msg ).TrimEnd()._('.');
    logables.Add(msg);

    Verbosity actVerbosity= dom->GetVerbosity( no );
    if( actVerbosity != verbosity )
    logables.Add( " Lower priority ({} < {}). Remains {}.",
                  priority, dom->GetPriority(no), ToString( actVerbosity ) );
    logInternal( Verbosity::Info, "LGR", logables );
}

void Lox::setDomainImpl( const String& scopeDomain, Scope   scope, int pathLevel,
                         bool           removeNTRSD, Thread* thread )
{
    //note: the public class interface assures that \p removeNTRSD (named thread related scope domain)
    // only evaluates true for thread related scopes

    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // check
    if( !checkScopeInformation( scope, pathLevel, "DMN" ) )
        return;

    int threadID= thread != nullptr ? thread->GetId() : Thread::NullThreadId;

    AString* previousScopeDomain;

    scopeDomains.InitAccess( scope, pathLevel, threadID );
    if ( removeNTRSD )
    {
        String64 searchedValue( scopeDomain );
        previousScopeDomain= scopeDomains.Remove( &searchedValue );
    }
    else
    {
        if ( scopeDomain.IsNotEmpty() )
        {
            AString* newValue= new AString( scopeDomain );
            newValue->Trim();
            previousScopeDomain= scopeDomains.Store ( newValue );
        }
        else
            previousScopeDomain= scopeDomains.Remove( nullptr );
    }

    // log info on this
    String256 msg;
    if ( !removeNTRSD && scopeDomain.IsNotEmpty() )
    {
        msg << '\'' << scopeDomain
            << "\' set as default for "; ToString(scope, pathLevel, msg); msg  << '.' ;

        if ( previousScopeDomain  == nullptr )
            logInternal( Verbosity::Info,    "DMN", msg );
        else
        {
            if ( previousScopeDomain->Equals( scopeDomain ) )
            {
                msg << " (Was already set.)";
                logInternal( Verbosity::Verbose, "DMN", msg );
            }
            else
            {
                msg << " Replacing previous default \'" << previousScopeDomain << "\'.";
                logInternal( Verbosity::Warning, "DMN", msg );
            }
        }

    }
    else
    {
        if ( previousScopeDomain  != nullptr )
        {
            msg << '\'' << previousScopeDomain
                << "\' removed from " ; ToString(scope, pathLevel, msg); msg  << '.';
            logInternal( Verbosity::Info, "DMN", msg );
        }
        else
        {
            if ( removeNTRSD )
                msg << '\'' << scopeDomain << "\' not found. Nothing removed for ";
            else
                msg  << "Empty Scope Domain given, nothing registered for ";
            ToString(scope, pathLevel, msg); msg  << '.';

            logInternal( Verbosity::Warning, "DMN", msg );
        }
    }

    // it is on us to delete the previous one
    if ( previousScopeDomain != nullptr )
        delete previousScopeDomain;
}

void Lox::RemoveThreadDomain( const String& scopeDomain, Scope scope, Thread* thread )
{
    if ( !isThreadRelatedScope( scope ) )
        return;

    // check
    if (  scopeDomain.IsEmpty() )
    {
        String128 msg;
        msg  << "Illegal parameter. No scope domain path given. Nothing removed for ";
             ToString(scope, 0, msg); msg  << '.';
        logInternal( Verbosity::Warning, "DMN", msg );

        // do nothing
        return;
    }

    // invoke internal master
    setDomainImpl( scopeDomain, scope, 0, true, thread);
}

void Lox::SetDomainSubstitutionRule( const String& domainPath, const String& replacement )
{
    // check null param: clears all rules
    if ( domainPath.IsEmpty() )
    {
        oneTimeWarningCircularDS= false;
        domainSubstitutions.clear();
        logInternal( Verbosity::Info, "DMN", String("Domain substitution rules removed.") );
        return;
    }


    // create rule
    DomainSubstitutionRule newRule( domainPath, replacement );
    if ( newRule.Search.IsEmpty() )
    {
        logInternal( Verbosity::Warning, "DMN", String("Illegal domain substitution rule. Nothing stored.") );
        return;
    }

    // search existing rule
    std::vector<DomainSubstitutionRule>::iterator  it;
    for( it= domainSubstitutions.begin(); it != domainSubstitutions.end() ; ++it )
    {
        if (     (*it).type == newRule.type
              && (*it).Search.Equals( newRule.Search ) )
            break;
    }

    // no replacement given?
    if ( replacement.IsEmpty() )
    {
        Boxes& logables= acquireInternalLogables();
        if ( it == domainSubstitutions.end() )
        {
            logables.Add("Domain substitution rule {!Q} not found. Nothing to remove.",  domainPath );
            logInternal( Verbosity::Warning, "DMN", logables );
            return;
        }

        logables.Add("Domain substitution rule {!Q} -> {!Q} removed.", domainPath, (*it).Replacement );
        logInternal( Verbosity::Info, "DMN", logables );
        domainSubstitutions.erase( it );
        return;
    }

    Boxes& logables= acquireInternalLogables();
    logables.Add("Domain substitution rule {!Q} -> {!Q} set.", domainPath, newRule.Replacement );

    // change of rule
    String256 msg;
    if ( it != domainSubstitutions.end() )
    {
        msg << " Replacing previous -> \"" << (*it).Replacement  << "\".";
        logables.Add( msg );
        (*it).Replacement._()._( newRule.Replacement );
    }
    else
        domainSubstitutions.emplace_back( newRule );

    logInternal( Verbosity::Info, "DMN", logables );
}

void Lox::setPrefixImpl( const Box& prefix, Scope scope, int pathLevel, Thread* thread  )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // check
    if( !checkScopeInformation( scope, pathLevel, "PFX" ) )
        return;

    int threadID= thread != nullptr ? thread->GetId() : Thread::NullThreadId;

    scopePrefixes.InitAccess( scope, pathLevel, threadID );
    bool isNullOrEmpty=  prefix.Invoke<IIsEmpty, bool>();

    Box* previousLogable=  !isNullOrEmpty ? scopePrefixes.Store( new PrefixLogable( prefix ) )
                                          : scopePrefixes.Remove( nullptr );


    String256 intMsg( "Object ");
    Verbosity intMsgVerbosity= Verbosity::Info;
    if ( !isNullOrEmpty )
    {
        intMsg << prefix
               << " added as prefix logable for "; ToString(scope, pathLevel, intMsg); intMsg  << '.' ;

        if ( previousLogable  != nullptr )
        {
            if ( previousLogable->Invoke<IEquals, bool>( prefix )  )
            {
                intMsg << " (Same as before.)";
                intMsgVerbosity= Verbosity::Verbose;
            }
            else
            {
                intMsg << " Replacing previous "
                       << previousLogable
                       << '.';
            }
        }
    }
    else
    {
        if ( previousLogable  != nullptr )
        {
            intMsg << previousLogable
                   << " removed from list of prefix logables for " ; ToString(scope, pathLevel, intMsg);
            intMsg << '.';
        }
        else
        {
            intMsg  << "<nullptr> given but no prefix logable to remove for ";
            ToString(scope, pathLevel, intMsg);
            intMsg  << '.';

            intMsgVerbosity= Verbosity::Warning;
        }
    }
    logInternal( intMsgVerbosity, "PFX", intMsg );

    // it is on us to delete the previous one
    if ( previousLogable != nullptr )
    {
        delete static_cast<PrefixLogable*>( previousLogable );
    }
}


void Lox::SetPrefix( const Box& prefix, const String& domain, Inclusion otherPLs )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    Domain* dom= evaluateResultDomain( domain );

    bool isNullOrEmpty=  prefix.Invoke<IIsEmpty, bool>();

    String256 msg;
    Verbosity intLogVerbosity= Verbosity::Info;

    if ( !isNullOrEmpty )
    {
        // create logable: if String* type, then copy the string. We are responsible, then.
        msg._("Object ");

        //dom->PrefixLogables.emplace_back( PrefixLogable( prefix ), otherPLs );
        dom->PrefixLogables.emplace_back( new PrefixLogable( prefix ), otherPLs );

        msg << prefix  << " added as prefix logable for";
    }
    else
    {
        size_t qtyPLs=  dom->PrefixLogables.size();
        if ( qtyPLs > 0 )
        {
            PrefixLogable* removedLogable= dom->PrefixLogables[ qtyPLs - 1 ].first;
            dom->PrefixLogables.pop_back();
            msg << "Object " <<  static_cast<Box*>(removedLogable) << " removed from list of prefix logables for";
            delete removedLogable;
        }
        else
        {
            msg << "No prefix logables to remove for";
            intLogVerbosity= Verbosity::Warning;
        }
    }

    msg << " domain \'" << dom->FullPath << "\'.";
    logInternal( intLogVerbosity, "PFX", msg );

}


#if defined (__GLIBCXX__) || defined(__APPLE__)
    void Lox::SetStartTime( time_t startTime, const String& loggerName )
    {
        Ticks t(0);
        t.SetFromEpochSeconds( startTime );
        SetStartTime( t, loggerName );
    }

#elif defined( _WIN32 )
    void Lox::SetStartTime( const FILETIME& startTime, const String& loggerName )
    {
        Ticks t(0);
        t.SetFromFileTime( startTime );
        SetStartTime( t, loggerName );
    }
#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif

void Lox::SetStartTime( Ticks startTime, const String& loggerName )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );


    // request logger only from main domain tree
    Logger* logger= domains.GetLogger( loggerName );
    if ( logger == nullptr )
    {
        Boxes& logables= acquireInternalLogables();
        logables.Add( "Logger {!Q}: not found. Start time not set.", loggerName );
        logInternal( Verbosity::Error, "LGR", logables );
        return;
    }

    // log info on this
    Boxes& logables= acquireInternalLogables();
    logables.Add( "Logger {!Q}: Start time set to " );
    if ( startTime.Raw() == 0L )
    {
        startTime.Set();
        logables.Add( "'now'" );
    }
    else
       logables.Add( "{:yyyy-MM-dd HH:mm:ss}", startTime );

    // do
    logger->TimeOfCreation.Set( startTime );
    logger->TimeOfLastLog .Set( startTime );

    logInternal( Verbosity::Info, "LGR", logables );
}


void Lox::MapThreadName( const String& threadName, int id )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // get current thread id
    String origThreadName;
    if ( id == 0 )
    {
        Thread*         t= Thread::CurrentThread();
        id=             t->GetId();
        origThreadName= t->GetName();
    }

    // add entry
    threadDictionary[id]= threadName;

    // log info on this
    Boxes& logables= acquireInternalLogables();
    logables.Add( "Mapped thread ID {} to {!Q}.", id, threadName);
    if ( origThreadName.IsNotEmpty() )
        logables.Add(" Original thread name: {!Q}.", origThreadName );
    logInternal( Verbosity::Info, "THR", logables );
}

void Lox::once(  const String&  domain,   Verbosity verbosity,
                 const Box&     logable,
                 const String&  pGroup,
                 Scope          scope,    int       pathLevel,
                 int            quantity                                                            )
{
    // We need a group. If none is given, there are two options:
    String512 group(pGroup);
    bool groupWasEmtpy= group.IsEmpty();
    if ( groupWasEmtpy )
    {
        // GLOBAL scope: exact code line match match
        if ( scope == Scope::Global )
        {
            scope= Scope::Filename;
            group._('#')._( scopeInfo.GetLineNumber() );
        }

        // not GLOBAL scope: Unique group per Scope
        else
        {
            group._( noKeyHashKey );
        }
    }

    // get the store
    scopeLogOnce.InitAccess( scope, pathLevel, Thread::NullThreadId );

    std::map<AString, int>* map= scopeLogOnce.Get();
    if( map == nullptr )
    {
        map= new std::map<AString, int>();
        scopeLogOnce.Store( map );
    }

    // create map entry (if not created yet)
    auto it=  map->find( group );
    if (it == map->end() )
        it=   map->insert( std::make_pair( group, 0) ).first;

    // log Once
    if ( quantity >= 0 )
    {
        if ( it->second < quantity )
        {
            it->second++;

            // do the log
            GetLogableContainer().Add( std::forward<const Box&>( logable ) );
            Entry( domain, verbosity );

            // log info if this was the last time
            if( it->second == quantity )
            {
                String128 msg;
                msg <<  "Once() reached limit of "     << quantity
                    << " logs. No further logs for ";

                if ( groupWasEmtpy )
                {
                    if ( scope == Scope::Global )
                        msg << "this line";
                    else
                        ToString(scope, pathLevel, msg);
                }
                else
                {
                    msg << "group \"" << group << '\"';
                    if ( scope != Scope::Global )
                    {
                        msg << " in ";
                        ToString(scope, pathLevel, msg);
                    }
                }
                msg << '.';

                logInternal( Verbosity::Info, "", msg );
            }
        }
    }

    // log Nth
    else
    {
        if ( it->second++ % -quantity == 0 )
        {
            GetLogableContainer().Add( std::forward<const Box&>( logable ) );
            Entry( domain, verbosity );
        }
    }
}

void Lox::storeImpl( const Box& data,  const String&  pKey,
                     Scope      scope, int            pathLevel )
{
    // We need a key. If none is given, we use a constant one indicating that storage is
    // associated exclusively with scope
    String512 key(pKey);
    bool keyWasEmtpy= key.IsEmpty();
    if ( keyWasEmtpy )
        key._( noKeyHashKey );

    // get the store
    scopeLogData.InitAccess( scope, pathLevel, Thread::NullThreadId );
    std::map<AString, Box>* map= scopeLogData.Get();
    if( map == nullptr )
    {
        map= new std::map<AString, Box>;
        scopeLogData.Store( map );
    }

    String128 msg;

    // create map entry (if not created yet)
    auto it=  map->find( key );
    if ( !data.IsNull() )
    {
        bool replacedPrevious= false;
        if ( it == map->end() )
            it=   map->insert( std::make_pair( key, data ) ).first;
        else
        {
            replacedPrevious= true;
            it->second= data;
        }

        // log info if this was the last time
        msg <<  "Stored data ";

        if ( !keyWasEmtpy )
            msg << " with key \"" << key << "\" ";
        msg << "in ";
        ToString(scope, pathLevel, msg);
        msg << '.';
        if ( replacedPrevious )
            msg << " (Replaced and deleted previous.)";
    }

    // delete
    else
    {
        if ( it != map->end() )
        {
            map->erase( it );
            if ( map->size() == 0 )
            {
                delete map;
                scopeLogData.Remove( nullptr );
            }
            msg <<  "Deleted map data ";
        }
        else
            msg <<  "No map data found to delete ";

        if ( !keyWasEmtpy )
            msg << " with key \"" << key << "\" ";
        msg << "in ";
        ToString(scope, pathLevel, msg);
        msg << '.';
    }

    logInternal( Verbosity::Info, "LGD", msg );
}


Box Lox::retrieveImpl( const String& pKey, Scope scope, int  pathLevel )
{
    // We need a key. If none is given, we use a constant one indicating that storage is
    // associated exclusively with scope
    String512 key(pKey);
    bool keyWasEmtpy= key.IsEmpty();
    if ( keyWasEmtpy )
        key._( noKeyHashKey );

    // get the data (create if not found)
    scopeLogData.InitAccess( scope, pathLevel, Thread::NullThreadId );
    Box returnValue;
    for( int i= 0; i < 2 ; i++ )
    {
        std::map<AString, Box>* map= scopeLogData.Get();
        if( map != nullptr )
        {
            auto it=  map->find( key );
            if ( it != map->end() )
                returnValue= it->second;
        }

        if ( returnValue.IsNull() )
            storeImpl( Box(), pKey, scope, pathLevel );
        else
            break;
    }

    // log info if this was the last time
    String128 msg;
    msg <<  "Data ";

    if ( !keyWasEmtpy )
        msg << " with key \"" << key << "\" ";
    msg << "in ";
    ToString(scope, pathLevel, msg);
    msg << ( !returnValue.IsNull() ? " received." : " not found." );

    logInternal( Verbosity::Info, "LGD", msg );
    return returnValue;
}


void Lox::State( const String&    domain,
                 Verbosity        verbosity,
                 const String&    headLine,
                 int              flags      )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    AString buf( 2048 );
    if ( headLine.IsNotEmpty() )
        buf._NC( headLine ).NewLine();

    GetState( buf, flags );

    GetLogableContainer().Add( buf );
    Entry( domain, verbosity );
}

Boxes&  Lox::GetLogableContainer()
{
    ALIB_ASSERT_ERROR( cntAcquirements >= 1, "Lox not acquired." );
    ALIB_ASSERT_WARNING( cntAcquirements < 5, "Logging recursion depth >= 5" );
    while( logableContainers.size() < static_cast<size_t>(cntAcquirements) )
        logableContainers.emplace_back( new Boxes() );

    Boxes& logables= *logableContainers[static_cast<size_t>(cntAcquirements - 1)];
    logables.clear();
    return logables;
}

void Lox::Entry( const String& domain, Verbosity verbosity )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // auto-initialization of debug loggers
    #if ALOX_DBG_LOG
        if( domains.CountLoggers() == 0 && this == ALox::Log() )
            Log::AddDebugLogger( this );
    #endif

    ALIB_ASSERT_ERROR(!ALox::Init(), "ALox not initialized" );

    CntLogCalls++;

    if ( domains.CountLoggers() == 0 )
        return;

    log( evaluateResultDomain( domain ), verbosity, *logableContainers[static_cast<size_t>(cntAcquirements - 1)], Inclusion::Include );
}

void Lox::entryDetectDomainImpl( Verbosity verbosity )
{
    Boxes& logables= *logableContainers[static_cast<size_t>(cntAcquirements - 1)];
    if ( logables.size() > 1 )
    {
        if( logables[0].IsArrayOf<char>() )
        {
            String firstArg= logables[0].Unbox<String>();

            bool illegalCharacterFound= false;
            for( int i= 0; i< firstArg.Length() ; ++i )
            {
                char c= firstArg[i];
                if (!(    isdigit( c )
                       || ( c >= 'A' && c <= 'Z' )
                       || c == '-'
                       || c == '_'
                       || c == '/'
                       || c == '.'
                ))
                {
                    illegalCharacterFound= true;
                    break;
                }
            }

            if ( illegalCharacterFound )
            {
                Entry( nullptr, verbosity );
                return;
            }

            logables.erase( logables.begin() );
            Entry( firstArg, verbosity );
            return;
        }
    }

    Entry( nullptr, verbosity );
}


// #################################################################################################
// internals
// #################################################################################################
Domain* Lox::evaluateResultDomain( const String& domainPath )
{
    String128 resDomain;

    // 0. internal domain tree?
    if ( domainPath.StartsWith( ALox::InternalDomains, Case::Sensitive ) )
    {
        // cut "$/" from the path
        resDomain._( domainPath, ALox::InternalDomains.Length() );
        return findDomain( internalDomains, resDomain );
    }

    // loop over scopes
    String64 localPath;
    scopeDomains.InitWalk( Scope::ThreadInner,
                           // we have to provide nullptr if parameter is empty
                           domainPath.IsNotEmpty() ? &localPath._(domainPath)
                                                   : nullptr
                           );
    AString* nextDefault;
    while( (nextDefault= scopeDomains.Walk() ) != nullptr )
    {
        ALIB_ASSERT( nextDefault->IsNotEmpty() );

        if ( resDomain.IsNotEmpty() )
            resDomain.InsertAt( "/", 0);
        resDomain.InsertAt( nextDefault, 0 );

        // absolute path? That's it
        if ( resDomain.CharAtStart() == Domain::Separator() )
            break;
    }

    return findDomain( domains, resDomain );
}

void Lox::getVerbosityFromConfig( core::Logger*  logger, core::Domain*  dom,
                                  Variable& variable )
{
    // get logger number. It may happen that the logger is not existent in this domain tree.
    int loggerNo= dom->GetLoggerNo( logger ) ;
    if ( loggerNo < 0 )
        return;

    for( int varNo= 0; varNo< variable.Size(); varNo++ )
    {
        Tokenizer verbosityTknzr( variable.GetString( varNo ), '=' );

        Substring domainStr= verbosityTknzr.Next();
        String128 domainStrBuf;
        if ( domainStr.StartsWith( "INTERNAL_DOMAINS", Case::Ignore ) )
        {
            domainStrBuf._( domainStr, 16 );
            while ( domainStrBuf.CharAtStart() == '/' )
                domainStrBuf.DeleteStart( 1 );
            domainStrBuf.InsertAt( ALox::InternalDomains, 0 );
            domainStr.Set( domainStrBuf );
        }

        String    verbosityStr= verbosityTknzr.Next();
        if ( verbosityStr.IsEmpty() )
            continue;

        int searchMode= 0;
        if ( domainStr.ConsumeChar       ( '*' ) )    searchMode+= 2;
        if ( domainStr.ConsumeCharFromEnd( '*' ) )    searchMode+= 1;
        if(     ( searchMode == 0 && dom->FullPath.Equals          ( domainStr,    Case::Ignore )     )
            ||  ( searchMode == 1 && dom->FullPath.StartsWith      ( domainStr,    Case::Ignore )     )
            ||  ( searchMode == 2 && dom->FullPath.EndsWith        ( domainStr,    Case::Ignore )     )
            ||  ( searchMode == 3 && dom->FullPath.IndexOfSubstring( domainStr, 0, Case::Ignore ) >=0 )
            )
        {
            Verbosity verbosity= ReadVerbosity( verbosityStr );
            dom->SetVerbosity( loggerNo, verbosity, variable.Priority );

            // log info on this
            String128 msg;  msg._NC( "Logger \"" )._NC( logger->GetName() ) ._NC( "\":" )._(Format::Tab(11 + maxLoggerNameLength))
                               ._NC( '\'' )._NC( dom->FullPath )
                               ._( '\'' ).InsertChars(' ', maxDomainPathLength - dom->FullPath.Length() + 1 )
                               ._( "= Verbosity::" );
                               ToString( verbosity , dom->GetPriority( loggerNo ), msg ).TrimEnd()
                               ._NC( '.' );

            logInternal( Verbosity::Info, "LGR", msg );
        }
    }
}

void Lox::getDomainPrefixFromConfig( core::Domain*  dom )
{
    Variable variable( ALox::PREFIXES, GetName() );
    if( variable.Load() == 0 )
        return;

    for( int varNo= 0; varNo< variable.Size(); varNo++ )
    {
        Tokenizer prefixTok( variable.GetString( varNo ), '=' );

        Substring domainStr= prefixTok.Next();
        String128 domainStrBuf;
        if ( domainStr.StartsWith( "INTERNAL_DOMAINS", Case::Ignore ) )
        {
            domainStrBuf._( domainStr, 16 );
            while ( domainStrBuf.CharAtStart() == '/' )
                domainStrBuf.DeleteStart( 1 );
            domainStrBuf.InsertAt( ALox::InternalDomains, 0 );
            domainStr.Set( domainStrBuf );
        }

        Tokenizer prefixTokInner( prefixTok.Next(), ',' );
        Substring prefixStr= prefixTokInner.Next();
        if ( prefixStr.IsEmpty() )
            continue;
        if ( prefixStr.ConsumeChar( '\"' ) )
            prefixStr.ConsumeCharFromEnd( '\"' );

        Inclusion otherPLs= Inclusion::Include;
        prefixTokInner.Next();
        if ( prefixTokInner.Actual.IsNotEmpty() )
            otherPLs= lib::lang::ReadInclusion( prefixTokInner.Actual  );

        int searchMode= 0;
        if ( domainStr.ConsumeChar       ( '*' ) )    searchMode+= 2;
        if ( domainStr.ConsumeCharFromEnd( '*' ) )    searchMode+= 1;
        if(     ( searchMode == 0 && dom->FullPath.Equals          ( domainStr,    Case::Ignore )     )
            ||  ( searchMode == 1 && dom->FullPath.StartsWith      ( domainStr,    Case::Ignore )     )
            ||  ( searchMode == 2 && dom->FullPath.EndsWith        ( domainStr,    Case::Ignore )     )
            ||  ( searchMode == 3 && dom->FullPath.IndexOfSubstring( domainStr, 0, Case::Ignore ) >=0 )
            )
        {
            dom->PrefixLogables.emplace_back( new PrefixLogable( prefixStr ), otherPLs );

            // log info on this
            String128 msg;  msg._NC( "String \"" )._NC( prefixStr )._NC ( "\" added as prefix logable for domain \'" )
                               ._NC( dom->FullPath )
                               ._NC( "\'. (Retrieved from configuration variable" )
                               ._NC( variable.Fullname )._( ".)" );

            logInternal( Verbosity::Info, "PFX", msg );
        }
    }
}

void Lox::getAllVerbosities( core::Logger*  logger, core::Domain*  dom,
                             Variable& variable  )
{
    // get verbosity for us
    getVerbosityFromConfig( logger, dom, variable );

    // loop over all sub domains (recursion)
    for ( Domain* subDomain : dom->SubDomains )
        getAllVerbosities( logger, subDomain, variable );
}


Domain* Lox::findDomain( Domain& rootDomain, String domainPath )
{
    int maxSubstitutions= 10;
    String128 substPath;
    for(;;)
    {
        // loop for creating domains, one by one
        Domain* dom= nullptr;
        for(;;)
        {
            bool wasCreated;
            dom= rootDomain.Find( domainPath, 1, &wasCreated );
            if ( wasCreated )
            {
                // get maximum domain path length (for nicer State output only...)
                if ( maxDomainPathLength < dom->FullPath.Length() )
                     maxDomainPathLength=  dom->FullPath.Length();

                // log info on new domain
                Boxes& logables= acquireInternalLogables();
                logables.Add( "{!Q} registered.", dom->FullPath );
                logInternal( Verbosity::Info, "DMN", logables );
            }

            // read domain from Config
            if ( !dom->ConfigurationRead )
            {
                dom->ConfigurationRead= true;

                Variable variable;
                for ( int i= 0; i < dom->CountLoggers(); ++i )
                {
                    Logger* logger= dom->GetLogger(i);
                    if ( 0 != variable.Define(ALox::VERBOSITY, GetName(), logger->GetName()).Load() )
                        getVerbosityFromConfig( logger, dom, variable );
                }

                getDomainPrefixFromConfig( dom );
            }

            if ( wasCreated )
            {
                if ( dom->CountLoggers() == 0 )
                    logInternal( Verbosity::Verbose, "DMN", String("   No loggers set, yet.") );
                else
                {
                    for ( int i= 0; i < dom->CountLoggers(); i++ )
                    {
                        String256 msg; msg._("  \"")._( dom->GetLogger(i)->GetName() )._("\": ");
                                       msg.InsertChars( ' ', maxLoggerNameLength  + 6 - msg.Length() );
                                       msg._( dom->FullPath )._(" = " );
                                          ToString( dom->GetVerbosity(i), dom->GetPriority(i), msg );
                        logInternal( Verbosity::Verbose, "DMN", msg );
                    }
                }
            }
            else
                break;
        }

        // apply domain substitutions
        if( domainSubstitutions.size() > 0 )
        {
            substPath._();
            while( maxSubstitutions-- > 0  )
            {
                // loop over rules
                bool substituted= false;
                for( auto& rule : domainSubstitutions )
                {
                    switch( rule.type )
                    {
                        case DomainSubstitutionRule::Type::StartsWith:
                            if( substPath.IsEmpty() )
                            {
                                if ( dom->FullPath.StartsWith( rule.Search, Case::Sensitive ) )
                                {
                                    substPath._( rule.Replacement )._( dom->FullPath, rule.Search.Length() );
                                    substituted= true;
                                    continue;
                                }
                            }
                            else
                            {
                                if ( substPath.StartsWith( rule.Search, Case::Sensitive ) )
                                {
                                    substPath.ReplaceSubstring( rule.Replacement, 0, rule.Search.Length()  );
                                    substituted= true;
                                    continue;
                                }
                            }
                        break;

                        case DomainSubstitutionRule::Type::EndsWith:
                            if( substPath.IsEmpty() )
                            {
                                if ( dom->FullPath.EndsWith( rule.Search, Case::Sensitive ) )
                                {
                                    substPath._( dom->FullPath, 0, dom->FullPath.Length() - rule.Search.Length() )._( rule.Replacement );
                                    substituted= true;
                                    continue;
                                }
                            }
                            else
                            {
                                if ( substPath.EndsWith( rule.Search, Case::Sensitive ) )
                                {
                                    substPath.DeleteEnd( rule.Search.Length() )._( rule.Replacement );
                                    substituted= true;
                                    continue;
                                }
                            }
                        break;


                        case DomainSubstitutionRule::Type::Substring:
                        {
                            if( substPath.IsEmpty() )
                            {
                                integer idx= dom->FullPath.IndexOf( rule.Search, 0, Case::Sensitive );
                                if ( idx >= 0 )
                                {
                                    substPath._( dom->FullPath, 0, idx )._( rule.Replacement)._( dom->FullPath, idx + rule.Search.Length() );
                                    substituted= true;
                                    continue; //next rule
                                }
                            }
                            else
                            {
                                integer idx= substPath.IndexOf( rule.Search, 0, Case::Sensitive );
                                if ( idx >= 0 )
                                {
                                    substPath.ReplaceSubstring( rule.Replacement, idx, rule.Search.Length()  );
                                    substituted= true;
                                    continue; //next rule
                                }
                            }
                        }
                        break;


                        case DomainSubstitutionRule::Type::Exact:
                        {
                            if( substPath.IsEmpty() )
                            {
                                if ( dom->FullPath.Equals( rule.Search ) )
                                {
                                    substPath._( rule.Replacement);
                                    substituted= true;
                                    continue; //next rule
                                }
                            }
                            else
                            {
                                if ( substPath.Equals( rule.Search) )
                                {
                                    substPath._()._( rule.Replacement );
                                    substituted= true;
                                    continue; //next rule
                                }
                            }
                        }
                        break;

                    } // switch rule type

                }//rules loop

                // stop if non was found
                if( !substituted )
                    break;
            }

            // too many substitutions?
            if ( maxSubstitutions <= 0 && !oneTimeWarningCircularDS )
            {
                oneTimeWarningCircularDS= true;
                logInternal( Verbosity::Error, "DMN",
                  String( "The Limit of 10 domain substitutions was reached. Circular substitution assumed!"
                          " (This error is only reported once!)") );
            }

            // anything substituted?
            if( substPath.Length() > 0 )
            {
                domainPath= substPath;
                continue;
            }
        }

        return dom;
    }
}

bool Lox::checkScopeInformation( Scope scope, int pathLevel, const String& internalDomain )
{
    if (     ( scope == Scope::Path     &&  scopeInfo.GetFullPath().IsEmpty() )
         ||  ( scope == Scope::Filename &&  scopeInfo.GetFileName().IsEmpty() )
         ||  ( scope == Scope::Method   &&  scopeInfo.GetMethod()  .IsEmpty() ) )
    {
        String256 msg;
            msg << "Missing scope information. Cant use ";
            ToString(scope, pathLevel, msg);
            msg << '.';
        logInternal( Verbosity::Error, internalDomain, msg );
        return false;
    }
    return true;
}

bool Lox::isThreadRelatedScope( Scope scope )
{
    // check
    if (    scope == Scope::ThreadOuter
         || scope == Scope::ThreadInner )
        return true;

    String128 msg;
    msg  << "Illegal parameter, only Scope::ThreadOuter and Scope::ThreadInner allowed."
         << " Given: " ;
         ToString(scope, 0, msg); msg  << '.';
    logInternal( Verbosity::Error, "DMN", msg );

    ALIB_DEBUG_CODE(
        aworx::lib::lang::Report::GetDefault()
        .DoReport(  scopeInfo.GetOrigFile(), scopeInfo.GetLineNumber(), scopeInfo.GetMethod(),
                     0, "Illegal parameter, only Scope::ThreadOuter and Scope::ThreadInner allowed." );
                   )

    return false;
}

void Lox::log( core::Domain* dom, Verbosity verbosity, Boxes& logables, Inclusion includePrefixes )
{
    dom->CntLogCalls++;
    bool logablesCollected= false;
    Box marker;
    for ( int i= 0; i < dom->CountLoggers() ; i++ )
        if( dom->IsActive( i, verbosity ) )
        {
            // lazily collect objects once an active logger is found
            if ( !logablesCollected )
            {
                logablesCollected= true;
                scopePrefixes.InitWalk( Scope::ThreadInner, &marker );
                const Box* next;
                int qtyUserLogables= static_cast<int>( logables.size() );
                int qtyThreadInners= -1;

                while( (next= scopePrefixes.Walk() ) != nullptr )
                {
                    if( next != &marker )
                    {
                        // this is false for internal domains (only domain specific logables are added there)
                        if ( includePrefixes == Inclusion::Include )
                        {
                            // after marker is read, logables need to be prepended. This is checked below
                            // using "qtyThreadInners < 0"
                            if ( next->IsType<Boxes*>() )
                            {
                                Boxes* boxes= next->Unbox<Boxes*>();
                                for (int pfxI= static_cast<int>(boxes->size()) - 1 ; pfxI >= 0 ; --pfxI )
                                    logables.insert( logables.begin() + ( qtyThreadInners < 0 ? qtyUserLogables : 0 ),
                                                    (*boxes)[static_cast<size_t>(pfxI)] );
                            }
                            else
                                logables.insert( logables.begin() + ( qtyThreadInners < 0 ? qtyUserLogables : 0 ), next );
                        }
                    }

                    // was this the actual? then insert domain-associated logables now
                    else
                    {
                        bool excludeOthers= false;
                        qtyThreadInners= static_cast<int>( logables.size() ) - qtyUserLogables;
                        Domain* pflDom= dom;
                        while ( pflDom != nullptr )
                        {
                            for( auto it= pflDom->PrefixLogables.rbegin() ; it != pflDom->PrefixLogables.rend() ; it++ )
                            {
                                // a list of logables? Copy them
                                PrefixLogable& prefix= *it->first;
                                if ( prefix.IsType<Boxes*>() )
                                {
                                    Boxes* boxes= prefix.Unbox<Boxes*>();
                                    for (int pfxI= static_cast<int>(boxes->size()) - 1 ; pfxI >= 0 ; --pfxI )
                                        logables.insert( logables.begin(), (*boxes)[static_cast<size_t>(pfxI)] );
                                }
                                else
                                    logables.insert( logables.begin(), prefix );


                                if ( it->second == Inclusion::Exclude )
                                {
                                    excludeOthers= true;
                                    break;
                                }
                            }

                            pflDom= excludeOthers ? nullptr :  pflDom->Parent;
                        }

                        // found a stoppable one? remove those from thread inner and break
                        if (excludeOthers)
                        {
                            for ( int ii= 0; ii < qtyThreadInners ; ii++ )
                                logables.pop_back();
                            break;
                        }
                    }
                }
            } // end of collection

            Logger* logger= dom->GetLogger(i);
            OWN(*logger);
                logger->CntLogs++;
                logger->Log( *dom, verbosity, logables, scopeInfo );
                logger->TimeOfLastLog.Set();
        }
}

void Lox::logInternal( Verbosity verbosity, const String& subDomain, Boxes& msg )
{
    ALIB_ASSERT_ERROR(!ALox::Init(), "ALox not initialized" );
    log( findDomain( internalDomains, subDomain ), verbosity, msg, Inclusion::Exclude );

    internalLogables[--internalLogRecursionCounter]->clear();
}

void Lox::logInternal( Verbosity verbosity, const String& subDomain, const String& msg )
{
    Boxes& logables= acquireInternalLogables();
    logables.Add( msg );
    logInternal( verbosity, subDomain, logables );
}

}}// namespace aworx::lox
