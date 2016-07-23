// #################################################################################################
//  ALox Samples
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using cs.aworx.lib;
using cs.aworx.lib.time;
using cs.aworx.lox;
using cs.aworx.lox.loggers;
using cs.aworx.lox.tools;
using cs.aworx;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib.config;

namespace ALox_CS_Test_Perf  {

class AloxSamples
{
    // #############################################################################################
    // static entrance (Main)
    // #############################################################################################
//! [DOXYGEN_CREATE_INIFILE]
    static void Main( string[] args )
    {
        // first attach INI file to config system...
        IniFile iniFile= new IniFile();
        ALIB.Config.InsertPlugin( iniFile, Configuration.PrioIniFile );

        // .. then initialize ALox Logging Library
        ALox.Init( args );

        //...
//! [DOXYGEN_CREATE_INIFILE]

        if ( iniFile.FileComments.IsEmpty() )
        {
            iniFile.FileComments._(
            "##################################################################################################\n" +
            "# ALox Samples INI file (created when running ALox Samples)\n"                                        +
            "#\n"                                                                                                  +
            "# (c) 2013-2016 A-Worx GmbH, Germany\n"                                                               +
            "# Published under MIT License (Open Source License, see LICENSE.txt)\n"                               +
            "##################################################################################################\n"
            );
        }

        // Suppress setting "writeback" as default verbosities. We need to do this as this main()
        // method invokes a list of independent samples. Those would now read from the INI file wrong
        // values written in other sample methods and thus the samples would not work any more
        // (because INI file settings overrules settings in the code)
        Variable var= new Variable();
        var.Define( "ALOX", "LOG_DEBUG_LOGGER_VERBOSITY"  ).Store( "" );
        var.Define( "ALOX", "RELEASELOX_CONSOLE_VERBOSITY").Store( "" );
        var.Define( "ALOX", "LOG_MEMORY_VERBOSITY"        ).Store( "" );
        var.Define( "ALOX", "RELEASELOX_MEMORY_VERBOSITY" ).Store( "" );
        var.Define( "ALOX", "LOG_TEXTFILE_VERBOSITY"      ).Store( "" );

        // do some release logging tests.
        Console.WriteLine( "PRINT: Debug logging:" );
            AloxSamples.DebugLogging();
        ALoxSampleReset();

        // do some release logging tests.
        Console.WriteLine( "PRINT: Release logging:" );
            AloxSamples.ReleaseLogging();
        ALoxSampleReset();

        // do some performance tests.
        Console.WriteLine( "PRINT: Performance test (debug logging):" );
           AloxSamples.PerformanceTest();
        ALoxSampleReset();

        // do some performance tests.
        Console.WriteLine( "PRINT: Performance test (release logging):" );
           AloxSamples.PerformanceTestRL();
        ALoxSampleReset();

        // test class TextFileLogger
        Console.WriteLine( "PRINT: test class TextFileLogger:" );
            AloxSamples.TextFileLogger();
        ALoxSampleReset();

        // test class terminal test (colors and styles)
        Console.WriteLine( "PRINT: Colors (depending on detected terminal):" );
            AloxSamples.ColorTest();
        ALoxSampleReset();

        Console.WriteLine( "PRINT: Thats it!" );

        // sample ALib report facility through ALox
        AloxSamples.SampleALibReport();

//! [DOXYGEN_REMOVE_INIFILE]
        //...
        ALIB.Config.RemovePlugin( iniFile );
        ALIB.Config.FetchFromDefault( iniFile );
        iniFile.WriteFile();

        ALIB.TerminationCleanUp();
    }
//! [DOXYGEN_REMOVE_INIFILE]

    static void ALoxSampleReset()
    {
        Log.Reset();
        Log.SetSourcePathTrimRule( "*/src.cs/", Inclusion.Include );
    }

    public static void DebugLogging()
    {
        Log.Info( "Hello ALox" );
    }

    public static void ReleaseLogging()
    {
        // create a lox for release logging
        Lox lox= new Lox( "ReleaseLox" );

        // let the system choose an appropriate console logger
        TextLogger releaseLogger=  Lox.CreateConsoleLogger();

        // In debug compilations, we still install a report writer.
        Log.AddALibReportWriter( lox );
        #if ALOX_DBG_LOG
            lox.SetVerbosity( releaseLogger, Verbosity.Verbose, ALoxReportWriter.LogDomain() );
        #endif

        // we set a format string without scope information (as this is of-course not available in release logging)
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            releaseLogger.MetaInfo.Format= new AString( "[%TC +%TL][%tN]%V[%D]%A1(%#): " );
        #endif
        lox.SetVerbosity( releaseLogger, Verbosity.Info, "A_DOMAIN" );

        lox.Info ( "A_DOMAIN", "Hello ALox, this is release logging" );

        // cleanup
        Log.RemoveALibReportWriter();
        lox.RemoveLogger( releaseLogger );
    }

