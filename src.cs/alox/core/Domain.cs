// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using cs.aworx.lib;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;



namespace cs.aworx.lox.core {
/** ************************************************************************************************
 * Objects of this class represent a <em>Log Domain</em> of \b %ALox. This class is internally used by
 * class \b Lox.
 **************************************************************************************************/
public class Domain
{

#if ALOX_DBG_LOG || ALOX_REL_LOG

    // #############################################################################################
    // static fields
    // #############################################################################################

    /** Domain separation character  */
    public static readonly char             Separator                                      ='/';

    /** ********************************************************************************************
     * Internal class that holds data stored per Logger
     **********************************************************************************************/
    public class LoggerData
    {
        /**  The logger  */
        public Logger           Logger;

        /**  The verbosity of the \e Logger for this domain */
        public Verbosity        LoggerVerbosity              =Verbosity.Off;

        /**  The priority value that was used to set the priority */
        public int              Priority                     = 0;

        /** the number of log calls on this domain for this logger */
        public int              LogCallsPerDomain            =0;

        /**
         * Constructor
         * @param logger The logger to add
         */
        public LoggerData( Logger logger )
        {
            this.Logger= logger;
        }
    }

    /** ********************************************************************************************
     * Internal class that holds a <em>Prefix Logable</em> and information about its exclusivity
     **********************************************************************************************/
    public class PL
    {
        public Object        Logable;         ///< The \e Logable
        public Inclusion     IncludeOtherPLs; ///< Flag if other PLs should be included as well

        /**
         * Constructor
         * @param logable         The \e Logable
         * @param includeOtherPLs Flag if other PLs should be included as well
         */
        public PL( Object logable, Inclusion includeOtherPLs )
        {
            this.Logable=           logable;
            this.IncludeOtherPLs=   includeOtherPLs;
        }
    }

    // #############################################################################################
    // Public fields
    // #############################################################################################

    /** The name of the domain. For root domains, this is null. */
    public          AString                 Name;

    /** The parent domain. For root domains, this is null. */
    public          Domain                  Parent;

    /** Data stored per logger. The index is corresponding to the list of loggers in 'our' Lox.*/
    public          List<LoggerData>        Data;

    /** The full path of the domain (set in the constructor once) . */
    public          AString                 FullPath;

    /**
      * A counter for the quantity of calls on this domain.
      * The does not include:
      * - logs when no \e Logger was set
      * - conditional logs that were suppressed
      * Otherwise, it includes all log calls, even when no \e Logger was enabled on this domain.
      */
    public          int                     CntLogCalls                                   =0;

    /** <em>Prefix Logables</em> associated with this domain. */
    public          List<PL>                PrefixLogables                         = new List<PL>();

    /** A list of sub domains. */
    public          List<Domain>            SubDomains;

    /** Flag to which is set when verbosity configuration data was read. */
    public          bool                    ConfigurationRead                                =false;

    // #############################################################################################
    // Protected fields
    // #############################################################################################

    /** A reusable AString . */
    protected       AString                 tAString                                 =new AString();

    /** A reusable substring . */
    protected       Substring               tSubstring=                             new Substring();

    /** A reusable substring . */
    protected       Substring               tSubstring2=                            new Substring();

    // #############################################################################################
    // Public interface
    // #############################################################################################

    /** ********************************************************************************************
     * Constructor for domain.
     * @param parent     The parent domain. For root domains, this is null.
     * @param name       The name of the domain. For root domains, this is null.
     **********************************************************************************************/
    public Domain( Domain parent,  AString name )
    {
        // store parameters
        this.Name=      name;
        this.Parent=    parent;

        // create fields
        SubDomains=     new List<Domain>(3);
        Data=           new List<LoggerData>( parent == null ? 2 : parent.Data.Count );

        // if we have a parent, we inherit all logger's verbosities
        if( parent != null )
            foreach( LoggerData ldParent in parent.Data )
            {
                LoggerData ld= new LoggerData( ldParent.Logger );
                ld.LoggerVerbosity= ldParent.LoggerVerbosity;
                ld.Priority=        ldParent.Priority;
                Data.Add( ld );
            }

        FullPath= new AString();
        Domain dom= this;
        do
        {
            if ( dom != this || dom.Parent == null )
                FullPath.InsertAt( "/", 0 );
            FullPath.InsertAt( dom.Name, 0 );
            dom= dom.Parent;
        }
        while( dom != null );
    }

