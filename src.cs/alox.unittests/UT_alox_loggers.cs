// #################################################################################################
//  cs.aworx.lox.unittests - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.Threading;
using System.Xml.Linq;
using ut_cs_aworx;

#if ALIB_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if ALIB_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using cs.aworx.lib;
using cs.aworx.lox;
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
    public class CS_ALox_Consoles   : UnitTest
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
            clearCreateAndAddLoggers( true, true );

            Log.SetDomain( "COLORS", Log.DomainLevel.All);
            Log.SetDomain( "COLORS", Log.Scope.Method );

            Log.Info   ( "Playing with colors. Depending on the test environment, the colors might "
                        +"be visible or not" );
            Log.Info   ( "In the memory logger, all color/style codes have to disappear (by default)" );
            Log.Verbose( "A verbose message" );
            Log.Info   ( "An info message" );
            Log.Warning( "A warning message" );
            Log.Error  ( "An error message" );

            #if ALOX_DBG_LOG || ALOX_REL_LOG
                int mlPos= ml.MemoryLog.IndexOf("COLORS]:" );
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

            #if ALOX_DBG_LOG || ALOX_REL_LOG
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

            #if ALOX_DBG_LOG || ALOX_REL_LOG
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

            #if ALOX_DBG_LOG || ALOX_REL_LOG
                Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
                UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
            #endif
            Log.Info( "Reset FG/BG: "
                                        + ESC.BG_RED     + "BG RED"
                                        + ESC.GREEN      + "FG REEN"
                                        + ESC.FG_RESET   + "FG Reset"
                                        + ESC.BG_RESET   + "BG Reset"
                                        );
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
                UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
            #endif

            Log.Info( "Reset FG/BG: "
                                        + ESC.BG_RED     + "BG RED"
                                        + ESC.GREEN      + "FG REEN"
                                        + ESC.BG_RESET   + "BG Reset"
                                        + ESC.FG_RESET   + "FG Reset"
                                        );
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
                UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
            #endif

            Log.Info( "Reset FG/BG: "
                                        + ESC.BG_RED     + "BG RED"
                                        + ESC.GREEN      + "FG REEN"
                                        + ESC.RESET      + "All Reset"
                                        );
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
                UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
            #endif

            Log.Info( "Styles: "
                                        + ">>>" + ESC.BOLD     + "Bold"          + ESC.STYLE_RESET + "<<<"
                                        + ">>>" + ESC.ITALICS  + "Italics"       + ESC.STYLE_RESET  + "<<<"
                                        + ">>>" + ESC.BOLD
                                        + ">>>" + ESC.ITALICS  + "Bold/Italics"   + ESC.STYLE_RESET  + "+<  Styles do not work in Windows consoles"
                                        );

            #if ALOX_DBG_LOG || ALOX_REL_LOG
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
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
                UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
            #endif

            Log.Info( "Reset Style/FG/BG: "
                                        + ESC.BOLD        + "Bold"
                                        + ESC.BG_RED      + "BG RED"
                                        + ESC.GREEN       + "FG REEN"
                                        + ESC.RESET       + "Reset All"
                                        );

            #if ALOX_DBG_LOG || ALOX_REL_LOG
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

            #if ALOX_DBG_LOG || ALOX_REL_LOG
                Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
                UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
            #endif

            Log.Info( "An URL: "
                                        + ESC.URL_START   + "www.darwin.heaven"
                                        + ESC.URL_END     + ", your resource for happyness!"
                                        );

            #if ALOX_DBG_LOG || ALOX_REL_LOG
                Log.Verbose( ml.MemoryLog.ToString( mlPos ) );
                UT_TRUE( ml.MemoryLog.IndexOf("\x1B") < 0 ); ml.MemoryLog.Clear();
            #endif
        }

    } // class
} // namespace
