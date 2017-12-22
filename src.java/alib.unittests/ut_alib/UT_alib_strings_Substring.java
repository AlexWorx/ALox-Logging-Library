// #################################################################################################
//  Unit Tests - AWorx Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package ut_alib;
import org.junit.Test;

import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.NumberFormat;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.util.Tokenizer;

import ut_com_aworx.AWorxUnitTesting;
import ut_com_aworx.UTSampleWriter;


public class UT_alib_strings_Substring extends AWorxUnitTesting
{
//##################################################################################################
// SAMPLE code of class documentation
//##################################################################################################

static
void documentationSampleTokenizer()
{
    UTSampleWriter utsw= new UTSampleWriter("DOC_SAMPLES_ALIB_LIB_STRING_TOKEN.txt");

//! [DOC_SAMPLES_ALIB_LIB_STRING_TOKEN]
    // data string to tokenize
    AString data= new AString( "test;  abc ; 1,2 , 3 ; xyz ; including;separator" );

    // create tokenizer on data with ';' as delimiter
    Tokenizer tknzr= new Tokenizer( data, ';' );

    // read tokens
    System.out.println( tknzr.next().toString() ); // will print "test"
    System.out.println( tknzr.next().toString() ); // will print "abc"
    System.out.println( tknzr.next().toString() ); // will print "1,2 , 3"

    // tokenize actual (third) token (nested tokenizer)
    Tokenizer subTknzr= new Tokenizer( tknzr.actual,  ',');
    System.out.print( subTknzr.next().toString() );

    while( subTknzr.hasNext() )
        System.out.print( "~" + subTknzr.next().toString() );

    System.out.println();

    // continue with the main tokenizer
    System.out.println( tknzr.next().toString() ); // will print "xyz"

    // grab the rest, as we know that the last token might include our separator character
    System.out.println( tknzr.getRest().toString() ); // will print "including;separator"
//! [DOC_SAMPLES_ALIB_LIB_STRING_TOKEN]

    utsw.flushAndResetSystemOut();
}


@Test
public void DocumentationSamples()
{
    UT_INIT();

    //UT_PRINT("*** Documentation Sample +**")
    documentationSampleTokenizer();
}


//--------------------------------------------------------------------------------------------------
//--- Test Constructor
//--------------------------------------------------------------------------------------------------
static void constructorTest( String inputString, AString result, boolean trim )
{
    Substring tok= new Substring( inputString );
    if ( trim )
        tok.trim();
    tok.copyTo( result );
}

@SuppressWarnings("static-method")
@Test
public void SubstringConstructor()
{
    UT_INIT();

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
            astr.clear()._( "xy xz abc xy" );
            Substring subs= new Substring();
            subs.set(astr).trim("xy ".toCharArray()).copyTo( res );
            UT_EQ( "z abc",      res );
        }

        {
            Substring subs= new Substring( "xy xz abc xy" );
            subs.trimStart("xy ".toCharArray()).trimEnd("xy ".toCharArray()).copyTo( res );
            UT_EQ( "z abc",      res );
        }
    }

    // test other constructors
    {
        astr.clear()._( " astring ");
        UT_TRUE  ( (new Substring()).isEmpty() );
        UT_TRUE  ( (new Substring()).isNull() );
        UT_EQ( "astring",  (new Substring( astr )).trim() .toString() );
        UT_EQ( "str",      (new Substring( astr,  2, 3 )) .toString() );
        UT_EQ( "",         (new Substring( astr, 20, 3 )) .toString() );
        UT_TRUE  (         (new Substring( astr, 20, 3 )).isEmpty()  );
        UT_FALSE (         (new Substring( astr, 20, 3 )).isNull()   );

        UT_EQ( "astring",  (new Substring( (new Substring( astr )).trim())) .toString() );
        UT_EQ( "str",      (new Substring( (new Substring( astr, 2,3   )))) .toString() );
    }

}


