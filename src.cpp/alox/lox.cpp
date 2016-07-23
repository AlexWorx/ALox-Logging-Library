// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

#if !defined (HPP_ALIB_CONFIG_CONFIGURATION)
    #include "alib/config/configuration.hpp"
#endif
#if !defined (HPP_ALIB_SYSTEM_SYSTEM)
    #include "alib/system/system.hpp"
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
#if !defined (HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif


#if !defined (_GLIBCXX_ALGORITHM) && !defined(_ALGORITHM_)
    #include <algorithm>
#endif


using namespace std;

namespace aworx {
    namespace lox   {

    using namespace core;
// For code compatibility with ALox Java/C++
#define _NC _<false>


// #################################################################################################
// Constructors/destructor
// #################################################################################################

Lox::Lox(const TString& name, bool doRegister )
       : ThreadLock( lib::enums::LockMode::Recursive, lib::enums::Safeness::Safe)
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
        internalDomains.Find( it, Case::Sensitive, 1, nullptr );
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

            int idx= rule->IndexOfSubstring( "->" );
            if ( idx > 0 )
            {
                String64 domainPath ( rule, 0, idx  ); domainPath .Trim();
                String64 replacement( rule, idx + 2 ); replacement.Trim();
                SetDomainSubstitutionRule( domainPath, replacement );
            }
            else
            {
                // using alib warning here as we can't do internal logging in the constructor
                ALIB_WARNING_S512( "Syntax error in variable \"" << variable.Fullname << "\"." );
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
    for ( int i= domains.CountLoggers() -1; i >= 0  ; i-- )
    {
        Logger* logger= domains.GetLogger( i );
        int ii= internalDomains.GetLoggerNo( logger );
        if ( ii >= 0 )
            internalDomains.RemoveLogger( ii );
        logger->RemoveAcquirer( this );
    }

    // deregister remaining loggers in internal domains
    for ( int i= internalDomains.CountLoggers() - 1; i >= 0 ; i-- )
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
    // c) std::map<AString, LogData*>
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
    {
        if ( scopePrefixes.globalStore->Type == 0 )
            delete (AString*) scopePrefixes.globalStore->Object;
        delete scopePrefixes.globalStore;
    }

    for ( auto& it : *scopePrefixes.languageStore )
    {
        if ( it.Value->Type == 0 )
            delete (AString*) it.Value->Object;
        delete it.Value;
    }
    scopePrefixes.languageStore->Clear();


    for ( auto& thread : scopePrefixes.threadOuterStore )
        for ( auto& it : thread.second )
        {
            if ( it->Type == 0 )
                delete (AString*) it->Object;
            delete it;
        }

    for ( auto& thread : scopePrefixes.threadInnerStore )
        for ( auto& it : thread.second )
        {
            if ( it->Type == 0 )
                delete (AString*) it->Object;
            delete it;
        }
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
        for ( auto& it : *scopeLogData.globalStore )
            delete it.second;
        delete scopeLogData.globalStore;
    }

    for ( auto& map : *scopeLogData.languageStore )
    {
        for ( auto& it : *(map.Value) )
            delete it.second;
        delete map.Value;
    }
    scopeLogData.languageStore->Clear();


    for ( auto& thread : scopeLogData.threadOuterStore )
        for ( auto& vec : (thread.second) )
        {
            for ( auto& it : *vec )
                delete it.second;
            delete vec;
        }
    for ( auto& thread : scopeLogData.threadInnerStore )
        for ( auto& vec : (thread.second) )
        {
            for ( auto& it : *vec )
                delete it.second;
            delete vec;
        }
    scopeLogData.Clear();

    // other things
    domainSubstitutions.clear();
    threadDictionary.clear();
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
    //--- first: check configuration setting "CONSOLE_TYPE"  ---
    bool cfgNoQTCreator= false;

