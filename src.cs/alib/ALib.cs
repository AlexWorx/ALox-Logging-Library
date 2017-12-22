// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
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
using cs.aworx.lib.lang;

/**
 * This is the outer C++ namespace for all classes published by A-Worx GmbH, Germany.
 * There is nothing inside this namespace but other namespaces.<p>
 * \note
 *   While the Java language strongly proposes to use the complete 'reverse domain' name
 *   and therefore Java code published by A-Worx GmbH resides in namespace <em>com.aworx</em>,
 *   for C# we decided for the prefix *cs* and for C++ we do not use a prefix.
 *   This is for having classes with the same names existing in C++, C# and Java not collide
 *   within the [Doxygen](http://www.stack.nl/~dimitri/doxygen) documentation system.
 */
namespace cs.aworx {}


/**
 * This is the C# namespace for core utility classes developed by A-Worx GmbH, Germany,
 * published under <em>Boost Software License</em>.
 *
 * The set of classes and things found within this namespace and its descendants is referred
 * to as <em>AWorx Utility Classes</em>, <em>AWorx Library</em> or just <em>A-Worx</em>.
 *
 * Besides C#, this library is available in C++ and Java, with language specific differences.
 * The design goals of the three are:
 * - Be small, efficient and easy to understand
 * - Keep C++, C# and Java versions similar and mimic functionality of core classes of all
 *   three languages whenever this is appropriate, with the intent to keep source code building
 *   upon the library to a certain degree similar and exchangable.
 */
namespace cs.aworx.lib {

/** ************************************************************************************************
 *  This class is a 100% static placeholder for global methods and fields of
 * \ref cs.aworx.lib "ALib".
 *   Among the things implemented here are:
 * - Collecting information on the executed process and its environment.
 * - Initialization of several ALib components with methods #Init and #TerminationCleanUp.
 * - Thread sleep methods
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
        public static readonly  int                    Version                                =1712;

        /**
         * The revision number of this release. Each ALib #Version is initially released as
         * revision \e 0. Pure bug-fix releases that do not change the interface of ALib
         * are holding the same #Version but an increased number in this field.
         */
        public static readonly  int                    Revision                                  =0;

        /**
         * The configuration used by \alox. This is received or created with overloaded
         * #Init methods. It might be shared with other libraries or can be an instance
         * explicitly dedicated to the \alox library.<br>
         * The option to use an exclusive one may be used to store \alox configuration
         * variables in different configuration files, e.g. to reduce "clutter" of an
         * applications' then "main" configuration file.<br>
         * Changes should only be made at very initial, single threaded bootstrap code,
         * with the invocation of the according method \ref #Init(Configuration).
         *
         * \see  Field #ConfigCategory.
         */
        public static      Configuration               Config                                 =null;

        /**
         * The name of the configuration category of configuration variables used by the AWorx
         * library.<br>
         * Defaults to "ALIB".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #Init.
         */
        public  static      AString                    ConfigCategory   = new AString( "ALIB" );

        /** Configuration variable declaration */
        public static       VariableDecl      WAIT_FOR_KEY_PRESS = new VariableDecl(

            ALIB.ConfigCategory,   null,     "WAIT_FOR_KEY_PRESS",
            "",
            '\0', null, Variable.FormatHint.None,
            "If true, the process waits for a key stroke on termination. If empty, under Windows \n"
          + "behavior is detected, under other OSes, defaults to false." );


        /**
        * If true, within #TerminationCleanUp, it is waited for a key press in the console
        * window.<br>
        * By default, this flag is enabled when debugging a console application under Visual
        * Studio.<br>
        * This default behavior can be overruled by setting configuration variable
        * [ALIB_WAIT_FOR_KEY_PRESS](../group__GrpALoxConfigVars.html).<br>
        * In addition, this public flag may be modified at runtime.
        */
        public static       bool                    WaitForKeyPressOnTermination;

        /**
         * This is a smart mutex that allows to lock an applications' <em>standard output
         * streams</em>.
         *
         * In multi-threaded processes, to protect the output streams from concurrent access,
         * this smart lock might be used by any \e entity that writes data to the streams.
         * Before it can be used (acquired and released), it is needed to register with the object
         * using
         * \ref cs.aworx.lib.threads.SmartLock.AddAcquirer "SmartLock.AddAcquirer".
         * This has to be done once per thread that aims to write to the stream. Then, prior to
         * writing, this object has to be acquired and after writing released.
         *
         * Because often, the standard \e output stream and standard \e error stream are identical,
         * ALib provides one single lock for both, to protect also against interwoven
         * standard output and error information.
         *
         * If the 'entity' that is registering is not of type
         * \ref cs.aworx.lib.threads.ThreadLock "ThreadLock" it is allowed to provide \c null
         * in the parameter of method \b AddAcquirer. In this case, the process of adding and
         * removing \e acquirers is not performed in a thread safe way. Therefore it is advised
         * to register so called anonymous (\c null) \e acquirers only at bootstrap time, when
         * no parallel threads were started, yet.
         *
         * If an application is deemed to always write to the standard output streams from within
         * multiple threads, an alternative to registering each writing entity, is to
         * invoke \b AddAcquirer just two times in a row with \c null at the start of a process
         * and then never do this again (and never de-register). This way, no thread needs
         * to register/deregister but threads may still \b Acquire and \b Release the lock without
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

        /** Internal flag used to by property #HasConsoleWindow     */
        private static      bool?                   _sysInfo_HasConsoleWindow;

