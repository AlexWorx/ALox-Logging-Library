// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"
#include "alib/strings/tokenizer.hpp"
#include "alib/strings/numberformat.hpp"
#include "alib/time/ticks.hpp"
#include "alib/compatibility/std_iostream.hpp"
#include "alib/compatibility/std_string.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>


#include "aworx_unittests.hpp"


#define TESTCLASSNAME       CPP_ALib_Strings_ASBasic


using namespace std;
using namespace aworx;
using namespace aworx::lib;
using namespace aworx::lib::enums;
using namespace aworx::lib::strings;

namespace myns
{
    class MyString
    {
        private:
            const char* theString= "This is my string!";

        public:
            inline     bool         IsNulled   () const { return false; }
            constexpr  const char*  GetMyBuffer() const { return               theString;   }
            inline     int          GetMyLength() const { return (int) strlen( theString ); }
    };

}

namespace aworx { namespace lib { namespace strings {

    template<> struct              ToASDefined <const myns::MyString&> : public std::true_type {};
    template<> inline  const char* ToAS        <const myns::MyString&>( const myns::MyString& src )
    {
        return  src.GetMyBuffer();
    }
    template<> inline  int         ToAS        <const myns::MyString&>( const myns::MyString& src )
    {
        return  src.GetMyLength();
    }
    template<> struct              IsApplicable<const myns::MyString&> : public std::true_type {};
    template<> inline  int         ApplyTo( AString& target, const myns::MyString& src )
    {
        if ( src.IsNulled() )
            return -1;
        target.Append<false>( src.GetMyBuffer(), src.GetMyLength() );
        return src.GetMyLength();
    }

    // we have to define the helper struct IsApplicable. Its whole reason for existence is
    // to be able to throw compile time errors for types that do not have an ApplyTo
    // specialization
    template<>  struct       IsApplicable<const aworx::lib::time::Ticks&> : public std::true_type {};

    // And now the ApplyTo specialization itself
    template<>  inline   int ApplyTo( AString& target, const aworx::lib::time::Ticks& ticks )
    {
        time::TicksCalendarTime calendarTime;
        calendarTime.Set( ticks, Timezone::UTC );
        calendarTime.Format("yyyy-MM-dd HH:mm", target );
        return 16; // this is not too relevant. But has to be > 0 if something was written!
    }


}}} // namespace aworx::lib::strings


namespace ut_aworx {

UT_CLASS()

void testParam            ( ALIBUnitTesting& ut, const char* exp, const AS&             as )
{
    #if defined(ALIB_DEBUG_STRINGS)
        ALIB_STRING_DBG_CHK(&as);
    #endif
    String32 asTemp;
    asTemp._(as);
    UT_EQ( exp, asTemp  );
    UT_TRUE( as.Equals(exp) );
}
void testParamTerminatable( ALIBUnitTesting& ut, const char* exp, const ASTerminatable& as )
{
    #if defined(ALIB_DEBUG_STRINGS)
        ALIB_STRING_DBG_CHK(&as);
    #endif
    String32 asTemp;
    asTemp._(as);
    UT_EQ( exp, asTemp  );
    UT_TRUE( as.Equals(exp) );
}

void testParamASPreAlloc( ALIBUnitTesting& ut, const char* exp, const String64& as )
{
    #if defined(ALIB_DEBUG_STRINGS)
        ALIB_STRING_DBG_CHK(&as);
    #endif
    String32 asTemp;
    asTemp._(as);
    UT_EQ( exp, asTemp  );
    UT_TRUE( as.Equals(exp) );
}

void testParamSubstring( ALIBUnitTesting& ut, const char* exp, const ASSubstring& as )
{
    #if defined(ALIB_DEBUG_STRINGS)
        ALIB_STRING_DBG_CHK(&as);
    #endif
    String32 asTemp;
    asTemp._(as);
    UT_EQ( exp, asTemp  );
    UT_TRUE( as.Equals(exp) );
}


//---------------------------------------------------------------------------------------------------------
//--- Explicit constructors
//---------------------------------------------------------------------------------------------------------
UT_METHOD( ConstructorsExplicit )

    // before we begin...
    static_assert( std::is_nothrow_move_constructible<AS>             ::value, "AS has to be move constructable with no assertions");
    static_assert( std::is_nothrow_move_constructible<ASSubstring>    ::value, "ASSubstring has to be move constructable with no assertions");
    static_assert( std::is_nothrow_move_constructible<ASTerminatable> ::value, "ASTerminatable has to be move constructable with no assertions");
    static_assert( std::is_nothrow_move_constructible<AString>        ::value, "AString has to be move constructable with no assertions");
    static_assert( std::is_nothrow_move_constructible<ASPreAlloc<10>> ::value, "ASPreAlloc has to be move constructable with no assertions");

