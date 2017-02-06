// #####################################################################oggeg############################
//  com.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core;

import java.util.ArrayList;
import java.util.HashMap;

import com.aworx.lib.containers.PathMap;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lox.Scope;

/** ************************************************************************************************
 * This class is responsible for scope-related functionality of class Lox.
 * \note This is a pure internal helper class. Documentation may be limited.
 **************************************************************************************************/
public class ScopeStore<T>
{
    // #############################################################################################
    // Public fields
    // These fields are public, but publicly accessed only for State and Reset()
    // (bauhaus code style, omitting getters. For library users this is still invisible, as
    // the stores are protected in class Lox)
    // #############################################################################################
        /** The value to the global scope */
        public T                              globalStore;

        /** PathMap store for language-related scopes (path,source,method) */
        public PathMap<T>                     languageStore                      = new PathMap<T>();

        /** A list of domain paths of \e %Scope.THREAD_OUTER */
        public HashMap<Thread, ArrayList<T>>  threadOuterStore= new HashMap<Thread, ArrayList<T>>();

        /** A list of domain paths of \e %Scope.THREAD_INNER */
        public HashMap<Thread, ArrayList<T>>  threadInnerStore= new HashMap<Thread, ArrayList<T>>();


    // #############################################################################################
    // Protected fields
    // #############################################################################################

        /** The ScopeInfo singleton of our Lox    */
        protected ScopeInfo                           scopeInfo;

        /** If true, values stored for thread scopes will be always replaced instead of appended.
         *  This is for example \c true for <em>Log Data</em> and \c false for
         *  <em>Scope Domains</em>                                                              */
        protected boolean                             cfgSingleThreadValue;

        /** Flag used to lazily create the key to language-related scope values */
        protected AString                             languageKey                = new AString(128);

        /** Flag used to lazily create the key to source-related scope values */
        protected boolean                             lazyLanguageNode;

        /** Indicates if currently a scope walk is active */
        protected boolean                             walking;

        /** The actual scope of a walk (array, because it is used as second return value) */
        protected Scope                               actScope;

        /** The actual language related scopes' map node */
        protected PathMap<T>                          actPathMapNode;

        /** The next package level of a walk during scope 'PACKAGE' */
        protected int                                 actPackageLevel;

        /** The actual thread  */
        protected Thread                              actThread;

        /** The 'local object' returned by a walk after Scope. THREAD_INNER and before Scope.METHOD */
        protected T                                   walkLocalObject;

        /** The next value of a walk during \e %Scope.THREAD_OUTER/INNER */
        protected int                                 walkNextThreadIdx;

        /** The list of values of \e %Scope.THREAD_OUTER/Inner during a walk */
        protected ArrayList<T>                        walkThreadValues;

        /** The (constant) list of separators needed by the tree map */
        protected AString                             separators              = new AString( "#." );

        /** A temporary substring used for searching keys in the tree map */
        protected Substring                           languageKeySubstr           = new Substring();
    // #############################################################################################
    // Public interface
    // #############################################################################################
        /** ****************************************************************************************
         * Constructor
         * @param scopeInfo  The ScopeInfo singleton of 'our' Lox.
         * @param cfgSingleThreadValue Determines if for thread-related scopes, a list of values is
         *                             stored, or just one.
         ******************************************************************************************/
        public ScopeStore( ScopeInfo scopeInfo, boolean cfgSingleThreadValue)
        {
            this.scopeInfo=             scopeInfo;
            this.cfgSingleThreadValue=  cfgSingleThreadValue;
            this.globalStore=           null;
        }


        /** ****************************************************************************************
         * Clears all data stored, resets all values.
         ******************************************************************************************/
        public void clear()
        {
            globalStore=    null;
            threadInnerStore.clear();
            languageStore=  new PathMap<T>();
            threadOuterStore.clear();
        }

        /** ****************************************************************************************
         * Stores a new value for the given scope.
         * @param value   The new value to set.
         * @return Returns the previous value stored.
         ******************************************************************************************/
        public T store(  T value )
        {
            return access( 0, value );
        }

        /** ****************************************************************************************
         * Removes a value for the given scope.
         * @param value   The value to remove (only used for thread-related \e Scopes).
         * @return Returns the previous value stored.
         ******************************************************************************************/
        public T remove( T value  )
        {
            return access( 1, value );
        }

