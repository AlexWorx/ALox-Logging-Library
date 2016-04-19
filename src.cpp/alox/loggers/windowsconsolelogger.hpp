// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include ALox main header first...
#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

// then, set include guard
#ifndef HPP_ALOX_WINDOWS_CONSOLE_LOGGER
#define HPP_ALOX_WINDOWS_CONSOLE_LOGGER 1

#if defined( _WIN32 )

// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALOX_CORE_TEXTLOGGER_TEXTLOGGER)
    #include "alox/core/textlogger/textlogger.hpp"
#endif


namespace aworx {
namespace       lox {
namespace           loggers{

/** ************************************************************************************************
 *  A logger that logs all messages to the standard output <em>cout</em>.
 *  The name of the \e Logger defaults to "WINDOWS_CONSOLE".
 *
 *  ALox text logger escape sequences (see class \ref aworx::lox::ESC "ESC")
 *  are translated to Windows API calls (<em>SetConsoleTextAttribute</em>) which manipulates
 *  colors the text output.
 *  There is not 100% match between windows console capabilities and the definitions in
 *  \ref aworx::lox::ESC "ESC". Especially, ESC style attributes are ignored.
 *
 *  Foreground and background colors are set to be either light/dark or dark/light. This improves
 *  the readability of log output a lot. However, the right setting for this is dependent on
 *  the color scheme of final output device (window). To manipulate the right setting, see field
 *  #IsBackgroundLight and also configuration variable
 *  [ALOX_CONSOLE_HAS_LIGHT_BACKGROUND](../group__GrpALoxConfigVars.html).
 *
 *  In the constructor, a default format string and some other definitions in member
 *  \ref MetaInfo get set to include ESC sequences. Of-course, these publicly accessible
 *  format attributes can be customized after creation.
 *
 *  \note This class can not enable the output console (which receives ALox
 *  log data) to support the windows API call <em>SetConsoleTextAttribute</em>.
 *  The opposite is right: this class should be used only if the output console supports such calls.
 **************************************************************************************************/
class WindowsConsoleLogger : public aworx::lox::core::textlogger::TextLogger
{
    // #############################################################################################
    // Internals
    // #############################################################################################
    protected:
        /**
         * The attributes that were set on the windows console at the time this object was created.
         */
        WORD        originalConsoleAttributes;

    // #############################################################################################
    // public fields
    // #############################################################################################
    public:
        /**
         * If \c false, foreground colors will be light colors and background colors dark. If
         * \c true, the opposite is chosen.
         *
         * This flag can be modified from outside any time.
         *
         * The "right" setup will be automatically determined in the constructor of this class
         * by determining the color scheme of the windows console.
         * It will be set to \c true, if the standard console of the application is displaying
         * a light color foreground on a dark color background and vice versa.
         *
         * The configuration variable [ALOX_CONSOLE_HAS_LIGHT_BACKGROUND](../group__GrpALoxConfigVars.html)
         * is evaluated within the constructor of this class, to allow to modifying this flag at
         * runtime.
         */
        bool            IsBackgroundLight;


        /**
         * The code page that is used for the console log output. For possible values refer to
         * [Microsoft documentation] (https://msdn.microsoft.com/EN-US/library/windows/desktop/dd317756%28v=vs.85%29.aspx)
         *
         * This defaults to 65001, which is UTF-8 unicode encoding.
         *
         * This flag can be modified from outside any time. If the value is not equal to 0,
         * the code page of the output console is set prior to each log output.
         *
         * The configuration variable [ALOX_CODE_PAGE](../group__GrpALoxConfigVars.html)
         * is evaluated within the constructor of this class, to allow to modifying the codepage at
         * runtime.
         */

        UINT            CodePage                                                            =65001;

        /** Color of a log line with \e Verbosity 'Error'.*/
        WORD            MsgColorError;

        /** Color of a log line with \e Verbosity 'Warning'.*/
        WORD            MsgColorWarning;

        /** Color of a log line with \e Verbosity 'Info'.*/
        WORD            MsgColorInfo;

        /** Color of a log line with \e Verbosity 'Verbose'.*/
        WORD            MsgColorVerbose;

    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Creates a WindowsConsoleLogger.
         * @param name  (Optional) The name of the \e Logger, defaults to "WINDOWS_CONSOLE".
         ******************************************************************************************/
        ALOX_API
        explicit            WindowsConsoleLogger( const String& name= nullptr  );

        /** ****************************************************************************************
         * Destructs a WindowsConsoleLogger
         ******************************************************************************************/
        ALOX_API
        virtual            ~WindowsConsoleLogger();


    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  The implementation of the abstract method of parent class TextLogger.
         *  Logs messages to the basic output stream 'cout' and sets windows console colors
         *  by invoking corresponding Windows API methods..
         *
         * @param domain      The <em>Log Domain</em>.
         * @param verbosity   The verbosity. This has been checked to be active already on this
         *                    stage and is provided to be able to be logged out only.
         * @param msg         The log message.
         * @param scope       Information about the scope of the <em>Log Statement</em>..
         * @param lineNumber  The line number of a multi-line message, starting with 0. For
         *                    single line messages this is -1.
         ******************************************************************************************/
        ALOX_API
        virtual void logText(  core::Domain&     domain,
                               Verbosity         verbosity,
                               AString&          msg,
                               core::ScopeInfo&  scope,
                               int               lineNumber);

        /** ****************************************************************************************
         *  Empty implementation, not needed for this class
         ******************************************************************************************/
        ALOX_API
        virtual void notifyMultiLineOp (lib::enums::Phase )    {  }

}; // class WindowsConsoleLogger

}} // namespace lox::loggers

/** Type alias name in namespace #aworx. */
using     WindowsConsoleLogger=     aworx::lox::loggers::WindowsConsoleLogger;

}  // namespace aworx

#endif // defined( _WIN32 )

#endif // HPP_ALOX_WINDOWS_CONSOLE_LOGGER

