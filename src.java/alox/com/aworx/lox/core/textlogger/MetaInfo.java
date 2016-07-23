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
import com.aworx.lib.Util;
import com.aworx.lib.enums.Alignment;
import com.aworx.lib.enums.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.Tokenizer;
import com.aworx.lib.time.TickSpan;
import com.aworx.lib.time.Ticks;
import com.aworx.lox.Verbosity;
import com.aworx.lox.core.Domain;
import com.aworx.lox.core.ScopeInfo;


/** ************************************************************************************************
 * This class is a sort of plug-in for the TextLogger class. Its purpose is to assemble the meta
 * information of each log line (things like timestamps, thread information, verbosity and domain, etc.).
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
         * - %SF: The callers' source file name
         * - %SP: The callers' package name
         * - %SC: The callers' class name
         * - %SL: The line number in the callers' source file
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
         *        #verbosityError, #verbosityWarning, #verbosityInfo and #verbosityVerbose.
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
         * \code "(%SF:%SL) %SM():%A5[%TC +%TL][%tN]%V[%D]%A1(%#): " \endcode
         *
         */
        public    AString               format
             =  new AString( "(%SF:%SL) %SM():%A5[%TC +%TL][%tN]%V[%D]%A1(%#): ");

        /** The replacement for variable \c %%V in field #format if \e Verbosity is \c ERROR */
        public    AString               verbosityError           = new AString( "[ERR]" );

        /** The replacement for variable \c %%V in field #format if \e Verbosity is \c WARNING */
        public    AString               verbosityWarning         = new AString( "[WRN]" );

        /** The replacement for variable \c %%V in field #format if \e Verbosity is \c INFO */
        public    AString               verbosityInfo            = new AString( "     " );

        /** The replacement for variable \c %%V in field #format if \e Verbosity is \c VERBOSE */
        public    AString               verbosityVerbose         = new AString( "[***]" );

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

        /**  
         * Object to retrieve formatted log date. This field has to be set to null,
         * when the field #dateFormat gets modified and log operations have been scheduled
         * since the creation of the \e Logger (respectively since the last change of that format).  
         */
        public    SimpleDateFormat      dateFormatter;

        /**
         * Object to retrieve formatted time of day. This field has to be set to null,
         * when the field #timeOfDayFormat gets modified and log operations have been scheduled
         * since the creation of the \e Logger (respectively since the last change of that format). 
         */
        public    SimpleDateFormat      timeOfDayFormatter;

        /**
         * The maximum time elapsed. Used to determine the width of the output when writing
         * the elapsed time.
         *
         * This field will be read from the 
         * configuration variable [ALOX_LOGGERNAME_MAX_ELAPSED_TIME](../group__GrpALoxConfigVars.html)
         * when the \b %TextLogger that this object belongs to is attached to a \b %Lox 
         * and written back on removal.
         */
        public    Ticks                 maxElapsedTime                           = new Ticks(0);

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /**  Internal calendar object to get string representations of dates. */
        protected Date                  callerDateTimeDate            = new Date();

        /**  Internal calendar object to get string representations of dates. */
        protected GregorianCalendar     callerDateTimeCal             = new GregorianCalendar();

        /**  Flag to indicate if date instance was set during one logText call  */
        protected boolean               dateInstanceSet;

        /**  Flag to indicate if calendar instance was set during one logText call  */
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

        /**  A reusable object for displaying the elapsed time */
        protected Ticks                 elapsedTime                   = new Ticks(0);

        /// Tokenizer used in #write.
        protected Tokenizer             tTok                          = new Tokenizer();

        /** A reusable AString . */
        protected AString               tmpAString                    = new AString();

        /** Helper flag that indicates if a format warning report was already issued */
        protected boolean               warnedOnce                    = false;

    /** ********************************************************************************************
     *  Parses the #format string and logs meta information into the log buffer.
     *  For each variable found, method #processVariable is invoked. Hence, to add new variables,
     *  the latter method can be overwritten by descendants. Overwriting this method is
     *  recommended for formatter classes that do not rely on format strings.
     *
     * @param logger    The logger that we are embedded in.
     * @param buf       The buffer to write meta information into.
     * @param domain    The <em>Log Domain</em>.
     * @param verbosity The verbosity. This has been checked to be active already on this
     *                  stage and is provided to be able to be logged out only.
     * @param scope     Information about the scope of the <em>Log Statement</em>..
     * @return The number of tab sequences that were written (by adding ESC::TAB to the buffer).
     **********************************************************************************************/
    protected int write( TextLogger logger, AString buf, Domain domain, Verbosity verbosity, ScopeInfo scope )
    {
        int qtyTabStops= 0;

        // check
        if ( format == null || format.isEmpty() )
            return 0;

        // set date object only once per loop
        calInstanceSet=  false;
        dateInstanceSet= false;

        // loop/switch over content specified in configuration array
        tTok.set( format, '%' );
        while ( true )
        {
            // get next and log substring between commands
            if ( tTok.next( Whitespaces.KEEP ).isNotEmpty() )
                buf._( tTok.actual );

            // previous next did not find a delimiter
            if ( !tTok.hasNext() )
                break;

            // process the found variable
            qtyTabStops+= processVariable( logger, domain, verbosity, scope, buf, tTok.rest );
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
     * @return The number of tab sequences that were written (by adding ESC::TAB to the buffer).
     **********************************************************************************************/
    protected int processVariable( TextLogger logger, Domain domain, Verbosity verbosity, ScopeInfo scope, AString dest, Substring variable )
    {
        // process commands
        char c2;
        switch ( variable.consume() )
        {
            // scope info
            case 'S':
            {
                // read sub command
                char s= variable.consume();
                if ( s == 'L' )
                    dest._( scope.getLineNumber() );
                else
                    dest._NC( s == 'F' ?    scope.getFileName()      :
                              s == 'P' ?    scope.getPackageName()   :
                              s == 'C' ?    scope.getClassName()     :
                              s == 'M' ?    scope.getMethodName()    : new AString("#ERROR") );
            }
            return 0;


            // %Tx: Time
            case 'T':
            {
                // read sub command
                c2= variable.consume();

                // %TD: Date
                if ( c2 == 'D' )
                {
                    // avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!)
                    // and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
                    if ( dateFormat.equals( defaultfmtDate ) )
                    {
                        // set time in calendar object
                        scope.timeStamp.inJavaCalendar( callerDateTimeCal );
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
                        scope.timeStamp.inJavaDate( callerDateTimeDate );
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

                // %TT: Time of Day
                else if ( c2 == 'T' )
                {
                    // avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!)
                    // and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
                    if ( timeOfDayFormat.equals( defaultfmtTimeOfDay ) )
                    {
                        // set time in calendar object
                        if ( ! calInstanceSet )
                            scope.timeStamp.inJavaCalendar( callerDateTimeCal );

                        dest ._( callerDateTimeCal.get( Calendar.HOUR_OF_DAY ),   2 )._( ':' )
                             ._( callerDateTimeCal.get( Calendar.MINUTE ),        2 )._( ':' )
                             ._( callerDateTimeCal.get( Calendar.SECOND ),        2 );
                    }

                    // support user defined standards
                    else
                    {
                        // set time in date object
                        if ( ! dateInstanceSet )
                            scope.timeStamp.inJavaDate( callerDateTimeDate );

                        if ( timeOfDayFormatter == null )
                            timeOfDayFormatter= new SimpleDateFormat( timeOfDayFormat, Locale.US );

                        tempSBuf.setLength( 0 );
                        timeOfDayFormatter.format( callerDateTimeDate, tempSBuf, fieldPositionZero );

                        dest._( tempSBuf );
                    }
                }

                // %TC: Time elapsed since created
                else if ( c2 == 'C' )
                {
                    elapsedTime.set( scope.timeStamp );
                    elapsedTime.sub( logger.timeOfCreation );
    
                    if( maxElapsedTime.raw() < elapsedTime.raw() )
                        maxElapsedTime.set( elapsedTime );
    
                    long      maxElapsedSecs= maxElapsedTime.inSeconds();
                    elapsed.set( elapsedTime );
    
                    if ( maxElapsedSecs >= 60*60*24 )  dest._( elapsed.days  )._NC( timeElapsedDays );
                    if ( maxElapsedSecs >= 60*60    )  dest._( elapsed.hours  ,  maxElapsedSecs >= 60*60*10 ?  2 : 1 )._( ':' );
                    if ( maxElapsedSecs >= 60       )  dest._( elapsed.minutes,  maxElapsedSecs >= 10*60    ?  2 : 1 )._( ':' );
                    dest._( elapsed.seconds,  maxElapsedSecs > 9 ? 2 : 1          )._( '.' );
                    dest._( elapsed.milliseconds,  3 );
                }

                // %TL: Time elapsed since last log call
                else if ( c2 == 'L' )
                    writeTimeDiff( dest, scope.timeStamp.since( logger.timeOfLastLog ).inNanos() );
                else
                {
                    if( !warnedOnce )
                    {
                        warnedOnce= true;
                        ALIB.WARNING( "Unknown format variable '%S" + c2 + "\' (only one warning)" );
                    }
                    dest._( "%ERROR" );
                }

                return 0;
            }

            // Thread
            case 't':
            {
                c2= variable.consume();
                if ( c2 == 'N' )
                {
                    AString threadName= scope.getThreadName();
                    dest.field()
                         ._( threadName )
                       .field( logger.autoSizes.next( threadName.length(), 0 ), Alignment.CENTER );
                }
                else if ( c2 == 'I' )
                {
                    tmpAString._()._( scope.getThreadID() );
                    dest.field()
                         ._( tmpAString )
                       .field( logger.autoSizes.next( tmpAString.length()      , 0 ), Alignment.CENTER );
                }
                else
                {
                    if( !warnedOnce )
                    {
                        warnedOnce= true;
                        ALIB.WARNING( "Unknown format variable '%t" + c2 + "\' (only one warning)" );
                    }
                    dest._( "%ERROR" );
                }

                return 0;
            }

            case 'L':
            {
                c2= variable.consume();
                     if ( c2 == 'G' )     dest._NC( logger.getName() );
                else if ( c2 == 'X' )     dest._NC( scope.getLoxName() );
                else
                {
                    if( !warnedOnce )
                    {
                        warnedOnce= true;
                        ALIB.WARNING( "Unknown format variable '%L" + c2 + "\' (only one warning)" );
                    }
                    dest._( "%ERROR" );
                    return 0;
                }
                return 0;
            }

            case 'P':
            {
                dest._NC( Util.getProcessName() );
                return 0;
            }

            case 'V':    dest._( verbosity == Verbosity.ERROR    ?  verbosityError     :
                                 verbosity == Verbosity.WARNING  ?  verbosityWarning   :
                                 verbosity == Verbosity.INFO     ?  verbosityInfo      :
                                                                    verbosityVerbose        );
                        return 0;

            case 'D':
            {
                dest.field()._( domain.fullPath ).field( logger.autoSizes.next( domain.fullPath.length(), 0 ), Alignment.LEFT );
                return 0;
            }

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
                return 1;
            }

            default:
            {
                ALIB.ERROR( "Unknown format character \'" + variable.buf[variable.start - 1] + "\'" );
                return 0;
            }
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
