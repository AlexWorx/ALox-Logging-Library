// #################################################################################################
//  ut_com_aworx - AWorx Unit Test Support using ALib and ALox
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
//
//  Relies on ALox logging library, which in turn relies on ALib. Hence, ALibs' unit
//  tests can only be compiled if ALox library is present.
// #################################################################################################
package ut_com_aworx;


import com.aworx.lib.lang.Phase;
import com.aworx.lib.lang.Report;
import com.aworx.lib.lang.ReportWriter;
import com.aworx.lox.ALox;
import com.aworx.lox.ESC;
import com.aworx.lox.Lox;
import com.aworx.lox.Verbosity;
import com.aworx.lox.core.textlogger.TextLogger;

/** ****************************************************************************************
 * Used for writing messages is unit tests. Creates an own Lox and adds a text Logger.
 * In addition, implements ALib \b %ReportWriter interface and attaches to ALib.
 *
 * Only one singleton of this class is (and should be) created in class \b UnitTest.
 ******************************************************************************************/
public class UTWriter implements ReportWriter
{
    public Lox          lox;
    public TextLogger   logger;

    public UTWriter()
    {
        lox= new Lox( "UTLox" );
        lox.omittablePackagePrefixes.add( "ut_com_aworx" );

        logger= Lox.createConsoleLogger( "UT ALib ReportWriter" );
logger.metaInfo.format.clear()._( ".(%SF:%SL) %SM():%A5[%TC +%TL][%tN]%V[%D]%A1#%#: " );

        lox.setVerbosity( logger, Verbosity.VERBOSE,  "/UT" );
        lox.setVerbosity( logger, Verbosity.VERBOSE,  ALox.INTERNAL_DOMAINS );
        lox.setPrefix( ESC.BG_GRAY, "/" );

        Report.getDefault().pushWriter( this );
    }

    public void printx( Verbosity verbosity, Object... msgs )
    {
        lox.entry( "UT", verbosity, msgs );
    }

    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    @Override
    public void NotifyActivation( Phase phase )
    {
        /* nothing to do here */
    }

    /** ************************************************************************************
     * Write ALib reports using ALox.
     * @param report The report.
     **************************************************************************************/
    @Override
    public void report  (Report.Message report)
    {
        lox.entry( ALox.INTERNAL_DOMAINS + "UT_REPORT",
                   report.type == 0 ? Verbosity.ERROR       :
                   report.type == 1 ? Verbosity.WARNING     :
                   report.type == 2 ? Verbosity.INFO        :
                                      Verbosity.VERBOSE,
                   report.contents );
    }
}

