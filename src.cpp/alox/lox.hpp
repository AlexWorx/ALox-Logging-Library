// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include ALox main header first...
#if !defined (HPP_ALOX)
    #error "lox.hpp must not be included manually. Include alox.hpp instead."
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

// then, set include guard
#ifndef HPP_ALOX_LOX
#define HPP_ALOX_LOX 1

// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
#endif
#if !defined (HPP_ALOX_CORE_SCOPEINFO)
    #include "alox/core/scopeinfo.hpp"
#endif
#if !defined (HPP_ALOX_CORE_LOGGER)
    #include "alox/core/logger.hpp"
#endif
#if !defined (HPP_ALOX_CORE_DOMAIN)
    #include "alox/core/domain.hpp"
#endif
#if !defined (HPP_ALOX_CORE_SCOPE)
    #include "alox/core/scopestore.hpp"
#endif

#if !defined (_GLIBCXX_MAP) && !defined(_MAP_)
    #include <map>
#endif


namespace aworx {
namespace       lox {

namespace  core   {
                     class Logger;
                     namespace  textlogger  {class TextLogger; }
                  }


/** ************************************************************************************************
 * This class acts as a container for \e Loggers and provides a convenient interface to logging.
 * Fore information how to use this class, checkout the ALox tutorials and the ALox manual.
 *
 * If thread safeness is not needed for the logging system (see user manual),
 * the mutex can be switched of using inherited method
 * \ref aworx::lib::threads::ThreadLock::SetSafeness "ThreadLock::SetSafeness".
 * The goal here would be to increase logging performance. This is really a very
 * seldom case when performance is absolutely key, and it is better to be kept in safe mode.
 *
 * <b>'Logable Objects' in <em>ALox for C++</em></b><br>
 * While other ALox implementations, like ALox for C# or ALox for Java use the 'runtime type
 * information' feature of their underlying programming language to identify any object type,
 * this is not possible in standard C++. Therefore, in ALox for C++ objects of type
 * \e void* are logged. Together with the pointer, a type information has to be provided.
 *
 * The default type '0' is the only predefined type that ALox comes with and indicates
 * \ref aworx::lib::strings::TString "ALib TString". Due to the flexible and
 * implicit conversion of user defined string types, almost anything that is a string can be passed
 * to be logged. (For more information on string handling in ALib, see \ref aworx::lib::strings).
 *
 * The use of custom types (in combination with custom logger implementations or custom
 * \ref aworx::lox::core::textlogger::ObjectConverter "textlogger::ObjectConverter" types
 * allows to dispatch just any other data to their log destination.
 **************************************************************************************************/
class Lox : public aworx::lib::threads::ThreadLock
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
         * A counter for the quantity of calls. The count includes logs that were suppressed by
         * disabled <em>Log Domain</em> and those suppressed by the optional log condition parameter.
         */
        int                                        CntLogCalls                                   =0;

        /**
         * Denotes if <em>Log Domains</em> are searched ignoring the letter case or being sensitive
         * about it.<br>
         * Defaults to \p Case::Ignore.
         */
        Case                                       DomainSensitivity                  =Case::Ignore;

        /**
         * Constant providing default value for parameter \p priority of method #SetVerbosity.
         * This value is defined in alignment with plug-in priority constants found in
         * ALib class \b %Configuration, namely
         * - \ref aworx::lib::config::Configuration::PrioCmdLine   "Configuration::PrioCmdLine"
         *   with a value of of 400,
         * - \ref aworx::lib::config::Configuration::PrioEnvVars   "Configuration::PrioEnvVars"
         *   with a value of 300 and
         * - \ref aworx::lib::config::Configuration::PrioIniFile   "Configuration::PrioIniFile"
         *   with a value of 200.
         *
         * Having a value of 100, source code settings by default have lowest priority.
         */
        static constexpr  int                      PrioSource                                 = 100;

        /**
         * Constant providing the maximum value for parameter \p priority of method #SetVerbosity.
         * A \e Verbosity set with this priority is immutable in respect to external configuration
         * data.
         */
         #if defined( _MSC_VER )
            constexpr   static      int            PrioProtected  = MAXINT;
         #else
            static constexpr  int                  PrioProtected  = std::numeric_limits<int>::max();
         #endif



    // #############################################################################################
    // Private/protected fields  and constants
    // #############################################################################################
    protected:
        /** Information about the source code, method, thread, etc. invoking a log  call */
        core::ScopeInfo                            scopeInfo;

        /**
         * Dictionary to translate thread IDs into something maybe nicer/shorter.
         * The dictionary has to be filled by the user of the library.
         */
        core::ScopeInfo::ThreadDictionary          threadDictionary;

        /**
         * The root domain \"/\". All registered domains become a sub domain of this root.
         * If a <em>Sub-Log Domains' Verbosity</em> is not explicitly set, such sub domain inherits
         * the verbosity of its parent.
         */
        core::Domain                               domains;

        /**
         * The root domain for internal <em>Log Domains</em>.
         */
        core::Domain                               internalDomains;

        /** Scope Domains */
        core::ScopeStore<AString*>                 scopeDomains;

        /** Log once counters */
        core::ScopeStore<std::map<AString, int>*>  scopeLogOnce;

        /** Prefix logables store */
        core::ScopeStore<core::Logable*>           scopePrefixes;

        /** Log data store */
        core::ScopeStore<std::map<AString, LogData*>*> scopeLogData;

        /** Used for tabular output of logger lists */
        int                                        maxLoggerNameLength                           =0;

        /** Used for tabular output of logger lists */
        int                                        maxDomainPathLength;

        /** A key value used in stores if no key is given (global object).  */
        const aworx::TString                       noKeyHashKey                               = "$";

        /** The list of collected log objects which is passed to the \e Loggers  */
        core::Logables                             tmpLogables;


        /**  Domain stubstitution rules.  */
        struct DomainSubstitutionRule
        {
            /** Rule types */
            public: enum class Type
            {
                Exact,       ///< Exact match
                StartsWith,  ///< Starts with match
                EndsWith,    ///< Ends with match
                Substring    ///< Any sub-string
            };

            Type            type;          ///< Denotes the type of the rule, depending of what
                                           ///  was set in originally as search path
            String32        Search;        ///< The path to search.
            String32        Replacement;   ///< The replacement.

            /**  Constructor.
             * @param s The path to search.
             * @param r The replacment.
            */
            DomainSubstitutionRule( const TString& s, const TString& r )
            {
                ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( Search,      ReplaceExternalBuffer );
                ALIB_WARN_ONCE_PER_INSTANCE_DISABLE( Replacement, ReplaceExternalBuffer );

                // get type and adjust given search parameter
                int startPos=   0;
                int length=     s.Length();
                if ( s.CharAtStart() == '*' )
                {
                    startPos++;
                    length--;
                    if ( s.CharAtEnd() == '*' )
                    {
                        type= Type::Substring;
                        length--;
                    }
                    else
                        type= Type::EndsWith;
                }
                else
                {
                    if ( s.CharAtEnd() == '*' )
                    {
                        type= Type::StartsWith;
                        length--;
                    }
                    else
                        type= Type::Exact;
                }
                Search._( s, startPos, length );

                // minimum rule check
                if (   (     (    type == Type::Exact
                               || type == Type::StartsWith )
                         && !Search.StartsWith( "/" )
                        )
                    || (    type == Type::EndsWith
                        &&  Search.EndsWith( "/" )
                       )
                   )
                    Search._(); // illegal rule


                Replacement= r;
            }
        };

        /**  The list of domain substitution rules.  */
        std::vector<DomainSubstitutionRule>        domainSubstitutions;

        /**  Flag if a warning on circular rule detection was logged.  */
        bool                                       oneTimeWarningCircularDS                  =false;


    // #############################################################################################
    // Constructors/destructor
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Constructs a new, empty Lox with the given \p name.
         * The name is immutable and all \b %Lox objects registered with ALox must be unique.
         * Lower case letters in the name are converted to upper case.
         * The name \c "Log" is reserved for the internal default singleton used for debug-logging.
         * In addition, name \c "GLOBAL" is not allowed.
         *
         * If parameter \p register is \c true (the default), static method
         * \ref aworx::lox::ALox::Register "ALox::Register" is invoked and the object will be
         * retrievable with static method
         * \ref aworx::lox::ALox::Get "ALox::Get". In some situations, such 'registration'
         * may not be wanted.
         *
         * @param name       The name of the Lox. Can be logged out, e.g. by setting
         *                   aworx::lox::textlogger::MetaInfo::Format "MetaInfo.Format" accordingly.
         *                   Will be converted to upper case.
         * @param doRegister If \c true, this object is registered with static class
         *                   \ref aworx::lox::ALox "ALox".
         *                   Optional and defaults to \c true.
         ******************************************************************************************/
        ALOX_API
        Lox(const TString& name, bool doRegister =true );

        /** ****************************************************************************************
         * Destructs a lox
         ******************************************************************************************/
        ALOX_API virtual    ~Lox();

    // #############################################################################################
    // Interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Returns the name of this \b %Lox. The name user defined, provided in the constructor,
         * converted to upper case and otherwise immutable.
         *
         * @returns The name of this %Lox.
         ******************************************************************************************/
        const TString    GetName()                        { return scopeInfo.loxName;              }

