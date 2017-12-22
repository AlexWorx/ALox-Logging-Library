// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if ALIB_DEBUG && ALIB_MODULE_BOXING

#if !defined(HPP_ALIB_STRINGS_SUBSTRING)
    #include "alib/strings/substring.hpp"
#endif
#if !defined(HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif

#if !defined(HPP_ALIB_STRINGS_BOXING_DEBUG)
    #include "alib/strings/boxing/debug.hpp"
#endif

#if ALIB_DEBUG
    #include "alib/strings/util/stringtuples.hpp"
    #include <algorithm>
#endif


namespace aworx { namespace lib { namespace debug {


// #################################################################################################
// Boxing
// #################################################################################################



AString&  Boxing::GetTypeName( const std::type_info &type )
{
    target._()._( type );
         if( target.StartsWith( "aworx::lib::boxing::BoxerT<"      ) )   target.DeleteStart( 27 ).DeleteEnd(1);
    else if( target.StartsWith( "aworx::lib::boxing::ArrayBoxerT<" ) )   target.DeleteStart( 32 ).DeleteEnd(1)._("[]");


    #if defined ( _MSC_VER )
        if( target.StartsWith( "class ") )
            target.DeleteStart(6);
    #endif

    return target;
}

AString&  Boxing::GetType( const Box& box )
{
    target._()._( box.GetTypeInfo() );
    if ( box.IsArray() )
        target._( "[]" );
    return target;
}

//! @cond NO_DOX

void Boxing::typesToStrings(const std::vector<const std::type_info *> &list)
{
    strings.clear();
    for( auto& type : list )
    {
        GetTypeName(*type);
        aworx::lib::debug::RemoveALibNamespaces( target, removeNamespaces );
        strings.emplace_back( target );
    }
    std::sort( strings.begin(), strings.end(),
               [] (String & a, String& b )
               {
                    return a.CompareTo<true, Case::Ignore>( b ) < 0;
               }
             );
}
//! @endcond


Boxing::StringVector& Boxing::GetInterfaces( const Box& box     ) { typesToStrings( BOXING.DbgGetInterfaces(box.DbgGetReferenceType()) ); return strings; }
Boxing::StringVector& Boxing::GetKnownBoxTypes                 () { typesToStrings( BOXING.DbgGetKnownBoxers       ()                  ); return strings; }
Boxing::StringVector& Boxing::GetKnownInterfaces               () { typesToStrings( BOXING.DbgGetKnownInterfaces   ()                  ); return strings; }
Boxing::StringVector& Boxing::GetKnownInterfaceDefaults        () { typesToStrings( BOXING.DbgGetDefaultInterfaces ()                  ); return strings; }
Boxing::StringVector& Boxing::GetKnownInterfaceImplementations () { typesToStrings( BOXING.DbgGetKnownInterfaceImpl()                  ); return strings; }

//! @cond NO_DOX
void  Boxing::dumpHelper(const std::vector<const std::type_info *> &list, const String &headline, const String &indent )
{
    typesToStrings(list);

    if ( headline.IsNotNull() )
    {
        dump << headline << NewLine;
        dump.InsertChars('-', 80) << NewLine;
    }

    for( String& name : strings )
        dump << indent << name << NewLine;
    dump << NewLine;
}
//! @endcond

AString&  Boxing::Dump()
{
    dump.Clear();

    // Get boxers and add names to string array
    std::vector<const std::type_info*>    boxers= BOXING.DbgGetKnownBoxers();
    StringTable<const std::type_info*>    boxerNames;

    for( auto& type : boxers )
    {
        GetTypeName(*type);
        debug::RemoveALibNamespaces( target, removeNamespaces );
        boxerNames.Add( target, type );
    }
    std::sort( boxerNames.begin(), boxerNames.end(),
               []   ( StringTable<const std::type_info*>::ElementType & a,
                      StringTable<const std::type_info*>::ElementType & b )
               {
                    return std::get<0>(a).CompareTo<true, Case::Ignore>( std::get<0>(b)  ) < 0;
               }
            );

    // dump boxers and their interfaces
    dump << "ALib Boxing: Boxed Types and Associated Interfaces:"  << NewLine;
    dump.InsertChars('-', 80) << NewLine;
    for( auto& boxer: boxerNames )
    {
        dump << "  " << std::get<0>(boxer) << NewLine;
        dumpHelper(BOXING.DbgGetInterfaces(*std::get<1>(boxer)), nullptr, "    " );
    }

    // interface information
    dumpHelper(BOXING.DbgGetKnownInterfaces(),    "ALib Boxing: Interfaces (all known):"   , "  ");
    dumpHelper(BOXING.DbgGetDefaultInterfaces(),  "ALib Boxing: Default Interfaces:"       , "  ");
    dumpHelper(BOXING.DbgGetKnownInterfaceImpl(), "ALib Boxing: Interface Implementations:", "  ");
    return dump;
}




}}}// namespace [aworx::lib::debug]

#endif // ALIB_DEBUG && ALIB_MODULE_BOXING


