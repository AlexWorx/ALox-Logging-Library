// #################################################################################################
//  cs.aworx.unittests - AWorx Util
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Globalization;
using cs.aworx.lox;
using cs.aworx.lox.loggers;
using cs.aworx.lib.strings;
using cs.aworx.lib.strings.format;
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

//--------------------------------------------------------------------------------------------------
//--- class CS_Strings_Format
//--------------------------------------------------------------------------------------------------
public class CS_Strings_Format  : AWorxUnitTesting
{


//--------------------------------------------------------------------------------------------------
//--- Test ConvertIntegers
//--------------------------------------------------------------------------------------------------
#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings_Format")]
    #endif
#endif
public void Unsorted()

{
    AString a= new AString();
    int pos;
    int posOrig;

    // parse on empty
    a.Clear();
    {
        posOrig= pos= 0;
        UT_EQ(   0,  a.ParseDec( posOrig, out pos )  );    UT_EQ( pos, posOrig );
        posOrig= pos= -5;
        UT_EQ(   0,  a.ParseDec( posOrig, out pos )  );    UT_EQ( pos, posOrig );
    }

    // parse on non number
    a._()._( "Hello");
    {
        posOrig= pos= 0;    UT_EQ(   0,  a.ParseDec( posOrig, out pos )  );    UT_EQ( pos, posOrig );
        posOrig= pos= -5;   UT_EQ(   0,  a.ParseDec( posOrig, out pos )  );    UT_EQ( pos, posOrig );
        posOrig= pos= 2;    UT_EQ(   0,  a.ParseDec( posOrig, out pos )  );    UT_EQ( pos, posOrig );
    }

    // check that leading whitespaces do not move pointer
    a._()._( "   Hello");
    {
        posOrig= pos= 0;    UT_EQ(   0,  a.ParseDec( posOrig, out pos )  );    UT_EQ( pos, posOrig );
        posOrig= pos= -5;   UT_EQ(   0,  a.ParseDec( posOrig, out pos )  );    UT_EQ( pos, posOrig );
        posOrig= pos= 2;    UT_EQ(   0,  a.ParseDec( posOrig, out pos )  );    UT_EQ( pos, posOrig );
    }

    // parse integers
    {
        a._()._( "123456789");     UT_EQ( 123456789,  a.ParseInt  ( 0, out pos ) );      UT_EQ(  0  + a.Length() , pos );
        a._()._( "  123");         UT_EQ( 123,        a.ParseInt  ( 0, out pos ) );      UT_EQ(  0  + a.Length() , pos );
        a._()._( "  -23  ");       UT_EQ( -23,        a.ParseInt  ( 0, out pos ) );      UT_EQ( -2  + a.Length() , pos );
        a._()._(   "123  ");       UT_EQ( 123,        a.ParseInt  ( 0, out pos ) );      UT_EQ( -2  + a.Length() , pos );

        a._()._( "xxx123456789");  UT_EQ( 123456789,  a.ParseInt  ( 3, out pos ) );      UT_EQ(  0  + a.Length() , pos );
        a._()._( "xxx  123");      UT_EQ( 123,        a.ParseInt  ( 3, out pos ) );      UT_EQ(  0  + a.Length() , pos );
        a._()._( "xxx  123  ");    UT_EQ( 123,        a.ParseInt  ( 3, out pos ) );      UT_EQ( -2  + a.Length() , pos );
        a._()._(   "xxx123  ");    UT_EQ( 123,        a.ParseInt  ( 3, out pos ) );      UT_EQ( -2  + a.Length() , pos );
    }

    // parse with grouping symbol
    {
        NumberFormat numberFormat= new NumberFormat();
        numberFormat.WriteGroupChars= true;
        numberFormat.ReadGroupChars= true;
        a._()._( "123,456,789");   UT_EQ( 123456789,  a.ParseInt( 0, numberFormat, out pos ) ); UT_EQ(  0  + a.Length() , pos );
        a._()._( "  1,2,3");       UT_EQ( 123,        a.ParseInt( 0, numberFormat, out pos ) ); UT_EQ(  0  + a.Length() , pos );
        a._()._( " +1,2,,4");      UT_EQ( 124,        a.ParseInt( 0, numberFormat, out pos ) ); UT_EQ(  0  + a.Length() , pos );
        a._()._( "  -2,3  ");     UT_EQ( -23,         a.ParseInt( 0, numberFormat, out pos ) ); UT_EQ( -2  + a.Length() , pos );
        a._()._(   ",123  ");      UT_EQ(   0,        a.ParseInt( 0, numberFormat, out pos ) ); UT_EQ(  0               , pos );
    }


                                                                                                    // append int32
    {
        AString ms= new AString();

        uint ui;
        int   i;
        NumberFormat nf= new NumberFormat();
        nf.WriteGroupChars= true;

        ms.Clear(); ui= 0;              ms._( ui     );   UT_EQ(                    "0",  ms );
        ms.Clear(); ui= 0;              ms._( ui, 1  );   UT_EQ(                    "0",  ms );
        ms.Clear(); ui= 0;              ms._( ui, 3  );   UT_EQ(                  "000",  ms );
        ms.Clear(); ui= 10;             ms._( ui     );   UT_EQ(                   "10",  ms );
        ms.Clear(); ui= 100;            ms._( ui, 1  );   UT_EQ(                  "100",  ms );
        ms.Clear(); ui= 100;            ms._( ui, 3  );   UT_EQ(                  "100",  ms );
        ms.Clear(); ui= 23;             ms._( ui     );   UT_EQ(                   "23",  ms );
        ms.Clear(); ui= 99;             ms._( ui, 5  );   UT_EQ(                "00099",  ms );
        ms.Clear();  i= 49;             ms._( i      );   UT_EQ(                   "49",  ms );
        ms.Clear();  i= -5;             ms._( i, 5   );   UT_EQ(                "-0005",  ms );
        ms.Clear();  i= -5324;          ms._( i, 2   );   UT_EQ(                "-5324",  ms );
        ms.Clear(); ui= uint.MaxValue;  ms._( ui     );   UT_EQ(           "4294967295",  ms );
        ms.Clear(); ui= uint.MinValue;  ms._( ui     );   UT_EQ(                    "0",  ms );
        ms.Clear();  i=  int.MaxValue;  ms._( i      );   UT_EQ(           "2147483647",  ms );
        ms.Clear();  i=  int.MinValue;  ms._( i      );   UT_EQ(          "-2147483648",  ms );
        ms.Clear(); ui= uint.MaxValue;  ms._( ui, 12 );   UT_EQ(         "004294967295",  ms );
        ms.Clear(); ui= uint.MinValue;  ms._( ui, 12 );   UT_EQ(         "000000000000",  ms );
        ms.Clear();  i=  int.MaxValue;  ms._( i , 12 );   UT_EQ(         "002147483647",  ms );
        ms.Clear();  i=  int.MinValue;  ms._( i , 12 );   UT_EQ(         "-02147483648",  ms );


        ms.Clear(); ui= 0;              ms._( ui     , nf);   UT_EQ(                    "0",  ms );
        ms.Clear(); ui= 0;              ms._( ui, 1  , nf);   UT_EQ(                    "0",  ms );
        ms.Clear(); ui= 0;              ms._( ui, 3  , nf);   UT_EQ(                  "000",  ms );
        ms.Clear(); ui= 10;             ms._( ui     , nf);   UT_EQ(                   "10",  ms );
        ms.Clear(); ui= 100;            ms._( ui, 1  , nf);   UT_EQ(                  "100",  ms );
        ms.Clear(); ui= 100;            ms._( ui, 3  , nf);   UT_EQ(                  "100",  ms );
        ms.Clear(); ui= 23;             ms._( ui     , nf);   UT_EQ(                   "23",  ms );
        ms.Clear(); ui= 99;             ms._( ui, 5  , nf);   UT_EQ(                "0,099",  ms );
        ms.Clear();  i= 49;             ms._( i      , nf);   UT_EQ(                   "49",  ms );
        ms.Clear();  i= -5;             ms._( i, 5   , nf);   UT_EQ(                "- 005",  ms );
        ms.Clear();  i= -5324;          ms._( i, 2   , nf);   UT_EQ(               "-5,324",  ms );
        ms.Clear(); ui= uint.MaxValue;  ms._( ui     , nf);   UT_EQ(        "4,294,967,295",  ms );
        ms.Clear(); ui= uint.MinValue;  ms._( ui     , nf);   UT_EQ(                    "0",  ms );
        ms.Clear();  i=  int.MaxValue;  ms._( i      , nf);   UT_EQ(        "2,147,483,647",  ms );
        ms.Clear();  i=  int.MinValue;  ms._( i      , nf);   UT_EQ(       "-2,147,483,648",  ms );
        ms.Clear(); ui= uint.MaxValue;  ms._( ui, 12 , nf);   UT_EQ(        "4,294,967,295",  ms );
        ms.Clear(); ui= uint.MinValue;  ms._( ui, 12 , nf);   UT_EQ(         " 000,000,000",  ms );
        ms.Clear();  i=  int.MaxValue;  ms._( i , 12 , nf);   UT_EQ(        "2,147,483,647",  ms );
        ms.Clear();  i=  int.MinValue;  ms._( i , 12 , nf);   UT_EQ(       "-2,147,483,648",  ms );
    }

    // append int64
    {
        AString ms= new AString();

        ulong ui;
         long  i;

        ui= 0;              ms._()._( ui     );   UT_EQ(                    "0",  ms );
        ui= 0;              ms._()._( ui, 1  );   UT_EQ(                    "0",  ms );
        ui= 0;              ms._()._( ui, 3  );   UT_EQ(                  "000",  ms );
        ui= 10;             ms._()._( ui     );   UT_EQ(                   "10",  ms );
        ui= 100;            ms._()._( ui, 1  );   UT_EQ(                  "100",  ms );
        ui= 100;            ms._()._( ui, 3  );   UT_EQ(                  "100",  ms );
        ui= 100;            ms._()._( ui, 4  );   UT_EQ(                 "0100",  ms );
        ui= 23;             ms._()._( ui     );   UT_EQ(                   "23",  ms );
        ui= 99;             ms._()._( ui, 5  );   UT_EQ(                "00099",  ms );
         i= 49;             ms._()._( i      );   UT_EQ(                   "49",  ms );
         i= -5;             ms._()._( i, 5   );   UT_EQ(               "-0005",  ms );
         i= -5324;          ms._()._( i, 2   );   UT_EQ(               "-5324",  ms );
        ui= uint.MaxValue;  ms._()._( ui     );   UT_EQ(           "4294967295",  ms );
        ui= uint.MinValue;  ms._()._( ui     );   UT_EQ(                    "0",  ms );
         i= int.MaxValue;   ms._()._( i      );   UT_EQ(           "2147483647",  ms );
         i= int.MinValue;   ms._()._( i      );   UT_EQ(          "-2147483648",  ms );
        ui= uint.MaxValue;  ms._()._( ui, 12 );   UT_EQ(         "004294967295",  ms );
        ui= uint.MinValue;  ms._()._( ui, 12 );   UT_EQ(         "000000000000",  ms );
         i= int.MaxValue;   ms._()._( i , 12 );   UT_EQ(         "002147483647",  ms );
         i= int.MinValue;   ms._()._( i , 12 );   UT_EQ(         "-02147483648",  ms );

        ui= ulong.MaxValue; ms._()._( ui     );   UT_EQ( "18446744073709551615",  ms );
        ui= ulong.MinValue; ms._()._( ui     );   UT_EQ(                    "0",  ms );
         i= long.MaxValue;  ms._()._( i      );   UT_EQ(  "9223372036854775807",  ms );
        ms.SetBuffer(20);
         i= long.MinValue;  ms._()._( i      );   UT_EQ( "-9223372036854775808",  ms );
         i= long.MinValue
            + 75008;        ms._()._( i      );   UT_EQ( "-9223372036854700800",  ms );


        NumberFormat nf= new NumberFormat();
        nf.WriteGroupChars= true;
        ui= 0;              ms._()._( ui     , nf );   UT_EQ(                    "0",  ms );
        ui= 0;              ms._()._( ui, 1  , nf );   UT_EQ(                    "0",  ms );
        ui= 0;              ms._()._( ui, 3  , nf );   UT_EQ(                  "000",  ms );
        ui= 10;             ms._()._( ui     , nf );   UT_EQ(                   "10",  ms );
        ui= 100;            ms._()._( ui, 1  , nf );   UT_EQ(                  "100",  ms );
        ui= 100;            ms._()._( ui, 3  , nf );   UT_EQ(                  "100",  ms );
        ui= 100;            ms._()._( ui, 4  , nf );   UT_EQ(                 " 100",  ms );
        ui= 23;             ms._()._( ui     , nf );   UT_EQ(                   "23",  ms );
        ui= 99;             ms._()._( ui, 5  , nf );   UT_EQ(                "0,099",  ms );
         i= 49;             ms._()._( i      , nf );   UT_EQ(                   "49",  ms );
         i= -5;             ms._()._( i, 5   , nf );   UT_EQ(                "- 005",  ms );
         i= -5324;          ms._()._( i, 2   , nf );   UT_EQ(               "-5,324",  ms );
        ui= uint.MaxValue;  ms._()._( ui     , nf );   UT_EQ(        "4,294,967,295",  ms );
        ui= uint.MinValue;  ms._()._( ui     , nf );   UT_EQ(                    "0",  ms );
         i= int.MaxValue;   ms._()._( i      , nf );   UT_EQ(        "2,147,483,647",  ms );
         i= int.MinValue;   ms._()._( i      , nf );   UT_EQ(       "-2,147,483,648",  ms );
        ui= uint.MaxValue;  ms._()._( ui, 12 , nf );   UT_EQ(        "4,294,967,295",  ms );
        ui= uint.MinValue;  ms._()._( ui, 12 , nf );   UT_EQ(         " 000,000,000",  ms );
         i= int.MaxValue;   ms._()._( i , 12 , nf );   UT_EQ(        "2,147,483,647",  ms );
         i= int.MinValue;   ms._()._( i , 12 , nf );   UT_EQ(       "-2,147,483,648",  ms );

        ui= ulong.MaxValue; ms._()._( ui     , nf );   UT_EQ( "18,446,744,073,709,551,615",  ms );
        ui= ulong.MinValue; ms._()._( ui     , nf );   UT_EQ(                    "0",  ms );
         i= long.MaxValue;  ms._()._( i      , nf );   UT_EQ(  "9,223,372,036,854,775,807",  ms );
        ms.SetBuffer(20);
         i= long.MinValue;  ms._()._( i      , nf );   UT_EQ( "-9,223,372,036,854,775,808",  ms );
         i= long.MinValue
            + 75008;        ms._()._( i      , nf );   UT_EQ( "-9,223,372,036,854,700,800",  ms );
    }

    // plus sign
    {
        AString ms= new AString();

        int  i;
        NumberFormat nf= new NumberFormat();

        i= 49;                     ms._()._( i          );  UT_EQ(   "49", ms );
        i= 49; nf.PlusSign=' ';    ms._()._( i, -1, nf  );  UT_EQ(  " 49", ms );
        i= 49; nf.PlusSign='+';    ms._()._( i, -1, nf  );  UT_EQ(  "+49", ms );
        i= 49; nf.PlusSign=' ';    ms._()._( i,  4, nf  );  UT_EQ( " 049", ms );
        i= 49; nf.PlusSign='+';    ms._()._( i,  4, nf  );  UT_EQ( "+049", ms );
    }

    // Group character
    {
        AString ms= new AString();
        long    i;
        ulong   ui;
        NumberFormat nf= new NumberFormat(); nf.WriteGroupChars= true;
        int w;

        w=  3; ms._(); ui=              100;      ms._(  ui , w, nf   );   UT_EQ(                "100",  ms ); UT_EQ( w, ms.Length() );
        w=  4; ms._(); ui=              100;      ms._(  ui , w, nf   );   UT_EQ(               " 100",  ms ); UT_EQ( w, ms.Length() );
        w=  5; ms._(); ui=              100;      ms._(  ui , w, nf   );   UT_EQ(              "0,100",  ms ); UT_EQ( w, ms.Length() );
        w=  7; ms._(); ui=           100000;      ms._(  ui , w, nf   );   UT_EQ(            "100,000",  ms ); UT_EQ( w, ms.Length() );
        w=  8; ms._(); ui=           100000;      ms._(  ui , w, nf   );   UT_EQ(           " 100,000",  ms ); UT_EQ( w, ms.Length() );
        w=  9; ms._(); ui=           100000;      ms._(  ui , w, nf   );   UT_EQ(          "0,100,000",  ms ); UT_EQ( w, ms.Length() );
        w= 11; ms._(); ui=        100000000;      ms._(  ui , w, nf   );   UT_EQ(        "100,000,000",  ms ); UT_EQ( w, ms.Length() );
        w= 12; ms._(); ui=        100000000;      ms._(  ui , w, nf   );   UT_EQ(       " 100,000,000",  ms ); UT_EQ( w, ms.Length() );
        w= 13; ms._(); ui=        100000000;      ms._(  ui , w, nf   );   UT_EQ(      "0,100,000,000",  ms ); UT_EQ( w, ms.Length() );
        w= 15; ms._(); ui=     100000000000;      ms._(  ui , w, nf   );   UT_EQ(    "100,000,000,000",  ms ); UT_EQ( w, ms.Length() );
        w= 16; ms._(); ui=     100000000000;      ms._(  ui , w, nf   );   UT_EQ(   " 100,000,000,000",  ms ); UT_EQ( w, ms.Length() );
        w= 17; ms._(); ui=     100000000000;      ms._(  ui , w, nf   );   UT_EQ(  "0,100,000,000,000",  ms ); UT_EQ( w, ms.Length() );

        w=  3; ms._(); i=     -         100;      ms._(   i , w, nf   );   UT_EQ(               "-100",  ms ); UT_EQ( w+1, ms.Length() );
        w=  4; ms._(); i=     -         100;      ms._(   i , w, nf   );   UT_EQ(               "-100",  ms ); UT_EQ( w  , ms.Length() );
        w=  5; ms._(); i=     -         100;      ms._(   i , w, nf   );   UT_EQ(              "- 100",  ms ); UT_EQ( w  , ms.Length() );
        w=  6; ms._(); i=     -         100;      ms._(   i , w, nf   );   UT_EQ(             "-0,100",  ms ); UT_EQ( w  , ms.Length() );
        w=  7; ms._(); i=     -      100000;      ms._(   i , w, nf   );   UT_EQ(           "-100,000",  ms ); UT_EQ( w+1, ms.Length() );
        w=  8; ms._(); i=     -      100000;      ms._(   i , w, nf   );   UT_EQ(           "-100,000",  ms ); UT_EQ( w  , ms.Length() );
        w=  9; ms._(); i=     -      100000;      ms._(   i , w, nf   );   UT_EQ(          "- 100,000",  ms ); UT_EQ( w  , ms.Length() );
        w= 10; ms._(); i=     -      100000;      ms._(   i , w, nf   );   UT_EQ(         "-0,100,000",  ms ); UT_EQ( w  , ms.Length() );
        w= 11; ms._(); i=     -   100000000;      ms._(   i , w, nf   );   UT_EQ(       "-100,000,000",  ms ); UT_EQ( w+1, ms.Length() );
        w= 12; ms._(); i=     -   100000000;      ms._(   i , w, nf   );   UT_EQ(       "-100,000,000",  ms ); UT_EQ( w  , ms.Length() );
        w= 13; ms._(); i=     -   100000000;      ms._(   i , w, nf   );   UT_EQ(      "- 100,000,000",  ms ); UT_EQ( w  , ms.Length() );
        w= 14; ms._(); i=     -   100000000;      ms._(   i , w, nf   );   UT_EQ(     "-0,100,000,000",  ms ); UT_EQ( w  , ms.Length() );
        w= 15; ms._(); i=     -100000000000;      ms._(   i , w, nf   );   UT_EQ(   "-100,000,000,000",  ms ); UT_EQ( w+1, ms.Length() );
        w= 16; ms._(); i=     -100000000000;      ms._(   i , w, nf   );   UT_EQ(   "-100,000,000,000",  ms ); UT_EQ( w  , ms.Length() );
        w= 17; ms._(); i=     -100000000000;      ms._(   i , w, nf   );   UT_EQ(  "- 100,000,000,000",  ms ); UT_EQ( w  , ms.Length() );
        w= 18; ms._(); i=     -100000000000;      ms._(   i , w, nf   );   UT_EQ( "-0,100,000,000,000",  ms ); UT_EQ( w  , ms.Length() );
    }

}

//--------------------------------------------------------------------------------------------------
//--- Test WriteAndParseInt
//--------------------------------------------------------------------------------------------------

NumberFormat itNF   = new NumberFormat();
AString      itAS   = new AString();
Substring    itSB   = new Substring();

void intTestDetection( String src, long exp, bool parsable, int qtyConsume )
{
    itAS._()._("abc  ")._(src)._("@@@");
    int expNewIdx= 5 + ( qtyConsume >= 0 ? qtyConsume : src.Length );
    int newIdx;
    UT_EQ( exp, itAS.ParseInt( 3, out newIdx ) );
    if( parsable )
    {
        UT_EQ( expNewIdx, newIdx );
    }
    else
    {
        UT_EQ( 3        , newIdx );
    }


    long result;
    itSB.Set(itAS, 3);
    if( parsable )
    {
        UT_TRUE( itSB.ConsumeInt( out result ) );
        UT_EQ( exp, result );
        UT_EQ( 3 + (qtyConsume < 0 ?  0 :  src.Length - qtyConsume), itSB.Length() );
    }
    else
    {
        UT_FALSE( itSB.ConsumeInt( out result ) );
        UT_EQ( itAS.Length() -3, itSB.Length());
    }
}

void intTestRoundtrip( long i )
{

    itAS._();
    long    iBack;
    ulong   uiBack;

            itAS._()._("  ")._( i, itNF );   if( i>=0 ) { iBack= (long) itAS.ParseDec( 2, itNF );      UT_EQ( i, iBack ); }
                                              iBack= itAS.ParseInt(itNF);                        UT_EQ( i, iBack );
                         itSB.Set(itAS);     UT_TRUE(itSB.ConsumeInt( out iBack,itNF));          UT_EQ( i, iBack ); UT_TRUE(itSB.IsEmpty());

    ulong iUL= (ulong) i;

    itAS._()._("0b")._Bin( iUL, itNF );   uiBack= itAS.ParseBin( 2, itNF );             UT_EQ( i, (long) uiBack );
                                           iBack= itAS.ParseInt( itNF  );               UT_EQ( i,         iBack );
                      itSB.Set(itAS, 2);  UT_TRUE(itSB.ConsumeBin(out uiBack,itNF));    UT_EQ( i, (long) uiBack ); UT_TRUE(itSB.IsEmpty());
                      itSB.Set(itAS);     UT_TRUE(itSB.ConsumeInt(out  iBack,itNF));    UT_EQ( i,         iBack ); UT_TRUE(itSB.IsEmpty());

    itAS._()._("0x")._Hex( iUL, itNF );   uiBack= itAS.ParseHex( 2,itNF );              UT_EQ( i, (long) uiBack );
                                           iBack= itAS.ParseInt( itNF  );               UT_EQ( i,         iBack );
                      itSB.Set(itAS, 2);  UT_TRUE(itSB.ConsumeHex(out uiBack,itNF));    UT_EQ( i, (long) uiBack ); UT_TRUE(itSB.IsEmpty());
                      itSB.Set(itAS);     UT_TRUE(itSB.ConsumeInt(out  iBack,itNF));    UT_EQ( i,         iBack ); UT_TRUE(itSB.IsEmpty());

    itAS._()._("0o")._Oct( iUL, itNF );   uiBack= itAS.ParseOct( 2, itNF );             UT_EQ( i, (long) uiBack );
                                           iBack= itAS.ParseInt( itNF  );               UT_EQ( i,         iBack );
                      itSB.Set(itAS, 2);  UT_TRUE(itSB.ConsumeOct(out uiBack,itNF));    UT_EQ( i, (long) uiBack ); UT_TRUE(itSB.IsEmpty());
                      itSB.Set(itAS);     UT_TRUE(itSB.ConsumeInt(out  iBack,itNF));    UT_EQ( i,         iBack ); UT_TRUE(itSB.IsEmpty());
}

void intTestRoundtripUS( ulong i )
{

    itAS._();
    ulong   uiBack;


    itAS._()._("0b")._Bin( i, itNF );     uiBack= itAS.ParseBin( 2,itNF );           UT_EQ( i, uiBack );
                      itSB.Set(itAS, 2);  UT_TRUE(itSB.ConsumeBin(out uiBack,itNF)); UT_EQ( i, uiBack ); UT_TRUE(itSB.IsEmpty());

    itAS._()._("0x")._Hex( i, itNF );     uiBack= itAS.ParseHex( 2,itNF );           UT_EQ( i, uiBack );
                      itSB.Set(itAS, 2);  UT_TRUE(itSB.ConsumeHex(out uiBack,itNF)); UT_EQ( i, uiBack ); UT_TRUE(itSB.IsEmpty());

    itAS._()._("0o")._Oct( i, itNF );     uiBack= itAS.ParseOct( 2,itNF );            UT_EQ( i, uiBack );
                      itSB.Set(itAS, 2);  UT_TRUE(itSB.ConsumeOct(out uiBack,itNF)); UT_EQ( i, uiBack ); UT_TRUE(itSB.IsEmpty());
}



#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings_Format")]
    #endif
#endif
public void ConvertIntegers()
{
    UT_INIT();

    // int detection and string borders
    {
        {
            int result;
            int newIdx;
            Substring substring= new Substring("0x");
            UT_TRUE( substring.ConsumeInt( out result ));
            UT_EQ( 0, result );
            UT_EQ( "x", substring.ToString());

            AString astring= new AString("0x");
            UT_EQ( 0, astring.ParseInt( 0, out newIdx ));
            UT_EQ( 1, newIdx );
        }
        {
            int result;
            int newIdx;
            Substring substring= new Substring("0xy");
            UT_TRUE( substring.ConsumeInt( out result ));
            UT_EQ( 0, result );
            UT_EQ( "xy", substring.ToString());

            AString astring= new AString("0xy");
            UT_EQ( 0, astring.ParseInt( 0, out newIdx ));
            UT_EQ( 1, newIdx );
        }
        {
            int result;
            int newIdx;

            Substring substring= new Substring("0x1234", 0, 2);
            UT_TRUE( substring.ConsumeInt( out result ));
            UT_EQ( 0, result );
            UT_EQ( "x", substring.ToString() );

            AString astring= new AString("0x1234"); astring.SetLength(2);
            UT_EQ( 0,  astring.ParseInt( 0, out newIdx ));
            UT_EQ( 1,  newIdx );
        }

        // the same with leading spaces
        {
            int result;
            int newIdx;
            Substring substring= new Substring("  0x");
            UT_TRUE( substring.ConsumeInt( out result ));
            UT_EQ( 0, result );
            UT_EQ( "x", substring.ToString());

            AString astring= new AString("  0x");
            UT_EQ( 0, astring.ParseInt( 0, out newIdx ));
            UT_EQ( 3, newIdx );
        }
        {
            int result;
            int newIdx;
            Substring substring= new Substring("  0xy");
            UT_TRUE( substring.ConsumeInt( out result ));
            UT_EQ( 0, result );
            UT_EQ( "xy", substring.ToString());

            AString astring= new AString("  0xy");
            UT_EQ( 0, astring.ParseInt( 0, out newIdx ));
            UT_EQ( 3, newIdx );
        }
        {
            int result;
            int newIdx;

            Substring substring= new Substring("  0x1234", 0, 4);
            UT_TRUE( substring.ConsumeInt( out result ));
            UT_EQ( 0, result );
            UT_EQ( "x", substring.ToString() );

            AString astring= new AString("  0x1234"); astring.SetLength(4);
            UT_EQ( 0,  astring.ParseInt( 0, out newIdx ));
            UT_EQ( 3,  newIdx );
        }

    }


    // Negative Int parsing
    intTestDetection( " - 0xF"                  , -15          , true  , -1);
    intTestDetection( " - 0b1"                  ,  -1          , true  , -1);
    intTestDetection( " 0x F12A"                , 0            , true  ,  2);
    intTestDetection( " 0zF12A"                 , 0            , true  ,  2);
    intTestDetection( " - 0xF"                  , -0xF         , true  , -1);
    intTestDetection( " - 0b1"                  ,  -1          , true  , -1);
    intTestDetection( " - 0b111"                ,  -7          , true  , -1);
    intTestDetection( " 0b111F"                 ,   7          , true  ,  6);
    intTestDetection( "0o77"                    ,  63          , true  , -1);
    intTestDetection( " \t 0o777"               ,  511         , true  , -1);
    intTestDetection( " \t0o777"                ,  511         , true  , -1);
    intTestDetection( " \t-0o777"               , -511         , true  , -1);
    intTestDetection( " -\t0o777"               , -511         , true  , -1);
    intTestDetection( " -FF"                    ,  0           , false ,  0);

    // range from -4096  to + 4096
    for( int i= -0xFFF - 10; i < 0xFFF + 10 ; i++ )
        intTestRoundtrip( i );

    // limits
    intTestRoundtrip  (   long.MaxValue     );
    intTestRoundtrip  (   long.MaxValue - 1 );
    intTestRoundtrip  (   long.MinValue     );
    intTestRoundtrip  (   long.MinValue + 1 );
    intTestRoundtripUS(  ulong.MaxValue     );
    intTestRoundtripUS(  ulong.MaxValue - 1 );
    intTestRoundtripUS(  ulong.MinValue     );
    intTestRoundtripUS(  ulong.MinValue + 1 );

    // random
    Random r= new Random();
    for( int i= 0; i < 100 ; i++ )
        intTestRoundtrip(   ((long)r.Next())
                          * ((long)r.Next())
                          * ((long)r.Next())  );
}


//--------------------------------------------------------------------------------------------------
//--- Test ConvertFloats
//--------------------------------------------------------------------------------------------------
void floatTest( double d, char decimalPoint, int minDigitsBeforeDot, int digitsAfterDot, String expectedString, bool forceScientific= false )
{
    AString ms= new AString();
    NumberFormat nf= new NumberFormat();
    nf.ForceScientific= forceScientific;
    if ( decimalPoint == '\0' )
    {
        nf.WriteGroupChars= true;
    }
    else
        nf.DecimalPointChar=  decimalPoint;

    nf.IntegralPartMinimumWidth=    minDigitsBeforeDot;
    nf.FractionalPartWidth=  digitsAfterDot;
    nf.ThousandsGroupChar=    '\0';


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
            dSystem= Double.Parse( ms.ToString(), CultureInfo.InvariantCulture );
        }
        catch( Exception )
        {
            UT_TRUE( digitsAfterDot == 0 ); // this is not really allowed in c# when parsing
            dSystem= d;
        }
        UT_EQ( d, dSystem, precision );
    }

    // check with aworx parsing
    double dAWorx= ms.ParseFloat(nf);
    UT_EQ( d, dAWorx, precision );

}


