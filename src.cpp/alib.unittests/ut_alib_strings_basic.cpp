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

    template<> struct              ToStringDefined <const myns::MyString&> : public std::true_type {};
    template<> inline  const char* ToString    <const myns::MyString&>( const myns::MyString& src )
    {
        return  src.GetMyBuffer();
    }
    template<> inline  int         ToString    <const myns::MyString&>( const myns::MyString& src )
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

void testParam            ( ALIBUnitTesting& ut, const char* exp, const String&         as )
{
    #if defined(ALIB_DEBUG_STRINGS)
        ALIB_STRING_DBG_CHK(&as);
    #endif
    String32 asTemp;
    asTemp._(as);
    UT_EQ( exp, asTemp  );
    UT_TRUE( as.Equals(exp) );
}
void testParamTerminatable( ALIBUnitTesting& ut, const char* exp, const TString& as )
{
    #if defined(ALIB_DEBUG_STRINGS)
        ALIB_STRING_DBG_CHK(&as);
    #endif
    String32 asTemp;
    asTemp._(as);
    UT_EQ( exp, asTemp  );
    UT_TRUE( as.Equals(exp) );
}

void testParamPreallocatedString( ALIBUnitTesting& ut, const char* exp, const String64& as )
{
    #if defined(ALIB_DEBUG_STRINGS)
        ALIB_STRING_DBG_CHK(&as);
    #endif
    String32 asTemp;
    asTemp._(as);
    UT_EQ( exp, asTemp  );
    UT_TRUE( as.Equals(exp) );
}

