// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.loggers;

import java.io.BufferedWriter;
import java.io.FileWriter;

import com.aworx.lib.lang.Phase;
import com.aworx.lib.strings.AString;
import com.aworx.lox.ALox;
import com.aworx.lox.Verbosity;
import com.aworx.lox.detail.textlogger.PlainTextLogger;
import com.aworx.lox.tools.LogTools;


/** ************************************************************************************************
 * This is a very simple file logger for textual log outputs. The file name string provided
 * in the constructor is not verified.
 * The fileName may be changed any time by simply setting the public member #fileName
 * without the need of any other interaction other than acquiring the \c Lox that this logger is
 * attached to.
 **************************************************************************************************/
public class TextFileLogger extends PlainTextLogger
{
    /** The path and fileName to the log file. */
    public    String                    fileName;

    /** Used to write into a log file. */
    protected FileWriter                fw;

    /** Used to write into a log file. */
    protected BufferedWriter            bw;

    /** Flag to prevent file open/close operations when multi-line text logging is performed. */
    protected boolean                   currentlyInMultiLineOp;

    /** Flag that indicates if there was an error opening he file */
    public    boolean                   hasIoError                                           =false;

    /** ********************************************************************************************
     * Creates a TextFileLogger with the given name.
     *
     * @param fileName      The filename (potentially including a path) of the output log file.
     * @param loggerName  The name of the \e Logger. Defaults to "TEXTFILE".
     **********************************************************************************************/
    public    TextFileLogger( String fileName, String  loggerName  )
    {
        super( loggerName, "TEXTFILE", false );
        this.fileName= fileName;
    }

    /** ********************************************************************************************
     * Creates a TextFileLogger with the name "TEXTFILE".
     *
     * @param fileName      The filename (potentially including a path) of the output log file.
     **********************************************************************************************/
    public    TextFileLogger( String fileName )
    {
        super( null, "TEXTFILE", false );
        this.fileName= fileName;
     }

    /** ********************************************************************************************
     * Opens the file.
     **********************************************************************************************/
    protected void openFile()
    {
        try
        {
            fw=  new FileWriter    ( fileName, true ); // true= append
            bw=  new BufferedWriter( fw );
        }
        catch (Exception e)
        {
            hasIoError=     true;
            LogTools.exception( ALox.INTERNAL_DOMAINS, Verbosity.ERROR, e, "Can not open file: \"" + fileName + "\". Exception follows"  );
            return;
        }
        hasIoError= false;
    }

    /** ********************************************************************************************
     * Closes the file.
     **********************************************************************************************/
    protected void closeFile()
    {
        if(hasIoError)
            return;

        try
        {
            bw.close();
        }
        catch (Exception e)
        {
            hasIoError=     true;
            LogTools.exception( ALox.INTERNAL_DOMAINS, Verbosity.ERROR, e, "Error closing file: \"" + fileName + "\". Exception follows"  );
        }
    }

    /** ********************************************************************************************
     * Implementation of abstract interface signaling start and end of a multi line message.
     * On start signal, the log file is opened, closed otherwise. Also stores the actual
     * multi line message state in a field. This is for logText() to know whether file is to be
     * opened/closed.
     *
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    @Override
    protected void notifyMultiLineOp (Phase phase)
    {
        // save state (to have it in logText)
        currentlyInMultiLineOp= ( phase == Phase.BEGIN );

        // open/close the file
        if ( currentlyInMultiLineOp )
            openFile();
        else
            closeFile();
    }

    /** ********************************************************************************************
     * Start a new log line. Appends a new-line character sequence to previously logged lines.
     *
     * @param phase  Indicates the beginning or end of a log operation.
     * @return The IO status (\c true if OK).
     **********************************************************************************************/
    @Override
    protected boolean notifyLogOp( Phase phase )
    {
        // write new line
        if ( phase == Phase.END  )
        {
            try
            {
                bw.newLine();
            }
            catch (Exception e)
            {
                hasIoError=     true;
                LogTools.exception( ALox.INTERNAL_DOMAINS, Verbosity.ERROR, e, "Error writing to file: \"" + fileName + "\". Exception follows"  );
                return false;
            }
        }

        // open/close
        if( !currentlyInMultiLineOp )
        {
            if ( phase == Phase.BEGIN )
                openFile();
            else
                closeFile();
        }

        return !hasIoError;
    }

    /** ********************************************************************************************
     * Write the given region of the given AString to the destination buffer.
     *
     * @param buffer   The string to write a portion of.
     * @param start    The start of the portion in \p{buffer} to write out.
     * @param length   The length of the portion in \p{buffer} to write out.
     * @return The IO status (\c true if OK).
     **********************************************************************************************/
    @Override
    protected boolean logSubstring( AString buffer, int start, int length )
    {
        try
        {
            bw.write( buffer.buffer(), start, length );
        }
        catch (Exception e)
        {
            hasIoError=     true;
            LogTools.exception( ALox.INTERNAL_DOMAINS, Verbosity.ERROR, e, "Error writing to file: \"" + fileName + "\". Exception follows"  );
        }

        return hasIoError;
    }

} // class TextFileLogger




