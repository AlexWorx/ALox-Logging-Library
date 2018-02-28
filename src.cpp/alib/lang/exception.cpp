// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#if !defined (HPP_ALIB_STRINGS_FORMAT_FORMATTER)
    #include "alib/strings/format/formatter.hpp"
#endif

#if !defined (HPP_ALIB_LANG_EXCEPTION)
    #include "alib/lang/exception.hpp"
#endif


//! [DOX_ALIB_ENUM_META_DATA_SPECIFCATION_impl]
#if !defined (HPP_ALIB_LANG_RESOURCE_TUPLE_LOADER)
    #include "alib/lang/resourcedtupleloader.hpp"
#endif

ALIB_ENUM_SPECIFICATION_IMPL( aworx::lib::lang::Exception )
//! [DOX_ALIB_ENUM_META_DATA_SPECIFCATION_impl]

using namespace std;

namespace aworx { namespace lib {  namespace lang {

// #################################################################################################
// Exception
// #################################################################################################
Exception::~Exception()
{
    for( auto& entry : Entries )
        for( auto& box : entry.Args )
            if( box.IsType<BoxedAs<AString>>() )
                delete &box.Unbox<BoxedAs<AString>>().Get();
}


const Enum&   Exception::Code()
{
    auto it= Entries.end();
    while(--it > Entries.begin() )
        if( it->Code.Value() >= 0 )
            break;
    return it->Code;
}

void   Exception::copyStrings()
{
    for( auto& box : Entries.back().Args )
    {
        if( box.IsArrayOf<char>() )
            box= BoxedAs<AString>(* new AString( box.Unbox<String>() ));

        // TOWCHAR: when we have WAString, uncomment this line.
        // if( box.IsArrayOf<wchar_>() )
        //     box= BoxedAs<AStringW>(* new AStringW<wchar_t>( box.Unbox<String>() ));
    }
}

void   Exception::Describe( AString& target, Entry& entry )
{
    String formatString= entry.EnumLibrary.Get( std::get<2>(entry.ErrorMetaData)  );
    auto& fmt=
    aworx::Formatter::AcquireDefault( ALIB_SRCPOS_REL_EMPTY );
        fmt.Format( target, formatString, entry.Args );
    aworx::Formatter::ReleaseDefault();
}


}}}// namespace [aworx::lib::lang]
