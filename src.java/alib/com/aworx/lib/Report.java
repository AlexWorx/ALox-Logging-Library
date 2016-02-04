// ########################s#########################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


package com.aworx.lib;

/** ************************************************************************************************
 * This class provides a simple facility to collect what is called a \e 'report'.
 * Reports are maintenance messages, similar to error messages, but are not aiming to replace
 * error handling.
 * (Sending a \e 'report' usually precedes raising an error.)
 * Also, \e 'reports' are not replacing any debug or release logging facility, which is not
 * part of ALib. Much more, logging libraries might provide a derived object of type
 * \ref aworx::lib::ReportWriter "ReportWriter" to plug into ALibs' report facility
 * (like <em>ALox Logging Library</em> does, which completely builds on ALib).
 * This way, the concepts of logging and reports get unified.
 *
 * While a process can create different objects of this class, usually the default instance,
 * received by
 * \ref com::aworx::lib::Report::getDefault "getDefault".
 * is sufficient and all warnings and errors will be directed to this one. ALib itself directs
 * all messages to the default instance.
 *
 * This class uses a singleton of type
 * \ref com::aworx::lib::ReportWriter "ReportWriter" to actually write the reports. By default, an
 * object of type
 * \ref com::aworx::lib::ConsoleReportWriter "ConsoleReportWriter" is attached.
 *
 * The reporting method,
 * \ref com::aworx::lib::Report::doReport "doReport" will check the public flag
 * \ref com::aworx::lib::Report.haltOnError "haltOnError" respectively
 * \ref com::aworx::lib::Report.haltOnWarning "haltOnWarning",
 * which if \c true, causes the method to invoke \e assert() after the \b ReportWriter was called.
 * Such assertions are effective only in the debug compilation of the library/executable.
 * Custom implementations of class \b ReportWriter might take other actions.
 *
 * To simplify things, a set of static methods are defined in class
 * \ref com::aworx::lib::ALIB "ALIB" which  are deemed to be
 * pruned in release versions of the compilation unit. These are:
 *
 * - \ref com::aworx::lib::ALIB::ERROR           "ALIB.ERROR"
 * - \ref com::aworx::lib::ALIB::WARNING         "ALIB.WARNING"
 * - \ref com::aworx::lib::ALIB::ASSERT          "ALIB.ASSERT"
 * - \ref com::aworx::lib::ALIB::ASSERT_ERROR    "ALIB.ASSERT_ERROR"
 * - \ref com::aworx::lib::ALIB::ASSERT_WARNING  "ALIB.ASSERT_WARNING"
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
        public String      contents;

        /** The message type. '0' indicates \e 'severe' errors. Others are warnings and may be
         *  defined (interpreted) by custom implementations of
         *  \ref aworx::lib::ReportWriter "ReportWriter".  */
        public int         type;


        /** Constructs a message.
         * @param type The message type.
         * @param msg  The message.
         */
        public Message( int type, String msg  )
        {
            this.type=     type;
            this.contents= msg;
        }
    };

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /**  The ReportWriter.  */
        protected         ReportWriter      writer                       =new ConsoleReportWriter();

        /** The default Report used internally by ALib and usually by processes that rely on ALib. */
        protected static  Report            defaultReport                             =new Report();

        /** This is a flag that avoids recursion. Recursion might occur when a more sophisticated
         * report writer sends a report (e.g. an ALIB Error or Warning). Recursive calls are 
         * rejected without further notice.
         */
        protected         boolean           recursionBlocker             = false;

    // #############################################################################################
    // public fields
    // #############################################################################################

        /**
         * Flag, which if set to true, causes calls to #doReport with report type \e '0'to halt
         * program execution if executed in debugger.
         * Can be set at runtime by just overwriting the value.
         * Defaults to true.
         */
        public     boolean                  haltOnError                                       =true;

        /**
         * Flag, which if set to true, causes calls to #doReport with report type not equal to
         * \e '\0' to halt program execution if executed in debugger.
         * Can be set at runtime by just overwriting the value.
         * Defaults to true.
         */
        public     boolean                  haltOnWarning                                    =false;


    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         * Receives the default report object used by ALib and processes that rely on ALib.
         * @returns The default \b Report.
         ******************************************************************************************/
        public static Report  getDefault()           { return defaultReport; }

        /** ****************************************************************************************
         * Replaces the current
         * \ref aworx::lib::ReportWriter "ReportWriter" singleton by the one provided.
         * If null is provided, a new instance of
         * \ref com::aworx::lib::ConsoleReportWriter "ConsoleReportWriter" is created and set.
         *
         * @param newWriter The \b %ReportWriter to set.
         * @return The former \b %ReportWriter. 
         ******************************************************************************************/
        synchronized
        public ReportWriter replaceWriter( ReportWriter newWriter )
        {
            ReportWriter oldEH= writer;
            writer= newWriter != null ? newWriter
                                      : new ConsoleReportWriter();
            return oldEH;
        }

        /** ****************************************************************************************
         * Reports the given message to the current
         * \ref aworx::lib::ReportWriter "ReportWriter" in place. The default \b ReportWriter
         * will print the message on the process console. Furthermore, in debug
         * execution the flag #haltOnError, respectively #haltOnWarning, is checked.
         * If this is set the program halts or suspends into the debugger
         * (platform and language specific).
         *
         * If parameter \p is '0', the report is considered a \e severe error, otherwise a warning.
         * User defined implementations of class \e %ReportWriter may interpret this field
         * arbitrarily.
         *
         * @param type The report type.
         * @param msg  The report message.
         ******************************************************************************************/
        synchronized
        public void doReport( int type, String msg  )

        {
            if ( recursionBlocker )
                return;
            recursionBlocker= true;
                Message message= new Message( type, msg );
                writer.report( message );
                assert !(     (type == 0 && haltOnError)
                           || (type != 0 && haltOnWarning)
                         ):  msg;
            recursionBlocker= false;
        }
}// class ReportWriter

