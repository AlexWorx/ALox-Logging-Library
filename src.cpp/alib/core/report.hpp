// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_AWORX_LIB_ALIB) || defined(HPP_AWORX_LIB_REPORT)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_LIB_REPORT
#define HPP_AWORX_LIB_REPORT 1


namespace aworx {
namespace           lib {


// #################################################################################################
// forwards
// #################################################################################################
namespace threads { class ThreadLockNR;     }
namespace strings { class ASTerminatable;   }
namespace strings { class ASAlloc;   }
class ReportWriter;
class ConsoleReportWriter;


/** ************************************************************************************************
 * This class provides a simple facility to collect what is called a \e 'report'.
 * Reports are maintenance messages, similar to error messages, but is not aiming to replace
 * and error handling.
 * (Sending a \e 'report' usually precedes raising an error.)
 * Also, \e 'reports' are not replacing any debug or release logging facility, which is not
 * part of ALib. Much more, logging libraries (like \e ALox Logging Library, which
 * builds on ALib, does) might provide a derived object of type
 * \ref aworx::lib::ReportWriter "ReportWriter" to plug into ALib report facility.
 * This way, the concepts of logging and reports get unified.
 *
 * While a process can create different objects of this class, usually, the default instance,
 * received by
 * \ref aworx::lib::Report::GetDefault "GetDefault".
 * is sufficient and all warnings and errors will be directed to this one. ALib itself directs
 * all messages to the default instance.
 *
 * This class uses a singleton of type
 * \ref aworx::lib::ReportWriter "ReportWriter" to actually write the reports. By default, an
 * object of type
 * \ref aworx::lib::ConsoleReportWriter "ConsoleReportWriter" is attached.
 *
 * The reporting method,
 * \ref aworx::lib::Report::DoReport "DoReport" will check the public flag
 * \ref aworx::lib::Report.HaltOnError "HaltOnError" respectively
 * \ref aworx::lib::Report.HaltOnWarning "HaltOnWarning",
 * which if \c true, causes the method to invoke \e assert(). Such assertions are effective
 * only in the debug compilation of the library/executable. Custom \e 'ReportWriters' might
 * take action (e.g. for security reasons) and e.g. terminate the application also in
 * release compilations.
 *
 * To simplify things, a set of macros is defined which are pruned in release
 * versions of the compilation unit. These are:
 *
 * - #ALIB_ERROR
 * - #ALIB_WARNING
 * - #ALIB_ASSERT
 * - #ALIB_ASSERT_ERROR
 * - #ALIB_ASSERT_WARNING
 *
 * The use of the macros is recommended. For convenience, in debug compilations of the library/
 * executable, these macros provide the file name,line number and method name of the invocation
 * source, which can be used by more sophisticated \ref aworx::lib::ReportWriter "ReportWriter".
 **************************************************************************************************/
class Report
{
    // #############################################################################################
    // Inner classes
    // #############################################################################################
    public:

        /** A report message.  */
        class Message
        {
            public:

            #if defined(ALIB_DEBUG)
                /** The file name that reported.  */
                const strings::ASTerminatable&   File;

                /** The line number in the source file that reported.  */
                int                              Line;

                /** The function/method name that reported.  */
                const strings::ASTerminatable&   Func;
            #endif

            /** The message type. '0' indicates \e 'severe' errors. Others are warnings and may be
             *  defined (interpreted) by custom implementations of
             *  \ref aworx::lib::ReportWriter "ReportWriter".  */
            int                                  Type;

            /** The message.  */
            const strings::ASTerminatable&       Contents;

            /** Constructs a message.
             * @param type The message type.
             * @param msg  The message.
             */
            Message( ALIB_DBG_SRC_INFO_PARAMS_DECL   int type, const strings::ASTerminatable& msg );
        };

    // #############################################################################################
    // protected fields
    // #############################################################################################
    protected:
        /**  The ReportWriter.  */
        ReportWriter*           reportWriter;

        /** The default Report used internally by ALib and usually by processes that rely on ALib. */
        ALIB_API static Report  defaultReport;

        /** This is a flag that avoids recursion. Recursion might occur when a more sophisticated
         * report writer sends a report (e.g. an ALIB Error or Warning). Recursive calls are
         * rejected without further notice.
         */
        bool                    recursionBlocker                                            = false;

        /** A Lock to protect against multihreaded calls. */
        threads::ThreadLockNR*  lock;

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Flag, which if set to \c true, causes calls to #DoReport with report type \e '0'
         * to halt program execution by calling <em>assert(false)</em>.
         * Can be set at runtime by just overwriting the value.
         ******************************************************************************************/
        bool                    HaltOnError                                                   =true;

        /** ****************************************************************************************
         * Flag, which if set to \c true, causes calls to #DoReport with report type not equal to
         * \e '0' to halt program execution by calling <em>assert(false)</em>.
         * Can be set at runtime by just overwriting the value.
         ******************************************************************************************/
        bool                    HaltOnWarning                                                =false;

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
        Report&  GetDefault()           { return defaultReport; }

        /** ****************************************************************************************
         * Replaces the current ReportWriter by the one provided.
         * If nullptr, a \b %ReportWriter of type
         * \ref aworx::lib::ConsoleReportWriter "ConsoleReportWriter" will be created and attached.
         *
         * @param newReportWriter The \b %ReportWriter to set.
         * @param deletePrevious  Determines if the previous ReportWriter should be deleted.
         * @return The former ReportWriter.
         ******************************************************************************************/
        ALIB_API
        ReportWriter* ReplaceReportWriter( ReportWriter* newReportWriter, bool deletePrevious );

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
         ******************************************************************************************/
        ALIB_API
        void     DoReport( ALIB_DBG_SRC_INFO_PARAMS_DECL
                           int                            type,
                           const strings::ASTerminatable& msg  );
};// class Report


/** ************************************************************************************************
 * Interface for %ALIB \ref aworx::lib::ReportWriter "ReportWriter".
 * The \b %ReportWriter is invoked on internal %ALIB errors
 * caused by illegal arguments or other wrong %ALIB use. By default, a simple implementation is
 * installed that just uses cout/cerr to print the error and warning messages to
 * the application's standard output.
 * Applications may implement their own ReportWriter.
 *
 * \see Class \ref aworx::lib::Report "Report".
 **************************************************************************************************/
class ReportWriter
{
    public:
        /** ****************************************************************************************
         * Virtual destructor
         ******************************************************************************************/
        virtual ~ReportWriter()                    {}

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
    /** ********************************************************************************************
     * Just writes the prefix \"ALib Report (Error):\" (respectively \"ALib Report (Warning):\"
     * and the error message to the cout.
     * On Windows platform, if a debugger is present, the message is also written using
     * <em>OutputDebugStringA</em>.
     *
     * @param report    The report.
     **********************************************************************************************/
    virtual void Report  ( const Report::Message& report );
};

}} // namespace aworx::lib

#endif // HPP_AWORX_LIB_REPORT
