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
 *
 * In addtion, this class defines important public enumerations, provides library initialization and
 * other static functionality.
 **************************************************************************************************/
public static class Log
{
    // #############################################################################################
    // Public Enums for ALox
    // #############################################################################################

    /** ********************************************************************************************
     * These are the levels of log verbosity assignable to a log domain.
     **********************************************************************************************/
    public enum DomainLevel
    {
        /** Do not log anything  */
        Off,

        /** %Log only level Error */
        Errors,

        /** %Log only levels Warning or Error. */
        WarningsAndErrors,

        /** %Log all  levels but Verbose. */
        InfoWarningsAndErrors,

        /** %Log all. */
        All,

        /** Inherit level from parent domain */
        Inherit,
    }

    /** ********************************************************************************************
     * These are the levels of log verbosity used in a log call.
     **********************************************************************************************/
    public enum Level
    {
        /** The most verbose log level to be used for debug output statements. Logged only if
            * the domains log level is set to DomainLevel.All */
        Verbose,

        /** The standard log level for normal log output statements. Logged if the domains
            * level is either DomainLevel.All or DomainLevel.InfoWarningsAndErrors */
        Info,

        /** A log level for warning messages, hence things that might lead to errors or are not
            * welcome for other reasons, but maybe are not errors.
            * It is not logged only if the domains log level is DomainLevel.Errors or Domain.Level. Off */
        Warning,

        /** A log level for (severe) error messages
            * It is suppressed only if the domains log level is set to DomainLevel.Off */
        Error,
    }

    /** ********************************************************************************************
     * These are definitions which are used as a parameter to certain ALox methods to determine the
     * breadth of the scope of a setting. The definitions are platform dependent. E.g. in C# the
     * scope can be "Method" or "SourceFile" file while in Java it can be "Package", "Class" or
     * "Method". The difference is due to different mechanisms to automatically collect caller
     * information.
     *
     * Attn C# users: If within one source file two or more classes with equal same method names
     * exist, then such method names share the same scope and hence are ambiguous. This is due to
     * technical restrictions of how caller information is collected in C#/.Net.
     **********************************************************************************************/
    public enum Scope
    {
        /** No scope should be applied/affected */
        None,

        /** Defines the actual source file as the scope */
        SourceFile,

        /** Defines the actual method as the scope */
        Method,
    }


    // #############################################################################################
    // Public fields
    // #############################################################################################

        /**
         * The version of ALox. The version number follows the scheme YYMM (2-digit year,
         * 2-digit month) of the initial release date.
         * Besides this version number, field #Revision indicates if this is a revised version
         * of a former release.
         */
        public static readonly int                   Version                                  =1602;

        /**
         * The revision number of this release. Each ALox #Version is initially released as
         * revision \e 0. Pure maintenance releases that do not change the interface of ALox
         * are holding the same #Version but an increased number in this field.
         */
        public static readonly int                   Revision                                    =1;

        /**
         * The name of the configuration category of configuration variables used by ALox.<br>
         * Defaults to "ALOX".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #Init.<br>
         * See also \ref cs::aworx::lib::ALIB::ConfigCategoryName "ALIB.ConfigCategoryName".
         */
        public  static String         ConfigCategoryName                                    ="ALOX";

    // #############################################################################################
    // Library initialization
    // #############################################################################################
        /**  State of initialization, used to avoid double initialization.   */
        private static bool           isInitialized= false;

