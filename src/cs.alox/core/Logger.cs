// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using com.aworx.util;
using com.aworx.lox.core;


namespace com.aworx.lox.core {
/** ************************************************************************************************
 * <summary>
 *  This is central class of the ALox logging implementation. It is **not** recommended to use this
 *  class directly for logging. Instead, use the simple and convenient static interface class
 *  Log or, for release logging and other more complex operations use a Lox instance.
 *  The class is abstract. To implement an own log stream, derive a new Logger class and implement the
 *  abstract method #doLog().>
 * </summary>
 **************************************************************************************************/
public abstract class Logger
{
  #if ALOX_DEBUG || ALOX_REL_LOG

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /// <summary> A temporary string used for testing domains</summary>
        protected            AString    tempDomainPath;

    // #############################################################################################
    // public fields
    // #############################################################################################

        /** <summary>
         *  The name of the logger. Can be used to receive a reference to it. Logger names are case
         *  insensitive.
         * </summary> */
        public    String          Name;

        /** <summary>
         *  The number of logs actually performed so far. In a text logger this is similar to the line
         *  number, despite the fact that a single log call can produce more than one line.
         * </summary> */
        public    uint            CntLogs;

        /// <summary> The creation time of the logger </summary>
        public    Ticks           TimeOfCreation;

        /// <summary> Timestamp of  the last log operation </summary>
        public    Ticks           TimeOfLastLog;

        /// <summary> A flag to disable the logger.</summary>
        public    bool            IsDisabled                = false;

        /**
         * <summary>
         *   The root domain "/". All registered or just used domains become a sub domain of this root.
         *   If a sub domains log level is not explicitly set, such sub domain inherits the level setting
         *   of the root domain. Therefore, the log level setting of the root domain determines how
         *   unknown domains got logged. The default level of the root domain is Log.DomainLevel.Off.
         * </summary>
         */
        public    LogDomain       RootDomain;

    // #############################################################################################
    // protected constructor
    // #############################################################################################

        /** ****************************************************************************************
         * <summary>    Constructs a logger. </summary>
         * <param name="name">    The name of the logger. </param>
         ******************************************************************************************/
        protected Logger( String name )

        {
            // save parameters
            this.Name=      name;

            // create root domain
            RootDomain=     new LogDomain( null, null );

            // create buffers
            tempDomainPath= new AString( 64 );

            // set timestamps to now
            TimeOfCreation= new Ticks();
            TimeOfLastLog=  new Ticks();
        }

    // #############################################################################################
    // Abstract methods (introduced)
    // #############################################################################################

        /** ****************************************************************************************
         * <summary>
         *  This is the central method that derived logger classes have to implement to log a message.
         *  This function is invoked by method Line(), only if this instance is not disabled and domain level
         *  and given level match. Therefore, no checks need to be performed, the only action to take is
         *  to perform the log itself.
         * </summary>
         * <param name="domain">    The log domain name. The domain is already checked on this stage and
         *                          is provided to be able to be logged out only. </param>
         * <param name="level">     The log level. This has been checked to be active already on this
         *                          stage and is provided to be able to be logged out only. </param>
         * <param name="msgObject"> The log message object (mostly a String or AString). </param>
         * <param name="indent">    The indentation in the output. </param>
         * <param name="caller">    Once compiler generated and passed forward to here. </param>
         ******************************************************************************************/
        abstract protected void doLog(  AString       domain,       Log.Level    level,
                                        Object        msgObject,    int          indent,
                                        CallerInfo    caller                             );


    // #############################################################################################
    // interface
    // #############################################################################################

        /** ****************************************************************************************
         * <summary>
         *  This method is used to create a domain for the logger. Domains control the activation of log
         *  lines. If there are more than one unknown domains on the path, all domains are created.
         * </summary>
         * <param name="domainPath">    The log domain name with path. </param>
         * <returns>The new domain. </returns>
         ******************************************************************************************/
        public LogDomain CreateDomain( AString domainPath )
        {
            // add the domain
            tempDomainPath.Clear().Append( domainPath ).ConvertCase( true );
            LogDomain domain= RootDomain.FindOrCreate( tempDomainPath, true);

            return domain;
        }

        /** ****************************************************************************************
         * <summary>    This method is used to find a domain of the logger. </summary>
         * <param name="domainPath">    The log domain name with path. </param>
         * <returns>    The new domain. </returns>
         ******************************************************************************************/
        public LogDomain FindDomain( AString domainPath )
        {
            // add the domain
            tempDomainPath.Clear().Append( domainPath ).ConvertCase( true );
            LogDomain domain= RootDomain.FindOrCreate( tempDomainPath, false );

            return domain;
        }

        /** ****************************************************************************************
         * <summary>
         *  This is the method to log a message. Internally it calls the abstract method doLog() to let
         *  derived classes perform the log. Note: this method (in fact the whole class) should not be
         *  used from outside. Instead, the static interface Log should be the right choice for most use
         *  cases.
         * </summary>
         * <param name="domain">    The log domain name. </param>
         * <param name="level">     The log level. This is checked against the level setting of the given
         *                          domain. </param>
         * <param name="msgObject"> The log message object (mostly a String or AString). </param>
         * <param name="indent">    The desired indentation in the output. </param>
         * <param name="caller">    Once compiler generated and passed forward to here. </param>
         ******************************************************************************************/
        public virtual void Line(   AString       domain,           Log.Level    level,
                                    Object        msgObject,        int          indent,
                                    CallerInfo    caller)
        {
            // do nothing if we are disabled or domain is not active
            if ( IsDisabled )
                return;

            // search domain
            tempDomainPath.Clear().Append( domain ).ConvertCase( true );
            LogDomain logDomain= RootDomain.FindOrCreate( tempDomainPath, false );

            // not found?
            if ( logDomain == null )
            {
                // add domain with default domain level
                logDomain= CreateDomain( domain );

                // inform the if default is All
                if ( logDomain.GetLevel() == Log.DomainLevel.All )
                {
                    AString    msg= new AString( 128 );
                    msg .Append( "Logger '").Append( Name )
                        .Append( "': log domain '" ).Append( domain )
                        .Append( "' not found. Created. Inherited domain level is: All ");
                    doLog( domain, Log.Level.Verbose, msg, 0, caller);
                }
            }

            // not active?
            if ( !logDomain.IsActive( level ) )
                return;

            // increase log line counter
            CntLogs++;

            // log the line
            doLog( domain, level, msgObject, indent, caller);

            // get current time    as time of last log (we do this at the end of our log operation!)
            TimeOfLastLog.Set();
        }


    #endif // ALOX_DEBUG || ALOX_REL_LOG


} // class Logger

} // namespace
