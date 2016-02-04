// #################################################################################################
//  cs.aworx.lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System.Runtime.CompilerServices;
using System;
using System.Collections.Generic;
using System.Text;
using cs.aworx.lib;
using cs.aworx.lib.enums;
using cs.aworx.lox.core;
using cs.aworx.lox.loggers;
using cs.aworx.lib.threads;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lox.core.textlogger;

#if (!ALOX_NO_THREADS)
    using System.Threading;
using System.Globalization;
using System.Diagnostics;
#endif

/** ************************************************************************************************
 * This is the C++ namespace for code of the <em>%ALox Logging Library</em>.
 * Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace cs.aworx.lox {


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
 * In standard log scenarios, it is recommend **not** to use this class, but to use class
 * \ref cs::aworx::lox::Log "Log" instead, which is a 100% static wrapper around this one.
 * In other words, class \b Log incorporates one static instance of this class and mirrors the
 * whole interface with static methods.
 *
 * Furthermore, all invocations of methods of class \b Log are pruned in release code, while
 * invocations of methods of this class are not. Hence, this class and interface should be used to
 * implement log code that is deemed to remain in the release version of software.
 * The use of class Log and Lox can be mixed, to enable debug log output in parallel to release
 * output.
 **************************************************************************************************/
public class Lox
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

        #if ALOX_DBG_LOG || ALOX_REL_LOG

        /**
         * A counter for the quantity of calls. The count includes logs that were suppressed by
         * disabled log rootDomain and those suppressed by the optional log condition parameter.
         * Hence, it can also be used as a condition to log only every n-th time by calling using
         * the conditional parameter of #Line(), e.g.: *Lox.Line( (Log.qtyLogCalls % n) == 0, ...*.
         */
        public                 int                      CntLogCalls                             =0;

        /**
         * This is the ThreadLock (mutex) for the Lox class. Each Lox method uses this mutex.
         * If thread safeness is not needed for the logging system (see user manual) the mutex can be
         * switched of using ThreadLock.setUnsafe(). The goal here would be to increase logging
         * performance. This is really a very seldom case, and it is better to be kept in safe mode.
         */
        public                 ThreadLock               Lock
                                                            #if ALOX_NO_THREADS // ->unsafe
                                                                      =new ThreadLock( true, true );
                                                            #else
                                                                      =new ThreadLock();
                                                            #endif

        /**
         * This is the log domain name used by this class. By manipulating this Domains log level, the
         * the verbosity of ALox itself can be controlled. For example, in 'Info' level,  calls to
         * #SetDomain are logged which can be helpful to determine the log
         * domains that are created by libraries and larger projects.
         */
        public                String                    InternalDomain                      ="ALOX";

        /**
         * This is the log domain name chosen when no resulting domain name could be evaluated, e.g.
         * when no domain was specified but also no default domain was set. Or when missing caller
         * information do not allow to detect the scope.
         */
        public               String                      NullDomain                         ="NULL";

        /**
         * If this is positive, an error is logged to the \ref InternalDomain "internal domain"
         * when a logging statement is executed which has no domain given and no default domain is
         * set either. The field is decremented with each warning until zero is hit.
         * Defaults to 10.
         */
        public                 int                      ErrIfNoDefaultDomain                    =10;

    // #############################################################################################
    // Private/protected fields
    // #############################################################################################
        /// The list of Loggers.
        protected         List<Logger>                  loggers            = new List<Logger>();

        /// Optional default domains for a source file.
        protected         Dictionary<AString, AString>  defaultDomains     = new Dictionary<AString, AString>();

        /// Code markers
        protected         Dictionary<AString, Object>   markers            = new Dictionary<AString, Object>();

        /// Information about the source code, method, thread, etc. invoking a log  call
        protected         CallerInfo                    caller             = new CallerInfo();

        /// The evaluated domain name.
        protected         AString                       resDomain          = new AString( 32 );

        /// An AString singleton. Can be acquired, using buf()
        protected         AString                       logBuf             = new AString( 128 );

        /// A locker for the log buffer singleton
        protected         ThreadLock                    logBufLock         = new ThreadLock();

        /// A temporary AString, following the "create once and reuse" design pattern.
        protected         AString                       tempAS             = new AString( 256 );

        #if !ALOX_NO_THREADS
            /**
                     *   Dictionary to translate thread ids into something maybe nicer/shorter. The dictionary has to
             *   be filled by the user of the library.
             *
             */
            public       Dictionary<int, String>        ThreadDictionary =new Dictionary<int, String>();
        #endif

    #endif //ALOX_DBG_LOG || ALOX_REL_LOG



    // #############################################################################################
    // Constructors
    // #############################################################################################

    /** ********************************************************************************************
     * Constructs a new, empty Lox.
     **********************************************************************************************/
    public Lox()
    {
        // set recursion warning of log buffer lock to 1. Warnings are logged if recursively acquired more
        // than once
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            logBufLock.RecursionWarningThreshold= 1;
        #endif
    }

    // #############################################################################################
    // Interface
    // #############################################################################################


    /** ********************************************************************************************
     * Returns an AString singleton, that can be reused for all basic log calls. Textual messages
     * that are assembled from out of strings, numbers and other data, can be efficiently built
     * by reusing this singleton.
     * Whenever this method is called, the returned AString object gets "locked" by a corresponding
     * ThreadLock object. Therefore it has to be used as a message within one of the log methods of
     * this class (error(), warning(), info(), verbose(), assert() or line()) or it has to be
     * explicitly released using BufAbort().
     * If this is not done, the object does not get released and parallel threads using this
     * method would block! So, do not use Buf() for other reasons than for creating log messages
     * and be sure to release it "in time".
     *
     * @return The static AString singleton.
     **********************************************************************************************/
    public AString    Buf()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            logBufLock.Acquire();
            logBuf.Clear();
            return logBuf;
        #else
            return  null;
        #endif
    }

    /** ********************************************************************************************
     * Use this method when you want to abort a log call that you "started" with acquiring the
     * internal AString singleton acquired using method Buf(). Use BufAbort() only if you did
     * not use the acquired buffer as a parameter of a log method, because this internally
     * releases the buf already.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void        BufAbort()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            logBufLock.Release();
        #endif
    }

    /** ************************************************************************************
     * This method creates an adequate/default console logger. 'Adequate' here means that
     * this function tries to detect what might be the best choice for the environment
     * that the ALox based process is running in.
     * This method is due to changes with the evolution of future ALox versions and
     * should be considered as a convenience method to shorten the bootstrap code needed
     * to use ALox.
     *
     * The current C# implementation takes the following approach:
     *
     * - check if configuration variable
     *   [ALOX_CL_MODE](../group__GrpALoxConfigVars.html) is set. This variable's
     *   setting takes priority and if set, the according logger is created.
     * - check whether a console window is attached to the current process.
     *   If not, then a plain text logger is chosen (class
     *   \ref cs::aworx::lox::loggers::ConsoleLogger "ConsoleLogger").
     * - Otherwise, on Unix like OS, class
     *   \ref cs::aworx::lox::loggers::AnsiConsoleLogger "AnsiConsoleLogger" is chosen,
     *   while on windows systems class
     *   \ref cs::aworx::lox::loggers::ColorConsoleLogger "ColorConsoleLogger"
     *   takes preference.
     *
     * For further information check out the source code.
     *
     * @param name (Optional) The name of the logger.
     *             Defaults to null, which implies standard logger names defined
     *             in the logger sub-classes.
     * @return The \b TextLogger chosen.
     **************************************************************************************/
    public static TextLogger CreateConsoleLogger( String name= null )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        //--- first: check environment "ALOX_DBG_CL_MODE". They have precedence ---
        {
            AString consoleMode= new AString();
            if( ALIB.Config.Get( Log.ConfigCategoryName, "CL_MODE", consoleMode ) != 0 )
            {
                if( consoleMode.Equals( "PLAIN",    Case.Ignore ) )   { return new ConsoleLogger     ( name ); }
                if( consoleMode.Equals( "ANSI",     Case.Ignore ) )   { return new AnsiConsoleLogger ( name ); }
                if( consoleMode.Equals( "WINDOWS",  Case.Ignore ) )   { return new ColorConsoleLogger( name ); }

                ALIB.WARNING( "Unrecognized value in config variable: ALOX_CL_MODE =" + consoleMode.ToString() );
            }
        }

        //--- second: check debug environment
        // .... this is not implemented in C#, yet ...

        // not detected: in windows, we choose ColorConsoleLogger, in Unix ANSI
        if( ALIB.SysInfo_HasConsoleWindow )
            return  ALIB.SysInfo_IsWindowsOS()  ? (TextLogger) new ColorConsoleLogger( name )
                                                : (TextLogger) new AnsiConsoleLogger ( name );
        // default
        return new ConsoleLogger( name );

        #else
            return null;
        #endif
    }



    /** ********************************************************************************************
     * Adds a logger to this container of loggers.
     * Each log call that is performed through this classes' interface
     * will be forwarded to this logger, unless filtered out with optional filter parameter.
     *
     * \note
     *   This method checks whether the domain used for internal ALox messages
     *   (see field #InternalDomain) is already registered with the given logger.
     *   Only if not, the domain is registered and set to domain level
     *   \ref cs::aworx::lox::Log::DomainLevel::WarningsAndErrors "DomainLevel.WarningsAndErrors".
     *   This means, that it does not play a role, if changes to the level of domain "ALOX" are
     *   performed prior to adding a logger, using
     *   \ref cs::aworx::lox::core::Logger::SetDomain "Logger.SetDomain"
     *   or after a logger was added, using
     *   \ref cs::aworx::lox::Lox::SetDomain "Lox.SetDomain".
     *
     * @param logger  The logger to be added.
     *
     * @param csf     (Optional) Caller info, compiler generated. Please omit.
     * @param cln     (Optional) Caller info, compiler generated. Please omit.
     * @param cmn     (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void        AddLogger( Logger logger,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // initialize caller information
                caller.Set( csf, cln, cmn
                                #if !ALOX_NO_THREADS
                                            , ThreadDictionary
                                #endif
                          );

                // if list existed, check if logger was added already
                if ( loggers.Contains( logger ) )
                {
                    internalLog( Log.Level.Warning,
                                 tempAS.Clear()._("AddLogger: Logger \"")
                                               ._( logger.Name )._("\" already exists. Not added.") );
                    return;
                }

                // add logger to list
                loggers.Add( logger );

                // if internal domain was not registered, yet (which is the normal case), we set
                // it to WarningsAndErrors
                bool wasCreated= false;
                Domain internalDomain= logger.RootDomain.Find( new AString( InternalDomain ), ref wasCreated );
                if ( wasCreated )
                    internalDomain.SetLevel( Log.DomainLevel.WarningsAndErrors );

                // log info on this
                tempAS._()._("AddLogger: Logger \"")._(logger.Name)._("\" ");
                if ( logger.Name.ToLower().CompareTo( logger.TypeName.ToLower() ) != 0 )
                    tempAS._('(')._( logger.TypeName )._(") ");
                tempAS._("added.");
                internalLog( Log.Level.Info, tempAS );


            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     *  Retrieve an instance of a Logger by its name.
     *
     * @param loggerName    The name of the logger to search for (case insensitive)
     * @return  The logger, null if not found.
     **********************************************************************************************/
    public  Logger GetLogger( String loggerName )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // search logger
                foreach ( Logger logger in loggers )
                if ( logger.Name.Equals( loggerName, StringComparison.OrdinalIgnoreCase ) )
                    return logger;

                // not found
                return null;

            } finally { Lock.Release(); }
        #else
            return  null;
        #endif
    }


    /** ********************************************************************************************
     * Removes all loggers that match the filter name from this  interface.
     * @param logger  The logger that is supposed to be removed.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void RemoveLogger( Logger logger )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // loop over all loggers backwards
                for( int i= loggers.Count - 1; i >= 0; i--)
                    if ( logger == loggers[ i ] )
                    {
                        loggers.RemoveAt( i );
                        return;
                    }

            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     * Removes all loggers that match the filter name from this  interface.
     * @param loggerFilter  (Optional) A filter for the loggers to be affected. A simple
     *                              string compare without case sensitivity is performed. An asterisk
     *                              ('*') at the beginning or end of the string is used as a
     *                              wildcard. Defaults to null which causes all loggers to be
     *                              removed.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void RemoveLoggers( String loggerFilter= null )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // loop over all loggers backwards
                for(int i= loggers.Count - 1; i >= 0; i--)
                    if ( simpleWildcardFilter( loggers[ i ], loggerFilter ) )
                        loggers.RemoveAt( i );

            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     * This method is used to define a log domain. The method is usually invoked within the same
     * source "context" (aka, class, namespace, package, etc.) that later on uses the domain to perform
     * log statements. Often, calls to this functions are placed in static constructors or similar
     * code that is executed only once and very early in the life-cycle of a process.
     *
     * Each log statement refers to such a domain which can be used specifically for different
     * parts of your application like assemblies, libraries, namespaces, specific code files or even
     * for a single method. The domain name should be short, pregnant and self explaining.
     *
     * Domains can be created with path separators '/', for example 'COMM/SOCK' could be the domain in
     * a socket class, residing within a communication library.
     * The advantage of creating paths and this way "sub domains", is that a whole bunch of logging
     * domains can be altered (on/off) by just altering the root domain.
     *
     * If a domain and path is given that is not known already, then the whole path of domains is
     * created.
     *
     * If the parameter **scope** is provided with a value not equal to Log.Scope.None, the given
     * domain becomes the default domain for respective scope. For any subsequent log calls from
     * within this scope, where no domain is explicitly given, this default domain is used.
     * If subsequent log calls specify a domain name with a leading '~' character, then such
     * domain is concatenated to the default domain to build a complete domain path.
     *
     * @param domain    The domain name (and path) to register.
     *                  If this is starting    with a swung dash ('~') this is interpreted a sub
     *                  domain to a (potentially already set!) default domain of the scope.
     *                  For other values, the default    domain is ignored (regardless if this is
     *                  starting with a slash or    not).
     * @param scope     If a value other than Log.Scope.None is provided, the given domain
     *                  name is registered as the default domain for the given scope. Default
     *                  domains set for 'inner scopes' have higher priority than those set for
     *                  outer scopes. Available Scope definitions are platform/language
     *                  dependent.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void SetDomain( String    domain,     Log.Scope scope,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // setup
                caller.Set( csf, cln, cmn
                                #if !ALOX_NO_THREADS
                                            , ThreadDictionary
                                #endif
                          );
                evaluateResultDomain( domain );

                // check parameter
                if ( String.IsNullOrEmpty( domain ) )
                {
                    internalLog( Log.Level.Error,
                                 tempAS.Clear()._("SetDomain: Empty domain given. Not registered.") );
                    return;
                }

                // set domain as default for calling source file's log calls
                if ( scope != Log.Scope.None )
                {
                    AString key= new AString(csf.Length + cmn.Length + 1);
                    key._( csf );
                    if ( scope == Log.Scope.Method )
                        key._( '#' )._( cmn );

                    // store domain in hash table
                    AString previous; defaultDomains.TryGetValue( key, out previous );
                    defaultDomains[key]= new AString( resDomain );

                    // log info on this
                    tempAS._()._("SetDomain: Domain \"")           ._(resDomain)
                              ._("\" set as default for scope \"") ._(scope.ToString())._("\".");

                    if ( previous != null )
                        tempAS._(" Replacing previous Domain \"")._(previous)._("\".");
                    internalLog( previous!=null? Log.Level.Warning : Log.Level.Info, tempAS );
                }

            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     *  Sets the domain log level and (by default) all it's sub domains recursively. In the case
     *  that sub domains should be set to a different log level, then this function has to be
     *  called for such sub domains after the call to the parent domain (or recursion has to be
     *  switched off, using the parameter 'recursive'). It is not necessary to register a domain
     *  before setting its log level and log levels can be set and modified any time.
     *
     * @param domain          If this is null, the default domain is used. If this is starting
     *                        with a swung dash ('~') this is interpreted a sub domain to the
     *                        default domain of the scope. For other values, the default
     *                        domain is ignored (regardless if this is starting with a slash or
     *                        not).
     * @param domainLevel     The domains log level to be set.
     * @param loggerFilter    (Optional) A filter for the loggers to be affected. This
     *                        parameter enables different loggers to have different domains and
     *                        log levels. A simple string compare without case sensitivity is
     *                        performed. An asterisk ('*') at the beginning or end of the
     *                        string is used as a wildcard. Leave to \e null if all loggers should be
     *                        affected. Use this parameter only in more complex logging
     *                        scenarios.
     * @param propagation     (Optional) If \c Propagation.ToDescendants, the default, the
     *                        level is set for all sub-domains recursively.
     *                        If \c Propagation.None, then only this domain is changed.
     * @param csf             (Optional) Caller info, compiler generated. Please omit.
     * @param cln             (Optional) Caller info, compiler generated. Please omit.
     * @param cmn             (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void SetDomain( String          domain,
                            Log.DomainLevel domainLevel,
                            String          loggerFilter=   null,
                            Propagation     propagation=    Propagation.ToDescendants,

    [CallerFilePath] String csf="",[CallerLineNumber]   int             cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                caller.Set( csf, cln, cmn
                                #if !ALOX_NO_THREADS
                                            , ThreadDictionary
                                #endif
                          );

                bool resultDomainEvaluatedLazily= false;
                foreach ( Logger logger in loggers )
                {
                    if ( !simpleWildcardFilter( logger, loggerFilter ) )
                        continue;

                    if (!resultDomainEvaluatedLazily)
                    {
                        resultDomainEvaluatedLazily= true;
                        evaluateResultDomain( domain );
                    }

                    logger.SetDomain( resDomain, domainLevel, propagation );

                    internalLog( Log.Level.Info,
                                 tempAS._()._NC( "SetDomain: Domain \""   ) ._NC(resDomain)
                                           ._NC( "\" log level set to \"" ) ._NC(domainLevel.ToString())
                                           ._NC( "\" for logger \""       ) ._NC(logger.Name)._("\".") );
                }


            } finally { Lock.Release(); }
        #endif
    }

    /** ****************************************************************************************
     * Invokes methods
     * <c>SetDomain(domain, scope)</c>  and <c>SetDomain(domain, domainLevel)</c>.<br>
     * Optional parameter \p loggerFilter applies only to the domain level setting.
     *
     * @param domain       If this is null, the default domain is used. If this is starting
     *                     with a swung dash ('~') this is interpreted a sub domain to the
     *                     default domain of the scope. For other values, the default
     *                     domain is ignored (regardless if this is starting with a slash or
     *                     not).
     * @param scope        If a value other than Log.Scope.None is provided, the given domain
     *                     name is registered as the default domain for the given scope. Default
     *                     domains set for 'inner scopes' have higher priority than those set for
     *                     outer scopes. Available Scope definitions are platform/language
     *                     dependent.
     * @param domainLevel  The domains log level to be set.
     * @param loggerFilter (Optional) A filter for the loggers to be affected. This
     *                     parameter enables different loggers to have different domains and
     *                     log levels. A simple string compare without case sensitivity is
     *                     performed. An asterisk ('*') at the beginning or end of the
     *                     string is used as a wildcard. Leave to \e null if all loggers should be
     *                     affected. Use this parameter only in more complex logging
     *                     scenarios.
     * @param csf          (Optional) Caller info, compiler generated. Please omit.
     * @param cln          (Optional) Caller info, compiler generated. Please omit.
     * @param cmn          (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void SetDomain( String          domain,
                            Log.Scope       scope,
                            Log.DomainLevel domainLevel,
                            String          loggerFilter=   null,

    [CallerFilePath] String csf="",[CallerLineNumber]   int             cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            SetDomain( domain, scope                                               , csf, cln, cmn );
            SetDomain( domain, domainLevel, loggerFilter, Propagation.ToDescendants, csf, cln, cmn );
        #endif
    }


    /** ****************************************************************************************
     * Invokes methods
     * <c>SetDomain(domain, scope)</c>  and <c>SetDomain(domain, domainLevel)</c>..
     *
     * @param domain       If this is null, the default domain is used. If this is starting
     *                     with a swung dash ('~') this is interpreted a sub domain to the
     *                     default domain of the scope. For other values, the default
     *                     domain is ignored (regardless if this is starting with a slash or
     *                     not).
     * @param domainLevel  The domains log level to be set.
     * @param scope        If a value other than Log.Scope.None is provided, the given domain
     *                     name is registered as the default domain for the given scope. Default
     *                     domains set for 'inner scopes' have higher priority than those set for
     *                     outer scopes. Available Scope definitions are platform/language
     *                     dependent.
     * @param csf          (Optional) Caller info, compiler generated. Please omit.
     * @param cln          (Optional) Caller info, compiler generated. Please omit.
     * @param cmn          (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void SetDomain( String          domain,
                            Log.DomainLevel domainLevel,
                            Log.Scope       scope,

    [CallerFilePath] String csf="",[CallerLineNumber]   int             cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            SetDomain( domain, scope                                               , csf, cln, cmn );
            SetDomain( domain, domainLevel, null, Propagation.ToDescendants, csf, cln, cmn );
        #endif
    }


    /** ********************************************************************************************
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
     *                      Leave to \e null if all loggers should be affected.
     * @param csf           (Optional) Caller info, compiler generated. Please omit.
     * @param cln           (Optional) Caller info, compiler generated. Please omit.
     * @param cmn           (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void SetLogger( cs.aworx.lib.enums.Switch newState, String loggerFilter,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // initialize caller information
                caller.Set( csf, cln, cmn
                                #if !ALOX_NO_THREADS
                                            , ThreadDictionary
                                #endif
                          );

                foreach ( Logger logger in loggers )
                {
                    if ( simpleWildcardFilter( logger, loggerFilter ) )
                    {
                        logger.IsDisabled= newState == cs.aworx.lib.enums.Switch.Off;

                        // log info on this
                        internalLog( Log.Level.Info,
                                     tempAS.Clear()._("SetLogger: Logger \"")
                                                   ._(logger.Name)._("\" ")
                                                   ._((logger.IsDisabled ? "disabled." : "enabled."))  );
                    }
                }

            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     *  This method is used reset (or to explicitly set) the start time of the logger(s).
     *  The only impact is the output of time differences in the log lines. Hence, it is useful to
     *  see some absolute time values when doing basic performance tests using the logger.
     *
     * @param startTime       (Optional) Optional parameter with the  new start time. Defaults
     *                        to DateTime.Now if omitted.
     * @param loggerFilter    (Optional) A filter for the loggers to be affected. A simple
     *                        string compare without case sensitivity is performed. An asterisk
     *                        ('*') at the beginning or end of the string is used as a
     *                        wildcard. Leave to \e null if all loggers should be affected.
     * @param csf             (Optional) Caller info, compiler generated. Please omit.
     * @param cln             (Optional) Caller info, compiler generated. Please omit.
     * @param cmn             (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void SetStartTime( DateTime? startTime= null, String loggerFilter= null,
       [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // initialize caller information
                caller.Set( csf, cln, cmn
                                #if !ALOX_NO_THREADS
                                            , ThreadDictionary
                                #endif
                          );

                // check if start time was set
                Ticks time= new Ticks( 0L );
                if ( startTime != null)
                    time.SetFromDotNetDateTime( startTime.Value );
                else
                    time.Set();

                // loop over all loggers
                foreach ( Logger logger in loggers )
                {
                    // logger filtered out? -> skip
                    if ( !simpleWildcardFilter( logger, loggerFilter ) )
                        continue;

                    // set new start time and last log time stamp
                    logger.TimeOfCreation.Set( time );
                    logger.TimeOfLastLog .Set( time );

                    // log info on this
                    internalLog( Log.Level.Info,
                                 tempAS.Clear()._("SetStartTime: Start time of \"")
                                               ._(logger.Name)._("\" set to: ")
                                               ._(startTime.HasValue? startTime.Value.ToString() : "\"now\"")
                                               ._('.')
                                );
                }

            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     *  This method sets a human readable name to the given thread ID (or current thread) which is
     *  optionally included in each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs
     * @param id            (Optional) Parameter providing the thread ID. If omitted, the
     *                      current thread's ID is used.
     * @param csf           (Optional) Caller info, compiler generated. Please omit.
     * @param cln           (Optional) Caller info, compiler generated. Please omit.
     * @param cmn           (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void MapThreadName( String threadName, int id= -1,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            #if !ALOX_NO_THREADS
                try { Lock.Acquire();

                    // get current thread id
                    String origThreadName= null;
                    if ( id < 0 )
                    {
                        Thread t=        Thread.CurrentThread;
                        id=                t.ManagedThreadId;
                        origThreadName= t.Name;
                    }

                    // add entry
                    ThreadDictionary[id]= threadName;

                    // log info on this
                    // initialize caller information
                    caller.Set( csf, cln, cmn
                                    #if !ALOX_NO_THREADS
                                                , ThreadDictionary
                                    #endif
                              );
                    tempAS.Clear()._("MapThreadName: Mapped thread ID ")
                                  ._(id)._(" to \"")._(threadName)._("\".");
                    if ( !String.IsNullOrEmpty( origThreadName )  )
                        tempAS._(" Original thread name was \"")._(origThreadName)._("\".");
                    internalLog( Log.Level.Info, tempAS );

                } finally { Lock.Release(); }
            #endif
        #endif
    }

    /** ********************************************************************************************
     *  This method is used store a marker object in the logging system. Markers are stored
     *  and retrieved relative to a given Log.Scope. In combination with Lox.GetMarker,
     *  this method provides an easy way to trace the last marked position, e.g. in the case of an
     *  exception. Within the exception handler, use Lox.GetMarker to retrieve the last marker
     *  object stored before the exception was thrown.
     *
     * @param marker  The object to store, for example a String that can be used for a
     *                log output later.
     * @param scope   The scope in which the marker should be stored. Markers and scopes
     *                work independently from each other. Different markers can be stored
     *                within different scopes and no fallback to "outer scopes" is made.
     *                A scope of 'None' stores the marker globally, hence as a system wide
     *                singleton.
     * @param csf     (Optional) Caller info, compiler generated. Please omit.
     * @param cln     (Optional) Caller info, compiler generated. Please omit.
     * @param cmn     (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void SetMarker( Object marker, Log.Scope scope,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // log info on this
                caller.Set( csf, cln, cmn
                                #if !ALOX_NO_THREADS
                                            , ThreadDictionary
                                #endif
                          );

                // build key string
                AString key= new AString(64);
                if ( scope == Log.Scope.None )
                    key._( "$GLOBAL" );
                else
                {
                    key._( csf );
                    if ( scope == Log.Scope.Method )
                        key._( '#' )._( cmn );
                }

                // save marker ([] overwrites any existing)
                markers[ key ]= marker;

                internalLog( Log.Level.Info,
                             tempAS.Clear()._("SetMarker: \"")
                                           ._(( marker != null ? marker.ToString() : "null"))
                                           ._('\"')  );

            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     *  Retrieves the most recently marker object stored using Lox.SetMarker. Markers are stored
     *  and retrieved relative to a given Log.Scope. In combination with Lox.SetMarker,
     *  this method provides an easy way to trace the last marked position, e.g. in the case of an
     *  exception. Within the exception handler, use this method to retrieve the last marker
     *  object stored before the exception was thrown.
     *
     * @param markerPointer   This is array is used to return the marker object. The array must
     *                        be at least of size 1. The object is stored in position 0. (Note:
     *                        due to compiler restrictions of C# V. 5.0, this laborious
     *                        approach for returning the object has been chosen. The function
     *                        can not return a value because it is conditionally compiled using
     *                        the ALOX_DBG_LOG compiler flag.
     * @param scope           The scope in which the marker should be stored. Markers and scopes
     *                        work independently from each other. Different markers can be stored
     *                        within different scopes and no fallback to "outer scopes" is made.
     *                        A scope of 'None' retrieves the global marker singleton.
     * @param csf             (Optional) Caller info, compiler generated. Please omit.
     * @param cln             (Optional) Caller info, compiler generated. Please omit.
     * @param cmn             (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void GetMarker( Object[] markerPointer, Log.Scope scope,
      [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                caller.Set( csf, cln, cmn
                                #if !ALOX_NO_THREADS
                                            , ThreadDictionary
                                #endif
                          );

                // build key string
                tempAS.Clear();
                if ( scope == Log.Scope.None )
                    tempAS._( "$GLOBAL" );
                else
                {
                    tempAS._( csf );
                    if ( scope == Log.Scope.Method )
                        tempAS._( '#' )._( cmn );
                }

                // get marker
                Object marker;
                markers.TryGetValue( tempAS, out marker );
                markerPointer[0]= marker;

                // log info on this
                internalLog( Log.Level.Info,
                             tempAS.Clear()._("GetMarker: \"")
                                           ._(( marker != null ? marker.ToString() : "null"))
                                           ._('\"') );
            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     *  This method logs the configuration this Lox and it's encapsulated objects.
     *
     * @param domain           If this is null, the default domain is used. If this is starting
     *                         with a swung dash ('~') this is interpreted a sub domain to the
     *                         default domain of the scope. For other values, the default
     *                         domain is ignored (regardless if this is starting with a slash or
     *                         not).
     * @param level            The log level.
     * @param headLine         If given, a separated headline will be logged at first place.
     * @param loggerFilter     (Optional) A filter for the loggers to be affected. This
     *                         parameter enables different loggers to have different domains. A
     *                         simple string compare without case sensitivity is performed. An
     *                         asterisk ('*') at the beginning or end of the string is used as a
     *                         wildcard. Leave to \e null if all loggers should be affected. Use this
     *                         parameter only in more complex logging scenarios.
     * @param csf              (Optional) Caller info, compiler generated. Please omit.
     * @param cln              (Optional) Caller info, compiler generated. Please omit.
     * @param cmn              (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void LogConfig( String            domain,
                            Log.Level         level,
                            String            headLine,
                            String            loggerFilter= null,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // setup
                caller.Set( csf, cln, cmn
                                #if !ALOX_NO_THREADS
                                            , ThreadDictionary
                                #endif
                          );
                evaluateResultDomain( domain );

                // count overall calls
                CntLogCalls++;

                // we write log all into a Buffer first
                AString buf=        new AString( 2048 );

                // log a headline?
                if ( !String.IsNullOrEmpty(headLine) )
                    buf._( headLine ).NewLine();

                // basic lox info
                buf._NC( "Version:         ")._( Log.Version )._NC(" (Rev. ")._( Log.Revision)._(')').NewLine();
                buf._NC( "Intern. Domain:  ")._NC( InternalDomain ).NewLine();
                buf._NC( "Thread-Safeness: ")._NC( Lock.IsUnsafe()  ? "No (!)" : "Yes" ).NewLine();
                buf._NC( "#Log Calls:      ")._  ( CntLogCalls    ).NewLine();

                // code markers
                if ( markers.Count > 0 ) buf.NewLine();
                buf._NC( "Code markers:    ")._( markers.Count  ).NewLine();
                foreach (  AString key in markers.Keys )
                {
                    Object o= markers[ key ];
                    buf._NC( "  Marker:    "  )._(  o != null ? o.ToString() : "null" )._('\"').NewLine();
                    buf._NC( "    Scope: \"" )._(  key ).NewLine();
                }

                // thread mappings
                if ( ThreadDictionary.Count > 0 )  buf.NewLine();
                buf._NC( "Named Threads:   " )._( ThreadDictionary.Count ).NewLine();
                foreach ( int key in ThreadDictionary.Keys )
                {
                    buf._NC( "  " ).Field()._('(')._(key)._( "):").Field( 7, Alignment.Left )
                                   ._('\"')._( ThreadDictionary[key] ) ._('\"');
                    buf.NewLine();
                }

                // default domains
                if ( defaultDomains.Count > 0 ) buf.NewLine();
                buf._NC( "Default Domains: ")._( defaultDomains.Count  ).NewLine();
                foreach (  AString key in defaultDomains.Keys )
                {
                    buf._( "  Domain:   " );
                    AString s= defaultDomains[ key ];
                    if ( s != null ) buf._NC( s ); else buf._NC( "null" );
                    buf.Tab( 25 );
                    buf._NC( "Scope: \"" );
                    buf._( key );
                    buf._( '\"' ).NewLine();
                }


                // Loggers (and their domains)
                if ( loggers.Count > 0 ) buf.NewLine();
                buf._( "Loggers:         ")._( loggers.Count    ).NewLine();
                StringBuilder timeOfCreationFB= new StringBuilder();
                foreach ( Logger logger in loggers )
                {
                    timeOfCreationFB.Clear();
                    timeOfCreationFB.AppendFormat( CultureInfo.InvariantCulture, "{0:yyyy-MM-dd HH:mm:ss}", logger.TimeOfCreation.InDotNetDateTime());
                    buf.NewLine();
                    buf._NC( "  Logger:  \""            )._NC(  logger.Name)._( '\"');
                    if ( !logger.Name.Equals( logger.TypeName) )
                        buf._NC( " Type: '" )._NC( logger.TypeName )._( '\'' );
                    buf.NewLine();
                    buf._NC( "    Creation Time: "     )._(  timeOfCreationFB ).NewLine();
                    buf._NC( "    Lines logged:  "     )._(  logger.CntLogs   ).NewLine();
                    buf._NC( "    Domains:"            )                       .NewLine();

                    foreach (Domain subDomain in logger.RootDomain.SubDomains)
                        logConfigDomainRecursive( subDomain, 3, "      " , buf);
                }

                // now, log it out
                Line( true, domain, level, buf, 0, loggerFilter, csf, cln, cmn );

            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     * Logs an object with log level equal to
     * \ref Log::Level::Verbose "Level.Verbose".
     * This is the most verbose log level, which is only actually logged if the log domains'
     * log level is set to
     * \ref Log::DomainLevel::All "DomainLevel.All".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Verbose( Object msg, int indent=    0,
      [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, null, Log.Level.Verbose, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a String with log level equal to
     * \ref Log::Level::Verbose "Level.Verbose".
     * This is the most verbose log level, which is only actually logged if the log domains'
     * log level is set to
     * \ref Log::DomainLevel::All "DomainLevel.All".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    // C# auto-boxes int arguments. This is why, we would get ambiguous invocations without this
    // otherwise redundant method.
    public  void Verbose( String msg, int indent=    0,
      [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, null, Log.Level.Verbose, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::Verbose "Level.Verbose".
     * This is the most verbose log level, which is only actually logged if the log domains'
     * log level is set to
     * \ref Log::DomainLevel::All "DomainLevel.All".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with
     *                  a swung dash ('~') this is interpreted a sub domain to the default domain
     *                  of the source file. For other values, the default domain is ignored
     *                  (regardless if this is starting with a slash or not).
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Verbose( String domain, Object msg, int indent= 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, domain, Log.Level.Verbose, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::Info "Level.Info".
     * The log operation is only executed if the resulting log domains' log level is set to
     * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel.InfoWarningsAndErrors" or
     * \ref Log::DomainLevel::All                   "DomainLevel.All".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Info( Object msg, int indent= 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true,  null, Log.Level.Info, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::Info "Level.Info".
     * The log operation is only executed if the resulting log domains' log level is set to
     * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel.InfoWarningsAndErrors" or
     * \ref Log::DomainLevel::All                   "DomainLevel.All".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    // C# auto-boxes int arguments. This is why, we would get ambiguous invocations without this
    // otherwise redundant method.
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Info( String msg, int indent= 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true,  null, Log.Level.Info, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::Info "Level.Info".
     * The log operation is only executed if the resulting log domains' log level is set to
     * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel.InfoWarningsAndErrors" or
     * \ref Log::DomainLevel::All                   "DomainLevel.All".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with
     *                  a swung dash ('~') this is interpreted a sub domain to the default domain
     *                  of the source file. For other values, the default domain is ignored
     *                  (regardless if this is starting with a slash or not).
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Info( String domain, Object msg, int indent= 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, domain, Log.Level.Info, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::Warning "Level.Warning".
     * This log level is enabled if the log domains' log level is set to
     * \ref Log::DomainLevel::All                   "DomainLevel.All",
     * \ref Log::DomainLevel::WarningsAndErrors     "DomainLevel.WarningsAndErrors" or
     * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel.InfoWarningsAndErrors".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Warning( Object msg, int indent= 0,
      [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, null, Log.Level.Warning, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::Warning "Level.Warning".
     * This log level is enabled if the log domains' log level is set to
     * \ref Log::DomainLevel::All                   "DomainLevel.All",
     * \ref Log::DomainLevel::WarningsAndErrors     "DomainLevel.WarningsAndErrors" or
     * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel.InfoWarningsAndErrors".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    // C# auto-boxes int arguments. This is why, we would get ambiguous invocations without this
    // otherwise redundant method.
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Warning( String msg, int indent= 0,
      [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, null, Log.Level.Warning, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::Warning "Level.Warning".
     * This log level is enabled if the log domains' log level is set to
     * \ref Log::DomainLevel::All                   "DomainLevel.All",
     * \ref Log::DomainLevel::WarningsAndErrors     "DomainLevel.WarningsAndErrors" or
     * \ref Log::DomainLevel::InfoWarningsAndErrors "DomainLevel.InfoWarningsAndErrors".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with
     *                  a swung dash ('~') this is interpreted a sub domain to the default domain
     *                  of the source file. For other values, the default domain is ignored
     *                  (regardless if this is starting with a slash or not).
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Warning( String domain, Object msg, int indent= 0,
      [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, domain, Log.Level.Warning, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::Error "Level.Error".
     * This log level is always enabled, unless the log domains' log level is set to
     * \ref Log::DomainLevel::Off  "DomainLevel.Off".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Error( Object msg, int indent= 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, null, Log.Level.Error, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::Error "Level.Error".
     * This log level is always enabled, unless the log domains' log level is set to
     * \ref Log::DomainLevel::Off  "DomainLevel.Off".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    // C# auto-boxes int arguments. This is why, we would get ambiguous invocations without this
    // otherwise redundant method.
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Error( String msg, int indent= 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, null, Log.Level.Error, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::Error "Level.Error".
     * This log level is always enabled, unless the log domains' log level is set to
     * \ref Log::DomainLevel::Off  "DomainLevel.Off".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with
     *                  a swung dash ('~') this is interpreted a sub domain to the default domain
     *                  of the source file. For other values, the default domain is ignored
     *                  (regardless if this is starting with a slash or not).
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Error( String domain, Object msg, int indent= 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, domain, Log.Level.Error, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object only if the given condition \p cond is not \e 'true'.
     * Log level will be highest, namely
     * \ref Log::Level::Error "Level.Error".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param cond      The log is only performed if condition is not true.
     * @param msg       An Object to be logged.
     * @param indent    (Optional) the indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Assert( bool cond, Object msg, int indent= 0,
     [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( !cond, null, Log.Level.Error, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an arbitrary object only if the given condition \p cond is not \e 'true'.
     * Log level will be highest, namely
     * \ref Log::Level::Error "Level.Error".
     *
     * @param cond      The log is only performed if condition is not true.
     * @param domain    If this is null, the default domain is used. If this is starting with
     *                  a swung dash ('~') this is interpreted a sub domain to the default
     *                  domain of the scope. For other values, the default domain is
     *                  ignored (regardless if this is starting with a slash or not).
     * @param msg       An Object to be logged.
     * @param indent    (Optional) the indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Assert( bool cond, String domain, Object msg, int indent= 0,
     [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( !cond, domain, Log.Level.Error, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     *  Provides a more flexible but complex way to log a message. The methods #Verbose(),
     *  #Info(), #Warning(), #Error() and #Assert() are using this function internally and should
     *  be used in standard cases. Use this function only in the rare cases, e.g. when a log level is
     *  decided only at runtime or when you want to use a logger filter, etc.
     *
     * @param doLog         Conditional logging. If false, the log is not performed. CntLogCalls
     *                      is still increased by one.
     * @param domain        If this is null, the default domain is used. If this is starting
     *                      with a swung dash ('~') this is interpreted a sub domain to the
     *                      default domain of the scope. For other values, the default
     *                      domain is ignored (regardless if this is starting with a slash or
     *                      not).
     * @param level         The log level.
     * @param msg           An Object to be logged.
     * @param indent        (Optional) The indentation in the output. Defaults to 0.
     * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
     *                      parameter enables different loggers to have different domains. A
     *                      simple string compare without case sensitivity is performed. An
     *                      asterisk ('*') at the beginning or end of the string is used as a
     *                      wildcard. Leave to \e null if all loggers should be affected. Use this
     *                      parameter only in more complex logging scenarios.
     * @param csf           (Optional) Caller info, compiler generated. Please omit.
     * @param cln           (Optional) Caller info, compiler generated. Please omit.
     * @param cmn           (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Line( bool doLog, String domain, Log.Level level, Object msg, int indent= 0, String loggerFilter= null,
       [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            // auto-initialization of ALox
            Log.Init();

            // auto-initialization of debug loggers
            if( loggers.Count == 0 && this == Log.LOX )
                Log.AddDebugLogger( this, true );
        #endif

        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Lock.Acquire();

                // count overall calls
                CntLogCalls++;

                // check the condition
                if ( doLog  && loggers.Count > 0 )
                {

                    // initialize caller information
                    caller.Set( csf, cln, cmn
                                    #if !ALOX_NO_THREADS
                                                , ThreadDictionary
                                    #endif
                              );

                    // setup domain
                    evaluateResultDomain( domain );

                    // loop over all loggers
                    bool dummy= false;
                    foreach ( Logger logger in loggers )
                        if ( simpleWildcardFilter( logger, loggerFilter ) )
                            if (!logger.Line( resDomain, level, msg, indent, caller ) )
                            {
                                tempAS._()._("Domain Resolution: Domain '"         )._(resDomain)
                                          ._("' implicitly registered for Logger '")._( logger.Name )
                                          ._("' Inherited DomainLevel: "           )
                                          ._(logger.RootDomain.Find( resDomain, ref dummy ).GetLevel().ToString());
                                internalLog( Log.Level.Info, tempAS );
                            }
                }

                // release lock if msg was our internal log buffer singleton
                if ( msg == logBuf )
                    logBufLock.Release();

            } finally { Lock.Release(); }
        #endif
    }

    /** ********************************************************************************************
     *  Logs an Object using the given log level, log domain and indentation and logger filter.
     *
     * @param domain        If this is null, the default domain is used. If this is starting
     *                      with a swung dash ('~') this is interpreted a sub domain to the
     *                      default domain of the scope. For other values, the default
     *                      domain is ignored (regardless if this is starting with a slash or
     *                      not).
     * @param level         The log level.
     * @param msg           An Object to be logged.
     * @param indent        (Optional) The indentation in the output. Defaults to 0.
     * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
     *                      parameter enables different loggers to have different domains. A
     *                      simple string compare without case sensitivity is performed. An
     *                      asterisk ('*') at the beginning or end of the string is used as a
     *                      wildcard. Leave to \e null if all loggers should be affected. Use this
     *                      parameter only in more complex logging scenarios.
     * @param csf           (Optional) Caller info, compiler generated. Please omit.
     * @param cln           (Optional) Caller info, compiler generated. Please omit.
     * @param cmn           (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Line( String           domain,
                      Log.Level        level,
                      Object           msg,
                      int              indent=                0,
                      String           loggerFilter=        null,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, domain, level, msg, indent, loggerFilter, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     *  Logs an Object using the given log level, indentation and logger filter and the default
     *  domain set for the scope.
     *
     * @param level         The log level.
     * @param msg           An Object to be logged.
     * @param indent        (Optional) The indentation in the output. Defaults to 0.
     * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
     *                      parameter enables different loggers to have different domains. A
     *                      simple string compare without case sensitivity is performed. An
     *                      asterisk ('*') at the beginning or end of the string is used as a
     *                      wildcard. Leave to \e null if all loggers should be affected. Use this
     *                      parameter only in more complex logging scenarios.
     * @param csf           (Optional) Caller info, compiler generated. Please omit.
     * @param cln           (Optional) Caller info, compiler generated. Please omit.
     * @param cmn           (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Line( Log.Level       level,
                      Object          msg,
                      int             indent=                0,
                      String          loggerFilter=        null,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Line( true, null, level, msg, indent, loggerFilter, csf,cln,cmn );
        #endif
    }

    //*****************************************************************************
    //***  internals
    //*****************************************************************************
    #if ALOX_DBG_LOG || ALOX_REL_LOG

        /** ****************************************************************************************
             *  Using the optionally provided domain and a default domain previously set according to
         *  the caller's scope. The resulting full domain string is evaluated as follows:
         *  If no domain given, the default domain is retrieved (depending on the caller's scope).
         *  If a domain is given it is used. If it is starting with a swung dash("~"), it is interpreted
         *  to be a sub domain of the default domain and both domains are concatenated.
         *
         * @param domain A domain or path. If starting with a swung dash ('~') it is interpreted as
         *               being a sub domain of the default domain defined for the current caller's
         *               scope.
         ******************************************************************************************/
        protected  void evaluateResultDomain( String domain )
        {
            // clear resulting domain name buffer
            resDomain.Clear();

            // get default domain name (if needed later)
            AString defaultDomain=    null;
            bool    noDomainGiven=    String.IsNullOrEmpty( domain );
            if ( noDomainGiven || domain[0] == '~' )
            {
                // get default domain
                tempAS.Clear()._( caller.SourceFileName );
                int strLengthSourceOnly= tempAS.Length();
                tempAS._( '#' )._( caller.MethodName );
                defaultDomains.TryGetValue( tempAS, out defaultDomain );
                if ( defaultDomain == null || defaultDomain.IsEmpty() )
                {
                    tempAS.SetLength_NC( strLengthSourceOnly );
                    defaultDomains.TryGetValue( tempAS, out defaultDomain );
                }
            }

            // no domain given
            if ( noDomainGiven )
            {
                if (  defaultDomain != null && defaultDomain.IsNotEmpty() )
                {
                    // return resulting domain
                    resDomain._( defaultDomain );
                    return;
                }
                // neither domain nor default domain given


                if ( ErrIfNoDefaultDomain > 0 )
                {
                    ErrIfNoDefaultDomain--;
                    tempAS.Clear()._("Domain Resolution: No log domain given and default domain not set for scope \"")
                                  ._(caller.SourceFileName)
                                  ._(" - ")._(caller.SourceFileName)._("\".");

                    internalLog( Log.Level.Error, tempAS );
                }
                resDomain._( NullDomain );
                return;
            }

            // domain starts with '~' ?    Relative path
            int start=    0;
            if ( domain[0] == '~' )
            {
                // cut the ~ character
                start=    1;

                // found one? build complete path
                if ( defaultDomain != null )
                    resDomain._( defaultDomain );
                else
                {
                    // not set? -> remove the ~ symbol and go ahead
                    internalLog( Log.Level.Error,
                                 tempAS.Clear()._("Domain Resolution: Relative domain path given: \"")._(domain)
                                               ._("\", but default domain is not set for scope \"")
                                               ._(caller.SourceFileName)._(" - ")._(caller.MethodName)._("\".")
                                );
                }
            }

            // remove any potential leading separator
            int len=    domain.Length;
            while (start < len && ( Domain.DomainSeparatorChars.IndexOf( domain[ start ] ) >= 0 ) )
                start++;

            // add domain to the path
            if (start < len )
            {
                if ( resDomain.IsNotEmpty() )
                    resDomain._( '/' );
                int oldLength= resDomain.Length();
                resDomain._NC( domain, start, len-start );
                resDomain.ToUpper( oldLength );
            }
        }

        /** ****************************************************************************************
         *  Logs an internal error message to the domain given by field InternalDomain. Attn: must only
         *  be called after saveAndSet() was performed.
         *
         * @param level    The log level.
         * @param msg      The message.
         ******************************************************************************************/
        protected  void internalLog( Log.Level level, AString msg )
        {
            // decrease log counter, as internal Log should not count
            CntLogCalls--;

            // log msg on InternalDomain
            String backup= resDomain.ToString();
            Line( true, InternalDomain, level, msg, 0, null, caller.SourceFileName, caller.LineNumber, caller.MethodName );
            resDomain._()._(backup);

            // reset the caller timestamp to avoid negative time differences in subsequent log call
            caller.TimeStamp.Set();
        }

        /** ****************************************************************************************
         *  Compares a loggers name with a filter string with simplest wildcard support ('*') at the
         *  beginning or end of the string. If loggerFilter is null, a match is indicated.
         *
         * @param logger          The logger to be filtered.
         * @param loggerFilter    The filter.
         * @return  True if logger is not filtered out.
         ******************************************************************************************/
        private static bool simpleWildcardFilter( Logger logger, string loggerFilter )
        {
            const string asterisk = "*";

            // null or empty? -> return TRUE (!)
            if ( String.IsNullOrEmpty( loggerFilter ) )
                return true;

            // wildcard at start?
            bool startWC= false;
            if ( loggerFilter[0] == '*' )
            {
                loggerFilter=    loggerFilter.Substring( 1 );
                startWC=        true;
            }

            // wildcard at end?
            bool endWC= false;
            if ( loggerFilter.EndsWith ( asterisk ) )
            {
                loggerFilter=    loggerFilter.Substring( 0, loggerFilter.Length - 1 );
                endWC=        true;
            }

            // wildcard at start?
            if ( startWC )
            {
                // both?
                if ( endWC )
                    return logger.Name.IndexOf   ( loggerFilter, StringComparison.OrdinalIgnoreCase ) >= 0;

                // at start only
                return logger    .Name.EndsWith  ( loggerFilter, StringComparison.OrdinalIgnoreCase );
            }

            // at end
            if ( endWC )
                return logger    .Name.StartsWith( loggerFilter, StringComparison.OrdinalIgnoreCase );

            // no wildcard
            return logger        .Name.Equals    ( loggerFilter, StringComparison.OrdinalIgnoreCase );
        }

        /** ****************************************************************************************
         * Internal method used by LogConfig() to recursively log Domain instances.
         * @param domain     The Domain instance to log out.
         * @param indent     The indentation in the output, recursively increased..
         * @param domPath    Actual path relative to recursion, solely for log output.
         * @param buf        The buffer to log to.
         ******************************************************************************************/
        protected  void logConfigDomainRecursive( Domain domain, int indent, String domPath, AString buf)
        {
            // append /ME to domain path string
            domPath= domPath + "/" + domain.Name;

            // add  domain name and log level
            buf._( domPath  ).Tab( 25 )._( domain.GetLevel().ToString() )  .NewLine();

            // loop over all sub domains (recursion)
            foreach ( Domain subDomain in domain.SubDomains )
                logConfigDomainRecursive( subDomain, indent + 1, domPath, buf );
        }

    #endif // ALOX_DBG_LOG || ALOX_REL_LOG
}




} // namespace