        /** ****************************************************************************************
         * Retrieves the value for the given scope.
         * @return Returns the current value stored.
         ******************************************************************************************/
        public T get()
        {
            return access( 2, null );
        }

        /** ****************************************************************************************
         * Initializes a scope 'walk' by storing the given scope information and
         * setting fields of our walk 'state-machine' to proper start values.
         *
         * @param startScope       The \e Scope to start searching for.
         * @param localObject      The 'local object' returned by a walk after Scope.THREAD_INNER
         *                         and before Scope.METHOD.
         ******************************************************************************************/
        public void initWalk( Scope startScope, T localObject )
        {
            actScope=           startScope;
            walkLocalObject=    localObject;
            actPackageLevel=    0;
            walkNextThreadIdx=  -2;
            lazyLanguageNode=   true;
            walking=            true;
        }

        /** ****************************************************************************************
         * Searches value in the actual scope. While not found, moves walk state to next outer
         * and continues there.
         * @return The next object found in the current or any next outer scope.
         ******************************************************************************************/
        public T walk( )
        {
            while ( walking )  switch( actScope )
            {
                case THREAD_INNER:
                {
                    // initialize
                    if ( walkNextThreadIdx == -2 )
                    {
                        walkNextThreadIdx= -1;
                        if ( threadInnerStore.size() != 0 )
                        {
                            walkThreadValues= threadInnerStore.get( scopeInfo.getThread() );
                            if ( walkThreadValues != null )
                                walkNextThreadIdx=   walkThreadValues.size();
                        }
                    }

                    // return next inner thread object (walkNext keeps being THREAD_INNER)
                    if ( walkNextThreadIdx > 0 )
                    {
                        walkNextThreadIdx--;
                        return walkThreadValues.get( walkNextThreadIdx );
                    }

                    // next scope is METHOD
                    actScope= Scope.METHOD;

                    // if we have a valid 'local object' return this first
                    if ( walkLocalObject != null )
                        return walkLocalObject;
                }
                break;


                case PACKAGE:
                case CLASS:
                case METHOD:
                {
                    if( lazyLanguageNode )
                        getPathMapNode( false );

                    while( actPathMapNode != null )
                    {
                        T actValue= actPathMapNode.value;
                        actPathMapNode= actPathMapNode.parent;
                        if( actValue != null )
                            return actValue;
                    }

                    actScope=  Scope.THREAD_OUTER;
                    walkNextThreadIdx= -2;
                }
                break;

                case THREAD_OUTER:
                {
                    // initialize
                    if ( walkNextThreadIdx == -2 )
                    {
                        if ( threadOuterStore.size() != 0 )
                        {
                            walkThreadValues= threadOuterStore.get( scopeInfo.getThread() );
                            if ( walkThreadValues != null )
                            {
                                walkNextThreadIdx=   walkThreadValues.size();
                                break;
                            }
                        }
                    }

                    // return next outer thread object (walkNext keeps being THREAD_OUTER)
                    if ( walkNextThreadIdx > 0 )
                    {
                        walkNextThreadIdx--;
                        return walkThreadValues.get( walkNextThreadIdx );
                    }

                    // next scope is Global
                    actScope=  Scope.GLOBAL;
                }
                break;

                case GLOBAL:
                {
                    walking=  false;
                    return globalStore;
                }
            }

            return null;
        }

    /** ****************************************************************************************
     * Initializes access methods #store, #get and #remove and has to be invoked prior to
     * using them
     *
     * @param scope          Scope to use.
     * @param packageLevel   Used with Scope.PACKAGE to determine outer level.
     * @param thread         The associated thread (for thread-related scopes only).
     *                       If \c 0 is given, the ID from \p scopeInfo is used.
     ******************************************************************************************/
    public void InitAccess( Scope scope, int packageLevel, Thread thread )
    {
        actScope=           scope;
        actPackageLevel=    packageLevel;
        actThread=          thread;
        lazyLanguageNode=   true;
    }

    // #############################################################################################
    // Internals
    // #############################################################################################