    public static void PerformanceTest()
    {
        Log.AddDebugLogger();
        MemoryLogger ml= new MemoryLogger();

        Log.SetVerbosity( Log.DebugLogger, Verbosity.Off );
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, "/CON" );
        Log.SetVerbosity( ml,              Verbosity.Verbose, "/MEM" );

        Log.Info( "/CON", "Logging simple info lines into a memory logger" );

        AString  msgBuf=  new AString( );
        long     fastest= long.MaxValue;
        Ticks    timer=     new Ticks();
        int      qtyLines=    100;
        int      qtyLoops=   1000;
        if( System.Diagnostics.Debugger.IsAttached )
            qtyLines= qtyLoops= 10;

        for ( int i= 0 ; i < qtyLoops ; i++ )
        {
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                ml.MemoryLog.Clear();
            #endif

            timer.Set();
                for ( int ii= 0 ; ii < qtyLines ; ii++ )
                {
                    Log.Info( "/MEM", "Test Line" );
                    if( i== 0 && ii == 0) Console.WriteLine( ml.MemoryLog.ToString() );
                }
            long t= timer.Age().Raw();

            if ( fastest > t )
            {
                fastest= t;
                Log.Info( "/CON", msgBuf.Clear()._( "Pass " )._( i, 3)._( " is new fastest:  ")
                        ._( (int) (new Ticks( fastest)).InMicros(), 0)._( " micros per ")._(qtyLines)._(" logs.") );
            }
        }

        double microsPerLog=  ( (double) (new Ticks(fastest)).InMicros() ) / qtyLines;
        int    logsPerSecond= (int)( 1000000.0 / microsPerLog);
        Log.Info( "/CON", msgBuf._()._( "  " )._( ESC.MAGENTA )._( "Fastest Debug Logging: " )
                                            ._( microsPerLog  )._( " micros per log (resp " )
                                            ._( logsPerSecond )._( " logs per second) " ) );

        Log.RemoveDebugLogger();
    }

    public static void PerformanceTestRL()
    {
        // create a lox for release logging
        Lox lox= new Lox( "ReleaseLox" );
        TextLogger   relLogger= Lox.CreateConsoleLogger();
        MemoryLogger ml       = new MemoryLogger();


        lox.SetVerbosity( relLogger, Verbosity.Verbose, "/CON" );
        lox.SetVerbosity( ml       , Verbosity.Verbose, "/MEM" );


        lox.Info( "/CON", "Logging simple info lines into a memory logger" );

        AString  msgBuf=  new AString( );
        long     fastest= long.MaxValue;
        Ticks    timer=     new Ticks();
        int      qtyLines=   100;
        int      qtyLoops=  1000;
        if( System.Diagnostics.Debugger.IsAttached )
            qtyLines= qtyLoops= 10;

        for ( int i= 0 ; i < qtyLoops ; i++ )
        {
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                ml.MemoryLog.Clear();
            #endif

            timer.Set();
                for ( int ii= 0 ; ii < qtyLines ; ii++ )
                {
                    lox.Info( "/MEM", "Test Line" );
                    if( i== 0 && ii == 0) Console.WriteLine( ml.MemoryLog.ToString() );
                }
            long t= timer.Age().Raw();

            if ( fastest > t )
            {
                fastest= t;
                lox.Info( "/CON", msgBuf.Clear()._( "Pass " )._( i, 3)._( " is new fastest:  ")
                                       ._( (int) (new Ticks( fastest)).InMicros(), 0)
                                       ._( " micros per ")._(qtyLines)._(" logs.") );
            }
        }

        double microsPerLog=  ( (double) (new Ticks(fastest)).InMicros() ) / qtyLines;
        int    logsPerSecond= (int)( 1000000.0 / microsPerLog);
        lox.Info( "/CON", msgBuf._()._( "  " )._( ESC.MAGENTA )._( "Fastest Release Logging: " )
                                    ._( microsPerLog  )._( " micros per log (resp " )
                                    ._( logsPerSecond )._( " logs per second) " ) );

        lox.RemoveLogger( ml );
        lox.RemoveLogger( relLogger );
    }

    public static void TextFileLogger()
    {
        Log.Info( "Creating a text file logger with file 'Test.log.txt'" );
        Log.SetDomain( "/TEXTFILE_TEST", Scope.Method );

        #if ALOX_REL_LOG
            TextFileLogger tfl= new TextFileLogger( "Test.log.txt" );
            Log.SetVerbosity( tfl, Verbosity.Verbose );
            Log.SetVerbosity( tfl, Verbosity.Error, ALox.InternalDomains );
        #endif

        Log.SetVerbosity( "TEXTFILE", Verbosity.Verbose, "" );

        Log.Verbose( "A verbose message (goes to textfile logger as well)" );
        Log.Info   ( "An info message  (goes to textfile logger as well)" );
        Log.Warning( "A warning message  (goes to textfile logger as well)" );
        Log.Error  ( "An error message (goes to textfile logger as well)" );
        Log.Info   ( "Multiline part 1...\n....part 2" );
    }

