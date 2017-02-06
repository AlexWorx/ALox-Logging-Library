// #################################################################################################
//  aworx - Unit Tests
//  Private, not published in git ( I hope! )
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"

#include "alib.unittests/aworx_unittests.hpp"
#define TESTCLASSNAME       CPP_ALib__Dox


#if defined(__clang__)
    #pragma clang diagnostic ignored "-Wmissing-prototypes"
    #pragma clang diagnostic ignored "-Wunused-variable"
    #pragma clang diagnostic ignored "-Wold-style-cast"
    #pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#elif defined(_MSC_VER)
    #pragma warning( disable:4100 ) // unreferenced formal parameter

#endif


//--------------------------------------------------------------------------------------------------
//--- DOCUMENTATION SAMPLES
//--------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include "alib/compatibility/std_iostream.hpp"
#include "alib/compatibility/std_string.hpp"

namespace std
{
    extern stringstream testOutputStream; // declaration (needed when clang warnings are on)
    stringstream testOutputStream;
}
#define cout testOutputStream
using namespace std;
using namespace aworx::literals;

// ###################################    intGap_t    #############################################
namespace dox_lang_complete_specialization {

//! [DOX_ALIB_LANG_INTEGER_LITERAL]

aworx::integer myInt= 42_integer;

//! [DOX_ALIB_LANG_INTEGER_LITERAL]


//! [DOX_ALIB_LANG_INTXX_DECLARATION]

// Template function
template <typename TInteger> const char* MyFunc(TInteger val) { return "NOT IMPLEMENTED"; }

// Specializations for integer types
template<> const char* MyFunc(  int8_t  ) { return "Type=  int8_t "; }
template<> const char* MyFunc( uint8_t  ) { return "Type= uint8_t "; }
template<> const char* MyFunc(  int16_t ) { return "Type=  int16_t"; }
template<> const char* MyFunc( uint16_t ) { return "Type= uint16_t"; }
template<> const char* MyFunc(  int32_t ) { return "Type=  int32_t"; }
template<> const char* MyFunc( uint32_t ) { return "Type= uint32_t"; }
template<> const char* MyFunc(  int64_t ) { return "Type=  int64_t"; }
template<> const char* MyFunc( uint64_t ) { return "Type= uint64_t"; }

// TestMethod
void test()
{
    // test std int types
    cout << " int8_t           : " << MyFunc( ( int8_t )           0 ) << endl; // OK
    cout << "uint8_t           : " << MyFunc( (uint8_t )           0 ) << endl; // OK
    cout << " int16_t          : " << MyFunc( ( int16_t)           0 ) << endl; // OK
    cout << "uint16_t          : " << MyFunc( (uint16_t)           0 ) << endl; // OK
    cout << " int32_t          : " << MyFunc( ( int32_t)           0 ) << endl; // OK
    cout << "uint32_t          : " << MyFunc( (uint32_t)           0 ) << endl; // OK
    cout << " int64_t          : " << MyFunc( ( int64_t)           0 ) << endl; // OK
    cout << "uint64_t          : " << MyFunc( (uint64_t)           0 ) << endl; // OK
    cout << endl;

    // test 'language' types
    cout << "         long     : " << MyFunc( (         long     ) 0 ) << endl; // Gap on common 32-bit platforms and 64-bit MSVC
    cout << "unsigned long     : " << MyFunc( (unsigned long     ) 0 ) << endl; // Gap on common 32-bit platforms and 64-bit MSVC
    cout << endl;
    cout << "         long long: " << MyFunc( (         long long) 0 ) << endl; // Gap on 64-Bit GNU C++
    cout << "unsigned long long: " << MyFunc( (unsigned long long) 0 ) << endl; // Gap on 64-Bit GNU C++
    cout << endl;

    // further info
    cout << endl;
    cout << "sizeof(         long     )= " << sizeof(         long     ) << endl;
    cout << "sizeof(unsigned long     )= " << sizeof(unsigned long     ) << endl;
    cout << endl;
    cout << "sizeof(         long long)= " << sizeof(         long long) << endl;
    cout << "sizeof(unsigned long long)= " << sizeof(unsigned long long) << endl;
}

//! [DOX_ALIB_LANG_INTXX_DECLARATION]

}//namespace dox_lang_complete_specialization

namespace dox_lang_complete_specialization2 {

template <typename TInteger> const char* MyFunc(TInteger val) { return "NOT IMPLEMENTED"; }

//! [DOX_ALIB_LANG_INTXX_DECLARATION2]
template<> const char* MyFunc( aworx:: intGap_t ) { return "Type=  intGap_t"; }
template<> const char* MyFunc( aworx::uintGap_t ) { return "Type= uintGap_t"; }
//! [DOX_ALIB_LANG_INTXX_DECLARATION2]
}//namespace dox_lang_complete_specialization2


// ###################################    Singleton    #############################################
namespace dox_lang_singleton
{
    extern void test();
}

// ###################################   Test Class   #############################################
namespace ut_aworx {

UT_CLASS()


    UT_METHOD( lang_IntXX )
    {
        UT_INIT();

        UT_PRINT("*** Documentation Sample +**")

        dox_lang_complete_specialization::test();
        ut.WriteResultFile( "DOX_ALIB_LANG_INTXX.txt", testOutputStream.str(), "//! [OUTPUT]" );
        testOutputStream.str("");


        dox_lang_singleton::test();
        testOutputStream.str("");
    }

UT_CLASS_END

}; //namespace




