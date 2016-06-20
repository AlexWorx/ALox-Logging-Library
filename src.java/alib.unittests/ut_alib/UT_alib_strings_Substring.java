// #################################################################################################
//  Unit Tests - AWorx Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package ut_alib;
import org.junit.Test;

import ut_com_aworx_uttools.AUnitTest;

import com.aworx.lib.enums.Case;
import com.aworx.lib.enums.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;


public class UT_alib_strings_Substring extends AUnitTest
{

    //--------------------------------------------------------------------------------------------------
    //--- Test Constructor
    //--------------------------------------------------------------------------------------------------
    void constructorTest( String inputString, AString result, boolean trim )
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
                subs.set(astr).trim("xy ".toCharArray());
                subs.copyTo( res );
                UT_EQ( "z abc",      res );
            }

            {
                Substring subs= new Substring( "xy xz abc xy" );
                subs.trimStart("xy ".toCharArray());
                subs.trimEnd("xy ".toCharArray());
                subs.copyTo( res );
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

            UT_EQ(  '\0',      s.consume       ( )         );
            UT_EQ(  0,         s.consume       (  0 ,   r) ); UT_TRUE(r.isNull());
            UT_EQ(  0,         s.consume       (  5 ,   r) ); UT_TRUE(r.isNull());
            UT_EQ(  false,     s.consume       ( 'a' )     );
            UT_EQ(  false,     s.consume       ( "word" )  );
            UT_EQ(  '\0',      s.consumeFromEnd( )         );
            UT_EQ(  0,         s.consumeFromEnd(  0  )     );
            UT_EQ(  0,         s.consumeFromEnd(  5  )     );
            UT_EQ(  false,     s.consumeFromEnd( 'a' )     );
            UT_EQ(  false,     s.consumeFromEnd( "word" )  );
        }

        // empty substring
        {
            Substring s= new Substring("aaaaaaaaaaaa");
            Substring r= new Substring("oldval");
            s.start= 5;
            s.end=   4;
            UT_EQ(  '\0',      s.consume       ( )         );
            UT_EQ(  0,         s.consume       (  0   , r) ); UT_TRUE( r.isNotNull()); UT_TRUE(r.isEmpty());
            UT_EQ(  0,         s.consume       (  5   , r) ); UT_TRUE( r.isNotNull()); UT_TRUE(r.isEmpty());
            UT_EQ(  false,     s.consume       ( 'a' )     );
            UT_EQ(  false,     s.consume       ( "word" )  );
            UT_EQ(  '\0',      s.consumeFromEnd( )         );
            UT_EQ(  0,         s.consumeFromEnd(  0  )     );
            UT_EQ(  0,         s.consumeFromEnd(  5  )     );
            UT_EQ(  false,     s.consumeFromEnd( 'a' )     );
            UT_EQ(  false,     s.consumeFromEnd( "word" )  );
        }

        // substring of length 1
        {
            Substring s= new Substring("aaaaaaaaaaaa");
            Substring r= new Substring("oldval");

            s.start= s.end= 5; UT_EQ(  'a',       s.consume       ( )         ); UT_EQ( 0, s.length() );
            s.start= s.end= 5; UT_EQ(  1,         s.consume       (  0  )     ); UT_EQ( 1, s.length() );
            s.start= s.end= 5; UT_EQ(  0,         s.consume       (  1  , r)  ); UT_EQ( 0, s.length() );  UT_TRUE(r.equals("a"));
            s.start= s.end= 5; UT_EQ(  0,         s.consume       (  5  , r)  ); UT_EQ( 0, s.length() );  UT_TRUE(r.equals("a"));
            s.start= s.end= 5; UT_EQ(  true,      s.consume       ( 'a' )     ); UT_EQ( 0, s.length() );
            s.start= s.end= 5; UT_EQ(  false,     s.consume       ( 'b' )     ); UT_EQ( 1, s.length() );
            s.start= s.end= 5; UT_EQ(  false,     s.consume       ( "word" )  ); UT_EQ( 1, s.length() );
            s.start= s.end= 5; UT_EQ(  'a',       s.consumeFromEnd( )         ); UT_EQ( 0, s.length() );
            s.start= s.end= 5; UT_EQ(  1,         s.consumeFromEnd(  0  )     ); UT_EQ( 1, s.length() );
            s.start= s.end= 5; UT_EQ(  0,         s.consumeFromEnd(  1  )     ); UT_EQ( 0, s.length() );
            s.start= s.end= 5; UT_EQ(  0,         s.consumeFromEnd(  5  )     ); UT_EQ( 0, s.length() );
            s.start= s.end= 5; UT_EQ(  true,      s.consumeFromEnd( 'a' )     ); UT_EQ( 0, s.length() );
            s.start= s.end= 5; UT_EQ(  false,     s.consumeFromEnd( 'b' )     ); UT_EQ( 1, s.length() );
            s.start= s.end= 5; UT_EQ(  false,     s.consumeFromEnd( "word" )  ); UT_EQ( 1, s.length() );
        }

        // substring of length 2
        {
            Substring s= new Substring("12ab3456");
            Substring r= new Substring("oldval");

            s.start= 2; s.end= 3; UT_EQ(  'a',       s.consume       ( )         ); UT_EQ( 1, s.length() );
                                  UT_EQ(  'b',       s.consume       ( )         ); UT_EQ( 0, s.length() );
            s.start= 2; s.end= 3; UT_EQ(  'b',       s.consumeFromEnd( )         ); UT_EQ( 1, s.length() );
                                  UT_EQ(  'a',       s.consumeFromEnd( )         ); UT_EQ( 0, s.length() );

            s.start= 2; s.end= 3; UT_EQ(  2,         s.consume       (  0   , r) ); UT_EQ( 2, s.length() ); UT_TRUE(r.isNotNull()); UT_TRUE(r.isEmpty());
            s.start= 2; s.end= 3; UT_EQ(  1,         s.consume       (  1   , r) ); UT_EQ( 1, s.length() ); UT_TRUE(r.equals("a"));                       
            s.start= 2; s.end= 3; UT_EQ(  0,         s.consume       (  2   , r) ); UT_EQ( 0, s.length() ); UT_TRUE(r.equals("ab"));                      
            s.start= 2; s.end= 3; UT_EQ(  0,         s.consume       (  3   , r) ); UT_EQ( 0, s.length() ); UT_TRUE(r.equals("ab"));                      
            s.start= 2; s.end= 3; UT_EQ(  2,         s.consumeFromEnd(  0   , r) ); UT_EQ( 2, s.length() ); UT_TRUE(r.isNotNull()); UT_TRUE(r.isEmpty());
            s.start= 2; s.end= 3; UT_EQ(  1,         s.consumeFromEnd(  1   , r) ); UT_EQ( 1, s.length() ); UT_TRUE(r.equals("b"));                       
            s.start= 2; s.end= 3; UT_EQ(  0,         s.consumeFromEnd(  2   , r) ); UT_EQ( 0, s.length() ); UT_TRUE(r.equals("ab"));                      
            s.start= 2; s.end= 3; UT_EQ(  0,         s.consumeFromEnd(  3   , r) ); UT_EQ( 0, s.length() ); UT_TRUE(r.equals("ab"));                      

            s.start= 2; s.end= 3; UT_EQ(  false,     s.consume       ( 'b' )     ); UT_EQ( 2, s.length() );
                                  UT_EQ(  true,      s.consume       ( 'a' )     ); UT_EQ( 1, s.length() );
                                  UT_EQ(  true,      s.consume       ( 'b' )     ); UT_EQ( 0, s.length() );
                                  UT_EQ(  false,     s.consume       ( 'a' )     ); UT_EQ( 0, s.length() );
                                  UT_EQ(  false,     s.consume       ( 'b' )     ); UT_EQ( 0, s.length() );
            s.start= 2; s.end= 3; UT_EQ(  false,     s.consumeFromEnd( 'a' )     ); UT_EQ( 2, s.length() );
                                  UT_EQ(  true,      s.consumeFromEnd( 'b' )     ); UT_EQ( 1, s.length() );
                                  UT_EQ(  true,      s.consumeFromEnd( 'a' )     ); UT_EQ( 0, s.length() );
                                  UT_EQ(  false,     s.consumeFromEnd( 'b' )     ); UT_EQ( 0, s.length() );
                                  UT_EQ(  false,     s.consumeFromEnd( 'a' )     ); UT_EQ( 0, s.length() );

            s.start= 2; s.end= 3; UT_EQ(  false,     s.consume       ( "word" )  ); UT_EQ( 2, s.length() );
            s.start= 2; s.end= 3; UT_EQ(  false,     s.consume       ( "AB"   )  ); UT_EQ( 2, s.length() );
            s.start= 2; s.end= 3; UT_EQ(  true,      s.consume       ( "ab"   )  ); UT_EQ( 0, s.length() );
            s.start= 2; s.end= 3; UT_EQ(  false,     s.consumeFromEnd( "word" )  ); UT_EQ( 2, s.length() );
            s.start= 2; s.end= 3; UT_EQ(  false,     s.consumeFromEnd( "AB"   )  ); UT_EQ( 2, s.length() );
            s.start= 2; s.end= 3; UT_EQ(  true,      s.consumeFromEnd( "ab"   )  ); UT_EQ( 0, s.length() );
        }

        // 3 words
        {
            Substring s= new Substring("word1 word2 word3");

            UT_EQ(  'w',       s.consume       ( )         );
            UT_EQ(  'o',       s.consume       ( )         );
            UT_EQ(  'r',       s.consume       ( )         );
            UT_EQ(  'd',       s.consume       ( )         );
            UT_EQ(  '1',       s.consume       ( )         );

            UT_EQ(  false    , s.consume       ('w'                        )   );
            UT_EQ(  true     , s.consume       ('w'     , Whitespaces.TRIM )   );
            UT_EQ(  true     , s.consume       ('o'     , Whitespaces.TRIM )   );
            UT_EQ(  false    , s.consume       ('o'     , Whitespaces.TRIM )   );
            UT_EQ(  true     , s.consume       ('r'     , Whitespaces.TRIM )   );
            UT_EQ(  false    , s.consume       ("D2"    , Whitespaces.TRIM )   );
            UT_EQ(  false    , s.consume       ("D2"                       )   );
            UT_EQ(  true     , s.consume       ("d2"                       )   );

            UT_EQ(  2        , s.consume       ( 4 )   );
            UT_EQ(  "d3"     , s.toString() );

                      s= new Substring("word1 word2 word3");

            UT_EQ(  '3',       s.consumeFromEnd( )         );
            UT_EQ(  'd',       s.consumeFromEnd( )         );
            UT_EQ(  'r',       s.consumeFromEnd( )         );
            UT_EQ(  'o',       s.consumeFromEnd( )         );
            UT_EQ(  'w',       s.consumeFromEnd( )         );

            UT_EQ(  false    , s.consumeFromEnd('2'                        )   );
            UT_EQ(  true     , s.consumeFromEnd('2'     , Whitespaces.TRIM )   );
            UT_EQ(  true     , s.consumeFromEnd('d'     , Whitespaces.TRIM )   );
            UT_EQ(  false    , s.consumeFromEnd('d'     , Whitespaces.TRIM )   );
            UT_EQ(  true     , s.consumeFromEnd('r'     , Whitespaces.TRIM )   );
            UT_EQ(  false    , s.consumeFromEnd("WO"    , Whitespaces.TRIM )   );
            UT_EQ(  false    , s.consumeFromEnd("WO"                       )   );
            UT_EQ(  true     , s.consumeFromEnd("wo"                       )   );

            UT_EQ(  2        , s.consumeFromEnd( 4 )   );
            UT_EQ(  "wo"     , s.toString() );
        }
    }

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
    //--- Test ParseNumbers
    //--------------------------------------------------------------------------------------------------
    public void ParseNumbers()
    {
        UT_INIT();
        
        // toInt()
        {
            Substring subs= new Substring();

                                           UT_EQ(     0,   subs.toInt() ); UT_EQ( 0,   subs.start );
            subs.set( ""              );   UT_EQ(     0,   subs.toInt() ); UT_EQ( 0,   subs.start );
            subs.set( "  ABC"         );   UT_EQ(     0,   subs.toInt() ); UT_EQ( 0,   subs.start );
            subs.set( "  12345"       );   UT_EQ( 12345,   subs.toInt() ); UT_EQ( 7,   subs.start );
            subs.set( "  12 45"       );   UT_EQ(    12,   subs.toInt() ); UT_EQ( 4,   subs.start );
                                           UT_EQ(    45,   subs.toInt() ); UT_EQ( 7,   subs.start );

            subs.set( " 42 ; 7 ; 6 "  );   UT_EQ(    42,  subs.toInt() );
                                           UT_EQ(    0,   subs.toInt() );
                                           UT_EQ(    0,   subs.toInt() );

            char[] whitespaces= " ;".toCharArray();
            subs.set( " 42 ; 7 ; 6 ");     UT_EQ(    42,  subs.toInt(whitespaces) );
                                           UT_EQ(    7,   subs.toInt(whitespaces) );
                                           UT_EQ(    6,   subs.toInt(whitespaces) );
                                           UT_EQ(    0,   subs.toInt(whitespaces) );
                                           UT_EQ(    0,   subs.toInt(whitespaces) );
        }

        // toFloat()
        {
            Substring subs= new Substring();

                                           UT_EQ(     0.0,   subs.toFloat(), 0.0 ); UT_EQ( 0,   subs.start );
            subs.set( ""       );          UT_EQ(     0.0,   subs.toFloat(), 0.0 ); UT_EQ( 0,   subs.start );
            subs.set( "  ABC"  );          UT_EQ(     0.0,   subs.toFloat(), 0.0 ); UT_EQ( 0,   subs.start );
            subs.set( "  12345");          UT_EQ( 12345.0,   subs.toFloat(), 0.0 ); UT_EQ( 7,   subs.start );
            subs.set( " 12.45 ");          UT_EQ(    12.45,  subs.toFloat(), 0.0 ); UT_EQ( 6,   subs.start );

            char[] whitespaces= " ;".toCharArray();
            subs.set( " 42.3 ; 0.7 ; 6 "); UT_EQ(    42.3,  subs.toFloat(whitespaces),  0.0000001 );
                                           UT_EQ(    0.7,   subs.toFloat(whitespaces),  0.0000001 );
                                           UT_EQ(    6.0,   subs.toFloat(whitespaces),  0.0000001 );
                                           UT_EQ(    0.0,   subs.toFloat(whitespaces),  0.0000001 );
                                           UT_EQ(    0.0,   subs.toFloat(whitespaces),  0.0000001 );

        }
    }


}
