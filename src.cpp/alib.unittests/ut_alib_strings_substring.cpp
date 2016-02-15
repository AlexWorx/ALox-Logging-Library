// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"



#define TESTCLASSNAME       CPP_ALib_Strings_Substring
#include "aworx_unittests.hpp"
#include "alib/compatibility/std_string.hpp"
#include "alib/compatibility/std_iostream.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>


// Windows.h might bring in max/min macros
#if defined( max )
    #undef max
    #undef min
#endif

// For code compatibility with ALox Java/C++
#define _NC _<false>

using namespace std;
using namespace aworx;


namespace ut_aworx {


UT_CLASS()

//---------------------------------------------------------------------------------------------------------
//--- Test Substring
//---------------------------------------------------------------------------------------------------------
void substringConstruction( const char* inputString, AString& res, bool trim )
{
    Substring subs( inputString );
    if (trim)
        subs.Trim();
    res.Clear()._(subs);
}

UT_METHOD( Constructor )

    AString as;
    AString res;

    substringConstruction( "a"        , res, false ); UT_EQ( "a",        res );
    substringConstruction( " a"       , res, false ); UT_EQ( " a",       res );
    substringConstruction( "a "       , res, false ); UT_EQ( "a ",       res );
    substringConstruction( "a b"      , res, false ); UT_EQ( "a b",      res );
    substringConstruction( " a b"     , res, false ); UT_EQ( " a b",     res );
    substringConstruction( "a b "     , res, false ); UT_EQ( "a b ",     res );

    substringConstruction( "a"        , res, true  ); UT_EQ( "a",        res );
    substringConstruction( " a"       , res, true  ); UT_EQ( "a",        res );
    substringConstruction( "a "       , res, true  ); UT_EQ( "a",        res );
    substringConstruction( "a b"      , res, true  ); UT_EQ( "a b",      res );
    substringConstruction( " a b"     , res, true  ); UT_EQ( "a b",      res );
    substringConstruction( "a b "     , res, true  ); UT_EQ( "a b",      res );

    // changing whitespaces
    {
        {
            as= "xy xz abc xy";
            Substring subs;
            (subs= as).Trim( "xy ");
            res= subs;
            UT_EQ( "z abc", res );
        }
        {
            Substring subs( "xy xz abc xy" );
            subs.TrimStart( "xy " );
            subs.TrimEnd( "xy " );
            res= subs;
            UT_EQ( "z abc", res );
        }
    }

    // test other constructors
    {
        {
            Substring null;
            UT_EQ( true,      null.IsEmpty() );
            UT_EQ( true,      null.IsNull()  );
        }

        {
            Substring subs( " const char* " );
            subs.Trim();
            res= subs;
            UT_EQ( "const char*", res );
        }
        {
            Substring subs( "const char* ", 0, 5);
            subs.Trim();
            res= subs;
            UT_EQ( "const", res );
        }

        {
            String64 astr( " astring ");
            Substring subs( astr);
            subs.Trim();
            res= subs;
            UT_EQ( "astring", res );

            Substring subs2( astr, 2, 3 );
            subs2.Trim();
            res= subs2;
            UT_EQ( "str", res );

            Substring subs3( astr, 20, 3 );
            subs3.Trim();
            res= subs3;
            UT_TRUE(  subs3.IsEmpty() );
            UT_TRUE( !subs3.IsNull()  );
        }
    }
}

UT_METHOD( Operators )


    String32 as;
    Substring subs( " word   " );
    subs.Trim();
    as << subs << '@' << subs;

    UT_EQ( "word@word",          as );
    as << '@';
    as << subs;
    UT_EQ( "word@word@word",     as );

    stringstream sstr;
    sstr << subs;
    UT_EQ( "word",        sstr.str().c_str() );

}

