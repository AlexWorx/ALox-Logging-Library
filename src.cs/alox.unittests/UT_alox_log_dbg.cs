// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;
using System.Xml.Linq;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib.strings;
using ut_cs_aworx;

#if ALIB_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if ALIB_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using cs.aworx.lib;
using cs.aworx.lox;
using cs.aworx.lox.core;
using cs.aworx.lox.loggers;
using cs.aworx.lox.tools;
using System.Collections.Generic;

#if !WINDOWS_PHONE
    using cs.aworx.lox.tools.json;
#endif

namespace ut_cs_aworx_lox
{
    #if ALIB_MONO_DEVELOP
        [TestFixture ()]
    #endif
    #if ALIB_VSTUDIO
        [TestClass]
    #endif
    public class CS_ALox   : UnitTest
    {
    /** ********************************************************************************************
     * The loggers.
     **********************************************************************************************/
    #if ALOX_DBG_LOG || ALOX_REL_LOG
        public static ConsoleLogger       cl;
        public static MemoryLogger        ml;
    #endif  // ALOX_DBG_LOG || ALOX_REL_LOG

    /** ********************************************************************************************
     * Creates loggers.
     **********************************************************************************************/
    public void   clearCreateAndAddLoggers( bool memoryLogger= false, bool consoleLogger= true)
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Log.Reset();
            cl= null;
            ml= null;

            if ( consoleLogger )
            {
                cl= new ConsoleLogger("UNITTESTLOGGER");
                Log.AddLogger( cl );
            }

            if ( memoryLogger )
            {
                ml= new MemoryLogger();
                Log.AddLogger( ml );
            }

            Log.MapThreadName( "UnitTest" );
        #endif  // ALOX_DBG_LOG || ALOX_REL_LOG
    }

    /** ********************************************************************************************
     * Log.TestLogLevelSetting
     **********************************************************************************************/
    #if ALOX_DBG_LOG || ALOX_REL_LOG
        protected class T : MetaInfo
        {
            public       void    t(AString buf, long diff)     { writeTimeDiff( buf, diff ); }
        }
    #endif

    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_TestTextLoggerTimeDiff()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        T t= new T();
        t.TimeDiffMinimum= 0;
        AString ms= new AString();
        long diff;
        long micros=     1000L;
        long millis=     1000L * micros;
        long secs=       1000L * millis;
        long mins=          60 * secs;
        long hours=         60 * mins;
        long days=          24 * hours;


