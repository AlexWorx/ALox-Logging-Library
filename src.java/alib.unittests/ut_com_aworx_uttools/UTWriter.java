// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_aworx_uttools;


import com.aworx.lib.Report;
import com.aworx.lib.ReportWriter;
import com.aworx.lib.enums.Phase;
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
        lox.omittablePackagePrefixes.add( "ut_com_aworx_uttools" );
            
        logger= Lox.createConsoleLogger( "UT ALib ReportWriter" );

        lox.setVerbosity( logger, Verbosity.VERBOSE,  "/UT" );
        lox.setVerbosity( logger, Verbosity.VERBOSE,  ALox.INTERNAL_DOMAINS );
        lox.setPrefix( ESC.BG_GRAY, "/" );
        
        Report.getDefault().pushWriter( this );
    }
    
    public void print( Verbosity verbosity, Object msg )
    {
        lox.entry( "UT", verbosity, msg );
    }

    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    @Override
    public void NotifyActivation( Phase phase )
    {
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