    wchar_t backTest[1024];

          char               testChar=            '@';
    const char               testConstChar=       '@';
    const char*              testConstCharP=      "TEST";
          char*              testCharP=           (char*) testConstCharP;
          wchar_t            testWChar=           L'\u20AC'; // euro sign
    const wchar_t            testConstWChar=      L'\u20AC'; // euro sign
    const wchar_t*           testConstWCharP=     L"\u03B1\u03B2\u03B3\u03B4\u03B5"; // Greek characters;
          wchar_t*           testWCharP=          (wchar_t*) testConstWCharP;
    std::string              testStdString        (testConstCharP);
    AS                       testAS               (testConstCharP);
    AString                  testAString          (testConstCharP);
    ASLiteral<1>             testASLiteral        ("1");
    ASSubstring              testSubstring        ( "@TEST@",1,4 );
    String32                 testASPreAlloc       ( testConstCharP );
    myns::MyString           testMyString;

    const std::string        testConstStdString   (testConstCharP);
    const AS                 testConstAS          (testConstCharP);
    const AString            testConstAString     (testConstCharP);
    const ASLiteral<1>       testConstASLiteral   ("1");
    const ASSubstring        testConstSubstring   ( "@TEST@",1,4 );
    const String32           testConstASPreAlloc  ( testConstCharP );
    const myns::MyString     testConstMyString;

    const char* myStringBuf= testMyString.GetMyBuffer();

    // this has to assert:
    // { AS     as( 42  );  }

