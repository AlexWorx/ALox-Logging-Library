package unittests.com.aworx.util;

import static org.junit.Assert.*;

import org.junit.Test;

import com.aworx.util.MString;


public class Test_MString
{

	@SuppressWarnings("static-method")
	@Test 
	public void MString_Constructors()
	{
		MString ms= new MString();
		ms= new MString( );							assertTrue ( ms.buffer.length > 0    && ms.length == 0 );		
		ms= new MString(25);		                assertTrue ( ms.buffer.length ==  25 && ms.length == 0 );
		ms= new MString("Test");	                assertTrue ( ms.buffer.length >=  4  && ms.length == 4 );

		MString tMSEmpty= new MString ( );
		ms= new MString( (MString) null );			assertTrue ( ms.length == 0 );
		ms= new MString( tMSEmpty );				assertTrue ( ms.length == 0 );
		ms= new MString( tMSEmpty, 1,     0 );		assertTrue ( ms.length == 0 );
		ms= new MString( tMSEmpty, -1000, 0 );		assertTrue ( ms.length == 0 );
		ms= new MString( tMSEmpty, -1000, 1 );		assertTrue ( ms.length == 0 );
		ms= new MString( tMSEmpty, -100,  1000);	assertTrue ( ms.length == 0 );

		MString tMS=		new MString ( "0123456789" );
		ms= new MString( tMS );						assertTrue ( ms.buffer.length >=  10 && ms.length == 10 );
													assertEquals( ms.toString(), "0123456789");
		ms= new MString( tMS, 5);					assertTrue ( ms.buffer.length >=  5  && ms.length == 5 );
													assertEquals( ms.toString(), "56789");
		ms= new MString( tMS, 5, 100);				assertTrue ( ms.buffer.length >=  5  && ms.length == 5 );
													assertEquals( ms.toString(), "56789");
		ms= new MString( tMS, -5);					assertTrue ( ms.buffer.length >=  10 && ms.length == 10 );
													assertEquals( ms.toString(), "0123456789");
		ms= new MString( tMS, -5, 10);				assertTrue ( ms.buffer.length >=  5  && ms.length == 5 );
													assertEquals( ms.toString(), "01234");
		ms= new MString( tMS, -5, 100);				assertTrue ( ms.buffer.length >=  10  && ms.length == 10 );
													assertEquals( ms.toString(), "0123456789");

		String tS= "0123456789";
		ms= new MString( (String) null );			assertTrue ( ms.length == 0 );
		ms= new MString( "" );						assertTrue ( ms.length == 0 );
		ms= new MString( "", 1,     0 );			assertTrue ( ms.length == 0 );
		ms= new MString( "", -1000, 0 );			assertTrue ( ms.length == 0 );
		ms= new MString( "", -1000, 1 );			assertTrue ( ms.length == 0 );
		ms= new MString( "", -100,  1000);			assertTrue ( ms.length == 0 );
		ms= new MString( tS );						assertTrue ( ms.buffer.length >=  10 && ms.length == 10 );
													assertEquals( ms.toString(), "0123456789");
		ms= new MString( tS, 5);					assertTrue ( ms.buffer.length >=  5  && ms.length == 5 );
													assertEquals( ms.toString(), "56789");
		ms= new MString( tS, 5, 100);				assertTrue ( ms.buffer.length >=  5  && ms.length == 5 );
													assertEquals( ms.toString(), "56789");
		ms= new MString( tS, -5);					assertTrue ( ms.buffer.length >=  10 && ms.length == 10 );
													assertEquals( ms.toString(), "0123456789");
		ms= new MString( tS, -5, 10);				assertTrue ( ms.buffer.length >=  5  && ms.length == 5 );
													assertEquals( ms.toString(), "01234");
		ms= new MString( tS, -5, 100);				assertTrue ( ms.buffer.length >=  10  && ms.length == 10 );
														assertEquals( ms.toString(), "0123456789");


		StringBuffer tSBEmpty= new StringBuffer ( );
		ms= new MString( (StringBuffer) null );	assertTrue ( ms.length == 0 );
		ms= new MString( tSBEmpty );				assertTrue ( ms.length == 0 );
		ms= new MString( tSBEmpty, 1,     0 );		assertTrue ( ms.length == 0 );
		ms= new MString( tSBEmpty, -1000, 0 );		assertTrue ( ms.length == 0 );
		ms= new MString( tSBEmpty, -1000, 1 );		assertTrue ( ms.length == 0 );
		ms= new MString( tSBEmpty, -100,  1000);	assertTrue ( ms.length == 0 );

		StringBuffer tSB= new StringBuffer ( "0123456789" );
		ms= new MString( tSB );						assertTrue ( ms.buffer.length >=  10 && ms.length == 10 );
													assertEquals( ms.toString(), "0123456789");
		ms= new MString( tSB, 5);					assertTrue ( ms.buffer.length >=  5  && ms.length == 5 );
													assertEquals( ms.toString(), "56789");
		ms= new MString( tSB, 5, 100);				assertTrue ( ms.buffer.length >=  5  && ms.length == 5 );
													assertEquals( ms.toString(), "56789");
		ms= new MString( tSB, -5);					assertTrue ( ms.buffer.length >=  10 && ms.length == 10 );
													assertEquals( ms.toString(), "0123456789");
		ms= new MString( tSB, -5, 10);				assertTrue ( ms.buffer.length >=  5  && ms.length == 5 );
													assertEquals( ms.toString(), "01234");
		ms= new MString( tSB, -5, 100);				assertTrue ( ms.buffer.length >=  10  && ms.length == 10 );
													assertEquals( ms.toString(), "0123456789");

	}