        /** ****************************************************************************************
         * Retrieves and optionally creates an entry in the map that stores language-related
         * scope information. The result is stored in field #actPathMapNode.
         * @param create     If \c true, a non-existing entry is created.
         ******************************************************************************************/
        protected void getPathMapNode( boolean create )
        {
            lazyLanguageNode= false;

            // key: package
            languageKey._()._( scopeInfo.getPackageName() );

            // key: package
            if ( actScope == Scope.PACKAGE )
            {
                // Subtract folders at the back
                int packageLevel= actPackageLevel;
                while (packageLevel > 0 )
                {
                    int idx= languageKey.lastIndexOf( '.' );
                    if (idx < 0 )
                    {
                        languageKey._();
                        break;
                    }
                    languageKey.setLength_NC( idx );
                    packageLevel--;
                }

                languageKey._( separators.charAt_NC(1) );
                actPathMapNode= languageStore.Get( languageKeySubstr.set(languageKey), create, separators );
                return;
            }

            languageKey._( separators.charAt_NC(1) );


            // key: class
            languageKey._( '-' ) // we need a prefix to have all methods share one start node which is not
                                 // a separator-node
                       ._( scopeInfo.getClassName() )
                       ._( separators.charAt_NC(0) );

            // key: method
            if ( actScope == Scope.METHOD )
                languageKey._( '-' ) // we need a prefix to have all methods share one start node which is not
                                     // a separator-node
                           ._( scopeInfo.getMethodName() )
                           ._( separators.charAt_NC(0) );

            actPathMapNode= languageStore.Get( languageKeySubstr.set(languageKey), create, separators );
        }

        /** ****************************************************************************************
         * Receives, inserts or removes a value.
         * @param cmd            0= insert, 1= remove, 2= get.
         * @param value          The new value or the one to be removed.
         * @return Returns the previous value stored.
         ******************************************************************************************/
        protected T access( int cmd, T value )
        {
            T oldValue= null;

            // --------- global scope ---------
            if( actScope == Scope.GLOBAL )
            {
                oldValue= globalStore;
                if ( cmd == 0 )
                    globalStore= value;
                else if ( cmd == 1 )
                    globalStore= null;

                return oldValue;
            }

            // --------- tread-related scopes ---------
            if(     actScope == Scope.THREAD_OUTER
                ||  actScope == Scope.THREAD_INNER    )
            {
                // choose outer/inner store
                HashMap<Thread, ArrayList<T>> threadStore=
                    actScope == Scope.THREAD_INNER  ? threadInnerStore
                                                     : threadOuterStore;

                // check if empty (to avoid key creation/thread detection )
                if ( cmd != 0 && threadStore.size() == 0 )
                    return oldValue;

                // thread given?
                if ( actThread == null )
                    actThread= scopeInfo.getThread();

                // find (create) the vector of values
                ArrayList<T>  values= threadStore.get( actThread );
                if ( values == null )
                    threadStore.put( actThread, values= new ArrayList<T>());

                // 'get'
                if ( cmd == 2 )
                    return  ( values.size() > 0) ? values.get( values.size() -1 ) : null;

                // 'insert'
                if ( cmd == 0 )
                {
                    if ( cfgSingleThreadValue )
                    {
                        if ( values.size() > 0)
                        {
                            oldValue= values.get( 0 );
                            if ( value != null)
                                values.set( 0, value );
                            else
                                values.remove( 0 );
                        }
                        else // value is never null here
                            values.add( value );
                    }
                    else
                        // if multiple values are allowed we do not return an 'oldValue'
                        values.add( value );

                   return oldValue;
                }

                // remove has two options: the last or, if given, a specific one
                if ( cmd == 1  && values.size() > 0)
                {
                    // remove the last
                    if ( value == null )
                    {
                        oldValue= values.get( values.size() - 1 );
                        values.remove( values.size() - 1 ) ;
                    }

                    // remove a specific one.
                    else
                        for ( int i= values.size() - 1; i>= 0; i-- )
                        {
                            //We return the found value, if found, otherwise we don't do anything
                            if ( values.get(i).equals( value ) )
                            {
                                oldValue= values.get(i);
                                values.remove( i );
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
                    ||  ( actPathMapNode == null && cmd == 0 ) ) // insert
                    getPathMapNode( true ); // always create

                if ( actPathMapNode != null )
                {
                    oldValue = actPathMapNode.value;

                    if ( cmd == 0 ) // insert
                        actPathMapNode.value= value;

                    else if ( cmd == 1 ) // remove
                        languageStore.Remove( actPathMapNode );
                }

                return oldValue;
            }
        }




} // class ScopeStore
