
// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using cs.aworx.lib;
using cs.aworx.lib.strings;
using cs.aworx.lib.strings.util;
using cs.aworx.lib.lang;
using cs.aworx.lib.threads;
using cs.aworx.lib.config;
using cs.aworx.lox;
using cs.aworx.lox.core;

/** ************************************************************************************************
 * This namespaces defines class \b TextLogger and its helpers.
**************************************************************************************************/
namespace cs.aworx.lox.core.textlogger
{

/** ************************************************************************************************
 *  This class is a still abstract implementation of class Logger which is used as the super class
 *  for all textual Logger implementations within ALox, e.g. ConsoleLogger.
 *
 *  The class uses two helper classes. One to convert the log message object into a string representation
 *  and a second to generate the textual representation of the meta information of a log call.
 *  These helpers can be extended and replaced to modify the behavior of TextLogger.
 *
 *  The final log message is then passed to the abstract method #logText(). Hence, custom Logger classes
 *  that inherited from this class instead of directly from class #Logger, need to implement #logText()
 *  instead of implementing #Log.
 *
 *  Class TextLogger supports multi line log outputs. Such multi line log outputs can be configured to
 *  be logged in different ways. See #MultiLineMsgMode for more information.
 **************************************************************************************************/
public abstract class TextLogger : Logger
{

    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DBG_LOG || ALOX_REL_LOG)

        // Empty constructor
        protected TextLogger()
        {
        }

    #else

    // #############################################################################################
    // Internal fields
    // #############################################################################################

    /**  The internal log Buffer. */
    protected AString                   logBuf                                  =new AString( 256 );

    /** A buffer for converting the user object(s)      */
    protected AString                   msgBuf                                  =new AString( 128 );

    /** Denotes whether this logger writes to the <em>standard output streams</em>.  */
    protected bool                      usesStdStreams;

    /** Used to avoid to repeatedly register with ALib <em>standard output stream</em> lockers
        when attached to multiple instances of class \b Lox.   */
    protected int                       stdStreamLockRegistrationCounter                                         =0;

    /**
     * A list of pairs of strings. Within each log message, the first string of a pair is
     *  searched and replaced by the second string. Very simple, but useful in some cases.
     */
    protected List<String>              replacements                            =new List<String>();

    // #############################################################################################
    // Public fields
    // #############################################################################################

    /**
     * A helper object to get textual representation of logable objects.
     * If no converter is set when this logger is used, a converter of type
     * \ref cs::aworx::lox::core::textlogger::StandardConverter "StandardConverter" is created and used.
     * In the destructor of this class, the current object converter will be deleted.
     *
     * To extend class \b %TextLogger to support logging custom objects, custom converters can
     * set. The preferred alternative is however, to make custom types be formattable
     * by formatter classes used with \b %StandardConverter.
     */
    public    ObjectConverter          Converter;

    /**
     * A helper object to format log objects into textual representations. This class incorporates
     * a format string that defines the meta information in the log output. Furthermore, to extend
     * TextLogger, this object can be replaced by custom implementations of it.
     */
    public    MetaInfo                  MetaInfo                                    =new MetaInfo();

    /**
     * Characters written after each <em>Log Statement</em>.
     * This may be used for example to reset colors and styles.
     * Note, that with multi-line <em>Log Statements</em>, the contents of this field is \b not
     * written at the end of each line, but only at the end of the last line.
     * To define characters that are written after each line of a multi-line
     * <em>Log Statement</em>, field #FmtMultiLineSuffix.
     *
     * Defaults to empty string.
     */
    public    String                    FmtMsgSuffix                                            ="";

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
    public    AutoSizes                 AutoSizes                                = new AutoSizes();


    /**
     * Determines if multi line messages should be split into different log lines.
     * Possible values are:
     *
     * - 0: No line split is performed, delimiters can be replaced by readable delimiters
     *      (depending on setting of #MultiLineDelimiter and # MultiLineDelimiterRepl).
     *
     * - 1: Each log line contains all meta information
     *
     * - 2: Starting with second log line, meta information is replaced by blanks  (default)
     *
     * - 3: The headline #FmtMultiLineMsgHeadline is logged and all lines of the multi line
     *      text are logged at position zero (without further meta information)
     *
     * - 4: Just the multi line text is logged, starting at column zero (no meta information
     *      is logged)
     */
    public    int                       MultiLineMsgMode                                         =2;

