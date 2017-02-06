// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"

#include "alib/strings/tokenizer.hpp"
#include "alib/strings/numberformat.hpp"
#include "alib/time/ticks.hpp"
#include "alib/compatibility/std_string.hpp"
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
    UT_PRINT( String128() << "  std::wstring: Smileys: " << std::wstring( L"\U0001F609 * \U0001F607 * \U0001F603 * \U0001F60E * "
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

UT_METHOD( Std_StringBoxing )
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
