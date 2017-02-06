// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################



/**
 * \namespace com.aworx
 * This is the outer Java package for all classes published by A-Worx GmbH, Germany. As far as we
 * have planned today, there is nothing inside this namespace but other namespaces.<p>
 * \note
 *   While the Java language strongly proposes to use the complete 'reverse domain' name
 *   and therefore Java code published by A-Worx GmbH resides in namespace <em>com.aworx</em>,
 *   for C++ we decided to omit the <em>com</em> and for C# we replaced the prefix *com*
 *   with *cs*.<br>
 *   This is for having classes with the same names existing in C++, C# and Java not collide
 *   within the [Doxygen](http://www.stack.nl/~dimitri/doxygen) documentation system.
 */



/**
 * This is the Java package for core utility classes developed by A-Worx GmbH, Germany,
 * published under <em>Boost Software License</em>.
 *
 * The set of classes and things found within this namespace and its descendants is referred
 * to as <em>AWorx Utility Classes</em>, <em>AWorx Library</em> or just <em>A-Worx</em>.
 *
 * Besides Java, this library is available in C# and C++, with language specific differences.
 * The design goals of the three are:
 * - Be small, efficient and easy to understand
 * - Keep C++, C# and Java versions similar and mimic functionality of core classes of all
 *   three languages whenever this is appropriate.
 */
package com.aworx.lib;

import com.aworx.lib.config.Configuration;
import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Inclusion;
import com.aworx.lib.lang.Report;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lib.strings.NumberFormat;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.threads.SmartLock;
import com.aworx.lib.time.Ticks;

/** ************************************************************************************************
 * This class is a 100% static placeholder for global methods and fields of
 * \ref com::aworx::lib "ALib".
 * Among the things implemented here are:
 * - Collecting information on the executed process and its environment.
 * - Initialization of several ALib components with methods #init and #terminationCleanUp.
 * - Thread sleep methods
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
        public static final int         version                                               =1702;

        /**
         * The revision number of this release. Each ALib #version is initially released as
         * revision \e 0. Pure maintenance releases that do not change the interface of ALox
         * are holding the same #version but an increased number in this field.
         */
        public static final int         revision                                                 =0;


        /**
         * The name of the configuration category of configuration variables used by the AWorx
         * library.<br>
         * Defaults to "ALIB".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #init.
         */
        public  static AString          configCategoryName                  = new AString( "ALIB" );

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
         * This method must be called prior to using ALib, e.g. at the beginning of
         * the \c main() method of an application. It is OK, to call this method more than once, which
         * allows independent code blocks (e.g. libraries) to bootstrap %ALIB independently.
         * However, only the first invocation is effective with the exclamation that if
         * command line parameters are provided with a call, those are set.
         * Also, the very first invocation should not be interrupted by a parallel invocation of a
         * second thread. Consequently, it has to be assured that this method is invoked once on
         * the real bootstrap an app.
         *
         * In the Java version of the AWorx Library (ALib), the invocation of this method is optional.
         * However, it is good practice to invoke this method in the main() method of a process
         * and provide the command line arguments. If no invocation is performed, no
         * configuration plug-ins are set.
         *
         * If other, custom configuration data sources should be used already with this method
         * (however, in the current Java implementation, no configuration variables are read),
         * then such plug-in(s) have to be added to public, static field
         * \ref com::aworx::lib::config::Configuration::Default "Configuration.Default" prior to
         * invoking this method.
         * In other words, currently it is irrelevant whether custom plug-ins are added prior
         * or after invoking this method. But in future versions this may change and in other
         * language versions of ALib, some variables are read. Therefore, it is good practice
         * to add custom plug-ins prior to invoking this method.
         *
         * @param args    Parameters taken from <em>standard Java</em> method \c main()
         *                (the list of command line arguments). Accepts \c null to ignore
         *                command line parameters.
         ******************************************************************************************/
        synchronized
        public static void     init( String[] args )
        {
            if ( isInitialized )
                return;
            isInitialized= true;

            // set the system's locale as the default for our static default number format
            NumberFormat.global.setFromLocale();
            NumberFormat.global.writeGroupChars= true;

            Configuration.Default.setCommandLineArgs( args );
        }

        /** ****************************************************************************************
         * Got nothing to do in Java.
         ******************************************************************************************/
        public static void     terminationCleanUp()
        {
            /* Got nothing to do in current Java version of ALib */
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
            catch (@SuppressWarnings ("unused") ClassNotFoundException e) { /* void */}
            return false;
        }


    // #############################################################################################
    // Other static interface methods
    // #############################################################################################

        /** ****************************************************************************************
         * Suspends the current thread for the given number of milliseconds.
         * Variants of this method are #sleepMillis, #sleepMicros and #sleepNanos.
         *
         * @param ticks Sleep time in \b %Ticks.
         ******************************************************************************************/
        public  static void sleep( Ticks ticks )
        {
            sleepNanos ( ticks.inNanos() );
        }

        /** ****************************************************************************************
         * Suspends the current thread for the given number of milliseconds.
         * Variants of this method are #sleep, #sleepMicros and #sleepNanos.
         *
         * @param millisecs Sleep time in milliseconds.
         ******************************************************************************************/
        public  static void sleepMillis( int millisecs )
        {
            sleepNanos ( millisecs * 1000000L );
        }

        /** ****************************************************************************************
         * Suspends the current thread for the given number of microseconds.
         * Variants of this method are #sleep, #sleepMillis and #sleepNanos.
         * @param microsecs Sleep time in microseconds.
         ******************************************************************************************/
        public  static void sleepMicros( long microsecs )
        {
            sleepNanos ( microsecs * 1000L );
        }

        /** ****************************************************************************************
         * Suspends the current thread for the given number of nanoseconds.
         * Variants of this method are #sleep, #sleepMillis and #sleepNanos.
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

                try { Thread.sleep( millisecs, nanos ); } catch( @SuppressWarnings ("unused") InterruptedException e ) {/* void */}
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
         * \ref com::aworx::lib::lang::Inclusion "enums.Inclusion".
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
         * \ref com::aworx::lib::lang::Case "enums.Case".
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
         * \ref com::aworx::lib::lang::Inclusion "enums.Inclusion".
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