    /**
     * This is the string interpreted as line delimiter within log messages. If \e nulled, then
     * <c>'\\n'</c>, <c>'\\r'</c> or <c>'\\r\\n'</c> is recognized.<br>
     * Important: Can be set to an empty string, to stop any multi line processing of
     * \b %TextLogger, even the replacements of the delimiter character.
     */
    public    String                    MultiLineDelimiter                                    =null;

    /**
     * This is the readable (!) separator string, for logging out multi line messages into a
     * single line (#MultiLineMsgMode==0).
     */
    public    String                    MultiLineDelimiterRepl  ="\\r";


    /// Headline for multi line messages (depending on #MultiLineMsgMode).
    public    String                    FmtMultiLineMsgHeadline ="ALox: Multi line message follows: ";

    /**
     *  Prefix for multi line messages. This is also used if multi line messages logging is switched off
     *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
     */
    public    String                    FmtMultiLinePrefix                                   =">> ";

    /**
     * Suffix for multi line messages. This is also used if multi line messages logging is
     * switched off (MultiLineMsgMode == 0) and replacing of a set #MultiLineDelimiter
     * takes place.<br>
     * Note that at the end of the last line, in addition #FmtMsgSuffix is added.<br>
     * Defaults to "".
     */
    public    String                    FmtMultiLineSuffix                                    =null;

    // #############################################################################################
    // Constructor
    // #############################################################################################
    /** ********************************************************************************************
     * Constructs a TextLogger.
     * @param name           The name of the \e Logger. If empty, it defaults to the type name.
     * @param typeName       The type of the \e Logger.
     * @param usesStdStreams Denotes whether this logger writes to the
     *                       <em>standard output streams</em>.
     **********************************************************************************************/
    protected TextLogger(String name, String typeName, bool usesStdStreams )
        : base ( name, typeName )
    {
        this.usesStdStreams= usesStdStreams;
        Converter= new StandardConverter();
    }

    // #############################################################################################
    // Reimplementing interface of grand-parent class SmartLock
    // #############################################################################################

