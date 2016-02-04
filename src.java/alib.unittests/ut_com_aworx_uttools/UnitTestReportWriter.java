// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_aworx_uttools;


import com.aworx.lib.Report;
import com.aworx.lib.ReportWriter;
import com.aworx.lox.Lox;

/** ****************************************************************************************
 *  The \b %ReportWriter for unit tests using AWorx Libraries
 ******************************************************************************************/
public class UnitTestReportWriter implements ReportWriter
{
    public Lox     lox= new Lox();

    public void print( int level, String msg )
    {
             if ( level == 0 )  lox.info    ( "UT", msg );
        else if ( level == 1 )  lox.warning ( "UT", msg );
        else                    lox.error   ( "UT", msg );
    }

    /** ************************************************************************************
     * Write ALib reports using ALox.
     * @param report The report.
     **************************************************************************************/
    @Override
    public void report  (Report.Message report)
    {
        if ( report.type == 0 )
            lox.error   ( "UT_REP", report.contents );
        else
            lox.warning ( "UT_REP", report.contents );
    }
}

