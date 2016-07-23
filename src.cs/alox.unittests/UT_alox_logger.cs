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
using cs.aworx.lib.enums;
using cs.aworx.lib.config;

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
using System.IO;
#endif

namespace ut_cs_aworx_lox
{
    class MyType
    {}

    class MyObjectConverter : cs.aworx.lox.core.textlogger.ObjectConverter
    {
        public override bool ConvertObject( Object o, AString result )
        {
            if ( o == null )
            {
                result._( "MyObjectConverter: null" );
                return true;
            }

            if ( o.GetType() == typeof(MyType) )
            {
                result._( "my type" );
                return true;
            }

            return false;
        }
    }


    #if ALIB_MONO_DEVELOP
        [TestFixture ()]
    #endif
    #if ALIB_VSTUDIO
        [TestClass]
    #endif
    public class CS_ALox_Logger  : AWorxUnitTesting
    {
    public static void ScopeInfoCacheTest() { Log.Info("Test method of CS_ALox_Logger"); }

    /** ********************************************************************************************
     * Log_ObjectConverter.
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_Consoles")]
        #endif
    #endif
    public void Log_ObjectConverter()
    {
        UT_INIT();

        Log.AddDebugLogger();

        Log.SetDomain( "OBJECT_CONV",       Scope.Method );
        MemoryLogger ml= new MemoryLogger();
        ml.MetaInfo.Format._();
        Log.SetVerbosity( ml, Verbosity.Verbose );

        StringConverter mainConverter= (StringConverter) ml.ObjectConverters[0];
        // test without my converter
        MyType mytype= new MyType();
        Log.Info( "Test" ); UT_TRUE( ml.MemoryLog.IndexOf( "Test" ) >= 0 );                        ml.MemoryLog._();
        Log.Info( null   ); UT_TRUE( ml.MemoryLog.IndexOf( mainConverter.FmtNullObject ) >= 0 );   ml.MemoryLog._();
        Log.Info( mytype ); UT_EQ  ( mytype.ToString(), ml.MemoryLog );                            ml.MemoryLog._();
        Log.Info( null   ); UT_EQ  ( mainConverter.FmtNullObject,  ml.MemoryLog );                 ml.MemoryLog._();

        // test without my converter
                     ml.ObjectConverters.Add( new MyObjectConverter() );
        Log.DebugLogger.ObjectConverters.Add( new MyObjectConverter() );
        Log.Info( "Test" ); UT_TRUE( ml.MemoryLog.IndexOf( "Test" ) >= 0 );                        ml.MemoryLog._();
        Log.Info( null   ); UT_EQ  ( "MyObjectConverter: null" , ml.MemoryLog );                   ml.MemoryLog._();
        Log.Info( mytype   ); UT_EQ( "my type"                 , ml.MemoryLog );                   ml.MemoryLog._();

        // cleanup
        Log.RemoveLogger( ml );
        Log.RemoveDebugLogger();
    }
    #endif
    /** ********************************************************************************************
     * Log_TestException.
     **********************************************************************************************/
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox_Consoles")]
        #endif
    #endif
    public void Log_ColorsAndStyles()
    {
        UT_INIT();

        Log.AddDebugLogger();
        Log.SetDomain( "COLORS", Scope.Method );
        #if ALOX_DBG_LOG
            MemoryLogger ml= new MemoryLogger();
            Log.SetVerbosity( ml, Verbosity.Verbose, "/" );
        #endif
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "/" );

        Log.Info   ( "Playing with colors. Depending on the test environment, the colors might "
                    +"be visible or not" );
        Log.Info   ( "In the memory logger, all color/style codes have to disappear (by default)" );
        Log.Verbose( "A verbose message" );
        Log.Info   ( "An info message" );
        Log.Warning( "A warning message" );
        Log.Error  ( "An error message" );

        #if ALOX_DBG_LOG
            int mlPos= ml.MemoryLog.IndexOf("/COLORS" );
            UT_TRUE( mlPos > 0 );
            mlPos+= 8;
        #endif

