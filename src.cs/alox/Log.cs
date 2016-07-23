// #################################################################################################
//  cs.aworx.lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System.Diagnostics;
using System.Runtime.CompilerServices;
using System;
using cs.aworx.lib;
using cs.aworx.lox.core;
using cs.aworx.lox.loggers;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;
using System.Threading;
using cs.aworx.lib.config;

namespace cs.aworx.lox {

/** ************************************************************************************************
 * This is a simple, 100% static wrapper of class Lox. In other words, this class incorporates
 * one static singleton of Lox and mirrors the whole non static interface of Lox into a static
 * one.
 *
 * The exclusive use of this class covers the vast majority of all debug logging scenarios.
 * For release logging, remote logging and similar scenarios, the use of a dedicated instance of
 * class Lox is needed. All invocations of methods of Log are pruned in release code.
 * (Using method annotation <em>"[Conditional("ALOX_DBG_LOG")]"</em> ).
 **************************************************************************************************/
public static class Log
{
    // #############################################################################################
    // Debug Logging
    // #############################################################################################
        /** The debug logger created by AddDebugLogger. */
        public static   TextLogger       DebugLogger                                          =null;

    #if ALOX_DBG_LOG

        /**
         *  This is a static singleton of type class Lox which is used for standard
         *  debug logging statements.
         */
        public static   Lox              LOX                                  =new Lox("Log", true );

        /**  An (additional) IDE specific logger, that might be created by AddDebugLogger. */
        public static   TextLogger       IDELogger                                            =null;
        /**
         * The ALib ReportWriter. This will be created and registered in method
         * \ref cs::aworx::lox::Log::AddDebugLogger    "Log.AddDebugLogger" and removed in
         * \ref cs::aworx::lox::Log::RemoveDebugLogger "Log.RemoveDebugLogger" in the case that
         * the original ALib ConsoleReportWriter is in place.
         */
        public static   ALoxReportWriter DebugReportWriter                                    =null;
    #endif


    // #########################################################################################
    // Interface (not auto removed)
    // #########################################################################################

        /** ****************************************************************************************
         * Retrieve an instance of a Logger by its name. This might be useful when access to a
         * \e %Logger is needed to change its configuration.
         * \note This function is not automatically removed from the release code because of
         *       technical restrictions. It has to be conditionally compiled by enclosing calls
         *       to it with "#if ... #endif" statements.
         *
         * @param loggerName    The name of the \e Logger to search for (case insensitive).
         *
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         * @return  The logger, null if not found.
         ******************************************************************************************/
        public static Logger GetLogger( String loggerName,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            #if ALOX_DBG_LOG
                return LOX.GetLogger( loggerName,  cln,csf,cmn );
            #else
                return null;
            #endif
        }


    // #############################################################################################
    // Interface methods NOT copied from Lox (not auto removed)
    // #############################################################################################

        /** ****************************************************************************************
         * Returns an AString singleton (contained in the Lox singleton), that can be reused for
         * all basic log calls. Textual messages that are assembled from out of strings, numbers
         * and other data, can be efficiently built by reusing this singleton.
         * Whenever this method is called, the returned AString object gets "locked" by a
         * corresponding ThreadLock object. Therefore it has to be used as a message within one of
         * the log methods of this class
         * (error(), warning(), info(), verbose(), if(), once() or entry())
         * or it has to be explicitly released using BufAbort().
         * If this is not done, the object does not get released and parallel threads using this
         * method would block! So, do not use Buf() for other reasons than for creating log messages
         * and be sure to release it "in time".
         *
         * @return The static LogBuf singleton.
         ******************************************************************************************/
        public static AString Buf()
        {
            #if ALOX_DBG_LOG
                return LOX.Buf();
            #else
                return null;
            #endif
        }

        /** ****************************************************************************************
         * Use this method when you want to abort a log call that you "started" with acquiring the
         * internal AString singleton acquired using method Buf(). Use BufAbort() only if you did
         * not use the acquired buffer as a parameter of a log method, because this internally
         * releases the buf already.
         ******************************************************************************************/
        public static void BufAbort()
        {
            #if ALOX_DBG_LOG
                LOX.BufAbort();
            #endif
        }

