// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

/** ************************************************************************************************
 *  This is the Java package for code of the <b>%ALox Logging Library</b>.
 *  Developed by A-Worx GmbH and published under Boost Software License.
 **************************************************************************************************/
package com.aworx.lox;

import java.text.FieldPosition;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Locale;
import java.util.Vector;

import com.aworx.lib.ALIB;
import com.aworx.lib.config.Configuration;
import com.aworx.lib.config.Variable;
import com.aworx.lib.lang.Alignment;
import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.ContainerOp;
import com.aworx.lib.lang.Inclusion;
import com.aworx.lib.lang.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.util.Tokenizer;
import com.aworx.lib.threads.ThreadLock;
import com.aworx.lib.time.Ticks;
import com.aworx.lox.detail.Domain;
import com.aworx.lox.detail.Logger;
import com.aworx.lox.detail.ScopeDump;
import com.aworx.lox.detail.ScopeInfo;
import com.aworx.lox.detail.ScopeStore;
import com.aworx.lox.detail.textlogger.TextLogger;
import com.aworx.lox.loggers.AnsiConsoleLogger;
import com.aworx.lox.loggers.ConsoleLogger;

/** ************************************************************************************************
 * This class acts as a container for Loggers and provides a convenient interface to logging.
 * Fore information how to use this class, checkout the \b %ALox tutorials and the
 * [ALox User Manual](../manual.html).
 **************************************************************************************************/
