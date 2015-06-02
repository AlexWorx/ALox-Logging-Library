// #################################################################################################
//  Unit Tests - aworx::util
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package unittests.com.aworx.util;

import static org.junit.Assert.*;

import org.junit.Test;

import com.aworx.util.AString;


public class Test_AString
{
    //---------------------------------------------------------------------------------------------------------
    //--- Test Constructors
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void Constructors()
    {
        AString ms= new AString();
        ms= new AString();                            assertTrue ( ms.getAllocation() ==   0 && ms.length() == 0 );
        ms= new AString(25);                          assertTrue ( ms.getAllocation() ==  25 && ms.length() == 0 );
        ms= new AString("Test");                      assertTrue ( ms.getAllocation() >=   4 && ms.length() == 4 );

        AString tMSEmpty= new AString ( );
        ms= new AString( (AString) null );            assertTrue ( ms.length() == 0 );    assertTrue ( ms.getAllocation() == 0 );
        ms.append( "was null" );                      assertTrue ( ms.length() == 8 );
        ms= new AString( tMSEmpty );                  assertTrue ( ms.length() == 0 );    assertTrue ( ms.getAllocation() > 0 );
        ms= new AString( tMSEmpty, 1,     0 );        assertTrue ( ms.length() == 0 );    assertTrue ( ms.getAllocation() > 0 );
        ms= new AString( tMSEmpty, -1000, 0 );        assertTrue ( ms.length() == 0 );    assertTrue ( ms.getAllocation() > 0 );
        ms= new AString( tMSEmpty, -1000, 1 );        assertTrue ( ms.length() == 0 );    assertTrue ( ms.getAllocation() > 0 );
        ms= new AString( tMSEmpty, -100,  1000);      assertTrue ( ms.length() == 0 );    assertTrue ( ms.getAllocation() > 0 );

        AString tMS=        new AString ( "0123456789" );
        ms= new AString( tMS );                       assertTrue ( ms.getAllocation() >=  10 && ms.length()  == 10 );        assertEquals( ms.toString(), "0123456789");
        ms= new AString( tMS, 5);                     assertTrue ( ms.getAllocation() >=   5 && ms.length()  ==  5 );        assertEquals( ms.toString(), "56789");
        ms= new AString( tMS, 5, 100);                assertTrue ( ms.getAllocation() >=   5 && ms.length()  ==  5 );        assertEquals( ms.toString(), "56789");
        ms= new AString( tMS, -5);                    assertTrue ( ms.getAllocation() >=  10 && ms.length()  == 10 );        assertEquals( ms.toString(), "0123456789");
        ms= new AString( tMS, -5,   3);               assertTrue ( ms.getAllocation() >    0 && ms.length()  ==  0 );        assertEquals( ms.toString(), "");
        ms= new AString( tMS, 50,   3);               assertTrue ( ms.getAllocation() >    0 && ms.length()  ==  0 );        assertEquals( ms.toString(), "");
        ms= new AString( tMS, 10,   3);               assertTrue ( ms.getAllocation() >    0 && ms.length()  ==  0 );        assertEquals( ms.toString(), "");
        ms= new AString( tMS, -5,  10);               assertTrue ( ms.getAllocation() >=   5 && ms.length()  ==  5 );        assertEquals( ms.toString(), "01234");
        ms= new AString( tMS, -5, 100);               assertTrue ( ms.getAllocation() >=  10 && ms.length()  == 10 );        assertEquals( ms.toString(), "0123456789");

        String tS= "0123456789";
        ms= new AString( (String) null );             assertTrue ( ms.length() == 0 );
        ms= new AString( "" );                        assertTrue ( ms.length() == 0 );
        ms= new AString( "",     1,    0 );           assertTrue ( ms.length() == 0 );
        ms= new AString( "", -1000,    0 );           assertTrue ( ms.length() == 0 );
        ms= new AString( "", -1000,    1 );           assertTrue ( ms.length() == 0 );
        ms= new AString( "",  -100, 1000 );           assertTrue ( ms.length() == 0 );
        ms= new AString( tS );                        assertTrue ( ms.buffer().length >=  10 && ms.length()  == 10 );        assertEquals( ms.toString(), "0123456789");
        ms= new AString( tS, 5);                      assertTrue ( ms.buffer().length >=   5 && ms.length()  ==  5 );        assertEquals( ms.toString(), "56789");
        ms= new AString( tS, 5, 100);                 assertTrue ( ms.buffer().length >=   5 && ms.length()  ==  5 );        assertEquals( ms.toString(), "56789");
        ms= new AString( tS, -5);                     assertTrue ( ms.buffer().length >=  10 && ms.length()  == 10 );        assertEquals( ms.toString(), "0123456789");
        ms= new AString( tS, -5, 10);                 assertTrue ( ms.buffer().length >=   5 && ms.length()  ==  5 );        assertEquals( ms.toString(), "01234");
        ms= new AString( tS, -5, 100);                assertTrue ( ms.buffer().length >=  10 && ms.length()  == 10 );        assertEquals( ms.toString(), "0123456789");


        StringBuffer tSBEmpty= new StringBuffer ( );
        ms= new AString( (StringBuffer) null );       assertTrue ( ms.length() == 0 );      assertTrue ( ms.getAllocation() == 0 );
        ms.append( "was null" );                      assertTrue ( ms.length() == 8 );
        ms= new AString( tSBEmpty );                  assertTrue ( ms.length() == 0 );      assertTrue ( ms.getAllocation() > 0 );
        ms= new AString( tSBEmpty, 1,     0 );        assertTrue ( ms.length() == 0 );      assertTrue ( ms.getAllocation() > 0 );
        ms= new AString( tSBEmpty, -1000, 0 );        assertTrue ( ms.length() == 0 );      assertTrue ( ms.getAllocation() > 0 );
        ms= new AString( tSBEmpty, -1000, 1 );        assertTrue ( ms.length() == 0 );      assertTrue ( ms.getAllocation() > 0 );
        ms= new AString( tSBEmpty, -100,  1000);      assertTrue ( ms.length() == 0 );      assertTrue ( ms.getAllocation() > 0 );

        StringBuffer tSB= new StringBuffer ( "0123456789" );
        ms= new AString( tSB );                       assertTrue ( ms.buffer().length >=  10 && ms.length()  == 10 );        assertEquals( ms.toString(), "0123456789");
        ms= new AString( tSB, 5);                     assertTrue ( ms.buffer().length >=   5 && ms.length()  ==  5 );        assertEquals( ms.toString(), "56789");
        ms= new AString( tSB, 5, 100);                assertTrue ( ms.buffer().length >=   5 && ms.length()  ==  5 );        assertEquals( ms.toString(), "56789");
        ms= new AString( tSB, -5);                    assertTrue ( ms.buffer().length >=  10 && ms.length()  == 10 );        assertEquals( ms.toString(), "0123456789");
        ms= new AString( tSB, -5, 10);                assertTrue ( ms.buffer().length >=   5 && ms.length()  ==  5 );        assertEquals( ms.toString(), "01234");
        ms= new AString( tSB, -5, 100);               assertTrue ( ms.buffer().length >=  10 && ms.length()  == 10 );        assertEquals( ms.toString(), "0123456789");

    }

