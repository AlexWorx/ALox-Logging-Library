// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


/** ************************************************************************************************
 * This namespaces defines class \b TextLogger and its helpers.
 **************************************************************************************************/
package com.aworx.lox.core.textlogger;

import java.util.ArrayList;

import com.aworx.lib.ALIB;
import com.aworx.lib.config.Variable;
import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Phase;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.util.AutoSizes;
import com.aworx.lib.threads.ThreadLock;
import com.aworx.lox.ALox;
import com.aworx.lox.ESC;
import com.aworx.lox.Verbosity;
import com.aworx.lox.core.Domain;
import com.aworx.lox.core.Logger;
import com.aworx.lox.core.ScopeInfo;

/** ************************************************************************************************
 * This class is a still abstract implementation of class Logger which is used as the super class
 * for all textual Logger implementations within \b %ALox, e.g. ConsoleLogger.
 *
 * The class uses two helper classes. One to convert the log message object into a string representation
 * and a second to generate the textual representation of the meta information of a log call.
 * These helpers can be extended and replaced to modify the behavior of TextLogger.
 *
 * The final log message is then passed to the abstract method #logText(). Hence, custom Logger classes
 * that inherited from this class instead of directly from class #Logger, need to implement #logText()
 * instead of implementing #log.
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
        protected AString                   logBuf                             = new AString( 256 );

        /** A buffer for converting the user object(s).     */
        protected AString                   msgBuf                             = new AString( 128 );

        /** Denotes whether this logger writes to the <em>standard output streams</em>.  */
        protected boolean                   usesStdStreams;

        /** Used to avoid to repeatedly register with \b %ALib <em>standard output stream</em> lockers
            when attached to multiple instances of class \b Lox.   */
        protected int                       stdStreamLockRegistrationCounter                     =0;

        /**
         * A list of pairs of strings. Within each log message, the first string of a pair is
         *  searched and replaced by the second string. Very simple, but useful in some cases.
         */
        protected ArrayList<String>         replacements                = new ArrayList<String>();


    // #############################################################################################
    // Public fields
    // #############################################################################################

        /**
         * A helper object to get textual representation of logable objects.
         * If no converter is set when this logger is used, a converter of type
         * \ref com.aworx.lox.core.textlogger.StandardConverter "StandardConverter" is created and used.
         * In the destructor of this class, the current object converter will be deleted.
         *
         * To extend class \b %TextLogger to support logging custom objects, custom converters can
         * set. The preferred alternative is however, to make custom types be formattable
         * by formatter classes used with \b %StandardConverter.
         */
        public  ObjectConverter             converter;

        /**
         * A helper object to format log objects into textual representations. This class incorporates
         * a format string that defines the meta information in the log output. Furthermore, to extend
         * TextLogger, this object can be replaced by custom implementations of it.
         */
        public  MetaInfo                    metaInfo                               = new MetaInfo();

        /**
         * Characters written after each <em>Log Statement</em>.
         * This may be used for example to reset colors and styles.
         * Note, that with multi-line <em>Log Statements</em>, the contents of this field is \b not
         * written at the end of each line, but only at the end of the last line.
         * To define characters that are written after each line of a multi-line
         * <em>Log Statement</em>, field #fmtMultiLineSuffix.
         *
         * Defaults to empty string.
         */
        public    String                    fmtMsgSuffix                                        ="";

        /**
         * Holds a list of values for auto tab positions and field sizes.
         * For each requested value, a corresponding array field is created on the fly.
         * If the format string get's changed and different (new) auto values should be used, then
         * this field should be reset after setting the new format string.
         * The other way round, it is also possible to preset set minimum values for tabs and field
         * sizes and hence avoid the columns growing during the lifetime of the Logger.
         *
         * This field will be read from the
         * configuration variable [ALOX_LOGGERNAME_AUTO_SIZES](../group__GrpALoxConfigVars.html)
         * when the \b %TextLogger that we belong to is attached to a \b %Lox and written back
         * on removal.
         */
        public    AutoSizes                 autoSizes                             = new AutoSizes();

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
        public    int                       multiLineMsgMode                                    = 2;

        /**
         * This is the string interpreted as line delimiter within log messages. If \e nulled, then
         * <c>'\\n'</c>, <c>'\\r'</c> or <c>'\\r\\n'</c> is recognized.<br>
         * Important: Can be set to an empty string, to stop any multi line processing of
         * \b %TextLogger, even the replacements of the delimiter character.
         */
        public    String                    multiLineDelimiter                               = null;

        /**
         * This is the readable (!) separator string, for logging out multi line messages into a
         * single line (#multiLineMsgMode==0).
         */
        public    String                    multiLineDelimiterRepl                          = "\\r";


        /** Headline for multi line messages (depending on #multiLineMsgMode)  . */
        public    String                    fmtMultiLineMsgHeadline="ALox: Multi line message follows: ";

        /**
         *  Prefix for multi line messages. This is also used if multi line messages logging is switched off
         *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
         */
        public    String                    fmtMultiLinePrefix                              = ">> ";

        /**
         * Suffix for multi line messages. This is also used if multi line messages logging is
         * switched off (MultiLineMsgMode == 0) and replacing of a set #multiLineDelimiter
         * takes place.<br>
         * Note that at the end of the last line, in addition #fmtMsgSuffix is added.<br>
         * Defaults to "".
         */
        public    String                    fmtMultiLineSuffix                               = null;

    // #############################################################################################
    // Constructor
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs a TextLogger.
         *
         * @param name           The name of the \e Logger. If empty, it defaults to the type name.
         * @param typeName       The type of the \e Logger.
         * @param usesStdStreams Denotes whether this logger writes to the
         *                       <em>standard output streams</em>.
         ******************************************************************************************/
        protected TextLogger( String name, String typeName, boolean usesStdStreams )
        {
            super( name, typeName );
            this.usesStdStreams= usesStdStreams;
            converter= new com.aworx.lox.core.textlogger.StandardConverter();
        }

    // #############################################################################################
    // Re-implementing interface of grand-parent class SmartLock
    // #############################################################################################

        /** ****************************************************************************************
         * Invokes grand-parent's method and in addition, if field #usesStdStreams is set,
         * registers with
         * \ref com.aworx.lib.ALIB.stdOutputStreamsLock "ALIB.stdOutputStreamsLock"
         *
         * @param newAcquirer The acquirer to add.
         * @return The new number of \e acquirers set.
         ******************************************************************************************/
        @Override @SuppressWarnings ("boxing")
        public int   addAcquirer( ThreadLock newAcquirer )
        {
            // register with ALIB lockers (if not done yet)
            if ( usesStdStreams )
            {
                int  registrationCounter;
                synchronized (this)
                {
                    registrationCounter= this.stdStreamLockRegistrationCounter++;
                }

                if ( registrationCounter == 0 )
                    ALIB.stdOutputStreamsLock.addAcquirer( this );
            }

            Variable variable= new Variable();

            // import autosizes from configuration (last session)
            if ( ALox.config.load(variable.declare( ALox.AUTO_SIZES, getName() )) != 0 )
                autoSizes.importValues( variable.getString() );

            // import "max elapsed time" from configuration (last session)
            if ( ALox.config.load(variable.declare( ALox.MAX_ELAPSED_TIME, getName() )) != 0 )
            {
                long maxInSecs= variable.getInteger();
                Substring attrValue= new Substring();
                if ( variable.getAttribute( "limit", attrValue ) )
                {
                    attrValue.consumeInt();
                    if ( maxInSecs > attrValue.consumedLong )
                        maxInSecs= attrValue.consumedLong;

                }
                metaInfo.maxElapsedTime.fromSeconds( maxInSecs );
            }

            // Variable  <name>_FORMAT / <typeName>_FORMAT:
            com.aworx.lib.ALIB_DBG.ASSERT_WARNING( ALox.FORMAT.defaultValue == null,
                                 "Default value of variable FORMAT should be kept null" );
            if(    0 ==  ALox.config.load(variable.declare( ALox.FORMAT, getName()     ))
                && 0 ==  ALox.config.load(variable.declare( ALox.FORMAT, getTypeName() )) )
            {
                // no variable created, yet. Let's create a 'personal' one on our name
                variable.declare( ALox.FORMAT, getName() );
                variable.add( metaInfo.format            );
                variable.add( metaInfo.verbosityError    );
                variable.add( metaInfo.verbosityWarning  );
                variable.add( metaInfo.verbosityInfo     );
                variable.add( metaInfo.verbosityVerbose  );
                variable.add( fmtMsgSuffix               );
                ALox.config.store(variable);
            }
            else
            {
                                           metaInfo.format          ._()._( variable.getString(0) );
                if( variable.size() >= 2 ) metaInfo.verbosityError  = variable.getString(1).toString();
                if( variable.size() >= 3 ) metaInfo.verbosityWarning= variable.getString(2).toString();
                if( variable.size() >= 4 ) metaInfo.verbosityInfo   = variable.getString(3).toString();
                if( variable.size() >= 5 ) metaInfo.verbosityVerbose= variable.getString(4).toString();
                if( variable.size() >= 6 ) fmtMsgSuffix             = variable.getString(5).toString();
            }

            // Variable  <name>_FORMAT_DATE_TIME / <typeName>_FORMAT_DATE_TIME:
            com.aworx.lib.ALIB_DBG.ASSERT_WARNING( ALox.FORMAT_DATE_TIME.defaultValue == null,
                                 "Default value of variable FORMAT_DATE_TIME should be kept null" );
            if(    0 ==  ALox.config.load(variable.declare( ALox.FORMAT_DATE_TIME, getName()     ))
                && 0 ==  ALox.config.load(variable.declare( ALox.FORMAT_DATE_TIME, getTypeName() )) )
            {
                // no variable created, yet. Let's create a 'personal' one on our name
                variable.declare( ALox.FORMAT_DATE_TIME, getName() );
                variable.add( metaInfo.dateFormat        );
                variable.add( metaInfo.timeOfDayFormat   );
                variable.add( metaInfo.timeElapsedDays   );
                ALox.config.store(variable);
            }
            else
            {
                                           metaInfo.dateFormat      = variable.getString(0).toString();
                if( variable.size() >= 2 ) metaInfo.timeOfDayFormat = variable.getString(1).toString();
                if( variable.size() >= 3 ) metaInfo.timeElapsedDays = variable.getString(2).toString();
            }

            // Variable  <name>FORMAT_TIME_DIFF / <typeName>FORMAT_TIME_DIFF:
            com.aworx.lib.ALIB_DBG.ASSERT_WARNING( ALox.FORMAT_TIME_DIFF.defaultValue == null,
                                 "Default value of variable FORMAT_TIME_DIFF should be kept null" );
            if(    0 ==  ALox.config.load(variable.declare( ALox.FORMAT_TIME_DIFF, getName()     ))
                && 0 ==  ALox.config.load(variable.declare( ALox.FORMAT_TIME_DIFF, getTypeName() )) )
            {
                // no variable created, yet. Let's create a 'personal' one on our name
                variable.declare( ALox.FORMAT_TIME_DIFF, getName() );
                variable.add(metaInfo.timeDiffMinimum);
                variable.add( metaInfo.timeDiffNone   );
                variable.add( metaInfo.timeDiffNanos  );
                variable.add( metaInfo.timeDiffMicros );
                variable.add( metaInfo.timeDiffMillis );
                variable.add( metaInfo.timeDiffSecs   );
                variable.add( metaInfo.timeDiffMins   );
                variable.add( metaInfo.timeDiffHours  );
                variable.add( metaInfo.timeDiffDays   );
                ALox.config.store(variable);
            }
            else
            {
                                           metaInfo.timeDiffMinimum= variable.getInteger   (0);
                if( variable.size() >= 2 ) metaInfo.timeDiffNone   = variable.getString(1).toString();
                if( variable.size() >= 3 ) metaInfo.timeDiffNanos  = variable.getString(2).toString();
                if( variable.size() >= 4 ) metaInfo.timeDiffMicros = variable.getString(3).toString();
                if( variable.size() >= 5 ) metaInfo.timeDiffMillis = variable.getString(4).toString();
                if( variable.size() >= 6 ) metaInfo.timeDiffSecs   = variable.getString(5).toString();
                if( variable.size() >= 7 ) metaInfo.timeDiffMins   = variable.getString(6).toString();
                if( variable.size() >= 8 ) metaInfo.timeDiffHours  = variable.getString(7).toString();
                if( variable.size() >= 9 ) metaInfo.timeDiffDays   = variable.getString(8).toString();
            }

            // Variable  <name>FORMAT_MULTILINE / <typeName>FORMAT_MULTILINE:
            com.aworx.lib.ALIB_DBG.ASSERT_WARNING( ALox.FORMAT_MULTILINE.defaultValue == null,
                                 "Default value of variable FORMAT_MULTILINE should be kept null" );
            if(    0 ==  ALox.config.load(variable.declare( ALox.FORMAT_MULTILINE, getName()     ))
                && 0 ==  ALox.config.load(variable.declare( ALox.FORMAT_MULTILINE, getTypeName() )) )
            {
                // no variable created, yet. Let's create a 'personal' one on our name
                variable.declare( ALox.FORMAT_MULTILINE, getName() );
                variable.add( multiLineMsgMode );
                variable.add( fmtMultiLineMsgHeadline   );
                variable.add( fmtMultiLinePrefix );
                variable.add( fmtMultiLineSuffix );
                ALox.config.store(variable);
            }
            else
            {
                                           multiLineMsgMode=        (int) variable.getInteger(0)  ;
                if( variable.size() >= 2 ) fmtMultiLineMsgHeadline= variable.getString(1).toString();
                if( variable.size() >= 3 ) fmtMultiLinePrefix     = variable.getString(2).toString();
                if( variable.size() >= 4 ) fmtMultiLineSuffix     = variable.getString(3).toString();
                if( variable.size() >= 5 ) { if (variable.getString(4).equals( "nulled" , Case.IGNORE ) )
                                                multiLineDelimiter= null;
                                             else
                                                multiLineDelimiter= variable.getString(4).toString();
                                           }
                if( variable.size() >= 6 ) multiLineDelimiterRepl = variable.getString(5).toString();
            }

            // Variable  <name>FORMAT_REPLACEMENTS / <typeName>FORMAT_REPLACEMENTS:
            com.aworx.lib.ALIB_DBG.ASSERT_WARNING( ALox.REPLACEMENTS.defaultValue == null,
                                 "Default value of variable FORMAT_MULTILINE should be kept null" );
            if(    0 !=  ALox.config.load(variable.declare( ALox.REPLACEMENTS, getName()     ))
                || 0 !=  ALox.config.load(variable.declare( ALox.REPLACEMENTS, getTypeName() )) )
            {
                for( int i= 0; i< variable.size() / 2 ; i++ )
                {
                    AString searchString=  variable.getString(i * 2);
                    AString replaceString= variable.getString(i * 2 + 1);
                    if( searchString != null  && replaceString != null )
                        setReplacement( searchString.toString(), replaceString.toString() );
                }
            }

            // call parents' implementation
            return super.addAcquirer( newAcquirer );
        }

        /** ****************************************************************************************
         * Invokes grand-parent's method and in addition, de-registers with
         * \ref com.aworx.lib.ALIB.stdOutputStreamsLock "ALIB.stdOutputStreamsLock".
         * @param acquirer The acquirer to remove.
         * @return The new number of \e acquirers set.
         ******************************************************************************************/
        @Override
        public int   removeAcquirer( ThreadLock acquirer )
        {
            // de-register with ALIB lockers (if not done yet)
            if ( usesStdStreams )
            {
                int  registrationCounter;
                synchronized (this)
                {
                    registrationCounter= --this.stdStreamLockRegistrationCounter;
                }

                if ( registrationCounter == 0 )
                    ALIB.stdOutputStreamsLock.removeAcquirer( this );
            }

            Variable variable= new Variable();

            // export autosizes to configuration
            variable.declare( ALox.AUTO_SIZES, getName() );
            autoSizes.exportValues( variable.add() );
            ALox.config.store(variable);

            // export "max elapsed time" to configuration
            variable.declare( ALox.MAX_ELAPSED_TIME, getName() );
            AString destVal=  ALox.config.load(variable) != 0  ?  variable.getString()
                                                               :  variable.add();
            destVal._()._( metaInfo.maxElapsedTime.inSeconds() );
            ALox.config.store(variable);

            // call parents' implementation
            return super.removeAcquirer( acquirer );
        }

    // #############################################################################################
    // Public interface
    // #############################################################################################

        /** ****************************************************************************************
         * Adds the given pair of replacement strings. If searched string already exists, the
         * current replacement string gets replaced. If the replacement string is \c null,
         * nothing is set and a previously set replacement definition becomes unset.
         *
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

                    replacements.remove( i );
                    replacements.remove( i );
                    return;
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
         * Removes all pairs of searched strings and their replacement value.
         ******************************************************************************************/
        public void  clearReplacements()
        {
            replacements.clear();
        }


    // #############################################################################################
    // Abstract methods (introduced)
    // #############################################################################################

        /** ****************************************************************************************
         * This abstract method introduced by this class "replaces" the abstract method #log
         * of parent class Logger which this class implements. In other words, descendants of this
         * class need to override this method instead of \b %log. This class %TextLogger is
         * responsible for generating meta information, doing text replacements, handle multi-line
         * messages, etc. and provides the textual representation of the whole log contents
         * to descendants using this method.
         *
         * @param domain        The <em>Log Domain</em>.
         * @param verbosity     The verbosity. This has been checked to be active already on this
         *                      stage and is provided to be able to be logged out only.
         * @param msg           The log message.
         * @param scope         Information about the scope of the <em>Log Statement</em>.
         * @param lineNumber    The line number of a multi-line message, starting with 0.
         *                      For single line messages this is -1.
         ******************************************************************************************/
        abstract protected void logText( Domain      domain,     Verbosity verbosity,
                                         AString     msg,
                                         ScopeInfo   scope,      int       lineNumber  );

        /** ****************************************************************************************
         * Abstract method to be implemented by descendants. This message is called only when
         * multi-line messages are logged. It is called exactly once before a series of #logText
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
         * This is the implementation of the abstract method inherited from class Logger
         * that executes a log.<br>
         * This class implements this method and but exposes the new abstract method #logText.
         * This mechanism allows this class to do various things that are standard to Loggers
         * of type TextLogger. For example, meta information of the log invocation is formatted and
         * string replacements are performed. This way, descendants of this class will consumeChar
         * a ready to use log buffer with all meta information and contents of all objects to be
         * included and their primary obligation is to copy the content into a corresponding
         * output stream.
         *
         * @param domain    The <em>Log Domain</em>.
         * @param verbosity The verbosity.
         * @param logables  The list of objects to log.
         * @param scope     Information about the scope of the <em>Log Statement</em>.
         ******************************************************************************************/
        @Override public void log( Domain            domain,
                                   Verbosity         verbosity,
                                   ArrayList<Object> logables,
                                   ScopeInfo         scope       )
        {
            // check
            if ( converter == null )
                converter= new StandardConverter();

            // we store the current msgBuf length and reset the buffer to this length when exiting.
            // This allows recursive calls! Recursion might happen with the evaluation of the
            // logables (in the next line!)
            int msgBufStartLength= msgBuf.length();
            converter.convertObjects( msgBuf, logables );

            // replace strings in message
            for ( int i= 0 ; i < replacements.size() -1 ; i+= 2 )
                msgBuf.searchAndReplace( replacements.get( i ),
                                         replacements.get( i + 1 ), msgBufStartLength );

            // setup log buffer with meta info << ESC.EOMETA
            logBuf.clear();
            autoSizes.start();
            int qtyESCTabsWritten=  metaInfo.write( this, logBuf, domain, verbosity, scope );
            logBuf._NC( ESC.EOMETA );

            // check for empty messages
            if ( msgBuf.length() == msgBufStartLength )
            {
                // log empty msg and quit
                logBuf._NC( fmtMsgSuffix );
                if (usesStdStreams) ALIB.stdOutputStreamsLock.acquire();
                    logText( domain, verbosity, logBuf, scope, -1 );
                if (usesStdStreams) ALIB.stdOutputStreamsLock.release();
                return;
            }

            // single line output
            if ( multiLineMsgMode == 0 )
            {
                // replace line separators
                int cntReplacements= 0;
                if ( multiLineDelimiter != null )
                    cntReplacements+= msgBuf.searchAndReplace( multiLineDelimiter, multiLineDelimiterRepl, msgBufStartLength );
                else
                {
                    cntReplacements+= msgBuf.searchAndReplace( "\r\n",  multiLineDelimiterRepl, msgBufStartLength );
                    cntReplacements+= msgBuf.searchAndReplace( "\r",    multiLineDelimiterRepl, msgBufStartLength );
                    cntReplacements+= msgBuf.searchAndReplace( "\n",    multiLineDelimiterRepl, msgBufStartLength );
                }

                // append msg to logBuf
                if ( cntReplacements == 0 )
                {
                    logBuf._NC( msgBuf, msgBufStartLength, msgBuf.length() - msgBufStartLength );
                }
                else
                {
                    logBuf._( fmtMultiLinePrefix );
                      logBuf._NC( msgBuf, msgBufStartLength, msgBuf.length() - msgBufStartLength );
                    logBuf._( fmtMultiLineSuffix );
                }
                logBuf._NC( fmtMsgSuffix );

                // now do the logging by calling our derived classes' logText
                logText( domain, verbosity, logBuf, scope, -1 );

                // stop here
                msgBuf.setLength( msgBufStartLength );
                return;
            }

            // multiple line output
            int qtyTabStops=        autoSizes.actualIndex;
            int actStart=           msgBufStartLength;
            int lineNo=             0;
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
                    delimLen= 1;
                    actEnd= msgBuf.indexOf( '\n', actStart );
                    if( actEnd > actStart )
                    {
                        if( msgBuf.charAt(actEnd - 1) == '\r' )
                        {
                            actEnd--;
                            delimLen= 2;
                        }
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
                        logBuf._NC( msgBuf, msgBufStartLength, msgBuf.length() - msgBufStartLength );
                        logBuf._NC( fmtMsgSuffix );

                        // now do the logging by calling our derived classes' logText
                        if (usesStdStreams) ALIB.stdOutputStreamsLock.acquire();
                            logText( domain, verbosity, logBuf, scope, -1 );
                        if (usesStdStreams) ALIB.stdOutputStreamsLock.release();

                        // stop here
                        msgBuf.setLength( msgBufStartLength );
                        return;
                    }

                    // store actual end
                    actEnd= msgBuf.length();
                }

                // found a delimiter

                // signal start of multi line log
                if ( lineNo == 0 )
                {
                    if (usesStdStreams) ALIB.stdOutputStreamsLock.acquire();
                    notifyMultiLineOp( Phase.BEGIN );
                }

                // in mode 3, 4, meta info is deleted
                if ( lineNo == 0 && (multiLineMsgMode == 3 || multiLineMsgMode == 4) )
                {
                    // log headline in mode 3
                    if ( multiLineMsgMode == 3 )
                    {
                        logBuf._( fmtMultiLineMsgHeadline );
                        autoSizes.actualIndex=  qtyTabStops;
                        logText( domain, verbosity, logBuf, scope, 0 );
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
                actStart= actEnd + delimLen;
                if ( actStart >= msgBuf.length() )
                    logBuf._NC( fmtMsgSuffix );
                logText( domain, verbosity, logBuf, scope, lineNo );

                // next
                lineNo++;
            }

            // signal end of multi line log
            if ( lineNo > 0 )
            {
                notifyMultiLineOp( Phase.END );
                if (usesStdStreams) ALIB.stdOutputStreamsLock.release();
            }

            msgBuf.setLength( msgBufStartLength );
        }

} // class TextLogger