        Log.Info( "FG Colors:  "
                                    + ">>>" + ESC.RED     + "RED"        + ESC.FG_RESET + "<<<"
                                    + ">>>" + ESC.GREEN   + "GREEN"      + ESC.FG_RESET + "<<<"
                                    + ">>>" + ESC.BLUE    + "BLUE"       + ESC.FG_RESET + "<<<"
                                    + ">>>" + ESC.CYAN    + "CYAN"       + ESC.FG_RESET + "<<<"
                                    + ">>>" + ESC.MAGENTA + "MAGENTA"    + ESC.FG_RESET + "<<<"
                                    + ">>>" + ESC.YELLOW  + "YELLOW"     + ESC.FG_RESET + "<<<"
                                    + ">>>" + ESC.GRAY    + "GRAY"       + ESC.FG_RESET + "<<<"
                                    + ">>>" + ESC.WHITE   + "WHITE"      + ESC.FG_RESET + "<<<"
                                    + ">>>" + ESC.BLACK   + "BLACK"      + ESC.FG_RESET + "<<<"
                                    );

        #if ALOX_DBG_LOG
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif
        Log.Info( "BG Colors:  "
                                    + ">>>" + ESC.BG_RED     + "RED"        + ESC.BG_RESET + "<<<"
                                    + ">>>" + ESC.BG_GREEN   + "GREEN"      + ESC.BG_RESET + "<<<"
                                    + ">>>" + ESC.BG_BLUE    + "BLUE"       + ESC.BG_RESET + "<<<"
                                    + ">>>" + ESC.BG_CYAN    + "CYAN"       + ESC.BG_RESET + "<<<"
                                    + ">>>" + ESC.BG_MAGENTA + "MAGENTA"    + ESC.BG_RESET + "<<<"
                                    + ">>>" + ESC.BG_YELLOW  + "YELLOW"     + ESC.BG_RESET + "<<<"
                                    + ">>>" + ESC.BG_GRAY    + "GRAY"       + ESC.BG_RESET + "<<<"
                                    + ">>>" + ESC.BG_WHITE   + "WHITE"      + ESC.BG_RESET + "<<<"
                                    + ">>>" + ESC.BG_BLACK   + "BLACK"      + ESC.BG_RESET + "<<<"
                                    );

        #if ALOX_DBG_LOG
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif
        Log.Info( "FG/BG same: "
                                + ">>>" + ESC.RED     + ESC.BG_RED     + "RED"        + ESC.RESET + "<<<"
                                + ">>>" + ESC.GREEN   + ESC.BG_GREEN   + "GREEN"      + ESC.RESET + "<<<"
                                + ">>>" + ESC.BLUE    + ESC.BG_BLUE    + "BLUE"       + ESC.RESET + "<<<"
                                + ">>>" + ESC.CYAN    + ESC.BG_CYAN    + "CYAN"       + ESC.RESET + "<<<"
                                + ">>>" + ESC.MAGENTA + ESC.BG_MAGENTA + "MAGENTA"    + ESC.RESET + "<<<"
                                + ">>>" + ESC.YELLOW  + ESC.BG_YELLOW  + "YELLOW"     + ESC.RESET + "<<<"
                                + ">>>" + ESC.GRAY    + ESC.BG_GRAY    + "GRAY"       + ESC.RESET + "<<<"
                                + ">>>" + ESC.WHITE   + ESC.BG_WHITE   + "WHITE"      + ESC.RESET + "<<<"
                                + ">>>" + ESC.BLACK   + ESC.BG_BLACK   + "BLACK"      + ESC.RESET + "<<<"
                                );

        #if ALOX_DBG_LOG
            AnsiConsoleLogger   acl= (AnsiConsoleLogger)    Log.GetLogger( "ANSI_CONSOLE" );
            ColorConsoleLogger  ccl= (ColorConsoleLogger)   Log.GetLogger( "COLORCONSOLE" );
            if ( acl!=null )        acl.IsBackgroundLight= !acl.IsBackgroundLight;
            if ( ccl!=null )        ccl.IsBackgroundLight= !ccl.IsBackgroundLight;
        #endif


