// #################################################################################################ests
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core.textlogger;

import java.text.FieldPosition;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;

import com.aworx.lib.ALIB;
import com.aworx.lib.enums.Alignment;
import com.aworx.lib.enums.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.Tokenizer;
import com.aworx.lib.time.TickSpan;
import com.aworx.lox.Log;
import com.aworx.lox.core.CallerInfo;


/** ************************************************************************************************
 * This class is a sort of plug-in for the TextLogger class. Its purpose is to assemble the meta
 * information of each log line (things like timestamps, thread information, level and domain, etc.).
 *
 * To manipulate the meta information log output, three options exist:
 * - by just changing the #format string (at runtime).
 * - by creating a derived class that introduces a new version of method #processVariable() to handle
 *   one or more format variable differently or to introduce new variables.
 * - by creating a derived class that introduces a new version of method #write() to
 *   completely control the meta information output.
 **************************************************************************************************/
public class MetaInfo
{
    // #############################################################################################
    // public fields
    // #############################################################################################

        /**
         *  The line format specifies the (automated) log output that is prepended to each log line before
         *  the log message itself.
         *
         *  The string supports replacement variables that begin with a % sign
         *  - %CF: The caller's source file name
         *  - %CL: The line number in the caller's source file
         *  - %CP: The caller's package name
         *  - %CC: The caller's class name
         *  - %CM: The caller's method name
         *  - %D:  Date
         *  - %TD: Time of day
         *  - %TE: Time elapsed since the Logger was created or it's timer was reset
         *  - %TI: Time elapsed since the last log call
         *  - %t:  Thread information
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
        //public         AString                format    =    new AString( "(%CF:%CL) %CP.%CC.%CM():%A3[%DD] [%TD] [%TE +%TI] [%t] %L [%O] <%#>: ");
        //public    AString               format                   =  new AString( "(%CF:%CL) %CM():%A8[%TE +%TI] [%t] %L [%O]: ");
        public    AString               format                   =  new AString( "(%CF:%CL) %CM():%A8[%TE +%TI] [%t] %L [%O] %A1(%#): ");



        /** The output for the log level "Error". */
        public    String                logLevelError            = "[ERR]";

        /** The output for the log level "Warning". */
        public    String                logLevelWarning          = "[WRN]";

        /** The output for the log level "Info". */
        public    String                logLevelInfo             = "     ";

        /** The output for the log level "Verbose". */
        public    String                logLevelVerbose          = "[***]";

        /** Format string for the output of the log date.
            For more information about possible, see class java.text.SimpleDateFormat  */
        public    String                dateFormat               = "yyyy-MM-dd";

        /** Format string for the output of the time of day.
            For more information about possible, see class java.text.SimpleDateFormat  */
        public    String                timeOfDayFormat          = "HH:mm:ss";

        /** The word "Days" the out put of time elapsed (if longer than a day). */
        public    String                timeElapsedDays          = " Days ";

        /// Minimum time difference to log in nanoseconds.  Below that #timeDiffNone is written.
        public    long                  timeDiffMinimum          = 1000L;

        /// Output for time difference if below reasonable (measurable) minimum defined in #timeDiffMinimum.
        public    String                timeDiffNone             = "  0 ns";

        /** Entity milliseconds. */
        public    String                timeDiffNanos            = " ns";

        /** Entity microseconds */
        public    String                timeDiffMicros           = " \u00B5s"; //" µs";

        /** Entity milliseconds */
        public    String                timeDiffMillis           = " ms";

        /** Format for time difference outputs between 10s and 99.9s. */
        public    String                timeDiffSecs             = " s";

        /** Format for time difference outputs between 100s and 60 min. */
        public    String                timeDiffMins             = " m";

        /** Format for time difference outputs between 1h and 24h. */
        public    String                timeDiffHours            = " h";

        /** Format for time difference outputs of more than a day. */
        public    String                timeDiffDays             = " days";

        /** Prefix for the domain. */
        public    int                   logNumberMinDigits       = 3;