	@SuppressWarnings("static-method")
	@Test 
	public void MString_Conversion()
	{
		MString   ms;
		String			s;
		ms= new MString("0123456789");
		s= ms.toString();					assertTrue ( s.equals("0123456789") ); 
		s= ms.toString( 5);					assertTrue ( s.equals("56789") ); 
		s= ms.toString( 5, 100);			assertTrue ( s.equals("56789") ); 
		s= ms.toString( -5);				assertTrue ( s.equals("0123456789") ); 
		s= ms.toString( -5, 10);			assertTrue ( s.equals("01234") ); 
		s= ms.toString( -5, 100);			assertTrue ( s.equals("0123456789") ); 

		s= ms.toString( 0,  0);				assertTrue ( s.equals("") ); 
		s= ms.toString( 5,  0);				assertTrue ( s.equals("") ); 
		s= ms.toString( 20, 0);				assertTrue ( s.equals("") ); 
		s= ms.toString( 0,  -1);			assertTrue ( s.equals("") ); 
		s= ms.toString( 5,  -5);			assertTrue ( s.equals("") ); 
		s= ms.toString( 5,  -100);			assertTrue ( s.equals("") ); 
		s= ms.toString( 20,  -1);			assertTrue ( s.equals("") ); 
		s= ms.toString( 20,  20);			assertTrue ( s.equals("") ); 
		s= ms.toString( 20,  -100);			assertTrue ( s.equals("") ); 
		s= ms.toString( 20, 0);				assertTrue ( s.equals("") ); 
		s= ms.toString( 20, 100);			assertTrue ( s.equals("") ); 
	}

