// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"

#if !defined (HPP_AWORX_ALOX_ALOX)
    #include "alox.hpp"
#endif

#if !defined (HPP_AWORX_ALOX_CONSOLE_LOGGER)
    #include "loggers/consolelogger.hpp"
#endif

#if !defined (_GLIBCXX_ALGORITHM) && !defined(_ALGORITHM_)
    #include <algorithm>
#endif


using namespace std;
using namespace aworx::util;
using namespace aworx::lox;
using namespace aworx::lox::core;

// #################################################################################################
// Fields
// #################################################################################################

const char Lox::Version[]        =    "1.2.0";

// #################################################################################################
// Constructors/destructor
// #################################################################################################

Lox::~Lox()
{
}

// #################################################################################################
// Methods
// #################################################################################################

void Lox::AddLogger( Logger* logger, Log::DomainLevel internalDomainLevel )
{
    OWN(*this);
    OWN(callerInfo);


    // Find or Create the internal domain (LOX) for logger  and set level
    resDomain= InternalDomain;
    if ( logger->FindDomain  ( resDomain ) == nullptr )
        logger->CreateDomain( resDomain )->SetLevel( internalDomainLevel, false );

    // check for doubles
    if ( find( loggers.begin(), loggers.end(), logger) != loggers.end() )
    {
        internalLog( Log::Level::WARNING,  AString128() << "Lox.AddLogger(): Logger \"" << logger->Name <<  "\" already exists. Not added." );
        return;
    }

    loggers.insert( loggers.end(), logger );

    internalLog( Log::Level::INFO,         AString128() << "Lox.AddLogger(): Logger \"" << logger->Name  << "\" added. Internal Domain Level set to: " << Log::ToString(internalDomainLevel) << '.');
}

Logger* Lox::GetLogger( const char* loggerName )
{
    OWN(*this);

    // search logger
    AString cmp( loggerName );
    for ( Logger* logger : loggers )
        if ( cmp.Equals( logger->Name, true ) )
            return logger;

    // not found
    return nullptr;
}

bool Lox::RemoveLogger( const Logger* logger )
{
    OWN(*this);
    OWN(callerInfo);

    size_t qtyLoggers= loggers.size();


    loggers.erase( std::remove  ( loggers.begin(),
                                  loggers.end(),
                                   logger
                                  ),
                   loggers.end() );
    return loggers.size() < qtyLoggers;
}

int Lox::RemoveLoggers( const char* loggerFilter )
{
    OWN(*this);
    OWN(callerInfo);

    size_t qtyLoggers= loggers.size();

    loggers.erase( std::remove_if(  loggers.begin(),
                                    loggers.end(),
                                    [loggerFilter](Logger* logger)
                                    {
                                        return simpleWildcardFilter( logger, loggerFilter );
                                    }
                                  ),
                   loggers.end() );


    return qtyLoggers - loggers.size();
}

