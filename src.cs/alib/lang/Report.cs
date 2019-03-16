// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System.Runtime.CompilerServices;
using System;
using System.Diagnostics;
using System.Text;
using System.Threading;
using cs.aworx.lib.threads;
using cs.aworx.lib.config;
using cs.aworx.lib.time;
using System.Collections.Generic;
using cs.aworx.lib.lang;

namespace cs.aworx.lib.lang {


/** ************************************************************************************************
 * This class provides a simple facility to collect what is called a \e 'report'.
 * Reports are maintenance messages, mostly error and warning messages, but is not aiming to replace
 * any sort of error handling.
 * (In ALib itself, sending a \e 'report' usually precedes raising an error.)
 * Also, \e reports are not replacing any debug or release logging facility, which is not
 * part of ALib. Much more, logging libraries might provide a derived object of type
 * \ref cs.aworx.lib.lang.ReportWriter "ReportWriter" to plug into ALib report facility.
 * This way, the concepts of logging and reports get unified. (As a sample,
 * <em>ALox Logging Library </em> which builds on ALib does so.)
 *
 * While a process can create different objects of this class, usually, the default instance,
 * received by
 * \ref cs.aworx.lib.lang.Report.GetDefault "GetDefault".
 * is sufficient and all warnings and errors will be directed to this one. ALib itself directs
 * all internal reports to the default instance.
 *
 * This class uses a singleton of type
 * \ref cs.aworx.lib.lang.ReportWriter "ReportWriter" to actually write the reports. By default, an
 * object of type
 * \ref cs.aworx.lib.lang.ReportWriterStdIO "ReportWriterStdIO" is attached.
 *
 * The reporting method,
 * \ref cs.aworx.lib.lang.Report.DoReport "DoReport" will check the flags provided with
 * \ref cs.aworx.lib.lang.Report.PushHaltFlags "PushHaltFlags" for message types \c 0 (errors)
 * and \c 1 (warnings), and may invoke \e assert(). Such assertions are effective
 * only in the debug compilation of the library/executable. Custom \e 'ReportWriters' might
 * take action (e.g. for security reasons) and e.g. terminate the application also in
 * release compilations.
 *
 * To simplify things, a set of static methods are defined in class
 * \ref cs.aworx.lib.ALIB "ALIB" which are deemed to be
 * pruned in release versions of the compilation unit. These are:
 *
 * - \ref cs.aworx.lib.ALIB_DBG.REPORT          "ALIB_DBG.REPORT"
 * - \ref cs.aworx.lib.ALIB_DBG.ERROR           "ALIB_DBG.ERROR"
 * - \ref cs.aworx.lib.ALIB_DBG.WARNING         "ALIB_DBG.WARNING"
 * - \ref cs.aworx.lib.ALIB_DBG.ASSERT          "ALIB_DBG.ASSERT"
 * - \ref cs.aworx.lib.ALIB_DBG.ASSERT_ERROR    "ALIB_DBG.ASSERT_ERROR"
 * - \ref cs.aworx.lib.ALIB_DBG.ASSERT_WARNING  "ALIB_DBG.ASSERT_WARNING"
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

        /**
         * The message type. \c 0 indicates \e 'severe' errors, \c 1 warnings.
         * Others are status messages and may be defined (interpreted) by custom
         * implementations of
         * \ref cs.aworx.lib.lang.ReportWriter "ReportWriter".
         */
        public int         Type;

        /** The message.  */
        public Object[]    Contents;

