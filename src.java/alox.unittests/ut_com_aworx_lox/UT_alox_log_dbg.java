// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_aworx_lox;

import org.junit.Test;

import ut_com_aworx_uttools.UnitTest;

import com.aworx.lib.ALIB;
import com.aworx.lib.enums.Switch;
import com.aworx.lib.strings.AString;
import com.aworx.lox.*;
import com.aworx.lox.core.textlogger.MetaInfo;
import com.aworx.lox.loggers.MemoryLogger;


public class UT_alox_log_dbg extends UnitTest
{
    /** ********************************************************************************************
     *     Log_TestLogLevelSetting
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void Log_TestTextLoggerTimeDiff()
    {
        class T extends MetaInfo
        {
            public       void     t( AString buf, long diff )         { writeTimeDiff( buf, diff ); } 
        }
        T t= new T();
        AString ms= new AString();
        long diff;
        long micros=   1000L;
        long millis=   1000L * micros;
        long secs=     1000L * millis;
        long mins=        60 * secs;
        long hours=       60 * mins;
        long days=        24 * hours;

        t.timeDiffMinimum= 0;
        diff= 0;                            ms.clear(); t.t( ms, diff ); UT_EQ(  "000" + t.timeDiffNanos,    ms.toString(0,  ms.length() ) );
        diff= 15;                           ms.clear(); t.t( ms, diff ); UT_EQ(  "015" + t.timeDiffNanos,    ms.toString(0,  ms.length() ) );
        diff= 99;                           ms.clear(); t.t( ms, diff ); UT_EQ(  "099" + t.timeDiffNanos,    ms.toString(0,  ms.length() ) );
        diff= 600;                          ms.clear(); t.t( ms, diff ); UT_EQ(  "600" + t.timeDiffNanos,    ms.toString(0,  ms.length() ) );
        diff= 999;                          ms.clear(); t.t( ms, diff ); UT_EQ(  "999" + t.timeDiffNanos,    ms.toString(0,  ms.length() ) );
        diff= 1000;                         ms.clear(); t.t( ms, diff ); UT_EQ(  "001" + t.timeDiffMicros,   ms.toString(0,  ms.length() ) );
        t.timeDiffMinimum= 700;
        diff= 600;                          ms.clear(); t.t( ms, diff ); UT_EQ(          t.timeDiffNone,     ms.toString(0,  ms.length() ) );
        diff= 700;                          ms.clear(); t.t( ms, diff ); UT_EQ(  "700" + t.timeDiffNanos,    ms.toString(0,  ms.length() ) );
        diff= 999;                          ms.clear(); t.t( ms, diff ); UT_EQ(  "999" + t.timeDiffNanos,    ms.toString(0,  ms.length() ) );
        t.timeDiffMinimum= 1000;
        diff= 1000;                         ms.clear(); t.t( ms, diff ); UT_EQ(  "001"  + t.timeDiffMicros,  ms.toString(0,  ms.length() ) );
        diff= 15  * micros;                 ms.clear(); t.t( ms, diff ); UT_EQ(  "015"  + t.timeDiffMicros,  ms.toString(0,  ms.length() ) );
        diff= 99  * micros;                 ms.clear(); t.t( ms, diff ); UT_EQ(  "099"  + t.timeDiffMicros,  ms.toString(0,  ms.length() ) );
        diff= 600 * micros;                 ms.clear(); t.t( ms, diff ); UT_EQ(  "600"  + t.timeDiffMicros,  ms.toString(0,  ms.length() ) );
        diff= 999 * micros;                 ms.clear(); t.t( ms, diff ); UT_EQ(  "999"  + t.timeDiffMicros,  ms.toString(0,  ms.length() ) );
        diff= 1   * millis;                 ms.clear(); t.t( ms, diff ); UT_EQ(  "001"  + t.timeDiffMillis,  ms.toString(0,  ms.length() ) );
        diff= 999 * millis;                 ms.clear(); t.t( ms, diff ); UT_EQ(  "999"  + t.timeDiffMillis,  ms.toString(0,  ms.length() ) );
        diff= 1   * secs;                   ms.clear(); t.t( ms, diff ); UT_EQ(  "1.00" + t.timeDiffSecs,    ms.toString(0,  ms.length() ) );
        diff= 2   * secs + 344 * millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "2.34" + t.timeDiffSecs,    ms.toString(0,  ms.length() ) );
        diff= 3   * secs + 345 * millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "3.35" + t.timeDiffSecs,    ms.toString(0,  ms.length() ) );
        diff= 9   * secs + 994 * millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "9.99" + t.timeDiffSecs,    ms.toString(0,  ms.length() ) );
        diff= 9   * secs + 995 * millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "10.0" + t.timeDiffSecs,    ms.toString(0,  ms.length() ) );
        diff= 9   * secs + 999 * millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "10.0" + t.timeDiffSecs,    ms.toString(0,  ms.length() ) );
        diff= 10  * secs + 940 * millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "10.9" + t.timeDiffSecs,    ms.toString(0,  ms.length() ) );
        diff= 10  * secs + 950 * millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "11.0" + t.timeDiffSecs,    ms.toString(0,  ms.length() ) );

        diff= 99  * secs + 900 * millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.timeDiffSecs,    ms.toString(0,  ms.length() ) );
        diff= 99  * secs + 949 * millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.timeDiffSecs,    ms.toString(0,  ms.length() ) );

//        diff= 99  * secs + 950 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.fmtTimeDiffSecs,        ms.toString(0,  ms.Length ) );

        diff= 2  * mins + 0 * secs;         ms.clear(); t.t( ms, diff ); UT_EQ(  "2.00" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );
        diff= 2  * mins + 30 * secs;        ms.clear(); t.t( ms, diff ); UT_EQ(  "2.50" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );
        diff= 9  * mins + 45 * secs;        ms.clear(); t.t( ms, diff ); UT_EQ(  "9.75" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );
        diff= 9  * mins + 59 * secs;        ms.clear(); t.t( ms, diff ); UT_EQ(  "9.98" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );
        diff= 9  * mins + 59500 * millis;   ms.clear(); t.t( ms, diff ); UT_EQ(  "9.99" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );
        diff= 9  * mins + 59999 * millis;   ms.clear(); t.t( ms, diff ); UT_EQ(  "10.0" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );

        diff= 99 * mins + 0 * secs;         ms.clear(); t.t( ms, diff ); UT_EQ(  "99.0" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );
        diff= 99 * mins + 30* secs;         ms.clear(); t.t( ms, diff ); UT_EQ(  "99.5" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );
        diff= 99 * mins + 59* secs;         ms.clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );
        diff= 99 * mins + 59500* millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );
        diff= 99 * mins + 59999* millis;    ms.clear(); t.t( ms, diff ); UT_EQ(  "1.66" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 1 * hours + 30* mins;         ms.clear(); t.t( ms, diff ); UT_EQ(  "90.0" + t.timeDiffMins,    ms.toString(0,  ms.length() ) );

        diff= 5 * hours + 30* mins;         ms.clear(); t.t( ms, diff ); UT_EQ(  "5.50" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );

        diff= 9 * hours + 45* mins;         ms.clear(); t.t( ms, diff ); UT_EQ(  "9.75" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 9 * hours + 59* mins;         ms.clear(); t.t( ms, diff ); UT_EQ(  "9.98" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 9 * hours + 3540* secs;       ms.clear(); t.t( ms, diff ); UT_EQ(  "9.98" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 9 * hours + 3580* secs;       ms.clear(); t.t( ms, diff ); UT_EQ(  "9.99" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 9 * hours + 3599* secs;       ms.clear(); t.t( ms, diff ); UT_EQ(  "9.99" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 9 * hours + 3600* secs;       ms.clear(); t.t( ms, diff ); UT_EQ(  "10.0" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );

        diff= 50 * hours + 15 *mins;        ms.clear(); t.t( ms, diff ); UT_EQ(  "50.2" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 99 * hours + 45 *mins;        ms.clear(); t.t( ms, diff ); UT_EQ(  "99.7" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 99 * hours + 48 *mins;        ms.clear(); t.t( ms, diff ); UT_EQ(  "99.8" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 99 * hours + 59 *mins;        ms.clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 99 * hours + 3540* secs;      ms.clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 99 * hours + 3580* secs;      ms.clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 99 * hours + 3599* secs;      ms.clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.timeDiffHours,   ms.toString(0,  ms.length() ) );
        diff= 99 * hours + 3600* secs;      ms.clear(); t.t( ms, diff ); UT_EQ(  "4.16" + t.timeDiffDays,    ms.toString(0,  ms.length() ) );

        diff= 1 * days + 12* hours;         ms.clear(); t.t( ms, diff ); UT_EQ(  "36.0" + t.timeDiffHours,    ms.toString(0,  ms.length() ) );

        diff= 5 * days + 18* hours;         ms.clear(); t.t( ms, diff ); UT_EQ(  "5.75" + t.timeDiffDays,        ms.toString(0,  ms.length() ) );
        diff= 9 * days + 23* hours;         ms.clear(); t.t( ms, diff ); UT_EQ(  "9.95" + t.timeDiffDays,        ms.toString(0,  ms.length() ) );
        diff= 9 * days + 1380 * mins;       ms.clear(); t.t( ms, diff ); UT_EQ(  "9.95" + t.timeDiffDays,        ms.toString(0,  ms.length() ) );
        diff= 9 * days + 1400 * mins;       ms.clear(); t.t( ms, diff ); UT_EQ(  "9.97" + t.timeDiffDays,        ms.toString(0,  ms.length() ) );
        diff= 9 * days + 1439 * mins;       ms.clear(); t.t( ms, diff ); UT_EQ(  "9.99" + t.timeDiffDays,        ms.toString(0,  ms.length() ) );
        diff= 9 * days + 1440 * mins;       ms.clear(); t.t( ms, diff ); UT_EQ(  "10.0" + t.timeDiffDays,        ms.toString(0,  ms.length() ) );
        diff= 15 * days + 6 * hours;        ms.clear(); t.t( ms, diff ); UT_EQ(  "15.2" + t.timeDiffDays,        ms.toString(0,  ms.length() ) );
        diff= 99 * days + 18 * hours;       ms.clear(); t.t( ms, diff ); UT_EQ(  "99.7" + t.timeDiffDays,        ms.toString(0,  ms.length() ) );
        diff= 99 * days + 1439 * mins;      ms.clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.timeDiffDays,        ms.toString(0,  ms.length() ) );
        diff= 99 * days + 1440 * mins;      ms.clear(); t.t( ms, diff ); UT_EQ(  "100.0"+ t.timeDiffDays,    ms.toString(0,  ms.length() ) );

        diff= 13452 * days + 12* hours;     ms.clear(); t.t( ms, diff ); UT_EQ("13452.5"+ t.timeDiffDays,    ms.toString(0,  ms.length() ) );
        //System.out.println(ms.toString());
    }

    /** ********************************************************************************************
     *     Log_TestLogLevelSetting
     **********************************************************************************************/
    @Test
    public void Log_TestLogLevelSetting()
    {
        resetLoxAndCreateDebugLogger();
        
        Log.setDomain( "TLLS_DF", Log.Scope.METHOD );
        Log.setDomain( Log.LOX.internalDomain, Log.DomainLevel.OFF );

        // Test log level setting
        int logLinesBefore= Log.debugLogger.cntLogs;
        Log.setDomain( "TLLS_DF", Log.DomainLevel.ALL );
        Log.verbose  (         "This Verbose line should be logged" );
        Log.info     (         "This Info    line should be logged" );
        Log.warning  (         "This WARN    line should be logged" );
        Log.error    (         "This Error   line should be logged" );
        Log.verbose  (         "(Indented) This Verbose line should be logged", 1 );
        Log.info     (         "(Indented) This Info    line should be logged", 1 );
        Log.warning  (         "(Indented) This WARN    line should be logged", 1 );
        Log.error    (         "(Indented) This Error   line should be logged", 1 );

        Log.setDomain( "TLLS_DF", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
        Log.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     (         "This Info    line should be logged" );
        Log.warning  (         "This Warning line should be logged" );
        Log.error    (         "This Error   line should be logged" );
        Log.verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.info     (         "(Indented) This Info    line should be logged", 1 );
        Log.warning  (         "(Indented) This Warning line should be logged", 1 );
        Log.error    (         "(Indented) This Error   line should be logged", 1 );


        Log.setDomain( "TLLS_DF", Log.DomainLevel.WARNINGS_AND_ERRORS );
        Log.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  (         "This Warning line should be logged" );
        Log.error    (         "This Error   line should be logged" );
        Log.verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.warning  (         "(Indented) This Warning line should be logged", 1 );
        Log.error    (         "(Indented) This Error   line should be logged", 1 );

        Log.setDomain( "TLLS_DF", Log.DomainLevel.ERRORS );
        Log.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.error    (         "This Error   line should be logged" );
        Log.verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.error    (         "(Indented) This Error   line should be logged", 1 );

        Log.setDomain( "TLLS_DF", Log.DomainLevel.OFF );
        Log.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.error    (         "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.error    (         "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!" );


        Log.setDomain( "TLLS", Log.DomainLevel.ALL );
        Log.verbose  ( "TLLS", "This Verbose line should be logged" );
        Log.info     ( "TLLS", "This Info    line should be logged" );
        Log.warning  ( "TLLS", "This WARN    line should be logged" );
        Log.error    ( "TLLS", "This Error   line should be logged" );
        Log.verbose  ( "TLLS", "(Indented) This Verbose line should be logged", 1 );
        Log.info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        Log.warning  ( "TLLS", "(Indented) This WARN    line should be logged", 1 );
        Log.error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Log.setDomain( "TLLS", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
        Log.verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     ( "TLLS", "This Info    line should be logged" );
        Log.warning  ( "TLLS", "This Warning line should be logged" );
        Log.error    ( "TLLS", "This Error   line should be logged" );
        Log.verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        Log.warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        Log.error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );


        Log.setDomain( "TLLS", Log.DomainLevel.WARNINGS_AND_ERRORS );
        Log.verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  ( "TLLS", "This Warning line should be logged" );
        Log.error    ( "TLLS", "This Error   line should be logged" );
        Log.verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        Log.error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Log.setDomain( "TLLS", Log.DomainLevel.ERRORS );
        Log.verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.error    ( "TLLS", "This Error   line should be logged" );
        Log.verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Log.setDomain( "TLLS", Log.DomainLevel.OFF );
        Log.verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.error    ( "TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.error    ( "TLLS", "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        UT_EQ( 40, Log.debugLogger.cntLogs - logLinesBefore );
    }

    /** ********************************************************************************************
     *     Log_TestDefaultDomain
     **********************************************************************************************/
    @Test
    public void Log_TestDefaultDomain()
    {
        int cntLL;
        MemoryLogger ml= new MemoryLogger();
        Log.addLogger( ml );

        Log.setDomain( "DFLT", Log.Scope.METHOD );
        Log.setDomain( "DFLT", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
        Log.info( "***Log_TestDefaultDomain***" );


        String testOK=  "OK";
        String testERR= "Error";

        // Test log level setting
        cntLL= Log.debugLogger.cntLogs;
        Log.setDomain( "DFLT",Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
        cntLL= Log.debugLogger.cntLogs;    Log.verbose   ( testERR );    UT_EQ ( 0, Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.info      ( testOK  );    UT_EQ ( 1, Log.debugLogger.cntLogs - cntLL );

        Log.setDomain( "~",   Log.DomainLevel.WARNINGS_AND_ERRORS );
        cntLL= Log.debugLogger.cntLogs;    Log.info      ( testERR );    UT_EQ ( 0, Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.warning   ( testOK  );    UT_EQ ( 1, Log.debugLogger.cntLogs - cntLL );

        Log.setDomain( "~/",  Log.DomainLevel.ERRORS );
        cntLL= Log.debugLogger.cntLogs;    Log.warning   ( testERR );    UT_EQ ( 0, Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.error     ( testOK  );    UT_EQ ( 1, Log.debugLogger.cntLogs - cntLL );


        // test sub domains
        Log.setDomain( "DFLT/WARN",   Log.Scope.NONE );
        Log.setDomain(    "~/ERR",    Log.Scope.NONE );
        Log.logConfig( "TEST",        Log.Level.INFO, "Dumping Log Configuration:", Log.debugLogger.name );

        Log.setDomain( "DFLT",        Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
        Log.setDomain( "DFLT/WARN",   Log.DomainLevel.WARNINGS_AND_ERRORS      );
        Log.setDomain(    "~/ERR",    Log.DomainLevel.ERRORS                   );

        Log.logConfig( "TEST",  Log.Level.INFO, "Dumping Log Configuration:", Log.debugLogger.name );

        // log with leading "/" on domain
        cntLL= ml.cntLogs;    Log.verbose    ( "/DFLT",        testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "/DFLT/ERR",    testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "/DFLT/WARN",   testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.info       ( "/DFLT",        testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "/DFLT/ERR",    testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "/DFLT/WARN",   testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.warning    ( "/DFLT",        testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "/DFLT/WARN",   testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "/DFLT/ERR",    testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.error      ( "/DFLT",        testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "/DFLT/WARN",   testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "/DFLT/ERR",    testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );

        // log without leading "/" on domain, still absolute
        cntLL= ml.cntLogs;    Log.verbose    ( "DFLT",         testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "DFLT/ERR",     testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "DFLT/WARN",    testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.info       ( "DFLT",         testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "DFLT/ERR",     testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "DFLT/WARN",    testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.warning    ( "DFLT",         testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "DFLT/WARN",    testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "DFLT/ERR",     testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.error      ( "DFLT",         testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "DFLT/WARN",    testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "DFLT/ERR",     testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );


        // relative addressing with "~"domain
        cntLL= ml.cntLogs;    Log.verbose    (                 testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "~",            testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "~ERR",         testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "~WARN",        testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.info       (                 testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "~",            testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "~ERR",         testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "~WARN",        testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.warning    (                 testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "~",            testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "~WARN",        testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "~ERR",         testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.error      (                 testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "~",            testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "~WARN",        testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "~ERR",         testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );

        Log.removeLogger( ml );
    }

    /** ****************************************************************************************
     *     Log_TestDefaultDomain
     ******************************************************************************************/
    @Test
    public void Log_TestAssertAndConditional()
    {
        Log.setDomain( "ASSERT", Log.Scope.METHOD );

        String testOK=  "OK";
        String testERR= "Error";

        // Test log level setting
        int cntLL= Log.debugLogger.cntLogs;
        Log.setDomain( "ASSERT", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS);

        cntLL= Log.debugLogger.cntLogs;    Log.Assert( true,  testERR );                           UT_EQ(  0, Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.Assert( false, testOK  );                           UT_EQ(  1, Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.line   ( false, null, Log.Level.INFO, testERR );    UT_EQ(  0, Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.line   ( true,  null, Log.Level.INFO, testOK  );    UT_EQ(  1, Log.debugLogger.cntLogs - cntLL );
    }

    /** ****************************************************************************************
     *     Log_TestDefaultDomain
     ******************************************************************************************/
    @Test
    public void Log_TestLineFormat()
    {
        Log.setDomain( "FMT", Log.Scope.METHOD );
        Log.setDomain( "FMT", Log.DomainLevel.ALL);

        Log.info( "This is the default ConsoleLogger log line" );
        com.aworx.lox.core.textlogger.AutoSizes backup= Log.debugLogger.autoSizes;
        Log.debugLogger.autoSizes= new com.aworx.lox.core.textlogger.AutoSizes();

        AString  lf;
        lf= new AString( "(%CF) %CP.%CC.%CM():%A3[%D][%TD][%TE +%TI] [%t] %L [%O] <%#>: ");    Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(     "(%CF) %CC.%CM():%A3[%D][%TD][%TE +%TI] [%t] %L [%O] <%#>: ");    Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%CF) %CM():%A3[%D][%TD][%TE +%TI] [%t] %L [%O] <%#>: ");    Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%CF) %CM():%A3[%TD][%TE +%TI] [%t] %L [%O] <%#>: ");        Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%CF) %CM():%A3[%TE +%TI] [%t] %L [%O] <%#>: ");             Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%CF) %CM():%A3[+%TI] [%t] %L [%O] <%#>: ");                 Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%CF) %CM():%A3[%t] %L [%O] <%#>: ");                        Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%CF) %CM():%A3%L [%O] <%#>: ");                             Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%CF) %CM():%A3[%O] <%#>: ");                                Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%CF) %CM():%A3[%O]: ");                                     Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%CF):%A3[%O]: ");                                           Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "[%O]: ");                                                            Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "");                                                                  Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );

        Log.debugLogger.autoSizes= backup;
    }


    /** ****************************************************************************************
     *     Log_TestMarker
     ******************************************************************************************/
    @Test
    public void Log_TestMarker()
    {
        Log.setDomain( "MARKER", Log.Scope.METHOD );
        Log.setDomain( "MARKER", Log.DomainLevel.ALL );

        Log.info( "*** Testing markers ***" );
        final String markerDisposedGlobal=   "overwritten global marker (should NOT appear in the test log)";
        final String markerGlobal=           "global marker (this is right to appear in the test log!)";
        //final String markerDisposedPkg=      "overwritten package level marker (should NOT appear in the test log)";
        //final String markerPkg=              "package level marker (this is right to appear in the test log!)";
        final String markerDisposedClass=    "overwritten class marker (should NOT appear in the test log)";
        final String markerClass=            "class marker (this is right to appear in the test log!)";
        final String markerDisposedMethod=   "overwritten method marker (should NOT appear in the test log)";
        final String markerMethod=           "method marker (this is right to appear in the test log!)";


        /*#/AWX_LOG// Log.setMarker( markerDisposedSrc,    true );        //#/AWX_LOG*/
        Log.setMarker( markerDisposedGlobal, Log.Scope.NONE    );
        Log.setMarker( markerGlobal,         Log.Scope.NONE    );
        //Log.setMarker( markerDisposedPkg,    Log.Scope.PACKAGE );
        //Log.setMarker( markerPkg,            Log.Scope.PACKAGE );
        Log.setMarker( markerDisposedClass,  Log.Scope.CLASS   );
        Log.setMarker( markerClass,          Log.Scope.CLASS   );
        Log.setMarker( markerDisposedMethod, Log.Scope.METHOD  );
        Log.setMarker( markerMethod,         Log.Scope.METHOD  );

        Object marker;

        marker= Log.getMarker( Log.Scope.NONE );    Log.info( "The current global        marker is: " + marker );     UT_TRUE( (String) marker == markerGlobal    );
        //marker= Log.getMarker( Log.Scope.PACKAGE ); Log.info( "The current package level marker is: " + marker );     UT_TRUE( (String) marker == markerPkg       );
        marker= Log.getMarker( Log.Scope.CLASS );   Log.info( "The current class   level marker is: " + marker );     UT_TRUE( (String) marker == markerClass     );
        marker= Log.getMarker( Log.Scope.METHOD );  Log.info( "The current method  level marker is: " + marker );     UT_TRUE( (String) marker == markerMethod    );
    }


    /** ****************************************************************************************
     *     Log_TestThreads
     ******************************************************************************************/
    @Test
    public void Log_TestThreads()
    {
        Log.setDomain ( "TEST/THREAD1", Log.Scope.METHOD );
        Log.setDomain ( "TEST/THREAD1", Log.DomainLevel.ALL );

        // if this gets commented out, the test might crash. At least the console will
        // become scrambled!
        //Log.LOX.Lock.setUnsafe( true );

        Thread thread = new Thread( new TestDifferentThreadMethod() );
        thread.setName( "Thread2" );
        thread.start();

        for ( int i= 0 ; i < 50 ; i++ )
        {
            Log.info( "This is the main thread ");// + i );
            ALIB.sleepMillis( 4 );
        }
    }

    class TestDifferentThreadMethod implements Runnable
    {
        @Override public void run()
        {
            Log.setDomain ( "TEST/THREAD2", Log.Scope.METHOD );
            Log.setDomain ( "TEST/THREAD2", Log.DomainLevel.ALL );

            for ( int i= 0 ; i < 20 ; i++ )
            {
                Log.info( "This is a different Thread. Cnt= " + i );
                ALIB.sleepMillis( 3 );
            }
        }
    }


    /** ****************************************************************************************
     *     Log_TestMultiline.
     ******************************************************************************************/
    @Test
    public void Log_TestMultiline()
    {
        Log.setDomain( "MLine", Log.Scope.METHOD );
        Log.setDomain( "MLine", Log.DomainLevel.ALL );


        Log.debugLogger.multiLineMsgMode= 0;
        Log.info( "" );
        Log.info( "-------- ML Mode = 0 (single line) --------" );
        Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 0;
        Log.debugLogger.multiLineDelimiterRepl= "~|~";
        Log.info( "" );
        Log.info( "-------- ML Mode = 0 (single line) with delimiter replacement set to ~|~ --------" );
        Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 0;
        Log.debugLogger.multiLineDelimiter= "";
        Log.info( "" );
        Log.info( "-------- ML Mode = 0 (single line) with delimiter set to \"\" (stops multi line processing) --------" );
        Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 1;
        Log.info( "" );
        Log.info( "-------- ML Mode = 1 (multi line, all meta info per line) --------" );
        Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 2;
        Log.info( "" );
        Log.info( "-------- ML Mode = 2 (multi line, meta info blanked) --------" );
        Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 3;
        Log.info( "" );
        Log.info( "-------- ML Mode = 3 (multi line, print headline with info, text starts at pos 0) --------" );
        Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 4;
        Log.info( "" );
        Log.info( "-------- ML Mode = 4 (pure multi line, no meta info, no headline, starts at pos 0)) --------" );
        Log.logConfig( "MLine", Log.Level.INFO, "Our Log configuration is:" );
    }

    /** ****************************************************************************************
     *     Log_DisableLogger.
     ******************************************************************************************/
    @Test
    public void Log_DisableLogger()
    {
        resetLoxAndCreateDebugLogger();
        Log.setDomain( "DISABLE", Log.DomainLevel.ALL );
        Log.info( "DISABLE", "Testing disabling a logger with filter" );
        int cntLogs= (int) Log.debugLogger.cntLogs;
        Log.info( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 1, Log.debugLogger.cntLogs );
        Log.setLogger( Switch.OFF, "NOMATCH" );
        Log.info( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 2, Log.debugLogger.cntLogs );
        AString name= new AString( Log.debugLogger.name );
        name.delete( 0, 2 );
        name.delete( name.length() - 4 );
        name.buffer()[0]= '*';
        name._('*');
        Log.setLogger( Switch.OFF, name.toString() );
        Log.info( "DISABLE", "This message should NOT appear" );   UT_EQ( cntLogs + 2, Log.debugLogger.cntLogs );
        Log.setLogger( Switch.ON, null );
        Log.info( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 3, Log.debugLogger.cntLogs );
    }

}
