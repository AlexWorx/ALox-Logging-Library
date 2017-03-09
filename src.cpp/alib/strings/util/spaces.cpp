// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alib/alib.hpp"

#include "alib/strings/util/spaces.hpp"
#include "alib/threads/threadlocknr.hpp"

#include <iostream>


namespace aworx { namespace lib { namespace strings { namespace util  {

// #################################################################################################
// static objects
// #################################################################################################
AString Spaces::theSpaces;

// #################################################################################################
// Interface
// #################################################################################################
const aworx::AString&  Spaces::GetUnsafe( integer minSize )
{
    integer spacesLength= Spaces::theSpaces.Length();
    if ( spacesLength < minSize )
        Spaces::theSpaces.InsertChars( ' ', minSize - spacesLength );

    return theSpaces;
}
void Spaces::Write( std::ostream& os, integer qty )
{
    const AString& spaces= Spaces::Get();
    integer spacesLength= spaces.Length();
    while ( qty > 0 )
    {
        integer size= qty < spacesLength ? qty : spacesLength;
        os.write( spaces.Buffer(), size );
        qty-= size;
    }
}


}}}} // namespace [aworx::lib::strings::util]

