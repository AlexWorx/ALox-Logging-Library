// #################################################################################################
//  Unit Tests - AWorx Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package ut_alox;
import org.junit.Test;

import com.aworx.lib.ALIB;
import com.aworx.lib.config.Configuration;
import com.aworx.lib.config.Variable;
import com.aworx.lib.lang.Inclusion;
import com.aworx.lib.lang.Safeness;
import com.aworx.lox.ALox;
import com.aworx.lox.ESC;
import com.aworx.lox.Log;
import com.aworx.lox.Lox;
import com.aworx.lox.Scope;
import com.aworx.lox.Verbosity;
import com.aworx.lox.loggers.ConsoleLogger;
import com.aworx.lox.loggers.MemoryLogger;

import ut_com_aworx.AWorxUnitTesting;




public class UT_alox_lox  extends AWorxUnitTesting
{
    /** ****************************************************************************************
     *  Lox_AddLogger.
     ******************************************************************************************/
    @Test
    public void Lox_AddLogger()
    {
        UT_INIT();

        // twice
        {
            ConsoleLogger con=      new ConsoleLogger();
            Log.setVerbosity( con,      Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS );

            MemoryLogger checkCnt=  new MemoryLogger( "CHECK");
            Log.setVerbosity( checkCnt, Verbosity.WARNING, ALox.INTERNAL_DOMAINS );

            MemoryLogger mem1= new MemoryLogger( "MEM" );
            MemoryLogger mem2= new MemoryLogger( "MEM" );

            int checkVal= 0;
            Log.setVerbosity( mem1,     Verbosity.INFO ); UT_EQ( checkVal+= 0, checkCnt.cntLogs );
            Log.setVerbosity( mem2,     Verbosity.INFO ); UT_EQ( checkVal+= 1, checkCnt.cntLogs );
            Log.setVerbosity( "XYZ",    Verbosity.INFO ); UT_EQ( checkVal+= 1, checkCnt.cntLogs );

            // get unknown
            Log.getLogger(  "XYZ" );                      UT_EQ( checkVal+= 1, checkCnt.cntLogs );

            Log.removeLogger( mem2     );                 UT_EQ( checkVal+= 1, checkCnt.cntLogs );
            Log.removeLogger( mem1     );                 UT_EQ( checkVal+= 0, checkCnt.cntLogs );
            Log.removeLogger( mem1     );                 UT_EQ( checkVal+= 1, checkCnt.cntLogs );
            Log.removeLogger( "XYZ"    );                 UT_EQ( checkVal+= 1, checkCnt.cntLogs );
            Log.removeLogger( con      );                 UT_EQ( checkVal+= 0, checkCnt.cntLogs );
            Log.removeLogger( con      );                 UT_EQ( checkVal+= 1, checkCnt.cntLogs );
            Log.removeLogger( checkCnt );                 UT_EQ( checkVal+= 0, checkCnt.cntLogs );
        }

        // one logger in two loxes
        {

            Log.addDebugLogger();
            Lox lox= new Lox( "ReleaseLox" );

            UT_TRUE( Log.debugLogger.getSafeness() == Safeness.UNSAFE );

            lox.setVerbosity( Log.debugLogger , Verbosity.VERBOSE );

            UT_TRUE( Log.debugLogger.getSafeness() == Safeness.SAFE );

            lox.removeLogger( Log.debugLogger );

            UT_TRUE( Log.debugLogger.getSafeness() == Safeness.UNSAFE );

            Log.removeDebugLogger();
        }
    }

    /** ********************************************************************************************
     * Lox_LogLevelSetting
     **********************************************************************************************/
    @Test
    public void Lox_LogLevelSetting()
    {
        UT_INIT();
        Log.addDebugLogger();
        Log.setDomain( "TLLS_DF", Scope.METHOD );
        Log.setVerbosity( Log.debugLogger, Verbosity.OFF, ALox.INTERNAL_DOMAINS );

        // Test Verbosity setting
        int logLinesBefore= Log.debugLogger.cntLogs;
        Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, "" );
        Log.verbose  (         "This Verbose line should be logged" );
        Log.info     (         "This Info    line should be logged" );
        Log.warning  (         "This WARN    line should be logged" );
        Log.error    (         "This Error   line should be logged" );