    Variable variable( ALox::CONSOLE_TYPE );
    variable.Load();
    AString& val= variable.GetString()->Trim();
    if( val.IsEmpty() ||
        val.Equals( "default"       , Case::Ignore ) ) goto DEFAULT;

    if( val.Equals( "plain"         , Case::Ignore ) ) return new ConsoleLogger    ( name );
    if( val.Equals( "Ansi"          , Case::Ignore ) ) return new AnsiConsoleLogger( name );
    if( val.Equals( "NoQtCreator"   , Case::Ignore ) ) { cfgNoQTCreator= true; goto DEFAULT; }

    if( val.Equals( "WINDOWS",  Case::Ignore ) ) {
                                                                #if defined( _WIN32 )
                                                                     goto STD_COL_CHECK;
                                                                #else
                                                                     goto DEFAULT;
                                                                #endif
                                                 }

    ALIB_WARNING_S512( "Unrecognized value in config variable \"" << variable.Fullname
                       << "\"= " << variable.GetString() );

    //--- second: check debug environment
    DEFAULT:

    switch( System::RTE() )
    {
        // no color/ESC support
        case System::RuntimeEnvironment::EclipseCDT:    // Eclipse by default does not know ANSI
                                                            return new ConsoleLogger( name );

        // ANSI
        case System::RuntimeEnvironment::Shell:
        case System::RuntimeEnvironment::Desktop:
        case System::RuntimeEnvironment::VStudio:       goto STD_COL_CHECK;

        case System::RuntimeEnvironment::QTCreator:
        {
            if ( !cfgNoQTCreator )
            {
                // Does not support color! :-( But supports clickable output :-) ... but only for QMake projects
                ConsoleLogger* cl= new aworx::lox::loggers::ConsoleLogger( name );
                textlogger::MetaInfo* mi= cl->MetaInfo;

                // replace all square brackets
                AString* formatStrings[] =
                {
                    &mi->Format             ,
                    &mi->VerbosityError     ,
                    &mi->VerbosityWarning   ,
                    &mi->VerbosityInfo      ,
                    &mi->VerbosityVerbose   ,

                };
                for ( AString* fs : formatStrings )
                {
                    fs->SearchAndReplace( "][", " " );
                    fs->SearchAndReplace( "[" , " " );
                    fs->SearchAndReplace( "]" , " " );
                }

                // To have QTCreator recognize the location, it needs 3 spaces + "LOC: [...]"
                mi->Format.SearchAndReplace( "%Sp/%SF(%SL):",
                                             //"   Loc: [%SF(%SL)]:" );
                                             "   Loc: [%Sp/%SF(%SL)]:" );

                // replace square brackets in all log messages
                cl->SetReplacement( "[", "{" );
                cl->SetReplacement( "]", "}" );
                return cl;
            }
        }
        break;

        // plain
        case System::RuntimeEnvironment::MobileDevice:
        case System::RuntimeEnvironment::Unknown:       break;
    }

    // not detected:
    //--- in windows, we choose win console mode, if we have a console, otherwise plain
    #if defined( _WIN32 )
        goto STD_COL_CHECK;
    #else
        return new AnsiConsoleLogger( name );
    #endif


    STD_COL_CHECK:
        // if there is no console window we do not do colors
        if ( !System::HasConsoleWindow() )
            return new ConsoleLogger( name );

        #if defined(_WIN32)
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
    logInternal( Verbosity::Warning, "LGR", String128() <<
        "No logger named \"" << loggerName << "\" found." );
    return nullptr;
}

#if !defined( IS_DOXYGEN_PARSER)
void verbositySettingToVariable( Domain& domain, int loggerNo, Variable& var )
{
    var.AddString()._( domain.FullPath )
                   ._('=')
                   ._( ToString( domain.GetVerbosity( loggerNo ) ) );

    // loop over all sub domains (recursion)
    for ( Domain* subDomain : domain.SubDomains )
        verbositySettingToVariable( *subDomain, loggerNo, var );
}
#endif

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
    if ( !firstArg.Consume( "writeback", Case::Ignore, Whitespaces::Trim ) )
        return;

