// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

import com.aworx.lib.Report;
import com.aworx.lib.ReportWriter;
import com.aworx.lib.enums.Phase;

/** ************************************************************************************************
 * The \b %ReportWriter for ALib when using ALox. An instance of this class is
 * created in method \ref com::aworx::lox::Log::addDebugLogger "Log.addDebugLogger"
 * and registered with ALib.<br>
 * Uses internal domain <c>'$/REPORT'</c> for logging.
 **************************************************************************************************/
public class ALoxReportWriter implements ReportWriter
{
    /** The \b Lox to report to */
    protected   Lox        lox;

    /** ********************************************************************************************
     * Constructs an \b %ALoxReportWriter.
     * @param lox    The \b Lox to report to.
     **********************************************************************************************/
    public ALoxReportWriter ( Lox lox ) { this.lox= lox; }

    /** ********************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     **********************************************************************************************/
    @Override
    public void NotifyActivation( Phase phase )
    {
    }

    /** ********************************************************************************************
     * Log an ALib report using ALox.
     * @param report  The error message.
     **********************************************************************************************/
    @Override
    public void report  (Report.Message report)
    {
        lox.entry( ALoxReportWriter.logDomain(),
                   report.type == 0 ? Verbosity.ERROR      :
                   report.type == 1 ? Verbosity.WARNING    :
                   report.type == 2 ? Verbosity.INFO       :
                                      Verbosity.VERBOSE,
                   report.contents );
    }
    
    /** ********************************************************************************************
     * Returns the domain used to write reports.
     * @return The report log domain.
     **********************************************************************************************/
     public static String logDomain() 
     {
        return ALox.INTERNAL_DOMAINS + "REPORT"; 
     }
}
