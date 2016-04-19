// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_ALIB) || defined(HPP_ALIB_REPORT)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_ALIB_REPORT
#define HPP_ALIB_REPORT 1


namespace aworx {
namespace           lib {


// #################################################################################################
// forwards
// #################################################################################################
namespace threads { class ThreadLock; }
namespace strings { class TString;    }
namespace strings { class AString;    }
class ReportWriter;
class ConsoleReportWriter;


/** ************************************************************************************************
 * This class provides a simple facility to collect what is called a \e 'report'.
 * Reports are maintenance messages, mostly error and warning messages, but is not aiming to replace
 * any sort of error handling.
 * (In ALib itself, sending a \e 'report' usually precedes raising an error.)
 * Also, \e reports are not replacing any debug or release logging facility, which is not
 * part of ALib. Much more, logging libraries might provide a derived object of type
 * \ref aworx::lib::ReportWriter "ReportWriter" to plug into ALib report facility.
 * This way, the concepts of logging and reports get unified. (As a sample,
 * <em>ALox Logging Library </em> which builds on ALib does so.)
 *
 * While a process can create different objects of this class, usually, the default instance,
 * received by
 * \ref aworx::lib::Report::GetDefault "GetDefault".
 * is sufficient and all warnings and errors will be directed to this one. ALib itself directs
 * all internal reports to the default instance.
 *
 * This class uses a singleton of type
 * \ref aworx::lib::ReportWriter "ReportWriter" to actually write the reports. By default, an
 * object of type
 * \ref aworx::lib::ConsoleReportWriter "ConsoleReportWriter" is attached.
 *
 * The reporting method,
 * \ref aworx::lib::Report::DoReport "DoReport" will check the flags provided with
 * \ref aworx::lib::Report::PushHaltFlags "PushHaltFlags" for message types \c 0 (errors)
 * and \c 1 (warnings), and may invoke \e assert(). Such assertions are effective
 * only in the debug compilation of the library/executable. Custom \e 'ReportWriters' might
 * take action (e.g. for security reasons) and e.g. terminate the application also in
 * release compilations.
 *
 * To simplify things, a set of macros is defined which are pruned in release
 * versions of the compilation unit. These are:
 *
 * - #ALIB_REPORT
 * - #ALIB_ERROR
 * - #ALIB_WARNING
 * - #ALIB_ASSERT
 * - #ALIB_ASSERT_ERROR
 * - #ALIB_ASSERT_WARNING
 *
 * The use of the macros is recommended. For convenience, in debug compilations of the library/
 * executable, these macros provide the file name,line number and method name of the invocation
 * source, which can be used by more sophisticated versions of attached
 * \ref aworx::lib::ReportWriter "ReportWriter".
 **************************************************************************************************/
class Report
{
    // #############################################################################################
    // Inner classes
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * A report message.
         ******************************************************************************************/
        class Message
        {
            public:

            /**
             * The message type. \c 0 indicates \e 'severe' errors, \c 1 warnings.
             * Others are status messages and may be defined (interpreted) by custom
             * implementations of
             * \ref aworx::lib::ReportWriter "ReportWriter".
             */
            int                         Type;

            /** The message.  */
            const strings::TString&     Contents;

            /** The file name that reported.  */
            const strings::TString& File;

            /** The line number in the source file that reported.  */
            int                     Line;

            /** The function/method name that reported.  */
            const strings::TString& Func;

            /** Constructs a message.
             * @param type The message type.
             * @param msg  The message.
             * @param file Information about the scope of invocation.
             * @param line Information about the scope of invocation.
             * @param func Information about the scope of invocation.
             */
            Message( int type, const strings::TString& msg,
                     const strings::TString& file, int line, const strings::TString& func );
        };

    // #############################################################################################
    // protected fields
    // #############################################################################################
    protected:
        /** The default Report used internally by ALib and usually by processes that rely on ALib. */
        ALIB_API static Report*         defaultReport;

        /**
         * A stack of writers. The topmost one is the actual.
         * Can be set at runtime using methods #PushWriter and #PopWriter.
         */
        std::stack<ReportWriter*>       writers;


        /** This is a flag that avoids recursion. Recursion might occur when a more sophisticated
         * report writer sends a report (e.g. an ALIB Error or Warning). Recursive calls are
         * rejected without further notice.
         */
        bool                            recursionBlocker                                        = false;

        /** A Lock to protect against multihreaded calls. */
        threads::ThreadLock*            lock;

        /**
         * A stack of integers. The topmost value is used to decide, whether program execution is
         * halted on message of type 'error' (type \c 0, bit \c 0) or of type 'warning'
         * (type \c 1, bit \c 1).
         * Can be set at runtime using methods #PushHaltFlags and #PopHaltFlags.
         */
        std::stack<int>                 haltAfterReport;

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:


    // #############################################################################################
    // constructor/destructor
    // #############################################################################################
    public:
        ALIB_API     Report();
        ALIB_API    ~Report();