        Log.Info( "Same rev.:  "
                                + ">>>" + ESC.RED     + ESC.BG_RED     + "RED"        + ESC.RESET + "<<<"
                                + ">>>" + ESC.GREEN   + ESC.BG_GREEN   + "GREEN"      + ESC.RESET + "<<<"
                                + ">>>" + ESC.BLUE    + ESC.BG_BLUE    + "BLUE"       + ESC.RESET + "<<<"
                                + ">>>" + ESC.CYAN    + ESC.BG_CYAN    + "CYAN"       + ESC.RESET + "<<<"
                                + ">>>" + ESC.MAGENTA + ESC.BG_MAGENTA + "MAGENTA"    + ESC.RESET + "<<<"
                                + ">>>" + ESC.YELLOW  + ESC.BG_YELLOW  + "YELLOW"     + ESC.RESET + "<<<"
                                + ">>>" + ESC.GRAY    + ESC.BG_GRAY    + "GRAY"       + ESC.RESET + "<<<"
                                + ">>>" + ESC.WHITE   + ESC.BG_WHITE   + "WHITE"      + ESC.RESET + "<<<"
                                + ">>>" + ESC.BLACK   + ESC.BG_BLACK   + "BLACK"      + ESC.RESET + "<<<"
                                );
        #if ALOX_DBG_LOG
            if ( acl!=null )        acl.IsBackgroundLight= !acl.IsBackgroundLight;
            if ( ccl!=null )        ccl.IsBackgroundLight= !ccl.IsBackgroundLight;
        #endif

        #if ALOX_DBG_LOG
            Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif
        Log.Info( "Reset FG/BG: "
                                    + ESC.BG_RED     + "BG RED"
                                    + ESC.GREEN      + "FG REEN"
                                    + ESC.FG_RESET   + "FG Reset"
                                    + ESC.BG_RESET   + "BG Reset"
                                    );
        #if ALOX_DBG_LOG
            Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif

        Log.Info( "Reset FG/BG: "
                                    + ESC.BG_RED     + "BG RED"
                                    + ESC.GREEN      + "FG REEN"
                                    + ESC.BG_RESET   + "BG Reset"
                                    + ESC.FG_RESET   + "FG Reset"
                                    );
        #if ALOX_DBG_LOG
            Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif

        Log.Info( "Reset FG/BG: "
                                    + ESC.BG_RED     + "BG RED"
                                    + ESC.GREEN      + "FG REEN"
                                    + ESC.RESET      + "All Reset"
                                    );
        #if ALOX_DBG_LOG
            Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif

        Log.Info( "Styles: "
                                    + ">>>" + ESC.BOLD     + "Bold"          + ESC.STYLE_RESET + "<<<"
                                    + ">>>" + ESC.ITALICS  + "Italics"       + ESC.STYLE_RESET  + "<<<"
                                    + ">>>" + ESC.BOLD
                                    + ">>>" + ESC.ITALICS  + "Bold/Italics"   + ESC.STYLE_RESET  + "+<  Styles do not work in Windows consoles"
                                    );

        #if ALOX_DBG_LOG
            Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif

        Log.Info( "Reset Style/FG/BG: "
                                    + ESC.BOLD        + "Bold"
                                    + ESC.BG_RED      + "BG RED"
                                    + ESC.GREEN       + "FG REEN"
                                    + ESC.BG_RESET    + "BG Reset"
                                    + ESC.FG_RESET    + "FG Reset"
                                    + ESC.STYLE_RESET + "Style Reset"
                                    );
        #if ALOX_DBG_LOG
            Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif

        Log.Info( "Reset Style/FG/BG: "
                                    + ESC.BOLD        + "Bold"
                                    + ESC.BG_RED      + "BG RED"
                                    + ESC.GREEN       + "FG REEN"
                                    + ESC.RESET       + "Reset All"
                                    );

