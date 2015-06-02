// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core;

import com.aworx.lox.Log;
import com.aworx.util.AString;
import com.aworx.util.Ticks;

/** ************************************************************************************************
 * This is central class of the ALox logging implementation. It is **not** recommended to use
 * this class directly for logging. Instead, use the simple and convenient static interface
 * class Log or, for release logging and other more complex operations use a Lox instance. The
 * class is abstract. To implement an own log stream, derive a new Logger class and implement
 * the abstract method #doLog().
 **************************************************************************************************/
public abstract class Logger
{

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /**  A temporary string used for testing domains */
        protected AString           tempDomainPath;

     // #############################################################################################
    // public fields
    // #############################################################################################

        /** The name of the logger. Can be used to receive a reference to it. Logger names are case
         *  insensitive. */
        public    String            name;

        /** The number of logs actually performed so far. In a text logger this is similar to the line
         *    number, despite the fact that a single log call can produce more than one line. */
        public    int               cntLogs;

        /** The creation time of the logger */
        public    Ticks             timeOfCreation;

        /** Timestamp of  the last log operation */
        public    Ticks             timeOfLastLog;

        /** A flag to disable the logger.*/
        public    boolean           isDisabled                = false;

        /**
         *   The root domain "/". All registered or just used domains become a sub domain of this root.
         *   If a sub domains log level is not explicitly set, such sub domain inherits the level setting
         *   of the root domain. Therefore, the log level setting of the root domain determines how
         *   unknown domains got logged. The default level of the root domain is Log.DomainLevel.OFF.
         */
        public    LogDomain         rootDomain;


    // #############################################################################################
    // protected constructor
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs a logger.
         *
         * @param name  The name of the logger.
         ******************************************************************************************/
        protected Logger( String name )

        {
            this.name=        name;
            rootDomain=       new LogDomain( null, null );
            tempDomainPath=   new AString( 64 );
            timeOfCreation=   new Ticks();
            timeOfLastLog=    new Ticks();
        }

    // #############################################################################################
    // Abstract methods (introduced)
    // #############################################################################################

        /** ****************************************************************************************
         * This is the central method that derived logger classes have to implement to log a message.
         *
         * @param domain    The log domain name. The domain is already checked on this stage and is
         *                  provided to be able to be logged out only.
         * @param level     The log level. This has been checked to be active already on this stage and
         *                  is provided to be able to be logged out only.
         * @param msgObject The log message object (mostly a String or AString).
         * @param indent    The indentation in the output.
         * @param caller    Once compiler generated and passed forward to here.
         ******************************************************************************************/
        abstract protected void doLog(  AString     domain,       Log.Level    level,
                                        Object      msgObject,    int          indent,
                                        CallerInfo  caller                                );


    // #############################################################################################
    // interface
    // #############################################################################################

        /** ****************************************************************************************
         * This method is used to create a domain for the logger. Domains control the activation of log
         * lines. If there are more than one unknown domains on the path, all domains are created.
         *
         * @param domainPath    The log domain name with path.
         *
         * @return  The new domain.
         ******************************************************************************************/
        public LogDomain createDomain( AString domainPath )
        {
            // add the domain
            tempDomainPath.clear().append( domainPath ).convertCase( true );
            LogDomain domain= rootDomain.findOrCreate( tempDomainPath, true);

            return domain;
        }

        /** ****************************************************************************************
         * This method is used to find a domain of the logger.
         *
         * @param domainPath    The log domain name with path.
         *
         * @return  The new domain.
         ******************************************************************************************/
        public LogDomain findDomain( AString domainPath )
        {
            // add the domain
            tempDomainPath.clear().append( domainPath ).convertCase( true );
            LogDomain domain= rootDomain.findOrCreate( tempDomainPath, false );

            return domain;
        }

        /** ****************************************************************************************
         * This is the method to log a message. Internally it calls the abstract method doLog() to let
         * derived classes perform the log. Note: this method (in fact the whole class) should not be
         * used from outside. Instead, the static interface Log should be the right choice for most use
         * cases.
         *
         * @param domain    The log domain name. If not starting with a slash ('/')
         *                  is is appended to any default domain name that might have been specified for
         *                  the source file.
         * @param level     The log level. This is checked against the level setting of the given domain.
         * @param msgObject The log message object (mostly a String or AString).
         * @param indent    The desired indentation in the output.
         * @param caller    Once compiler generated and passed forward to here.
         ******************************************************************************************/
        public void line(   AString       domain,           Log.Level    level,
                            Object        msgObject,        int          indent,
                            CallerInfo    caller                                    )
        {
            // do nothing if we are disabled
            if ( isDisabled )
                return;

            // search domain
            tempDomainPath.clear().append( domain ).convertCase( true );
            LogDomain logDomain= rootDomain.findOrCreate( tempDomainPath, false );

            // not found?
            if ( logDomain == null )
            {
                // add domain with default domain level
                logDomain= createDomain( domain );

                // inform the if default is All
                if ( logDomain.getLevel() == Log.DomainLevel.ALL )
                {
                    AString    msg= new AString( 128 );
                    msg.append( "Logger '").append( name )
                       .append( "': log domain '" ).append( domain )
                       .append( "' not found. Created. Inherited domain level is: All ");
                    doLog( domain, Log.Level.VERBOSE, msg, 0, caller);
                }
            }

            // check if active
            if ( !logDomain.isActive( level ) )
                return;

            // increase log line counter
            cntLogs++;

            // log the line
            doLog( domain, level, msgObject, indent, caller);

            // get current time
            timeOfLastLog.set();
        }

} // class Logger