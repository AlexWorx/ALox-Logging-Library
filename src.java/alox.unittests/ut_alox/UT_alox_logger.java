// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_alox;

import org.junit.Test;

import ut_com_aworx_uttools.AUnitTest;

import com.aworx.lib.ALIB;
import com.aworx.lib.config.Configuration;
import com.aworx.lib.config.IniFile;
import com.aworx.lib.strings.AString;
import com.aworx.lox.*;
import com.aworx.lox.core.textlogger.MetaInfo;
import com.aworx.lox.core.textlogger.StringConverter;
import com.aworx.lox.loggers.AnsiConsoleLogger;
import com.aworx.lox.loggers.MemoryLogger;


class MyType
{}

class MyObjectConverter implements com.aworx.lox.core.textlogger.ObjectConverter
{
    @Override
    public  boolean convertObject( Object o, AString result )
    {
        if ( o == null )
        {
            result._( "MyObjectConverter: null" );
            return true;
        }

        if ( o instanceof MyType )
        {
            result._( "my type" );
            return true;
        }

        return false;
    }
}
public class UT_alox_logger extends AUnitTest
{

    /** ********************************************************************************************
     *   Log_ObjectConverter
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void Log_ObjectConverter()
    {
        UT_INIT();
    
        Log.addDebugLogger();
    
        Log.setDomain( "OBJECT_CONV",       Scope.METHOD );
        MemoryLogger ml= new MemoryLogger();
        ml.metaInfo.format._();
        Log.setVerbosity( ml, Verbosity.VERBOSE );
    
        StringConverter mainConverter= (StringConverter) ml.objectConverters.get( 0 );
        
        // test without my converter
        MyType mytype= new MyType();
        Log.info( "Test" ); UT_TRUE( ml.memoryLog.indexOf( "Test" ) >= 0 );                          ml.memoryLog._();
        Log.info( null   ); UT_TRUE( ml.memoryLog.indexOf( mainConverter.fmtNullObject ) >= 0 );     ml.memoryLog._();
        Log.info( mytype ); UT_EQ  ( mytype.toString(), ml.memoryLog );                              ml.memoryLog._();
        Log.info( null   ); UT_EQ  ( mainConverter.fmtNullObject, ml.memoryLog );                    ml.memoryLog._();
    
        // test without my converter
                     ml.objectConverters.add( new MyObjectConverter() );
        Log.debugLogger.objectConverters.add( new MyObjectConverter() );
        Log.info( "Test" ); UT_TRUE( ml.memoryLog.indexOf( "Test" ) >= 0 );                          ml.memoryLog._();
        Log.info( null   ); UT_EQ  ( "MyObjectConverter: null" , ml.memoryLog );                     ml.memoryLog._();
        Log.info( mytype ); UT_EQ  ( "my type"                 , ml.memoryLog );                     ml.memoryLog._();
    
        // cleanup
        Log.removeLogger( ml );
        Log.removeDebugLogger();
    }

    /** ********************************************************************************************
     *     Log_ColorsAndStyles
     **********************************************************************************************/
    @SuppressWarnings("static-method")
    @Test
    public void Log_ColorsAndStyles()
    {
        UT_INIT();
        
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
            acl.isBackgroundLight= !acl.isBackgroundLight;
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
        if ( acl!=null )
            acl.isBackgroundLight= !acl.isBackgroundLight;


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
    void testFormatConfig( String testFormat,
                           String expFmt,
                           String expFmtError   ,
                           String expFmtWarning ,
                           String expFmtInfo    ,
                           String expFmtVerbose 
                         )
    {
        IniFile iniFile= new IniFile("*"); // don't read
        iniFile.save( ALox.configCategoryName, "TESTML_FORMAT", testFormat   );
        ALIB.config.insertPlugin( iniFile, Configuration.PRIO_INI_FILE );
        MemoryLogger ml= new MemoryLogger("TESTML");
    
                                     UT_EQ( expFmt, ml.metaInfo.format );
        if( expFmtError  != null ) { UT_EQ( expFmtError  , ml.metaInfo.verbosityError   ); }
        if( expFmtWarning!= null ) { UT_EQ( expFmtWarning, ml.metaInfo.verbosityWarning ); }
        if( expFmtInfo   != null ) { UT_EQ( expFmtInfo   , ml.metaInfo.verbosityInfo    ); }
        if( expFmtVerbose!= null ) { UT_EQ( expFmtVerbose, ml.metaInfo.verbosityVerbose ); }
    
        ALIB.config.removePlugin( iniFile );
    }
    
    
    @SuppressWarnings("static-method")
    @Test
    public void Log_TextLogger_FormatConfig()
    {
        UT_INIT();
    
        testFormatConfig( "Test"                                , "Test"    ,null,null,null,null   );
        testFormatConfig( "\"Test"                              , "\"Test"  ,null,null,null,null   );
        testFormatConfig( "\"Test\""                            , "Test"    ,null,null,null,null   );
        testFormatConfig( "  \" Test  \"  s"                    , " Test  " ,null,null,null,null   );
    
        testFormatConfig( " Test , a ,b, c,d  "                 , "Test", "a","b","c","d"    );
        testFormatConfig( "\" Test, a ,b, c,d  "                , "\" Test", "a","b","c","d" );
        testFormatConfig( "\" Test \", a ,b, c,d  "             , " Test ", "a","b","c","d"  );
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
        com.aworx.lox.core.textlogger.AutoSizes backup= Log.debugLogger.autoSizes;
        Log.debugLogger.autoSizes= new com.aworx.lox.core.textlogger.AutoSizes();

        AString  lf;
        lf= new AString( "(%SF) %SP.%SL.%SM():%A3[%D][%TD][%TC +%TL][%tN]%V[%D]<%#>: ");    Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(     "(%SF) %SP.%SM():%A3[%D][%TD][%TC +%TL][%tN]%V[%D]<%#>: ");    Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%D][%TD][%TC +%TL][%tN]%V[%D]<%#>: ");    Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%TD][%TC +%TL][%tN]%V[%D]<%#>: ");        Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%TC +%TL][%tN]%V[%D]<%#>: ");             Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[+%TL][%tN]%V[%D]<%#>: ");                 Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%tN]%V[%D]<%#>: ");                       Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3 %V[%D]<%#>: ");                          Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%D]<%#>: ");                             Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF) %SM():%A3[%D]: ");                                 Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString(         "(%SF):%A3[%D]: ");                                       Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "[%D]: ");                                                        Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );
        lf= new AString( "");                                                              Log.debugLogger.metaInfo.format= lf;    Log.info( "LineFormat set to= \"" + lf + "\"" );

        Log.debugLogger.metaInfo.format._()._( "%TD@" );
        testML.metaInfo.format._()._( "%TD@" );
        String df;
        df= ">yy-MM-dd<";    Log.debugLogger.metaInfo.dateFormat= df;                                              Log.info( "Date test. Format: \""+ df + '\"' );
        testML.memoryLog.clear();
        df= ">yyyy/dd/MM<";  Log.debugLogger.metaInfo.dateFormat= df;  testML.metaInfo.dateFormat= df;             Log.info( "FMT", "Date test. Format: \""+ df + '\"' );
        UT_TRUE( testML.memoryLog.searchAndReplace( "/", "@") == 4 );
        Log.debugLogger.metaInfo.format._()._( "%TT@" );
        testML.metaInfo.format._()._( "%TT@" );
        df= ">HH:mm:ss<";    Log.debugLogger.metaInfo.timeOfDayFormat= df;                                         Log.info( "FMT", "Time of day test Format: \""+ df + '\"' );
        testML.memoryLog.clear();
        df= ">HH-mm-ss<";    Log.debugLogger.metaInfo.timeOfDayFormat= df;  testML.metaInfo.timeOfDayFormat= df;   Log.info( "FMT", "Time of day test. Format: \"" + df + '\"' );
        UT_TRUE( testML.memoryLog.searchAndReplace( "-", "@") == 4 );

        Log.debugLogger.metaInfo.format._( "%tI@" );
        testML.metaInfo.format._()._( "%tI@" );
        testML.memoryLog.clear();
        testML.autoSizes.reset();
        Log.info("");
        UT_TRUE( testML.memoryLog.equals( "1@") );
        

        Log.debugLogger.metaInfo.format._()._( "%P" );
                 testML.metaInfo.format._()._( "%P" );
        testML.memoryLog.clear(); testML.autoSizes.reset(); Log.info("");  UT_EQ( "RemoteTestRunner" , testML.memoryLog );

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
        Log.logConfig( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 0;
        Log.debugLogger.multiLineDelimiterRepl= "~|~";
        Log.info( "" );
        Log.info( "-------- ML Mode = 0 (single line) with delimiter replacement set to ~|~ --------" );
        Log.logConfig( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 0;
        Log.debugLogger.multiLineDelimiter= "";
        Log.info( "" );
        Log.info( "-------- ML Mode = 0 (single line) with delimiter set to \"\" (stops multi line processing) --------" );
        Log.logConfig( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 1;
        Log.info( "" );
        Log.info( "-------- ML Mode = 1 (multi line, all meta info per line) --------" );
        Log.logConfig( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 2;
        Log.info( "" );
        Log.info( "-------- ML Mode = 2 (multi line, meta info blanked) --------" );
        Log.logConfig( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 3;
        Log.info( "" );
        Log.info( "-------- ML Mode = 3 (multi line, print headline with info, text starts at pos 0) --------" );
        Log.logConfig( "MLine", Verbosity.INFO, "Our Log configuration is:" );

        Log.debugLogger.multiLineMsgMode= 4;
        Log.info( "" );
        Log.info( "-------- ML Mode = 4 (pure multi line, no meta info, no headline, starts at pos 0)) --------" );
        Log.logConfig( "MLine", Verbosity.INFO, "Our Log configuration is:" );
    }

}