    //---------------------------------------------------------------------------------------------------------
    //--- Test DeleteInsert
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void DeleteInsertSet()
    {
        AString ms= new AString();
        // delete
        {
            ms.clear().append("0123456789");        ms.delete(  5          );    assertEquals    (  5,    ms.length() );    assertEquals( "01234",         ms.toString() );
            ms.clear().append("0123456789");        ms.delete(  5,      0  );    assertEquals    ( 10,    ms.length() );    assertEquals( "0123456789",    ms.toString() );
            ms.clear().append("0123456789");        ms.delete(  5,     -1  );    assertEquals    ( 10,    ms.length() );    assertEquals( "0123456789",    ms.toString() );
            ms.clear().append("0123456789");        ms.delete(  5,      1  );    assertEquals    (  9,    ms.length() );    assertEquals( "012346789",     ms.toString() );
            ms.clear().append("0123456789");        ms.delete(  5,    100  );    assertEquals    (  5,    ms.length() );    assertEquals( "01234",         ms.toString() );
            ms.clear().append("0123456789");        ms.delete(  -5,     10 );    assertEquals    (  5,    ms.length() );    assertEquals( "56789",         ms.toString() );
        }

        // insert
        {
            ms.clear().append("0123456789");        ms.insert( -1,    1        );    assertEquals    ( 10,    ms.length() );    assertEquals( "0123456789",        ms.toString() );
            ms.clear().append("0123456789");        ms.insert( 20,    1        );    assertEquals    ( 10,    ms.length() );    assertEquals( "0123456789",        ms.toString() );
            ms.clear().append("0123456789");        ms.insert(  0,    0        );    assertEquals    ( 10,    ms.length() );    assertEquals( "0123456789",        ms.toString() );

            ms.clear().append("0123456789");        ms.insert(  0,    1        );    assertEquals    ( 11,    ms.length() );    assertEquals( " 0123456789",    ms.toString() );
            ms.clear().append("0123456789");        ms.insert(  1,    1        );    assertEquals    ( 11,    ms.length() );    assertEquals( "0 123456789",    ms.toString() );
            ms.clear().append("0123456789");        ms.insert(  0,    2        );    assertEquals    ( 12,    ms.length() );    assertEquals( "  0123456789",    ms.toString() );
            ms.clear().append("0123456789");        ms.insert(  1,    2        );    assertEquals    ( 12,    ms.length() );    assertEquals( "0  123456789",    ms.toString() );

            ms.clear().append("0123456789");        ms.insert(  11,    1       );    assertEquals    ( 10,    ms.length() );    assertEquals( "0123456789",        ms.toString() );
            ms.clear().append("0123456789");        ms.insert(  10,    1       );    assertEquals    ( 11,    ms.length() );    assertEquals( "0123456789 ",    ms.toString() );
            ms.clear().append("0123456789");        ms.insert(  5,    3, '@'   );    assertEquals    ( 13,    ms.length() );    assertEquals( "01234@@@56789",    ms.toString() );

            // test if tab reference pos is preserved
            ms.clear().append("ABC").newLine().append("123").insert(  3, 3, '@'  ).tab(5, 0, '$').append('>');
            assertEquals    ( new AString("ABC@@@").newLine().append( "123$$>" ).toString(),    ms.toString() );

            ms.clear().append("ABC").newLine().append("123"); ms.insert(  ms.length()-2, 3, '@'  ).tab(5, 0, '$').append('>');
            assertEquals    ( new AString("ABC").newLine().append( "1@@@23$$$$>" ).toString(),    ms.toString() );
        }

        // set
        {
            ms.clear().append("0123456789");  ms.set( '@'           );  assertEquals( 10,  ms.length() ); assertEquals( "@@@@@@@@@@", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@', -10      );  assertEquals( 10,  ms.length() ); assertEquals( "@@@@@@@@@@", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@', -10, 100 );  assertEquals( 10,  ms.length() ); assertEquals( "@@@@@@@@@@", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@', -10,  5  );  assertEquals( 10,  ms.length() ); assertEquals( "0123456789", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@', -10, 10  );  assertEquals( 10,  ms.length() ); assertEquals( "0123456789", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@', -10, 11  );  assertEquals( 10,  ms.length() ); assertEquals( "@123456789", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@',   0,  1  );  assertEquals( 10,  ms.length() ); assertEquals( "@123456789", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@',   0,  2  );  assertEquals( 10,  ms.length() ); assertEquals( "@@23456789", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@',   1,  1  );  assertEquals( 10,  ms.length() ); assertEquals( "0@23456789", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@',   1,  2  );  assertEquals( 10,  ms.length() ); assertEquals( "0@@3456789", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@',   8,  1  );  assertEquals( 10,  ms.length() ); assertEquals( "01234567@9", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@',   8,  2  );  assertEquals( 10,  ms.length() ); assertEquals( "01234567@@", ms.toString() );
            ms.clear().append("0123456789");  ms.set( '@',   8,  3  );  assertEquals( 10,  ms.length() ); assertEquals( "01234567@@", ms.toString() );
        }

    }

    //---------------------------------------------------------------------------------------------------------
    //--- Test Conversion
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void Conversion()
    {
        AString   ms;
        String            s;
        ms= new AString("0123456789");
        s= ms.toString();              assertTrue( s.equals("0123456789") );
        s= ms.toString( 5);            assertTrue( s.equals("56789") );
        s= ms.toString( 5, 100);       assertTrue( s.equals("56789") );
        s= ms.toString( -5);           assertTrue( s.equals("0123456789") );
        s= ms.toString( -5, 10 );      assertTrue( s.equals("01234") );
        s= ms.toString( -5, 100);      assertTrue( s.equals("0123456789") );

        s= ms.toString(  0,    0);     assertTrue( s.equals("") );
        s= ms.toString(  5,    0);     assertTrue( s.equals("") );
        s= ms.toString( 20,    0);     assertTrue( s.equals("") );
        s= ms.toString(  0,   -1);     assertTrue( s.equals("") );
        s= ms.toString(  5,   -5);     assertTrue( s.equals("") );
        s= ms.toString(  5, -100);     assertTrue( s.equals("") );
        s= ms.toString( 20,   -1);     assertTrue( s.equals("") );
        s= ms.toString( 20,   20);     assertTrue( s.equals("") );
        s= ms.toString( 20, -100);     assertTrue( s.equals("") );
        s= ms.toString( 20,    0);     assertTrue( s.equals("") );
        s= ms.toString( 20,  100);     assertTrue( s.equals("") );

        StringBuilder sb= new StringBuilder();
        ms.toString( sb, 0, ms.length(), false );    assertTrue( sb.toString().equals("0123456789") );
        ms.toString( sb, 0, ms.length(), true  );    assertTrue( sb.toString().equals("01234567890123456789") );
        ms.toString( sb, 0, ms.length(), false );    assertTrue( sb.toString().equals("0123456789") );
        ms.toString( sb, 5, 100,         false );    assertTrue( sb.toString().equals("56789") );
        ms.toString( sb, -5, 10,         true  );    assertTrue( sb.toString().equals("5678901234") );
    }

    //---------------------------------------------------------------------------------------------------------
    //--- Test Append
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void append()
    {
        // append strings
        {
            // create mutable string
            AString ms=    new AString(5);
            assertTrue( ms.length() == 0 );

            // append constant string
            {
                String  t=    "Hallo World";
                ms=    new AString(5);
                ms.append(t);

                assertTrue( ms.length() == t.length());
                for ( int i= 0; i < t.length() ; i++ )
                    assertEquals( ms.buffer()[i],  t.charAt( i ));
            }

            // append part of constant string
            {
                String  t=        "Hallo World";
                int     startIdx= 6;
                int     len=      3;
                        ms=       new AString(5);
                ms.append( t, startIdx, len );

                assertTrue( ms.length() == len);
                for ( int i= 0; i < len ; i++ )
                    assertEquals( ms.buffer()[i],  t.charAt( startIdx + i) );
            }

            // append more than available in source string
            {
                String  t=        "Hallo World";
                int     startIdx= 6;
                int     len=      3;
                        ms=       new AString(5);
                ms.append(t);
                ms.append ( t, startIdx, t.length() );
                len= t.length() - startIdx;

                assertTrue( ms.length() == t.length() + len );
                for ( int i= 0; i < len ; i++ )
                    assertEquals( ms.buffer()[t.length() + i],  t.charAt( startIdx + i) );
            }

            // append int
            {
                ms= new AString();
                int ui;
                int  i;

                ms.clear(); ui=   0;  ms.append( ui     ); assertEquals(      "0", ms.toString());
                ms.clear(); ui=   0;  ms.append( ui,  1 ); assertEquals(      "0", ms.toString());
                ms.clear(); ui=   0;  ms.append( ui,  3 ); assertEquals(    "000", ms.toString());
                ms.clear(); ui=  10;  ms.append( ui     ); assertEquals(     "10", ms.toString());
                ms.clear(); ui= 100;  ms.append( ui,  1 ); assertEquals(    "100", ms.toString());
                ms.clear(); ui= 100;  ms.append( ui,  3 ); assertEquals(    "100", ms.toString());
                ms.clear(); ui= 100;  ms.append( ui,  4 ); assertEquals(   "0100", ms.toString());
                ms.clear(); ui=  23;  ms.append( ui     ); assertEquals(     "23", ms.toString());
                ms.clear(); ui=  99;  ms.append( ui,  5 ); assertEquals(  "00099", ms.toString());
                ms.clear(); i=   49;  ms.append( i      ); assertEquals(     "49", ms.toString());
                ms.clear(); i=   -5;  ms.append( i,   5 ); assertEquals( "-00005", ms.toString());
                ms.clear(); i=-5324;  ms.append( i,   2 ); assertEquals(  "-5324", ms.toString());

                i= Integer.MAX_VALUE;
                int iLen= ( "" + i ).length();
                ms= new AString( iLen -1 );     ms.append( i );     assertEquals("" + i, ms.toString()); assertTrue( ms.buffer().length >= iLen );
                ms= new AString( iLen    );     ms.append( i );     assertEquals("" + i, ms.toString()); assertTrue( ms.buffer().length >= iLen + 1);
                ms= new AString( iLen +1 );     ms.append( i );     assertEquals("" + i, ms.toString()); assertTrue( ms.buffer().length == iLen + 1 );

                ui= Integer.MIN_VALUE;
                iLen= ( "" + i ).length();
                ms= new AString( iLen -1 );     ms.append( i );     assertEquals("" + i, ms.toString()); assertTrue( ms.buffer().length >= iLen );
                ms= new AString( iLen    );     ms.append( i );     assertEquals("" + i, ms.toString()); assertTrue( ms.buffer().length >= iLen );
                ms= new AString( iLen +1 );     ms.append( i );     assertEquals("" + i, ms.toString()); assertTrue( ms.buffer().length == iLen + 1 );
            }

            // append double
            {
                ms= new AString();
                double d;

                ms.clear(); d=      0d;  ms.append( d, 0,0 );  assertEquals(    "0.",    ms.toString());
                ms.clear(); d=      0d;  ms.append( d, 1,1 );  assertEquals(    "0.0",   ms.toString());
                ms.clear(); d=      0d;  ms.append( d, 2,2 );  assertEquals(   "00.00",  ms.toString());
                ms.clear(); d=     10d;  ms.append( d, 2,2 );  assertEquals(   "10.00",  ms.toString());
                ms.clear(); d=  23.37d;  ms.append( d, 2,1 );  assertEquals(   "23.4",   ms.toString());
                ms.clear(); d=  23.37d;  ms.append( d, 2,3 );  assertEquals(   "23.370", ms.toString());
                ms.clear(); d= 12.345d;  ms.append( d, 0,3 );  assertEquals(   "12.345", ms.toString());
                ms.clear(); d=   -5.1d;  ms.append( d, 5,0 );  assertEquals("-00005.",   ms.toString());
                ms.clear(); d=   -5.1d;  ms.append( d, 5,1 );  assertEquals("-00005.1",  ms.toString());
                ms.clear(); d= -53.24d;  ms.append( d, 2,2 );  assertEquals(  "-53.24",  ms.toString());
                ms.clear(); d=   -0.2d;  ms.append( d, 1,3 );  assertEquals(   "-0.200", ms.toString());
                ms.clear(); d=   -0.6d;  ms.append( d, 1,3 );  assertEquals(   "-0.600", ms.toString());
                ms.clear(); d= -0.999d;  ms.append( d, 1,3 );  assertEquals(   "-0.999", ms.toString());
                ms.clear(); d=  0.999d;  ms.append( d, 1,3 );  assertEquals(    "0.999", ms.toString());
                ms.clear(); d=    0.99;  ms.append( d, 1,3 );  assertEquals(    "0.990", ms.toString());
                ms.clear(); d=   0.999;  ms.append( d, 1,3 );  assertEquals(    "0.999", ms.toString());
                ms.clear(); d=  0.9999;  ms.append( d, 1,3 );  assertEquals(    "1.000", ms.toString());
                ms.clear(); d= 0.99999;  ms.append( d, 1,3 );  assertEquals(    "1.000", ms.toString());

                d= -3.0d;
                double end= 3.0d;
                double inc= 0.001d;
                int    digits= 5;
                while ( d <= end)
                {
                    ms.clear();
                    ms.append( d, 0, digits );
                    double dRes= Double.parseDouble( ms.toString() );
                    assertEquals( d, dRes, 0.00000001d );
                    d+= inc;
                }
            }
        }

        // append mutable strings
        {
            // create mutable string
            AString ms=    new AString();
            assertTrue( ms.length() == 0 );

            // append constant string
            AString t=    new AString();
            t.append( "Hallo World" );
            ms.append(t);

            assertTrue( ms.length() == t.length() );
            for ( int i= 0; i < t.length() ; i++ )
                assertEquals( ms.buffer()[i],  t.buffer()[i] );

            // append part of constant string
            int startIdx= 6;
            int len=      3;
            ms.append( t, startIdx, len );

            assertTrue( ms.length() == t.length() + len);
            for ( int i= 0; i < len ; i++ )
                assertEquals( ms.buffer()[t.length() + i],  t.buffer()[ startIdx + i]);

            // append more than available in source string
            ms=    new AString(5);
            ms.append(t);
            ms.append ( t, startIdx, t.length() );
            len= t.length() - startIdx;

            assertTrue( ms.length() == t.length() + len);
            for ( int i= 0; i < len ; i++ )
                assertEquals( ms.buffer()[t.length() + i],  t.buffer()[ startIdx + i]);
        }

        // append String Builders
        {
            // create mutable string
            AString ms=    new AString();
            assertTrue( ms.length() == 0 );

            // append constant string
            StringBuffer t=    new StringBuffer();
            t.append( "Hallo World" );
            ms.append(t);

            assertTrue( ms.length() == t.length());
            for ( int i= 0; i < t.length() ; i++ )
                assertEquals( ms.buffer()[i],  t.charAt( i ) );

            // append part of constant string
            int startIdx= 6;
            int len=      3;
            ms.append( t, startIdx, len );

            assertTrue( ms.length() == t.length() + len );
            for ( int i= 0; i < len ; i++ )
                assertEquals( ms.buffer()[t.length() + i],  t.charAt( startIdx + i) );

            // append more than available in source string
            ms=    new AString(5);
            ms.append(t);
            ms.append ( t, startIdx, t.length() );
            len= t.length() - startIdx;

            assertTrue( ms.length() == t.length() + len );
            for ( int i= 0; i < len ; i++ )
                assertEquals( ms.buffer()[t.length() + i],  t.charAt( startIdx + i) );
        }

    }

    //---------------------------------------------------------------------------------------------------------
    //--- Test Capacity
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void CapacityLength()
    {
        // null-allocated
        {
            AString ms= new AString();       assertTrue ( ms.getAllocation() == 0 );
                    ms= new AString( 0 );    assertTrue ( ms.getAllocation() == 0 );
                    ms= new AString( null ); assertTrue ( ms.getAllocation() == 0 );
            ms.append( "" );        assertTrue ( ms.getAllocation() > 0 );
        }
    
        {
            AString ms= new AString( 5 );
            ms.append( 'a' );        assertTrue ( ms.buffer().length == 5 );
            ms.append( 'b' );        assertTrue ( ms.buffer().length == 5 );
            ms.append( 'c' );        assertTrue ( ms.buffer().length == 5 );
            ms.append( 'd' );        assertTrue ( ms.buffer().length == 5 );
            ms.append( 'e' );        assertTrue ( ms.buffer().length == 5 );
            ms.append( 'x' );
            assertTrue ( ms.buffer().length >= 6 );
            assertEquals( "abcdex", ms.toString() );

            ms.ensureAllocation( 2000 ); assertTrue ( ms.buffer().length >= 2000 );
        }

        {
            AString   ms= new AString();
            int as;
            ms.append( "0123456789" );  assertEquals    ( ms.length(), 10 );    assertTrue  ( ms.getAllocation() >= 10 );

            as= ms.getAllocation();

            System.out.println( "A warning should follow" );
            ms.setLength(20);           assertEquals    ( ms.length(), 10 );    assertEquals( ms.getAllocation(), as );    assertEquals( ms.toString(), "0123456789" );

            System.out.println( "No (second) warning should follow" );
            ms.setLength(20);           assertEquals    ( ms.length(), 10 );    assertEquals( ms.getAllocation(), as );    assertEquals( ms.toString(), "0123456789" );

            AString.AWXU_OTW_SetLength= true;

            System.out.println( "No warning should follow" );
            ms.setLength(10);           assertEquals    ( ms.length(), 10 );    assertEquals( ms.getAllocation(), as );    assertEquals( ms.toString(), "0123456789" );

            System.out.println( "A warning should follow" );
            ms.setLength(11);           assertEquals    ( ms.length(), 10 );    assertEquals( ms.getAllocation(), as );    assertEquals( ms.toString(), "0123456789" );

            System.out.println( "No (second) warning should follow" );
            ms.setLength(11);           assertEquals    ( ms.length(), 10 );    assertEquals( ms.getAllocation(), as );    assertEquals( ms.toString(), "0123456789" );

            ms.setLength(5);            assertEquals    ( ms.length(), 5 );     assertEquals( ms.getAllocation(), as );    assertEquals( ms.toString(), "01234"     );
            ms.setAllocation(3);        assertEquals    ( ms.length(), 3 );     assertEquals( ms.getAllocation(), 3  );    assertEquals( ms.toString(), "012"         );
            ms.append("ABC");           assertEquals    ( ms.length(), 6 );     assertTrue  ( ms.getAllocation() >= 6);    assertEquals( ms.toString(), "012ABC"     );
        }

    }

    //---------------------------------------------------------------------------------------------------------
    //--- Test AppendWithPadding
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void Fields()
    {
        AString ms= new AString();

        // empty fields
        ms.clear();
        ms.field().field( 3, AString.Align.LEFT,     '#' );    assertEquals( ms.toString(), "###"           );
        ms.field().field( 4, AString.Align.CENTER,   '*' );    assertEquals( ms.toString(), "###****"       );
        ms.field().field( 5, AString.Align.RIGHT,    '+' );    assertEquals( ms.toString(), "###****+++++"  );

        // field, alignment left
        ms.clear();
        ms.field().append( "A" )        .field( 5,    AString.Align.LEFT );
        ms.field().append( "AB" )       .field( 5,    AString.Align.LEFT );
        ms.field().append( "ABC" )      .field( 5,    AString.Align.LEFT );
        ms.field().append( "ABCD" )     .field( 5,    AString.Align.LEFT );
        ms.field().append( "ABCDE" )    .field( 5,    AString.Align.LEFT );
        ms.field().append( "ABCDEF" )   .field( 5,    AString.Align.LEFT );
        ms.field().append( "ABCDEFG" )  .field( 5,    AString.Align.LEFT );
        assertEquals( ms.toString(), "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG" );

        // field, alignment right
        ms.clear();
        ms.field().append( "A" )        .field( 5,    AString.Align.RIGHT );
        ms.field().append( "AB" )       .field( 5,    AString.Align.RIGHT );
        ms.field().append( "ABC" )      .field( 5 ); // btw: right is default
        ms.field().append( "ABCD" )     .field( 5 );
        ms.field().append( "ABCDE" )    .field( 5 );
        ms.field().append( "ABCDEF" )   .field( 5,    AString.Align.RIGHT );
        ms.field().append( "ABCDEFG" )  .field( 5,    AString.Align.RIGHT );
        assertEquals( ms.toString(), "    A   AB  ABC ABCDABCDEABCDEFABCDEFG" );

        // field, alignment center
        ms.clear();
        ms.field().append( "A" )        .field( 5,    AString.Align.CENTER );
        ms.field().append( "AB" )       .field( 5,    AString.Align.CENTER );
        ms.field().append( "ABC" )      .field( 5,    AString.Align.CENTER );
        ms.field().append( "ABCD" )     .field( 5,    AString.Align.CENTER );
        ms.field().append( "ABCDE" )    .field( 5,    AString.Align.CENTER );
        ms.field().append( "ABCDEF" )   .field( 5,    AString.Align.CENTER );
        ms.field().append( "ABCDEFG" )  .field( 5,    AString.Align.CENTER );
        assertEquals( ms.toString(), "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG" );

        // a nested field
        ms.clear();
        ms.append("***");
            int outerFieldStart= ms.length();
            ms.append( "OS:" )  .field().append( "Linux" ).field( 10, AString.Align.RIGHT, '-' );
            ms.append( " Lang:").field().append( "en_US" ).field(  8, AString.Align.RIGHT, '-' );
            ms.field(35, AString.Align.CENTER, '#', outerFieldStart );
        ms.append("***");
        assertEquals( ms.toString(), "***####OS:-----Linux Lang:---en_US####***" );
    }


    //---------------------------------------------------------------------------------------------------------
    //--- Test Tabs
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void Tabs()
    {
        AString ms= new AString();

        // test some bad input
                     ms.tab(  0,    -1,  '@' );  assertEquals( "",  ms.toString() );
        ms.clear();  ms.tab(  0,     0,  '@' );  assertEquals( "",  ms.toString() );
        ms.clear();  ms.tab( -1,     0,  '@' );  assertEquals( "",  ms.toString() );
        ms.clear();  ms.tab( -1,     0,  '@' );  assertEquals( "",  ms.toString() );
        ms.clear();  ms.tab( -1,    -1,  '@' );  assertEquals( "",  ms.toString() );
        ms.clear();  ms.tab( -5,     0,  '@' );  assertEquals( "",  ms.toString() );
        ms.clear();  ms.tab( -5,  -100,  '@' );  assertEquals( "",  ms.toString() );
        ms.clear();  ms.tab(  2,  -100,  '@' );  assertEquals( "",  ms.toString() );
        ms.clear();  ms.tab(  0,     0,  '@' );  assertEquals( "",  ms.toString() );
        ms.clear();  ms.tab(  1,     0,  '@' );  assertEquals( "",  ms.toString() );
        ms.clear();  ms.tab(  1,     1,  '@' );  assertEquals( "@", ms.toString() );
        ms.clear();  ms.tab(  0,     1,  '@' );  assertEquals( "@", ms.toString() );

        // minpad 0 (not common, default is 1, tab wont move if on tab position)
        ms.clear();                        ms.tab( 2, 0,    '@' ).append( '-' );        assertEquals( "-",   ms.toString());
        ms.clear();    ms.append( 'x' );    ms.tab( 2, 0,    '@' ).append( '-' );        assertEquals( "x@-", ms.toString());

        // more standard tabs
        ms.clear();
        ms.append( "12" ).tab( 2 )
          .append( "1" ).tab( 2 )
          .tab(2)
          .append( "@" );
        assertEquals( "12  1   @", ms.toString() );

        ms.clear();
        ms.append( "12" ).tab( 2, 0 )
          .append( "1"  ).tab( 2, 0 )
                           .tab( 2, 0 )
          .append( "@" );
        assertEquals( "121 @", ms.toString() );


        ms.clear();
        ms.append( "12345" ).tab( 5 )
          .append( "1234" ) .tab( 5 )
          .append( "123" )  .tab( 5 )
          .append( "12" )   .tab( 5 )
          .append( "1" )    .tab( 5 )
                            .tab( 5 )
          .append( "@" );
        assertEquals( "12345     1234 123  12   1         @", ms.toString() );

        ms.clear();
        ms.append( "12345" ).tab( 5, 0 )
          .append( "1234" ) .tab( 5, 0 )
          .append( "123" )  .tab( 5, 0 )
          .append( "12" )   .tab( 5, 0 )
          .append( "1" )    .tab( 5, 0 )
                            .tab( 5, 0 )
          .append( "@" );
        assertEquals( "123451234 123  12   1    @", ms.toString() );

        ms.clear();                        ms.tab( 0 ).append( '-' ); assertEquals( " -"  , ms.toString() );
        ms.clear();                        ms.tab( 1 ).append( '-' ); assertEquals( " -"  , ms.toString() );
        ms.clear();                        ms.tab( 2 ).append( '-' ); assertEquals( "  -" , ms.toString() );
        ms.clear();                        ms.tab( 3 ).append( '-' ); assertEquals( "   -", ms.toString() );
        ms.clear();    ms.append( 'x' );   ms.tab( 1 ).append( '-' ); assertEquals( "x -" , ms.toString() );
        ms.clear();    ms.append( 'x' );   ms.tab( 2 ).append( '-' ); assertEquals( "x -" , ms.toString() );
        ms.clear();    ms.append( 'x' );   ms.tab( 3 ).append( '-' ); assertEquals( "x  -", ms.toString() );

        // tabs with tab reference set (designed for multi line tabs)
        ms.clear().append("ABC").newLine();
        ms.append( "12345" ).tab( 5 )
          .append( "1234" ) .tab( 5 )
          .append( "123" )  .tab( 5 )
          .append( "12" )   .tab( 5 )
          .append( "1" )    .tab( 5 )
                            .tab( 5 )
          .append( "@" );
        assertEquals( "ABC" + AString.NEWLINE  + "12345     1234 123  12   1         @", ms.toString() );

        ms.clear().append("ABC").newLine();
        ms.append( "12345" ).tab( 5, 0 )
          .append( "1234" ) .tab( 5, 0 )
          .append( "123" )  .tab( 5, 0 )
          .append( "12" )   .tab( 5, 0 )
          .append( "1" )    .tab( 5, 0 )
                            .tab( 5, 0 )
          .append( "@" );
        assertEquals( "ABC" + AString.NEWLINE  + "123451234 123  12   1    @", ms.toString() );
    }

    //---------------------------------------------------------------------------------------------------------
    //--- Test SearchAndReplace
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void SearchAndReplace()
    {
        AString ms= new AString();
        int result;

        // search characters
        ms.clear().append("abcd abcd");
        {
            result= ms.indexOf( '@'      );  assertEquals(  -1,  result );
            result= ms.indexOf( '@',  -5 );  assertEquals(  -1,  result );
            result= ms.indexOf( '@',   5 );  assertEquals(  -1,  result );
            result= ms.indexOf( '@', 150 );  assertEquals(  -1,  result );

            result= ms.indexOf( 'a'      );  assertEquals(   0,  result );
            result= ms.indexOf( 'b'      );  assertEquals(   1,  result );
            result= ms.indexOf( 'c'      );  assertEquals(   2,  result );
                                                             
            result= ms.indexOf( 'a',   0 );  assertEquals(   0,  result );
            result= ms.indexOf( 'b',   0 );  assertEquals(   1,  result );
            result= ms.indexOf( 'c',   0 );  assertEquals(   2,  result );
                                                             
            result= ms.indexOf( 'a',   1 );  assertEquals(   5,  result );
            result= ms.indexOf( 'b',   1 );  assertEquals(   1,  result );
            result= ms.indexOf( 'c',   1 );  assertEquals(   2,  result );
                                                             
            result= ms.indexOf( 'a',   2 );  assertEquals(   5,  result );
            result= ms.indexOf( 'b',   2 );  assertEquals(   6,  result );
            result= ms.indexOf( 'c',   2 );  assertEquals(   2,  result );
                                                             
            result= ms.indexOf( 'a',   3 );  assertEquals(   5,  result );
            result= ms.indexOf( 'b',   3 );  assertEquals(   6,  result );
            result= ms.indexOf( 'c',   3 );  assertEquals(   7,  result );
                                                             
            result= ms.indexOf( 'd',   7 );  assertEquals(   8,  result );
            result= ms.indexOf( 'd',   8 );  assertEquals(   8,  result );
            result= ms.indexOf( 'd',   9 );  assertEquals(  -1,  result );
        }


        // search nullptr, empty string
        ms.clear().append("abcd abcd");
        {
            result= ms.indexOf( null );           assertEquals( result, 0 );
            result= ms.indexOf( null,    5  );    assertEquals( result, 5 );
            result= ms.indexOf( null,   50  );    assertEquals( result, -1 );
            result= ms.indexOf( null,   -5  );    assertEquals( result, 0 );

            result= ms.indexOf( "",     -5  );    assertEquals( result, 0 );
            result= ms.indexOf( "",      0  );    assertEquals( result, 0 );
            result= ms.indexOf( "",      4  );    assertEquals( result, 4 );
            result= ms.indexOf( "",    100  );    assertEquals( result,-1 );

        }

        // search
        ms.clear().append("abcd abcd");
        {
            result= ms.indexOf( "abcd"     );            assertTrue( result == 0 );
            result= ms.indexOf( "b"        );            assertTrue( result == 1 );
            result= ms.indexOf( " abcd"    );            assertTrue( result == 4 );
            result= ms.indexOf( "abcd",  1 );            assertTrue( result == 5 );
            result= ms.indexOf( "abcd", -1 );            assertTrue( result == 0 );
            result= ms.indexOf( "xyz", -10 );            assertTrue( result == -1 );
        }

        // ignore case
        ms.clear().append( "Hallo A-Worx util" );
        {
            result= ms.indexOf( "a-worx",   0,  true ); assertEquals( result,  6 );
            result= ms.indexOf( "a-worx",   1,  true ); assertEquals( result,  6 );
            result= ms.indexOf( "a-worx", -10,  true ); assertEquals( result,  6 );
            result= ms.indexOf( "a-worx",   6,  true ); assertEquals( result,  6 );
            result= ms.indexOf( "a-worx",   7,  true ); assertEquals( result, -1 );
            result= ms.indexOf( "a-worx", 100,  true ); assertEquals( result, -1 );
            result= ms.indexOf( "hal",      0,  true ); assertEquals( result,  0 );
            result= ms.indexOf( "hal",      1,  true ); assertEquals( result, -1 );
            result= ms.indexOf( "util",     1,  true ); assertEquals( result, 13 );
            result= ms.indexOf( "UTIL",     5,  true ); assertEquals( result, 13 );
            result= ms.indexOf( "UTIL",    13,  true ); assertEquals( result, 13 );
            result= ms.indexOf( "UTIL",    14,  true ); assertEquals( result, -1 );
        }

        // search in normal strings ignore case (static util methods)
        String s= "Hallo A-Worx util";
        {
            result= AString.indexOfIgnoreCase( s, "a-worx"       ); assertTrue( result ==  6 );
            result= AString.indexOfIgnoreCase( s, "a-worx",   1  ); assertTrue( result ==  6 );
            result= AString.indexOfIgnoreCase( s, "a-worx", -10  ); assertTrue( result ==  6 );
            result= AString.indexOfIgnoreCase( s, "a-worx",   6  ); assertTrue( result ==  6 );
            result= AString.indexOfIgnoreCase( s, "a-worx",   7  ); assertTrue( result == -1 );
            result= AString.indexOfIgnoreCase( s, "a-worx", 100  ); assertTrue( result == -1 );
            result= AString.indexOfIgnoreCase( s, "hal",      0  ); assertTrue( result ==  0 );
            result= AString.indexOfIgnoreCase( s, "hal",      1  ); assertTrue( result == -1 );
            result= AString.indexOfIgnoreCase( s, "util",     1  ); assertTrue( result == 13 );
            result= AString.indexOfIgnoreCase( s, "UTIL",     5  ); assertTrue( result == 13 );
            result= AString.indexOfIgnoreCase( s, "UTIL",    13  ); assertTrue( result == 13 );
            result= AString.indexOfIgnoreCase( s, "UTIL",    14  ); assertTrue( result == -1 );
        }

        // replace nullptr
        ms.clear().append("Hello");
        {
            ms.replace( null, null );   assertEquals( ms.toString(), "Hello" );
            ms.replace( "l",  null );   assertEquals( ms.toString(), "Heo" );
            ms.replace( null, "xx" );   assertEquals( ms.toString(), "Heo" );
        }

        // replaceCount nullptr
        ms.clear().append("Hello");
        {
            result= ms.replaceCount( null, null );  assertEquals( ms.toString(), "Hello" );  assertEquals( 0, result );
            result= ms.replaceCount( "l",  null );  assertEquals( ms.toString(), "Heo"   );  assertEquals( 2, result );
            result= ms.replaceCount( null, "xx" );  assertEquals( ms.toString(), "Heo"   );  assertEquals( 0, result );
        }

        // replace
        ms.clear().append("Hello W!");
        {
            result= ms.replaceCount( "W!",    "world!"  );    assertEquals( ms.toString(), "Hello world!"   );    assertEquals( 1, result );
            result= ms.replaceCount( " ",    "* *"      );    assertEquals( ms.toString(), "Hello* *world!" );    assertEquals( 1, result );
            result= ms.replaceCount( "*",    "#", 0, 1  );    assertEquals( ms.toString(), "Hello# *world!" );    assertEquals( 1, result );
            result= ms.replaceCount( "*",    "#"        );    assertEquals( ms.toString(), "Hello# #world!" );    assertEquals( 1, result );
            result= ms.replaceCount( "#",    "$$$"      );    assertEquals( ms.toString(), "Hello$$$ $$$world!"); assertEquals( 2, result );
            result= ms.replaceCount( "$$$",    "*"      );    assertEquals( ms.toString(), "Hello* *world!" );    assertEquals( 2, result );
            result= ms.replaceCount( "*",    ""         );    assertEquals( ms.toString(), "Hello world!"   );    assertEquals( 2, result );
        }

        // replace one space by two spaces in a string of spaces
        ms.clear().append("     ");
        {
            result= ms.replaceCount( " ",    "  "  );        assertEquals( ms.toString(), "          " );        assertEquals( 5, result );
        }

        // replace ignoreCase
        {
            ms.clear().append("ABC"); result= ms.replaceCount( "abc", "xxx",0, 1, false ); assertEquals( ms.toString(), "ABC" ); assertEquals( 0, result );
            ms.clear().append("ABC"); result= ms.replaceCount( "abc", "xxx",0, 1, true  ); assertEquals( ms.toString(), "xxx" ); assertEquals( 1, result );
            ms.clear().append("ABC"); result= ms.replaceCount( "ABC", "xxx",0, 1, true  ); assertEquals( ms.toString(), "xxx" ); assertEquals( 1, result );

            ms.clear().append("abc");         ms.replaceCount( "ABC", "xxx",0, 1, false ); assertEquals( ms.toString(), "abc" );
            ms.clear().append("abc");         ms.replaceCount( "ABC", "xxx",0, 1, true  ); assertEquals( ms.toString(), "xxx" );
            ms.clear().append("abc");         ms.replaceCount( "abc", "xxx",0, 1, true  ); assertEquals( ms.toString(), "xxx" );
        }

    }

    //---------------------------------------------------------------------------------------------------------
    //--- Test Compare
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void Compare()
    {
        AString ms= new AString();
        int result;

        // null string comparison
        String  nullString= null;
        AString aString= new AString(0);
        assertTrue( aString.compareTo( nullString) == 0 );
        assertTrue( aString.equals( nullString) );
    
        aString.append( "" );
        assertTrue( aString.compareTo( nullString) != 0 );
        assertTrue( !aString.equals( nullString) );
    
        aString.setAllocation( 0 );
        assertTrue( aString.compareTo( nullString) == 0 );
        assertTrue( aString.equals( nullString) );


        String t= "abcde";
        ms.append( t );
        result= ms.compareTo( t      );                          assertEquals( t.compareTo( t ),                                result );
        result= ms.compareTo( t + "x"      );                    assertEquals( t.compareTo( t + "x" ),                          result );
        result= ms.compareTo( t.substring (0, t.length() -1 )  );assertEquals( t.compareTo( t.substring (0, t.length() -1 ) ),  result );
        result= ms.compareTo( "pad" + t,  false, 3      );       assertEquals(  0,                                              result );
        result= ms.compareTo( "pad" + t,  false, 3, 2  );        assertEquals(  1,                                              result );
        result= ms.compareTo( "pad" + t,  false, 3, 100, 0, 4 ); assertEquals( -1,                                              result );
        result= ms.compareTo( "pad" + t,  false, 3, 100, 0, 5 ); assertEquals(  0,                                              result );
        result= ms.compareTo( t, false, 2,2,   2,2      );       assertEquals(  0,                                              result );
        result= ms.compareTo( t, false, 2,2,   2,1      );       assertEquals( -1,                                              result );
        result= ms.compareTo( t, false, 2,2,   2,3      );       assertEquals(  1,                                              result );

        result= ms.compareTo( t, false, -2,5,   -2, 5 );                                   assertEquals( 0, result );
        result= ms.compareTo( t, false,  2, Integer.MAX_VALUE,    2, Integer.MAX_VALUE );  assertEquals( 0, result );
        result= ms.compareTo( t, false, -2, Integer.MAX_VALUE,   -2, Integer.MAX_VALUE );  assertEquals( 0, result );
        result= ms.compareTo( t, false, -2, 100,            -2, 99 );                      assertEquals( 0, result );
        result= ms.compareTo( t, false, -2, 5,                -2, Integer.MAX_VALUE );     assertEquals( 1, result );
        result= ms.compareTo( t, false, -2, Integer.MAX_VALUE,    -2, 5 );                 assertEquals(-1, result );

        // greater/smaller strings
        String greater=     "x";
        String greater2= "abcdef";
        String smaller=  "aaa";
        String smaller2= "abcd";
        result= ms.compareTo( greater  );   assertEquals( t.compareTo( greater  ),  result );
        result= ms.compareTo( greater2 );   assertEquals( t.compareTo( greater2 ),  result );
        result= ms.compareTo( smaller  );   assertEquals( t.compareTo( smaller ),   result );
        result= ms.compareTo( smaller2 );   assertEquals( t.compareTo( smaller2 ),  result );

        // ignore case
        String ut= t.toUpperCase();
        result= ms.compareTo( ut );                      assertEquals( t.compareTo(ut),       result );
        result= ms.compareTo( ut, false );               assertEquals( t.compareTo(ut),       result );
        result= ms.compareTo( ut, true );                assertEquals( 0,                     result );
        result= ms.compareTo( ut, false, 2,2,   2,2 );   assertEquals( "cd".compareTo("CD"),  result );
        result= ms.compareTo( ut, true,  2,2,   2,2 );   assertEquals( 0,                     result );


        // we do just a very little testing with StringBuffer and AString parameter version of this function, as
        // the code differences are very small
        StringBuffer tSB= new StringBuffer(); tSB.append( t );
        result= ms.compareTo( tSB      );                            assertEquals( 0,  result );
        result= ms.compareTo( tSB, false, -5, 100, -10, 100      );  assertEquals( 0,  result );
        result= ms.compareTo( tSB, false,  2,   3,   2,   3      );  assertEquals( 0,  result );

        AString tMS= new AString(); tMS.append( t );
        result= ms.compareTo( tMS      );                            assertEquals( 0,  result );
        result= ms.compareTo( tMS, false, -5, 100, -10, 100      );  assertEquals( 0,  result );
        result= ms.compareTo( tMS, false,  2,   3,   2,   3      );  assertEquals( 0,  result );

        // different ranges
        String r1=   "*ABCDEF*";
        String r2= "##*ABCDEF*##";
        ms.clear().append( r1 );
        result= ms.compareTo( r2, false, 2,8          );        assertEquals( 0, result );
        result= ms.compareTo( r2, false, 3,6,   1,6      );     assertEquals( 0, result );

        // startsWith/Endswith/ContainsAt
        String sub1=  "ABC";
        String sub2=  "abc";
        String s1= "ABCDEF";
        String s2= "123ABC";
        String s3= "##12ABC21##";
        String s4= "AB";
        boolean bRes;
        ms.clear().append( s1 );    bRes= ms.startsWith( sub1 );              assertEquals( true,     bRes );
                                    bRes= ms.startsWith( sub2 );              assertEquals( false,    bRes );
        ms.clear().append( s2 );    bRes= ms.endsWith  ( sub1 );              assertEquals( true,     bRes );
                                    bRes= ms.endsWith  ( sub2 );              assertEquals( false,    bRes );
        ms.clear().append( s3 );    bRes= ms.containsAt( sub1, 4 );           assertEquals( true,     bRes );
                                    bRes= ms.containsAt( sub2, 4 );           assertEquals( false,    bRes );
                                    bRes= ms.containsAt( sub2, 4, true );     assertEquals( true,     bRes );
        ms.clear().append( s4 );    bRes= ms.containsAt( sub1, 4 );           assertEquals( false,    bRes );
                                    bRes= ms.containsAt( sub2, 4 );           assertEquals( false,    bRes );
        ms.clear().append( s4 );    bRes= ms.containsAt( sub1, 0 );           assertEquals( false,    bRes );
                                    bRes= ms.containsAt( sub2, 0, true );     assertEquals( false,    bRes );

        ms.clear().append( "Hallo A-Worx util" );

                            assertTrue( ms.startsWith( "Hallo A-Worx util",  true ) == true );
                            assertTrue( ms.endsWith  ( "Hallo A-Worx util",  true ) == true  );
                            assertTrue( ms.startsWith( "Hallo A-Worx utilx", true ) == false );
                            assertTrue( ms.endsWith  ( "xHallo A-Worx util", true ) == false );
                            assertTrue( ms.startsWith( "haLLO", true ) == true  );
                            assertTrue( ms.startsWith( "HaLLO", true ) == true  );
                            assertTrue( ms.endsWith  ( "haLLO", true ) == false );
                            assertTrue( ms.startsWith( "UTIL" , true ) == false );
                            assertTrue( ms.endsWith  ( "UTIL" , true ) == true  );
                            assertTrue( ms.endsWith  ( "utIl" , true ) == true  );


        // contains with empty/null strings
        ms.clear().append( "AB" );  bRes= ms.containsAt( null, -1 );   assertEquals( false,   bRes );
                                    bRes= ms.containsAt( null,  0 );   assertEquals( true,    bRes );
                                    bRes= ms.containsAt( null,  1 );   assertEquals( true,    bRes );
                                    bRes= ms.containsAt( null,  2 );   assertEquals( true,    bRes );
                                    bRes= ms.containsAt( null,  3 );   assertEquals( false,   bRes );

        ms.clear();                 bRes= ms.containsAt( null, -1 );   assertEquals( false,   bRes );
                                    bRes= ms.containsAt( null,  0 );   assertEquals( true,    bRes );
                                    bRes= ms.containsAt( null,  1 );   assertEquals( false,   bRes );


        ms.clear().append(sub1);    bRes= ms.containsAt( "",   -1 );   assertEquals( false,   bRes );
                                    bRes= ms.containsAt( "",    0 );   assertEquals( true,    bRes );
                                    bRes= ms.containsAt( "",    1 );   assertEquals( true,    bRes );
                                    bRes= ms.containsAt( "",  100 );   assertEquals( false,   bRes );


        // equals String
        ms.clear().append( "" );    bRes= ms.equals( null );          assertEquals( false,    bRes );
                                    bRes= ms.equals( ""   );          assertEquals( true,     bRes );
                                    bRes= ms.equals( "a"  );          assertEquals( false,    bRes );

        ms.clear().append( "AB" );  bRes= ms.equals( null );          assertEquals( false,    bRes );
                                    bRes= ms.equals( ""   );          assertEquals( false,    bRes );
                                    bRes= ms.equals( "ab" );          assertEquals( false,    bRes );
                                    bRes= ms.equals( "A"  );          assertEquals( false,    bRes );
                                    bRes= ms.equals( "B"  );          assertEquals( false,    bRes );
                                    bRes= ms.equals( "AB" );          assertEquals( true,     bRes );
                                    bRes= ms.equals( "AB" );          assertEquals( true,     bRes );

        // equals AString
        ms.clear().append( "" );    bRes= ms.equals( (AString) null   );    assertEquals( false,    bRes );
                                    bRes= ms.equals( new AString(""  ));    assertEquals( true,     bRes );
                                    bRes= ms.equals( new AString("a" ));    assertEquals( false,    bRes );

        ms.clear().append( "AB" );  bRes= ms.equals( (AString) null   );    assertEquals( false,    bRes );
                                    bRes= ms.equals( new AString(""  ));    assertEquals( false,    bRes );
                                    bRes= ms.equals( new AString("ab"));    assertEquals( false,    bRes );
                                    bRes= ms.equals( new AString("A" ));    assertEquals( false,    bRes );
                                    bRes= ms.equals( new AString("B" ));    assertEquals( false,    bRes );
                                    bRes= ms.equals( new AString("AB"));    assertEquals( true,     bRes );
                                    bRes= ms.equals( new AString("AB"));    assertEquals( true,     bRes );

        // search in normal strings ignore case (static util methods)
        String s= "Hallo A-Worx util";
        {
            assertTrue( AString.startsWithIgnoreCase( s, s      ) == true  );
            assertTrue( AString.endsWithIgnoreCase  ( s, s      ) == true  );
            assertTrue( AString.startsWithIgnoreCase( s, s + "x") == false );
            assertTrue( AString.endsWithIgnoreCase  ( s, "x" +s ) == false );
            assertTrue( AString.startsWithIgnoreCase( s, "haLLO") == true  );
            assertTrue( AString.startsWithIgnoreCase( s, "HaLLO") == true  );
            assertTrue( AString.endsWithIgnoreCase  ( s, "haLLO") == false );
            assertTrue( AString.startsWithIgnoreCase( s, "UTIL" ) == false );
            assertTrue( AString.endsWithIgnoreCase  ( s, "UTIL" ) == true  );
            assertTrue( AString.endsWithIgnoreCase  ( s, "utIl" ) == true  );
        }


    }

    //---------------------------------------------------------------------------------------------------------
    //--- Test ConvertCase
    //---------------------------------------------------------------------------------------------------------
    @SuppressWarnings("static-method")
    @Test
    public void ConvertCase()
    {
        AString ms= new AString();
        String t;

        // test substring conversion
        t= "AAAbbb";
        ms.clear().append( t ).convertCase( false,  0, 2 ); assertTrue( ms.toString().equals( "aaAbbb" ) );
        ms.clear().append( t ).convertCase( false, -2, 3 ); assertTrue( ms.toString().equals( "aAAbbb" ) );
        ms.clear().append( t ).convertCase( false, -2    ); assertTrue( ms.toString().equals( "aaabbb" ) );

        ms.clear().append( t ).convertCase( true,  3,  2 ); assertTrue( ms.toString().equals( "AAABBb" ) );
        ms.clear().append( t ).convertCase( true, -2,  6 ); assertTrue( ms.toString().equals( "AAABbb" ) );
        ms.clear().append( t ).convertCase( true, -2     ); assertTrue( ms.toString().equals( "AAABBB" ) );
    }

}
