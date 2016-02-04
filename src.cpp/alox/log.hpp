// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// include ALox main header first...
#if !defined (HPP_ALOX)
    #error "lox.hpp must not be included manually. Include alox.hpp instead."
#endif

// then, set include guard
#ifndef HPP_ALOX_LOG
#define HPP_ALOX_LOG 1



namespace aworx {
namespace       lox {


// forwards
class Lox;
namespace  core   {
                     class Logger;
                     namespace  textlogger  {class TextLogger; }
                  }


/** ************************************************************************************************
 *  The \b %ReportWriter for ALib when using ALox. An instance of this class is created
 *  in method \ref aworx::lox::Log::AddDebugLogger "Log::AddDebugLogger"
 *  and registered with ALib.
 **************************************************************************************************/
class    ALoxReportWriter : public aworx::lib::ReportWriter
{
    protected:
        /** The \b Lox to report to */
        Lox*        lox;

    public:
    /** ************************************************************************************
     * Constructs an \b %ALoxReportWriter.
     * @param lox    The \b Lox to report to.
     **************************************************************************************/
     ALOX_API
     ALoxReportWriter ( Lox* lox );

    /** ************************************************************************************
     * Write ALib reports using ALox.
     * @param report The report to log.
     **************************************************************************************/
     virtual void Report  ( const lib::Report::Message& report );
};

/** ************************************************************************************************
 * While in other implementations of ALox this is a 100% static wrapper of class Lox,
 * in C++, we are not in the need to double Lox functionality in this class.
 * (Note: In C# and Java, this class is the interface class for debug logging, and mimics
 * the the functionality of class
 * \ref aworx::lox::Lox "Lox")
 *
 * What remains are the definitions of important public enumerations, library initialization and
 * other minor things.
 **************************************************************************************************/
class Log
{
    // #############################################################################################
    // Public Enums for ALox
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  These are the levels of log verbosity assignable to a log domain.
         ******************************************************************************************/
        enum class DomainLevel
        {
            /** Do not log anything */
            Off,

            /** %Log only Level::Error*/
            Errors,

            /** %Log only levels Level::WARNING or Level::Error.*/
            WarningsAndErrors,

            /** %Log all levels but Level::Verbose.*/
            InfoWarningsAndErrors,

            /** %Log all.*/
            All,

            /** Inherit level from parent domain*/
            Inherit,
        };

        /** ****************************************************************************************
         *  Provides a string representation of the Log::DomainLevel enums.
         *  @param level The enum value to retrieve a string representation for.
         *  @returns A string representation of the provided Log::DomainLevel value.
         ******************************************************************************************/
        static const String ToString( DomainLevel level );



        /** ****************************************************************************************
         *  These are the levels of log verbosity used in a log call.
         ******************************************************************************************/
        enum class Level
        {
            /** The most verbose log level to be used for debug output statements. Logged only if
             * the domains log level is set to DomainLevel::All*/
            Verbose,

            /** The standard log level for normal log output statements. Logged if the domains
             * level is either DomainLevel::All or DomainLevel::InfoWarningsAndErrors*/
            Info,

            /** A log level for warning messages, hence things that might lead to errors or are not
             * welcome for other reasons, but maybe are not errors.
             * It is not logged only if the domains' log level is DomainLevel::ErrorS or DomainLevel::OFF */
            Warning,

            /** A log level for (severe) error messages
             * It is suppressed only if the domains log level is set to DomainLevel::Off */
            Error,
        };

        /** ****************************************************************************************
         *  Provides a string representation of the Log::Level enums.
         *  @param level The enum value to retrieve a string representation for.
         *  @returns A string representation of the provided Log::Level value.
         ******************************************************************************************/
        static const String ToString( Level level );

        /** ****************************************************************************************
         *  These are definitions which are used as a parameter to certain ALox methods to determine
         *  the breadth of the scope of a setting. The definitions are platform dependent. E.g. in
         *  C# the scope can be "Method" or "SourceFile" file while in Java it can be "Package",
         *  "Class" or "Method". The difference is due to different mechanisms to automatically
         *  collect caller information.<p>
         *
         *  \note The C++ version of ALox implements scope mechanisms using caller information
         *  generated by the preprocessor. By default, debug logging supports such caller
         *  information, release logging does not.<br>
         *  If scope information is not supported, all uses of scopes in C++ will just default
         *  to an empty scope and therefore reflect the same, shared scope, which is not very
         *  helpful. Therefore, for standard release logging, the use of the scope mechanisms
         *  should be be avoided, unless caller information is explicitly enabled. <br>
         *  For more information on how to change the defaults, see \ref ALOX_DBG_LOG_CI and
         *  \ref ALOX_REL_LOG_CI in section \ref GrpALoxCodeSelectorSymbols.
         ******************************************************************************************/
        enum class Scope
        {
            /** No scope should be applied/affected*/
            None,