        /**  Internal object to retrieve formatted log date. This field has to be set to null,
         *   when the field #dateFormat gets modified and log operations have been scheduled
         *   since the creation of the logger (respectively since the last change of that format).  */
        public    SimpleDateFormat      dateFormatter;

        /**  Internal object to retrieve formatted time of day. This field has to be set to null,
         *   when the field #timeOfDayFormat gets modified and log operations have been scheduled
         *   since the creation of the logger (respectively since the last change of that format).  */
        public    SimpleDateFormat      timeOfDayFormatter;


    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /**  Internal calendar object to get string representations of dates. */
        protected Date                  callerDateTimeDate            = new Date();

        /**  Internal calendar object to get string representations of dates. */
        protected GregorianCalendar     callerDateTimeCal             = new GregorianCalendar();

        /**  Flag to indicate if date instance was set during one doLog() call  */
        protected boolean               dateInstanceSet;

        /**  Flag to indicate if calendar instance was set during one doLog() call  */
        protected boolean               calInstanceSet;

        /**  Internal object to retrieve formatted time of day  */
        protected StringBuffer          tempSBuf                      = new StringBuffer();

        /**  Internal object to pass int parameters to methods that modify those  */
        protected int[]                 tempIntParameter              = new int[1];

        /**  Internal singleton to specify a first field in formatted output */
        protected FieldPosition         fieldPositionZero             = new FieldPosition( 0 );

        /**  Internal default string to detect default format for optimized format generation */
        protected String                defaultfmtDate                = "yyyy-MM-dd";

        /**  Internal default string to detect default format for optimized format generation */
        protected String                defaultfmtTimeOfDay           = "HH:mm:ss";

        /**  A reusable object for displaying the elapsed time span  */
        protected TickSpan              elapsed                       = new TickSpan();

        /// Tokenizer used in #write.
        protected Tokenizer             tok                           = new Tokenizer();


