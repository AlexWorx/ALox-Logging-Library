// #################################################################################################
//  Simple Tests - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################



import com.aworx.lib.ALIB;
import com.aworx.lib.Report;
import com.aworx.lib.config.Configuration;
import com.aworx.lib.config.IniFile;
import com.aworx.lib.strings.AString;
import com.aworx.lib.time.Ticks;
import com.aworx.lox.*;
import com.aworx.lox.core.textlogger.TextLogger;
import com.aworx.lox.loggers.AnsiConsoleLogger;
import com.aworx.lox.loggers.MemoryLogger;

public class ALoxSamples
{

    public void debugLogging()
    {
        Log.info( "Hello ALox" );
    }

    public void releaseLogging()
    {
        // create a lox for release logging
        Lox lox= new Lox( "ReleaseLox" );

        // let the system choose an appropriate console logger
        TextLogger releaseLogger= Lox.createConsoleLogger();

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
    void sampleALibReport()
    {
        System.out.println( "Sample: ALib Report via using ALox" );
        Log.setDomain( "SAMPLE", Scope.METHOD);

        Log.addDebugLogger();
        Log.setVerbosity(  Log.debugLogger,  Verbosity.INFO, "/"  );

        Log.info(   "Method \"Log.AddDebugLogger()\" by default creates a replacement for ALib\n"
                  + "error/warning reporter. If this is a debug compiliation, let's have a try and\n"
                  + "create 3 Messages:"  );

        Report.getDefault().pushHaltFlags(false, false);
            ALIB.ERROR(   "This is an error report!" );
            ALIB.WARNING( "And this is a warning!"   );
            AString illegalAccess= new AString(10);
            illegalAccess._()._("1234");
            illegalAccess.setCharAt_NC( 5, '5' );
        Report.getDefault().popHaltFlags();

        Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS);
        ALIB.REPORT( 2,   "This is an ALib Report. Types other than '0' and '1' are user defined.\n"
                        + "Verbosity of ALox.INTERAL_DOMAINS has to be increased to see them when using"
                        + " ALoxReportWriter." );

        Log.info(   "Note the domain prefix '" + ALox.INTERNAL_DOMAINS.toString() + "'. This addresses "
                  + "the tree of internal domains\nof the Lox, which the report writer is just "
                  + "using." );

        Log.removeDebugLogger();
    }

    void performanceTest()
    {
        Log.addDebugLogger();
        MemoryLogger  ml= new MemoryLogger( "Memory");

        Log.setVerbosity( Log.debugLogger, Verbosity.OFF);
        Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, "/CON");
        Log.setVerbosity( ml,              Verbosity.VERBOSE, "/MEM" );

        Log.info( "Logging simple info lines" );
        long  fastest=    Long.MAX_VALUE;
        int   qtyLines=    100;
        int   qtyLoops=   1000;
        for ( int i= 0 ; i < qtyLoops ; i++ )
        {
            ml.memoryLog.clear();
            Ticks tt= new Ticks();
                for ( int ii= 0 ; ii < qtyLines ; ii++ )
                {
                    Log.info( "/MEM", "Test Line " + ii );
                    if( i== 0 && ii == 0) System.out.println( ml.memoryLog.toString() );
                }
            Ticks t= tt.age();
            if ( t.raw() < fastest )
            {
                fastest= t.raw();
                Log.info( "/CON",
                         Log.buf()._( "Pass " )._( i, 3)._( " is new fastest:  ")
                                  ._(  (new Ticks( fastest)).inMicros(), 0)._( " micros per ")
                                  ._( qtyLines)._( " logs.") );
            }

        }
        double microsPerLog=  ( (double) (new Ticks(fastest)).inMicros() ) / qtyLines;
        int    logsPerSecond= (int)( 1000000.0 / microsPerLog);
        Log.info( "/CON", Log.buf()._( "  " )._( ESC.MAGENTA )._( "Fastest Debug Logging: " )
                                   ._( microsPerLog  )._( " micros per log (resp " )
                                   ._( logsPerSecond )._( " logs per second) " ) );


