// #################################################################################################
//  aworx - Unit Tests
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
#include "alox/alox.hpp"

#define TESTCLASSNAME       CPP_ALib_Strings_AString
#include "aworx_unittests.hpp"
#include "alib/compatibility/std_string.hpp"
#include "alib/compatibility/std_iostream.hpp"

#include <iostream>
#include <sstream>

#include <clocale>

// Windows.h might bring in max/min macros
#if defined( max )
    #undef max
    #undef min
#endif


// For code compatibility with ALox Java/C++
// We have to use underscore as the start of the name and for this have to disable a compiler
// warning. But this is a local code (cpp file) anyhow.
#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif

    #define _NC _<false>

#if defined(__clang__)
    #pragma clang diagnostic pop
#endif

using namespace std;
using namespace aworx;

namespace ut_aworx {


UT_CLASS()


//--------------------------------------------------------------------------------------------------
//--- Test Constructors
//--------------------------------------------------------------------------------------------------
UT_METHOD( Constructors )
{
    UT_INIT();

    AString* ms;
    char*     csNull= nullptr;
               ms= new AString();                        UT_EQ    ( 0 , ms->Capacity()   );    UT_EQ( ms->Length(), 0 );
    delete ms; ms= new AString( 0 );                     UT_EQ    ( 0 , ms->Capacity()   );    UT_EQ( ms->Length(), 0 );
    delete ms; ms= new AString( csNull );                UT_EQ    ( 0 , ms->Capacity()   );    UT_EQ( ms->Length(), 0 );
    delete ms; ms= new AString( "" );                    UT_TRUE  ( ms->Capacity() >  0 );    UT_EQ( ms->Length(), 0 );
    delete ms; ms= new AString( 25 );                    UT_TRUE  ( ms->Capacity() >  0 );    UT_EQ( ms->Length(), 0 );
    delete ms; ms= new AString( "Test" );                UT_TRUE  ( ms->Capacity() >= 4 );    UT_EQ( ms->Length(), 4 );

    AString tNullString;
    delete ms; ms= new AString( tNullString, 1,     0 );     UT_TRUE  ( ms->Length() == 0 );  UT_TRUE  ( ms->IsNull() );
    delete ms; ms= new AString( tNullString, -1000, 0 );     UT_TRUE  ( ms->Length() == 0 );  UT_TRUE  ( ms->IsNull() );
    delete ms; ms= new AString( tNullString, -1000, 1 );     UT_TRUE  ( ms->Length() == 0 );  UT_TRUE  ( ms->IsNull() );
    delete ms; ms= new AString( tNullString, -100,  1000);   UT_TRUE  ( ms->Length() == 0 );  UT_TRUE  ( ms->IsNull() );

    AString tASEmpty("");
    delete ms; ms= new AString( tASEmpty, 1,     0 );    UT_TRUE  ( ms->Length()     == 0 );  UT_TRUE  ( ms->Capacity() > 0 );
    delete ms; ms= new AString( tASEmpty, -1000, 0 );    UT_TRUE  ( ms->Length()     == 0 );  UT_TRUE  ( ms->Capacity() > 0 );
    delete ms; ms= new AString( tASEmpty, -1000, 1 );    UT_TRUE  ( ms->Length()     == 0 );  UT_TRUE  ( ms->Capacity() > 0 );
    delete ms; ms= new AString( tASEmpty, -100,  1000);  UT_TRUE  ( ms->Length()     == 0 );  UT_TRUE  ( ms->Capacity() > 0 );

    AString tAS( "0123456789" );
    delete ms; ms= new AString( tAS, 5);                 UT_TRUE  ( ms->Capacity() >=   5 && ms->Length() ==  5 );    UT_EQ( "56789"       , *ms);
    delete ms; ms= new AString( tAS, 5, 100);            UT_TRUE  ( ms->Capacity() >=   5 && ms->Length() ==  5 );    UT_EQ( "56789"       , *ms);
    delete ms; ms= new AString( tAS, -5);                UT_TRUE  ( ms->Capacity() >=  10 && ms->Length() == 10 );    UT_EQ( "0123456789"  , *ms);
    delete ms; ms= new AString( tAS, -5, 3);             UT_TRUE  ( ms->Capacity() >    0 && ms->Length() ==  0 );    UT_EQ( ""            , *ms);
    delete ms; ms= new AString( tAS, 50, 3);             UT_TRUE  ( ms->Capacity() >    0 && ms->Length() ==  0 );    UT_EQ( ""            , *ms);
    delete ms; ms= new AString( tAS, 10, 3);             UT_TRUE  ( ms->Capacity() >    0 && ms->Length() ==  0 );    UT_EQ( ""            , *ms);
    delete ms; ms= new AString( tAS, -5, 10);            UT_TRUE  ( ms->Capacity() >=   5 && ms->Length() ==  5 );    UT_EQ( "01234"       , *ms);
    delete ms; ms= new AString( tAS, -5, 100);           UT_TRUE  ( ms->Capacity() >=  10 && ms->Length() == 10 );    UT_EQ( "0123456789"  , *ms);

    string tS("0123456789");
    delete ms; ms= new AString( "" );                    UT_TRUE  ( ms->Length() == 0 );    UT_TRUE    ( ms->Capacity() > 0 );
    delete ms; ms= new AString( "", 1,     0 );          UT_TRUE  ( ms->Length() == 0 );    UT_TRUE    ( ms->Capacity() > 0 );
    delete ms; ms= new AString( "", -1000, 0 );          UT_TRUE  ( ms->Length() == 0 );    UT_TRUE    ( ms->Capacity() > 0 );
    delete ms; ms= new AString( "", -1000, 1 );          UT_TRUE  ( ms->Length() == 0 );    UT_TRUE    ( ms->Capacity() > 0 );
    delete ms; ms= new AString( "", -100,  1000);        UT_TRUE  ( ms->Length() == 0 );    UT_TRUE    ( ms->Capacity() > 0 );
    delete ms; ms= new AString( tS );                    UT_TRUE  ( ms->Capacity() >=  10 && ms->Length() == 10 );
                                                         UT_EQ( "0123456789"  , *ms );
    delete ms; ms= new AString( tS, 5);                  UT_TRUE  ( ms->Capacity() >=  5  && ms->Length() == 5 );
                                                         UT_EQ( "56789"       , *ms );
    delete ms; ms= new AString( tS, 5, 100);             UT_TRUE  ( ms->Capacity() >=  5  && ms->Length() == 5 );
                                                         UT_EQ( "56789"       ,*ms );
    delete ms; ms= new AString( tS, -5);                 UT_TRUE  ( ms->Capacity() >=  10 && ms->Length() == 10 );
                                                         UT_EQ( "0123456789"  , *ms );
    delete ms; ms= new AString( tS, -5, 10);             UT_TRUE  ( ms->Capacity() >=  5  && ms->Length() == 5 );
                                                         UT_EQ( "01234"       , *ms );
    delete ms; ms= new AString( tS, -5, 100);            UT_TRUE  ( ms->Capacity() >=  10 && ms->Length() == 10 );
                                                         UT_EQ( "0123456789"  , *ms );
    const char* tSBEmpty= "";
    delete ms; ms= new AString( tSBEmpty );              UT_TRUE  ( ms->Length() == 0 );
    delete ms; ms= new AString( tSBEmpty, 1,     0 );    UT_TRUE  ( ms->Length() == 0 );
    delete ms; ms= new AString( tSBEmpty, -1000, 0 );    UT_TRUE  ( ms->Length() == 0 );
    delete ms; ms= new AString( tSBEmpty, -1000, 1 );    UT_TRUE  ( ms->Length() == 0 );
    delete ms; ms= new AString( tSBEmpty, -100,  1000);  UT_TRUE  ( ms->Length() == 0 );

    const char*  tSB= "0123456789";
    delete ms; ms= new AString( tSB );                   UT_TRUE  ( ms->Capacity() >=  10 && ms->Length() == 10 ); UT_EQ( "0123456789"   , *ms );
    delete ms; ms= new AString( tSB, 5);                 UT_TRUE  ( ms->Capacity() >=  5  && ms->Length() == 5  ); UT_EQ( "56789"        , *ms );
    delete ms; ms= new AString( tSB, 5, 100);            UT_TRUE  ( ms->Capacity() >=  5  && ms->Length() == 5  ); UT_EQ( "56789"        , *ms );
    delete ms; ms= new AString( tSB, -5);                UT_TRUE  ( ms->Capacity() >=  10 && ms->Length() == 10 ); UT_EQ( "0123456789"   , *ms );
    delete ms; ms= new AString( tSB, -5, 10);            UT_TRUE  ( ms->Capacity() >=  5  && ms->Length() == 5  ); UT_EQ( "01234"        , *ms );
    delete ms; ms= new AString( tSB, -5, 100);           UT_TRUE  ( ms->Capacity() >=  10 && ms->Length() == 10 );
    delete ms;
}


//--------------------------------------------------------------------------------------------------
//--- Test IsNull
//--------------------------------------------------------------------------------------------------
UT_METHOD( IsNull )
{
    UT_INIT();

    AString ms;          UT_TRUE( ms.IsNull()    ); UT_TRUE(  ms.IsNull() );  UT_TRUE( !ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
    ms= "";              UT_TRUE( ms.IsNotNull() ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
    ms= "x";             UT_TRUE( ms.IsNotNull() ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE( !ms.IsEmpty() );  UT_TRUE(  ms.IsNotEmpty() );

    ms= static_cast<char*>( nullptr);
                         UT_TRUE( ms.IsNull()    ); UT_TRUE(  ms.IsNull() );  UT_TRUE( !ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
    ms._( "");           UT_TRUE( ms.IsNotNull() ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
    ms._( "xx");         UT_TRUE( ms.IsNotNull() ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE( !ms.IsEmpty() );  UT_TRUE(  ms.IsNotEmpty() );

    ms.SetNull();        UT_TRUE( ms.IsNull()    ); UT_TRUE(  ms.IsNull() );  UT_TRUE( !ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
    ms.SetBuffer(5);     UT_TRUE( ms.IsNotNull() ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );

    ms.SetNull();        UT_TRUE( ms.IsNull()    ); UT_TRUE(  ms.IsNull() );  UT_TRUE( !ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
    ms= "";              UT_TRUE( ms.IsNotNull() ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );

    ms.SetNull();        UT_TRUE( ms.IsNull()    ); UT_TRUE(  ms.IsNull() );  UT_TRUE( !ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
    ms= "abc";           UT_TRUE( ms.IsNotNull() ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE( !ms.IsEmpty() );  UT_TRUE(  ms.IsNotEmpty() );
}

//--------------------------------------------------------------------------------------------------
//--- Test FirstBackCharAt
//--------------------------------------------------------------------------------------------------
UT_METHOD( CharAt )
{
    UT_INIT();

    AString ms;
    UT_EQ(  ms.CharAtStart       ()    ,    '\0' );
    UT_EQ(  ms.CharAtEnd         ()    ,    '\0' );
    UT_EQ(  ms.CharAt            ( -1 ),    '\0' );
    UT_EQ(  ms.CharAt            (  0 ),    '\0' );
    UT_EQ(  ms.CharAt            (  1 ),    '\0' );

    ms.Clear()._('A');

    UT_EQ(  ms.CharAtStart       ()    ,    'A'  );
    UT_EQ(  ms.CharAtStart<false>()    ,    'A'  );
    UT_EQ(  ms.CharAtEnd         ()    ,    'A'  );
    UT_EQ(  ms.CharAtEnd<false>  ()    ,    'A'  );
    UT_EQ(  ms.CharAt            ( -1 ),    '\0' );
    UT_EQ(  ms.CharAt            (  0 ),    'A'  );
    UT_EQ(  ms.CharAt            (  1 ),    '\0' );
    UT_EQ(  ms.CharAt<false>     (  0 ),    'A'  );

    UT_EQ(  ms                   [  0 ],    'A'  );

    ms.Clear()._("ABC");

    UT_EQ(  ms.CharAtStart       ()    ,    'A'  );
    UT_EQ(  ms.CharAtStart<false>()    ,    'A'  );
    UT_EQ(  ms.CharAtEnd         ()    ,    'C'  );
    UT_EQ(  ms.CharAtEnd<false>  ()    ,    'C'  );
    UT_EQ(  ms.CharAt            ( -1 ),    '\0' );
    UT_EQ(  ms.CharAt            (  0 ),    'A'  );
    UT_EQ(  ms.CharAt            (  1 ),    'B'  );
    UT_EQ(  ms.CharAt            (  2 ),    'C'  );
    UT_EQ(  ms.CharAt            (  3 ),    '\0' );

    UT_EQ(  ms.CharAt<false>     (  0 ),    'A'  );
    UT_EQ(  ms.CharAt<false>     (  1 ),    'B'  );
    UT_EQ(  ms.CharAt<false>     (  2 ),    'C'  );

    UT_EQ(  ms                   [  0 ],    'A'  );
    UT_EQ(  ms                   [  1 ],    'B'  );
    UT_EQ(  ms                   [  2 ],    'C'  );

    ms.Clear()._("ABC");
    ms.SetCharAt( -1, '@' );    UT_EQ( "ABC",   ms );
    ms.SetCharAt(  0, 'X' );    UT_EQ( "XBC",   ms );
    ms.SetCharAt(  1, 'Y' );    UT_EQ( "XYC",   ms );
    ms.SetCharAt(  2, 'Z' );    UT_EQ( "XYZ",   ms );
    ms.SetCharAt(  3, '$' );    UT_EQ( "XYZ",   ms );
}


//--------------------------------------------------------------------------------------------------
//--- Test DeleteInsert
//--------------------------------------------------------------------------------------------------
UT_METHOD( DeleteInsertFillReplace )
{
    UT_INIT();

    AString ms;
    // delete
    {
        ms.Clear()._("0123456789");   ms.Delete                 (  5           );      UT_EQ( "01234",        ms );
        ms.Clear()._("0123456789");   ms.Delete                 (  5,      0   );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.Delete                 (  5,     -1   );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.Delete                 (  5,      1   );      UT_EQ( "012346789",    ms );
        ms.Clear()._("0123456789");   ms.Delete                 (  5,    100   );      UT_EQ( "01234",        ms );
        ms.Clear()._("0123456789");   ms.Delete                 (  -5,     10  );      UT_EQ( "56789",        ms );

        ms.Clear()._("0123456789");   ms.Delete<false>          (  5,    5     );      UT_EQ( "01234",        ms );
        ms.Clear()._("0123456789");   ms.Delete<false>          (  0,    5     );      UT_EQ( "56789",        ms );
        ms.Clear()._("0123456789");   ms.Delete<false>          (  0,    1     );      UT_EQ( "123456789",    ms );
        ms.Clear()._("0123456789");   ms.Delete<false>          (  9,    1     );      UT_EQ( "012345678",    ms );

        ms.Clear()._("0123456789");   ms.DeleteStart            (  -2          );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart            (  -1          );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart            (   0          );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart            (   1          );      UT_EQ(  "123456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart            (   2          );      UT_EQ(   "23456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart            (   9          );      UT_EQ(          "9",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart            (  10          );      UT_EQ(           "",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart            (  11          );      UT_EQ(           "",   ms );

        ms.Clear()._("0123456789");   ms.DeleteStart<false>     (   0          );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart<false>     (   1          );      UT_EQ(  "123456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart<false>     (   2          );      UT_EQ(   "23456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart<false>     (   9          );      UT_EQ(          "9",   ms );
        ms.Clear()._("0123456789");   ms.DeleteStart<false>     (  10          );      UT_EQ(           "",   ms );

        ms.Clear()._("0123456789");   ms.DeleteEnd              (  -2          );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd              (  -1          );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd              (   0          );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd              (   1          );      UT_EQ( "012345678" ,   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd              (   2          );      UT_EQ( "01234567"  ,   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd              (   9          );      UT_EQ( "0"         ,   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd              (  10          );      UT_EQ( ""          ,   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd              (  11          );      UT_EQ( ""          ,   ms );

        ms.Clear()._("0123456789");   ms.DeleteEnd <false>      (   0          );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd <false>      (   1          );      UT_EQ( "012345678" ,   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd <false>      (   2          );      UT_EQ( "01234567"  ,   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd <false>      (   9          );      UT_EQ( "0"         ,   ms );
        ms.Clear()._("0123456789");   ms.DeleteEnd <false>      (  10          );      UT_EQ( ""          ,   ms );
    }

    // InsertChars
    {
        ms.Clear()._("0123456789");   ms.InsertChars            ( ' ',  1,  -1 );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.InsertChars            ( ' ',  1,  20 );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.InsertChars            ( ' ',  0,   0 );      UT_EQ( "0123456789",   ms );

        ms.Clear()._("0123456789");   ms.InsertChars            ( ' ',  1,   0 );      UT_EQ( " 0123456789",  ms );
        ms.Clear()._("0123456789");   ms.InsertChars            ( ' ',  1,   1 );      UT_EQ( "0 123456789",  ms );
        ms.Clear()._("0123456789");   ms.InsertChars            ( ' ',  2,   0 );      UT_EQ( "  0123456789", ms );
        ms.Clear()._("0123456789");   ms.InsertChars            ( ' ',  2,   1 );      UT_EQ( "0  123456789", ms );

        ms.Clear()._("0123456789");   ms.InsertChars            ( ' ',  1,  11 );      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.InsertChars            ( ' ',  1,  10 );      UT_EQ( "0123456789 ",  ms );
        ms.Clear()._("0123456789");   ms.InsertChars            ( '@',  3,   5 );      UT_EQ( "01234@@@56789",ms );
    }

    // InsertAt
    {
        ms.Clear()._("0123456789");   ms.InsertAt               ( "TST",  -2 );        UT_EQ( "0123456789",    ms );
        ms.Clear()._("0123456789");   ms.InsertAt               ( "TST",  -1 );        UT_EQ( "0123456789",    ms );
        ms.Clear()._("0123456789");   ms.InsertAt               ( "TST",   0 );        UT_EQ( "TST0123456789", ms );
        ms.Clear()._("0123456789");   ms.InsertAt               ( "TST",   1 );        UT_EQ( "0TST123456789", ms );
        ms.Clear()._("0123456789");   ms.InsertAt               ( "TST",   8 );        UT_EQ( "01234567TST89", ms );
        ms.Clear()._("0123456789");   ms.InsertAt               ( "TST",   9 );        UT_EQ( "012345678TST9", ms );
        ms.Clear()._("0123456789");   ms.InsertAt               ( "TST",  10 );        UT_EQ( "0123456789TST", ms );
        ms.Clear()._("0123456789");   ms.InsertAt               ( "TST",  11 );        UT_EQ( "0123456789",    ms );
        ms.Clear()._("0123456789");   ms.InsertAt               ( "TST",  12 );        UT_EQ( "0123456789",    ms );

        ms.Clear()._("0123456789");   ms.InsertAt<false>        ( "TST",   0 );        UT_EQ( "TST0123456789", ms );
        ms.Clear()._("0123456789");   ms.InsertAt<false>        ( "TST",   1 );        UT_EQ( "0TST123456789", ms );
        ms.Clear()._("0123456789");   ms.InsertAt<false>        ( "TST",   8 );        UT_EQ( "01234567TST89", ms );
        ms.Clear()._("0123456789");   ms.InsertAt<false>        ( "TST",   9 );        UT_EQ( "012345678TST9", ms );
        ms.Clear()._("0123456789");   ms.InsertAt<false>        ( "TST",  10 );        UT_EQ( "0123456789TST", ms );

    }

    // ReplaceSubstring
    {
        String r= "ABC";
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r,   0,  10)  ;      UT_EQ( "ABC",          ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r, -10, 100)  ;      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r, -10,  5 )  ;      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r, -10, 10 )  ;      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r, -10, 11 )  ;      UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r,   0,  1 )  ;      UT_EQ( "ABC123456789", ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r,   0,  2 )  ;      UT_EQ( "ABC23456789",  ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r,   1,  1 )  ;      UT_EQ( "0ABC23456789", ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r,   1,  2 )  ;      UT_EQ( "0ABC3456789",  ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r,   8,  1 )  ;      UT_EQ( "01234567ABC9", ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r,   8,  2 )  ;      UT_EQ( "01234567ABC",  ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring       ( r,   8,  3 )  ;      UT_EQ( "0123456789",   ms );

        ms.Clear()._("0123456789");   ms.ReplaceSubstring<false>( r,   0,  1 )  ;      UT_EQ( "ABC123456789", ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring<false>( r,   0,  2 )  ;      UT_EQ( "ABC23456789",  ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring<false>( r,   1,  1 )  ;      UT_EQ( "0ABC23456789", ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring<false>( r,   1,  2 )  ;      UT_EQ( "0ABC3456789",  ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring<false>( r,   8,  1 )  ;      UT_EQ( "01234567ABC9", ms );
        ms.Clear()._("0123456789");   ms.ReplaceSubstring<false>( r,   8,  2 )  ;      UT_EQ( "01234567ABC",  ms );
    }

    // ReplaceRegion
    {
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@',   0,  10)  ;    UT_EQ( "@@@@@@@@@@",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@', -10, 100)  ;    UT_EQ( "@@@@@@@@@@",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@', -10,  5 )  ;    UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@', -10, 10 )  ;    UT_EQ( "0123456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@', -10, 11 )  ;    UT_EQ( "@123456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@',   0,  1 )  ;    UT_EQ( "@123456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@',   0,  2 )  ;    UT_EQ( "@@23456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@',   1,  1 )  ;    UT_EQ( "0@23456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@',   1,  2 )  ;    UT_EQ( "0@@3456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@',   8,  1 )  ;    UT_EQ( "01234567@9",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@',   8,  2 )  ;    UT_EQ( "01234567@@",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion          ( '@',   8,  3 )  ;    UT_EQ( "01234567@@",   ms );

        ms.Clear()._("0123456789");   ms.ReplaceRegion<false>   ( '@',   0,  1 )  ;    UT_EQ( "@123456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion<false>   ( '@',   0,  2 )  ;    UT_EQ( "@@23456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion<false>   ( '@',   1,  1 )  ;    UT_EQ( "0@23456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion<false>   ( '@',   1,  2 )  ;    UT_EQ( "0@@3456789",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion<false>   ( '@',   8,  1 )  ;    UT_EQ( "01234567@9",   ms );
        ms.Clear()._("0123456789");   ms.ReplaceRegion<false>   ( '@',   8,  2 )  ;    UT_EQ( "01234567@@",   ms );
    }

}

//--------------------------------------------------------------------------------------------------
//--- Test Conversions
//--------------------------------------------------------------------------------------------------
UT_METHOD( Conversions )
{
    UT_INIT();

    AString   ms;
    string        s;
    ms= "0123456789";

    s= ToStdString(ms  );                     UT_EQ( s.c_str(), "0123456789" );
    s= ToStdString(ms,  5);                   UT_EQ( s.c_str(), "56789" );
    s= ToStdString(ms,  5, 100);              UT_EQ( s.c_str(), "56789" );
    s= ToStdString(ms,  -5);                  UT_EQ( s.c_str(), "0123456789" );
    s= ToStdString(ms,  -5, 10);              UT_EQ( s.c_str(), "01234" );
    s= ToStdString(ms,  -5, 100);             UT_EQ( s.c_str(), "0123456789" );

    s= ToStdString(ms,  0,  0);               UT_EQ( s.c_str(), "" );
    s= ToStdString(ms,  5,  0);               UT_EQ( s.c_str(), "" );
    s= ToStdString(ms,  20, 0);               UT_EQ( s.c_str(), "" );
    s= ToStdString(ms,  0,  -1);              UT_EQ( s.c_str(), "" );
    s= ToStdString(ms,  5,  -5);              UT_EQ( s.c_str(), "" );
    s= ToStdString(ms,  5,  -100);            UT_EQ( s.c_str(), "" );
    s= ToStdString(ms,  20,  -1);             UT_EQ( s.c_str(), "" );
    s= ToStdString(ms,  20,  20);             UT_EQ( s.c_str(), "" );
    s= ToStdString(ms,  20,  -100);           UT_EQ( s.c_str(), "" );
    s= ToStdString(ms,  20, 0);               UT_EQ( s.c_str(), "" );
    s= ToStdString(ms,  20, 100);             UT_EQ( s.c_str(), "" );

       ToStdString(ms, s);                    UT_EQ( s.c_str(), "0123456789" );
       ToStdString(ms, s, 5);                 UT_EQ( s.c_str(), "56789" );
       ToStdString(ms, s, 5, 100);            UT_EQ( s.c_str(), "56789" );
       ToStdString(ms, s, -5);                UT_EQ( s.c_str(), "0123456789" );
       ToStdString(ms, s, -5, 10);            UT_EQ( s.c_str(), "01234" );
       ToStdString(ms, s, -5, 100);           UT_EQ( s.c_str(), "0123456789" );

       ToStdString(ms, s, 0,  0);             UT_EQ( s.c_str(), "" );
       ToStdString(ms, s, 5,  0);             UT_EQ( s.c_str(), "" );
       ToStdString(ms, s, 20, 0);             UT_EQ( s.c_str(), "" );
       ToStdString(ms, s, 0,  -1);            UT_EQ( s.c_str(), "" );
       ToStdString(ms, s, 5,  -5);            UT_EQ( s.c_str(), "" );
       ToStdString(ms, s, 5,  -100);          UT_EQ( s.c_str(), "" );
       ToStdString(ms, s, 20,  -1);           UT_EQ( s.c_str(), "" );
       ToStdString(ms, s, 20,  20);           UT_EQ( s.c_str(), "" );
       ToStdString(ms, s, 20,  -100);         UT_EQ( s.c_str(), "" );
       ToStdString(ms, s, 20, 0);             UT_EQ( s.c_str(), "" );
       ToStdString(ms, s, 20, 100);           UT_EQ( s.c_str(), "" );

       s.clear();
       ToStdString(ms,  s );                           UT_EQ( s.c_str(), "0123456789"            );
       ToStdString(ms,  s,         CurrentData::Keep); UT_EQ( s.c_str(), "01234567890123456789"  );
       ToStdString(ms,  s );                           UT_EQ( s.c_str(), "0123456789"            );
       ToStdString(ms,  s, 5, 100 );                   UT_EQ( s.c_str(), "56789"                 );
       ToStdString(ms,  s, -5, 10, CurrentData::Keep); UT_EQ( s.c_str(), "5678901234"            );


    stringstream strs;
    ms= "hello stringstream";
    strs << ms;
    UT_EQ( strs.str(), "hello stringstream" );

    strs << endl;
    strs << "second line";

    strs >> ms;
    UT_EQ( "hello stringstream", ms );
    strs >> ms;
    UT_EQ( "second line"       , ms );

    strs >> ms;
    UT_EQ( ""                  , ms );
}


//--------------------------------------------------------------------------------------------------
//--- Test AssignAndAppend
//--------------------------------------------------------------------------------------------------
UT_METHOD( Append )
{
    UT_INIT();

    // const char*
    {
        AString ms;  const char* csNull= nullptr;  const char* csEmpty= "";

        ms= csNull;                UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNull()    );
        ms= csEmpty;               UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNotNull() );
        ms= "assign";              UT_EQ  ( 6, ms.Length()     );
        ms= csNull;                UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNull()    );
        ms= "assign";              UT_EQ  ( 6, ms.Length()     );
        ms= csNull;                UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNull()    );


        ms._( csNull );            UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNull()    );
        ms._( csEmpty);            UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNotNull() );
        ms.SetNull();              UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNull()    );

        ms._("1234567");           UT_EQ  (16, ms.Capacity()   );  UT_EQ( "1234567",   ms );
        ms._("89");                UT_TRUE( ms.Length()> 7      );  UT_EQ( "123456789", ms );

        const char* t= "0123456789";
        ms.Clear()._   ( t, 5);                     UT_EQ( "56789"      , ms );
        ms.Clear()._   ( t, 5, 100);                UT_EQ( "56789"      , ms );
        ms.Clear()._   ( t, -5);                    UT_EQ( "0123456789" , ms );
        ms.Clear()._   ( t, -5, 3);                 UT_EQ( ""           , ms );
        ms.Clear()._   ( t, 50, 3);                 UT_EQ( ""           , ms );
        ms.Clear()._   ( t, 10, 3);                 UT_EQ( ""           , ms );
        ms.Clear()._   ( t, -5, 10);                UT_EQ( "01234"      , ms );
        ms.Clear()._   ( t, -5, 100);               UT_EQ( "0123456789" , ms );

        // _NC
        ms.SetNull();            UT_EQ  ( 0, ms.Length()      );  UT_TRUE( ms.IsNull()   );
        ms._NC( csEmpty );       UT_EQ  ( 0, ms.Length()      );  UT_TRUE( ms.IsNull()   );
        ms.Clear()._NC( t, 5,3);                  UT_EQ( "567"   ,  ms    );

    }

    // const char*
    {
        AString ms;  const char* csNull= nullptr;  const char* csEmpty= "";

        ms= csNull;                UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNull()    );
        ms= csEmpty;               UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNotNull() );
        ms= "assign";              UT_EQ  ( 6, ms.Length()     );
        ms= csNull;                UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNull()    );
        ms= "assign";              UT_EQ  ( 6, ms.Length()     );
        ms= csNull;                UT_EQ  ( 0, ms.Length()     );  UT_TRUE( ms.IsNull()    );


        ms._( csNull );            UT_EQ  ( 0, ms.Length()    );  UT_TRUE( ms.IsNull()    );
        ms._( csEmpty);            UT_EQ  ( 0, ms.Length()    );  UT_TRUE( ms.IsNotNull() );
        ms.SetNull();              UT_EQ  ( 0, ms.Length()    );  UT_TRUE( ms.IsNull()    );

        ms._("1234567");           UT_EQ  (16, ms.Capacity()  );  UT_EQ( "1234567",   ms );
        ms._("89");                UT_TRUE( ms.Length()> 7     );  UT_EQ( "123456789", ms );

        const char* t= "0123456789";
        ms.Clear()._   ( t, 5);                     UT_EQ( "56789"      , ms );
        ms.Clear()._   ( t, 5, 100);                UT_EQ( "56789"      , ms );
        ms.Clear()._   ( t, -5);                    UT_EQ( "0123456789" , ms );
        ms.Clear()._   ( t, -5, 3);                 UT_EQ( ""           , ms );
        ms.Clear()._   ( t, 50, 3);                 UT_EQ( ""           , ms );
        ms.Clear()._   ( t, 10, 3);                 UT_EQ( ""           , ms );
        ms.Clear()._   ( t, -5, 10);                UT_EQ( "01234"      , ms );
        ms.Clear()._   ( t, -5, 100);               UT_EQ( "0123456789" , ms );

        // _NC
        ms.SetNull();            UT_EQ  ( 0, ms.Length()      );  UT_TRUE( ms.IsNull()   );
        ms._NC( csEmpty );       UT_EQ  ( 0, ms.Length()      );  UT_TRUE( ms.IsNull()   );
        ms.Clear()._NC( t, 5,3);                  UT_EQ( "567"   ,  ms   );

    }

    // fundamental types
    {
        AString ms;
        {  int      i= 5;   ms._()._(i)._('/')._(&i);       UT_EQ ( "5/5",    ms); }

        {  int8_t   i=  4;  ms._()._(i)._('/')._(&i);       UT_EQ ( "4/4"   , ms); }

        {  int8_t   i= -4;  ms._()._(i)._('/')._(&i);       UT_EQ ( "-4/-4" , ms); }
        {  uint8_t  i=  4;  ms._()._(i)._('/')._(&i);       UT_EQ ( "4/4"   , ms); }


        {  int16_t  i=  5;  ms._()._(i)._('/')._(&i);       UT_EQ ( "5/5"   , ms); }
        {  int16_t  i= -5;  ms._()._(i)._('/')._(&i);       UT_EQ ( "-5/-5" , ms); }
        {  uint16_t i=  5;  ms._()._(i)._('/')._(&i);       UT_EQ ( "5/5"   , ms); }

        {  int32_t  i=  6;  ms._()._(i)._('/')._(&i);       UT_EQ ( "6/6"   , ms); }
        {  int32_t  i= -6;  ms._()._(i)._('/')._(&i);       UT_EQ ( "-6/-6" , ms); }
        {  uint32_t i=  6;  ms._()._(i)._('/')._(&i);       UT_EQ ( "6/6"   , ms); }

        {  int64_t  i=  7;  ms._()._(i)._('/')._(&i);       UT_EQ ( "7/7"   , ms); }
        {  int64_t  i= -7;  ms._()._(i)._('/')._(&i);       UT_EQ ( "-7/-7" , ms); }
        {  uint64_t i=  7;  ms._()._(i)._('/')._(&i);       UT_EQ ( "7/7"   , ms); }

        {  int8_t   i=  4;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "4/4"   , ms); }
        {  int8_t   i= -4;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "-4/-4" , ms); }
        {  uint8_t  i=  4;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "4/4"   , ms); }


        {  int16_t  i=  5;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "5/5"   , ms); }
        {  int16_t  i= -5;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "-5/-5" , ms); }
        {  uint16_t i=  5;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "5/5"   , ms); }

        {  int32_t  i=  6;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "6/6"   , ms); }
        {  int32_t  i= -6;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "-6/-6" , ms); }
        {  uint32_t i=  6;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "6/6"   , ms); }

        {  int64_t  i=  7;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "7/7"   , ms); }
        {  int64_t  i= -7;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "-7/-7" , ms); }
        {  uint64_t i=  7;  ms._()._<false>(i)._('/')._<false>(&i);       UT_EQ ( "7/7"   , ms); }
    }

    // Substring
    {
        AString ms;  Substring ssNull; Substring ssEmpty("");  Substring t( "01234" );

        ms= ssNull;                UT_EQ  ( 0, ms.Length()        );  UT_TRUE( ms.IsNull()    );
        ms= ssEmpty;               UT_EQ  ( 0, ms.Length()        );  UT_TRUE( ms.IsNotNull() );
        ms= t;                     UT_EQ  ( 5, ms.Length()        );  UT_EQ  ( String(t), ms);
        ms= ssNull;                UT_EQ  ( 0, ms.Length()        );  UT_TRUE( ms.IsNull()    );

        ms._( ssNull );            UT_EQ  ( 0, ms.Length()        );  UT_TRUE( ms.IsNull()    );
        ms._( ssEmpty);            UT_EQ  ( 0, ms.Length()        );  UT_TRUE( ms.IsNotNull() );
        ms.SetNull();              UT_EQ  ( 0, ms.Length()        );  UT_TRUE( ms.IsNull()    );
        ms._( t );                 UT_EQ  (16, ms.Capacity()      );    UT_EQ( "01234"     , ms );
        ms._( t );                 UT_TRUE( ms.Length()> 5     );  UT_EQ( "0123401234", ms );

        t.ConsumeChar();         ms.Clear()._( t );           UT_EQ( "1234" , ms  );
        t.ConsumeChar();         ms.Clear()._( t );           UT_EQ(  "234" , ms  );
        t.ConsumeCharFromEnd();  ms.Clear()._( t );           UT_EQ( "23"   , ms  );

        // _NC
        ms.SetNull();             UT_EQ  ( 0, ms.Length()        );  UT_TRUE( ms.IsNull()    );
        ms._NC( ssEmpty );        UT_EQ  ( 0, ms.Length()        );  UT_TRUE( ms.IsNull()   );
        ms.Clear()._NC( t);                       UT_EQ( "23"  ,  ms   );
    }

    // std::string
    {
        AString ms;   std::string t( "012" ); std::string ssEmpty("");
                                   UT_EQ  ( 0, ms.Length()      );  UT_TRUE( ms.IsNull()    );
        ms= ssEmpty;               UT_EQ  ( 0, ms.Length()      );  UT_TRUE( ms.IsNotNull() );
        ms= t;                     UT_EQ  ( 3, ms.Length()      );  UT_EQ  ( t.c_str(), ms  );
        ms.SetNull();

        ms._( ssEmpty);            UT_EQ  ( 0, ms.Length()      );  UT_TRUE( ms.IsNotNull() );
        ms.SetNull();              UT_EQ  ( 0, ms.Length()      );  UT_TRUE( ms.IsNull()    );
        ms._( t );                 UT_EQ  (16, ms.Capacity()    );  UT_EQ( "012"   , ms );
        ms._( t );                 UT_TRUE( ms.Length()> 3      );  UT_EQ( "012012", ms );
        t= "0123456789";
        ms.Clear()._( t, 5);            UT_EQ( "56789"      , ms );
        ms.Clear()._( t, 5, 100);       UT_EQ( "56789"      , ms );
        ms.Clear()._( t, -5);           UT_EQ( "0123456789" , ms );
        ms.Clear()._( t, -5, 3);        UT_EQ( ""           , ms );
        ms.Clear()._( t, 50, 3);        UT_EQ( ""           , ms );
        ms.Clear()._( t, 10, 3);        UT_EQ( ""           , ms );
        ms.Clear()._( t, -5, 10);       UT_EQ( "01234"      , ms );
        ms.Clear()._( t, -5, 100);      UT_EQ( "0123456789" , ms );

        // _NC
        ms.SetNull();                   UT_EQ( 0, ms.Length());  UT_TRUE( ms.IsNull()    );
        ms._NC( ssEmpty );              UT_EQ( 0, ms.Length());  UT_FALSE( ms.IsNull()   );
        ms.Clear()._NC( t);             UT_EQ( "0123456789", ms  );
        ms.Clear()._<false>( t ,2,3);   UT_EQ( "234"       , ms  );
    }

    // string literals
    {
        // zero length literal
        {
            AString ms( "" );         UT_EQ( 0, ms.Length() );   UT_TRUE( ms.IsNotNull() );
        }
        {
            AString ms;
            ms._ ( "" );              UT_EQ( 0, ms.Length() );   UT_TRUE( ms.IsNotNull() );
        }
        {
            AString ms;
            ms <<       ""  ;         UT_EQ( 0, ms.Length() );   UT_TRUE( ms.IsNotNull() );
        }

        // 1 - 6 length literals
        {
            {   AString ms( "a" );       UT_EQ( 1, ms.Length() );   UT_EQ( "a"        , ms  );}
            {   AString ms( "ab" );      UT_EQ( 2, ms.Length() );   UT_EQ( "ab"       , ms  );}
            {   AString ms( "abc" );     UT_EQ( 3, ms.Length() );   UT_EQ( "abc"      , ms  );}
            {   AString ms( "abcd" );    UT_EQ( 4, ms.Length() );   UT_EQ( "abcd"     , ms  );}
            {   AString ms( "abcde" );   UT_EQ( 5, ms.Length() );   UT_EQ( "abcde"    , ms  );}
            {   AString ms( "abcdef" );  UT_EQ( 6, ms.Length() );   UT_EQ( "abcdef"   , ms  );}

            { AString ms;
              ms.Clear()._( "a" );       UT_EQ( 1, ms.Length() );   UT_EQ( "a"        , ms  );
              ms.Clear()._( "ab" );      UT_EQ( 2, ms.Length() );   UT_EQ( "ab"       , ms  );
              ms.Clear()._( "abc" );     UT_EQ( 3, ms.Length() );   UT_EQ( "abc"      , ms  );
              ms.Clear()._( "abcd" );    UT_EQ( 4, ms.Length() );   UT_EQ( "abcd"     , ms  );
              ms.Clear()._( "abcde" );   UT_EQ( 5, ms.Length() );   UT_EQ( "abcde"    , ms  );
              ms.Clear()._( "abcdef" );  UT_EQ( 6, ms.Length() );   UT_EQ( "abcdef"   , ms  );}
            { AString ms;
              ms.Clear() << "a"  ;       UT_EQ( 1, ms.Length() );   UT_EQ( "a"        , ms  );
              ms.Clear() << "ab"  ;      UT_EQ( 2, ms.Length() );   UT_EQ( "ab"       , ms  );
              ms.Clear() << "abc"  ;     UT_EQ( 3, ms.Length() );   UT_EQ( "abc"      , ms  );
              ms.Clear() << "abcd"  ;    UT_EQ( 4, ms.Length() );   UT_EQ( "abcd"     , ms  );
              ms.Clear() << "abcde"  ;   UT_EQ( 5, ms.Length() );   UT_EQ( "abcde"    , ms  );
              ms.Clear() << "abcdef"  ;  UT_EQ( 6, ms.Length() );   UT_EQ( "abcdef"   , ms  );}
        }

    }

}


//--------------------------------------------------------------------------------------------------
//--- Test Fields
//--------------------------------------------------------------------------------------------------
UT_METHOD( Fields )
{
    UT_INIT();

    AString ms;

    // empty fields
    ms._( Format::Field( nullptr, 3, Alignment::Left,     '#' ) );
    #if ALIB_DEBUG
        #if defined(_WIN32)
            UT_EQ( "std::nullptr_t(0x0)", ms   );
        #else
            UT_EQ( "decltype(nullptr)(0x0)", ms   );
        #endif
    #endif

    ms.Clear();

    ms._( Format::Field( "" ,     3, Alignment::Left,     '#' ) );    UT_EQ( "###"          , ms );
    ms._( Format::Field( "" ,     4, Alignment::Center,   '*' ) );    UT_EQ( "###****"      , ms );
    ms._( Format::Field( "" ,     5, Alignment::Right,    '+' ) );    UT_EQ( "###****+++++" , ms );

    // field, alignment left
    ms.Clear();
    ms._( Format::Field( "A"       , 5,    Alignment::Left ) );
    ms._( Format::Field( "AB"      , 5,    Alignment::Left ) );
    ms._( Format::Field( "ABC"     , 5,    Alignment::Left ) );
    ms._( Format::Field( "ABCD"    , 5,    Alignment::Left ) );
    ms._( Format::Field( "ABCDE"   , 5,    Alignment::Left ) );
    ms._( Format::Field( "ABCDEF"  , 5,    Alignment::Left ) );
    ms._( Format::Field( "ABCDEFG" , 5,    Alignment::Left ) );
    UT_EQ( "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG", ms );

    // field, alignment right
    ms.Clear();
    ms._( Format::Field( "A"       , 5,    Alignment::Right ) );
    ms._( Format::Field( "AB"      , 5,    Alignment::Right ) );
    ms._( Format::Field( "ABC"     , 5                      ) ); // btw: right is default
    ms._( Format::Field( "ABCD"    , 5                      ) );
    ms._( Format::Field( "ABCDE"   , 5                      ) );
    ms._( Format::Field( "ABCDEF"  , 5,    Alignment::Right ) );
    ms._( Format::Field( "ABCDEFG" , 5,    Alignment::Right ) );
    UT_EQ( "    A   AB  ABC ABCDABCDEABCDEFABCDEFG", ms );

    // field, alignment center
    ms.Clear();
    ms._( Format::Field( "A"       , 5,    Alignment::Center) );
    ms._( Format::Field( "AB"      , 5,    Alignment::Center) );
    ms._( Format::Field( "ABC"     , 5,    Alignment::Center) );
    ms._( Format::Field( "ABCD"    , 5,    Alignment::Center) );
    ms._( Format::Field( "ABCDE"   , 5,    Alignment::Center) );
    ms._( Format::Field( "ABCDEF"  , 5,    Alignment::Center) );
    ms._( Format::Field( "ABCDEFG" , 5,    Alignment::Center) );
    UT_EQ( "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG", ms );

    // a nested field
    ms.Clear();
    ms._("***");
        String32 inner  ("OS:");    inner._(Format::Field( "Linux", 10, Alignment::Right, '-' ) );
             inner._(" Lang:"); inner._(Format::Field( "en_US",  8, Alignment::Right, '-' ) );
        ms._(Format::Field( inner, 35, Alignment::Center, '#' ) );
    ms._("***");
    UT_EQ( "***####OS:-----Linux Lang:---en_US####***", ms );
}




//--------------------------------------------------------------------------------------------------
//--- Test Capacity
//--------------------------------------------------------------------------------------------------
UT_METHOD( CapacityLength )
{
    UT_INIT();

    // null-allocated
    {
        AString ms( 0 );
        ms._(  "" );       UT_TRUE( ms.Capacity() > 0 );
    }

    {
        AString ms( 5 );
        ms._( 'a' );        UT_EQ( 5, ms.Capacity() );
        ms._( 'b' );        UT_EQ( 5, ms.Capacity() );
        ms._( 'c' );        UT_EQ( 5, ms.Capacity() );
        ms._( 'd' );        UT_EQ( 5, ms.Capacity() );
        ms._( 'e' );        UT_EQ( 5, ms.Capacity() );
        ms._( 'x' );        UT_TRUE( ms.Capacity() >= 6 );
        UT_EQ( "abcdex", ms );

        ms.GrowBufferAtLeastBy( 2000 );      UT_TRUE( ms.Capacity() >= 2000 );
    }

    {
        AString   ms;
        integer as;
        ms._( "0123456789" );           UT_EQ( 10, ms.Length() );    UT_TRUE  ( ms.Capacity() >= 10 );

        as= ms.Capacity();

        lib::lang::Report::GetDefault().PushHaltFlags( false, false );
            UT_PRINT( "A warning should follow" );
            ms.SetLength(20);                    UT_EQ( 10, ms.Length() );    UT_EQ  ( ms.Capacity(), as );    UT_EQ("0123456789"   ,  ms  );

            UT_PRINT( "No (second) warning should follow" );
            ms.SetLength(20);                    UT_EQ( 10, ms.Length() );    UT_EQ  ( ms.Capacity(), as );    UT_EQ("0123456789"   ,  ms  );

            ALIB_WARN_ONCE_PER_TYPE_ENABLE( AString, SetLengthLonger );

            UT_PRINT( "No warning should follow" );
            ms.SetLength(10);                    UT_EQ( 10, ms.Length() );    UT_EQ  ( ms.Capacity(), as );    UT_EQ("0123456789"   ,  ms  );

            UT_PRINT( "A warning should follow" );
            ms.SetLength(11);                    UT_EQ( 10, ms.Length() );    UT_EQ  ( ms.Capacity(), as );    UT_EQ("0123456789"   ,  ms  );

            UT_PRINT( "No (second) warning should follow" );
            ms.SetLength(11);                    UT_EQ( 10, ms.Length() );    UT_EQ  ( ms.Capacity(), as );    UT_EQ("0123456789"   ,  ms  );

        lib::lang::Report::GetDefault().PopHaltFlags();

        ms.SetLength(5);                         UT_EQ( 5, ms.Length() );    UT_EQ  ( ms.Capacity(), as );    UT_EQ( "01234"  , ms    );
        ms.SetBuffer(3);                         UT_EQ( 3, ms.Length() );    UT_EQ  ( ms.Capacity(), 3  );    UT_EQ( "012"    , ms    );
        ms._("ABC");                             UT_EQ( 6, ms.Length() );    UT_TRUE( ms.Capacity() >= 6);    UT_EQ( "012ABC" , ms    );
    }

    // external buffer
    {
        AString* ms;
        ms= new AString();
        ms->SetBuffer( new char[5], 5, 0, Responsibility::Transfer );
        ms->_("ABC");                  UT_EQ( 3, ms->Length() );        UT_TRUE ( ms->Capacity() == 4 );  UT_EQ( "ABC"   , *ms  );

        delete ms;

        ms= new AString();
        ms->SetBuffer( new char[5], 5, 0, Responsibility::Transfer );
        ms->_("ABC");
        ms->_("ABC");                  UT_EQ( 6, ms->Length() );        UT_TRUE ( ms->Capacity() > 4 );  UT_EQ( "ABCABC"   , *ms  );
        delete ms;

        char stackCA1[5];
        AString sMS1;
        sMS1.SetBuffer( reinterpret_cast<char*>(&stackCA1), 5 );
        sMS1._("ABC");                 UT_TRUE ( sMS1.Buffer() == reinterpret_cast<char*>(&stackCA1) );  UT_EQ( "ABC"   , sMS1  );

        lib::lang::Report::GetDefault().PushHaltFlags( false, false );
            char stackCA2[5];
            AString sMS2;
            sMS2.SetBuffer( reinterpret_cast<char*>(&stackCA2), 5 );
            sMS2._("ABC");
            UT_PRINT( "A warning should follow" );
            sMS2._("ABC");                UT_TRUE ( sMS2.Buffer() != reinterpret_cast<char*>(&stackCA2) );  UT_EQ( "ABCABC"   , sMS2  );

            PreallocatedString<5> msS;
            const char* orig= msS.Buffer();
            msS._("ABC");                 UT_TRUE ( msS.Buffer() == orig );  UT_EQ( "ABC"   , String(msS)  );
            UT_PRINT( "A warning should follow" );
            msS._("ABC");                 UT_TRUE ( msS.Buffer() != orig );  UT_EQ( "ABCABC", String(msS)  );

            String64 ms64;
            orig= ms64.Buffer();
            ms64._("ABC");                UT_TRUE ( ms64.Buffer() == orig ); UT_EQ( "ABC"   , String(ms64) );
            ms64.Clear();
            ms64.InsertChars('@', 63 );   UT_TRUE ( ms64.Buffer() == orig );
            UT_PRINT( "A warning should follow" );
            ms64._( '@' );
            UT_TRUE ( ms64 != orig );
            UT_TRUE ( ms64.SearchAndReplace( '@', 'X' ) == 64 );
        lib::lang::Report::GetDefault().PopHaltFlags();
    }
}


//--------------------------------------------------------------------------------------------------
//--- Test Tab
//--------------------------------------------------------------------------------------------------
UT_METHOD( Tab )
{
    UT_INIT();

    AString ms;

    // test some bad input
                   ms._(Format::Tab(  0, 0, -1,        '@' ));        UT_EQ( "",  ms );
    ms.Clear();    ms._(Format::Tab(  0, 0,  0,        '@' ));        UT_EQ( "",  ms );
    ms.Clear();    ms._(Format::Tab( -1, 0,  0,        '@' ));        UT_EQ( "",  ms );
    ms.Clear();    ms._(Format::Tab( -1, 0,  0,        '@' ));        UT_EQ( "",  ms );
    ms.Clear();    ms._(Format::Tab( -1, 0,  -1,       '@' ));        UT_EQ( "",  ms );
    ms.Clear();    ms._(Format::Tab( -5, 0,  0,        '@' ));        UT_EQ( "",  ms );
    ms.Clear();    ms._(Format::Tab( -5, 0,  -100,     '@' ));        UT_EQ( "",  ms );
    ms.Clear();    ms._(Format::Tab(  2, 0,  -101,     '@' ));        UT_EQ( "",  ms );
    ms.Clear();    ms._(Format::Tab(  0, 0,  0,        '@' ));        UT_EQ( "",  ms );
    ms.Clear();    ms._(Format::Tab(  1, 0,  0,        '@' ));        UT_EQ( "",  ms );
    ms.Clear();    ms._(Format::Tab(  1, 0,  1,        '@' ));        UT_EQ( "@", ms );
    ms.Clear();    ms._(Format::Tab(  0, 0,  1,        '@' ));        UT_EQ( "@", ms );


    // minpad 0 (not common, default is 1, tab wont move if on tab position)
    ms.Clear();                    ms._(Format::Tab( 2, 0, 0,    '@' ) )._( '-' );       UT_EQ( "-",   ms );
    ms.Clear();    ms._( 'x' );    ms._(Format::Tab( 2, 0, 0,    '@' ) )._( '-' );       UT_EQ( "x@-", ms );

    // more standard tabs
    ms.Clear();
    ms._( "12" )._(Format::Tab( 2 ))
      ._(  '1' )._(Format::Tab( 2 ))
                ._(Format::Tab( 2 ))
      ._(  '@' );
    UT_EQ( "12  1   @", ms );

    ms.Clear();
    ms._( "12" )._(Format::Tab( 2, 0, 0 ))
      ._(  '1' )._(Format::Tab( 2, 0, 0 ))
      ._(Format::Tab(2, 0, 0))
      ._(  '@' );
    UT_EQ( "121 @", ms );


    ms.Clear();
    ms._( "12345" )._(Format::Tab( 5 ))
      ._( "1234" ) ._(Format::Tab( 5 ))
      ._( "123" )  ._(Format::Tab( 5 ))
      ._( "12" )   ._(Format::Tab( 5 ))
      ._(  '1' )   ._(Format::Tab( 5 ))
                   ._(Format::Tab( 5 ))
      ._(  '@' );
    UT_EQ( "12345     1234 123  12   1         @", ms );

    ms.Clear();
    ms._( "12345" )._(Format::Tab( 5, 0, 0 ))
      ._( "1234" ) ._(Format::Tab( 5, 0, 0 ))
      ._( "123" )  ._(Format::Tab( 5, 0, 0 ))
      ._( "12" )   ._(Format::Tab( 5, 0, 0 ))
      ._(  '1' )   ._(Format::Tab( 5, 0, 0 ))
                   ._(Format::Tab( 5, 0, 0 ))
      ._(  '@' );
    UT_EQ( "123451234 123  12   1    @", ms );

    ms.Clear();                   ms._(Format::Tab( 0 ))  ._( '-' );        UT_EQ( " -"    , ms );
    ms.Clear();                   ms._(Format::Tab( 1 ))  ._( '-' );        UT_EQ( " -"    , ms );
    ms.Clear();                   ms._(Format::Tab( 2 ))  ._( '-' );        UT_EQ( "  -"   , ms );
    ms.Clear();                   ms._(Format::Tab( 3 ))  ._( '-' );        UT_EQ( "   -"  , ms );
    ms.Clear();    ms._( 'x' );   ms._(Format::Tab( 1 ))  ._( '-' );        UT_EQ( "x -"   , ms );
    ms.Clear();    ms._( 'x' );   ms._(Format::Tab( 2 ))  ._( '-' );        UT_EQ( "x -"   , ms );
    ms.Clear();    ms._( 'x' );   ms._(Format::Tab( 3 ))  ._( '-' );        UT_EQ( "x  -"  , ms );

    // tabs with tab reference set (designed for multi line tabs)
    ms.Clear()._("ABC").NewLine();
    ms._( "12345" )._(Format::Tab( 5 , -1))
      ._( "1234" ) ._(Format::Tab( 5 , -1))
      ._( "123" )  ._(Format::Tab( 5 , -1))
      ._( "12" )   ._(Format::Tab( 5 , -1))
      ._(  '1' )   ._(Format::Tab( 5 , -1))
                   ._(Format::Tab( 5 , -1))
      ._(  '@' );
    UT_EQ( String64("ABC").NewLine()._( "12345     1234 123  12   1         @" ), ms );

    ms.Clear()._("ABC").NewLine();
    ms._( "12345" )._(Format::Tab( 5, -1, 0 ))
      ._( "1234" ) ._(Format::Tab( 5, -1, 0 ))
      ._( "123" )  ._(Format::Tab( 5, -1, 0 ))
      ._( "12" )   ._(Format::Tab( 5, -1, 0 ))
      ._(  '1' )   ._(Format::Tab( 5, -1, 0 ))
                   ._(Format::Tab( 5, -1, 0 ))
      ._(  '@' );
    UT_EQ( String32("ABC").NewLine()._( "123451234 123  12   1    @" )        , ms );


}

//--------------------------------------------------------------------------------------------------
//--- Test SearchReplace
//--------------------------------------------------------------------------------------------------
UT_METHOD( SearchAndReplace )
{
    UT_INIT();

    integer result;

    // search characters
    {
        String ms("abcd abcd");
        result= ms.IndexOf       ( '@', -5  );   UT_EQ(    -1,  result );
        result= ms.IndexOf       ( '@'      );   UT_EQ(    -1,  result );
        result= ms.IndexOf       ( '@', 5   );   UT_EQ(    -1,  result );
        result= ms.IndexOf       ( '@', 150 );   UT_EQ(    -1,  result );

        result= ms.IndexOf       ( 'a'      );   UT_EQ(    0,   result );
        result= ms.IndexOf       ( 'b'      );   UT_EQ(    1,   result );
        result= ms.IndexOf       ( 'c'      );   UT_EQ(    2,   result );

        result= ms.IndexOf       ( 'a', 0   );   UT_EQ(    0,   result );
        result= ms.IndexOf       ( 'b', 0   );   UT_EQ(    1,   result );
        result= ms.IndexOf       ( 'c', 0   );   UT_EQ(    2,   result );

        result= ms.IndexOf       ( 'a', 1   );   UT_EQ(    5,   result );
        result= ms.IndexOf       ( 'b', 1   );   UT_EQ(    1,   result );
        result= ms.IndexOf       ( 'c', 1   );   UT_EQ(    2,   result );

        result= ms.IndexOf       ( 'a', 2   );   UT_EQ(    5,   result );
        result= ms.IndexOf       ( 'b', 2   );   UT_EQ(    6,   result );
        result= ms.IndexOf       ( 'c', 2   );   UT_EQ(    2,   result );

        result= ms.IndexOf       ( 'a', 3   );   UT_EQ(    5,   result );
        result= ms.IndexOf       ( 'b', 3   );   UT_EQ(    6,   result );
        result= ms.IndexOf       ( 'c', 3   );   UT_EQ(    7,   result );

        result= ms.IndexOf       ( 'd', 7   );   UT_EQ(    8,   result );
        result= ms.IndexOf       ( 'd', 8   );   UT_EQ(    8,   result );
        result= ms.IndexOf       ( 'd', 9   );   UT_EQ(   -1,   result );

        result= ms.IndexOf<false>( '@', 5   );   UT_EQ(    -1,  result );

        result= ms.IndexOf<false>( 'a', 0   );   UT_EQ(    0,   result );
        result= ms.IndexOf<false>( 'b', 0   );   UT_EQ(    1,   result );
        result= ms.IndexOf<false>( 'c', 0   );   UT_EQ(    2,   result );

        result= ms.IndexOf<false>( 'a', 1   );   UT_EQ(    5,   result );
        result= ms.IndexOf<false>( 'b', 1   );   UT_EQ(    1,   result );
        result= ms.IndexOf<false>( 'c', 1   );   UT_EQ(    2,   result );

        result= ms.IndexOf<false>( 'a', 2   );   UT_EQ(    5,   result );
        result= ms.IndexOf<false>( 'b', 2   );   UT_EQ(    6,   result );
        result= ms.IndexOf<false>( 'c', 2   );   UT_EQ(    2,   result );

        result= ms.IndexOf<false>( 'a', 3   );   UT_EQ(    5,   result );
        result= ms.IndexOf<false>( 'b', 3   );   UT_EQ(    6,   result );
        result= ms.IndexOf<false>( 'c', 3   );   UT_EQ(    7,   result );

        result= ms.IndexOf<false>( 'd', 7   );   UT_EQ(    8,   result );
        result= ms.IndexOf<false>( 'd', 8   );   UT_EQ(    8,   result );
    }

    {
        AString ms("0123456789");
        result= ms.IndexOf       ( '1',    -5,   3 );   UT_EQ( -1,  result );
        result= ms.IndexOf       ( '1',     0,   1 );   UT_EQ( -1,  result );
        result= ms.IndexOf       ( '1',     0,   2 );   UT_EQ(  1,  result );
        result= ms.IndexOf       ( '2',     0,   2 );   UT_EQ( -1,  result );
        result= ms.IndexOf       ( '2',     1,   2 );   UT_EQ(  2,  result );
        result= ms.IndexOf       ( '2',     1,   3 );   UT_EQ(  2,  result );
        result= ms.IndexOf       ( '2',     2,   3 );   UT_EQ(  2,  result );
        result= ms.IndexOf       ( '2',     2,   1 );   UT_EQ(  2,  result );
        result= ms.IndexOf       ( '2',     2,   0 );   UT_EQ( -1,  result );
        result= ms.IndexOf       ( '2',     3,   0 );   UT_EQ( -1,  result );
        result= ms.IndexOf       ( '2',     3,   1 );   UT_EQ( -1,  result );
        result= ms.IndexOf       ( '2',   100,  20 );   UT_EQ( -1,  result );
        result= ms.IndexOf       ( '2',  -100, 102 );   UT_EQ( -1,  result );
        result= ms.IndexOf       ( '2',  -100, 103 );   UT_EQ(  2,  result );
        result= ms.IndexOf       ( '2',  -100, 202 );   UT_EQ(  2,  result );

        result= ms.IndexOf<false>( '1',     0,   1 );   UT_EQ( -1,  result );
        result= ms.IndexOf<false>( '1',     0,   2 );   UT_EQ(  1,  result );
        result= ms.IndexOf<false>( '2',     0,   2 );   UT_EQ( -1,  result );
        result= ms.IndexOf<false>( '2',     1,   2 );   UT_EQ(  2,  result );
        result= ms.IndexOf<false>( '2',     1,   3 );   UT_EQ(  2,  result );
        result= ms.IndexOf<false>( '2',     2,   3 );   UT_EQ(  2,  result );
        result= ms.IndexOf<false>( '2',     2,   1 );   UT_EQ(  2,  result );
        result= ms.IndexOf<false>( '2',     3,   1 );   UT_EQ( -1,  result );
    }

    // ------------------ search char backwards ------------------
    {
        AString ms("abcd abcd");
        result= ms.LastIndexOf       ( '@', -5  );   UT_EQ(    -1,  result );
        result= ms.LastIndexOf       ( '@'      );   UT_EQ(    -1,  result );
        result= ms.LastIndexOf       ( '@', 5   );   UT_EQ(    -1,  result );
        result= ms.LastIndexOf       ( '@', 150 );   UT_EQ(    -1,  result );

        result= ms.LastIndexOf       ( 'a'      );   UT_EQ(    5,   result );
        result= ms.LastIndexOf       ( 'b'      );   UT_EQ(    6,   result );
        result= ms.LastIndexOf       ( 'c'      );   UT_EQ(    7,   result );
        result= ms.LastIndexOf       ( 'd'      );   UT_EQ(    8,   result );

        result= ms.LastIndexOf       ( 'a', 0   );   UT_EQ(    0,   result );
        result= ms.LastIndexOf       ( 'b', 0   );   UT_EQ(   -1,   result );
        result= ms.LastIndexOf       ( 'c', 0   );   UT_EQ(   -1,   result );

        result= ms.LastIndexOf       ( 'a', 1   );   UT_EQ(    0,   result );
        result= ms.LastIndexOf       ( 'b', 1   );   UT_EQ(    1,   result );
        result= ms.LastIndexOf       ( 'c', 1   );   UT_EQ(   -1,   result );

        result= ms.LastIndexOf       ( 'a', 2   );   UT_EQ(    0,   result );
        result= ms.LastIndexOf       ( 'b', 2   );   UT_EQ(    1,   result );
        result= ms.LastIndexOf       ( 'c', 2   );   UT_EQ(    2,   result );

        result= ms.LastIndexOf       ( 'a', 3   );   UT_EQ(    0,   result );
        result= ms.LastIndexOf       ( 'b', 3   );   UT_EQ(    1,   result );
        result= ms.LastIndexOf       ( 'c', 3   );   UT_EQ(    2,   result );

        result= ms.LastIndexOf       ( 'd', 7   );   UT_EQ(    3,   result );
        result= ms.LastIndexOf       ( 'd', 8   );   UT_EQ(    8,   result );
        result= ms.LastIndexOf       ( 'd', 9   );   UT_EQ(    8,   result );
        result= ms.LastIndexOf       ( 'd', 10  );   UT_EQ(    8,   result );
        result= ms.LastIndexOf       ( 'd', 11  );   UT_EQ(    8,   result );
        result= ms.LastIndexOf       ( 'c', 11  );   UT_EQ(    7,   result );


        result= ms.LastIndexOf<false>( '@', 5   );   UT_EQ(    -1,  result );

        result= ms.LastIndexOf<false>( 'a', 0   );   UT_EQ(    0,   result );
        result= ms.LastIndexOf<false>( 'b', 0   );   UT_EQ(   -1,   result );
        result= ms.LastIndexOf<false>( 'c', 0   );   UT_EQ(   -1,   result );

        result= ms.LastIndexOf<false>( 'a', 1   );   UT_EQ(    0,   result );
        result= ms.LastIndexOf<false>( 'b', 1   );   UT_EQ(    1,   result );
        result= ms.LastIndexOf<false>( 'c', 1   );   UT_EQ(   -1,   result );

        result= ms.LastIndexOf<false>( 'a', 2   );   UT_EQ(    0,   result );
        result= ms.LastIndexOf<false>( 'b', 2   );   UT_EQ(    1,   result );
        result= ms.LastIndexOf<false>( 'c', 2   );   UT_EQ(    2,   result );

        result= ms.LastIndexOf<false>( 'a', 3   );   UT_EQ(    0,   result );
        result= ms.LastIndexOf<false>( 'b', 3   );   UT_EQ(    1,   result );
        result= ms.LastIndexOf<false>( 'c', 3   );   UT_EQ(    2,   result );

        result= ms.LastIndexOf<false>( 'd', 7   );   UT_EQ(    3,   result );
        result= ms.LastIndexOf<false>( 'd', 8   );   UT_EQ(    8,   result );
    }


    // ------------------ search one of several characters ------------------
    // non static version
    {
        String ms("abcd abcde");

        // search one of
        integer l= ms.Length();
        result= ms.IndexOfAny    <Inclusion::Include       >( ""           );    UT_EQ(  -1, result );
        result= ms.IndexOfAny    <Inclusion::Include       >( "x"          );    UT_EQ(  -1, result );
        result= ms.IndexOfAny    <Inclusion::Include       >( "xy"         );    UT_EQ(  -1, result );
        result= ms.IndexOfAny    <Inclusion::Include       >( "xyz"        );    UT_EQ(  -1, result );
        result= ms.IndexOfAny    <Inclusion::Include       >( "xyd"        );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Include       >( "d"          );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Include       >( "xyd" ,  -2  );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Include       >( "xyd" ,   4  );    UT_EQ(   8, result );
        result= ms.IndexOfAny    <Inclusion::Include       >( "xyd" ,  20  );    UT_EQ(  -1, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( ""           );    UT_EQ(  -1, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "x"          );    UT_EQ(  -1, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "xy"         );    UT_EQ(  -1, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "xyz"        );    UT_EQ(  -1, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "xyd"        );    UT_EQ(   8, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "xyd" ,  -2  );    UT_EQ(  -1, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "xyd" ,   2  );    UT_EQ(  -1, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "xyd" ,   4  );    UT_EQ(   3, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "a"   ,   4  );    UT_EQ(   0, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "b"   ,   4  );    UT_EQ(   1, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "ba"  ,   4  );    UT_EQ(   1, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "xa"  ,   4  );    UT_EQ(   0, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "xyd" ,  20  );    UT_EQ(   8, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "d"   ,  20  );    UT_EQ(   8, result );
        result= ms.LastIndexOfAny<Inclusion::Include       >( "e"   ,  20  );    UT_EQ(   9, result );
        result= ms.IndexOfAny    <Inclusion::Include, false>( "x"          );    UT_EQ(  -1, result );
        result= ms.IndexOfAny    <Inclusion::Include, false>( "xy"         );    UT_EQ(  -1, result );
        result= ms.IndexOfAny    <Inclusion::Include, false>( "xyz"        );    UT_EQ(  -1, result );
        result= ms.IndexOfAny    <Inclusion::Include, false>( "xyd"        );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Include, false>( "d"          );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Include, false>( "xyd"  ,  4  );    UT_EQ(   8, result );
        result= ms.LastIndexOfAny<Inclusion::Include, false>( "xyd"  ,  2  );    UT_EQ(  -1, result );
        result= ms.LastIndexOfAny<Inclusion::Include, false>( "xyd"  ,  4  );    UT_EQ(   3, result );
        result= ms.LastIndexOfAny<Inclusion::Include, false>( "a"    ,  4  );    UT_EQ(   0, result );
        result= ms.LastIndexOfAny<Inclusion::Include, false>( "b"    ,  4  );    UT_EQ(   1, result );
        result= ms.LastIndexOfAny<Inclusion::Include, false>( "ba"   ,  4  );    UT_EQ(   1, result );
        result= ms.LastIndexOfAny<Inclusion::Include, false>( "xa"   ,  4  );    UT_EQ(   0, result );

        // search NOT one of
        result= ms.IndexOfAny    <Inclusion::Exclude       >( ""           );    UT_EQ(   0, result );
        result= ms.IndexOfAny    <Inclusion::Exclude       >( "x"          );    UT_EQ(   0, result );
        result= ms.IndexOfAny    <Inclusion::Exclude       >( "xy"         );    UT_EQ(   0, result );
        result= ms.IndexOfAny    <Inclusion::Exclude       >( "xyz"        );    UT_EQ(   0, result );
        result= ms.IndexOfAny    <Inclusion::Exclude       >( "a"          );    UT_EQ(   1, result );
        result= ms.IndexOfAny    <Inclusion::Exclude       >( "ba"         );    UT_EQ(   2, result );
        result= ms.IndexOfAny    <Inclusion::Exclude       >( "abc"        );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Exclude       >( "acb"        );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Exclude       >( "cba"        );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Exclude       >( "xcba"       );    UT_EQ(   3, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( ""           );    UT_EQ( l-1, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "x"          );    UT_EQ( l-1, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "xy"         );    UT_EQ( l-1, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "e"          );    UT_EQ( l-2, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "de"         );    UT_EQ( l-3, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "cde"        );    UT_EQ( l-4, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "ced"        );    UT_EQ( l-4, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "ecd"        );    UT_EQ( l-4, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "ecd"  ,  5  );    UT_EQ(   5, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "ecd"  ,  4  );    UT_EQ(   4, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "acd"  ,  3  );    UT_EQ(   1, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "abc"  ,  2  );    UT_EQ(  -1, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "xay"  ,  3  );    UT_EQ(   3, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "d"    ,  3  );    UT_EQ(   2, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude       >( "a"    ,  0  );    UT_EQ(  -1, result );
        result= ms.IndexOfAny    <Inclusion::Exclude ,false>( "x"          );    UT_EQ(   0, result );
        result= ms.IndexOfAny    <Inclusion::Exclude ,false>( "xy"         );    UT_EQ(   0, result );
        result= ms.IndexOfAny    <Inclusion::Exclude ,false>( "xyz"        );    UT_EQ(   0, result );
        result= ms.IndexOfAny    <Inclusion::Exclude ,false>( "a"          );    UT_EQ(   1, result );
        result= ms.IndexOfAny    <Inclusion::Exclude ,false>( "ba"         );    UT_EQ(   2, result );
        result= ms.IndexOfAny    <Inclusion::Exclude ,false>( "abc"        );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Exclude ,false>( "acb"        );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Exclude ,false>( "cba"        );    UT_EQ(   3, result );
        result= ms.IndexOfAny    <Inclusion::Exclude ,false>( "xcba"       );    UT_EQ(   3, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude ,false>( "ecd"  ,  4  );    UT_EQ(   4, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude ,false>( "acd"  ,  3  );    UT_EQ(   1, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude ,false>( "abc"  ,  2  );    UT_EQ(  -1, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude ,false>( "xay"  ,  3  );    UT_EQ(   3, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude ,false>( "d"    ,  3  );    UT_EQ(   2, result );
        result= ms.LastIndexOfAny<Inclusion::Exclude ,false>( "a"    ,  0  );    UT_EQ(  -1, result );
    }

    // ------------------ search one of several characters TString version  ------------------
    // non static version
    {
        TString ms("abcd abcde");
        // search one of
        result= ms.IndexOfAny<Inclusion::Include       >( ""            );    UT_EQ(  -1, result );
        result= ms.IndexOfAny<Inclusion::Include       >( "x"           );    UT_EQ(  -1, result );
        result= ms.IndexOfAny<Inclusion::Include       >( "xy"          );    UT_EQ(  -1, result );
        result= ms.IndexOfAny<Inclusion::Include       >( "xyz"         );    UT_EQ(  -1, result );
        result= ms.IndexOfAny<Inclusion::Include       >( "xyd"         );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Include       >( "d"           );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Include       >( "xyd"   , -2  );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Include       >( "xyd"   ,  4  );    UT_EQ(   8, result );
        result= ms.IndexOfAny<Inclusion::Include       >( "xyd"   , 20  );    UT_EQ(  -1, result );
        result= ms.IndexOfAny<Inclusion::Include, false>( "x"           );    UT_EQ(  -1, result );
        result= ms.IndexOfAny<Inclusion::Include, false>( "xy"          );    UT_EQ(  -1, result );
        result= ms.IndexOfAny<Inclusion::Include, false>( "xyz"         );    UT_EQ(  -1, result );
        result= ms.IndexOfAny<Inclusion::Include, false>( "xyd"         );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Include, false>( "d"           );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Include, false>( "xyd"   ,  4  );    UT_EQ(   8, result );
        result= ms.IndexOfAny<Inclusion::Exclude       >( ""            );    UT_EQ(   0, result );
        result= ms.IndexOfAny<Inclusion::Exclude       >( "x"           );    UT_EQ(   0, result );
        result= ms.IndexOfAny<Inclusion::Exclude       >( "xy"          );    UT_EQ(   0, result );
        result= ms.IndexOfAny<Inclusion::Exclude       >( "xyz"         );    UT_EQ(   0, result );
        result= ms.IndexOfAny<Inclusion::Exclude       >( "a"           );    UT_EQ(   1, result );
        result= ms.IndexOfAny<Inclusion::Exclude       >( "ba"          );    UT_EQ(   2, result );
        result= ms.IndexOfAny<Inclusion::Exclude       >( "abc"         );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Exclude       >( "acb"         );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Exclude       >( "cba"         );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Exclude       >( "xcba"        );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Exclude, false>( "x"           );    UT_EQ(   0, result );
        result= ms.IndexOfAny<Inclusion::Exclude, false>( "xy"          );    UT_EQ(   0, result );
        result= ms.IndexOfAny<Inclusion::Exclude, false>( "xyz"         );    UT_EQ(   0, result );
        result= ms.IndexOfAny<Inclusion::Exclude, false>( "a"           );    UT_EQ(   1, result );
        result= ms.IndexOfAny<Inclusion::Exclude, false>( "ba"          );    UT_EQ(   2, result );
        result= ms.IndexOfAny<Inclusion::Exclude, false>( "abc"         );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Exclude, false>( "acb"         );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Exclude, false>( "cba"         );    UT_EQ(   3, result );
        result= ms.IndexOfAny<Inclusion::Exclude, false>( "xcba"        );    UT_EQ(   3, result );
    }

    // search nullptr, empty string
    {
        TString ms("abcd abcd");
        result= ms.IndexOfSubstring( nullptr        );    UT_EQ( -1, result );
        result= ms.IndexOfSubstring( nullptr,    5  );    UT_EQ( -1, result );
        result= ms.IndexOfSubstring( nullptr,   50  );    UT_EQ( -1, result );
        result= ms.IndexOfSubstring( nullptr, -  5  );    UT_EQ( -1, result );
        result= ms.IndexOfSubstring( "",      -  5  );    UT_EQ(  0, result );
        result= ms.IndexOfSubstring( "",         0  );    UT_EQ(  0, result );
        result= ms.IndexOfSubstring( "",         4  );    UT_EQ(  4, result );
        result= ms.IndexOfSubstring( "",       100  );    UT_EQ( -1, result );
        result= ms.IndexOf  ( nullptr        );    UT_EQ(  0, result );
        result= ms.IndexOf  ( nullptr,    5  );    UT_EQ(  5, result );
        result= ms.IndexOf  ( nullptr,   50  );    UT_EQ( -1, result );
        result= ms.IndexOf  ( nullptr, -  5  );    UT_EQ(  0, result );
        result= ms.IndexOf  ( "",      -  5  );    UT_EQ(  0, result );
        result= ms.IndexOf  ( "",         0  );    UT_EQ(  0, result );
        result= ms.IndexOf  ( "",         4  );    UT_EQ(  4, result );
        result= ms.IndexOf  ( "",       100  );    UT_EQ( -1, result );
    }

    // search
    {
        TString ms("abcd abcd");
        result= ms.IndexOfSubstring                        ( "abcd"       );  UT_EQ( result,   0 );
        result= ms.IndexOfSubstring                        ( "b"          );  UT_EQ( result,   1 );
        result= ms.IndexOfSubstring                        ( " abcd"      );  UT_EQ( result,   4 );
        result= ms.IndexOfSubstring                        ( "abcd",     1);  UT_EQ( result,   5 );
        result= ms.IndexOfSubstring                        ( "abcd",   - 1);  UT_EQ( result,   0 );
        result= ms.IndexOfSubstring                        ( "xyz",    -10);  UT_EQ( result,  -1 );
        result= ms.IndexOfSubstring<Case::Sensitive, false>( "abcd"       );  UT_EQ( result,   0 );
        result= ms.IndexOfSubstring<Case::Sensitive, false>( "b"          );  UT_EQ( result,   1 );
        result= ms.IndexOfSubstring<Case::Sensitive, false>( " abcd"      );  UT_EQ( result,   4 );
        result= ms.IndexOfSubstring<Case::Sensitive, false>( "abcd",     1);  UT_EQ( result,   5 );
        result= ms.IndexOf                                 ( "abcd"       );  UT_EQ( result,   0 );
        result= ms.IndexOf                                 ( "b"          );  UT_EQ( result,   1 );
        result= ms.IndexOf                                 ( " abcd"      );  UT_EQ( result,   4 );
        result= ms.IndexOf                                 ( "abcd",     1);  UT_EQ( result,   5 );
        result= ms.IndexOf                                 ( "abcd",   - 1);  UT_EQ( result,   0 );
        result= ms.IndexOf                                 ( "xyz",    -10);  UT_EQ( result,  -1 );
        result= ms.IndexOf         <Case::Sensitive, false>( "abcd"       );  UT_EQ( result,   0 );
        result= ms.IndexOf         <Case::Sensitive, false>( "b"          );  UT_EQ( result,   1 );
        result= ms.IndexOf         <Case::Sensitive, false>( " abcd"      );  UT_EQ( result,   4 );
        result= ms.IndexOf         <Case::Sensitive, false>( "abcd",     1);  UT_EQ( result,   5 );
    }

    // ignore case
    {
        AString ms( "Hello A-Worx utilXXX" );
        ms.DeleteEnd(3);
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "a-worx",    0 ); UT_EQ( result,  6 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "a-worx",    1 ); UT_EQ( result,  6 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "a-worx",  -10 ); UT_EQ( result,  6 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "a-worx",    6 ); UT_EQ( result,  6 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "a-worx",    7 ); UT_EQ( result, -1 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "a-worx",  100 ); UT_EQ( result, -1 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "hel",       0 ); UT_EQ( result,  0 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "hel",       1 ); UT_EQ( result, -1 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "util",      1 ); UT_EQ( result, 13 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "UTIL",      5 ); UT_EQ( result, 13 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "UTIL",     13 ); UT_EQ( result, 13 );
        result= ms.IndexOfSubstring<Case::Ignore   , true >( "UTIL",     14 ); UT_EQ( result, -1 );
        result= ms.IndexOfSubstring<Case::Ignore   , false>( "a-worx",    0 ); UT_EQ( result,  6 );
        result= ms.IndexOfSubstring<Case::Ignore   , false>( "a-worx",    1 ); UT_EQ( result,  6 );
        result= ms.IndexOfSubstring<Case::Ignore   , false>( "a-worx",    6 ); UT_EQ( result,  6 );
        result= ms.IndexOfSubstring<Case::Ignore   , false>( "a-worx",    7 ); UT_EQ( result, -1 );
        result= ms.IndexOfSubstring<Case::Ignore   , false>( "hel",       0 ); UT_EQ( result,  0 );
        result= ms.IndexOfSubstring<Case::Ignore   , false>( "hel",       1 ); UT_EQ( result, -1 );
        result= ms.IndexOfSubstring<Case::Ignore   , false>( "util",      1 ); UT_EQ( result, 13 );
        result= ms.IndexOfSubstring<Case::Ignore   , false>( "UTIL",      5 ); UT_EQ( result, 13 );
        result= ms.IndexOfSubstring<Case::Ignore   , false>( "UTIL",     13 ); UT_EQ( result, 13 );
        result= ms.IndexOf         <Case::Ignore          >( "a-worx",    0 ); UT_EQ( result,  6 );
        result= ms.IndexOf         <Case::Ignore          >( "a-worx",    1 ); UT_EQ( result,  6 );
        result= ms.IndexOf         <Case::Ignore          >( "a-worx",  -10 ); UT_EQ( result,  6 );
        result= ms.IndexOf         <Case::Ignore          >( "a-worx",    6 ); UT_EQ( result,  6 );
        result= ms.IndexOf         <Case::Ignore          >( "a-worx",    7 ); UT_EQ( result, -1 );
        result= ms.IndexOf         <Case::Ignore          >( "a-worx",  100 ); UT_EQ( result, -1 );
        result= ms.IndexOf         <Case::Ignore          >( "hel",       0 ); UT_EQ( result,  0 );
        result= ms.IndexOf         <Case::Ignore          >( "hel",       1 ); UT_EQ( result, -1 );
        result= ms.IndexOf         <Case::Ignore          >( "util",      1 ); UT_EQ( result, 13 );
        result= ms.IndexOf         <Case::Ignore          >( "UTIL",      5 ); UT_EQ( result, 13 );
        result= ms.IndexOf         <Case::Ignore          >( "UTIL",     13 ); UT_EQ( result, 13 );
        result= ms.IndexOf         <Case::Ignore          >( "UTIL",     14 ); UT_EQ( result, -1 );
        result= ms.IndexOf         <Case::Ignore   , false>( "a-worx",    0 ); UT_EQ( result,  6 );
        result= ms.IndexOf         <Case::Ignore   , false>( "a-worx",    1 ); UT_EQ( result,  6 );
        result= ms.IndexOf         <Case::Ignore   , false>( "a-worx",    6 ); UT_EQ( result,  6 );
        result= ms.IndexOf         <Case::Ignore   , false>( "a-worx",    7 ); UT_EQ( result, -1 );
        result= ms.IndexOf         <Case::Ignore   , false>( "hel",       0 ); UT_EQ( result,  0 );
        result= ms.IndexOf         <Case::Ignore   , false>( "hel",       1 ); UT_EQ( result, -1 );
        result= ms.IndexOf         <Case::Ignore   , false>( "util",      1 ); UT_EQ( result, 13 );
        result= ms.IndexOf         <Case::Ignore   , false>( "UTIL",      5 ); UT_EQ( result, 13 );
        result= ms.IndexOf         <Case::Ignore   , false>( "UTIL",     13 ); UT_EQ( result, 13 );
    }

    // IndexOfFirstDifference
    {
        String as("abcdef");
        UT_EQ( 6, as.IndexOfFirstDifference("abcdef") );
        UT_EQ( 5, as.IndexOfFirstDifference("abcde") );
        UT_EQ( 6, as.IndexOfFirstDifference("abcdefg") );

        UT_EQ( 0, as.IndexOfFirstDifference("123") );
        UT_EQ( 0, as.IndexOfFirstDifference("123", Case::Ignore   ) );
        UT_EQ( 0, as.IndexOfFirstDifference("123", Case::Ignore, 2) );

        UT_EQ( 3, as.IndexOfFirstDifference("abc") );
        UT_EQ( 3, as.IndexOfFirstDifference("abc", Case::Ignore   ) );
        UT_EQ( 0, as.IndexOfFirstDifference("abc", Case::Ignore, 1) );
        UT_EQ( 0, as.IndexOfFirstDifference( "bc", Case::Ignore, 0) );
        UT_EQ( 2, as.IndexOfFirstDifference( "bc", Case::Ignore, 1) );
        UT_EQ( 1, as.IndexOfFirstDifference( "bd", Case::Ignore, 1) );


        UT_EQ( 3, as.IndexOfFirstDifference("ABC", Case::Ignore   ) );
        UT_EQ( 0, as.IndexOfFirstDifference("ABC", Case::Ignore, 1) );
        UT_EQ( 0, as.IndexOfFirstDifference( "BC", Case::Ignore, 0) );
        UT_EQ( 2, as.IndexOfFirstDifference( "BC", Case::Ignore, 1) );
        UT_EQ( 1, as.IndexOfFirstDifference( "BD", Case::Ignore, 1) );


        UT_EQ( 0, as.IndexOfFirstDifference("ABC") );
        UT_EQ( 0, as.IndexOfFirstDifference("ABC", Case::Sensitive   ) );
        UT_EQ( 0, as.IndexOfFirstDifference("ABC", Case::Sensitive, 1) );
        UT_EQ( 0, as.IndexOfFirstDifference( "BC", Case::Sensitive, 0) );
        UT_EQ( 0, as.IndexOfFirstDifference( "BC", Case::Sensitive, 1) );
        UT_EQ( 0, as.IndexOfFirstDifference( "BD", Case::Sensitive, 1) );
    }

    // replace nullptr
    {
        AString ms("Hello");
        ms.SearchAndReplace( NullString, NullString );     UT_EQ( "Hello" , ms );
        ms.SearchAndReplace( "l",        NullString );     UT_EQ( "Heo"   , ms );
        ms.SearchAndReplace( NullString, "xx"       );     UT_EQ( "Heo"   , ms );
    }

    // SearchAndReplace nullptr
    {
        AString ms("Hello");
        result= ms.SearchAndReplace( NullString,  NullString );  UT_EQ( "Hello" , ms );   UT_EQ( 0, result );
        result= ms.SearchAndReplace( "l",         NullString );  UT_EQ( "Heo"   , ms );   UT_EQ( 2, result );
        result= ms.SearchAndReplace( NullString,  "xx"   );      UT_EQ( "Heo"   , ms );   UT_EQ( 0, result );
    }

    // replace
    {
        AString ms("Hello W!");
        result= ms.SearchAndReplace( "W!",  "world!"   );    UT_EQ( "Hello world!"       ,ms );      UT_EQ( 1, result );
        result= ms.SearchAndReplace( " ",   "* *"      );    UT_EQ( "Hello* *world!"     ,ms );      UT_EQ( 1, result );
        result= ms.SearchAndReplace( "*",   "#", 0, 0  );    UT_EQ( "Hello* *world!"     ,ms );      UT_EQ( 0, result );
        result= ms.SearchAndReplace( "*",   "#", 0, 1  );    UT_EQ( "Hello# *world!"     ,ms );      UT_EQ( 1, result );
        result= ms.SearchAndReplace( "*",   "#"        );    UT_EQ( "Hello# #world!"     ,ms );      UT_EQ( 1, result );
        result= ms.SearchAndReplace( "#",   "$$$"      );    UT_EQ( "Hello$$$ $$$world!" ,ms );      UT_EQ( 2, result );
        result= ms.SearchAndReplace( "$$$", "*"        );    UT_EQ( "Hello* *world!"     ,ms );      UT_EQ( 2, result );
        result= ms.SearchAndReplace( "*",   ""         );    UT_EQ( "Hello world!"       ,ms );      UT_EQ( 2, result );
    }

    // replace one space by two spaces in a string of spaces
    {
        AString ms("     ");
        result= ms.SearchAndReplace( " ",   "  "  );    UT_EQ( "          ", ms  );        UT_EQ( 5, result );
    }

    // replace ignoreCase
    {
        AString ms;
        ms.Clear()._("ABC"); result= ms.SearchAndReplace( "abc",    "xxx",0, 1, Case::Sensitive );    UT_EQ( "ABC", ms );        UT_EQ( 0, result );
        ms.Clear()._("ABC"); result= ms.SearchAndReplace( "abc",    "xxx",0, 1, Case::Ignore    );    UT_EQ( "xxx", ms );        UT_EQ( 1, result );
        ms.Clear()._("ABC"); result= ms.SearchAndReplace( "ABC",    "xxx",0, 1, Case::Ignore    );    UT_EQ( "xxx", ms );        UT_EQ( 1, result );
        ms.Clear()._("abc");         ms.SearchAndReplace( "ABC",    "xxx",0, 1, Case::Sensitive );    UT_EQ( "abc", ms );
        ms.Clear()._("abc");         ms.SearchAndReplace( "ABC",    "xxx",0, 1, Case::Ignore    );    UT_EQ( "xxx", ms );
        ms.Clear()._("abc");         ms.SearchAndReplace( "abc",    "xxx",0, 1, Case::Ignore    );    UT_EQ( "xxx", ms );
    }

}


//--------------------------------------------------------------------------------------------------
//--- Test Trim
//--------------------------------------------------------------------------------------------------
UT_METHOD( Count )
{
    UT_INIT();

    // Count
    String str;

    str= "";
    UT_EQ( 0, str.Count( NullString ) );
    UT_EQ( 0, str.Count( ""  ) );
    UT_EQ( 0, str.Count( "x" ) );

    UT_EQ( 0, str.CountChar( 'x' ) );
    UT_EQ( 0, str.CountChar( '\0') );

    str= "abcdef";
    UT_EQ( 1, str.Count( "a"  ) );   UT_EQ( 1, str.CountChar( 'a'  ) );  UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>( "a"  ) );   UT_EQ( 1, str.CountChar<false>( 'a'  ) );
    UT_EQ( 1, str.Count( "b"  ) );   UT_EQ( 1, str.CountChar( 'b'  ) );  UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>( "b"  ) );   UT_EQ( 1, str.CountChar<false>( 'b'  ) );
    UT_EQ( 1, str.Count( "e"  ) );   UT_EQ( 1, str.CountChar( 'e'  ) );  UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>( "e"  ) );   UT_EQ( 1, str.CountChar<false>( 'e'  ) );
    UT_EQ( 1, str.Count( "f"  ) );   UT_EQ( 1, str.CountChar( 'f'  ) );  UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>( "f"  ) );   UT_EQ( 1, str.CountChar<false>( 'f'  ) );
    UT_EQ( 0, str.Count( "x"  ) );   UT_EQ( 0, str.CountChar( 'x'  ) );  UT_EQ( 0, str.Count<Case::Sensitive ALIB_COMMA false>( "x"  ) );   UT_EQ( 0, str.CountChar<false>( 'x'  ) );
    UT_EQ( 0, str.Count( ""   ) );                                       UT_EQ( 0, str.Count<Case::Sensitive ALIB_COMMA false>( ""   ) );
    UT_EQ( 1, str.Count( "ab" ) );                                       UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>( "ab" ) );
    UT_EQ( 1, str.Count( "bc" ) );                                       UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>( "bc" ) );
    UT_EQ( 1, str.Count( "ef" ) );                                       UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>( "ef" ) );

    UT_EQ( 1, str.Count( "ab", "X" ) );                                  UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>( "ab", "X" ) );
    UT_EQ( 0, str.Count( "ab", "c" ) );                                  UT_EQ( 0, str.Count<Case::Sensitive ALIB_COMMA false>( "ab", "c" ) );
    UT_EQ( 0, str.Count( "ab", ""  ) );                                  UT_EQ( 0, str.Count<Case::Sensitive ALIB_COMMA false>( "ab", ""  ) );

    str= "abcabcabcabc";
    UT_EQ( 1, str.Count( "abcabcabcabc" ) );                                        UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>( "abcabcabcabc" ) );
    UT_EQ( 0, str.Count( "abcabcabcabcX") );                                        UT_EQ( 0, str.Count<Case::Sensitive ALIB_COMMA false>( "abcabcabcabcX") );
    UT_EQ( 1, str.Count(  "bcabcabcabc" ) );                                        UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>(  "bcabcabcabc" ) );
    UT_EQ( 1, str.Count( "abcabcabcab"  ) );                                        UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>( "abcabcabcab"  ) );
    UT_EQ( 1, str.Count(  "bcabcabcab"  ) );                                        UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>(  "bcabcabcab"  ) );
    UT_EQ( 1, str.Count(   "cabcabc"    ) );                                        UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>(   "cabcabc"    ) );
    UT_EQ( 4, str.Count(   "abc"        ) );                                        UT_EQ( 4, str.Count<Case::Sensitive ALIB_COMMA false>(   "abc"        ) );
    UT_EQ( 3, str.Count(   "cab"        ) );                                        UT_EQ( 3, str.Count<Case::Sensitive ALIB_COMMA false>(   "cab"        ) );
    UT_EQ( 4, str.Count(   "ab"         ) );                                        UT_EQ( 4, str.Count<Case::Sensitive ALIB_COMMA false>(   "ab"         ) );
    UT_EQ( 4, str.Count(   "a"          ) ); UT_EQ( 4, str.CountChar('a'      ) );  UT_EQ( 4, str.Count<Case::Sensitive ALIB_COMMA false>(   "a"          ) ); UT_EQ( 4, str.CountChar<false>(   'a'          ) );
    UT_EQ( 0, str.Count(   "a"  ,"b"    ) ); UT_EQ( 0, str.CountChar('a', 'b' ) );  UT_EQ( 0, str.Count<Case::Sensitive ALIB_COMMA false>(   "a" , "b"    ) ); UT_EQ( 0, str.CountChar<false>(   'a' ,'b'     ) );
    UT_EQ( 4, str.Count(   "a"  ,"c"    ) ); UT_EQ( 4, str.CountChar('a', 'c' ) );  UT_EQ( 4, str.Count<Case::Sensitive ALIB_COMMA false>(   "a" , "c"    ) ); UT_EQ( 4, str.CountChar<false>(   'a' ,'c'     ) );
    UT_EQ( 1, str.Count(   "ab" ,"ca"   ) ); UT_EQ( 1, str.CountChar('c', 'a' ) );  UT_EQ( 1, str.Count<Case::Sensitive ALIB_COMMA false>(   "ab" ,"ca"   ) ); UT_EQ( 1, str.CountChar<false>(   'c' ,'a'     ) );
}

