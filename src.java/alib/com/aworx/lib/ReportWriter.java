// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib;

import com.aworx.lib.enums.Phase;


/** ************************************************************************************************
 * Interface that defines a writer for for %ALib \ref com::aworx::lib::Report "Report".
 * By default, a simple implementation is installed that just uses standard output and 
 * standard error streams.<br>
 * Applications may implement their own ReportWriter.
 **************************************************************************************************/
public interface ReportWriter
{
    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    public void NotifyActivation  ( Phase phase );

    /** ********************************************************************************************
     * Report a message. Pure virtual abstract interface method.
     * @param report     The report.
     **********************************************************************************************/
    public void report( Report.Message report );
}
