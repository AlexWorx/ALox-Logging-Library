// #################################################################################################
//  aworx::lox::core - ALox Logging Library
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
#ifndef HPP_ALOX_CORE_TEXTLOGGER_TEXTLOGGER
#define HPP_ALOX_CORE_TEXTLOGGER_TEXTLOGGER 1


// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALOX_CORE_LOGGER)
    #include "alox/core/logger.hpp"
#endif


// #################################################################################################
// forwards
// #################################################################################################
namespace aworx { namespace lib { namespace strings { class ASSubstring; } } }

namespace aworx {
namespace           lox {
namespace                   core{
/** ************************************************************************************************
 * This namespaces defines class \b TextLogger and its helpers.
 **************************************************************************************************/
namespace                           textlogger{



/** ************************************************************************************************
 *  This class is a sort of plug-in for the TextLogger class which converts a given Object
 *  into its textual representation. An internal AString singleton is used as a string buffer
 *  and returned.
 *
 *  This class might be extended to be able to handle custom objects within text loggers.
 *  This default implementation, only handles objects of type
 *  \ref aworx::lib::strings::ASTerminatable "aworx::TString".
 *  For nullptr and nulled \b %TStrings a configurable string message is returned.
 *
 *  While other ALox implementations, like ALox for C# or ALox for Java use the 'runtime type
 *  information' feature of their underlying programming language to identify any object type,
 *  this is not possible in standard C++. Therefore, all logging objects in ALox for C++ have
 *  to be accompanied with a type information. This is implemented as a simple integer and
 *  the value \b '0' is reserved for \b TStrings.
 *
 *  All other types are extension types, which are not part of core ALox and user specific types.
 *
 *  It is recommended to use positive values for user specific types. Negative IDs
 *  are reserved to 'official' ALox extensions.
 **************************************************************************************************/
class ObjectConverter
{
    public:
        /// Used to convert null values to string representation.
        String64        FmtNullObject     ="ALox message object is nullptr, type=%.";

        /// Used to return an error message in the case the object could not be converted (type unknown)
        String64        FmtUnknownObject  ="ALox message object unknown, type=%.";

    public:
        /** ****************************************************************************************
         * Constructs an object of this class.
         ******************************************************************************************/
         ALOX_API       ObjectConverter();
        /** ****************************************************************************************
         * Destructs an object of this class.
         ******************************************************************************************/
        virtual        ~ObjectConverter() {};

        /** ****************************************************************************************
         * The conversion method.
         * @param o         The object to convert.
         * @param typeInfo  The type of the object.
         * @param result    An AString that takes the result.
         * @return True, if the object was converted successfully, false otherwise. Note:
         * Even if false was returned, the error text of template field \ref FmtUnknownObject
         * is appended, including the typeInfo value.
         ******************************************************************************************/
        ALOX_API
        virtual bool    ConvertObject( const void* o, int typeInfo, AString& result );
};

/** ************************************************************************************************
 * Auto sizes are used for tabulator positions and field sizes that expand automatically when they
 * are exceeded. This way, any next line will have that new, expanded tabs and field sizes set
 * leading to a nicely formatted, but still flexible, minimized width of output.
 *
 * To preserve the information across <em>sessions</em>, this class provides methods to transform
 * it's information from and to string representations which can be stored in configuration files.
 *
 * All values are doubly stored: once for the session and once for the last imported values.
 * Those values that were imported are used for getting the actual size. However, those that are
 * stored for the session are the ones that would have been created if there was no import done.
 * This leads to the fact that the session values may be smaller than the actual (imported) ones.
 * This mechanism, in combination with the fact that on importing it can be decided if the session
 * is newly started or not, allows the values to shrink again over different sessions.
 **************************************************************************************************/
class AutoSizes
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /** The current sizes                                */
        std::vector<int>                values;

