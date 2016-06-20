// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "alib/alib.hpp"
#include "alib/compatibility/std_string.hpp"

#include "alox/alox_console_loggers.hpp"
#include "alox/loggers/memorylogger.hpp"

// conditional expression is constant (which is a great thing for the compiler by the way ;-)
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4127 )
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#if !defined (HPP_ALIB_CONFIG_INI_FILE)
    #include "alib/config/inifile.hpp"
#endif

#define TESTCLASSNAME       CPP_ALox_Lox


#include "alib.unittests/aworx_unittests.hpp"

using namespace std;
using namespace ut_aworx;
using namespace aworx;

namespace ut_alox {

// used with unit test Log_ScopeInfoCacheTest
void ScopeInfoCacheTest6() { Log_Info("Test Method 6"); }
void ScopeInfoCacheTest1() { Log_Info("Test Method 1"); }
extern void ScopeInfoCacheTest2();
extern void ScopeInfoCacheTest3();
extern void ScopeInfoCacheTest4();
extern void ScopeInfoCacheTest5();
extern void ScopeInfoCacheTest6();
extern void ScopeInfoCacheTest7();

void check_MemLogStartsWith( const aworx::TString& exp, ALIBUnitTesting& ut, MemoryLogger& memlog, bool doLog= true )
{
    if (doLog)
        Log_Info("");

    if( DirectorySeparator == '/' )
    {
        UT_TRUE( memlog.MemoryLog.StartsWith( exp, Case::Ignore ) );
    }
    else
    {
        String256 expCorrected( exp );
        expCorrected.SearchAndReplaceAll( "/", "\\"  );
        UT_TRUE( memlog.MemoryLog.StartsWith( expCorrected, Case::Ignore ) );
    }

    memlog.MemoryLog.Clear();
}

void check_MemLogContains( const aworx::TString& exp, ALIBUnitTesting& ut, MemoryLogger& memlog, bool doLog= true )
{
    if (doLog)
        Log_Info("");

    if( DirectorySeparator == '/' )
    {
        UT_TRUE( memlog.MemoryLog.IndexOf( exp, 0, Case::Ignore ) >=0 );
    }
    else
    {
        String256 expCorrected( exp );
        expCorrected.SearchAndReplaceAll( "/", "\\"  );
        UT_TRUE( memlog.MemoryLog.IndexOf( expCorrected, 0, Case::Ignore ) >=0 );
    }

    memlog.MemoryLog.Clear();
}

class TThread : public Thread
{
    public: TThread( const String& name, int cntLoops, int sleepMicros )
            : Thread( name )
            {
                this->cntLoops=     cntLoops;
                this->sleepMicros=  sleepMicros;
                this->name= name;
            }
    String32 name;
    int cntLoops;
    int sleepMicros;

