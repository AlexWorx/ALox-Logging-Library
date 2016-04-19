// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include ALox main header first...
#if !defined (HPP_ALOX)
    #error "lox.hpp must not be included manually. Include alox.hpp instead."
#endif

// then, set include guard
#ifndef HPP_ALOX_LOG
#define HPP_ALOX_LOG 1

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif


namespace aworx {
namespace       lox {


// forwards
class Lox;
namespace  core   {
                     class Logger;
                     namespace  textlogger  {class TextLogger; }
                  }


/** ************************************************************************************************
 * Holds static objects used for standard debug logging and provides an interface to
 * create such objects. If compiler symbol #ALOX_DBG_LOG_OFF is set, this class will be empty.
 *
 * \note:
 *   In C# and Java, this class is the interface class for debug logging which gets pruned,
 *   and mimics the the functionality of class \ref aworx::lox::Lox "Lox".
 *   In C++, there is no need to double functionality of \b Lox here.
 **************************************************************************************************/
class Log
{
    #if defined(ALOX_DBG_LOG)

    // #############################################################################################
    // Public fields
    // #############################################################################################

    public:
        /**  The debug logger created by AddDebugLogger. */
        ALOX_API static core::textlogger::TextLogger*   DebugLogger;

        /**  An (additional) IDE specific logger, that might be created by AddDebugLogger. */
        ALOX_API static core::textlogger::TextLogger*   IDELogger;

        /**  The ALib ReportWriter. This will be created and registered in method
         *   \ref aworx::lox::Log::AddDebugLogger "Log::AddDebugLogger" and removed and deleted in
         *   \ref aworx::lox::Log::RemoveDebugLogger "Log::RemoveDebugLogger" in the case that
         * the original ALib ConsoleReportWriter is in place.
         */
        static ALoxReportWriter*                        DebugReportWriter;

    // #############################################################################################
    // Interface
    // #############################################################################################
        public:

        /** ****************************************************************************************
         * This method creates an adequate/default debug logger.
         * It is used by macro \ref Log_AddDebugLogger also automatically invoked
         * when debug logging is used without the explicit creation and registration of
         * any other logger.
         *
         * Of-course, alternatively to using this method (resp. the macro), a suitable (set of)
         * debug logger(s) can be created manually. Also, before or after using this method
         * additional debug loggers may be created.
         *
         * In the current version of ALox (future changes are likely), this method does:
         * - use
         *   \ref aworx::lox::Lox::CreateConsoleLogger "Lox::CreateConsoleLogger"
         *   to create the best compatible console logger for the
         *   running platform
         * - this logger will be added to the debug Lox object with specifiying
         *   \c Verbosity::Error for internal domains.
         * - If under windows, a Visual Studio debug session is running, adds a
         *   \ref aworx::lox::loggers::VStudioLogger "VStudioLogger"
         *   in addition to the standard console logger. This can be suppressed using
         *   configuration variable [ALOX_NO_IDE_LOGGER](../group__GrpALoxConfigVars.html).
         *
         * The name of the \e Logger created is \c "DEBUG_LOGGER". It will be registered with
         * the standard \b %Lox used for debug-logging, by setting \e Verbosities
         * - Verbosity::Verbose for the root domain <c> '/'</c> and
         * - Verbosity::Warning for internal domains.
         *
         * An optionally created second, IDE-specific \e Logger will be named \c "IDE_LOGGER"
         * and will be registered with the standard \b %Lox used for debug-logging with the same
         * \e Verbosities as \c "DEBUG_LOGGER" is.
         *
         * Finally, in the case that the original ALib ConsoleReportWriter is still in place,
         * \ref aworx::lib::Report::PushWriter "Report.PushWriter" is invoked to provide a
         * ReportWriter of type
         * \ref aworx::lox::ALoxReportWriter "ALoxReportWriter".
         *
         * @param lox  The lox to add the debug logger(s) to.
         ******************************************************************************************/
        ALOX_API static void      AddDebugLogger( Lox* lox );

        /** ****************************************************************************************
         *  Removes the \e Logger(s) and which was (were) created by \ref AddDebugLogger.
         *  This method also invokes
         *  \ref aworx::lib::Report::PopWriter "Report::Pop"
         *  to install a default \ref aworx::lib::ReportWriter "ReportWriter" for ALib.
         *
         *  @param lox The lox to remove the debug logger(s) from.
         ******************************************************************************************/
        ALOX_API static void      RemoveDebugLogger( Lox* lox );

    #endif // ALOX_DBG_LOG

}; // LOG


} // namespace lox

/** Type alias name in namespace #aworx. */
using     Log=           aworx::lox::Log;

}  // namespace aworx

#endif // HPP_ALOX_LOG
