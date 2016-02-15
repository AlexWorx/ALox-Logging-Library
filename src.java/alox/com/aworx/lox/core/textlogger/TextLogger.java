// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


/** ************************************************************************************************
 * This namespaces defines class \b TextLogger and its helpers.
 **************************************************************************************************/
package com.aworx.lox.core.textlogger;

import java.util.ArrayList;

import com.aworx.lib.enums.Phase;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lox.ESC;
import com.aworx.lox.Log;
import com.aworx.lox.core.CallerInfo;
import com.aworx.lox.core.Logger;

/** ************************************************************************************************
 * This class is a still abstract implementation of class Logger which is used as the super class
 * for all textual Logger implementations within ALox, e.g. ConsoleLogger.
 *
 * The class uses two helper classes. One to convert the log message object into a string representation
 * and a second to generate the textual representation of the meta information of a log call.
 * These helpers can be extended and replaced to modify the behavior of TextLogger.
 *
 * The final log message is then passed to the abstract method #doTextLog(). Hence, custom Logger classes
 * that inherited from this class instead of directly from class #Logger, need to implement #doTextLog()
 * instead of implementing #doLog()!
 *
 * Class TextLogger supports multi line log outputs. Such multi line log outputs can be configured to
 * be logged in different ways. See #multiLineMsgMode for more information.
 **************************************************************************************************/
public abstract class TextLogger extends Logger
{
    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /**  The internal log Buffer. */
        protected AString                   logBuf                      = new AString( 256 );

        /**
         * A list of pairs of strings. Within each log message, the first string of a pair is
         *  searched and replaced by the second string. Very simple, but useful in some cases.
         */
        protected ArrayList<String>         replacements                = new ArrayList<String>();


    // #############################################################################################
    // Public fields
    // #############################################################################################

        /**
         * A helper object to convert log objects into textual representations. To extend TextLogger, this
         * object can be replaced by custom implementations.
         */
        public    ObjectConverter           objectConverter             = new ObjectConverter();

        /**
         * A helper object to format log objects into textual representations. This class incorporates
         * a format string that defines the meta information in the log output. Furthermore, to extend
         * TextLogger, this object can be replaced by custom implementations of it.
         */
        public    MetaInfo                  metaInfo                    = new MetaInfo();

        /**
         *  Holds a list of values for auto tab positions and field sizes.
         *  For each requested value, a corresponding array field is created on the fly.
         *  If the format string get's changed and different (new) auto values should be used, then
         *  this field should be reset after setting the new format string.
         *  The other way round, it is also possible to preset set minimum values for tabs and field
         *  sizes and hence avoid the columns growing during the lifetime of the Logger.
         */
        public    AutoSizes                 autoSizes                   = new AutoSizes();

        /**
         * Determines if multi line messages should be split into different log lines. Possible values are:
         *
         * - 0: No line split is performed. Delimiters can be replaced by readable delimiters (depending on
         *   setting of #multiLineDelimiter and #multiLineDelimiterRepl).
         *
         * - 1: Each log line contains all meta information
         *
         * - 2: Starting with second log line, meta information is replaced by blanks  (default)
         *
         * - 3: The headline #fmtMultiLineMsgHeadline is logged and all lines of the multi line text are logged
         *      at position zero (without further meta information)
         *
         * - 4: Just the multi line text is logged, starting at column zero (no meta information is logged)
         */
        public    int                       multiLineMsgMode             = 2;

        /**
         * This is the string interpreted as line delimiter within log messages. If null, CR, LF or CRLF
         * are used.  Important: Set to empty string, to stop any multi line processing of TextLogger, even the replacements.
         */
        public    String                    multiLineDelimiter           = null;

        /**
         * This is the readable (!) separator string, for logging out multi line messages into a
         * single line (#multiLineMsgMode==0).
         */
        public    String                    multiLineDelimiterRepl       = "\\r";


        /** Headline for multi line messages (depending on #multiLineMsgMode)  . */
        public    String                    fmtMultiLineMsgHeadline      = "ALox: Multi line message follows: ";

        /**
         *  Prefix for multi line messages. This is also used if multi line messages logging is switched off
         *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
         */
        public    String                    fmtMultiLinePrefix           = ">> ";

        /**
         *  Suffix for multi line messages. This is also used if multi line messages logging is switched off
         *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
         */
        public    String                    fmtMultiLineSuffix          = null;

        /** The character(s) used for indentation. */
        public    String                    fmtIndentString              = "  ";



    // #############################################################################################
    // Constructor
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs a TextLogger.
         *
         * @param name     The name of the logger. If empty, it defaults to the type name.
         * @param typeName The type of the logger.
         ******************************************************************************************/
        protected TextLogger( String  name, String typeName )
        {
            super( name, typeName );
        }

