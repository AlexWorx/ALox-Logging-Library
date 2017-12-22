// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#include "alib/strings/util/spaces.hpp"

#include <iostream>


namespace aworx { namespace lib { namespace strings { namespace util  {


//! @cond NO_DOX
namespace
{
    AString      theSpaces;
}
//! @endcond

String  Spaces::Get()
{
    return theSpaces;
}

void    Spaces::Initialize( integer minSize )
{
    integer spacesLength= theSpaces.Length();
    if ( spacesLength < minSize )
        theSpaces.InsertChars( ' ', minSize - spacesLength );
}

void Spaces::Write( std::ostream& os, integer qty )
{
    auto spaces= Spaces::Get();
    while ( qty > 0 )
    {
        integer size= qty < spaces.Length() ? qty : spaces.Length();
        os.write( spaces.Buffer(), size );
        qty-= size;
    }
}


}}}} // namespace [aworx::lib::strings::util]