        #if ALOX_DBG_LOG
            Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif

            Log.Info( "Reset Style/FG/BG: "
                                    + ESC.BOLD        + "Bold"
                                    + ESC.BG_RED      + "BG RED"
                                    + ESC.GREEN       + "FG REEN"
                                    + ESC.STYLE_RESET + "Style Reset"
                                    + ESC.BG_RESET    + "BG Reset"
                                    + ESC.FG_RESET    + "FG Reset"
                                    + "   +< This does not work on ANSI terminals: Styl reset, resets ALL here"
                                    );

        #if ALOX_DBG_LOG
            Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif

        Log.Info( "An URL: "
                                    + ESC.URL_START   + "www.darwin.heaven"
                                    + ESC.URL_END     + ", your resource for happyness!"
                                    );

        #if ALOX_DBG_LOG
            Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
            UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
        #endif
    }

    /** ********************************************************************************************
    * Log_TextLogger_FormatConfig
    **********************************************************************************************/
    void testFormatConfig( String testFormat,
                           String expFmt,
                           String expFmtError    = null,
                           String expFmtWarning  = null,
                           String expFmtInfo     = null,
                           String expFmtVerbose  = null
                         )
    {
        Variable var= new Variable();
        var.Define(ALox.ConfigCategoryName, "TESTML_FORMAT", ',').Store( testFormat  );
    
        Lox lox= new Lox("TEST");   
        MemoryLogger ml= new MemoryLogger("TESTML");
        lox.SetVerbosity( ml, Verbosity.Info );
        lox.RemoveLogger( ml );
        ALox.Register( lox, ContainerOp.Remove );
    
                                     UT_EQ( expFmt       , ml.MetaInfo.Format );
        if( expFmtError  != null ) { UT_EQ( expFmtError  , ml.MetaInfo.VerbosityError   ); }
        if( expFmtWarning!= null ) { UT_EQ( expFmtWarning, ml.MetaInfo.VerbosityWarning ); }
        if( expFmtInfo   != null ) { UT_EQ( expFmtInfo   , ml.MetaInfo.VerbosityInfo    ); }
        if( expFmtVerbose!= null ) { UT_EQ( expFmtVerbose, ml.MetaInfo.VerbosityVerbose ); }
    }


    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_TextLogger_FormatConfig()
    {
        UT_INIT();

        testFormatConfig( "Test"                                , "Test"                     );
        testFormatConfig( "\"Test"                              , "Test"                     );
        testFormatConfig( "\"Test\""                            , "Test"                     );
        testFormatConfig( "  \" Test  \"  s"                    , " Test  s"                 );

        testFormatConfig( " Test , a ,b, c,d  "                 , "Test", "a","b","c","d"    );
        testFormatConfig( "\" Test, a\" ,b, \"c\",d  "          , " Test, a","b","c", "d"    );
        testFormatConfig( "\" Test, a\" ,b, \"c,d\"  "          , " Test, a","b","c,d"       );
    }

