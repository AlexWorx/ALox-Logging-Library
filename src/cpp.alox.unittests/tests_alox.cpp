// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"

#include "alox_console_logger.hpp"
#include "alox_memory_logger.hpp"



#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define TESTCLASSNAME       CPP_ALox
#include "../cpp.aworx.util.unittests/awx_unittests.hpp"

using namespace std;
using namespace tests_aworx_util;

using namespace aworx::util;
using namespace aworx::lox;
using namespace aworx::lox::loggers;


namespace tests_alox {

class T : public core::TextLoggerLineFormatter
{
    public:       void    t(AString& buf, int64_t diff)     { writeTimeDiff( buf, diff ); }
};

class TThread : public Thread
{
    public: TThread( const char* name, int cntLoops, int sleepMicros )
            : Thread( name )
            {
                this->cntLoops=     cntLoops;
                this->sleepMicros=  sleepMicros;
                this->name= name;
            }
    AString32 name;
    int cntLoops;
    int sleepMicros;

    virtual void Run()
    {
        Log_RegDomain( "TEST/THREAD2", Log::Scope::METHOD );
        Log_SetDomain( "TEST/THREAD2", Log::DomainLevel::ALL );

        for ( int i= 0 ; i < cntLoops ; i++ )
        {
            Log_Info( AString32("This is a ") << name << ". Cnt= " << i );
            AWXU::SleepMillis( 3 );
        }
    }
};


A_TEST_CLASS()

    /** ********************************************************************************************
     * loggers used
     **********************************************************************************************/
     Log_Prune( ConsoleLogger*  cl= nullptr; )
     Log_Prune( MemoryLogger*   ml= nullptr; )

    /** ********************************************************************************************
     * <summary>    Creates loggers. </summary>
     **********************************************************************************************/
    void   deleteLoggers()
    {
        Log_RemoveLoggers( nullptr );
        Log_Prune( if( cl != nullptr ) { delete cl; cl= nullptr; } )
        Log_Prune( if( ml != nullptr ) { delete ml; ml= nullptr; } )
    }

    void   clearCreateAndAddLoggers( bool memoryLogger= false, bool consoleLogger= true)
    {
        #if defined(ALOX_DBG_LOG)
            delete Log::lox;
            Log::lox= new Lox();

            if ( consoleLogger )
            {
                cl= new ConsoleLogger();
                Log_AddLoggerD( cl, Log::DomainLevel::ALL );

                //cl->EnableAppConsole=        true;
                //cl->EnableVSDebugConsole=    true;
            }

            if ( memoryLogger )
            {
                ml= new MemoryLogger();
                Log_AddLoggerD( ml, Log::DomainLevel::OFF );
            }

            Log_MapThreadName( "UnitTest" );
        #endif
    }

    /** ********************************************************************************************
     * <summary>    Log_TestLogLevelSetting </summary>
     **********************************************************************************************/
    A_TEST_METHOD(Log_TestTextLoggerTimeDiff)

        T t;
        t.TimeDiffMinimum= 0;
        AString ms;
        int64_t diff;
        int64_t micros=     1000L;
        int64_t millis=     1000L * micros;
        int64_t secs=       1000L * millis;
        int64_t mins=          60 * secs;
        int64_t hours=         60 * mins;
        int64_t days=          24 * hours;


