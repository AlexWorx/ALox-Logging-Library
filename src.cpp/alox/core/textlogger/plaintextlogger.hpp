// #################################################################################################
//  aworx::lox::core - ALox Logging Library
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
#ifndef HPP_ALOX_CORE_TEXTLOGGER_PLAINTEXTLOGGER
#define HPP_ALOX_CORE_TEXTLOGGER_PLAINTEXTLOGGER 1


// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALOX_CORE_TEXTLOGGER_TEXTLOGGER)
    #include "alox/core/textlogger/textlogger.hpp"
#endif


// #################################################################################################
// forwards
// #################################################################################################
namespace aworx { namespace lib { namespace strings { class Substring; } } }

namespace aworx {
namespace           lox {
namespace                   core{
namespace                           textlogger{

/** ************************************************************************************************
 * A text logger that either removes or ignores (just writes through) ALox ESC sequences.
 * Implements abstract method #doTextLog and introduces two new abstract methods
 * doLogSubstring.
 **************************************************************************************************/
class PlainTextLogger : public aworx::lox::core::textlogger::TextLogger
{
    // #############################################################################################
    // public fields
    // #############################################################################################
    public:
        /**
         * If this field is set to \c true (the default), all \ref aworx::lox::ESC "ESC" color and
         * style codes get removed when logging into this Logger. \c ESC::TAB is processed.
         *
         * It might be useful, to set this to false, e.g. in the case, the contents of the
         * Logger is (later) written into a different logger (e.g. as a multi line message)
         * which is capable of interpreting the escape sequences of class ESC.
         */
        bool                        PruneESCSequences                                        = true;

    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Creates a PlainTextLogger
         * @param name     The name of the logger. If empty, it defaults to the type name.
         * @param typeName The type of the logger.
         ******************************************************************************************/
        explicit        PlainTextLogger( const String& name, const String& typeName )
                        : TextLogger( name, typeName )
                        {}

        /** ****************************************************************************************
         * Destructs a MemoryLogger
         ******************************************************************************************/
        virtual        ~PlainTextLogger() {};

    // #############################################################################################
    // Abstract methods introduced
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Abstract method to be implemented by descendants. This method is called when a new
         * log message is started. It is called exactly once before a series of doLogPortion()
         * calls and exactly once after such series. If either the start or one of the calls
         * #doLogSubstring returns \c false, the invocation that would indicate the end of a log
         * message is omitted.
         *
         * Implementing this method allows the acquisition of system resources
         * (e.g. opening a file).
         *
         * @param phase  Indicates the beginning or end of a log line.
         * @return If \c false is returned, the log line is aborted without an invocation of
         *         \ref notifyLogOp "notifyLogOp(Phase::End)".
         ******************************************************************************************/
        virtual bool notifyLogOp(lib::enums::Phase phase)                                       = 0;

        /** ****************************************************************************************
         * Abstract method to be implemented by descendants. Has to write the given region of
         * the given AString to the destination.
         * Has to return the number of characters written, which might be different from the
         * substrings' length, e.g. in case of character set conversions. If an error occurs, \c -1
         * can be returned to indicate that the current log should be aborted. In this case, no
         * invocation of \ref notifyLogOp "notifyLogOp(Phase::End)" will be performed.
         *
         * @param buffer   The string to write a portion of.
         * @param start    The start of the portion in \p buffer to write out.
         * @param length   The length of the portion in \p buffer to write out.
         * @return The number of characters written, -1 on error.
         ******************************************************************************************/
        virtual int doLogSubstring( const AString& buffer, int start, int length )             = 0;


    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * The implementation of the abstract method of parent class TextLogger.
         * Loops over the log text, removes or ignores ESC sequences (all but ESC.TAB) and invokes
         * abstract methods of descendants as follows:
         * - \ref notifyLogOp "notifyLogOp(true)"
         * -   #doLogSubstring()
         * -   ...
         * - \ref notifyLogOp "notifyLogOp(Phase::End)"
         *
         * @param domain        The log domain name.
         * @param level         The log level. This has been checked to be active already on this
         *                      stage and is provided to be able to be logged out only.
         * @param msg           The log message.
         * @param indent        the indentation in the output. Defaults to 0.
         * @param caller        Once compiler generated and passed forward to here.
         * @param lineNumber    The line number of a multi-line message, starting with 0. For
         *                      single line messages this is -1.
         ******************************************************************************************/
        ALOX_API
        virtual void doTextLog( const TString&            domain,     Log::Level     level,
                                      AString&            msg,        int            indent,
                                      core::CallerInfo*   caller,     int            lineNumber);
}; // class PlainTextLogger

}}}} // namespace

#endif // HPP_ALOX_CORE_TEXTLOGGER_PLAINTEXTLOGGER