//--------------------------------------------------------------------------------------------------
//--- Test FrontEnd
//--------------------------------------------------------------------------------------------------
@SuppressWarnings("static-method")
@Test
public void FrontEnd()
{
    UT_INIT();

    // null substring
    {
        Substring subs= new Substring();
        UT_EQ(  '\0',      subs.charAtStart() );
        UT_EQ(  '\0',      subs.charAt( 0 ) );
        UT_EQ(  '\0',      subs.charAt( 1 ) );
        UT_EQ(  '\0',      subs.charAt(-1 ) );
        UT_EQ(  '\0',      subs.charAt( 2 ) );
        UT_EQ(  '\0',      subs.charAt(-2 ) );

        UT_EQ(  '\0',      subs.charAtEnd (   ) );
        UT_EQ(  '\0',      subs.charAtEnd ( 0 ) );
        UT_EQ(  '\0',      subs.charAtEnd ( 1 ) );
        UT_EQ(  '\0',      subs.charAtEnd (-1 ) );
        UT_EQ(  '\0',      subs.charAtEnd ( 2 ) );
        UT_EQ(  '\0',      subs.charAtEnd (-2 ) );
    }

    // empty substring
    {
        Substring subs= new Substring("aaaaaaaaaaaa");
        subs.start= 5;
        subs.end=   4;
        UT_EQ(  '\0',      subs.charAtStart() );
        UT_EQ(  '\0',      subs.charAt( 0 ) );
        UT_EQ(  '\0',      subs.charAt( 1 ) );
        UT_EQ(  '\0',      subs.charAt(-1 ) );
        UT_EQ(  '\0',      subs.charAt( 2 ) );
        UT_EQ(  '\0',      subs.charAt(-2 ) );

        UT_EQ(  '\0',      subs.charAtEnd (   ) );
        UT_EQ(  '\0',      subs.charAtEnd ( 0 ) );
        UT_EQ(  '\0',      subs.charAtEnd ( 1 ) );
        UT_EQ(  '\0',      subs.charAtEnd (-1 ) );
        UT_EQ(  '\0',      subs.charAtEnd ( 2 ) );
        UT_EQ(  '\0',      subs.charAtEnd (-2 ) );
    }

    // substring of length 1
    {
        Substring subs= new Substring("aaaaaaaaaaaa");
        subs.start= subs.end= 5;
        UT_EQ( 'a',      subs.charAtStart() );
        UT_EQ( 'a',      subs.charAt( 0 ) );
        UT_EQ( '\0',     subs.charAt( 1 ) );
        UT_EQ( '\0',     subs.charAt(-1 ) );
        UT_EQ( '\0',     subs.charAt( 2 ) );
        UT_EQ( '\0',     subs.charAt(-2 ) );

        UT_EQ( 'a',      subs.charAtEnd (   ) );
        UT_EQ( 'a',      subs.charAtEnd ( 0 ) );
        UT_EQ( '\0',     subs.charAtEnd ( 1 ) );
        UT_EQ( '\0',     subs.charAtEnd (-1 ) );
        UT_EQ( '\0',     subs.charAtEnd ( 2 ) );
        UT_EQ( '\0',     subs.charAtEnd (-2 ) );
    }

    // substring of length 2
    {
        Substring subs= new Substring("aaaaabbbbbb");
        subs.end= subs.indexOf('b');
        subs.start= subs.end - 1;
        UT_EQ( 'a',      subs.charAtStart() );
        UT_EQ( 'a',      subs.charAt( 0 ) );
        UT_EQ( 'b',      subs.charAt( 1 ) );
        UT_EQ( '\0',     subs.charAt(-1 ) );
        UT_EQ( '\0',     subs.charAt( 2 ) );
        UT_EQ( '\0',     subs.charAt(-2 ) );

        UT_EQ( 'b',      subs.charAtEnd (   ) );
        UT_EQ( 'b',      subs.charAtEnd ( 0 ) );
        UT_EQ( 'a',      subs.charAtEnd ( 1 ) );
        UT_EQ( '\0',     subs.charAtEnd (-1 ) );
        UT_EQ( '\0',     subs.charAtEnd ( 2 ) );
        UT_EQ( '\0',     subs.charAtEnd (-2 ) );
    }
}


