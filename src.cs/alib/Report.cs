﻿// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System.Runtime.CompilerServices;
using System;
using System.Diagnostics;
using System.Text;
using System.Threading;
using cs.aworx.lib.threads;
using cs.aworx.lib.config;
using cs.aworx.lib.time;

namespace cs.aworx.lib {


/** ************************************************************************************************
 * This class provides a simple facility to collect what is called a \e 'report'.
 * Reports are maintenance messages, similar to error messages, but is not aiming to replace
 * and error handling.
 * (Sending a \e 'report' usually precedes raising an error.)
 * Also, \e 'reports' are not replacing any debug or release logging facility, which is not
 * part of ALib. Much more, logging libraries (like \e ALox Logging Library, which
 * builds on ALib, does) might provide a derived object of type
 * \ref aworx::lib::ReportWriter "ReportWriter" to plug into the ALib report facility.
 * This way, the concepts of logging and reports get unified.
 *
 * While a process can createe different objects of this class, usually, the default instance,
 * received by
 * \ref cs::aworx::lib::Report::GetDefault "GetDefault".
 * is sufficient and all warnings and errors will be directed to this one. ALib itself directs
 * all messages to the default instance.
 *
 * This class uses a singleton of type
 * \ref cs::aworx::lib::ReportWriter "ReportWriter" to actually write the reports. By default, an
 * object of type
 * \ref cs::aworx::lib::ConsoleReportWriter "ConsoleReportWriter" is attached.
 *
 * The reporting method,
 * \ref cs::aworx::lib::Report::DoReport "DoReport" will check the public flag
 * \ref cs::aworx::lib::Report.HaltOnError "HaltOnError" respectively
 * \ref cs::aworx::lib::Report.HaltOnWarning "HaltOnWarning",
 * which if \c true, causes the method to invoke \e assert(). Such assertions are effective
 * only in the debug compilation of the library/executable. Custom \e 'ReportWriters' might
 * take action (e.g. for security reasons) and e.g. terminate the application also in
 * release compilations.
 *
 * To simplify things, a set of static methods are defined in class
 * \ref cs::aworx::lib::ALIB "ALIB" wich are deemed to be
 * pruned in release versions of the compilation unit. These are:
 *
 * - \ref cs::aworx::lib::ALIB::ERROR           "ALIB.ERROR"
 * - \ref cs::aworx::lib::ALIB::WARNING         "ALIB.WARNING"
 * - \ref cs::aworx::lib::ALIB::ASSERT          "ALIB.ASSERT"
 * - \ref cs::aworx::lib::ALIB::ASSERT_ERROR    "ALIB.ASSERT_ERROR"
 * - \ref cs::aworx::lib::ALIB::ASSERT_WARNING  "ALIB.ASSERT_WARNING"
 *
 * The use of these methods is recommended and preferred over the direct use of class Report
 * whenever pure debug reports are intended.
 **************************************************************************************************/
public class Report
{
    /** A report message.  */
    public class Message
    {
        /** The file name that reported.  */
        public String      File;

        /** The line number in the source file that reported.  */
        public int         Line;

        /** The function/method name that reported.  */
        public String      Func;

        /** The message type. '0' indicates \e 'severe' errors. Others are warnings and may be
         *  defined (interpreted) by custom implementations of
         *  \ref aworx::lib::ReportWriter "ReportWriter".  */
        public int         Type;

        /** The message.  */
        public String      Contents;

        /** Constructs a message.
         * @param type The message type.
         * @param msg  The message.
         * @param csf  (Optional) Caller info, compiler generated. Please omit.
         * @param cln  (Optional) Caller info, compiler generated. Please omit.
         * @param cmn  (Optional) Caller info, compiler generated. Please omit.
         */
        public Message( int type, String msg,  String csf="",  int    cln= 0, String cmn=""  )
        {
            Type=     type;
            Contents= msg;
            File= csf;
            Line= cln;
            Func= cmn;
        }
    };

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /**  The ReportWriter.  */
        protected         ReportWriter      writer                      =new ConsoleReportWriter();

        /** The default Report used internally by ALib and usually by processes that rely on ALib.*/
        protected static  Report            defaultReport                            =new Report();

        /** This is a flag that avoids recursion. Recursion might occur when a more sophisticated
         * report writer sends a report (e.g. an ALIB Error or Warning). Recursive calls are 
         * rejected without further notice.
         */
        protected         bool              recursionBlocker                              = false;

        /** A Lock to protect against multihreaded calls.     */
        protected         ThreadLock        Lock
                                                            #if ALOX_NO_THREADS // ->unsafe
                                                                      =new ThreadLock( true, true );
                                                            #else
                                                                      =new ThreadLock();
                                                            #endif
    

    // #############################################################################################
    // public fields
    // #############################################################################################

        /**
         * Flag, which if set to true, causes calls to #DoReport with report type \e '0'
         * to halt program execution if executed in debugger.
         * Can be set at runtime by just overwriting the value.
         * Defaults to true
         */
        public     bool                     HaltOnError                                       =true;

        /**
         * Flag, which if set to true, causes calls to #DoReport with report type not equal to
         * \e '0' to halt program execution if executed in debugger.
         * Can be set at runtime by just overwriting the value.
         * Defaults to true
         */
        public     bool                     HaltOnWarning                                    =false;


    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         * Receives the default report object used by ALib and processes that rely on ALib.
         * @returns The default \b Report.
         ******************************************************************************************/
        public static Report  GetDefault()           { return defaultReport; }

        /** ****************************************************************************************
         * Replaces the current \b %ReportWriter singleton by the one provided.
         * If null is provided, a new instance of
         * \ref cs::aworx::lib::ConsoleReportWriter "ConsoleReportWriter" is created and set.
         *
         * @param newWriter The \b %ReportWriter to set.
         * @return The former \b %ReportWriter.
         ******************************************************************************************/
        public ReportWriter ReplaceWriter( ReportWriter newWriter )
        {
            try { Lock.Acquire();
                ReportWriter oldEH= writer;
                writer= newWriter != null ? newWriter
                                          : new ConsoleReportWriter();
                return oldEH;
            } finally { Lock.Release(); }
        }

        /** ****************************************************************************************
         * Reports the given message to the current
         * \ref aworx::lib::ReportWriter "ReportWriter" in place. The default \b ReportWriter
         * will print the message on the process console. Furthermore, in debug
         * execution the flag #HaltOnError, respectively #HaltOnWarning, is checked.
         * If this is set the program halts or suspends into the debugger
         * (platform and language specific).
         *
         * If parameter \p is '0', the report is considered a \e severe error, otherwise a warning.
         * User defined implementations of class \e %ReportWriter may interpret this field
         * arbitrarily.
         *
         * @param type The report type.
         * @param msg  The report message.
         * @param csf  (Optional) Caller info, compiler generated. Please omit.
         * @param cln  (Optional) Caller info, compiler generated. Please omit.
         * @param cmn  (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        public void DoReport( int type, String msg,
                              [CallerFilePath]   String csf="",
                              [CallerLineNumber] int    cln= 0,
                              [CallerMemberName] String cmn=""      )

        {
            try { Lock.Acquire();
                if ( recursionBlocker )
                    return;
                recursionBlocker= true;
                    Message message= new Message( type, msg, csf, cln, cmn );
                    writer.Report( message );
        
                    System.Diagnostics.Debug.Assert( !(     (type == 0 && HaltOnError)
                                                         || (type != 0 && HaltOnWarning)
                                                      ),  msg );
                recursionBlocker= false;
            } finally { Lock.Release(); }
        }
}// class ReportWriter



} // namespace / EOF