        /** ****************************************************************************************
         * Status of registration with ALox. To keep a \b %Lox "private" using parameter
         * \p doRegister of the constructor, allows to suppress registration.
         * Registered instances of this class can be statically received (by their name) using
         * \ref aworx::lox::ALox::Get "ALox::Get".
         *
         * @returns \c true if this instance was registered with ALox, \c false if not.
         ******************************************************************************************/
        bool             IsRegistered()                   { return ALox::Get( GetName() ) == this; }


        /** ***************************************************************************************
         * Sets the scope information data for the next log. In addition, invoces
         * \ref aworx::lib::threads::ThreadLock::Acquire()
         *
         * @param file  The name of the source code file that the call is placed in. Usually
         *              the predefined preprocessor macro __FILE__ is passed here.
         * @param line  The line number within the source code file that the call is placed in.
         *              Normally the predefined preprocessor macro __LINE__ is passed here.
         * @param func  The name of the function that the call is placed in. Usually the
         *              predefined preprocessor macro __func__ (or __FUNCTION__) is passed here.
         **************************************************************************************/
        void SetScopeInfo( const TString& file, int line, const TString& func )
        {
            #if defined( ALIB_DEBUG )
                ThreadLock::Acquire(file,line,func);
            #else
                ThreadLock::Acquire();
            #endif

            scopeInfo.Set( file, line, func, owner );
        }

        /** ****************************************************************************************
         * Releases ownership of this object. If #Acquire was called multiple times, the same
         * number of calls to this method have to be performed to release ownership.
         ******************************************************************************************/
        virtual void        Release()
        {
             ThreadLock::Release();
        }

        /** ****************************************************************************************
         * Resets this object. Concretely the following steps are performed:
         * - All loggers are removed
         * - All domain settings are cleared
         * - Scope Domains are cleared
         * - Log data is cleared
         * - Log once counters are cleard
         * - The thread dictionary is cleared.
         * - All Trim domains which set are cleared
         *
         * \attention
         *   This method was introduced to support resetting the debug \b %Lox objects in the unit
         *   tests. In real applications, and for release logging it recommended to delete a Lox
         *   and create a new one instead of resetting one.
         *   Side effects might appear using this method!
         ******************************************************************************************/
        ALOX_API
        void        Reset();

        /** ****************************************************************************************
         * Adds \p path to an internal list of substrings that are used to trim the path of
         * a source file name. Trimmed paths are used for \e Scope mechanisms and can be
         * logged (e.g. with meta information of class \b TextLogger.
         *
         * By default such setting affects all instances of class \b Lox, not only
         * this instance. This can be altered using parameter \p global.
         * one other The given trim information can either
         *
         * If given \p path starts with character <c> '*'</c>, the rest of the string is searched
         * within source paths. Otherwise, it is checked if a source path starts with the given
         * path.
         *
         * Parameter \p includeString determines if the given path should be included in the
         * resulting source path or not. In addition, parameter \p offsets, which can be negative
         * or positive, is added to the position of trimming. This can be used to increase the
         * length of the search path, and then cut only a portion of what was searched for.
         *
         * Finally, parameter \p sensitivity determines whether the match is performed case
         * sensitive or not. It defaults to non-sensitive, for convenience and for the fact that
         * for example Microsoft C++ compilers' preprocessor passes lower case path-strings!
         *
         * \note
         *   If the platform (compiler) specific path separator is <c>'/'</c>, then characters
         *   <c>'\'</c> found in parameter \p path are replaced by <c>'\'</c> and vice versa.
         *   This allows to specify paths and substrings thereof in a platform independent way.
         *
         * \attention
         *   Setting global rules (when parameter \p global equals \c Inclusion::Include) is not
         *   protected by a \c mutex against concurrent access. Therefore, global rules have
         *   to be either at bootstrap of a process, before threads are created, or such creation
         *   has to 'manually' be protected by locking all existing instances of this class!
         *
         * @param path          The path to search for. If not starting with <c> '*'</c>, a prefix
         *                      is searched.
         * @param includeString Determines if \p path should be included in the trimmed path or not.
         *                      Optional and defaults to \b %Inclusion::Exclude.
         * @param trimOffset    Adjusts the portion of \p path that is trimmed.
         *                      Optional and defaults to 0.
         * @param sensitivity   Determines if the comparison of \p path with a source files' path
         *                      is performed case sensitive or not.
         *                      Optional and defaults to \b Case::Ignore.
         * @param global        If Inclusion::Exclude, only this instance is affected. Otherwise
         *                      the setting applies to all instances of class \b Lox.
         *                      Optional and defaults to \b Inclusion::Include.
         ******************************************************************************************/
        void      SetSourcePathTrimRule( const TString& path,
                                         Inclusion      includeString   = Inclusion::Exclude,
                                         int            trimOffset      = 0,
                                         Case           sensitivity     = Case::Ignore,
                                         Inclusion      global          = Inclusion::Include )
        {
            scopeInfo.SetSourcePathTrimRule( path, includeString, trimOffset, sensitivity, global );
        }

        /** ****************************************************************************************
         * Removes all local trimming rules set with #SetSourcePathTrimRule.
         * If parameter \p global is set to \b Inclusion::Include, the global rules are cleared
         * in addition.
         *
         * Setting parameter \p allowAutoRule to \c false, allows to suppress the creation of an
         * automatic rule based on the executables path.
         *
         * \see ALox User Manual for more information.
         *
         * @param global        If Inclusion::Exclude, only this instances' rules are cleared.
         *                      Otherwise, the global rules are cleared as well.
         * @param allowAutoRule Determines if an auto rule should be tried to be detected next
         *                      no appropriate rule is found.
         ******************************************************************************************/
        void      ClearSourcePathTrimRules( Inclusion   global          = Inclusion::Include,
                                            bool        allowAutoRule   = true                  )
        {
            scopeInfo.SetSourcePathTrimRule( nullptr, allowAutoRule ? Inclusion::Include
                                                                    : Inclusion::Exclude,
                                             999999, // code for clearing
                                             Case::Ignore,  global  );
        }

        /** ************************************************************************************
         * This static method creates an adequate/default console logger. 'Adequate' here means
         * that this function tries to detect what might be the best choice for the environment
         * that the ALox based process is running in.
         * This method is due to changes with the evolution of future ALox versions and
         * should be considered as a convenience method to shorten the bootstrap code needed
         * to use ALox.
         *
         * The current C++ implementation takes the following approach:
         *
         * - check if configuration variable
         *   [ALOX_CONSOLE_TYPE](../group__GrpALoxConfigVars.html) is set. This variable's
         *   setting takes priority and if set, the according logger is created.
         * - check which
         *   \ref aworx::lib::system::System::RuntimeEnvironment "System::RuntimeEnvironment"
         *   is set and try to choose a reasonable setting.
         *   E.g. if Eclipse CDT IDE is detected, no ANSI support is assumed.
         * - Otherwise, on Unix like OS, class
         *   \ref aworx::lox::loggers::AnsiConsoleLogger "AnsiConsoleLogger" is chosen.
         * - Otherwise, on windows system, check if process is attached to a windows console.
         *   If yes, a
         *   \ref aworx::lox::loggers::WindowsConsoleLogger "WindowsConsoleLogger"
         *   is chosen to enabled colorful output. If no, plain text mode is preferred
         *   by choosing
         *   \ref aworx::lox::loggers::ConsoleLogger "ConsoleLogger".
         *
         * For further information check out the source code.
         *
         * @param name The name of the \e Logger. Defaults to nullptr, which implies standard
         *             logger names defined in the \e Logger sub-classes.
         *
         * @return An instance of the chosen console type logger.
         **************************************************************************************/
        ALOX_API
        static core::textlogger::TextLogger*  CreateConsoleLogger( const String& name= nullptr );

        /** ****************************************************************************************
         * Retrieves an instance of a Logger by its name. This might be useful when access to a
         * \e %Logger is needed to change its configuration.
         *
         * @param loggerName    The name of the \e Logger to search for (case insensitive).
         * @return  The logger, nullptr if not found.
         ******************************************************************************************/
        ALOX_API
        core::Logger*   GetLogger( const String& loggerName );

        /** ****************************************************************************************
         * Removes a logger from this container.
         * \note
         *  To (temporarily) disable a logger without removing it, a call to
         *  \ref SetVerbosity(core::Logger*,Verbosity,const TString&,int) "SetVerbosity(logger, Verbosity::Off)"
         *   can be used.
         *
         * @param logger   The logger to be removed.
         * @returns \c true, if the \e Logger was found and removed, \c false otherwise.
         ******************************************************************************************/
        ALOX_API
        bool            RemoveLogger( core::Logger* logger );

        /** ****************************************************************************************
         * Removes logger named \p loggerName from this container.
         * \note
         *  To (temporarily) disable a logger without removing it, a call to
         *  \ref SetVerbosity(core::Logger*,Verbosity,const TString&,int) "SetVerbosity(logger, Verbosity::Off)"
         *   can be used.
         *
         * @param loggerName  The name of the \e Logger(s) to be removed (case insensitive).
         * @returns The logger that was removed, \c nullptr if not found.
         ******************************************************************************************/
        ALOX_API
        core::Logger*   RemoveLogger( const String& loggerName );

