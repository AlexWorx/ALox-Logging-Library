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
namespace aworx { namespace lib { namespace strings { class Substring; } } }

namespace aworx {
namespace           lox {
namespace                   core{
/** ************************************************************************************************
 * This namespaces defines class \b TextLogger and its helpers.
 **************************************************************************************************/
namespace                           textlogger{



/** ************************************************************************************************
 * This abstract class represents a plug-in for the TextLogger class which converts a given Object
 * into its textual representation.
 * \see StringConverter for further information.
 **************************************************************************************************/
class ObjectConverter
{
    public:
        /** ****************************************************************************************
         * Destructs an object of this class.
         ******************************************************************************************/
        virtual        ~ObjectConverter() {};

        /** ****************************************************************************************
         * The conversion method.
         * @param logable   The object to convert.
         * @param target    An AString that takes the result.
         *
         * @return \c true, if the object was converted successfully, \c false otherwise.
         ******************************************************************************************/
        virtual bool    ConvertObject( const Logable& logable, AString& target )                = 0;
};

/** ************************************************************************************************
 * Implements the interface
 * \ref aworx::lox::core::textlogger::ObjectConverter "ObjectConverter".
 * With ALox leveraging the underlying
 * \ref aworx::lib::strings "ALib string class-family", various standard string types are supported
 * with this converter.
 *
 * While other ALox implementations, like ALox for C# or ALox for Java use the 'runtime type
 * information' feature of their underlying programming language to identify any object type,
 * this is not possible in standard C++. Therefore, all logging objects in ALox for C++ have
 * to be accompanied with a type information. This is implemented as a simple integer and
 * the value \b '0' is reserved for \b TStrings.
 *
 * All other types are extension types, which are not part of core ALox and user specific types.
 *
 * It is recommended to use positive values for user specific types.
 * Negative IDs are reserved for future ALox types and extensions.
 **************************************************************************************************/
class StringConverter : public ObjectConverter
{
    public:
        /** Used to convert null values to string representation. */
        TString          FmtNullObject                  ="ALox message object (type=0) is nullptr.";

    public:
        /** ****************************************************************************************
         * Constructs an object of this class.
         ******************************************************************************************/
         ALOX_API       StringConverter();
        /** ****************************************************************************************
         * Destructs an object of this class.
         ******************************************************************************************/
        virtual        ~StringConverter() {};

        /** ****************************************************************************************
         * The conversion method.
         * @param logable   The object to convert.
         * @param target    An AString that takes the result.
         *
         * @return \c true, if the object was converted successfully, \c false otherwise.
         ******************************************************************************************/
        ALOX_API
        virtual bool    ConvertObject( const Logable& logable, AString& target );
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
        inline
        void        Reset ()                      {   values.clear(); sessionValues.clear();       }

        /** ****************************************************************************************
         * Initializes a new query sequence, which is a series of invocations of method #Next.
         ******************************************************************************************/
        inline
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
         * \ref aworx::lib::strings::String "String" by parsing it. The numbers in the string have
         * to be separated by ' ' characters (space).
         *
         * @param source    The \b %String that is parsed for the numbers
         * @param session   If \c CurrentData::Clear, which is the default, the current values
         *                  are taken from the last session stored and the sessions data is set to 0.
         *                  If \c CurrentData::Keep, both, current values and
         *                  session values are taken from the string.
         ******************************************************************************************/
        ALOX_API
        void        Import( const String& source, lib::enums::CurrentData session= lib::enums::CurrentData::Clear );

