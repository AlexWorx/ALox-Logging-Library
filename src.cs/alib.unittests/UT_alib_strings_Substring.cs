// #################################################################################################
//  cs.aworx.unittests - AWorx Util
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Globalization;
using cs.aworx.lox;
using cs.aworx.lox.loggers;
using cs.aworx.lib.strings;
using cs.aworx.lib.strings.util;
using ut_cs_aworx;
using cs.aworx.lib.lang;


#if ALIB_NUNIT
    using NUnit.Framework;
#endif
#if ALIB_IDE_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using System.Text;
using cs.aworx.lib;


namespace ut_cs_aworx_lib
{
//--------------------------------------------------------------------------------------------------
//--- class CS_Strings_Substring
//--------------------------------------------------------------------------------------------------
    #if ALIB_NUNIT
        [TestFixture ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestClass]
    #endif
    public class CS_Strings_Substring  : AWorxUnitTesting
    {


//##################################################################################################
// SAMPLE code of class documentation
//##################################################################################################

void documentationSampleTokenizer()
{
    UTSampleWriter utsw= new UTSampleWriter("DOC_SAMPLES_ALIB_LIB_STRING_TOKEN.txt");


//! [DOC_SAMPLES_ALIB_LIB_STRING_TOKEN]
    // data string to tokenize
    AString data= new AString( "test;  abc ; 1,2 , 3 ; xyz ; including;separator" );

    // create tokenizer on data with ';' as delimiter
    Tokenizer tknzr= new Tokenizer( data, ';' );

    // read tokens

    System.Console.WriteLine( tknzr.Next() ); // will print "test"
    System.Console.WriteLine( tknzr.Next() ); // will print "abc"
    System.Console.WriteLine( tknzr.Next() ); // will print "1,2 , 3"

    // tokenize actual (third) token (nested tokenizer)
    Tokenizer subTknzr= new Tokenizer( tknzr.Actual,  ',');
    System.Console.Write( subTknzr.Next().ToString() );

    while( subTknzr.HasNext() )
        System.Console.Write( "~" + subTknzr.Next().ToString() );

    System.Console.WriteLine();

    // continue with the main tokenizer
    System.Console.WriteLine( tknzr.Next().ToString() ); // will print "xyz"

    // grab the rest, as we know that the last token might include our separator character
    System.Console.WriteLine( tknzr.GetRest().ToString() ); // will print "including;separator"
//! [DOC_SAMPLES_ALIB_LIB_STRING_TOKEN]

    utsw.FlushAndResetConsole();
}


#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
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

//--------------------------------------------------------------------------------------------------
//--- Test Constructors
//--------------------------------------------------------------------------------------------------
void constructorTest( String inputString, AString result, bool trim )
{
    Substring tok= new Substring( inputString );
    if ( trim )
        tok.Trim();
    tok.CopyTo( result );
}


#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings")]
    #endif
#endif
public void SubstringConstructor()
{
    AString astr=   new AString();
    AString res=    new AString();

    constructorTest( "a"        , res, false ); UT_EQ( "a",        res );
    constructorTest( " a"       , res, false ); UT_EQ( " a",       res );
    constructorTest( "a "       , res, false ); UT_EQ( "a ",       res );
    constructorTest( "a b"      , res, false ); UT_EQ( "a b",      res );
    constructorTest( " a b"     , res, false ); UT_EQ( " a b",     res );
    constructorTest( "a b "     , res, false ); UT_EQ( "a b ",     res );

    constructorTest( "a"        , res, true  ); UT_EQ( "a",        res );
    constructorTest( " a"       , res, true  ); UT_EQ( "a",        res );
    constructorTest( "a "       , res, true  ); UT_EQ( "a",        res );
    constructorTest( "a b"      , res, true  ); UT_EQ( "a b",      res );
    constructorTest( " a b"     , res, true  ); UT_EQ( "a b",      res );
    constructorTest( "a b "     , res, true  ); UT_EQ( "a b",      res );

    // changing whitespaces
    {
        {
            astr.Clear()._( "xy xz abc xy" );
            Substring subs= new Substring();
            subs.Set(astr).Trim("xy ".ToCharArray()).CopyTo( res );
            UT_EQ( "z abc",      res );
        }

        {
            Substring subs= new Substring( "xy xz abc xy" );
            subs.TrimStart("xy ".ToCharArray());
            subs.TrimEnd("xy ".ToCharArray());
            subs.CopyTo( res );
            UT_EQ( "z abc",      res );
        }
    }

    // test other constructors
    {
        astr.Clear()._( " astring ");
        UT_TRUE  ( (new Substring()).IsEmpty() );
        UT_TRUE  ( (new Substring()).IsNull() );
        UT_EQ( "astring",  (new Substring( astr)).Trim() .ToString() );
        UT_EQ( "str",      (new Substring( astr,  2, 3 )).ToString() );
        UT_EQ( "",         (new Substring( astr, 20, 3 )).ToString() );
        UT_TRUE (          (new Substring( astr, 20, 3 )).IsEmpty()  );
        UT_FALSE(          (new Substring( astr, 20, 3 )).IsNull()   );


        Substring s2= new Substring( astr);
        UT_EQ( "astring",  new Substring( s2.Trim().ToString() ).ToString() );
        UT_EQ( "str",      (new Substring( (new Substring( astr, 2,3  )))).ToString() );
    }

}

//--------------------------------------------------------------------------------------------------
//--- Test FrontEnd
//--------------------------------------------------------------------------------------------------
#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings")]
    #endif
#endif
public void FrontEnd()
{
    // empty substring
    {
        Substring subs= new Substring();
        UT_EQ(  '\0',      subs.CharAtStart(   ) );
        UT_EQ(  '\0',      subs.CharAt( 0 ) );
        UT_EQ(  '\0',      subs.CharAt( 1 ) );
        UT_EQ(  '\0',      subs.CharAt(-1 ) );
        UT_EQ(  '\0',      subs.CharAt( 2 ) );
        UT_EQ(  '\0',      subs.CharAt(-2 ) );

        UT_EQ(  '\0',      subs.CharAtEnd (   ) );
        UT_EQ(  '\0',      subs.CharAtEnd ( 0 ) );
        UT_EQ(  '\0',      subs.CharAtEnd ( 1 ) );
        UT_EQ(  '\0',      subs.CharAtEnd (-1 ) );
        UT_EQ(  '\0',      subs.CharAtEnd ( 2 ) );
        UT_EQ(  '\0',      subs.CharAtEnd (-2 ) );
    }

    // empty substring
    {
        Substring subs= new Substring("aaaaaaaaaaaa");
        subs.Start= 5;
        subs.End=   4;
        UT_EQ(  '\0',      subs.CharAtStart(   ) );
        UT_EQ(  '\0',      subs.CharAt( 0 ) );
        UT_EQ(  '\0',      subs.CharAt( 1 ) );
        UT_EQ(  '\0',      subs.CharAt(-1 ) );
        UT_EQ(  '\0',      subs.CharAt( 2 ) );
        UT_EQ(  '\0',      subs.CharAt(-2 ) );

        UT_EQ(  '\0',      subs.CharAtEnd (   ) );
        UT_EQ(  '\0',      subs.CharAtEnd ( 0 ) );
        UT_EQ(  '\0',      subs.CharAtEnd ( 1 ) );
        UT_EQ(  '\0',      subs.CharAtEnd (-1 ) );
        UT_EQ(  '\0',      subs.CharAtEnd ( 2 ) );
        UT_EQ(  '\0',      subs.CharAtEnd (-2 ) );
    }

    // substring of length 1
    {
        Substring subs= new Substring("aaaaaaaaaaaa");
        subs.Start= subs.End= 5;
        UT_EQ('a',      subs.CharAtStart(   ) );
        UT_EQ('a',      subs.CharAt( 0 ) );
        UT_EQ('\0',     subs.CharAt( 1 ) );
        UT_EQ('\0',     subs.CharAt(-1 ) );
        UT_EQ('\0',     subs.CharAt( 2 ) );
        UT_EQ('\0',     subs.CharAt(-2 ) );

        UT_EQ('a',      subs.CharAtEnd (   ) );
        UT_EQ('a',      subs.CharAtEnd ( 0 ) );
        UT_EQ('\0',     subs.CharAtEnd ( 1 ) );
        UT_EQ('\0',     subs.CharAtEnd (-1 ) );
        UT_EQ('\0',     subs.CharAtEnd ( 2 ) );
        UT_EQ('\0',     subs.CharAtEnd (-2 ) );
    }

    // substring of length 2
    {
        Substring subs= new Substring("aaaaabbbbbb");
        subs.End= subs.IndexOf('b');
        subs.Start= subs.End - 1;
        UT_EQ('a',      subs.CharAtStart(   ) );
        UT_EQ('a',      subs.CharAt( 0 ) );
        UT_EQ('b',      subs.CharAt( 1 ) );
        UT_EQ('\0',     subs.CharAt(-1 ) );
        UT_EQ('\0',     subs.CharAt( 2 ) );
        UT_EQ('\0',     subs.CharAt(-2 ) );

        UT_EQ('b',      subs.CharAtEnd (   ) );
        UT_EQ('b',      subs.CharAtEnd ( 0 ) );
        UT_EQ('a',      subs.CharAtEnd ( 1 ) );
        UT_EQ('\0',     subs.CharAtEnd (-1 ) );
        UT_EQ('\0',     subs.CharAtEnd ( 2 ) );
        UT_EQ('\0',     subs.CharAtEnd (-2 ) );
    }

}

//--------------------------------------------------------------------------------------------------
//--- Test Consume
//--------------------------------------------------------------------------------------------------
#if ALIB_NUNIT
[Test ()]
#endif
#if ALIB_IDE_VSTUDIO
[TestMethod]
#if !WINDOWS_PHONE
    [TestCategory("CS_Strings")]
#endif
#endif
public void Consume()
{
    // null substring
    {
        Substring s= new Substring();
        Substring r= new Substring("oldval");
        UT_EQ(  '\0',      s.ConsumeChar         ( )         );
        UT_EQ(  0,         s.ConsumeChars        (  0   , r) ); UT_TRUE(r.IsNull());
        UT_EQ(  0,         s.ConsumeChars        (  5   , r) ); UT_TRUE(r.IsNull());
        UT_EQ(  false,     s.ConsumeChar         ( 'a' )     );
        UT_EQ(  false,     s.ConsumeString       ( "word" )  );
        UT_EQ(  '\0',      s.ConsumeCharFromEnd  ( )         );
        UT_EQ(  0,         s.ConsumeCharsFromEnd (  0  )     );
        UT_EQ(  0,         s.ConsumeCharsFromEnd (  5  )     );
        UT_EQ(  false,     s.ConsumeCharFromEnd  ( 'a' )     );
        UT_EQ(  false,     s.ConsumeStringFromEnd( "word" )  );
    }

    // empty substring
    {
        Substring s= new Substring("aaaaaaaaaaaa");
        Substring r= new Substring("oldval");
        s.Start= 5;
        s.End=   4;
        UT_EQ(  '\0',      s.ConsumeChar       ( )         );
        UT_EQ(  0,         s.ConsumeChars       (  0  ,r )  ); UT_TRUE( r.IsNotNull()); UT_TRUE(r.IsEmpty());
        UT_EQ(  0,         s.ConsumeChars       (  5  ,r )  ); UT_TRUE( r.IsNotNull()); UT_TRUE(r.IsEmpty());
        UT_EQ(  false,     s.ConsumeChar       ( 'a' )     );
        UT_EQ(  false,     s.ConsumeString       ( "word" )  );
        UT_EQ(  '\0',      s.ConsumeCharFromEnd( )         );
        UT_EQ(  0,         s.ConsumeCharsFromEnd(  0  )     );
        UT_EQ(  0,         s.ConsumeCharsFromEnd(  5  )     );
        UT_EQ(  false,     s.ConsumeCharFromEnd( 'a' )     );
        UT_EQ(  false,     s.ConsumeStringFromEnd( "word" )  );
    }

    // substring of length 1
    {
        Substring s= new Substring("aaaaaaaaaaaa");
        Substring r= new Substring("oldval");

        s.Start= s.End= 5; UT_EQ(  'a',       s.ConsumeChar       ( )         ); UT_EQ( 0, s.Length() );
        s.Start= s.End= 5; UT_EQ(  1,         s.ConsumeChars       (  0  )     ); UT_EQ( 1, s.Length() );
        s.Start= s.End= 5; UT_EQ(  0,         s.ConsumeChars       (  1  , r ) ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("a"));
        s.Start= s.End= 5; UT_EQ(  0,         s.ConsumeChars       (  5  , r ) ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("a"));
        s.Start= s.End= 5; UT_EQ(  true,      s.ConsumeChar       ( 'a' )     ); UT_EQ( 0, s.Length() );
        s.Start= s.End= 5; UT_EQ(  false,     s.ConsumeChar       ( 'b' )     ); UT_EQ( 1, s.Length() );
        s.Start= s.End= 5; UT_EQ(  false,     s.ConsumeString       ( "word" )  ); UT_EQ( 1, s.Length() );
        s.Start= s.End= 5; UT_EQ(  'a',       s.ConsumeCharFromEnd( )         ); UT_EQ( 0, s.Length() );
        s.Start= s.End= 5; UT_EQ(  1,         s.ConsumeCharsFromEnd(  0  )     ); UT_EQ( 1, s.Length() );
        s.Start= s.End= 5; UT_EQ(  0,         s.ConsumeCharsFromEnd(  1  )     ); UT_EQ( 0, s.Length() );
        s.Start= s.End= 5; UT_EQ(  0,         s.ConsumeCharsFromEnd(  5  )     ); UT_EQ( 0, s.Length() );
        s.Start= s.End= 5; UT_EQ(  true,      s.ConsumeCharFromEnd( 'a' )     ); UT_EQ( 0, s.Length() );
        s.Start= s.End= 5; UT_EQ(  false,     s.ConsumeCharFromEnd( 'b' )     ); UT_EQ( 1, s.Length() );
        s.Start= s.End= 5; UT_EQ(  false,     s.ConsumeStringFromEnd( "word" )  ); UT_EQ( 1, s.Length() );
    }

    // substring of length 2
    {
        Substring s= new Substring("12ab3456");
        Substring r= new Substring("oldval");

        s.Start= 2; s.End= 3; UT_EQ(  'a',       s.ConsumeChar       ( )         ); UT_EQ( 1, s.Length() );
                              UT_EQ(  'b',       s.ConsumeChar       ( )         ); UT_EQ( 0, s.Length() );
        s.Start= 2; s.End= 3; UT_EQ(  'b',       s.ConsumeCharFromEnd( )         ); UT_EQ( 1, s.Length() );
                              UT_EQ(  'a',       s.ConsumeCharFromEnd( )         ); UT_EQ( 0, s.Length() );

        s.Start= 2; s.End= 3; UT_EQ(  2,         s.ConsumeChars       (  0 , r )  ); UT_EQ( 2, s.Length() ); UT_TRUE(r.IsNotNull()); UT_TRUE(r.IsEmpty());
        s.Start= 2; s.End= 3; UT_EQ(  1,         s.ConsumeChars       (  1 , r )  ); UT_EQ( 1, s.Length() ); UT_TRUE(r.Equals("a"));
        s.Start= 2; s.End= 3; UT_EQ(  0,         s.ConsumeChars       (  2 , r )  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));
        s.Start= 2; s.End= 3; UT_EQ(  0,         s.ConsumeChars       (  3 , r )  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));
        s.Start= 2; s.End= 3; UT_EQ(  2,         s.ConsumeCharsFromEnd(  0 , r )  ); UT_EQ( 2, s.Length() ); UT_TRUE(r.IsNotNull()); UT_TRUE(r.IsEmpty());
        s.Start= 2; s.End= 3; UT_EQ(  1,         s.ConsumeCharsFromEnd(  1 , r )  ); UT_EQ( 1, s.Length() ); UT_TRUE(r.Equals("b"));
        s.Start= 2; s.End= 3; UT_EQ(  0,         s.ConsumeCharsFromEnd(  2 , r )  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));
        s.Start= 2; s.End= 3; UT_EQ(  0,         s.ConsumeCharsFromEnd(  3 , r )  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));

        s.Start= 2; s.End= 3; UT_EQ(  false,     s.ConsumeChar       ( 'b' )     ); UT_EQ( 2, s.Length() );
                              UT_EQ(  true,      s.ConsumeChar       ( 'a' )     ); UT_EQ( 1, s.Length() );
                              UT_EQ(  true,      s.ConsumeChar       ( 'b' )     ); UT_EQ( 0, s.Length() );
                              UT_EQ(  false,     s.ConsumeChar       ( 'a' )     ); UT_EQ( 0, s.Length() );
                              UT_EQ(  false,     s.ConsumeChar       ( 'b' )     ); UT_EQ( 0, s.Length() );
        s.Start= 2; s.End= 3; UT_EQ(  false,     s.ConsumeCharFromEnd( 'a' )     ); UT_EQ( 2, s.Length() );
                              UT_EQ(  true,      s.ConsumeCharFromEnd( 'b' )     ); UT_EQ( 1, s.Length() );
                              UT_EQ(  true,      s.ConsumeCharFromEnd( 'a' )     ); UT_EQ( 0, s.Length() );
                              UT_EQ(  false,     s.ConsumeCharFromEnd( 'b' )     ); UT_EQ( 0, s.Length() );
                              UT_EQ(  false,     s.ConsumeCharFromEnd( 'a' )     ); UT_EQ( 0, s.Length() );

        s.Start= 2; s.End= 3; UT_EQ(  false,     s.ConsumeString       ( "word" )  ); UT_EQ( 2, s.Length() );
        s.Start= 2; s.End= 3; UT_EQ(  false,     s.ConsumeString       ( "AB"   )  ); UT_EQ( 2, s.Length() );
        s.Start= 2; s.End= 3; UT_EQ(  true,      s.ConsumeString       ( "ab"   )  ); UT_EQ( 0, s.Length() );
        s.Start= 2; s.End= 3; UT_EQ(  false,     s.ConsumeStringFromEnd( "word" )  ); UT_EQ( 2, s.Length() );
        s.Start= 2; s.End= 3; UT_EQ(  false,     s.ConsumeStringFromEnd( "AB"   )  ); UT_EQ( 2, s.Length() );
        s.Start= 2; s.End= 3; UT_EQ(  true,      s.ConsumeStringFromEnd( "ab"   )  ); UT_EQ( 0, s.Length() );
    }

    // 3 words
    {
        Substring s= new Substring("word1 word2 word3");

        UT_EQ(  'w',       s.ConsumeChar       ( )         );
        UT_EQ(  'o',       s.ConsumeChar       ( )         );
        UT_EQ(  'r',       s.ConsumeChar       ( )         );
        UT_EQ(  'd',       s.ConsumeChar       ( )         );
        UT_EQ(  '1',       s.ConsumeChar       ( )         );

        UT_EQ(  false    , s.ConsumeChar       ('w'                        )   );
        UT_EQ(  true     , s.ConsumeChar       ('w'     , Case.Sensitive, Whitespaces.Trim )   );
        UT_EQ(  true     , s.ConsumeChar       ('o'     , Case.Sensitive, Whitespaces.Trim )   );
        UT_EQ(  false    , s.ConsumeChar       ('o'     , Case.Sensitive, Whitespaces.Trim )   );
        UT_EQ(  true     , s.ConsumeChar       ('r'     , Case.Sensitive, Whitespaces.Trim )   );
        UT_EQ(  false    , s.ConsumeString       ("D2"    , Case.Sensitive, Whitespaces.Trim )   );
        UT_EQ(  false    , s.ConsumeString       ("D2"                       )   );
        UT_EQ(  true     , s.ConsumeString       ("d2"                       )   );

        UT_EQ(  2        , s.ConsumeChars       ( 4 )   );
        UT_EQ(  "d3"     , s.ToString() );

                  s= new Substring("word1 word2 word3");

        UT_EQ(  '3',       s.ConsumeCharFromEnd( )         );
        UT_EQ(  'd',       s.ConsumeCharFromEnd( )         );
        UT_EQ(  'r',       s.ConsumeCharFromEnd( )         );
        UT_EQ(  'o',       s.ConsumeCharFromEnd( )         );
        UT_EQ(  'w',       s.ConsumeCharFromEnd( )         );

        UT_EQ(  false    , s.ConsumeCharFromEnd('2'                        )   );
        UT_EQ(  true     , s.ConsumeCharFromEnd('2'     , Case.Sensitive, Whitespaces.Trim )   );
        UT_EQ(  true     , s.ConsumeCharFromEnd('d'     , Case.Sensitive, Whitespaces.Trim )   );
        UT_EQ(  false    , s.ConsumeCharFromEnd('d'     , Case.Sensitive, Whitespaces.Trim )   );
        UT_EQ(  true     , s.ConsumeCharFromEnd('r'     , Case.Sensitive, Whitespaces.Trim )   );
        UT_EQ(  false    , s.ConsumeStringFromEnd("WO"    , Case.Sensitive, Whitespaces.Trim )   );
        UT_EQ(  false    , s.ConsumeStringFromEnd("WO"                       )   );
        UT_EQ(  true     , s.ConsumeStringFromEnd("wo"                       )   );

        UT_EQ(  2        , s.ConsumeCharsFromEnd( 4 )   );
        UT_EQ(  "wo"     , s.ToString() );
    }

    // Tokens
    {
        Substring s= new Substring("word1 word2 word3");
        Substring t=new Substring();
        s.ConsumeToken(t, ' '); UT_EQ( "word1", t.ToString() );    UT_EQ( "word2 word3", s.ToString() );
        s.ConsumeToken(t, ' '); UT_EQ( "word2", t.ToString() );    UT_EQ( "word3"      , s.ToString() );
        s.ConsumeToken(t, ' '); UT_EQ( "word3", t.ToString() );    UT_EQ( 0, s.Length() );
        s.ConsumeToken(t, ' '); UT_EQ( ""     , t.ToString() );    UT_EQ( 0, s.Length() );
        s.ConsumeToken(t, ' '); UT_EQ( ""     , t.ToString() );    UT_EQ( 0, s.Length() );
    }




    // consume AString, Substring
    {
        Substring s= new Substring("word1 word2 word3 word4");
        Substring sConsume= new Substring( "1234word12", 4, 4 );
        AString   aConsume= new AString  (     "word"         );

        UT_EQ(  true,      s.ConsumeString       ( sConsume )  );
        UT_EQ(  false,     s.ConsumeString       ( sConsume )  );
        UT_EQ(  '1',       s.ConsumeChar       ( )           );
        UT_EQ(  false,     s.ConsumeString       ( sConsume )  );
        UT_EQ(  true,      s.ConsumeString       ( sConsume, Case.Sensitive, Whitespaces.Trim ) );
        UT_EQ(  '2',       s.ConsumeChar       ( )           );
        UT_EQ(  ' ',       s.ConsumeChar       ( )           );

        UT_EQ(  true,      s.ConsumeString       ( aConsume )  );
        UT_EQ(  false,     s.ConsumeString       ( aConsume )  );
        UT_EQ(  '3',       s.ConsumeChar       ( )           );
        UT_EQ(  false,     s.ConsumeString       ( aConsume )  );
        UT_EQ(  true,      s.ConsumeString       ( aConsume, Case.Sensitive, Whitespaces.Trim ) );

                  s.Set("1word  2word 3word  4word");

        UT_EQ(  true,      s.ConsumeStringFromEnd( sConsume )  );
        UT_EQ(  false,     s.ConsumeStringFromEnd( sConsume )  );
        UT_EQ(  '4',       s.ConsumeCharFromEnd( )           );
        UT_EQ(  false,     s.ConsumeStringFromEnd( sConsume )  );
        UT_EQ(  true,      s.ConsumeStringFromEnd( sConsume, Case.Sensitive, Whitespaces.Trim ) );
        UT_EQ(  '3',       s.ConsumeCharFromEnd( )           );
        UT_EQ(  ' ',       s.ConsumeCharFromEnd( )           );

        UT_EQ(  true,      s.ConsumeStringFromEnd( aConsume )  );
        UT_EQ(  false,     s.ConsumeStringFromEnd( aConsume )  );
        UT_EQ(  '2',       s.ConsumeCharFromEnd( )           );
        UT_EQ(  false,     s.ConsumeStringFromEnd( aConsume )  );
        UT_EQ(  true,      s.ConsumeStringFromEnd( aConsume, Case.Sensitive, Whitespaces.Trim ) );
    }

    {
        Substring subs= new Substring("1234567890");
        UT_EQ( 0, subs.ConsumePartOf("abc") );
        UT_EQ( 0, subs.ConsumePartOf("abc", 2) );
        UT_EQ( 0, subs.ConsumePartOf("abc", 5) );
        UT_EQ( 0, subs.ConsumePartOf("125", 5) );       UT_EQ( "1234567890", subs.ToString() );
        UT_EQ( 0, subs.ConsumePartOf("125", 3) );       UT_EQ( "1234567890", subs.ToString() );
        UT_EQ( 2, subs.ConsumePartOf("125", 2) );       UT_EQ(   "34567890", subs.ToString() );
        UT_EQ( 0, subs.ConsumePartOf("125")    );       UT_EQ(   "34567890", subs.ToString() );
        UT_EQ( 2, subs.ConsumePartOf("34" )    );       UT_EQ(     "567890", subs.ToString() );
        UT_EQ( 1, subs.ConsumePartOf("59" )    );       UT_EQ(      "67890", subs.ToString() );
        UT_EQ( 3, subs.ConsumePartOf("678", 2 ));       UT_EQ(         "90", subs.ToString() );
        UT_EQ( 2, subs.ConsumePartOf("90"     ));       UT_EQ(           "", subs.ToString() );
        UT_EQ( 0, subs.ConsumePartOf("90"     ));       UT_EQ(           "", subs.ToString() );
        UT_EQ( 0, subs.ConsumePartOf(""       ));       UT_EQ(           "", subs.ToString() );
    }

    {
        Substring subs= new Substring("abcdef");
        UT_EQ( 0, subs.ConsumePartOf("ABC", 1, Case.Sensitive ) );
        UT_EQ( 0, subs.ConsumePartOf("aBC", 2, Case.Sensitive ) );
        UT_EQ( 0, subs.ConsumePartOf("aBC", 5, Case.Ignore)     );
        UT_EQ( 0, subs.ConsumePartOf("aBX", 3, Case.Ignore)     );       UT_EQ( "abcdef", subs.ToString() );
        UT_EQ( 0, subs.ConsumePartOf("aBX", 2, Case.Sensitive)  );       UT_EQ( "abcdef", subs.ToString() );
        UT_EQ( 2, subs.ConsumePartOf("aBX", 2, Case.Ignore)     );       UT_EQ(   "cdef", subs.ToString() );
        UT_EQ( 0, subs.ConsumePartOf("CXX", 2, Case.Ignore)     );       UT_EQ(   "cdef", subs.ToString() );
        UT_EQ( 1, subs.ConsumePartOf("CXX", 1, Case.Ignore)     );       UT_EQ(    "def", subs.ToString() );
        UT_EQ( 3, subs.ConsumePartOf("def", 2, Case.Ignore)     );       UT_EQ(       "", subs.ToString() );
        UT_EQ( 0, subs.ConsumePartOf("def", 2, Case.Ignore)     );       UT_EQ(       "", subs.ToString() );
        UT_EQ( 0, subs.ConsumePartOf("",    2, Case.Ignore)     );       UT_EQ(       "", subs.ToString() );
        UT_EQ( 0, subs.ConsumePartOf("",    0, Case.Ignore)     );       UT_EQ(       "", subs.ToString() );
    }
}

