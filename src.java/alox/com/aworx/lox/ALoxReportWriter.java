// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

import com.aworx.lib.lang.Phase;
import com.aworx.lib.lang.Report;
import com.aworx.lib.lang.ReportWriter;

/** ************************************************************************************************
 * The \b %ReportWriter for \b %ALib when using \b %ALox. An instance of this class is
 * created in method \ref com::aworx::lox::Log::addDebugLogger "Log.addDebugLogger"
 * and registered with \b %ALib.<br>
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
    public ALoxReportWriter ( Lox lox )
    {
        this.lox= lox;
        lox.entry( ALoxReportWriter.logDomain(), Verbosity.VERBOSE,  new Object[] {"ALoxReportWriter set"} );
    }

    /** ********************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     **********************************************************************************************/
    @Override
    public void NotifyActivation( Phase phase )
    {
       /* nothing to do here */
    }

    /** ********************************************************************************************
     * Log an \b %ALib report using \b %ALox.
     * @param msg The message to report.
     **********************************************************************************************/
    @Override
    public void report  (Report.Message msg)
    {
        lox.entry( ALoxReportWriter.logDomain(),
                   msg.type == 0 ? Verbosity.ERROR      :
                   msg.type == 1 ? Verbosity.WARNING    :
                   msg.type == 2 ? Verbosity.INFO       :
                                   Verbosity.VERBOSE,
                   msg.contents );
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