//--------------------------------------------------------------------------------------------------
//--- Test Consume
//--------------------------------------------------------------------------------------------------
@SuppressWarnings("static-method")
@Test
public void Consume()
{
    UT_INIT();

    // null substring
    {
        Substring s= new Substring();
        Substring r= new Substring("oldval");

        UT_EQ(  '\0',      s.consumeChar( )         );
        UT_EQ(  0,         s.consumeChars(  0 ,   r) ); UT_TRUE(r.isNull());
        UT_EQ(  0,         s.consumeChars(  5 ,   r) ); UT_TRUE(r.isNull());
        UT_EQ(  false,     s.consumeChar( 'a' )     );
        UT_EQ(  false,     s.consumeString( "word" )  );
        UT_EQ(  '\0',      s.consumeCharFromEnd( )         );
        UT_EQ(  0,         s.consumeCharFromEnd(  0  )     );
        UT_EQ(  0,         s.consumeCharFromEnd(  5  )     );
        UT_EQ(  false,     s.consumeCharFromEnd( 'a' )     );
        UT_EQ(  false,     s.consumeStringFromEnd( "word" )  );
    }

    // empty substring
    {
        Substring s= new Substring("aaaaaaaaaaaa");
        Substring r= new Substring("oldval");
        s.start= 5;
        s.end=   4;
        UT_EQ(  '\0',      s.consumeChar( )         );
        UT_EQ(  0,         s.consumeChars(  0   , r) ); UT_TRUE( r.isNotNull()); UT_TRUE(r.isEmpty());
        UT_EQ(  0,         s.consumeChars(  5   , r) ); UT_TRUE( r.isNotNull()); UT_TRUE(r.isEmpty());
        UT_EQ(  false,     s.consumeChar( 'a' )     );
        UT_EQ(  false,     s.consumeString( "word" )  );
        UT_EQ(  '\0',      s.consumeCharFromEnd( )         );
        UT_EQ(  0,         s.consumeCharFromEnd(  0  )     );
        UT_EQ(  0,         s.consumeCharFromEnd(  5  )     );
        UT_EQ(  false,     s.consumeCharFromEnd( 'a' )     );
        UT_EQ(  false,     s.consumeStringFromEnd( "word" )  );
    }

    // substring of length 1
    {
        Substring s= new Substring("aaaaaaaaaaaa");
        Substring r= new Substring("oldval");

        s.start= s.end= 5; UT_EQ(  'a',       s.consumeChar( )         ); UT_EQ( 0, s.length() );
        s.start= s.end= 5; UT_EQ(  1,         s.consumeChars(  0  )     ); UT_EQ( 1, s.length() );
        s.start= s.end= 5; UT_EQ(  0,         s.consumeChars(  1  , r)  ); UT_EQ( 0, s.length() );  UT_TRUE(r.equals("a"));
        s.start= s.end= 5; UT_EQ(  0,         s.consumeChars(  5  , r)  ); UT_EQ( 0, s.length() );  UT_TRUE(r.equals("a"));
        s.start= s.end= 5; UT_EQ(  true,      s.consumeChar( 'a' )     ); UT_EQ( 0, s.length() );
        s.start= s.end= 5; UT_EQ(  false,     s.consumeChar( 'b' )     ); UT_EQ( 1, s.length() );
        s.start= s.end= 5; UT_EQ(  false,     s.consumeString( "word" )  ); UT_EQ( 1, s.length() );
        s.start= s.end= 5; UT_EQ(  'a',       s.consumeCharFromEnd( )         ); UT_EQ( 0, s.length() );
        s.start= s.end= 5; UT_EQ(  1,         s.consumeCharFromEnd(  0  )     ); UT_EQ( 1, s.length() );
        s.start= s.end= 5; UT_EQ(  0,         s.consumeCharFromEnd(  1  )     ); UT_EQ( 0, s.length() );
        s.start= s.end= 5; UT_EQ(  0,         s.consumeCharFromEnd(  5  )     ); UT_EQ( 0, s.length() );
        s.start= s.end= 5; UT_EQ(  true,      s.consumeCharFromEnd( 'a' )     ); UT_EQ( 0, s.length() );
        s.start= s.end= 5; UT_EQ(  false,     s.consumeCharFromEnd( 'b' )     ); UT_EQ( 1, s.length() );
        s.start= s.end= 5; UT_EQ(  false,     s.consumeStringFromEnd( "word" )  ); UT_EQ( 1, s.length() );
    }

    // substring of length 2
    {
        Substring s= new Substring("12ab3456");
        Substring r= new Substring("oldval");

        s.start= 2; s.end= 3; UT_EQ(  'a',       s.consumeChar( )         ); UT_EQ( 1, s.length() );
                              UT_EQ(  'b',       s.consumeChar( )         ); UT_EQ( 0, s.length() );
        s.start= 2; s.end= 3; UT_EQ(  'b',       s.consumeCharFromEnd( )         ); UT_EQ( 1, s.length() );
                              UT_EQ(  'a',       s.consumeCharFromEnd( )         ); UT_EQ( 0, s.length() );

        s.start= 2; s.end= 3; UT_EQ(  2,         s.consumeChars(  0   , r) ); UT_EQ( 2, s.length() ); UT_TRUE(r.isNotNull()); UT_TRUE(r.isEmpty());
        s.start= 2; s.end= 3; UT_EQ(  1,         s.consumeChars(  1   , r) ); UT_EQ( 1, s.length() ); UT_TRUE(r.equals("a"));
        s.start= 2; s.end= 3; UT_EQ(  0,         s.consumeChars(  2   , r) ); UT_EQ( 0, s.length() ); UT_TRUE(r.equals("ab"));
        s.start= 2; s.end= 3; UT_EQ(  0,         s.consumeChars(  3   , r) ); UT_EQ( 0, s.length() ); UT_TRUE(r.equals("ab"));
        s.start= 2; s.end= 3; UT_EQ(  2,         s.consumeCharFromEnd(  0   , r) ); UT_EQ( 2, s.length() ); UT_TRUE(r.isNotNull()); UT_TRUE(r.isEmpty());
        s.start= 2; s.end= 3; UT_EQ(  1,         s.consumeCharFromEnd(  1   , r) ); UT_EQ( 1, s.length() ); UT_TRUE(r.equals("b"));
        s.start= 2; s.end= 3; UT_EQ(  0,         s.consumeCharFromEnd(  2   , r) ); UT_EQ( 0, s.length() ); UT_TRUE(r.equals("ab"));
        s.start= 2; s.end= 3; UT_EQ(  0,         s.consumeCharFromEnd(  3   , r) ); UT_EQ( 0, s.length() ); UT_TRUE(r.equals("ab"));

        s.start= 2; s.end= 3; UT_EQ(  false,     s.consumeChar( 'b' )     ); UT_EQ( 2, s.length() );
                              UT_EQ(  true,      s.consumeChar( 'a' )     ); UT_EQ( 1, s.length() );
                              UT_EQ(  true,      s.consumeChar( 'b' )     ); UT_EQ( 0, s.length() );
                              UT_EQ(  false,     s.consumeChar( 'a' )     ); UT_EQ( 0, s.length() );
                              UT_EQ(  false,     s.consumeChar( 'b' )     ); UT_EQ( 0, s.length() );
        s.start= 2; s.end= 3; UT_EQ(  false,     s.consumeCharFromEnd( 'a' )     ); UT_EQ( 2, s.length() );
                              UT_EQ(  true,      s.consumeCharFromEnd( 'b' )     ); UT_EQ( 1, s.length() );
                              UT_EQ(  true,      s.consumeCharFromEnd( 'a' )     ); UT_EQ( 0, s.length() );
                              UT_EQ(  false,     s.consumeCharFromEnd( 'b' )     ); UT_EQ( 0, s.length() );
                              UT_EQ(  false,     s.consumeCharFromEnd( 'a' )     ); UT_EQ( 0, s.length() );

        s.start= 2; s.end= 3; UT_EQ(  false,     s.consumeString( "word" )  ); UT_EQ( 2, s.length() );
        s.start= 2; s.end= 3; UT_EQ(  false,     s.consumeString( "AB"   )  ); UT_EQ( 2, s.length() );
        s.start= 2; s.end= 3; UT_EQ(  true,      s.consumeString( "ab"   )  ); UT_EQ( 0, s.length() );
        s.start= 2; s.end= 3; UT_EQ(  false,     s.consumeStringFromEnd( "word" )  ); UT_EQ( 2, s.length() );
        s.start= 2; s.end= 3; UT_EQ(  false,     s.consumeStringFromEnd( "AB"   )  ); UT_EQ( 2, s.length() );
        s.start= 2; s.end= 3; UT_EQ(  true,      s.consumeStringFromEnd( "ab"   )  ); UT_EQ( 0, s.length() );
    }

    // 3 words
    {
        Substring s= new Substring("word1 word2 word3");

        UT_EQ(  'w',       s.consumeChar( )         );
        UT_EQ(  'o',       s.consumeChar( )         );
        UT_EQ(  'r',       s.consumeChar( )         );
        UT_EQ(  'd',       s.consumeChar( )         );
        UT_EQ(  '1',       s.consumeChar( )         );

        UT_EQ(  false    , s.consumeChar('w'                        )   );
        UT_EQ(  true     , s.consumeChar('w'     , Case.SENSITIVE, Whitespaces.TRIM )   );
        UT_EQ(  true     , s.consumeChar('o'     , Case.SENSITIVE, Whitespaces.TRIM )   );
        UT_EQ(  false    , s.consumeChar('o'     , Case.SENSITIVE, Whitespaces.TRIM )   );
        UT_EQ(  true     , s.consumeChar('r'     , Case.SENSITIVE, Whitespaces.TRIM )   );
        UT_EQ(  false    , s.consumeString("D2"    , Case.SENSITIVE, Whitespaces.TRIM )   );
        UT_EQ(  false    , s.consumeString("D2"                       )   );
        UT_EQ(  true     , s.consumeString("d2"                       )   );

        UT_EQ(  2        , s.consumeChars( 4 )   );
        UT_EQ(  "d3"     , s.toString() );

                  s= new Substring("word1 word2 word3");

        UT_EQ(  '3',       s.consumeCharFromEnd( )         );
        UT_EQ(  'd',       s.consumeCharFromEnd( )         );
        UT_EQ(  'r',       s.consumeCharFromEnd( )         );
        UT_EQ(  'o',       s.consumeCharFromEnd( )         );
        UT_EQ(  'w',       s.consumeCharFromEnd( )         );

        UT_EQ(  false    , s.consumeCharFromEnd('2'                        )   );
        UT_EQ(  true     , s.consumeCharFromEnd('2'     , Case.SENSITIVE, Whitespaces.TRIM )   );
        UT_EQ(  true     , s.consumeCharFromEnd('d'     , Case.SENSITIVE, Whitespaces.TRIM )   );
        UT_EQ(  false    , s.consumeCharFromEnd('d'     , Case.SENSITIVE, Whitespaces.TRIM )   );
        UT_EQ(  true     , s.consumeCharFromEnd('r'     , Case.SENSITIVE, Whitespaces.TRIM )   );
        UT_EQ(  false    , s.consumeStringFromEnd("WO"    , Case.SENSITIVE, Whitespaces.TRIM )   );
        UT_EQ(  false    , s.consumeStringFromEnd("WO"                       )   );
        UT_EQ(  true     , s.consumeStringFromEnd("wo"                       )   );

        UT_EQ(  2        , s.consumeCharFromEnd( 4 )   );
        UT_EQ(  "wo"     , s.toString() );
    }

    // Tokens
    {
        Substring s= new Substring("word1 word2 word3");
        Substring t=new Substring();
        s.consumeToken(t, ' '); UT_EQ( "word1", t.toString() );    UT_EQ( "word2 word3", s.toString() );
        s.consumeToken(t, ' '); UT_EQ( "word2", t.toString() );    UT_EQ( "word3"      , s.toString() );
        s.consumeToken(t, ' '); UT_EQ( "word3", t.toString() );    UT_EQ( 0, s.length() );
        s.consumeToken(t, ' '); UT_EQ( ""     , t.toString() );    UT_EQ( 0, s.length() );
        s.consumeToken(t, ' '); UT_EQ( ""     , t.toString() );    UT_EQ( 0, s.length() );
    }


    {
        Substring subs= new Substring("1234567890");
        UT_EQ( 0, subs.consumePartOf("abc") );
        UT_EQ( 0, subs.consumePartOf("abc", 2) );
        UT_EQ( 0, subs.consumePartOf("abc", 5) );
        UT_EQ( 0, subs.consumePartOf("125", 5) );       UT_EQ( "1234567890", subs.toString() );
        UT_EQ( 0, subs.consumePartOf("125", 3) );       UT_EQ( "1234567890", subs.toString() );
        UT_EQ( 2, subs.consumePartOf("125", 2) );       UT_EQ(   "34567890", subs.toString() );
        UT_EQ( 0, subs.consumePartOf("125")    );       UT_EQ(   "34567890", subs.toString() );
        UT_EQ( 2, subs.consumePartOf("34" )    );       UT_EQ(     "567890", subs.toString() );
        UT_EQ( 1, subs.consumePartOf("59" )    );       UT_EQ(      "67890", subs.toString() );
        UT_EQ( 3, subs.consumePartOf("678", 2 ));       UT_EQ(         "90", subs.toString() );
        UT_EQ( 2, subs.consumePartOf("90"     ));       UT_EQ(           "", subs.toString() );
        UT_EQ( 0, subs.consumePartOf("90"     ));       UT_EQ(           "", subs.toString() );
        UT_EQ( 0, subs.consumePartOf(""       ));       UT_EQ(           "", subs.toString() );
    }

    {
        Substring subs= new Substring("abcdef");
        UT_EQ( 0, subs.consumePartOf("ABC"   , 1, Case.SENSITIVE)  );
        UT_EQ( 0, subs.consumePartOf("aBC"   , 2, Case.SENSITIVE)  );
        UT_EQ( 0, subs.consumePartOf("aBC"   , 5, Case.SENSITIVE)  );
        UT_EQ( 0, subs.consumePartOf("aBX"   , 3, Case.IGNORE)     );       UT_EQ( "abcdef", subs.toString() );
        UT_EQ( 0, subs.consumePartOf("aBX"   , 2, Case.SENSITIVE)  );       UT_EQ( "abcdef", subs.toString() );
        UT_EQ( 2, subs.consumePartOf("aBX"   , 2, Case.IGNORE)     );       UT_EQ(   "cdef", subs.toString() );
        UT_EQ( 0, subs.consumePartOf("CXX"   , 2, Case.IGNORE)     );       UT_EQ(   "cdef", subs.toString() );
        UT_EQ( 1, subs.consumePartOf("CXX"   , 1, Case.IGNORE)     );       UT_EQ(    "def", subs.toString() );
        UT_EQ( 3, subs.consumePartOf("def"   , 2, Case.IGNORE)     );       UT_EQ(       "", subs.toString() );
        UT_EQ( 0, subs.consumePartOf("def"   , 2, Case.IGNORE)     );       UT_EQ(       "", subs.toString() );
        UT_EQ( 0, subs.consumePartOf(""      , 2, Case.IGNORE)     );       UT_EQ(       "", subs.toString() );
        UT_EQ( 0, subs.consumePartOf(""      , 0, Case.IGNORE)     );       UT_EQ(       "", subs.toString() );
    }
}


