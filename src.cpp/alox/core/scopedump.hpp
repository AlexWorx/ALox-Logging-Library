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
#ifndef HPP_ALOX_CORE_SCOPEDUMP
#define HPP_ALOX_CORE_SCOPEDUMP 1


// #################################################################################################
// includes
// #################################################################################################
#if !defined (_GLIBCXX_VECTOR) && !defined(_VECTOR_)
    #include <vector>
#endif

#include "scopestore.hpp"


namespace aworx {
namespace       lox {
namespace           core{

/** ************************************************************************************************
 * This class is an internal helper to export current scope values.
 * It was extracted from class \b %Lox to keep that class clean from this somehow 'cluttered' code.
 *
 * The current purpose of this class is to write information into an AString buffer. This is used
 * by method \ref aworx::lox::Lox::State "Lox::State". In the future, other export formats,
 * like JSON might be implemented here.
 *
 * \note As this is a pure internal helper class. Documentation may be limited.
 **************************************************************************************************/
class ScopeDump
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /** The target to write to */
        AString&                        target;

        /** String to identify global keys. */
        const TString                   noKeyHashKey;

        /** The maximum length of a key. Adjusts (increases) over lifecycle. */
        int                             maxKeyLength;

        /** User-defined threads names. */
        ScopeInfo::ThreadDictionary&    threadDictionary;

    // #############################################################################################
    // Public interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Constructor
         * @param threadDictionary User-defined threads names.
         * @param target           Target string to write to.
         * @param noKeyHashKey     String to identify global keys.
         * @param maxKeyLength     The start value for the maximum length of a key.
         ******************************************************************************************/
        ScopeDump( ScopeInfo::ThreadDictionary& threadDictionary, const TString noKeyHashKey,
                   AString& target, int maxKeyLength= 10 )
        : target(target)
        , noKeyHashKey(noKeyHashKey)
        , maxKeyLength(maxKeyLength)
        , threadDictionary(threadDictionary)
        {
        }

        /** ****************************************************************************************
         * Writes hash tables stored in a ScopeStore. Keys are AStrings.
         * Value types currently supported are LogData* and int.
         * @param store The store to use.
         * @return The total number of hash table entries written.
         ******************************************************************************************/
        template<typename T>
        ALOX_API
        int writeStoreMap( ScopeStore<T>* store );


        /** ****************************************************************************************
         * Writes the contents of the ScopeStore used for <em>Scope Domains</em>.
         * @param store         The store to use
         * @param indentSpaces  The number of spaces to add at the beginning of each line.
         * @return The total number of <em>Scope Domains</em> written.
         ******************************************************************************************/
        template<typename T>
        ALOX_API
        int writeStore( ScopeStore<T>* store, int indentSpaces );

    // #############################################################################################
    // Internals
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Helper method to #writeStoreMap.
         * @param map       The map to use
         * @param prefix    A prefix string for each line
         * @return The number of objects written
         ******************************************************************************************/
        template<typename T>
        ALOX_API
        int writeStoreMapHelper( std::map<AString, T>& map, const TString& prefix );

        /** ****************************************************************************************
         * Helper method to write thread information.
         * @param threadID  The thread id.
         * @return The target to allow concatenated calls.
         ******************************************************************************************/
        ALOX_API
        AString& storeThreadToScope( int threadID );

        /** ****************************************************************************************
         * Helper method to write a PathMaps' key as scope information.
         * @param map  The PathMap node to get scope information for.
         * @return The target to allow concatenated calls.
         ******************************************************************************************/
        template<typename T>
        ALOX_API
        AString& storeKeyToScope( const lib::containers::PathMap<T>& map );

}; // ScopeDump

}}} // namespace aworx::lox::core



#endif // HPP_ALOX_CORE_SCOPEDUMP
