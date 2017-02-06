// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.lang;

import com.aworx.lib.ALIB;
import com.aworx.lib.threads.ThreadLock;
import com.aworx.lib.threads.SmartLock;
import com.aworx.lib.lang.Phase;
import com.aworx.lib.lang.Report;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Formatter;
import com.aworx.lib.strings.FormatterPythonStyle;

/** ************************************************************************************************
 * The standard \b %ReportWriter writing the message to \c System.err and \c System.out.
 * A formatter of type
 * \ref com::aworx::lib::strings::FormatterPythonStyle "FormatterPythonStyle" is used to process the
 * objects in the report message.
 **************************************************************************************************/
public class ReportWriterStdIO implements ReportWriter
{
    /** The singleton which is added in the constructor of \b Report. */
    public final static     ReportWriterStdIO SINGLETON= new com.aworx.lib.lang.ReportWriterStdIO();

    /**
     * The formatter used to format the output. This field is public and might be exchanged by
     * users, while no 'safe' change interface is provided (neither in respect to threading,
     * nor allocation. In contrast the field is just public. Therefore, when replacing this
     * field,
     * - the previous one needs to be deleted and
     * - concurrent access needs to be avoided.
     */
    public                  Formatter           formatter              = new FormatterPythonStyle();

    /** Buffer used for formatting messages */
    protected               AString             buffer                              = new AString();


    /** ********************************************************************************************
     * Protected constructor, only one Singleton might exist.
     **********************************************************************************************/
    protected ReportWriterStdIO(){}

    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    @Override
    public void NotifyActivation( Phase phase )
    {
        if ( phase == Phase.BEGIN )
            ALIB.stdOutputStreamsLock.addAcquirer   ( null );
        else
            ALIB.stdOutputStreamsLock.removeAcquirer( null );
    }

    /** ********************************************************************************************
     * Just writes the prefix \"ALib Report (Error):\" (respectively \"ALib Report (Warning):\"
     * and the error message to the cout.
     *
     * @param report     The report.
     **********************************************************************************************/
    @Override
    @SuppressWarnings("all")
    public void report( Report.Message report )
    {
        ALIB.stdOutputStreamsLock.acquire();
            buffer._()._("ALib ");
                 if (  report.type == 0 )   buffer._( "Error:   ");
            else if (  report.type == 1 )   buffer._( "Warning: ");
            else                            buffer._( "Report (type=")._( report.type )._("): ");


            formatter.FormatList( buffer, report.contents );

            if (report.type == 0 || report.type == 1)
            {
                System.err.flush();
                System.err.println( buffer.toString() );
                System.err.flush();
            }
            else
            {
                System.out.flush();
                System.out.println( buffer.toString() );
                System.out.flush();
            }

         ALIB.stdOutputStreamsLock.release();
    }
}

