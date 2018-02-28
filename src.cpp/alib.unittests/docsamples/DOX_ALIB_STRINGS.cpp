// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"


#define TESTCLASSNAME       CPP_ALib_Dox_Strings

#include <iostream>
#include <sstream>


// get support for  ostream operator<<() on String objects
#include "alib/compatibility/std_iostream.hpp"
#include "alib/compatibility/std_string.hpp"
#include "alib/strings/substring.hpp"
#include "alib/strings/format/propertyformatters.hpp"
#include "alib.unittests/aworx_unittests.hpp"
#include "alox/logtools.hpp"


namespace std
{
    extern stringstream testOutputStream;
}
#define cout testOutputStream

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
TakeStrings( "Str1", aworx::AString("Str2"), "Str3" ); // OK, AString explicit, String and PreallocatedString implicit
//! [DOX_ALIB_STRINGS_AS_PARAMETERS_3]

}

//! [DOX_ALIB_STRINGS_ASPREALLOC_MEMBER]
class MyClass
{
    aworx::PreallocatedString<20> name=  "(none)";
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

// ####################################### PropertyFormatter #######################################
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_1]
enum class Hobbies
{
    Hacking,
    FineArts,
};

struct  Person
{
    String        Name;
    int           Age;
    Hobbies       Hobby;
};
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_1]

//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_2]
namespace
{
    Box getName  ( Person& p, AString&  ) { return  p.Name;  }
    Box getAge   ( Person& p, AString&  ) { return  p.Age;   }
    Box getHobby ( Person& p, AString&  ) { return  p.Hobby == Hobbies::Hacking ? "hacking" : "fine arts"  ; }
}
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_2]

//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_3]
PropertyFormatter<Person>::TCallbackTable  PersonCallbacks=
{
      { "name"  , 1, getName  },
      { "age"   , 1, getAge   },
      { "hobby" , 1, getHobby },
};
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_3]


//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_1]
enum class PersonFormats
{
    Short,
    Default,
    All
};
ALIB_CONFIG_VARIABLES( PersonFormats, aworx::lib::ALIB, "PersonFormats")
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_1]



namespace ut_aworx {

UT_CLASS()

UT_METHOD( PropertyFormatter )
{
    UT_INIT();
    UT_PRINT( "ALib PropertyFormatter tests and documentation sample" );
    {
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_4]

// Our data objects
Person p1= { "Sue" , 28, Hobbies::Hacking };
Person p2= { "John", 35, Hobbies::Hacking };

// The format string. Make this changeable at runtime, e.g. load from INI-file!
String format= "{@name} is aged {@age} and his/her hobby is {@hobby}";

// create a formatter
aworx::PropertyFormatter<Person>  propertyFormatter( format, PersonCallbacks  );

// format the two data objects
AString target;
propertyFormatter.Format( target, p1 );
target << NewLine;
propertyFormatter.Format( target, p2 );
target << NewLine;

// that's it!
std::cout << target;

//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_4]
    }
    ut.WriteResultFile( "DOX_ALIB_STRINGS_PROPERTY_FORMATTER.txt", testOutputStream.str(), "//! [OUTPUT]" );
    testOutputStream.str("");

    // do some more unit testing
    {
        bool caught= false;
        try
        {
            aworx::PropertyFormatter<Person>  propertyFormatter( "Test {@Unknown}", PersonCallbacks  );
        }
        catch( Exception& e )
        {
            UT_PRINT( "Exception caught as expected: " );
            LogTools::Exception( ut.lox, e, Verbosity::Info, ut.Domain, "  " );
            if( e.Code() != lib::strings::format::Exceptions::UnknownPropertyInFormatString  )
            {
              UT_PRINT( "But wrong type: caught: {}, expected: {}", e.Code(), lib::strings::format::Exceptions::UnknownPropertyInFormatString );
              UT_TRUE( false );
            }

            caught= true;
        }
        if( !caught )
        {
            UT_PRINT( "No Exception caught. Expected: ", lib::strings::format::Exceptions::UnknownPropertyInFormatString );
            UT_TRUE( caught );
        }

    }

}


