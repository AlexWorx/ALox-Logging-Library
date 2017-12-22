// #################################################################################################
//  Unit Tests - AWorx Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package ut_alox;

import org.junit.Test;

import com.aworx.lib.config.Variable;
import com.aworx.lib.lang.ContainerOp;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.util.AutoSizes;
import com.aworx.lox.ALox;
import com.aworx.lox.ESC;
import com.aworx.lox.Log;
import com.aworx.lox.Lox;
import com.aworx.lox.Scope;
import com.aworx.lox.Verbosity;
import com.aworx.lox.core.textlogger.MetaInfo;
import com.aworx.lox.loggers.AnsiLogger;
import com.aworx.lox.loggers.AnsiConsoleLogger;
import com.aworx.lox.loggers.MemoryLogger;
import ut_com_aworx.AWorxUnitTesting;

class ApplyLog
{
    public String Text;
    public int    Mode; // 0, no logging, 1 simple, 2 with formatter
    public ApplyLog( String text, int mode )
    {
        Text= text;
        Mode= mode;
    }


    @Override
    public String toString()
    {
        if( Mode == 1 )
        {
            String output= "Logging object >" + Text + "<";
            Log.info(output);
        }
        else if( Mode == 2 )
        {
            Log.info("{}{}{}", "Logging object >", Text, "<" );
        }

        return Text;
    }
}



class MyType
{/* empty type */}