    // #############################################################################################
    // Interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Receives the default report object used by ALib and processes that rely on ALib.
         * @returns The default \b Report.
         ******************************************************************************************/
        static
        Report&  GetDefault()
        {
            if ( defaultReport == nullptr )
                defaultReport= new Report();
            return *defaultReport;
        }

        /** ****************************************************************************************
         * Reports the given message to the current
         * \ref aworx::lib::ReportWriter "ReportWriter" in place. The default \b ReportWriter
         * will print the message on the process console. Furthermore, in debug
         * execution the flags provided with #PushHaltFlags is checked.
         * If this is set for the type of message, the program halts or suspends into the debugger
         * (platform and language specific).
         *
         * If parameter \p type is '0', the report is considered a \e severe error, otherwise
         * a warning.
         * User defined implementations of class \e %ReportWriter may interpret this field
         * arbitrarily.
         *
         * @param type The report type.
         * @param msg  The report message.
         * @param file Information about the scope of invocation.
         * @param line Information about the scope of invocation.
         * @param func Information about the scope of invocation.
         ******************************************************************************************/
        ALIB_API
        void     DoReport( int type,  const lib::strings::TString& msg,
                           const lib::strings::TString& file, int line, const lib::strings::TString& func );

        /** ****************************************************************************************
         * Writes new values to the internal flags that decide if calls to #DoReport with
         * report type \e '0' (errors), respectively report type '>0' (warnings) cause
         * to halt program execution by calling <em>assert(false)</em>.
         * The previous values can be restored using #PopHaltFlags.
         * @param haltOnErrors      Specifies if halting on errors is wanted.
         * @param haltOnWarnings    Specifies if halting on warnings is wanted.
         ******************************************************************************************/
        ALIB_API
        void     PushHaltFlags( bool haltOnErrors, bool haltOnWarnings );

        /** ****************************************************************************************
         * Restores the previous values after an invocation to #PushHaltFlags.
         ******************************************************************************************/
        ALIB_API
        void     PopHaltFlags();

        /** ****************************************************************************************
         * Sets a new writer. The actual writer is implemented as a stack. It is important to
         * keep the right order when pushing and popping writers, as there lifetime is externally
         * managed. (In standard use-cases, only one, app-specific writer should be pushed anyhow).
         * To give a little assurance, method #PopWriter takes the same parameter as this method
         * does, to verify if if the one to be removed is really the topmost.
         * @param newWriter   The writer to use.
         ******************************************************************************************/
        ALIB_API
        void     PushWriter( ReportWriter* newWriter );

        /** ****************************************************************************************
         * Retrieves the actual report writer.
         *
         * \note This method should not be used to retrieve the writer and use it. It should be used
         *       only to test the installation.
         * @return The actual report writer in place.
         ******************************************************************************************/
        ALIB_API
        ReportWriter* PeekWriter();

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
        ALIB_API
        void     PopWriter( ReportWriter* checkWriter );
};// class Report


/** ************************************************************************************************
 * Interface that defines a writer for for %ALib \ref aworx::lib::Report "Report".
 * By default, a simple implementation is installed that just uses \c out and \c cerr.
 * Applications may implement their own ReportWriter.
 **************************************************************************************************/
class ReportWriter
{
    public:
        /** ****************************************************************************************
         * Virtual destructor
         ******************************************************************************************/
        virtual ~ReportWriter()                    {}

        /** ****************************************************************************************
         * Notify activation/deactivation
         * @param phase     Information if activated or deactivated.
         ******************************************************************************************/
        virtual void NotifyActivation  ( enums::Phase phase )      =0;

        /** ****************************************************************************************
         * Report a message. Pure virtual abstract interface method.
         * @param report     The report.
         ******************************************************************************************/
        virtual void Report  ( const Report::Message& report )    =0;
};

/** ************************************************************************************************
 * The simple, default \b %ReportWriter, just writing the message to the console.
 **************************************************************************************************/
class ConsoleReportWriter : public ReportWriter
{
    public:
        /** The singleton which is added in the constructor of \b Report. */
        ALIB_API
        static ConsoleReportWriter Singleton;

    protected:
        /** ********************************************************************************************
         * Protected constructor, only one Singleton might exist.
         **********************************************************************************************/
        ConsoleReportWriter(){}

    public:
        /** ****************************************************************************************
         * Notify activation/deactivation
         * @param phase     Information if activated or deactivated.
         ******************************************************************************************/
        ALIB_API
        virtual void NotifyActivation  ( enums::Phase phase );

        /** ********************************************************************************************
         * Just writes the prefix \"ALib Report (Error):\" (respectively \"ALib Report (Warning):\"
         * and the error message to the cout.
         * On Windows platform, if a debugger is present, the message is also written using
         * <em>OutputDebugStringA</em>.
         *
         * @param report    The report.
         **********************************************************************************************/
        ALIB_API
        virtual void Report  ( const Report::Message& report );

};

}} // namespace aworx::lib

#endif // HPP_ALIB_REPORT
