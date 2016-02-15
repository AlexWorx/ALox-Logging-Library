// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;

#if (ALOX_DBG_LOG || ALOX_REL_LOG)

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using cs.aworx.lib;
using cs.aworx.lox;
using cs.aworx.lox.core;

namespace cs.aworx.lox.core.textlogger
{

/** ************************************************************************************************
 * This class is a sort of plug-in for the TextLogger class. Its purpose is to assemble the meta
 * information of each log line (things like timestamps, thread information, level and domain, etc.).
 *
 * To manipulate the meta information log output, three options exist:
 * - by just changing the #Format string (at runtime).
 * - by creating a derived class that introduces a new version of method #processVariable() to handle
 *   one or more format variable differently or to introduce new variables.
 * - by creating a derived class that introduces a new version of method #Write() to
 *   completely control the meta information output.
 **************************************************************************************************/
public class MetaInfo
{
    // #############################################################################################
    // public fields
    // #############################################################################################

        /**
         *
         *  The line format specifies the (automated) log output that is prepended to each log line before
         *  the log message itself.
         *
         *  The string supports replacement variables that begin with a % sign
         *  - %CF: The caller's source file name including path
         *  - %Cf: The caller's source file name (excluding path)
         *  - %CL: The line number in the caller's source file
         *  - %CM: The caller's method name
         *  - %D:  The date the log call was invoked
         *  - %TD: Time of day the log call was invoked
         *  - %TE: Time elapsed since the Logger was created or it's timer was reset
         *  - %TI: Time elapsed since the last log call
         *  - %t:  Thread name and/or ID
         *  - %L:  The log level
         *  - %O:  Log domain
         *  - %#:  The log call counter (like a line counter, but counting multi lines as one)
         *  - %An: An auto-adjusted tabulator. This grows whenever it needs, but never shrinks. The
         *         optional integer number n specifies how much extra space is added when tab is adjusted.
         *         Setting this to a higher value avoids too many adjustments at the beginning of a log session.
         *  - %N:  The name of the logger. This might be useful if multiple loggers write to the same
         *           output stream (e.g. Console).
         *
         */
        //public AString  Format= new AString( "%CF(%CL):%CM()%A3[%DD] [%TD] [%TE +%TI] [%t] %L [%O] <%#>: ");
        public            AString            Format    = new AString( "%CF(%CL):%CM()%A5[%TE +%TI] [%t] %L [%O]: ");


        /**
         *
         *  To shorten the log output the given prefix might be cut from the source file path.
         *  If this field is left to 'null' (or set to null at runtime), it is tried to detect this path
         *  automatically once. However, in remote debug sessions (e.g. on mobile device development)
         *  this fails. Hence, this parameter can be set 'manually' to the right prefix that is to be
         *  consumed. In this case, whenever the project is compiled on a different machine setup (with
         *  different project path), this field has to be changed. If it is not changed, there is no
         *  other problem than that the path is not shortened and the log output might get a little wide.
         *  If the output of the full path is intended, the parameter can be set to 'String.Empty'.
         *
         */
        public         String                   ConsumableSourcePathPrefixString;


        /// The output for the log level "Error".
        public            String            LogLevelError                               = "[ERR]";

        /// The output for the log level "Warning".
        public            String            LogLevelWarning                             = "[WRN]";

        /// The output for the log level "Info".
        public            String            LogLevelInfo                                = "     ";

        /// The output for the log level "Verbose".
        public            String            LogLevelVerbose                             = "[***]";

        /// Format string for the output of the log date. For more information, see
        ///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat()
        public            String            DateFormat                                  = "yyyy-MM-dd";

        /// Format string for the output of the time of day. For more information, see
        ///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat()
        public            String            TimeOfDayFormat                             = "HH:mm:ss";

        /// The word "Days" the out put of time elapsed (if longer than a day).
        public            String            TimeElapsedDays                             = " Days ";

        /// Entity microseconds for time difference outputs below 1000 microseconds.
        public            String            TimeDiffMicros                              = " \u00B5s"; //" ?s";

