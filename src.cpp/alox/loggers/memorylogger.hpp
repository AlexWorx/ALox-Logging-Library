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
#ifndef HPP_ALOX_MEMORY_LOGGER
#define HPP_ALOX_MEMORY_LOGGER 1

// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALOX_CORE_TEXTLOGGER_PLAINTEXTLOGGER)
    #include "alox/core/textlogger/plaintextlogger.hpp"
#endif

namespace aworx { namespace lox { namespace loggers
{

/** ************************************************************************************************
 *  A logger that logs all messages to an in-memory buffer of type AString. The name of the \e Logger
 *  defaults to "MEMORY".
 **************************************************************************************************/
class MemoryLogger : public aworx::lox::core::textlogger::PlainTextLogger
{
    // #############################################################################################
    // public fields
    // #############################################################################################
    public:
        /**
         * The logging Buffer. This can be accessed publicly and hence used as preferred.
         * Especially, the whole log can easily be cleared using
         * \ref aworx::lib::strings::AString::Clear "AString::Clear".
         * In multi-threaded environments, \c Lox interfaces' mutex should be acquired
         * before accessing this buffer. The initial size of the buffer is 8kb.
         */
        AString                     MemoryLog;

        /**
         * If this field is set to \c true (which is the default), the effective length of the
         * messages when converted to wide character strings are taken into account.
         *
         * Switching this off increases the overall logging performance (especially when logging
         * into memory) significantly.
         */
        bool                        UseWCharLengthForTabAdjustments                          = true;


    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Creates a MemoryLogger with the given name.
         * @param name              (Optional) The name of the \e Logger. Defaults to "MEMORY".
         * @param pruneESCSequences (Optional) Sets the member \ref PruneESCSequences.
         *                          Defaults to \c true.
         * @param useWCharLengthForTabAdjustments (Optional) Sets the member
         *                          \ref UseWCharLengthForTabAdjustments.
         *                          Defaults to \c true.
         ******************************************************************************************/
        explicit        MemoryLogger( const String& name                    = nullptr,
                                      bool pruneESCSequences                = true,
                                      bool useWCharLengthForTabAdjustments  = true )
                        : PlainTextLogger( name, "MEMORY", false )
                        , MemoryLog      ( 8092 )
                        {
                            PruneESCSequences              = pruneESCSequences;
                            UseWCharLengthForTabAdjustments= useWCharLengthForTabAdjustments;
                        }


        /** ****************************************************************************************
         * Destructs a MemoryLogger
         ******************************************************************************************/
        virtual        ~MemoryLogger() {}

    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Start a new log line. Appends a new-line character sequence to previously logged lines.
         *
         * @param phase  Indicates the beginning or end of a log line.
         * @return Always returns true.
         ******************************************************************************************/
        virtual bool notifyLogOp(lib::lang::Phase phase)
        {
            // append new line if buffer has already lines stored
            if ( phase == lib::lang::Phase::Begin && MemoryLog.IsNotEmpty() )
                MemoryLog.NewLine();
            return true;
        }

        /** ****************************************************************************************
         * Write the given region of the given AString to the destination buffer.
         *
         * @param buffer   The string to write a portion of.
         * @param start    The start of the portion in \p buffer to write out.
         * @param length   The length of the portion in \p buffer to write out.
         * @return The number of characters written, -1 on error.
         ******************************************************************************************/
        virtual integer logSubstring( const AString& buffer, integer start, integer length )
        {
            MemoryLog._<false>( buffer, start, length );
            return UseWCharLengthForTabAdjustments
                ? lib::strings::CString::LengthWhenConvertedToWChar( buffer.Buffer() + start, length )
                : length;
        }

        /** ****************************************************************************************
         *  Empty implementation, not needed for this class
         ******************************************************************************************/
        virtual    void notifyMultiLineOp( lib::lang::Phase )     {}

}; // class MemoryLogger

}} // namespace lox::loggers

/** Type alias name in namespace #aworx. */
using     MemoryLogger=           aworx::lox::loggers::MemoryLogger;

}  // namespace aworx

#endif // HPP_ALOX_MEMORY_LOGGER