//--------------------------------------------------------------------------------------------------
//--- Test Trim
//--------------------------------------------------------------------------------------------------
UT_METHOD( Trim )
{
    UT_INIT();

    AString ms;

    // ------------------ TrimAt ------------------
    {
        for (int i= -2; i < 6; i++ )
        {
            ms.Clear()._("abc").TrimAt( i );
            UT_EQ( "abc", ms );
        }

        ms.Clear()._(" abc").TrimAt( -1 );        UT_EQ( " abc"        , ms );
        ms.Clear()._(" abc").TrimAt(  0 );        UT_EQ( "abc"         , ms );
        ms.Clear()._(" abc").TrimAt(  1 );        UT_EQ( " abc"        , ms );

        ms.Clear()._("abc ").TrimAt( -1 );        UT_EQ( "abc "        , ms );
        ms.Clear()._("abc ").TrimAt(  0 );        UT_EQ( "abc "        , ms );
        ms.Clear()._("abc ").TrimAt(  2 );        UT_EQ( "abc "        , ms );
        ms.Clear()._("abc ").TrimAt(  3 );        UT_EQ( "abc"         , ms );
        ms.Clear()._("abc ").TrimAt(  4 );        UT_EQ( "abc "        , ms );

        ms.Clear()._("a bc").TrimAt( -1 );        UT_EQ( "a bc"        , ms );
        ms.Clear()._("a bc").TrimAt(  0 );        UT_EQ( "a bc"        , ms );
        ms.Clear()._("a bc").TrimAt(  1 );        UT_EQ( "abc"         , ms );
        ms.Clear()._("a bc").TrimAt(  2 );        UT_EQ( "a bc"        , ms );
        ms.Clear()._("a bc").TrimAt(  3 );        UT_EQ( "a bc"        , ms );

        ms.Clear()._("a  c").TrimAt( -1 );        UT_EQ( "a  c"        , ms );
        ms.Clear()._("a  c").TrimAt(  0 );        UT_EQ( "a  c"        , ms );
        ms.Clear()._("a  c").TrimAt(  1 );        UT_EQ( "ac"          , ms );
        ms.Clear()._("a  c").TrimAt(  2 );        UT_EQ( "ac"          , ms );
        ms.Clear()._("a  c").TrimAt(  3 );        UT_EQ( "a  c"        , ms );

        ms.Clear()._(" \t abc \t ").TrimStart();   UT_EQ( "abc \t "     , ms );
                                 ms.TrimEnd();  UT_EQ( "abc"         , ms );
    }

    // ------------------ Trim ------------------
    {
        ms.Clear()._(""          ).Trim();        UT_EQ( ""            , ms );
        ms.Clear()._(' '         ).Trim();        UT_EQ( ""            , ms );
        ms.Clear()._("  "        ).Trim();        UT_EQ( ""            , ms );
        ms.Clear()._("abc"       ).Trim();        UT_EQ( "abc"         , ms );
        ms.Clear()._("abc"       ).Trim();        UT_EQ( "abc"         , ms );
        ms.Clear()._(" abc"      ).Trim();        UT_EQ( "abc"         , ms );
        ms.Clear()._("  abc"     ).Trim();        UT_EQ( "abc"         , ms );
        ms.Clear()._(" \tabc"    ).Trim();        UT_EQ( "abc"         , ms );
        ms.Clear()._("\t abc"    ).Trim();        UT_EQ( "abc"         , ms );
        ms.Clear()._("abc\r\n"   ).Trim();        UT_EQ( "abc"         , ms );
        ms.Clear()._("\tabc\r\n" ).Trim();        UT_EQ( "abc"         , ms );
        ms.Clear()._("\tabc\rx\n" ).Trim();       UT_EQ( "abc\rx"      , ms );
    }
}


