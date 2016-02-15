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
#ifndef HPP_ALOX_CORE_DOMAIN
#define HPP_ALOX_CORE_DOMAIN 1


// #################################################################################################
// includes
// #################################################################################################
#if !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
#endif


namespace aworx {
namespace       lox {
namespace           core{

/** ************************************************************************************************
 * Objects of this class represent a logging Domain. Each log statement refers to
 * such a domain which can be defined specifically for different parts of your application like
 * assemblies, libraries, namespaces, specific code files or even for a single log call.
 * Domains can be created with path separators '/', for example 'COMM/SOCKET' could be the domain
 * for log calls in a socket class, residing within a communication library. The advantage of
 * creating paths and this way trees of domains, is that a whole bunch of logging domains can
 * be altered (in respect of logging verbosity) by just changing their root domain.
 * \note This class should not be used directly. Nevertheless the interface is kept public which is
 *       a general design decision for the classes of ALox libraries.
 **************************************************************************************************/
class Domain
{
    // #############################################################################################
    // static fields
    // #############################################################################################
    public:
        /**
         *  Contains all characters allowed for domain separation (slash, backslash and pipe symbol)
        */
        static    TString                   DomainSeparatorChars;

    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:

        ///  The name of the domain. For root domains, this is null.
        String32                            Name;

        ///  The parent domain. For root domains, this is null.
        Domain*                             Parent;

        ///  A list of sub domains (recursion).
        std::vector<Domain*>                SubDomains;


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
         * Constructor for log domains.
         * @param parent    The parent domain. For root domains, this is null.
         * @param name      The name of the domain. For root domains, this is null.
         ******************************************************************************************/
        ALOX_API
        Domain( Domain* parent,  const String& name );

        /** ****************************************************************************************
         * Destroys the log domain object.
         ******************************************************************************************/
        ALOX_API
        ~Domain();

        /** ****************************************************************************************
         * Returns the domains log level. If this is set to INHERIT, the effective value is evaluated
         * (recursively) from the parent's domain.
         *
         * @return The found/defined domain log level.
         ******************************************************************************************/
        ALOX_API
        Log::DomainLevel    GetLevel();

        /** ****************************************************************************************
         * Sets the level of this domain and optionally of all its sub domains to the specified value.
         * \note
         *   The root domain's level can not be set to DomainLevel.Inherit.
         *   Such request would be ignored.
         *
         * @param domainLevel The domain level value to set.
         * @param propagation If \c Propagation::ToDescendants (the default), the level is set for all
         *                    sub-domains currently existing.
         *                    If \c Propagation::None, then only this domain is changed.
         ******************************************************************************************/
        ALOX_API
        void                SetLevel( Log::DomainLevel domainLevel,
                                      lib::enums::Propagation propagation= lib::enums::Propagation::ToDescendants );

        /** ****************************************************************************************
         * Determines if the domain is active in respect to the given Log.Level and the current
         * domain level.
         *
         * @param level    The log level to check .
         * @return  \c true if domain is active (log should be performed)
         ******************************************************************************************/
        ALOX_API
        bool                IsActive( Log::Level level );

        /** ****************************************************************************************
         * Searches a domain. If not found, the domain is (or branch of domains are) created in
         * the domain tree.
         * If the path String starts with a domain separator character, then
         * the search (and creation) is done starting from the root domain of this domain and not
         * from this domain.
         *
         * @param       domainPath  Path and domain to search.
         * @param[out]  wasCreated  Output parameter that is set \c true if domain was not found
         *                          and hence created.
         * @return    The domain found or created.
         ******************************************************************************************/
        ALOX_API
        Domain*             Find( Substring domainPath, bool* wasCreated= nullptr );


    // #############################################################################################
    // Internals
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * The internal recursive helper to implement the Find() interface.
         *
         * @param       domainPath  Path to search.
         * @param[out]  wasCreated  Output parameter that is set \c true if domain was not found
         *                          and hence created.
         * @return    The domain found or created.
         ******************************************************************************************/
         Domain*           findRecursive( Substring&  domainPath, bool* wasCreated= nullptr  );

}; // Domain

}}} // namespace aworx::lox::core

#endif // HPP_ALOX_CORE_DOMAIN