    // optionally read a destination variable name
    Substring destVarCategory;
    Substring destVarName;

    if( firstArg.Trim().IsNotEmpty() )
    {
        // separate category from variable name
        int catSeparatorIdx= firstArg.IndexOf( '_' );
        if (catSeparatorIdx >= 0 )
        {
            destVarCategory.Set( firstArg, 0                   , catSeparatorIdx );
            destVarName    .Set( firstArg, catSeparatorIdx + 1);
        }
        else
            destVarName.Set( firstArg );

        if ( destVarName.IsEmpty() )
        {
            logInternal( Verbosity::Error, "VAR", String256()
                         ._( "Argument 'writeback' in variable " )
                         ._(variable.Fullname)
                         ._( "\n  Error:    Wrong destination variable name format: \"" )
                         ._( firstArg)._( "\"" )  );
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
    String512 intMsg;
    ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( intMsg,  ReplaceExternalBuffer );
    intMsg._( "Argument 'writeback' in variable " )._( variable.Fullname )
          ._( ":\n  Verbosities for logger \"" )   ._( logger->GetName() )
          ._( "\" written " );
    if( destVarName.IsEmpty() )
        intMsg._( "(to source variable)." );
    else
        intMsg._( "to variable \"" )  ._( destVar->Fullname ) ._("\".") ;
    logInternal( Verbosity::Info, "VAR", intMsg );

    // verbose logging of the value written
    intMsg._()._("  Value:");
    for( int i= 0; i< destVar->Size() ; i++ )
        intMsg._( "\n    " )._( destVar->GetString(i) );
    logInternal( Verbosity::Verbose, "VAR", intMsg );
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
        else if( tok.Consume( "domain", Case::Ignore, Whitespaces::Trim ) )
        {
            if( tok.Consume( '=', Case::Sensitive, Whitespaces::Trim ) )
                domain= tok.Trim();
        }
        else if( tok.Consume( "verbosity", Case::Ignore, Whitespaces::Trim ) )
        {
            if( tok.Consume( '=', Case::Sensitive, Whitespaces::Trim ) )
                verbosity= ReadVerbosity( tok.Trim() );
        }

        // unknown argument
        else
        {
            logInternal( Verbosity::Error, "VAR", String256()
                         ._( "Unknown argument '" )._(tok)
                         ._( "' in variable " )._(variable.Fullname)._( " = \"")._(variable.GetString())._('\"') );
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
    logInternal( Verbosity::Warning, "LGR", String128()
         << "Logger \"" << logger  << "\" not found. Nothing removed." );

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

        logInternal( Verbosity::Info, "LGR", String128() <<
            "Logger \"" << logger << "\" removed." );
        return logger;
    }

    // not found
    logInternal( Verbosity::Warning, "LGR", String128() <<
        "Logger \"" << loggerName << "\" not found. Nothing removed." );

    return nullptr;
}

void Lox::SetVerbosity( Logger* logger, Verbosity verbosity, const TString& domain, int priority )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // check
    if ( logger == nullptr )
    {
        logInternal( Verbosity::Error, "LGR", "Given Logger is \"null\". Verbosity not set." );
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
            logInternal( Verbosity::Error, "LGR",  String128()
                << "Unable to add logger \"" << logger << "\". Logger with same name exists."   );

            logInternal( Verbosity::Verbose, "LGR",  String256()
                << "  Request was: SetVerbosity( \""   << logger                << "\", \""
                                                       << dom->FullPath         << "\", Verbosity::"
                                                       << ToString( verbosity ) << ", "
                                                       << priority
                                             << " )." );

            Logger* existingLogger= dom->GetLogger( logger->GetName() );
            logInternal( Verbosity::Verbose, "LGR",  String128()
                << "  Existing Logger: "  << existingLogger );

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
        logInternal( Verbosity::Info, "LGR",  String128()
            << "Logger \""  << logger
            << (domain.StartsWith(ALox::InternalDomains)
                    ? "\" added for internal log messages." : "\" added." ));

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

    Verbosity actVerbosity= dom->GetVerbosity( no );
    if( actVerbosity != verbosity )
        msg << " Lower priority (" << priority
            << " < " << dom->GetPriority(no)
            << "). Remains "  << ToString( actVerbosity ) << '.';

    logInternal( Verbosity::Info, "LGR", msg );
}

void Lox::SetVerbosity( const String& loggerName, Verbosity verbosity, const TString& domain, int priority )
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
            logInternal( Verbosity::Warning, "LGR",  String256() <<
                   "Logger not found. Request was: SetVerbosity( \""   << loggerName            << "\", \""
                                                                       << dom->FullPath         << "\", Verbosity::"
                                                                       << ToString( verbosity ) << ", "
                                                                       << priority
                                                             << " )." );
            return;
        }
    }

    // do
    dom->SetVerbosity( no, verbosity, priority );

    // log info on this
    String128 msg;  msg._("Logger \"")._( dom->GetLogger(no) )._NC( "\":")._(Format::Tab(11 + maxLoggerNameLength))
                       ._('\'')._NC( dom->FullPath )
                       ._( '\'' ).InsertChars(' ', maxDomainPathLength - dom->FullPath.Length() + 1 )
                       ._( "= Verbosity::" );
                       ToString( verbosity, priority, msg ).TrimEnd()._('.');

    Verbosity actVerbosity= dom->GetVerbosity( no );
    if( actVerbosity != verbosity )
        msg << " Lower priority (" << priority
            << " < " << dom->GetPriority(no)
            << "). Remains "  << ToString( actVerbosity ) << '.';

    logInternal( Verbosity::Info, "LGR", msg );
}