        /** ****************************************************************************************
         * Exports the current session values by converting the stored numbers to a string
         * representation and appending them to the given
         * \ref aworx::lib::strings::AString "AString" object.
         * The numbers in the string will be separated by ' ' characters (space).
         *
         * @param target       The \b %AString to receive the our values
         ******************************************************************************************/
        ALOX_API
        void        Export( AString& target );
};


/** ************************************************************************************************
 * This class is a sort of plug-in for the TextLogger class. Its purpose is to assemble the meta
 * information of each log line (things like timestamps, thread information, verbosity and domain, etc.).
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
         * - %SP: The full path of the source file
         * - %Sp: The trimmed path of the source file
         * - %SF: The callers' source file name
         * - %Sf: The callers' source file name without extension
         * - %SL: The line number in the source file
         * - %SM: The method name
         *
         * - %TD: The date the log call was invoked
         * - %TT: Time of day the log call was invoked
         * - %TC: Time elapsed since the Logger was created or its timer was reset
         * - %TL: Time elapsed since the last log call
         *
         * - %tN: Thread name
         * - %tI: Thread ID
         * - %V:  The verbosity. This is replaced by the corresponding strings found in fields
         *        #VerbosityError, #VerbosityWarning, #VerbosityInfo and #VerbosityVerbose.
         * - %D:  Log domain
         * - %#:  The log call counter (like a line counter, but counting multi lines as one)
         * - %An: An auto-adjusted tabulator. This grows whenever it needs, but never shrinks. The
         *        optional integer number n specifies how much extra space is added when tab is adjusted.
         *        Setting this to a higher value avoids too many adjustments at the beginning of a log session.
         * - %LG: The name of the \e Logger. This might be useful if multiple loggers write to the same
         *        output stream (e.g. Console).
         * - %LX: The name of the \e Lox.
         * - %P:  The name of the process / application.
         *
         * Defaults to
         * \code "%Sp/%SF(%SL):%A5%SM() %A5[%TC +%TL][%tN]%V[%D]%A1(%#): " \endcode
         *
         * If debug logging as well as release logging has scope information disabled
         * (see \ref ALOX_DBG_LOG_CI_OFF and \ref ALOX_REL_LOG_CI_ON ), then it defaults to:
         * \code "[%TC +%TL][%tN]%V[%D]%A1(%#): " \endcode
         */

        #if defined(ALOX_DBG_LOG_CI) || defined(ALOX_REL_LOG_CI)
            #if !defined(_WIN32)
                AString Format { "%Sp/%SF(%SL):%A5%SM() %A5[%TC +%TL][%tN]%V[%D]%A1(%#): "};
            #else
                AString Format {"%Sp\\%SF(%SL):%A5%SM() %A5[%TC +%TL][%tN]%V[%D]%A1(%#): "};
            #endif
        #else
            AString Format {"[%TC +%TL][%tN]%V[%D]%A1(%#): "};
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


        /** The replacement for variable \c %%V in field #Format if \e Verbosity is \c Error */
        String16  VerbosityError           ="[ERR]";

        /** The replacement for variable \c %%V in field #Format if \e Verbosity is \c Warning */
        String16  VerbosityWarning         ="[WRN]";

        /** The replacement for variable \c %%V in field #Format if \e Verbosity is \c  Info */
        String16  VerbosityInfo            ="     ";

        /** The replacement for variable \c %%V in field #Format if \e Verbosity is \c Verbose */
        String16  VerbosityVerbose         ="[***]";

        /** Format string for the output of the log date. For more information, see
             "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat() */
        TString    DateFormat               ="yyyy-MM-dd";

        /** Format string for the output of the time of day. For more information, see
             "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat() */
        TString    TimeOfDayFormat          ="HH:mm:ss";

        /** The word "Days" the out put of time elapsed (if longer than a day). */
        TString    TimeElapsedDays          =" Days ";

        /** Minimum time difference to log in nanoseconds.  Below that #TimeDiffNone is written. */
        long       TimeDiffMinimum          =1000L;

        /** Output for time difference if below reasonable (measurable) minimum defined in #TimeDiffMinimum. */
        TString    TimeDiffNone             ="---   ";

        /** Entity nanoseconds for time difference outputs below 1000 microsecond. */
        TString    TimeDiffNanos            =" ns";

        /** Entity microseconds for time difference outputs below 1000 microseconds. */
        TString    TimeDiffMicros           =" \xC2\xB5s"; // UTF-8 encoding of the greek 'm' letter;

        /** Entity milliseconds for time difference outputs below 1000 milliseconds. */
        TString    TimeDiffMillis           =" ms";

        /** Format for time difference outputs between 10s and 99.9s. */
        TString    TimeDiffSecs             =" s";

        /** Format for time difference outputs between 100s and 60 min. */
        TString    TimeDiffMins             =" m";

        /** Format for time difference outputs between 1h and 24h. */
        TString    TimeDiffHours            =" h";

        /** Format for time difference outputs of more than a day. */
        TString    TimeDiffDays             =" days";

        /** Replacement string if no source info is available. */
        TString    NoSourceFileInfo         ="---";

        /** Replacement string if no source info is available. */
        TString    NoMethodInfo             ="---";

        /** The minimum digits to write for the log number (if used in format string). */
        int        LogNumberMinDigits       = 3;

        /**
         * The maximum time elapsed. Used to determine the width of the output when writing
         * the elapsed time.
         *
         * This field will be read from the
         * configuration variable [ALOX_LOGGERNAME_MAX_ELAPSED_TIME](../group__GrpALoxConfigVars.html)
         * when the \b %TextLogger that this object belongs to is attached to a \b %Lox
         * and written back on removal.
         */
        Ticks      MaxElapsedTime;

