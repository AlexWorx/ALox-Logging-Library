// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"


#define TESTCLASSNAME       CPP_ALib__Dox

#include <iostream>
#include <sstream>


// get support for  ostream operator<<() on String objects
#include "alib/compatibility/std_iostream.hpp"
#include "alib/compatibility/std_string.hpp"
#include "alib/strings/substring.hpp"
#include "alib.unittests/aworx_unittests.hpp"

using namespace std;
using namespace aworx;

//##################################################################################################
// SAMPLE code of Non-Checking method variants
//##################################################################################################

void parse( aworx::Substring line );
//! [DOX_ALIB_STRINGS_NONCHECKING_1]
void parse( aworx::Substring line )
{
    // object 'line' is of type aworx::Substring
    aworx::TString startWord= "<start>";
    integer idx= line.IndexOfSubstring( startWord );
    if( idx > 0 )
        line.ConsumeChars( idx + startWord.Length() );
    //...
    //...
//! [DOX_ALIB_STRINGS_NONCHECKING_1]
}

void sample22( aworx::Substring line );
void sample22( aworx::Substring line )
{
    aworx::TString startWord= "<start>";
    integer idx= line.IndexOfSubstring( startWord );
//! [DOX_ALIB_STRINGS_NONCHECKING_2]
    if( idx > 0 )
        line.ConsumeChars<false>( idx + startWord.Length() ); // No check for length of object 'line'
//! [DOX_ALIB_STRINGS_NONCHECKING_2]
}

void TakeStrings( const aworx::String& s1, const aworx::AString& s2, const aworx::String64 s3 );

//! [DOX_ALIB_STRINGS_AS_PARAMETERS_1]
void TakeStrings( const aworx::String& s1, const aworx::AString& s2, const aworx::String64 s3 )
//! [DOX_ALIB_STRINGS_AS_PARAMETERS_1]
{
    (void) s1;
    (void) s2;
    (void) s3;
}

void InvokeTakeStrings();
void InvokeTakeStrings()
{
/*
//! [DOX_ALIB_STRINGS_AS_PARAMETERS_2]
TakeStrings( "Str1", "Str2", "Str3" );          // Error, AString not implicitly constructable
//! [DOX_ALIB_STRINGS_AS_PARAMETERS_2]
*/
}

void InvokeTakeStrings2();
void InvokeTakeStrings2()
{
//! [DOX_ALIB_STRINGS_AS_PARAMETERS_3]
TakeStrings( "Str1", aworx::AString("Str2"), "Str3" ); // OK, AString explicit, AS and ASPrealloc implicit
//! [DOX_ALIB_STRINGS_AS_PARAMETERS_3]

}

//! [DOX_ALIB_STRINGS_ASPREALLOC_MEMBER]
class MyClass
{
    aworx::PAString<20> name=  "(none)";
};
//! [DOX_ALIB_STRINGS_ASPREALLOC_MEMBER]


void StringLiteral1();
void StringLiteral1()
{
//! [DOX_ALIB_STRINGS_LITERAL_1]
aworx::SLiteral<3> litA= "123";
aworx::SLiteral<5> litB= "MAGIC";
aworx::SLiteral<1> litC= "x";
//! [DOX_ALIB_STRINGS_LITERAL_1]
(void)litA;
(void)litB;
(void)litC;
}

aworx::AString StringLiteral2();
aworx::AString StringLiteral2()
{
//! [DOX_ALIB_STRINGS_LITERAL_2]
char carr[4] {"123"};
aworx::SLiteral<3> variableLit= carr;
aworx::AString          as( variableLit );

carr[0]= '4';
carr[1]= '5';
carr[2]= '6';

as << variableLit;
//! [DOX_ALIB_STRINGS_LITERAL_2]
//!
return as;
}




namespace ut_aworx {

UT_CLASS()


    UT_METHOD( Strings_NonCheckingSample )
    {
        UT_INIT();

        UT_PRINT("*** Documentation Sample +**")

        InvokeTakeStrings2();
        UT_EQ( "123456" , StringLiteral2() );
//        UT_RESULT_FILE( "DOX_ALIB_ASTRING_FORMAT.txt", testOutputStream.str() );

    }

UT_CLASS_END

}; //namespace
