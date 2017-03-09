// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"

#include "alib/strings/util/tokenizer.hpp"
#include "alib/strings/numberformat.hpp"
#include "alib/compatibility/std_string.hpp"
#include "alib/compatibility/std_vector.hpp"
#include "alib/compatibility/std_iostream.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>


#include "aworx_unittests.hpp"


#define TESTCLASSNAME       CPP_ALib_Compatibility


using namespace std;
using namespace aworx;

namespace ut_aworx {


UT_CLASS()

//--------------------------------------------------------------------------------------------------
//--- Std_String
//--------------------------------------------------------------------------------------------------
UT_METHOD( Std_String )
{
    UT_INIT();

    UT_PRINT( String128() << "std::String toUtf8() " );
    UT_PRINT( String128() << "  std::wstring: German:  " << std::wstring( L"ÄÜÖäüöß") );
    UT_PRINT( String128() << "  std::wstring: Greek:   " << std::wstring( L"\u03B1\u03B2\u03B3\u03B4\u03B5") );
    UT_PRINT( String256() << "  std::wstring: Smileys: " << std::wstring( L"\U0001F609 * \U0001F607 * \U0001F603 * \U0001F60E * "
                                                                           "\U00000361\U000000b0\U0000035c\U00000296\U00000361\U000000b0") );

    AString test;
    std::string       str(  "std::string" );
    std::wstring     wStr( L"std::wstring"   );
    std::u16string u16Str( u"std::u16string" );
    std::u32string u32Str( U"std::u32string" );

    test._().Append(     str.c_str(), static_cast<integer>(    str.length()));  UT_EQ( "std::string"    , test );
    test._() <<          str;                                                    UT_EQ( "std::string"    , test );
    test._()._<true>   ( str);                                                   UT_EQ( "std::string"    , test );
    test._()._<false>  ( str);                                                   UT_EQ( "std::string"    , test );

    test._().Append(    wStr.c_str(), static_cast<integer>(   wStr.length()));  UT_EQ( "std::wstring"   , test );
    test._() <<         wStr;                                                    UT_EQ( "std::wstring"   , test );
    test._()._<true>  ( wStr);                                                   UT_EQ( "std::wstring"   , test );
    test._()._<false> ( wStr);                                                   UT_EQ( "std::wstring"   , test );

    test._().Append(  u16Str.c_str(), static_cast<integer>( u16Str.length()));  UT_EQ( "std::u16string" , test );
    test._() <<       u16Str;                                                    UT_EQ( "std::u16string" , test );
    test._()._<true> (u16Str);                                                   UT_EQ( "std::u16string" , test );
    test._()._<false>(u16Str);                                                   UT_EQ( "std::u16string" , test );

    test._().Append(  u32Str.c_str(), static_cast<integer>( u32Str.length()));  UT_EQ( "std::u32string" , test );
    test._() <<       u32Str;                                                    UT_EQ( "std::u32string" , test );
    test._()._<true> (u32Str);                                                   UT_EQ( "std::u32string" , test );
    test._()._<false>(u32Str);                                                   UT_EQ( "std::u32string" , test );
}


//--------------------------------------------------------------------------------------------------
//--- Std_Vector
//--------------------------------------------------------------------------------------------------
UT_METHOD( Std_Vector )
{
    UT_INIT();

    // Creating a String from std::vector
    {
        std::vector<char> vec= {'a', 'b', 'c', };    UT_EQ( String( "abc"  ), String( vec ) );
        vec.push_back( 'd');                         UT_EQ( String( "abcd" ), String( vec ) );
        vec.clear();                                 UT_EQ( String( "" ),     String( vec ) );
                                                     UT_TRUE ( String( vec ).IsEmpty() );
                                                     UT_FALSE( String( vec ).IsNull()  );
                                                     UT_TRUE ( String( std::vector<char>() ).IsEmpty() );
                                                     UT_TRUE ( String( std::vector<char>() ).IsNull () );
    }

    // appending std::vector<char> to AString
    {
        AString as;
        std::vector<char> vec= {'a', 'b', 'c', };
        as << vec;
        UT_EQ( vec, as );
        UT_EQ( "abc"   , as );
    }

    // appending std::vector<wchar_t> to AString
    {
        AString as;
        std::vector<wchar_t> vec= { 'a', 'b', 'c', };
        as << vec;
        UT_EQ( "abc"   , as );
    }

    // appending std::vector<char16_t> to AString
    {
        AString as;
        std::vector<char16_t> vec= { u'a', u'b', u'c', };
        as << vec;
        UT_EQ( "abc"   , as );
    }

    // appending std::vector<char32_t> to AString
    {
        AString as;
        std::vector<char32_t> vec= { U'a', U'b', U'c', };
        as << vec;
        UT_EQ( "abc"   , as );
    }

    // Creating a vector from aworx::String
    {
        AString as( "abc" );
        auto vec= ToStdVector( as );

        UT_EQ( String( vec ), String( vec ) );

        aworx::lib::strings::ToStdVector( "abc", vec,       CurrentData::Keep );    UT_EQ( "abcabc"       , vec );
        aworx::lib::strings::ToStdVector( "abc", vec,  1,1, CurrentData::Keep );    UT_EQ( "abcabcb"      , vec );
        aworx::lib::strings::ToStdVector( "abc", vec,  1,5, CurrentData::Keep );    UT_EQ( "abcabcbbc"    , vec );
        aworx::lib::strings::ToStdVector( "abc", vec, -1,5, CurrentData::Keep );    UT_EQ( "abcabcbbcabc" , vec );
    }
}

//--------------------------------------------------------------------------------------------------
//--- String_Std_Iterator
//--------------------------------------------------------------------------------------------------
UT_METHOD( String_Std_Iterator )
{
    UT_INIT();

    UT_PRINT("") UT_PRINT( "### String/AString: Testing satisification of concept of std::RandomAccessIterator  ###" );

    // Test iterator: Template code using std::string. This is copied below for aworx::String and aworx::AString
    {
        std::string str("abcdef");

        auto it= std::find( str.begin(), str.end(), 'c' );
        UT_TRUE( it != str.end() );
        UT_TRUE( *it == 'c' );
        UT_TRUE( str.end() - it == 4 );

        auto it2= std::find( begin(str), end(str), 'c' );
        UT_TRUE( it == it2 );

        {  auto i= it++;    UT_TRUE( *i == 'c' );  UT_TRUE( *it == 'd' );    }
        {  auto i= ++it;    UT_TRUE( *i == 'e' );  UT_TRUE( *it == 'e' );    }
        {  auto i= it--;    UT_TRUE( *i == 'e' );  UT_TRUE( *it == 'd' );    }
        {  auto i= --it;    UT_TRUE( *i == 'c' );  UT_TRUE( *it == 'c' );    }
        {  auto i= it-= 2;  UT_TRUE( *i == 'a' );  UT_TRUE( *it == 'a' ); UT_TRUE( *(it + 5 ) == 'f' );   }
        {  auto i= it+= 3;  UT_TRUE( *i == 'd' );  UT_TRUE( *it == 'd' ); UT_TRUE( *(it - 3 ) == 'a' );   }

        {  auto i= it;  i++; UT_TRUE( 1 == i - it );    i+=2; UT_TRUE( 3 == i - it );    i-=5; UT_TRUE( -2 == i - it );       }

        UT_TRUE( it[ 1] == 'e' ); UT_TRUE( it[ 2] == 'f' ); UT_TRUE( it[ 0] == 'd' );
        UT_TRUE( it[-1] == 'c' ); UT_TRUE( it[-2] == 'b' ); UT_TRUE( it[-3] == 'a' );

        *it=    'X'; UT_EQ( "abcXef", str );
        it[ 0]= '-'; UT_EQ( "abc-ef", str );
        it[ 1]= '*'; UT_EQ( "abc-*f", str );
        it[-1]= '~'; UT_EQ( "ab~-*f", str );
        it[ 2]= '@'; UT_EQ( "ab~-*@", str );
        it[-2]= '$'; UT_EQ( "a$~-*@", str );
        it[-3]= '#'; UT_EQ( "#$~-*@", str );

        auto itID= it;
        auto itP1= it + 1;
        UT_TRUE ( it <  itP1 );   UT_FALSE( itP1 <  it );  UT_TRUE ( itP1 >  it  );   UT_FALSE(  it >  itP1 );
        UT_TRUE ( it <= itP1 );   UT_FALSE( itP1 <= it );  UT_TRUE ( itP1 >= it  );   UT_FALSE(  it >= itP1 );
        UT_FALSE( it <  itID );   UT_FALSE( itID <  it );  UT_FALSE( itID >  it  );   UT_FALSE(  it >  itID );
        UT_TRUE ( it <= itID );   UT_TRUE ( itID <= it );  UT_TRUE ( itID >= it  );   UT_TRUE (  it >= itID );
    }

    // Test aworx::String::ConstIterator
    {
        aworx::String str("abcdef");

        auto it= std::find( str.begin(), str.end(), 'c' );
        UT_TRUE( it != str.end() );
        UT_TRUE( *it == 'c' );
        UT_TRUE( str.end() - it == 4 );

        auto it2= std::find( begin(str), end(str), 'c' );
        UT_TRUE( it == it2 );

        {  auto i= it++;    UT_TRUE( *i == 'c' );  UT_TRUE( *it == 'd' );    }
        {  auto i= ++it;    UT_TRUE( *i == 'e' );  UT_TRUE( *it == 'e' );    }
        {  auto i= it--;    UT_TRUE( *i == 'e' );  UT_TRUE( *it == 'd' );    }
        {  auto i= --it;    UT_TRUE( *i == 'c' );  UT_TRUE( *it == 'c' );    }
        {  auto i= it-= 2;  UT_TRUE( *i == 'a' );  UT_TRUE( *it == 'a' ); UT_TRUE( *(it + 5 ) == 'f' );   }
        {  auto i= it+= 3;  UT_TRUE( *i == 'd' );  UT_TRUE( *it == 'd' ); UT_TRUE( *(it - 3 ) == 'a' );   }

        {  auto i= it;  i++; UT_TRUE( 1 == i - it );    i+=2; UT_TRUE( 3 == i - it );    i-=5; UT_TRUE( -2 == i - it );       }

        UT_TRUE( it[ 1] == 'e' ); UT_TRUE( it[ 2] == 'f' ); UT_TRUE( it[ 0] == 'd' );
        UT_TRUE( it[-1] == 'c' ); UT_TRUE( it[-2] == 'b' ); UT_TRUE( it[-3] == 'a' );

        // forbidden:
        // *it=    'X'; UT_EQ( "abcXef", str );
        // it[ 0]= '-'; UT_EQ( "abc-ef", str );
        // ...


        auto itID= it;
        auto itP1= it + 1;
        UT_TRUE ( it <  itP1 );   UT_FALSE( itP1 <  it );  UT_TRUE ( itP1 >  it  );   UT_FALSE(  it >  itP1 );
        UT_TRUE ( it <= itP1 );   UT_FALSE( itP1 <= it );  UT_TRUE ( itP1 >= it  );   UT_FALSE(  it >= itP1 );
        UT_FALSE( it <  itID );   UT_FALSE( itID <  it );  UT_FALSE( itID >  it  );   UT_FALSE(  it >  itID );
        UT_TRUE ( it <= itID );   UT_TRUE ( itID <= it );  UT_TRUE ( itID >= it  );   UT_TRUE (  it >= itID );
    }

    // Test aworx::AString::Iterator
    {
        aworx::AString str("abcdef");

        auto it= std::find( str.begin(), str.end(), 'c' );
        UT_TRUE( it != str.end() );
        UT_TRUE( *it == 'c' );
        UT_TRUE( str.end() - it == 4 );

        auto it2= std::find( begin(str), end(str), 'c' );
        UT_TRUE( it == it2 );

        {  auto i= it++;    UT_TRUE( *i == 'c' );  UT_TRUE( *it == 'd' );    }
        {  auto i= ++it;    UT_TRUE( *i == 'e' );  UT_TRUE( *it == 'e' );    }
        {  auto i= it--;    UT_TRUE( *i == 'e' );  UT_TRUE( *it == 'd' );    }
        {  auto i= --it;    UT_TRUE( *i == 'c' );  UT_TRUE( *it == 'c' );    }
        {  auto i= it-= 2;  UT_TRUE( *i == 'a' );  UT_TRUE( *it == 'a' ); UT_TRUE( *(it + 5 ) == 'f' );   }
        {  auto i= it+= 3;  UT_TRUE( *i == 'd' );  UT_TRUE( *it == 'd' ); UT_TRUE( *(it - 3 ) == 'a' );   }

        {  auto i= it;  i++; UT_TRUE( 1 == i - it );    i+=2; UT_TRUE( 3 == i - it );    i-=5; UT_TRUE( -2 == i - it );       }

        UT_TRUE( it[ 1] == 'e' ); UT_TRUE( it[ 2] == 'f' ); UT_TRUE( it[ 0] == 'd' );
        UT_TRUE( it[-1] == 'c' ); UT_TRUE( it[-2] == 'b' ); UT_TRUE( it[-3] == 'a' );

        *it=    'X'; UT_EQ( "abcXef", str );
        it[ 0]= '-'; UT_EQ( "abc-ef", str );
        it[ 1]= '*'; UT_EQ( "abc-*f", str );
        it[-1]= '~'; UT_EQ( "ab~-*f", str );
        it[ 2]= '@'; UT_EQ( "ab~-*@", str );
        it[-2]= '$'; UT_EQ( "a$~-*@", str );
        it[-3]= '#'; UT_EQ( "#$~-*@", str );

        auto itID= it;
        auto itP1= it + 1;
        UT_TRUE ( it <  itP1 );   UT_FALSE( itP1 <  it );  UT_TRUE ( itP1 >  it  );   UT_FALSE(  it >  itP1 );
        UT_TRUE ( it <= itP1 );   UT_FALSE( itP1 <= it );  UT_TRUE ( itP1 >= it  );   UT_FALSE(  it >= itP1 );
        UT_FALSE( it <  itID );   UT_FALSE( itID <  it );  UT_FALSE( itID >  it  );   UT_FALSE(  it >  itID );
        UT_TRUE ( it <= itID );   UT_TRUE ( itID <= it );  UT_TRUE ( itID >= it  );   UT_TRUE (  it >= itID );
    }


    // Test basic algorithms (template code with std::string, copied below)
    {
        std::string str("cafdeb");

        std::sort( str.begin(), str.end() );
        UT_EQ( "abcdef", str);

        std::rotate( str.begin() + 1, str.begin() + 4, str.end() - 1 );
        UT_EQ( "aebcdf", str);

        std::string copy("12345");
        std::remove_copy( str.begin(), str.end(), copy.begin(), 'd' );
        UT_EQ( "aebcf", copy);
    }


    // Test basic algorithms
    {
        aworx::AString str("cafdeb");

        std::sort( str.begin(), str.end() );
        UT_EQ( "abcdef", str);

        std::rotate( str.begin() + 1, str.begin() + 4, str.end() - 1 );
        UT_EQ( "aebcdf", str);

        aworx::AString copy("12345");
        std::remove_copy( str.begin(), str.end(), copy.begin(), 'd' );
        UT_EQ( "aebcf", copy);
    }

}

//--------------------------------------------------------------------------------------------------
//--- Boxing_Std_String
//--------------------------------------------------------------------------------------------------
UT_METHOD( Boxing_Std_String )
{
    UT_INIT();
    aworx::lib::boxing::InitStdString();

    UT_PRINT("") UT_PRINT( "### Boxing: Testing Equals: char*/char[]  with std::string ###" );
    {
        bool result;
        Box helloP( static_cast<const char*>("Hello"));
        Box helloA(                          "Hello");
        Box falseP( static_cast<const char*>("not hello"));
        Box falseA(                          "not hello");
        std::string sHello= std::string ( "Hello"     );
        std::string sFalse= std::string ( "not Hello" );
        Box helloStdS( sHello );
        Box falseStdS( sFalse );

        result= helloStdS.Invoke<IEquals, bool>( helloP ); UT_EQ( true , result );
        result= helloStdS.Invoke<IEquals, bool>( helloA ); UT_EQ( true , result );
        result= helloStdS.Invoke<IEquals, bool>( falseP ); UT_EQ( false, result );
        result= helloStdS.Invoke<IEquals, bool>( falseA ); UT_EQ( false, result );

        result= helloA.Invoke<IEquals, bool>( helloStdS ); UT_EQ( true , result );
        result= helloP.Invoke<IEquals, bool>( helloStdS ); UT_EQ( true , result );
        result= helloA.Invoke<IEquals, bool>( falseStdS ); UT_EQ( false, result );
        result= helloP.Invoke<IEquals, bool>( falseStdS ); UT_EQ( false, result );
    }

    UT_PRINT("") UT_PRINT( "### Boxing: Testing Equals: wchar_t*/wchar_t[]  with std::wstring ###" );
    {
        bool result;
        Box helloP( static_cast<const wchar_t*>(L"Hello"));
        Box helloA(                             L"Hello");
        Box falseP( static_cast<const wchar_t*>(L"not hello"));
        Box falseA(                             L"not hello");
        std::wstring wsHello( L"Hello"     );
        std::wstring wsFalse( L"not Hello" );
        Box helloStdWS( wsHello );
        Box falseStdWS( wsFalse );

        result= helloStdWS.Invoke<IEquals, bool>( helloP ); UT_EQ( true , result );
        result= helloStdWS.Invoke<IEquals, bool>( helloA ); UT_EQ( true , result );
        result= helloStdWS.Invoke<IEquals, bool>( falseP ); UT_EQ( false, result );
        result= helloStdWS.Invoke<IEquals, bool>( falseA ); UT_EQ( false, result );

        result= helloA.Invoke<IEquals, bool>( helloStdWS ); UT_EQ( true , result );
        result= helloP.Invoke<IEquals, bool>( helloStdWS ); UT_EQ( true , result );
        result= helloA.Invoke<IEquals, bool>( falseStdWS ); UT_EQ( false, result );
        result= helloP.Invoke<IEquals, bool>( falseStdWS ); UT_EQ( false, result );
    }

    UT_PRINT("") UT_PRINT( "### Boxing: Testing Equals: char16_t*/char16_t[]  with std::u16string ###" );
    {
        bool result;
        Box helloP( static_cast<const char16_t*>(u"Hello"));
        Box helloA(                              u"Hello");
        Box falseP( static_cast<const char16_t*>(u"not hello"));
        Box falseA(                              u"not hello");
        std::u16string u16Hello( u"Hello"     );
        std::u16string u16False( u"not Hello" );
        Box helloU16( u16Hello );
        Box falseU16( u16False );

        result= helloU16.Invoke<IEquals, bool>( helloP ); UT_EQ( true , result );
        result= helloU16.Invoke<IEquals, bool>( helloA ); UT_EQ( true , result );
        result= helloU16.Invoke<IEquals, bool>( falseP ); UT_EQ( false, result );
        result= helloU16.Invoke<IEquals, bool>( falseA ); UT_EQ( false, result );

        result= helloA.Invoke<IEquals, bool>( helloU16 ); UT_EQ( true , result );
        result= helloP.Invoke<IEquals, bool>( helloU16 ); UT_EQ( true , result );
        result= helloA.Invoke<IEquals, bool>( falseU16 ); UT_EQ( false, result );
        result= helloP.Invoke<IEquals, bool>( falseU16 ); UT_EQ( false, result );
    }

    UT_PRINT("") UT_PRINT( "### Boxing: Testing Equals: char32_t*/char32_t[]  with std::u32string ###" );
    {
        bool result;
        Box helloP( static_cast<const char32_t*>(U"Hello"));
        Box helloA(                              U"Hello");
        Box falseP( static_cast<const char32_t*>(U"not hello"));
        Box falseA(                              U"not hello");
        std::u32string u32Hello( U"Hello"     );
        std::u32string u32False( U"not Hello" );
        Box helloU32( u32Hello );
        Box falseU32( u32False );

        result= helloU32.Invoke<IEquals, bool>( helloP ); UT_EQ( true , result );
        result= helloU32.Invoke<IEquals, bool>( helloA ); UT_EQ( true , result );
        result= helloU32.Invoke<IEquals, bool>( falseP ); UT_EQ( false, result );
        result= helloU32.Invoke<IEquals, bool>( falseA ); UT_EQ( false, result );

        result= helloA.Invoke<IEquals, bool>( helloU32 ); UT_EQ( true , result );
        result= helloP.Invoke<IEquals, bool>( helloU32 ); UT_EQ( true , result );
        result= helloA.Invoke<IEquals, bool>( falseU32 ); UT_EQ( false, result );
        result= helloP.Invoke<IEquals, bool>( falseU32 ); UT_EQ( false, result );
    }

    UT_PRINT("") UT_PRINT( "### Boxing: TApply for BoxedAs<QTxxx> ###" );
    {
        AString test;
        { std::string       stdstr( "std::string"     ); test._() << Box( BoxedAs<std::string      >( stdstr ) ); UT_EQ( "std::string"    , test); }
        { std::wstring      stdstr(L"std::wstring"    ); test._() << Box( BoxedAs<std::wstring     >( stdstr ) ); UT_EQ( "std::wstring"   , test); }
        { std::u16string    stdstr(u"std::u16string"  ); test._() << Box( BoxedAs<std::u16string   >( stdstr ) ); UT_EQ( "std::u16string" , test); }
        { std::u32string    stdstr(U"std::u32string"  ); test._() << Box( BoxedAs<std::u32string   >( stdstr ) ); UT_EQ( "std::u32string" , test); }
    }

}

UT_CLASS_END

} //namespace