void Lox::setDomainImpl( const TString& scopeDomain, Scope   scope, int pathLevel,
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

void Lox::RemoveThreadDomain( const TString& scopeDomain, Scope scope, Thread* thread )
{
    if ( !isThreadReleatedScope( scope ) )
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

void Lox::SetDomainSubstitutionRule( const TString& domainPath, const TString& replacement )
{
    // check null param: clears all rules
    if ( domainPath.IsEmpty() )
    {
        oneTimeWarningCircularDS= false;
        domainSubstitutions.clear();
        logInternal( Verbosity::Info, "DMN", "Domain substitution rules removed." );
        return;
    }

    String256 msg;

    // create rule
    DomainSubstitutionRule newRule( domainPath, replacement );
    if ( newRule.Search.IsEmpty() )
    {
        logInternal( Verbosity::Warning, "DMN", "Illegal domain substitution rule. Nothing stored." );
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
        if ( it == domainSubstitutions.end() )
        {
            msg << "Domain substitution rule \"" << domainPath << "\" not found. Nothing to remove.";
            logInternal( Verbosity::Warning, "DMN", msg );
            return;
        }

        msg << "Domain substitution rule \"" << domainPath       << "\" -> \""
                                            << (*it).Replacement   << "\" removed.";
        domainSubstitutions.erase( it );
        logInternal( Verbosity::Info, "DMN", msg );
        return;
    }


    msg << "Domain substitution rule \"" << domainPath           << "\" -> \""
                                        << newRule.Replacement  << "\" set.";

    // change of rule
    if ( it != domainSubstitutions.end() )
    {
        msg << " Replacing previous -> \"" << (*it).Replacement  << "\".";
        (*it).Replacement._()._( newRule.Replacement );
    }
    else
        domainSubstitutions.emplace_back( newRule );

    logInternal( Verbosity::Info, "DMN", msg );
}


void Lox::setPrefixImpl(  const void*  logable, int   type,
                          Scope        scope,   int   pathLevel,   Thread* thread  )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // check
    if( !checkScopeInformation( scope, pathLevel, "PFX" ) )
        return;

    int threadID= thread != nullptr ? thread->GetId() : Thread::NullThreadId;

    Logable* previousLogable;

    scopePrefixes.InitAccess( scope, pathLevel, threadID );
    bool isNullObject=       logable == nullptr
                        || ( type == 0 && ((const TString*) logable)->IsEmpty() );

    if ( !isNullObject )
    {
        // create logable: if TString* type, then copy the string. We are responsible, then.
        Logable* newValue= new Logable( type, logable );
        if ( type == 0 )
            newValue->Object= new AString( (const TString*) logable );
        previousLogable= scopePrefixes.Store( newValue );
    }
    else
    {
        previousLogable= scopePrefixes.Remove( nullptr );
    }


    String256 intMsg( "Object ");
    Verbosity intMsgVerbosity= Verbosity::Info;
    if ( !isNullObject )
    {
        Logable( type, logable).ToString( intMsg );
        intMsg << " added as prefix logable for "; ToString(scope, pathLevel, intMsg); intMsg  << '.' ;

        if ( previousLogable  != nullptr )
        {
            if (    ( type == 0 && previousLogable->Type == 0 && (( (const TString*) logable)->Equals ((const TString*) previousLogable->Object) ) )
                 || ( type == previousLogable->Type && logable == previousLogable->Object )
               )
            {
                intMsg << " (Same as before.)";
                intMsgVerbosity= Verbosity::Verbose;
            }
            else
            {
                intMsg << " Replacing previous ";
                previousLogable->ToString( intMsg );
                intMsg  << '.';
            }
        }
    }
    else
    {
        if ( previousLogable  != nullptr )
        {
            previousLogable->ToString( intMsg );
            intMsg << " removed from list of prefix logables for " ; ToString(scope, pathLevel, intMsg);
            intMsg  << '.';
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
        if ( previousLogable->Type == 0 )
            delete (AString*) previousLogable->Object;
        delete previousLogable;
    }
}


void Lox::SetPrefix(  const void* logable, int type, const TString& domain, Inclusion otherPLs )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    Domain* dom= evaluateResultDomain( domain );

    bool isNullObject=       logable == nullptr
                        || ( type == 0 && ((const TString*) logable)->IsEmpty() );

    String256 msg;
    Verbosity intLogVerbosity= Verbosity::Info;

    if ( !isNullObject )
    {
        // create logable: if TString* type, then copy the string. We are responsible, then.
        msg._("Object ");
        Logable newLogable( type, logable );
        if ( type == 0 )
            newLogable.Object= new AString( (const TString*) logable );
        dom->PrefixLogables.emplace_back( newLogable, otherPLs );

        Logable( type, logable).ToString( msg );

        msg << " added as prefix logable for";
    }
    else
    {
        int qtyPLs= (int) dom->PrefixLogables.size();
        if ( qtyPLs > 0 )
        {
            Logable& removedLogable= dom->PrefixLogables[ qtyPLs - 1 ].first;
            dom->PrefixLogables.pop_back();

            msg._("Object ");
            removedLogable.ToString( msg );
            msg << " removed from list of prefix logables for";

            // we have to delete strings
            if ( removedLogable.Type == 0 && removedLogable.Object != nullptr )
                delete (AString*) removedLogable.Object;
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


#if defined (__GLIBCXX__)
    void Lox::SetStartTime( time_t startTime, const String& loggerName )
    {
        Ticks t(0);
        t.SetFromEpochSeconds( startTime );
        SetStartTime( t, loggerName );
    }

#elif defined( _WIN32 )
    void Lox::SetStartTime( LPFILETIME startTime, const String& loggerName )
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

    bool toNow= ( startTime.Raw() == 0L );

    // create string representation for internal log
    String32 startTimeString;
    if ( toNow )
    {
        startTime.Set();
        startTimeString= "'now'";
    }
    else
    {
        TicksCalendarTime ct( startTime );
        ct.Format( "yyyy-MM-dd HH:mm:ss", startTimeString );
    }

    // request logger only from main domain tree
    Logger* logger= domains.GetLogger( loggerName );
    if ( logger == nullptr )
    {
        logInternal( Verbosity::Error, "LGR", String128()
            << "\"" << loggerName << "\": not found. Start time not set." );
        return;
    }

    // do
    logger->TimeOfCreation.Set( startTime );
    logger->TimeOfLastLog .Set( startTime );

    // log info on this
    logInternal( Verbosity::Info, "LGR", String128()
         << '\"' << logger << "\": Start time set to " << startTimeString );
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
    String128 msg( "Mapped thread ID "); msg  << id << " to \"" << threadName << "\"." ;
    if ( origThreadName.IsNotEmpty() )
        msg << " Original thread name: \"" << origThreadName << "\".";
    logInternal( Verbosity::Info, "THR", msg );
}

void Lox::once(  const TString& domain,   Verbosity verbosity,     const void* msgObject, int msgType,
                 const TString& pgroup,
                 Scope          scope,    int       pathLevel,
                 int            quantity                                                            )
{
    // We need a group. If none is given, there are two options:
    String512 group(pgroup);
    bool groupWasEmtpy= group.IsEmpty();
    if ( groupWasEmtpy )
    {
        // GLOBAL scope: exact code line match match
        if ( scope == Scope::Global )
        {
            scope= Scope::Filename;
            group._('#')._( scopeInfo.GetLineNumber() );
        }

        // not GOBAL scope: Unique group per Scope
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
            Entry( domain, verbosity, msgObject, msgType );

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
            Entry( domain, verbosity, msgObject, msgType );
    }
}

void Lox::storeImpl( LogData* data,  const TString& pkey,
                     Scope    scope, int            pathLevel )
{
    // We need a key. If none is given, we use a constant one indicating that storage is
    // associated exclusively with scope
    String512 key(pkey);
    bool keyWasEmtpy= key.IsEmpty();
    if ( keyWasEmtpy )
        key._( noKeyHashKey );

    // get the store
    scopeLogData.InitAccess( scope, pathLevel, Thread::NullThreadId );
    std::map<AString, LogData*>* map= scopeLogData.Get();
    if( map == nullptr )
    {
        map= new std::map<AString, LogData*>;
        scopeLogData.Store( map );
    }

    String128 msg;

    // create map entry (if not created yet)
    auto it=  map->find( key );
    if ( data != nullptr)
    {
        bool replacedPrevious= false;
        if ( it == map->end() )
            it=   map->insert( std::make_pair( key, data ) ).first;
        else
        {
            replacedPrevious= true;
            if ( it->second != data )
            {
                delete it->second;
            }
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
            delete it->second;
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


LogData* Lox::retrieveImpl( const TString& pkey, Scope scope, int  pathLevel )
{
    // We need a key. If none is given, we use a constant one indicating that storage is
    // associated exclusively with scope
    String512 key(pkey);
    bool keyWasEmtpy= key.IsEmpty();
    if ( keyWasEmtpy )
        key._( noKeyHashKey );

    // get the data (create if not found)
    scopeLogData.InitAccess( scope, pathLevel, Thread::NullThreadId );
    LogData* returnValue= nullptr;
    for( int i= 0; i < 2 ; i++ )
    {
        std::map<AString, LogData*>* map= scopeLogData.Get();
        if( map != nullptr )
        {
            auto it=  map->find( key );
            if ( it != map->end() )
                returnValue= it->second;
        }

        if ( returnValue == nullptr )
            storeImpl( new LogData(), pkey, scope, pathLevel );
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
    msg << ( returnValue != nullptr ? " received." : " not found." );

    logInternal( Verbosity::Info, "LGD", msg );
    return returnValue;
}


void Lox::State( const TString&   domain,
                 Verbosity        verbosity,
                 const String&    headLine,
                 unsigned int     flags     )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    AString buf( 2048 );
    if ( headLine.IsNotEmpty() )
        buf._NC( headLine ).NewLine();

    GetState( buf, flags );
    Entry( domain, verbosity, &buf, 0 );
}




void Lox::Entry( const TString&  domain,
                Verbosity       verbosity,
                const void*     msgObject,
                int             typeInfo   )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // auto-initialization of debug loggers
    #if defined( ALOX_DBG_LOG )
        if( domains.CountLoggers() == 0 && this == ALox::Log() )
            Log::AddDebugLogger( this );
    #endif

    ALIB_ASSERT_ERROR(!ALox::Init(), "ALox not initialized" );

    CntLogCalls++;

    if ( domains.CountLoggers() == 0 )
        return;

    Logable logable( typeInfo, msgObject );
    log( evaluateResultDomain( domain ), verbosity, logable, Inclusion::Include );
}

// #################################################################################################
// internals
// #################################################################################################
Domain* Lox::evaluateResultDomain( const TString& domainPath )
{
    String128 resDomain;

    // 0. internal domain tree?
    if ( domainPath.StartsWith( ALox::InternalDomains, DomainSensitivity ) )
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
        if ( domainStr.StartsWith( "INTERNAL_DOMAINS", DomainSensitivity ) )
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
        if ( domainStr.Consume       ( '*' ) )    searchMode+= 2;
        if ( domainStr.ConsumeFromEnd( '*' ) )    searchMode+= 1;
        if(     ( searchMode == 0 && dom->FullPath.Equals          ( domainStr,    DomainSensitivity )     )
            ||  ( searchMode == 1 && dom->FullPath.StartsWith      ( domainStr,    DomainSensitivity )     )
            ||  ( searchMode == 2 && dom->FullPath.EndsWith        ( domainStr,    DomainSensitivity )     )
            ||  ( searchMode == 3 && dom->FullPath.IndexOfSubstring( domainStr, 0, DomainSensitivity ) >=0 )
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
        if ( domainStr.StartsWith( "INTERNAL_DOMAINS", DomainSensitivity ) )
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
        if ( prefixStr.Consume( '\"' ) )
            prefixStr.ConsumeFromEnd( '\"' );

        Inclusion otherPLs= Inclusion::Include;
        prefixTokInner.Next();
        if ( prefixTokInner.Actual.IsNotEmpty() )
            otherPLs= lib::enums::ReadInclusion( prefixTokInner.Actual  );

        int searchMode= 0;
        if ( domainStr.Consume       ( '*' ) )    searchMode+= 2;
        if ( domainStr.ConsumeFromEnd( '*' ) )    searchMode+= 1;
        if(     ( searchMode == 0 && dom->FullPath.Equals          ( domainStr,    DomainSensitivity )     )
            ||  ( searchMode == 1 && dom->FullPath.StartsWith      ( domainStr,    DomainSensitivity )     )
            ||  ( searchMode == 2 && dom->FullPath.EndsWith        ( domainStr,    DomainSensitivity )     )
            ||  ( searchMode == 3 && dom->FullPath.IndexOfSubstring( domainStr, 0, DomainSensitivity ) >=0 )
            )
        {
            Logable newLogable( 0, new AString( prefixStr ) );
            dom->PrefixLogables.emplace_back( newLogable, otherPLs );

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


Domain* Lox::findDomain( Domain& rootDomain, TString domainPath )
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
            dom= rootDomain.Find( domainPath, DomainSensitivity, 1, &wasCreated );
            if ( wasCreated )
            {
                // get maximum domain path length (for nicer State output only...)
                if ( maxDomainPathLength < dom->FullPath.Length() )
                     maxDomainPathLength=  dom->FullPath.Length();

                // log info on new domain
                logInternal( Verbosity::Info, "DMN", String256()
                             ._('\'' )._( dom->FullPath )._("' registered.") );
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
                    logInternal( Verbosity::Verbose, "DMN", "   No loggers set, yet." );
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
                                if ( dom->FullPath.StartsWith( rule.Search, DomainSensitivity ) )
                                {
                                    substPath._( rule.Replacement )._( dom->FullPath, rule.Search.Length() );
                                    substituted= true;
                                    continue;
                                }
                            }
                            else
                            {
                                if ( substPath.StartsWith( rule.Search, DomainSensitivity ) )
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
                                if ( dom->FullPath.EndsWith( rule.Search, DomainSensitivity ) )
                                {
                                    substPath._( dom->FullPath, 0, dom->FullPath.Length() - rule.Search.Length() )._( rule.Replacement );
                                    substituted= true;
                                    continue;
                                }
                            }
                            else
                            {
                                if ( substPath.EndsWith( rule.Search, DomainSensitivity ) )
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
                                int idx= dom->FullPath.IndexOf( rule.Search, 0, DomainSensitivity );
                                if ( idx >= 0 )
                                {
                                    substPath._( dom->FullPath, 0, idx )._( rule.Replacement)._( dom->FullPath, idx + rule.Search.Length() );
                                    substituted= true;
                                    continue; //next rule
                                }
                            }
                            else
                            {
                                int idx= substPath.IndexOf( rule.Search, 0, DomainSensitivity );
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
                  "The Limit of 10 domain substitutions was reached. Circular substitution assumed!"
                  " (This error is only reported once!)" );
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

bool Lox::checkScopeInformation( Scope scope, int pathLevel, const TString& internalDomain )
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

bool Lox::isThreadReleatedScope( Scope scope )
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
        aworx::lib::Report::GetDefault()
        .DoReport(  0, "Illegal parameter, only Scope::ThreadOuter and Scope::ThreadInner allowed.",
                    scopeInfo.GetOrigFile(), scopeInfo.GetLineNumber(), scopeInfo.GetMethod()  ); )

    return false;
}

void Lox::log( core::Domain* dom, Verbosity verbosity, Logable& logable, Inclusion prefixes )
{
    dom->CntLogCalls++;
    tmpLogables.clear();
    for ( int i= 0; i < dom->CountLoggers() ; i++ )
        if( dom->IsActive( i, verbosity ) )
        {
            // lazily collect objects once
            if ( tmpLogables.size() == 0 )
            {
                scopePrefixes.InitWalk( Scope::ThreadInner, &logable );
                Logable* next;
                while( (next= scopePrefixes.Walk() ) != nullptr )
                {
                    // this is false for internal domains (only domain specific logables are added there)
                    if ( prefixes == Inclusion::Include ||  next == &logable)
                        tmpLogables.insert( tmpLogables.begin(), next );

                    // was this the actual? then insert domain-associated logables now
                    bool excludeOthers= false;
                    if( next == &logable )
                    {
                        int qtyThreadInner= (int) tmpLogables.size() -1;
                        Domain* pflDom= dom;
                        while ( pflDom != nullptr )
                        {
                            for( auto it= pflDom->PrefixLogables.rbegin() ; it != pflDom->PrefixLogables.rend() ; it++ )
                            {
                                tmpLogables.insert( tmpLogables.begin(), &(it->first) );
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
                            for ( int ii= 0; ii < qtyThreadInner ; ii++ )
                                tmpLogables.pop_back();
                            break;
                        }
                    }
                }
            }

            Logger* logger= dom->GetLogger(i);
            OWN(*logger);
                logger->CntLogs++;
                logger->Log( *dom, verbosity, tmpLogables, scopeInfo );
                logger->TimeOfLastLog.Set();
        }
}

void Lox::logInternal( Verbosity verbosity, const String& subDomain, const TString& msg )
{
    ALIB_ASSERT_ERROR(!ALox::Init(), "ALox not initialized" );
    Logable logable( 0, &msg );
    log( findDomain( internalDomains, subDomain ), verbosity, logable, Inclusion::Exclude );
}

}}// namespace aworx::lox