#if ALIB_NUNIT
    [Test ()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings_Format")]
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
        posOrig= pos= 0;    UT_EQ( 0.0,        a.ParseFloat  ( pos )  );             UT_EQ( pos, posOrig );
        posOrig= pos= -5;   UT_EQ( 0.0,        a.ParseFloat  ( pos )  );
    }

    // parse on non number
    a._()._( "Hello");
    {
        posOrig= pos= 0;    UT_EQ( 0.0,        a.ParseFloat  ( pos )  );
        posOrig= pos= -5;   UT_EQ( 0.0,        a.ParseFloat  ( pos )  );
        posOrig= pos= 2;    UT_EQ( 0.0,        a.ParseFloat  ( pos )  );
    }

    // check that leading whitespaces do not move pointer
    a._()._( "   Hello");
    {
        posOrig= pos= 0;    UT_EQ( 0.0,        a.ParseFloat  ( pos )  );
        posOrig= pos= -5;   UT_EQ( 0.0,        a.ParseFloat  ( pos )  );
        posOrig= pos= 2;    UT_EQ( 0.0,        a.ParseFloat  ( pos )  );
    }

    // parse NaN and INF
    {
        a._()._( "nan");    UT_TRUE( Double.IsNaN     ( a.ParseFloat(0, out pos ) ) );        UT_EQ( 3, pos );
        a._()._("-nan");    UT_TRUE( Double.IsNaN     ( a.ParseFloat(0, out pos ) ) );        UT_EQ( 4, pos );
        a._()._( "nAN");    UT_TRUE( Double.IsNaN     ( a.ParseFloat(0, out pos ) ) );        UT_EQ( 3, pos );
        a._()._("-nAN");    UT_TRUE( Double.IsNaN     ( a.ParseFloat(0, out pos ) ) );        UT_EQ( 4, pos );

        a._()._( "inf");    UT_TRUE( Double.IsInfinity( a.ParseFloat(0, out pos ) ) );        UT_EQ( 3, pos );
        a._()._("-inf");    UT_TRUE( Double.IsInfinity( a.ParseFloat(0, out pos ) ) );        UT_EQ( 4, pos );
        a._()._( "INf");    UT_TRUE( a.ParseFloat(0, out pos ) == Double.PositiveInfinity );  UT_EQ( 3, pos );
        a._()._("-INf");    UT_TRUE( a.ParseFloat(0, out pos ) == Double.NegativeInfinity );  UT_EQ( 4, pos );
    }

    // write NaN and INF
    {
        a._()._(  Double.NaN              );    UT_EQ( NumberFormat.Global.NANLiteral       ,  a );
        a._()._(  Double.PositiveInfinity );    UT_EQ( NumberFormat.Global.INFLiteral       ,  a );
        a._()._(  Double.NegativeInfinity );    UT_EQ( "-" + NumberFormat.Global.INFLiteral ,  a );
    }

    // parse floats
    {
        NumberFormat nf= new NumberFormat();

        a._()._( "12345.789");     UT_EQ( 12345.789,        a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  0  + a.Length() , pos );

        a._()._( "");              UT_EQ( 0.0,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  0               , pos );
        a._()._( "-");             UT_EQ( 0.0,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  0               , pos );
        a._()._( "-X");            UT_EQ( 0.0,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  0               , pos );
        a._()._( ".");             UT_EQ( 0.0,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  1               , pos );
        a._()._( ".0");            UT_EQ( 0.0,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  2               , pos );
        a._()._( "0.");            UT_EQ( 0.0,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  2               , pos );
        a._()._( ".5");            UT_EQ( 0.5,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  2               , pos );
        a._()._( "5.");            UT_EQ( 5.0,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  2               , pos );
        a._()._( "+0");            UT_EQ( 0.0,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  2               , pos );
        a._()._( "-0");            UT_EQ( 0.0,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  2               , pos );
        a._()._( "+6");            UT_EQ( 6.0,              a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  2               , pos );
        a._()._( "-7");            UT_EQ( -7.0,             a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  2               , pos );
        a._()._( "-7");            UT_EQ( 7.0,              a.ParseFloat( 1, nf, out pos ) );  UT_EQ(  2               , pos );

        a._()._( "+42");           UT_EQ( 42.0,             a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  3               , pos );
        a._()._( " -42 ");         UT_EQ(-42.0,             a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  4               , pos );
        a._()._( "  +42.  ");      UT_EQ( 42.0,             a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  6               , pos );

        a._()._( "  123");         UT_EQ( 123.0,            a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  0  + a.Length() , pos );
        a._()._( "  -23  ");       UT_EQ( -23.0,            a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  5               , pos );
        a._()._( "123  ");         UT_EQ( 123.0,            a.ParseFloat( 0, nf, out pos ) );  UT_EQ(  3               , pos );

        a._()._( "xxx123456789");  UT_EQ( 123456789.0,      a.ParseFloat( 3, nf, out pos ) );  UT_EQ(  0  + a.Length() , pos );
        a._()._( "xxx  1.3");      UT_EQ( 1.3,              a.ParseFloat( 3, nf, out pos ) );  UT_EQ(  0  + a.Length() , pos );
        a._()._( "xxx  1.3  ");    UT_EQ( 1.3,              a.ParseFloat( 3, nf, out pos ) );  UT_EQ(  0  + a.Length()-2 , pos );
        a._()._( "xxx1.3  ");      UT_EQ( 1.3,              a.ParseFloat( 3, nf, out pos ) );  UT_EQ(  0  + a.Length()-2 , pos );

        nf.DecimalPointChar= '@';
        a._()._( "-2495@321");     UT_EQ( -2495.321,        a.ParseFloat( 0, nf, out pos  ) );  UT_EQ(  0  + a.Length() ,  pos );
        nf.DecimalPointChar= '.';

        a._()._( "1.234E1");      UT_EQ( 12.34,            a.ParseFloat( 0, nf, out pos  ) );  UT_EQ(  0  + a.Length() ,  pos );
        a._()._( "1.234E0") ;     UT_EQ( 1.234,            a.ParseFloat( 0, nf, out pos  ) );  UT_EQ(  0  + a.Length() ,  pos );
        a._()._( "1.234E-1");     UT_EQ( 0.1234,           a.ParseFloat( 0, nf, out pos  ), 0.000000001 );  UT_EQ(  0  + a.Length() ,  pos );
        a._()._( "1.234E");       UT_EQ( 1.234,            a.ParseFloat( 0, nf, out pos  ) );  UT_EQ(  a.Length()   ,  pos );
        a._()._( "1.234Ex");      UT_EQ( 1.234,            a.ParseFloat( 0, nf, out pos  ) );  UT_EQ(  a.Length() -1   ,  pos );



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
            NumberFormat nf= new NumberFormat();
            nf.ExponentSeparator= "*10^";
            AString s= new AString();
            double v= 7.5E42;
            s._( v, nf );
            UT_EQ( s, "7.5*10^42" );
            double back= s.ParseFloat( nf );
            UT_EQ( v, back, 0.0000000001 );
        }
    }
}