        /** Determines if a console is attached to this process */
        public static       bool                    HasConsoleWindow
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
         * This method must be called prior to using \alib, e.g. at the beginning of
         * the \c main() method of an application. It is OK, to call this method more than once,
         * which allows independent code blocks (e.g. libraries) to bootstrap %ALIB independently.
         * However, only the first invocation is effective
         *
         * The very first invocation should not be interrupted by a parallel invocation of a
         * second thread. Consequently, with more complex applications it is recommended to
         * explicitly invoke this method once when the software is bootstrapped.
         *
         * If command line parameters should be used for configuring \b %ALox, then the very first
         * call to this method has to provide the argc and argv parameters.
         * Subsequent calls to this method with different parameters do not change the setup.
         *
         * If other, custom configuration data sources should be used already with this method
         * use overloaded method
         * \ref aworx.lib.ALIB.Init(Configuration) "ALIB.Init(Configuration)".
         *
         * \note
             In the current implementation, the only configuration variable read with this method
         *   is \c WAIT_FOR_KEY_PRESS.
         *
         * @param args    Parameters taken from <em>standard C#</em> method \c main()
         *                (the list of command line arguments).
         *                Defaults to null.
         ******************************************************************************************/
        public static void     Init( String[] args= null )
        {
            if ( isInitialized )
                return;
            isInitialized= true;

            Config= new Configuration();
            Config.SetCommandLineArgs( args );
            init();
        }

        /** ****************************************************************************************
         * Variant of method #Init, accepting a configuration.
         * This will be stored in field #Config and used for loading and storing \alib
         * variables.
         *
         * @param config  The configuration object to use with \alib variables.
         ******************************************************************************************/
        public static void Init( Configuration config )
        {
            if ( isInitialized )
                return;
            isInitialized= true;

            Config= config;
            init();
        }

        /** ****************************************************************************************
         * Used by #Init functions.
         ******************************************************************************************/
        private static void init( )
        {
            // set the system's locale as the default for our static default number format
            NumberFormat.Global.SetFromLocale();
            NumberFormat.Global.WriteGroupChars= true;

            // --- determine if we want to wait for a keypress upon termination ---
            {
                Variable variable= new Variable( ALIB.WAIT_FOR_KEY_PRESS );
                Config.Load( variable );
                if ( variable.Size() > 0 )
                    WaitForKeyPressOnTermination= variable.IsTrue();
                else
                {
                    #if ALIB_IDE_VSTUDIO
                        WaitForKeyPressOnTermination=  ALIB.HasConsoleWindow && System.Diagnostics.Debugger.IsAttached;
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

    // #############################################################################################
    // System info
    // #############################################################################################

        /** ****************************************************************************************
         * Detects if this is running on Windows OS.
         *
         * @return \c true if the calling process is running on Windows
         ******************************************************************************************/
        public static bool IsWindowsOS()
        {
            var os= System.Environment.OSVersion.Platform;
            return      os==PlatformID.Win32NT
                    ||  os==PlatformID.Win32S
                    ||  os==PlatformID.Win32Windows;
        }

        // #############################################################################################
        // Other static interface methods
        // #############################################################################################

        /** ****************************************************************************************
         * Suspends the current thread by calling Thread.Sleep().
         * Provided for compatibility with other platform versions of ALib.
         * Variants of this method are #SleepMillis, #SleepMicros and #SleepNanos.
         *
         * @param ticks    Sleep time in \b %Ticks.
         ******************************************************************************************/
        public static void Sleep(Ticks ticks)
        {
            if ( ticks.Raw() > 0 )
                Thread.Sleep( TimeSpan.FromTicks( ticks.Raw() ) );
        }

        /** ****************************************************************************************
         * Suspends the current thread by calling Thread.Sleep().
         * Provided for compatibility with other platform versions of ALib.
         * Variants of this method are #Sleep, #SleepMicros and #SleepNanos.
         *
         * @param millisecs    Sleep time in milliseconds.
         ******************************************************************************************/
        public static void SleepMillis(int millisecs)
        {
            if ( millisecs > 0 )
                Thread.Sleep( millisecs );
        }

        /** ****************************************************************************************
         * Suspends the current thread by calling Thread.Sleep().
         * Provided for compatibility with other platform versions of ALib.
         * Variants of this method are #Sleep, #SleepMillis and #SleepNanos.
         *
         * @param microsecs    Sleep time in microseconds.
         ******************************************************************************************/
        public static void SleepMicros( long microsecs )
        {
            if ( microsecs > 0 )
                Thread.Sleep( TimeSpan.FromTicks( microsecs * 10L ) );
        }

        /** ****************************************************************************************
         * Suspends the current thread by calling Thread.Sleep().
         * Provided for compatibility with other platform versions of ALib.
         * Variants of this method are #Sleep, #SleepMillis and #SleepMicros.
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
         * \ref cs.aworx.lib.lang.Inclusion "enums.Inclusion".
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
         * \ref aworx.lib.lang.Case "enums.Case".
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
         * \ref cs.aworx.lib.lang.Inclusion "enums.Inclusion".
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
