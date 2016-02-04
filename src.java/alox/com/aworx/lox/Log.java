// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

import java.util.Date;

import com.aworx.lib.ALIB;
import com.aworx.lib.Report;
import com.aworx.lib.ReportWriter;
import com.aworx.lib.enums.Propagation;
import com.aworx.lib.enums.Switch;
import com.aworx.lib.strings.AString;
import com.aworx.lib.threads.ThreadLock;
import com.aworx.lox.core.Logger;
import com.aworx.lox.core.textlogger.TextLogger;

// #############################################################################################
// Define and set ALox based ALib \b %ReportWriter
// #############################################################################################

    /** ****************************************************************************************
     *  The \b %ReportWriter for ALib when using ALox. An instance of this class is
     *  created in method \ref com::aworx::lox::Log::addDebugLogger "Log.addDebugLogger"
     *  and registered with ALib.
     ******************************************************************************************/
    class ALoxReportWriter implements ReportWriter
    {
        /** The \b Lox to report to */
        protected   Lox        lox;

        /** ************************************************************************************
         * Constructs an \b %ALoxReportWriter.
         * @param lox    The \b Lox to report to.
         **************************************************************************************/
        public ALoxReportWriter ( Lox lox ) { this.lox= lox; }

        /** ************************************************************************************
         * Log an ALib report using ALox.
         * @param report  The error message.
         **************************************************************************************/
        @Override
        public void report  (Report.Message report)
        {
            if( report.type == 0 )
                Log.error  ( "REPORT", report.contents );
            else
                Log.warning( "REPORT", report.contents );
        }
    }

/** ************************************************************************************************
 * This is a simple, 100% static wrapper of class Lox. In other words, this class incorporates
 * one static singleton of Lox and mirrors the whole non static interface of Lox into a static
 * one.
 *
 * The exclusive use of this class covers the vast majority of all debug logging scenarios.
 * For release logging, remote logging and similar scenarios, the use of a dedicated instance of
 * class Lox is needed.
 *
 * Use your preferred java byte code processing tool (e.g. Proguard) to remove all method
 * invocations to this class from your release code.
 *
 * In addtion, this class defines important public enumerations, provides library initialization and
 * other static functionality.
 *
 *  This class is flagged 'abstract' to prevent instance creation.
 **************************************************************************************************/
public abstract class Log
{
    // #############################################################################################
    // Public Enums
    // #############################################################################################

        /** ****************************************************************************************
         * These are the levels of log verbosity assignable to a log domain.
         ******************************************************************************************/
        public enum DomainLevel
        {
            /** Do not log anything. */
            OFF,

            /** %Log only level Error. */
            ERRORS,

            /** %Log only levels Warning or Error. */
            WARNINGS_AND_ERRORS,

            /** %Log all  levels but Verbose. */
            INFO_WARNINGS_AND_ERRORS,

            /** %Log all. */
            ALL,

            /** Inherit level from parent domain. */
            INHERIT,
        }

        /** ****************************************************************************************
         * These are the levels of log verbosity used in a log call.
         ******************************************************************************************/
        public enum Level
        {
            /** The most verbose log level to be used for debug output statements. Logged only if
                the domains log level is set to DomainLevel.All. */
            VERBOSE,

            /** The standard log level for normal log output statements. Logged if the domains
                level is either DomainLevel.All or DomainLevel.InfoWarningsAndErrors. */
            INFO,

            /** A log level for warning messages, hence things that might lead to errors or are not
                welcome for other reasons, but maybe are not errors.
                It is not logged only if the domains log level is DomainLevel.Errors or Domain.Level.Off. */
            WARNING,

            /** A log level for (severe) error messages.
                It is suppressed only if the domains log level is set to DomainLevel.Off. */
            ERROR,
        }