        /** ****************************************************************************************
         * Invokes grand-parent's method and in addition, if field #usesStdStreams is set,
         * registers with
         * \ref cs::aworx::lib::ALIB::StdOutputStreamsLock "ALIB.StdOutputStreamsLock", respectively
         *
         * @param newAcquirer The acquirer to add.
         * @return The new number of \e acquirers set.
         ******************************************************************************************/
        public override int   AddAcquirer( ThreadLock newAcquirer )
        {
            // register with ALIB lockers (if not done yet)
            if ( usesStdStreams )
            {
                int  stdStreamLockRegistrationCounter;
                lock(this)
                {
                    stdStreamLockRegistrationCounter= this.stdStreamLockRegistrationCounter++;
                }
                if ( stdStreamLockRegistrationCounter == 0 )
                    ALIB.StdOutputStreamsLock.AddAcquirer( this );
            }

            Variable variable= new Variable();

            // import autosizes from configuration (last session)
            if ( variable.Define( ALox.AUTO_SIZES, GetName()).Load() != 0 )
                AutoSizes.Import( variable.GetString() );

            // import "max elapsed time" from configuration (last session)
            if ( variable.Define( ALox.MAX_ELAPSED_TIME, GetName()).Load()  != 0 )
            {
                long maxInSecs= variable.GetInteger();
                Substring attrValue= new Substring();
                if ( variable.GetAttribute( "limit", attrValue ) )
                {
                    long maxMax;
                    attrValue.ConsumeInt( out maxMax );
                    if ( maxInSecs > maxMax )
                        maxInSecs= maxMax;
                }
                MetaInfo.MaxElapsedTime.FromSeconds( maxInSecs );
            }

            // Variable  <name>_FORMAT / <typeName>_FORMAT:
            ALIB_DBG.ASSERT_WARNING( ALox.FORMAT.DefaultValue == null,
                                 "Default value of variable FORMAT should be kept null" );
            if(    0 ==  variable.Define( ALox.FORMAT, GetName()     ).Load()
                && 0 ==  variable.Define( ALox.FORMAT, GetTypeName() ).Load() )
            {
                // no variable created, yet. Let's create a 'personal' one on our name
                variable.Define( ALox.FORMAT, GetName() );
                variable.Add( MetaInfo.Format            );
                variable.Add( MetaInfo.VerbosityError    );
                variable.Add( MetaInfo.VerbosityWarning  );
                variable.Add( MetaInfo.VerbosityInfo     );
                variable.Add( MetaInfo.VerbosityVerbose  );
                variable.Add( FmtMsgSuffix               );
                variable.Store();
            }
            else
            {
                                           MetaInfo.Format          ._()._( variable.GetString(0) );
                if( variable.Size() >= 2 ) MetaInfo.VerbosityError  = variable.GetString(1).ToString();
                if( variable.Size() >= 3 ) MetaInfo.VerbosityWarning= variable.GetString(2).ToString();
                if( variable.Size() >= 4 ) MetaInfo.VerbosityInfo   = variable.GetString(3).ToString();
                if( variable.Size() >= 5 ) MetaInfo.VerbosityVerbose= variable.GetString(4).ToString();
                if( variable.Size() >= 6 ) FmtMsgSuffix             = variable.GetString(5).ToString();
            }

            // Variable  <name>_FORMAT_DATE_TIME / <typeName>_FORMAT_DATE_TIME:
            ALIB_DBG.ASSERT_WARNING( ALox.FORMAT_DATE_TIME.DefaultValue == null,
                                 "Default value of variable FORMAT_DATE_TIME should be kept null" );
            if(    0 ==  variable.Define( ALox.FORMAT_DATE_TIME, GetName()     ).Load()
                && 0 ==  variable.Define( ALox.FORMAT_DATE_TIME, GetTypeName() ).Load() )
            {
                // no variable created, yet. Let's create a 'personal' one on our name
                variable.Define( ALox.FORMAT_DATE_TIME, GetName() );
                variable.Add( MetaInfo.DateFormat        );
                variable.Add( MetaInfo.TimeOfDayFormat   );
                variable.Add( MetaInfo.TimeElapsedDays   );
                variable.Store();
            }
            else
            {
                                           MetaInfo.DateFormat      = variable.GetString(0).ToString();
                if( variable.Size() >= 2 ) MetaInfo.TimeOfDayFormat = variable.GetString(1).ToString();
                if( variable.Size() >= 3 ) MetaInfo.TimeElapsedDays = variable.GetString(2).ToString();
            }

            // Variable  <name>FORMAT_TIME_DIFF / <typeName>FORMAT_TIME_DIFF:
            ALIB_DBG.ASSERT_WARNING( ALox.FORMAT_TIME_DIFF.DefaultValue == null,
                                 "Default value of variable FORMAT_TIME_DIFF should be kept null" );
            if(    0 ==  variable.Define( ALox.FORMAT_TIME_DIFF, GetName()     ).Load()
                && 0 ==  variable.Define( ALox.FORMAT_TIME_DIFF, GetTypeName() ).Load() )
            {
                // no variable created, yet. Let's create a 'personal' one on our name
                variable.Define( ALox.FORMAT_TIME_DIFF, GetName() );
                variable.Add( MetaInfo.TimeDiffMinimum);
                variable.Add( MetaInfo.TimeDiffNone   );
                variable.Add( MetaInfo.TimeDiffNanos  );
                variable.Add( MetaInfo.TimeDiffMicros );
                variable.Add( MetaInfo.TimeDiffMillis );
                variable.Add( MetaInfo.TimeDiffSecs   );
                variable.Add( MetaInfo.TimeDiffMins   );
                variable.Add( MetaInfo.TimeDiffHours  );
                variable.Add( MetaInfo.TimeDiffDays   );
                variable.Store();
            }
            else
            {
                                           MetaInfo.TimeDiffMinimum= variable.GetInteger   (0);
                if( variable.Size() >= 2 ) MetaInfo.TimeDiffNone   = variable.GetString(1).ToString();
                if( variable.Size() >= 3 ) MetaInfo.TimeDiffNanos  = variable.GetString(2).ToString();
                if( variable.Size() >= 4 ) MetaInfo.TimeDiffMicros = variable.GetString(3).ToString();
                if( variable.Size() >= 5 ) MetaInfo.TimeDiffMillis = variable.GetString(4).ToString();
                if( variable.Size() >= 6 ) MetaInfo.TimeDiffSecs   = variable.GetString(5).ToString();
                if( variable.Size() >= 7 ) MetaInfo.TimeDiffMins   = variable.GetString(6).ToString();
                if( variable.Size() >= 8 ) MetaInfo.TimeDiffHours  = variable.GetString(7).ToString();
                if( variable.Size() >= 9 ) MetaInfo.TimeDiffDays   = variable.GetString(8).ToString();
            }

            // Variable  <name>FORMAT_MULTILINE / <typeName>FORMAT_MULTILINE:
            ALIB_DBG.ASSERT_WARNING( ALox.FORMAT_MULTILINE.DefaultValue == null,
                                 "Default value of variable FORMAT_MULTILINE should be kept null" );
            if(    0 ==  variable.Define( ALox.FORMAT_MULTILINE, GetName()     ).Load()
                && 0 ==  variable.Define( ALox.FORMAT_MULTILINE, GetTypeName() ).Load() )
            {
                // no variable created, yet. Let's create a 'personal' one on our name
                variable.Define( ALox.FORMAT_MULTILINE, GetName() );
                variable.Add( MultiLineMsgMode );
                variable.Add ( FmtMultiLineMsgHeadline   );
                variable.Add ( FmtMultiLinePrefix  );
                variable.Add ( FmtMultiLineSuffix );
                variable.Store();
            }
            else
            {
                                           MultiLineMsgMode=        (int) variable.GetInteger(0)  ;
                if( variable.Size() >= 2 ) FmtMultiLineMsgHeadline= variable.GetString(1).ToString();
                if( variable.Size() >= 3 ) FmtMultiLinePrefix     = variable.GetString(2).ToString();
                if( variable.Size() >= 4 ) FmtMultiLineSuffix     = variable.GetString(3).ToString();
                if( variable.Size() >= 5 ) { if (variable.GetString(4).Equals( "nulled" , Case.Ignore ) )
                                                MultiLineDelimiter= null;
                                             else
                                                MultiLineDelimiter= variable.GetString(4).ToString();
                                           }
                if( variable.Size() >= 6 ) MultiLineDelimiterRepl = variable.GetString(5).ToString();
            }

            // Variable  <name>FORMAT_REPLACEMENTS / <typeName>FORMAT_REPLACEMENTS:
            ALIB_DBG.ASSERT_WARNING( ALox.REPLACEMENTS.DefaultValue == null,
                                 "Default value of variable FORMAT_MULTILINE should be kept null" );
            if(    0 !=  variable.Define( ALox.REPLACEMENTS, GetName()     ).Load()
                || 0 !=  variable.Define( ALox.REPLACEMENTS, GetTypeName() ).Load() )
            {
                for( int i= 0; i< variable.Size() / 2 ; i++ )
                {
                    AString searchString=  variable.GetString(i * 2);
                    AString replaceString= variable.GetString(i * 2 + 1);
                    if( searchString != null  && replaceString != null )
                        SetReplacement( searchString.ToString(), replaceString.ToString() );
                }
            }

            // call parents' implementation
            return base.AddAcquirer( newAcquirer );
        }

