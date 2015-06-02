// #################################################################################################
//  aworx::util - Unit Tests
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "stdafx_awxu.h"

#if !defined (HPP_AWORX_UTIL_ASTRING)
    #include "astring.hpp"
#endif


#define TESTCLASSNAME       CPP_AString
#include "awx_unittests.hpp"

using namespace std;
using namespace aworx::util;

namespace tests_aworx_util {

A_TEST_CLASS()

//---------------------------------------------------------------------------------------------------------
//--- Test Constructors
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( Constructors )

    AString* ms;
    char*     csNull= nullptr;
               ms= new AString();                        EXPECT_EQ    ( ms->GetAllocation(),   0 );    EXPECT_EQ    ( ms->Length(), 0 );
    delete ms; ms= new AString( 0 );                     EXPECT_EQ    ( ms->GetAllocation(),   0 );    EXPECT_EQ    ( ms->Length(), 0 );
    delete ms; ms= new AString( csNull );                EXPECT_EQ    ( ms->GetAllocation(),   0 );    EXPECT_EQ    ( ms->Length(), 0 );
    delete ms; ms= new AString( "" );                    EXPECT_TRUE  ( ms->GetAllocation() >  0 );    EXPECT_EQ    ( ms->Length(), 0 );
    delete ms; ms= new AString( 25 );                    EXPECT_TRUE  ( ms->GetAllocation() >  0 );    EXPECT_EQ    ( ms->Length(), 0 );
    delete ms; ms= new AString( "Test" );                EXPECT_TRUE  ( ms->GetAllocation() >= 4 );    EXPECT_EQ    ( ms->Length(), 4 );

    AString tMSEmpty;
    delete ms; ms= new AString( (AString*) nullptr );    EXPECT_TRUE ( ms->Length() == 0 );            EXPECT_TRUE  ( ms->GetAllocation() == 0 );
    ms->Append( "was null" );                            EXPECT_TRUE ( ms->Length() == 8 );
    delete ms; ms= new AString( tMSEmpty );              EXPECT_TRUE ( ms->Length() == 0 );            EXPECT_TRUE  ( ms->GetAllocation() > 0 );
    delete ms; ms= new AString( tMSEmpty, 1,     0 );    EXPECT_TRUE ( ms->Length() == 0 );            EXPECT_TRUE  ( ms->GetAllocation() > 0 );
    delete ms; ms= new AString( tMSEmpty, -1000, 0 );    EXPECT_TRUE ( ms->Length() == 0 );            EXPECT_TRUE  ( ms->GetAllocation() > 0 );
    delete ms; ms= new AString( tMSEmpty, -1000, 1 );    EXPECT_TRUE ( ms->Length() == 0 );            EXPECT_TRUE  ( ms->GetAllocation() > 0 );
    delete ms; ms= new AString( tMSEmpty, -100,  1000);  EXPECT_TRUE ( ms->Length() == 0 );            EXPECT_TRUE  ( ms->GetAllocation() > 0 );

    AString tMS( "0123456789" );
    delete ms; ms= new AString( tMS );                   EXPECT_TRUE ( ms->GetAllocation() >=  10 && ms->Length() == 10 );       EXPECT_STREQ( ms->Buffer(), "0123456789");
    delete ms; ms= new AString( tMS, 5);                 EXPECT_TRUE ( ms->GetAllocation() >=   5 && ms->Length() == 5 );        EXPECT_STREQ( ms->Buffer(), "56789");
    delete ms; ms= new AString( tMS, 5, 100);            EXPECT_TRUE ( ms->GetAllocation() >=   5 && ms->Length() == 5 );        EXPECT_STREQ( ms->Buffer(), "56789");
    delete ms; ms= new AString( tMS, -5);                EXPECT_TRUE ( ms->GetAllocation() >=  10 && ms->Length() == 10 );       EXPECT_STREQ( ms->Buffer(), "0123456789");
    delete ms; ms= new AString( tMS, -5, 3);             EXPECT_TRUE ( ms->GetAllocation() >    0 && ms->Length() == 0 );        EXPECT_STREQ( ms->Buffer(), "");
    delete ms; ms= new AString( tMS, 50, 3);             EXPECT_TRUE ( ms->GetAllocation() >    0 && ms->Length() == 0 );        EXPECT_STREQ( ms->Buffer(), "");
    delete ms; ms= new AString( tMS, 10, 3);             EXPECT_TRUE ( ms->GetAllocation() >    0 && ms->Length() == 0 );        EXPECT_STREQ( ms->Buffer(), "");
    delete ms; ms= new AString( tMS, -5, 10);            EXPECT_TRUE ( ms->GetAllocation() >=   5 && ms->Length() == 5 );        EXPECT_STREQ( ms->Buffer(), "01234");
    delete ms; ms= new AString( tMS, -5, 100);           EXPECT_TRUE ( ms->GetAllocation() >=  10 && ms->Length() == 10 );       EXPECT_STREQ( ms->Buffer(), "0123456789");

    string tS("0123456789");
    delete ms; ms= new AString( (string*) nullptr );    EXPECT_TRUE ( ms->Length() == 0 );    EXPECT_TRUE    ( ms->GetAllocation() == 0 );
    ms->Append( "was null" );                           EXPECT_TRUE ( ms->Length() == 8 );
    delete ms; ms= new AString( "" );                   EXPECT_TRUE ( ms->Length() == 0 );    EXPECT_TRUE    ( ms->GetAllocation() > 0 );
    delete ms; ms= new AString( "", 1,     0 );         EXPECT_TRUE ( ms->Length() == 0 );    EXPECT_TRUE    ( ms->GetAllocation() > 0 );
    delete ms; ms= new AString( "", -1000, 0 );         EXPECT_TRUE ( ms->Length() == 0 );    EXPECT_TRUE    ( ms->GetAllocation() > 0 );
    delete ms; ms= new AString( "", -1000, 1 );         EXPECT_TRUE ( ms->Length() == 0 );    EXPECT_TRUE    ( ms->GetAllocation() > 0 );
    delete ms; ms= new AString( "", -100,  1000);       EXPECT_TRUE ( ms->Length() == 0 );    EXPECT_TRUE    ( ms->GetAllocation() > 0 );
    delete ms; ms= new AString( tS );                   EXPECT_TRUE ( ms->GetAllocation() >=  10 && ms->Length() == 10 );
                                                        EXPECT_STREQ( ms->Buffer(), "0123456789");
    delete ms; ms= new AString( tS, 5);                 EXPECT_TRUE ( ms->GetAllocation() >=  5  && ms->Length() == 5 );
                                                        EXPECT_STREQ( ms->Buffer(), "56789");
    delete ms; ms= new AString( tS, 5, 100);            EXPECT_TRUE ( ms->GetAllocation() >=  5  && ms->Length() == 5 );
                                                        EXPECT_STREQ( ms->Buffer(), "56789");
    delete ms; ms= new AString( tS, -5);                EXPECT_TRUE ( ms->GetAllocation() >=  10 && ms->Length() == 10 );
                                                        EXPECT_STREQ( ms->Buffer(), "0123456789");
    delete ms; ms= new AString( tS, -5, 10);            EXPECT_TRUE ( ms->GetAllocation() >=  5  && ms->Length() == 5 );
                                                        EXPECT_STREQ( ms->Buffer(), "01234");
    delete ms; ms= new AString( tS, -5, 100);           EXPECT_TRUE ( ms->GetAllocation() >=  10  && ms->Length() == 10 );
                                                        EXPECT_STREQ( ms->Buffer(), "0123456789");
    const char* tSBEmpty= "";
    delete ms; ms= new AString( tSBEmpty );             EXPECT_TRUE ( ms->Length() == 0 );
    delete ms; ms= new AString( tSBEmpty, 1,     0 );   EXPECT_TRUE ( ms->Length() == 0 );
    delete ms; ms= new AString( tSBEmpty, -1000, 0 );   EXPECT_TRUE ( ms->Length() == 0 );
    delete ms; ms= new AString( tSBEmpty, -1000, 1 );   EXPECT_TRUE ( ms->Length() == 0 );
    delete ms; ms= new AString( tSBEmpty, -100,  1000); EXPECT_TRUE ( ms->Length() == 0 );