        /** ****************************************************************************************
         * Sets the \e %Verbosity of the <em>Log Domain</em> which is evaluated from parameter \p domain and
         * applicable <em>Scope Domains</em>. The \p verbosity given, is set recursively for all sub-domains.
         *
         * With the first invocation of this method for a distinct \p logger, this \e %Logger
         * is registered with this \e %Lox. In this case, prior to setting the given \e Verbosity
         * for the evaluated sub-domain, the \e Verbosity for all domains is set to
         * \b %Verbosity::Off.
         *
         * To unregister a \e Logger with a \b Lox, use method #RemoveLogger.
         * To 'disable' a \e Logger, invoke this method with parameters \p verbosity equaling to
         * \b %Verbosity::Off and \p domain to \c "/".
         *
         * Optional parameter \p priority defaults to #PrioSource, which is a lower priority
         * than those of the standard plug-ins of external configuration data. Therefore, external
         * configuration by default 'overwrite' settings made from 'within the source code', which
         * simply means by invoking this method.<br>
         * The parameter can be provided for two main reasons:
         * - To 'lock' a verbosity setting against external manipulation.
         * - to 'break' the standard mechanism that an invocation of this method sets all
         *   sub-domains recursively. If a sub-domain was set with a higher priority
         *   (e.g. <c>%PrioSource + 1</c>, then this sub-domain will not be affected by
         *   future invocations of this method with standard-priority given.
         *
         * For more information on how to use external configuration variables with priority and
         * on protecting verbosity settings, consult the [ALox user manual](../manual.html).
         *
         * \attention
         *   The same as with most interface methods of this class, the given \p domain parameter is
         *   combined with <em>%Scope Domains</em> set for the callers' \e %Scope. In standard use
         *   cases of %ALox, the \e %Verbosity of a \e Domain is set using absolute domain path
         *   addressing. Therefore, it is recommended to have any domain path passed to this method
         *   starting with <c> '/'</c>, which suppresses the concatenation of <em>%Scope Domains</em>.<br>
         *   This is why this parameter with this method defaults to <c> '/'</c>, while with other
         *   methods of this class, it defaults to an empty string.
         * <p>
         * \attention
         *   Even when using an absolute domain path, <em>%Scope Domains</em> of
         *   \e %Scope.ThreadInner, will still apply. This means that from within a thread that
         *   has such <em>%Scope Domain</em> set, this method is (almost) not usable!
         *   This all aligns with the concept (advice), that \e Loggers and their \e %Verbosity
         *   are generally set outside of such scopes, hence in configuration sections of a
         *   process.<p>
         * \attention
         *   Consequently, this method may be (mis-) used to modify the 'actual' (default) scope
         *   when explicitly giving an empty string with parameter \p domain. This is useful, to
         *   temporarily adjust a scope. But remember: %ALox was designed to avoid temporary
         *   code lines...
         *
         * @param logger     The logger to be to be affected (case insensitive).
         * @param verbosity  The 'level of verboseness' to be set.
         * @param domain     The parent (start) domain to be set. The use of absolute paths
         *                   starting with <c> '/'</c> are recommended.
         *                   Defaults to root domain \"/\".
         * @param priority   The priority of the setting. Defaults to #PrioSource, which is
         *                   a lower priority than standard plug-ins of external configuration
         *                   have.
         ******************************************************************************************/
        ALOX_API
        void            SetVerbosity( core::Logger*    logger,
                                      Verbosity        verbosity,
                                      const TString&   domain        = TString("/"),
                                      int              priority      = PrioSource             );

        /** ****************************************************************************************
         * Same as \ref #SetVerbosity(core::Logger*,Verbosity,const TString&,int) "SetVerbosity"
         * but addressing the \e %Logger to manipulate by its name.<br>
         * This method may only be used after a \e %Logger was once 'registered' with this \b %Lox
         * using \ref #SetVerbosity(core::Logger*,Verbosity,const TString&,int) "SetVerbosity".
         *
         * @param loggerName The logger to be to be affected, identified by its name (case
         *                   insensitive).
         * @param verbosity  The 'level of verboseness' to be set.
         * @param domain     The parent (start) domain to be set. The use of absolute paths
         *                   starting with <c> '/'</c> are recommended.
         *                   Defaults to root domain \"/\".
         * @param priority   The priority of the setting. Defaults to #PrioSource, which is
         *                   a lower priority than that of standard plug-ins of external
         *                   configuration have.
         ******************************************************************************************/
        ALOX_API
        void            SetVerbosity( const String&    loggerName,
                                      Verbosity        verbosity,
                                      const TString&   domain        =  TString("/"),
                                      int              priority      =  PrioSource          );

        /** ****************************************************************************************
         * The given \p scopeDomain becomes the default domain path for given \p scope.
         * This means, that any subsequent log invocations (from within this same scope) can omit the
         * domain parameter, or if they provide one, this Scope Domain path is prepended.
         * If subsequent log calls specify a domain name with a leading '/' character,
         * then the Scope Domain of the scope is ignored.<br>
         * Furthermore, if the given scope is an inner scope, outer scopes are prepended to the
         * given \p scopeDomain when the resulting domain of a log invocation is evaluated.
         * Again, this behavior can be overruled by prepending a leading '/' character to
         * \p scopeDomain.
         *
         * To remove a previously set Scope Domain a nulled or empty string has to be passed with
         * parameter \p scopeDomain.
         * For \e %Scope.ThreadOuter and \e %Scope.ThreadInner, passing an empty or nulled string
         * removes the most recently added domain path. For removing an explicitly named
         * domain path of \e %Scope.ThreadOuter and \e %Scope.ThreadInner use method
         * #RemoveThreadDomain.
         *
         * \note  The C++ version of ALox implements scope mechanisms using scope information
         *        generated by the preprocessor. By default, debug logging supports such caller
         *        information, release logging does not. This can be changed. For more information
         *        on how to change such defaults, see \ref ALOX_DBG_LOG_CI and \ref ALOX_REL_LOG_CI
         *        in section \ref GrpALoxCodeSelectorSymbols.
         *
         * @param scopeDomain The domain path to register.
         * @param scope       The scope that should the given \p domain be registered for.
         *                    Available Scope definitions are platform/language dependent.
         * @param pathLevel   Used only if parameter \p scope equals
         *                    \ref aworx::lox::Scope::Path "Scope.Path"
         *                    to reference parent directories. Optional and defaults to \c 0.
         ******************************************************************************************/
        void        SetDomain( const TString& scopeDomain, Scope scope, int pathLevel = 0  )
        {
            setDomainImpl( scopeDomain, scope, pathLevel, false, nullptr );
        }

        /** ****************************************************************************************
         * This overloaded version of
         * \ref SetDomain(const TString&,Scope,int) "SetDomain" is applicable only for
         * \e %Scope.ThreadOuter and \e %Scope.ThreadInner and allows to specify the thread that
         * the setting should be associated with.
         *
         * If \p scopeDomain is nullptr or empty, the most recently added domain path is removed.
         * For removing an explicitly named domain associated with  a thread use method
         * #RemoveThreadDomain.
         *
         * @param scopeDomain The domain path to register.
         * @param scope       Either \e %Scope.ThreadOuter or \e %Scope.ThreadInner. With other
         *                    values, an internal error is logged.
         * @param thread      The thread to set/unset a thread-related Scope Domains for.
         ******************************************************************************************/
        void        SetDomain( const TString& scopeDomain, Scope scope, Thread* thread )
        {
            if ( !isThreadReleatedScope( scope ) )
                return;
            setDomainImpl( scopeDomain, scope, 0, false, thread );
        }