        /** ********************************************************************************************
         * This method must (may) be called prior to using the ALox library, e.g. at the beginning of
         * the main() method of an application. It is OK, to call this method more than once, which
         * allows independent code blocks (e.g. libraries) to bootstrap ALox without interfering.
         * But only the first call is effective and may be used to set the command line arguments
         * as configuration plug-in.
         *
         * In the C# version of the AWorx library, the invocation of this method is optional.
         * However, it is good practice to invoke this method in the main() method of a process
         * and provide the command line arguments. See \ref cs::aworx::lib::ALIB::Init "ALIB.Init"
         * for more information on the configuration parameters.
         *
         *  @param useEnv  If true, a
         *                 \ref aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         *                 is attached to the
         *                 \ref aworx::lib::ALIB::Config "ALIB.Config" singleton. Hence,
         *                 environment variables are read and potentially overwrite
         *                 configuration variables in other configuration plug-ins.<br>
         *                 Defaults to true.
         *  @param args    Parameter which in the standard case is taken from  C/C++ main()
         *                 method providing the command line arguments.
         *                 If arguments are provided, a
         *                 \ref aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn"
         *                 is attached to the
         *                 \ref aworx::lib::ALIB::Config "ALIB.Config" singleton. Hence,
         *                 command line options are read and those potentially overwrite
         *                 configuration variables in other configuration plug-ins.<br>
         *                 Defaults to null.
         **********************************************************************************************/
        public static void     Init(  bool useEnv= true, String[] args= null )
        {
            if ( isInitialized )
                return;
            isInitialized= true;

            // initialize ALIB
            ALIB.Init( useEnv, args );
        }

    // #############################################################################################
    // Debug Logging
    // #############################################################################################
    #if ALOX_DBG_LOG

        // #########################################################################################
        // Public static fields
        // #########################################################################################

        /**
         *  This is a static singleton of type class Lox which is used for standard
         *  debug logging statements.
         */
        public static   Lox              LOX                                             =new Lox();

        /** The debug logger created by AddDebugLogger. */
        public static   TextLogger       DebugLogger                                          =null;

        /**
         * The ALib ReportWriter. This will be created and registered in method
         * \ref cs::aworx::lox::Log::AddDebugLogger    "Log.AddDebugLogger" and removed in
         * \ref cs::aworx::lox::Log::RemoveDebugLogger "Log.RemoveDebugLogger".
         */
        public static   ALoxReportWriter DebugReportWriter                                    =null;

        // #########################################################################################
        // ALox based AWorx lib ReportWriter
        // #########################################################################################

        /** ****************************************************************************************
         * The \b %ReportWriter for ALib when using ALox. An instance of this class is
         * created in method \ref cs::aworx::lox::Log::AddDebugLogger "Log.AddDebugLogger"
         * and registered with ALib.
         ******************************************************************************************/
        public class    ALoxReportWriter : ReportWriter
        {
            /** The \b Lox to report to */
            protected   Lox        lox;

            /** ************************************************************************************
             * Constructs an \b %ALoxReportWriter.
             * @param lox    The \b Lox to report to.
             **************************************************************************************/
            public ALoxReportWriter ( Lox lox )                 { this.lox= lox; }

            /** ************************************************************************************
             * Log an ALib report using ALox.
             * @param report  The error message.
             **************************************************************************************/
            public void Report  (Report.Message report)
            {
                if( report.Type == 0 )
                    lox.Error  ( "REPORT",  report.Contents, 0, report.File, report.Line, report.Func );
                else
                    lox.Warning( "REPORT",  report.Contents, 0, report.File, report.Line, report.Func );
            }
        }

    // #########################################################################################
    // Interface (not auto removed)
    // #########################################################################################

        /** ****************************************************************************************
         * Retrieve an instance of a Logger by its name. Note: This function is not automatically
         * removed from the release code because of technical restrictions. It has to be conditionally
         * compiled by enclosing calls to it with "#if ... #endif" statements.
         *
         * @param loggerName    The name of the logger to search for (case insensitive)
         * @return  The logger, null if not found.
         ******************************************************************************************/
        public static Logger GetLogger( String loggerName )
        {
            return LOX.GetLogger( loggerName );
        }

    #endif

    // #############################################################################################
    // Interface methods NOT copied from Lox (not auto removed)
    // #############################################################################################

        /** ********************************************************************************************
         * Returns an AString singleton (contained in the Lox singleton), that can be reused for all basic
         * log calls. Textual messages that are assembled from out of strings, numbers and other data, can
         * be efficiently built by reusing this singleton.
         * Whenever this method is called, the returned AString object gets "locked" by a corresponding
         * ThreadLock object. Therefore it has to be used as a message within one of the log methods of
         * this class (error(), warning(), info(), verbose(), assert() or line()) or it has to be
         * explicitly released using BufAbort().
         * If this is not done, the object does not get released and parallel threads using this method would
         * block! So, do not use Buf() for other reasons than for creating log messages and be sure to
         * release it "in time".
         *
         * @return The static LogBuf singleton.
         **********************************************************************************************/
        public static AString Buf()
        {
            #if ALOX_DBG_LOG
                return LOX.Buf();
            #else
                return null;
            #endif
        }

