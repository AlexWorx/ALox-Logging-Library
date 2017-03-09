// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.lang;

import com.aworx.lib.lang.Phase;


/** ************************************************************************************************
 * Interface that defines a writer for for %ALib \ref com::aworx::lib::lang::Report "Report".
 * By default, an instance of \ref com::aworx::lib::lang::ReportWriterStdIO "ReportWriterStdIO"
 * is installed.
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
     * @param msg     The message to report.
     **********************************************************************************************/
    public void report( Report.Message msg );
}
