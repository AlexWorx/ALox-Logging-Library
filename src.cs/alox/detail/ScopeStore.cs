// #################################################################################################
//  cs.aworx.lox.detail - ALox Logging Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using cs.aworx.lib;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using System.IO;
using System.Threading;
using cs.aworx.lib.util;

namespace cs.aworx.lox.detail {
/** ************************************************************************************************
 * This class is responsible for scope-related functionality of class Lox.
 * \note This is a pure internal helper class. Documentation may be limited.
 **************************************************************************************************/
#if ALOX_DBG_LOG || ALOX_REL_LOG

public class ScopeStore<T>
{
    // #############################################################################################
    // Public fields
    // These fields are public, but publicly accessed only for State and Reset()
    // (bauhaus code style, omitting getters. For library users this is still invisible, as
    // the stores are protected in class Lox)
    // #############################################################################################

        /** The value to the global scope */
        public T                                   globalStore;

        /** StringTree store for language-related scopes (path,source,method) */
        public StringTree<T>                       languageStore              = new StringTree<T>();

        /** A list of domain paths of \e %Scope.ThreadOuter */
        public Dictionary<Thread, List<T>>         threadOuterStore=new Dictionary<Thread, List<T>>();

        /** A list of domain paths of \e %Scope.ThreadInner */
        public Dictionary<Thread, List<T>>         threadInnerStore=new Dictionary<Thread, List<T>>();

    // #############################################################################################
    // Protected fields
    // #############################################################################################

        /** If true, values stored for thread scopes will be always replaced instead of appended.
         *  This is for example \c true for <em>Log Data</em> and \c false for
         *  <em>Scope Domains</em>                                                              */
        protected bool                             cfgSingleThreadValue;

        /** The ScopeInfo singleton of our Lox    */
        protected ScopeInfo                        scopeInfo;

        /** Temporary string for assembling source key */
        protected AString                          languageKey                   = new AString(128);

        /** Temporary substring for consuming the source key */
        protected Substring                        languageKeySubs                = new Substring();

        /** Flag used to lazily create the key to language-related scope values */
        protected bool                             lazyLanguageNode;

        /** Indicates if currently a scope walk is active */
        protected bool                             walking;

        /** The actual scope of a walk */
        protected Scope                            actScope;

        /** The actual language related scopes' map node */
        protected StringTree<T>.Cursor             actStringTreeNode;

        /** The next path level of a walk during scope 'Path' */
        protected int                              actPathLevel;

        /** The actual thread  */
        protected Thread                           actThread;

        /** The 'local object' returned by a walk after Scope.ThreadInner and before
         *  Scope.Method */
        protected T                                walkLocalObject;

        /** The next value of a walk during \e %Scope.ThreadOuter/Inner */
        protected int                              walkNextThreadIdx;

        /** The list of values of \e %Scope.ThreadOuter/Inner during a walk */
        protected List<T>                          walkThreadValues;

    // #############################################################################################
    // Public interface
    // #############################################################################################
        /** ****************************************************************************************
         * Constructor
         * @param scopeInfo  The ScopeInfo singleton of 'our' Lox.
         * @param cfgSingleThreadValue Determines if for thread-related scopes, a list of values is
         *                             stored, or just one.
         ******************************************************************************************/
        public ScopeStore( ScopeInfo scopeInfo, bool cfgSingleThreadValue )
        {
            this.scopeInfo=             scopeInfo;
            this.cfgSingleThreadValue=  cfgSingleThreadValue;
            this.globalStore=           default(T);
            actStringTreeNode=          languageStore.Root();
        }

        /** ****************************************************************************************
         * Clears all data stored, resets all values.
         ******************************************************************************************/
        public void Clear()
        {
            globalStore=    default(T);
            threadInnerStore.Clear();
            languageStore=  new StringTree<T>();
            threadOuterStore.Clear();
        }

        /** ****************************************************************************************
         * Stores a new value for the given scope.
         * @param value          The new value to set.
         * @return Returns the previous value stored.
         ******************************************************************************************/
        public T Store    (T value  )
        {
            return access( 0, value );
        }

        /** ****************************************************************************************
         * Removes a value for the given scope.
         * @param value      The value to remove (only used for thread-related \e Scopes).
         * @return Returns the previous value stored.
         ******************************************************************************************/
        public T Remove(T value )
        {
            return access( 1, value );
        }

        /** ****************************************************************************************
         * Retrieves the value for the given scope.
         * @return Returns the current value stored.
         ******************************************************************************************/
        public T Get()
        {
            return access( 2, default(T) );
        }

