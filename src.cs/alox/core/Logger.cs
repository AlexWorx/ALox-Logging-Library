// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using cs.aworx.lib;
using cs.aworx.lox.core;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;




/** ************************************************************************************************
 * This is the C# namespace for internal main classes and other things belonging to
 * the <em>%ALox Logging Library</em>.<p>
 * Types and interfaces found in this namespace are not designed for access by users of the
 * library. However, if extending ALox, e.g. by implementing new custom <em>loggers</em>, things
 * found here provide an important foundation.
 *
 * Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace cs.aworx.lox.core {
/** ************************************************************************************************
 * This is central class of the ALox logging implementation. It is **not** recommended to use this
 * class directly for logging. Instead, use the simple and convenient static interface class
 * Log or, for release logging and other more complex operations use a Lox instance.
 * The class is abstract. To implement an own log stream, derive a new Logger class and implement
 * the abstract method #doLog().>
 **************************************************************************************************/
public abstract class Logger
{
  #if ALOX_DBG_LOG || ALOX_REL_LOG

    // #############################################################################################
    // Internal fields
    // #############################################################################################
        /** Internal one-time allocated string.*/
        protected AString           tmpDomainName=      new AString();

    // #############################################################################################
    // public fields
    // #############################################################################################

        /**
         * The name of the logger. Can be used to receive a reference to a logger and for
         * filtering. Logger names are case insensitive.
         * If no name is specified with the constructor, the name will by the same as #TypeName.
         */
        public    String          Name;

        /**
         *  The type name of the logger. This is equal to the default Logger name.
         */
        public    String          TypeName;

        /**
         * The number of logs actually performed so far. In a text logger this is similar to the
         * line number, despite the fact that a single log call can produce more than one line.
         */
        public    uint            CntLogs;

        /// The creation time of the logger.
        public    Ticks           TimeOfCreation                                      = new Ticks();

        /// Timestamp of  the last log operation.
        public    Ticks           TimeOfLastLog                                       = new Ticks();

        /// A flag to disable the logger.
        public    bool            IsDisabled                                                = false;

        /**
         * The root domain "/". All registered or just used domains become a sub domain of this
         * root. If a sub domains log level is not explicitly set, such sub domain inherits the
         * level setting of the root domain. Therefore, the log level setting of the root
         * domain determines how unknown domains got logged. The default level of the root domain
         * is Log.DomainLevel.Off.
         */
        public    Domain          RootDomain                             = new Domain( null, null );


    // #############################################################################################
    // protected constructor
    // #############################################################################################

        /** ****************************************************************************************
         *  Constructs a logger.
         * @param name     The name of the logger. If empty, it defaults to the type name.
         * @param typeName The type of the logger.
         ******************************************************************************************/
        protected Logger( String name, String typeName )
        {
            // save parameters
            this.TypeName=  typeName;
            this.Name=      !String.IsNullOrEmpty( name ) ? name : typeName;
        }

    // #############################################################################################
    // Abstract methods (introduced)
    // #############################################################################################

        /** ****************************************************************************************
         * This is the central method that derived logger classes have to implement to log a
         * message. This function is invoked by method Line(), only if this instance is not
         * performed, the only action to take is disabled and domain level and given level match.
         * Therefore, no checks need to be to perform the log itself.
         *
         * @param domain    The log domain name. The domain is already checked on this stage and
         *                  is provided to be able to be logged out only.
         * @param level     The log level. This has been checked to be active already on this
         *                  stage and is provided to be able to be logged out only.
         * @param msgObject The log message object (mostly a String or AString).
         * @param indent    The indentation in the output. </param>
         * @param caller    Once compiler generated and passed forward to here.
         ******************************************************************************************/
        abstract protected void doLog(  AString       domain,       Log.Level    level,
                                        Object        msgObject,    int          indent,
                                        CallerInfo    caller                             );


    // #############################################################################################
    // interface
    // #############################################################################################