    /** ********************************************************************************************
     * Log.TestVerbositySetting
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
    public void Log_TextLoggerTimeDiff()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        UT_INIT();

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
     * Log_LogLevelSetting
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_LogLevelSetting()
    {

        #if ALOX_DBG_LOG || ALOX_REL_LOG
        UT_INIT();

        Log.AddDebugLogger();

        Log.SetDomain( "TLLS_DF", Scope.Method );

        // Test Verbosity setting
        int logLinesBefore= Log.DebugLogger.CntLogs;

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "" );
        Log.Verbose  (         "This Verbose line should be logged" );
        Log.Info     (         "This Info    line should be logged" );
        Log.Warning  (         "This WARN    line should be logged" );
        Log.Error    (         "This Error   line should be logged" );

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Info, "" );
        Log.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     (         "This Info    line should be logged" );
        Log.Warning  (         "This Warning line should be logged" );
        Log.Error    (         "This Error   line should be logged" );


        Log.SetVerbosity( Log.DebugLogger, Verbosity.Warning, "" );
        Log.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  (         "This Warning line should be logged" );
        Log.Error    (         "This Error   line should be logged" );

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Error, "" );
        Log.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Error    (         "This Error   line should be logged" );

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Off, "" );
        Log.Verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Error    (         "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "/TLLS" );
        Log.Verbose  ( "/TLLS", "This Verbose line should be logged" );
        Log.Info     ( "/TLLS", "This Info    line should be logged" );
        Log.Warning  ( "/TLLS", "This WARN    line should be logged" );
        Log.Error    ( "/TLLS", "This Error   line should be logged" );

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Info, "/TLLS" );
        Log.Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     ( "/TLLS", "This Info    line should be logged" );
        Log.Warning  ( "/TLLS", "This Warning line should be logged" );
        Log.Error    ( "/TLLS", "This Error   line should be logged" );

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Warning, "/TLLS" );
        Log.Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  ( "/TLLS", "This Warning line should be logged" );
        Log.Error    ( "/TLLS", "This Error   line should be logged" );

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Error, "/TLLS" );
        Log.Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  ( "/TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Error    ( "/TLLS", "This Error   line should be logged" );

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Off, "/TLLS" );
        Log.Verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Warning  ( "/TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.Error    ( "/TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

        UT_EQ ( (uint) 20, Log.DebugLogger.CntLogs - logLinesBefore );
    }
    #endif


    /** ********************************************************************************************
     * Log_LineFormat
     **********************************************************************************************/
    #if ALOX_DBG_LOG
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
        [TestMethod]
        #if !WINDOWS_PHONE
            [TestCategory("CS_ALox")]
        #endif
    #endif
    public void Log_LineFormat()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        UT_INIT();

        Log.AddDebugLogger();

        MemoryLogger testML= new MemoryLogger();