	@SuppressWarnings("static-method")
	@Test 
	public void MString_Append()
	{
		// append strings
		{
			// create mutable string
			MString ms=	new MString(5);
			assertTrue( ms.length == 0 );

			// append constant string
			{
				String  t=	"Hallo World";
				ms=	new MString(5);
				ms.append(t);

				assertTrue( ms.length == t.length());
				for ( int i= 0; i < t.length() ; i++ )
					assertEquals( ms.buffer[i],  t.charAt( i ));
			}

			// append part of constant string
			{
				String  t=			"Hallo World";
				int		startIdx=	6;
				int		len=		3;
				ms=	new MString(5);
				ms.append( t, startIdx, len );

				assertTrue( ms.length == len);
				for ( int i= 0; i < len ; i++ )
					assertEquals( ms.buffer[i],  t.charAt( startIdx + i) );
			}

			// append more than available in source string
			{
				String  t=			"Hallo World";
				int		startIdx=	6;
				int		len=		3;
				ms=	new MString(5);
				ms.append(t);
				ms.append ( t, startIdx, t.length() );
				len= t.length() - startIdx;

				assertTrue( ms.length == t.length() + len );
				for ( int i= 0; i < len ; i++ )
					assertEquals( ms.buffer[t.length() + i],  t.charAt( startIdx + i) );
			}

			// append int
			{
				ms= new MString();
				int ui;
				int  i;
		
				ms.clear(); ui= 0;	 	ms.append( ui ); 	assertEquals(      "0", ms.toString());
				ms.clear(); ui= 0;	 	ms.append( ui, 1 ); assertEquals(      "0", ms.toString());
				ms.clear(); ui= 0;	 	ms.append( ui, 3 ); assertEquals(    "000", ms.toString());
				ms.clear(); ui= 10;	 	ms.append( ui ); 	assertEquals(     "10", ms.toString());
				ms.clear(); ui= 100; 	ms.append( ui, 1 ); assertEquals(    "100", ms.toString());
				ms.clear(); ui= 100; 	ms.append( ui, 3 ); assertEquals(    "100", ms.toString());
				ms.clear(); ui= 100; 	ms.append( ui, 4 ); assertEquals(   "0100", ms.toString());
				ms.clear(); ui= 23; 	ms.append( ui ); 	assertEquals(     "23", ms.toString());
				ms.clear(); ui= 99; 	ms.append( ui, 5 ); assertEquals(  "00099", ms.toString());
				ms.clear(); i= 49; 		ms.append( i  ); 	assertEquals(     "49", ms.toString());
				ms.clear(); i= -5; 		ms.append( i, 5 ); 	assertEquals( "-00005", ms.toString());
				ms.clear(); i= -5324;	ms.append( i, 2 ); 	assertEquals(  "-5324", ms.toString());

				i= Integer.MAX_VALUE;
				int iLen= ( "" + i ).length();
				ms= new MString( iLen -1 ); 	ms.append( i ); 	assertEquals("" + i, ms.toString()); assertTrue( ms.buffer.length >= iLen );
				ms= new MString( iLen    ); 	ms.append( i ); 	assertEquals("" + i, ms.toString()); assertTrue( ms.buffer.length >= iLen + 1);
				ms= new MString( iLen +1 ); 	ms.append( i ); 	assertEquals("" + i, ms.toString()); assertTrue( ms.buffer.length == iLen + 1 );
				
				ui= Integer.MIN_VALUE;
				iLen= ( "" + i ).length();
				ms= new MString( iLen -1 ); 	ms.append( i ); 	assertEquals("" + i, ms.toString()); assertTrue( ms.buffer.length >= iLen );
				ms= new MString( iLen    ); 	ms.append( i ); 	assertEquals("" + i, ms.toString()); assertTrue( ms.buffer.length >= iLen );
				ms= new MString( iLen +1 ); 	ms.append( i ); 	assertEquals("" + i, ms.toString()); assertTrue( ms.buffer.length == iLen + 1 );
			}

			// append double
			{
				ms= new MString();
				double d;
		
				ms.clear(); d= 0d;	 	ms.append( d, 0,0 ); 	assertEquals(     "0.", ms.toString());
				ms.clear(); d= 0d;	 	ms.append( d, 1,1 );	assertEquals(    "0.0", ms.toString());
				ms.clear(); d= 0d;	 	ms.append( d, 2,2 ); 	assertEquals(  "00.00", ms.toString());
				ms.clear(); d= 10d;	 	ms.append( d, 2,2 ); 	assertEquals(  "10.00", ms.toString());
				ms.clear(); d= 23.37d; 	ms.append( d, 2,1 ); 	assertEquals(   "23.4", ms.toString());
				ms.clear(); d= 23.37d; 	ms.append( d, 2,3 ); 	assertEquals( "23.370", ms.toString());
				ms.clear(); d= 12.345d; ms.append( d, 0,3 );	assertEquals( "12.345", ms.toString());
				ms.clear(); d= -5.1d; 	ms.append( d, 5,0 ); 	assertEquals("-00005.", ms.toString());
				ms.clear(); d= -5.1d; 	ms.append( d, 5,1 ); 	assertEquals("-00005.1", ms.toString());
				ms.clear(); d= -53.24d;	ms.append( d, 2,2 ); 	assertEquals( "-53.24", ms.toString());
				ms.clear(); d= -0.2d;	ms.append( d, 1,3 ); 	assertEquals( "-0.200", ms.toString());
				ms.clear(); d= -0.6d;	ms.append( d, 1,3 ); 	assertEquals( "-0.600", ms.toString());
				ms.clear(); d= -0.999d;	ms.append( d, 1,3 ); 	assertEquals( "-0.999", ms.toString());
				ms.clear(); d=  0.999d;	ms.append( d, 1,3 ); 	assertEquals(  "0.999", ms.toString());
				ms.clear(); d=  0.99;	ms.append( d, 1,3 ); 	assertEquals(  "0.990", ms.toString());
				ms.clear(); d=  0.999;	ms.append( d, 1,3 ); 	assertEquals(  "0.999", ms.toString());
				ms.clear(); d=  0.9999;	ms.append( d, 1,3 ); 	assertEquals(  "1.000", ms.toString());
				ms.clear(); d=  0.99999;ms.append( d, 1,3 ); 	assertEquals(  "1.000", ms.toString());
				
				d= -3.0d;
				double end= 3.0d;
				double inc= 0.001d;
				int	digits= 5;
				while ( d <= end)
				{
					ms.clear();
					ms.append( d, 0, digits );
					double dRes= Double.parseDouble( ms.toString() );
					assertEquals( d, dRes, 0.00000001d );
					d+= inc;
				} 
			}

			// Tabs
			{
				ms= new MString();
		
				ms.clear();									ms.tab( 5 ); ms.append( "#" );			assertEquals( ms.toString(), "     #"			);
				ms.clear(); ms.append( "123" );				ms.tab( 5 ); ms.append( "#" );			assertEquals( ms.toString(), "123  #"			);
				ms.clear(); ms.append( "1234" );			ms.tab( 5 ); ms.append( "#" );			assertEquals( ms.toString(), "1234 #"			);
				ms.clear(); ms.append( "12345" );			ms.tab( 5 ); ms.append( "#" );			assertEquals( ms.toString(), "12345     #"		);
				ms.clear(); ms.append( "123456789" );		ms.tab( 5 ); ms.append( "#" );			assertEquals( ms.toString(), "123456789 #"		);
				ms.clear(); ms.append( "1234567890" );		ms.tab( 5 ); ms.append( "#" );			assertEquals( ms.toString(), "1234567890     #"	);

				ms.clear(); ms.append( "REF:123" );			ms.tab( 5, 4 ); ms.append( "#" );		assertEquals( ms.toString(), "REF:123  #"			);
				ms.clear(); ms.append( "REF:1234" );		ms.tab( 5, 4 ); ms.append( "#" );		assertEquals( ms.toString(), "REF:1234 #"			);
				ms.clear(); ms.append( "REF:12345" );		ms.tab( 5, 4 ); ms.append( "#" );		assertEquals( ms.toString(), "REF:12345     #"		);
				ms.clear(); ms.append( "REF:123456789" );	ms.tab( 5, 4 ); ms.append( "#" );		assertEquals( ms.toString(), "REF:123456789 #"		);
				ms.clear(); ms.append( "REF:1234567890" );	ms.tab( 5, 4 ); ms.append( "#" );		assertEquals( ms.toString(), "REF:1234567890     #"	);
			}
		}

		// append mutable strings
		{
			// create mutable string
			MString ms=	new MString();
			assertTrue( ms.length == 0 );

			// append constant string
			MString t=	new MString();
			t.append( "Hallo World" );
			ms.append(t);

			assertTrue( ms.length == t.length );
			for ( int i= 0; i < t.length ; i++ )
				assertEquals( ms.buffer[i],  t.buffer[i] );

			// append part of constant string
			int startIdx= 6;
			int len=	  3;
			ms.append( t, startIdx, len );

			assertTrue( ms.length == t.length + len);
			for ( int i= 0; i < len ; i++ )
				assertEquals( ms.buffer[t.length + i],  t.buffer[ startIdx + i]);

			// append more than available in source string
			ms=	new MString(5);
			ms.append(t);
			ms.append ( t, startIdx, t.length );
			len= t.length - startIdx;

			assertTrue( ms.length == t.length + len);
			for ( int i= 0; i < len ; i++ )
				assertEquals( ms.buffer[t.length + i],  t.buffer[ startIdx + i]);
		}

		// append String Builders
		{
			// create mutable string
			MString ms=	new MString();
			assertTrue( ms.length == 0 );

			// append constant string
			StringBuffer t=	new StringBuffer();
			t.append( "Hallo World" );
			ms.append(t);

			assertTrue( ms.length == t.length());
			for ( int i= 0; i < t.length() ; i++ )
				assertEquals( ms.buffer[i],  t.charAt( i ) );

			// append part of constant string
			int startIdx= 6;
			int len=	  3;
			ms.append( t, startIdx, len );

			assertTrue( ms.length == t.length() + len );
			for ( int i= 0; i < len ; i++ )
				assertEquals( ms.buffer[t.length() + i],  t.charAt( startIdx + i) );

			// append more than available in source string
			ms=	new MString(5);
			ms.append(t);
			ms.append ( t, startIdx, t.length() );
			len= t.length() - startIdx;

			assertTrue( ms.length == t.length() + len );
			for ( int i= 0; i < len ; i++ )
				assertEquals( ms.buffer[t.length() + i],  t.charAt( startIdx + i) );
		}

	}