        /// Minimum time difference to log in nanoseconds. Below that #TimeDiffNone is written.
        public            long              TimeDiffMinimum                             = 1000L;

        /// Output for time difference if below reasonable (measurable) minimum defined in #TimeDiffMinimum.
        public            String            TimeDiffNone                                = "  0 ns";

        /// Entity nanoseconds for time difference outputs below 1000 microseconds.
        public            String            TimeDiffNanos                               = " ns";

        /// Entity milliseconds for time difference outputs below 1000 milliseconds.
        public            String            TimeDiffMillis                              = " ms";

        /// Format for time difference outputs between 10s and 99.9s.
        public            String            TimeDiffSecs                                = " s";

        /// Format for time difference outputs between 100s and 60 min.
        public            String            TimeDiffMins                                = " m";

        /// Format for time difference outputs between 1h and 24h.
        public            String            TimeDiffHours                               = " h";

        /// Format for time difference outputs of more than a day.
        public            String            TimeDiffDays                                = " days";

        /// Prefix for the domain.
        public            int               LogNumberMinDigits                          = 3;

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /// Internal string builder used for formatting operations.
        protected        StringBuilder     formatSB                                     = new StringBuilder( 64 );

        /// Reference to last date format string to detect changes at runtime.
        protected        String            detectDateFormatChanges;

        /// The .Net format string built at runtime to {0:FmtDate}.
        protected        String            dateFormatString;

        /// Reference to last time of day format string to detect changes at runtime.
        protected        String            detectTimeOfDayFormatChanges;

        /// The .Net format string built at runtime to {0:FmtTimeOfDay}.
        protected        String            timeOfDayFormatString;

        /// A singleton DateTime object shared between different format variables during one invocation.
        protected        DateTime?         callerDateTime;

        /// Tokenizer used in #Write.
        protected        Tokenizer         tok=                         new Tokenizer();


    /** ********************************************************************************************
     *  Parses the #Format string and logs meta information into the log buffer. For each
     *  variable found, method #processVariable is invoked. Hence, to add new variables,
     *  the latter method can be overwritten by descendants. Overwriting this method is
     *  recommended for formatter classes that do not rely on format strings.
     * @param logger    The logger that we are embedded in.
     * @param buffer    The buffer to write meta information into.
     * @param domain    The log domain name.
     * @param level     The log level. This has been checked to be active already on this
     *                  stage and is provided to be able to be logged out only.
     * @param caller    Once compiler generated and passed forward to here.
     *
     * @return The number of tab sequences that were written (by adding ESC::TAB to the buffer).
     **********************************************************************************************/
    public virtual int Write( TextLogger logger, AString buffer, AString domain, Log.Level level, CallerInfo caller )
    {
        int qtyTabStops= 0;

        // check
        if ( Format == null || Format.IsEmpty() )
            return 0;

        // clear DateTime singleton
        callerDateTime= null ;

        // loop/switch over content specified in configuration array
        tok.Set( Format, '%' );

        while ( true )
        {
            // get next and log substring between commands
            if ( tok.Next(Whitespaces.Keep).IsNotEmpty() )
                buffer._( tok.Actual );

            // previous next did not find a delimiter
            if ( !tok.HasNext() )
                break;

            // process the found variable
            qtyTabStops+= processVariable( logger, domain, level, caller, buffer, tok.Rest );
        }

        return qtyTabStops;
    }