UT_METHOD( CharAt)
    // empty substring
    {
        Substring subs;
        UT_EQ(  '\0',      subs.CharAtStart() );
        UT_EQ(  '\0',      subs.CharAtEnd() );
    }

    // Consume/PopLast
    {
        Substring subs("abcde");
        UT_EQ('a',      subs.CharAtStart()           );
        UT_EQ('e',      subs.CharAtEnd ()            );
        UT_EQ('a',      subs.CharAtStart<false>()    );
        UT_EQ('e',      subs.CharAtEnd <false>()     );
        UT_EQ('a',      subs.Consume()               );
        UT_EQ('e',      subs.ConsumeFromEnd()        );
        UT_EQ('d',      subs.ConsumeFromEnd()        );
        UT_EQ('b',      subs.Consume()               );
        UT_EQ('c',      subs.Consume()               );
        UT_EQ('\0',     subs.Consume()               );
        UT_EQ('\0',     subs.Consume()               );
        UT_EQ('\0',     subs.ConsumeFromEnd()        );
        UT_EQ('\0',     subs.ConsumeFromEnd()        );
    }

    // Delete first
    {
        Substring subs("1234567890");
        subs.Consume<false>        (2)     ;UT_TRUE( strncmp( subs.Buffer(), "34567890" , subs.Length() )==0 );
        subs.ConsumeFromEnd <false>(3)     ;UT_TRUE( strncmp( subs.Buffer(), "34567"    , subs.Length() )==0 );
        subs.Consume               (2)     ;UT_TRUE( strncmp( subs.Buffer(), "567890"   , subs.Length() )==0 );
        subs.ConsumeFromEnd        (3)     ;UT_TRUE( strncmp( subs.Buffer(), "34"       , subs.Length() )==0 );
        subs.Consume<false>        (0)     ;UT_TRUE( strncmp( subs.Buffer(), "34"       , subs.Length() )==0 );
        subs.ConsumeFromEnd <false>(0)     ;UT_TRUE( strncmp( subs.Buffer(), "34"       , subs.Length() )==0 );
        subs.Consume               (0)     ;UT_TRUE( strncmp( subs.Buffer(), "34"       , subs.Length() )==0 );
        subs.ConsumeFromEnd        (0)     ;UT_TRUE( strncmp( subs.Buffer(), "34"       , subs.Length() )==0 );
        subs.Consume               (-2)    ;UT_TRUE( strncmp( subs.Buffer(), "34"       , subs.Length() )==0 );
        subs.ConsumeFromEnd        (-2)    ;UT_TRUE( strncmp( subs.Buffer(), "34"       , subs.Length() )==0 );
        subs.Consume               (20)    ;UT_EQ  ( 0 , subs.Length() );
        subs= "1234567890";
        subs.ConsumeFromEnd        (20)    ;UT_EQ  ( 0 , subs.Length() );
    }

}

