// #####################################################################oggeg############################
//  com.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

import com.aworx.lib.*;
import com.aworx.lib.lang.*;
import com.aworx.lib.util.StringTree;
import com.aworx.lib.lang.Alignment;
import com.aworx.lib.strings.AString;
import com.aworx.lox.ESC;

/** ************************************************************************************************
 * This class is an internal helper to export current scope values.
 * It was extracted from class \b %Lox to keep that class clean from this somehow 'cluttered' code.
 *
 * The current purpose of this class is to write information into an AString buffer. This is used
 * by method \ref com.aworx.lox.Lox.state "Lox.state". In the future, other export formats,
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
                ALIB_DBG.ASSERT( thread.getValue().size() == 1 );
                if( firstEntry ) firstEntry= false; else   target.newLine();
                target._NC("  Scope.THREAD_OUTER ");  storeThreadToScope( thread.getKey() )._( ':' ).newLine();
                cnt+= thread.getValue().get( 0 ).size();
                maxKeyLength= writeMap( thread.getValue().get( 0 ), "    " );
            }

            StringTree<HashMap<AString, ?>>.Walker walker= storeC.languageStore.new Walker();
            walker.pathGeneration( Switch.ON );
            walker.setRecursionDepth(-1);
            for( walker.setStart() ;walker.isValid() ; walker.next() )
            {
                HashMap<AString, ?> map= walker.value();
                if( map == null )
                    continue;
                if( firstEntry ) firstEntry= false; else   target.newLine();
                target._NC( "  " );
                storeKeyToScope(  walker.getPath(tempAS) ).newLine();
                cnt+= map.size();
                maxKeyLength= writeMap( map, "    " );
            }

            for( Map.Entry<Thread, ArrayList<HashMap<AString, ?>>> thread : storeC.threadInnerStore.entrySet() )
            {
                if ( thread.getValue().size() == 0 )
                    continue;
                ALIB_DBG.ASSERT( thread.getValue().size() == 1 );
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

            StringTree<AString>.Walker walker= store.languageStore.new Walker();
            walker.pathGeneration( Switch.ON );
            walker.setRecursionDepth(-1);
            for( walker.setStart() ;walker.isValid() ; walker.next() )
            {
                if( walker.value() == null )
                    continue;
                cnt++;

                target.insertChars( ' ', indentSpaces );
                target._NC( walker.value() );
                target.tab( 25, -1 );

                storeKeyToScope(  walker.getPath(tempAS) ).newLine();
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
                target._( '\"' );
                int idx= target.length();
                target._NC( store.globalStore.toString() );
                ESC.replaceToReadable( target, idx );
                target._( '\"' );

                target.tab( 25, -1 )._NC( "Scope.Global " ).newLine();
            }

            for( Map.Entry<Thread, ArrayList<Object>> thread : store.threadOuterStore.entrySet() )
                for ( Object it : thread.getValue() )
                {
                    cnt++;
                    target.insertChars( ' ', indentSpaces );
                    target._( '\"' );
                    int idx= target.length();
                    target._NC( it.toString() );
                    ESC.replaceToReadable( target, idx );
                    target._( '\"' );
                    target.tab( 25, -1 )
                          ._NC( "Scope.THREAD_OUTER " );
                    storeThreadToScope( thread.getKey() ).newLine();
                }

            StringTree<Object>.Walker walker= store.languageStore.new Walker();
            walker.pathGeneration( Switch.ON );
            walker.setRecursionDepth(-1);
            for( walker.setStart() ;walker.isValid() ; walker.next() )
            {
                if( walker.value() == null )
                    continue;
                cnt++;

                target.insertChars( ' ', indentSpaces );
                    target._( '\"' );
                    int idx= target.length();
                    target._NC( walker.value().toString() );
                    ESC.replaceToReadable( target, idx );
                    target._( '\"' );
                target.tab( 25, -1 );

                storeKeyToScope(  walker.getPath(tempAS) ).newLine();
            }

            for( Map.Entry<Thread, ArrayList<Object>> thread : store.threadInnerStore.entrySet() )
                for ( Object it : thread.getValue() )
                {
                    cnt++;
                    target.insertChars( ' ', indentSpaces );
                    target._( '\"' );
                    int idx= target.length();
                    target._NC( it.toString() );
                    ESC.replaceToReadable( target, idx );
                    target._( '\"' );
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
         * @param key  The key of the StringTree that is to be "translated".
         * @return The target to allow concatenated calls.
         ******************************************************************************************/
        protected AString storeKeyToScope( AString key  )
        {
            int oldStart= target.length();
            int fileNameEnd= key.indexOf('#');
            int methodEnd=    fileNameEnd >= 0 ? key.indexOf('#', fileNameEnd + 1)  : -1;

            target._NC("Scope.");
                 if ( methodEnd   >= 0 )  target._NC( "Method       [" );
            else if ( fileNameEnd >= 0 )  target._NC( "CLASS        [" );
            else                          target._NC( "PACKAGE      [" );

            int targetStart= target.length();
            target._NC( key );
            target.searchAndReplace( '/', '.', oldStart );

            if ( methodEnd >= 0 )
            {
                target.replaceSubstring( " @", targetStart + fileNameEnd +1, 2 ); // characters: "/#"
                target._NC( "()" );
            }

            if ( fileNameEnd >= 0 )
                target.replaceSubstring("", targetStart + fileNameEnd,  1);

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
                    target._( o );


                target.newLine();
            }
            return maxKeyLength;
        }


} // class ScopeDump