    /** ********************************************************************************************
     *  Processes the next command found in the format string, by writing formatted information
     *  into the given buffer.
     *  The given Substring holds the next command. When method returns, the command is cut
     *  from the front.
     *
     * @param logger   The logger that we are embedded in.
     * @param domain   The log domain name.
     * @param level    The log level. This has been checked to be active already on this
     *                 stage and is provided to be able to be logged out only.
     * @param caller   Once compiler generated and passed forward to here.
     * @param dest     The buffer to write meta information into.
     * @param variable The variable to read (may have more characters appended)
     *
     * @return The number of tab sequences that were written (by adding ESC::TAB to the buffer).
     **********************************************************************************************/
    protected virtual int processVariable( TextLogger logger, AString domain, Log.Level level,
                                           CallerInfo caller, AString dest, Substring variable )
    {
        // process commands
        switch ( variable.Consume() )
        {
            // caller info
            case 'C':
            {
                // read sub command
                char s= variable.Consume();

                // add source file
                if ( s == 'F' )
                {
                    // can we cut the source file name by a prefix?
                    String sourceFileName=    caller.SourceFileName;
                    // detect cutable prefix from the filename path and current working directory
                    // Note: we do this only once. And we do not use the prefix here
                    //       This is up to the derived logger to do so.
                    if ( ConsumableSourcePathPrefixString == null )
                    {

                        // get system execution path and compare to file path
                        ConsumableSourcePathPrefixString= Environment.CurrentDirectory;

                        // Get the prefix that is the same in both paths
                        // The first letter might be a drive letter and here we have to ignore the case
                        int driveLetterIndex= ConsumableSourcePathPrefixString.Length >= 2 && ConsumableSourcePathPrefixString[1] == ':' ? 0 : -1;
                        int i= 0;
                        while (     i < sourceFileName                  .Length
                                &&  i < ConsumableSourcePathPrefixString.Length
                                &&  ( i== driveLetterIndex  ? Char.ToUpperInvariant( ConsumableSourcePathPrefixString[i]) == Char.ToUpperInvariant( sourceFileName[i] )
                                                            :                         ConsumableSourcePathPrefixString[i]  ==                        sourceFileName[i]
                                    )
                        )
                            i++;

                        // store consumable prefix and its length. If unsuccessful, "" is stored to prevent searching again
                        ConsumableSourcePathPrefixString=  ( i > 1) ? ConsumableSourcePathPrefixString.Substring(0, i)
                                                                    : String.Empty;
                    }

                    dest._NC( sourceFileName, ConsumableSourcePathPrefixString.Length, sourceFileName.Length - ConsumableSourcePathPrefixString.Length );
                }

                // add source file without path
                if ( s == 'f' )
                {
                    // can we cut the source file name by a prefix?
                    String sourceFileName=    caller.SourceFileName;

                    int sfnLen=         sourceFileName.Length;
                    int appendStart=    sfnLen - 1;
                    while( appendStart > 0 && sourceFileName[appendStart] != System.IO.Path.VolumeSeparatorChar )
                        appendStart--;
                    if( appendStart == 0 )
                        dest._( sourceFileName );
                    else
                        dest._NC( sourceFileName, appendStart + 1, sourceFileName.Length - appendStart -1  );
                }

                // add line number or method name
                else if ( s == 'L' )  dest._( caller.LineNumber );
                else if ( s == 'M' )  dest._( caller.MethodName );
            }
            return 0;

            // Date
            case 'D':
            {
                // get time stamp as DateTime once
                if ( callerDateTime == null )
                    callerDateTime= caller.TimeStamp.InDotNetDateTime();

                // avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!)
                // and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
                if ( DateFormat.Equals( "yyyy-MM-dd" ) )
                {
                    dest ._( callerDateTime.Value.Year,  4 )._( '-' )
                         ._( callerDateTime.Value.Month, 2 )._( '-' )
                         ._( callerDateTime.Value.Day,   2 );
                }

                // support user defined standards
                else
                {
                    // detect changes of format string since last log
                    if ( detectDateFormatChanges != DateFormat )
                    {
                        detectDateFormatChanges= DateFormat;
                        dateFormatString= "{0:" + DateFormat + "}";
                    }

                    // get date string from system and append to log buffer
                    formatSB.Clear();
                    formatSB.AppendFormat( CultureInfo.InvariantCulture, dateFormatString, callerDateTime );
                    dest._( formatSB );
                }
            }
            return 0;

            // %Tx: Time
            case 'T':
            {
                // read sub command
                char s= variable.Consume();

                // %TD: Time of Day
                if ( s == 'D' )
                {
                    // get time stamp as DateTime once
                    if ( callerDateTime == null )
                        callerDateTime= caller.TimeStamp.InDotNetDateTime();

                    // avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!)
                    // and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
                    if ( TimeOfDayFormat.Equals( "HH:mm:ss" ) )
                    {
                        dest ._( callerDateTime.Value.Hour,   2 )._( ':' )
                             ._( callerDateTime.Value.Minute, 2 )._( ':' )
                             ._( callerDateTime.Value.Second, 2 );
                    }

                    // support user defined standards
                    else
                    {
                        // detect changes of format string since last log
                        if ( detectTimeOfDayFormatChanges != TimeOfDayFormat )
                        {
                            detectTimeOfDayFormatChanges= TimeOfDayFormat;
                            timeOfDayFormatString= "{0:" + TimeOfDayFormat + "}";
                        }

                        // get time string from system and append to log buffer
                        formatSB.Clear();
                        formatSB.AppendFormat( CultureInfo.InvariantCulture, timeOfDayFormatString, callerDateTime);
                        dest     ._( formatSB );
                    }
                }

                // %TE: Time Elapsed
                else if ( s == 'E' )
                {
                    // create TimeSpan object (on the stack by using new! :)
                        TimeSpan elapsed= new TimeSpan( caller.TimeStamp.Raw() - logger.TimeOfCreation.Raw() );

                    if ( elapsed.Days > 0 )
                        dest._( elapsed.Days )._( TimeElapsedDays );

                    if ( elapsed.Hours > 0 )
                        dest._( elapsed.Hours )    ._( ':' );

                    dest ._( elapsed.Minutes, 2)._( ':' )
                         ._( elapsed.Seconds, 2)._( '.' )
                         ._( elapsed.Milliseconds, 3);
                }

                // %TE: Time Diff
                else
                    writeTimeDiff( dest, caller.TimeStamp.Since(logger.TimeOfLastLog).InNanos() );
            }
            return 0;


            // Thread
            case 't':
            {
                #if !ALOX_NO_THREADS
                    // get name length and store max value
                    dest.Field()
                         ._( caller.ThreadName )
                       .Field( logger.AutoSizes.Next( caller.ThreadName.Length(), 0 ), Alignment.Center );
                #endif
            }
            return 0;

            case 'L':   dest._ (    level == Log.Level.Error    ? LogLevelError
                                  : level == Log.Level.Warning  ? LogLevelWarning
                                  : level == Log.Level.Info     ? LogLevelInfo
                                  :                               LogLevelVerbose    );
            return 0;

            case 'O':
            {
                // If no domain logged yet and domain name is empty, we omit it
                    dest.Field()
                         ._( domain )
                       .Field( logger.AutoSizes.Next( domain.Length(), 0 ), Alignment.Center );
            }
            return 0;

            case '#':    dest._( logger.CntLogs, LogNumberMinDigits );
            return 0;

            // A: Auto tab
            case 'A':
            {
                // read extra space from format string
                int oldStart=    variable.Start;
                int extraSpace;  variable.ConsumeInteger( out extraSpace );
                if ( oldStart == variable.Start )
                    extraSpace=         1;

                // insert ESC code to jump to next tab level
                extraSpace= Math.Min( extraSpace, 10 + ('Z'-'A') );
                char escNo= extraSpace < 10 ?   (char) ( '0' + extraSpace )
                                            :   (char) ( 'A' + extraSpace );

                dest._( "\x1Bt" )._( escNo );
            }
            return 1;

            case 'N':    dest._( logger.Name );
            return 0;

            default:
            {
                ALIB.WARNING( "Unknown format character \'" + variable.Buf[variable.Start - 1] + "\'" );
            }
            return 0;
        }

    }