        /** ****************************************************************************************
         * Adds a <em>Domain Substitution</em>R.
         * <em>Domain Substitution</em> is performed as a last step when evaluating the domain path of a <em>Log Statement</em>,
         * taking <em>Scope Domains</em> and the optional parameter \p domain of the statement into
         * account.<br>
         *
         * <b>Wildcards</b><br>
         * Parameter \p domainPath supports \b 'wildcard' character <c> '*'</c> at the its beginning
         * and at its end (or both). This allows to have four types of rules:
         * - Exact match
         * - Prefix match (\c * at the end of \p domainPath)
         * - Suffix match (\c * at the start of \p domainPath)
         * - Substring match (\c * at both, start and the end of \p domainPath)
         *
         * Only minimal checks are performed, e.g. if an exact match is requested, but \p domainPath
         * does not start with character <c> '/'</c>. In this and some other cases, the rule is not
         * stored and an internal warning is logged. Further checks, for example for illegal
         * domain path characters are not performed (those will be eliminated when the resulting
         * domain path is to be created internally).
         *
         * <b>Circular Dependencies</b><br>
         * If the given rules have circular dependencies, only a limited number (ten) replacements
         * are performed. If this number of replacements for one <em>Log Statement</em> is exceeded, an internal
         * warning message is logged. This is done only \e once over the life-time of a \e Logger.
         *
         * <b>Application of Rules</b><br>
         * Rules are applied in the order of their definition. After all rules have been applied
         * this is repeated as long as at least one rule matched (up to ten times).
         *
         * <b>Deletion of Rules</b>
         * To delete a rule, invoke the method with same parameter \p domainPath and a 'nulled'
         * or empty string for parameter \p replacement.
         * To delete all rules, invoke the method with parameter \p domainPath 'nulled'
         * or empty.
         *
         * <b>Final remarks</b>
         * Domain substitution is useful to permanently change ('redirect') domain paths of
         * 3rd party code (e.g. libraries using ALox) or log statements that must not be changed
         * for other reasons. It is advised to not 'overuse' this feature, as side effects
         * are inherent to the concept of <em>Domain Substitution</em>. For example, an unwanted side effect might be
         * that <em>Prefix Logables</em> are not applicable to the substituted domain, while other <em>Prefix Logables</em> are
         * bound to the resulting domain.
         *
         * For \b %Lox objects that should be protected of external manipulation, it is advisable,
         * to remove all <em>Domain Substitution</em>Rs right after the \b %Lox was created by invoking this method with
         * a nulled value for parameter \p domainPath. The reason is, that otherwise, through
         * configuration files or command line parameters, domains of the \b %Lox can be substituted
         * and then the resulting domains \e Verbosities be \e overwritten using further configuration
         * variables. Any prioritized \e 'internal' setting of \e Verbosities this way could be
         * circumvented!
         *
         * For more information consult the ALox user manual.
         *
         * @param domainPath  The path to search. Has to start with either  <c> '/'</c> or <c> '*'</c>.
         * @param replacement The replacement path.
         ******************************************************************************************/
        ALOX_API
        void     SetDomainSubstitutionRule( const TString& domainPath, const TString& replacement );

        /** ****************************************************************************************
         * This method is used to remove an <em>explicitly given</em> domain path from the list
         * of domain paths set for \e %Scope.ThreadOuter or \e %Scope.ThreadInner.
         *
         * To remove the most recently added domain path from such thread-related \e %Scope,
         * use one of the overloaded methods #SetDomain and provide an empty or nulled
         * value for parameter \p scopeDomain (the same as how domain paths of other \e %Scopes
         * are removed).
         *
         * \note
         *   The long name of the method already indicates that this method is a little special.
         *   Only seldom, more than one <em>%Scope Domain</em> is needed to be added. And if this
         *   is needed, then such <em>%Scope Domains</em> usually get removed in reverse order of
         *   their definition, with is performed using the standard interface that allows 'removing'
         *   any other <em>%Scope Domain</em>. (Passing an empty or nulled domain
         *   path to method #SetDomain.)
         *
         * @param scopeDomain The domain path to register.
         * @param scope       Either \e %Scope.ThreadOuter or \e %Scope.ThreadInner. With other
         *                    values, an internal error is logged.
         * @param thread      The thread to set/unset a thread-related Scope Domains for.
         *                    Defaults to the current thread.
         ******************************************************************************************/
        ALOX_API
        void        RemoveThreadDomain( const TString& scopeDomain, Scope scope, Thread* thread= nullptr );

        /** ****************************************************************************************
         * The given \p logable becomes a <em>Prefix Logable</em> provided to loggers with log statements
         * executed within the given \p scope.
         * The list of objects received by a logger is sorted from outer scope to inner scope.
         * The logable of the <em>Log Statement</em> itself, is the last in the list, except one or
         * more <em>Prefix Logables</em> of \e %Scope.ThreadInner are set. Those are (similar to how this
         * \e %Scope is handled with <em>%Scope Domains</em>) are appended to the end of the list.
         *
         * To remove a previously set <em>Prefix Logable</em>, \c nullptr has to be passed with
         * parameter \p logable.
         * For \e %Scope.ThreadOuter and \e %Scope.ThreadInner, passing \c nullptr (respectively
         * with the overloaded method accepting string messages, a \e nulled string)
         * removes the most recently added <em>Prefix Logable</em>.
         *
         * \note  The C++ version of ALox implements scope mechanisms using scope information
         *        generated by the preprocessor. By default, debug logging supports such caller
         *        information, release logging does not. This can be changed. For more information
         *        on how to change such defaults, see \ref ALOX_DBG_LOG_CI and \ref ALOX_REL_LOG_CI
         *        in section \ref GrpALoxCodeSelectorSymbols.
         *
         *<p>
         * \note
         *   The word 'prefix' in this methods' name and in the name of ALox feature
         *   <em>Prefix Logables</em> is chosen for the fact that with text loggers (which is the
         *   most widely applied use case for ALox) such objects are prefixes to the log
         *   message. Of-course, with using \e %Scope.ThreadInner, this turns into a suffix!<br>
         *   When using ALox to process objects instead of log messages, the concept of
         *   <em>Prefix Logables</em> is very useful. Just the name does not fit so well anymore.
         *   Think of 'SetContext' and <em>Context Objects</em> instead.
         *
         * @param logable     The <em>Prefix Logable</em> to set.
         * @param type        Type information of \p logable.
         * @param scope       The scope that should the given \p domain be registered for.
         *                    Available Scope definitions are platform/language dependent.
         * @param pathLevel   Used only if parameter \p scope equals
         *                    \ref aworx::lox::Scope::Path "Scope.Path"
         *                    to reference parent directories. Optional and defaults to \c 0.
         ******************************************************************************************/
        void        SetPrefix( const void* logable, int type, Scope scope, int pathLevel = 0  )
        {
            setPrefixImpl( logable, type, scope, pathLevel, nullptr );
        }


        /** ****************************************************************************************
         * This overloaded version of
         * \ref SetPrefix(const void*,int,Scope,int) "SetPrefix" is applicable only for
         * \e %Scope.ThreadOuter and \e %Scope.ThreadInner and allows to specify the thread that
         * the setting should be associated with.
         *
         * If \p scopeDomain is nullptr or empty, the most recently added <em>Prefix Logable</em>
         * is removed.
         *
         * @param logable     The <em>Prefix Logable</em> to set.
         * @param type        Type information of \p logable.
         * @param scope       Either \e %Scope.ThreadOuter or \e %Scope.ThreadInner. With other
         *                    values, an internal error is logged.
         * @param thread      The thread to set/unset a thread-related Scope Domains for.
         ******************************************************************************************/
        void        SetPrefix( const void* logable, int type, Scope scope, Thread* thread )
        {
            setPrefixImpl( logable, type, scope, 0, thread );
        }


        /** ****************************************************************************************
         * Overloaded version of \ref SetPrefix(const void*,int,Scope,int) "SetPrefix"
         * accepting a string-type logable.
         *
         * \note
         *   String-type \e Logables are duplicated interally by ALox when setting as <em>Prefix Logables</em>.
         *   This means, different to <em>Prefix Logables</em> of custom types, the life-cycle of the object passed
         *   in parameter \p logable is allowed to end right after the invokation of this method.
         *
         * @param logable     The string-type <em>Prefix Logable</em> to set.
         * @param scope       The scope that should the given \p logable be registered for.
         *                    Available Scope definitions are platform/language dependent.
         * @param pathLevel   Used only if parameter \p scope equals
         *                    \ref aworx::lox::Scope::Path "Scope.Path"
         *                    to reference parent directories. Optional and defaults to \c 0.
         ******************************************************************************************/
        void        SetPrefix( const TString& logable, Scope scope, int pathLevel = 0  )
        {
            setPrefixImpl( &logable, 0, scope, pathLevel, nullptr );
        }


        /** ****************************************************************************************
         * Overloaded version of \ref SetPrefix(const void*,int,Scope,Thread*) "SetPrefix"
         * accepting a string-type logable.
         *
         * To remove the most recently added <em>Prefix Logable</em> associated with a <em>Log Domain</em>,
         * \c nullptr or a nulled or empty string has to be passed with parameter \p logable.
         *
         * \note
         *   String-type \e Logables are duplicated interally by ALox when setting as <em>Prefix Logables</em>.
         *   This means, different to <em>Prefix Logables</em> of custom types, the life-cycle of the object passed
         *   in parameter \p logable is allowed to end right after the invokation of this method.
         *
         * @param logable     The string-type <em>Prefix Logable</em> to set.
         * @param scope       Either \e %Scope.ThreadOuter or \e %Scope.ThreadInner. With other
         *                    values an internal error is logged.
         * @param thread      The thread to set/unset a thread-related <em>Prefix Logable</em> for.
         ******************************************************************************************/
        void        SetPrefix( const TString& logable, Scope scope, Thread* thread )
        {
            setPrefixImpl( &logable, 0, scope, 0, thread );
        }

