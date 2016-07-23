// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ //<- needed for Doxygen include

#ifndef HPP_ALOX_TYPES_AND_ENUMS
#define HPP_ALOX_TYPES_AND_ENUMS 1



namespace aworx {
namespace       lox {

/** ************************************************************************************************
 * This enum is used in %ALox to control the 'verbosity' or 'verboseness' of the log output.
 * The values herein - apart from special value 'Off' - are sorted in the following order
 * - Verbose (highest level)
 * - Info
 * - Warning
 * - Error (lowest level).
 *
 * A value of this set is provided to ALox in two different ways:
 * First, all methods of class \ref aworx::lox::Lox "Lox" that execute a log operation
 * assign a value of this enum to the <em>Log Statement</em>. Secondly, methods
 * \ref aworx::lox::Lox::SetVerbosity "Lox::SetVerbosity", are defining the 'accepted' \e minimal
 * \e Verbosity for a pair of <em>\<Logger/%Log Domain\></em>.
 *
 * %ALox, when executing a statement, checks both values against each other. A <em>Log Statement</em>
 * is executed, when the <em>\<Logger/%Log Domain\></em> setting is set to the same or a 'higher level'.
 * For example if a <em>\<Logger/%Log Domain\></em> setting is \b %Warning, then <em>Log Statements</em>
 * with associated \e %Verbosity \b %Warning and \b %Error are executed and those with \b %Info and
 * \b %Verbose are suppressed.
 *
 * If special value \b %Off is used with \ref aworx::lox::Lox::SetVerbosity "Lox::SetVerbosity",
 * all logging is switched Off for this pair of <em>\<Logger/%Log Domain\></em>.
 *
 * Some of the <em>Log Statements</em> accept the parameter directly (e.g.
 * \ref aworx::lox::Lox::Entry "Lox::Entry",
 * \ref aworx::lox::Lox::Once  "Lox::Once" and
 * \ref aworx::lox::Lox::If "Lox::If"), others inherently use the right value as their method
 * name suggests (e.g.
 * \ref aworx::lox::Lox::Error      "Lox::Error",
 * \ref aworx::lox::Lox::Warning    "Lox::Warning",
 * \ref aworx::lox::Lox::Info       "Lox::Info",
 * \ref aworx::lox::Lox::Verbose    "Lox::Verbose" and
 * \ref aworx::lox::Lox::Assert     "Lox::Assert"). The latter group of methods do not support
 * parameter \b %Off.
 *
 * If special value \b %Off is used with those <em>Log Statements</em>, that allow to specify the \e %Verbosity
 * as a parameter, the <em>Log Statement</em> is never executed This is useful if the parameter is
 * determined at runtime, depending on the state of an application.
 **************************************************************************************************/
enum class Verbosity
{
    /**
     * The 'highest' level of \e %Verbosity.
     * Statements with this value associated are logged only if a <em>%Log Domain</em> is set to \b %Verbose as well.
     */
    Verbose,

    /**
     * The standard \e Verbosity for normal log output statements.
     * Logged if a <em>%Log Domain</em> is set to \b %Info or \b %Verbose.
     */
    Info,

    /**
     * A \e Verbosity for warning messages, hence things that might lead to errors or are not
     * welcome for other reasons, but maybe are not errors.<br>
     * Logged if a <em>%Log Domain</em> is set to \b %Warning, \b %Info or \b %Verbose.
     */
    Warning,

    /**
     * A \e Verbosity for error messages.
     * It is suppressed only if a <em>%Log Domains'</em> setting is \b %Off.
     */
    Error,

