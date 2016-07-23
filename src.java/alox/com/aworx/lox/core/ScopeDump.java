// #####################################################################oggeg############################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import com.aworx.lib.ALIB;
import com.aworx.lib.containers.PathMap;
import com.aworx.lib.enums.Alignment;
import com.aworx.lib.strings.AString;
import com.aworx.lox.LogData;

/** ************************************************************************************************
 * This class is an internal helper to export current scope values.
 * It was extracted from class \b %Lox to keep that class clean from this somehow 'cluttered' code.
 *
 * The current purpose of this class is to write information into an AString buffer. This is used
 * by method \ref com::aworx::lox::Lox::state "Lox.state". In the future, other export formats,
 * like JSON might be implemented here.
 *
 * \note As this is a pure internal helper class. Documentation may be limited.
 **************************************************************************************************/
public class ScopeDump
{
    // #############################################################################################
    // protected fields
    // #############################################################################################

        /** The target to write to */
        protected AString                 target;

        /** String to identify global keys. */
        protected String                  noKeyHashKey;

        /** The maximum length of a key. Adjusts (increases) over lifecycle. */
        protected int                     maxKeyLength;

        /** Temporary, reused string */
        protected AString                 tempAS                                    = new AString();

        /** Temporary, reused string */
        protected AString                 key                                       = new AString();

        /** User-defined threads names. */
        protected HashMap<Long, String>   threadDictionary;

    // #############################################################################################
    // public interface
    // #############################################################################################

        /** ****************************************************************************************
         * Constructor
         * @param threadDictionary User-defined threads names.
         * @param noKeyHashKey     String to identify global keys.
         * @param target           Target string to write to.
         * @param maxKeyLength     The start value for the maximum length of a key.
         ******************************************************************************************/
        public ScopeDump( HashMap<Long, String> threadDictionary, String noKeyHashKey,
                          AString target, int maxKeyLength )
        {
            this.threadDictionary=  threadDictionary;
            this.noKeyHashKey=      noKeyHashKey;
            this.target=            target;
            this.maxKeyLength=      maxKeyLength;
        }

        /** ****************************************************************************************
         * Constructor
         * @param threadDictionary User-defined threads names.
         * @param target        Target string to write to.
         * @param noKeyHashKey  String to identify global keys.
         ******************************************************************************************/
        public ScopeDump( HashMap<Long, String> threadDictionary, String noKeyHashKey,
                          AString target )
        {
            this.threadDictionary=  threadDictionary;
            this.target=            target;
            this.noKeyHashKey=      noKeyHashKey;
            this.maxKeyLength=      10;
        }


        /** ****************************************************************************************
         * Writes hash tables stored in a ScopeStore. Keys are AStrings.
         * Value types currently supported are LogData and int (in C# different method).
         * @param store The store to use.
         * @return The total number of hash table entries written.
         ******************************************************************************************/
        public int writeMap( ScopeStore<?> store)
        {
            // for some reason the compiler does not accept the following type as a parameter, so
            // we have to cast
            @SuppressWarnings({"unchecked"})
            ScopeStore<HashMap<AString, ?>> storeC=  ( ScopeStore<HashMap<AString, ?>> ) store;

            boolean firstEntry= true;
            int cnt= 0;
            if ( storeC.globalStore != null && storeC.globalStore.size() > 0)
            {
                cnt+= storeC.globalStore.size();
                if( firstEntry ) firstEntry= false; else   target.newLine();
                target._NC( "  Scope.GLOBAL:" ).newLine();
                maxKeyLength= writeMap( storeC.globalStore, "    " );
            }

            for( Map.Entry<Thread, ArrayList<HashMap<AString, ?>>> thread : storeC.threadOuterStore.entrySet() )
            {
                if ( thread.getValue().size() == 0 )
                    continue;
                ALIB.ASSERT( thread.getValue().size() == 1 );
                if( firstEntry ) firstEntry= false; else   target.newLine();
                target._NC("  Scope.THREAD_OUTER ");  storeThreadToScope( thread.getKey() )._( ':' ).newLine();
                cnt+= thread.getValue().get( 0 ).size();
                maxKeyLength= writeMap( thread.getValue().get( 0 ), "    " );
            }

            for( PathMap<HashMap<AString, ?>> map : storeC.languageStore )
            {
                if( firstEntry ) firstEntry= false; else   target.newLine();
                target._NC( "  " );
                storeKeyToScope( map )      ._( ':' ).newLine();
                cnt+= map.value.size();
                maxKeyLength= writeMap( map.value, "    " );
            }

            for( Map.Entry<Thread, ArrayList<HashMap<AString, ?>>> thread : storeC.threadInnerStore.entrySet() )
            {
                if ( thread.getValue().size() == 0 )
                    continue;
                ALIB.ASSERT( thread.getValue().size() == 1 );
                if( firstEntry ) firstEntry= false; else   target.newLine();
                target._NC("  Scope.THREAD_INNER ");  storeThreadToScope( thread.getKey() )._( ':' ).newLine();
                cnt+= thread.getValue().get( 0 ).size();
                maxKeyLength= writeMap( thread.getValue().get( 0 ), "    " );
            }

            return cnt;
        }