        /** ****************************************************************************************
         * Initializes a scope 'walk' by storing the given scope information and
         * setting fields of our walk 'state-machine' to proper start values.
         *
         * @param startScope       The \e Scope to start searching for.
         * @param localObject      The 'local object' returned by a walk after Scope.ThreadInner
         *                         and before Scope.Method
         ******************************************************************************************/
        public void InitWalk( Scope startScope, T localObject )
        {
            actScope=            startScope;
            walkLocalObject=     localObject;
            actPathLevel=        0;
            walkNextThreadIdx=   -2;
            lazyLanguageNode=    true;
            walking=             true;
        }


        /** ****************************************************************************************
         * Searches value in the actual scope. While not found, moves walk state to next outer
         * and continues there.
         * @return The next object found in the current or any next outer scope.
         ******************************************************************************************/
        public T  Walk()
        {
            while ( walking )  switch( actScope )
            {
                case Scope.ThreadInner:
                {
                    // initialize
                    if ( walkNextThreadIdx == -2 )
                    {
                        walkNextThreadIdx= -1;
                        if ( threadInnerStore.Count != 0 )
                        {
                            walkThreadValues= null;
                            threadInnerStore.TryGetValue( scopeInfo.GetThread(), out walkThreadValues );
                            if ( walkThreadValues != null )
                                walkNextThreadIdx=   walkThreadValues.Count;
                        }
                    }

                    // return next inner thread object (walkNext keeps being ThreadInner)
                    if ( walkNextThreadIdx > 0 )
                    {
                        walkNextThreadIdx--;
                        return walkThreadValues[walkNextThreadIdx];
                    }

                    // next scope is Method
                    actScope= Scope.Method;

                    // if we have a valid 'local object' return this first
                    if ( walkLocalObject != null )
                        return walkLocalObject;
                }
                break;

                case Scope.Path:
                case Scope.Filename:
                case Scope.Method:
                {
                    if( lazyLanguageNode )
                        initCursor( false );

                    while( actStringTreeNode.IsValid() )
                    {
                        T actValue = actStringTreeNode.Value();
                        actStringTreeNode.MoveToParentUnchecked();
                        if( actValue != null )
                            return actValue;
                    }

                    actScope=  Scope.ThreadOuter;
                    walkNextThreadIdx= -2;
                }
                break;

                case Scope.ThreadOuter:
                {
                    // initialize
                    if ( walkNextThreadIdx == -2 )
                    {
                        if ( threadOuterStore.Count != 0 )
                        {
                            walkThreadValues= null;
                            threadOuterStore.TryGetValue( scopeInfo.GetThread(), out walkThreadValues );
                            if ( walkThreadValues != null )
                                walkNextThreadIdx=   walkThreadValues.Count;
                        }
                    }

                    // return next outer thread object (walkNext keeps being ThreadOuter)
                    if ( walkNextThreadIdx > 0 )
                    {
                        walkNextThreadIdx--;
                        return walkThreadValues[walkNextThreadIdx];
                    }

                    // next scope is Global
                    actScope= Scope.Global;
                }
                break;

                case Scope.Global:
                {
                    walking=  false;
                    return globalStore;
                }
            }

            return default(T);
        }

    /** ****************************************************************************************
     * Initializes access methods #Store, #Get and #Remove and has to be invoked prior to
     * using them
     *
     * @param scope          Scope to use.
     * @param pathLevel      Used with Scope.FilePath to determine outer level.
     * @param thread         The associated thread (for thread-related scopes only).
     *                       If \c 0 is given, the ID from \p{scopeInfo} is used.
     ******************************************************************************************/
    public void InitAccess( Scope scope, int pathLevel, Thread thread )
    {
        actScope=           scope;
        actPathLevel=       pathLevel;
        actThread=          thread;
        lazyLanguageNode=   true;
    }


    // #############################################################################################
    // Internals
    // #############################################################################################