    /** ****************************************************************************************
     * Returns the root domain of this object.
     * @return The root domain of this object
     ******************************************************************************************/
    public Domain GetRoot()
    {
        Domain rootDomain= this;
        while ( rootDomain.Parent != null )
            rootDomain= rootDomain.Parent;
        return rootDomain;
    }

    /** ****************************************************************************************
     * Adds a new entry in field #Data and recursively demands the same from its sub-domains.
     * Checks if a logger with the same name exists.
     *
     * @param logger The logger to add.
     * @return The number of the \e Logger, -1 if a logger with the same name exists already.
     ******************************************************************************************/
    public int    AddLogger( Logger logger )
    {
        // let our root do this
        if ( Parent != null )
            return Parent.AddLogger( logger );

        // check for doubles
        if ( GetLoggerNo( logger.GetName() ) >= 0 )
            return -1;

        // now this and all children
        addLoggerRecursive( logger );
        return Data.Count - 1;
    }

    /** ****************************************************************************************
     * Removes an new entry in field #Data and recursively demands the same from
     * its sub-domains.
     * @param loggerNo  The number of the \e Logger to be removed
     ******************************************************************************************/
    public void    RemoveLogger( int loggerNo )
    {
        // let our root do this
        if ( Parent != null )
        {
            Parent.RemoveLogger( loggerNo );
            return;
        }

        // now this and all children
        removeLoggerRecursive( loggerNo );
    }

    /** ****************************************************************************************
     * Returns the number of loggers stored in this domain (the same for all domains within
     * a tree).
     * @return The number of loggers attached.
     ******************************************************************************************/
    public int  CountLoggers()
    {
        return Data.Count;
    }

    /** ****************************************************************************************
     * Searches and returns the \e Logger given by name.
     * @param loggerName  The logger to search.
     * @return The \e Logger found corresponding to given name.
     *         If the \e Logger does not exist, null is returned.
     ******************************************************************************************/
    public Logger  GetLogger( String loggerName )
    {
        loggerName= loggerName.ToUpper();
        for ( int i= 0; i < Data.Count; i++  )
                if ( loggerName.Equals( Data[i].Logger.GetName() ) )
                return Data[i].Logger;
        return null;
    }

    /** ****************************************************************************************
     * Returns logger of given number.
     * @param no  The number of the \e Logger to return.
     * @return The \e Logger found with number \p{no}.
     ******************************************************************************************/
    public Logger  GetLogger( int no )
    {
        ALIB_DBG.ASSERT_ERROR( no >= 0 && no < (int) Data.Count, "Internal error: Illegal Logger Number" );
        return Data[no].Logger;
    }

    /** ****************************************************************************************
     * Returns the number of the \e Logger specified by name.
     * @param loggerName  The logger name to search.
     * @return The number of the \e Logger found corresponding to given name.
     *         If the \e Logger does not exist, -1 is returned.
     ******************************************************************************************/
    public int  GetLoggerNo( String loggerName )
    {
        loggerName= loggerName.ToUpper();
        for ( int i= 0; i < Data.Count ; i++  )
            if ( loggerName.Equals( Data[i].Logger.GetName()) )
                return i;
        return -1;
    }

    /** ****************************************************************************************
     * Returns the number of a \e Logger.
     * @param logger  The logger to search.
     * @return The number of the \e Logger. If the \e Logger does not exist, -1 is returned.
     ******************************************************************************************/
    public int  GetLoggerNo( Logger logger)
    {
        for ( int i= 0; i < Data.Count ; i++  )
            if ( logger == Data[i].Logger )
                return i;
        return -1;
    }

    /** ****************************************************************************************
     * Sets the verbosity for a logger of this domain of all its sub domains to the specified
     * value. If given priority is lower than those actually stored, nothing is set and
     * recursion is stopped.
     *
     * @param loggerNo    The number of the \e Logger to set the \e Verbosity for.
     * @param verbosity   The verbosity value to set.
     * @param priority    The priority of the setting.
     * @return The new \e Verbosity.
     ******************************************************************************************/
    public Verbosity    SetVerbosity( int loggerNo, Verbosity verbosity, int priority )
    {
        LoggerData ld= Data[loggerNo];
        if( priority >= ld.Priority )
        {
            ld.Priority=        priority;
            ld.LoggerVerbosity= verbosity;

            foreach( Domain subDomain in SubDomains )
                subDomain.SetVerbosity( loggerNo, verbosity, priority );
        }
        return ld.LoggerVerbosity;
    }

