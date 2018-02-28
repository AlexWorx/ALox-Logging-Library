// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.lang;

import com.aworx.lib.ALIB;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.format.Formatter;

/** ************************************************************************************************
 * The standard \b %ReportWriter writing the message to \c System.err and \c System.out.
 * The global formatter singleton is used is used to process the objects in the report message.
 * This is by default of type
 * \ref com.aworx.lib.strings.format.FormatterPythonStyle "FormatterPythonStyle". See
 * \ref com.aworx.lib.strings.format.Formatter.acquireDefault "Formatter.acquireDefault"
 * for more information.
 **************************************************************************************************/
public class ReportWriterStdIO implements ReportWriter
{
    /** The singleton which is added in the constructor of \b Report. */
    public final static     ReportWriterStdIO SINGLETON= new com.aworx.lib.lang.ReportWriterStdIO();

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
     * @param msg The message to report.
     **********************************************************************************************/
    @Override
    @SuppressWarnings("all")
    public void report( Report.Message msg )
    {
        ALIB.stdOutputStreamsLock.acquire();
            buffer._()._("ALib ");
                 if (  msg.type == 0 )   buffer._( "Error:   ");
            else if (  msg.type == 1 )   buffer._( "Warning: ");
            else                         buffer._( "Report (type=")._( msg.type )._("): ");


            Formatter formatter= Formatter.acquireDefault();
            formatter.format( buffer, msg.contents );
            Formatter.releaseDefault();


            if (msg.type == 0 || msg.type == 1)
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

