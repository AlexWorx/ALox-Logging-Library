// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################



/**
 *  \namespace com.aworx
 *  This is the outer Java package for all classes published by A-Worx GmbH, Germany. As far as we
 *  have planned today, there is nothing inside this namespace but other namespaces.<p>
 *  \note While the Java language strongly proposes to use the complete 'reverse domain' name
 *  and therefore Java code published by A-Worx GmbH resides in namespace <em>com.aworx</em>,
 *  for C++ we decided to omit the <em>com</em> and for C# we replaced the prefix *com*
 *  with *cs*.<br>
 *  This is for having classes with the same names existing in C++, C# and Java not collide
 *  within the Doxygen documentation system.
 */



/**
 *  This is the Java package for core utility classes developed by A-Worx GmbH, Germany,
 *  published under the <em>MIT License</em>.
 *
 *  The set of classes and things found within this namespace and its descendants is referred
 *  to as <em>AWorx Utility Classes</em>, <em>AWorx Library</em> or just <em>A-Worx</em>.
 *
 *  Besides Java, this library is available in C# and C++, with language specific differences.
 *  The design goals of the three are:
 *  - Be small, efficient and easy to understand
 *  - Keep C++, C# and Java versions similar and mimic functionality of core classes of all
 *    three languages whenever this is appropriate.
 *  - Do not reinvent the world: There are more comprehensive 'low level' libraries out
 *    there! However, for some reason, we have right to exist.
 */
package com.aworx.lib;

import com.aworx.lib.config.*;
import com.aworx.lib.enums.Case;
import com.aworx.lib.enums.Inclusion;
import com.aworx.lib.enums.LockMode;
import com.aworx.lib.strings.CString;
import com.aworx.lib.strings.NumberFormat;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.threads.SmartLock;
import com.aworx.lib.threads.ThreadLock;

/** ************************************************************************************************
 * This class is a 100% static placeholder for global methods and fields of
 * \ref com::aworx::lib "ALib".
 * Among the things implemented here are:
 * - Collecting information on the executed process and its environment.
 * - Initialization of several ALib components with methods #init and #terminationCleanUp.
 * - Thread sleep methods
 * - 'Pruneable' debug shortcuts to to methods of class
 *   \ref com::aworx::lib::Report "Report".
 **************************************************************************************************/
