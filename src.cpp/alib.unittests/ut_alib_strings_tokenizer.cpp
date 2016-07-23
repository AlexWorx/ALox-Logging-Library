// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#include "alib/strings/tokenizer.hpp"
#include "alib/compatibility/std_iostream.hpp"

#define TESTCLASSNAME       CPP_ALib_StringsTokenizer
#include "aworx_unittests.hpp"

#include <iostream>
#include <iomanip>

using namespace std;
using namespace aworx;

namespace ut_aworx {



UT_CLASS()



//--------------------------------------------------------------------------------------------------
//--- Tokenizer
//--------------------------------------------------------------------------------------------------
void tokenizerTest( const char* inputString, AString& res, char delim, char newDelim,
                    Whitespaces trim, int inpStart= -1, int inpEnd= -1  )
{
    Substring inp( inputString );
    if ( inpStart < 0 )  inpStart= 0;
    if ( inpEnd   < 0 )  inpEnd=   inp.Length() - 1;
    inp.Set( inp, inpStart, inpEnd-inpStart +1 );

    res.Clear();

    Tokenizer tknzr( inp, delim );

    while( tknzr.HasNext() )
    {
        res._( tknzr.Next(trim) );
        res._( newDelim );
    }

}

UT_METHOD( Tokenize )
{
    UT_INIT();

    AString as;
    AString res;

    // tokenizing empty string
    as.Clear()._( "" );
    res.Clear();
    {
        Tokenizer tknzr( as, ',' );  UT_EQ( true,  tknzr.HasNext() );
        res._( tknzr.Next() );                UT_EQ( "", res );
    }

    // tokenizing no delim
    as.Clear()._( "abc" );
    res.Clear();
    {
        Tokenizer tknzr( as, ',' );           UT_EQ( true,  tknzr.HasNext() );
        res._( tknzr.Next() );                UT_EQ( "abc", res );
    }

    // tokenizing
    {
        tokenizerTest( "abc",                   res, ',', '@',   Whitespaces::Trim,  -1,  -1 );   UT_EQ( res, "abc@"                );
        tokenizerTest( "a,bc",                  res, ',', '@',   Whitespaces::Trim,  -1,  -1 );   UT_EQ( res, "a@bc@"               );
        tokenizerTest( "a,bc",                  res, ',', '@',   Whitespaces::Trim,  -1,  -1 );   UT_EQ( res, "a@bc@"               );
        tokenizerTest( ",",                     res, ',', '@',   Whitespaces::Trim,  -1,  -1 );   UT_EQ( res, "@@"                  );
        tokenizerTest( ",,",                    res, ',', '@',   Whitespaces::Trim,  -1,  -1 );   UT_EQ( res, "@@@"                 );
        tokenizerTest( "a,b,c,,",               res, ',', '@',   Whitespaces::Trim,  -1,  -1 );   UT_EQ( res, "a@b@c@@@"            );
        tokenizerTest( "a,b,c",                 res, ',', '@',   Whitespaces::Trim,  -1,  -1 );   UT_EQ( res, "a@b@c@"              );
        tokenizerTest( ",a,b,c",                res, ',', '@',   Whitespaces::Trim,  -1,  -1 );   UT_EQ( res, "@a@b@c@"             );
        tokenizerTest( "123567",                res, ',', '@',   Whitespaces::Trim,   2,   2 );   UT_EQ( res, "3@"                  );
        tokenizerTest( "123567",                res, ',', '@',   Whitespaces::Trim,   2,   1 );   UT_EQ( res, "@"                   );
        tokenizerTest( "  abc , def , ghe ",    res, ',', '@',   Whitespaces::Trim,  -1,  -1 );   UT_EQ( res, "abc@def@ghe@"        );
        tokenizerTest( "abc , def,ghe,",        res, ',', '@',   Whitespaces::Trim,  -1,  -1 );   UT_EQ( res, "abc@def@ghe@@"       );
        tokenizerTest( "  abc , def , ghe ",    res, ',', '@',   Whitespaces::Keep,  -1,  -1 );   UT_EQ( res, "  abc @ def @ ghe @" );
        tokenizerTest( "abc , def,ghe,",        res, ',', '@',   Whitespaces::Keep,  -1,  -1 );   UT_EQ( res, "abc @ def@ghe@@"     );
    }

    // tokenizing with different delimiters
    {
        as.Clear()._( "1,5;3@4" );
        Tokenizer tknzr(as, ',');
        res= tknzr.Next();                            UT_EQ( "1",   res );  UT_EQ( true,  tknzr.HasNext() );
        res= tknzr.Next( Whitespaces::Trim, ';' );    UT_EQ( "5",   res );  UT_EQ( true,  tknzr.HasNext() );
        res= tknzr.Next( Whitespaces::Trim, '@' );    UT_EQ( "3",   res );  UT_EQ( true,  tknzr.HasNext() );
        res= tknzr.Next( Whitespaces::Trim, '-' );    UT_EQ( "4",   res );  UT_EQ( false, tknzr.HasNext() );
    }

    // tokenizing with different delimiters
    {
        as.Clear()._( "abc, 5;\t3;;; 4  " );
        Tokenizer tknzr(as,',');
        res= tknzr.Next();                          UT_EQ( "abc", res );  UT_EQ( true,  tknzr.HasNext() );
        res= tknzr.Next( Whitespaces::Trim, ';' );  UT_EQ( "5",   res );  UT_EQ( true,  tknzr.HasNext() );
        res= tknzr.Next();                          UT_EQ( "3",   res );  UT_EQ( true,  tknzr.HasNext() );
        res= tknzr.Next();                          UT_EQ( "",    res );  UT_EQ( true,  tknzr.HasNext() );
        res= tknzr.GetRest();                       UT_EQ( "; 4", res );  UT_EQ( false, tknzr.HasNext() );
    }

    // sub-tokens
    {
        as.Clear()._( "1,2;3 , 4;5,;," );
        Tokenizer tknzr(as, ';');

        Tokenizer tknzr2( tknzr.Next(), ',');
        res= tknzr2.Next(); UT_EQ( "1", res );  UT_TRUE(  tknzr2.HasNext() );
        res= tknzr2.Next(); UT_EQ( "2", res );  UT_TRUE( !tknzr2.HasNext() );
        UT_TRUE( tknzr.HasNext() );

        tknzr2.Set( tknzr.Next(), ',');
        res= tknzr2.Next(); UT_EQ( "3", res );  UT_TRUE(  tknzr2.HasNext() );
        res= tknzr2.Next(); UT_EQ( "4", res );  UT_TRUE( !tknzr2.HasNext() );
        UT_TRUE( tknzr.HasNext() );

        tknzr2.Set( tknzr.Next(), ',');
        res= tknzr2.Next(); UT_EQ( "5", res );  UT_TRUE(  tknzr2.HasNext() );
        res= tknzr2.Next(); UT_EQ( "",  res );  UT_TRUE( !tknzr2.HasNext() );
        UT_TRUE( tknzr.HasNext() );

        tknzr2.Set( tknzr.Next(), ',');
        res= tknzr2.Next(); UT_EQ( "", res );  UT_TRUE(  tknzr2.HasNext() );
        res= tknzr2.Next(); UT_EQ( "", res );  UT_TRUE( !tknzr2.HasNext() );
        UT_TRUE( !tknzr.HasNext() );
    }
}



UT_CLASS_END

} //namespace
