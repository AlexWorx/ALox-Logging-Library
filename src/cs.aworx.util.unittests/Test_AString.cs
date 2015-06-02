// #################################################################################################
//  com.aworx.util.unittests - AWorx Util
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using System;
using System.Globalization;
using com.aworx.lox;
using com.aworx.lox.loggers;


#if AWORX_MONO_DEVELOP
    using NUnit.Framework;
#endif
#if AWORX_VSTUDIO
    using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using System.Text;
using com.aworx.util;

namespace com.aworx.util.unittests
{
    #if AWORX_MONO_DEVELOP
        [TestFixture ()]
    #endif
    #if AWORX_VSTUDIO
        [TestClass]
    #endif
    public class TestsAString
    {
        //---------------------------------------------------------------------------------------------------------
        //--- Test Constructors
        //---------------------------------------------------------------------------------------------------------

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void Constructors()
        {
            AString ms;
            ms= new AString();                        Assert.IsTrue (    ms.GetAllocation() ==  0  && ms.Length() == 0 );
            ms= new AString(25);                      Assert.IsTrue ( ms.GetAllocation() == 25  && ms.Length() == 0 );
            ms= new AString("Test");                  Assert.IsTrue ( ms.GetAllocation() >=  4  && ms.Length() == 4 );

            AString tMSEmpty= new AString ( );

            ms= new AString( (AString) null );        Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() == 0 );
            ms.Append( "was null" );                  Assert.IsTrue ( ms.Length() == 8 );
            ms= new AString( tMSEmpty );              Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() > 0 );
            ms= new AString( tMSEmpty, 1,     0 );    Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() > 0 );
            ms= new AString( tMSEmpty, -1000, 0 );    Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() > 0 );
            ms= new AString( tMSEmpty, -1000, 1 );    Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() > 0 );
            ms= new AString( tMSEmpty, -100,  1000);  Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() > 0 );

            AString tMS=        new AString ( "0123456789" );
            ms= new AString( tMS );                   Assert.IsTrue ( ms.GetAllocation() >=  10 && ms.Length() == 10 );    Assert.AreEqual( ms.ToString(), "0123456789");
            ms= new AString( tMS, 5);                 Assert.IsTrue ( ms.GetAllocation() >=   5 && ms.Length() ==  5 );    Assert.AreEqual( ms.ToString(), "56789");
            ms= new AString( tMS, 5, 100);            Assert.IsTrue ( ms.GetAllocation() >=   5 && ms.Length() ==  5 );    Assert.AreEqual( ms.ToString(), "56789");
            ms= new AString( tMS, -5);                Assert.IsTrue ( ms.GetAllocation() >=  10 && ms.Length() == 10 );    Assert.AreEqual( ms.ToString(), "0123456789");
            ms= new AString( tMS, -5,  3);            Assert.IsTrue ( ms.GetAllocation() >    0 && ms.Length() ==  0 );    Assert.AreEqual( ms.ToString(), "");
            ms= new AString( tMS, 50,  3);            Assert.IsTrue ( ms.GetAllocation() >    0 && ms.Length() ==  0 );    Assert.AreEqual( ms.ToString(), "");
            ms= new AString( tMS, 10,  3);            Assert.IsTrue ( ms.GetAllocation() >    0 && ms.Length() ==  0 );    Assert.AreEqual( ms.ToString(), "");
            ms= new AString( tMS, -5, 10);            Assert.IsTrue ( ms.GetAllocation() >=   5 && ms.Length() ==  5 );    Assert.AreEqual( ms.ToString(), "01234");
            ms= new AString( tMS, -5, 100);           Assert.IsTrue ( ms.GetAllocation() >=  10 && ms.Length() == 10 );    Assert.AreEqual( ms.ToString(), "0123456789");

            String tS= "0123456789";
            ms= new AString( (String) null );         Assert.IsTrue ( ms.Length() == 0 ); Assert.IsTrue ( ms.GetAllocation() == 0 );
            ms.Append( "was null" );                  Assert.IsTrue ( ms.Length() == 8 );
            ms= new AString( "" );                    Assert.IsTrue ( ms.Length() == 0 ); Assert.IsTrue ( ms.GetAllocation() >  0 );
            ms= new AString( "", 1,     0 );          Assert.IsTrue ( ms.Length() == 0 ); Assert.IsTrue ( ms.GetAllocation() >  0 );
            ms= new AString( "", -1000, 0 );          Assert.IsTrue ( ms.Length() == 0 ); Assert.IsTrue ( ms.GetAllocation() >  0 );
            ms= new AString( "", -1000, 1 );          Assert.IsTrue ( ms.Length() == 0 ); Assert.IsTrue ( ms.GetAllocation() > 0 );
            ms= new AString( "", -100,  1000);        Assert.IsTrue ( ms.Length() == 0 ); Assert.IsTrue ( ms.GetAllocation() >  0 );
            ms= new AString( tS );                    Assert.IsTrue ( ms.GetAllocation() >=  10 && ms.Length() == 10 );    Assert.AreEqual( ms.ToString(), "0123456789");
            ms= new AString( tS, 5);                  Assert.IsTrue ( ms.GetAllocation() >=   5 && ms.Length() ==  5 );    Assert.AreEqual( ms.ToString(), "56789");
            ms= new AString( tS, 5, 100);             Assert.IsTrue ( ms.GetAllocation() >=   5 && ms.Length() ==  5 );    Assert.AreEqual( ms.ToString(), "56789");
            ms= new AString( tS, -5);                 Assert.IsTrue ( ms.GetAllocation() >=  10 && ms.Length() == 10 );    Assert.AreEqual( ms.ToString(), "0123456789");
            ms= new AString( tS, -5, 10);             Assert.IsTrue ( ms.GetAllocation() >=   5 && ms.Length() ==  5 );    Assert.AreEqual( ms.ToString(), "01234");
            ms= new AString( tS, -5, 100);            Assert.IsTrue ( ms.GetAllocation() >=  10 && ms.Length() == 10 );    Assert.AreEqual( ms.ToString(), "0123456789");


            StringBuilder tSBEmpty= new StringBuilder ( );
            ms= new AString( (StringBuilder) null ); Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() == 0 );
            ms.Append( "was null" );                 Assert.IsTrue ( ms.Length() == 8 );
            ms= new AString( tSBEmpty );             Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() > 0 );
            ms= new AString( tSBEmpty, 1,     0 );   Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() > 0 );
            ms= new AString( tSBEmpty, -1000, 0 );   Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() > 0 );
            ms= new AString( tSBEmpty, -1000, 1 );   Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() > 0 );
            ms= new AString( tSBEmpty, -100,  1000); Assert.IsTrue ( ms.Length() == 0 );    Assert.IsTrue ( ms.GetAllocation() > 0 );

            StringBuilder tSB= new StringBuilder ( "0123456789" );
            ms= new AString( tSB );                  Assert.IsTrue  ( ms.GetAllocation() >=  10 && ms.Length() == 10 );
                                                     Assert.AreEqual( ms.ToString(), "0123456789");
            ms= new AString( tSB, 5);                Assert.IsTrue  ( ms.GetAllocation() >=  5  && ms.Length() == 5 );
                                                     Assert.AreEqual( ms.ToString(), "56789");
            ms= new AString( tSB, 5, 100);           Assert.IsTrue  ( ms.GetAllocation() >=  5  && ms.Length() == 5 );
                                                     Assert.AreEqual( ms.ToString(), "56789");
            ms= new AString( tSB, -5);               Assert.IsTrue  ( ms.GetAllocation() >=  10 && ms.Length() == 10 );
                                                     Assert.AreEqual( ms.ToString(), "0123456789");
            ms= new AString( tSB, -5, 10);           Assert.IsTrue  ( ms.GetAllocation() >=  5  && ms.Length() == 5 );
                                                     Assert.AreEqual( ms.ToString(), "01234");
            ms= new AString( tSB, -5, 100);          Assert.IsTrue  ( ms.GetAllocation() >=  10 && ms.Length() == 10 );
                                                     Assert.AreEqual( ms.ToString(), "0123456789");
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test DeleteInsert
        //---------------------------------------------------------------------------------------------------------
        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
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
                ms.Clear().Append("0123456789");        ms.Delete(  5            );    Assert.AreEqual    (  5,    ms.Length() );    Assert.AreEqual    ( "01234",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Delete(  5,      0    );    Assert.AreEqual    ( 10,    ms.Length() );    Assert.AreEqual    ( "0123456789",        ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Delete(  5,     -1    );    Assert.AreEqual    ( 10,    ms.Length() );    Assert.AreEqual    ( "0123456789",        ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Delete(  5,      1    );    Assert.AreEqual    (  9,    ms.Length() );    Assert.AreEqual    ( "012346789",        ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Delete(  5,    100    );    Assert.AreEqual    (  5,    ms.Length() );    Assert.AreEqual    ( "01234",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Delete(  -5,     10   );    Assert.AreEqual    (  5,    ms.Length() );    Assert.AreEqual    ( "56789",            ms.ToString() );
            }

            // insert
            {
                ms.Clear().Append("0123456789");        ms.Insert( -1,    1        );    Assert.AreEqual    ( 10,    ms.Length() );    Assert.AreEqual    ( "0123456789",        ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Insert( 20,    1        );    Assert.AreEqual    ( 10,    ms.Length() );    Assert.AreEqual    ( "0123456789",        ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Insert(  0,    0        );    Assert.AreEqual    ( 10,    ms.Length() );    Assert.AreEqual    ( "0123456789",        ms.ToString() );

                ms.Clear().Append("0123456789");        ms.Insert(  0,    1        );    Assert.AreEqual    ( 11,    ms.Length() );    Assert.AreEqual    ( " 0123456789",    ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Insert(  1,    1        );    Assert.AreEqual    ( 11,    ms.Length() );    Assert.AreEqual    ( "0 123456789",    ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Insert(  0,    2        );    Assert.AreEqual    ( 12,    ms.Length() );    Assert.AreEqual    ( "  0123456789",    ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Insert(  1,    2        );    Assert.AreEqual    ( 12,    ms.Length() );    Assert.AreEqual    ( "0  123456789",    ms.ToString() );

                ms.Clear().Append("0123456789");        ms.Insert(  11,    1       );    Assert.AreEqual    ( 10,    ms.Length() );    Assert.AreEqual    ( "0123456789",        ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Insert(  10,    1       );    Assert.AreEqual    ( 11,    ms.Length() );    Assert.AreEqual    ( "0123456789 ",    ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Insert(  5,    3, '@'   );    Assert.AreEqual    ( 13,    ms.Length() );    Assert.AreEqual    ( "01234@@@56789",    ms.ToString() );

                // test if tab reference pos is preserved
                ms.Clear().Append("ABC").NewLine().Append("123").Insert(  3, 3, '@'  ).Tab(5, 0, '$').Append('>');
                Assert.AreEqual    ( new AString("ABC@@@").NewLine().Append( "123$$>" ).ToString(),    ms.ToString() );

                ms.Clear().Append("ABC").NewLine().Append("123"); ms.Insert(  ms.Length()-2, 3, '@'  ).Tab(5, 0, '$').Append('>');
                Assert.AreEqual    ( new AString("ABC").NewLine().Append( "1@@@23$$$$>" ).ToString(),    ms.ToString() );

            }

            // set
            {
                ms.Clear().Append("0123456789");        ms.Fill( '@'             );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "@@@@@@@@@@",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@', -10        );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "@@@@@@@@@@",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@', -10, 100   );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "@@@@@@@@@@",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@', -10,  5    );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "0123456789",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@', -10, 10    );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "0123456789",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@', -10, 11    );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "@123456789",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@',   0,  1    );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "@123456789",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@',   0,  2    );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "@@23456789",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@',   1,  1    );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "0@23456789",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@',   1,  2    );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "0@@3456789",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@',   8,  1    );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "01234567@9",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@',   8,  2    );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "01234567@@",            ms.ToString() );
                ms.Clear().Append("0123456789");        ms.Fill( '@',   8,  3    );    Assert.AreEqual    (  10,    ms.Length() );    Assert.AreEqual    ( "01234567@@",            ms.ToString() );
            }

        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test Conversion
        //---------------------------------------------------------------------------------------------------------

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
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
            s= ms.ToString();                    Assert.IsTrue ( s.Equals("0123456789") );
            s= ms.ToString( 5 );                 Assert.IsTrue ( s.Equals("56789") );
            s= ms.ToString( 5,  100);            Assert.IsTrue ( s.Equals("56789") );
            s= ms.ToString( -5);                 Assert.IsTrue ( s.Equals("0123456789") );
            s= ms.ToString( -5,  10);            Assert.IsTrue ( s.Equals("01234") );
            s= ms.ToString( -5, 100);            Assert.IsTrue ( s.Equals("0123456789") );

            s= ms.ToString( 0,    0);            Assert.IsTrue ( s.Equals("") );
            s= ms.ToString( 5,    0);            Assert.IsTrue ( s.Equals("") );
            s= ms.ToString( 20,   0);            Assert.IsTrue ( s.Equals("") );
            s= ms.ToString( 0,   -1);            Assert.IsTrue ( s.Equals("") );
            s= ms.ToString( 5,   -5);            Assert.IsTrue ( s.Equals("") );
            s= ms.ToString( 5, -100);            Assert.IsTrue ( s.Equals("") );
            s= ms.ToString( 20,  -1);            Assert.IsTrue ( s.Equals("") );
            s= ms.ToString( 20,  20);            Assert.IsTrue ( s.Equals("") );
            s= ms.ToString( 20,-100);            Assert.IsTrue ( s.Equals("") );
            s= ms.ToString( 20,   0);            Assert.IsTrue ( s.Equals("") );
            s= ms.ToString( 20, 100);            Assert.IsTrue ( s.Equals("") );

            StringBuilder sb= new StringBuilder();
            ms.ToString( sb );                   Assert.IsTrue ( sb.ToString().Equals("0123456789") );
            ms.ToString( sb, true );             Assert.IsTrue ( sb.ToString().Equals("01234567890123456789") );
            ms.ToString( sb );                   Assert.IsTrue ( sb.ToString().Equals("0123456789") );
            ms.ToString( sb, 5, 100 );           Assert.IsTrue ( sb.ToString().Equals("56789") );
            ms.ToString( sb, -5, 10, true );     Assert.IsTrue ( sb.ToString().Equals("5678901234") );
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test Append
        //---------------------------------------------------------------------------------------------------------

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void Append()
        {
            // append strings
            {
                // create mutable string
                AString ms=    new AString(5);
                Assert.IsTrue( ms.Length() == 0 );

                // append constant string
                {
                    String  t=    "Hallo World";
                    ms=    new AString(5);
                    ms.Append(t);

                    Assert.IsTrue( ms.Length() == t.Length );
                    for ( int i= 0; i < t.Length ; i++ )
                        Assert.AreEqual( ms.Buffer()[i],  t[i]);
                }

                // append part of constant string
                {
                    String  t=            "Hallo World";
                    int        startIdx=    6;
                    int        len=        3;
                    ms=    new AString(5);
                    ms.Append( t, startIdx, len );

                    Assert.IsTrue( ms.Length() == len);
                    for ( int i= 0; i < len ; i++ )
                        Assert.AreEqual( ms.Buffer()[i],  t[ startIdx + i] );
                }

                // append more than available in source string
                {
                    String  t=            "Hallo World";
                    int        startIdx=    6;
                    int        len=        3;
                    ms=    new AString(5);
                    ms.Append(t);
                    ms.Append ( t, startIdx, t.Length );
                    len= t.Length - startIdx;

                    Assert.IsTrue( ms.Length() == t.Length + len );
                    for ( int i= 0; i < len ; i++ )
                        Assert.AreEqual( ms.Buffer()[t.Length + i],  t[ startIdx + i]);
                }

                // append int
                {
                    ms= new AString();
                    uint ui;
                    int  i;

                    ms.Clear(); ui=   0;    ms.Append( ui );     Assert.AreEqual(      "0", ms.ToString());
                    ms.Clear(); ui=   0;    ms.Append( ui, 1 );  Assert.AreEqual(      "0", ms.ToString());
                    ms.Clear(); ui=   0;    ms.Append( ui, 3 );  Assert.AreEqual(    "000", ms.ToString());
                    ms.Clear(); ui=  10;    ms.Append( ui );     Assert.AreEqual(     "10", ms.ToString());
                    ms.Clear(); ui= 100;    ms.Append( ui, 1 );  Assert.AreEqual(    "100", ms.ToString());
                    ms.Clear(); ui= 100;    ms.Append( ui, 3 );  Assert.AreEqual(    "100", ms.ToString());
                    ms.Clear(); ui= 100;    ms.Append( ui, 4 );  Assert.AreEqual(   "0100", ms.ToString());
                    ms.Clear(); ui=  23;    ms.Append( ui );     Assert.AreEqual(     "23", ms.ToString());
                    ms.Clear(); ui=  99;    ms.Append( ui, 5 );  Assert.AreEqual(  "00099", ms.ToString());
                    ms.Clear(); i=   49;    ms.Append( i  );     Assert.AreEqual(     "49", ms.ToString());
                    ms.Clear(); i=   -5;    ms.Append( i, 5 );   Assert.AreEqual( "-00005", ms.ToString());
                    ms.Clear(); i=-5324;    ms.Append( i, 2 );   Assert.AreEqual(  "-5324", ms.ToString());

                    i= int.MaxValue;
                    int iLen= ( "" + i ).Length;
                    ms= new AString( iLen -1 );     ms.Append( i );     Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.GetAllocation() >= iLen );
                    ms= new AString( iLen    );     ms.Append( i );     Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.GetAllocation() >= iLen );
                    ms= new AString( iLen +1 );     ms.Append( i );     Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.GetAllocation() == iLen + 1 );

                    i= int.MinValue;
                    iLen= ( "" + i ).Length;
                    ms= new AString( iLen -1 );     ms.Append( i );     Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.GetAllocation() >= iLen );
                    ms= new AString( iLen    );     ms.Append( i );     Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.GetAllocation() >= iLen );
                    ms= new AString( iLen +1 );     ms.Append( i );     Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.GetAllocation() == iLen + 1 );
                }

                // append double
                {
                    ms= new AString();
                    double d;

                    ms.Clear(); d= 0d;      ms.Append( d, 0,0 );     Assert.AreEqual(     "0.", ms.ToString());
                    ms.Clear(); d= 0d;      ms.Append( d, 1,1 );     Assert.AreEqual(    "0.0", ms.ToString());
                    ms.Clear(); d= 0d;      ms.Append( d, 2,2 );     Assert.AreEqual(  "00.00", ms.ToString());
                    ms.Clear(); d= 10d;     ms.Append( d, 2,2 );     Assert.AreEqual(  "10.00", ms.ToString());
                    ms.Clear(); d= 23.37d;  ms.Append( d, 2,1 );     Assert.AreEqual(   "23.4", ms.ToString());
                    ms.Clear(); d= 23.37d;  ms.Append( d, 2,3 );     Assert.AreEqual( "23.370", ms.ToString());
                    ms.Clear(); d= 12.345d; ms.Append( d, 0,3 );     Assert.AreEqual( "12.345", ms.ToString());
                    ms.Clear(); d= -5.1d;   ms.Append( d, 5,0 );     Assert.AreEqual("-00005.", ms.ToString());
                    ms.Clear(); d= -5.1d;   ms.Append( d, 5,1 );     Assert.AreEqual("-00005.1",ms.ToString());
                    ms.Clear(); d=-53.24d;  ms.Append( d, 2,2 );     Assert.AreEqual( "-53.24", ms.ToString());
                    ms.Clear(); d= -0.2d;   ms.Append( d, 1,3 );     Assert.AreEqual( "-0.200", ms.ToString());
                    ms.Clear(); d= -0.6d;   ms.Append( d, 1,3 );     Assert.AreEqual( "-0.600", ms.ToString());
                    ms.Clear(); d= -0.999d; ms.Append( d, 1,3 );     Assert.AreEqual( "-0.999", ms.ToString());
                    ms.Clear(); d=  0.999d; ms.Append( d, 1,3 );     Assert.AreEqual(  "0.999", ms.ToString());
                    ms.Clear(); d=  0.99;   ms.Append( d, 1,3 );     Assert.AreEqual(  "0.990", ms.ToString());
                    ms.Clear(); d=  0.999;  ms.Append( d, 1,3 );     Assert.AreEqual(  "0.999", ms.ToString());
                    ms.Clear(); d=  0.9999; ms.Append( d, 1,3 );     Assert.AreEqual(  "1.000", ms.ToString());
                    ms.Clear(); d=  0.99999;ms.Append( d, 1,3 );     Assert.AreEqual(  "1.000", ms.ToString());

                    d= -3.0d;
                    double end= 3.0d;
                    double inc= 0.001d;
                    int    digits= 5;
                    while ( d <= end)
                    {
                        ms.Clear();
                        ms.Append( d, 0, digits );
                        double dRes= Double.Parse( ms.ToString(), CultureInfo.InvariantCulture );
                        Assert.AreEqual( d, dRes, 0.00000001d );
                        d+= inc;
                    }
                }
            }

            // append mutable strings
            {
                // create mutable string
                AString ms=    new AString();
                Assert.IsTrue( ms.Length() == 0 );

                // append constant string
                AString t=    new AString();
                t.Append( "Hallo World" );
                ms.Append(t);

                Assert.IsTrue( ms.Length() == t.Length());
                for ( int i= 0; i < t.Length() ; i++ )
                    Assert.AreEqual( ms.Buffer()[i],  t.Buffer()[i]);

                // append part of constant string
                int startIdx= 6;
                int len=      3;
                ms.Append( t, startIdx, len );

                Assert.IsTrue( ms.Length() == t.Length() + len );
                for ( int i= 0; i < len ; i++ )
                    Assert.AreEqual( ms.Buffer()[t.Length() + i],  t.Buffer()[ startIdx + i]);

                // append more than available in source string
                ms=    new AString(5);
                ms.Append(t);
                ms.Append ( t, startIdx, t.Length() );
                len= t.Length() - startIdx;

                Assert.IsTrue( ms.Length() == t.Length() + len );
                for ( int i= 0; i < len ; i++ )
                    Assert.AreEqual( ms.Buffer()[t.Length() + i],  t.Buffer()[ startIdx + i] );
            }

            // append String Builders
            {
                // create mutable string
                AString ms=    new AString();
                Assert.IsTrue( ms.Length() == 0 );

                // append constant string
                StringBuilder t=    new StringBuilder();
                t.Append( "Hallo World" );
                ms.Append(t);

                Assert.IsTrue( ms.Length() == t.Length);
                for ( int i= 0; i < t.Length ; i++ )
                    Assert.AreEqual( ms.Buffer()[i],  t[i]);

                // append part of constant string
                int startIdx= 6;
                int len=      3;
                ms.Append( t, startIdx, len );

                Assert.IsTrue( ms.Length() == t.Length + len );
                for ( int i= 0; i < len ; i++ )
                    Assert.AreEqual( ms.Buffer()[t.Length + i],  t[ startIdx + i] );

                // append more than available in source string
                ms=    new AString(5);
                ms.Append(t);
                ms.Append ( t, startIdx, t.Length );
                len= t.Length - startIdx;

                Assert.IsTrue( ms.Length() == t.Length + len );
                for ( int i= 0; i < len ; i++ )
                    Assert.AreEqual( ms.Buffer()[t.Length + i],  t[ startIdx + i] );
            }

        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test Capacity
        //---------------------------------------------------------------------------------------------------------

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
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
                AString ms= new AString();              Assert.AreEqual( ms.GetAllocation(), 0 );
                        ms= new AString( 0 );           Assert.AreEqual( ms.GetAllocation(), 0 );
                        ms= new AString( nullString );  Assert.AreEqual( ms.GetAllocation(), 0 );
                ms.Append( "" );        Assert.IsTrue( ms.GetAllocation() > 0 );
            }

            {
                AString ms= new AString( 5 );
                ms.Append( 'a' );        Assert.IsTrue ( ms.GetAllocation() == 5 );
                ms.Append( 'b' );        Assert.IsTrue ( ms.GetAllocation() == 5 );
                ms.Append( 'c' );        Assert.IsTrue ( ms.GetAllocation() == 5 );
                ms.Append( 'd' );        Assert.IsTrue ( ms.GetAllocation() == 5 );
                ms.Append( 'e' );        Assert.IsTrue ( ms.GetAllocation() == 5 );
                ms.Append( 'x' );
                Assert.IsTrue ( ms.GetAllocation() >= 6 );
                Assert.AreEqual( "abcdex", ms.ToString() );

                ms.EnsureAllocation( 2000 ); Assert.IsTrue ( ms.GetAllocation() >= 2000 );
            }

            {
                AString   ms= new AString();
                int asize;
                ms.Append( "0123456789" );      Assert.AreEqual    ( ms.Length(), 10 );     Assert.IsTrue    ( ms.GetAllocation() >= 10 );

                asize= ms.GetAllocation();

                Console.WriteLine( "A warning should follow" );
                ms.SetLength(20);               Assert.AreEqual    ( ms.Length(), 10 );     Assert.AreEqual  ( ms.GetAllocation(), asize );    Assert.AreEqual( ms.ToString(), "0123456789" );

                Console.WriteLine( "No (second) warning should follow" );
                ms.SetLength(20);               Assert.AreEqual    ( ms.Length(), 10 );     Assert.AreEqual  ( ms.GetAllocation(), asize );    Assert.AreEqual( ms.ToString(), "0123456789" );

                AString.AWXU_OTW_SetLength=    true;

                Console.WriteLine( "No warning should follow" );
                ms.SetLength(10);               Assert.AreEqual    ( ms.Length(), 10 );     Assert.AreEqual  ( ms.GetAllocation(), asize );    Assert.AreEqual( ms.ToString(), "0123456789" );

                Console.WriteLine( "A warning should follow" );
                ms.SetLength(11);               Assert.AreEqual    ( ms.Length(), 10 );     Assert.AreEqual  ( ms.GetAllocation(), asize );    Assert.AreEqual( ms.ToString(), "0123456789" );

                Console.WriteLine( "No (second) warning should follow" );
                ms.SetLength(11);               Assert.AreEqual    ( ms.Length(), 10 );     Assert.AreEqual  ( ms.GetAllocation(), asize );    Assert.AreEqual( ms.ToString(), "0123456789" );

                ms.SetLength(5);                Assert.AreEqual    ( ms.Length(), 5 );      Assert.AreEqual  ( ms.GetAllocation(), asize );    Assert.AreEqual( ms.ToString(), "01234" );
                ms.SetAllocation(3);            Assert.AreEqual    ( ms.Length(), 3 );      Assert.AreEqual  ( ms.GetAllocation(), 3  );       Assert.AreEqual( ms.ToString(), "012" );
                ms.Append("ABC");               Assert.AreEqual    ( ms.Length(), 6 );      Assert.IsTrue    ( ms.GetAllocation() >= 6);       Assert.AreEqual( ms.ToString(), "012ABC" );
            }
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test AppendWithPadding
        //---------------------------------------------------------------------------------------------------------

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
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
            ms.Field().Field( 3, AString.Align.Left,     '#' );    Assert.AreEqual( ms.ToString(), "###"           );
            ms.Field().Field( 4, AString.Align.Center,   '*' );    Assert.AreEqual( ms.ToString(), "###****"       );
            ms.Field().Field( 5, AString.Align.Right,    '+' );    Assert.AreEqual( ms.ToString(), "###****+++++"  );

            // field, alignment left
            ms.Clear();
            ms.Field().Append( "A" )        .Field( 5,    AString.Align.Left );
            ms.Field().Append( "AB" )       .Field( 5,    AString.Align.Left );
            ms.Field().Append( "ABC" )      .Field( 5,    AString.Align.Left );
            ms.Field().Append( "ABCD" )     .Field( 5,    AString.Align.Left );
            ms.Field().Append( "ABCDE" )    .Field( 5,    AString.Align.Left );
            ms.Field().Append( "ABCDEF" )   .Field( 5,    AString.Align.Left );
            ms.Field().Append( "ABCDEFG" )  .Field( 5,    AString.Align.Left );
            Assert.AreEqual( ms.ToString(), "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG" );

            // field, alignment right
            ms.Clear();
            ms.Field().Append( "A" )        .Field( 5,    AString.Align.Right );
            ms.Field().Append( "AB" )       .Field( 5,    AString.Align.Right );
            ms.Field().Append( "ABC" )      .Field( 5 ); // btw: right is default
            ms.Field().Append( "ABCD" )     .Field( 5 );
            ms.Field().Append( "ABCDE" )    .Field( 5 );
            ms.Field().Append( "ABCDEF" )   .Field( 5,    AString.Align.Right );
            ms.Field().Append( "ABCDEFG" )  .Field( 5,    AString.Align.Right );
            Assert.AreEqual( ms.ToString(), "    A   AB  ABC ABCDABCDEABCDEFABCDEFG" );

            // field, alignment center
            ms.Clear();
            ms.Field().Append( "A" )        .Field( 5,    AString.Align.Center );
            ms.Field().Append( "AB" )       .Field( 5,    AString.Align.Center );
            ms.Field().Append( "ABC" )      .Field( 5,    AString.Align.Center );
            ms.Field().Append( "ABCD" )     .Field( 5,    AString.Align.Center );
            ms.Field().Append( "ABCDE" )    .Field( 5,    AString.Align.Center );
            ms.Field().Append( "ABCDEF" )   .Field( 5,    AString.Align.Center );
            ms.Field().Append( "ABCDEFG" )  .Field( 5,    AString.Align.Center );
            Assert.AreEqual( ms.ToString(), "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG" );

            // a nested field
            ms.Clear();
            ms.Append("***");
                int outerFieldStart= ms.Length();
                ms.Append( "OS:" )  .Field().Append( "Linux" ).Field( 10, AString.Align.Right, '-' );
                ms.Append( " Lang:").Field().Append( "en_US" ).Field(  8, AString.Align.Right, '-' );
                ms.Field(35, AString.Align.Center, '#', outerFieldStart );
            ms.Append("***");
            Assert.AreEqual( ms.ToString(), "***####OS:-----Linux Lang:---en_US####***" );
        }



        //---------------------------------------------------------------------------------------------------------
        //--- Test Tabs
        //---------------------------------------------------------------------------------------------------------

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void Tabs()
        {
            AString ms= new AString();

            // test some bad input
                           ms.Tab(  0,    -1,     '@' );            Assert.AreEqual( "", ms.ToString() );
            ms.Clear();    ms.Tab(  0,     0,     '@' );            Assert.AreEqual( "", ms.ToString() );
            ms.Clear();    ms.Tab( -1,     0,     '@' );            Assert.AreEqual( "", ms.ToString() );
            ms.Clear();    ms.Tab( -1,     0,     '@' );            Assert.AreEqual( "", ms.ToString() );
            ms.Clear();    ms.Tab( -1,    -1,     '@' );            Assert.AreEqual( "", ms.ToString() );
            ms.Clear();    ms.Tab( -5,     0,     '@' );            Assert.AreEqual( "", ms.ToString() );
            ms.Clear();    ms.Tab( -5,  -100,     '@' );            Assert.AreEqual( "", ms.ToString() );
            ms.Clear();    ms.Tab(  2,  -100,     '@' );            Assert.AreEqual( "", ms.ToString() );
            ms.Clear();    ms.Tab(  0,     0,     '@' );            Assert.AreEqual( "", ms.ToString() );
            ms.Clear();    ms.Tab(  1,     0,     '@' );            Assert.AreEqual( "",  ms.ToString() );
            ms.Clear();    ms.Tab(  1,     1,     '@' );            Assert.AreEqual( "@", ms.ToString() );
            ms.Clear();    ms.Tab(  0,     1,     '@' );            Assert.AreEqual( "@", ms.ToString() );


            // minpad 0 (not common, default is 1, tab wont move if on tab position)
            ms.Clear();                        ms.Tab( 2, 0,    '@' ).Append( '-' );        Assert.AreEqual( "-",   ms.ToString());
            ms.Clear();    ms.Append( 'x' );    ms.Tab( 2, 0,    '@' ).Append( '-' );        Assert.AreEqual( "x@-", ms.ToString());

            // more standard tabs
            ms.Clear();
            ms.Append( "12" ).Tab( 2 )
              .Append( "1"  ).Tab( 2 )
              .Tab(2)
              .Append( "@" );
            Assert.AreEqual( "12  1   @", ms.ToString() );

            ms.Clear();
            ms.Append( "12" ).Tab( 2, 0 )
              .Append( "1"  ).Tab( 2, 0 )
                             .Tab( 2, 0 )
              .Append( "@" );
            Assert.AreEqual( "121 @", ms.ToString() );


            ms.Clear();
            ms.Append( "12345" ).Tab( 5 )
              .Append( "1234" ) .Tab( 5 )
              .Append( "123" )  .Tab( 5 )
              .Append( "12" )   .Tab( 5 )
              .Append( "1" )    .Tab( 5 )
                                .Tab( 5 )
              .Append( "@" );
            Assert.AreEqual( "12345     1234 123  12   1         @", ms.ToString() );

            ms.Clear();
            ms.Append( "12345" ).Tab( 5, 0 )
              .Append( "1234" ) .Tab( 5, 0 )
              .Append( "123" )  .Tab( 5, 0 )
              .Append( "12" )   .Tab( 5, 0 )
              .Append( "1" )    .Tab( 5, 0 )
                                .Tab( 5, 0 )
              .Append( "@" );
            Assert.AreEqual( "123451234 123  12   1    @", ms.ToString() );

            ms.Clear();                         ms.Tab( 0 ).Append( '-' );        Assert.AreEqual( " -"        , ms.ToString() );
            ms.Clear();                         ms.Tab( 1 ).Append( '-' );        Assert.AreEqual( " -"        , ms.ToString() );
            ms.Clear();                         ms.Tab( 2 ).Append( '-' );        Assert.AreEqual( "  -"       , ms.ToString() );
            ms.Clear();                         ms.Tab( 3 ).Append( '-' );        Assert.AreEqual( "   -"      , ms.ToString() );
            ms.Clear();    ms.Append( 'x' );    ms.Tab( 1 ).Append( '-' );        Assert.AreEqual( "x -"       , ms.ToString() );
            ms.Clear();    ms.Append( 'x' );    ms.Tab( 2 ).Append( '-' );        Assert.AreEqual( "x -"       , ms.ToString() );
            ms.Clear();    ms.Append( 'x' );    ms.Tab( 3 ).Append( '-' );        Assert.AreEqual( "x  -"      , ms.ToString() );

            // tabs with tab reference set (designed for multi line tabs)
            ms.Clear().Append("ABC").NewLine();
            ms.Append( "12345" ).Tab( 5 )
              .Append( "1234" ) .Tab( 5 )
              .Append( "123" )  .Tab( 5 )
              .Append( "12" )   .Tab( 5 )
              .Append( "1" )    .Tab( 5 )
                                .Tab( 5 )
              .Append( "@" );
            Assert.AreEqual( "ABC" + Environment.NewLine + "12345     1234 123  12   1         @", ms.ToString() );

            ms.Clear().Append("ABC").NewLine();
            ms.Append( "12345" ).Tab( 5, 0 )
              .Append( "1234" ) .Tab( 5, 0 )
              .Append( "123" )  .Tab( 5, 0 )
              .Append( "12" )   .Tab( 5, 0 )
              .Append( "1" )    .Tab( 5, 0 )
                                .Tab( 5, 0 )
              .Append( "@" );
            Assert.AreEqual( "ABC" + Environment.NewLine + "123451234 123  12   1    @", ms.ToString() );
        }


        //---------------------------------------------------------------------------------------------------------
        //--- Test SearchAndReplace
        //---------------------------------------------------------------------------------------------------------

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void SearchAndReplace()
        {
            AString ms= new AString();
            int result;

            // search characters
            ms.Clear().Append("abcd abcd");
            {
                result= ms.IndexOf( '@', -5   );     Assert.AreEqual(    -1,   result );
                result= ms.IndexOf( '@'       );     Assert.AreEqual(    -1,   result );
                result= ms.IndexOf( '@', 5    );     Assert.AreEqual(    -1,   result );
                result= ms.IndexOf( '@', 150  );     Assert.AreEqual(    -1,   result );

                result= ms.IndexOf( 'a'       );     Assert.AreEqual(    0,   result );
                result= ms.IndexOf( 'b'       );     Assert.AreEqual(    1,   result );
                result= ms.IndexOf( 'c'       );     Assert.AreEqual(    2,   result );

                result= ms.IndexOf( 'a', 0    );     Assert.AreEqual(    0,   result );
                result= ms.IndexOf( 'b', 0    );     Assert.AreEqual(    1,   result );
                result= ms.IndexOf( 'c', 0    );     Assert.AreEqual(    2,   result );

                result= ms.IndexOf( 'a', 1    );     Assert.AreEqual(    5,   result );
                result= ms.IndexOf( 'b', 1    );     Assert.AreEqual(    1,   result );
                result= ms.IndexOf( 'c', 1    );     Assert.AreEqual(    2,   result );

                result= ms.IndexOf( 'a', 2    );     Assert.AreEqual(    5,   result );
                result= ms.IndexOf( 'b', 2    );     Assert.AreEqual(    6,   result );
                result= ms.IndexOf( 'c', 2    );     Assert.AreEqual(    2,   result );

                result= ms.IndexOf( 'a', 3    );     Assert.AreEqual(    5,   result );
                result= ms.IndexOf( 'b', 3    );     Assert.AreEqual(    6,   result );
                result= ms.IndexOf( 'c', 3    );     Assert.AreEqual(    7,   result );

                result= ms.IndexOf( 'd', 7    );     Assert.AreEqual(    8,   result );
                result= ms.IndexOf( 'd', 8    );     Assert.AreEqual(    8,   result );
                result= ms.IndexOf( 'd', 9    );     Assert.AreEqual(   -1,   result );
            }

            // search nullptr, empty string
            ms.Clear().Append("abcd abcd");
            {
                result= ms.IndexOf( (AString) null );           Assert.AreEqual( result, 0 );
                result= ms.IndexOf( (AString) null,   5  );     Assert.AreEqual( result, 5 );
                result= ms.IndexOf( (AString) null,  50  );     Assert.AreEqual( result,-1 );
                result= ms.IndexOf( (AString) null, - 5  );     Assert.AreEqual( result, 0 );

                result= ms.IndexOf( (String) null );            Assert.AreEqual( result, 0 );
                result= ms.IndexOf( (String) null,    5  );     Assert.AreEqual( result, 5 );
                result= ms.IndexOf( (String) null,   50  );     Assert.AreEqual( result,-1 );
                result= ms.IndexOf( (String) null, -  5  );     Assert.AreEqual( result, 0 );

                result= ms.IndexOf( "",            -  5  );     Assert.AreEqual( result, 0 );
                result= ms.IndexOf( "",               0  );     Assert.AreEqual( result, 0 );
                result= ms.IndexOf( "",               4  );     Assert.AreEqual( result, 4 );
                result= ms.IndexOf( "",             100  );     Assert.AreEqual( result,-1 );
            }

            // search
            ms.Clear().Append("abcd abcd");
            {
                result= ms.IndexOf( "abcd"     );            Assert.AreEqual( result, 0 );
                result= ms.IndexOf( "b"        );            Assert.AreEqual( result, 1 );
                result= ms.IndexOf( " abcd"    );            Assert.AreEqual( result, 4 );
                result= ms.IndexOf( "abcd",  1 );            Assert.AreEqual( result, 5 );
                result= ms.IndexOf( "abcd",- 1 );            Assert.AreEqual( result, 0 );
                result= ms.IndexOf( "xyz", -10 );            Assert.AreEqual( result, -1);
            }

            // ignore case
            ms.Clear().Append( "Hallo A-Worx util" );
            {
                result= ms.IndexOf( "a-worx",   0    ,true ); Assert.AreEqual( result, 6 );
                result= ms.IndexOf( "a-worx",   1    ,true ); Assert.AreEqual( result, 6 );
                result= ms.IndexOf( "a-worx", -10    ,true ); Assert.AreEqual( result, 6 );
                result= ms.IndexOf( "a-worx",   6    ,true ); Assert.AreEqual( result, 6 );
                result= ms.IndexOf( "a-worx",   7    ,true ); Assert.AreEqual( result, -1 );
                result= ms.IndexOf( "a-worx", 100    ,true ); Assert.AreEqual( result, -1 );
                result= ms.IndexOf( "hal",      0    ,true ); Assert.AreEqual( result,  0 );
                result= ms.IndexOf( "hal",      1    ,true ); Assert.AreEqual( result, -1 );
                result= ms.IndexOf( "util",     1    ,true ); Assert.AreEqual( result, 13 );
                result= ms.IndexOf( "UTIL",     5    ,true ); Assert.AreEqual( result, 13 );
                result= ms.IndexOf( "UTIL",    13    ,true ); Assert.AreEqual( result, 13 );
                result= ms.IndexOf( "UTIL",    14    ,true ); Assert.AreEqual( result, -1 );
            }

            // replace nullptr
            ms.Clear().Append("Hello");
            {
                ms.Replace( null,     null );        Assert.AreEqual( ms.ToString(), "Hello" );
                ms.Replace( "l",      null );        Assert.AreEqual( ms.ToString(), "Heo" );
                ms.Replace( null,     "xx" );        Assert.AreEqual( ms.ToString(), "Heo" );
            }

            // replaceCount nullptr
            ms.Clear().Append("Hello");
            {
                result= ms.ReplaceCount( (AString) null,        (AString) null );        Assert.AreEqual( ms.ToString(), "Hello" );      Assert.AreEqual( 0, result );
                result= ms.ReplaceCount( new AString("l"),      (AString) null );        Assert.AreEqual( ms.ToString(), "Heo" );        Assert.AreEqual( 2, result );
                result= ms.ReplaceCount( (AString) null,        new AString("xx") );     Assert.AreEqual( ms.ToString(), "Heo" );        Assert.AreEqual( 0, result );
            }

            ms.Clear().Append("Hello");
            {
                result= ms.ReplaceCount( (String) null,          (String) null );        Assert.AreEqual( ms.ToString(), "Hello" );      Assert.AreEqual( 0, result );
                result= ms.ReplaceCount( "l",                    (String) null );        Assert.AreEqual( ms.ToString(), "Heo" );        Assert.AreEqual( 2, result );
                result= ms.ReplaceCount( (String) null,          "xx"    );              Assert.AreEqual( ms.ToString(), "Heo" );        Assert.AreEqual( 0, result );
            }

            // replace
            ms.Clear().Append("Hello W!");
            {

                result= ms.ReplaceCount( "W!",    "world!"  );    Assert.AreEqual( ms.ToString(), "Hello world!" );          Assert.AreEqual( 1, result );
                result= ms.ReplaceCount( " ",    "* *"      );    Assert.AreEqual( ms.ToString(), "Hello* *world!" );        Assert.AreEqual( 1, result );
                result= ms.ReplaceCount( "*",    "#", 0, 1  );    Assert.AreEqual( ms.ToString(), "Hello# *world!" );        Assert.AreEqual( 1, result );
                result= ms.ReplaceCount( "*",    "#"        );    Assert.AreEqual( ms.ToString(), "Hello# #world!" );        Assert.AreEqual( 1, result );
                result= ms.ReplaceCount( "#",    "$$$"      );    Assert.AreEqual( ms.ToString(), "Hello$$$ $$$world!" );    Assert.AreEqual( 2, result );
                result= ms.ReplaceCount( "$$$",    "*"      );    Assert.AreEqual( ms.ToString(), "Hello* *world!" );        Assert.AreEqual( 2, result );
                result= ms.ReplaceCount( "*",    ""         );    Assert.AreEqual( ms.ToString(), "Hello world!" );          Assert.AreEqual( 2, result );
            }

            // replace one space by two spaces in a string of spaces
            ms.Clear().Append("     ");
            {
                result= ms.ReplaceCount( " ",    "  "  );    Assert.AreEqual( ms.ToString(), "          " );        Assert.AreEqual( 5, result );
            }

            // replace ignoreCase
            {
                ms.Clear().Append("ABC"); result= ms.ReplaceCount( "abc",    "xxx",0, 1, false );    Assert.AreEqual( ms.ToString(), "ABC" );        Assert.AreEqual( 0, result );
                ms.Clear().Append("ABC"); result= ms.ReplaceCount( "abc",    "xxx",0, 1, true  );    Assert.AreEqual( ms.ToString(), "xxx" );        Assert.AreEqual( 1, result );
                ms.Clear().Append("ABC"); result= ms.ReplaceCount( "ABC",    "xxx",0, 1, true  );    Assert.AreEqual( ms.ToString(), "xxx" );        Assert.AreEqual( 1, result );

                ms.Clear().Append("abc");         ms.ReplaceCount( "ABC",    "xxx",0, 1, false );    Assert.AreEqual( ms.ToString(), "abc" );
                ms.Clear().Append("abc");         ms.ReplaceCount( "ABC",    "xxx",0, 1, true  );    Assert.AreEqual( ms.ToString(), "xxx" );
                ms.Clear().Append("abc");         ms.ReplaceCount( "abc",    "xxx",0, 1, true  );    Assert.AreEqual( ms.ToString(), "xxx" );
            }

        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test Compare
        //---------------------------------------------------------------------------------------------------------

        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
            [TestMethod]
            #if !WINDOWS_PHONE
                [TestCategory("CS_AString")]
            #endif
        #endif
        public void Compare()
        {
            // null string comparison
            String  nullString= null;
            AString aString= new AString(0);
            Assert.IsTrue( aString.CompareTo( nullString) == 0 );
            Assert.IsTrue( aString.Equals( nullString) );

            aString.Append( "" );
            Assert.IsTrue( aString.CompareTo( nullString) != 0 );
            Assert.IsTrue( !aString.Equals( nullString) );

            aString.SetAllocation( 0 );
            Assert.IsTrue( aString.CompareTo( nullString) == 0 );
            Assert.IsTrue( aString.Equals( nullString) );


            AString ms= new AString();
            AString msNull=    null;
            String     sNull=    null;

            int result;

            String t= "abcde";
            ms.Append( t );
            result= ms.CompareTo( t      );                                      Assert.AreEqual( t.CompareTo( t ),                              result );
            result= ms.CompareTo( t + "x"      );                                Assert.AreEqual( t.CompareTo( t + "x" ),                        result );
            result= ms.CompareTo( t.Substring (0, t.Length -1 )  );              Assert.AreEqual( t.CompareTo( t.Substring (0, t.Length -1 ) ),  result );
            result= ms.CompareTo( "pad" + t,  false, 3      );                   Assert.AreEqual( 0,                                             result );
            result= ms.CompareTo( "pad" + t,  false, 3, 2   );                   Assert.AreEqual( 1,                                             result );
            result= ms.CompareTo( "pad" + t,  false, 3, 100, 0, 4 );             Assert.AreEqual( -1,                                            result );
            result= ms.CompareTo( "pad" + t,  false, 3, 100, 0, 5 );             Assert.AreEqual( 0,                                             result );
            result= ms.CompareTo( t,          false, 2,   2, 2, 2      );        Assert.AreEqual( 0,                                             result );
            result= ms.CompareTo( t,          false, 2,   2, 2, 1      );        Assert.AreEqual( -1,                                            result );
            result= ms.CompareTo( t,          false, 2,   2, 2, 3      );        Assert.AreEqual( 1,                                             result );

            result= ms.CompareTo( t,          false, -2,  5,-2, 5 );                             Assert.AreEqual( 0,  result );
            result= ms.CompareTo( t,          false,  2, int.MaxValue,    2, int.MaxValue );     Assert.AreEqual( 0,  result );
            result= ms.CompareTo( t,          false, -2, int.MaxValue,   -2, int.MaxValue );     Assert.AreEqual( 0,  result );
            result= ms.CompareTo( t,          false, -2, 100,            -2, 99 );               Assert.AreEqual( 0,  result );
            result= ms.CompareTo( t,          false, -2, 5,              -2, int.MaxValue );     Assert.AreEqual( 1,  result );
            result= ms.CompareTo( t,          false, -2, int.MaxValue,   -2, 5 );                Assert.AreEqual(-1,  result );

            // greater/smaller strings
            int scRes;
            String greater=     "x";
            String greater2= "abcdef";
            String smaller=  "aaa";
            String smaller2= "abcd";
            result= ms.CompareTo( greater  );            scRes=    t.CompareTo( greater  );    Assert.IsTrue( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );
            result= ms.CompareTo( greater2 );            scRes=    t.CompareTo( greater2 );    Assert.IsTrue( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );
            result= ms.CompareTo( smaller  );            scRes=    t.CompareTo( smaller  );    Assert.IsTrue( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );
            result= ms.CompareTo( smaller2 );            scRes=    t.CompareTo( smaller2 );    Assert.IsTrue( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );

            // ignore case
            String ut= t.ToUpperInvariant();
            result= ms.CompareTo( ut );                              Assert.IsTrue( result >  0 );
            result= ms.CompareTo( ut, false );                       Assert.IsTrue( result >  0 );
            result= ms.CompareTo( ut, true );                        Assert.IsTrue( result == 0 );
            result= ms.CompareTo( ut, false, 2,2,   2,2      );      Assert.IsTrue( result >  0 );
            result= ms.CompareTo( ut, true,  2,2,   2,2      );      Assert.IsTrue( result == 0 );

            // we do just a very little testing with StringBuilder and AString parameter version of this function, as
            // the code differences are very small
            StringBuilder tSB= new StringBuilder(); tSB.Append( t );
            result= ms.CompareTo( tSB      );                            Assert.AreEqual( 0,  result );
            result= ms.CompareTo( tSB, false, -5, 100, -10, 100      );  Assert.AreEqual( 0,  result );
            result= ms.CompareTo( tSB, false,  2,   3,   2,   3      );  Assert.AreEqual( 0,  result );

            AString tMS= new AString(); tMS.Append( t );
            result= ms.CompareTo( tMS      );                            Assert.AreEqual( 0,  result );
            result= ms.CompareTo( tMS, false, -5, 100, -10, 100      );  Assert.AreEqual( 0,  result );
            result= ms.CompareTo( tMS, false,  2,   3,   2,   3      );  Assert.AreEqual( 0,  result );

            // different ranges
            String r1=   "*ABCDEF*";
            String r2= "##*ABCDEF*##";
            ms.Clear().Append( r1 );
            result= ms.CompareTo( r2, false, 2,8          );             Assert.AreEqual( 0,  result );
            result= ms.CompareTo( r2, false, 3,6,   1,6   );             Assert.AreEqual( 0,  result );

            // startsWith/Endswith/ContainsAt
            String sub1=  "ABC";
            String sub2=  "abc";
            String s1= "ABCDEF";
            String s2= "123ABC";
            String s3= "##12ABC21##";
            String s4= "AB";
            bool bRes;
            ms.Clear().Append( s1 );    bRes= ms.StartsWith( sub1 );              Assert.AreEqual( true,        bRes );
                                        bRes= ms.StartsWith( sub2 );              Assert.AreEqual( false,       bRes );
            ms.Clear().Append( s2 );    bRes= ms.EndsWith  ( sub1 );              Assert.AreEqual( true,        bRes );
                                        bRes= ms.EndsWith  ( sub2 );              Assert.AreEqual( false,       bRes );
            ms.Clear().Append( s3 );    bRes= ms.ContainsAt( sub1, 4 );           Assert.AreEqual( true,        bRes );
                                        bRes= ms.ContainsAt( sub2, 4 );           Assert.AreEqual( false,       bRes );
                                        bRes= ms.ContainsAt( sub2, 4, true );     Assert.AreEqual( true,        bRes );
            ms.Clear().Append( s4 );    bRes= ms.ContainsAt( sub1, 4 );           Assert.AreEqual( false,       bRes );
                                        bRes= ms.ContainsAt( sub2, 4 );           Assert.AreEqual( false,       bRes );
            ms.Clear().Append( s4 );    bRes= ms.ContainsAt( sub1, 0 );           Assert.AreEqual( false,       bRes );
                                        bRes= ms.ContainsAt( sub2, 0, true );     Assert.AreEqual( false,       bRes );

            ms.Clear().Append( "Hallo A-Worx util" );

                                Assert.IsTrue( ms.StartsWith( "Hallo A-Worx util", true ) == true );
                                Assert.IsTrue( ms.EndsWith  ( "Hallo A-Worx util", true  ) == true  );
                                Assert.IsTrue( ms.StartsWith( "Hallo A-Worx utilx", true ) == false );
                                Assert.IsTrue( ms.EndsWith  ( "xHallo A-Worx util", true  ) == false );
                                Assert.IsTrue( ms.StartsWith( "haLLO", true ) == true  );
                                Assert.IsTrue( ms.StartsWith( "HaLLO", true ) == true  );
                                Assert.IsTrue( ms.EndsWith  ( "haLLO", true ) == false );
                                Assert.IsTrue( ms.StartsWith( "UTIL" , true ) == false );
                                Assert.IsTrue( ms.EndsWith  ( "UTIL" , true ) == true  );
                                Assert.IsTrue( ms.EndsWith  ( "utIl" , true ) == true  );


            // contains with empty/null strings
            ms.Clear().Append( "AB" );  bRes= ms.ContainsAt( msNull, -1 );      Assert.AreEqual( false,    bRes );
                                        bRes= ms.ContainsAt( msNull, 0 );       Assert.AreEqual( true,     bRes );
                                        bRes= ms.ContainsAt( msNull, 1 );       Assert.AreEqual( true,     bRes );
                                        bRes= ms.ContainsAt( msNull, 2 );       Assert.AreEqual( true,     bRes );
                                        bRes= ms.ContainsAt( msNull, 3 );       Assert.AreEqual( false,    bRes );

                                        bRes= ms.ContainsAt( sNull, -1 );       Assert.AreEqual( false,    bRes );
                                        bRes= ms.ContainsAt( sNull, 0 );        Assert.AreEqual( true,     bRes );
                                        bRes= ms.ContainsAt( sNull, 1 );        Assert.AreEqual( true,     bRes );
                                        bRes= ms.ContainsAt( sNull, 2 );        Assert.AreEqual( true,     bRes );
                                        bRes= ms.ContainsAt( sNull, 3 );        Assert.AreEqual( false,    bRes );

            ms.Clear();                 bRes= ms.ContainsAt( msNull, -1 );      Assert.AreEqual( false,    bRes );
                                        bRes= ms.ContainsAt( msNull, 0 );       Assert.AreEqual( true,     bRes );
                                        bRes= ms.ContainsAt( msNull, 1 );       Assert.AreEqual( false,    bRes );

                                        bRes= ms.ContainsAt( sNull, -1 );       Assert.AreEqual( false,    bRes );
                                        bRes= ms.ContainsAt( sNull, 0 );        Assert.AreEqual( true,     bRes );
                                        bRes= ms.ContainsAt( sNull, 1 );        Assert.AreEqual( false,    bRes );

            ms.Clear().Append(sub1);    bRes= ms.ContainsAt( "", -1 );          Assert.AreEqual( false,    bRes );
                                        bRes= ms.ContainsAt( "", 0 );           Assert.AreEqual( true,     bRes );
                                        bRes= ms.ContainsAt( "", 1 );           Assert.AreEqual( true,     bRes );
                                        bRes= ms.ContainsAt( "", 100 );         Assert.AreEqual( false,    bRes );

            // equals String
            ms.Clear().Append( "" );    bRes= ms.Equals( null );                Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( ""   );                Assert.AreEqual( true,     bRes );
                                        bRes= ms.Equals( "a"  );                Assert.AreEqual( false,    bRes );

            ms.Clear().Append( "AB" );    bRes= ms.Equals( null );              Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( ""   );                Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( "ab" );                Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( "A"  );                Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( "B"  );                Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( "AB" );                Assert.AreEqual( true,     bRes );
                                        bRes= ms.Equals( "AB" );                Assert.AreEqual( true,     bRes );

            // equals AString
            ms.Clear().Append( "" );    bRes= ms.Equals( (AString) null   );    Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( new AString(""  ));    Assert.AreEqual( true,     bRes );
                                        bRes= ms.Equals( new AString("a" ));    Assert.AreEqual( false,    bRes );

            ms.Clear().Append( "AB" );    bRes= ms.Equals( (AString) null   );  Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( new AString(""  ));    Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( new AString("ab"));    Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( new AString("A" ));    Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( new AString("B" ));    Assert.AreEqual( false,    bRes );
                                        bRes= ms.Equals( new AString("AB"));    Assert.AreEqual( true,     bRes );
                                        bRes= ms.Equals( new AString("AB"));    Assert.AreEqual( true,     bRes );
        }

        //---------------------------------------------------------------------------------------------------------
        //--- Test ConvertCase
        //---------------------------------------------------------------------------------------------------------
        #if AWORX_MONO_DEVELOP
            [Test ()]
        #endif
        #if AWORX_VSTUDIO
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

            ms.Clear().Append( t ).ConvertCase( false );            Assert.IsTrue( tLower.Equals( ms.ToString() ) );
            ms.Clear().Append( t ).ConvertCase( true  );            Assert.IsTrue( tUpper.Equals( ms.ToString() ) );

            // test substring conversion
            t= "AAAbbb";
            ms.Clear().Append( t ).ConvertCase( false,  0, 2 );        Assert.IsTrue( ms.ToString().Equals( "aaAbbb" ) );
            ms.Clear().Append( t ).ConvertCase( false, -2, 3 );        Assert.IsTrue( ms.ToString().Equals( "aAAbbb" ) );
            ms.Clear().Append( t ).ConvertCase( false, -2    );        Assert.IsTrue( ms.ToString().Equals( "aaabbb" ) );

            ms.Clear().Append( t ).ConvertCase( true,  3,  2 );        Assert.IsTrue( ms.ToString().Equals( "AAABBb" ) );
            ms.Clear().Append( t ).ConvertCase( true, -2,  6 );        Assert.IsTrue( ms.ToString().Equals( "AAABbb" ) );
            ms.Clear().Append( t ).ConvertCase( true, -2     );        Assert.IsTrue( ms.ToString().Equals( "AAABBB" ) );
        }
    }
}
