// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Diagnostics;
using System.Text;
using System.Threading;
using cs.aworx.lib.threads;
using cs.aworx.lib.config;
using cs.aworx.lib.time;

namespace cs.aworx.lib {

/** ************************************************************************************************
 *  Interface for %ALIB \b %ReportWriter. The %ALIB \b %ReportWriter is invoked on internal %ALIB errors
 *  caused by illegal arguments or other wrong use of ALib.
 *  By default, a simple implementation is installed that just uses standard output to print
 *  the error and warning messages to the application's console.
 *  Applications may implement their own ReportWriter.
 *
 *  \see Class \ref cs::aworx::lib::Report "Report".
 **************************************************************************************************/
public interface ReportWriter
{
    /** ********************************************************************************************
     * Report a message. Pure virtual abstract interface method.
     * @param report     The report.
     **********************************************************************************************/
    void Report( Report.Message report );
}

/** ************************************************************************************************
 * The simple, default \b %ReportWriter, just writing the message to the console.
 **************************************************************************************************/
class ConsoleReportWriter : ReportWriter
{
    /** ********************************************************************************************
     * Just writes the prefix \"ALib Report (Error):\" (respectively \"ALib Report (Warning):\"
     * and the error message to the cout.
     *
     * @param report     The report.
     **********************************************************************************************/
    public virtual void Report( Report.Message report )
    {
        Console.WriteLine( "ALib Report " + (report.Type == 0 ? "Error: "
                                                              : "Warng: " )
                            + report.Contents );
    }
}

} // namespace / EOF