    const char*  tSB= "0123456789";
    delete ms; ms= new AString( tSB );                  EXPECT_TRUE ( ms->GetAllocation() >=  10 && ms->Length() == 10 );
                                                        EXPECT_STREQ( ms->Buffer(), "0123456789");
    delete ms; ms= new AString( tSB, 5);                EXPECT_TRUE ( ms->GetAllocation() >=  5  && ms->Length() == 5 );
                                                        EXPECT_STREQ( ms->Buffer(), "56789");
    delete ms; ms= new AString( tSB, 5, 100);           EXPECT_TRUE ( ms->GetAllocation() >=  5  && ms->Length() == 5 );
                                                        EXPECT_STREQ( ms->Buffer(), "56789");
    delete ms; ms= new AString( tSB, -5);               EXPECT_TRUE ( ms->GetAllocation() >=  10 && ms->Length() == 10 );
                                                        EXPECT_STREQ( ms->Buffer(), "0123456789");
    delete ms; ms= new AString( tSB, -5, 10);           EXPECT_TRUE ( ms->GetAllocation() >=  5  && ms->Length() == 5 );
                                                        EXPECT_STREQ( ms->Buffer(), "01234");
    delete ms; ms= new AString( tSB, -5, 100);          EXPECT_TRUE ( ms->GetAllocation() >=  10  && ms->Length() == 10 );
    delete ms;
}

