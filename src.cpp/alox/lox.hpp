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
#ifndef HPP_ALOX_LOX
#define HPP_ALOX_LOX 1

// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_AWORX_LIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
#endif

#if !defined (HPP_ALOX_CORE_CALLERINFO)
    #include "alox/core/callerinfo.hpp"
#endif

#if !defined (HPP_ALOX_CORE_DOMAIN)
    #include "alox/core/domain.hpp"
#endif

#if !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
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
 * This class acts as a container for Loggers and provides a convenient interface into them.
 * Features are:
 *
 * - %Log into one or more Logger instances at once
 * - Manage default domain names for different scopes
 * - Store and manage caller information
 * - Store "code markers" and retrieve for simple tracing in log statements
 * - Count log operations
 *
 * Lox inherits ThreadLock. Each Lox method uses this mutex. If thread safeness is not needed
 * for the logging system (see user manual) the mutex can be switched of using
 * \ref aworx::lib::threads::ThreadLock::SetMode "ThreadLock::SetMode".
 * The goal here would be to increase logging performance. This is really a very
 * seldom case when performance is absolutely key, and it is better to be kept in safe mode.
 *
 * <b>'Loggable Objects' in <em>ALox for C++</em></b><br>
 * While other ALox implementations, like ALox for C# or ALox for Java use the 'runtime type
 * information' feature of their underlying programming language to identify any object type,
 * this is not possible in standard C++. Therefore, in ALox for C++ objects of type
 * \e void* are logged. Together with the pointer, a type information has to be provided.
 *
 * The default type '0' is the only predefined type that ALox comes with and indicates
 * \ref aworx::lib::strings::ASTerminatable "ALib TString". Due to the flexible and
 * implicit conversion of user defined string types, almost anything that is a string can be passed
 * to be logged. (For more information on string handling in ALib, see \ref aworx::lib::strings).
 *
 * The use of custom types (in combination with custom logger implementations or custom
 * \ref aworx::lox::core::textlogger::ObjectConverter "textlogger::ObjectConverter" types
 * allows to dispatch just any other data to their log destination.
 **************************************************************************************************/
class Lox     : public aworx::lib::threads::ThreadLock
{
    // #############################################################################################
    // Private/protected fields
    // #############################################################################################
    protected:

        /// The loggers. At least one logger (e.g. ConsoleLogger) needs to be created.
        std::vector<core::Logger*>   loggers;

        /// Optional default domains for a source file
        std::map<AString, AString>   defaultDomains;

        /// Code markers
        std::map<AString, void*>     markers;

        /// The resulting domain name.
        AString                      resDomain;


    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
         * A counter for the quantity of calls. The count includes logs that were suppressed by
         * disabled log rootDomain and those suppressed by the optional log condition parameter.
         * Hence, it can also be used as a condition to log only every n-th time by calling using
         * the conditional parameter of #Line(), e.g.: *Lox.Line( (Log.qtyLogCalls % n) == 0, ...*.
         */
        int                                        CntLogCalls                                   =0;

        /**
         * This is the log domain name used by this class. By manipulating this Domains log level,
         * the verbosity of ALox itself can be controlled. For example, in 'Info' level,
         * calls to #SetDomain are logged which can be helpful to determine the log
         * domains that are created by libraries and larger projects.
         */
        TString                                    InternalDomain                           ="ALOX";

        /**
         * This is the log domain name chosen when no resulting domain name could be evaluated, e.g.
         * when no domain was specified but also no default domain was set. Or when missing caller
         * information do not allow to detect the scope.
         */
        TString                                    NullDomain                               ="NULL";



        /**
         * If this is positive, an error is logged to the \ref InternalDomain "internal domain"
         * when a logging statement is executed which has no domain given and no default domain is
         * set either. The field is decremented with each warning until zero is hit.
         * Defaults to 10.
         */
        int                                        ErrIfNoDefaultDomain                        = 10;


    // has to be placed behind the tread dictionary
    protected:
        /** Information about the source code, method, thread, etc. invoking a log  call */
        core::CallerInfo                           callerInfo;

        #if defined(ALIB_FEAT_THREADS)
            /**
             *  Dictionary to translate thread ids into something maybe nicer/shorter.
             *  The dictionary has to be filled by the user of the library.
             */
            core::CallerInfo::ThreadDictionary     threadDictionary;
        #endif

    // #############################################################################################
    // Constructors/destructor
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Constructs a new, empty Lox.
         * Note: This constructor has to stay in the header. This way, the Log::InitALox call
         * receives the size of classes from the compilation unit that invokes the constructor.
         * If different compile options are set, we have a chance to detect them here.
         ******************************************************************************************/
        Lox()  : ThreadLock( lib::enums::LockMode::Recursive, lib::enums::Safeness::Safe)
               , resDomain( 32 )
        #if defined(ALIB_FEAT_THREADS)
               , callerInfo( threadDictionary )
        #endif
        {
        }

        /** ****************************************************************************************
         * Destructs a lox
         ******************************************************************************************/
        ALOX_API virtual    ~Lox();

    // #############################################################################################
    // Interface
    // #############################################################################################
    public:
        /** ***************************************************************************************
         * Sets the caller information data for the next log. In addition, the method #Acquire
         * of this class' # Ownable interface is invoked. Therefore, each invocation of this
         * methods has to be followed by an invocation of # Release().<br>
         * When using \ref GrpMacrosDebugLog, this method is by the macros internally.
         *
         * @param file  The name of the source code file that the call is placed in. Normally
                        the predefined preprocessor macro __FILE__ is passed here.
         * @param line  The line number within the source code file that the call is placed in.
                        Normally the predefined preprocessor macro __LINE__ is passed here.
         * @param func  The name of the function that the call is placed in. Normally the
                        predefined preprocessor macro __func__ (or __FUNCTION__) is passed here.
         **************************************************************************************/
        void AcquireAndSetCI( const TString& file, int line, const TString& func )
        {
             ThreadLock::Acquire();
                callerInfo.AcquireAndSet( file, line, func );
        }

        /** ****************************************************************************************
         * Acquires ownership of this object without setting caller information.
         ******************************************************************************************/
        virtual void        Acquire()
        {
             ThreadLock::Acquire();
                callerInfo.Acquire();
        }

        /** ****************************************************************************************
         * Releases ownership of this object. If #Acquire was called multiple times before, the same
         * number of calls to this method have to be performed to release ownership.
         ******************************************************************************************/
        virtual void        Release()
        {
                callerInfo.Release();
             ThreadLock::Release();
        }

        /** ****************************************************************************************
         * Resets this object. Concretely the following steps are performed:
         * - All loggers are removed
         * -
         * \note
         *   This method was introduced to support resetting the debug \b %Lox objects in the unit
         *   tests. In real applications, and for release logging it recommended to delete a Lox
         *   and create a new one instead of resetting one. But this might be wrong and resetting
         *   could be justified as well.
         ******************************************************************************************/
        ALOX_API
        void        Reset();

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
         *   [ALOX_CL_MODE](../group__GrpALoxConfigVars.html) is set. This variable's
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
         * @param name The name of the logger. Defaults to nullptr, which implies standard
         *             logger names defined in the logger sub-classes.
         *
         * @return An instance of the chosen console type logger.
         **************************************************************************************/
        ALOX_API
        static core::textlogger::TextLogger*  CreateConsoleLogger( const String& name= nullptr );

        /** ****************************************************************************************
         * Adds a logger to this container of loggers.
         * Each log call that is performed through this classes' interface
         * will be forwarded to this logger, unless filtered out with optional filter parameter.
         *
         * \note
         *   This method checks whether the domain used for internal ALox messages
         *   (see field #InternalDomain) is already registered with the given logger.
         *   Only if not, the domain is registered and set to domain level
         *   \ref aworx::lox::Log::DomainLevel::WarningsAndErrors "DomainLevel::WarningsAndErrors".
         *   This means, that it does not play a role, if changes to the level of domain "ALOX" are
         *   performed prior to adding a logger, using
         *   \ref aworx::lox::core::Logger::SetDomain "Logger::SetDomain"
         *   or after a logger was added, using
         *   \ref aworx::lox::Lox::SetDomain "Lox::SetDomain".
         *
         * @param logger  The logger to be added.
         ******************************************************************************************/
        ALOX_API
        void            AddLogger( core::Logger* logger );

        /** ****************************************************************************************
         *  Retrieve an instance of a Logger by its name.
         *
         * @param loggerName    The name of the logger to search for (case insensitive)
         * @return  The logger, nullptr if not found.
         ******************************************************************************************/
        ALOX_API
        core::Logger*   GetLogger( const String& loggerName );

        /** ****************************************************************************************
         *  Removes a logger from this container.
         *  @param logger   The logger to be removed.
         *  @returns \c true, if the logger was found and removed, \c false otherwise.
         ******************************************************************************************/
        ALOX_API
        bool            RemoveLogger( const core::Logger* logger );

        /** ****************************************************************************************
         *  Removes all loggers that match the filter name from this  interface.
         *  @param loggerFilter    (Optional) A filter for the loggers to be affected. A simple
         *                         string compare without case sensitivity is performed. An asterisk
         *                         ('*') at the beginning or end of the string is used as a
         *                         wildcard. Defaults to nullptr which causes all loggers to be
         *                         removed.
         *  @returns The number of loggers that were removed.
         ******************************************************************************************/
        ALOX_API
        int             RemoveLoggers( const String& loggerFilter= nullptr );

        /** ****************************************************************************************
         * This version of the method registers a log domain with a 'Scope'.
         * If the parameter \p scope is provided with a value not equal to Log::Scope.None, the
         * given domain becomes the default domain for respective scope. For any subsequent log
         * calls from within this scope, where no domain is explicitly given, this default domain
         * is used. If subsequent log calls specify a domain name with a leading '~' character,
         * then such domain is concatenated to the default domain to build a complete domain path.
         *
         * \note  The C++ version of ALox implements scope mechanisms using caller information
         *        generated by the preprocessor. By default, debug logging supports such caller
         *        information, release logging does not. This can be changed. For more information
         *        on how to change such defaults, see \ref ALOX_DBG_LOG_CI and \ref ALOX_REL_LOG_CI
         *        in section \ref GrpALoxCodeSelectorSymbols.
         *
         * @param domain    The domain name (and path) to register.
         *                  If this is starting  with a swung dash ('~') this is interpreted a sub
         *                  domain to a (potentially not already set) default domain of the scope.
         *                  For other values, the default domain is ignored (regardless if
         *                  this is starting with a slash or not).
         * @param scope     If a value other than Log::Scope.None is provided, the given domain
         *                  name is registered as the default domain for the given scope. Default
         *                  domains set for 'inner scopes' have higher priority than those set for
         *                  outer scopes.<br>
         *                  Available Scope definitions are platform/language dependent.
         *
         ******************************************************************************************/
        ALOX_API
        void        SetDomain( const TString& domain, Log::Scope scope=  Log::Scope::None );


        /** ****************************************************************************************
         * Sets the domain log level and (by default) all it's sub domains recursively. In the case
         * that sub domains should be set to a different log level, then this function has to be
         * called for such sub domains after the call to the parent domain (or recursion has to be
         * switched off, using the parameter 'recursive'). It is not necessary to register a domain
         * before setting its log level and log levels can be set and modified any time.
         *
         * @param domain       If this is nullptr, the default domain is used. If this is
         *                     starting with a swung dash ('~') this is interpreted a sub domain
         *                     to the default domain of the scope. For other values, the
         *                     default domain is ignored (regardless if this is starting with a
         *                     slash or not).
         * @param domainLevel  The domains log level to be set.
         * @param loggerFilter (Optional) A filter for the loggers to be affected. This
         *                     parameter enables different loggers to have different domains and
         *                     log levels. A simple string compare without case sensitivity is
         *                     performed. An asterisk ('*') at the beginning or end of the
         *                     string is used as a wildcard. Leave to \e nullptr if all loggers
         *                     should be affected. Use this parameter only in more complex logging
         *                     scenarios.
         * @param propagation  (Optional) If \c Propagation::ToDescendants, which is the default,
         *                     the level is set for all sub-domains recursively.
         *                     If \c Propagation::None, then only this domain is changed.
         ******************************************************************************************/
        ALOX_API
        void        SetDomain( const TString&           domain,
                               Log::DomainLevel         domainLevel,
                               const String&            loggerFilter=   nullptr,
                               lib::enums::Propagation  propagation=    lib::enums::Propagation::ToDescendants );

        /** ****************************************************************************************
         * Invokes methods
         * \ref SetDomain(const TString&, Log::Scope) "SetDomain(domain, scope)"  and
         * \ref SetDomain(const TString&, Log::Scope) "SetDomain(domain, domainLevel)".<br>
         * Optional parameter \p loggerFilter applies only to the domain level setting.
         *
         * @param domain      The domain name (and path) to register.
         *                    If this is starting  with a swung dash ('~') this is interpreted a sub
         *                    domain to a (potentially not already set) default domain of the scope.
         *                    For other values, the default domain is ignored (regardless if
         *                    this is starting with a slash or not).
         * @param scope       If a value other than Log::Scope.None is provided, the given domain
         *                    name is registered as the default domain for the given scope. Default
         *                    domains set for 'inner scopes' have higher priority than those set for
         *                    outer scopes.<br>
         *                    Available Scope definitions are platform/language dependent.
         * @param domainLevel The domains log level to be set.
         * @param loggerFilter (Optional) A filter for the loggers to be affected. This
         *                     parameter enables different loggers to have different domains and
         *                     log levels. A simple string compare without case sensitivity is
         *                     performed. An asterisk ('*') at the beginning or end of the
         *                     string is used as a wildcard. Leave to \e nullptr if all loggers
         *                     should be affected. Use this parameter only in more complex logging
         *                     scenarios.
         ******************************************************************************************/
        inline
        void        SetDomain( const TString& domain,        Log::Scope      scope,
                               Log::DomainLevel domainLevel, const String&   loggerFilter =nullptr)
        {
            SetDomain( domain, scope );
            SetDomain( domain, domainLevel, loggerFilter );
        }

        /** ****************************************************************************************
         * Invokes methods
         * \ref SetDomain(const TString&, Log::Scope) "SetDomain(domain, scope)"  and
         * \ref SetDomain(const TString&, Log::Scope) "SetDomain(domain, domainLevel)".
         *
         * @param scope       If a value other than Log::Scope.None is provided, the given domain
         *                    name is registered as the default domain for the given scope. Default
         *                    domains set for 'inner scopes' have higher priority than those set for
         *                    outer scopes.<br>
         *                    Available Scope definitions are platform/language dependent.
         * @param domain      The domain name (and path) to register.
         *                    If this is starting  with a swung dash ('~') this is interpreted a sub
         *                    domain to a (potentially not already set) default domain of the scope.
         *                    For other values, the default domain is ignored (regardless if
         *                    this is starting with a slash or not).
         * @param domainLevel The domains log level to be set.
         ******************************************************************************************/
        inline
        void        SetDomain( const TString& domain, Log::DomainLevel domainLevel,
                               Log::Scope      scope )
        {
            SetDomain( domain, scope );
            SetDomain( domain, domainLevel );
        }


        /** ****************************************************************************************
         * This method is used to disable (and enable again) one or more loggers completely without
         * touching the log levels of the domains and hence without the need to restore such log
         * levels later.
         *
         * @param newState      If \c Switch::Off, the logger(s) will be completely disabled,
         *                      if \c Switch::On, the normal, domain specific log levels will
         *                      be applied for log  decisions.
         * @param loggerFilter  A filter for the loggers to be affected. A simple string compare
         *                      (case insensitiv) is performed. An asterisk ('*') at the beginning
         *                      or end of the string can be used for 'globbing'.
         *                      If \e nullptr, all loggers will be switched.
         ******************************************************************************************/
        ALOX_API
        void        SetLogger( lib::enums::Switch newState, const String& loggerFilter );

        /** ****************************************************************************************
         *  This method is used reset (or to explicitly set) the start time of the logger(s).
         *  The only impact is the output of time differences in the log lines. Hence, this method
         *  is useful to reset them and see some absolute time values when doing basic performance
         *  tests using the logger.
         *
         * @param startTime       (Optional) Optional parameter with the  new start time. Defaults
         *                        to DateTime.Now if omitted.
         * @param loggerFilter    (Optional) A filter for the loggers to be affected. A simple
         *                        string compare without case sensitivity is performed. An asterisk
         *                        ('*') at the beginning or end of the string is used as a
         *                         wildcard. Leave to \e nullptr if all loggers should be affected.
         ******************************************************************************************/
        ALOX_API
        void SetStartTime( lib::time::Ticks  startTime           = lib::time::Ticks(0),
                           const String&     loggerFilter        = nullptr );

        #if defined (__GLIBCXX__)
        /** ****************************************************************************************
         *  This method is used reset (or to explicitly set) the start time of the logger(s).
         *  The only impact is the output of time differences in the log lines. Hence, it is useful
         *  to see some absolute time values when doing basic performance tests using the logger.
         *  \note  GLib specific.
         *
         * @param startTime       The new start time in system specific time unit.
         * @param loggerFilter    (Optional) A filter for the loggers to be affected. A simple
         *                        string compare without case sensitivity is performed. An asterisk
         *                        ('*') at the beginning or end of the string is used as a
         *                        wildcard. Leave to \e nullptr if all loggers should be affected.
         ******************************************************************************************/
            ALOX_API
            void SetStartTime( time_t startTime, const String& loggerFilter= nullptr );


        #endif // no elif here, otherwise doxygen would ignore it!

        #if defined( _MSC_VER )
        /** ****************************************************************************************
         *  This method is used reset (or to explicitly set) the start time of the logger(s).
         *  The only impact is the output of time differences in the log lines. Hence, it is useful
         *  to see some absolute time values when doing basic performance tests using the logger.
         *  \note  Microsoft Windows specific.
         * @param startTime       The new start time in system specific time unit.
         * @param loggerFilter    (Optional) A filter for the loggers to be affected. A simple
         *                        string compare without case sensitivity is performed. An asterisk
         *                        ('*') at the beginning or end of the string is used as a
         *                        wildcard. Leave to \e nullptr if all loggers should be affected.
         ******************************************************************************************/
            ALOX_API
            void        SetStartTime( LPFILETIME startTime, const String& loggerFilter= nullptr );

        #endif

        /** ****************************************************************************************
         *  This method sets a human readable name to the given thread ID (or current thread) which
         *  is optionally included in each log line.
         *
         * @param threadName    The name of the thread as it should be displayed in the logs
         * @param id            (Optional) Parameter providing the thread ID. If omitted, the
         *                      current thread's ID is used.
         ******************************************************************************************/
        ALOX_API
        void        MapThreadName( const String& threadName, int id= 0 );

        /** ****************************************************************************************
         *  This method is used store a marker object in the logging system. Markers are stored
         *  and retrieved relative to a given Log::Scope. In combination with Lox.GetMarker,
         *  this method provides an easy way to trace the last marked position, e.g. in the case of
         *  an exception. Within the exception handler, use Lox.GetMarker to retrieve the last marker
         *  object stored before the exception was thrown.
         *
         *  \note  The code marker facility of ALox was designed primarily to support debugging
         *         of an application by the analysis of log files.<br>
         *         The C++ version of ALox implements scope mechanisms using caller information
         *         generated by the preprocessor. By default, debug logging supports such caller
         *         information, release logging does not. This can be changed. For more information
         *         on how to change such defaults, see \ref ALOX_DBG_LOG_CI and \ref ALOX_REL_LOG_CI
         *         in section \ref GrpALoxCodeSelectorSymbols.<br>
         *
         * @param marker The object to store, for example a std::string* that can be used for a
         *               log output later.
         * @param scope  The scope in which the marker should be stored. Markers and scopes
         *               work independently from each other. Different markers can be stored
         *               within different scopes and no fallback to "outer scopes" is made.
         *               A scope of 'None' stores the marker globally, hence as a system wide
         *               singleton.
         ******************************************************************************************/
        ALOX_API
        void        SetMarker( void* marker, Log::Scope scope );

        /** ****************************************************************************************
         *  Retrieves the most recently marker object stored using Lox.SetMarker. Markers are stored
         *  and retrieved relative to a given Log::Scope. In combination with Lox.SetMarker,
         *  this method provides an easy way to trace the last marked position, e.g. in the case of
         *  an exception. Within the exception handler, use this method to retrieve the last marker
         *  object stored before the exception was thrown.
         *
         *  \note  The code marker facility of ALox was designed primarily to support debugging
         *         of an application by the analysis of log files.<br>
         *         The C++ version of ALox implements scope mechanisms using caller information
         *         generated by the preprocessor. By default, debug logging supports such caller
         *         information, release logging does not. This can be changed. For more information
         *         on how to change such defaults, see \ref ALOX_DBG_LOG_CI and \ref ALOX_REL_LOG_CI
         *         in section \ref GrpALoxCodeSelectorSymbols.
         *
         * @param scope  The scope in which the marker should be stored. Markers and scopes work
         *               independently from each other. Different markers can be stored within
         *               different scopes and no fallback to "outer scopes" is made. A scope of
         *               'None' retrieves the global marker singleton.
         * @returns The marker object, null if not found.
         ******************************************************************************************/
        ALOX_API
        void*       GetMarker( Log::Scope scope );

        /** ****************************************************************************************
         *  This method logs the configuration this Lox and it's encapsulated objects.
         *
         * @param domain        If this is nullptr, the default domain is used. If this is starting
         *                      with a swung dash ('~') this is interpreted a sub domain to the
         *                      default domain of the scope. For other values, the default
         *                      domain is ignored (regardless if this is starting with a slash or
         *                      not).
         * @param level         The log level.
         * @param headLine      If given, a separated headline will be logged at first place.
         * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
         *                      parameter enables different loggers to have different domains. A
         *                      simple string compare without case sensitivity is performed. An
         *                      asterisk ('*') at the beginning or end of the string is used as a
         *                      wildcard. Leave to \e nullptr if all loggers should be affected. Use this
         *                      parameter only in more complex logging scenarios.
         ******************************************************************************************/
        ALOX_API
        void        LogConfig( const String&       domain,
                               Log::Level          level,
                               const String&       headLine,
                               const String&       loggerFilter= nullptr );


    // #############################################################################################
    // Main logging methods
    // #############################################################################################

        /** ****************************************************************************************
         * Logs a string with log level equal to
         * \ref Log::Level::Verbose "Level::Verbose".
         * This is the most verbose log level, which is only actually logged if the log domains'
         * log level is set to
         * \ref Log::DomainLevel::All "DomainLevel::All".
         *
         * This overloaded version does not offer a domain parameter but relies on a
         * default domain set for the scope.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Verbose(                     const TString& msg,   int indent= 0 )
        {
            Line(  true, nullptr, Log::Level::Verbose, &msg, 0, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs a string with log level equal to
         * \ref Log::Level::Verbose "Level::Verbose".
         * This is the most verbose log level, which is only actually logged if the log domains'
         * log level is set to
         * \ref Log::DomainLevel::All "DomainLevel::All".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Verbose( const TString& domain, const TString& msg,   int indent= 0 )
        {
             Line( true, domain, Log::Level::Verbose, &msg, 0, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs arbitrary objects with log level equal to
         * \ref Log::Level::Verbose "Level::Verbose".
         * This is the most verbose log level, which is only actually logged if the log domains'
         * log level is set to
         * \ref Log::DomainLevel::All "DomainLevel::All".
         *
         * The object \p msgObject of given type \p msgType  has to be interpreted by the (custom)
         * Logger(s) attached to this \b %Lox.
         *
         * This overloaded version does not offer a domain parameter but relies on a
         * default domain set for the scope.
         *
         * @param msgObject Pointer to the object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Verbose( void* msgObject, int msgType,   int indent= 0 )
        {
            (void) msgObject;
            (void) msgType;
            Line(  true, nullptr, Log::Level::Verbose, msgObject, msgType, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs arbitrary objects with log level equal to
         * \ref Log::Level::Verbose "Level::Verbose".
         * This is the most verbose log level, which is only actually logged if the log domains'
         * log level is set to
         * \ref Log::DomainLevel::All "DomainLevel::All".
         *
         * The object \p msgObject of given type \p msgType  has to be interpreted by the (custom)
         * Logger(s) attached to this \b %Lox.
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msgObject Pointer to the object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Verbose( const TString& domain, void* msgObject, int msgType,   int indent= 0 )
        {
             Line( true, domain, Log::Level::Verbose, msgObject, msgType, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs a string with log level equal to
         * \ref Log::Level::Info "Level::Info".
         * The log operation is only executed if the resulting log domains' log level is set to
         * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel::InfoWarningsAndErrors" or
         * \ref Log::DomainLevel::All                   "DomainLevel::All".
         *
         * This overloaded version does not offer a domain parameter but relies on a
         * default domain set for the scope.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Info( const TString& msg,   int indent= 0 )
        {
            Line( true,  nullptr, Log::Level::Info, &msg, 0, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs a string with log level equal to
         * \ref Log::Level::Info "Level::Info".
         * The log operation is only executed if the resulting log domains' log level is set to
         * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel::InfoWarningsAndErrors" or
         * \ref Log::DomainLevel::All                   "DomainLevel::All".<br>
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Info( const TString&  domain,   const TString& msg,   int indent= 0 )
        {
            Line( true, domain, Log::Level::Info, &msg, 0, indent, nullptr );
        }


        /** ****************************************************************************************
         * Logs an arbitrary object with log level equal to
         * \ref Log::Level::Info "Level::Info".
         * The log operation is only executed if the resulting log domains' log level is set to
         * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel::InfoWarningsAndErrors" or
         * \ref Log::DomainLevel::All                   "DomainLevel::All".
         *
         * The object \p msgObject of given type \p msgType  has to be interpreted by the (custom)
         * Logger(s) attached to this \b %Lox.
         *
         * This overloaded version does not offer a domain parameter but relies on a
         * default domain set for the scope.
         *
         * @param msgObject Pointer to the object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Info( void* msgObject, int msgType,   int indent= 0 )
        {
            Line( true,  nullptr, Log::Level::Info, msgObject, msgType, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs an arbitrary object with log level equal to
         * \ref Log::Level::Info "Level::Info".
         * The log operation is only executed if the resulting log domains' log level is set to
         * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel::InfoWarningsAndErrors" or
         * \ref Log::DomainLevel::All                   "DomainLevel::All".
         *
         * The object \p msgObject of given type \p msgType  has to be interpreted by the (custom)
         * Logger(s) attached to this \b %Lox.
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msgObject Pointer to the object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Info( const TString&  domain, void* msgObject, int msgType, int indent= 0 )
        {
            Line( true, domain, Log::Level::Info, msgObject, msgType, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs a string with log level equal to
         * \ref Log::Level::Warning "Level::Warning".
         * This log level is enabled if the log domains' log level is set to
         * \ref Log::DomainLevel::All                   "DomainLevel::All",
         * \ref Log::DomainLevel::WarningsAndErrors     "DomainLevel::WarningsAndErrors" or
         * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel::InfoWarningsAndErrors".
         *
         * This overloaded version does not offer a domain parameter but relies on a
         * default domain set for the scope.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Warning( const TString& msg,   int indent= 0 )
        {
            Line( true, nullptr, Log::Level::Warning, &msg, 0, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs a string with log level equal to
         * \ref Log::Level::Warning "Level::Warning".
         * This log level is enabled if the log domains' log level is set to
         * \ref Log::DomainLevel::All                   "DomainLevel::All",
         * \ref Log::DomainLevel::WarningsAndErrors     "DomainLevel::WarningsAndErrors" or
         * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel::InfoWarningsAndErrors".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Warning( const TString& domain, const TString& msg,   int indent= 0 )
        {
            Line( true, domain, Log::Level::Warning, &msg, 0, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs an arbitrary object with log level equal to
         * \ref Log::Level::Warning "Level::Warning".
         * This log level is enabled if the log domains' log level is set to
         * \ref Log::DomainLevel::All                   "DomainLevel::All",
         * \ref Log::DomainLevel::WarningsAndErrors     "DomainLevel::WarningsAndErrors" or
         * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel::InfoWarningsAndErrors".
         *
         * The object \p msgObject of given type \p msgType  has to be interpreted by the (custom)
         * Logger(s) attached to this \b %Lox.
         *
         * This overloaded version does not offer a domain parameter but relies on a
         * default domain set for the scope.
         *
         * @param msgObject Pointer to the object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Warning( void* msgObject, int msgType, int indent= 0 )
        {
            Line( true, nullptr, Log::Level::Warning, msgObject, msgType, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs an arbitrary object with log level equal to
         * \ref Log::Level::Warning "Level::Warning".
         * This log level is enabled if the log domains' log level is set to
         * \ref Log::DomainLevel::All                   "DomainLevel::All",
         * \ref Log::DomainLevel::WarningsAndErrors     "DomainLevel::WarningsAndErrors" or
         * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel::InfoWarningsAndErrors".
         *
         * The object \p msgObject of given type \p msgType  has to be interpreted by the (custom)
         * Logger(s) attached to this \b %Lox.
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msgObject Pointer to the object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Warning( const TString& domain, void* msgObject, int msgType,   int indent= 0 )
        {
            Line( true, domain, Log::Level::Warning, msgObject, msgType, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs a string with log level equal to
         * \ref Log::Level::Error "Level::Error".
         * This log level is always enabled, unless the log domains' log level is set to
         * \ref Log::DomainLevel::Off                   "DomainLevel::Off".
         *
         * This overloaded version does not offer a domain parameter but relies on a
         * default domain set for the scope.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Error( const TString& msg,   int indent= 0 )
        {
            Line( true, nullptr, Log::Level::Error, &msg, 0, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs a string with log level equal to
         * \ref Log::Level::Error "Level::Error".
         * This log level is always enabled, unless the log domains' log level is set to
         * \ref Log::DomainLevel::Off                   "DomainLevel::Off".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Error( const TString& domain,   const TString& msg,   int indent= 0 )
        {
            Line( true, domain, Log::Level::Error, &msg, 0, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs an arbitrary object with log level equal to
         * \ref Log::Level::Error "Level::Error".
         * This log level is always enabled, unless the log domains' log level is set to
         * \ref Log::DomainLevel::Off                   "DomainLevel::Off".
         *
         * The object \p msgObject of given type \p msgType  has to be interpreted by the (custom)
         * Logger(s) attached to this \b %Lox.
         *
         * This overloaded version does not offer a domain parameter but relies on a
         * default domain set for the scope.
         *
         * @param msgObject Pointer to the object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Error( void* msgObject, int msgType,   int indent= 0 )
        {
            Line( true, nullptr, Log::Level::Error, msgObject, msgType, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs an arbitrary object with log level equal to
         * \ref Log::Level::Error "Level::Error".
         * This log level is always enabled, unless the log domains' log level is set to
         * \ref Log::DomainLevel::Off                   "DomainLevel::Off".
         *
         * The object \p msgObject of given type \p msgType  has to be interpreted by the (custom)
         * Logger(s) attached to this \b %Lox.
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msgObject Pointer to the object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Error( const TString& domain,  void* msgObject, int msgType,   int indent= 0 )
        {
            Line( true, domain, Log::Level::Error, msgObject, msgType, indent, nullptr );
        }


        /** ****************************************************************************************
         * Logs a string only if the given condition \p cond is not \e 'true'.
         * Log level will be highest, namely
         * \ref Log::Level::Error "Level::Error".
         *
         * This overloaded version does not offer a domain parameter but relies on a
         * default domain set for the scope.
         *
         * @param cond      The log is only performed if condition is not \c true.
         * @param msg       The string to be logged.
         * @param indent    (Optional) the indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Assert( bool cond, const TString& msg,  int indent= 0 )
        {
            Line( !cond, nullptr, Log::Level::Error, &msg, 0, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs a string only if the given condition \p cond is not \e 'true'.
         * Log level will be highest, namely
         * \ref Log::Level::Error "Level::Error".
         *
         * @param cond      The log is only performed if condition is not \c true.
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default
         *                  domain of the scope. For other values, the default domain is
         *                  ignored (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) the indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Assert( bool cond, const TString& domain, const TString& msg,  int indent= 0 )
        {
            Line( !cond, domain, Log::Level::Error, &msg, 0, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs an arbitrary object only if the given condition \p cond is not \e 'true'.
         * Log level will be highest, namely
         * \ref Log::Level::Error "Level::Error".
         *
         * The object \p msgObject of given type \p msgType  has to be interpreted by the (custom)
         * Logger(s) attached to this \b %Lox.
         *
         * This overloaded version does not offer a domain parameter but relies on a
         * default domain set for the scope.
         *
         * @param cond      The log is only performed if condition is not \c true.
         * @param msgObject Pointer to the object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    (Optional) the indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Assert( bool cond, void* msgObject, int msgType,  int indent= 0 )
        {
            Line( !cond, nullptr, Log::Level::Error, msgObject, msgType, indent, nullptr );
        }

        /** ****************************************************************************************
         * Logs an arbitrary object only if the given condition \p cond is not \e 'true'.
         * Log level will be highest, namely
         * \ref Log::Level::Error "Level::Error".
         *
         * The object \p msgObject of given type \p msgType  has to be interpreted by the (custom)
         * Logger(s) attached to this \b %Lox.
         *
         * @param cond      The log is only performed if condition is not \c true.
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default
         *                  domain of the scope. For other values, the default domain is
         *                  ignored (regardless if this is starting with a slash or not).
         * @param msgObject Pointer to the object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    (Optional) the indentation in the output. Defaults to 0.
         ******************************************************************************************/
        inline
        void Assert( bool cond, const TString& domain, void* msgObject, int msgType, int indent= 0 )
        {
            Line( !cond, domain, Log::Level::Error, msgObject, msgType, indent, nullptr );
        }


        // #############################################################################################
        // Line() methods
        // #############################################################################################

        /** ****************************************************************************************
         *  Provides the most flexible but complex way to log an arbitrary object.
         *  The methods #Verbose, #Info, #Warning, #Error and #Assert() are 'shortcuts' to this
         *  function and are more convenient to use.
         *  Use this method only in the rare cases, e.g. when a log level is decided only at runtime.
         *
         * @param doLog         Conditional logging. If \c false, the log is not performed. CntLogCalls
         *                      is still increased by one.
         * @param domain        If this is nullptr, the default domain is used. If this is starting
         *                      with a swung dash ('~') this is interpreted a sub domain to the
         *                      default domain of the scope. For other values, the default
         *                      domain is ignored (regardless if this is starting with a slash or
         *                      not).
         * @param level         The log level.
         * @param msgObject     The object to log.
         * @param msgType       Type information on the object to log.
         * @param indent        (Optional) The indentation in the output. Defaults to 0.
         * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
         *                      parameter enables different loggers to have different domains. A
         *                      simple string compare without case sensitivity is performed. An
         *                      asterisk ('*') at the beginning or end of the string is used as a
         *                      wildcard. Leave to \e nullptr if all loggers should be affected. Use this
         *                      parameter only in more complex logging scenarios.
         ******************************************************************************************/
        ALOX_API
        void Line(  bool              doLog,
                    const TString&    domain,
                    Log::Level        level,
                    const void*       msgObject,
                    int               msgType ,
                    int               indent= 0,
                    const String&     loggerFilter= nullptr );

        /** ****************************************************************************************
         *  Logs an arbitrary object using the given log level, log domain, indentation and
         *  logger filter.
         *  See \ref Line(bool, const TString&, Log::Level, const void*, int, int, const String&) "Line"
         *  for a version of this method that supports the maximum number of parameters.
         *
         * @param domain        If this is nullptr, the default domain is used. If this is starting
         *                      with a swung dash ('~') this is interpreted a sub domain to the
         *                      default domain of the scope. For other values, the default
         *                      domain is ignored (regardless if this is starting with a slash or
         *                      not).
         * @param level         The log level.
         * @param msgObject     The object to log.
         * @param msgType       Type information on the object to log.
         * @param indent        (Optional) The indentation in the output. Defaults to 0.
         * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
         *                      parameter enables different loggers to have different domains. A
         *                      simple string compare without case sensitivity is performed. An
         *                      asterisk ('*') at the beginning or end of the string is used as a
         *                      wildcard. Leave to \e nullptr if all loggers should be affected. Use this
         *                      parameter only in more complex logging scenarios.
         ******************************************************************************************/
        inline
        void Line(                           const TString& domain,         Log::Level level,
                    const void* msgObject,   int            msgType ,
                    int         indent= 0,   const String&  loggerFilter= nullptr )
        {
            Line( true, domain, level, msgObject, msgType , indent, loggerFilter );
        }

        /** ****************************************************************************************
         *  Logs an arbitrary object using the given log level, indentation and logger filter
         *  using the default domain set for the scope.
         *  See \ref Line(bool, const TString&, Log::Level, const void*, int, int, const String&) "Line"
         *  for a version of this method that supports the maximum number of parameters.
         *
         * @param level         The log level.
         * @param msgObject     The object to log.
         * @param msgType       Type information on the object to log.
         * @param indent        (Optional) The indentation in the output. Defaults to 0.
         * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
         *                      parameter enables different loggers to have different domains. A
         *                      simple string compare without case sensitivity is performed. An
         *                      asterisk ('*') at the beginning or end of the string is used as a
         *                      wildcard. Leave to \e nullptr if all loggers should be affected. Use this
         *                      parameter only in more complex logging scenarios.
         ******************************************************************************************/
        inline
        void Line(                                                            Log::Level level,
                    const void* msgObject,  int             msgType ,
                    int         indent= 0,  const String&   loggerFilter= nullptr )
        {
            Line( true, nullptr, level, msgObject, msgType , indent, loggerFilter );
        }

    // #############################################################################################
    // internals
    // #############################################################################################
    protected:

        /** ****************************************************************************************
         *  Using the optionally provided domain and a default domain previously set according to
         *  the caller's scope. The resulting full domain string is evaluated as follows:
         *  If no domain given, the default domain is retrieved (depending on the caller's scope).
         *  If a domain is given it is used. If it is starting with a swung dash("~"), it is interpreted
         *  to be a sub domain of the default domain and both domains are concatenated.
         *
         * @param domain  A domain or path. If starting with a swung dash ('~') it is interpreted as
         *                being a sub domain of the default domain defined for the current caller's scope.
         ******************************************************************************************/
        ALOX_API
        void            evaluateResultDomain( const TString& domain  );

        /** ****************************************************************************************
         *  Logs an internal error message to the domain given by field InternalDomain. Attn: must only
         *  be called after saveAndSet() was performed.
         *
         * @param level  The log level.
         * @param msg    The message.
         ******************************************************************************************/
        ALOX_API
        void            internalLog( Log::Level level, const TString& msg );

        /** ****************************************************************************************
         *  Compares a loggers name with a filter string with simplest wildcard support ('*') at the
         *  beginning or end of the string. If loggerFilter is nullptr, a match is indicated.
         *
         * @param logger          The logger to be filtered.
         * @param loggerFilter    The filter.
         * @return \c true if logger is not filtered out.
         ******************************************************************************************/
        ALOX_API
        static bool     simpleWildcardFilter( core::Logger* logger, const String& loggerFilter );

        /** ****************************************************************************************
         *  Internal method used by LogConfig() to recursively log Domain instances.
         * @param domain     The Domain instance to log out.
         * @param indent     The indentation in the output, recursively increased.
         * @param domPath    Actual path relative to recursion, solely for log output.
         * @param buffer     The buffer to log to.
         ******************************************************************************************/
        ALOX_API
        void            logConfigDomainRecursive( core::Domain& domain, int indent, AString& domPath, AString& buffer );

}; // class Lox
}} // namespace



#endif // HPP_ALOX_LOX
