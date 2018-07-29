// ########################s#########################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.lang;

import java.util.Deque;
import java.util.LinkedList;

/** ************************************************************************************************
 * This class provides a simple facility to collect what is called a \e 'report'.
 * Reports are maintenance messages, mostly error and warning messages, but is not aiming to replace
 * any sort of error handling.
 * (In \b %ALib itself, sending a \e 'report' usually precedes raising an error.)
 * Also, \e reports are not replacing any debug or release logging facility, which is not
 * part of \b %ALib. Much more, logging libraries might provide a derived object of type
 * \ref com.aworx.lib.lang.ReportWriter "ReportWriter" to plug into \b %ALib report facility.
 * This way, the concepts of logging and reports get unified. (As a sample,
 * <b>%ALox Logging Library </b> which builds on \b %ALib does so.)
 *
 * While a process can create different objects of this class, usually, the default instance,
 * received by
 * \ref com.aworx.lib.lang.Report.getDefault "getDefault".
 * is sufficient and all warnings and errors will be directed to this one. \b %ALib itself directs
 * all internal reports to the default instance.
 *
 * This class uses a singleton of type
 * \ref com.aworx.lib.lang.ReportWriter "ReportWriter" to actually write the reports. By default, an
 * object of type
 * \ref com.aworx.lib.lang.ReportWriterStdIO "ReportWriterStdIO" is attached.
 *
 * The reporting method,
 * \ref com.aworx.lib.lang.Report.doReport      "doReport" will check the flags provided with
 * \ref com.aworx.lib.lang.Report.pushHaltFlags "pushHaltFlags" for message types \c 0 (errors)
 * and \c 1 (warnings), and may invoke \e assert(). Such assertions are effective
 * only in the debug compilation of the library/executable. Custom \e 'ReportWriters' might
 * take action (e.g. for security reasons) and e.g. terminate the application also in
 * release compilations.
 *
 * To simplify things, a set of static methods are defined in class
 * \ref com.aworx.lib.ALIB "ALIB" which  are deemed to be
 * pruned in release versions of the compilation unit. These are:
 *
 * - \ref com.aworx.lib.ALIB_DBG.REPORT          "ALIB_DBG.REPORT"
 * - \ref com.aworx.lib.ALIB_DBG.ERROR           "ALIB_DBG.ERROR"
 * - \ref com.aworx.lib.ALIB_DBG.WARNING         "ALIB_DBG.WARNING"
 * - \ref com.aworx.lib.ALIB_DBG.ASSERT          "ALIB_DBG.ASSERT"
 * - \ref com.aworx.lib.ALIB_DBG.ASSERT_ERROR    "ALIB_DBG.ASSERT_ERROR"
 * - \ref com.aworx.lib.ALIB_DBG.ASSERT_WARNING  "ALIB_DBG.ASSERT_WARNING"
 *
 * The use of these methods is recommended and preferred over the direct use of class Report
 * whenever pure debug reports are intended.
 **************************************************************************************************/
public class Report
{
    /** A report message.  */
    public class Message
    {
        /** The message.  */
        public Object[]    contents;

        /**
         * The message type. \c 0 indicates \e 'severe' errors, \c 1 warnings.
         * Others are status messages and may be defined (interpreted) by custom
         * implementations of
         * \ref com.aworx.lib.lang.ReportWriter "ReportWriter".
         */
        public int         type;


        /** Constructs a message.
         * @param type The message type.
         * @param msg  The message.
         */
        public Message( int type, Object[] msg  )
        {
            this.type=     type;
            this.contents= msg;
        }
    }

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /** The default Report used internally by \b %ALib and usually by processes that rely on \b %ALib. */
        protected static  Report            defaultReport                             =new Report();

        /** This is a flag that avoids recursion. Recursion might occur when a more sophisticated
         * report writer sends a report (e.g. an ALIB Error or Warning). Recursive calls are
         * rejected without further notice.
         */
        protected         boolean           recursionBlocker                                 =false;

        /**
         * A stack of integers. The topmost value is used to decide, whether program execution is
         * halted on message of type 'error' (type \c 0, bit \c 0) or of type 'warning'
         * (type \c 1, bit \c 1).
         * Can be set at runtime using methods #pushHaltFlags and #popHaltFlags.
         */
        protected         Deque<Integer>    haltAfterReport              =new LinkedList<Integer>();

        /**
         * A stack of writers. The topmost one is the actual.
         * Can be set at runtime using methods #pushWriter and #popWriter.
         */
        protected         Deque<ReportWriter> writers               =new LinkedList<ReportWriter>();


    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         * Constructor
         ******************************************************************************************/
        public Report()
        {
            pushHaltFlags( true,  false );
            pushWriter( ReportWriterStdIO.SINGLETON );
        }

        /** ****************************************************************************************
         * Receives the default report object used by \b %ALib and processes that rely on \b %ALib.
         * @returns The default \b Report.
         ******************************************************************************************/
        public static Report  getDefault()           { return defaultReport; }

