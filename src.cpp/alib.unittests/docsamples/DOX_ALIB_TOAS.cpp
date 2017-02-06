// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"


#define TESTCLASSNAME       CPP_ALib__Dox


//--------------------------------------------------------------------------------------------------
//--- DOCUMENTATION SAMPLES
//--------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>

namespace std
{
    extern stringstream testOutputStream1; // declaration (needed when clang warnings are on)
    stringstream testOutputStream1;
}
#define cout testOutputStream1

void MyFunction();


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
            inline     size_t       GetMyLength() const { return strlen( theString ); }
    };

}

//
// Template struct specialization (has to be made in namespace aworx::lib::strings)
//
namespace aworx { namespace lib { namespace strings {

    // specialize T_String struct for String creation
    template<> struct T_String <myns::MyString> : public std::true_type
    {
        static inline const char* Buffer( const myns::MyString& src )  { return  src.GetMyBuffer();  }
        static inline integer    Length( const myns::MyString& src )  { return  static_cast<integer>( src.GetMyLength() );  }
    };

}}} // namespace aworx::lib::strings

//
// Defining a test method that takes a const reference to String
//

void Print( const aworx::String& text );
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

    // Method AString::Apply also checks for struct T_String, hence we can apply MyString objects
    // to objects of class AString!
    aworx::AString as(myString);
    as                 << "<- constructor,   ";
    as <<  myString    << "<- applied as reference,    ";
    as << &myString    << "<- applied as pointer";         // again, works with pointers
    Print( as );
}
//! [DOX_ALIB_TOAS]
#undef cout

//----------- Now to the unit tests -------------
#include "alib.unittests/aworx_unittests.hpp"

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
