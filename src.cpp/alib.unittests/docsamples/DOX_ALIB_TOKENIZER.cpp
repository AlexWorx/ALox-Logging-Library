// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"

#include "alib/strings/util/tokenizer.hpp"
#include "alib/compatibility/std_string.hpp"
#include "alib/compatibility/std_iostream.hpp"

#define TESTCLASSNAME       CPP_ALib_Dox_Tokenizer
#include "alib.unittests/aworx_unittests.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

namespace ut_aworx {

UT_CLASS()

//##################################################################################################
// SAMPLE code of class documentation
//##################################################################################################

void documentationSampleTokenizer(AWorxUnitTesting& ut)
{
    stringstream testOutputStream;
    #define cout testOutputStream

//! [DOX_ALIB_TOKENIZER]
    // data string to tokenize
    aworx::String data=  "test;  abc ; 1,2 , 3 ; xyz ; including;separator";

    // create tokenizer on data with ';' as delimiter
    aworx::Tokenizer tknzr( data, ';' );

    // read tokens
    cout << tknzr.Next() << endl; // will print "test"
    cout << tknzr.Next() << endl; // will print "abc"
    cout << tknzr.Next() << endl; // will print "1,2 , 3"

    // tokenize actual (third) token (nested tokenizer)
    aworx::Tokenizer subTknzr( tknzr.Actual,  ',');
    cout << subTknzr.Next();

    while( subTknzr.HasNext() )
        cout << '~' << subTknzr.Next();

    cout << endl;

    // continue with the main tokenizer
    cout << tknzr.Next() << endl; // will print "xyz"

    // grab the rest, as we know that the last token might include our separator character
    cout << tknzr.GetRest()      << endl; // will print "including;separator"
//! [DOX_ALIB_TOKENIZER]

    #undef cout
    ut.WriteResultFile( "DOX_ALIB_TOKENIZER.txt", testOutputStream.str(), "//! [OUTPUT]" );
}


UT_METHOD( DOX_ALIB_TOKEN )
{
    UT_INIT();

    UT_PRINT("*** Documentation Sample +**")
    documentationSampleTokenizer( ut );
}

UT_CLASS_END

} //namespace
