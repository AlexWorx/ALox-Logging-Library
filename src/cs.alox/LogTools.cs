// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:	LogTools
//  File:	LogTools.cs													  Namespace:  com.aworx.lox
// #################################################################################################

using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using com.aworx.util;

#if ( !ALOX_NO_XML) 
	using System.Xml.Linq;
#endif

#if (!ALOX_NO_REFLECTION) 
	using System.Reflection;
#endif

#if (!ALOX_NO_THREADS) 
	using System.Threading;
using com.aworx.lox.core;
#endif
   
namespace com.aworx.lox {

/** ***********************************************************************************************
 * <summary> 
 *	Provides high level functionality for logging things like multiple lines, Exceptions, 
 *	XML documents or object instances.</summary>
 **************************************************************************************************/
public class LogTools 
{
	// #################################################################################################
	#region  __String_Constants__
	// #################################################################################################

		/// <summary> The String to log out if the exception parameter equals null</summary>
		public static	String			FormatNullException				= "<No exception given>";

		/// <summary> The String to log out if a given object instance equals null</summary>
		public static	String			FormatNullInstance				= "<null> (no object)";

		/// <summary> Prefix for instance line numbers</summary>
		public static	String			FormatInstanceLineNoPrefix	= "<";

		/// <summary> Postfix for instance line numbers</summary>
		public static	String			FormatInstanceLineNoPostfix	= ">";

		/// <summary> Indent String for instance lines</summary>
		public static	String			FormatInstanceIndent			= "  ";

	#endregion


	// #################################################################################################
	// Public fields
	// #################################################################################################

		/// <summary>Tab stop for values when logging instances.</summary>
		protected	static		int							InstanceLogTabStop= 30;

	#if ALOX_DEBUG || ALOX_REL_LOG

		// #################################################################################################
		// Private/protected fields
		// #################################################################################################

		/// <summary>Buffer to build log messages.</summary>
		protected	static		MString				toolBuf;

		/// <summary>Instance line number counter.</summary>
		protected	static		uint						instanceLineNumber;

		/// <summary>Instance line number dictionary used to refer to already logged sub objects.</summary>
		protected	static		Dictionary<Object, UInt32>	instanceObject2LineNumber;

		/** 
		 * <summary>
		 *  This is the ThreadLock (mutex) which each method of this class uses to lock resources, e.g.
		 *  the toolBuf 
		 * </summary>
		 */
		protected	static		ThreadLock					Lock					=new ThreadLock();


		// #################################################################################################
		// Public static interface (not accessible in release code)
		// #################################################################################################

	#endif

