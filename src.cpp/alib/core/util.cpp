// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALIB_ALIB)
    #include "alib/alib.hpp"
#endif

#include "alib/core/util.hpp"
#include "alib/threads/threadlock.hpp"

#include <iostream>


using namespace std;

namespace aworx {
namespace           lib {


// #################################################################################################
// static objects
// #################################################################################################
AString Util::theSpaces;

// #################################################################################################
// WriteSpaces
// #################################################################################################
const aworx::AString&  Util::GetSpaces( int minSize )
{
    int spacesLength= Util::theSpaces.Length();
    if ( spacesLength < minSize )
    {
        OWN( ALIB::Lock)

        // check it again, after having the lock
        spacesLength= Util::theSpaces.Length();
        if ( spacesLength < minSize )
            Util::theSpaces.InsertChars( ' ', minSize - spacesLength );
    }

    return theSpaces;
}

// #################################################################################################
// WriteSpaces
// #################################################################################################
void Util::WriteSpaces( std::ostream& os, int qty )
{
    const AString& spaces= Util::GetSpaces();
    int spacesLength= spaces.Length();
    while ( qty > 0 )
    {
        int size= qty < spacesLength ? qty : spacesLength;
        os.write( spaces.Buffer(), size );
        qty-= size;
    }
}


}}// namespace aworx::lib