        t.TimeDiffMinimum= 0;
        diff= 0;                            ms.Clear(); t.t( ms, diff ); UT_EQ(   "000" + t.TimeDiffNanos,   ms.ToString(0, ms.Length() ) );
        diff= 15;                           ms.Clear(); t.t( ms, diff ); UT_EQ(   "015" + t.TimeDiffNanos,   ms.ToString(0, ms.Length() ) );
        diff= 99;                           ms.Clear(); t.t( ms, diff ); UT_EQ(   "099" + t.TimeDiffNanos,   ms.ToString(0, ms.Length() ) );
        diff= 600;                          ms.Clear(); t.t( ms, diff ); UT_EQ(   "600" + t.TimeDiffNanos,   ms.ToString(0, ms.Length() ) );
        diff= 999;                          ms.Clear(); t.t( ms, diff ); UT_EQ(   "999" + t.TimeDiffNanos,   ms.ToString(0, ms.Length() ) );
        diff= 1000;                         ms.Clear(); t.t( ms, diff ); UT_EQ(   "001" + t.TimeDiffMicros,  ms.ToString(0, ms.Length() ) );
        t.TimeDiffMinimum= 700;
        diff= 600;                          ms.Clear(); t.t( ms, diff ); UT_EQ(           t.TimeDiffNone,    ms.ToString(0, ms.Length() ) );
        diff= 700;                          ms.Clear(); t.t( ms, diff ); UT_EQ(   "700" + t.TimeDiffNanos,   ms.ToString(0, ms.Length() ) );
        diff= 999;                          ms.Clear(); t.t( ms, diff ); UT_EQ(   "999" + t.TimeDiffNanos,   ms.ToString(0, ms.Length() ) );
        t.TimeDiffMinimum= 1000;
        diff= 1000;                         ms.Clear(); t.t( ms, diff ); UT_EQ(   "001" + t.TimeDiffMicros,  ms.ToString(0, ms.Length() ) );
        diff= 15 * micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ(   "015" + t.TimeDiffMicros,  ms.ToString(0, ms.Length() ) );
        diff= 99 * micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ(   "099" + t.TimeDiffMicros,  ms.ToString(0, ms.Length() ) );
        diff= 600* micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ(   "600" + t.TimeDiffMicros,  ms.ToString(0, ms.Length() ) );
        diff= 999* micros;                  ms.Clear(); t.t( ms, diff ); UT_EQ(   "999" + t.TimeDiffMicros,  ms.ToString(0, ms.Length() ) );
        diff= 1   * millis;                 ms.Clear(); t.t( ms, diff ); UT_EQ(   "001" + t.TimeDiffMillis,  ms.ToString(0, ms.Length() ) );
        diff= 999 * millis;                 ms.Clear(); t.t( ms, diff ); UT_EQ(   "999" + t.TimeDiffMillis,  ms.ToString(0, ms.Length() ) );
        diff= 1   * secs;                   ms.Clear(); t.t( ms, diff ); UT_EQ(  "1.00" + t.TimeDiffSecs,    ms.ToString(0, ms.Length() ) );
        diff= 2   * secs + 344 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "2.34" + t.TimeDiffSecs,    ms.ToString(0, ms.Length() ) );
        diff= 3   * secs + 345 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "3.35" + t.TimeDiffSecs,    ms.ToString(0, ms.Length() ) );
        diff= 9   * secs + 994 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.99" + t.TimeDiffSecs,    ms.ToString(0, ms.Length() ) );
        diff= 9   * secs + 995 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "10.0" + t.TimeDiffSecs,    ms.ToString(0, ms.Length() ) );
        diff= 9   * secs + 999 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "10.0" + t.TimeDiffSecs,    ms.ToString(0, ms.Length() ) );
        diff= 10  * secs + 940 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "10.9" + t.TimeDiffSecs,    ms.ToString(0, ms.Length() ) );
        diff= 10  * secs + 950 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "11.0" + t.TimeDiffSecs,    ms.ToString(0, ms.Length() ) );

        diff= 99  * secs + 900 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.TimeDiffSecs,    ms.ToString(0, ms.Length() ) );
        diff= 99  * secs + 949 * millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.TimeDiffSecs,    ms.ToString(0, ms.Length() ) );


        diff= 2  * mins + 0 * secs;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "2.00" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );
        diff= 2  * mins + 30 * secs;        ms.Clear(); t.t( ms, diff ); UT_EQ(  "2.50" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );
        diff= 9  * mins + 45 * secs;        ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.75" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );
        diff= 9  * mins + 59 * secs;        ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.98" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );
        diff= 9  * mins + 59500 * millis;   ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.99" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );
        diff= 9  * mins + 59999 * millis;   ms.Clear(); t.t( ms, diff ); UT_EQ(  "10.0" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );

        diff= 99 * mins + 0 * secs;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.0" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );
        diff= 99 * mins + 30* secs;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.5" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );
        diff= 99 * mins + 59* secs;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );
        diff= 99 * mins + 59500* millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );
        diff= 99 * mins + 59999* millis;    ms.Clear(); t.t( ms, diff ); UT_EQ(  "1.66" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 1 * hours + 30* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "90.0" + t.TimeDiffMins,    ms.ToString(0, ms.Length() ) );

        diff= 5 * hours + 30* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "5.50" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );

        diff= 9 * hours + 45* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.75" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 9 * hours + 59* mins;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.98" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 9 * hours + 3540* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.98" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 9 * hours + 3580* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.99" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 9 * hours + 3599* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.99" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 9 * hours + 3600* secs;       ms.Clear(); t.t( ms, diff ); UT_EQ(  "10.0" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );

        diff= 50 * hours + 15 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ(  "50.2" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 99 * hours + 45 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.7" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 99 * hours + 48 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.8" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 99 * hours + 59 *mins;        ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 99 * hours + 3540* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 99 * hours + 3580* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 99 * hours + 3599* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.TimeDiffHours,   ms.ToString(0, ms.Length() ) );
        diff= 99 * hours + 3600* secs;      ms.Clear(); t.t( ms, diff ); UT_EQ(  "4.16" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );

        diff= 1 * days + 12* hours;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "36.0" + t.TimeDiffHours,    ms.ToString(0, ms.Length() ) );

        diff= 5 * days + 18* hours;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "5.75" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );
        diff= 9 * days + 23* hours;         ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.95" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );
        diff= 9 * days + 1380 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.95" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );
        diff= 9 * days + 1400 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.97" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );
        diff= 9 * days + 1439 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ(  "9.99" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );
        diff= 9 * days + 1440 * mins;       ms.Clear(); t.t( ms, diff ); UT_EQ(  "10.0" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );
        diff= 15 * days + 6 * hours;        ms.Clear(); t.t( ms, diff ); UT_EQ(  "15.2" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );
        diff= 99 * days + 18 * hours;       ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.7" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );
        diff= 99 * days + 1439 * mins;      ms.Clear(); t.t( ms, diff ); UT_EQ(  "99.9" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );
        diff= 99 * days + 1440 * mins;      ms.Clear(); t.t( ms, diff ); UT_EQ( "100.0" + t.TimeDiffDays,    ms.ToString(0, ms.Length() ) );

        diff= 13452 * days+ 12* hours;      ms.Clear(); t.t( ms, diff ); UT_EQ("13452.5" + t.TimeDiffDays,   ms.ToString(0, ms.Length() ) );
        //System.out.println(ms.ToString());
        #endif
    }

    /** ********************************************************************************************
     * Log_TestLogLevelSetting
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_TestLogLevelSetting()
    {

        #if ALOX_DBG_LOG || ALOX_REL_LOG
        clearCreateAndAddLoggers();

        Log.SetDomain( "TLLS_DF", Log.Scope.Method );
        #if ALOX_DBG_LOG
            Log.SetDomain( Log.LOX.InternalDomain, Log.DomainLevel.Off );
        #endif

        // Test log level setting
        uint logLinesBefore= cl.CntLogs;

        Log.SetDomain( "TLLS_DF", Log.DomainLevel.All );
        Log.Verbose  (         "This Verbose line should be logged" );
        Log.Info     (         "This Info    line should be logged" );
        Log.Warning  (         "This WARN    line should be logged" );
        Log.Error    (         "This Error   line should be logged" );
        Log.Verbose  (         "(Indented) This Verbose line should be logged", 1 );
        Log.Info     (         "(Indented) This Info    line should be logged", 1 );
        Log.Warning  (         "(Indented) This WARN    line should be logged", 1 );
        Log.Error    (         "(Indented) This Error   line should be logged", 1 );

        Log.SetDomain( "TLLS_DF", Log.DomainLevel.InfoWarningsAndErrors );
        Log.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     (         "This Info    line should be logged" );
        Log.Warning  (         "This Warning line should be logged" );
        Log.Error    (         "This Error   line should be logged" );
        Log.Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Info     (         "(Indented) This Info    line should be logged", 1 );
        Log.Warning  (         "(Indented) This Warning line should be logged", 1 );
        Log.Error    (         "(Indented) This Error   line should be logged", 1 );


        Log.SetDomain( "TLLS_DF", Log.DomainLevel.WarningsAndErrors );
        Log.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  (         "This Warning line should be logged" );
        Log.Error    (         "This Error   line should be logged" );
        Log.Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Warning  (         "(Indented) This Warning line should be logged", 1 );
        Log.Error    (         "(Indented) This Error   line should be logged", 1 );

        Log.SetDomain( "TLLS_DF", Log.DomainLevel.Errors );
        Log.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Error    (         "This Error   line should be logged" );
        Log.Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Error    (         "(Indented) This Error   line should be logged", 1 );

        Log.SetDomain( "TLLS_DF", Log.DomainLevel.Off );
        Log.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Error    (         "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Error    (         "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

        Log.SetDomain( "TLLS", Log.DomainLevel.All );
        Log.Verbose  ( "TLLS", "This Verbose line should be logged" );
        Log.Info     ( "TLLS", "This Info    line should be logged" );
        Log.Warning  ( "TLLS", "This WARN    line should be logged" );
        Log.Error    ( "TLLS", "This Error   line should be logged" );
        Log.Verbose  ( "TLLS", "(Indented) This Verbose line should be logged", 1 );
        Log.Info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        Log.Warning  ( "TLLS", "(Indented) This WARN    line should be logged", 1 );
        Log.Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Log.SetDomain( "TLLS", Log.DomainLevel.InfoWarningsAndErrors );
        Log.Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     ( "TLLS", "This Info    line should be logged" );
        Log.Warning  ( "TLLS", "This Warning line should be logged" );
        Log.Error    ( "TLLS", "This Error   line should be logged" );
        Log.Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        Log.Warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        Log.Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );


        Log.SetDomain( "TLLS", Log.DomainLevel.WarningsAndErrors );
        Log.Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  ( "TLLS", "This Warning line should be logged" );
        Log.Error    ( "TLLS", "This Error   line should be logged" );
        Log.Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        Log.Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Log.SetDomain( "TLLS", Log.DomainLevel.Errors );
        Log.Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Error    ( "TLLS", "This Error   line should be logged" );
        Log.Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        Log.Error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        Log.SetDomain( "TLLS", Log.DomainLevel.Off );
        Log.Verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Error    ( "TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Error    ( "TLLS", "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!" );



        #if ALOX_DBG_LOG
            UT_EQ ( (uint) 40, cl.CntLogs - logLinesBefore );
        #else
            UT_EQ ( (uint)  0, cl.CntLogs - logLinesBefore );
        #endif
    }

    /** ********************************************************************************************
     * Log_TestDefaultDomain
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_TestDefaultDomain()
    {
        uint cntLL;
        clearCreateAndAddLoggers( true );
        Log.Error("No domain and nothing set");

        Log.SetDomain( "DFLT", Log.Scope.Method );

        String testOK=  "OK";
        String testERR= "Error";

        #if ALOX_DBG_LOG
            uint oneLine= 1;
        #else
            uint oneLine= 0;
        #endif

        // Test log level setting
        cntLL= cl.CntLogs;
        Log.SetDomain( "DFLT",Log.DomainLevel.InfoWarningsAndErrors );
        cntLL= cl.CntLogs;    Log.Verbose    ( testERR );    UT_EQ ( (uint) 0, cl.CntLogs - cntLL );
        cntLL= cl.CntLogs;    Log.Info       ( testOK  );    UT_EQ ( oneLine,  cl.CntLogs - cntLL );

        Log.SetDomain( "~",   Log.DomainLevel.WarningsAndErrors );
        cntLL= cl.CntLogs;    Log.Info       ( testERR );    UT_EQ ( (uint) 0, cl.CntLogs - cntLL );
        cntLL= cl.CntLogs;    Log.Warning    ( testOK  );    UT_EQ ( oneLine,  cl.CntLogs - cntLL );

        Log.SetDomain( "~/",Log.DomainLevel.Errors );
        cntLL= cl.CntLogs;    Log.Warning    ( testERR );    UT_EQ ( (uint) 0, cl.CntLogs - cntLL );
        cntLL= cl.CntLogs;    Log.Error      ( testOK  );    UT_EQ ( oneLine,  cl.CntLogs - cntLL );


        // test sub domains
        Log.SetDomain( "DFLT/WARN", Log.Scope.None );
        Log.SetDomain(    "~/ERR",  Log.Scope.None );
        Log.LogConfig( "TEST",      Log.Level.Info, "Dumping Log Configuration:", cl.Name );

        Log.SetDomain( "DFLT",      Log.DomainLevel.InfoWarningsAndErrors );
        Log.SetDomain( "DFLT/WARN", Log.DomainLevel.WarningsAndErrors     );
        Log.SetDomain(    "~/ERR",  Log.DomainLevel.Errors                );

        Log.LogConfig( "TEST",      Log.Level.Info, "Dumping Log Configuration:", cl.Name );

        // log with leading "/" on domain
        cntLL= ml.CntLogs;    Log.Verbose( "/DFLT",        testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "/DFLT/ERR",    testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "/DFLT/WARN",   testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Info   ( "/DFLT",        testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "/DFLT/ERR",    testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "/DFLT/WARN",   testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Warning( "/DFLT",        testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "/DFLT/WARN",   testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "/DFLT/ERR",    testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Error  ( "/DFLT",        testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "/DFLT/WARN",   testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "/DFLT/ERR",    testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );

        // log without leading "/" on domain, still absolute
        cntLL= ml.CntLogs;    Log.Verbose( "DFLT",         testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "DFLT/ERR",     testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "DFLT/WARN",    testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Info   ( "DFLT",         testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "DFLT/ERR",     testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "DFLT/WARN",    testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Warning( "DFLT",         testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "DFLT/WARN",    testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "DFLT/ERR",     testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Error  ( "DFLT",         testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "DFLT/WARN",    testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "DFLT/ERR",     testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );


        // relative addressing with "~"domain
        cntLL= ml.CntLogs;    Log.Verbose(                 testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "~",            testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "~ERR",         testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Verbose( "~WARN",        testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Info   (                 testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "~",            testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "~ERR",         testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Info   ( "~WARN",        testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Warning(                 testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "~",            testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "~WARN",        testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Warning( "~ERR",         testERR );    UT_EQ ( (uint) 0, ml.CntLogs - cntLL );

        cntLL= ml.CntLogs;    Log.Error  (                 testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "~",            testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "~WARN",        testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );
        cntLL= ml.CntLogs;    Log.Error  ( "~ERR",         testOK  );    UT_EQ ( oneLine,  ml.CntLogs - cntLL );

        #endif  // ALOX_DBG_LOG || ALOX_REL_LOG

    }

    /** ********************************************************************************************
     * Log_TestDefaultDomain
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_TestAssertAndConditional()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            clearCreateAndAddLoggers( true );

            Log.SetDomain( "ASSERT", Log.Scope.Method );

            String testOK=  "OK";
            String testERR= "Error";

            // Test log level setting
            uint cntLL= cl.CntLogs;
            Log.SetDomain( "ASSERT", Log.DomainLevel.InfoWarningsAndErrors);

            #if ALOX_DBG_LOG
                uint oneLine= 1;
            #else
                uint oneLine= 0;
            #endif

            cntLL= cl.CntLogs;    Log.Assert( true,  testERR );                          UT_EQ ( (uint) 0, cl.CntLogs - cntLL );
            cntLL= cl.CntLogs;    Log.Assert( false, testOK  );                          UT_EQ ( oneLine,  cl.CntLogs - cntLL );
            cntLL= cl.CntLogs;    Log.Line  ( false, null, Log.Level.Info, testERR );    UT_EQ ( (uint) 0, cl.CntLogs - cntLL );
            cntLL= cl.CntLogs;    Log.Line  ( true,  null, Log.Level.Info, testOK  );    UT_EQ ( oneLine , cl.CntLogs - cntLL );
        #endif
    }


    /** ********************************************************************************************
     * Log_TestLineFormat
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_TestLineFormat()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        clearCreateAndAddLoggers();

        Log.SetDomain( "FMT", Log.Scope.Method );
        Log.SetDomain( "FMT", Log.DomainLevel.All);

        Log.Info( "This is the default ConsoleLogger log line" );

        AString  lf;
        lf= new AString( "%CF(%CL):%CM()%A3[%D][%TD][%TE +%TI] [%t] %L [%O] <%#>: ");   cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%CF(%CL):%A3[%D][%TD][%TE +%TI] [%t] %L [%O] <%#>: ");        cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%CF(%CL):%A3[%TD][%TE +%TI] [%t] %L [%O] <%#>: ");             cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%CF(%CL):%A3[%TE +%TI] [%t] %L [%O] <%#>: ");                  cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%CF(%CL):%A3[+%TI] [%t] %L [%O] <%#>: ");                      cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%CF(%CL):%A3[%t] %L [%O] <%#>: ");                             cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%CF(%CL):%A3%L [%O] <%#>: ");                                  cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%CF(%CL):%A3[%O] <%#>: ");                                     cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%CF(%CL):%A3[%O]: ");                                          cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%CF:%A3[%O]: ");                                               cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "[%O]: ");                                                      cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "");                                                            cl.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );

        cl.MetaInfo.Format.Clear()._("%D@");
        String df;
        df= "yyyy-MM-dd";           cl.MetaInfo.DateFormat= df;    Log.Info( "Date test. Format: \"" + df + "\"" );
        df= "yyy'Bla'MM'fasel'dd";  cl.MetaInfo.DateFormat= df;    Log.Info( "Date test. Format: \"" + df + "\"" );


        #endif
    }

    /** ********************************************************************************************
     * Log_TestMarker
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_TestMarker()
    {
        clearCreateAndAddLoggers();

        Log.SetDomain( "MARKER", Log.Scope.Method );
        Log.SetDomain( "MARKER", Log.DomainLevel.All );


        Log.Info( "*** Testing markers ***" );
        const String markerDisposedGlobal=    "overwritten global level marker (should NOT appear in the test log)";
        const String markerGlobal=            "global marker (this is right to appear in the test log!)";
        const String markerDisposedSrc=       "overwritten source level marker (should NOT appear in the test log)";
        const String markerSrc=               "source level marker (this is right to appear in the test log!)";
        const String markerDisposedMethod=    "overwritten method marker (should NOT appear in the test log)";
        const String markerMethod=            "method marker (this is right to appear in the test log!)";


        /*#/AWX_LOG// Log.SetMarker( markerDisposedSrc,    true );        //#/AWX_LOG*/
        Log.SetMarker( markerDisposedGlobal,    Log.Scope.None );
        Log.SetMarker( markerGlobal,            Log.Scope.None );
        Log.SetMarker( markerDisposedSrc,       Log.Scope.SourceFile );
        Log.SetMarker( markerSrc,               Log.Scope.SourceFile );
        Log.SetMarker( markerDisposedMethod,    Log.Scope.Method );
        Log.SetMarker( markerMethod,            Log.Scope.Method );

        Object[] markerpointer= new Object[1];

        Log.GetMarker( markerpointer, Log.Scope.None );          Log.Info( "The current global level marker is: " + markerpointer[0] );
            #if ALOX_DBG_LOG
                UT_TRUE( (String) markerpointer[0] == markerGlobal     );
            #else
                UT_TRUE( markerpointer[0] == null     );
            #endif
        Log.GetMarker( markerpointer, Log.Scope.SourceFile );    Log.Info( "The current source level marker is: " + markerpointer[0] );
            #if ALOX_DBG_LOG
                UT_TRUE( (String) markerpointer[0] == markerSrc     );
            #else
                UT_TRUE( markerpointer[0] == null     );
            #endif
        Log.GetMarker( markerpointer, Log.Scope.Method );        Log.Info( "The current method level marker is: " + markerpointer[0] );
            #if ALOX_DBG_LOG
                UT_TRUE( (String) markerpointer[0] == markerMethod     );
            #else
                UT_TRUE( markerpointer[0] == null     );
            #endif
    }


    /** ********************************************************************************************
     * Log_TestThreads
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_TestThreads()
    {
        clearCreateAndAddLoggers();

        Log.SetDomain( "TEST/THREAD1", Log.Scope.Method );
        Log.SetDomain( "TEST/THREAD1", Log.DomainLevel.All );

        // if this gets commented out, the test might crash. At least the console will
        // become scrambled!
        //Log.LOX.Lock.setUnsafe( true );


        Thread thread = new Thread( new ThreadStart( testDifferentThreadMethod ) ) {Name = "Thread2"};
        thread.Start();

        for ( int i= 0 ; i < 50 ; i++ )
        {
            Log.Info( "This is the main thread ");// + i );
            ALIB.SleepMillis( 4 );
        }
    }

    public void testDifferentThreadMethod()
    {
        Log.SetDomain( "TEST/THREAD2", Log.Scope.Method );
        Log.SetDomain( "TEST/THREAD2", Log.DomainLevel.All );

        for ( int i= 0 ; i < 20 ; i++ )
        {
            Log.Info( "This is a different Thread. Cnt= " + i );
            ALIB.SleepMillis( 3 );
        }
    }


    /** ********************************************************************************************
     * Log_TestException.
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_TestMultiline()
    {
        clearCreateAndAddLoggers();

        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Log.SetDomain( "MLine", Log.Scope.Method );
            Log.SetDomain( "MLine", Log.DomainLevel.All );


            cl.MultiLineMsgMode= 0;
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 0 (single line) --------" );
            Log.LogConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );

            cl.MultiLineMsgMode= 0;
            cl.MultiLineDelimiterRepl= "~|~";
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 0 (single line) with delimiter replacement set to ~|~ --------" );
            Log.LogConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );

            cl.MultiLineMsgMode= 0;
            cl.MultiLineDelimiter= "";
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 0 (single line) with delimiter set to \"\" (stops multi line processing) --------" );
            Log.LogConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );

            cl.MultiLineMsgMode= 1;
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 1 (multi line, all meta info per line) --------" );
            Log.LogConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );

            cl.MultiLineMsgMode= 2;
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 2 (multi line, meta info blanked) --------" );
            Log.LogConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );

            cl.MultiLineMsgMode= 3;
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 3 (multi line, print headline with info, text starts at pos 0) --------" );
            Log.LogConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );

            cl.MultiLineMsgMode= 4;
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 4 (pure multi line, no meta info, no headline, starts at pos 0)) --------" );
            Log.LogConfig( "MLine", Log.Level.Info, "Our Log configuration is:" );
        #endif
    }

    /** ********************************************************************************************
     * Log_TestException.
     **********************************************************************************************/
        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_ALox")]
            #endif
        #endif
        public void Log_DisableLogger()
        {
            clearCreateAndAddLoggers();

            Log.SetDomain( "DISABLE", Log.DomainLevel.All );

            #if ALOX_DBG_LOG || ALOX_REL_LOG
                uint cntLogs= cl.CntLogs;
                Log.Info( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 1, cl.CntLogs );
                Log.SetLogger( cs.aworx.lib.enums.Switch.Off, "NOMATCH" );
                Log.Info( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 2, cl.CntLogs );
                Log.SetLogger( cs.aworx.lib.enums.Switch.Off, "*tTESTlo*" );
                Log.Info( "DISABLE", "This message should NOT appear" );   UT_EQ( cntLogs + 2, cl.CntLogs );
                Log.SetLogger( cs.aworx.lib.enums.Switch.On, null );
                Log.Info( "DISABLE", "This message should appear" );       UT_EQ( cntLogs + 3, cl.CntLogs ); 
            #endif

        }


    } // class
} // namespace
