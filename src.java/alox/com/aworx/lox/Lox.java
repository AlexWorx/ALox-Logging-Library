// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

/** ************************************************************************************************
 *  This is the Java package for code of the <em>%ALox Logging Library</em>.
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
package com.aworx.lox;

import java.text.FieldPosition;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Locale;
import java.util.Vector;

import com.aworx.lib.ALIB;
import com.aworx.lib.enums.*;
import com.aworx.lib.strings.*;
import com.aworx.lib.threads.ThreadLock;
import com.aworx.lib.time.Ticks;
import com.aworx.lox.core.*;
import com.aworx.lox.core.textlogger.TextLogger;
import com.aworx.lox.loggers.*;

/** ************************************************************************************************
 * This class acts as a container for Loggers and provides a convenient interface to logging.
 * Fore information how to use this class, checkout the ALox tutorials and the ALox manual.
 **************************************************************************************************/
public class Lox extends ThreadLock
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

        /**
         * A counter for the quantity of calls. The count includes logs that were suppressed by
         * disabled <em>Log Domain</em> and those suppressed by the optional log condition parameter.
         */
        public int                  cntLogCalls                                                 = 0;

        /**
         * A list of prefixes of \e 'packages.classes.methods' on the stack that are ignored when
         * identifying the scope info.
         * Usually this contains \e "com.aworx.lox" and \e "com.aworx.lib" and there is no need
         * to change this.
         */
        public Vector<String>       omittablePackagePrefixes;

        /**
         * Denotes if <em>Log Domains</em> are searched ignoring the letter case or being sensitive
         * about it.<br>
         * Defaults to \p Case::IGNORE.
         */
        public Case                 domainSensitivity                                 = Case.IGNORE;

        /**
         * Constant providing default value for parameter \p priority of method #setVerbosity.
         * This value is defined in alignment with plug-in priority constants found in
         * ALib class \b %Configuration, namely
         * - \ref com::aworx::lib::config::Configuration::PRIO_CMD_LINE "Configuration.PRIO_CMD_LINE"
         *   with a value of of 400,
         * - \ref com::aworx::lib::config::Configuration::PRIO_ENV_VARS "Configuration.PRIO_ENV_VARS"
         *   with a value of 300 and
         * - \ref com::aworx::lib::config::Configuration::PRIO_INI_FILE "Configuration.PRIO_INI_FILE"
         *   with a value of 200.
         *
         * Having a value of 100, source code settings by default have lowest priority.
         */
        public static final   int   PRIO_SOURCE                                               = 100;

        /**
         * Constant providing the maximum value for parameter \p priority of method #setVerbosity.
         * A \e Verbosity set with this priority is immutable in respect to external configuration
         * data.
         */
        public static final   int   PRIO_PROTECTED                              = Integer.MAX_VALUE;


    // #############################################################################################
    // Private/protected fields
    // #############################################################################################

    /**
     * The root domain \"/\". All registered domains become a sub domain of this root.
     * If a <em>Sub-Log Domains' Verbosity</em> is not explicitly set, such sub domain inherits the
     * verbosity of its parent.
     */
    protected Domain                domains;

    /**
     * The root domain for internal <em>Log Domains</em>.
     */
    protected Domain                internalDomains;

    /** Scope Domains .*/
    protected ScopeStore<AString>                   scopeDomains;

    /** Log Data */
    protected ScopeStore<HashMap<AString, LogData>> scopeLogData;

    /** Log once counters */
    protected ScopeStore<HashMap<AString, int[]>>   scopeLogOnce;

    /** Prefix logables store */
    protected         ScopeStore<Object>            scopePrefixes;

    /** Information about the source code, method, thread, etc. invoking a log  call */
    protected ScopeInfo             scopeInfo;

    /**
     *  Dictionary to translate thread IDs into something maybe nicer/shorter.
     *  The dictionary has to be filled by the user of the library.
     */
    protected HashMap<Long, String> threadDictionary                  = new HashMap<Long, String>();

    /** The resulting domain name. */
    protected AString               resDomain                                   = new AString( 32 );

    /** The resulting domain name for internal logs. */
    protected AString               resDomainInternal                           = new AString( 32 );

    /** An AString singleton. Can be acquired, using buf() */
    protected AString               logBuf                                     = new AString( 128 );

    /** A locker for the log buffer singleton */
    protected ThreadLock            logBufLock                                   = new ThreadLock();

    /**  A temporary AString, following the "create once and reuse" design pattern. */
    protected AString               intMsg                                     = new AString( 256 );

    /** A temporary AString  */
    protected AString               tmpAS                                       = new AString( 64 );

    /** A temporary AString  */
    protected AString               tmpConfigValue                                  = new AString();

    /**  A temporary object following the "create once and reuse" design pattern. */
    protected boolean[]             booleanOutputParam                             = new boolean[1];

    /** Used for tabular output of logger lists */
    protected int                   maxLoggerNameLength                                         = 0;

    /** Used for tabular output of logger lists */
    protected int                   maxDomainPathLength                                         = 0;

    /** A key value used in stores if no key is given (global object).  */
    protected final static String   noKeyHashKey                                              = "$";

    /** The list of collected log objects which is passed to the \e Loggers  */
    protected ArrayList<Object>     tmpLogables                            = new ArrayList<Object>();

    /** Rule types */
    public enum  DSRType
    {
        EXACT,        ///< Exact match
        STARTS_WITH,  ///< Starts with match
        ENDS_WIDTH,   ///< Ends with match
        SUBSTRING     ///< Any sub-string
    }

    /**  Domain substitution rules.  */
    public class DomainSubstitutionRule
    {
        public DSRType type;                       ///< Denotes if path given started with '*' or not.
        public AString search     = new AString(); ///< The path to search.
        public AString replacement= new AString(); ///< The replacement.

        /**  Constructor.
         * @param s The path to search.
         * @param r The replacement.
        */
        public DomainSubstitutionRule( String s, String r )
        {
            // get type and adjust given search parameter
            int startPos=   0;
            int length=     s.length();
            if ( s.charAt(0) == '*' )
            {
                startPos++;
                length--;
                if ( s.charAt(length) == '*' )
                {
                    type= DSRType.SUBSTRING;
                    length--;
                }
                else
                    type= DSRType.ENDS_WIDTH;
            }
            else
            {
                if ( s.charAt(length-1) == '*' )
                {
                    type= DSRType.STARTS_WITH;
                    length--;
                }
                else
                    type= DSRType.EXACT;
            }
            search._( s, startPos, length );

            // minimum rule check
            if (   (     (    type == DSRType.EXACT
                           || type == DSRType.STARTS_WITH )
                     && !search.startsWith( "/" )
                    )
                || (    type == DSRType.ENDS_WIDTH
                    &&  search.endsWith( "/" )
                   )
               )
                search._(); // illegal rule

            replacement._(r);
        }
    };

    /**  The list of domain substitution rules.  */
    protected ArrayList<DomainSubstitutionRule> domainSubstitutions= new ArrayList<DomainSubstitutionRule>();

    /**  Temporary string used with domain substitutions.  */
    protected AString               tmpSubstitutionPath                         = new AString( 64 );

    /**  Temporary string used with domain substitutions.  */
    protected AString               tmpSubstitutionPathInternalDomains          = new AString( 64 );

    /**  Flag if a warning on circular rule detection was logged.  */
    protected boolean               oneTimeWarningCircularDS                                 =false;

    // #############################################################################################
    // Constructors
    // #############################################################################################

    /** ****************************************************************************************
     * Constructs a new, empty Lox with the given \p name.
     * The name is immutable and all \b %Lox objects registered with ALox must be unique.
     * Lower case letters in the name are converted to upper case.
     * The name \c "Log" is reserved for the internal default singleton used for debug-logging.
     *
     * If parameter \p register is \c true (the default), static method
     * \ref com::aworx::lox::ALox::register "ALox.register" is invoked and the object will be
     * retrievable with static method
     * \ref com::aworx::lox::ALox::get "ALox.get". In some situations, such 'registration'
     * may not be wanted.
     *
     * @param name       The name of the Lox. Can be logged out, e.g. by setting
     *                   com::aworx::lox::textlogger::MetaInfo::Format "MetaInfo.Format"
     *                   accordingly.
     * @param doRegister If \c true, this object is registered with static class
     *                   \ref com::aworx::lox::ALox "ALox".
     *                   Optional and defaults to \c true.
     ******************************************************************************************/
    public Lox( String name, boolean doRegister )
    {
        construct( name, doRegister );
    }

    /** ****************************************************************************************
     * Overloaded constructor providing value \c true for parameter \p doRegister.
     * @param name       The name of the Lox. Can be logged out, e.g. by setting
     *                   com::aworx::lox::textlogger::MetaInfo::Format "MetaInfo.Format"
     *                   accordingly.
     ******************************************************************************************/
    public Lox( String name )
    {
        construct( name, true );
    }

    /** ****************************************************************************************
     * Protected constructor helper method
     * @param name       The name of the Lox. Can be logged out, e.g. by setting
     *                   com::aworx::lox::textlogger::MetaInfo::Format "MetaInfo.Format"
     *                   accordingly.
     * @param doRegister If \c true, this object is registered with static class
     *                   \ref com::aworx::lox::ALox "ALox".
     *                   Optional and defaults to \c true.
     ******************************************************************************************/
    protected void construct( String name, boolean doRegister )
    {
        // uncomment this for debugging deadlocks
        // createOwnerStackTrace= true;

        // set recursion warning of log buffer lock to 1. Warnings are logged if recursively
        // acquired more than once
        logBufLock.recursionWarningThreshold= 1;

        // set packages that might be omitted
        omittablePackagePrefixes= new Vector<String>();
        omittablePackagePrefixes.add( "com.aworx.lib" );
        omittablePackagePrefixes.add( "com.aworx.lox" );

        // create scope info
        scopeInfo=      new ScopeInfo( name,  threadDictionary, omittablePackagePrefixes );
        scopeDomains=   new ScopeStore<AString                  >( scopeInfo, false );
        scopeLogData=   new ScopeStore<HashMap<AString, LogData>>( scopeInfo, true  );
        scopeLogOnce=   new ScopeStore<HashMap<AString, int[]>  >( scopeInfo, true  );
        scopePrefixes=  new ScopeStore<Object                   >( scopeInfo, false );


        // create domain trees
        domains= new Domain( null, new AString( "" ) );
        internalDomains= new Domain( null,
                                     new AString( ALox.INTERNAL_DOMAINS,
                                                  0,
                                                  ALox.INTERNAL_DOMAINS.length() - 1 )  );

        // create internal sub-domains
        String[] internalDomainList= {"LGR", "DMN", "PFX", "THR", "LGD" };
        for ( String it : internalDomainList )
        {
            resDomainInternal._()._( it );
            internalDomains.find( resDomainInternal, Case.SENSITIVE, 1, booleanOutputParam );
        }
        maxDomainPathLength= ALox.INTERNAL_DOMAINS.length() + 3;

        // register with ALox
        if ( doRegister )
            ALox.register( this, ContainerOp.INSERT );

        // read domain substitution rules from configuration
        {
            tmpAS._()._( getName() )._( "_DOMAIN_SUBSTITUTION" );
            tmpConfigValue._();
            if ( ALIB.config.get( ALox.configCategoryName, tmpAS, tmpConfigValue ) != 0 )
            {
                Tokenizer tok= new Tokenizer();
                tok.set( tmpConfigValue, ';' );
                Substring rule;
                while( (rule= tok.next()).isNotEmpty() )
                {
                    int idx= rule.indexOf( "->" );
                    if ( idx > 0 )
                    {
                        String domainPath=  rule.toString( 0, idx ).trim();
                        String replacement= rule.toString( idx + 2 ).trim();
                        setDomainSubstitutionRule( domainPath, replacement );
                    }
                }
            }

        }

    }

    // #############################################################################################
    // Interface
    // #############################################################################################

    /** ********************************************************************************************
     * Returns the name of this \b %Lox. The name user defined, provided in the constructor,
     * converted to upper case and otherwise immutable.
     *
     * @returns The name of this %Lox.
     **********************************************************************************************/
    public String    getName()                      { return scopeInfo.getLoxName();               }

    /** ********************************************************************************************
     * Status of registration with ALox. To keep a \b %Lox "private" using parameter
     * \p doRegister of the constructor, allows to suppress registration.
     * Registered instances of this class can be statically received (by their name) using
     * \ref com::aworx::lox::ALox::get "ALox.get".
     *
     * @returns \c true if this instance was registered with ALox, \c false if not.
     **********************************************************************************************/
    public boolean   isRegistered()                 { return ALox.get( getName() ) == this;        }

    /** ********************************************************************************************
     * Returns an AString singleton, similar to the LogBuf singleton returned by Log.buf().
     * Whenever this method is called, the returned AString object has to be used as a message
     * within one of the log methods of this class
     * (error(), warning(), info(), verbose(), if(), once() or entry()) .
     * If this is not done, the object does not get released and parallel threads using
     * it would block! So, do not use buf() for other reasons than for creating log messages and
     * be sure to re-acquire the AString object by calling this method again prior to the next
     * log call.
     *
     * @return the static AString singleton.
     **********************************************************************************************/
    public AString buf()
    {
        logBufLock.acquire();
        logBuf.clear();
        return logBuf;
    }

    /** ********************************************************************************************
     *  Use this method when you want to abort a log call that you "started" with acquiring the
     *  internal AString singleton acquired using method buf(). Use bufAbort() only if you did not
     *  use the acquired buffer as a parameter of a log method, because this internally releases the
     *  buf already.
     **********************************************************************************************/
    public void bufAbort()
    {
        logBufLock.release();
    }

    /** ************************************************************************************
     *  This static method creates an adequate/default console logger.
     *  Currently, there is no detection mechanism implemented in the Java implementation
     *  of ALox. This might change in the future.
     *
     *  Hence, unless configuration variable
     *  [ALOX_CONSOLE_TYPE](../group__GrpALoxConfigVars.html) is set, this method creates
     *  a logger of type
     *  \ref com::aworx::lox::loggers::ConsoleLogger "ConsoleLogger".
     *
     *  @param name  The name of the \e Logger.  A value of null implies standard logger names
     *               defined in the \e Logger sub-classes.

     *  @return      The TextLogger that was chosen.
     **************************************************************************************/
    public static TextLogger createConsoleLogger(String name)
    {
        //--- check environment "ALOX_CONSOLE_TYPE". They have precedence ---
        AString consoleMode= new AString();
        if (ALIB.config.get( ALox.configCategoryName, "CONSOLE_TYPE", consoleMode ) != 0)
        {
            if (consoleMode.equals( "PLAIN", Case.IGNORE )) return new ConsoleLogger( name );
            if (consoleMode.equals( "ANSI", Case.IGNORE ))
                return new AnsiConsoleLogger( name );

            else if (consoleMode.equals( "DEFAULT", Case.IGNORE ))
            {
            }
            else
            {
                ALIB.WARNING( "Unrecognized value in config variable: ALOX_CONSOLE_TYPE =" + consoleMode );
            }
        }

        //--- in JAVA, we currently have no detection.
        return new ConsoleLogger( name );
    }

    /** ************************************************************************************
     * Overloaded method providing default parameter \c null.
     *
     *  @return      The TextLogger that was chosen.
     **************************************************************************************/
    public static TextLogger createConsoleLogger()
    {
        return createConsoleLogger( null );
    }

    /** ********************************************************************************************
     * Retrieves an instance of a Logger by its name. This might be useful when access to a
     * \e %Logger is needed to change its configuration.
     *
     * @param loggerName    The name of the \e Logger to search for (case insensitive).
     * @return The logger, null if not found.
     **********************************************************************************************/
    public Logger getLogger(String loggerName)
    {
        try { acquire();

            // search logger
            Logger logger;
            if ((logger=         domains.getLogger( loggerName )) != null) return logger;
            if ((logger= internalDomains.getLogger( loggerName )) != null) return logger;

            // not found
            logInternal( Verbosity.WARNING, "LGR", intMsg._()._( "No logger named \"" )._( loggerName )._( "\" found." ) );
            return null;

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Removes a logger from this container.
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref setVerbosity  "setVerbosity( logger, Verbosity.OFF )"
     *       can be used.
     *
     * @param logger   The logger to be removed.
     * @returns \c true, if the \e Logger was found and removed, \c false otherwise.
     **********************************************************************************************/
    public boolean removeLogger(Logger logger)
    {
        try { acquire();

            boolean found= false;
            int no;
            if ((no= domains.getLoggerNo( logger )) >= 0)
            {
                found= true;
                domains.removeLogger( no );
            }
            if ((no= internalDomains.getLoggerNo( logger )) >= 0)
            {
                found= true;
                internalDomains.removeLogger( no );
            }

            if (found)
                logger.removeAcquirer( this );
            else
            {
                logInternal( Verbosity.WARNING, "LGR",
                        intMsg._()._( "Logger \"" )._( logger )._( "\" not found. Nothing removed." ) );
            }
            return found;
        }
        finally { release(); }
    }

    /** ********************************************************************************************
     * Removes logger named \p loggerName from this container.
     *
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref setVerbosity  "setVerbosity( logger, Verbosity.OFF )"
     *       can be used.
     *
     * @param loggerName  The name of the \e Logger(s) to be removed (case insensitive).
     * @returns The logger that was removed, \c null if not found.
     **********************************************************************************************/
    public Logger removeLogger(String loggerName)
    {
        try
        { acquire();

            scopeInfo.set( owner );

            Logger logger= null;
            int no;

            if ((no= domains.getLoggerNo( loggerName )) >= 0)
            {
                logger= domains.getLogger( no );
                domains.removeLogger( no );
            }

            if ((no= internalDomains.getLoggerNo( loggerName )) >= 0)
            {
                logger= internalDomains.getLogger( no );
                internalDomains.removeLogger( no );
            }

            if (logger != null)
            {
                logger.removeAcquirer( this );

                logInternal( Verbosity.INFO, "LGR", intMsg._()._( "Logger \"" )._( logger )._( "\" removed." ) );
            }
            else
                logInternal( Verbosity.WARNING, "LGR", intMsg._()._( "Logger \"" )._( loggerName )
                                                             ._( "\" not found. Nothing removed." ) );
            return logger;
        }
        finally { release(); }
    }

    /** ********************************************************************************************
     * Sets the \e %Verbosity of the <em>Log Domain</em> which is evaluated from parameter \p domain and
     * applicable <em>Scope Domains</em>. The \p verbosity given, is set recursively for all sub-domains.
     *
     * With the first invocation of this method for a distinct \p logger, this \e %Logger
     * is registered with this \e %Lox. In this case, prior to setting the given \e Verbosity
     * for the evaluated sub-domain, the \e Verbosity for all domains is set to
     * \b %Verbosity.Off.
     *
     * To unregister a \e Logger with a \b Lox, use method #removeLogger.
     * To 'disable' a \e Logger, invoke this method with parameters \p verbosity equaling to
     * \b %Verbosity.Off and \p domain to \c "/".
     *
     * Optional parameter \p priority defaults to #PRIO_SOURCE, which is a lower priority
     * than those of the standard plug-ins of external configuration data. Therefore, external
     * configuration by default 'overwrite' settings made from 'within the source code', which
     * simply means by invoking this method.<br>
     * The parameter can be provided for two main reasons:
     * - To 'lock' a verbosity setting against external manipulation.
     * - to 'break' the standard mechanism that an invocation of this method sets all
     *   sub-domains recursively. If a sub-domain was set with a higher priority
     *   (e.g. <c>%PRIO_SOURCE + 1</c>, then this sub-domain will not be affected by
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
     *   methods of this class, it defaults to an empty string.<p>
     * \attention
     *   Even when using an absolute domain path, <em>%Scope Domains</em> of
     *   \e %Scope.THREAD_INNER, will still apply. This means that from within a thread that
     *   has such <em>%Scope Domain</em> set, this method is (almost) not usable!
     *   This all aligns with the concept (advice), that \e Loggers and their \e %Verbosity
     *   are generally set outside of such scopes, hence in configuration sections of a
     *   process.<p>
     * \attention
     *   Consequently, this method may be (mis-) used to modify the 'actual' (default) scope
     *   when explicitly giving an empty string with parameter \p domain. This is useful, to
     *   temporarily adjust a scope. But remember: %ALox was designed to avoid temporary code
     *   lines...
     *
     * @param logger     The logger to be to be affected (case insensitive).
     * @param verbosity  The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     * @param priority   The priority of the setting. Defaults to #PRIO_SOURCE, which is
     *                   a lower priority than standard plug-ins of external configuration
     *                   have.
     **********************************************************************************************/
    public void setVerbosity(Logger logger, Verbosity verbosity, String domain, int priority )
    {
        try { acquire();

            // initialize scope information
            scopeInfo.set( owner );

            // check
            if (logger == null)
            {
                logInternal( Verbosity.ERROR, "LGR", intMsg._()._( "Given Logger is \"null\". Verbosity not set." ) );
                return;
            }

            // this might create the (path of) domain(s) and set the \e Loggers' verbosity like their
            // first parent's or as given in configuration
            Domain dom= evaluateResultDomain( domain );

            // search logger, insert if not found
            boolean isNewLogger= false;
            int no= dom.getLoggerNo( logger );

            if (no < 0)
            {
                no= dom.addLogger( logger );

                // error, logger with same name already exists
                if (no < 0)
                {
                    logInternal( Verbosity.ERROR, "LGR",
                            intMsg._()._( "Unable to add logger \"" )._( logger )._( "\". Logger with same name exists." ) );

                    logInternal( Verbosity.VERBOSE, "LGR", intMsg._()
                              ._NC( "  Request was: setVerbosity( \"")._(logger)._NC("\", \"")
                              ._(dom.fullPath)  ._NC("\", Verbosity.")
                              ._NC(verbosity)   ._NC(", ")
                              ._NC(priority)    ._NC(" )" )    );

                    Logger existingLogger= dom.getLogger( logger.getName() );
                    logInternal( Verbosity.VERBOSE, "LGR", intMsg._()._( "  Existing Logger: \"" )._( existingLogger )
                            ._( '\"' ) );

                    return;
                }

                // We have to register with the SmartLock facility of the \e Logger.
                // But only if we have not done this yet, via the 'other' root domain tree
                if ( (dom.getRoot() == domains ? internalDomains.getLoggerNo( logger )
                                               :         domains.getLoggerNo( logger ) ) < 0 )
                    logger.addAcquirer( this );

                // store size of name to support tabular internal log output
                String loggerName= logger.toString();
                if (maxLoggerNameLength < loggerName.length()) maxLoggerNameLength= loggerName.length();

                // for internal log
                isNewLogger= true;
            }

            // do
            Verbosity newVerbosity= dom.setVerbosity( no, verbosity, priority );

            // log info on this
            if (isNewLogger)
            {
                logInternal(
                        Verbosity.INFO,
                        "LGR",
                        intMsg._()._( "Logger \"" )._( logger )
                                ._( domain.startsWith( ALox.INTERNAL_DOMAINS ) ?
                                        "\" added for internal log messages." : "\" added." ) );

                // we have to get all verbosities of already existing domains
                getAllVerbosities( logger, domains         , null, 0 );
                getAllVerbosities( logger, internalDomains , null, 0 );
            }

            intMsg._()._("Logger \"")._( logger )._NC( "\":").tab(11 + maxLoggerNameLength)
                      ._('\"')._NC( dom.fullPath )._( "\" = Verbosity." );
                      ALox.toString( verbosity, priority, intMsg ).trimEnd()._('.');
            if( newVerbosity != verbosity )
                intMsg._( " Lower priority (")._( priority )
                      ._(" < ")._(dom.getPriority(no))
                      ._( "). Remains " )._NC( newVerbosity )._( '.' );
            logInternal( Verbosity.INFO, "LGR", intMsg );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(Logger,Verbosity,String) "setVerbosity" providing
     * default value \c PRIO_SOURCE for parameter \p priority.
     *
     * @param logger     The logger to be to be affected.
     * @param verbosity  The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     **********************************************************************************************/
    public void setVerbosity(Logger logger, Verbosity verbosity, String domain)
    {
        setVerbosity( logger, verbosity, domain, PRIO_SOURCE );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(Logger,Verbosity,String) "setVerbosity" providing
     * - default value \c PRIO_SOURCE for parameter \p priority and
     * - default value <c> '/'</c> for parameter \p domain.
     *
     * @param logger     The logger to be to be affected.
     * @param verbosity  The 'level of verboseness' to be set.
     **********************************************************************************************/
    public void setVerbosity(Logger logger, Verbosity verbosity)
    {
        setVerbosity( logger, verbosity, "/" , PRIO_SOURCE );
    }

    /** ********************************************************************************************
     * Same as \ref #setVerbosity(Logger,Verbosity,String) "setVerbosity" but
     * addressing the \e %Logger to manipulate by its name.<br>
     * This method may only be used after a \e %Logger was once 'registered' with this \b %Lox
     * using \ref #setVerbosity(Logger,Verbosity,String) "setVerbosity".
     *
     * @param loggerName The logger to be to be affected, identified by its name (case
     *                   insensitive).
     * @param verbosity  The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     * @param priority   The priority of the setting. Defaults to #PRIO_SOURCE, which is
     *                   a lower priority than standard plug-ins of external configuration
     *                   have.
     **********************************************************************************************/
    public void setVerbosity(String loggerName, Verbosity verbosity, String domain, int priority)
    {
        try { acquire();

            scopeInfo.set( owner );

            // this might create the (path of) domain(s) and set the \e Loggers' verbosity like their first parent's
            Domain dom= evaluateResultDomain( domain );

            // get logger
            int no= dom.getLoggerNo( loggerName );
            if (no < 0)
            {
                // we have to check if the logger was added in the 'other' tree
                Domain actualTree= dom.getRoot();
                Domain otherTree=  actualTree == domains ? internalDomains
                                                         : domains;
                no= otherTree.getLoggerNo( loggerName );
                if ( no >= 0 )
                {
                    setVerbosity( otherTree.getLogger( no ),      Verbosity.OFF,
                                  actualTree.fullPath.toString(), Lox.PRIO_SOURCE      );
                    no= dom.getLoggerNo( loggerName );
                    ALIB.ASSERT( no >= 0 );
                }
                else
                {
                    intMsg._()._NC( "Logger not found. Request was: setVerbosity( \"")._(loggerName)._NC("\", \"")
                              ._(dom.fullPath)  ._NC("\", ")
                              ._NC(verbosity)   ._NC(", Verbosity.")
                              ._NC(priority)    ._NC(" )." );
                    logInternal( Verbosity.WARNING, "LGR", intMsg );
                    return;
                }
            }

            // do
            Verbosity newVerbosity= dom.setVerbosity( no, verbosity, priority );

            // log info on this
            intMsg._()._("Logger \"")._( dom.getLogger( no ) )._NC( "\":").tab(11 + maxLoggerNameLength)
                      ._('\"')._NC( dom.fullPath )._( "\" = Verbosity." );
                      ALox.toString( verbosity, priority, intMsg ).trimEnd()._('.');
            if( newVerbosity != verbosity )
                intMsg._( " Lower priority (")._( priority )
                      ._(" < ")._(dom.getPriority(no))
                      ._( "). Remains " )._NC( newVerbosity )._( '.' );
            logInternal( Verbosity.INFO, "LGR", intMsg );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(String,Verbosity,String,int) "setVerbosity" providing
     * default value \c PRIO_SOURCE for parameter \p priority.
     *
     * @param loggerName  The logger to be to be affected, identified by its name (case
     *                    insensitive).
     * @param verbosity   The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     **********************************************************************************************/
    public void setVerbosity(String loggerName, Verbosity verbosity, String domain)
    {
        setVerbosity( loggerName, verbosity, domain, PRIO_SOURCE );
    }


    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(String,Verbosity,String,int) "setVerbosity" providing
     * - default value \c PRIO_SOURCE for parameter \p priority and
     * - default value <c> '/'</c> for parameter \p domain.
     *
     * @param loggerName  The logger to be to be affected, identified by its name (case
     *                    insensitive).
     * @param verbosity   The 'level of verboseness' to be set.
     **********************************************************************************************/
    public void setVerbosity(String loggerName, Verbosity verbosity)
    {
        setVerbosity( loggerName, verbosity, "/", PRIO_SOURCE );
    }

    /** ********************************************************************************************
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
     *
     * To remove a previously set Scope Domain a nulled or empty string has to be passed with
     * parameter \p scopeDomain.
     *
     * For \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER, passing an empty or nulled string
     * removes the most recently added domain path. For removing an explicitly named
     * domain path of \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER use method
     * #removeThreadDomain.
     *
     *
     * @param scopeDomain  The domain path to register.
     * @param scope        The scope that should the given \p domain be registered for.
     *                     Available Scope definitions are platform/language dependent.
     * @param packageLevel Used only if parameter \p scope equals
     *                     \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                    to reference parent packages. Optional and defaults to \c 0.
     **********************************************************************************************/
    public void setDomain(String scopeDomain, Scope scope, int packageLevel)
    {
        setDomainImpl( scopeDomain, scope, packageLevel, false, null );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setDomain( String, Scope, int) "setDomain"
     * providing default value \c 0 for parameter \p packageLevel.
     *
     * @param scopeDomain    The domain path to register.
     * @param scope        The scope that should the given \p domain be registered for.
     *                     Available Scope definitions are platform/language dependent.
     **********************************************************************************************/
    public void setDomain(String scopeDomain, Scope scope)
    {
        setDomainImpl( scopeDomain, scope, 0, false, null );
    }

    /** ****************************************************************************************
     * This overloaded version of
     * \ref setDomain( String, Scope, int) "setDomain"
     * is applicable only for \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER and allows to
     * specify the thread that the setting should be associated with.
     *
     * If \p scopeDomain is \c null or empty, the most recently added domain path is removed.
     * For removing an explicitly named domain associated with  a thread use method
     * #removeThreadDomain.
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.THREAD_OUTER or \e %Scope.THREAD_INNER. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related Scope Domains for.
     ******************************************************************************************/
    public void setDomain(String scopeDomain, Scope scope, Thread thread)
    {
        if (!isThreadReleatedScope( scope )) return;
        setDomainImpl( scopeDomain, scope, 0, false, thread );
    }

    /** ****************************************************************************************
     * This method is used to remove an <em>explicitly given</em> domain path from the list
     * of domain paths set for \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER.
     *
     * To remove the most recently added domain path from such thread-related \e %Scope,
     * use one of the overloaded methods #setDomain and provide an empty or nulled
     * value for parameter \p scopeDomain (the same as how domain paths of other \e %Scopes
     * are removed).
     *
     * \note
     *   The long name of the method already indicates that this method is a little special.
     *   Only seldom, more than one <em>%Scope Domain</em> is needed to be added. And if this
     *   is needed, then such <em>%Scope Domains</em> usually get removed in reverse order of
     *   their definition, with is performed using the standard interface that allows 'removing'
     *   any other <em>%Scope Domain</em>. (Passing an empty or nulled domain
     *   path to method #setDomain.)
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related Scope Domains for.
     *                    Defaults to the current thread.
     ******************************************************************************************/
    public void removeThreadDomain(String scopeDomain, Scope scope, Thread thread)
    {
        try { acquire();

            scopeInfo.set( owner );

            if (!isThreadReleatedScope( scope )) return;

            if (CString.isNullOrEmpty( scopeDomain ))
            {
                intMsg._()._( "No scope domain path given to remove for " );
                ALox.toString( scope, 0, intMsg );
                intMsg._( '.' );
                logInternal( Verbosity.WARNING, "DMN", intMsg );
                return;
            }

            setDomainImpl( scopeDomain, scope, 0, true, thread );

        } finally { release(); }
    }

    /** ****************************************************************************************
     * Overload version providing default value for parameter \p thread.
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER. With other values,
     *                    an internal error is logged.
     ******************************************************************************************/
    public void removeThreadDomain(String scopeDomain, Scope scope)
    {
        removeThreadDomain( scopeDomain, scope, null );
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
    public void   setDomainSubstitutionRule( String domainPath, String replacement )
    {
        try { acquire();

            // initialize scope information
            scopeInfo.set( owner );
            intMsg._();

            // check null param: clears all rules
            if ( CString.isNullOrEmpty( domainPath ) )
            {
                oneTimeWarningCircularDS= false;
                domainSubstitutions.clear();
                intMsg._( "Domain substituion rules removed." );
                logInternal( Verbosity.INFO, "DMN", intMsg );
                return;
            }

            // create rule
            DomainSubstitutionRule newRule= new DomainSubstitutionRule( domainPath, replacement );
            if ( newRule.search.isEmpty() )
            {
                intMsg._( "Illegal domain substitution rule. Nothing stored." );
                logInternal( Verbosity.WARNING, "DMN", intMsg );
                return;
            }

            // search existing rule
            int  it;
            for( it= 0; it != domainSubstitutions.size() ; ++it )
            {
                if (     domainSubstitutions.get(it).type == newRule.type
                      && domainSubstitutions.get(it).search.equals( newRule.search ) )
                    break;
            }

            // no replacement given?
            if ( CString.isNullOrEmpty( replacement) )
            {
                if ( it == domainSubstitutions.size() )
                {
                    intMsg._( "Domain substituion rule \"")._( domainPath)._( "\" not found. Nothing to remove." );
                    logInternal( Verbosity.WARNING, "DMN", intMsg );
                    return;
                }

                intMsg._( "Domain substituion rule \"")._( domainPath      )._( "\" -> \"" )
                                                    ._( domainSubstitutions.get(it).replacement  )._( "\" removed." );
                domainSubstitutions.remove( it );
                logInternal( Verbosity.INFO, "DMN", intMsg );
                return;
            }


            intMsg._( "Domain substituion rule \"")._( domainPath          )._( "\" -> \"" )
                                                ._( newRule.replacement )._( "\" set." );

            // change of rule
            if ( it != domainSubstitutions.size() )
            {
                intMsg._( " Replacing previous -> \"")._( domainSubstitutions.get(it).replacement )._( "\"." );
                domainSubstitutions.get(it).replacement._()._( newRule.replacement );
            }
            else
                domainSubstitutions.add( newRule );

            logInternal( Verbosity.INFO, "DMN", intMsg );


        } finally { release(); }
    }

    /** ****************************************************************************************
     * The given \p logable becomes a <em>Prefix Logable</em> provided to loggers with log statements
     * executed within the given \p scope.
     * The list of objects received by a logger is sorted from outer scope to inner scope.
     * The logable of the <em>Log Statement</em> itself, is the last in the list, except one or
     * more <em>Prefix Logables</em> of \e %Scope.THREAD_INNER are set. Those are (similar to how this
     * \e %Scope is handled with <em>%Scope Domains</em>) are appended to the end of the list.
     *
     * To remove a previously set <em>Prefix Logable</em>, \c null has to be passed with
     * parameter \p logable.
     * For \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER, passing \c null
     * removes the most recently added <em>Prefix Logable</em>.
     *
     *<p>
     * \note
     *   The word 'prefix' in this methods' name and in the name of ALox feature
     *   <em>Prefix Logables</em> is chosen for the fact that with text loggers (which is the
     *   most widely applied use case for ALox) such objects are prefixes to the log
     *   message. Of-course, with using \e %Scope.THREAD_INNER, this turns into a suffix!<br>
     *   When using ALox to process objects instead of log messages, the concept of
     *   <em>Prefix Logables</em> is very useful. Just the name does not fit so well anymore.
     *   Think of 'SetContext' and <em>Context Objects</em> instead.
     *
     * @param logable      The <em>Prefix Logable</em> to set.
     * @param scope        The scope that should the given \p logable be registered for.
     *                     Available Scope definitions are platform/language dependent.
     * @param packageLevel Used only with
     *                     \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE".
     *                     Cuts the given number of package parts (separated with '.') from the end
     *                     of the packages. Optional and defaults to \c 0.
     ******************************************************************************************/
    public void        setPrefix( Object logable, Scope scope, int packageLevel  )
    {
        setPrefixImpl( logable, scope, packageLevel, null );
    }

    /** ****************************************************************************************
     * Overloaded version of \ref setPrefix(Object,Scope,int) "setPrefix" providing value \c 0
     * as default for parameter \p packageLevel.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     * @param scope       The scope that should the given \p logable be registered for.
     *                    Available Scope definitions are platform/language dependent.
     ******************************************************************************************/
    public void        setPrefix( Object logable, Scope scope  )
    {
        setPrefixImpl( logable, scope, 0, null );
    }

    /** ****************************************************************************************
     * This overloaded version of
     * \ref setPrefix(Object,Scope,int) "setPrefix" is applicable only for
     * \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER and allows to specify the thread that
     * the setting should be associated with.
     *
     * If \p logable is \c null, the most recently added <em>Prefix Logable</em>
     * is removed.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     * @param scope       Either \e %Scope.THREAD_OUTER or \e %Scope.THREAD_INNER. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related <em>Prefix Logable</em> for.
     ******************************************************************************************/
    public void        setPrefix( Object logable, Scope scope, Thread thread )
    {
        setPrefixImpl( logable, scope, 0, thread );
    }

    /** ****************************************************************************************
     * The given \p logable becomes a <em>Prefix Logable</em> associated to the given <em>Log Domain</em>.
     * <em>Prefix Logables</em> associated with the <em>Log Domain</em> are added to the list of \e Logables right
     * before the main \e Logable of the <em>Log Statement</em> itself.
     * Multiple <em>Prefix Logables</em> can be added per <em>Log Domain</em>.
     *
     * To remove the most recently added <em>Prefix Logable</em> associated with a <em>Log Domain</em>,
     * \c null has to be passed with parameter \p logable.
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
     * @param domain      The domain path. Defaults to \c null, resulting in
     *                    evaluated <em>Scope Domain</em> path.
     * @param otherPLs    If set to \c Inclusion.Exclude, scope-related <em>Prefix Logables</em>
     *                    are ignored and only domain-related <em>Prefix Logables</em> are passed to
     *                    the \e Loggers.
     *                    Defaults to \c Inclusion.Include.
     ******************************************************************************************/
    public void        setPrefix( Object logable, String domain, Inclusion otherPLs )
    {
        try { acquire();

            scopeInfo.set( owner );

            // we consider empty strings as unset command, so we set them to null
            if( logable != null )
            {
                if (    (( logable instanceof AString ) && ((AString) logable).isNull() )
                     || (( logable instanceof String  ) && ((String)  logable).length() == 0 )
                   )
                    logable= null;
            }

            Domain dom= evaluateResultDomain( domain );

            Verbosity intLogVerbosity= Verbosity.INFO;
            intMsg._();

            if ( logable != null )
            {
                dom.prefixLogables.add( dom.new PL( logable, otherPLs ) );
                intMsg._( '\"' )._( logable )._( " added as prefix logable for" );
            }
            else
            {
                int qtyPLs= dom.prefixLogables.size();
                if ( qtyPLs > 0 )
                {
                    Object removedLogable= dom.prefixLogables.get( qtyPLs - 1).logable;
                    dom.prefixLogables.remove( qtyPLs - 1 );

                    intMsg._('\"')._( removedLogable )._( "\" removed as prefix logable from");
                }
                else
                {
                    intMsg._( " No prefix logable to remove from" );
                    intLogVerbosity=  Verbosity.WARNING;
                }
            }

            intMsg._( " domain \'")._( dom.fullPath )._( "\'."  );
            logInternal( intLogVerbosity,    "PFX", intMsg );

        } finally { release(); }

    }

    /** ****************************************************************************************
     * Overloaded version of #setPrefix providing
     * default value \c Inclusion.INCLUDE for parameter \p otherPLs.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     * @param domain      The domain path. Defaults to \c null, resulting in
     *                    evaluated <em>Scope Domain</em> path.
     ******************************************************************************************/
    public void        setPrefix( Object logable, String domain )
    {
        setPrefix( logable, domain, Inclusion.INCLUDE );
    }

    /** ****************************************************************************************
     * Overloaded version of #setPrefix providing
     * default value \c Inclusion.INCLUDE for parameter \p otherPLs and
     * default value \c null for parameter \p domain.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     ******************************************************************************************/
    public void        setPrefix( Object logable )
    {
        setPrefix( logable, null, Inclusion.INCLUDE );
    }

    /** ********************************************************************************************
     * This method is used reset (or to explicitly set) the start time of the \e Logger(s). The only
     * impact is the output of time differences in the log lines. Hence, it is useful to see some
     * absolute time values when doing basic performance tests using the \e Logger.
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
     **********************************************************************************************/
    public void setStartTime(Date startTime, String loggerName)
    {
        try { acquire();

            scopeInfo.set( owner );

            // check if start time was set
            Ticks time= new Ticks( 0L );
            if (startTime != null)
                time.setFromJavaDate( startTime );
            else
                time.set();

            // request logger only from main domain tree
            Logger logger= domains.getLogger( loggerName );
            if (logger == null)
            {
                logInternal( Verbosity.ERROR, "LGR",
                        intMsg.clear()._( '\"' )._( loggerName )._( "\": not found. Start time not set." ) );
                return;
            }

            // do
            logger.timeOfCreation.set( time );
            logger.timeOfLastLog.set( time );

            // log info on this
            logInternal( Verbosity.INFO, "LGR",
                         intMsg.clear()._( '\"' )._( logger )._( "\": Start time set to " )
                               ._( startTime != null ? startTime : "<now>" )._( '.' ) );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of #setStartTime( Date, String ) providing default value \c null
     * for parameter \p loggerName.
     *
     * @param startTime     Optional parameter with the  new start time. Defaults to DateTime.Now if
     *                      omitted.
     **********************************************************************************************/
    public void setStartTime(Date startTime)
    {
        setStartTime( startTime, null );
    }

    /** ********************************************************************************************
     * Overloaded version of #setStartTime( Date, String ) providing default values
     * \c null for parameters \p startTime and \p loggerName.
     **********************************************************************************************/
    public void setStartTime()
    {
        setStartTime( null, null );
    }

    /** ********************************************************************************************
     * This method sets a human readable name to the given thread ID (or current thread) which is
     * optionally included in each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     * @param id            Parameter providing the thread ID.
     *                      Defaults to \c -1 which uses the current thread.
     **********************************************************************************************/
    public void mapThreadName(String threadName, long id)

    {
        try { acquire();

            // get current thread id
            String origThreadName= null;
            if (id < 0)
            {
                Thread t= Thread.currentThread();
                id= t.getId();
                origThreadName= t.getName();
            }

            // add entry
            threadDictionary.put( id, threadName );

            // log info on this
            scopeInfo.set( owner );
            intMsg.clear()._( "Mapped thread ID " )._( (int) id )._( " to \"" )._( threadName )._( "\"." );
            if (!CString.isNullOrEmpty( origThreadName )) intMsg._( " Original thread name: \"" )._( origThreadName )._( "\"." );
            logInternal( Verbosity.INFO, "THR", intMsg );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * This method sets a human readable name to the current thread which is optionally included in
     * each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     **********************************************************************************************/
    public void mapThreadName(String threadName)
    {
        mapThreadName( threadName, -1 );
    }

    /** ****************************************************************************************
     * Stores ALox <em>Log Data</em>, an object of base type
     * \ref com::aworx::lox::LogData "LogData" which can afterwards be retrieved by invoking
     * #retrieve. Using the optional \p key and \p scope offer various possibilities to reference
     * this data later.<br>
     *
     * To remove data from the store, pass \c null with parameter \p data.
     *
     * \attention
     * When data objects are 'overwritten', previous objects will be deleted internally.
     * Hence, only pointers to heap-allocated objects (created with \c new) may be passed!<br>
     * For more information, consult the ALox user manual.
     *
     * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
     *       It is not advised to use <em>Log Data</em> to implement application logic.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     ******************************************************************************************/
    public void store( LogData data, String key, Scope scope, int pkgLevel )
    {
        try { acquire();

            scopeInfo.set( owner );
            intMsg._();

            // We need a key. If none is given, we use a constant one indicating that storage is
            // associated exclusively with scope
            AString aKey= new AString(key);
            boolean keyWasEmtpy;
            if ( (keyWasEmtpy= aKey.isEmpty()) )
                aKey._( noKeyHashKey );

            // get the store
            scopeLogData.InitAccess( scope, pkgLevel, null );
            HashMap<AString, LogData> map= scopeLogData.get();
            if( map == null && data != null )
            {
                map= new HashMap<AString, LogData>();
                scopeLogData.store( map );
            }

            // create map entry
            LogData previous= map != null ? map.get( aKey ) : null;
            if ( data != null )
            {
                map.put( aKey, data );

                // log info if this was the last time
                intMsg._(  "Stored data " );

                if ( !keyWasEmtpy )
                    intMsg._( " with key \"" )._( tmpAS )._( "\" " );
                intMsg._( "in " );
                ALox.toString(scope, pkgLevel, intMsg);

                intMsg._( '.' );
                if ( previous != null )
                    intMsg._( " (Replaced previous.)" );
            }
            else
            {
                if ( previous != null )
                {
                    map.remove( aKey );
                    if ( map.size() == 0 )
                        scopeLogData.remove( null );

                    intMsg._( "Deleted map data " );
                }
                else
                    intMsg._( "No map data found to delete " );

                if ( !keyWasEmtpy )
                    intMsg._( " with key \"" )._( tmpAS )._( "\" " );
                intMsg._( "in " );
                ALox.toString(scope, pkgLevel, intMsg);
            }

            logInternal( Verbosity.INFO, "LGD", intMsg );

        } finally { release(); }
    }

    /** ****************************************************************************************
     * Overloaded version of #store providing default parameters.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     ******************************************************************************************/
    public void store( LogData data, String key, Scope scope )
    {
        store( data, key, scope, 0 );
    }

    /** ****************************************************************************************
     * Overloaded version of #store providing default parameters.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     ******************************************************************************************/
    public void store( LogData data, String key )
    {
        store( data, key, Scope.GLOBAL, 0 );
    }

    /** ****************************************************************************************
     * Overloaded version of #store providing default parameters.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     ******************************************************************************************/
    public void store( LogData data )
    {
        store( data, null, Scope.GLOBAL, 0 );
    }

    /** ****************************************************************************************
     * Overloaded version of #store providing default parameters.
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     ******************************************************************************************/
    public void store( LogData  data, Scope scope, int  pkgLevel )
    {
        store( data, null, scope, pkgLevel );
    }

    /** ****************************************************************************************
     * Overloaded version of #store providing default parameters.
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param scope     The \e %Scope that the data is bound to.
     ******************************************************************************************/
    public void store( LogData  data, Scope scope )
    {
        store( data, null, scope, 0 );
    }


    /** ****************************************************************************************
     * Retrieves ALox <em>Log Data</em>, an object of base type
     * \ref com::aworx::lox::LogData "LogData" which can be stored by invoking
     * #store. Using the optional \p key and \p scope offer various possibilities to reference
     * such objects.<br>
     *
     * \note If no <em>Log Data</em> object is found, an empty object is stored and returned.
     *
     * <p>
     * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
     *       It is not advised to use <em>Log Data</em> to implement application logic.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public LogData  retrieve( String key, Scope scope,  int pkgLevel )
    {
        try { acquire();

            scopeInfo.set( owner );

            // We need a key. If none is given, we use a constant one indicating that storage is
            // associated exclusively with scope
            tmpAS._()._(key);
            boolean keyWasEmtpy;
            if ( (keyWasEmtpy= tmpAS.isEmpty()) )
                tmpAS._( noKeyHashKey );

            // get the data (create if not found)
            scopeLogData.InitAccess( scope, pkgLevel, null );
            LogData returnValue= null;
            for( int i= 0; i < 2 ; i++ )
            {
                HashMap<AString, LogData> map= scopeLogData.get();
                if( map != null )
                    returnValue= map.get( tmpAS );

                if( returnValue == null )
                    store( new LogData(), key, scope, pkgLevel );
                else
                    break;
            }

            // log info if this was the last time
            intMsg._(  "Data " );

            if ( !keyWasEmtpy )
                intMsg._( " with key \"" )._( key )._( "\" " );
            intMsg._( "in " );
            ALox.toString(scope, pkgLevel, intMsg);
            intMsg._( returnValue != null ? " received." : " not found." );

            logInternal( Verbosity.INFO, "LGD", intMsg );
            return returnValue;

        } finally { release(); }
    }

    /** ****************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public LogData  retrieve( String key, Scope scope )
    {
        return retrieve( key, scope, 0 );
    }

    /** ****************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public LogData  retrieve( String key )
    {
        return retrieve( key, Scope.GLOBAL, 0 );
    }

    /** ****************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public LogData  retrieve()
    {
        return retrieve( null, Scope.GLOBAL, 0 );
    }

    /** ****************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param scope     The \e %Scope that the data is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public LogData  retrieve( Scope scope, int pkgLevel )
    {
            return retrieve( null, scope, pkgLevel);
    }

    /** ****************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param scope     The \e %Scope that the data is bound to.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public LogData  retrieve( Scope scope )
    {
            return retrieve( null, scope, 0 );
    }

    /** ********************************************************************************************
     * This method logs the configuration this Lox and its encapsulated objects.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param headLine  If given, a separated headline will be logged at first place.
     **********************************************************************************************/
    public void logConfig(String domain, Verbosity verbosity, String headLine)
    {
        try { acquire();

            // note: scope info is set later when entry() is invoked
            // we write log all into a Buffer first
            AString buf= new AString( 2048 );

            ScopeDump scopeDump= new ScopeDump( threadDictionary, noKeyHashKey, buf );

            // log a headline?
            if (!CString.isNullOrEmpty( headLine )) buf._( headLine ).newLine();

            // basic lox info
            buf._NC( "Name:            \"" )._( scopeInfo.getLoxName() )._('\"').newLine();
            buf._NC( "Version:         " )._( ALox.version )._NC( " (Rev. " )._( ALox.revision )._( ')' ).newLine();
            buf._NC( "Thread-Safe:     " )._NC( getSafeness() ).newLine();
            buf._NC( "#Log Calls:      " )._( cntLogCalls ).newLine();
            buf.newLine();

            //  domain substitutions
            buf._NC( "Domain Substitution Rules: " ).newLine();
            if( domainSubstitutions.size() > 0 )
            {
                // get size
                int maxWidth= 0;
                for ( DomainSubstitutionRule it : domainSubstitutions )
                    if ( maxWidth < it.search.length() )
                         maxWidth = it.search.length();
                maxWidth+= 2;

                // write
                for ( DomainSubstitutionRule it : domainSubstitutions )
                {
                    buf._NC( "  " );
                    if (    it.type == DSRType.ENDS_WIDTH
                         || it.type == DSRType.SUBSTRING )
                        buf._NC( '*' );

                    buf._NC( it.search );

                    if (    it.type == DSRType.STARTS_WITH
                         || it.type == DSRType.SUBSTRING )
                        buf._NC( '*' );

                    buf.tab( maxWidth, 0 )
                       ._NC( " -> " )
                       ._NC( it.replacement );
                    buf.newLine();
                }
            }
            else
                buf._NC("  <no rules set>" ).newLine();
            buf.newLine();

            // Log Once Counters
            buf._NC( "Once() Counters: " ).newLine();
            if ( scopeDump.writeMap( scopeLogOnce ) == 0 )
                buf._NC("  <no Once() counters set>" ).newLine();
            buf.newLine();

            // Log Data
            buf._NC( "Log Data: " ).newLine();
            if ( scopeDump.writeMap( scopeLogData ) == 0 )
                buf._NC("  <no data objects stored>" ).newLine();
            buf.newLine();

            // Prefix Logables
            buf._NC( "Prefix Logables: " ).newLine();
            int oldLength= buf.length();
            scopeDump.writePrefixes( scopePrefixes, 2 );
            logConfigCollectPrefixes( domains, 2, buf );
            if ( oldLength == buf.length() )
                buf._NC("  <no prefix logables set>" ).newLine();
            buf.newLine();

            // thread mappings
            buf._NC( "Named Threads:   " ).newLine();
            if (threadDictionary.size() == 0)
                buf._NC( "  No thread name mappings" ).newLine();
            else
                for (long key : threadDictionary.keySet())
                {
                    buf._NC( "  " ).field()._( '(' )._( key )._( "):" ).field( 7, Alignment.LEFT )._( '\"' )
                            ._( threadDictionary.get( key ) )._( '\"' );
                    buf.newLine();
                }
            buf.newLine();

            // Scope Domains
            buf._NC( "Scope Domains: " ).newLine();
            if ( scopeDump.writeDomains( scopeDomains, 2 ) == 0 )
                buf._NC("  <no scope domains set>" ).newLine();
            buf.newLine();

            // Loggers (and their domains)
            {
                ArrayList<Domain> domsWithDiffVerb= new ArrayList<Domain>();
                StringBuffer tempSB= new StringBuffer();
                SimpleDateFormat dateFormatter= new SimpleDateFormat( "yyyy-MM-dd HH:mm:ss", Locale.US );
                Date date= new Date();

                for (int treeNo= 0; treeNo < 2; ++treeNo )
                {
                    Domain domTree;
                    if( treeNo==0 )
                    {
                         domTree= domains;
                         buf._NC( "Loggers:" ).newLine();
                    }
                    else
                    {
                         domTree= internalDomains;
                         buf._NC( "Loggers on Internal Domains:" ).newLine();
                    }
                    int cnt= 0;

                    tempSB.setLength( 0 );
                    for (int loggerNo= 0 ; loggerNo < domTree.countLoggers() ; loggerNo++)
                    {
                        cnt++;
                        Logger logger= domTree.getLogger( loggerNo );
                        tempSB.setLength( 0 );
                        buf._NC( "  " )._NC( logger ).newLine();
                        buf._NC( "    Lines logged:  " )._( logger.cntLogs ).newLine();
                        buf._NC( "    Creation time: " )
                           ._( dateFormatter.format( logger.timeOfCreation.inJavaDate( date ), tempSB, new FieldPosition( 0 ) ) )
                           .newLine(); tempSB.setLength(0);
                        buf._NC( "    Last log time: " )
                           ._( dateFormatter.format( logger.timeOfLastLog .inJavaDate( date ), tempSB, new FieldPosition( 0 ) ) )
                           .newLine();

                        domsWithDiffVerb.clear();
                        logConfigDomsWithDiffVerb( domTree, loggerNo, domsWithDiffVerb);
                        for ( Domain dom : domsWithDiffVerb )
                        {
                            buf._NC( "    " )
                               ._NC(  dom == domsWithDiffVerb.get(0) ? "Verbosities:   "
                                                                     : "               " );

                            int tabRef= buf.length();
                            buf._( dom.fullPath );
                            buf.insertChars( ' ',  maxDomainPathLength + 1 - buf.length() + tabRef );
                            buf._("= "); ALox.toString(  dom.getVerbosity( loggerNo ), dom.getPriority(loggerNo), buf )
                               .newLine();
                        }

                        buf.newLine();
                    }

                    if ( cnt == 0 )
                        buf._NC("  <no loggers attached>" ).newLine();
                    buf.newLine();

                }
            }

            // Domains
            buf._NC( "Internal Domains:" ).newLine();
            logConfigDomainRecursive( internalDomains, buf );
            buf.newLine();

            // Domains
            buf._NC( "Domains:" ).newLine();
            logConfigDomainRecursive( domains, buf );
            buf.newLine();

            // now, log it out
            entry( domain, verbosity, buf );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Internal method used by LogConfig() to recursively log Domain instances.
     *
     * @param domain      The Domain instance to log out.
     * @param buf         The buffer to log to.
     **********************************************************************************************/
    protected void logConfigDomainRecursive(Domain domain, AString buf)
    {
        int reference= buf.length();
        buf._( "  " )._( domain );
        int idx= buf.indexOf( '[', reference );
        buf.insertChars( ' ', maxDomainPathLength + 5 - idx + reference, idx );
        buf.newLine();

        // loop over all sub domains (recursion)
        for (Domain subDomain : domain.subDomains)
            logConfigDomainRecursive( subDomain, buf );
    }

    /** ********************************************************************************************
     * Internal method used by LogConfig() to recursively (DFS) log <em>Prefix Logables</em> bound to
     * <em>Log Domains</em>
     *
     * @param domain        The actual domain to check.
     * @param indentSpaces  The number of spaces to write before each line.
     * @param target        The target string.
     **********************************************************************************************/
    protected void logConfigCollectPrefixes( Domain domain, int indentSpaces, AString target )
    {
        for ( Domain.PL pfl : domain.prefixLogables )
        {
            target.insertChars( ' ', indentSpaces );
            target._('\"');
            int idx= target.length();
            target._NC( pfl.logable );
            ESC.replaceToReadable( target, idx );
            target._('\"');

            if ( pfl.includeOtherPLs == Inclusion.EXCLUDE )
                target._NC( " (Excl.)" );
            target.tab( 25 );
            target._NC( "<domain>            [" )._( domain.fullPath )._(']').newLine();
        }

        for( Domain it : domain.subDomains )
            logConfigCollectPrefixes( it, indentSpaces, target );
    }

    /** ********************************************************************************************
     * Internal method used by LogConfig() to recursively (DFS) collect Domains of Logger that have
     * a different verbosity than their parent.
     *
     * @param domain      The actual domain to check.
     * @param loggerNo    The logger to collect domains for.
     * @param results     The result list.
     **********************************************************************************************/
    protected void logConfigDomsWithDiffVerb( Domain domain, int loggerNo, ArrayList<Domain> results )
    {
        if (    domain.parent == null
            ||  domain.parent.getVerbosity(loggerNo) != domain.getVerbosity(loggerNo) )
            results.add( domain );

        for( Domain it : domain.subDomains )
            logConfigDomsWithDiffVerb( it, loggerNo, results );
    }


    // #############################################################################################
    // Main logging methods
    // #############################################################################################

    /** ********************************************************************************************
     * Logs a \e Logable with the given \e %Verbosity.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param logable   The object to log.
     **********************************************************************************************/
    public void entry( String domain, Verbosity verbosity, Object logable )
    {
        try { acquire();

            // auto-initialization of ALox
            ALox.init( true, null );

            // auto-initialization of debug loggers
            if (domains.countLoggers() == 0 && this == Log.LOX) Log.addDebugLogger( this );


            cntLogCalls++;
            if ( domains.countLoggers() == 0 )
                return;
            scopeInfo.set( owner );
            log( evaluateResultDomain( domain ), verbosity, logable, Inclusion.INCLUDE );

            // release lock if logable was our internal log buffer singleton
            if (logable == logBuf) logBufLock.release();

        }
        finally  { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of #entry, defaulting parameter \p domain to a nulled string.
     *
     * @param verbosity The verbosity.
     * @param logable   The object to log.
     **********************************************************************************************/
    public void entry(Verbosity verbosity, Object logable)
    {
        entry( null, verbosity, logable );
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::VERBOSE "Verbosity.VERBOSE".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * Scope Domain set for the scope.
     *
     * @param logable   The object to log.
     **********************************************************************************************/
    public void verbose(Object logable)
    {
        entry( null, Verbosity.VERBOSE, logable );
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::VERBOSE "Verbosity.VERBOSE".
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     **********************************************************************************************/
    public void verbose(String domain, Object logable)
    {
        entry( domain, Verbosity.VERBOSE, logable );
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::INFO "Verbosity.INFO".
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The message to log.
     **********************************************************************************************/
    public void info(String domain, Object logable)
    {
        entry( domain, Verbosity.INFO, logable );
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::INFO "Verbosity.INFO".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * Scope Domain set for the scope.
     *
     * @param logable   The object to log.
     **********************************************************************************************/
    public void info(Object logable)
    {
        entry( null, Verbosity.INFO, logable );
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::WARNING "Verbosity.WARNING".
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The message to log.
     **********************************************************************************************/
    public void warning(String domain, Object logable)
    {
        entry( domain, Verbosity.WARNING, logable );
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::WARNING "Verbosity.WARNING".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * Scope Domain set for the scope.
     *
     * @param logable   The object to log.
     **********************************************************************************************/
    public void warning(Object logable)
    {
        entry( null, Verbosity.WARNING, logable );
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity.ERROR "Verbosity.ERROR".
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     **********************************************************************************************/
    public void error(String domain, Object logable)
    {
        entry( domain, Verbosity.ERROR, logable );
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity.ERROR "Verbosity.ERROR".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * Scope Domain set for the scope.
     *
     * @param logable   The object to log.
     **********************************************************************************************/
    public void error(Object logable)
    {
        entry( null, Verbosity.ERROR, logable );
    }

    /** ********************************************************************************************
     * Logs a \e Logable once, up to \p quantity times or every n-th time.
     * In its simplest overloaded version, the counter is bound to the source code line, hence,
     * only the first execution of this exact <em>Log Statement</em> is executed.
     *
     * Using parameter \p group, a set of <em>Log Statements</em> that share the same group key, can be
     * grouped and of such set, only the one which is first executed actually logs.<br>
     * Alternatively, when \p key is omitted (or null or empty), but a
     * \ref com::aworx::lox::Scope "Scope" is given with parameter \p scope, then the
     * counter is associated with the scope.<br>
     * Finally, parameters \p key and \p scope can also be used in combination. The key is
     * then unique in respect to the \ref com::aworx::lox::Scope "Scope" provided.
     *
     * Using, none, one or both of the parameters \p group and \p scope, among others, the
     * following use cases can be achieved.
     * - %Log a specific statement up to n-times.
     * - %Log only the first n of a group of statements.
     * - %Log only the first n statements within a method.
     * - %Log only the first n statements belonging to the same group and method .
     * - %Log only the first n statements within any method of
     *   - a class
     *   - a package
     *   - a parent package with all sub-packages
     * - %Log only the first n statements which belong to the same group and are placed within
     *   any method of
     *   - a class
     *   - a package
     *   - a parent package with all sub-packages
     * - %Log a <em>Log Statement</em> n-times per new thread.
     * - %Log only the first n statements of a group of statements executed by a specific thread.
     *
     * \note
     *   Due to the limitations of the Java language to dissolve ambiguities when invoking
     *   overloaded methods, most of the overloads provided await parameters
     *   \p domain and \p verbosity at the start. This is in difference to ALox for C++ and C#,
     *   where overloaded methods always default these parameters to \c null respectively
     *   \c %Verbosity.INFO.<br>
     *   Fortunate exceptions are
     *   - <b>%once(Object logable)</b> and
     *   - <b>%once(Object logable, int quantity)</b>.
     *
     * \note
     *   Furthermore, to to cover the most  frequent use cases, methods
     *   - <b>%once(Object logable, int quantity, String group)</b>,
     *   - <b>%once(Object logable, int quantity, %Scope scope, int pkgLevel)</b> and
     *   - <b>%once(Object logable, int quantity, %Scope scope)</b>
     *
     * \note
     *   have been added.  While their parameter order is 'wrong' and therefore need \p quantity to be specified,
     *   still they are nice shortcuts.
     *
     * When parameter \p quantity is a negative value, the log statement is executed every n-th time
     * instead n-times. E.g, if \p quantity is \c -5, the first statement is executed and afterwards
     * every fifth invocation.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope::Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *                  If negative, the first and every "-quantity-th" statement is executed.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logable, String group, Scope scope, int pkgLevel, int quantity)
    {
        try { acquire();

            scopeInfo.set( owner );

            // We need a group. If none is given, there are two options:
            tmpAS._()._( group );
            boolean groupWasEmtpy;
            if ((groupWasEmtpy= tmpAS.isEmpty()))
            {
                // GLOBAL scope: exact code line match match
                if (scope == Scope.GLOBAL)
                {
                    scope= Scope.METHOD;
                    tmpAS._( '#' )._( scopeInfo.lineNumber );
                }

                // not GOBAL scope: Unique tempAS per Scope
                else
                    tmpAS._( noKeyHashKey );
            }

            // get the store
            scopeLogOnce.InitAccess( scope, pkgLevel, null );
            HashMap<AString, int[]> map= scopeLogOnce.get();
            if (map == null)
            {
                map= new HashMap<AString, int[]>();
                scopeLogOnce.store( map );
            }

            int[] qty= map.get( tmpAS );
            if (qty == null) map.put( new AString( tmpAS ), qty= new int[1] );

            // log Once
            if ( quantity >= 0 )
            {
                if (qty[0] < quantity)
                {
                    qty[0]++;

                    // do the log
                    entry( domain, verbosity, logable );

                    // log info if this was the last time
                    if (qty[0] == quantity)
                    {
                        intMsg._()._( "Once() reached limit of " )._( quantity )._( " logs. No further logs for " );

                        if (groupWasEmtpy)
                        {
                            if (scope == Scope.GLOBAL)
                                intMsg._( "this line" );
                            else
                                ALox.toString( scope, pkgLevel, intMsg );
                        }
                        else
                        {
                            intMsg._( "group \"" )._( tmpAS )._( '\"' );
                            if (scope != Scope.GLOBAL)
                            {
                                intMsg._( " in " );
                                ALox.toString( scope, pkgLevel, intMsg );
                            }
                        }
                        intMsg._( '.' );

                        logInternal( Verbosity.INFO, "", intMsg );
                    }
                }
                else
                    // release lock if logable was our internal log buffer singleton
                    if (logable == logBuf) logBufLock.release();
            }
            // log Nth
            else
            {
                if ( qty[0]++ % -quantity == 0 )
                    entry( domain, verbosity, logable );
                else
                    // release lock if logable was our internal log buffer singleton
                    if (logable == logBuf) logBufLock.release();
            }

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope::Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logable, String group, Scope scope, int pkgLevel)
    {
        once( domain, verbosity, logable, group, scope, pkgLevel, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope::Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logable, String group, Scope scope )
    {
        once( domain, verbosity, logable, group, scope, 0, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope::Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logable, String group )
    {
        once( domain, verbosity, logable, group, Scope.GLOBAL, 0, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope::Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logable, String group, int quantity )
    {
        once( domain, verbosity, logable, group, Scope.GLOBAL, 0, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logable, Scope scope, int pkgLevel, int quantity)
    {
        once( domain, verbosity, logable, null, scope, pkgLevel, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logable, Scope scope, int pkgLevel)
    {
        once( domain, verbosity, logable, null, scope, pkgLevel, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param scope     The \e %Scope that the group or counter is bound to.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logable, Scope scope)
    {
        once( domain, verbosity, logable, null, scope, 0, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logable  )
    {
        once( domain, verbosity, logable, null, Scope.GLOBAL, 0, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logable, int quantity  )
    {
        once( domain, verbosity, logable, null, Scope.GLOBAL, 0, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logable   The string message to log.
     **********************************************************************************************/
    public void once( Object logable)
    {
        once( null, Verbosity.INFO, logable, null, Scope.GLOBAL, 0, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     **********************************************************************************************/
    public void once( Object logable, int quantity)
    {
        once( null, Verbosity.INFO, logable, null, Scope.GLOBAL, 0, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope::Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
    **********************************************************************************************/
    public void once( Object logable, int quantity, String group  )
    {
        once( null, Verbosity.INFO, logable, group, Scope.GLOBAL, 0, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
    **********************************************************************************************/
    public void once( Object logable, int quantity, Scope scope, int pkgLevel  )
    {
        once( null, Verbosity.INFO, logable, null, scope, pkgLevel, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     * @param scope     The \e %Scope that the group or counter is bound to.
    **********************************************************************************************/
    public void once( Object logable, int quantity, Scope scope  )
    {
        once( null, Verbosity.INFO, logable, null, scope, 0, quantity );
    }


    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is not \c true.
     * If executed, \ref Verbosity.ERROR is used.
     *
     * \note This Method's name starts with capital letter, as <c>'assert'</c> is a Java keyword.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     **********************************************************************************************/
    public void Assert(boolean condition, String domain, Object logable)
    {
        if (!condition)
            entry( domain, Verbosity.ERROR, logable );
        else
        {
            cntLogCalls++;
            if (logable == logBuf)
                logBufLock.release();
        }
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is not \c true.
     * If executed, \ref Verbosity.ERROR is used.
     *
     * This overloaded version omits parameter \p domain.
     *
     * \note This Method's name starts with capital letter, as <c>'assert'</c> is a Java keyword.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param logable   The object to log.
     **********************************************************************************************/
    public void Assert(boolean condition, Object logable)
    {
        if (!condition)
            entry( null, Verbosity.ERROR, logable );
        else
        {
            cntLogCalls++;
            if (logable == logBuf)
                logBufLock.release();
        }
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is \c true.
     * This overloaded version omits parameter \p domain.
     *
     * \note This Method's name starts with capital letter, as <c>'assert'</c> is a Java keyword.
     *
     * \see Method #Assert.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param logable   The object to log.
     **********************************************************************************************/
    public void If(boolean condition, String domain, Verbosity verbosity, Object logable)
    {
        if (condition)
            entry( domain, verbosity, logable );
        else
        {
            cntLogCalls++;
            if (logable == logBuf)
                logBufLock.release();
        }
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is \c true.
     * This overloaded version omits parameter \p domain.
     *
     * \note This Method's name starts with capital letter, as <c>'if'</c> is a Java keyword.
     *
     * \see Method #Assert.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param verbosity The verbosity.
     * @param logable   The object to log.
     **********************************************************************************************/
    public void If(boolean condition, Verbosity verbosity, Object logable)
    {
        if (condition)
            entry( null, verbosity, logable );
        else
        {
            cntLogCalls++;
            if (logable == logBuf)
                logBufLock.release();
        }
    }

    // #############################################################################################
    // internals
    // #############################################################################################

    /** ****************************************************************************************
     * Assembles the resulting domain from the given \p domainPath and the Scope Domain paths
     * (see #setDomain) according to the scope identified by scopeInfo.
     * The resulting full domain string is assembled from inner to outer scope.
     * If \p domainPath, respectively as soon as any of the scope levels' Scope Domain paths
     * starts with the character defined in
     * \ref com::aworx::lox::core::Domain::PATH_SEPARATOR "Domain.PATH_SEPARATOR",
     * the evaluation is stopped (the path is interpreted as absolute).
     *
     * @param domainPath The domain path. If starting with the character defined in
     *                   \ref com::aworx::lox::core::Domain::PATH_SEPARATOR "Domain.PATH_SEPARATOR",
     *                   no Scope Domains are applied.
     * @return The resulting \ref com::aworx::lox::core::Domain "Domain".
     ******************************************************************************************/
    protected Domain evaluateResultDomain(String domainPath)
    {
        // 0. internal domain tree?
        if (domainPath != null && domainPath.startsWith( ALox.INTERNAL_DOMAINS ))
        {
            // cut "$/" from the path
            resDomain._()._( domainPath, ALox.INTERNAL_DOMAINS.length() ).trim();
            return findDomain( internalDomains, resDomain );
        }

        // loop over scopes
        scopeDomains.initWalk( Scope.THREAD_INNER,
                // we have to provide null if parameter is empty
                CString.isNullOrEmpty( domainPath ) ? null : tmpAS._()._( domainPath ) );
        AString nextDefault;
        resDomain._();
        while ((nextDefault= scopeDomains.walk()) != null)
        {
            if (resDomain.isNotEmpty()) resDomain.insertAt( "/", 0 );
            resDomain.insertAt( nextDefault, 0 );

            // absolute path? That's it
            if (resDomain.charAtStart() == Domain.PATH_SEPARATOR) break;
        }
        return findDomain( domains, resDomain );
    }

    /** ****************************************************************************************
     * Invokes \b Find on the given domain and logs internal message when the domain was
     * not known before.
     * @param domainSystem The domain system. Either the standard or the internal one.
     * @param domainPath   The domain path.
     * @return The resulting \ref com::aworx::lox::core::Domain "Domain".
     ******************************************************************************************/
    Domain findDomain(Domain domainSystem, AString domainPath)
    {
        AString substPath= domainSystem == domains ? tmpSubstitutionPath
                                                   : tmpSubstitutionPathInternalDomains;

        int maxSubstitutions= 10;
        for(;;)
        {
            // loop for creating domains, one by one
            Domain dom= null;
            for(;;)
            {
                dom= domainSystem.find( domainPath, domainSensitivity, 1, booleanOutputParam );

                if (!booleanOutputParam[0])
                    break;

                // get maximum domain path length (for nicer LogConfig output only...)
                if (maxDomainPathLength < dom.fullPath.length())
                    maxDomainPathLength=  dom.fullPath.length();

                // log info on new domain
                intMsg._()._( '\'' )._( dom.fullPath )._( "' registered." );
                logInternal( Verbosity.INFO, "DMN", intMsg );

                // read domain from Config
                for ( int i= 0; i < dom.countLoggers(); ++i )
                    getVerbosityFromConfig( dom.getLogger(i), dom, null, 0 );

                // log inherited setting for each logger
                if (domainSystem.countLoggers() == 0)
                    logInternal( Verbosity.VERBOSE, "DMN", intMsg._()._( "No loggers set, yet." ) );
                else
                {
                    for (int i= 0 ; i < domainSystem.countLoggers() ; i++)
                    {
                        intMsg._()._( "  \"" )._( dom.getLogger( i ) )._( "\": " );
                        intMsg.insertChars( ' ', maxLoggerNameLength  + 6 - intMsg.length() );
                        intMsg._( dom.fullPath )
                              ._NC( " = " ); ALox.toString( dom.getVerbosity( i ), dom.getPriority(i), intMsg );
                        logInternal( Verbosity.VERBOSE, "DMN", intMsg );
                    }
                }
            }

            // apply domain substitutions
            if( domainSubstitutions.size() > 0 )
            {
                substPath.clear();
                while( maxSubstitutions-- > 0  )
                {
                    // loop over rules
                    boolean substituted= false;
                    for( DomainSubstitutionRule rule : domainSubstitutions )
                    {
                        switch( rule.type )
                        {
                            case STARTS_WITH:
                                if( substPath.isEmpty() )
                                {
                                    if ( dom.fullPath.startsWith( rule.search, domainSensitivity ) )
                                    {
                                        substPath._( rule.replacement )._( dom.fullPath, rule.search.length() );
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }
                                else
                                {
                                    if ( substPath.startsWith( rule.search, domainSensitivity ) )
                                    {
                                        substPath.replaceSubstring( rule.replacement, 0, rule.search.length()  );
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }

                            break;

                            case ENDS_WIDTH:
                                if( substPath.isEmpty() )
                                {
                                    if ( dom.fullPath.endsWith( rule.search, domainSensitivity ) )
                                    {
                                        substPath._( dom.fullPath, 0, dom.fullPath.length() - rule.search.length() )._( rule.replacement );
                                        substituted= true;
                                        continue;
                                    }
                                }
                                else
                                {
                                    if ( substPath.endsWith( rule.search, domainSensitivity ) )
                                    {
                                        substPath.deleteEnd( rule.search.length() )._( rule.replacement );
                                        substituted= true;
                                        continue;
                                    }
                                }
                            break;

                            case SUBSTRING:
                                if( substPath.isEmpty() )
                                {
                                    int idx= dom.fullPath.indexOf( rule.search, 0, domainSensitivity );
                                    if ( idx >= 0 )
                                    {
                                        substPath._( dom.fullPath, 0, idx )._( rule.replacement)._( dom.fullPath, idx + rule.search.length() );
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }
                                else
                                {
                                    int idx= substPath.indexOf( rule.search, 0, domainSensitivity );
                                    if ( idx >= 0 )
                                    {
                                        substPath.replaceSubstring( rule.replacement, idx, rule.search.length()  );
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }
                            break;

                            case EXACT:
                            {
                                if( substPath.isEmpty() )
                                {
                                    if ( dom.fullPath.equals( rule.search ) )
                                    {
                                        substPath._( rule.replacement);
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }
                                else
                                {
                                    if ( substPath.equals( rule.search) )
                                    {
                                        substPath._()._( rule.replacement );
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }
                            }
                            break;

                        }//switch rule type

                    }//rules loop

                    // stop if non was found
                    if( !substituted )
                        break;
                }

                // too many substitutions?
                if ( maxSubstitutions <= 0 && !oneTimeWarningCircularDS )
                {
                    oneTimeWarningCircularDS= true;
                    intMsg._()._(   "The Limit of 10 domain substitutions was reached. Circular substitution assumed!"
                                  + " (This error is only reported once!)" );

                    logInternal( Verbosity.ERROR, "DMN", intMsg );
                }

                // anything substituted?
                if( substPath.length() > 0 )
                {
                    domainPath= substPath;
                    continue;
                }
            }

            return dom;
        }

    }

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
    protected void log( Domain dom, Verbosity verbosity, Object logable, Inclusion prefixes )
    {
        // OK, this is a little crude, but the simplest solution: As class ScopeStore sees
        // null objects as nothing and won't return them in a walk, we replace null by
        // an object (we choose the store itself) and fix this in the loop back to null
        if ( logable == null )
            logable= scopePrefixes;

        dom.cntLogCalls++;
        tmpLogables.clear();
        for ( int i= 0; i < dom.countLoggers() ; i++ )
            if( dom.isActive( i, verbosity ) )
            {
                // lazily collect objects once
                if ( tmpLogables.size() == 0 )
                {
                    if ( prefixes == Inclusion.INCLUDE )
                    {
                        scopePrefixes.initWalk( Scope.THREAD_INNER, logable );
                        Object next;
                        while( (next= scopePrefixes.walk() ) != null )
                        {
                            tmpLogables.add( 0, next != scopePrefixes ? next : null );

                            // was this the actual? then insert domain-associated logables now
                            boolean excludeOthers= false;
                            if( next == logable )
                            {
                                int qtyThreadInner= tmpLogables.size() -1;
                                Domain pflDom= dom;
                                while ( pflDom != null )
                                {
                                    for( int ii= pflDom.prefixLogables.size() -1 ; ii >= 0 ; ii-- )
                                    {
                                        Domain.PL pl= pflDom.prefixLogables.get(ii);
                                        tmpLogables.add( 0,  pl.logable );
                                        if ( pl.includeOtherPLs == Inclusion.EXCLUDE )
                                        {
                                            excludeOthers= true;
                                            break;
                                        }
                                    }

                                    pflDom= excludeOthers ? null :  pflDom.parent;
                                }

                                // found a stoppable one? remove those from thread inner and break
                                if (excludeOthers)
                                {
                                    for ( int ii= 0; ii < qtyThreadInner ; ii++ )
                                        tmpLogables.remove( tmpLogables.size() - 1 );
                                    break;
                                }
                            }
                        }


                    }
                    else
                        tmpLogables.add( logable );
                }

                Logger logger= dom.getLogger( i );
                logger.acquire();
                    logger.cntLogs++;
                    logger.log( dom, verbosity, tmpLogables, scopeInfo );
                    logger.timeOfLastLog.set();
                logger.release();
            }
    }

    /** ****************************************************************************************
     * Logs an internal error message using the internal domain tree as defined in
     * \ref com::aworx::lox::ALox::INTERNAL_DOMAINS "ALox.INTERNAL_DOMAINS".
     *
     * @param verbosity The verbosity.
     * @param subDomain The sub-domain of the internal domain to log into.
     * @param logable   The message.
     ******************************************************************************************/
    protected void logInternal(Verbosity verbosity, String subDomain, AString logable)
    {
        log( findDomain( internalDomains, resDomainInternal._()._( subDomain ) ),
             verbosity, logable, Inclusion.EXCLUDE );
    }

    /** ********************************************************************************************
     * Implementation of the interface method fetching all possible parameters.
     *
     * @param scopeDomain  The domain path to register.
     * @param scope        The scope that the given \p domain should be registered for.
     *                     Available Scope definitions are platform/language dependent.
     * @param packageLevel Used only if parameter \p scope equals
     *                     \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                     to reference parent packages. Optional and defaults to \c 0.
     * @param removeNTRSD  Used to remove thread-related Scope Domains (and is true only when
     *                     invoked by interface method #removeThreadDomain.
     * @param thread       The thread to set/unset a thread-related Scope Domain for.
     **********************************************************************************************/
    protected void setDomainImpl(String scopeDomain, Scope scope, int packageLevel, boolean removeNTRSD, Thread thread)
    {
        //note: the public class interface assures that \p removeNTRSD (named thread-related
        //      scope domain) only evaluates true for thread related scopes
        try { acquire();

            scopeInfo.set( owner );

            boolean newValueIsNotEmpty= scopeDomain != null && scopeDomain.length() > 0;

            AString previousScopeDomain;
            scopeDomains.InitAccess( scope, packageLevel, thread );
            if (removeNTRSD)
            {
                AString searchedValue= new AString( scopeDomain );
                previousScopeDomain= scopeDomains.remove( searchedValue );
            }
            else
            {
                if (newValueIsNotEmpty)
                {
                    AString newValue= new AString( scopeDomain );
                    newValue.trim();
                    previousScopeDomain= scopeDomains.store( newValue );
                }
                else
                    previousScopeDomain= scopeDomains.remove( null );
            }

            // log info on this
            if (!removeNTRSD && newValueIsNotEmpty)
            {
                intMsg._()._( '\'' )._( scopeDomain )._( "\' set as default for " );
                ALox.toString( scope, packageLevel, intMsg )._( '.' );

                if (previousScopeDomain == null)
                    logInternal( Verbosity.INFO, "DMN", intMsg );
                else
                {
                    intMsg._( " Replacing previous default '" )._( previousScopeDomain )._( '\'' );
                    logInternal( Verbosity.WARNING, "DMN", intMsg );
                }
            }
            else
            {
                if (previousScopeDomain != null)
                {
                    intMsg._()._( '\'' )._( previousScopeDomain )._( "\' removed from " );
                    ALox.toString( scope, packageLevel, intMsg )._( '.' );
                    logInternal( Verbosity.INFO, "DMN", intMsg );
                }
                else
                {
                    intMsg._();
                    if (removeNTRSD)
                        intMsg._( '\'' )._( scopeDomain )._( "\' not found. Nothing removed for " );
                    else
                        intMsg._( "Empty Scope Domain given, nothing registered for " );
                    ALox.toString( scope, packageLevel, intMsg )._( '.' );

                    logInternal( Verbosity.WARNING, "DMN", intMsg );
                }
            }

        }
        finally  { release(); }
    }

    /** ****************************************************************************************
     * Implementation of the interface method fetching all possible parameters.
     *
     * @param logable      The <em>Prefix Logable</em> to set.
     * @param scope        The scope that the given \p logable should be registered for.
     *                     Available Scope definitions are platform/language dependent.
     * @param packageLevel Used only with
     *                     \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE".
     *                     Cuts the given number of package parts (separated with '.') from the end
     *                     of the packages. Optional and defaults to \c 0.
     * @param thread       The thread to set/unset a thread-related <em>Prefix Logable</em> for.
     **********************************************************************************************/
    protected void setPrefixImpl( Object  logable, Scope scope, int packageLevel, Thread thread )
    {
        try { acquire();
            scopeInfo.set( owner );

            // store new prefix for this scope (and get current)
            Object previousLogable;
            scopePrefixes.InitAccess( scope, packageLevel, thread );
            if ( logable != null )
                previousLogable= scopePrefixes.store ( logable );
            else
                previousLogable= scopePrefixes.remove( null );


            // log info on this
            intMsg._()._( "Prefix ");
            Verbosity intMsgVerbosity= Verbosity.INFO;

            if ( logable != null )
            {
                intMsg._( '\"' )._(logable)._( '\"' )
                      ._( " set for "); ALox.toString(scope, packageLevel, intMsg); intMsg._( '.') ;

                if ( previousLogable  != null )
                {
                    if (     ( logable instanceof String  && previousLogable instanceof String && logable.equals( previousLogable ))
                         ||   logable == previousLogable )
                    {
                        intMsg._( " (Same as before.)" );
                        intMsgVerbosity= Verbosity.VERBOSE;
                    }
                    else
                        intMsg ._( " Replacing previous \"" )._( previousLogable )._( "\"." );
                }
            }
            else
            {
                if ( previousLogable  != null )
                {
                    intMsg._( '\"' )._( previousLogable )._( '\"' )
                          ._( " removed from " ) ; ALox.toString(scope, packageLevel, intMsg); intMsg ._( '.' );
                }
                else
                {
                    intMsg._( "<null> given but nothing to remove for " );
                    ALox.toString(scope, packageLevel, intMsg); intMsg._( '.' );

                    intMsgVerbosity= Verbosity.WARNING;
                }
            }
           logInternal( intMsgVerbosity,    "PFX", intMsg );
        }
        finally  { release(); }
    }

    /** ********************************************************************************************
     * Checks if given scope is thread-related.
     *
     * @param scope     The scope that is to be checked.
     * @return \c true if \p scope is thread-related, \c false else.
     **********************************************************************************************/
    protected boolean isThreadReleatedScope(Scope scope)
    {
        if (scope == Scope.THREAD_INNER || scope == Scope.THREAD_OUTER) return true;

        intMsg._()._( "Illegal parameter, only Scope.THREAD_OUTER and Scope.THREAD_INNER allowed." )._( " Given: " );
        ALox.toString( scope, 0, intMsg );
        intMsg._( '.' );
        logInternal( Verbosity.ERROR, "DMN", intMsg );

        ALIB.ERROR( "Illegal parameter, only Scope.THREAD_OUTER and Scope.THREAD_INNER allowed." );

        return false;
    }

    /** ****************************************************************************************
     * Reads the verbosity for the given logger and domain from ALib configuration system.
     * This internal method is used in two occasions:
     * - when a new logger is added: recursively for all existing domains (\p configStr is
     *   given)
     * - when a new domain is created on the fly(\p configStr is not given)
     *
     * @param logger      The logger to set the verbosity for.
     * @param dom         The domain to set the verbosity for.
     * @param cfgStr      The configuration string. If not read yet, null may be given.
     * @param cfgPriority The priority of the configuration plug-in providing the variable.
     ******************************************************************************************/
    protected void  getVerbosityFromConfig( Logger  logger, Domain  dom,
                                            AString cfgStr, int     cfgPriority )
    {
        // get logger number. It may happen that the logger is not existent in this domain tree.
        int loggerNo= dom.getLoggerNo( logger ) ;
        if ( loggerNo < 0 )
            return;

        // check priority
        int priority= dom.getPriority( loggerNo );
        if ( priority == Lox.PRIO_PROTECTED )
            return;

        if ( cfgStr == null )
        {
            tmpAS._()._( scopeInfo.getLoxName() )._( '_' )._( logger.getName() )._( "_VERBOSITY" );
            cfgStr= tmpConfigValue._();
            cfgPriority= ALIB.config.get( ALox.configCategoryName, tmpAS, cfgStr );
            if( cfgPriority == 0  || cfgPriority < priority )
                return;
        }

        Tokenizer verbositiesTok= new Tokenizer( cfgStr, ';' );
        Tokenizer verbosityTok=   new Tokenizer();
        Substring domainStr=      new Substring();
        Substring verbositySettingStr;
        while( (verbositySettingStr= verbositiesTok.next()).isNotEmpty() )
        {
            verbosityTok.set( verbositySettingStr, '=' );

                      domainStr.set( verbosityTok.next() );
            Substring verbosityStr=  verbosityTok.next();
            if ( verbosityStr.isEmpty() )
                continue;

            int searchMode= 0;
            if ( domainStr.consume       ( '*' ) )    searchMode+= 2;
            if ( domainStr.consumeFromEnd( '*' ) )    searchMode+= 1;
            if(     ( searchMode == 0 && dom.fullPath.equals          ( domainStr,    domainSensitivity )     )
                ||  ( searchMode == 1 && dom.fullPath.startsWith      ( domainStr,    domainSensitivity )     )
                ||  ( searchMode == 2 && dom.fullPath.endsWith        ( domainStr,    domainSensitivity )     )
                ||  ( searchMode == 3 && dom.fullPath.indexOf         ( domainStr, 0, domainSensitivity ) >=0 )
                )
            {
                Verbosity verbosity= ALox.readVerbosity( verbosityStr );
                dom.setVerbosity( loggerNo, verbosity, cfgPriority );

                // log info on this
                intMsg._()._( "Verbosity set from configuration: \"" )
                          ._NC( logger )._NC( "\": " )._NC( dom.fullPath )
                          ._NC( " = " ); ALox.toString( verbosity, dom.getPriority( loggerNo), intMsg )
                          .trimEnd()._('.');
                logInternal( Verbosity.INFO, "LGR", intMsg );
            }
        }
    }


    /** ****************************************************************************************
     * Reads the verbosity for the given logger and domain from ALib configuration system.
     * This internal method is used when a new logger is added.
     * Walks recursively for all existing domains.
     *
     * @param logger      The logger to set the verbosity for.
     * @param dom         The domain to set the verbosity for.
     * @param cfgStr      The configuration string. If not read yet, null may be given.
     * @param cfgPriority The priority of the configuration plug-in providing the variable.
     ******************************************************************************************/
    protected void getAllVerbosities      ( Logger  logger,  Domain  dom,
                                            AString cfgStr,  int     cfgPriority )
    {
        // get config string once
        if ( cfgStr == null )
        {
            tmpAS._()._( scopeInfo.getLoxName() )._( '_' )._( logger.getName() )._( "_VERBOSITY" );
            cfgStr= tmpConfigValue._();
            cfgPriority= ALIB.config.get( ALox.configCategoryName, tmpAS, cfgStr );
            if( cfgPriority == 0 )
                return;
         }

        // get verbosity for us
        getVerbosityFromConfig( logger, dom, cfgStr, cfgPriority );

        // loop over all sub domains (recursion)
        for ( Domain subDomain : dom.subDomains )
            getAllVerbosities( logger, subDomain, cfgStr, cfgPriority );
    }

}
