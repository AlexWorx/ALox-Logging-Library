// #################################################################################################
//  cs.aworx.unittests - AWorx Util
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.Globalization;
using cs.aworx.lox;
using cs.aworx.lox.loggers;
using cs.aworx.lib.strings;
using ut_cs_aworx;
using cs.aworx.lib.enums;


#if ALIB_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if ALIB_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using System.Text;
using cs.aworx.lib;


namespace ut_cs_aworx_lib
{
    #if ALIB_MONO_DEVELOP
        [TestFixture ()]
    #endif
    #if ALIB_VSTUDIO
        [TestClass]
    #endif
    public class CS_Strings_Tokenizer  : AUnitTest
    {


//##################################################################################################
// SAMPLE code of class documentation
//##################################################################################################

void documentationSampleTokenizer()
{
    UnitTestSampleWriter utsw= new UnitTestSampleWriter("DOC_SAMPLES_ALIB_LIB_STRING_TOKEN.txt");


//! [DOC_SAMPLES_ALIB_LIB_STRING_TOKEN]
    // data string to tokenize
    AString data= new AString( "test;  abc ; 1,2 , 3 ; xyz ; including;separator" );

    // create tokenizer on data with ';' as delimiter
    Tokenizer tokens= new Tokenizer( data, ';' );

    // read tokens

    System.Console.WriteLine( tokens.Next() ); // will print "test"
    System.Console.WriteLine( tokens.Next() ); // will print "abc"
    System.Console.WriteLine( tokens.Next() ); // will print "1,2 , 3"

    // tokenize actual (third) token (nested tokenizer)
    Tokenizer subTokens= new Tokenizer( tokens.Actual,  ',');
    System.Console.Write( subTokens.Next().ToString() );

    while( subTokens.HasNext() )
        System.Console.Write( "~" + subTokens.Next().ToString() );

    System.Console.WriteLine();

    // continue with the main tokenizer
    System.Console.WriteLine( tokens.Next().ToString() ); // will print "xyz"

    // grab the rest, as we know that the last token might include our separator character
    System.Console.WriteLine( tokens.GetRest().ToString() ); // will print "including;separator"
//! [DOC_SAMPLES_ALIB_LIB_STRING_TOKEN]

    utsw.FlushAndResetConsole();
}


#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings")]
    #endif
#endif
public void DocumentationSamples()
{

    //UT_PRINT("*** Documentation Sample +**")
    documentationSampleTokenizer();
}


//---------------------------------------------------------------------------------------------------------
//--- Test Tokenizer
//---------------------------------------------------------------------------------------------------------
void tokenizerTest( string inputString, AString res, char delim, char newDelim,
                    Whitespaces trim, int inpStart= -1, int inpEnd= -1  )
{
    Substring inp= new Substring( inputString );
    if ( inpStart >= 0 ) inp.Start= inpStart;
    if ( inpEnd   >= 0 ) inp.End=   inpEnd;
    res.Clear();

    Tokenizer tok= new Tokenizer( inp, delim );

    while( tok.HasNext() )
    {
        tok.Next(trim).CopyTo( res, true );
        res._( newDelim );
    }

}

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings")]
    #endif
#endif
public void Tokenize()
{
    AString astr=  new AString();
    AString res= new AString();

    // tokenizing empty string
    astr.Clear()._( "" );
    res.Clear();
    {
        Tokenizer tok= new Tokenizer( astr, ',' );   UT_EQ( true,  tok.HasNext() );
        tok.Next().CopyTo( res, true );              UT_EQ( "", res );
    }

    // tokenizing no delim
    astr.Clear()._( "abc" );
    res.Clear();
    {
        Tokenizer tok= new Tokenizer( astr, ',' );                UT_EQ( true,  tok.HasNext() );
        tok.Next().CopyTo( res, true );     UT_EQ( "abc", res );
    }

    // tokenizing
    {
        tokenizerTest( "abc",       res, ',', '@',   Whitespaces.Trim, -1,   -1 );
        UT_EQ ( "abc@",      res );

        tokenizerTest( "a,bc",      res, ',', '@',   Whitespaces.Trim, -1,   -1 );
        UT_EQ ( "a@bc@",     res );

        tokenizerTest( "a,bc",      res, ',', '@',   Whitespaces.Trim, -1,   -1 );
        UT_EQ ( "a@bc@",     res );

        tokenizerTest( ",",         res, ',', '@',   Whitespaces.Trim, -1,   -1 );
        UT_EQ ( "@@",        res );

        tokenizerTest( ",,",        res, ',', '@',   Whitespaces.Trim, -1,   -1 );
        UT_EQ ( "@@@",       res );

        tokenizerTest( "a,b,c,,",   res, ',', '@',   Whitespaces.Trim, -1,   -1 );
        UT_EQ ( "a@b@c@@@",  res );

        tokenizerTest( "a,b,c",     res, ',', '@',   Whitespaces.Trim, -1,   -1 );
        UT_EQ ( "a@b@c@",    res );

        tokenizerTest( ",a,b,c",    res, ',', '@',   Whitespaces.Trim, -1,   -1 );
        UT_EQ ( "@a@b@c@",   res );

        tokenizerTest( "123567",    res, ',', '@',   Whitespaces.Trim, 2,   2 );
        UT_EQ ( "3@",        res );

        tokenizerTest( "123567",    res, ',', '@',   Whitespaces.Trim, 2,   1 );
        UT_EQ ( "@",         res );

        tokenizerTest( "  abc , def , ghe ",    res, ',', '@',   Whitespaces.Trim, -1,   -1 );
        UT_EQ ( "abc@def@ghe@",          res );

        tokenizerTest( "abc , def,ghe,",        res, ',', '@',   Whitespaces.Trim, -1,   -1 );
        UT_EQ ( "abc@def@ghe@@",         res );


        tokenizerTest( "  abc , def , ghe ",    res, ',', '@',   Whitespaces.Keep, -1,   -1 );
        UT_EQ ( "  abc @ def @ ghe @",   res );

        tokenizerTest( "abc , def,ghe,",        res, ',', '@',   Whitespaces.Keep, -1,   -1 );
        UT_EQ ( "abc @ def@ghe@@",       res );
    }

    // tokenizing with different delimiters
    {
        astr.Clear()._( "1,5;3@4" );
        Tokenizer tok= new Tokenizer(astr, ',');
        tok.Next()                       .CopyTo( res );    UT_EQ ( "1",   res );  UT_EQ( true,  tok.HasNext() );
        tok.Next( Whitespaces.Trim, ';' ).CopyTo( res );    UT_EQ ( "5",   res );  UT_EQ( true,  tok.HasNext() );
        tok.Next( Whitespaces.Trim, '@' ).CopyTo( res );    UT_EQ ( "3",   res );  UT_EQ( true,  tok.HasNext() );
        tok.Next( Whitespaces.Trim, '-' ).CopyTo( res );    UT_EQ ( "4",   res );  UT_EQ( false, tok.HasNext() );
    }

    // tokenizing with different delimiters
    {
        astr.Clear()._( "abc, 5;\t3;;; 4  " );
        Tokenizer tok= new Tokenizer(astr,',');
        tok.Next()                       .CopyTo( res );    UT_EQ ( "abc", res );  UT_EQ( true,  tok.HasNext() );
        tok.Next( Whitespaces.Trim, ';' ).CopyTo( res );    UT_EQ ( "5",   res );  UT_EQ( true,  tok.HasNext() );
        tok.Next()                       .CopyTo( res );    UT_EQ ( "3",   res );  UT_EQ( true,  tok.HasNext() );
        tok.Next()                       .CopyTo( res );    UT_EQ ( "",    res );  UT_EQ( true,  tok.HasNext() );
        tok.GetRest()                    .CopyTo( res );    UT_EQ ( "; 4", res );  UT_EQ( false, tok.HasNext() );
    }

    // sub-tokens
    {
        astr.Clear()._( "1,2;3 , 4;5,;," );
        Tokenizer tok= new Tokenizer(astr, ';');

        Tokenizer tok2= new Tokenizer( tok.Next(), ',');
        tok2.Next().CopyTo( res ); UT_EQ ( "1", res );  UT_TRUE(  tok2.HasNext() );
        tok2.Next().CopyTo( res ); UT_EQ ( "2", res );  UT_TRUE( !tok2.HasNext() );
        UT_TRUE( tok.HasNext() );

        tok2.Set( tok.Next(), ',');
        tok2.Next().CopyTo( res ); UT_EQ ( "3", res );  UT_TRUE(  tok2.HasNext() );
        tok2.Next().CopyTo( res ); UT_EQ ( "4", res );  UT_TRUE( !tok2.HasNext() );
        UT_TRUE( tok.HasNext() );

        tok2.Set( tok.Next(), ',');
        tok2.Next().CopyTo( res ); UT_EQ ( "5", res );  UT_TRUE(  tok2.HasNext() );
        tok2.Next().CopyTo( res ); UT_EQ ( "",  res );  UT_TRUE( !tok2.HasNext() );
        UT_TRUE( tok.HasNext() );

        tok2.Set( tok.Next(), ',');
        tok2.Next().CopyTo( res ); UT_EQ ( "", res );  UT_TRUE(  tok2.HasNext() );
        tok2.Next().CopyTo( res ); UT_EQ ( "", res );  UT_TRUE( !tok2.HasNext() );
        UT_TRUE( !tok.HasNext() );
    }
}



    }
}