        /** ************************************************************************************
         * This method creates an adequate/default debug logger (or multiple).
         * Of-course, alternatively to using this method, a suitable set of
         * debug loggers can be created manually. Also, before/after using this method
         * additional debug loggers may be created.
         *
         * In the current version of ALox (future changes are likely), this method does:
         * - use
         *   \ref cs::aworx::lox::Lox::CreateConsoleLogger "Lox.CreateConsoleLogger"
         *   to create the best compatible console logger for the
         *   running platform
         * - If a CLR debug session is running (e.g. running in debug mode in Visual Studio or
         *   MonoDevelop IDE), adds a
         *   \ref cs.aworx.lox::loggers::CLRDebuggerLogger "CLRDebuggerLogger"
         *   in addition to the standard console logger. This can be suppressed using
         *   configuration variable [ALOX_NO_IDE_LOGGER](../group__GrpALoxConfigVars.html).
         *
         *
         * The name of the \e Logger created is \c "DEBUG_LOGGER". It will be registered with
         * the standard \b %Lox used for debug-logging, by setting \e Verbosities
         * - Verbosity.Verbose for the root domain <c> '/'</c> and
         * - Verbosity.Warning for internal domains.
         *
         * An optionally created second, IDE-specific \e Logger will be named \c "IDE_LOGGER"
         * and will be registered with the standard \b %Lox used for debug-logging with the same
         * \e Verbosities as \c "DEBUG_LOGGER" is.
         *
         * Finally, this method invokes #AddALibReportWriter.
         *
         * @param lox The lox to add the debug logger(s) to. If null, the static debug object
         *            #LOX is used. Defaults to null.
         *
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         **************************************************************************************/
        [Conditional("ALOX_DBG_LOG")]
        public static void AddDebugLogger( Lox lox= null,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            #if ALOX_DBG_LOG

                if ( lox == null )
                    lox= LOX;

                ALIB.ASSERT_ERROR( DebugLogger == null, "Illeagal repeated invocation." );

                // add a CLR logger if this a debug session
                if( System.Diagnostics.Debugger.IsAttached )
                {
                    Variable variable= new Variable(ALox.NO_IDE_LOGGER);
                    variable.Load();
                    if( !variable.IsTrue() )
                    {
                        IDELogger= new CLRDebuggerLogger( "IDE_LOGGER" );

                        // add logger
                        lox.SetVerbosity( IDELogger  , Verbosity.Verbose, "/"                 , Configuration.PrioDefault ,cln,csf,cmn );
                        lox.SetVerbosity( IDELogger  , Verbosity.Warning, ALox.InternalDomains, Configuration.PrioDefault ,cln,csf,cmn );
                    }
                }

                // add a default console logger
                DebugLogger= Lox.CreateConsoleLogger("DEBUG_LOGGER");

                lox.SetVerbosity( DebugLogger, Verbosity.Verbose, "/"                 , Configuration.PrioDefault ,cln,csf,cmn );
                lox.SetVerbosity( DebugLogger, Verbosity.Warning, ALox.InternalDomains, Configuration.PrioDefault ,cln,csf,cmn );

                // replace the ReportWriter
                Log.AddALibReportWriter( lox );

            #endif
        }

        /** ************************************************************************************
         * Removes the \e Logger(s) which was/were created by \ref AddDebugLogger.
         * This method also invokes
         * \ref cs::aworx::lib::Report::PopWriter "Report.PopWriter"
         * to install a default \ref cs::aworx::lib::ReportWriter "ReportWriter" for ALib.
         *
         * @param lox The lox to remove the debug logger(s) from.
         *            If null, the static debug object#LOX is used.
         *
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         **************************************************************************************/
        [Conditional("ALOX_DBG_LOG")]
        public static void RemoveDebugLogger( Lox lox= null,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            #if ALOX_DBG_LOG
                // replace the report writer (if we replaced it before)
                Log.RemoveALibReportWriter();

                // remove debug logger(s)
                ALIB.ASSERT_WARNING( DebugLogger != null, "No debug logger to remove." );

                if ( lox == null )
                    lox= LOX;

                if ( DebugLogger != null )
                {
                    lox.RemoveLogger( DebugLogger,  cln,csf,cmn );
                    DebugLogger= null;
                }

                if ( IDELogger != null )
                {
                    lox.RemoveLogger( IDELogger,  cln,csf,cmn );
                    IDELogger= null;
                }

            #endif
        }

