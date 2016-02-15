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

#include "alib/alib.hpp"

// get support for  ostream operator<<() on String objects
#include "alib/compatibility/std_iostream.hpp"
#include "alib/compatibility/std_string.hpp"
#include "alib/strings/substring.hpp"
#include "aworx_unittests.hpp"

using namespace std;
using namespace aworx;

//##################################################################################################
// SAMPLE code of Non-Checking method variants
//##################################################################################################

void sample12( aworx::Substring line )
{
//! [DOX_ALIB_STRINGS_NONCHECKING_1]
    // object 'line' is of type aworx::Substring
    aworx::String startWord= "<start>";
    int idx= line.IndexOfAS( startWord );
    if( idx > 0 )
        line.Consume( idx + startWord.Length() );
//! [DOX_ALIB_STRINGS_NONCHECKING_1]
}

void sample22( aworx::Substring line )
{
//! [DOX_ALIB_STRINGS_NONCHECKING_2]
    aworx::String startWord= "<start>";
    int idx= line.IndexOfAS( startWord );
    if( idx > 0 )
        line.Consume<false>( idx + startWord.Length() ); // No check for length of object 'line'
//! [DOX_ALIB_STRINGS_NONCHECKING_2]
}

//! [DOX_ALIB_STRINGS_AS_PARAMETERS_1]
void TakeStrings( const aworx::String& s1, const aworx::AString& s2, const aworx::String64 s3 )
//! [DOX_ALIB_STRINGS_AS_PARAMETERS_1]
{
    (void) s1;
    (void) s2;
    (void) s3;
}

void InvokeTakeStrings()
{
/*
//! [DOX_ALIB_STRINGS_AS_PARAMETERS_2]
TakeStrings( "Str1", "Str2", "Str3" );          // Error, AString not implicitly constructable
//! [DOX_ALIB_STRINGS_AS_PARAMETERS_2]
*/
}

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


void ASLiteral1()
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

aworx::AString ASLiteral2()
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





// Windows.h might bring in max/min macros
#if defined( max )
    #undef max
    #undef min
#endif

namespace ut_aworx {

UT_CLASS()


    UT_METHOD( Strings_NonCheckingSample )

        UT_PRINT("*** Documentation Sample +**")

        InvokeTakeStrings2();
        UT_EQ( "123456" , ASLiteral2() );
//        UT_RESULT_FILE( "DOX_ALIB_ASTRING_FORMAT.txt", testOutputStream.str() );

    }

UT_CLASS_END

}; //namespace
