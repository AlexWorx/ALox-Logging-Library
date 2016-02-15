// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System.Runtime.CompilerServices;
using System;
using System.Diagnostics;
using System.Text;
using System.Threading;
using cs.aworx.lib.threads;
using cs.aworx.lib.config;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;

/**
 *  This is the outer C++ namespace for all classes published by A-Worx GmbH, Germany. As far as we
 *  have planned today, there is nothing inside this namespace but other namespaces.<p>
 *  \note While the Java language strongly proposes to use the complete 'reverse domain' name
 *  and therefore Java code published by A-Worx GmbH resides in namespace <em>com.aworx</em>,
 *  for C# we decided for the prefix *cs* and for C++ we do not use a prefix.
 *  This is for having classes with the same names existing in C++, C# and Java not collide
 *  within the Doxygen documentation system.
 */


namespace cs.aworx {}


/**
 *  This is the C# namespace for core utility classes developed by A-Worx GmbH, Germany,
 *  published under the <em>MIT License</em>.
 *
 *  The set of classes and things found within this namespace and its descendants is referred
 *  to as <em>AWorx Utility Classes</em>, <em>AWorx Library</em> or just <em>A-Worx</em>.
 *
 *  Besides C#, this library is available in C++ and Java, with language specific differences.
 *  The design goals of the three are:
 *  - Be small, efficient and easy to understand
 *  - Keep C++, C# and Java versions similar and mimic functionality of core classes of all
 *    three languages whenever this is appropriate.
 *  - Do not reinvent the world: There are more comprehensive 'low level' libraries out
 *    there! However, for some reason, we have right to exist.
 */
namespace cs.aworx.lib {

/** ************************************************************************************************
 *  This class is a 100% static placeholder for global methods and fields of
 * \ref cs::aworx::lib "ALib".
 *   Among the things implemented here are:
 * - Collecting information on the executed process and its environment.
 * - Initialization of several ALib components with methods #Init and #TerminationCleanUp.
 * - Thread sleep methods
 * - 'Pruneable' debug shortcuts to to methods of class
 *   \ref cs::aworx::lib::Report "Report".
 **************************************************************************************************/
public static class ALIB
{
    // #############################################################################################
    // public fields
    // #############################################################################################

        /**
         * The ALib version. The versioning follows the scheme YYMM (2-digit year, 2-digit month)
         * of the initial release date.
         * Besides this version number, field #Revision indicates if this is a revised version
         * of a former release.
         */
        public static readonly  int                    Version                              =1602;

        /**
         * The revision number of this release. Each ALib #Version is initially released as
         * revision \e 0. Pure bug-fix releases that do not change the interface of ALib
         * are holding the same #Version but an increased number in this field.
         */
        public static readonly  int                    Revision                                =1;

        /**
         * This is a general mutex that is used by ALib internally but also may be used from outside
         * for different purposes. It is non-recursive and supposed to be used seldom and 'shortly',
         * e.g. for one-time initialization tasks. In case of doubt, a separated, problem-specific
         * mutex should be created.
         */
        public static    ThreadLock                    Lock                     =new ThreadLock();

        /**
         * This is the configuration singleton for ALib.
         * In method #Init(), this configuration is optionally filled with the default
         * configuration plug-ins
         * \ref cs::aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         * and
         * \ref cs::aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn".
         * Further, custom plug-ins may be attached.
         *
         * For more information, see \ref cs::aworx::lib::config.
         */
        public static       Configuration           Config                   =new Configuration();

        /**
         * The name of the configuration category of configuration variables used by the AWorx
         * library.<br>
         * Defaults to "ALIB".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #Init.
         */

        public  static      String                  ConfigCategoryName                    ="ALIB";

        /**
        * If true, within #TerminationCleanUp, it is waited for a key press in the console
        * window.<br>
        * By default, this flag is enabled when debugging a console application under Visual Studio.<br>
        * This default behavior can be overruled by setting configuration variable
        * [ALIB_WAIT_FOR_KEY_PRESS_ON_TERMINATION](../group__GrpALoxConfigVars.html).<br>
        * In addition, this public flag may be modified at runtime.
        */
        public static       bool                    WaitForKeyPressOnTermination;




    // #############################################################################################
    // Environment definition/detection
    // #############################################################################################

        /** Internal flag used to by property #SysInfo_HasConsoleWindow     */
        private static      bool?                   _sysInfo_HasConsoleWindow;

        /** Determines if a console is attached to this process */
        public static       bool                    SysInfo_HasConsoleWindow
        {
            get
            {
                if (_sysInfo_HasConsoleWindow == null)
                {
                    _sysInfo_HasConsoleWindow = true;
                    try { int window_height = Console.WindowHeight; }
                    catch { _sysInfo_HasConsoleWindow = false; }
                }
                return _sysInfo_HasConsoleWindow.Value;
            }
        }



    // #############################################################################################
    // Init/TerminationCleanUp()
    // #############################################################################################