        /** ************************************************************************************
         * In the case that the original ALib ConsoleReportWriter is still in place,
         * \ref cs::aworx::lib::Report::PushWriter "Report.PushWriter" is invoked to provide a
         * ReportWriter of type
         * \ref cs::aworx::lox::ALoxReportWriter "ALoxReportWriter".
         *
         * \note
         * This method is effective only in debug compilations. Usually it is invoked indirectly by
         * using method #AddDebugLogger. Applications that do not use that method (e.g. because
         * they are using release logging exclusively), should invoke this method on bootstrap
         * providing their (release) lox.
         * In this case, the \e Verbosity of the internal domain used by class
         * \ref cs::aworx::lox::ALoxReportWriter "ALoxReportWriter" has to be set for the
         * the logger(s) in given \p lox in question.
         *
         * @param lox  The lox that the
         *             \ref cs::aworx::lox::ALoxReportWriter "ALoxReportWriter" created will be using.
         *
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         **************************************************************************************/
        [Conditional("ALOX_DBG_LOG")]
        public static void AddALibReportWriter( Lox lox= null,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            #if ALOX_DBG_LOG

                ALIB.ASSERT_WARNING( DebugReportWriter == null,
                                     "Log.AddReportWriter(): ALoxReportWriter already created." );

                // replace the ReportWriter
                if ( Report.GetDefault().PeekWriter() == ConsoleReportWriter.Singleton  )
                   Report.GetDefault().PushWriter( DebugReportWriter= new ALoxReportWriter( lox ) );
            #endif
        }

        /** ************************************************************************************
         * Removes the report writer created with #AddALibReportWriter.
         *
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         **************************************************************************************/
        [Conditional("ALOX_DBG_LOG")]
        public static void RemoveALibReportWriter(
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            #if ALOX_DBG_LOG
                // replace the report writer (if we replaced it before)
                if( DebugReportWriter != null )
                {
                    Report.GetDefault().PopWriter( DebugReportWriter );
                    DebugReportWriter= null;
                }
            #endif
        }
        /** ************************************************************************************
         * This method is convenient to use in console applications at the end of the main()
         * method. It checks if this process has a console window and a Visual Studio debug
         * session is running.
         * Such applications will otherwise close the console window when the application
         * exits.
         * The method returns immediately, if the aforementioned condition is false as well
         * as in release compilations.
         **************************************************************************************/
        [Conditional("ALOX_DBG_LOG")]
        public static void WaitForKeyPress()
        {
            #if ALOX_DBG_LOG && ALIB_VSTUDIO
               if( ALIB.SysInfo_HasConsoleWindow && System.Diagnostics.Debugger.IsAttached )
               {
                    System.Diagnostics.Debug.WriteLine(   "\r\nALox: Waiting for any key in the console window." );
                    Console.WriteLine(  "ALox: Press any to exit... " );
                    Console.ReadKey();
              }
            #endif
        }

    // #############################################################################################
    // Interface methods copied from Lox (auto removed)
    // #############################################################################################

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
     * Parameter \p includeString determines if the searched substring should be included in the
     * resulting source path or not. In addition, parameter \p trimOffset, which can be negative
     * or positive, is added to the position of trimming. This can be used to increase the
     * length of the search path, and then cut only a portion of what was searched for.
     *
     * Parameter \p trimReplacement optionally provides a replacement string for the trimmed
     * path. This can be used for example to provide the right absolute path for an IDE
     * to find source files of a library.
     *
     * Finally, parameter \p sensitivity determines whether the match is performed case
     * sensitive or not. It defaults to non-sensitive, for convenience and for the fact that
     * for example Microsoft C++ compilers' preprocessor passes lower case path-strings!
     *
     * \note
     *   If the platform (compiler) specific path separator is <c>'/'</c>, then characters
     *   <c>'\'</c> found in parameters \p path and \p trimReplacement are replaced by <c>'\'</c>
     *   and vice versa. This allows to specify paths and substrings thereof in a platform
     *   independent way.
     *
     * \attention
     *   Setting global rules (when parameter \p global equals \c Inclusion::Include) is not
     *   protected by a \c mutex against concurrent access. Therefore, global rules have
     *   to be either at bootstrap of a process, before threads are created, or such creation
     *   has to 'manually' be protected by locking all existing instances of this class!
     *
     * @param path            The path to search for. If not starting with <c> '*'</c>,
     *                        a prefix is searched.
     * @param includeString   Determines if \p path should be included in the trimmed
     *                        path or not.
     *                        Optional and defaults to \b %Inclusion.Exclude.
     * @param trimOffset      Adjusts the portion of \p path that is trimmed.
     *                        Optional and defaults to 0.
     * @param sensitivity     Determines if the comparison of \p path with a source
     *                        files' path is performed case sensitive or not.
     *                        Optional and defaults to \b Case.Ignore.
     * @param reach           Denotes whether the rule is applied locally (to this \b %Lox only)
     *                        or applies to all instances of class \b %Lox.
     *                        Defaults to \b %Reach.Global.
     * @param trimReplacement Replacement string for trimmed portion of the path.
     *                        Optional and defaults to \b %NullString.
     * @param priority        The priority of the setting. Defaults to
     *                        \ref cs::aworx::lib::config::Configuration::PrioDefault "Configuration.PrioDefault".
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void      SetSourcePathTrimRule( String       path,
                                                   Inclusion    includeString   = Inclusion.Exclude,
                                                   int          trimOffset      = 0,
                                                   Case         sensitivity     = Case.Ignore,
                                                   Reach        reach           = Reach.Global,
                                                   String       trimReplacement = null ,
                                                   int          priority        = Configuration.PrioDefault    )
    {
        #if ALOX_DBG_LOG
            LOX.SetSourcePathTrimRule( path, includeString, trimOffset, sensitivity,
                                       trimReplacement, reach, priority );
        #endif
    }