        /** ****************************************************************************************
         * Retrieves and optionally creates an entry in the map that stores language-related
         * scope information. The result is stored in field #actStringTreeNode.
         * @param create     If \c true, a non-existing entry is created.
         ******************************************************************************************/
        protected void initCursor( bool create )
        {
            lazyLanguageNode=   false;
            actStringTreeNode.Root();

            // path key for the StringTree
            languageKey._()._( scopeInfo.GetTrimmedPath() );
            languageKey.SearchAndReplace( '\\', '/' );
            languageKeySubs.Set(languageKey);

            // read-only mode
            if( !create )
            {
                // in non-creation mode, it is always scope Method
                ALIB_DBG.ASSERT(actScope == Scope.Method);

                // in read only mode, we can leave as soon as a portion was not read
                actStringTreeNode.MoveToExistingPart( languageKeySubs );
                if ( languageKeySubs.IsNotEmpty() )
                    return;

                // filename: append '#' to distinguish from directories
                if ( !actStringTreeNode.MoveToChild( languageKey._()._NC( scopeInfo.GetFileNameWithoutExtension() )._( '#' ).ToString() ) )
                    return;

                // filename: prepend '#' to distinguish from filenames
                actStringTreeNode.MoveToChild( languageKey._()._NC( '#' )._NC( scopeInfo.GetMethod() ).ToString() );

                return;
            }

            // create mode:
            actStringTreeNode.MoveToAndCreateNonExistingPart( languageKeySubs );
            if ( actScope == Scope.Path )
            {
                // subtract folders at the back
                int pathLevel= actPathLevel;
                while ( --pathLevel >= 0 && !actStringTreeNode.IsRoot() )
                    actStringTreeNode.MoveToParent();
                return;
            }

            // filename: append '#' to distinguish from directories
            languageKey._()._( scopeInfo.GetFileNameWithoutExtension() )._( '#' );

            // filename: prepend '#' to distinguish from filenames
            if ( actScope == Scope.Method )
                languageKey._( "/#" )._( scopeInfo.GetMethod() );
            languageKeySubs.Set(languageKey);

            actStringTreeNode.MoveToAndCreateNonExistingPart( languageKeySubs );
        }

        /** ****************************************************************************************
         * Receives, inserts or removes a value.
         * @param cmd            0= insert, 1= remove, 2= get.
         * @param value          The new value or the one to be removed.
         * @return Returns the previous value stored.
         ******************************************************************************************/
        protected T access( int cmd, T value )
        {
            T oldValue= default(T);

            // --------- global scope ---------
            if( actScope == Scope.Global )
            {
                oldValue= globalStore;
                if ( cmd == 0 )
                    globalStore= value;
                else if ( cmd == 1 )
                    globalStore= default(T);

                return oldValue;
            }

            // --------- tread-related scopes ---------
            if(     actScope == Scope.ThreadOuter
                ||  actScope == Scope.ThreadInner    )
            {
                // choose outer/inner store
                Dictionary<Thread, List<T>>  threadStore=
                    actScope == Scope.ThreadInner  ? threadInnerStore
                                                   : threadOuterStore;

                // check if empty (to avoid key creation/thread detection )
                if ( cmd != 0 && threadStore.Count == 0 )
                    return oldValue;

                // thread given?
                if ( actThread == null )
                    actThread= scopeInfo.GetThread();

                // find (create) the vector of values
                List<T>  values= null;
                threadStore.TryGetValue( actThread, out values );
                if ( values == null )
                    threadStore[actThread]= (values= new List<T>());

                // 'get'
                if ( cmd == 2 )
                    return  values.Count > 0 ? values[ values.Count -1 ] : default(T);


                // insert is simple, we do not even return an 'oldValue'
                if ( cmd == 0 )
                {
                    if ( cfgSingleThreadValue )
                    {
                        if ( values.Count > 0)
                        {
                            oldValue= values[0];
                            if ( value != null)
                                values[0]= value;
                            else
                                values.RemoveAt( 0 );
                        }
                        else // value is never null here
                            values.Add( value );
                    }
                    else
                        // if multiple values are allowed we do not return an 'oldValue'
                        values.Add( value );

                   return oldValue;
                }

                // remove has two options: the last or, if given, a specific one
                if ( cmd == 1  && values.Count > 0)
                {
                    // remove the last
                    if ( value == null )
                    {
                        oldValue= values[ values.Count - 1 ];
                        values.RemoveAt(  values.Count - 1 ) ;
                    }

                    // remove a specific one.
                    else
                        for ( int i= values.Count - 1; i>= 0; i-- )
                        {
                            //We return the found value, if found, otherwise we don't do anything
                            if ( values[i].Equals( value ) )
                            {
                                oldValue= values[i];
                                values.RemoveAt( i );
                                break;
                            }
                        }
                }

                return oldValue;
            }

            // --------- language-related scopes ---------
            {
                // 0= insert, 1= remove, 2= get.
                if ( cmd == 0 && value == null )
                    cmd= 1;

                if (    lazyLanguageNode
                    ||  ( actStringTreeNode == null && cmd == 0 ) ) // insert
                    initCursor( true ); // always create

                if ( actStringTreeNode.IsValid() )
                {
                    oldValue = actStringTreeNode.Value();

                    if ( cmd == 0 ) // insert
                        actStringTreeNode.SetValue( value );

                    else if ( cmd == 1 ) // remove
                        actStringTreeNode.SetValue( default(T) );
                }

                return oldValue;
            }
        }



} // class ScopeStore

#endif // ALOX_DBG_LOG || ALOX_REL_LOG ,started before class ScopeInfo


} // namespace