UT_METHOD( ConsumeNumbers )

    // ConsumeInteger()
    {
        Substring subs;
        int result;
                                   UT_EQ( false,  subs.ConsumeInteger( result                ) );   UT_EQ(       0,  result );
        subs= ""                 ; UT_EQ( false,  subs.ConsumeInteger( result                ) );   UT_EQ(       0,  result );
        subs= "  ABC"            ; UT_EQ( false,  subs.ConsumeInteger( result                ) );   UT_EQ(       0,  result );
        subs= "  12345"          ; UT_EQ( true ,  subs.ConsumeInteger( result                ) );   UT_EQ(   12345,  result );
        subs= "  12 45"          ; UT_EQ( true ,  subs.ConsumeInteger( result                ) );   UT_EQ(      12,  result );
                                   UT_EQ( true ,  subs.ConsumeInteger( result                ) );   UT_EQ(      45,  result );

        subs= " 42 ; 7 ; 6 "     ; UT_EQ( true ,  subs.ConsumeInteger( result                ) );   UT_EQ(      42,  result );
                                   UT_EQ( false,  subs.ConsumeInteger( result                ) );   UT_EQ(       0,  result );
                                   UT_EQ( false,  subs.ConsumeInteger( result                ) );   UT_EQ(       0,  result );

        subs= " 42 ; 7 ; 6 "     ; UT_EQ( true ,  subs.ConsumeInteger( result, " ;"          ) );   UT_EQ(      42,  result );
                                   UT_EQ( true ,  subs.ConsumeInteger( result, " ;"          ) );   UT_EQ(       7,  result );
                                   UT_EQ( true ,  subs.ConsumeInteger( result, " ;"          ) );   UT_EQ(       6,  result );
                                   UT_EQ( false,  subs.ConsumeInteger( result, " ;"          ) );   UT_EQ(       0,  result );
                                   UT_EQ( false,  subs.ConsumeInteger( result, " ;"          ) );   UT_EQ(       0,  result );
    }

    // ConsumeFloat()
    {
        Substring subs;
        double result;
                                   UT_EQ( false,  subs.ConsumeFloat  ( result                ) );   UT_EQ(      0.,  result );
        subs= ""                 ; UT_EQ( false,  subs.ConsumeFloat  ( result                ) );   UT_EQ(      0.,  result );
        subs= "  ABC"            ; UT_EQ( false,  subs.ConsumeFloat  ( result                ) );   UT_EQ(      0.,  result );
        subs= "  12345"          ; UT_EQ( true ,  subs.ConsumeFloat  ( result                ) );   UT_EQ(  12345.,  result );
        subs= " 12.45 "          ; UT_EQ( true ,  subs.ConsumeFloat  ( result                ) );   UT_EQ(  12.45,   result );
        subs= "  12 45"          ; UT_EQ( true ,  subs.ConsumeFloat  ( result                ) );   UT_EQ(     12.,  result );
                                   UT_EQ( true ,  subs.ConsumeFloat  ( result                ) );   UT_EQ(     45.,  result );

        subs= " 42.3 ; 0.7 ; 6 " ; UT_EQ( true ,  subs.ConsumeFloat  ( result, nullptr, " ;" ) );   UT_EQ(    42.3,  result );
                                   UT_EQ( true ,  subs.ConsumeFloat  ( result, nullptr, " ;" ) );   UT_EQ(     0.7,  result );
                                   UT_EQ( true ,  subs.ConsumeFloat  ( result, nullptr, " ;" ) );   UT_EQ(      6.,  result );
                                   UT_EQ( false,  subs.ConsumeFloat  ( result, nullptr, " ;" ) );   UT_EQ(      0.,  result );
                                   UT_EQ( false,  subs.ConsumeFloat  ( result, nullptr, " ;" ) );   UT_EQ(      0.,  result );
    }
}