            /** Defines the actual source file as the scope*/
            SourceFile,

            /** Defines the actual method as the scope*/
            Method,
        };

        /** ****************************************************************************************
         *  Provides a string representation of the Log::Scope enums.
         *  @param scope The enum value to retrieve a string representation for.
         *  @returns A string representation of the provided Log::Scope value.
         ******************************************************************************************/
        static const String ToString( Scope scope );


    // #############################################################################################
    // Version, Compilation flags and verification
    // #############################################################################################
    public:
        /**
         * The version of ALox. The versioning follows the scheme YYMM (2-digit year, 2-digit month)
         * of the initial release date.
         * Besides this version number, field #Revision indicates if this is a revised version
         * of a former release.
         */
        ALIB_API static    const int                    Version;

        /**
         * The revision number of this release. Each ALox #Version is initially released as
         * revision \e 0. Pure maintenance releases that do not change the interface of ALox
         * are holding the same #Version but an increased number in this field.
         */
        ALIB_API static    const int                    Revision;

         /**
         * These flags are used internally to detect incompatibilities when linking ALox to
         * binaries that use differen compilation flags.
         */
        ALIB_API static    const uint32_t               CompilationFlags;

        /**
         * This is for creationg (debug) output on information about the bits found in
         * field #CompilationFlags.
         */
        ALIB_API static
        std::pair <const char*, uint32_t>               CompilationFlagMeanings[4];


         /**
         * These flags are used internally to detect incompatibilities when linking ALox to
         * ALib (can only be different in the unusual case that ALib exists in a library independent
         * from ALox).
         */
        ALIB_API static    const uint32_t               ALibCompilationFlags;

        /** ****************************************************************************************
         * Verifies a given sets of ALox compilation flags with the internal set
         * \ref Log::CompilationFlags. In case they are different in a way
         * that alib gets incompatible (e.g. different class sizes, which results in errors that are
         * very hard to debug), the flags are written to \e cout for comparison and \c false is
         * returned.
         *
         * This method should be called on bootstrap to detect if incompatible library types were
         * built. If several libraries that use ALib are linked together, each should invoke this
         * test against separatedly. The macro \c ALIB_COMPATIBILITY_VERYFIER will provide the
         * flags.
         *
         * @param flags The flags externally grabed using macro \c ALIB_COMPATIBILITY_VERYFIER.
         *
         * @return \c true if compatible, \c false else.
         ******************************************************************************************/
        ALIB_API  static bool    VerifyCompilationFlags( uint32_t flags );


    // #############################################################################################
    // The lox singletons for debug and release logging
    // #############################################################################################
    #if defined(ALOX_DBG_LOG)
    protected:
        /** ****************************************************************************************
         *  This is a singleton static object of type class Lox which is provided for standard
         *  debug logging statements.
         ******************************************************************************************/
        ALOX_API static Lox     defaultDbgLox;

    public:
        /** ****************************************************************************************
         *  This is a singleton static object of type class Lox which is provided for standard
         *  debug logging statements.
         ******************************************************************************************/
        ALOX_API static Lox*    lox;
    #endif

    #if defined(ALOX_REL_LOG)
    protected:
        /** ****************************************************************************************
         *  This is a singleton static object of type class Lox which provided for standard
         *  release logging statements.
         ******************************************************************************************/
        ALOX_API static Lox     defaultRelLox;
    public:
        /** ****************************************************************************************
         *  This is a singleton static object of type class Lox which provided for standard
         *  release logging statements.
         ******************************************************************************************/
        ALOX_API static Lox*    relLox;
    #endif


    // #############################################################################################
    // Initialization and Termination
    // #############################################################################################
    public:
        /**
         * The name of the configuration category of configuration variables used by ALox.<br>
         * Defaults to "ALOX".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #Init.<br>
         * See also \ref aworx::lib::ALIB::ConfigCategoryName "ALIB::ConfigCategoryName".
         */
        ALIB_API static const String&                    ConfigCategoryName;