    virtual void Run()
    {
        Log_SetDomain( "TEST/THREAD2", Scope::Method );

        for ( int i= 0 ; i < cntLoops ; i++ )
        {
            Log_Info( String64( "This is a " ) << name << ". Cnt= " << i );
            ALIB::SleepMillis( 3 );
        }
    }
};

/** ********************************************************************************************
* UT_CLASS
**********************************************************************************************/

// with GTEST macros it all gets wild. Fix the method name
#undef  ALIB_SRC_INFO_PARAMS
#define ALIB_SRC_INFO_PARAMS     __FILE__, __LINE__, aworxTestName

UT_CLASS()

/** ********************************************************************************************
 * AddLogger
 **********************************************************************************************/
#if defined (ALOX_DBG_LOG)
UT_METHOD(AddLogger)
{
    UT_INIT();

    // twice
    {
        ConsoleLogger con;
        Log_SetVerbosity( &con,      Verbosity::Verbose, ALox::InternalDomains );
        MemoryLogger checkCnt;
        Log_SetVerbosity( &checkCnt, Verbosity::Warning, ALox::InternalDomains );

        MemoryLogger mem1( "MEM" );
        MemoryLogger mem2( "MEM" );

        Log_SetVerbosity( &mem1,     Verbosity::Info ); UT_EQ( 0, checkCnt.CntLogs );
        Log_SetVerbosity( &mem2,     Verbosity::Info ); UT_EQ( 1, checkCnt.CntLogs );
        Log_SetVerbosity( "XYZ",     Verbosity::Info ); UT_EQ( 2, checkCnt.CntLogs );

        Log_RemoveLogger( &mem2     );                  UT_EQ( 3, checkCnt.CntLogs );
        Log_RemoveLogger( &mem1     );                  UT_EQ( 3, checkCnt.CntLogs );
        Log_RemoveLogger( &mem1     );                  UT_EQ( 4, checkCnt.CntLogs );
        Log_RemoveLogger( "XYZ"     );                  UT_EQ( 5, checkCnt.CntLogs );
        Log_RemoveLogger( &con      );                  UT_EQ( 5, checkCnt.CntLogs );
        Log_RemoveLogger( &con      );                  UT_EQ( 6, checkCnt.CntLogs );
        Log_RemoveLogger( &checkCnt );                  UT_EQ( 6, checkCnt.CntLogs );
    }

    // debug and realease lox
    {
        Log_AddDebugLogger();

        Lox lox("ReleaseLox");

        UT_TRUE( ((ThreadLock*) Log::DebugLogger)->GetSafeness() == Safeness::Unsafe );

        lox.SetScopeInfo(ALIB_SRC_INFO_PARAMS);
            lox.SetVerbosity( Log::DebugLogger , Verbosity::Verbose );
        lox.Release();

        UT_TRUE( ((ThreadLock*) Log::DebugLogger)->GetSafeness() == Safeness::Safe   );

        lox.SetScopeInfo(ALIB_SRC_INFO_PARAMS);
            lox.RemoveLogger( Log::DebugLogger );
        lox.Release();

        UT_TRUE( ((ThreadLock*) Log::DebugLogger)->GetSafeness() == Safeness::Unsafe );

        Log_RemoveDebugLogger();
    }

    // two release loxes
    {
        Lox lox1("Lox1");
        Lox lox2("Lox2");
        TextLogger*  cl= Lox::CreateConsoleLogger();

        UT_TRUE( ((ThreadLock*) cl)->GetSafeness() == Safeness::Unsafe );

        #undef  LOX_LOX
        #define LOX_LOX lox1
        Lox_SetVerbosity( cl, Verbosity::Verbose );

        UT_TRUE( ((ThreadLock*) cl)->GetSafeness() == Safeness::Unsafe );

        #undef  LOX_LOX
        #define LOX_LOX lox2
        Lox_SetVerbosity( cl, Verbosity::Verbose );


        UT_TRUE( ((ThreadLock*) cl)->GetSafeness() == Safeness::Safe  );

        #undef  LOX_LOX
        #define LOX_LOX lox1
        Lox_RemoveLogger( cl );

        UT_TRUE( ((ThreadLock*) cl)->GetSafeness() == Safeness::Unsafe );


        #undef  LOX_LOX
        #define LOX_LOX lox2
        Lox_RemoveLogger( cl );

        UT_TRUE( ((ThreadLock*) cl)->GetSafeness() == Safeness::Unsafe );


        delete cl;
    }
}
#endif

/** ********************************************************************************************
 * Log_LogLevelSetting
 **********************************************************************************************/
#if defined( ALOX_DBG_LOG ) && defined(ALOX_DBG_LOG_CI)
UT_METHOD(Log_LogLevelSetting)
{
    UT_INIT();

    Log_AddDebugLogger();
    Log_SetDomain( "TLLS_DF", Scope::Method );

    // Test Verbosity setting
    int  logLinesBefore= Log::DebugLogger->CntLogs;

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Verbose, "" );
    Log_Verbose  (          "This Verbose line should be logged" );
    Log_Info     (          "This Info    line should be logged" );
    Log_Warning  (          "This WARN    line should be logged" );
    Log_Error    (          "This Error   line should be logged" );

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Info, "" );
    Log_Verbose  (          "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Info     (          "This Info    line should be logged" );
    Log_Warning  (          "This Warning line should be logged" );
    Log_Error    (          "This Error   line should be logged" );

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Warning, "" );
    Log_Verbose  (          "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Info     (          "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Warning  (          "This Warning line should be logged" );
    Log_Error    (          "This Error   line should be logged" );

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Error, "" );
    Log_Verbose  (          "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Info     (          "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Warning  (          "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Error    (          "This Error   line should be logged" );

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Off, "" );
    Log_Verbose  (          "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Info     (          "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Warning  (          "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Error    (          "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Verbose, "/TLLS" );
    Log_Verbose  ( "/TLLS", "This Verbose line should be logged" );
    Log_Info     ( "/TLLS", "This Info    line should be logged" );
    Log_Warning  ( "/TLLS", "This WARN    line should be logged" );
    Log_Error    ( "/TLLS", "This Error   line should be logged" );

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Info, "/TLLS" );
    Log_Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Info     ( "/TLLS", "This Info    line should be logged" );
    Log_Warning  ( "/TLLS", "This Warning line should be logged" );
    Log_Error    ( "/TLLS", "This Error   line should be logged" );

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Warning, "/TLLS" );
    Log_Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Warning  ( "/TLLS", "This Warning line should be logged" );
    Log_Error    ( "/TLLS", "This Error   line should be logged" );

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Error, "/TLLS" );
    Log_Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Warning  ( "/TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Error    ( "/TLLS", "This Error   line should be logged" );

    Log_SetVerbosity( Log::DebugLogger, Verbosity::Off, "/TLLS" );
    Log_Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Warning  ( "/TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
    Log_Error    ( "/TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

    UT_EQ( 20, Log::DebugLogger->CntLogs - logLinesBefore );
}
#endif

/** ********************************************************************************************
 * Log_SimpleScopeDomain
 **********************************************************************************************/
#if defined( ALOX_DBG_LOG_CI )
UT_METHOD(Log_SimpleScopeDomain)
{
    UT_INIT();

        int  cntLL;
        Log_SetVerbosity( Log::DebugLogger, Verbosity::Verbose, ALox::InternalDomains );
        Log_Error("No domain and nothing set");

        Log_SetDomain( "REPLACED",  Scope::Method );
        Log_SetDomain( "DFLT",      Scope::Method );

        string testOK=  "This line has to appear";
        string testERR= "This line must not appear";

        // Test Verbosity setting
        Log_SetVerbosity( Log::DebugLogger,    Verbosity::Warning, "" );
        cntLL= Log::DebugLogger->CntLogs;    Log_Info       ( testERR );    UT_EQ( 0, Log::DebugLogger->CntLogs - cntLL );
        cntLL= Log::DebugLogger->CntLogs;    Log_Warning    ( testOK  );    UT_EQ( 1, Log::DebugLogger->CntLogs - cntLL );

        Log_SetVerbosity( Log::DebugLogger,   Verbosity::Error );
        cntLL= Log::DebugLogger->CntLogs;    Log_Warning    ( testERR );    UT_EQ( 0, Log::DebugLogger->CntLogs - cntLL );
        cntLL= Log::DebugLogger->CntLogs;    Log_Error      ( testOK  );    UT_EQ( 1, Log::DebugLogger->CntLogs - cntLL );

        // test sub domains
        Log_Prune( MemoryLogger* testML= new MemoryLogger(); )
        Log_SetVerbosity( testML, Verbosity::Off );
        Log_SetVerbosity( Log::DebugLogger, Verbosity::Verbose, ALox::InternalDomains );
        Log_LogConfig ( "/TEST",      Verbosity::Info, "Dumping Log Configuration:" );

        Log_SetVerbosity ( testML,           Verbosity::Info       , "/DFLT"      );
        Log_SetVerbosity ( testML,           Verbosity::Warning    , "/DFLT/WARN" );
        Log_SetVerbosity ( testML,           Verbosity::Error      ,       "ERR"  );
        Log_SetVerbosity ( Log::DebugLogger, Verbosity::Info       , "/DFLT"      );
        Log_SetVerbosity ( Log::DebugLogger, Verbosity::Warning    , "/DFLT/WARN" );
        Log_SetVerbosity ( Log::DebugLogger, Verbosity::Error      ,       "ERR"  );

        Log_LogConfig ( "/TEST",      Verbosity::Info, "Dumping Log Configuration:" );

        // log with leading "/" on domain
        cntLL= testML->CntLogs;    Log_Verbose( "/DFLT",        testERR );    UT_EQ( 0, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Verbose( "/DFLT/ERR",    testERR );    UT_EQ( 0, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Verbose( "/DFLT/WARN",   testERR );    UT_EQ( 0, testML->CntLogs - cntLL );

        cntLL= testML->CntLogs;    Log_Info   ( "/DFLT",        testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Info   ( "/DFLT/ERR",    testERR );    UT_EQ( 0, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Info   ( "/DFLT/WARN",   testERR );    UT_EQ( 0, testML->CntLogs - cntLL );

        cntLL= testML->CntLogs;    Log_Warning( "/DFLT",        testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Warning( "/DFLT/WARN",   testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Warning( "/DFLT/ERR",    testERR );    UT_EQ( 0, testML->CntLogs - cntLL );

        cntLL= testML->CntLogs;    Log_Error  ( "/DFLT",        testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Error  ( "/DFLT/WARN",   testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Error  ( "/DFLT/ERR",    testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );

        // log without leading "/" on domain (of course, this is quite an error of using ALox)
        cntLL= testML->CntLogs;    Log_Verbose( "DFLT",         testERR );    UT_EQ( 0, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Verbose( "DFLT/ERR",     testERR );    UT_EQ( 0, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Verbose( "DFLT/WARN",    testERR );    UT_EQ( 0, testML->CntLogs - cntLL );

        cntLL= testML->CntLogs;    Log_Info   ( "DFLT",         testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Info   ( "DFLT/ERR",     testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Info   ( "DFLT/WARN",    testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );

        cntLL= testML->CntLogs;    Log_Warning( "DFLT",         testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Warning( "DFLT/WARN",    testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Warning( "DFLT/ERR",     testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );

        cntLL= testML->CntLogs;    Log_Error  ( "DFLT",         testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Error  ( "DFLT/WARN",    testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Error  ( "DFLT/ERR",     testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );


        // relative addressing
        cntLL= testML->CntLogs;    Log_Verbose(                 testERR );    UT_EQ( 0, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Verbose( "",             testERR );    UT_EQ( 0, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Verbose( "ERR",          testERR );    UT_EQ( 0, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Verbose( "WARN",         testERR );    UT_EQ( 0, testML->CntLogs - cntLL );

        cntLL= testML->CntLogs;    Log_Info   (                 testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Info   ( "",             testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Info   ( "ERR",          testERR );    UT_EQ( 0, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Info   ( "WARN",         testERR );    UT_EQ( 0, testML->CntLogs - cntLL );

        cntLL= testML->CntLogs;    Log_Warning(                 testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Warning( "",             testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Warning( "WARN",         testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Warning( "ERR",          testERR );    UT_EQ( 0, testML->CntLogs - cntLL );

        cntLL= testML->CntLogs;    Log_Error  (                 testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Error  ( "",             testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Error  ( "WARN",         testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );
        cntLL= testML->CntLogs;    Log_Error  ( "ERR",          testOK  );    UT_EQ( 1, testML->CntLogs - cntLL );

        Log_RemoveLogger( testML )
        Log_Prune( delete testML; )
    }
#endif

/** ********************************************************************************************
 * Log_Threads
 **********************************************************************************************/
UT_METHOD(Log_Threads)
{
    UT_INIT();

    Log_SetDomain( "/TEST/THREAD1", Scope::Method );
    Log_SetVerbosity( Log::DebugLogger, Verbosity::Verbose, "" );

    // if this gets commented out, the test might crash. At least the console will
    // become scrambled!
    //Log_LOX.Lock.setUnsafe( true );
    {
        TThread thread2( "Thread2" , 50, 0 );
        thread2.Start();
        TThread thread3( "Thread3" , 50, 0 );
        thread3.Start();

        for ( int i= 0 ; i < 50 ; i++ )
        {
            Log_Info( String64("This is the main thread ") << i );
            ALIB::SleepMicros( 1 );
        }
    }
}


/** ********************************************************************************************
 * Log_TestAssertAndIf
 **********************************************************************************************/
#if defined (ALOX_DBG_LOG)
UT_METHOD(Log_TestAssertAndIf)
{
    UT_INIT();

    Log_Prune( String testOK=  "OK";    )
    Log_Prune( String testERR= "Error"; )

    // Test Verbosity setting
    Log_AddDebugLogger();
    int cntLL= Log::DebugLogger->CntLogs;
    Log_SetVerbosity( Log::DebugLogger, Verbosity::Info, "ASSERT");

    #ifdef ALOX_DBG_LOG
        int oneLine= 1;
    #else
        int oneLine= 0;
    #endif

    Log_SetDomain( "/ASSERT", Scope::Method );

    cntLL= Log::DebugLogger->CntLogs;    Log_Assert( true,  "/ASSERT",                  testERR ); UT_EQ( 0,        Log::DebugLogger->CntLogs - cntLL );
    cntLL= Log::DebugLogger->CntLogs;    Log_Assert( false, "/ASSERT",                  testOK  ); UT_EQ( oneLine,  Log::DebugLogger->CntLogs - cntLL );
    cntLL= Log::DebugLogger->CntLogs;    Log_Assert( true,                              testERR ); UT_EQ( 0,        Log::DebugLogger->CntLogs - cntLL );
    cntLL= Log::DebugLogger->CntLogs;    Log_Assert( false,                             testOK  ); UT_EQ( oneLine,  Log::DebugLogger->CntLogs - cntLL );


    cntLL= Log::DebugLogger->CntLogs;    Log_If(     true,  "/ASSERT", Verbosity::Info, testOK  ); UT_EQ( oneLine,  Log::DebugLogger->CntLogs - cntLL );
    cntLL= Log::DebugLogger->CntLogs;    Log_If(     false, "/ASSERT", Verbosity::Info, testERR ); UT_EQ( 0,        Log::DebugLogger->CntLogs - cntLL );
    cntLL= Log::DebugLogger->CntLogs;    Log_If(     true,             Verbosity::Info, testOK  ); UT_EQ( oneLine,  Log::DebugLogger->CntLogs - cntLL );
    cntLL= Log::DebugLogger->CntLogs;    Log_If(     false,            Verbosity::Info, testERR ); UT_EQ( 0,        Log::DebugLogger->CntLogs - cntLL );
}
#endif

/** ********************************************************************************************
 * Log_ScopeInfoCacheTest
 **********************************************************************************************/
#if defined (ALOX_DBG_LOG_CI)
UT_METHOD(Log_ScopeInfoCacheTest)
{
    UT_INIT();

    Log_AddDebugLogger();

    Log_Prune( MemoryLogger memLogger;  )
    if( DirectorySeparator == '/' )
        { Log_Prune( memLogger.MetaInfo->Format=  "%Sp/%SF@";   ) }
    else
        { Log_Prune( memLogger.MetaInfo->Format=  "%Sp\\%SF@";  ) }

    Log_SetVerbosity( &memLogger, Verbosity::Verbose );

    ScopeInfoCacheTest1(); check_MemLogContains( "alox.unittests/ut_alox_lox.cpp"               , ut, memLogger, false );
    ScopeInfoCacheTest2(); check_MemLogContains( "alox.unittests/ut_alox_log_domains.cpp"       , ut, memLogger, false );
    ScopeInfoCacheTest3(); check_MemLogContains( "alox.unittests/ut_alox_log_rel.cpp"           , ut, memLogger, false );
    ScopeInfoCacheTest2(); check_MemLogContains( "alox.unittests/ut_alox_log_domains.cpp"       , ut, memLogger, false );
    ScopeInfoCacheTest3(); check_MemLogContains( "alox.unittests/ut_alox_log_rel.cpp"           , ut, memLogger, false );
    ScopeInfoCacheTest4(); check_MemLogContains( "alox.unittests/ut_alox_log_scopes.cpp"        , ut, memLogger, false );
    ScopeInfoCacheTest5(); check_MemLogContains( "alox.unittests/ut_alox_log_scopes_helper.cpp" , ut, memLogger, false );
    ScopeInfoCacheTest6(); check_MemLogContains( "alox.unittests/ut_alox_lox.cpp"               , ut, memLogger, false );
    ScopeInfoCacheTest7(); check_MemLogContains( "alox.unittests/ut_dox_tutorial.cpp"           , ut, memLogger, false );

    Log_RemoveDebugLogger();
    Log_RemoveLogger( &memLogger );
}
#endif


/** ********************************************************************************************
 * Log_SetSourcePathTrimRuleTest
 **********************************************************************************************/
#if defined (ALOX_DBG_LOG_CI)
UT_METHOD(Log_SetSourcePathTrimRuleTest)
{
    UT_INIT();

    Log_AddDebugLogger();

    Log_Prune( MemoryLogger memLogger;  )
    Log_Prune( memLogger.MetaInfo->Format=  "%Sp@";   )
    Log_SetVerbosity( &memLogger, Verbosity::Verbose );

    Log_ClearSourcePathTrimRules( Inclusion::Include, false )

    #if defined(_WIN32)
        Log_Info( ""); UT_TRUE( memLogger.MemoryLog.CharAt(1) == ':' );
        Log_Prune( memLogger.MemoryLog._();   )

    #else
        #if !defined(ALOX_UNITTESTS_QMAKE_BUILD)
            check_MemLogStartsWith( "/home"               , ut, memLogger );
        #endif
    #endif

    Log_SetSourcePathTrimRule( "*"         , Inclusion::Include     );  // illegal rule, not stored (debug into)
    Log_SetSourcePathTrimRule( "**"        , Inclusion::Include     );  // illegal rule, not stored (debug into)
    Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Include     );  check_MemLogStartsWith( "alox.unittests@"     , ut, memLogger );
    Log_SetSourcePathTrimRule( "*"         , Inclusion::Include     );  // illegal rule, not stored (debug into)
    Log_SetSourcePathTrimRule( "**"        , Inclusion::Include     );  // illegal rule, not stored (debug into)
                                                                        check_MemLogStartsWith( "alox.unittests@"     , ut, memLogger );

    Log_ClearSourcePathTrimRules( Inclusion::Include, false )
    Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Include, -3 );  check_MemLogStartsWith( "pp/alox.unittests@"  , ut, memLogger );
    Log_ClearSourcePathTrimRules( Inclusion::Include, false )
    Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Include, 2  );  check_MemLogStartsWith( "ox.unittests@"       , ut, memLogger );

    Log_ClearSourcePathTrimRules( Inclusion::Include, false )
    Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Exclude     );  check_MemLogStartsWith( "/src.cpp"            , ut, memLogger );

    Log_ClearSourcePathTrimRules( Inclusion::Include, false )
    #if !defined(ALOX_UNITTESTS_QMAKE_BUILD)
        Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Exclude, -3 );  check_MemLogStartsWith( "lox/src.cpp"         , ut, memLogger );

        Log_ClearSourcePathTrimRules( Inclusion::Include, false )
        Log_SetSourcePathTrimRule( "*/src.cpp/*",Inclusion::Exclude, -3 );  check_MemLogStartsWith( "lox/src.cpp"         , ut, memLogger );

        // clear only local rule. (the above rule was global)
        Log_ClearSourcePathTrimRules( Inclusion::Exclude, false )
                                                                      check_MemLogStartsWith( "lox/src.cpp"         , ut, memLogger );
    #endif

    // set local rules
    Log_ClearSourcePathTrimRules( Inclusion::Include, false )
    Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Exclude, 0, Case::Ignore, Inclusion::Exclude );  check_MemLogStartsWith( "/src.cpp"         , ut, memLogger );

    Log_ClearSourcePathTrimRules( Inclusion::Include, false )
    Log_SetSourcePathTrimRule( "*/src.cpp/", Inclusion::Exclude, 0, Case::Ignore, Inclusion::Exclude );  check_MemLogStartsWith( "/src.cpp"         , ut, memLogger );

    // check non ignore case
    Log_ClearSourcePathTrimRules( Inclusion::Include, false )
    Log_SetSourcePathTrimRule( "*/SRC.Cpp/", Inclusion::Exclude, 0, Case::Ignore, Inclusion::Exclude );   check_MemLogStartsWith( "/src.cpp"         , ut, memLogger );

    Log_ClearSourcePathTrimRules( Inclusion::Include, false )
    Log_SetSourcePathTrimRule( "*/SRC.Cpp/", Inclusion::Exclude, 0, Case::Sensitive, Inclusion::Exclude );

    #if !defined(_WIN32)
        #if !defined(ALOX_UNITTESTS_QMAKE_BUILD)
            check_MemLogStartsWith( "/home"               , ut, memLogger );
        #endif
    #else
        Log_Info( ""); UT_TRUE( memLogger.MemoryLog.CharAt(1) == ':' );
    #endif

    Log_RemoveDebugLogger();
    Log_RemoveLogger( &memLogger );
}
#endif

/** ********************************************************************************************
 * Log_SetSourcePathTrimRuleExternal
 **********************************************************************************************/
#if defined (ALOX_REL_LOG) && defined (ALOX_REL_LOG_CI)
UT_METHOD(Log_SetSourcePathTrimRuleExternal)
{
    UT_INIT();
        // for the unit tests to reset, we need an extra lox to be able to clear the global rules
        // beforewe initialize our main lox
        Lox clearLox("ClearingRules");

        // global rule
        clearLox.ClearSourcePathTrimRules( Inclusion::Include, false );
        {
            // create iniFile
            IniFile iniFile("*"); // don't read
            iniFile.Save( ALox::ConfigCategoryName, "TESTML_FORMAT","%Sp"   );
            iniFile.Save( ALox::ConfigCategoryName, "GLOBAL_SOURCE_PATH_TRIM_RULES",
                             "*/src., true"
                    );
            ALIB::Config.InsertPlugin( &iniFile, Configuration::PrioIniFile );


            // test
            Lox lox("T_LOX", false);
            lox.SetScopeInfo(ALIB_SRC_INFO_PARAMS);

                Logger* consoleLogger= Lox::CreateConsoleLogger("CONSOLE");
                lox.SetVerbosity( "CONSOLE" , Verbosity::Verbose );
                lox.SetVerbosity( "CONSOLE" , Verbosity::Verbose, ALox::InternalDomains );

                MemoryLogger ml("TESTML");
                lox.SetVerbosity( &ml, Verbosity::Verbose );

                lox.Info( "" );
                if( DirectorySeparator == '/' )
                    { UT_TRUE(ml.MemoryLog.StartsWith("cpp/") );  }
                else
                    { UT_TRUE(ml.MemoryLog.StartsWith("cpp\\") ); }

                ml.MemoryLog._(); ml.AutoSizes.Reset();

                ALIB::Config.RemovePlugin( &iniFile );
                lox.RemoveLogger( &ml );
                lox.RemoveLogger( "CONSOLE" );
                delete consoleLogger;

            lox.Release();
        }


        // local rule
        clearLox.ClearSourcePathTrimRules( Inclusion::Include, false );
        {
            // create iniFile
            IniFile iniFile("*"); // don't read
            iniFile.Save( ALox::ConfigCategoryName, "TESTML_FORMAT","%Sp"   );
            iniFile.Save( ALox::ConfigCategoryName, "T_LOX_SOURCE_PATH_TRIM_RULES",
                             "*;**; *alox.u*, include ;*;**" // default values, 0, ignore"
                                                             // the * will be removed
                                                             // two illegal rules before and after
                    );
            ALIB::Config.InsertPlugin( &iniFile, Configuration::PrioIniFile );


            // test
            Lox lox("T_LOX", false);
            lox.SetScopeInfo(ALIB_SRC_INFO_PARAMS);

                Logger* consoleLogger= Lox::CreateConsoleLogger("CONSOLE");
                lox.SetVerbosity( "CONSOLE" , Verbosity::Verbose );
                lox.SetVerbosity( "CONSOLE" , Verbosity::Verbose, ALox::InternalDomains );

                MemoryLogger ml("TESTML");
                lox.SetVerbosity( &ml, Verbosity::Verbose );

                lox.Info( "" ); UT_EQ( "nittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();

                ALIB::Config.RemovePlugin( &iniFile );
                lox.RemoveLogger( &ml );
                lox.RemoveLogger( "CONSOLE" );
                delete consoleLogger;

            lox.Release();
        }

        clearLox.ClearSourcePathTrimRules( Inclusion::Include, false );
        {
            // create iniFile
            IniFile iniFile("*"); // don't read
            iniFile.Save( ALox::ConfigCategoryName, "TESTML_FORMAT","%Sp"   );
            iniFile.Save( ALox::ConfigCategoryName, "T_LOX_SOURCE_PATH_TRIM_RULES",
                             "*alox.u, excl, 2, sens"
                    );
            ALIB::Config.InsertPlugin( &iniFile, Configuration::PrioIniFile );


            // test
            Lox lox("T_LOX", false);
            #undef LOX_LOX
            #define LOX_LOX lox

            Logger* consoleLogger= Lox::CreateConsoleLogger("CONSOLE");
            Lox_SetVerbosity( "CONSOLE" , Verbosity::Verbose );
            Lox_SetVerbosity( "CONSOLE" , Verbosity::Verbose, ALox::InternalDomains );

            MemoryLogger ml("TESTML");
            Lox_SetVerbosity( &ml, Verbosity::Verbose );

            Lox_Info( "" ); UT_EQ( "ox.unittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();


            // overwrite with source priority
            Lox_SetSourcePathTrimRule( "*alox.u", Inclusion::Exclude, 0, Case::Ignore, Inclusion::Exclude, "REPLACE_1/" );
            Lox_Info( "" ); UT_EQ( "ox.unittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();
            Lox_SetSourcePathTrimRule( "*alox.u", Inclusion::Exclude, 0, Case::Ignore, Inclusion::Exclude, "REPLACE_2/", Lox::PrioProtected );
            Lox_Info( "" ); UT_TRUE( ml.MemoryLog.StartsWith( "REPLACE_2/" ) ); ml.MemoryLog._(); ml.AutoSizes.Reset();


            ALIB::Config.RemovePlugin( &iniFile );
            Lox_RemoveLogger( &ml );
            Lox_RemoveLogger( "CONSOLE" );
            delete consoleLogger;
        }

        // ignore case
        clearLox.ClearSourcePathTrimRules( Inclusion::Include, false );
        {
            // create iniFile
            IniFile iniFile("*"); // don't read
            iniFile.Save( ALox::ConfigCategoryName, "TESTML_FORMAT","%Sp"   );
            iniFile.Save( ALox::ConfigCategoryName, "T_LOX_SOURCE_PATH_TRIM_RULES",
                             "*aLOX.U, exc, 2, ign"
                    );
            ALIB::Config.InsertPlugin( &iniFile, Configuration::PrioIniFile );


            // test
            Lox lox("T_LOX", false);
            lox.SetScopeInfo(ALIB_SRC_INFO_PARAMS);

                Logger* consoleLogger= Lox::CreateConsoleLogger("CONSOLE");
                lox.SetVerbosity( "CONSOLE" , Verbosity::Verbose );
                lox.SetVerbosity( "CONSOLE" , Verbosity::Verbose, ALox::InternalDomains );

                MemoryLogger ml("TESTML");
                lox.SetVerbosity( &ml, Verbosity::Verbose );

                lox.Info( "" ); UT_EQ( "ox.unittests"  , ml.MemoryLog ); ml.MemoryLog._(); ml.AutoSizes.Reset();

                ALIB::Config.RemovePlugin( &iniFile );
                lox.RemoveLogger( &ml );
                lox.RemoveLogger( "CONSOLE" );
                delete consoleLogger;

            lox.Release();
        }

        clearLox.ClearSourcePathTrimRules( Inclusion::Include, false );
        {
            // create iniFile
            IniFile iniFile("*"); // don't read
            iniFile.Save( ALox::ConfigCategoryName, "TESTML_FORMAT","%Sp"   );
            iniFile.Save( ALox::ConfigCategoryName, "T_LOX_SOURCE_PATH_TRIM_RULES",
                             "*aLOX.U, excl, 2, insens"
                    );
            ALIB::Config.InsertPlugin( &iniFile, Configuration::PrioIniFile );


            // test
            Lox lox("T_LOX", false);
            lox.SetScopeInfo(ALIB_SRC_INFO_PARAMS);

                Logger* consoleLogger= Lox::CreateConsoleLogger("CONSOLE");
                lox.SetVerbosity( "CONSOLE" , Verbosity::Verbose );
                lox.SetVerbosity( "CONSOLE" , Verbosity::Verbose, ALox::InternalDomains );

                MemoryLogger ml("TESTML");
                lox.SetVerbosity( &ml, Verbosity::Verbose );

                lox.Info( "" );
                { UT_EQ( "ox.unittests" , ml.MemoryLog );  }

                ml.MemoryLog._(); ml.AutoSizes.Reset();

                ALIB::Config.RemovePlugin( &iniFile );
                lox.RemoveLogger( &ml );
                lox.RemoveLogger( "CONSOLE" );
                delete consoleLogger;

            lox.Release();
        }
}
#endif

/** ********************************************************************************************
 * Log_ChangeStartTime
 **********************************************************************************************/
UT_METHOD(Log_ChangeStartTime)
{
    UT_INIT();

    Log_AddDebugLogger();
    Log_SetVerbosity  ( Log::DebugLogger, Verbosity::Verbose, "/S-TIME" );

    Log_Info ( "/S-TIME", "This is the first log with normal start time" );

    Log_Prune( Ticks newTime;                       )
    Log_Prune( Ticks sub(0); sub.FromMinutes(20);   )
    Log_Prune( newTime.Sub ( sub );                 )
    Log_SetStartTime( newTime, Log::DebugLogger->GetName() )
    Log_Info ( "/S-TIME", "Starttime set to 20 minutes ago" );
    Log_SetStartTime( Ticks(),  Log::DebugLogger->GetName() )
    Log_Info ( "/S-TIME", "Starttime set to 'now'" );
}


UT_CLASS_END
} // namespace

#if defined(_MSC_VER)
    #pragma warning( pop )
#endif

