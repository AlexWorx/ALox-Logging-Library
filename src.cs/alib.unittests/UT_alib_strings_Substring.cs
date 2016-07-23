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
    public class CS_Strings_Substring  : AWorxUnitTesting
    {


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


#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
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
#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
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
#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
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
            UT_EQ(  '\0',      s.Consume       ( )         );
            UT_EQ(  0,         s.Consume       (  0   , r) ); UT_TRUE(r.IsNull());
            UT_EQ(  0,         s.Consume       (  5   , r) ); UT_TRUE(r.IsNull());
            UT_EQ(  false,     s.Consume       ( 'a' )     );
            UT_EQ(  false,     s.Consume       ( "word" )  );
            UT_EQ(  '\0',      s.ConsumeFromEnd( )         );
            UT_EQ(  0,         s.ConsumeFromEnd(  0  )     );
            UT_EQ(  0,         s.ConsumeFromEnd(  5  )     );
            UT_EQ(  false,     s.ConsumeFromEnd( 'a' )     );
            UT_EQ(  false,     s.ConsumeFromEnd( "word" )  );
        }

        // empty substring
        {
            Substring s= new Substring("aaaaaaaaaaaa");
            Substring r= new Substring("oldval");
            s.Start= 5;
            s.End=   4;
            UT_EQ(  '\0',      s.Consume       ( )         );
            UT_EQ(  0,         s.Consume       (  0  ,r )  ); UT_TRUE( r.IsNotNull()); UT_TRUE(r.IsEmpty());
            UT_EQ(  0,         s.Consume       (  5  ,r )  ); UT_TRUE( r.IsNotNull()); UT_TRUE(r.IsEmpty());
            UT_EQ(  false,     s.Consume       ( 'a' )     );
            UT_EQ(  false,     s.Consume       ( "word" )  );
            UT_EQ(  '\0',      s.ConsumeFromEnd( )         );
            UT_EQ(  0,         s.ConsumeFromEnd(  0  )     );
            UT_EQ(  0,         s.ConsumeFromEnd(  5  )     );
            UT_EQ(  false,     s.ConsumeFromEnd( 'a' )     );
            UT_EQ(  false,     s.ConsumeFromEnd( "word" )  );
        }

        // substring of length 1
        {
            Substring s= new Substring("aaaaaaaaaaaa");
            Substring r= new Substring("oldval");

            s.Start= s.End= 5; UT_EQ(  'a',       s.Consume       ( )         ); UT_EQ( 0, s.Length() );
            s.Start= s.End= 5; UT_EQ(  1,         s.Consume       (  0  )     ); UT_EQ( 1, s.Length() );
            s.Start= s.End= 5; UT_EQ(  0,         s.Consume       (  1  , r ) ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("a"));
            s.Start= s.End= 5; UT_EQ(  0,         s.Consume       (  5  , r ) ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("a"));
            s.Start= s.End= 5; UT_EQ(  true,      s.Consume       ( 'a' )     ); UT_EQ( 0, s.Length() );
            s.Start= s.End= 5; UT_EQ(  false,     s.Consume       ( 'b' )     ); UT_EQ( 1, s.Length() );
            s.Start= s.End= 5; UT_EQ(  false,     s.Consume       ( "word" )  ); UT_EQ( 1, s.Length() );
            s.Start= s.End= 5; UT_EQ(  'a',       s.ConsumeFromEnd( )         ); UT_EQ( 0, s.Length() );
            s.Start= s.End= 5; UT_EQ(  1,         s.ConsumeFromEnd(  0  )     ); UT_EQ( 1, s.Length() );
            s.Start= s.End= 5; UT_EQ(  0,         s.ConsumeFromEnd(  1  )     ); UT_EQ( 0, s.Length() );
            s.Start= s.End= 5; UT_EQ(  0,         s.ConsumeFromEnd(  5  )     ); UT_EQ( 0, s.Length() );
            s.Start= s.End= 5; UT_EQ(  true,      s.ConsumeFromEnd( 'a' )     ); UT_EQ( 0, s.Length() );
            s.Start= s.End= 5; UT_EQ(  false,     s.ConsumeFromEnd( 'b' )     ); UT_EQ( 1, s.Length() );
            s.Start= s.End= 5; UT_EQ(  false,     s.ConsumeFromEnd( "word" )  ); UT_EQ( 1, s.Length() );
        }

        // substring of length 2
        {
            Substring s= new Substring("12ab3456");
            Substring r= new Substring("oldval");

            s.Start= 2; s.End= 3; UT_EQ(  'a',       s.Consume       ( )         ); UT_EQ( 1, s.Length() );
                                  UT_EQ(  'b',       s.Consume       ( )         ); UT_EQ( 0, s.Length() );
            s.Start= 2; s.End= 3; UT_EQ(  'b',       s.ConsumeFromEnd( )         ); UT_EQ( 1, s.Length() );
                                  UT_EQ(  'a',       s.ConsumeFromEnd( )         ); UT_EQ( 0, s.Length() );

            s.Start= 2; s.End= 3; UT_EQ(  2,         s.Consume       (  0 , r )  ); UT_EQ( 2, s.Length() ); UT_TRUE(r.IsNotNull()); UT_TRUE(r.IsEmpty());
            s.Start= 2; s.End= 3; UT_EQ(  1,         s.Consume       (  1 , r )  ); UT_EQ( 1, s.Length() ); UT_TRUE(r.Equals("a"));
            s.Start= 2; s.End= 3; UT_EQ(  0,         s.Consume       (  2 , r )  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));
            s.Start= 2; s.End= 3; UT_EQ(  0,         s.Consume       (  3 , r )  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));
            s.Start= 2; s.End= 3; UT_EQ(  2,         s.ConsumeFromEnd(  0 , r )  ); UT_EQ( 2, s.Length() ); UT_TRUE(r.IsNotNull()); UT_TRUE(r.IsEmpty());
            s.Start= 2; s.End= 3; UT_EQ(  1,         s.ConsumeFromEnd(  1 , r )  ); UT_EQ( 1, s.Length() ); UT_TRUE(r.Equals("b"));
            s.Start= 2; s.End= 3; UT_EQ(  0,         s.ConsumeFromEnd(  2 , r )  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));
            s.Start= 2; s.End= 3; UT_EQ(  0,         s.ConsumeFromEnd(  3 , r )  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));

            s.Start= 2; s.End= 3; UT_EQ(  false,     s.Consume       ( 'b' )     ); UT_EQ( 2, s.Length() );
                                  UT_EQ(  true,      s.Consume       ( 'a' )     ); UT_EQ( 1, s.Length() );
                                  UT_EQ(  true,      s.Consume       ( 'b' )     ); UT_EQ( 0, s.Length() );
                                  UT_EQ(  false,     s.Consume       ( 'a' )     ); UT_EQ( 0, s.Length() );
                                  UT_EQ(  false,     s.Consume       ( 'b' )     ); UT_EQ( 0, s.Length() );
            s.Start= 2; s.End= 3; UT_EQ(  false,     s.ConsumeFromEnd( 'a' )     ); UT_EQ( 2, s.Length() );
                                  UT_EQ(  true,      s.ConsumeFromEnd( 'b' )     ); UT_EQ( 1, s.Length() );
                                  UT_EQ(  true,      s.ConsumeFromEnd( 'a' )     ); UT_EQ( 0, s.Length() );
                                  UT_EQ(  false,     s.ConsumeFromEnd( 'b' )     ); UT_EQ( 0, s.Length() );
                                  UT_EQ(  false,     s.ConsumeFromEnd( 'a' )     ); UT_EQ( 0, s.Length() );

            s.Start= 2; s.End= 3; UT_EQ(  false,     s.Consume       ( "word" )  ); UT_EQ( 2, s.Length() );
            s.Start= 2; s.End= 3; UT_EQ(  false,     s.Consume       ( "AB"   )  ); UT_EQ( 2, s.Length() );
            s.Start= 2; s.End= 3; UT_EQ(  true,      s.Consume       ( "ab"   )  ); UT_EQ( 0, s.Length() );
            s.Start= 2; s.End= 3; UT_EQ(  false,     s.ConsumeFromEnd( "word" )  ); UT_EQ( 2, s.Length() );
            s.Start= 2; s.End= 3; UT_EQ(  false,     s.ConsumeFromEnd( "AB"   )  ); UT_EQ( 2, s.Length() );
            s.Start= 2; s.End= 3; UT_EQ(  true,      s.ConsumeFromEnd( "ab"   )  ); UT_EQ( 0, s.Length() );
        }

        // 3 words
        {
            Substring s= new Substring("word1 word2 word3");

            UT_EQ(  'w',       s.Consume       ( )         );
            UT_EQ(  'o',       s.Consume       ( )         );
            UT_EQ(  'r',       s.Consume       ( )         );
            UT_EQ(  'd',       s.Consume       ( )         );
            UT_EQ(  '1',       s.Consume       ( )         );

            UT_EQ(  false    , s.Consume       ('w'                        )   );
            UT_EQ(  true     , s.Consume       ('w'     , Case.Sensitive, Whitespaces.Trim )   );
            UT_EQ(  true     , s.Consume       ('o'     , Case.Sensitive, Whitespaces.Trim )   );
            UT_EQ(  false    , s.Consume       ('o'     , Case.Sensitive, Whitespaces.Trim )   );
            UT_EQ(  true     , s.Consume       ('r'     , Case.Sensitive, Whitespaces.Trim )   );
            UT_EQ(  false    , s.Consume       ("D2"    , Case.Sensitive, Whitespaces.Trim )   );
            UT_EQ(  false    , s.Consume       ("D2"                       )   );
            UT_EQ(  true     , s.Consume       ("d2"                       )   );

            UT_EQ(  2        , s.Consume       ( 4 )   );
            UT_EQ(  "d3"     , s.ToString() );

                      s= new Substring("word1 word2 word3");

            UT_EQ(  '3',       s.ConsumeFromEnd( )         );
            UT_EQ(  'd',       s.ConsumeFromEnd( )         );
            UT_EQ(  'r',       s.ConsumeFromEnd( )         );
            UT_EQ(  'o',       s.ConsumeFromEnd( )         );
            UT_EQ(  'w',       s.ConsumeFromEnd( )         );

            UT_EQ(  false    , s.ConsumeFromEnd('2'                        )   );
            UT_EQ(  true     , s.ConsumeFromEnd('2'     , Case.Sensitive, Whitespaces.Trim )   );
            UT_EQ(  true     , s.ConsumeFromEnd('d'     , Case.Sensitive, Whitespaces.Trim )   );
            UT_EQ(  false    , s.ConsumeFromEnd('d'     , Case.Sensitive, Whitespaces.Trim )   );
            UT_EQ(  true     , s.ConsumeFromEnd('r'     , Case.Sensitive, Whitespaces.Trim )   );
            UT_EQ(  false    , s.ConsumeFromEnd("WO"    , Case.Sensitive, Whitespaces.Trim )   );
            UT_EQ(  false    , s.ConsumeFromEnd("WO"                       )   );
            UT_EQ(  true     , s.ConsumeFromEnd("wo"                       )   );

            UT_EQ(  2        , s.ConsumeFromEnd( 4 )   );
            UT_EQ(  "wo"     , s.ToString() );
        }

        // consume AString, Substring
        {
            Substring s= new Substring("word1 word2 word3 word4");
            Substring sConsume= new Substring( "1234word12", 4, 4 );
            AString   aConsume= new AString  (     "word"         );

            UT_EQ(  true,      s.Consume       ( sConsume )  );
            UT_EQ(  false,     s.Consume       ( sConsume )  );
            UT_EQ(  '1',       s.Consume       ( )           );
            UT_EQ(  false,     s.Consume       ( sConsume )  );
            UT_EQ(  true,      s.Consume       ( sConsume, Case.Sensitive, Whitespaces.Trim ) );
            UT_EQ(  '2',       s.Consume       ( )           );
            UT_EQ(  ' ',       s.Consume       ( )           );

            UT_EQ(  true,      s.Consume       ( aConsume )  );
            UT_EQ(  false,     s.Consume       ( aConsume )  );
            UT_EQ(  '3',       s.Consume       ( )           );
            UT_EQ(  false,     s.Consume       ( aConsume )  );
            UT_EQ(  true,      s.Consume       ( aConsume, Case.Sensitive, Whitespaces.Trim ) );

                      s.Set("1word  2word 3word  4word");

            UT_EQ(  true,      s.ConsumeFromEnd( sConsume )  );
            UT_EQ(  false,     s.ConsumeFromEnd( sConsume )  );
            UT_EQ(  '4',       s.ConsumeFromEnd( )           );
            UT_EQ(  false,     s.ConsumeFromEnd( sConsume )  );
            UT_EQ(  true,      s.ConsumeFromEnd( sConsume, Case.Sensitive, Whitespaces.Trim ) );
            UT_EQ(  '3',       s.ConsumeFromEnd( )           );
            UT_EQ(  ' ',       s.ConsumeFromEnd( )           );

            UT_EQ(  true,      s.ConsumeFromEnd( aConsume )  );
            UT_EQ(  false,     s.ConsumeFromEnd( aConsume )  );
            UT_EQ(  '2',       s.ConsumeFromEnd( )           );
            UT_EQ(  false,     s.ConsumeFromEnd( aConsume )  );
            UT_EQ(  true,      s.ConsumeFromEnd( aConsume, Case.Sensitive, Whitespaces.Trim ) );
        }
    }


    //--------------------------------------------------------------------------------------------------
    //--- Test IndexOf
    //--------------------------------------------------------------------------------------------------
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
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
    #if ALIB_MONO_DEVELOP
        [Test ()]
    #endif
    #if ALIB_VSTUDIO
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

