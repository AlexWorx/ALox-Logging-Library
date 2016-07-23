// #################################################################################################
//  cs.aworx.lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System.Runtime.CompilerServices;
using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Globalization;
using System.Threading;
using cs.aworx.lib;
using cs.aworx.lib.enums;
using cs.aworx.lib.config;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lib.threads;
using cs.aworx.lox.core;
using cs.aworx.lox.loggers;
using cs.aworx.lox.core.textlogger;

/** ************************************************************************************************
 * This is the C++ namespace for code of the <em>%ALox Logging Library</em>.
 * Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace cs.aworx.lox {

/** ************************************************************************************************
 * This class acts as a container for Loggers and provides a convenient interface to logging.
 * Fore information how to use this class, checkout the ALox tutorials and the ALox manual.
 **************************************************************************************************/
public class Lox : ThreadLock
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

        #if ALOX_DBG_LOG || ALOX_REL_LOG

        /**
         * A counter for the quantity of calls. The count includes logs that were suppressed by
         * disabled <em>Log Domain</em> and those suppressed by the optional log condition parameter.
         */
        public    int                           CntLogCalls                                      =0;

        /**
         * Denotes if <em>Log Domains</em> are searched ignoring the letter case or being sensitive
         * about it.<br>
         * Defaults to \p Case::Ignore.
         */
        public    Case                          DomainSensitivity                      =Case.Ignore;


        /**
         * Denotes flags used with methods #GetState and #State to select different parts
         * of the state receive.
         */
        public enum StateInfo
        {

            Basic                    = 1 <<  0, ///< Name and number of log calls
            Version                  = 1 <<  1, ///< Library Version and thread safeness
            Loggers                  = 1 <<  2, ///< Loggers

            Domains                  = 1 <<  3, ///< Log domains currently registered
            InternalDomains          = 1 <<  4, ///< Internal domains
            ScopeDomains             = 1 <<  5, ///< Scope domains
            DSR                      = 1 <<  6, ///< Domain substitution rules
            PrefixLogables           = 1 <<  7, ///< Prefix logables
            Once                     = 1 <<  8, ///< Log once counters
            LogData                  = 1 <<  9, ///< Log data objects
            ThreadMappings           = 1 << 10, ///< Named threads

            SPTR                     = 1 << 20, ///< Source path trim rules

            All                      = ~0,
        };

    // #############################################################################################
    // Private/protected fields
    // #############################################################################################

        /** Information about the source code, method, thread, etc. invoking a log  call */
        protected ScopeInfo                     scopeInfo;

        /**
         * The root domain \"/\". All registered domains become a sub domain of this root.
         * If a <em>Sub-Log Domains' Verbosity</em> is not explicitly set, such sub domain inherits
         * the \e Verbosity of its parent.
         */
        protected Domain                        domains;

        /**
         * The root domain for internal <em>Log Domains</em>.
         */
        protected Domain                        internalDomains;

        /** Scope Domains .*/
        protected ScopeStore<AString>                       scopeDomains;

        /** Log Data */
        protected ScopeStore<Dictionary<AString, LogData>>  scopeLogData;

        /** Log once counters */
        protected ScopeStore<Dictionary<AString, int[]>>    scopeLogOnce;

        /** Prefix logables store */
        protected ScopeStore<Object>                        scopePrefixes;

        /** The resulting domain name. */
        protected AString                       resDomain                       = new AString( 32 );

        /** The resulting domain name for internal logs. */
        protected AString                       resDomainInternal               = new AString( 32 );

        /** An AString singleton. Can be acquired, using buf() */
        protected AString                       logBuf                         = new AString( 128 );

        /** A locker for the log buffer singleton */
        protected ThreadLock                    logBufLock                       = new ThreadLock();

        /** Used for tabular output of logger lists */
        protected int                           maxLoggerNameLength                             = 0;

        /** Used for tabular output of logger lists */
        protected int                           maxDomainPathLength                             = 0;

        /** Dictionary to translate thread ids into something maybe nicer/shorter.
         *  The dictionary has to be filled by the user of the library. */
        protected Dictionary<int, String>       threadDictionary =new Dictionary<int, String>();

        /** A key value used in stores if no key is given (global object).  */
        protected readonly String               noKeyHashKey                                  = "$";

        /** The list of collected log objects which is passed to the \e Loggers  */
        protected List<Object>                  logObjects                     = new List<Object>();

        /** A temporary AString, following the "create once and reuse" design pattern. */
        protected AString                       intMsg                         = new AString( 256 );

        /**  Flag used with configuration variable LOXNAME_DUMP_STATE_ON_EXIT.  */
        protected bool                          loggerAddedSinceLastDebugState               =false;

        /** A temporary AString  */
        protected AString                       tmpAS                           = new AString( 64 );

        /** A temporary AString  */
        protected AString                       tmpComments                    = new AString( 128 );

        /**  Domain substitution rules.  */
        public class DomainSubstitutionRule
        {
            /** Rule types */
            public enum  Type
            {
                Exact,       ///< Exact match
                StartsWith,  ///< Starts with match
                EndsWith,    ///< Ends with match
                Substring    ///< Any sub-string
            }

            public Type     type;                         ///< Denotes if path given started with '*' or not.
            public AString  Search       = new AString(); ///< The path to search.
            public AString  Replacement  = new AString(); ///< The replacement.



            /**  Constructor.
             * @param s The path to search.
             * @param r The replacement.
            */
            public DomainSubstitutionRule( String s, String r )
            {
                // get type and adjust given search parameter
                int startPos=   0;
                int length=     s.Length;
                if ( s[0] == '*' )
                {
                    startPos++;
                    length--;
                    if ( s[length] == '*' )
                    {
                        type= Type.Substring;
                        length--;
                    }
                    else
                        type= Type.EndsWith;
                }
                else
                {
                    if ( s[length-1] == '*' )
                    {
                        type= Type.StartsWith;
                        length--;
                    }
                    else
                        type= Type.Exact;
                }
                Search._( s, startPos, length );

                // minimum rule check
                if (   (     (    type == Type.Exact
                               || type == Type.StartsWith )
                         && !Search.StartsWith( "/" )
                        )
                    || (     type == Type.EndsWith
                         &&  Search.EndsWith( "/" )
                       )
                   )
                    Search._(); // illegal rule


                Replacement._(r);
            }
        };

        /**  The list of domain substitution rules.  */
        protected List<DomainSubstitutionRule> domainSubstitutions =new List<DomainSubstitutionRule>();

        /**  Flag if a warning on circular rule detection was logged.  */
        protected bool                          oneTimeWarningCircularDS                     =false;

        /**  Temporary string used with domain substitutions.  */
        protected AString                       tmpSubstitutionPath                =new AString(64);

        /**  Temporary string used with domain substitutions.  */
        protected AString                       tmpSubstitutionPathInternalDomains =new AString(64);

    #else
        public enum StateInfo 
        {
              All   = ~0
        }
    #endif //ALOX_DBG_LOG || ALOX_REL_LOG



    // #############################################################################################
    // Constructors
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs a new, empty Lox with the given \p name.
         * The name is immutable and all \b %Lox objects registered with ALox must be unique.
         * The name \c "Log" is reserved for the internal default singleton used for debug-logging.
         * In addition, name \c "GLOBAL" is not allowed.
         *
         * If parameter \p register is \c true (the default), static method
         * \ref cs::aworx::lox::ALox::Register "ALox.Register" is invoked and the object will be
         * retrievable with static method
         * \ref cs::aworx::lox::ALox::Get "ALox.Get". In some situations, such 'registration'
         * may not be wanted.
         * @param name       The name of the Lox. Will be converted to upper case.
         * @param doRegister If \c true, this object is registered with static class
         *                   \ref cs::aworx::lox::ALox "ALox".
         *                   Optional and defaults to \c true.
         ******************************************************************************************/
        public Lox( String name, bool doRegister = true )   : base()
        {
            // set recursion warning of log buffer lock to 1. Warnings are logged if recursively
            // acquired more than once
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                logBufLock.RecursionWarningThreshold= 1;

                scopeInfo=      new ScopeInfo( name, threadDictionary );
                scopeDomains=   new ScopeStore<AString                     >( scopeInfo, false );
                scopePrefixes=  new ScopeStore<Object                      >( scopeInfo, false );
                scopeLogData=   new ScopeStore<Dictionary<AString, LogData>>( scopeInfo, true  );
                scopeLogOnce=   new ScopeStore<Dictionary<AString, int[]>  >( scopeInfo, true  );


                // create domain trees
                domains          = new Domain( null, new AString( "") );
                internalDomains  = new Domain( null, new AString( ALox.InternalDomains,
                                                                  0, ALox.InternalDomains.Length - 1) );

                // create internal sub-domains
                bool wasCreated= false;
                String[] internalDomainList= {"LGR", "DMN", "PFX", "THR", "LGD", "VAR"  };
                foreach ( String it in internalDomainList )
                {
                    resDomainInternal._()._NC( it );
                    internalDomains.Find( resDomainInternal, Case.Sensitive, 1, ref wasCreated );
                }

                maxDomainPathLength= ALox.InternalDomains.Length + 3;

                // register with ALox
                if ( doRegister )
                    ALox.Register( this, ContainerOp.Insert );

                // read domain substitution rules from configuration
                Variable variable= new Variable( ALox.DOMAIN_SUBSTITUTION, GetName() );
                if ( variable.Load() != 0 )
                {
                    for( int ruleNo= 0; ruleNo< variable.Size(); ruleNo++ )
                    {
                        AString rule= variable.GetString( ruleNo );
                        int idx= rule.IndexOf( "->" );
                        if ( idx > 0 )
                        {
                            String domainPath=  rule.ToString( 0,  idx ).Trim();
                            String replacement= rule.ToString( idx + 2 ).Trim();
                            SetDomainSubstitutionRule( domainPath, replacement );
                        }
                        else
                        {
                            // using alib warning here as we can't do internal logging in the constructor
                            ALIB.WARNING( "Syntax error in variable \"" + variable.Fullname + "\"." );
                        }
                    }
                }
            #endif
        }

    // #############################################################################################
    // Interface
    // #############################################################################################

    /** ********************************************************************************************
     * Returns the name of this \b %Lox. The name user defined, provided in the constructor,
     * converted to upper case and otherwise immutable.
     *
     * @returns The name of this %Lox.
     **********************************************************************************************/
    public String    GetName()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            return scopeInfo.GetLoxName();
        #else
            return null;
        #endif
    }

    /** ********************************************************************************************
     * Status of registration with ALox. To keep a \b %Lox "private" using parameter
     * \p doRegister of the constructor, allows to suppress registration.
     * Registered instances of this class can be statically received (by their name) using
     * \ref cs::aworx::lox::ALox::Get "ALox.Get".
     *
     * @returns \c true if this instance was registered with ALox, \c false if not.
     **********************************************************************************************/
        public bool      IsRegistered()
        {
            #if ALOX_DBG_LOG || ALOX_REL_LOG
                return ALox.Get( GetName() ) == this;
            #else
                return false;
            #endif
        }


    /** ********************************************************************************************
     * Returns an AString singleton, that can be reused for all basic log calls. Textual messages
     * that are assembled from out of strings, numbers and other data, can be efficiently built
     * by reusing this singleton.
     * Whenever this method is called, the returned AString object gets "locked" by a corresponding
     * ThreadLock object. Therefore it has to be used as a message within one of the log methods of
     * this class
     * (error(), warning(), info(), verbose(), if(), once() or entry())
     * or it has to be
     * explicitly released using BufAbort().
     * If this is not done, the object does not get released and parallel threads using this
     * method would block! So, do not use Buf() for other reasons than for creating log messages
     * and be sure to release it "in time".
     *
     * @return The static AString singleton.
     **********************************************************************************************/
    public AString    Buf()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            logBufLock.Acquire();
            logBuf.Clear();
            return logBuf;
        #else
            return  null;
        #endif
    }

    /** ********************************************************************************************
     * Use this method when you want to abort a log call that you "started" with acquiring the
     * internal AString singleton acquired using method Buf(). Use BufAbort() only if you did
     * not use the acquired buffer as a parameter of a log method, because this internally
     * releases the buf already.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void        BufAbort()
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            logBufLock.Release();
        #endif
    }

    /** ****************************************************************************************
     * Adds \p path to an internal list of substrings that are used to trim the path of
     * a source file name. Trimmed paths are used for \e Scope mechanisms and can be
     * logged (e.g. with meta information of class \b TextLogger.
     *
     * By default such setting affects all instances of class \b Lox, not only
     * this instance. This can be altered using parameter \p global.
     * one other The given trim information can either
     *
     * If given \p path starts with character <c> '*'</c>, the rest of the string is searched
     * within source paths. Otherwise, it is checked if a source path starts with the given
     * path.
     *
     * Parameter \p includeString determines if the searched substring should be included in the
     * resulting source path or not. In addition, parameter \p trimOffset, which can be negative
     * or positive, is added to the position of trimming. This can be used to increase the
     * length of the search path, and then cut only a portion of what was searched for.
     *
     * Parameter \p trimReplacement optionally provides a replacement string for the trimmed
     * path. This can be used for example to provide the right absolute path for an IDE
     * to find source files of a library.
     *
     * Finally, parameter \p sensitivity determines whether the match is performed case
     * sensitive or not. It defaults to non-sensitive, for convenience and for the fact that
     * for example Microsoft C++ compilers' preprocessor passes lower case path-strings!
     *
     * \note
     *   If the platform (compiler) specific path separator is <c>'/'</c>, then characters
     *   <c>'\'</c> found in parameters \p path and \p trimReplacement are replaced by <c>'\'</c>
     *   and vice versa. This allows to specify paths and substrings thereof in a platform
     *   independent way.
     *
     * \attention
     *   Setting global rules (when parameter \p global equals \c Inclusion::Include) is not
     *   protected by a \c mutex against concurrent access. Therefore, global rules have
     *   to be either at bootstrap of a process, before threads are created, or such creation
     *   has to 'manually' be protected by locking all existing instances of this class!
     *
     * @param path            The path to search for. If not starting with <c> '*'</c>,
     *                        a prefix is searched.
     * @param includeString   Determines if \p path should be included in the trimmed
     *                        path or not.
     *                        Optional and defaults to \b %Inclusion.Exclude.
     * @param trimOffset      Adjusts the portion of \p path that is trimmed.
     *                        Optional and defaults to 0.
     * @param sensitivity     Determines if the comparison of \p path with a source
     *                        files' path is performed case sensitive or not.
     *                        Optional and defaults to \b Case.Ignore.
     * @param trimReplacement Replacement string for trimmed portion of the path.
     *                        Optional and defaults to \b %NullString.
     * @param reach           Denotes whether the rule is applied locally (to this \b %Lox only)
     *                        or applies to all instances of class \b %Lox.
     *                        Defaults to \b %Reach.Global.
     * @param priority        The priority of the setting. Defaults to
     *                        \ref cs::aworx::lib::config::Configuration::PrioDefault "Configuration.PrioDefault",
     *                        which is a lower priority than standard plug-ins of external
     *                        configuration have.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void      SetSourcePathTrimRule( String    path,
                                            Inclusion includeString     = Inclusion.Exclude,
                                            int       trimOffset        = 0,
                                            Case      sensitivity       = Case.Ignore,
                                            String    trimReplacement   = null,
                                            Reach     reach             = Reach.Global,
                                            int       priority          = Configuration.PrioDefault    )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();

            scopeInfo.SetSourcePathTrimRule( path, includeString, trimOffset, sensitivity,
                                             trimReplacement, reach, priority );

        } finally { Release(); }
        #endif
    }

    /** ****************************************************************************************
     * Removes all local trimming rules set with #SetSourcePathTrimRule.
     * If parameter \p global is set to \b Inclusion.Include, the global rules are cleared
     * in addition.
     *
     * Setting parameter \p allowAutoRule to \c false, allows to suppress the creation of an
     * automatic rule based on the executables path.
     *
     * \see ALox User Manual for more information.
     *
     * @param reach         Denotes whether only local rules are cleared or also global ones.
     *                      Defaults to \b %Reach.Global.
     * @param allowAutoRule Determines if an auto rule should be tried to be detected next
     *                      no appropriate rule is found.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void   ClearSourcePathTrimRules( Reach reach= Reach.Global, bool allowAutoRule= true )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();
            scopeInfo.SetSourcePathTrimRule( null, allowAutoRule ? Inclusion.Include
                                                                 : Inclusion.Exclude,
                                             999999, // code for clearing
                                             Case.Ignore, null,  reach, -1  );
        } finally { Release(); }
        #endif
    }


    /** ************************************************************************************
     * This method creates an adequate/default console logger. 'Adequate' here means that
     * this function tries to detect what might be the best choice for the environment
     * that the ALox based process is running in.
     * This method is due to changes with the evolution of future ALox versions and
     * should be considered as a convenience method to shorten the bootstrap code needed
     * to use ALox.
     *
     * The current C# implementation takes the following approach:
     *
     * - check if configuration variable
     *   [ALOX_CONSOLE_TYPE](../group__GrpALoxConfigVars.html) is set. This variable's
     *   setting takes priority and if set, the according logger is created.
     * - check whether a console window is attached to the current process.
     *   If not, then a plain text logger is chosen (class
     *   \ref cs::aworx::lox::loggers::ConsoleLogger "ConsoleLogger").
     * - Otherwise, on Unix like OS, class
     *   \ref cs::aworx::lox::loggers::AnsiConsoleLogger "AnsiConsoleLogger" is chosen,
     *   while on windows systems class
     *   \ref cs::aworx::lox::loggers::ColorConsoleLogger "ColorConsoleLogger"
     *   takes preference.
     *
     * For further information check out the source code.
     *
     * @param name (Optional) The name of the \e Logger.
     *             Defaults to null, which implies standard logger names defined
     *             in the \e Logger sub-classes.
     * @return The \b TextLogger chosen.
     **************************************************************************************/
    public static TextLogger CreateConsoleLogger( String name= null )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG

        //--- first: check environment "ALOX_DBG_CONSOLE_TYPE". They have precedence ---
        Variable variable= new Variable(ALox.CONSOLE_TYPE);
        variable.Load();
        AString val= variable.GetString().Trim();

        if (    val.IsEmpty()
             || val.Equals( "DEFAULT",  Case.Ignore )
             || val.Equals( "PLAIN",    Case.Ignore ) )   return new ConsoleLogger     ( name );
        if(     val.Equals( "ANSI",     Case.Ignore ) )   return new AnsiConsoleLogger ( name );
        if(     val.Equals( "WINDOWS",  Case.Ignore ) )   return new ColorConsoleLogger( name );

        ALIB.WARNING( "Unrecognized value in config variable \"" + variable.Fullname
                       + "\"= " + variable.GetString() );

        //--- second: check debug environment
        // .... this is not implemented in C#, yet ...

        // not detected: in windows, we choose ColorConsoleLogger, in Unix ANSI
        if( ALIB.SysInfo_HasConsoleWindow )
            return  ALIB.SysInfo_IsWindowsOS()  ? (TextLogger) new ColorConsoleLogger( name )
                                                : (TextLogger) new AnsiConsoleLogger ( name );
        // default
        return new ConsoleLogger( name );

        #else
            return null;
        #endif
    }


    /** ********************************************************************************************
     * Retrieves an instance of a Logger by its name. This might be useful when access to a
     * \e %Logger is needed to change its configuration.
     *
     * @param loggerName    The name of the \e Logger to search for (case insensitive).
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     * @return  The logger, null if not found.
     **********************************************************************************************/
    public  Logger GetLogger( String loggerName,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Acquire();

                // search logger
                Logger logger;
                if ( (logger= domains        .GetLogger( loggerName ) ) != null )    return logger;
                if ( (logger= internalDomains.GetLogger( loggerName ) ) != null )    return logger;

                // not found
                scopeInfo.Set( cln,csf,cmn, owner );

                logInternal( Verbosity.Warning, "LGR", intMsg._()
                    ._NC("No logger named \"")._NC( loggerName )._NC( "\" found.") );
                return null;

            } finally { Release(); }
        #else
            return  null;
        #endif
    }

    /** ****************************************************************************************
     * Helper method of #dumpStateOnLoggerRemoval to recursively collect domain settings.
     * @param domain    The actual domain.
     * @param loggerNo  The number of the logger
     * @param variable  The AString to collect the information.
     ******************************************************************************************/
    #if ALOX_DBG_LOG || ALOX_REL_LOG
    protected void verbositySettingToVariable( Domain domain, int loggerNo, Variable variable )
    {
        variable.AddString()._( domain.FullPath )
                            ._('=')
                            ._( domain.GetVerbosity( loggerNo ).ToString() );

        // loop over all sub domains (recursion)
        foreach( Domain subDomain in domain.SubDomains )
            verbositySettingToVariable( subDomain, loggerNo, variable );
    }


    /** ****************************************************************************************
     * Implements functionality for configuration variable \c LOXNAME_LOGGERNAME_VERBOSITY.
     * Is called when a logger is removed.
     * @param logger      The logger to write the verbosity for.
     ******************************************************************************************/
    protected void  writeVerbositiesOnLoggerRemoval( Logger logger )
    {
        // When writing back we will use this priority as the maximum to write. This way, if this was
        // an automatic default value, we will not write back into the user's variable store.
        // As always, only if the app fetches new variables on termination, this is entry is copied.
        Variable variable= new Variable( ALox.VERBOSITY, GetName(), logger.GetName() );
        variable.Load();

        // first token is "writeback" ?
        if ( variable.Size() == 0 )
            return;
        Substring firstArg= new Substring( variable.GetString() );
        if ( !firstArg.Consume( "writeback", Case.Ignore, Whitespaces.Trim ) )
            return;

        // optionally read a destination variable name
        Substring destVarCategory = new Substring();
        Substring destVarName     = new Substring();
        if( firstArg.Trim().IsNotEmpty() )
        {
            // separate category from variable name
            int catSeparatorIdx= firstArg.IndexOf( '_' );
            if (catSeparatorIdx >= 0 )
            {
                destVarCategory.Set( firstArg, 0                   , catSeparatorIdx );
                destVarName    .Set( firstArg, catSeparatorIdx + 1);
            }
            else
                destVarName.Set( firstArg );

            if ( destVarName.IsEmpty() )
            {
                logInternal( Verbosity.Error, "VAR", intMsg._()
                             ._( "Argument 'writeback' in variable " )
                             ._( variable.Fullname)
                             ._( "\n  Error:    Wrong destination variable name format\"" )
                             ._( firstArg )._( "\"" )  );
                return;
            }
        }

        // either write directly into LOX_LOGGER_VERBOSITY variable...
        Variable destVar= null;
        if( destVarName.IsEmpty() )
        {
            variable.ClearValues( 1 );
            destVar= variable;
        }
        // ...or into a new given variable
        else
        {
            destVar= new Variable( destVarCategory, destVarName, ALox.VERBOSITY.Delim );
            destVar.FormatHints=         variable.FormatHints;
            destVar.FormatAttrAlignment= variable.FormatAttrAlignment;
            destVar.Comments._("Created at runtime through config option 'writeback' in variable \"")._( variable.Fullname )._("\".");
        }

        // collect verbosities
        {
            int loggerNoMainDom= domains        .GetLoggerNo( logger );
            int loggerNoIntDom=  internalDomains.GetLoggerNo( logger );

            if ( loggerNoMainDom >= 0 ) verbositySettingToVariable( domains        , loggerNoMainDom, destVar );
            if ( loggerNoIntDom  >= 0 ) verbositySettingToVariable( internalDomains, loggerNoIntDom , destVar );
        }

        // now store using the same plug-in as original variable has
        destVar.Priority= variable.Priority;
        destVar.Store();

        // internal logging
        intMsg._()._( "Argument 'writeback' in variable " )._( variable.Fullname )
                  ._( ":\n  Verbosities for logger \"" )   ._( logger.GetName() )
                  ._( "\" written " );

        if( destVarName.IsEmpty() )
            intMsg._( "(to source variable)." );
        else
            intMsg._( "to variable \"" )  ._( destVar.Fullname ) ._("\".") ;
        logInternal( Verbosity.Info, "VAR", intMsg._( destVarName )._( "\"." ) );


        // verbose logging of the value written
        intMsg._()._("  Value:");
        for( int i= 0; i< destVar.Size() ; i++ )
            intMsg._( "\n    " )._( destVar.GetString(i) );
        logInternal( Verbosity.Verbose, "VAR", intMsg );
    }

    /** ****************************************************************************************
     * Implements functionality for configuration variable \c LOXNAME_DUMP_STATE_ON_EXIT.
     * Is called when a logger is removed.
     ******************************************************************************************/
    protected void dumpStateOnLoggerRemoval()
    {
        if( !loggerAddedSinceLastDebugState )
            return;
        loggerAddedSinceLastDebugState= false;

        Variable variable= new Variable( ALox.DUMP_STATE_ON_EXIT, GetName() );
        variable.Load();

        String      domain=         null;
        Verbosity   verbosity=      Verbosity.Info;

        Substring tok= new Substring();
        int flags= 0;
        for( int tokNo= 0; tokNo< variable.Size(); tokNo++ )
        {
            tok.Set( variable.GetString( tokNo ) );
            if( tok.IsEmpty() )
                continue;

            // state flags
                 if( tok.Equals( "NONE"            , Case.Ignore ) )  { flags= 0; break; }
            else if( tok.Equals( "Basic"           , Case.Ignore ) )  flags|= (int) Lox.StateInfo.Basic           ;
            else if( tok.Equals( "Version"         , Case.Ignore ) )  flags|= (int) Lox.StateInfo.Version         ;
            else if( tok.Equals( "Loggers"         , Case.Ignore ) )  flags|= (int) Lox.StateInfo.Loggers         ;

            else if( tok.Equals( "Domains"         , Case.Ignore ) )  flags|= (int) Lox.StateInfo.Domains         ;
            else if( tok.Equals( "InternalDomains" , Case.Ignore ) )  flags|= (int) Lox.StateInfo.InternalDomains ;
            else if( tok.Equals( "ScopeDomains"    , Case.Ignore ) )  flags|= (int) Lox.StateInfo.ScopeDomains    ;
            else if( tok.Equals( "DSR"             , Case.Ignore ) )  flags|= (int) Lox.StateInfo.DSR             ;
            else if( tok.Equals( "PrefixLogables"  , Case.Ignore ) )  flags|= (int) Lox.StateInfo.PrefixLogables  ;
            else if( tok.Equals( "Once"            , Case.Ignore ) )  flags|= (int) Lox.StateInfo.Once            ;
            else if( tok.Equals( "LogData"         , Case.Ignore ) )  flags|= (int) Lox.StateInfo.LogData         ;
            else if( tok.Equals( "ThreadMappings"  , Case.Ignore ) )  flags|= (int) Lox.StateInfo.ThreadMappings  ;

            else if( tok.Equals( "SPTR"            , Case.Ignore ) )  flags|= (int) Lox.StateInfo.SPTR            ;


            else if( tok.Equals( "All"             , Case.Ignore ) )  flags|= (int) Lox.StateInfo.All             ;

            // domain and verbosity
            else if( tok.Consume( "domain", Case.Ignore, Whitespaces.Trim ) )
            {
                if( tok.Consume( '=', Case.Sensitive, Whitespaces.Trim ) )
                    domain= tok.Trim().ToString();
            }
            else if( tok.Consume( "verbosity", Case.Ignore, Whitespaces.Trim ) )
            {
                if( tok.Consume( '=', Case.Sensitive, Whitespaces.Trim ) )
                    verbosity= ALox.ReadVerbosity( tok.Trim() );
            }

            // unknown argument
            else
            {
                logInternal( Verbosity.Error, "VAR", intMsg._()
                             ._( "Unknown argument '" )._(tok)
                             ._( "' in variable " )._(variable.Fullname)._( " = \"")._(variable.GetString())._('\"') );
            }
        }

        if ( flags != 0 )
        {
            State( domain, verbosity, "Auto dump state on exit requested: ", (Lox.StateInfo) flags );
        }
    }
    #endif // #if ALOX_DBG_LOG || ALOX_REL_LOG


    /** ********************************************************************************************
     * Removes a logger from this container.
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref SetVerbosity "SetVerbosity( logger, Verbosity.Off )"
     *       can be used.
     *
     * @param logger   The logger to be removed.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void RemoveLogger( Logger logger,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            bool omit= false;
            RemoveLogger( logger, ref omit,  cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Removes a logger from this container.
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref SetVerbosity "SetVerbosity( logger, Verbosity.Off )"
     *       can be used.
     *
     * @param      logger     The logger to be removed.
     * @param[out] wasFound   Output parameter that is set to \c true, if the \e Logger was found
     *                        and removed, to \c false otherwise.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void RemoveLogger( Logger logger, ref bool wasFound,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Acquire();

                int noMainDom=  domains        .GetLoggerNo( logger );
                int noIntDom=   internalDomains.GetLoggerNo( logger );

                if( noMainDom >= 0 || noIntDom >= 0 )
                {
                    dumpStateOnLoggerRemoval();
                    writeVerbositiesOnLoggerRemoval( logger );

                    if( noMainDom >= 0 )
                        domains.RemoveLogger( noMainDom );

                    if( noIntDom >= 0 )
                        internalDomains.RemoveLogger( noIntDom );

                    logger.RemoveAcquirer( this );

                    return;
                }

                // not found
                scopeInfo.Set( cln,csf,cmn, owner );

                logInternal( Verbosity.Warning, "LGR", intMsg._()
                    ._("Logger \"")._( logger)._NC("\" not found. Nothing removed."));

            } finally { Release(); }

        #endif
    }

    /** ********************************************************************************************
     * Removes logger named \p loggerName from this container.
     *
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref SetVerbosity "SetVerbosity( logger, Verbosity.Off )"
     *       can be used.
     *
     * @param loggerName  The name of the \e Logger to be removed (case insensitive).
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void RemoveLogger( String loggerName,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Logger omit= null;
            RemoveLogger( loggerName, ref omit,  cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Removes logger named \p loggerName from this container.
     *
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref SetVerbosity "SetVerbosity( logger, Verbosity.Off )"
     *       can be used.
     *
     * @param      loggerName  The name of the \e Logger to be removed (case insensitive).
     * @param[out] logger      Output parameter that returns the \e Logger that was removed, to null
     *                         if not found.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void RemoveLogger( String loggerName, ref Logger logger,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Acquire();
                scopeInfo.Set( cln,csf,cmn, owner );


                int noMainDom=  domains        .GetLoggerNo( loggerName );
                int noIntDom=   internalDomains.GetLoggerNo( loggerName );

                if( noMainDom >= 0 || noIntDom >= 0 )
                {
                                            logger=         domains.GetLogger( noMainDom );
                    if ( logger == null )   logger= internalDomains.GetLogger( noIntDom );

                    dumpStateOnLoggerRemoval();
                    writeVerbositiesOnLoggerRemoval( logger );

                    if( noMainDom >= 0 )
                        domains.RemoveLogger( noMainDom );

                    if( noIntDom >= 0 )
                        internalDomains.RemoveLogger( noIntDom );

                    logger.RemoveAcquirer( this );

                    logInternal( Verbosity.Info, "LGR", intMsg._()
                        ._("Logger \"")._NC(logger)._NC("\" removed."));

                    return;
                }

                // not found
                logInternal( Verbosity.Warning, "LGR", intMsg._()
                        ._("Logger \"")._NC(loggerName)._NC("\" not found. Nothing removed."));

            } finally { Release(); }
        #endif
    }

    /** ********************************************************************************************
     * Sets the \e %Verbosity of the <em>Log Domain</em> which is evaluated from parameter \p domain and
     * applicable <em>Scope Domains</em>. The \p verbosity given, is set recursively for all sub-domains.
     *
     * With the first invocation of this method for a distinct \p logger, this \e %Logger
     * is registered with this \e %Lox. In this case, prior to setting the given \e Verbosity
     * for the evaluated sub-domain, the \e Verbosity for all domains is set to
     * \b %Verbosity.Off.
     *
     * To deregister a \e Logger with a \b Lox, use method #RemoveLogger.
     * To 'disable' a \e Logger, invoke this method with parameters \p verbosity equaling to
     * \b %Verbosity.Off and \p domain to \c "/".
     *
     * Optional parameter \p priority defaults to
     * \ref cs::aworx::lib::config::Configuration::PrioDefault "Configuration.PrioDefault",
     * which is a lower priority than those of the standard plug-ins of external configuration data.
     * Therefore, external configuration by default 'overwrite' settings made from 'within the
     * source code', which simply means by invoking this method.<br>
     * The parameter can be provided for two main reasons:
     * - To 'lock' a verbosity setting against external manipulation.
     * - to 'break' the standard mechanism that an invocation of this method sets all
     *   sub-domains recursively. If a sub-domain was set with a higher priority
     *   (e.g. <c>%Configuration.PrioDefault + 1</c>, then this sub-domain will not be affected by
     *   future invocations of this method with standard-priority given.
     *
     * \attention
     *   The same as with most interface methods of this class, the given \p domain parameter is
     *   combined with <em>%Scope Domains</em> set for the callers' \e %Scope. In standard use
     *   cases of %ALox, the \e %Verbosity of a \e Domain is set using absolute domain path
     *   addressing. Therefore, it is recommended to have any domain path passed to this method
     *   starting with <c> '/'</c>, which suppresses the concatenation of <em>%Scope Domains</em>.<br>
     *   This is why this parameter with this method defaults to <c> '/'</c>, while with other
     *   methods of this class, it defaults to an empty string.<p>
     * \attention
     *   Even when using an absolute domain path, <em>%Scope Domains</em> of
     *   \e %Scope.ThreadInner, will still apply. This means that from within a thread that
     *   has such <em>%Scope Domain</em> set, this method is (almost) not usable!
     *   This all aligns with the concept (advice), that \e Loggers and their \e %Verbosity
     *   are generally set outside of such scopes, hence in configuration sections of a
     *   process.<p>
     * \attention
     *   Consequently, this method may be (mis-) used to modify the 'actual' (default) scope
     *   when explicitly giving an empty string with parameter \p domain. This is useful, to
     *   temporarily adjust a scope. But remember: %ALox was designed to avoid temporary code
     *   lines...
     *
     * @param logger     The logger to be to be affected (case insensitive).
     * @param verbosity  The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     * @param priority   The priority of the setting. Defaults to
     *                   \ref cs::aworx::lib::config::Configuration::PrioDefault "Configuration.PrioDefault".
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void        SetVerbosity( Logger logger, Verbosity verbosity, String domain = "/",
                                     int priority = Configuration.PrioDefault,
    [CallerLineNumber] int cln=0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();

            // initialize scope information
            scopeInfo.Set( cln,csf,cmn, owner );

            // check
            if ( logger == null )
            {
                logInternal( Verbosity.Error, "LGR", intMsg._()
                    ._NC( "Given Logger is \"null\". Verbosity not set."  ) );
                return;
            }

            // this might create the (path of) domain(s) and set the \e Loggers' verbosity like their
            // first parent's or as given in configuration
            Domain dom= evaluateResultDomain( domain );

            // search logger, insert if not found
            bool isNewLogger= false;
            int no= dom.GetLoggerNo( logger );
            if( no < 0 )
            {
                no= dom.AddLogger( logger );

                // error, logger with same name already exists
                if( no < 0 )
                {
                    logInternal( Verbosity.Error, "LGR",  intMsg._()
                            ._NC( "Unable to add logger \"" )._NC(logger)
                            ._NC("\". Logger with same name exists." ) );

                    logInternal( Verbosity.Verbose, "LGR",  intMsg._()
                              ._NC( "  Request was: SetVerbosity( \"")._(logger)._NC("\", \"")
                              ._(domain)        ._NC("\", Verbosity.")
                              ._NC(verbosity)   ._NC("\", ")
                              ._(priority)      ._NC(" )." ));

                    Logger existingLogger= dom.GetLogger( logger.GetName() );
                    logInternal( Verbosity.Verbose, "LGR", intMsg._()
                        ._NC( "  Existing Logger: \"")._NC(existingLogger)._('\"') );

                    return;
                }

                // We have to register with the SmartLock facility of the \e Logger.
                // But only if we have not done this yet, via the 'other' root domain tree
                if ( (dom.GetRoot() == domains ? internalDomains.GetLoggerNo( logger )
                                               :         domains.GetLoggerNo( logger ) ) < 0 )
                    logger.AddAcquirer( this );

                // store size of name to support tabular internal log output
                String loggerName= logger.GetName();
                if ( maxLoggerNameLength < loggerName.Length )
                    maxLoggerNameLength=   loggerName.Length;

                // for internal log
                isNewLogger= true;

                // remember that a logger was set after the last removal
                // (for variable LOXNAME_DUMP_STATE_ON_EXIT)
                loggerAddedSinceLastDebugState= true;
            }

            // do
            dom.SetVerbosity( no, verbosity, priority );

            // get verbosities from configuration
            if( isNewLogger )
            {
                logInternal( Verbosity.Info, "LGR",  intMsg._()
                    ._("Logger \"")._( logger )
                    ._(domain.StartsWith(ALox.InternalDomains) ?
                            "\" added for internal log messages." : "\" added." ) );

                // we have to get all verbosities of already existing domains
                Variable variable= new Variable( ALox.VERBOSITY, GetName(), logger.GetName() );
                if( 0 != variable.Load() )
                {
                    getAllVerbosities( logger, domains         , variable );
                    getAllVerbosities( logger, internalDomains , variable );
                }
            }

            intMsg._()._("Logger \"")._( logger.GetName() )._NC( "\":").Tab(11 + maxLoggerNameLength)
                          ._('\'')._NC( dom.FullPath )
                          ._( '\'' ).InsertChars(' ', maxDomainPathLength - dom.FullPath.Length() + 1 )
                          ._( "= Verbosity." );
                          ALox.ToString( verbosity, priority, intMsg ).TrimEnd()._('.');

            Verbosity actVerbosity= dom.GetVerbosity( no );
            if( actVerbosity != verbosity )
                intMsg._( " Lower priority (")._( priority )
                      ._(" < ")._(dom.GetPriority(no))
                      ._( "). Remains " )._NC( actVerbosity )._( '.' );
            logInternal( Verbosity.Info, "LGR", intMsg );

        } finally { Release(); }
        #endif
    }

    /** ********************************************************************************************
     * Same as \ref #SetVerbosity(Logger,Verbosity,String,int,int,String,String) "SetVerbosity" but
     * addressing the \e %Logger to manipulate by its name.<br>
     * This method may only be used after a \e %Logger was once 'registered' with this \b %Lox
     * using \ref #SetVerbosity(Logger,Verbosity,String,int,int,String,String) "SetVerbosity".
     *
     * @param loggerName The logger to be to be affected, identified by its name (case
     *                   insensitive).
     * @param verbosity  The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     * @param priority   The priority of the setting. Defaults to
     *                   \ref cs::aworx::lib::config::Configuration::PrioDefault "Configuration.PrioDefault".
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void SetVerbosity(  String     loggerName,
                                Verbosity  verbosity,
                                String     domain        ="/",
                                int        priority      = Configuration.PrioDefault,
    [CallerLineNumber] int cln=0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();

            scopeInfo.Set( cln,csf,cmn, owner );

            // get domain
            Domain dom= evaluateResultDomain( domain );

            // get logger
            int no= dom.GetLoggerNo( loggerName );
            if( no < 0 )
            {
                // we have to check if the logger was added in the 'other' tree
                Domain actualTree= dom.GetRoot();
                Domain otherTree=  actualTree == domains ? internalDomains
                                                         : domains;
                no= otherTree.GetLoggerNo( loggerName );
                if ( no >= 0 )
                {
                    SetVerbosity( otherTree.GetLogger( no ), Verbosity.Off,
                                  actualTree.FullPath.ToString(), Configuration.PrioDefault    ,cln,csf,cmn );
                    no= dom.GetLoggerNo( loggerName );
                    ALIB.ASSERT( no >= 0 );
                }
                else
                {
                    intMsg._()._NC( "Logger not found. Request was: SetVerbosity( \"")._(loggerName)._NC("\", \"")
                              ._(dom.FullPath)  ._NC("\", Verbosity.")
                              ._NC(verbosity)   ._NC(", ")
                              ._(priority)      ._NC(" )." );

                    logInternal( Verbosity.Warning, "LGR", intMsg );
                    return;
                }
            }

            // do
            dom.SetVerbosity( no, verbosity, priority );

            // log info on this
            intMsg._()._("Logger \"")._( dom.GetLogger( no ).GetName() )._NC( "\":").Tab(11 + maxLoggerNameLength)
                      ._('\'')._NC( dom.FullPath )
                      ._( '\'' ).InsertChars(' ', maxDomainPathLength - dom.FullPath.Length() + 1 )
                      ._( "= Verbosity." );
                      ALox.ToString( verbosity, priority, intMsg ).TrimEnd()._('.');
            Verbosity actVerbosity= dom.GetVerbosity( no );
            if( actVerbosity != verbosity )
                intMsg._( " Lower priority (")._( priority )
                      ._( " < ")._(dom.GetPriority(no))
                      ._( "). Remains " )._NC( actVerbosity )._( '.' );
            logInternal( Verbosity.Info, "LGR", intMsg );

        } finally { Release(); }
        #endif
    }

    /** ********************************************************************************************
     * The given \p scopeDomain becomes the default domain path for given \p scope.
     * This means, that any subsequent log invocations (from within this same scope) can omit the
     * domain parameter, or if they provide one, this Scope Domain path is prepended.
     * If subsequent log calls specify a domain name with a leading '/' character,
     * then the Scope Domain of the scope is ignored.<br>
     * Furthermore, if the given scope is an inner scope, outer scopes are prepended to the
     * given \p scopeDomain when the resulting domain of a log invocation is evaluated.
     * Again, this behavior can be overruled by prepending a leading '/' character to
     * \p scopeDomain.
     *
     * To remove a previously set Scope Domain a nulled or empty string has to be passed with
     * parameter \p scopeDomain.
     *
     * For \e %Scope.ThreadOuter and \e %Scope.ThreadInner, passing an empty or nulled string
     * removes the most recently added domain path. For removing an explicitly named
     * domain path of \e %Scope.ThreadOuter and \e %Scope.ThreadInner use method
     * #RemoveThreadDomain.
     *
     *
     * @param scopeDomain    The domain path to register.
     * @param scope     The scope that should the given \p domain be registered for.
     *                  Available Scope definitions are platform/language dependent.
     * @param pathLevel Used only with
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path".
     *                  Cuts the given number of directories from the end of the source path.
     *                  Optional and defaults to \c 0.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
        public  void SetDomain( String scopeDomain, Scope scope, int pathLevel= 0,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            setDomainImpl( scopeDomain, scope, pathLevel, false, null, cln,csf,cmn );
        #endif
    }

    /** ****************************************************************************************
     * This overloaded version of
     * \ref SetDomain(String,Scope,int,int,String,String) "SetDomain"
     * is applicable only for \e %Scope.ThreadOuter and \e %Scope.ThreadInner and allows to
     * specify the thread that the setting should be associated with.
     *
     * If \p scopeDomain is null or empty, the most recently added domain path is removed.
     * For removing an explicitly named domain associated with  a thread use method
     * #RemoveThreadDomain.
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.ThreadOuter or \e %Scope.ThreadInner. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related Scope Domains for.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
        public  void SetDomain( String scopeDomain, Scope scope, Thread thread,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            if ( !isThreadReleatedScope( scope, cln,csf,cmn) )
                return;

            setDomainImpl( scopeDomain, scope, 0, false, thread, cln,csf,cmn );
        #endif
    }

    /** ****************************************************************************************
     * This method is used to remove an <em>explicitly given</em> domain path from the list
     * of domain paths set for \e %Scope.ThreadOuter or \e %Scope.ThreadInner.
     *
     * To remove the most recently added domain path from such thread-related \e %Scope,
     * use one of the overloaded methods #SetDomain and provide an empty or nulled
     * value for parameter \p scopeDomain (the same as how domain paths of other \e %Scopes
     * are removed).
     *
     * \note
     *   The long name of the method already indicates that this method is a little special.
     *   Only seldom, more than one <em>%Scope Domain</em> is needed to be added. And if this
     *   is needed, then such <em>%Scope Domains</em> usually get removed in reverse order of
     *   their definition, with is performed using the standard interface that allows 'removing'
     *   any other <em>%Scope Domain</em>. (Passing an empty or nulled domain
     *   path to method #SetDomain.)
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.ThreadOuter or \e %Scope.ThreadInner. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related Scope Domains for.
     *                    Defaults to the current thread.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
        public  void RemoveThreadDomain( String scopeDomain, Scope scope, Thread thread=null,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();
            if ( !isThreadReleatedScope( scope, cln,csf,cmn) )
                return;

            // initialize scope information
            scopeInfo.Set( cln,csf,cmn, owner );

            // check
            if ( String.IsNullOrEmpty( scopeDomain ) )
            {
                intMsg._()._NC( "Illegal parameter. No scope domain path given. Nothing removed for " );
                ALox.ToString(scope, 0, intMsg); intMsg._( '.' );
                logInternal( Verbosity.Warning, "DMN", intMsg );

                // do nothing
                return;
            }

            // invoke internal master
            setDomainImpl( scopeDomain, scope, 0, true, thread,  cln,csf,cmn );
        } finally { Release(); }
        #endif
    }

    /** ****************************************************************************************
     * Adds a <em>Domain Substitution Rule</em>.
     * <em>Domain Substitution</em> is performed as a last step when evaluating the domain path of a <em>Log Statement</em>,
     * taking <em>Scope Domains</em> and the optional parameter \p domain of the statement into
     * account.<br>
     *
     * <b>Wildcards</b><br>
     * Parameter \p domainPath supports \b 'wildcard' character <c> '*'</c> at the its beginning
     * and at its end (or both). This allows to have four types of rules:
     * - Exact match
     * - Prefix match (\c * at the end of \p domainPath)
     * - Suffix match (\c * at the start of \p domainPath)
     * - Substring match (\c * at both, start and the end of \p domainPath)
     *
     * Only minimal checks are performed, e.g. if an exact match is requested, but \p domainPath
     * does not start with character <c> '/'</c>. In this and some other cases, the rule is not
     * stored and an internal warning is logged. Further checks, for example for illegal
     * domain path characters are not performed (those will be eliminated when the resulting
     * domain path is to be created internally).
     *
     * <b>Circular Dependencies</b><br>
     * If the given rules have circular dependencies, only a limited number (ten) replacements
     * are performed. If this number of replacements for one <em>Log Statement</em> is exceeded, an internal
     * warning message is logged. This is done only \e once over the life-time of a \e Logger.
     *
     * <b>Application of Rules</b><br>
     * Rules are applied in the order of their definition. After all rules have been applied
     * this is repeated as long as at least one rule matched (up to ten times).
     *
     * <b>Deletion of Rules</b>
     * To delete a rule, invoke the method with same parameter \p domainPath and a 'nulled'
     * or empty string for parameter \p replacement.
     * To delete all rules, invoke the method with parameter \p domainPath 'nulled'
     * or empty.
     *
     * <b>Final remarks</b>
     * Domain substitution is useful to permanently change ('redirect') domain paths of
     * 3rd party code (e.g. libraries using ALox) or log statements that must not be changed
     * for other reasons. It is advised to not 'overuse' this feature, as side effects
     * are inherent to the concept of <em>Domain Substitution</em>. For example, an unwanted side effect might be
     * that <em>Prefix Logables</em> are not applicable to the substituted domain, while other <em>Prefix Logables</em> are
     * bound to the resulting domain.
     *
     * For \b %Lox objects that should be protected of external manipulation, it is advisable,
     * to remove all <em>Domain Substitution Rules</em> right after the \b %Lox was created by invoking this method with
     * a nulled value for parameter \p domainPath. The reason is, that otherwise, through
     * configuration files or command line parameters, domains of the \b %Lox can be substituted
     * and then the resulting domains \e Verbosities be \e overwritten using further configuration
     * variables. Any prioritized \e 'internal' setting of \e Verbosities this way could be
     * circumvented!
     *
     * For more information consult the ALox user manual.
     *
     * @param domainPath  The path to search. Has to start with either  <c> '/'</c> or <c> '*'</c>.
     * @param replacement The replacement path.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void SetDomainSubstitutionRule( String domainPath, String replacement,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();

            // initialize scope information
            scopeInfo.Set( cln,csf,cmn, owner );
            intMsg._();

            // check null param: clears all rules
            if ( String.IsNullOrEmpty( domainPath ) )
            {
                oneTimeWarningCircularDS= false;
                domainSubstitutions.Clear();
                intMsg._( "Domain substitution rules removed." );
                logInternal( Verbosity.Info, "DMN", intMsg );
                return;
            }

            DomainSubstitutionRule newRule= new DomainSubstitutionRule( domainPath, replacement );
            if ( newRule.Search.IsEmpty() )
            {
                intMsg._( "Illegal domain substitution rule. Nothing stored." );
                logInternal( Verbosity.Warning, "DMN", intMsg );
                return;
            }

            // search existing rule
            int  it;
            for( it= 0; it != domainSubstitutions.Count ; ++it )
            {
                if (     domainSubstitutions[it].type == newRule.type
                      && domainSubstitutions[it].Search.Equals( newRule.Search ) )
                    break;
            }

            // no replacement given?
            if ( String.IsNullOrEmpty(replacement) )
            {
                if ( it == domainSubstitutions.Count )
                {
                    intMsg._( "Domain substitution rule \"")._( domainPath)._( "\" not found. Nothing to remove." );
                    logInternal( Verbosity.Warning, "DMN", intMsg );
                    return;
                }

                intMsg._( "Domain substitution rule \"")._( domainPath      )._( "\" -> \"" )
                                                    ._( domainSubstitutions[it].Replacement  )._( "\" removed." );
                domainSubstitutions.RemoveAt( it );
                logInternal( Verbosity.Info, "DMN", intMsg );
                return;
            }


            intMsg._( "Domain substitution rule \"")._( domainPath          )._( "\" -> \"" )
                                                ._( newRule.Replacement )._( "\" set." );

            // change of rule
            if ( it != domainSubstitutions.Count )
            {
                intMsg._( " Replacing previous -> \"")._( domainSubstitutions[it].Replacement )._( "\"." );
                domainSubstitutions[it].Replacement._()._( newRule.Replacement );
            }
            else
                domainSubstitutions.Add( newRule );

            logInternal( Verbosity.Info, "DMN", intMsg );


        } finally { Release(); }
        #endif
    }


    /** ****************************************************************************************
     * The given \p logable becomes a <em>Prefix Logable</em> provided to loggers with log statements
     * executed within the given \p scope.
     * The list of objects received by a logger is sorted from outer scope to inner scope.
     * The logable of the <em>Log Statement</em> itself, is the last in the list, except one or
     * more <em>Prefix Logables</em> of \e %Scope.ThreadInner are set. Those are (similar to how this
     * \e %Scope is handled with <em>%Scope Domains</em>) are appended to the end of the list.
     *
     * To remove a previously set <em>Prefix Logable</em>, \c null has to be passed with
     * parameter \p logable.
     * For \e %Scope.ThreadOuter and \e %Scope.ThreadInner, passing \c null
     * removes the most recently added <em>Prefix Logable</em>.
     *
     *<p>
     * \note
     *   The word 'prefix' in this methods' name and in the name of ALox feature
     *   <em>Prefix Logables</em> is chosen for the fact that with text loggers (which is the
     *   most widely applied use case for ALox) such objects are prefixes to the log
     *   message. Of-course, with using \e %Scope.ThreadInner, this turns into a suffix!<br>
     *   When using ALox to process objects instead of log messages, the concept of
     *   <em>Prefix Logables</em> is very useful. Just the name does not fit so well anymore.
     *   Think of 'SetContext' and <em>Context Objects</em> instead.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     * @param scope       The scope that should the given \p logable be registered for.
     *                    Available Scope definitions are platform/language dependent.
     * @param pathLevel   Used only if parameter \p scope equals
     *                    \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                    to reference parent directories. Optional and defaults to \c 0.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void        SetPrefix( Object logable, Scope scope, int pathLevel = 0,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            setPrefixImpl( logable, scope, pathLevel, null ,cln,csf,cmn );
        #endif
    }


    /** ****************************************************************************************
     * This overloaded version of
     * \ref SetPrefix(Object,Scope,int, int,String,String) "SetPrefix" is applicable only for
     * \e %Scope.ThreadOuter and \e %Scope.ThreadInner and allows to specify the thread that
     * the setting should be associated with.
     *
     * If \p logable is null, the most recently added <em>Prefix Logable</em> is removed.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     * @param scope       Either \e %Scope.ThreadOuter or \e %Scope.ThreadInner. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related <em>Prefix Logable</em> for.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void        SetPrefix( Object logable, Scope scope, Thread thread,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            setPrefixImpl( logable, scope, 0, thread ,cln,csf,cmn );
        #endif
    }

    /** ****************************************************************************************
     * The given \p logable becomes a <em>Prefix Logable</em> associated to the given <em>Log Domain</em>.
     * <em>Prefix Logables</em> associated with the <em>Log Domain</em> are added to the list of \e Logables right
     * before the main \e Logable of the <em>Log Statement</em> itself.
     * Multiple <em>Prefix Logables</em> can be added per <em>Log Domain</em>.
     *
     * To remove the most recently added <em>Prefix Logable</em> associated with a <em>Log Domain</em>,
     * \c null has to be passed with parameter \p logable.
     *
     * \attention
     *   The same as with most interface methods of this class, the given \p domain parameter is
     *   combined with <em>%Scope Domains</em> set for the callers' \e %Scope.
     *   To suppress this, an absolute domain path can be used. (Still any <em>Scope Domain</em> of
     *   \e %Scope.Thread.Inner will be applied).
     *   The default value of parameter \p domain is \c "" which addresses the domain evaluated
     *   for the current scope.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     * @param domain      The domain path. Defaults to \c null, resulting in
     *                    evaluated <em>Scope Domain</em> path.
     * @param otherPLs    If set to \c Inclusion.Exclude, scope-related <em>Prefix Logables</em>
     *                    are ignored and only domain-related <em>Prefix Logables</em> are passed to
     *                    the \e Loggers.
     *                    Defaults to \c Inclusion.Include.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void        SetPrefix( Object logable, String domain =null,
                                  Inclusion otherPLs =Inclusion.Include,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();

            // initialize scope information
            scopeInfo.Set( cln,csf,cmn, owner );

            // we consider empty strings as unset command, so we set them to null
            if( logable != null )
            {
                Type type= logable.GetType();
                if (    ( type == typeof( AString ) && ((AString) logable).IsNull() )
                     || ( type == typeof( String  ) && ((String)  logable).Length == 0 )
                   )

                    logable= null;
            }

            Domain dom= evaluateResultDomain( domain );

            Verbosity intLogVerbosity= Verbosity.Info;
            intMsg._();

            if ( logable != null )
            {
                dom.PrefixLogables.Add( new Domain.PL( logable, otherPLs ) );
                intMsg._("Object \"")._NC(logable)._NC( "\" added as prefix logable for" );
            }
            else
            {
                int qtyPLs= dom.PrefixLogables.Count;
                if ( qtyPLs > 0 )
                {
                    Object removedLogable= dom.PrefixLogables[qtyPLs - 1].Logable;
                    dom.PrefixLogables.RemoveAt( qtyPLs - 1 );

                    intMsg._("Object \"")._NC(removedLogable)._NC( "\" removed from list of prefix logables for");
                }
                else
                {
                    intMsg._NC( "No prefix logable to remove for" );
                    intLogVerbosity=  Verbosity.Warning;
                }
            }

            intMsg._NC( " domain \'")._NC( dom.FullPath )._NC( "\'."  );
            logInternal( intLogVerbosity,    "PFX", intMsg );

        } finally { Release(); }
        #endif
    }

    /** ********************************************************************************************
     * This method is used reset (or to explicitly set) the start time of the \e Logger(s).
     * The only impact is the output of time differences in the log lines. Hence, it is useful to
     * see some absolute time values when doing basic performance tests using the \e Logger.
     *
     * \note This affects loggers that are registered for at least one standard domain.
     *       In other words, loggers that are exclusively attached to the internal domain,
     *       will not be affected.
     *
     * @param startTime  Optional parameter with the new start time. Defaults
     *                   to current time if omitted.
     * @param loggerName The name of the \e Logger(s) whose start time is to be set (case insensitive).
     *                   Defaults to empty string, which indicates that all loggers are to
     *                   be affected.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void SetStartTime( DateTime? startTime= null, String loggerName= null,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();

            // initialize scope information
            scopeInfo.Set( cln,csf,cmn, owner );

            // check if start time was set
            Ticks time= new Ticks( 0L );
            if ( startTime != null)
                time.SetFromDotNetDateTime( startTime.Value );
            else
                time.Set();

            // request logger only from main domain tree
            Logger logger= domains.GetLogger( loggerName );
            if ( logger == null )
            {
                logInternal( Verbosity.Error, "LGR", intMsg.Clear()
                    ._( '\"' ) ._NC( loggerName )._NC( "\": not found. Start time not set." ) );
                return;
            }

            // do
            logger.TimeOfCreation.Set( time );
            logger.TimeOfLastLog .Set( time );

            // log info on this
            logInternal( Verbosity.Info, "LGR", intMsg.Clear()
                ._('\"')._NC(logger)._NC("\": Start time set to ")
                ._NC(startTime.HasValue? startTime.Value.ToString() : "<now>")._('.') );

        } finally { Release(); }
        #endif
    }

    /** ********************************************************************************************
     * This method sets a human readable name to the given thread ID (or current thread) which is
     * optionally included in each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs
     * @param id            (Optional) Parameter providing the thread ID. If omitted, the
     *                      current thread's ID is used.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void MapThreadName( String threadName, int id= -1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Acquire();

                // get current thread id
                String origThreadName= null;
                if ( id < 0 )
                {
                    Thread t=       Thread.CurrentThread;
                    id=             t.ManagedThreadId;
                    origThreadName= t.Name;
                }

                // add entry
                threadDictionary[id]= threadName;

                // log info on this
                // initialize scope information
                scopeInfo.Set( cln,csf,cmn, owner );

                intMsg.Clear()._NC("Mapped thread ID ")
                              ._(id)._NC(" to \"")._NC(threadName)._NC("\".");
                if ( !String.IsNullOrEmpty( origThreadName )  )
                    intMsg._NC(" Original thread name: \"")._NC(origThreadName)._NC("\".");
                logInternal( Verbosity.Info, "THR",  intMsg );

            } finally { Release(); }
        #endif
    }

    /** ****************************************************************************************
     * Stores ALox <em>Log Data</em>, an object of base type
     * \ref cs::aworx::lox::LogData "LogData" which can afterwards be retrieved by invoking
     * #Retrieve. Using the optional \p key and \p scope offer various possibilities to reference
     * this data later.<br>
     *
     * To remove data from the store, pass \c null with parameter \p data.
     *
     * \attention
     * When data objects are 'overwritten', previous objects will be deleted internally.
     * Hence, only pointers to heap-allocated objects (created with \c new) may be passed!<br>
     * For more information, consult the ALox user manual.
     *
     * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
     *       It is not advised to use <em>Log Data</em> to implement application logic.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param key       The optional key to the data.
     *                  If omitted (or empty or null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                  to reference parent directories. Optional and defaults to \c 0.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Store( LogData  data,                 String    key,
                       Scope    scope= Scope.Global , int       pathLevel= 0,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Acquire(cln, csf, cmn );

            // store scope info
            scopeInfo.Set( cln,csf,cmn, owner );
            intMsg._();

            // We need a key. If none is given, we use a constant one indicating that storage is
            // associated exclusively with scope
            AString aKey= new AString(key);
            bool keyWasEmtpy;
            if ( (keyWasEmtpy= aKey.IsEmpty()) )
                aKey._NC( noKeyHashKey );

            // get the store
            scopeLogData.InitAccess( scope, pathLevel, null );
            Dictionary<AString, LogData> map= (Dictionary<AString, LogData>) scopeLogData.Get();
            if( map == null && data != null )
            {
                map= new Dictionary<AString, LogData>();
                scopeLogData.Store(map );
            }

            // create map entry
            LogData previous= null;
            if ( map != null )
                map.TryGetValue( aKey, out previous );

            if ( data != null )
            {
                map[aKey]= data;

                // log info if this was the last time
                intMsg._NC(  "Stored data " );

                if ( !keyWasEmtpy )
                    intMsg._NC( " with key \"" )._NC( tmpAS )._NC( "\" " );
                intMsg._NC( "in " );
                ALox.ToString(scope, pathLevel, intMsg);

                intMsg._( '.' );
                if ( previous != null )
                    intMsg._NC( " (Replaced previous.)" );
            }
            else
            {
                if ( previous != null )
                {
                    map.Remove( aKey );
                    if ( map.Count == 0 )
                        scopeLogData.Remove( null );

                    intMsg._NC( "Deleted map data " );
                }
                else
                    intMsg._NC( "No map data found to delete " );

                if ( !keyWasEmtpy )
                    intMsg._NC( " with key \"" )._NC( tmpAS )._NC( "\" " );
                intMsg._NC( "in " );
                ALox.ToString(scope, pathLevel, intMsg);
            }

            logInternal( Verbosity.Info, "LGD", intMsg );


        } finally { Release(); }
        #endif
    }

    /** ****************************************************************************************
     * Overloaded version of
     * Store(LogData*,const TString&,Scope,int) "Store" which omits parameter \p key.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                  to reference parent directories. Optional and defaults to \c 0.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     ******************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Store( LogData  data,
                       Scope scope= Scope.Global , int  pathLevel= 0,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Store( data, null, scope, pathLevel    ,cln,csf,cmn);
        #endif
    }

    /** ****************************************************************************************
     * Retrieves ALox <em>Log Data</em>, an object of base type
     * \ref cs::aworx::lox::LogData "LogData" which can be stored by invoking
     * #Store. Using the optional \p key and \p scope offer various possibilities to reference
     * such objects.<br>
     *
     * \note If no <em>Log Data</em> object is found, an empty object is stored and returned.
     *
     * <p>
     * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
     *       It is not advised to use <em>Log Data</em> to implement application logic.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                  to reference parent directories. Optional and defaults to \c 0.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public LogData  Retrieve( String key, Scope scope= Scope.Global,  int pathLevel= 0,

    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();

            // store scope info
            scopeInfo.Set( cln,csf,cmn, owner );

            // get the data (create if not found)
            LogData returnValue= null;
            scopeLogData.InitAccess( scope, pathLevel, null );
            bool keyWasEmtpy= false;
            for( int i= 0; i < 2 ; i++ )
            {
                // We need a key. If none is given, we use a constant one indicating that storage is
                // associated exclusively with scope
                tmpAS._()._(key);
                if ( (keyWasEmtpy= tmpAS.IsEmpty()) )
                    tmpAS._( noKeyHashKey );

                Dictionary<AString, LogData> map= (Dictionary<AString, LogData>) scopeLogData.Get();
                if( map != null )
                    map.TryGetValue( tmpAS, out returnValue );

                if( returnValue == null )
                    Store( new LogData(), key, scope, pathLevel,  cln,csf,cmn);
                else
                    break;
            }

            // log info if this was the last time
            intMsg._NC(  "Data " );

            if ( !keyWasEmtpy )
                intMsg._NC( " with key \"" )._NC( key )._NC( "\" " );
            intMsg._NC( "in " );
            ALox.ToString(scope, pathLevel, intMsg);
            intMsg._NC( returnValue != null ? " received." : " not found." );

            logInternal( Verbosity.Info, "LGD", intMsg );
            return returnValue;

        } finally { Release(); }
        #else
            return null;
        #endif
    }

    /** ****************************************************************************************
     * Overloaded version of #Retrieve which omits parameter \p key.
     *
     * \note <em>Log Data</em> is a feature provided by ALox to support debug-logging.
     *       It is not advised to use <em>Log Data</em> to implement application logic.
     *
     * @param scope     The \e %Scope that the data is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                  to reference parent directories. Optional and defaults to \c 0.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     * @return The \b LogData object, \c null if nothing was found.
     ******************************************************************************************/
    public LogData  Retrieve( Scope scope= Scope.Global, int pathLevel= 0,

    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            return Retrieve( null, scope, pathLevel    ,cln,csf,cmn);
        #else
            return null;
        #endif
    }

    /** ********************************************************************************************
     * This method logs the current configuration of this Lox and its encapsulated objects.
     * It uses method #GetState to assemble the logable string.
     *
     * \note
     *   As an alternative to (temporarily) adding an invocation of <b>%Lox.State</b> to
     *   your code, ALox provides configuration variable
     *   [ALOX_LOXNAME_DUMP_STATE_ON_EXIT](group__GrpALoxConfigVars.html).
     *   This allows to enable an automatic invocation of this method using external
     *   configuration data like command line parameters, environment variables or
     *   INI files.
     *
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param headLine  If given, a separated headline will be logged at first place.
     * @param flags     Flag bits that define which state information is logged.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void State( String        domain,
                        Verbosity     verbosity,
                        String        headLine,
                        StateInfo     flags,

    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Acquire();

                scopeInfo.Set( cln,csf,cmn, owner );
                AString buf=        new AString( 2048 );
                if ( !String.IsNullOrEmpty(headLine) )
                    buf._NC( headLine ).NewLine();
                GetState( buf, flags );
                Entry( domain, verbosity, buf, cln,csf,cmn );

            } finally { Release(); }
        #endif
    }

    /** ********************************************************************************************
     *  This method collects state information about this lox.
     *
     * @param buf       The target string.
     * @param flags     Flag bits that define which state information is collected.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void GetState( AString   buf,  Lox.StateInfo flags,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            try { Acquire();

                ScopeDump scopeDump= new ScopeDump( threadDictionary, noKeyHashKey, buf );


                // basic lox info
                if( (flags & Lox.StateInfo.Basic) != 0 )
                    buf._NC( "Name:            \"" )._NC( scopeInfo.GetLoxName() )._('\"').NewLine();
                if( (flags & Lox.StateInfo.Version) != 0 )
                {
                    buf._NC( "Version:         " )._NC( ALox.Version )._NC(" (Rev. ")._NC( ALox.Revision)._(')').NewLine();
                    buf._NC( "Thread-Safeness: " )._NC( GetSafeness() ).NewLine();
                }
                if( (flags & Lox.StateInfo.Basic) != 0 )
                    buf._NC( "#Log Calls:      " )._  ( CntLogCalls                   ).NewLine();
                if( (flags & Lox.StateInfo.Basic ) != 0 || (flags & Lox.StateInfo.Version ) != 0 )
                    buf.NewLine();

                //  source path trim info
                if( (flags & Lox.StateInfo.SPTR ) != 0 )
                {
                    buf._NC( "Source Path Trimming Rules: " ).NewLine();

                    int cnt= 0;
                    // do 2 times, 0== global list, 1 == local list
                    for( int trimRuleNo= 0; trimRuleNo < 2 ; trimRuleNo++ )
                    {
                        // choosel local or global list
                        List<ScopeInfo.SourcePathTrimRule>  trimRulesList=
                                   trimRuleNo == 0   ? ScopeInfo.GlobalSPTRs
                                                     : scopeInfo.LocalSPTRs;


                        // loop over trimInfo
                        foreach ( ScopeInfo.SourcePathTrimRule rule in trimRulesList )
                        {
                            cnt++;
                            buf._NC( trimRuleNo == 0 ? "  Global: "
                                                     : "  Local:  " );
                            buf._NC( rule.IsPrefix ?  "\"" : "\"*");
                            buf._NC( rule.Path )._NC( "\", " );
                            buf._NC( rule.IncludeString );
                            if ( rule.TrimOffset != 0 )
                                buf._NC( rule.Path )._NC( "\", Offset: " )._( rule.TrimOffset );
                            buf._NC( ", Priority: " ); ALox.ToStringPriority( rule.Priority, buf );
                            buf.NewLine();
                        }
                    }

                    if ( cnt == 0 )
                        buf._NC("  <no rules set>" ).NewLine();
                    buf.NewLine();
                }

                //  domain substitutions
                if( (flags & Lox.StateInfo.DSR ) != 0 )
                {
                    buf._NC( "Domain Substitution Rules: " ).NewLine();
                    if( domainSubstitutions.Count > 0 )
                    {
                        // get size
                        int maxWidth= 0;
                        foreach ( DomainSubstitutionRule it in domainSubstitutions )
                            if ( maxWidth < it.Search.Length() )
                                 maxWidth = it.Search.Length();
                        maxWidth+= 2;

                        // write
                        foreach ( DomainSubstitutionRule it in domainSubstitutions )
                        {
                            buf._NC( "  " );
                            if (    it.type == DomainSubstitutionRule.Type.EndsWith
                                 || it.type == DomainSubstitutionRule.Type.Substring )
                                buf._( '*' );

                            buf._NC( it.Search );

                            if (    it.type == DomainSubstitutionRule.Type.StartsWith
                                 || it.type == DomainSubstitutionRule.Type.Substring )
                                buf._( '*' );

                            buf.Tab( maxWidth, 0 )
                               ._NC( " -> " )
                               ._NC( it.Replacement );
                            buf.NewLine();
                        }
                    }
                    else
                        buf._NC("  <no rules set>" ).NewLine();
                    buf.NewLine();
                }

                // Log Once Counters
                if( (flags & Lox.StateInfo.Once ) != 0 )
                {
                    buf._NC( "Once() Counters: " ).NewLine();
                    if ( scopeDump.writeStoreMap( scopeLogOnce ) == 0 )
                        buf._NC("  <no Once() counters set>" ).NewLine();
                    buf.NewLine();
                }

                // Log Data
                if( (flags & Lox.StateInfo.LogData ) != 0 )
                {
                    buf._NC( "Log Data: " ).NewLine();
                    if ( scopeDump.writeStoreMap( scopeLogData ) == 0 )
                        buf._NC("  <no data objects stored>" ).NewLine();
                    buf.NewLine();
                }

                // Prefix Logables
                if( (flags & Lox.StateInfo.PrefixLogables ) != 0 )
                {
                    buf._NC( "Prefix Logables: " ).NewLine();
                    int oldLength= buf.Length();
                    scopeDump.writeScopePrefixes( scopePrefixes, 2 );
                    logStateCollectPrefixes( domains, 2, buf );
                    if ( oldLength == buf.Length() )
                        buf._NC("  <no prefix logables set>" ).NewLine();
                    buf.NewLine();
                }

                // thread mappings
                if( (flags & Lox.StateInfo.ThreadMappings ) != 0 )
                {
                    buf._NC( "Named Threads:   " ).NewLine();
                    if ( threadDictionary.Count == 0 )
                        buf._NC("  No thread name mappings" ).NewLine();
                    else
                        foreach ( int key in threadDictionary.Keys )
                        {
                            buf._NC( "  " ).Field()._('(')._(key)._NC( "):").Field( 7, Alignment.Left )
                                           ._('\"')._NC( threadDictionary[key] ) ._('\"');
                            buf.NewLine();
                        }
                    buf.NewLine();
                }

                // Scope Domains
                if( (flags & Lox.StateInfo.ScopeDomains ) != 0 )
                {
                    buf._NC( "Scope Domains: " ).NewLine();
                    if ( scopeDump.writeScopeDomains( scopeDomains, 2 ) == 0 )
                        buf._NC("  <no scope domains set>" ).NewLine();
                    buf.NewLine();
                }

                // Loggers (and their domains)
                if( (flags & Lox.StateInfo.Loggers ) != 0 )
                {
                    List<Domain> domsWithDiffVerb= new List<Domain>();
                    StringBuilder tSB= new StringBuilder();

                    for (int treeNo= 0; treeNo < 2; ++treeNo )
                    {
                        Domain domTree;
                        if( treeNo==0 )
                        {
                             domTree= domains;
                             buf._NC( "Loggers:" ).NewLine();
                        }
                        else
                        {
                             domTree= internalDomains;
                             buf._NC( "Loggers on Internal Domains:" ).NewLine();
                        }
                        int cnt= 0;

                        tSB.Clear();
                        for ( int loggerNo= 0; loggerNo < domTree.CountLoggers() ; loggerNo++ )
                        {
                            cnt++;
                            Logger logger= domTree.GetLogger( loggerNo );
                            buf._NC( "  "  )._NC(  logger).NewLine();
                            buf._NC( "    Lines logged:  "     )._(  logger.CntLogs   ).NewLine();

                            tSB.Clear(); tSB.AppendFormat( CultureInfo.InvariantCulture, "{0:yyyy-MM-dd HH:mm:ss}", logger.TimeOfCreation.InDotNetDateTime());
                            buf._NC( "    Creation time: "     )._NC(  tSB ).NewLine();

                            tSB.Clear(); tSB.AppendFormat( CultureInfo.InvariantCulture, "{0:yyyy-MM-dd HH:mm:ss}", logger.TimeOfLastLog.InDotNetDateTime());
                            buf._NC( "    Last log time: "     )._NC(  tSB ).NewLine();

                            domsWithDiffVerb.Clear();
                            logStateDomsWithDiffVerb( domTree, loggerNo, domsWithDiffVerb);
                            foreach ( Domain dom in domsWithDiffVerb )
                            {
                                buf._NC( "    " )
                                   ._NC(  dom == domsWithDiffVerb[0] ? "Verbosities:   "
                                                                     : "               " );

                                int tabRef= buf.Length();
                                buf._NC( dom.FullPath )
                                   .InsertChars( ' ',  maxDomainPathLength + 1 - buf.Length() + tabRef )
                                   ._NC("= "); ALox.ToString(  dom.GetVerbosity( loggerNo ), dom.GetPriority(loggerNo), buf )
                                   .NewLine();
                            }
                            buf.NewLine();
                        }

                        if ( cnt == 0 )
                            buf._NC("  <no loggers attached>" ).NewLine();
                        buf.NewLine();
                    }
                }


                // internal domains
                if( (flags & Lox.StateInfo.InternalDomains ) != 0 )
                {
                    buf._NC( "Internal Domains:" ).NewLine();
                    logStateDomainRecursive( internalDomains, buf );
                    buf.NewLine();
                }

                // main domains
                if( (flags & Lox.StateInfo.Domains ) != 0 )
                {
                    buf._NC( "Domains:" ).NewLine();
                    logStateDomainRecursive( domains,         buf );
                    buf.NewLine();
                }
            } finally { Release(); }
        #endif
    }


    #if ALOX_DBG_LOG || ALOX_REL_LOG
    /** ********************************************************************************************
     * Internal method used by State() to recursively log Domain instances.
     *
     * @param domain      The Domain instance to log out.
     * @param buf         The buffer to log to.
     **********************************************************************************************/
    protected  void logStateDomainRecursive( Domain domain, AString buf )
    {
        int reference= buf.Length();
        buf._NC("  ")  ._NC( domain );
        int idx= buf.IndexOf( '[', reference );
        buf.InsertChars( ' ', maxDomainPathLength + 5 - idx + reference , idx);
        buf.NewLine();

        // loop over all sub domains (recursion)
        foreach ( Domain subDomain in domain.SubDomains )
            logStateDomainRecursive( subDomain, buf);
    }


    /** ********************************************************************************************
     * Internal method used by State() to recursively (DFS) log <em>Prefix Logables</em> bound to
     * <em>Log Domains</em>
     *
     * @param domain        The actual domain to check.
     * @param indentSpaces  The number of spaces to write before each line.
     * @param target        The target string.
     **********************************************************************************************/
    protected void logStateCollectPrefixes( Domain domain, int indentSpaces, AString target )
    {
        foreach ( Domain.PL pfl in domain.PrefixLogables )
        {
            target.InsertChars( ' ', indentSpaces );

            target._('\"');
            int idx= target.Length();
            target._NC( pfl.Logable );
            ESC.ReplaceToReadable( target, idx );
            target._('\"');

            if ( pfl.IncludeOtherPLs == Inclusion.Exclude )
                target._NC( " (Excl.)" );
            target.Tab( 25 );
            target._NC( "<domain>           [" )._NC( domain.FullPath )._(']').NewLine();
        }

        foreach( Domain it in domain.SubDomains )
            logStateCollectPrefixes( it, indentSpaces, target );
    }

    /** ********************************************************************************************
     * Internal method used by State() to recursively (DFS) collect Domains of Logger that have
     * a different verbosity than their parent.
     *
     * @param domain      The actual domain to check.
     * @param loggerNo    The logger to collect domains for.
     * @param results     The result list.
     **********************************************************************************************/
    protected void logStateDomsWithDiffVerb( Domain domain, int loggerNo, List<Domain> results )
    {
        if (    domain.Parent == null
            ||  domain.Parent.GetVerbosity(loggerNo) != domain.GetVerbosity(loggerNo) )
            results.Add( domain );

        foreach( Domain it in domain.SubDomains )
            logStateDomsWithDiffVerb( it, loggerNo, results );
    }
    #endif


    // #############################################################################################
    // Main logging methods
    // #############################################################################################

    /** ********************************************************************************************
     * Logs a \e Logable with the given \e %Verbosity.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Entry( String domain, Verbosity verbosity, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();

            #if ALOX_DBG_LOG
                // auto-initialization of ALox
                ALox.Init();

                // auto-initialization of debug loggers
                if( domains.CountLoggers() == 0 && this == Log.LOX )
                    Log.AddDebugLogger( this );
            #endif

            CntLogCalls++;

            if ( domains.CountLoggers() == 0 )
                return;

            scopeInfo.Set( cln,csf,cmn, owner );

            log( evaluateResultDomain( domain ), verbosity, logable, Inclusion.Include );

            // release lock if logable was our internal log buffer singleton
            if ( logable == logBuf )
                logBufLock.Release();

       } finally { Release(); }
       #endif
    }

    /** ********************************************************************************************
     * Overloaded version of #Entry, defaulting parameter \p domain to a nulled string.
     *
     * @param verbosity     The verbosity.
     * @param logable       The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Entry( Verbosity       verbosity,
                      Object          logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Entry( null, verbosity, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable using \ref Verbosity::Verbose.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Verbose( String domain, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Entry( domain, Verbosity.Verbose, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of #Verbose, defaulting parameter \p domain to a nulled string.
     *
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Verbose( Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Entry( null, Verbosity.Verbose, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable using \ref Verbosity::Info.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Info( String domain, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Entry( domain, Verbosity.Info, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of #Info, defaulting parameter \p domain to a nulled string.
     *
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Info( Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Entry(  null, Verbosity.Info, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable using \ref Verbosity::Warning.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Warning( String domain, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Entry( domain, Verbosity.Warning, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of #Warning, defaulting parameter \p domain to a nulled string.
     *
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Warning( Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Entry( null, Verbosity.Warning, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable using \ref Verbosity.Error.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Error( String domain, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Entry( domain, Verbosity.Error, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of #Error, defaulting parameter \p domain to a nulled string.
     *
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Error( Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            Entry( null, Verbosity.Error, logable, cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable once, up to \p quantity times or every n-th time.
     * In its simplest overloaded version, the counter is bound to the source code line, hence,
     * only the first execution of this exact <em>Log Statement</em> is executed.
     *
     * Using parameter \p group, a set of <em>Log Statements</em> that share the same group key, can be
     * grouped and of such set, only the one which is first executed actually logs.<br>
     * Alternatively, when \p key is omitted (or null or empty), but a
     * \ref cs::aworx::lox::Scope "Scope" is given with parameter \p scope, then the
     * counter is associated with the scope.<br>
     * Finally, parameters \p key and \p scope can also be used in combination. The key is
     * then unique in respect to the \ref cs::aworx::lox::Scope "Scope" provided.
     *
     * Using, none, one or both of the parameters \p group and \p scope, among others, the
     * following use cases can be achieved.
     * - %Log a specific statement up to n-times.
     * - %Log only the first n of a group of statements.
     * - %Log only the first n statements within a method.
     * - %Log only the first n statements belonging to the same group and method .
     * - %Log only the first n statements within any method of
     *   - a source file
     *   - a directory of source files
     *   - a parent directory of source files and all sources recursively
     * - %Log only the first n statements which belong to the same group and are placed within
     *   any method of
     *   - a source file
     *   - a directory of source files
     *   - a parent directory of source files and all sources recursively
     * - %Log a <em>Log Statement</em> n-times per new thread.
     * - %Log only the first n statements of a group of statements executed by a specific thread.
     *
     * When parameter \p quantity is a negative value, the log statement is executed every n-th time
     * instead n-times. E.g, if \p quantity is \c -5, the first statement is executed and afterwards
     * every fifth invocation.
     *
     * \note C# autoboxes parameter values of type 'int', which leads to ambiguous statements.
     *       This is why all %Once methods are doubled with a String-type parameter \p logable.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope::Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *                  If negative, the first and every "-quantity-th" statement is executed.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once( String domain, Verbosity verbosity, Object logable,
                      String group,
                      Scope scope= Scope.Global , int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( domain, verbosity, logable, group, scope, pathLevel, quantity,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log..
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                        Verbosity verbosity, Object logable,
                      String group,
                      Scope scope, int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, verbosity, logable, group, scope, pathLevel, quantity,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log..
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                        Verbosity verbosity, Object logable,
                      String group,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, verbosity, logable, group, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log..
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                        Verbosity verbosity, Object logable,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, verbosity, logable, null, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The object to log..
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                                          Object logable,
                      String group,
                      Scope scope, int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, Verbosity.Info, logable, group, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log..
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once( String domain, Verbosity verbosity, Object logable,
                      Scope scope= Scope.Global , int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( domain, verbosity, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The object to log..
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                        Verbosity verbosity, Object logable,
                      Scope scope, int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, verbosity, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The object to log..
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                                          Object logable,
                      Scope scope, int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, Verbosity.Info, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The object to log..
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                                          Object logable,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, Verbosity.Info, logable, null, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The object to log..
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                                          Object logable,
                      String group, int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, Verbosity.Info, logable, group, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * \note C# autoboxes parameter values of type 'int', which leads to ambiguous statements.
     *       This is why all %Once methods are doubled with a String-type parameter \p logable.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope::Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once( String domain, Verbosity verbosity, String logable,
                      String group,
                      Scope scope= Scope.Global , int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( domain, verbosity, logable, group, scope, pathLevel, quantity,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                        Verbosity verbosity, String logable,
                      String group,
                      Scope scope, int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, verbosity, logable, group, scope, pathLevel, quantity,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                        Verbosity verbosity, String logable,
                      String group,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, verbosity, logable, group, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                        Verbosity verbosity, String logable,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, verbosity, logable, null, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The string message to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                                          String logable,
                      String group,
                      Scope scope, int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, Verbosity.Info, logable, group, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once( String domain, Verbosity verbosity, String logable,
                      Scope scope= Scope.Global , int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( domain, verbosity, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string message to log.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                        Verbosity verbosity, String logable,
                      Scope scope, int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, verbosity, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The string message to log.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                                          String logable,
                      Scope scope, int pathLevel= 0,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, Verbosity.Info, logable, null, scope, pathLevel, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The string message to log.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                                          String logable,
                      int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, Verbosity.Info, logable, null, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Overloaded version of \ref Once.
     *
     * @param logable   The string message to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public void Once(                                          String logable,
                      String group, int quantity= 1,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            once( null, Verbosity.Info, logable, group, Scope.Global, 0, quantity ,   cln,csf,cmn );
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is not \c true.
     * If executed, \ref Verbosity.Error is used.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Assert( bool condition, String domain, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            if ( !condition )
                Entry( domain, Verbosity.Error, logable, cln,csf,cmn );
            else
            {
                CntLogCalls++;
                if ( logable == logBuf )
                    logBufLock.Release();
            }

        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is not \c true.
     * If executed, \ref Verbosity.Error is used.
     *
     * This overloaded version omits parameter \p domain.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void Assert( bool condition, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            if ( !condition )
                Entry( null, Verbosity.Error, logable, cln,csf,cmn );
            else
            {
                CntLogCalls++;
                if ( logable == logBuf )
                    logBufLock.Release();
            }
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is \c true.
     *
     * \see Method #Assert.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void If( bool condition, String domain, Verbosity verbosity, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            if ( condition )
                Entry( domain, verbosity, logable, cln,csf,cmn );
            else
            {
                CntLogCalls++;
                if ( logable == logBuf )
                    logBufLock.Release();
            }
        #endif
    }

    /** ********************************************************************************************
     * Logs a \e Logable only if the parameter \p condition is \c true.
     * This overloaded version omits parameter \p domain.
     *
     * \see Method #Assert.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param verbosity The verbosity.
     * @param logable   The object to log.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    [Conditional("ALOX_DBG_LOG"), Conditional("ALOX_REL_LOG")]
    public  void If( bool condition, Verbosity verbosity, Object logable,
    [CallerLineNumber] int cln= 0,[CallerFilePath] String csf="",[CallerMemberName] String cmn="" )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
            if ( condition )
                Entry( null, verbosity, logable, cln,csf,cmn );
            else
            {
                CntLogCalls++;
                if ( logable == logBuf )
                    logBufLock.Release();
            }
        #endif
    }

    // #############################################################################################
    // internals
    // #############################################################################################
    #if ALOX_DBG_LOG || ALOX_REL_LOG

        /** ****************************************************************************************
         * Assembles the resulting domain from the given \p domainPath and the Scope Domain paths
         * (see #SetDomain) according to the scope identified by \p scopeInfo.
         * The resulting full domain string is assembled from inner to outer scope.
         * If \p domainPath, respectively as soon as any of the scope levels' Scope Domain paths
         * starts with the character defined in
         * \ref cs::aworx::lox::core::Domain::Separator "Domain.Separator",
         * the evaluation is stopped (the path is interpreted as absolute).
         *
         * @param domainPath The domain path. If starting with the character defined in
         *                   \ref cs::aworx::lox::core::Domain::Separator "Domain.Separator",
         *                   no Scope Domains are applied.
         * @return The resulting \ref cs::aworx::lox::core::Domain "Domain".
         ******************************************************************************************/
        protected  Domain evaluateResultDomain( String domainPath )
        {
            // 0. internal domain tree?
            if ( domainPath != null && domainPath.StartsWith( ALox.InternalDomains ) )
            {
                // cut "$/" from the path
                resDomain._()._(domainPath, ALox.InternalDomains.Length ).Trim();
                return findDomain( internalDomains, resDomain );
            }

            // loop over scopes
            scopeDomains.InitWalk( Scope.ThreadInner,
                                   // we have to provide null if parameter is empty
                                   String.IsNullOrEmpty( domainPath ) ? null
                                                                      : tmpAS._()._NC(domainPath) );
            AString nextDefault;
            resDomain._();
            while( (nextDefault= (AString) scopeDomains.Walk() ) != null )
            {
                if (resDomain.IsNotEmpty() )
                    resDomain.InsertAt( "/", 0);
                resDomain.InsertAt( nextDefault, 0 );

                // absolute path? That's it
                if ( resDomain.CharAtStart() == Domain.Separator )
                    break;
            }
           return findDomain( domains, resDomain );
        }

        /** ****************************************************************************************
         * Invokes \b Find on the given domain and logs internal message when the domain was
         * not known before.
         *
         * @param domainSystem  The domain system. Either the standard or the internal one.
         * @param domainPath    The domain path.
         * @return The resulting \ref cs::aworx::lox::core::Domain "Domain".
         ******************************************************************************************/
        Domain findDomain( Domain domainSystem, AString domainPath )
        {
            AString substPath= domainSystem == domains ? tmpSubstitutionPath
                                                       : tmpSubstitutionPathInternalDomains;

            int maxSubstitutions= 10;
            for(;;)
            {
                // loop for creating domains, one by one
                Domain dom= null;
                for(;;)
                {
                    bool wasCreated= false;
                    dom= domainSystem.Find( domainPath, DomainSensitivity, 1, ref wasCreated );

                    if ( wasCreated )
                    {
                        // get maximum domain path length (for nicer State output only...)
                        if ( maxDomainPathLength < dom.FullPath.Length() )
                            maxDomainPathLength=   dom.FullPath.Length();

                        // log info on new domain
                        intMsg._()._('\'')._NC( dom.FullPath )._NC("' registered.");
                        logInternal( Verbosity.Info, "DMN", intMsg );
                    }

                    // read domain from Config
                    if ( !dom.ConfigurationRead )
                    {
                        dom.ConfigurationRead= true;

                        Variable variable= new Variable();
                        for ( int i= 0; i < dom.CountLoggers(); ++i )
                        {
                            Logger logger= dom.GetLogger(i);
                            if ( 0 != variable.Define( ALox.VERBOSITY, GetName(), logger.GetName() ).Load() )
                                getVerbosityFromConfig( logger, dom, variable );
                        }

                        getDomainPrefixFromConfig( dom );
                    }

                    // log inherited setting for each logger
                    if ( wasCreated )
                    {
                        if ( domainSystem.CountLoggers() == 0 )
                            logInternal( Verbosity.Verbose, "DMN", intMsg._()._NC("No loggers set, yet.") );
                        else
                            for ( int i= 0; i < domainSystem.CountLoggers(); i++ )
                            {
                                intMsg._()._("  \"")._( dom.GetLogger(i).GetName() )._NC("\":");
                                intMsg.InsertChars( ' ', maxLoggerNameLength  + 6 - intMsg.Length() );
                                intMsg._NC( dom.FullPath )
                                      ._NC( " = " ); ALox.ToString( dom.GetVerbosity( i ), dom.GetPriority( i), intMsg );

                                logInternal( Verbosity.Verbose, "DMN", intMsg );
                            }
                    }
                    else
                        break;
                }

                // apply domain substitutions
                if( domainSubstitutions.Count > 0 )
                {
                    substPath.Clear();
                    while( maxSubstitutions-- > 0  )
                    {
                        // loop over rules
                        bool substituted= false;
                        foreach( DomainSubstitutionRule rule in domainSubstitutions )
                        {
                            switch( rule.type )
                            {
                                case DomainSubstitutionRule.Type.StartsWith:
                                    if( substPath.IsEmpty() )
                                    {
                                        if ( dom.FullPath.StartsWith( rule.Search, DomainSensitivity ) )
                                        {
                                            substPath._( rule.Replacement )._( dom.FullPath, rule.Search.Length() );
                                            substituted= true;
                                            continue; //next rule
                                        }
                                    }
                                    else
                                    {
                                        if ( substPath.StartsWith( rule.Search, DomainSensitivity ) )
                                        {
                                            substPath.ReplaceSubstring( rule.Replacement, 0, rule.Search.Length()  );
                                            substituted= true;
                                            continue; //next rule
                                        }
                                    }
                                break;

                                case DomainSubstitutionRule.Type.EndsWith:
                                    if( substPath.IsEmpty() )
                                    {
                                        if ( dom.FullPath.EndsWith( rule.Search, DomainSensitivity ) )
                                        {
                                            substPath._( dom.FullPath, 0, dom.FullPath.Length() - rule.Search.Length() )._( rule.Replacement );
                                            substituted= true;
                                            continue;
                                        }
                                    }
                                    else
                                    {
                                        if ( substPath.EndsWith( rule.Search, DomainSensitivity ) )
                                        {
                                            substPath.DeleteEnd( rule.Search.Length() )._( rule.Replacement );
                                            substituted= true;
                                            continue;
                                        }
                                    }
                                break;


                                case DomainSubstitutionRule.Type.Substring:
                                    if( substPath.IsEmpty() )
                                    {
                                        int idx= dom.FullPath.IndexOf( rule.Search, 0, DomainSensitivity );
                                        if ( idx >= 0 )
                                        {
                                            substPath._( dom.FullPath, 0, idx )._( rule.Replacement)._( dom.FullPath, idx + rule.Search.Length() );
                                            substituted= true;
                                            continue; //next rule
                                        }
                                    }
                                    else
                                    {
                                        int idx= substPath.IndexOf( rule.Search, 0, DomainSensitivity );
                                        if ( idx >= 0 )
                                        {
                                            substPath.ReplaceSubstring( rule.Replacement, idx, rule.Search.Length()  );
                                            substituted= true;
                                            continue; //next rule
                                        }
                                    }
                                break;

                                case DomainSubstitutionRule.Type.Exact:
                                {
                                    if( substPath.IsEmpty() )
                                    {
                                        if ( dom.FullPath.Equals( rule.Search ) )
                                        {
                                            substPath._( rule.Replacement);
                                            substituted= true;
                                            continue; //next rule
                                        }
                                    }
                                    else
                                    {
                                        if ( substPath.Equals( rule.Search) )
                                        {
                                            substPath._()._( rule.Replacement );
                                            substituted= true;
                                            continue; //next rule
                                        }
                                    }
                                }
                                break;

                            } // switch rule type

                        }//rules loop

                        // stop if non was found
                        if( !substituted )
                            break;
                    }

                    // too many substitutions?
                    if ( maxSubstitutions <= 0 && !oneTimeWarningCircularDS )
                    {
                        oneTimeWarningCircularDS= true;
                        intMsg._()._(   "The Limit of 10 domain substitutions was reached. Circular substitution assumed!"
                                      + " (This error is only reported once!)" );

                        logInternal( Verbosity.Error, "DMN", intMsg );
                    }

                    // anything substituted?
                    if( substPath.Length() > 0 )
                    {
                        domainPath= substPath;
                        continue;
                    }
                }

                return dom;
            }
        }

        /** ****************************************************************************************
         * This method is looping over the \e Loggers, checking their verbosity against the given
         * one, and, if they match, invoke the log method of the \e Logger.
         * With the first logger identified to be active, the <em>Prefix Objects</em> get
         * collected from the scope store.
         * @param dom       The domain to log on
         * @param verbosity The verbosity.
         * @param logable   The object to log.
         * @param prefixes  Denotes if prefixes should be included or not.
         ******************************************************************************************/
        protected void log( Domain dom, Verbosity verbosity, Object logable, Inclusion prefixes )
        {
            // OK, this is a little crude, but the simplest solution: As class ScopeStore sees
            // null objects as nothing and won't return them in a walk, we replace null by
            // an object (we choose the store itself) and fix this in the loop back to null
            if ( logable == null )
                logable= scopePrefixes;

            dom.CntLogCalls++;
            logObjects.Clear();
            for ( int i= 0; i < dom.CountLoggers() ; i++ )
                if( dom.IsActive( i, verbosity ) )
                {
                    // lazily collect objects once
                    if ( logObjects.Count == 0 )
                    {
                        scopePrefixes.InitWalk( Scope.ThreadInner, logable );
                        Object next;
                        while( (next= scopePrefixes.Walk() ) != null )
                        {
                            if ( prefixes == Inclusion.Include || next == logable)
                                logObjects.Insert( 0, next != scopePrefixes ? next : null );

                            // was this the actual? then insert domain-associated logables now
                            bool excludeOthers= false;
                            if( next == logable )
                            {
                                int qtyThreadInner= logObjects.Count -1;
                                Domain pflDom= dom;
                                while ( pflDom != null )
                                {
                                    for( int ii= pflDom.PrefixLogables.Count -1 ; ii >= 0 ; ii-- )
                                    {
                                        Domain.PL pl= pflDom.PrefixLogables[ii];
                                        logObjects.Insert( 0,  pl.Logable );
                                        if ( pl.IncludeOtherPLs == Inclusion.Exclude )
                                        {
                                            excludeOthers= true;
                                            break;
                                        }
                                    }

                                    pflDom= excludeOthers ? null :  pflDom.Parent;
                                }

                                // found a stoppable one? remove those from thread inner and break
                                if (excludeOthers)
                                {
                                    for ( int ii= 0; ii < qtyThreadInner ; ii++ )
                                        logObjects.RemoveAt( logObjects.Count - 1 );
                                    break;
                                }
                            }
                        }
                    }

                    Logger logger= dom.GetLogger(i);
                    logger.Acquire();
                        logger.CntLogs++;
                        logger.Log( dom, verbosity, logObjects, scopeInfo );
                        logger.TimeOfLastLog.Set();
                    logger.Release();
                }
        }

        /** ****************************************************************************************
         * Logs an internal error message using the internal domain tree as defined in
         * \ref cs::aworx::lox::ALox::InternalDomains "ALox.InternalDomains".
         *
         * @param verbosity The verbosity.
         * @param subDomain The sub-domain of the internal domain to log into.
         * @param logable   The message.
         ******************************************************************************************/
        protected  void logInternal( Verbosity verbosity, String subDomain, AString logable )
        {
            log( findDomain( internalDomains, resDomainInternal._()._NC( subDomain ) ),
                 verbosity, logable, Inclusion.Exclude );
        }

    /** ********************************************************************************************
     * Implementation of the interface method fetching all possible parameters.
     *
     * @param scopeDomain The domain path to register.
     * @param scope       The scope that the given \p domain should be registered for.
     *                    Available Scope definitions are platform/language dependent.
     * @param pathLevel   Used only with
     *                    \ref cs::aworx::lox::Scope::Path "Scope.Path".
     *                    Cuts the given number of directories from the end of the source path.
     * @param removeNTRSD Used to remove thread-related Scope Domains (and is true only when
     *                    invoked by interface method #RemoveThreadDomain.
     * @param thread      The thread to set/unset a thread-related Scope Domain for.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    protected void setDomainImpl( String scopeDomain,  Scope    scope,   int pathLevel,
                                  bool   removeNTRSD,  Thread   thread,
                                  int cln,String csf,String cmn )
    {
        //note: the public class interface assures that \p removeNTRSD (named thread-related
        //      scope domain) only evaluates true for thread related scopes
        try { Acquire();

            scopeInfo.Set( cln,csf,cmn, owner );

            if( !checkScopeInformation( scope, pathLevel, "DMN" ) )
                return;

            bool newValueIsNotEmpty =     scopeDomain != null
                                       && scopeDomain.Length > 0;

            AString previousScopeDomain;
            scopeDomains.InitAccess( scope, pathLevel, thread );
            if ( removeNTRSD )
            {
                AString searchedValue= new AString( scopeDomain );
                previousScopeDomain= (AString) scopeDomains.Remove( searchedValue );
            }
            else
            {
                if ( newValueIsNotEmpty )
                {
                    AString newValue= new AString( scopeDomain);
                    newValue.Trim();
                    previousScopeDomain= (AString) scopeDomains.Store ( newValue  );
                }
                else
                    previousScopeDomain= (AString) scopeDomains.Remove( null );
            }

            // log info on this
            if ( !removeNTRSD && newValueIsNotEmpty )
            {
                intMsg._()._( '\'' )._NC( scopeDomain )
                          ._NC( "\' set as default for "   );
                ALox.ToString( scope, pathLevel, intMsg )._( '.' );

                if ( previousScopeDomain == null )
                    logInternal(  Verbosity.Info,     "DMN", intMsg );
                else
                {
                    if ( previousScopeDomain.Equals( scopeDomain ) )
                    {
                        intMsg._( " (Was already set.)" );
                        logInternal(  Verbosity.Verbose,  "DMN", intMsg );
                    }
                    else
                    {
                        intMsg._NC( " Replacing previous default '" )._NC( previousScopeDomain )._('\'');
                        logInternal(  Verbosity.Warning,  "DMN", intMsg );
                    }

                }
            }
            else
            {
                if ( previousScopeDomain != null )
                {
                    intMsg._()._('\'')._NC( previousScopeDomain )
                              ._NC( "\' removed from " ); ALox.ToString( scope, pathLevel, intMsg )._( '.' );
                    logInternal( Verbosity.Info, "DMN", intMsg );
                }
                else
                {
                    intMsg._();
                    if ( removeNTRSD )
                        intMsg._('\'')._NC( scopeDomain )._NC( "\' not found. Nothing removed for " );
                    else
                        intMsg._NC( "Empty Scope Domain given, nothing registered for " );
                    ALox.ToString( scope, pathLevel, intMsg )._( '.' );

                    logInternal( Verbosity.Warning, "DMN", intMsg );
                }
            }

        } finally { Release(); }
    }

    /** ****************************************************************************************
     * Implementation of the interface method fetching all possible parameters.
     *
     * @param logable     The <em>Prefix Logable</em> to set.
     * @param scope       The scope that the given \p logable should be registered for.
     *                    Available Scope definitions are platform/language dependent.
     * @param pathLevel   Used only if parameter \p scope equals
     *                    \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                    to reference parent directories.
     * @param thread      The thread to set/unset a thread-related <em>Prefix Logable</em> for.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    protected void setPrefixImpl( Object  logable, Scope scope, int pathLevel, Thread thread,
                                  int cln,String csf,String cmn )
    {
        try { Acquire();

            scopeInfo.Set( cln,csf,cmn, owner );

            if( !checkScopeInformation( scope, pathLevel, "PFX" ) )
                return;

            // check if the LogBuf singleton of static class Log was used
            if( logable == logBuf )
                logable= logBuf.ToString();

            // store new prefix for this scope (and get current)
            Object previousLogable;
            scopePrefixes.InitAccess ( scope, pathLevel, thread );
            if ( logable != null )
                previousLogable= scopePrefixes.Store ( logable );
            else
                previousLogable= scopePrefixes.Remove( null );


            // log info on this
            intMsg._()._NC( "Object ");
            Verbosity intMsgVerbosity= Verbosity.Info;
            if ( logable != null )
            {
                intMsg._( '\"' )._( logable )._( '\"' )
                      ._NC( " set as prefix logable for "); ALox.ToString(scope, pathLevel, intMsg); intMsg._( '.') ;

                if ( previousLogable  != null )
                {
                    if (      logable == previousLogable
                         || ( logable is String  && previousLogable is String && logable.Equals( previousLogable ))
                        )
                    {
                        intMsg._NC( " (Same as before.)" );
                        intMsgVerbosity= Verbosity.Verbose;
                    }
                    else
                       intMsg ._NC( " Replacing previous \"" )._( previousLogable )._NC( "\"." );
                }
            }
            else
            {
                if ( previousLogable  != null )
                {
                    intMsg._( '\"' )._( previousLogable )._( '\"' )
                          ._NC( " removed from list of prefix logables for " ) ; ALox.ToString(scope, pathLevel, intMsg); intMsg ._( '.' );
                }
                else
                {
                    intMsg._NC( "<null> given but no prefix logable to remove for " );
                    ALox.ToString(scope, pathLevel, intMsg); intMsg._( '.' );
                }
            }
            logInternal( intMsgVerbosity, "PFX", intMsg );

        } finally { Release(); }
    }

    /** ********************************************************************************************
     * Checks if given scope is thread-related.
     *
     * @param scope     The scope that is to be checked.
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     * @return \c true if \p scope is thread-related, \c false else.
     **********************************************************************************************/
    protected bool isThreadReleatedScope( Scope scope, int cln,String csf,String cmn )
    {
        if (    scope == Scope.ThreadOuter
             || scope == Scope.ThreadInner )
            return true;

        intMsg._()
            ._NC( "Illegal parameter, only Scope.ThreadOuter and Scope.ThreadInner allowed." )
            ._NC( " Given: " );
        ALox.ToString(scope, 0, intMsg); intMsg._( '.' );
        logInternal( Verbosity.Error, "DMN", intMsg );

        ALIB.ERROR( "Illegal parameter, only Scope.ThreadOuter and Scope.ThreadInner allowed.",
                    cln,csf,cmn );

        return false;
    }

    /** ********************************************************************************************
     * Checks if given scope needs information that is not available.
     *
     * @param scope            The scope that is to be checked.
     * @param pathLevel        Used only with
     *                         \ref cs::aworx::lox::Scope::Path "Scope.Path".
     *                         Cuts the given number of directories from the end of the source path.
     * @param internalDomain   The internal sub-domain to log any error/warning into.
     *
     * @return \c true if all is fine, \c false else.
     **********************************************************************************************/
    protected bool checkScopeInformation( Scope scope, int pathLevel, String internalDomain )
    {
        if (     ( scope == Scope.Path     &&  scopeInfo.GetTrimmedPath().IsEmpty() )
             ||  ( scope == Scope.Filename &&  scopeInfo.GetFileName()   .IsEmpty() )
             ||  ( scope == Scope.Method   &&  scopeInfo.GetMethod().Length == 0    ) )
        {
            intMsg._()
                ._NC( "Missing scope information. Can't use " );
                ALox.ToString(scope, pathLevel, intMsg);
            intMsg._( '.' );
            logInternal( Verbosity.Error, internalDomain, intMsg );
            return false;
        }
        return true;
    }

    /** ********************************************************************************************
     * Internal implementation of Once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logable   The string to log.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p scope.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p scope is Scope::Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pathLevel Used only if parameter \p scope equals
     *                  \ref cs::aworx::lox::Scope::Path "Scope.Path"
     *                   to reference parent directories. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *
     * @param cln (Optional) Caller info, compiler generated. Please omit.
     * @param csf (Optional) Caller info, compiler generated. Please omit.
     * @param cmn (Optional) Caller info, compiler generated. Please omit.
     **********************************************************************************************/
    protected void once( String domain, Verbosity verbosity, Object logable,
                         String group, Scope scope, int pathLevel,int quantity,
                         int cln,String csf,String cmn )
    {
        #if ALOX_DBG_LOG || ALOX_REL_LOG
        try { Acquire();

            scopeInfo.Set( cln,csf,cmn, owner );

            // We need a group. If none is given, there are two options:
            tmpAS._()._(group);
            bool groupWasEmtpy;
            if ( (groupWasEmtpy= tmpAS.IsEmpty()) )
            {
                // GLOBAL scope: exact code line match match
                if ( scope == Scope.Global )
                {
                    scope= Scope.Filename;
                    tmpAS._('#')._NC( scopeInfo.GetLineNumber() );
                }
                // not GOBAL scope: Unique tempAS per Scope
                else
                    tmpAS._( noKeyHashKey );
            }

            // get the store
            scopeLogOnce.InitAccess( scope, pathLevel, null );
            Dictionary<AString, int[]> map=  scopeLogOnce.Get();
            if( map == null )
            {
                map= new Dictionary<AString, int[]>();
                scopeLogOnce.Store( map );
            }

            int[] qty= null;
            if ( !map.TryGetValue( tmpAS, out qty ) )
                map[ new AString( tmpAS )]=  ( qty= new int[1] );

            // log Once
            if ( quantity >= 0 )
            {
                if ( qty[0] < quantity )
                {
                    qty[0]++;

                    // do the log
                    Entry( domain, verbosity, logable, cln,csf,cmn );

                    // log info if this was the last time
                    if( qty[0] == quantity )
                    {
                        intMsg._()
                              ._NC( "Once() reached limit of "    )._( quantity )
                              ._NC( " logs. No further logs for " );

                        if ( groupWasEmtpy )
                        {
                            if ( scope == Scope.Global )
                                intMsg._NC( "this line" );
                            else
                                ALox.ToString(scope, pathLevel, intMsg);
                        }
                        else
                        {
                            intMsg._NC( "group \"" )._NC( tmpAS )._( '\"' );
                            if ( scope != Scope.Global )
                            {
                                intMsg._NC( " in " );
                                ALox.ToString(scope, pathLevel, intMsg);
                            }
                        }
                        intMsg._( '.' );

                        logInternal( Verbosity.Info, "", intMsg );
                    }
                }
                else
                {
                    if ( logable == logBuf )
                        logBufLock.Release();
                }
            }

            // log Nth
            else
            {
                if ( qty[0]++ % -quantity == 0 )
                    Entry( domain, verbosity, logable, cln,csf,cmn );
                else
                {
                    if ( logable == logBuf )
                        logBufLock.Release();
                }
            }


        } finally { Release(); }
        #endif
    }

    /** ****************************************************************************************
     * Reads the verbosity for the given logger and domain from the ALib configuration system.
     * This internal method is used in two occasions:
     * - when a new logger is added: recursively for all existing domains (\p configStr is
     *   given)
     * - when a new domain is created on the fly(\p configStr is not given)
     *
     * @param logger      The logger to set the verbosity for.
     * @param dom         The domain to set the verbosity for.
     * @param variable    The (already read) variable to set verbosities from.
     ******************************************************************************************/
    protected void  getVerbosityFromConfig( Logger  logger,  Domain  dom, Variable variable  )
    {
        // get logger number. It may happen that the logger is not existent in this domain tree.
        int loggerNo= dom.GetLoggerNo( logger ) ;
        if ( loggerNo < 0 )
            return;

        Tokenizer verbosityTknzr=   new Tokenizer();
        Substring domainStr=      new Substring();
        AString   domainStrBuf=   new AString();
        for( int varNo= 0; varNo< variable.Size(); varNo++ )
        {
            verbosityTknzr.Set( variable.GetString( varNo ), '=' );

            domainStr.Set( verbosityTknzr.Next() );
            if ( domainStr.StartsWith( "INTERNAL_DOMAINS", DomainSensitivity ) )
            {
                domainStrBuf._()._( domainStr.Buf, domainStr.Start + 16, domainStr.Length() -16 );
                while ( domainStrBuf.CharAtStart() == '/' )
                    domainStrBuf.DeleteStart( 1 );
                domainStrBuf.InsertAt( ALox.InternalDomains, 0 );
                domainStr.Set( domainStrBuf );
            }

            Substring verbosityStr=  verbosityTknzr.Next();
            if ( verbosityStr.IsEmpty() )
                continue;

            int searchMode= 0;
            if ( domainStr.Consume       ( '*' ) )    searchMode+= 2;
            if ( domainStr.ConsumeFromEnd( '*' ) )    searchMode+= 1;
            if(     ( searchMode == 0 && dom.FullPath.Equals          ( domainStr,    DomainSensitivity )     )
                ||  ( searchMode == 1 && dom.FullPath.StartsWith      ( domainStr,    DomainSensitivity )     )
                ||  ( searchMode == 2 && dom.FullPath.EndsWith        ( domainStr,    DomainSensitivity )     )
                ||  ( searchMode == 3 && dom.FullPath.IndexOf         ( domainStr, 0, DomainSensitivity ) >=0 )
                )
            {
                Verbosity verbosity= ALox.ReadVerbosity( verbosityStr);
                dom.SetVerbosity( loggerNo, verbosity, variable.Priority );

                // log info on this
                intMsg._()._NC( "Logger \"" )._NC( logger.GetName() ) ._NC( "\":" ).Tab(11 + maxLoggerNameLength)
                          ._( '\'' )._NC( dom.FullPath )
                          ._( '\'' ).InsertChars(' ', maxDomainPathLength - dom.FullPath.Length() + 1 )
                          ._("= Verbosity." );
                          ALox.ToString( verbosity, dom.GetPriority(loggerNo), intMsg ).TrimEnd()
                          ._('.');
                logInternal( Verbosity.Info, "LGR", intMsg );
            }
        }
    }

    /** ****************************************************************************************
     * Reads a prefix string from the ALib configuration system.
     * This internal method is used when a new domain is created,
     *
     * @param dom         The domain to set the verbosity for.
     ******************************************************************************************/
    protected void  getDomainPrefixFromConfig( Domain  dom )
    {
        Variable variable= new Variable( ALox.PREFIXES, GetName() );
        if( 0 == variable.Load() )
            return;

        Tokenizer prefixTok=        new Tokenizer();
        Tokenizer prefixTokInner=   new Tokenizer();
        Substring domainStr=        new Substring();
        AString   domainStrBuf=     new AString();
        Substring prefixStr=        new Substring();
        for( int varNo= 0; varNo< variable.Size(); varNo++ )
        {
            prefixTok.Set( variable.GetString( varNo ), '=' );

            domainStr.Set( prefixTok.Next() );
            if ( domainStr.StartsWith( "INTERNAL_DOMAINS", DomainSensitivity ) )
            {
                domainStrBuf._()._( domainStr.Buf, domainStr.Start + 16, domainStr.Length() -16 );
                while ( domainStrBuf.CharAtStart() == '/' )
                    domainStrBuf.DeleteStart( 1 );
                domainStrBuf.InsertAt( ALox.InternalDomains, 0 );
                domainStr.Set( domainStrBuf );
            }

            prefixTokInner.Set( prefixTok.Next(), ',' );
            prefixStr.Set( prefixTokInner.Next() );
            if ( prefixStr.IsEmpty() )
                continue;
            if ( prefixStr.Consume( '\"' ) )
                prefixStr.ConsumeFromEnd( '\"' );

            Inclusion otherPLs= Inclusion.Include;
            prefixTokInner.Next();
            if ( prefixTokInner.Actual.IsNotEmpty() )
                otherPLs= ALIB.ReadInclusion( prefixTokInner.Actual  );

            int searchMode= 0;
            if ( domainStr.Consume       ( '*' ) )    searchMode+= 2;
            if ( domainStr.ConsumeFromEnd( '*' ) )    searchMode+= 1;
            if(     ( searchMode == 0 && dom.FullPath.Equals          ( domainStr,    DomainSensitivity )     )
                ||  ( searchMode == 1 && dom.FullPath.StartsWith      ( domainStr,    DomainSensitivity )     )
                ||  ( searchMode == 2 && dom.FullPath.EndsWith        ( domainStr,    DomainSensitivity )     )
                ||  ( searchMode == 3 && dom.FullPath.IndexOf         ( domainStr, 0, DomainSensitivity ) >=0 )
                )
            {
                dom.PrefixLogables.Add( new Domain.PL( new AString( prefixStr ), otherPLs ) );

                // log info on this
                intMsg._()._NC( "String \"" )._NC( prefixStr )._NC ( "\" added as prefix logable for domain \'" )
                          ._NC( dom.FullPath )
                          ._NC( "\'. (Retrieved from variable" )
                          ._NC( variable.Fullname )._( ".)" );
                logInternal( Verbosity.Info, "PFX", intMsg );
            }
        }
    }


    /** ****************************************************************************************
     * Reads the verbosity for the given logger and domain from the ALib configuration system.
     * This internal method is used when a new logger is added.
     * Walks recursively for all existing domains.
     *
     * @param logger      The logger to set the verbosity for.
     * @param dom         The domain to set the verbosity for.
     * @param cfgResult   The result of the search for the variable to set verbosities from.
     ******************************************************************************************/
    protected void getAllVerbosities      ( Logger  logger,  Domain  dom,  Variable cfgResult )
    {
        // get verbosity for us
        getVerbosityFromConfig( logger, dom, cfgResult );

        // loop over all sub domains (recursion)
        foreach ( Domain subDomain in dom.SubDomains )
            getAllVerbosities( logger, subDomain, cfgResult );
    }

    #endif // ALOX_DBG_LOG || ALOX_REL_LOG
}


} // namespace
