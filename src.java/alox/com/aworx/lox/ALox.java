// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

import java.util.ArrayList;

import com.aworx.lib.ALIB;
import com.aworx.lib.config.Configuration;
import com.aworx.lib.enums.Alignment;
import com.aworx.lib.enums.ContainerOp;
import com.aworx.lib.enums.Create;
import com.aworx.lib.enums.Inclusion;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lib.strings.Substring;

/** ************************************************************************************************
 * This is a 100% static class that holds constants and 'global' methods of the
 * ALox Logging Library.
 **************************************************************************************************/
public abstract class ALox
{
    // #############################################################################################
    // Static helpers
    // #############################################################################################

        /** ****************************************************************************************
         *  Provides a string representation of the Scope enums.
         *  @param scope        The enum value to retrieve a string representation for.
         *  @param packageLevel The package level.
         *  @param target       The target string.
         *  @returns A string representation of the provided Scope value.
         ******************************************************************************************/
        public static AString toString( Scope scope, int packageLevel, AString target )
        {
            target._("Scope.");
            switch( scope )
            {
                case GLOBAL:         { target._("GLOBAL");      break; }
                case THREAD_OUTER:   { target._("THREAD_OUTER");break; }
                case METHOD:         { target._("METHOD");      break; }
                case CLASS:          { target._("CLASS");       break; }
                case PACKAGE:        { target._("PACKAGE")._("(L" )._( packageLevel )._( ")" ); break; }
                case THREAD_INNER:   { target._("THREAD_INNER");break; }
            }
            return target;
        }

        /** ****************************************************************************************
         * Writes a string representation of the \e Verbosity and priority into the given
         * AString.
         *
         * @param verbosity The enum value to retrieve a string representation for.
         * @param priority  The priority of the \p verbosity setting.
         * @param target    The target to write into.
         * @returns \p target to allow concatenated calls.
         ******************************************************************************************/
        public static AString toString( Verbosity verbosity, int priority, AString target )
        {
            target.field()._( verbosity.toString() ).field( 8, Alignment.LEFT)
                  ._( '(' );

                 if ( priority ==           Lox.PRIO_SOURCE   )  target._( "SOURCE)   " );
            else if ( priority ==           Lox.PRIO_PROTECTED)  target._( "PROTECTED)" );
            else if ( priority == Configuration.PRIO_CMD_LINE )  target._( "CMD_LINE) " );
            else if ( priority == Configuration.PRIO_ENV_VARS )  target._( "ENV_VARS) " );
            else if ( priority == Configuration.PRIO_INI_FILE )  target._( "INI_FILE) " );
            else                                                 target._( priority)._( ')' );
            return target;
        }