        /** ****************************************************************************************
         * These are definitions which are used as a parameter to certain ALox methods to determine the
         * breadth of the scope of a setting. The definitions are platform dependent. E.g. in C# the
         * scope can be "method" or "source" file while in Java it can be "package", "class" or
         * "method". The difference is due to different mechanisms to automatically collect caller
         * information.
         ******************************************************************************************/
        public enum Scope
        {
            /** No scope should be applied/affected. */
            NONE,

            /** Defines the actual package as the scope. */
            PACKAGE,

            /** Defines the actual class as the scope. */
            CLASS,

            /** Defines the actual method as the scope. */
            METHOD,
        }

    // #############################################################################################
    // Public static fields
    // #############################################################################################

        /**
         * The version of ALox. The version number follows the scheme YYMM (2-digit year, 2-digit month)
         * of the initial release date.
         * Besides this version number, field #revision indicates if this is a revised version
         * of a former release.
         */
        public static final int         version                                               =1601;

        /**
         * The revision number of this release. Each ALox #version is initially released as
         * revision \e 0. Pure maintenance releases that do not change the interface of ALox
         * are holding the same #version but an increased number in this field.
         */
        public static final int         revision                                                 =0;

        /// This is a static singleton of type class Lox which is used for standard
        /// debug logging statements.
        public static Lox               LOX                                              =new Lox();

        /// The debug logger created by AddDebugLogger.
        public static TextLogger        debugLogger                                           =null;

        /**
         * The ALib ReportWriter. This will be created and registered in method
         * \ref com::aworx::lox::Log::addDebugLogger    "Log.addDebugLogger" and removed in
         * \ref com::aworx::lox::Log::removeDebugLogger "Log.removeDebugLogger".
         */
        public static ALoxReportWriter  debugReportWriter                                     =null;


    // #############################################################################################
    // Protected static fields
    // #############################################################################################

        /** A log buffer singleton. Can be acquired, using buf() */
        protected static LogBuf         logBuf                                        =new LogBuf();

        /** A locker for the log buffer singleton */
        protected static ThreadLock     logBufLock                                =new ThreadLock();

    // #############################################################################################
    // Library initialization
    // #############################################################################################

        /**
         * The name of the configuration category of configuration variables used by ALox.<br>
         * Defaults to "ALOX".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #init.<br>
         * See also \ref com::aworx::lib::ALIB::configCategoryName "ALIB.configCategoryName".
         */
        public  static String           configCategoryName                                  ="ALOX";

        /** ****************************************************************************************
         * Static library code
         ******************************************************************************************/
        static
        {
            // set recursion warning of log buffer lock to 1.
            // Warnings are logged if recursively acquired more than once
            logBufLock.recursionWarningThreshold= 1;
        }

        /**  State of initialization, used to avoid double initialization.   */
        protected static      boolean   isInitialized= false;

        /** ****************************************************************************************
         * This method must (may) be called prior to using the ALox library, e.g. at the beginning
         * of the main() method of an application. It is OK, to call this method more than once,
         * which allows independent code blocks (e.g. libraries) to bootstrap ALox without
         * interfering. But only the first call is effective and may be used to set the
         * command line arguments as configuration plug-in.
         *
         * In the Java version of the AWorx library, the invocation of this method is optional.
         * However, it is good practice to invoke this method in the main() method of a process
         * and provide the command line arguments.
         * See \ref com::aworx::lib::ALIB::init "ALIB.init"
         * for more information on the configuration parameters.
         *
         * @param useEnv  If true, a
         *                \ref com::aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         *                is attached to the
         *                \ref com::aworx::lib::ALIB::config "ALIB.config" singleton. Hence,
         *                environment variables are read and potentially overwrite
         *                configuration variables in other configuration plug-ins.<br>
         * @param args    Parameter which in the standard case is taken from  C/C++ main()
         *                method providing the command line arguments.
         *                If arguments are provided, a
         *                \ref aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn"
         *                is attached to the
         *                \ref aworx::lib::ALIB::config "ALIB.config" singleton. Hence,
         *                command line options are read and those potentially overwrite
         *                configuration variables in other configuration plug-ins.<br>
         *******************************************************************************************/
        public static void     init(  boolean useEnv, String[] args )
        {
            if ( isInitialized )
                return;
            isInitialized= true;

            // initialize ALIB
            ALIB.init( useEnv, args );
        }

