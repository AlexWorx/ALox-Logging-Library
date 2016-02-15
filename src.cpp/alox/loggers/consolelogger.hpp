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
#ifndef HPP_ALOX_CONSOLE_LOGGER
#define HPP_ALOX_CONSOLE_LOGGER 1


// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALOX_CORE_TEXTLOGGER_PLAINTEXTLOGGER)
    #include "alox/core/textlogger/plaintextlogger.hpp"
#endif


namespace aworx {
namespace       lox {
/** ************************************************************************************************
 *  This is the C++ namespace for the implementation of <em>logger classes</em> that are provided
 *  by default with <em>%ALox Logging Library</em>.
 *
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace           loggers{

/** ************************************************************************************************
 *  A logger that logs all messages to the standard output <em>cout</em>.
 *  The name of the logger defaults to "PLAIN_CONSOLE".
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
 *  \note For the ease of use, class \ref aworx::lox::Log "Log" implements a method
 *  \ref aworx::lox::Log::AddDebugLogger "Log::AddDebugLogger"
 *  that tries to create the right Logger type for standard debug logging (potentially this one),
 *  depending on the platform, IDE and optional configuration settings.
 **************************************************************************************************/
class ConsoleLogger : public aworx::lox::core::textlogger::PlainTextLogger
{
    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Creates a ConsoleLogger.
         * @param name (Optional) The name of the logger, defaults to "CONSOLE".
         ******************************************************************************************/
        explicit            ConsoleLogger( const String& name= nullptr )
                            :  PlainTextLogger( name, "CONSOLE" )
        {
            // set default domain level to all: As an app console logger/IDE logger we want to fetch all we can
            RootDomain.SetLevel( Log::DomainLevel::All, lib::enums::Propagation::None );
        }


        /** ****************************************************************************************
         * Destructs a ConsoleLogger
         ******************************************************************************************/
        virtual            ~ConsoleLogger() {}

    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Starts/ends log line. Appends a new-line character sequence to previously logged lines.
         *
         * @param phase  Indicates the beginning or end of a log line.
         * @return Always returns true.
         ******************************************************************************************/
        ALIB_API
        virtual bool notifyLogOp( lib::enums::Phase phase );

        /** ****************************************************************************************
         * Writes the given region of the given AString to the console.
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
        virtual void notifyMultiLineOp( lib::enums::Phase )    {}

}; // class ConsoleLogger


}} // namespace lox::loggers

/** Type alias name in namespace #aworx. */
using     ConsoleLogger=           aworx::lox::loggers::ConsoleLogger;

}  // namespace aworx

#endif // HPP_ALOX_CONSOLE_LOGGER