        /** ****************************************************************************************
         * Interprets given \p src as a verbosity.
         * A case insensitive comparison of only the first (!) character of the start of the string
         * is performed (against 'v', 'i', 'w' and 'e').
         * If no match is found, \e %Verbosity::Off is returned.
         * @param src The string to 'parse'.
         * @returns The verbosity read.
         ******************************************************************************************/
        public static Verbosity readVerbosity( Substring src )
        {
            int idx= src.indexOfAny( CString.DEFAULT_WHITESPACES, Inclusion.EXCLUDE );
            if ( idx >= 0 )
            {
                char c= Character.toLowerCase( src.charAt(idx) );
                if ( c == 'v' ) return Verbosity.VERBOSE;
                if ( c == 'i' ) return Verbosity.INFO;
                if ( c == 'w' ) return Verbosity.WARNING;
                if ( c == 'e' ) return Verbosity.ERROR;
            }
            return Verbosity.OFF;
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
        public static final int         version                                               =1604;

        /**
         * The revision number of this release. Each ALox #version is initially released as
         * revision \e 0. Pure maintenance releases that do not change the interface of ALox
         * are holding the same #version but an increased number in this field.
         */
        public static final int         revision                                                 =2;

        /**
         * The name of the configuration category of configuration variables used by ALox.<br>
         * Defaults to "ALOX".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #init.<br>
         * See also \ref com::aworx::lib::ALIB::configCategoryName "ALIB.configCategoryName".
         */
        public  static String           configCategoryName                                  ="ALOX";

        /**
         * This is the path for logging to the internal domain. By manipulating this
         *  <em>Log Domains' Verbosity</em>, the verbosity of ALox itself can be controlled.
         * For example, with \e Verbosity.INFO, the 'on the fly' creation of <em>Log Domains</em>
         * are logged, which can be helpful to determine the <em>Log Domains</em> that are
         * created by libraries and larger projects.
         *
         * The following sub-domains are used by ALox:
         *
         *   Sub-Domain | Description
         *   - - - - - -| - - - - - - - - - - - - - - - - - - -
         *   LGR        | Used when \e %Loggers are registered, retrieved or removed from a \b %Lox and when the \e Verbosity of a <em>Log Domain</em> for a \e %Logger is changed.<br>In addition used with method \b %Lox.SetStartTime.
         *   DMN        | Used when <em>Log Domains</em> are registered (on first use), when <em>Scope Domains</em> are set or removed and when <em>Domain Substitution Rules</em> are set.
         *   PFX        | Used when <em>Prefix Logables</em> are set or removed.
         *   THR        | Used with method \b %Lox.MapThreadName.
         *   LGD        | Used with storing and retrieving <em>Log Data</em> objects.
         *
         * In addition, class
         * \ref com::aworx::lox::ALoxReportWriter "ALoxReportWriter" logs into sub-domain
         * <c>'REPORT'</c>.
         *
         * \note For internal logging an separated <em>domain tree</em> is used. This means, that
         *       setting the root domain of a \b %Lox to a certain \e Verbosity does \e not affect
         *       the internal domains. In other words, the \e Verbosity of the internal domain
         *       (or one of its sub-domains) has to be set explicitly.
         */
         public static final  String    INTERNAL_DOMAINS                                      ="$/";

    // #############################################################################################
    // Library initialization
    // #############################################################################################

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
         *                \ref com::aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn"
         *                is attached to the
         *                \ref com::aworx::lib::ALIB::config "ALIB.config" singleton. Hence,
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
    // Lox management
    // #############################################################################################

        /** The Lox objects registered with us. */
        private static ArrayList<Lox>    loxes                               = new ArrayList<Lox>();

        /** ****************************************************************************************
         * Returns the \b Lox with the given name.
         * A lox is only found if it was created and registered with ALox using #register.
         * If not found, and parameter \p create is \c true (the default), a new \b Lox is created,
         * registered and returned.
         *
         * @param name      The name of the \b %Lox to search and optionally to create.
         *                  Comparison is case insensitive.
         * @param create    Denotes whether a \b %Lox that was not found is created.
         *                  Optional and defaults to \b Create.NEVER.
         * @return The \b Lox found, \c null in case of failure.
         ******************************************************************************************/
        public static
        Lox      get( String name, Create create )
        {
            try { ALIB.lock.acquire();

                // search
                for( Lox it : loxes )
                    if( it.getName().equalsIgnoreCase( name ) )
                        return it;

                // create?
                if ( create == Create.IF_NOT_EXISTENT )
                {
                    Lox newLox= new Lox( name, false );
                    loxes.add( newLox );
                    return newLox;
                }

                // not found
                return null;

            } finally { ALIB.lock.release(); }
        }

        /** ****************************************************************************************
         * Overloaded version of #get providing value \c Create.ifNotExistent as default for
         * parameter \p create.
         *
         * @param name      The name of the \b %Lox to search and optionally to create.
         * @return The \b Lox found, \c null in case of failure.
         ******************************************************************************************/
        public static
        Lox      get( String name )
        {
            return get( name, Create.NEVER );
        }

        /** ****************************************************************************************
         * Registers or un-registers a \b %Lox object statically with ALox.
         * Once registered,  any code entity of the same process is enabled to retrieve
         * the \b %Lox using #get.<br>
         * No two objects with the same name must be registered. If this is done, the latter
         * will not be registered and not be found by #get. In debug-compilations, an ALib
         * error report is written (by default raises 'assert') if a name is registered twice.<br>
         * Note that name comparisson is performed case <b>in</b>-sensitive.
         *
         * If debug-logging is enabled (depends on compilation symbols) and used, the singleton
         * of type \% Lox provided for debug-logging is registered. This uses the name \c "Log"
         *
         * Registration is \e not mandatory but done by default by the constructor of class \b %Lox.
         * Therefore, to keep a \b Lox private, an optional parameter is available.
         *
         * @param lox       The \b %Lox to register.
         * @param operation If \b %ContainerOp.REMOVE, the given \p Lox is unregistered.
         *                  Defaults to \b %ContainerOp.INSERT.
         ******************************************************************************************/
        public static
        void     register( Lox lox, ContainerOp operation )
        {
            try { ALIB.lock.acquire();

                // check
                if ( lox == null )
                {
                    ALIB.ERROR( "null given" );
                    return;
                }

                // remove
                if( operation == ContainerOp.REMOVE )
                {
                    if ( !loxes.remove( lox ) )
                    {
                        ALIB.WARNING(  "A lox named \"" + lox.getName()
                                    + "\" could not be found for removal." );
                    }
                }

                // insert
                else
                {
                    for( Lox it : loxes )
                        if( it.getName().equals( lox.getName() ) )
                        {
                            ALIB.ERROR(   "A lox named \"" + lox.getName()
                                        + "\" was already registered. Registration ignored" );
                            return;
                        }

                    loxes.add( lox );
                }

            } finally { ALIB.lock.release(); }
        }

        /** ****************************************************************************************
         * Resets this object. Concretely the following steps are performed:
         * - All \b %Lox objects are removed.
         * - If the debug lox singleton exists, it is deleted.
         *
         * \attention
         *   This method was introduced to support resetting ALox in the unit tests.
         *   In real applications, this method should NOT be used.
         *   Side effects might appear using this method and it is not tested otherwise than
         *   used in tests!
         ******************************************************************************************/
        public static
        void     reset()
        {
            loxes.clear();
            if( Log.LOX != null )
                loxes.add( Log.LOX );
            Log.reset();
        }

}
