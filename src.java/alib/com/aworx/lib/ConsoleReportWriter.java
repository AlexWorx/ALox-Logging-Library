// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib;

/** ************************************************************************************************
 * The simple, default \b %ReportWriter, just writing the message to the console.
 **************************************************************************************************/
public class ConsoleReportWriter implements ReportWriter
{
    /** ********************************************************************************************
     * Just writes the prefix \"ALib Report (Error):\" (respectively \"ALib Report (Warning):\"
     * and the error message to the cout.
     *
     * @param report     The report.
     **********************************************************************************************/
    @Override
    public void report( Report.Message report )
    {
        System.out.println( "ALib Report " + (report.type == 0 ? "Error: "
                                                            : "Warng: " )
                            + report.contents );
    }
}

