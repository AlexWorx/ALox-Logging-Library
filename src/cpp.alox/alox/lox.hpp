// #################################################################################################
//  aworx::lox - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// include ALox main header first...
#if !defined (HPP_AWORX_ALOX_ALOX)
    #error "lox.hpp must not be included manually. Include alox.hpp instead."
#endif

// then, set include guard
#ifndef HPP_AWORX_ALOX_LOX
#define HPP_AWORX_ALOX_LOX 1


// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_AWORX_UTIL_ASTRING)
    #include "astring.hpp"
#endif

#if !defined (HPP_AWORX_UTIL_THREADLOCK)
    #include "threadlock.hpp"
#endif

#if !defined (HPP_AWORX_ALOX_CALLERINFO)
    #include "core/callerinfo.hpp"
#endif

#if !defined (HPP_AWORX_ALOX_LOGDOMAIN)
    #include "core/logdomain.hpp"
#endif


#if !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
#endif

#if !defined (_GLIBCXX_MAP) && !defined(_MAP_)
    #include <map>
#endif



namespace aworx {
namespace       lox {

namespace core { class Logger; }

/** ************************************************************************************************
 *  This class acts as a container for Loggers and provides a convenient interface into them.
 *  Features are:
 *
 *  a) Store and log into one or several Logger instances at once
 *  b) Manage default domain names for different scopes
 *  d) Store and manage caller information
 *  e) Store "code markers" and retrieve for simple tracing in log statements
 *  d) Provide shortcut methods to log strings.
 *  f) Count log operations
 *
 *  Lox inherits ThreadLock. Each Lox method uses this mutex. If thread safeness is not needed
 *  for the logging system (see user manual) the mutex can be switched of using SetUnsafe() inherited
 *  by ThreadLock. The goal here would be to increase logging performance. This is really a very
 *  seldom case when performance is absolutely key, and it is better to be kept in safe mode.
 **************************************************************************************************/
class Lox : public aworx::util::ThreadLock
{
    /**
     *  A utility value. Has to be first in the class. Will be initialized prior to any other
     *  field. Initializer uses insensitive. For more info see # Log::InitALox()
     */
    private:    bool _apiInitializer;

    // #############################################################################################
    // Private/protected fields
    // #############################################################################################
    protected:

        /// The loggers. At least one logger (e.g. ConsoleLogger) needs to be created.
        std::vector<core::Logger*>                  loggers;

        /// Optional default domains for a source file
        std::map<util::AString, util::AString16>    defaultDomains;

        /// Code markers
        std::map<util::AString, void*>              markers;

        /// The resulting domain name.
        util::AString                               resDomain;

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:

        /**     The version of ALox.  */
        static  const char                          Version[];

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
         *  A counter for the quantity of calls. The count includes logs that were suppressed by disabled
         *  log rootDomain and those suppressed by the optional log condition parameter. Hence, it can
         *  also be used as a condition to log only every n-th time by calling using the conditional parameter
         *  of #Line(), e.g.: *Lox.Line( (Log.qtyLogCalls % n) == 0, ...*.
         *
         */
        int                                         CntLogCalls                             =0;

        /**
         *  This is the log domain name used by this class. By manipulating this Domains log level, the
         *  verbosity of this interface class can be controlled. For example, in 'Info' level, calls to
         *  #RegDomain and #SetDomain are logged which can be helpful to determine the log
         *  domains that are created by libraries and larger projects.
         */
        const char*                                 InternalDomain                          ="ALOX";

    // has to be placed behind the tread dictionary
    protected:
        /** Information about the source code, method, thread, etc. invoking a log  call */
        core::CallerInfo                            callerInfo;

