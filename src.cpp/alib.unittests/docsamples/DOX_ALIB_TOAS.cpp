// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"


#define TESTCLASSNAME       CPP_ALib__Dox


//--------------------------------------------------------------------------------------------------
//--- DOCUMENTATION SAMPLEs
//--------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
namespace std { stringstream testOutputStream1; }
#define cout testOutputStream1


//! [DOX_ALIB_TOAS]
#include "alib/alib.hpp"

#include "alib/compatibility/std_iostream.hpp"

// get support for using std::strings with ALib strings
#include "alib/compatibility/std_string.hpp"

#include <iostream>
#include <iomanip>

using namespace std;
using namespace aworx;

//
// user defined string class sample
//
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

//
// Partial template method implementation (has to be declared in namespace aworx::lib::strings)
// Use "constexpr" when possible, otherwise "inline"
//
namespace aworx { namespace lib { namespace strings {

    // specialize ToStringDefined, to enable static_assert in String construction to success for MyString class
    template<> struct              ToStringDefined <const myns::MyString&> : public std::true_type {};

    // the two implementations of ToString. One for providing the buffer, one for the length
    template<> inline  const char* ToString        <const myns::MyString&>( const myns::MyString& src )
    {
        return  src.GetMyBuffer();
    }

    template<> inline  int         ToString        <const myns::MyString&>( const myns::MyString& src )
    {
        return  src.GetMyLength();
    }

    // to be capable of also using MyString for append operations with class AString, we
    // do a similar partial template method implementation for AString.
    // (These two usually go together)
    template<> struct              IsApplicable<const myns::MyString&> : public std::true_type {};
    template<> inline  int         ApplyTo( AString& target, const myns::MyString& src )
    {
        if ( src.IsNulled() )
            return -1;

        target.Append<false>( src.GetMyBuffer(), src.GetMyLength() );

        return src.GetMyLength();
    }

}}} // namespace aworx::lib::strings

//
// Defining a test method that takes a const reference to String
//

void Print( const aworx::String& text )
{
    std::cout << "Print: " << text << std::endl;
}

//
// Using it
//
void MyFunction()
{
    // using method Print with core string types
    Print( "From string literal (no strlen() performed)" );

    const char* cc= "From 'char *' (strlen() is performed)";
    Print( cc );

    // using method Print with std::string types. This is possible, because we included
    // "alib/compatibility/std_string.hpp" above
    std::string std_string( "From std::string" );
    Print( std_string );

    // using method Print with MyString
    myns::MyString myString;
    Print( myString );

    // ...this also works with pointers
    Print( &myString );

    // Now, as we have also implemented "IsApplicable" and "ApplyTo" for MyString, we can easily
    // append them to objects of class AString
    aworx::AString as;
    as._(myString);
    as << myString;
    as << &myString; // again, works with pointers
}
//! [DOX_ALIB_TOAS]
#undef cout
namespace std { stringstream testOutputStream2; }
#define cout testOutputStream2
#undef HPP_ALIB_COMPATIBILITY_STD_IOSTREAM // be

//----------- Now to the unit tests -------------
#include "alib.unittests/aworx_unittests.hpp"
#include "alib/strings/tokenizer.hpp"
#include "alib/strings/numberformat.hpp"

namespace ut_aworx {


UT_CLASS()

UT_METHOD( DOX_ALIB_TOAS )
{
    UT_INIT();

    MyFunction();
    ut.WriteResultFile( "DOX_ALIB_TOAS.txt", testOutputStream1.str(), "//! [OUTPUT]" );

//! [DOX_ALIB_AS_DIRECTORY]
// Creating Directory object from C++ string literal
Directory bin( "/usr/bin" );

// Creating Directory object from std::string
std::string libPath( "/usr/lib" );
Directory lib( libPath );

// Creating Directory object from std::string given as pointer
Directory lib2( &libPath );

// Creating Directory object from ALib AString
aworx::AString srcPath( "/usr/src" );
Directory src( srcPath );

// Creating Directory object from ALib AString given as pointer
Directory src2( &srcPath );
//! [DOX_ALIB_AS_DIRECTORY]


}


UT_CLASS_END

} //namespace
