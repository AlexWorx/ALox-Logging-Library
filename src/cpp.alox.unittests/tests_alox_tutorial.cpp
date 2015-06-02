// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"


//! [Tut_include_statement]
#include "alox_console_logger.hpp"
//! [Tut_include_statement]

#include "alox_memory_logger.hpp"

#include "environment.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define TESTCLASSNAME       CPP_Tutorial
#include "../cpp.aworx.util.unittests/awx_unittests.hpp"



using namespace std;
using namespace tests_aworx_util;

//! [Tut_using_statement]
using namespace aworx::util;
using namespace aworx::lox;
using namespace aworx::lox::loggers;
//! [Tut_using_statement]



// #################################################################################################
// Save output of tutorial logger to file
// #################################################################################################
const char* outputPath= "../../../../../src/docs/ALox.CPP/generated/";


void SaveTutorialOutput( AWXUnitTesting& ut, const char* fileName, AString& log )
{
    string fName= outputPath; fName.append( fileName );


    string test=  Environment::CurrentDirectory();
    ofstream myfile;
    myfile.open( fName );
    if ( myfile.is_open() )
    {
        myfile <<  log.ToString();
        myfile.close();
    }
    PRINT(      "Could not write Tutorial Output File. If needed, check path in line "
            <<  (__LINE__ - 16 ) << "of file "  << __FILE__ )
}

namespace tests_alox {


A_TEST_CLASS()

// #################################################################################################
// Hello_ALox
// #################################################################################################

A_TEST_METHOD(Hello_ALox)
    #define ConsoleLogger MemoryLogger

    //! [Tut_Hello_ALox]

    //! [Tut_Hello_ALox_Line1]
    Log_Prune( ConsoleLogger myConsoleLogger; )
    Log_AddLogger( &myConsoleLogger );
    //! [Tut_Hello_ALox_Line1]
    //! [Tut_Hello_ALox_Line2]
    Log_SetDomain( "APP", Log::DomainLevel::INFO_WARNINGS_AND_ERRORS );
     //! [Tut_Hello_ALox_Line2]

    //! [Tut_Hello_ALox_Line3]
    Log_InfoD( "APP", "Hello ALox" );
    //! [Tut_Hello_ALox_Line3]
    //! [Tut_Hello_ALox]

    #undef ConsoleLogger

    Log_RemoveLoggers( "MEMORY" );
    Log_Prune( SaveTutorialOutput( ut, "Tut_Hello_ALox.txt", myConsoleLogger.Buffer  ); )
}



















// moved to 3-digit line number, to have log output formatted well :-)

// #################################################################################################
// Tut_LogLevels
// #################################################################################################
A_TEST_METHOD(Tut_LogLevels )

    #define ConsoleLogger MemoryLogger

    //! [Tut_LogLevels]
    Log_Prune( ConsoleLogger myConsoleLogger; )
    Log_AddLogger( &myConsoleLogger );

    //! [Tut_LogLevels_SetDomain]
    Log_SetDomain( "APP", Log::DomainLevel::INFO_WARNINGS_AND_ERRORS );
    //! [Tut_LogLevels_SetDomain]

    Log_ErrorD(   "APP", "A severe error happened :-(" );
    Log_WarningD( "APP", "This is a warning :-/ Maybe an error follows?" );
    Log_InfoD(    "APP", "Just for your further information!" );
    Log_VerboseD( "APP", "Today, I am in the mood to talk..." );
    //! [Tut_LogLevels]

    #undef ConsoleLogger

    Log_RemoveLoggers( "MEMORY" );
    Log_Prune( SaveTutorialOutput( ut, "Tut_LogLevels.txt", myConsoleLogger.Buffer ); )
}


// #################################################################################################
// Tut_DefaultDomains
// #################################################################################################
A_TEST_METHOD(Tut_DefaultDomains)

    #define ConsoleLogger MemoryLogger

    {
    //! [Tut_DefaultDomains]
    Log_Prune( ConsoleLogger myConsoleLogger; )
    Log_AddLogger( &myConsoleLogger );
    Log_RegDomain( "APP", Log::Scope::SOURCE_FILE );
    Log_SetDomain( "APP", Log::DomainLevel::INFO_WARNINGS_AND_ERRORS );

    Log_Error(   "A severe error happened :-(" );
    Log_Warning( "This is a warning :-/ Maybe an error follows?" );
    Log_Info(    "Just for your further information!" );
    Log_Verbose( "Today, I am in the mood to talk..." );
    //! [Tut_DefaultDomains]

    Log_RemoveLoggers( "MEMORY" );
    Log_Prune( SaveTutorialOutput( ut, "Tut_DefaultDomains.txt", myConsoleLogger.Buffer ); )
    }

    {
    //! [Tut_DefaultDomains_part2]
    Log_Prune( ConsoleLogger myConsoleLogger; )
    Log_AddLogger( &myConsoleLogger );

    Log_InfoD( "APP", "Hallo ALox" );
    //! [Tut_DefaultDomains_part2]

    Log_RemoveLoggers( "MEMORY" );
    Log_Prune( myConsoleLogger.Buffer.Replace( "MEMORY", "CONSOLE" );                       )
    Log_Prune( SaveTutorialOutput( ut, "Tut_DefaultDomains_part2.txt", myConsoleLogger.Buffer ); )
    }

    #undef ConsoleLogger
}


