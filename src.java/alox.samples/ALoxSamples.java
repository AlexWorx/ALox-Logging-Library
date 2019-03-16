// #################################################################################################
//  ALox Samples
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

import com.aworx.lib.ALIB;
import com.aworx.lib.lang.Report;
import com.aworx.lib.config.Configuration;
import com.aworx.lib.config.IniFile;
import com.aworx.lib.config.Variable;
import com.aworx.lib.strings.AString;
import com.aworx.lib.time.Ticks;
import com.aworx.lox.ALox;
import com.aworx.lox.ALoxReportWriter;
import com.aworx.lox.ESC;
import com.aworx.lox.Log;
import com.aworx.lox.Lox;
import com.aworx.lox.Scope;
import com.aworx.lox.Verbosity;
import com.aworx.lox.detail.textlogger.TextLogger;
import com.aworx.lox.loggers.MemoryLogger;
import com.aworx.lox.loggers.TextFileLogger;

public class ALoxSamples
{
    public static void debugLogging()
    {
        Log.info( "Hello ALox" );
    }

    public static void releaseLogging()
    {
        // create a lox for release logging
        Lox lox= new Lox( "MyReleaseLox" );

        // let the system choose an appropriate console logger
        TextLogger releaseLogger= Lox.createConsoleLogger( "MyReleaseLogger" );

        // In debug compilations, we still install a report writer.
        Log.addALibReportWriter( lox );
        lox.setVerbosity( releaseLogger, Verbosity.VERBOSE, ALoxReportWriter.logDomain() );

        // we set a format string without scope information (as this is of-course not available in release logging)
        releaseLogger.metaInfo.format= new AString( "[%TC +%TL][%tN]%V[%D]%A1(%#): " );
        lox.setVerbosity( releaseLogger, Verbosity.INFO, "A_DOMAIN" );

        lox.info ( "A_DOMAIN", "Hello ALox, this is release logging" );

        // cleanup
        Log.removeALibReportWriter();
        lox.removeLogger( releaseLogger );
    }

    // #############################################################################################
    // Test functions
    // #############################################################################################
    static void sampleALibReport()
    {
        System.out.println( "Sample: ALib Report Writer" );
        Log.setDomain( "SAMPLE", Scope.METHOD);

        Log.addDebugLogger();
        Log.setVerbosity(  Log.debugLogger,  Verbosity.INFO, "/"  );

        Log.info(   "Method \"Log.addDebugLogger()\" by default creates a replacement for the\n"
                  + "standard ALib report writer. If this is a debug compiliation, let's have a try and\n"
                  + "create 3 Messages:"  );

        Report.getDefault().pushHaltFlags(false, false);
            com.aworx.lib.ALIB_DBG.ERROR(   "This is an error report!" );
            com.aworx.lib.ALIB_DBG.WARNING( "And this is a warning! ({})", "With a parameter"  );
            AString illegalAccess= new AString(10);
            illegalAccess._()._("1234");
            illegalAccess.setCharAt_NC( 5, '5' );
        Report.getDefault().popHaltFlags();

        Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS);
        com.aworx.lib.ALIB_DBG.REPORT( 2,   "This is an ALib Report. Types other than '0' and '1' are user defined.\n"
                       + "Verbosity of ALox.INTERAL_DOMAINS has to be increased to see them when using"
                       + " ALoxReportWriter." );

        Log.info(   "Note the domain prefix '" + ALox.INTERNAL_DOMAINS.toString() + "'. This addresses "
                  + "the tree of internal domains\nof the Lox, which the report writer is just "
                  + "using." );

