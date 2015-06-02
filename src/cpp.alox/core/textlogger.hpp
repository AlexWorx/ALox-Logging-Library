// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// include ALox main header first...
#if !defined (HPP_AWORX_ALOX_ALOX)
    #include "alox.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_ALOX_TEXTLOGGER
#define HPP_AWORX_ALOX_TEXTLOGGER 1


// -------------------------------------------------------------------------------------------------
// --- includes
// -------------------------------------------------------------------------------------------------
#if !defined (HPP_AWORX_ALOX_LOGGER)
    #include "core/logger.hpp"
#endif


namespace aworx {
namespace       lox {
namespace           core{


/** ************************************************************************************************
 *  This class is a sort of plug-in for the TextLogger class which converts a given Object
 *  into its textual representation. An internal AString singleton is used as a string buffer
 *  and returned.
 *
 *  This class might be extended to be able to handle custom objects within text loggers.
 *  This default implementation, handles objects of type *String*, *AString* and *StringBuilder*,
 *  For null values a predefined string is returned.
 **************************************************************************************************/
class TextLoggerObjectConverter
{
    public:
        /// Used to convert null values to string representation. </summary>
        aworx::util::AString32       FmtNullObject                            ="<null, type=%>";

        /// Used to convert null values to string representation. </summary>
        aworx::util::AString32       FmtUnknownObject                         ="<unknown, type=%>";

    protected:
        ///  Buffer singleton to store the string representation of Objects. </summary>
        aworx::util::AString         buffer;

    public:
        /** ****************************************************************************************
         * Constructs an object of this class.
         ******************************************************************************************/
                    TextLoggerObjectConverter();
        /** ****************************************************************************************
         * Destructs an object of this class.
         ******************************************************************************************/
        virtual    ~TextLoggerObjectConverter() {};

        /** ****************************************************************************************
         * The conversion method. </summary>
         * @param o         The object to convert. </param>
         * @param typeInfo  The type of the object.
         * @return The filled AString singleton #buffer or, in the case that the given object was
         * of type AString already, just the object itself! </returns>
         ******************************************************************************************/
        virtual aworx::util::AString& ConvertObject( const void* o, int typeInfo );
};

/** ************************************************************************************************
 *
 * This class is a sort of plug-in for the TextLogger class. Its purpose is to assemble the meta
 * information of each log line (things like timestamps, thread information, level and domain, etc.).
 *
 * To manipulate the meta information log output, three options exist:
 * - by just changing the #Format string (at runtime).
 * - by creating a derived class that introduces a new version of method #processVariable() to handle
 *   one or more format variable differently or to introduce new variables.
 * - by creating a derived class that introduces a new version of method #WriteMetaInfo() to
 *   completely control the meta information output.
 *
 **************************************************************************************************/
class TextLoggerLineFormatter
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:

        /**
         *
         *  The line format specifies the (automated) log output that is prepended to each log line before
         *  the log message itself.
         *
         *  The string supports replacement variables that begin with a % sign
         *  - %CF: The caller's source file name
         *  - %CL: The line number in the caller's source file
         *  - %CM: The caller's method name
         *  - %D:  The date the log call was invoked
         *  - %TD: Time of day the log call was invoked
         *  - %TE: Time elapsed since the Logger was created or it's timer was reset
         *  - %TI: Time elapsed since the last log call
         *  - %t:  Thread name and/or ID
         *  - %L:  The log level
         *  - %O:  Log domain
         *  - %#:  The log call counter (like a line counter, but counting multi lines as one)
         *  - %An: An auto-adjusted tabulator. This grows whenever it needs, but never shrinks. The
         *         optional integer number n specifies how much extra space is added when tab is adjusted.
         *         Setting this to a higher value avoids too many adjustments at the beginning of a log session.
         *  - %N:  The name of the logger. This might be useful if multiple loggers write to the same
         *           output stream (e.g. Console).
         */
        //public AString  Format= new AString( "%CF(%CL):%CM()%A3[%DD] [%TD] [%TE +%TI] [%t] %L [%O] <%#>: ");
        util::AString       Format            =
                                                #if defined(ALOX_DBG_LOG_CI) || defined(ALOX_REL_LOG_CI)
                                                    "%CF(%CL):%CM()%A5[%TE +%TI] [%t] %L [%O]: ";
                                                #else
                                                    "[%TE +%TI] [%t] %L [%O]: ";
                                                #endif
        /** ****************************************************************************************
         *  To shorten the log output the given prefix might be cut from the source file path.
         *  If this AStrings allocation size is zero (or reset to zero at runtime), it is tried to
         *  detect this path automatically once. (Note: in C++, setting the allocation size of an
         *  AString to 0, can be used to indicate a null-string).<p>
         *  However, in various debug sessions (e.g. remote debugging) this might fail.
         *  Hence, this parameter can be set 'manually' to the right prefix that is to be consumed.
         *  In this case, whenever the project is compiled on a different machine setup (with
         *  different project path), this field has to be changed. If it is not changed, there is no
         *  other problem than that the path is not shortened and the log output might get a little
         *  wide.
         *
         *  If the output of the full path is intended, the filed can be set to empty string(\"\").
         ******************************************************************************************/
         aworx::util::AString               ConsumableSourcePathPrefix;


