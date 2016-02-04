// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

/** ************************************************************************************************
 *  This is the Java namespace for internal main classes and other things belonging to
 *  the <em>%ALox Logging Library</em>.<p>
 *  Types and interfaces found in this namespace are not designed for access by users of the
 *  library. However, if extending ALox, e.g. by implementing new custom <em>loggers</em>, things
 *  found here provide an important foundation.<p>
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
package com.aworx.lox.core;

import com.aworx.lib.enums.Propagation;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lib.time.Ticks;
import com.aworx.lox.Log;

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

        /** Internal one-time allocated string.*/
        protected AString           tmpDomainName=      new AString();

        /** Internal one-time allocated boolean[] used as output parameter.*/
        protected boolean[]         outputParam=        new boolean[1];


     // #############################################################################################
    // public fields
    // #############################################################################################

        /**
         * The name of the logger. Can be used to receive a reference to a logger and for filtering.
         * Logger names are case insensitive.
         * If no name is specified with the constructor, the name will by the same as #typeName.
         */
        public    String            name;

        /**
         *  The type name of the logger. This is equal to the default Logger name.
         */
        public    String            typeName;


        /** The number of logs actually performed so far. In a text logger this is similar to the line
         *    number, despite the fact that a single log call can produce more than one line. */
        public    int               cntLogs;

        /** The creation time of the logger */
        public    Ticks             timeOfCreation                                    = new Ticks();

        /** Timestamp of  the last log operation */
        public    Ticks             timeOfLastLog                                     = new Ticks();

        /** A flag to disable the logger.*/
        public    boolean           isDisabled                                        = false;

        /**
         *   The root domain "/". All registered or just used domains become a sub domain of this root.
         *   If a sub domains log level is not explicitly set, such sub domain inherits the level setting
         *   of the root domain. Therefore, the log level setting of the root domain determines how
         *   unknown domains got logged. The default level of the root domain is Log.DomainLevel.OFF.
         */
        public    Domain         rootDomain                        = new Domain( null, null );

    // #############################################################################################
    // protected constructor
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs a logger.
         *
         * @param name     The name of the logger. If empty, it defaults to the type name.
         * @param typeName The type of the logger.
         ******************************************************************************************/
        protected Logger( String name, String typeName )

        {
            this.name=      !CString.isNullOrEmpty( name ) ? name : typeName;
            this.typeName=  typeName;
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
         * Same as \ref setDomain( AString, Log.DomainLevel, Propagation ) "setDomain" but
         * takes parameter \p domain as type String. This will be converted to capital letters.
         *
         * @param domain       The log domain name as String (will be converted to capital letters).
         * @param domainLevel  The domains log level to be set.
         * @param propagation  (Optional) If \c Propagation::ToDescendants, which is the default,
         *                     the level is set for all sub-domains recursively.
         *                     If \c Propagation::None, then only this domain is changed.
         ******************************************************************************************/
        public  void setDomain( String      domain,       Log.DomainLevel  domainLevel,
                                Propagation propagation                                   )
        {
            tmpDomainName._()._(domain).toUpper();
            rootDomain.find( tmpDomainName, null ).setLevel( domainLevel, propagation );
        }

        /** ****************************************************************************************
         * Sets the domains' log level and (by default) all it's sub domains recursively. In the case
         * that sub domains should be set to a different log level, then this function has to be
         * called for such sub domains after the call to the parent domain (or recursion has to be
         * switched off, using the parameter \p propagation). It is not necessary to register/create
         * a domain before setting its log level and log levels can be set and modified any time.
         * \note
         *   It is recommended to set domain levels for one or more loggers using
         *   \ref aworx::lox::Lox::setDomain "Lox.setDomain", which invokes this method internally.
         *   This method may be used directly in cases when certain
         *   dedicated domains (e.g.
         *   \ref aworx::lox::Lox::internalDomain "Lox.internalDomain" are to be manipulated for
         *   a logger, regardless in which context (Lox) it is used.
         *
         * @param domain       The log domain name as AString (has to be provided in capital letters).
         * @param domainLevel  The domains log level to be set.
         * @param propagation  (Optional) If \c Propagation::ToDescendants, which is the default,
         *                     the level is set for all sub-domains recursively.
         *                     If \c Propagation::None, then only this domain is changed.
         ******************************************************************************************/
        public  void setDomain( AString     domain,       Log.DomainLevel  domainLevel,
                                Propagation propagation                                   )
        {
            rootDomain.find( domain, null ).setLevel( domainLevel, propagation );
        }

        /** ****************************************************************************************
         * Overloaded method that provides default paramter \p propagation with value
         * \b Propagation.TO_DESCENDANTS.
         *
         * @param domain       The log domain name as String (will be converted to capital letters).
         * @param domainLevel  The domains log level to be set.
         ******************************************************************************************/
        public  void setDomain( String  domain,       Log.DomainLevel  domainLevel )
        {
            setDomain( domain, domainLevel, Propagation.TO_DESCENDANTS );
        }

        /** ****************************************************************************************
         * This is the method to log a message. Internally it calls the abstract method doLog() to let
         * derived classes perform the log.
         *
         * @param domain    The log domain name (has to be provided in capital letters).
         * @param level     The log level. This is checked against the level setting of the given domain.
         * @param msgObject The log message object (mostly a String or AString).
         * @param indent    The desired indentation in the output.
         * @param caller    Information on the caller.
         * @return \c false if the domain was not found and automatically created with level
         *         \b Log.DomainLevel.INHERIT.
         *         \c true otherwise.
         ******************************************************************************************/
        public boolean line( AString      domain,        Log.Level    level,
                             Object       msgObject,     int          indent,
                             CallerInfo   caller                                 )
        {
            // do nothing if we are disabled
            if ( isDisabled )
                return true;

            Domain domainObject= rootDomain.find( domain, outputParam );
            if ( !domainObject.isActive( level ) )
                return !outputParam[0];

            cntLogs++;
            doLog( domain, level, msgObject, indent, caller);
            timeOfLastLog.set();
            return !outputParam[0];
        }

        /** ****************************************************************************************
         * This is for debugging purposes. E.g. this enables the \e Eclipse IDE to display
         * object descriptions in the debugger.
         * @returns A human readable string representation of this object.
         ******************************************************************************************/
        @Override
        public String toString()
        {
            String result= isDisabled ? "(disabled) " : "";
            result+= name;
            if (!name.equals(typeName))
                result+= " (" + typeName + ")";
            result+= " [" + cntLogs + "]";
            return result;
        }

} // class Logger