// #################################################################################################
// Tut_PlacingLogCode
// #################################################################################################
double heavyCalculation() { return 42.0; }

void notExecuted_Tut_PlacingLogCode()
{
    //! [Tut_Placing_Part1]
    Log_Prune( ConsoleLogger myConsoleLogger; )
    Log_AddLogger( &myConsoleLogger );

    Log_SetDomain( "MYAPP",     Log::DomainLevel::ALL );
    Log_SetDomain( "SOCKETS",   Log::DomainLevel::WARNINGS_AND_ERRORS );
    Log_SetDomain( "UI",        Log::DomainLevel::ERRORS );
    Log_SetDomain( "UI/DLGS",   Log::DomainLevel::INFO_WARNINGS_AND_ERRORS );
    Log_SetDomain( "3DCALC",    Log::DomainLevel::OFF );
    //! [Tut_Placing_Part1]

    //! [Tut_Placing_Part3]
    Log_InfoD( "MYDOM/PERF", "Heavy calculation started..." );
        heavyCalculation();
    Log_InfoD( "MYDOM/PERF", "Heavy calculation finished!" );
    //! [Tut_Placing_Part3]

    //! [Tut_Placing_Part3b]
    Log_InfoD( "~PERF", "Heavy calculation started..." );
        heavyCalculation();
    Log_InfoD( "~PERF", "Heavy calculation finished!" );
    //! [Tut_Placing_Part3b]
}


A_TEST_METHOD(PlacingCodeMapThreadName )

    #define ConsoleLogger MemoryLogger

    //! [Tut_PlacingCodeMapThreadName]
    Log_Prune( ConsoleLogger myConsoleLogger; )
    Log_AddLogger( &myConsoleLogger );
    Log_SetDomain( "APP", Log::DomainLevel::INFO_WARNINGS_AND_ERRORS );

    Log_MapThreadName( "BKGRND" );

    Log_InfoD( "APP", "Hello ALox" );
    //! [Tut_PlacingCodeMapThreadName]

    #undef ConsoleLogger

    Log_RemoveLoggers( "MEMORY" );
    Log_Prune( SaveTutorialOutput( ut, "Tut_PlacingCodeMapThreadName.txt", myConsoleLogger.Buffer ); )
}



// #################################################################################################
// Tut_AStringNN
// #################################################################################################
void getUsersFromDB( std::vector<std::string>& users)
{
    users.insert( users.end(), "Lisa" );
    users.insert( users.end(), "John" );
    users.insert( users.end(), "Joe" );
}

void notExecuted_Tut_AStringNN()
{
    //! [Tut_AStringNN]
    double  result= heavyCalculation();
    Log_Info( AString32() << "Heavy calculation finished. Result: " << result );
    //! [Tut_AStringNN]
    (void) result;

}

