// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

import java.util.Date;

import com.aworx.lib.ALIB;
import com.aworx.lib.ConsoleReportWriter;
import com.aworx.lib.Report;
import com.aworx.lib.enums.ContainerOp;
import com.aworx.lib.enums.Inclusion;
import com.aworx.lib.threads.ThreadLock;
import com.aworx.lox.core.Logger;
import com.aworx.lox.core.textlogger.TextLogger;

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
 *  This class is flagged 'abstract' to prevent instance creation.
 **************************************************************************************************/
public abstract class Log
{
    // #############################################################################################
    // Interface methods NOT copied from Lox (auto removed)
    // #############################################################################################

        /** ************************************************************************************
         * This method creates an adequate/default debug logger using
         * \ref com::aworx::lox::Lox::createConsoleLogger "Lox.createConsoleLogger"
         * and attaches it to the debug instance of class
         * \ref com::aworx::lox::Lox "Lox".
         * Of-course, alternatively to using this method, a suitable set of
         * debug loggers can be created manually. Also, before/after using this method
         * additional debug loggers may be created.
         *
         * The name of the \e Logger created is \c "DEBUG_LOGGER". It will be registered with
         * the standard \b %Lox used for debug-logging, by setting \e Verbosities
         * - Verbosity.VERBOSE for the root domain <c> '/'</c> and
         * - Verbosity.WARNING for internal domains.
         *
         * Finally, this method invokes #addALibReportWriter.
         *
         * @param lox The lox to add the debug logger(s) to. If null, the static debug object
         *            #LOX is used.
         *            Defaults to null
         **************************************************************************************/
        public static void addDebugLogger( Lox lox )
        {
            if ( lox == null )
                lox= LOX;

            ALIB.ASSERT_ERROR( debugLogger == null, "Illegal double invocation." );

            // add a default console logger
            debugLogger= Lox.createConsoleLogger( "DEBUG_LOGGER" );

            lox.setVerbosity( debugLogger, Verbosity.VERBOSE,                  "/" );
            lox.setVerbosity( debugLogger, Verbosity.WARNING, ALox.INTERNAL_DOMAINS );

            // replace the ReportWriter
            Log.addALibReportWriter( lox );
        }

        /** ************************************************************************************
         * This method invokes #addDebugLogger(Lox) providing the static debug instance #LOX.
         * for parameter \p lox.
         **************************************************************************************/
        public static void addDebugLogger()
        {
            addDebugLogger( LOX );
        }