        /** Constructs a message.
         * @param type      The message type.
         * @param contents  The message.
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         */
        public Message( int type, Object[] contents,  String csf="",  int    cln= 0, String cmn=""  )
        {
            Type=     type;
            Contents= contents;
            File=     csf;
            Line=     cln;
            Func=     cmn;
        }
    };

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /** The default Report used internally by ALib and usually by processes that rely on ALib.*/
        protected static  Report                defaultReport                         =new Report();

        /** This is a flag that avoids recursion. Recursion might occur when a more sophisticated
         * report writer sends a report (e.g. an ALIB Error or Warning). Recursive calls are
         * rejected without further notice.
         */
        protected         bool                  recursionBlocker                           = false;

        /** A Lock to protect against multihreaded calls.     */
        protected         ThreadLock            Lock                             =new ThreadLock();

         /**
         * A stack of integers. The topmost value is used to decide, whether program execution is
         * halted on message of type 'error' (type \c 0, bit \c 0) or of type 'warning'
         * (type \c 1, bit \c 1).
         * Can be set at runtime using methods #PushHaltFlags and #PopHaltFlags.
         */
        protected         Stack<int>            haltAfterReport                 = new Stack<int>();

        /**
         * A stack of writers. The topmost one is the actual.
         * Can be set at runtime using methods #PushWriter and #PopWriter.
         */
        protected         Stack<ReportWriter>   writers                 =new Stack<ReportWriter>();


    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         * Constructor
         ******************************************************************************************/
        public Report()
        {
            PushHaltFlags( true,  false );
            PushWriter( ReportWriterStdIO.Singleton );
        }

        /** ****************************************************************************************
         * Receives the default report object used by ALib and processes that rely on ALib.
         * @returns The default \b Report.
         ******************************************************************************************/
        public static Report  GetDefault()           { return defaultReport; }

        /** ****************************************************************************************
         * Sets a new writer. The actual writer is implemented as a stack. It is important to
         * keep the right order when pushing and popping writers, as there lifetime is externally
         * managed. (In standard use-cases, only one, app-specific writer should be pushed anyhow).
         * To give a little assurance, method #PopWriter takes the same parameter as this method
         * does, to verify if if the one to be removed is really the topmost.
         *
         * @param newWriter   The writer to use.
         ******************************************************************************************/
        public void PushWriter( ReportWriter newWriter )
        {
            try { Lock.Acquire();

                if ( writers.Count > 0 )
                    writers.Peek().NotifyActivation( Phase.End );

                writers.Push( newWriter );
                newWriter.NotifyActivation( Phase.Begin );
            } finally { Lock.Release(); }
        }

        /** ****************************************************************************************
         * Restores the previous writer after setting a new one using #PushWriter.
         * It is important to keep the right order when pushing and popping writers, as there
         * lifetime is externally managed.
         * (In standard use-cases, only one, app-specific writer should be pushed anyhow).
         * To give a little assurance, this method #PopWriter takes the same parameter as
         * #PushWriter does, to verify if the one to be removed is really the topmost.
         *
         * @param checkWriter  The previously pushed writer (for checking of call order).
         ******************************************************************************************/
        public void PopWriter( ReportWriter checkWriter )
        {
            try { Lock.Acquire();
                if ( writers.Count  == 0 )             { ALIB_DBG.ERROR( "No Writer to remove" );          return; }
                if ( writers.Peek() != checkWriter )   { ALIB_DBG.ERROR( "Report Writer is not actual" );  return; }

                writers.Peek().NotifyActivation( Phase.End );
                writers.Pop();
                if ( writers.Count > 0 )
                    writers.Peek().NotifyActivation( Phase.Begin );

            } finally { Lock.Release(); }
        }

        /** ****************************************************************************************
         * Retrieves the actual report writer.
         *
         * \note This method should not be used to retrieve the writer and use it. It should be used
         *       only to test the installation.
         * @return The actual report writer in place.
         ******************************************************************************************/
        public ReportWriter PeekWriter()
        {
            try { Lock.Acquire();
                return writers.Peek();
            } finally { Lock.Release(); }
        }


        /** ****************************************************************************************
         * Writes new values to the internal flags that decide if calls to #DoReport with
         * report type \e '0' (errors), respectively report type '>0' (warnings) cause
         * to halt program execution by calling <em>assert(false)</em>.
         * The previous values can be restored using #PopHaltFlags.
         * @param haltOnErrors      Specifies if halting on errors is wanted.
         * @param haltOnWarnings    Specifies if halting on warnings is wanted.
         ******************************************************************************************/
        public void PushHaltFlags( bool haltOnErrors, bool haltOnWarnings )
        {
            try { Lock.Acquire();
                haltAfterReport.Push(    (haltOnErrors   ? 1 : 0)
                                       + (haltOnWarnings ? 2 : 0));
            } finally { Lock.Release(); }
        }

        /** ****************************************************************************************
         * Restores the previous values after an invocation to #PushHaltFlags.
         ******************************************************************************************/
        public void PopHaltFlags()
        {
            #if DEBUG
                bool stackEmptyError;
            #endif

            try { Lock.Acquire();
                haltAfterReport.Pop();

                #if DEBUG
                    stackEmptyError= haltAfterReport.Count == 0;
                #endif
            } finally { Lock.Release(); }

            #if DEBUG
                if ( stackEmptyError )
                {
                    PushHaltFlags( true, true );
                    ALIB_DBG.ERROR( "Stack empty, too many pop operations" );
                }
            #endif
        }

        /** ****************************************************************************************
         * Reports the given message to the current
         * \ref cs.aworx.lib.lang.ReportWriter "ReportWriter" in place. The default \b ReportWriter
         * will print the message on the process console. Furthermore, in debug
         * execution the flags provided with #PushHaltFlags is checked.
         * If this is set for the type of message, the program halts or suspends into the debugger
         * (platform and language specific).
         *
         * If parameter \p{is} '0', the report is considered a \e severe error, otherwise a warning.
         * User defined implementations of class \e %ReportWriter may interpret this field
         * arbitrarily.
         *
         * @param type The report type.
         * @param msg      The report object.
         * @param optMsg2  An optional additional report object.
         * @param optMsg3  An optional additional report object.
         * @param optMsg4  An optional additional report object.
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        public void DoReport( int type, Object msg,
                              Object optMsg2    = null,
                              Object optMsg3    = null,
                              Object optMsg4    = null,
                              [CallerFilePath]   String csf="",
                              [CallerLineNumber] int    cln= 0,
                              [CallerMemberName] String cmn=""      )

        {
            try { Lock.Acquire();
                if ( recursionBlocker )
                    return;
                recursionBlocker= true;
                    Object[] report;
                         if( optMsg4 != null) report= new Object[]{ msg, optMsg2, optMsg3, optMsg4 };
                    else if( optMsg3 != null) report= new Object[]{ msg, optMsg2, optMsg3 };
                    else if( optMsg2 != null) report= new Object[]{ msg, optMsg2 };
                    else                      report= new Object[]{ msg };
                    Message message= new Message( type, report, csf, cln, cmn );
                    if ( writers.Count > 0 )
                        writers.Peek().Report( message );
                    int haltFlags= haltAfterReport.Peek();
                    System.Diagnostics.Debug.Assert( !(    (type == 0 && ( (haltFlags & 1) != 0) )
                                                        || (type != 0 && ( (haltFlags & 2) != 0) )
                                                      ),  "Runtime Error (see report message)" );
                recursionBlocker= false;
            } finally { Lock.Release(); }
        }


}// class ReportWriter



} // namespace / EOF