        /** ****************************************************************************************
         *  A list of values for auto tab positions. For each %A variable in LineFormat, a corresponding
         *  array field is created on the fly. If the format string get's changed and different (new) auto
         *  values should be used, then this field should be nulled after setting the new format string.
         *  The other way round, it is also possible to set minimum values for the tabs and
         *  hence avoid the columns growing during the lifetime of the Logger.
         ******************************************************************************************/
        std::vector<int>    AutoTabs;

        /** The character(s) used for indentation. */
        const char*         IndentString                    = "  ";

        /// The output for the log level "Error".
        const char*         LogLevelError                   = "[ERR]";

        /// The output for the log level "Warning".
        const char*         LogLevelWarning                 = "[WRN]";

        /// The output for the log level "Info".
        const char*         LogLevelInfo                    = "     ";

        /// The output for the log level "Verbose".
        const char*         LogLevelVerbose                 = "[***]";

        /// Format string for the output of the log date. For more information, see
        ///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat()
        const char*         DateFormat                      = "yyyy-MM-dd";

        /// Format string for the output of the time of day. For more information, see
        ///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat()
        const char*         TimeOfDayFormat                 = "HH:mm:ss";

        /// The word "Days" the out put of time elapsed (if longer than a day).
        const char*         TimeElapsedDays                 = " Days ";

        /// Minimum time difference to log in nanoseconds.  Below that #TimeDiffNone is written.
        long                TimeDiffMinimum                 = 1000L;

        /// Output for time difference if below reasonable (measurable) minimum defined in #TimeDiffMinimum.
        const char*         TimeDiffNone                    = "---   ";

        /// Entity nanoseconds for time difference outputs below 1000 microsecond.
        const char*         TimeDiffNanos                   = " ns";

        /// Entity microseconds for time difference outputs below 1000 microseconds.
        const char*         TimeDiffMicros                  = " µs";//" \xB5s"; //" µs";

        /// Entity milliseconds for time difference outputs below 1000 milliseconds.
        const char*         TimeDiffMillis                  = " ms";

        /// Format for time difference outputs between 10s and 99.9s.
        const char*         TimeDiffSecs                    = " s";

        /// Format for time difference outputs between 100s and 60 min.
        const char*         TimeDiffMins                    = " m";

        /// Format for time difference outputs between 1h and 24h.
        const char*         TimeDiffHours                   = " h";

        /// Format for time difference outputs of more than a day.
        const char*         TimeDiffDays                    = " days";

        /// Replacement string if no source info is available.
        const char*         NoSourceFileInfo                = "no_source_info";

        /// Replacement string if no source info is available.
        const char*         NoMethodInfo                    = "no_method_info";


        /// Prefix for the domain.
        int                 LogNumberMinDigits               = 3;

        /// The maximum length of a thread name logged so far. This 'auto growing'
        /// field assures to keep output in nice column format.
        int                 AutoGrowThreadNameLength         = 0;

        /// The maximum length of a domain name logged so far. This 'auto growing'
        /// field assures to keep output in nice column format.
        int                 AutoGrowDomainNameLength         = 0;



    // #############################################################################################
    // Internal fields
    // #############################################################################################
    protected:
        ///  The actual auto tab number detected in the format string.
        int                     autoTabNo;

