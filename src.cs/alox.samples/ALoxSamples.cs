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

namespace ALox_CS_Test_Perf  {

class AloxTests
{
    // #############################################################################################
    // static entrance (Main)
    // #############################################################################################
    static void Main( string[] args )
    {
        ALIB.Init( true, args );

        // create us
        AloxTests test= new AloxTests();

        // do some release logging tests.
        Console.WriteLine( "PRINT: Debug logging:" );
            test.DebugLogging();
        Log.Reset();

        // do some release logging tests.
        Console.WriteLine( "PRINT: Release logging:" );
            test.ReleaseLogging();
        Log.Reset();

        // do some performance tests.
        Console.WriteLine( "PRINT: Performance test (debug logging):" );
           test.PerformanceTest();
        Log.Reset();

        // do some performance tests.
        Console.WriteLine( "PRINT: Performance test (release logging):" );
           test.PerformanceTestRL();
        Log.Reset();

        // test class TextFileLogger
        Console.WriteLine( "PRINT: test class TextFileLogger:" );
            test.TextFileLogger();
        Log.Reset();

        // test class terminal test (colors and styles)
        Console.WriteLine( "PRINT: Colors (depending on detected terminal):" );
            test.ColorTest();
        Log.Reset();

        Console.WriteLine( "PRINT: Thats it!" );

        // sample ALib report facility through ALox
        test.SampleALibReport();

        ALIB.TerminationCleanUp();
    }


    public void DebugLogging()
    {
        Log.Info( "Hello ALox" );
    }

    public void ReleaseLogging()
    {
        // create a lox for release logging
        Lox lox= new Lox();

        // let the system choose an appropriate console logger
        TextLogger releaseLogger=  Lox.CreateConsoleLogger();

        // we set a format string without caller information (as this is of-course not available in release logging)
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            releaseLogger.MetaInfo.Format= new AString( "[%TE +%TI] [%t] %L [%O] %A1(%#): " );
        #endif
        lox.AddLogger( releaseLogger );
        lox.SetDomain( "A_DOMAIN", Log.DomainLevel.InfoWarningsAndErrors );

        lox.Info ( "A_DOMAIN", "Hello ALox, this is release logging" );

        lox.RemoveLoggers();
    }

    void PerformanceTest()
    {
        Log.AddDebugLogger();
        #if ALOX_DBG_LOG
            Log.SetDomain( Log.LOX.InternalDomain, Log.DomainLevel.WarningsAndErrors, Log.DebugLogger.Name );
        #endif


        MemoryLogger ml= new MemoryLogger();
        Log.AddLogger( ml );


        Log.SetDomain( "CON", Log.Scope.SourceFile );
        Log.SetDomain( "MEM", Log.Scope.None  );
        Log.SetDomain( "BOTH",Log.Scope.None );

        Log.SetDomain( "CON", Log.DomainLevel.All);
        Log.SetDomain( "MEM", Log.DomainLevel.Off);
        Log.SetDomain( "MEM", Log.DomainLevel.All, "Memory" );
        Log.SetDomain( "CON", Log.DomainLevel.Off, "Memory" );
        Log.SetDomain( "BOTH",Log.DomainLevel.All );


        Log.Info( "Logging simple info lines into a memory logger" );

        AString  msgBuf=  new AString( );
        long     fastest= long.MaxValue;
        Ticks    timer=     new Ticks();
        const int qtyLines=   100;
        const int qtyLoops= 10000;

        for ( int i= 0 ; i < qtyLoops ; i++ )
        {
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                ml.MemoryLog.Clear();
            #endif

            timer.Set();
                for ( int ii= 0 ; ii < qtyLines ; ii++ )
                    Log.Info( "MEM", "Test Line" );
            long t= timer.Age().Raw();

            if ( fastest > t )
            {
                fastest= t;
                Log.Info( msgBuf.Clear()._( "Pass " )._( i, 3)._( " is new fastest:  ")
                        ._( (int) (new Ticks( fastest)).InMicros(), 0)._( " micros per ")._(qtyLines)._(" logs.") );
            }
        }

        double microsPerLog=  ( (double) (new Ticks(fastest)).InMicros() ) / qtyLines;
        int    logsPerSecond= (int)( 1000000.0 / microsPerLog);
        Log.Info( msgBuf._()._( "  " )._( ESC.MAGENTA )._( "Fastest Debug Logging: " )
                        ._( microsPerLog  )._( " micros per log (resp " )
                        ._( logsPerSecond )._( " logs per second) " ) );

        Log.RemoveDebugLogger();
    }