        /** The sizes measured in this session. These are the ones that will be received in method
         *  #Export                                         */
        std::vector<int>                sessionValues;

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**  The actual index requested by #Next. This is reset to 0 with every invocation of
         *   #Start. */
        int                             ActualIndex;

    // #############################################################################################
    // Interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Resets the whole object. All values get deleted.
         ******************************************************************************************/
        void        Reset ()                      {   values.clear(); sessionValues.clear();       }

        /** ****************************************************************************************
         * Initializes a new query sequence, which is a series of invocations of method #Next.
         ******************************************************************************************/
        void        Start ()                      {   ActualIndex=   0; }

        /** ****************************************************************************************
         * Returns the next auto value stored, respectively, if the given requested size is higher,
         * then stores and returns the requested size. The given extra growth is added to the
         * requested size if the currently stored value is unequal to 0. In other words, the extra
         * size is added only with the second growth and each subsequent one.
         *
         * @param requestedSize   The minimum size that is requested.
         * @param extraGrowth     Added to the new size if the requested size is greater than
         *                        the stored size and if the stored size does not equal 0.
         *
         * @return The (new) size of the auto field.
         ******************************************************************************************/
        ALOX_API
        int         Next  ( int requestedSize, int extraGrowth );

        /** ****************************************************************************************
         * Imports values from the given
         * \ref aworx::lib::strings::AS "AS" by parsing it. The numbers in the string have
         * to be separated by ' ' characters (space).
         *
         * @param source    The \b %AS that is parsed for the numbers
         * @param session   If \c CurrentData::Clear, which is the default, the current values
         *                  are taken from the last session stored and the sessions data is set to 0.
         *                  If \c CurrentData::Keep, both, current values and
         *                  session values are taken from the string.
         ******************************************************************************************/
        ALOX_API
        void        Import( const String& source, lib::enums::CurrentData session= lib::enums::CurrentData::Clear );

        /** ****************************************************************************************
         *  Exports the current session values by converting the stored numbers to a string
         *  representation and appending them to the given
         *  \ref aworx::lib::strings::ASAlloc "AString" object.
         *  The numbers in the string will be separated by ' ' characters (space).
         *
         * @param target       The \b %AString to receive the our values
         ******************************************************************************************/
        ALOX_API
        void        Export( AString& target );
};


/** ************************************************************************************************
 * This class is a sort of plug-in for the TextLogger class. Its purpose is to assemble the meta
 * information of each log line (things like timestamps, thread information, level and domain, etc.).
 *
 * To manipulate the meta information log output, three options exist:
 * - by just changing the #Format string (at runtime).
 * - by creating a derived class that introduces a new version of method #processVariable() to handle
 *   one or more format variable differently or to introduce new variables.
 * - by creating a derived class that introduces a new version of method #Write() to
 *   completely control the meta information output.
 **************************************************************************************************/
class MetaInfo
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:

        /**
         * The line format specifies the (automated) log output that is prepended to each log line before
         * the log message itself. This format string can be changed after the creation
         * of a \ref TextLogger.
         *
         * The string supports replacement variables that begin with a % sign
         * - %CF: The caller's source file name including path
         * - %Cf: The caller's source file name (excluding path)
         * - %CL: The line number in the caller's source file
         * - %CM: The caller's method name
         * - %D:  The date the log call was invoked
         * - %TD: Time of day the log call was invoked
         * - %TE: Time elapsed since the Logger was created or it's timer was reset
         * - %TI: Time elapsed since the last log call
         * - %t:  Thread name and/or ID
         * - %L:  The log level
         * - %O:  Log domain
         * - %#:  The log call counter (like a line counter, but counting multi lines as one)
         * - %An: An auto-adjusted tabulator. This grows whenever it needs, but never shrinks. The
         *        optional integer number n specifies how much extra space is added when tab is adjusted.
         *        Setting this to a higher value avoids too many adjustments at the beginning of a log session.
         * - %N:  The name of the logger. This might be useful if multiple loggers write to the same
         *        output stream (e.g. Console).
         *
         * A sample that would show just all info in the output is be:
         * \code "%CF(%CL):%CM()%A5[%D] [%TD] [%TE +%TI] [%t] [%t] %L [%O] <%#>: " \endcode
         *
         * Defaults to
         * \code "%CF(%CL):%A5%CM() %A5[%TE +%TI] [%t] %L [%O] %A1(%#): " \endcode
         *
         * If debug logging as well as release logging has caller information disabled
         * (see \ref ALOX_DBG_LOG_CI_OFF and \ref ALOX_REL_LOG_CI_ON ), then it defaults to:
         * \code "[%TE +%TI] [%t] %L [%O]: " \endcode
         */

