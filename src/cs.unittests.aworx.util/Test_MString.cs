using System;
using System.Globalization;
#if MONO_DEVELOP
	using NUnit.Framework;
#else
	using Microsoft.VisualStudio.TestTools.UnitTesting;
#endif

using System.Text;
using com.aworx.util;

namespace com.aworx.util.unittests
{
	#if MONO_DEVELOP
		[TestFixture ()]
	#else
		[TestClass]
	#endif
	public class TestsMString
	{
		#if MONO_DEVELOP
		[Test ()]
		#else
		[TestMethod]
		#if !WINDOWS_PHONE
		[TestCategory("MString")]
		#endif
		#endif
		public void MString_Constructors()
		{
			MString ms;
			ms= new MString( );		Assert.IsTrue ( ms.Buffer.Length > 0    && ms.Length == 0 );
			ms= new MString(25);		Assert.IsTrue ( ms.Buffer.Length ==  25 && ms.Length == 0 );
			ms= new MString("Test");	Assert.IsTrue ( ms.Buffer.Length >=  4  && ms.Length == 4 );

			MString tMSEmpty= new MString ( );
			ms= new MString( (MString) null );	Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tMSEmpty );				Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tMSEmpty, 1,     0 );	Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tMSEmpty, -1000, 0 );	Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tMSEmpty, -1000, 1 );	Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tMSEmpty, -100,  1000);	Assert.IsTrue ( ms.Length == 0 );

			MString tMS=		new MString ( "0123456789" );
			ms= new MString( tMS );					Assert.IsTrue ( ms.Buffer.Length >=  10 && ms.Length == 10 );
															Assert.AreEqual( ms.ToString(), "0123456789");
			ms= new MString( tMS, 5);					Assert.IsTrue ( ms.Buffer.Length >=  5  && ms.Length == 5 );
															Assert.AreEqual( ms.ToString(), "56789");
			ms= new MString( tMS, 5, 100);			Assert.IsTrue ( ms.Buffer.Length >=  5  && ms.Length == 5 );
															Assert.AreEqual( ms.ToString(), "56789");
			ms= new MString( tMS, -5);				Assert.IsTrue ( ms.Buffer.Length >=  10 && ms.Length == 10 );
															Assert.AreEqual( ms.ToString(), "0123456789");
			ms= new MString( tMS, -5, 10);			Assert.IsTrue ( ms.Buffer.Length >=  5  && ms.Length == 5 );
															Assert.AreEqual( ms.ToString(), "01234");
			ms= new MString( tMS, -5, 100);			Assert.IsTrue ( ms.Buffer.Length >=  10  && ms.Length == 10 );
															Assert.AreEqual( ms.ToString(), "0123456789");

			String tS= "0123456789";
			ms= new MString( (String) null );			Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( "" );					Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( "", 1,     0 );			Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( "", -1000, 0 );			Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( "", -1000, 1 );			Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( "", -100,  1000);		Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tS );					Assert.IsTrue ( ms.Buffer.Length >=  10 && ms.Length == 10 );
															Assert.AreEqual( ms.ToString(), "0123456789");
			ms= new MString( tS, 5);					Assert.IsTrue ( ms.Buffer.Length >=  5  && ms.Length == 5 );
															Assert.AreEqual( ms.ToString(), "56789");
			ms= new MString( tS, 5, 100);				Assert.IsTrue ( ms.Buffer.Length >=  5  && ms.Length == 5 );
															Assert.AreEqual( ms.ToString(), "56789");
			ms= new MString( tS, -5);					Assert.IsTrue ( ms.Buffer.Length >=  10 && ms.Length == 10 );
															Assert.AreEqual( ms.ToString(), "0123456789");
			ms= new MString( tS, -5, 10);				Assert.IsTrue ( ms.Buffer.Length >=  5  && ms.Length == 5 );
															Assert.AreEqual( ms.ToString(), "01234");
			ms= new MString( tS, -5, 100);			Assert.IsTrue ( ms.Buffer.Length >=  10  && ms.Length == 10 );
															Assert.AreEqual( ms.ToString(), "0123456789");


			StringBuilder tSBEmpty= new StringBuilder ( );
			ms= new MString( (StringBuilder) null );	Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tSBEmpty );				Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tSBEmpty, 1,     0 );	Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tSBEmpty, -1000, 0 );	Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tSBEmpty, -1000, 1 );	Assert.IsTrue ( ms.Length == 0 );
			ms= new MString( tSBEmpty, -100,  1000);	Assert.IsTrue ( ms.Length == 0 );

			StringBuilder tSB= new StringBuilder ( "0123456789" );
			ms= new MString( tSB );					Assert.IsTrue ( ms.Buffer.Length >=  10 && ms.Length == 10 );
															Assert.AreEqual( ms.ToString(), "0123456789");
			ms= new MString( tSB, 5);					Assert.IsTrue ( ms.Buffer.Length >=  5  && ms.Length == 5 );
															Assert.AreEqual( ms.ToString(), "56789");
			ms= new MString( tSB, 5, 100);			Assert.IsTrue ( ms.Buffer.Length >=  5  && ms.Length == 5 );
															Assert.AreEqual( ms.ToString(), "56789");
			ms= new MString( tSB, -5);				Assert.IsTrue ( ms.Buffer.Length >=  10 && ms.Length == 10 );
															Assert.AreEqual( ms.ToString(), "0123456789");
			ms= new MString( tSB, -5, 10);			Assert.IsTrue ( ms.Buffer.Length >=  5  && ms.Length == 5 );
															Assert.AreEqual( ms.ToString(), "01234");
			ms= new MString( tSB, -5, 100);			Assert.IsTrue ( ms.Buffer.Length >=  10  && ms.Length == 10 );
															Assert.AreEqual( ms.ToString(), "0123456789");
		}

		#if MONO_DEVELOP
		[Test ()]
		#else
		[TestMethod]
		#if !WINDOWS_PHONE
		[TestCategory("MString")]
		#endif
		#endif
		public void MString_Conversion()
		{
			MString   ms;
			String			s;
			ms= new MString("0123456789");
			s= ms.ToString();					Assert.IsTrue ( s.Equals("0123456789") ); 
			s= ms.ToString( 5);					Assert.IsTrue ( s.Equals("56789") ); 
			s= ms.ToString( 5, 100);			Assert.IsTrue ( s.Equals("56789") ); 
			s= ms.ToString( -5);				Assert.IsTrue ( s.Equals("0123456789") ); 
			s= ms.ToString( -5, 10);			Assert.IsTrue ( s.Equals("01234") ); 
			s= ms.ToString( -5, 100);			Assert.IsTrue ( s.Equals("0123456789") ); 

			s= ms.ToString( 0,  0);				Assert.IsTrue ( s.Equals("") ); 
			s= ms.ToString( 5,  0);				Assert.IsTrue ( s.Equals("") ); 
			s= ms.ToString( 20, 0);				Assert.IsTrue ( s.Equals("") ); 
			s= ms.ToString( 0,  -1);			Assert.IsTrue ( s.Equals("") ); 
			s= ms.ToString( 5,  -5);			Assert.IsTrue ( s.Equals("") ); 
			s= ms.ToString( 5,  -100);			Assert.IsTrue ( s.Equals("") ); 
			s= ms.ToString( 20,  -1);			Assert.IsTrue ( s.Equals("") ); 
			s= ms.ToString( 20,  20);			Assert.IsTrue ( s.Equals("") ); 
			s= ms.ToString( 20,  -100);			Assert.IsTrue ( s.Equals("") ); 
			s= ms.ToString( 20, 0);				Assert.IsTrue ( s.Equals("") ); 
			s= ms.ToString( 20, 100);			Assert.IsTrue ( s.Equals("") ); 
		}

		#if MONO_DEVELOP
		[Test ()]
		#else
		[TestMethod]
		#if !WINDOWS_PHONE
		[TestCategory("MString")]
		#endif
		#endif
		public void MString_Append()
		{
			// append strings
			{
				// create mutable string
				MString ms=	new MString(5);
				Assert.IsTrue( ms.Length == 0 );

				// append constant string
				{
					String  t=	"Hallo World";
					ms=	new MString(5);
					ms.Append(t);

					Assert.IsTrue( ms.Length == t.Length );
					for ( int i= 0; i < t.Length ; i++ )
						Assert.AreEqual( ms.Buffer[i],  t[i]);
				}

				// append part of constant string
				{
					String  t=			"Hallo World";
					int		startIdx=	6;
					int		len=		3;
					ms=	new MString(5);
					ms.Append( t, startIdx, len );

					Assert.IsTrue( ms.Length == len);
					for ( int i= 0; i < len ; i++ )
						Assert.AreEqual( ms.Buffer[i],  t[ startIdx + i] );
				}

				// append more than available in source string
				{
					String  t=			"Hallo World";
					int		startIdx=	6;
					int		len=		3;
					ms=	new MString(5);
					ms.Append(t);
					ms.Append ( t, startIdx, t.Length );
					len= t.Length - startIdx;

					Assert.IsTrue( ms.Length == t.Length + len );
					for ( int i= 0; i < len ; i++ )
						Assert.AreEqual( ms.Buffer[t.Length + i],  t[ startIdx + i]);
				}

				// append int
				{
					ms= new MString();
					uint ui;
					int  i;
			
					ms.Clear(); ui= 0;	 	ms.Append( ui ); 	Assert.AreEqual(      "0", ms.ToString());
					ms.Clear(); ui= 0;	 	ms.Append( ui, 1 ); Assert.AreEqual(      "0", ms.ToString());
					ms.Clear(); ui= 0;	 	ms.Append( ui, 3 ); Assert.AreEqual(    "000", ms.ToString());
					ms.Clear(); ui= 10;	 	ms.Append( ui ); 	Assert.AreEqual(     "10", ms.ToString());
					ms.Clear(); ui= 100; 	ms.Append( ui, 1 ); Assert.AreEqual(    "100", ms.ToString());
					ms.Clear(); ui= 100; 	ms.Append( ui, 3 ); Assert.AreEqual(    "100", ms.ToString());
					ms.Clear(); ui= 100; 	ms.Append( ui, 4 ); Assert.AreEqual(   "0100", ms.ToString());
					ms.Clear(); ui= 23; 	ms.Append( ui ); 	Assert.AreEqual(     "23", ms.ToString());
					ms.Clear(); ui= 99; 	ms.Append( ui, 5 ); Assert.AreEqual(  "00099", ms.ToString());
					ms.Clear(); i= 49; 		ms.Append( i  ); 	Assert.AreEqual(     "49", ms.ToString());
					ms.Clear(); i= -5; 		ms.Append( i, 5 ); 	Assert.AreEqual( "-00005", ms.ToString());
					ms.Clear(); i= -5324;	ms.Append( i, 2 ); 	Assert.AreEqual(  "-5324", ms.ToString());

					i= int.MaxValue;
					int iLen= ( "" + i ).Length;
					ms= new MString( iLen -1 ); 	ms.Append( i ); 	Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.Buffer.Length >= iLen );
					ms= new MString( iLen    ); 	ms.Append( i ); 	Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.Buffer.Length >= iLen );
					ms= new MString( iLen +1 ); 	ms.Append( i ); 	Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.Buffer.Length == iLen + 1 );

					i= int.MinValue;
					iLen= ( "" + i ).Length;
					ms= new MString( iLen -1 ); 	ms.Append( i ); 	Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.Buffer.Length >= iLen );
					ms= new MString( iLen    ); 	ms.Append( i ); 	Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.Buffer.Length >= iLen );
					ms= new MString( iLen +1 ); 	ms.Append( i ); 	Assert.AreEqual("" + i, ms.ToString()); Assert.IsTrue( ms.Buffer.Length == iLen + 1 );
				}

				// append double
				{
					ms= new MString();
					double d;
		
					ms.Clear(); d= 0d;	 	ms.Append( d, 0,0 ); 	Assert.AreEqual(     "0.", ms.ToString());
					ms.Clear(); d= 0d;	 	ms.Append( d, 1,1 );	Assert.AreEqual(    "0.0", ms.ToString());
					ms.Clear(); d= 0d;	 	ms.Append( d, 2,2 ); 	Assert.AreEqual(  "00.00", ms.ToString());
					ms.Clear(); d= 10d;	 	ms.Append( d, 2,2 ); 	Assert.AreEqual(  "10.00", ms.ToString());
					ms.Clear(); d= 23.37d; 	ms.Append( d, 2,1 ); 	Assert.AreEqual(   "23.4", ms.ToString());
					ms.Clear(); d= 23.37d; 	ms.Append( d, 2,3 ); 	Assert.AreEqual( "23.370", ms.ToString());
					ms.Clear(); d= 12.345d; ms.Append( d, 0,3 );	Assert.AreEqual( "12.345", ms.ToString());
					ms.Clear(); d= -5.1d; 	ms.Append( d, 5,0 ); 	Assert.AreEqual("-00005.", ms.ToString());
					ms.Clear(); d= -5.1d; 	ms.Append( d, 5,1 ); 	Assert.AreEqual("-00005.1",ms.ToString());
					ms.Clear(); d= -53.24d;	ms.Append( d, 2,2 ); 	Assert.AreEqual( "-53.24", ms.ToString());
					ms.Clear(); d= -0.2d;	ms.Append( d, 1,3 ); 	Assert.AreEqual( "-0.200", ms.ToString());
					ms.Clear(); d= -0.6d;	ms.Append( d, 1,3 ); 	Assert.AreEqual( "-0.600", ms.ToString());
					ms.Clear(); d= -0.999d;	ms.Append( d, 1,3 ); 	Assert.AreEqual( "-0.999", ms.ToString());
					ms.Clear(); d=  0.999d;	ms.Append( d, 1,3 ); 	Assert.AreEqual(  "0.999", ms.ToString());
					ms.Clear(); d=  0.99;	ms.Append( d, 1,3 ); 	Assert.AreEqual(  "0.990", ms.ToString());
					ms.Clear(); d=  0.999;	ms.Append( d, 1,3 ); 	Assert.AreEqual(  "0.999", ms.ToString());
					ms.Clear(); d=  0.9999;	ms.Append( d, 1,3 ); 	Assert.AreEqual(  "1.000", ms.ToString());
					ms.Clear(); d=  0.99999;ms.Append( d, 1,3 ); 	Assert.AreEqual(  "1.000", ms.ToString());
				
					d= -3.0d;
					double end= 3.0d;
					double inc= 0.001d;
					int	digits= 5;
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
				MString ms=	new MString();
				Assert.IsTrue( ms.Length == 0 );

				// append constant string
				MString t=	new MString();
				t.Append( "Hallo World" );
				ms.Append(t);

				Assert.IsTrue( ms.Length == t.Length);
				for ( int i= 0; i < t.Length ; i++ )
					Assert.AreEqual( ms.Buffer[i],  t.Buffer[i]);

				// append part of constant string
				int startIdx= 6;
				int len=	  3;
				ms.Append( t, startIdx, len );

				Assert.IsTrue( ms.Length == t.Length + len );
				for ( int i= 0; i < len ; i++ )
					Assert.AreEqual( ms.Buffer[t.Length + i],  t.Buffer[ startIdx + i]);

				// append more than available in source string
				ms=	new MString(5);
				ms.Append(t);
				ms.Append ( t, startIdx, t.Length );
				len= t.Length - startIdx;

				Assert.IsTrue( ms.Length == t.Length + len );
				for ( int i= 0; i < len ; i++ )
					Assert.AreEqual( ms.Buffer[t.Length + i],  t.Buffer[ startIdx + i] );
			}

			// append String Builders
			{
				// create mutable string
				MString ms=	new MString();
				Assert.IsTrue( ms.Length == 0 );

				// append constant string
				StringBuilder t=	new StringBuilder();
				t.Append( "Hallo World" );
				ms.Append(t);

				Assert.IsTrue( ms.Length == t.Length);
				for ( int i= 0; i < t.Length ; i++ )
					Assert.AreEqual( ms.Buffer[i],  t[i]);

				// append part of constant string
				int startIdx= 6;
				int len=	  3;
				ms.Append( t, startIdx, len );

				Assert.IsTrue( ms.Length == t.Length + len );
				for ( int i= 0; i < len ; i++ )
					Assert.AreEqual( ms.Buffer[t.Length + i],  t[ startIdx + i] );

				// append more than available in source string
				ms=	new MString(5);
				ms.Append(t);
				ms.Append ( t, startIdx, t.Length );
				len= t.Length - startIdx;

				Assert.IsTrue( ms.Length == t.Length + len );
				for ( int i= 0; i < len ; i++ )
					Assert.AreEqual( ms.Buffer[t.Length + i],  t[ startIdx + i] );
			}

		}

		#if MONO_DEVELOP
		[Test ()]
		#else
		[TestMethod]
		#if !WINDOWS_PHONE
		[TestCategory("MString")]
		#endif
		#endif
		public void MString_Capacity()
		{
			MString ms= new MString( 5 );
			ms.Append( 'a' );		Assert.IsTrue ( ms.Buffer.Length == 5 );
			ms.Append( 'b' );		Assert.IsTrue ( ms.Buffer.Length == 5 );
			ms.Append( 'c' );		Assert.IsTrue ( ms.Buffer.Length == 5 );
			ms.Append( 'd' );		Assert.IsTrue ( ms.Buffer.Length == 5 );
			ms.Append( 'e' );		Assert.IsTrue ( ms.Buffer.Length == 5 );
			ms.Append( 'x' );		
			Assert.IsTrue ( ms.Buffer.Length >= 6 );
			Assert.AreEqual( "abcdex", ms.ToString() );
			
			ms.EnsureCapacity( 2000 ); Assert.IsTrue ( ms.Buffer.Length >= 2000 );
		}

		#if MONO_DEVELOP
		[Test ()]
		#else
		[TestMethod]
		#if !WINDOWS_PHONE
		[TestCategory("MString")]
		#endif
		#endif
		public void MString_AppendWithPadding()
		{
			MString ms= new MString();

			// append pad null objects
			ms.Clear();
			ms.AppendPadRight	( (String)		  null,	3, '#' );	Assert.AreEqual( ms.ToString(), "###"		   );
			ms.AppendPadCenter	( (String)		  null,	4, '*' );	Assert.AreEqual( ms.ToString(), "###****"	   );
			ms.AppendPadLeft	( (String)		  null,	5, '+' );	Assert.AreEqual( ms.ToString(), "###****+++++" );

			ms.Clear();
			ms.AppendPadRight	( (MString) null,	3, '#' );	Assert.AreEqual( ms.ToString(), "###"		   );
			ms.AppendPadCenter	( (MString) null,	4, '*' );	Assert.AreEqual( ms.ToString(), "###****"	   );
			ms.AppendPadLeft	( (MString) null,	5, '+' );	Assert.AreEqual( ms.ToString(), "###****+++++" );

			ms.Clear();
			ms.AppendPadRight	( (StringBuilder) null,	3, '#' );	Assert.AreEqual( ms.ToString(), "###"		   );
			ms.AppendPadCenter	( (StringBuilder) null,	4, '*' );	Assert.AreEqual( ms.ToString(), "###****"	   );
			ms.AppendPadLeft	( (StringBuilder) null,	5, '+' );	Assert.AreEqual( ms.ToString(), "###****+++++" );

			// append pad String objects
			ms.Clear();
			ms.AppendPadRight( "A",		5 );
			ms.AppendPadRight( "AB",	5 );
			ms.AppendPadRight( "ABC",	5 );
			ms.AppendPadRight( "ABCD",	5 );
			ms.AppendPadRight( "ABCDE",	5 );
			ms.AppendPadRight( "ABCDEF",5 );
			ms.AppendPadRight( "ABCDEFG",5 );
			Assert.AreEqual( ms.ToString(), "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG" );

			ms.Clear();
			ms.AppendPadLeft( "A",		5 );
			ms.AppendPadLeft( "AB",		5 );
			ms.AppendPadLeft( "ABC",	5 );
			ms.AppendPadLeft( "ABCD",	5 );
			ms.AppendPadLeft( "ABCDE",	5 );
			ms.AppendPadLeft( "ABCDEF",	5 );
			ms.AppendPadLeft( "ABCDEFG",5 );
			Assert.AreEqual( ms.ToString(), "    A   AB  ABC ABCDABCDEABCDEFABCDEFG" );

			ms.Clear();
			ms.AppendPadCenter( "A", 5 );
			ms.AppendPadCenter( "AB", 5 );
			ms.AppendPadCenter( "ABC", 5 );
			ms.AppendPadCenter( "ABCD", 5 );
			ms.AppendPadCenter( "ABCDE", 5 );
			ms.AppendPadCenter( "ABCDEF", 5 );
			ms.AppendPadCenter( "ABCDEFG", 5 );	   
			Assert.AreEqual( ms.ToString(), "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG" );

			// append pad MString objects
			MString ms2= new MString();
			ms.Clear();
			ms2.Clear().Append( "A"			);	ms.AppendPadRight( ms2,		5 );
			ms2.Clear().Append( "AB"		);	ms.AppendPadRight( ms2,		5 );
			ms2.Clear().Append( "ABC"		);	ms.AppendPadRight( ms2,		5 );
			ms2.Clear().Append( "ABCD"		);	ms.AppendPadRight( ms2,		5 );
			ms2.Clear().Append( "ABCDE"		);	ms.AppendPadRight( ms2,		5 );
			ms2.Clear().Append( "ABCDEF"	);	ms.AppendPadRight( ms2,		5 );
			ms2.Clear().Append( "ABCDEFG"	);	ms.AppendPadRight( ms2,		5 );
			Assert.AreEqual( ms.ToString(), "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG" );

			ms.Clear();	ms2.Clear();
			ms2.Clear().Append( "A"			);	ms.AppendPadLeft( ms2,		5 );
			ms2.Clear().Append( "AB"		);	ms.AppendPadLeft( ms2,		5 );
			ms2.Clear().Append( "ABC"		);	ms.AppendPadLeft( ms2,		5 );
			ms2.Clear().Append( "ABCD"		);	ms.AppendPadLeft( ms2,		5 );
			ms2.Clear().Append( "ABCDE"		);	ms.AppendPadLeft( ms2,		5 );
			ms2.Clear().Append( "ABCDEF"	);	ms.AppendPadLeft( ms2,		5 );
			ms2.Clear().Append( "ABCDEFG"	);	ms.AppendPadLeft( ms2,		5 );
			Assert.AreEqual( ms.ToString(), "    A   AB  ABC ABCDABCDEABCDEFABCDEFG" );

			ms.Clear();	ms2.Clear();
			ms2.Clear().Append( "A"			);	ms.AppendPadCenter( ms2,	5 );
			ms2.Clear().Append( "AB"		);	ms.AppendPadCenter( ms2,	5 );
			ms2.Clear().Append( "ABC"		);	ms.AppendPadCenter( ms2,	5 );
			ms2.Clear().Append( "ABCD"		);	ms.AppendPadCenter( ms2,	5 );
			ms2.Clear().Append( "ABCDE"		);	ms.AppendPadCenter( ms2,	5 );
			ms2.Clear().Append( "ABCDEF"	);	ms.AppendPadCenter( ms2,	5 );
			ms2.Clear().Append( "ABCDEFG"	);	ms.AppendPadCenter( ms2,	5 );
			Assert.AreEqual( ms.ToString(), "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG" );

			// append pad StringBuilder objects
			StringBuilder sb= new StringBuilder();
			ms.Clear();
			sb.Clear().Append( "A"			);	ms.AppendPadRight( sb,		5 );
			sb.Clear().Append( "AB"			);	ms.AppendPadRight( sb,		5 );
			sb.Clear().Append( "ABC"		);	ms.AppendPadRight( sb,		5 );
			sb.Clear().Append( "ABCD"		);	ms.AppendPadRight( sb,		5 );
			sb.Clear().Append( "ABCDE"		);	ms.AppendPadRight( sb,		5 );
			sb.Clear().Append( "ABCDEF"		);	ms.AppendPadRight( sb,		5 );
			sb.Clear().Append( "ABCDEFG"	);	ms.AppendPadRight( sb,		5 );
			Assert.AreEqual( ms.ToString(), "A    AB   ABC  ABCD ABCDEABCDEFABCDEFG" );

			ms.Clear();	
			sb.Clear().Append( "A"			);	ms.AppendPadLeft( sb,		5 );
			sb.Clear().Append( "AB"			);	ms.AppendPadLeft( sb,		5 );
			sb.Clear().Append( "ABC"		);	ms.AppendPadLeft( sb,		5 );
			sb.Clear().Append( "ABCD"		);	ms.AppendPadLeft( sb,		5 );
			sb.Clear().Append( "ABCDE"		);	ms.AppendPadLeft( sb,		5 );
			sb.Clear().Append( "ABCDEF"		);	ms.AppendPadLeft( sb,		5 );
			sb.Clear().Append( "ABCDEFG"	);	ms.AppendPadLeft( sb,		5 );
			Assert.AreEqual( ms.ToString(), "    A   AB  ABC ABCDABCDEABCDEFABCDEFG" );

			ms.Clear();
			sb.Clear().Append( "A"			);	ms.AppendPadCenter( sb,		5 );
			sb.Clear().Append( "AB"			);	ms.AppendPadCenter( sb,		5 );
			sb.Clear().Append( "ABC"		);	ms.AppendPadCenter( sb,		5 );
			sb.Clear().Append( "ABCD"		);	ms.AppendPadCenter( sb,		5 );
			sb.Clear().Append( "ABCDE"		);	ms.AppendPadCenter( sb,		5 );
			sb.Clear().Append( "ABCDEF"		);	ms.AppendPadCenter( sb,		5 );
			sb.Clear().Append( "ABCDEFG"	);	ms.AppendPadCenter( sb,		5 );
			Assert.AreEqual( ms.ToString(), "  A   AB   ABC ABCD ABCDEABCDEFABCDEFG" );
		}



		#if MONO_DEVELOP
		[Test ()]
		#else
		[TestMethod]
		#if !WINDOWS_PHONE
		[TestCategory("MString")]
		#endif
		#endif
		public void MString_Tabs()
		{
			MString ms= new MString();

			// test some bad input 
						ms.Tab(  0,	0,	-1,	'@' );			Assert.AreEqual( "", ms.ToString() );
			ms.Clear();	ms.Tab(  0,	-1,	 0,	'@' );			Assert.AreEqual( "", ms.ToString() );
			ms.Clear();	ms.Tab( -1,	 0,	 0,	'@' );			Assert.AreEqual( "", ms.ToString() );
			ms.Clear();	ms.Tab( -1,	 -1, 0,	'@' );			Assert.AreEqual( "", ms.ToString() );
			ms.Clear();	ms.Tab( -1,	 -1, -1,'@' );			Assert.AreEqual( "", ms.ToString() );
			ms.Clear();	ms.Tab( -5,	-10, 0,	'@' );			Assert.AreEqual( "", ms.ToString() );
			ms.Clear();	ms.Tab( -5,	-10, -100,	'@' );		Assert.AreEqual( "", ms.ToString() );
			ms.Clear();	ms.Tab( 2,	-10, -100,	'@' );		Assert.AreEqual( "", ms.ToString() );
			ms.Clear();	ms.Tab( 0,	  5,    0,	'@' );		Assert.AreEqual( "", ms.ToString() );


			// minpad 0 (not common, default is 1, tab wont move if on tab position) 
			ms.Clear();						ms.Tab( 2, 0 , 0,	'@' ).Append( '-' );		Assert.AreEqual( "-",   ms.ToString());
			ms.Clear();	ms.Append( 'x' );	ms.Tab( 2, 0 , 0,	'@' ).Append( '-' );		Assert.AreEqual( "x@-", ms.ToString());
			
			// more standard tabs
			ms.Clear();
			ms.Append( "12" ).Tab( 2 )
			  .Append( "1" ).Tab( 2 )
			  .Tab(2)
			  .Append( "@" );
			Assert.AreEqual( "12  1   @", ms.ToString() );
			
			ms.Clear();
			ms.Append( "12" ).Tab( 2, 0, 0 )
			  .Append( "1" ).Tab( 2, 0, 0 )
			  .Tab(2, 0, 0)
			  .Append( "@" );
			Assert.AreEqual( "121 @", ms.ToString() );
			
			 
			ms.Clear();
			ms.Append( "12345" ).Tab( 5 )
			  .Append( "1234" )	.Tab( 5 )
			  .Append( "123" )	.Tab( 5 )
			  .Append( "12" )	.Tab( 5 )
			  .Append( "1" )	.Tab( 5 )
			  					.Tab( 5 )
			  .Append( "@" );
			Assert.AreEqual( "12345     1234 123  12   1         @", ms.ToString() );
			
			ms.Clear();
			ms.Append( "12345" ).Tab( 5, 0, 0 )
			  .Append( "1234" )	.Tab( 5, 0, 0 )
			  .Append( "123" )	.Tab( 5, 0, 0 )
			  .Append( "12" )	.Tab( 5, 0, 0 )
			  .Append( "1" )	.Tab( 5, 0, 0 )
			  					.Tab( 5, 0, 0 )
			  .Append( "@" );
			Assert.AreEqual( "123451234 123  12   1    @", ms.ToString() );
			
			ms.Clear();						ms.Tab( 0 ).Append( '-' );		Assert.AreEqual( " -"		, ms.ToString() );
			ms.Clear();						ms.Tab( 1 ).Append( '-' );		Assert.AreEqual( " -"		, ms.ToString() );
			ms.Clear();						ms.Tab( 2 ).Append( '-' );		Assert.AreEqual( "  -"		, ms.ToString() );
			ms.Clear();						ms.Tab( 3 ).Append( '-' );		Assert.AreEqual( "   -"		, ms.ToString() );
			ms.Clear();	ms.Append( 'x' );	ms.Tab( 1 ).Append( '-' );		Assert.AreEqual( "x -"		, ms.ToString() );
			ms.Clear();	ms.Append( 'x' );	ms.Tab( 2 ).Append( '-' );		Assert.AreEqual( "x -"		, ms.ToString() );
			ms.Clear();	ms.Append( 'x' );	ms.Tab( 3 ).Append( '-' );		Assert.AreEqual( "x  -"		, ms.ToString() );
			
			// tabs with tab reference set (designed for multi line tabs)
			ms.Clear().Append("ABC");
			ms.Append( "12345" ).Tab( 5, 3 )
			  .Append( "1234" )	.Tab( 5, 3 )
			  .Append( "123" )	.Tab( 5, 3 )
			  .Append( "12" )	.Tab( 5, 3 )
			  .Append( "1" )	.Tab( 5, 3 )
			  					.Tab( 5, 3 )
			  .Append( "@" );
			Assert.AreEqual( "ABC12345     1234 123  12   1         @", ms.ToString() );

			ms.Clear().Append("ABC");
			ms.Append( "12345" ).Tab( 5, 3, 0 )
			  .Append( "1234" )	.Tab( 5, 3, 0 )
			  .Append( "123" )	.Tab( 5, 3, 0 )
			  .Append( "12" )	.Tab( 5, 3, 0 )
			  .Append( "1" )	.Tab( 5, 3, 0 )
			  					.Tab( 5, 3, 0 )
			  .Append( "@" );
			Assert.AreEqual( "ABC123451234 123  12   1    @", ms.ToString() );
		}


		#if MONO_DEVELOP
		[Test ()]
		#else
		[TestMethod]
		#if !WINDOWS_PHONE
		[TestCategory("MString")]
		#endif
		#endif
		public void MString_SearchAndReplace()
		{
			MString ms= new MString();
			int result;

			// search
			ms.Append("abcd abcd");
			result= ms.IndexOf( "abcd"	  );			Assert.IsTrue( result == 0 );
			result= ms.IndexOf( "b"		  );			Assert.IsTrue( result == 1 );
			result= ms.IndexOf( " abcd"	  );			Assert.IsTrue( result == 4 );
			result= ms.IndexOf( "abcd", 1 );			Assert.IsTrue( result == 5 );
			
			// replace
			ms.Clear();
			ms.Append("Hello W!");
			result= ms.ReplaceCount( "W!",	"world!"  );	Assert.AreEqual( ms.ToString(), "Hello world!" );		Assert.AreEqual( 1, result );
			result= ms.ReplaceCount( " ",	"* *"	  );	Assert.AreEqual( ms.ToString(), "Hello* *world!" );		Assert.AreEqual( 1, result );
			result= ms.ReplaceCount( "*",	"#", 0, 1 );	Assert.AreEqual( ms.ToString(), "Hello# *world!" );		Assert.AreEqual( 1, result );
			result= ms.ReplaceCount( "*",	"#"		  );	Assert.AreEqual( ms.ToString(), "Hello# #world!" );		Assert.AreEqual( 1, result );
			result= ms.ReplaceCount( "#",	"$$$"	  );	Assert.AreEqual( ms.ToString(), "Hello$$$ $$$world!" );	Assert.AreEqual( 2, result );
			result= ms.ReplaceCount( "$$$",	"*"		  );	Assert.AreEqual( ms.ToString(), "Hello* *world!" );		Assert.AreEqual( 2, result );
			result= ms.ReplaceCount( "*",	""		  );	Assert.AreEqual( ms.ToString(), "Hello world!" );		Assert.AreEqual( 2, result );
		}

		#if MONO_DEVELOP
		[Test ()]
		#else
		[TestMethod]
		#if !WINDOWS_PHONE
		[TestCategory("MString")]
		#endif
		#endif
		public void MString_Compare()
		{
			MString ms= new MString();
			int result;

			String t= "abcde";
			ms.Append( t );
			result= ms.CompareTo( t	  );							Assert.AreEqual( t.CompareTo( t ),								result );
			result= ms.CompareTo( t + "x"	  );					Assert.AreEqual( t.CompareTo( t + "x" ),						result );
			result= ms.CompareTo( t.Substring (0, t.Length -1 )  );	Assert.AreEqual( t.CompareTo( t.Substring (0, t.Length -1 ) ),	result );
			result= ms.CompareTo( "pad" + t,  false, 3	  );		Assert.AreEqual( 0,												result );
			result= ms.CompareTo( "pad" + t,  false, 3, 2  );		Assert.AreEqual( 1,												result );
			result= ms.CompareTo( "pad" + t,  false, 3, 100, 0, 4 );Assert.AreEqual( -1,											result );
			result= ms.CompareTo( "pad" + t,  false, 3, 100, 0, 5 );Assert.AreEqual( 0,												result );
			result= ms.CompareTo( t, false, 2,2,   2,2	  );		Assert.AreEqual( 0,												result );
			result= ms.CompareTo( t, false, 2,2,   2,1	  );		Assert.AreEqual( -1,											result );
			result= ms.CompareTo( t, false, 2,2,   2,3	  );		Assert.AreEqual( 1, 											result );

			result= ms.CompareTo( t, false, -2,5,   -2, 5 );							Assert.AreEqual( 0, 						result );
			result= ms.CompareTo( t, false,  2, int.MaxValue,    2, int.MaxValue );		Assert.AreEqual( 0, 						result );
			result= ms.CompareTo( t, false, -2, int.MaxValue,   -2, int.MaxValue );		Assert.AreEqual( 0, 						result );
			result= ms.CompareTo( t, false, -2, 100,			-2, 99 );				Assert.AreEqual( 0, 						result );
			result= ms.CompareTo( t, false, -2, 5,				-2, int.MaxValue );		Assert.AreEqual( 1, 						result );
			result= ms.CompareTo( t, false, -2, int.MaxValue,	-2, 5 );				Assert.AreEqual( -1, 						result );

			// greater/smaller strings
			int scRes;
			String greater=	 "x";
			String greater2= "abcdef";
			String smaller=  "aaa";
			String smaller2= "abcd";
			result= ms.CompareTo( greater  );			scRes=	t.CompareTo( greater  );	Assert.IsTrue( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );
			result= ms.CompareTo( greater2 );			scRes=	t.CompareTo( greater2 );	Assert.IsTrue( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );
			result= ms.CompareTo( smaller  );			scRes=	t.CompareTo( smaller );		Assert.IsTrue( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );
			result= ms.CompareTo( smaller2 );			scRes=	t.CompareTo( smaller2 );	Assert.IsTrue( (result==0 && scRes==0) || (result<0 && scRes<0) ||(result>0 && scRes>0)   );

			// ignore case
			String ut= t.ToUpperInvariant();
			result= ms.CompareTo( ut );								Assert.IsTrue( result >  0 );
			result= ms.CompareTo( ut, false );						Assert.IsTrue( result >  0 );
			result= ms.CompareTo( ut, true );						Assert.IsTrue( result == 0 );
			result= ms.CompareTo( ut, false, 2,2,   2,2	  );		Assert.IsTrue( result >  0 );
			result= ms.CompareTo( ut, true,  2,2,   2,2	  );		Assert.IsTrue( result == 0 );
																									   
			// we do just a very little testing with StringBuilder and MString parameter version of this function, as
			// the code differences are very small
			StringBuilder tSB= new StringBuilder(); tSB.Append( t );
			result= ms.CompareTo( tSB	  );							Assert.AreEqual( 0,											result );
			result= ms.CompareTo( tSB, false, -5, 100, -10, 100	  );	Assert.AreEqual( 0,											result );
			result= ms.CompareTo( tSB, false,  2,   3,   2,   3	  );	Assert.AreEqual( 0,											result );
			
			MString tMS= new MString(); tMS.Append( t );
			result= ms.CompareTo( tMS	  );							Assert.AreEqual( 0,											result );
			result= ms.CompareTo( tMS, false, -5, 100, -10, 100	  );	Assert.AreEqual( 0,											result );
			result= ms.CompareTo( tMS, false,  2,   3,   2,   3	  );	Assert.AreEqual( 0,											result );
			
			// different ranges
			String r1=   "*ABCDEF*";
			String r2= "##*ABCDEF*##";
			ms.Clear().Append( r1 );
			result= ms.CompareTo( r2, false, 2,8		  );		Assert.AreEqual( 0,												result );
			result= ms.CompareTo( r2, false, 3,6,   1,6	  );		Assert.AreEqual( 0,												result );

			// startsWith/Endswith/ContainsAt
			String sub1=  "ABC";
			String sub2=  "abc";
			String s1= "ABCDEF";
			String s2= "123ABC";
			String s3= "##12ABC21##";
			String s4= "AB";
			bool bRes;
			ms.Clear().Append( s1 );	bRes= ms.StartsWith( sub1 );  			Assert.AreEqual( true,		bRes );
										bRes= ms.StartsWith( sub2 );  			Assert.AreEqual( false,		bRes );
			ms.Clear().Append( s2 );	bRes= ms.EndsWith  ( sub1 );  			Assert.AreEqual( true,		bRes );
										bRes= ms.EndsWith  ( sub2 );  			Assert.AreEqual( false,		bRes );
			ms.Clear().Append( s3 );	bRes= ms.ContainsAt( sub1, 4 );			Assert.AreEqual( true,		bRes );
										bRes= ms.ContainsAt( sub2, 4 );			Assert.AreEqual( false,		bRes );
										bRes= ms.ContainsAt( sub2, 4, true );	Assert.AreEqual( true,		bRes );
			ms.Clear().Append( s4 );	bRes= ms.ContainsAt( sub1, 4 );			Assert.AreEqual( false,		bRes );
										bRes= ms.ContainsAt( sub2, 4 );			Assert.AreEqual( false,		bRes );
			ms.Clear().Append( s4 );	bRes= ms.ContainsAt( sub1, 0 );			Assert.AreEqual( false,		bRes );
										bRes= ms.ContainsAt( sub2, 0, true );	Assert.AreEqual( false,		bRes );
		}

		#if MONO_DEVELOP
		[Test ()]
		#else
		[TestMethod]
		#if !WINDOWS_PHONE
		[TestCategory("MString")]
		#endif
		#endif
		public void MString_ConvertCase()
		{
			MString ms= new MString();

			// test all characters in the 16 bit range
			int testCharRangeStart= (int) Char.MinValue;
			int testCharRangeEnd=	(int) Char.MaxValue;

			StringBuilder sb= new StringBuilder( testCharRangeEnd - testCharRangeStart );
			for ( int i= testCharRangeStart; i < testCharRangeEnd ; i++ )
				sb.Append( (char) i );
			String t= sb.ToString();
			String tUpper= t.ToUpperInvariant();
			String tLower= t.ToLowerInvariant();

			ms.Clear().Append( t ).ConvertCase( false );			Assert.IsTrue( tLower.Equals( ms.ToString() ) );
			ms.Clear().Append( t ).ConvertCase( true  );			Assert.IsTrue( tUpper.Equals( ms.ToString() ) );

			// test substring conversion
			t= "AAAbbb";
			ms.Clear().Append( t ).ConvertCase( false,  0, 2 );		Assert.IsTrue( ms.ToString().Equals( "aaAbbb" ) );
			ms.Clear().Append( t ).ConvertCase( false, -2, 3 );		Assert.IsTrue( ms.ToString().Equals( "aAAbbb" ) );
			ms.Clear().Append( t ).ConvertCase( false, -2    );		Assert.IsTrue( ms.ToString().Equals( "aaabbb" ) );

			ms.Clear().Append( t ).ConvertCase( true,  3,  2 );		Assert.IsTrue( ms.ToString().Equals( "AAABBb" ) );
			ms.Clear().Append( t ).ConvertCase( true, -2,  6 );		Assert.IsTrue( ms.ToString().Equals( "AAABbb" ) );
			ms.Clear().Append( t ).ConvertCase( true, -2     );		Assert.IsTrue( ms.ToString().Equals( "AAABBB" ) );
		}

	}
}