        Log.removeDebugLogger();
    }

    static void performanceTest()
    {
        Log.addDebugLogger();
        MemoryLogger  ml= new MemoryLogger( "Memory");

        Log.setVerbosity( Log.debugLogger, Verbosity.OFF);
        Log.setVerbosity( Log.debugLogger, Verbosity.INFO   , "/CON", Configuration.PRIO_PROTECTED_VALUES);
        Log.setVerbosity( ml,              Verbosity.VERBOSE, "/MEM", Configuration.PRIO_PROTECTED_VALUES);

        Log.info( "Logging simple info lines" );
        long  fastest=    Long.MAX_VALUE;
        int   qtyLines=   100;
        int   qtyLoops=   1000;
        for ( int i= 0 ; i < qtyLoops ; i++ )
        {
            ml.memoryLog.clear();
            Ticks tt= new Ticks();
                for ( int ii= 0 ; ii < qtyLines ; ii++ )
                {
                    Log.info( "/MEM", "Test Line ", ii );
                    if( i== 0 && ii == 0) Log.info( "/CON", "Sample Output:\\n{}", ml.memoryLog );
                }
            Ticks t= tt.age();
            if ( t.raw() < fastest )
            {
                fastest= t.raw();
                Log.verbose( "/CON", "Pass {:03} is new fastest: {:4} micros per {} logs.",
                                     i, (new Ticks( fastest)).inMicros(), qtyLines );
            }

        }
        double microsPerLog=  ( (double) (new Ticks(fastest)).inMicros() ) / qtyLines;
        int    logsPerSecond= (int)( 1000000.0 / microsPerLog);
        Log.info( "/CON", ESC.MAGENTA, "  Fastest Debug Logging: {} micros per log (resp. {:,} logs per second) ",
                          microsPerLog, logsPerSecond );


       Log.removeDebugLogger();
       Log.removeLogger( ml );
    }

    static void performanceTestRL()
    {
        Lox lox= new Lox( "ReleaseLox" );

        TextLogger    relLogger= Lox.createConsoleLogger( "Console" );
        MemoryLogger  ml=        new MemoryLogger( "Memory");
        lox.setVerbosity( relLogger, Verbosity.INFO   , "/CON", Configuration.PRIO_PROTECTED_VALUES);
        lox.setVerbosity( relLogger, Verbosity.OFF    , "/MEM", Configuration.PRIO_PROTECTED_VALUES);
        lox.setVerbosity( ml,        Verbosity.VERBOSE, "/MEM", Configuration.PRIO_PROTECTED_VALUES);


        lox.info( "Logging simple info lines (release logging)" );
        long fastest=   Long.MAX_VALUE;
        int  qtyLines=  100;
        int  qtyLoops=  1000;
        for ( int i= 0 ; i < qtyLoops ; i++ )
        {
            ml.memoryLog.clear();
            Ticks tt= new Ticks();
                for ( int ii= 0 ; ii < qtyLines ; ii++ )
                {
                    lox.info( "/MEM", "Test Line ", ii );
                    if( i== 0 && ii == 0) lox.info( "/CON", "Sample Output:\\n{}", ml.memoryLog );
                }

            Ticks t= tt.age();
            if ( t.raw() < fastest )
            {
                fastest= t.raw();
                lox.verbose( "/CON", "Pass {:03} is new fastest: {:4} micros per {} logs.",
                                      i, (new Ticks( fastest)).inMicros(), qtyLines );
            }

        }
        double microsPerLog=  ( (double) (new Ticks(fastest)).inMicros() ) / qtyLines;
        int    logsPerSecond= (int)( 1000000.0 / microsPerLog);
        lox.info( "/CON", ESC.MAGENTA, "  Fastest Release Logging: {} micros per log (resp. {:,} logs per second) ",
                          microsPerLog, logsPerSecond );


       Log.removeLogger(relLogger);
       Log.removeLogger(ml);
    }


    public static void uniCodeOutput()
    {
        Log.addDebugLogger();

        Log.setDomain( "UNICODE", Scope.METHOD );

        Log.info( "Some unicode characters:" );
        Log.info( " Euro Sign:     €" );
        Log.info( " Micro:         µ" );
        Log.info( " More Greek:    \u03B1\u03B2\u03B3\u03B4\u03B5" );

        Log.removeDebugLogger( null );
    }

    public static void formatting()
    {
        Log.info("Python-Style Format: {}, {:08.3}, *{:^12}*", "Hello", 12.3456789, "Centered" );
        Log.info("Java-Style Format:   %s, %08.3f, *%^12s*"  , "Hello", 12.3456789, "Centered" );

        Log.info("We can mix styles: {}-Style", "Python", " and %s-Style in one log statement", "Java" );
        Log.info("But mixing must not be done within one format string: {} %s", "Right", "Wrong" );
    }

    public static void colorsAndStyles()
    {
        Log.addDebugLogger();

        Log.setDomain( "COLORS", Scope.METHOD );


        Log.info   ( "Let us do some color test. First, lets see if different verbosities have different colors:" );
        Log.verbose( "A verbose message" );
        Log.info   ( "An info message" );
        Log.warning( "A warning message" );
        Log.error  ( "An error message" );
        Log.info   ( "Color table:");

        Log.info( "FG Colors:  "
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


        Log.info( "BG Colors:  "
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

        Log.info( "FG/BG same: "
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

        Log.info( "Styles: "
                                    + ">>>" + ESC.BOLD     + "Bold"          + ESC.STYLE_RESET + "<<<"
                                    + ">>>" + ESC.ITALICS  + "Italics"       + ESC.STYLE_RESET  + "<<<"
                                    + ">>>" + ESC.BOLD
                                    + ">>>" + ESC.ITALICS  + "Bold/Italics"   + ESC.STYLE_RESET  + "+<  Styles do not work in Windows consoles"
                                    );

        Log.info( "An URL: "
                                    + ESC.URL_START   + "http://www.darwin.heaven"
                                    + ESC.URL_END     + ", your resource for happyness!"
                                    );

        // that's it
        Log.removeDebugLogger( null );
    }

    public static void textFileLogger()
    {
        Log.setDomain( "TEXTFILE_TEST", Scope.METHOD    );
        Log.info( "Creating a text file logger with file 'Test.log.txt'" );

        TextFileLogger tfl= new TextFileLogger( "Test.log.txt" );
        Log.setVerbosity( tfl, Verbosity.VERBOSE );
        Log.setVerbosity( tfl, Verbosity.ERROR, ALox.INTERNAL_DOMAINS );

        Log.verbose( "A verbose message (goes to textfile logger as well)" );
        Log.info   ( "An info message  (goes to textfile logger as well)" );
        Log.warning( "A warning message  (goes to textfile logger as well)" );
        Log.error  ( "An error message (goes to textfile logger as well)" );
        Log.info   ( "Multiline part 1...\n....part 2" );
    }

    static void aworxLibraryDebugCodePruning()
    {
        Report.getDefault().pushHaltFlags(false, false);
            Log.addDebugLogger();

            String appear=    "This message should appear in pruned version";
            String notAppear= "This message should NOT appear in pruned version";

            // without 'macros'
            Report.getDefault().doReport( 0, appear ); // error
            Report.getDefault().doReport( 1, appear ); // warning

            com.aworx.lib.ALIB_DBG.ERROR         (        notAppear );
            com.aworx.lib.ALIB_DBG.WARNING       (        notAppear );
            com.aworx.lib.ALIB_DBG.ASSERT_ERROR  ( false, notAppear );
            com.aworx.lib.ALIB_DBG.ASSERT_WARNING( false, notAppear );

        Report.getDefault().popHaltFlags();
    }


    // #############################################################################################
    // static entrance (Main)
    // #############################################################################################
    /**
     *  In-between the different tests, we have to do some System.out.println() here to have at
     *  least a minimum output after pruning \b %ALox (as this software does not do anything but
     *  logging).
     *
     * @param args
     */
    public static void main(String[] args)
    {
        // first attach INI file to config system...
        IniFile iniFile= new IniFile();
        if ( iniFile.fileComments.isEmpty() )
        {
            iniFile.fileComments._(
            "##################################################################################################\n" +
            "# ALox Samples INI file (created when running ALox Samples)\n"                                        +
            "#\n"                                                                                                  +
            "# Copyright 2013-2019 A-Worx GmbH, Germany\n"                                                         +
            "# Published under 'Boost Software License' (a free software license, see LICENSE.txt)\n"                    +
            "##################################################################################################\n"
            );
        }

        Configuration config= new Configuration();
        config.setCommandLineArgs(args);
        config.insertPlugin( iniFile, Configuration.PRIO_STANDARD );

        // .. then initialize ALox Logging Library
        ALox.init( config );

        // Suppress setting "writeback" for verbosities. We need to do this as this main()
        // method invokes a list of independent samples. Those would now read from the INI file wrong
        // values written in other sample methods and thus the samples would not work any more
        // (because INI file settings overrules settings in the code)
        Variable var= new Variable();
        config.store( var.declare( "ALOX", "LOG_DEBUG_LOGGER_VERBOSITY"  ), "" );
        config.store( var.declare( "ALOX", "RELEASELOX_CONSOLE_VERBOSITY"), "" );
        config.store( var.declare( "ALOX", "LOG_MEMORY_VERBOSITY"        ), "" );
        config.store( var.declare( "ALOX", "RELEASELOX_MEMORY_VERBOSITY" ), "" );
        config.store( var.declare( "ALOX", "LOG_TEXTFILE_VERBOSITY"      ), "" );


        System.out.println( "PRINT: Hello world debug logging" );
            ALoxSamples.debugLogging();
        ALox.reset();
        System.out.println();

        System.out.println( "PRINT: Release logging test:" );
            ALoxSamples.releaseLogging();
        ALox.reset();
        System.out.println();

        System.out.println( "PRINT: Performance test (debug logging):" );
            ALoxSamples.performanceTest();
        ALox.reset();
        System.out.println();

        System.out.println( "PRINT: Performance test (release logging):" );
            ALoxSamples.performanceTestRL();
        ALox.reset();
        System.out.println();

        System.out.println( "PRINT: Use the predefined formatters:" );
            ALoxSamples.formatting();
        ALox.reset();
        System.out.println();

        System.out.println( "PRINT: Colors and Styles:" );
            ALoxSamples.colorsAndStyles();
        ALox.reset();
        System.out.println();

        System.out.println( "PRINT: TextFile Logger" );
            ALoxSamples.textFileLogger();
        ALox.reset();
        System.out.println();

        ALoxSamples.uniCodeOutput();
        ALox.reset();

        System.out.println();
        System.out.println( "PRINT: AWorx Library debug code pruning test (errors displayed are just for testing!):" );
            ALoxSamples.aworxLibraryDebugCodePruning();
        ALox.reset();
        System.out.println();

        System.out.println();
        System.out.println( "PRINT: Sample ALib report:" );
            ALoxSamples.sampleALibReport();
        System.out.println();

        System.out.println( "PRINT: Thats it!" );
        config.removePlugin( iniFile );
        config.fetchFromDefault( iniFile );
        iniFile.writeFile();

        ALIB.terminationCleanUp();
    }
}
