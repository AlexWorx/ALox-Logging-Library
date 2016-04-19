// #################################################################################################
//  aworx - Unit Tests
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
#include "alib/stdafx_alib.h"

#if !defined (HPP_ALIB_STRINGS)
    #include "alib/strings/tokenizer.hpp"
#endif
#if !defined (HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif

#undef min
#undef max


#define TESTCLASSNAME       CPP_ALib_Strings_AS
#include "aworx_unittests.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>


using namespace std;
using namespace aworx;

namespace ut_aworx {

UT_CLASS()



//---------------------------------------------------------------------------------------------------------
//--- Test ConvertIntegers
//---------------------------------------------------------------------------------------------------------
UT_METHOD( ConvertIntegers )
{
    UT_INIT();

    AString as;
    int pos;
    int posOrig;

    // parse on empty
    as.Clear();
    {
        UT_EQ(   0,  as.ToInt()   );

        posOrig= pos= 0;    UT_EQ(   0,  as.ToInt( pos, &pos )  );     UT_EQ( pos, posOrig );
        posOrig= pos= -5;   UT_EQ(   0,  as.ToInt( pos, &pos )  );     UT_EQ( pos, posOrig );
    }

    // parse on non number
    as.Clear()._( "Hello");
    {
        UT_EQ(   0,  as.ToInt()   );

        posOrig= pos= 0;    UT_EQ(   0,  as.ToInt( pos, &pos )  );     UT_EQ( pos, posOrig );
        posOrig= pos= -5;   UT_EQ(   0,  as.ToInt( pos, &pos )  );     UT_EQ( pos, posOrig );
        posOrig= pos= 2;    UT_EQ(   0,  as.ToInt( pos, &pos )  );     UT_EQ( pos, posOrig );
    }

    // check that leading whitespaces do not move pointer
    as.Clear()._( "   Hello");
    {
        UT_EQ(   0,  as.ToInt()   );

        posOrig= pos= 0;    UT_EQ(   0,  as.ToInt( pos, &pos )  );     UT_EQ( pos, posOrig );
        posOrig= pos= -5;   UT_EQ(   0,  as.ToInt( pos, &pos )  );     UT_EQ( pos, posOrig );
        posOrig= pos= 2;    UT_EQ(   0,  as.ToInt( pos, &pos )  );     UT_EQ( pos, posOrig );
    }

    // parse integers
    {
        as.Clear()._( "123456789");      UT_EQ( 123456789,  as.ToInt  ( 0, &pos ) );        UT_EQ(  0  + as.Length() , pos );
        as.Clear()._( "  123");          UT_EQ( 123,        as.ToInt  ( 0, &pos ) );        UT_EQ(  0  + as.Length() , pos );
        as.Clear()._( "  -23  ");        UT_EQ( -23,        as.ToInt  ( 0, &pos ) );        UT_EQ( -2  + as.Length() , pos );
        as.Clear()._(   "123  ");        UT_EQ( 123,        as.ToInt  ( 0, &pos ) );        UT_EQ( -2  + as.Length() , pos );

        as.Clear()._( "xxx123456789");   UT_EQ( 123456789,  as.ToInt  ( 3, &pos ) );        UT_EQ(  0  + as.Length() , pos );
        as.Clear()._( "xxx  123");       UT_EQ( 123,        as.ToInt  ( 3, &pos ) );        UT_EQ(  0  + as.Length() , pos );
        as.Clear()._( "xxx  123  ");     UT_EQ( 123,        as.ToInt  ( 3, &pos ) );        UT_EQ( -2  + as.Length() , pos );
        as.Clear()._(   "xxx123  ");     UT_EQ( 123,        as.ToInt  ( 3, &pos ) );        UT_EQ( -2  + as.Length() , pos );
    }

    // int32
    {
        AString ms;

        uint32_t ui;
        int32_t   i;

        ms.Clear(); ui= 0;       ms._( ui    );                     UT_EQ(      "0", ms );
        ms.Clear(); ui= 0;       ms._( Format::UInt32( ui, 1 ) );   UT_EQ(      "0", ms );
        ms.Clear(); ui= 0;       ms._( Format::UInt32( ui, 3 ) );   UT_EQ(    "000", ms );
        ms.Clear(); ui= 10;      ms._( ui    );                     UT_EQ(     "10", ms );
        ms.Clear(); ui= 100;     ms._( Format::UInt32( ui, 1 ) );   UT_EQ(    "100", ms );
        ms.Clear(); ui= 100;     ms._( Format::UInt32( ui, 3 ) );   UT_EQ(    "100", ms );
        ms.Clear(); ui= 100;     ms._( Format::UInt32( ui, 4 ) );   UT_EQ(   "0100", ms );
        ms.Clear(); ui= 23;      ms._( ui    );                     UT_EQ(     "23", ms );
        ms.Clear(); ui= 99;      ms._( Format::UInt32( ui, 5 ) );   UT_EQ(  "00099", ms );
        ms.Clear();  i= 49;      ms._( i     );                     UT_EQ(     "49", ms );
        ms.Clear();  i= -5;      ms._( Format::Int32 ( i, 5  ) );   UT_EQ( "-00005", ms );
        ms.Clear();  i= -5324;   ms._( Format::Int32 ( i, 2  ) );   UT_EQ(  "-5324", ms );
        ms.Clear(); ui= std::numeric_limits<uint32_t>::max();    ms._(                 ui       );   UT_EQ(    "4294967295",  ms );
        ms.Clear(); ui= std::numeric_limits<uint32_t>::min();    ms._(                 ui       );   UT_EQ(             "0",  ms );
        ms.Clear();  i= std::numeric_limits<int32_t> ::max();    ms._(                 i        );   UT_EQ(    "2147483647",  ms );
        ms.Clear();  i= std::numeric_limits<int32_t> ::min();    ms._(                 i        );   UT_EQ(   "-2147483648",  ms );
        ms.Clear(); ui= std::numeric_limits<uint32_t>::max();    ms._( Format::UInt32( ui, 12 ) );   UT_EQ(  "004294967295",  ms );
        ms.Clear(); ui= std::numeric_limits<uint32_t>::min();    ms._( Format::UInt32( ui, 12 ) );   UT_EQ(  "000000000000",  ms );
        ms.Clear();  i= std::numeric_limits<int32_t> ::max();    ms._( Format::Int32 ( i , 12 ) );   UT_EQ(  "002147483647",  ms );
        ms.Clear();  i= std::numeric_limits<int32_t> ::min();    ms._( Format::Int32 ( i , 12 ) );   UT_EQ( "-002147483648",  ms );
    }

    // int64
    {
        AString ms;

        uint64_t ui;
        int64_t   i;

        ms.Clear(); ui= 0;       ms._( ui );                      UT_EQ(      "0", ms );
        ms.Clear(); ui= 0;       ms._( Format::UInt64( ui, 1) );  UT_EQ(      "0", ms );
        ms.Clear(); ui= 0;       ms._( Format::UInt64( ui, 3) );  UT_EQ(    "000", ms );
        ms.Clear(); ui= 10;      ms._( ui );                      UT_EQ(     "10", ms );
        ms.Clear(); ui= 100;     ms._( Format::UInt64( ui, 1 ));  UT_EQ(    "100", ms );
        ms.Clear(); ui= 100;     ms._( Format::UInt64( ui, 3 ));  UT_EQ(    "100", ms );
        ms.Clear(); ui= 100;     ms._( Format::UInt64( ui, 4 ));  UT_EQ(   "0100", ms );
        ms.Clear(); ui= 23;      ms._( ui );                      UT_EQ(     "23", ms );
        ms.Clear(); ui= 99;      ms._( Format::UInt64( ui, 5 ));  UT_EQ(  "00099", ms );
        ms.Clear();  i= 49;      ms._(                 i      );  UT_EQ(     "49", ms );
        ms.Clear();  i= -5;      ms._( Format::Int64 ( i, 5  ));  UT_EQ( "-00005", ms );
        ms.Clear();  i= -5324;   ms._( Format::Int64 ( i, 2  ));  UT_EQ(  "-5324", ms );
        ms.Clear(); ui= std::numeric_limits<uint32_t>::max();    ms._(                ui       );   UT_EQ(    "4294967295",  ms );
        ms.Clear(); ui= std::numeric_limits<uint32_t>::min();    ms._(                ui       );   UT_EQ(             "0",  ms );
        ms.Clear();  i= std::numeric_limits<int32_t> ::max();    ms._(                i        );   UT_EQ(    "2147483647",  ms );
        ms.Clear();  i= std::numeric_limits<int32_t> ::min();    ms._(                i        );   UT_EQ(   "-2147483648",  ms );
        ms.Clear(); ui= std::numeric_limits<uint32_t>::max();    ms._( Format::UInt64(ui, 12 ) );   UT_EQ(  "004294967295",  ms );
        ms.Clear(); ui= std::numeric_limits<uint32_t>::min();    ms._( Format::UInt64(ui, 12 ) );   UT_EQ(  "000000000000",  ms );
        ms.Clear();  i= std::numeric_limits<int32_t> ::max();    ms._( Format::Int64 (i , 12 ) );   UT_EQ(  "002147483647",  ms );
        ms.Clear();  i= std::numeric_limits<int32_t> ::min();    ms._( Format::Int64 (i , 12 ) );   UT_EQ( "-002147483648",  ms );

        ms.Clear(); ui= std::numeric_limits<uint64_t>::max();    ms._( ui     );   UT_EQ( "18446744073709551615",  ms );
        ms.Clear(); ui= std::numeric_limits<uint64_t>::min();    ms._( ui     );   UT_EQ(                    "0",  ms );
        ms.Clear();  i= std::numeric_limits<int64_t> ::max();    ms._( i      );   UT_EQ(  "9223372036854775807",  ms );
        ms.Clear(); ms.SetBuffer(20);  i= std::numeric_limits<int64_t> ::min();    ms._( i      );   UT_EQ( "-9223372036854775808",  ms );
        ms.Clear();  i= std::numeric_limits<int64_t> ::min() + 75008; ms._( i );   UT_EQ( "-9223372036854700800",  ms );
    }
}

//---------------------------------------------------------------------------------------------------------
//--- Test ConvertFloats
//---------------------------------------------------------------------------------------------------------
void floatTest( ALIBUnitTesting& ut, double d, char decimalPoint, int minDigitsBeforeDot, int digitsAfterDot, const char* expectedString, bool forceScientifc= false )
{
    String64 ms;
    NumberFormat nf;
    nf.ForceScientificFormat= forceScientifc;
    nf.MinIntegralDigits= minDigitsBeforeDot;
    nf.FractionalDigits=  digitsAfterDot;

    if ( decimalPoint == '\0' )
    {
        // reset number format to reflect current locale
        NumberFormat::Global.SetFromLocale();
        nf.DecimalPointCharacter=   NumberFormat::Global.DecimalPointCharacter;
    }
    else
        nf.DecimalPointCharacter=  decimalPoint;

    ms._( Format::Double(d, &nf) );
    if ( expectedString != nullptr )
    {
        UT_EQ(  expectedString, ms );
    }

    double precision= digitsAfterDot < 0 ?  pow ( 10, (d != 0.0 ? (int) floor((log10( d ) )) : 0 )   - 14 )
                                         :  pow ( 10, digitsAfterDot ) / 2.0;

    // check with system parsing (only if system specific decimal point format was given)
    if ( decimalPoint == '\0' )
    {
        double dSystem= ::atof( ms.ToCString() );
        UT_NEAR( d, dSystem, precision );
    }

    // check with aworx parsing
    double dALib= ms.ToFloat();
    UT_NEAR( d, dALib, precision );
}


UT_METHOD( ConvertFloats )
{
    UT_INIT();

    AString as;
    int pos;
    int posOrig;

    // parse on empty
    as.Clear();
    {
                                UT_EQ( 0.0,        as.ToFloat  (           )  );
        posOrig= pos= 0;        UT_EQ( 0.0,        as.ToFloat  ( pos, &pos )  );     UT_EQ( pos, posOrig );
        posOrig= pos= -5;       UT_EQ( 0.0,        as.ToFloat  ( pos, &pos )  );     UT_EQ( pos, posOrig );
    }

    // parse on non number
    as.Clear()._( "Hello");
    {
                            UT_EQ( 0.0,        as.ToFloat  (           )  );
        posOrig= pos= 0;    UT_EQ( 0.0,        as.ToFloat  ( pos, &pos )  );     UT_EQ( pos, posOrig );
        posOrig= pos= -5;   UT_EQ( 0.0,        as.ToFloat  ( pos, &pos )  );     UT_EQ( pos, posOrig );
        posOrig= pos= 2;    UT_EQ( 0.0,        as.ToFloat  ( pos, &pos )  );     UT_EQ( pos, posOrig );
    }

    // check that leading whitespaces do not move pointer
    as.Clear()._( "   Hello");
    {
                            UT_EQ( 0.0,        as.ToFloat  ()             );
        posOrig= pos= 0;    UT_EQ( 0.0,        as.ToFloat  ( pos, &pos )  );     UT_EQ( pos, posOrig );
        posOrig= pos= -5;   UT_EQ( 0.0,        as.ToFloat  ( pos, &pos )  );     UT_EQ( pos, posOrig );
        posOrig= pos= 2;    UT_EQ( 0.0,        as.ToFloat  ( pos, &pos )  );     UT_EQ( pos, posOrig );
    }

    // write and parse doubles
    {
        NumberFormat nf;
        nf.DecimalPointCharacters= ".";      as.Clear()._( "12345.789");      UT_EQ( 12345.789,  as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  0  + as.Length() , pos );
        nf.DecimalPointCharacters= ".,";     as.Clear()._( "12345.789");      UT_EQ( 12345.789,  as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  0  + as.Length() , pos );
        nf.DecimalPointCharacters= ".,";     as.Clear()._( "12345.789");      UT_EQ( 12345.789,  as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  0  + as.Length() , pos );
        nf.DecimalPointCharacters= "abc@.,"; as.Clear()._( "12345.789");      UT_EQ( 12345.789,  as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  0  + as.Length() , pos );
        nf.DecimalPointCharacters= "abc@.,"; as.Clear()._( "12345@789");      UT_EQ( 12345.789,  as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  0  + as.Length() , pos );
        nf.DecimalPointCharacters= "abc.,";  as.Clear()._( "12345@789");      UT_EQ( 12345.0  ,  as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  5                , pos );

        nf.DecimalPointCharacters= ".";
        as.Clear()._( "");               UT_EQ(   0.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  0                , pos );
        as.Clear()._(  '-');              UT_EQ(   0.,            as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  0                , pos );
        as.Clear()._( "-X");             UT_EQ(   0.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  0                , pos );
        as.Clear()._(  '.');              UT_EQ(   0.,            as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  1                , pos );
        as.Clear()._( ".0");             UT_EQ(   0.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  2                , pos );
        as.Clear()._( "0.");             UT_EQ(   0.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  2                , pos );
        as.Clear()._( "+.");             UT_EQ(   0.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  2                , pos );
        as.Clear()._( "-.");             UT_EQ(   0.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  2                , pos );
        as.Clear()._( "-.0");            UT_EQ(   0.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  3                , pos );
        as.Clear()._( "-.08");           UT_EQ(  -0.08,           as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  4                , pos );
        as.Clear()._( "  123");          UT_EQ( 123.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  0  + as.Length() , pos );
        as.Clear()._( "+42");            UT_EQ(  42.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  3                , pos );
        as.Clear()._( "  +42  ");        UT_EQ(  42.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ( -2  + as.Length() , pos );
        as.Clear()._( "  +42.  ");       UT_EQ(  42.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ( -2  + as.Length() , pos );
        as.Clear()._( "-23");            UT_EQ( -23.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ(  3                , pos );
        as.Clear()._( "  -23  ");        UT_EQ( -23.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ( -2  + as.Length() , pos );
        as.Clear()._(   "123  ");        UT_EQ( 123.,             as.ToFloat( 0, &pos, &nf ) );   UT_EQ( -2  + as.Length() , pos );

        as.Clear()._( "xxx123456789");   UT_EQ( 123456789.,       as.ToFloat( 3, &pos, &nf ) );   UT_EQ(  0  + as.Length() , pos );
        as.Clear()._( "xxx  1.3");       UT_EQ( 1.3,              as.ToFloat( 3, &pos, &nf ) );   UT_EQ(  0  + as.Length() , pos );
        as.Clear()._( "xxx  1.3  ");     UT_EQ( 1.3,              as.ToFloat( 3, &pos, &nf ) );   UT_EQ( -2  + as.Length() , pos );
        as.Clear()._(   "xxx1.3  ");     UT_EQ( 1.3,              as.ToFloat( 3, &pos, &nf ) );   UT_EQ( -2  + as.Length() , pos );
    }

    // write and parse doubles, non scientific mode
    {
        // digits after dot: -1
        floatTest( ut,     3.0              ,'.' , -1, -1 ,      "3.0"                  );
        floatTest( ut,     3.1              ,'.' , -1, -1 ,      "3.1"                  );
        floatTest( ut,     3.14             ,'.' , -1, -1 ,      "3.14"                 );
        floatTest( ut,     3.145            ,'.' , -1, -1 ,      "3.145"                );
        floatTest( ut,     3.02             ,'.' , -1, -1 ,      "3.02"                 );
        floatTest( ut,     3.001            ,'.' , -1, -1 ,      "3.001"                );
        floatTest( ut,     3.09             ,'.' , -1, -1 ,      "3.09"                 );
        floatTest( ut,     3.009            ,'.' , -1, -1 ,      "3.009"                );

        floatTest( ut,     0.               ,'.' , -1, -1 ,      "0.0"                  );
        floatTest( ut,     0.1              ,'.' , -1, -1 ,      "0.1"                  );
        floatTest( ut,     0.14             ,'.' , -1, -1 ,      "0.14"                 );
        floatTest( ut,     0.145            ,'.' , -1, -1 ,      "0.145"                );
        floatTest( ut,     0.02             ,'.' , -1, -1 ,      "0.02"                 );
        floatTest( ut,     0.001            ,'.' , -1, -1 ,      "0.001"                );
        floatTest( ut,     0.09             ,'.' , -1, -1 ,      "0.09"                 );
        floatTest( ut,     0.009            ,'.' , -1, -1 ,      "0.009"                );

        // forces scientific notation
        floatTest( ut,     3.               ,'.' , -1, -1 ,      "3.0E00"              , true );
        floatTest( ut,     3.1              ,'.' , -1, -1 ,      "3.1E00"              , true );
        floatTest( ut,     3.14             ,'.' , -1, -1 ,      "3.14E00"             , true );
        floatTest( ut,     3.145            ,'.' , -1, -1 ,      "3.145E00"            , true );
        floatTest( ut,     3.02             ,'.' , -1, -1 ,      "3.02E00"             , true );
        floatTest( ut,     3.001            ,'.' , -1, -1 ,      "3.001E00"            , true );
        floatTest( ut,     3.09             ,'.' , -1, -1 ,      "3.09E00"             , true );
        floatTest( ut,     3.009            ,'.' , -1, -1 ,      "3.009E00"            , true );

        floatTest( ut,     3.145            ,'.' , -1,  1 ,      "3.1E00"              , true  );
        floatTest( ut,     3.145            ,'.' ,  1,  1 ,      "3.1E00"              , true  );
        floatTest( ut,     3.145            ,'.' ,  5,  3 ,  "00003.145E00"            , true  );
        floatTest( ut,     123.12341234     ,'.' , -1,  6 ,      "1.231234E02"         , true  );
        floatTest( ut,       0.00123123123  ,'.' , -1,  6 ,      "1.231231E-03"        , true  );
        floatTest( ut,       0.321          ,'.' ,  0,  6 ,      "3.210000E-01"        , true  );
        floatTest( ut,     3.789            ,'.' , -1,  1 ,      "3.8E00"              , true  );
        floatTest( ut,     123.78978978     ,'.' , -1,  6 ,      "1.237898E02"         , true  );
        floatTest( ut,       0.00789789789  ,'.' , -1,  6 ,      "7.897898E-03"        , true  );



        // many digits after dot
        //                  123456789 123456789 12345
        double RoundDown= 1.123412341234123412341234;
        floatTest( ut,  RoundDown  ,'.' ,  1,  12 ,   "1.123412341234"       );
        floatTest( ut,  RoundDown  ,'.' ,  1,  13 ,   "1.1234123412341"      );
        floatTest( ut,  RoundDown  ,'.' ,  1,  14 ,   "1.12341234123412"     );
        floatTest( ut,  RoundDown  ,'.' ,  1,  15 ,   "1.123412341234123"    );

               RoundDown= 0.123412341234123412341234;
        floatTest( ut,  RoundDown  ,'.' ,  1,  12 ,   "0.123412341234"       );
        floatTest( ut,  RoundDown  ,'.' ,  1,  13 ,   "0.1234123412341"      );
        floatTest( ut,  RoundDown  ,'.' ,  1,  14 ,   "0.12341234123412"     );
        floatTest( ut,  RoundDown  ,'.' ,  1,  15 ,   "0.123412341234123"    );

        double RoundUp=   1.678967896789678967896789;
        floatTest( ut,  RoundUp    ,'.' ,  1,  12 ,   "1.678967896790"       );
        floatTest( ut,  RoundUp    ,'.' ,  1,  13 ,   "1.6789678967897"      );
        floatTest( ut,  RoundUp    ,'.' ,  1,  14 ,   "1.67896789678968"     );
        floatTest( ut,  RoundUp    ,'.' ,  1,  15 ,   "1.678967896789679"    );

               RoundUp=   0.678967896789678967896789;
        floatTest( ut,  RoundUp    ,'.' ,  1,  12 ,   "0.678967896790"       );
        floatTest( ut,  RoundUp    ,'.' ,  1,  13 ,   "0.6789678967897"      );
        floatTest( ut,  RoundUp    ,'.' ,  1,  14 ,   "0.67896789678968"     );
        floatTest( ut,  RoundUp    ,'.' ,  1,  15 ,   "0.678967896789679"    );

        //            123456789 123456789                           123456789 12345
        floatTest( ut,  0.00001234123412341234    ,'.' ,  1,  15 ,   "0.000012341234123"    );
        floatTest( ut,  0.00000123412341234123    ,'.' ,  1,  15 ,   "0.000001234123412"    );
        floatTest( ut,  0.00000012341234123412    ,'.' ,  1,  15 ,   "0.000000123412341"    );
        floatTest( ut,  0.00000001234123412341    ,'.' ,  1,  15 ,   "0.000000012341234"    );
        floatTest( ut,  0.00000000123412341234    ,'.' ,  1,  15 ,   "0.000000001234123"    );
        floatTest( ut,  0.00000000012341234123    ,'.' ,  1,  15 ,   "0.000000000123412"    );
        floatTest( ut,  0.00000000001234123412    ,'.' ,  1,  15 ,   "0.000000000012341"    );
        floatTest( ut,  0.00000000000123412341    ,'.' ,  1,  15 ,   "0.000000000001234"    );
        floatTest( ut,  0.00000000000012341234    ,'.' ,  1,  15 ,   "0.000000000000123"    );
        floatTest( ut,  0.00000000000001234123    ,'.' ,  1,  15 ,   "0.000000000000012"    );
        floatTest( ut,  0.00000000000000123412    ,'.' ,  1,  15 ,   "0.000000000000001"    );
        floatTest( ut,  0.00000000000000012341    ,'.' ,  1,  15 ,   "0.000000000000000"    );
        floatTest( ut,  0.00000000000000001234    ,'.' ,  1,  15 ,   "0.000000000000000"    );

        floatTest( ut,  0.00006789678967896789    ,'.' ,  1,  15 ,   "0.000067896789679"    );
        floatTest( ut,  0.00000678967896789678    ,'.' ,  1,  15 ,   "0.000006789678968"    );
        floatTest( ut,  0.00000067896789678967    ,'.' ,  1,  15 ,   "0.000000678967897"    );
        floatTest( ut,  0.00000006789678967896    ,'.' ,  1,  15 ,   "0.000000067896790"    );
        floatTest( ut,  0.00000000678967896789    ,'.' ,  1,  15 ,   "0.000000006789679"    );
        floatTest( ut,  0.00000000067896789678    ,'.' ,  1,  15 ,   "0.000000000678968"    );
        floatTest( ut,  0.00000000006789678967    ,'.' ,  1,  15 ,   "0.000000000067897"    );
        floatTest( ut,  0.00000000000678967896    ,'.' ,  1,  15 ,   "0.000000000006790"    );
        floatTest( ut,  0.00000000000067896789    ,'.' ,  1,  15 ,   "0.000000000000679"    );
        floatTest( ut,  0.00000000000006789678    ,'.' ,  1,  15 ,   "0.000000000000068"    );
        floatTest( ut,  0.00000000000000678967    ,'.' ,  1,  15 ,   "0.000000000000007"    );
        floatTest( ut,  0.00000000000000067896    ,'.' ,  1,  15 ,   "0.000000000000001"    );
        floatTest( ut,  0.00000000000000006789    ,'.' ,  1,  15 ,   "0.000000000000000"    );
        floatTest( ut,  0.00000000000000000678    ,'.' ,  1,  15 ,   "0.000000000000000"    );

        // digits after dot: 0 or positive
        floatTest( ut,  300.00050000001     ,'.' ,  1,  2 ,   "300.00"               );
        floatTest( ut,  300.00050000001     ,'.' ,  1,  3 ,   "300.001"              );
        floatTest( ut,  300.00050000001     ,'.' ,  1,  4 ,   "300.0005"             );
        floatTest( ut,  300.00050000001     ,'.' ,  1,  5 ,   "300.00050"            );
        floatTest( ut,  300.00050000001     ,'.' ,  1,  6 ,   "300.000500"           );
        floatTest( ut,    5.01              ,'.' ,  1,  3 ,      "5.010"             );


        floatTest( ut,     0.5              ,'.' ,  0,  0 ,       "."                );
        floatTest( ut,     0.5              ,'.' ,  0,  1 ,       ".5"               );
        floatTest( ut,     0.5              ,'.' ,  1,  0 ,      "0."                );
        floatTest( ut,     0.5              ,'.' ,  1,  1 ,      "0.5"               );
        floatTest( ut,     0.5              ,'.' ,  2,  2 ,     "00.50"              );
        floatTest( ut,     0.5              ,'.' ,  3,  3 ,    "000.500"             );
        floatTest( ut,     0.54             ,'.' ,  3,  3 ,    "000.540"             );
        floatTest( ut,     0.543            ,'.' ,  3,  3 ,    "000.543"             );
        floatTest( ut,     0.5432           ,'.' ,  3,  3 ,    "000.543"             );


        floatTest( ut,    23.37             ,'.' ,  2,  1 ,     "23.4"               );
        floatTest( ut,     1.5              ,'.' ,  0,  0 ,      "1."                );
        floatTest( ut,     1.9              ,'.' ,  0,  0 ,      "2."                );
        floatTest( ut,     1.9              ,'.' ,  0,  4 ,      "1.9000"            );
        floatTest( ut,     1.500001         ,'.' ,  0,  0 ,      "2."                );
        floatTest( ut,     1.54             ,'.' ,  3,  3 ,    "001.540"             );
        floatTest( ut,     1.543            ,'.' ,  3,  3 ,    "001.543"             );
        floatTest( ut,     1.5432           ,'.' ,  3,  3 ,    "001.543"             );
        floatTest( ut,    23.37             ,'.' ,  2,  3 ,     "23.370"             );
        floatTest( ut,    12.345            ,'.' ,  0,  3 ,     "12.345"             );
        floatTest( ut,    12.345            ,'.' ,  5,  1 ,  "00012.3"               );
        floatTest( ut,    12.36789          ,'.' ,  5,  1 ,  "00012.4"               );
        floatTest( ut,     1.5              ,'.' ,  0,  0 ,      "1."                );
        floatTest( ut,     1.5              ,'.' ,  1,  0 ,      "1."                );
        floatTest( ut,     1.5              ,'.' ,  0,  1 ,      "1.5"               );
        floatTest( ut,     1.5              ,'.' ,  1,  1 ,      "1.5"               );
        floatTest( ut,     1.5              ,'.' ,  2,  2 ,     "01.50"              );
        floatTest( ut,     1.5              ,'.' ,  3,  3 ,    "001.500"             );
        floatTest( ut,     1.54             ,'.' ,  3,  3 ,    "001.540"             );
        floatTest( ut,     1.543            ,'.' ,  3,  3 ,    "001.543"             );
        floatTest( ut,     1.5432           ,'.' ,  3,  3 ,    "001.543"             );


        floatTest( ut,     0.0              ,'.' ,  0,  0 ,       "."                );
        floatTest( ut,     0.0              ,'.' ,  1,  0 ,      "0."                );
        floatTest( ut,     0.0              ,'.' ,  0,  1 ,       ".0"               );
        floatTest( ut,     0.0              ,'.' ,  1,  1 ,      "0.0"               );
        floatTest( ut,     0.0              ,'.' ,  2,  2 ,     "00.00"              );
        floatTest( ut,    10.0              ,'.' ,  2,  2 ,     "10.00"              );
        floatTest( ut,    23.37             ,'.' ,  2,  1 ,     "23.4"               );
        floatTest( ut,    23.37             ,'.' ,  2,  3 ,     "23.370"             );
        floatTest( ut,    12.345            ,'.' ,  0,  3 ,     "12.345"             );
        floatTest( ut, -   5.1              ,'.' ,  5,  0 , "-00005."                );
        floatTest( ut, -   5.1              ,'.' ,  5,  1 , "-00005.1"               );
        floatTest( ut, -  53.24             ,'.' ,  2,  2 ,    "-53.24"              );
        floatTest( ut, -   0.2              ,'.' ,  1,  3 ,     "-0.200"             );
        floatTest( ut, -   0.6              ,'.' ,  1,  3 ,     "-0.600"             );
        floatTest( ut, -   0.999            ,'.' ,  1,  3 ,     "-0.999"             );

        floatTest( ut,     0.999            ,'.' ,  1,  3 ,      "0.999"             );
        floatTest( ut,     0.99             ,'.' ,  1,  3 ,      "0.990"             );
        floatTest( ut,     0.999            ,'.' ,  1,  3 ,      "0.999"             );
        floatTest( ut,     0.9999           ,'.' ,  1,  3 ,      "1.000"             );
        floatTest( ut,     0.0999           ,'.' ,  2,  3 ,     "00.100"             );
        floatTest( ut,     0.99999          ,'.' ,  1,  3 ,      "1.000"             );
        floatTest( ut,     0.099            ,'.' ,  2,  3 ,     "00.099"             );
        floatTest( ut,     0.0999           ,'.' ,  1,  3 ,      "0.100"             );
        floatTest( ut,     0.09999          ,'.' ,  2,  3 ,     "00.100"             );
        floatTest( ut,     0.999            ,'.' ,  2,  3 ,     "00.999"             );

        floatTest( ut,     0.0099           ,'.' ,  1,  3 ,      "0.010"             );
        floatTest( ut,     0.00999          ,'.' ,  1,  3 ,      "0.010"             );
        floatTest( ut,     0.009            ,'.' ,  1,  3 ,      "0.009"             );
        floatTest( ut,     0.00099          ,'.' ,  1,  3 ,      "0.001"             );
        floatTest( ut,     0.00009          ,'.' ,  1,  3 ,      "0.000"             );

        floatTest( ut,     1.0099           ,'.' ,  1,  3 ,      "1.010"             );
        floatTest( ut,     1.00999          ,'.' ,  1,  3 ,      "1.010"             );
        floatTest( ut,     1.009            ,'.' ,  1,  3 ,      "1.009"             );
        floatTest( ut,     1.00099          ,'.' ,  1,  3 ,      "1.001"             );
        floatTest( ut,     1.00009          ,'.' ,  1,  3 ,      "1.000"             );

        floatTest( ut,     0.00050          ,'.' ,  1,  3 ,      "0.000"             );
        floatTest( ut,     0.00051          ,'.' ,  1,  3 ,      "0.001"             );
        floatTest( ut,     0.00050000001    ,'.' ,  1,  3 ,      "0.001"             );
        floatTest( ut,  300.00050000001     ,'.' ,  1,  3 ,    "300.001"             );

        floatTest( ut,     0.10099          ,'.' ,  1,  4 ,     "0.1010"             );
        floatTest( ut,     0.10099          ,'.' ,  1,  4 ,     "0.1010"             );
        floatTest( ut,     0.00099          ,'.' ,  1,  4 ,     "0.0010"             );
        floatTest( ut,     1.099            ,'.' ,  1,  1 ,     "1.1"                );
        floatTest( ut,     0.00999          ,'.' ,  1,  4 ,     "0.0100"             );



        // roundtrip -3.0 to 3.0 step 0.001
        {
            for (int digits= -1 ; digits < 5 ; digits++ )
            {
                double d= -3.0;
                double end= 3.0;
                double inc= 0.001;
                while ( d <= end )
                {
                    floatTest( ut, d, '\0' , -1, digits, nullptr );
                    d+= inc;
                }
            }
        }

        // roundtrip e-200 to e+200
        {
            for ( int exp= -200 ; exp <= 200 ; exp+=1 )
            {
                double expFactor= pow( 10, exp );

                for ( int t= 0 ; t <= 1000 ; t++)
                {
                    // create a random number of type r.rrrrr *10^exp
                    //double d= drand48() * expFactor;
                    double d= ( double( rand() ) / RAND_MAX ) * expFactor;
                    if ( t & 1 )
                        d= -d;

                    floatTest( ut, d, '\0' , -1, -1, nullptr );
                }
            }
        }

        // special exponent symbol
        {
            NumberFormat nf;
            nf.DecimalExponentSeparator= "*10^";
            String64 s;
            double v= 7.5E42;
            s._( Format::Double(v, &nf) );
            UT_EQ( s, "7.5*10^42" );
            double back= s.ToFloat( 0, nullptr, &nf );
            UT_NEAR( v, back, 0.0000000001 );
        }

        // single floats
        {
            float f= 3.14f;
            as.Clear()._(f);
            double d= as.ToFloat();
            UT_EQ( d, f );
        }
    }
}


UT_CLASS_END

} //namespace