//##################################################################################################
// Format tests
//##################################################################################################
AString     testAS= new AString();
Formatter   testFormatter;
void    checkError( String exp, params Object[] args )
{
    testAS._();
    testAS.SetBuffer(1);

    // invoke format
    cs.aworx.lib.lang.Report.GetDefault().PushHaltFlags( false, false );
    testFormatter.Format( testAS, args );
    cs.aworx.lib.lang.Report.GetDefault().PopHaltFlags();

    UT_TRUE( testAS.IndexOf(exp) >= 0 );

}


void    checkFormat( String exp, params Object[] args )
{
    // clear AString buffer to test for enough capacity
    testAS._();
    testAS.SetBuffer(1);

    // invoke format
    testFormatter.Format( testAS, args );
    UT_EQ( exp, testAS );
}



//--------------------------------------------------------------------------------------------------
//--- Test JavaStyle
//--------------------------------------------------------------------------------------------------
#if ALIB_NUNIT
    [Test()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings_Format")]
    #endif
#endif
public void FormatterJavaStyle()
{
    UT_PRINT( "ALib Format Tests Python Style: Start" );

    FormatterJavaStyle formatter= new FormatterJavaStyle();
    formatter.Next = new FormatterPythonStyle();
    testFormatter= formatter;

    formatter.AlternativeNumberFormat.DecimalPointChar=     ',';
    formatter.AlternativeNumberFormat.ThousandsGroupChar=   '.';

    NumberFormat nfBackup= new NumberFormat();
    nfBackup.Set( formatter.DefaultNumberFormat );

    //===== Simple initial tests =========
    checkFormat(  "No JSF"                 , ""                 , "No JSF"        );
    checkFormat("%%No JSF"                 , "%%"               , "No JSF"        );
    checkError ( "Format Conversion Ex"    , "% %"              , "Hello JSF"     );
    checkFormat("Hello JSF"                , "%1$s"             , "Hello JSF"     );
    checkFormat("Hello JSF"                , "%1$s %2$s"        , "Hello", "JSF"  );
    checkFormat("Hello HelloJSF"           , "%1$s %1$s"        , "Hello", "JSF"  );
    checkFormat("JSF Hello"                , "%2$s %1$s"        , "Hello", "JSF"  );
    checkError ( "Missing decimal value"   , "%.s"          , "x"          );

    //===== replace %% and new line =========
    checkFormat("repl. percents% X"   , "repl. percents%% %s"              , "X" );
    checkFormat("repl. percents%%X"   , "repl. percents%%%%%s"             , "X" );
    checkFormat("repl. X%percents%"   , "repl. %s%%percents%%"             , "X" );


    checkFormat("x\\nxX"                , "x\\nx"                          , "X" ); // not a format string (no replacement)
    checkFormat("x\nx%sX"               , "x\nx%s"                         , "X" ); // not a format string (contains \n)

    checkFormat("y" + CString.NewLineChars + "yX" , "y%ny%s"               , "X" ); // a format string (contains \n)

    //===== Parameter addressing =========
    checkFormat("1 1 1END"          , "%<s %<s %<s"   ,'1', "END" );
    checkFormat("1 1 1END"          , "%<s %<s %<s"   ,'1', "END" );
    checkFormat("2 2 4 1 1 2END"    , "%2$s %<s %4$s %s %1$s %s"   ,'1','2','3','4', "END" );
    checkFormat( "abracadabra"      , "%s%s%1$s"     ,  "abra", "cad" );
    checkFormat( "abracadabra"      , "%1$s%2$s%s"   ,  "abra", "cad" );

    //================== Concatenated operations (mixed formatters)  ===============================
    checkFormat( "123"     , "%s"   ,  1,   "%s",2,     "%s",3             );
    checkFormat( "123456"  , "%s"   ,  1,   "%s%s",2,3, "%s%s",4,5  ,6     );
    checkFormat( "123456"  , "%s"   ,  1,   "%s",2,  3, "%s%s",4,5  ,6     );
    checkFormat( "13456"   , "%s"   ,  1,   "%2$s",2,3, "%s%s",4,5  ,6     );

    checkFormat( "123"     , "{}"   ,  1,   "%s",2,     "{}",3             );
    checkFormat( "123456"  , "{}"   ,  1,   "%s%s",2,3, "{}{}",4,5  ,6     );
    checkFormat( "123456"  , "{}"   ,  1,   "%s",2,  3, "{}{}",4,5  ,6     );
    checkFormat( "13456"   , "{}"   ,  1,   "{1}",2,3, "{}{}",4,5  ,6     );

    checkFormat( "123"     , "{}"   ,  1,   "{}",2,     "{}",3             );
    checkFormat( "123456"  , "{}"   ,  1,   "{}{}",2,3, "{}{}",4,5  ,6     );
    checkFormat( "123456"  , "{}"   ,  1,   "{}",2,  3, "{}{}",4,5  ,6     );
    checkFormat( "13456"   , "{}"   ,  1,   "%2$s",2,3, "{}{}",4,5  ,6     );

    checkFormat( "123"     , "{}"   ,  1,   "{}",2,     "%s",3             );
    checkFormat( "123456"  , "{}"   ,  1,   "{}{}",2,3, "%s%s",4,5  ,6     );
    checkFormat( "123456"  , "{}"   ,  1,   "{}",2,  3, "%s%s",4,5  ,6     );
    checkFormat( "13456"   , "{}"   ,  1,   "{1}",2,3 , "%s%s",4,5  ,6     );


    //===== Strings witdh/precision =========
    checkFormat("aBcDe",         "%s"       , "aBcDe"  );
    checkFormat("ABCDE",         "%S"       , "aBcDe"  );
    checkFormat("aBc",           "%.3s"     , "aBcDe"  );
    checkFormat("ABC",           "%.3S"     , "aBcDe"  );
    checkFormat("  ABC",         "%5.3S"    , "aBcDe"  );
    checkFormat("ABC   ",        "%-6.3S"   , "aBcDe"  );
    checkFormat(" ABC  ",        "%^6.3S"   , "aBcDe"  );
    checkFormat("ABCDE",        "%3S"   , "aBcDe"  );


    //===== Boolean =========
    checkFormat("true false true false true", "%b %b %b %b %b"  , true, false, 1, 0, "Hello"  );
    checkFormat("true",         "%.4b"  , true  );
    checkFormat("fals",         "%.4b"  , false  );
    checkFormat("tru",          "%.3b"  , true  );
    checkFormat("fal",          "%.3b"  , false  );
    checkFormat("  tru",        "%5.3b"  , true  );
    checkFormat("  fal",        "%5.3b"  , false  );
    checkFormat(" true",        "%5.6b"  , true  );
    checkFormat("false",        "%5.6b"  , false  );

    //===== Hash value 'h'/'H' =========
    checkFormat(   "ff"            , "%h"                    , 255);
    checkFormat(   "FF"            , "%H"                    , 255);

    //===== Date/Time 't'/'T' =========

    DateTime ticksAM= new DateTime(2015,01,03,05,06,02);
    DateTime ticksPM= new DateTime(2016,09,30,14,18,22);

    checkFormat( "05"                         , "%tH"         ,ticksAM );
    checkFormat( "14"                         , "%tH"         ,ticksPM );
    checkFormat( "05"                         , "%tk"         ,ticksAM ); // should be "5" but not possible to implement
    checkFormat( "14"                         , "%tk"         ,ticksPM );
    checkFormat( "05 AM"                      , "%tI"         ,ticksAM );
    checkFormat( "02 PM"                      , "%tI"         ,ticksPM );
    checkFormat( "5 AM"                       , "%tl"         ,ticksAM );
    checkFormat( "2 PM"                       , "%tl"         ,ticksPM );
    checkFormat( "06"                         , "%tM"         ,ticksAM );
    checkFormat( "18"                         , "%tM"         ,ticksPM );
    checkFormat( "02"                         , "%tS"         ,ticksAM );
    checkFormat( "22"                         , "%tS"         ,ticksPM );

    checkFormat( "January"                    , "%tB"         ,ticksAM );
    checkFormat( "September"                  , "%tB"         ,ticksPM );
    checkFormat( "Jan"                        , "%tb"         ,ticksAM );
    checkFormat( "Sep"                        , "%tb"         ,ticksPM );
    checkFormat( "Saturday"                   , "%tA"         ,ticksAM );
    checkFormat( "Friday"                     , "%tA"         ,ticksPM );
    checkFormat( "Sat"                        , "%ta"         ,ticksAM );
    checkFormat( "Fri"                        , "%ta"         ,ticksPM );
    checkFormat( "2015"                       , "%tY"         ,ticksAM );
    checkFormat( "2016"                       , "%tY"         ,ticksPM );
    checkFormat( "15"                         , "%ty"         ,ticksAM );
    checkFormat( "16"                         , "%ty"         ,ticksPM );
    checkFormat( "01"                         , "%tm"         ,ticksAM );
    checkFormat( "09"                         , "%tm"         ,ticksPM );
    checkFormat( "03"                         , "%td"         ,ticksAM );
    checkFormat( "30"                         , "%td"         ,ticksPM );
    checkFormat( "03"                         , "%te"         ,ticksAM );  // should be "3" but not possible to implement
    checkFormat( "30"                         , "%te"         ,ticksPM );

    checkFormat( "05:06"                      , "%tR"         ,ticksAM );
    checkFormat( "14:18"                      , "%tR"         ,ticksPM );
    checkFormat( "05:06:02"                   , "%tT"         ,ticksAM );
    checkFormat( "14:18:22"                   , "%tT"         ,ticksPM );

    checkFormat( "01/03/15"                   , "%tD"         ,ticksAM );
    checkFormat( "09/30/16"                   , "%tD"         ,ticksPM );
    checkFormat( "2015-01-03"                 , "%tF"         ,ticksAM );
    checkFormat( "2016-09-30"                 , "%tF"         ,ticksPM );

    //======================================= Characters ===========================================

    // alignment
    checkFormat( "x"                          , "%s"           , 'x'          );
    checkFormat( "#x  #"                      , "#%-3c#"       , 'x'    );
    checkFormat( "#  x#"                      , "#%3c#"        , 'x'    );
    checkFormat( "# x #"                      , "#%^3c#"       , 'x'    );
    checkFormat( "    x"                      , "%5c"          , 'x'          );

    // errors
    checkError( "Precision = .2"              , "%5.2c"         , 'x'          );
    checkError( "Flags = #"                   , "%#c"           , 'x'          );

    // wchar
    checkFormat( "\u03B1"        , "%c"       , '\u03B1'   ); //greek alpha
    checkFormat( "    \u03B1"    , "%5c"      , '\u03B1'   ); //greek alpha
    checkFormat( "a\u03B1b\u03B2", "a%cb%c"   , '\u03B1', '\u03B2'    ); //greek alpha, beta
    checkFormat( "@"                          , "%c"         , 64           ); // int   ascii @
    checkFormat( "@"                          , "%c"         , 64L          ); // long  ascii @
    checkFormat( "@"                          , "%c"         , 64UL         ); // ulong ascii @
    checkFormat( "\u03B1"       , "%c"        , 0x03B1       ); //greek alpha
    checkFormat( "\u03B1"       , "%c"        , 0x03B1L      ); //greek alpha
    checkFormat( "\u03B1"       , "%c"        , 0x03B1UL     ); //greek alpha


    //===== Hex =========
    checkFormat("1'0000"      , "%,x"         ,65536 );
    checkFormat("10000"       , "%x"          ,65536 );
    checkFormat("ffff"        , "%x"          ,65535 );
    checkFormat("fe"          , "%x"          ,254 );
    checkFormat("FE"          , "%X"          ,254 );
    checkFormat("0xfe"        , "%#x"         ,254 );
    checkFormat("FE"          , "%X"          ,254 );
    checkFormat("0XFE"        , "%#X"         ,254 );



    //======================================= Integers (Decimal) ===========================================
    checkFormat( "0"                    , "%d"              ,  0    );
    checkFormat( "1"                    , "%d"              ,  1    );
    checkFormat( "5"                    , "%d"              ,  5    );
    checkFormat( "-1"                   , "%d"              ,  -1   );
    checkFormat( "-5"                   , "%d"              ,  -5   );
    checkFormat( "0"                    , "%d"              ,  0U   );
    checkFormat( "1"                    , "%d"              ,  1U   );
    checkFormat( "5"                    , "%d"              ,  5U   );
    checkFormat( "-2147483648"          , "%D"              ,   int.MinValue   );
    checkFormat( "2147483647"           , "%D"              ,   int.MaxValue   );
    checkFormat( "-2147483647"          , "%D"              ,   int.MinValue +1);
    checkFormat( "2147483646"           , "%D"              ,   int.MaxValue -1);
    checkFormat( "0"                    , "%D"              ,  uint.MinValue   );
    checkFormat( "4294967295"           , "%D"              ,  uint.MaxValue   );
    checkFormat( "1"                    , "%D"              ,  uint.MinValue +1);
    checkFormat( "4294967294"           , "%D"              ,  uint.MaxValue -1);
    checkFormat( "-9223372036854775808" , "%D"              ,  long.MinValue   );
    checkFormat( "9223372036854775807"  , "%D"              ,  long.MaxValue   );
    checkFormat( "-9223372036854775807" , "%D"              ,  long.MinValue +1);
    checkFormat( "9223372036854775806"  , "%D"              ,  long.MaxValue -1);
    checkFormat( "0"                    , "%D"              , ulong.MinValue   );
    checkFormat( "18446744073709551615" , "%D"              , ulong.MaxValue   );
    checkFormat( "1"                    , "%D"              , ulong.MinValue +1);
    checkFormat( "18446744073709551614" , "%D"              , ulong.MaxValue -1);



    // integer sign
    checkFormat( "0"                    , "%d"             ,  0    );
    checkFormat( "1"                    , "%d"             ,  1    );
    checkFormat( "-1"                   , "%d"             , -1    );

    checkFormat( " 0"                   , "% d"            ,  0    );
    checkFormat( " 1"                   , "% d"            ,  1    );
    checkFormat( "-1"                   , "% d"            , -1    );

    checkFormat( "+0"                   , "%+d"            ,  0    );
    checkFormat( "+1"                   , "%+d"            ,  1    );
    checkFormat( "-1"                   , "%+d"            , -1    );

    // integer field width
    checkFormat( " 0"                   , "%2d"            ,  0    );

    // integer mindigits
    checkFormat( "000"                 , "%03d"           ,  0    );
    checkFormat( "001"                 , "%03d"           ,  1    );
    checkFormat( "-01"                 , "%03d"           , -1    );


    checkFormat( " 00"                 , "% 03d"          ,  0    );
    checkFormat( " 01"                 , "% 03d"          ,  1    );
    checkFormat( "-01"                 , "% 03d"          , -1    );




    //========================================= Floats =============================================
    // mixed tests
    checkFormat(                    "0.0", "%s"                 , 0.0          ) ;
    checkFormat(     "0.3333333333333333", "%s"                 , 1.0/3.0      ) ;
    checkFormat(      "3.333333333333334", "%s"                 , 10.0/3.0     ) ;
    checkFormat(      "6.666666666666667", "%s"                 , 20.0/3.0     ) ;
    checkFormat(                "4.23456", "%s"                 , 4.23456      ) ;
    checkFormat(               "-4.2345" , "%s"                 , -4.2345      ) ;

    checkFormat(                    "0.0", "%.5s"               , 0.0f         ) ;
    checkFormat(                  "0.333", "%.5s"               , 1.0f/3.0f    ) ;
    checkFormat(                  "3.333", "%.5s"               , 10.0f/3.0f   ) ;
    checkFormat(                  "6.666", "%.5s"               , 20.0f/3.0f   ) ;
    checkFormat(                  "4.234", "%.5s"               , 4.23456f     ) ;
    checkFormat(                  "-4.23", "%.5s"               , -4.23456789f ) ;

    checkFormat(           "0.000000E+00", "%E"                 , 0.0          ) ;
    checkFormat(           "0.000000E+00", "%#E"                , 0.0          ) ;
    checkFormat(               "1.23E-01", "%.2E"               , 0.12345      ) ;
    checkFormat(               "1.23E-01", "%#.2E"              , 0.12345      ) ;
    checkFormat(                  "1E-01", "%.0E"               , 0.12345      ) ;
    checkFormat(                 "1.E-01", "%#.0E"              , 0.12345      ) ;

    checkFormat(              "123.45"   , "%s"                 , 123.45       ) ;
    checkFormat(              "1"        , "%.1s"               , 123.45       ) ;
    checkFormat(              ""         , "%.0s"               , 123.45       ) ;

    checkFormat(              "123.0"    , "%s"                 , 123.0        ) ;
    checkFormat(              "0.45"     , "%.5s"               , 0.45         ) ;

    checkFormat( "1.234000"              , "%g"                  ,  1.234 );
    checkFormat( "1.234000"              , "%G"                  ,  1.234 );
    checkFormat( "1.234000e+20"          , "%g"                  ,  1.234e20 );
    checkFormat( "1.234000E+20"          , "%G"                  ,  1.234e20 );

    checkFormat( "1.234"                 , "%f"                  ,  1.234 );
    checkFormat( "1.0"                   , "%f"                  ,  1.0 );
    checkFormat( "1.00"                  , "%.2f"                ,  1.0 );
    checkFormat( "1.23456789"            , "%f"                  ,  1.23456789 );
    checkFormat( "1234567890.0"          , "%f"                  ,  1.23456789e9 );
    checkFormat( "12345678900000.0"      , "%f"                  ,  1.23456789e13 );

    checkFormat("5"                      , "%s"                  , 5     );
    checkFormat("12345.6"                , "%s"                  , 12345.6   );
    checkFormat("12,345.6"               , "%,s"                 , 12345.6   );
    checkFormat("12,345.6"               , "%,s"                 , 12345.6   );

    checkFormat( "1.234E+20"             , "%s"                  ,  1.234e20 );
    checkFormat( "1.234E+20"             , "%S"                  ,  1.234e20 );


    //--- a quick check on local setting (this procedure is maybe not too nice but documented)  ---


    formatter.DefaultNumberFormat.DecimalPointChar  = ',';
    formatter.DefaultNumberFormat.ThousandsGroupChar= '.';
    checkFormat(           "1234,500"         ,  "%.3g"             ,  1234.5       );
    checkFormat(          "1.234,500"         ,  "%,.3g"             ,  1234.5       );
    formatter.DefaultNumberFormat.Set(nfBackup);


    //----------------------------- floats with width and precision ----------------------------

    // floats with field width
    checkFormat(          "       0.0"       ,  "%10s"             ,  0.0         );
    checkFormat(          "       0.0"       ,  "%10.5s"           ,  0.0         );
    checkFormat(          "  0.000000"       ,  "%10g"             ,  0.0         );
    checkFormat(          "       0.0"       ,  "%10f"             ,  0.0         );
    checkFormat(          "  0.000000"       ,  "%10.6f"           ,  0.0         );
    checkFormat(          "   0.00000"       ,  "%10.5g"           ,  0.0         );
    checkFormat(          "  14.05000"       ,  "%10.5g"           ,  14.05       );
    checkFormat(          " -14.05000"       ,  "%10.5g"           , -14.05       );
    checkFormat(           " 14.05000"       ,  "%9.5g"            ,  14.05       );
    checkFormat(           "-14.05000"       ,  "%9.5g"            , -14.05       );
    checkFormat(            "14.05000"       ,  "%8.5g"            ,  14.05       );
    checkFormat(           " 14.05000"       , "% 8.5g"            ,  14.05       );
    checkFormat(           "-14.05000"       ,  "%8.5g"            , -14.05       );
    checkFormat(            "14.05000"       ,  "%7.5g"            ,  14.05       );
    checkFormat(           "+14.05000"       ,  "%+7.5g"           ,  14.05       );
    checkFormat(           "-14.05000"       ,  "%7.5g"            , -14.05       );


    // Leading '0' in width forces padding after the sign
    //     positive without sign
    checkFormat( "0012.3456789"          , "%012.7g"          ,  12.3456789   );
    checkFormat( "012.3456789"           , "%011.7g"          ,  12.3456789   );
    checkFormat( "12.3456789"            , "%010.7g"          ,  12.3456789   );
    checkFormat( "12.3456789"            , "%09.7g"           ,  12.3456789   );

    checkFormat( "000012.3"              , "%08.1g"         ,  12.3456789   );
    checkFormat( "00012.35"              , "%08.2g"         ,  12.3456789   );
    checkFormat( "0012.346"              , "%08.3g"         ,  12.3456789   );
    checkFormat( "012.3457"              , "%08.4g"         ,  12.3456789   );

    checkFormat( " 012.3456789"          , "% 012.7g"        ,  12.3456789   );
    checkFormat( " 12.3456789"           , "% 011.7g"        ,  12.3456789   );
    checkFormat( " 12.3456789"           , "% 010.7g"        ,  12.3456789   );
    checkFormat( " 12.3456789"           , "% 09.7g"         ,  12.3456789   );
    checkFormat( " 12.3456789"           , "% 08.7g"         ,  12.3456789   );
    checkFormat( " 00012.3"              , "% 08.1g"         ,  12.3456789   );
    checkFormat( " 0012.35"              , "% 08.2g"         ,  12.3456789   );
    checkFormat( " 012.346"              , "% 08.3g"         ,  12.3456789   );
    checkFormat( " 12.3457"              , "% 08.4g"         ,  12.3456789   );

    //     negative
    checkFormat( "-012.3456789"          , "% 012.7g"        ,  -12.3456789   );
    checkFormat( "-12.3456789"           , "% 011.7g"        ,  -12.3456789   );
    checkFormat( "-12.3456789"           , "% 010.7g"        ,  -12.3456789   );
    checkFormat( "-12.3456789"           , "% 09.7g"         ,  -12.3456789   );
    checkFormat( "-12.3456789"           , "% 08.7g"         ,  -12.3456789   );
    checkFormat( "-00012.3"              , "% 08.1g"         ,  -12.3456789   );
    checkFormat( "-0012.35"              , "% 08.2g"         ,  -12.3456789   );
    checkFormat( "-012.346"              , "% 08.3g"         ,  -12.3456789   );
    checkFormat( "-12.3457"              , "% 08.4g"         ,  -12.3456789   );


    //     positive with + sign
    checkFormat( "+012.3456789"          , "%+012.7g"        ,  12.3456789   );
    checkFormat( "+12.3456789"           , "%+011.7g"        ,  12.3456789   );
    checkFormat( "+12.3456789"           , "%+010.7g"        ,  12.3456789   );
    checkFormat( "+12.3456789"           , "%+09.7g"         ,  12.3456789   );
    checkFormat( "+12.3456789"           , "%+08.7g"         ,  12.3456789   );
    checkFormat( "+00012.3"              , "%+08.1g"         ,  12.3456789   );
    checkFormat( "+0012.35"              , "%+08.2g"         ,  12.3456789   );
    checkFormat( "+012.346"              , "%+08.3g"         ,  12.3456789   );
    checkFormat( "+12.3457"              , "%+08.4g"         ,  12.3456789   );



    //-------  Nan,Inf, -0.0 -------
    checkFormat( "NaN"                  , "%s"             ,  double.NaN );
    checkFormat( "Infinity"             , "%s"             ,  double.PositiveInfinity );
    checkFormat( "-Infinity"            , "%s"             ,  double.NegativeInfinity );
    checkFormat( "0.0"                  , "%s"             ,  0.0 );
    checkFormat( "-0.0"                 , "%s"             , -0.0 ); // negative zero
    checkFormat( "NaN"                  , "%+g"            ,  double.NaN );
    checkFormat( "+Infinity"            , "%+g"            ,  double.PositiveInfinity );
    checkFormat( "-Infinity"            , "%+g"            ,  double.NegativeInfinity );
    checkFormat( "+0.000000"            , "%+g"            ,  0.0 );
    checkFormat( "-0.000000"            , "%+g"            , -0.0 ); // negative zero
    checkFormat( "NaN"                  , "%+G"            ,  double.NaN );
    checkFormat( "+INFINITY"            , "%+G"            ,  double.PositiveInfinity );
    checkFormat( "-INFINITY"            , "%+G"            ,  double.NegativeInfinity );
    checkFormat( "+0.000000"            , "%+G"            ,  0.0 );
    checkFormat( "-0.000000"            , "%+G"            , -0.0 ); // negative zero


    //-------  Nan,Inf, -0.0, field width -------
    checkFormat( "       NaN"           , "%10g"           ,  double.NaN );
    checkFormat( "  Infinity"           , "%10g"           ,  double.PositiveInfinity );
    checkFormat( " -Infinity"           , "%10g"           ,  double.NegativeInfinity );
    checkFormat( "  0.000000"           , "%10g"           ,  0.0 );
    checkFormat( " -0.000000"           , "%10g"           , -0.0 ); // negative zero

    checkFormat( "       NaN"           , "%+10g"         ,  double.NaN );
    checkFormat( " +Infinity"           , "%+10g"         ,  double.PositiveInfinity );
    checkFormat( " -Infinity"           , "%+10g"         ,  double.NegativeInfinity );
    checkFormat( " +0.000000"           , "%+10g"         ,  0.0 );
    checkFormat( " -0.000000"           , "%+10g"         , -0.0 ); // negative zero

    checkFormat( "       NaN"           , "%010g"          ,  double.NaN );
    checkFormat( "  Infinity"           , "%010g"          ,  double.PositiveInfinity );
    checkFormat( "- Infinity"           , "%010g"          ,  double.NegativeInfinity );
    checkFormat( "00000000.0"           , "%010.1g"        ,  0.0 );
    checkFormat( "-0000000.0"           , "%010.1g"        , -0.0 ); // negative zero

    checkFormat( "NaN       "           , "%-10g"          ,  double.NaN );
    checkFormat( "Infinity  "           , "%-10g"          ,  double.PositiveInfinity );
    checkFormat( "-Infinity "           , "%-10g"          ,  double.NegativeInfinity );
    checkFormat( "0.0       "           , "%-10.1g"        ,  0.0 );
    checkFormat( "-0.0      "           , "%-10.1g"        , -0.0 ); // negative zero


    // -------------------------------- scientific -------------------------------------------

    checkFormat( "1.234568e+01"         , "%-e"            ,  12.3456789   );
    checkFormat( "1.235e+01"            , "%-.3e"          ,  12.3456789   );
    checkFormat( " 1.235e+01"           , "%10.3e"         ,  12.3456789   );
    checkFormat( "01.235e+01"           , "%010.3e"        ,  12.3456789   );
    checkFormat( "001.23e+01"           , "%010.2e"        ,  12.3456789   );
    checkFormat( "-01.23e+01"           , "%010.2e"        , -12.3456789   );
    checkFormat( "-1.235e+01"           , "%010.3e"        , -12.3456789   );
    checkFormat( "-1.2346e+01"          , "%010.4e"        , -12.3456789   );

    checkFormat( "1.234568E+01"         , "%-E"            ,  12.3456789   );
    checkFormat( "1.235E+01"            , "%-.3E"          ,  12.3456789   );
    checkFormat( " 1.235E+01"           , "%10.3E"        ,  12.3456789   );
    checkFormat( "01.235E+01"           , "%010.3E"       ,  12.3456789   );
    checkFormat( "001.23E+01"           , "%010.2E"       ,  12.3456789   );
    checkFormat( "-01.23E+01"           , "%010.2E"       , -12.3456789   );
    checkFormat( "-1.235E+01"           , "%010.3E"       , -12.3456789   );
    checkFormat( "-1.2346E+01"          , "%010.4E"       , -12.3456789   );


    //-------  Nan,Inf, -0.0 -------
    checkFormat( "NaN"                  , "%E"            ,  double.NaN );
    checkFormat( "INFINITY"             , "%E"            ,  double.PositiveInfinity );
    checkFormat( "-INFINITY"            , "%E"            ,  double.NegativeInfinity );
    checkFormat( "0.000000E+00"         , "%E"            ,  0.0 );
    checkFormat( "-0.000000E+00"        , "%E"            , -0.0 ); // negative zero
    checkFormat( "NaN"                  , "%+e"           ,  double.NaN );
    checkFormat( "+Infinity"            , "%+e"           ,  double.PositiveInfinity );
    checkFormat( "-Infinity"            , "%+e"           ,  double.NegativeInfinity );
    checkFormat( "+0.000000e+00"        , "%+e"           ,  0.0 );
    checkFormat( "-0.000000e+00"        , "%+e"           , -0.0 ); // negative zero


    // -------------------------------- FixedPoint -------------------------------------------
    checkFormat( "12.345"               , "%f"            ,  12.345         );
    checkFormat( "12.3456789123"        , "%f"            ,  12.3456789123  );
    checkFormat( "-12.345"              , "%f"            , -12.345         );
    checkFormat( "-12.3456789123"       , "%f"            , -12.3456789123  );
    checkFormat( "12.345"               , "%f"            ,  12.345         );
    checkFormat( "12.3456789123"        , "%f"            ,  12.3456789123  );
    checkFormat( "-12.345"              , "%f"            , -12.345         );
    checkFormat( "-12.3456789123"       , "%f"            , -12.3456789123  );





    checkFormat(            "0.00000"       , "%,06.5f"             ,  0.0         );
    checkFormat(            "0.00000"       , "%,07.5f"             ,  0.0         );
    checkFormat(           "00.00000"       , "%,08.5f"             ,  0.0         );
    checkFormat(          "000.00000"       , "%,09.5f"             ,  0.0         );
    checkFormat(         " 000.00000"       , "%,010.5f"           ,  0.0         );
    checkFormat(        "0,000.00000"       , "%,011.5f"           ,  0.0         );
    checkFormat(       "00,000.00000"       , "%,012.5f"           ,  0.0         );
    checkFormat(      "000,000.00000"       , "%,013.5f"           ,  0.0         );
    checkFormat(     " 000,000.00000"       , "%,014.5f"           ,  0.0         );
    checkFormat(    "0,000,000.00000"       , "%,015.5f"           ,  0.0         );
    checkFormat(   "00,000,000.00000"       , "%,016.5f"           ,  0.0         );


    checkFormat(                "0.0"       , "%,.1f"              ,          0.0 );
    checkFormat(                "1.0"       , "%,.1f"              ,          1.0 );
    checkFormat(               "10.0"       , "%,.1f"              ,         10.0 );
    checkFormat(              "100.0"       , "%,.1f"              ,        100.0 );
    checkFormat(            "1,000.0"       , "%,.1f"              ,       1000.0 );
    checkFormat(           "10,000.0"       , "%,.1f"              ,      10000.0 );
    checkFormat(          "100,000.0"       , "%,.1f"              ,     100000.0 );
    checkFormat(        "1,000,000.0"       , "%,.1f"              ,    1000000.0 );
    checkFormat(       "10,000,000.0"       , "%,.1f"              ,   10000000.0 );
    checkFormat(      "100,000,000.0"       , "%,.1f"              ,  100000000.0 );

    checkFormat(            "0.00000"       ,  "%,05.5f"           ,  0.0         );
    checkFormat(            "0.00000"       ,  "%,06.5f"           ,  0.0         );
    checkFormat(            "0.00000"       ,  "%,07.5f"           ,  0.0         );
    checkFormat(           "00.00000"       ,  "%,08.5f"           ,  0.0         );
    checkFormat(          "000.00000"       ,  "%,09.5f"           ,  0.0         );
    checkFormat(         " 000.00000"       , "%#,010.5f"           ,  0.0         );
    checkFormat(        "0,000.00000"       , "%#,011.5f"           ,  0.0         );
    checkFormat(       "00,000.00000"       , "%#,012.5f"           ,  0.0         );
    checkFormat(      "000,000.00000"       , "%#,013.5f"           ,  0.0         );
    checkFormat(     " 000,000.00000"       , "%#,014.5f"           ,  0.0         );
    checkFormat(    "0,000,000.00000"       , "%#,015.5f"           ,  0.0         );
    checkFormat(   "00,000,000.00000"       , "%#,016.5f"           ,  0.0         );

    checkFormat(          "1.00000"         , "%,#5.5f"            ,  1.0         );
    checkFormat(          "1.00000"         , "%,#6.5f"            ,  1.0         );
    checkFormat(          "1.00000"         , "%,#7.5f"            ,  1.0         );
    checkFormat(         " 1.00000"         , "%,#8.5f"            ,  1.0         );
    checkFormat(        "  1.00000"         , "%,#9.5f"            ,  1.0         );
    checkFormat(       "   1.00000"         , "%,#10.5f"           ,  1.0         );
    checkFormat(      "    1.00000"         , "%,#11.5f"           ,  1.0         );
    checkFormat(     "     1.00000"         , "%,#12.5f"           ,  1.0         );
    checkFormat(    "      1.00000"         , "%,#13.5f"           ,  1.0         );
    checkFormat(   "       1.00000"         , "%,#14.5f"           ,  1.0         );
    checkFormat(  "        1.00000"         , "%,#15.5f"           ,  1.0         );
    checkFormat( "         1.00000"         , "%,#16.5f"           ,  1.0         );

    checkFormat(          "1.00000"         , "%,#05.5f"            ,  1.0         );
    checkFormat(          "1.00000"         , "%,#06.5f"            ,  1.0         );
    checkFormat(          "1.00000"         , "%,#07.5f"            ,  1.0         );
    checkFormat(         "01.00000"         , "%,#08.5f"            ,  1.0         );
    checkFormat(        "001.00000"         , "%,#09.5f"            ,  1.0         );
    checkFormat(       " 001.00000"         , "%,#010.5f"           ,  1.0         );
    checkFormat(      "0,001.00000"         , "%,#011.5f"           ,  1.0         );
    checkFormat(     "00,001.00000"         , "%,#012.5f"           ,  1.0         );
    checkFormat(    "000,001.00000"         , "%,#013.5f"           ,  1.0         );
    checkFormat(   " 000,001.00000"         , "%,#014.5f"           ,  1.0         );
    checkFormat(  "0,000,001.00000"         , "%,#015.5f"           ,  1.0         );
    checkFormat( "00,000,001.00000"         , "%,#016.5f"           ,  1.0         );

    checkFormat(           "0.00000"        , "%,#.5f"              ,          0.0 );
    checkFormat(           "1.00000"        , "%,#.5f"              ,          1.0 );
    checkFormat(          "10.00000"        , "%,#.5f"              ,         10.0 );
    checkFormat(         "100.00000"        , "%,#.5f"              ,        100.0 );
    checkFormat(       "1,000.00000"        , "%,#.5f"              ,       1000.0 );
    checkFormat(      "10,000.00000"        , "%,#.5f"              ,      10000.0 );
    checkFormat(     "100,000.00000"        , "%,#.5f"              ,     100000.0 );
    checkFormat(   "1,000,000.00000"        , "%,#.5f"              ,    1000000.0 );
    checkFormat(  "10,000,000.00000"        , "%,#.5f"              ,   10000000.0 );
    checkFormat( "100,000,000.00000"        , "%,#.5f"              ,  100000000.0 );


    UT_PRINT( "ALib Format Tests Java Style: Done" );

}

//--------------------------------------------------------------------------------------------------
//--- Test PythonStyle
//--------------------------------------------------------------------------------------------------
#if ALIB_NUNIT
    [Test()]
#endif
#if ALIB_IDE_VSTUDIO
    [TestMethod]
    #if !WINDOWS_PHONE
        [TestCategory("CS_Strings_Format")]
    #endif
#endif
public void FormatterPythonStyle()
{
    UT_PRINT( "ALib Format Tests Python Style: Start" );

    FormatterPythonStyle formatter= new FormatterPythonStyle();
    formatter.Next = new FormatterJavaStyle();
    testFormatter= formatter;

    formatter.AlternativeNumberFormat.DecimalPointChar=     ',';
    formatter.AlternativeNumberFormat.ThousandsGroupChar=   '.';


    NumberFormat nfBackup= new NumberFormat();
    nfBackup.Set( formatter.DefaultNumberFormat );


    //===== null  =========
    checkFormat( "Hello PX"                   , "Hello {}", 'P', null, null, "X", null);

    //===== Conversion '!'  =========
    checkFormat("Hello world"                , "{}{!X} {}"                 , "Hello", "freaking", "world"  );
    checkFormat("world"                      , "{!X}{!X}{}"                , "Hello", "freaking", "world"  );
    checkFormat(""                           , "{!X}{!X}{!X}"              , "Hello", "freaking", "world"  );
    checkFormat("HELLO world"                , "{!U} {!L}"                 , "hELlo", "WorlD"  );
    checkFormat("HELLO hello"                , "{!U} {0!L}"                , "hELlo"           );
    checkFormat("ABC abc"                    , "{1!U} {1!L}"               , "hELlo", "abc"    );
    checkFormat("This \"is\" it"             , "This {!str} it"            , "is"              );
    checkFormat("This is \"quoted\""         , "This is {!Quote}"          , "quoted"          );
    checkFormat("This is \"quoted\""         , "This is {!Qu}"             , "quoted"          );
    checkFormat("This is \"QUOTEDUPPER\""    , "This is {!Qu!UP}"          , "quotedUpper"      );
    checkFormat("This is \"QUOTEDUPPER\""    , "This is {!Up!Qu}"          , "quotedUpper"      );
    checkFormat("This is \"quotedlower\""    , "This is {!Up!Qu!Lo}"       , "quotedLOWER"      );
    checkFormat("This is \"quotedlower\""    , "This is {!Qu!Lo}"          , "quotedLOWER"      );

    checkFormat("X   Y"                      , "X{!Fill}Y"                 , 3      );
    checkFormat("XY"                         , "X{!Fill}Y"                 , 0      );
    checkFormat("X@@@Y"                      , "X{!FillC@}Y"               , 3      );
    checkFormat("X   Y"                      , "X{!FillC}Y"                , 3      );

    checkFormat("Tab     X"                  , "Tab{!Tab}"                 , "X"      );
    checkFormat("Tab10     X"                , "Tab10{!Tab10}"             , "X"      );
    checkFormat("Tab10x    X"                , "Tab10x{!Tab10}"            , "X"      );
    checkFormat("Tab10xx   X"                , "Tab10xx{!Tab10}"           , "X"      );
    checkFormat("Tab10xxxx X"                , "Tab10xxxx{!Tab10}"         , "X"      );
    checkFormat("Tab10xxxxx          X"      , "Tab10xxxxx{!Tab10}"        , "X"      );
    checkFormat("Tab10xxxxxx         X"      , "Tab10xxxxxx{!Tab10}"       , "X"      );
    checkFormat("Tab10xxxxxx*********X"      , "Tab10xxxxxx{!TabC*10}"     , "X"      );
    checkFormat("   X\n   Y"                 , "{!Tab3}\\n{!Tab3}"         , "X", "Y" );

    checkFormat("ATab2 X"                    , "ATab2{!ATab2}"            , "X"           );
    checkFormat("ATab2x  X"                  , "ATab2x{!ATab2}"           , "X"           );
    checkFormat("ATab2xx X"                  , "ATab2xx{!ATab2}"          , "X"           );
    checkFormat("ATab2xxx  X"                , "ATab2xxx{!ATab2}"         , "X"           );
    checkFormat("ATab2xxxx X"                , "ATab2xxxx{!ATab2}"        , "X"           );
    checkFormat("ATab2x    X"                , "ATab2x{!ATab2}"           , "X"           );
    checkFormat("ATab2x    X Y"              , "ATab2x{!ATab2}{!ATab3}"   , "X"   , "Y"   );
    checkFormat("ATab2x    Xxx   Y"          , "ATab2x{!ATab2}{!ATab3}"   , "Xxx" , "Y"   );
    checkFormat("ATab2x    Xxxx  Y"          , "ATab2x{!ATab2}{!ATab3}"   , "Xxxx", "Y"   );
    checkFormat("          ABC   123"        , "{!ATab2}{!ATab3}"         , "ABC" , "123" );
    checkFormat("          abc   123"        , "{!ATab2!L}{!ATab3}"       , "ABC" , "123" );
    checkFormat("==========abc---123"        , "{!ATabC=2!L}{!ATabC-3}"   , "ABC" , "123" );
    checkFormat(" X Y"                       , "{!ATabRes!ATab2}{!ATab3}" , "X"   , "Y"   );
    formatter.Reset();

    checkFormat("\\r\\n\\t"                  , "{!ESC<}"                  , "\r\n\t"      );
    checkFormat("\t\\r\\n\\t\t"              , "\t{!ESC<}\t"              , "\r\n\t"      );
    checkFormat("\\xFF"                      , "{!ESC<}"                  , "\xFF"        );
    checkFormat("\\xE5"                      , "{!ESC<}"                  , "\xE5"        );
    checkFormat("\\033\\t"                   , "{!ESC<}"                  , "\x001B\t"    );

    checkFormat("\r"                         , "{!ESC>}"                  , "\\r"         );
    checkFormat("\r\n\t"                     , "{!ESC>}"                  , "\\r\\n\\t"   );
    checkFormat("\t\r\n\t\t"                 , "\t{!ESC>}\t"              , "\\r\\n\\t"   );
    checkFormat("\xFF"                       , "{!ESC>}"                  , "\\xFF"       );
    checkFormat("\xE5"                       , "{!ESC>}"                  , "\\xE5"       );
    checkFormat("\x001B\t"                   , "{!ESC>}"                  , "\\033\\t"    );

    checkFormat("This is right"              , "This is {!Repl<wrong><right>}" , "wrong"  );
    checkFormat("Never empty: abc"           , "Never empty: {!Repl<><N/A>}"   , "abc"    );
    checkFormat("Never empty: N/A"           , "Never empty: {!Repl<><N/A>}"   , ""       );

    checkFormat("Auto width"                 , "Auto {!AWidth:>}"         , "width"  );
    checkFormat("Auto     w"                 , "Auto {!AWidth:>}"         , "w"      );
    formatter.Reset();

    //============================ Samples taken from Python docs ==================================
    checkFormat( "a, b, c"          , "{0}, {1}, {2}"           ,  'a', 'b', 'c' );
    checkFormat( "a, b, c"          , "{}, {}, {}"              ,  'a', 'b', 'c' );
    checkFormat( "c, b, a"          , "{2}, {1}, {0}"           ,  'a', 'b', 'c' );

    checkFormat( "abracadabra"      , "{0}{1}{0}"               ,  "abra", "cad" );

    //===== replace brackets and new line =========
    checkFormat("repl. brackets{ X"   , "repl. brackets{{ {}"              , "X" );
    checkFormat("repl. brackets{{X"   , "repl. brackets{{{{{}"             , "X" );
    checkFormat("repl. brackets} X"   , "repl. brackets}} {}"              , "X" );
    checkFormat("repl. X}brackets{"   , "repl. {}}}brackets{{"             , "X" );


    checkFormat("x\\nxX"                , "x\\nx"                          , "X" ); // not a format string (no replacement)
    checkFormat("x\nx{}X"               , "x\nx{}"                         , "X" ); // not a format string (contains \n)
    checkFormat("y\nyX"                 , "y\\ny{}"                        , "X" ); // a format string (contains \n)

    //===== Boolean =========
    checkFormat("true false true false true", "{:B} {:B} {:B} {:B} {:B}"  , true, false, 1, 0, "Hello"  );
    checkFormat("true",         "{:B}"   , true  );
    checkFormat("false",        "{:B}"   , false );
    checkFormat("true",         "{:B}"   ,  1    );
    checkFormat("true",         "{:B}"   , -1    );
    { Formatter x = null;      checkFormat("false",  "{:B}"   , x     );}
    { Formatter x = formatter; checkFormat("true" ,  "{:B}"   , x     );}

    checkFormat("true",         "{:.4B}"   , true  );
    checkFormat("fals",         "{:.4B}"   , false );
    checkFormat("tru",          "{:.3B}"   , true  );
    checkFormat("fal",          "{:.3B}"   , false );
    checkFormat("  tru",        "{:5.3B}"  , true  );
    checkFormat("  fal",        "{:5.3B}"  , false );
    checkFormat(" true",        "{:5.6B}"  , true  );
    checkFormat("false",        "{:5.6B}"  , false );

    //===== h/H Hash Code (extension to Python format spec) =========
    checkFormat(   "ff"            , "{:h}"                    , 255);
    checkFormat( "0xff"            , "{:#h}"                   , 255);
    checkFormat(   "FF"            , "{:H}"                    , 255);
    checkFormat( "0xFF"            , "{:#H}"                   , 255);


    //===== ticks/calendar =========
    {
        DateTime dt= new DateTime(2016,12,03,14,05,22,100);
        checkFormat("2016-12-03 14:05:22"   , "{:yyyy-MM-dd HH:mm:ss}"      , dt);
        checkFormat("2016"                  , "{:yyyy}"                     , dt);
        checkFormat("Sat"                   , "{:ddd}"                      , dt);
        checkFormat("Saturday"              , "{:dddd}"                     , dt);

        // set locale
        if (CultureInfo.CurrentCulture.EnglishName.StartsWith("German") )
        {
            formatter.DateTimeFormatProvider = DateTimeFormatInfo.CurrentInfo;
            checkFormat("Samstag", "{:dddd}", dt);
            formatter.DateTimeFormatProvider = DateTimeFormatInfo.InvariantInfo;
        }
    }

    {
        TimeSpan interval= new TimeSpan(1,2,3,4);

         checkFormat("1.02:03:04"   , "{}"            ,   interval );
         checkFormat("1"            , "{:%d}"         ,   interval );
         checkFormat("2"            , "{:%h}"         ,   interval );
         checkFormat("3"            , "{:%m}"         ,   interval );
         checkFormat("4"            , "{:%s}"         ,   interval );
         checkFormat("01020304"     , "{:ddhhmmss}"   ,   interval );

    }

    //================================== Mixed tests ==============================================
    {
        checkFormat( "a  "             , "{:3}"                       ,  'a'  );
        checkFormat( "ab "             , "{:3}"                       ,  "ab" );

        checkFormat( "  3"             , "{:3}"                       ,   3 );
        checkFormat( " 13"             , "{:3}"                       ,  13 );

        checkFormat( "0,1,0,2"         , "{},{},{0},{}"               ,0,1,2);
        checkFormat( "3,0,1,0,2"       , "{3},{},{},{0},{}"           ,0,1,2,3);
    }

    //======================================= Errors ===========================================

    checkError ( "Duplicate type code"      , "{:df}"        , 'x'    ); // double type code
    checkError ( "Incompatible format code" , "{:f}"         , 'x'    ); // wrong type
    checkError ( "Missing argument #1"      , "{}{}"         , 'x'    ); // to few arguments


    //======================================= Characters ===========================================

    checkFormat( "x"                        , "{}"           , 'x'          );
    checkFormat( "x    "                    , "{:5c}"        , 'x'          );
    checkFormat( "\u03B1"                   , "{:c}"         , '\x03B1'    ); //greek alpha
    checkFormat( "\u03B1    "               , "{:5c}"        , '\x03B1'    ); //greek alpha
    checkFormat( "@"                        , "{:c}"         , 64           ); // int   ascii @
    checkFormat( "@"                        , "{:c}"         , 64L          ); // long  ascii @
    checkFormat( "@"                        , "{:c}"         , 64UL         ); // ulong ascii @

    // alignment
    checkFormat( "#x  #"                , "#{:<3}#"         , 'x'    );
    checkFormat( "# x #"                , "#{:^3}#"         , 'x'    );
    checkFormat( "#  x#"                , "#{:>3}#"         , 'x'    );

    //======================================= Strings ===========================================
    checkFormat( "x"                 , "{}"         , "x"    );
    checkFormat( "xy"                , "{}"         , "xy"    );
    checkFormat( "xy"                , "{:s}"       , "xy"    );

    checkFormat( "xyz"                , "{}z"       , "xy"    );
    checkFormat( "xyz"                , "{:2}z"     , "xy"    );
    checkFormat( "xy z"               , "{:3}z"     , "xy"    );

    // precision (max width)
    checkFormat( "xyz"                , "{:.4s}"       , "xyz"    );
    checkFormat( "xyz"                , "{:.3s}"       , "xyz"    );
    checkFormat( "xy"                 , "{:.2s}"       , "xyz"    );


    // alignment
    checkFormat( "#x  #"                , "#{:<3}#"         , "x"    );
    checkFormat( "# x #"                , "#{:^3}#"         , "x"    );
    checkFormat( "#  x#"                , "#{:>3}#"         , "x"    );
    checkFormat( "#1234#"               , "#{:^3}#"         , "1234" );

    //===== Strings width/precision =========
    checkFormat("aBcDe",         "{:s}"          , "aBcDe"  );
    checkFormat("aBc",           "{:.3s}"        , "aBcDe"  );
    checkFormat("  aBc",         "{:>5.3s}"      , "aBcDe"  );
    checkFormat("ABC   ",        "{!UP:-6.3s}"   , "aBcDe"  );
    checkFormat(" ABC  ",        "{!UP:^6.3s}"   , "aBcDe"  );
    checkFormat("ABCDE",         "{!UP:3s}"      , "aBcDe"  );

    checkFormat("aBcDe",         "{:}"          , "aBcDe"  );
    checkFormat("aBc",           "{:.3}"        , "aBcDe"  );
    checkFormat("  aBc",         "{:>5.3}"      , "aBcDe"  );
    checkFormat("ABC   ",        "{!UP:-6.3}"   , "aBcDe"  );
    checkFormat(" ABC  ",        "{!UP:^6.3}"   , "aBcDe"  );
    checkFormat("ABCDE",         "{!UP:3}"      , "aBcDe"  );


    //===================================== C# int types  ==========================================
    { sbyte  val=-1;    checkFormat( "-1"                    , "{:2}"              ,  val    ); }
    { byte   val= 2;    checkFormat( " 2"                    , "{:2}"              ,  val    ); }
    { short  val=-3;    checkFormat( "-3"                    , "{:2}"              ,  val    ); }
    { ushort val= 4;    checkFormat( " 4"                    , "{:2}"              ,  val    ); }
    { int    val=-5;    checkFormat( "-5"                    , "{:2}"              ,  val    ); }
    { uint   val= 6;    checkFormat( " 6"                    , "{:2}"              ,  val    ); }
    { long   val=-7;    checkFormat( "-7"                    , "{:2}"              ,  val    ); }
    { ulong  val= 8;    checkFormat( " 8"                    , "{:2}"              ,  val    ); }


    //======================================= Integers (Decimal) ===========================================

    checkFormat( "0"                    , "{}"              ,  0    );
    checkFormat( "1"                    , "{}"              ,  1    );
    checkFormat( "5"                    , "{}"              ,  5    );
    checkFormat( "-1"                   , "{}"              ,  -1   );
    checkFormat( "-5"                   , "{}"              ,  -5   );
    checkFormat( "0"                    , "{}"              ,  0U   );
    checkFormat( "1"                    , "{}"              ,  1U   );
    checkFormat( "5"                    , "{}"              ,  5U   );
    checkFormat( "-2147483648"          , "{}"              ,   int.MinValue   );
    checkFormat( "2147483647"           , "{}"              ,   int.MaxValue   );
    checkFormat( "-2147483647"          , "{}"              ,   int.MinValue +1);
    checkFormat( "2147483646"           , "{}"              ,   int.MaxValue -1);
    checkFormat( "0"                    , "{}"              ,  uint.MinValue   );
    checkFormat( "4294967295"           , "{}"              ,  uint.MaxValue   );
    checkFormat( "1"                    , "{}"              ,  uint.MinValue +1);
    checkFormat( "4294967294"           , "{}"              ,  uint.MaxValue -1);
    checkFormat( "-9223372036854775808" , "{}"              ,  long.MinValue   );
    checkFormat( "9223372036854775807"  , "{}"              ,  long.MaxValue   );
    checkFormat( "-9223372036854775807" , "{}"              ,  long.MinValue +1);
    checkFormat( "9223372036854775806"  , "{}"              ,  long.MaxValue -1);
    checkFormat( "0"                    , "{}"              , ulong.MinValue   );
    checkFormat( "18446744073709551615" , "{}"              , ulong.MaxValue   );
    checkFormat( "1"                    , "{}"              , ulong.MinValue +1);
    checkFormat( "18446744073709551614" , "{}"              , ulong.MaxValue -1);




    // integer sign
    checkFormat( "0"                    , "{:}"             ,  0    );
    checkFormat( "1"                    , "{:}"             ,  1    );
    checkFormat( "-1"                   , "{:}"             , -1    );

    checkFormat( " 0"                   , "{: }"            ,  0    );
    checkFormat( " 1"                   , "{: }"            ,  1    );
    checkFormat( "-1"                   , "{: }"            , -1    );

    checkFormat( "+0"                   , "{:+}"            ,  0    );
    checkFormat( "+1"                   , "{:+}"            ,  1    );
    checkFormat( "-1"                   , "{:+}"            , -1    );

    // integer field width
    checkFormat( " 0"                   , "{:2}"            ,  0    );
    checkFormat( "1234"                 , "{:2}"            ,  1234    );

    // integer mindigits
    checkFormat(  "000"                 , "{:03}"           ,  0    );
    checkFormat(  "001"                 , "{:03}"           ,  1    );
    checkFormat(  "-01"                 , "{:03}"           , -1    );
    checkFormat(  " 00"                 , "{:03 }"          ,  0    );
    checkFormat(  " 01"                 , "{:03 }"          ,  1    );
    checkFormat(  "-01"                 , "{:03 }"          , -1    );

    checkError ( "Precision not allowed", "{:.3}"         ,  123456);


    //======================================= Binary ===========================================

    // variable length

    // without separators
    checkFormat(                                                 "0", "{:b}" ,         0x00  );
    checkFormat(                                                 "1", "{:b}" ,         0x01  );
    checkFormat(                                                "10", "{:b}" ,         0x02  );
    checkFormat(                                              "1001", "{:b}" ,         0x09  );
    checkFormat(                                              "1111", "{:b}" ,         0x0F  );
    checkFormat(                                             "10001", "{:b}" ,         0x11  );
    checkFormat(                                          "10001111", "{:b}" ,         0x8F  );
    checkFormat(                                         "100111110", "{:b}" ,        0x13E  );
    checkFormat(                                  "1111111111111111", "{:b}" ,       0xFFFF  );
    checkFormat(                  "10000001100000011111111111111111", "{:b}" ,   0x8181FFFFL );

    // with separators
    // default

    formatter.DefaultNumberFormat.BinNibbleGroupChar=   '~';
    formatter.DefaultNumberFormat.BinByteGroupChar=     '\'';
    formatter.DefaultNumberFormat.BinWordGroupChar=     '-';
    formatter.DefaultNumberFormat.BinWord32GroupChar=   '#';
    checkFormat(                                                 "0", "{:b,}",         0x00  );
    checkFormat(                                                 "1", "{:b,}",         0x01  );
    checkFormat(                                                "10", "{:b,}",         0x02  );
    checkFormat(                                              "1001", "{:b,}",         0x09  );
    checkFormat(                                              "1111", "{:b,}",         0x0F  );
    checkFormat(                                            "1~0001", "{:b,}",         0x11  );
    checkFormat(                                         "1000~1111", "{:b,}",         0x8F  );
    checkFormat(                                       "1'0011~1110", "{:b,}",        0x13E  );
    checkFormat(                               "1111~1111'1111~1111", "{:b,}",       0xFFFF  );
    checkFormat(           "1000~0001'1000~0001-1111~1111'1111~1111", "{:b,}",   0x8181FFFFL );

    checkFormat( "1111~1111#0001~0001'0010~0010-0011~0011'0100~0100", "{:b,}", 0xFF11223344  );

    formatter.DefaultNumberFormat.BinNibbleGroupChar=     '\0';
    checkFormat( "11111111#00010001'00100010-00110011'01000100", "{:b,}", 0xFF11223344L );
    formatter.DefaultNumberFormat.Set(nfBackup);

    // fixed length
    checkFormat(                                "0000000100111110", "{:16b}" ,              0x13E  );
    checkFormat(                                "1001000100111110", "{:16b}" ,             0x913E  );
    checkFormat(                                "1001000100111110", "{:16b}" ,       0xABCDEF913E  );
    checkFormat(                               "11001000100111110", "{:17b}" ,       0xABCDEF913E  );
    checkFormat(    "1111000011110000111100001111000011110000111100001111000011110000", "{:64b}" , 0xF0F0F0F0F0F0F0F0  );

    checkFormat( "bbb1111000011110000111100001111000011110000111100001111000011110000", "{:b>67b}" , 0xF0F0F0F0F0F0F0F0  );


    // including 0b
    checkFormat(                                              "0b0", "{:#b}"  ,        0x00  );
    checkFormat(                                              "0b1", "{:#b}"  ,        0x01  );
    checkFormat(                                             "0b10", "{:#b}"  ,        0x02  );
    checkFormat(                                             "0b11", "{:#,b}" ,        0x03  );
    checkFormat(                                         "0b1'0001", "{:#,b}" ,        0x11  );
    checkFormat(                                             "0b0",  "{:0#b}" ,        0x00  );
    checkFormat(                                                "0", "{:1#b}" ,        0x00  );
    checkFormat(                                               "0b", "{:2#b}" ,        0x00  );
    checkFormat(                                              "0b0", "{:3#b}" ,        0x00  );
    checkFormat(                                             "0b00", "{:4#b}" ,        0x00  );
    checkFormat(                                            "0b000", "{:5#b}" ,        0x00  );
    checkFormat(                                         "0b1'0001", "{:8#,b}",        0x11  );
    checkFormat(                                        "0b01'0001", "{:9#,b}",        0x11  );
    checkFormat(                                       "0b001'0001", "{:10#,b}",       0x11  );
    checkFormat(                                         "0b 0001", "{:7#,b}",        0x11  );
    checkFormat(                                          "0b0001", "{:6#,b}",        0x11  );
    checkFormat(                                           "0b001", "{:5#,b}",        0x11  );


    //======================================= Hex ===========================================

    // variable length
    // without separators
    checkFormat(                          "0", "{:X}"                ,                 0x00  );
    checkFormat(                          "1", "{:X}"                ,                 0x01  );
    checkFormat(                          "2", "{:X}"                ,                 0x02  );
    checkFormat(                          "9", "{:X}"                ,                 0x09  );
    checkFormat(                          "F", "{:X}"                ,                 0x0F  );
    checkFormat(                         "11", "{:X}"                ,                 0x11  );
    checkFormat(                         "8F", "{:X}"                ,                 0x8F  );
    checkFormat(                        "13E", "{:X}"                ,                0x13E  );
    checkFormat(                       "FFFF", "{:X}"                ,               0xFFFF  );
    checkFormat(                   "8181FFFF", "{:X}"                ,           0x8181FFFFL );
    checkFormat(                   "FFFFFFFF", "{:X}"                ,           0xFFFFFFFFL );
    checkFormat(           "FFFFFFFFFFFFFFFF", "{:X}"                ,   0xFFFFFFFFFFFFFFFFL );
    checkFormat(           "FFFFFFFFFFFFFFFF", "{:X}"                ,   0xFFFFFFFFFFFFFFFFUL);
    checkFormat(           "FFFFFFFFFFFFFFFF", "{:X}"                ,             (long) -1 );

    // -------------- variable length, lower case --------
    // without separators
    checkFormat(                          "0", "{:x}"                ,                 0x00  );
    checkFormat(                          "1", "{:x}"                ,                 0x01  );
    checkFormat(                          "2", "{:x}"                ,                 0x02  );
    checkFormat(                          "9", "{:x}"                ,                 0x09  );
    checkFormat(                          "f", "{:x}"                ,                 0x0F  );
    checkFormat(                         "11", "{:x}"                ,                 0x11  );
    checkFormat(                         "8f", "{:x}"                ,                 0x8F  );
    checkFormat(                        "13e", "{:x}"                ,                0x13E  );
    checkFormat(                       "ffff", "{:x}"                ,               0xFFFF  );
    checkFormat(                   "8181ffff", "{:x}"                ,           0x8181FFFFL );
    checkFormat(                   "ffffffff", "{:x}"                ,           0xFFFFFFFFL );
    checkFormat(           "ffffffffffffffff", "{:x}"                ,   0xFFffFFffFFffFFffUL);


    // with separators
    // default
    checkFormat( "FF'1122'3344", "{:X,}", 0xFF11223344  );
    formatter.DefaultNumberFormat.HexByteGroupChar=     '\'';
    formatter.DefaultNumberFormat.HexWordGroupChar=     '-';
    formatter.DefaultNumberFormat.HexWord32GroupChar=   '#';
    checkFormat(                         "8F", "{:X,}"               ,         0x8F  );
    checkFormat(                       "1'3E", "{:X,}"               ,        0x13E  );
    checkFormat(                      "FF'FF", "{:X,}"               ,       0xFFFF  );
    checkFormat(                "81'81-FF'FF", "{:X,}"               ,   0x8181FFFFL );
    checkFormat(             "FF#11'22-33'44", "{:X,}"               , 0xFF11223344  );

    formatter.DefaultNumberFormat.HexByteGroupChar=     '\0';
    checkFormat( "FF#1122-3344", "{:X,}"                , 0xFF11223344  );
    formatter.DefaultNumberFormat.SetComputational();
    formatter.DefaultNumberFormat.WriteExponentPlusSign= true;



    // fixed length
    checkFormat(                  "A3E", "{:0X}"    ,             0xA3E  );
    checkFormat(                    "E", "{:1X}"    ,             0xA3E  );
    checkFormat(                   "3E", "{:2X}"    ,             0xA3E  );
    checkFormat(                  "A3E", "{:3X}"    ,             0xA3E  );
    checkFormat(                 "0A3E", "{:4X}"    ,             0xA3E  );
    checkFormat(                "00A3E", "{:5X}"    ,             0xA3E  );
    checkFormat(               "000A3E", "{:6X}"    ,             0xA3E  );
    checkFormat(              "0000A3E", "{:7X}"    ,             0xA3E  );
    checkFormat(             "00000A3E", "{:8X}"    ,             0xA3E  );
    checkFormat(            "000000A3E", "{:9X}"    ,             0xA3E  );
    checkFormat(      "000000000000A3E", "{:15X}"   ,             0xA3E  );
    checkFormat(     "0000000000000A3E", "{:16X}"   ,             0xA3E  );
    checkFormat(     "0000000000000A3E", "{:>16X}"  ,             0xA3E  );
    checkFormat(    " 0000000000000A3E", "{:17X}"   ,             0xA3E  );
    checkFormat(   "  0000000000000A3E", "{:18X}"   ,             0xA3E  );
    checkFormat(    " 0000000000000A3E", "{:>17X}"  ,             0xA3E  );
    checkFormat(   "  0000000000000A3E", "{:>18X}"  ,             0xA3E  );

    // width

    checkFormat(                    "E", "{:1X}"    ,             0xA3E  );
    checkFormat(                   "3E", "{:2X}"    ,             0xA3E  );
    checkFormat(                  "A3E", "{:3X}"    ,             0xA3E  );

    // including 0x
    checkFormat(                "0xA3E",  "{:0#X}"  ,             0xA3E  );
    checkFormat(                    "0",  "{:1#X}"  ,             0xA3E  );
    checkFormat(                   "0x",  "{:2#X}"  ,             0xA3E  );
    checkFormat(                  "0xE",  "{:3#X}"  ,             0xA3E  );
    checkFormat(                 "0x3E",  "{:4#X}"  ,             0xA3E  );
    checkFormat(                "0xA3E",  "{:5#X}"  ,             0xA3E  );
    checkFormat(               "0x0A3E", "{:6#X}"   ,             0xA3E  );
    checkFormat(              "0x00A3E", "{:7#X}"   ,             0xA3E  );
    checkFormat(             "0x000A3E", "{:8#X}"   ,             0xA3E  );
    checkFormat(            "0x0000A3E", "{:9#X}"   ,             0xA3E  );
    checkFormat(      "0x0000000000A3E", "{:15#X}"  ,             0xA3E  );
    checkFormat(     "0x00000000000A3E", "{:16#X}"  ,             0xA3E  );
    checkFormat(     "0x00000000000A3E", "{:>16#X}" ,             0xA3E  );
    checkFormat(    "0x000000000000A3E", "{:17#X}"  ,             0xA3E  );
    checkFormat(   "0x0000000000000A3E", "{:18#X}"  ,             0xA3E  );
    checkFormat(   "0x0000000000000A3E", "{:>18#X}" ,             0xA3E  );
    checkFormat(  "0x0000000000000A3E ", "{:<19#X}" ,             0xA3E  );
    checkFormat(  " 0x0000000000000A3E", "{:>19#X}" ,             0xA3E  );
    checkFormat( "0x0000000000000A3E  ", "{:<20#X}" ,             0xA3E  );
    checkFormat( "  0x0000000000000A3E", "{:>20#X}" ,             0xA3E  );

    //======================================= Octal ===========================================

    // variable length
    // without separators
    checkFormat(                            "0", "{:o}"              ,                  0  );
    checkFormat(                            "1", "{:o}"              ,                  1  );
    checkFormat(                            "2", "{:o}"              ,                  2  );
    checkFormat(                            "7", "{:o}"              ,                  7  );
    checkFormat(                           "10", "{:o}"              ,                  8  );
    checkFormat(                           "11", "{:o}"              ,                  9  );
    checkFormat(                           "17", "{:o}"              ,                 15  );
    checkFormat(                           "20", "{:o}"              ,                 16  );
    checkFormat(                           "77", "{:o}"              ,                 63  );
    checkFormat(                          "100", "{:o}"              ,                 64  );
    checkFormat(                          "101", "{:o}"              ,                 65  );
    checkFormat(                       "177777", "{:o}"              ,             0xffff  );
    checkFormat(                  "37777777777", "{:o}"              ,         0xffffffffL );
    checkFormat(             "7777777777777777", "{:o}"              ,     0xffffffffffff  );
    checkFormat(       "1777777777777777777777", "{:o}"              , 0xFFffFFffFFffFFffUL);
    checkFormat(       "1777777777777777777777", "{:o}"              ,           (long) -1 );

    // with separator
    checkFormat(                            "0", "{:,o}"             ,                  0  );
    checkFormat(                            "1", "{:,o}"             ,                  1  );
    checkFormat(                            "2", "{:,o}"             ,                  2  );
    checkFormat(                            "7", "{:,o}"             ,                  7  );
    checkFormat(                           "10", "{:,o}"             ,                  8  );
    checkFormat(                           "11", "{:,o}"             ,                  9  );
    checkFormat(                           "17", "{:,o}"             ,                 15  );
    checkFormat(                           "20", "{:,o}"             ,                 16  );
    checkFormat(                           "77", "{:,o}"             ,                 63  );
    checkFormat(                          "100", "{:,o}"             ,                 64  );
    checkFormat(                          "101", "{:,o}"             ,                 65  );
    checkFormat(                      "177'777", "{:,o}"             ,             0xffff  );
    checkFormat(               "37'777'777'777", "{:,o}"             ,         0xffffffffL );
    checkFormat(        "7'777'777'777'777'777", "{:,o}"             ,     0xffffffffffff  );

    checkFormat( "1'777'777'777'777'777'777'777", "{:,o}"            , 0xFFffFFffFFffFFffUL);
    checkFormat( "1'777'777'777'777'777'777'777", "{:,o}"            ,           (long) -1 );



    // ints with thousands separator
    checkFormat(           "0"               , "{:00,}"              ,  0            );
    checkFormat(           "0"               , "{:01,}"              ,  0            );
    checkFormat(          "00"               , "{:02,}"              ,  0            );
    checkFormat(         "000"               , "{:03,}"              ,  0            );
    checkFormat(        " 000"               , "{:04,}"              ,  0            );
    checkFormat(       "0,000"               , "{:05,}"              ,  0            );
    checkFormat(      "00,000"               , "{:06,}"              ,  0            );
    checkFormat(     "000,000"               , "{:07,}"              ,  0            );
    checkFormat(    " 000,000"               , "{:08,}"              ,  0            );
    checkFormat(   "0,000,000"               , "{:09,}"              ,  0            );

    checkFormat(           "1"               , "{:00,}"              ,  1            );
    checkFormat(           "1"               , "{:01,}"              ,  1            );
    checkFormat(          "01"               , "{:02,}"              ,  1            );
    checkFormat(         "001"               , "{:03,}"              ,  1            );
    checkFormat(        " 001"               , "{:04,}"              ,  1            );
    checkFormat(       "0,001"               , "{:05,}"              ,  1            );
    checkFormat(      "00,001"               , "{:06,}"              ,  1            );
    checkFormat(     "000,001"               , "{:07,}"              ,  1            );
    checkFormat(    " 000,001"               , "{:08,}"              ,  1            );
    checkFormat(   "0,000,001"               , "{:09,}"              ,  1            );

    checkFormat(           "0"               , "{:,}"                ,          0    );
    checkFormat(           "1"               , "{:,}"                ,          1    );
    checkFormat(          "10"               , "{:,}"                ,         10    );
    checkFormat(         "100"               , "{:,}"                ,        100    );
    checkFormat(       "1,000"               , "{:,}"                ,       1000    );
    checkFormat(      "10,000"               , "{:,}"                ,      10000    );
    checkFormat(     "100,000"               , "{:,}"                ,     100000    );
    checkFormat(   "1,000,000"               , "{:,}"                ,    1000000    );
    checkFormat(  "10,000,000"               , "{:,}"                ,   10000000    );
    checkFormat( "100,000,000"               , "{:,}"                ,  100000000    );

    checkFormat(           "0"               , "{:,}"                ,          0    );
    checkFormat(           "1"               , "{:,}"                ,          1    );
    checkFormat(          "12"               , "{:,}"                ,         12    );
    checkFormat(         "123"               , "{:,}"                ,        123    );
    checkFormat(       "1,234"               , "{:,}"                ,       1234    );
    checkFormat(      "12,345"               , "{:,}"                ,      12345    );
    checkFormat(     "123,456"               , "{:,}"                ,     123456    );
    checkFormat(   "1,234,567"               , "{:,}"                ,    1234567    );
    checkFormat(  "12,345,678"               , "{:,}"                ,   12345678    );
    checkFormat( "123,456,789"               , "{:,}"                ,  123456789    );


    //======================================= Floats ===========================================

    // mixed tests
    checkFormat(                    "0.0", "{}"              ,        0.0 );
    checkFormat(     "0.3333333333333333", "{}"              ,    1.0/3.0 );
    checkFormat(      "3.333333333333334", "{}"              ,   10.0/3.0 );
    checkFormat(      "6.666666666666667", "{}"              ,   20.0/3.0 );
    checkFormat(                "4.23456", "{}"              ,    4.23456 );
    checkFormat(               "-4.23456", "{}"              ,   -4.23456 );

    checkFormat(                    "0.0", "{:.5}"              ,        0.0f );
    checkFormat(                "0.33333", "{:.5}"              ,   1.0f/3.0f );
    checkFormat(                "3.33333", "{:.5}"              ,  10.0f/3.0f );
    checkFormat(                "6.66667", "{:.5}"              ,  20.0f/3.0f );
    checkFormat(                "4.23456", "{:.5}"              ,    4.23456f );
    checkFormat(               "-4.23456", "{:.5}"              ,   -4.23456f );

    checkFormat(                "0.0E+00", "{:E}"            ,        0.0 );
    checkFormat(           "0.000000E+00", "{:#E}"           ,        0.0 );

    checkFormat(              "123.45"   , "{}"              ,     123.45 );
    checkFormat(              "123.4"    , "{:.1}"           ,     123.45 );
    checkFormat(              "123"      , "{:.0}"           ,     123.45 );
    checkFormat(              "123."     , "{:#.0}"          ,     123.45 );

    checkFormat(              "0.45"     , "{:.5}"          ,        0.45 );

    checkFormat( "1.234e+20"       , "{}"                         ,  1.234e20 );
    checkFormat( "1.234"           , "{:g}"                       ,  1.234 );
    checkFormat( "1.234"           , "{:G}"                       ,  1.234 );
    checkFormat( "1.234e+20"       , "{:g}"                       ,  1.234e20 );
    checkFormat( "1.234e+20"       , "{:.6g}"                       ,  1.234e20 );
    checkFormat( "1.234E+20"       , "{:G}"                       ,  1.234e20 );
    checkFormat( "1.234"           , "{:#g}"                      ,  1.234 );
    checkFormat( "1.234"           , "{:#G}"                      ,  1.234 );
    checkFormat( "1.234000"        , "{:f}"                       ,  1.234 );
    checkFormat( "1.234000"        , "{:F}"                       ,  1.234 );
    checkFormat( "1.234000"        , "{:#f}"                      ,  1.234 );
    checkFormat( "1.234000"        , "{:#F}"                      ,  1.234 );
    checkFormat( "1.234568"        , "{:f}"                       ,  1.23456789 );
    checkFormat( "1.234568"        , "{:F}"                       ,  1.23456789 );
    checkFormat( "1.234568"        , "{:#f}"                      ,  1.23456789 );
    checkFormat( "1.234568"        , "{:#F}"                      ,  1.23456789 );

    // locale specific
    checkFormat(  "1234.5678"         , "{:g}"           ,    1234.5678 );
    checkFormat(  "1234,5678"         , "{:n}"           ,    1234.5678 );
    checkFormat( "1,234.5678"         , "{:,g}"          ,    1234.5678 );
    checkFormat( "1.234,5678"         , "{:,n}"          ,    1234.5678 );

    // integer types as floats
    checkFormat(  "1234.0"            , "{:g}"           ,    1234 );
    checkFormat(  "1234.0"            , "{:G}"           ,    1234 );
    checkFormat(  "1234.000000"       , "{:f}"           ,    1234 );
    checkFormat(  "1234.00000"        , "{:.5f}"         ,    1234 );
    checkFormat(  "1234.00000"        , "{:#.5f}"        ,    1234 );
    checkFormat("  1234.00000"        , "{:12.5f}"       ,    1234 );
    checkFormat(  "14.0"              , "{:.5g}"         ,      14 );
    checkFormat(  "  14.00000"        , "{:#10.5g}"      ,      14 );
    checkFormat(  "14.00000"          , "{:#.5g}"        ,      14 );




    //----------------------------- floats with width and precision ----------------------------

    // floats with field width
    checkFormat(          "       0.0"       ,  "{:10}"             ,  0.0         );
    checkFormat(          "       0.0"       ,  "{:10.5}"           ,  0.0         );
    checkFormat(          "   0.00000"       , "{:#10.5}"           ,  0.0         );

    checkFormat(          "     14.05"       ,  "{:10}"             ,  14.05       );
    checkFormat(          "     14.05"       ,  "{:10.5}"           ,  14.05       );
    checkFormat(          "  14.05000"       , "{:#10.5}"           ,  14.05       );
    checkFormat(          " -14.05000"       , "{:#10.5}"           , -14.05       );
    checkFormat(           "-14.05000"       , "{:#9.5}"            , -14.05       );
    checkFormat(           "-14.05000"       , "{:#8.5}"            , -14.05       );

    // '='-alignment (forces padding after the sign)
    //     positive without sign
    checkFormat( "0012.3456789"          , "{:=12}"          ,  12.3456789   );
    checkFormat( "012.3456789"           , "{:=11}"          ,  12.3456789   );
    checkFormat( "12.3456789"            , "{:=10}"          ,  12.3456789   );
    checkFormat( "12.3456789"            , "{:=9}"           ,  12.3456789   );
    checkFormat( "12.3456789"            , "{:=8}"           ,  12.3456789   );
    checkFormat( "000012.3"              , "{:=8.1}"         ,  12.3456789   );
    checkFormat( "00012.35"              , "{:=8.2}"         ,  12.3456789   );
    checkFormat( "0012.346"              , "{:=8.3}"         ,  12.3456789   );
    checkFormat( "012.3457"              , "{:=8.4}"         ,  12.3456789   );

    checkFormat( " 012.3456789"          , "{:= 12}"         ,  12.3456789   );
    checkFormat( " 12.3456789"           , "{:= 11}"         ,  12.3456789   );
    checkFormat( " 12.3456789"           , "{:= 10}"         ,  12.3456789   );
    checkFormat( " 12.3456789"           , "{:= 9}"          ,  12.3456789   );
    checkFormat( " 12.3456789"           , "{:= 8}"          ,  12.3456789   );
    checkFormat( " 12.3456789"           , "{:= 8}"          ,  12.3456789   );
    checkFormat( " 00012.3"              , "{:= 8.1}"        ,  12.3456789   );
    checkFormat( " 0012.35"              , "{:= 8.2}"        ,  12.3456789   );
    checkFormat( " 012.346"              , "{:= 8.3}"        ,  12.3456789   );
    checkFormat( " 12.3457"              , "{:= 8.4}"        ,  12.3456789   );

    //     negative
    checkFormat( "-012.3456789"          , "{:= 12}"         , -12.3456789   );
    checkFormat( "-12.3456789"           , "{:= 11}"         , -12.3456789   );
    checkFormat( "-12.3456789"           , "{:= 10}"         , -12.3456789   );
    checkFormat( "-12.3456789"           , "{:= 9}"          , -12.3456789   );
    checkFormat( "-12.3456789"           , "{:= 8}"          , -12.3456789   );
    checkFormat( "-12.3456789"           , "{:= 8}"          , -12.3456789   );
    checkFormat( "-00012.3"              , "{:= 8.1}"        , -12.3456789   );
    checkFormat( "-0012.35"              , "{:= 8.2}"        , -12.3456789   );
    checkFormat( "-012.346"              , "{:= 8.3}"        , -12.3456789   );
    checkFormat( "-12.3457"              , "{:= 8.4}"        , -12.3456789   );

    //     positive with + sign
    checkFormat( "+012.3456789"          , "{:=+12}"         ,  12.3456789   );
    checkFormat( "+12.3456789"           , "{:=+11}"         ,  12.3456789   );
    checkFormat( "+12.3456789"           , "{:=+10}"         ,  12.3456789   );
    checkFormat( "+12.3456789"           , "{:=+9}"          ,  12.3456789   );
    checkFormat( "+12.3456789"           , "{:=+8}"          ,  12.3456789   );
    checkFormat( "+12.3456789"           , "{:=+8}"          ,  12.3456789   );
    checkFormat( "+00012.3"              , "{:=+8.1}"        ,  12.3456789   );
    checkFormat( "+0012.35"              , "{:=+8.2}"        ,  12.3456789   );
    checkFormat( "+012.346"              , "{:=+8.3}"        ,  12.3456789   );
    checkFormat( "+12.3457"              , "{:=+8.4}"        ,  12.3456789   );

    // Leading 0 in width name ( same as '='-alignment)
    checkFormat( "0012.3456789"          , "{:012}"         ,  12.3456789   );
    checkFormat( "012.3456789"           , "{:011}"         ,  12.3456789   );
    checkFormat( "12.3456789"            , "{:010}"         ,  12.3456789   );
    checkFormat( "12.3456789"            , "{:09}"          ,  12.3456789   );
    checkFormat( "12.3456789"            , "{:08}"          ,  12.3456789   );
    checkFormat( "000012.3"              , "{:08.1}"        ,  12.3456789   );
    checkFormat( "00012.35"              , "{:08.2}"        ,  12.3456789   );
    checkFormat( "0012.346"              , "{:08.3}"        ,  12.3456789   );
    checkFormat( "012.3457"              , "{:08.4}"        ,  12.3456789   );
    checkFormat( "-012.3456789"          , "{:=012}"        , -12.3456789   );
    checkFormat( "-0012.35"              , "{:=08.2}"       , -12.3456789   );

    //-------  Nan,Inf, -0.0 -------
    checkFormat( "nan"                  , "{}"              ,  double.NaN );
    checkFormat( "inf"                  , "{}"              ,  double.PositiveInfinity );
    checkFormat( "-inf"                 , "{}"              ,  double.NegativeInfinity );
    checkFormat( "0.0"                  , "{}"              ,  0.0 );
    checkFormat( "-0.0"                 , "{}"              , -0.0 ); // negative zero
    checkFormat( "nan"                  , "{:+}"            ,  double.NaN );
    checkFormat( "+inf"                 , "{:+}"            ,  double.PositiveInfinity );
    checkFormat( "-inf"                 , "{:+}"            ,  double.NegativeInfinity );
    checkFormat( "+0.0"                 , "{:+}"            ,  0.0 );
    checkFormat( "-0.0"                 , "{:+}"            , -0.0 ); // negative zero

    //-------  Nan,Inf, -0.0 -------
    checkFormat( "       nan"           , "{:10}"           ,  double.NaN );
    checkFormat( "       inf"           , "{:10}"           ,  double.PositiveInfinity );
    checkFormat( "      -inf"           , "{:10}"           ,  double.NegativeInfinity );
    checkFormat( "       0.0"           , "{:10}"           ,  0.0 );
    checkFormat( "      -0.0"           , "{:10}"           , -0.0 ); // negative zero

    checkFormat( "       nan"           , "{:+10}"          ,  double.NaN );
    checkFormat( "      +inf"           , "{:+10}"          ,  double.PositiveInfinity );
    checkFormat( "      -inf"           , "{:+10}"          , double.NegativeInfinity );
    checkFormat( "      +0.0"           , "{:+10}"          ,  0.0 );
    checkFormat( "      -0.0"           , "{:+10}"          , -0.0 ); // negative zero

    checkFormat( "       nan"           , "{:010}"          ,  double.NaN );
    checkFormat( "       inf"           , "{:010}"          ,  double.PositiveInfinity );
    checkFormat( "-      inf"           , "{:010}"          , double.NegativeInfinity );
    checkFormat( "00000000.0"           , "{:010}"          ,  0.0 );
    checkFormat( "-0000000.0"           , "{:010}"          , -0.0 ); // negative zero

    checkFormat( "nan       "           , "{:<10}"          ,  double.NaN );
    checkFormat( "inf       "           , "{:<10}"          ,  double.PositiveInfinity );
    checkFormat( "-inf      "           , "{:<10}"          ,  double.NegativeInfinity );
    checkFormat( "0.0       "           , "{:<10}"          ,  0.0 );
    checkFormat( "-0.0      "           , "{:<10}"          , -0.0 ); // negative zero
    checkFormat( "       nan"           , "{:>10}"          ,  double.NaN );
    checkFormat( "       inf"           , "{:>10}"          ,  double.PositiveInfinity );
    checkFormat( "      -inf"           , "{:>10}"          ,  double.NegativeInfinity );
    checkFormat( "       0.0"           , "{:>10}"          ,  0.0 );
    checkFormat( "      -0.0"           , "{:>10}"          , -0.0 ); // negative zero

    // -------------------------------- scientific -------------------------------------------

    checkFormat( "1.234568e+01"         , "{:e}"            ,  12.3456789   );
    checkFormat( "1.235e+01"            , "{:.3e}"          ,  12.3456789   );
    checkFormat( " 1.235e+01"           , "{:>10.3e}"       ,  12.3456789   );
    checkFormat( "01.235e+01"           , "{:>010.3e}"      ,  12.3456789   );
    checkFormat( "001.23e+01"           , "{:>010.2e}"      ,  12.3456789   );
    checkFormat( "-01.23e+01"           , "{:>010.2e}"      , -12.3456789   );
    checkFormat( "-1.235e+01"           , "{:>010.3e}"      , -12.3456789   );
    checkFormat( "-1.2346e+01"          , "{:>010.4e}"      , -12.3456789   );

    checkFormat( "1.234568E+01"         , "{:E}"            ,  12.3456789   );
    checkFormat( "1.235E+01"            , "{:.3E}"          ,  12.3456789   );
    checkFormat( " 1.235E+01"           , "{:>10.3E}"       ,  12.3456789   );
    checkFormat( "01.235E+01"           , "{:>010.3E}"      ,  12.3456789   );
    checkFormat( "001.23E+01"           , "{:>010.2E}"      ,  12.3456789   );
    checkFormat( "-01.23E+01"           , "{:>010.2E}"      , -12.3456789   );
    checkFormat( "-1.235E+01"           , "{:>010.3E}"      , -12.3456789   );
    checkFormat( "-1.2346E+01"          , "{:>010.4E}"      , -12.3456789   );


    //-------  Nan,Inf, -0.0 -------
    checkFormat( "NAN"                  , "{:E}"            ,  double.NaN );
    checkFormat( "INF"                  , "{:E}"            ,  double.PositiveInfinity );
    checkFormat( "-INF"                 , "{:E}"            ,  double.NegativeInfinity );
    checkFormat( "0.0E+00"              , "{:E}"            ,  0.0 );
    checkFormat( "-0.0E+00"             , "{:E}"            , -0.0 ); // negative zero
    checkFormat( "nan"                  , "{:+e}"           ,  double.NaN );
    checkFormat( "+inf"                 , "{:+e}"           ,  double.PositiveInfinity );
    checkFormat( "-inf"                 , "{:+e}"           ,  double.NegativeInfinity );
    checkFormat( "+0.0e+00"             , "{:+e}"           ,  0.0 );
    checkFormat( "-0.0e+00"             , "{:+e}"           , -0.0 ); // negative zero


    // -------------------------------- FixedPoint -------------------------------------------
    checkFormat( "12.345000"            , "{:f}"            ,  12.345         );
    checkFormat( "12.345679"            , "{:f}"            ,  12.3456789123  );
    checkFormat( "-12.345000"           , "{:f}"            , -12.345         );
    checkFormat( "-12.345679"           , "{:f}"            , -12.3456789123  );
    checkFormat( "12.345000"            , "{:F}"            ,  12.345         );
    checkFormat( "12.345679"            , "{:F}"            ,  12.3456789123  );
    checkFormat( "-12.345000"           , "{:F}"            , -12.345         );
    checkFormat( "-12.345679"           , "{:F}"            , -12.3456789123  );

    checkFormat( "12.345000"            , "{:#f}"            ,  12.345         );
    checkFormat( "12.345679"            , "{:#f}"            ,  12.3456789123  );
    checkFormat( "-12.345000"           , "{:#f}"            , -12.345         );
    checkFormat( "-12.345679"           , "{:#f}"            , -12.3456789123  );
    checkFormat( "12.345000"            , "{:#F}"            ,  12.345         );
    checkFormat( "12.345679"            , "{:#F}"            ,  12.3456789123  );
    checkFormat( "-12.345000"           , "{:#F}"            , -12.345         );
    checkFormat( "-12.345679"           , "{:#F}"            , -12.3456789123  );


    //-------  Nan,Inf, -0.0 -------
    checkFormat( "nan"                  , "{:f}"            ,  double.NaN );
    checkFormat( "inf"                  , "{:f}"            ,  double.PositiveInfinity );
    checkFormat( "-inf"                 , "{:f}"            ,  double.NegativeInfinity );
    checkFormat( "0.000000"             , "{:f}"            ,  0.0 );
    checkFormat( "-0.000000"            , "{:f}"            , -0.0 ); // negative zero
    checkFormat( "NAN"                  , "{:+F}"           ,  double.NaN );
    checkFormat( "+INF"                 , "{:+F}"           ,  double.PositiveInfinity );
    checkFormat( "-INF"                 , "{:+F}"           ,  double.NegativeInfinity );
    checkFormat( "+0.000000"            , "{:+F}"           ,  0.0 );
    checkFormat( "-0.000000"            , "{:+F}"           , -0.0 ); // negative zero

    checkFormat( "nan"                  , "{:#f}"            ,  double.NaN );
    checkFormat( "inf"                  , "{:#f}"            ,  double.PositiveInfinity );
    checkFormat( "-inf"                 , "{:#f}"            ,  double.NegativeInfinity );
    checkFormat( "0.000000"             , "{:#f}"            ,  0.0 );
    checkFormat( "-0.000000"            , "{:#f}"            , -0.0 ); // negative zero
    checkFormat( "NAN"                  , "{:#+F}"           ,  double.NaN );
    checkFormat( "+INF"                 , "{:#+F}"           ,  double.PositiveInfinity );
    checkFormat( "-INF"                 , "{:#+F}"           ,  double.NegativeInfinity );
    checkFormat( "+0.000000"            , "{:#+F}"           ,  0.0 );
    checkFormat( "-0.000000"            , "{:#+F}"           , -0.0 ); // negative zero


    checkFormat(             "   0.0"       , "{:06,.5}"            ,  0.0         );
    checkFormat(            "    0.0"       , "{:07,.5}"            ,  0.0         );
    checkFormat(           "    00.0"       , "{:08,.5}"            ,  0.0         );
    checkFormat(          "    000.0"       , "{:09,.5}"            ,  0.0         );
    checkFormat(         "     000.0"       , "{:010,.5}"           ,  0.0         );
    checkFormat(        "    0,000.0"       , "{:011,.5}"           ,  0.0         );
    checkFormat(       "    00,000.0"       , "{:012,.5}"           ,  0.0         );
    checkFormat(      "    000,000.0"       , "{:013,.5}"           ,  0.0         );
    checkFormat(     "     000,000.0"       , "{:014,.5}"           ,  0.0         );
    checkFormat(    "    0,000,000.0"       , "{:015,.5}"           ,  0.0         );
    checkFormat(   "    00,000,000.0"       , "{:016,.5}"           ,  0.0         );

    checkFormat(            "0.00000"       ,  "{:06#,.5}"            ,  0.0         );
    checkFormat(            "0.00000"       ,  "{:07#,.5}"            ,  0.0         );
    checkFormat(           "00.00000"       ,  "{:08#,.5}"            ,  0.0         );
    checkFormat(          "000.00000"       ,  "{:09#,.5}"            ,  0.0         );
    checkFormat(         " 000.00000"       , "{:010#,.5}"           ,  0.0         );
    checkFormat(        "0,000.00000"       , "{:011#,.5}"           ,  0.0         );
    checkFormat(       "00,000.00000"       , "{:012#,.5}"           ,  0.0         );
    checkFormat(      "000,000.00000"       , "{:013#,.5}"           ,  0.0         );
    checkFormat(     " 000,000.00000"       , "{:014#,.5}"           ,  0.0         );
    checkFormat(    "0,000,000.00000"       , "{:015#,.5}"           ,  0.0         );
    checkFormat(   "00,000,000.00000"       , "{:016#,.5}"           ,  0.0         );

    checkFormat(                "0.0"       , "{:,.5}"              ,          0.0 );
    checkFormat(                "1.0"       , "{:,.5}"              ,          1.0 );
    checkFormat(               "10.0"       , "{:,.5}"              ,         10.0 );
    checkFormat(              "100.0"       , "{:,.5}"              ,        100.0 );
    checkFormat(            "1,000.0"       , "{:,.5}"              ,       1000.0 );
    checkFormat(           "10,000.0"       , "{:,.5}"              ,      10000.0 );
    checkFormat(          "100,000.0"       , "{:,.5}"              ,     100000.0 );
    checkFormat(        "1,000,000.0"       , "{:,.5}"              ,    1000000.0 );
    checkFormat(       "10,000,000.0"       , "{:,.5}"              ,   10000000.0 );
    checkFormat(      "100,000,000.0"       , "{:,.5}"              ,  100000000.0 );

    checkFormat(            "0.00000"       ,  "{:#05,.5}"           ,  0.0         );
    checkFormat(            "0.00000"       ,  "{:#06,.5}"           ,  0.0         );
    checkFormat(            "0.00000"       ,  "{:#07,.5}"           ,  0.0         );
    checkFormat(           "00.00000"       ,  "{:#08,.5}"           ,  0.0         );
    checkFormat(          "000.00000"       ,  "{:#09,.5}"           ,  0.0         );
    checkFormat(         " 000.00000"       , "{:#010,.5}"           ,  0.0         );
    checkFormat(        "0,000.00000"       , "{:#011,.5}"           ,  0.0         );
    checkFormat(       "00,000.00000"       , "{:#012,.5}"           ,  0.0         );
    checkFormat(      "000,000.00000"       , "{:#013,.5}"           ,  0.0         );
    checkFormat(     " 000,000.00000"       , "{:#014,.5}"           ,  0.0         );
    checkFormat(    "0,000,000.00000"       , "{:#015,.5}"           ,  0.0         );
    checkFormat(   "00,000,000.00000"       , "{:#016,.5}"           ,  0.0         );

    checkFormat(          "1.00000"         , "{:#5,.5}"            ,  1.0         );
    checkFormat(          "1.00000"         , "{:#6,.5}"            ,  1.0         );
    checkFormat(          "1.00000"         , "{:#7,.5}"            ,  1.0         );
    checkFormat(         " 1.00000"         , "{:#8,.5}"            ,  1.0         );
    checkFormat(        "  1.00000"         , "{:#9,.5}"            ,  1.0         );
    checkFormat(       "   1.00000"         , "{:#10,.5}"           ,  1.0         );
    checkFormat(      "    1.00000"         , "{:#11,.5}"           ,  1.0         );
    checkFormat(     "     1.00000"         , "{:#12,.5}"           ,  1.0         );
    checkFormat(    "      1.00000"         , "{:#13,.5}"           ,  1.0         );
    checkFormat(   "       1.00000"         , "{:#14,.5}"           ,  1.0         );
    checkFormat(  "        1.00000"         , "{:#15,.5}"           ,  1.0         );
    checkFormat( "         1.00000"         , "{:#16,.5}"           ,  1.0         );

    checkFormat(          "1.00000"         , "{:#05,.5}"            ,  1.0         );
    checkFormat(          "1.00000"         , "{:#06,.5}"            ,  1.0         );
    checkFormat(          "1.00000"         , "{:#07,.5}"            ,  1.0         );
    checkFormat(         "01.00000"         , "{:#08,.5}"            ,  1.0         );
    checkFormat(        "001.00000"         , "{:#09,.5}"            ,  1.0         );
    checkFormat(       " 001.00000"         , "{:#010,.5}"           ,  1.0         );
    checkFormat(      "0,001.00000"         , "{:#011,.5}"           ,  1.0         );
    checkFormat(     "00,001.00000"         , "{:#012,.5}"           ,  1.0         );
    checkFormat(    "000,001.00000"         , "{:#013,.5}"           ,  1.0         );
    checkFormat(   " 000,001.00000"         , "{:#014,.5}"           ,  1.0         );
    checkFormat(  "0,000,001.00000"         , "{:#015,.5}"           ,  1.0         );
    checkFormat( "00,000,001.00000"         , "{:#016,.5}"           ,  1.0         );

    checkFormat(           "0.00000"        , "{:#,.5}"              ,          0.0 );
    checkFormat(           "1.00000"        , "{:#,.5}"              ,          1.0 );
    checkFormat(          "10.00000"        , "{:#,.5}"              ,         10.0 );
    checkFormat(         "100.00000"        , "{:#,.5}"              ,        100.0 );
    checkFormat(       "1,000.00000"        , "{:#,.5}"              ,       1000.0 );
    checkFormat(      "10,000.00000"        , "{:#,.5}"              ,      10000.0 );
    checkFormat(     "100,000.00000"        , "{:#,.5}"              ,     100000.0 );
    checkFormat(   "1,000,000.00000"        , "{:#,.5}"              ,    1000000.0 );
    checkFormat(  "10,000,000.00000"        , "{:#,.5}"              ,   10000000.0 );
    checkFormat( "100,000,000.00000"        , "{:#,.5}"              ,  100000000.0 );

    // percentage
    checkFormat(  "0.000000%"          , "{:%}"                ,          0.0       );
    checkFormat(  "0.000000%"          , "{:#%}"                ,          0.0       );

    checkFormat(     "0.00%"          , "{:.2%}"              ,          0.0       );
    checkFormat(     "0.00%"          , "{:#.2%}"             ,          0.0       );
    checkFormat(    "45.37%"          , "{:.2%}"              ,          0.4537    );
    checkFormat(     "45%"             , "{:.0%}"              ,          0.4537    );
    checkFormat(     "45.%"            , "{:#.0%}"             ,          0.4537    );




    UT_PRINT( "ALib Format Tests Python Style: Done" );

}


} // class
}//namespace