void Lox::RegDomain( const char* domain, Log::Scope scope )
{
    OWN(*this);
    OWN(callerInfo);

    // check parameter
    if ( AString::IsNullOrEmpty( domain  ) )
    {
        internalLog( Log::Level::ERROR, AString128() << "Lox::RegDomain(): Empty domain given. Not registered." );
        return;
    }

    // get resulting domain
    evaluateResultDomain( domain );
    AString32 domainToRegister( resDomain );

    // loop over all loggers (without filtering)
    for ( Logger* logger : loggers )
    {
        // search domain
        LogDomain* logDomain= logger->FindDomain( domainToRegister );

        // not found?
        if ( logDomain == nullptr )
        {
            //create domain
            logger->CreateDomain( domainToRegister );

            // log info on this
            internalLog( Log::Level::INFO, AString128() << "Lox::RegDomain(): Domain \"" << domainToRegister << "\" created in logger: " << logger->Name << '.' );
        }
    }

    // set domain as default for calling source file's log calls
    if ( scope != Log::Scope::NONE && callerInfo.SourceFileName != nullptr )
    {
        int mnLen=     callerInfo.MethodName != nullptr ? strlen( callerInfo.MethodName ) : 0;

        AString256 key;
        key.Append( callerInfo.SourceFileName );
        if ( scope == Log::Scope::METHOD )
        {
            if ( mnLen > 0 )
                key.Append( '#' ).Append( callerInfo.MethodName );
            else
            {
                internalLog( Log::Level::ERROR, AString128() << "Lox::RegDomain(\"" << domain
                                                             << "\", Log::Scope::Method): No method information to register default domain for method scope." );
            }
        }

        // store domain in hash table
        AString16 previous;
        auto it=    defaultDomains.find( key );
        if (it != defaultDomains.end() )
        {
            previous= (*it).second;
            defaultDomains.erase( it );
        }
        defaultDomains.insert( make_pair( key, domainToRegister ) );


        // log info on this
        if ( previous == nullptr )
            internalLog( Log::Level::INFO,
                         AString128() << "Lox::RegDomain(): Domain \""    << domainToRegister
                                      << "\" set as default for scope \"" << Log::ToString(scope)
                                      << "\"." );
        else
            internalLog( Log::Level::WARNING,
                         AString128() << "Lox::RegDomain(): Replacing default Domain \"" <<  previous
                                      << "\" by \"" << domainToRegister
                                      << "\" as default for scope \"" << Log::ToString(scope)
                                      << "\"."  );
    }
}

void Lox::SetDomain( const char* domain,      Log::DomainLevel domainLevel,
                     bool        recursive,   const char*      loggerFilter )
{
    OWN(*this);
    OWN(callerInfo);

    // save caller info and get resulting domain
    // we have to duplicate the result domain, as this might be overwritten in internal log statements
    evaluateResultDomain( domain );
    AString64 tempDomain( resDomain );

    // loop over loggers
    for ( Logger* logger : loggers )
    {
        // logger filtered out?
        if ( !simpleWildcardFilter( logger, loggerFilter ) )
            continue;

        // create domain (maybe not existent yet)
        LogDomain* logDomain= logger->CreateDomain( tempDomain );
        logDomain->SetLevel( domainLevel, recursive ) ;

        // log info on this (has to be done last, for the case that domain is the internal domain!)
        internalLog( Log::Level::INFO,    AString128() << "Lox::SetDomain(): Domain \"" << tempDomain   << "\" log level set to \"" << Log::ToString(domainLevel)
                                                       << "\" for logger \""            << logger->Name << "\"." );
    }
}


void Lox::SetDisabled(    bool disabled, const char* loggerFilter )
{
    OWN(*this);
    OWN(callerInfo);

    for ( Logger* logger : loggers )
    {
        if ( simpleWildcardFilter( logger, loggerFilter ) )
        {
            logger->IsDisabled= disabled;

            // log info on this
            internalLog( Log::Level::INFO,    AString128() << "Lox::SetDisabled(): Logger \"" << logger->Name << "\" " << (disabled ? "disabled." : "enabled.")  );
        }
    }
}

#if defined (__GLIBCXX__)
    void Lox::SetStartTime( time_t startTime, const char* loggerFilter )
    {
        Ticks t(0);
        t.SetFromEpochSeconds( startTime );
        SetStartTime( t, loggerFilter );
    }

#elif defined( _MSC_VER )
    void Lox::SetStartTime( LPFILETIME startTime, const char* loggerFilter )
    {
        aworx::util::Ticks t(0);
        t.SetFromFileTime( startTime );
        SetStartTime( t, loggerFilter );
    }
#else
    #pragma message ("Unknown Platform in file: " __FILE__ )
#endif