    // #############################################################################################
    // Public interface
    // #############################################################################################

        /** ****************************************************************************************
         *  Adds the given pair of replacement strings. If searched string already exists, the
         *  current replacement string gets replaced. If the replacement string equals 'null'
         *  nothing is set and a previously set replacement definition becomes unset.
          * @param searched    The string to be searched.
          * @param replacement The replacement string. If this equals \c null a previously set
          *                    replacement will be unset.
         ******************************************************************************************/
        public void  setReplacement( String searched, String replacement )
        {
            // if exists, replace replacement
            for( int i= 0; i < replacements.size(); i+= 2)
            {
                String s= replacements.get(i);
                if ( s.equals( searched ) )
                {
                    if ( replacement != null )
                    {
                        i++;
                        replacements.set( i, replacement );
                        return;
                    }
                    else
                    {
                        replacements.remove( i );
                        replacements.remove( i );
                        return;
                    }
                }
            }

            // append at the end
            if ( replacement != null )
            {
                replacements.add( searched    );
                replacements.add( replacement );
            }
        }

        /** ****************************************************************************************
         *  Removes all pairs of searched strings and their replacement value.
         ******************************************************************************************/
        public void  clearReplacements()
        {
            replacements.clear();
        }


    // #############################################################################################
    // Abstract methods (introduced)
    // #############################################################################################

        /** ****************************************************************************************
         *  This abstract method introduced by this class "replaces" the the abstract method #doLog
         *  of parent class Logger which this class implements. In other words, descendants of this
         *  class need to overwrite this method instead of #doLog. This class %TextLogger is
         *  responsible for generating meta information, doing text replacements, handle multi-line
         *  messages, etc. and provides the textual representation of the whole log contents
         *  to descendants using this method.
         *
         * @param domain        The log domain name. If not starting with a slash ('/')
         *                      this is appended to any default domain name that might have been
         *                      specified for the source file.
         * @param level         The log level. This has been checked to be active already on this
         *                      stage and is provided to be able to be logged out only.
         * @param msg           The log message.
         * @param indent        the indentation in the output. Defaults to 0.
         * @param caller        Once compiler generated and passed forward to here.
         * @param lineNumber    The line number of a multi-line message, starting with 0.
         *                      For single line messages this is -1.
         ******************************************************************************************/
        abstract protected void doTextLog( AString     domain,     Log.Level   level,
                                           AString     msg,        int         indent,
                                           CallerInfo  caller,     int         lineNumber);

        /** ****************************************************************************************
         * Abstract method to be implemented by descendants. This message is called only when
         * multi-line messages are logged. It is called exactly once before a series of doLog()
         * calls of a multi-line message and exactly once after such series.<br>
         * This is useful if the writing of text includes the acquisition of system resources
         * (e.g. opening a file).
         *
         * @param phase  Indicates the beginning or end of a multi-line operation.
         ******************************************************************************************/
        abstract protected void notifyMultiLineOp( Phase phase );

    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################

        /** ****************************************************************************************
         *  This is the implementation of the abstract method inherited from class Logger
         *  that executes a log.<br>
         *  This class implements this method and but exposes the new abstract method #doTextLog.
         *  This mechanism allows this class to do various things that are standard to Loggers
         *  of type TextLogger. For example, meta information of the log invocation is formatted and
         *  string replacements are performed. This way, descendants of this class will consume
         *  a ready to use log buffer with all meta information included and their primary
         *  obligation is to copy the content into a corresponding output stream.
         *
         *
         * @param domain    The log domain name. If not starting with a slash ('/')
         *                  this is appended to any default domain name that might have been specified
         *                  for the source file.
         * @param level     The log level. This has been checked to be active already on this stage and
         *                  is provided to be able to be logged out only.
         * @param msgObject The log message. If this is not a String (StringBuilder, AString, etc.)
         *                  type, then is converted to a text using 'toString()'.
         * @param indent    the indentation in the output. Defaults to 0.
         * @param caller    Once compiler generated and passed forward to here.
         ******************************************************************************************/
        @Override protected void doLog(    AString     domain,     Log.Level   level,
                                           Object      msgObject,  int         indent,
                                           CallerInfo  caller )