        /** ****************************************************************************************
         * This method should be called prior to using the ALox library, e.g. at the beginning of
         * the main() method of an application. It is OK, to call this method more than once, which
         * allows independent code entities (e.g. libraries) to bootstrap ALox without having to
         * rely on other code entities to do so.
         * Nevertheless, the very first invocation should not be interrupted by a parallel invocation
         * of a second thread. So, it has to be assured that this method is invoked once on the
         * bootstrap of an application before other threads are active.
         *
         * \note This method invokes
         *       \ref aworx::lib::ALIB::Init "ALIB::Init", hence no explicit initialization of
         *       underlying ALib is needed.
         *
         * If command line parameters should be used for configuring ALox, then the very first
         * call to this method has to provide the argc and argv parameters. In addition, the
         * first invocation decides if environment variables are used for the configuration
         * of ALox as well (see parameter 'useEnv'). Subsequent calls to this method with different
         * parameters do not change the setup.
         *
         * \note On the Windows platform, the Microsoft compiler provides the global variables
         *       <em>__argc</em> and <em>__argv</em> (respectively <em>__wargv</em> for wide
         *       character binaries. These variables a can be used if this method is invoked
         *       outside of the <em>main()</em> method.
         *
         * For convenience, several ALox classes call this method implicitly on construction
         * or when using them, e.g. Lox and Logger. Therefore, when using ALox, there is no need
         * to to call this method, unless aforementioned command line parameters should be passed.
         *
         * \note ALox must not be used before all global/static variables are created. Hence, it
         * is not allowed to initialize ALox within static variable initialization code. This
         * restriction is wanted by design, because different platforms and compilers implement the
         * bootstrap of static and global data differently and it is not considered a good
         * programming style to rely on C++ bootstrap. Using ALox/ALIB within C++ bootstrap is
         * undefined behavior. (This is true for any C++ library.)
         *
         *  @param environment  If \c Inclusion::Include (the default), an
         *                    \ref aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         *                    is attached to the
         *                    \ref aworx::lib::ALIB::Config "ALIB::Config" singleton. Hence,
         *                    environment variables are read and potentially do overwrite
         *                    configuration variables in other configuration plug-ins.<br>
         *                    Defaults to \c true.
         *  @param argc       Parameter which in the standard case is taken from  C/C++ main()
         *                    method (Provides the number of command line arguments in argv).
         *                    If this greater than 0, a
         *                    \ref aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn"
         *                    is attached to the
         *                    \ref aworx::lib::ALIB::Config "ALIB::Config" singleton. Hence,
         *                    environment variables are read and potentially overwrite
         *                    configuration variables in other configuration plug-ins.<br>
         *                    Defaults to 0.
         *  @param argv       Parameter which in the standard case is taken from  C/C++ main()
         *                    method (Provides a pointer to a list of command line arguments).
         *                    Defaults to nullptr.
         *
         *  @param wArgs      If \c true, parameter argv is of type '<em>wchar_t **</em>', otherwise
         *                    of type '<em>char **</em>'.
         *                    Defaults to \c false.
         *
         * @returns Returns \c true if ALox was initialized before, \c false if not.
         ******************************************************************************************/
         inline
         static bool     Init( lib::enums::Inclusion environment= lib::enums::Inclusion::Include,
                                        int argc=    0, void** argv= nullptr, bool wArgs= false )
        {
            if ( isInitialized )
                return false;

            Log::checkLibraryVersions();
            return initInternal( environment, argc, argv, wArgs );
        }

        /** ****************************************************************************************
         *  Cleans up static/global ALox memory on termination. This method is useful if using
         *  memory analysis tools (such as valgrind) to remove any internal allocations before a
         *  program terminates.
         ******************************************************************************************/
        ALOX_API static void      TerminationCleanUp();


    protected:
        /**  flag indicating that ALox has been initialized */
        ALOX_API static bool      isInitialized;

        /** ****************************************************************************************
         * Internal, main part of the Init function. (The method is split into two parts, because
         * a portion of it has to be inlined. This allows to veryfy if the ALib/ALox library that
         * a binary is linked to, has the same compilation flags set. This check may avoid a lot of
         * unnecessary debugging trouble.
         *  @param environment  Passed from method #Init
         *  @param argc         Passed from method #Init
         *  @param argv         Passed from method #Init
         *  @param wArgs        Passed from method #Init
         * @returns Returns \c true if ALox was initialized before, \c false if not.
         ******************************************************************************************/
        ALOX_API
        static bool               initInternal( lib::enums::Inclusion environment,
                                                int argc, void** argv, bool wArgs );