        ///  A singleton calendar time object shared between different format variables during one invocation.
        util::TicksCalendarTime callerDateTime;


    // #############################################################################################
    // Constructor/Destructor
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Constructs a TextLoggerLineFormatter.
         ******************************************************************************************/
        TextLoggerLineFormatter()                   {}

        /** ****************************************************************************************
         * Virtual destructor of TextLoggerLineFormatter.
         ******************************************************************************************/
        virtual ~TextLoggerLineFormatter()          {}

    // #############################################################################################
    // Public interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  Parses the #Format string and logs meta information into the log buffer.
         * @param logger    The logger that we are embedded in.
         * @param buffer    The buffer to write meta information into.
         * @param domain    The log domain name.
         * @param level     The log level. This has been checked to be active already on this
         *                  stage and is provided to be able to be logged out only.
         * @param indent    The desired indentation of the log call.
         * @param caller    Once compiler generated and passed forward to here.
         ******************************************************************************************/
        ALOX_API
        virtual void WriteMetaInfo( Logger&                 logger,
                                    util::AString&          buffer,
                                    const util::AString&    domain,
                                    Log::Level              level,
                                    int                     indent,
                                    CallerInfo*             caller      );

    // #############################################################################################
    // Internals
    // #############################################################################################
    protected:

        /** ****************************************************************************************
         *  Processes the next command found in the format string, by writing formatted information
         * into the given buffer.
         * @param logger            The logger that we are embedded in.
         * @param domain            The log domain name.
         * @param level             The log level. This has been checked to be active already on this
         *                          stage and is provided to be able to be logged out only.
         * @param caller            Once compiler generated and passed forward to here.
         * @param buffer            The buffer to write meta information into.
         * @param formatStringIdx   The index of the command in the format string.
         * @return The index as received but potentially increased by the number of characters read by
         * the variable as parameters.
         ******************************************************************************************/
        ALOX_API
        virtual int processVariable( Logger&               logger,
                                     const util::AString&  domain,
                                     Log::Level            level,
                                     CallerInfo*           caller,
                                     util::AString&        buffer,
                                     int                   formatStringIdx );

        /** ****************************************************************************************
         *  Helper function that logs a time given difference into the given buffer in a human readable
         *  format. Works from nanoseconds seconds to days.
         *
         * @param buffer       The buffer to write the time difference representation into.
         * @param diffNanos    The time difference to write in nanoseconds.
         ******************************************************************************************/
        ALOX_API
        virtual void writeTimeDiff( util::AString& buffer, int_fast64_t diffNanos );
}; // class



/** ************************************************************************************************
 *  This class is a still abstract implementation of class Logger which is used as the super class
 *  for all textual Logger implementations within ALox, e.g. ConsoleLogger.
 *
 *  The class uses two helper classes. One to convert the log message object into a string representation
 *  and a second to generate the textual representation of the meta information of a log call.
 *  These helpers can be extended and replaced to modify the behavior of TextLogger.
 *
 *  The final log message is then passed to the abstract method #doTextLog(). Hence, custom Logger classes
 *  that inherited from this class instead of directly from class #Logger, need to implement #doTextLog()
 *  instead of implementing #doLog()!
 *
 *  Class TextLogger supports multi line log outputs. Such multi line log outputs can be configured to
 *  be logged in different ways. See #MultiLineMsgMode for more information.
 **************************************************************************************************/
class TextLogger : public Logger
{
    // #############################################################################################
    // Internal fields
    // #############################################################################################
    protected:
        ///  The internal log Buffer.
        util::AString               logBuf;

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
         * A helper object to convert log objects into textual representations. To extend TextLogger, this
         * object can be replaced by custom implementations.
         */
        TextLoggerObjectConverter* ObjectConverter;

        /**
         * A helper object to format log objects into textual representations. This class incorporates
         * a format string that defines the meta information in the log output. Furthermore, to extend
         * TextLogger, this object can be replaced by custom implementations of it.
         */
        TextLoggerLineFormatter*    LineFormatter;


        /**
         * A list of pairs of strings. Within each log message, the first string of a pair is
         *  searched and replaced by the second string. Very simple, but useful in some cases.
         */
        std::vector<std::string>    Replacements;