	/** ***********************************************************************************************
	 * <summary>
	 *  Log an exception including inner exceptions recursively. Note: Calls to this  method are
	 *  automatically removed from release code.
	 * </summary>
	 * <param name="domain">  	The log domain name. If not starting with a slash ('/')
	 * 							this is appended to any default domain name that might have been
	 * 							specified for the source file. If null, default domain is used. </param>
	 * <param name="level">   	The logging level. </param>
	 * <param name="e">		  	The Exception to log. </param>
	 * <param name="headline">	(Optional) A headline string to precede the exception with. </param>
	 * <param name="indent">  	(Optional) the indentation in the output (recursively increased).
	 * 							Defaults to 0. </param>
	 * <param name="lox">	  	(Optional) The lox to log with. If null, the static member LOX of 
	 * 							the static class Log is used. </param>
	 * <param name="csf">	  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">	  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">	  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")] 
	public static void Exception( String		domain,		Log.Level	level,
								  Exception		e,			String		headline= null,
								  int			indent= 0, 	Lox			lox= null,
								  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.aquire();

				// create/clear toolBuf
				if ( toolBuf == null )
					toolBuf= new MString( 1024 );
				toolBuf.Clear();

				// dump exception to the Buffer
				exception ( e, headline, -1 );

				// if no lox given, use static Log.LOX
				if ( lox == null )
 					lox= Log.LOX;

				// log it using the static Log interface
				lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn);

			} finally { Lock.release(); } 
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log an exception including inner exceptions recursively. Default domain of file is used with
	 *  Log.Level.Error. Note: Calls to this  method are automatically removed from release code.
	 * </summary>
	 * <param name="e">		  	The Exception to log. </param>
	 * <param name="headline">	(Optional) A headline string to precede the exception with. </param>
	 * <param name="indent">  	(Optional) the indentation in the output (recursively increased).
	 * 							Defaults to 0. </param>
	 * <param name="lox">	  	(Optional) The lox to log with. If null, the static member LOX of 
	 * 							the static class Log is used. </param>
	 * <param name="csf">	   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">	   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">	   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")] 
	public static void Exception( Exception		e,				String		headline= null,
								  int			indent=	0,		Lox			lox= null,
								  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Exception( null, Log.Level.Error, e, headline, indent, lox, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>	Uses reflection to log an object. </summary>
	 * <param name="domain">	  	The log domain name. If not starting with a slash ('/') this is
	 * 								appended to any default domain name that might have been
	 * 								specified for the source file. </param>
	 * <param name="level">		  	The logging level. </param>
	 * <param name="o">			  	The object to be logged. </param>
	 * <param name="maxRecursion">	The maximum depth of recursion for logging nested object. </param>
	 * <param name="headline">	  	(Optional) A headline string to precede the exception with. </param>
	 * <param name="indent">	  	(Optional) The indentation in the output (recursively increased).
	 * 								Defaults to 0. </param>
	 * <param name="lox">			(Optional) The lox to log with. If null, the static member LOX of 
	 * 								the static class Log is used. </param>
	 * <param name="csf">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")] 
	public static void Instance( String		domain,				Log.Level	level,
								 Object		o,					int			maxRecursion,
								 String		headline=  null, 	int			indent=	0,
								 Lox		lox=	   null,
								 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.aquire();

				// if no lox given, use static Log.LOX
				if ( lox == null )
 					lox= Log.LOX;

				#if !(ALOX_WP71 || ALOX_WP8 || ALOX_NO_REFLECTION)

					// dump exception to the Buffer
					instance( o, maxRecursion, headline );

					// log it using the static Log interface
					lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn );

				#else
					lox.Line ( true, domain, level, "LoxTools.Instance(): Reflection not supported on this platform. ToString(): ", indent );
					lox.Line ( true, domain, level, ( o == null ? "null" : o.ToString()), indent + 1 );
				#endif // NO_REFLECTION

			} finally { Lock.release(); }
#endif
	}

	/** ***********************************************************************************************
	 * <summary>	Uses reflection to log an object. </summary>
	 * <param name="level">		  	The logging level. </param>
	 * <param name="o">			  	The object to be logged. </param>
	 * <param name="maxRecursion">	The maximum depth of recursion for logging nested object. </param>
	 * <param name="headline">	  	(Optional) A headline string to precede the exception with. </param>
	 * <param name="indent">	  	(Optional) The indentation in the output (recursively increased).
	 * 								Defaults to 0. </param>
	 * <param name="lox">		  	(Optional) The lox to log with. If null, the static member LOX of 
	 * 								the static class Log is used. </param>
	 * <param name="csf">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")] 
	public static void Instance( Log.Level	level,
								 Object		o,					int	maxRecursion,
								 String		headline= null, 	int	indent=	0,
								 Lox		lox=	  null,
								 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Instance( null, level, o, maxRecursion, headline, indent, lox, csf, cln, cmn );
		#endif 
	}

	#if  !ALOX_NO_XML
		/** ***********************************************************************************************
		 * <summary>
		 *  Log a xml document. Note: Calls to this method are automatically removed from release code.
		 * </summary>
		 * <param name="domain">   	The log domain name. If not starting with a slash ('/')
		 * 							this is appended to any default domain name that might have been
		 * 							specified for the source file. </param>
		 * <param name="level">	   	The logging level. </param>
		 * <param name="xDocument">	the xml document to be logged. </param>
		 * <param name="headLine"> 	(Optional) The headline to log. </param>
		 * <param name="indent">  	(Optional) the indentation in the output (recursively increased).
		 * 							Defaults to 0. </param>
		 * <param name="lox">	  	(Optional) The lox to log with. If null, the static member LOX of 
		 * 							the static class Log is used. </param>
		 * <param name="csf">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 * <param name="cln">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 * <param name="cmn">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 **************************************************************************************************/
		[Conditional("ALOX_DEBUG")] 
		public static void XML(	String		domain,			Log.Level	level,
								XDocument	xDocument,		String		headLine=	null,
								int			indent=	  0, 	Lox			lox=		null,
								[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
		{
			#if ALOX_DEBUG || ALOX_REL_LOG
				try { Lock.aquire();

					// dump exception to the Buffer
					xml( xDocument, headLine );

					// if no lox given, use static Log.LOX
					if ( lox == null )
 						lox= Log.LOX;

					// log it using the static Log interface
					lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn );


				} finally { Lock.release(); } 
			#endif
		}

		/** ***********************************************************************************************
		 * <summary>
		 *  Log a xml document. Note: Calls to this method are automatically removed from release code.
		 * </summary>
		 * <param name="level">	   	The logging level. </param>
		 * <param name="xDocument">	the xml document to be logged. </param>
		 * <param name="headLine"> 	The headline to log. </param>
		 * <param name="indent">  	(Optional) the indentation in the output (recursively increased).
		 * 							Defaults to 0. </param>
		 * <param name="lox">	  	(Optional) The lox to log with. If null, the static member LOX of 
		 * 							the static class Log is used. </param>
		 * <param name="csf">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 * <param name="cln">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 * <param name="cmn">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 **************************************************************************************************/
		[Conditional("ALOX_DEBUG")] 
		public static void XML(	Log.Level		level,
								XDocument		xDocument,	String	headLine,
								int				indent=	0, 	Lox		lox= null,
								[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
		{
			#if ALOX_DEBUG || ALOX_REL_LOG
				XML( null, level, xDocument, headLine, indent, lox, csf, cln, cmn );
			#endif
		}

		/** ***********************************************************************************************
		 * <summary>
		 *  Log a xml element. Note: Calls to this method are automatically removed from release code.
		 * </summary>
		 * <param name="domain">  	The log domain name. If not starting with a slash ('/')
		 * 							this is appended to any default domain name that might have been
		 * 							specified for the source file. </param>
		 * <param name="level">   	The logging level. </param>
		 * <param name="xElement">	the answer node of the xml tree to be logged. </param>
		 * <param name="headLine">	(Optional) The headline to log. </param>
		 * <param name="indent">  	(Optional) the indentation in the output (recursively increased).
		 * 							Defaults to 0. </param>
		 * <param name="lox">	  	(Optional) The lox to log with. If null, the static member LOX of 
		 * 							the static class Log is used. </param>
		 * <param name="csf">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 * <param name="cln">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 * <param name="cmn">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 **************************************************************************************************/
		[Conditional("ALOX_DEBUG")] 
		public static void XML(	String			domain,		Log.Level	level,
								XElement		xElement,	String		headLine=	null,
								int				indent=	 0, Lox			lox= null,
								[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
		{
			#if ALOX_DEBUG || ALOX_REL_LOG
				try { Lock.aquire();

					// create/clear toolBuf
					if ( toolBuf == null )
						toolBuf= new MString( 1024 );
					else
						toolBuf.Clear();

					// dump exception to the Buffer
					xmlElement( xElement, headLine, 0 );

					// if no lox given, use static Log.LOX
					if ( lox == null )
 						lox= Log.LOX;

					// log it using the static Log interface
					lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn );

			
				} finally { Lock.release(); } 
			#endif
		}

		/** ***********************************************************************************************
		 * <summary>
		 *  Log a xml element. Note: Calls to this method are automatically removed from release code.
		 * </summary>
		 * <param name="level">   	The logging level. </param>
		 * <param name="xElement">	the answer node of the xml tree to be logged. </param>
		 * <param name="headLine">	The head line. </param>
		 * <param name="indent">  	(Optional) the indentation in the output (recursively increased).
		 * 							Defaults to 0. </param>
		 * <param name="lox">	  	(Optional) The lox to log with. If null, the static member LOX of 
		 * 							the static class Log is used. </param>
		 * <param name="csf">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 * <param name="cln">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 * <param name="cmn">	   	(Optional) Caller info, compiler generated. Please omit. </param>
		 **************************************************************************************************/
		[Conditional("ALOX_DEBUG")] 
		public static void XML(	Log.Level	level,
								XElement	xElement,	String		headLine,
								int			indent=	0, 	Lox			lox= null,
								[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
		{
			#if ALOX_DEBUG || ALOX_REL_LOG
				XML( null, level, xElement, headLine, indent, lox, csf, cln, cmn );
			#endif
		}

	#endif // ALOX_NO_XML

	// #################################################################################################
	// internals
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>	Logs an exception. </summary>
	 * <param name="e">		  	The log domain name. If not starting with a slash ('/') this is
	 * 							appended to any default domain name that might have been specified
	 * 							for the source file. </param>
	 * <param name="headline">	A headline string to precede the exception with. </param>
	 * <param name="indent">  	The indentation in the output (recursively increased). If set to -1
	 * 							the 'headline' is logged. </param>
	 **************************************************************************************************/
	#if ALOX_DEBUG || ALOX_REL_LOG
	protected static void exception( Exception e, String headline, int indent )
	{ 
			// log headline if answer exception
			if ( indent == -1 )
			{
				indent= 0;
				if ( headline != null )
					toolBuf.Append( headline ).NewLine();
			}

			// increase tab level
			indent++;

			// Assert
			if ( e == null )
			{
				toolBuf.Append( ' ',  indent * 2 ).Append( FormatNullException );
				return;
			}


			// log exception details
											{ toolBuf.Append( ' ',  indent * 2 ).Append( "Type:       ").Append(e.GetType().ToString()				).NewLine(); }
											{ toolBuf.Append( ' ',  indent * 2 ).Append( "Message:    ").Append(e.Message							).NewLine(); }
			#if !ALOX_WP71
			if ( e.HelpLink		!= null)	{ toolBuf.Append( ' ',  indent * 2 ).Append( "HelpLink:   ").Append(e.HelpLink							).NewLine(); }
			if ( e.Source		!= null)	{ toolBuf.Append( ' ',  indent * 2 ).Append( "Source:     ").Append(e.Source							).NewLine(); }
			if ( e.HResult		!= 0)		{ toolBuf.Append( ' ',  indent * 2 ).Append( "HResult:    ").Append(String.Format("0x{0:X08}",e.HResult)).NewLine(); }
			#endif

			if ( e.StackTrace	!= null)	
			{
				toolBuf.Append( ' ',  indent * 2 ).Append( "StackTrace: ").NewLine(); 
				toolBuf.Append( e.StackTrace ).NewLine(); 
			}

			// recursion
			if ( e.InnerException != null )
			{
				toolBuf.Append( ' ',  indent * 2 ).Append( "Inner:   " ).NewLine();
				exception( e.InnerException, null, indent );
			}
	}
	#endif  // ALOX_DEBUG || ALOX_REL_LOG

	#if !(ALOX_WP71 || ALOX_WP8 || ALOX_NO_REFLECTION)

		/** ***********************************************************************************************
		 * <summary>
		 *  Use reflection to log an instance an object to the log stream (including inner objects
		 *  recursively)
		 * </summary>
		 * <param name="o">			  	The object to be logged. </param>
		 * <param name="maxRecursion">	The maximum depth of recursion for logging nested object. </param>
		 * <param name="headLine">	  	The headline to log. </param>
		 **************************************************************************************************/
		protected static void instance( Object o, int maxRecursion, String headLine) 
		{ 
			#if ALOX_DEBUG || ALOX_REL_LOG
				// prepare fields
				if ( toolBuf == null )
					toolBuf= new MString( 1024 );
				else
					toolBuf.Clear();
				instanceLineNumber=			0;
				instanceObject2LineNumber=  new Dictionary<Object, UInt32>(); 

				// log headline if answer exception
				if ( headLine != null )
				{
					toolBuf.Append( headLine ).Append(' ');
				}

				// check for null
				if ( o == null )
				{
					toolBuf.Append( FormatNullInstance );
					return;
				}

				// check for simple?
				if (o is ValueType || o is String)
				{
					if( o is ValueType )
						toolBuf.Append( o.ToString() );
					else
						toolBuf.Append( '\"' ).Append( (String) o ).Append( '\"' );

					toolBuf.Tab( 5 ).Append( '{' ).Append( o.GetType().Name ).Append( '}' );
					return;
				}

				// dump the object
				instanceRecursive( o, maxRecursion, headLine != null ? 1 : 0  );

				// dispose the dictionary
				instanceObject2LineNumber= null; 

			#endif  // ALOX_DEBUG || ALOX_REL_LOG
		}

		#if ALOX_DEBUG || ALOX_REL_LOG

		/** ***********************************************************************************************
		 * <summary>
		 *  Creates a new line, adds line number (format defined in fields #FormatInstanceLineNoPrefix
		 *  and #FormatInstanceLineNoPostfix) and then adds indent characters (defined in field
		 *  FormatInstanceIndent).
		 * </summary>
		 * <param name="indent">	The indentation of the line. </param>
		 **************************************************************************************************/
		protected static void instanceNewLine( int indent )
		{
			instanceLineNumber++;
			toolBuf.NewLine();
			toolBuf.Append( FormatInstanceLineNoPrefix ).Append( instanceLineNumber, 2 ).Append( FormatInstanceLineNoPostfix );
			for ( int i= indent; i > 0; i-- )
				toolBuf.Append( FormatInstanceIndent ); 
		}

		/** ***********************************************************************************************
		 * <summary>	Instance recursive. </summary>
		 * <param name="element">			The element. </param>
		 * <param name="maxRecursion">  	The maximum depth of recursion for logging nested object. </param>
		 * <param name="indent">			The indentation in the output (recursively increased). </param>
		 **************************************************************************************************/
		protected static void instanceRecursive( Object element, int maxRecursion, int indent )
		{
			int tabReference= toolBuf.Length;

			// get type
			Type elementType= element.GetType();

			// check for maximum recursion
			if ( maxRecursion < 0 )
			{
				String eToString=	element.ToString();
				String eType=		elementType.Namespace + "." + elementType.Name;

				// often, ToString() just returns the type
				if ( !eToString.Equals( eType ) )
					toolBuf.Append( eToString );

				// append "(max rec.)" + tab + type
				toolBuf.Append( "(max rec.)" ).Tab( InstanceLogTabStop, tabReference ).Append( '{' ).Append( eType ).Append( "}");

				return;
			}

			// string?
			if ( elementType == typeof(string) )
			{
				// add value and type, that's it
				toolBuf	.Append( '\"' ).Append( element.ToString() ).Append( '\"' )
						.Tab(	InstanceLogTabStop, tabReference )
						.Append( '{' ).Append( elementType.Name ).Append( '}' );

				return;
			}

			// value type?
			if ( elementType.IsValueType )
			{
				// add value and type, that's it
				toolBuf	.Append( element.ToString() )
						.Tab(	InstanceLogTabStop, tabReference )
						.Append( '{' ).Append( elementType.Name ).Append( '}' );

				return;
			}

			// mark object as being logged (in next line)
			instanceObject2LineNumber.Add( element, instanceLineNumber );

			// log object type if not type of IEnumerable 
			if (!typeof(IEnumerable).IsAssignableFrom(elementType))
			{
				instanceNewLine( ++indent );
				toolBuf.Append( '{' ).Append( elementType.Namespace + "." + elementType.Name).Append( "}:" );
			}

			// log collections
			IEnumerable enumerableElement= element as IEnumerable;
			if (enumerableElement != null)
			{
				// count objects
				int qtyObjects= enumerableElement.Cast<object>().Count();

				instanceNewLine( ++indent );
				toolBuf.Append( elementType.Name).Append( " of size " ).Append( qtyObjects );

				// loop over all objects
				int itemNo= 0;
				foreach (object item in enumerableElement)
				{
					instanceNewLine( indent );
					toolBuf.Append( "  " ).Append( itemNo++, 1 ).Append(": ");

					// null item?
					if ( item == null )
					{
						toolBuf.Append("  ", indent*2).Append( "<null>" );
						continue;
					}

					// already touched?
					uint lineNumber;
					if ( !item.GetType().IsValueType && instanceObject2LineNumber.TryGetValue( item, out lineNumber ) )
					{
						tabReference= toolBuf.Length;
						toolBuf.Append( "(Cyclic ref., see line " )
							   .Append( FormatInstanceLineNoPrefix )
							   .Append( lineNumber, 2 )
							   .Append( FormatInstanceLineNoPostfix )
							   .Append( ')' ).Tab(	InstanceLogTabStop, tabReference )
							   .Append( '{' ).Append( item.GetType().Name ).Append( '}' );
							   
						continue;
					}

					// log element
					instanceRecursive( item, maxRecursion - 1, indent + 1 );
				}
			}

			// log classes
			else
			{
				// loop over fields
				MemberInfo[] members= element.GetType().GetMembers( BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance );

				foreach (var memberInfo in members)
				{
					// get type	and value
					Type	type;
					object	value;

					// get field/property info
					FieldInfo		fInfo=	memberInfo as FieldInfo;
					PropertyInfo	pInfo=	memberInfo as PropertyInfo;

						 if ( fInfo != null )
					{
							  type=		fInfo.FieldType;
						try { value=	fInfo.GetValue(element); }  catch (Exception) {	value= "<not retrievable>"; }
					}
					else if ( pInfo != null )
					{
							  type=		pInfo.PropertyType;
						try { value=	pInfo.GetValue(element); }  catch (Exception) {	value= "<not retrievable>"; }
					}

					// not a field or property?
					else
						continue;
				

					// fill temp buf with "name: "

					// filter "__BackingField"s 
					if ( memberInfo.Name.Contains( "__BackingField" ) )
						continue;

					instanceNewLine( indent );
					tabReference= toolBuf.Length;
					toolBuf.Append( memberInfo.Name ).Append(':').Tab(	InstanceLogTabStop, tabReference );

					// null, value type or string?
					if (	type			.IsValueType
						 ||	type			== typeof(string)
						 || value			== null 
						 || value			is string 
						 || value.GetType().IsValueType 
					   )
					{
						// add value and type, that's it

							 if ( value == null )
							toolBuf.Append("<null>"						).Tab(	InstanceLogTabStop, tabReference );
						else if ( type == typeof(string) )
							toolBuf.Append("\"" + (string) value + "\"" ).Tab(	InstanceLogTabStop, tabReference );
						else
							toolBuf.Append(value.ToString()				).Tab(	InstanceLogTabStop, tabReference );

						toolBuf.Append( "{" ).Append( type.Name ).Append( '}' );

						continue;
					}

					// already logged?
					uint lineNumber;
					if ( instanceObject2LineNumber.TryGetValue( value, out lineNumber ) )
					{
						toolBuf	.Append( "(Cyclic ref., see line " )
								.Append( FormatInstanceLineNoPrefix )
								.Append( lineNumber, 2 )
								.Append( FormatInstanceLineNoPostfix )	.Append( ')' )
								.Tab   ( InstanceLogTabStop, tabReference )
								.Append( "{" ).Append( type.Name ).Append( '}' );

						continue;
					}

					// recursively log value
					instanceRecursive( value, maxRecursion - 1, indent );
				}
			}

		}
	#endif  // ALOX_DEBUG || ALOX_REL_LOG
	#endif  // !(ALOX_WP71 || ALOX_WP8 || ALOX_NO_REFLECTION)


	#if !ALOX_NO_XML
	#if ALOX_DEBUG


		/** ***********************************************************************************************
		 * <summary> Dump a xml document into our Buffer. </summary>
		 * <param name="xDocument"> 	The XDocument to be logged. </param>
		 * <param name="headLine">  	The headline to log. </param>
		 **************************************************************************************************/
		protected static void xml( XDocument xDocument, String headLine)
		{ 
			// create/clear toolBuf
			if ( toolBuf == null )
				toolBuf= new MString( 1024 );
			else
				toolBuf.Clear();

			// print headline
			if ( headLine != null )
				toolBuf.Append( headLine ).NewLine();

			// log elements
			foreach ( XElement el in xDocument.Elements() )
				xmlElement( el, null, headLine != null ? 1 : 0 );
		}

		/** ***********************************************************************************************
		 * <summary>	Internal function for logging an XElement. </summary>
		 * <param name="xe">	  	The XElement to log. </param>
		 * <param name="headLine">	The headline to log. </param>
		 * <param name="indent">  	The indentation to Log. </param>
		 **************************************************************************************************/
		protected static void xmlElement( XElement xe, String headLine, int indent )
		{ 
			// print headline
			if ( headLine != null )
				toolBuf.Append( headLine ).NewLine();

			// print name
			toolBuf.Append( ' ',  indent * 2 ).Append( xe.Name.ToString() );
			if ( !xe.HasElements )
				toolBuf.Append( '=' ).Append( '\"' ).Append(xe.Value).Append( '\"' );

			// print attributes
			if ( xe.HasAttributes )
				foreach ( var attribute in xe.Attributes() )
					toolBuf.Append( ' ' ).Append( attribute.Name.ToString() ).Append( '=' ).Append( '\"' ).Append( attribute.Value ).Append( '\"' );

			toolBuf.NewLine();

			// recursion
			foreach ( var element in xe.Elements() )
				xmlElement( element, null, indent + 1 );
		}
	#endif  // ALOX_DEBUG || ALOX_REL_LOG
	#endif //(!ALOX_NO_XML)
} //class LogTools
} // namespace