        #if defined(ALOX_DBG_LOG_CI) || defined(ALOX_REL_LOG_CI)
            AString  Format {"%CF(%CL):%A5%CM() %A5[%TE +%TI] [%t] %L [%O] %A1(%#): "};
        #else
            AString  Format {"[%TE +%TI] [%t] %L [%O] %A1(%#): "};
        #endif

        /**
         *  If \c true, an one-time warning (using
         *  \ref aworx::lib::Report::DoReport "Report::DoReport")
         *  will be issued if the format string is illegal.
         *
         *  \note This field can not be accessed directly (For technical reasons, it is
         *        differently declared than stated here in the source documentation).<br>
         *        To change the field use macros
         *        - \ref ALIB_WARN_ONCE_PER_INSTANCE_ENABLE(myinstance, FormatWarning) and
         *        - \ref ALIB_WARN_ONCE_PER_INSTANCE_DISABLE(myinstance, FormatWarning)
         *
         *        where \p myinstance is a reference to the object in question).
         */
        #if defined(IS_DOXYGEN_PARSER)
            bool                              FormatWarning= true;
        #else
            ALIB_WARN_ONCE_PER_INSTANCE_DECL( FormatWarning, true );
        #endif


        /**
         *  To shorten the log output the given prefix might be cut from the source file path.
         *  If this
         *  \ref aworx::lib::strings::ASAlloc "AString" is \e nulled, it is tried to
         *  detect this path automatically once.<p>
         *  However, in various debug sessions (e.g. remote debugging) this might fail.
         *  Hence, this parameter can be set 'manually' to the right prefix that is to be consumed.
         *  In this case, whenever the project is compiled on a different machine setup (with
         *  different project path), this field has to be changed. If it is not changed, there is no
         *  other problem than that the path is not shortened and the log output might get a little
         *  wide.
         *
         *  If the output of the full path is intended, the filed can be set to empty string(\"\").
         */
        AString  ConsumableSourcePathPrefix;


        /// The output for the log level "Error".
        String16     LogLevelError            ="[ERR]";

        /// The output for the log level "Warning".
        String16     LogLevelWarning          ="[WRN]";

        /// The output for the log level "Info".
        String16     LogLevelInfo             ="     ";

        /// The output for the log level "Verbose".
        String16     LogLevelVerbose          ="[***]";

        /// Format string for the output of the log date. For more information, see
        ///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat()
        String16     DateFormat               ="yyyy-MM-dd";

        /// Format string for the output of the time of day. For more information, see
        ///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat()
        String16     TimeOfDayFormat          ="HH:mm:ss";

        /// The word "Days" the out put of time elapsed (if longer than a day).
        String16     TimeElapsedDays          =" Days ";

        /// Minimum time difference to log in nanoseconds.  Below that #TimeDiffNone is written.
        long         TimeDiffMinimum          =1000L;

        /// Output for time difference if below reasonable (measurable) minimum defined in #TimeDiffMinimum.
        String16     TimeDiffNone             ="---   ";

        /// Entity nanoseconds for time difference outputs below 1000 microsecond.
        String16     TimeDiffNanos            =" ns";