A_TEST_METHOD(Tut_AStringNN )

    #define ConsoleLogger MemoryLogger
    Log_Prune( if ( Log::lox != nullptr )    )
    Log_Prune( {                             )
    Log_Prune(     delete Log::lox;          )
    Log_Prune(     Log::lox= new Lox();      )
    Log_Prune( }                             )

    //! [Tut_AStringNN-2]
    Log_Prune( ConsoleLogger myConsoleLogger; )
    Log_AddLogger( &myConsoleLogger );
    Log_RegDomain( "DB_QUERIES", Log::Scope::SOURCE_FILE );
    Log_SetDomain( "DB_QUERIES", Log::DomainLevel::ALL );

    // get users from database
    vector<std::string> usersInDB;
    getUsersFromDB( usersInDB );

    Log_Info( AString64() << "There are " << usersInDB.size() << " users in the database"  );

    Log_Prune( AString256 userNames("The users are: ");   )
    Log_Prune( for( auto user : usersInDB )               )
    Log_Prune(     userNames << user << ' ';              )

    Log_Verbose( userNames )
    //! [Tut_AStringNN-2]

    #undef ConsoleLogger
    Log_RemoveLoggers( "MEMORY" );
    Log_Prune( SaveTutorialOutput( ut, "Tut_AStringNN.txt", myConsoleLogger.Buffer ); )
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
A_TEST_METHOD(Tut_SeparatedLogLevels )

    #define ConsoleLogger MemoryLogger
    Log_Prune( if ( Log::lox != nullptr )    )
    Log_Prune( {                             )
    Log_Prune(     delete Log::lox;          )
    Log_Prune(     Log::lox= new Lox();      )
    Log_Prune( }                             )

    //! [Tut_SeparatedLogLevels]
    // create two different loggers
    Log_Prune( MemoryLogger myLogger1("MyLog1"); )
    Log_Prune( MemoryLogger myLogger2("MyLog2"); )
    Log_AddLogger( &myLogger1 );
    Log_AddLogger( &myLogger2 );

    // reduce meta information to limit tutorial output width
    Log_Prune( myLogger1.LineFormatter->Format= "[%O]: ";   )
    Log_Prune( myLogger2.LineFormatter->Format= "[%O]: ";   )

    // register domains DOM as default and add two sub domains
    Log_RegDomain( "DOM",      Log::Scope::METHOD );
    Log_RegDomain( "DOM/SUB1", Log::Scope::NONE );
    Log_RegDomain( "DOM/SUB2", Log::Scope::NONE );

    // set domain level of domain DOM for all loggers to ALL
    Log_SetDomainR( "DOM",  Log::DomainLevel::ALL, false );

    // set domain level of "DOM/SUB1" to OFF for Logger 2
    Log_SetDomainRF( "~SUB1", Log::DomainLevel::OFF, false, "MyLog2"  );

    // set domain level of "DOM/SUB2" to OFF for Logger 1
    Log_SetDomainRF( "~SUB2", Log::DomainLevel::OFF, false, "MyLog1"  );

    // Log something using each domain
    Log_InfoD( "DOM",   "This goes to all loggers" );
    Log_InfoD( "~SUB1", "This goes to MyLog1 exclusively" );
    Log_InfoD( "~SUB2", "This goes to MyLog2 exclusively" );

    // remove the loggers and add a console logger to test our log result from above
    Log_RemoveLoggers( nullptr ) // null: no filter -> remove all
    Log_Prune( ConsoleLogger cl );

    Log_AddLogger( &cl );
    Log_RegDomain( "RESULT", Log::Scope::NONE );
    Log_InfoD("RESULT", "MyLog 1 output:" );
    Log_InfoD("RESULT", myLogger1.Buffer );
    Log_InfoD("RESULT", "MyLog 2 output:" );
    Log_InfoD("RESULT", myLogger2.Buffer );
    //! [Tut_SeparatedLogLevels]

    Log_RemoveLoggers( nullptr );
    Log_Prune( SaveTutorialOutput( ut, "Tut_SeparatedLogLevels.txt", cl.Buffer ); )

    #undef ConsoleLogger
}


// #################################################################################################
// Tut_LogConfig
// #################################################################################################
A_TEST_METHOD(Tut_LogConfig)

    #define ConsoleLogger MemoryLogger
    Log_Prune( if ( Log::lox != nullptr )    )
    Log_Prune( {                             )
    Log_Prune(     delete Log::lox;          )
    Log_Prune(     Log::lox= new Lox();      )
    Log_Prune( }                             )

    //! [Tut_LogConfig]
    // create and add two different loggers
    Log_Prune( MemoryLogger myLogger1("MyLog1"); )
    Log_Prune( MemoryLogger myLogger2("MyLog2"); )
    Log_AddLogger( &myLogger1 );
    Log_AddLogger( &myLogger2 );

    // reduce meta information to limit tutorial output width
    Log_Prune( myLogger1.LineFormatter->Format= "[%O]: ";   )
    Log_Prune( myLogger2.LineFormatter->Format= "[%O]: ";   )

    // register domains DOM as default and add two sub domains
    Log_RegDomain( "DOM",      Log::Scope::METHOD );
    Log_RegDomain( "DOM/SUB1", Log::Scope::NONE );
    Log_RegDomain( "DOM/SUB2", Log::Scope::NONE );

    // set domain level of domain DOM for all loggers to ALL
    Log_SetDomainR( "DOM",  Log::DomainLevel::ALL, false );

    // set domain level of "DOM/SUB1" to OFF for Logger 2
    Log_SetDomainRF( "~SUB1", Log::DomainLevel::OFF, false, "MyLog2"  );

    // set domain level of "DOM/SUB2" to OFF for Logger 1
    Log_SetDomainRF( "~SUB2", Log::DomainLevel::OFF, false, "MyLog1"  );

    // add a console logger to view the current config on the
    Log_Prune( ConsoleLogger cl("MainLogger") );
    Log_AddLogger( &cl );
    Log_Prune( cl.MultiLineMsgMode= 4 );
    Log_RegDomain( "CONFIG", Log::Scope::NONE );
    Log_LogConfig("CONFIG", Log::Level::INFO, "The current configuration of this Lox is:" );
    //! [Tut_LogConfig]


    Log_RemoveLoggers( nullptr );
    Log_Prune( SaveTutorialOutput( ut, "Tut_LogConfig.txt", cl.Buffer ); )
    #undef ConsoleLogger
}