        /**
         * Determines if multi line messages should be split into different log lines. Possible values are:
         *
         * - 0: No line split is performed, delimiters can be replaced by readable delimiters (depending on
         *      setting of #MultiLineDelimiter and # MultiLineDelimiterRepl).
         *
         * - 1: Each log line contains all meta information
         *
         * - 2: Starting with second log line, meta information is replaced by blanks  (default)
         *
         * - 3: The headline #FmtMultiLineMsgHeadline is logged and all lines of the multi line text are logged
         *      at position zero (without further meta information)
         *
         * - 4: Just the multi line text is logged, starting at column zero (no meta information is logged)
         */
        int                         MultiLineMsgMode                    = 2;

        /**
         * This is the string interpreted as line delimiter within log messages. If null, CR, LF or CRLF
         * are used. Important: Set to empty string, to stop any multi line processing of TextLogger, even the replacements.
         * */
        util::AString               MultiLineDelimiter;

        /**
         * This is the readable (!) separator string, for logging out multi line messages into a
         * single line (#MultiLineMsgMode==0).
         * */
        util::AString               MultiLineDelimiterRepl              = "\\r";


        /// Headline for multi line messages (depending on #MultiLineMsgMode)  .
        const char*                 FmtMultiLineMsgHeadline             = "ALox: Multi line message follows: ";

        /**
         *  Prefix for multi line messages. This is also used if multi line messages logging is switched off
         *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
         */
        const char*                 FmtMultiLinePrefix                  = ">> ";

        /**
         *  Postfix for multi line messages. This is also used if multi line messages logging is switched off
         *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
         */
        const char*                 FmtMultiLinePostfix                  = "";

    // #############################################################################################
    // protected Constructor/destructor
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Constructs a TextLogger.
         * @param name The name of the logger.
         ******************************************************************************************/
        ALOX_API explicit TextLogger( const char* name );

        /** ****************************************************************************************
         *  Destructs a TextLogger.
         ******************************************************************************************/
        ALOX_API virtual ~TextLogger();

    // #############################################################################################
    // Abstract methods introduced
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  The abstract function that logs a text message to be implemented by descendants
         * @param domain     The log domain name.
         * @param level      The log level. This has been checked to be active already on this
         *                   stage and is provided to be able to be logged out only.
         * @param msg        The log message.
         * @param indent     the indentation in the output. Defaults to 0.
         * @param caller     Once compiler generated and passed forward to here.
         * @param lineNumber The line number of a multi-line message, starting with 0. For single line
         *                   messages this is -1.
         ******************************************************************************************/
        ALOX_API
        virtual void doTextLog(  const aworx::util::AString&    domain,
                                 aworx::lox::Log::Level         level,
                                 aworx::util::AString&          msg,
                                 int                            indent,
                                 aworx::lox::core::CallerInfo*  caller,
                                 int                            lineNumber)    =0;

        /** ****************************************************************************************
         *  Abstract method to be implemented by descendants. This message is called only when multi-line
         *  messages are logged. It is called exactly once before a series of doLog() calls of a multi-line
         *  message and exactly once after such series.<br>
         *  This is useful if the writing of text includes the acquisition of system resources (e.g. opening
         *  a file).
         *
         * @param isStart    If true, indicates the begin of a multi-line message, the end otherwise.
         ******************************************************************************************/
        ALOX_API
        virtual void notifyMultiLineOp (bool isStart)     =0;


    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  Implementation of Logger.doLog(). Creates all the textual information that is logged in a line
         *  before the message itself.
         *
         * @param domain    The log domain name.
         * @param level     The log level. This has been checked to be active already on this
         *                  stage and is provided to be able to be logged out only.
         * @param msgObject The object to log.
         * @param typeInfo  Type information on the object to log.
         * @param indent    the indentation in the output. Defaults to 0.
         * @param caller    Once compiler generated and passed forward to here.
         ******************************************************************************************/
        ALOX_API
        virtual void doLog( const util::AString&   domain,     Log::Level      level,
                            const void*            msgObject,  int             typeInfo,
                            int                    indent,     CallerInfo*     caller  );

}; // class TextLogger

}}} // namespace

#endif // HPP_AWORX_ALOX_TEXTLOGGER
