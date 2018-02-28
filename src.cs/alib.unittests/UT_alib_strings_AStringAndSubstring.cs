// #################################################################################################
//  cs.aworx.unittests - AWorx Util
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Globalization;
using cs.aworx.lox;
using cs.aworx.lox.loggers;
using cs.aworx.lib.strings;
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
    #if ALIB_NUNIT
        [TestFixture ()]
    #endif
    #if ALIB_IDE_VSTUDIO
        [TestClass]
    #endif
    public class CS_Strings_AStringAndSubstring  : AWorxUnitTesting
    {
    //--------------------------------------------------------------------------------------------------
    //--- Test Compare
    //--------------------------------------------------------------------------------------------------
    AString     haystackAString  = new AString();
    Substring   haystackSubstring= new Substring();
    AString     needleAString    = new AString();
    Substring   needleSubstring  = new Substring();
    void tStartsWith( String haystack, String needle, bool expectedSensitive  , bool expectedIgnoreCase )
    {
        haystackAString._()._( haystack );
        haystackSubstring.Set( "01" + haystack + "234" , 2, haystack.Length );


        if ( needle != null)
        {
            UT_EQ( expectedSensitive  , haystackAString  .StartsWith( needle                ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .StartsWith( needle                ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.StartsWith( needle                ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.StartsWith( needle                ,Case.Ignore    ) );
            needleAString._()._( needle );
            UT_EQ( expectedSensitive  , haystackAString  .StartsWith( needleAString         ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .StartsWith( needleAString         ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.StartsWith( needleAString         ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.StartsWith( needleAString         ,Case.Ignore    ) );

            needleSubstring.Set( "XY" + needle + "Z", 2, needle.Length ).Trim();
            UT_EQ( expectedSensitive  , haystackAString  .StartsWith( needleSubstring       ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .StartsWith( needleSubstring       ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.StartsWith( needleSubstring       ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.StartsWith( needleSubstring       ,Case.Ignore    ) );

        }
        else
        {
            UT_EQ( expectedSensitive  , haystackAString  .StartsWith( needle                ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .StartsWith( needle                ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackAString  .StartsWith((AString) null         ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .StartsWith((AString) null         ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackAString  .StartsWith((Substring) null       ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .StartsWith((Substring) null       ,Case.Ignore    ) );

            UT_EQ( expectedSensitive  , haystackSubstring.StartsWith( needle                ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.StartsWith( needle                ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.StartsWith((AString) null         ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.StartsWith((AString) null         ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.StartsWith((Substring) null       ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.StartsWith((Substring) null       ,Case.Ignore    ) );
        }
    }

    void tEndsWith( String haystack, String needle, bool expectedSensitive  , bool expectedIgnoreCase )
    {
        haystackAString._()._( haystack );
        haystackSubstring.Set( "01" + haystack + "234" , 2, haystack.Length );

        if ( needle != null)
        {
            UT_EQ( expectedSensitive  , haystackAString  .EndsWith( needle                  ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .EndsWith( needle                  ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.EndsWith( needle                  ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.EndsWith( needle                  ,Case.Ignore    ) );
            needleAString._()._( needle );
            UT_EQ( expectedSensitive  , haystackAString  .EndsWith( needleAString           ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .EndsWith( needleAString           ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.EndsWith( needleAString           ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.EndsWith( needleAString           ,Case.Ignore    ) );
            needleSubstring.Set( "XY" + needle + "Z", 2, needle.Length ).Trim();
            UT_EQ( expectedSensitive  , haystackAString  .EndsWith( needleSubstring         ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .EndsWith( needleSubstring         ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.EndsWith( needleSubstring         ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.EndsWith( needleSubstring         ,Case.Ignore    ) );

        }
        else
        {
            UT_EQ( expectedSensitive  , haystackAString  .EndsWith( needle                  ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .EndsWith( needle                  ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackAString  .EndsWith((AString) null           ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .EndsWith((AString) null           ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackAString  .EndsWith((Substring) null         ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .EndsWith((Substring) null         ,Case.Ignore    ) );

            UT_EQ( expectedSensitive  , haystackSubstring.EndsWith( needle                  ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.EndsWith( needle                  ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.EndsWith((AString) null           ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.EndsWith((AString) null           ,Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.EndsWith((Substring) null         ,Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.EndsWith((Substring) null         ,Case.Ignore    ) );
        }
    }

    void tEquals( String haystack, String needle, bool expectedSensitive  , bool expectedIgnoreCase )
    {
        haystackAString._()._( haystack );
        haystackSubstring.Set( "01" + haystack + "234" , 2, haystack.Length );

        if ( needle != null)
        {
            UT_EQ( expectedSensitive  , haystackAString  .Equals( needle                    , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .Equals( needle                    , Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.Equals( needle                    , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.Equals( needle                    , Case.Ignore    ) );
            needleAString._()._( needle );
            UT_EQ( expectedSensitive  , haystackAString  .Equals( needleAString             , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .Equals( needleAString             , Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.Equals( needleAString             , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.Equals( needleAString             , Case.Ignore    ) );

            needleSubstring.Set( "XY" + needle + "Z", 2, needle.Length ).Trim();
            UT_EQ( expectedSensitive  , haystackAString  .Equals( needleSubstring           , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .Equals( needleSubstring           , Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.Equals( needleSubstring           , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.Equals( needleSubstring           , Case.Ignore    ) );
        }
        else
        {
            UT_EQ( expectedSensitive  , haystackAString  .Equals(  needle                   , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .Equals(  needle                   , Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackAString  .Equals( (AString) null            , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .Equals( (AString) null            , Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackAString  .Equals( (Substring) null          , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .Equals( (Substring) null          , Case.Ignore    ) );

            UT_EQ( expectedSensitive  , haystackSubstring.Equals(  needle                   , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.Equals(  needle                   , Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.Equals( (AString) null            , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.Equals( (AString) null            , Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.Equals( (Substring) null          , Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.Equals( (Substring) null          , Case.Ignore    ) );
        }
    }


    void tContainsAt( String haystack, String needle, int pos, bool expectedSensitive  , bool expectedIgnoreCase )
    {
        haystackAString._()._( haystack );
        haystackSubstring.Set( "01" + haystack + "234" , 2, haystack.Length );

        if ( needle != null)
        {
            UT_EQ( expectedSensitive  , haystackAString  .ContainsAt( needle                , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .ContainsAt( needle                , pos, Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.ContainsAt( needle                , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.ContainsAt( needle                , pos, Case.Ignore    ) );
            needleAString._()._( needle );
            UT_EQ( expectedSensitive  , haystackAString  .ContainsAt( needleAString         , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .ContainsAt( needleAString         , pos, Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.ContainsAt( needleAString         , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.ContainsAt( needleAString         , pos, Case.Ignore    ) );

            needleSubstring.Set( "XY" + needle + "Z", 2, needle.Length ).Trim();
            UT_EQ( expectedSensitive  , haystackAString  .ContainsAt( needleSubstring       , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .ContainsAt( needleSubstring       , pos, Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.ContainsAt( needleSubstring       , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.ContainsAt( needleSubstring       , pos, Case.Ignore    ) );
        }
        else
        {
            UT_EQ( expectedSensitive  , haystackAString  .ContainsAt(  needle               , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .ContainsAt(  needle               , pos, Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackAString  .ContainsAt( (AString) null        , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .ContainsAt( (AString) null        , pos, Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackAString  .ContainsAt( (Substring) null      , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .ContainsAt( (Substring) null      , pos, Case.Ignore    ) );

            UT_EQ( expectedSensitive  , haystackSubstring.ContainsAt(  needle               , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.ContainsAt(  needle               , pos, Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.ContainsAt( (AString) null        , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.ContainsAt( (AString) null        , pos, Case.Ignore    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.ContainsAt( (Substring) null      , pos, Case.Sensitive ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.ContainsAt( (Substring) null      , pos, Case.Ignore    ) );
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
    public void Compare()
    {
        // StartsWith/Endsweith
        tStartsWith( "ABCDEF"     , "ABC",    true,  true  );
        tStartsWith( "ABCDEF"     , "abc",    false, true  );
        tEndsWith  ( "123ABC"     , "ABC",    true,  true  );
        tEndsWith  ( "123ABC"     , "abc",    false, true  );
        tContainsAt( "##12ABC21##", "ABC", 4, true,  true  );
        tContainsAt( "##12ABC21##", "abc", 4, false, true  );
        tContainsAt( "##12ABC21##", "abc", 3, false, false );
        tContainsAt( "AB"         , "ABC", 4, false, false );
        tContainsAt( "AB"         , "abc", 4, false, false );
        tContainsAt( "AB"         , "abc", 3, false, false );

        String s= "Hello A-Worx util" ;

        tStartsWith( s, "Hello A-Worx util",  true  , true  );
        tStartsWith( s, "Hello A-Worx utilx", false , false );
        tStartsWith( s, "heLLO",              false , true  );
        tStartsWith( s, "HeLLO",              false , true  );
        tStartsWith( s, "UTIL" ,              false , false );

        tEndsWith  ( s, "Hello A-Worx util",  true  , true  );
        tEndsWith  ( s, "xHello A-Worx util", false , false );
        tEndsWith  ( s, "heLLO",              false , false );
        tEndsWith  ( s, "UTIL" ,              false , true  );
        tEndsWith  ( s, "utIl" ,              false , true  );

//
        // contains with empty/null strings
        s= "AB";
        tContainsAt( s, null,  -1 , false, false );
        tContainsAt( s, null,   0 , false, false );
        tContainsAt( s, null,   1 , false, false );
        tContainsAt( s, null,   2 , false, false );
        tContainsAt( s, null,   3 , false, false );
        tContainsAt( s, ""  ,  -1 , false, false );
        tContainsAt( s, ""  ,   0 , true,  true  );
        tContainsAt( s, ""  ,   1 , true,  true  );
        tContainsAt( s, ""  ,   2 , true,  true  );
        tContainsAt( s, ""  ,   3 , false, false );
        tContainsAt( s, ""  , 100 , false, false );

        // equals String
        tEquals(""  , null , false,   false );
        tEquals(""  , ""   , true,    true  );
        tEquals(""  , "a"  , false,   false );
        tEquals("AB", null , false,   false );
        tEquals("AB", ""   , false,   false );
        tEquals("AB", "ab" , false,   true  );
        tEquals("AB", "A"  , false,   false );
        tEquals("AB", "B"  , false,   false );
        tEquals("AB", "AB" , true,    true  );
    }



    //--------------------------------------------------------------------------------------------------
    //--- Test IndexOfChar
    //--------------------------------------------------------------------------------------------------
    Substring haystackSubsPlain = new Substring();
    void tIndexOfChar(String haystack, char needle, int startPos, int expectedResult )
    {
        haystackAString._()._( haystack );
        haystackSubsPlain.Set( haystack );
        haystackSubstring.Set( "01" + haystack + haystack + "234" , 2 + haystack.Length, haystack.Length );

        UT_EQ( expectedResult, haystackAString  .IndexOf( needle, startPos ) );
        UT_EQ( expectedResult, haystackSubsPlain.IndexOf( needle, startPos ) );
        UT_EQ( expectedResult, haystackSubstring.IndexOf( needle, startPos ) );
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
    public void IndexOfChar()
    {
        {
            tIndexOfChar( "ABCD",  'X',  0,     -1 );
            tIndexOfChar( "ABCD",  'A',  0,      0 );
            tIndexOfChar( "ABCD",  'B',  0,      1 );
            tIndexOfChar( "ABCD",  'C',  0,      2 );
            tIndexOfChar( "ABCD",  'D',  0,      3 );
        }

        // search characters
        {
            tIndexOfChar( "abcd abcd",  '@',   0   ,  -1 );
            tIndexOfChar( "abcd abcd",  '@',  -5   ,  -1 );
            tIndexOfChar( "abcd abcd",  '@',   5   ,  -1 );
            tIndexOfChar( "abcd abcd",  '@', 150   ,  -1 );
            tIndexOfChar( "abcd abcd",  'a',   0   ,   0 );
            tIndexOfChar( "abcd abcd",  'b',   0   ,   1 );
            tIndexOfChar( "abcd abcd",  'c',   0   ,   2 );
            tIndexOfChar( "abcd abcd",  'a',   0   ,   0 );
            tIndexOfChar( "abcd abcd",  'b',   0   ,   1 );
            tIndexOfChar( "abcd abcd",  'c',   0   ,   2 );
            tIndexOfChar( "abcd abcd",  'a',   1   ,   5 );
            tIndexOfChar( "abcd abcd",  'b',   1   ,   1 );
            tIndexOfChar( "abcd abcd",  'c',   1   ,   2 );
            tIndexOfChar( "abcd abcd",  'a',   2   ,   5 );
            tIndexOfChar( "abcd abcd",  'b',   2   ,   6 );
            tIndexOfChar( "abcd abcd",  'c',   2   ,   2 );
            tIndexOfChar( "abcd abcd",  'a',   3   ,   5 );
            tIndexOfChar( "abcd abcd",  'b',   3   ,   6 );
            tIndexOfChar( "abcd abcd",  'c',   3   ,   7 );
            tIndexOfChar( "abcd abcd",  'd',   7   ,   8 );
            tIndexOfChar( "abcd abcd",  'd',   8   ,   8 );
            tIndexOfChar( "abcd abcd",  'd',   9   ,  -1 );
        }


        // IndexOfFirstDifference
        {
            Substring substr= new Substring("abcdef");
            UT_EQ( 6, substr.IndexOfFirstDifference("abcdef") );
            UT_EQ( 5, substr.IndexOfFirstDifference("abcde") );
            UT_EQ( 6, substr.IndexOfFirstDifference("abcdefg") );

            UT_EQ( 0, substr.IndexOfFirstDifference("123") );
            UT_EQ( 0, substr.IndexOfFirstDifference("123", Case.Ignore   ) );
            UT_EQ( 0, substr.IndexOfFirstDifference("123", Case.Ignore, 2) );

            UT_EQ( 3, substr.IndexOfFirstDifference("abc") );
            UT_EQ( 3, substr.IndexOfFirstDifference("abc", Case.Ignore   ) );
            UT_EQ( 0, substr.IndexOfFirstDifference("abc", Case.Ignore, 1) );
            UT_EQ( 0, substr.IndexOfFirstDifference( "bc", Case.Ignore, 0) );
            UT_EQ( 2, substr.IndexOfFirstDifference( "bc", Case.Ignore, 1) );
            UT_EQ( 1, substr.IndexOfFirstDifference( "bd", Case.Ignore, 1) );


            UT_EQ( 3, substr.IndexOfFirstDifference("ABC", Case.Ignore   ) );
            UT_EQ( 0, substr.IndexOfFirstDifference("ABC", Case.Ignore, 1) );
            UT_EQ( 0, substr.IndexOfFirstDifference( "BC", Case.Ignore, 0) );
            UT_EQ( 2, substr.IndexOfFirstDifference( "BC", Case.Ignore, 1) );
            UT_EQ( 1, substr.IndexOfFirstDifference( "BD", Case.Ignore, 1) );


            UT_EQ( 0, substr.IndexOfFirstDifference("ABC") );
            UT_EQ( 0, substr.IndexOfFirstDifference("ABC", Case.Sensitive   ) );
            UT_EQ( 0, substr.IndexOfFirstDifference("ABC", Case.Sensitive, 1) );
            UT_EQ( 0, substr.IndexOfFirstDifference( "BC", Case.Sensitive, 0) );
            UT_EQ( 0, substr.IndexOfFirstDifference( "BC", Case.Sensitive, 1) );
            UT_EQ( 0, substr.IndexOfFirstDifference( "BD", Case.Sensitive, 1) );
        }

    }


    //--------------------------------------------------------------------------------------------------
    //--- Test IndexOfString
    //--------------------------------------------------------------------------------------------------
    void tIndexOfString(String haystack, String needle, int startPos, Case sensitivity, int expectedResult )
    {
        haystackAString._()._( haystack );
        haystackSubsPlain.Set( haystack );
        haystackSubstring.Set( "01" + haystack + haystack + "234" , 2 + haystack.Length, haystack.Length );

        if ( needle != null )
        {
            needleAString._()._( needle );
            needleSubstring.Set( "XY" + needle + "Z", 2, needle.Length );

            UT_EQ( expectedResult, haystackAString  .IndexOf( needle           , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.IndexOf( needle           , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.IndexOf( needle           , startPos, sensitivity ) );

            UT_EQ( expectedResult, haystackAString  .IndexOf( needleAString    , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.IndexOf( needleAString    , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.IndexOf( needleAString    , startPos, sensitivity ) );

            UT_EQ( expectedResult, haystackAString  .IndexOf( needleSubstring  , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.IndexOf( needleSubstring  , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.IndexOf( needleSubstring  , startPos, sensitivity ) );
        }
        else
        {
            UT_EQ( expectedResult, haystackAString  .IndexOf( needle           , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.IndexOf( needle           , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.IndexOf( needle           , startPos, sensitivity ) );

            UT_EQ( expectedResult, haystackAString  .IndexOf( (AString)   null , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.IndexOf( (AString)   null , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.IndexOf( (AString)   null , startPos, sensitivity ) );

            UT_EQ( expectedResult, haystackAString  .IndexOf( (Substring) null , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.IndexOf( (Substring) null , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.IndexOf( (Substring) null , startPos, sensitivity ) );
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
    public void IndexOfString()
    {
        // search null, empty string
        {
            tIndexOfString(  "abcd abcd",  null     ,     0  , Case.Sensitive,   0  );
            tIndexOfString(  "abcd abcd",  null     ,     5  , Case.Sensitive,   5  );
            tIndexOfString(  "abcd abcd",  null     ,    50  , Case.Sensitive,  -1  );
            tIndexOfString(  "abcd abcd",  null     ,    -5  , Case.Sensitive,   0  );
            tIndexOfString(  "abcd abcd",  ""       ,    -5  , Case.Sensitive,   0  );
            tIndexOfString(  "abcd abcd",  ""       ,     0  , Case.Sensitive,   0  );
            tIndexOfString(  "abcd abcd",  ""       ,     4  , Case.Sensitive,   4  );
            tIndexOfString(  "abcd abcd",  ""       ,   100  , Case.Sensitive,  -1  );

        }

        // normal
        {
            tIndexOfString(  "abcd abcd",  "abcd"   ,    0   , Case.Sensitive,    0 );
            tIndexOfString(  "abcd abcd",  "b"      ,    0   , Case.Sensitive,    1 );
            tIndexOfString(  "abcd abcd",  " abcd"  ,    0   , Case.Sensitive,    4 );
            tIndexOfString(  "abcd abcd",  "abcd"   ,    1   , Case.Sensitive,    5 );
            tIndexOfString(  "abcd abcd",  "abcd"   ,   -1   , Case.Sensitive,    0 );
            tIndexOfString(  "abcd abcd",  "xyz"    ,  -10   , Case.Sensitive,   -1 );
        }

        // ignore case
        {
            tIndexOfString(  "Hello A-Worx util", "a-worx",   0,  Case.Ignore,  6 );
            tIndexOfString(  "Hello A-Worx util", "a-worx",   1,  Case.Ignore,  6 );
            tIndexOfString(  "Hello A-Worx util", "a-worx", -10,  Case.Ignore,  6 );
            tIndexOfString(  "Hello A-Worx util", "a-worx",   6,  Case.Ignore,  6 );
            tIndexOfString(  "Hello A-Worx util", "a-worx",   7,  Case.Ignore, -1 );
            tIndexOfString(  "Hello A-Worx util", "a-worx", 100,  Case.Ignore, -1 );
            tIndexOfString(  "Hello A-Worx util", "hel"   ,   0,  Case.Ignore,  0 );
            tIndexOfString(  "Hello A-Worx util", "hel"   ,   1,  Case.Ignore, -1 );
            tIndexOfString(  "Hello A-Worx util", "util"  ,   1,  Case.Ignore, 13 );
            tIndexOfString(  "Hello A-Worx util", "UTIL"  ,   5,  Case.Ignore, 13 );
            tIndexOfString(  "Hello A-Worx util", "UTIL"  ,  13,  Case.Ignore, 13 );
            tIndexOfString(  "Hello A-Worx util", "UTIL"  ,  14,  Case.Ignore, -1 );
        }
    }

    //--------------------------------------------------------------------------------------------------
    //--- Test IndexOfAny
    //--------------------------------------------------------------------------------------------------
    int DEF=99999;
    void tIndexOfAny(bool forward, String haystack, String needles, int startPos, Inclusion inclusion, int expectedResult )
    {
        char[] needlesArr= needles.ToCharArray();

        haystackAString._()._( haystack );
        haystackSubsPlain.Set( haystack );
        haystackSubstring.Set( "01" + haystack + haystack + "234" , 2 + haystack.Length, haystack.Length );


        if ( startPos == DEF )
        {
            if ( forward )
            {
                UT_EQ( expectedResult, haystackAString  .IndexOfAny    ( needlesArr, inclusion            ) );
                UT_EQ( expectedResult, haystackSubsPlain.IndexOfAny    ( needlesArr, inclusion            ) );
                UT_EQ( expectedResult, haystackSubstring.IndexOfAny    ( needlesArr, inclusion            ) );
            }
            else
            {
                UT_EQ( expectedResult, haystackAString  .LastIndexOfAny( needlesArr, inclusion            ) );
                UT_EQ( expectedResult, haystackSubsPlain.LastIndexOfAny( needlesArr, inclusion            ) );
                UT_EQ( expectedResult, haystackSubstring.LastIndexOfAny( needlesArr, inclusion            ) );
            }
        }
        else
        {
            if ( forward )
            {
                UT_EQ( expectedResult, haystackAString  .IndexOfAny    ( needlesArr, inclusion , startPos ) );
                UT_EQ( expectedResult, haystackSubsPlain.IndexOfAny    ( needlesArr, inclusion , startPos ) );
                UT_EQ( expectedResult, haystackSubstring.IndexOfAny    ( needlesArr, inclusion , startPos ) );
            }
            else
            {
                UT_EQ( expectedResult, haystackAString  .LastIndexOfAny( needlesArr, inclusion , startPos ) );
                UT_EQ( expectedResult, haystackSubsPlain.LastIndexOfAny( needlesArr, inclusion , startPos ) );
                UT_EQ( expectedResult, haystackSubstring.LastIndexOfAny( needlesArr, inclusion , startPos ) );
            }
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
    public void IndexOfAny()
    {

        // ------------------ search one of several characters ------------------
        String s= "abcd abcde";
        int l= s.Length;
        {
            // search one of
            tIndexOfAny( true , s,  ""       , DEF ,Inclusion.Include,   -1  );
            tIndexOfAny( true , s,  "x"      , DEF ,Inclusion.Include,   -1  );
            tIndexOfAny( true , s,  "xy"     , DEF ,Inclusion.Include,   -1  );
            tIndexOfAny( true , s,  "xyz"    , DEF ,Inclusion.Include,   -1  );
            tIndexOfAny( true , s,  "xyd"    , DEF ,Inclusion.Include,    3  );
            tIndexOfAny( true , s,  "d"      , DEF ,Inclusion.Include,    3  );
            tIndexOfAny( true , s,  "xyd"    ,  -2 ,Inclusion.Include,    3  );
            tIndexOfAny( true , s,  "xyd"    ,   4 ,Inclusion.Include,    8  );
            tIndexOfAny( true , s,  "xyd"    ,  20 ,Inclusion.Include,   -1  );

            tIndexOfAny( false, s,  ""       , DEF ,Inclusion.Include,   -1  );
            tIndexOfAny( false, s,  "x"      , DEF ,Inclusion.Include,   -1  );
            tIndexOfAny( false, s,  "xy"     , DEF ,Inclusion.Include,   -1  );
            tIndexOfAny( false, s,  "xyz"    , DEF ,Inclusion.Include,   -1  );
            tIndexOfAny( false, s,  "xyd"    , DEF ,Inclusion.Include,    8  );
            tIndexOfAny( false, s,  "xyd"    ,  -2 ,Inclusion.Include,   -1  );
            tIndexOfAny( false, s,  "xyd"    ,   2 ,Inclusion.Include,   -1  );
            tIndexOfAny( false, s,  "xyd"    ,   4 ,Inclusion.Include,    3  );
            tIndexOfAny( false, s,  "a"      ,   4 ,Inclusion.Include,    0  );
            tIndexOfAny( false, s,  "b"      ,   4 ,Inclusion.Include,    1  );
            tIndexOfAny( false, s,  "ba"     ,   4 ,Inclusion.Include,    1  );
            tIndexOfAny( false, s,  "xa"     ,   4 ,Inclusion.Include,    0  );
            tIndexOfAny( false, s,  "xyd"    ,  20 ,Inclusion.Include,    8  );
            tIndexOfAny( false, s,  "d"      ,  20 ,Inclusion.Include,    8  );
            tIndexOfAny( false, s,  "e"      ,  20 ,Inclusion.Include,    9  );

            // exclude
            tIndexOfAny( true , s,  ""       , DEF ,Inclusion.Exclude,    0  );
            tIndexOfAny( true , s,  "x"      , DEF ,Inclusion.Exclude,    0  );
            tIndexOfAny( true , s,  "xy"     , DEF ,Inclusion.Exclude,    0  );
            tIndexOfAny( true , s,  "xyz"    , DEF ,Inclusion.Exclude,    0  );
            tIndexOfAny( true , s,  "a"      , DEF ,Inclusion.Exclude,    1  );
            tIndexOfAny( true , s,  "ba"     , DEF ,Inclusion.Exclude,    2  );
            tIndexOfAny( true , s,  "abc"    , DEF ,Inclusion.Exclude,    3  );
            tIndexOfAny( true , s,  "acb"    , DEF ,Inclusion.Exclude,    3  );
            tIndexOfAny( true , s,  "cba"    , DEF ,Inclusion.Exclude,    3  );
            tIndexOfAny( true , s,  "xcba"   , DEF ,Inclusion.Exclude,    3  );

            tIndexOfAny( false, s,  ""       , DEF ,Inclusion.Exclude,  l-1  );
            tIndexOfAny( false, s,  "x"      , DEF ,Inclusion.Exclude,  l-1  );
            tIndexOfAny( false, s,  "xy"     , DEF ,Inclusion.Exclude,  l-1  );
            tIndexOfAny( false, s,  "e"      , DEF ,Inclusion.Exclude,  l-2  );
            tIndexOfAny( false, s,  "de"     , DEF ,Inclusion.Exclude,  l-3  );
            tIndexOfAny( false, s,  "cde"    , DEF ,Inclusion.Exclude,  l-4  );
            tIndexOfAny( false, s,  "ced"    , DEF ,Inclusion.Exclude,  l-4  );
            tIndexOfAny( false, s,  "ecd"    , DEF ,Inclusion.Exclude,  l-4  );
            tIndexOfAny( false, s,  "ecd"    ,   5 ,Inclusion.Exclude,    5  );
            tIndexOfAny( false, s,  "ecd"    ,   4 ,Inclusion.Exclude,    4  );
            tIndexOfAny( false, s,  "acd"    ,   3 ,Inclusion.Exclude,    1  );
            tIndexOfAny( false, s,  "abc"    ,   2 ,Inclusion.Exclude,   -1  );
            tIndexOfAny( false, s,  "xay"    ,   3 ,Inclusion.Exclude,    3  );
            tIndexOfAny( false, s,  "d"      ,   3 ,Inclusion.Exclude,    2  );
            tIndexOfAny( false, s,  "a"      ,   0 ,Inclusion.Exclude,   -1  );
        }

    }


}
}
