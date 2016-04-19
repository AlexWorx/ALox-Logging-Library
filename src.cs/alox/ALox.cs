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
using System.Collections.Generic;
using cs.aworx.lib.config;

namespace cs.aworx.lox {

// #################################################################################################
// Public enums, constants and helper classes for ALox
// #################################################################################################

/** ************************************************************************************************
 * This is a 100% static class that holds constants and 'global' methods of the
 * ALox Logging Library.
***************************************************************************************************/
public static class ALox
{
    // #############################################################################################
    // static helpers
    // #############################################################################################

        /** ****************************************************************************************
         * Provides a string representation of the Scope enums.
         *
         * @param scope        The enum value to retrieve a string representation for.
         * @param pathLevel    The path level.
         * @param target       The target string.
         * @returns A string representation of the provided Scope value.
         ******************************************************************************************/
        public static AString ToString( Scope scope, int pathLevel, AString target )
        {
            target._( "Scope." );
            switch( scope )
            {
                case Scope.Global:      { target._("Global");     break; }
                case Scope.ThreadOuter: { target._("ThreadOuter");break; }
                case Scope.Path:        { target._("Path")._("(L" )._( pathLevel )._( ")" ); break; }
                case Scope.Filename:    { target._("Filename");   break; }
                case Scope.Method:      { target._("Method");     break; }
                case Scope.ThreadInner: { target._("ThreadInner");break; }
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
        public static AString ToString( Verbosity verbosity, int priority, AString target )
        {
            target.Field()._( verbosity.ToString() ).Field( 8, Alignment.Left)
                  ._( '(' );

                 if ( priority ==           Lox.PrioSource    )  target._( "Source)   " );
            else if ( priority ==           Lox.PrioProtected )  target._( "Protected)" );
            else if ( priority == Configuration.PrioCmdLine   )  target._( "CmdLine)  " );
            else if ( priority == Configuration.PrioEnvVars   )  target._( "EnvVars)  " );
            else if ( priority == Configuration.PrioIniFile   )  target._( "IniFile)  " );
            else                                                 target._( priority )._( ')' );

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
        public static Verbosity ReadVerbosity( Substring src )
        {
            int idx= src.IndexOfAny( CString.DefaultWhitespaces, Inclusion.Exclude );
            if ( idx >= 0 )
            {
                char c= Char.ToLower( src.CharAt(idx) );
                if ( c == 'v' ) return Verbosity.Verbose;
                if ( c == 'i' ) return Verbosity.Info;
                if ( c == 'w' ) return Verbosity.Warning;
                if ( c == 'e' ) return Verbosity.Error;
            }
            return Verbosity.Off;
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
        public static readonly int                   Version                                  =1604;

        /**
         * The revision number of this release. Each ALox #Version is initially released as
         * revision \e 0. Pure maintenance releases that do not change the interface of ALox
         * are holding the same #Version but an increased number in this field.
         */
        public static readonly int                   Revision                                    =0;

        /**
         * The name of the configuration category of configuration variables used by ALox.<br>
         * Defaults to "ALOX".<br>
         * This value can be changed to avoid conflicts between applications (especially in
         * respect to environment variable settings). Changes should be placed at very initial
         * bootstrap code, before the invocation of #Init.<br>
         * See also \ref cs::aworx::lib::ALIB::ConfigCategoryName "ALIB.ConfigCategoryName".
         */
        public  static         String                ConfigCategoryName                     ="ALOX";

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
         *   DMN        | Used when <em>Log Domains</em> are registered (on first use), when <em>Scope Domains</em> are set or removed and when <em>Domain Substitution</em>Rs are set.
         *   PFX        | Used when <em>Prefix Logables</em> are set or removed.
         *   THR        | Used with method \b %Lox.MapThreadName.
         *   LGD        | Used with storing and retrieving <em>Log Data</em> objects.
         *
         * In addition, class
         * \ref cs::aworx::lox::ALoxReportWriter "ALoxReportWriter" logs into sub-domain
         * <c>'REPORT'</c>.
         *
         * \note For internal logging an separated <em>domain tree</em> is used. This means, that
         *       setting the root domain of a \b %Lox to a certain \e Verbosity does \e not affect
         *       the internal domains. In other words, the \e Verbosity of the internal domain
         *       (or one of its sub-domains) has to be set explicitly.
         */
         public static readonly    String  InternalDomains                                   ="$/";


    // #############################################################################################
    // Library initialization
    // #############################################################################################
        /**  State of initialization, used to avoid double initialization.   */
        private static bool           isInitialized= false;

        /** ****************************************************************************************
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
         *                 \ref cs::aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
         *                 is attached to the
         *                 \ref cs::aworx::lib::ALIB::Config "ALIB.Config" singleton. Hence,
         *                 environment variables are read and potentially overwrite
         *                 configuration variables in other configuration plug-ins.<br>
         *                 Defaults to true.
         *  @param args    Parameter which in the standard case is taken from  C/C++ main()
         *                 method providing the command line arguments.
         *                 If arguments are provided, a
         *                 \ref cs::aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn"
         *                 is attached to the
         *                 \ref cs::aworx::lib::ALIB::Config "ALIB.Config" singleton. Hence,
         *                 command line options are read and those potentially overwrite
         *                 configuration variables in other configuration plug-ins.<br>
         *                 Defaults to null.
         ******************************************************************************************/
        public static void     Init(  bool useEnv= true, String[] args= null )
        {
            if ( isInitialized )
                return;
            isInitialized= true;

            // initialize ALIB
            ALIB.Init( useEnv, args );
        }

    // #############################################################################################
    // Lox management
    // #############################################################################################

        /** The Lox objects registered with us. */
        private static List<Lox>    loxes                                         = new List<Lox>();

        /** ****************************************************************************************
         * Returns the \b Lox with the given name.
         * A lox is only found if it was created and registered with ALox using #Register.
         * If not found, and parameter \p create is \c true (the default), a new \b Lox is created,
         * registered and returned.
         *
         * @param name      The name of the \b %Lox to search and optionally to create.
         * @param create    Denotes whether a \b %Lox that was not found is created.
         *                  Optional and defaults to Create::Never.
         * @return The \b Lox found, \c null in case of failure.
         ******************************************************************************************/
        public static
        Lox      Get( String name, Create create= Create.Never )
        {
            try { ALIB.Lock.Acquire();

                // search
                foreach( Lox it in loxes )
                    if( it.GetName().Equals( name ) )
                        return it;

                // create?
                if ( create == Create.IfNotExistent )
                {
                    Lox newLox= new Lox( name, false );
                    loxes.Add( newLox );
                    return newLox;
                }

                // not found
                return null;

            } finally { ALIB.Lock.Release(); }
        }

        /** ****************************************************************************************
         * Registers or un-registers a \b %Lox object statically with ALox.
         * Once registered,  any code entity of the same process is enabled to retrieve
         * the \b %Lox using #Get.<br>
         * No two objects with the same name must be registered. If this is done, the latter
         * will not be registered and not be found by #Get. In debug-compilations, an ALib
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
         * @param operation If \b %ContainerOp.Remove, the given \p Lox is unregistered.
         *                  Defaults to \b %ContainerOp.Insert.
         ******************************************************************************************/
        public static
        void     Register( Lox lox, ContainerOp operation )
        {
            try { ALIB.Lock.Acquire();

                // check
                if ( lox == null )
                {
                    ALIB.ERROR( "null given" );
                    return;
                }

                // remove
                if( operation == ContainerOp.Remove )
                {
                    if ( !loxes.Remove( lox ) )
                    {
                        ALIB.WARNING(  "A lox named \"" + lox.GetName()
                                    + "\" could not be found for removal." );
                    }
                }

                // insert
                else
                {
                    foreach( Lox it in loxes )
                        if( it.GetName().Equals( lox.GetName( ) ) )
                        {
                            ALIB.ERROR(   "A lox named \"" + lox.GetName()
                                        + "\" was already registered. Registration ignored" );
                            return;
                        }
                    loxes.Add( lox );
                }

            } finally { ALIB.Lock.Release(); }
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
        void     Reset()
        {
            loxes.Clear();
            #if ALOX_DBG_LOG
                if( Log.LOX != null )
                    loxes.Add( Log.LOX );
                Log.Reset();
            #endif
        }
}

// #########################################################################################
// ALox based AWorx lib ReportWriter
// #########################################################################################

/** ****************************************************************************************
 * The \b %ReportWriter for ALib when using ALox. An instance of this class is
 * created in method \ref cs::aworx::lox::Log::AddDebugLogger "Log.AddDebugLogger"
 * and registered with ALib.<br>
 * Uses internal domain <c>'$/REPORT'</c> for logging.
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

    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    public virtual void NotifyActivation( Phase phase )
    {
    }

    /** ************************************************************************************
     * Log an ALib report using ALox.
     * @param report  The error message.
     **************************************************************************************/
    public void Report  (Report.Message report)
    {
        lox.Entry( ALox.InternalDomains + "REPORT",
                        report.Type == 0 ? Verbosity.Error
                   :    report.Type == 1 ? Verbosity.Warning
                   :    report.Type == 2 ? Verbosity.Info
                   :                       Verbosity.Verbose,
                   report.Contents,
                   report.Line, report.File, report.Func );
    }
}


} // namespace