        /// Entity microseconds for time difference outputs below 1000 microseconds.
        String16     TimeDiffMicros           =" \xC2\xB5s"; // UTF-8 encoding of the greek 'm' letter;

        /// Entity milliseconds for time difference outputs below 1000 milliseconds.
        String16     TimeDiffMillis           =" ms";

        /// Format for time difference outputs between 10s and 99.9s.
        String16     TimeDiffSecs             =" s";

        /// Format for time difference outputs between 100s and 60 min.
        String16     TimeDiffMins             =" m";

        /// Format for time difference outputs between 1h and 24h.
        String16     TimeDiffHours            =" h";

        /// Format for time difference outputs of more than a day.
        String16     TimeDiffDays             =" days";

        /// Replacement string if no source info is available.
        String32     NoSourceFileInfo         ="---";

        /// Replacement string if no source info is available.
        String32     NoMethodInfo             ="---";

        /// The minimum digits to write for the log number (if used in format string).
        int          LogNumberMinDigits       = 3;

    // #############################################################################################
    // Internal fields
    // #############################################################################################
    protected:

        ///  A singleton calendar time object shared between different format variables during one invocation.
        lib::time::TicksCalendarTime callerDateTime;

    // #############################################################################################
    // Constructor/Destructor
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Virtual destructor of MetaInfo.
         ******************************************************************************************/
        virtual ~MetaInfo()          {}

    // #############################################################################################
    // Public interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  Parses the #Format string and logs meta information into the log buffer. For each
         *  variable found, method #processVariable is invoked. Hence, to add new variables,
         *  the latter method can be overwritten by descendants. Overwriting this method is
         *  recommended for formatter classes that do not rely on format strings.
         * @param logger    The logger that we are embedded in.
         * @param buffer    The buffer to write meta information into.
         * @param domain    The log domain name.
         * @param level     The log level. This has been checked to be active already on this
         *                  stage and is provided to be able to be logged out only.
         * @param caller    Once compiler generated and passed forward to here.
         *
         * @return The number of tab sequences that were written (by adding ESC::TAB to the buffer).
         ******************************************************************************************/
        ALOX_API
        virtual int Write( TextLogger&        logger,
                           AString&           buffer,
                           const TString&     domain,
                           Log::Level         level,
                           CallerInfo*        caller      );

    // #############################################################################################
    // Internals
    // #############################################################################################
    protected:

        /** ****************************************************************************************
         *  Processes the next command found in the format string, by writing formatted information
         *  into the given buffer.
         *  The given
         *  \ref aworx::lib::strings::ASSubstring "ASSubstring" holds the next command.
         *  When method the returns, the command is cut from the front.
         *
         * @param logger       The logger that we are embedded in.
         * @param domain       The log domain name.
         * @param level        The log level. This has been checked to be active already on this
         *                     stage and is provided to be able to be logged out only.
         * @param caller       Once compiler generated and passed forward to here.
         * @param buffer       The buffer to write meta information into.
         * @param variable     The variable to read (may have more characters appended)
         *
         * @return The number of tab sequences that were written (by adding ESC::TAB to the buffer).
         ******************************************************************************************/
        ALOX_API
        virtual int processVariable( TextLogger&      logger,
                                     const TString&   domain,
                                     Log::Level       level,
                                     CallerInfo*      caller,
                                     AString&         buffer,
                                     Substring&       variable      );