        /** ****************************************************************************************
         * The given \p logable becomes a <em>Prefix Logable</em> associated to the given <em>Log Domain</em>.
         * <em>Prefix Logables</em> associated with the <em>Log Domain</em> are added to the list of \e Logables right
         * before the main \e Logable of the <em>Log Statement</em> itself.
         * Multiple <em>Prefix Logables</em> can be added per <em>Log Domain</em>.
         *
         * To remove the most recently added <em>Prefix Logable</em> associated with a <em>Log Domain</em>,
         * \c nullptr has to be passed with parameter \p logable.
         *
         * \attention
         *   The same as with most interface methods of this class, the given \p domain parameter is
         *   combined with <em>%Scope Domains</em> set for the callers' \e %Scope.
         *   To suppress this, an absolute domain path can be used. (Still any <em>Scope Domain</em> of
         *   \e %Scope.Thread.Inner will be applied).
         *   The default value of parameter \p domain is \c "" which addresses the domain evaluated
         *   for the current scope.
         *
         * @param logable     The <em>Prefix Logable</em> to set.
         * @param type        Type information of \p logable.
         * @param domain      The domain path. Defaults to \c nullptr, resulting in
         *                    evaluated <em>Scope Domain</em> path.
         * @param otherPLs    If set to \c Inclusion::Exclude, scope-related <em>Prefix Logables</em>
         *                    are ignored and only domain-related <em>Prefix Logables</em> are passed to
         *                    the \e Loggers.
         *                    Defaults to \c Inclusion::Include.
         ******************************************************************************************/
        ALOX_API
        void        SetPrefix( const void* logable, int type, const TString& domain= nullptr,
                               lib::enums::Inclusion otherPLs=  lib::enums::Inclusion::Include );


        /** ****************************************************************************************
         * Overloaded version of \ref SetPrefix(const void*,int,const TString&, Inclusion) "SetPrefix"
         * accepting a string-type logable.
         *
         * To remove the most recently added <em>Prefix Logable</em> associated with a <em>Log Domain</em>,
         * \c nullptr or a nulled or empty string has to be passed with parameter \p logable.
         *
         * \note
         *   String-type \e Logables are duplicated internally by ALox when setting as <em>Prefix Logables</em>.
         *   This means, different to <em>Prefix Logables</em> of custom types, the life-cycle of the object passed
         *   in parameter \p logable is allowed to end right after the invocation of this method.
         *
         * @param logable     The string-type <em>Prefix Logable</em> to set.
         * @param domain      The domain path. Defaults to \c nullptr, resulting in
         *                    evaluated <em>Scope Domain</em> path.
         * @param otherPLs    If set to \c Inclusion::Exclude, scope-related <em>Prefix Logables</em>
         *                    are ignored and only domain-related <em>Prefix Logables</em> are passed to
         *                    the \e Loggers.
         *                    Defaults to \c Inclusion::Include.
         ******************************************************************************************/
        void        SetPrefix( const TString& logable, const TString& domain= nullptr,
                               Inclusion otherPLs=  Inclusion::Include )
        {
            SetPrefix( &logable, 0, domain, otherPLs );
        }

        /** ****************************************************************************************
         * This method is used reset (or to explicitly set) the start time of one or all logger(s).
         * The only impact is the output of time differences in the log lines. Hence, this method
         * is useful to reset them and see some absolute time values when doing basic performance
         * tests using the \e Logger.
         *
         * \note This affects loggers that are registered for at least one standard domain.
         *       In other words, loggers that are exclusively attached to the internal domain,
         *       will not be affected.
         *
         * @param startTime  Optional parameter with the new start time. Defaults
         *                   to current time if omitted.
         * @param loggerName The name of the \e Logger(s) whose start time is to be set (case insensitive).
         *                   Defaults to empty string, which indicates that all loggers are to
         *                   be affected.
         ******************************************************************************************/
        ALOX_API
        void SetStartTime( lib::time::Ticks  startTime = lib::time::Ticks(0),
                           const String&     loggerName= nullptr );

        #if defined (__GLIBCXX__)
            /** ****************************************************************************************
             * Convertes the given \p startTime and invokes #SetStartTime(lib::time::Ticks, const String&)
             * \note  GLib specific.
             *
             * @param startTime  The new start time in system specific time unit.
             * @param loggerName The name of the \e Logger whose start time is to be set (case insensitive).
             *                   Defaults to empty string, which indicates that all loggers are to
             *                   be affected.
             ******************************************************************************************/
            ALOX_API
            void SetStartTime( time_t startTime, const String& loggerName= nullptr );


        #endif // no elif here, otherwise doxygen would ignore it!

        #if defined( _MSC_VER )
            /** ****************************************************************************************
             * Convertes the given \p startTime and invokes #SetStartTime(lib::time::Ticks, const String&)
             * \note  Microsoft Windows specific.
             *
             * @param startTime  The new start time in system specific time unit.
             * @param loggerName The name of the \e Logger whose start time is to be set (case insensitive).
             *                   Defaults to empty string, which indicates that all loggers are to
             *                   be affected.
             ******************************************************************************************/
            ALOX_API
            void        SetStartTime( LPFILETIME startTime, const String& loggerName= nullptr );

        #endif

        /** ****************************************************************************************
         * This method sets a human readable name to the given thread ID (or current thread) which
         * is optionally included in each log line.
         *
         * @param threadName    The name of the thread as it should be displayed in the logs
         * @param id            (Optional) Parameter providing the thread ID. If omitted, the
         *                      current thread's ID is used.
         ******************************************************************************************/
        ALOX_API
        void        MapThreadName( const String& threadName, int id= 0 );