    /**
     * Statements with this value associated are never logged (useful if \e %Verbosity is
     * evaluated at run-time). <em>%Log Domains</em> with this setting do not execute any
     * <em>Log Statement</em>.
     */
    Off
};

/** ****************************************************************************************
 * Provides a string representation of the Verbosity enums.
 * @param verbosity The enum value to retrieve a string representation for.
 * @returns A string representation of the provided Verbosity value.
 ******************************************************************************************/
ALOX_API
const String ToString( Verbosity verbosity );

/** ****************************************************************************************
 * Writes a string representation of the priority value into the given AString.
 *
 * @param priority  The priority value
 * @param target    The target to write into.
 * @returns \p target to allow concatenated calls.
 ******************************************************************************************/
ALOX_API
AString& ToStringPriority( int priority, AString& target );

/** ****************************************************************************************
 * Writes a string representation of the \e Verbosity and priority into the given
 * AString.
 *
 * @param verbosity The enum value to retrieve a string representation for.
 * @param priority  The priority of the \p verbosity setting.
 * @param target    The target to write into.
 * @returns \p target to allow concatenated calls.
 ******************************************************************************************/
ALOX_API
AString& ToString( Verbosity verbosity, int priority, AString& target );

/** ****************************************************************************************
 * Interprets given \p src as a verbosity.
 * A case insensitive comparison of only the first (!) character of the start of the string
 * is performed (against 'v', 'i', 'w' and 'e').
 * If no match is found, \e %Verbosity::Off is returned.
 * @param src The string to 'parse'.
 * @returns The verbosity read.
 ******************************************************************************************/
ALOX_API
Verbosity ReadVerbosity( const String& src );



/** ************************************************************************************************
 * These are definitions which are used as a parameter to certain ALox methods to denote
 * the \e Scope of a setting. \e Scopes are dependent of the programming language
 * and hence differ slightly from each other in the different versions of ALox.
 *
 * \note
 *   ALox for C++ implements scope mechanisms using scope information generated by the
 *   preprocessor.
 *   By default, debug logging supports such 'caller information', while release logging
 *   does not.<br>
 *   Therefore, in release-logging, the use of \e Scopes 'Path', 'Filename' and
 *   'Method' will just default to an empty scope and therefore the all reflect the same,
 *   shared scope, which is not very helpful. Therefore, for standard release logging,
 *   the use of the scope mechanisms should be be avoided, unless scope information is
 *   explicitly enabled.<br>
 *   For more information on how to change the defaults, see \ref ALOX_DBG_LOG_CI and
 *   \ref ALOX_REL_LOG_CI in section \ref GrpALoxCodeSelectorSymbols.
 *   For more information on \e Scopes consult the [ALox user manual](../manual.html).
 **************************************************************************************************/
enum class Scope
{
    /** Denotes the global (singleton) scope */
    Global,

    /** Denotes the actual thread as the scope. When used with <em>Scope Domains</em>,
    *   'inner' scopes can be defined optionally by multiple definitions.                */
    ThreadOuter,

    /** Denotes the actual source path as the scope. When used, optionally 'outer' \e Scopes
     *  of this scope level itself can be defined using parent directories of the path.*/
    Path,

    /** Denotes the actual source file as the scope*/
    Filename,

    /** Denotes the actual method as the scope*/
    Method,

    /** Denotes the actual thread as the scope. When used with <em>Scope Domains</em>,
     *   'inner' scopes can be defined optionally by multiple definitions.              */
    ThreadInner
};

/** ****************************************************************************************
 *  Provides a string representation of the Scope enums.
 *  @param scope        The enum value to retrieve a string representation for.
 *  @param pathLevel    The path level.
 *  @param target       The target string.
 *  @returns The \p target, with string representation of the provided Scope value
 *           appended
 ******************************************************************************************/
ALOX_API
AString& ToString( Scope scope, int pathLevel, AString& target );


/** ************************************************************************************************
 * Data objects used with
 * \ref aworx::lox::Lox::Store      "Lox::Store" and
 * \ref aworx::lox::Lox::Retrieve   "Lox::Retrieve".
 **************************************************************************************************/
struct LogData
{
    /** C++ specific: may be used for indentifying derived types. Same as all other fields,
        not futher used by ALox */
    int         Type                            =   0;

    /** A string value*/
    AString     StringValue;

    /** An integer value */
    int         IntegerValue;

    /** Any type of data */
    void*       ObjectValue;

    /** Constructs a data object.
     *  @param s    String data to store.
     *  @param i    Integer value to store.
     *  @param o    Object to store.          */
    LogData( const aworx::String& s, int i, void* o= nullptr)   { StringValue= s; IntegerValue= i; ObjectValue= o; }

    /** Constructs a data object
     *  @param s    String data to store.
     *  @param o    Object to store.          */
    LogData( const aworx::String& s,        void* o= nullptr)   { StringValue= s; IntegerValue= 0; ObjectValue= o; }

    /** Constructs a data object.
     *  @param i    Integer value to store.
     *  @param o    Object to store.          */
    LogData(                         int i, void* o= nullptr)   {                 IntegerValue= i; ObjectValue= o; }