public final class ALIB
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
        /**
         * The version of ALib. The version number follows the scheme YYMM (2-digit year, 2-digit month)
         * of the initial release date.
         * Besides this version number, field #revision indicates if this is a revised version
         * of a former release.
         */
        public static final int         version                                               =1604;

        /**
         * The revision number of this release. Each ALib #version is initially released as
         * revision \e 0. Pure maintenance releases that do not change the interface of ALox
         * are holding the same #version but an increased number in this field.
         */
        public static final int         revision                                                 =0;


        /**
         *  This is the configuration singleton for ALib.
         *  In method #init(), this configuration is optionally filled with the default
         *  configuration plug-ins
         *  \ref com::aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         *  and
         *  \ref com::aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn".
         *  Further, custom plug-ins may be attached.
         *
         *  For more information, see namespace \ref com::aworx::lib::config.
         */
        public static  Configuration    config                    = new Configuration( true, null );

        /**
         * The name of the configuration category of configuration variables used by the AWorx
         * library.<br>
         * Defaults to "ALIB".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #init.
         */
        public  static String           configCategoryName                                 ="ALIB";

        /**
         * This is a general mutex that is used by ALib internally but also may be used from outside
         * for different purposes. It is non-recursive and supposed to be used seldom and 'shortly',
         * e.g. for one-time initialization tasks. In case of doubt, a separated, problem-specific
         * mutex should be created.
         */
        public static    ThreadLock     lock                 =new ThreadLock(LockMode.SINGLE_LOCKS);

        /**
         * This is a smart mutex that allows to lock an applications' <em>standard output
         * streams</em>.
         *
         * In multi-threaded processes, to protect the output streams from concurrent access,
         * this smart lock might be used by any \e entity that writes data to the streams.
         * Before it can be used (acquired and released), it is needed to register with the object
         * using
         * \ref com::aworx::lib::threads::SmartLock::addAcquirer "SmartLock.addAcquirer".
         * This has to be done once per thread that aims to write to the stream. Then, prior to
         * writing, this object has to be acquired and after writing released.
         *
         * Because often, the standard \e output stream and standard \e error stream are identical,
         * ALib provides one single lock for both, to protect also against interwoven
         * standard output and error information.
         *
         * If the 'entity' that is registering is not of type
         * \ref com::aworx::lib::threads::ThreadLock "ThreadLock" it is allowed to provide \c null
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
         *   parallel use, e.g. 'std::cout', should register at bootstrap and \e acquire this
         *   instance prior to writing. This way, log output and other application output is
         *   not mixed, but separated in different Lines.
         */
        public static     SmartLock              stdOutputStreamsLock             = new SmartLock();

    // #############################################################################################
    // Init/TerminationCleanUp()
    // #############################################################################################

        /**  State of initialization, used to avoid double initialization.   */
        protected static      boolean   isInitialized= false;

        /** ****************************************************************************************
         * This method must (may) be called prior to using the AWorx library, e.g. at the beginning of
         * the main() method of an application. It is OK, to call this method more than once, which
         * allows independent code blocks (e.g. libraries) to bootstrap ALIB without interfering.
         *
         * In the C# version of the AWorx library, the invocation of this method is optional.
         * However, it is good practice to invoke this method in the main() method of a process
         * and provide the command line arguments. If no invocation is performed, no
         * configuration plug-ins are set.
         *
         * If the configuration should <em>not</em> take
         * command line  arguments and/or environment variables into account, then the parameters
         * can be set accordingly. If other, custom configuration data sources should be used
         * already with this method (however, in the current implementation, no configuration variable
         * are read), then such plug-in(s)
         * have to be added to public, static field #config prior to invoking this method.
         * In other words, currently it is irrelevant whether custom plug-ins are added prior
         * or after invoking this method. But in future versions this may change and in other
         * language versions of ALib, some variables are read. Therefore, it is good practice
         * to add custom plug-ins prior to invoking this method.
         *
         *  @param useEnv  If true, a
         *                 \ref com::aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         *                 is attached to the
         *                 \ref com::aworx::lib::ALIB::config "ALIB.config" singleton. Hence,
         *                 environment variables are read and potentially overwrite
         *                 configuration variables in other configuration plug-ins.
         *  @param args    Parameter which in the standard case is taken from  C/C++ main()
         *                 method providing the command line arguments.
         *                 If arguments are provided, a
         *                 \ref com::aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn"
         *                 is attached to the
         *                 \ref com::aworx::lib::ALIB::config "ALIB.config" singleton. Hence,
         *                 command line options are read and those potentially overwrite
         *                 configuration variables in other configuration plug-ins.
         ******************************************************************************************/
        synchronized
        public static void     init(  boolean useEnv, String[] args )
        {
            if ( isInitialized )
                return;
            isInitialized= true;

            // set the system's locale as the default for our static default number format
            NumberFormat.global.setFromLocale();

            synchronized (config)
            {
                // remove or insert environment plug-in
                if ( useEnv && config.envCP == null )
                {
                    config.envCP= new EnvironmentPlugIn();
                    config.insertPlugin( config.envCP,    Configuration.PRIO_ENV_VARS );
                }

                if ( !useEnv && config.envCP != null )
                {
                    config.removePlugin( config.envCP );
                    config.envCP= null;
                }

                // insert command line plug-in
                boolean useArgs= ( args != null && args.length > 0 );
                if ( useArgs && config.cmdLineCP == null )
                {
                    config.cmdLineCP= new CommandLinePlugIn ( args );
                    config.insertPlugin( config.cmdLineCP, Configuration.PRIO_CMD_LINE );
                }
            }
        }

        /** ****************************************************************************************
         * Got nothing to do in Java.
         ******************************************************************************************/
        public static void     terminationCleanUp()
        {
        }

    // #############################################################################################
    // ReportWriter debug interface
    // #############################################################################################

        /** ****************************************************************************************
         * Invokes
         * \ref com::aworx::lib::Report::doReport "Report.doReport".
         * This method is pruned from release code.
         *
         * @param type  The msg type.
         * @param msg  The msg to be passed to the \ref com::aworx::lib::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void REPORT( int type, String msg )
        {
            Report.getDefault().doReport( type, msg );
        }

        /** ****************************************************************************************
         * Invokes
         * \ref com::aworx::lib::Report::doReport "Report.doReport".
         * This method is pruned from release code.
         *
         *  @param msg  The msg to be passed to the \ref com::aworx::lib::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void ERROR( String msg )
        {
            Report.getDefault().doReport( 0, msg );
        }

        /** ****************************************************************************************
         * Invokes
         * \ref com::aworx::lib::Report::doReport "Report.doReport".
         * This method is pruned from release code.
         *
         *  @param msg  The msg to be passed to the
         *              \ref com::aworx::lib::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void WARNING( String msg )
        {
            Report.getDefault().doReport( 1, msg );
        }

        /** ****************************************************************************************
         * If given condition is false, method
         * \ref com::aworx::lib::Report::doReport "Report.doReport" gets invoked with the standard message
         * "Internal Error".
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref com::aworx::lib::ReportWriter "ReportWriter" call.
         ******************************************************************************************/
        public static void ASSERT( boolean cond )
        {
            if ( !cond )
                Report.getDefault().doReport( 0, "Internal Error" );
        }


        /** ****************************************************************************************
         * If given condition is false, method
         * \ref com::aworx::lib::Report::doReport "Report.doReport" gets invoked with the given message.
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref com::aworx::lib::ReportWriter "ReportWriter" call.
         * @param msg  The msg to be passed to the \ref com::aworx::lib::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void ASSERT_ERROR( boolean cond, String msg )
        {
            if ( !cond )
                Report.getDefault().doReport( 0, msg );
        }

        /** ****************************************************************************************
         * If given condition is false, method
         * \ref com::aworx::lib::Report::doReport "Report.doReport" gets invoked with the given message.
         * This method is pruned from release code.
         *
         * @param cond The condition that has to be met to prevent
         *             \ref com::aworx::lib::ReportWriter "ReportWriter" call.
         * @param msg  The msg to be passed to the \ref com::aworx::lib::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void ASSERT_WARNING( boolean cond, String msg )
        {
            if ( !cond )
                Report.getDefault().doReport( 1, msg );
        }

    // #############################################################################################
    // System info
    // #############################################################################################

        /** ****************************************************************************************
         * Detects if this is an Android application.
         * This, in the current implementation is done by looking for class
         *
         * @return \c true if the calling process is running on Android
         ******************************************************************************************/
        public static boolean sysInfo_IsAndroid()
        {
            try
            {
                Class.forName("android.app.Activity");
                return true;
            }
            catch (ClassNotFoundException e) {}
            return false;
        }


    // #############################################################################################
    // Other static interface methods
    // #############################################################################################

        /** ****************************************************************************************
         * Sleeps for the given nmber of milliseconds.
         * Variants of this method are #sleepMicros and #sleepNanos.
         *
         * @param millisecs Sleep time in milliseconds.
         ******************************************************************************************/
        public  static void sleepMillis( int millisecs )
        {
            sleepNanos ( millisecs * 1000000L );
        }

        /** ****************************************************************************************
         * Sleeps for the given nmber of microseconds.
         * Variants of this method are #sleepMillis and #sleepNanos.
         * @param microsecs Sleep time in microseconds.
         ******************************************************************************************/
        public  static void sleepMicros( long microsecs )
        {
            sleepNanos ( microsecs * 1000L );
        }

        /** ****************************************************************************************
         * Sleeps for the given nmber of nanoseconds.
         * Variants of this method are #sleepMillis and #sleepNanos.
         *
         * @param nanosecs Sleep time in nanoseconds.
         ******************************************************************************************/
        public  static void sleepNanos( long nanosecs )
        {
            long time=          System.nanoTime();
            long targetTime=    time + nanosecs;
            do
            {
                long sleepTime=  targetTime-time;
                if (sleepTime <= 0 )
                    break;

                long millisecs= sleepTime / 1000000L;
                int  nanos=     (int) ( sleepTime % 1000000L );

                try { Thread.sleep( millisecs, nanos ); } catch( InterruptedException e ) {}
                time=  System.nanoTime();
            }
            while( time < targetTime );
        }

        // #########################################################################################
        // Methods to 'parse' ALib enum values from strings.
        // #########################################################################################

        /** Strings used to identify a boolean value from a string representation */
         private static char[]  trueValuesBoolean= { 't', '1', 'y' };

        /** ****************************************************************************************
         * Interprets given \p src as a boolean value.
         * \ref com::aworx::lib::enums::Inclusion "enums.Inclusion".
         * If the case insensitive comparison of the first non-whitespace characters of the string with
         * with values "t", "1", "y", "on", "ok"
         * matches, \c true is returned.
         * Otherwise, including the case that \p src is 'nulled', \c false is returned.
         *
         * @param src The string to 'parse'.
         *
         * @returns The \b %Case value read.
         ******************************************************************************************/
        public static boolean   readBoolean( Substring src )
        {
            int idx= src.indexOfAny( CString.DEFAULT_WHITESPACES, Inclusion.EXCLUDE );
            if ( idx >= 0 )
            {
                char c=  Character.toLowerCase( src.charAt(idx) );
                for ( char v : trueValuesBoolean )
                    if ( c == v )
                        return true;

                char c2= Character.toLowerCase( src.charAt( idx + 1 ) );
                if ( c == 'o' &&  ( c2 == 'n' || c2 == 'k' ) )
                    return true;
            }
            return false;
        }

        /** Strings used to identify an enum \b Case from a string representation */
         private static char[]  trueValuesCase= { 's', 't', '1', 'y' };

        /** ****************************************************************************************
         * Interprets given \p src as a value of enum type
         * \ref com::aworx::lib::enums::Case "enums.Case".
         * If the case insensitive comparison of the first non-whitespace characters of the string
         * with values "s", "y", "t", "1"
         * matches, \b %Case.SENSITIVE is returned.
         * Otherwise, including the case that \p src is 'nulled', \b %Case.IGNORE is returned.
         *
         * @param src The string to 'parse'.
         *
         * @returns The \b %Case value read.
         ******************************************************************************************/
        public static Case      readCase( Substring src )
        {
            int idx= src.indexOfAny( CString.DEFAULT_WHITESPACES, Inclusion.EXCLUDE );
            if ( idx >= 0 )
            {
                int c= Character.toLowerCase( src.charAt(idx) );
                for ( char v : trueValuesCase )
                    if ( c == v )
                        return Case.SENSITIVE;
            }
            return Case.IGNORE;
        }

        /** Strings used to identify an enum \b Inclusion from a string representation */
        private static char[]   trueValuesInclusion= { 'i', 't', '1', 'y' };

        /** ****************************************************************************************
         * Interprets given \p src as a value of enum type
         * \ref com::aworx::lib::enums::Inclusion "enums.Inclusion".
         * If the case insensitive comparison of the first non-whitespace characters of the string
         * with values "i", "y", "t", "1"
         * matches, \b %Inclusion.INCLUDE is returned.
         * Otherwise, including the case that \p src is 'nulled', \b %Inclusion.EXCLUDE is returned.
         *
         * @param src The string to 'parse'.
         *
         * @returns The \b %Inclusion value read.
         ******************************************************************************************/
        public static Inclusion readInclusion( Substring src )
        {
            int idx= src.indexOfAny( CString.DEFAULT_WHITESPACES, Inclusion.EXCLUDE );
            if ( idx >= 0 )
            {
                int c= Character.toLowerCase( src.charAt(idx) );
                for ( char v : trueValuesInclusion )
                    if ( c == v )
                        return Inclusion.INCLUDE;
            }
            return Inclusion.EXCLUDE;
        }

}// class ALIB
