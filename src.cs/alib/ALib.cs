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
using cs.aworx.lib.enums;

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
        public static readonly  int                    Version                                =1604;

        /**
         * The revision number of this release. Each ALib #Version is initially released as
         * revision \e 0. Pure bug-fix releases that do not change the interface of ALib
         * are holding the same #Version but an increased number in this field.
         */
        public static readonly  int                    Revision                                  =1;

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
        public static       Configuration           Config                     =new Configuration();

        /**
         * The name of the configuration category of configuration variables used by the AWorx
         * library.<br>
         * Defaults to "ALIB".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #Init.
         */

        public  static      String                  ConfigCategoryName                      ="ALIB";

        /**
        * If true, within #TerminationCleanUp, it is waited for a key press in the console
        * window.<br>
        * By default, this flag is enabled when debugging a console application under Visual
        * Studio.<br>
        * This default behavior can be overruled by setting configuration variable
        * [ALIB_WAIT_FOR_KEY_PRESS_ON_TERMINATION](../group__GrpALoxConfigVars.html).<br>
        * In addition, this public flag may be modified at runtime.
        */
        public static       bool                    WaitForKeyPressOnTermination;

        /**
         * This is a general mutex that is used by ALib internally but also may be used from outside
         * for different purposes. It is non-recursive and supposed to be used seldom and 'shortly',
         * e.g. for one-time initialization tasks. In case of doubt, a separated, problem-specific
         * mutex should be created.
         */
        public static       ThreadLock              Lock      =new ThreadLock(LockMode.SingleLocks);

        /**
         * This is a smart mutex that allows to lock an applications' <em>standard output
         * streams</em>.
         *
         * In multi-threaded processes, to protect the output streams from concurrent access,
         * this smart lock might be used by any \e entity that writes data to the streams.
         * Before it can be used (acquired and released), it is needed to register with the object
         * using
         * \ref cs::aworx::lib::threads::SmartLock::AddAcquirer "SmartLock.AddAcquirer".
         * This has to be done once per thread that aims to write to the stream. Then, prior to
         * writing, this object has to be acquired and after writing released.
         *
         * Because often, the standard \e output stream and standard \e error stream are identical,
         * ALib provides one single lock for both, to protect also against interwoven
         * standard output and error information.
         *
         * If the 'entity' that is registering is not of type
         * \ref cs::aworx::lib::threads::ThreadLock "ThreadLock" it is allowed to provide \c null
         * in the parameter of method \b AddAcquirer. In this case, the process of adding and
         * removing \e acquirers is not performed in a thread safe way. Therefore it is advised
         * to register so called anonymous (\c null) \e acquirers only at bootstrap time, when
         * no parallel threads were started, yet.
         *
         * If an application is deemed to always write to the standard output streams from within
         * multiple threads, an alternative to registering each writing entity, is to
         * invoke \b AddAcquirer just two times in a row with \c null at the start of a process
         * and then never do this again (and never de-register). This way, no thread needs
         * to register/unregister but threads may still \b Acquire and \b Release the lock without
         * being registered. In other words, once a smart lock is enabled, subsequent registrations
         * are just used to count and identify the de-registration.
         *
         * \note
         *   The advantage of the SmartLock is that if only one 'entity' registered, no
         *   system \e mutexes will be used with \b Acquire and \b Release, hence there is
         *   a performance gain. Such gain is not noticeable for the 'slow' terminal console output,
         *   but it is for fast, buffered output streams.
         * <p>
         * \note
         *   Logging library \b ALox, which is built on ALib, will register whenever a \e Logger
         *   is used that writes to the standard output stream. Hence, applications that in
         *   parallel use, e.g. \c Console.WriteLine, should register at bootstrap and \e acquire this
         *   instance prior to writing. This way, log output and other application output is
         *   not mixed, but separated in different Lines.
         */
        public static     SmartLock              StdOutputStreamsLock             = new SmartLock();

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
         * Only the first invocation is effective.
         *
         * In the C# version of the AWorx library, the invocation of this method is optional.
         * However, it is good practice to invoke this method in the main() method of a process
         * and provide the command line arguments. If no invocation is performed, no
         * configuration plug-ins are set.
         *
         * If the configuration should <em>not</em> take
         * command line arguments and/or environment variables into account, then the parameters
         * can be set accordingly. If other, custom configuration data sources should be used
         * already with this method (in the current implementation, the only configuration variable
         * read with this method is \c WAIT_FOR_KEY_PRESS_ON_TERMINATION), then such plug-in(s)
         * have to be added to public, static field #Config prior to invoking this method.
         *
         * @param useEnv        If true, a
         *                      \ref cs::aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         *                      is attached to the
         *                      \ref cs::aworx::lib::ALIB::Config "ALIB.Config" singleton. Hence,
         *                      environment variables are read and potentially overwrite
         *                      configuration variables in other configuration plug-ins.<br>
         *                      Defaults to true.
         * @param args          Parameter which in the standard case is taken from  C/C++ main()
         *                      method providing the command line arguments.
         *                      If arguments are provided, a
         *                      \ref cs::aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn"
         *                      is attached to the
         *                      \ref cs::aworx::lib::ALIB::Config "ALIB.Config" singleton. Hence,
         *                      command line options are read and those potentially overwrite
         *                      configuration variables in other configuration plug-ins.<br>
         *                      Defaults to null.
         ******************************************************************************************/
        public static void     Init(  bool useEnv= true, String[] args= null)
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
                    Config.InsertPlugin( Config.EnvCP,    Configuration.PrioEnvVars );
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
                    Config.InsertPlugin( Config.CmdLineCP, Configuration.PrioCmdLine );
                }
            }

            // --- determine if we want to wait for a keypress upon termination ---
            {
                // read configuration
                int found= 0;
                bool configValue=   Config.IsTrue( ALIB.ConfigCategoryName, "WAIT_FOR_KEY_PRESS_ON_TERMINATION", out found );
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
         * Invokes \ref cs::aworx::lib::Report::DoReport "Report.DoReport".
         * This method is pruned from release code.
         *
         * @param type  The msg type.
         * @param msg   The msg to be passed to the
         *              \ref cs::aworx::lib::ReportWriter "ReportWriter".
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void REPORT( int type, String msg ,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            Report.GetDefault().DoReport( type, msg,  csf,cln,cmn );
        }

        /** ****************************************************************************************
         * Invokes \ref cs::aworx::lib::Report::DoReport "Report.DoReport".
         * This method is pruned from release code.
         *
         * @param msg  The msg to be passed to the
         *             \ref cs::aworx::lib::ReportWriter "ReportWriter".
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ERROR( String msg ,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            Report.GetDefault().DoReport( 0, msg,  csf,cln,cmn );
        }

        /** ****************************************************************************************
         * Invokes \ref cs::aworx::lib::Report::DoReport "Report.DoReport".
         * This method is pruned from release code.
         *
         * @param msg  The msg to be passed to the
         *             \ref cs::aworx::lib::ReportWriter "ReportWriter".
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void WARNING( String msg,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            Report.GetDefault().DoReport( 1, msg,  csf,cln,cmn );
        }

        /** ****************************************************************************************
         * If given condition is false, method
         * \ref cs::aworx::lib::Report::DoReport "Report.DoReport" gets invoked with the standard message
         * "Internal Error".
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref cs::aworx::lib::ReportWriter "ReportWriter" call.
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ASSERT( bool cond,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            if ( !cond )
                Report.GetDefault().DoReport( 0, "Internal Error",  csf,cln,cmn );
        }


        /** ****************************************************************************************
         * If given condition is false, method
         * \ref cs::aworx::lib::Report::DoReport "Report.DoReport" gets invoked with the given message.
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref cs::aworx::lib::ReportWriter "ReportWriter" call.
         * @param msg  The msg to be passed to the
         *             \ref cs::aworx::lib::ReportWriter "ReportWriter".
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ASSERT_ERROR( bool cond, String msg,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
        {
            if ( !cond )
                Report.GetDefault().DoReport( 0, msg,  csf,cln,cmn );
        }

        /** ****************************************************************************************
         * If given condition is false, method
         * \ref cs::aworx::lib::Report::DoReport "Report.DoReport" gets invoked with the given message.
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref cs::aworx::lib::ReportWriter "ReportWriter" call.
         * @param msg  The msg to be passed to the
         *             \ref cs::aworx::lib::ReportWriter "ReportWriter".
         * @param cln (Optional) Caller info, compiler generated. Please omit.
         * @param csf (Optional) Caller info, compiler generated. Please omit.
         * @param cmn (Optional) Caller info, compiler generated. Please omit.
         ******************************************************************************************/
        [Conditional( "DEBUG" )]
        public static void ASSERT_WARNING( bool cond, String msg,
        [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
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


        // #########################################################################################
        // Methods to 'parse' ALib enum values from strings.
        // #########################################################################################

        /** Strings used to identify a boolean value from a string representation */
         private static char[]  trueValuesBoolean= { 't', '1', 'y' };

        /** ****************************************************************************************
         * Interprets given \p src as a boolean value.
         * \ref cs::aworx::lib::enums::Inclusion "enums.Inclusion".
         * If the case insensitive comparison of the first non-whitespace characters of the string with
         * with values "t", "1", "y", "on", "ok"
         * matches, \c true is returned.
         * Otherwise, including the case that \p src is 'nulled', \c false is returned.
         *
         * @param src The string to 'parse'.
         *
         * @returns The \b %Case value read.
         ******************************************************************************************/
        public static bool      ReadBoolean( Substring src )
        {
            int idx= src.IndexOfAny( CString.DefaultWhitespaces, Inclusion.Exclude );
            if ( idx >= 0 )
            {
                char c=  Char.ToLower( src.CharAt(idx) );
                foreach ( char v in trueValuesBoolean )
                    if ( c == v )
                        return true;

                char c2= Char.ToLower( src.CharAt( idx + 1 ) );
                if ( c == 'o' &&  ( c2 == 'n' || c2 == 'k' ) )
                    return true;
            }
            return false;
        }

        /** Strings used to identify an enum \b Case from a string representation */
         private static char[]  trueValuesCase= { 's', 't', '1', 'y' };

        /** ****************************************************************************************
         * Interprets given \p src as a value of enum type
         * \ref aworx.lib::enums::Case "enums.Case".
         * If the case insensitive comparison of the first non-whitespace characters of the string
         * with values "s", "y", "t", "1"
         * matches, \b %Case.Sensitive is returned.
         * Otherwise, including the case that \p src is 'nulled', \b %Case.Ignore is returned.
         *
         * @param src The string to 'parse'.
         *
         * @returns The \b %Case value read.
         ******************************************************************************************/
        public static Case      ReadCase( Substring src )
        {
            int idx= src.IndexOfAny( CString.DefaultWhitespaces, Inclusion.Exclude );
            if ( idx >= 0 )
            {
                int c= Char.ToLower( src.CharAt(idx) );
                foreach ( char v in trueValuesCase )
                    if ( c == v )
                        return Case.Sensitive;
            }
            return Case.Ignore;
        }

        /** Strings used to identify an enum \b Inclusion from a string representation */
        private static char[]   trueValuesInclusion= { 'i', 't', '1', 'y' };

        /** ****************************************************************************************
         * Interprets given \p src as a value of enum type
         * \ref cs::aworx::lib::enums::Inclusion "enums.Inclusion".
         * If the case insensitive comparison of the first non-whitespace characters of the string
         * with values "i", "y", "t", "1"
         * matches, \b %Inclusion.Include is returned.
         * Otherwise, including the case that \p src is 'nulled', \b %Inclusion.Exclude is returned.
         *
         * @param src The string to 'parse'.
         *
         * @returns The \b %Inclusion value read.
         ******************************************************************************************/
        public static Inclusion ReadInclusion( Substring src )
        {
            int idx= src.IndexOfAny( CString.DefaultWhitespaces, Inclusion.Exclude );
            if ( idx >= 0 )
            {
                int c= Char.ToLower( src.CharAt(idx) );
                foreach ( char v in trueValuesInclusion )
                    if ( c == v )
                        return Inclusion.Include;
            }
            return Inclusion.Exclude;
        }
}// class ALIB



} // namespace / EOF