    /** Constructs a data object.
     * This constructor is not available under MSC compilation due to ambiguous overloading.
     * With MSC, an parameterless constructor is provided instead (for technical reasons
     * not shown in this documentation).
     *  @param o    Object to store.
     */
    #if !defined ( _MSC_VER ) || defined( IS_DOXYGEN_PARSER)
        LogData(                            void* o= nullptr)   {                 IntegerValue= 0; ObjectValue= o; }
    #else
        LogData(                                            )   {                 IntegerValue= 0; ObjectValue= nullptr; }
    #endif

    /** Virtual Destructor.
     * Objects of this type will be created by the user, but destructed by the Lox */
    virtual ~LogData()                                         {}

    /** ************************************************************************************************
     * Provides a string representation of a LogData object
     * @param target  The target string.
     * @returns The \p target, with string representation of the provided Scope value
     *          appended
     **************************************************************************************************/
    ALOX_API
    AString& ToString( AString& target );
};

/** ************************************************************************************************
 * This class defines "escape sequences" that influence the formatting of log output.
 * Specific implementations of class
 * \ref aworx::lox::core::Logger "Logger"
 * have to convert or interpret this classes definitions of escape sequences
 * when processing log data. If no formatting of the output is supported by a specific Logger
 * implementation, such logger should filter and discard escape sequences defined here.
 *
 * The sequences are similar to ANSI Escape sequences and logger classes that
 * log to 'VT100' compatible terminals will simply convert them.
 *
 * The name of the class was intentionally chosen to be short, because the escape codes
 * defined with this class will be concatenated to log strings like that:
 *
 * \snippet "ut_dox_manual.cpp"     DOX_ALOX_ESC
 **************************************************************************************************/
class ESC
{
    public:
    #if defined(_MSC_VER)
    // MSC  (as of 12/2015):
    // C4579: in-class initialization for type 'const aworx::SLiteral<10>'
    // is not yet implemented; static member will remain uninitialized at runtime but
    // use in constant-expressions is supported

    ALIB_API static     SLiteral<3>  RED                    ; ///< Select red color for foreground.
    ALIB_API static     SLiteral<3>  GREEN                  ; ///< Select green color for foreground.
    ALIB_API static     SLiteral<3>  YELLOW                 ; ///< Select yellow color for foreground.
    ALIB_API static     SLiteral<3>  BLUE                   ; ///< Select blue color for foreground.
    ALIB_API static     SLiteral<3>  MAGENTA                ; ///< Select magenta color for foreground.
    ALIB_API static     SLiteral<3>  CYAN                   ; ///< Select cyan color for foreground.
    ALIB_API static     SLiteral<3>  BLACK                  ; ///< Select black color for foreground.
    ALIB_API static     SLiteral<3>  WHITE                  ; ///< Select white color for foreground.
    ALIB_API static     SLiteral<3>  GRAY                   ; ///< Select gray color for foreground.
    ALIB_API static     SLiteral<3>  FG_RESET               ; ///< Select std color for foreground.

    ALIB_API static     SLiteral<3>  BG_RED                 ; ///< Select red color for background.
    ALIB_API static     SLiteral<3>  BG_GREEN               ; ///< Select green color for background.
    ALIB_API static     SLiteral<3>  BG_YELLOW              ; ///< Select yellow color for background.
    ALIB_API static     SLiteral<3>  BG_BLUE                ; ///< Select blue color for background.
    ALIB_API static     SLiteral<3>  BG_MAGENTA             ; ///< Select blue color for background.
    ALIB_API static     SLiteral<3>  BG_CYAN                ; ///< Select blue color for background.
    ALIB_API static     SLiteral<3>  BG_BLACK               ; ///< Select red color for background.
    ALIB_API static     SLiteral<3>  BG_WHITE               ; ///< Select blue color for background.
    ALIB_API static     SLiteral<3>  BG_GRAY                ; ///< Select gray color for background.
    ALIB_API static     SLiteral<3>  BG_RESET               ; ///< Select std color for background.

    ALIB_API static     SLiteral<3>  BOLD                   ; ///< Select bold font style.
    ALIB_API static     SLiteral<3>  ITALICS                ; ///< Select italics font style.
    ALIB_API static     SLiteral<3>  STYLE_RESET            ; ///< Select standard font style.
    ALIB_API static     SLiteral<3>  RESET                  ; ///< Reset color and style.