    void PerformanceTestRL()
    {
        // create a lox for release logging
        Lox lox= new Lox();
        TextLogger relLogger= Lox.CreateConsoleLogger();
        lox.AddLogger( relLogger );
        MemoryLogger ml= new MemoryLogger();
        lox.AddLogger( ml );


        lox.SetDomain( "CON", Log.Scope.SourceFile );
        lox.SetDomain( "MEM", Log.Scope.None  );
        lox.SetDomain( "BOTH",Log.Scope.None );

        lox.SetDomain( "CON", Log.DomainLevel.All );
        lox.SetDomain( "MEM", Log.DomainLevel.Off );
        lox.SetDomain( "MEM", Log.DomainLevel.All, "Memory" );
        lox.SetDomain( "CON", Log.DomainLevel.Off, "Memory" );
        lox.SetDomain( "BOTH",Log.DomainLevel.All  );


        lox.Info( "Logging simple info lines into a memory logger" );

        AString  msgBuf=  new AString( );
        long     fastest= long.MaxValue;
        Ticks    timer=     new Ticks();
        const int qtyLines=   100;
        const int qtyLoops= 10000;

        for ( int i= 0 ; i < qtyLoops ; i++ )
        {
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                ml.MemoryLog.Clear();
            #endif

            timer.Set();
                for ( int ii= 0 ; ii < qtyLines ; ii++ )
                    lox.Info( "MEM", "Test Line" );
            long t= timer.Age().Raw();

            if ( fastest > t )
            {
                fastest= t;
                lox.Info( msgBuf.Clear()._( "Pass " )._( i, 3)._( " is new fastest:  ")
                        ._( (int) (new Ticks( fastest)).InMicros(), 0)._( " micros per ")._(qtyLines)._(" logs.") );
            }
        }

        double microsPerLog=  ( (double) (new Ticks(fastest)).InMicros() ) / qtyLines;
        int    logsPerSecond= (int)( 1000000.0 / microsPerLog);
        lox.Info( msgBuf._()._( "  " )._( ESC.MAGENTA )._( "Fastest Debug Logging: " )
                            ._( microsPerLog  )._( " micros per log (resp " )
                            ._( logsPerSecond )._( " logs per second) " ) );

        lox.RemoveLoggers();
    }

    public void TextFileLogger()
    {
        Log.Info( "Creating a text file logger with file 'Test.log.txt'" );
        Log.AddLogger( new TextFileLogger( "Test.log.txt" ) );
        #if ALOX_DBG_LOG
            Log.GetLogger("TEXTFILE").SetDomain( Log.LOX.InternalDomain, Log.DomainLevel.Errors );
        #endif
        Log.SetDomain( "TEXTFILE_TEST", Log.Scope.Method    );
        Log.SetDomain( "TEXTFILE_TEST", Log.DomainLevel.All );

        Log.Verbose( "A verbose message (goes to textfile logger as well)" );
        Log.Info   ( "An info message  (goes to textfile logger as well)" );
        Log.Warning( "A warning message  (goes to textfile logger as well)" );
        Log.Error  ( "An error message (goes to textfile logger as well)" );
        Log.Info   ( "Multiline part 1...\n....part 2" );
    }

    void ColorTest()
    {

        Log.AddDebugLogger();

        Log.SetDomain( "COLORS", Log.DomainLevel.All );
        Log.SetDomain( "COLORS", Log.Scope.Method );

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

    void SampleALibReport()
    {
        Console.WriteLine( "Sample: ALib Report via using ALox" );

        Log.AddDebugLogger();
        Log.SetDomain( "SAMPLE", Log.DomainLevel.InfoWarningsAndErrors );
        Log.SetDomain( "SAMPLE", Log.Scope.SourceFile);
        Log.Info(   "Method \"Log.AddDebugLogger()\" by default creates a replacement for ALibs'\n"
                  + "error/warning reporter. If this is a debug compiliation, let's have a try and\n"
                  + "create an ALib error:"  );

        // must be done only in debug compiles
        //#if ALOX_DBG_LOG
            Report.GetDefault().HaltOnError= false;

            {
                AString illegalAccess= new AString(10);
                illegalAccess._("1234");
                illegalAccess.SetCharAt_NC(5, '5');
            }

            Report.GetDefault().HaltOnError= true;
        //#endif
        Log.Info( "Note the domain 'REPORT' used by ALib reporter." );

        Log.RemoveDebugLogger();
    }


} // class
}