public class UT_alox_logger extends AWorxUnitTesting
{
    /** ********************************************************************************************
     *     Log_ColorsAndStyles
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void Log_ColorsAndStyles()
    {
        UT_INIT();

        Log.addDebugLogger();
        Log.setDomain( "COLORS", Scope.METHOD );
        MemoryLogger ml= new MemoryLogger();
        Log.setVerbosity( ml , Verbosity.VERBOSE, "COLORS");


        Log.info(   "Playing with colors. Depending on the test environment, the colors might "
                  + "be visible or not" );
        Log.info( "In the memory logger, all color/style codes have to disappear (by default)" );
        Log.verbose( "A verbose message" );
        Log.info   ( "An info message" );
        Log.warning( "A warning message" );
        Log.error  ( "An error message" );

        ml.memoryLog.clear();
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


        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        ml.memoryLog.clear();
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


        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        ml.memoryLog.clear();
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


        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        AnsiConsoleLogger acl= (AnsiConsoleLogger) Log.getLogger( "ANSI_CONSOLE" );
        if ( acl!=null )
        {
            AnsiLogger.LightColorUsage useLightColors= acl.useLightColors;
            acl.useLightColors= acl.useLightColors == AnsiLogger.LightColorUsage.FOREGROUND_LIGHT ? AnsiLogger.LightColorUsage.FOREGROUND_DARK : AnsiLogger.LightColorUsage.FOREGROUND_LIGHT;
            ml.memoryLog.clear();
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
            acl.useLightColors= useLightColors;
        }


        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        ml.memoryLog.clear();
        Log.info( "Reset FG/BG: "
                                    + ESC.BG_RED     + "BG RED"
                                    + ESC.GREEN      + "FG REEN"
                                    + ESC.FG_RESET   + "FG Reset"
                                    + ESC.BG_RESET   + "BG Reset"
                                    );

        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        ml.memoryLog.clear();
        Log.info( "Reset FG/BG: "
                                    + ESC.BG_RED     + "BG RED"
                                    + ESC.GREEN      + "FG REEN"
                                    + ESC.BG_RESET   + "BG Reset"
                                    + ESC.FG_RESET   + "FG Reset"
                                    );

        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        ml.memoryLog.clear();
        Log.info( "Reset FG/BG: "
                                    + ESC.BG_RED     + "BG RED"
                                    + ESC.GREEN      + "FG REEN"
                                    + ESC.RESET      + "All Reset"
                                    );

        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        ml.memoryLog.clear();
        Log.info( "Styles: "
                                    + ">>>" + ESC.BOLD     + "Bold"          + ESC.STYLE_RESET + "<<<"
                                    + ">>>" + ESC.ITALICS  + "Italics"       + ESC.STYLE_RESET  + "<<<"
                                    + ">>>" + ESC.BOLD
                                    + ">>>" + ESC.ITALICS  + "Bold/Italics"   + ESC.STYLE_RESET  + "+<  Styles do not work in Windows consoles"
                                    );


        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        ml.memoryLog.clear();
        Log.info( "Reset Style/FG/BG: "
                                    + ESC.BOLD        + "Bold"
                                    + ESC.BG_RED      + "BG RED"
                                    + ESC.GREEN       + "FG REEN"
                                    + ESC.BG_RESET    + "BG Reset"
                                    + ESC.FG_RESET    + "FG Reset"
                                    + ESC.STYLE_RESET + "Style Reset"
                                    );

        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        ml.memoryLog.clear();
        Log.info( "Reset Style/FG/BG: "
                                    + ESC.BOLD        + "Bold"
                                    + ESC.BG_RED      + "BG RED"
                                    + ESC.GREEN       + "FG REEN"
                                    + ESC.RESET       + "Reset All"
                                    );

        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        ml.memoryLog.clear();
        Log.info( "Reset Style/FG/BG: "
                                    + ESC.BOLD        + "Bold"
                                    + ESC.BG_RED      + "BG RED"
                                    + ESC.GREEN       + "FG REEN"
                                    + ESC.STYLE_RESET + "Style Reset"
                                    + ESC.BG_RESET    + "BG Reset"
                                    + ESC.FG_RESET    + "FG Reset"
                                    + "   +< This does not work on ANSI terminals: Styl reset, resets ALL here"
                                    );

        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        ml.memoryLog.clear();
        Log.info( "An URL: "
                                    + ESC.URL_START   + "www.darwin.heaven"
                                    + ESC.URL_END     + ", your resource for happyness!"
                                    );

        UT_TRUE( ml.memoryLog.indexOf("\033") < 0 );

        Log.removeLogger( ml );

    }

    /** ********************************************************************************************
    * Log_TextLogger_FormatConfig
    **********************************************************************************************/
    static
    void testFormatConfig( String testFormat,
                           String expFmt,
                           String expFmtError   ,
                           String expFmtWarning ,
                           String expFmtInfo    ,
                           String expFmtVerbose
                         )
    {
        Variable var= new Variable();
        ALox.config.store( var.declare(ALox.configCategoryName, "TESTML_FORMAT", ','), testFormat  );
        Lox lox= new Lox("TEST");
        MemoryLogger ml= new MemoryLogger("TESTML");
        lox.setVerbosity( ml, Verbosity.INFO );
        lox.removeLogger( ml );
        ALox.register( lox, ContainerOp.REMOVE );

                                     UT_EQ( expFmt       , ml.metaInfo.format );
        if( expFmtError  != null ) { UT_EQ( expFmtError  , ml.metaInfo.verbosityError   ); }
        if( expFmtWarning!= null ) { UT_EQ( expFmtWarning, ml.metaInfo.verbosityWarning ); }
        if( expFmtInfo   != null ) { UT_EQ( expFmtInfo   , ml.metaInfo.verbosityInfo    ); }
        if( expFmtVerbose!= null ) { UT_EQ( expFmtVerbose, ml.metaInfo.verbosityVerbose ); }
    }


    @SuppressWarnings("static-method")
    @Test
    public void Log_TextLogger_FormatConfig()
    {
        UT_INIT();

        testFormatConfig( "Test"                                , "Test", null,null,null,null     );
        testFormatConfig( "\"Test"                              , "Test", null,null,null,null     );
        testFormatConfig( "\"Test\""                            , "Test", null,null,null,null     );
        testFormatConfig( "  \" Test  \"  s"                    , " Test  s",null,null,null,null  );

        testFormatConfig( " Test , a ,b, c,d  "                 , "Test", "a","b","c","d"         );
        testFormatConfig( "\" Test, a\" ,b, \"c\",d  "          , " Test, a","b","c", "d",null    );
        testFormatConfig( "\" Test, a\" ,b, \"c,d\"  "          , " Test, a","b","c,d",null,null  );
    }


    /** ********************************************************************************************
     *     Log_TextLoggerTimeDiff
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void Log_TextLoggerTimeDiff()
    {
        UT_INIT();

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


    /** ****************************************************************************************
     *     Log_LineFormat
     ******************************************************************************************/
    @Test
    public void Log_LineFormat()
    {
        UT_INIT();

        Log.addDebugLogger();
        MemoryLogger testML= new MemoryLogger();
        Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, "/FMT");
        Log.setVerbosity( testML,          Verbosity.VERBOSE, "/FMT");

