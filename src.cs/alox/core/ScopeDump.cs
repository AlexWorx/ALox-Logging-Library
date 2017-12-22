// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections.Generic;
using cs.aworx.lib;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;
using System.IO;
using System.Threading;
using cs.aworx.lib.util;

namespace cs.aworx.lox.core {
/** ************************************************************************************************
 * This class is an internal helper to export current scope values.
 * It was extracted from class \b %Lox to keep that class clean from this somehow 'cluttered' code.
 *
 * The current purpose of this class is to write information into an AString buffer. This is used
 * by method \ref cs.aworx.lox.Lox.State "Lox.State". In the future, other export formats,
 * like JSON might be implemented here.
 *
 * \note As this is a pure internal helper class. Documentation may be limited.
 **************************************************************************************************/
#if ALOX_DBG_LOG || ALOX_REL_LOG

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
        protected Dictionary<int, String> threadDictionary;

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
        public ScopeDump( Dictionary<int, String> threadDictionary, String noKeyHashKey, AString target, int maxKeyLength= 10 )
        {
            this.threadDictionary=  threadDictionary;
            this.target=            target;
            this.noKeyHashKey=      noKeyHashKey;
            this.maxKeyLength=      maxKeyLength;
        }

        /** ****************************************************************************************
         * Writes hash tables stored in a ScopeStore. Keys are AStrings.
         * Value types currently supported are Object and int (in C# different method).
         * @param store The store to use.
         * @return The total number of hash table entries written.
         ******************************************************************************************/
        public int writeStoreMap<T>( ScopeStore<Dictionary<AString, T>> store )
        {
            bool firstEntry= true;
            int cnt= 0;
            if ( store.globalStore != null && store.globalStore.Count > 0)
            {
                cnt+= store.globalStore.Count;
                if( firstEntry ) firstEntry= false; else   target.NewLine();
                target._NC( "  Scope.Global:" ).NewLine();
                maxKeyLength= writeStoreMapHelper( store.globalStore, "    " );
            }

            foreach( KeyValuePair<Thread, List<Dictionary<AString, T>>> thread in store.threadOuterStore )
            {
                if ( thread.Value.Count == 0 )
                    continue;
                ALIB_DBG.ASSERT( thread.Value.Count == 1 );
                if( firstEntry ) firstEntry= false; else   target.NewLine();
                target._NC("  Scope.ThreadOuter ");  storeThreadToScope( thread.Key )._( ':' ).NewLine();
                cnt+= thread.Value[0].Count;
                maxKeyLength= writeStoreMapHelper( thread.Value[0], "    " );
            }

            var walker= new StringTree<Dictionary<AString, T>>.Walker( store.languageStore );
            walker.PathGeneration( Switch.On );
            walker.SetRecursionDepth(-1);
            for( walker.SetStart( store.languageStore) ;walker.IsValid() ; walker.Next() )
            {
                Dictionary<AString, T> map = walker.Value();
                if (map == null)
                    continue;
                cnt+= map.Count;
                if( firstEntry ) firstEntry= false; else   target.NewLine();
                target._NC( "  " );
                storeKeyToScope( walker.GetPath(tempAS) ).NewLine();
                maxKeyLength= writeStoreMapHelper( map, "    " );
            }

            foreach( KeyValuePair<Thread, List<Dictionary<AString, T>>> thread in store.threadInnerStore )
            {
                if ( thread.Value.Count == 0 )
                    continue;
                ALIB_DBG.ASSERT( thread.Value.Count == 1 );
                if( firstEntry ) firstEntry= false; else   target.NewLine();
                target._NC("  Scope.ThreadInner ");  storeThreadToScope( thread.Key )._( ':' ).NewLine();
                cnt+= thread.Value[0].Count;
                maxKeyLength= writeStoreMapHelper( thread.Value[0], "    " );
            }

            return cnt;
        }

        /** ****************************************************************************************
         * Writes the contents of the ScopeStore used for <em>Scope Domains</em>
         * @param store         The store to use
         * @param indentSpaces  The number of spaces to add at the beginning of each line.
         * @return The total number of <em>Scope Domains</em> written.
         ******************************************************************************************/
        public int writeScopeDomains( ScopeStore<AString> store, int indentSpaces )
        {
            int cntScopeDomains= 0;

            if ( store.globalStore != null )
            {
                cntScopeDomains++;
                target.InsertChars( ' ', indentSpaces );
                target._NC( store.globalStore );
                target.Tab( 25, -1 )._NC( "Scope.Global " ).NewLine();
            }

            foreach( KeyValuePair<Thread, List<AString>> thread in store.threadOuterStore )
                foreach ( AString it in thread.Value )
                {
                    cntScopeDomains++;
                    target.InsertChars( ' ', indentSpaces );
                    target._NC( it );
                    target.Tab( 25, -1 )
                          ._NC( "Scope.ThreadOuter " );
                    storeThreadToScope( thread.Key ).NewLine();
                }

            var walker= new StringTree<AString>.Walker( store.languageStore );
            walker.PathGeneration( Switch.On );
            walker.SetRecursionDepth(-1);
            for( walker.SetStart( store.languageStore) ;walker.IsValid() ; walker.Next() )
            {
                if( walker.Value() == null )
                    continue;
                cntScopeDomains++;

                target.InsertChars( ' ', indentSpaces );
                target._NC( walker.Value() );
                target.Tab( 25, -1 );

                storeKeyToScope( walker.GetPath(tempAS) ).NewLine();
            }

            foreach( KeyValuePair<Thread, List<AString>> thread in store.threadInnerStore )
                foreach ( AString it in thread.Value )
                {
                    cntScopeDomains++;
                    target.InsertChars( ' ', indentSpaces );
                    target._NC( it );
                    target.Tab( 25, -1 )
                          ._NC( "Scope.ThreadInner " );
                    storeThreadToScope( thread.Key ).NewLine();
                }

            return cntScopeDomains;
        }