A_TEST_METHOD(Tut_LogConfig2)

    #define ConsoleLogger MemoryLogger
    Log_Prune( if ( Log::lox != nullptr )    )
    Log_Prune( {                             )
    Log_Prune(     delete Log::lox;          )
    Log_Prune(     Log::lox= new Lox();      )
    Log_Prune( }                             )

    //! [Tut_LogConfig2]
    // create two different loggers
    Log_Prune( MemoryLogger myLogger1("MyLog1"); )
    Log_Prune( MemoryLogger myLogger2("MyLog2"); )

    // we are adding logger 1 with level of internal domain "ALOX" set to ALL
    Log_AddLoggerD( &myLogger1, Log::DomainLevel::ALL );
    Log_AddLogger(  &myLogger2 );

    // reduce meta information to limit tutorial output width
    Log_Prune( myLogger1.LineFormatter->Format= "[%O]: ";   )
    Log_Prune( myLogger2.LineFormatter->Format= "[%O]: ";   )

    // register domains DOM as default and add two sub domains
    Log_RegDomain( "DOM",      Log::Scope::METHOD );
    Log_RegDomain( "DOM/SUB1", Log::Scope::NONE );
    Log_RegDomain( "DOM/SUB2", Log::Scope::NONE );

    // set domain level of domain DOM for all loggers to ALL
    Log_SetDomainR( "DOM",  Log::DomainLevel::ALL, false );

    // set domain level of "DOM/SUB1" to OFF for Logger 2
    Log_SetDomainRF( "~SUB1", Log::DomainLevel::OFF, false, "MyLog2"  );

    // set domain level of "DOM/SUB2" to OFF for Logger 1
    Log_SetDomainRF( "~SUB2", Log::DomainLevel::OFF, false, "MyLog1"  );

    // add a console logger to view the current config on the
    Log_RemoveLoggers( nullptr ) // null: no filter -> remove all
    Log_Prune( ConsoleLogger cl );

    Log_AddLogger( &cl );
    Log_Prune( cl.MultiLineMsgMode= 4 );
    Log_Prune( cl.FmtMultiLinePrefix= "" );
    Log_RegDomain( "CONFIG", Log::Scope::NONE );
    Log_InfoD("CONFIG", "MyLog 1 output:" );
    Log_InfoD("CONFIG", myLogger1.Buffer );
    //! [Tut_LogConfig2]

    //! [Tut_LogConfig3]
    Log_SetDomainRF( "ALOX", Log::DomainLevel::ALL, true, "Console");
    //! [Tut_LogConfig3]

    //! [Tut_LogConfig4]
    Log_SetDomainRF( Log::lox->InternalDomain, Log::DomainLevel::ALL, true, "Console");
    //! [Tut_LogConfig4]


    Log_RemoveLoggers( nullptr );
    Log_Prune( SaveTutorialOutput( ut, "Tut_LogConfig2.txt", cl.Buffer ); )
    #undef ConsoleLogger
}

A_TEST_CLASS_END
} // namespace


//! [Tut_Placing_Part2]
class MyClass
{
    #if defined(ALOX_DBG_LOG)
        static bool aloxInitialized;
    #endif
    MyClass();
};

#if defined(ALOX_DBG_LOG)
bool MyClass::aloxInitialized= false;
#endif

MyClass::MyClass()
{
    #if defined(ALOX_DBG_LOG)
        if( !aloxInitialized )
        {
            aloxInitialized= true;
            Log_RegDomain( "MYDOM",         Log::Scope::SOURCE_FILE );
            Log_RegDomain( "MYDOM/PERF",    Log::Scope::NONE);
        }
    #endif

    // ... constructor continues here
}
//! [Tut_Placing_Part2]
