// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined(HPP_ALIB_STRINGS_SUBSTRING)
    #include "alib/strings/substring.hpp"
#endif
#if !defined(HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif

#if ALIB_DEBUG
    #include "alib/strings/util/stringtuples.hpp"
    #include <algorithm>
#endif


namespace aworx { namespace lib { namespace boxing {


// #################################################################################################
// Boxing
// #################################################################################################

#if ALIB_DEBUG && ALIB_MODULE_BOXING

} // aworx::lib[::boxing]
namespace debug {


Boxing::Boxing( bool removeALibNamespaces ) : removeNamespaces( removeALibNamespaces )
{
    strings= new Strings();
}

Boxing::~Boxing()
{
    delete strings;
}


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
    return GetTypeName( box.DbgGetBoxerType() );
}

//! @cond NO_DOX

void Boxing::typesToStrings(const std::vector<const std::type_info *> &list)
{
    strings->Clear();
    for( auto& type : list )
    {
        GetTypeName(*type);
        aworx::lib::debug::RemoveALibNamespaces( target, removeNamespaces );
        strings->Add( target );
    }
    std::sort( strings->begin(), strings->end(),
               [] (Strings::ElementType & a, Strings::ElementType& b )
               {
                    return std::get<0>(a).CompareTo( std::get<0>(b), Case::Ignore  ) < 0;
               }
             );
}
//! @endcond NO_DOX


Strings& Boxing::GetInterfaces( const Box& box     ) { typesToStrings( lib::boxing::Boxer::DbgGetInterfaces(box.DbgGetBoxerType()) ); return *strings; }
Strings& Boxing::GetKnownBoxTypes                 () { typesToStrings( lib::boxing::Boxer::DbgGetKnownBoxers       ()              ); return *strings; }
Strings& Boxing::GetKnownInterfaces               () { typesToStrings( lib::boxing::Boxer::DbgGetKnownInterfaces   ()              ); return *strings; }
Strings& Boxing::GetKnownInterfaceDefaults        () { typesToStrings( lib::boxing::Boxer::DbgGetDefaultInterfaces ()              ); return *strings; }
Strings& Boxing::GetKnownInterfaceImplementations () { typesToStrings( lib::boxing::Boxer::DbgGetKnownInterfaceImpl()              ); return *strings; }

//! @cond NO_DOX
void  Boxing::dumpHelper(const std::vector<const std::type_info *> &list, const String &headline, const String &indent )
{
    typesToStrings(list);

    if ( headline.IsNotNull() )
    {
        dump << headline << NewLine;
        dump.InsertChars('-', 80) << NewLine;
    }

    for( Strings::ElementType& name : *strings )
        dump << indent << std::get<0>(name) << NewLine;
    dump << NewLine;
}
//! @endcond NO_DOX

AString&  Boxing::Dump()
{
    dump.Clear();

    // Get boxers and add names to string array
    std::vector<const std::type_info*>    boxers= lib::boxing::Boxer::DbgGetKnownBoxers();
    StringTuples<const std::type_info*> boxerNames;

    for( auto& type : boxers )
    {
        GetTypeName(*type);
        debug::RemoveALibNamespaces( target, removeNamespaces );
        boxerNames.Add( target, type );
    }
    std::sort( boxerNames.begin(), boxerNames.end(),
               []   ( StringTuples<const std::type_info*>::ElementType & a,
                      StringTuples<const std::type_info*>::ElementType & b )
               {
                    return std::get<0>(a).CompareTo( std::get<0>(b), Case::Ignore  ) < 0;
               }
            );

    // dump boxers and their interfaces
    dump << "ALib Boxing: Boxed Types and Associated Interfaces:"  << NewLine;
    dump.InsertChars('-', 80) << NewLine;
    for( auto& boxer: boxerNames )
    {
        dump << "  " << std::get<0>(boxer) << NewLine;
        dumpHelper(lib::boxing::Boxer::DbgGetInterfaces(*std::get<1>(boxer)), nullptr, "    " );
    }

    // interface information
    dumpHelper(lib::boxing::Boxer::DbgGetKnownInterfaces(),    "ALib Boxing: Interfaces (all known):"   , "  ");
    dumpHelper(lib::boxing::Boxer::DbgGetDefaultInterfaces(),  "ALib Boxing: Default Interfaces:"       , "  ");
    dumpHelper(lib::boxing::Boxer::DbgGetKnownInterfaceImpl(), "ALib Boxing: Interface Implementations:", "  ");
    return dump;
}


#endif

} // namespace aworx::lib [::debug]


namespace strings {


/**
 * This namespace provides a customization of <b>ALib %Boxing</b> for <b>ALib Strings</b>.
 * This means, on the one hand that code in this namespace specifies how objects found in parent
 * namespace #aworx::lib::strings are boxed and on the other hand introduces box-interfaces
 * related to strings.
 *
 * \attention
 *   In this documentation, you will find specializations of templated namespace functions of
 *   namespace \c aworx::lib::boxing. This is of-course wrong in respect to the C++ language
 *   definition, which requires such specializations to be placed in the original namespace.<br>
 *   It was decided to 'trick' the [documentation parser](http://www.stack.nl/~dimitri/doxygen) to
 *   show these specialization in this namespace, to keep namespace \b %boxing
 *   clean and to have all specializations related to this namespace in one place.
 */
namespace boxing
{
ALIB_NAMESPACE_INIT_FLAG
void Init()
{
    ALIB_NAMESPACE_INIT_DEDUP

    // set boxer interfaces of type IApply
    aworx::lib::boxing::DefineDefaultInterface<IApply>();

//! [DOX_ALIB_BOXING_SAMPLE_TEMPLATED_INTERFACE]
    aworx::lib::boxing::DefineInterface<bool      , false, IApply_TApplicable<bool      >>();
    aworx::lib::boxing::DefineInterface<char      , false, IApply_TApplicable<char      >>();
    aworx::lib::boxing::DefineInterface<wchar_t   , false, IApply_TApplicable<wchar_t   >>();
    aworx::lib::boxing::DefineInterface<char16_t  , false, IApply_TApplicable<char16_t  >>();
    aworx::lib::boxing::DefineInterface<char32_t  , false, IApply_TApplicable<char32_t  >>();
    aworx::lib::boxing::DefineInterface<boxed_int , false, IApply_TApplicable<boxed_int >>();
    aworx::lib::boxing::DefineInterface<boxed_uint, false, IApply_TApplicable<boxed_uint>>();
    aworx::lib::boxing::DefineInterface<double    , false, IApply_TApplicable<double    >>();
//! [DOX_ALIB_BOXING_SAMPLE_TEMPLATED_INTERFACE]

    aworx::lib::boxing::DefineInterface<char      , true , IApply_TcharArr    >();
    aworx::lib::boxing::DefineInterface<wchar_t   , true , IApply_Twchar_tArr >();
    aworx::lib::boxing::DefineInterface<char16_t  , true , IApply_Tchar16_tArr>();
    aworx::lib::boxing::DefineInterface<char32_t  , true , IApply_Tchar32_tArr>();
    aworx::lib::boxing::DefineInterface<BoxedAs<AString>  , false , IApply_BoxedAs_TApplicable<AString>>();
}



void IApply::Invoke( const Box& box, AString& target)
{
    #if ALIB_DEBUG
        target._( lib::debug::Boxing().GetType(box) );
    #else
        target._( "Unknown" );
    #endif

    target._('(')._( NumberFormat::Computational.HexLiteralPrefix)._( Format::Hex(static_cast<uint64_t >( box.UnboxRaw())) )._(')');
}

}// namespace boxing


}}}// namespace aworx::lib::strings

