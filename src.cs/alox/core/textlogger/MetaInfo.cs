// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using cs.aworx.lib.strings;
using cs.aworx.lib.strings.util;
using cs.aworx.lib.lang;
using cs.aworx.lib.time;
using cs.aworx.lib.system;

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
 * information of each log line (things like timestamps, thread information, verbosity and domain, etc.).
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
         * The line format specifies the (automated) log output that is prepended to each log
         * line before the log message itself.
         *
         * The string supports replacement variables that begin with a % sign
         * - %SP: The full path of the source file
         * - %Sp: The trimmed path of the source file
         * - %SF: The callers' source file name
         * - %Sf: The callers' source file name without extension
         * - %SL: The line number in the source file
         * - %SM: The method name
         *
         * - %TD: The date the log call was invoked
         * - %TT: Time of day the log call was invoked
         * - %TC: Time elapsed since the Logger was created or its timer was reset
         * - %TL: Time elapsed since the last log call
         *
         * - %tN: Thread name
         * - %tI: Thread ID
         * - %V:  The verbosity. This is replaced by the corresponding strings found in fields
         *        #VerbosityError, #VerbosityWarning, #VerbosityInfo and #VerbosityVerbose.
         * - %D:  Log domain
         * - %#:  The log call counter (like a line counter, but counting multi lines as one)
         * - %An: An auto-adjusted tabulator. This grows whenever it needs, but never shrinks. The
         *        optional integer number n specifies how much extra space is added when tab is adjusted.
         *        Setting this to a higher value avoids too many adjustments at the beginning of a log session.
         * - %LG: The name of the \e Logger. This might be useful if multiple loggers write to the same
         *        output stream (e.g. Console).
         * - %LX: The name of the \e Lox.
         * - %P:  The name of the process / application.
         *
         * Defaults to
         * \code "%Sp/%SF(%SL):%A5%SM() %A5[%TC +%TL][%tN]%V[%D]%A1(%#): " \endcode
         *
         */
        public            AString           Format
                        = new AString( "%SF(%SL):%A5%SM() %A5[%TC +%TL][%tN]%V[%D]%A1(%#): " );

        /** The replacement for variable \c %%V in field #Format if \e Verbosity is \c Error */
        public            String            VerbosityError                              = "[ERR]";

        /** The replacement for variable \c %%V in field #Format if \e Verbosity is \c Warning */
        public            String            VerbosityWarning                            = "[WRN]";

        /** The replacement for variable \c %%V in field #Format if \e Verbosity is \c  Info */
        public            String            VerbosityInfo                               = "     ";

        /** The replacement for variable \c %%V in field #Format if \e Verbosity is \c Verbose */
        public            String            VerbosityVerbose                            = "[***]";

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

        /// Replacement string if no source info is available.
        public            AString           NoSourceFileInfo               = new AString( "---" );

        /// Replacement string if no source info is available.
        public            AString           NoMethodInfo                   = new AString( "---" );
        /// Prefix for the domain.
        public            int               LogNumberMinDigits                          = 3;

        /**
         * The maximum time elapsed. Used to determine the width of the output when writing
         * the elapsed time.
         *
         * This field will be read from the
         * configuration variable [ALOX_LOGGERNAME_MAX_ELAPSED_TIME](../group__GrpALoxConfigVars.html)
         * when the \b %TextLogger that this object belongs to is attached to a \b %Lox
         * and written back on removal.
         */
        public            Ticks             MaxElapsedTime                           = new Ticks(0);

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /// Internal string builder used for formatting operations.
        protected        StringBuilder     formatSB                       = new StringBuilder( 64 );

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
        protected        Tokenizer         tTok                                    =new Tokenizer();

        /** A reusable AString . */
        protected        AString           tmpAString                                =new AString();

        /** A reusable Ticks object. */
        protected        Ticks             elapsedTime                                =new Ticks(0);

        /** Helper flag that indicates if a format warning report was already issued */
        protected        bool              warnedOnce                                       = false;

    /** ********************************************************************************************
     *  Parses the #Format string and logs meta information into the log buffer. For each
     *  variable found, method #processVariable is invoked. Hence, to add new variables,
     *  the latter method can be overwritten by descendants. Overwriting this method is
     *  recommended for formatter classes that do not rely on format strings.
     * @param logger    The logger that we are embedded in.
     * @param buffer    The buffer to write meta information into.
     * @param domain    The <em>Log Domain</em>.
     * @param verbosity The verbosity. This has been checked to be active already on this
     *                  stage and is provided to be able to be logged out only.
     * @param scope     Information about the scope of the <em>Log Statement</em>..
     *
     * @return The number of tab sequences that were written (by adding ESC.TAB to the buffer).
     **********************************************************************************************/
    public virtual int Write( TextLogger logger, AString buffer, Domain domain, Verbosity verbosity, ScopeInfo scope )
    {
        int qtyTabStops= 0;

        // check
        if ( Format == null || Format.IsEmpty() )
            return 0;

        // clear DateTime singleton
        callerDateTime= null ;

        // loop/switch over content specified in configuration array
        tTok.Set( Format, '%' );

        while ( true )
        {
            // get next and log substring between commands
            if ( tTok.Next(Whitespaces.Keep).IsNotEmpty() )
                buffer._( tTok.Actual );

            // previous next did not find a delimiter
            if ( !tTok.HasNext() )
                break;

            // process the found variable
            qtyTabStops+= processVariable( logger, domain, verbosity, scope, buffer, tTok.Rest );
        }

        return qtyTabStops;
    }

    /** ********************************************************************************************
     *  Processes the next command found in the format string, by writing formatted information
     *  into the given buffer.
     *  The given Substring holds the next command. When method returns, the command is cut
     *  from the front.
     *
     * @param logger    The logger that we are embedded in.
     * @param domain    The <em>Log Domain</em>.
     * @param verbosity The verbosity. This has been checked to be active already on this
     *                  stage and is provided to be able to be logged out only.
     * @param scope     Information about the scope of the <em>Log Statement</em>..
     * @param dest      The buffer to write meta information into.
     * @param variable  The variable to read (may have more characters appended)
     *
     * @return The number of tab sequences that were written (by adding ESC.TAB to the buffer).
     **********************************************************************************************/
    protected virtual int processVariable( TextLogger logger, Domain  domain, Verbosity verbosity,
                                           ScopeInfo  scope,  AString dest,   Substring variable )
    {
        // process commands
        char c2;
        switch ( variable.ConsumeChar() )
        {
            // scope info
            case 'S':
            {
                    // read sub command
                AString val;
                switch( c2= variable.ConsumeChar() )
                {
                    case 'P':   // SP: full path
                    {
                        int    length;
                        String path= scope.GetFullPath( out length );
                        if ( length > 0 )
                        {
                            dest._( path, 0, length );
                            return 0;
                        }
                        val= NoSourceFileInfo;

                    } break;

                    case 'p':   // Sp: trimmed path
                    {
                        val= scope.GetTrimmedPath();
                        if ( val.IsEmpty() )
                            val= NoSourceFileInfo;
                    } break;

                    case 'F':   // file name
                    {
                        val= scope.GetFileName();
                        if ( val.IsEmpty() )
                            val= NoSourceFileInfo;
                    } break;

                    case 'f':   // file name without extension
                    {
                        val= scope.GetFileNameWithoutExtension();
                        if ( val.IsEmpty() )
                            val= NoSourceFileInfo;
                    } break;


                    case 'M':   // method name
                    {
                        String method= scope.GetMethod();
                        if ( method.Length == 0 )
                            dest._( NoMethodInfo );
                        else
                            dest._( method );
                        return 0;
                    }

                    case 'L':  // line number
                    {
                        dest._( scope.GetLineNumber() );
                        return 0;
                    }

                    default:
                    {
                        if( !warnedOnce )
                        {
                            warnedOnce= true;
                            ALIB_DBG.WARNING( "Unknown format variable '%S" + c2 + "\' (only one warning)" );
                        }
                        dest._( "%ERROR" );
                        return 0;
                    }
                }
                dest._( val );
                return 0;
            }

            // %Tx: Time
            case 'T':
            {
                // read sub command
                c2= variable.ConsumeChar();

                // %TD: Date
                if ( c2 == 'D' )
                {
                    // get time stamp as DateTime once
                    if ( callerDateTime == null )
                        callerDateTime= scope.GetTimeStamp().InDotNetDateTime();

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

                // %TT: Time of Day
                else if ( c2 == 'T' )
                {
                    // get time stamp as DateTime once
                    if ( callerDateTime == null )
                        callerDateTime= scope.GetTimeStamp().InDotNetDateTime();

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

                // %TC: Time elapsed since created
                else if ( c2 == 'C' )
                {
                    elapsedTime.Set( scope.GetTimeStamp()  );
                    elapsedTime.Sub( logger.TimeOfCreation );

                    if( MaxElapsedTime.Raw() < elapsedTime.Raw() )
                        MaxElapsedTime.Set( elapsedTime );

                    long      maxElapsedSecs= MaxElapsedTime.InSeconds();
                    TimeSpan  elapsed= new TimeSpan( elapsedTime.Raw() );

                    if ( maxElapsedSecs >= 60*60*24 )  dest._( elapsed.Days  )._NC( TimeElapsedDays );
                    if ( maxElapsedSecs >= 60*60    )  dest._( elapsed.Hours  ,  maxElapsedSecs >= 60*60*10 ?  2 : 1 )._( ':' );
                    if ( maxElapsedSecs >= 60       )  dest._( elapsed.Minutes,  maxElapsedSecs >= 10*60    ?  2 : 1 )._( ':' );
                    dest._( elapsed.Seconds,  maxElapsedSecs > 9 ? 2 : 1          )._NC( '.' );
                    dest._( elapsed.Milliseconds,  3 );
                }

                // %TL: Time elapsed since last log call
                else if ( c2 == 'L' )
                    writeTimeDiff( dest, scope.GetTimeStamp().Since(logger.TimeOfLastLog).InNanos() );

                else
                {
                    if( !warnedOnce )
                    {
                        warnedOnce= true;
                        ALIB_DBG.WARNING( "Unknown format variable '%T" + c2 + "\' (only one warning)" );
                    }
                    dest._( "%ERROR" );
                }
                return 0;
            }


            // thread name / ID
            case 't':
            {
                c2= variable.ConsumeChar();

                if ( c2 == 'N' )
                {
                    dest.Field()
                        ._( scope.GetThreadName() )
                        .Field( logger.AutoSizes.Next( scope.GetThreadName().Length(), 0 ), Alignment.Center );
                }
                else if ( c2 == 'I' )
                {
                    tmpAString._()._( scope.GetThreadID() );
                    dest.Field()
                        ._( tmpAString )
                        .Field( logger.AutoSizes.Next( tmpAString           .Length(), 0 ), Alignment.Center );
                }
                else
                {
                    if( !warnedOnce )
                    {
                        warnedOnce= true;
                        ALIB_DBG.WARNING( "Unknown format variable '%t" + c2 + "\' (only one warning)" );
                    }
                    dest._( "%ERROR" );
                }
                return 0;
            }

            case 'L':
            {
                c2= variable.ConsumeChar();
                     if ( c2 == 'G' )     dest._NC( logger.GetName() );
                else if ( c2 == 'X' )     dest._NC( scope.GetLoxName() );
                else
                {
                    if( !warnedOnce )
                    {
                        warnedOnce= true;
                        ALIB_DBG.WARNING( "Unknown format variable '%L" + c2 + "\' (only one warning)" );
                    }
                    dest._( "%ERROR" );
                    return 0;
                }
                return 0;
            }

            case 'P':
            {
                dest._NC( ProcessInfo.GetCurrentProcessName() );
                return 0;
            }

            case 'V':   dest._ (    verbosity == Verbosity.Error    ? VerbosityError
                                  : verbosity == Verbosity.Warning  ? VerbosityWarning
                                  : verbosity == Verbosity.Info     ? VerbosityInfo
                                  :                                   VerbosityVerbose    );
                        return 0;

            case 'D':
            {
                dest.Field()._( domain.FullPath ).Field( logger.AutoSizes.Next( domain.FullPath.Length(), 0 ), Alignment.Left );
                return 0;
            }

            case '#':    dest._( logger.CntLogs, LogNumberMinDigits );
                         return 0;

            // A: Auto tab
            case 'A':
            {
                // read extra space from format string
                int     oldStart=    variable.Start;
                int     extraSpace;  variable.ConsumeDecDigits( out extraSpace );
                if ( oldStart == variable.Start )
                    extraSpace=         1;

                // insert ESC code to jump to next tab level
                extraSpace= Math.Min( extraSpace, 10 + ('Z'-'A') );
                char escNo= extraSpace < 10 ?   (char) ( '0' + extraSpace )
                                            :   (char) ( 'A' + extraSpace );

                dest._( "\x1Bt" )._( escNo );
                return 1;
            }

            default:
            {
                if( !warnedOnce )
                {
                    warnedOnce= true;
                    ALIB_DBG.WARNING( "Unknown format variable \'" + variable.Buf[variable.Start - 1] + "\'" );
                }
                dest._( "%ERROR" );
            }
            return 0;
        }

    }


    /** ********************************************************************************************
     *
     *  Helper function that logs a time given difference into the given buffer in a human readable
     *  format. Works from micro seconds to days.
     *
     * @param buf         The buffer to write the time difference representation into.
     * @param diffNanos   The time difference to write in nanoseconds.
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