    /** ****************************************************************************************
     * Returns the <em>%Log %Domain's %Verbosity</em> for the given logger number.
     * @param loggerNo  The number of the \e Logger whose \e Verbosity is requested.
     * @return The found/defined domain \e Verbosity.
     ******************************************************************************************/
    public Verbosity    GetVerbosity( int loggerNo )
    {
        return Data[loggerNo].LoggerVerbosity;
    }

    /** ****************************************************************************************
     * Returns the priority of the \e Verbosity setting for the given logger number.
     * @param loggerNo  The number of the \e Logger whose \e Verbosity is requested.
     * @return The priority.
     ******************************************************************************************/
    public int         GetPriority( int loggerNo )
    {
        return Data[loggerNo].Priority;
    }

    /** ****************************************************************************************
     * Returns the number of log calls for this domain and logger.
     * @param loggerNo  The number of the \e Logger whose \e Verbosity is requested.
     * @return The number of calls executed by this logger on this domain.
     ******************************************************************************************/
    public int                GetCount( int loggerNo )
    {
        return Data[loggerNo].LogCallsPerDomain;
    }

    /** ********************************************************************************************
     * Determines if the domain is active in respect to the given Verbosity.
     *
     * @param loggerNo  The number of the \e Logger whose \e Verbosity is to be evaluated against
     *                  \p{level}.
     * @param statement The \e Verbosity to check.
     * @return  \c true if domain is active (log should be performed)
     **********************************************************************************************/
    public    bool IsActive( int loggerNo, Verbosity statement )
    {
        Verbosity domain= GetVerbosity( loggerNo );

        //    domain ^  / stmnt > |   Off   Error  Warning   Info  Verbose
        //  ---------------------------------------------------------------------
        //    Off                 |    -      -       -        -      -
        //    Errors              |    -      Y       -        -      -
        //    Warning             |    -      Y       Y        -      -
        //    Info                |    -      Y       Y        Y      -
        //    Verbose             |    -      Y       Y        Y      Y

        if(    statement != Verbosity.Off
            && (    ( domain == Verbosity.Error       &&        statement == Verbosity.Error   )
                 || ( domain == Verbosity.Warning     &&    (   statement == Verbosity.Warning || statement == Verbosity.Error ) )
                 || ( domain == Verbosity.Info        &&        statement != Verbosity.Verbose )
                 ||   domain == Verbosity.Verbose )
          )
        {
            Data[loggerNo].LogCallsPerDomain++;
            return true;
        }
        return false;
    }

    /** ********************************************************************************************
     * Searches a domain. If not found, the domain is (or path of domains are) created in
     * the domain tree.
     * If the path string starts with the character defined in #Separator, then
     * the search (and creation) is done starting from the root domain of this domain and not
     * from this domain.
     *
     * @param       domainPathAS  Path and domain to search.
     * @param       maxCreate     The maximum number of sub domains that are created if not
     *                            found at the end of the path.
     * @param[out]  wasCreated    Output parameter that is set \c true if domain was not found
     *                            and hence created.
     * @return The domain found or created.
     **********************************************************************************************/
    public Domain Find( AString domainPathAS, int maxCreate, ref bool wasCreated )
    {
        Substring domainPath= tSubstring;
        domainPath.Set( domainPathAS );

        // set optional output parameter as default to false
        wasCreated= false;

        int lenBeforeTrim= domainPath.Length();

        // if string is empty (resp. contains only separator characters), return ourselves
        while ( domainPath.ConsumeChar( Separator ) )
            ;
        if( domainPath.IsEmpty() )
        {
            return this;
        }

        // Trailing domain separator found: call find on root domain
        Domain startDomain= this;
        if ( lenBeforeTrim > domainPath.Length() )
        {
            while (startDomain.Parent != null )
                startDomain= startDomain.Parent;
        }

        // call find
        return startDomain.findRecursive( domainPath, maxCreate, ref wasCreated );
    }