        /** ****************************************************************************************
         *  Helper function that logs a time given difference into the given buffer in a human readable
         *  format. Works from nanoseconds seconds to days.
         *
         * @param buffer       The buffer to write the time difference representation into.
         * @param diffNanos    The time difference to write in nanoseconds.
         ******************************************************************************************/
        ALOX_API
        virtual void writeTimeDiff( AString& buffer, int_fast64_t diffNanos );
}; // class



/** ************************************************************************************************
 *  This class is a still abstract implementation of class Logger which is used as the super class
 *  for all textual Logger implementations within ALox, e.g. ConsoleLogger.
 *
 *  The class uses a helper class to generate the textual representation of the meta information
 *  of a log call.
 *  This helper can be extended and replaced in #MetaInfo to modify the behavior of TextLogger.
 *
 *  The final log message is then passed to the abstract method #doTextLog.
 *  Hence, custom Logger classes that inherited from this class instead of directly from class
 *  #Logger, need to implement #doTextLog instead of implementing #doLog!
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
        AString         logBuf;

        ///  A buffer for the textmessage
        AString         msgBuf;

        /**
         * A list of pairs of strings. Within each log message, the first string of a pair is
         *  searched and replaced by the second string. Very simple, but useful in some cases.
         */
        std::vector<AString>    replacements;

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
         * A helper object to convert log objects into textual representations. To extend TextLogger, this
         * object can be replaced by custom implementations.
         */
        textlogger::ObjectConverter*    ObjectConverter;

        /**
         * A helper object to format log objects into textual representations. This class incorporates
         * a format string that defines the meta information in the log output. Furthermore, to extend
         * TextLogger, this object can be replaced by custom implementations of it.
         */
        textlogger::MetaInfo*           MetaInfo;

        /**
         *  Holds a list of values for auto tab positions and field sizes.
         *  For each requested value, a corresponding array field is created on the fly.
         *  If the format string get's changed and different (new) auto values should be used, then
         *  this field should be reset after setting the new format string.
         *  The other way round, it is also possible to preset set minimum values for tabs and field
         *  sizes and hence avoid the columns growing during the lifetime of the Logger.
         */
        textlogger::AutoSizes           AutoSizes;

        /**
         * Determines if multi line messages should be split into different log lines. Possible
         * values are:
         *
         * - 0: No line split is performed, delimiters can be replaced by readable delimiters
         *   (depending on setting of #MultiLineDelimiter and # MultiLineDelimiterRepl).
         *
         * - 1: Each log line contains all meta information
         *
         * - 2: Starting with second log line, meta information is replaced by blanks  (default)
         *
         * - 3: The headline #FmtMultiLineMsgHeadline is logged and all lines of the multi line
         *      text are logged at position zero (without further meta information)
         *
         * - 4: Just the multi line text is logged, starting at column zero (no meta information
         *   is logged)
         *
         * \note In modes 3 and 4, no ESC::EOMETA is included at the beginning of the message.
         *       Loggers that need such info, have to implement method #notifyMultiLineOp.
         */
        int                             MultiLineMsgMode                                         =2;

        /**
         * This is the string interpreted as line delimiter within log messages. If \e nulled
         * (the default), CR, LF or CRLF are used. Important: Set to empty string, to stop
         * any multi line processing of TextLogger, even the replacements.
         */
        AString                         MultiLineDelimiter;

        /**
         * This is the readable (!) separator string, for logging out multi line messages into a
         * single line (#MultiLineMsgMode==0).
         * Defaults to "\\r".
         */
        String16                        MultiLineDelimiterRepl                               ="\\r";

        /**
         * Headline for multi line messages (depending on #MultiLineMsgMode)  .
         * Defaults to "ALox: Multi line message follows: "
         */
        String256                       FmtMultiLineMsgHeadline="ALox: Multi line message follows: ";

        /**
         * Prefix for multi line messages. This is also used if multi line messages logging is
         * switched off (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes
         * place.
         * Defaults to ">> ".
         */
        String16                        FmtMultiLinePrefix                                   =">> ";

        /**
         *  Postfix for multi line messages. This is also used if multi line messages logging is
         *  switched off (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter
         *  takes place.
         * Defaults to "".
         */
        String16                        FmtMultiLinePostfix                                     ="";

        /**
         * The characters  used for indentation.
         * Defaults to "  " (two spaces).
         */
        String16                        FmtIndentString                                       ="  ";