#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
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
//--- Test IndexOf
//--------------------------------------------------------------------------------------------------
#if ALIB_MONO_DEVELOP
    [Test ()]
#endif
#if ALIB_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings")]
    #endif
#endif
public void ParseNumbers()
{
    // ConsumeInteger()
    {
        Substring subs= new Substring();
        int result;
                                   UT_EQ( false,  subs.ConsumeInteger( out result                ) );   UT_EQ(       0,  result );
        subs.Set( ""            ); UT_EQ( false,  subs.ConsumeInteger( out result                ) );   UT_EQ(       0,  result );
        subs.Set( "  ABC"       ); UT_EQ( false,  subs.ConsumeInteger( out result                ) );   UT_EQ(       0,  result );
        subs.Set( "  12345"     ); UT_EQ( true ,  subs.ConsumeInteger( out result                ) );   UT_EQ(   12345,  result );
        subs.Set( "  12 45"     ); UT_EQ( true ,  subs.ConsumeInteger( out result                ) );   UT_EQ(      12,  result );
                                   UT_EQ( true ,  subs.ConsumeInteger( out result                ) );   UT_EQ(      45,  result );

        subs.Set( " 42 ; 7 ; 6 "); UT_EQ( true ,  subs.ConsumeInteger( out result                ) );   UT_EQ(      42,  result );
                                   UT_EQ( false,  subs.ConsumeInteger( out result                ) );   UT_EQ(       0,  result );
                                   UT_EQ( false,  subs.ConsumeInteger( out result                ) );   UT_EQ(       0,  result );

        char[] ws= " ;".ToCharArray();
        subs.Set( " 42 ; 7 ; 6 "); UT_EQ( true ,  subs.ConsumeInteger( out result, ws            ) );   UT_EQ(      42,  result );
                                   UT_EQ( true ,  subs.ConsumeInteger( out result, ws            ) );   UT_EQ(       7,  result );
                                   UT_EQ( true ,  subs.ConsumeInteger( out result, ws            ) );   UT_EQ(       6,  result );
                                   UT_EQ( false,  subs.ConsumeInteger( out result, ws            ) );   UT_EQ(       0,  result );
                                   UT_EQ( false,  subs.ConsumeInteger( out result, ws            ) );   UT_EQ(       0,  result );
    }

    // ConsumeFloat()
    {
        Substring subs= new Substring();
        double result;
                                        UT_EQ( false,  subs.ConsumeFloat  ( out result             ) );   UT_EQ(      0.0,  result );
        subs.Set( ""        )         ; UT_EQ( false,  subs.ConsumeFloat  ( out result             ) );   UT_EQ(      0.0,  result );
        subs.Set( "  ABC"   )         ; UT_EQ( false,  subs.ConsumeFloat  ( out result             ) );   UT_EQ(      0.0,  result );
        subs.Set( "  12345" )         ; UT_EQ( true ,  subs.ConsumeFloat  ( out result             ) );   UT_EQ(  12345.0,  result );
        subs.Set( " 12.45 " )         ; UT_EQ( true ,  subs.ConsumeFloat  ( out result             ) );   UT_EQ(     12.45, result );
        subs.Set( "  12 45" )         ; UT_EQ( true ,  subs.ConsumeFloat  ( out result             ) );   UT_EQ(     12.0,  result );
                                        UT_EQ( true ,  subs.ConsumeFloat  ( out result             ) );   UT_EQ(     45.0,  result );

        char[] ws= " ;".ToCharArray();
        subs.Set( " 42.3 ; 0.7 ; 6 " ); UT_EQ( true ,  subs.ConsumeFloat  ( out result, null, ws   ) );   UT_EQ(     42.3,  result );
                                        UT_EQ( true ,  subs.ConsumeFloat  ( out result, null, ws   ) );   UT_EQ(      0.7,  result );
                                        UT_EQ( true ,  subs.ConsumeFloat  ( out result, null, ws   ) );   UT_EQ(      6.0,  result );
                                        UT_EQ( false,  subs.ConsumeFloat  ( out result, null, ws   ) );   UT_EQ(      0.0,  result );
                                        UT_EQ( false,  subs.ConsumeFloat  ( out result, null, ws   ) );   UT_EQ(      0.0,  result );
    }

}




    }
}