    // #############################################################################################
    // Interface methods NOT copied from Lox (auto removed)
    // #############################################################################################

        /** ************************************************************************************
         * This method creates an adequate/default debug logger using
         *   \ref com::aworx::lox::Lox::createConsoleLogger "Lox.createConsoleLogger"
         * and attaches it to the debug instance of class
         * \ref com::aworx::lox::Lox "Lox".
         * Of-course, alternatively to using this method, a suitable set of
         * debug loggers can be created manually. Also, before/after using this method
         * additional debug loggers may be created.
         *
         * Finally, \ref com::aworx::lib::Report::replaceWriter "Report.replaceWriter"
         * is invoked to provide a ReportWriter of type
         * \ref com::aworx::lox::ALoxReportWriter "ALoxReportWriter".
         *
         * @param lox The lox to add the debug logger(s) to. If null, the static debug object
         *            #LOX is used.
         *            Defaults to null
         * @param replaceDefaultReportWriter
         *             If true, the
         *             \ref com::aworx::lib::ReportWriter "ReportWriter" of the \b Report returned by
         *             \ref com::aworx::lib::Report::getDefault "Report.getDefault()"
         *             will be replaced by an object of type
         *             \ref com::aworx::lox::ALoxReportWriter "ALoxReportWriter" using the given
         *             \p lox;
         **************************************************************************************/
        public static void addDebugLogger( Lox lox, boolean replaceDefaultReportWriter )
        {
            if ( lox == null )
                lox= LOX;

            ALIB.ASSERT_ERROR( debugLogger == null, "Illegal double invocation." );

            // add a default console logger
            debugLogger= Lox.createConsoleLogger( "DEBUG_LOGGER" );

            if ( debugLogger != null )
            {
                lox.addLogger( debugLogger );

                // replace the ReportWriter
                if ( replaceDefaultReportWriter )
                    Report.getDefault().replaceWriter( debugReportWriter= new ALoxReportWriter( lox ) );


                // get auto sizes from last session
                AString autoSizes= new AString();
                if( ALIB.config.get( Log.configCategoryName, "CL_AUTO_SIZES", autoSizes ) != 0 )
                    debugLogger.autoSizes.importValues( autoSizes );
            }
        }

        /** ************************************************************************************
         * This method invokes #addDebugLogger(Lox) providing the value \c true for
         * parameter \p replaceDefaultReportWriter.
         * @param lox The lox to add the debug logger(s) to. If null, the static debug object
         *           #LOX is used.
         *           Defaults to null
         **************************************************************************************/
        public static void addDebugLogger(Lox lox)
        {
            addDebugLogger( lox, true );
        }

        /** ************************************************************************************
         * This method invokes #addDebugLogger(Lox) providing the static debug instance #LOX.
         * and the value \c true for parameter \p replaceDefaultReportWriter.
         **************************************************************************************/
        public static void addDebugLogger()
        {
            addDebugLogger( LOX, true );
        }

        /** ************************************************************************************
         * Removes the logger(s) which was/were created by \ref addDebugLogger.
         *  This method also invokes
         *  \ref com::aworx::lib::Report::replaceWriter "Report.replaceWriter(null)"
         *  to install a default \ref aworx::lib::ReportWriter "ReportWriter" for ALib.
         *
         * @param lox The lox to remove the debug logger from.
         *           If null, the static debug object#LOX is used.
         **************************************************************************************/
        public static void removeDebugLogger( Lox lox )
        {
            // replace the report writer (if we replaced it before)
            if( debugReportWriter != null )
                Report.getDefault().replaceWriter( null );

            if ( lox == null )
                lox= LOX;

            ALIB.ASSERT_ERROR( debugLogger != null, "No debug logger to remove." );

            if ( debugLogger != null )
            {
                lox.removeLogger( debugLogger );

                // save auto sizes
                AString autoSizes= new AString();
                debugLogger.autoSizes.exportValues( autoSizes );
                ALIB.config.save( Log.configCategoryName, "CL_AUTO_SIZES", autoSizes,
                                   "Auto size values of last debug logger instance" );
                debugLogger= null;
            }


        }