    // AS
    { AS        as( "TEST"              ); testParam( ut, testConstCharP, as); }
    { AS        as( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { AS        as( testCharP           ); testParam( ut, testConstCharP, as); }

    { AS        as( testAS              ); testParam( ut, testConstCharP, as); }
    { AS        as( testASLiteral       ); testParam( ut, "1"           , as); }
    { AS        as( testSubstring       ); testParam( ut, testConstCharP, as); }
    { AS        as( testAString         ); testParam( ut, testConstCharP, as); }
    { AS        as( testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { AS        as( testStdString       ); testParam( ut, testConstCharP, as); }
    { AS        as( testMyString        ); testParam( ut, myStringBuf   , as); }

    { AS        as( testConstAS         ); testParam( ut, testConstCharP, as); }
    { AS        as( testConstASLiteral  ); testParam( ut, "1"           , as); }
    { AS        as( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AS        as( testConstAString    ); testParam( ut, testConstCharP, as); }
    { AS        as( testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { AS        as( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AS        as( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { AS        as(&testAS              ); testParam( ut, testConstCharP, as); }
    { AS        as(&testASLiteral       ); testParam( ut, "1"           , as); }
    { AS        as(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { AS        as(&testAString         ); testParam( ut, testConstCharP, as); }
    { AS        as(&testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { AS        as(&testStdString       ); testParam( ut, testConstCharP, as); }
    { AS        as(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { AS        as(&testConstAS         ); testParam( ut, testConstCharP, as); }
    { AS        as(&testConstASLiteral  ); testParam( ut, "1"           , as); }
    { AS        as(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AS        as(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { AS        as(&testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { AS        as(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AS        as(&testConstMyString   ); testParam( ut, myStringBuf   , as); }

    // ASTerminatable (no Substrings!)
    { ASTerminatable as( "TEST"              ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testCharP           ); testParam( ut, testConstCharP, as); }

    { ASTerminatable as( testAS              ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testASLiteral       ); testParam( ut, "1"           , as); }
    //{ ASTerminatable as( testSubstring       ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testAString         ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testStdString       ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testMyString        ); testParam( ut, myStringBuf   , as); }

    { ASTerminatable as( testConstAS         ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testConstASLiteral  ); testParam( ut, "1"           , as); }
    //{ ASTerminatable as( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testConstAString    ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { ASTerminatable as(&testAS              ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as(&testASLiteral       ); testParam( ut, "1"           , as); }
    //{ ASTerminatable as(&testAS              ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as(&testAString         ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as(&testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as(&testStdString       ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { ASTerminatable as(&testConstAS         ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as(&testConstASLiteral  ); testParam( ut, "1"           , as); }
    //{ ASTerminatable as(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as(&testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { ASTerminatable as(&testConstMyString   ); testParam( ut, myStringBuf   , as); }

    // AString
    { AString   as(  "TEST"             ); testParam( ut, testConstCharP, as); }
    { AString   as( L"TEST"             ); testParam( ut, testConstCharP, as); }
    { AString   as( testCharP           ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { AString   as( testWCharP          ); UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }
    { AString   as( testConstWCharP     ); UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }

    { AString   as( testChar            ); testParam( ut, "@",            as); }
    { AString   as( testWChar           ); UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { AString   as( testAS              ); testParam( ut, testConstCharP, as); }
    { AString   as( testASLiteral       ); testParam( ut, "1"           , as); }
    { AString   as( testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString   as( testAString         ); testParam( ut, testConstCharP, as); }
    { AString   as( testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { AString   as( testStdString       ); testParam( ut, testConstCharP, as); }
    { AString   as( testMyString        ); testParam( ut, myStringBuf   , as); }

    { AString   as( testConstChar       ); testParam( ut, "@",            as); }
    { AString   as( testConstWChar      ); UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { AString   as( testConstAS         ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstASLiteral  ); testParam( ut, "1"           , as); }
    { AString   as( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { AString   as(&testAS              ); testParam( ut, testConstCharP, as); }
    { AString   as(&testASLiteral       ); testParam( ut, "1"           , as); }
    { AString   as(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString   as(&testAString         ); testParam( ut, testConstCharP, as); }
    { AString   as(&testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { AString   as(&testStdString       ); testParam( ut, testConstCharP, as); }
    { AString   as(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { AString   as(&testConstAS         ); testParam( ut, testConstCharP, as); }
    { AString   as(&testConstASLiteral  ); testParam( ut, "1"           , as); }
    { AString   as(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString   as(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString   as(&testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { AString   as(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString   as(&testConstMyString   ); testParam( ut, myStringBuf   , as); }

    // ASPreAlloc
    { String64      as(  "TEST"             ); testParam( ut, testConstCharP, as); }
    { String64      as( L"TEST"             ); testParam( ut, testConstCharP, as); }
    { String64      as( testCharP           ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { String64      as( testWCharP          ); UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }
    { String64      as( testConstWCharP     ); UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }

    { String64      as( testChar            ); testParam( ut, "@",            as); }
    { String64      as( testWChar           ); UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { String64      as( testAS              ); testParam( ut, testConstCharP, as); }
    { String64      as( testASLiteral       ); testParam( ut, "1"           , as); }
    { String64      as( testSubstring       ); testParam( ut, testConstCharP, as); }
    { String64      as( testAString         ); testParam( ut, testConstCharP, as); }
    { String64      as( testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { String64      as( testStdString       ); testParam( ut, testConstCharP, as); }
    { String64      as( testMyString        ); testParam( ut, myStringBuf   , as); }

    { String64      as( testConstChar       ); testParam( ut, "@",            as); }
    { String64      as( testConstWChar      ); UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { String64      as( testConstAS         ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstASLiteral  ); testParam( ut, "1"           , as); }
    { String64      as( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstAString    ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { String64      as(&testAS              ); testParam( ut, testConstCharP, as); }
    { String64      as(&testASLiteral       ); testParam( ut, "1"           , as); }
    { String64      as(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { String64      as(&testAString         ); testParam( ut, testConstCharP, as); }
    { String64      as(&testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { String64      as(&testStdString       ); testParam( ut, testConstCharP, as); }
    { String64      as(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { String64      as(&testConstAS         ); testParam( ut, testConstCharP, as); }
    { String64      as(&testConstASLiteral  ); testParam( ut, "1"           , as); }
    { String64      as(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { String64      as(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { String64      as(&testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { String64      as(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { String64      as(&testConstMyString   ); testParam( ut, myStringBuf   , as); }

    // ASSubstring
    { ASSubstring as( "TEST"              ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testCharP           ); testParam( ut, testConstCharP, as); }

    { ASSubstring as( testAS              ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testASLiteral       ); testParam( ut, "1"           , as); }
    { ASSubstring as( testSubstring       ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testAString         ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testStdString       ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testMyString        ); testParam( ut, myStringBuf   , as); }

    { ASSubstring as( testConstAS         ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testConstASLiteral  ); testParam( ut, "1"           , as); }
    { ASSubstring as( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testConstAString    ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { ASSubstring as( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { ASSubstring as(&testAS              ); testParam( ut, testConstCharP, as); }
    { ASSubstring as(&testASLiteral       ); testParam( ut, "1"           , as); }
    { ASSubstring as(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { ASSubstring as(&testAString         ); testParam( ut, testConstCharP, as); }
    { ASSubstring as(&testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { ASSubstring as(&testStdString       ); testParam( ut, testConstCharP, as); }
    { ASSubstring as(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { ASSubstring as(&testConstAS         ); testParam( ut, testConstCharP, as); }
    { ASSubstring as(&testConstASLiteral  ); testParam( ut, "1"           , as); }
    { ASSubstring as(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { ASSubstring as(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { ASSubstring as(&testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { ASSubstring as(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { ASSubstring as(&testConstMyString   ); testParam( ut, myStringBuf   , as); }
}


UT_METHOD( ConstructorsImplicit )

    const char*              testConstCharP= "TEST";
    char*                    testCharP=      (char*) testConstCharP;
    std::string              testStdString   (testConstCharP);
    AString                  testAString     (testConstCharP);
    ASLiteral<1>             testASLiteral   ("1");
    ASSubstring              testSubstring   ( testConstCharP );
    String32                 testASPreAlloc  ( testConstCharP );
    myns::MyString           testMyString;

    const std::string        testConstStdString   (testConstCharP);
    const AString            testConstAString     (testConstCharP);
    const ASLiteral<1>       testConstASLiteral   ("1");
    const ASSubstring        testConstSubstring   ( testConstCharP );
    const String32           testConstASPreAlloc  ( testConstCharP );
    const myns::MyString     testConstMyString;

    const char* myStringBuf= testMyString.GetMyBuffer();

    // implicit AS
    {
       testParam( ut, testConstCharP,     "TEST"               );
       testParam( ut, testConstCharP,     testConstCharP       );
       testParam( ut, testConstCharP,     testCharP            );

       testParam( ut, "1",                testASLiteral        );
       testParam( ut, testConstCharP,     testSubstring        );
       testParam( ut, testConstCharP,     testAString          );
       testParam( ut, testConstCharP,     testASPreAlloc       );
       testParam( ut, testConstCharP,     testStdString        );
       testParam( ut, myStringBuf   ,     testMyString         );

       testParam( ut, "1",                testConstASLiteral   );
       testParam( ut, testConstCharP,     testConstSubstring   );
       testParam( ut, testConstCharP,     testConstAString     );
       testParam( ut, testConstCharP,     testConstASPreAlloc  );
       testParam( ut, myStringBuf   ,     testConstMyString    );

       testParam( ut, "1",               &testASLiteral        );
       testParam( ut, testConstCharP,    &testSubstring        );
       testParam( ut, testConstCharP,    &testAString          );
       testParam( ut, testConstCharP,    &testASPreAlloc       );
       testParam( ut, testConstCharP,    &testStdString        );
       testParam( ut, myStringBuf   ,    &testMyString         );

       testParam( ut, "1",               &testConstASLiteral   );
       testParam( ut, testConstCharP,    &testConstSubstring   );
       testParam( ut, testConstCharP,    &testConstAString     );
       testParam( ut, testConstCharP,    &testConstASPreAlloc  );
       testParam( ut, testConstCharP,    &testConstStdString   );
       testParam( ut, myStringBuf   ,    &testConstMyString    );
    }

    // implicit SubString
    {
       testParamSubstring( ut, testConstCharP,     "TEST"               );
       testParamSubstring( ut, testConstCharP,     testConstCharP       );
       testParamSubstring( ut, testConstCharP,     testCharP            );

       testParamSubstring( ut, "1",                testASLiteral        );
       testParamSubstring( ut, testConstCharP,     testSubstring        );
       testParamSubstring( ut, testConstCharP,     testAString          );
       testParamSubstring( ut, testConstCharP,     testASPreAlloc       );
       testParamSubstring( ut, testConstCharP,     testStdString        );
       testParamSubstring( ut, myStringBuf   ,     testMyString         );

       testParamSubstring( ut, "1",                testConstASLiteral   );
       testParamSubstring( ut, testConstCharP,     testConstSubstring   );
       testParamSubstring( ut, testConstCharP,     testConstAString     );
       testParamSubstring( ut, testConstCharP,     testConstASPreAlloc  );
       testParamSubstring( ut, myStringBuf   ,     testConstMyString    );

       testParamSubstring( ut, "1",               &testASLiteral        );
       testParamSubstring( ut, testConstCharP,    &testSubstring        );
       testParamSubstring( ut, testConstCharP,    &testAString          );
       testParamSubstring( ut, testConstCharP,    &testASPreAlloc       );
       testParamSubstring( ut, testConstCharP,    &testStdString        );
       testParamSubstring( ut, myStringBuf   ,    &testMyString         );

       testParamSubstring( ut, "1",               &testConstASLiteral   );
       testParamSubstring( ut, testConstCharP,    &testConstSubstring   );
       testParamSubstring( ut, testConstCharP,    &testConstAString     );
       testParamSubstring( ut, testConstCharP,    &testConstASPreAlloc  );
       testParamSubstring( ut, testConstCharP,    &testConstStdString   );
       testParamSubstring( ut, myStringBuf   ,    &testConstMyString    );
    }

    // implicit ASTerminatable
    {
       testParamTerminatable( ut, testConstCharP,     "TEST"               );
       testParamTerminatable( ut, testConstCharP,     testConstCharP       );
       testParamTerminatable( ut, testConstCharP,     testCharP            );

       testParamTerminatable( ut, "1",                testASLiteral        );
       //Substrings are not allowed!  testParamTerminatable( ut, testConstCharP,     testSubstring        );
       testParamTerminatable( ut, testConstCharP,     testAString          );
       testParamTerminatable( ut, testConstCharP,     testASPreAlloc       );
       testParamTerminatable( ut, testConstCharP,     testStdString        );
       testParamTerminatable( ut, myStringBuf   ,     testMyString         );

       testParamTerminatable( ut, "1",                testConstASLiteral   );
       //Substrings are not allowed!  testParamTerminatable( ut, testConstCharP,     testConstSubstring   );
       testParamTerminatable( ut, testConstCharP,     testConstAString     );
       testParamTerminatable( ut, testConstCharP,     testConstASPreAlloc  );
       testParamTerminatable( ut, testConstCharP,     testConstStdString   );
       testParamTerminatable( ut, myStringBuf   ,     testConstMyString    );

       testParamTerminatable( ut, "1",               &testASLiteral        );
       //Substrings are not allowed!  testParamTerminatable( ut, testConstCharP,    &testSubstring        );
       testParamTerminatable( ut, testConstCharP,    &testAString          );
       testParamTerminatable( ut, testConstCharP,    &testASPreAlloc       );
       testParamTerminatable( ut, testConstCharP,    &testStdString        );
       testParamTerminatable( ut, myStringBuf   ,    &testMyString         );

       testParamTerminatable( ut, "1",               &testConstASLiteral   );
       testParamTerminatable( ut, testConstCharP,    &testConstAString     );
       //Substrings are not allowed!  testParamTerminatable( ut, testConstCharP,    &testConstSubstring   );
       testParamTerminatable( ut, testConstCharP,    &testConstASPreAlloc  );
       testParamTerminatable( ut, testConstCharP,    &testConstStdString   );
       testParamTerminatable( ut, myStringBuf   ,    &testConstMyString    );
    }

}

//---------------------------------------------------------------------------------------------------------
//--- Assignment
//---------------------------------------------------------------------------------------------------------
UT_METHOD( Assignment )

    wchar_t backTest[1024];

          char               testChar=            '@';
    const char               testConstChar=       '@';
    const char*              testConstCharP=      "TEST";
          char*              testCharP=           (char*) testConstCharP;
          wchar_t            testWChar=           L'\u20AC'; // euro sign
    const wchar_t            testConstWChar=      L'\u20AC'; // euro sign
    const wchar_t*           testConstWCharP=     L"\u03B1\u03B2\u03B3\u03B4\u03B5"; // Greek characters;
          wchar_t*           testWCharP=          (wchar_t*) testConstWCharP;
    std::string              testStdString        (testConstCharP);
    AString                  testAString          (testConstCharP);
    ASLiteral<1>             testASLiteral        ("1");
    ASSubstring              testSubstring        ( "@TEST@",1,4 );
    String32                 testASPreAlloc       ( testConstCharP );
    myns::MyString           testMyString;

    const std::string        testConstStdString   (testConstCharP);
    const AString            testConstAString     (testConstCharP);
    const ASLiteral<1>       testConstASLiteral   ("1");
    const ASSubstring        testConstSubstring   ( "@TEST@",1,4 );
    const String32           testConstASPreAlloc  ( testConstCharP );
    const myns::MyString     testConstMyString;

    const char* myStringBuf= testMyString.GetMyBuffer();

    // AS
    { AS            as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { AS            as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { AS            as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { AS            as=  testASLiteral       ; testParam( ut, "1"           , as); }
    { AS            as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { AS            as=  testAString         ; testParam( ut, testConstCharP, as); }
    { AS            as=  testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { AS            as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { AS            as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { AS            as=  testConstASLiteral  ; testParam( ut, "1"           , as); }
    { AS            as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AS            as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { AS            as=  testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { AS            as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AS            as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { AS            as= &testASLiteral       ; testParam( ut, "1"           , as); }
    { AS            as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { AS            as= &testAString         ; testParam( ut, testConstCharP, as); }
    { AS            as= &testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { AS            as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { AS            as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { AS            as= &testConstASLiteral  ; testParam( ut, "1"           , as); }
    { AS            as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AS            as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { AS            as= &testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { AS            as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AS            as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { AS        as; as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { AS        as; as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { AS        as; as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { AS        as; as=  testASLiteral       ; testParam( ut, "1"           , as); }
    { AS        as; as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { AS        as; as=  testAString         ; testParam( ut, testConstCharP, as); }
    { AS        as; as=  testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { AS        as; as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { AS        as; as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { AS        as; as=  testConstASLiteral  ; testParam( ut, "1"           , as); }
    { AS        as; as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AS        as; as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { AS        as; as=  testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { AS        as; as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AS        as; as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { AS        as; as= &testASLiteral       ; testParam( ut, "1"           , as); }
    { AS        as; as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { AS        as; as= &testAString         ; testParam( ut, testConstCharP, as); }
    { AS        as; as= &testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { AS        as; as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { AS        as; as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { AS        as; as= &testConstASLiteral  ; testParam( ut, "1"           , as); }
    { AS        as; as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AS        as; as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { AS        as; as= &testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { AS        as; as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AS        as; as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }


    // ASSubstring
    { ASSubstring          as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { ASSubstring          as=  testASLiteral       ; testParam( ut, "1"           , as); }
    { ASSubstring          as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as=  testAString         ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as=  testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { ASSubstring          as=  testConstASLiteral  ; testParam( ut, "1"           , as); }
    { ASSubstring          as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as=  testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { ASSubstring          as= &testASLiteral       ; testParam( ut, "1"           , as); }
    { ASSubstring          as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as= &testAString         ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as= &testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { ASSubstring          as= &testConstASLiteral  ; testParam( ut, "1"           , as); }
    { ASSubstring          as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as= &testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { ASSubstring          as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { ASSubstring      as; as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { ASSubstring      as; as=  testASLiteral       ; testParam( ut, "1"           , as); }
    { ASSubstring      as; as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as=  testAString         ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as=  testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { ASSubstring      as; as=  testConstASLiteral  ; testParam( ut, "1"           , as); }
    { ASSubstring      as; as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as=  testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { ASSubstring      as; as= &testASLiteral       ; testParam( ut, "1"           , as); }
    { ASSubstring      as; as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as= &testAString         ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as= &testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { ASSubstring      as; as= &testConstASLiteral  ; testParam( ut, "1"           , as); }
    { ASSubstring      as; as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as= &testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { ASSubstring      as; as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    // ASTerminatable (no Substrings!)
    { ASTerminatable     as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { ASTerminatable     as=  testASLiteral       ; testParam( ut, "1"           , as); }
    //{ ASTerminatable   as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as=  testAString         ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as=  testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { ASTerminatable     as=  testConstASLiteral  ; testParam( ut, "1"           , as); }
    //{ ASTerminatable   as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as=  testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { ASTerminatable     as= &testASLiteral       ; testParam( ut, "1"           , as); }
    //{ ASTerminatable   as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as= &testAString         ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as= &testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { ASTerminatable     as= &testConstASLiteral  ; testParam( ut, "1"           , as); }
    //{ ASTerminatable   as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as= &testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { ASTerminatable     as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { ASTerminatable as; as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { ASTerminatable as; as=  testASLiteral       ; testParam( ut, "1"           , as); }
    //{ ASTerminatable as; as=testSubstring       ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as=  testAString         ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as=  testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { ASTerminatable as; as=  testConstASLiteral  ; testParam( ut, "1"           , as); }
    //{ ASTerminatable as; as=testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as=  testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { ASTerminatable as; as= &testASLiteral       ; testParam( ut, "1"           , as); }
    //{ ASTerminatable as;as=&testSubstring       ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as= &testAString         ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as= &testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { ASTerminatable as; as= &testConstASLiteral  ; testParam( ut, "1"           , as); }
    //{ ASTerminatable as;as=&testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as= &testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { ASTerminatable as; as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    // AString

    // direct initialization not allowed!
    //{ AString            as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    //...
    //...

    { AString        as; as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  L"TEST"             ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testCharP           ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testWCharP          ; UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }
    { AString        as; as=  testConstWCharP     ; UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }


    { AString        as; as=  testChar            ; testParam( ut, "@",            as); }
    { AString        as; as=  testWChar           ; UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { AString        as; as=  testASLiteral       ; testParam( ut, "1"           , as); }
    { AString        as; as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testAString         ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { AString        as; as=  testConstChar       ; testParam( ut, "@",            as); }
    { AString        as; as=  testConstWChar      ; UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { AString        as; as=  testConstASLiteral  ; testParam( ut, "1"           , as); }
    { AString        as; as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { AString        as; as= &testASLiteral       ; testParam( ut, "1"           , as); }
    { AString        as; as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testAString         ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { AString        as; as= &testConstASLiteral  ; testParam( ut, "1"           , as); }
    { AString        as; as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    // ASPreAlloc
    // direct initialization not allowed!
    //{ String32             as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    //...
    //...
    { String32           as; as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  L"TEST"             ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testCharP           ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testWCharP          ; UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }
    { String32           as; as=  testConstWCharP     ; UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }

    { String32           as; as=  testChar            ; testParam( ut, "@",            as); }
    { String32           as; as=  testWChar           ; UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { String32           as; as=  testASLiteral       ; testParam( ut, "1"           , as); }
    { String32           as; as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testAString         ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { String32           as; as=  testConstChar       ; testParam( ut, "@",            as); }
    { String32           as; as=  testConstWChar      ; UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { String32           as; as=  testConstASLiteral  ; testParam( ut, "1"           , as); }
    { String32           as; as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { String32           as; as= &testASLiteral       ; testParam( ut, "1"           , as); }
    { String32           as; as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testAString         ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { String32           as; as= &testConstASLiteral  ; testParam( ut, "1"           , as); }
    { String32           as; as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    // ASLiteral
    { ASLiteral<4>           as=  "TEST"              ; testParam( ut, testConstCharP, as); }
}

//---------------------------------------------------------------------------------------------------------
//--- Append and operator <<
//---------------------------------------------------------------------------------------------------------
UT_METHOD( AppendAndAppendOperator )

    const char*              testConstCharP= "TEST";
    char*                    testCharP=      (char*) testConstCharP;
    std::string              testStdString   (testConstCharP);
    AString                  testAString     (testConstCharP);
    ASLiteral<1>             testASLiteral   ("1");
    ASSubstring              testSubstring   ( "@TEST@",1,4 );
    String32                 testASPreAlloc  ( testConstCharP );
    myns::MyString           testMyString;

    const std::string        testConstStdString   (testConstCharP);
    const AString            testConstAString     (testConstCharP);
    const ASLiteral<1>       testConstASLiteral   ("1");
    const ASSubstring        testConstSubstring   ( "@TEST@",1,4 );
    const String32           testConstASPreAlloc  ( testConstCharP );
    const myns::MyString     testConstMyString;

    const char* myStringBuf= testMyString.GetMyBuffer();

    // these have to fail
    // { vector<int> x;             AS as(x);}
    // { vector<int> x; AString as; as._ (x);}
    // { char c   ='a';             AS as(c);}

    time::TicksCalendarTime calendar;
    calendar.Day=     1;
    calendar.Month=   4;
    calendar.Year=    2011;
    calendar.Hour=    16;
    calendar.Minute=  00;
    calendar.Second=  01;
    time::Ticks         testTicks(calendar.Get(Timezone::UTC));
    const time::Ticks   testConstTicks  ( testTicks );
    const char* ticksResult= "2011-04-01 16:00";

    // AString
    { AString as; as <<  "TEST"              ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testCharP           ; testParam( ut, testConstCharP, as); }

    { AString as; as <<  testASLiteral       ; testParam( ut, "1"           , as); }
    { AString as; as <<  testSubstring       ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testAString         ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testStdString       ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testMyString        ; testParam( ut, myStringBuf   , as); }
    { AString as; as <<  testTicks           ; testParam( ut, ticksResult,    as); }

    { AString as; as <<  testConstASLiteral  ; testParam( ut, "1"           , as); }
    { AString as; as <<  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testConstAString    ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testConstMyString   ; testParam( ut, myStringBuf   , as); }
    { AString as; as <<  testConstTicks      ; testParam( ut, ticksResult,    as); }

    { AString as; as << &testASLiteral       ; testParam( ut, "1"           , as); }
    { AString as; as << &testSubstring       ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testAString         ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testStdString       ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testMyString        ; testParam( ut, myStringBuf   , as); }
    { AString as; as << &testTicks           ; testParam( ut, ticksResult,    as); }

    { AString as; as << &testConstASLiteral  ; testParam( ut, "1"           , as); }
    { AString as; as << &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testConstAString    ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testConstMyString   ; testParam( ut, myStringBuf   , as); }
    { AString as; as << &testConstTicks      ; testParam( ut, ticksResult,    as); }

    { AString as; as._( "TEST"              ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testCharP           ); testParam( ut, testConstCharP, as); }

    { AString as; as._( testASLiteral       ); testParam( ut, "1"           , as); }
    { AString as; as._( testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testAString         ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testStdString       ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testMyString        ); testParam( ut, myStringBuf   , as); }
    { AString as; as._( testTicks           ); testParam( ut, ticksResult,    as); }

    { AString as; as._( testConstASLiteral  ); testParam( ut, "1"           , as); }
    { AString as; as._( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testConstMyString   ); testParam( ut, myStringBuf   , as); }
    { AString as; as._( testConstTicks      ); testParam( ut, ticksResult,    as); }

    { AString as; as._(&testASLiteral       ); testParam( ut, "1"           , as); }
    { AString as; as._(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testAString         ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testStdString       ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testMyString        ); testParam( ut, myStringBuf   , as); }
    { AString as; as._(&testTicks           ); testParam( ut, ticksResult,    as); }

    { AString as; as._(&testConstASLiteral  ); testParam( ut, "1"           , as); }
    { AString as; as._(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testConstMyString   ); testParam( ut, myStringBuf   , as); }
    { AString as; as._(&testConstTicks      ); testParam( ut, ticksResult,    as); }

    { AString as; as._<false>( "TEST"              ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testCharP           ); testParam( ut, testConstCharP, as); }

    { AString as; as._<false>( testASLiteral       ); testParam( ut, "1"           , as); }
    { AString as; as._<false>( testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testAString         ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testStdString       ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testMyString        ); testParam( ut, myStringBuf   , as); }
    { AString as; as._<false>( testTicks           ); testParam( ut, ticksResult,    as); }

    { AString as; as._<false>( testConstASLiteral  ); testParam( ut, "1"           , as); }
    { AString as; as._<false>( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testConstMyString   ); testParam( ut, myStringBuf   , as); }
    { AString as; as._<false>( testConstTicks      ); testParam( ut, ticksResult,    as); }

    { AString as; as._<false>(&testASLiteral       ); testParam( ut, "1"           , as); }
    { AString as; as._<false>(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testAString         ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testStdString       ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testMyString        ); testParam( ut, myStringBuf   , as); }
    { AString as; as._<false>(&testTicks           ); testParam( ut, ticksResult,    as); }

    { AString as; as._<false>(&testConstASLiteral  ); testParam( ut, "1"           , as); }
    { AString as; as._<false>(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testConstMyString   ); testParam( ut, myStringBuf   , as); }
    { AString as; as._<false>(&testConstTicks      ); testParam( ut, ticksResult,    as); }

    // ASPreAlloc
    { String64    as; as <<  "TEST"              ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testCharP           ; testParam( ut, testConstCharP, as); }

    { String64    as; as <<  testASLiteral       ; testParam( ut, "1"           , as); }
    { String64    as; as <<  testSubstring       ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testAString         ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testStdString       ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testMyString        ; testParam( ut, myStringBuf   , as); }

    { String64    as; as <<  testConstASLiteral  ; testParam( ut, "1"           , as); }
    { String64    as; as <<  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testConstAString    ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { String64    as; as << &testASLiteral       ; testParam( ut, "1"           , as); }
    { String64    as; as << &testSubstring       ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testAString         ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testASPreAlloc      ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testStdString       ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testMyString        ; testParam( ut, myStringBuf   , as); }

    { String64    as; as << &testConstASLiteral  ; testParam( ut, "1"           , as); }
    { String64    as; as << &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testConstAString    ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testConstASPreAlloc ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { String64    as; as._( "TEST"              ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testCharP           ); testParam( ut, testConstCharP, as); }

    { String64    as; as._( testASLiteral       ); testParam( ut, "1"           , as); }
    { String64    as; as._( testSubstring       ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testAString         ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testStdString       ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testMyString        ); testParam( ut, myStringBuf   , as); }

    { String64    as; as._( testConstASLiteral  ); testParam( ut, "1"           , as); }
    { String64    as; as._( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testConstAString    ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { String64    as; as._(&testASLiteral       ); testParam( ut, "1"           , as); }
    { String64    as; as._(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testAString         ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testASPreAlloc      ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testStdString       ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { String64    as; as._(&testConstASLiteral  ); testParam( ut, "1"           , as); }
    { String64    as; as._(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testConstASPreAlloc ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testConstMyString   ); testParam( ut, myStringBuf   , as); }

}


//---------------------------------------------------------------------------------------------------------
//--- Move constructors
//---------------------------------------------------------------------------------------------------------
UT_METHOD( MoveConstructors )

    bool oldHaltOnError=    Report::GetDefault().HaltOnError;
    bool oldHaltOnWarning=  Report::GetDefault().HaltOnWarning;
    Report::GetDefault().HaltOnError=
    Report::GetDefault().HaltOnWarning=    false;

    // this test is more for debug stepping to check if the right constructors are used
    {   AString as(AString("Anonymous"));       as._("x");   }

    {   String16    as(String16   ("123456789_12345" ));   as._("x");   }
    {   String16    as(String16   ("123456789_123456"));   as._("x");   }
    {   String16    as(AString("123456789_12345" ));   as._("x");   }
    {   String16    as(AString("123456789_123456"));   as._("x");   }

    {   String16    vola("123456789_123456");
        String16    as( std::move(vola));
                as._("x");
    }

    {   String16    vola("123456789_123456");
        String16    as; as= std::move(vola);
                as._("x");
    }
    Report::GetDefault().HaltOnError=      oldHaltOnError;
    Report::GetDefault().HaltOnWarning=    oldHaltOnWarning;

}
UT_CLASS_END

} //namespace