        /** ********************************************************************************************
         * Use this method when you want to abort a log call that you "started" with acquiring the internal
         * AString singleton acquired using method Buf(). Use BufAbort() only if you did not use the
         * acquired buffer as a parameter of a log method, because this internally releases the buf already.
         **********************************************************************************************/
        public static void BufAbort()
        {
            #if ALOX_DBG_LOG
                LOX.BufAbort();
            #endif
        }


    // #############################################################################################
    // Interface methods NOT copied from Lox (auto removed)
    // #############################################################################################

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
         *   configuration variable [ALOX_CL_NO_ADDITONAL_IDE_LOGGER](../group__GrpALoxConfigVars.html).
         *
         * Finally, \ref cs::aworx::lib::Report::ReplaceWriter "Report.ReplaceWriter"
         * is invoked to provide a ReportWriter of type
         * \ref cs::aworx::lox::Log::ALoxReportWriter "ALoxReportWriter".
         *
         * @param lox The lox to add the debug logger(s) to. If null, the static debug object
         *            #LOX is used. Defaults to null.
         * @param replaceDefaultReportWriter
         *             If true, the
         *             \ref cs::aworx::lib::ReportWriter "ReportWriter" of the \b Report returned by
         *             \ref cs::aworx::lib::Report::GetDefault "Report.GetDefault()"
         *             will be replaced by an object of type
         *             \ref cs::aworx::lox::Log::ALoxReportWriter "Log.ALoxReportWriter" using the given
         *             \p lox;
         **************************************************************************************/
        [Conditional("ALOX_DBG_LOG")]
        public static void AddDebugLogger( Lox lox= null, bool replaceDefaultReportWriter= true )
        {
            #if ALOX_DBG_LOG

                if ( lox == null )
                    lox= LOX;

                ALIB.ASSERT_ERROR( DebugLogger == null, "Illeagal repeated invocation." );

                // add a CLR logger if this a debug session
                if(     System.Diagnostics.Debugger.IsAttached
                    &&  !ALIB.Config.IsTrue( Log.ConfigCategoryName, "CL_NO_ADDITONAL_IDE_LOGGER" ))
                {
                    CLRDebuggerLogger clr= new CLRDebuggerLogger();
                    lox.AddLogger( clr );

                    // get auto sizes from last session
                    AString autoSizes= new AString();
                    if( ALIB.Config.Get( Log.ConfigCategoryName, "CL_AUTO_SIZES_IDE_LOGGER", autoSizes ) != 0 )
                        clr.AutoSizes.Import( autoSizes );
                }

                // add a default console logger
                DebugLogger= Lox.CreateConsoleLogger("DEBUG_LOGGER");

                if ( DebugLogger != null )
                {
                    lox.AddLogger( DebugLogger );

                    // replace the ReportWriter
                    if ( replaceDefaultReportWriter )
                       Report.GetDefault().ReplaceWriter( DebugReportWriter= new ALoxReportWriter( lox ) );

                    // get auto sizes from last session
                    AString autoSizes= new AString();
                    if( ALIB.Config.Get( Log.ConfigCategoryName, "CL_AUTO_SIZES", autoSizes ) != 0 )
                        DebugLogger.AutoSizes.Import( autoSizes );
                }

            #endif
        }

