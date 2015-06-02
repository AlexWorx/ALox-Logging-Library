// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using com.aworx.util;
using com.aworx.lox;
using com.aworx.lox.core;

namespace com.aworx.lox.core
{
/** ************************************************************************************************
 * <summary>
 *  This class is a still abstract implementation of class Logger which is used as the super class
 *  for all textual Logger implementations within ALox, e.g. ConsoleLogger.
 *
 *  The class uses two helper classes. One to convert the log message object into a string representation
 *  and a second to generate the textual representation of the meta information of a log call.
 *  These helpers can be extended and replaced to modify the behavior of TextLogger.
 *
 *  The final log message is then passed to the abstract method #doTextLog(). Hence, custom Logger classes
 *  that inherited from this class instead of directly from class #Logger, need to implement #doTextLog()
 *  instead of implementing #doLog()!
 *
 *  Class TextLogger supports multi line log outputs. Such multi line log outputs can be configured to
 *  be logged in different ways. See #MultiLineMsgMode for more information.
 * </summary>
 **************************************************************************************************/
public abstract class TextLogger : Logger
{

    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DEBUG || ALOX_REL_LOG)

        // Empty constructor
        protected TextLogger()
        {
        }

    #else

    // #############################################################################################
    // Internal fields
    // #############################################################################################

    /// <summary> The internal log Buffer.</summary>
    protected         AString            logBuf                                    = new AString( 256 );


    // #############################################################################################
    // Public fields
    // #############################################################################################

    /**
     * A helper object to convert log objects into textual representations. To extend TextLogger, this
     * object can be replaced by custom implementations.
     */
    public            TextLoggerObjectConverter ObjectConverter         =new TextLoggerObjectConverter();

    /** <summary>
     * A helper object to format log objects into textual representations. This class incorporates
     * a format string that defines the meta information in the log output. Furthermore, to extend
     * TextLogger, this object can be replaced by custom implementations of it.
     * </summary>*/
    public            TextLoggerLineFormatter   LineFormatter           =new TextLoggerLineFormatter();


    /** <summary>
     * A list of pairs of strings. Within each log message, the first string of a pair is
     *  searched and replaced by the second string. Very simple, but useful in some cases.
     * </summary>*/
    public            List<String>              Replacements            =new List<String>();

    /** <summary>
     * Determines if multi line messages should be split into different log lines. Possible values are:
     *
     * - 0: No line split is performed, delimiters can be replaced by readable delimiters (depending on
     *      setting of #MultiLineDelimiter and # MultiLineDelimiterRepl).
     *
     * - 1: Each log line contains all meta information
     *
     * - 2: Starting with second log line, meta information is replaced by blanks  (default)
     *
     * - 3: The headline #FmtMultiLineMsgHeadline is logged and all lines of the multi line text are logged
     *      at position zero (without further meta information)
     *
     * - 4: Just the multi line text is logged, starting at column zero (no meta information is logged)
     * </summary>*/
    public            int                       MultiLineMsgMode        =2;

    /** <summary>
     * This is the string interpreted as line delimiter within log messages. If null, CR, LF or CRLF
     * are used. Important: Set to empty string, to stop any multi line processing of TextLogger, even the replacements.
     * </summary>*/
    public            String                    MultiLineDelimiter      =null;

    /** <summary>
     * This is the readable (!) separator string, for logging out multi line messages into a
     * single line (#MultiLineMsgMode==0).
     * </summary>*/
    public            String                    MultiLineDelimiterRepl  ="\\r";


    /// <summary>Headline for multi line messages (depending on #MultiLineMsgMode)  .</summary>
    public            String                    FmtMultiLineMsgHeadline ="ALox: Multi line message follows: ";

    /** <summary>
     *  Prefix for multi line messages. This is also used if multi line messages logging is switched off
     *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
     * </summary>*/
    public            String                    FmtMultiLinePrefix      =">> ";

    /** <summary>
     *  Postfix for multi line messages. This is also used if multi line messages logging is switched off
     *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
     * </summary>*/
    public            String                    FmtMultiLinePostfix     =null;


    // #############################################################################################
    // Constructor
    // #############################################################################################
    /** ********************************************************************************************
     * <summary>    Constructs a logger. </summary>
     * <param name="name"> The name of the logger. </param>
     **********************************************************************************************/
    protected TextLogger(String    name )
        : base ( name )
    {
    }

    // #############################################################################################
    // Abstract methods (introduced)
    // #############################################################################################

        /** ****************************************************************************************
         * <summary> The abstract function that logs a text message to be implemented by descendants </summary>
         * <param name="domain">    The log domain name. </param>
         * <param name="level">     The log level. This has been checked to be active already on this
         *                          stage and is provided to be able to be logged out only. </param>
         * <param name="msg">       The log message. </param>
         * <param name="indent">    the indentation in the output. Defaults to 0. </param>
         * <param name="caller">    Once compiler generated and passed forward to here. </param>
         * <param name="lineNumber">The line number of a multi-line message, starting with 0. For single line
         *                             messages this is -1. </param>
         ******************************************************************************************/
        abstract protected void doTextLog(  AString       domain,     Log.Level    level,
                                            AString       msg,        int          indent,
                                            CallerInfo    caller,     int          lineNumber);

        /** ****************************************************************************************
         * <summary>
         *  Abstract method to be implemented by descendants. This message is called only when multi-line
         *  messages are logged. It is called exactly once before a series of doLog() calls of a multi-line
         *  message and exactly once after such series.<br>
         *  This is useful if the writing of text includes the acquisition of system resources (e.g. opening
         *  a file).
         * </summary>
         * <param name="isStart">    If true, indicates the begin of a multi-line message, the end otherwise.  </param>
         ******************************************************************************************/
        abstract protected void notifyMultiLineOp( bool isStart );


    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################