//--------------------------------------------------------------------------------------------------
//--- Test Compare
//--------------------------------------------------------------------------------------------------
UT_METHOD( Compare )
{
    UT_INIT();

    // null string comparison
    char*   nullCString= nullptr;

    AString aString;
    UT_TRUE( aString.CompareTo( nullCString) == 0 );
    UT_TRUE( aString.Equals( nullCString) );

    aString= "";
    UT_TRUE( aString.CompareTo( nullCString) != 0 );
    UT_TRUE( !aString.Equals( nullCString) );

    aString= nullCString;
    UT_TRUE( aString.CompareTo( nullCString) == 0 );
    UT_TRUE( aString.Equals( nullCString) );


    // compare/region
    AString ms;

    int result;
    int resultX;
    int intMaxValue= std::numeric_limits<int>::max();
    string t; t= "abcde";
    ms._( t );
    result= ms.CompareTo( t      );                          resultX= t.compare( t );                            UT_EQ( resultX,    result );
    result= ms.CompareTo( string(t).append("x")       );     resultX= t.compare( string(t).append("x") );        UT_EQ( resultX,    result );
    result= ms.CompareTo( t.substr (0, t.size() -1 )  );     resultX= t.compare( t.substr(0, t.size() -1 ) );    UT_EQ( resultX,    result );
    result= ms.CompareTo<true, Case::Sensitive>( "pad" + t,  3            );    UT_EQ(  0,     result );
    result= ms.CompareTo<true, Case::Sensitive>( "pad" + t,  3, 2         );    UT_EQ(  1,     result );
    result= ms.CompareTo<true, Case::Sensitive>( "pad" + t,  3, 100, 0, 4 );    UT_EQ( -1,     result );
    result= ms.CompareTo<true, Case::Sensitive>( "pad" + t,  3, 100, 0, 5 );    UT_EQ(  0,     result );
    result= ms.CompareTo<true, Case::Sensitive>(         t,  2,2,   2,2   );    UT_EQ(  0,     result );
    result= ms.CompareTo<true, Case::Sensitive>(         t,  2,2,   2,1   );    UT_EQ( -1,     result );
    result= ms.CompareTo<true, Case::Sensitive>(         t,  2,2,   2,3   );    UT_EQ(  1,     result );
    result= ms.CompareTo<true, Case::Sensitive>(         t,  -2,5,   -2, 5 );                           UT_EQ( 0,   result );
    result= ms.CompareTo<true, Case::Sensitive>(         t,   2, intMaxValue,    2, intMaxValue );      UT_EQ( 0,   result );
    result= ms.CompareTo<true, Case::Sensitive>(         t,  -2, intMaxValue,   -2, intMaxValue );      UT_EQ( 0,   result );
    result= ms.CompareTo<true, Case::Sensitive>(         t,  -2, 100,           -2, 99 );               UT_EQ( 0,   result );
    result= ms.CompareTo<true, Case::Sensitive>(         t,  -2, 5,             -2, intMaxValue );      UT_EQ( 1,   result );
    result= ms.CompareTo<true, Case::Sensitive>(         t,  -2, intMaxValue,   -2, 5 );                UT_EQ( -1,  result );


    result= ms.CompareTo<false, Case::Sensitive>( "pad" + t,  3, 2         );    UT_EQ(  1,     result );
    result= ms.CompareTo<false, Case::Sensitive>( "pad" + t,  3, 5         );    UT_EQ(  0,     result );
    result= ms.CompareTo<false, Case::Sensitive>( "pad" + t,  3, 6         );    UT_EQ(  -1,    result );
    result= ms.CompareTo<false, Case::Sensitive>(         t,  2,2,   2,2   );    UT_EQ(  0,     result );
    result= ms.CompareTo<false, Case::Sensitive>(         t,  2,2,   2,1   );    UT_EQ( -1,     result );
    result= ms.CompareTo<false, Case::Sensitive>(         t,  2,2,   2,3   );    UT_EQ(  1,     result );


    // greater/smaller strings
    int scRes;
    string greater=  "x";
    string greater2= "abcdef";
    string smaller=  "aaa";
    string smaller2= "abcd";
    result= ms.CompareTo( greater  );   scRes= t.compare( greater  );    UT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) || (result>0 && scRes>0)   );
    result= ms.CompareTo( greater2 );   scRes= t.compare( greater2 );    UT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) || (result>0 && scRes>0)   );
    result= ms.CompareTo( smaller  );   scRes= t.compare( smaller  );    UT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) || (result>0 && scRes>0)   );
    result= ms.CompareTo( smaller2 );   scRes= t.compare( smaller2 );    UT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) || (result>0 && scRes>0)   );
    UT_TRUE ( ms < greater  );
    UT_TRUE ( ms < greater2 );
    UT_TRUE ( ms > smaller  );
    UT_TRUE ( ms > smaller2 );
    UT_FALSE( ms > greater  );
    UT_FALSE( ms > greater2 );
    UT_FALSE( ms < smaller  );
    UT_FALSE( ms < smaller2 );
    UT_TRUE ( ms == ms );
    UT_TRUE ( ms != greater );
    UT_FALSE( ms < ms );
    UT_FALSE( ms > ms );

    // ignore case
    string ABCDE= "ABCDE";
    result= ms.CompareTo                         ( ABCDE               );    UT_TRUE( result >  0 );
    result= ms.CompareTo<true, Case::Sensitive  >( ABCDE               );    UT_TRUE( result >  0 );
    result= ms.CompareTo<true, Case::Ignore     >( ABCDE               );    UT_TRUE( result == 0 );
    result= ms.CompareTo<false                  >( ABCDE               );    UT_TRUE( result >  0 );
    result= ms.CompareTo<false, Case::Sensitive >( ABCDE               );    UT_TRUE( result >  0 );
    result= ms.CompareTo<false, Case::Ignore    >( ABCDE               );    UT_TRUE( result == 0 );
    result= ms.CompareTo<true , Case::Sensitive >( ABCDE,  2,2,   2,2  );    UT_TRUE( result >  0 );
    result= ms.CompareTo<true , Case::Ignore    >( ABCDE,  2,2,   2,2  );    UT_TRUE( result == 0 );
    result= ms.CompareTo<false, Case::Sensitive >( ABCDE,  2,2,   2,2  );    UT_TRUE( result >  0 );
    result= ms.CompareTo<false, Case::Ignore    >( ABCDE,  2,2,   2,2  );    UT_TRUE( result == 0 );

    // we do just a very little testing with StringBuilder and AString parameter version of this function, as
    // the code differences are very small
    const char* cp= t.c_str(); //new StringBuilder(); tSB._( t );
    result= ms.CompareTo<true ,Case::Sensitive>( cp                          );  UT_EQ( 0,   result );
    result= ms.CompareTo<true ,Case::Sensitive>( cp,  -5, 100, -10, 100      );  UT_EQ( 0,   result );
    result= ms.CompareTo<true ,Case::Sensitive>( cp,   2,   3,   2,   3      );  UT_EQ( 0,   result );
    result= ms.CompareTo<false                >( cp,   2,   3,   2,   3      );  UT_EQ( 0,   result );

    AString tAS( t );
    result= ms.CompareTo                        ( tAS      );                     UT_EQ( 0,   result );
    result= ms.CompareTo<true , Case::Sensitive>(tAS,  -5, 100, -10, 100      );  UT_EQ( 0,   result );
    result= ms.CompareTo<true , Case::Sensitive>( cp,   2,   3,   2,   3      );  UT_EQ( 0,   result );
    result= ms.CompareTo<false, Case::Sensitive>( cp,   2,   3,   2,   3      );  UT_EQ( 0,   result );

    // different ranges
    string r1=   "*ABCDEF*";
    string r2= "##*ABCDEF*##";
    ms.Clear()._( r1 );
    result= ms.CompareTo<true , Case::Sensitive>( r2,  2,8          );       UT_EQ( 0,   result );
    result= ms.CompareTo<false, Case::Sensitive>( r2,  2,7          );       UT_EQ( 1,   result );
    result= ms.CompareTo<false, Case::Sensitive>( r2,  2,8          );       UT_EQ( 0,   result );
    result= ms.CompareTo<false, Case::Sensitive>( r2,  2,9          );       UT_EQ(-1,   result );
    result= ms.CompareTo<true , Case::Sensitive>( r2,  3,6,   1,6   );       UT_EQ( 0,   result );
    result= ms.CompareTo<false, Case::Sensitive>( r2,  3,6,   1,6   );       UT_EQ( 0,   result );

    // startsWith/Endswith/ContainsAt
    string sub1=  "ABC";
    string sub2=  "abc";
    string s1=    "ABCDEF";
    string s2=    "123ABC";
    string s3=    "##12ABC21##";
    string s4=    "AB";
    ms.Clear()._( s1 );    UT_TRUE  ( ms.StartsWith                              ( sub1    ) )
                           UT_FALSE ( ms.StartsWith                              ( sub2    ) )
    ms.Clear()._( s2 );    UT_TRUE  ( ms.EndsWith                                ( sub1    ) )
                           UT_FALSE ( ms.EndsWith                                ( sub2    ) )
    ms.Clear()._( s3 );    UT_TRUE  ( ms.ContainsAt                              ( sub1, 4 ) )
                           UT_FALSE ( ms.ContainsAt                              ( sub2, 4 ) )
                           UT_TRUE  ( ms.ContainsAt<true ALIB_COMMA Case::Ignore>( sub2, 4 ) )
    ms.Clear()._( s4 );    UT_FALSE ( ms.ContainsAt                              ( sub1, 4 ) )
                           UT_FALSE ( ms.ContainsAt                              ( sub2, 4 ) )
    ms.Clear()._( s4 );    UT_FALSE ( ms.ContainsAt                              ( sub1, 0 ) )
                           UT_FALSE ( ms.ContainsAt<true ALIB_COMMA Case::Ignore>( sub2, 0 ) )

    ms.Clear()._( "Hello ALib classes" );

    UT_TRUE( ms.StartsWith<Case::Ignore>( "Hello ALib classes"   ) == true  );
    UT_TRUE( ms.EndsWith  <Case::Ignore>( "Hello ALib classes"   ) == true  );
    UT_TRUE( ms.StartsWith<Case::Ignore>( "Hello ALib classesx"  ) == false );
    UT_TRUE( ms.EndsWith  <Case::Ignore>( "xHello ALib classes"  ) == false );
    UT_TRUE( ms.StartsWith<Case::Ignore>( "heLLO"                ) == true  );
    UT_TRUE( ms.StartsWith<Case::Ignore>( "HeLLO"                ) == true  );
    UT_TRUE( ms.EndsWith  <Case::Ignore>( "heLLO"                ) == false );
    UT_TRUE( ms.StartsWith<Case::Ignore>( "CLASSES"              ) == false );
    UT_TRUE( ms.EndsWith  <Case::Ignore>( "CLASSES"              ) == true  );
    UT_TRUE( ms.EndsWith  <Case::Ignore>( "clASSes"              ) == true  );

    // contains with empty/null strings
    ms._()._("AB");             UT_FALSE ( ms.ContainsAt( NullString, -1 )  )
                                UT_FALSE ( ms.ContainsAt( NullString,  0 )  )
                                UT_FALSE ( ms.ContainsAt( NullString,  1 )  )
                                UT_FALSE ( ms.ContainsAt( NullString,  2 )  )
                                UT_FALSE ( ms.ContainsAt( NullString,  3 )  )

                                UT_FALSE ( ms.ContainsAt( "",  -1 )  )
                                UT_TRUE  ( ms.ContainsAt( "",   0 )  )
                                UT_TRUE  ( ms.ContainsAt( "",   1 )  )
                                UT_TRUE  ( ms.ContainsAt( "",   2 )  )
                                UT_FALSE ( ms.ContainsAt( "",   3 )  )
                                UT_FALSE ( ms.ContainsAt( "", 100 )  )

    ms._();                     UT_FALSE ( ms.ContainsAt( NullString, -1 )  )
                                UT_FALSE ( ms.ContainsAt( NullString,  0 )  )
                                UT_FALSE ( ms.ContainsAt( NullString,  1 )  )

                                UT_FALSE ( ms.ContainsAt( "",  -1 )  )
                                UT_TRUE  ( ms.ContainsAt( "",   0 )  )
                                UT_FALSE ( ms.ContainsAt( "",   1 )  )

    // equals String
    ms.Clear()._( "" );         UT_TRUE  ( ms.Equals( string("")   )     )
                                UT_FALSE ( ms.Equals( string("a")  )     )

    ms.Clear()._( "AB" );       UT_FALSE ( ms.Equals( string(""   ))     )
                                UT_FALSE ( ms.Equals( string("ab" ))     )
                                UT_FALSE ( ms.Equals( string("A"  ))     )
                                UT_FALSE ( ms.Equals( string("B"  ))     )
                                UT_TRUE  ( ms.Equals( string("AB" ))     )
                                UT_TRUE  ( ms.Equals( string("AB" ))     )

    // equals AString
    ms.Clear()._( "" );         UT_TRUE  ( ms.Equals( String(""  ))   )
                                UT_FALSE ( ms.Equals( String("a" ))   )

    ms.Clear()._( "AB" );       UT_FALSE ( ms.Equals( String(""  ))   )
                                UT_FALSE ( ms.Equals( String("ab"))   )
                                UT_FALSE ( ms.Equals( String("A" ))   )
                                UT_FALSE ( ms.Equals( String("B" ))   )
                                UT_TRUE  ( ms.Equals( String("AB"))   )
                                UT_TRUE  ( ms.Equals( String("AB"))   )
}