        /** ****************************************************************************************
         * Writes the contents of the ScopeStore used for <em>Prefix Logables</em>
         * @param store         The store to use
         * @param indentSpaces  The number of spaces to add at the beginning of each line.
         * @return The total number of <em>Prefix Logables</em> written.
         ******************************************************************************************/
        public int writeScopePrefixes( ScopeStore<Object> store, int indentSpaces )
        {
            int cntScopeDomains= 0;

            if ( store.globalStore != null )
            {
                cntScopeDomains++;
                target.InsertChars( ' ', indentSpaces );
                target._( '\"' );
                int idx= target.Length();
                target._NC( store.globalStore.ToString() );
                ESC.ReplaceToReadable( target, idx );
                target._( '\"' );

                target.Tab( 25, -1 )._NC( "Scope.Global " ).NewLine();
            }

            foreach( KeyValuePair<Thread, List<Object>> thread in store.threadOuterStore )
                foreach ( Object it in thread.Value )
                {
                    cntScopeDomains++;
                    target.InsertChars( ' ', indentSpaces );
                    target._( '\"' );
                    int idx= target.Length();
                    target._NC( it.ToString() );
                    ESC.ReplaceToReadable( target, idx );
                    target._( '\"' );
                    target.Tab( 25, -1 )
                          ._NC( "Scope.ThreadOuter " );
                    storeThreadToScope( thread.Key ).NewLine();
                }

            var walker= new StringTree<Object>.Walker( store.languageStore );
            walker.PathGeneration( Switch.On );
            walker.SetRecursionDepth(-1);
            for( walker.SetStart( store.languageStore) ;walker.IsValid() ; walker.Next() )
            {
                if( walker.Value() == null )
                    continue;
                cntScopeDomains++;

                target.InsertChars( ' ', indentSpaces );
                target._( '\"' );
                int idx= target.Length();
                target._NC( walker.Value().ToString() );
                ESC.ReplaceToReadable( target, idx );
                target._( '\"' );
                target.Tab( 25, -1 );

                storeKeyToScope( walker.GetPath(tempAS) ).NewLine();
            }

            foreach( KeyValuePair<Thread, List<Object>> thread in store.threadInnerStore )
                foreach ( Object it in thread.Value )
                {
                    cntScopeDomains++;
                    target.InsertChars( ' ', indentSpaces );
                    target._( '\"' );
                    int idx= target.Length();
                    target._NC( it.ToString() );
                    ESC.ReplaceToReadable( target, idx );
                    target._( '\"' );
                    target.Tab( 25, -1 )
                          ._NC( "Scope.ThreadInner " );
                    storeThreadToScope( thread.Key ).NewLine();
                }

            return cntScopeDomains;
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
            int id= thread.ManagedThreadId;
            String threadName= null;
            threadDictionary.TryGetValue( id, out threadName );
            if ( threadName != null )
                return target._("[Thread=\"")._(threadName)._("\"]");
            return target._("[ThreadID=")._(id)._(']');
        }

        /** ****************************************************************************************
         * Helper method to write a ScopeStores' source related scope key as scope information.
         * @param key  The key of the StringTree that is to be "translated".
         * @return The target to allow concatenated calls.
         ******************************************************************************************/
        protected AString storeKeyToScope( AString  key  )
        {
            int fileNameEnd= key.IndexOf('#');
            int methodEnd=    fileNameEnd >= 0 ? key.IndexOf('#', fileNameEnd + 1)  : -1;

            target._NC("Scope.");
                 if ( methodEnd   >= 0 )  target._NC( "Method      [" );
            else if ( fileNameEnd >= 0 )  target._NC( "FileName    [" );
            else                          target._NC( "Path        [" );

            int targetStart= target.Length();
            target._NC( key );

            if ( methodEnd >= 0 )
            {
                target.ReplaceSubstring( " @", targetStart + fileNameEnd +1, 2 ); // characters: "/#"
                target._NC( "()" );
            }

            if ( fileNameEnd >= 0 )
                target.ReplaceSubstring(".*", targetStart + fileNameEnd,  1);
            else
                target._('/');

            target._(']');

            return target;
        }

        /** ****************************************************************************************
         * Helper method.
         * @param map       The map to use
         * @param prefix    A prefix string for each line
         * @return The number of objects written
         ******************************************************************************************/
        int writeStoreMapHelper<T>( Dictionary<AString, T> map, String prefix )
        {
            foreach(KeyValuePair<AString,T> it in map )
            {
                target._NC( prefix );

                tempAS._();

                if ( it.Key.Equals( noKeyHashKey ) )
                    tempAS._NC( "<global>" );
                else
                    tempAS._NC( "\"" )._( it.Key )._( '\"' );
                if ( maxKeyLength < tempAS.Length() + 1 )
                    maxKeyLength= tempAS.Length() + 1;

                target.Field()._( tempAS).Field( maxKeyLength, Alignment.Left )._( '=' );

                if ( map is Dictionary<AString, Object> )
                    target._((Object) it.Value);
                else
                    target._( ((int[]) (Object) it.Value)[0] );


                target.NewLine();
            }
            return maxKeyLength;

        }

} // class ScopeDump

#endif // ALOX_DBG_LOG || ALOX_REL_LOG ,started before class ScopeInfo


} // namespace