        /** ****************************************************************************************
         * Invokes grand-parent's method and in addition, de-registers with
         * \ref cs::aworx::lib::ALIB::StdOutputStreamsLock "ALIB.StdOutputStreamsLock"
         * @param acquirer The acquirer to remove.
         * @return The new number of \e acquirers set.
         ******************************************************************************************/
        public override int   RemoveAcquirer( ThreadLock acquirer )
        {
            // d-register with ALIB lockers (if not done yet)
            if ( usesStdStreams )
            {
                int  stdStreamLockRegistrationCounter;
                lock(this)
                {
                    stdStreamLockRegistrationCounter= --this.stdStreamLockRegistrationCounter;
                }
                if ( stdStreamLockRegistrationCounter == 0 )
                    ALIB.StdOutputStreamsLock.RemoveAcquirer( this );
            }

            Variable variable= new Variable();

            // export autosizes to configuration
            variable.Define( ALox.AUTO_SIZES, GetName() );
            AutoSizes.Export( variable.Add() );
            variable.Store();

            // export "max elapsed time" to configuration
            variable.Define( ALox.MAX_ELAPSED_TIME, GetName() );
            AString destVal=  variable.Load() != 0  ?  variable.GetString()
                                                    :  variable.Add();
            destVal._()._( MetaInfo.MaxElapsedTime.InSeconds() );
            variable.Store();

            // call parents' implementation
            return base.RemoveAcquirer( acquirer );
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
        public void  SetReplacement( String searched, String replacement )
        {
            // if exists, replace replacement
            for( int i= 0; i < replacements.Count; i+= 2)
            {
                String s= replacements[i];
                if ( s.Equals( searched ) )
                {
                    if ( replacement != null )
                    {
                        i++;
                        replacements[i]= replacement;
                        return;
                    }

                    replacements.RemoveAt( i );
                    replacements.RemoveAt( i );
                    return;
                }
            }

            // append at the end
            if ( replacement != null )
            {
                replacements.Add( searched    );
                replacements.Add( replacement );
            }
        }

        /** ****************************************************************************************
         * Removes all pairs of searched strings and their replacement value.
         ******************************************************************************************/
        public void  ClearReplacements()
        {
            replacements.Clear();
        }

    // #############################################################################################
    // Abstract methods (introduced)
    // #############################################################################################

        /** ****************************************************************************************
         * This abstract method introduced by this class "replaces" the abstract method #Log
         * of parent class Logger which this class implements. In other words, descendants of this
         * class need to overwrite this method instead of \b %Log. This class %TextLogger is
         * responsible for generating meta information, doing text replacements, handle multi-line
         * messages, etc. and provides the textual representation of the whole log contents
         * to descendants using this method.
         *
         * @param domain     The <em>Log Domain</em>.
         * @param verbosity  The verbosity. This has been checked to be active already on this
         *                   stage and is provided to be able to be logged out only.
         * @param msg        The log message.
         * @param scope      Information about the scope of the <em>Log Statement</em>.
         * @param lineNumber The line number of a multi-line message, starting with 0.
         *                   For single line messages this is -1.
         ******************************************************************************************/
        abstract protected void logText(  Domain        domain,     Verbosity verbosity,
                                          AString       msg,
                                          ScopeInfo     scope,      int       lineNumber);

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
         * string replacements are performed. This way, descendants of this class will consume
         * a ready to use log buffer with all meta information and contents of all objects to be
         * included and their primary obligation is to copy the content into a corresponding
         * output stream.
         *
         * @param domain    The <em>Log Domain</em>.
         * @param verbosity The verbosity. This has been checked to be active already on this
         *                  stage and is provided to be able to be logged out only.
         * @param logables  The list of objects to log.
         * @param scope     Information about the scope of the <em>Log Statement</em>..
         ******************************************************************************************/
        override public void Log(  Domain        domain,
                                   Verbosity     verbosity,
                                   List<Object>  logables,
                                   ScopeInfo     scope  )
        {
            // check
            if ( Converter == null )
                Converter= new StandardConverter();

            // we store the current msgBuf length and reset the buffer to this length when exiting.
            // This allows recursive calls! Recursion might happen with the evaluation of the
            // logables (in the next line!)
            int msgBufStartLength= msgBuf.Length();
            Converter.ConvertObjects( msgBuf, logables );

            // replace strings in message
            for ( int i= 0; i < replacements.Count ; i+=2 )
                msgBuf.SearchAndReplace( replacements[i],
                                         replacements[i + 1], msgBufStartLength );

            // setup log buffer with meta info << ESC::EOMETA
            logBuf.Clear();
            AutoSizes.Start();
            int qtyESCTabsWritten=  MetaInfo.Write( this, logBuf, domain, verbosity, scope );
            logBuf._NC( ESC.EOMETA );

            // check for empty messages
            if ( msgBuf.Length() == msgBufStartLength )
            {
                // log empty msg and quit
                logBuf._NC( FmtMsgSuffix );
                if (usesStdStreams) ALIB.StdOutputStreamsLock.Acquire();
                    logText( domain, verbosity, logBuf, scope, -1 );
                if (usesStdStreams) ALIB.StdOutputStreamsLock.Release();
                return;
            }

            // single line output
            if ( MultiLineMsgMode == 0 )
            {
                // replace line separators
                int cntReplacements=0;
                if ( MultiLineDelimiter != null )
                    cntReplacements+=msgBuf.SearchAndReplace( MultiLineDelimiter,    MultiLineDelimiterRepl, msgBufStartLength );
                else
                {
                    cntReplacements+=msgBuf.SearchAndReplace( "\r\n", MultiLineDelimiterRepl, msgBufStartLength );
                    cntReplacements+=msgBuf.SearchAndReplace( "\r"  , MultiLineDelimiterRepl, msgBufStartLength );
                    cntReplacements+=msgBuf.SearchAndReplace( "\n"  , MultiLineDelimiterRepl, msgBufStartLength );
                }

                // append msg to logBuf
                if ( cntReplacements == 0 )
                {
                    logBuf._( msgBuf, msgBufStartLength, msgBuf.Length() - msgBufStartLength );
                }
                else
                {
                    logBuf._( FmtMultiLinePrefix );
                    logBuf._( msgBuf, msgBufStartLength, msgBuf.Length() - msgBufStartLength );
                    logBuf._( FmtMultiLineSuffix );
                }
                logBuf._NC( FmtMsgSuffix );

                // now do the logging by calling our derived classes' logText
                logText( domain, verbosity, logBuf, scope, -1 );

                // stop here
                msgBuf.SetLength( msgBufStartLength );
                return;
            }

            // multiple line output
            int qtyTabStops=        AutoSizes.ActualIndex;
            int actStart=           msgBufStartLength;
            int lineNo=             0;
            int lbLenBeforeMsgPart= logBuf.Length();

            // loop over lines in msg
            while ( actStart < msgBuf.Length() )
            {
                // find next end
                int delimLen;
                int actEnd;

                // no delimiter given: search "\r\n", then '\r', then '\n'
                if ( String.IsNullOrEmpty( MultiLineDelimiter ) )
                {
                    delimLen= 1;
                    actEnd= msgBuf.IndexOf( '\n', actStart );
                    if( actEnd > actStart )
                    {
                        if( msgBuf.CharAt(actEnd - 1) == '\r' )
                        {
                            actEnd--;
                            delimLen= 2;
                        }
                    }
                }
                else
                {
                    delimLen=MultiLineDelimiter.Length;
                    actEnd=msgBuf.IndexOf( MultiLineDelimiter, actStart );
                }

                // not found a delimiter? - log the rest
                if ( actEnd < 0 )
                {
                    // single line?
                    if ( lineNo == 0 )
                    {
                        // append msg to logBuf
                        logBuf._NC( msgBuf, msgBufStartLength, msgBuf.Length() - msgBufStartLength );
                        logBuf._NC( FmtMsgSuffix );

                        // now do the logging by calling our derived classes' logText
                        if (usesStdStreams) ALIB.StdOutputStreamsLock.Acquire();
                            logText( domain, verbosity, logBuf, scope, -1 );
                        if (usesStdStreams) ALIB.StdOutputStreamsLock.Release();

                        // stop here
                        msgBuf.SetLength( msgBufStartLength );
                        return;
                    }

                    // store actual end
                    actEnd= msgBuf.Length();
                }

                // found a delimiter

                // signal start of multi line log
                if ( lineNo == 0 )
                {
                    if (usesStdStreams) ALIB.StdOutputStreamsLock.Acquire();
                    notifyMultiLineOp( Phase.Begin );
                }

                // in mode 3, 4, meta info is deleted
                if ( lineNo == 0 && ( MultiLineMsgMode == 3 || MultiLineMsgMode == 4 ) )
                {
                    // log headline in mode 3
                    if ( MultiLineMsgMode == 3 )
                    {
                        logBuf._( FmtMultiLineMsgHeadline );
                        AutoSizes.ActualIndex=  qtyTabStops;
                        logText( domain, verbosity, logBuf, scope, 0 );
                    }

                    // remember zero as offset
                    lbLenBeforeMsgPart=0;
                }

                // blank out meta information? (do this exactly in 2nd line once)
                if ( MultiLineMsgMode == 2 )
                {
                    if (lineNo != 0 )
                    {
                        logBuf.Clear()._( ESC.EOMETA );
                        AutoSizes.ActualIndex=  qtyTabStops + qtyESCTabsWritten;
                    }
                }
                // reset logBuf length to marked position
                else
                {
                    logBuf.SetLength_NC( lbLenBeforeMsgPart );
                    AutoSizes.ActualIndex=  qtyTabStops;
                }

                // append message
                logBuf._( FmtMultiLinePrefix );
                logBuf._NC( msgBuf, actStart, actEnd - actStart  );
                logBuf._( FmtMultiLineSuffix );
                logText( domain, verbosity, logBuf, scope, lineNo );

                // next
                actStart= actEnd + delimLen;
                lineNo++;
            }

            // signal end of multi line log
            if ( lineNo > 0 )
            {
                notifyMultiLineOp( Phase.End );
                if (usesStdStreams) ALIB.StdOutputStreamsLock.Release();
            }

            msgBuf.SetLength( msgBufStartLength );
        }

    #endif // ALOX_DBG_LOG || ALOX_REL_LOG

} // class TextLogger

} // namespace