void Lox::SetStartTime( Ticks  startTime, const char* loggerFilter )
{
    OWN(*this);
    OWN(callerInfo);

    bool toNow= ( startTime.Raw() == 0L );

    // create string representation for internal log
    AString32 startTimeString;
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
        internalLog( Log::Level::INFO,
                     AString128() << "Lox::SetStartTime(): Start time of \"" << logger->Name
                     << "\" set to: " << startTimeString << '.' );
    }
}


#if defined(AWXU_FEAT_THREADS)
    void Lox::MapThreadName( const char* threadName, int id )
    {
        OWN(*this);
        OWN(callerInfo);

        // get current thread id
        string origThreadName;
        if ( id == 0 )
        {
            Thread* t=      Thread::CurrentThread();
            id=             t->GetId();
            origThreadName= t->GetName();
        }

        // add entry
        ThreadDictionary[id]= threadName;

        // log info on this
        AString128 msg;
        msg << "Lox: Mapped thread ID " << id << " to \"" << threadName << "\"." ;
        if ( origThreadName.size() > 0 )
            msg << " Original thread name was \"" << origThreadName << "\".";
        internalLog( Log::Level::INFO, msg );
    }
#else
    void Lox::MapThreadName( const char* , int ) {}
#endif

void Lox::SetMarker( void* marker, Log::Scope scope )
{
    OWN(*this);
    OWN(callerInfo);

    // build key string
    AString256 key;
    if ( scope == Log::Scope::NONE )
        key.Append( "$GLOBAL" );
    else
    {
        key.Append( callerInfo.SourceFileName );
        if ( scope == Log::Scope::METHOD )
            key.Append( '#' ). Append( callerInfo.MethodName );
    }

    // save marker ([] overwrites any existing)
    markers[ key ]= marker;

    // log info on this
    AString128 msg( "Lox: Marker (");
    if ( (int64_t) marker > 0  && (int64_t) marker < 65536 )
        msg << (int) (int64_t) marker ;
    else
        msg << "void*";
    msg << ") set.";

    internalLog( Log::Level::VERBOSE, msg );
}


void* Lox::GetMarker( Log::Scope scope )
{
    OWN(*this);
    OWN(callerInfo);

    // build key string
    AString128 key;
    if ( scope == Log::Scope::NONE )
        key.Append( "$GLOBAL" );
    else
    {
        key.Append( callerInfo.SourceFileName );
        if ( scope == Log::Scope::METHOD )
            key.Append( '#' ). Append( callerInfo.MethodName );
    }

    // get marker
    auto search= markers.find( key );
    void* marker=  search != markers.end() ? search->second
                                                  : nullptr;
    // log info on this
    if ( marker != nullptr)
        internalLog( Log::Level::VERBOSE, AString32() << "Lox: Marker retrieved." );
    else
        internalLog( Log::Level::WARNING, AString32() << "Lox: Marker not found." );

    return marker;
}