       Log.removeDebugLogger();
       Log.removeLogger( ml );
    }

    void performanceTestRL()
    {
        Lox lox= new Lox( "ReleaseLox" );

        TextLogger    relLogger= Lox.createConsoleLogger( "Console" );
        MemoryLogger  ml=        new MemoryLogger( "Memory");
        lox.setVerbosity( relLogger, Verbosity.VERBOSE, "/CON" );
        lox.setVerbosity( ml,        Verbosity.VERBOSE, "/MEM" );


        lox.info( "Logging simple info lines (release logging)" );
        long fastest=   Long.MAX_VALUE;
        int  qtyLines=   100;
        int  qtyLoops=  1000;
        for ( int i= 0 ; i < qtyLoops ; i++ )
        {
            ml.memoryLog.clear();
            Ticks tt= new Ticks();
                for ( int ii= 0 ; ii < qtyLines ; ii++ )
                {
                    lox.info( "/MEM", "Test Line " + ii );
                    if( i== 0 && ii == 0) System.out.println( ml.memoryLog.toString() );
                }

            Ticks t= tt.age();
            if ( t.raw() < fastest )
            {
                fastest= t.raw();
                lox.entry( "/CON", Verbosity.INFO,
                         lox.buf()._( "Pass " )._( i, 3)._( " is new fastest:  ")
                                  ._(  (new Ticks( fastest)).inMicros(), 0)._( " micros per ")
                                  ._( qtyLines)._( " logs.") );
            }

        }
        double microsPerLog=  ( (double) (new Ticks(fastest)).inMicros() ) / qtyLines;
        int    logsPerSecond= (int)( 1000000.0 / microsPerLog);
        lox.info( "/CON", lox.buf()._( "  " )._( ESC.MAGENTA )._( "Fastest Release Logging: " )
                                   ._( microsPerLog  )._( " micros per log (resp " )
                                   ._( logsPerSecond )._( " logs per second) " ) );


       Log.removeLogger(relLogger);
       Log.removeLogger(ml);
    }


    public void uniCodeOutput()
    {
        Log.addDebugLogger();

        Log.setDomain( "UNICODE", Scope.METHOD );

        Log.info( "Some unicode characters:" );
        Log.info( " Euro Sign:     €" );
        Log.info( " Micro:         µ" );
        Log.info( " More Greek:    \u03B1\u03B2\u03B3\u03B4\u03B5" );

        Log.removeDebugLogger( null );
    }

    public void colorsAndStyles()
    {
        Log.addDebugLogger();

        Log.setDomain( "COLORS", Scope.METHOD );


        Log.info(   "Playing with colors. Depending on the test environment, the colors might "
                  + "be visible or not" );
        Log.info( "In the memory logger, all color/style codes have to disappear (by default)" );
        Log.verbose( "A verbose message" );
        Log.info   ( "An info message" );
        Log.warning( "A warning message" );
        Log.error  ( "An error message" );

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


        AnsiConsoleLogger acl= (AnsiConsoleLogger) Log.getLogger( "ANSI_CONSOLE" );
        if ( acl!=null )
            acl.isBackgroundLight= !acl.isBackgroundLight;
        Log.info( "Same rev.:  "
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
        if ( acl!=null )
            acl.isBackgroundLight= !acl.isBackgroundLight;


        Log.info( "Reset FG/BG: "
                                    + ESC.BG_RED     + "BG RED"
                                    + ESC.GREEN      + "FG REEN"
                                    + ESC.FG_RESET   + "FG Reset"
                                    + ESC.BG_RESET   + "BG Reset"
                                    );
        Log.info( "Reset FG/BG: "
                                    + ESC.BG_RED     + "BG RED"
                                    + ESC.GREEN      + "FG REEN"
                                    + ESC.BG_RESET   + "BG Reset"
                                    + ESC.FG_RESET   + "FG Reset"
                                    );

        Log.info( "Reset FG/BG: "
                                    + ESC.BG_RED     + "BG RED"
                                    + ESC.GREEN      + "FG REEN"
                                    + ESC.RESET      + "All Reset"
                                    );

        Log.info( "Styles: "
                                    + ">>>" + ESC.BOLD     + "Bold"          + ESC.STYLE_RESET + "<<<"
                                    + ">>>" + ESC.ITALICS  + "Italics"       + ESC.STYLE_RESET  + "<<<"
                                    + ">>>" + ESC.BOLD
                                    + ">>>" + ESC.ITALICS  + "Bold/Italics"   + ESC.STYLE_RESET  + "+<  Styles do not work in Windows consoles"
                                    );


        Log.info( "Reset Style/FG/BG: "
                                    + ESC.BOLD        + "Bold"
                                    + ESC.BG_RED      + "BG RED"
                                    + ESC.GREEN       + "FG REEN"
                                    + ESC.BG_RESET    + "BG Reset"
                                    + ESC.FG_RESET    + "FG Reset"
                                    + ESC.STYLE_RESET + "Style Reset"
                                    );

        Log.info( "Reset Style/FG/BG: "
                                    + ESC.BOLD        + "Bold"
                                    + ESC.BG_RED      + "BG RED"
                                    + ESC.GREEN       + "FG REEN"
                                    + ESC.RESET       + "Reset All"
                                    );

        Log.info( "Reset Style/FG/BG: "
                                    + ESC.BOLD        + "Bold"
                                    + ESC.BG_RED      + "BG RED"
                                    + ESC.GREEN       + "FG REEN"
                                    + ESC.STYLE_RESET + "Style Reset"
                                    + ESC.BG_RESET    + "BG Reset"
                                    + ESC.FG_RESET    + "FG Reset"
                                    + "   +< This does not work on ANSI terminals: Styl reset, resets ALL here"
                                    );

        Log.info( "An URL: "
                                    + ESC.URL_START   + "www.darwin.heaven"
                                    + ESC.URL_END     + ", your resource for happyness!"
                                    );

        // that's it
        Log.removeDebugLogger( null );
    }

    public void textFileLogger()
    {
        Log.setDomain( "TEXTFILE_TEST", Scope.METHOD    );
        Log.info( "Creating a text file logger with file 'Test.log.txt'" );
        Log.setVerbosity( "TEXTFILE", Verbosity.VERBOSE, "TEXTFILE_TEST" );

        Log.verbose( "A verbose message (goes to textfile logger as well)" );
        Log.info   ( "An info message  (goes to textfile logger as well)" );
        Log.warning( "A warning message  (goes to textfile logger as well)" );
        Log.error  ( "An error message (goes to textfile logger as well)" );
        Log.info   ( "Multiline part 1...\n....part 2" );
    }

    void aworxLibraryDebugCodePruning()
    {
        Report.getDefault().pushHaltFlags(false, false);
            Log.addDebugLogger();

            String appear=    "This message should appear in pruned version";
            String notAppear= "This message should NOT appear in pruned version";

            // without 'macros'
            Report.getDefault().doReport( 0, appear ); // error
            Report.getDefault().doReport( 1, appear ); // warning

            ALIB.ERROR         (        notAppear );
            ALIB.WARNING       (        notAppear );
            ALIB.ASSERT_ERROR  ( false, notAppear );
            ALIB.ASSERT_WARNING( false, notAppear );

        Report.getDefault().popHaltFlags();
    }



    // #############################################################################################
    // static entrance (Main)
    // #############################################################################################
    /**
     *  In-between the different tests, we have to do some System.out.println() here to have at
     *  least a minimum output after pruning ALox (as this software does not do anything but
     *  logging).
     *
     * @param args
     */
    public static void main(String[] args)
    {
        ALox.init( true, args );

        // open and attach ini-file
        IniFile iniFile= new IniFile( null );
        ALIB.config.insertPlugin( iniFile, Configuration.PRIO_INI_FILE );

        // create us
        ALoxSamples test= new ALoxSamples();


        System.out.println( "PRINT: Hello world debug logging" );
            test.debugLogging();
        ALox.reset();
        System.out.println();

        // do some release logging tests.
        System.out.println( "PRINT: Release logging test:" );
            test.releaseLogging();
        ALox.reset();
        System.out.println();

        // do some performance tests.
        System.out.println( "PRINT: Performance test (debug logging):" );
            test.performanceTest();
        ALox.reset();
        System.out.println();

        // do some performance tests.
        System.out.println( "PRINT: Performance test (release logging):" );
            test.performanceTestRL();
        ALox.reset();
        System.out.println();

        // have a try on colors and styles
        System.out.println( "PRINT: Colors and Styles:" );
            test.colorsAndStyles();
        ALox.reset();
        System.out.println();

        // have a try on colors and styles
        System.out.println( "PRINT: TextFile Logger" );
            test.textFileLogger();
        ALox.reset();
        System.out.println();

        test.uniCodeOutput();
        ALox.reset();

        // test pruning of ALIB debug messages and assertions
        System.out.println();
        System.out.println( "PRINT: AWorx Library debug code pruning test (errors displayed are just for testing!):" );
            test.aworxLibraryDebugCodePruning();
        ALox.reset();
        System.out.println();


        System.out.println();
        System.out.println( "PRINT: Sample ALib report:" );
            test.sampleALibReport();
        System.out.println();

        System.out.println( "PRINT: Thats it!" );

        ALIB.terminationCleanUp();
    }
}