        /**  State of initialization, used to avoid double initialization.   */
        private static      bool                    isInitialized= false;

        /** ****************************************************************************************
         * This method must (may) be called prior to using the AWorx library, e.g. at the beginning of
         * the main() method of an application. It is OK, to call this method more than once, which
         * allows independent code blocks (e.g. libraries) to bootstrap ALIB without interfering.
         *
         * In the C# version of the AWorx library, the invocation of this method is optional.
         * However, it is good practice to invoke this method in the main() method of a process
         * and provide the command line arguments. If the configuration should <em>not</em> take
         * command line  arguments and/or environment variables into account, then the parameters
         * can be set accordingly.
         *
         * As different code entities might or might not invoke this method during initialization
         * the behavior is defined as follows:
         * - If the method is never invoked, environment variables are used for
         *   configuration while command line options are not.
         * - If the method is invoked multiple times, environment variables are used if the
         *   last invocation that occurs demands to use them. Command line parameters are
         *   used if one of the invocations provides the parameter array.
         *
         *
         * @param useEnv  If true, a
         *                \ref aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         *                is attached to the
         *                \ref aworx::lib::ALIB::Config "ALIB.Config" singleton. Hence,
         *                environment variables are read and potentially overwrite
         *                configuration variables in other configuration plug-ins.<br>
         *                Defaults to true.
         * @param args    Parameter which in the standard case is taken from  C/C++ main()
         *                method providing the command line arguments.
         *                If arguments are provided, a
         *                \ref aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn"
         *                is attached to the
         *                \ref aworx::lib::ALIB::Config "ALIB.Config" singleton. Hence,
         *                command line options are read and those potentially overwrite
         *                configuration variables in other configuration plug-ins.<br>
         *                Defaults to null.
         ******************************************************************************************/
        public static void     Init(  bool useEnv= true, String[] args= null )
        {
            if ( isInitialized )
                return;
            isInitialized= true;

            // set the system's locale as the default for our static default number format
            NumberFormat.Global.SetFromLocale();

            lock( Config )
            {
                // remove or insert environment plug-in
                if ( useEnv && Config.EnvCP == null )
                {
                    Config.EnvCP= new EnvironmentPlugIn();
                    Config.InsertPlugin( Config.EnvCP,    20 );
                }

                if ( !useEnv && Config.EnvCP != null )
                {
                    Config.RemovePlugin( Config.EnvCP );
                    Config.EnvCP= null;
                }

                // insert command line plug-in
                bool useArgs= ( args != null && args.Length > 0 );
                if ( useArgs && Config.CmdLineCP == null )
                {
                    Config.CmdLineCP= new CommandLinePlugIn ( args );
                    Config.InsertPlugin( Config.CmdLineCP, 10 );
                }
            }

            // --- determine if we want to wait for a keypress upon termination ---
            {
                // read configuration
                int found= 0;
                bool configValue=   Config.IsTrue( ALIB.ConfigCategoryName, "WAIT_FOR_KEY_PRESS_ON_TERMINATION", ref found );
                if ( found != 0 )
                    WaitForKeyPressOnTermination= configValue;
                else
                {
                    #if ALIB_VSTUDIO

                        WaitForKeyPressOnTermination=  ALIB.SysInfo_HasConsoleWindow && System.Diagnostics.Debugger.IsAttached;

                    #else

                        WaitForKeyPressOnTermination=  false;

                    #endif // WIN32
                }
            }


        }

        /** ****************************************************************************************
         * Got nothing to do in C#.
         ******************************************************************************************/
        public static void     TerminationCleanUp()
        {
            if ( ALIB.WaitForKeyPressOnTermination )
            {
                System.Diagnostics.Debug.Write(   "\r\nALIB: Waiting for a key press in the console window."
                                                 +"\r\n     (To disable this, set 'ALIB.WaitForKeyPressOnTermination' to 'false'.)\r\n" );

                Console.WriteLine();
                Console.WriteLine(   "ALIB: Press any key to exit... "
                                   + "      (To disable this, set 'ALIB.WaitForKeyPressOnTermination to 'false'.)" );
                Console.ReadKey();
            }

        }

