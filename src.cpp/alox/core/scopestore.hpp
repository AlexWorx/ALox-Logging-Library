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
#ifndef HPP_ALOX_CORE_SCOPE
#define HPP_ALOX_CORE_SCOPE 1


// #################################################################################################
// includes
// #################################################################################################

namespace aworx { namespace lib { namespace containers{ template<typename StoreT> class PathMap; }}}

namespace aworx {
namespace       lox {
namespace           core{


/** ************************************************************************************************
 * Static axiomatic methods on value types stored in class \b ScopeStore.
 * \note This is a pure internal helper class. Documentation may be limited.
 **************************************************************************************************/
template<typename StoreT>
class ScopeStoreType
{
    public:

    /** ********************************************************************************************
     * Static method to retrieve a value representing null for the template type.
     * @return The value representing null.
     **********************************************************************************************/
    ALOX_API
    static StoreT NullValue();

    /** ********************************************************************************************
     * Returns true if the value is representing null.
     * @param value  The object to test for null.
     * @returns \c true if the value is representing null, \c false otherwise.
     **********************************************************************************************/
    ALOX_API
    static bool IsNull( StoreT value );

    /** ********************************************************************************************
     * Compares two template values.
     * @param first          First value.
     * @param second         Second value.
     * @returns \c true if objects are equal, \c false otherwise.
     **********************************************************************************************/
    ALOX_API
    static bool AreEqual( StoreT first, StoreT second );

}; // ScopeStoreType

/** ************************************************************************************************
 * This class is responsible for scope-related functionality of class Lox.
 * \note This is a pure internal helper class. Documentation may be limited.
 **************************************************************************************************/
template<typename StoreT>
class ScopeStore
{
    // #############################################################################################
    // Public fields
    // These fields are public, but publicly accessed only for LogConfig and Reset()
    // (bauhaus code style, omitting getters. For library users this is still invisible, as
    // the stores are protected in class Lox)
    // #############################################################################################
    public:
        /** The value of the global scope */
        StoreT                                  globalStore;

        /** PathMap store for language-related scopes (path,source,method) */
        lib::containers::PathMap<StoreT>*      languageStore;

        /** A list of domain paths of \e Scope::ThreadOuter */
        std::map<int, std::vector<StoreT>>      threadOuterStore;

        /** A list of domain paths of \e Scope::ThreadInner */
        std::map<int, std::vector<StoreT>>      threadInnerStore;


    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:

        /** ScopeInfo of 'our' lox  */
        ScopeInfo&                              scopeInfo;

        /** If true, values stored for thread scopes will be always replaced instead of appended.
         *  This is for example \c true for <em>Log Data</em> and \c false for
         *  <em>Scope Domains</em>                                                                */
        bool                                    cfgSingleThreadValue;

        /** Flag used to lazily create the key to language-related scope values */
        bool                                    lazyLanguageNode;

        /** Indicates if currently a scope walk is active */
        bool                                    walking;

        /** The actual scope of a walk  */
        Scope                                   actScope;

        /** The actual language related scopes' map node */
        lib::containers::PathMap<StoreT>*       actPathMapNode;

        /** The path level when using access methods */
        int                                     actPathLevel;

        /** Actual thread ID */
        int                                     actThreadID;

        /** The 'local object' returned by a walk after Scope::ThreadInner and before Scope::Method */
        StoreT                                  walkLocalObject;

        /** The next value of a walk during \e Scope::ThreadInner/Outer  */
        int                                     walkNextThreadIdx;

        /** The list of values of \e Scope::ThreadOuter/Inner during a walk */
        std::vector<StoreT>*                    walkThreadValues;

    // #############################################################################################
    // Public interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Constructor
         * @param scopeInfo  The ScopeInfo singleton of 'our' Lox.
         * @param cfgSingleThreadValue Determines if for thread-related scopes, a list of values is
         *                             stored, or just one.
         ******************************************************************************************/
        ALOX_API
        ScopeStore( ScopeInfo& scopeInfo, bool cfgSingleThreadValue );

        /** ****************************************************************************************
         * Destructor
         ******************************************************************************************/
        ALOX_API
        ~ScopeStore();

        /** ****************************************************************************************
         * Clears all data stored, resets all values.
         ******************************************************************************************/
        ALOX_API
        void Clear();

        /** ****************************************************************************************
         * Initializes access methods #Store, #Get and #Remove and has to be invoked prior to
         * using them
         * @param scope      Scope to use.
         * @param pathLevel  Used only if parameter \p scope equals
         *                   \ref aworx::lox::Scope::Path "Scope.Path"
         *                   to reference parent directories. Optional and defaults to \c 0.
         * @param threadID   ID of the associated thread (for thread-related scopes only).
         *                   If Thread::NullThreadId is given, the ID from \p scopeInfo is used.
         ******************************************************************************************/
        ALOX_API
        void InitAccess    ( Scope scope, int pathLevel, int threadID );

        /** ****************************************************************************************
         * Stores a new value for the given scope.
         * @param value      The value to set.
         * @return Returns the previous value stored.
         ******************************************************************************************/
        StoreT Store    ( StoreT value )
        {
            ALIB_ASSERT( value != ScopeStoreType<StoreT>::NullValue() );
            return access( 0, value );
        }


        /** ****************************************************************************************
         * Removes a value for the given scope.
         * @param value      The value to remove (must only be given for thread-related \e Scopes).
         * @return Returns the previous value stored.
         ******************************************************************************************/
        StoreT Remove   ( StoreT value )
        {
            return access( 1, value );
        }

        /** ****************************************************************************************
         * Retrieves the value for the given scope.
         *                   If Thread::NullThreadId is given, the ID from \p scopeInfo is used.
         * @return Returns the current value stored.
         ******************************************************************************************/
        StoreT Get      ()
        {
            return access( 2, ScopeStoreType<StoreT>::NullValue() );
        }

        /** ****************************************************************************************
         * Initializes a scope 'walk' by storing the given scope information and
         * setting fields of our walk 'state-machine' to proper start values.
         *
         * @param startScope       The \e Scope to start searching for.
         * @param localObject      The 'local object' returned by a walk after Scope::ThreadInner
         *                         and before Scope::Method
         ******************************************************************************************/
        ALOX_API
        void InitWalk( Scope startScope, StoreT localObject  );

        /** ****************************************************************************************
         * Searches value in the actual scope. While not found, moves walk state to next outer
         * and continues there.
         * @return The next object found in the current or any next outer scope.
         ******************************************************************************************/
        ALOX_API
        StoreT Walk();

    // #############################################################################################
    // Internals
    // #############################################################################################
    protected:

        /** ****************************************************************************************
         * Retrieves and optionally creates an entry in the map that stores language-related
         * scope information. The result is stored in field #actPathMapNode.
         * @param create     If \c true, a non-existing entry is created.
         ******************************************************************************************/
        void getPathMapNode( bool create );

        /** ****************************************************************************************
         * Receives, inserts or removes a value.
         * @param cmd        0= insert, 1= remove, 2= get.
         * @param value      The new value or the one to be removed.
         * @return Returns the previous value stored.
         ******************************************************************************************/
        StoreT access( int cmd, StoreT value );

}; // ScopeStore

}}} // namespace aworx::lox::core



#endif // HPP_ALOX_CORE_SCOPE
