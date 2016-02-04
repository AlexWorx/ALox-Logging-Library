// #################################################################################################
//  Unit Tests - ALox Logging Library
//  (Unit Tests to create tutorial sample code and output)
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "alib/compatibility/std_string.hpp"

#include "alox/alox_console_loggers.hpp"
#include "alox/loggers/memorylogger.hpp"



#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define TESTCLASSNAME       CPP_ALox_Log_Debug
#include "aworx_unittests.hpp"

using namespace std;
using namespace ut_aworx;

using namespace aworx;
using namespace aworx::lib;
using namespace aworx::lib::enums;
using namespace aworx::lib::strings;
using namespace aworx::lox;
using namespace aworx::lox::core::textlogger;
using namespace aworx::lox::loggers;


namespace ut_alox {

#if defined (ALOX_DBG_LOG)

    class T : public MetaInfo
    {
        public:       void    t(AString& buf, int64_t diff)     { writeTimeDiff( buf, diff ); }
    };

    class TThread : public threads::Thread
    {
        public: TThread( const String& name, int cntLoops, int sleepMicros )
                : threads::Thread( name )
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
            Log_SetDomain( "TEST/THREAD2", Log::Scope::Method );
            Log_SetDomain( "TEST/THREAD2", Log::DomainLevel::All );

            for ( int i= 0 ; i < cntLoops ; i++ )
            {
                Log_Info( String64( "This is a " ) << name << ". Cnt= " << i );
                ALIB::SleepMillis( 3 );
            }
        }
    };


    /** ********************************************************************************************
     * loggers used
     **********************************************************************************************/
     MemoryLogger*  ml_dbg_log= nullptr;

    /** ********************************************************************************************
     * Creates loggers.
     **********************************************************************************************/
    void   deleteLoggers_dbg_log()
    {
        Log_RemoveDebugLogger();
        Log_RemoveLoggers( nullptr );
        if( ml_dbg_log != nullptr )
        {
            delete ml_dbg_log;
            ml_dbg_log= nullptr;
        }
    }

    void   clearCreateAndAddLoggers_dbg_log( bool memoryLogger= false, bool consoleLogger= true)
    {
        if( Log::DebugLogger )
            Log::RemoveDebugLogger(Log::lox);
        Log::lox->RemoveLoggers();

        if ( consoleLogger )
        {
            Log_Prune( Log::AddDebugLogger( Log::lox, false ); )
            Log_RemoveLogger( Log::DebugLogger );
            Log_AddLogger( Log::DebugLogger );
        }

        if ( memoryLogger )
        {
            ml_dbg_log= new MemoryLogger();
            Log_AddLogger( ml_dbg_log );
        }

        Log_MapThreadName( "UnitTest" );
    }