    /** ********************************************************************************************
     *
     *  Helper function that logs a time given difference into the given buffer in a human readable
     *  format. Works from micro seconds to days.
     *
     * @param buf         The buffer to write the time difference representation into. </param>
     * @param diffNanos     The time difference to write in nanoseconds.     </param>
     **********************************************************************************************/
    protected virtual void writeTimeDiff( AString buf, long diffNanos )
    {
        // unmeasurable?
        if ( diffNanos < TimeDiffMinimum )  { buf._( TimeDiffNone );                                 return; }

        if ( diffNanos < 1000 )             { buf._( (int) diffNanos, 3  )._( TimeDiffNanos );  return; }

        // we continue with micros
        long diffMicros= diffNanos / 1000L;

        // below 1000 microseconds?
        if ( diffMicros < 1000 )            { buf._( (int) diffMicros, 3 )._( TimeDiffMicros ); return; }

        // below 1000 ms?
        if ( diffMicros < 1000000 )         { buf._( (int) (diffMicros / 1000), 3 )._( TimeDiffMillis ); return; }


        // below 10 secs (rounded) ?
        if ( diffMicros < 9995000 )
        {
            // convert to hundredth of secs
            long hundredthSecs=  ((diffMicros / 1000) + 5) / 10;

            // print two digits after dot x.xx
            buf._( (int) (hundredthSecs / 100), 1 )
               ._( '.' )
               ._( (int) (hundredthSecs % 100), 2 )
               ._( TimeDiffSecs );
            return;
        }

        // convert to tenth of secs
        long tenthSecs=  ((diffMicros / 10000) + 5) / 10 ;

        // below 100 secs ?
        if ( tenthSecs < 1000 )
        {
            // print one digits after dot xx.x (round value by adding 5 hundredth)
            buf._( (int) ( tenthSecs / 10 ), 2 )
               ._( '.' )
               ._( (int) ( tenthSecs % 10 ), 1 )
               ._( TimeDiffSecs );
            return;
        }

        //     below 10 minutes ?
        if ( tenthSecs < 6000 )
        {
            // convert to hundredth of minutes
            long hundredthMins=  tenthSecs / 6;

            // print two digits after dot x.xx
            buf._( (int) (hundredthMins / 100), 1 )
               ._( '.' )
               ._( (int) (hundredthMins % 100), 2 )
               ._( TimeDiffMins );
            return;
        }

        // convert to tenth of minutes
        long tenthMins=  tenthSecs / 60;

        // below 100 minutes ?
        if ( tenthMins < 1000 )
        {
            // print one digits after dot xx.x (round value by adding 5 hundredth)
            buf._( (int) (tenthMins / 10), 2 )
               ._( '.' )
               ._( (int) (tenthMins % 10), 1 )
               ._( TimeDiffMins );
            return;
        }

        // below ten hours?
        if ( tenthMins < 6000 )
        {
            // convert to hundredth of hours
            long hundredthHours=  tenthMins / 6;

            // print two digits after dot x.xx
            buf._( (int) (hundredthHours / 100), 1 )
               ._( '.' )
               ._( (int) (hundredthHours % 100), 2 )
               ._( TimeDiffHours );
            return;
        }

        // convert to tenth of minutes
        long tenthHours=  tenthMins / 60;

        // below 10 hours ?
        if ( tenthHours < 1000 )
        {
            // print two digits after dot x.xx
            buf._( (int) (tenthHours / 10), 2 )
               ._( '.' )
               ._( (int) (tenthHours % 10), 1 )
               ._( TimeDiffHours );
            return;
        }

        // below 100 hours ?
        if ( tenthHours < 1000 )
        {
            // print one digits after dot xx.x (round value by adding 5 hundredth)
            buf._( (int) (tenthHours / 10), 2 )
               ._( '.' )
               ._( (int) ((tenthHours / 10) % 10), 1 )
               ._( TimeDiffHours );
            return;
        }

        // convert to hundredth of days
        long hundredthDays=  tenthHours * 10 / 24;

        // below 10 days ?
        if ( hundredthDays < 1000 )
        {
            // print two digits after dot x.xx
            buf._( (int) (hundredthDays / 100), 1 )
               ._( '.' )
               ._( (int) (hundredthDays % 100), 2 )
               ._( TimeDiffDays );
            return;
        }

        // 10 days or more (print days plus one digit after the comma)
        // print one digits after dot xx.x (round value by adding 5 hundredth)
        buf ._( (int) (hundredthDays / 100), 2 )
            ._( '.' )
            ._( (int) ((hundredthDays / 10) % 10), 1 )
            ._( TimeDiffDays );
    }

} // class
} // namespace

#endif