//--------------------------------------------------------------------------------------------------
//--- Test ConsumeNumbers
//--------------------------------------------------------------------------------------------------
public void ConsumeNumbers()
{
    UT_INIT();

    // ConsumeDec()
    {
        Substring subs= new Substring();
                                        UT_EQ( false,  subs.consumeInt(   ) );   UT_EQ(       0,  subs.consumedLong );
        subs.set( ""            );      UT_EQ( false,  subs.consumeInt(   ) );   UT_EQ(       0,  subs.consumedLong );
        subs.set( "  ABC"       );      UT_EQ( false,  subs.consumeInt(   ) );   UT_EQ(       0,  subs.consumedLong );
        subs.set( "  12345"     );      UT_EQ( true ,  subs.consumeInt(   ) );   UT_EQ(   12345,  subs.consumedLong );
        subs.set( "  12 45"     );      UT_EQ( true ,  subs.consumeInt(   ) );   UT_EQ(      12,  subs.consumedLong );
                                        UT_EQ( true ,  subs.consumeInt(   ) );   UT_EQ(      45,  subs.consumedLong );

        subs.set( " 42 ; 7 ; 6 ");      UT_EQ( true ,  subs.consumeInt(   ) );   UT_EQ(      42,  subs.consumedLong );
                                        UT_EQ( false,  subs.consumeInt(   ) );   UT_EQ(       0,  subs.consumedLong );
                                        UT_EQ( false,  subs.consumeInt(   ) );   UT_EQ(       0,  subs.consumedLong );

        NumberFormat nf= new NumberFormat();
        nf.whitespaces= " ;".toCharArray();
        subs.set( " 42 ; 7 ; 6 ");      UT_EQ( true ,  subs.consumeInt( nf ) );   UT_EQ(      42,  subs.consumedLong );
                                        UT_EQ( true ,  subs.consumeInt( nf ) );   UT_EQ(       7,  subs.consumedLong );
                                        UT_EQ( true ,  subs.consumeInt( nf ) );   UT_EQ(       6,  subs.consumedLong );
                                        UT_EQ( false,  subs.consumeInt( nf ) );   UT_EQ(       0,  subs.consumedLong );
                                        UT_EQ( false,  subs.consumeInt( nf ) );   UT_EQ(       0,  subs.consumedLong );
    }

    // ConsumeFloat()
    {
        Substring subs= new Substring();
        NumberFormat nf= new NumberFormat();
                                        UT_EQ( false,  subs.consumeFloat    ( nf ) );   UT_EQ(      0.0,  subs.consumedFloat );
        subs.set( ""        )         ; UT_EQ( false,  subs.consumeFloat    ( nf ) );   UT_EQ(      0.0,  subs.consumedFloat );
        subs.set( "  ABC"   )         ; UT_EQ( false,  subs.consumeFloat    ( nf ) );   UT_EQ(      0.0,  subs.consumedFloat );
        subs.set( "  12345" )         ; UT_EQ( true ,  subs.consumeFloat    ( nf ) );   UT_EQ(  12345.0,  subs.consumedFloat );
        subs.set( " 12.45 " )         ; UT_EQ( true ,  subs.consumeFloat    ( nf ) );   UT_EQ(     12.45, subs.consumedFloat );
        subs.set( "  12 45" )         ; UT_EQ( true ,  subs.consumeFloat    ( nf ) );   UT_EQ(     12.0,  subs.consumedFloat );
                                        UT_EQ( true ,  subs.consumeFloat    ( nf ) );   UT_EQ(     45.0,  subs.consumedFloat );

        nf.whitespaces= " ;".toCharArray();
        subs.set( " 42.3 ; 0.7 ; 6 " ); UT_EQ( true ,  subs.consumeFloat    ( nf ) );   UT_EQ(     42.3,  subs.consumedFloat );
                                        UT_EQ( true ,  subs.consumeFloat    ( nf ) );   UT_EQ(      0.7,  subs.consumedFloat );
                                        UT_EQ( true ,  subs.consumeFloat    ( nf ) );   UT_EQ(      6.0,  subs.consumedFloat );
                                        UT_EQ( false,  subs.consumeFloat    ( nf ) );   UT_EQ(      0.0,  subs.consumedFloat );
                                        UT_EQ( false,  subs.consumeFloat    ( nf ) );   UT_EQ(      0.0,  subs.consumedFloat );
    }
}


