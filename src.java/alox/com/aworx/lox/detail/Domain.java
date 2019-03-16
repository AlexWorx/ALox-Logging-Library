// #####################################################################oggeg############################
//  com.aworx.lox.detail - ALox Logging Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.detail;

import java.util.ArrayList;

import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Inclusion;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lox.ALox;
import com.aworx.lox.Verbosity;

/** ************************************************************************************************
 * Objects of this class represent a <em>Log Domain</em> of \b %ALox. This class is internally used by
 * class \b Lox.
 **************************************************************************************************/
public class Domain
{
    // #############################################################################################
    // static fields
    // #############################################################################################

    /** Domain separation character  */
    public final static char                   PATH_SEPARATOR                                  ='/';

    /** ********************************************************************************************
     * Internal class that holds data stored per Logger
     **********************************************************************************************/
    public class LoggerData
    {
        /**  The logger  */
        public Logger               logger;

        /**  The verbosity of the \e Logger for this domain */
        public Verbosity            loggerVerbosity         =Verbosity.OFF;

        /**  The priority value that was used to set the priority */
        public int                  priority                = 0;

        /** the number of log calls on this domain for this logger */
        public int                  logCallsPerDomain       =0;

        /**
         * Constructor
         * @param logger The logger to add
         */
        public LoggerData( Logger logger )
        {
            this.logger= logger;
        }
    }

    /** ********************************************************************************************
     * Internal class that holds a <em>Prefix Logable</em> and information about its exclusivity
     **********************************************************************************************/
    public class PL
    {
        public Object        logable;         ///< The \e Logable
        public Inclusion     includeOtherPLs; ///< Flag if other PLs should be included as well

        /**
         * Constructor
         * @param logable         The \e Logable
         * @param includeOtherPLs Flag if other PLs should be included as well
         */
        public PL( Object logable, Inclusion includeOtherPLs )
        {
            this.logable=           logable;
            this.includeOtherPLs=   includeOtherPLs;
        }
    }

    // #############################################################################################
    // Public fields
    // #############################################################################################

    /** The name of the domain. For root domains, this is null. */
    public        AString                       name;

    /** The parent domain. For root domains, this is null. */
    public        Domain                        parent;

    /** Data stored per logger. The index is corresponding to the list of loggers in 'our' Lox.*/
    public        ArrayList<LoggerData>         data;

    /** The full path of the domain (set in the constructor once) . */
    public        AString                       fullPath;

    /**
      * A counter for the quantity of calls on this domain.
      * The does not include:
      * - logs when no \e Logger was set
      * - conditional logs that were suppressed
      * Otherwise, it includes all log calls, even when no \e Logger was enabled on this domain.
      */
    public int                                  cntLogCalls                                      =0;

    /** <em>Prefix Logables</em> associated with this domain. */
    public        ArrayList<PL>                 prefixLogables                = new ArrayList<PL>();

    /** A list of sub domains. */
    public        ArrayList<Domain>             subDomains;

    /** Flag to which is set when verbosity configuration data was read. */
    public        boolean                       configurationRead                            =false;

    // #############################################################################################
    // Protected fields
    // #############################################################################################

    /** A reusable AString . */
    protected     AString                       tAString                             =new AString();

    /** A reusable substring . */
    protected     Substring                     tSubstring                         =new Substring();

    /** A reusable substring . */
    protected     Substring                     tSubstring2                        =new Substring();


    // #############################################################################################
    // Public interface
    // #############################################################################################

    /** ********************************************************************************************
     * Constructor for domain.
     *
     * @param parent    The parent domain. For root domains, this is null.
     * @param name      The name of the domain. For root domains, this is null.
     **********************************************************************************************/
    public Domain( Domain parent,  AString name )
    {
        // store parameters
        this.name=   name;
        this.parent= parent;

        // create fields
        subDomains=     new ArrayList<Domain>(3);
        data=           new ArrayList<LoggerData>( parent == null ? 2 : parent.data.size() );

        // if we have a parent, we inherit all logger's verbosities
        if( parent != null )
            for( LoggerData ldParent : parent.data )
            {
                LoggerData ld= new LoggerData( ldParent.logger );
                ld.loggerVerbosity= ldParent.loggerVerbosity;
                ld.priority=        ldParent.priority;
                data.add( ld );
            }

        fullPath= new AString();
        Domain dom= this;
        do
        {
            if ( dom != this || dom.parent == null )
                fullPath.insertAt( "/", 0 );
            fullPath.insertAt( dom.name, 0 );
            dom= dom.parent;
        }
        while( dom != null );

    }