    // #############################################################################################
    // Internal fields
    // #############################################################################################
    protected:

        /**  A singleton calendar time object shared between different format variables during one
         *   invocation. */
        lib::time::TicksCalendarTime callerDateTime;

    // #############################################################################################
    // Constructor/Destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Constructor.
         ******************************************************************************************/
                 MetaInfo() : MaxElapsedTime(0)      {}

        /** ****************************************************************************************
         * Virtual destructor.
         ******************************************************************************************/
        virtual ~MetaInfo()                         {}

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
         * @param domain    The <em>Log Domain</em>.
         * @param verbosity The verbosity.
         * @param scope     Information about the scope of the <em>Log Statement</em>..
         *
         * @return The number of tab sequences that were written (by adding ESC::TAB to the buffer).
         ******************************************************************************************/
        ALOX_API
        virtual int Write( TextLogger&        logger,
                           AString&           buffer,
                           core::Domain&      domain,
                           Verbosity          verbosity,
                           ScopeInfo&         scope     );

    // #############################################################################################
    // Internals
    // #############################################################################################
    protected:

        /** ****************************************************************************************
         * Processes the next command found in the format string, by writing formatted information
         * into the given buffer.
         * The given
         * \ref aworx::lib::strings::Substring "Substring" holds the next command.
         * When method the returns, the command is cut from the front.
         *
         * @param logger       The logger that we are embedded in.
         * @param domain       The <em>Log Domain</em>.
         * @param verbosity    The verbosity. This has been checked to be active already on this
         *                     stage and is provided to be able to be logged out only.
         * @param scope        Information about the scope of the <em>Log Statement</em>..
         * @param dest         The buffer to write meta information into.
         * @param variable     The variable to read (may have more characters appended)
         *
         * @return The number of tab sequences that were written (by adding ESC::TAB to the buffer).
         ******************************************************************************************/
        ALOX_API
        virtual int processVariable( TextLogger&      logger,
                                     core::Domain&    domain,
                                     Verbosity        verbosity,
                                     ScopeInfo&       scope,
                                     AString&         dest,
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
 *  The final log message is then passed to the abstract method #logText.
 *  Hence, custom Logger classes that inherited from this class instead of directly from class
 *  #Logger, need to implement #logText instead of implementing #Log.
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
        /** The internal log Buffer. */
        AString         logBuf;

        /** A buffer for converting the user object(s).     */
        AString         msgBuf;

        /** Denotes whether this logger writes to the <em>standard output streams</em>.  */
        bool            usesStdStreams;

        /** Used to avoid to repeatedly register with ALib <em>standard output stream</em> lockers
            when attached to multiple instances of class \b Lox.   */
        int             stdStreamLockRegistrationCounter                                         =0;

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
         * A list of helper objects to get textual representation of logable objects.<br>
         * To extend TextLogger to support logging custom objects, custom converters can
         * be appended. Also, the default may be removed and deleted.<br>
         * In the destructor of this class, all object converters (still attached) will be deleted.
         *
         * When converting an object, all object converts listed here are invoked in
         * <b> reverse order</b> until a first reports a successful conversion.
         */
        std::vector<ObjectConverter*>   ObjectConverters;

        /**
         * A helper object to format log objects into textual representations. This class incorporates
         * a format string that defines the meta information in the log output. Furthermore, to extend
         * TextLogger, this object can be replaced by custom implementations of it.
         */
        textlogger::MetaInfo*           MetaInfo;

        /**
         * Holds a list of values for auto tab positions and field sizes.
         * For each requested value, a corresponding array field is created on the fly.
         * If the format string get's changed and different (new) auto values should be used, then
         * this field should be reset after setting the new format string.
         * The other way round, it is also possible to preset set minimum values for tabs and field
         * sizes and hence avoid the columns growing during the lifetime of the Logger.
         *
         * This field will be read from the
         * configuration variable [ALOX_LOGGERNAME_AUTO_SIZES](../group__GrpALoxConfigVars.html)
         * when the \b %TextLogger that we belong to is attached to a \b %Lox and written back
         * on removal.
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
        TString                         MultiLineDelimiterRepl                               ="\\r";

        /**
         * Headline for multi line messages (depending on #MultiLineMsgMode)  .
         * Defaults to "ALox: Multi line message follows: "
         */
        TString                         FmtMultiLineMsgHeadline="ALox: Multi line message follows: ";

        /**
         * Prefix for multi line messages. This is also used if multi line messages logging is
         * switched off (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes
         * place.
         * Defaults to ">> ".
         */
        TString                         FmtMultiLinePrefix                                   =">> ";

        /**
         *  Suffix for multi line messages. This is also used if multi line messages logging is
         *  switched off (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter
         *  takes place.
         * Defaults to "".
         */
        TString                         FmtMultiLineSuffix                                      ="";

        /** Used to return an error message in the case the object could not be converted. */
        TString                         FmtUnknownObject                 ="<unknown object type %>";

    // #############################################################################################
    // protected Constructor/ public destructor
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Constructs a TextLogger.
         * Reads the format variable for the meta information from the configuration. The
         * variable name is created from the \e Logger name and the suffix <c>'_FORMAT'</c>
         * @param name            The name of the \e Logger.
         * @param typeName        The type of the \e Logger.
         * @param usesStdStreams  Denotes whether this logger writes to the
         *                        <em>standard output streams</em>.
         ******************************************************************************************/
        ALOX_API explicit TextLogger( const String& name, const String& typeName,
                                      bool  usesStdStreams );

        /** ****************************************************************************************
         *  Destructs a TextLogger.
         ******************************************************************************************/
    public:
        ALOX_API virtual ~TextLogger();

    // #############################################################################################
    // Reimplementing interface of grand-parent class SmartLock
    // #############################################################################################

        /** ****************************************************************************************
         * Invokes grand-parent's method and in addition, if field #usesStdStreams
         * is set, registers with
         * \ref aworx::lib::ALIB::StdOutputStreamsLock "ALIB::StdOutputStreamsLock".
         *
         * @param newAcquirer The acquirer to add.
         * @return The new number of \e acquirers set.
         ******************************************************************************************/
        ALIB_API
        virtual int   AddAcquirer( ThreadLock* newAcquirer );

        /** ****************************************************************************************
         * Invokes grand-parent's method and in addition, de-registers with
         * \ref aworx::lib::ALIB::StdOutputStreamsLock "ALIB::StdOutputStreamsLock".
         * @param acquirer The acquirer to remove.
         * @return The new number of \e acquirers set.
         ******************************************************************************************/
        ALIB_API
        virtual int   RemoveAcquirer( ThreadLock* acquirer );


    // #############################################################################################
    // Abstract methods introduced
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  This abstract method introduced by this class "replaces" the the abstract method #Log
         *  of parent class Logger which this class implements. In other words, descendants of this
         *  class need to overwrite this method instead of \b %Do. This class %TextLogger is
         *  responsible for generating meta information, doing text replacements, handle multi-line
         *  messages, etc. and provides the textual representation of the whole log contents
         *  to descendants using this method.
         *
         * @param domain     The <em>Log Domain</em>.
         * @param verbosity  The verbosity. This has been checked to be active already on this
         *                   stage and is provided to be able to be logged out only.
         * @param msg        The log message.
         * @param scope     Information about the scope of the <em>Log Statement</em>..
         * @param lineNumber The line number of a multi-line message, starting with 0.
         *                   For single line messages this is -1.
         ******************************************************************************************/
        virtual void logText(  core::Domain&      domain,
                               Verbosity          verbosity,
                               AString&           msg,
                               core::ScopeInfo&   scope,
                               int                lineNumber)    =0;

        /** ****************************************************************************************
         * Abstract method to be implemented by descendants. This message is called only when
         * multi-line messages are logged. It is called exactly once before a series of #logText
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
    public:
        /** ****************************************************************************************
         * This is the implementation of the abstract method inherited from class Logger
         * that executes a log.<br>
         * This class implements this method and but exposes the new abstract method #logText.
         * This mechanism allows this class to do various things that are standard to Loggers
         * of type TextLogger. For example, meta information of the log invocation is formatted
         * and string replacements are performed. This way, descendants of this class will consume
         * a ready to use log buffer with all meta information and contents of all objects to be
         * included and their primary obligation is to copy the content into a corresponding
         * output stream.
         *
         * @param domain    The <em>Log Domain</em>.
         * @param verbosity The verbosity.
         * @param logables  The list of objects to log.
         * @param scope     Information about the scope of the <em>Log Statement</em>..
         ******************************************************************************************/
        ALOX_API
        virtual void Log( Domain& domain, Verbosity verbosity, Logables& logables, ScopeInfo& scope);

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

}}} // namespace lox::core::textlogger

/** Type alias name in namespace #aworx. */
using     TextLogger=       aworx::lox::core::textlogger::TextLogger;

}  // namespace aworx

#endif // HPP_ALOX_CORE_TEXTLOGGER_TEXTLOGGER
