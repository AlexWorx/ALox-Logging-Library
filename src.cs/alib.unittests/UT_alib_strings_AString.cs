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
using cs.aworx.lib.time;
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
    public class CS_Strings_AString    : AUnitTest
    {
        //---------------------------------------------------------------------------------------------------------
        //--- Test Constructors
        //---------------------------------------------------------------------------------------------------------

        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void Constructors()
        {
            AString ms;
            ms= new AString();                        UT_TRUE ( ms.Capacity() ==  0  && ms.Length() == 0 );
            ms= new AString(25);                      UT_TRUE ( ms.Capacity() == 25  && ms.Length() == 0 );
            ms= new AString("Test");                  UT_TRUE ( ms.Capacity() >=  4  && ms.Length() == 4 );

            AString tMSEmpty= new AString ( );

            ms= new AString( (AString) null );        UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() == 0 );
            ms._( "was null" );                  UT_TRUE ( ms.Length() == 8 );
            ms= new AString( tMSEmpty );              UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() > 0 );
            ms= new AString( tMSEmpty, 1,     0 );    UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() > 0 );
            ms= new AString( tMSEmpty, -1000, 0 );    UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() > 0 );
            ms= new AString( tMSEmpty, -1000, 1 );    UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() > 0 );
            ms= new AString( tMSEmpty, -100,  1000);  UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() > 0 );

            AString tMS=        new AString ( "0123456789" );
            ms= new AString( tMS );                   UT_TRUE ( ms.Capacity() >=  10 && ms.Length() == 10 );    UT_EQ( ms, "0123456789");
            ms= new AString( tMS, 5);                 UT_TRUE ( ms.Capacity() >=   5 && ms.Length() ==  5 );    UT_EQ( ms, "56789");
            ms= new AString( tMS, 5, 100);            UT_TRUE ( ms.Capacity() >=   5 && ms.Length() ==  5 );    UT_EQ( ms, "56789");
            ms= new AString( tMS, -5);                UT_TRUE ( ms.Capacity() >=  10 && ms.Length() == 10 );    UT_EQ( ms, "0123456789");
            ms= new AString( tMS, -5,  3);            UT_TRUE ( ms.Capacity() >    0 && ms.Length() ==  0 );    UT_EQ( ms, "");
            ms= new AString( tMS, 50,  3);            UT_TRUE ( ms.Capacity() >    0 && ms.Length() ==  0 );    UT_EQ( ms, "");
            ms= new AString( tMS, 10,  3);            UT_TRUE ( ms.Capacity() >    0 && ms.Length() ==  0 );    UT_EQ( ms, "");
            ms= new AString( tMS, -5, 10);            UT_TRUE ( ms.Capacity() >=   5 && ms.Length() ==  5 );    UT_EQ( ms, "01234");
            ms= new AString( tMS, -5, 100);           UT_TRUE ( ms.Capacity() >=  10 && ms.Length() == 10 );    UT_EQ( ms, "0123456789");

            Substring tSS=     new Substring ( "ABCDE0123456789FG".ToCharArray(), 5,10 );
            ms= new AString( tSS );                       UT_TRUE ( ms.Capacity() >=  10 && ms.Length()  == 10 );        UT_EQ( ms, "0123456789");

            String tS= "0123456789";
            ms= new AString( (String) null );         UT_TRUE ( ms.Length() == 0 ); UT_TRUE ( ms.Capacity() == 0 );
            ms._( "was null" );                  UT_TRUE ( ms.Length() == 8 );
            ms= new AString( "" );                    UT_TRUE ( ms.Length() == 0 ); UT_TRUE ( ms.Capacity() >  0 );
            ms= new AString( "", 1,     0 );          UT_TRUE ( ms.Length() == 0 ); UT_TRUE ( ms.Capacity() >  0 );
            ms= new AString( "", -1000, 0 );          UT_TRUE ( ms.Length() == 0 ); UT_TRUE ( ms.Capacity() >  0 );
            ms= new AString( "", -1000, 1 );          UT_TRUE ( ms.Length() == 0 ); UT_TRUE ( ms.Capacity() > 0 );
            ms= new AString( "", -100,  1000);        UT_TRUE ( ms.Length() == 0 ); UT_TRUE ( ms.Capacity() >  0 );
            ms= new AString( tS );                    UT_TRUE ( ms.Capacity() >=  10 && ms.Length() == 10 );    UT_EQ( ms, "0123456789");
            ms= new AString( tS, 5);                  UT_TRUE ( ms.Capacity() >=   5 && ms.Length() ==  5 );    UT_EQ( ms, "56789");
            ms= new AString( tS, 5, 100);             UT_TRUE ( ms.Capacity() >=   5 && ms.Length() ==  5 );    UT_EQ( ms, "56789");
            ms= new AString( tS, -5);                 UT_TRUE ( ms.Capacity() >=  10 && ms.Length() == 10 );    UT_EQ( ms, "0123456789");
            ms= new AString( tS, -5, 10);             UT_TRUE ( ms.Capacity() >=   5 && ms.Length() ==  5 );    UT_EQ( ms, "01234");
            ms= new AString( tS, -5, 100);            UT_TRUE ( ms.Capacity() >=  10 && ms.Length() == 10 );    UT_EQ( ms, "0123456789");


            StringBuilder tSBEmpty= new StringBuilder ( );
            ms= new AString( (StringBuilder) null ); UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() == 0 );
            ms._( "was null" );                 UT_TRUE ( ms.Length() == 8 );
            ms= new AString( tSBEmpty );             UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() > 0 );
            ms= new AString( tSBEmpty, 1,     0 );   UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() > 0 );
            ms= new AString( tSBEmpty, -1000, 0 );   UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() > 0 );
            ms= new AString( tSBEmpty, -1000, 1 );   UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() > 0 );
            ms= new AString( tSBEmpty, -100,  1000); UT_TRUE ( ms.Length() == 0 );    UT_TRUE ( ms.Capacity() > 0 );

            StringBuilder tSB= new StringBuilder ( "0123456789" );
            ms= new AString( tSB );                  UT_TRUE  ( ms.Capacity() >=  10 && ms.Length() == 10 );
                                                     UT_EQ( ms, "0123456789");
            ms= new AString( tSB, 5);                UT_TRUE  ( ms.Capacity() >=  5  && ms.Length() == 5 );
                                                     UT_EQ( ms, "56789");
            ms= new AString( tSB, 5, 100);           UT_TRUE  ( ms.Capacity() >=  5  && ms.Length() == 5 );
                                                     UT_EQ( ms, "56789");
            ms= new AString( tSB, -5);               UT_TRUE  ( ms.Capacity() >=  10 && ms.Length() == 10 );
                                                     UT_EQ( ms, "0123456789");
            ms= new AString( tSB, -5, 10);           UT_TRUE  ( ms.Capacity() >=  5  && ms.Length() == 5 );
                                                     UT_EQ( ms, "01234");
            ms= new AString( tSB, -5, 100);          UT_TRUE  ( ms.Capacity() >=  10 && ms.Length() == 10 );
                                                     UT_EQ( ms, "0123456789");
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test IsNull
        //---------------------------------------------------------------------------------------------------------
        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void IsNull()
        {
            AString ms
            = new AString();    UT_TRUE( ms.Capacity() == 0 ); UT_TRUE(  ms.IsNull() );  UT_TRUE( !ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
            ms._("");           UT_TRUE( ms.Capacity() != 0 ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
            ms._("x");          UT_TRUE( ms.Capacity() != 0 ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE( !ms.IsEmpty() );  UT_TRUE(  ms.IsNotEmpty() );

            ms.SetNull();       UT_TRUE( ms.Capacity() == 0 ); UT_TRUE(  ms.IsNull() );  UT_TRUE( !ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
            ms._("");           UT_TRUE( ms.Capacity() != 0 ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
            ms._("x");          UT_TRUE( ms.Capacity() != 0 ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE( !ms.IsEmpty() );  UT_TRUE(  ms.IsNotEmpty() );

            ms.SetNull();       UT_TRUE( ms.Capacity() == 0 ); UT_TRUE(  ms.IsNull() );  UT_TRUE( !ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
            ms.SetBuffer(5);    UT_TRUE( ms.Capacity() != 0 ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE(  ms.IsEmpty() );  UT_TRUE( !ms.IsNotEmpty() );
            ms._("x");          UT_TRUE( ms.Capacity() != 0 ); UT_TRUE( !ms.IsNull() );  UT_TRUE(  ms.IsNotNull() );  UT_TRUE( !ms.IsEmpty() );  UT_TRUE(  ms.IsNotEmpty() );
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test FrontEnd
        //---------------------------------------------------------------------------------------------------------
        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void CharAt()
        {
            AString ms= new AString();

            UT_EQ(  ms.CharAtStart   ()    ,    '\0' );
            UT_EQ(  ms.CharAtEnd     ()    ,    '\0' );
            UT_EQ(  ms.CharAt        ( -1 ),    '\0' );
            UT_EQ(  ms.CharAt        (  0 ),    '\0' );
            UT_EQ(  ms.CharAt        (  1 ),    '\0' );

            UT_EQ(  ms               [ -1 ],    '\0' );
            UT_EQ(  ms               [  0 ],    '\0' );
            UT_EQ(  ms               [  1 ],    '\0' );

            ms.Clear()._("A");

            UT_EQ(  ms.CharAtStart   ()    ,    'A'  );
            UT_EQ(  ms.CharAtStart_NC()    ,    'A'  );
            UT_EQ(  ms.CharAtEnd     ()    ,    'A'  );
            UT_EQ(  ms.CharAtEnd_NC  ()    ,    'A'  );
            UT_EQ(  ms.CharAt        ( -1 ),    '\0' );
            UT_EQ(  ms.CharAt        (  0 ),    'A'  );
            UT_EQ(  ms.CharAt        (  1 ),    '\0' );
            UT_EQ(  ms.CharAt_NC     (  0 ),    'A'  );

            UT_EQ(  ms               [ -1 ],    '\0' );
            UT_EQ(  ms               [  0 ],    'A'  );
            UT_EQ(  ms               [  1 ],    '\0' );

            ms.Clear()._("ABC");

            UT_EQ(  ms.CharAtStart   ()    ,    'A'  );
            UT_EQ(  ms.CharAtStart_NC()    ,    'A'  );
            UT_EQ(  ms.CharAtEnd     ()    ,    'C'  );
            UT_EQ(  ms.CharAtEnd_NC  ()    ,    'C'  );
            UT_EQ(  ms.CharAt        ( -1 ),    '\0' );
            UT_EQ(  ms.CharAt        (  0 ),    'A'  );
            UT_EQ(  ms.CharAt        (  1 ),    'B'  );
            UT_EQ(  ms.CharAt        (  2 ),    'C'  );
            UT_EQ(  ms.CharAt        (  3 ),    '\0' );

            UT_EQ(  ms.CharAt_NC     (  0 ),    'A'  );
            UT_EQ(  ms.CharAt_NC     (  1 ),    'B'  );
            UT_EQ(  ms.CharAt_NC     (  2 ),    'C'  );

            UT_EQ(  ms               [ -1 ],    '\0' );
            UT_EQ(  ms               [  0 ],    'A'  );
            UT_EQ(  ms               [  1 ],    'B'  );
            UT_EQ(  ms               [  2 ],    'C'  );
            UT_EQ(  ms               [  3 ],    '\0' );

            ms.Clear()._("ABC");
            ms.SetCharAt( -1, '@' );    UT_EQ    ( "ABC",   ms );
            ms.SetCharAt(  0, 'X' );    UT_EQ    ( "XBC",   ms );
            ms.SetCharAt(  1, 'Y' );    UT_EQ    ( "XYC",   ms );
            ms.SetCharAt(  2, 'Z' );    UT_EQ    ( "XYZ",   ms );
            ms.SetCharAt(  3, '$' );    UT_EQ    ( "XYZ",   ms );
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test DeleteInsert
        //---------------------------------------------------------------------------------------------------------
        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void DeleteInsertSet()
        {
            AString ms= new AString();
            // delete
            {
                ms.Clear()._("0123456789");    ms.Delete         (  5           );      UT_EQ( "01234",         ms );
                ms.Clear()._("0123456789");    ms.Delete         (  5,      0   );      UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");    ms.Delete         (  5,     -1   );      UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");    ms.Delete         (  5,      1   );      UT_EQ( "012346789",     ms );
                ms.Clear()._("0123456789");    ms.Delete         (  5,    100   );      UT_EQ( "01234",         ms );
                ms.Clear()._("0123456789");    ms.Delete         (  -5,     10  );      UT_EQ( "56789",         ms );

                ms.Clear()._("0123456789");    ms.Delete_NC      (  5,    5     );      UT_EQ( "01234",         ms );
                ms.Clear()._("0123456789");    ms.Delete_NC      (  0,    5     );      UT_EQ( "56789",         ms );
                ms.Clear()._("0123456789");    ms.Delete_NC      (  0,    1     );      UT_EQ( "123456789",     ms );
                ms.Clear()._("0123456789");    ms.Delete_NC      (  9,    1     );      UT_EQ( "012345678",     ms );

                ms.Clear()._("0123456789");    ms.DeleteStart    (  -2          );      UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart    (  -1          );      UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart    (   0          );      UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart    (   1          );      UT_EQ(  "123456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart    (   2          );      UT_EQ(   "23456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart    (   9          );      UT_EQ(          "9",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart    (  10          );      UT_EQ(           "",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart    (  11          );      UT_EQ(           "",    ms );

                ms.Clear()._("0123456789");    ms.DeleteStart_NC (   0         );       UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart_NC (   1         );       UT_EQ(  "123456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart_NC (   2         );       UT_EQ(   "23456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart_NC (   9         );       UT_EQ(          "9",    ms );
                ms.Clear()._("0123456789");    ms.DeleteStart_NC (  10         );       UT_EQ(           "",    ms );

                ms.Clear()._("0123456789");    ms.DeleteEnd      (  -2          );      UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd      (  -1          );      UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd      (   0          );      UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd      (   1          );      UT_EQ( "012345678" ,    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd      (   2          );      UT_EQ( "01234567"  ,    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd      (   9          );      UT_EQ( "0"         ,    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd      (  10          );      UT_EQ( ""          ,    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd      (  11          );      UT_EQ( ""          ,    ms );

                ms.Clear()._("0123456789");    ms.DeleteEnd_NC   (   0         );       UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd_NC   (   1         );       UT_EQ( "012345678" ,    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd_NC   (   2         );       UT_EQ( "01234567"  ,    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd_NC   (   9         );       UT_EQ( "0"         ,    ms );
                ms.Clear()._("0123456789");    ms.DeleteEnd_NC   (  10         );       UT_EQ( ""          ,    ms );
            }
            // insertChars
           {
                ms.Clear()._("0123456789");    ms.InsertChars    ( ' ',   1,  -1 );     UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");    ms.InsertChars    ( ' ',   1,  20 );     UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");    ms.InsertChars    ( ' ',   0,   0 );     UT_EQ( "0123456789",   ms );

                ms.Clear()._("0123456789");    ms.InsertChars    ( ' ',   1,   0 );     UT_EQ( " 0123456789",  ms );
                ms.Clear()._("0123456789");    ms.InsertChars    ( ' ',   1,   1 );     UT_EQ( "0 123456789",  ms );
                ms.Clear()._("0123456789");    ms.InsertChars    ( ' ',   2,   0 );     UT_EQ( "  0123456789", ms );
                ms.Clear()._("0123456789");    ms.InsertChars    ( ' ',   2,   1 );     UT_EQ( "0  123456789", ms );

                ms.Clear()._("0123456789");    ms.InsertChars    ( ' ',   1,  11 );     UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");    ms.InsertChars    ( ' ',   1,  10 );     UT_EQ( "0123456789 ",  ms );
                ms.Clear()._("0123456789");    ms.InsertChars    ( '@',   3,   5 );     UT_EQ( "01234@@@56789",ms );
            }

            // InsertAt
            {
                ms.Clear()._("0123456789");   ms.InsertAt        ( "TST",  -2 );        UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( "TST",  -1 );        UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( "TST",   0 );        UT_EQ( "TST0123456789", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( "TST",   1 );        UT_EQ( "0TST123456789", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( "TST",   8 );        UT_EQ( "01234567TST89", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( "TST",   9 );        UT_EQ( "012345678TST9", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( "TST",  10 );        UT_EQ( "0123456789TST", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( "TST",  11 );        UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( "TST",  12 );        UT_EQ( "0123456789",    ms );

                AString astr= new AString( "TST" );
                ms.Clear()._("0123456789");   ms.InsertAt        ( astr ,  -2 );        UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( astr ,  -1 );        UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( astr ,   0 );        UT_EQ( "TST0123456789", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( astr ,   1 );        UT_EQ( "0TST123456789", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( astr ,   8 );        UT_EQ( "01234567TST89", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( astr ,   9 );        UT_EQ( "012345678TST9", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( astr ,  10 );        UT_EQ( "0123456789TST", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( astr ,  11 );        UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( astr ,  12 );        UT_EQ( "0123456789",    ms );

                Substring subs= new Substring( "0123TSTxyz".ToCharArray(), 4, 3 );
                ms.Clear()._("0123456789");   ms.InsertAt        ( subs ,  -2 );        UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( subs ,  -1 );        UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( subs ,   0 );        UT_EQ( "TST0123456789", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( subs ,   1 );        UT_EQ( "0TST123456789", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( subs ,   8 );        UT_EQ( "01234567TST89", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( subs ,   9 );        UT_EQ( "012345678TST9", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( subs ,  10 );        UT_EQ( "0123456789TST", ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( subs ,  11 );        UT_EQ( "0123456789",    ms );
                ms.Clear()._("0123456789");   ms.InsertAt        ( subs ,  12 );        UT_EQ( "0123456789",    ms );
            }

            // ReplaceSubstring
            {
                String r= "ABC";
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r,   0,  10)  ;      UT_EQ( "ABC",          ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r, -10, 100)  ;      UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r, -10,  5 )  ;      UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r, -10, 10 )  ;      UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r, -10, 11 )  ;      UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r,   0,  1 )  ;      UT_EQ( "ABC123456789", ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r,   0,  2 )  ;      UT_EQ( "ABC23456789",  ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r,   1,  1 )  ;      UT_EQ( "0ABC23456789", ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r,   1,  2 )  ;      UT_EQ( "0ABC3456789",  ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r,   8,  1 )  ;      UT_EQ( "01234567ABC9", ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r,   8,  2 )  ;      UT_EQ( "01234567ABC",  ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( r,   8,  3 )  ;      UT_EQ( "0123456789",   ms );

                Substring s= new Substring( "0123ABCxyz".ToCharArray(), 4, 3 );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s,   0,  10)  ;      UT_EQ( "ABC",          ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s, -10, 100)  ;      UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s, -10,  5 )  ;      UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s, -10, 10 )  ;      UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s, -10, 11 )  ;      UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s,   0,  1 )  ;      UT_EQ( "ABC123456789", ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s,   0,  2 )  ;      UT_EQ( "ABC23456789",  ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s,   1,  1 )  ;      UT_EQ( "0ABC23456789", ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s,   1,  2 )  ;      UT_EQ( "0ABC3456789",  ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s,   8,  1 )  ;      UT_EQ( "01234567ABC9", ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s,   8,  2 )  ;      UT_EQ( "01234567ABC",  ms );
                ms.Clear()._("0123456789");   ms.ReplaceSubstring( s,   8,  3 )  ;      UT_EQ( "0123456789",   ms );
            }

            // ReplaceRegion
            {
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@',   0,  10 );      UT_EQ( "@@@@@@@@@@",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@', -10, 100 );      UT_EQ( "@@@@@@@@@@",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@', -10,  5  );      UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@', -10, 10  );      UT_EQ( "0123456789",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@', -10, 11  );      UT_EQ( "@123456789",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@',   0,  1  );      UT_EQ( "@123456789",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@',   0,  2  );      UT_EQ( "@@23456789",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@',   1,  1  );      UT_EQ( "0@23456789",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@',   1,  2  );      UT_EQ( "0@@3456789",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@',   8,  1  );      UT_EQ( "01234567@9",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@',   8,  2  );      UT_EQ( "01234567@@",   ms );
                ms.Clear()._("0123456789");    ms.ReplaceRegion  ( '@',   8,  3  );      UT_EQ( "01234567@@",   ms );
            }


        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test Conversion
        //---------------------------------------------------------------------------------------------------------

        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void Conversion()
        {
            AString   ms;
            String            s;
            ms= new AString("0123456789");
            s= ms.ToString();                    UT_TRUE ( s.Equals("0123456789") );
            s= ms.ToString( 5 );                 UT_TRUE ( s.Equals("56789") );
            s= ms.ToString( 5,  100);            UT_TRUE ( s.Equals("56789") );
            s= ms.ToString( -5);                 UT_TRUE ( s.Equals("0123456789") );
            s= ms.ToString( -5,  10);            UT_TRUE ( s.Equals("01234") );
            s= ms.ToString( -5, 100);            UT_TRUE ( s.Equals("0123456789") );

            s= ms.ToString( 0,    0);            UT_TRUE ( s.Equals("") );
            s= ms.ToString( 5,    0);            UT_TRUE ( s.Equals("") );
            s= ms.ToString( 20,   0);            UT_TRUE ( s.Equals("") );
            s= ms.ToString( 0,   -1);            UT_TRUE ( s.Equals("") );
            s= ms.ToString( 5,   -5);            UT_TRUE ( s.Equals("") );
            s= ms.ToString( 5, -100);            UT_TRUE ( s.Equals("") );
            s= ms.ToString( 20,  -1);            UT_TRUE ( s.Equals("") );
            s= ms.ToString( 20,  20);            UT_TRUE ( s.Equals("") );
            s= ms.ToString( 20,-100);            UT_TRUE ( s.Equals("") );
            s= ms.ToString( 20,   0);            UT_TRUE ( s.Equals("") );
            s= ms.ToString( 20, 100);            UT_TRUE ( s.Equals("") );

            StringBuilder sb= new StringBuilder();
            ms.ToString( sb );                   UT_TRUE ( sb.ToString().Equals("0123456789") );
            ms.ToString( sb, true );             UT_TRUE ( sb.ToString().Equals("01234567890123456789") );
            ms.ToString( sb );                   UT_TRUE ( sb.ToString().Equals("0123456789") );
            ms.ToString( sb, 5, 100 );           UT_TRUE ( sb.ToString().Equals("56789") );
            ms.ToString( sb, -5, 10, true );     UT_TRUE ( sb.ToString().Equals("5678901234") );
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test Append
        //---------------------------------------------------------------------------------------------------------

        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif

        public void _()
        {
            // append char[]
            {
                AString ms= new AString();  char[] csNull= null;  char[] csEmpty= "".ToCharArray();

                ms._( csNull );            UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()    );
                ms._( csEmpty);            UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNotNull() );
                ms.SetNull();                   UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()    );

                ms._("1234567".ToCharArray());  UT_EQ  ( ms.Capacity(), 7 );  UT_EQ( "1234567",   ms );
                ms._("89"     .ToCharArray());  UT_TRUE( ms.Length()> 7     );  UT_EQ( "123456789", ms );

                char[] t= "0123456789".ToCharArray();
                ms.Clear()._   ( t, 5);                     UT_EQ( ms, "56789"      );
                ms.Clear()._   ( t, 5, 100);                UT_EQ( ms, "56789"      );
                ms.Clear()._   ( t, -5);                    UT_EQ( ms, "0123456789" );
                ms.Clear()._   ( t, -5, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._   ( t, 50, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._   ( t, 10, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._   ( t, -5, 10);                UT_EQ( ms, "01234"      );
                ms.Clear()._   ( t, -5, 100);               UT_EQ( ms, "0123456789" );

                // _NC
                ms.SetNull();                  UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()    );
                ms._NC( csEmpty,0,0);    UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()   );
                ms.Clear()._NC( t, 5,3);                   UT_EQ( ms, "567"      );
            }

            // append AString
            {
                AString ms= new AString();  AString asNull= null; AString asEmpty= new AString(""); AString t= new AString( "012" );
                ms._( asNull );            UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()   );
                ms._( asEmpty);            UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNotNull() );
                ms.SetNull();                   UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()    );
                ms._( t );                 UT_EQ  ( ms.Capacity(), 3 );  UT_EQ( "012"   , ms );
                ms._( t );                 UT_TRUE( ms.Length()> 3     );  UT_EQ( "012012", ms );
                t.Clear()._( "0123456789" );
                ms.Clear()._   ( t, 5);                     UT_EQ( ms, "56789"      );
                ms.Clear()._   ( t, 5, 100);                UT_EQ( ms, "56789"      );
                ms.Clear()._   ( t, -5);                    UT_EQ( ms, "0123456789" );
                ms.Clear()._   ( t, -5, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._   ( t, 50, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._   ( t, 10, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._   ( t, -5, 10);                UT_EQ( ms, "01234"      );
                ms.Clear()._   ( t, -5, 100);               UT_EQ( ms, "0123456789" );

                ms.Clear()._NC( t       );                  UT_EQ( ms, "0123456789" );
                ms.Clear()._NC( t, 1, 9 );                  UT_EQ( ms,  "123456789" );
                ms.Clear()._NC( t, 1, 2 );                  UT_EQ( ms,  "12"        );
                ms.Clear()._NC( t, 1, 8 );                  UT_EQ( ms,  "12345678"  );
                ms.Clear()._NC( t, 1, 9 );                  UT_EQ( ms,  "123456789" );
                ms.Clear()._NC( t, 5, 5 );                  UT_EQ( ms,      "56789" );

                // _NC
                ms.SetNull();                  UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()    );
                ms._NC( asEmpty);        UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()   );
                ms.Clear()._NC( t, 5, 3);                  UT_EQ( ms, "567"      );
            }

            // append Substring
            {
                AString ms= new AString();  Substring ssNull= null; Substring ssEmpty= new Substring( "" ); Substring t= new Substring( "01234" );
                ms._( ssNull );            UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()    );
                ms._( ssEmpty);            UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNotNull() );
                ms.SetNull();                   UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()    );
                ms._( t );                 UT_EQ  ( ms.Capacity(), 5 );  UT_EQ( "01234"     , ms );
                ms._( t );                 UT_TRUE( ms.Length()> 5     );  UT_EQ( "0123401234", ms );

                t.Consume();      ms.Clear()._( t );           UT_EQ( ms,  "1234"      );
                t.Consume();      ms.Clear()._( t );           UT_EQ( ms,   "234"      );
                t.ConsumeFromEnd();  ms.Clear()._( t );           UT_EQ( ms,  "23"        );

                // _NC
                ms.SetNull();                   UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()   );
                ms._NC( ssEmpty );        UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()   );
                ms.Clear()._NC( t);                       UT_EQ( ms, "23"   );
            }

            // append String
            {
                AString ms= new AString();   String sEmpty= "";  String t= "012";
                ms._( sEmpty);             UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNotNull() );
                ms.SetNull();                   UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()    );
                ms._( t );                 UT_EQ  ( ms.Capacity(), 3 );  UT_EQ( "012"   , ms );
                ms._( t );                 UT_TRUE( ms.Length()> 3     );  UT_EQ( "012012", ms );
                t= "0123456789";
                ms.Clear()._( t, 5);                     UT_EQ( ms, "56789"      );
                ms.Clear()._( t, 5, 100);                UT_EQ( ms, "56789"      );
                ms.Clear()._( t, -5);                    UT_EQ( ms, "0123456789" );
                ms.Clear()._( t, -5, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._( t, 50, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._( t, 10, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._( t, -5, 10);                UT_EQ( ms, "01234"      );
                ms.Clear()._( t, -5, 100);               UT_EQ( ms, "0123456789" );

                // _NC
                ms.SetNull();                   UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()   );
                ms._NC(  sEmpty );        UT_EQ  ( ms.Length(), 0     );  UT_TRUE( ms.IsNull()   );
                ms.Clear()._NC( t);                      UT_EQ( ms, "0123456789"   );
                ms.Clear()._NC( t ,2,3);                 UT_EQ( ms, "234"          );
            }

            // append String Builders
            {
                AString ms= new AString();   StringBuilder t= new StringBuilder( "012");
                ms._( t );                 UT_EQ  ( ms.Capacity(), 3 );  UT_EQ( "012"   , ms );
                ms._( t );                 UT_TRUE( ms.Length()> 3     );  UT_EQ( "012012", ms );
                t.Clear().Append("0123456789");
                ms.Clear()._( t, 5);                     UT_EQ( ms, "56789"      );
                ms.Clear()._( t, 5, 100);                UT_EQ( ms, "56789"      );
                ms.Clear()._( t, -5);                    UT_EQ( ms, "0123456789" );
                ms.Clear()._( t, -5, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._( t, 50, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._( t, 10, 3);                 UT_EQ( ms, ""           );
                ms.Clear()._( t, -5, 10);                UT_EQ( ms, "01234"      );
                ms.Clear()._( t, -5, 100);               UT_EQ( ms, "0123456789" );
            }
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test Capacity
        //---------------------------------------------------------------------------------------------------------

        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void CapacityLength()
        {
            // null-allocated
            {
                String nullString= null;
                AString ms= new AString();              UT_EQ( ms.Capacity(), 0 );
                        ms= new AString( 0 );           UT_EQ( ms.Capacity(), 0 );
                        ms= new AString( nullString );  UT_EQ( ms.Capacity(), 0 );
                ms._( "" );        UT_TRUE( ms.Capacity() > 0 );
            }

            {
                AString ms= new AString( 5 );
                ms._( 'a' );        UT_TRUE ( ms.Capacity() == 5 );
                ms._( 'b' );        UT_TRUE ( ms.Capacity() == 5 );
                ms._( 'c' );        UT_TRUE ( ms.Capacity() == 5 );
                ms._( 'd' );        UT_TRUE ( ms.Capacity() == 5 );
                ms._( 'e' );        UT_TRUE ( ms.Capacity() == 5 );
                ms._( 'x' );
                UT_TRUE ( ms.Capacity() >= 6 );
                UT_EQ( "abcdex", ms );

                ms.EnsureRemainingCapacity( 2000 ); UT_TRUE ( ms.Capacity() >= 2000 );
            }

            {
                AString   ms= new AString();
                int asize;
                ms._( "0123456789" );      UT_EQ    ( ms.Length(), 10 );     UT_TRUE    ( ms.Capacity() >= 10 );

                asize= ms.Capacity();

                Report.GetDefault().PushHaltFlags( false, false );
                    Console.WriteLine( "A warning should follow" );
                    ms.SetLength(20);               UT_EQ    ( ms.Length(), 10 );     UT_EQ  ( ms.Capacity(), asize );    UT_EQ( ms, "0123456789" );

                    ms.SetLength(5);                UT_EQ    ( ms.Length(), 5 );      UT_EQ  ( ms.Capacity(), asize );    UT_EQ( ms, "01234" );
                    ms.SetBuffer(3);            UT_EQ    ( ms.Length(), 3 );      UT_EQ  ( ms.Capacity(), 3  );       UT_EQ( ms, "012" );
                    ms._("ABC");               UT_EQ    ( ms.Length(), 6 );      UT_TRUE( ms.Capacity() >= 6);       UT_EQ( ms, "012ABC" );
                Report.GetDefault().PopHaltFlags();
            }
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test AppendWithPadding
        //---------------------------------------------------------------------------------------------------------

        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void Fields()
        {
            AString ms= new AString();

            // empty fields
            ms.Clear();
            ms.Field().Field( 3, Alignment.Left,     '#' );    UT_EQ( ms, "###"           );
            ms.Field().Field( 4, Alignment.Center,   '*' );    UT_EQ( ms, "###****"       );
            ms.Field().Field( 5, Alignment.Right,    '+' );    UT_EQ( ms, "###****+++++"  );

            // field, alignment left
            ms.Clear();
            ms.Field()._( "A" )        .Field( 5,    Alignment.Left );
            ms.Field()._( "AB" )       .Field( 5,    Alignment.Left );
            ms.Field()._( "ABC" )      .Field( 5,    Alignment.Left );
            ms.Field()._( "ABCD" )     .Field( 5,    Alignment.Left );
            ms.Field()._( "ABCDE" )    .Field( 5,    Alignment.Left );
            ms.Field()._( "ABCDEF" )   .Field( 5,    Alignment.Left );
            ms.Field()._( "ABCDEFG" )  .Field( 5,    Alignment.Left );
            UT_EQ( ms, "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG" );

            // field, alignment right
            ms.Clear();
            ms.Field()._( "A" )        .Field( 5,    Alignment.Right );
            ms.Field()._( "AB" )       .Field( 5,    Alignment.Right );
            ms.Field()._( "ABC" )      .Field( 5 ); // btw: right is default
            ms.Field()._( "ABCD" )     .Field( 5 );
            ms.Field()._( "ABCDE" )    .Field( 5 );
            ms.Field()._( "ABCDEF" )   .Field( 5,    Alignment.Right );
            ms.Field()._( "ABCDEFG" )  .Field( 5,    Alignment.Right );
            UT_EQ( ms, "    A   AB  ABC ABCDABCDEABCDEFABCDEFG" );

            // field, alignment center
            ms.Clear();
            ms.Field()._( "A" )        .Field( 5,    Alignment.Center );
            ms.Field()._( "AB" )       .Field( 5,    Alignment.Center );
            ms.Field()._( "ABC" )      .Field( 5,    Alignment.Center );
            ms.Field()._( "ABCD" )     .Field( 5,    Alignment.Center );
            ms.Field()._( "ABCDE" )    .Field( 5,    Alignment.Center );
            ms.Field()._( "ABCDEF" )   .Field( 5,    Alignment.Center );
            ms.Field()._( "ABCDEFG" )  .Field( 5,    Alignment.Center );
            UT_EQ( ms, "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG" );

            // a nested field
            ms.Clear();
            ms._("***");
                int outerFieldStart= ms.Length();
                ms._( "OS:" )  .Field()._( "Linux" ).Field( 10, Alignment.Right, '-' );
                ms._( " Lang:").Field()._( "en_US" ).Field(  8, Alignment.Right, '-' );
                ms.Field(35, Alignment.Center, '#', outerFieldStart );
            ms._("***");
            UT_EQ( ms, "***####OS:-----Linux Lang:---en_US####***" );
        }



        //---------------------------------------------------------------------------------------------------------
        //--- Test Tabs
        //---------------------------------------------------------------------------------------------------------

        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void Tabs()
        {
            AString ms= new AString();

            // test some bad input
                           ms.Tab(  0,    -1,     '@' );            UT_EQ( "", ms );
            ms.Clear();    ms.Tab(  0,     0,     '@' );            UT_EQ( "", ms );
            ms.Clear();    ms.Tab( -1,     0,     '@' );            UT_EQ( "", ms );
            ms.Clear();    ms.Tab( -1,     0,     '@' );            UT_EQ( "", ms );
            ms.Clear();    ms.Tab( -1,    -1,     '@' );            UT_EQ( "", ms );
            ms.Clear();    ms.Tab( -5,     0,     '@' );            UT_EQ( "", ms );
            ms.Clear();    ms.Tab( -5,  -100,     '@' );            UT_EQ( "", ms );
            ms.Clear();    ms.Tab(  2,  -100,     '@' );            UT_EQ( "", ms );
            ms.Clear();    ms.Tab(  0,     0,     '@' );            UT_EQ( "", ms );
            ms.Clear();    ms.Tab(  1,     0,     '@' );            UT_EQ( "",  ms );
            ms.Clear();    ms.Tab(  1,     1,     '@' );            UT_EQ( "@", ms );
            ms.Clear();    ms.Tab(  0,     1,     '@' );            UT_EQ( "@", ms );


            // minpad 0 (not common, default is 1, tab wont move if on tab position)
            ms.Clear();                        ms.Tab( 2, 0,    '@' )._( '-' );        UT_EQ( "-",   ms);
            ms.Clear();    ms._( 'x' );    ms.Tab( 2, 0,    '@' )._( '-' );        UT_EQ( "x@-", ms);

            // more standard tabs
            ms.Clear();
            ms._( "12" ).Tab( 2 )
              ._( "1"  ).Tab( 2 )
              .Tab(2)
              ._( "@" );
            UT_EQ( "12  1   @", ms );

            ms.Clear();
            ms._( "12" ).Tab( 2, 0 )
              ._( "1"  ).Tab( 2, 0 )
                             .Tab( 2, 0 )
              ._( "@" );
            UT_EQ( "121 @", ms );


            ms.Clear();
            ms._( "12345" ).Tab( 5 )
              ._( "1234" ) .Tab( 5 )
              ._( "123" )  .Tab( 5 )
              ._( "12" )   .Tab( 5 )
              ._( "1" )    .Tab( 5 )
                                .Tab( 5 )
              ._( "@" );
            UT_EQ( "12345     1234 123  12   1         @", ms );

            ms.Clear();
            ms._( "12345" ).Tab( 5, 0 )
              ._( "1234" ) .Tab( 5, 0 )
              ._( "123" )  .Tab( 5, 0 )
              ._( "12" )   .Tab( 5, 0 )
              ._( "1" )    .Tab( 5, 0 )
                                .Tab( 5, 0 )
              ._( "@" );
            UT_EQ( "123451234 123  12   1    @", ms );

            ms.Clear();                         ms.Tab( 0 )._( '-' );        UT_EQ( " -"        , ms );
            ms.Clear();                         ms.Tab( 1 )._( '-' );        UT_EQ( " -"        , ms );
            ms.Clear();                         ms.Tab( 2 )._( '-' );        UT_EQ( "  -"       , ms );
            ms.Clear();                         ms.Tab( 3 )._( '-' );        UT_EQ( "   -"      , ms );
            ms.Clear();    ms._( 'x' );    ms.Tab( 1 )._( '-' );        UT_EQ( "x -"       , ms );
            ms.Clear();    ms._( 'x' );    ms.Tab( 2 )._( '-' );        UT_EQ( "x -"       , ms );
            ms.Clear();    ms._( 'x' );    ms.Tab( 3 )._( '-' );        UT_EQ( "x  -"      , ms );

            // tabs with tab reference set (designed for multi line tabs)
            ms.Clear()._("ABC").NewLine();
            ms._( "12345" ).Tab( 5 )
              ._( "1234" ) .Tab( 5 )
              ._( "123" )  .Tab( 5 )
              ._( "12" )   .Tab( 5 )
              ._( "1" )    .Tab( 5 )
                                .Tab( 5 )
              ._( "@" );
            UT_EQ( "ABC" + Environment.NewLine + "12345     1234 123  12   1         @", ms );

            ms.Clear()._("ABC").NewLine();
            ms._( "12345" ).Tab( 5, 0 )
              ._( "1234" ) .Tab( 5, 0 )
              ._( "123" )  .Tab( 5, 0 )
              ._( "12" )   .Tab( 5, 0 )
              ._( "1" )    .Tab( 5, 0 )
                                .Tab( 5, 0 )
              ._( "@" );
            UT_EQ( "ABC" + Environment.NewLine + "123451234 123  12   1    @", ms );
        }


        //---------------------------------------------------------------------------------------------------------
        //--- Test SearchAndReplace
        //---------------------------------------------------------------------------------------------------------

        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void SearchAndReplace()
        {
            AString ms= new AString();
            int result;

            // SearchAndReplace null
            ms.Clear()._("Hello");
            {
                String s= null;
                ms.SearchAndReplace( s,     s );        UT_EQ( ms, "Hello" );
                ms.SearchAndReplace( "l",   s );        UT_EQ( ms, "Heo" );
                ms.SearchAndReplace( s,     "xx" );     UT_EQ( ms, "Heo" );
            }

            ms.Clear()._("Hello");
            {
                result= ms.SearchAndReplace( (AString) null,        (AString) null );        UT_EQ( ms, "Hello" );      UT_EQ( 0, result );
                result= ms.SearchAndReplace( new AString("l"),      (AString) null );        UT_EQ( ms, "Heo" );        UT_EQ( 2, result );
                result= ms.SearchAndReplace( (AString) null,        new AString("xx") );     UT_EQ( ms, "Heo" );        UT_EQ( 0, result );
            }

            ms.Clear()._("Hello");
            {
                result= ms.SearchAndReplace( (String) null,          (String) null );        UT_EQ( ms, "Hello" );      UT_EQ( 0, result );
                result= ms.SearchAndReplace( "l",                    (String) null );        UT_EQ( ms, "Heo" );        UT_EQ( 2, result );
                result= ms.SearchAndReplace( (String) null,          "xx"    );              UT_EQ( ms, "Heo" );        UT_EQ( 0, result );
            }

            // SearchAndReplace
            ms.Clear()._("Hello W!");
            {

                result= ms.SearchAndReplace( "W!",    "world!"  );    UT_EQ( ms, "Hello world!" );          UT_EQ( 1, result );
                result= ms.SearchAndReplace( " ",    "* *"      );    UT_EQ( ms, "Hello* *world!" );        UT_EQ( 1, result );
                result= ms.SearchAndReplace( "*",    "#", 0, 1  );    UT_EQ( ms, "Hello# *world!" );        UT_EQ( 1, result );
                result= ms.SearchAndReplace( "*",    "#"        );    UT_EQ( ms, "Hello# #world!" );        UT_EQ( 1, result );
                result= ms.SearchAndReplace( "#",    "$$$"      );    UT_EQ( ms, "Hello$$$ $$$world!" );    UT_EQ( 2, result );
                result= ms.SearchAndReplace( "$$$",    "*"      );    UT_EQ( ms, "Hello* *world!" );        UT_EQ( 2, result );
                result= ms.SearchAndReplace( "*",    ""         );    UT_EQ( ms, "Hello world!" );          UT_EQ( 2, result );
            }

            // replace one space by two spaces in a string of spaces
            ms.Clear()._("     ");
            {
                result= ms.SearchAndReplace( " ",    "  "  );    UT_EQ( ms, "          " );        UT_EQ( 5, result );
            }

            // replace ignoreCase
            {
                ms.Clear()._("ABC"); result= ms.SearchAndReplace( "abc",    "xxx",0, 1, Case.Sensitive );    UT_EQ( ms, "ABC" );        UT_EQ( 0, result );
                ms.Clear()._("ABC"); result= ms.SearchAndReplace( "abc",    "xxx",0, 1, Case.Ignore  );    UT_EQ( ms, "xxx" );        UT_EQ( 1, result );
                ms.Clear()._("ABC"); result= ms.SearchAndReplace( "ABC",    "xxx",0, 1, Case.Ignore  );    UT_EQ( ms, "xxx" );        UT_EQ( 1, result );

                ms.Clear()._("abc");         ms.SearchAndReplace( "ABC",    "xxx",0, 1, Case.Sensitive );    UT_EQ( ms, "abc" );
                ms.Clear()._("abc");         ms.SearchAndReplace( "ABC",    "xxx",0, 1, Case.Ignore  );    UT_EQ( ms, "xxx" );
                ms.Clear()._("abc");         ms.SearchAndReplace( "abc",    "xxx",0, 1, Case.Ignore  );    UT_EQ( ms, "xxx" );
            }

        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test SearchAndReplace
        //---------------------------------------------------------------------------------------------------------

        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void Trim()
        {
            AString ms= new AString();

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

                ms.Clear()._(" \t abc \t ").TrimStart();  UT_EQ( "abc \t "     , ms );
                                         ms.TrimEnd();    UT_EQ( "abc"         , ms );

            }

            // ------------------ Trim ------------------
            {
                ms.Clear()._(""          ).Trim();        UT_EQ( ""            , ms );
                ms.Clear()._(" "         ).Trim();        UT_EQ( ""            , ms );
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

        //---------------------------------------------------------------------------------------------------------
        //--- Test Compare
        //---------------------------------------------------------------------------------------------------------

        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void CompareTo()
        {
            // null string comparison
            String  nullString= null;
            AString aString= new AString(0);
            UT_TRUE( aString.CompareTo( nullString) == 0 );
            UT_TRUE( aString.Equals( nullString) );

            aString._( "" );
            UT_TRUE( aString.CompareTo( nullString) != 0 );
            UT_TRUE( !aString.Equals( nullString) );

            aString.SetBuffer( 0 );
            UT_TRUE( aString.CompareTo( nullString) == 0 );
            UT_TRUE( aString.Equals( nullString) );


            AString    ms= new AString();

            int result;

            String t= "abcde";
            ms._( t );
            result= ms.CompareTo( t      );                                      UT_EQ( t.CompareTo( t ),                              result );
            result= ms.CompareTo( t + "x"      );                                UT_EQ( t.CompareTo( t + "x" ),                        result );
            result= ms.CompareTo( t.Substring (0, t.Length -1 )  );              UT_EQ( t.CompareTo( t.Substring (0, t.Length -1 ) ),  result );
            result= ms.CompareTo( "pad" + t,  Case.Sensitive, 3      );                   UT_EQ( 0,                                             result );
            result= ms.CompareTo( "pad" + t,  Case.Sensitive, 3, 2   );                   UT_EQ( 1,                                             result );
            result= ms.CompareTo( "pad" + t,  Case.Sensitive, 3, 100, 0, 4 );             UT_EQ( -1,                                            result );
            result= ms.CompareTo( "pad" + t,  Case.Sensitive, 3, 100, 0, 5 );             UT_EQ( 0,                                             result );
            result= ms.CompareTo( t,          Case.Sensitive, 2,   2, 2, 2      );        UT_EQ( 0,                                             result );
            result= ms.CompareTo( t,          Case.Sensitive, 2,   2, 2, 1      );        UT_EQ( -1,                                            result );
            result= ms.CompareTo( t,          Case.Sensitive, 2,   2, 2, 3      );        UT_EQ( 1,                                             result );

            result= ms.CompareTo( t,          Case.Sensitive, -2,  5,-2, 5 );                             UT_EQ( 0,  result );
            result= ms.CompareTo( t,          Case.Sensitive,  2, int.MaxValue,    2, int.MaxValue );     UT_EQ( 0,  result );
            result= ms.CompareTo( t,          Case.Sensitive, -2, int.MaxValue,   -2, int.MaxValue );     UT_EQ( 0,  result );
            result= ms.CompareTo( t,          Case.Sensitive, -2, 100,            -2, 99 );               UT_EQ( 0,  result );
            result= ms.CompareTo( t,          Case.Sensitive, -2, 5,              -2, int.MaxValue );     UT_EQ( 1,  result );
            result= ms.CompareTo( t,          Case.Sensitive, -2, int.MaxValue,   -2, 5 );                UT_EQ(-1,  result );

            // greater/smaller strings
            int scRes;
            String greater=     "x";
            String greater2= "abcdef";
            String smaller=  "aaa";
            String smaller2= "abcd";
            result= ms.CompareTo( greater  );            scRes=    t.CompareTo( greater  );    UT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );
            result= ms.CompareTo( greater2 );            scRes=    t.CompareTo( greater2 );    UT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );
            result= ms.CompareTo( smaller  );            scRes=    t.CompareTo( smaller  );    UT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );
            result= ms.CompareTo( smaller2 );            scRes=    t.CompareTo( smaller2 );    UT_TRUE( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );

            // ignore case
            String ut= t.ToUpperInvariant();
            result= ms.CompareTo( ut );                              UT_TRUE( result >  0 );
            result= ms.CompareTo( ut, Case.Sensitive );                       UT_TRUE( result >  0 );
            result= ms.CompareTo( ut, Case.Ignore );                        UT_TRUE( result == 0 );
            result= ms.CompareTo( ut, Case.Sensitive, 2,2,   2,2      );      UT_TRUE( result >  0 );
            result= ms.CompareTo( ut, Case.Ignore,  2,2,   2,2      );      UT_TRUE( result == 0 );


            AString tMS= new AString(); tMS._( t );
            result= ms.CompareTo( tMS      );                            UT_EQ( 0,  result );
            result= ms.CompareTo( tMS, Case.Sensitive, -5, 100, -10, 100      );  UT_EQ( 0,  result );
            result= ms.CompareTo( tMS, Case.Sensitive,  2,   3,   2,   3      );  UT_EQ( 0,  result );

            // different ranges
            String r1=   "*ABCDEF*";
            String r2= "##*ABCDEF*##";
            ms.Clear()._( r1 );
            result= ms.CompareTo( r2, Case.Sensitive, 2,8          );             UT_EQ( 0,  result );
            result= ms.CompareTo( r2, Case.Sensitive, 3,6,   1,6   );             UT_EQ( 0,  result );
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test ConvertCase
        //---------------------------------------------------------------------------------------------------------
        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void ConvertCase()
        {
            AString ms= new AString();

            // test all characters in the 16 bit range
            int testCharRangeStart= (int) Char.MinValue;
            int testCharRangeEnd=    (int) Char.MaxValue;

            StringBuilder sb= new StringBuilder( testCharRangeEnd - testCharRangeStart );
            for ( int i= testCharRangeStart; i < testCharRangeEnd ; i++ )
                sb.Append( (char) i );
            String t= sb.ToString();
            String tUpper= t.ToUpperInvariant();
            String tLower= t.ToLowerInvariant();

            ms.Clear()._( t ).ToLower();            UT_TRUE( tLower.Equals( ms.ToString() ) );
            ms.Clear()._( t ).ToUpper();           UT_TRUE( tUpper.Equals( ms.ToString() ) );

            // test substring conversion
            t= "AAAbbb";
            ms.Clear()._( t ).ToLower(  0, 2 );     UT_TRUE( ms.Equals( "aaAbbb" ) );
            ms.Clear()._( t ).ToLower( -2, 3 );     UT_TRUE( ms.Equals( "aAAbbb" ) );
            ms.Clear()._( t ).ToLower( -2    );     UT_TRUE( ms.Equals( "aaabbb" ) );

            ms.Clear()._( t ).ToUpper(  3, 2 );     UT_TRUE( ms.Equals( "AAABBb" ) );
            ms.Clear()._( t ).ToUpper( -2, 6 );     UT_TRUE( ms.Equals( "AAABbb" ) );
            ms.Clear()._( t ).ToUpper( -2    );     UT_TRUE( ms.Equals( "AAABBB" ) );
        }


        //---------------------------------------------------------------------------------------------------------
        //--- Test ConvertIntegers
        //---------------------------------------------------------------------------------------------------------
        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void ConvertIntegers()

        {
            AString a= new AString();
            int pos;
            int posOrig;

            // parse on empty
            a.Clear();
            {
                posOrig= pos= 0;
                UT_EQ(   0,  a.ToInt( posOrig, out pos )  );    UT_EQ( pos, posOrig );
                posOrig= pos= -5;
                UT_EQ(   0,  a.ToInt( posOrig, out pos )  );    UT_EQ( pos, posOrig );
            }

            // parse on non number
            a.Clear()._( "Hello");
            {
                posOrig= pos= 0;    UT_EQ(   0,  a.ToInt( posOrig, out pos )  );    UT_EQ( pos, posOrig );
                posOrig= pos= -5;   UT_EQ(   0,  a.ToInt( posOrig, out pos )  );    UT_EQ( pos, posOrig );
                posOrig= pos= 2;    UT_EQ(   0,  a.ToInt( posOrig, out pos )  );    UT_EQ( pos, posOrig );
            }

            // check that leading whitespaces do not move pointer
            a.Clear()._( "   Hello");
            {
                posOrig= pos= 0;    UT_EQ(   0,  a.ToInt( posOrig, out pos )  );    UT_EQ( pos, posOrig );
                posOrig= pos= -5;   UT_EQ(   0,  a.ToInt( posOrig, out pos )  );    UT_EQ( pos, posOrig );
                posOrig= pos= 2;    UT_EQ(   0,  a.ToInt( posOrig, out pos )  );    UT_EQ( pos, posOrig );
            }

            // parse integers
            {
                a.Clear()._( "123456789");     UT_EQ( 123456789,  a.ToInt  ( 0, out pos ) );      UT_EQ(  0  + a.Length() , pos );
                a.Clear()._( "  123");         UT_EQ( 123,        a.ToInt  ( 0, out pos ) );      UT_EQ(  0  + a.Length() , pos );
                a.Clear()._( "  -23  ");       UT_EQ( -23,        a.ToInt  ( 0, out pos ) );      UT_EQ( -2  + a.Length() , pos );
                a.Clear()._(   "123  ");       UT_EQ( 123,        a.ToInt  ( 0, out pos ) );      UT_EQ( -2  + a.Length() , pos );

                a.Clear()._( "xxx123456789");  UT_EQ( 123456789,  a.ToInt  ( 3, out pos ) );      UT_EQ(  0  + a.Length() , pos );
                a.Clear()._( "xxx  123");      UT_EQ( 123,        a.ToInt  ( 3, out pos ) );      UT_EQ(  0  + a.Length() , pos );
                a.Clear()._( "xxx  123  ");    UT_EQ( 123,        a.ToInt  ( 3, out pos ) );      UT_EQ( -2  + a.Length() , pos );
                a.Clear()._(   "xxx123  ");    UT_EQ( 123,        a.ToInt  ( 3, out pos ) );      UT_EQ( -2  + a.Length() , pos );
            }

                                                                                                            // append int32
            {
                AString ms= new AString();

                uint ui;
                int   i;

                ms.Clear(); ui= 0;              ms._( ui     );   UT_EQ(                    "0",  ms );
                ms.Clear(); ui= 0;              ms._( ui, 1  );   UT_EQ(                    "0",  ms );
                ms.Clear(); ui= 0;              ms._( ui, 3  );   UT_EQ(                  "000",  ms );
                ms.Clear(); ui= 10;             ms._( ui     );   UT_EQ(                   "10",  ms );
                ms.Clear(); ui= 100;            ms._( ui, 1  );   UT_EQ(                  "100",  ms );
                ms.Clear(); ui= 100;            ms._( ui, 3  );   UT_EQ(                  "100",  ms );
                ms.Clear(); ui= 100;            ms._( ui, 4  );   UT_EQ(                 "0100",  ms );
                ms.Clear(); ui= 23;             ms._( ui     );   UT_EQ(                   "23",  ms );
                ms.Clear(); ui= 99;             ms._( ui, 5  );   UT_EQ(                "00099",  ms );
                ms.Clear();  i= 49;             ms._( i      );   UT_EQ(                   "49",  ms );
                ms.Clear();  i= -5;             ms._( i, 5   );   UT_EQ(               "-00005",  ms );
                ms.Clear();  i= -5324;          ms._( i, 2   );   UT_EQ(                "-5324",  ms );
                ms.Clear(); ui= uint.MaxValue;  ms._( ui     );   UT_EQ(           "4294967295",  ms );
                ms.Clear(); ui= uint.MinValue;  ms._( ui     );   UT_EQ(                    "0",  ms );
                ms.Clear();  i=  int.MaxValue;  ms._( i      );   UT_EQ(           "2147483647",  ms );
                ms.Clear();  i=  int.MinValue;  ms._( i      );   UT_EQ(          "-2147483648",  ms );
                ms.Clear(); ui= uint.MaxValue;  ms._( ui, 12 );   UT_EQ(         "004294967295",  ms );
                ms.Clear(); ui= uint.MinValue;  ms._( ui, 12 );   UT_EQ(         "000000000000",  ms );
                ms.Clear();  i=  int.MaxValue;  ms._( i , 12 );   UT_EQ(         "002147483647",  ms );
                ms.Clear();  i=  int.MinValue;  ms._( i , 12 );   UT_EQ(        "-002147483648",  ms );
            }

            // append int64
            {
                AString ms= new AString();

                ulong ui;
                 long  i;

                ms.Clear(); ui= 0;              ms._( ui     );   UT_EQ(                    "0",  ms );
                ms.Clear(); ui= 0;              ms._( ui, 1  );   UT_EQ(                    "0",  ms );
                ms.Clear(); ui= 0;              ms._( ui, 3  );   UT_EQ(                  "000",  ms );
                ms.Clear(); ui= 10;             ms._( ui     );   UT_EQ(                   "10",  ms );
                ms.Clear(); ui= 100;            ms._( ui, 1  );   UT_EQ(                  "100",  ms );
                ms.Clear(); ui= 100;            ms._( ui, 3  );   UT_EQ(                  "100",  ms );
                ms.Clear(); ui= 100;            ms._( ui, 4  );   UT_EQ(                 "0100",  ms );
                ms.Clear(); ui= 23;             ms._( ui     );   UT_EQ(                   "23",  ms );
                ms.Clear(); ui= 99;             ms._( ui, 5  );   UT_EQ(                "00099",  ms );
                ms.Clear();  i= 49;             ms._( i      );   UT_EQ(                   "49",  ms );
                ms.Clear();  i= -5;             ms._( i, 5   );   UT_EQ(               "-00005",  ms );
                ms.Clear();  i= -5324;          ms._( i, 2   );   UT_EQ(                "-5324",  ms );
                ms.Clear(); ui= uint.MaxValue;  ms._( ui     );   UT_EQ(           "4294967295",  ms );
                ms.Clear(); ui= uint.MinValue;  ms._( ui     );   UT_EQ(                    "0",  ms );
                ms.Clear();  i= int.MaxValue;   ms._( i      );   UT_EQ(           "2147483647",  ms );
                ms.Clear();  i= int.MinValue;   ms._( i      );   UT_EQ(          "-2147483648",  ms );
                ms.Clear(); ui= uint.MaxValue;  ms._( ui, 12 );   UT_EQ(         "004294967295",  ms );
                ms.Clear(); ui= uint.MinValue;  ms._( ui, 12 );   UT_EQ(         "000000000000",  ms );
                ms.Clear();  i= int.MaxValue;   ms._( i , 12 );   UT_EQ(         "002147483647",  ms );
                ms.Clear();  i= int.MinValue;   ms._( i , 12 );   UT_EQ(        "-002147483648",  ms );

                ms.Clear(); ui= ulong.MaxValue; ms._( ui     );   UT_EQ( "18446744073709551615",  ms );
                ms.Clear(); ui= ulong.MinValue; ms._( ui     );   UT_EQ(                    "0",  ms );
                ms.Clear();  i= long.MaxValue;  ms._( i      );   UT_EQ(  "9223372036854775807",  ms );
                ms.Clear(); ms.SetBuffer(20);
                             i= long.MinValue;  ms._( i      );   UT_EQ( "-9223372036854775808",  ms );
                ms.Clear();  i= long.MinValue
                                + 75008;        ms._( i      );   UT_EQ( "-9223372036854700800",  ms );
            }

        }


        //---------------------------------------------------------------------------------------------------------
        //--- Test ConvertFloats
        //---------------------------------------------------------------------------------------------------------
        void floatTest( double d, char decimalPoint, int minDigitsBeforeDot, int digitsAfterDot, String expectedString, bool forceScientific= false )
        {
            AString ms= new AString();
            NumberFormat nf= new NumberFormat();
            nf.ForceScientificFormat= forceScientific;
            if ( decimalPoint == '\0' )
            {
                // reset ALIB' number format to reflect current locale
                NumberFormat.Global.SetFromLocale();
                nf.DecimalPointCharacter=   NumberFormat.Global.DecimalPointCharacter;
            }
            else
                nf.DecimalPointCharacter=  decimalPoint;

            nf.MinIntegralDigits= minDigitsBeforeDot;
            nf.FractionalDigits=  digitsAfterDot;

            ms._( d, nf );
            if ( expectedString != null )
            {
                UT_EQ(  expectedString, ms );
            }

            double precision= digitsAfterDot < 0 ?  Math.Pow( 10,  (d != 0.0 ? (int) Math.Floor((Math.Log10( d ) )) : 0 )   - 14 )
                                                 :  Math.Pow( 10,  digitsAfterDot ) / 2.0;

            // check with system parsing (only if system specific decimal point format was given)
            if ( decimalPoint == '\0' )
            {
                double dSystem= 0.0;
                try
                {
                    dSystem= Double.Parse( ms.ToString(), CultureInfo.CurrentCulture );
                }
                catch( Exception )
                {
                    UT_TRUE( digitsAfterDot == 0 ); // this is not really allowed in c# when parsing
                    dSystem= d;
                }
                UT_EQ( d, dSystem, precision );
            }

            // check with aworx parsing
            double dAWorx= ms.ToFloat();
            UT_EQ( d, dAWorx, precision );

        }


        #if ALIB_MONO_DEVELOP
            [Test ()]
        #endif
        #if ALIB_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void ConvertFloats()

        {
            AString a= new AString();
            int pos;
            int posOrig;

            // parse on empty
            a.Clear();
            {
                posOrig= pos= 0;    UT_EQ( 0.0,        a.ToFloat  ( pos )  );             UT_EQ( pos, posOrig );
                posOrig= pos= -5;   UT_EQ( 0.0,        a.ToFloat  ( pos )  );
            }

            // parse on non number
            a.Clear()._( "Hello");
            {
                posOrig= pos= 0;    UT_EQ( 0.0,        a.ToFloat  ( pos )  );
                posOrig= pos= -5;   UT_EQ( 0.0,        a.ToFloat  ( pos )  );
                posOrig= pos= 2;    UT_EQ( 0.0,        a.ToFloat  ( pos )  );
            }

            // check that leading whitespaces do not move pointer
            a.Clear()._( "   Hello");
            {
                posOrig= pos= 0;    UT_EQ( 0.0,        a.ToFloat  ( pos )  );
                posOrig= pos= -5;   UT_EQ( 0.0,        a.ToFloat  ( pos )  );
                posOrig= pos= 2;    UT_EQ( 0.0,        a.ToFloat  ( pos )  );
            }

            // parse floats
            {
                NumberFormat nf= new NumberFormat();

                a.Clear()._( "12345.789");     UT_EQ( 12345.789,        a.ToFloat( 0, out pos, nf ) );  UT_EQ(  0  + a.Length() , pos );

                a.Clear()._( "");              UT_EQ( 0.0,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  0               , pos );
                a.Clear()._( "-");             UT_EQ( 0.0,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  0               , pos );
                a.Clear()._( "-X");            UT_EQ( 0.0,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  0               , pos );
                a.Clear()._( ".");             UT_EQ( 0.0,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  1               , pos );
                a.Clear()._( ".0");            UT_EQ( 0.0,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  2               , pos );
                a.Clear()._( "0.");            UT_EQ( 0.0,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  2               , pos );
                a.Clear()._( ".5");            UT_EQ( 0.5,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  2               , pos );
                a.Clear()._( "5.");            UT_EQ( 5.0,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  2               , pos );
                a.Clear()._( "+0");            UT_EQ( 0.0,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  2               , pos );
                a.Clear()._( "-0");            UT_EQ( 0.0,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  2               , pos );
                a.Clear()._( "+6");            UT_EQ( 6.0,              a.ToFloat( 0, out pos, nf ) );  UT_EQ(  2               , pos );
                a.Clear()._( "-7");            UT_EQ( -7.0,             a.ToFloat( 0, out pos, nf ) );  UT_EQ(  2               , pos );
                a.Clear()._( "-7");            UT_EQ( 7.0,              a.ToFloat( 1, out pos, nf ) );  UT_EQ(  2               , pos );

                a.Clear()._( "+42");           UT_EQ( 42.0,             a.ToFloat( 0, out pos, nf ) );  UT_EQ(  3               , pos );
                a.Clear()._( " -42 ");         UT_EQ(-42.0,             a.ToFloat( 0, out pos, nf ) );  UT_EQ(  4               , pos );
                a.Clear()._( "  +42.  ");      UT_EQ( 42.0,             a.ToFloat( 0, out pos, nf ) );  UT_EQ(  6               , pos );

                a.Clear()._( "  123");         UT_EQ( 123.0,            a.ToFloat( 0, out pos, nf ) );  UT_EQ(  0  + a.Length() , pos );
                a.Clear()._( "  -23  ");       UT_EQ( -23.0,            a.ToFloat( 0, out pos, nf ) );  UT_EQ(  5               , pos );
                a.Clear()._( "123  ");         UT_EQ( 123.0,            a.ToFloat( 0, out pos, nf ) );  UT_EQ(  3               , pos );

                a.Clear()._( "xxx123456789");  UT_EQ( 123456789.0,      a.ToFloat( 3, out pos, nf ) );  UT_EQ(  0  + a.Length() , pos );
                a.Clear()._( "xxx  1.3");      UT_EQ( 1.3,              a.ToFloat( 3, out pos, nf ) );  UT_EQ(  0  + a.Length() , pos );
                a.Clear()._( "xxx  1.3  ");    UT_EQ( 1.3,              a.ToFloat( 3, out pos, nf ) );  UT_EQ(  0  + a.Length()-2 , pos );
                a.Clear()._( "xxx1.3  ");      UT_EQ( 1.3,              a.ToFloat( 3, out pos, nf ) );  UT_EQ(  0  + a.Length()-2 , pos );

                nf.DecimalPointCharacters= "@".ToCharArray();
                a.Clear()._( "-2495@321");     UT_EQ( -2495.321,        a.ToFloat( 0, out pos, nf  ) );  UT_EQ(  0  + a.Length() ,  pos );
            }

            // write floats, non scientific mode
            {
                // digits after dot: -1
                floatTest(     3.0              ,'.' , -1, -1 ,      "3.0"                  );
                floatTest(     3.1              ,'.' , -1, -1 ,      "3.1"                  );
                floatTest(     3.14             ,'.' , -1, -1 ,      "3.14"                 );
                floatTest(     3.145            ,'.' , -1, -1 ,      "3.145"                );
                floatTest(     3.02             ,'.' , -1, -1 ,      "3.02"                 );
                floatTest(     3.001            ,'.' , -1, -1 ,      "3.001"                );
                floatTest(     3.09             ,'.' , -1, -1 ,      "3.09"                 );
                floatTest(     3.009            ,'.' , -1, -1 ,      "3.009"                );

                floatTest(     0.0              ,'.' , -1, -1 ,      "0.0"                  );
                floatTest(     0.1              ,'.' , -1, -1 ,      "0.1"                  );
                floatTest(     0.14             ,'.' , -1, -1 ,      "0.14"                 );
                floatTest(     0.145            ,'.' , -1, -1 ,      "0.145"                );
                floatTest(     0.02             ,'.' , -1, -1 ,      "0.02"                 );
                floatTest(     0.001            ,'.' , -1, -1 ,      "0.001"                );
                floatTest(     0.09             ,'.' , -1, -1 ,      "0.09"                 );
                floatTest(     0.009            ,'.' , -1, -1 ,      "0.009"                );

                // forces scientific notation
                floatTest(     3.0              ,'.' , -1, -1 ,      "3.0E00"              , true );
                floatTest(     3.1              ,'.' , -1, -1 ,      "3.1E00"              , true );
                floatTest(     3.14             ,'.' , -1, -1 ,      "3.14E00"             , true );
                floatTest(     3.145            ,'.' , -1, -1 ,      "3.145E00"            , true );
                floatTest(     3.02             ,'.' , -1, -1 ,      "3.02E00"             , true );
                floatTest(     3.001            ,'.' , -1, -1 ,      "3.001E00"            , true );
                floatTest(     3.09             ,'.' , -1, -1 ,      "3.09E00"             , true );
                floatTest(     3.009            ,'.' , -1, -1 ,      "3.009E00"            , true );

                floatTest(     3.145            ,'.' , -1,  1 ,      "3.1E00"              , true  );
                floatTest(     3.145            ,'.' ,  1,  1 ,      "3.1E00"              , true  );
                floatTest(     3.145            ,'.' ,  5,  3 ,  "00003.145E00"            , true  );
                floatTest(     123.12341234     ,'.' , -1,  6 ,      "1.231234E02"         , true  );
                floatTest(       0.00123123123  ,'.' , -1,  6 ,      "1.231231E-03"        , true  );
                floatTest(       0.321          ,'.' ,  0,  6 ,      "3.210000E-01"        , true  );
                floatTest(     3.789            ,'.' , -1,  1 ,      "3.8E00"              , true  );
                floatTest(     123.78978978     ,'.' , -1,  6 ,      "1.237898E02"         , true  );
                floatTest(       0.00789789789  ,'.' , -1,  6 ,      "7.897898E-03"        , true  );

                // many digits after dot
                //                  123456789 123456789 12345
                double RoundDown= 1.123412341234123412341234;
                floatTest(  RoundDown  ,'.' ,  1,  12 ,   "1.123412341234"       );
                floatTest(  RoundDown  ,'.' ,  1,  13 ,   "1.1234123412341"      );
                floatTest(  RoundDown  ,'.' ,  1,  14 ,   "1.12341234123412"     );
                floatTest(  RoundDown  ,'.' ,  1,  15 ,   "1.123412341234123"    );

                       RoundDown= 0.123412341234123412341234;
                floatTest(  RoundDown  ,'.' ,  1,  12 ,   "0.123412341234"       );
                floatTest(  RoundDown  ,'.' ,  1,  13 ,   "0.1234123412341"      );
                floatTest(  RoundDown  ,'.' ,  1,  14 ,   "0.12341234123412"     );
                floatTest(  RoundDown  ,'.' ,  1,  15 ,   "0.123412341234123"    );

                double RoundUp=   1.678967896789678967896789;
                floatTest(  RoundUp    ,'.' ,  1,  12 ,   "1.678967896790"       );
                floatTest(  RoundUp    ,'.' ,  1,  13 ,   "1.6789678967897"      );
                floatTest(  RoundUp    ,'.' ,  1,  14 ,   "1.67896789678968"     );
                floatTest(  RoundUp    ,'.' ,  1,  15 ,   "1.678967896789679"    );

                       RoundUp=   0.678967896789678967896789;
                floatTest(  RoundUp    ,'.' ,  1,  12 ,   "0.678967896790"       );
                floatTest(  RoundUp    ,'.' ,  1,  13 ,   "0.6789678967897"      );
                floatTest(  RoundUp    ,'.' ,  1,  14 ,   "0.67896789678968"     );
                floatTest(  RoundUp    ,'.' ,  1,  15 ,   "0.678967896789679"    );

                //            123456789 123456789                           123456789 12345
                floatTest(  0.00001234123412341234    ,'.' ,  1,  15 ,   "0.000012341234123"    );
                floatTest(  0.00000123412341234123    ,'.' ,  1,  15 ,   "0.000001234123412"    );
                floatTest(  0.00000012341234123412    ,'.' ,  1,  15 ,   "0.000000123412341"    );
                floatTest(  0.00000001234123412341    ,'.' ,  1,  15 ,   "0.000000012341234"    );
                floatTest(  0.00000000123412341234    ,'.' ,  1,  15 ,   "0.000000001234123"    );
                floatTest(  0.00000000012341234123    ,'.' ,  1,  15 ,   "0.000000000123412"    );
                floatTest(  0.00000000001234123412    ,'.' ,  1,  15 ,   "0.000000000012341"    );
                floatTest(  0.00000000000123412341    ,'.' ,  1,  15 ,   "0.000000000001234"    );
                floatTest(  0.00000000000012341234    ,'.' ,  1,  15 ,   "0.000000000000123"    );
                floatTest(  0.00000000000001234123    ,'.' ,  1,  15 ,   "0.000000000000012"    );
                floatTest(  0.00000000000000123412    ,'.' ,  1,  15 ,   "0.000000000000001"    );
                floatTest(  0.00000000000000012341    ,'.' ,  1,  15 ,   "0.000000000000000"    );
                floatTest(  0.00000000000000001234    ,'.' ,  1,  15 ,   "0.000000000000000"    );

                floatTest(  0.00006789678967896789    ,'.' ,  1,  15 ,   "0.000067896789679"    );
                floatTest(  0.00000678967896789678    ,'.' ,  1,  15 ,   "0.000006789678968"    );
                floatTest(  0.00000067896789678967    ,'.' ,  1,  15 ,   "0.000000678967897"    );
                floatTest(  0.00000006789678967896    ,'.' ,  1,  15 ,   "0.000000067896790"    );
                floatTest(  0.00000000678967896789    ,'.' ,  1,  15 ,   "0.000000006789679"    );
                floatTest(  0.00000000067896789678    ,'.' ,  1,  15 ,   "0.000000000678968"    );
                floatTest(  0.00000000006789678967    ,'.' ,  1,  15 ,   "0.000000000067897"    );
                floatTest(  0.00000000000678967896    ,'.' ,  1,  15 ,   "0.000000000006790"    );
                floatTest(  0.00000000000067896789    ,'.' ,  1,  15 ,   "0.000000000000679"    );
                floatTest(  0.00000000000006789678    ,'.' ,  1,  15 ,   "0.000000000000068"    );
                floatTest(  0.00000000000000678967    ,'.' ,  1,  15 ,   "0.000000000000007"    );
                floatTest(  0.00000000000000067896    ,'.' ,  1,  15 ,   "0.000000000000001"    );
                floatTest(  0.00000000000000006789    ,'.' ,  1,  15 ,   "0.000000000000000"    );
                floatTest(  0.00000000000000000678    ,'.' ,  1,  15 ,   "0.000000000000000"    );

                // digits after dot: 0 or positive
                floatTest(  300.00050000001     ,'.' ,  1,  2 ,   "300.00"               );
                floatTest(  300.00050000001     ,'.' ,  1,  3 ,   "300.001"              );
                floatTest(  300.00050000001     ,'.' ,  1,  4 ,   "300.0005"             );
                floatTest(  300.00050000001     ,'.' ,  1,  5 ,   "300.00050"            );
                floatTest(  300.00050000001     ,'.' ,  1,  6 ,   "300.000500"           );
                floatTest(    5.01              ,'.' ,  1,  3 ,      "5.010"             );


                floatTest(     0.5              ,'.' ,  0,  0 ,       "."                );
                floatTest(     0.5              ,'.' ,  0,  1 ,       ".5"               );
                floatTest(     0.5              ,'.' ,  1,  0 ,      "0."                );
                floatTest(     0.5              ,'.' ,  1,  1 ,      "0.5"               );
                floatTest(     0.5              ,'.' ,  2,  2 ,     "00.50"              );
                floatTest(     0.5              ,'.' ,  3,  3 ,    "000.500"             );
                floatTest(     0.54             ,'.' ,  3,  3 ,    "000.540"             );
                floatTest(     0.543            ,'.' ,  3,  3 ,    "000.543"             );
                floatTest(     0.5432           ,'.' ,  3,  3 ,    "000.543"             );


                floatTest(    23.37             ,'.' ,  2,  1 ,     "23.4"               );
                floatTest(     1.5              ,'.' ,  0,  0 ,      "1."                );
                floatTest(     1.9              ,'.' ,  0,  0 ,      "2."                );
                floatTest(     1.9              ,'.' ,  0,  4 ,      "1.9000"            );
                floatTest(     1.500001         ,'.' ,  0,  0 ,      "2."                );
                floatTest(     1.54             ,'.' ,  3,  3 ,    "001.540"             );
                floatTest(     1.543            ,'.' ,  3,  3 ,    "001.543"             );
                floatTest(     1.5432           ,'.' ,  3,  3 ,    "001.543"             );
                floatTest(    23.37             ,'.' ,  2,  3 ,     "23.370"             );
                floatTest(    12.345            ,'.' ,  0,  3 ,     "12.345"             );
                floatTest(    12.345            ,'.' ,  5,  1 ,  "00012.3"               );
                floatTest(    12.36789          ,'.' ,  5,  1 ,  "00012.4"               );
                floatTest(     1.5              ,'.' ,  0,  0 ,      "1."                );
                floatTest(     1.5              ,'.' ,  1,  0 ,      "1."                );
                floatTest(     1.5              ,'.' ,  0,  1 ,      "1.5"               );
                floatTest(     1.5              ,'.' ,  1,  1 ,      "1.5"               );
                floatTest(     1.5              ,'.' ,  2,  2 ,     "01.50"              );
                floatTest(     1.5              ,'.' ,  3,  3 ,    "001.500"             );
                floatTest(     1.54             ,'.' ,  3,  3 ,    "001.540"             );
                floatTest(     1.543            ,'.' ,  3,  3 ,    "001.543"             );
                floatTest(     1.5432           ,'.' ,  3,  3 ,    "001.543"             );


                floatTest(     0.0              ,'.' ,  0,  0 ,       "."                );
                floatTest(     0.0              ,'.' ,  1,  0 ,      "0."                );
                floatTest(     0.0              ,'.' ,  0,  1 ,       ".0"               );
                floatTest(     0.0              ,'.' ,  1,  1 ,      "0.0"               );
                floatTest(     0.0              ,'.' ,  2,  2 ,     "00.00"              );
                floatTest(    10.0              ,'.' ,  2,  2 ,     "10.00"              );
                floatTest(    23.37             ,'.' ,  2,  1 ,     "23.4"               );
                floatTest(    23.37             ,'.' ,  2,  3 ,     "23.370"             );
                floatTest(    12.345            ,'.' ,  0,  3 ,     "12.345"             );
                floatTest( -   5.1              ,'.' ,  5,  0 , "-00005."                );
                floatTest( -   5.1              ,'.' ,  5,  1 , "-00005.1"               );
                floatTest( -  53.24             ,'.' ,  2,  2 ,    "-53.24"              );
                floatTest( -   0.2              ,'.' ,  1,  3 ,     "-0.200"             );
                floatTest( -   0.6              ,'.' ,  1,  3 ,     "-0.600"             );
                floatTest( -   0.999            ,'.' ,  1,  3 ,     "-0.999"             );

                floatTest(     0.999            ,'.' ,  1,  3 ,      "0.999"             );
                floatTest(     0.99             ,'.' ,  1,  3 ,      "0.990"             );
                floatTest(     0.999            ,'.' ,  1,  3 ,      "0.999"             );
                floatTest(     0.9999           ,'.' ,  1,  3 ,      "1.000"             );
                floatTest(     0.0999           ,'.' ,  2,  3 ,     "00.100"             );
                floatTest(     0.99999          ,'.' ,  1,  3 ,      "1.000"             );
                floatTest(     0.099            ,'.' ,  2,  3 ,     "00.099"             );
                floatTest(     0.0999           ,'.' ,  1,  3 ,      "0.100"             );
                floatTest(     0.09999          ,'.' ,  2,  3 ,     "00.100"             );
                floatTest(     0.999            ,'.' ,  2,  3 ,     "00.999"             );

                floatTest(     0.0099           ,'.' ,  1,  3 ,      "0.010"             );
                floatTest(     0.00999          ,'.' ,  1,  3 ,      "0.010"             );
                floatTest(     0.009            ,'.' ,  1,  3 ,      "0.009"             );
                floatTest(     0.00099          ,'.' ,  1,  3 ,      "0.001"             );
                floatTest(     0.00009          ,'.' ,  1,  3 ,      "0.000"             );

                floatTest(     1.0099           ,'.' ,  1,  3 ,      "1.010"             );
                floatTest(     1.00999          ,'.' ,  1,  3 ,      "1.010"             );
                floatTest(     1.009            ,'.' ,  1,  3 ,      "1.009"             );
                floatTest(     1.00099          ,'.' ,  1,  3 ,      "1.001"             );
                floatTest(     1.00009          ,'.' ,  1,  3 ,      "1.000"             );

                floatTest(     0.00050          ,'.' ,  1,  3 ,      "0.000"             );
                floatTest(     0.00051          ,'.' ,  1,  3 ,      "0.001"             );
                floatTest(     0.00050000001    ,'.' ,  1,  3 ,      "0.001"             );
                floatTest(  300.00050000001     ,'.' ,  1,  3 ,    "300.001"             );

                floatTest(     0.10099          ,'.' ,  1,  4 ,     "0.1010"             );
                floatTest(     0.10099          ,'.' ,  1,  4 ,     "0.1010"             );
                floatTest(     0.00099          ,'.' ,  1,  4 ,     "0.0010"             );
                floatTest(     1.099            ,'.' ,  1,  1 ,     "1.1"                );
                floatTest(     0.00999          ,'.' ,  1,  4 ,     "0.0100"             );



                // roundtrip -3.0 to 3.0 step 0.001
                {
                    for (int digits= -1 ; digits < 5 ; digits++ )
                    {
                        double d= -3.0;
                        double end= 3.0;
                        double inc= 0.001;
                        while ( d <= end )
                        {
                            floatTest( d, '\0' , -1, digits, null );
                            d+= inc;
                        }
                    }
                }

                // roundtrip e-200 to e+200
                {
                    Random r = new Random();
                    for ( int exp= -200 ; exp <= 200 ; exp+=1 )
                    {
                        double expFactor= Math.Pow( 10, exp );

                        for ( int t= 0 ; t <= 1000 ; t++)
                        {
                            // create a random number of type r.rrrrr *10^exp
                            double d= r.NextDouble();
                            while ( d < 1.0 )
                                d*= 10.0;
                            d*= expFactor;
                            if ( (t & 1  ) != 0 )
                                d= -d;

                            floatTest( d, '\0' , -1, -1, null );
                        }
                    }
                }

                // special exponent symbol
                {
                    int dummy;
                    NumberFormat nf= new NumberFormat();
                    nf.DecimalExponentSeparator= "*10^".ToCharArray();
                    AString s= new AString();
                    double v= 7.5E42;
                    s._( v, nf );
                    UT_EQ( s, "7.5*10^42" );
                    double back= s.ToFloat( 0, out dummy, nf );
                    UT_EQ( v, back, 0.0000000001 );
                }
            }
        }
    }
}