        /** ************************************************************************************
         * Removes the \e Logger(s) which was/were created by \ref addDebugLogger.
         *  This method also invokes
         *  \ref com::aworx::lib::Report::popWriter "Report.popWriter(null)"
         *  to install a default \ref com::aworx::lib::ReportWriter "ReportWriter" for ALib.
         *
         * @param lox The lox to remove the debug logger from.
         *           If null, the static debug object#LOX is used.
         **************************************************************************************/
        public static void removeDebugLogger( Lox lox )
        {
            // replace the report writer (if we replaced it before)
            Log.removeALibReportWriter();

            // remove debug logger(s)
            ALIB.ASSERT_ERROR( debugLogger != null, "No debug logger to remove." );

            if ( debugLogger != null )
            {
                if ( lox == null )
                    lox= LOX;
                lox.removeLogger( debugLogger );
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


        /** ************************************************************************************
         * In the case that the original ALib ConsoleReportWriter is still in place,
         * \ref com::aworx::lib::Report::pushWriter "Report.pushWriter" is invoked to provide a
         * ReportWriter of type
         * \ref com::aworx::lox::ALoxReportWriter "ALoxReportWriter".
         *
         * \note
         * This method is effective only in debug compilations. Usually it is invoked indirectly by
         * using method #addDebugLogger. Applications that do not use that method (e.g. because
         * they are using release logging exclusively), should invoke this method on bootstrap
         * providing their (release) lox.
         * In this case, the \e Verbosity of the internal domain used by class
         * \ref aworx::lox::ALoxReportWriter "ALoxReportWriter" has to be set for the
         * the logger(s) in given \p lox in question.
         *
         * @param lox  The lox that the
         *             \ref aworx::lox::ALoxReportWriter "ALoxReportWriter" created will be using.
         **************************************************************************************/
        public static void addALibReportWriter( Lox lox )
        {
            ALIB.ASSERT_WARNING( debugReportWriter == null, 
                                 "Log.addReportWriter(): ALoxReportWriter already created." );

            // replace the ReportWriter
            if ( Report.getDefault().peekWriter() == ConsoleReportWriter.SINGLETON  )
                Report.getDefault().pushWriter( debugReportWriter= new ALoxReportWriter( lox ) );
        }

        /** ************************************************************************************
         * Removes the report writer created with #addALibReportWriter.
         **************************************************************************************/
        public static void removeALibReportWriter()
        {
            ALIB.ASSERT_WARNING( debugReportWriter != null, 
                                 "Log.removeReportWriter(): No ALoxReportWriter to remove." );
            // replace the report writer (if we replaced it before)
            if( debugReportWriter != null )
            {
                Report.getDefault().popWriter( debugReportWriter );
                debugReportWriter= null;
            }
        }


        /// This is a static singleton of type class Lox which is used for standard
        /// debug logging statements.
        public static Lox               LOX                                   =new Lox("Log", true);

        /// The debug logger created by AddDebugLogger.
        public static TextLogger        debugLogger                                           =null;

        /**
         * The ALib ReportWriter. This will be created and registered in method
         * \ref com::aworx::lox::Log::addDebugLogger    "Log.addDebugLogger" and removed in
         * \ref com::aworx::lox::Log::removeDebugLogger "Log.removeDebugLogger" in the case that
         * the original ALib ConsoleReportWriter is in place.
         */
        public static ALoxReportWriter  debugReportWriter                                     =null;


    // #############################################################################################
    // Debug-Log Buffer mimicking AString
    // #############################################################################################

        /** A log buffer singleton. Can be acquired, using buf() */
        protected static LogBuf         logBuf                                        =new LogBuf();

        /** A locker for the log buffer singleton */
        protected static ThreadLock     logBufLock                                =new ThreadLock();

        /** ****************************************************************************************
         * Static code
         ******************************************************************************************/
        static
        {
            // set recursion warning of log buffer lock to 1.
            // Warnings are logged if recursively acquired more than once
            logBufLock.recursionWarningThreshold= 1;
        }

        /** ****************************************************************************************
         * Returns a LogBuf singleton, similar to the AString singleton returned by Lox.buf(). Class
         * LogBuf is a pruneable mimic of AString. Hence working with LogBuf instead of AString is
         * allowed only for debug logging purposes, not for release logging.<br>
         * Whenever this method is called, the returned LogBuf object has to be used as a message
         * within one of the log methods of this class (error(), warning(), info(), verbose(),
         * assert(), if() or entry()). If this is not done, the object does not get released and
         * parallel threads using it would be blocked! So, do not use buf() for other reasons
         * than for creating log messages and be sure to re-acquire the LogBuf object by calling
         * this method again prior to the next log call.
         *
         * @return the static LogBuf singleton.
         ******************************************************************************************/
        public static LogBuf buf()
        {
            logBufLock.acquire();
            logBuf.clear();
            return logBuf;
        }

        /** ****************************************************************************************
         * Use this method when you want to abort a log call that you "started" with acquiring the
         * internal LogBuf singleton acquired using method buf(). Use bufAbort() only if you did
         * not use the acquired buffer as a parameter of a log method, because this internally
         * releases the buf already.
         ******************************************************************************************/
        public static void bufAbort()
        {
            logBufLock.release();
        }


    // #############################################################################################
    // Interface methods copied from Lox (to be pruned)
    // #############################################################################################

    /** ********************************************************************************************
     * Retrieves an instance of a Logger by its name. This might be useful when access to a
     * \e %Logger is needed to change its configuration.
     *
     * @param loggerName    The name of the \e Logger to search for (case insensitive).
     * @return The logger, null if not found.
     **********************************************************************************************/
    public static Logger getLogger(String loggerName)
    {
        return LOX.getLogger( loggerName );
    }

    /** ********************************************************************************************
     * This method should not be used in standard applications. It was added to support clean unit
     * testing. This method disposes the internal static Lox and with it all loggers, preferences
     * and stuff and replaces it with a fresh one.
     **********************************************************************************************/
    public static void reset()
    {
        if ( Log.debugLogger != null )
            Log.removeDebugLogger();
        ALox.register( Log.LOX, ContainerOp.REMOVE );
        Log.LOX=                new Lox("Log", true );
        Log.debugLogger=        null;
        Log.logBuf=             new LogBuf();
        Log.logBufLock=         new ThreadLock();
        Log.logBufLock.recursionWarningThreshold= 1;
        ALox.configCategoryName= "ALOX";
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
    public static boolean removeLogger( Logger logger )
    {
        return LOX.removeLogger( logger );
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
    public static Logger removeLogger( String loggerName )
    {
        return LOX.removeLogger( loggerName );
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
     * Optional parameter \p priority defaults to
     * \ref com::aworx::lox::Lox::PRIO_SOURCE "Lox.PRIO_SOURCE", which is a lower priority
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
     * @param priority   The priority of the setting. Defaults to
     *                   \ref com::aworx::lox::Lox::PRIO_SOURCE "Lox.PRIO_SOURCE",
     *                   which is a lower priority than standard plug-ins of external
     *                   configuration have.
     **********************************************************************************************/
    public static  void setVerbosity( Logger logger, Verbosity verbosity, String domain, int priority )
    {
        LOX.setVerbosity( logger, verbosity, domain, priority );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(Logger,Verbosity,String,int) "setVerbosity" providing
     * default value \c PRIO_SOURCE for parameter \p priority.
     *
     * @param logger     The logger to be to be affected.
     * @param verbosity  The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     **********************************************************************************************/
    public static  void setVerbosity( Logger logger, Verbosity verbosity, String domain)
    {
        LOX.setVerbosity( logger, verbosity, domain, Lox.PRIO_SOURCE );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(Logger,Verbosity,String,int) "setVerbosity" providing
     * - default value \c PRIO_SOURCE for parameter \p priority and
     * - default value <c> '/'</c> for parameter \p domain.
     *
     * @param logger     The logger to be to be affected.
     * @param verbosity  The 'level of verboseness' to be set.
     **********************************************************************************************/
    public static  void setVerbosity( Logger logger, Verbosity verbosity)
    {
        LOX.setVerbosity( logger, verbosity, "/", Lox.PRIO_SOURCE );
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
     * @param priority   The priority of the setting. Defaults to
     *                   \ref com::aworx::lox::Lox::PRIO_SOURCE "Lox.PRIO_SOURCE",
     *                   which is a lower priority than standard plug-ins of external
     *                   configuration have.
     **********************************************************************************************/
    public static  void setVerbosity( String loggerName, Verbosity verbosity, String domain, int priority )
    {
        LOX.setVerbosity( loggerName, verbosity, domain );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(String,Verbosity,String) "setVerbosity" providing
     * default value \c PRIO_SOURCE for parameter \p priority.
     *
     * @param loggerName  The logger to be to be affected, identified by its name (case
     *                    insensitive).
     * @param verbosity   The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     **********************************************************************************************/
    public static  void setVerbosity( String loggerName, Verbosity verbosity, String domain)
    {
        LOX.setVerbosity( loggerName, verbosity, domain, Lox.PRIO_SOURCE );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(String,Verbosity,String) "setVerbosity" providing
     * - default value \c PRIO_SOURCE for parameter \p priority and
     * - default value <c> '/'</c> for parameter \p domain.
     *
     * @param loggerName  The logger to be to be affected, identified by its name (case
     *                    insensitive).
     * @param verbosity   The 'level of verboseness' to be set.
     **********************************************************************************************/
    public static  void setVerbosity( String loggerName, Verbosity verbosity)
    {
        LOX.setVerbosity( loggerName, verbosity, "/", Lox.PRIO_SOURCE );
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
     * @param packageLevel Used only with
     *                     \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE".
     *                     Cuts the given number of package parts (separated with '.') from the end
     *                     of the packages. Optional and defaults to \c 0.
     **********************************************************************************************/
    public static void setDomain( String scopeDomain, Scope scope, int packageLevel )
    {
        LOX.setDomainImpl( scopeDomain, scope, packageLevel, false, null );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setDomain( String, Scope, int) "setDomain"
     * providing default value \c 0 for parameter \p packageLevel.
     *
     * @param scopeDomain    The domain path to register.
     * @param scope        The scope that should the given \p domain be registered for.
     *                     Available Scope definitions are platform/language dependent.
     **********************************************************************************************/
    public static void setDomain( String scopeDomain, Scope scope)
    {
        LOX.setDomainImpl( scopeDomain, scope, 0, false, null );
    }

    /** ****************************************************************************************
     * This overloaded version of
     * \ref setDomain( String, Scope, int) "setDomain"
     * is applicable only for \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER and allows to
     * specify the thread that the setting should be associated with.
     *
     * If \p scopeDomain is null or empty, the most recently added domain path is removed.
     * For removing an explicitly named domain associated with  a thread use method
     * #removeThreadDomain.
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.THREAD_OUTER or \e %Scope.THREAD_INNER. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related Scope Domains for.
     ******************************************************************************************/
    public static void setDomain( String scopeDomain, Scope scope, Thread thread )
    {
        LOX.setDomainImpl( scopeDomain, scope, 0, false, thread );
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
    public static void removeThreadDomain( String scopeDomain, Scope scope, Thread thread )
    {
        LOX.removeThreadDomain( scopeDomain, scope, thread );
    }

    /** ****************************************************************************************
     * Overload version providing default value for parameter \p thread.
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER. With other values,
     *                    an internal error is logged.
     ******************************************************************************************/
    public static void removeThreadDomain( String scopeDomain, Scope scope )
    {
        LOX.removeThreadDomain( scopeDomain, scope, null );
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
    public static void setDomainSubstitutionRule( String domainPath, String replacement )
    {
        LOX.setDomainSubstitutionRule( domainPath, replacement );
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
    public static  void setPrefix( Object logable, Scope scope, int packageLevel  )
    {
        LOX.setPrefixImpl( logable, scope, packageLevel, null );
    }

    /** ****************************************************************************************
     * Overloaded version of \ref setPrefix(Object,Scope,int) "setPrefix" providing value \c 0
     * as default for parameter \p packageLevel.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     * @param scope       The scope that should the given \p logable be registered for.
     *                    Available Scope definitions are platform/language dependent.
     ******************************************************************************************/
    public static  void setPrefix( Object logable, Scope scope  )
    {
        LOX.setPrefixImpl( logable, scope, 0, null );
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
    public static  void setPrefix( Object logable, Scope scope, Thread thread )
    {
        LOX.setPrefixImpl( logable, scope, 0, thread );
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
     *   \e %Scope.THREAD_INNER will be applied).
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
    public static void        setPrefix( Object logable, String domain, Inclusion otherPLs )
    {
        LOX.setPrefix( logable, domain, otherPLs );
    }

    /** ****************************************************************************************
     * Overloaded version of #setPrefix providing
     * default value \c Inclusion.INCLUDE for parameter \p otherPLs.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     * @param domain      The domain path. Defaults to \c null, resulting in
     *                    evaluated <em>Scope Domain</em> path.
     ******************************************************************************************/
    public static void        setPrefix( Object logable, String domain )
    {
        LOX.setPrefix( logable, domain, Inclusion.INCLUDE );
    }

    /** ****************************************************************************************
     * Overloaded version of #setPrefix providing
     * default value \c Inclusion.INCLUDE for parameter \p otherPLs and
     * default value \c null for parameter \p domain.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     ******************************************************************************************/
    public static void        setPrefix( Object logable )
    {
        LOX.setPrefix( logable, null, Inclusion.INCLUDE );
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
    public static  void setStartTime( Date startTime, String loggerName)
    {
        LOX.setStartTime( startTime, loggerName );
    }

    /** ********************************************************************************************
     * Overloaded version of #setStartTime( Date, String ) providing default value \c null
     * for parameter \p loggerName.
     *
     * @param startTime     Optional parameter with the  new start time. Defaults to DateTime.Now if
     *                      omitted.
     **********************************************************************************************/
    public static  void setStartTime( Date startTime )
    {
        LOX.setStartTime( startTime, null );
    }

    /** ********************************************************************************************
     * Overloaded version of #setStartTime( Date, String ) providing default values
     * \c null for parameters \p startTime and \p loggerName.
     **********************************************************************************************/
    public static  void setStartTime()
    {
        LOX.setStartTime( null, null );
    }

    /** ********************************************************************************************
     * This method sets a human readable name to the given thread ID (or current thread) which is
     * optionally included in each log entry.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     * @param id            Parameter providing the thread ID.
     *                      Defaults to \c -1 which uses the current thread.
     **********************************************************************************************/
    public static  void mapThreadName( String threadName, long id )
    {
        LOX.mapThreadName( threadName, id );
    }

    /** ********************************************************************************************
     * This method sets a human readable name to the current thread which is optionally included in
     * each log entry.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     **********************************************************************************************/
    public static  void mapThreadName( String threadName )
    {
        LOX.mapThreadName( threadName, -1 );
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
     *                  If omitted (or empty or null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     ******************************************************************************************/
    public static void store( LogData data, String key, Scope scope, int pkgLevel )
    {
        LOX.store( data, key, scope, pkgLevel );
    }

    /** ****************************************************************************************
     * Overloaded version of #store providing default parameters.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param key       The optional key to the data.
     *                  If omitted (or empty or null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     ******************************************************************************************/
    public static void store( LogData data, String key, Scope scope )
    {
        LOX.store( data, key, scope, 0 );
    }

    /** ****************************************************************************************
     * Overloaded version of #store providing default parameters.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param key       The optional key to the data.
     *                  If omitted (or empty or null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     ******************************************************************************************/
    public static void store( LogData data, String key )
    {
        LOX.store( data, key, Scope.GLOBAL, 0 );
    }

    /** ****************************************************************************************
     * Overloaded version of #store providing default parameters.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     ******************************************************************************************/
    public static void store( LogData data )
    {
        LOX.store( data, null, Scope.GLOBAL, 0 );
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
    public static void store( LogData  data, Scope scope, int  pkgLevel )
    {
        LOX.store( data, null, scope, pkgLevel );
    }

    /** ****************************************************************************************
     * Overloaded version of #store providing default parameters.
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param scope     The \e %Scope that the data is bound to.
     ******************************************************************************************/
    public static void store( LogData  data, Scope scope )
    {
        LOX.store( data, null, scope, 0 );
    }

    /** ****************************************************************************************
     * Retrieves ALox <em>Log Data</em>, an object of base type
     * \ref com::aworx::lox::LogData "LogData" which can be stored by invoking
     * #store. Using the optional \p key and \p scope offer various possibilities to reference
     * such objects.<br>
     *
     * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
     *       It is not advised to use <em>Log Data</em> to implement application logic.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pkgLevel  Used only if parameter \p scope equals
     *                  \ref com::aworx::lox::Scope::PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public static LogData  retrieve( String key, Scope scope,  int pkgLevel )
    {
        return LOX.retrieve( key, scope, pkgLevel );
    }

    /** ****************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public static LogData  retrieve( String key, Scope scope )
    {
        return LOX.retrieve( key, scope, 0 );
    }

    /** ****************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public static LogData  retrieve( String key )
    {
        return LOX.retrieve( key, Scope.GLOBAL, 0 );
    }

    /** ****************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public static LogData  retrieve()
    {
        return LOX.retrieve( null, Scope.GLOBAL, 0 );
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
    public static LogData  retrieve( Scope scope, int pkgLevel )
    {
        return LOX.retrieve( null, scope, pkgLevel);
    }

    /** ****************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param scope     The \e %Scope that the data is bound to.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public static LogData  retrieve( Scope scope )
    {
        return LOX.retrieve( null, scope, 0 );
    }


    /** ********************************************************************************************
     * This method logs the configuration the Lox encapsulated in this static Log interface.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param headLine  If given, a separated headline will be logged at first place.
     **********************************************************************************************/
    public static void logConfig(String domain, Verbosity verbosity, String headLine)
    {
        LOX.logConfig( domain, verbosity, headLine );
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
     * @param logable   The message to log out.
     **********************************************************************************************/
    public static void entry(String domain, Verbosity verbosity, Object logable)
    {
        LOX.entry( domain, verbosity, logable );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Overloaded version of #entry, defaulting parameter \p domain to a nulled string.
     *
     * @param verbosity The verbosity.
     * @param logable   The message to log out.
     **********************************************************************************************/
    public static void entry(Verbosity verbosity, Object logable)
    {
        LOX.entry( null, verbosity, logable );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::VERBOSE "Verbosity.VERBOSE".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * Scope Domain set for the scope.
     *
     * @param logable   The message to log out.
     **********************************************************************************************/
    public static void verbose(Object logable)
    {
        LOX.entry( null, Verbosity.VERBOSE, logable );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::VERBOSE "Verbosity.VERBOSE".
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The message to log out.
     **********************************************************************************************/
    public static void verbose(String domain, Object logable)
    {
        LOX.entry( domain, Verbosity.VERBOSE, logable );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::INFO "Verbosity.INFO".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * Scope Domain set for the scope.
     *
     * @param logable   The message to log out.
     **********************************************************************************************/
    public static void info(Object logable)
    {
        LOX.entry( null, Verbosity.INFO, logable );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::INFO "Verbosity.INFO".
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The message to log.
     **********************************************************************************************/
    public static void info(String domain, Object logable)
    {
        LOX.entry( domain, Verbosity.INFO, logable );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::WARNING "Verbosity.WARNING".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * Scope Domain set for the scope.
     *
     * @param logable   The message to log out.
     **********************************************************************************************/
    public static void warning(Object logable)
    {
        LOX.entry( null, Verbosity.WARNING, logable );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity::WARNING "Verbosity.WARNING".
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The message to log.
     **********************************************************************************************/
    public static void warning(String domain, Object logable)
    {
        LOX.entry( domain, Verbosity.WARNING, logable );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity.ERROR "Verbosity.ERROR".
     *
     * This overloaded version does not offer a domain parameter but relies on a
     * Scope Domain set for the scope.
     *
     * @param logable   The message to log out.
     **********************************************************************************************/
    public static void error(Object logable)
    {
        LOX.entry( null, Verbosity.ERROR, logable );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Logs a \e Logable with
     * \ref Verbosity.ERROR "Verbosity.ERROR".
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The message to log out.
     **********************************************************************************************/
    public static void error(String domain, Object logable)
    {
        LOX.entry( domain, Verbosity.ERROR, logable );
        if (logable == logBuf) logBufLock.release();
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
     **********************************************************************************************/
    public static void once(String domain, Verbosity verbosity, Object logable, String group, Scope scope, int pkgLevel, int quantity)
    {
        LOX.once( domain, verbosity, logable, group, scope, pkgLevel, quantity );
        if (logable == logBuf) logBufLock.release();
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
    public static void once(String domain, Verbosity verbosity, Object logable, String group, Scope scope, int pkgLevel)
    {
        LOX.once( domain, verbosity, logable, group, scope, pkgLevel, 1 );
        if (logable == logBuf) logBufLock.release();
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
    public static void once(String domain, Verbosity verbosity, Object logable, String group, Scope scope )
    {
        LOX.once( domain, verbosity, logable, group, scope, 0, 1 );
        if (logable == logBuf) logBufLock.release();
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
    public static void once(String domain, Verbosity verbosity, Object logable, String group )
    {
        LOX.once( domain, verbosity, logable, group, Scope.GLOBAL, 0, 1 );
        if (logable == logBuf) logBufLock.release();
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
    public static void once(String domain, Verbosity verbosity, Object logable, String group, int quantity )
    {
        LOX.once( domain, verbosity, logable, group, Scope.GLOBAL, 0, quantity );
        if (logable == logBuf) logBufLock.release();
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
    public static void once(String domain, Verbosity verbosity, Object logable, Scope scope, int pkgLevel, int quantity)
    {
        LOX.once( domain, verbosity, logable, null, scope, pkgLevel, quantity );
        if (logable == logBuf) logBufLock.release();
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
    public static void once(String domain, Verbosity verbosity, Object logable, Scope scope, int pkgLevel)
    {
        LOX.once( domain, verbosity, logable, null, scope, pkgLevel, 1 );
        if (logable == logBuf) logBufLock.release();
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
    public static void once(String domain, Verbosity verbosity, Object logable, Scope scope)
    {
        LOX.once( domain, verbosity, logable, null, scope, 0, 1 );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     **********************************************************************************************/
    public static void once(String domain, Verbosity verbosity, Object logable  )
    {
        LOX.once( domain, verbosity, logable, null, Scope.GLOBAL, 0, 1 );
        if (logable == logBuf) logBufLock.release();
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
    public static void once(String domain, Verbosity verbosity, Object logable, int quantity  )
    {
        LOX.once( domain, verbosity, logable, null, Scope.GLOBAL, 0, quantity );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logable   The string message to log.
    **********************************************************************************************/
    public static void once( Object logable )
    {
        LOX.once( null, Verbosity.INFO, logable, null, Scope.GLOBAL, 0, 1);
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
    **********************************************************************************************/
    public static void once( Object logable, int quantity  )
    {
        LOX.once( null, Verbosity.INFO, logable, null, Scope.GLOBAL, 0, quantity );
        if (logable == logBuf) logBufLock.release();
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
    public static void once( Object logable, int quantity, String group  )
    {
        LOX.once( null, Verbosity.INFO, logable, group, Scope.GLOBAL, 0, quantity );
        if (logable == logBuf) logBufLock.release();
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
    public static void once( Object logable, int quantity, Scope scope, int pkgLevel )
    {
        LOX.once( null, Verbosity.INFO, logable, null, scope, pkgLevel, quantity );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     * @param scope     The \e %Scope that the group or counter is bound to.
    **********************************************************************************************/
    public static void once( Object logable, int quantity, Scope scope  )
    {
        LOX.once( null, Verbosity.INFO, logable, null, scope, 0, quantity );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is not \c true.
     * If executed, \ref Verbosity.ERROR is used.
     *
     * \note This Method's name starts with capital letter, as \e 'assert' is a Java keyword.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     **********************************************************************************************/
    public static void Assert(boolean condition, String domain, Object logable)
    {
        LOX.Assert( condition, domain, logable );
        if (logable == logBuf) logBufLock.release();
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is not \c true.
     * If executed, \ref Verbosity.ERROR is used.
     *
     * This overloaded version omits parameter \p domain.
     *
     * \note This Method's name starts with capital letter, as \e 'assert' is a Java keyword.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param logable   The object to log.
     **********************************************************************************************/
    public static void Assert(boolean condition, Object logable)
    {
        LOX.Assert( condition, null, logable );
        if (logable == logBuf) logBufLock.release();
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
    public static void If(boolean condition, String domain, Verbosity verbosity, Object logable)
    {
        LOX.If( condition, domain, verbosity, logable );
        if (logable == logBuf) logBufLock.release();
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
    public static void If(boolean condition, Verbosity verbosity, Object logable)
    {
        LOX.If( condition, null, verbosity, logable );
        if (logable == logBuf) logBufLock.release();
    }
}
