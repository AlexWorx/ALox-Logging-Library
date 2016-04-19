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
    const char* internalDomainList[]= {"LGR", "DMN", "PFX", "THR", "LGD" };
    for ( auto it : internalDomainList )
        internalDomains.Find( it, Case::Sensitive, 1, nullptr );
    maxDomainPathLength=  ALox::InternalDomains.Length() + 3;

    // register with ALox
    if( doRegister )
        ALox::Register( this, ContainerOp::Insert );

    // read domain substitution rules from configuration
    {
        String64   variableName( GetName() ); variableName._( "_DOMAIN_SUBSTITUTION" );
        String512  result;
        if ( ALIB::Config.Get( ALox::ConfigCategoryName, variableName, result ) != 0 )
        {
            Tokenizer tok( result, ';' );
            Substring rule;
            while( (rule= tok.Next()).IsNotEmpty() )
            {
                int idx= rule.IndexOfSubstring( "->" );
                if ( idx > 0 )
                {
                    String64 domainPath ( rule, 0, idx  ); domainPath .Trim();
                    String64 replacement( rule, idx + 2 ); replacement.Trim();
                    SetDomainSubstitutionRule( domainPath, replacement );
                }
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
    // unregister each logger in std domains and remove it in internals
    for ( int i= domains.CountLoggers() -1; i >= 0  ; i-- )
    {
        Logger* logger= domains.GetLogger( i );
        int ii= internalDomains.GetLoggerNo( logger );
        if ( ii >= 0 )
            internalDomains.RemoveLogger( ii );
        logger->RemoveAcquirer( this );
    }

    // unregister remaining loggers in internal domains
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

    ClearSourcePathTrimRules( Inclusion::Include, true );
}


// #################################################################################################
// Methods
// #################################################################################################

TextLogger* Lox::CreateConsoleLogger(const String& name)
{
    //--- first: check configuration setting "CONSOLE_TYPE"  ---
    {
        String64 consoleMode;
        if( ALIB::Config.Get( ALox::ConfigCategoryName, "CONSOLE_TYPE", consoleMode ) != 0 )
        {
            if( consoleMode.Equals( "PLAIN", Case::Ignore ) ) return new ConsoleLogger    ( name );
            if( consoleMode.Equals( "ANSI" , Case::Ignore ) ) return new AnsiConsoleLogger( name );

            #if defined( _WIN32 )
                if( consoleMode.Equals( "WINDOWS",  Case::Ignore ) ) goto STD_COL_CHECK;
            #endif

            ALIB_ASSERT_WARNING_S512( consoleMode.Equals( "DEFAULT", Case::Ignore),
                                        "Unrecognized value in config variable: "
                                        << ALox::ConfigCategoryName
                                        << "_CONSOLE_TYPE=" <<  consoleMode  )
        }
    }

    //--- second: check debug environment
    switch( System::RTE() )
    {
        // no color/ESC support
        case System::RuntimeEnvironment::EclipseCDT:    // Eclipse by default does not know ANSI
                                                            return new ConsoleLogger( name );

        // ANSI
        case System::RuntimeEnvironment::Shell:
        case System::RuntimeEnvironment::Desktop:
        case System::RuntimeEnvironment::QTCreator:
        case System::RuntimeEnvironment::VStudio:       goto STD_COL_CHECK;

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

    //---------- GOTO labels -----------

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

bool Lox::RemoveLogger( Logger* logger )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    bool found= false;
    int no;
    if ( (no= domains        .GetLoggerNo( logger )) >= 0 )
    {
        found= true;
        domains.RemoveLogger( no );
    }
    if ( (no= internalDomains.GetLoggerNo( logger )) >= 0 )
    {
        found= true;
        internalDomains.RemoveLogger( no );
    }

    if ( found )
        logger->RemoveAcquirer( this );
    else
    {
        logInternal( Verbosity::Warning, "LGR", String128()
             << "Logger \"" << logger  << "\" not found. Nothing removed." );
        return false;
    }

    return true;
}

Logger* Lox::RemoveLogger( const String& loggerName )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    Logger* logger= nullptr;
    int no;

    if( (no= domains        .GetLoggerNo( loggerName )) >= 0 )
    {
        logger= domains.GetLogger( no );
        domains.RemoveLogger( no );
    }

    if( (no= internalDomains.GetLoggerNo( loggerName )) >= 0 )
    {
        logger= internalDomains.GetLogger( no );
        internalDomains.RemoveLogger( no );
    }

    // log info on this
    if( logger != nullptr )
    {
        logger->RemoveAcquirer( this );

        logInternal( Verbosity::Info, "LGR", String128() <<
            "Logger \"" << logger << "\" removed." );
    }
    else
        logInternal( Verbosity::Warning, "LGR", String128() <<
            "Logger \"" << loggerName << "\" not found. Nothing removed." );

    return logger;
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
                                                       << ToStringX( verbosity ) << ", "
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
            logger->AddAcquirer( this );

        // store size of name to support tabular internal log output
        String128 tempLoggerName( logger );
        if ( maxLoggerNameLength < tempLoggerName.Length() )
             maxLoggerNameLength=  tempLoggerName.Length();

        // for internal log
        isNewLogger= true;
    }

    // do
    Verbosity newVerbosity= dom->SetVerbosity( no, verbosity, priority );

    // log info on this
    if( isNewLogger )
    {
        logInternal( Verbosity::Info, "LGR",  String128()
            << "Logger \""  << logger
            << (domain.StartsWith(ALox::InternalDomains)
                    ? "\" added for internal log messages." : "\" added." ));

        // we have to get all verbosities of already existing domains
        getAllVerbosities( logger, &domains         , nullptr, 0 );
        getAllVerbosities( logger, &internalDomains , nullptr, 0 );

    }

    String128 msg;  msg._("Logger \"")._( logger )._NC( "\":")._(Format::Tab(11 + maxLoggerNameLength))
                       ._('\"')._NC( dom->FullPath )._( "\" = Verbosity::" );
                    ToString( verbosity, priority, msg ).TrimEnd()._('.');
    if( newVerbosity != verbosity )
        msg << " Lower priority (" << priority
            << " < " << dom->GetPriority(no)
            << "). Remains "  << ToStringX( newVerbosity ) << '.';

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
            SetVerbosity( otherTree->GetLogger( no ), Verbosity::Off, actualTree->FullPath, Lox::PrioSource );
            no= dom->GetLoggerNo( loggerName );
            ALIB_ASSERT( no >= 0 );
        }
        else
        {
            logInternal( Verbosity::Warning, "LGR",  String256() <<
                   "Logger not found. Request was: SetVerbosity( \""   << loggerName            << "\", \""
                                                                       << dom->FullPath         << "\", Verbosity::"
                                                                       << ToStringX( verbosity ) << ", "
                                                                       << priority
                                                             << " )." );
            return;
        }
    }

    // do
    Verbosity newVerbosity= dom->SetVerbosity( no, verbosity, priority );

    // log info on this
    String128 msg;  msg._("Logger \"")._( dom->GetLogger(no) )._NC( "\":")._(Format::Tab(11 + maxLoggerNameLength))
                          ._('\"')._NC( dom->FullPath )._( "\" = Verbosity::" );
                        ToString( verbosity, priority, msg ).TrimEnd()._('.');
    if( newVerbosity != verbosity )
        msg << " Lower priority (" << priority
            << " < " << dom->GetPriority(no)
            << "). Remains "  << ToStringX( newVerbosity ) << '.';

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
            msg << " Replacing previous default \'" << previousScopeDomain << "\'.";
            logInternal( Verbosity::Warning, "DMN", msg );
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
        logInternal( Verbosity::Info, "DMN", "Domain substituion rules removed." );
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
            msg << "Domain substituion rule \"" << domainPath << "\" not found. Nothing to remove.";
            logInternal( Verbosity::Warning, "DMN", msg );
            return;
        }

        msg << "Domain substituion rule \"" << domainPath       << "\" -> \""
                                            << (*it).Replacement   << "\" removed.";
        domainSubstitutions.erase( it );
        logInternal( Verbosity::Info, "DMN", msg );
        return;
    }


    msg << "Domain substituion rule \"" << domainPath           << "\" -> \""
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


    String256 intMsg( "Prefix ");
    Verbosity intMsgVerbosity= Verbosity::Info;
    if ( !isNullObject )
    {
        Logable( type, logable).ToString( intMsg );
        intMsg << " set for "; ToString(scope, pathLevel, intMsg); intMsg  << '.' ;

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
            intMsg << " removed from " ; ToString(scope, pathLevel, intMsg);
            intMsg  << '.';
        }
        else
        {
            intMsg  << "<nullptr> given but nothing to remove for ";
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

    String256 msg( "Prefix ");
    Verbosity intLogVerbosity= Verbosity::Info;

    if ( !isNullObject )
    {
        // create logable: if TString* type, then copy the string. We are responsible, then.
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

            removedLogable.ToString( msg );
            msg << " removed as prefix logable from";

            // we have to delete strings
            if ( removedLogable.Type == 0 && removedLogable.Object != nullptr )
                delete (AString*) removedLogable.Object;
        }
        else
        {
            msg << "No prefix logable to remove from";
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

#if !defined( IS_DOXYGEN_PARSER)
void logConfigDomsWithDiffVerb( Domain* dom, int loggerNo, vector<Domain*>& results )
{
    if (    dom->Parent == nullptr
        ||  dom->Parent->GetVerbosity(loggerNo) != dom->GetVerbosity(loggerNo) )
        results.emplace_back( dom );

    for( auto it : dom->SubDomains )
        logConfigDomsWithDiffVerb( it, loggerNo, results );
}

void logConfigCollectPrefixes( Domain* dom, int indentSpaces, AString& target )
{
    for ( auto pfl : dom->PrefixLogables )
    {
        target.InsertChars( ' ', indentSpaces );
        pfl.first.ToString( target );
        if ( pfl.second == Inclusion::Exclude )
            target._NC( " (Excl.)" );
        target._NC( Format::Tab( 25, -1 ) );
        target._NC( "<domain>           [" )._NC( dom->FullPath )._NC(']').NewLine();
    }

    for( auto it : dom->SubDomains )
        logConfigCollectPrefixes( it, indentSpaces, target );
}
#endif

void Lox::LogConfig( const String&    domain,
                     Verbosity        verbosity,
                     const String&    headLine )
{
    ALIB_ASSERT_ERROR ( this->GetSafeness() == Safeness::Unsafe || this->DbgCountAcquirements() > 0,
                        "Lox not acquired" );

    // we write log all into a Buffer first
    AString buf( 2048 );

    ScopeDump scopeDump( threadDictionary, noKeyHashKey, buf );

    // log a headline?
    if ( headLine.IsNotEmpty() )
        buf._NC( headLine ).NewLine();

    buf._NC( "ALib Version:      " )._NC( ALIB::Version)._NC(" (Rev. ")._( ALIB::Revision)._(')').NewLine();
    buf._NC( "ALib compilation symbols:" ).NewLine();
    {
        for( auto& p : ALIB::CompilationFlagMeanings )
        {
            buf << "  " << Format::Field( String32() << p.first << ':', 20, Alignment::Left )
                << (ALIB::CompilationFlags & p.second  ? " On" : " Off")
                << NewLine;
        }
    }

    buf._NC( "ALox compilation symbols:" ).NewLine();
    {
        for( auto& p : ALox::CompilationFlagMeanings )
        {
            buf << "  " << Format::Field( p.first, 20, Alignment::Left ) << ':'
                << (ALox::CompilationFlags & p.second  ? " On" : " Off")
                << NewLine;
        }
    }
    buf.NewLine();

    // basic lox info
    buf._NC( "Name:            \"" )._( scopeInfo.GetLoxName() )._('\"').NewLine();
    buf._NC( "Version:         " )._NC( ALox::Version)._NC(" (Rev. ")._( ALox::Revision)._(')').NewLine();
    buf._NC( "Thread Safeness: " )._NC( GetSafeness()   ).NewLine();
    buf._NC( "#Log Calls:      " )._NC( CntLogCalls     ).NewLine();
    buf.NewLine();

    //  source path trim info
    buf._NC( "Source Path Trimming Rules: " ).NewLine();
    {
        int cnt= 0;
        // do 2 times, 0== global list, 1 == local list
        for( int trimInfoNo= 0; trimInfoNo < 2 ; trimInfoNo++ )
        {
            // choosel local or global list
            std::vector<ScopeInfo::SourcePathTrimRule>* trimInfoList=
                       trimInfoNo == 0   ?  &scopeInfo.LocalSPTRs
                                         : &ScopeInfo::GlobalSPTRs;


            // loop over trimInfo
            for ( auto& ti : *trimInfoList )
            {
                cnt++;
                buf._NC( trimInfoNo == 0 ? "  Global: "
                                         : "  Local:  " );
                buf._NC( ti.IsPrefix ?  "\"" : "\"*");
                buf._NC( ti.Path )._NC( "\", " );
                buf._NC( ti.IncludeString );
                if ( ti.TrimOffset != 0 )
                    buf._NC( ti.Path )._NC( "\", Offset: " )._NC( ti.TrimOffset );
                buf.NewLine();
            }
        }


        if ( cnt == 0 )
            buf._NC("  <no rules set>" ).NewLine();
        buf.NewLine();
    }

    //  domain substitutions
    buf._NC( "Domain Substitution Rules: " ).NewLine();
    if( domainSubstitutions.size() > 0 )
    {
        // get size
        int maxWidth= 0;
        for ( auto& it : domainSubstitutions )
            if ( maxWidth < it.Search.Length() )
                 maxWidth = it.Search.Length();
        maxWidth+= 2;

        // write
        for ( auto& it : domainSubstitutions )
        {
            buf._NC( "  " );
            if (    it.type == DomainSubstitutionRule::Type::EndsWith
                 || it.type == DomainSubstitutionRule::Type::Substring )
                buf._NC( '*' );

            buf._NC( it.Search );
            if (    it.type == DomainSubstitutionRule::Type::StartsWith
                 || it.type == DomainSubstitutionRule::Type::Substring )
                buf._NC( '*' );

            buf._NC( Format::Tab( maxWidth, -1, 0 ) )
               ._NC( " -> " )
               ._NC( it.Replacement );
            buf.NewLine();
        }
    }
    else
        buf._NC("  <no rules set>" ).NewLine();
    buf.NewLine();

    // Log Once Counters
    buf._NC( "Once() Counters: " ).NewLine();
    if ( scopeDump.writeStoreMap( &scopeLogOnce ) == 0 )
        buf._NC("  <no Once() counters set>" ).NewLine();
    buf.NewLine();

    // Log Data
    buf._NC( "Log Data: " ).NewLine();
    if ( scopeDump.writeStoreMap( &scopeLogData ) == 0 )
        buf._NC("  <no data objects stored>" ).NewLine();
    buf.NewLine();

    // Prefix Logables
    buf._NC( "Prefix Logables: " ).NewLine();
    int oldLength= buf.Length();
    scopeDump.writeStore( &scopePrefixes, 2 );
    logConfigCollectPrefixes( &domains, 2, buf );
    if ( oldLength == buf.Length() )
        buf._NC("  <no prefix logables set>" ).NewLine();
    buf.NewLine();

    // thread mappings
    buf._NC( "Named Threads:   " ).NewLine();
    if ( threadDictionary.size() == 0 )
        buf._NC("  <no thread name mappings set>" ).NewLine();
    else
        for ( auto pair : threadDictionary )
        {
            buf._NC( "  " ) << Format::Field( String32() << '(' << pair.first << "):", 7, Alignment::Left )
                            << '\"' << pair.second << '\"';
            buf.NewLine();
        }
    buf.NewLine();

    // Scope Domains
    buf._NC( "Scope Domains: " ).NewLine();
    if ( scopeDump.writeStore( &scopeDomains, 2 ) == 0 )
        buf._NC("  <no scope domains set>" ).NewLine();
    buf.NewLine();

    // Loggers
    {
        vector<Domain*> domsWithDiffVerb;
        for (int treeNo= 0; treeNo < 2; ++treeNo )
        {
            int cnt= 0;
            Domain* domTree;
            if( treeNo==0 )
            {
                 domTree= &domains;
                 buf._NC( "Loggers:" ).NewLine();
            }
            else
            {
                 domTree= &internalDomains;
                 buf._NC( "Loggers on Internal Domains:" ).NewLine();
            }

            for ( int loggerNo= 0; loggerNo< domTree->CountLoggers(); loggerNo++ )
            {
                cnt++;
                String64 as64;
                Logger* logger= domTree->GetLogger(loggerNo);
                buf._NC( "  "  )._NC( logger  ).NewLine();
                buf._NC( "    Lines logged:  "     )._NC( logger->CntLogs                                                 ).NewLine();
                buf._NC( "    Creation time: "     )._NC( logger->TimeOfCreation.Format( "yyyy-MM-dd HH:mm:ss", as64._()) ).NewLine();
                buf._NC( "    Last log time: "     )._NC( logger->TimeOfLastLog .Format( "yyyy-MM-dd HH:mm:ss", as64._()) ).NewLine();

                domsWithDiffVerb.clear();
                logConfigDomsWithDiffVerb( domTree, loggerNo, domsWithDiffVerb);
                for ( Domain* dom : domsWithDiffVerb )
                {
                    buf._NC( "    " )
                       ._(  dom == *domsWithDiffVerb.begin() ? "Verbosities:   "
                                                             : "               " );

                    int tabRef= buf.Length();
                    buf << dom->FullPath << Format::Tab( maxDomainPathLength +1, tabRef);

                    buf << "= "; ToString(  dom->GetVerbosity( loggerNo ), dom->GetPriority(loggerNo), buf )
                        .NewLine();
                }
            }
            if ( cnt == 0 )
                buf._NC("  <no loggers attached>" ).NewLine();
            buf.NewLine();
        }

    }

    // Internal Domains
    buf._NC( "Internal Domains:" ).NewLine();
    logConfigDomainRecursive( internalDomains, buf );
    buf.NewLine();

    // Domains
    buf._NC( "Domains:" ).NewLine();
    logConfigDomainRecursive( domains,         buf );
    buf.NewLine();

    // now, log it out
    Entry( domain, verbosity, &buf, 0 );
}

void Lox::logConfigDomainRecursive( Domain& domain, AString& buf )
{
    int reference= buf.Length();
    buf._("  "); domain.ToString( buf );
    int idx= buf.IndexOf( '[', reference );
    buf.InsertChars( ' ', maxDomainPathLength + 5 - idx + reference, idx);
    buf.NewLine();

    // loop over all sub domains (recursion)
    for ( Domain* subDomain : domain.SubDomains )
        logConfigDomainRecursive( *subDomain, buf );
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
        if ( resDomain.CharAtStart() == Domain::PathSeparator() )
            break;
    }

    return findDomain( domains, resDomain );
}

void Lox::getVerbosityFromConfig( core::Logger* logger, core::Domain*  dom,
                                  TString*      cfgStr, int            cfgPriority )
{
    // get logger number. It may happen that the logger is not existent in this domain tree.
    int loggerNo= dom->GetLoggerNo( logger ) ;
    if ( loggerNo < 0 )
        return;

    // check priority
    int priority= dom->GetPriority( loggerNo );
    if ( priority == Lox::PrioProtected )
        return;

    String512 configStringLocal;
    if ( cfgStr == nullptr )
    {
        String64  variableName; variableName._( scopeInfo.GetLoxName() )._( '_' )._( logger->GetName() )._( "_VERBOSITY" );

        cfgPriority= ALIB::Config.Get( ALox::ConfigCategoryName, variableName, configStringLocal );
        if( cfgPriority == 0  || cfgPriority < priority )
            return;
        cfgStr= &configStringLocal;
    }

    Tokenizer verbositiesTok( cfgStr, ';' );
    Substring verbositySettingStr;
    while( (verbositySettingStr= verbositiesTok.Next()).IsNotEmpty() )
    {
        Tokenizer verbosityTok( verbositySettingStr, '=' );

        Substring domainStr=    verbosityTok.Next();
        String    verbosityStr= verbosityTok.Next();
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
            dom->SetVerbosity( loggerNo, verbosity,  cfgPriority );

            // log info on this
            String128 msg;  msg << "Verbosity set from configuration: \""
                                << logger << "\": " << dom->FullPath
                                << " = "; ToString( verbosity, dom->GetPriority( loggerNo), msg ).TrimEnd()
                                << '.';

            logInternal( Verbosity::Info, "LGR", msg );
        }
    }
}