    // #############################################################################################
    // protected Constructor/ public destructor
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Constructs a TextLogger.
         * @param name      The name of the logger.
         * @param typeName  The type of the logger.
         ******************************************************************************************/
        ALOX_API explicit TextLogger( const String& name, const String& typeName );

        /** ****************************************************************************************
         *  Destructs a TextLogger.
         ******************************************************************************************/
    public:
        ALOX_API virtual ~TextLogger();

    // #############################################################################################
    // Abstract methods introduced
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  This abstract method introduced by this class "replaces" the the abstract method #doLog
         *  of parent class Logger which this class implements. In other words, descendants of this
         *  class need to overwrite this method instead of #doLog. This class %TextLogger is
         *  responsible for generating meta information, doing text replacements, handle multi-line
         *  messages, etc. and provides the textual representation of the whole log contents
         *  to descendants using this method.
         *
         * @param domain     The log domain name.
         * @param level      The log level. This has been checked to be active already on this
         *                   stage and is provided to be able to be logged out only.
         * @param msg        The log message.
         * @param indent     the indentation in the output. Defaults to 0.
         * @param caller     Once compiler generated and passed forward to here.
         * @param lineNumber The line number of a multi-line message, starting with 0.
         *                   For single line messages this is -1.
         ******************************************************************************************/
        virtual void doTextLog(  const TString&     domain,
                                 Log::Level         level,
                                 AString&           msg,
                                 int                indent,
                                 core::CallerInfo*  caller,
                                 int                lineNumber)    =0;

        /** ****************************************************************************************
         * Abstract method to be implemented by descendants. This message is called only when
         * multi-line messages are logged. It is called exactly once before a series of doLog()
         * calls of a multi-line message and exactly once after such series.<br>
         * This is useful if the writing of text includes the acquisition of system resources
         * (e.g. opening a file).
         *
         * @param phase  Indicates the beginning or end of a multi-line operation.
         ******************************************************************************************/
        virtual void notifyMultiLineOp (lib::enums::Phase phase)     =0;

    // #############################################################################################
    // Abstract method implementations
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * This is the implementation of the abstract method inherited from class Logger
         * that executes a log.<br>
         * This class implements this method and but exposes the new abstract method #doTextLog.
         * This mechanism allows this class to do various things that are standard to Loggers
         * of type TextLogger. For example, meta information of the log invocation is formatted
         * and string replacements are performed. This way, descendants of this class will consume
         * a ready to use log buffer with all meta information included and their primary
         * obligation is to copy the content into a corresponding output stream.
         *
         * @param domain    The log domain name.
         * @param level     The log level. This has been checked to be active already on this
         *                  stage and is provided to be able to be logged out only.
         * @param msgObject The object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    the indentation in the output. Defaults to 0.
         * @param caller    Once compiler generated and passed forward to here.
         ******************************************************************************************/
        ALOX_API
        virtual void doLog( const TString&   domain,     Log::Level      level,
                            const void*      msgObject,  int             msgType,
                            int              indent,     CallerInfo*     caller  );

    // #############################################################################################
    // Public interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Adds the given pair of replacement strings. If searched string already exists, the
         * current replacement string gets replaced. If the replacement string equals 'nullptr'
         * nothing is set and a previously set replacement definition becomes unset.
         * @param searched    The string to be searched.
         * @param replacement The replacement string. If this equals 'nullptr' a previously set
         *                    replacement will be unset.
        ******************************************************************************************/
        ALOX_API
        virtual void  SetReplacement( const String& searched, const String& replacement );

        /** ****************************************************************************************
         *  Removes all pairs of searched strings and their replacement value.
         ******************************************************************************************/
        ALOX_API
        virtual void  ClearReplacements();

}; // class TextLogger

}}}} // namespace

#endif // HPP_ALOX_CORE_TEXTLOGGER_TEXTLOGGER
