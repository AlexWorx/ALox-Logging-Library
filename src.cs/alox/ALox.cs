// #################################################################################################
//  cs.aworx.lox - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System.Diagnostics;
using System.Runtime.CompilerServices;
using System;
using cs.aworx.lib;
using cs.aworx.lox.core;
using cs.aworx.lox.loggers;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;
using System.Threading;
using System.Collections.Generic;
using cs.aworx.lib.config;
using cs.aworx.lib.threads;

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
         * Writes a string representation of the priority value into the given AString.
         *
         * @param priority  The priority of the \p verbosity setting.
         * @param target    The target to write into.
         * @returns \p target to allow concatenated calls.
         ******************************************************************************************/
        public static AString ToStringPriority( int priority, AString target )
        {
            if ( priority == Configuration.PrioDefault   )  return target._( "Default  " );
            if ( priority == Configuration.PrioProtected )  return target._( "Protected" );
            if ( priority == Configuration.PrioCmdLine   )  return target._( "CmdLine  " );
            if ( priority == Configuration.PrioEnvironment   )  return target._( "EnvVars  " );
            if ( priority == Configuration.PrioIniFile   )  return target._( "IniFile  " );

            return target.Field()._( priority ).Field( 9, Alignment.Left );
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
            return ToStringPriority( priority, target )
                   .InsertAt( ")", target.LastIndexOfAny( CString.DefaultWhitespaces, Inclusion.Exclude )  + 1 );
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
        public static readonly int                   Version                                  =1709;

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
        public  static         AString               ConfigCategoryName      = new AString("ALOX" );

        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::Lox::CreateConsoleLogger "Lox.CreateConsoleLogger".
         */
        public static          VariableDefinition           CONSOLE_TYPE = new VariableDefinition(
            ConfigCategoryName,   null,             "CONSOLE_TYPE",
            "default",
            '\0', null, Variable.FormatHint.None,
            "Influences the type of console logger to be created by method\n"         +
            "Lox.CreateConsoleLogger which is also used by Log.AddDebugLogger\n"    +
            "Possible values are: default, plain, ansi, windows, noqtcreator"
            );

        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::Log::AddDebugLogger "Log.AddDebugLogger".
         */
        public static          VariableDefinition           NO_IDE_LOGGER = new VariableDefinition(
            ConfigCategoryName,   null,     "NO_IDE_LOGGER",

            "false",
            '\0', null, Variable.FormatHint.None,
             "If true, the creation of an additional, ide-specific debug logger is suppressed." +
             "(In particular suppresses CLRDebugLogger (C#) and VStudioLogger (C++))"
        );

        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::core::textlogger::TextLogger "TextLogger".
         */
        public static          VariableDefinition           AUTO_SIZES = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_AUTO_SIZES",
            null,
            '\0', null, Variable.FormatHint.None,
            "Auto size values of last run of Logger '%1' (generated and temporary values)."
        );

        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::core::textlogger::TextLogger "TextLogger".
         */
        public static          VariableDefinition           MAX_ELAPSED_TIME = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_MAX_ELAPSED_TIME",
            "0, limit=59",
            ',', null, Variable.FormatHint.None,
            "Maximum elapsed time of all runs of Logger '%1'. To reset elapsed time display\n" +
            "width, set this to 0 manually. Generated and temporary value.)"
        );



        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::Lox "Lox".
         */
        public static          VariableDefinition           DOMAIN_SUBSTITUTION = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_DOMAIN_SUBSTITUTION",
            null,
            ';', "->", Variable.FormatHint.MultLine,
            ""
        );


        /**
         * Attributes of corresponding configuration variable
         * [ALOX_LOXNAME_LOGGERNAME_VERBOSITY](../group__GrpALoxConfigVars.html).
         */
        public static          VariableDefinition           VERBOSITY = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_%2_VERBOSITY",
            "writeback;",
            ';', "=", Variable.FormatHint.MultLine,
            "The verbosities of logger \"%2\" in lox \"%1\". Use 'writeback [VAR_NAME] ;'\n" +
            "to enable automatic writing on application exit."
        );


        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::Lox "Lox".
         */
        public static          VariableDefinition           PREFIXES = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_PREFIXES",
            "",
            ';', "=", Variable.FormatHint.MultLine,
            "Prefix strings for log domains of lox \"%1\".\n"                           +
            "   Format: [*]domainpath[*] = prefixstring [, inclusion] [ ; … ] "
        );


        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::Lox "Lox".
         */
        public static          VariableDefinition           DUMP_STATE_ON_EXIT = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_DUMP_STATE_ON_EXIT",
            "none, verbosity=info, domain=/ALOX",
            ',', null, Variable.FormatHint.None,
            "Log information about lox \"%1\" on exit. Comma separated list of arguments define\n"    +
            "verbosity, domain and content of output. Possible values content arguments are:\n"       +
            "  All, Basic, Version, SPTR, Loggers, Domains, InternalDomains\n"   +
            "  ScopeDomains, DSR, PrefixLogablesOnce, LogData, ThreadMappings,\n"   +
            "  CompilationFlags. If NONE is given nothing is dumped."
        );


        /**
         * Attributes of corresponding configuration variable
         * [ALOX_GLOBAL_SOURCE_PATH_TRIM_RULES](../group__GrpALoxConfigVars.html).
         */
        public static          VariableDefinition           SPTR_GLOBAL = new VariableDefinition(
            ConfigCategoryName,   null,     "GLOBAL_SOURCE_PATH_TRIM_RULES",
            "",
            ';', "=", Variable.FormatHint.MultLine,
             "Defines global source path trim rules (applicable for all Lox instances).\n"   +
             "   Format: [*]sourcepath [, inclusion, trimoffset, sensitivity, replacement] [ ; … ]"
        );


        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::Lox "Lox".
         */
        public static          VariableDefinition           SPTR_LOX = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_SOURCE_PATH_TRIM_RULES",

            "",

            ';', "=", Variable.FormatHint.MultLine,
             "Defines global source path trim rules for Lox \"%1\".\n"           +
             "   Format: [*]sourcepath [, inclusion, trimoffset, sensitivity, replacement] [ ; … ]"
        );

        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by colorful specializations of class
         * \ref cs::aworx::lox::core::textlogger::TextLogger "TextLogger".
         */
        public static          VariableDefinition           CONSOLE_LIGHT_COLORS = new VariableDefinition(
            ConfigCategoryName,   null,     "CONSOLE_LIGHT_COLORS",
            "",
            '\0', null, Variable.FormatHint.None,
            "Evaluated by colorful loggers that dispose about light and dark colors. Those may\n"        +
            "adjust their foreground and background color accordingly. If not given, under Windows OS\n" +
            "the right value is detected. Otherwise the value defaults to \"foreground\". In some\n"     +
            "occasions, the (detected or set) runtime environment might also indicate a different\n"     +
            "default value. Possible values are 'foreground', 'background' and 'never'."
        );

        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::core::textlogger::TextLogger "TextLogger".
         */
        public static          VariableDefinition           FORMAT = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_FORMAT",

            null,

            ',', null, Variable.FormatHint.MultLine,
            "Meta info format of text logger \"%1\", including signatures for verbosity strings and\n"   +
            "an optional string added to the end of each log statement.\n"                               +
            "   Format: metaInfoFormat [, Error [, Warning [, Info [, Verbose [, MsgSuffix ]]]]]"
        );

        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::core::textlogger::TextLogger "TextLogger".
         */
        public static          VariableDefinition           FORMAT_DATE_TIME = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_FORMAT_DATE_TIME",

            null,

            ',', null, Variable.FormatHint.None,
             "Meta info date and time format of text logger \"%1\".\n"              +
             "   Format: DateFormat [, TimeOfDayFormat [, TimeElapsedDays ]]]"
        );

        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::core::textlogger::TextLogger "TextLogger".
         */
        public static          VariableDefinition           FORMAT_TIME_DIFF = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_FORMAT_TIME_DIFF",

            null,

            ',', null, Variable.FormatHint.None,
             "Meta info time difference entities of text logger \"%1\".\n"                                        +
             "   Format: TimeDiffMinimum [, TimeDiffNone [, TimeDiffNanos [, TimeDiffMicros [, TimeDiffMillis \n" +
             "           [, TimeDiffSecs [, TimeDiffMins [, TimeDiffHours [,  TimeDiffDays  ]]]]]]]]"
        );

        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::core::textlogger::TextLogger "TextLogger".
         */
        public static          VariableDefinition           FORMAT_MULTILINE = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_FORMAT_MULTILINE",

            null,

            ',', null, Variable.FormatHint.None,
             "Multi-line format of text logger \"%1\".\n"                                                           +
             "   Format: MultiLineMsgMode [, FmtMultiLineMsgHeadline [, FmtMultiLinePrefix [, FmtMultiLineSuffix\n" +
             "           [, MultiLineDelimiter [, MultiLineDelimiterRepl ]]]]]"
        );

        /**
         * Attributes of corresponding [configuration variable](../group__GrpALoxConfigVars.html)
         * used by \ref cs::aworx::lox::core::textlogger::TextLogger "TextLogger".
         */
        public static          VariableDefinition           REPLACEMENTS     = new VariableDefinition(
            ConfigCategoryName,   null,     "%1_REPLACEMENTS",

            null,

            ',', null, Variable.FormatHint.None,
            "Pairs of search and replacement strings for text logger \"%1\".\n"  +
            "   Format: search, replacement [, search, replacement] [,...]"
        );


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
         * This method must be called prior to using %ALox, e.g. at the beginning of
         * the \c main() method of an application. It is OK, to call this method more than once, which
         * allows independent code blocks (e.g. libraries) to bootstrap %ALox independently.
         * However, only the first invocation is effective with the exclamation that if
         * command line parameters are provided with a call, those are set.
         * Also, the very first invocation should not be interrupted by a parallel invocation of a
         * second thread. Consequently, it has to be assured that this method is invoked once on
         * the real bootstrap an app.
         *
         * In the C# version of the ALox Logging Library, not invoking this method will not lead to
         * severe problems, however, some options might fail.
         * It is good practice to invoke this method in the main() method of a process
         * and provide the command line arguments.
         *
         * See also \ref cs::aworx::lib::ALIB::Init "ALIB.Init" which is invoked by this method.
         *
         * @param args    Parameters taken from <em>standard C#</em> method \c main()
         *                (the list of command line arguments).
         *                Defaults to null.
         ******************************************************************************************/
        public static void     Init(  String[] args= null )
        {
            if ( isInitialized )
                return;
            isInitialized= true;

            // initialize ALIB
            ALIB.Init( args );
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
         *                  Comparison is case insensitive.
         * @param create    Denotes whether a \b %Lox that was not found is created.
         *                  Optional and defaults to \b %Create.Never.
         * @return The \b Lox found, \c null in case of failure.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public static
        Lox      Get( String name, Create create= Create.Never )
        {
            // search
            name= name.ToUpper();
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
        }

        /** ****************************************************************************************
         * Registers or un-registers a \b %Lox object statically with ALox.
         * Once registered,  any code entity of the same process is enabled to retrieve
         * the \b %Lox using #Get.<br>
         * No two objects with the same name must be registered. If this is done, the latter
         * will not be registered and not be found by #Get. In debug-compilations, an ALib
         * error report is written (by default raises 'assert') if a name is registered twice.<br>
         * Note that name comparison is performed case <b>in</b>-sensitive.
         *
         * If debug-logging is enabled (depends on compilation symbols) and used, the singleton
         * of type \% Lox provided for debug-logging is registered. This uses the name \c "Log"
         *
         * Registration is \e not mandatory but done by default by the constructor of class \b %Lox.
         * Therefore, to keep a \b Lox private, an optional parameter is available.
         *
         * @param lox       The \b %Lox to register.
         * @param operation If \b %ContainerOp.Remove, the given \p Lox is deregistered.
         *                  Defaults to \b %ContainerOp.Insert.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public static
        void     Register( Lox lox, ContainerOp operation )
        {
            // check
            if ( lox == null )
            {
                ALIB_DBG.ERROR( "null given" );
                return;
            }

            // remove
            if( operation == ContainerOp.Remove )
            {
                if ( !loxes.Remove( lox ) )
                {
                    ALIB_DBG.WARNING(  "A lox named \"" + lox.GetName()
                                + "\" could not be found for removal." );
                }
            }

            // insert
            else
            {
                foreach( Lox it in loxes )
                    if( it.GetName().Equals( lox.GetName( ) ) )
                    {
                        ALIB_DBG.ERROR(   "A lox named \"" + lox.GetName()
                                    + "\" was already registered. Registration ignored" );
                        return;
                    }
                loxes.Add( lox );
            }
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
    public ALoxReportWriter ( Lox lox )
    {
        this.lox= lox;
        lox.Entry( ALoxReportWriter.LogDomain(), Verbosity.Verbose,  new Object[] {"ALoxReportWriter set"} );
    }

    /** ****************************************************************************************
     * Notify activation/deactivation
     * @param phase     Information if activated or deactivated.
     ******************************************************************************************/
    public virtual void NotifyActivation( Phase phase )
    {
    }

    /** ************************************************************************************
     * Log an ALib report using ALox.
     * @param msg  The message to report.
     **************************************************************************************/
    public void Report  (Report.Message msg)
    {
        lox.Entry( ALoxReportWriter.LogDomain(),
                        msg.Type == 0 ? Verbosity.Error
                   :    msg.Type == 1 ? Verbosity.Warning
                   :    msg.Type == 2 ? Verbosity.Info
                   :                    Verbosity.Verbose,
                   msg.Contents,
                   msg.Line, msg.File, msg.Func );
    }

    /** ********************************************************************************************
     * Returns the domain used to write reports.
     * @return The report log domain.
     **********************************************************************************************/
     public static String LogDomain()
     {
        return ALox.InternalDomains + "REPORT";
     }
}


} // namespace
