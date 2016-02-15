// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include ALox main header first...
#if !defined (HPP_ALOX)
    #include "alox/alox.hpp"
#endif

// then, set include guard
#ifndef HPP_ALOX_CORE_LOGGER
#define HPP_ALOX_CORE_LOGGER 1


// #################################################################################################
// includes
// #################################################################################################

#if !defined (HPP_ALOX_CORE_CALLERINFO)
    #include "callerinfo.hpp"
#endif

#if !defined (HPP_ALOX_CORE_DOMAIN)
    #include "domain.hpp"
#endif


#if !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
#endif


namespace aworx {
namespace       lox {
/** ************************************************************************************************
 *  This is the C++ namespace for internal main classes and other things belonging to
 *  the <em>%ALox Logging Library</em>.<p>
 *  Types and interfaces found in this namespace are not designed for access by users of the
 *  library. However, if extending ALox, e.g. by implementing new custom <em>loggers</em>, things
 *  found here provide an important foundation.
 *
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace           core{


/** ************************************************************************************************
 *  This is central class of the ALox logging implementation. It is **not** recommended to use this
 *  class directly for logging. Instead, use the simple and convenient static interface class
 *  Log or, for release logging and other more complex operations use a Lox instance.
 *  The class is abstract. To implement an own log stream, derive a new Logger class and implement the
 *  abstract method #doLog().
 **************************************************************************************************/
class Logger
{
    /**
     *  An utility value. Has to be first in the class. Will be initialized prior to any other
     *  field. For more info see # Log::InitALox()
     */
    private:    bool _apiInitializer;

    // #############################################################################################
    // public fields
    // #############################################################################################
    public:
        /**
         * The name of the logger. Can be used to receive a reference to a logger and for filtering.
         * Logger names are case insensitive.
         * If no name is specified with the constructor, the name will by the same as #TypeName.
         */
        String32                    Name;

        /**
         *  The type name of the logger. This is equal to the default Logger name.
         */
        String32                    TypeName;

        /**
         * The number of logs actually performed so far. In a text logger this is similar to the line
         * number, despite the fact that a single log call can produce more than one line.
         */
        unsigned int                CntLogs                                               =0;

        ///  The creation time of the logger
        lib::time::Ticks            TimeOfCreation;

        ///  Timestamp of  the last log operation
        lib::time::Ticks            TimeOfLastLog;

        ///  A flag to disable the logger.
        bool                        IsDisabled                                            =false;

        /**
         *   The root domain "/". All registered or just used domains become a sub domain of this root.
         *   If a sub domains log level is not explicitly set, such sub domain inherits the level setting
         *   of the root domain. Therefore, the log level setting of the root domain determines how
         *   unknown domains got logged. The default level of the root domain is Log.DomainLevel.Off.
         */
        Domain                      RootDomain;

    // #############################################################################################
    // Internal fields
    // #############################################################################################


    // #############################################################################################
    // Constructor/Destructor
    // #############################################################################################
    protected:

        /** ****************************************************************************************
         * Constructs a logger. This constructor is protected because this class is abstract.
         *
         * Note: This constructor is implemented in the header and annotated as inline.
         * This way, the Log::InitALox call receives the size of classes from the compilation unit
         * that invokes the constructor. If different compile options are set, we have a chance to
         * detect them here.
         * @param name     The name of the logger. If empty, it defaults to the type name.
         * @param typeName The type of the logger.
         ******************************************************************************************/
        inline
        Logger( const String& name, const String& typeName )
                                     : _apiInitializer( Log::Init() )
                                     , Name(name)
                                     , TypeName(typeName)
                                     , TimeOfCreation ()
                                     , TimeOfLastLog  ()
                                     , RootDomain     ( nullptr, nullptr )
        {
            if ( Name.IsEmpty() )
                Name << TypeName;
        }


        /** ****************************************************************************************
         *  Destructs a logger
         ******************************************************************************************/
    public:
        ALOX_API virtual  ~Logger();

    // #############################################################################################
    // Abstract methods to be overwritten
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  This is the central method that derived logger classes have to implement to log a message.
         *  This function is invoked by method Line(), only if this instance is not disabled and domain level
         *  and given level match. Therefore, no checks need to be performed, the only action to take is
         *  to perform the log itself.
         *
         * @param domain    The log domain name. The domain is already checked on this stage and
         *                  is provided to be able to be logged out only.
         * @param level     The log level. This has been checked to be active already on this
         *                  stage and is provided to be able to be logged out only.
         * @param msgObject The object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    The indentation in the output.
         * @param caller    Once compiler generated and passed forward to here.
         ******************************************************************************************/
        virtual void    doLog(  const TString&  domain,     Log::Level      level,
                                const void*     msgObject,  int             msgType,
                                int             indent,
                                CallerInfo*     caller       )                    =0;


    // #############################################################################################
    // interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Sets the domains' log level and (by default) all it's sub domains recursively. In the case
         * that sub domains should be set to a different log level, then this function has to be
         * called for such sub domains after the call to the parent domain (or recursion has to be
         * switched off, using the parameter \p propagation). It is not necessary to register/create
         * a domain before setting its log level and log levels can be set and modified any time.
         * \note
         *   It is recommended to set domain levels for one or more loggers using
         *   \ref aworx::lox::Lox::SetDomain "Lox::SetDomain", which invokes this method internally.
         *   This method may be used directly in cases when certain
         *   dedicated domains (e.g.
         *   \ref aworx::lox::Lox::InternalDomain "Lox::InternalDomain" are to be manipulated for
         *   a logger, regardless in which context (Lox) it is used.
         *
         * @param domain       The log domain.
         * @param domainLevel  The domains log level to be set.
         * @param propagation  (Optional) If \c Propagation::ToDescendants, which is the default,
         *                     the level is set for all sub-domains recursively.
         *                     If \c Propagation::None, then only this domain is changed.
         ******************************************************************************************/
        void        SetDomain( const TString&           domain,
                               Log::DomainLevel         domainLevel,
                               lib::enums::Propagation  propagation=    lib::enums::Propagation::ToDescendants )
        {
            RootDomain.Find( String128()._( domain ).ToUpper() )->SetLevel( domainLevel, propagation );
        }


        /** ****************************************************************************************
         * This is the method to log a message. Internally it calls the abstract method doLog() to
         * let derived classes perform the log.
         *
         * @param domain    The log domain name (has to be provided in capital letters).
         * @param level     The log level. This is checked against the level setting of the given
         *                  domain.
         * @param msgObject The object to log.
         * @param msgType   Type information on the object to log.
         * @param indent    The desired indentation in the output.
         * @param caller    Once compiler generated and passed forward to here.
         * @return \c false if the domain was not found and automatically created with level
         *         \b Log::DomainLevel::Inherit.
         *         \c true otherwise.
         ******************************************************************************************/
        ALOX_API
        virtual bool   Line( const AString&  domain,        Log::Level      level,
                             const void*     msgObject,     int             msgType,
                             int             indent,        CallerInfo*     caller    );
}; // class Logger

}}} // namespace



#endif // HPP_ALOX_CORE_LOGGER