        /** ************************************************************************************
         * Removes the logger(s) which was/were created by \ref AddDebugLogger.
         * This method also invokes
         * \ref cs::aworx::lib::Report::ReplaceWriter "Report.ReplaceWriter(null)"
         * to install a default \ref aworx::lib::ReportWriter "ReportWriter" for ALib.
         *
         * @param lox The lox to remove the debug logger(s) from.
         *            If null, the static debug object#LOX is used.
         **************************************************************************************/
        [Conditional("ALOX_DBG_LOG")]
        public static void RemoveDebugLogger( Lox lox= null )
        {
            #if ALOX_DBG_LOG
                // replace the report writer (if we replaced it before)
                if( DebugReportWriter != null )
                    Report.GetDefault().ReplaceWriter( null );

                if ( lox == null )
                    lox= LOX;

                ALIB.ASSERT_WARNING( DebugLogger != null, "No debug logger to remove." );
                if ( DebugLogger != null )
                {
                    lox.RemoveLogger( DebugLogger );

                    // save auto sizes
                    AString autoSizes= new AString();
                    DebugLogger.AutoSizes.Export( autoSizes );
                    ALIB.Config.Save( Log.ConfigCategoryName, "CL_AUTO_SIZES", autoSizes,
                                       "Auto size values of last debug logger instance" );
                    DebugLogger= null;
                }

                CLRDebuggerLogger clr= (CLRDebuggerLogger) lox.GetLogger( "CLR_DEBUGGER" );
                if ( clr != null )
                {
                    lox.RemoveLogger( clr );

                    // save auto sizes
                    AString autoSizes= new AString();
                    clr.AutoSizes.Export( autoSizes );
                    ALIB.Config.Save( Log.ConfigCategoryName, "CL_AUTO_SIZES_IDE_LOGGER", autoSizes,
                                       "Auto size values of last IDE specific debug logger instance" );
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

    /** ********************************************************************************************
     * Adds a logger to this container of loggers.
     * Each log call that is performed through this classes' interface
     * will be forwarded to this logger, unless filtered out with optional filter parameter.
     *
     * \note
     *   This method checks whether the domain used for internal ALox messages
     *   (see field
     *   \ref cs::aworx::lox::Lox::InternalDomain "Lox.InternalDomain") is already registered
     *    with the given logger. Only if not, the domain is registered and set to domain level
     *   \ref cs::aworx::lox::Log::DomainLevel::WarningsAndErrors "DomainLevel.WarningsAndErrors".
     *   This means, that it does not play a role, if changes to the level of domain "ALOX" are
     *   performed prior to adding a logger, using
     *   \ref cs::aworx::lox::core::Logger::SetDomain "Logger.SetDomain"
     *   or after a logger was added, using
     *   \ref cs::aworx::lox::Lox::SetDomain "Lox.SetDomain".
     *
     * @param logger  The logger to be added.
     * @param csf     (Optional) Caller info, compiler generated. Please omit.
     * @param cln     (Optional) Caller info, compiler generated. Please omit.
     * @param cmn     (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void AddLogger( Logger logger,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

    {
        #if ALOX_DBG_LOG
            LOX.AddLogger( logger, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Removes all loggers that match the filter name from this static interface.
     * @param loggerFilter (Optional) A filter for the loggers to be affected. A simple
     *                              string compare without case sensitivity is performed. An asterisk
     *                              ('*') at the beginning or end of the string is used as a
     *                              wildcard. Defaults to null which causes all loggers to be
     *                              removed.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void RemoveLoggers( String loggerFilter= null )
    {
        #if ALOX_DBG_LOG
            LOX.RemoveLoggers( loggerFilter );
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
            LOX= new Lox();
            DebugLogger= null;
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
     * domain becomes the default domain for respective scope. For any subsequent log calls from within
     * this scope, where no domain is explicitly given, this default domain is used. If subsequent
     * log calls specify a domain name with a leading '~' character, then such domain is
     * concatenated to the default domain to build a complete domain path.
     *
     * @param domain    The domain name (and path) to register.
     *                          If this is starting with a swung dash ('~') this is interpreted a sub
     *                          domain to a (potentially already set!) default domain of the source file.
     *                          For other values, the default domain is ignored (regardless if this is
     *                          starting with a slash or    not).
     * @param scope     If a value other than Log.Scope.None is provided, the given domain
     *                          name is registered as the default domain for the given scope. Default
     *                          domains set for 'inner scopes' have higher priority than those set for
     *                          outer scopes. Available Scope definitions are platform/language
     *                          dependent.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void SetDomain( String    domain,     Log.Scope scope,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetDomain( domain, scope, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Sets the domain log level and (by default) all it's sub domains recursively. In the case that
     * sub domains should be set to a different log level, then this function has to be called for
     * such sub domains after the call to the parent domain (or recursion has to be switched off,
     * using the parameter 'recursive'). It is not necessary to register a domain before setting its
     * log level and log levels can be set and modified any time.
     *
     * @param domain        If this is null, the default domain is used. If this is starting
     *                      with a swung dash ('~') this is interpreted a sub domain to the
     *                      default domain of the source file. For other values, the default
     *                      domain is ignored (regardless if this is starting with a slash or
     *                      not).
     * @param domainLevel   The domains log level to be set.
     * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
     *                      parameter enables different loggers to have different domains and
     *                      log levels. A simple string compare without case sensitivity is
     *                      performed. An asterisk ('*') at the beginning or end of the
     *                      string is used as a wildcard. Leave to \e null if all loggers should be
     *                      affected. Use this parameter only in more complex logging
     *                      scenarios.
     * @param propagation   (Optional) If \c Propagation.ToDescendants, the default, the
     *                      level is set for all sub-domains recursively.
     *                      If \c Propagation.None, then only this domain is changed.
     * @param csf           (Optional) Caller info, compiler generated. Please omit.
     * @param cln           (Optional) Caller info, compiler generated. Please omit.
     * @param cmn           (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void SetDomain( String        domain,
                                  DomainLevel   domainLevel,
                                  String        loggerFilter=   null,
                                  Propagation   propagation=    Propagation.ToDescendants,

    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetDomain( domain, domainLevel, loggerFilter, propagation, csf,cln,cmn );
        #endif
    }

    /** ****************************************************************************************
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
    public  static void SetDomain( String          domain,
                                   Log.Scope       scope,
                                   Log.DomainLevel domainLevel,
                                   String          loggerFilter=   null,

    [CallerFilePath] String csf="",[CallerLineNumber]   int             cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetDomain( domain, scope, domainLevel, loggerFilter, csf, cln, cmn );
        #endif
    }

    /** ****************************************************************************************
     * <c>SetDomain(domain, scope)</c>  and <c>SetDomain(domain, domainLevel)</c>.
     *
     * @param domainLevel  The domains log level to be set.
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
     * @param csf          (Optional) Caller info, compiler generated. Please omit.
     * @param cln          (Optional) Caller info, compiler generated. Please omit.
     * @param cmn          (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  static void SetDomain( String          domain,
                                   Log.Scope       scope,
                                   Log.DomainLevel domainLevel,

    [CallerFilePath] String csf="",[CallerLineNumber]   int             cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetDomain( domain, scope, domainLevel, null, csf, cln, cmn );
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
    [Conditional("ALOX_DBG_LOG")]
    public static void SetLogger( cs.aworx.lib.enums.Switch newState, String loggerFilter,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetLogger( newState, loggerFilter, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * This method is used reset (or to explicitly set) the start time of the logger(s).
     * The only impact is the output of time differences in the log lines. Hence, it is useful to
     * see some absolute time values when doing basic performance tests using the logger. Note:
     * Calls to this method are automatically removed from release code.
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
    [Conditional("ALOX_DBG_LOG")]
    public static void SetStartTime( DateTime? startTime= null, String loggerFilter= null,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetStartTime( startTime, loggerFilter, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * This method sets a human readable name to the given thread ID (or current thread) which is
     * optionally included in each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs
     * @param id            (Optional) Parameter providing the thread ID. If omitted, the
     *                              current thread's ID is used.
     * @param csf           (Optional) Caller info, compiler generated. Please omit.
     * @param cln           (Optional) Caller info, compiler generated. Please omit.
     * @param cmn           (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void MapThreadName( String threadName, int id= -1,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.MapThreadName( threadName, id, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * This method is used store a marker object in the logging system. Markers are stored
     * and retrieved relative to a given Log.Scope. In combination with Log.GetMarker,
     * this method provides an easy way to trace the last marked position, e.g. in the case of an
     * exception. Within the exception handler, use Log.GetMarker to retrieve the last marker
     * object stored before the exception was thrown.
     *
     * @param marker  The object to store, for example a String that can be used for a
     *                        log output later.
     * @param scope   The scope in which the marker should be stored. Markers and scopes
     *                        work independently from each other. Different markers can be stored
     *                        within different scopes and no fallback to "outer scopes" is made.
     *                        A scope of 'None' stores the marker globally, hence as a system wide
     *                        singleton.
     * @param csf     (Optional) Caller info, compiler generated. Please omit.
     * @param cln     (Optional) Caller info, compiler generated. Please omit.
     * @param cmn     (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void SetMarker(    Object marker, Log.Scope scope,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.SetMarker( marker, scope, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Retrieves the most recently marker object stored using Log.SetMarker. Markers are stored
     * and retrieved relative to a given Log.Scope. In combination with Log.SetMarker,
     * this method provides an easy way to trace the last marked position, e.g. in the case of an
     * exception. Within the exception handler, use this method to retrieve the last marker
     * object stored before the exception was thrown.
     *
     * @param markerPointer    This is array is used to return the marker object. The array must
     *                                 be at least of size 1. The object is stored in position 0. (Note:
     *                                 due to compiler restrictions of C# V. 5.0, this laborious
     *                                 approach for returning the object has been chosen. The function
     *                                 can not return a value because it is conditionally compiled using
     *                                 the ALOX_DBG_LOG compiler flag.
     * @param scope            The scope in which the marker should be stored. Markers and scopes
     *                                 work independently from each other. Different markers can be stored
     *                                 within different scopes and no fallback to "outer scopes" is made.
     *                                 A scope of 'None' retrieves the global marker singleton.
     * @param csf              (Optional) Caller info, compiler generated. Please omit.
     * @param cln              (Optional) Caller info, compiler generated. Please omit.
     * @param cmn              (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void GetMarker( Object[] markerPointer, Log.Scope scope,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.GetMarker( markerPointer, scope, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * This method logs the configuration the Lox encapsulated in this static Log interface.
     *
     * @param domain           If this is null, the default domain is used. If this is starting
     *                                 with a swung dash ('~') this is interpreted a sub domain to the
     *                                 default domain of the source file. For other values, the default
     *                                 domain is ignored (regardless if this is starting with a slash or
     *                                 not).
     * @param level            The log level.
     * @param headLine         If given, a separated headline will be logged at first place.
     * @param loggerFilter     (Optional) A filter for the loggers to be affected. This
     *                                 parameter enables different loggers to have different domains. A
     *                                 simple string compare without case sensitivity is performed. An
     *                                 asterisk ('*') at the beginning or end of the string is used as a
     *                                 wildcard. Leave to \e null if all loggers should be affected. Use this
     *                                 parameter only in more complex logging scenarios.
     * @param csf              (Optional) Caller info, compiler generated. Please omit.
     * @param cln              (Optional) Caller info, compiler generated. Please omit.
     * @param cmn              (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void LogConfig(    String            domain,
                                    Log.Level        level,
                                    String            headLine,
                                    String            loggerFilter= null,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.LogConfig( domain, level, headLine, loggerFilter, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
     * log level, which is only actually logged if the log domains log level is set to "All". This
     * overloaded version does not offer a domain parameter but relies on a default domain set for
     * the source file this function is used in.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Verbose( Object msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, null, Log.Level.Verbose, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log a String with log level equal to Log.Level.Verbose. This is the highest (most verbose)
     * log level, which is only actually logged if the log domains log level is set to "All". This
     * overloaded version does not offer a domain parameter but relies on a default domain set for
     * the source file this function is used in.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    // C# auto-boxes int arguments. This is why, we would get ambiguous invocations without this
    // otherwise redundant method.
    [Conditional("ALOX_DBG_LOG")]
    public static void Verbose( String msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, null, Log.Level.Verbose, msg, indent, null, csf, cln, cmn );
        #endif
    }


    /** ********************************************************************************************
     * Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
     * log level, which is only actually logged if the log domains log level is set to "All". Note:
     * Calls to this method are automatically removed from release code.
     *
     * @param domain    If this is null, the default domain is used. If this is starting with
     *                          a swung dash ('~') this is interpreted a sub domain to the default domain
     *                          of the source file. For other values, the default domain is ignored
     *                          (regardless if this is starting with a slash or not).
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Verbose( String domain, Object msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, domain, Log.Level.Verbose, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
     * Verbose) log level, which is only actually logged if the log domains log level is set to
     * "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
     * a default domain set for the source file this function is used in.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Info( Object msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true,  null, Log.Level.Info, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log a String with log level equal to Log.Level.Info. This is the second highest (after
     * Verbose) log level, which is only actually logged if the log domains log level is set to
     * "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
     * a default domain set for the source file this function is used in.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    // C# auto-boxes int arguments. This is why, we would get ambiguous invocations without this
    // otherwise redundant method.
    [Conditional("ALOX_DBG_LOG")]
    public static void Info( String msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true,  null, Log.Level.Info, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
     * Verbose) log level, which is only actually logged if the log domains log level is set to
     * "Info" or "Verbose".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with
     *                          a swung dash ('~') this is interpreted a sub domain to the default domain
     *                          of the source file. For other values, the default domain is ignored
     *                          (regardless if this is starting with a slash or not).
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Info( String domain, Object msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, domain, Log.Level.Info, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level
     * are are logged if the log domains log level is set to "Warning", "Info" or "All".
     * This overloaded version does not offer a domain parameter but relies on a default domain set
     * for the source file this function is used in.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Warning( Object msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, null, Log.Level.Warning, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log a String with log level equal to Log.Level.Warning. Log messages of this log level
     * are are logged if the log domains log level is set to "Warning", "Info" or "All".
     * This overloaded version does not offer a domain parameter but relies on a default domain set
     * for the source file this function is used in.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    // C# auto-boxes int arguments. This is why, we would get ambiguous invocations without this
    // otherwise redundant method.
    [Conditional("ALOX_DBG_LOG")]
    public static void Warning( String msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, null, Log.Level.Warning, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
     * are logged if the log domains log level is set to "Warning", "Info" or "All".
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
    [Conditional("ALOX_DBG_LOG")]
    public static void Warning( String domain, Object msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, domain, Log.Level.Warning, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are
     * are always logged unless domains log level is set to "Off". This overloaded version does not
     * offer a domain parameter but relies on a default domain set for the source file this function
     * is used in.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Error( Object msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, null, Log.Level.Error, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log a String with log level equal to Log.Level.Error. Log messages of this log level are
     * are always logged unless domains log level is set to "Off". This overloaded version does not
     * offer a domain parameter but relies on a default domain set for the source file this function
     * is used in.
     *
     * @param msg       An Object to be logged.
     * @param indent    (Optional) The indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    // C# auto-boxes int arguments. This is why, we would get ambiguous invocations without this
    // otherwise redundant method.
    [Conditional("ALOX_DBG_LOG")]
    public static void Error( String msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, null, Log.Level.Error, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log an Object with log level equal to Log.Level Error. Log messages of this log level are are
     * always logged unless domains log level is set to "Off".
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
    [Conditional("ALOX_DBG_LOG")]
    public static void Error( String domain, Object msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, domain, Log.Level.Error, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log a string only if the given condition is not true. Log level will be highest, namely Error
     * if condition is false. This overloaded version does not offer a domain parameter but relies
     * on a default domain set for the source file this function is used in.
     *
     * @param trueOrLog The log is only performed if condition is not true.
     * @param msg       An Object to be logged.
     * @param indent    (Optional) the indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Assert( bool trueOrLog, Object msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( !trueOrLog, null, Log.Level.Error, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Log a string only if the given condition is not true. Log level will be highest, namely
     * Log.Level.Error.
     *
     * @param trueOrLog The log is only performed if condition is not true.
     * @param domain    If this is null, the default domain is used. If this is starting with
     *                  a swung dash ('~') this is interpreted a sub domain to the default
     *                  domain of the source file. For other values, the default domain is
     *                  ignored (regardless if this is starting with a slash or not).
     * @param msg       An Object to be logged.
     * @param indent    (Optional) the indentation in the output. Defaults to 0.
     * @param csf       (Optional) Caller info, compiler generated. Please omit.
     * @param cln       (Optional) Caller info, compiler generated. Please omit.
     * @param cmn       (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Assert( bool trueOrLog, String domain, Object msg, int indent = 0,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( !trueOrLog, domain, Log.Level.Error, msg, indent, null, csf, cln, cmn );
        #endif
    }

    /** ********************************************************************************************
     * Provides a more flexible but complex way to log a message. The methods #Verbose(),
     * #Info(), #Warning(), #Error() and #Assert() are using this function internally and should
     * be used in standard cases. Use this function only in the rare cases, e.g. when a log level is
     * decided only at runtime or when you want to use a logger filter, etc.
     *
     * @param doLog        Conditional logging. If false, the log is not performed. CntLogCalls
     *                     is still increased by one.
     * @param domain       If this is null, the default domain is used. If this is starting
     *                     with a swung dash ('~') this is interpreted a sub domain to the
     *                     default domain of the source file. For other values, the default
     *                     domain is ignored (regardless if this is starting with a slash or
     *                     not).
     * @param level        The log level.
     * @param msg          An Object to be logged.
     * @param indent       (Optional) The indentation in the output. Defaults to 0.
     * @param loggerFilter (Optional) A filter for the loggers to be affected. This
     *                     parameter enables different loggers to have different domains. A
     *                     simple string compare without case sensitivity is performed. An
     *                     asterisk ('*') at the beginning or end of the string is used as a
     *                     wildcard. Leave to \e null if all loggers should be affected. Use this
     *                     parameter only in more complex logging scenarios.
     * @param csf          (Optional) Caller info, compiler generated. Please omit.
     * @param cln          (Optional) Caller info, compiler generated. Please omit.
     * @param cmn          (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Line( bool doLog, String domain, Level level, Object msg, int indent = 0, String loggerFilter = null,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( doLog, domain, level, msg, indent, loggerFilter, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an Object using the given log level, log domain and indentation and logger filter.
     *
     * @param domain       If this is null, the default domain is used. If this is starting
     *                     with a swung dash ('~') this is interpreted a sub domain to the
     *                     default domain of the source file. For other values, the default
     *                     domain is ignored (regardless if this is starting with a slash or
     *                     not).
     * @param level        The log level.
     * @param msg          An Object to be logged.
     * @param indent       (Optional) The indentation in the output. Defaults to 0.
     * @param loggerFilter (Optional) A filter for the loggers to be affected. This
     *                     parameter enables different loggers to have different domains. A
     *                     simple string compare without case sensitivity is performed. An
     *                     asterisk ('*') at the beginning or end of the string is used as a
     *                     wildcard. Leave to \e null if all loggers should be affected. Use this
     *                     parameter only in more complex logging scenarios.
     * @param csf          (Optional) Caller info, compiler generated. Please omit.
     * @param cln          (Optional) Caller info, compiler generated. Please omit.
     * @param cmn          (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Line( String domain, Level level, Object msg, int indent = 0, String loggerFilter = null,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, domain, level, msg, indent, loggerFilter, csf,cln,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs an Object using the given log level, indentation and logger filter and the default
     * domain set for the scope.
     *
     * @param level         The log level.
     * @param msg           An Object to be logged.
     * @param indent        (Optional) The indentation in the output. Defaults to 0.
     * @param loggerFilter  (Optional) A filter for the loggers to be affected. This
     *                     parameter enables different loggers to have different domains. A
     *                      simple string compare without case sensitivity is performed. An
     *                      asterisk ('*') at the beginning or end of the string is used as a
     *                      wildcard. Leave to \e null if all loggers should be affected. Use this
     *                      parameter only in more complex logging scenarios.
     * @param csf           (Optional) Caller info, compiler generated. Please omit.
     * @param cln           (Optional) Caller info, compiler generated. Please omit.
     * @param cmn           (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG")]
    public static void Line( Level level, Object msg, int indent = 0, String loggerFilter = null,
    [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG
            LOX.Line( true, null, level, msg, indent, loggerFilter, csf,cln,cmn );
        #endif
    }
}


} // namespace