    /** ****************************************************************************************
     * This is for debugging purposes and for configuration output.
     * E.g. this enables the \e Monodevelop IDE to display object descriptions in the debugger.
     * @returns A human readable string representation of this object.
     ******************************************************************************************/
    public override String ToString()
    {
        tAString._()._( FullPath );
        tAString._('[')._( CntLogCalls,3 )._("] ");

        // get verbosities
        tAString._(" { ");
            for( int i= 0; i < Data.Count ; i++ )
            {
                LoggerData ld= Data[i];
                tAString._(i!=0 ? ", " : "" )
                        ._('(')
                            ._('[')._(ld.LogCallsPerDomain,3)._( "], " );
                            ALox.ToString( ld.LoggerVerbosity, ld.Priority, tAString )
                        ._( ')' );
            }
        return tAString._(" }").ToString();
    }

    // #############################################################################################
    // Internals
    // #############################################################################################
        /** ****************************************************************************************
         * Internal, recursive helper of #Find.
         *
         * @param       domainPath  Path to search.
         * @param       maxCreate   The maximum number of sub domains that are created if not
         *                          found at the end of the path.
         * @param[out]  wasCreated  Output parameter that is set \c true if domain was not found
         *                          and hence created.
         * @return The domain found or created.
         ******************************************************************************************/
        protected Domain findRecursive( Substring domainPath, int maxCreate, ref bool wasCreated          )
        {
            //--- get act sub-name and rest of path
            domainPath.ConsumeChar( Separator );
            int endSubName= domainPath.IndexOf( Separator );

            ALIB_DBG.ASSERT_ERROR( endSubName != 0, "Internal Error" );

            // find end of actual domain name and save rest
            Substring restOfDomainPath= tSubstring2;
            restOfDomainPath.SetNull();
            if ( endSubName > 0 )
                domainPath.Split( endSubName, restOfDomainPath, 1 );

            // search sub-domain
            Domain subDomain= null;

            // "."
            if( domainPath.Equals( "." ) )
                subDomain= this;

            // ".."
            else if( domainPath.Equals( ".." ) )
                subDomain= Parent != null ? Parent : this;


            // search in sub-domain
            else
            {
                int i;
                bool fixedOnce= false;
                for(;;)
                {
                    for( i= 0; i< SubDomains.Count; i++ )
                    {
                        int comparison=   SubDomains[i].Name.CompareTo( domainPath, Case.Sensitive );
                        if( comparison >= 0 )
                        {
                            if ( comparison == 0 )
                                subDomain= SubDomains[i];
                            break;
                        }
                    }

                    // domain found?
                    if ( subDomain != null )
                        break;

                    // try and fix name
                    if( !fixedOnce )
                    {
                        fixedOnce= true;

                        bool illegalCharacterFound= false;
                        for( int cp= 0; cp< domainPath.Length() ; ++cp )
                        {
                            char c= domainPath.CharAt(cp);
                            if (!(    ( c >= '0' && c <= '9' )
                                   || ( c >= 'A' && c <= 'Z' )
                                   || c == '-'
                                   || c == '_'
                            ))
                            {
                                illegalCharacterFound= true;
                                domainPath.Buf[domainPath.Start + cp]= '#';
                            }
                        }

                        if ( illegalCharacterFound )
                            continue;
                     }

                    // create
                    if ( maxCreate == 0 )
                        return null;
                    wasCreated= true;
                    SubDomains.Insert( i, subDomain= new Domain( this,  new AString( domainPath ) ) );
                    maxCreate--;
                    if ( maxCreate == 0 )
                        return subDomain;

                    break;
                }

            }
            // recursion?
            if ( restOfDomainPath.IsNotEmpty() )
            {
                domainPath.Set( restOfDomainPath );
                return subDomain.findRecursive( domainPath, maxCreate, ref wasCreated );
            }

            // that's it
            return subDomain;
        }

        /** ****************************************************************************************
         * Internal, recursive helper of #AddLogger.
         * @param logger The logger to add.
         ******************************************************************************************/
        protected void   addLoggerRecursive( Logger logger)
        {
            // add data here
            Data.Add( new LoggerData( logger ) );

            // add to all children
            foreach( Domain subDomain in SubDomains )
                subDomain.addLoggerRecursive( logger );
        }

        /** ****************************************************************************************
         * Internal, recursive helper of #RemoveLogger.
         * @param loggerNo  The number of the \e Logger to be removed.
         ******************************************************************************************/
        protected void        removeLoggerRecursive( int loggerNo )
        {
            Data.RemoveAt( loggerNo );
            foreach( Domain subDomain in SubDomains )
                subDomain.removeLoggerRecursive( loggerNo );
        }
    #endif
} // Domain

} // namespace
