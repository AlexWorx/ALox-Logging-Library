// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

// include ALox main header first...
#if !defined (HPP_AWORX_ALOX_ALOX)
    #include "alox.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_ALOX_LOGGER
#define HPP_AWORX_ALOX_LOGGER 1


// -------------------------------------------------------------------------------------------------
// --- includes
// -------------------------------------------------------------------------------------------------

#if !defined (HPP_AWORX_ALOX_CALLERINFO)
    #include "callerinfo.hpp"
#endif

#if !defined (HPP_AWORX_ALOX_LOGDOMAIN)
    #include "logdomain.hpp"
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
 *  found here provide an important the foundation.<p>
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace           core{


/** ************************************************************************************************
 *
 *  This is central class of the ALox logging implementation. It is **not** recommended to use this
 *  class directly for logging. Instead, use the simple and convenient static interface class
 *  Log or, for release logging and other more complex operations use a Lox instance.
 *  The class is abstract. To implement an own log stream, derive a new Logger class and implement the
 *  abstract method #doLog().>
 *
 **************************************************************************************************/
class Logger
{
    /**
     *  A utility value. Has to be first in the class. Will be initialized prior to any other
     *  field. Initializer uses insensitive. For more info see # Log::InitALox()
     */
    private:    bool _apiInitializer;

    // #############################################################################################
    // public fields
    // #############################################################################################
    public:
        /**
         *  The name of the logger. Can be used to receive a reference to it. Logger names are case
         *  insensitive.
         *  */
        aworx::util::AString32       Name;

        /**
         * The number of logs actually performed so far. In a text logger this is similar to the line
         * number, despite the fact that a single log call can produce more than one line.
         */
        unsigned int                 CntLogs                                               =0;

        ///  The creation time of the logger
        aworx::util::Ticks           TimeOfCreation;

        ///  Timestamp of  the last log operation
        aworx::util::Ticks           TimeOfLastLog;

        ///  A flag to disable the logger.
        bool                         IsDisabled                                            =false;

        /**
         *
         *   The root domain "/". All registered or just used domains become a sub domain of this root.
         *   If a sub domains log level is not explicitly set, such sub domain inherits the level setting
         *   of the root domain. Therefore, the log level setting of the root domain determines how
         *   unknown domains got logged. The default level of the root domain is Log.DomainLevel.Off.
         *
         */
        LogDomain                    RootDomain;


    // #############################################################################################
    // Internal fields
    // #############################################################################################


    // #############################################################################################
    // Constructor/Destructor
    // #############################################################################################
    protected:

        /** ****************************************************************************************
         * Constructs a logger. This constructor is protected because this class is abstract.
         * Note: This constructor has to stay in the header. This way, the Log::InitALox call
         * receives the size of classes from the compilation unit that invokes the constructor.
         * If different compile options are set, we have a chance to detect them here.
         * @param name    The name of the logger.
         ******************************************************************************************/
        Logger( const char* name ) : _apiInitializer( Log::InitALox(ALOX_COMPILED_CLASS_SIZE_VERIFYER) )
                                   , TimeOfCreation (0)
                                   , TimeOfLastLog  (0)
                                   , RootDomain     ( nullptr, aworx::util::AString() )
        {
            Name=  name;

            TimeOfCreation.Set();
            TimeOfLastLog.Set();
        }


        /** ****************************************************************************************
         *     Destructs a logger
         ******************************************************************************************/
        ALOX_API virtual  ~Logger();

    // #############################################################################################
    // Abstract methods to be overwritten
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *
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
         * @param typeInfo  Type information on the object to log.
         * @param indent    The indentation in the output.
         * @param caller    Once compiler generated and passed forward to here.
         ******************************************************************************************/
        virtual void    doLog(  const util::AString&  domain,     Log::Level      level,
                                const void*           msgObject,  int             typeInfo,
                                int                   indent,     CallerInfo*     caller         )    = 0;


    // #############################################################################################
    // interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  This method is used to create a domain for the logger. Domains control the activation of log
         *  lines. If there are more than one unknown domains on the path, all domains are created.
         * @param domainPath    The log domain name with path.
         * @return The new domain.
         ******************************************************************************************/
        ALOX_API
        LogDomain*      CreateDomain( const util::AString& domainPath );

        /** ****************************************************************************************
         *  This method is used to find a domain of the logger.
         *  @param domainPath    The log domain name with path.
         *  @return  The new domain.
         ******************************************************************************************/
        ALOX_API
        LogDomain*      FindDomain( const util::AString& domainPath );

        /** ****************************************************************************************
         *  This is the method to log a message. Internally it calls the abstract method doLog() to let
         *  derived classes perform the log. Note: this method (in fact the whole class) should not be
         *  used from outside. Instead, the static interface Log should be the right choice for most use
         *  cases.
         *
         * @param domain    The log domain name.
         * @param level     The log level. This is checked against the level setting of the given
         *                  domain.
         * @param msgObject The object to log.
         * @param typeInfo  Type information on the object to log.
         * @param indent    The desired indentation in the output.
         * @param caller    Once compiler generated and passed forward to here.
         ******************************************************************************************/
        ALOX_API
        virtual void    Line(   const util::AString& domain,        Log::Level      level,
                                const void*          msgObject,     int             typeInfo,
                                int                  indent,        CallerInfo*     caller    );
}; // class Logger

}}} // namespace


#endif // HPP_AWORX_ALOX_LOGGER
