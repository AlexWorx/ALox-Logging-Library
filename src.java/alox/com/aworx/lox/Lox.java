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
 * This class acts as a container for Loggers and provides a convenient interface into them.
 * Features are:
 *
 * - %Log into one or more Logger instances at once
 * - Manage default domain names for different scopes
 * - Store "code markers" and retrieve for simple tracing in log statements
 * - Count log operations
 *
 * In standard log scenarios, it is recommend **not** to use this class, but to use class
 * \ref com::aworx::lox::Log "Log" instead, which is a 100% static wrapper around this one.
 * In other words, class \b Log incorporates one static instance of this class and mirrors the
 * whole interface with static methods.
 *
 * Furthermore, all invocations of methods of class \b Log are pruned in release code, while
 * invocations of methods of this class are not. Hence, this class and interface should be used
 * to implement log code that is deemed to remain in the release version of software.
 * The use of class Log and Lox can be mixed, to enable debug log output in parallel to release
 * output.
 **************************************************************************************************/
public class Lox
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

        /**
         * A counter for the quantity of calls. The count includes logs that were suppressed by
         * disabled log rootDomain and those suppressed by the optional log condition parameter.
         * Hence, it can also be used as a condition to log only every n-th time by calling using
         * the conditional parameter of #line(), e.g.: *lox.line( (Log.qtyLogCalls % n) == 0, ...*.
         */
        public    int                       cntLogCalls                                         = 0;

        /**
         * This is the ThreadLock (mutex) for the Lox class. Each Lox method uses this mutex.
         * If thread safeness is not needed for the logging system (see user manual) the mutex
         * can be switched of using ThreadLock.setUnsafe(). The goal here would be to increase
         * logging performance. This is really a very seldom case, and it is better to be kept
         * in safe mode.
         */
        public    ThreadLock                lock                                  =new ThreadLock();

        /**
         * This is the log domain name used by this class. By manipulating this Domains log level,
         * the verbosity of ALox itself can be controlled. For example, in 'Info' level,
         * calls to #setDomain are logged which can be helpful to determine the log
         * domains that are created by libraries and larger projects.
         */
        public    String                    internalDomain                                  ="ALOX";

        /**
         * This is the log domain name chosen when no resulting domain name could be evaluated, e.g.
         * when no domain was specified but also no default domain was set. Or when missing caller
         * information do not allow to detect the scope.
         */
        public    String                    nullDomain                                      ="NULL";

        /**
         * A list of prefixes of \e 'packages.classes.methods' on the stack that are ignored when
         * identifying the caller info.
         * Usually this contains \e "com.aworx.lox" and \e "com.aworx.lib" and there is no need
         * to change this.
         */
        public    Vector<String>            omittablePackagePrefixes;


        /**
         * If this is positive, an error is logged to the \ref internalDomain "internal domain"
         * when a logging statement is executed which has no domain given and no default domain is
         * set either. The field is decremented with each warning until zero is hit.
         * Defaults to 10.
         */
        public    int                       errIfNoDefaultDomain                                =10;

    // #############################################################################################
    // Private/protected fields
    // #############################################################################################

        /** The list of Loggers. */
        protected ArrayList<Logger>         loggers                       = new ArrayList<Logger>();

        /** Optional default domains for a source file.*/
        protected HashMap<AString, AString> defaultDomains        = new HashMap<AString, AString>();

        /** Code markers*/
        protected HashMap<AString, Object>  markers                = new HashMap<AString, Object>();

        /** Information about the source code, method, thread, etc. invoking a log  call */
        protected CallerInfo                caller                               = new CallerInfo();

        /**
         *  Dictionary to translate thread IDs into something maybe nicer/shorter.
         *  The dictionary has to be filled by the user of the library.
         */
        protected HashMap <Long, String>    threadDictionary          = new HashMap<Long, String>();

        /** The resulting domain name. */
        protected AString                   resDomain                           = new AString( 32 );

        /** An AString singleton. Can be acquired, using buf() */
        protected AString                   logBuf                             = new AString( 128 );

        /** A locker for the log buffer singleton */
        protected ThreadLock                logBufLock                           = new ThreadLock();

        /**  A temporary AString, following the "create once and reuse" design pattern. */
        protected AString                   tempAS                             = new AString( 256 );

    // #############################################################################################
    // Constructors
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs a new, empty Lox.
         ******************************************************************************************/
        public Lox()
        {
            // set recursion warning of log buffer lock to 1. Warnings are logged if recursively
            // acquired more than once
            logBufLock.recursionWarningThreshold= 1;

            // set packages that might be omitted
            omittablePackagePrefixes     = new Vector<String>();
            omittablePackagePrefixes.add( "com.aworx.lib" );
            omittablePackagePrefixes.add( "com.aworx.lox" );
        }

    // #############################################################################################
    // Interface
    // #############################################################################################

    /** *********************************************************************************************
     * Returns an AString singleton, similar to the LogBuf singleton returned by Log.buf().
     * Whenever this method is called, the returned AString object has to be used as a message
     * within one of the log methods of this class (error(), warning(), info(), verbose(), assert()
     * or line()). If this is not done, the object does not get released and parallel threads using
     * it would block! So, do not use buf() for other reasons than for creating log messages and
     * be sure to re-acquire the AString object by calling this method again prior to the next
     * log call.
     *
     * @return the static AString singleton.
     **********************************************************************************************/
    public AString     buf()            { logBufLock.acquire(); logBuf.clear(); return logBuf; }

    /** ********************************************************************************************
     *  Use this method when you want to abort a log call that you "started" with acquiring the
     *  internal AString singleton acquired using method buf(). Use bufAbort() only if you did not
     *  use the acquired buffer as a parameter of a log method, because this internally releases the
     *  buf already.
     **********************************************************************************************/
    public void     bufAbort()          { logBufLock.release(); }

    /** ************************************************************************************
     *  This static method creates an adequate/default console logger.
     *  Currently, there is no detection mechanism implemented in the Java implementation
     *  of ALox. This might change in the future.
     *
     *  Hence, unless configuration variable
     *  [ALOX_CL_MODE](../group__GrpALoxConfigVars.html) is set, this method creates
     *  a logger of type
     *  \ref com::aworx::lox::loggers::ConsoleLogger "ConsoleLogger".
     *
     *  @param name  The name of the logger.  A value of null implies standard logger names
     *               defined in the logger sub-classes.

     *  @return      The TextLogger that was chosen.
     **************************************************************************************/
    public static TextLogger createConsoleLogger( String name )
    {
        //--- check environment "ALOX_CL_MODE". They have precedence ---
        AString consoleMode= new AString();
        if( ALIB.config.get( Log.configCategoryName, "CL_MODE", consoleMode ) != 0 )
        {
                 if( consoleMode.equals( "PLAIN",          Case.IGNORE ) )   return new ConsoleLogger    ( name );
                 if( consoleMode.equals( "ANSI",           Case.IGNORE ) )   return new AnsiConsoleLogger( name );

            else if( consoleMode.equals( "DEFAULT",        Case.IGNORE ) )   {}
            else { ALIB.WARNING( "Unrecognized value in config variable: ALOX_CL_MODE =" + consoleMode.toString() ); }
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
     * Adds a logger to this container of loggers.
     * Each log call that is performed through this classes' interface
     * will be forwarded to this logger, unless filtered out with optional filter parameter.
     *
     * \note
     *   This method checks whether the domain used for internal ALox messages
     *   (see field #internalDomain) is already registered with the given logger.
     *   Only if not, the domain is registered and set to domain level
     *   \ref com::aworx::lox::Log::DomainLevel::WARNINGS_AND_ERRORS "DomainLevel.WARNINGS_AND_ERRORS".
     *   This means, that it does not play a role, if changes to the level of domain "ALOX" are
     *   performed prior to adding a logger, using
     *   \ref com::aworx::lox::core::Logger::setDomain "Logger.setDomain"
     *   or after a logger was added, using
     *   \ref com::aworx::lox::Lox::setDomain "Lox.setDomain".
     *
     * @param logger  The logger to be added.
     **********************************************************************************************/
    public  void addLogger( Logger logger )
    {
        try { lock.acquire();

            // initialize caller information
            caller.set( threadDictionary, omittablePackagePrefixes );

            // if list existed, check if logger was added already
            if ( loggers.contains( logger ) )
            {
                internalLog( Log.Level.WARNING,
                             tempAS.clear()._("AddLogger: Logger \"")
                                           ._( logger.name )
                                           ._("\" already exists. Not added.") );
                return;
            }

            // add logger to list
            loggers.add( logger );

            // if internal domain was not registered, yet (which is the normal case), we set
            // it to WarningsAndErrors
            boolean[] wasCreated= new boolean[1];
            Domain domain= logger.rootDomain.find( new AString( internalDomain ), wasCreated );
            if ( wasCreated[0] )
                domain.setLevel( Log.DomainLevel.WARNINGS_AND_ERRORS );

            // log info on this
            tempAS._()._("AddLogger: Logger \"")._(logger.name)._("\" ");
            if ( !logger.name.equalsIgnoreCase( logger.typeName ))
                tempAS._('(')._( logger.typeName )._(") ");
            tempAS._("added.");
            internalLog( Log.Level.INFO, tempAS );

        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * Retrieve an instance of a Logger by its name.
     *
     * @param loggerName    The name of the logger to search for (case insensitive)
     * @return The logger, null if not found.
     **********************************************************************************************/
    public  Logger getLogger( String loggerName )
    {
        try { lock.acquire();

            // search logger
            for ( Logger logger : loggers )
                if ( logger.name.equalsIgnoreCase( loggerName ) )
                    return logger;

            // not found
            return null;

        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     *  Removes a logger from this container.
     *  @param logger   The logger to be removed.
     *  @returns True, if the logger was found and removed, false otherwise.
     **********************************************************************************************/
    public boolean removeLogger( Logger logger )
    {
        try { lock.acquire();

            // loop over all loggers backwards
            for(int i= loggers.size() - 1; i >= 0; i--)
                if ( loggers.get( i ) == logger )
                {
                    loggers.remove( i );
                    return true;
                }
            return false;
        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * Removes all loggers that match the filter name from this container.
     *
     * @param loggerFilter  A filter for the loggers to be affected. A simple string compare without
     *                      case sensitivity is performed. An asterisk ('*') at the beginning or end
     *                      of the string is used as a wildcard. Defaults to null which causes all
     *                      loggers to be removed.
     *  @returns The number of loggers that were removed.
     **********************************************************************************************/
    public int removeLoggers( String loggerFilter )
    {
        try { lock.acquire();

            int qtyLoggers= loggers.size();

            // loop over all loggers backwards
            for(int i= loggers.size() - 1; i >= 0; i--)
                if ( simpleWildcardFilter( loggers.get( i ), loggerFilter ) )
                    loggers.remove( i );

            return qtyLoggers - loggers.size();
        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * Removes all loggers from this Lox.
     *  @returns The number of loggers that were removed.
     **********************************************************************************************/
    public int removeLoggers(  ) { return removeLoggers( null ); }


    /** *********************************************************************************************
     * This method is used to define a log domain. The method is usually invoked within the same
     * source "context" (aka, class, namespace, package, etc.) that later on uses the domain to
     * perform log statements. Often, calls to this functions are placed in static constructors or
     * similar code that is executed only once and very early in the lifecycle of a process.
     *
     * Each log statement refers to such a domain which can be used specifically for different parts
     * of your application like assemblies, libraries, namespaces, specific code files or even for a
     * single method. The domain name should be short, pregnant and self explaining.
     *
     * Domains can be created with path separators '/', for example 'COMM/SOCK' could be the domain
     * in a socket class, residing within a communication library. The advantage of creating paths
     * and this way "sub domains", is that a whole bunch of logging domains can be altered (on/off)
     * by just altering the root domain.
     *
     * If a domain and path is given that is not known already, then the whole path of domains is
     * created.
     *
     * If the parameter **scope** is provided with a value not equal to Log.Scope.None, the given
     * domain becomes the default domain for respective scope. For any subsequent log calls from
     * within this scope, where no domain is explicitly given, this default domain is used. If
     * subsequent log calls specify a domain name with a leading '~' character, then such domain is
     * concatenated to the default domain to build a complete domain path.
     *
     * @param domain    The domain name (and path) to register. If this is starting with a swung dash
     *                  ('~') this is interpreted a sub domain to a (potentially already set!) default
     *                  domain of the scope. For other values, the default domain is ignored
     *                  (regardless if this is starting with a slash or not).
     * @param scope     If a value other than Log.Scope.None is provided, the given domain name is
     *                  registered as the default domain for the given scope. Default domains set for
     *                  'inner scopes' have higher priority than those set for outer scopes. Available
     *                  Scope definitions are platform/language dependent.
     **********************************************************************************************/
    public  void setDomain( String    domain,     Log.Scope scope )
    {
        try { lock.acquire();

            // save caller info and get resulting domain
            caller.set( threadDictionary, omittablePackagePrefixes );
            evaluateResultDomain( domain );

            // check parameter
            if ( CString.isNullOrEmpty( domain ) )
            {
                internalLog( Log.Level.ERROR,
                             tempAS.clear()._( "SetDomain: Empty domain given. Not registered.") );
                return;
            }

            // set domain as default for calling source file's log calls
            if ( scope != Log.Scope.NONE )
            {
                AString key= new AString( caller.packageName.length() + caller.className.length() + caller.methodName.length() + 2);
                key._( caller.packageName );
                if ( scope != Log.Scope.PACKAGE )
                    key._( '#' )._( caller.className );
                if ( scope == Log.Scope.METHOD )
                    key._( '#' )._( caller.methodName );

                // store domain in hash table
                AString previous= defaultDomains.get( key );
                defaultDomains.put( key, new AString( resDomain ) );

                // log info on this
                tempAS._()._("SetDomain: Domain \"")           ._(resDomain)
                          ._("\" set as default for scope \"") ._(scope.toString())._("\".");

                if ( previous != null )
                    tempAS._(" Replacing previous Domain \"")._(previous)._("\".");
                internalLog( previous!=null? Log.Level.WARNING : Log.Level.INFO, tempAS );
            }

        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * Sets the domain log level and (by default) all it's sub domains recursively. In the case that
     * sub domains should be set to a different log level, then this function has to be called for
     * such sub domains after the call to the parent domain (or recursion has to be switched off,
     * using the parameter 'recursive'). It is not necessary to register a domain before setting its
     * log level and log levels can be set and modified any time.
     *
     * @param domain        If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the scope. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param domainLevel   The domains log level to be set.
     * @param propagation   If \c Propagation.TO_DESCENDANTS, which is the default, the level is
     *                      set for all sub-domains recursively.
     *                      If \c Propagation.NONE, then only this domain is changed.
     * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
     *                      loggers to have different domains and log levels. A simple string compare
     *                      without case sensitivity is performed. An asterisk ('*') at the beginning
     *                      or end of the string is used as a wildcard. Leave to \e null if all loggers
     *                      should be affected. Use this parameter only in more complex logging
     *                      scenarios.
     **********************************************************************************************/
    public  void setDomain( String  domain,       Log.DomainLevel  domainLevel,
                            String  loggerFilter, Propagation      propagation    )
    {
        try { lock.acquire();

            caller.set( threadDictionary, omittablePackagePrefixes );

            boolean resultDomainEvaluatedLazily= false;
            for ( Logger logger : loggers )
            {
                if ( !simpleWildcardFilter( logger, loggerFilter ) )
                    continue;

                if (!resultDomainEvaluatedLazily)
                {
                    resultDomainEvaluatedLazily= true;
                    evaluateResultDomain( domain );
                }

                logger.setDomain( resDomain, domainLevel, propagation );

                internalLog( Log.Level.INFO,
                             tempAS._()._NC( "SetDomain: Domain \""   ) ._NC(resDomain)
                                       ._NC( "\" log level set to \"" ) ._NC(domainLevel.toString())
                                       ._NC( "\" for logger \""       ) ._NC(logger.name)._("\".") );
            }


        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * Sets the domain log level and (by default) all it's sub domains recursively. In the case that
     * sub domains should be set to a different log level, then this function has to be called for
     * such sub domains after the call to the parent domain (or recursion has to be switched off,
     * using the parameter 'recursive'). It is not necessary to register a domain before setting its
     * log level and log levels can be set and modified any time.
     *
     * @param domain        If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the scope. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param domainLevel   The domains log level to be set.
     * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
     *                      loggers to have different domains and log levels. A simple string compare
     *                      without case sensitivity is performed. An asterisk ('*') at the beginning
     *                      or end of the string is used as a wildcard. Leave to \e null if all loggers
     *                      should be affected. Use this parameter only in more complex logging
     *                      scenarios.
     **********************************************************************************************/
    public void setDomain(String domain, Log.DomainLevel domainLevel, String loggerFilter)
    {
        setDomain( domain, domainLevel, loggerFilter, Propagation.TO_DESCENDANTS );
    }

    /** *********************************************************************************************
     * Sets the domain log level and all it's sub domains recursively. In the case that sub domains
     * should be set to a different log level, then this function has to be called for such sub
     * domains after the call to the parent domain (or recursion has to be switched off, using the
     * parameter 'recursive'). It is not necessary to register a domain before setting its log level
     * and log levels can be set and modified any time.
     *
     * @param domain        If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the scope. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param domainLevel   The domains log level to be set.
     **********************************************************************************************/
    public void setDomain(String domain, Log.DomainLevel domainLevel)
    {
        setDomain( domain, domainLevel, null, Propagation.TO_DESCENDANTS );
    }

    /** *********************************************************************************************
     * <c>setDomain(domain, scope)</c> and <c>setDomain(domain, domainLevel)</c>.<br>
     * Optional parameter \p loggerFilter applies only to the domain level setting.
     *
     * @param domain        If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the source file. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param scope         If a value other than Log.Scope.None is provided, the given domain name is
     *                      registered as the default domain for the given scope. Default domains set for
     *                      'inner scopes' have higher priority than those set for outer scopes. Available
     *                      Scope definitions are platform/language dependent.
     * @param domainLevel   The domains log level to be set.
     * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
     *                      loggers to have different domains and log levels. A simple string compare
     *                      without case sensitivity is performed. An asterisk ('*') at the beginning
     *                      or end of the string is used as a wildcard. Leave to \e null if all loggers
     *                      should be affected. Use this parameter only in more complex logging
     *                      scenarios.
     **********************************************************************************************/
    public void setDomain( String domain, Log.Scope scope, Log.DomainLevel domainLevel,
                           String loggerFilter )
    {
        setDomain( domain, scope );
        setDomain( domain, domainLevel, loggerFilter );
    }

    /** *********************************************************************************************
     * <c>setDomain(domain, scope)</c> and <c>setDomain(domain, domainLevel)</c>.
     *
     * @param domain        If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the source file. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param scope         If a value other than Log.Scope.None is provided, the given domain name is
     *                      registered as the default domain for the given scope. Default domains set for
     *                      'inner scopes' have higher priority than those set for outer scopes. Available
     *                      Scope definitions are platform/language dependent.
     * @param domainLevel   The domains log level to be set.
     **********************************************************************************************/
    public void setDomain( String domain, Log.Scope scope, Log.DomainLevel domainLevel )
    {
        setDomain( domain, scope );
        setDomain( domain, domainLevel );
    }
    /** *********************************************************************************************
     * <c>setDomain(domain, scope)</c> and <c>setDomain(domain, domainLevel)</c>.
     *
     * @param scope         If a value other than Log.Scope.None is provided, the given domain name is
     *                      registered as the default domain for the given scope. Default domains set for
     *                      'inner scopes' have higher priority than those set for outer scopes. Available
     *                      Scope definitions are platform/language dependent.
     * @param domain        If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the source file. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param domainLevel   The domains log level to be set.
     **********************************************************************************************/
    public void setDomain( String domain, Log.DomainLevel domainLevel, Log.Scope scope )
    {
        setDomain( domain, scope );
        setDomain( domain, domainLevel );
    }


    /** *********************************************************************************************
     * This method is used to disable (and enable again) one or more loggers completely without
     * touching the log levels of the domains and hence without the need to restore such log
     * levels later.
     *
     * @param newState      If \c Switch::Off, the logger(s) will be completely disabled,
     *                      if \c Switch::On, the normal, domain specific log levels will
     *                      be applied for log  decisions.
     * @param loggerFilter  A filter for the loggers to be affected. A simple string compare without
     *                      case sensitivity is performed. An asterisk ('*') at the beginning or end
     *                      of the string can be used for 'globbing'.
     *                      If \e null, all loggers will be switched.
     **********************************************************************************************/
    public  void setLogger( Switch newState, String loggerFilter )
    {
        try { lock.acquire();

            caller.set( threadDictionary, omittablePackagePrefixes );

            for ( Logger logger : loggers )
            {
                if ( simpleWildcardFilter( logger, loggerFilter ) )
                {
                    logger.isDisabled= newState == Switch.OFF;

                    // log info on this
                    internalLog( Log.Level.INFO,
                                 tempAS.clear()._("SetLogger: Logger \"")
                                               ._(logger.name)._("\" ")
                                               ._((newState == Switch.OFF ? "disabled." : "enabled."))  );
                }
            }

        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * This method is used reset (or to explicitly set) the start time of the logger(s). The only
     * impact is the output of time differences in the log lines. Hence, it is useful to see some
     * absolute time values when doing basic performance tests using the logger.
     *
     * @param startTime     Optional parameter with the  new start time. Defaults to DateTime.Now if
     *                      omitted.
     * @param loggerFilter  A filter for the loggers to be affected. A simple string compare without
     *                      case sensitivity is performed. An asterisk ('*') at the beginning or end
     *                      of the string is used as a wildcard. Leave to \e null if all loggers
     *                      should be affected.
     **********************************************************************************************/
    public  void setStartTime( Date startTime, String loggerFilter)
    {
        try { lock.acquire();

            caller.set( threadDictionary, omittablePackagePrefixes );

            // check if start time was set
            Ticks time= new Ticks( 0L );
            if ( startTime != null)
                time.setFromJavaDate( startTime );
            else
                time.set();

            // loop over all loggers
            for ( Logger logger : loggers )
            {
                // logger filtered out? -> skip
                if ( !simpleWildcardFilter( logger, loggerFilter ) )
                    continue;

                // set new start time and last log time stamp
                logger.timeOfCreation.set( time );
                logger.timeOfLastLog .set( time );

                // log info on this
                internalLog( Log.Level.INFO,
                             tempAS.clear()._("SetStartTime: Start time of \"")
                                           ._(logger.name)
                                           ._("\" set to: ")
                                           ._(startTime!=null ? startTime.toString() : "\"now\"")
                                           ._('.')  );
            }

        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * This method is used reset (or to explicitly set) the start time of the logger(s). The only
     * impact is the output of time differences in the log lines. Hence, it is useful to see some
     * absolute time values when doing basic performance tests using the logger.
     *
     * @param startTime     Optional parameter with the  new start time. Defaults to DateTime.Now if
     *                      omitted.
     **********************************************************************************************/
    public  void setStartTime( Date startTime )     { setStartTime( startTime,    null ); }

    /** *********************************************************************************************
     * This method is used reset the start time of the logger(s) to now. The only impact is the
     * output of time differences in the log lines. Hence, it is useful to see some absolute time
     * values when doing basic performance tests using the logger.
     **********************************************************************************************/
    public  void setStartTime()                     { setStartTime( null,        null ); }

    /** *********************************************************************************************
     * This method sets a human readable name to the given thread ID (or current thread) which is
     * optionally included in each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     * @param id            Parameter providing the thread ID. If set to -1, the current thread's ID is
     *                      used.
     **********************************************************************************************/
    public  void mapThreadName(    String threadName, long id )

    {
        try { lock.acquire();

            // get current thread id
            String origThreadName= null;
            if ( id < 0 )
            {
                Thread t=        Thread.currentThread();
                id=                t.getId();
                origThreadName= t.getName();
            }

            // add entry
            threadDictionary.put( id, threadName );

            // log info on this
            caller.set( threadDictionary, omittablePackagePrefixes );
            tempAS.clear()._("MapThreadName: Mapped thread ID ")._((int) id)._(" to \"")._(threadName)._("\".");
            if ( !CString.isNullOrEmpty( origThreadName )  )
                tempAS._(" Original thread name was \"")._(origThreadName)._("\".");
            internalLog( Log.Level.INFO, tempAS );

        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * This method sets a human readable name to the current thread which is optionally included in
     * each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     **********************************************************************************************/
    public  void mapThreadName(    String threadName ) { mapThreadName( threadName, -1 ); }

    /** *********************************************************************************************
     * This method is used store a marker object in the logging system. Markers are stored and
     * retrieved relative to a given Log.Scope. In combination with Log.GetMarker, this method
     * provides an easy way to trace the last marked position, e.g. in the case of an exception.
     * Within the exception handler, use Log.GetMarker to retrieve the last marker object stored
     * before the exception was thrown.
     *
     * @param marker    The object to store, for example a String that can be used for a log output
     *                  later.
     * @param scope     The scope in which the marker should be stored. Markers and scopes work
     *                  independently from each other. Different markers can be stored within different
     *                  scopes and no fallback to "outer scopes" is made. A scope of 'None' stores the
     *                  marker globally, hence as a system wide singleton.
     **********************************************************************************************/
    public  void setMarker(    Object marker, Log.Scope scope)
    {
        try { lock.acquire();

            caller.set( threadDictionary, omittablePackagePrefixes );

            // build key string
            AString key= new AString(64);
            if ( scope == Log.Scope.NONE )
                key._NC( "$GLOBAL" );
            else
            {
                key._NC( caller.packageName );
                if ( scope != Log.Scope.PACKAGE )
                    key._( '#' )._NC( caller.className );
                if ( scope == Log.Scope.METHOD )
                    key._( '#' )._NC( caller.methodName );
            }

            // save marker ([] overwrites any existing)
            markers.put( key, marker );

            // log info on this
            internalLog( Log.Level.INFO,
                         tempAS.clear()._NC("SetMarker: Marker set (")
                                       ._NC(( marker != null ? marker.toString() : "null"))
                                       ._NC(").") );

        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * Retrieves the most recently marker object stored using Log.SetMarker. Markers are stored and
     * retrieved relative to a given Log.Scope. In combination with Log.SetMarker, this method
     * provides an easy way to trace the last marked position, e.g. in the case of an exception.
     * Within the exception handler, use this method to retrieve the last marker object stored
     * before the exception was thrown.
     *
     * @param scope  The scope in which the marker should be stored. Markers and scopes work
     *               independently from each other. Different markers can be stored within
     *               different scopes and no fallback to "outer scopes" is made. A scope of
     *               'None' retrieves the global marker singleton.
     * @returns The marker object, null if not found.
     **********************************************************************************************/
    public  Object getMarker( Log.Scope scope )
    {
        try { lock.acquire();

            caller.set( threadDictionary, omittablePackagePrefixes );

            // build key string
            tempAS.clear();
            if ( scope == Log.Scope.NONE )
                tempAS._NC( "$GLOBAL" );
            else
            {
                tempAS._NC( caller.packageName );
                if ( scope != Log.Scope.PACKAGE )       tempAS._( '#' )._NC( caller.className );
                if ( scope == Log.Scope.METHOD )        tempAS._( '#' )._NC( caller.methodName );
            }


            // get marker
            Object marker= markers.get( tempAS );

            // log info on this
            internalLog( Log.Level.INFO,
                         tempAS.clear()._("GetMarker: Marker retrieved (")
                                       ._(( marker != null ? marker.toString() : "null"))
                                       ._(").") );

            return marker;

        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * This method logs the configuration this Lox and its encapsulated objects.
     *
     * @param domain        If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the scope. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param level         The logging level.
     * @param headLine      If given, a separated headline will be logged at first place.
     * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
     *                      loggers to have different domains. A simple string compare without case
     *                      sensitivity is performed. An asterisk ('*') at the beginning or end of
     *                      the string is used as a wildcard. Leave to \e null if all loggers should be
     *                      affected. Use this parameter only in more complex logging scenarios.
     **********************************************************************************************/
    public  void logConfig(    String    domain,            Log.Level        level,
                            String    headLine,        String            loggerFilter )
    {
        try { lock.acquire();

            // setup
            caller.set( threadDictionary, omittablePackagePrefixes );
            evaluateResultDomain( domain );

            // count overall calls
            cntLogCalls++;

            // we write log all into a Buffer first
            AString buf=        new AString( 2048 );

            // log a headline?
            if ( !CString.isNullOrEmpty(headLine) )
                buf._( headLine ).newLine();

            // basic lox info
            buf._NC( "Version:         ")._( Log.version)._NC(" (Rev. ")._( Log.revision)._(')').newLine();
            buf._NC( "Intern. Domain:  ")._NC( internalDomain   ).newLine();
            buf._NC( "Thread-Safe:     ")._NC( lock.isUnsafe()  ? "No (!)" : "Yes" ).newLine();
            buf._NC( "#Log Calls:      ")._   ( cntLogCalls     ).newLine();

            // code markers
            if ( markers.size() > 0 ) buf.newLine();
            buf._NC( "Code markers:    ")._( markers.size()  ).newLine();
            for (  AString key : markers.keySet() )
            {
                Object o= markers.get( key );
                buf._NC( "  Marker:    "  )._(  o != null ? o.toString() : "null" ).newLine();
                buf._NC( "   Scope: \"" )._(  key                                )._('\"').newLine();
            }

            // thread mappings
            if ( threadDictionary.size() > 0 )  buf.newLine();
            buf._NC( "Named Threads:   " )._( threadDictionary.size() ).newLine();
            for ( long key : threadDictionary.keySet() )
            {
                buf._NC( "  " ).field()._('(')._(key)._( "):").field( 7, Alignment.LEFT )
                               ._('\"')._( threadDictionary.get(key) ) ._('\"');
                buf.newLine();
            }


            // default domains
            if ( defaultDomains.size() > 0 ) buf.newLine();
            buf._NC( "Default Domains: ")._( defaultDomains.size()  ).newLine();
            for (  AString key : defaultDomains.keySet() )
            {
                buf._NC( "  Domain:   " );
                AString s= defaultDomains.get( key );
                if ( s != null ) buf._( s ); else buf._( "null" );
                buf.tab( 25 );
                buf._NC( "Scope: \"" )._( key )._( '\"' ).newLine();
            }

            // Loggers (and their domains)
            if ( loggers.size() > 0 ) buf.newLine();
            buf._( "Loggers:          ")._( loggers.size()    ).newLine();

            SimpleDateFormat dateFormatter= new SimpleDateFormat( "yyyy-MM-dd HH:mm:ss", Locale.US );
            Date date = new Date();
            StringBuffer tempSB= new StringBuffer();

            for ( Logger logger : loggers )
            {
                tempSB.setLength( 0 );
                buf.newLine();
                buf._NC( "  Logger: \""            )._NC(  logger.name )._( '\"');
                if ( !logger.name.equals( logger.typeName) )
                    buf._NC( " Type: '" )._NC( logger.typeName )._( '\'' );
                buf.newLine();

                buf._NC( "    Creation Time: "     )._(  dateFormatter.format( logger.timeOfCreation.inJavaDate(date),
                                                                               tempSB,
                                                                               new FieldPosition( 0 ) )
                                                       ).newLine();
                buf._NC( "    Lines logged:  "     )._(  logger.cntLogs   ).newLine();
                buf._NC( "    Domains:"            )                       .newLine();

                for (Domain subDomain : logger.rootDomain.subDomains)
                    logConfigDomainRecursive( subDomain, 3, "      " , buf);
            }

            // now, log it out
            line( true, domain, level, buf, 0, loggerFilter );

        } finally { lock.release(); }
    }

    /** *********************************************************************************************
     * This method logs the configuration the Lox encapsulated in this static Log interface.
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  scope. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param level     The logging level.
     * @param headLine  If given, a separated headline will be logged at first place.
     **********************************************************************************************/
    public void logConfig(String domain, Log.Level level, String headLine)
    {
        logConfig( domain, level, headLine, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::VERBOSE "Level.VERBOSE".
     * This is the most verbose log level, which is only actually logged if the log domains'
     * log level is set to
     * \ref Log::DomainLevel::ALL "DomainLevel.ALL".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public void verbose(Object msg, int indent)
    {
        line( true, null, Log.Level.VERBOSE, msg, indent, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::VERBOSE "Level.VERBOSE".
     * This is the most verbose log level, which is only actually logged if the log domains'
     * log level is set to
     * \ref Log::DomainLevel::ALL "DomainLevel.ALL".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg   The message to log out.
     **********************************************************************************************/
    public void verbose(Object msg)
    {
        line( true, null, Log.Level.VERBOSE, msg, 0, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::VERBOSE "Level.VERBOSE".
     * This is the most verbose log level, which is only actually logged if the log domains'
     * log level is set to
     * \ref Log::DomainLevel::ALL "DomainLevel.ALL".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the scope.
     *                  file. For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public void verbose(String domain, Object msg, int indent)
    {
        line( true, domain, Log.Level.VERBOSE, msg, indent, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::VERBOSE "Level.VERBOSE".
     * This is the most verbose log level, which is only actually logged if the log domains'
     * log level is set to
     * \ref Log::DomainLevel::ALL "DomainLevel.ALL".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the scope.
     *                  For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log out.
     **********************************************************************************************/
    public void verbose(String domain, Object msg)
    {
        line( true, domain, Log.Level.VERBOSE, msg, 0, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::INFO "Level.INFO".
     * The log operation is only executed if the resulting log domains' log level is set to
     * \ref Log::DomainLevel::INFO_WARNINGS_AND_ERRORS "DomainLevel.INFO_WARNINGS_AND_ERRORS" or
     * \ref Log::DomainLevel::ALL                      "DomainLevel.ALL".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public void info(Object msg, int indent)
    {
        line( true, null, Log.Level.INFO, msg, indent, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::INFO "Level.INFO".
     * The log operation is only executed if the resulting log domains' log level is set to
     * \ref Log::DomainLevel::INFO_WARNINGS_AND_ERRORS "DomainLevel.INFO_WARNINGS_AND_ERRORS" or
     * \ref Log::DomainLevel::ALL                      "DomainLevel.ALL".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       The message to log out.
     **********************************************************************************************/
    public void info(Object msg)
    {
        line( true, null, Log.Level.INFO, msg, 0, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::INFO "Level.INFO".
     * The log operation is only executed if the resulting log domains' log level is set to
     * \ref Log::DomainLevel::INFO_WARNINGS_AND_ERRORS "DomainLevel.INFO_WARNINGS_AND_ERRORS" or
     * \ref Log::DomainLevel::ALL                      "DomainLevel.ALL".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the scope.
     *                  For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public void info(String domain, Object msg, int indent)
    {
        line( true, domain, Log.Level.INFO, msg, indent, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::INFO "Level.INFO".
     * The log operation is only executed if the resulting log domains' log level is set to
     * \ref Log::DomainLevel::INFO_WARNINGS_AND_ERRORS "DomainLevel.INFO_WARNINGS_AND_ERRORS" or
     * \ref Log::DomainLevel::ALL                      "DomainLevel.ALL".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the scope.
     *                  For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log.
     **********************************************************************************************/
    public void info(String domain, Object msg)
    {
        line( true, domain, Log.Level.INFO, msg, 0, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::WARNING "Level.WARNING".
     * This log level is enabled if the log domains' log level is set to
     * \ref Log::DomainLevel::ALL                      "DomainLevel.ALL",
     * \ref Log::DomainLevel::WARNINGS_AND_ERRORS      "DomainLevel.WARNINGS_AND_ERRORS" or
     * \ref Log::DomainLevel::INFO_WARNINGS_AND_ERRORS "DomainLevel.INFO_WARNINGS_AND_ERRORS".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public void warning(Object msg, int indent)
    {
        line( true, null, Log.Level.WARNING, msg, indent, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::WARNING "Level.WARNING".
     * This log level is enabled if the log domains' log level is set to
     * \ref Log::DomainLevel::ALL                      "DomainLevel.ALL",
     * \ref Log::DomainLevel::WARNINGS_AND_ERRORS      "DomainLevel.WARNINGS_AND_ERRORS" or
     * \ref Log::DomainLevel::INFO_WARNINGS_AND_ERRORS "DomainLevel.INFO_WARNINGS_AND_ERRORS".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg   The message to log out.
     **********************************************************************************************/
    public void warning(Object msg)
    {
        line( true, null, Log.Level.WARNING, msg, 0, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::WARNING "Level.WARNING".
     * This log level is enabled if the log domains' log level is set to
     * \ref Log::DomainLevel::ALL                      "DomainLevel.ALL",
     * \ref Log::DomainLevel::WARNINGS_AND_ERRORS      "DomainLevel.WARNINGS_AND_ERRORS" or
     * \ref Log::DomainLevel::INFO_WARNINGS_AND_ERRORS "DomainLevel.INFO_WARNINGS_AND_ERRORS".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the scope.
     *                  For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public void warning(String domain, Object msg, int indent)
    {
        line( true, domain, Log.Level.WARNING, msg, indent, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::WARNING "Level.WARNING".
     * This log level is enabled if the log domains' log level is set to
     * \ref Log::DomainLevel::ALL                      "DomainLevel.ALL",
     * \ref Log::DomainLevel::WARNINGS_AND_ERRORS      "DomainLevel.WARNINGS_AND_ERRORS" or
     * \ref Log::DomainLevel::INFO_WARNINGS_AND_ERRORS "DomainLevel.INFO_WARNINGS_AND_ERRORS".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the scope.
     *                  For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log.
     **********************************************************************************************/
    public void warning(String domain, Object msg)
    {
        line( true, domain, Log.Level.WARNING, msg, 0, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::ERROR "Level.ERROR".
     * This log level is always enabled, unless the log domains' log level is set to
     * \ref Log::DomainLevel::OFF  "DomainLevel.OFF".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public void error(Object msg, int indent)
    {
        line( true, null, Log.Level.ERROR, msg, indent, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::ERROR "Level.ERROR".
     * This log level is always enabled, unless the log domains' log level is set to
     * \ref Log::DomainLevel::OFF  "DomainLevel.OFF".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * @param msg       The message to log out.
     **********************************************************************************************/
    public void error(Object msg)
    {
        line( true, null, Log.Level.ERROR, msg, 0, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::ERROR "Level.ERROR".
     * This log level is always enabled, unless the log domains' log level is set to
     * \ref Log::DomainLevel::OFF  "DomainLevel.OFF".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the scope.
     *                  For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public void error(String domain, Object msg, int indent)
    {
        line( true, domain, Log.Level.ERROR, msg, indent, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object with log level equal to
     * \ref Log::Level::ERROR "Level.ERROR".
     * This log level is always enabled, unless the log domains' log level is set to
     * \ref Log::DomainLevel::OFF  "DomainLevel.OFF".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the scope.
     *                  For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log out.
     **********************************************************************************************/
    public void error(String domain, Object msg)
    {
        line( true, domain, Log.Level.ERROR, msg, 0, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object only if the given condition \p cond is not \e 'true'.
     * Log level will be highest, namely
     * \ref Log::Level::ERROR "Level.ERROR".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * \note This Method's name starts with capital letter, as \e 'assert' is a Java keyword.
     *
     * @param cond      The log is only performed if condition is not true.
     * @param msg       The message to log out.
     * @param indent    the indentation in the output.
     **********************************************************************************************/
    public void Assert(boolean cond, Object msg, int indent)
    {
        line( !cond, null, Log.Level.ERROR, msg, indent, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object only if the given condition \p cond is not \e 'true'.
     * Log level will be highest, namely
     * \ref Log::Level::ERROR "Level.ERROR".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * default domain set for the scope.
     *
     * \note This Method's name starts with capital letter, as \e 'assert' is a Java keyword.
     *
     * @param cond      The log is only performed if condition is not true.
     * @param msg       The message to log out.
     **********************************************************************************************/
    public void Assert(boolean cond, Object msg)
    {
        line( !cond, null, Log.Level.ERROR, msg, 0, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object only if the given condition \p cond is not \e 'true'.
     * Log level will be highest, namely
     * \ref Log::Level::ERROR "Level.ERROR".
     *
     * \note This Method's name starts with capital letter, as \e 'assert' is a Java keyword.
     *
     * @param cond      The log is only performed if condition is not true.
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  scope. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param msg       The message to log out.
     * @param indent    the indentation in the output.
     **********************************************************************************************/
    public void Assert(boolean cond, String domain, Object msg, int indent)
    {
        line( !cond, domain, Log.Level.ERROR, msg, indent, null );
    }

    /** *********************************************************************************************
     * Logs an arbitrary object only if the given condition \p cond is not \e 'true'.
     * Log level will be highest, namely
     * \ref Log::Level::ERROR "Level.ERROR".
     *
     * \note This Method's name starts with capital letter, as \e 'assert' is a Java keyword.
     *
     * @param cond      The log is only performed if condition is not true.
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  scope. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param msg       The message to log out.
     **********************************************************************************************/
    public void Assert(boolean cond, String domain, Object msg)
    {
        line( !cond, domain, Log.Level.ERROR, msg, 0, null );
    }

    /** *********************************************************************************************
     * Provides a the a more flexible but complex way to log a message. The methods #verbose(),
     * #info(), #warning(), #error() and #Assert() are using this function internally and should
     * be used in standard cases. Use this function only in the rare cases, e.g. when a log level is
     * decided only at runtime or when you want to use a logger filter, etc.
     *
     * @param doLog         Conditional logging. If false, the log is not performed. CntLogCalls is
     *                      still increased by one.
     * @param domain        If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the scope. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param level         The log level.
     * @param msgObject     An Object to be logged.
     * @param indent        The indentation in the output.
     * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
     *                      loggers to have different domains. A simple string compare without case
     *                      sensitivity is performed. An asterisk ('*') at the beginning or end of
     *                      the string is used as a wildcard. Leave to \e null if all loggers should be
     *                      affected. Use this parameter only in more complex logging scenarios.
     *
     *
     *
     *
     **********************************************************************************************/
    public void line(boolean doLog, String domain, Log.Level level, Object msgObject, int indent, String loggerFilter)
    {
        // auto-initialization of ALox
        Log.init( true, null );

        // auto-initialization of debug loggers
        if( loggers.size() == 0 && this == Log.LOX )
            Log.addDebugLogger( this, true );

        try
        {
            lock.acquire();

            // count overall calls
            cntLogCalls++;

            // check the condition
            if (!doLog || loggers.size() == 0)
                return;

            // initialize caller information
            caller.set( threadDictionary, omittablePackagePrefixes );

            // setup domain
            evaluateResultDomain( domain );

            // loop over all loggers
            for (Logger logger : loggers)
                if (simpleWildcardFilter( logger, loggerFilter ))
                    if ( !logger.line( resDomain, level, msgObject, indent, caller ) )
                    {
                        tempAS._()._("Domain Resolution: Domain '"         )._(resDomain)
                                  ._("' implicitly registered for Logger '")._( logger.name )
                                  ._("' Inherited DomainLevel: "           )
                                  ._(logger.rootDomain.find( resDomain, null ).getLevel().toString());
                        internalLog( Log.Level.INFO, tempAS );
                    }

            // release lock if msgObject was our internal log buffer singleton
            if (msgObject == logBuf) logBufLock.release();

        }
        finally
        {
            lock.release();
        }
    }

    /** *********************************************************************************************
     * Conditionally logs an Object using the given log level, log domain and indentation.
     *
     * @param doLog     Conditional logging. If false, the log is not performed. CntLogCalls is still
     *                  increased by one.
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  scope. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param level     The log level.
     * @param msgObject An Object to be logged.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public void line(boolean doLog, String domain, Log.Level level, Object msgObject, int indent)
    {
        line( doLog, domain, level, msgObject, indent, null );
    }

    /** *********************************************************************************************
     * Conditionally logs an Object using the given log level and log domain.
     *
     * @param doLog     Conditional logging. If false, the log is not performed. CntLogCalls is still
     *                  increased by one.
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  scope. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param level     The log level.
     * @param msgObject An Object to be logged.
     **********************************************************************************************/
    public void line(boolean doLog, String domain, Log.Level level, Object msgObject)
    {
        line( doLog, domain, level, msgObject, 0, null );
    }

    /** *********************************************************************************************
     * Logs an Object using the given log level and log domain.
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  scope. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param level     The log level.
     * @param msgObject An Object to be logged.
     **********************************************************************************************/
    public void line(String domain, Log.Level level, Object msgObject)
    {
        line( true, domain, level, msgObject, 0, null );
    }

    /** *********************************************************************************************
     * Logs an Object using the given log level and the default domain for this scope.
     *
     * @param level     The log level.
     * @param msgObject An Object to be logged.
     **********************************************************************************************/
    public void line(Log.Level level, Object msgObject)
    {
        line( true, null, level, msgObject, 0, null );
    }

    /** *********************************************************************************************
     * Logs an Object using the given log level and indentation using the default domain for this scope.
     *
     * @param level     The log level.
     * @param msgObject An Object to be logged.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public void line(Log.Level level, Object msgObject, int indent)
    {
        line( true, null, level, msgObject, indent, null );
    }

    /** *********************************************************************************************
     * Logs an Object using the given log level, indentation and logger filter using the default domain
     * for this scope.
     *
     * @param level         Conditional logging. If false, the log is not performed. CntLogCalls is
     *                      still increased by one.
     * @param msgObject     If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the scope. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param indent        The indentation in the output.
     * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
     *                      loggers to have different domains. A simple string compare without case
     *                      sensitivity is performed. An asterisk ('*') at the beginning or end of
     *                      the string is used as a wildcard. Leave to \e null if all loggers should be
     *                      affected. Use this parameter only in more complex logging scenarios.
     **********************************************************************************************/
    public void line(Log.Level level, Object msgObject, int indent, String loggerFilter)
    {
        line( true, null, level, msgObject, indent, loggerFilter );
    }

    //*****************************************************************************
    //***  internals
    //*****************************************************************************

        /** ****************************************************************************************
         *  Using the optionally provided domain. Any default domain previously set according to
         *  the caller's scope. The resulting full domain string is evaluated as follows:
         *  If no domain given, the default domain is retrieved (depending on the caller's scope).
         *  If a domain is given it is used. If it is starting with a swung dash("~"), it is interpreted
         *  to be a sub domain of the default domain and both domains are concatenated.
         *
         * @param domain      A domain or path. If starting with a swung dash ('~') it is interpreted as
         *                    being a sub domain of the default domain defined for the current caller's scope.
         ******************************************************************************************/
        protected  void evaluateResultDomain( String domain  )
        {
            // clear resulting domain name buffer
            resDomain.clear();

            // get default domain name (if needed later)
            AString    defaultDomain=    null;
            boolean    noDomainGiven=    CString.isNullOrEmpty( domain );
            if ( noDomainGiven || domain.charAt( 0 ) == '~' )
            {
                tempAS.clear()._( caller.packageName );       int strLengthPkgScope=      tempAS.length();
                tempAS._( '#' )._( caller.className );        int strLengthClassScope=    tempAS.length();
                tempAS._( '#' )._( caller.methodName);

                defaultDomain= defaultDomains.get( tempAS );
                if ( CString.isNullOrEmpty( defaultDomain ) )
                {
                    tempAS.setLength_NC( strLengthClassScope );

                    defaultDomain= defaultDomains.get( tempAS );
                    if ( CString.isNullOrEmpty( defaultDomain ) )
                    {
                        tempAS.setLength_NC( strLengthPkgScope );
                        defaultDomain= defaultDomains.get( tempAS );
                    }
                }
            }


            // no domain given
            if ( noDomainGiven )
            {
                // return resulting domain
                if ( !CString.isNullOrEmpty( defaultDomain ) )
                {
                    resDomain._( defaultDomain );
                    return;
                }

                // Warning: neither domain nor default domain given
                if ( errIfNoDefaultDomain > 0 )
                {
                    errIfNoDefaultDomain--;
                    internalLog( Log.Level.ERROR,
                                 tempAS.clear() ._("Domain Resolution: No log domain given and default domain not set for scope \"")
                                                ._(caller.packageName)
                                                ._('.')._(caller.className)
                                                ._('.')._(caller.methodName)._("\".")
                                );
                }
                resDomain._( nullDomain );
                return;
            }

            // domain starts with '~' ?    Relative path
            int start=    0;
            if ( domain.charAt( 0 ) == '~' )
            {
                // cut the ~ character
                start=    1;

                // found one? build complete path
                if ( defaultDomain != null )
                    resDomain._( defaultDomain );
                else
                {
                    // not set? -> remove the ~ symbol and go ahead
                    internalLog( Log.Level.ERROR,
                                 tempAS.clear() ._("Domain Resolution: Relative domain path given: \"")._(domain)
                                                ._("\", but default domain is not set for scope \"")
                                                ._(caller.packageName)._('.')
                                                ._(caller.className)._('.')
                                                ._(caller.methodName)._("\".")  );
                }
            }

            // remove any potential leading separator
            int len=    domain.length();
            while (start < len && ( Domain.domainSeparatorChars.indexOf( domain.charAt( start ) ) >= 0 ) )
                start++;

            // add domain to the path
            if (start < len )
            {
                if ( resDomain.isNotEmpty() )
                    resDomain._( '/' );
                int oldLength= resDomain.length();
                resDomain._NC( domain, start, len-start );
                resDomain.toUpper( oldLength );
            }
        }

        /** ****************************************************************************************
         * Logs an internal error message to the domain given by field InternalDomain. Attn: must only
         * be called after saveAndSet() was performed.
         *
         * @param level The logging level.
         * @param msg   The message.
         ******************************************************************************************/
        protected  void internalLog( Log.Level level, AString msg )
        {
            // decrease log counter, as internal Log should not count
            cntLogCalls--;

            // log msg on InternalDomain
            String backup= resDomain.toString();
            line( true, internalDomain, level, msg , 0, null );
            resDomain._()._(backup);

            // reset the caller timestamp to avoid negative time differences in subsequent log call
            caller.timeStamp.set();
        }

        /** ****************************************************************************************
         * Compares a loggers name with a filter string with simplest wildcard support ('*') at the
         * beginning or end of the string. If loggerFilter is null, a match is indicated.
         *
         * @param logger        The logger to be filtered.
         * @param loggerFilter  The filter.
         *
         * @return  True if logger is not filtered out.
         ******************************************************************************************/
        private static  boolean simpleWildcardFilter( Logger logger, String loggerFilter )
        {
            final String asterisk = "*";

            // null or empty? -> return TRUE (!)
            if ( CString.isNullOrEmpty( loggerFilter ) )
                return true;

            // wildcard at start?
            boolean startWC= false;
            if ( loggerFilter.charAt( 0 ) == '*' )
            {
                loggerFilter=    loggerFilter.substring( 1 );
                startWC=        true;
            }

            // wildcard at end?
            boolean endWC= false;
            if ( loggerFilter.endsWith ( asterisk ) )
            {
                loggerFilter=    loggerFilter.substring( 0, loggerFilter.length() - 1 );
                endWC=        true;
            }

            // wildcard at start?
            if ( startWC )
            {
                // both?
                if ( endWC )
                    return CString.indexOfIgnoreCase( logger.name, loggerFilter ) >= 0;

                // at start only
                return  CString.endsWithIgnoreCase( logger.name, loggerFilter );
            }

            // at end
            if ( endWC)
                return CString.startsWithIgnoreCase( logger.name, loggerFilter );

            // no wildcard
            return logger.name.equalsIgnoreCase( loggerFilter );
        }

        /** ****************************************************************************************
         * Internal method used by LogConfig() to recursively log Domain instances.
         *
         * @param domain    The Domain instance to log out.
         * @param indent    The indentation in the output, recursively increased..
         * @param domPath   Actual path relative to recursion, solely for log output.
         * @param buf       The buffer to log to.
         ******************************************************************************************/
        protected  void logConfigDomainRecursive( Domain domain, int indent, String domPath, AString buf)
        {
            // append /ME to domain path string
            domPath= domPath + "/" + domain.name;

            // add  domain name and log level
            buf._( domPath  )    .tab( 25 )    ._( domain.getLevel().toString() )  .newLine();

            // loop over all sub domains (recursion)
            for ( Domain subDomain : domain.subDomains )
                logConfigDomainRecursive( subDomain, indent + 1, domPath, buf );
        }
}


