// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"


//! [Tut_include_statement]
#include "alox/alox_console_loggers.hpp"
#include "alox/loggers/memorylogger.hpp"
#include "alib/compatibility/std_iostream.hpp"
#include "alib/compatibility/std_string.hpp"
//! [Tut_include_statement]


#if !defined (HPP_AWORX_LIB_SYSTEM_DIRECTORY)
    #include "alib/system/directory.hpp"
#endif

#include "alib/system/system.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define TESTCLASSNAME       CPP_ALox_Tutorial
#include "aworx_unittests.hpp"



using namespace ut_aworx;

//! [Tut_using_statement]
using namespace std;
using namespace aworx;
using namespace aworx::lib;
using namespace aworx::lib::enums;
using namespace aworx::lox;
using namespace aworx::lox::loggers;
//! [Tut_using_statement]


extern void HelloALox();

// #################################################################################################
// Save output of tutorial logger to file
// #################################################################################################
namespace ut_alox {


UT_CLASS()

UT_METHOD(MiniMumAlox)
    HelloALox();
}

// #################################################################################################
// Hello_ALox
// #################################################################################################

UT_METHOD(Hello_ALox)
//    #define ConsoleLogger MemoryLogger

    Log_Prune( if ( Log::DebugLogger != nullptr ) )
                   Log_RemoveDebugLogger();

    Log_Prune    ( MemoryLogger memLog; )
    Log_Prune    ( memLog.SetDomain( LOG_LOX.InternalDomain, Log::DomainLevel::Errors ) );
    Log_AddLogger( &memLog );

    //! [Tut_Understanding_ALox_All]

    //! [Tut_Understanding_ALox_Line1]
    Log_AddDebugLogger();
    //! [Tut_Understanding_ALox_Line1]
    //! [Tut_Understanding_ALox_Line2]
    Log_SetDomain( "APP", Log::DomainLevel::InfoWarningsAndErrors );
    //! [Tut_Understanding_ALox_Line2]

    //! [Tut_Understanding_ALox_Line3]
    Log_Info ( "APP", "Hello ALox" );
    //! [Tut_Understanding_ALox_Line3]

    //! [Tut_Understanding_ALox_All]

    Log_RemoveLoggers( "MEMORY" );
    Log_RemoveDebugLogger();
    Log_Prune( ut.WriteResultFile( "Tut_Understanding_ALox.txt", memLog.MemoryLog, "" ); )
}





// moved to 3-digit line number, to have log output formatted well :-)

// #################################################################################################
// Tut_LogLevels
// #################################################################################################
UT_METHOD(Tut_LogLevels )

    MemoryLogger memLog;
    Log_AddLogger( &memLog );

    //! [Tut_LogLevels]
    Log_AddDebugLogger();

    //! [Tut_LogLevels_SetDomain]
    Log_SetDomain( "APP", Log::DomainLevel::InfoWarningsAndErrors );
    //! [Tut_LogLevels_SetDomain]

    Log_Error  ( "APP", "A severe error happened :-(" );
    Log_Warning( "APP", "This is a warning :-/ Maybe an error follows?" );
    Log_Info   ( "APP", "Just for your further information!" );
    Log_Verbose( "APP", "Today, I am in the mood to talk..." );
    //! [Tut_LogLevels]

    Log_RemoveLoggers( "MEMORY" );
    Log_RemoveDebugLogger();
    Log_Prune( ut.WriteResultFile( "Tut_LogLevels.txt", memLog.MemoryLog, "" ); )
}