void Lox::LogConfig( const char*     domain,
                     Log::Level      level,
                     const char*     headLine,
                     const char*     loggerFilter )
{
    OWN(*this);
    OWN(callerInfo);

    // count overall calls
    CntLogCalls++;

    evaluateResultDomain( domain );

    // we write log all into a Buffer first
    AStringPreAlloc<4096> buf;

    // log a headline?
    if ( !AString::IsNullOrEmpty( headLine ) )
        buf.Append( headLine ).NewLine();

    ( buf <<  "ALox library compilation symbols:").NewLine();
    {
        ALOX_COMPILER_SYMBOL_SETTINGS
        buf << acss.Buffer();
    }

    // basic lox info
    ( buf <<  "Version:      " <<  Version                               ).NewLine();
    ( buf <<  "Intern. dom.: " <<  InternalDomain                        ).NewLine();
    ( buf <<  "Thread safe:  " <<  (IsUnsafe  ()  ? "No (!)" : "Yes" )   ).NewLine();
    ( buf <<  "No. of calls: " <<  CntLogCalls                           ).NewLine();

    // code markers
    if ( markers.size() > 0 )        buf.NewLine();
    ( buf <<  "Code markers: " <<  markers.size() ).NewLine();
    for ( auto pair : markers )
    {
        buf <<  "  Marker (";
        if ( (int64_t) pair.second > 0  && (int64_t) pair.second < 65536 )
            buf.Append( (int) (int64_t) pair.second, 5 );
         else
            buf << "void*";
        buf << ") set for scope:";
        ( buf.Tab(35)  <<  pair.first  ).NewLine();
    }

    // default domains
    if ( defaultDomains.size() > 0 ) buf.NewLine();
    ( buf <<  "Def. domains: " <<  defaultDomains.size() ).NewLine();
    for (  auto pair : defaultDomains )
    {
        buf <<  "  Domain:   ";
        AString& s= pair.second;
        buf <<  s;
        buf.Tab( 25 );
        buf <<  "Scope: \"";
        buf.Append( pair.first ).Append( '\"' ).NewLine();
    }


    // Loggers (and their domains)
    if ( loggers.size() > 0 )        buf.NewLine();
    ( buf <<  "Loggers:      " <<  loggers.size()  ).NewLine();
    for ( Logger* logger : loggers )
    {
        buf.NewLine();
        ( buf <<  "  Logger: \""            <<   logger->Name <<  '\"'                ).NewLine();
        ( buf <<  "    Creation time: "     <<   logger->TimeOfCreation.Format("yyyy-MM-dd HH:mm:ss")  ).NewLine();
        ( buf <<  "    Lines logged:  "     <<   logger->CntLogs                      ).NewLine();
        ( buf <<  "    Domains:"                                                      ).NewLine();

        for (LogDomain* logDomain : logger->RootDomain.SubDomains)
            logConfigDomainRecursive( *logDomain, 3, AString128() << "      " , buf);
    }

    // now, log it out
    for ( Logger* logger : loggers )
        if ( simpleWildcardFilter( logger, loggerFilter ) )
            logger->Line( resDomain, level, buf.Buffer(), buf.Length(), 0, &callerInfo );
}


void Lox::Line( bool doLog, const char* domain, Log::Level level,
                const void* msgObject, int typeInfo,
                int indent, const char* loggerFilter )
{
    OWN(*this);
    OWN(callerInfo);

    CntLogCalls++;

    if ( !doLog )
        return;

    // if no logger was added, automatically add a console logger
    if ( loggers.size() == 0 )
    {
        AddLogger( new loggers::ConsoleLogger() );
        internalLog( Log::Level::WARNING,    AString128() << "Lox: Class 'Log' was used without prior creation of a Log instance. ConsoleLogger Logger created as default." );
    }

    evaluateResultDomain( domain );

    for ( Logger* logger : loggers )
        if ( simpleWildcardFilter( logger, loggerFilter ) )
            logger->Line( resDomain, level, msgObject, typeInfo, indent, &callerInfo );
}



// #################################################################################################
// internals
// #################################################################################################