        /** ****************************************************************************************
         * Stores ALox <em>Log Data</em>, a \e Logable  of base type
         * \ref aworx::lox::LogData "LogData" which can afterwards be retrieved by invoking
         * #Retrieve. Using the optional \p key and \p scope offer various possibilities to reference
         * this data later.<br>
         *
         * To remove data from the store, pass \c nullptr with parameter \p data.
         *
         * \attention
         *  When data objects are 'overwritten', previous objects will be deleted internally.
         *  Hence, only pointers to heap-allocated objects (created with \c new) may be passed!<br>
         *  For more information, consult the ALox user manual.
         *
         * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
         *       It is not advised to use <em>Log Data</em> to implement application logic.
         *
         * @param data      The data object to store.
         *                  If \c nullptr, currently stored data will be removed.
         *                  In C++, has to be heap allocated and will be deleted
         *                  by this \b %Lox when overwritten or this lox is deleted.
         * @param key       The optional key to the data.
         *                  If omitted (or empty or nullptr), the data is bound to the \e %Scope
         *                  provided. If omitted and \p scope is Scope::Global, then the
         *                  data is unique to the \e Lox.
         * @param scope     The \e %Scope that the data is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope::Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         ******************************************************************************************/
        inline
        void        Store( LogData* data,                       const TString& key,
                           Scope scope= Scope::Global , int            pathLevel= 0 )
        {
            storeImpl( data, key, scope, pathLevel );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * Store(LogData*,const TString&,Scope,int) "Store" which omits parameter \p key.
         * @param data      The data object to store.
         *                  In C++, has to be heap allocated and will be deleted
         *                  by this \b %Lox when overwritten or this lox is deleted.
         * @param scope     The \e %Scope that the data is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope::Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         ******************************************************************************************/
        inline
        void        Store( LogData* data,
                           Scope scope= Scope::Global , int            pathLevel= 0 )
        {
            storeImpl( data, nullptr, scope, pathLevel );
        }

        /** ****************************************************************************************
         * Retrieves ALox <em>Log Data</em>, an object of base type
         * \ref aworx::lox::LogData "LogData" which can be stored by invoking
         * #Store. Using the optional \p key and \p scope offer various possibilities to reference
         * such objects.<br>
         *
         * \note If no <em>Log Data</em> object is found, an empty object is stored and returned.
         *
         * <p>
         * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
         *       It is not advised to use <em>Log Data</em> to implement application logic.
         *
         * @param key       The optional key to the data.
         *                  If omitted (or empty or nullptr), the data is bound to the \e %Scope
         *                  provided. If omitted and \p scope is Scope::Global, then the
         *                  data is unique to the \e Lox.
         * @param scope     The \e %Scope that the data is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope::Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         * @return The \b LogData object, \c nullptr if nothing was found.
         ******************************************************************************************/
        ALOX_API
        LogData*  Retrieve( const TString& key,
                              Scope scope= Scope::Global , int  pathLevel= 0 )
        {
            return retrieveImpl( key, scope, pathLevel );
        }

        /** ****************************************************************************************
         * * Overloaded version of #Retrieve which omits parameter \p key.
         *
         * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
         *       It is not advised to use <em>Log Data</em> to implement application logic.
         *
         * @param scope     The \e %Scope that the data is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope::Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         * @return The \b LogData object, \c nullptr if nothing was found.
         ******************************************************************************************/
        ALOX_API
        LogData*  Retrieve  ( Scope scope= Scope::Global , int  pathLevel= 0 )
        {
            return retrieveImpl( nullptr, scope, pathLevel );
        }

        /** ****************************************************************************************
         *  This method logs the configuration this Lox and it's encapsulated objects.
         *
         * @param domain        Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                      set for the \e %Scope of invocation.
         * @param verbosity     The verbosity.
         * @param headLine      If given, a separated headline will be logged at first place.
         ******************************************************************************************/
        ALOX_API
        void        LogConfig( const String&       domain,
                               Verbosity           verbosity,
                               const String&       headLine );


    // #############################################################################################
    // Main logging methods
    // #############################################################################################

        /** ****************************************************************************************
         * Logs a \e Logable  with the given \e %Verbosity.
         *
         * @param domain        Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                      set for the \e %Scope of invocation.
         * @param verbosity     The verbosity.
         * @param logable       The object to log.
         * @param type          Type information on the object to log.
         ******************************************************************************************/
        ALOX_API
        void Entry(  const TString&    domain,
                    Verbosity         verbosity,
                    const void*       logable,
                    int               type );

        /** ****************************************************************************************
         * Overloaded version of \ref Entry(const TString&,Verbosity,const void*,int) "Entry",
         * defaulting parameter \p domain to a nulled string.
         *
         * @param verbosity     The verbosity.
         * @param logable       The object to log.
         * @param type          Type information on the object to log.
         ******************************************************************************************/
        inline
        void Entry(Verbosity verbosity, const void* logable, int type )
        {
            Entry( nullptr, verbosity, logable, type );
        }

        /** ****************************************************************************************
         * Logs a string with the given \e %Verbosity.
         *
         * @param domain        Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                      set for the \e %Scope of invocation.
         * @param verbosity     The verbosity.
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Entry(  const TString&    domain,
                    Verbosity         verbosity,
                    const TString&    msg         )
        {
            Entry( domain, verbosity, &msg, 0 );
        }

        /** ****************************************************************************************
         * Overloaded version of \ref Entry(const TString&,Verbosity,const TString&) "Entry"
         * defaulting parameter \p domain to a nulled string.
         *
         * @param verbosity     The verbosity.
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Entry(Verbosity verbosity, const TString& msg )
        {
            Entry( nullptr, verbosity, &msg, 0 );
        }

        /** ****************************************************************************************
         * Logs a \e Logable  using \ref Verbosity::Verbose.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void Verbose( const TString& domain, void* logable, int type )
        {
             Entry( domain, Verbosity::Verbose, logable, type );
        }

        /** ****************************************************************************************
         * Overloaded version of \ref Verbose(const TString&,const void*,int) "Verbose",
         * defaulting parameter \p domain to a nulled string.
         *
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void Verbose( void* logable, int type )
        {
            Entry( nullptr, Verbosity::Verbose, logable, type );
        }

        /** ****************************************************************************************
         * Logs a string using \ref Verbosity::Verbose.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Verbose( const TString& domain, const TString& msg )
        {
             Entry( domain, Verbosity::Verbose, &msg, 0 );
        }

        /** ****************************************************************************************
         * Overloaded version of \ref Verbose(const TString&,const TString&) "Verbose"
         * defaulting parameter \p domain to a nulled string.
         *
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Verbose( const TString& msg )
        {
            Entry( nullptr, Verbosity::Verbose, &msg, 0 );
        }

        /** ****************************************************************************************
         * Logs a \e Logable  using \ref Verbosity::Info.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void Info( const TString&  domain, void* logable, int type )
        {
            Entry( domain, Verbosity::Info, logable, type );
        }

        /** ****************************************************************************************
         * Overloaded version of \ref aworx::lox::Lox::Info(const TString&,void*,int) "Info",
         * defaulting parameter \p domain to a nulled string.
         *
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void Info( void* logable, int type )
        {
            Entry(  nullptr, Verbosity::Info, logable, type );
        }

        /** ****************************************************************************************
         * Logs a string using \ref Verbosity::Info.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Info( const TString&  domain,   const TString& msg )
        {
            Entry( domain, Verbosity::Info, &msg, 0 );
        }

        /** ****************************************************************************************
         * Overloaded version of \ref aworx::lox::Lox::Info(const TString&,const TString&) "Info"
         * defaulting parameter \p domain to a nulled string.
         *
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Info( const TString& msg )
        {
            Entry(  nullptr, Verbosity::Info, &msg, 0 );
        }

        /** ****************************************************************************************
         * Logs a \e Logable  using \ref Verbosity::Warning.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void Warning( const TString& domain, void* logable, int type )
        {
            Entry( domain, Verbosity::Warning, logable, type );
        }

        /** ****************************************************************************************
         * Overloaded version of \ref Warning(const TString&,const void*,int) "Warning",
         * defaulting parameter \p domain to a nulled string.
         *
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void Warning( void* logable, int type )
        {
            Entry( nullptr, Verbosity::Warning, logable, type );
        }

        /** ****************************************************************************************
         * Logs a string using \ref Verbosity::Warning.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Warning( const TString& domain, const TString& msg )
        {
            Entry( domain, Verbosity::Warning, &msg, 0 );
        }

        /** ****************************************************************************************
         * Overloaded version of \ref Warning(const TString&,const TString&) "Warning"
         * defaulting parameter \p domain to a nulled string.
         *
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Warning( const TString& msg )
        {
            Entry( nullptr, Verbosity::Warning, &msg, 0 );
        }

        /** ****************************************************************************************
         * Logs a \e Logable  using \ref Verbosity::Error.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void Error( const TString& domain,  void* logable, int type )
        {
            Entry( domain, Verbosity::Error, logable, type );
        }

        /** ****************************************************************************************
         * Overloaded version of \ref Error(const TString&,void*,int) "Error",
         * defaulting parameter \p domain to a nulled string.
         *
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void Error( void* logable, int type )
        {
            Entry( nullptr, Verbosity::Error, logable, type );
        }

        /** ****************************************************************************************
         * Logs a string using \ref Verbosity::Error.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Error( const TString& domain,   const TString& msg )
        {
            Entry( domain, Verbosity::Error, &msg, 0 );
        }

        /** ****************************************************************************************
         * Overloaded version of \ref Error(const TString&,const TString&) "Error"
         * defaulting parameter \p domain to a nulled string.
         *
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Error( const TString& msg )
        {
            Entry( nullptr, Verbosity::Error, &msg, 0 );
        }

        /** ****************************************************************************************
         * Logs a \e Logable  or a string message once, up to \p quantity times, or
         * every n-th time.
         * In its simplest overloaded version, the counter is bound to the source code line, hence,
         * only the first execution of this exact <em>Log Statement</em> is executed.
         *
         * Using parameter \p group, a set of <em>Log Statements</em> that share the same group key, can be
         * grouped and of such set, only the one which is first executed actually logs.<br>
         * Alternatively, when \p key is omitted (or nullptr or empty), but a
         * \ref aworx::lox::Scope "Scope" is given with parameter \p scope, then the
         * counter is associated with the scope.<br>
         * Finally, parameters \p key and \p scope can also be used in combination. The key is
         * then unique in respect to the \ref aworx::lox::Scope "Scope" provided.
         *
         * Using, none, one or both of the parameters \p group and \p scope, among others, the
         * following use cases can be achieved.
         * - %Log a specific statement up to n-times.
         * - %Log only the first n of a group of statements.
         * - %Log only the first n statements within a method.
         * - %Log only the first n statements belonging to the same group and method .
         * - %Log only the first n statements within any method of
         *   - a source file
         *   - a directory of source files
         *   - a parent directory of source files and all sources recursively
         * - %Log only the first n statements which belong to the same group and are placed within
         *   any method of
         *   - a source file
         *   - a directory of source files
         *   - a parent directory of source files and all sources recursively
         * - %Log a <em>Log Statement</em> n-times per new thread.
         * - %Log only the first n statements of a group of statements executed by a specific thread.
         *
         * \note
         *   To avoid another set of even more overloaded methods, this is the only method that
         *   accepts arbitrary objects (void* along with a type identifier).
         *
         *
         * When parameter \p quantity is a negative value, the log statement is executed every n-th time
         * instead n-times. E.g, if \p quantity is \c -5, the first statement is executed and afterwards
         * every fifth invocation.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param verbosity The verbosity of the <em>Log Statement</em> (if performed).
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         * @param group     The optional name of the statement group . If used, all statements that
         *                  share the same group name are working on the same counter (according
         *                  to the \p scope.)
         *                  If omitted (or empty or nullptr), the counter is is bound to the \e %Scope
         *                  provided. If omitted and \p scope is Scope::Global, then the
         *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
         * @param scope     The \e %Scope that the group or counter is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope::Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         *                  If negative, the first and every "-quantity-th" statement is executed.
         ******************************************************************************************/
        inline
        void Once( const TString& domain, Verbosity verbosity, const void* logable, int type,
                   const TString& group,
                   Scope scope= Scope::Global , int pathLevel= 0,
                   int quantity= 1)
        {
            once( domain, verbosity, logable, type, group, scope, pathLevel, quantity );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref Once(const TString&,Verbosity,const void*,int,const TString&,Scope,int,int) "Once".
         * which accepts an aworx::String object as the log message.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param verbosity The verbosity of the <em>Log Statement</em> (if performed).
         * @param msg       The string message to log.
         * @param group     The optional name of the statement group . If used, all statements that
         *                  share the same group name are working on the same counter (according
         *                  to the \p scope.)
         *                  If omitted (or empty or nullptr), the counter is is bound to the \e %Scope
         *                  provided. If omitted and \p scope is Scope::Global, then the
         *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
         * @param scope     The \e %Scope that the group or counter is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope.Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        inline
        void Once( const TString& domain, Verbosity verbosity, const TString& msg,
                   const TString& group,
                   Scope scope= Scope::Global , int pathLevel= 0,
                   int quantity= 1)
        {
            once( domain, verbosity, &msg, 0, group, scope, pathLevel, quantity );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref Once(const TString&,Verbosity,const void*,int,const TString&,Scope,int,int) "Once".
         *
         * @param verbosity The verbosity of the <em>Log Statement</em> (if performed).
         * @param msg       The string message to log.
         * @param group     The optional name of the statement group . If used, all statements that
         *                  share the same group name are working on the same counter (according
         *                  to the \p scope.)
         *                  If omitted (or empty or nullptr), the counter is is bound to the \e %Scope
         *                  provided. If omitted and \p scope is Scope::Global, then the
         *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
         * @param scope     The \e %Scope that the group or counter is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope.Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        inline
        void Once(                        Verbosity verbosity, const TString& msg,
                   const TString& group,
                   Scope scope, int pathLevel= 0,
                   int quantity= 1)
        {
            once( nullptr, verbosity, &msg, 0, group, scope, pathLevel, quantity );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref Once(const TString&,Verbosity,const void*,int,const TString&,Scope,int,int) "Once".
         *
         * @param verbosity The verbosity of the <em>Log Statement</em> (if performed).
         * @param msg       The string message to log.
         * @param group     The optional name of the statement group . If used, all statements that
         *                  share the same group name are working on the same counter (according
         *                  to the \p scope.)
         *                  If omitted (or empty or nullptr), the counter is is bound to the \e %Scope
         *                  provided. If omitted and \p scope is Scope::Global, then the
         *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        inline
        void Once(                        Verbosity verbosity, const TString& msg,
                   const TString& group,
                   int quantity= 1)
        {
            once( nullptr, verbosity, &msg, 0, group, Scope::Global, 0, quantity );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref Once(const TString&,Verbosity,const void*,int,const TString&,Scope,int,int) "Once".
         *
         * @param verbosity The verbosity of the <em>Log Statement</em> (if performed).
         * @param msg       The string message to log.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        inline
        void Once(                        Verbosity verbosity, const TString& msg,
                   int quantity= 1)
        {
            once( nullptr, verbosity, &msg, 0, nullptr, Scope::Global, 0, quantity );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref Once(const TString&,Verbosity,const void*,int,const TString&,Scope,int,int) "Once".
         *
         * @param msg       The string message to log.
         * @param group     The optional name of the statement group . If used, all statements that
         *                  share the same group name are working on the same counter (according
         *                  to the \p scope.)
         *                  If omitted (or empty or nullptr), the counter is is bound to the \e %Scope
         *                  provided. If omitted and \p scope is Scope::Global, then the
         *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
         * @param scope     The \e %Scope that the group or counter is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope.Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        inline
        void Once(                                          const TString& msg,
                   const TString& group,
                   Scope scope, int pathLevel= 0,
                   int quantity= 1)
        {
            once( nullptr, Verbosity::Info, &msg, 0, group, scope, pathLevel, quantity );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref Once(const TString&,Verbosity,const void*,int,const TString&,Scope,int,int) "Once".
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param verbosity The verbosity of the <em>Log Statement</em> (if performed).
         * @param msg       The string message to log.
         * @param scope     The \e %Scope that the group or counter is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope.Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        inline
        void Once( const TString& domain, Verbosity verbosity, const TString& msg,
                   Scope scope= Scope::Global , int pathLevel= 0,
                   int quantity= 1)
        {
            once( domain, verbosity, &msg, 0, nullptr, scope, pathLevel, quantity );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref Once(const TString&,Verbosity,const void*,int,const TString&,Scope,int,int) "Once".
         *
         * @param verbosity The verbosity of the <em>Log Statement</em> (if performed).
         * @param msg       The string message to log.
         * @param scope     The \e %Scope that the group or counter is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope.Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        inline
        void Once(                        Verbosity verbosity, const TString& msg,
                   Scope scope, int pathLevel= 0,
                   int quantity= 1)
        {
            once( nullptr, verbosity, &msg, 0, nullptr, scope, pathLevel, quantity );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref Once(const TString&,Verbosity,const void*,int,const TString&,Scope,int,int) "Once".
         *
         * @param msg       The string message to log.
         * @param scope     The \e %Scope that the group or counter is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope.Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        inline
        void Once(                                          const TString& msg,
                   Scope scope, int pathLevel= 0,
                   int quantity= 1)
        {
            once( nullptr, Verbosity::Info, &msg, 0, nullptr, scope, pathLevel, quantity );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref Once(const TString&,Verbosity,const void*,int,const TString&,Scope,int,int) "Once".
         *
         * @param msg       The string message to log.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        inline
        void Once(                                          const TString& msg,
                   int quantity= 1)
        {
            once( nullptr, Verbosity::Info, &msg, 0, nullptr, Scope::Global, 0, quantity );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref Once(const TString&,Verbosity,const void*,int,const TString&,Scope,int,int) "Once".
         *
         * @param msg       The string message to log.
         * @param group     The optional name of the statement group . If used, all statements that
         *                  share the same group name are working on the same counter (according
         *                  to the \p scope.)
         *                  If omitted (or empty or nullptr), the counter is is bound to the \e %Scope
         *                  provided. If omitted and \p scope is Scope::Global, then the
         *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        inline
        void Once(                                          const TString& msg,
                   const TString& group, int quantity= 1 )
        {
            once( nullptr, Verbosity::Info, &msg, 0, group, Scope::Global, 0, quantity );
        }


        /** ****************************************************************************************
         * Logs a \e Logable  only if the parameter \p condition is not \c true.
         * If executed, \ref Verbosity::Error is used.
         *
         * @param condition If \c false, the <em>Log Statement</em> is executed.
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void Assert( bool condition, const TString& domain, void* logable, int type )
        {
            if (!condition )
                Entry( domain, Verbosity::Error, logable, type );
            else
                CntLogCalls++;
        }

        /** ****************************************************************************************
         * Logs a \e Logable  only if the parameter \p condition is not \c true.
         * If executed, \ref Verbosity::Error is used.
         *
         * This overloaded version omits parameter \p domain.
         *
         * @param condition If \c false, the <em>Log Statement</em> is executed.
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void Assert( bool condition, void* logable, int type )
        {
            if (!condition )
                Entry( nullptr, Verbosity::Error, logable, type );
            else
                CntLogCalls++;
        }

        /** ****************************************************************************************
         * Logs a string only if the parameter \p condition is not \c true.
         * If executed, \ref Verbosity::Error is used.
         *
         * @param condition If \c false, the <em>Log Statement</em> is executed.
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Assert( bool condition, const TString& domain, const TString& msg )
        {
            if (!condition )
                Entry( domain, Verbosity::Error, &msg, 0 );
            else
                CntLogCalls++;
        }

        /** ****************************************************************************************
         * Logs a string only if the parameter \p condition is not \c true.
         * If executed, \ref Verbosity::Error is used.
         *
         * This overloaded version omits parameter \p domain.
         *
         * @param condition If \c false, the <em>Log Statement</em> is executed.
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void Assert( bool condition, const TString& msg )
        {
            if (!condition )
                Entry( nullptr, Verbosity::Error, &msg, 0 );
            else
                CntLogCalls++;
        }

        /** ****************************************************************************************
         * Logs a \e Logable  only if the parameter \p condition is \c true.
         *
         * \see Method \ref Assert(bool, const TString&, void*, int) "Assert".
         *
         * @param condition If \c false, the <em>Log Statement</em> is executed.
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param verbosity The verbosity.
         * @param logable   Pointer to the object to log.
         * @param type      Type information on the object to log.
         ******************************************************************************************/
        inline
        void If( bool condition, const TString& domain, Verbosity verbosity, void* logable, int type )
        {
            if ( condition )
                Entry( domain, verbosity, logable, type );
            else
                CntLogCalls++;
        }

        /** ****************************************************************************************
         * Logs a \e Logable  only if the parameter \p condition is \c true.
         *
         * This overloaded version omits parameter \p domain.
         *
         * \see Method \ref Assert(bool, const TString&, void*, int) "Assert".
         *
         * @param condition If \c false, the <em>Log Statement</em> is executed.
         * @param verbosity The verbosity.
         * @param logable   Pointer to the object to log.
         * @param type       information on the object to log.
         ******************************************************************************************/
        inline
        void If( bool condition, Verbosity verbosity, void* logable, int type )
        {
            if ( condition )
                Entry( nullptr, verbosity, logable, type );
            else
                CntLogCalls++;
        }

        /** ****************************************************************************************
         * Logs a string only if the parameter \p condition is \c true.
         *
         * \see Method \ref Assert(bool, const TString&, const TString&) "Assert".
         *
         * @param condition If \c false, the <em>Log Statement</em> is executed.
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param verbosity The verbosity.
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void If( bool condition, const TString& domain, Verbosity verbosity, const TString& msg )
        {
            if ( condition )
                Entry( domain, verbosity, &msg, 0 );
            else
                CntLogCalls++;
        }

        /** ****************************************************************************************
         * Logs a string only if the parameter \p condition is \c true.
         *
         * This overloaded version omits parameter \p domain.
         *
         * \see Method \ref Assert(bool, const TString&, const TString&) "Assert".
         *
         * @param condition If \c false, the <em>Log Statement</em> is executed.
         * @param verbosity The verbosity.
         * @param msg       The string to be logged.
         ******************************************************************************************/
        inline
        void If( bool condition, Verbosity verbosity, const TString& msg )
        {
            if ( condition )
                Entry( nullptr, verbosity, &msg, 0 );
            else
                CntLogCalls++;
        }

    // #############################################################################################
    // internals
    // #############################################################################################
    protected:

        /** ****************************************************************************************
         * Assembles the resulting domain from the given \p domainPath and the Scope Domain paths
         * (see #SetDomain) according to the scope identified by \p scopeInfo.
         * The resulting full domain string is assembled from inner to outer scope.
         * If \p domainPath, respectively as soon as any of the Scope Domains' paths
         * start with the character defined with
         * \ref aworx::lox::core::Domain::PathSeparator "Domain::PathSeparator",
         * the evaluation is stopped (the path is interpreted as absolute).
         *
         * @param domainPath The domain path. If starting with the character defined with
         *                   \ref aworx::lox::core::Domain::PathSeparator "Domain::PathSeparator",
         *                   no Scope Domains are applied.
         * @return The resulting \ref aworx::lox::core::Domain "Domain".
         ******************************************************************************************/
        ALOX_API
        core::Domain*   evaluateResultDomain( const TString& domainPath );

        /** ****************************************************************************************
         * Invokes \b Find on the given domain and logs internal message when the domain was
         * not known before.
         *
         * @param domainSystem  The domain system. Either the standard or the internal one.
         * @param domainPath    The domain path.
         * @return The resulting \ref aworx::lox::core::Domain "Domain".
         ******************************************************************************************/
        ALOX_API
        core::Domain*   findDomain( core::Domain& domainSystem, TString domainPath );

        /** ****************************************************************************************
         * This method is looping over the \e Loggers, checking their verbosity against the given
         * one, and, if they match, invoke the log method of the \e Logger.
         * With the first logger identified to be active, the <em>Prefix Objects</em> get
         * collected from the scope store.
         * @param dom       The domain to log on
         * @param verbosity The verbosity.
         * @param logable   The object to log.
         * @param prefixes  Denotes if prefixes should be included or not.
         ******************************************************************************************/
        ALOX_API
        void      log( core::Domain*  dom,     Verbosity verbosity,
                       core::Logable& logable, Inclusion prefixes );


        /** ****************************************************************************************
         * Logs an internal error message using the internal domain tree as defined in
         * \ref aworx::lox::ALox::InternalDomains "ALox::InternalDomains".
         *
         * @param verbosity The verbosity.
         * @param subDomain The sub-domain of the internal domain to log into.
         * @param msg       The message.
         ******************************************************************************************/
        ALOX_API
        void            logInternal( Verbosity verbosity, const String& subDomain, const TString& msg );

        /** ****************************************************************************************
         * Internal method used by LogConfig() to recursively log Domain instances.
         * @param domain      The Domain instance to log out.
         * @param buffer      The buffer to log to.
         * @return The entry width (potentially increased).
         ******************************************************************************************/
        ALOX_API
        void      logConfigDomainRecursive( core::Domain& domain, AString& buffer );

        /** ****************************************************************************************
         * Implementation of the interface method fetching all possible parameters.
         *
         * @param scopeDomain The domain path to register.
         * @param scope       The scope that the given \p domain should be registered for.
         *                    Available Scope definitions are platform/language dependent.
         * @param pathLevel   Used only if parameter \p scope equals
         *                    \ref aworx::lox::Scope::Path "Scope.Path"
         *                    to reference parent directories.
         * @param removeNTRSD Used to remove a named thread-related Scope Domain (and is true only when
         *                    invoked by interface method #RemoveThreadDomain.
         * @param thread      The thread to set/unset a thread-related Scope Domain for.
         ******************************************************************************************/
        ALOX_API
        void      setDomainImpl( const TString& scopeDomain, Scope scope,
                                 int pathLevel, bool removeNTRSD, Thread* thread  );

        /** ****************************************************************************************
         * Implementation of the interface method fetching all possible parameters.
         *
         * @param logable     The <em>Prefix Logable</em> to set.
         * @param type        Type information of \p logable.
         * @param scope       The scope that the given \p logable should be registered for.
         *                    Available Scope definitions are platform/language dependent.
         * @param pathLevel   Used only if parameter \p scope equals
         *                    \ref aworx::lox::Scope::Path "Scope.Path"
         *                    to reference parent directories.
         * @param thread      The thread to set/unset a thread-related <em>Prefix Logable</em> for.
         ******************************************************************************************/
        ALOX_API
        void      setPrefixImpl( const void*  logable, int   type,
                                 Scope        scope,   int   pathLevel,   Thread* thread  );

        /** ****************************************************************************************
         * Internal method serving public interface #Once.
         *
         * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
         *                  set for the \e %Scope of invocation.
         * @param verbosity The verbosity of the <em>Log Statement</em> (if performed).
         * @param logable   Pointer to the object to log.
         * @param type      information on the object to log.
         * @param group     The optional name of the statement group . If used, all statements that
         *                  share the same group name are working on the same counter (according
         *                  to the \p scope.)
         *                  If omitted (or empty or nullptr), the counter is is bound to the \e %Scope
         *                  provided. If omitted and \p scope is Scope::Global, then the
         *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
         * @param scope     The \e %Scope that the group or counter is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope.Path"
         *                  to reference parent directories. Optional and defaults to \c 0.
         * @param quantity  The number of logs to be performed. As the name of the method indicates,
         *                  this defaults to \c 1.
         ******************************************************************************************/
        ALOX_API
        void once( const TString& domain, Verbosity verbosity, const void* logable,   int type,
                   const TString& group,  Scope     scope,     int         pathLevel, int quantity );

        /** ****************************************************************************************
         * Internal method serving public interface #Store.
         *
         * @param data      The data object to store.
         *                  In C++, has to be heap allocated and will be deleted
         *                  by this \b %Lox when overwritten or this lox is deleted.
         * @param key       The key to the data.
         * @param scope     The \e %Scope that the data is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope::Path"
         *                  to reference parent directories.
         ******************************************************************************************/
        ALOX_API
        void      storeImpl( LogData* data, const TString& key, Scope scope, int pathLevel );

        /** ****************************************************************************************
         * Internal method serving public interface #Retrieve.
         *
         * @param key       The key to the data.
         * @param scope     The \e %Scope that the data is bound to.
         * @param pathLevel Used only if parameter \p scope equals
         *                  \ref aworx::lox::Scope::Path "Scope::Path"
         *                  to reference parent directories.
         * @return The \b LogData object, \c nullptr if nothing was found.
         ******************************************************************************************/
        ALOX_API
        LogData*  retrieveImpl  ( const TString& key, Scope scope, int  pathLevel );

        /** ****************************************************************************************
         * Checks if given scope is thread-related.
         *
         * @param scope     The scope that is to be checked.
         * @return \c true if \p scope is thread-related, \c false else.
         ******************************************************************************************/
        ALOX_API
        bool      isThreadReleatedScope( Scope scope );

        /** ****************************************************************************************
         * Checks if given scope needs information that is not available.
         *
         * @param scope          The scope that is to be checked.
         * @param pathLevel      Used only if parameter \p scope equals
         *                       \ref aworx::lox::Scope::Path "Scope.Path"
         *                       to reference parent directories.
         * @param internalDomain The internal sub-domain to log any error/warning into.
         * @return \c true if all is fine, \c false else.
         ******************************************************************************************/
        ALOX_API
        bool      checkScopeInformation( Scope scope, int pathLevel, const TString& internalDomain );

        /** ****************************************************************************************
         * Used on destruction and with #Reset.
         ******************************************************************************************/
        ALOX_API
        void      clear();

        /** ****************************************************************************************
         * Reads the verbosity for the given logger and domain from ALib configuration system.
         * This internal method is used in two occasions:
         * - when a new logger is added: recursively for all existing domains (\p configStr is
         *   given)
         * - when a new domain is created on the fly(\p configStr is not given)
         *
         * @param logger      The logger to set the verbosity for.
         * @param dom         The domain to set the verbosity for.
         * @param cfgStr      The configuration string. If not read yet, nullptr may be given.
         * @param cfgPriority The priority of the configuration plug-in providing the variable.
         ******************************************************************************************/
        ALOX_API
        void      getVerbosityFromConfig( core::Logger*  logger, core::Domain*  dom,
                                          TString*       cfgStr, int            cfgPriority );

        /** ****************************************************************************************
         * Reads the verbosity for the given logger and domain from ALib configuration system.
         * This internal method is used when a new logger is added.
         * Walks recursively for all existing domains.
         *
         * @param logger      The logger to set the verbosity for.
         * @param dom         The domain to set the verbosity for.
         * @param cfgStr      The configuration string. If not read yet, nullptr may be given.
         * @param cfgPriority The priority of the configuration plug-in providing the variable.
         ******************************************************************************************/
        ALOX_API
        void      getAllVerbosities( core::Logger*  logger,   core::Domain*  dom,
                                     TString*       cfgStr,   int            cfgPriority  );

}; // class Lox

} // namespace lox

/** Type alias name in namespace #aworx. */
using     Lox=           aworx::lox::Lox;

}  // namespace aworx


#endif // HPP_ALOX_LOX