UT_METHOD( PropertyFormatters )
{
    UT_INIT();
    UT_PRINT( "ALib PropertyFormatters tests and documentation sample" );

//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_2]
aworx::lib::ALIB.Res->AddBulk( aworx::lib::ALIB.ResourceCategory.ToCString(),

    // Enum meta data for enum class "PersonFormats"
    "PersonFormats",
        "0|FORMATS|"   "SHORT"     "|PFVal0"  "||||"  "PFComnt|"
        "1|FORMATS|"   "DEFAULT"   "|PFVal1"  "||||"  "PFComnt|"
        "2|FORMATS|"   "ALL"       "|PFVal2"  "||||"  "PFComnt"  ,

        // Built-in default values for the variables
        "PFVal0"   ,  "{@name}"                           ,
        "PFVal1"   ,  "{@name} ({@age})"                  ,
        "PFVal2"   ,  "{@name} aged {@age} loves {@hobby}",

        // Variable comments. These are written for example to an INI-file if the application
        // fetches default values at the end of the process. In this sample, all variables share
        // the same comment.
        "PFComnt" , "A property format string for printing \"Persons\".\n"
                    "You can use @name, @age and @hobby as placeholders for person attributes." ,

        nullptr
);
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_2]

//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_31]
aworx::PropertyFormatters<Person, PersonFormats>  PersonFormatterMap( PersonCallbacks  );
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_31]

//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_32]
using  FMTPerson= aworx::lib::strings::format::PropertyFormatterMapApplicable<Person, PersonFormats>;
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_32]


//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_4]
// Our data objects
Person sue=  { "Sue" , 28, Hobbies::Hacking };
Person john= { "John", 35, Hobbies::Hacking };

// format the two data objects
AString target;
target << FMTPerson( PersonFormatterMap, PersonFormats::Short, sue  ) << NewLine;
target << FMTPerson( PersonFormatterMap, PersonFormats::All,   john ) << NewLine;

std::cout << target;
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_4]
    ut.WriteResultFile( "DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP.txt", testOutputStream.str(), "//! [OUTPUT]" );
    testOutputStream.str("");
    target.Clear();
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_5]

#define FMT_PERSON(o,p)        FMTPerson( PersonFormatterMap, o                     , p )
#define FMT_PERSON_DEFAULT(p)  FMTPerson( PersonFormatterMap, PersonFormats::Default, p )
#define FMT_PERSON_SHORT(p)    FMTPerson( PersonFormatterMap, PersonFormats::Short  , p )
#define FMT_PERSON_ALL(p)      FMTPerson( PersonFormatterMap, PersonFormats::All    , p )

target << FMT_PERSON( PersonFormats::Short, sue )     << NewLine;
target << FMT_PERSON_SHORT( sue )                     << NewLine;
target << FMT_PERSON_DEFAULT( sue )                   << NewLine;
target << FMT_PERSON_ALL( sue )                       << NewLine;

std::cout << target;
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_5]

  ut.WriteResultFile( "DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_2.txt", testOutputStream.str(), "//! [OUTPUT]" );
  testOutputStream.str("");
    target.Clear();

//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_6]
ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE( FMTPerson* )
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_6]

//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_7]
Formatter::AcquireDefault( ALIB_SRCPOS_REL_EMPTY )
          .Format( target, "The person is: {}", FMT_PERSON_ALL( john ) );
Formatter::ReleaseDefault();

std::cout << target << endl;
//! [DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_7]
  ut.WriteResultFile( "DOX_ALIB_STRINGS_PROPERTY_FORMATTER_MAP_3.txt", testOutputStream.str(), "//! [OUTPUT]" );
  testOutputStream.str("");
  target.Clear();
}


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