//--------------------------------------------------------------------------------------------------
//--- Test CompareTo
//--------------------------------------------------------------------------------------------------
@SuppressWarnings("static-method")
@Test
public void CompareTo()
{
    UT_INIT();

    int result;

    // null string comparison
    String  nullString= null;
    AString aString= new AString(0);
    UT_TRUE( aString.compareTo( nullString) == 0 );
    UT_TRUE( aString.equals( nullString) );

    aString._( "" );
    UT_TRUE( aString.compareTo( nullString) != 0 );
    UT_TRUE( !aString.equals( nullString) );

    aString.setBuffer( 0 );
    UT_TRUE( aString.compareTo( nullString) == 0 );
    UT_TRUE( aString.equals( nullString) );


    String t= "abcde";
    Substring ms= new Substring("01"+t+"234", 2, t.length() );
    result= ms.compareTo( t      );                                     UT_EQ( t.compareTo( t ),                                result );
    result= ms.compareTo( t + "x"      );                               UT_EQ( t.compareTo( t + "x" ),                          result );
    result= ms.compareTo( t.substring (0, t.length() -1 )  );           UT_EQ( t.compareTo( t.substring (0, t.length() -1 ) ),  result );
    result= ms.compareTo( "pad" + t,  Case.SENSITIVE, 3            );   UT_EQ(  0,                                              result );
    result= ms.compareTo( "pad" + t,  Case.SENSITIVE, 3, 2         );   UT_EQ(  1,                                              result );


    // greater/smaller strings
    String greater=     "x";
    String greater2= "abcdef";
    String smaller=  "aaa";
    String smaller2= "abcd";
    result= ms.compareTo( greater  );   UT_EQ( t.compareTo( greater  ),  result );
    result= ms.compareTo( greater2 );   UT_EQ( t.compareTo( greater2 ),  result );
    result= ms.compareTo( smaller  );   UT_EQ( t.compareTo( smaller ),   result );
    result= ms.compareTo( smaller2 );   UT_EQ( t.compareTo( smaller2 ),  result );

    // ignore case
    String ut= t.toUpperCase();
    result= ms.compareTo( ut );                      UT_EQ( t.compareTo(ut),       result );
    result= ms.compareTo( ut, Case.SENSITIVE );      UT_EQ( t.compareTo(ut),       result );
    result= ms.compareTo( ut, Case.IGNORE );         UT_EQ( 0,                     result );
}


