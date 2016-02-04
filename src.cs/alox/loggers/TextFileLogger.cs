// #################################################################################################
//  cs.aworx.lox.loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.IO;
using System.Runtime.CompilerServices;


using cs.aworx.lib;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lox.tools;
using cs.aworx.lox.core;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;


namespace cs.aworx.lox.loggers    {

/** ************************************************************************************************
 * This is a very simple file logger for textual log outputs. The file name string provided
 * in the constructor is not verified. If write operations fail, this logger disables
 * itself by setting the inherited flag isDisabled to true.
 * The fileName may be changed by simply setting the public member #FileName and the flag
 * #IsDisabled may be set to false by the user without the need of any other interaction other
 * than acquiring the \c Lox that the logger is added to.
 **************************************************************************************************/
public class TextFileLogger : PlainTextLogger
{
    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DBG_LOG || ALOX_REL_LOG)
        public TextFileLogger( String fileName, String    loggerName= "TEXTFILE"  )    {}
        public        String            fileName;
    #else

    /** The path and fileName to the log file. */
    public           String                  FileName;

    /** Used to write into a log file. */
    protected        StreamWriter            sw;

    /** Flag to prevent file open/close operations when multi line text logging is performed. */
    protected        bool                    currentlyInMultiLineOp;


    /** ********************************************************************************************
     * Creates a TextFileLogger.
     *
     * @param fileName    The filename (potentially including a path) of the output log file.
     * @param loggerName  The name of the logger. Defaults to "TEXTFILE".
     **********************************************************************************************/
    public TextFileLogger( String fileName, String loggerName= null  )
    : base ( loggerName, "TEXTFILE" )
    {
        this.FileName= fileName;
    }

    /** ********************************************************************************************
     * Opens the file. If not successful, the logger will be disabled by setting field
     * #IsDisabled to \c true.
     **********************************************************************************************/
    protected void openFile()
    {
        try
        {
            sw=        new StreamWriter( FileName, true );
        }
        #pragma warning disable 168
        catch (Exception e)
        {
            IsDisabled=     true;
            #if ALOX_DBG_LOG
                LogTools.Exception( Log.LOX.InternalDomain, Log.Level.Error, e, "Can not open file: \"" + FileName + "\". Exception follows"  );
            #endif
        }
        #pragma warning restore 168
    }

    /** ********************************************************************************************
     * Closes the file. If not successful, the logger will be disabled by setting field
     * #IsDisabled to \c true.
     **********************************************************************************************/
    protected void closeFile()
    {
        try
        {
            sw.Close();
        }
        #pragma warning disable 168
        catch (Exception e)
        {
            IsDisabled=     true;
            #if ALOX_DBG_LOG
                LogTools.Exception( Log.LOX.InternalDomain, Log.Level.Error, e, "Error closing file: \"" + FileName + "\". Exception follows"  );
            #endif
        }
        #pragma warning restore 168
    }

    /** ********************************************************************************************
     * Implementation of abstract interface signaling start and end of a multi line message.
     * On start signal, the log file is opened, closed otherwise. Also stores the actual
     * multi line message state in a field. This is for doTextLog() to know whether file is to be
     * opened/closed.
     *
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    protected override void notifyMultiLineOp( Phase phase )
    {
        // save state (to have it in doTextLog)
        currentlyInMultiLineOp= (phase == Phase.Begin );

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
    protected override bool notifyLogOp( Phase phase )
    {
        // write new line
        if ( phase == Phase.End  )
        {
            try
            {
                sw.WriteLine();
            }
            #pragma warning disable 168
            catch (Exception e)
            {
                IsDisabled=     true;
                #if ALOX_DBG_LOG
                    LogTools.Exception( Log.LOX.InternalDomain, Log.Level.Error, e, "Error writing to file: \"" + FileName + "\". Exception follows"  );
                #endif
                return false;
            }
            #pragma warning restore 168
        }

        // open/close
        if( !currentlyInMultiLineOp )
        {
            if ( phase == Phase.Begin )
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
    protected override bool doLogSubstring( AString buffer, int start, int length )
    {
        try
        {
            sw.Write( buffer.Buffer(), start, length );
        }
        #pragma warning disable 168
        catch (Exception e)
        {
            IsDisabled=     true;
            #if ALOX_DBG_LOG
                LogTools.Exception( Log.LOX.InternalDomain, Log.Level.Error, e, "Error writing to file: \"" + FileName + "\". Exception follows"  );
            #endif
            return false;
        }
        #pragma warning restore 168

        return true;
    }

    #endif // ALOX_DBG_LOG || ALOX_REL_LOG

} // class TextFileLogger
} // namespace