    public static void ColorTest()
    {
        Log.AddDebugLogger();
        Log.SetDomain( "/COLORS", Scope.Method );

        Log.Info(      "Hello ALox, this debug logging" );
        Log.Verbose(   "Some verbose log output" );
        Log.Warning(   "A warning" );
        Log.Error(     "An error" );

        Log.Info( "Playing with colors. Depending on the test environment, the colors might "
                    +  "be visible or not" );
        Log.Info( "In the memory logger, all color/style codes have to disappear (by default)" );
        Log.Verbose( "A verbose message" );
        Log.Info   ( "An info message" );
        Log.Warning( "A warning message" );
        Log.Error  ( "An error message" );

        Log.Info(    "FG Colors:  "
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

        Log.Info(    "BG Colors:  "
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

        Log.Info(    "FG/BG same: "
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


        Log.Info(    "Reset FG/BG: "
                            + ESC.BG_RED     + "BG RED"
                            + ESC.GREEN      + "FG REEN"
                            + ESC.FG_RESET   + "FG Reset"
                            + ESC.BG_RESET   + "BG Reset"
                            );

        Log.Info(    "Reset FG/BG: "
                            + ESC.BG_RED     + "BG RED"
                            + ESC.GREEN      + "FG REEN"
                            + ESC.BG_RESET   + "BG Reset"
                            + ESC.FG_RESET   + "FG Reset"
                            );

        Log.Info(    "Reset FG/BG: "
                            + ESC.BG_RED     + "BG RED"
                            + ESC.GREEN      + "FG REEN"
                            + ESC.RESET      + "All Reset"
                            );

        Log.Info(    "Styles: "
                            + ">>>" + ESC.BOLD     + "Bold"          + ESC.STYLE_RESET + "<<<"
                            + ">>>" + ESC.ITALICS  + "Italics"       + ESC.STYLE_RESET  + "<<<"
                            + ">>>" + ESC.BOLD
                            + ">>>" + ESC.ITALICS  + "Bold/Italics"   + ESC.STYLE_RESET  + "<<<"
                            );

        Log.Info(    "Reset Style/FG/BG: "
                            + ESC.BOLD        + "Bold"
                            + ESC.BG_RED      + "BG RED"
                            + ESC.GREEN       + "FG REEN"
                            + ESC.BG_RESET    + "BG Reset"
                            + ESC.FG_RESET    + "FG Reset"
                            + ESC.STYLE_RESET + "Style Reset"
                            );

        Log.Info(    "Reset Style/FG/BG: "
                            + ESC.BOLD        + "Bold"
                            + ESC.BG_RED      + "BG RED"
                            + ESC.GREEN       + "FG REEN"
                            + ESC.RESET       + "Reset All"
                            );

        Log.Info(    "Reset Style/FG/BG: "
                            + ESC.BOLD        + "Bold"
                            + ESC.BG_RED      + "BG RED"
                            + ESC.GREEN       + "FG REEN"
                            + ESC.STYLE_RESET + "Style Reset"
                            + ESC.BG_RESET    + "BG Reset"
                            + ESC.FG_RESET    + "FG Reset"
                            + "   +< This does not work on ANSI terminals: Styl reset, resets ALL here"
                            );

        Log.Info(    "An URL: "
                            + ESC.URL_START   + "www.darwin.heaven"
                            + ESC.URL_END     + ", your resource for happyness!"
                            );

    }

    public static void SampleALibReport()
    {
        Console.WriteLine( "Sample: ALib Report via using ALox" );

        Log.AddDebugLogger();
        Log.SetDomain( "/SAMPLE", Scope.Filename);
        Log.SetVerbosity( Log.DebugLogger, Verbosity.Info, "" );
        Log.Info(   "Method \"Log.AddDebugLogger()\" by default creates a replacement for the\n"
                  + "standard ALib report writer. If this is a debug compiliation, let's have a try and\n"
                  + "create 3 Messages:"  );

            Report.GetDefault().PushHaltFlags( false, false );
                ALIB.ERROR(   "This is an error report!" );
                ALIB.WARNING( "And this is a warning!"   );
                AString illegalAccess= new AString(10);
                illegalAccess._("1234");
                illegalAccess.SetCharAt_NC(5, '5');
            Report.GetDefault().PopHaltFlags();


            Log.SetVerbosity( Log.DebugLogger, Verbosity.Verbose, ALox.InternalDomains );
            ALIB.REPORT( 2,   "This is an ALib Report. Types other than '0' and '1' are user defined.\n"
                            + "Verbosity of ALox.InternalDomains has to be increased to see them when using"
                            + " ALoxReportWriter." );


        Log.Info(   "Note the domain prefix '" + ALox.InternalDomains.ToString() + "'. This addresses "
                  + "the tree of internal domains\nof the Lox, which the report writer is just "
                  + "using for ALib reports." );

        Log.RemoveDebugLogger();
    }


} // class
}