        /** ************************************************************************************
         * This method invokes #removeDebugLogger(Lox) providing the static debug instance #LOX.
         **************************************************************************************/
        public static void removeDebugLogger()
        {
            removeDebugLogger( LOX );
        }

    // #############################################################################################
    // Interface methods copied from Lox (to be pruned)
    // #############################################################################################

    /** ********************************************************************************************
     * Returns a LogBuf singleton, similar to the AString singleton returned by Lox.buf(). Class
     * LogBuf is a pruneable mimic of AString. Hence working with LogBuf instead of AString is
     * allowed only for debug logging purposes, not for release logging.<br>
     * Whenever this method is called, the returned LogBuf object has to be used as a message within
     * one of the log methods of this class (error(), warning(), info(), verbose(), assert() or line()).
     * If this is not done, the object does not get released and parallel threads using it would
     * be blocked! So, do not use buf() for other reasons than for creating log messages and be sure to
     * re-acquire the LogBuf object by calling this method again prior to the next log call.
     *
     * @return the static LogBuf singleton.
     **********************************************************************************************/
    public static LogBuf buf()
    {
        logBufLock.acquire();
        logBuf.clear();
        return logBuf;
    }

    /** *********************************************************************************************
     *  Use this method when you want to abort a log call that you "started" with acquiring the internal
     *  LogBuf singleton acquired using method buf(). Use bufAbort() only if you did not use the
     *  acquired buffer as a parameter of a log method, because this internally releases the buf already.
     **********************************************************************************************/
    public static void bufAbort()
    {
        logBufLock.release();
    }

    /** ********************************************************************************************
     * Adds a logger to this container of loggers.
     * Each log call that is performed through this classes' interface
     * will be forwarded to this logger, unless filtered out with optional filter parameter.
     *
     * \note
     *   This method checks whether the domain used for internal ALox messages
     *   (see field
     *   \ref com::aworx::lox::Lox::internalDomain "Lox.internalDomain")
     *   is already registered with the given logger.
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
    public static void addLogger(Logger logger)
    {
        LOX.addLogger( logger );
    }

    /** *********************************************************************************************
     * Retrieve an instance of a Logger by its name.
     *
     * @param loggerName    The name of the logger to search for (case insensitive)
     *
     * @return  The logger, null if not found.
     **********************************************************************************************/
    public static Logger getLogger(String loggerName)
    {
        return LOX.getLogger( loggerName );
    }

    /** *********************************************************************************************
     *  Removes a logger from this container.
     *  @param logger   The logger to be removed.
     *  @returns True, if the logger was found and removed, false otherwise.
     **********************************************************************************************/
    public static boolean removeLogger( Logger logger )
    {
        return LOX.removeLogger( logger );
    }

    /** *********************************************************************************************
     * Removes all loggers that match the filter name from this  interface.
     *
     * @param loggerFilter  A filter for the loggers to be affected. A simple string compare without
     *                      case sensitivity is performed. An asterisk ('*') at the beginning or end
     *                      of the string is used as a wildcard. Defaults to null which causes all
     *                      loggers to be removed.
     *  @returns The number of loggers that were removed.
     **********************************************************************************************/
    public static int removeLoggers(String loggerFilter)
    {
        return LOX.removeLoggers( loggerFilter );
    }

    /** *********************************************************************************************
     * Removes all loggers this interface.
     *  @returns The number of loggers that were removed.
     **********************************************************************************************/
    public static int removeLoggers()
    {
        return LOX.removeLoggers( null );
    }