UT_CLASS()

    /** ********************************************************************************************
     * Log_LogLevelSetting
     **********************************************************************************************/
    UT_METHOD(Log_TextLoggerTimeDiff)

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
        UT_EQ( String16( "000" )._( t.TimeDiffNanos    ),   ms );
        diff= 15;                           ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "015"  )._( t.TimeDiffNanos    ),    ms );
        diff= 99;                           ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "099"  )._( t.TimeDiffNanos    ),    ms );
        diff= 600;                          ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "600"  )._( t.TimeDiffNanos    ),    ms );
        diff= 999;                          ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "999"  )._( t.TimeDiffNanos    ),    ms );
        diff= 1000;                         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "001"  )._( t.TimeDiffMicros   ),    ms );
        t.TimeDiffMinimum= 700;
        diff= 600;                          ms.Clear(); t.t( ms, diff ); UT_EQ( String16(          )._( t.TimeDiffNone     ),    ms );
        diff= 700;                          ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "700"  )._( t.TimeDiffNanos    ),    ms );
        diff= 999;                          ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "999"  )._( t.TimeDiffNanos    ),    ms );
        t.TimeDiffMinimum= 1000;
        diff= 1000;                         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "001"  )._( t.TimeDiffMicros   ),    ms );
        diff= 15 * micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "015"  )._( t.TimeDiffMicros   ),    ms );
        diff= 99 * micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "099"  )._( t.TimeDiffMicros   ),    ms );
        diff= 600* micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "600"  )._( t.TimeDiffMicros   ),    ms );
        diff= 999* micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "999"  )._( t.TimeDiffMicros   ),    ms );
        diff= 1   * millis;                 ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "001"  )._( t.TimeDiffMillis   ),    ms );
        diff= 999 * millis;                 ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "999"  )._( t.TimeDiffMillis   ),    ms );
        diff= 1   * secs;                   ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "1.00" )._( t.TimeDiffSecs     ),    ms );

        diff= 2   * secs + 344 * millis;    ms.Clear(); t.t( ms, diff );
        UT_EQ( String16(  "2.34" )._( t.TimeDiffSecs     ),    ms );

        diff= 3   * secs + 345 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "3.35" )._( t.TimeDiffSecs     ),    ms );
        diff= 9   * secs + 994 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.99" )._( t.TimeDiffSecs     ),    ms );
        diff= 9   * secs + 995 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.0" )._( t.TimeDiffSecs     ),    ms );
        diff= 9   * secs + 999 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.0" )._( t.TimeDiffSecs     ),    ms );
        diff= 10  * secs + 940 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.9" )._( t.TimeDiffSecs     ),    ms );
        diff= 10  * secs + 950 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "11.0" )._( t.TimeDiffSecs     ),    ms );

        diff= 99  * secs + 900 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffSecs     ),    ms );
        diff= 99  * secs + 949 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffSecs     ),    ms );


        diff= 2  * mins + 0 * secs;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "2.00" )._( t.TimeDiffMins     ),    ms );
        diff= 2  * mins + 30 * secs;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "2.50" )._( t.TimeDiffMins     ),    ms );
        diff= 9  * mins + 45 * secs;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.75" )._( t.TimeDiffMins     ),    ms );
        diff= 9  * mins + 59 * secs;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.98" )._( t.TimeDiffMins     ),    ms );
        diff= 9  * mins + 59500 * millis;   ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.99" )._( t.TimeDiffMins     ),    ms );
        diff= 9  * mins + 59999 * millis;   ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.0" )._( t.TimeDiffMins     ),    ms );

        diff= 99 * mins + 0 * secs;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.0" )._( t.TimeDiffMins     ),    ms );
        diff= 99 * mins + 30* secs;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.5" )._( t.TimeDiffMins     ),    ms );
        diff= 99 * mins + 59* secs;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffMins     ),    ms );
        diff= 99 * mins + 59500* millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffMins     ),    ms );
        diff= 99 * mins + 59999* millis;    ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "1.66" )._( t.TimeDiffHours    ),    ms );
        diff= 1 * hours + 30* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "90.0" )._( t.TimeDiffMins     ),    ms );

        diff= 5 * hours + 30* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "5.50" )._( t.TimeDiffHours    ),    ms );

        diff= 9 * hours + 45* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.75" )._( t.TimeDiffHours    ),    ms );
        diff= 9 * hours + 59* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.98" )._( t.TimeDiffHours    ),    ms );
        diff= 9 * hours + 3540* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.98" )._( t.TimeDiffHours    ),    ms );
        diff= 9 * hours + 3580* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.99" )._( t.TimeDiffHours    ),    ms );
        diff= 9 * hours + 3599* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.99" )._( t.TimeDiffHours    ),    ms );
        diff= 9 * hours + 3600* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.0" )._( t.TimeDiffHours    ),    ms );

        diff= 50 * hours + 15 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "50.2" )._( t.TimeDiffHours    ),    ms );
        diff= 99 * hours + 45 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.7" )._( t.TimeDiffHours    ),    ms );
        diff= 99 * hours + 48 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.8" )._( t.TimeDiffHours    ),    ms );
        diff= 99 * hours + 59 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffHours    ),    ms );
        diff= 99 * hours + 3540* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffHours    ),    ms );
        diff= 99 * hours + 3580* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffHours    ),    ms );
        diff= 99 * hours + 3599* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffHours    ),    ms );
        diff= 99 * hours + 3600* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "4.16" )._( t.TimeDiffDays     ),    ms );

        diff= 1 * days + 12* hours;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "36.0" )._( t.TimeDiffHours    ),    ms );

        diff= 5 * days + 18* hours;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "5.75" )._( t.TimeDiffDays     ),    ms );
        diff= 9 * days + 23* hours;         ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.95" )._( t.TimeDiffDays     ),    ms );
        diff= 9 * days + 1380 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.95" )._( t.TimeDiffDays     ),    ms );
        diff= 9 * days + 1400 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.97" )._( t.TimeDiffDays     ),    ms );
        diff= 9 * days + 1439 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "9.99" )._( t.TimeDiffDays     ),    ms );
        diff= 9 * days + 1440 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "10.0" )._( t.TimeDiffDays     ),    ms );
        diff= 15 * days + 6 * hours;        ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "15.2" )._( t.TimeDiffDays     ),    ms );
        diff= 99 * days + 18 * hours;       ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.7" )._( t.TimeDiffDays     ),    ms );
        diff= 99 * days + 1439 * mins;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16(  "99.9" )._( t.TimeDiffDays     ),    ms );
        diff= 99 * days + 1440 * mins;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16( "100.0" )._( t.TimeDiffDays     ),    ms );

        diff= 13452 * days+ 12* hours;      ms.Clear(); t.t( ms, diff ); UT_EQ( String16("13452.5")._( t.TimeDiffDays     ),    ms );
        //System.out.println(ms.ToString());
    }

    /** ********************************************************************************************
     * Log_LogLevelSetting
     **********************************************************************************************/
    #if defined( ALOX_DBG_LOG ) && defined(ALOX_DBG_LOG_CI)
    UT_METHOD(Log_LogLevelSetting)

        clearCreateAndAddLoggers_dbg_log();

        Log_SetDomain( "TLLS_DF", Log::Scope::Method );
        Log_SetDomain( LOG_LOX.InternalDomain, Log::DomainLevel::Off );

        // Test log level setting
        int  logLinesBefore= Log::DebugLogger->CntLogs;

        Log_SetDomain( "TLLS_DF", Log::DomainLevel::All );
        Log_Verbose  (         "This Verbose line should be logged" );
        Log_Info     (         "This Info    line should be logged" );
        Log_Warning  (         "This WARN    line should be logged" );
        Log_Error    (         "This Error   line should be logged" );
        Log_Verbose  (         "(Indented) This Verbose line should be logged", 1 );
        Log_Info     (         "(Indented) This Info    line should be logged", 1 );
        Log_Warning  (         "(Indented) This WARN    line should be logged", 1 );
        Log_Error    (         "(Indented) This Error   line should be logged", 1 );

        Log_SetDomain( "TLLS_DF", Log::DomainLevel::InfoWarningsAndErrors );
        Log_Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Info     (         "This Info    line should be logged" );
        Log_Warning  (         "This Warning line should be logged" );
        Log_Error    (         "This Error   line should be logged" );
        Log_Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Info     (         "(Indented) This Info    line should be logged", 1 );
        Log_Warning  (         "(Indented) This Warning line should be logged", 1 );
        Log_Error    (         "(Indented) This Error   line should be logged", 1 );

        Log_SetDomain( "TLLS_DF", Log::DomainLevel::WarningsAndErrors );
        Log_Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Warning  (         "This Warning line should be logged" );
        Log_Error    (         "This Error   line should be logged" );
        Log_Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Warning  (         "(Indented) This Warning line should be logged", 1 );
        Log_Error    (         "(Indented) This Error   line should be logged", 1 );

        Log_SetDomain( "TLLS_DF", Log::DomainLevel::Errors );
        Log_Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Error    (         "This Error   line should be logged" );
        Log_Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Error    (         "(Indented) This Error   line should be logged", 1 );

        Log_SetDomain( "TLLS_DF", Log::DomainLevel::Off );
        Log_Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Error    (         "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Error    (         "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!", 1 );

        Log_SetDomain( "TLLS", Log::DomainLevel::All );
        Log_Verbose  ( "TLLS", "This Verbose line should be logged" );
        Log_Info     ( "TLLS", "This Info    line should be logged" );
        Log_Warning  ( "TLLS", "This WARN    line should be logged" );
        Log_Error    ( "TLLS", "This Error   line should be logged" );
        Log_Verbose  ( "TLLS", "(Indented) This Verbose line should be logged", 1 );
        Log_Info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        Log_Warning  ( "TLLS", "(Indented) This WARN    line should be logged", 1 );
        Log_Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Log_SetDomain( "TLLS", Log::DomainLevel::InfoWarningsAndErrors );
        Log_Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Info     ( "TLLS", "This Info    line should be logged" );
        Log_Warning  ( "TLLS", "This Warning line should be logged" );
        Log_Error    ( "TLLS", "This Error   line should be logged" );
        Log_Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        Log_Warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        Log_Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Log_SetDomain( "TLLS", Log::DomainLevel::WarningsAndErrors );
        Log_Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Warning  ( "TLLS", "This Warning line should be logged" );
        Log_Error    ( "TLLS", "This Error   line should be logged" );
        Log_Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        Log_Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Log_SetDomain( "TLLS", Log::DomainLevel::Errors );
        Log_Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Error    ( "TLLS", "This Error   line should be logged" );
        Log_Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Log_SetDomain( "TLLS", Log::DomainLevel::Off );
        Log_Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Error    ( "TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        Log_Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log_Error    ( "TLLS", "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!", 1 );

        UT_EQ( 40, (int) Log::DebugLogger->CntLogs - logLinesBefore );
        deleteLoggers_dbg_log();
    }
    #endif

    /** ********************************************************************************************
     * Log_DefaultDomain
     **********************************************************************************************/
    #if defined( ALOX_DBG_LOG_CI )
        UT_METHOD(Log_DefaultDomain)

            int  cntLL;
            clearCreateAndAddLoggers_dbg_log( true );
            Log_Error("No domain and nothing set");

            Log_SetDomain( "REPLACED",  Log::Scope::Method );
            Log_SetDomain( "DFLT",      Log::Scope::Method );

            string testOK=  "OK";
            string testERR= "Error";

            // Test log level setting
            cntLL= Log::DebugLogger->CntLogs;
            Log_SetDomain( "DFLT", Log::DomainLevel::InfoWarningsAndErrors );
            cntLL= Log::DebugLogger->CntLogs;    Log_Verbose    ( testERR );    UT_EQ( 0,        (int) Log::DebugLogger->CntLogs - cntLL );
            cntLL= Log::DebugLogger->CntLogs;    Log_Info       ( testOK  );    UT_EQ( 1,        (int) Log::DebugLogger->CntLogs - cntLL );

            Log_SetDomain( "~",    Log::DomainLevel::WarningsAndErrors );
            cntLL= Log::DebugLogger->CntLogs;    Log_Info       ( testERR );    UT_EQ( 0,        (int) Log::DebugLogger->CntLogs - cntLL );
            cntLL= Log::DebugLogger->CntLogs;    Log_Warning    ( testOK  );    UT_EQ( 1,        (int) Log::DebugLogger->CntLogs - cntLL );

            Log_SetDomain( "~/",   Log::DomainLevel::Errors );
            cntLL= Log::DebugLogger->CntLogs;    Log_Warning    ( testERR );    UT_EQ( 0,        (int) Log::DebugLogger->CntLogs - cntLL );
            cntLL= Log::DebugLogger->CntLogs;    Log_Error      ( testOK  );    UT_EQ( 1,        (int) Log::DebugLogger->CntLogs - cntLL );

            // test sub domains
            Log_SetDomain ( "DFLT/WARN", Log::Scope::None );
            Log_SetDomain (    "~/ERR",  Log::Scope::None );
            Log_LogConfig ( "TEST",      Log::Level::Info, "Dumping Log Configuration:", Log::DebugLogger->Name );

            Log_SetDomain ( "DFLT",      Log::DomainLevel::InfoWarningsAndErrors );
            Log_SetDomain ( "DFLT/WARN", Log::DomainLevel::WarningsAndErrors     );
            Log_SetDomain (    "~/ERR",  Log::DomainLevel::Errors                );

            Log_LogConfig ( "TEST",      Log::Level::Info, "Dumping Log Configuration:", Log::DebugLogger->Name );

            // log with leading "/" on domain
            cntLL= ml_dbg_log->CntLogs;    Log_Verbose( "/DFLT",        testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Verbose( "/DFLT/ERR",    testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Verbose( "/DFLT/WARN",   testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );

            cntLL= ml_dbg_log->CntLogs;    Log_Info   ( "/DFLT",        testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Info   ( "/DFLT/ERR",    testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Info   ( "/DFLT/WARN",   testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );

            cntLL= ml_dbg_log->CntLogs;    Log_Warning( "/DFLT",        testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Warning( "/DFLT/WARN",   testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Warning( "/DFLT/ERR",    testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );

            cntLL= ml_dbg_log->CntLogs;    Log_Error  ( "/DFLT",        testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Error  ( "/DFLT/WARN",   testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Error  ( "/DFLT/ERR",    testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );

            // log without leading "/" on domain, still absolute
            cntLL= ml_dbg_log->CntLogs;    Log_Verbose( "DFLT",         testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Verbose( "DFLT/ERR",     testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Verbose( "DFLT/WARN",    testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );

            cntLL= ml_dbg_log->CntLogs;    Log_Info   ( "DFLT",         testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Info   ( "DFLT/ERR",     testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Info   ( "DFLT/WARN",    testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );

            cntLL= ml_dbg_log->CntLogs;    Log_Warning( "DFLT",         testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Warning( "DFLT/WARN",    testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Warning( "DFLT/ERR",     testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );

            cntLL= ml_dbg_log->CntLogs;    Log_Error  ( "DFLT",         testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Error  ( "DFLT/WARN",    testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Error  ( "DFLT/ERR",     testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );


            // relative addressing with "~"domain
            cntLL= ml_dbg_log->CntLogs;    Log_Verbose(                 testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Verbose( "~",            testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Verbose( "~ERR",         testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Verbose( "~WARN",        testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );

            cntLL= ml_dbg_log->CntLogs;    Log_Info   (                 testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Info   ( "~",            testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Info   ( "~ERR",         testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Info   ( "~WARN",        testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );

            cntLL= ml_dbg_log->CntLogs;    Log_Warning(                 testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Warning( "~",            testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Warning( "~WARN",        testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Warning( "~ERR",         testERR );    UT_EQ( 0, (int) ml_dbg_log->CntLogs - cntLL );

            cntLL= ml_dbg_log->CntLogs;    Log_Error  (                 testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Error  ( "~",            testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Error  ( "~WARN",        testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );
            cntLL= ml_dbg_log->CntLogs;    Log_Error  ( "~ERR",         testOK  );    UT_EQ( 1, (int) ml_dbg_log->CntLogs - cntLL );

            deleteLoggers_dbg_log();
        }
    #endif

    /** ********************************************************************************************
     * Log_DefaultDomain
     **********************************************************************************************/
    UT_METHOD(Log_AssertAndConditional)

        clearCreateAndAddLoggers_dbg_log( true );

        Log_SetDomain( "ASSERT", Log::Scope::None);

        Log_Prune( String testOK=  "OK";    )
        Log_Prune( String testERR= "Error"; )

        // Test log level setting
        int cntLL= Log::DebugLogger->CntLogs;
        Log_SetDomain( "ASSERT", Log::DomainLevel::InfoWarningsAndErrors);

        #ifdef ALOX_DBG_LOG
            int oneLine= 1;
        #else
            int oneLine= 0;
        #endif

        cntLL= Log::DebugLogger->CntLogs;    Log_Assert( true,  "ASSERT",                   testERR         ); UT_EQ( 0,        (int) Log::DebugLogger->CntLogs - cntLL );
        cntLL= Log::DebugLogger->CntLogs;    Log_Assert( false, "ASSERT",                   testOK          ); UT_EQ( oneLine,  (int) Log::DebugLogger->CntLogs - cntLL );
        cntLL= Log::DebugLogger->CntLogs;    Log_Line  ( false, "ASSERT", Log::Level::Info, &testERR, 0, 1 ); UT_EQ( 0,        (int) Log::DebugLogger->CntLogs - cntLL );
        cntLL= Log::DebugLogger->CntLogs;    Log_Line  ( true,  "ASSERT", Log::Level::Info, &testOK,  0, 1 ); UT_EQ( oneLine , (int) Log::DebugLogger->CntLogs - cntLL );

        deleteLoggers_dbg_log();
    }


    /** ********************************************************************************************
     * Log_LineFormat
     **********************************************************************************************/
    UT_METHOD(Log_LineFormat)

        Lox lox;
        clearCreateAndAddLoggers_dbg_log(true, true);
        if (Log::DebugLogger != nullptr )
            lox.AddLogger( Log::DebugLogger );
        lox.AddLogger( ml_dbg_log );

        lox.SetDomain( "FMT", Log::Scope::Method );
        lox.SetDomain( "FMT", Log::DomainLevel::All);

        lox.Info( "This is the default ConsoleLogger log line" );

        String64  lf;
        lf= "%CF(%CL):%CM()%A3[%D][%TD][%TE +%TI] [%t] %L [%O] <%#>: ";   Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "%CF(%CL):%A3[%D][%TD][%TE +%TI] [%t] %L [%O] <%#>: ";        Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "%CF(%CL):%A3[%TD][%TE +%TI] [%t] %L [%O] <%#>: ";            Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "%CF(%CL):%A3[%TE +%TI] [%t] %L [%O] <%#>: ";                 Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "%CF(%CL):%A3[+%TI] [%t] %L [%O] <%#>: ";                     Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "%CF(%CL):%A3[%t] %L [%O] <%#>: ";                            Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "%CF(%CL):%A3%L [%O] <%#>: ";                                 Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "%CF(%CL):%A3[%O] <%#>: ";                                    Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "%CF(%CL):%A3[%O]: ";                                         Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "%CF:%A3[%O]: ";                                              Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "[%O]: ";                                                     Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );
        lf= "";                                                           Log::DebugLogger->MetaInfo->Format= lf;    lox.Info( String128("LineFormat set to= \"") << lf << '\"' );

        Log::DebugLogger->MetaInfo->Format= "%D@";
        ml_dbg_log->MetaInfo->Format= "%D@";
        const char* df;
        df= ">yy-MM-dd<";    Log::DebugLogger->MetaInfo->DateFormat= df;    lox.Info( String128("Date test. Format: \"") << df << '\"' );
        ml_dbg_log->MemoryLog.Clear();
        df= ">yyyy/dd/MM<";  Log::DebugLogger->MetaInfo->DateFormat= df;  ml_dbg_log->MetaInfo->DateFormat= df;           lox.Info( "FMT", String128("Date test. Format: \"") << df << '\"' );
        UT_TRUE( ml_dbg_log->MemoryLog.SearchAndReplace( "/", "@") == 4 );
        Log::DebugLogger->MetaInfo->Format= "%TD@";
        ml_dbg_log->MetaInfo->Format= "%TD@";
        df= ">HH:mm:ss<";    Log::DebugLogger->MetaInfo->TimeOfDayFormat= df;                                          lox.Info( "FMT", String128("Time of day test Format: \"") << df << '\"' );
        ml_dbg_log->MemoryLog.Clear();
        df= ">HH-mm-ss<";    Log::DebugLogger->MetaInfo->TimeOfDayFormat= df;  ml_dbg_log->MetaInfo->TimeOfDayFormat= df; lox.Info( "FMT", String128("Time of day test. Format: \"") << df << '\"' );
        UT_TRUE( ml_dbg_log->MemoryLog.SearchAndReplace( "-", "@") == 4 );

        deleteLoggers_dbg_log();
    }

    /** ********************************************************************************************
     * Log_Replacements
     **********************************************************************************************/
    UT_METHOD(Log_Replacements)

        clearCreateAndAddLoggers_dbg_log(true, true);

        Log_SetDomain( "REPL", Log::Scope::Method );
        Log_SetDomain( "REPL", Log::DomainLevel::All);

        Log_Prune( ml_dbg_log->SetReplacement( "F...", "F-Word"   ); )

        Log_Info( "What the F...!" )

        UT_TRUE( ml_dbg_log->MemoryLog.IndexOf( "F...")   < 0 );
        UT_TRUE( ml_dbg_log->MemoryLog.IndexOf( "F-Word") > 0 );

        deleteLoggers_dbg_log();
    }

    /** ********************************************************************************************
     * Log_Marker
     **********************************************************************************************/
    UT_METHOD(TestMarker)

        clearCreateAndAddLoggers_dbg_log();

        Log_SetDomain( "MARKER", Log::Scope::Method );
        Log_SetDomain( "MARKER", Log::DomainLevel::All );

        Log_Info( "*** Testing markers ***" );
        Log_Prune(String markerDisposedGlobal=    "overwritten global level marker (should NOT appear in the test log)";   )
        Log_Prune(String markerGlobal=            "global marker (this is right to appear in the test log!)";              )
        Log_Prune(String markerDisposedSrc=       "overwritten source level marker (should NOT appear in the test log)";   )
        Log_Prune(String markerSrc=               "source level marker (this is right to appear in the test log!)";       )
        Log_Prune(String markerDisposedMethod=    "overwritten method marker (should NOT appear in the test log)";         )
        Log_Prune(String markerMethod=            "method marker (this is right to appear in the test log!)";              )

        Log_SetMarker( (void*) &markerDisposedGlobal,    Log::Scope::None );
        Log_SetMarker( (void*) &markerGlobal,            Log::Scope::None );
        Log_SetMarker( (void*) &markerDisposedSrc,       Log::Scope::SourceFile );
        Log_SetMarker( (void*) &markerSrc,               Log::Scope::SourceFile );
        Log_SetMarker( (void*) &markerDisposedMethod,    Log::Scope::Method );
        Log_SetMarker( (void*) &markerMethod,            Log::Scope::Method );

        Log_Prune( String notSet=            "NOT SET";              )
        Log_Prune( void* markerpointer= (void*) &notSet; )

        Log_GetMarker( markerpointer, Log::Scope::None );
        Log_Info( String128("The current global level marker is: ") << (String*) markerpointer );
        Log_Prune( UT_TRUE( markerpointer == &markerGlobal ); )

        Log_GetMarker( markerpointer, Log::Scope::SourceFile );
        Log_Info( String128("The current source level marker is: ") << (String*) markerpointer );
        #if defined( ALOX_DBG_LOG_CI )
            UT_TRUE( markerpointer == &markerSrc    );
        #endif
        Log_GetMarker( markerpointer, Log::Scope::Method );
        Log_Info( String128("The current method level marker is: ") << (String*) markerpointer );
        #if defined( ALOX_DBG_LOG_CI )
            UT_TRUE( markerpointer == &markerMethod );
        #endif

        deleteLoggers_dbg_log();
    }

    /** ********************************************************************************************
     * Log_Threads
     **********************************************************************************************/
    UT_METHOD(Log_Threads)

        clearCreateAndAddLoggers_dbg_log();

        Log_SetDomain( "TEST/THREAD1", Log::Scope::Method );
        Log_SetDomain( "TEST/THREAD1", Log::DomainLevel::All );

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
        deleteLoggers_dbg_log();
    }

    /** ********************************************************************************************
     * Log_Exception.
     **********************************************************************************************/
    UT_METHOD(Log_Multiline)

        clearCreateAndAddLoggers_dbg_log();

//        Log::DebugLogger->MetaInfo->MsgPrefixInfo=   "$$$";
//        Log::DebugLogger->MetaInfo->MsgPrefixInfo=   ESC::MAGENTA;
//        Log::DebugLogger->MetaInfo->MsgPostfix=      "###";
//        Log::DebugLogger->MetaInfo->MsgPostfix=      ESC::FG_RESET;
        Log::DebugLogger->FmtMultiLinePostfix=            "<<";

        Log_SetDomain( "MLine", Log::Scope::Method );
        Log_SetDomain( "MLine", Log::DomainLevel::All );


        Log::DebugLogger->MultiLineMsgMode= 0;
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 0 (single line) --------" );
        Log_LogConfig( "MLine", Log::Level::Info, "Our Log configuration is:" );

        Log::DebugLogger->MultiLineMsgMode= 0;
        Log::DebugLogger->MultiLineDelimiterRepl= "~|~";
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 0 (single line) with delimiter replacement set to ~|~ --------" );
        Log_LogConfig( "MLine", Log::Level::Info, "Our Log configuration is:" );

        Log::DebugLogger->MultiLineMsgMode= 0;
        Log::DebugLogger->MultiLineDelimiter= "";
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 0 (single line) with delimiter set to \"\" (stops multi line processing) --------" );
        Log_LogConfig( "MLine", Log::Level::Info, "Our Log configuration is:" );
        Log::DebugLogger->MultiLineDelimiter= (const char*) nullptr; // reset

        Log::DebugLogger->MultiLineMsgMode= 1;
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 1 (multi line, all meta info per line) --------" );
        Log_LogConfig( "MLine", Log::Level::Info, "Our Log configuration is:" );

        Log::DebugLogger->MultiLineMsgMode= 2;
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 2 (multi line, meta info blanked) --------" );
        Log_LogConfig( "MLine", Log::Level::Info, "Our Log configuration is:" );

        Log::DebugLogger->MultiLineMsgMode= 3;
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 3 (multi line, print headline with info, text starts at pos 0) --------" );
        Log_LogConfig( "MLine", Log::Level::Info, "Our Log configuration is:" );

        Log::DebugLogger->MultiLineMsgMode= 4;
        Log_Info( "" );
        Log_Info( "-------- ML Mode = 4 (pure multi line, no meta info, no headline, starts at pos 0)) --------" );
        Log_LogConfig( "MLine", Log::Level::Info, "Our Log configuration is:" );

        deleteLoggers_dbg_log();
    }

    /** ********************************************************************************************
     * Log_ChangeStartTime.
     **********************************************************************************************/
    UT_METHOD(Log_ChangeStartTime)

        clearCreateAndAddLoggers_dbg_log();

        Log_SetDomain( "S-TIME", Log::DomainLevel::All );

        Log_Info ( "S-TIME", "This is the first log with normal start time" );

        Log_Prune( time::Ticks newTime;                       )
        Log_Prune( time::Ticks sub(0); sub.FromMinutes(20);   )
        Log_Prune( newTime.Sub ( sub );                 )
        Log_SetStartTime( newTime, nullptr )
        Log_Info ( "S-TIME", "Starttime set to 20 minutes ago" );
        Log_SetStartTime( time::Ticks(),  nullptr )
        Log_Info ( "S-TIME", "Starttime set to 'now'" );

        deleteLoggers_dbg_log();
    }

    /** ********************************************************************************************
     * Log_DisableLogger.
     **********************************************************************************************/
    UT_METHOD(Log_DisableLogger)

        clearCreateAndAddLoggers_dbg_log();

        Log_SetDomain( "DISABLE", Log::DomainLevel::All );
        Log_Prune( Log::DebugLogger->SetDomain( Log::lox->InternalDomain, Log::DomainLevel::All); )
        auto cntLogs= Log::DebugLogger->CntLogs;
        Log_Info ( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 1, Log::DebugLogger->CntLogs );
        Log_SetLogger( Switch::Off, "NOMATCH" );
        Log_Info ( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 2, Log::DebugLogger->CntLogs );

        Log_Prune( String64 name( Log::DebugLogger->Name ); );
        Log_Prune( name.Delete( 0, 2 );                      );
        Log_Prune( name.Delete( name.Length() - 2 );         );
        Log_Prune( name[0]= '*';                             );
        Log_Prune( name._('*');                         );

        Log_SetLogger( Switch::Off, name );
        Log_Info ( "DISABLE", "This message should NOT appear" );   UT_EQ( cntLogs + 2, Log::DebugLogger->CntLogs );
        Log_SetLogger( Switch::On,  nullptr );
        Log_Info ( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 4, Log::DebugLogger->CntLogs ); // plus one for internal log message
        deleteLoggers_dbg_log();
    }


UT_CLASS_END

#endif // defined (ALOX_DBG_LOG)

} // namespace