void Lox::evaluateResultDomain( const char* domain  )
{
    // clear resulting domain name buffer
    resDomain.Clear();

    // get default domain name  (if needed later)
    const AString*  defaultDomain=          nullptr;
    bool            domainGiven=            !AString::IsNullOrEmpty( domain );
    bool            relativeDomainGiven=    domainGiven && *domain == '~';

    if ( callerInfo.SourceFileName != nullptr && ( !domainGiven || relativeDomainGiven) )
    {
        // get default domain
        AString128 key;
        key.Append( callerInfo.SourceFileName );
        int strLengthSourceOnly= key.Length();
        if ( callerInfo.MethodName != nullptr )
            key.Append( '#' ).Append( callerInfo.MethodName );

        // search with method scope
        auto it= defaultDomains.find( key );
        if ( it != defaultDomains.end() )
        {
            defaultDomain= &(*it).second;
        }
        else
        {
            key.SetLength( strLengthSourceOnly );
            if ( (it= defaultDomains.find( key )) != defaultDomains.end() )
                defaultDomain= &(*it).second;
        }
    }

    // no domain given: use default
    if ( !domainGiven )
    {
        if ( defaultDomain != nullptr )
        {
            resDomain.Append( *defaultDomain );
            return;
        }

        // neither domain nor default domain given
        AString256 msg;
        msg << "Lox: No log domain given and ";
             if ( callerInfo.SourceFileName != nullptr )
                msg << "no default domain set for scope \"" << callerInfo.SourceFileName << " - " << callerInfo.MethodName << "\".";
             else
                msg << "no caller information available (Release logging or ALOX_REL_LOG_CI unset?).";
        internalLog( Log::Level::WARNING, msg );
        return;

    }

    // relative domain given: prefix default domain
    if ( relativeDomainGiven )
    {
        if ( defaultDomain != nullptr )
            resDomain << *defaultDomain;
        else
        {
            internalLog( Log::Level::WARNING, AString128()
                                 << "Lox: Relative domain path given: \"" << domain
                                 << "\", but default domain is not set for scope \""
                                 << callerInfo.SourceFileName << " - " << callerInfo.MethodName
                                 << '.'
                        );
            }
    }

    // remove any potential leading separator
    int len=      strlen( domain );
    int start=    relativeDomainGiven ? 1 : 0;
    while (start < len && ( LogDomain::DomainSeparatorChars.find( domain[ start ] ) != string::npos ) )
        start++;

    // add domain to the path
    if (start < len )
    {
        if ( resDomain.Length() > 0 )
            resDomain.Append( '/' );
        resDomain.Append( domain, start );
    }
}


void Lox::internalLog( Log::Level level, AString& msg )
{
    // decrease log counter, as internal Log should not count
    CntLogCalls--;

    // log msg on InternalDomain (restore caller info freshness as multiple log calls might come)
    bool wasFresh= callerInfo.isFresh;
    Line( true, InternalDomain, level, &msg, 3, 0, nullptr );
    callerInfo.isFresh= wasFresh;


    // reset the caller timestamp to avoid negative time differences in subsequent log call
    callerInfo.TimeStamp.Set();
}



//static
bool Lox::simpleWildcardFilter( Logger* logger, const char* loggerFilter )
{
    // nullptr or empty? -> return TRUE (!)
    if ( AString::IsNullOrEmpty( loggerFilter ) )
        return true;

    AString32 wcfLoggerName( logger->Name );
    AString32 wcfFilter    ( loggerFilter );

    // wildcard at start?
    bool startWC= false;
    if ( wcfFilter.StartsWith ( "*" ) )
    {
        wcfFilter.Delete(0, 1);
        startWC=        true;
    }

    // wildcard at end?
    bool endWC= false;
    if ( wcfFilter.EndsWith ( "*" ) )
    {
        wcfFilter.SetLength( wcfFilter.Length() - 1 );
        endWC=        true;
    }

    // wildcard at start?
    if ( startWC )
    {
        // both?
        if ( endWC )
            return wcfLoggerName.IndexOf( wcfFilter, 0, true ) >= 0;

        // at start only
        return wcfLoggerName.EndsWith( wcfFilter, true );
    }

    // at end
    if ( endWC)
        return wcfLoggerName.StartsWith( wcfFilter, true );

    // no wildcard
    return wcfLoggerName.Equals( wcfFilter, true);
}

void Lox::logConfigDomainRecursive( LogDomain& domain, int indent, AString& domPath, AString& buf )
{
    // append /ME to domain path string
    domPath << "/" << domain.Name;

    // add  domain name and log level
    buf.Append( domPath  )    .Tab( 25 )    .Append( Log::ToString( domain.GetLevel() ) )  .NewLine();

    // loop over all sub domains (recursion)
    for ( LogDomain* subDomain : domain.SubDomains )
        logConfigDomainRecursive( *subDomain, indent + 1, domPath, buf );
}