    /** *********************************************************************************************
     * This method should not be used in standard applications. It was added to support clean unit
     * testing. This method disposes the internal static Lox and with it all loggers, preferences
     * and stuff and replaces it with a fresh one.
     **********************************************************************************************/
    public static void reset()
    {
        LOX=                new Lox();
        debugLogger=        null;
        logBuf=             new LogBuf();
        logBufLock=         new ThreadLock();
        logBufLock.recursionWarningThreshold= 1;
        configCategoryName= "ALOX";
    }

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
     *                  domain of the source file. For other values, the default    domain is ignored
     *                  (regardless if this is starting with a slash or not).
     * @param scope     If a value other than Log.Scope.None is provided, the given domain name is
     *                  registered as the default domain for the given scope. Default domains set for
     *                  'inner scopes' have higher priority than those set for outer scopes. Available
     *                  Scope definitions are platform/language dependent.
     **********************************************************************************************/
    public static void setDomain(String domain, Log.Scope scope)
    {
        LOX.setDomain( domain, scope );
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
     *                      of the source file. For other values, the default domain is ignored
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
    public static void setDomain( String  domain,         Log.DomainLevel  domainLevel,
                                  String  loggerFilter,   Propagation      propagation     )
    {
        LOX.setDomain( domain, domainLevel, loggerFilter, propagation );
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
     *                      of the source file. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param domainLevel   The domains log level to be set.
     * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
     *                      loggers to have different domains and log levels. A simple string compare
     *                      without case sensitivity is performed. An asterisk ('*') at the beginning
     *                      or end of the string is used as a wildcard. Leave to \e null if all loggers
     *                      should be affected. Use this parameter only in more complex logging
     *                      scenarios.
     **********************************************************************************************/
    public static void setDomain( String  domain,       Log.DomainLevel domainLevel,
                                  String  loggerFilter                                )
    {
        LOX.setDomain( domain, domainLevel, loggerFilter, Propagation.TO_DESCENDANTS );
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
     *                      of the source file. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param domainLevel   The domains log level to be set.
     **********************************************************************************************/
    public static void setDomain( String domain, Log.DomainLevel domainLevel )
    {
        LOX.setDomain( domain, domainLevel, null, Propagation.TO_DESCENDANTS );
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
    public static void setDomain( String domain, Log.Scope scope, Log.DomainLevel domainLevel,
                                  String loggerFilter )
    {
        LOX.setDomain( domain, scope, domainLevel, loggerFilter );
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
    public static void setDomain( String domain, Log.Scope scope, Log.DomainLevel domainLevel )
    {
        LOX.setDomain( domain, scope, domainLevel );
    }

    /** *********************************************************************************************
     * <c>setDomain(domain, scope)</c> and <c>setDomain(domain, domainLevel)</c>.
     *
     * @param domain        If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the source file. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param domainLevel   The domains log level to be set.
     * @param scope         If a value other than Log.Scope.None is provided, the given domain name is
     *                      registered as the default domain for the given scope. Default domains set for
     *                      'inner scopes' have higher priority than those set for outer scopes. Available
     *                      Scope definitions are platform/language dependent.
     **********************************************************************************************/
    public static void setDomain( String domain, Log.DomainLevel domainLevel, Log.Scope scope )
    {
        LOX.setDomain( domain, domainLevel, scope );
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
    public  static void setLogger( Switch newState, String loggerFilter )
    {
        LOX.setLogger( newState, loggerFilter );
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
     *                      of the string is used as a wildcard. Leave to \e null if all loggers should be
     *                      affected.
     **********************************************************************************************/
    public static void setStartTime(Date startTime, String loggerFilter)
    {
        LOX.setStartTime( startTime, loggerFilter );
    }

    /** *********************************************************************************************
     * This method is used reset (or to explicitly set) the start time of the logger(s). The only
     * impact is the output of time differences in the log lines. Hence, it is useful to see some
     * absolute time values when doing basic performance tests using the logger.
     *
     * @param startTime     Optional parameter with the  new start time. Defaults to DateTime.Now if
     *                      omitted.
     **********************************************************************************************/
    public static void setStartTime(Date startTime)
    {
        LOX.setStartTime( startTime, null );
    }

    /** *********************************************************************************************
     * This method is used reset the start time of the logger(s) to now. The only impact is the
     * output of time differences in the log lines. Hence, it is useful to see some absolute time
     * values when doing basic performance tests using the logger.
     **********************************************************************************************/
    public static void setStartTime()
    {
        LOX.setStartTime( null, null );
    }

    /** *********************************************************************************************
     * This method sets a human readable name to the given thread ID (or current thread) which is
     * optionally included in each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     * @param id            Parameter providing the thread ID. If set to -1, the current thread's ID is
     *                      used.
     **********************************************************************************************/
    public static void mapThreadName(String threadName, long id)
    {
        LOX.mapThreadName( threadName, id );
    }

    /** *********************************************************************************************
     * This method sets a human readable name to the current thread which is optionally included in
     * each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     **********************************************************************************************/
    public static void mapThreadName(String threadName)
    {
        LOX.mapThreadName( threadName, -1 );
    }

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
    public static void setMarker(Object marker, Log.Scope scope)
    {
        LOX.setMarker( marker, scope );
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
    public static Object getMarker( Log.Scope scope )
    {
        return LOX.getMarker(  scope );
    }

    /** *********************************************************************************************
     * This method logs the configuration the Lox encapsulated in this static Log interface.
     *
     * @param domain        If this is null, the default domain is used. If this is starting with a
     *                      swung dash ('~') this is interpreted a sub domain to the default domain
     *                      of the source file. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param level         The log level.
     * @param headLine      If given, a separated headline will be logged at first place.
     * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
     *                      loggers to have different domains. A simple string compare without case
     *                      sensitivity is performed. An asterisk ('*') at the beginning or end of
     *                      the string is used as a wildcard. Leave to \e null if all loggers should be
     *                      affected. Use this parameter only in more complex logging scenarios.
     **********************************************************************************************/
    public static void logConfig(String domain, Log.Level level, String headLine, String loggerFilter)
    {
        LOX.logConfig( domain, level, headLine, loggerFilter );
    }

    /** *********************************************************************************************
     * This method logs the configuration the Lox encapsulated in this static Log interface.
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  source file. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param level     The log level.
     * @param headLine  If given, a separated headline will be logged at first place.
     **********************************************************************************************/
    public static void logConfig(String domain, Log.Level level, String headLine)
    {
        LOX.logConfig( domain, level, headLine, null );
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Log.Level.Verbose. This is the highest (most
     * verbose) log level, which is only actually logged if the log domains log level is set to
     * "All". This overloaded version does not offer a domain parameter but relies on a default
     * domain set for the source file this function is used in.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public static void verbose(Object msg, int indent)
    {
        LOX.line( true, null, Log.Level.VERBOSE, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
     * log level, which is only actually logged if the log domains log level is set to "All". This
     * overloaded version does not offer a domain parameter but relies on a default domain set for
     * the source file this function is used in.
     *
     * @param msg   The message to log out.
     **********************************************************************************************/
    public static void verbose(Object msg)
    {
        LOX.line( true, null, Log.Level.VERBOSE, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
     * log level, which is only actually logged if the log domains log level is set to "All".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public static void verbose(String domain, Object msg, int indent)
    {
        LOX.line( true, domain, Log.Level.VERBOSE, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
     * log level, which is only actually logged if the log domains log level is set to "All".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log out.
     **********************************************************************************************/
    public static void verbose(String domain, Object msg)
    {
        LOX.line( true, domain, Log.Level.VERBOSE, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
     * Verbose) log level, which is only actually logged if the log domains log level is set to
     * "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
     * a default domain set for the source file this function is used in.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public static void info(Object msg, int indent)
    {
        LOX.line( true, null, Log.Level.INFO, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
     * Verbose) log level, which is only actually logged if the log domains log level is set to
     * "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
     * a default domain set for the source file this function is used in.
     *
     * @param msg       The message to log out.
     **********************************************************************************************/
    public static void info(Object msg)
    {
        LOX.line( true, null, Log.Level.INFO, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
     * Verbose) log level, which is only actually logged if the log domains log level is set to
     * "Info" or "Verbose".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardles if this is
     *                  starting with a slash or not).
     * @param msg       The message to log.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public static void info(String domain, Object msg, int indent)
    {
        LOX.line( true, domain, Log.Level.INFO, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
     * Verbose) log level, which is only actually logged if the log domains log level is set to
     * "Info" or "Verbose".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardles if this is
     *                  starting with a slash or not).
     * @param msg       The message to log.
     **********************************************************************************************/
    public static void info(String domain, Object msg)
    {
        LOX.line( true, domain, Log.Level.INFO, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
     * are logged if the log domains log level is set to "Warning", "Info" or "All". This overloaded
     * version does not offer a domain parameter but relies on a default domain set for the source
     * file this function is used in.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public static void warning(Object msg, int indent)
    {
        LOX.line( true, null, Log.Level.WARNING, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
     * are logged if the log domains log level is set to "Warning", "Info" or "All". This overloaded
     * version does not offer a domain parameter but relies on a default domain set for the source
     * file this function is used in.
     *
     * @param msg   The message to log out.
     **********************************************************************************************/
    public static void warning(Object msg)
    {
        LOX.line( true, null, Log.Level.WARNING, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
     * are logged if the log domains log level is set to "Warning", "Info" or "All".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public static void warning(String domain, Object msg, int indent)
    {
        LOX.line( true, domain, Log.Level.WARNING, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
     * are logged if the log domains log level is set to "Warning", "Info" or "All".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log.
     **********************************************************************************************/
    public static void warning(String domain, Object msg)
    {
        LOX.line( true, domain, Log.Level.WARNING, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
     * always logged unless domains log level is set to "Off". This overloaded version does not
     * offer a domain parameter but relies on a default domain set for the source file this function
     * is used in.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public static void error(Object msg, int indent)
    {
        LOX.line( true, null, Log.Level.ERROR, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
     * always logged unless domains log level is set to "Off". This overloaded version does not
     * offer a domain parameter but relies on a default domain set for the source file this function
     * is used in.
     *
     * @param msg       The message to log out.
     **********************************************************************************************/
    public static void error(Object msg)
    {
        LOX.line( true, null, Log.Level.ERROR, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
     * always logged unless domains log level is set to "Off".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public static void error(String domain, Object msg, int indent)
    {
        LOX.line( true, domain, Log.Level.ERROR, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
     * always logged unless domains log level is set to "Off".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log out.
     **********************************************************************************************/
    public static void error(String domain, Object msg)
    {
        LOX.line( true, domain, Log.Level.ERROR, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log a string only if the given condition is not true. Log level will be highest, namely Error
     * if condition is false. This overloaded version does not offer a domain parameter but relies
     * on a default domain set for the source file this function is used in.
     * \note Method name is starts with capital letter, as <em>assert</em> is a Java keyword.
     *
     * @param trueOrLog The log is only performed if condition is not true.
     * @param msg       The message to log out.
     * @param indent    the indentation in the output.
     **********************************************************************************************/
    public static void Assert(boolean trueOrLog, Object msg, int indent)
    {
        LOX.line( !trueOrLog, null, Log.Level.ERROR, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log a string only if the given condition is not true. Log level will be highest, namely Error
     * if condition is false. This overloaded version does not offer a domain parameter but relies
     * on a default domain set for the source file this function is used in.
     * \note Method name is starts with capital letter, as <em>assert</em> is a Java keyword.
     * @param trueOrLog The log is only performed if condition is not true.
     * @param msg       The message to log out.
     **********************************************************************************************/
    public static void Assert(boolean trueOrLog, Object msg)
    {
        LOX.line( !trueOrLog, null, Log.Level.ERROR, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log a string only if the given condition is not true. Log level will be highest, namely
     * Log.Level.Error.
     * \note Method name is starts with capital letter, as <em>assert</em> is a Java keyword.
     *
     * @param trueOrLog The log is only performed if condition is not true.
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  source file. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param msg       The message to log out.
     * @param indent    the indentation in the output.
     **********************************************************************************************/
    public static void Assert(boolean trueOrLog, String domain, Object msg, int indent)
    {
        LOX.line( !trueOrLog, domain, Log.Level.ERROR, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Log a string only if the given condition is not true. Log level will be highest, namely
     * Log.Level.Error.
     * \note Method name is starts with capital letter, as <em>assert</em> is a Java keyword.
     *
     * @param trueOrLog The log is only performed if condition is not true.
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  source file. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param msg       The message to log out.
     **********************************************************************************************/
    public static void Assert(boolean trueOrLog, String domain, Object msg)
    {
        LOX.line( !trueOrLog, domain, Log.Level.ERROR, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
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
     *                      of the source file. For other values, the default domain is ignored
     *                      (regardless if this is starting with a slash or not).
     * @param level         The log level.
     * @param msg           The message to log out.
     * @param indent        The indentation in the output.
     * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
     *                      loggers to have different domains. A simple string compare without case
     *                      sensitivity is performed. An asterisk ('*') at the beginning or end of
     *                      the string is used as a wildcard. Leave to \e null if all loggers should be
     *                      affected. Use this parameter only in more complex logging scenarios.
     **********************************************************************************************/
    public static void line(boolean doLog, String domain, Log.Level level, Object msg, int indent, String loggerFilter)
    {
        LOX.line( doLog, domain, level, msg, indent, loggerFilter );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Conditionally logs an Object using the given log level, log domain and indentation.
     *
     * @param doLog     Conditional logging. If false, the log is not performed. CntLogCalls is still
     *                  increased by one.
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  source file. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param level     The log level.
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public static void line(boolean doLog, String domain, Log.Level level, Object msg, int indent)
    {
        LOX.line( doLog, domain, level, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Conditionally logs an Object using the given log level and log domain.
     *
     * @param doLog     Conditional logging. If false, the log is not performed. CntLogCalls is still
     *                  increased by one.
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  source file. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param level     The log level.
     * @param msg       The message to log out.
     **********************************************************************************************/
    public static void line(boolean doLog, String domain, Log.Level level, Object msg)
    {
        LOX.line( doLog, domain, level, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Logs an Object using the given log level and log domain.
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  source file. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param level     The log level.
     * @param msg       The message to log out.
     **********************************************************************************************/
    public static void line(String domain, Log.Level level, Object msg)
    {
        LOX.line( true, domain, level, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Logs an Object using the given log level and the default domain for this scope.
     *
     * @param level     The log level.
     * @param msg       The message to log out.
     **********************************************************************************************/
    public static void line(Log.Level level, Object msg)
    {
        LOX.line( true, null, level, msg, 0, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Logs an Object using the given log level and indentation using the default domain for this scope.
     *
     * @param level     The log level.
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **********************************************************************************************/
    public static void line(Log.Level level, Object msg, int indent)
    {
        LOX.line( true, null, level, msg, indent, null );
        if (msg == logBuf) logBufLock.release();
    }

    /** *********************************************************************************************
     * Logs an Object using the given log level, indentation and logger filter using the default domain
     * for this scope.
     *
     * @param level         The log level.
     * @param msg           The message to log out.
     * @param indent        The indentation in the output.
     * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
     *                      loggers to have different domains. A simple string compare without case
     *                      sensitivity is performed. An asterisk ('*') at the beginning or end of
     *                      the string is used as a wildcard. Leave to \e null if all loggers should be
     *                      affected. Use this parameter only in more complex logging scenarios.
     **********************************************************************************************/
    public static void line(Log.Level level, Object msg, int indent, String loggerFilter)
    {
        LOX.line( true, null, level, msg, indent, loggerFilter );
        if (msg == logBuf) logBufLock.release();
    }
}
