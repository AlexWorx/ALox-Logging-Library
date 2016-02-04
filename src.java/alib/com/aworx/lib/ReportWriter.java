// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib;


/** ************************************************************************************************
 * Interface class declaring a plug-in for class \ref com::aworx::lib::Report "Report".
 * By default, a simple implementation is installed that just uses standard output to print
 * the error and warning messages to the applications' console.
 * Applications may implement their own \b %ReportWriter.
 **************************************************************************************************/
public interface ReportWriter
{
    /** ********************************************************************************************
     * Report a message. Pure virtual abstract interface method.
     * @param report     The report.
     **********************************************************************************************/
    void report( Report.Message report );
}
