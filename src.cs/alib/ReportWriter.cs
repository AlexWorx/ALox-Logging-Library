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
 * Interface that defines a writer for for %ALib \ref cs::aworx::lib::Report "Report".
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
    void NotifyActivation  ( enums.Phase phase );

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
    /** The singleton which is added in the constructor of \b Report. */
    public static readonly ConsoleReportWriter Singleton= new ConsoleReportWriter();

    /** ********************************************************************************************
     * Protected constructor, only one Singleton might exist.
     **********************************************************************************************/
    protected  ConsoleReportWriter(){}

    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    public virtual void NotifyActivation( enums.Phase phase )
    {
        if ( phase == enums.Phase.Begin )
            ALIB.StdOutputStreamsLock.AddAcquirer   ( null );
        else
            ALIB.StdOutputStreamsLock.RemoveAcquirer( null );
    }

    /** ********************************************************************************************
     * Just writes the prefix \"ALib Report (Error):\" (respectively \"ALib Report (Warning):\"
     * and the error message to the cout.
     *
     * @param report     The report.
     **********************************************************************************************/
    public virtual void Report( Report.Message report )
    {
        ALIB.StdOutputStreamsLock.Acquire();
            String sMsg= "ALib ";
                 if (  report.Type == 0 )   sMsg= sMsg +  "Error:   ";
            else if (  report.Type == 1 )   sMsg= sMsg +  "Warning: ";
            else                            sMsg= sMsg +  "Report (type=" + report.Type  +"): ";

            sMsg= sMsg + report.Contents;

            System.IO.TextWriter tw= report.Type == 0 || report.Type == 1 ? Console.Error : Console.Out;
            tw.Flush();
            tw.WriteLine( sMsg );
            tw.Flush();

            #if DEBUG
                if ( System.Diagnostics.Debugger.IsAttached )
                    System.Diagnostics.Debug.WriteLine( sMsg );
            #endif

        ALIB.StdOutputStreamsLock.Release();

    }
}

} // namespace / EOF