        Log.setVerbosity( Log.debugLogger, Verbosity.INFO, "" );
        Log.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     (         "This Info    line should be logged" );
        Log.warning  (         "This Warning line should be logged" );
        Log.error    (         "This Error   line should be logged" );

        Log.setVerbosity( Log.debugLogger, Verbosity.WARNING, "" );
        Log.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  (         "This Warning line should be logged" );
        Log.error    (         "This Error   line should be logged" );

        Log.setVerbosity( Log.debugLogger, Verbosity.ERROR, "" );
        Log.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.error    (         "This Error   line should be logged" );

        Log.setVerbosity( Log.debugLogger, Verbosity.OFF, "" );
        Log.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.error    (         "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );

        Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, "/TLLS" );
        Log.verbose  ( "/TLLS", "This Verbose line should be logged" );
        Log.info     ( "/TLLS", "This Info    line should be logged" );
        Log.warning  ( "/TLLS", "This WARN    line should be logged" );
        Log.error    ( "/TLLS", "This Error   line should be logged" );

        Log.setVerbosity( Log.debugLogger, Verbosity.INFO, "/TLLS" );
        Log.verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     ( "/TLLS", "This Info    line should be logged" );
        Log.warning  ( "/TLLS", "This Warning line should be logged" );
        Log.error    ( "/TLLS", "This Error   line should be logged" );

        Log.setVerbosity( Log.debugLogger, Verbosity.WARNING, "/TLLS" );
        Log.verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  ( "/TLLS", "This Warning line should be logged" );
        Log.error    ( "/TLLS", "This Error   line should be logged" );