    /** ****************************************************************************************
     * Removes all local trimming rules set with #SetSourcePathTrimRule.
     * If parameter \p global is set to \b Inclusion.Include, the global rules are cleared
     * in addition.
     *
     * Setting parameter \p allowAutoRule to \c false, allows to suppress the creation of an
     * automatic rule based on the executables path.
     *
     * \see ALox User Manual for more information.
     *
     * @param reach         Denotes whether only local rules are cleared or also global ones.
     *                      Defaults to \b %Reach.Global.
     * @param allowAutoRule Determines if an auto rule should be tried to be detected next
     *                      no appropriate rule is found.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static  void  ClearSourcePathTrimRules( Reach reach= Reach.Global, bool allowAutoRule= true )
    {
        #if ALOX_DBG_LOG
            LOX.ClearSourcePathTrimRules( reach, allowAutoRule );
        #endif
    }


    /** ********************************************************************************************
     * This method disposes the internal static Lox and with it all loggers, preferences and stuff
     * and replaces it with a fresh one. The method was added to support clean unit testing.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Reset()
    {
        #if ALOX_DBG_LOG
            if ( Log.DebugLogger != null )
                Log.RemoveDebugLogger();
            if ( Log.LOX != null )
                ALox.Register( Log.LOX, ContainerOp.Remove );
            Log.LOX= new Lox("Log", true );
            Log.ClearSourcePathTrimRules( Reach.Global, true );
            Log.DebugLogger= null;
            Log.IDELogger  = null;
            ALox.ConfigCategoryName._()._( "ALOX" );
        #endif
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
     * To deregister a \e Logger with a \b Lox, use method #RemoveLogger.
     * To 'disable' a \e Logger, invoke this method with parameters \p verbosity equaling to
     * \b %Verbosity.Off and \p domain to \c "/".
     *
     * Optional parameter \p priority defaults to
     * \ref cs::aworx::lib::config::Configuration::PrioDefault "Configuration.PrioDefault", which
     * is a lower priority than those of the standard plug-ins of external configuration data.
     * Therefore, external configuration by default 'overwrite' settings made from
     * 'within the source code', which simply means by invoking this method.<br>
     * The parameter can be provided for two main reasons:
     * - To 'lock' a verbosity setting against external manipulation.
     * - to 'break' the standard mechanism that an invocation of this method sets all
     *   sub-domains recursively. If a sub-domain was set with a higher priority
     *   (e.g. <c>%Configuration.PrioDefault + 1</c>, then this sub-domain will not be affected by
     *   future invocations of this method with standard-priority given.
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
     *   \e %Scope.ThreadInner, will still apply. This means that from within a thread that
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
     * @param logger     The logger to be to be affected.
     * @param domain     The domain to be set (including sub-domains).
     *                   Defaults to root domain \"/\".
     * @param verbosity  The 'level of verboseness' to be set.
     * @param priority   The priority of the setting. Defaults to
     *                   \ref cs::aworx::lib::config::Configuration::PrioDefault "Configuration.PrioDefault".
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static  void        SetVerbosity( Logger logger, Verbosity verbosity, String domain= "/",
                                             int priority = Configuration.PrioDefault,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetVerbosity( logger, verbosity, domain, priority, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Same as \ref #SetVerbosity(Logger,Verbosity,String,int,int,String,String) "SetVerbosity" but
     * addressing the \e %Logger to manipulate by its name.<br>
     * This method may only be used after a \e %Logger was once 'registered' with this \b %Lox
     * using \ref #SetVerbosity(Logger,Verbosity,String,int,int,String,String) "SetVerbosity".
     *
     * @param loggerName The logger to be to be affected, identified by its name (case
     *                   insensitive).
     * @param domain     The domain to be set (including sub-domains).
     *                   Defaults to root domain \"/\".
     * @param verbosity  The 'level of verboseness' to be set.
     * @param priority   The priority of the setting. Defaults to
     *                   \ref cs::aworx::lib::config::Configuration::PrioDefault "Configuration.PrioDefault".
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static   void SetVerbosity( String       loggerName,
                                       Verbosity    verbosity,
                                       String       domain        = "/",
                                       int          priority      = Configuration.PrioDefault,
    [CallerLineNumber] int cln=0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetVerbosity( loggerName, verbosity, domain, priority, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Removes a logger from this container.
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref SetVerbosity "SetVerbosity( logger, Verbosity.Off )"
     *       can be used.
     *
     * @param logger   The logger to be removed.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void RemoveLogger( Logger logger,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.RemoveLogger( logger,  cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Removes a logger from this container.
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref SetVerbosity "SetVerbosity( logger, Verbosity.Off )"
     *       can be used.
     *
     * @param      logger     The logger to be removed.
     * @param[out] wasFound   Output parameter that is set to \c true, if the \e Logger was found
     *                        and removed, to \c false otherwise.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void RemoveLogger( Logger logger, ref bool wasFound,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.RemoveLogger( logger, ref wasFound,  cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Removes logger named \p loggerName from this container.
     *
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref SetVerbosity "SetVerbosity( logger, Verbosity.Off )"
     *       can be used.
     *
     * @param      loggerName  The name of the \e Logger to be removed (case insensitive).
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static  void RemoveLogger( String loggerName,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.RemoveLogger( loggerName,  cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Removes logger named \p loggerName from this container.
     *
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref SetVerbosity "SetVerbosity( logger, Verbosity.Off )"
     *       can be used.
     *
     * @param      loggerName  The name of the \e Logger to be removed (case insensitive).
     * @param[out] logger      Output parameter that returns the \e Logger that was removed, to null
     *                         if not found.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void RemoveLogger( String loggerName, ref Logger logger,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.RemoveLogger( loggerName, ref logger,  cln,csf,cmn );
        #endif
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
     * To remove a previously set Scope Domain a nulled or empty string has to be passed with
     * parameter \p scopeDomain.
     *
     * For \e %Scope.ThreadOuter and \e %Scope.ThreadInner, passing an empty or nulled string
     * removes the most recently added domain path. For removing an explicitly named
     * domain path of \e %Scope.ThreadOuter and \e %Scope.ThreadInner use method
     * #RemoveThreadDomain.
     *
     *
     * @param scopeDomain    The domain path to register.
     * @param scope     The scope that should the given \p domain be registered for.
     *                  Available Scope definitions are platform/language dependent.
     * @param pathLevel Used only with
     *                  \ref aworx.lox::Scope::Path "Scope.Path".
     *                  Cuts the given number of directories from the end of the source path.
     *                  Optional and defaults to \c 0.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static   void SetDomain( String scopeDomain, Scope scope, int pathLevel = 0,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetDomain( scopeDomain, scope, pathLevel, cln,csf,cmn );
        #endif
    }

    /** ****************************************************************************************
     * This overloaded version of
     * \ref SetDomain(String,Scope,int,int,String, String) "SetDomain"
     * is applicable only for \e %Scope.ThreadOuter and \e %Scope.ThreadInner and allows to
     * specify the thread that the setting should be associated with.
     *
     * If \p scopeDomain is null or empty, the most recently added domain path is removed.
     * For removing an explicitly named domain associated with  a thread use method
     * #RemoveThreadDomain.
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.ThreadOuter or \e %Scope.ThreadInner. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related Scope Domains for.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static   void SetDomain( String scopeDomain, Scope scope, Thread thread,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetDomain( scopeDomain, scope, thread, cln,csf,cmn );
        #endif
    }

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
     * @param scope       Either \e %Scope.ThreadOuter or \e %Scope.ThreadInner. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related Scope Domains for.
     *                    Defaults to the current thread.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void RemoveThreadDomain( String scopeDomain, Scope scope, Thread thread= null,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.RemoveThreadDomain( scopeDomain, scope, thread, cln,csf,cmn );
        #endif
    }

    /** ****************************************************************************************
     * Adds a <em>Domain Substitution Rule</em>.
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
     * to remove all <em>Domain Substitution Rules</em> right after the \b %Lox was created by invoking this method with
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
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void     SetDomainSubstitutionRule( String domainPath, String replacement,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetDomainSubstitutionRule( domainPath, replacement ,cln,csf,cmn);
        #endif
    }

    /** ****************************************************************************************
     * The given \p logable becomes a <em>Prefix Logable</em> provided to loggers with log statements
     * executed within the given \p scope.
     * The list of objects received by a logger is sorted from outer scope to inner scope.
     * The logable of the <em>Log Statement</em> itself, is the last in the list, except one or
     * more <em>Prefix Logables</em> of \e %Scope.ThreadInner are set. Those are (similar to how this
     * \e %Scope is handled with <em>%Scope Domains</em>) are appended to the end of the list.
     *
     * To remove a previously set <em>Prefix Logable</em>, \c null has to be passed with
     * parameter \p logable.
     * For \e %Scope.ThreadOuter and \e %Scope.ThreadInner, passing \c null
     * removes the most recently added <em>Prefix Logable</em>.
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
     * @param scope       The scope that should the given \p logable be registered for.
     *                    Available Scope definitions are platform/language dependent.
     * @param pathLevel   Used only if parameter \p scope equals
     *                    \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                    to reference parent directories. Optional and defaults to \c 0.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void SetPrefix( Object logable, Scope scope, int pathLevel = 0,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetPrefix( logable, scope, pathLevel ,cln,csf,cmn);
        #endif
    }


    /** ****************************************************************************************
     * This overloaded version of
     * \ref SetPrefix(Object,Scope,int, int,String,String) "SetPrefix" is applicable only for
     * \e %Scope.ThreadOuter and \e %Scope.ThreadInner and allows to specify the thread that
     * the setting should be associated with.
     *
     * If \p logable is null, the most recently added <em>Prefix Logable</em> is removed.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     * @param scope       Either \e %Scope.ThreadOuter or \e %Scope.ThreadInner. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related <em>Prefix Logable</em> for.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void SetPrefix( Object logable, Scope scope, Thread thread,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetPrefix( logable, scope, thread ,cln,csf,cmn);
        #endif
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
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void SetPrefix( Object logable, String domain =null,
                                  Inclusion otherPLs =Inclusion.Include,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetPrefix( logable, domain, otherPLs  ,cln,csf,cmn);
        #endif
    }

    /** ********************************************************************************************
     * This method is used reset (or to explicitly set) the start time of the \e Logger(s).
     * The only impact is the output of time differences in the log lines. Hence, it is useful to
     * see some absolute time values when doing basic performance tests using the \e Logger.
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
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void SetStartTime( DateTime? startTime= null, String loggerName= null,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetStartTime( startTime, loggerName, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * This method sets a human readable name to the given thread ID (or current thread) which is
     * optionally included in each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs
     * @param id            (Optional) Parameter providing the thread ID. If omitted, the
     *                      current thread's ID is used.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void MapThreadName( String threadName, int id= -1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.MapThreadName( threadName, id, cln,csf,cmn );
        #endif
    }

    /** ****************************************************************************************
     * Stores ALox <em>Log Data</em>, an object of base type
     * \ref cs::aworx::lox::LogData "LogData" which can afterwards be retrieved by invoking
     * #Retrieve. Using the optional \p key and \p scope offer various possibilities to reference
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
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                  to reference parent directories. Optional and defaults to \c 0.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Store( LogData  data,                     String    key,
                       Scope scope= Scope.Global , int       pathLevel= 0,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Store( data, key, scope, pathLevel,  cln,csf,cmn);
        #endif
    }

    /** ****************************************************************************************
     * Overloaded version of
     * Store(LogData*,const TString&,Scope,int) "Store" which omits parameter \p key.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                  to reference parent directories. Optional and defaults to \c 0.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Store( LogData data,
                              Scope scope= Scope.Global , int            pathLevel= 0,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Store( data, null, scope, pathLevel,  cln,csf,cmn);
        #endif
    }

    /** ****************************************************************************************
     * Retrieves ALox <em>Log Data</em>, an object of base type
     * \ref cs::aworx::lox::LogData "LogData" which can be stored by invoking
     * #Store. Using the optional \p key and \p scope offer various possibilities to reference
     * such objects.<br>
     *
     * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
     *       It is not advised to use <em>Log Data</em> to implement application logic.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                  to reference parent directories. Optional and defaults to \c 0.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public static LogData  Retrieve( String key, Scope scope= Scope.Global,  int pathLevel= 0,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            return LOX.Retrieve( key, scope, pathLevel,  cln,csf,cmn);
        #else
            return null;
        #endif
    }

    /** ****************************************************************************************
     * Overloaded version of #Retrieve which omits parameter \p key.
     *
     * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
     *       It is not advised to use <em>Log Data</em> to implement application logic.
     *
     * @param scope     The \e %Scope that the data is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                  to reference parent directories. Optional and defaults to \c 0.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public static LogData  Retrieve( Scope scope= Scope.Global , int pathLevel= 0,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            return LOX.Retrieve( null, scope, pathLevel    ,cln,csf,cmn);
        #else
            return null;
        #endif
    }

    /** ********************************************************************************************
     * This method logs the current configuration of this Lox and its encapsulated objects.
     * It uses method #GetState to assemble the logable string.
     *
     * \note
     *   As an alternative to (temporarily) adding an invocation of <b>%Lox.State</b> to
     *   your code, ALox provides configuration variable
     *   [ALOX_LOXNAME_DUMP_STATE_ON_EXIT](group__GrpALoxConfigVars.html).
     *   This allows to enable an automatic invocation of this method using external
     *   configuration data like command line parameters, environment variables or
     *   INI files.
     *
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param headLine  If given, a separated headline will be logged at first place.
     * @param flags     Flag bits that define which state information is logged.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void State(   String          domain,
                                    Verbosity       verbosity,
                                    String          headLine,
                                    Lox.StateInfo  flags    = Lox.StateInfo.All,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.State( domain, verbosity, headLine, flags, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * This method collects state information about this lox in a formated multi-line AString.
     * Parameter \p flags is a bit field with bits defined in enum
     * \ref cs::aworx::lox::Lox::StateInfo "Lox.StateInfo".
     *
     * @param buf       The target string.
     * @param flags     Flag bits that define which state information is collected.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void GetState( AString buf,  Lox.StateInfo flags,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.GetState( buf, flags, cln,csf,cmn );
        #endif
    }

    // #############################################################################################
    // Main logging methods
    // #############################################################################################

    /** ********************************************************************************************
     * Logs a \e Logable with the given \e %Verbosity.
     *
     * @param domain       Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                     set for the \e %Scope of invocation.
     * @param verbosity    The verbosity.
     * @param logable      The object to log.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Entry( String domain, Verbosity verbosity, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Entry( domain, verbosity, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of #Entry, defaulting parameter \p domain to a nulled string.
     *
     * @param verbosity     The verbosity.
     * @param logable       The object to log.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Entry( Verbosity verbosity, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Entry( null, verbosity, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable using \ref Verbosity.Verbose.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Verbose( String domain, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Entry( domain, Verbosity.Verbose, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of #Verbose, defaulting parameter \p domain to a nulled string.
     *
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Verbose( Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Entry( null, Verbosity.Verbose, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable using \ref Verbosity.Info.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Info( String domain, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Entry( domain, Verbosity.Info, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of #Info, defaulting parameter \p domain to a nulled string.
     *
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Info( Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Entry(  null, Verbosity.Info, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable using \ref Verbosity.Warning.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Warning( String domain, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Entry( domain, Verbosity.Warning, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of #Warning, defaulting parameter \p domain to a nulled string.
     *
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Warning( Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Entry( null, Verbosity.Warning, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable using \ref Verbosity.Error.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Error( String domain, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Entry( domain, Verbosity.Error, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of #Error, defaulting parameter \p domain to a nulled string.
     *
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Error( Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Entry( null, Verbosity.Error, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable once, up to \p quantity times or every n-th time.
     * In its simplest overloaded version, the counter is bound to the source code line, hence,
     * only the first execution of this exact <em>Log Statement</em> is executed.
     *
     * Using parameter \p group, a set of <em>Log Statements</em> that share the same group key, can be
     * grouped and of such set, only the one which is first executed actually logs.<br>
     * Alternatively, when \p key is omitted (or null or empty), but a
     * \ref cs::aworx::lox::Scope "Scope" is given with parameter \p scope, then the
     * counter is associated with the scope.<br>
     * Finally, parameters \p key and \p scope can also be used in combination. The key is
     * then unique in respect to the \ref cs::aworx::lox::Scope "Scope" provided.
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
     * When parameter \p quantity is a negative value, the log statement is executed every n-th time
     * instead n-times. E.g, if \p quantity is \c -5, the first statement is executed and afterwards
     * every fifth invocation.
     *
     * \note C# autoboxes parameter values of type 'int', which leads to ambiguous statements.
     *       This is why all %Once methods are doubled with a String-type parameter \p logable.
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
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *                  If negative, the first and every "-quantity-th" statement is executed.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once( String domain, Verbosity verbosity, Object logable,
               String group,
               Scope scope= Scope.Global , int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( domain, verbosity, logable, group, scope, pathLevel, quantity,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log..
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                        Verbosity verbosity, Object logable,
               String group,
               Scope scope, int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, verbosity, logable, group, scope, pathLevel, quantity,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log..
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                        Verbosity verbosity, Object logable,
               String group,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, verbosity, logable, group, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log..
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                        Verbosity verbosity, Object logable,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, verbosity, logable, null, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The object to log..
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                                          Object logable,
               String group,
               Scope scope, int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, Verbosity.Info, logable, group, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log..
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once( String domain, Verbosity verbosity, Object logable,
               Scope scope= Scope.Global , int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( domain, verbosity, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log..
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                        Verbosity verbosity, Object logable,
               Scope scope, int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, verbosity, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The object to log..
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                                          Object logable,
               Scope scope, int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, Verbosity.Info, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The object to log..
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                                          Object logable,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, Verbosity.Info, logable, null, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The object to log..
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                                          Object logable,
               String group, int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, Verbosity.Info, logable, group, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable once, or up to \p quantity times.
     * In its simplest overloaded version, the counter is bound to the source code line, hence,
     * only the first execution of this exact <em>Log Statement</em> is executed.
     *
     * Using parameter \p group, a set of <em>Log Statements</em> that share the same group key, can be
     * grouped and of such set, only the one which is first executed actually logs.<br>
     * Alternatively, when \p key is omitted (or null or empty), but a
     * \ref cs::aworx::lox::Scope "Scope" is given with parameter \p scope, then the
     * counter is associated with the scope.<br>
     * Finally, parameters \p key and \p scope can also be used in combination. The key is
     * then unique in respect to the \ref cs::aworx::lox::Scope "Scope" provided.
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
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once( String domain, Verbosity verbosity, String logable,
               String group,
               Scope scope= Scope.Global , int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( domain, verbosity, logable, group, scope, pathLevel, quantity,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                        Verbosity verbosity, String logable,
               String group,
               Scope scope, int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, verbosity, logable, group, scope, pathLevel, quantity,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                        Verbosity verbosity, String logable,
               String group,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, verbosity, logable, group, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                        Verbosity verbosity, String logable,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, verbosity, logable, null, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The string message to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                                          String logable,
               String group,
               Scope scope, int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, Verbosity.Info, logable, group, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once( String domain, Verbosity verbosity, String logable,
               Scope scope= Scope.Global , int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( domain, verbosity, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                        Verbosity verbosity, String logable,
               Scope scope, int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, verbosity, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The string message to log.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                                          String logable,
               Scope scope, int pathLevel= 0,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, Verbosity.Info, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                                          String logable,
               int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, Verbosity.Info, logable, null, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The string message to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static
    void Once(                                          String logable,
               String group, int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Once( null, Verbosity.Info, logable, group, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is not \c true.
     * If executed, \ref Verbosity.Error is used.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Assert( bool condition, String domain, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Assert( condition, domain, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is not \c true.
     * If executed, \ref Verbosity.Error is used.
     *
     * This overloaded version omits parameter \p domain.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Assert( bool condition, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Assert( condition, null, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is \c true.
     *
     * \see Method #Assert.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void If( bool condition, String domain, Verbosity verbosity, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.If( condition, domain, verbosity, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is \c true.
     * This overloaded version omits parameter \p domain.
     *
     * \see Method #Assert.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param verbosity The verbosity.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void If( bool condition, Verbosity verbosity, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.If( condition, null, verbosity, logable, cln,csf,cmn );
        #endif
    }
}


} // namespace
