// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_com_alib;
import org.junit.Test;

import ut_com_aworx_uttools.UnitTest;

import com.aworx.lib.enums.Case;
import com.aworx.lib.enums.Inclusion;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lib.strings.Substring;


public class UT_alib_strings_AStringAndSubstring extends UnitTest
{
    AString     haystackAString  = new AString();
    Substring   haystackSubstring= new Substring();
    AString     needleAString    = new AString();
    Substring   needleSubstring  = new Substring();

    //---------------------------------------------------------------------------------------------------------
    //--- Test Compare
    //---------------------------------------------------------------------------------------------------------
    void tStartsWith( String haystack, String needle, boolean expectedSensitive  , boolean expectedIgnoreCase )
    {
        haystackAString._()._( haystack );
        haystackSubstring.set( "01" + haystack + "234" , 2, haystack.length() );


        if ( needle != null)
        {
            UT_EQ( expectedSensitive  , haystackAString  .startsWith( needle                ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .startsWith( needle                ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.startsWith( needle                ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.startsWith( needle                ,Case.IGNORE    ) );
            needleAString._()._( needle );
            UT_EQ( expectedSensitive  , haystackAString  .startsWith( needleAString         ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .startsWith( needleAString         ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.startsWith( needleAString         ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.startsWith( needleAString         ,Case.IGNORE    ) );

            needleSubstring.set( "XY" + needle + "Z", 2, needle.length() );
            UT_EQ( expectedSensitive  , haystackAString  .startsWith( needleSubstring       ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .startsWith( needleSubstring       ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.startsWith( needleSubstring       ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.startsWith( needleSubstring       ,Case.IGNORE    ) );


            UT_TRUE( CString.startsWithIgnoreCase( haystackAString, needle      ) == expectedIgnoreCase  );
            UT_TRUE( CString.startsWithIgnoreCase( haystackSubstring  , needle      ) == expectedIgnoreCase  );

        }
        else
        {
            UT_EQ( expectedSensitive  , haystackAString  .startsWith( needle                ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .startsWith( needle                ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackAString  .startsWith((AString) null         ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .startsWith((AString) null         ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackAString  .startsWith((Substring) null       ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .startsWith((Substring) null       ,Case.IGNORE    ) );

            UT_EQ( expectedSensitive  , haystackSubstring.startsWith( needle                ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.startsWith( needle                ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.startsWith((AString) null         ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.startsWith((AString) null         ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.startsWith((Substring) null       ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.startsWith((Substring) null       ,Case.IGNORE    ) );
        }
    }

    void tEndsWith( String haystack, String needle, boolean expectedSensitive  , boolean expectedIgnoreCase )
    {
        haystackAString._()._( haystack );
        haystackSubstring.set( "01" + haystack + "234" , 2, haystack.length() );

        if ( needle != null)
        {
            UT_EQ( expectedSensitive  , haystackAString  .endsWith( needle                  ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .endsWith( needle                  ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.endsWith( needle                  ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.endsWith( needle                  ,Case.IGNORE    ) );
            needleAString._()._( needle );
            UT_EQ( expectedSensitive  , haystackAString  .endsWith( needleAString           ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .endsWith( needleAString           ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.endsWith( needleAString           ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.endsWith( needleAString           ,Case.IGNORE    ) );
            needleSubstring.set( "XY" + needle + "Z", 2, needle.length() );
            UT_EQ( expectedSensitive  , haystackAString  .endsWith( needleSubstring         ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .endsWith( needleSubstring         ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.endsWith( needleSubstring         ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.endsWith( needleSubstring         ,Case.IGNORE    ) );

            UT_TRUE( CString.endsWithIgnoreCase( haystackAString, needle      ) == expectedIgnoreCase  );
            UT_TRUE( CString.endsWithIgnoreCase( haystackSubstring  , needle      ) == expectedIgnoreCase  );
        }
        else
        {
            UT_EQ( expectedSensitive  , haystackAString  .endsWith( needle                  ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .endsWith( needle                  ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackAString  .endsWith((AString) null           ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .endsWith((AString) null           ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackAString  .endsWith((Substring) null         ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .endsWith((Substring) null         ,Case.IGNORE    ) );

            UT_EQ( expectedSensitive  , haystackSubstring.endsWith( needle                  ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.endsWith( needle                  ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.endsWith((AString) null           ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.endsWith((AString) null           ,Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.endsWith((Substring) null         ,Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.endsWith((Substring) null         ,Case.IGNORE    ) );
        }
    }

    void tEquals( String haystack, String needle, boolean expectedSensitive  , boolean expectedIgnoreCase )
    {
        haystackAString._()._( haystack );
        haystackSubstring.set( "01" + haystack + "234" , 2, haystack.length() );

        if ( needle != null)
        {
            UT_EQ( expectedSensitive  , haystackAString  .equals( needle                    , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .equals( needle                    , Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.equals( needle                    , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.equals( needle                    , Case.IGNORE    ) );
            needleAString._()._( needle );
            UT_EQ( expectedSensitive  , haystackAString  .equals( needleAString             , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .equals( needleAString             , Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.equals( needleAString             , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.equals( needleAString             , Case.IGNORE    ) );

            needleSubstring.set( "XY" + needle + "Z", 2, needle.length() );
            UT_EQ( expectedSensitive  , haystackAString  .equals( needleSubstring           , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .equals( needleSubstring           , Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.equals( needleSubstring           , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.equals( needleSubstring           , Case.IGNORE    ) );
        }
        else
        {
            UT_EQ( expectedSensitive  , haystackAString  .equals(  needle                   , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .equals(  needle                   , Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackAString  .equals( (AString) null            , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .equals( (AString) null            , Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackAString  .equals( (Substring) null          , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .equals( (Substring) null          , Case.IGNORE    ) );

            UT_EQ( expectedSensitive  , haystackSubstring.equals(  needle                   , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.equals(  needle                   , Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.equals( (AString) null            , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.equals( (AString) null            , Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.equals( (Substring) null          , Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.equals( (Substring) null          , Case.IGNORE    ) );
        }
    }


    void tContainsAt( String haystack, String needle, int pos, boolean expectedSensitive  , boolean expectedIgnoreCase )
    {
        haystackAString._()._( haystack );
        haystackSubstring.set( "01" + haystack + "234" , 2, haystack.length() );

        if ( needle != null)
        {
            UT_EQ( expectedSensitive  , haystackAString  .containsAt( needle                , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .containsAt( needle                , pos, Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.containsAt( needle                , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.containsAt( needle                , pos, Case.IGNORE    ) );
            needleAString._()._( needle );
            UT_EQ( expectedSensitive  , haystackAString  .containsAt( needleAString         , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .containsAt( needleAString         , pos, Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.containsAt( needleAString         , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.containsAt( needleAString         , pos, Case.IGNORE    ) );

            needleSubstring.set( "XY" + needle + "Z", 2, needle.length() );
            UT_EQ( expectedSensitive  , haystackAString  .containsAt( needleSubstring       , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .containsAt( needleSubstring       , pos, Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.containsAt( needleSubstring       , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.containsAt( needleSubstring       , pos, Case.IGNORE    ) );
        }
        else
        {
            UT_EQ( expectedSensitive  , haystackAString  .containsAt(  needle               , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .containsAt(  needle               , pos, Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackAString  .containsAt( (AString) null        , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .containsAt( (AString) null        , pos, Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackAString  .containsAt( (Substring) null      , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackAString  .containsAt( (Substring) null      , pos, Case.IGNORE    ) );

            UT_EQ( expectedSensitive  , haystackSubstring.containsAt(  needle               , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.containsAt(  needle               , pos, Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.containsAt( (AString) null        , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.containsAt( (AString) null        , pos, Case.IGNORE    ) );
            UT_EQ( expectedSensitive  , haystackSubstring.containsAt( (Substring) null      , pos, Case.SENSITIVE ) );
            UT_EQ( expectedIgnoreCase , haystackSubstring.containsAt( (Substring) null      , pos, Case.IGNORE    ) );
        }
    }

    @SuppressWarnings("static-method")
    @Test
    public void Compare()
    {
        // startsWith/EndswequalsnsAt
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


    //---------------------------------------------------------------------------------------------------------
    //--- Test IndexOfChar
    //---------------------------------------------------------------------------------------------------------
    Substring haystackSubsPlain = new Substring();
    void tIndexOfChar(String haystack, char needle, int startPos, int expectedResult )
    {
        haystackAString._()._( haystack );
        haystackSubsPlain.set( haystack );
        haystackSubstring.set( "01" + haystack + haystack + "234" , 2 + haystack.length(), haystack.length() );

        UT_EQ( expectedResult, haystackAString  .indexOf( needle, startPos ) );
        UT_EQ( expectedResult, haystackSubsPlain.indexOf( needle, startPos ) );
        UT_EQ( expectedResult, haystackSubstring.indexOf( needle, startPos ) );
    }

    @SuppressWarnings("static-method")
    @Test
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
    }


    //---------------------------------------------------------------------------------------------------------
    //--- Test IndexOfString
    //---------------------------------------------------------------------------------------------------------
    void tIndexOfString(String haystack, String needle, int startPos, Case sensitivity, int expectedResult )
    {
        haystackAString._()._( haystack );
        haystackSubsPlain.set( haystack );
        haystackSubstring.set( "01" + haystack + haystack + "234" , 2 + haystack.length(), haystack.length() );

        if ( needle != null )
        {
            needleAString._()._( needle );
            needleSubstring.set( "XY" + needle + "Z", 2, needle.length() );

            UT_EQ( expectedResult, haystackAString  .indexOf( needle           , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.indexOf( needle           , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.indexOf( needle           , startPos, sensitivity ) );

            UT_EQ( expectedResult, haystackAString  .indexOf( needleAString    , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.indexOf( needleAString    , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.indexOf( needleAString    , startPos, sensitivity ) );

            UT_EQ( expectedResult, haystackAString  .indexOf( needleSubstring  , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.indexOf( needleSubstring  , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.indexOf( needleSubstring  , startPos, sensitivity ) );
        }
        else
        {
            UT_EQ( expectedResult, haystackAString  .indexOf( needle           , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.indexOf( needle           , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.indexOf( needle           , startPos, sensitivity ) );

            UT_EQ( expectedResult, haystackAString  .indexOf( (AString)   null , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.indexOf( (AString)   null , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.indexOf( (AString)   null , startPos, sensitivity ) );

            UT_EQ( expectedResult, haystackAString  .indexOf( (Substring) null , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubsPlain.indexOf( (Substring) null , startPos, sensitivity ) );
            UT_EQ( expectedResult, haystackSubstring.indexOf( (Substring) null , startPos, sensitivity ) );
        }

        if ( sensitivity == Case.IGNORE )
            UT_EQ( expectedResult, CString.indexOfIgnoreCase( haystack, needle, startPos ) );
    }

    @SuppressWarnings("static-method")
    @Test
    public void IndexOfString()
    {
        // search nullptr, empty string
        {
            tIndexOfString(  "abcd abcd",  null     ,     0  , Case.SENSITIVE,   0  );
            tIndexOfString(  "abcd abcd",  null     ,     5  , Case.SENSITIVE,   5  );
            tIndexOfString(  "abcd abcd",  null     ,    50  , Case.SENSITIVE,  -1  );
            tIndexOfString(  "abcd abcd",  null     ,    -5  , Case.SENSITIVE,   0  );
            tIndexOfString(  "abcd abcd",  ""       ,    -5  , Case.SENSITIVE,   0  );
            tIndexOfString(  "abcd abcd",  ""       ,     0  , Case.SENSITIVE,   0  );
            tIndexOfString(  "abcd abcd",  ""       ,     4  , Case.SENSITIVE,   4  );
            tIndexOfString(  "abcd abcd",  ""       ,   100  , Case.SENSITIVE,  -1  );

        }

        // normal
        {
            tIndexOfString(  "abcd abcd",  "abcd"   ,    0   , Case.SENSITIVE,    0 );
            tIndexOfString(  "abcd abcd",  "b"      ,    0   , Case.SENSITIVE,    1 );
            tIndexOfString(  "abcd abcd",  " abcd"  ,    0   , Case.SENSITIVE,    4 );
            tIndexOfString(  "abcd abcd",  "abcd"   ,    1   , Case.SENSITIVE,    5 );
            tIndexOfString(  "abcd abcd",  "abcd"   ,   -1   , Case.SENSITIVE,    0 );
            tIndexOfString(  "abcd abcd",  "xyz"    ,  -10   , Case.SENSITIVE,   -1 );
        }

        // ignore case
        {
            tIndexOfString(  "Hallo A-Worx util", "a-worx",   0,  Case.IGNORE,  6 );
            tIndexOfString(  "Hallo A-Worx util", "a-worx",   1,  Case.IGNORE,  6 );
            tIndexOfString(  "Hallo A-Worx util", "a-worx", -10,  Case.IGNORE,  6 );
            tIndexOfString(  "Hallo A-Worx util", "a-worx",   6,  Case.IGNORE,  6 );
            tIndexOfString(  "Hallo A-Worx util", "a-worx",   7,  Case.IGNORE, -1 );
            tIndexOfString(  "Hallo A-Worx util", "a-worx", 100,  Case.IGNORE, -1 );
            tIndexOfString(  "Hallo A-Worx util", "hal"   ,   0,  Case.IGNORE,  0 );
            tIndexOfString(  "Hallo A-Worx util", "hal"   ,   1,  Case.IGNORE, -1 );
            tIndexOfString(  "Hallo A-Worx util", "util"  ,   1,  Case.IGNORE, 13 );
            tIndexOfString(  "Hallo A-Worx util", "UTIL"  ,   5,  Case.IGNORE, 13 );
            tIndexOfString(  "Hallo A-Worx util", "UTIL"  ,  13,  Case.IGNORE, 13 );
            tIndexOfString(  "Hallo A-Worx util", "UTIL"  ,  14,  Case.IGNORE, -1 );
        }
    }

    //---------------------------------------------------------------------------------------------------------
    //--- Test IndexOfAny
    //---------------------------------------------------------------------------------------------------------
    int DEF=99999;
    void tIndexOfAny(boolean forward, String haystack, String needles, int startPos, Inclusion inclusion, int expectedResult )
    {
        char[] needlesArr= needles.toCharArray();

        haystackAString._()._( haystack );
        haystackSubsPlain.set( haystack );
        haystackSubstring.set( "01" + haystack + haystack + "234" , 2 + haystack.length(), haystack.length() );


        if ( startPos == DEF )
        {
            if ( forward )
            {
                UT_EQ( expectedResult, haystackAString  .indexOfAny        ( needlesArr, inclusion            ) );
                UT_EQ( expectedResult, haystackSubsPlain.indexOfAny        ( needlesArr, inclusion            ) );
                UT_EQ( expectedResult, haystackSubstring.indexOfAny        ( needlesArr, inclusion            ) );
            }
            else
            {
                UT_EQ( expectedResult, haystackAString  .lastIndexOfAny( needlesArr, inclusion            ) );
                UT_EQ( expectedResult, haystackSubsPlain.lastIndexOfAny( needlesArr, inclusion            ) );
                UT_EQ( expectedResult, haystackSubstring.lastIndexOfAny( needlesArr, inclusion            ) );
            }
        }
        else
        {
            if ( forward )
            {
                UT_EQ( expectedResult, haystackAString  .indexOfAny        ( needlesArr, inclusion , startPos ) );
                UT_EQ( expectedResult, haystackSubsPlain.indexOfAny        ( needlesArr, inclusion , startPos ) );
                UT_EQ( expectedResult, haystackSubstring.indexOfAny        ( needlesArr, inclusion , startPos ) );
            }
            else
            {
                UT_EQ( expectedResult, haystackAString  .lastIndexOfAny( needlesArr, inclusion , startPos ) );
                UT_EQ( expectedResult, haystackSubsPlain.lastIndexOfAny( needlesArr, inclusion , startPos ) );
                UT_EQ( expectedResult, haystackSubstring.lastIndexOfAny( needlesArr, inclusion , startPos ) );
            }
        }
    }

    @SuppressWarnings("static-method")
    @Test
    public void IndexOfAny()
    {

        // ------------------ search one of several characters ------------------
        String s= "abcd abcde";
        int l= s.length();
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