        Log.SetDomain( "/FMT", Scope.Method );
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "/FMT");
        Log.SetVerbosity( testML,          Verbosity.Verbose, "/FMT");

        Log.Info( "This is the default ConsoleLogger log line" );



        AString  lf;
        lf= new AString( "%SF(%SL):%SM()%A3[%D][%TD][%TC +%TL][%tN]%V[%D]<%#>: ");    Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%SF(%SL):%A3[%D][%TD][%TC +%TL][%tN]%V[%D]<%#>: ");         Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%SF(%SL):%A3[%TD][%TC +%TL][%tN]%V[%D]<%#>: ");             Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%SF(%SL):%A3[%TC +%TL][%tN]%V[%D]<%#>: ");                  Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%SF(%SL):%A3[+%TL][%tN]%V[%D]<%#>: ");                      Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%SF(%SL):%A3[%tN]%V[%D]<%#>: ");                            Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%SF(%SL):%A3 %V[%D]<%#>: ");                                Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%SF(%SL):%A3[%D]<%#>: ");                                   Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%SF(%SL):%A3[%D]: ");                                       Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "%SF:%A3[%D]: ");                                            Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "[%D]: ");                                                   Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "");                                                         Log.DebugLogger.MetaInfo.Format= lf;    Log.Info( "LineFormat set to= \"" + lf + "\"" );


        Log.DebugLogger.MetaInfo.Format._()._( "%TD@" );
        testML.MetaInfo.Format._()._( "%TD@" );
        String df;
        df= ">yy-MM-dd<";    Log.DebugLogger.MetaInfo.DateFormat= df;                                                Log.Info( "Date test. Format: \""+ df + '\"' );
        testML.MemoryLog.Clear();
        df= ">yyyy/dd/MM<";  Log.DebugLogger.MetaInfo.DateFormat= df;  testML.MetaInfo.DateFormat= df;             Log.Info( "FMT", "Date test. Format: \""+ df + '\"' );
        UT_TRUE( testML.MemoryLog.SearchAndReplace( "/", "@") == 4 );

        Log.DebugLogger.MetaInfo.Format._()._( "%TT@" );
        testML.MetaInfo.Format._()._( "%TT@" );
        df= ">HH:mm:ss<";    Log.DebugLogger.MetaInfo.TimeOfDayFormat= df;                                           Log.Info( "FMT", "Time of day test Format: \""+ df + '\"' );
        testML.MemoryLog.Clear();
        df= ">HH-mm-ss<";    Log.DebugLogger.MetaInfo.TimeOfDayFormat= df;  testML.MetaInfo.TimeOfDayFormat= df;   Log.Info( "FMT", "Time of day test. Format: \"" + df + '\"' );
        UT_TRUE( testML.MemoryLog.SearchAndReplace( "-", "@") == 4 );


        Log.DebugLogger.MetaInfo.Format._()._( "%P" );
                 testML.MetaInfo.Format._()._( "%P" );
        testML.MemoryLog.Clear(); testML.AutoSizes.Reset(); Log.Info("");  UT_TRUE(    testML.MemoryLog.IndexOf( ".Net45-NUnit"    ) >= 0
                                                                                    || testML.MemoryLog.IndexOf( "UnitTestAdapter" ) >= 0   );

        Log.DebugLogger.MetaInfo.Format._()._( "%LX" );
                 testML.MetaInfo.Format._()._( "%LX" );
        testML.MemoryLog.Clear(); testML.AutoSizes.Reset(); Log.Info("");  UT_EQ( "LOG"     ,testML.MemoryLog );

        Log.DebugLogger.MetaInfo.Format._()._( "%LG" );
                 testML.MetaInfo.Format._()._( "%LG" );
        testML.MemoryLog.Clear(); testML.AutoSizes.Reset(); Log.Info("");  UT_EQ( "MEMORY"  , testML.MemoryLog );

        #endif
    }
    #endif


    /** ********************************************************************************************
     * Log_Multiline.
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
    public void Log_Multiline()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            UT_INIT();
            Log.AddDebugLogger();
            MemoryLogger ml= new MemoryLogger();


            Log.SetDomain( "/MLine", Scope.Method );
            Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "/MLine" );
            Log.SetVerbosity( ml, Verbosity.Verbose, "/MLine" );


            Log.DebugLogger.MultiLineMsgMode= 0;
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 0 (single line) --------" );
            Log.State( "MLine", Verbosity.Info, "Our Log configuration is:" );

            Log.DebugLogger.MultiLineMsgMode= 0;
            Log.DebugLogger.MultiLineDelimiterRepl= "~|~";
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 0 (single line) with delimiter replacement set to ~|~ --------" );
            Log.State( "MLine", Verbosity.Info, "Our Log configuration is:" );

            Log.DebugLogger.MultiLineMsgMode= 0;
            Log.DebugLogger.MultiLineDelimiter= "";
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 0 (single line) with delimiter set to \"\" (stops multi line processing) --------" );
            Log.State( "MLine", Verbosity.Info, "Our Log configuration is:" );

            Log.DebugLogger.MultiLineMsgMode= 1;
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 1 (multi line, all meta info per line) --------" );
            Log.State( "MLine", Verbosity.Info, "Our Log configuration is:" );

            Log.DebugLogger.MultiLineMsgMode= 2;
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 2 (multi line, meta info blanked) --------" );
            Log.State( "MLine", Verbosity.Info, "Our Log configuration is:" );

            Log.DebugLogger.MultiLineMsgMode= 3;
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 3 (multi line, print headline with info, text starts at pos 0) --------" );
            Log.State( "MLine", Verbosity.Info, "Our Log configuration is:" );

            Log.DebugLogger.MultiLineMsgMode= 4;
            Log.Info( "" );
            Log.Info( "-------- ML Mode = 4 (pure multi line, no meta info, no headline, starts at pos 0)) --------" );
            Log.State( "MLine", Verbosity.Info, "Our Log configuration is:" );
        #endif
    }


        #endif  // ALOX_DBG_LOG || ALOX_REL_LOG


    } // class
} // namespace
