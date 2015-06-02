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
#ifndef HPP_AWORX_ALOX_LOGDOMAIN
#define HPP_AWORX_ALOX_LOGDOMAIN 1


// -------------------------------------------------------------------------------------------------
// --- includes
// -------------------------------------------------------------------------------------------------
#if !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
#endif


namespace aworx {
namespace       lox {
namespace           core{

/** ************************************************************************************************
 *  Class <c>LogDomain</c> represents a logging Domain. Each log statement refers to
 *  such a domain which can be defined specifically for different parts of your application like
 *  assemblies, libraries, namespaces, specific code files or even for a single log call.
 *  Domains can be created with path separators '/', for example 'COMM/SOCKET' could be the domain
 *  for log calls in a socket class, residing within a communication library. The advantage of
 *  creating paths and this way "sub domains", is that a whole bunch of logging domains can be
 *  altered (on/off) by just altering their root domain.
 *  Note: This class should not be used directly. Nevertheless the interface is kept public which is
 *  a general design decision for the classes of ALox libraries.
 **************************************************************************************************/
class LogDomain
{
    // #############################################################################################
    // static fields
    // #############################################################################################
    public:
        /**
         *  Contains all characters allowed for domain separation (slash, backslash and pipe symbol)
        */
        static    std::string               DomainSeparatorChars;

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:

        ///  The name of the domain. For root domains, this is null.
        util::AString32           Name;

        ///  The parent domain. For root domains, this is null.
        LogDomain*                          Parent;

        ///  A list of sub domains (recursion).
        std::vector<LogDomain*>             SubDomains;


    // #############################################################################################
    // Protected fields
    // #############################################################################################
    //
    ///  The actual user setting for the log level of the domain.
    protected:
        Log::DomainLevel        level;


    // #############################################################################################
    // Public interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  Constructor for log domains.
         * @param parent    The parent domain. For root domains, this is null.
         * @param name      The name of the domain. For root domains, this is null.
         ******************************************************************************************/
        LogDomain( LogDomain* parent,  const aworx::util::AString& name );

        /** ****************************************************************************************
         *  Destroys the log domain object.
         ******************************************************************************************/
        ~LogDomain();

        /** ****************************************************************************************
         *  Returns the domain log level. If set to Inherit, recursion with parent domain is
         *  performed.
         *
         * @return The found/defined domain log level.
         ******************************************************************************************/
        Log::DomainLevel    GetLevel();

        /** ****************************************************************************************
         *  Sets the level of the this domain and optionally for all sub domains to the specified
         *  value.
         *  The root domain's level is always set to All and can not be changed.
         *
         * @param level        The domain level value to set.
         * @param recursive    true to process recursively, false to process locally only.
         ******************************************************************************************/
        void                SetLevel( Log::DomainLevel level, bool recursive );

        /** ****************************************************************************************
         *  Determines if the domain is active in respect to the given Log.Level and the current
         *  domain level.
         *
         * @param level    The log level to check .
         * @return    True if domain is active (log should be performed)
         ******************************************************************************************/
        bool                IsActive( Log::Level level );

        /** ****************************************************************************************
         *  Searches a domain. If the flag createIfNotExistent is set, then one or more sub domains
         *  are created as needed. If the path String starts with a domain separator character, then
         *  the search (and creation) is done starting from the root domain of this domain and not
         *  from this domain.
         *
         * @param domainPath             Path and domain to search.
         * @param createIfNotExistent    If set true, domains in the path that are not found are
         *                               created.
         * @return    The domain found or created.
         ******************************************************************************************/
        LogDomain*          FindOrCreate( const  aworx::util::AString& domainPath, bool createIfNotExistent);


    // #############################################################################################
    // Internals
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         *  The internal recursive helper to implement the FindOrCreate() interface.
         *  @param domainPath             Path to search.
         *  @param dpStartIdx             The current scan position in the domain path.
         *  @param createIfNotExistent    Create domain if not found on the path.
         *  @return  The domain found.
         ******************************************************************************************/
         LogDomain* findOrCreateInternal( const aworx::util::AString&  domainPath, int dpStartIdx,
                                          bool createIfNotExistent );

}; // LogDomain

}}} // namespace aworx::lox::core

#endif // HPP_AWORX_ALOX_LOGDOMAIN
