// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib;

import com.aworx.lib.enums.Phase;

/** ************************************************************************************************
 * The simple, default \b %ReportWriter, just writing the message to the console.
 **************************************************************************************************/
public class ConsoleReportWriter implements ReportWriter
{
    /** The singleton which is added in the constructor of \b Report. */
    public final static ConsoleReportWriter SINGLETON= new ConsoleReportWriter();

    /** ********************************************************************************************
     * Protected constructor, only one Singleton might exist.
     **********************************************************************************************/
    protected  ConsoleReportWriter(){}

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
            
            String sMsg= "ALib ";
                 if (  report.type == 0 )   sMsg= sMsg +  "Error:   ";
            else if (  report.type == 1 )   sMsg= sMsg +  "Warning: ";
            else                            sMsg= sMsg +  "Report (type=" + report.type  +"): ";
    
            sMsg= sMsg + report.contents;
    
            if (report.type == 0 || report.type == 1)
            { 
                System.err.flush();
                System.err.println( sMsg );
                System.err.flush();
            }
            else
            { 
                System.out.flush();
                System.out.println( sMsg );
                System.out.flush();
            }
        
         ALIB.stdOutputStreamsLock.release();
    }
}

