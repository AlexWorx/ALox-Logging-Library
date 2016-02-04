// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.loggers;

import java.io.*;

import com.aworx.lib.enums.Phase;
import com.aworx.lib.strings.AString;
import com.aworx.lox.Log;
import com.aworx.lox.core.textlogger.PlainTextLogger;
import com.aworx.lox.tools.LogTools;


/** ************************************************************************************************
 * This is a very simple file logger for textual log outputs. The file name string provided
 * in the constructor is not verified. If write operations fail, this logger disables
 * itself by setting the inherited flag isDisabled to true.
 * The fileName may be changed by simply setting the public member #fileName and the flag
 * #isDisabled may be set to false by the user without the need of any other interaction
 * than acquiring the \c Lox that the logger is added to.
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

    /** ********************************************************************************************
     * Creates a TextFileLogger with the given name.
     *
     * @param fileName      The filename (potentially including a path) of the output log file.
     * @param loggerName  The name of the logger. Defaults to "TEXTFILE".
     **********************************************************************************************/
    public    TextFileLogger( String fileName, String  loggerName  )
    {
        super( loggerName, "TEXTFILE" );
        this.fileName= fileName;
    }

    /** ********************************************************************************************
     * Creates a TextFileLogger with the name "TEXTFILE".
     *
     * @param fileName      The filename (potentially including a path) of the output log file.
     **********************************************************************************************/
    public    TextFileLogger( String fileName )
    {
        super( null, "TEXTFILE" );
        this.fileName= fileName;
     }

    /** ********************************************************************************************
     * Opens the file. If not successful, the logger will be disabled by setting field
     * #isDisabled to \c true.
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
            isDisabled=     true;
            LogTools.exception( Log.LOX.internalDomain, Log.Level.ERROR, e, "Can not open file: \"" + fileName + "\". Exception follows"  );
        }
    }

    /** ********************************************************************************************
     * Closes the file. If not successful, the logger will be disabled by setting field
     * #isDisabled to \c true.
     **********************************************************************************************/
    protected void closeFile()
    {
        try
        {
            bw.close();
        }
        catch (Exception e)
        {
            isDisabled=     true;
            LogTools.exception( Log.LOX.internalDomain, Log.Level.ERROR, e, "Error closing file: \"" + fileName + "\". Exception follows"  );
        }
    }

    /** ********************************************************************************************
     * Implementation of abstract interface signaling start and end of a multi line message.
     * On start signal, the log file is opened, closed otherwise. Also stores the actual
     * multi line message state in a field. This is for doTextLog() to know whether file is to be
     * opened/closed.
     *
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    @Override
    protected void notifyMultiLineOp (Phase phase)
    {
        // save state (to have it in doTextLog)
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
     * @return Always returns true.
     **********************************************************************************************/
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
                isDisabled=     true;
                LogTools.exception( Log.LOX.internalDomain, Log.Level.ERROR, e, "Error writing to file: \"" + fileName + "\". Exception follows"  );
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

        return true;
    }

    /** ********************************************************************************************
     * Write the given region of the given AString to the destination buffer.
     *
     * @param buffer   The string to write a portion of.
     * @param start    The start of the portion in \p buffer to write out.
     * @param length   The length of the portion in \p buffer to write out.
     * @return Always returns true.
     **********************************************************************************************/
    protected boolean doLogSubstring( AString buffer, int start, int length )
    {
        try
        {
            bw.write( buffer.buffer(), start, length );
        }
        catch (Exception e)
        {
            isDisabled=     true;
            LogTools.exception( Log.LOX.internalDomain, Log.Level.ERROR, e, "Error writing to file: \"" + fileName + "\". Exception follows"  );
            return false;
        }

        return true;
    }

} // class TextFileLogger