        t.TimeDiffMinimum= 0;
        diff= 0;                            ms.Clear(); t.t( ms, diff );
        EXPECT_STREQ( AString16(   "000" ).Append( t.TimeDiffNanos    ).Buffer(),   ms.Buffer() );
        diff= 15;                           ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "015" ).Append( t.TimeDiffNanos    ).Buffer(),    ms.Buffer() );
        diff= 99;                           ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "099" ).Append( t.TimeDiffNanos    ).Buffer(),    ms.Buffer() );
        diff= 600;                          ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "600" ).Append( t.TimeDiffNanos    ).Buffer(),    ms.Buffer() );
        diff= 999;                          ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "999" ).Append( t.TimeDiffNanos    ).Buffer(),    ms.Buffer() );
        diff= 1000;                         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "001" ).Append( t.TimeDiffMicros   ).Buffer(),    ms.Buffer() );
        t.TimeDiffMinimum= 700;
        diff= 600;                          ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(         ).Append( t.TimeDiffNone     ).Buffer(),    ms.Buffer() );
        diff= 700;                          ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "700" ).Append( t.TimeDiffNanos    ).Buffer(),    ms.Buffer() );
        diff= 999;                          ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "999" ).Append( t.TimeDiffNanos    ).Buffer(),    ms.Buffer() );
        t.TimeDiffMinimum= 1000;
        diff= 1000;                         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "001" ).Append( t.TimeDiffMicros   ).Buffer(),    ms.Buffer() );
        diff= 15 * micros;                  ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "015" ).Append( t.TimeDiffMicros   ).Buffer(),    ms.Buffer() );
        diff= 99 * micros;                  ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "099" ).Append( t.TimeDiffMicros   ).Buffer(),    ms.Buffer() );
        diff= 600* micros;                  ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "600" ).Append( t.TimeDiffMicros   ).Buffer(),    ms.Buffer() );
        diff= 999* micros;                  ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "999" ).Append( t.TimeDiffMicros   ).Buffer(),    ms.Buffer() );
        diff= 1   * millis;                 ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "001" ).Append( t.TimeDiffMillis   ).Buffer(),    ms.Buffer() );
        diff= 999 * millis;                 ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(   "999" ).Append( t.TimeDiffMillis   ).Buffer(),    ms.Buffer() );
        diff= 1   * secs;                   ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "1.00" ).Append( t.TimeDiffSecs     ).Buffer(),    ms.Buffer() );

        diff= 2   * secs + 344 * millis;    ms.Clear(); t.t( ms, diff );
        EXPECT_STREQ( AString16(  "2.34" ).Append( t.TimeDiffSecs     ).Buffer(),    ms.Buffer() );

        diff= 3   * secs + 345 * millis;    ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "3.35" ).Append( t.TimeDiffSecs     ).Buffer(),    ms.Buffer() );
        diff= 9   * secs + 994 * millis;    ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.99" ).Append( t.TimeDiffSecs     ).Buffer(),    ms.Buffer() );
        diff= 9   * secs + 995 * millis;    ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "10.0" ).Append( t.TimeDiffSecs     ).Buffer(),    ms.Buffer() );
        diff= 9   * secs + 999 * millis;    ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "10.0" ).Append( t.TimeDiffSecs     ).Buffer(),    ms.Buffer() );
        diff= 10  * secs + 940 * millis;    ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "10.9" ).Append( t.TimeDiffSecs     ).Buffer(),    ms.Buffer() );
        diff= 10  * secs + 950 * millis;    ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "11.0" ).Append( t.TimeDiffSecs     ).Buffer(),    ms.Buffer() );

        diff= 99  * secs + 900 * millis;    ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.9" ).Append( t.TimeDiffSecs     ).Buffer(),    ms.Buffer() );
        diff= 99  * secs + 949 * millis;    ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.9" ).Append( t.TimeDiffSecs     ).Buffer(),    ms.Buffer() );


        diff= 2  * mins + 0 * secs;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "2.00" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );
        diff= 2  * mins + 30 * secs;        ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "2.50" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );
        diff= 9  * mins + 45 * secs;        ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.75" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );
        diff= 9  * mins + 59 * secs;        ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.98" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );
        diff= 9  * mins + 59500 * millis;   ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.99" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );
        diff= 9  * mins + 59999 * millis;   ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "10.0" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );

        diff= 99 * mins + 0 * secs;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.0" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );
        diff= 99 * mins + 30* secs;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.5" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );
        diff= 99 * mins + 59* secs;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.9" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );
        diff= 99 * mins + 59500* millis;    ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.9" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );
        diff= 99 * mins + 59999* millis;    ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "1.66" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 1 * hours + 30* mins;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "90.0" ).Append( t.TimeDiffMins     ).Buffer(),    ms.Buffer() );

        diff= 5 * hours + 30* mins;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "5.50" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );

        diff= 9 * hours + 45* mins;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.75" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 9 * hours + 59* mins;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.98" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 9 * hours + 3540* secs;       ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.98" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 9 * hours + 3580* secs;       ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.99" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 9 * hours + 3599* secs;       ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.99" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 9 * hours + 3600* secs;       ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "10.0" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );

        diff= 50 * hours + 15 *mins;        ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "50.2" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 99 * hours + 45 *mins;        ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.7" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 99 * hours + 48 *mins;        ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.8" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 99 * hours + 59 *mins;        ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.9" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 99 * hours + 3540* secs;      ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.9" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 99 * hours + 3580* secs;      ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.9" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 99 * hours + 3599* secs;      ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.9" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );
        diff= 99 * hours + 3600* secs;      ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "4.16" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );

        diff= 1 * days + 12* hours;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "36.0" ).Append( t.TimeDiffHours    ).Buffer(),    ms.Buffer() );

        diff= 5 * days + 18* hours;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "5.75" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );
        diff= 9 * days + 23* hours;         ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.95" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );
        diff= 9 * days + 1380 * mins;       ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.95" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );
        diff= 9 * days + 1400 * mins;       ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.97" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );
        diff= 9 * days + 1439 * mins;       ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "9.99" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );
        diff= 9 * days + 1440 * mins;       ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "10.0" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );
        diff= 15 * days + 6 * hours;        ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "15.2" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );
        diff= 99 * days + 18 * hours;       ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.7" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );
        diff= 99 * days + 1439 * mins;      ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16(  "99.9" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );
        diff= 99 * days + 1440 * mins;      ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16( "100.0" ).Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );

        diff= 13452 * days+ 12* hours;      ms.Clear(); t.t( ms, diff ); EXPECT_STREQ( AString16("13452.5").Append( t.TimeDiffDays     ).Buffer(),    ms.Buffer() );
        //System.out.println(ms.ToString());
    }

    /** ********************************************************************************************
     * <summary>    Log_TestLogLevelSetting </summary>
     **********************************************************************************************/
    A_TEST_METHOD(Log_TestLogLevelSetting)

        clearCreateAndAddLoggers();

        Log_RegDomain( "TLLS", Log::Scope::METHOD );
        Log_SetDomain( ALOX_DBG_LOX_INSTANCE InternalDomain, Log::DomainLevel::OFF );

        // Test log level setting
        int  logLinesBefore= cl->CntLogs;
        Log_SetDomain( "TLLS", Log::DomainLevel::ALL );
        Log_VerboseD ( "TLLS", "This Verbose line should be logged" );
        Log_InfoD    ( "TLLS", "This Info    line should be logged" );
        Log_WarningD ( "TLLS", "This WARN    line should be logged" );
        Log_ErrorD   ( "TLLS", "This Error   line should be logged" );

        Log_SetDomain( "TLLS", Log::DomainLevel::INFO_WARNINGS_AND_ERRORS );
        Log_VerboseD ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_InfoD    ( "TLLS", "This Info    line should be logged" );
        Log_WarningD ( "TLLS", "This Warning line should be logged" );
        Log_ErrorD   ( "TLLS", "This Error   line should be logged" );


        Log_SetDomain( "TLLS", Log::DomainLevel::WARNINGS_AND_ERRORS );
        Log_VerboseD ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_InfoD    ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_WarningD ( "TLLS", "This Warning line should be logged" );
        Log_ErrorD   ( "TLLS", "This Error   line should be logged" );

        Log_SetDomain( "TLLS", Log::DomainLevel::ERRORS );
        Log_VerboseD ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_InfoD    ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_WarningD ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_ErrorD   ( "TLLS", "This Error   line should be logged" );

        Log_SetDomain( "TLLS", Log::DomainLevel::OFF );
        Log_VerboseD ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_InfoD    ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_WarningD ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_ErrorD   ( "TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

        #ifdef ALOX_DBG_LOG
            EXPECT_EQ ( 10, (int) cl->CntLogs - logLinesBefore );
        #else
            EXPECT_EQ ( 0,  (int) cl->CntLogs - logLinesBefore );
        #endif
        deleteLoggers();
    }

    /** ********************************************************************************************
     * <summary>    Log_TestDefaultDomain </summary>
     **********************************************************************************************/
    A_TEST_METHOD(Log_TestDefaultDomain)

        #if defined (ALOX_DBG_LOG_CI)
            int  cntLL;
            clearCreateAndAddLoggers( true );
            Log_Error("No domain and nothing set");

            Log_RegDomain( "REPLACED",  Log::Scope::METHOD );
            Log_RegDomain( "DFLT",      Log::Scope::METHOD );

            string testOK=  "OK";
            string testERR= "Error";

            #if defined (ALOX_DBG_LOG)
                int  oneLine= 1;
            #else
                int  oneLine= 0;
            #endif

            // Test log level setting
            cntLL= cl->CntLogs;
            Log_SetDomain( "DFLT", Log::DomainLevel::INFO_WARNINGS_AND_ERRORS );
            cntLL= cl->CntLogs;    Log_Verbose    ( testERR );    EXPECT_EQ ( 0,        (int) cl->CntLogs - cntLL );
            cntLL= cl->CntLogs;    Log_Info       ( testOK  );    EXPECT_EQ ( oneLine,  (int) cl->CntLogs - cntLL );

            Log_SetDomain( "~",    Log::DomainLevel::WARNINGS_AND_ERRORS );
            cntLL= cl->CntLogs;    Log_Info       ( testERR );    EXPECT_EQ ( 0,        (int) cl->CntLogs - cntLL );
            cntLL= cl->CntLogs;    Log_Warning    ( testOK  );    EXPECT_EQ ( oneLine,  (int) cl->CntLogs - cntLL );

            Log_SetDomain( "~/",   Log::DomainLevel::ERRORS );
            cntLL= cl->CntLogs;    Log_Warning    ( testERR );    EXPECT_EQ ( 0,        (int) cl->CntLogs - cntLL );
            cntLL= cl->CntLogs;    Log_Error      ( testOK  );    EXPECT_EQ ( oneLine,  (int) cl->CntLogs - cntLL );

            // test sub domains
            Log_RegDomain ( "DFLT/WARN", Log::Scope::NONE );
            Log_RegDomain (    "~/ERR",  Log::Scope::NONE );
            Log_LogConfigF( "TEST",      Log::Level::INFO, "Dumping Log Configuration:", cl->Name.Buffer() );

            Log_SetDomainR( "DFLT",      Log::DomainLevel::INFO_WARNINGS_AND_ERRORS, true );
            Log_SetDomainR( "DFLT/WARN", Log::DomainLevel::WARNINGS_AND_ERRORS,      true );
            Log_SetDomainR(    "~/ERR",  Log::DomainLevel::ERRORS,                   true );

            Log_LogConfigF( "TEST",      Log::Level::INFO, "Dumping Log Configuration:", cl->Name.Buffer() );

            // log with leading "/" on domain
            cntLL= ml->CntLogs;    Log_VerboseD( "/DFLT",        testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_VerboseD( "/DFLT/ERR",    testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_VerboseD( "/DFLT/WARN",   testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );

            cntLL= ml->CntLogs;    Log_InfoD   ( "/DFLT",        testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_InfoD   ( "/DFLT/ERR",    testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_InfoD   ( "/DFLT/WARN",   testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );

            cntLL= ml->CntLogs;    Log_WarningD( "/DFLT",        testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_WarningD( "/DFLT/WARN",   testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_WarningD( "/DFLT/ERR",    testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );

            cntLL= ml->CntLogs;    Log_ErrorD  ( "/DFLT",        testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_ErrorD  ( "/DFLT/WARN",   testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_ErrorD  ( "/DFLT/ERR",    testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );

            // log without leading "/" on domain, still absolute
            cntLL= ml->CntLogs;    Log_VerboseD( "DFLT",         testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_VerboseD( "DFLT/ERR",     testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_VerboseD( "DFLT/WARN",    testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );

            cntLL= ml->CntLogs;    Log_InfoD   ( "DFLT",         testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_InfoD   ( "DFLT/ERR",     testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_InfoD   ( "DFLT/WARN",    testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );

            cntLL= ml->CntLogs;    Log_WarningD( "DFLT",         testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_WarningD( "DFLT/WARN",    testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_WarningD( "DFLT/ERR",     testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );

            cntLL= ml->CntLogs;    Log_ErrorD  ( "DFLT",         testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_ErrorD  ( "DFLT/WARN",    testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_ErrorD  ( "DFLT/ERR",     testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );


            // relative addressing with "~"domain
            cntLL= ml->CntLogs;    Log_Verbose (                 testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_VerboseD( "~",            testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_VerboseD( "~ERR",         testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_VerboseD( "~WARN",        testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );

            cntLL= ml->CntLogs;    Log_Info    (                 testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_InfoD   ( "~",            testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_InfoD   ( "~ERR",         testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_InfoD   ( "~WARN",        testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );

            cntLL= ml->CntLogs;    Log_Warning (                 testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_WarningD( "~",            testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_WarningD( "~WARN",        testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_WarningD( "~ERR",         testERR );    EXPECT_EQ ( 0,        (int) ml->CntLogs - cntLL );

            cntLL= ml->CntLogs;    Log_Error   (                 testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_ErrorD  ( "~",            testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_ErrorD  ( "~WARN",        testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );
            cntLL= ml->CntLogs;    Log_ErrorD  ( "~ERR",         testOK  );    EXPECT_EQ ( oneLine,  (int) ml->CntLogs - cntLL );

            deleteLoggers();
        #endif
    }

    /** ********************************************************************************************
     * <summary>    Log_TestDefaultDomain </summary>
     **********************************************************************************************/
    A_TEST_METHOD(Log_TestAssertAndConditional)

        clearCreateAndAddLoggers( true );

        Log_RegDomain( "ASSERT", Log::Scope::NONE);

        Log_Prune( const char* testOK=  "OK";    )
        Log_Prune( const char* testERR= "Error"; )

        // Test log level setting
        int cntLL= cl->CntLogs;
        Log_SetDomain( "ASSERT", Log::DomainLevel::INFO_WARNINGS_AND_ERRORS);

        #ifdef ALOX_DBG_LOG
            int oneLine= 1;
        #else
            int oneLine= 0;
        #endif

        cntLL= cl->CntLogs;    Log_AssertD( true,  "ASSERT",                   testERR    ); EXPECT_EQ ( 0,        (int) cl->CntLogs - cntLL );
        cntLL= cl->CntLogs;    Log_AssertD( false, "ASSERT",                   testOK     ); EXPECT_EQ ( oneLine,  (int) cl->CntLogs - cntLL );
        cntLL= cl->CntLogs;    Log_Line   ( false, "ASSERT", Log::Level::INFO, testERR, 1 ); EXPECT_EQ ( 0,        (int) cl->CntLogs - cntLL );
        cntLL= cl->CntLogs;    Log_Line   ( true,  "ASSERT", Log::Level::INFO, testOK,  1 ); EXPECT_EQ ( oneLine , (int) cl->CntLogs - cntLL );

        deleteLoggers();
    }


    /** ********************************************************************************************
     * <summary>    Log_TestLineFormat </summary>
     **********************************************************************************************/
    A_TEST_METHOD(Log_TestLineFormat)

        Lox lox;
        clearCreateAndAddLoggers(true, true);
        lox.AddLogger( cl, Log::DomainLevel::ALL );
        lox.AddLogger( ml, Log::DomainLevel::OFF );

        lox.RegDomain( "FMT", Log::Scope::METHOD );
        lox.SetDomain( "FMT", Log::DomainLevel::ALL);

        lox.Info( "This is the default ConsoleLogger log line" );

        AString64  lf;
        lf= "%CF(%CL):%CM()%A3[%D][%TD][%TE +%TI] [%t] %L [%O] <%#>: ";   cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "%CF(%CL):%A3[%D][%TD][%TE +%TI] [%t] %L [%O] <%#>: ";        cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "%CF(%CL):%A3[%TD][%TE +%TI] [%t] %L [%O] <%#>: ";            cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "%CF(%CL):%A3[%TE +%TI] [%t] %L [%O] <%#>: ";                 cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "%CF(%CL):%A3[+%TI] [%t] %L [%O] <%#>: ";                     cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "%CF(%CL):%A3[%t] %L [%O] <%#>: ";                            cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "%CF(%CL):%A3%L [%O] <%#>: ";                                 cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "%CF(%CL):%A3[%O] <%#>: ";                                    cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "%CF(%CL):%A3[%O]: ";                                         cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "%CF:%A3[%O]: ";                                              cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "[%O]: ";                                                     cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );
        lf= "";                                                           cl->LineFormatter->Format= lf;    lox.Info( AString128("LineFormat set to= \"") << lf << "\"" );

        cl->LineFormatter->Format= "%D@";
        ml->LineFormatter->Format= "%D@";
        const char* df;
        df= ">yy-MM-dd<";    cl->LineFormatter->DateFormat= df;    lox.Info( AString128("Date test. Format: \"") << df << "\"" );
        ml->Buffer.Clear();
        df= ">yyyy/dd/MM<";  cl->LineFormatter->DateFormat= df;  ml->LineFormatter->DateFormat= df;           lox.Info( "FMT", AString128("Date test. Format: \"") << df << "\"" );
        EXPECT_TRUE( ml->Buffer.ReplaceCount( "/", "@") == 4 );

        cl->LineFormatter->Format= "%TD@";
        ml->LineFormatter->Format= "%TD@";
        df= ">HH:mm:ss<";    cl->LineFormatter->TimeOfDayFormat= df;                                          lox.Info( "FMT", AString128("Time of day test Format: \"") << df << "\"" );
        ml->Buffer.Clear();
        df= ">HH-mm-ss<";    cl->LineFormatter->TimeOfDayFormat= df;  ml->LineFormatter->TimeOfDayFormat= df; lox.Info( "FMT", AString128("Time of day test. Format: \"") << df << "\"" );
        EXPECT_TRUE( ml->Buffer.ReplaceCount( "-", "@") == 4 );

        deleteLoggers();
    }

    /** ********************************************************************************************
        * <summary>    Log_TestMarker </summary>
        **********************************************************************************************/
    A_TEST_METHOD(TestMarker)

        clearCreateAndAddLoggers();

        Log_RegDomain( "MARKER", Log::Scope::METHOD );
        Log_SetDomain( "MARKER", Log::DomainLevel::ALL );


        Log_Info( "*** Testing markers ***" );
        Log_Prune(const char* markerDisposedGlobal=    "overwritten global level marker (should NOT appear in the test log)";   )
        Log_Prune(const char* markerGlobal=            "global marker (this is right to appear in the test log!)";              )
        Log_Prune(const char* markerDisposedSrc=       "overwritten source level marker (should NOT appear in the test log)";   )
        Log_Prune( const char* markerSrc=               "source level marker (this is right to appear in the test log!)";       )
        Log_Prune(const char* markerDisposedMethod=    "overwritten method marker (should NOT appear in the test log)";         )
        Log_Prune(const char* markerMethod=            "method marker (this is right to appear in the test log!)";              )


        /*#/AWX_LOG// Log_SetMarker( markerDisposedSrc,    true );        //#/AWX_LOG*/
        Log_SetMarker( (void*) markerDisposedGlobal,    Log::Scope::NONE );
        Log_SetMarker( (void*) markerGlobal,            Log::Scope::NONE );
        Log_SetMarker( (void*) markerDisposedSrc,       Log::Scope::SOURCE_FILE );
        Log_SetMarker( (void*) markerSrc,               Log::Scope::SOURCE_FILE );
        Log_SetMarker( (void*) markerDisposedMethod,    Log::Scope::METHOD );
        Log_SetMarker( (void*) markerMethod,            Log::Scope::METHOD );

        void* markerpointer= (void*) "NOT SET";
        #if ! defined( ALOX_DBG_LOG )
            void* untouched=     markerpointer;
        #endif

        Log_GetMarker( markerpointer, Log::Scope::NONE );
        Log_Info( AString128("The current global level marker is: ") << (char*) markerpointer );
        #if defined( ALOX_DBG_LOG ) && defined( ALOX_DBG_LOG_CI )
            EXPECT_TRUE( markerpointer == markerGlobal );
        #endif
        Log_GetMarker( markerpointer, Log::Scope::SOURCE_FILE );
        Log_Info( AString128("The current source level marker is: ") << (char*) markerpointer );
        #if defined( ALOX_DBG_LOG ) && defined( ALOX_DBG_LOG_CI )
            EXPECT_TRUE( markerpointer == markerSrc    );
        #endif
        Log_GetMarker( markerpointer, Log::Scope::METHOD );
        Log_Info( AString128("The current method level marker is: ") << (char*) markerpointer );
        #if defined( ALOX_DBG_LOG ) && defined( ALOX_DBG_LOG_CI )
            EXPECT_TRUE( markerpointer == markerMethod );
        #endif
        deleteLoggers();
    }


    /** ********************************************************************************************
     * <summary>    Log_TestThreads </summary>
     **********************************************************************************************/
    A_TEST_METHOD(Log_TestThreads)

        clearCreateAndAddLoggers();

        Log_RegDomain( "TEST/THREAD1", Log::Scope::METHOD );
        Log_SetDomain( "TEST/THREAD1", Log::DomainLevel::ALL );

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
                Log_Info( AString32("This is the main thread ") << i );
                AWXU::SleepMicros( 1 );
            }
        }
        deleteLoggers();
    }

    /** ********************************************************************************************
     * <summary>    Log_TestException. </summary>
     **********************************************************************************************/
    A_TEST_METHOD(Log_TestMultiline)

        clearCreateAndAddLoggers();


        Log_RegDomain( "MLine", Log::Scope::METHOD );
        Log_SetDomain( "MLine", Log::DomainLevel::ALL );


        cl->MultiLineMsgMode= 0;
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 0 (single line) --------" );
        Log_LogConfig( "MLine", Log::Level::INFO, "Our Log configuration is:" );

        cl->MultiLineMsgMode= 0;
        cl->MultiLineDelimiterRepl= "~|~";
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 0 (single line) with delimiter replacement set to ~|~ --------" );
        Log_LogConfig( "MLine", Log::Level::INFO, "Our Log configuration is:" );

        cl->MultiLineMsgMode= 0;
        cl->MultiLineDelimiter= "";
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 0 (single line) with delimiter set to \"\" (stops multi line processing) --------" );
        Log_LogConfig( "MLine", Log::Level::INFO, "Our Log configuration is:" );
        cl->MultiLineDelimiter= nullptr; // reset

        cl->MultiLineMsgMode= 1;
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 1 (multi line, all meta info per line) --------" );
        Log_LogConfig( "MLine", Log::Level::INFO, "Our Log configuration is:" );

        cl->MultiLineMsgMode= 2;
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 2 (multi line, meta info blanked) --------" );
        Log_LogConfig( "MLine", Log::Level::INFO, "Our Log configuration is:" );

        cl->MultiLineMsgMode= 3;
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 3 (multi line, print headline with info, text starts at pos 0) --------" );
        Log_LogConfig( "MLine", Log::Level::INFO, "Our Log configuration is:" );

        cl->MultiLineMsgMode= 4;
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 4 (pure multi line, no meta info, no headline, starts at pos 0)) --------" );
        Log_LogConfig( "MLine", Log::Level::INFO, "Our Log configuration is:" );

        deleteLoggers();
    }

    /** ********************************************************************************************
     * <summary>    Log_TestException. </summary>
     **********************************************************************************************/
    A_TEST_METHOD(Log_ChangeStartTime)

        clearCreateAndAddLoggers();

        Log_SetDomain( "S-TIME", Log::DomainLevel::ALL );

        Log_InfoD( "S-TIME", "This is the first log with normal start time" );

        Log_Prune( Ticks newTime;                       )
        Log_Prune( Ticks sub(0); sub.FromMinutes(20);   )
        Log_Prune( newTime.Sub ( sub );                 )
        Log_SetStartTime( newTime, nullptr )
        Log_InfoD( "S-TIME", "Starttime set to 20 minutes ago" );
        Log_SetStartTime( Ticks(),  nullptr )
        Log_InfoD( "S-TIME", "Starttime set to 'now'" );

        deleteLoggers();
    }

    /** ********************************************************************************************
     * <summary>    Log_TestException. </summary>
     **********************************************************************************************/
    A_TEST_METHOD(Log_DisableLogger)

        clearCreateAndAddLoggers();

        Log_SetDomain( "DISABLE", Log::DomainLevel::ALL );

        Log_InfoD( "DISABLE", "This message should appear" );
        Log_SetDisabled( true, "NOMATCH" );
        Log_InfoD( "DISABLE", "This message should appear" );
        Log_SetDisabled( true, "*onsol*" );
        Log_InfoD( "DISABLE", "This message should NOT appear" );
        Log_SetDisabled( false, nullptr );
        Log_InfoD( "DISABLE", "This message should appear" );

        deleteLoggers();
    }


A_TEST_CLASS_END
} // namespace