        Log.setVerbosity( Log.debugLogger, Verbosity.ERROR, "/TLLS" );
        Log.verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  ( "/TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.error    ( "/TLLS", "This Error   line should be logged" );

        Log.setVerbosity( Log.debugLogger, Verbosity.OFF, "/TLLS" );
        Log.verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.warning  ( "/TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        Log.error    ( "/TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        UT_EQ( 20, Log.debugLogger.cntLogs - logLinesBefore );
    }

    /** ********************************************************************************************
     *     Lox_ScopeDomain
     **********************************************************************************************/
    @Test
    public void Lox_SimpleScopeDomain()
    {
        UT_INIT();

        int cntLL;
        Log.setDomain( "REPLACED", Scope.METHOD );
        Log.setDomain( "DFLT",     Scope.METHOD );
        MemoryLogger ml= new MemoryLogger();
        Log.info( "***Log_SimpleScopeDomain***" );


        String testOK=  "OK";
        String testERR= "Error";

        // Test Verbosity setting
        Log.setVerbosity( Log.debugLogger, Verbosity.WARNING,  "" );
        cntLL= Log.debugLogger.cntLogs;    Log.info      ( testERR );    UT_EQ ( 0, Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.warning   ( testOK  );    UT_EQ ( 1, Log.debugLogger.cntLogs - cntLL );

        Log.setVerbosity( Log.debugLogger, Verbosity.ERROR, "/" );
        cntLL= Log.debugLogger.cntLogs;    Log.warning   ( testERR );    UT_EQ ( 0, Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.error     ( testOK  );    UT_EQ ( 1, Log.debugLogger.cntLogs - cntLL );


        // test sub domains
        Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, "/test" );
        Log.state( "/TEST",   Verbosity.INFO, "Dumping Log Configuration:" );

        Log.setVerbosity( Log.debugLogger, Verbosity.INFO,   "/DFLT"      );
        Log.setVerbosity( Log.debugLogger, Verbosity.WARNING     ,   "/DFLT/WARN" );
        Log.setVerbosity( Log.debugLogger, Verbosity.ERROR                  ,         "ERR"  );
        Log.setVerbosity( ml             , Verbosity.INFO,   "/DFLT"      );
        Log.setVerbosity( ml             , Verbosity.WARNING     ,   "/DFLT/WARN" );
        Log.setVerbosity( ml             , Verbosity.ERROR                  ,         "ERR"  );


        Log.state( "/TEST",  Verbosity.INFO, "Dumping Log Configuration:" );

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

        // log without leading "/" on domain (of-course, this is quite an error of using ALox)
        cntLL= ml.cntLogs;    Log.verbose    ( "DFLT",         testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "DFLT/ERR",     testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "DFLT/WARN",    testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.info       ( "DFLT",         testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "DFLT/ERR",     testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "DFLT/WARN",    testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.warning    ( "DFLT",         testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "DFLT/WARN",    testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "DFLT/ERR",     testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.error      ( "DFLT",         testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "DFLT/WARN",    testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "DFLT/ERR",     testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );


        // relative addressing with "~"domain
        cntLL= ml.cntLogs;    Log.verbose    (                 testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "",             testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "ERR",          testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.verbose    ( "WARN",         testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.info       (                 testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "",             testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "ERR",          testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.info       ( "WARN",         testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.warning    (                 testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "",             testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "WARN",         testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.warning    ( "ERR",          testERR );    UT_EQ ( 0, ml.cntLogs - cntLL );

        cntLL= ml.cntLogs;    Log.error      (                 testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "",             testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "WARN",         testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );
        cntLL= ml.cntLogs;    Log.error      ( "ERR",          testOK  );    UT_EQ ( 1, ml.cntLogs - cntLL );

        Log.removeLogger( ml );
    }

    /** ****************************************************************************************
     *     Lox_AssertAndIf
     ******************************************************************************************/
    @Test
    public void Lox_AssertAndIf()
    {
        UT_INIT();

        Log.addDebugLogger();
        Log.setDomain( "ASSERT", Scope.METHOD );

        String testOK=  "OK";
        String testERR= "Error";

        // Test Verbosity setting
        int cntLL= Log.debugLogger.cntLogs;
        Log.setVerbosity( Log.debugLogger, Verbosity.INFO, "/");

        cntLL= Log.debugLogger.cntLogs;    Log.Assert( true,  "/ASSERT",                 testERR ); UT_EQ ( 0,  Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.Assert( false, "/ASSERT",                 testOK  ); UT_EQ ( 1,  Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.Assert( true,                             testERR ); UT_EQ ( 0,  Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.Assert( false,                            testOK  ); UT_EQ ( 1,  Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.If    ( true,  "/ASSERT", Verbosity.INFO, testERR ); UT_EQ ( 1,  Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.If    ( false, "/ASSERT", Verbosity.INFO, testOK  ); UT_EQ ( 0,  Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.If    ( true,             Verbosity.INFO, testERR ); UT_EQ ( 1,  Log.debugLogger.cntLogs - cntLL );
        cntLL= Log.debugLogger.cntLogs;    Log.If    ( false,            Verbosity.INFO, testOK  ); UT_EQ ( 0,  Log.debugLogger.cntLogs - cntLL );

    }


    /** ****************************************************************************************
     *     Lox_Threads
     ******************************************************************************************/
    @Test
    public void Lox_Threads()
    {
        UT_INIT();

        Log.addDebugLogger();
        Log.setDomain ( "TEST/THREAD1", Scope.METHOD );

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
            Log.setDomain ( "TEST/THREAD2", Scope.METHOD );
            Log.setVerbosity ( Log.debugLogger, Verbosity.VERBOSE, "TEST/THREAD2" );

            for ( int i= 0 ; i < 20 ; i++ )
            {
                Log.info( "This is a different Thread. Cnt= " + i );
                ALIB.sleepMillis( 3 );
            }
        }
    }

    /** ********************************************************************************************
     * Log_MultipleLogables
     **********************************************************************************************/
    @Test @SuppressWarnings ("boxing")
    public void Log_MultipleLogables()
    {
        UT_INIT();

        Log.addDebugLogger();
        MemoryLogger memLogger= new MemoryLogger();
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );

        Object[] logables= { "First, ", "second, ", 3 };

        //---- Log.Info -----
        memLogger.memoryLog.clear();
        Log.info( logables );
        UT_TRUE( memLogger.memoryLog.indexOf( "First, second, 3" ) > 0 );

        //---- Log.Once -----
        memLogger.memoryLog.clear();
        Log.once( logables );
        UT_TRUE( memLogger.memoryLog.indexOf( "First, second, 3" ) > 0 );

        memLogger.memoryLog.clear();
//! [DOX_ALOX_LOX_ONCE]
Log.once( new Object[] {"One - {} - {}!", "two", 3}  );
//! [DOX_ALOX_LOX_ONCE]
        UT_TRUE( memLogger.memoryLog.indexOf( "One - two - 3" ) > 0 );

    }

    /** ****************************************************************************************
     *     Log_GetState
     ******************************************************************************************/
    @Test
    public void Log_GetState()
    {
        UT_INIT();

        Log.addDebugLogger();
        MemoryLogger memLogger= new MemoryLogger();

        // reduce meta information to limit output width
        Log.debugLogger.metaInfo.format._()._( "[%tN]%V[%D](%#): " );
        memLogger.metaInfo.format._()._(       "[%tN]%V[%D](%#): " );
        memLogger.multiLineMsgMode= 3;
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );

        // OK, let's use ALox
        Log.setDomain( "PNS"   ,   Scope.PACKAGE, 1 );
        Log.setDomain( "PATH",     Scope.PACKAGE );
        Log.setDomain( "FN",       Scope.CLASS );
        Log.setDomain( "THREAD",   Scope.THREAD_OUTER );

        Log.setVerbosity( "MEMORY",        Verbosity.OFF      , "/CON"    );
        Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.VERBOSE              );
        Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.OFF      , "/MEM"    );
        Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.ERROR    , "/UI"     );
        Log.setVerbosity( "DEBUG_LOGGER" , Verbosity.INFO     , "/UI/DLG" );

        Log.info( "This goes to both loggers" );
        Log.info( "/MEM", "This goes only to the memory logger" );
        Log.info( "/CON", "This goes only to the console logger" );

        Log.once( "Will we see this in the config?" );
        Log.once( null, Verbosity.INFO, "Will we see this in the config?", "ONCEKEY", Scope.CLASS );

        Log.store( "MyData 1", Scope.METHOD );
        Log.store( "MyData 2", "DataKey", Scope.METHOD );
        Log.store( 3         , "DataKey", Scope.CLASS );
        Log.store( 4         , "DataKey", Scope.THREAD_OUTER );

        Log.setPrefix( "TPre: "  , Scope.THREAD_OUTER );
        Log.setPrefix( "MPre: "  , Scope.METHOD );
        Log.setPrefix( "DomPre: " );
        Log.setPrefix( "Mouse: ", "/UI/MOUSE" );
        Log.setPrefix( ESC.RED,  "/ERRORS", Inclusion.EXCLUDE );

        Log.mapThreadName( "TUTORIAL" );

        // now, log the current config
        Log.state( null, Verbosity.INFO, "State(ALL):" );

        Log.state( null, Verbosity.INFO, "State(Domains):", Lox.STATE_INFO_DOMAINS );
        Log.state( null, Verbosity.INFO, "State(Loggers):", Lox.STATE_INFO_LOGGERS );


        // cleanup
        Log.removeDebugLogger();
        Log.removeLogger( memLogger );
    }

    /** ********************************************************************************************
     * Log_DumpStateOnExit
     **********************************************************************************************/
    @Test
    public void Log_DumpStateOnExit()
    {
        UT_INIT();

        Log.addDebugLogger();
        MemoryLogger memLogger= new MemoryLogger();


        Log.setVerbosity( memLogger, Verbosity.VERBOSE );
        UT_TRUE( Log.debugLogger.cntLogs == 0 );
        Log.removeLogger( memLogger );
        UT_TRUE( Log.debugLogger.cntLogs == 0 );

        Variable var= new Variable( ALox.configCategoryName, Log.LOX.getName() + "_DUMP_STATE_ON_EXIT",  ',' );
        int cntLogs;


        var.store( "domain=/TEST, verbosity = e, domains, basic" );

        var.store("domain=/TEST, verbosity = e, sptr, basic" );
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );
        cntLogs= Log.debugLogger.cntLogs;
        Log.removeLogger( memLogger );
        UT_TRUE( Log.debugLogger.cntLogs > cntLogs );

        var.store("verbosity = e, domains, basic" );
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );
        cntLogs= Log.debugLogger.cntLogs;
        Log.removeLogger( memLogger );
        UT_TRUE( Log.debugLogger.cntLogs > cntLogs );

        var.store("domains, loggers" );
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );
        cntLogs= Log.debugLogger.cntLogs;
        Log.removeLogger( memLogger );
        UT_TRUE( Log.debugLogger.cntLogs > cntLogs );

        var.store("" );
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );
        cntLogs= Log.debugLogger.cntLogs;
        Log.removeLogger( memLogger );
        UT_TRUE( Log.debugLogger.cntLogs == cntLogs );


        Log.removeDebugLogger();
    }

    /** ********************************************************************************************
     * Log_WriteVerbosities
     **********************************************************************************************/
    @Test
    public void Log_WriteVerbosities()
    {
        UT_INIT();

        Log.addDebugLogger();
        MemoryLogger memLogger= new MemoryLogger( "MYLGGR" );

        Variable var= new Variable( ALox.configCategoryName, Log.LOX.getName() + "_MYLGGR_VERBOSITY",  ';' );
        Variable varBack= new Variable();

        Log.setVerbosity( Log.debugLogger, Verbosity.VERBOSE, ALox.INTERNAL_DOMAINS);

        // test writing into other variable with variable name error
        UT_PRINT( "An error message should follow (wrong variable format): " );
        var.store("writeback MY_" );
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );
        Log.removeLogger( memLogger );

        // test writing into other variable
        var.store("writeback MY_VAR" );
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );
        Log.removeLogger( memLogger );
        varBack.define( "MY",  "VAR" ).load();
        UT_PRINT(  "Variable written: ", varBack.getString() );
        UT_TRUE( varBack.getString().length() > 0 );

        // test writing into other variable without cat
        var.store("writeback ANON" );
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );
        Log.removeLogger( memLogger );
        varBack.define( "",  "ANON" ).load();
        UT_PRINT(  "Variable written: ", varBack.getString() );
        UT_TRUE( varBack.getString().length() > 0 );

        // test writing into other variable without cat and with underscores in name
        var.store("writeback _2ND_ANON" );
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );
        Log.removeLogger( memLogger );
        varBack.define( "",  "2ND_ANON" ).load();
        UT_PRINT(  "Variable written: ", varBack.getString() );
        UT_TRUE( varBack.getString().length() > 0 );

        // test writing into other the variable itself
        var.store("writeback" );
        Log.setVerbosity( memLogger, Verbosity.VERBOSE );
        Log.removeLogger( memLogger );

        Configuration.Default.load( var );
        UT_PRINT(  "Variable written: ", varBack.getString() );
        UT_TRUE( var.getString().length() > 0 );

       Log.removeDebugLogger();
    }

}