// #################################################################################################
// Tut_DefaultDomains
// #################################################################################################
UT_METHOD(Tut_DefaultDomains)

    {
    MemoryLogger memLog;
    Log_AddLogger( &memLog );

    //! [Tut_DefaultDomains]
    Log_AddDebugLogger();
    Log_SetDomain( "APP", Log::Scope::SourceFile );
    Log_SetDomain( "APP", Log::DomainLevel::InfoWarningsAndErrors );

    Log_Error  ( "A severe error happened :-(" );
    Log_Warning( "This is a warning :-/ Maybe an error follows?" );
    Log_Info   ( "Just for your further information!" );
    Log_Verbose( "Today, I am in the mood to talk..." );
    //! [Tut_DefaultDomains]

    Log_RemoveDebugLogger();
    Log_RemoveLoggers();
    Log_Prune( ut.WriteResultFile( "Tut_DefaultDomains.txt", memLog.MemoryLog, "" ); )
    }

    {
    //! [Tut_DefaultDomains_part2]
    Log_AddDebugLogger();
    Log_Info ( "APP", "Hello ALox" );
    //! [Tut_DefaultDomains_part2]

    Log_RemoveDebugLogger();
    }

    {
    //! [Tut_DefaultDomains_part3]
    Log_AddDebugLogger();
    Log_SetDomain( LOG_LOX.InternalDomain, Log::DomainLevel::InfoWarningsAndErrors );
    Log_Info ( "APP", "Hello ALox" );
    //! [Tut_DefaultDomains_part3]
    Log_RemoveDebugLogger();

    // now the same with a memory logger
    MemoryLogger memLog;
    Log_AddLogger( &memLog );
    Log_Prune    ( memLog.RootDomain.SetLevel( Log::DomainLevel::All, Propagation::None ); )
    Log_SetDomain( LOG_LOX.InternalDomain, Log::DomainLevel::InfoWarningsAndErrors );
    Log_Info ( "APP", "Hello ALox" );

    Log_RemoveLoggers( "MEMORY" );

    Log_Prune( memLog.MemoryLog.SearchAndReplace( "MEMORY", "CONSOLE" );                       )
    Log_Prune( ut.WriteResultFile( "Tut_DefaultDomains_part3.txt", memLog.MemoryLog, "" ); )
    }
}


// #################################################################################################
// Tut_PlacingLogCode
// #################################################################################################
double heavyCalculation() { return 42.0; }

void notExecuted_Tut_PlacingLogCode()
{
    //! [Tut_Placing_Part1]
    Log_AddDebugLogger();
    Log_SetDomain( "MYAPP",     Log::DomainLevel::All );
    Log_SetDomain( "SOCKETS",   Log::DomainLevel::WarningsAndErrors );
    Log_SetDomain( "UI",        Log::DomainLevel::Errors );
    Log_SetDomain( "UI/DLGS",   Log::DomainLevel::InfoWarningsAndErrors );
    Log_SetDomain( "3DCALC",    Log::DomainLevel::Off );
    //! [Tut_Placing_Part1]

    //! [Tut_Placing_Part3]
    Log_Info ( "MYDOM/PERF", "Heavy calculation started..." );
        heavyCalculation();
    Log_Info ( "MYDOM/PERF", "Heavy calculation finished!" );
    //! [Tut_Placing_Part3]

    //! [Tut_Placing_Part3b]
    Log_Info ( "~PERF", "Heavy calculation started..." );
        heavyCalculation();
    Log_Info ( "~PERF", "Heavy calculation finished!" );
    //! [Tut_Placing_Part3b]
    Log_RemoveDebugLogger();
}


UT_METHOD(PlacingCodeMapThreadName )

    Log_Prune    ( LOG_LOX.Reset(); )
    Log_Prune    ( MemoryLogger memLog; )
    Log_Prune    ( memLog.RootDomain.SetLevel( Log::DomainLevel::All, Propagation::None ); )
    Log_AddLogger( &memLog );
    Log_SetDomain( LOG_LOX.InternalDomain, Log::DomainLevel::Errors );
    Log_Prune    ( memLog.MemoryLog.Clear(); )


    //! [Tut_PlacingCodeMapThreadName]
    Log_MapThreadName( "BKGRND" );
    Log_Info ( "Hello ALox" );
    //! [Tut_PlacingCodeMapThreadName]
    Log_MapThreadName( "MAIN" );


    Log_RemoveLoggers();
    Log_Prune( memLog.MemoryLog.SearchAndReplace( "MEMORY", "CONSOLE" );                       )
    Log_Prune( ut.WriteResultFile( "Tut_PlacingCodeMapThreadName.txt", memLog.MemoryLog, "" ); )

}

// #################################################################################################
// Tut_ALibStringNN
// #################################################################################################
void getUsersFromDB( std::vector<std::string>& users)
{
    users.insert( users.end(), "Lisa" );
    users.insert( users.end(), "John" );
    users.insert( users.end(), "Joe" );
}

void notExecuted_Tut_ALibStringNN()
{
    //! [Tut_ALibStringNN]
    double  result= heavyCalculation();
    Log_Info( String64() << "Heavy calculation finished. Result: " << result );
    //! [Tut_ALibStringNN]
    (void) result;

}

