// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/strings/tokenizer.hpp"
#include "alib/compatibility/std_string.hpp"
#include "alib/compatibility/std_iostream.hpp"

#define TESTCLASSNAME       CPP_ALib__Dox
#include "aworx_unittests.hpp"

#include <iostream>
#include <iomanip>

using namespace std;

namespace ut_aworx {



UT_CLASS()

//##################################################################################################
// SAMPLE code of class documentation
//##################################################################################################

void documentationSampleTokenizer(ALIBUnitTesting& ut)
{
    stringstream testOutputStream;
    #define cout testOutputStream

//! [DOX_ALIB_TOKENIZER]
    // data string to tokenize
    aworx::String data=  "test;  abc ; 1,2 , 3 ; xyz ; including;separator";

    // create tokenizer on data with ';' as delimiter
    aworx::Tokenizer tokens( data, ';' );

    // read tokens
    cout << tokens.Next() << endl; // will print "test"
    cout << tokens.Next() << endl; // will print "abc"
    cout << tokens.Next() << endl; // will print "1,2 , 3"

    // tokenize actual (third) token (nested tokenizer)
    aworx::Tokenizer subTokens( tokens.Actual,  ',');
    cout << subTokens.Next();

    while( subTokens.HasNext() )
        cout << '~' << subTokens.Next();

    cout << endl;

    // continue with the main tokenizer
    cout << tokens.Next() << endl; // will print "xyz"

    // grab the rest, as we know that the last token might include our separator character
    cout << tokens.GetRest()      << endl; // will print "including;separator"
//! [DOX_ALIB_TOKENIZER]

    #undef cout
    ut.WriteResultFile( "DOX_ALIB_TOKENIZER.txt", testOutputStream.str(), "//! [OUTPUT]" );
}


UT_METHOD( DOX_ALIB_TOKEN )

    UT_PRINT("*** Documentation Sample +**")
    documentationSampleTokenizer( ut );
}

UT_CLASS_END

} //namespace
