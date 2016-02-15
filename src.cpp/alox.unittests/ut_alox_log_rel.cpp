// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alox/alox_console_loggers.hpp"
#include "alox/loggers/memorylogger.hpp"



#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define TESTCLASSNAME       CPP_ALox_Lox_Release
#include "aworx_unittests.hpp"

using namespace std;
using namespace ut_aworx;

using namespace aworx;

namespace ut_alox {

#if defined (ALOX_REL_LOG)

    Lox releaseLox;
    #define LOX_LOX releaseLox

    /** ********************************************************************************************
     * loggers used
     **********************************************************************************************/
     TextLogger*    cl_rel_log= nullptr;
     MemoryLogger*  ml_rel_log= nullptr;

    /** ********************************************************************************************
     * Creates loggers.
     **********************************************************************************************/
    void   deleteLoggers_rel_log()
    {
        Lox_RemoveLoggers( nullptr );
        if( ml_rel_log != nullptr )
        {
            delete ml_rel_log;
            ml_rel_log= nullptr;
        }

        if( cl_rel_log != nullptr )
        {
            delete cl_rel_log;
            cl_rel_log= nullptr;
        }
    }

    void   clearCreateAndAddLoggers_rel_log( bool memoryLogger= false, bool consoleLogger= true)
    {
        LOX_LOX.RemoveLoggers();

        if ( consoleLogger )
        {
            cl_rel_log= Lox::CreateConsoleLogger();
            Lox_RemoveLogger( cl_rel_log );
            Lox_AddLogger( cl_rel_log );
        }

        if ( memoryLogger )
        {
            ml_rel_log= new MemoryLogger();
            Lox_AddLogger( ml_rel_log );
        }

        Lox_MapThreadName( "UnitTest" );
    }

UT_CLASS()

    /** ********************************************************************************************
     * Lox_TestLogLevelSetting
     **********************************************************************************************/
    UT_METHOD(Lox_TestLogLevelSetting)

        clearCreateAndAddLoggers_rel_log( true );
        Lox_SetDomain( LOX_LOX.InternalDomain, Log::DomainLevel::Off, "MEMORY" );

        Lox_SetDomain( "TLLS_DF", Log::Scope::Method );

        // Test log level setting
        int  logLinesBefore= ml_rel_log->CntLogs;

        Lox_SetDomain( "TLLS_DF", Log::DomainLevel::All );
        Lox_Verbose  (         "This Verbose line should be logged" );
        Lox_Info     (         "This Info    line should be logged" );
        Lox_Warning  (         "This WARN    line should be logged" );
        Lox_Error    (         "This Error   line should be logged" );
        Lox_Verbose  (         "(Indented) This Verbose line should be logged", 1 );
        Lox_Info     (         "(Indented) This Info    line should be logged", 1 );
        Lox_Warning  (         "(Indented) This WARN    line should be logged", 1 );
        Lox_Error    (         "(Indented) This Error   line should be logged", 1 );

        Lox_SetDomain( "TLLS_DF", Log::DomainLevel::InfoWarningsAndErrors );
        Lox_Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Info     (         "This Info    line should be logged" );
        Lox_Warning  (         "This Warning line should be logged" );
        Lox_Error    (         "This Error   line should be logged" );
        Lox_Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Info     (         "(Indented) This Info    line should be logged", 1 );
        Lox_Warning  (         "(Indented) This Warning line should be logged", 1 );
        Lox_Error    (         "(Indented) This Error   line should be logged", 1 );

        Lox_SetDomain( "TLLS_DF", Log::DomainLevel::WarningsAndErrors );
        Lox_Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Warning  (         "This Warning line should be logged" );
        Lox_Error    (         "This Error   line should be logged" );
        Lox_Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Warning  (         "(Indented) This Warning line should be logged", 1 );
        Lox_Error    (         "(Indented) This Error   line should be logged", 1 );

        Lox_SetDomain( "TLLS_DF", Log::DomainLevel::Errors );
        Lox_Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Error    (         "This Error   line should be logged" );
        Lox_Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Error    (         "(Indented) This Error   line should be logged", 1 );

