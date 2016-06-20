// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"


#define TESTCLASSNAME       CPP_ALib__Dox

#include <iostream>
#include <sstream>


std::stringstream testOutputStream;
#define cout testOutputStream

//! [DOX_ALIB_ASTRING_FORMAT]
#include "alib/alib.hpp"

// get support for  ostream operator<<() on String objects
#include "alib/compatibility/std_iostream.hpp"
#include "alib/compatibility/std_string.hpp"

#include "alib/system/directory.hpp"

using namespace std;
using namespace aworx;

void PrintResult()
{
    const int result= 42; // this took a long time to calculate

    AString as;
    as <<  "The result is: " << Format::Tab(15) << Format::Field( String16(result), 8, Alignment::Center, '*' );
    cout << as << endl;
}

//! [DOX_ALIB_ASTRING_FORMAT]
#undef cout


//##################################################################################################
// SAMPLE code of class documentation
//##################################################################################################

void docmentationSample()
{
{
//! [DOX_ALIB_ASTRING_NULLED]
    // Default constructor does not allocate space, yet.
    // The instance is "nulled".
    AString aString;
    assert(  aString.IsNull()                 );
    assert(  aString.Equals( NullString )     );
    assert(  aString == nullptr );

    // Assign an empty string. Now the AString is not nullptr any more
    aString= "";
    assert(  aString.IsNotNull()              );
    assert( !aString.Equals   ( NullString )  );
    assert(  aString != nullptr );

    // Assign nullptr
    aString= nullptr;
    assert(  aString.IsNull()                 );
    assert(  aString.Equals   ( NullString )  );
    assert(  aString == nullptr );
//! [DOX_ALIB_ASTRING_NULLED]
}

{
//! [DOX_ALIB_ASTRING_MODIFY_CONST_BUFFER]
    const AString myAString( "Hello" );

    // this would not compile because ALib volunteers to not declare AString::SetCharAt()
    // to be a const method.
    //myAString.SetCharAt( 1, 'e' );

    myAString.VBuffer()[1]= 'e';
//! [DOX_ALIB_ASTRING_MODIFY_CONST_BUFFER]
}

}


#include "alib.unittests/aworx_unittests.hpp"


// Windows.h might bring in max/min macros
#if defined( max )
    #undef max
    #undef min
#endif

namespace ut_aworx {

UT_CLASS()


    UT_METHOD( DocumentationSample )
    {
        UT_INIT();

        UT_PRINT("*** Documentation Sample +**")
        docmentationSample();
        PrintResult();
        ut.WriteResultFile( "DOX_ALIB_ASTRING_FORMAT.txt", testOutputStream.str(), "//! [OUTPUT]" );

    }

UT_CLASS_END

}; //namespace
