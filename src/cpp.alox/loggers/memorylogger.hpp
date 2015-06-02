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
#ifndef HPP_AWORX_ALOX_MEMORY_LOGGER
#define HPP_AWORX_ALOX_MEMORY_LOGGER 1

// -------------------------------------------------------------------------------------------------
// --- includes
// -------------------------------------------------------------------------------------------------
#if !defined (HPP_AWORX_ALOX_TEXTLOGGER)
    #include "core/textlogger.hpp"
#endif


namespace aworx {
namespace       lox {
namespace           loggers{


/** ************************************************************************************************
 *  A logger that logs all messages to a in-memory buffer of type AString. The name of the logger
 *  defaults to "MEMORY".
 **************************************************************************************************/
class MemoryLogger : public aworx::lox::core::TextLogger
{
    // #############################################################################################
    // public fields
    // #############################################################################################
    public:

        /**
         *  The logging Buffer. This can be accessed publicly and hence used as you prefer. Especially,
         *  the whole log can easily be cleared using the AString.Clear(). However, in
         *  multithreaded environments, locking to the Log interface's mutex should be performed before
         *  accessing this Buffer. The initial size of the buffer is 8KB.
         */
        aworx::util::AString            Buffer;


    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *     Creates a MemoryLogger with the given name.
         * @param name    (Optional) The name of the logger. Defaults to "MEMORY".
         ******************************************************************************************/
        ALOX_API
        explicit        MemoryLogger( const char* name= "MEMORY" );

        /** ****************************************************************************************
         * Destructs a MemoryLogger
         ******************************************************************************************/
        ALOX_API
        virtual        ~MemoryLogger() {};

    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  The implementation of the abstract method of parent class TextLogger. Logs messages to the
         *  Buffer field.
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
        void doTextLog( const aworx::util::AString&            domain,     Log::Level     level,
                              aworx::util::AString&            msg,        int            indent,
                              aworx::lox::core::CallerInfo*    caller,     int            lineNumber);


        /** ****************************************************************************************
         *  Empty implementation, not needed for this class
         ******************************************************************************************/
        virtual    void notifyMultiLineOp (bool )    {  }

}; // class MemoryLogger

}}} // namespace

#endif // HPP_AWORX_ALOX_CONSOLE_LOGGER