        {
            // clear Buffer and reset utility members
            logBuf.clear();
            autoSizes.start();

            //  << meta info << ESC::EOMETA << indent
            int qtyESCTabsWritten=  metaInfo.write( this, logBuf, domain, level, caller );

            logBuf._( ESC.EOMETA );

            for (int i= indent; i > 0 ; i--)
                logBuf._( fmtIndentString );


            // convert msg object into an AString representation
            AString msgBuf=  objectConverter.convertObject( msgObject );

            // replace strings in message
            for ( int i= 0 ; i < replacements.size() -1 ; i+= 2 )
                msgBuf.searchAndReplace( replacements.get( i ), replacements.get( i + 1 ) );

            // check for empty messages
            if ( msgBuf.isEmpty() )
            {
                // log empty msg and quit
                doTextLog( domain, level, logBuf, indent, caller, -1 );
                return;
            }

            // single line output
            if ( multiLineMsgMode == 0 )
            {
                // replace line separators
                int cntReplacements= 0;
                if ( multiLineDelimiter != null )
                    cntReplacements+= msgBuf.searchAndReplace( multiLineDelimiter, multiLineDelimiterRepl );
                else
                {
                    cntReplacements+= msgBuf.searchAndReplace( "\r\n",  multiLineDelimiterRepl );
                    cntReplacements+= msgBuf.searchAndReplace( "\r",    multiLineDelimiterRepl );
                    cntReplacements+= msgBuf.searchAndReplace( "\n",    multiLineDelimiterRepl );
                }

                // append msg to logBuf
                if ( cntReplacements == 0 )
                {
                    logBuf._NC( msgBuf );
                }
                else
                {
                    logBuf._( fmtMultiLinePrefix );
                      logBuf._NC( msgBuf );
                    logBuf._( fmtMultiLineSuffix );
                }

                // now do the logging by calling our derived classes' doLog
                doTextLog( domain, level, logBuf, indent, caller, -1 );

                // stop here
                return;
            }

            // multiple line output
            int qtyTabStops= autoSizes.actualIndex;
            int actStart= 0;
            int lineNo= 0;
            int lbLenBeforeMsgPart= logBuf.length();

            // loop over lines in msg
            while( actStart < msgBuf.length() )
            {
                // find next end
                int delimLen;
                int actEnd;

                // no delimiter given: search "\r\n", then '\r', then '\n'
                if ( CString.isNullOrEmpty(multiLineDelimiter) )
                {
                    delimLen=    2;
                    actEnd=        msgBuf.indexOf ( "\r\n", actStart );
                    if (actEnd < 0 )
                    {
                        delimLen= 1;
                        actEnd=    msgBuf.indexOf ( "\r",   actStart );

                        if (actEnd < 0 )
                            actEnd=    msgBuf.indexOf ( "\n",   actStart );
                    }
                }
                else
                {
                    delimLen=     multiLineDelimiter.length();
                    actEnd=       msgBuf.indexOf( multiLineDelimiter, actStart );
                }

                // not found a delimiter? - log the rest
                if ( actEnd < 0 )
                {
                    // single line?
                    if (lineNo == 0)
                    {
                        // append msg to logBuf
                        logBuf._( msgBuf );

                        // now do the logging by calling our derived classes' doLog
                        doTextLog( domain, level, logBuf, indent, caller, -1 );

                        // stop here
                        return;
                    }

                    // store actual end
                    actEnd= msgBuf.length();
                }

                // found a delimiter

                // signal start of multi line log
                if ( lineNo == 0 )
                    notifyMultiLineOp( Phase.BEGIN );

                // in mode 3, 4, meta info is deleted
                if ( lineNo == 0 && (multiLineMsgMode == 3 || multiLineMsgMode == 4) )
                {
                    // log headline in mode 3
                    if ( multiLineMsgMode == 3 )
                    {
                        logBuf._( fmtMultiLineMsgHeadline );
                        autoSizes.actualIndex=  qtyTabStops;
                        doTextLog( domain, level, logBuf, indent, caller, 0 );
                    }

                    // remember zero as offset
                    lbLenBeforeMsgPart= 0;
                }

                // blank out meta information? (do this exactly in 2nd line once)
                if ( multiLineMsgMode == 2)
                {
                    if (lineNo != 0 )
                    {
                        logBuf.clear()._( ESC.EOMETA );
                        autoSizes.actualIndex=  qtyTabStops + qtyESCTabsWritten;
                    }
                }
                else
                {
                    // reset logBuf length to marked position
                    logBuf.setLength_NC( lbLenBeforeMsgPart );
                    autoSizes.actualIndex=  qtyTabStops;
                }

                // append message
                logBuf._( fmtMultiLinePrefix );
                  logBuf._NC( msgBuf, actStart, actEnd - actStart  );
                logBuf._( fmtMultiLineSuffix );
                doTextLog( domain, level, logBuf, indent, multiLineMsgMode != 4 ? caller : null, lineNo );

                // next
                actStart= actEnd + delimLen;
                lineNo++;
            }

            // signal end of multi line log
            if ( lineNo > 0 )
                notifyMultiLineOp( Phase.END );
        }

} // class TextLogger