//--------------------------------------------------------------------------------------------------
//--- Test ConvertCase
//--------------------------------------------------------------------------------------------------
UT_METHOD( ConvertCase )
{
    UT_INIT();

    AString ms;

    {
        // test all characters in the 8 bit range
        int testCharRangeStart= 1;
        int testCharRangeEnd=   255;

        string sb;
        for ( int i= testCharRangeStart; i <= testCharRangeEnd ; i++ )
            sb.append( 1, static_cast<char>( i ) );

        string tUpper= sb;    std::transform( tUpper.begin(), tUpper.end(), tUpper.begin(), [](char c) { return  static_cast<char>( ::toupper(c) ); } );
        string tLower= sb;    std::transform( tLower.begin(), tLower.end(), tLower.begin(), [](char c) { return  static_cast<char>( ::tolower(c) ); } );

        ms.Clear()._( sb ).ToLower(); UT_EQ( tLower.c_str(), ms );
        ms.Clear()._( sb ).ToUpper(); UT_EQ( tUpper.c_str(), ms );
    }

    // test substring conversion
    {
        const char* t= "AAAbbb";
        ms.Clear()._( t ).ToLower(  0,  2 );        UT_EQ( "aaAbbb", ms );
        ms.Clear()._( t ).ToLower( -2,  3 );        UT_EQ( "aAAbbb", ms );
        ms.Clear()._( t ).ToLower( -2     );        UT_EQ( "aaabbb", ms );
        ms.Clear()._( t ).ToUpper(  3,  2 );        UT_EQ( "AAABBb", ms );
        ms.Clear()._( t ).ToUpper( -2,  6 );        UT_EQ( "AAABbb", ms );
        ms.Clear()._( t ).ToUpper( -2     );        UT_EQ( "AAABBB", ms );
    }
}

//--------------------------------------------------------------------------------------------------
//--- Test ConvertCase
//--------------------------------------------------------------------------------------------------
void wCharRoundTrip( AString& astring, AWorxUnitTesting& ut, const wchar_t* wstring )
{
    const char*      msgPrefix=      "wchar string to AString: ";
    aworx::integer  msgPrefixLen=   static_cast<aworx::integer>( strlen( msgPrefix ) );

    astring._()._( msgPrefix );
    astring._( wstring );
//    UT_PRINT( astring );

    wchar_t conversionBack[1024];

    UT_TRUE( astring.ToWString( conversionBack, 1024, msgPrefixLen ) >= 0)
    UT_EQ(const_cast<wchar_t*>( wstring ), conversionBack );
}

UT_METHOD( WCharConversion )
{
    UT_INIT();

    AString ms;

    wCharRoundTrip( ms, ut, L"AString" );
    wCharRoundTrip( ms, ut, L"\u20AC" );
    wCharRoundTrip( ms, ut, L"\u03B1\u03B2\u03B3\u03B4\u03B5" );
}


UT_CLASS_END

}; //namespace