UT_METHOD(Tut_ALibStringNN )

    //! [Tut_ALibStringNN-2]
    Log_AddDebugLogger();
    Log_SetDomain( "DB_QUERIES", Log::Scope::SourceFile );
    Log_SetDomain( "DB_QUERIES", Log::DomainLevel::All );

    // get users from database
    vector<std::string> usersInDB;
    getUsersFromDB( usersInDB );

    Log_Info( String64() << "There are " << usersInDB.size() << " users in the database"  );

    Log_Prune( String256 userNames("The users are: ");   )
    Log_Prune( for( auto user : usersInDB )               )
    Log_Prune(     userNames << user << ' ';              )

    Log_Verbose( userNames )
    //! [Tut_ALibStringNN-2]
    //!
    Log_RemoveDebugLogger();

    // we repeat that with a memory logger

    MemoryLogger memLog;
    Log_AddLogger( &memLog );
    Log_SetDomain( LOG_LOX.InternalDomain, Log::DomainLevel::Off );
    Log_Prune    ( memLog.RootDomain.SetLevel( Log::DomainLevel::All, Propagation::None ); )

        Log_SetDomain( "DB_QUERIES", Log::Scope::SourceFile );
        Log_SetDomain( "DB_QUERIES", Log::DomainLevel::All );

        // get users from database
        getUsersFromDB( usersInDB );

        Log_Info( String64() << "There are " << usersInDB.size() << " users in the database"  );
        Log_Verbose( userNames )

    Log_RemoveLoggers();
    Log_Prune( memLog.MemoryLog.SearchAndReplace( "MEMORY", "CONSOLE" );                       )
    Log_Prune( ut.WriteResultFile( "Tut_ALibStringNN.txt", memLog.MemoryLog, "" ); )
}


// #################################################################################################
// Tut_ConditionalLogging
// #################################################################################################
void process(int) {}
void notCompiledConditionalLogging()
{
    string* array= nullptr;
    int len= 5;
    string search="";

    //! [Tut_ConditionalLogging]
    int i= 0;
    while( i < len )
    {
        if ( array[i] == search )
        {
            process( i );
            break;
        }
        i++;
    }
    if ( i == len )
        Log_Error( "Nothing found :-(" );
    //! [Tut_ConditionalLogging]

    //! [Tut_ConditionalLogging2]
    Log_Assert( i < len, "Nothing found :-(" );
    //! [Tut_ConditionalLogging2]
}


// #################################################################################################
// Tut_SeparatedLogLevels
// #################################################################################################
UT_METHOD(Tut_SeparatedLogLevels )

    Log_Prune( MemoryLogger memLogger2("DEBUG_LOGGER"); )
    Log_AddLogger( &memLogger2 );

    //! [Tut_SeparatedLogLevels]
    // create two different loggers
    Log_AddDebugLogger();
    Log_Prune( MemoryLogger memLogger("MY_MEM_LOGGER"); )
    Log_AddLogger( &memLogger );

    // reduce meta information to limit tutorial output width
    Log_Prune( memLogger.MetaInfo->Format= "[%O]: ";   )

    // register domains DOM as default and add two sub domains
    Log_SetDomain( "DOM",      Log::Scope::Method );
    Log_SetDomain( "DOM/CON",  Log::Scope::None );
    Log_SetDomain( "DOM/MEM",  Log::Scope::None );

    // set domain level of domain DOM for all loggers to ALL
    Log_SetDomain ( "DOM",  Log::DomainLevel::All );

    // set domain level of "DOM/SUB1" to OFF for Logger 2
    Log_SetDomain ( "~CON", Log::DomainLevel::Off, "MY_MEM_LOGGER" );

    // set domain level of "DOM/SUB2" to OFF for Logger 1
    Log_SetDomain ( "~MEM", Log::DomainLevel::Off, "DEBUG_LOGGER"  );

    // Log something using each domain
    Log_Info ( "DOM",   "This goes to all loggers" );
    Log_Info ( "~CON",  "This goes to my console debug logger only" );
    Log_Info ( "~MEM",  "This goes to the memory logger only" );

    // now we log the contents of the memory logger to the console
    Log_Info ( "~CON",  "This is the contents of the memory logger:" );
    Log_Info ( "~CON",  memLogger.MemoryLog );

    //! [Tut_SeparatedLogLevels]

    Log_RemoveDebugLogger();
    Log_RemoveLoggers();

    Log_Prune( ut.WriteResultFile( "Tut_SeparatedLogLevels.txt", memLogger2.MemoryLog, "" ); )
}