        /** ****************************************************************************************
         * Checks if versions of ALib, ALox and the actual compilation unit share compatible
         * compilation symbols.
         * This method is invoked automatically by method #Init.
         * @param alibVersion Defaults to a value defined by the currently included headers.
         * @param aloxVersion Defaults to a value defined by the currently included headers.
         * @param flagsALib   Defaults to a value defined by the currently included headers.
         * @param flagsALox   Defaults to a value defined by the currently included headers.
         ******************************************************************************************/
        ALOX_API
        static void               checkLibraryVersions( int alibVersion    =ALIB_VERSION_VERYFIER,
                                                        int aloxVersion    =ALIB_VERSION_VERYFIER, //currently the same as ALib
                                                        uint32_t flagsALib =ALIB_COMPATIBILITY_VERYFIER,
                                                        uint32_t flagsALox =ALOX_COMPATIBILITY_VERYFIER  );


    public:
        /**  The ALib ReportWriter. This will be created and registered in method
         *   \ref aworx::lox::Log::AddDebugLogger "Log::AddDebugLogger" and removed and deleted in
         *   \ref aworx::lox::Log::RemoveDebugLogger "Log::RemoveDebugLogger".
         */
        static ALoxReportWriter*  DebugReportWriter;
        /**  The original ALib ReportWriter was replaced by method
         *   \ref aworx::lox::Log::AddDebugLogger "Log::AddDebugLogger" and is reinstalled with
         *   \ref aworx::lox::Log::RemoveDebugLogger "Log::RemoveDebugLogger".
         */
        static lib::ReportWriter* OrigReportWriter;

    // #############################################################################################
    // Determine/Guessing debug log environment
    // #############################################################################################
    public:
        #if defined(ALOX_DBG_LOG)
            /**  The debug logger created by AddDebugLogger. */
            ALOX_API static aworx::lox::core::textlogger::TextLogger*   DebugLogger;

            /** ************************************************************************************
             * This method creates an adequate/default debug logger.
             * It is used by macro \ref Log_AddDebugLogger also automatically invoked
             * when debug logging is used without the explicit creation and registration of
             * any other logger.
             *
             * Of-course, alternatively to using this method (resp. the macro), a suitable (set of)
             * debug logger(s) can be created manually. Also, before or after using this method
             * additional debug loggers may be created.
             *
             * In the current version of ALox (future changes are likely), this method does:
             * - use
             *   \ref aworx::lox::Lox::CreateConsoleLogger "Lox::CreateConsoleLogger"
             *   to create the best compatible console logger for the
             *   running platform
             * - this logger will be added to the debug Lox object with specifiying
             *   \c Log::DomainLevel::Errors as the level for internal messages.
             * - If under windows, a Visual Studio debug session is running, adds a
             *   \ref aworx::lox::loggers::VStudioLogger "VStudioLogger"
             *   in addition to the standard console logger. This can be suppressed using
             *   configuration variable [ALOX_CL_NO_ADDITONAL_IDE_LOGGER](../group__GrpALoxConfigVars.html).
             *
             * Finally, depending on parameter \p replaceDefaultReportWriter,
             * \ref aworx::lib::Report::ReplaceReportWriter "Report::ReplaceReportWriter"
             * is invoked to provide an \b %ReportWriter of type
             * \ref aworx::lox::ALoxReportWriter "ALoxReportWriter".
             *
             * @param lox  The lox to add the debug logger(s) to.
             * @param replaceDefaultReportWriter
             *             If true, the
             *             \ref aworx::lib::ReportWriter "ReportWriter" of the \b Report returned by
             *             \ref aworx::lib::Report::GetDefault "Report::GetDefault()"
             *             will be replaced by an object of type
             *             \ref aworx::lox::ALoxReportWriter "ALoxReportWriter" using the given
             *             \p lox;
             **************************************************************************************/
            ALOX_API static void      AddDebugLogger( Lox* lox, bool replaceDefaultReportWriter );

            /** ************************************************************************************
             *  Removes the logger(s) and which was (were) created by \ref AddDebugLogger.
             *  This method also invokes
             *  \ref aworx::lib::Report::ReplaceReportWriter "Report::Replace(null)"
             *  to install a default \ref aworx::lib::ReportWriter "ReportWriter" for ALib.
             *
             *  @param lox The lox to remove the debug logger(s) from.
             **************************************************************************************/
            ALOX_API static void      RemoveDebugLogger( Lox* lox );
        #endif // ALOX_DBG_LOG

}; // LOG


}} // namespace

#endif // HPP_ALOX_LOG
