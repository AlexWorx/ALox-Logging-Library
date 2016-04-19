// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using cs.aworx.lib;
using cs.aworx.lox;
using cs.aworx.lox.core;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;
using cs.aworx.lib.threads;

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
     * A list of helper objects to get textual representation of logable objects.<br>
     * To extend TextLogger to support logging custom objects, custom converters can
     * be appended. Also, the default may be removed and deleted.<br>
     * In the destructor of this class, all object converters (still attached) will be deleted.
     *
     * When converting an object, all object converts listed here are invoked in
     * <b> reverse order</b> until a first reports a successful conversion.
     */
    public    List<ObjectConverter>     ObjectConverters               =new List<ObjectConverter>();

    /**
     * A helper object to format log objects into textual representations. This class incorporates
     * a format string that defines the meta information in the log output. Furthermore, to extend
     * TextLogger, this object can be replaced by custom implementations of it.
     */
    public    MetaInfo                  MetaInfo                                    =new MetaInfo();

    /**
     *  Holds a list of values for auto tab positions and field sizes.
     *  For each requested value, a corresponding array field is created on the fly.
     *  If the format string get's changed and different (new) auto values should be used, then
     *  this field should be reset after setting the new format string.
     *  The other way round, it is also possible to preset set minimum values for tabs and field
     *  sizes and hence avoid the columns growing during the lifetime of the Logger.
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
     * This is the string interpreted as line delimiter within log messages. If null, CR, LF or CRLF
     * are used. Important: Set to empty string, to stop any multi line processing of TextLogger, even the replacements.
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
     *  Suffix for multi line messages. This is also used if multi line messages logging is switched off
     *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
     */
    public    String                    FmtMultiLineSuffix                                    =null;

    /** Used to return an error message in the case the object could not be converted. */
    public    String                    FmtUnknownObject               ="<unknown object type '%'>";


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
        ObjectConverters.Add( new StringConverter() );

        // evaluate config variable <name>_FORMAT / <typeName>_FORMAT
        {
            AString variableName= new AString( name ); variableName._( "_FORMAT" );
            AString result= new AString();
            if ( ALIB.Config.Get( ALox.ConfigCategoryName, variableName, result ) == 0 )
            {
                variableName._()._( typeName )._( "_FORMAT" );
                ALIB.Config.Get( ALox.ConfigCategoryName, variableName, result );
            }

            if( result.IsNotEmpty() )
                MetaInfo.Format._()._( result );
        }
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
                ALIB.Lock.Acquire();
                    int  stdStreamLockRegistrationCounter= this.stdStreamLockRegistrationCounter++;
                ALIB.Lock.Release();
                if ( stdStreamLockRegistrationCounter == 0 )
                    ALIB.StdOutputStreamsLock.AddAcquirer( this );
            }

            // get auto sizes from last session
            {
                AString autoSizes= new AString();
                AString variableName= new AString(name); variableName._( "_AUTO_SIZES" );
                if( ALIB.Config.Get( ALox.ConfigCategoryName, variableName, autoSizes ) != 0 )
                    AutoSizes.Import( autoSizes );
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
                ALIB.Lock.Acquire();
                    int  stdStreamLockRegistrationCounter= --this.stdStreamLockRegistrationCounter;
                ALIB.Lock.Release();

                if ( stdStreamLockRegistrationCounter == 0 )
                    ALIB.StdOutputStreamsLock.RemoveAcquirer( this );
            }

            // export autosizes to configuration
            {
                AString autoSizes= new AString();
                AString variableName= new AString(name); variableName._( "_AUTO_SIZES" );
                AutoSizes.Export( autoSizes );
                ALIB.Config.Save( ALox.ConfigCategoryName, variableName, autoSizes,
                                  "Auto size values of last run" );
            }

            // call parents' implementation
            return base.RemoveAcquirer( acquirer );
        }

    // #############################################################################################
    // Public interface
    // #############################################################################################

        /** ****************************************************************************************
         * Adds the given pair of replacement strings. If searched string already exists, the
         * current replacement string gets replaced. If the replacement string equals 'null'
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
                    else
                    {
                        replacements.RemoveAt( i );
                        replacements.RemoveAt( i );
                        return;
                    }
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
         * This abstract method introduced by this class "replaces" the the abstract method #Log
         * of parent class Logger which this class implements. In other words, descendants of this
         * class need to overwrite this method instead of \b %Do. This class %TextLogger is
         * responsible for generating meta information, doing text replacements, handle multi-line
         * messages, etc. and provides the textual representation of the whole log contents
         * to descendants using this method.
         *
         * @param domain     The <em>Log Domain</em>.
         * @param verbosity  The verbosity. This has been checked to be active already on this
         *                   stage and is provided to be able to be logged out only.
         * @param msg        The log message.
         * @param scope      Information about the scope of the <em>Log Statement</em>..
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
            // clear Buffer and reset utility members
            logBuf.Clear();
            AutoSizes.Start();

            //  << meta info << ESC::EOMETA
            int qtyESCTabsWritten=  MetaInfo.Write( this, logBuf, domain, verbosity, scope );

            logBuf._( ESC.EOMETA );

            // convert msg object into an AString representation
            msgBuf._();
            foreach( Object logable in logables )
            {
                int i;
                for( i= ObjectConverters.Count - 1; i >= 0 ; i-- )
                    if ( ObjectConverters[i].ConvertObject( logable, msgBuf ) )
                        break;
                if ( i == -1 )
                {
                    AString msg= new AString( FmtUnknownObject );
                    msg.SearchAndReplace( "%", "" + logable.GetType().ToString() );
                    msgBuf._NC( msg );
                }
            }

            // replace strings in message
            for ( int i= 0; i < replacements.Count ; i+=2 )
                msgBuf.SearchAndReplace( replacements[i], replacements[i + 1] );

            // check for empty messages
            if ( msgBuf.IsEmpty() )
            {
                // log empty msg and quit
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
                    cntReplacements+=msgBuf.SearchAndReplace( MultiLineDelimiter,    MultiLineDelimiterRepl );
                else
                {
                    cntReplacements+=msgBuf.SearchAndReplace( "\r\n", MultiLineDelimiterRepl );
                    cntReplacements+=msgBuf.SearchAndReplace( "\r", MultiLineDelimiterRepl );
                    cntReplacements+=msgBuf.SearchAndReplace( "\n", MultiLineDelimiterRepl );
                }

                // append msg to logBuf
                if ( cntReplacements == 0 )
                {
                    logBuf._( msgBuf );
                }
                else
                {
                    logBuf._( FmtMultiLinePrefix );
                    logBuf._( msgBuf );
                    logBuf._( FmtMultiLineSuffix );
                }

                // now do the logging by calling our derived classes' logText
                logText( domain, verbosity, logBuf, scope, -1 );

                // stop here
                return;
            }

            // multiple line output
            int qtyTabStops= AutoSizes.ActualIndex;

            int actStart=0;
            int lineNo=0;
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
                        logBuf._( msgBuf );

                        // now do the logging by calling our derived classes' logText
                        if (usesStdStreams) ALIB.StdOutputStreamsLock.Acquire();
                            logText( domain, verbosity, logBuf, scope, -1 );
                        if (usesStdStreams) ALIB.StdOutputStreamsLock.Release();

                        // stop here
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
        }

    #endif // ALOX_DBG_LOG || ALOX_REL_LOG

} // class TextLogger

} // namespace