        #if defined(AWXU_FEAT_THREADS)
            /**
             *  Dictionary to translate thread ids into something maybe nicer/shorter. The dictionary has to
             *  be filled by the user of the library.
             */
            std::map<int, std::string>              ThreadDictionary;
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
        Lox()  : ThreadLock( true, true)
               , _apiInitializer(Log::InitALox( ALOX_COMPILED_CLASS_SIZE_VERIFYER ))
               , resDomain( 32 )
        #if defined(AWXU_FEAT_THREADS)
               , callerInfo( ThreadDictionary )
        #endif
        {
            // we do this here instead of in the constructor's initializer list, to be able to
            // first initialize ALox/AWXU
            SetUnsafe( false);
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
        void AcquireAndSetCI( const char* file, int line, const char* func )
        {
             ThreadLock::Acquire(); callerInfo.SetSourceInfo( file, line, func );
        }

        /** ****************************************************************************************
         *  Adds a logger to the Log interface. Each log call that is performed through this
         *  interface will be forwarded to this logger, unless filtered out with optional filter
         *  parameter. The logger will then check it's domain level against the given log level to
         *  decide whether a log should performed.
         *
         * @param logger                 The logger to be added.
         * @param internalDomainLevel    (Optional) The desired domain level for the #InternalDomain
         *                               which is used for logging code of class Lox itself. For
         *                               console loggers this can be set to **All**, for log streams
         *                               dedicated to a certain domain, this should be set to
         '                               <em>OFF</em>.
         ******************************************************************************************/
        ALOX_API
        void            AddLogger(  core::Logger* logger,
                                    Log::DomainLevel internalDomainLevel= Log::DomainLevel::WARNINGS_AND_ERRORS );


        /** ****************************************************************************************
         *  Retrieve an instance of a Logger by its name.
         *
         * @param loggerName    The name of the logger to search for (case insensitive)
         * @return  The logger, nullptr if not found.
         ******************************************************************************************/
        ALOX_API
        core::Logger*   GetLogger( const char* loggerName );

        /** ****************************************************************************************
         *  Removes a logger from this container.
         *  @param logger   The logger to be removed.
         *  @returns True, if the logger was found and removed, false otherwise.
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
        int             RemoveLoggers( const char* loggerFilter= nullptr );

        /** ****************************************************************************************
         *  This method is used to define a log domain. The method is usually invoked within the
         *  same source "context" (aka, class, namespace, package, etc.) that later on uses the
         *  domain to perform log statements. Often, calls to this functions are placed in static
         *  constructors or similar code that is executed only once and very early in the life-cycle
         *  of a process.
         *
         *  Each log statement refers to such a domain which can be used specifically for different
         *  parts of your application like assemblies, libraries, namespaces, specific code files or
         *  even for a single method. The domain name should be short, pregnant and self explaining.
         *
         *  Domains can be created with path separators '/', for example 'COMM/SOCK' could be the
         *  domain in a socket class, residing within a communication library.
         *  The advantage of creating paths and this way "sub domains", is that a whole bunch of
         *  logging domains can be altered (on/off) by just altering the root domain.
         *
         *  If a domain and path is given that is not known already, then the whole path of domains
         *  is created.
         *
         *  If the parameter **scope** is provided with a value not equal to Log::Scope.None, the
         *  given domain becomes the default domain for respective scope. For any subsequent log
         *  calls from within this scope, where no domain is explicitly given, this default domain
         *  is used. If subsequent log calls specify a domain name with a leading '~' character,
         *  then such domain is concatenated to the default domain to build a complete domain path.
         *
         *  \note  The C++ version of ALox implements scope mechanisms using caller information
         *         generated by the preprocessor. By default, debug logging supports such caller
         *         information, release logging does not. This can be changed. For more information
         *         on how to change such defaults, see \ref ALOX_DBG_LOG_CI and \ref ALOX_REL_LOG_CI
         *         in section \ref GrpALoxCodeSelectorSymbols.
         *
         * @param domain    The domain name (and path) to register.
         *                  If this is starting    with a swung dash ('~') this is interpreted a sub
         *                  domain to a (potentially already set!) default domain of the source
         *                  file. For other values, the default domain is ignored (regardless if
         *                  this is starting with a slash or not).
         * @param scope     If a value other than Log::Scope.None is provided, the given domain
         *                  name is registered as the default domain for the given scope. Default
         *                  domains set for 'inner scopes' have higher priority than those set for
         *                  outer scopes.<br>
         *                  Available Scope definitions are platform/language dependent.
         *
         ******************************************************************************************/
        ALOX_API
        void        RegDomain( const char* domain, Log::Scope scope=  Log::Scope::NONE );


        /** ****************************************************************************************
         *  Sets the domain log level and (by default) all it's sub domains recursively. In the case
         *  that sub domains should be set to a different log level, then this function has to be
         *  called for such sub domains after the call to the parent domain (or recursion has to be
         *  switched off, using the parameter 'recursive'). It is not necessary to register a domain
         *  before setting its log level and log levels can be set and modified any time.
         *
         * @param domain          If this is nullptr, the default domain is used. If this is
         *                        starting with a swung dash ('~') this is interpreted a sub domain
         *                        to the default domain of the source file. For other values, the
         *                        default domain is ignored (regardless if this is starting with a
         *                        slash or not).
         * @param domainLevel     The domains log level to be set.
         * @param recursive       (Optional) Set sub domains recursively. Defaults to true.
         * @param loggerFilter    (Optional) A filter for the loggers to be affected. This
         *                        parameter enables different loggers to have different domains and
         *                        log levels. A simple string compare without case sensitivity is
         *                        performed. An asterisk ('*') at the beginning or end of the
         *                        string is used as a wildcard. Leave nullptr if all loggers should
         *                        be affected. Use this parameter only in more complex logging
         *                        scenarios.
         ******************************************************************************************/
        ALOX_API
        void        SetDomain( const char*       domain,
                               Log::DomainLevel  domainLevel,
                               bool              recursive=      true,
                               const char*       loggerFilter=   nullptr );

        /** ****************************************************************************************
         *  This method is used disable one or more loggers completely without touching the log
         *  levels of the domains and hence without the need to restore such log levels later.
         *
         * @param disabled        If true, the logger(src) will be completely disabled, if false
         *                        the normal domain specific log levels will be applied for log
         *                        decisions.
         * @param loggerFilter    (Optional) A filter for the loggers to be affected. A simple
         *                        string compare without case sensitivity is performed. An asterisk
         *                        ('*') at the beginning or end of the string is used as a
         *                        wildcard. Leave nullptr if all loggers should be affected. This
         *                        parameter is optional and used in more complex logging scenarios.
         ******************************************************************************************/
        ALOX_API
        void        SetDisabled(    bool disabled, const char* loggerFilter= nullptr );

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
         *                         wildcard. Leave nullptr if all loggers should be affected.
         ******************************************************************************************/
        ALOX_API
        void SetStartTime( aworx::util::Ticks startTime= aworx::util::Ticks(0), const char* loggerFilter= nullptr );

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
         *                        wildcard. Leave nullptr if all loggers should be affected.
         ******************************************************************************************/
            ALOX_API
            void SetStartTime( time_t startTime, const char* loggerFilter= nullptr );


        #endif // no else here (doxygen)!

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
         *                        wildcard. Leave nullptr if all loggers should be affected.
         ******************************************************************************************/
            ALOX_API
            void        SetStartTime( LPFILETIME startTime, const char* loggerFilter= nullptr );

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
        void        MapThreadName( const char* threadName, int id= 0 );

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
         *                      default domain of the source file. For other values, the default
         *                      domain is ignored (regardless if this is starting with a slash or
         *                      not).
         * @param level         The log level.
         * @param headLine      If given, a separated headline will be logged at first place.
         * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
         *                      parameter enables different loggers to have different domains. A
         *                      simple string compare without case sensitivity is performed. An
         *                      asterisk ('*') at the beginning or end of the string is used as a
         *                      wildcard. Leave nullptr if all loggers should be affected. Use this
         *                      parameter only in more complex logging scenarios.
         ******************************************************************************************/
        ALOX_API
        void        LogConfig( const char*       domain,
                               Log::Level        level,
                               const char*       headLine,
                               const char*       loggerFilter= nullptr );


    // #############################################################################################
    // Main logging methods
    // #############################################################################################

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Verbose. This is the highest (most
         *  verbose) log level, which is only actually logged if the log domains log level is set
         *  to "All". This overloaded version does not offer a domain parameter but relies on a
         *  default domain set for the source file this function is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Verbose(                     const util::AString& msg,   int indent= 0 )
        {
            Line( true, nullptr, Log::Level::VERBOSE, &msg, 3, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Verbose. This is the highest (most
         *  verbose) log level, which is only actually logged if the log domains log level is set
         *  to "All".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Verbose( const char* domain, const util::AString& msg,   int indent= 0 )
        {
             Line( true, domain, Log::Level::VERBOSE, &msg, 3, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Verbose. This is the highest (most verbose)
         *  log level, which is only actually logged if the log domains log level is set to "All". This
         *  overloaded version does not offer a domain parameter but relies on a default domain set for
         *  the source file this function is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Verbose(                     std::string& msg,           int indent= 0 )
        {
            Line( true, nullptr, Log::Level::VERBOSE, &msg, 2, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Verbose. This is the highest (most verbose)
         *  log level, which is only actually logged if the log domains log level is set to "All".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Verbose( const char* domain, std::string&  msg,          int indent= 0 )
        {
            Line( true, domain, Log::Level::VERBOSE, &msg, 2, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Verbose. This is the highest (most verbose)
         *  log level, which is only actually logged if the log domains log level is set to "All". This
         *  overloaded version does not offer a domain parameter but relies on a default domain set for
         *  the source file this function is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Verbose(                     const char* msg,            int indent= 0 )
        {
            Line( true, nullptr, Log::Level::VERBOSE, msg, 1, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Verbose. This is the highest (most verbose)
         *  log level, which is only actually logged if the log domains log level is set to "All".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Verbose( const char* domain, const char* msg,            int indent= 0 )
        {
            Line( true, domain, Log::Level::VERBOSE, msg, 1, indent, nullptr );
        }

        /** ****************************************************************************************
         *
         *  Logs a string with log level equal to Log::Level::Info. This is the second highest (after
         *  Verbose) log level, which is only actually logged if the log domains log level is set to
         *  "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
         *  a default domain set for the source file this function is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Info(                        const util::AString& msg,   int indent= 0 )
        {
            Line( true,  nullptr, Log::Level::INFO, &msg, 3, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Info. This is the second highest (after
         *  Verbose) log level, which is only actually logged if the log domains log level is set to
         *  "Info" or "Verbose".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Info( const char*  domain,   const util::AString& msg,   int indent= 0 )
        {
            Line( true, domain, Log::Level::INFO, &msg, 3, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Info. This is the second highest (after
         *  Verbose) log level, which is only actually logged if the log domains log level is set to
         *  "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
         *  a default domain set for the source file this function is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Info(                        std::string& msg,           int indent= 0 )
        {
            Line( true,  nullptr, Log::Level::INFO, &msg, 2, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Info. This is the second highest (after
         *  Verbose) log level, which is only actually logged if the log domains log level is set to
         *  "Info" or "Verbose".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Info( const char* domain,    std::string& msg,           int indent= 0 )
        {
            Line( true, domain, Log::Level::INFO, &msg, 2, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Info. This is the second highest (after
         *  Verbose) log level, which is only actually logged if the log domains log level is set to
         *  "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
         *  a default domain set for the source file this function is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Info(                        const char* msg,            int indent= 0 )
        {
            Line( true,  nullptr, Log::Level::INFO, msg, 1, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Info. This is the second highest (after
         *  Verbose) log level, which is only actually logged if the log domains log level is set to
         *  "Info" or "Verbose".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Info( const char* domain,    const char* msg,            int indent= 0 )
        {
            Line( true, domain, Log::Level::INFO, msg, 1, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Warning. Log messages of this log level
         *  are are logged if the log domains log level is set to "Warning", "Info" or "All".
         *  This overloaded version does not offer a domain parameter but relies on a default domain set
         *  for the source file this function is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Warning(                     const util::AString& msg,   int indent= 0 )
        {
            Line( true, nullptr, Log::Level::WARNING, &msg, 3, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Warning. Log messages of this log level are
         *  are logged if the log domains log level is set to "Warning", "Info" or "All".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Warning( const char* domain, const util::AString& msg,   int indent= 0 )
        {
            Line( true, domain, Log::Level::WARNING, &msg, 3, indent, nullptr );
        }


        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Warning. Log messages of this log level
         *  are are logged if the log domains log level is set to "Warning", "Info" or "All".
         *  This overloaded version does not offer a domain parameter but relies on a default domain set
         *  for the source file this function is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Warning(                     std::string& msg,           int indent= 0 )
        {
            Line( true, nullptr, Log::Level::WARNING, &msg, 2, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Warning. Log messages of this log level are
         *  are logged if the log domains log level is set to "Warning", "Info" or "All".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Warning( const char* domain, std::string& msg,           int indent= 0 )
        {
            Line( true, domain, Log::Level::WARNING, &msg, 2, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Warning. Log messages of this log level
         *  are are logged if the log domains log level is set to "Warning", "Info" or "All".
         *  This overloaded version does not offer a domain parameter but relies on a default domain set
         *  for the source file this function is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Warning(                     const char* msg,            int indent= 0 )
        {
            Line( true, nullptr, Log::Level::WARNING, msg, 1, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Warning. Log messages of this log level are
         *  are logged if the log domains log level is set to "Warning", "Info" or "All".
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Warning( const char* domain, const char* msg,            int indent= 0 )
        {
            Line( true, domain, Log::Level::WARNING, msg, 1, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Error. Log messages of this log level are
         *  are always logged unless domains log level is set to <em>OFF</em>. This overloaded version does not
         *  offer a domain parameter but relies on a default domain set for the source file this function
         *  is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Error(                       const util::AString& msg,   int indent= 0 )
        {
            Line( true, nullptr, Log::Level::ERROR, &msg, 3, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level Error. Log messages of this log level are are
         *  always logged unless domains log level is set to <em>OFF</em>.
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Error( const char* domain,   const util::AString& msg,   int indent= 0 )
        {
            Line( true, domain, Log::Level::ERROR, &msg, 3, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Error. Log messages of this log level are
         *  are always logged unless domains log level is set to <em>OFF</em>. This overloaded version does not
         *  offer a domain parameter but relies on a default domain set for the source file this function
         *  is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Error(                       std::string& msg,           int indent= 0 )
        {
            Line( true, nullptr, Log::Level::ERROR, &msg, 2, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level Error. Log messages of this log level are are
         *  always logged unless domains log level is set to <em>OFF</em>.
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Error( const char* domain,   std::string& msg,           int indent= 0 )
        {
            Line( true, domain, Log::Level::ERROR, &msg, 2, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level::Error. Log messages of this log level are
         *  are always logged unless domains log level is set to <em>OFF</em>. This overloaded version does not
         *  offer a domain parameter but relies on a default domain set for the source file this function
         *  is used in.
         *
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Error(                       const char* msg,            int indent= 0 )
        {
            Line( true, nullptr, Log::Level::ERROR, msg, 1, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string with log level equal to Log::Level Error.
         *  Log messages of this log level are are always logged unless domains log level is set to
         *  <em>OFF</em>.
         *
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default domain
         *                  of the source file. For other values, the default domain is ignored
         *                  (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) The indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Error(  const char* domain,  const char* msg,            int indent= 0 )
        {
            Line( true, domain, Log::Level::ERROR, msg, 1, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string only if the given condition is not true. Log level will be highest,
         *  namely Log::Level::Error if condition is false.
         *  This overloaded version does not offer a domain parameter but relies on a default
         *  domain set for the source file this function is used in.
         *
         * @param trueOrLog The log is only performed if condition is not true.
         * @param msg       The string to be logged.
         * @param indent    (Optional) the indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Assert( bool trueOrLog,      const util::AString& msg,                 int indent= 0 )
        {
            Line( !trueOrLog, nullptr, Log::Level::ERROR, &msg, 3, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string only if the given condition is not true. Log level will be highest, namely
         *  Log::Level::Error.
         *
         * @param trueOrLog The log is only performed if condition is not true.
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default
         *                  domain of the source file. For other values, the default domain is
         *                  ignored (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) the indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Assert( bool trueOrLog, const char* domain, const util::AString& msg,  int indent= 0 )
        {
            Line( !trueOrLog, domain, Log::Level::ERROR, &msg, 3, indent, nullptr );
        }


        /** ****************************************************************************************
         *  Logs a string only if the given condition is not true. Log level will be highest, namely
         *  Error if condition is false. This overloaded version does not offer a domain parameter
         *  but relies on a default domain set for the source file this function is used in.
         *
         * @param trueOrLog The log is only performed if condition is not true.
         * @param msg       The string to be logged.
         * @param indent    (Optional) the indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Assert( bool trueOrLog,                     std::string& msg,          int indent= 0 )
        {
            Line( !trueOrLog, nullptr, Log::Level::ERROR, &msg, 2, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string only if the given condition is not true. Log level will be highest, namely
         *  Log::Level::Error.
         *
         * @param trueOrLog  The log is only performed if condition is not true.
         * @param domain     If this is nullptr, the default domain is used. If this is starting
         *                   with a swung dash ('~') this is interpreted a sub domain to the default
         *                   domain of the source file. For other values, the default domain is
         *                   ignored (regardless if this is starting with a slash or not).
         * @param msg        The string to be logged.
         * @param indent     (Optional) the indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Assert( bool trueOrLog, const char* domain, std::string& msg,          int indent= 0 )
        {
            Line( !trueOrLog, domain, Log::Level::ERROR, &msg, 2, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string only if the given condition is not true. Log level will be highest, namely
         *  Log::Level::Error if condition is false. This overloaded version does not offer a
         *  domain parameter but relies on a default domain set for the source file this function
         *  is used in.
         *
         * @param trueOrLog The log is only performed if condition is not true.
         * @param msg       The string to be logged.
         * @param indent    (Optional) the indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Assert( bool trueOrLog,                     const char* msg,           int indent= 0 )
        {
            Line( !trueOrLog, nullptr, Log::Level::ERROR, msg, 1, indent, nullptr );
        }

        /** ****************************************************************************************
         *  Logs a string only if the given condition is not true. Log level will be highest, namely
         *  Log::Level::Error.
         *
         * @param trueOrLog The log is only performed if condition is not true.
         * @param domain    If this is nullptr, the default domain is used. If this is starting with
         *                  a swung dash ('~') this is interpreted a sub domain to the default
         *                  domain of the source file. For other values, the default domain is
         *                  ignored (regardless if this is starting with a slash or not).
         * @param msg       The string to be logged.
         * @param indent    (Optional) the indentation in the output. Defaults to 0.
         ******************************************************************************************/
        void Assert( bool trueOrLog, const char* domain, const char* msg,           int indent= 0 )
        {
            Line( !trueOrLog, domain, Log::Level::ERROR, msg,  1, indent, nullptr );
        }

        // #############################################################################################
        // Line() methods
        // #############################################################################################

        /** ****************************************************************************************
         *  Provides a more flexible but complex way to log a message. Especially it provides the
         *  possibility to log other objects than string types.
         *  The methods #Verbose, #Info, #Warning, #Error and #Assert() are 'shortcuts' to this
         *  function and are more convenient to use.
         *  For logging strings, use this function only in the rare cases, e.g. when a log
         *  level is decided only at runtime or when you want to use a logger filter, etc.
         *
         * @param doLog         Conditional logging. If false, the log is not performed. CntLogCalls
         *                      is still increased by one.
         * @param domain        If this is nullptr, the default domain is used. If this is starting
         *                      with a swung dash ('~') this is interpreted a sub domain to the
         *                      default domain of the source file. For other values, the default
         *                      domain is ignored (regardless if this is starting with a slash or
         *                      not).
         * @param level         The log level.
         * @param msgObject     The object to log.
         * @param typeInfo      Type information on the object to log.
         * @param indent        (Optional) The indentation in the output. Defaults to 0.
         * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
         *                      parameter enables different loggers to have different domains. A
         *                      simple string compare without case sensitivity is performed. An
         *                      asterisk ('*') at the beginning or end of the string is used as a
         *                      wildcard. Leave nullptr if all loggers should be affected. Use this
         *                      parameter only in more complex logging scenarios.
         ******************************************************************************************/
        ALOX_API
        void Line(  bool        doLog,       const char*  domain,             Log::Level level,
                    const void* msgObject,   int          typeInfo,
                    int         indent= 0,   const char*  loggerFilter= nullptr );

        /** ****************************************************************************************
         *  Logs an object using the given log level, log domain and indentation and logger filter.
         *  See \ref Line(bool, const char*, Log::Level, const void*, int, int, const char*) "Line"
         *  for a version of this method that supports the maximum number of parameters.
         *
         * @param domain        If this is nullptr, the default domain is used. If this is starting
         *                      with a swung dash ('~') this is interpreted a sub domain to the
         *                      default domain of the source file. For other values, the default
         *                      domain is ignored (regardless if this is starting with a slash or
         *                      not).
         * @param level         The log level.
         * @param msgObject     The object to log.
         * @param typeInfo      Type information on the object to log.
         * @param indent        (Optional) The indentation in the output. Defaults to 0.
         * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
         *                      parameter enables different loggers to have different domains. A
         *                      simple string compare without case sensitivity is performed. An
         *                      asterisk ('*') at the beginning or end of the string is used as a
         *                      wildcard. Leave nullptr if all loggers should be affected. Use this
         *                      parameter only in more complex logging scenarios.
         ******************************************************************************************/
        void Line(                           const char*  domain,             Log::Level level,
                    const void* msgObject,   int          typeInfo,
                    int         indent= 0,   const char*  loggerFilter= nullptr )
        {
            Line( true, domain, level, msgObject, typeInfo, indent, loggerFilter );
        }

        /** ****************************************************************************************
         *  Logs an object using the given log level, indentation and logger filter and the default
         *  domain set for the scope.
         *  See \ref Line(bool, const char*, Log::Level, const void*, int, int, const char*) "Line"
         *  for a version of this method that supports the maximum number of parameters.
         *
         * @param level         The log level.
         * @param msgObject     The object to log.
         * @param typeInfo      Type information on the object to log.
         * @param indent        (Optional) The indentation in the output. Defaults to 0.
         * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
         *                      parameter enables different loggers to have different domains. A
         *                      simple string compare without case sensitivity is performed. An
         *                      asterisk ('*') at the beginning or end of the string is used as a
         *                      wildcard. Leave nullptr if all loggers should be affected. Use this
         *                      parameter only in more complex logging scenarios.
         ******************************************************************************************/
        void Line(                                                            Log::Level level,
                    const void* msgObject,   int          typeInfo,
                    int         indent= 0,   const char*  loggerFilter= nullptr )
        {
            Line( true, nullptr, level, msgObject, typeInfo, indent, loggerFilter );
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
        void            evaluateResultDomain( const char* domain  );

        /** ****************************************************************************************
         *  Logs an internal error message to the domain given by field InternalDomain. Attn: must only
         *  be called after saveAndSet() was performed.
         *
         * @param level  The log level.
         * @param msg    The message.
         ******************************************************************************************/
        ALOX_API
        void            internalLog( Log::Level level, util::AString& msg );

        /** ****************************************************************************************
         *  Compares a loggers name with a filter string with simplest wildcard support ('*') at the
         *  beginning or end of the string. If loggerFilter is nullptr, a match is indicated.
         *
         * @param logger          The logger to be filtered.
         * @param loggerFilter    The filter.
         * @return True if logger is not filtered out.
         ******************************************************************************************/
        ALOX_API
        static bool     simpleWildcardFilter( core::Logger* logger, const char* loggerFilter );

        /** ****************************************************************************************
         *  Internal method used by LogConfig() to recursively log LogDomain instances.
         * @param domain     The LogDomain instance to log out.
         * @param indent     The indentation in the output, recursively increased..
         * @param domPath    Actual path relative to recursion, solely for log output.
         * @param buffer     The buffer to log to.
         ******************************************************************************************/
        ALOX_API
        void            logConfigDomainRecursive( core::LogDomain& domain, int indent, util::AString& domPath, util::AString& buffer );

}; // class Lox
}} // namespace



#endif // HPP_AWORX_ALOX_LOX