        Lox_SetDomain( "TLLS_DF", Log::DomainLevel::Off );
        Lox_Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Error    (         "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Error    (         "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!", 1 );

        Lox_SetDomain( "TLLS", Log::DomainLevel::All );
        Lox_Verbose  ( "TLLS", "This Verbose line should be logged" );
        Lox_Info     ( "TLLS", "This Info    line should be logged" );
        Lox_Warning  ( "TLLS", "This WARN    line should be logged" );
        Lox_Error    ( "TLLS", "This Error   line should be logged" );
        Lox_Verbose  ( "TLLS", "(Indented) This Verbose line should be logged", 1 );
        Lox_Info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        Lox_Warning  ( "TLLS", "(Indented) This WARN    line should be logged", 1 );
        Lox_Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Lox_SetDomain( "TLLS", Log::DomainLevel::InfoWarningsAndErrors );
        Lox_Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Info     ( "TLLS", "This Info    line should be logged" );
        Lox_Warning  ( "TLLS", "This Warning line should be logged" );
        Lox_Error    ( "TLLS", "This Error   line should be logged" );
        Lox_Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        Lox_Warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        Lox_Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Lox_SetDomain( "TLLS", Log::DomainLevel::WarningsAndErrors );
        Lox_Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Warning  ( "TLLS", "This Warning line should be logged" );
        Lox_Error    ( "TLLS", "This Error   line should be logged" );
        Lox_Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        Lox_Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Lox_SetDomain( "TLLS", Log::DomainLevel::Errors );
        Lox_Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Error    ( "TLLS", "This Error   line should be logged" );
        Lox_Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Lox_SetDomain( "TLLS", Log::DomainLevel::Off );
        Lox_Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Error    ( "TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        Lox_Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Lox_Error    ( "TLLS", "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!", 1 );

        #if defined(ALOX_REL_LOG_CI)
            UT_EQ( 40, (int) ml_rel_log->CntLogs - logLinesBefore );
        #else
            // without caller information in release log, the first 20 logs will not come come
            // (as no default domain is found)
            UT_EQ( 20, (int) ml_rel_log->CntLogs - logLinesBefore );
        #endif
        deleteLoggers_rel_log();
    }

    /** ********************************************************************************************
     * Lox_TestDefaultDomain
     **********************************************************************************************/
    #if defined(ALOX_REL_LOG_CI)
        UT_METHOD(Lox_TestDefaultDomain)

            int  cntLL;
            clearCreateAndAddLoggers_rel_log( true );
            Lox_Error("No domain and nothing set");

            Lox_SetDomain( "REPLACED",  Log::Scope::Method );
            Lox_SetDomain( "DFLT",      Log::Scope::Method );

            String testOK=  "OK";
            String testERR= "Error";

            // Test log level setting
            cntLL= cl_rel_log->CntLogs;
            Lox_SetDomain( "DFLT", Log::DomainLevel::InfoWarningsAndErrors );
            cntLL= cl_rel_log->CntLogs;    Lox_Verbose    ( testERR );    UT_EQ( 0,        (int) cl_rel_log->CntLogs - cntLL );
            cntLL= cl_rel_log->CntLogs;    Lox_Info       ( testOK  );    UT_EQ( 1,        (int) cl_rel_log->CntLogs - cntLL );

            Lox_SetDomain( "~",    Log::DomainLevel::WarningsAndErrors );
            cntLL= cl_rel_log->CntLogs;    Lox_Info       ( testERR );    UT_EQ( 0,        (int) cl_rel_log->CntLogs - cntLL );
            cntLL= cl_rel_log->CntLogs;    Lox_Warning    ( testOK  );    UT_EQ( 1,        (int) cl_rel_log->CntLogs - cntLL );

            Lox_SetDomain( "~/",   Log::DomainLevel::Errors );
            cntLL= cl_rel_log->CntLogs;    Lox_Warning    ( testERR );    UT_EQ( 0,        (int) cl_rel_log->CntLogs - cntLL );
            cntLL= cl_rel_log->CntLogs;    Lox_Error      ( testOK  );    UT_EQ( 1,        (int) cl_rel_log->CntLogs - cntLL );

            // test sub domains
            Lox_SetDomain ( "DFLT/WARN", Log::Scope::None );
            Lox_SetDomain (    "~/ERR",  Log::Scope::None );
            Lox_LogConfig ( "TEST",      Log::Level::Info, "Dumping Log Configuration:", cl_rel_log->Name );

            Lox_SetDomain ( "DFLT",      Log::DomainLevel::InfoWarningsAndErrors, Propagation::None );
            Lox_SetDomain ( "DFLT/WARN", Log::DomainLevel::WarningsAndErrors,     Propagation::None );
            Lox_SetDomain (    "~/ERR",  Log::DomainLevel::Errors,                Propagation::None );

            Lox_LogConfig ( "TEST",      Log::Level::Info, "Dumping Log Configuration:", cl_rel_log->Name );

            // log with leading "/" on domain
            cntLL= ml_rel_log->CntLogs;    Lox_Verbose ( "/DFLT",        testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Verbose ( "/DFLT/ERR",    testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Verbose ( "/DFLT/WARN",   testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );

            cntLL= ml_rel_log->CntLogs;    Lox_Info    ( "/DFLT",        testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Info    ( "/DFLT/ERR",    testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Info    ( "/DFLT/WARN",   testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );

            cntLL= ml_rel_log->CntLogs;    Lox_Warning ( "/DFLT",        testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Warning ( "/DFLT/WARN",   testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Warning ( "/DFLT/ERR",    testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );

            cntLL= ml_rel_log->CntLogs;    Lox_Error   ( "/DFLT",        testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Error   ( "/DFLT/WARN",   testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Error   ( "/DFLT/ERR",    testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );

            // log without leading "/" on domain, still absolute
            cntLL= ml_rel_log->CntLogs;    Lox_Verbose ( "DFLT",         testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Verbose ( "DFLT/ERR",     testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Verbose ( "DFLT/WARN",    testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );

            cntLL= ml_rel_log->CntLogs;    Lox_Info    ( "DFLT",         testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Info    ( "DFLT/ERR",     testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Info    ( "DFLT/WARN",    testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );

            cntLL= ml_rel_log->CntLogs;    Lox_Warning ( "DFLT",         testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Warning ( "DFLT/WARN",    testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Warning ( "DFLT/ERR",     testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );

            cntLL= ml_rel_log->CntLogs;    Lox_Error   ( "DFLT",         testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Error   ( "DFLT/WARN",    testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Error   ( "DFLT/ERR",     testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );


            // relative addressing with "~"domain
            cntLL= ml_rel_log->CntLogs;    Lox_Verbose (                 testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Verbose ( "~",            testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Verbose ( "~ERR",         testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Verbose ( "~WARN",        testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );

            cntLL= ml_rel_log->CntLogs;    Lox_Info    (                 testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Info    ( "~",            testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Info    ( "~ERR",         testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Info    ( "~WARN",        testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );

            cntLL= ml_rel_log->CntLogs;    Lox_Warning (                 testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Warning ( "~",            testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Warning ( "~WARN",        testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Warning ( "~ERR",         testERR );    UT_EQ( 0,        (int) ml_rel_log->CntLogs - cntLL );

            cntLL= ml_rel_log->CntLogs;    Lox_Error   (                 testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Error   ( "~",            testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Error   ( "~WARN",        testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );
            cntLL= ml_rel_log->CntLogs;    Lox_Error   ( "~ERR",         testOK  );    UT_EQ( 1,        (int) ml_rel_log->CntLogs - cntLL );

            deleteLoggers_rel_log();
        }
    #endif

    /** ********************************************************************************************
     * Lox_TestAssertAndConditional
     **********************************************************************************************/
    UT_METHOD(Lox_TestAssertAndConditional)

        clearCreateAndAddLoggers_rel_log( true );

        Lox_SetDomain( "ASSERT", Log::Scope::None);

        Lox_Prune( String testOK=  "OK";    )
        Lox_Prune( String testERR= "Error"; )

        // Test log level setting
        int cntLL= cl_rel_log->CntLogs;
        Lox_SetDomain( "ASSERT", Log::DomainLevel::InfoWarningsAndErrors);

        cntLL= cl_rel_log->CntLogs;    Lox_Assert( true,  "ASSERT",                   testERR        ); UT_EQ( 0, (int) cl_rel_log->CntLogs - cntLL );
        cntLL= cl_rel_log->CntLogs;    Lox_Assert( false, "ASSERT",                   testOK         ); UT_EQ( 1, (int) cl_rel_log->CntLogs - cntLL );
        cntLL= cl_rel_log->CntLogs;    Lox_Line  ( false, "ASSERT", Log::Level::Info, &testERR, 0, 1 ); UT_EQ( 0, (int) cl_rel_log->CntLogs - cntLL );
        cntLL= cl_rel_log->CntLogs;    Lox_Line  ( true,  "ASSERT", Log::Level::Info, &testOK,  0, 1 ); UT_EQ( 1, (int) cl_rel_log->CntLogs - cntLL );

        deleteLoggers_rel_log();
    }


    /** ********************************************************************************************
     * Lox_TestMarkerRelLog
     **********************************************************************************************/
    #if defined( ALOX_REL_LOG_CI )
        UT_METHOD(TestMarker)

            clearCreateAndAddLoggers_rel_log();

            Lox_SetDomain( "MARKER", Log::Scope::Method );
            Lox_SetDomain( "MARKER", Log::DomainLevel::All );

            Lox_Info( "*** Testing in Release Log markers ***" );
            Lox_Prune(String markerDisposedGlobal=    "overwritten global level marker (should NOT appear in the test log)";   )
            Lox_Prune(String markerGlobal=            "global marker (this is right to appear in the test log!)";              )
            Lox_Prune(String markerDisposedSrc=       "overwritten source level marker (should NOT appear in the test log)";   )
            Lox_Prune(String markerSrc=               "source level marker (this is right to appear in the test log!)";       )
            Lox_Prune(String markerDisposedMethod=    "overwritten method marker (should NOT appear in the test log)";         )
            Lox_Prune(String markerMethod=            "method marker (this is right to appear in the test log!)";              )

            Lox_SetMarker( (void*) &markerDisposedGlobal,    Log::Scope::None );
            Lox_SetMarker( (void*) &markerGlobal,            Log::Scope::None );
            Lox_SetMarker( (void*) &markerDisposedSrc,       Log::Scope::SourceFile );
            Lox_SetMarker( (void*) &markerSrc,               Log::Scope::SourceFile );
            Lox_SetMarker( (void*) &markerDisposedMethod,    Log::Scope::Method );
            Lox_SetMarker( (void*) &markerMethod,            Log::Scope::Method );

            Lox_Prune( String notSet=            "NOT SET";              )
            Log_Prune( void* markerpointer= (void*) &notSet; )

            Lox_GetMarker( markerpointer, Log::Scope::None );
            Lox_Info( String128("The current global level marker is: ") << (String*) markerpointer );

            UT_TRUE( markerpointer == &markerGlobal );

            Lox_GetMarker( markerpointer, Log::Scope::SourceFile );
            Lox_Info( String128("The current source level marker is: ") << (String*) markerpointer );
            UT_TRUE( markerpointer == &markerSrc    );
            Lox_GetMarker( markerpointer, Log::Scope::Method );
            Lox_Info( String128("The current method level marker is: ") << (String*) markerpointer );
            UT_TRUE( markerpointer == &markerMethod );

            deleteLoggers_rel_log();
        }
    #endif


    UT_METHOD(Lox_ChangeStartTime)

        clearCreateAndAddLoggers_rel_log();

        Lox_SetDomain( "S-TIME", Log::DomainLevel::All );

        Lox_Info ( "S-TIME", "This is the first log with normal start time" );

        Lox_Prune( Ticks newTime;                       )
        Lox_Prune( Ticks sub(0); sub.FromMinutes(20);   )
        Lox_Prune( newTime.Sub ( sub );                 )
        Lox_SetStartTime( newTime, nullptr )
        Lox_Info ( "S-TIME", "Starttime set to 20 minutes ago" );
        Lox_SetStartTime( Ticks(),  nullptr )
        Lox_Info ( "S-TIME", "Starttime set to 'now'" );

        deleteLoggers_rel_log();
    }

    /** ********************************************************************************************
     * Lox_DisableLogger.
     **********************************************************************************************/
    UT_METHOD(Lox_DisableLogger)

        clearCreateAndAddLoggers_rel_log();

        Lox_SetDomain( "DISABLE", Log::DomainLevel::All );

        auto cntLogs= cl_rel_log->CntLogs;
        Lox_Info ( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 1, cl_rel_log->CntLogs );
        Lox_SetLogger( Switch::Off, "NOMATCH" );
        Lox_Info ( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 2, cl_rel_log->CntLogs );
        Lox_SetLogger( Switch::Off, "*cONSole*" );
        Lox_Info ( "DISABLE", "This message should NOT appear" );   UT_EQ( cntLogs + 2, cl_rel_log->CntLogs );
        Lox_SetLogger( Switch::On,  nullptr );
        Lox_Info ( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 3, cl_rel_log->CntLogs );
        deleteLoggers_rel_log();
    }


UT_CLASS_END

#endif // defined (ALOX_REL_LOG)

} // namespace


