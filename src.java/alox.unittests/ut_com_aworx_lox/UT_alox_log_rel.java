// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_aworx_lox;
import org.junit.Test;

import ut_com_aworx_uttools.UnitTest;

import com.aworx.lox.*;
import com.aworx.lox.core.textlogger.TextLogger;



public class UT_alox_log_rel extends UnitTest
{
    /** ********************************************************************************************
     *     Log_TestLogLevelSetting
     **********************************************************************************************/
    @Test
    public void Log_TestLogLevelSetting()
    {
        //new UnitTests();
        Lox lox= new Lox();
        TextLogger logger= Lox.createConsoleLogger( null );
        lox.addLogger( logger );
        lox.setDomain( "TLLS_DF", Log.Scope.METHOD );
        lox.setDomain( lox.internalDomain, Log.DomainLevel.OFF );

        // Test log level setting
        int logLinesBefore= logger.cntLogs;
        lox.setDomain( "TLLS_DF", Log.DomainLevel.ALL );
        lox.verbose  (         "This Verbose line should be logged" );
        lox.info     (         "This Info    line should be logged" );
        lox.warning  (         "This WARN    line should be logged" );
        lox.error    (         "This Error   line should be logged" );
        lox.verbose  (         "(Indented) This Verbose line should be logged", 1 );
        lox.info     (         "(Indented) This Info    line should be logged", 1 );
        lox.warning  (         "(Indented) This WARN    line should be logged", 1 );
        lox.error    (         "(Indented) This Error   line should be logged", 1 );

        lox.setDomain( "TLLS_DF", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
        lox.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     (         "This Info    line should be logged" );
        lox.warning  (         "This Warning line should be logged" );
        lox.error    (         "This Error   line should be logged" );
        lox.verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.info     (         "(Indented) This Info    line should be logged", 1 );
        lox.warning  (         "(Indented) This Warning line should be logged", 1 );
        lox.error    (         "(Indented) This Error   line should be logged", 1 );


        lox.setDomain( "TLLS_DF", Log.DomainLevel.WARNINGS_AND_ERRORS );
        lox.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  (         "This Warning line should be logged" );
        lox.error    (         "This Error   line should be logged" );
        lox.verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.warning  (         "(Indented) This Warning line should be logged", 1 );
        lox.error    (         "(Indented) This Error   line should be logged", 1 );

        lox.setDomain( "TLLS_DF", Log.DomainLevel.ERRORS );
        lox.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.error    (         "This Error   line should be logged" );
        lox.verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.error    (         "(Indented) This Error   line should be logged", 1 );

        lox.setDomain( "TLLS_DF", Log.DomainLevel.OFF );
        lox.verbose  (         "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     (         "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  (         "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.error    (         "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.verbose  (         "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     (         "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  (         "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.error    (         "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!" );


        lox.setDomain( "TLLS", Log.DomainLevel.ALL );
        lox.verbose  ( "TLLS", "This Verbose line should be logged" );
        lox.info     ( "TLLS", "This Info    line should be logged" );
        lox.warning  ( "TLLS", "This WARN    line should be logged" );
        lox.error    ( "TLLS", "This Error   line should be logged" );
        lox.verbose  ( "TLLS", "(Indented) This Verbose line should be logged", 1 );
        lox.info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        lox.warning  ( "TLLS", "(Indented) This WARN    line should be logged", 1 );
        lox.error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        lox.setDomain( "TLLS", Log.DomainLevel.INFO_WARNINGS_AND_ERRORS );
        lox.verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     ( "TLLS", "This Info    line should be logged" );
        lox.warning  ( "TLLS", "This Warning line should be logged" );
        lox.error    ( "TLLS", "This Error   line should be logged" );
        lox.verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.info     ( "TLLS", "(Indented) This Info    line should be logged", 1 );
        lox.warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        lox.error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );


        lox.setDomain( "TLLS", Log.DomainLevel.WARNINGS_AND_ERRORS );
        lox.verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  ( "TLLS", "This Warning line should be logged" );
        lox.error    ( "TLLS", "This Error   line should be logged" );
        lox.verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.warning  ( "TLLS", "(Indented) This Warning line should be logged", 1 );
        lox.error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        lox.setDomain( "TLLS", Log.DomainLevel.ERRORS );
        lox.verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.error    ( "TLLS", "This Error   line should be logged" );
        lox.verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!", 1 );
        lox.error    ( "TLLS", "(Indented) This Error   line should be logged", 1 );

        lox.setDomain( "TLLS", Log.DomainLevel.OFF );
        lox.verbose  ( "TLLS", "This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     ( "TLLS", "This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  ( "TLLS", "This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.error    ( "TLLS", "This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.verbose  ( "TLLS", "(Indented) This Verbose line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.info     ( "TLLS", "(Indented) This Info    line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.warning  ( "TLLS", "(Indented) This Warning line should NOT be logged. !!!!!Test Error!!!!!" );
        lox.error    ( "TLLS", "(Indented) This Error   line should NOT be logged. !!!!!Test Error!!!!!" );
        UT_EQ( 40, logger.cntLogs - logLinesBefore );
    }

  
}