        /** ****************************************************************************************
         * Writes the contents of the ScopeStore used for <em>Scope Domains</em>
         * @param store         The store to use
         * @param indentSpaces  The number of spaces to add at the beginning of each line.
         * @return The total number of <em>Scope Domains</em> written.
         ******************************************************************************************/
        public int writeDomains( ScopeStore<AString> store, int indentSpaces)
        {
            int cnt= 0;

            if ( store.globalStore != null )
            {
                cnt++;
                target.insertChars( ' ', indentSpaces );
                target._NC( store.globalStore );
                target.tab( 25, -1 )._NC( "Scope.GLOBAL " ).newLine();
            }

            for( Map.Entry<Thread, ArrayList<AString>> thread : store.threadOuterStore.entrySet() )
                for ( AString it : thread.getValue() )
                {
                    cnt++;
                    target.insertChars( ' ', indentSpaces );
                    target._NC( it );
                    target.tab( 25, -1 )
                          ._NC( "Scope.THREAD_OUTER " );
                    storeThreadToScope( thread.getKey() ).newLine();
                }

            for( PathMap<AString> it : store.languageStore )
            {
                cnt++;

                target.insertChars( ' ', indentSpaces );
                target._NC( it.value );
                target.tab( 25, -1 );

                storeKeyToScope( it ).newLine();
            }

            for( Map.Entry<Thread, ArrayList<AString>> thread : store.threadInnerStore.entrySet() )
                for ( AString it : thread.getValue() )
                {
                    cnt++;
                    target.insertChars( ' ', indentSpaces );
                    target._NC( it );
                    target.tab( 25, -1 )
                          ._NC( "Scope.THREAD_INNER " );
                    storeThreadToScope( thread.getKey() ).newLine();
                }

            return cnt;
        }


        /** ****************************************************************************************
         * Writes the contents of the ScopeStore used for <em>Prefix Logables</em>
         * @param store         The store to use
         * @param indentSpaces  The number of spaces to add at the beginning of each line.
         * @return The total number of <em>Prefix Logables</em> written.
         ******************************************************************************************/
        public int writePrefixes( ScopeStore<Object> store, int indentSpaces )
        {
            int cnt= 0;

            if ( store.globalStore != null )
            {
                cnt++;
                target.insertChars( ' ', indentSpaces );
                target._( '\"' )._NC( store.globalStore.toString() )._( '\"' );
                target.tab( 25, -1 )._NC( "Scope.Global " ).newLine();
            }

            for( Map.Entry<Thread, ArrayList<Object>> thread : store.threadOuterStore.entrySet() )
                for ( Object it : thread.getValue() )
                {
                    cnt++;
                    target.insertChars( ' ', indentSpaces );
                    target._( '\"' )._NC( it.toString() )._( '\"' );
                    target.tab( 25, -1 )
                          ._NC( "Scope.THREAD_OUTER " );
                    storeThreadToScope( thread.getKey() ).newLine();
                }

            for( PathMap<Object> it : store.languageStore )
            {
                cnt++;

                target.insertChars( ' ', indentSpaces );
                target._( '\"' )._NC( it.value.toString() )._( '\"' );
                target.tab( 25, -1 );

                storeKeyToScope( it ).newLine();
            }

            for( Map.Entry<Thread, ArrayList<Object>> thread : store.threadInnerStore.entrySet() )
                for ( Object it : thread.getValue() )
                {
                    cnt++;
                    target.insertChars( ' ', indentSpaces );
                    target._( '\"' )._NC( it.toString() )._( '\"' );
                    target.tab( 25, -1 )
                          ._NC( "Scope.THREAD_INNER " );
                    storeThreadToScope( thread.getKey() ).newLine();
                }

            return cnt;
        }