        /** ****************************************************************************************
         * <summary>
         *  Implementation of Logger.doLog(). Creates all the textual information that is logged in a line
         *  before the message itself.
         * </summary>
         * <param name="domain">    The log domain name. </param>
         * <param name="level">     The log level. This has been checked to be active already on this
         *                          stage and is provided to be able to be logged out only. </param>
         * <param name="msgObject"> The log message object (mostly a String or AString). </param>
         * <param name="indent">    the indentation in the output. Defaults to 0. </param>
         * <param name="caller">    Once compiler generated and passed forward to here. </param>
         ******************************************************************************************/
        override protected void doLog(  AString       domain,       Log.Level    level,
                                        Object        msgObject,    int          indent,
                                        CallerInfo    caller )
        {

            // clear Buffer
            logBuf.Clear();

            // process log line format
            LineFormatter.WriteMetaInfo( this, logBuf, domain, level, indent, caller );

            // convert msg object into a AString representation
            AString msg=    ObjectConverter.ConvertObject( msgObject );

            // replace strings in message
            for ( int i=0; i < Replacements.Count - 1; i+=2 )
                msg.Replace( Replacements[i], Replacements[i + 1] );

            // check for empty messages
            if ( msg.Length() == 0 )
            {
                // log empty msg and quit
                doTextLog( domain, level, logBuf, indent, caller, -1 );
                return;
            }

            // single line output
            if ( MultiLineMsgMode == 0 )
            {
                // replace line separators
                int cntReplacements=0;
                if ( MultiLineDelimiter != null )
                    cntReplacements+=msg.ReplaceCount( MultiLineDelimiter,    MultiLineDelimiterRepl );
                else
                {
                    cntReplacements+=msg.ReplaceCount( "\r\n", MultiLineDelimiterRepl );
                    cntReplacements+=msg.ReplaceCount( "\r", MultiLineDelimiterRepl );
                    cntReplacements+=msg.ReplaceCount( "\n", MultiLineDelimiterRepl );
                }

                // append msg to logBuf
                if ( cntReplacements == 0 )
                    logBuf.Append( msg );
                else
                {
                    logBuf.Append( FmtMultiLinePrefix );
                    logBuf.Append( msg );
                    logBuf.Append( FmtMultiLinePostfix );
                }

                // now do the logging by calling our derived classes' doLog
                doTextLog( domain, level, logBuf, indent, caller, -1 );

                // stop here
                return;
            }

            // multiple line output
            int actStart=0;
            int lineNo=0;
            int lbLenBeforeMsgPart=logBuf.Length();

            // loop over lines in msg
            while ( actStart < msg.Length() )
            {
                // find next end
                int delimLen;
                int actEnd;

                // no delimiter given: search "\r\n", then '\r', then '\n'
                if ( String.IsNullOrEmpty( MultiLineDelimiter ) )
                {
                    delimLen=2;
                    actEnd=msg.IndexOf( "\r\n", actStart );
                    if ( actEnd < 0 )
                    {
                        delimLen=1;
                        actEnd=msg.IndexOf( "\r", actStart );

                        if ( actEnd < 0 )
                            actEnd=msg.IndexOf( "\n", actStart );
                    }
                }
                else
                {
                    delimLen=MultiLineDelimiter.Length;
                    actEnd=msg.IndexOf( MultiLineDelimiter, actStart );
                }

                // not found a delimiter? - log the rest
                if ( actEnd < 0 )
                {
                    // single line?
                    if ( lineNo == 0 )
                    {
                        // append msg to logBuf
                        logBuf.Append( msg );

                        // now do the logging by calling our derived classes' doLog
                        doTextLog( domain, level, logBuf, indent, caller, -1 );

                        // stop here
                        return;
                    }

                    // store actual end
                    actEnd=msg.Length();
                }

                // found a delimiter

                // signal start of multi line log
                if ( lineNo == 0 )
                    notifyMultiLineOp( true );

                // in mode 3, 4, when meta info is deleted, we log a separate line first!
                if ( lineNo == 0 && ( MultiLineMsgMode == 3 || MultiLineMsgMode == 4 ) )
                {
                    // log headline
                    if ( MultiLineMsgMode == 3 )
                    {
                        logBuf.Append( FmtMultiLineMsgHeadline );
                        doTextLog( domain, level, logBuf, indent, caller, 0 );
                    }

                    // remember zero as offset
                    lbLenBeforeMsgPart=0;
                }

                // blank out meta information? (do this exactly in 2nd line once)
                if ( lineNo == 1 && MultiLineMsgMode == 2 )
                    logBuf.Fill(' ', 0, lbLenBeforeMsgPart );


                // reset logBuf length to marked position
                logBuf.SetLength( lbLenBeforeMsgPart );

                // append message
                logBuf.Append( FmtMultiLinePrefix );
                  logBuf.Append( msg, actStart, actEnd - actStart  );
                logBuf.Append( FmtMultiLinePostfix );

                // now do the logging by calling our derived classes' doLog
                doTextLog( domain, level, logBuf, indent, MultiLineMsgMode != 4 ? caller : null, lineNo );

                // next
                actStart= actEnd + delimLen;
                lineNo++;
            }

            // signal end of multi line log
            if ( lineNo > 0 )
                notifyMultiLineOp( false );
        }

    #endif // ALOX_DEBUG || ALOX_REL_LOG

} // class TextLogger

} // namespace