void Lox::getAllVerbosities( core::Logger* logger, core::Domain*  dom,
                             TString*      cfgStr, int            cfgPriority )
{
    // get config string once
    String512 configStringLocal;
    if ( cfgStr == nullptr )
    {
        String64  variableName; variableName._( scopeInfo.GetLoxName() )._( '_' )._( logger->GetName() )._( "_VERBOSITY" );
        cfgPriority= ALIB::Config.Get( ALox::ConfigCategoryName, variableName, configStringLocal );
        if( cfgPriority == 0  )
            return;
        cfgStr= &configStringLocal;
     }

    // get verbosity for us
    getVerbosityFromConfig( logger, dom, cfgStr, cfgPriority );

    // loop over all sub domains (recursion)
    for ( Domain* subDomain : dom->SubDomains )
        getAllVerbosities( logger, subDomain, cfgStr, cfgPriority );
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
            if ( !wasCreated )
                break;

            // get maximum domain path length (for nicer LogConfig output only...)
            if ( maxDomainPathLength < dom->FullPath.Length() )
                 maxDomainPathLength=  dom->FullPath.Length();

            // log info on new domain
            logInternal( Verbosity::Info, "DMN", String256()
                         ._('\'' )._( dom->FullPath )._("' registered.") );

            // read domain from Config
            for ( int i= 0; i < dom->CountLoggers(); ++i )
                getVerbosityFromConfig( dom->GetLogger(i), dom, nullptr, 0 );

            if ( dom->CountLoggers() == 0 )
                logInternal( Verbosity::Verbose, "DMN", "   No loggers set, yet." );
            else
            {
                for ( int i= 0; i < dom->CountLoggers(); i++ )
                {
                    String256 msg; msg._("  \"")._( dom->GetLogger(i) )._("\": ");
                                   msg.InsertChars( ' ', maxLoggerNameLength  + 6 - msg.Length() );
                                   msg._( dom->FullPath )._(" = " );
                                      ToString( dom->GetVerbosity(i), dom->GetPriority(i), msg );
                    logInternal( Verbosity::Verbose, "DMN", msg );
                }
            }
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
    if (     ( scope == Scope::Path     &&  scopeInfo.GetTrimmedPath().IsEmpty() )
         ||  ( scope == Scope::Filename &&  scopeInfo.GetFileName()   .IsEmpty() )
         ||  ( scope == Scope::Method   &&  scopeInfo.GetMethod()     .IsEmpty() ) )
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
                if ( prefixes == Inclusion::Include )
                {
                    scopePrefixes.InitWalk( Scope::ThreadInner, &logable );
                    Logable* next;
                    while( (next= scopePrefixes.Walk() ) != nullptr )
                    {
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
                else
                    tmpLogables.emplace_back( &logable );
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