//---------------------------------------------------------------------------------------------------------
//--- Test Consume
//---------------------------------------------------------------------------------------------------------
UT_METHOD( Consume )
    // null substring
    {
        Substring s= new Substring();
        Substring r("oldval");
        UT_EQ(  '\0',      s.Consume       ( )         );
        UT_EQ(  0,         s.Consume       (  0  , &r) ); UT_TRUE(r.IsNull());
        UT_EQ(  0,         s.Consume       (  5  , &r) ); UT_TRUE(r.IsNull());
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
        Substring s= new Substring("");
        Substring r("oldval");
        UT_EQ(  '\0',      s.Consume       ( )         );
        UT_EQ(  0,         s.Consume       (  0   ,&r) ); UT_TRUE( r.IsNotNull()); UT_TRUE(r.IsEmpty());
        UT_EQ(  0,         s.Consume       (  5   ,&r) ); UT_TRUE( r.IsNotNull()); UT_TRUE(r.IsEmpty());
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
        Substring s= new Substring();
        Substring r("oldval");
        s= "a"; UT_EQ(  'a',       s.Consume       ( )         ); UT_EQ( 0, s.Length() );
        s= "a"; UT_EQ(  1,         s.Consume       (  0  )     ); UT_EQ( 1, s.Length() );
        s= "a"; UT_EQ(  0,         s.Consume       (  1  , &r) ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("a"));
        s= "a"; UT_EQ(  0,         s.Consume       (  5  , &r) ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("a"));
        s= "a"; UT_EQ(  true,      s.Consume       ( 'a' )     ); UT_EQ( 0, s.Length() );
        s= "a"; UT_EQ(  false,     s.Consume       ( 'b' )     ); UT_EQ( 1, s.Length() );
        s= "a"; UT_EQ(  false,     s.Consume       ( "word" )  ); UT_EQ( 1, s.Length() );
        s= "a"; UT_EQ(  'a',       s.ConsumeFromEnd( )         ); UT_EQ( 0, s.Length() );
        s= "a"; UT_EQ(  1,         s.ConsumeFromEnd(  0  )     ); UT_EQ( 1, s.Length() );
        s= "a"; UT_EQ(  0,         s.ConsumeFromEnd(  1  )     ); UT_EQ( 0, s.Length() );
        s= "a"; UT_EQ(  0,         s.ConsumeFromEnd(  5  )     ); UT_EQ( 0, s.Length() );
        s= "a"; UT_EQ(  true,      s.ConsumeFromEnd( 'a' )     ); UT_EQ( 0, s.Length() );
        s= "a"; UT_EQ(  false,     s.ConsumeFromEnd( 'b' )     ); UT_EQ( 1, s.Length() );
        s= "a"; UT_EQ(  false,     s.ConsumeFromEnd( "word" )  ); UT_EQ( 1, s.Length() );
    }

    // substring of length 2
    {
        Substring s= new Substring();
        Substring r("oldval");

        s= "ab"; UT_EQ(  'a',       s.Consume       ( )         ); UT_EQ( 1, s.Length() );
                 UT_EQ(  'b',       s.Consume       ( )         ); UT_EQ( 0, s.Length() );
        s= "ab"; UT_EQ(  'b',       s.ConsumeFromEnd( )         ); UT_EQ( 1, s.Length() );
                 UT_EQ(  'a',       s.ConsumeFromEnd( )         ); UT_EQ( 0, s.Length() );

        s= "ab"; UT_EQ(  2,         s.Consume       (  0  ,&r)  ); UT_EQ( 2, s.Length() ); UT_TRUE(r.IsNotNull()); UT_TRUE(r.IsEmpty());
        s= "ab"; UT_EQ(  1,         s.Consume       (  1  ,&r)  ); UT_EQ( 1, s.Length() ); UT_TRUE(r.Equals("a" ));
        s= "ab"; UT_EQ(  0,         s.Consume       (  2  ,&r)  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));
        s= "ab"; UT_EQ(  0,         s.Consume       (  3  ,&r)  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));
        s= "ab"; UT_EQ(  2,         s.ConsumeFromEnd(  0  ,&r)  ); UT_EQ( 2, s.Length() ); UT_TRUE(r.IsNotNull()); UT_TRUE(r.IsEmpty());
        s= "ab"; UT_EQ(  1,         s.ConsumeFromEnd(  1  ,&r)  ); UT_EQ( 1, s.Length() ); UT_TRUE(r.Equals("b" ));
        s= "ab"; UT_EQ(  0,         s.ConsumeFromEnd(  2  ,&r)  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));
        s= "ab"; UT_EQ(  0,         s.ConsumeFromEnd(  3  ,&r)  ); UT_EQ( 0, s.Length() ); UT_TRUE(r.Equals("ab"));

        s= "ab"; UT_EQ(  false,     s.Consume       ( 'b' )     ); UT_EQ( 2, s.Length() );
                 UT_EQ(  true,      s.Consume       ( 'a' )     ); UT_EQ( 1, s.Length() );
                 UT_EQ(  true,      s.Consume       ( 'b' )     ); UT_EQ( 0, s.Length() );
                 UT_EQ(  false,     s.Consume       ( 'a' )     ); UT_EQ( 0, s.Length() );
                 UT_EQ(  false,     s.Consume       ( 'b' )     ); UT_EQ( 0, s.Length() );
        s= "ab"; UT_EQ(  false,     s.ConsumeFromEnd( 'a' )     ); UT_EQ( 2, s.Length() );
                 UT_EQ(  true,      s.ConsumeFromEnd( 'b' )     ); UT_EQ( 1, s.Length() );
                 UT_EQ(  true,      s.ConsumeFromEnd( 'a' )     ); UT_EQ( 0, s.Length() );
                 UT_EQ(  false,     s.ConsumeFromEnd( 'b' )     ); UT_EQ( 0, s.Length() );
                 UT_EQ(  false,     s.ConsumeFromEnd( 'a' )     ); UT_EQ( 0, s.Length() );

        s= "ab"; UT_EQ(  false,     s.Consume       ( "word" )  ); UT_EQ( 2, s.Length() );
        s= "ab"; UT_EQ(  false,     s.Consume       ( "AB"   )  ); UT_EQ( 2, s.Length() );
        s= "ab"; UT_EQ(  true,      s.Consume       ( "ab"   )  ); UT_EQ( 0, s.Length() );
        s= "ab"; UT_EQ(  false,     s.ConsumeFromEnd( "word" )  ); UT_EQ( 2, s.Length() );
        s= "ab"; UT_EQ(  false,     s.ConsumeFromEnd( "AB"   )  ); UT_EQ( 2, s.Length() );
        s= "ab"; UT_EQ(  true,      s.ConsumeFromEnd( "ab"   )  ); UT_EQ( 0, s.Length() );
    }

    // 3 words
    {
        Substring s= new Substring("word1 word2 word3");

        UT_EQ(  'w',       s.Consume       ( )         );
        UT_EQ(  'o',       s.Consume       ( )         );
        UT_EQ(  'r',       s.Consume       ( )         );
        UT_EQ(  'd',       s.Consume       ( )         );
        UT_EQ(  '1',       s.Consume       ( )         );

        UT_EQ(  false    , s.Consume       ('w'                         )   );
        UT_EQ(  true     , s.Consume       ('w'     , Whitespaces::Trim )   );
        UT_EQ(  true     , s.Consume       ('o'     , Whitespaces::Trim )   );
        UT_EQ(  false    , s.Consume       ('o'     , Whitespaces::Trim )   );
        UT_EQ(  true     , s.Consume       ('r'     , Whitespaces::Trim )   );
        UT_EQ(  false    , s.Consume       ("D2"    , Whitespaces::Trim )   );
        UT_EQ(  false    , s.Consume       ("D2"                        )   );
        UT_EQ(  true     , s.Consume       ("d2"                        )   );

        UT_EQ(  2        , s.Consume       ( 4 )   );
        UT_EQ(  "d3"     , s );

                  s= new Substring("word1 word2 word3");

        UT_EQ(  '3',       s.ConsumeFromEnd( )         );
        UT_EQ(  'd',       s.ConsumeFromEnd( )         );
        UT_EQ(  'r',       s.ConsumeFromEnd( )         );
        UT_EQ(  'o',       s.ConsumeFromEnd( )         );
        UT_EQ(  'w',       s.ConsumeFromEnd( )         );

        UT_EQ(  false    , s.ConsumeFromEnd('2'                         )   );
        UT_EQ(  true     , s.ConsumeFromEnd('2'     , Whitespaces::Trim )   );
        UT_EQ(  true     , s.ConsumeFromEnd('d'     , Whitespaces::Trim )   );
        UT_EQ(  false    , s.ConsumeFromEnd('d'     , Whitespaces::Trim )   );
        UT_EQ(  true     , s.ConsumeFromEnd('r'     , Whitespaces::Trim )   );
        UT_EQ(  false    , s.ConsumeFromEnd("WO"    , Whitespaces::Trim )   );
        UT_EQ(  false    , s.ConsumeFromEnd("WO"                        )   );
        UT_EQ(  true     , s.ConsumeFromEnd("wo"                        )   );

        UT_EQ(  2        , s.ConsumeFromEnd( 4 )   );
        UT_EQ(  "wo"     , s );
    }
}


UT_CLASS_END

}; //namespace
