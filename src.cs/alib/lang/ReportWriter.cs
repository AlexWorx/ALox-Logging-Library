// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Diagnostics;
using System.Text;
using System.Threading;
using cs.aworx.lib.threads;
using cs.aworx.lib.config;
using cs.aworx.lib.strings;
using cs.aworx.lib.strings.format;
using cs.aworx.lib.time;

namespace cs.aworx.lib.lang {

/** ************************************************************************************************
 * Interface that defines a writer for for %ALib \ref cs::aworx::lib::lang::Report "Report".
 * By default, an instance of \ref cs::aworx::lib::lang::ReportWriterStdIO "ReportWriterStdIO"
 * is installed.
 * Applications may implement their own ReportWriter.
 **************************************************************************************************/
public interface ReportWriter
{
    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    void NotifyActivation  ( lang.Phase phase );

    /** ********************************************************************************************
     * Report a message. Pure virtual abstract interface method.
     * @param msg    The message to report.
     **********************************************************************************************/
    void Report( Report.Message msg );
}

/** ************************************************************************************************
 * The standard \b %ReportWriter writing the message to \c Console.Error and \c Console.Out.
 * The global formatter singleton is used is used to process the objects in the report message.
 * This is by default of type
 * \ref cs::aworx::lib::strings::format::FormatterPythonStyle "FormatterPythonStyle". See
 * \ref cs::aworx::lib::strings::format::Formatter::AcquireDefault "Formatter.AcquireDefault"
 * for more information.
 **************************************************************************************************/
class ReportWriterStdIO : ReportWriter
{
    /** The singleton which is added in the constructor of \b Report. */
    public static readonly  ReportWriterStdIO     Singleton               = new ReportWriterStdIO();

    /** Buffer used for formatting messages */
    protected               AString             buffer                              = new AString();

    /** ********************************************************************************************
     * Protected constructor, only one Singleton might exist.
     **********************************************************************************************/
    protected  ReportWriterStdIO(){}

    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    public virtual void NotifyActivation( lang.Phase phase )
    {
        if ( phase == lang.Phase.Begin )
            ALIB.StdOutputStreamsLock.AddAcquirer   ( null );
        else
            ALIB.StdOutputStreamsLock.RemoveAcquirer( null );
    }

    /** ********************************************************************************************
     * Just writes the prefix \"ALib Report (Error):\" (respectively \"ALib Report (Warning):\"
     * and the error message to the cout.
     *
     * @param msg The message to report.
     **********************************************************************************************/
    public virtual void Report( Report.Message msg )
    {
        ALIB.StdOutputStreamsLock.Acquire();
            buffer._()._("ALib ");
                 if (  msg.Type == 0 )   buffer._( "Error:   ");
            else if (  msg.Type == 1 )   buffer._( "Warning: ");
            else                         buffer._( "Report (type=")._( msg.Type )._("): ");

            Formatter formatter= Formatter.AcquireDefault();
            formatter.Format( buffer, msg.Contents );
            Formatter.ReleaseDefault();

            System.IO.TextWriter tw= msg.Type == 0 || msg.Type == 1 ? Console.Error : Console.Out;
            tw.Flush();
            tw.WriteLine( buffer.ToString() );
            tw.Flush();

            #if DEBUG
                if ( System.Diagnostics.Debugger.IsAttached )
                    System.Diagnostics.Debug.WriteLine( buffer.ToString() );
            #endif

        ALIB.StdOutputStreamsLock.Release();
    }
}

} // namespace / EOF