//--------------------------------------------------------------------------------------------------
//--- Tokenizer
//--------------------------------------------------------------------------------------------------
static  void tokenizerTest( String inputString, AString res, char delim, char newDelim,
                    Whitespaces trim, int inpStart, int inpEnd  )
{
    Substring inp= new Substring( inputString );
    if ( inpStart >= 0 ) inp.start= inpStart;
    if ( inpEnd   >= 0 ) inp.end=   inpEnd;
    res.clear();

    Tokenizer tknzr= new Tokenizer( inp, delim );

    while( tknzr.hasNext() )
    {
        tknzr.next(trim).copyTo( res, true );
        res._( newDelim );
    }

}

static
void tokenizerTest( String inputString, AString res, char delim, char newDelim,
                    Whitespaces trim, int inpStart  )
{
    tokenizerTest( inputString, res, delim, newDelim, trim, inpStart, -1);
}

static
void tokenizerTest( String inputString, AString res, char delim, char newDelim,
                    Whitespaces trim )
{
    tokenizerTest( inputString, res, delim, newDelim, trim, -1, -1);
}

@SuppressWarnings("static-method")
@Test
public void Tokenize()
{
    UT_INIT();

    AString astr=  new AString();
    AString res=   new AString();

    // tokenizing empty string
    astr.clear()._( "" );
    res.clear();
    {
        Tokenizer tknzr= new Tokenizer( astr, ',' );   UT_EQ( true,  tknzr.hasNext() );
        tknzr.next().copyTo( res, true );              UT_TRUE( res.isEmpty() );
    }

    // tokenizing no delim
    astr.clear()._( "abc" );
    res.clear();
    {
        Tokenizer tknzr= new Tokenizer( astr, ',' );                UT_EQ( true,  tknzr.hasNext() );
        tknzr.next().copyTo( res, true );     UT_EQ( "abc", res );
    }

    // tokenizing
    {
        tokenizerTest( "abc",                res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "abc@",               res );
        tokenizerTest( "a,bc",               res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@bc@",              res );
        tokenizerTest( "a,bc",               res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@bc@",              res );
        tokenizerTest( ",",                  res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "@@",                 res );
        tokenizerTest( ",,",                 res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "@@@",                res );
        tokenizerTest( "a,b,c,,",            res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@b@c@@@",           res );
        tokenizerTest( "a,b,c",              res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "a@b@c@",             res );
        tokenizerTest( ",a,b,c",             res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "@a@b@c@",            res );
        tokenizerTest( "123567",             res, ',', '@',   Whitespaces.TRIM,  2,    2 );  UT_EQ ( "3@",                 res );
        tokenizerTest( "123567",             res, ',', '@',   Whitespaces.TRIM,  2,    1 );  UT_EQ ( "@",                  res );
        tokenizerTest( "  abc , def , ghe ", res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "abc@def@ghe@",       res );
        tokenizerTest( "abc , def,ghe,",     res, ',', '@',   Whitespaces.TRIM, -1,   -1 );  UT_EQ ( "abc@def@ghe@@",      res );
        tokenizerTest( "  abc , def , ghe ", res, ',', '@',   Whitespaces.KEEP, -1,   -1 );  UT_EQ ( "  abc @ def @ ghe @",res );
        tokenizerTest( "abc , def,ghe,",     res, ',', '@',   Whitespaces.KEEP, -1,   -1 );  UT_EQ ( "abc @ def@ghe@@",    res );
    }

    // tokenizing with different delimiters
    {
        astr.clear()._( "1,5;3@4" );
        Tokenizer tknzr= new Tokenizer(astr, ',');
        tknzr.next()                       .copyTo( res );    UT_EQ ( "1",   res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next( Whitespaces.TRIM, ';' ).copyTo( res );    UT_EQ ( "5",   res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next( Whitespaces.TRIM, '@' ).copyTo( res );    UT_EQ ( "3",   res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next( Whitespaces.TRIM, '-' ).copyTo( res );    UT_EQ ( "4",   res );  UT_EQ( false, tknzr.hasNext() );
    }

    // tokenizing with different delimiters
    {
        astr.clear()._( "abc, 5;\t3;;; 4  " );
        Tokenizer tknzr= new Tokenizer(astr,',');
        tknzr.next()                       .copyTo( res );    UT_EQ ( "abc", res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next( Whitespaces.TRIM, ';' ).copyTo( res );    UT_EQ ( "5",   res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next()                       .copyTo( res );    UT_EQ ( "3",   res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.next()                       .copyTo( res );    UT_EQ ( "",    res );  UT_EQ( true,  tknzr.hasNext() );
        tknzr.getRest()                    .copyTo( res );    UT_EQ ( "; 4", res );  UT_EQ( false, tknzr.hasNext() );
    }

    // sub-tokens
    {
        astr.clear()._( "1,2;3 , 4;5,;," );
        Tokenizer tknzr= new Tokenizer(astr, ';');

        Tokenizer tknzr2= new Tokenizer( tknzr.next(), ',');
        tknzr2.next().copyTo( res ); UT_EQ ( "1", res );  UT_TRUE(  tknzr2.hasNext() );
        tknzr2.next().copyTo( res ); UT_EQ ( "2", res );  UT_TRUE( !tknzr2.hasNext() );
        UT_TRUE( tknzr.hasNext() );

        tknzr2.set( tknzr.next(), ',');
        tknzr2.next().copyTo( res ); UT_EQ ( "3", res );  UT_TRUE(  tknzr2.hasNext() );
        tknzr2.next().copyTo( res ); UT_EQ ( "4", res );  UT_TRUE( !tknzr2.hasNext() );
        UT_TRUE( tknzr.hasNext() );

        tknzr2.set( tknzr.next(), ',');
        tknzr2.next().copyTo( res ); UT_EQ ( "5", res );  UT_TRUE(  tknzr2.hasNext() );
        tknzr2.next().copyTo( res ); UT_EQ ( "",  res );  UT_TRUE( !tknzr2.hasNext() );
        UT_TRUE( tknzr.hasNext() );

        tknzr2.set( tknzr.next(), ',');
        tknzr2.next().copyTo( res ); UT_EQ ( "", res );  UT_TRUE(  tknzr2.hasNext() );
        tknzr2.next().copyTo( res ); UT_EQ ( "", res );  UT_TRUE( !tknzr2.hasNext() );
        UT_TRUE( !tknzr.hasNext() );
    }

}

} // class
