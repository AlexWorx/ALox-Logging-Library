// #################################################################################################
//  aworx::lox::loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// include ALox main header first...
#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

// then, set include guard
#ifndef HPP_ALOX_TEXT_FILE_LOGGER
#define HPP_ALOX_TEXT_FILE_LOGGER 1


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
 * This is a very simple file logger for textual log outputs. The file name string provided
 * in the constructor is not verified. If write operations fail, this logger disables
 * itself by setting the inherited flag isDisabled to true.
 * The fileName may be changed by simply setting the public member #FileName and the flag
 * #IsDisabled may be set to false by the user without the need of any other interaction other
 * than acquiring the \c Lox that the logger is added to.
 **************************************************************************************************/
class TextFileLogger : public aworx::lox::core::textlogger::PlainTextLogger
{
    // #############################################################################################
    // Fields
    // #############################################################################################
        /** The path and fileName to the log file. */
        public:           aworx::AString           FileName;

        /** Used to write into a log file. */
        protected:        std::ofstream*           os                                     = nullptr;

        /** Flag to prevent file open/close operations when multi line text logging is performed. */
        protected:        bool                     currentlyInMultiLineOp                 = false;


    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Creates a TextFileLogger.
         * @param fileName    The filename (potentially including a path) of the output log file.
         * @param loggerName  The name of the logger. Defaults to "TEXTFILE".
         ******************************************************************************************/
        explicit            TextFileLogger( const aworx::String& fileName,
                                            const aworx::String& loggerName    =nullptr )
                            :  PlainTextLogger( loggerName, "TEXTFILE" )
        {
            FileName << fileName;
        }


        /** ****************************************************************************************
         * Destructs a TextFileLogger
         ******************************************************************************************/
        virtual            ~TextFileLogger()
        {
             ALIB_ASSERT_ERROR( os == nullptr, "ostream not deleted" )
        }

    // #############################################################################################
    // Protected methods
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Opens the file. If not successful, the logger will be disabled by setting field
         * #IsDisabled to \c true.
         ******************************************************************************************/
        ALIB_API
        void openFile();

        /** ****************************************************************************************
         * Closes the file. If not successful, the logger will be disabled by setting field
         * #IsDisabled to \c true.
         ******************************************************************************************/
        ALIB_API
        void closeFile();

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
         * @param phase  Indicates the beginning or end of a multi-line operation.
         ******************************************************************************************/
        ALIB_API
        virtual void notifyMultiLineOp (lib::enums::Phase phase );

}; // class TextFileLogger


}}} // namespace

#endif // HPP_ALOX_TEXT_FILE_LOGGER

