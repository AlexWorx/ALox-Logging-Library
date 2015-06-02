// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// include ALox main header first...
#if !defined (HPP_AWORX_ALOX_ALOX)
    #include "alox.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_ALOX_CONSOLE_LOGGER
#define HPP_AWORX_ALOX_CONSOLE_LOGGER 1


// -------------------------------------------------------------------------------------------------
// --- includes
// -------------------------------------------------------------------------------------------------
#if !defined (HPP_AWORX_ALOX_TEXTLOGGER)
    #include "core/textlogger.hpp"
#endif


namespace aworx {
namespace       lox {
/** ************************************************************************************************
 *  This is the C++ namespace for the implementation of <em>logger classes</em> that are provided
 *  by default with <em>%ALox Logging Library</em>.<p>
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace           loggers{



/** ************************************************************************************************
 *  A logger that logs all messages to the standard ouput <em>cout</em>.
 *  If compiled within Visual Studio IDE (see \ref AWORX_VSTUDIO_ON), when debugging, also logs to
 *  the Visual Studio ouput window (using <em>System.Diagnostics.Debug.WriteLine()</em>).<br>
 *  The name of the logger defaults to "CONSOLE".
 *
 *  The constructor sets the level of the root domain, and as such the level of all 'unknown'
 *  domains that inherit from root domain to 'All'. This is because this class represents a logger
 *  that logs into the developer's IDE, and hence just wants to fetch all log domains that the
 *  app and its library uses - unless explicitly set differently in the bootstrap code.  By default,
 *  root domains of loggers have domain level 'Off'.
 **************************************************************************************************/
class ConsoleLogger : public aworx::lox::core::TextLogger
{
    // #############################################################################################
    // Output flags
    // #############################################################################################
    public:
        /// Enables logging to the std::cout stream.
        bool        EnableCout                        = true;

    #if defined(AWORX_VSTUDIO)
        ///  Enables logging to the debug window of Visual Studio.
        ///  Available only if AWORX_VSTUDIO is set. Logs to the VStudio output window, when
        ///  Application is debugged.
        ///  Defaults to true in ALOX_DEBUG configuration, to false in ALOX_REL_LOG configuration.
        bool        EnableVSDebugConsole
                                                #if defined(AWXU_DEBUG)
                                                        = true;
                                                #else
                                                        = false;
                                                #endif
    #endif


    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Creates a ConsoleLogger.
         * @param name    (Optional) The name of the logger, defaults to "CONSOLE"
         ******************************************************************************************/
        ALOX_API
        explicit        ConsoleLogger( const char* name= "CONSOLE" );

        /** ****************************************************************************************
         * Destructs a ConsoleLogger
         ******************************************************************************************/
        ALOX_API
        virtual        ~ConsoleLogger() {};

    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  The implementation of the abstract method of parent class TextLogger. Logs messages to the
         *  application console and/or the VStudio output window.
         *
         * @param domain      The log domain name.
         * @param level       The log level. This has been checked to be active already on this
         *                    stage and is provided to be able to be logged out only.
         * @param msg         The log message.
         * @param indent      the indentation in the output. Defaults to 0.
         * @param caller      Once compiler generated and passed forward to here.
         * @param lineNumber  The line number of a multi-line message, starting with 0. For
         *                    single line messages this is -1.
         ******************************************************************************************/
        ALOX_API
        virtual void doTextLog(  const aworx::util::AString&    domain,
                                 aworx::lox::Log::Level         level,
                                 aworx::util::AString&          msg,
                                 int                            indent,
                                 aworx::lox::core::CallerInfo*  caller,
                                 int                            lineNumber);

        /** ****************************************************************************************
         *  Empty implementation, not needed for this class
         ******************************************************************************************/
        ALOX_API
        virtual void notifyMultiLineOp (bool )    {  }

}; // class ConsoleLogger

}}} // namespace

#endif // HPP_AWORX_ALOX_CONSOLE_LOGGER