	@SuppressWarnings("static-method")
	@Test 
	public void MString_Capacity()
	{
		MString ms= new MString( 5 );
		ms.append( 'a' );		assertTrue ( ms.buffer.length == 5 );
		ms.append( 'b' );		assertTrue ( ms.buffer.length == 5 );
		ms.append( 'c' );		assertTrue ( ms.buffer.length == 5 );
		ms.append( 'd' );		assertTrue ( ms.buffer.length == 5 );
		ms.append( 'e' );		assertTrue ( ms.buffer.length == 5 );
		ms.append( 'x' );		
		assertTrue ( ms.buffer.length >= 6 );
		assertEquals( "abcdex", ms.toString() );
		
		ms.ensureCapacity( 2000 ); assertTrue ( ms.buffer.length >= 2000 );
	}

	@SuppressWarnings("static-method")
	@Test 
	public void MString_AppendWithPadding()
	{
		MString ms= new MString();
		
		// append pad null objects
		ms.appendPadRight	( (String)		  null,	3, '#' );	assertEquals( ms.toString(), "###"		   );
		ms.appendPadCenter	( (String)		  null,	4, '*' );	assertEquals( ms.toString(), "###****"	   );
		ms.appendPadLeft	( (String)		  null,	5, '+' );	assertEquals( ms.toString(), "###****+++++" );

		ms.clear();
		ms.appendPadRight	( (MString) null,	3, '#' );	assertEquals( ms.toString(), "###"		   );
		ms.appendPadCenter	( (MString) null,	4, '*' );	assertEquals( ms.toString(), "###****"	   );
		ms.appendPadLeft	( (MString) null,	5, '+' );	assertEquals( ms.toString(), "###****+++++" );

		ms.clear();
		ms.appendPadRight	( (StringBuffer) null,	3, '#' );	assertEquals( ms.toString(), "###"		   );
		ms.appendPadCenter	( (StringBuffer) null,	4, '*' );	assertEquals( ms.toString(), "###****"	   );
		ms.appendPadLeft	( (StringBuffer) null,	5, '+' );	assertEquals( ms.toString(), "###****+++++" );

		// append pad String objects
		ms.clear();
		ms.appendPadRight( "A",		5 );
		ms.appendPadRight( "AB",	5 );
		ms.appendPadRight( "ABC",	5 );
		ms.appendPadRight( "ABCD",	5 );
		ms.appendPadRight( "ABCDE",	5 );
		ms.appendPadRight( "ABCDEF",5 );
		ms.appendPadRight( "ABCDEFG",5 );
		assertEquals( ms.toString(), "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG" );

		ms.clear();
		ms.appendPadLeft( "A",		5 );
		ms.appendPadLeft( "AB",		5 );
		ms.appendPadLeft( "ABC",	5 );
		ms.appendPadLeft( "ABCD",	5 );
		ms.appendPadLeft( "ABCDE",	5 );
		ms.appendPadLeft( "ABCDEF",	5 );
		ms.appendPadLeft( "ABCDEFG",5 );
		assertEquals( ms.toString(), "    A   AB  ABC ABCDABCDEABCDEFABCDEFG" );

		ms.clear();
		ms.appendPadCenter( "A", 5 );
		ms.appendPadCenter( "AB", 5 );
		ms.appendPadCenter( "ABC", 5 );
		ms.appendPadCenter( "ABCD", 5 );
		ms.appendPadCenter( "ABCDE", 5 );
		ms.appendPadCenter( "ABCDEF", 5 );
		ms.appendPadCenter( "ABCDEFG", 5 );	   
		assertEquals( ms.toString(), "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG" );
		
		// append pad MString objects
		MString ms2= new MString();
		ms.clear();
		ms2.clear().append( "A"			);	ms.appendPadRight( ms2,		5 );
		ms2.clear().append( "AB"		);	ms.appendPadRight( ms2,		5 );
		ms2.clear().append( "ABC"		);	ms.appendPadRight( ms2,		5 );
		ms2.clear().append( "ABCD"		);	ms.appendPadRight( ms2,		5 );
		ms2.clear().append( "ABCDE"		);	ms.appendPadRight( ms2,		5 );
		ms2.clear().append( "ABCDEF"	);	ms.appendPadRight( ms2,		5 );
		ms2.clear().append( "ABCDEFG"	);	ms.appendPadRight( ms2,		5 );
		assertEquals( ms.toString(), "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG" );

		ms.clear();	ms2.clear();
		ms2.clear().append( "A"			);	ms.appendPadLeft( ms2,		5 );
		ms2.clear().append( "AB"		);	ms.appendPadLeft( ms2,		5 );
		ms2.clear().append( "ABC"		);	ms.appendPadLeft( ms2,		5 );
		ms2.clear().append( "ABCD"		);	ms.appendPadLeft( ms2,		5 );
		ms2.clear().append( "ABCDE"		);	ms.appendPadLeft( ms2,		5 );
		ms2.clear().append( "ABCDEF"	);	ms.appendPadLeft( ms2,		5 );
		ms2.clear().append( "ABCDEFG"	);	ms.appendPadLeft( ms2,		5 );
		assertEquals( ms.toString(), "    A   AB  ABC ABCDABCDEABCDEFABCDEFG" );

		ms.clear();	ms2.clear();
		ms2.clear().append( "A"			);	ms.appendPadCenter( ms2,	5 );
		ms2.clear().append( "AB"		);	ms.appendPadCenter( ms2,	5 );
		ms2.clear().append( "ABC"		);	ms.appendPadCenter( ms2,	5 );
		ms2.clear().append( "ABCD"		);	ms.appendPadCenter( ms2,	5 );
		ms2.clear().append( "ABCDE"		);	ms.appendPadCenter( ms2,	5 );
		ms2.clear().append( "ABCDEF"	);	ms.appendPadCenter( ms2,	5 );
		ms2.clear().append( "ABCDEFG"	);	ms.appendPadCenter( ms2,	5 );
		assertEquals( ms.toString(), "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG" );

		// append pad StringBuffer objects
		StringBuffer sb= new StringBuffer();
		ms.clear();
		sb.setLength( 0 ); sb.append( "A"			);	ms.appendPadRight( sb,		5 );
		sb.setLength( 0 ); sb.append( "AB"			);	ms.appendPadRight( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABC"			);	ms.appendPadRight( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCD"		);	ms.appendPadRight( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCDE"		);	ms.appendPadRight( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCDEF"		);	ms.appendPadRight( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCDEFG"		);	ms.appendPadRight( sb,		5 );
		assertEquals( ms.toString(), "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG" );

		ms.clear();	
		sb.setLength( 0 ); sb.append( "A"			);	ms.appendPadLeft( sb,		5 );
		sb.setLength( 0 ); sb.append( "AB"			);	ms.appendPadLeft( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABC"			);	ms.appendPadLeft( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCD"		);	ms.appendPadLeft( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCDE"		);	ms.appendPadLeft( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCDEF"		);	ms.appendPadLeft( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCDEFG"		);	ms.appendPadLeft( sb,		5 );
		assertEquals( ms.toString(), "    A   AB  ABC ABCDABCDEABCDEFABCDEFG" );

		ms.clear();	
		sb.setLength( 0 ); sb.append( "A"			);	ms.appendPadCenter( sb,		5 );
		sb.setLength( 0 ); sb.append( "AB"			);	ms.appendPadCenter( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABC"			);	ms.appendPadCenter( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCD"		);	ms.appendPadCenter( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCDE"		);	ms.appendPadCenter( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCDEF"		);	ms.appendPadCenter( sb,		5 );
		sb.setLength( 0 ); sb.append( "ABCDEFG"		);	ms.appendPadCenter( sb,		5 );
		assertEquals( ms.toString(), "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG" );
		
	}



	@SuppressWarnings("static-method")
	@Test 
	public void MString_Tabs()
	{
		MString ms= new MString();
		int result;

		// search
		ms.append("abcd abcd");
		result= ms.indexOf( "abcd"	  );			assertTrue( result == 0 );
		result= ms.indexOf( "b"		  );			assertTrue( result == 1 );
		result= ms.indexOf( " abcd"	  );			assertTrue( result == 4 );
		result= ms.indexOf( "abcd", 1 );			assertTrue( result == 5 );
		
		// replace
		ms.clear();
		ms.append("Hello W!");
		result= ms.replace( "W!",	"world!"  );	assertEquals( ms.toString(), "Hello world!" );		assertEquals( 1, result );
		result= ms.replace( " ",	"* *"	  );	assertEquals( ms.toString(), "Hello* *world!" );		assertEquals( 1, result );
		result= ms.replace( "*",	"#", 0, 1 );	assertEquals( ms.toString(), "Hello# *world!" );		assertEquals( 1, result );
		result= ms.replace( "*",	"#"		  );	assertEquals( ms.toString(), "Hello# #world!" );		assertEquals( 1, result );
		result= ms.replace( "#",	"$$$"	  );	assertEquals( ms.toString(), "Hello$$$ $$$world!" );	assertEquals( 2, result );
		result= ms.replace( "$$$",	"*"		  );	assertEquals( ms.toString(), "Hello* *world!" );		assertEquals( 2, result );
		result= ms.replace( "*",	""		  );	assertEquals( ms.toString(), "Hello world!" );		assertEquals( 2, result );
	}


	@SuppressWarnings("static-method")
	@Test 
	public void MString_SearchAndReplace()
	{
		MString ms= new MString();
		int result;

		// search
		ms.append("abcd abcd");
		result= ms.indexOf( "abcd"	  );			assertTrue( result == 0 );
		result= ms.indexOf( "b"		  );			assertTrue( result == 1 );
		result= ms.indexOf( " abcd"	  );			assertTrue( result == 4 );
		result= ms.indexOf( "abcd", 1 );			assertTrue( result == 5 );
		
		// replace
		ms.clear();
		ms.append("Hello W!");
		result= ms.replace( "W!",	"world!"  );	assertEquals( ms.toString(), "Hello world!" );		assertEquals( 1, result );
		result= ms.replace( " ",	"* *"	  );	assertEquals( ms.toString(), "Hello* *world!" );		assertEquals( 1, result );
		result= ms.replace( "*",	"#", 0, 1 );	assertEquals( ms.toString(), "Hello# *world!" );		assertEquals( 1, result );
		result= ms.replace( "*",	"#"		  );	assertEquals( ms.toString(), "Hello# #world!" );		assertEquals( 1, result );
		result= ms.replace( "#",	"$$$"	  );	assertEquals( ms.toString(), "Hello$$$ $$$world!" );	assertEquals( 2, result );
		result= ms.replace( "$$$",	"*"		  );	assertEquals( ms.toString(), "Hello* *world!" );		assertEquals( 2, result );
		result= ms.replace( "*",	""		  );	assertEquals( ms.toString(), "Hello world!" );		assertEquals( 2, result );
		
		// search in normal strings ignore case (static util methods)
		String s= "Hallo A-Worx util";
		result= MString.indexOfIgnoreCase( s, "a-worx" 		); assertTrue( result == 6 );
		result= MString.indexOfIgnoreCase( s, "a-worx", 1	); assertTrue( result == 6 );
		result= MString.indexOfIgnoreCase( s, "a-worx", -10	); assertTrue( result == 6 );
		result= MString.indexOfIgnoreCase( s, "a-worx", 6	); assertTrue( result == 6 );
		result= MString.indexOfIgnoreCase( s, "a-worx", 7	); assertTrue( result == -1 );
		result= MString.indexOfIgnoreCase( s, "a-worx", 100	); assertTrue( result == -1 );
		result= MString.indexOfIgnoreCase( s, "hal",	0	); assertTrue( result ==  0 );
		result= MString.indexOfIgnoreCase( s, "hal",	1	); assertTrue( result == -1 );
		result= MString.indexOfIgnoreCase( s, "util",	1	); assertTrue( result == 13 );
		result= MString.indexOfIgnoreCase( s, "UTIL",	5	); assertTrue( result == 13 );
		result= MString.indexOfIgnoreCase( s, "UTIL",	13	); assertTrue( result == 13 );
		result= MString.indexOfIgnoreCase( s, "UTIL",	14	); assertTrue( result == -1 );
		
		assertTrue( MString.startsWithIgnoreCase( s, s) == true );
		assertTrue( MString.endsWithIgnoreCase  ( s, s) == true  );
		assertTrue( MString.startsWithIgnoreCase( s, s + "x") == false );
		assertTrue( MString.endsWithIgnoreCase  ( s, "x" +s ) == false );
		assertTrue( MString.startsWithIgnoreCase( s, "haLLO") == true );
		assertTrue( MString.startsWithIgnoreCase( s, "HaLLO") == true );
		assertTrue( MString.endsWithIgnoreCase  ( s, "haLLO") == false  );
		assertTrue( MString.startsWithIgnoreCase( s, "UTIL") == false );
		assertTrue( MString.endsWithIgnoreCase  ( s, "UTIL") == true  );
		assertTrue( MString.endsWithIgnoreCase  ( s, "utIl") == true  );
	}

	@SuppressWarnings("static-method")
	@Test 
	public void MString_Compare()
	{
		MString ms= new MString();
		int result;

		String t= "abcde";
		ms.append( t );
		result= ms.compareTo( t	  );							assertEquals( t.compareTo( t ),								result );
		result= ms.compareTo( t + "x"	  );					assertEquals( t.compareTo( t + "x" ),						result );
		result= ms.compareTo( t.substring (0, t.length() -1 )  );	assertEquals( t.compareTo( t.substring (0, t.length() -1 ) ),	result );
		result= ms.compareTo( "pad" + t,  false, 3	  );		assertEquals( 0,												result );
		result= ms.compareTo( "pad" + t,  false, 3, 2  );		assertEquals( 1,												result );
		result= ms.compareTo( "pad" + t,  false, 3, 100, 0, 4 );assertEquals( -1,											result );
		result= ms.compareTo( "pad" + t,  false, 3, 100, 0, 5 );assertEquals( 0,												result );
		result= ms.compareTo( t, false, 2,2,   2,2	  );		assertEquals( 0,												result );
		result= ms.compareTo( t, false, 2,2,   2,1	  );		assertEquals( -1,											result );
		result= ms.compareTo( t, false, 2,2,   2,3	  );		assertEquals( 1, 											result );

		result= ms.compareTo( t, false, -2,5,   -2, 5 );							assertEquals( 0, 						result );
		result= ms.compareTo( t, false,  2, Integer.MAX_VALUE,    2, Integer.MAX_VALUE );		assertEquals( 0, 						result );
		result= ms.compareTo( t, false, -2, Integer.MAX_VALUE,   -2, Integer.MAX_VALUE );		assertEquals( 0, 						result );
		result= ms.compareTo( t, false, -2, 100,			-2, 99 );				assertEquals( 0, 						result );
		result= ms.compareTo( t, false, -2, 5,				-2, Integer.MAX_VALUE );		assertEquals( 1, 						result );
		result= ms.compareTo( t, false, -2, Integer.MAX_VALUE,	-2, 5 );				assertEquals( -1, 						result );

		// greater/smaller strings
		String greater=	 "x";
		String greater2= "abcdef";
		String smaller=  "aaa";
		String smaller2= "abcd";
		result= ms.compareTo( greater  );						assertEquals( t.compareTo( greater  ),						result );
		result= ms.compareTo( greater2 );						assertEquals( t.compareTo( greater2 ),						result );
		result= ms.compareTo( smaller  );						assertEquals( t.compareTo( smaller ),						result );
		result= ms.compareTo( smaller2 );						assertEquals( t.compareTo( smaller2 ),						result );

		// ignore case
		String ut= t.toUpperCase();
		result= ms.compareTo( ut );								assertEquals( t.compareTo(ut),								result );
		result= ms.compareTo( ut, false );						assertEquals( t.compareTo(ut),								result );
		result= ms.compareTo( ut, true );						assertEquals( 0,											result );
		result= ms.compareTo( ut, false, 2,2,   2,2	  );		assertEquals( "cd".compareTo("CD"),							result );
		result= ms.compareTo( ut, true,  2,2,   2,2	  );		assertEquals( 0,											result );


		// we do just a very little testing with StringBuffer and MString parameter version of this function, as
		// the code differences are very small
		StringBuffer tSB= new StringBuffer(); tSB.append( t );
		result= ms.compareTo( tSB	  );							assertEquals( 0,										result );
		result= ms.compareTo( tSB, false, -5, 100, -10, 100	  );	assertEquals( 0,										result );
		result= ms.compareTo( tSB, false,  2,   3,   2,   3	  );	assertEquals( 0,										result );
		
		MString tMS= new MString(); tMS.append( t );
		result= ms.compareTo( tMS	  );							assertEquals( 0,										result );
		result= ms.compareTo( tMS, false, -5, 100, -10, 100	  );	assertEquals( 0,											result );
		result= ms.compareTo( tMS, false,  2,   3,   2,   3	  );	assertEquals( 0,											result );
		
		// different ranges
		String r1=   "*ABCDEF*";
		String r2= "##*ABCDEF*##";
		ms.clear().append( r1 );
		result= ms.compareTo( r2, false, 2,8		  );		assertEquals( 0,												result );
		result= ms.compareTo( r2, false, 3,6,   1,6	  );		assertEquals( 0,												result );
		
		// startsWith/Endswith/ContainsAt
		String sub1=  "ABC";
		String sub2=  "abc";
		String s1= "ABCDEF";
		String s2= "123ABC";
		String s3= "##12ABC21##";
		String s4= "AB";
		boolean bRes;
		ms.clear().append( s1 );	bRes= ms.startsWith( sub1 );  			assertEquals( true,		bRes );
									bRes= ms.startsWith( sub2 );  			assertEquals( false,	bRes );
		ms.clear().append( s2 );	bRes= ms.endsWith  ( sub1 );  			assertEquals( true,		bRes );
									bRes= ms.endsWith  ( sub2 );  			assertEquals( false,	bRes );
		ms.clear().append( s3 );	bRes= ms.containsAt( sub1, 4 );			assertEquals( true,		bRes );
									bRes= ms.containsAt( sub2, 4 );			assertEquals( false,	bRes );
									bRes= ms.containsAt( sub2, 4, true );	assertEquals( true,		bRes );
		ms.clear().append( s4 );	bRes= ms.containsAt( sub1, 4 );			assertEquals( false,	bRes );
									bRes= ms.containsAt( sub2, 4 );			assertEquals( false,	bRes );
		ms.clear().append( s4 );	bRes= ms.containsAt( sub1, 0 );			assertEquals( false,	bRes );
									bRes= ms.containsAt( sub2, 0, true );	assertEquals( false,	bRes );
	}

	@SuppressWarnings("static-method")
	@Test 
	public void MString_ConvertCase()
	{
		MString ms= new MString();
		String t;
		
		// test substring conversion
		t= "AAAbbb";
		ms.clear().append( t ).convertCase( false,  0, 2 );		assertTrue( ms.toString().equals( "aaAbbb" ) );
		ms.clear().append( t ).convertCase( false, -2, 3 );		assertTrue( ms.toString().equals( "aAAbbb" ) );
		ms.clear().append( t ).convertCase( false, -2    );		assertTrue( ms.toString().equals( "aaabbb" ) );

		ms.clear().append( t ).convertCase( true,  3,  2 );		assertTrue( ms.toString().equals( "AAABBb" ) );
		ms.clear().append( t ).convertCase( true, -2,  6 );		assertTrue( ms.toString().equals( "AAABbb" ) );
		ms.clear().append( t ).convertCase( true, -2     );		assertTrue( ms.toString().equals( "AAABBB" ) );
	}

}