    /** ****************************************************************************************
     * Returns the root domain of this object.
     * @return The root domain of this object
     ******************************************************************************************/
    public Domain getRoot()
    {
        Domain rootDomain= this;
        while ( rootDomain.parent != null )
            rootDomain= rootDomain.parent;
        return rootDomain;
    }

    /** ****************************************************************************************
     * Adds a new entry in field #data and recursively demands the same from its sub-domains.
     * Checks if a logger with the same name exists.
     *
     * @param logger The logger to add.
     * @return The number of the \e Logger, -1 if a logger with the same name exists already.
     ******************************************************************************************/
    public int    addLogger( Logger logger )
    {
        // let our root do this
        if ( parent != null )
            return parent.addLogger( logger );

        // check for doubles
        if ( getLoggerNo( logger.name ) >= 0 )
            return -1;

        // now this and all children
        addLoggerRecursive( logger );
        return data.size() - 1;
    }

    /** ****************************************************************************************
     * Removes an new entry in field #data and recursively demands the same from
     * its sub-domains.
     * @param loggerNo  The number of the \e Logger to be removed
     ******************************************************************************************/
    public void    removeLogger( int loggerNo )
    {
        // let our root do this
        if ( parent != null )
        {
            parent.removeLogger( loggerNo );
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
    public int  countLoggers()
    {
        return data.size();
    }

    /** ****************************************************************************************
     * Searches and returns the \e Logger given by name.
     * @param loggerName  The logger to search.
     * @return The \e Logger found corresponding to given name.
     *         If the \e Logger does not exist, null is returned.
     ******************************************************************************************/
    public Logger  getLogger( String loggerName )
    {
        for ( int i= 0; i < data.size() ; i++  )
            if ( loggerName.equalsIgnoreCase( data.get(i).logger.name ) )
                return data.get(i).logger;
        return null;
    }

    /** ****************************************************************************************
     * Returns logger of given number.
     * @param no  The number of the \e Logger to return.
     * @return The \e Logger found with number \p{no}.
     ******************************************************************************************/
    public Logger  getLogger( int no )
    {
        com.aworx.lib.ALIB_DBG.ASSERT_ERROR( no >= 0 && no < data.size(), "Internal error: Illegal Logger Number" );
        return data.get(no).logger;
    }

    /** ****************************************************************************************
     * Returns the number of the \e Logger specified by name.
     * @param loggerName  The logger name to search.
     * @return The number of the \e Logger found corresponding to given name.
     *         If the \e Logger does not exist, -1 is returned.
     ******************************************************************************************/
    public int  getLoggerNo( String loggerName )
    {
        for ( int i= 0; i < data.size() ; i++  )
            if ( loggerName.equalsIgnoreCase( data.get(i).logger.name ) )
                return i;
        return -1;
    }

    /** ****************************************************************************************
     * Returns the number of a \e Logger.
     * @param logger  The logger to search.
     * @return The number of the \e Logger. If the \e Logger does not exist, -1 is returned.
     ******************************************************************************************/
    public int  getLoggerNo( Logger logger)
    {
        for ( int i= 0; i < data.size() ; i++  )
            if ( logger == data.get(i).logger )
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
    public Verbosity    setVerbosity( int loggerNo, Verbosity verbosity, int priority )
    {
        LoggerData ld= data.get( loggerNo );
        if( priority >= ld.priority )
        {
            ld.priority=        priority;
            ld.loggerVerbosity= verbosity;
            for( Domain subDomain : subDomains )
                subDomain.setVerbosity( loggerNo, verbosity, priority );
        }
        return ld.loggerVerbosity;
    }

    /** ****************************************************************************************
     * Returns the domains \e Verbosity for the given logger number.
     * @param loggerNo  The number of the \e Logger whose \e Verbosity is requested.
     * @return The found/defined domain \e Verbosity.
     ******************************************************************************************/
    public Verbosity    getVerbosity( int loggerNo )
    {
        return data.get( loggerNo ).loggerVerbosity;
    }

    /** ****************************************************************************************
     * Returns the priority of the \e Verbosity setting for the given logger number.
     * @param loggerNo  The number of the \e Logger whose \e Verbosity is requested.
     * @return The priority.
     ******************************************************************************************/
    public int          getPriority( int loggerNo )
    {
        return data.get( loggerNo ).priority;
    }

    /** ****************************************************************************************
     * Returns the number of log calls for this domain and logger.
     * @param loggerNo  The number of the \e Logger whose \e Verbosity is requested.
     * @return The number of calls executed by this logger on this domain.
     ******************************************************************************************/
    public int          getCount( int loggerNo )
    {
        return data.get( loggerNo ).logCallsPerDomain;
    }

    /** ********************************************************************************************
     * Determines if the domain is active in respect to the given Verbosity.
     *
     * @param loggerNo  The number of the \e Logger whose \e Verbosity is to be evaluated against
     *                  \p{statement}.
     * @param statement The \e Verbosity to check.
     * @return  \c true if domain is active (log should be performed)
     **********************************************************************************************/
    public boolean      isActive( int loggerNo, Verbosity statement )
    {
        Verbosity domain= getVerbosity( loggerNo );

        //    domain ^  / stmnt > |   Off   Error  Warning   Info  Verbose
        //  ---------------------------------------------------------------------
        //    Off                 |    -      -       -        -      -
        //    Errors              |    -      Y       -        -      -
        //    Warning             |    -      Y       Y        -      -
        //    Info                |    -      Y       Y        Y      -
        //    Verbose             |    -      Y       Y        Y      Y

        if(    statement != Verbosity.OFF
            && (    ( domain == Verbosity.ERROR       &&        statement == Verbosity.ERROR   )
                 || ( domain == Verbosity.WARNING     &&    (   statement == Verbosity.WARNING || statement == Verbosity.ERROR ) )
                 || ( domain == Verbosity.INFO        &&        statement != Verbosity.VERBOSE )
                 ||   domain == Verbosity.VERBOSE )
          )
        {
            data.get( loggerNo ).logCallsPerDomain++;
            return true;
        }
        return false;
    }

    /** ********************************************************************************************
     * Searches a domain. If not found, the domain is (or path of domains are) created in
     * the domain tree.
     * If the path string starts with the character defined in #PATH_SEPARATOR, then
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
    public Domain find( AString domainPathAS, int maxCreate, boolean[] wasCreated )
    {
        Substring domainPath= tSubstring;
        domainPath.set( domainPathAS );

        // set optional output parameter as default to false
        wasCreated[0]= false;

        int lenBeforeTrim= domainPath.length();

        // if string is empty (resp. contains only separator characters), return ourselves
        while( domainPath.consumeChar( PATH_SEPARATOR ) )
        { /* eat separators */ }

        if( domainPath.isEmpty() )
            return this;

        // Trailing domain separator found: call find on root domain
        Domain startDomain= this;
        if ( lenBeforeTrim > domainPath.length() )
        {
            while (startDomain.parent != null )
                startDomain= startDomain.parent;
        }

        // call find
        return startDomain.findRecursive( domainPath, maxCreate, wasCreated );
    }

    /** ****************************************************************************************
     * This is for debugging purposes and for configuration output.
     * E.g. this enables the \e Eclipse IDE to display object descriptions in the debugger.
     * @returns A human readable string representation of this object.
     ******************************************************************************************/
    @Override
    public String toString()
    {
        tAString._()._( fullPath );
        tAString._('[')._( cntLogCalls,3 )._("] ");

        // get verbosities
        tAString._(" { ");
            for( int i= 0; i < data.size() ; i++ )
            {
                LoggerData ld= data.get( i );
                tAString._(i!=0 ? ", " : "" )
                        ._('(')
                            ._('[')._(ld.logCallsPerDomain,3)._( "], " );
                            ALox.toString( ld.loggerVerbosity, ld.priority, tAString )
                        ._(')');
            }
        return tAString._(" }").toString();
    }

    // #############################################################################################
    // Internals
    // #############################################################################################

        /** ****************************************************************************************
         * The internal recursive helper of #find.
         *
         * @param       domainPath  Path to search.
         * @param       maxCreate   The maximum number of sub domains that are created if not
         *                          found at the end of the path.
         * @param[out]  wasCreated    Output parameter that is set \c true if domain was not found
         *                            and hence created.
         * @return The domain found or created.
         ******************************************************************************************/
        @SuppressWarnings ("null")
        protected Domain findRecursive( Substring domainPath, int maxCreate, boolean[] wasCreated )
        {
            //--- get act sub-name and rest of path
            domainPath.consumeChar( PATH_SEPARATOR );
            int endSubName= domainPath.indexOf( PATH_SEPARATOR );

            com.aworx.lib.ALIB_DBG.ASSERT_ERROR( endSubName != 0, "Internal Error" );

            // find end of actual domain name and save rest
            Substring restOfDomainPath= tSubstring2;
            restOfDomainPath.setNull();
            if ( endSubName > 0 )
                domainPath.split( endSubName, restOfDomainPath, 1 );

            // search sub-domain
            Domain subDomain= null;

            // "."
            if( domainPath.equals( "." ) )
                subDomain= this;

            // ".."
            else if( domainPath.equals( ".." ) )
                subDomain= parent != null ? parent : this;


            // search in sub-domain
            else
            {
                int i;
                boolean fixedOnce= false;
                for(;;)
                {
                    for( i= 0; i< subDomains.size(); i++ )
                    {
                        int comparison=   subDomains.get(i).name.compareTo( domainPath, Case.SENSITIVE );
                        if( comparison >= 0 )
                        {
                            if ( comparison == 0 )
                                subDomain= subDomains.get(i);
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

                        boolean illegalCharacterFound= false;
                        for( int cp= 0; cp< domainPath.length() ; ++cp )
                        {
                            char c= domainPath.charAt(cp);
                            if (!(    ( c >= '0' && c <= '9' )
                                   || ( c >= 'A' && c <= 'Z' )
                                   || c == '-'
                                   || c == '_'
                            ))
                            {
                                illegalCharacterFound= true;
                                domainPath.buf[domainPath.start + cp]= '#';
                            }
                        }

                        if ( illegalCharacterFound )
                            continue;
                     }

                    // create
                    if ( maxCreate == 0 )
                        return null;
                    wasCreated[0]= true;
                    subDomains.add( i, subDomain= new Domain( this,  new AString( domainPath ) ) );
                    maxCreate--;
                    if ( maxCreate == 0 )
                        return subDomain;
                    break;
                }
            }

            // recursion?
            if ( restOfDomainPath.isNotEmpty() )
            {
                domainPath.set( restOfDomainPath );
                return subDomain.findRecursive( domainPath, maxCreate, wasCreated );
            }

            // that's it
            return subDomain;
        }

        /** ****************************************************************************************
         * Internal, recursive helper of #addLogger.
         * @param logger The logger to add.
         ******************************************************************************************/
        protected void   addLoggerRecursive( Logger logger)
        {
            data.add( new LoggerData( logger ) );
            for( Domain subDomain : subDomains )
                subDomain.addLoggerRecursive( logger );
        }

        /** ****************************************************************************************
         * Internal, recursive helper of #removeLogger.
         * @param loggerNo  The number of the \e Logger to be removed.
         ******************************************************************************************/
        protected void        removeLoggerRecursive( int loggerNo )
        {
            data.remove( loggerNo );
            for( Domain subDomain : subDomains )
                subDomain.removeLoggerRecursive( loggerNo );
        }

} // class Domain
