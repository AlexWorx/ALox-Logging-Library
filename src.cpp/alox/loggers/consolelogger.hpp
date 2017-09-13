// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
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


namespace aworx { namespace lox
{
/** ************************************************************************************************
 * This is the C++ namespace for the implementation of <em>logger classes</em> that are provided
 * by default with <b>%ALox Logging Library</b>.
 *
 * Developed by A-Worx GmbH and published under Boost Software License.
 **************************************************************************************************/
namespace loggers{

/** ************************************************************************************************
 * A logger that logs all messages to the standard output <em>cout</em>.
 * The name of the \e Logger defaults to "CONSOLE".
 *
 * \b %ALox text logger escape sequences (see class \ref aworx::lox::ESC "ESC")
 * are removed and ignored.
 **************************************************************************************************/
class ConsoleLogger : public aworx::lox::core::textlogger::PlainTextLogger
{
    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Creates a ConsoleLogger.
         * @param name (Optional) The name of the \e Logger, defaults to "CONSOLE".
         ******************************************************************************************/
        explicit            ConsoleLogger( const String& name= nullptr )
                            :  PlainTextLogger( name, "CONSOLE", true )
        {
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
        virtual bool notifyLogOp( lib::lang::Phase phase );

        /** ****************************************************************************************
         * Writes the given region of the given AString to the console.
         *
         * @param buffer   The string to write a portion of.
         * @param start    The start of the portion in \p buffer to write out.
         * @param length   The length of the portion in \p buffer to write out.
         * @return The number of characters written, -1 on error.
         ******************************************************************************************/
        ALIB_API
        virtual integer logSubstring( const AString& buffer, integer start, integer length );


        /** ****************************************************************************************
         *  Empty implementation, not needed for this class
         ******************************************************************************************/
        virtual void notifyMultiLineOp( lib::lang::Phase )    {}

}; // class ConsoleLogger


}} // namespace lox::loggers

/** Type alias name in namespace #aworx. */
using     ConsoleLogger=           aworx::lox::loggers::ConsoleLogger;

}  // namespace aworx

#endif // HPP_ALOX_CONSOLE_LOGGER