        Log.setDomain( "FMT", Scope.METHOD );

        Log.info( "This is the default ConsoleLogger log line" );
        AutoSizes backup= Log.debugLogger.autoSizes;
        Log.debugLogger.autoSizes= new AutoSizes();

        AString  lf;
        lf= new AString( "(%SF) %SP.%SL.%SM():%A3[%D][%TD][%TC +%TL][%tN]%V[%D]<%#>: ");    Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(     "(%SF) %SP.%SM():%A3[%D][%TD][%TC +%TL][%tN]%V[%D]<%#>: ");    Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%D][%TD][%TC +%TL][%tN]%V[%D]<%#>: ");    Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%TD][%TC +%TL][%tN]%V[%D]<%#>: ");        Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%TC +%TL][%tN]%V[%D]<%#>: ");             Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[+%TL][%tN]%V[%D]<%#>: ");                 Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%tN]%V[%D]<%#>: ");                       Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3 %V[%D]<%#>: ");                           Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%D]<%#>: ");                              Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%D]: ");                                  Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF):%A3[%D]: ");                                        Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "[%D]: ");                                                         Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "");                                                               Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );

        Log.debugLogger.metaInfo.format._()._( "%TD@" );
        testML.metaInfo.format._()._( "%TD@" );
        String df;
        df= ">yy-MM-dd<";    Log.debugLogger.metaInfo.dateFormat= df;                                              Log.info( "Date test. Format: \""+ df + '\"' );
        testML.memoryLog.clear();
        df= ">yyyy/dd/MM<";  Log.debugLogger.metaInfo.dateFormat= df;  testML.metaInfo.dateFormat= df;             Log.info( "FMT", "Date test. Format: \""+ df + '\"' );
        UT_TRUE( testML.memoryLog.searchAndReplace( '/', '@') == 4 );
        Log.debugLogger.metaInfo.format._()._( "%TT@" );
        testML.metaInfo.format._()._( "%TT@" );
        df= ">HH:mm:ss<";    Log.debugLogger.metaInfo.timeOfDayFormat= df;                                         Log.info( "FMT", "Time of day test Format: \""+ df + '\"' );
        testML.memoryLog.clear();
        df= ">HH-mm-ss<";    Log.debugLogger.metaInfo.timeOfDayFormat= df;  testML.metaInfo.timeOfDayFormat= df;   Log.info( "FMT", "Time of day test. Format: \"" + df + '\"' );
        UT_TRUE( testML.memoryLog.searchAndReplace( '-', '@') == 4 );

        Log.debugLogger.metaInfo.format._( "%tI@" );
        testML.metaInfo.format._()._( "%tI@" );
        testML.memoryLog.clear();
        testML.autoSizes.reset();
        Log.info("");
        UT_TRUE( testML.memoryLog.equals( "1@") );


        Log.debugLogger.metaInfo.format._()._( "%P" );
                 testML.metaInfo.format._()._( "%P" );
        testML.memoryLog.clear(); testML.autoSizes.reset(); Log.info("");
        UT_TRUE(    testML.memoryLog.equals("RemoteTestRunner"  )  // eclipse
                 || testML.memoryLog.equals("AppMain"           )  // intellij old?
                 || testML.memoryLog.equals("JUnitStarter"      )  // intellij
            );

        Log.debugLogger.metaInfo.format._()._( "%LX" );
                 testML.metaInfo.format._()._( "%LX" );
        testML.memoryLog.clear(); testML.autoSizes.reset(); Log.info("");  UT_EQ( "LOG"     ,testML.memoryLog );

        Log.debugLogger.metaInfo.format._()._( "%LG" );
                 testML.metaInfo.format._()._( "%LG" );
        testML.memoryLog.clear(); testML.autoSizes.reset(); Log.info("");  UT_EQ( "MEMORY"  , testML.memoryLog );


        Log.debugLogger.autoSizes= backup;
    }

    /** ****************************************************************************************
     *     Log_Multiline.
     ******************************************************************************************/
    @Test
    public void Log_Multiline()
    {
        UT_INIT();

        Log.addDebugLogger();
        Log.setDomain( "MLine", Scope.METHOD );

        Log.debugLogger.multiLineMsgMode= 0;
        Log.info( "" );
        Log.info( "-------- ML Mode = 0 (single line) --------" );
        Log.state( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 0;
        Log.debugLogger.multiLineDelimiterRepl= "~|~";
        Log.info( "" );
        Log.info( "-------- ML Mode = 0 (single line) with delimiter replacement set to ~|~ --------" );
        Log.state( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 0;
        Log.debugLogger.multiLineDelimiter= "";
        Log.info( "" );
        Log.info( "-------- ML Mode = 0 (single line) with delimiter set to \"\" (stops multi line processing) --------" );
        Log.state( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 1;
        Log.info( "" );
        Log.info( "-------- ML Mode = 1 (multi line, all meta info per line) --------" );
        Log.state( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 2;
        Log.info( "" );
        Log.info( "-------- ML Mode = 2 (multi line, meta info blanked) --------" );
        Log.state( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 3;
        Log.info( "" );
        Log.info( "-------- ML Mode = 3 (multi line, print headline with info, text starts at pos 0) --------" );
        Log.state( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 4;
        Log.info( "" );
        Log.info( "-------- ML Mode = 4 (pure multi line, no meta info, no headline, starts at pos 0)) --------" );
        Log.state( "MLine", Verbosity.INFO, "Our Log configuration is:" );
    }


    /** ****************************************************************************************
     *     Log_Recursive.
     ******************************************************************************************/
    @Test
    public void Log_Recursive()
    {
        UT_INIT();

        Log.setDomain( "RECURSION", Scope.METHOD );
        MemoryLogger testML= new MemoryLogger();
        Log.setVerbosity( testML , Verbosity.VERBOSE);

        // tests without the use of the formatter when logging recursively
        {
            int oldCntLogs= testML.cntLogs;
            (new ApplyLog("Test", 1)).toString ();
            UT_TRUE( testML.memoryLog.indexOf( "Logging object >Test<")  > 0 );
            UT_EQ( 1, testML.cntLogs - oldCntLogs );
            testML.memoryLog.clear();

            oldCntLogs= testML.cntLogs;
            Log.info( "outer>{}<log", new ApplyLog("Test", 1) );
            UT_EQ( 2, testML.cntLogs - oldCntLogs );
//UT_PRINT("--->>> MemLog:" + CString.NEW_LINE_CHARS + testML.memoryLog.toString() + CString.NEW_LINE_CHARS + "----<<<" );
            UT_TRUE( testML.memoryLog.indexOf( "outer>Test<log")  > 0 );
            testML.memoryLog.clear();


            oldCntLogs= testML.cntLogs;
            Log.info( "123{:^8}456--abc{!UP}efg", new ApplyLog("Test", 1), new ApplyLog("lowerTest", 1) );
            UT_EQ( 3, testML.cntLogs - oldCntLogs );
            UT_TRUE( testML.memoryLog.indexOf( "123  Test  456"     )  > 0 );
            UT_TRUE( testML.memoryLog.indexOf( "abcLOWERTESTefg")  > 0 );
        }

        // same tests, now using formatter recursively
        {
            int oldCntLogs= testML.cntLogs;
            (new ApplyLog("Test", 2)).toString ();
            UT_TRUE( testML.memoryLog.indexOf( "Logging object >Test<")  > 0 );
            UT_EQ( 1, testML.cntLogs - oldCntLogs );
            testML.memoryLog.clear();

            oldCntLogs= testML.cntLogs;
            Log.info( "outer>{}<log", new ApplyLog("Test", 2) );
            UT_EQ( 2, testML.cntLogs - oldCntLogs );
//UT_PRINT("--->>> MemLog:" + CString.NEW_LINE_CHARS + testML.memoryLog.toString() + CString.NEW_LINE_CHARS + "----<<<" );
            UT_TRUE( testML.memoryLog.indexOf( "outer>Test<log")  > 0 );
            testML.memoryLog.clear();


            oldCntLogs= testML.cntLogs;
            Log.info( "123{:^8}456--abc{!UP}efg", new ApplyLog("Test", 2), new ApplyLog("lowerTest", 2) );
            UT_EQ( 3, testML.cntLogs - oldCntLogs );
            UT_TRUE( testML.memoryLog.indexOf( "123  Test  456"     )  > 0 );
            UT_TRUE( testML.memoryLog.indexOf( "abcLOWERTESTefg")  > 0 );
        }


        Log.removeLogger( testML );
    }

}