        /** ****************************************************************************************
         * Sets a new writer. The actual writer is implemented as a stack. It is important to
         * keep the right order when pushing and popping writers, as there lifetime is externally
         * managed. (In standard use-cases, only one, app-specific writer should be pushed anyhow).
         * To give a little assurance, method #popWriter takes the same parameter as this method
         * does, to verify if if the one to be removed is really the topmost.
         * @param newWriter   The writer to use.
         ******************************************************************************************/
        synchronized
        public void          pushWriter( ReportWriter newWriter )
        {
            if ( writers.size() > 0 )
                writers.peek().NotifyActivation( Phase.END );

            writers.push( newWriter );
            newWriter.NotifyActivation( Phase.BEGIN );
        }

        /** ****************************************************************************************
         * Restores the previous writer after setting a new one using #pushWriter.
         * It is important to keep the right order when pushing and popping writers, as there
         * lifetime is externally managed.
         * (In standard use-cases, only one, app-specific writer should be pushed anyhow).
         * To give a little assurance, this method #popWriter takes the same parameter as
         * #pushWriter does, to verify if the one to be removed is really the topmost.
         *
         * @param checkWriter  The previously pushed writer (for checking of call order).
         ******************************************************************************************/
        synchronized
        public void          popWriter( ReportWriter checkWriter )
        {
            if ( writers.size() == 0 )             { com.aworx.lib.ALIB_DBG.ERROR( "No Writer to remove" );          return; }
            if ( writers.peek() != checkWriter )   { com.aworx.lib.ALIB_DBG.ERROR( "Report Writer is not actual" );  return; }

            writers.peek().NotifyActivation( Phase.END );
            writers.pop();
            if ( writers.size() > 0 )
                writers.peek().NotifyActivation( Phase.BEGIN );

        }

        /** ****************************************************************************************
         * Retrieves the actual report writer.
         *
         * \note This method should not be used to retrieve the writer and use it. It should be used
         *       only to test the installation.
         *
         * @return The actual report writer in place.
         ******************************************************************************************/
        synchronized
        public ReportWriter peekWriter()
        {
            return writers.peek();
        }

        /** ****************************************************************************************
         * Writes new values to the internal flags that decide if calls to #doReport with
         * report type \e '0' (errors), respectively report type '>0' (warnings) cause
         * to halt program execution by calling <em>assert(false)</em>.
         * The previous values can be restored using #popHaltFlags.
         * @param haltOnErrors      Specifies if halting on errors is wanted.
         * @param haltOnWarnings    Specifies if halting on warnings is wanted.
         ******************************************************************************************/
        synchronized
        public void pushHaltFlags( boolean haltOnErrors, boolean haltOnWarnings )
        {
            haltAfterReport.push(new Integer(   (haltOnErrors   ? 1 : 0)
                                              + (haltOnWarnings ? 2 : 0)  ));
        }

        /** ****************************************************************************************
         * Restores the previous values after an invocation to #pushHaltFlags.
         ******************************************************************************************/
        synchronized
        public void popHaltFlags()
        {
            haltAfterReport.pop();
        }

        /** ****************************************************************************************
         * Reports the given message to the current
         * \ref com.aworx.lib.lang.ReportWriter "ReportWriter" in place. The default \b ReportWriter
         * will print the message on the process console. Furthermore, in debug
         * execution the flags provided with #pushHaltFlags is checked.
         * If this is set for the type of message, the program halts or suspends into the debugger
         * (platform and language specific).
         *
         * If parameter \p{is} '0', the report is considered a \e severe error, otherwise a warning.
         * User defined implementations of class \e %ReportWriter may interpret this field
         * arbitrarily.
         *
         * \note
         *   In Java, assertions are disabled by default. Therefore, to really have your program
         *   'halted' on reports, assertions have to be enabled, by providing parameter
         *   \c -enableassertions to the Java virtual machine.
         *
         * @param type The report type.
         * @param msg  The report message.
         ******************************************************************************************/
        synchronized
        public void doReport( int type, Object... msg )

        {
            if ( recursionBlocker )
                return;
            recursionBlocker= true;
                Message message= new Message( type, msg );
                if ( writers.size() > 0 )
                    writers.peek().report( message );
                int haltFlags= haltAfterReport.element().intValue();

// As an alternative to enabling jvm assert, this can be undocumented and a breakpoint may be set
/*
 if (    (type == 0 && ( (haltFlags & 1) != 0) )
      || (type != 0 && ( (haltFlags & 2) != 0) )
    )
 {
      System.out.println( "This should be commented out. For debug, set a breakpoint here! " );
 }
*/

                assert !(     (type == 0 && ( (haltFlags & 1) != 0) )
                           || (type != 0 && ( (haltFlags & 2) != 0) )
                         ):  msg;
            recursionBlocker= false;
        }

}// class ReportWriter