    ALIB_API static     SLiteral<3>  URL_START              ; ///< Mark the start of an URL.
    ALIB_API static     SLiteral<3>  URL_END                ; ///< Mark the end of an URL.
    ALIB_API static     SLiteral<3>  TAB                    ; ///< Go to next tab. Usually, text loggers will increase the tab position automatically.

    ALIB_API static     SLiteral<3>  EOMETA                 ; ///< End of meta information in log string

    #else
    static constexpr    SLiteral<3>  RED        { "\033c0" }; ///< Select red color for foreground.
    static constexpr    SLiteral<3>  GREEN      { "\033c1" }; ///< Select green color for foreground.
    static constexpr    SLiteral<3>  YELLOW     { "\033c2" }; ///< Select yellow color for foreground.
    static constexpr    SLiteral<3>  BLUE       { "\033c3" }; ///< Select blue color for foreground.
    static constexpr    SLiteral<3>  MAGENTA    { "\033c4" }; ///< Select magenta color for foreground.
    static constexpr    SLiteral<3>  CYAN       { "\033c5" }; ///< Select cyan color for foreground.
    static constexpr    SLiteral<3>  BLACK      { "\033c6" }; ///< Select black color for foreground.
    static constexpr    SLiteral<3>  WHITE      { "\033c7" }; ///< Select white color for foreground.
    static constexpr    SLiteral<3>  GRAY       { "\033c8" }; ///< Select gray color for foreground.
    static constexpr    SLiteral<3>  FG_RESET   { "\033c9" }; ///< Select std color for foreground.

    static constexpr    SLiteral<3>  BG_RED     { "\033C0" }; ///< Select red color for background.
    static constexpr    SLiteral<3>  BG_GREEN   { "\033C1" }; ///< Select green color for background.
    static constexpr    SLiteral<3>  BG_YELLOW  { "\033C2" }; ///< Select yellow color for background.
    static constexpr    SLiteral<3>  BG_BLUE    { "\033C3" }; ///< Select blue color for background.
    static constexpr    SLiteral<3>  BG_MAGENTA { "\033C4" }; ///< Select blue color for background.
    static constexpr    SLiteral<3>  BG_CYAN    { "\033C5" }; ///< Select blue color for background.
    static constexpr    SLiteral<3>  BG_BLACK   { "\033C6" }; ///< Select red color for background.
    static constexpr    SLiteral<3>  BG_WHITE   { "\033C7" }; ///< Select blue color for background.
    static constexpr    SLiteral<3>  BG_GRAY    { "\033C8" }; ///< Select gray color for background.
    static constexpr    SLiteral<3>  BG_RESET   { "\033C9" }; ///< Select std color for background.

    static constexpr    SLiteral<3>  BOLD       { "\033sB" }; ///< Select bold font style.
    static constexpr    SLiteral<3>  ITALICS    { "\033sI" }; ///< Select italics font style.
    static constexpr    SLiteral<3>  STYLE_RESET{ "\033sr" }; ///< Select standard font style.
    static constexpr    SLiteral<3>  RESET      { "\033sa" }; ///< Reset color and style.

    static constexpr    SLiteral<3>  URL_START  { "\033lS" }; ///< Mark the start of an URL.
    static constexpr    SLiteral<3>  URL_END    { "\033lE" }; ///< Mark the end of an URL.
    static constexpr    SLiteral<3>  TAB        { "\033t0" }; ///< Go to next tab. Usually, text loggers will increase the tab position automatically.

    static constexpr    SLiteral<3>  EOMETA     { "\033A0" }; ///< End of meta information in log string

    #endif

    /** ************************************************************************************************
     * Replaces ESC codes in a string reversely to "ESC::XXX".
     * @param target   The string to replace in.
     * @param startIdx The index to start searching for ESC codes.
     **************************************************************************************************/
    ALOX_API
    static void ReplaceToReadable( AString& target, int startIdx );
};

} // namespace lox

/** Type alias name in namespace #aworx. */
using     ESC=           aworx::lox::ESC;

/** Type alias name in namespace #aworx. */
using     Verbosity=     aworx::lox::Verbosity;

/** Type alias name in namespace #aworx. */
using     Scope=         aworx::lox::Scope;

/** Type alias name in namespace #aworx. */
using     LogData=       aworx::lox::LogData;

}  // namespace aworx
#endif // HPP_ALOX_TYPES_AND_ENUMS