        /** ****************************************************************************************
         * Same as \ref SetDomain( AString, Log.DomainLevel, Propagation ) "SetDomain" but
         * takes parameter \p domain as type String. This will be converted to capital letters.
         *
         * @param domain       The log domain name as String (will be converted to capital letters).
         * @param domainLevel  The domains log level to be set.
         * @param propagation  (Optional) If \c Propagation::ToDescendants, which is the default,
         *                     the level is set for all sub-domains recursively.
         *                     If \c Propagation::None, then only this domain is changed.
         ******************************************************************************************/
        public  void SetDomain( String      domain,       Log.DomainLevel  domainLevel,
                                Propagation propagation= Propagation.ToDescendants            )
        {
            tmpDomainName._()._(domain).ToUpper();
            bool wasCreated= false;
            RootDomain.Find( tmpDomainName, ref wasCreated ).SetLevel( domainLevel, propagation );
        }

        /** ****************************************************************************************
         * Sets the domains' log level and (by default) all it's sub domains recursively.
         * In the case that sub domains should be set to a different log level, then this
         * function has to be called for such sub domains after the call to the parent domain
         * (or recursion has to be switched off, using the parameter \p propagation).
         * It is not necessary to register/create a domain before setting its log level and log
         * levels can be set and modified any time.
         * \note
         *   It is recommended to set domain levels for one or more loggers using
         *   \ref aworx::lox::Lox::SetDomain "Lox.SetDomain", which invokes this method internally.
         *   This method may be used directly in cases when certain
         *   dedicated domains (e.g.
         *   \ref aworx::lox::Lox::InternalDomain "Lox.InternalDomain" are to be manipulated for
         *   a logger, regardless in which context (Lox) it is used.
         *
         * @param domain       The log domain name as AString (has to be provided in capital letters).
         * @param domainLevel  The domains log level to be set.
         * @param propagation  (Optional) If \c Propagation::ToDescendants, which is the default,
         *                     the level is set for all sub-domains recursively.
         *                     If \c Propagation::None, then only this domain is changed.
         ******************************************************************************************/
        public  void SetDomain( AString     domain,       Log.DomainLevel  domainLevel,
                                Propagation propagation                                   )
        {
            bool dummy= false;
            RootDomain.Find( domain, ref dummy ).SetLevel( domainLevel, propagation );
        }


        /** ****************************************************************************************
         * This is the method to log a message. Internally it calls the abstract method doLog()
         * to let derived classes perform the log.
         *
         * @param domain    The log domain name as AString (has to be provided in capital letters).
         * @param level     The log level. This is checked against the level setting of the given
         *                  domain.
         * @param msgObject The log message object (mostly a String or AString).
         * @param indent    The desired indentation in the output.
         * @param caller    Once compiler generated and passed forward to here.
         * @return \c false if the domain was not found and automatically created with level
         *         \b Log.DomainLevel.Inherit.
         *         \c true otherwise.
         ******************************************************************************************/
        public virtual bool Line(   AString       domain,           Log.Level    level,
                                    Object        msgObject,        int          indent,
                                    CallerInfo    caller)
        {
            // do nothing if we are disabled or domain is not active
            if ( IsDisabled )
                return true;

            bool retVal= false;
            Domain domainObject= RootDomain.Find( domain, ref retVal );
            if ( !domainObject.IsActive( level ) )
                return !retVal;

            CntLogs++;
            doLog( domain, level, msgObject, indent, caller);
            TimeOfLastLog.Set();
            return !retVal;
        }


        /** ****************************************************************************************
         * This is for debugging purposes. E.g. this enables the \e Monodevelop IDE to display
         * object descriptions in the debugger.
         * @returns A human readable string representation of this object.
         ******************************************************************************************/
        public override String ToString()
        {
            String result= IsDisabled ? "(disabled) " : "";
            result+= Name;
            if (!Name.Equals(TypeName))
                result+= " (" + TypeName + ")";
            result+= " [" + CntLogs + "]";
            return result;
        }


    #endif // ALOX_DBG_LOG || ALOX_REL_LOG


} // class Logger

} // namespace
