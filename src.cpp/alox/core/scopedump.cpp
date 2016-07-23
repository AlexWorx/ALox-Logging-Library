// #################################################################################################
//  aworx::lox::core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "scopedump.hpp"

#if !defined(_GLIBCXX_IOSTREAM) && !defined(_IOSTREAM_)
    #include <iostream>
#endif

#if !defined (_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif

#include "alib/containers/pathmap.hpp"

// For code compatibility with ALox Java/C++
#define _NC _<false>



using namespace aworx;


namespace aworx {
        namespace lox {
                namespace core {

#if !defined( IS_DOXYGEN_PARSER )

// #################################################################################################
// template instantiations
// #################################################################################################
template   int ScopeDump::writeStore   ( ScopeStore<AString*>*                      store, int indentSpaces );
template   int ScopeDump::writeStore   ( ScopeStore<Logable*>*                      store, int indentSpaces );
template   int ScopeDump::writeStoreMap( ScopeStore<std::map<AString, int      >*>* store );
template   int ScopeDump::writeStoreMap( ScopeStore<std::map<AString, LogData* >*>* store );


// #################################################################################################
// local helper functions (non members)
// #################################################################################################
template<typename T> void write( T          val, AString& target ) {  val->ToString( target ); }
template<>           void write( int        val, AString& target ) {  target._(val);                 }
template<>           void write( AString*   val, AString& target ) {  target._(val);                 }


// #################################################################################################
// protected methods
// #################################################################################################
template<typename T>
AString& ScopeDump::storeKeyToScope( const lib::containers::PathMap<T>& map )
{
//target._();
    String512 key;
    const PathMap<T>* node= &map;
    while( node != nullptr )
    {
        key.InsertAt( node->Path, 0 );
        node= node->Parent;
    }

    int fileNameStart= 0;
    int fileNameEnd= key.IndexOf('#');
    if (fileNameEnd > 0 )
        fileNameStart= key.LastIndexOf( '/', fileNameEnd ) + 1;
    int methodEnd=    fileNameEnd >= 0 ? key.IndexOf('#', fileNameEnd + 1)  : -1;

    target._NC("Scope::");
         if ( methodEnd   >= 0 )  target._NC( "Method      [" );
    else if ( fileNameEnd >= 0 )  target._NC( "FileName    [" );
    else                          target._NC( "Path        [" );

    int targetStart= target.Length();
    target._NC( key );

    if ( fileNameEnd >= 0 )
        target.DeleteEnd(1);

    if ( methodEnd >= 0 )
    {
        target._NC( "()\"" );
        target.ReplaceSubstring( " Method=\"", targetStart + fileNameEnd, 2 );
    }

    if ( fileNameEnd >= 0 )
    {
        target.InsertAt        ( ".*\""            , targetStart + fileNameEnd      );
        target.ReplaceSubstring( " Filename=\""    , targetStart + fileNameStart, 1 );
    }

    int pos= fileNameEnd > 0 ? fileNameStart : target.Length() - targetStart;
    target.InsertAt( "\""     , targetStart + pos );
    target.InsertAt( "Path=\"", targetStart );

    target._(']');

    return target;
}

AString& ScopeDump::storeThreadToScope( int threadID )
{
    auto it= threadDictionary.find( threadID );
    if ( it != threadDictionary.end() )
        return target._("[Thread=\"")._( it->second )._("\"]");

    return target._("[ThreadID=")._( threadID )._(']');
}

template<typename T>
int ScopeDump::writeStoreMapHelper( std::map<AString, T>& map, const TString& prefix )
{
    for ( auto& it : map )
    {
        target._NC( prefix );

        String64 keyString;

        if ( it.first.Equals( noKeyHashKey ) )
            keyString._NC( "<global>" );
        else
            keyString._NC( "\"" )._( it.first )._( '\"' );
        if ( maxKeyLength < keyString.Length() + 1 )
            maxKeyLength= keyString.Length() + 1;

        target._NC(Format::Field(keyString, maxKeyLength, Alignment::Left))._NC( '=' );


        write( it.second, target);
        target.NewLine();
    }
    return maxKeyLength;
}

// #################################################################################################
// Interface
// #################################################################################################
template<typename T>
int ScopeDump::writeStoreMap( ScopeStore<T>* store )
{
    int cnt= 0;
    bool firstEntry= true;
    if ( store->globalStore && store->globalStore->size() > 0)
    {
        cnt+= (int) store->globalStore->size();
        if( firstEntry ) firstEntry= false; else   target.NewLine();
        target._NC( "  Scope::Global:" ).NewLine();
        maxKeyLength= writeStoreMapHelper( *store->globalStore, "    " );
    }

    for ( auto& thread : store->threadOuterStore )
    {
        if ( thread.second.size() == 0 )
            continue;
        ALIB_ASSERT( thread.second.size() == 1 );
        if( firstEntry ) firstEntry= false; else   target.NewLine();
        target._NC("  Scope::ThreadOuter ");  storeThreadToScope( thread.first )._( ':' ).NewLine();
        cnt+= (int) thread.second[0]->size();
        maxKeyLength= writeStoreMapHelper( *thread.second[0], "    " );
    }


    for ( auto& map : *store->languageStore )
    {
        cnt+= (int) map.Value->size();
        if( firstEntry ) firstEntry= false; else   target.NewLine();
        target._NC( "  " );
        storeKeyToScope   ( map )   ._( ':' ).NewLine();
        maxKeyLength= writeStoreMapHelper( *map.Value, "    " );
    }

    for ( auto& thread : store->threadInnerStore )
    {
        if ( thread.second.size() == 0 )
            continue;
        ALIB_ASSERT( thread.second.size() == 1 );
        if( firstEntry ) firstEntry= false; else   target.NewLine();
        target._NC("  Scope::ThreadInner ");  storeThreadToScope( thread.first )._( ':' ).NewLine();
        cnt+= (int) thread.second[0]->size();
        maxKeyLength= writeStoreMapHelper( *thread.second[0], "    " );
    }
    return cnt;
}

template<typename T>
int ScopeDump::writeStore( ScopeStore<T>* store, int indentSpaces )
{
    int cnt= 0;
    if ( store->globalStore )
    {
        cnt++;
        target.InsertChars( ' ', indentSpaces );
        write( store->globalStore, target );
        target._NC(Format::Tab( 25, -1 ) )._NC( "Scope::Global " ).NewLine();
    }

    for ( auto& thread : store->threadOuterStore )
        for ( auto& it : thread.second )
        {
            cnt++;
            target.InsertChars( ' ', indentSpaces );
            write(it, target);
            target._NC( Format::Tab( 25, -1 ) )
                  ._NC( "Scope::ThreadOuter " );
            storeThreadToScope( thread.first ).NewLine();
        }


    for ( auto& it : *store->languageStore )
    {
        cnt++;
        target.InsertChars( ' ', indentSpaces );

        write( it.Value, target );
        target._NC(Format::Tab( 25, -1 ) );

        storeKeyToScope( it ).NewLine();
    }

    for ( auto& thread : store->threadInnerStore )
        for ( auto& it : thread.second )
        {
            cnt++;
            target.InsertChars( ' ', indentSpaces );
            write(it, target);
            target._NC( Format::Tab( 25, -1 ) )
                  ._NC( "Scope::ThreadInner " );
            storeThreadToScope( thread.first ).NewLine();
        }
    return cnt;
}

#endif // IS_DOXYGEN_PARSER
}}} // namespace aworx::lox::core
