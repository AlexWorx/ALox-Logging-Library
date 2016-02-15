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
#ifndef HPP_ALOX_VSTUDIO_LOGGER
#define HPP_ALOX_VSTUDIO_LOGGER 1

#if defined(ALIB_VSTUDIO) && defined(ALIB_DEBUG)


// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALOX_CORE_TEXTLOGGER_PLAINTEXTLOGGER)
    #include "alox/core/textlogger/plaintextlogger.hpp"
#endif


namespace aworx {
namespace       lox {
namespace           loggers{

/** ************************************************************************************************
 *  A logger that logs to the Visual Studio output pane using <em>OutputDebugString()</em>.
 *  The name of the logger defaults to "VSTUDIO_CONSOLE".
 *
 *  ALox text logger escape sequences (see class \ref aworx::lox::ESC "ESC")
 *  are removed and ignored.
 *
 *  While by default, the
 *  \ref aworx::lox::Log::DomainLevel "DomainLevel"
 *  of root domains of loggers are set to 'Off', the constructor of this class sets this value
 *  to 'All'. This way, all log invocations on 'unknown' domains (those that have not been
 *  registered and explicitly set) are fully enabled by default.
 *  This is done because this class typically represents a logger that used for debug logging,
 *  e.g. logging into the developer's IDE. Such loggers should detect all messages of any log domain
 *  that the application and its library uses - unless those are explicitly set differently in
 *  the bootstrap code of the application.
 *
 *  \note For the ease of use, class
 *  \ref aworx::lox::Log "Log" implements a method
 *  \ref aworx::lox::Log::AddDebugLogger "Log::AddDebugLogger"
 *  that tries to create the right Logger type for standard debug logging.
 *  If a Visual Studio debug session is detected, this logger is added. If in addition, a windows
 *  console application is detected, then a second logger of type WindowsConsoleLogger is added.
 **************************************************************************************************/
class VStudioLogger : public aworx::lox::core::textlogger::PlainTextLogger
{
    // #############################################################################################
    // Internal members
    // #############################################################################################
    protected:
        /** A wide character buffer for the conversion of the debug message to uni-code. Conversion
         * is made by invoking
         * \ref aworx::lib::strings::AString::ToWString "AString::ToWString".
         */
        wchar_t*                wCharBuffer                                                =nullptr;

        /** Current size of uni-code conversion buffer. The buffer's size is increased when needed,
         *  but never decreased.
         */
        int                     wCharBufferSize                                            =0;


    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Creates a VStudioLogger.
         * @param name   (Optional) The name of the logger, defaults to "VSTUDIO_CONSOLE".
         ******************************************************************************************/
        ALOX_API
        explicit            VStudioLogger( const String& name= nullptr );

        /** ****************************************************************************************
         * Destructs a VStudioLogger
         ******************************************************************************************/
        ALOX_API
        virtual            ~VStudioLogger();

    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Start a new log line. Appends a new-line character sequence to previously logged lines.
         *
         * @param phase  Indicates the beginning or end of a log operation.
         * @return Always returns true.
         ******************************************************************************************/
        ALIB_API
        virtual bool notifyLogOp(lib::enums::Phase phase);

        /** ****************************************************************************************
         * Write the given region of the given AString to the destination buffer.
         *
         * @param buffer   The string to write a portion of.
         * @param start    The start of the portion in \p buffer to write out.
         * @param length   The length of the portion in \p buffer to write out.
         * @return The number of characters written, -1 on error.
         ******************************************************************************************/
        ALIB_API
        virtual int doLogSubstring( const AString& buffer, int start, int length );


        /** ****************************************************************************************
         *  Empty implementation, not needed for this class
         ******************************************************************************************/
        ALOX_API
        virtual void notifyMultiLineOp ( lib::enums::Phase )    {  }


}; // class VStudioLogger


}} // namespace lox::loggers

/** Type alias name in namespace #aworx. */
using     VStudioLogger=           aworx::lox::loggers::VStudioLogger;

}  // namespace aworx


#endif //defined(ALIB_VSTUDIO) &&  defined(ALIB_DEBUG)

#endif // HPP_ALOX_VSTUDIO_LOGGER

