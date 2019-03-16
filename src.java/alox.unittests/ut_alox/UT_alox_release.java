// #################################################################################################
//  Unit Tests - AWorx Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package ut_alox;
import org.junit.Test;

import com.aworx.lox.*;
import com.aworx.lox.detail.textlogger.TextLogger;

import ut_com_aworx.AWorxUnitTesting;


public class UT_alox_release extends AWorxUnitTesting
{
    /** ********************************************************************************************
     *     Log_LogLevelSetting
     **********************************************************************************************/
    @Test
    public void Log_LogLevelSetting()
    {
        UT_INIT();

        //new UnitTests();
        Lox lox= new Lox( "ReleaseLox" );
        TextLogger logger= Lox.createConsoleLogger( null );
        lox.setDomain( "TLLS_DF", Scope.METHOD );

        // Test Verbosity setting
        int logLinesBefore= logger.cntLogs;
        lox.setVerbosity( logger, Verbosity.VERBOSE, "" );
        lox.verbose  (         "This Verbose line should be logged" );
        lox.info     (         "This Info    line should be logged" );
        lox.warning  (         "This WARN    line should be logged" );
        lox.error    (         "This Error   line should be logged" );

        lox.setVerbosity( logger,  Verbosity.INFO, "" );
        lox.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     (         "This Info    line should be logged" );
        lox.warning  (         "This Warning line should be logged" );
        lox.error    (         "This Error   line should be logged" );

        lox.setVerbosity( logger, Verbosity.WARNING, "" );
        lox.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  (         "This Warning line should be logged" );
        lox.error    (         "This Error   line should be logged" );

        lox.setVerbosity( logger, Verbosity.ERROR, "" );
        lox.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.error    (         "This Error   line should be logged" );

        lox.setVerbosity( logger, Verbosity.OFF, "" );
        lox.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.error    (         "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );


        lox.setVerbosity( logger, Verbosity.VERBOSE, "/TLLS" );
        lox.verbose  ( "/TLLS", "This Verbose line should be logged" );
        lox.info     ( "/TLLS", "This Info    line should be logged" );
        lox.warning  ( "/TLLS", "This WARN    line should be logged" );
        lox.error    ( "/TLLS", "This Error   line should be logged" );

        lox.setVerbosity( logger, Verbosity.INFO, "/TLLS" );
        lox.verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     ( "/TLLS", "This Info    line should be logged" );
        lox.warning  ( "/TLLS", "This Warning line should be logged" );
        lox.error    ( "/TLLS", "This Error   line should be logged" );

        lox.setVerbosity( logger, Verbosity.WARNING, "/TLLS" );
        lox.verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  ( "/TLLS", "This Warning line should be logged" );
        lox.error    ( "/TLLS", "This Error   line should be logged" );

        lox.setVerbosity( logger, Verbosity.ERROR, "/TLLS" );
        lox.verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  ( "/TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.error    ( "/TLLS", "This Error   line should be logged" );

        lox.setVerbosity( logger, Verbosity.OFF, "/TLLS" );
        lox.verbose  ( "/TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     ( "/TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  ( "/TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.error    ( "/TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        UT_EQ( 20, logger.cntLogs - logLinesBefore );

        // cleanup
        lox.removeLogger( logger );
    }


}