    /** ********************************************************************************************
     *  Parses the #format string and logs meta information into the log buffer.
     *  For each variable found, method #processVariable is invoked. Hence, to add new variables,
     *  the latter method can be overwritten by descendants. Overwriting this method is
     *  recommended for formatter classes that do not rely on format strings.
     *
     * @param logger    The logger that we are embedded in.
     * @param buf       The buffer to write meta information into.
     * @param domain    The log domain name.
     * @param level     The log level. This has been checked to be active already on this
     *                  stage and is provided to be able to be logged out only.
     * @param caller    Once compiler generated and passed forward to here.
     * @return The number of tab sequences that were written (by adding ESC::TAB to the buffer).
     **********************************************************************************************/
    protected int write( TextLogger logger, AString buf, AString domain, Log.Level level, CallerInfo caller )
    {
        int qtyTabStops= 0;

        // check
        if ( format == null || format.isEmpty() )
            return 0;

        // set date object only once per loop
        calInstanceSet=  false;
        dateInstanceSet= false;

        // loop/switch over content specified in configuration array
        tok.set( format, '%' );
        while ( true )
        {
            // get next and log substring between commands
            if ( tok.next( Whitespaces.KEEP ).isNotEmpty() )
                buf._( tok.actual );

            // previous next did not find a delimiter
            if ( !tok.hasNext() )
                break;

            // process the found variable
            qtyTabStops+= processVariable( logger, domain, level, caller, buf, tok.rest );
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
    protected int processVariable( TextLogger logger, AString domain, Log.Level level, CallerInfo caller, AString dest, Substring variable )
    {
        // process commands
        switch ( variable.consume() )
        {
            // caller info
            case 'C':
            {
                // read sub command
                char s= variable.consume();
                if ( s == 'L' )
                    dest._( caller.lineNumber );
                else
                    dest._NC( s == 'F' ?    caller.fileName      :
                                    s == 'P' ?    caller.packageName   :
                                    s == 'C' ?    caller.className     :
                                    s == 'M' ?    caller.methodName    : new AString("?") );
            }
            return 0;

            // Date
            case 'D':
            {
                // avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!)
                // and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
                if ( dateFormat.equals( defaultfmtDate ) )
                {
                    // set time in calendar object
                    caller.timeStamp.inJavaCalendar( callerDateTimeCal );
                    calInstanceSet= true;

                    // append date 'manually'
                    dest._( callerDateTimeCal.get( Calendar.YEAR  )        , 4 )._( '-' )
                        ._( callerDateTimeCal.get( Calendar.MONTH )        , 2 )._( '-' )
                        ._( callerDateTimeCal.get( Calendar.DAY_OF_MONTH ) , 2 );
                }

                // support user defined standards
                else
                {
                    // set time in date object
                    caller.timeStamp.inJavaDate( callerDateTimeDate );
                    dateInstanceSet= true;

                    // create date formatter once
                    if ( dateFormatter == null )
                        dateFormatter= new SimpleDateFormat( dateFormat, Locale.US );

                    // get date string from system and append to log buffer
                    tempSBuf.setLength( 0 );
                    dateFormatter.format( callerDateTimeDate, tempSBuf, fieldPositionZero );
                    dest._( tempSBuf );

                }
            }

            return 0;

            // %Tx: Time
            case 'T':
            {
                // read sub command
                char s= variable.consume();

                // %TD: Time of Day
                if ( s == 'D' )
                {
                    // avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!)
                    // and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
                    if ( timeOfDayFormat.equals( defaultfmtTimeOfDay ) )
                    {
                        // set time in calendar object
                        if ( ! calInstanceSet )
                            caller.timeStamp.inJavaCalendar( callerDateTimeCal );

                        dest ._( callerDateTimeCal.get( Calendar.HOUR_OF_DAY ),   2 )._( ':' )
                             ._( callerDateTimeCal.get( Calendar.MINUTE ),        2 )._( ':' )
                             ._( callerDateTimeCal.get( Calendar.SECOND ),        2 );
                    }

                    // support user defined standards
                    else
                    {
                        // set time in date object
                        if ( ! dateInstanceSet )
                            caller.timeStamp.inJavaDate( callerDateTimeDate );

                        if ( timeOfDayFormatter == null )
                            timeOfDayFormatter= new SimpleDateFormat( timeOfDayFormat, Locale.US );

                        tempSBuf.setLength( 0 );
                        timeOfDayFormatter.format( callerDateTimeDate, tempSBuf, fieldPositionZero );

                        dest._( tempSBuf );
                    }
                }

                // %TE: Time Elapsed
                else if ( s == 'E' )
                {
                    elapsed.set( caller.timeStamp.raw() - logger.timeOfCreation.raw() );

                    if ( elapsed.days  > 0 )  dest._( elapsed.days  )._( timeElapsedDays );
                    if ( elapsed.hours > 0 )  dest._( elapsed.hours )._( ':' );

                    dest._( elapsed.minutes,      2)._( ':' )
                        ._( elapsed.seconds,      2)._( '.' )
                        ._( elapsed.milliseconds, 3);


                }

                // %TE: Time Diff
                else
                    writeTimeDiff( dest, caller.timeStamp.since( logger.timeOfLastLog ).inNanos() );
            }
            return 0;


            // Thread
            case 't':
            {
                // append thread name
                dest.field()
                     ._( caller.threadName )
                   .field( logger.autoSizes.next( caller.threadName.length(), 0 ), Alignment.CENTER );
            }
            return 0;

            case 'L':    dest._( level == Log.Level.ERROR    ?  logLevelError     :
                                     level == Log.Level.WARNING  ?  logLevelWarning   :
                                     level == Log.Level.INFO     ?  logLevelInfo      :
                                                                    logLevelVerbose        );
            return 0;

            case 'O':
            {
                // log domain
                dest.field()
                     ._( domain )
                   .field( logger.autoSizes.next( domain.length(), 0 ), Alignment.CENTER );
            }
            return 0;

            case '#':    dest._( logger.cntLogs, logNumberMinDigits );
            return 0;

            // A: Auto tab
            case 'A':
            {
                // read extra space from format string
                int oldStart=    variable.start;
                int extraSpace=  variable.toInt();
                if ( oldStart == variable.start )
                    extraSpace=         1;

                // insert ESC code to jump to next tab level
                extraSpace= Math.min( extraSpace, 10 + ('Z'-'A') );
                char escNo= extraSpace < 10 ?   (char) ( '0' + extraSpace )
                                            :   (char) ( 'A' + extraSpace );

                dest._( "\033t" )._( escNo );
            }
            return 1;

            case 'N':    dest._( logger.name );
            return 0;

            default:
            {
                ALIB.ERROR( "Unknown format character \'" + variable.buf[variable.start - 1] + "\'" );
            }
            return 0;
        }

    }


    /** ********************************************************************************************
     * Helper function that logs a time given difference into the given buffer in a human readable
     * format. Works from nano seconds to days.
     *
     * @param buf        The buffer to write the time difference representation into.
     * @param diffNanos  The time difference to write in nanoseconds.
     **********************************************************************************************/
    protected void writeTimeDiff( AString buf, long diffNanos )
    {
        // unmeasurable?
        if ( diffNanos < timeDiffMinimum )
        {
            buf._( timeDiffNone );
            return;
        }

        if ( diffNanos < 1000 )
        {
            buf._( (int) diffNanos, 3 )._( timeDiffNanos );
            return;
        }

        // we continue with micros
        long diffMicros= diffNanos / 1000L;

        // below 1000 microseconds?
        if ( diffMicros < 1000 )
        {
            buf._( (int) diffMicros, 3 )._( timeDiffMicros );
            return;
        }

        // below 1000 ms?
        if ( diffMicros < 1000000 )
        {
            buf._( (int) (diffMicros / 1000), 3 )._( timeDiffMillis );
            return;
        }

        // below 10 secs (rounded) ?
        if ( diffMicros < 9995000 )
        {
            // convert to hundredth of secs
            long hundredthSecs=  ((diffMicros / 1000) + 5) / 10;

            // print two digits after dot x.xx
            buf._( (int) (hundredthSecs / 100), 1 )
               ._( '.' )
               ._( (int) (hundredthSecs % 100), 2 )
               ._( timeDiffSecs );

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
               ._( timeDiffSecs );
            return;
        }

        //     below 10 mins ?
        if ( tenthSecs < 6000 )
        {
            // convert to hundredth of minutes
            long hundredthMins=  tenthSecs / 6;

            // print two digits after dot x.xx
            buf._( (int) (hundredthMins / 100), 1 )
               ._( '.' )
               ._( (int) (hundredthMins % 100), 2 )
               ._( timeDiffMins );

            return;
        }

        // convert to tenth of minutes
        long tenthMins=  tenthSecs / 60;

        // below 100 mins ?
        if ( tenthMins < 1000 )
        {
            // print one digits after dot xx.x (round value by adding 5 hundredth)
            buf._( (int) (tenthMins / 10), 2 )
               ._( '.' )
               ._( (int) (tenthMins % 10), 1 )
               ._( timeDiffMins );
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
               ._( timeDiffHours );

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
               ._( timeDiffHours );
            return;
        }

        // below 100 hours ?
        if ( tenthHours < 1000 )
        {
            // print one digits after dot xx.x (round value by adding 5 hundredth)
            buf._( (int) (tenthHours / 10), 2 )
               ._( '.' )
               ._( (int) ((tenthHours / 10) % 10), 1 )
               ._( timeDiffHours );
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
               ._( timeDiffDays );
            return;
        }

        // 10 days or more (print days plus one digit after the comma)
        // print one digits after dot xx.x (round value by adding 5 hundredth)
        buf._( (int) (hundredthDays / 100), 2 )
           ._( '.' )
           ._( (int) ((hundredthDays / 10) % 10), 1 )
           ._( timeDiffDays );
    }

} // class