        /** ****************************************************************************************
         * Invokes \ref aworx::lib::Report::DoReport "Report.DoReport".
         * This method is pruned from release code.
         *
         * @param msg  The msg to be passed to the
         *             \ref aworx::lib::ReportWriter "ReportWriter".
         * @param csf  (Optional) Caller info, compiler generated. Please omit.
         * @param cln  (Optional) Caller info, compiler generated. Please omit.
         * @param cmn  (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ERROR( String msg ,
                                  [CallerFilePath]   String csf="",
                                  [CallerLineNumber] int    cln= 0,
                                  [CallerMemberName] String cmn=""           )
        {
            Report.GetDefault().DoReport( 0, msg,  csf,cln,cmn );
        }

        /** ****************************************************************************************
         * Invokes \ref aworx::lib::Report::DoReport "Report.DoReport".
         * This method is pruned from release code.
         *
         * @param msg  The msg to be passed to the
         *             \ref aworx::lib::ReportWriter "ReportWriter".
         * @param csf  (Optional) Caller info, compiler generated. Please omit.
         * @param cln  (Optional) Caller info, compiler generated. Please omit.
         * @param cmn  (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void WARNING( String msg,
                                    [CallerFilePath]   String csf="",
                                    [CallerLineNumber] int    cln= 0,
                                    [CallerMemberName] String cmn=""           )
        {
            Report.GetDefault().DoReport( 1, msg,  csf,cln,cmn );
        }

        /** ****************************************************************************************
         * If given condition is false, method
         * \ref aworx::lib::Report::DoReport "Report.DoReport" gets invoked with the standard message
         * "Internal Error".
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref aworx::lib::ReportWriter "ReportWriter" call.
         * @param csf  (Optional) Caller info, compiler generated. Please omit.
         * @param cln  (Optional) Caller info, compiler generated. Please omit.
         * @param cmn  (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ASSERT( bool cond,
                                   [CallerFilePath]   String csf="",
                                   [CallerLineNumber] int    cln= 0,
                                   [CallerMemberName] String cmn=""           )
        {
            if ( !cond )
                Report.GetDefault().DoReport( 0, "Internal Error",  csf,cln,cmn );
        }


        /** ****************************************************************************************
         * If given condition is false, method
         * \ref aworx::lib::Report::DoReport "Report.DoReport" gets invoked with the given message.
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref aworx::lib::ReportWriter "ReportWriter" call.
         * @param msg  The msg to be passed to the
         *             \ref aworx::lib::ReportWriter "ReportWriter".
         * @param csf  (Optional) Caller info, compiler generated. Please omit.
         * @param cln  (Optional) Caller info, compiler generated. Please omit.
         * @param cmn  (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ASSERT_ERROR( bool cond, String msg,
                                         [CallerFilePath]   String csf="",
                                         [CallerLineNumber] int    cln= 0,
                                         [CallerMemberName] String cmn=""           )

        {
            if ( !cond )
                Report.GetDefault().DoReport( 0, msg,  csf,cln,cmn );
        }

        /** ****************************************************************************************
         * If given condition is false, method
         * \ref aworx::lib::Report::DoReport "Report.DoReport" gets invoked with the given message.
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref aworx::lib::ReportWriter "ReportWriter" call.
         * @param msg  The msg to be passed to the
         *             \ref aworx::lib::ReportWriter "ReportWriter".
         * @param csf  (Optional) Caller info, compiler generated. Please omit.
         * @param cln  (Optional) Caller info, compiler generated. Please omit.
         * @param cmn  (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ASSERT_WARNING( bool cond, String msg,
                                           [CallerFilePath]   String csf="",
                                           [CallerLineNumber] int    cln= 0,
                                           [CallerMemberName] String cmn=""           )
        {
            if ( !cond )
                Report.GetDefault().DoReport( 1, msg,  csf,cln,cmn );
        }

    // #############################################################################################
    // System info
    // #############################################################################################

        /** ****************************************************************************************
         * Detects if this is running on Windows OS.
         *
         * @return \c true if the calling process is running on Windows
         ******************************************************************************************/
        public static bool SysInfo_IsWindowsOS()
        {
            var os= Environment.OSVersion.Platform;
            return      os==PlatformID.Win32NT
                    ||  os==PlatformID.Win32S
                    ||  os==PlatformID.Win32Windows;
        }

        // #############################################################################################
        // Other static interface methods
        // #############################################################################################

        /** ****************************************************************************************
         * This is calling Thread.Sleep(). This is for compatibility with other platform
         * versions of A-Worx Utility Classes.
         * Variants of this method are #SleepMicros and #SleepNanos.
         *
         * @param millisecs    Sleep time in milliseconds.
         ******************************************************************************************/
        public static void SleepMillis(int millisecs)
        {
            if ( millisecs > 0 )
                Thread.Sleep( millisecs );
        }

        /** ****************************************************************************************
         * This is calling Thread.Sleep(). This is for compatibility with other platform
         * versions of A-Worx Utility Classes.
         * Variants of this method are #SleepMillis and #SleepNanos.
         *
         * @param microsecs    Sleep time in microseconds.
         ******************************************************************************************/
        public static void SleepMicros( long microsecs )
        {
            if ( microsecs > 0 )
                Thread.Sleep( TimeSpan.FromTicks( microsecs * 10L ) );
        }

        /** ****************************************************************************************
         * This is calling Thread.Sleep(). This is for compatibility with other platform
         * versions of A-Worx Utility Classes.
         * Variants of this method are #SleepMillis and #SleepMicros.
         *
         * @param nanosecs    Sleep time in microseconds.
         ******************************************************************************************/
        public static void SleepNanos( long nanosecs )
        {
            if ( nanosecs > 0 )
                Thread.Sleep( TimeSpan.FromTicks( nanosecs / 100L ) );
        }

}// class ALIB



} // namespace / EOF