void testParamSubstring( ALIBUnitTesting& ut, const char* exp, const Substring& as )
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
    static_assert( std::is_nothrow_move_constructible<String>       ::value, "String has to be move constructable with no assertions");
    static_assert( std::is_nothrow_move_constructible<Substring>    ::value, "Substring has to be move constructable with no assertions");
    static_assert( std::is_nothrow_move_constructible<TString>      ::value, "TString has to be move constructable with no assertions");
    static_assert( std::is_nothrow_move_constructible<AString>      ::value, "AString has to be move constructable with no assertions");
    static_assert( std::is_nothrow_move_constructible<PAString<10>> ::value, "PreallocatedString has to be move constructable with no assertions");

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
    String                   testString           (testConstCharP);
    AString                  testAString          (testConstCharP);
    SLiteral<1>              testStringLiteral    ("1");
    Substring                testSubstring        ( "@TEST@",1,4 );
    String32                 testPreallocatedString       ( testConstCharP );
    myns::MyString           testMyString;

    const std::string        testConstStdString   (testConstCharP);
    const String             testConstString      (testConstCharP);
    const AString            testConstAString     (testConstCharP);
    const SLiteral<1>        testConstStringLiteral("1");
    const Substring          testConstSubstring   ( "@TEST@",1,4 );
    const String32           testConstPreallocatedString  ( testConstCharP );
    const myns::MyString     testConstMyString;

    const char* myStringBuf= testMyString.GetMyBuffer();

    // this has to assert:
    // { String     as( 42  );  }

    // String
    { String    as( "TEST"              ); testParam( ut, testConstCharP, as); }
    { String    as( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { String    as( testCharP           ); testParam( ut, testConstCharP, as); }

    { String    as( testString          ); testParam( ut, testConstCharP, as); }
    { String    as( testStringLiteral   ); testParam( ut, "1"           , as); }
    { String    as( testSubstring       ); testParam( ut, testConstCharP, as); }
    { String    as( testAString         ); testParam( ut, testConstCharP, as); }
    { String    as( testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { String    as( testStdString       ); testParam( ut, testConstCharP, as); }
    { String    as( testMyString        ); testParam( ut, myStringBuf   , as); }

    { String    as( testConstString     ); testParam( ut, testConstCharP, as); }
    { String    as( testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { String    as( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { String    as( testConstAString    ); testParam( ut, testConstCharP, as); }
    { String    as( testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { String    as( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { String    as( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { String    as(&testString          ); testParam( ut, testConstCharP, as); }
    { String    as(&testStringLiteral   ); testParam( ut, "1"           , as); }
    { String    as(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { String    as(&testAString         ); testParam( ut, testConstCharP, as); }
    { String    as(&testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { String    as(&testStdString       ); testParam( ut, testConstCharP, as); }
    { String    as(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { String    as(&testConstString     ); testParam( ut, testConstCharP, as); }
    { String    as(&testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { String    as(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { String    as(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { String    as(&testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { String    as(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { String    as(&testConstMyString   ); testParam( ut, myStringBuf   , as); }

    // TString (no Substrings!)
    { TString as( "TEST"              ); testParam( ut, testConstCharP, as); }
    { TString as( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { TString as( testCharP           ); testParam( ut, testConstCharP, as); }

    { TString as( testString          ); testParam( ut, testConstCharP, as); }
    { TString as( testStringLiteral   ); testParam( ut, "1"           , as); }
    //{ TString as( testSubstring       ); testParam( ut, testConstCharP, as); }
    { TString as( testAString         ); testParam( ut, testConstCharP, as); }
    { TString as( testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { TString as( testStdString       ); testParam( ut, testConstCharP, as); }
    { TString as( testMyString        ); testParam( ut, myStringBuf   , as); }

    { TString as( testConstString     ); testParam( ut, testConstCharP, as); }
    { TString as( testConstStringLiteral  ); testParam( ut, "1"           , as); }
    //{ TString as( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { TString as( testConstAString    ); testParam( ut, testConstCharP, as); }
    { TString as( testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { TString as( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { TString as( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { TString as(&testString          ); testParam( ut, testConstCharP, as); }
    { TString as(&testStringLiteral   ); testParam( ut, "1"           , as); }
    //{ TString as(&testString          ); testParam( ut, testConstCharP, as); }
    { TString as(&testAString         ); testParam( ut, testConstCharP, as); }
    { TString as(&testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { TString as(&testStdString       ); testParam( ut, testConstCharP, as); }
    { TString as(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { TString as(&testConstString     ); testParam( ut, testConstCharP, as); }
    { TString as(&testConstStringLiteral  ); testParam( ut, "1"           , as); }
    //{ TString as(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { TString as(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { TString as(&testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { TString as(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { TString as(&testConstMyString   ); testParam( ut, myStringBuf   , as); }

    // AString
    { AString   as(  "TEST"             ); testParam( ut, testConstCharP, as); }
    { AString   as( L"TEST"             ); testParam( ut, testConstCharP, as); }
    { AString   as( testCharP           ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { AString   as( testWCharP          ); UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }
    { AString   as( testConstWCharP     ); UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }

    { AString   as( testChar            ); testParam( ut, "@",            as); }
    { AString   as( testWChar           ); UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { AString   as( testString          ); testParam( ut, testConstCharP, as); }
    { AString   as( testStringLiteral   ); testParam( ut, "1"           , as); }
    { AString   as( testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString   as( testAString         ); testParam( ut, testConstCharP, as); }
    { AString   as( testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { AString   as( testStdString       ); testParam( ut, testConstCharP, as); }
    { AString   as( testMyString        ); testParam( ut, myStringBuf   , as); }

    { AString   as( testConstChar       ); testParam( ut, "@",            as); }
    { AString   as( testConstWChar      ); UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { AString   as( testConstString     ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { AString   as( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString   as( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { AString   as(&testString          ); testParam( ut, testConstCharP, as); }
    { AString   as(&testStringLiteral   ); testParam( ut, "1"           , as); }
    { AString   as(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString   as(&testAString         ); testParam( ut, testConstCharP, as); }
    { AString   as(&testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { AString   as(&testStdString       ); testParam( ut, testConstCharP, as); }
    { AString   as(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { AString   as(&testConstString     ); testParam( ut, testConstCharP, as); }
    { AString   as(&testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { AString   as(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString   as(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString   as(&testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { AString   as(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString   as(&testConstMyString   ); testParam( ut, myStringBuf   , as); }

    // PreallocatedString
    { String64      as(  "TEST"             ); testParam( ut, testConstCharP, as); }
    { String64      as( L"TEST"             ); testParam( ut, testConstCharP, as); }
    { String64      as( testCharP           ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { String64      as( testWCharP          ); UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }
    { String64      as( testConstWCharP     ); UT_TRUE( as.ToWString( backTest, 1024 ) == 5 ); UT_EQ( backTest, testWCharP ); }

    { String64      as( testChar            ); testParam( ut, "@",            as); }
    { String64      as( testWChar           ); UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { String64      as( testString          ); testParam( ut, testConstCharP, as); }
    { String64      as( testStringLiteral   ); testParam( ut, "1"           , as); }
    { String64      as( testSubstring       ); testParam( ut, testConstCharP, as); }
    { String64      as( testAString         ); testParam( ut, testConstCharP, as); }
    { String64      as( testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { String64      as( testStdString       ); testParam( ut, testConstCharP, as); }
    { String64      as( testMyString        ); testParam( ut, myStringBuf   , as); }

    { String64      as( testConstChar       ); testParam( ut, "@",            as); }
    { String64      as( testConstWChar      ); UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { String64      as( testConstString     ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { String64      as( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstAString    ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { String64      as( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { String64      as(&testString          ); testParam( ut, testConstCharP, as); }
    { String64      as(&testStringLiteral   ); testParam( ut, "1"           , as); }
    { String64      as(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { String64      as(&testAString         ); testParam( ut, testConstCharP, as); }
    { String64      as(&testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { String64      as(&testStdString       ); testParam( ut, testConstCharP, as); }
    { String64      as(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { String64      as(&testConstString     ); testParam( ut, testConstCharP, as); }
    { String64      as(&testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { String64      as(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { String64      as(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { String64      as(&testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { String64      as(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { String64      as(&testConstMyString   ); testParam( ut, myStringBuf   , as); }

    // Substring
    { Substring as( "TEST"              ); testParam( ut, testConstCharP, as); }
    { Substring as( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { Substring as( testCharP           ); testParam( ut, testConstCharP, as); }

    { Substring as( testString          ); testParam( ut, testConstCharP, as); }
    { Substring as( testStringLiteral   ); testParam( ut, "1"           , as); }
    { Substring as( testSubstring       ); testParam( ut, testConstCharP, as); }
    { Substring as( testAString         ); testParam( ut, testConstCharP, as); }
    { Substring as( testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { Substring as( testStdString       ); testParam( ut, testConstCharP, as); }
    { Substring as( testMyString        ); testParam( ut, myStringBuf   , as); }

    { Substring as( testConstString     ); testParam( ut, testConstCharP, as); }
    { Substring as( testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { Substring as( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { Substring as( testConstAString    ); testParam( ut, testConstCharP, as); }
    { Substring as( testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { Substring as( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { Substring as( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { Substring as(&testString          ); testParam( ut, testConstCharP, as); }
    { Substring as(&testStringLiteral   ); testParam( ut, "1"           , as); }
    { Substring as(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { Substring as(&testAString         ); testParam( ut, testConstCharP, as); }
    { Substring as(&testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { Substring as(&testStdString       ); testParam( ut, testConstCharP, as); }
    { Substring as(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { Substring as(&testConstString     ); testParam( ut, testConstCharP, as); }
    { Substring as(&testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { Substring as(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { Substring as(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { Substring as(&testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { Substring as(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { Substring as(&testConstMyString   ); testParam( ut, myStringBuf   , as); }
}


UT_METHOD( ConstructorsImplicit )

    const char*              testConstCharP= "TEST";
    char*                    testCharP=      (char*) testConstCharP;
    std::string              testStdString   (testConstCharP);
    AString                  testAString     (testConstCharP);
    SLiteral<1>              testStringLiteral("1");
    Substring              testSubstring   ( testConstCharP );
    String32                 testPreallocatedString  ( testConstCharP );
    myns::MyString           testMyString;

    const std::string        testConstStdString   (testConstCharP);
    const AString            testConstAString     (testConstCharP);
    const SLiteral<1>        testConstStringLiteral("1");
    const Substring        testConstSubstring   ( testConstCharP );
    const String32           testConstPreallocatedString  ( testConstCharP );
    const myns::MyString     testConstMyString;

    const char* myStringBuf= testMyString.GetMyBuffer();

    // implicit String
    {
       testParam( ut, testConstCharP,     "TEST"               );
       testParam( ut, testConstCharP,     testConstCharP       );
       testParam( ut, testConstCharP,     testCharP            );

       testParam( ut, "1",                testStringLiteral    );
       testParam( ut, testConstCharP,     testSubstring        );
       testParam( ut, testConstCharP,     testAString          );
       testParam( ut, testConstCharP,     testPreallocatedString       );
       testParam( ut, testConstCharP,     testStdString        );
       testParam( ut, myStringBuf   ,     testMyString         );

       testParam( ut, "1",                testConstStringLiteral);
       testParam( ut, testConstCharP,     testConstSubstring   );
       testParam( ut, testConstCharP,     testConstAString     );
       testParam( ut, testConstCharP,     testConstPreallocatedString  );
       testParam( ut, myStringBuf   ,     testConstMyString    );

       testParam( ut, "1",               &testStringLiteral    );
       testParam( ut, testConstCharP,    &testSubstring        );
       testParam( ut, testConstCharP,    &testAString          );
       testParam( ut, testConstCharP,    &testPreallocatedString       );
       testParam( ut, testConstCharP,    &testStdString        );
       testParam( ut, myStringBuf   ,    &testMyString         );

       testParam( ut, "1",               &testConstStringLiteral);
       testParam( ut, testConstCharP,    &testConstSubstring   );
       testParam( ut, testConstCharP,    &testConstAString     );
       testParam( ut, testConstCharP,    &testConstPreallocatedString  );
       testParam( ut, testConstCharP,    &testConstStdString   );
       testParam( ut, myStringBuf   ,    &testConstMyString    );
    }

    // implicit SubString
    {
       testParamSubstring( ut, testConstCharP,     "TEST"               );
       testParamSubstring( ut, testConstCharP,     testConstCharP       );
       testParamSubstring( ut, testConstCharP,     testCharP            );

       testParamSubstring( ut, "1",                testStringLiteral    );
       testParamSubstring( ut, testConstCharP,     testSubstring        );
       testParamSubstring( ut, testConstCharP,     testAString          );
       testParamSubstring( ut, testConstCharP,     testPreallocatedString       );
       testParamSubstring( ut, testConstCharP,     testStdString        );
       testParamSubstring( ut, myStringBuf   ,     testMyString         );

       testParamSubstring( ut, "1",                testConstStringLiteral);
       testParamSubstring( ut, testConstCharP,     testConstSubstring   );
       testParamSubstring( ut, testConstCharP,     testConstAString     );
       testParamSubstring( ut, testConstCharP,     testConstPreallocatedString  );
       testParamSubstring( ut, myStringBuf   ,     testConstMyString    );

       testParamSubstring( ut, "1",               &testStringLiteral    );
       testParamSubstring( ut, testConstCharP,    &testSubstring        );
       testParamSubstring( ut, testConstCharP,    &testAString          );
       testParamSubstring( ut, testConstCharP,    &testPreallocatedString       );
       testParamSubstring( ut, testConstCharP,    &testStdString        );
       testParamSubstring( ut, myStringBuf   ,    &testMyString         );

       testParamSubstring( ut, "1",               &testConstStringLiteral);
       testParamSubstring( ut, testConstCharP,    &testConstSubstring   );
       testParamSubstring( ut, testConstCharP,    &testConstAString     );
       testParamSubstring( ut, testConstCharP,    &testConstPreallocatedString  );
       testParamSubstring( ut, testConstCharP,    &testConstStdString   );
       testParamSubstring( ut, myStringBuf   ,    &testConstMyString    );
    }

    // implicit TString
    {
       testParamTerminatable( ut, testConstCharP,     "TEST"               );
       testParamTerminatable( ut, testConstCharP,     testConstCharP       );
       testParamTerminatable( ut, testConstCharP,     testCharP            );

       testParamTerminatable( ut, "1",                testStringLiteral    );
       //Substrings are not allowed!  testParamTerminatable( ut, testConstCharP,     testSubstring        );
       testParamTerminatable( ut, testConstCharP,     testAString          );
       testParamTerminatable( ut, testConstCharP,     testPreallocatedString       );
       testParamTerminatable( ut, testConstCharP,     testStdString        );
       testParamTerminatable( ut, myStringBuf   ,     testMyString         );

       testParamTerminatable( ut, "1",                testConstStringLiteral);
       //Substrings are not allowed!  testParamTerminatable( ut, testConstCharP,     testConstSubstring   );
       testParamTerminatable( ut, testConstCharP,     testConstAString     );
       testParamTerminatable( ut, testConstCharP,     testConstPreallocatedString  );
       testParamTerminatable( ut, testConstCharP,     testConstStdString   );
       testParamTerminatable( ut, myStringBuf   ,     testConstMyString    );

       testParamTerminatable( ut, "1",               &testStringLiteral    );
       //Substrings are not allowed!  testParamTerminatable( ut, testConstCharP,    &testSubstring        );
       testParamTerminatable( ut, testConstCharP,    &testAString          );
       testParamTerminatable( ut, testConstCharP,    &testPreallocatedString       );
       testParamTerminatable( ut, testConstCharP,    &testStdString        );
       testParamTerminatable( ut, myStringBuf   ,    &testMyString         );

       testParamTerminatable( ut, "1",               &testConstStringLiteral);
       testParamTerminatable( ut, testConstCharP,    &testConstAString     );
       //Substrings are not allowed!  testParamTerminatable( ut, testConstCharP,    &testConstSubstring   );
       testParamTerminatable( ut, testConstCharP,    &testConstPreallocatedString  );
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
    SLiteral<1>              testStringLiteral    ("1");
    Substring                testSubstring        ( "@TEST@",1,4 );
    String32                 testPreallocatedString       ( testConstCharP );
    myns::MyString           testMyString;

    const std::string        testConstStdString   (testConstCharP);
    const AString            testConstAString     (testConstCharP);
    const SLiteral<1>        testConstStringLiteral("1");
    const Substring          testConstSubstring   ( "@TEST@",1,4 );
    const String32           testConstPreallocatedString  ( testConstCharP );
    const myns::MyString     testConstMyString;

    const char* myStringBuf= testMyString.GetMyBuffer();

    // String
    { String        as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { String        as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { String        as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { String        as=  testStringLiteral   ; testParam( ut, "1"           , as); }
    { String        as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { String        as=  testAString         ; testParam( ut, testConstCharP, as); }
    { String        as=  testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { String        as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { String        as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { String        as=  testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { String        as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String        as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { String        as=  testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { String        as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String        as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { String        as= &testStringLiteral   ; testParam( ut, "1"           , as); }
    { String        as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { String        as= &testAString         ; testParam( ut, testConstCharP, as); }
    { String        as= &testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { String        as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { String        as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { String        as= &testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { String        as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String        as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { String        as= &testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { String        as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String        as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { String    as; as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { String    as; as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { String    as; as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { String    as; as=  testStringLiteral   ; testParam( ut, "1"           , as); }
    { String    as; as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { String    as; as=  testAString         ; testParam( ut, testConstCharP, as); }
    { String    as; as=  testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { String    as; as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { String    as; as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { String    as; as=  testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { String    as; as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String    as; as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { String    as; as=  testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { String    as; as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String    as; as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { String    as; as= &testStringLiteral   ; testParam( ut, "1"           , as); }
    { String    as; as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { String    as; as= &testAString         ; testParam( ut, testConstCharP, as); }
    { String    as; as= &testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { String    as; as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { String    as; as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { String    as; as= &testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { String    as; as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String    as; as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { String    as; as= &testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { String    as; as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String    as; as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }


    // Substring
    { Substring          as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { Substring          as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { Substring          as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { Substring          as=  testStringLiteral   ; testParam( ut, "1"           , as); }
    { Substring          as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { Substring          as=  testAString         ; testParam( ut, testConstCharP, as); }
    { Substring          as=  testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { Substring          as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { Substring          as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { Substring          as=  testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { Substring          as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { Substring          as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { Substring          as=  testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { Substring          as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { Substring          as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { Substring          as= &testStringLiteral   ; testParam( ut, "1"           , as); }
    { Substring          as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { Substring          as= &testAString         ; testParam( ut, testConstCharP, as); }
    { Substring          as= &testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { Substring          as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { Substring          as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { Substring          as= &testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { Substring          as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { Substring          as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { Substring          as= &testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { Substring          as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { Substring          as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { Substring      as; as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { Substring      as; as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { Substring      as; as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { Substring      as; as=  testStringLiteral   ; testParam( ut, "1"           , as); }
    { Substring      as; as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { Substring      as; as=  testAString         ; testParam( ut, testConstCharP, as); }
    { Substring      as; as=  testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { Substring      as; as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { Substring      as; as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { Substring      as; as=  testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { Substring      as; as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { Substring      as; as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { Substring      as; as=  testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { Substring      as; as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { Substring      as; as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { Substring      as; as= &testStringLiteral   ; testParam( ut, "1"           , as); }
    { Substring      as; as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { Substring      as; as= &testAString         ; testParam( ut, testConstCharP, as); }
    { Substring      as; as= &testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { Substring      as; as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { Substring      as; as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { Substring      as; as= &testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { Substring      as; as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { Substring      as; as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { Substring      as; as= &testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { Substring      as; as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { Substring      as; as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    // TString (no Substrings!)
    { TString     as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { TString     as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { TString     as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { TString     as=  testStringLiteral   ; testParam( ut, "1"           , as); }
    //{ TString   as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { TString     as=  testAString         ; testParam( ut, testConstCharP, as); }
    { TString     as=  testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { TString     as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { TString     as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { TString     as=  testConstStringLiteral  ; testParam( ut, "1"           , as); }
    //{ TString   as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { TString     as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { TString     as=  testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { TString     as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { TString     as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { TString     as= &testStringLiteral   ; testParam( ut, "1"           , as); }
    //{ TString   as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { TString     as= &testAString         ; testParam( ut, testConstCharP, as); }
    { TString     as= &testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { TString     as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { TString     as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { TString     as= &testConstStringLiteral  ; testParam( ut, "1"           , as); }
    //{ TString   as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { TString     as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { TString     as= &testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { TString     as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { TString     as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { TString as; as=  "TEST"              ; testParam( ut, testConstCharP, as); }
    { TString as; as=  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { TString as; as=  testCharP           ; testParam( ut, testConstCharP, as); }

    { TString as; as=  testStringLiteral   ; testParam( ut, "1"           , as); }
    //{ TString as; as=testSubstring       ; testParam( ut, testConstCharP, as); }
    { TString as; as=  testAString         ; testParam( ut, testConstCharP, as); }
    { TString as; as=  testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { TString as; as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { TString as; as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { TString as; as=  testConstStringLiteral  ; testParam( ut, "1"           , as); }
    //{ TString as; as=testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { TString as; as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { TString as; as=  testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { TString as; as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { TString as; as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { TString as; as= &testStringLiteral   ; testParam( ut, "1"           , as); }
    //{ TString as;as=&testSubstring       ; testParam( ut, testConstCharP, as); }
    { TString as; as= &testAString         ; testParam( ut, testConstCharP, as); }
    { TString as; as= &testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { TString as; as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { TString as; as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { TString as; as= &testConstStringLiteral  ; testParam( ut, "1"           , as); }
    //{ TString as;as=&testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { TString as; as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { TString as; as= &testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { TString as; as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { TString as; as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

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
    { AString        as; as=  testStringLiteral   ; testParam( ut, "1"           , as); }
    { AString        as; as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testAString         ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { AString        as; as=  testConstChar       ; testParam( ut, "@",            as); }
    { AString        as; as=  testConstWChar      ; UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { AString        as; as=  testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { AString        as; as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AString        as; as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { AString        as; as= &testStringLiteral   ; testParam( ut, "1"           , as); }
    { AString        as; as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testAString         ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { AString        as; as= &testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { AString        as; as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AString        as; as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    // PreallocatedString
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
    { String32           as; as=  testStringLiteral   ; testParam( ut, "1"           , as); }
    { String32           as; as=  testSubstring       ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testAString         ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testStdString       ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testMyString        ; testParam( ut, myStringBuf   , as); }

    { String32           as; as=  testConstChar       ; testParam( ut, "@",            as); }
    { String32           as; as=  testConstWChar      ; UT_TRUE( as.ToWString( backTest, 1024 + 1 ) == 1 ); UT_TRUE( backTest[0] == testWChar ); }
    { String32           as; as=  testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { String32           as; as=  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testConstAString    ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String32           as; as=  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { String32           as; as= &testStringLiteral   ; testParam( ut, "1"           , as); }
    { String32           as; as= &testSubstring       ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testAString         ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testStdString       ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testMyString        ; testParam( ut, myStringBuf   , as); }

    { String32           as; as= &testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { String32           as; as= &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testConstAString    ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String32           as; as= &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    // StringLiteral
    { SLiteral<4>        as=  "TEST"                  ; testParam( ut, testConstCharP, as); }
}

//---------------------------------------------------------------------------------------------------------
//--- Append and operator <<
//---------------------------------------------------------------------------------------------------------
UT_METHOD( AppendAndAppendOperator )

    const char*              testConstCharP= "TEST";
    char*                    testCharP=       (char*) testConstCharP;
    std::string              testStdString    (testConstCharP);
    AString                  testAString      (testConstCharP);
    SLiteral<1>              testStringLiteral("1");
    Substring                testSubstring    ( "@TEST@",1,4 );
    String32                 testPreallocatedString  ( testConstCharP );
    myns::MyString           testMyString;

    const std::string        testConstStdString    (testConstCharP);
    const AString            testConstAString      (testConstCharP);
    const SLiteral<1>        testConstStringLiteral("1");
    const Substring          testConstSubstring    ( "@TEST@",1,4 );
    const String32           testConstPreallocatedString  ( testConstCharP );
    const myns::MyString     testConstMyString;

    const char* myStringBuf= testMyString.GetMyBuffer();

    // these have to fail
    // { vector<int> x;             String as(x);}
    // { vector<int> x; AString as; as._ (x);}
    // { char c   ='a';             String as(c);}

    TicksCalendarTime calendar;
    calendar.Day=     1;
    calendar.Month=   4;
    calendar.Year=    2011;
    calendar.Hour=    16;
    calendar.Minute=  00;
    calendar.Second=  01;
    Ticks         testTicks(calendar.Get(Timezone::UTC));
    const Ticks   testConstTicks  ( testTicks );
    const char* ticksResult= "2011-04-01 16:00";

    // AString
    { AString as; as <<  "TEST"              ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testCharP           ; testParam( ut, testConstCharP, as); }

    { AString as; as <<  testStringLiteral   ; testParam( ut, "1"           , as); }
    { AString as; as <<  testSubstring       ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testAString         ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testStdString       ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testMyString        ; testParam( ut, myStringBuf   , as); }
    { AString as; as <<  testTicks           ; testParam( ut, ticksResult,    as); }

    { AString as; as <<  testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { AString as; as <<  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testConstAString    ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AString as; as <<  testConstMyString   ; testParam( ut, myStringBuf   , as); }
    { AString as; as <<  testConstTicks      ; testParam( ut, ticksResult,    as); }

    { AString as; as << &testStringLiteral   ; testParam( ut, "1"           , as); }
    { AString as; as << &testSubstring       ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testAString         ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testStdString       ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testMyString        ; testParam( ut, myStringBuf   , as); }
    { AString as; as << &testTicks           ; testParam( ut, ticksResult,    as); }

    { AString as; as << &testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { AString as; as << &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testConstAString    ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { AString as; as << &testConstMyString   ; testParam( ut, myStringBuf   , as); }
    { AString as; as << &testConstTicks      ; testParam( ut, ticksResult,    as); }

    { AString as; as._( "TEST"              ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testCharP           ); testParam( ut, testConstCharP, as); }

    { AString as; as._( testStringLiteral   ); testParam( ut, "1"           , as); }
    { AString as; as._( testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testAString         ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testStdString       ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testMyString        ); testParam( ut, myStringBuf   , as); }
    { AString as; as._( testTicks           ); testParam( ut, ticksResult,    as); }

    { AString as; as._( testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { AString as; as._( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString as; as._( testConstMyString   ); testParam( ut, myStringBuf   , as); }
    { AString as; as._( testConstTicks      ); testParam( ut, ticksResult,    as); }

    { AString as; as._(&testStringLiteral   ); testParam( ut, "1"           , as); }
    { AString as; as._(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testAString         ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testStdString       ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testMyString        ); testParam( ut, myStringBuf   , as); }
    { AString as; as._(&testTicks           ); testParam( ut, ticksResult,    as); }

    { AString as; as._(&testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { AString as; as._(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString as; as._(&testConstMyString   ); testParam( ut, myStringBuf   , as); }
    { AString as; as._(&testConstTicks      ); testParam( ut, ticksResult,    as); }

    { AString as; as._<false>( "TEST"              ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testCharP           ); testParam( ut, testConstCharP, as); }

    { AString as; as._<false>( testStringLiteral   ); testParam( ut, "1"           , as); }
    { AString as; as._<false>( testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testAString         ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testStdString       ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testMyString        ); testParam( ut, myStringBuf   , as); }
    { AString as; as._<false>( testTicks           ); testParam( ut, ticksResult,    as); }

    { AString as; as._<false>( testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { AString as; as._<false>( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>( testConstMyString   ); testParam( ut, myStringBuf   , as); }
    { AString as; as._<false>( testConstTicks      ); testParam( ut, ticksResult,    as); }

    { AString as; as._<false>(&testStringLiteral   ); testParam( ut, "1"           , as); }
    { AString as; as._<false>(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testAString         ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testStdString       ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testMyString        ); testParam( ut, myStringBuf   , as); }
    { AString as; as._<false>(&testTicks           ); testParam( ut, ticksResult,    as); }

    { AString as; as._<false>(&testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { AString as; as._<false>(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { AString as; as._<false>(&testConstMyString   ); testParam( ut, myStringBuf   , as); }
    { AString as; as._<false>(&testConstTicks      ); testParam( ut, ticksResult,    as); }

    // PreallocatedString
    { String64    as; as <<  "TEST"              ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testConstCharP      ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testCharP           ; testParam( ut, testConstCharP, as); }

    { String64    as; as <<  testStringLiteral   ; testParam( ut, "1"           , as); }
    { String64    as; as <<  testSubstring       ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testAString         ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testStdString       ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testMyString        ; testParam( ut, myStringBuf   , as); }

    { String64    as; as <<  testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { String64    as; as <<  testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testConstAString    ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String64    as; as <<  testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { String64    as; as << &testStringLiteral   ; testParam( ut, "1"           , as); }
    { String64    as; as << &testSubstring       ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testAString         ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testPreallocatedString      ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testStdString       ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testMyString        ; testParam( ut, myStringBuf   , as); }

    { String64    as; as << &testConstStringLiteral  ; testParam( ut, "1"           , as); }
    { String64    as; as << &testConstSubstring  ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testConstAString    ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testConstPreallocatedString ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testConstStdString  ; testParam( ut, testConstCharP, as); }
    { String64    as; as << &testConstMyString   ; testParam( ut, myStringBuf   , as); }

    { String64    as; as._( "TEST"              ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testConstCharP      ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testCharP           ); testParam( ut, testConstCharP, as); }

    { String64    as; as._( testStringLiteral   ); testParam( ut, "1"           , as); }
    { String64    as; as._( testSubstring       ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testAString         ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testStdString       ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testMyString        ); testParam( ut, myStringBuf   , as); }

    { String64    as; as._( testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { String64    as; as._( testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testConstAString    ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testConstStdString  ); testParam( ut, testConstCharP, as); }
    { String64    as; as._( testConstMyString   ); testParam( ut, myStringBuf   , as); }

    { String64    as; as._(&testStringLiteral   ); testParam( ut, "1"           , as); }
    { String64    as; as._(&testSubstring       ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testAString         ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testPreallocatedString      ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testStdString       ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testMyString        ); testParam( ut, myStringBuf   , as); }

    { String64    as; as._(&testConstStringLiteral  ); testParam( ut, "1"           , as); }
    { String64    as; as._(&testConstSubstring  ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testConstAString    ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testConstPreallocatedString ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testConstStdString  ); testParam( ut, testConstCharP, as); }
    { String64    as; as._(&testConstMyString   ); testParam( ut, myStringBuf   , as); }

}


//---------------------------------------------------------------------------------------------------------
//--- Move constructors
//---------------------------------------------------------------------------------------------------------
UT_METHOD( MoveConstructors )

    lib::Report::GetDefault().PushHaltFlags( false, false );

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
    lib::Report::GetDefault().PopHaltFlags();

}
UT_CLASS_END

} //namespace
