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
import com.aworx.lib.strings.NumberFormat;

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
        public static final int         version                                               =1602;

        /**
         * The revision number of this release. Each ALib #version is initially released as
         * revision \e 0. Pure maintenance releases that do not change the interface of ALox
         * are holding the same #version but an increased number in this field.
         */
        public static final int         revision                                                 =1;


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
         * In the Java version of the AWorx library, the invocation of this method is optional.
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
                    config.insertPlugin( config.envCP,    20 );
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
                    config.insertPlugin( config.cmdLineCP, 10 );
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
         *  Invokes
         *  \ref com::aworx::lib::Report::doReport "Report.doReport".
         *  This method is pruned from release code.
         *
         *  @param msg  The msg to be passed to the \ref aworx::lib::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void ERROR( String msg )
        {
            Report.getDefault().doReport( 0, msg );
        }

        /** ****************************************************************************************
         *  Invokes
         *  \ref aworx::lib::Report::doReport "Report.doReport".
         *  This method is pruned from release code.
         *
         *  @param msg  The msg to be passed to the
         *              \ref aworx::lib::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void WARNING( String msg )
        {
            Report.getDefault().doReport( 1, msg );
        }

        /** ****************************************************************************************
         *  If given condition is false, method
         *  \ref com::aworx::lib::Report::doReport "Report.doReport" gets invoked with the standard message
         *  "Internal Error".
         *  This method is pruned from release code.
         *
         *  @param cond The condition that has to be met to prevent
         *              \ref aworx::lib::ReportWriter "ReportWriter" call.
         ******************************************************************************************/
        public static void ASSERT( boolean cond )
        {
            if ( !cond )
                Report.getDefault().doReport( 0, "Internal Error" );
        }


        /** ****************************************************************************************
         *  If given condition is false, method
         *  \ref com::aworx::lib::Report::doReport "Report.doReport" gets invoked with the given message.
         *  This method is pruned from release code.
         *
         *  @param cond The condition that has to be met to prevent
         *              \ref aworx::lib::ReportWriter "ReportWriter" call.
         *  @param msg  The msg to be passed to the \ref aworx::lib::ReportWriter "ReportWriter".
         ******************************************************************************************/
        public static void ASSERT_ERROR( boolean cond, String msg )
        {
            if ( !cond )
                Report.getDefault().doReport( 0, msg );
        }

        /** ****************************************************************************************
         *  If given condition is false, method
         *  \ref aworx::lib::Report::doReport "Report.doReport" gets invoked with the given message.
         *  This method is pruned from release code.
         *
         *  @param cond The condition that has to be met to prevent
         *              \ref aworx::lib::ReportWriter "ReportWriter" call.
         *  @param msg  The msg to be passed to the \ref aworx::lib::ReportWriter "ReportWriter".
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

}// class ALIB