    // #############################################################################################
    // Internals
    // #############################################################################################

        /** ****************************************************************************************
         * Helper method to write thread information.
         * @param thread  The thread in question
         * @return The target to allow concatenated calls.
         ******************************************************************************************/
        protected AString storeThreadToScope( Thread thread  )
        {
            long id= thread.getId();
            String threadName= threadDictionary.get( new Long( id ) );
            if ( threadName != null )
                return target._("[Thread=\"")._(threadName)._("\"]");
                
            return target._("[ThreadID=")._(id)._(']');
        }

        /** ****************************************************************************************
         * Helper method to write a ScopeStores' source related scope key as scope information.
         * @param map  The PathMap node to get scope information for.
         * @return The target to allow concatenated calls.
         ******************************************************************************************/
        protected AString storeKeyToScope( PathMap<?> map  )
        {
            key._();
            PathMap<?> node= map;
            while( node != null )
            {
                key.insertAt( node.path, 0 );
                node= node.parent;
            }

            int classNameStart= 0;
            int classNameEnd= key.indexOf('#');
            if (classNameEnd > 0 )
                classNameStart= key.lastIndexOf( '.', classNameEnd ) + 1;
            int methodEnd=    classNameEnd >= 0 ? key.indexOf('#', classNameEnd + 1)  : -1;

            target._NC("Scope.");
                 if ( methodEnd   >= 0 )   target._NC( "METHOD       [" );
            else if ( classNameEnd >= 0 )  target._NC( "CLASS        [" );
            else                           target._NC( "PACKAGE      [" );

            int targetStart= target.length();
            target._NC( key );

            if ( classNameEnd >= 0 )
                target.deleteEnd(1);

            if ( methodEnd >= 0 )
            {
                target._NC( "()\"" );
                target.replaceSubstring( " METHOD=\"", targetStart + classNameEnd, 2 );
            }

            if ( classNameEnd >= 0 )
            {
                target.insertAt        ( "\""           , targetStart + classNameEnd      );
                target.replaceSubstring( " CLASS=\""    , targetStart + classNameStart, 1 );
            }

            int pos= classNameEnd > 0 ? classNameStart : target.length() - targetStart;
            target.setCharAt( targetStart + pos -1, '\"' );
            target.insertAt ( "PACKAGE=\"", targetStart );

            target._(']');

            return target;
        }

        /** ****************************************************************************************
         * Helper method.
         * @param map       The map to use.
         * @param prefix    A prefix string for each line.
         * @return The number of objects written.
         ******************************************************************************************/
        int writeMap( HashMap<AString, ?> map, String prefix )
        {
            for(Map.Entry<AString,?> it : map.entrySet() )
            {
                target._NC( prefix );

                tempAS._();

                if ( it.getKey().equals( noKeyHashKey ) )
                    tempAS._NC( "<global>" );
                else
                    tempAS._NC( "\"" )._( it.getKey() )._( '\"' );
                if ( maxKeyLength < tempAS.length() + 1 )
                    maxKeyLength= tempAS.length() + 1;

                target.field()._( tempAS).field( maxKeyLength, Alignment.LEFT )._( '=' );
                Object o= it.getValue();
                if (o instanceof int[])
                    target._( ((int[]) o)[0] );
                else
                    ((LogData)o).toString( target );


                target.newLine();
            }
            return maxKeyLength;
        }


} // class ScopeDump
