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

#include "alib/config/configuration.hpp"
#include "alib/system/system.hpp"

#include "alox/alox_console_loggers.hpp"


#if !defined (_GLIBCXX_ALGORITHM) && !defined(_ALGORITHM_)
    #include <algorithm>
#endif


using namespace std;
using namespace aworx;
using namespace aworx::lib;
using namespace aworx::lib::enums;
using namespace aworx::lib::system;
using namespace aworx::lib::strings;
using namespace aworx::lox;
using namespace aworx::lox::core;
using namespace aworx::lox::core::textlogger;
using namespace aworx::lox::loggers;

// For code compatibility with ALox Java/C++
#define _NC _<false>


// #################################################################################################
// Constructors/destructor
// #################################################################################################

Lox::~Lox()
{
}

void  Lox::Reset()
{
    OWN(*this);
    RemoveLoggers();
    defaultDomains.clear();
    markers.clear();
    threadDictionary.clear();

    InternalDomain=         "ALOX";
    ErrIfNoDefaultDomain=   10;
    CntLogCalls=            0;
}


// #################################################################################################
// Methods
// #################################################################################################

TextLogger* Lox::CreateConsoleLogger(const String& name)
{
    //--- first: check configuration setting "CL_MODE"  ---
    {
        String64 consoleMode;
        if( ALIB::Config->Get( Log::ConfigCategoryName, "CL_MODE", consoleMode ) != 0 )
        {
            if( consoleMode.Equals( "PLAIN", Case::Ignore ) ) return new ConsoleLogger    ( name );
            if( consoleMode.Equals( "ANSI" , Case::Ignore ) ) return new AnsiConsoleLogger( name );

            #if defined( _WIN32 )
                if( consoleMode.Equals( "WINDOWS",  Case::Ignore ) ) goto STD_COL_CHECK;
            #endif

            ALIB_ASSERT_WARNING_AS( consoleMode.Equals( "DEFAULT", Case::Ignore),
                                        "Unrecognized value in config variable: "
                                        << Log::ConfigCategoryName
                                        << "_CL_MODE=" <<  consoleMode  )
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

void Lox::AddLogger( Logger* logger )
{
    OWN(*this);

    // check for doubles
    if ( find( loggers.begin(), loggers.end(), logger) != loggers.end() )
    {
        internalLog( Log::Level::Warning,  String128() << "AddLogger: Logger \"" << logger->Name <<  "\" already exists. Not added." );
        return;
    }

    loggers.insert( loggers.end(), logger );

    // if internal domain was not registered, yet (which is the normal case), we set
    // it to WarningsAndErrors
    bool wasCreated;
    Domain* internalDomain= logger->RootDomain.Find( InternalDomain, &wasCreated );
    if ( wasCreated )
        internalDomain->SetLevel( Log::DomainLevel::WarningsAndErrors );


    String128 msg; msg << "AddLogger: Logger \"" << logger->Name  << "\" ";
    if (!logger->Name.Equals( logger->TypeName, Case::Ignore ) )
        msg << "(" << logger->TypeName << ") ";
    msg << "added.";
    internalLog( Log::Level::Info,  msg );
}

Logger* Lox::GetLogger( const String& loggerName )
{
    OWN(*this);

    // search logger
    for ( Logger* logger : loggers )
        if ( loggerName.Equals( logger->Name, Case::Ignore ) )
            return logger;

    // not found
    return nullptr;
}

bool Lox::RemoveLogger( const Logger* logger )
{
    OWN(*this);

    size_t qtyLoggers= loggers.size();

    loggers.erase( std::remove(     loggers.begin(),
                                    loggers.end(),
                                    logger           ),
                   loggers.end()
                 );

    return loggers.size() < qtyLoggers;
}

int Lox::RemoveLoggers( const String& loggerFilter )
{
    OWN(*this);

    size_t qtyLoggers= loggers.size();

    loggers.erase( std::remove_if(  loggers.begin(),
                                    loggers.end(),
                                    [loggerFilter](Logger* logger)
                                    {
                                        return simpleWildcardFilter( logger, loggerFilter );
                                    }
                                  ),
                   loggers.end() );

    return (int) (qtyLoggers - loggers.size());
}

void Lox::SetDomain( const TString& domain, Log::Scope scope )
{
    OWN(*this);

    // check parameter
    if ( domain.IsEmpty() )
    {
        internalLog( Log::Level::Error, String128() << "SetDomain: Empty domain given. Not registered." );
        return;
    }

    // get resulting domain
    evaluateResultDomain( domain );

    // set domain as default for calling source file's log calls
    if ( scope != Log::Scope::None )
    {
        if ( callerInfo.SourceFileName == nullptr )
        {
            internalLog( Log::Level::Error,
                         String256() << "SetDomain(\"" << domain << "\", Log::Scope::"
                                 << Log::ToString( scope )
                                 << "): Error: No caller information available "
                                    "(Release logging or ALOX_DBG_LOG_CI unset?)."             );
            return;
        }

        String256 key;
        key._( callerInfo.SourceFileName );
        if ( scope == Log::Scope::Method )
        {
            if ( callerInfo.MethodName.Length() > 0 )
                key._( '#' )._( callerInfo.MethodName );
            else
            {
                internalLog( Log::Level::Error,
                             String128() << "SetDomain(\"" << domain
                             << "\", Log::Scope::Method): No method information to register default domain for method scope." );
                return;
            }
        }

        // store domain in hash table
        String32    previous;
        bool    overwriting=  false;
        auto    it=           defaultDomains.find( key );
        if (it != defaultDomains.end() )
        {
            overwriting= true;
            previous= (*it).second;
            defaultDomains.erase( it );
        }
        defaultDomains.insert( make_pair( key, resDomain ) );


        // log info on this
        String256 msg;
        msg << "SetDomain: Domain \""           << resDomain
            << "\" set as default for scope \"" << Log::ToString(scope)  << "\"." ;

        if ( overwriting )
            msg << " Replacing previous Domain \"" <<  previous << "\"";
        internalLog( overwriting ? Log::Level::Warning : Log::Level::Info,  msg );
    }
}

void Lox::SetDomain( const TString& domain,       Log::DomainLevel domainLevel,
                     const String&  loggerFilter, Propagation      propagation  )
{
    OWN(*this);

    // loop over loggers
    bool resultDomainEvaluatedLazily= false;
    for ( Logger* logger : loggers )
    {
        // logger filtered out?
        if ( !simpleWildcardFilter( logger, loggerFilter ) )
            continue;

        // first logger found?
        if( !resultDomainEvaluatedLazily )
        {
            evaluateResultDomain( domain );
            resultDomainEvaluatedLazily= true;
        }

        // create domain (maybe not existent yet)
        logger->SetDomain( resDomain, domainLevel, propagation );

        // log info on this (has to be done last, for the case that domain is the internal domain!)
        internalLog( Log::Level::Info,
                     String128() << "SetDomain: Domain \""      << resDomain
                                 << "\" log level set to \""    << Log::ToString(domainLevel)
                                 << "\" for logger \""          << logger->Name << "\"."         );
    }
}


void Lox::SetLogger( Switch newState, const String& loggerFilter )
{
    OWN(*this);

    for ( Logger* logger : loggers )
    {
        if ( simpleWildcardFilter( logger, loggerFilter ) )
        {
            logger->IsDisabled= (newState == Switch::Off);

            // log info on this
            internalLog( Log::Level::Info,
                         String128() << "SetLogger: Logger \"" << logger->Name
                                     << "\" " << (newState == Switch::Off ? "disabled." : "enabled.")      );
        }
    }
}

#if defined (__GLIBCXX__)
    void Lox::SetStartTime( time_t startTime, const String& loggerFilter )
    {
        time::Ticks t(0);
        t.SetFromEpochSeconds( startTime );
        SetStartTime( t, loggerFilter );
    }

#elif defined( _WIN32 )
    void Lox::SetStartTime( LPFILETIME startTime, const String& loggerFilter )
    {
        time::Ticks t(0);
        t.SetFromFileTime( startTime );
        SetStartTime( t, loggerFilter );
    }
#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif

void Lox::SetStartTime( time::Ticks  startTime, const String& loggerFilter )
{
    OWN(*this);

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
        time::TicksCalendarTime ct( startTime );
        ct.Format( "yyyy-MM-dd HH:mm:ss", startTimeString );
    }

    // loop over all loggers
    for ( Logger* logger : loggers )
    {
        // logger filtered out? -> skip
        if ( !simpleWildcardFilter( logger, loggerFilter ) )
            continue;

        // set new start time and last log time stamp
        logger->TimeOfCreation.Set( startTime );
        logger->TimeOfLastLog .Set( startTime );

        // log info on this
        internalLog( Log::Level::Info,
                     String128() << "SetStartTime: Start time of \"" << logger->Name
                             << "\" set to: " << startTimeString << '.'                     );
    }
}


#if defined(ALIB_FEAT_THREADS)
    void Lox::MapThreadName( const String& threadName, int id )
    {
        OWN(*this);

        // get current thread id
        String origThreadName;
        if ( id == 0 )
        {
            threads::Thread* t= threads::Thread::CurrentThread();
            id=              t->GetId();
            origThreadName=  t->GetName();
        }

        // add entry
        threadDictionary[id]= threadName;

        // log info on this
        String128 msg( "MapThreadName: Mapped thread ID "); msg  << id << " to \"" << threadName << "\"." ;
        if ( origThreadName.IsNotEmpty() )
            msg << " Original thread name was \"" << origThreadName << "\".";
        internalLog( Log::Level::Info, msg );
    }
#else
    void Lox::MapThreadName( const String& , int ) {}
#endif

void Lox::SetMarker( void* marker, Log::Scope scope )
{
    OWN(*this);

    // build key string
    String256 key;
    if ( scope == Log::Scope::None )
        key._( "$GLOBAL" );
    else
    {
        key._( callerInfo.SourceFileName );
        if ( scope == Log::Scope::Method )
            key._( '#' ). _( callerInfo.MethodName );
    }

    // save marker ([] overwrites any existing)
    markers[ key ]= marker;

    // log info on this
    String128 msg( "SetMarker: Marker (");
    if ( (int64_t) marker > 0  && (int64_t) marker < 65536 )
        msg._NC( (int) (int64_t) marker );
    else
        msg._NC( "void*" );
    msg._NC( ") set." );

    internalLog( Log::Level::Info, msg );
}


void* Lox::GetMarker( Log::Scope scope )
{
    OWN(*this);

    // build key string
    String128 key;
    if ( scope == Log::Scope::None )
        key._( "$GLOBAL" );
    else
    {
        key._( callerInfo.SourceFileName );
        if ( scope == Log::Scope::Method )
            key._( '#' ). _( callerInfo.MethodName );
    }

    // get marker
    auto search= markers.find( key );
    void* marker=  search != markers.end() ? search->second
                                                  : nullptr;
    // log info on this
    if ( marker != nullptr)
        internalLog( Log::Level::Info,    "GetMarker: Marker retrieved." );
    else
        internalLog( Log::Level::Warning, "GetMarker: Marker not found." );

    return marker;
}


void Lox::LogConfig( const String&    domain,
                     Log::Level       level,
                     const String&    headLine,
                     const String&    loggerFilter )
{
    OWN(*this);

    // count overall calls
    CntLogCalls++;

    evaluateResultDomain( domain );

    // we write log all into a Buffer first
    AString buf(4096);

    // log a headline?
    if ( headLine.IsNotEmpty() )
        buf._NC( headLine ).NewLine();

    buf._NC( "ALib Version:      " )._NC( ALIB::Version)._NC(" (Rev. ")._( ALIB::Revision)._(')').NewLine();
    buf._NC( "ALib compilation symbols:" ).NewLine();
    {
        for( auto& p : ALIB::CompilationFlagMeanings )
        {
            buf << "  " << Format::Field( String32() << p.first << ':', 20, enums::Alignment::Left )
                << (ALIB::CompilationFlags & p.second  ? " On" : " Off")
                << NewLine;
        }
    }

    buf._NC( "ALox compilation symbols:" ).NewLine();
    {
        for( auto& p : Log::CompilationFlagMeanings )
        {
            buf << "  " << Format::Field( p.first, 20, enums::Alignment::Left ) << ':'
                << (Log::CompilationFlags & p.second  ? " On" : " Off")
                << NewLine;
        }
    }
    buf.NewLine();

    // basic lox info
    buf._NC( "Version:         " )._NC( Log::Version)._NC(" (Rev. ")._( Log::Revision)._(')').NewLine();
    buf._NC( "Intern. Domain:  " )._NC( InternalDomain  ).NewLine();
    buf._NC( "Thread Safeness: " )._NC( Mode()          ).NewLine();
    buf._NC( "#Log Calls:      " )._NC( CntLogCalls     ).NewLine();

    // code markers
    if ( markers.size() > 0 )        buf.NewLine();
    buf._NC( "Code markers:    " )._NC( markers.size() ).NewLine();
    for ( auto pair : markers )
    {
        buf._NC( "  Marker (" );
        if ( (int64_t) pair.second > 0  && (int64_t) pair.second < 65536 )
            buf._( Format::Int32( (int) (int64_t) pair.second, 5 ) );
         else
            buf._NC( "void*" );
        buf._NC( ") set for scope:" );
        buf._NC( Format::Tab(35, -1) )._NC( pair.first ).NewLine();
    }

    // thread mappings
    if ( threadDictionary.size() > 0 )        buf.NewLine();
    buf._NC( "Named Threads:   " )._NC( threadDictionary.size() ).NewLine();
    for ( auto pair : threadDictionary )
    {
        buf._NC( "  " ) << Format::Field( String32() << '(' << pair.first << "):", 7, enums::Alignment::Left )
                        << '\"' << pair.second << '\"';
        buf.NewLine();
    }

    // default domains
    if ( defaultDomains.size() > 0 ) buf.NewLine();
        buf._NC( "Default Domains: " )._NC( defaultDomains.size() ).NewLine();
    for (  auto& pair : defaultDomains )
    {
        buf._NC( "  Domain:   " );
        AString& s= pair.second;
        buf._NC(s)
           ._NC(Format::Tab( 25, -1 ) )
           ._NC( "Scope: \"" )
           ._NC( pair.first )._NC( '\"' ).NewLine();
    }


    // Loggers (and their domains)
    if ( loggers.size() > 0 )        buf.NewLine();
        buf._NC( "Loggers:         " )._NC( loggers.size() ).NewLine();
    for ( Logger* logger : loggers )
    {
        String64 as64;
        buf.NewLine();
        buf._NC(  "  Logger: \""            )._NC( logger->Name )._NC( '\"'        );
        if ( !logger->Name.Equals( logger->TypeName) )
            buf._NC( " Type: '" )._NC( logger->TypeName )._NC( '\'' );
        buf.NewLine();
        buf._NC(  "    Creation Time: "     )._NC( logger->TimeOfCreation.Format( "yyyy-MM-dd HH:mm:ss", as64) ).NewLine();
        buf._NC(  "    Lines logged:  "     )._NC( logger->CntLogs                      ).NewLine();
        buf._NC(  "    Domains:"            )                                                 .NewLine();

        for (Domain* subDomain : logger->RootDomain.SubDomains)
            logConfigDomainRecursive( *subDomain, 3, String128()._NC( "      " ), buf);
    }

    // now, log it out
    Line( true, domain, level, &buf, 0, 0, loggerFilter );
}


void Lox::Line( bool            doLog,
                const TString&  domain,
                Log::Level      level,
                const void*     msgObject,
                int             typeInfo,
                int             indent,
                const String&   loggerFilter  )
{
    OWN(*this);

    // auto-initialization of debug loggers
    #if defined( ALOX_DBG_LOG )
        if( loggers.size() == 0 && this == Log::lox )
            Log::AddDebugLogger( this, true );
    #endif

    ALIB_ASSERT_ERROR(!Log::Init(), "ALox not initialized" );

    CntLogCalls++;

    if ( !doLog || loggers.size() == 0 )
        return;

    evaluateResultDomain( domain );

    for ( Logger* logger : loggers )
        if ( simpleWildcardFilter( logger, loggerFilter ) )
            if( !logger->Line( resDomain, level, msgObject, typeInfo, indent, &callerInfo ) )
            {
                String256 msg;
                msg._("Domain Resolution: Domain '"         )._(resDomain)
                   ._("' implicitly registered for Logger '")._(logger->Name)
                   ._("' Inherited DomainLevel: "           )._(Log::ToString( logger->RootDomain.Find( resDomain )->GetLevel() ));

                internalLog( Log::Level::Info, msg );
            }

}

// #################################################################################################
// internals
// #################################################################################################

void Lox::evaluateResultDomain( const TString& domain  )
{
    // clear resulting domain name buffer
    resDomain.Clear();

    // get default domain name  (if needed later)
    const AString*  defaultDomain=          nullptr;
    bool            domainGiven=            domain.IsNotEmpty();
    bool            relativeDomainGiven=    domain.CharAtStart() == '~';

    if ( callerInfo.SourceFileName.IsNotNull() && ( !domainGiven || relativeDomainGiven) )
    {
        // get default domain
        String128 key;
        key._( callerInfo.SourceFileName );
        int strLengthSourceOnly= key.Length();
        if ( callerInfo.MethodName != nullptr )
            key._( '#' )._( callerInfo.MethodName );

        // search with method scope
        auto it= defaultDomains.find( key );
        if ( it != defaultDomains.end() )
        {
            defaultDomain= &(*it).second;
        }
        else
        {
            key.SetLength<false>( strLengthSourceOnly );
            if ( (it= defaultDomains.find( key )) != defaultDomains.end() )
                defaultDomain= &(*it).second;
        }
    }

    // no domain given: use default
    if ( !domainGiven )
    {
        if ( defaultDomain != nullptr )
        {
            resDomain._( *defaultDomain );
            return;
        }

        // neither domain nor default domain given
        if ( ErrIfNoDefaultDomain > 0 )
        {
            ErrIfNoDefaultDomain--;
            String256 msg;
            msg._NC( "Domain Resolution: No log domain given and " );
                 if ( callerInfo.SourceFileName != nullptr )
                    msg._NC( "no default domain set for scope <" )
                       ._NC( callerInfo.SourceFileName )._NC( " - " )._NC( callerInfo.MethodName )._NC( ">." );
                 else
                    msg._NC( "no caller information available (Release logging or ALOX_DBG_LOG_CI unset?)>." );
            internalLog( Log::Level::Error, msg );
        }

        resDomain._( NullDomain );
        return;
    }

    // relative domain given: prefix default domain
    if ( relativeDomainGiven )
    {
        if ( defaultDomain != nullptr )
            resDomain._NC( *defaultDomain );
        else
        {
            internalLog( Log::Level::Error, String256()
                                 << "Domain Resolution: Relative domain path given: \"" << domain
                                 << "\", but default domain is not set for scope \""
                                 << callerInfo.SourceFileName << " - " << callerInfo.MethodName
                                 << '.'
                        );
            }
    }

    // remove any potential leading separator
    int start= domain.IndexOfAny( Domain::DomainSeparatorChars, Inclusion::Exclude, relativeDomainGiven ? 1 : 0  );

    // add domain to the path
    if (start >= 0 )
    {
        if ( resDomain.IsNotEmpty() )
            resDomain._( '/' );
        int oldLength= resDomain.Length();
        resDomain._NC( domain, start, domain.Length() - start );
        resDomain.ToUpper( oldLength );
    }
}


void Lox::internalLog( Log::Level level, const TString& msg )
{
    // decrease log counter, as internal Log should not count
    CntLogCalls--;

    String64 backup(resDomain);
    Line( true, InternalDomain, level, &msg, 0, 0, nullptr );
    resDomain= backup;

    // reset the caller timestamp to avoid negative time differences in subsequent log call
    callerInfo.TimeStamp.Set();
}



//static
bool Lox::simpleWildcardFilter( Logger* logger, const String& loggerFilter )
{
    // nullptr or empty? -> return TRUE (!)
    if ( loggerFilter.IsEmpty() )
        return true;

    String64 wcfLoggerName( logger->Name );
    String64 wcfFilter    ( loggerFilter );

    // wildcard at start?
    bool startWC= false;
    if ( wcfFilter.CharAtStart<false>() == '*' )
    {
        wcfFilter.Delete<false>(0, 1);
        startWC=        true;
    }

    // wildcard at end?
    bool endWC= false;
    if ( wcfFilter.CharAtEnd() == '*' )
    {
        wcfFilter.DeleteEnd<false>( 1 );
        endWC=        true;
    }

    // wildcard at start?
    if ( startWC )
    {
        // both?
        if ( endWC )
            return wcfLoggerName.IndexOf<false>( wcfFilter, 0, Case::Ignore ) >= 0;

        // at start only
        return wcfLoggerName.EndsWith( wcfFilter, Case::Ignore );
    }

    // at end
    if ( endWC)
        return wcfLoggerName.StartsWith( wcfFilter, Case::Ignore );

    // no wildcard
    return wcfLoggerName.Equals( wcfFilter, Case::Ignore );
}

void Lox::logConfigDomainRecursive( Domain& domain, int indent, AString& domPath, AString& buf )
{
    // append /ME to domain path string
    domPath._NC( '/'  )._NC( domain.Name );

    // add  domain name and log level
    buf._NC( domPath  ) ._( Format::Tab( 25, -1 ) )  ._( Log::ToString( domain.GetLevel() ) )  .NewLine();

    // loop over all sub domains (recursion)
    for ( Domain* subDomain : domain.SubDomains )
        logConfigDomainRecursive( *subDomain, indent + 1, domPath, buf );
}