//---------------------------------------------------------------------------------------------------------
//--- Test DeleteInsert
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( DeleteInsertSet )

    AString ms;
    // delete
    {
        ms.Clear().Append("0123456789");        ms.Delete(  5           );    EXPECT_EQ    (  5,    ms.Length() );    EXPECT_STREQ    ( "01234",        ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Delete(  5,      0   );    EXPECT_EQ    ( 10,    ms.Length() );    EXPECT_STREQ    ( "0123456789",   ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Delete(  5,     -1   );    EXPECT_EQ    ( 10,    ms.Length() );    EXPECT_STREQ    ( "0123456789",   ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Delete(  5,      1   );    EXPECT_EQ    (  9,    ms.Length() );    EXPECT_STREQ    ( "012346789",    ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Delete(  5,    100   );    EXPECT_EQ    (  5,    ms.Length() );    EXPECT_STREQ    ( "01234",        ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Delete(  -5,     10  );    EXPECT_EQ    (  5,    ms.Length() );    EXPECT_STREQ    ( "56789",        ms.Buffer() );
    }

    // insert
    {
        ms.Clear().Append("0123456789");        ms.Insert( -1,    1     );    EXPECT_EQ    ( 10,    ms.Length() );    EXPECT_STREQ    ( "0123456789",   ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Insert( 20,    1     );    EXPECT_EQ    ( 10,    ms.Length() );    EXPECT_STREQ    ( "0123456789",   ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Insert(  0,    0     );    EXPECT_EQ    ( 10,    ms.Length() );    EXPECT_STREQ    ( "0123456789",   ms.Buffer() );

        ms.Clear().Append("0123456789");        ms.Insert(  0,    1     );    EXPECT_EQ    ( 11,    ms.Length() );    EXPECT_STREQ    ( " 0123456789",  ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Insert(  1,    1     );    EXPECT_EQ    ( 11,    ms.Length() );    EXPECT_STREQ    ( "0 123456789",  ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Insert(  0,    2     );    EXPECT_EQ    ( 12,    ms.Length() );    EXPECT_STREQ    ( "  0123456789", ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Insert(  1,    2     );    EXPECT_EQ    ( 12,    ms.Length() );    EXPECT_STREQ    ( "0  123456789", ms.Buffer() );

        ms.Clear().Append("0123456789");        ms.Insert(  11,    1    );    EXPECT_EQ    ( 10,    ms.Length() );    EXPECT_STREQ    ( "0123456789",   ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Insert(  10,    1    );    EXPECT_EQ    ( 11,    ms.Length() );    EXPECT_STREQ    ( "0123456789 ",  ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Insert(  5,    3, '@');    EXPECT_EQ    ( 13,    ms.Length() );    EXPECT_STREQ    ( "01234@@@56789",ms.Buffer() );

        // test if tab reference pos is preserved
        ms.Clear().Append("ABC").NewLine().Append("123").Insert(  3, 3, '@'  ).Tab(5, 0, '$').Append('>');
        EXPECT_STREQ    ( AString("ABC@@@").NewLine().Append( "123$$>" ).Buffer(),    ms.Buffer() );

        ms.Clear().Append("ABC").NewLine().Append("123"); ms.Insert(  ms.Length()-2, 3, '@'  ).Tab(5, 0, '$').Append('>');
        EXPECT_STREQ    ( AString("ABC").NewLine().Append( "1@@@23$$$$>" ).Buffer(),    ms.Buffer() );
    }

    // set
    {
        ms.Clear().Append("0123456789");        ms.Fill( '@'             );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "@@@@@@@@@@",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@', -10        );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "@@@@@@@@@@",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@', -10, 100   );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "@@@@@@@@@@",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@', -10,  5    );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "0123456789",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@', -10, 10    );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "0123456789",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@', -10, 11    );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "@123456789",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@',   0,  1    );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "@123456789",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@',   0,  2    );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "@@23456789",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@',   1,  1    );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "0@23456789",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@',   1,  2    );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "0@@3456789",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@',   8,  1    );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "01234567@9",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@',   8,  2    );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "01234567@@",            ms.Buffer() );
        ms.Clear().Append("0123456789");        ms.Fill( '@',   8,  3    );    EXPECT_EQ    (  10,    ms.Length() );    EXPECT_STREQ    ( "01234567@@",            ms.Buffer() );
    }
}

//---------------------------------------------------------------------------------------------------------
//--- Test Conversions
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( Conversions )

    AString*   ms;
    string        s;
    ms= new AString("0123456789");
    s= ms->ToString();                  EXPECT_STREQ( s.c_str(), "0123456789" );
    s= ms->ToString( 5);                EXPECT_STREQ( s.c_str(), "56789" );
    s= ms->ToString( 5, 100);           EXPECT_STREQ( s.c_str(), "56789" );
    s= ms->ToString( -5);               EXPECT_STREQ( s.c_str(), "0123456789" );
    s= ms->ToString( -5, 10);           EXPECT_STREQ( s.c_str(), "01234" );
    s= ms->ToString( -5, 100);          EXPECT_STREQ( s.c_str(), "0123456789" );

    s= ms->ToString( 0,  0);            EXPECT_STREQ( s.c_str(), "" );
    s= ms->ToString( 5,  0);            EXPECT_STREQ( s.c_str(), "" );
    s= ms->ToString( 20, 0);            EXPECT_STREQ( s.c_str(), "" );
    s= ms->ToString( 0,  -1);           EXPECT_STREQ( s.c_str(), "" );
    s= ms->ToString( 5,  -5);           EXPECT_STREQ( s.c_str(), "" );
    s= ms->ToString( 5,  -100);         EXPECT_STREQ( s.c_str(), "" );
    s= ms->ToString( 20,  -1);          EXPECT_STREQ( s.c_str(), "" );
    s= ms->ToString( 20,  20);          EXPECT_STREQ( s.c_str(), "" );
    s= ms->ToString( 20,  -100);        EXPECT_STREQ( s.c_str(), "" );
    s= ms->ToString( 20, 0);            EXPECT_STREQ( s.c_str(), "" );
    s= ms->ToString( 20, 100);          EXPECT_STREQ( s.c_str(), "" );

    ms->ToString(s);                    EXPECT_STREQ( s.c_str(), "0123456789" );
    ms->ToString(s, 5);                 EXPECT_STREQ( s.c_str(), "56789" );
    ms->ToString(s, 5, 100);            EXPECT_STREQ( s.c_str(), "56789" );
    ms->ToString(s, -5);                EXPECT_STREQ( s.c_str(), "0123456789" );
    ms->ToString(s, -5, 10);            EXPECT_STREQ( s.c_str(), "01234" );
    ms->ToString(s, -5, 100);           EXPECT_STREQ( s.c_str(), "0123456789" );

    ms->ToString(s, 0,  0);             EXPECT_STREQ( s.c_str(), "" );
    ms->ToString(s, 5,  0);             EXPECT_STREQ( s.c_str(), "" );
    ms->ToString(s, 20, 0);             EXPECT_STREQ( s.c_str(), "" );
    ms->ToString(s, 0,  -1);            EXPECT_STREQ( s.c_str(), "" );
    ms->ToString(s, 5,  -5);            EXPECT_STREQ( s.c_str(), "" );
    ms->ToString(s, 5,  -100);          EXPECT_STREQ( s.c_str(), "" );
    ms->ToString(s, 20,  -1);           EXPECT_STREQ( s.c_str(), "" );
    ms->ToString(s, 20,  20);           EXPECT_STREQ( s.c_str(), "" );
    ms->ToString(s, 20,  -100);         EXPECT_STREQ( s.c_str(), "" );
    ms->ToString(s, 20, 0);             EXPECT_STREQ( s.c_str(), "" );
    ms->ToString(s, 20, 100);           EXPECT_STREQ( s.c_str(), "" );

    s.clear();
    ms->ToString( s );                  EXPECT_STREQ( s.c_str(), "0123456789"            );
    ms->ToString( s, true );            EXPECT_STREQ( s.c_str(), "01234567890123456789"  );
    ms->ToString( s );                  EXPECT_STREQ( s.c_str(), "0123456789"            );
    ms->ToString( s, 5, 100 );          EXPECT_STREQ( s.c_str(), "56789"                 );
    ms->ToString( s, -5, 10, true );    EXPECT_STREQ( s.c_str(), "5678901234"            );

    delete ms;
}


//---------------------------------------------------------------------------------------------------------
//--- Test Append
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( Append )

    // append strings
    {
        // null paramters
        {
            AString ms;
            const char* csNull= nullptr;
            ms.Append( csNull );                EXPECT_EQ( ms.Length(), 0 );
            ms.Append(   0,   csNull );         EXPECT_EQ( ms.Length(), 0 );
            ms.Append(  10,   csNull );         EXPECT_EQ( ms.Length(), 0 );
            ms.Append( -10,   csNull );         EXPECT_EQ( ms.Length(), 0 );
            ms.Append(  10,   csNull, 1, 8 );   EXPECT_EQ( ms.Length(), 0 );
        }

        // append constant string
        {
            AString ms(5);
            string  t("Hallo World");
            ms.Append(t);

            EXPECT_EQ( (string::size_type) ms.Length(), t.size() );
            for ( unsigned int i= 0; i < t.size() ; i++ )
                EXPECT_EQ( ms[i],  t[i]);
        }

        // append part of constant string
        {
            string  t("Hallo World");
            int        startIdx=    6;
            int        len=        3;
            AString ms(5);
            ms.Append( t, startIdx, len );

            EXPECT_EQ( ms.Length(), len);
            for ( int i= 0; i < len ; i++ )
                EXPECT_EQ( ms[i],  t[ startIdx + i] );
        }

        // append more than available in source string
        {
            string  t("Hallo World");
            int        startIdx=    6;
            int        len=        3;
            AString ms(5);
            ms.Append(t);
            ms.Append ( t, startIdx, t.size() );
            len= t.size() - startIdx;

            EXPECT_EQ( (string::size_type) ms.Length(), t.size() + len );
            for ( int i= 0; i < len ; i++ )
                EXPECT_EQ( ms[t.size() + i],  t[ startIdx + i]);
        }

        // append int32
        {
            AString ms;

            uint32_t ui;
            int32_t   i;

            ms.Clear(); ui= 0;       ms.Append( ui );     EXPECT_STREQ(      "0", ms.Buffer() );
            ms.Clear(); ui= 0;       ms.Append( ui, 1 );  EXPECT_STREQ(      "0", ms.Buffer() );
            ms.Clear(); ui= 0;       ms.Append( ui, 3 );  EXPECT_STREQ(    "000", ms.Buffer() );
            ms.Clear(); ui= 10;      ms.Append( ui );     EXPECT_STREQ(     "10", ms.Buffer() );
            ms.Clear(); ui= 100;     ms.Append( ui, 1 );  EXPECT_STREQ(    "100", ms.Buffer() );
            ms.Clear(); ui= 100;     ms.Append( ui, 3 );  EXPECT_STREQ(    "100", ms.Buffer() );
            ms.Clear(); ui= 100;     ms.Append( ui, 4 );  EXPECT_STREQ(   "0100", ms.Buffer() );
            ms.Clear(); ui= 23;      ms.Append( ui );     EXPECT_STREQ(     "23", ms.Buffer() );
            ms.Clear(); ui= 99;      ms.Append( ui, 5 );  EXPECT_STREQ(  "00099", ms.Buffer() );
            ms.Clear();  i= 49;      ms.Append( i  );     EXPECT_STREQ(     "49", ms.Buffer() );
            ms.Clear();  i= -5;      ms.Append( i, 5 );   EXPECT_STREQ( "-00005", ms.Buffer() );
            ms.Clear();  i= -5324;   ms.Append( i, 2 );   EXPECT_STREQ(  "-5324", ms.Buffer() );
            ms.Clear(); ui= std::numeric_limits<uint32_t>::max();    ms.Append( ui     );   EXPECT_STREQ(    "4294967295",  ms.Buffer() );
            ms.Clear(); ui= std::numeric_limits<uint32_t>::min();    ms.Append( ui     );   EXPECT_STREQ(             "0",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int32_t> ::max();    ms.Append( i      );   EXPECT_STREQ(    "2147483647",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int32_t> ::min();    ms.Append( i      );   EXPECT_STREQ(   "-2147483648",  ms.Buffer() );
            ms.Clear(); ui= std::numeric_limits<uint32_t>::max();    ms.Append( ui, 12 );   EXPECT_STREQ(  "004294967295",  ms.Buffer() );
            ms.Clear(); ui= std::numeric_limits<uint32_t>::min();    ms.Append( ui, 12 );   EXPECT_STREQ(  "000000000000",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int32_t> ::max();    ms.Append( i , 12 );   EXPECT_STREQ(  "002147483647",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int32_t> ::min();    ms.Append( i , 12 );   EXPECT_STREQ( "-002147483648",  ms.Buffer() );
        }

        // append int64
        {
            AString ms;

            uint64_t ui;
            int64_t   i;

            ms.Clear(); ui= 0;       ms.Append( ui );     EXPECT_STREQ(      "0", ms.Buffer() );
            ms.Clear(); ui= 0;       ms.Append( ui, 1 );  EXPECT_STREQ(      "0", ms.Buffer() );
            ms.Clear(); ui= 0;       ms.Append( ui, 3 );  EXPECT_STREQ(    "000", ms.Buffer() );
            ms.Clear(); ui= 10;      ms.Append( ui );     EXPECT_STREQ(     "10", ms.Buffer() );
            ms.Clear(); ui= 100;     ms.Append( ui, 1 );  EXPECT_STREQ(    "100", ms.Buffer() );
            ms.Clear(); ui= 100;     ms.Append( ui, 3 );  EXPECT_STREQ(    "100", ms.Buffer() );
            ms.Clear(); ui= 100;     ms.Append( ui, 4 );  EXPECT_STREQ(   "0100", ms.Buffer() );
            ms.Clear(); ui= 23;      ms.Append( ui );     EXPECT_STREQ(     "23", ms.Buffer() );
            ms.Clear(); ui= 99;      ms.Append( ui, 5 );  EXPECT_STREQ(  "00099", ms.Buffer() );
            ms.Clear();  i= 49;      ms.Append( i  );     EXPECT_STREQ(     "49", ms.Buffer() );
            ms.Clear();  i= -5;      ms.Append( i, 5 );   EXPECT_STREQ( "-00005", ms.Buffer() );
            ms.Clear();  i= -5324;   ms.Append( i, 2 );   EXPECT_STREQ(  "-5324", ms.Buffer() );
            ms.Clear(); ui= std::numeric_limits<uint32_t>::max();    ms.Append( ui     );   EXPECT_STREQ(    "4294967295",  ms.Buffer() );
            ms.Clear(); ui= std::numeric_limits<uint32_t>::min();    ms.Append( ui     );   EXPECT_STREQ(             "0",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int32_t> ::max();    ms.Append( i      );   EXPECT_STREQ(    "2147483647",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int32_t> ::min();    ms.Append( i      );   EXPECT_STREQ(   "-2147483648",  ms.Buffer() );
            ms.Clear(); ui= std::numeric_limits<uint32_t>::max();    ms.Append( ui, 12 );   EXPECT_STREQ(  "004294967295",  ms.Buffer() );
            ms.Clear(); ui= std::numeric_limits<uint32_t>::min();    ms.Append( ui, 12 );   EXPECT_STREQ(  "000000000000",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int32_t> ::max();    ms.Append( i , 12 );   EXPECT_STREQ(  "002147483647",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int32_t> ::min();    ms.Append( i , 12 );   EXPECT_STREQ( "-002147483648",  ms.Buffer() );

            ms.Clear(); ui= std::numeric_limits<uint64_t>::max();    ms.Append( ui     );   EXPECT_STREQ( "18446744073709551615",  ms.Buffer() );
            ms.Clear(); ui= std::numeric_limits<uint64_t>::min();    ms.Append( ui     );   EXPECT_STREQ(                    "0",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int64_t> ::max();    ms.Append( i      );   EXPECT_STREQ(  "9223372036854775807",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int64_t> ::min();    ms.Append( i      );   EXPECT_STREQ( "-9223372036854775808",  ms.Buffer() );
            ms.Clear();  i= std::numeric_limits<int64_t> ::min() + 75008; ms.Append( i );   EXPECT_STREQ( "-9223372036854700800",  ms.Buffer() );
        }

        // append double
        {
            AString ms;
            double d;

            ms.Clear(); d=     0.0;      ms.Append( d, 0,0 );     EXPECT_STREQ(       "."    , ms.Buffer() );
            ms.Clear(); d=     0.0;      ms.Append( d, 1,0 );     EXPECT_STREQ(      "0."    , ms.Buffer() );
            ms.Clear(); d=     0.0;      ms.Append( d, 0,1 );     EXPECT_STREQ(       ".0"   , ms.Buffer() );
            ms.Clear(); d=     0.0;      ms.Append( d, 1,1 );     EXPECT_STREQ(      "0.0"   , ms.Buffer() );
            ms.Clear(); d=     0.0;      ms.Append( d, 2,2 );     EXPECT_STREQ(     "00.00"  , ms.Buffer() );
            ms.Clear(); d=    10.0;      ms.Append( d, 2,2 );     EXPECT_STREQ(     "10.00"  , ms.Buffer() );
            ms.Clear(); d=    23.37;     ms.Append( d, 2,1 );     EXPECT_STREQ(     "23.4"   , ms.Buffer() );
            ms.Clear(); d=    23.37;     ms.Append( d, 2,3 );     EXPECT_STREQ(     "23.370" , ms.Buffer() );
            ms.Clear(); d=    12.345;    ms.Append( d, 0,3 );     EXPECT_STREQ(     "12.345" , ms.Buffer() );
            ms.Clear(); d= -   5.1;      ms.Append( d, 5,0 );     EXPECT_STREQ( "-00005."    , ms.Buffer() );
            ms.Clear(); d= -   5.1;      ms.Append( d, 5,1 );     EXPECT_STREQ( "-00005.1"   , ms.Buffer() );
            ms.Clear(); d= -  53.24;     ms.Append( d, 2,2 );     EXPECT_STREQ(    "-53.24"  , ms.Buffer() );
            ms.Clear(); d= -   0.2;      ms.Append( d, 1,3 );     EXPECT_STREQ(     "-0.200" , ms.Buffer() );
            ms.Clear(); d= -   0.6;      ms.Append( d, 1,3 );     EXPECT_STREQ(     "-0.600" , ms.Buffer() );
            ms.Clear(); d= -   0.999;    ms.Append( d, 1,3 );     EXPECT_STREQ(     "-0.999" , ms.Buffer() );
            ms.Clear(); d=     0.999;    ms.Append( d, 1,3 );     EXPECT_STREQ(      "0.999" , ms.Buffer() );
            ms.Clear(); d=     0.99;     ms.Append( d, 1,3 );     EXPECT_STREQ(      "0.990" , ms.Buffer() );
            ms.Clear(); d=     0.999;    ms.Append( d, 1,3 );     EXPECT_STREQ(      "0.999" , ms.Buffer() );
            ms.Clear(); d=     0.9999;   ms.Append( d, 1,3 );     EXPECT_STREQ(      "1.000" , ms.Buffer() );
            ms.Clear(); d=     0.99999;  ms.Append( d, 1,3 );     EXPECT_STREQ(      "1.000" , ms.Buffer() );

            d= -3.0;
            double end= 3.0;
            double inc= 0.001;
            int    digits= 5;
            while ( d <= end)
            {
                ms.Clear();
                ms.Append( d, 0, digits );
                double dRes= ::atof( ms.Buffer() );
                EXPECT_NEAR( d, dRes, 0.00000001 );
                d+= inc;
            }
        }
    }

    // append mutable strings
    {
        AString ms;

        // append constant string
        AString t;
        t.Append( "Hallo World" );
        ms.Append(t);

        EXPECT_EQ( ms.Length(), t.Length());
        for ( int i= 0; i < t.Length() ; i++ )
            EXPECT_EQ( ms[i],  t[i]);

        // append part of constant string
        int startIdx= 6;
        int len=      3;
        ms.Append( t, startIdx, len );

        EXPECT_EQ( ms.Length(), t.Length() + len );
        for ( int i= 0; i < len ; i++ )
            EXPECT_EQ( ms[t.Length() + i],  t[ startIdx + i]);

        // append more than available in source string
        ms.Clear();
        ms.Append(t);
        ms.Append ( t, startIdx, t.Length() );
        len= t.Length() - startIdx;

        EXPECT_EQ( ms.Length(), t.Length() + len );
        for ( int i= 0; i < len ; i++ )
            EXPECT_EQ( ms[t.Length() + i],  t[ startIdx + i] );
    }

    // append const char*
    {
        // create mutable string
        AString ms;
        EXPECT_EQ( ms.Length(), 0 );

        // append constant string
        const char* t=    "Hallo World";
        int tLength= strlen(t);
        ms.Append(t);

        EXPECT_EQ( ms.Length(), tLength);
        for ( int i= 0; i < tLength ; i++ )
            EXPECT_EQ( ms[i],  t[i]);

        // append part of constant string
        int startIdx= 6;
        int len=      3;
        ms.Append( t, startIdx, len );

        EXPECT_EQ( ms.Length(), tLength + len );
        for ( int i= 0; i < len ; i++ )
            EXPECT_EQ( ms[tLength + i],  t[ startIdx + i] );

        // append more than available in source string
        ms.Clear();
        ms.Append(t);
        ms.Append ( t, startIdx, tLength );
        len= tLength - startIdx;

        EXPECT_EQ( ms.Length(), tLength + len );
        for ( int i= 0; i < len ; i++ )
            EXPECT_EQ( ms[tLength + i],  t[ startIdx + i] );
    }
}


//---------------------------------------------------------------------------------------------------------
//--- Test Fields
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( Fields )

    AString ms;

    // empty fields
    ms.Clear();
    ms.Field().Field( 3, AString::Align::LEFT,     '#' );    EXPECT_STREQ( ms.Buffer(), "###"           );
    ms.Field().Field( 4, AString::Align::CENTER,   '*' );    EXPECT_STREQ( ms.Buffer(), "###****"       );
    ms.Field().Field( 5, AString::Align::RIGHT,    '+' );    EXPECT_STREQ( ms.Buffer(), "###****+++++"  );

    // field, alignment left
    ms.Clear();
    ms.Field().Append( "A" )        .Field( 5,    AString::Align::LEFT );
    ms.Field().Append( "AB" )       .Field( 5,    AString::Align::LEFT );
    ms.Field().Append( "ABC" )      .Field( 5,    AString::Align::LEFT );
    ms.Field().Append( "ABCD" )     .Field( 5,    AString::Align::LEFT );
    ms.Field().Append( "ABCDE" )    .Field( 5,    AString::Align::LEFT );
    ms.Field().Append( "ABCDEF" )   .Field( 5,    AString::Align::LEFT );
    ms.Field().Append( "ABCDEFG" )  .Field( 5,    AString::Align::LEFT );
    EXPECT_STREQ( ms.Buffer(), "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG" );

    // field, alignment right
    ms.Clear();
    ms.Field().Append( "A" )        .Field( 5,    AString::Align::RIGHT );
    ms.Field().Append( "AB" )       .Field( 5,    AString::Align::RIGHT );
    ms.Field().Append( "ABC" )      .Field( 5 ); // btw: right is default
    ms.Field().Append( "ABCD" )     .Field( 5 );
    ms.Field().Append( "ABCDE" )    .Field( 5 );
    ms.Field().Append( "ABCDEF" )   .Field( 5,    AString::Align::RIGHT );
    ms.Field().Append( "ABCDEFG" )  .Field( 5,    AString::Align::RIGHT );
    EXPECT_STREQ( ms.Buffer(), "    A   AB  ABC ABCDABCDEABCDEFABCDEFG" );

    // field, alignment center
    ms.Clear();
    ms.Field().Append( "A" )        .Field( 5,    AString::Align::CENTER );
    ms.Field().Append( "AB" )       .Field( 5,    AString::Align::CENTER );
    ms.Field().Append( "ABC" )      .Field( 5,    AString::Align::CENTER );
    ms.Field().Append( "ABCD" )     .Field( 5,    AString::Align::CENTER );
    ms.Field().Append( "ABCDE" )    .Field( 5,    AString::Align::CENTER );
    ms.Field().Append( "ABCDEF" )   .Field( 5,    AString::Align::CENTER );
    ms.Field().Append( "ABCDEFG" )  .Field( 5,    AString::Align::CENTER );
    EXPECT_STREQ( ms.Buffer(), "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG" );

    // a nested field
    ms.Clear();
    ms.Append("***");
        int outerFieldStart= ms.Length();
        ms.Append( "OS:" )  .Field().Append( "Linux" ).Field( 10, AString::Align::RIGHT, '-' );
        ms.Append( " Lang:").Field().Append( "en_US" ).Field(  8, AString::Align::RIGHT, '-' );
        ms.Field(35, AString::Align::CENTER, '#', outerFieldStart );
    ms.Append("***");
    EXPECT_STREQ( ms.Buffer(), "***####OS:-----Linux Lang:---en_US####***" );
}


//---------------------------------------------------------------------------------------------------------
//--- Test Capacity
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( CapacityLength )

    // null-allocated
    {
        AString ms( 0 );
        ms.Append(  "" );       EXPECT_TRUE( ms.GetAllocation() > 0 );
    }

    {
        AString ms( 5 );
        ms.Append( 'a' );        EXPECT_EQ  ( ms.GetAllocation(), 5 );
        ms.Append( 'b' );        EXPECT_EQ  ( ms.GetAllocation(), 5 );
        ms.Append( 'c' );        EXPECT_EQ  ( ms.GetAllocation(), 5 );
        ms.Append( 'd' );        EXPECT_EQ  ( ms.GetAllocation(), 5 );
        ms.Append( 'e' );        EXPECT_EQ  ( ms.GetAllocation(), 5 );
        ms.Append( 'x' );        EXPECT_TRUE( ms.GetAllocation() >= 6 );
        EXPECT_STREQ( "abcdex", ms.Buffer() );

        ms.EnsureAllocation( 2000 ); EXPECT_TRUE( ms.GetAllocation() >= 2000 );
    }

    {
        AString   ms;
        int as;
        ms.Append( "0123456789" );           EXPECT_EQ    ( ms.Length(), 10 );    EXPECT_TRUE  ( ms.GetAllocation() >= 10 );

        as= ms.GetAllocation();

        bool oldHaltOnError=    AWXU::HaltOnError;
        bool oldHaltOnWarning=  AWXU::HaltOnWarning;
        AWXU::HaltOnError=
        AWXU::HaltOnWarning=    false;
            PRINT( "A warning should follow" );
            ms.SetLength(20);                    EXPECT_EQ    ( ms.Length(), 10 );    EXPECT_EQ    ( ms.GetAllocation(), as );    EXPECT_STREQ( ms.Buffer(), "0123456789" );

            PRINT( "No (second) warning should follow" );
            ms.SetLength(20);                    EXPECT_EQ    ( ms.Length(), 10 );    EXPECT_EQ    ( ms.GetAllocation(), as );    EXPECT_STREQ( ms.Buffer(), "0123456789" );

            AWXU_ONE_TIME_WARNING_SET( AString, SetLength, true );

            PRINT( "No warning should follow" );
            ms.SetLength(10);                    EXPECT_EQ    ( ms.Length(), 10 );    EXPECT_EQ    ( ms.GetAllocation(), as );    EXPECT_STREQ( ms.Buffer(), "0123456789" );

            PRINT( "A warning should follow" );
            ms.SetLength(11);                    EXPECT_EQ    ( ms.Length(), 10 );    EXPECT_EQ    ( ms.GetAllocation(), as );    EXPECT_STREQ( ms.Buffer(), "0123456789" );

            PRINT( "No (second) warning should follow" );
            ms.SetLength(11);                    EXPECT_EQ    ( ms.Length(), 10 );    EXPECT_EQ    ( ms.GetAllocation(), as );    EXPECT_STREQ( ms.Buffer(), "0123456789" );

        AWXU::HaltOnError=      oldHaltOnError;
        AWXU::HaltOnWarning=    oldHaltOnWarning;

        ms.SetLength(5);                    EXPECT_EQ    ( ms.Length(), 5 );      EXPECT_EQ    ( ms.GetAllocation(), as );    EXPECT_STREQ( ms.Buffer(), "01234" );
        ms.SetAllocation(3);                EXPECT_EQ    ( ms.Length(), 3 );      EXPECT_EQ    ( ms.GetAllocation(), 3  );    EXPECT_STREQ( ms.Buffer(), "012" );
        ms.Append("ABC");                   EXPECT_EQ    ( ms.Length(), 6 );      EXPECT_TRUE  ( ms.GetAllocation() >= 6 );   EXPECT_STREQ( ms.Buffer(), "012ABC" );
    }

    // external buffer
    {
        AString* ms;
        ms= new AString();
        ms->SetExternalBuffer( new char[5], 5, 0, true );
        ms->Append("ABC");                  EXPECT_EQ    ( ms->Length(), 3 );        EXPECT_TRUE ( ms->GetAllocation() == 4 );  EXPECT_STREQ( ms->Buffer(), "ABC" );
        delete ms;

        ms= new AString();
        ms->SetExternalBuffer( new char[5], 5, 0, true );
        ms->Append("ABC");
        ms->Append("ABC");                  EXPECT_EQ    ( ms->Length(), 6 );        EXPECT_TRUE ( ms->GetAllocation() > 4 );  EXPECT_STREQ( ms->Buffer(), "ABCABC" );
        delete ms;

        char stackCA1[5];
        AString sMS1;
        sMS1.SetExternalBuffer( (char*) &stackCA1, 5 );
        sMS1.Append("ABC");                 EXPECT_TRUE ( sMS1.Buffer() == (char*) &stackCA1 );  EXPECT_STREQ( sMS1.Buffer(), "ABC" );

        bool oldHaltOnError=    AWXU::HaltOnError;
        bool oldHaltOnWarning=  AWXU::HaltOnWarning;
        AWXU::HaltOnError=
        AWXU::HaltOnWarning=    false;
            char stackCA2[5];
            AString sMS2;
            sMS2.SetExternalBuffer( (char*) &stackCA2, 5 );
            sMS2.Append("ABC");
            PRINT( "A warning should follow" );
            sMS2.Append("ABC");                 EXPECT_TRUE ( sMS2.Buffer() != (char*) &stackCA2 );  EXPECT_STREQ( sMS2.Buffer(), "ABCABC" );
            #if defined(AWXU_DEBUG)
                AString::AWXU_OTW_ReplaceExternalBuffer= true;
            #endif

            AStringPreAlloc<(size_t) 5> msS;
            const char* orig= msS.Buffer();
            msS.Append("ABC");                 EXPECT_TRUE ( msS.Buffer() == orig );  EXPECT_STREQ( msS.Buffer(), "ABC" );
            PRINT( "A warning should follow" );
            msS.Append("ABC");                 EXPECT_TRUE ( msS.Buffer() != orig );  EXPECT_STREQ( msS.Buffer(), "ABCABC" );
            #if defined(AWXU_DEBUG)
                AString::AWXU_OTW_ReplaceExternalBuffer= true;
            #endif

            AString64 ms64;
            orig= ms64.Buffer();
            ms64.Append("ABC");                EXPECT_TRUE ( ms64.Buffer() == orig ); EXPECT_STREQ( ms64.Buffer(), "ABC" );
            ms64.Clear();
            ms64.Append( '@', 63 );            EXPECT_TRUE ( ms64.Buffer() == orig );
            PRINT( "A warning should follow" );
            ms64.Append( '@' );
            EXPECT_TRUE ( ms64.Buffer() != orig );
            EXPECT_TRUE ( ms64.ReplaceCount("@", "X") == 64 );
            #if defined(AWXU_DEBUG)
                AString::AWXU_OTW_ReplaceExternalBuffer= true;
            #endif
        AWXU::HaltOnError=      oldHaltOnError;
        AWXU::HaltOnWarning=    oldHaltOnWarning;
    }
}


//---------------------------------------------------------------------------------------------------------
//--- Test Tab
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( Tab )

    AString ms;

    // test some bad input
                   ms.Tab(  0, -1,        '@' );        EXPECT_STREQ( "",  ms.Buffer() );
    ms.Clear();    ms.Tab(  0,  0,        '@' );        EXPECT_STREQ( "",  ms.Buffer() );
    ms.Clear();    ms.Tab( -1,  0,        '@' );        EXPECT_STREQ( "",  ms.Buffer() );
    ms.Clear();    ms.Tab( -1,  0,        '@' );        EXPECT_STREQ( "",  ms.Buffer() );
    ms.Clear();    ms.Tab( -1,  -1,       '@' );        EXPECT_STREQ( "",  ms.Buffer() );
    ms.Clear();    ms.Tab( -5,  0,        '@' );        EXPECT_STREQ( "",  ms.Buffer() );
    ms.Clear();    ms.Tab( -5,  -100,     '@' );        EXPECT_STREQ( "",  ms.Buffer() );
    ms.Clear();    ms.Tab(  2,  -101,     '@' );        EXPECT_STREQ( "",  ms.Buffer() );
    ms.Clear();    ms.Tab(  0,  0,        '@' );        EXPECT_STREQ( "",  ms.Buffer() );
    ms.Clear();    ms.Tab(  1,  0,        '@' );        EXPECT_STREQ( "",  ms.Buffer() );
    ms.Clear();    ms.Tab(  1,  1,        '@' );        EXPECT_STREQ( "@", ms.Buffer() );
    ms.Clear();    ms.Tab(  0,  1,        '@' );        EXPECT_STREQ( "@", ms.Buffer() );


    // minpad 0 (not common, default is 1, tab wont move if on tab position)
    ms.Clear();                         ms.Tab( 2, 0,    '@' ).Append( '-' );       EXPECT_STREQ( "-",   ms.Buffer() );
    ms.Clear();    ms.Append( 'x' );    ms.Tab( 2, 0,    '@' ).Append( '-' );       EXPECT_STREQ( "x@-", ms.Buffer() );

    // more standard tabs
    ms.Clear();
    ms.Append( "12" ).Tab( 2 )
      .Append( "1"  ).Tab( 2 )
      .Tab(2)
      .Append( "@" );
    EXPECT_STREQ( "12  1   @", ms.Buffer() );

    ms.Clear();
    ms.Append( "12" ).Tab( 2, 0 )
      .Append( "1"  ).Tab( 2, 0 )
      .Tab(2, 0, 0)
      .Append( "@" );
    EXPECT_STREQ( "121 @", ms.Buffer() );


    ms.Clear();
    ms.Append( "12345" ).Tab( 5 )
      .Append( "1234" ) .Tab( 5 )
      .Append( "123" )  .Tab( 5 )
      .Append( "12" )   .Tab( 5 )
      .Append( "1" )    .Tab( 5 )
                        .Tab( 5 )
      .Append( "@" );
    EXPECT_STREQ( "12345     1234 123  12   1         @", ms.Buffer() );

    ms.Clear();
    ms.Append( "12345" ).Tab( 5, 0 )
      .Append( "1234" ) .Tab( 5, 0 )
      .Append( "123" )  .Tab( 5, 0 )
      .Append( "12" )   .Tab( 5, 0 )
      .Append( "1" )    .Tab( 5, 0 )
                        .Tab( 5, 0 )
      .Append( "@" );
    EXPECT_STREQ( "123451234 123  12   1    @", ms.Buffer() );

    ms.Clear();                        ms.Tab( 0 ).Append( '-' );        EXPECT_STREQ( " -"    , ms.Buffer() );
    ms.Clear();                        ms.Tab( 1 ).Append( '-' );        EXPECT_STREQ( " -"    , ms.Buffer() );
    ms.Clear();                        ms.Tab( 2 ).Append( '-' );        EXPECT_STREQ( "  -"   , ms.Buffer() );
    ms.Clear();                        ms.Tab( 3 ).Append( '-' );        EXPECT_STREQ( "   -"  , ms.Buffer() );
    ms.Clear();    ms.Append( 'x' );   ms.Tab( 1 ).Append( '-' );        EXPECT_STREQ( "x -"   , ms.Buffer() );
    ms.Clear();    ms.Append( 'x' );   ms.Tab( 2 ).Append( '-' );        EXPECT_STREQ( "x -"   , ms.Buffer() );
    ms.Clear();    ms.Append( 'x' );   ms.Tab( 3 ).Append( '-' );        EXPECT_STREQ( "x  -"  , ms.Buffer() );

    // tabs with tab reference set (designed for multi line tabs)
    ms.Clear().Append("ABC").NewLine();
    ms.Append( "12345" ).Tab( 5 )
      .Append( "1234" ) .Tab( 5 )
      .Append( "123" )  .Tab( 5 )
      .Append( "12" )   .Tab( 5 )
      .Append( "1" )    .Tab( 5 )
                        .Tab( 5 )
      .Append( "@" );
    EXPECT_STREQ( AString64("ABC").NewLine().Append( "12345     1234 123  12   1         @" ).Buffer(), ms.Buffer() );

    ms.Clear().Append("ABC").NewLine();
    ms.Append( "12345" ).Tab( 5, 0 )
      .Append( "1234" ) .Tab( 5, 0 )
      .Append( "123" )  .Tab( 5, 0 )
      .Append( "12" )   .Tab( 5, 0 )
      .Append( "1" )    .Tab( 5, 0 )
                        .Tab( 5, 0 )
      .Append( "@" );
    EXPECT_STREQ( AString32("ABC").NewLine().Append( "123451234 123  12   1    @" )        .Buffer(), ms.Buffer() );


}

//---------------------------------------------------------------------------------------------------------
//--- Test SearchReplace
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( SearchAndReplace )

    AString ms;
    int result;

    // search characters
    ms.Clear().Append("abcd abcd");
    {
        result= ms.IndexOf( '@', -5  );   EXPECT_EQ(    -1,  result );
        result= ms.IndexOf( '@'      );   EXPECT_EQ(    -1,  result );
        result= ms.IndexOf( '@', 5   );   EXPECT_EQ(    -1,  result );
        result= ms.IndexOf( '@', 150 );   EXPECT_EQ(    -1,  result );

        result= ms.IndexOf( 'a'      );   EXPECT_EQ(    0,   result );
        result= ms.IndexOf( 'b'      );   EXPECT_EQ(    1,   result );
        result= ms.IndexOf( 'c'      );   EXPECT_EQ(    2,   result );

        result= ms.IndexOf( 'a', 0   );   EXPECT_EQ(    0,   result );
        result= ms.IndexOf( 'b', 0   );   EXPECT_EQ(    1,   result );
        result= ms.IndexOf( 'c', 0   );   EXPECT_EQ(    2,   result );

        result= ms.IndexOf( 'a', 1   );   EXPECT_EQ(    5,   result );
        result= ms.IndexOf( 'b', 1   );   EXPECT_EQ(    1,   result );
        result= ms.IndexOf( 'c', 1   );   EXPECT_EQ(    2,   result );

        result= ms.IndexOf( 'a', 2   );   EXPECT_EQ(    5,   result );
        result= ms.IndexOf( 'b', 2   );   EXPECT_EQ(    6,   result );
        result= ms.IndexOf( 'c', 2   );   EXPECT_EQ(    2,   result );

        result= ms.IndexOf( 'a', 3   );   EXPECT_EQ(    5,   result );
        result= ms.IndexOf( 'b', 3   );   EXPECT_EQ(    6,   result );
        result= ms.IndexOf( 'c', 3   );   EXPECT_EQ(    7,   result );

        result= ms.IndexOf( 'd', 7   );   EXPECT_EQ(    8,   result );
        result= ms.IndexOf( 'd', 8   );   EXPECT_EQ(    8,   result );
        result= ms.IndexOf( 'd', 9   );   EXPECT_EQ(   -1,   result );
    }

    // search nullptr, empty string
    ms.Clear().Append("abcd abcd");
    {
        result= ms.IndexOf( nullptr        );    EXPECT_EQ( result, 0 );
        result= ms.IndexOf( nullptr,    5  );    EXPECT_EQ( result, 5 );
        result= ms.IndexOf( nullptr,   50  );    EXPECT_EQ( result,-1 );
        result= ms.IndexOf( nullptr, -  5  );    EXPECT_EQ( result, 0 );
        result= ms.IndexOf( "",      -  5  );    EXPECT_EQ( result, 0 );
        result= ms.IndexOf( "",         0  );    EXPECT_EQ( result, 0 );
        result= ms.IndexOf( "",         4  );    EXPECT_EQ( result, 4 );
        result= ms.IndexOf( "",       100  );    EXPECT_EQ( result,-1 );
    }

    // search
    ms.Clear().Append("abcd abcd");
    {
        result= ms.IndexOf( "abcd"       );      EXPECT_EQ( result, 0 );
        result= ms.IndexOf( "b"          );      EXPECT_EQ( result, 1 );
        result= ms.IndexOf( " abcd"      );      EXPECT_EQ( result, 4 );
        result= ms.IndexOf( "abcd",     1);      EXPECT_EQ( result, 5 );
        result= ms.IndexOf( "abcd",   - 1);      EXPECT_EQ( result, 0 );
        result= ms.IndexOf( "xyz",    -10);      EXPECT_EQ( result,-1 );
    }

    // ignore case
    ms.Clear().Append( "Hallo A-Worx util" );
    {
        result= ms.IndexOf( "a-worx",   0  ,true ); EXPECT_EQ( result, 6 );
        result= ms.IndexOf( "a-worx",   1  ,true ); EXPECT_EQ( result, 6 );
        result= ms.IndexOf( "a-worx", -10  ,true ); EXPECT_EQ( result, 6 );
        result= ms.IndexOf( "a-worx",   6  ,true ); EXPECT_EQ( result, 6 );
        result= ms.IndexOf( "a-worx",   7  ,true ); EXPECT_EQ( result, -1 );
        result= ms.IndexOf( "a-worx", 100  ,true ); EXPECT_EQ( result, -1 );
        result= ms.IndexOf( "hal",      0  ,true ); EXPECT_EQ( result,  0 );
        result= ms.IndexOf( "hal",      1  ,true ); EXPECT_EQ( result, -1 );
        result= ms.IndexOf( "util",     1  ,true ); EXPECT_EQ( result, 13 );
        result= ms.IndexOf( "UTIL",     5  ,true ); EXPECT_EQ( result, 13 );
        result= ms.IndexOf( "UTIL",    13  ,true ); EXPECT_EQ( result, 13 );
        result= ms.IndexOf( "UTIL",    14  ,true ); EXPECT_EQ( result, -1 );
    }

    // replace nullptr
    ms.Clear().Append("Hello");
    {
        ms.Replace( nullptr,    nullptr );        EXPECT_STREQ( ms.Buffer(), "Hello" );
        ms.Replace( "l",        nullptr );        EXPECT_STREQ( ms.Buffer(), "Heo" );
        ms.Replace( nullptr,    "xx"    );        EXPECT_STREQ( ms.Buffer(), "Heo" );
    }

    // replaceCount nullptr
    ms.Clear().Append("Hello");
    {
        result= ms.ReplaceCount( nullptr,    nullptr );    EXPECT_STREQ( ms.Buffer(), "Hello" );   EXPECT_EQ( 0, result );
        result= ms.ReplaceCount( "l",        nullptr );    EXPECT_STREQ( ms.Buffer(), "Heo" );     EXPECT_EQ( 2, result );
        result= ms.ReplaceCount( nullptr,    "xx"    );    EXPECT_STREQ( ms.Buffer(), "Heo" );     EXPECT_EQ( 0, result );
    }

    // replace
    ms.Clear().Append("Hello W!");
    {
        result= ms.ReplaceCount( "W!",    "world!"  );    EXPECT_STREQ( ms.Buffer(), "Hello world!"     );        EXPECT_EQ( 1, result );
        result= ms.ReplaceCount( " ",    "* *"      );    EXPECT_STREQ( ms.Buffer(), "Hello* *world!"   );        EXPECT_EQ( 1, result );
        result= ms.ReplaceCount( "*",    "#", 0, 0  );    EXPECT_STREQ( ms.Buffer(), "Hello* *world!"   );        EXPECT_EQ( 0, result );
        result= ms.ReplaceCount( "*",    "#", 0, 1  );    EXPECT_STREQ( ms.Buffer(), "Hello# *world!"   );        EXPECT_EQ( 1, result );
        result= ms.ReplaceCount( "*",    "#"        );    EXPECT_STREQ( ms.Buffer(), "Hello# #world!"   );        EXPECT_EQ( 1, result );
        result= ms.ReplaceCount( "#",    "$$$"      );    EXPECT_STREQ( ms.Buffer(), "Hello$$$ $$$world!" );      EXPECT_EQ( 2, result );
        result= ms.ReplaceCount( "$$$",    "*"      );    EXPECT_STREQ( ms.Buffer(), "Hello* *world!"   );        EXPECT_EQ( 2, result );
        result= ms.ReplaceCount( "*",    ""         );    EXPECT_STREQ( ms.Buffer(), "Hello world!"     );        EXPECT_EQ( 2, result );
    }

    // replace one space by two spaces in a string of spaces
    ms.Clear().Append("     ");
    {
        result= ms.ReplaceCount( " ",    "  "  );    EXPECT_STREQ( ms.Buffer(), "          " );        EXPECT_EQ( 5, result );
    }

    // replace ignoreCase
    {
        ms.Clear().Append("ABC"); result= ms.ReplaceCount( "abc",    "xxx",0, 1, false );    EXPECT_STREQ( ms.Buffer(), "ABC" );        EXPECT_EQ( 0, result );
        ms.Clear().Append("ABC"); result= ms.ReplaceCount( "abc",    "xxx",0, 1, true  );    EXPECT_STREQ( ms.Buffer(), "xxx" );        EXPECT_EQ( 1, result );
        ms.Clear().Append("ABC"); result= ms.ReplaceCount( "ABC",    "xxx",0, 1, true  );    EXPECT_STREQ( ms.Buffer(), "xxx" );        EXPECT_EQ( 1, result );

        ms.Clear().Append("abc");         ms.ReplaceCount( "ABC",    "xxx",0, 1, false );    EXPECT_STREQ( ms.Buffer(), "abc" );
        ms.Clear().Append("abc");         ms.ReplaceCount( "ABC",    "xxx",0, 1, true  );    EXPECT_STREQ( ms.Buffer(), "xxx" );
        ms.Clear().Append("abc");         ms.ReplaceCount( "abc",    "xxx",0, 1, true  );    EXPECT_STREQ( ms.Buffer(), "xxx" );
    }

}

//---------------------------------------------------------------------------------------------------------
//--- Test Compare
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( Compare )

    // null string comparison
    char*   nullCString= nullptr;

    AString aString;
    EXPECT_TRUE( aString.CompareTo( nullCString) == 0 );
    EXPECT_TRUE( aString.Equals( nullCString) );
    EXPECT_TRUE( aString == nullptr );

    aString= "";
    EXPECT_TRUE( aString.CompareTo( nullCString) != 0 );
    EXPECT_TRUE( !aString.Equals( nullCString) );
    EXPECT_TRUE( aString != nullptr );

    aString= nullCString;
    EXPECT_TRUE( aString.CompareTo( nullCString) == 0 );
    EXPECT_TRUE( aString.Equals( nullCString) );
    EXPECT_TRUE( aString == nullptr );


    // compare/region
    AString ms;
    int result;
    int resultX;
    int intMaxValue= std::numeric_limits<int>::max();
    string t; t= "abcde";
    ms.Append( t );
    result= ms.CompareTo( t      );                          resultX= t.compare( t );                            EXPECT_EQ( resultX,    result );
    result= ms.CompareTo( string(t).append("x")       );     resultX= t.compare( string(t).append("x") );        EXPECT_EQ( resultX,    result );
    result= ms.CompareTo( t.substr (0, t.size() -1 )  );     resultX= t.compare( t.substr(0, t.size() -1 ) );    EXPECT_EQ( resultX,    result );
    result= ms.CompareTo( "pad" + t,  false, 3        );        EXPECT_EQ(  0,     result );
    result= ms.CompareTo( "pad" + t,  false, 3, 2     );        EXPECT_EQ(  1,     result );
    result= ms.CompareTo( "pad" + t,  false, 3, 100, 0, 4 );    EXPECT_EQ( -1,     result );
    result= ms.CompareTo( "pad" + t,  false, 3, 100, 0, 5 );    EXPECT_EQ(  0,     result );
    result= ms.CompareTo( t, false, 2,2,   2,2      );          EXPECT_EQ(  0,     result );
    result= ms.CompareTo( t, false, 2,2,   2,1      );          EXPECT_EQ( -1,     result );
    result= ms.CompareTo( t, false, 2,2,   2,3      );          EXPECT_EQ(  1,     result );

    result= ms.CompareTo( t, false, -2,5,   -2, 5 );                           EXPECT_EQ( 0,   result );
    result= ms.CompareTo( t, false,  2, intMaxValue,    2, intMaxValue );      EXPECT_EQ( 0,   result );
    result= ms.CompareTo( t, false, -2, intMaxValue,   -2, intMaxValue );      EXPECT_EQ( 0,   result );
    result= ms.CompareTo( t, false, -2, 100,           -2, 99 );               EXPECT_EQ( 0,   result );
    result= ms.CompareTo( t, false, -2, 5,             -2, intMaxValue );      EXPECT_EQ( 1,   result );
    result= ms.CompareTo( t, false, -2, intMaxValue,   -2, 5 );                EXPECT_EQ( -1,  result );

    // greater/smaller strings
    int scRes;
    string greater=     "x";
    string greater2= "abcdef";
    string smaller=  "aaa";
    string smaller2= "abcd";
    result= ms.CompareTo( greater  );   scRes= t.compare( greater  );    EXPECT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) || (result>0 && scRes>0)   );
    result= ms.CompareTo( greater2 );   scRes= t.compare( greater2 );    EXPECT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) || (result>0 && scRes>0)   );
    result= ms.CompareTo( smaller  );   scRes= t.compare( smaller  );    EXPECT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) || (result>0 && scRes>0)   );
    result= ms.CompareTo( smaller2 );   scRes= t.compare( smaller2 );    EXPECT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) || (result>0 && scRes>0)   );

    // ignore case
    string ABCDE= "ABCDE";
    result= ms.CompareTo( ABCDE );                        EXPECT_TRUE( result >  0 );
    result= ms.CompareTo( ABCDE, false );                 EXPECT_TRUE( result >  0 );
    result= ms.CompareTo( ABCDE, true  );                 EXPECT_TRUE( result == 0 );
    result= ms.CompareTo( ABCDE, false, 2,2,   2,2  );    EXPECT_TRUE( result >  0 );
    result= ms.CompareTo( ABCDE, true,  2,2,   2,2  );    EXPECT_TRUE( result == 0 );

    // we do just a very little testing with StringBuilder and AString parameter version of this function, as
    // the code differences are very small
    const char* cp= t.c_str(); //new StringBuilder(); tSB.Append( t );
    result= ms.CompareTo( cp      );                              EXPECT_EQ( 0,   result );
    result= ms.CompareTo( cp, false, -5, 100, -10, 100      );    EXPECT_EQ( 0,   result );
    result= ms.CompareTo( cp, false,  2,   3,   2,   3      );    EXPECT_EQ( 0,   result );

    AString tMS( t );
    result= ms.CompareTo( tMS      );                             EXPECT_EQ( 0,   result );
    result= ms.CompareTo( tMS, false, -5, 100, -10, 100      );   EXPECT_EQ( 0,   result );
    result= ms.CompareTo( tMS, false,  2,   3,   2,   3      );   EXPECT_EQ( 0,   result );

    // different ranges
    string r1=   "*ABCDEF*";
    string r2= "##*ABCDEF*##";
    ms.Clear().Append( r1 );
    result= ms.CompareTo( r2, false, 2,8          );              EXPECT_EQ( 0,   result );
    result= ms.CompareTo( r2, false, 3,6,   1,6      );           EXPECT_EQ( 0,   result );

    // startsWith/Endswith/ContainsAt
    string sub1=  "ABC";
    string sub2=  "abc";
    string s1=    "ABCDEF";
    string s2=    "123ABC";
    string s3=    "##12ABC21##";
    string s4=    "AB";
    bool bRes;
    ms.Clear().Append( s1 );    bRes= ms.StartsWith( sub1 );              EXPECT_EQ( true,    bRes );
                                bRes= ms.StartsWith( sub2 );              EXPECT_EQ( false,   bRes );
    ms.Clear().Append( s2 );    bRes= ms.EndsWith  ( sub1 );              EXPECT_EQ( true,    bRes );
                                bRes= ms.EndsWith  ( sub2 );              EXPECT_EQ( false,   bRes );
    ms.Clear().Append( s3 );    bRes= ms.ContainsAt( sub1, 4 );           EXPECT_EQ( true,    bRes );
                                bRes= ms.ContainsAt( sub2, 4 );           EXPECT_EQ( false,   bRes );
                                bRes= ms.ContainsAt( sub2, 4, true );     EXPECT_EQ( true,    bRes );
    ms.Clear().Append( s4 );    bRes= ms.ContainsAt( sub1, 4 );           EXPECT_EQ( false,   bRes );
                                bRes= ms.ContainsAt( sub2, 4 );           EXPECT_EQ( false,   bRes );
    ms.Clear().Append( s4 );    bRes= ms.ContainsAt( sub1, 0 );           EXPECT_EQ( false,   bRes );
                                bRes= ms.ContainsAt( sub2, 0, true );     EXPECT_EQ( false,   bRes );

    ms.Clear().Append( "Hallo A-Worx util" );

    EXPECT_TRUE( ms.StartsWith( "Hallo A-Worx util",  true ) == true  );
    EXPECT_TRUE( ms.EndsWith  ( "Hallo A-Worx util",  true ) == true  );
    EXPECT_TRUE( ms.StartsWith( "Hallo A-Worx utilx", true ) == false );
    EXPECT_TRUE( ms.EndsWith  ( "xHallo A-Worx util", true ) == false );
    EXPECT_TRUE( ms.StartsWith( "haLLO",              true ) == true  );
    EXPECT_TRUE( ms.StartsWith( "HaLLO",              true ) == true  );
    EXPECT_TRUE( ms.EndsWith  ( "haLLO",              true ) == false );
    EXPECT_TRUE( ms.StartsWith( "UTIL" ,              true ) == false );
    EXPECT_TRUE( ms.EndsWith  ( "UTIL" ,              true ) == true  );
    EXPECT_TRUE( ms.EndsWith  ( "utIl" ,              true ) == true  );


    // contains with empty/null strings
    ms.Clear();                 bRes= ms.ContainsAt( (char*)    nullptr, -1 );    EXPECT_EQ( false,    bRes );
                                bRes= ms.ContainsAt( (char*)    nullptr, 0 );     EXPECT_EQ( true,     bRes );
                                bRes= ms.ContainsAt( (char*)    nullptr, 1 );     EXPECT_EQ( false,    bRes );

    ms.Clear();                 bRes= ms.ContainsAt( (AString*) nullptr, -1 );    EXPECT_EQ( false,    bRes );
                                bRes= ms.ContainsAt( (AString*) nullptr, 0 );     EXPECT_EQ( true,     bRes );
                                bRes= ms.ContainsAt( (AString*) nullptr, 1 );     EXPECT_EQ( false,    bRes );

    ms.Clear();                 bRes= ms.ContainsAt( (string*)  nullptr, -1 );    EXPECT_EQ( false,    bRes );
                                bRes= ms.ContainsAt( (string*)  nullptr, 0 );     EXPECT_EQ( true,     bRes );
                                bRes= ms.ContainsAt( (string*)  nullptr, 1 );     EXPECT_EQ( false,    bRes );

    ms.Clear().Append(sub1);    bRes= ms.ContainsAt( "", -1 );                    EXPECT_EQ( false,    bRes );
                                bRes= ms.ContainsAt( "", 0 );                     EXPECT_EQ( true,     bRes );
                                bRes= ms.ContainsAt( "", 1 );                     EXPECT_EQ( true,     bRes );
                                bRes= ms.ContainsAt( "", 100 );                   EXPECT_EQ( false,    bRes );

    // equals String
    ms.Clear().Append( "" );    bRes= ms.Equals( (string*) nullptr );             EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( string("")   );                  EXPECT_EQ( true,     bRes );
                                bRes= ms.Equals( string("a")  );                  EXPECT_EQ( false,    bRes );

    ms.Clear().Append( "AB" );  bRes= ms.Equals( (string*)nullptr );              EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( string(""   ));                  EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( string("ab" ));                  EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( string("A"  ));                  EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( string("B"  ));                  EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( string("AB" ));                  EXPECT_EQ( true,     bRes );
                                bRes= ms.Equals( string("AB" ));                  EXPECT_EQ( true,     bRes );

    // equals AString
    ms.Clear().Append( "" );    bRes= ms.Equals( (AString*) nullptr);             EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( AString(""  ));                  EXPECT_EQ( true,     bRes );
                                bRes= ms.Equals( AString("a" ));                  EXPECT_EQ( false,    bRes );

    ms.Clear().Append( "AB" );  bRes= ms.Equals( (AString*) nullptr);             EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( AString(""  ));                  EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( AString("ab"));                  EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( AString("A" ));                  EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( AString("B" ));                  EXPECT_EQ( false,    bRes );
                                bRes= ms.Equals( AString("AB"));                  EXPECT_EQ( true,     bRes );
                                bRes= ms.Equals( AString("AB"));                  EXPECT_EQ( true,     bRes );
}

//---------------------------------------------------------------------------------------------------------
//--- Test ConvertCase
//---------------------------------------------------------------------------------------------------------
A_TEST_METHOD( ConvertCase )

    AString ms;

    {
        // test all characters in the 16 bit range
        int testCharRangeStart= (int) 1;
        int testCharRangeEnd=    (int) 255;

        string sb;
        for ( int i= testCharRangeStart; i <= testCharRangeEnd ; i++ )
            sb.append( 1, (char) i );

        string tUpper= sb;    transform( tUpper.begin(), tUpper.end(), tUpper.begin(), ::toupper );
        string tLower= sb;    transform( tLower.begin(), tLower.end(), tLower.begin(), ::tolower );

        ms.Clear().Append( sb ).ConvertCase( false );            EXPECT_STREQ( tLower.c_str(), ms.Buffer() );
        ms.Clear().Append( sb ).ConvertCase( true  );            EXPECT_STREQ( tUpper.c_str(), ms.Buffer() );
    }

    // test substring conversion
    {
        const char* t= "AAAbbb";
        ms.Clear().Append( t ).ConvertCase( false,  0,  2 );        EXPECT_STREQ( ms.Buffer(), "aaAbbb" );
        ms.Clear().Append( t ).ConvertCase( false, -2,  3 );        EXPECT_STREQ( ms.Buffer(), "aAAbbb" );
        ms.Clear().Append( t ).ConvertCase( false, -2     );        EXPECT_STREQ( ms.Buffer(), "aaabbb" );
        ms.Clear().Append( t ).ConvertCase( true,   3,  2 );        EXPECT_STREQ( ms.Buffer(), "AAABBb" );
        ms.Clear().Append( t ).ConvertCase( true,  -2,  6 );        EXPECT_STREQ( ms.Buffer(), "AAABbb" );
        ms.Clear().Append( t ).ConvertCase( true,  -2     );        EXPECT_STREQ( ms.Buffer(), "AAABBB" );
    }
}


A_TEST_CLASS_END

}; //namespace