//--------------------------------------------------------------------------------------------------
//--- Test ConsumeNumbers
//--------------------------------------------------------------------------------------------------
#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings")]
    #endif
#endif
public void ConsumeNumbers()
{
    // ConsumeDec()
    {
        Substring subs= new Substring();
        int result;
                                   UT_EQ( false,  subs.ConsumeInt( out result     ) );   UT_EQ(       0,  result );
        subs.Set( ""            ); UT_EQ( false,  subs.ConsumeInt( out result     ) );   UT_EQ(       0,  result );
        subs.Set( "  ABC"       ); UT_EQ( false,  subs.ConsumeInt( out result     ) );   UT_EQ(       0,  result );
        subs.Set( "  12345"     ); UT_EQ( true ,  subs.ConsumeInt( out result     ) );   UT_EQ(   12345,  result );
        subs.Set( "  12 45"     ); UT_EQ( true ,  subs.ConsumeInt( out result     ) );   UT_EQ(      12,  result );
                                   UT_EQ( true ,  subs.ConsumeInt( out result     ) );   UT_EQ(      45,  result );

        subs.Set( " 42 ; 7 ; 6 "); UT_EQ( true ,  subs.ConsumeInt( out result     ) );   UT_EQ(      42,  result );
                                   UT_EQ( false,  subs.ConsumeInt( out result     ) );   UT_EQ(       0,  result );
                                   UT_EQ( false,  subs.ConsumeInt( out result     ) );   UT_EQ(       0,  result );

        NumberFormat nf= new NumberFormat();
        nf.Whitespaces= " ;".ToCharArray();
        subs.Set( " 42 ; 7 ; 6 "); UT_EQ( true ,  subs.ConsumeInt( out result, nf ) );   UT_EQ(      42,  result );
                                   UT_EQ( true ,  subs.ConsumeInt( out result, nf ) );   UT_EQ(       7,  result );
                                   UT_EQ( true ,  subs.ConsumeInt( out result, nf ) );   UT_EQ(       6,  result );
                                   UT_EQ( false,  subs.ConsumeInt( out result, nf ) );   UT_EQ(       0,  result );
                                   UT_EQ( false,  subs.ConsumeInt( out result, nf ) );   UT_EQ(       0,  result );
    }

    // ConsumeFloat()
    {
        Substring subs= new Substring();
        double result;
        NumberFormat nf= new NumberFormat();
                                        UT_EQ( false,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(      0.0,  result );
        subs.Set( ""        )         ; UT_EQ( false,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(      0.0,  result );
        subs.Set( "  ABC"   )         ; UT_EQ( false,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(      0.0,  result );
        subs.Set( "  12345" )         ; UT_EQ( true ,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(  12345.0,  result );
        subs.Set( " 12.45 " )         ; UT_EQ( true ,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(     12.45, result );
        subs.Set( "  12 45" )         ; UT_EQ( true ,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(     12.0,  result );
                                        UT_EQ( true ,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(     45.0,  result );

        nf.Whitespaces= " ;".ToCharArray();
        subs.Set( " 42.3 ; 0.7 ; 6 " ); UT_EQ( true ,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(     42.3,  result );
                                        UT_EQ( true ,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(      0.7,  result );
                                        UT_EQ( true ,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(      6.0,  result );
                                        UT_EQ( false,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(      0.0,  result );
                                        UT_EQ( false,  subs.ConsumeFloat  ( out result, nf   ) );   UT_EQ(      0.0,  result );
    }
}



//--------------------------------------------------------------------------------------------------
//--- Test IndexOf
//--------------------------------------------------------------------------------------------------
#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings")]
    #endif
#endif
public void IndexOf()
{
    Substring subs;
    // indexOf()
    {
        subs= new Substring("ABCD");
        UT_EQ( -1,      subs.IndexOf('X') );
        UT_EQ(  0,      subs.IndexOf('A') );
        UT_EQ(  1,      subs.IndexOf('B') );
        UT_EQ(  2,      subs.IndexOf('C') );
        UT_EQ(  3,      subs.IndexOf('D') );
    }


    // search characters
    subs.Set( "abc@" +   "abcd abcd" + "abc@de", 4, 9 );
    {
        UT_EQ(   -1 ,  subs.IndexOf( '@', -5   ) );
        UT_EQ(   -1 ,  subs.IndexOf( '@'       ) );
        UT_EQ(   -1 ,  subs.IndexOf( '@', 5    ) );
        UT_EQ(   -1 ,  subs.IndexOf( '@', 150  ) );

        UT_EQ(    0 ,  subs.IndexOf( 'a'       ) );
        UT_EQ(    1 ,  subs.IndexOf( 'b'       ) );
        UT_EQ(    2 ,  subs.IndexOf( 'c'       ) );

        UT_EQ(    0 ,  subs.IndexOf( 'a', 0    ) );
        UT_EQ(    1 ,  subs.IndexOf( 'b', 0    ) );
        UT_EQ(    2 ,  subs.IndexOf( 'c', 0    ) );

        UT_EQ(    5 ,  subs.IndexOf( 'a', 1    ) );
        UT_EQ(    1 ,  subs.IndexOf( 'b', 1    ) );
        UT_EQ(    2 ,  subs.IndexOf( 'c', 1    ) );

        UT_EQ(    5 ,  subs.IndexOf( 'a', 2    ) );
        UT_EQ(    6 ,  subs.IndexOf( 'b', 2    ) );
        UT_EQ(    2 ,  subs.IndexOf( 'c', 2    ) );

        UT_EQ(    5 ,  subs.IndexOf( 'a', 3    ) );
        UT_EQ(    6 ,  subs.IndexOf( 'b', 3    ) );
        UT_EQ(    7 ,  subs.IndexOf( 'c', 3    ) );

        UT_EQ(    8 ,  subs.IndexOf( 'd', 7    ) );
        UT_EQ(    8 ,  subs.IndexOf( 'd', 8    ) );
        UT_EQ(   -1 ,  subs.IndexOf( 'd', 9    ) );
    }

    // search null, empty string
    subs.Set( "abc@" +   "abcd abcd" + "abc@de", 4, 9 );
    {
        UT_EQ(  0 ,  subs.IndexOf( (AString) null       ) );
        UT_EQ(  5 ,  subs.IndexOf( (AString) null,   5  ) );
        UT_EQ( -1 ,  subs.IndexOf( (AString) null,  50  ) );

        UT_EQ(  0 ,  subs.IndexOf( (AString) null, - 5  ) );

        UT_EQ(  0 ,  subs.IndexOf( (String) null        ) );
        UT_EQ(  5 ,  subs.IndexOf( (String) null,    5  ) );
        UT_EQ( -1 ,  subs.IndexOf( (String) null,   50  ) );
        UT_EQ(  0 ,  subs.IndexOf( (String) null, -  5  ) );

        UT_EQ(  0 ,  subs.IndexOf( "",            -  5  ) );
        UT_EQ(  0 ,  subs.IndexOf( "",               0  ) );
        UT_EQ(  4 ,  subs.IndexOf( "",               4  ) );
        UT_EQ( -1 ,  subs.IndexOf( "",             100  ) );
    }

    // search
    subs.Set( "abc@" +   "abcd abcd" + "abc@de", 4, 9 );
    {
        UT_EQ(  0 ,  subs.IndexOf( "abcd"     ) );
        UT_EQ(  1 ,  subs.IndexOf( "b"        ) );
        UT_EQ(  4 ,  subs.IndexOf( " abcd"    ) );
        UT_EQ(  5 ,  subs.IndexOf( "abcd",  1 ) );
        UT_EQ(  0 ,  subs.IndexOf( "abcd",- 1 ) );
        UT_EQ(  -1,  subs.IndexOf( "xyz", -10 ) );
    }

    // ignore case
    String t= "Hello A-Worx util";
    subs.Set( "abc@" +   t + "abc@de", 4, t.Length );
    {
        UT_EQ(  6 ,  subs.IndexOf( "a-worx",   0    ,Case.Ignore ) );
        UT_EQ(  6 ,  subs.IndexOf( "a-worx",   1    ,Case.Ignore ) );
        UT_EQ(  6 ,  subs.IndexOf( "a-worx", -10    ,Case.Ignore ) );
        UT_EQ(  6 ,  subs.IndexOf( "a-worx",   6    ,Case.Ignore ) );
        UT_EQ(  -1,  subs.IndexOf( "a-worx",   7    ,Case.Ignore ) );
        UT_EQ(  -1,  subs.IndexOf( "a-worx", 100    ,Case.Ignore ) );
        UT_EQ(   0,  subs.IndexOf( "hel",      0    ,Case.Ignore ) );
        UT_EQ(  -1,  subs.IndexOf( "hel",      1    ,Case.Ignore ) );
        UT_EQ(  13,  subs.IndexOf( "util",     1    ,Case.Ignore ) );
        UT_EQ(  13,  subs.IndexOf( "UTIL",     5    ,Case.Ignore ) );
        UT_EQ(  13,  subs.IndexOf( "UTIL",    13    ,Case.Ignore ) );
        UT_EQ(  -1,  subs.IndexOf( "UTIL",    14    ,Case.Ignore ) );
    }
    // ------------------ search one of several characters ------------------
    subs.Set( "abc@" +   "abcd abcde" + "abc@de", 4, 10 );
    {
        // search one of
        int l= subs.Length();
        UT_EQ(   4,  subs.IndexOfAny    ( CString.DefaultWhitespaces,Inclusion.Include  ) );
        UT_EQ(  -1,  subs.IndexOfAny    ( "x"    .ToCharArray() ,Inclusion.Include      ) );
        UT_EQ(  -1,  subs.IndexOfAny    ( "xy"   .ToCharArray() ,Inclusion.Include      ) );
        UT_EQ(  -1,  subs.IndexOfAny    ( "xyz"  .ToCharArray() ,Inclusion.Include      ) );
        UT_EQ(   3,  subs.IndexOfAny    ( "xyd"  .ToCharArray() ,Inclusion.Include      ) );
        UT_EQ(   3,  subs.IndexOfAny    ( "d"    .ToCharArray() ,Inclusion.Include      ) );
        UT_EQ(   3,  subs.IndexOfAny    ( "xyd"  .ToCharArray() ,Inclusion.Include,  -2 ) );
        UT_EQ(   8,  subs.IndexOfAny    ( "xyd"  .ToCharArray() ,Inclusion.Include,   4 ) );
        UT_EQ(  -1,  subs.IndexOfAny    ( "xyd"  .ToCharArray() ,Inclusion.Include,  20 ) );

        UT_EQ(  -1,  subs.LastIndexOfAny( ""     .ToCharArray() ,Inclusion.Include      ) );
        UT_EQ(  -1,  subs.LastIndexOfAny( "x"    .ToCharArray() ,Inclusion.Include      ) );
        UT_EQ(  -1,  subs.LastIndexOfAny( "xy"   .ToCharArray() ,Inclusion.Include      ) );
        UT_EQ(  -1,  subs.LastIndexOfAny( "xyz"  .ToCharArray() ,Inclusion.Include      ) );
        UT_EQ(   8,  subs.LastIndexOfAny( "xyd"  .ToCharArray() ,Inclusion.Include      ) );
        UT_EQ(  -1,  subs.LastIndexOfAny( "xyd"  .ToCharArray() ,Inclusion.Include,  -2 ) );
        UT_EQ(  -1,  subs.LastIndexOfAny( "xyd"  .ToCharArray() ,Inclusion.Include,   2 ) );
        UT_EQ(   3,  subs.LastIndexOfAny( "xyd"  .ToCharArray() ,Inclusion.Include,   4 ) );
        UT_EQ(   0,  subs.LastIndexOfAny( "a"    .ToCharArray() ,Inclusion.Include,   4 ) );
        UT_EQ(   1,  subs.LastIndexOfAny( "b"    .ToCharArray() ,Inclusion.Include,   4 ) );
        UT_EQ(   1,  subs.LastIndexOfAny( "ba"   .ToCharArray() ,Inclusion.Include,   4 ) );
        UT_EQ(   0,  subs.LastIndexOfAny( "xa"   .ToCharArray() ,Inclusion.Include,   4 ) );
        UT_EQ(   8,  subs.LastIndexOfAny( "xyd"  .ToCharArray() ,Inclusion.Include,  20 ) );
        UT_EQ(   8,  subs.LastIndexOfAny( "d"    .ToCharArray() ,Inclusion.Include,  20 ) );
        UT_EQ(   9,  subs.LastIndexOfAny( "e"    .ToCharArray() ,Inclusion.Include,  20 ) );

        // search NOT one of
        UT_EQ(   0,  subs.IndexOfAny    ( ""     .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ(   0,  subs.IndexOfAny    ( "x"    .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ(   0,  subs.IndexOfAny    ( "xy"   .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ(   0,  subs.IndexOfAny    ( "xyz"  .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ(   1,  subs.IndexOfAny    ( "a"    .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ(   2,  subs.IndexOfAny    ( "ba"   .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ(   3,  subs.IndexOfAny    ( "abc"  .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ(   3,  subs.IndexOfAny    ( "acb"  .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ(   3,  subs.IndexOfAny    ( "cba"  .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ(   3,  subs.IndexOfAny    ( "xcba" .ToCharArray() ,Inclusion.Exclude      ) );

        UT_EQ( l-1,  subs.LastIndexOfAny( ""     .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ( l-1,  subs.LastIndexOfAny( "x"    .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ( l-1,  subs.LastIndexOfAny( "xy"   .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ( l-2,  subs.LastIndexOfAny( "e"    .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ( l-3,  subs.LastIndexOfAny( "de"   .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ( l-4,  subs.LastIndexOfAny( "cde"  .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ( l-4,  subs.LastIndexOfAny( "ced"  .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ( l-4,  subs.LastIndexOfAny( "ecd"  .ToCharArray() ,Inclusion.Exclude      ) );
        UT_EQ(   5,  subs.LastIndexOfAny( "ecd"  .ToCharArray() ,Inclusion.Exclude, 5   ) );
        UT_EQ(   4,  subs.LastIndexOfAny( "ecd"  .ToCharArray() ,Inclusion.Exclude, 4   ) );
        UT_EQ(   1,  subs.LastIndexOfAny( "acd"  .ToCharArray() ,Inclusion.Exclude, 3   ) );
        UT_EQ(  -1,  subs.LastIndexOfAny( "abc"  .ToCharArray() ,Inclusion.Exclude, 2   ) );
        UT_EQ(   3,  subs.LastIndexOfAny( "xay"  .ToCharArray() ,Inclusion.Exclude, 3   ) );
        UT_EQ(   2,  subs.LastIndexOfAny( "d"    .ToCharArray() ,Inclusion.Exclude, 3   ) );
        UT_EQ(  -1,  subs.LastIndexOfAny( "a"    .ToCharArray() ,Inclusion.Exclude, 0   ) );
    }

}

//--------------------------------------------------------------------------------------------------
//--- Test IndexOf
//--------------------------------------------------------------------------------------------------
#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings")]
    #endif
#endif
public void Trim()
{
    Substring subs= new Substring();
    {
        String t;
        t= ""          ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( ""            , subs.ToString() );
        t= " "         ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( ""            , subs.ToString() );
        t= "  "        ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( ""            , subs.ToString() );
        t= "abc"       ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( "abc"         , subs.ToString() );
        t= "abc"       ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( "abc"         , subs.ToString() );
        t= " abc"      ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( "abc"         , subs.ToString() );
        t= "  abc"     ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( "abc"         , subs.ToString() );
        t= " \tabc"    ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( "abc"         , subs.ToString() );
        t= "\t abc"    ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( "abc"         , subs.ToString() );
        t= "abc\r\n"   ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( "abc"         , subs.ToString() );
        t= "\tabc\r\n" ; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( "abc"         , subs.ToString() );
        t= "\tabc\rx\n"; subs.Set(" pad " + t + " abc ", 5, t.Length).Trim();        UT_EQ( "abc\rx"      , subs.ToString() );
    }
}

//--------------------------------------------------------------------------------------------------
//--- Test CompareTo
//--------------------------------------------------------------------------------------------------

#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings")]
    #endif
#endif
public void CompareTo()
{
    Substring tss= new Substring();

    // null string comparison

    String  nullString= null;
    UT_TRUE( tss.CompareTo( nullString) == 0 );
    UT_TRUE( tss.Equals( nullString) );

    tss.Set( "" );
    UT_TRUE( tss.CompareTo( nullString) != 0 );
    UT_TRUE( !tss.Equals( nullString) );

    tss.SetNull();
    UT_TRUE( tss.CompareTo( nullString) == 0 );
    UT_TRUE( tss.Equals( nullString) );

    String t= "abcde";
    tss= new Substring("01"+t+"234", 2, t.Length );

    int result, resSys;
    result= tss.CompareTo( t      );                                     UT_EQ( t.CompareTo( t ),                                result );
    result= tss.CompareTo( t + "x"      );                               UT_EQ( t.CompareTo( t + "x" ),                          result );
    result= tss.CompareTo( t.Substring (0, t.Length -1 )  );             UT_EQ( t.CompareTo( t.Substring (0, t.Length -1 ) ),    result );
    result= tss.CompareTo( "pad" + t,  Case.Sensitive, 3            );   UT_EQ(  0,                                              result );
    result= tss.CompareTo( "pad" + t,  Case.Sensitive, 3, 2         );   UT_EQ(  1,                                              result );


    // greater/smaller strings
    {
        String greater=  "x";
        String greater2= "abcdef";
        String smaller=  "aaa";
        String smaller2= "abcd";
        result= tss.CompareTo( greater  );  resSys= t.CompareTo( greater  ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        result= tss.CompareTo( greater2 );  resSys= t.CompareTo( greater2 ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        result= tss.CompareTo( smaller  );  resSys= t.CompareTo( smaller  ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        result= tss.CompareTo( smaller2 );  resSys= t.CompareTo( smaller2 ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        String ut= t.ToUpper();
        UT_FALSE( 0 ==  tss.CompareTo( ut )                );
        UT_FALSE( 0 ==  tss.CompareTo( ut, Case.Sensitive ));
        UT_TRUE ( 0 ==  tss.CompareTo( ut, Case.Ignore    ));
    }

    {
        AString greater=  new AString( "x"      );
        AString greater2= new AString( "abcdef" );
        AString smaller=  new AString( "aaa"    );
        AString smaller2= new AString( "abcd"   );
        result= tss.CompareTo( greater  );  resSys= t.CompareTo( greater  .ToString() ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        result= tss.CompareTo( greater2 );  resSys= t.CompareTo( greater2 .ToString() ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        result= tss.CompareTo( smaller  );  resSys= t.CompareTo( smaller  .ToString() ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        result= tss.CompareTo( smaller2 );  resSys= t.CompareTo( smaller2 .ToString() ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        AString ut= new AString (t.ToUpper());
        UT_FALSE( 0 ==  tss.CompareTo( ut )                );
        UT_FALSE( 0 ==  tss.CompareTo( ut, Case.Sensitive ));
        UT_TRUE ( 0 ==  tss.CompareTo( ut, Case.Ignore    ));
    }
    {
        Substring greater=  new Substring( "123x"       , 3 );
        Substring greater2= new Substring( "123abcdef"  , 3 );
        Substring smaller=  new Substring( "123aaa"     , 3 );
        Substring smaller2= new Substring( "123abcd"    , 3 );
        result= tss.CompareTo( greater  );  resSys= t.CompareTo( greater  .ToString() ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        result= tss.CompareTo( greater2 );  resSys= t.CompareTo( greater2 .ToString() ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        result= tss.CompareTo( smaller  );  resSys= t.CompareTo( smaller  .ToString() ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        result= tss.CompareTo( smaller2 );  resSys= t.CompareTo( smaller2 .ToString() ); UT_TRUE( result==resSys || (result < 0 && resSys < 0) || (result > 0 && resSys > 0) );
        Substring ut= new Substring( t.ToUpper() );
        UT_FALSE( 0 ==  tss.CompareTo( ut )                );
        UT_FALSE( 0 ==  tss.CompareTo( ut, Case.Sensitive ));
        UT_TRUE ( 0 ==  tss.CompareTo( ut, Case.Ignore    ));
    }
}


//--------------------------------------------------------------------------------------------------
//--- Test Tokenizer
//--------------------------------------------------------------------------------------------------
void tokenizerTest( string inputString, AString res, char delim, char newDelim,
                    Whitespaces trim, int inpStart= -1, int inpEnd= -1  )
{
    Substring inp= new Substring( inputString );
    if ( inpStart >= 0 ) inp.Start= inpStart;
    if ( inpEnd   >= 0 ) inp.End=   inpEnd;
    res.Clear();

    Tokenizer tknzr= new Tokenizer( inp, delim );

    while( tknzr.HasNext() )
    {
        tknzr.Next(trim).CopyTo( res, true );
        res._( newDelim );
    }

}

#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
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
        Tokenizer tknzr= new Tokenizer( astr, ',' );   UT_EQ( true,  tknzr.HasNext() );
        tknzr.Next().CopyTo( res, true );              UT_EQ( "", res );
    }

    // tokenizing no delim
    astr.Clear()._( "abc" );
    res.Clear();
    {
        Tokenizer tknzr= new Tokenizer( astr, ',' );                UT_EQ( true,  tknzr.HasNext() );
        tknzr.Next().CopyTo( res, true );     UT_EQ( "abc", res );
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
        Tokenizer tknzr= new Tokenizer(astr, ',');
        tknzr.Next()                       .CopyTo( res );    UT_EQ ( "1",   res );  UT_EQ( true,  tknzr.HasNext() );
        tknzr.Next( Whitespaces.Trim, ';' ).CopyTo( res );    UT_EQ ( "5",   res );  UT_EQ( true,  tknzr.HasNext() );
        tknzr.Next( Whitespaces.Trim, '@' ).CopyTo( res );    UT_EQ ( "3",   res );  UT_EQ( true,  tknzr.HasNext() );
        tknzr.Next( Whitespaces.Trim, '-' ).CopyTo( res );    UT_EQ ( "4",   res );  UT_EQ( false, tknzr.HasNext() );
    }

    // tokenizing with different delimiters
    {
        astr.Clear()._( "abc, 5;\t3;;; 4  " );
        Tokenizer tknzr= new Tokenizer(astr,',');
        tknzr.Next()                       .CopyTo( res );    UT_EQ ( "abc", res );  UT_EQ( true,  tknzr.HasNext() );
        tknzr.Next( Whitespaces.Trim, ';' ).CopyTo( res );    UT_EQ ( "5",   res );  UT_EQ( true,  tknzr.HasNext() );
        tknzr.Next()                       .CopyTo( res );    UT_EQ ( "3",   res );  UT_EQ( true,  tknzr.HasNext() );
        tknzr.Next()                       .CopyTo( res );    UT_EQ ( "",    res );  UT_EQ( true,  tknzr.HasNext() );
        tknzr.GetRest()                    .CopyTo( res );    UT_EQ ( "; 4", res );  UT_EQ( false, tknzr.HasNext() );
    }

    // sub-tokens
    {
        astr.Clear()._( "1,2;3 , 4;5,;," );
        Tokenizer tknzr= new Tokenizer(astr, ';');

        Tokenizer tknzr2= new Tokenizer( tknzr.Next(), ',');
        tknzr2.Next().CopyTo( res ); UT_EQ ( "1", res );  UT_TRUE(  tknzr2.HasNext() );
        tknzr2.Next().CopyTo( res ); UT_EQ ( "2", res );  UT_TRUE( !tknzr2.HasNext() );
        UT_TRUE( tknzr.HasNext() );

        tknzr2.Set( tknzr.Next(), ',');
        tknzr2.Next().CopyTo( res ); UT_EQ ( "3", res );  UT_TRUE(  tknzr2.HasNext() );
        tknzr2.Next().CopyTo( res ); UT_EQ ( "4", res );  UT_TRUE( !tknzr2.HasNext() );
        UT_TRUE( tknzr.HasNext() );

        tknzr2.Set( tknzr.Next(), ',');
        tknzr2.Next().CopyTo( res ); UT_EQ ( "5", res );  UT_TRUE(  tknzr2.HasNext() );
        tknzr2.Next().CopyTo( res ); UT_EQ ( "",  res );  UT_TRUE( !tknzr2.HasNext() );
        UT_TRUE( tknzr.HasNext() );

        tknzr2.Set( tknzr.Next(), ',');
        tknzr2.Next().CopyTo( res ); UT_EQ ( "", res );  UT_TRUE(  tknzr2.HasNext() );
        tknzr2.Next().CopyTo( res ); UT_EQ ( "", res );  UT_TRUE( !tknzr2.HasNext() );
        UT_TRUE( !tknzr.HasNext() );
    }
}



    } // class
}//namespace