// #################################################################################################
// Tut_LogConfig
// #################################################################################################
UT_METHOD(Tut_LogConfig)

    Log_Prune( LOG_LOX.Reset(); )

    //! [Tut_LogConfig]
    // create two different loggers
    Log_AddDebugLogger();
    Log_Prune( MemoryLogger memLogger("MY_MEM_LOGGER"); )
    Log_AddLogger( &memLogger );

    // reduce meta information to limit tutorial output width
    Log_Prune( Log::DebugLogger->MetaInfo->Format=  "[%t]%L[%O](%#): ";   )
    Log_Prune( memLogger.MetaInfo->Format=          "[%t]%L[%O](%#): ";   )

    // Our previous sample
    Log_SetDomain( "DOM",      Log::Scope::Method );
    Log_SetDomain( "DOM/CON",  Log::Scope::None );
    Log_SetDomain( "DOM/MEM",  Log::Scope::None );
    Log_SetDomain( "DOM",  Log::DomainLevel::All );
    Log_SetDomain( "~CON", Log::DomainLevel::Off, "MY_MEM_LOGGER" );
    Log_SetDomain( "~MEM", Log::DomainLevel::Off, "DEBUG_LOGGER"  );
    Log_MapThreadName( "Thread1" );

    // now, log the current config
    Log_LogConfig( nullptr, Log::Level::Info, "The current configuration of this Lox is:" );
    //! [Tut_LogConfig]

    Log_RemoveDebugLogger();
    Log_RemoveLoggers();

    Log_Prune( ut.WriteResultFile( "Tut_LogConfig.txt", memLogger.MemoryLog, "" ); )
}


UT_METHOD(Tut_LogConfig2)

    Log_Prune( LOG_LOX.Reset(); )
    {
    //! [Tut_LogConfig2]
    // change internal domain ("ALOX") to level 'All'
    Log_AddDebugLogger();
    Log_SetDomain( "ALOX",  Log::DomainLevel::All );

    // Our previous sample
    Log_Prune( Log::DebugLogger->MetaInfo->Format=  "[%t]%L[%O](%#): ";   )
    Log_Prune( MemoryLogger memLogger("MY_MEM_LOGGER"); )
    Log_AddLogger( &memLogger );
    Log_SetDomain( "DOM",      Log::Scope::Method );
    Log_SetDomain( "DOM/CON",  Log::Scope::None );
    Log_SetDomain( "DOM/MEM",  Log::Scope::None );
    Log_SetDomain( "DOM",  Log::DomainLevel::All );
    Log_SetDomain( "~CON", Log::DomainLevel::Off, "MY_MEM_LOGGER" );
    Log_SetDomain( "~MEM", Log::DomainLevel::Off, "DEBUG_LOGGER"  );
    Log_MapThreadName( "Thread1" );
    //! [Tut_LogConfig2]
    }
    Log_RemoveDebugLogger();
    Log_RemoveLoggers();
    Log_RemoveLoggers( nullptr );


    //----------- do it again for the log output -----------------
    Log_Prune( LOG_LOX.Reset(); )
    {

        Log_Prune( MemoryLogger tutlog; )
        Log_Prune( tutlog.MetaInfo->Format= "[%t]%L[%O](%#): ";   )
        Log_AddLogger( &tutlog );
        Log_SetDomain( "ALOX",  Log::DomainLevel::All )

        // Our previous sample
        Log_Prune( MemoryLogger memLogger("MY_MEM_LOGGER"); )
        Log_AddLogger( &memLogger );
        Log_SetDomain( "DOM",      Log::Scope::Method );
        Log_SetDomain( "DOM/CON",  Log::Scope::None );
        Log_SetDomain( "DOM/MEM",  Log::Scope::None );
        Log_SetDomain( "DOM",  Log::DomainLevel::All );
        Log_SetDomain( "~CON", Log::DomainLevel::Off, "MY_MEM_LOGGER" );
        Log_SetDomain( "~MEM", Log::DomainLevel::Off, "DEBUG_LOGGER"  );
        Log_MapThreadName( "Thread1" );

        Log_Prune( tutlog.MemoryLog.SearchAndReplace( "MEMORY", "CONSOLE" );           )
        Log_Prune( tutlog.MemoryLog.SearchAndReplace( "(CONSOLE)", "(MEMORY)" );       )
        Log_Prune( ut.WriteResultFile( "Tut_LogConfig2.txt", tutlog.MemoryLog, "" ); )
    }
    Log_RemoveDebugLogger();
    Log_RemoveLoggers();
    Log_RemoveLoggers( nullptr );



}

UT_CLASS_END

} // namespace