public class Lox extends ThreadLock
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

        /**
         * A counter for the quantity of calls. The count includes logs that were suppressed by
         * disabled <em>Log Domain</em> and those suppressed by the optional log condition parameter.
         */
        public int                  cntLogCalls                                                 = 0;

        /**
         * A list of prefixes of \e 'packages.classes.methods' on the stack that are ignored when
         * identifying the scope info.
         * Usually this contains \e "com.aworx.lox" and \e "com.aworx.lib" and there is no need
         * to change this.
         */
        public Vector<String>       omittablePackagePrefixes;

        public final static int STATE_INFO_BASIC             = 1 <<  0; ///< Name and number of log calls
        public final static int STATE_INFO_VERSION           = 1 <<  1; ///< Library Version and thread safeness
        public final static int STATE_INFO_LOGGERS           = 1 <<  2; ///< Loggers

        public final static int STATE_INFO_DOMAINS           = 1 <<  3; ///< Domains currently registered
        public final static int STATE_INFO_INTERNAL_DOMAINS  = 1 <<  4; ///< Internal domains
        public final static int STATE_INFO_SCOPE_DOMAINS     = 1 <<  5; ///< Scope domains
        public final static int STATE_INFO_DSR               = 1 <<  6; ///< Domain substitution rules
        public final static int STATE_INFO_PREFIX_LOGABLES   = 1 <<  7; ///< Prefix logables
        public final static int STATE_INFO_ONCE              = 1 <<  8; ///< Log once counters
        public final static int STATE_INFO_LOG_DATA          = 1 <<  9; ///< Log data objects
        public final static int STATE_INFO_THREAD_MAPPINGS   = 1 << 10; ///< Named threads

        public final static int STATE_INFO_ALL               = ~0;      ///< All information available

    // #############################################################################################
    // Private/protected fields
    // #############################################################################################

    /**
     * The root domain \"/\". All registered domains become a sub domain of this root.
     * If a <em>Sub-Log Domains' Verbosity</em> is not explicitly set, such sub domain inherits the
     * verbosity of its parent.
     */
    protected Domain                domains;

    /**
     * The root domain for internal <em>Log Domains</em>.
     */
    protected Domain                internalDomains;

    /** Scope Domains .*/
    protected ScopeStore<AString>                   scopeDomains;

    /** Log Data */
    protected ScopeStore<HashMap<AString, Object>>  scopeLogData;

    /** Log once counters */
    protected ScopeStore<HashMap<AString, int[]>>   scopeLogOnce;

    /** Prefix logables store */
    protected         ScopeStore<Object>            scopePrefixes;

    /** Information about the source code, method, thread, etc. invoking a log  call */
    protected ScopeInfo             scopeInfo;

    /** The resulting domain name. */
    protected AString               resDomain                                   = new AString( 32 );

    /** The resulting domain name for internal logs. */
    protected AString               resDomainInternal                           = new AString( 32 );

    /** A temporary AString, following the "create once and reuse" design pattern. */
    protected AString               intMsg                                     = new AString( 256 );

    /** A temporary AString  */
    protected AString               tmpAS                                       = new AString( 64 );

    /** A temporary AString  */
    protected AString               tmpComments                                = new AString( 128 );

    /**  Flag used with configuration variable LOXNAME_DUMP_STATE_ON_EXIT.  */
    protected boolean               loggerAddedSinceLastDebugState                           =false;

    /**  A temporary object following the "create once and reuse" design pattern. */
    protected boolean[]             booleanOutputParam                             = new boolean[1];

    /** Used for tabular output of logger lists */
    protected int                   maxLoggerNameLength                                         = 0;

    /** Used for tabular output of logger lists */
    protected int                   maxDomainPathLength                                         = 0;

    /** A key value used in stores if no key is given (global object).  */
    protected final static String   noKeyHashKey                                              = "$";

    /** A list of lists of objects. The list is passed to the \e Loggers. For each recursive call,
     *  one list is created.    */
    protected ArrayList<ArrayList<Object>>  logableLists       = new ArrayList<ArrayList<Object>>();

    /** Rule types */
    public enum  DSRType
    {
        EXACT,        ///< Exact match
        STARTS_WITH,  ///< Starts with match
        ENDS_WIDTH,   ///< Ends with match
        SUBSTRING     ///< Any sub-string
    }

    /**  Domain substitution rules.  */
    public class DomainSubstitutionRule
    {
        public DSRType type;                       ///< Denotes if path given started with '*' or not.
        public AString search     = new AString(); ///< The path to search.
        public AString replacement= new AString(); ///< The replacement.

        /**  Constructor.
         * @param s The path to search.
         * @param r The replacement.
        */
        public DomainSubstitutionRule( String s, String r )
        {
            // get type and adjust given search parameter
            int startPos=   0;
            int length=     s.length();
            if ( s.charAt(0) == '*' )
            {
                startPos++;
                length--;
                if ( s.charAt(length) == '*' )
                {
                    type= DSRType.SUBSTRING;
                    length--;
                }
                else
                    type= DSRType.ENDS_WIDTH;
            }
            else
            {
                if ( s.charAt(length-1) == '*' )
                {
                    type= DSRType.STARTS_WITH;
                    length--;
                }
                else
                    type= DSRType.EXACT;
            }
            search._( s, startPos, length );

            // minimum rule check
            if (   (     (    type == DSRType.EXACT
                           || type == DSRType.STARTS_WITH )
                     && !search.startsWith( "/" )
                    )
                || (    type == DSRType.ENDS_WIDTH
                    &&  search.endsWith( "/" )
                   )
               )
                search._(); // illegal rule

            replacement._(r);
        }
    }

    /**  The list of domain substitution rules.  */
    protected ArrayList<DomainSubstitutionRule> domainSubstitutions= new ArrayList<DomainSubstitutionRule>();

    /**  Flag if a warning on circular rule detection was logged.  */
    protected boolean               oneTimeWarningCircularDS                                 =false;

    /**  Temporary string used with domain substitutions.  */
    protected AString               tmpSubstitutionPath                         = new AString( 64 );

    /**  Temporary string used with domain substitutions.  */
    protected AString               tmpSubstitutionPathInternalDomains          = new AString( 64 );


    // #############################################################################################
    // Overrides
    // #############################################################################################
    /** ********************************************************************************************
     * Acquires the lock and stores scope information
     **********************************************************************************************/
    @Override
    public void acquire()
    {
        super.acquire();
        scopeInfo.set( owner );
    }

    /** ********************************************************************************************
     * Releases latest scope information and the lock
     **********************************************************************************************/
    @Override
    public void release()
    {
        scopeInfo.release();
        super.release();
    }

    // #############################################################################################
    // Constructors
    // #############################################################################################

    /** ********************************************************************************************
     * Constructs a new, empty Lox with the given \p{name}.
     * The name is immutable and all \b %Lox objects registered with \b %ALox must be unique.
     * Lower case letters in the name are converted to upper case.
     * The name \c "Log" is reserved for the internal default singleton used for debug-logging.
     *
     * If parameter \p{register} is \c true (the default), static method
     * \ref com.aworx.lox.ALox.register "ALox.register" is invoked and the object will be
     * retrievable with static method
     * \ref com.aworx.lox.ALox.get "ALox.get". In some situations, such 'registration'
     * may not be wanted.
     *
     * @param name       The name of the Lox. Will be converted to upper case.
     * @param doRegister If \c true, this object is registered with static class
     *                   \ref com.aworx.lox.ALox "ALox".
     *                   Optional and defaults to \c true.
     **********************************************************************************************/
    public Lox( String name, boolean doRegister )
    {
        construct( name, doRegister );
    }

    /** ********************************************************************************************
     * Overloaded constructor providing value \c true for parameter \p{doRegister}.
     * @param name       The name of the Lox. Will be converted to upper case.
     **********************************************************************************************/
    public Lox( String name )
    {
        construct( name, true );
    }

    /** ********************************************************************************************
     * Protected constructor helper method
     * @param name       The name of the Lox. Will be converted to upper case.
     * @param doRegister If \c true, this object is registered with static class
     *                   \ref com.aworx.lox.ALox "ALox".
     *                   Optional and defaults to \c true.
     **********************************************************************************************/
    protected void construct( String name, boolean doRegister )
    {
        // uncomment this for debugging deadlocks
        // createOwnerStackTrace= true;

        // set packages that might be omitted
        omittablePackagePrefixes= new Vector<String>();
        omittablePackagePrefixes.add( "com.aworx.lib" );
        omittablePackagePrefixes.add( "com.aworx.lox" );

        // create scope info
        scopeInfo=      new ScopeInfo( name,  omittablePackagePrefixes );
        scopeDomains=   new ScopeStore<AString                 >( scopeInfo, false );
        scopeLogData=   new ScopeStore<HashMap<AString, Object>>( scopeInfo, true  );
        scopeLogOnce=   new ScopeStore<HashMap<AString, int[]> >( scopeInfo, true  );
        scopePrefixes=  new ScopeStore<Object                  >( scopeInfo, false );


        // create domain trees
        domains= new Domain( null, new AString( "" ) );
        internalDomains= new Domain( null,
                                     new AString( ALox.INTERNAL_DOMAINS,
                                                  0,
                                                  ALox.INTERNAL_DOMAINS.length() - 1 )  );

        // create internal sub-domains
        String[] internalDomainList= {"LGR", "DMN", "PFX", "THR", "LGD", "VAR"  };
        for ( String it : internalDomainList )
        {
            resDomainInternal._()._( it );
            internalDomains.find( resDomainInternal, 1, booleanOutputParam );
        }
        maxDomainPathLength= ALox.INTERNAL_DOMAINS.length() + 3;

        // register with ALox
        if ( doRegister )
            ALox.register( this, ContainerOp.INSERT );

        // read domain substitution rules from configuration
        Variable variable= new Variable( ALox.DOMAIN_SUBSTITUTION, getName() );
        if ( ALox.config.load(variable) != 0 )
        {
            for( int ruleNo= 0; ruleNo< variable.size(); ruleNo++ )
            {
                AString rule= variable.getString( ruleNo );
                int idx= rule.indexOf( "->" );
                if ( idx > 0 )
                {
                    String domainPath=  rule.toString( 0, idx ).trim();
                    String replacement= rule.toString( idx + 2 ).trim();
                    setDomainSubstitutionRule( domainPath, replacement );
                }
                else
                {
                    // using alib warning here as we can't do internal logging in the constructor
                    com.aworx.lib.ALIB_DBG.WARNING( "Syntax error in variable \"" + variable.fullname + "\"." );
                }
            }
        }
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
    public String    getName()                      { return scopeInfo.getLoxName();               }

    /** ********************************************************************************************
     * Status of registration with \b %ALox. To keep a \b %Lox "private" using parameter
     * \p{doRegister} of the constructor, allows to suppress registration.
     * Registered instances of this class can be statically received (by their name) using
     * \ref com.aworx.lox.ALox.get "ALox.get".
     *
     * @returns \c true if this instance was registered with \b %ALox, \c false if not.
     **********************************************************************************************/
    public boolean   isRegistered()                 { return ALox.get( getName() ) == this;        }

    /** ************************************************************************************
     *  This static method creates an adequate/default console logger.
     *  Currently, there is no detection mechanism implemented in the Java implementation
     *  of \b %ALox. This might change in the future.
     *
     *  Hence, unless configuration variable
     *  [ALOX_CONSOLE_TYPE](../group__GrpALoxConfigVars.html) is set, this method creates
     *  a logger of type
     *  \ref com.aworx.lox.loggers.ConsoleLogger "ConsoleLogger".
     *
     *  @param name  The name of the \e Logger.  A value of null implies standard logger names
     *               defined in the \e Logger sub-classes.

     *  @return      The TextLogger that was chosen.
     **************************************************************************************/
    public static TextLogger createConsoleLogger(String name)
    {
        //--- check environment "ALOX_CONSOLE_TYPE". They have precedence ---
        Variable variable= new Variable(ALox.CONSOLE_TYPE);
        ALox.config.load(variable);
        AString val= variable.getString().trim();

        if ( val.equals( "PLAIN",   Case.IGNORE ) ) return new ConsoleLogger    ( name );
        if ( val.equals( "ANSI" ,   Case.IGNORE ) ) return new AnsiConsoleLogger( name );

        com.aworx.lib.ALIB_DBG.ASSERT_WARNING( val.isEmpty() || val.equals( "DEFAULT", Case.IGNORE ),
                             "Unrecognized value in config variable \"" + variable.fullname
                            + "\"= " + variable.getString() );

        return new AnsiConsoleLogger( name );
    }

    /** ********************************************************************************************
     * Overloaded method providing default parameter \c null.
     *
     *  @return      The TextLogger that was chosen.
     **********************************************************************************************/
    public static TextLogger createConsoleLogger()
    {
        return createConsoleLogger( null );
    }

    /** ********************************************************************************************
     * Retrieves an instance of a Logger by its name. This might be useful when access to a
     * \e %Logger is needed to change its configuration.
     *
     * @param loggerName    The name of the \e Logger to search for (case insensitive).
     * @return The logger, null if not found.
     **********************************************************************************************/
    public Logger getLogger(String loggerName)
    {
        try { acquire();

            // search logger
            Logger logger;
            if ((logger=         domains.getLogger( loggerName )) != null) return logger;
            if ((logger= internalDomains.getLogger( loggerName )) != null) return logger;

              // not found
            logInternal( Verbosity.WARNING, "LGR", intMsg._()._( "No logger named \"" )._( loggerName )._( "\" found." ) );
            return null;

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Helper method of #dumpStateOnLoggerRemoval to recursively collect domain settings.
     * @param domain    The actual domain.
     * @param loggerNo  The number of the logger
     * @param variable  The AString to collect the information.
     **********************************************************************************************/
    protected void verbositySettingToVariable( Domain domain, int loggerNo, Variable variable )
    {
        variable.add()._( domain.fullPath )
                            ._('=')
                            ._( domain.getVerbosity( loggerNo ).toString() );

        // loop over all sub domains (recursion)
        for( Domain subDomain : domain.subDomains )
            verbositySettingToVariable( subDomain, loggerNo, variable );
    }

    /** ********************************************************************************************
     * Implements functionality for configuration variable \c LOXNAME_LOGGERNAME_VERBOSITY.
     * Is called when a logger is removed.
     * @param logger      The logger to write the verbosity for.
     **********************************************************************************************/
    protected void  writeVerbositiesOnLoggerRemoval( Logger logger )
    {
        // When writing back we will use this priority as the maximum to write. This way, if this was
        // an automatic default value, we will not write back into the user's variable store.
        // As always, only if the app fetches new variables on termination, this is entry is copied.
        Variable variable= new Variable( ALox.VERBOSITY, getName(), logger.getName() );
        ALox.config.load(variable);

        // first token is "writeback" ?
        if ( variable.size() == 0 )
            return;
        Substring firstArg= new Substring( variable.getString() );
        if ( !firstArg.consumeString( "writeback", Case.IGNORE, Whitespaces.TRIM ) )
            return;

        // optionally read a destination variable name
        Substring destVarCategory = new Substring();
        Substring destVarName     = new Substring();
        if( firstArg.trim().isNotEmpty() )
        {
            // separate category from variable name
            int catSeparatorIdx= firstArg.indexOf( '_' );
            if (catSeparatorIdx >= 0 )
            {
                destVarCategory.set( firstArg, 0                   , catSeparatorIdx );
                destVarName    .set( firstArg, catSeparatorIdx + 1);
            }
            else
                destVarName    .set( firstArg );

            if ( destVarName.isEmpty() )
            {
                logInternal( Verbosity.ERROR, "VAR", intMsg._()
                             ._( "Argument 'writeback' in variable " )
                             ._( variable.fullname )
                             ._( "\n  Error:    Wrong destination variable name format\"" )
                             ._( firstArg )._( "\"" )  );
                return;
            }
        }

        // either write directly into LOX_LOGGER_VERBOSITY variable...
        Variable destVar= null;
        if( destVarName.isEmpty() )
        {
            variable.clearValues( 1 );
            destVar= variable;
        }
        // ...or into a new given variable
        else
        {
            destVar= new Variable( destVarCategory, destVarName, ALox.VERBOSITY.delim );
            destVar.formatHints=         variable.formatHints;
            destVar.formatAttrAlignment= variable.formatAttrAlignment;
            destVar.comments._("Created at runtime through config option 'writeback' in variable \"")._( variable.fullname )._("\".");
        }

        // collect verbosities
        {
            int loggerNoMainDom= domains        .getLoggerNo( logger );
            int loggerNoIntDom=  internalDomains.getLoggerNo( logger );

            if ( loggerNoMainDom >= 0 ) verbositySettingToVariable( domains        , loggerNoMainDom, destVar );
            if ( loggerNoIntDom  >= 0 ) verbositySettingToVariable( internalDomains, loggerNoIntDom , destVar );
        }

        // now store using the same plug-in as original variable has
        destVar.priority= variable.priority;
        ALox.config.store(destVar);

        // internal logging
        intMsg._()._( "Argument 'writeback' in variable " )._( variable.fullname )
                  ._( ":\n  Verbosities for logger \"" )   ._( logger.getName() )
                  ._( "\" written " );

        if( destVarName.isEmpty() )
            intMsg._( "(to source variable)." );
        else
            intMsg._( "to variable \"" )  ._( destVar.fullname ) ._("\".") ;
        logInternal( Verbosity.INFO, "VAR", intMsg._( destVarName )._( "\"." ) );


        // verbose logging of the value written
        intMsg._()._("  Value:");
        for( int i= 0; i< destVar.size() ; i++ )
            intMsg._( "\n    " )._( destVar.getString(i) );
        logInternal( Verbosity.VERBOSE, "VAR", intMsg );
    }

    /** ********************************************************************************************
     * Implements functionality for configuration variable \c LOXNAME_DUMP_STATE_ON_EXIT.
     * Is called when a logger is removed.
     **********************************************************************************************/
    protected void dumpStateOnLoggerRemoval()
    {
        if( !loggerAddedSinceLastDebugState )
            return;
        loggerAddedSinceLastDebugState= false;

        Variable variable= new Variable( ALox.DUMP_STATE_ON_EXIT, getName() );
        ALox.config.load(variable);

        String      domain=         null;
        Verbosity   verbosity=      Verbosity.INFO;

        Substring tok= new Substring();
        int flags= 0;
        for( int tokNo= 0; tokNo< variable.size(); tokNo++ )
        {
            tok.set( variable.getString( tokNo ) );
            if( tok.isEmpty() )
                continue;

            // state flags
                 if( tok.equals( "NONE"            , Case.IGNORE ) )  { flags= 0; break; }
            else if( tok.equals( "Basic"           , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_BASIC           ;
            else if( tok.equals( "Version"         , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_VERSION         ;
            else if( tok.equals( "Loggers"         , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_LOGGERS         ;

            else if( tok.equals( "Domains"         , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_DOMAINS         ;
            else if( tok.equals( "InternalDomains" , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_INTERNAL_DOMAINS;
            else if( tok.equals( "ScopeDomains"    , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_SCOPE_DOMAINS   ;
            else if( tok.equals( "DSR"             , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_DSR             ;
            else if( tok.equals( "PrefixLogables"  , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_PREFIX_LOGABLES ;
            else if( tok.equals( "Once"            , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_ONCE            ;
            else if( tok.equals( "LogData"         , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_LOG_DATA        ;
            else if( tok.equals( "ThreadMappings"  , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_THREAD_MAPPINGS ;

            else if( tok.equals( "All"             , Case.IGNORE ) )  flags|=  Lox.STATE_INFO_ALL             ;

            // domain and verbosity
            else if( tok.consumeString( "domain", Case.IGNORE, Whitespaces.TRIM ) )
            {
                if( tok.consumeChar( '=', Case.SENSITIVE, Whitespaces.TRIM ) )
                    domain= tok.trim().toString();
            }
            else if( tok.consumeString( "verbosity", Case.IGNORE, Whitespaces.TRIM ) )
            {
                if( tok.consumeChar( '=', Case.SENSITIVE, Whitespaces.TRIM ) )
                    verbosity= ALox.readVerbosity( tok.trim() );
            }

            // unknown argument
            else
            {
                logInternal( Verbosity.ERROR, "VAR", intMsg._()
                             ._( "Unknown argument '" )._(tok)
                             ._( "' in variable " )._(variable.fullname)._( " = \"")._(variable.getString())._('\"') );
            }
        }

        if ( flags != 0 )
        {
            state( domain, verbosity, "Auto dump state on exit requested: ", flags );
        }
    }

    /** ********************************************************************************************
     * Removes a logger from this container.
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref setVerbosity  "setVerbosity( logger, Verbosity.OFF )"
     *       can be used.
     *
     * @param logger   The logger to be removed.
     * @returns \c true, if the \e Logger was found and removed, \c false otherwise.
     **********************************************************************************************/
    public boolean removeLogger(Logger logger)
    {
        try { acquire();


            int noMainDom=  domains        .getLoggerNo( logger );
            int noIntDom=   internalDomains.getLoggerNo( logger );

            if( noMainDom >= 0 || noIntDom >= 0 )
            {
                dumpStateOnLoggerRemoval();
                writeVerbositiesOnLoggerRemoval( logger );

                if( noMainDom >= 0 )
                    domains.removeLogger( noMainDom );

                if( noIntDom >= 0 )
                    internalDomains.removeLogger( noIntDom );

                logger.removeAcquirer( this );

                return true;
            }

            // not found
            logInternal( Verbosity.WARNING, "LGR",
                    intMsg._()._( "Logger \"" )._( logger )._( "\" not found. Nothing removed." ) );

            return false;
        }
        finally { release(); }
    }

    /** ********************************************************************************************
     * Removes logger named \p{loggerName} from this container.
     *
     * \note To (temporarily) disable a logger without removing it, a call to
     *       \ref setVerbosity  "setVerbosity( logger, Verbosity.OFF )"
     *       can be used.
     *
     * @param loggerName  The name of the \e Logger(s) to be removed (case insensitive).
     * @returns The logger that was removed, \c null if not found.
     **********************************************************************************************/
    @SuppressWarnings ("null")
    public Logger removeLogger( String loggerName )
    {
        try
        { acquire();
            int noMainDom=  domains        .getLoggerNo( loggerName );
            int noIntDom=   internalDomains.getLoggerNo( loggerName );

            if( noMainDom >= 0 || noIntDom >= 0 )
            {
                Logger                  logger=         domains.getLogger( noMainDom );
                if ( logger == null )   logger= internalDomains.getLogger( noIntDom );

                dumpStateOnLoggerRemoval();
                writeVerbositiesOnLoggerRemoval( logger );

                if( noMainDom >= 0 )
                    domains.removeLogger( noMainDom );

                if( noIntDom >= 0 )
                    internalDomains.removeLogger( noIntDom );

                logger.removeAcquirer( this );

                logInternal( Verbosity.INFO, "LGR", intMsg._()._( "Logger \"" )._( logger )._( "\" removed." ) );

                return logger;
            }

            // not found

            logInternal( Verbosity.WARNING, "LGR", intMsg._()._( "Logger \"" )._( loggerName )
                                                             ._( "\" not found. Nothing removed." ) );
            return null;
        }
        finally { release(); }
    }

    /** ********************************************************************************************
     * Sets the \e %Verbosity of the <em>Log Domain</em> which is evaluated from parameter \p{domain} and
     * applicable <em>Scope Domains</em>. The \p{verbosity} given, is set recursively for all sub-domains.
     *
     * With the first invocation of this method for a distinct \p{logger}, this \e %Logger
     * is registered with this \e %Lox. In this case, prior to setting the given \e Verbosity
     * for the evaluated sub-domain, the \e Verbosity for all domains is set to
     * \b %Verbosity.Off.
     *
     * To deregister a \e Logger with a \b Lox, use method #removeLogger.
     * To 'disable' a \e Logger, invoke this method with parameters \p{verbosity} equaling to
     * \b %Verbosity.Off and \p{domain} to \c "/".
     *
     * Optional parameter \p{priority} defaults to
     * \ref com.aworx.lib.config.Configuration.PRIO_DEFAULT_VALUES "Configuration.PRIO_DEFAULT_VALUES",
     * which is a lower priority than those of the standard plug-ins of external configuration data. Therefore, external
     * configuration by default 'overwrite' settings made from 'within the source code', which
     * simply means by invoking this method.<br>
     * The parameter can be provided for two main reasons:
     * - To 'lock' a verbosity setting against external manipulation.
     * - to 'break' the standard mechanism that an invocation of this method sets all
     *   sub-domains recursively. If a sub-domain was set with a higher priority
     *   (e.g. <c>%PRIO_DEFAULT_VALUES + 1</c>, then this sub-domain will not be affected by
     *   future invocations of this method with standard-priority given.
     *
     * For more information on how to use external configuration variables with priority and
     * on protecting verbosity settings, consult the [ALox User Manual](../manual.html).
     *
     * \attention
     *   The same as with most interface methods of this class, the given \p{domain} parameter is
     *   combined with <em>%Scope Domains</em> set for the callers' \e %Scope. In standard use
     *   cases of \b %ALox, the \e %Verbosity of a \e Domain is set using absolute domain path
     *   addressing. Therefore, it is recommended to have any domain path passed to this method
     *   starting with <c> '/'</c>, which suppresses the concatenation of <em>%Scope Domains</em>.<br>
     *   This is why this parameter with this method defaults to <c> '/'</c>, while with other
     *   methods of this class, it defaults to an empty string.<p>
     * \attention
     *   Even when using an absolute domain path, <em>%Scope Domains</em> of
     *   \e %Scope.THREAD_INNER, will still apply. This means that from within a thread that
     *   has such <em>%Scope Domain</em> set, this method is (almost) not usable!
     *   This all aligns with the concept (advice), that \e Loggers and their \e %Verbosity
     *   are generally set outside of such scopes, hence in configuration sections of a
     *   process.<p>
     * \attention
     *   Consequently, this method may be (mis-) used to modify the 'actual' (default) scope
     *   when explicitly giving an empty string with parameter \p{domain}. This is useful, to
     *   temporarily adjust a scope. But remember: \b %ALox was designed to avoid temporary code
     *   lines...
     *
     * @param logger     The logger to be to be affected (case insensitive).
     * @param verbosity  The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     * @param priority   The priority of the setting. Defaults to
     *                   \ref com.aworx.lib.config.Configuration.PRIO_DEFAULT_VALUES "Configuration.PRIO_DEFAULT_VALUES".
     **********************************************************************************************/
    public void setVerbosity(Logger logger, Verbosity verbosity, String domain, int priority )
    {
        try { acquire();

            // check
            if (logger == null)
            {
                logInternal( Verbosity.ERROR, "LGR", intMsg._()._( "Given Logger is \"null\". Verbosity not set." ) );
                return;
            }

            // this might create the (path of) domain(s) and set the \e Loggers' verbosity like their
            // first parent's or as given in configuration
            Domain dom= evaluateResultDomain( domain );

            // search logger, insert if not found
            boolean isNewLogger= false;
            int no= dom.getLoggerNo( logger );

            if (no < 0)
            {
                no= dom.addLogger( logger );

                // error, logger with same name already exists
                if (no < 0)
                {
                    logInternal( Verbosity.ERROR, "LGR",
                            intMsg._()._( "Unable to add logger \"" )._( logger )._( "\". Logger with same name exists." ) );

                    logInternal( Verbosity.VERBOSE, "LGR", intMsg._()
                              ._NC( "  Request was: setVerbosity( \"")._(logger)._NC("\", \"")
                              ._(dom.fullPath)  ._NC("\", Verbosity.")
                              ._NC(verbosity)   ._NC(", ")
                              ._(priority)      ._NC(" )" )    );

                    Logger existingLogger= dom.getLogger( logger.getName() );
                    logInternal( Verbosity.VERBOSE, "LGR", intMsg._()._( "  Existing Logger: \"" )._( existingLogger )
                            ._( '\"' ) );

                    return;
                }

                // We have to register with the SmartLock facility of the \e Logger.
                // But only if we have not done this yet, via the 'other' root domain tree
                if ( (dom.getRoot() == domains ? internalDomains.getLoggerNo( logger )
                                               :         domains.getLoggerNo( logger ) ) < 0 )
                    logger.addAcquirer( this );

                // store size of name to support tabular internal log output
                String loggerName= logger.getName();
                if (maxLoggerNameLength < loggerName.length())
                    maxLoggerNameLength=  loggerName.length();

                // for internal log
                isNewLogger= true;

                // remember that a logger was set after the last removal
                // (for variable LOXNAME_DUMP_STATE_ON_EXIT)
                loggerAddedSinceLastDebugState= true;
            }

            // get verbosities from configuration
            if (isNewLogger)
            {
                logInternal(
                        Verbosity.INFO,
                        "LGR",
                        intMsg._()._( "Logger \"" )._( logger )
                                ._( domain.startsWith( ALox.INTERNAL_DOMAINS ) ?
                                        "\" added for internal log messages." : "\" added." ) );

                // we have to get all verbosities of already existing domains
                Variable variable= new Variable( ALox.VERBOSITY, getName(), logger.getName() );
                if( 0 != ALox.config.load(variable) )
                {
                    getAllVerbosities( logger, domains         , variable );
                    getAllVerbosities( logger, internalDomains , variable );
                }
            }

            // do
            dom.setVerbosity( no, verbosity, priority );

            intMsg._()._("Logger \"")._( logger.getName() )._NC( "\":").tab(11 + maxLoggerNameLength)
                      ._('\'')._NC( dom.fullPath )
                      ._( '\'' ).insertChars(' ', maxDomainPathLength - dom.fullPath.length() + 1 )
                      ._( "= Verbosity." );
                      ALox.toString( verbosity, priority, intMsg ).trimEnd()._('.');

            Verbosity actVerbosity= dom.getVerbosity( no );
            if( actVerbosity != verbosity )
                intMsg._( " Lower priority (")._( priority )
                      ._(" < ")._(dom.getPriority(no))
                      ._( "). Remains " )._NC( actVerbosity )._( '.' );
            logInternal( Verbosity.INFO, "LGR", intMsg );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(Logger,Verbosity,String) "setVerbosity" providing
     * default value \c PRIO_SOURCE for parameter \p{priority}.
     *
     * @param logger     The logger to be to be affected.
     * @param verbosity  The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     **********************************************************************************************/
    public void setVerbosity(Logger logger, Verbosity verbosity, String domain)
    {
        setVerbosity( logger, verbosity, domain, Configuration.PRIO_DEFAULT_VALUES);
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(Logger,Verbosity,String) "setVerbosity" providing
     * - default value \c PRIO_SOURCE for parameter \p{priority} and
     * - default value <c> '/'</c> for parameter \p{domain}.
     *
     * @param logger     The logger to be to be affected.
     * @param verbosity  The 'level of verboseness' to be set.
     **********************************************************************************************/
    public void setVerbosity(Logger logger, Verbosity verbosity)
    {
        setVerbosity( logger, verbosity, "/" , Configuration.PRIO_DEFAULT_VALUES);
    }

    /** ********************************************************************************************
     * Same as \ref #setVerbosity(Logger,Verbosity,String) "setVerbosity" but
     * addressing the \e %Logger to manipulate by its name.<br>
     * This method may only be used after a \e %Logger was once 'registered' with this \b %Lox
     * using \ref #setVerbosity(Logger,Verbosity,String) "setVerbosity".
     *
     * @param loggerName The logger to be to be affected, identified by its name (case
     *                   insensitive).
     * @param verbosity  The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     * @param priority   The priority of the setting. Defaults to
     *                   \ref com.aworx.lib.config.Configuration.PRIO_DEFAULT_VALUES "Configuration.PRIO_DEFAULT_VALUES".
     **********************************************************************************************/
    public void setVerbosity(String loggerName, Verbosity verbosity, String domain, int priority)
    {
        try { acquire();

            // this might create the (path of) domain(s) and set the \e Loggers' verbosity like their first parent's
            Domain dom= evaluateResultDomain( domain );

            // get logger
            Logger logger;
            int no= dom.getLoggerNo( loggerName );
            if (no >= 0)
                logger= dom.getLogger( no );
            else
            {
                // we have to check if the logger was added in the 'other' tree
                Domain otherTree=  dom.getRoot() == domains ? internalDomains
                                                            : domains;
                no= otherTree.getLoggerNo( loggerName );
                if ( no < 0 )
                {
                    intMsg._()._NC( "Logger not found. Request was: setVerbosity( \"")._(loggerName)._NC("\", \"")
                              ._(dom.fullPath)  ._NC("\", ")
                              ._NC(verbosity)   ._NC(", Verbosity.")
                              ._(priority)      ._NC(" )." );
                    logInternal( Verbosity.WARNING, "LGR", intMsg );
                    return;
                }

                logger= otherTree.getLogger( no );
            }

            // use the overloaded method
            setVerbosity( logger, verbosity, domain, priority );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(String,Verbosity,String,int) "setVerbosity" providing
     * default value \c PRIO_SOURCE for parameter \p{priority}.
     *
     * @param loggerName  The logger to be to be affected, identified by its name (case
     *                    insensitive).
     * @param verbosity   The 'level of verboseness' to be set.
     * @param domain     The parent (start) domain to be set. The use of absolute paths
     *                   starting with <c> '/'</c> are recommended.
     *                   Defaults to root domain \"/\".
     **********************************************************************************************/
    public void setVerbosity(String loggerName, Verbosity verbosity, String domain)
    {
        setVerbosity( loggerName, verbosity, domain, Configuration.PRIO_DEFAULT_VALUES);
    }


    /** ********************************************************************************************
     * Overloaded version of \ref setVerbosity(String,Verbosity,String,int) "setVerbosity" providing
     * - default value \c PRIO_SOURCE for parameter \p{priority} and
     * - default value <c> '/'</c> for parameter \p{domain}.
     *
     * @param loggerName  The logger to be to be affected, identified by its name (case
     *                    insensitive).
     * @param verbosity   The 'level of verboseness' to be set.
     **********************************************************************************************/
    public void setVerbosity(String loggerName, Verbosity verbosity)
    {
        setVerbosity( loggerName, verbosity, "/", Configuration.PRIO_DEFAULT_VALUES);
    }

    /** ********************************************************************************************
     * The given \p{scopeDomain} becomes the default domain path for given \p{scope}.
     * This means, that any subsequent log invocations (from within this same scope) can omit the
     * domain parameter, or if they provide one, this Scope Domain path is prepended.
     * If subsequent log calls specify a domain name with a leading '/' character,
     * then the Scope Domain of the scope is ignored.<br>
     * Furthermore, if the given scope is an inner scope, outer scopes are prepended to the
     * given \p{scopeDomain} when the resulting domain of a log invocation is evaluated.
     * Again, this behavior can be overruled by prepending a leading '/' character to
     * \p{scopeDomain}.
     *
     *
     * To remove a previously set Scope Domain a nulled or empty string has to be passed with
     * parameter \p{scopeDomain}.
     *
     * For \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER, passing an empty or nulled string
     * removes the most recently added domain path. For removing an explicitly named
     * domain path of \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER use method
     * #removeThreadDomain.
     *
     *
     * @param scopeDomain  The domain path to register.
     * @param scope        The scope that should the given \p{domain} be registered for.
     *                     Available Scope definitions are platform/language dependent.
     * @param packageLevel Used only if parameter \p{scope} equals
     *                     \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                    to reference parent packages. Optional and defaults to \c 0.
     **********************************************************************************************/
    public void setDomain(String scopeDomain, Scope scope, int packageLevel)
    {
        setDomainImpl( scopeDomain, scope, packageLevel, false, null );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setDomain( String, Scope, int) "setDomain"
     * providing default value \c 0 for parameter \p{packageLevel}.
     *
     * @param scopeDomain    The domain path to register.
     * @param scope        The scope that should the given \p{domain} be registered for.
     *                     Available Scope definitions are platform/language dependent.
     **********************************************************************************************/
    public void setDomain(String scopeDomain, Scope scope)
    {
        setDomainImpl( scopeDomain, scope, 0, false, null );
    }

    /** ********************************************************************************************
     * This overloaded version of
     * \ref setDomain( String, Scope, int) "setDomain"
     * is applicable only for \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER and allows to
     * specify the thread that the setting should be associated with.
     *
     * If \p{scopeDomain} is \c null or empty, the most recently added domain path is removed.
     * For removing an explicitly named domain associated with  a thread use method
     * #removeThreadDomain.
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.THREAD_OUTER or \e %Scope.THREAD_INNER. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related Scope Domains for.
     **********************************************************************************************/
    public void setDomain(String scopeDomain, Scope scope, Thread thread)
    {
        if (!isThreadRelatedScope( scope )) return;
        setDomainImpl( scopeDomain, scope, 0, false, thread );
    }

    /** ********************************************************************************************
     * This method is used to remove an <em>explicitly given</em> domain path from the list
     * of domain paths set for \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER.
     *
     * To remove the most recently added domain path from such thread-related \e %Scope,
     * use one of the overloaded methods #setDomain and provide an empty or nulled
     * value for parameter \p{scopeDomain} (the same as how domain paths of other \e %Scopes
     * are removed).
     *
     * \note
     *   The long name of the method already indicates that this method is a little special.
     *   Only seldom, more than one <em>%Scope Domain</em> is needed to be added. And if this
     *   is needed, then such <em>%Scope Domains</em> usually get removed in reverse order of
     *   their definition, with is performed using the standard interface that allows 'removing'
     *   any other <em>%Scope Domain</em>. (Passing an empty or nulled domain
     *   path to method #setDomain.)
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER. With other values,
     *                    an internal error is logged.
     * @param thread      The thread to set/unset a thread-related Scope Domains for.
     *                    Defaults to the current thread.
     **********************************************************************************************/
    public void removeThreadDomain(String scopeDomain, Scope scope, Thread thread)
    {
        try { acquire();

            if (!isThreadRelatedScope( scope )) return;

            if (CString.isNullOrEmpty( scopeDomain ))
            {
                intMsg._()._( "No scope domain path given to remove for " );
                ALox.toString( scope, 0, intMsg );
                intMsg._( '.' );
                logInternal( Verbosity.WARNING, "DMN", intMsg );
                return;
            }

            setDomainImpl( scopeDomain, scope, 0, true, thread );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overload version providing default value for parameter \p{thread}.
     *
     * @param scopeDomain The domain path to register.
     * @param scope       Either \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER. With other values,
     *                    an internal error is logged.
     **********************************************************************************************/
    public void removeThreadDomain(String scopeDomain, Scope scope)
    {
        removeThreadDomain( scopeDomain, scope, null );
    }

    /** ********************************************************************************************
     * Adds a <em>Domain Substitution Rule</em>.
     * <em>Domain Substitution</em> is performed as a last step when evaluating the domain path of a <em>Log Statement</em>,
     * taking <em>Scope Domains</em> and the optional parameter \p{domain} of the statement into
     * account.<br>
     *
     * <b>Wildcards</b><br>
     * Parameter \p{domainPath} supports \b 'wildcard' character <c> '*'</c> at its beginning
     * and at its end (or both). This allows to have four types of rules:
     * - Exact match
     * - Prefix match (\c * at the end of \p{domainPath})
     * - Suffix match (\c * at the start of \p{domainPath})
     * - Substring match (\c * at both, start and the end of \p{domainPath})
     *
     * Only minimal checks are performed, e.g. if an exact match is requested, but \p{domainPath}
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
     * To delete a rule, invoke the method with same parameter \p{domainPath} and a 'nulled'
     * or empty string for parameter \p{replacement}.
     * To delete all rules, invoke the method with parameter \p{domainPath} 'nulled'
     * or empty.
     *
     * <b>Final remarks</b>
     * Domain substitution is useful to permanently change ('redirect') domain paths of
     * 3rd party code (e.g. libraries using \b %ALox) or log statements that must not be changed
     * for other reasons. It is advised to not 'overuse' this feature, as side effects
     * are inherent to the concept of <em>Domain Substitution</em>. For example, an unwanted side effect might be
     * that <em>Prefix Logables</em> are not applicable to the substituted domain, while other <em>Prefix Logables</em> are
     * bound to the resulting domain.
     *
     * For \b %Lox objects that should be protected of external manipulation, it is advisable,
     * to remove all <em>Domain Substitution Rules</em> right after the \b %Lox was created by invoking this method with
     * a nulled value for parameter \p{domainPath}. The reason is, that otherwise, through
     * configuration files or command line parameters, domains of the \b %Lox can be substituted
     * and then the resulting domains \e Verbosities be \e overwritten using further configuration
     * variables. Any prioritized \e 'internal' setting of \e Verbosities this way could be
     * circumvented!
     *
     * For more information consult the [ALox User Manual](../man_domain_substitution.html).
     *
     * @param domainPath  The path to search. Has to start with either  <c> '/'</c> or <c> '*'</c>.
     * @param replacement The replacement path.
     **********************************************************************************************/
    public void   setDomainSubstitutionRule( String domainPath, String replacement )
    {
        try { acquire();

            intMsg._();

            // check null param: clears all rules
            if ( CString.isNullOrEmpty( domainPath ) )
            {
                oneTimeWarningCircularDS= false;
                domainSubstitutions.clear();
                intMsg._( "Domain substitution rules removed." );
                logInternal( Verbosity.INFO, "DMN", intMsg );
                return;
            }

            // create rule
            DomainSubstitutionRule newRule= new DomainSubstitutionRule( domainPath, replacement );
            if ( newRule.search.isEmpty() )
            {
                intMsg._( "Illegal domain substitution rule. Nothing stored." );
                logInternal( Verbosity.WARNING, "DMN", intMsg );
                return;
            }

            // search existing rule
            int  it;
            for( it= 0; it != domainSubstitutions.size() ; ++it )
            {
                if (     domainSubstitutions.get(it).type == newRule.type
                      && domainSubstitutions.get(it).search.equals( newRule.search ) )
                    break;
            }

            // no replacement given?
            if ( CString.isNullOrEmpty( replacement) )
            {
                if ( it == domainSubstitutions.size() )
                {
                    intMsg._( "Domain substitution rule \"")._( domainPath)._( "\" not found. Nothing to remove." );
                    logInternal( Verbosity.WARNING, "DMN", intMsg );
                    return;
                }

                intMsg._( "Domain substitution rule \"")._( domainPath      )._( "\" -> \"" )
                                                    ._( domainSubstitutions.get(it).replacement  )._( "\" removed." );
                domainSubstitutions.remove( it );
                logInternal( Verbosity.INFO, "DMN", intMsg );
                return;
            }


            intMsg._( "Domain substitution rule \"")._( domainPath          )._( "\" -> \"" )
                                                ._( newRule.replacement )._( "\" set." );

            // change of rule
            if ( it != domainSubstitutions.size() )
            {
                intMsg._( " Replacing previous -> \"")._( domainSubstitutions.get(it).replacement )._( "\"." );
                domainSubstitutions.get(it).replacement._()._( newRule.replacement );
            }
            else
                domainSubstitutions.add( newRule );

            logInternal( Verbosity.INFO, "DMN", intMsg );


        } finally { release(); }
    }

    /** ********************************************************************************************
     * The given \p{prefix} becomes a <em>Prefix Logable</em> provided to loggers with each log
     * statement executed within the given \p{scope}.
     * The list of objects received by a logger is sorted from outer scope to inner scope.
     * The logable of the <em>%Log Statement</em> itself, is the last in the list, except one or
     * more <em>Prefix Logables</em> of \e %Scope.ThreadInner are set. Those are (similar to how
     * this \e %Scope is used with <em>%Scope Domains</em>) appended to the end of the
     * list.
     *
     * To remove a previously set <em>Prefix Logable</em>, \c null has to be passed with
     * parameter \p{logable}.
     * For \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER, passing \c null
     * removes the most recently added <em>Prefix Logable</em>.
     *
     *<p>
     * \note
     *   Unlike other methods of this class which accept more than one logable, this
     *   method and its overloaded variants accept only one (the prefix).
     *   To supply several objects to be prefix logables at once, those may be passed as an
     *   Object[] like shown in the following sample:
     *   \snippet "UT_alox_scopes.java"      DOX_ALOX_LOX_SETPREFIX
     *
     *<p>
     * \note
     *   The word 'prefix' in this methods' name and in the name of \b %ALox feature
     *   <em>Prefix Logables</em> is chosen for the fact that with text loggers (which is the
     *   most widely applied use case for \b %ALox) such objects are prefixes to the log
     *   message. Of-course, with using \e %Scope.THREAD_INNER, this turns into a suffix!<br>
     *   When using \b %ALox to process objects instead of log messages, the concept of
     *   <em>Prefix Logables</em> is very useful. Just the name does not fit so well anymore.
     *   Think of 'SetContext' and <em>Context Objects</em> instead.
     *
     * @param prefix       The <em>Prefix Logable(s)</em> to set.
     * @param scope        The scope that should the given \p{logable} be registered for.
     *                     Available Scope definitions are platform/language dependent.
     * @param packageLevel Used only with
     *                     \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE".
     *                     Cuts the given number of package parts (separated with '.') from the end
     *                     of the packages. Optional and defaults to \c 0.
     **********************************************************************************************/
    public void        setPrefix( Object prefix, Scope scope, int packageLevel  )
    {
        setPrefixImpl( prefix, scope, packageLevel, null );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref setPrefix(Object,Scope,int) "setPrefix" providing value \c 0
     * as default for parameter \p{packageLevel}.
     *
     * @param prefix  The <em>Prefix Logable(s)</em> to set.
     * @param scope   The scope that should the given \p{logable} be registered for.
     *                Available Scope definitions are platform/language dependent.
     **********************************************************************************************/
    public void        setPrefix( Object prefix, Scope scope  )
    {
        setPrefixImpl( prefix, scope, 0, null );
    }

    /** ********************************************************************************************
     * This overloaded version of
     * \ref setPrefix(Object,Scope,int) "setPrefix" is applicable only for
     * \e %Scope.THREAD_OUTER and \e %Scope.THREAD_INNER and allows to specify the thread that
     * the setting should be associated with.
     *
     * If \p{logable} is \c null, the most recently added <em>Prefix Logable</em>
     * is removed.
     *
     * @param prefix  The <em>Prefix Logable(s)</em> to set.
     * @param scope   Either \e %Scope.THREAD_OUTER or \e %Scope.THREAD_INNER. With other
     *                values, an internal error is logged.
     * @param thread  The thread to set/unset a thread-related <em>Prefix Logable</em> for.
     **********************************************************************************************/
    public void        setPrefix( Object prefix, Scope scope, Thread thread )
    {
        setPrefixImpl( prefix, scope, 0, thread );
    }

    /** ********************************************************************************************
     * The given \p{logable} becomes a <em>Prefix Logable</em> associated to the given
     * <em>Log Domain</em>.  <em>Prefix Logables</em> associated with the <em>Log Domain</em> are
     * added to the list of \e Logables right before the main \e Logable of the
     * <em>Log Statement</em> itself.
     * Multiple <em>Prefix Logables</em> can be added per <em>Log Domain</em>.
     *
     * To remove the most recently added <em>Prefix Logable</em> associated with a <em>Log Domain</em>,
     * \c null has to be passed with parameter \p{logable}.
     *
     * \attention
     *   The same as with most interface methods of this class, the given \p{domain} parameter is
     *   combined with <em>%Scope Domains</em> set for the callers' \e %Scope.
     *   To suppress this, an absolute domain path can be used. (Still any <em>Scope Domain</em> of
     *   \e %Scope.Thread.Inner will be applied).
     *   The default value of parameter \p{domain} is \c "" which addresses the domain evaluated
     *   for the current scope.
     *
     * <p>
     * \note
     *   Unlike other methods of this class which accept more than one logable, this
     *   method and its overloaded variants accept only one (the prefix).
     *   To supply several objects to be prefix logables at once, those may be passed as an
     *   Object[] like shown in the following sample:
     *   \snippet "UT_alox_scopes.java"      DOX_ALOX_LOX_SETPREFIX
     *
     * @param prefix     The <em>Prefix Logable(s)</em> to set.
     * @param domain     The domain path. Defaults to \c null, resulting in
     *                   evaluated <em>Scope Domain</em> path.
     * @param otherPLs   If set to \c Inclusion.Exclude, scope-related <em>Prefix Logables</em>
     *                   are ignored and only domain-related <em>Prefix Logables</em> are passed to
     *                   the \e Loggers.
     *                   Defaults to \c Inclusion.Include.
     **********************************************************************************************/
    public void        setPrefix( Object prefix, String domain, Inclusion otherPLs )
    {
        try { acquire();

            // we consider empty strings as unset command, so we set them to null
            if( prefix != null )
            {
                if (    (( prefix instanceof AString ) && ((AString) prefix).isNull() )
                     || (( prefix instanceof String  ) && ((String)  prefix).length() == 0 )
                   )
                    prefix= null;
            }

            Domain dom= evaluateResultDomain( domain );

            Verbosity intLogVerbosity= Verbosity.INFO;
            intMsg._();

            if ( prefix != null )
            {
                dom.prefixLogables.add( dom.new PL( prefix, otherPLs ) );
                intMsg._( "Object \"" )._( prefix )._( "\" added as prefix logable for" );
            }
            else
            {
                int qtyPLs= dom.prefixLogables.size();
                if ( qtyPLs > 0 )
                {
                    Object removedLogable= dom.prefixLogables.get( qtyPLs - 1).logable;
                    dom.prefixLogables.remove( qtyPLs - 1 );

                    intMsg._("Object \"")._( removedLogable )._( "\" removed from list of prefix logables for");
                }
                else
                {
                    intMsg._( " No prefix logable to remove from" );
                    intLogVerbosity=  Verbosity.WARNING;
                }
            }

            intMsg._( " domain \'")._( dom.fullPath )._( "\'."  );
            logInternal( intLogVerbosity,    "PFX", intMsg );

        } finally { release(); }

    }

    /** ********************************************************************************************
     * Overloaded version of #setPrefix providing
     * default value \c Inclusion.INCLUDE for parameter \p{otherPLs}.
     *
     * @param logable     The <em>Prefix Logable(s)</em> to set.
     * @param domain      The domain path. Defaults to \c null, resulting in
     *                    evaluated <em>Scope Domain</em> path.
     **********************************************************************************************/
    public void        setPrefix( Object logable, String domain )
    {
        setPrefix( logable, domain, Inclusion.INCLUDE );
    }

    /** ********************************************************************************************
     * Overloaded version of #setPrefix providing
     * default value \c Inclusion.INCLUDE for parameter \p{otherPLs} and
     * default value \c null for parameter \p{domain}.
     *
     * @param logable     The <em>Prefix Logable(s)</em> to set.
     **********************************************************************************************/
    public void        setPrefix( Object logable )
    {
        setPrefix( logable, null, Inclusion.INCLUDE );
    }

    /** ********************************************************************************************
     * This method is used reset (or to explicitly set) the start time of the \e Logger(s). The only
     * impact is the output of time differences in the log lines. Hence, it is useful to see some
     * absolute time values when doing basic performance tests using the \e Logger.
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
     **********************************************************************************************/
    public void setStartTime(Date startTime, String loggerName)
    {
        try { acquire();

            // check if start time was set
            Ticks time= new Ticks( 0L );
            if (startTime != null)
                time.setFromJavaDate( startTime );
            else
                time.set();

            // request logger only from main domain tree
            Logger logger= domains.getLogger( loggerName );
            if (logger == null)
            {
                logInternal( Verbosity.ERROR, "LGR",
                        intMsg.clear()._( '\"' )._( loggerName )._( "\": not found. Start time not set." ) );
                return;
            }

            // do
            logger.timeOfCreation.set( time );
            logger.timeOfLastLog.set( time );

            // log info on this
            logInternal( Verbosity.INFO, "LGR",
                         intMsg.clear()._( '\"' )._( logger )._( "\": Start time set to " )
                               ._( startTime != null ? startTime : "<now>" )._( '.' ) );

        } finally { release(); }
    }


    /** ********************************************************************************************
     * Overloaded version of #setStartTime( Date, String ) providing default value \c null
     * for parameter \p{loggerName}.
     *
     * @param startTime     Optional parameter with the  new start time. Defaults to DateTime.Now if
     *                      omitted.
     **********************************************************************************************/
    public void setStartTime(Date startTime)
    {
        setStartTime( startTime, null );
    }

    /** ********************************************************************************************
     * Overloaded version of #setStartTime( Date, String ) providing default values
     * \c null for parameters \p{startTime} and \p{loggerName}.
     **********************************************************************************************/
    public void setStartTime()
    {
        setStartTime( null, null );
    }

    /** ********************************************************************************************
     * This method sets a human readable name to the given thread ID (or current thread) which is
     * optionally included in each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     * @param id            Parameter providing the thread ID.
     *                      Defaults to \c -1 which uses the current thread.
     **********************************************************************************************/
    public void mapThreadName(String threadName, long id)

    {
        try { acquire();

            // get current thread id
            String origThreadName= null;
            if (id < 0)
            {
                Thread t= Thread.currentThread();
                id= t.getId();
                origThreadName= t.getName();
            }

            // add entry
            scopeInfo.threadDictionary.put( new Long( id ), threadName );

            // log info on this
            intMsg.clear()._( "Mapped thread ID " )._( (int) id )._( " to \"" )._( threadName )._( "\"." );
            if (!CString.isNullOrEmpty( origThreadName )) intMsg._( " Original thread name: \"" )._( origThreadName )._( "\"." );
            logInternal( Verbosity.INFO, "THR", intMsg );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * This method sets a human readable name to the current thread which is optionally included in
     * each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     **********************************************************************************************/
    public void mapThreadName(String threadName)
    {
        mapThreadName( threadName, -1 );
    }

    /** ****************************************************************************************
     * Stores an object which can afterwards be retrieved by invoking #retrieve.
     * Optional parameters \p{key} and \p{scope} offer various possibilities to reference
     * this data later.<br>
     *
     * To remove data from the store, pass \c null with parameter \p{data}.
     *
     * \attention
     * When data objects are 'overwritten', previous objects will be deleted internally.
     * Hence, only pointers to heap-allocated objects (created with \c new) may be passed!<br>
     * For more information, consult the [ALox User Manual](../manual.html).
     *
     * \note <em>Log Data</em> is a feature provided by \b %ALox to support debug-logging.
     *       It is not advised to use <em>Log Data</em> to implement application logic.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pkgLevel  Used only if parameter \p{scope} equals
     *                  \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     **********************************************************************************************/
    public void store( Object data, String key, Scope scope, int pkgLevel )
    {
        try { acquire();

            intMsg._();

            // We need a key. If none is given, we use a constant one indicating that storage is
            // associated exclusively with scope
            AString aKey= new AString(key);
            boolean keyWasEmtpy;
            if ( (keyWasEmtpy= aKey.isEmpty()) == true )
                aKey._( noKeyHashKey );

            // get the store
            scopeLogData.InitAccess( scope, pkgLevel, null );
            HashMap<AString, Object> map= scopeLogData.get();

            // create map entry
            if ( data != null )
            {
                if( map == null )
                {
                    map= new HashMap<AString, Object>();
                    scopeLogData.store( map );
                }
                Object previous= map.get( aKey );

                map.put( aKey, data );

                // log info if this was the last time
                intMsg._(  "Stored data " );

                if ( !keyWasEmtpy )
                    intMsg._( " with key \"" )._( tmpAS )._( "\" " );
                intMsg._( "in " );
                ALox.toString(scope, pkgLevel, intMsg);

                intMsg._( '.' );
                if ( previous != null )
                    intMsg._( " (Replaced previous.)" );
            }
            else
            {
                if( map != null &&  map.get( aKey ) != null )
                {
                    map.remove( aKey );
                    if ( map.size() == 0 )
                        scopeLogData.remove( null );

                    intMsg._( "Deleted map data " );
                }
                else
                    intMsg._( "No map data found to delete " );

                if ( !keyWasEmtpy )
                    intMsg._( " with key \"" )._( tmpAS )._( "\" " );
                intMsg._( "in " );
                ALox.toString(scope, pkgLevel, intMsg);
            }

            logInternal( Verbosity.INFO, "LGD", intMsg );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of #store providing default parameters.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     **********************************************************************************************/
    public void store( Object data, String key, Scope scope )
    {
        store( data, key, scope, 0 );
    }

    /** ********************************************************************************************
     * Overloaded version of #store providing default parameters.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     **********************************************************************************************/
    public void store( Object data, String key )
    {
        store( data, key, Scope.GLOBAL, 0 );
    }

    /** ********************************************************************************************
     * Overloaded version of #store providing default parameters.
     *
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     **********************************************************************************************/
    public void store( Object data )
    {
        store( data, null, Scope.GLOBAL, 0 );
    }

    /** ********************************************************************************************
     * Overloaded version of #store providing default parameters.
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pkgLevel  Used only if parameter \p{scope} equals
     *                  \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     **********************************************************************************************/
    public void store( Object  data, Scope scope, int  pkgLevel )
    {
        store( data, null, scope, pkgLevel );
    }

    /** ********************************************************************************************
     * Overloaded version of #store providing default parameters.
     * @param data      The data object to store.
     *                  If \c null, currently stored data will be removed.
     * @param scope     The \e %Scope that the data is bound to.
     **********************************************************************************************/
    public void store( Object  data, Scope scope )
    {
        store( data, null, scope, 0 );
    }


    /** ********************************************************************************************
     * Retrieves an object which was previously stored by invoking using #store.
     * Optional parameters \p{key} and \p{scope} offer various possibilities to reference
     * such objects.<br>
     *
     * \note If no <em>Log Data</em> object is found, an empty object is stored and returned.
     *
     * <p>
     * \note <em>Log Data</em> is a feature provided by \b %ALox to support debug-logging.
     *       It is not advised to use <em>Log Data</em> to implement application logic.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @param pkgLevel  Used only if parameter \p{scope} equals
     *                  \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     * @return The object, \c null if nothing was found.
     **********************************************************************************************/
    public Object  retrieve( String key, Scope scope,  int pkgLevel )
    {
        try { acquire();

            // get the data (create if not found)
            scopeLogData.InitAccess( scope, pkgLevel, null );
            Object returnValue= null;
            boolean keyWasEmtpy= false;
            for( int i= 0; i < 2 ; i++ )
            {
                // We need a key. If none is given, we use a constant one indicating that storage is
                // associated exclusively with scope
                tmpAS._()._(key);
                if ( (keyWasEmtpy= tmpAS.isEmpty()) == true )
                    tmpAS._( noKeyHashKey );

                HashMap<AString, Object> map= scopeLogData.get();
                if( map != null )
                    returnValue= map.get( tmpAS );

                if( returnValue == null )
                    store( new Object(), key, scope, pkgLevel );
                else
                    break;
            }

            // log info if this was the last time
            intMsg._(  "Data " );

            if ( !keyWasEmtpy )
                intMsg._( " with key \"" )._( key )._( "\" " );
            intMsg._( "in " );
            ALox.toString(scope, pkgLevel, intMsg);
            intMsg._( returnValue != null ? " received." : " not found." );

            logInternal( Verbosity.INFO, "LGD", intMsg );
            return returnValue;

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @param scope     The \e %Scope that the data is bound to.
     * @return The object, \c null if nothing was found.
     **********************************************************************************************/
    public Object  retrieve( String key, Scope scope )
    {
        return retrieve( key, scope, 0 );
    }

    /** ********************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param key       The optional key to the data.
     *                  If omitted (or empty or \c null), the data is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.GLOBAL, then the
     *                  data is unique to the \e Lox.
     * @return The object, \c null if nothing was found.
     **********************************************************************************************/
    public Object  retrieve( String key )
    {
        return retrieve( key, Scope.GLOBAL, 0 );
    }

    /** ********************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @return The object, \c null if nothing was found.
     **********************************************************************************************/
    public Object  retrieve()
    {
        return retrieve( null, Scope.GLOBAL, 0 );
    }

    /** ********************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param scope     The \e %Scope that the data is bound to.
     * @param pkgLevel  Used only if parameter \p{scope} equals
     *                  \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     * @return The object, \c null if nothing was found.
     **********************************************************************************************/
    public Object  retrieve( Scope scope, int pkgLevel )
    {
        return retrieve( null, scope, pkgLevel);
    }

    /** ********************************************************************************************
     * Overloaded version of #retrieve which omits parameters.
     *
     * @param scope     The \e %Scope that the data is bound to.
     * @return The object, \c null if nothing was found.
     **********************************************************************************************/
    public Object  retrieve( Scope scope )
    {
        return retrieve( null, scope, 0 );
    }

    /** ********************************************************************************************
     * This method logs the current configuration of this Lox and its encapsulated objects.
     * It uses method #getState to assemble the logable string.
     *
     * \note
     *   As an alternative to (temporarily) adding an invocation of <b>%Lox.State</b> to
     *   your code, \b %ALox provides configuration variable
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
     **********************************************************************************************/
    public void state( String domain, Verbosity verbosity, String headLine, int flags )
    {
        try { acquire();

            AString buf= new AString( 2048 );
            if (!CString.isNullOrEmpty( headLine ))
                buf._( headLine ).newLine();
            getState( buf, flags );
            entry( domain, verbosity, buf );

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of #state providing default value \c STATE_INFO_ALL for parameter \p{flags}.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param headLine  If given, a separated headline will be logged at first place.
     **********************************************************************************************/
    public void state( String domain, Verbosity verbosity, String headLine)
    {
        state( domain, verbosity, headLine,STATE_INFO_ALL );
    }

    /** ********************************************************************************************
     * This method collects state information about this lox in a formatted multi-line AString.
     * Parameter \p{flags} is a bit field with bits defined in constants of class \b %Lox
     * prefixed with \b "STATE_INFO_", e.g. \c %STATE_INFO_LOGGERS.
     *
     * @param buf       The target string.
     * @param flags     Flag bits that define which state information is collected.
     **********************************************************************************************/
    public void getState( AString buf, int flags )
    {
        try { acquire();

            ScopeDump scopeDump= new ScopeDump( scopeInfo.threadDictionary, noKeyHashKey, buf );

            // basic lox info
            if( (flags & Lox.STATE_INFO_BASIC) != 0 )
                buf._NC( "Name:            \"" )._( scopeInfo.getLoxName() )._('\"').newLine();
            if( (flags & Lox.STATE_INFO_VERSION) != 0 )
            {
                buf._NC( "Version:         " )._( ALox.version )._NC( " (Rev. " )._( ALox.revision )._( ')' ).newLine();
                buf._NC( "Thread-Safe:     " )._NC( getSafeness() ).newLine();
            }
            if( (flags & Lox.STATE_INFO_BASIC) != 0 )
                buf._NC( "#Log Calls:      " )._( cntLogCalls ).newLine();
            if( (flags & Lox.STATE_INFO_BASIC ) != 0 || (flags & Lox.STATE_INFO_VERSION ) != 0 )
                buf.newLine();

            //  domain substitutions
            if( (flags & Lox.STATE_INFO_DSR) != 0 )
            {
                buf._NC( "Domain Substitution Rules: " ).newLine();
                if( domainSubstitutions.size() > 0 )
                {
                    // get size
                    int maxWidth= 0;
                    for ( DomainSubstitutionRule it : domainSubstitutions )
                        if ( maxWidth < it.search.length() )
                             maxWidth = it.search.length();
                    maxWidth+= 2;

                    // write
                    for ( DomainSubstitutionRule it : domainSubstitutions )
                    {
                        buf._NC( "  " );
                        if (    it.type == DSRType.ENDS_WIDTH
                             || it.type == DSRType.SUBSTRING )
                            buf._( '*' );

                        buf._NC( it.search );

                        if (    it.type == DSRType.STARTS_WITH
                             || it.type == DSRType.SUBSTRING )
                            buf._( '*' );

                        buf.tab( maxWidth, 0 )
                           ._NC( " -> " )
                           ._NC( it.replacement );
                        buf.newLine();
                    }
                }
                else
                    buf._NC("  <no rules set>" ).newLine();
                buf.newLine();
            }

            // Log Once Counters
            if( (flags & Lox.STATE_INFO_ONCE) != 0 )
            {
                buf._NC( "Once() Counters: " ).newLine();
                if ( scopeDump.writeMap( scopeLogOnce ) == 0 )
                    buf._NC("  <no Once() counters set>" ).newLine();
                buf.newLine();
            }

            // Log Data
            if( (flags & Lox.STATE_INFO_LOG_DATA) != 0 )
            {
                buf._NC( "Log Data: " ).newLine();
                if ( scopeDump.writeMap( scopeLogData ) == 0 )
                    buf._NC("  <no data objects stored>" ).newLine();
                buf.newLine();
            }

            // Prefix Logables
            if( (flags & Lox.STATE_INFO_PREFIX_LOGABLES) != 0 )
            {
                buf._NC( "Prefix Logables: " ).newLine();
                int oldLength= buf.length();
                scopeDump.writePrefixes( scopePrefixes, 2 );
                logStateCollectPrefixes( domains, 2, buf );
                if ( oldLength == buf.length() )
                    buf._NC("  <no prefix logables set>" ).newLine();
                buf.newLine();
            }

            // thread mappings
            if( (flags & Lox.STATE_INFO_THREAD_MAPPINGS) != 0 )
            {
                buf._NC( "Named Threads:   " ).newLine();
                if (scopeInfo.threadDictionary.size() == 0)
                    buf._NC( "  No thread name mappings" ).newLine();
                else
                    for (long key : scopeInfo.threadDictionary.keySet())
                    {
                        buf._NC( "  " ).field()._( '(' )._( key )._( "):" ).field( 7, Alignment.LEFT )._( '\"' )
                                ._( scopeInfo.threadDictionary.get( new Long( key ) ) )._( '\"' );
                        buf.newLine();
                    }
                buf.newLine();
            }

            // Scope Domains
            if( (flags & Lox.STATE_INFO_SCOPE_DOMAINS) != 0 )
            {
                buf._NC( "Scope Domains: " ).newLine();
                if ( scopeDump.writeDomains( scopeDomains, 2 ) == 0 )
                    buf._NC("  <no scope domains set>" ).newLine();
                buf.newLine();
            }

            // Loggers (and their domains)
            if( (flags & Lox.STATE_INFO_LOGGERS) != 0 )
            {
                ArrayList<Domain> domsWithDiffVerb= new ArrayList<Domain>();
                StringBuffer tempSB= new StringBuffer();
                SimpleDateFormat dateFormatter= new SimpleDateFormat( "yyyy-MM-dd HH:mm:ss", Locale.US );
                Date date= new Date();

                for (int treeNo= 0; treeNo < 2; ++treeNo )
                {
                    Domain domTree;
                    if( treeNo==0 )
                    {
                         domTree= domains;
                         buf._NC( "Loggers:" ).newLine();
                    }
                    else
                    {
                         domTree= internalDomains;
                         buf._NC( "Loggers on Internal Domains:" ).newLine();
                    }
                    int cnt= 0;

                    tempSB.setLength( 0 );
                    for (int loggerNo= 0 ; loggerNo < domTree.countLoggers() ; loggerNo++)
                    {
                        cnt++;
                        Logger logger= domTree.getLogger( loggerNo );
                        tempSB.setLength( 0 );
                        buf._NC( "  " )._NC( logger ).newLine();
                        buf._NC( "    Lines logged:  " )._( logger.cntLogs ).newLine();
                        buf._NC( "    Creation time: " )
                           ._( dateFormatter.format( logger.timeOfCreation.inJavaDate( date ), tempSB, new FieldPosition( 0 ) ) )
                           .newLine(); tempSB.setLength(0);
                        buf._NC( "    Last log time: " )
                           ._( dateFormatter.format( logger.timeOfLastLog .inJavaDate( date ), tempSB, new FieldPosition( 0 ) ) )
                           .newLine();

                        domsWithDiffVerb.clear();
                        logStateDomainsWithDiffVerb( domTree, loggerNo, domsWithDiffVerb);
                        for ( Domain dom : domsWithDiffVerb )
                        {
                            buf._NC( "    " )
                               ._NC(  dom == domsWithDiffVerb.get(0) ? "Verbosities:   "
                                                                     : "               " );

                            int tabRef= buf.length();
                            buf._( dom.fullPath );
                            buf.insertChars( ' ',  maxDomainPathLength + 1 - buf.length() + tabRef );
                            buf._("= "); ALox.toString(  dom.getVerbosity( loggerNo ), dom.getPriority(loggerNo), buf )
                               .newLine();
                        }

                        buf.newLine();
                    }

                    if ( cnt == 0 )
                        buf._NC("  <no loggers attached>" ).newLine();
                    buf.newLine();

                }
            }

            // Domains
            if( (flags & Lox.STATE_INFO_INTERNAL_DOMAINS) != 0 )
            {
                buf._NC( "Internal Domains:" ).newLine();
                logStateDomainRecursive( internalDomains, buf );
                buf.newLine();
            }

            // Domains
            if( (flags & Lox.STATE_INFO_DOMAINS) != 0 )
            {
                buf._NC( "Domains:" ).newLine();
                logStateDomainRecursive( domains, buf );
                buf.newLine();
            }
        } finally { release(); }
    }

    /** ********************************************************************************************
     * Internal method used by State() to recursively log Domain instances.
     *
     * @param domain      The Domain instance to log out.
     * @param buf         The buffer to log to.
     **********************************************************************************************/
    protected void logStateDomainRecursive(Domain domain, AString buf)
    {
        int reference= buf.length();
        buf._( "  " )._( domain );
        int idx= buf.indexOf( '[', reference );
        buf.insertChars( ' ', maxDomainPathLength + 5 - idx + reference, idx );
        buf.newLine();

        // loop over all sub domains (recursion)
        for (Domain subDomain : domain.subDomains)
            logStateDomainRecursive( subDomain, buf );
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
        for ( Domain.PL pfl : domain.prefixLogables )
        {
            target.insertChars( ' ', indentSpaces );
            target._('\"');
            int idx= target.length();
            target._NC( pfl.logable );
            ESC.replaceToReadable( target, idx );
            target._('\"');

            if ( pfl.includeOtherPLs == Inclusion.EXCLUDE )
                target._NC( " (Excl.)" );
            target.tab( 25 );
            target._NC( "<domain>           [" )._( domain.fullPath )._(']').newLine();
        }

        for( Domain it : domain.subDomains )
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
    protected void logStateDomainsWithDiffVerb( Domain domain, int loggerNo, ArrayList<Domain> results )
    {
        if (    domain.parent == null
            ||  domain.parent.getVerbosity(loggerNo) != domain.getVerbosity(loggerNo) )
            results.add( domain );

        for( Domain it : domain.subDomains )
            logStateDomainsWithDiffVerb( it, loggerNo, results );
    }


    // #############################################################################################
    // Main logging methods
    // #############################################################################################

    /** ********************************************************************************************
     * Logs a list of \e Logables using the given \e %Verbosity.
     *
     * This method is usually \b not used directly. Instead, methods
     * #info, #verbose, #warning and #error provide simpler interfaces.
     *
     * Hence, the use of this method is recommended only if the verbosity of a log statement
     * is is evaluated only at runtime.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param logables  The objects to log.
     **********************************************************************************************/
    public void entry( String domain, Verbosity verbosity, Object... logables )
    {
        try { acquire();

            // auto-initialization of ALox
            ALox.init();

            // auto-initialization of debug loggers
            if (domains.countLoggers() == 0 && this == Log.LOX)
                Log.addDebugLogger( this );

            cntLogCalls++;
            if ( domains.countLoggers() == 0 )
                return;
            log( evaluateResultDomain( domain ), verbosity, logables, Inclusion.INCLUDE );
        }
        finally  { release(); }
    }

    /** ********************************************************************************************
     * Logs a list of \e Logables with the given \e %Verbosity.
     *
     * If more than one \e Logable is given and the first one is of string type and comprises a
     * valid domain name, then this first argument is interpreted as a the domain name!
     * Valid domain names are strings that consists only of characters of the following set:
     * - upper case letters,
     * - numbers,
     * - hyphen (\c '-') and
     * - underscore (\c '_').
     *
     * If a first \e Logable could be misinterpreted as being a domain name, an empty string
     * (the "neutral" domain) has to be added as a first argument. Alternatively, a character
     * which is illegal in respect to domain names could be added to the first argument,
     * for example a simple space at the end of an output string.
     *
     * \note
     *   This method allows a consistent interface of overloaded methods \b %Info, \b Error,
     *   etc, without introducing a separate version which excepts a then mandatory domain
     *   parameter.
     *   The little drawback of the auto detection is the possibility of ambiguous invocations.
     *
     * @param verbosity   The verbosity.
     * @param logables    The logables with optionally a detectable domain name as a
     *                    first argument.
     **********************************************************************************************/
    public void entryDetectDomain( Verbosity  verbosity, Object... logables )
    {
        if( logables.length > 1 )
        {
            if( logables[0] instanceof CharSequence )
            {
                CharSequence firstArg= (CharSequence) logables[0];

                boolean illegalCharacterFound= false;

                if( firstArg.length() > 0 )
                {

                    // accept internal domain at the start
                    int idx= 0;
                    if( firstArg.charAt(0) == ALox.INTERNAL_DOMAINS.charAt( 0 ) )
                    {
                        while(      ++idx < ALox.INTERNAL_DOMAINS.length()
                                &&    idx < firstArg.length()
                                &&  firstArg.charAt( idx ) == ALox.INTERNAL_DOMAINS.charAt( idx )
                             );
                        if( idx !=  ALox.INTERNAL_DOMAINS.length() )
                            idx= 0;
                    }

                    // loop over domain and check for illegal characters
                    for( ; idx < firstArg.length() ; ++idx )
                    {
                        char c= firstArg.charAt(idx);
                        if (   !(    ( c >= '0' && c <= '9' )
                                  || ( c >= 'A' && c <= 'Z' )
                                  || c == '-'
                                  || c == '_'
                                  || c == '/'
                                  || c == '.'
                                )
                           )
                        {
                            illegalCharacterFound= true;
                            break;
                        }
                    }
                }
                if ( illegalCharacterFound )
                {
                    entry( null, verbosity, logables );
                    return;
                }

                Object[] newLogables= new Object[ logables.length - 1 ];
                for(int i= 0; i < newLogables.length; i++ )
                    newLogables[i]= logables[i + 1];
                entry( firstArg instanceof String ? ((String) firstArg) : firstArg.toString() , verbosity, newLogables );
                return;
            }
        }

        entry( null, verbosity, logables );
    }

    /** ********************************************************************************************
     * Logs a list of \e Logables using \ref Verbosity.VERBOSE "Verbosity.VERBOSE".
     *
     * The first \e logable provided may be a domain name. All values are passed to
     * #entryDetectDomain. See documentation of this method for information on how to avoid
     * ambiguities in respect to domain names.
     *
     * If one of the arguments (or a single argument given) is of type \c Object[], then the
     * contents of this list is inserted into the list of logables.
     * This allows to collect logables prior to invoking the method.
     * In the C# version, where flexibility of parameter passing is limited due to the use of
     * compiler-inserted parameters, parameters of type \c Object[] can also be used to
     * provide more than four logables.
     *
     * @param logables  The list of \e Logables, optionally including a domain name at the start.
     **********************************************************************************************/
    public void verbose( Object... logables )
    {
        entryDetectDomain( Verbosity.VERBOSE, logables );
    }

    /** ********************************************************************************************
     * Logs a list of \e Logables using \ref Verbosity.INFO "Verbosity.INFO".
     *
     * The first \e logable provided may be a domain name. All values are passed to
     * #entryDetectDomain. See documentation of this method for information on how to avoid
     * ambiguities in respect to domain names.
     *
     * If one of the arguments (or a single argument given) is of type \c Object[], then the
     * contents of this list is inserted into the list of logables.
     * This allows to collect logables prior to invoking the method.
     * In the C# version, where flexibility of parameter passing is limited due to the use of
     * compiler-inserted parameters, parameters of type \c Object[] can also be used to
     * provide more than four logables.
     *
     * @param logables  The list of \e Logables, optionally including a domain name at the start.
     **********************************************************************************************/
    public void info( Object... logables )
    {
        entryDetectDomain( Verbosity.INFO, logables );
    }

    /** ********************************************************************************************
     * Logs a list of \e Logables using \ref Verbosity.WARNING "Verbosity.WARNING".
     *
     * The first \e logable provided may be a domain name. All values are passed to
     * #entryDetectDomain. See documentation of this method for information on how to avoid
     * ambiguities in respect to domain names.
     *
     * If one of the arguments (or a single argument given) is of type \c Object[], then the
     * contents of this list is inserted into the list of logables.
     * This allows to collect logables prior to invoking the method.
     * In the C# version, where flexibility of parameter passing is limited due to the use of
     * compiler-inserted parameters, parameters of type \c Object[] can also be used to
     * provide more than four logables.
     *
     * @param logables  The list of \e Logables, optionally including a domain name at the start.
     **********************************************************************************************/
    public void warning( Object... logables )
    {
        entryDetectDomain( Verbosity.WARNING, logables );
    }

    /** ********************************************************************************************
     * Logs a list of \e Logables using \ref Verbosity.ERROR "Verbosity.ERROR".
     *
     * The first \e logable provided may be a domain name. All values are passed to
     * #entryDetectDomain. See documentation of this method for information on how to avoid
     * ambiguities in respect to domain names.
     *
     * If one of the arguments (or a single argument given) is of type \c Object[], then the
     * contents of this list is inserted into the list of logables.
     * This allows to collect logables prior to invoking the method.
     * In the C# version, where flexibility of parameter passing is limited due to the use of
     * compiler-inserted parameters, parameters of type \c Object[] can also be used to
     * provide more than four logables.
     *
     * @param logables  The list of \e Logables, optionally including a domain name at the start.
     **********************************************************************************************/
    public void error( Object... logables )
    {
        entryDetectDomain( Verbosity.ERROR, logables );
    }


    /** ********************************************************************************************
     * Logs a list of \e Logables only if parameter \p{condition} is not \c true.
     *
     * If executed, \ref Verbosity.ERROR is used.
     *
     * The first \e logable provided may be a domain name. All values are passed to
     * #entryDetectDomain. See documentation of this method for information on how to avoid
     * ambiguities in respect to domain names.
     *
     * If one of the arguments (or a single argument given) is of type \c Object[], then the
     * contents of this list is inserted into the list of logables.
     * This allows to collect logables prior to invoking the method.
     * In the C# version, where flexibility of parameter passing is limited due to the use of
     * compiler-inserted parameters, parameters of type \c Object[] can also be used to
     * provide more than four logables.
     *
     * \note This Method's name starts with capital letter, as <c>'assert'</c> is a Java keyword.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param logables  The list of \e Logables, optionally including a domain name at the start.
     **********************************************************************************************/
    public void Assert( boolean condition, Object... logables )
    {
        if (!condition)
            entryDetectDomain( Verbosity.ERROR, logables );
        else
            cntLogCalls++;
    }

    /** ********************************************************************************************
     * Logs a list of \e Logables only if the parameter \p{condition} is \c true.
     *
     * If one of the arguments (or a single argument given) is of type \c Object[], then the
     * contents of this list is inserted into the list of logables.
     * This allows to collect logables prior to invoking the method.
     * In the C# version, where flexibility of parameter passing is limited due to the use of
     * compiler-inserted parameters, parameters of type \c Object[] can also be used to
     * provide more than four logables.
     *
     * \note This Method's name starts with capital letter, as <c>'if'</c> is a Java keyword.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The verbosity.
     * @param logables  The objects to log.
     **********************************************************************************************/
    public void If( boolean condition, String domain, Verbosity verbosity, Object... logables )
    {
        if (condition)
            entry( domain, verbosity, logables );
        else
            cntLogCalls++;
    }

    /** ********************************************************************************************
     * Logs a list of \e Logables only if the parameter \p{condition} is \c true.
     * This overloaded version omits parameter \p{domain}.
     *
     * The first \e logable provided may be a domain name. All values are passed to
     * #entryDetectDomain. See documentation of this method for information on how to avoid
     * ambiguities in respect to domain names.
     *
     * If one of the arguments (or a single argument given) is of type \c Object[], then the
     * contents of this list is inserted into the list of logables.
     * This allows to collect logables prior to invoking the method.
     * In the C# version, where flexibility of parameter passing is limited due to the use of
     * compiler-inserted parameters, parameters of type \c Object[] can also be used to
     * provide more than four logables.
     *
     * \note This Method's name starts with capital letter, as <c>'if'</c> is a Java keyword.
     *
     * @param condition If \c false, the <em>Log Statement</em> is executed.
     * @param verbosity The verbosity.
     * @param logables  The objects to log.
     **********************************************************************************************/
    public void If( boolean condition, Verbosity verbosity, Object... logables )
    {
        if (condition)
            entryDetectDomain( verbosity, logables );
        else
            cntLogCalls++;
    }

    /** ********************************************************************************************
     * Logs given \e logables once, up to \p{quantity} times or every n-th time.
     * In its simplest overloaded version, the counter is bound to the source code line, hence,
     * only the first execution of this exact <em>Log Statement</em> is executed.
     *
     * Using parameter \p{group}, a set of <em>Log Statements</em> that share the same group key, can be
     * grouped and of such set, only the one which is first executed actually logs.<br>
     * Alternatively, when \p{key} is omitted (or null or empty), but a
     * \ref com.aworx.lox.Scope "Scope" is given with parameter \p{scope}, then the
     * counter is associated with the scope.<br>
     * Finally, parameters \p{key} and \p{scope} can also be used in combination. The key is
     * then unique in respect to the \ref com.aworx.lox.Scope "Scope" provided.
     *
     * Using, none, one or both of the parameters \p{group} and \p{scope}, among others, the
     * following use cases can be achieved.
     * - %Log a specific statement up to n-times.
     * - %Log only the first n of a group of statements.
     * - %Log only the first n statements within a method.
     * - %Log only the first n statements belonging to the same group and method .
     * - %Log only the first n statements within any method of
     *   - a class
     *   - a package
     *   - a parent package with all sub-packages
     * - %Log only the first n statements which belong to the same group and are placed within
     *   any method of
     *   - a class
     *   - a package
     *   - a parent package with all sub-packages
     * - %Log a <em>Log Statement</em> n-times per new thread.
     * - %Log only the first n statements of a group of statements executed by a specific thread.
     *
     * \note
     *   Unlike other methods of this class which accept more than one logable, this
     *   method and its overloaded variants accept only one object. To supply several objects
     *   at once, an \c Object[] may be passed with parameter \p{logables}, like in the
     *   following sample:
     *   \snippet "UT_alox_lox.java"      DOX_ALOX_LOX_ONCE
     *
     *<p>
     *<p>
     * \note
     *   Due to the limitations of the Java language to dissolve ambiguities when invoking
     *   overloaded methods, most of the overloads provided await parameters
     *   \p{domain} and \p{verbosity} at the start. This is in difference to <b>ALox for C++</b>
     *   and <b>ALox for C#</b>, where overloaded methods always default these parameters to \c null
     *   respectively \c %Verbosity.INFO.<br>
     *   Fortunate exceptions are
     *   - <b>%once(Object logable)</b> and
     *   - <b>%once(Object logable, int quantity)</b>.
     *
     * \note
     *   Furthermore, to to cover the most  frequent use cases, methods
     *   - <b>%once(Object logable, int quantity, String group)</b>,
     *   - <b>%once(Object logable, int quantity, %Scope scope, int pkgLevel)</b> and
     *   - <b>%once(Object logable, int quantity, %Scope scope)</b>
     *
     * \note
     *   have been added.  While their parameter order is 'wrong' and therefore need \p{quantity} to be specified,
     *   still they are nice shortcuts.
     *
     * When parameter \p{quantity} is a negative value, the log statement is executed every n-th time
     * instead n-times. E.g, if \p{quantity} is \c -5, the first statement is executed and afterwards
     * every fifth invocation.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p{scope}.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pkgLevel  Used only if parameter \p{scope} equals
     *                  \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     *                  If negative, the first and every "-quantity-th" statement is executed.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logables, String group, Scope scope, int pkgLevel, int quantity)
    {
        try { acquire();

            // We need a group. If none is given, there are two options:
            tmpAS._()._( group );
            boolean groupWasEmtpy;
            if ( (groupWasEmtpy= tmpAS.isEmpty()) == true )
            {
                // GLOBAL scope: exact code line match match
                if (scope == Scope.GLOBAL)
                {
                    scope= Scope.METHOD;
                    tmpAS._( '#' )._( scopeInfo.getLineNumber() );
                }

                // not GOBAL scope: Unique tempAS per Scope
                else
                    tmpAS._( noKeyHashKey );
            }

            // get the store
            scopeLogOnce.InitAccess( scope, pkgLevel, null );
            HashMap<AString, int[]> map= scopeLogOnce.get();
            if (map == null)
            {
                map= new HashMap<AString, int[]>();
                scopeLogOnce.store( map );
            }

            int[] qty= map.get( tmpAS );
            if (qty == null) map.put( new AString( tmpAS ), qty= new int[1] );

            // log Once
            if ( quantity >= 0 )
            {
                if (qty[0] < quantity)
                {
                    qty[0]++;

                    // do the log
                    entry( domain, verbosity, logables );

                    // log info if this was the last time
                    if (qty[0] == quantity)
                    {
                        intMsg._()._( "Once() reached limit of " )._( quantity )._( " logs. No further logs for " );

                        if (groupWasEmtpy)
                        {
                            if (scope == Scope.GLOBAL)
                                intMsg._( "this line" );
                            else
                                ALox.toString( scope, pkgLevel, intMsg );
                        }
                        else
                        {
                            intMsg._( "group \"" )._( tmpAS )._( '\"' );
                            if (scope != Scope.GLOBAL)
                            {
                                intMsg._( " in " );
                                ALox.toString( scope, pkgLevel, intMsg );
                            }
                        }
                        intMsg._( '.' );

                        logInternal( Verbosity.INFO, "", intMsg );
                    }
                }
            }
            // log Nth
            else
            {
                if ( qty[0]++ % -quantity == 0 )
                    entry( domain, verbosity, logables );
            }

        } finally { release(); }
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p{scope}.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pkgLevel  Used only if parameter \p{scope} equals
     *                  \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logables, String group, Scope scope, int pkgLevel)
    {
        once( domain, verbosity, logables, group, scope, pkgLevel, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p{scope}.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param scope     The \e %Scope that the group or counter is bound to.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logables, String group, Scope scope )
    {
        once( domain, verbosity, logables, group, scope, 0, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p{scope}.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logables, String group )
    {
        once( domain, verbosity, logables, group, Scope.GLOBAL, 0, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p{scope}.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logables, String group, int quantity )
    {
        once( domain, verbosity, logables, group, Scope.GLOBAL, 0, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pkgLevel  Used only if parameter \p{scope} equals
     *                  \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logables, Scope scope, int pkgLevel, int quantity)
    {
        once( domain, verbosity, logables, null, scope, pkgLevel, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pkgLevel  Used only if parameter \p{scope} equals
     *                  \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logables, Scope scope, int pkgLevel)
    {
        once( domain, verbosity, logables, null, scope, pkgLevel, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param scope     The \e %Scope that the group or counter is bound to.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logables, Scope scope)
    {
        once( domain, verbosity, logables, null, scope, 0, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logables  )
    {
        once( domain, verbosity, logables, null, Scope.GLOBAL, 0, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param domain    Optional <em>Log Domain</em> which is combined with <em>%Scope Domains</em>
     *                  set for the \e %Scope of invocation.
     * @param verbosity The \e Verbosity of the <em>Log Statement</em> (if performed).
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     **********************************************************************************************/
    public void once(String domain, Verbosity verbosity, Object logables, int quantity  )
    {
        once( domain, verbosity, logables, null, Scope.GLOBAL, 0, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     **********************************************************************************************/
    public void once( Object logables)
    {
        once( null, Verbosity.INFO, logables, null, Scope.GLOBAL, 0, 1 );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     **********************************************************************************************/
    public void once( Object logables, int quantity)
    {
        once( null, Verbosity.INFO, logables, null, Scope.GLOBAL, 0, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     * @param group     The optional name of the statement group . If used, all statements that
     *                  share the same group name are working on the same counter (according
     *                  to the \p{scope}.)
     *                  If omitted (or empty or null), the counter is is bound to the \e %Scope
     *                  provided. If omitted and \p{scope} is Scope.Global, then the
     *                  counter is associated exclusively with the single <em>Log Statement</em> itself.
    **********************************************************************************************/
    public void once( Object logables, int quantity, String group  )
    {
        once( null, Verbosity.INFO, logables, group, Scope.GLOBAL, 0, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     * @param scope     The \e %Scope that the group or counter is bound to.
     * @param pkgLevel  Used only if parameter \p{scope} equals
     *                  \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                  to reference parent packages. Optional and defaults to \c 0.
    **********************************************************************************************/
    public void once( Object logables, int quantity, Scope scope, int pkgLevel  )
    {
        once( null, Verbosity.INFO, logables, null, scope, pkgLevel, quantity );
    }

    /** ********************************************************************************************
     * Overloaded version of \ref once.
     *
     * @param logables  The object(s) to log. (Multiple objects may be provided as an Object[].)
     * @param quantity  The number of logs to be performed. As the name of the method indicates,
     *                  this defaults to \c 1.
     * @param scope     The \e %Scope that the group or counter is bound to.
    **********************************************************************************************/
    public void once( Object logables, int quantity, Scope scope  )
    {
        once( null, Verbosity.INFO, logables, null, scope, 0, quantity );
    }


    // #############################################################################################
    // internals
    // #############################################################################################

    /** ****************************************************************************************
     * Assembles the resulting domain from the given \p{domainPath} and the Scope Domain paths
     * (see #setDomain) according to the scope identified by scopeInfo.
     * The resulting full domain string is assembled from inner to outer scope.
     * If \p{domainPath}, respectively as soon as any of the scope levels' Scope Domain paths
     * starts with the character defined in
     * \ref com.aworx.lox.detail.Domain.PATH_SEPARATOR "Domain.PATH_SEPARATOR",
     * the evaluation is stopped (the path is interpreted as absolute).
     *
     * @param domainPath The domain path. If starting with the character defined in
     *                   \ref com.aworx.lox.detail.Domain.PATH_SEPARATOR "Domain.PATH_SEPARATOR",
     *                   no Scope Domains are applied.
     * @return The resulting \ref com.aworx.lox.detail.Domain "Domain".
     **********************************************************************************************/
    protected Domain evaluateResultDomain(String domainPath)
    {
        // 0. internal domain tree?
        if (domainPath != null && domainPath.startsWith( ALox.INTERNAL_DOMAINS ))
        {
            // cut "$/" from the path
            resDomain._()._( domainPath, ALox.INTERNAL_DOMAINS.length() ).trim();
            return findDomain( internalDomains, resDomain );
        }

        // loop over scopes
        scopeDomains.initWalk( Scope.THREAD_INNER,
                // we have to provide null if parameter is empty
                CString.isNullOrEmpty( domainPath ) ? null : tmpAS._()._( domainPath ) );
        AString nextDefault;
        resDomain._();
        while ((nextDefault= scopeDomains.walk()) != null)
        {
            if (resDomain.isNotEmpty()) resDomain.insertAt( "/", 0 );
            resDomain.insertAt( nextDefault, 0 );

            // absolute path? That's it
            if (resDomain.charAtStart() == Domain.PATH_SEPARATOR) break;
        }
        return findDomain( domains, resDomain );
    }

    /** ********************************************************************************************
     * Invokes \b Find on the given domain and logs internal message when the domain was
     * not known before.
     * @param domainSystem The domain system. Either the standard or the internal one.
     * @param domainPath   The domain path.
     * @return The resulting \ref com.aworx.lox.detail.Domain "Domain".
     **********************************************************************************************/
    @SuppressWarnings ("null")
    Domain findDomain(Domain domainSystem, AString domainPath)
    {
        AString substPath= domainSystem == domains ? tmpSubstitutionPath
                                                   : tmpSubstitutionPathInternalDomains;

        int maxSubstitutions= 10;
        for(;;)
        {
            // loop for creating domains, one by one
            @SuppressWarnings ("null")
            Domain dom= null;
            for(;;)
            {
                dom= domainSystem.find( domainPath, 1, booleanOutputParam );
                boolean wasCreated= booleanOutputParam[0];
                if ( wasCreated )
                {
                    // get maximum domain path length (for nicer State output only...)
                    if (maxDomainPathLength < dom.fullPath.length())
                        maxDomainPathLength=  dom.fullPath.length();

                    // log info on new domain
                    intMsg._()._( '\'' )._( dom.fullPath )._( "' registered." );
                    logInternal( Verbosity.INFO, "DMN", intMsg );
                }

                // read domain from config
                if ( !dom.configurationRead )
                {
                    dom.configurationRead= true;

                    Variable variable= new Variable();
                    for ( int i= 0; i < dom.countLoggers(); ++i )
                    {
                        Logger logger= dom.getLogger(i);
                        if ( 0 != ALox.config.load(variable.declare( ALox.VERBOSITY, getName(), logger.getName() )) )
                            getVerbosityFromConfig( logger, dom, variable );
                    }

                    getDomainPrefixFromConfig( dom );

                }

                if ( wasCreated )
                {
                    // log inherited setting for each logger
                    if (domainSystem.countLoggers() == 0)
                        logInternal( Verbosity.VERBOSE, "DMN", intMsg._()._( "No loggers set, yet." ) );
                    else
                    {
                        for (int i= 0 ; i < domainSystem.countLoggers() ; i++)
                        {
                            intMsg._()._( "  \"" )._( dom.getLogger( i ).getName() )._( "\": " );
                            intMsg.insertChars( ' ', maxLoggerNameLength  + 6 - intMsg.length() );
                            intMsg._( dom.fullPath )
                                  ._NC( " = " ); ALox.toString( dom.getVerbosity( i ), dom.getPriority(i), intMsg );
                            logInternal( Verbosity.VERBOSE, "DMN", intMsg );
                        }
                    }
                }
                else
                    break;
            }

            // apply domain substitutions
            if( domainSubstitutions.size() > 0 )
            {
                substPath.clear();
                while( maxSubstitutions-- > 0  )
                {
                    // loop over rules
                    boolean substituted= false;
                    for( DomainSubstitutionRule rule : domainSubstitutions )
                    {
                        switch( rule.type )
                        {
                            case STARTS_WITH:
                                if( substPath.isEmpty() )
                                {
                                    if ( dom.fullPath.startsWith( rule.search, Case.SENSITIVE ) )
                                    {
                                        substPath._( rule.replacement )._( dom.fullPath, rule.search.length() );
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }
                                else
                                {
                                    if ( substPath.startsWith( rule.search, Case.SENSITIVE ) )
                                    {
                                        substPath.replaceSubstring( rule.replacement, 0, rule.search.length()  );
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }

                            break;

                            case ENDS_WIDTH:
                                if( substPath.isEmpty() )
                                {
                                    if ( dom.fullPath.endsWith( rule.search, Case.SENSITIVE ) )
                                    {
                                        substPath._( dom.fullPath, 0, dom.fullPath.length() - rule.search.length() )._( rule.replacement );
                                        substituted= true;
                                        continue;
                                    }
                                }
                                else
                                {
                                    if ( substPath.endsWith( rule.search, Case.SENSITIVE ) )
                                    {
                                        substPath.deleteEnd( rule.search.length() )._( rule.replacement );
                                        substituted= true;
                                        continue;
                                    }
                                }
                            break;

                            case SUBSTRING:
                                if( substPath.isEmpty() )
                                {
                                    int idx= dom.fullPath.indexOf( rule.search, 0, Case.SENSITIVE );
                                    if ( idx >= 0 )
                                    {
                                        substPath._( dom.fullPath, 0, idx )._( rule.replacement)._( dom.fullPath, idx + rule.search.length() );
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }
                                else
                                {
                                    int idx= substPath.indexOf( rule.search, 0, Case.SENSITIVE );
                                    if ( idx >= 0 )
                                    {
                                        substPath.replaceSubstring( rule.replacement, idx, rule.search.length()  );
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }
                            break;


                            case EXACT:
                            {
                                if( substPath.isEmpty() )
                                {
                                    if ( dom.fullPath.equals( rule.search ) )
                                    {
                                        substPath._( rule.replacement);
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }
                                else
                                {
                                    if ( substPath.equals( rule.search) )
                                    {
                                        substPath._()._( rule.replacement );
                                        substituted= true;
                                        continue; //next rule
                                    }
                                }
                            }
                            break;

                        }//switch rule type

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

                    logInternal( Verbosity.ERROR, "DMN", intMsg );
                }

                // anything substituted?
                if( substPath.length() > 0 )
                {
                    domainPath= substPath;
                    continue;
                }
            }

            return dom;
        }

    }

    /** ********************************************************************************************
     * Simple helper method that inserts a logable at the front of given \p{list}.
     * If the logable is an object array, each object will be inserted.
     *
     * @param list      The logable list
     * @param logable   The logable or array of logables.
     **********************************************************************************************/
    protected static void insertLogables( ArrayList<Object> list, Object logable )
    {
        if ( logable instanceof Object[] )
        {
            Object[] logableArray= (Object[]) logable;
            for (int i= logableArray.length - 1 ; i >= 0 ; --i )
                list.add( 0, logableArray[i] );
        }
        else
            list.add( 0, logable );
    }

    /** ********************************************************************************************
     * This method is looping over the \e Loggers, checking their verbosity against the given
     * one, and, if they match, invoke the log method of the \e Logger.
     * With the first logger identified to be active, the <em>Prefix Objects</em> get
     * collected from the scope store.
     * @param dom       The domain to log on
     * @param verbosity The verbosity.
     * @param logables  The objects to log.
     * @param prefixes  Denotes if prefixes should be included or not.
     **********************************************************************************************/
    protected void log( Domain dom, Verbosity verbosity, Object[] logables, Inclusion prefixes )
    {
        dom.cntLogCalls++;

        // get a logable list (reuse, one per recursive log)
        while( logableLists.size() < cntAcquirements )
            logableLists.add( new ArrayList<Object>() );
        ArrayList<Object> logableList= logableLists.get( cntAcquirements - 1 );

        for ( int i= 0; i < dom.countLoggers() ; i++ )
            if( dom.isActive( i, verbosity ) )
            {
                // lazily collect objects once
                if ( logableList.size() == 0 )
                {
                    // OK, this is a little crude, but the simplest solution: As class ScopeStore sees
                    // null objects as nothing and won't return them in a walk, we replace null by
                    // an object (ourselves) and fix this in the loop back to null
                    scopePrefixes.initWalk( Scope.THREAD_INNER, logables != null ? (Object) logables : (Object) this );
                    Object next;
                    while( (next= scopePrefixes.walk() ) != null )
                    {
                        if ( next == logables )
                            for( int l= logables.length -1 ; l >= 0; --l )
                                insertLogables( logableList, logables[l] );

                        else if (    next != this                    // see comment above
                                  && prefixes == Inclusion.INCLUDE ) // this is false for internal domains (only domain specific logables are added there)
                            insertLogables( logableList, next );

                        // was this the actual? then insert domain-associated logables now
                        boolean excludeOthers= false;
                        if( next == logables || next == this )
                        {
                            int qtyThreadInner= logableList.size() -1;
                            Domain pflDom= dom;
                            while ( pflDom != null )
                            {
                                for( int ii= pflDom.prefixLogables.size() -1 ; ii >= 0 ; ii-- )
                                {
                                    Domain.PL pl= pflDom.prefixLogables.get(ii);
                                    insertLogables( logableList, pl.logable );
                                    if ( pl.includeOtherPLs == Inclusion.EXCLUDE )
                                    {
                                        excludeOthers= true;
                                        break;
                                    }
                                }

                                pflDom= excludeOthers ? null :  pflDom.parent;
                            }

                            // found a stoppable one? remove those from thread inner and break
                            if (excludeOthers)
                            {
                                for ( int ii= 0; ii < qtyThreadInner ; ii++ )
                                    logableList.remove( logableList.size() - 1 );
                                break;
                            }
                        }
                    }
                }

                Logger logger= dom.getLogger( i );
                logger.acquire();
                    logger.cntLogs++;
                    logger.log( dom, verbosity, logableList, scopeInfo );
                    logger.timeOfLastLog.set();
                logger.release();
            }
        logableList.clear();
    }

    /** ********************************************************************************************
     * Logs an internal error message using the internal domain tree as defined in
     * \ref com.aworx.lox.ALox.INTERNAL_DOMAINS "ALox.INTERNAL_DOMAINS".
     *
     * @param verbosity The verbosity.
     * @param subDomain The sub-domain of the internal domain to log into.
     * @param logable   The message.
     **********************************************************************************************/
    protected  void logInternal( Verbosity verbosity, String subDomain, AString logable )
    {
        log( findDomain( internalDomains, resDomainInternal._()._NC( subDomain ) ),
            verbosity, new Object[] {logable}, Inclusion.EXCLUDE );
    }

    /** ********************************************************************************************
     * Implementation of the interface method fetching all possible parameters.
     *
     * @param scopeDomain  The domain path to register.
     * @param scope        The scope that the given \p{domain} should be registered for.
     *                     Available Scope definitions are platform/language dependent.
     * @param packageLevel Used only if parameter \p{scope} equals
     *                     \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE"
     *                     to reference parent packages. Optional and defaults to \c 0.
     * @param removeNTRSD  Used to remove thread-related Scope Domains (and is true only when
     *                     invoked by interface method #removeThreadDomain.
     * @param thread       The thread to set/unset a thread-related Scope Domain for.
     **********************************************************************************************/
    protected void setDomainImpl(String scopeDomain, Scope scope, int packageLevel, boolean removeNTRSD, Thread thread)
    {
        //note: the public class interface assures that \p{removeNTRSD} (named thread-related
        //      scope domain) only evaluates true for thread related scopes
        try { acquire();

            boolean newValueIsNotEmpty= scopeDomain != null && scopeDomain.length() > 0;

            AString previousScopeDomain;
            scopeDomains.InitAccess( scope, packageLevel, thread );
            if (removeNTRSD)
            {
                AString searchedValue= new AString( scopeDomain );
                previousScopeDomain= scopeDomains.remove( searchedValue );
            }
            else
            {
                if (newValueIsNotEmpty)
                {
                    AString newValue= new AString( scopeDomain );
                    newValue.trim();
                    previousScopeDomain= scopeDomains.store( newValue );
                }
                else
                    previousScopeDomain= scopeDomains.remove( null );
            }

            // log info on this
            if (!removeNTRSD && newValueIsNotEmpty)
            {
                intMsg._()._( '\'' )._( scopeDomain )._( "\' set as default for " );
                ALox.toString( scope, packageLevel, intMsg )._( '.' );

                if (previousScopeDomain == null)
                    logInternal( Verbosity.INFO, "DMN", intMsg );
                else
                {
                    if ( previousScopeDomain.equals( scopeDomain ) )
                    {
                        intMsg._( " (Was already set.)" );
                        logInternal(  Verbosity.VERBOSE,  "DMN", intMsg );
                    }
                    else
                    {
                        intMsg._NC( " Replacing previous default '" )._NC( previousScopeDomain )._('\'');
                        logInternal(  Verbosity.WARNING,  "DMN", intMsg );
                    }
                }
            }
            else
            {
                if (previousScopeDomain != null)
                {
                    intMsg._()._( '\'' )._( previousScopeDomain )._( "\' removed from " );
                    ALox.toString( scope, packageLevel, intMsg )._( '.' );
                    logInternal( Verbosity.INFO, "DMN", intMsg );
                }
                else
                {
                    intMsg._();
                    if (removeNTRSD)
                        intMsg._( '\'' )._( scopeDomain )._( "\' not found. Nothing removed for " );
                    else
                        intMsg._( "Empty Scope Domain given, nothing registered for " );
                    ALox.toString( scope, packageLevel, intMsg )._( '.' );

                    logInternal( Verbosity.WARNING, "DMN", intMsg );
                }
            }

        }
        finally  { release(); }
    }

    /** ********************************************************************************************
     * Implementation of the interface method fetching all possible parameters.
     *
     * @param prefix       The <em>Prefix Logable(s)</em> to set.
     * @param scope        The scope that the given \p{logable} should be registered for.
     *                     Available Scope definitions are platform/language dependent.
     * @param packageLevel Used only with
     *                     \ref com.aworx.lox.Scope.PACKAGE "Scope.PACKAGE".
     *                     Cuts the given number of package parts (separated with '.') from the end
     *                     of the packages. Optional and defaults to \c 0.
     * @param thread       The thread to set/unset a thread-related <em>Prefix Logable</em> for.
     **********************************************************************************************/
    protected void setPrefixImpl( Object  prefix, Scope scope, int packageLevel, Thread thread )
    {
        try { acquire();

            // store new prefix for this scope (and get current)
            Object previousLogable;
            scopePrefixes.InitAccess( scope, packageLevel, thread );
            if ( prefix != null )
                previousLogable= scopePrefixes.store ( prefix );
            else
                previousLogable= scopePrefixes.remove( null );


            // log info on this
            intMsg._()._( "Object ");
            Verbosity intMsgVerbosity= Verbosity.INFO;

            if ( prefix != null )
            {
                intMsg._( '\"' )._(prefix)._( '\"' )
                      ._( " set as prefix logable for "); ALox.toString(scope, packageLevel, intMsg); intMsg._( '.') ;

                if ( previousLogable  != null )
                {
                    if (     ( prefix instanceof String  && previousLogable instanceof String && prefix.equals( previousLogable ))
                         ||   prefix == previousLogable )
                    {
                        intMsg._( " (Same as before.)" );
                        intMsgVerbosity= Verbosity.VERBOSE;
                    }
                    else
                        intMsg ._( " Replacing previous \"" )._( previousLogable )._( "\"." );
                }
            }
            else
            {
                if ( previousLogable  != null )
                {
                    intMsg._( '\"' )._( previousLogable )._( '\"' )
                          ._( " removed from list of prefix lgables for " ) ; ALox.toString(scope, packageLevel, intMsg); intMsg ._( '.' );
                }
                else
                {
                    intMsg._( "<null> given but no prefix logable to remove for " );
                    ALox.toString(scope, packageLevel, intMsg); intMsg._( '.' );

                    intMsgVerbosity= Verbosity.WARNING;
                }
            }
           logInternal( intMsgVerbosity,    "PFX", intMsg );
        }
        finally  { release(); }
    }

    /** ********************************************************************************************
     * Checks if given scope is thread-related.
     *
     * @param scope     The scope that is to be checked.
     * @return \c true if \p{scope} is thread-related, \c false else.
     **********************************************************************************************/
    protected boolean isThreadRelatedScope(Scope scope)
    {
        if (scope == Scope.THREAD_INNER || scope == Scope.THREAD_OUTER) return true;

        intMsg._()._( "Illegal parameter, only Scope.THREAD_OUTER and Scope.THREAD_INNER allowed." )._( " Given: " );
        ALox.toString( scope, 0, intMsg );
        intMsg._( '.' );
        logInternal( Verbosity.ERROR, "DMN", intMsg );

        com.aworx.lib.ALIB_DBG.ERROR( "Illegal parameter, only Scope.THREAD_OUTER and Scope.THREAD_INNER allowed." );

        return false;
    }

    /** ********************************************************************************************
     * Reads the verbosity for the given logger and domain from the \b %ALib configuration system.
     * This internal method is used in two occasions:
     * - when a new logger is added: recursively for all existing domains (\p{configStr} is
     *   given)
     * - when a new domain is created on the fly(\p{configStr} is not given)
     *
     * @param logger      The logger to set the verbosity for.
     * @param dom         The domain to set the verbosity for.
     * @param variable    The (already read) variable to set verbosities from.
     **********************************************************************************************/
    protected void  getVerbosityFromConfig( Logger  logger, Domain  dom, Variable variable )
    {
        // get logger number. It may happen that the logger is not existent in this domain tree.
        int loggerNo= dom.getLoggerNo( logger ) ;
        if ( loggerNo < 0 )
            return;

        Tokenizer verbosityTknzr=   new Tokenizer();
        Substring domainStr=      new Substring();
        AString   domainStrBuf=   new AString();
        for( int varNo= 0; varNo< variable.size(); varNo++ )
        {
            verbosityTknzr.set( variable.getString( varNo ), '=' );

            domainStr.set( verbosityTknzr.next() );
            if ( domainStr.startsWith( "INTERNAL_DOMAINS", Case.IGNORE ) )
            {
                domainStrBuf._()._( domainStr.buf, domainStr.start + 16, domainStr.length() -16 );
                while ( domainStrBuf.charAtStart() == '/' )
                    domainStrBuf.deleteStart( 1 );
                domainStrBuf.insertAt( ALox.INTERNAL_DOMAINS, 0 );
                domainStr.set( domainStrBuf );
            }

            Substring verbosityStr=  verbosityTknzr.next();
            if ( verbosityStr.isEmpty() )
                continue;

            int searchMode= 0;
            if ( domainStr.consumeChar( '*' ) )    searchMode+= 2;
            if ( domainStr.consumeCharFromEnd( '*' ) )    searchMode+= 1;
            if(     ( searchMode == 0 && dom.fullPath.equals          ( domainStr,    Case.IGNORE )     )
                ||  ( searchMode == 1 && dom.fullPath.startsWith      ( domainStr,    Case.IGNORE )     )
                ||  ( searchMode == 2 && dom.fullPath.endsWith        ( domainStr,    Case.IGNORE )     )
                ||  ( searchMode == 3 && dom.fullPath.indexOf         ( domainStr, 0, Case.IGNORE ) >=0 )
                )
            {
                Verbosity verbosity= ALox.readVerbosity( verbosityStr );
                dom.setVerbosity( loggerNo, verbosity, variable.priority );

                // log info on this
                intMsg._()._NC( "Logger \"" )._NC( logger.getName() ) ._NC( "\":" ).tab(11 + maxLoggerNameLength)
                          ._( '\'' )._NC( dom.fullPath )
                          ._( '\'' ).insertChars(' ', maxDomainPathLength - dom.fullPath.length() + 1 )
                          ._( "= Verbosity." );
                          ALox.toString( verbosity, dom.getPriority( loggerNo), intMsg ).trimEnd()
                          ._('.');
                logInternal( Verbosity.INFO, "LGR", intMsg );
            }
        }
    }

    /** ********************************************************************************************
     * Reads a prefix string from the \b %ALib configuration system.
     * This internal method is used when a new domain is created,
     *
     * @param dom         The domain to set the verbosity for.
     **********************************************************************************************/
    protected void  getDomainPrefixFromConfig( Domain  dom )
    {
        Variable variable= new Variable( ALox.PREFIXES, getName());
        if( 0 == ALox.config.load(variable) )
            return;

        Tokenizer prefixTok=        new Tokenizer();
        Tokenizer prefixTokInner=   new Tokenizer();
        Substring domainStr=        new Substring();
        AString   domainStrBuf=     new AString();
        Substring prefixStr=        new Substring();
        for( int varNo= 0; varNo< variable.size(); varNo++ )
        {
            prefixTok.set( variable.getString( varNo ), '=' );

            domainStr.set( prefixTok.next() );
            if ( domainStr.startsWith( "INTERNAL_DOMAINS", Case.IGNORE ) )
            {
                domainStrBuf._()._( domainStr.buf, domainStr.start + 16, domainStr.length() -16 );
                while ( domainStrBuf.charAtStart() == '/' )
                    domainStrBuf.deleteStart( 1 );
                domainStrBuf.insertAt( ALox.INTERNAL_DOMAINS, 0 );
                domainStr.set( domainStrBuf );
            }

            prefixTokInner.set( prefixTok.next(), ',' );
            prefixStr.set( prefixTokInner.next() );
            if ( prefixStr.isEmpty() )
                continue;
            if ( prefixStr.consumeChar( '\"' ) )
                prefixStr.consumeCharFromEnd( '\"' );

            Inclusion otherPLs= Inclusion.INCLUDE;
            prefixTokInner.next();
            if ( prefixTokInner.actual.isNotEmpty() )
                otherPLs= ALIB.readInclusion( prefixTokInner.actual  );

            int searchMode= 0;
            if ( domainStr.consumeChar( '*' ) )    searchMode+= 2;
            if ( domainStr.consumeCharFromEnd( '*' ) )    searchMode+= 1;
            if(     ( searchMode == 0 && dom.fullPath.equals          ( domainStr,    Case.IGNORE )     )
                ||  ( searchMode == 1 && dom.fullPath.startsWith      ( domainStr,    Case.IGNORE )     )
                ||  ( searchMode == 2 && dom.fullPath.endsWith        ( domainStr,    Case.IGNORE )     )
                ||  ( searchMode == 3 && dom.fullPath.indexOf         ( domainStr, 0, Case.IGNORE ) >=0 )
                )
            {
                dom.prefixLogables.add( dom.new PL( new AString( prefixStr ), otherPLs ) );

                // log info on this
                intMsg._()._NC( "String \"" )._NC( prefixStr )._NC ( "\" added as prefix logable for domain \'" )
                          ._NC( dom.fullPath )
                          ._NC( "\'. (Retrieved from variable" )
                          ._NC( variable.fullname )._( ".)" );
                logInternal( Verbosity.INFO, "PFX", intMsg );
            }
        }
    }


    /** ********************************************************************************************
     * Reads the verbosity for the given logger and domain from the \b %ALib configuration system.
     * This internal method is used when a new logger is added.
     * Walks recursively for all existing domains.
     *
     * @param logger      The logger to set the verbosity for.
     * @param dom         The domain to set the verbosity for.
     * @param cfgResult   The result of the search for the variable to set verbosities from.
     **********************************************************************************************/
    protected void getAllVerbosities      ( Logger  logger,  Domain  dom,  Variable cfgResult )
    {
        // get verbosity for us
        getVerbosityFromConfig( logger, dom, cfgResult );

        // loop over all sub domains (recursion)
        for ( Domain subDomain : dom.subDomains )
            getAllVerbosities( logger, subDomain, cfgResult );
    }
}
