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
 *	Provides high level functionality for logging things like Exceptions, objects and XML documents.
 *	</summary>
 **************************************************************************************************/
public class LogTools 
{
	#if ALOX_DEBUG || ALOX_REL_LOG
	
		// #################################################################################################
		#region  __String_Constants__
		// #################################################################################################

		/// <summary> The String to log out if the exception parameter equals null</summary>
		public static	String			FmtExcNull						= "<No exception given>";

		/// <summary> Prefix for instance line numbers</summary>
		public static	String			FmtInstLineNoPrefix				= "<";

		/// <summary> Postfix for instance line numbers</summary>
		public static	String			FmtInstLineNoPostfix			= ">";

		/// <summary> The String to log out if a given object instance equals null</summary>
		public static	String			FmtInstNull						= "<null>";

		/// <summary> Prefix before logging out a string representation of a member because recursion limit was
		/// reached. </summary>
		public static	String			FmtInstRecursionLimit			= "(MAX REC) ";

		/// <summary> Prefix before logging out a cyclic reference line number. </summary>
		public static	String			FmtInstCycRefPrefix				= "(Cyclic ref., see line <";
	
		/// <summary> Prefix before logging size of an IEnumberable. </summary>
		public static	String			FmtInstIEnumerablePrefix 		= "IEnumerable, size= ";
	
		/// <summary> Postfix after logging IEnumberable. </summary>
		public static	String			FmtInstIEnumerablePostfix		= "";
	   
		/// <summary> Prefix before logging size of an IEnumberable. </summary>
		public static	String			FmtInstArrayPrefix 				= "array[";
	
		/// <summary> Postfix after logging IEnumberable. </summary>
		public static	String			FmtInstArrayPostfix				= "]";

		/// <summary> Postfix after logging out a cyclic reference line number. </summary>
		public static	String			FmtInstCycRefPostfix			= ">)";
		
		/// <summary> Indent String for instance lines</summary>
		public static	String			FmtInstNoAccessToValue			= "<no access>" ;

		/// <summary> Prefix for type names</summary>
		public static	String			FmtInstTypePrefix				= "{";

		/// <summary> Postfix for type names</summary>
		public static	String			FmtInstTypePostfix				= "}";

		/// <summary> Indent String for instance lines</summary>
		public static	String			FmtInstIndent					= "  ";

		#endregion


		// #################################################################################################
		// Public fields
		// #################################################################################################

		/// <summary>Tab stop for values when logging instances.</summary>
		protected	static		int		instValueTabStop				= 35;

		/// <summary>Tab stop for types when logging instances.</summary>
		protected	static		int		instTypeTabStop					= 65;


		// #################################################################################################
		// Private/protected fields
		// #################################################################################################

		/// <summary>Buffer to build log messages.</summary>
		protected	static		MString						toolBuf;

		/// <summary>Instance line number counter.</summary>
		protected	static		uint						instLineNumber;

		/// <summary>Instance line number dictionary used to refer to already logged sub objects.</summary>
		protected	static		Dictionary<Object, UInt32>	instObject2LineNumber;

		/// <summary>Instance index of beginning of line in toolBuf.</summary>
		protected	static		int							instLineBeginIdx;

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

	#endif // ALOX_DEBUG || ALOX_REL_LOG


	/** ***********************************************************************************************
	 * <summary>
	 *  Log an exception including inner exceptions recursively. Note: Calls to this  method are
	 *  automatically removed from release code.
	 * </summary>
	 * <param name="domain">	The log domain name. </param>
	 * <param name="level">   	The log level. </param>
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
			try { Lock.Aquire();

				// create/clear toolBuf
				if ( toolBuf == null )
					toolBuf= new MString( 1024 );
				toolBuf.Clear();

				// dump exception to the Buffer
				exception ( e, headline, -1 );

				// if no lox given, use static Log.LOX or, if debug logging is not active, return
				if ( lox == null )
					#if ALOX_DEBUG 
						lox= Log.LOX;
					#else
						return;
					#endif

				// log it using the static Log interface
				lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn);

			} finally { Lock.Release(); } 
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
	 * <param name="domain">		The log domain name. </param>
	 * <param name="level">		  	The log level. </param>
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
			try { Lock.Aquire();

				// if no lox given, use static Log.LOX or, if debug logging is not active, return
				if ( lox == null )
					#if ALOX_DEBUG 
						lox= Log.LOX;
					#else
						return;
					#endif

				#if !(ALOX_WP71 || ALOX_WP8 || ALOX_NO_REFLECTION)

					// dump exception to the Buffer
					instMain( o, maxRecursion, headline );

					// log it using the static Log interface
					lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn );

				#else
					lox.Line ( true, domain, level, "LoxTools.Instance(): Reflection not supported on this platform. ToString(): ", indent );
					lox.Line ( true, domain, level, ( o == null ? "null" : o.ToString()), indent + 1 );
				#endif // NO_REFLECTION

			} finally { Lock.Release(); }
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>	Uses reflection to log an object. </summary>
	 * <param name="level">		  	The log level. </param>
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
		 * <param name="domain">	The log domain name. </param>
		 * <param name="level">	   	The log level. </param>
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
				try { Lock.Aquire();

					// dump exception to the Buffer
					xml( xDocument, headLine );

					// if no lox given, use static Log.LOX or, if debug logging is not active, return
					if ( lox == null )
						#if ALOX_DEBUG 
							lox= Log.LOX;
						#else
							return;
						#endif

					// log it using the static Log interface
					lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn );


				} finally { Lock.Release(); } 
			#endif
		}

		/** ***********************************************************************************************
		 * <summary>
		 *  Log a xml document. Note: Calls to this method are automatically removed from release code.
		 * </summary>
		 * <param name="level">	   	The log level. </param>
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
		 * <param name="domain">	The log domain name. </param>
		 * <param name="level">   	The log level. </param>
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
				try { Lock.Aquire();

					// create/clear toolBuf
					if ( toolBuf == null )
						toolBuf= new MString( 1024 );
					else
						toolBuf.Clear();

					// dump exception to the Buffer
					xmlElement( xElement, headLine, 0 );

					// if no lox given, use static Log.LOX or, if debug logging is not active, return
					if ( lox == null )
						#if ALOX_DEBUG 
							lox= Log.LOX;
						#else
							return;
						#endif

					// log it using the static Log interface
					lox.Line ( true, domain, level, toolBuf, indent, null, csf, cln, cmn );

			
				} finally { Lock.Release(); } 
			#endif
		}

		/** ***********************************************************************************************
		 * <summary>
		 *  Log a xml element. Note: Calls to this method are automatically removed from release code.
		 * </summary>
		 * <param name="level">   	The log level. </param>
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

	#if ALOX_DEBUG || ALOX_REL_LOG
		// #################################################################################################
		// internals
		// #################################################################################################

		/** ***********************************************************************************************
		 * <summary>	Logs an exception. </summary>
		 * <param name="e">			The exception to log. </param>
		 * <param name="headline">	An optional headline string preceding the exception. </param>
		 * <param name="indent">  	The indentation in the output (recursively increased). If set to -1
		 * 							the 'headline' is logged. </param>
		 **************************************************************************************************/
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
				toolBuf.Append( ' ',  indent * 2 ).Append( FmtExcNull );
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

		#if !(ALOX_WP71 || ALOX_WP8 || ALOX_NO_REFLECTION)

			/** ***********************************************************************************************
			 * <summary>
			 *  Logs the header and invokes instRecursive()
			 * </summary>
			 * <param name="o">			  	The object to be logged. </param>
			 * <param name="maxRecursion">	The maximum depth of recursion for logging nested object. </param>
			 * <param name="headLine">	  	The headline to log. </param>
			 **************************************************************************************************/
			protected static void instMain( Object o, int maxRecursion, String headLine) 
			{ 
				// prepare fields
				if ( toolBuf == null )	  toolBuf= new MString( 1024 );
				else					  toolBuf.Clear();

				instLineNumber=			0;
				instLineBeginIdx=		0;
				instObject2LineNumber=  new Dictionary<Object, UInt32>(); 

				// log headline if answer exception
				if ( headLine != null )
					toolBuf.Append( headLine ).Append(' ');

				// dump the object
				instRecursive( o, maxRecursion, headLine != null ? 1 : 0  );

				// dispose the dictionary
				instObject2LineNumber= null; 
			}

			/** ***********************************************************************************************
			 * <summary> Recursively log an instance using reflection. </summary>
			 * <param name="inst">			The element. </param>
			 * <param name="maxRecursion">  	The maximum depth of recursion for logging nested object. </param>
			 * <param name="indent">			The indentation in the output (recursively increased). </param>
			 **************************************************************************************************/
			protected static void instRecursive( Object inst, int maxRecursion, int indent )
			{
				// get type
				Type type=	inst != null	? inst.GetType()
													: null;

				//### 1.  Detect and log value types (or null or sting)
				{
					bool isValueType= false;

					// check for null
					if ( inst == null )
					{
						toolBuf.Append( FmtInstNull );
						isValueType= true;
					}

					// string?
					else if ( type == typeof(String) )
					{
						// add value and type, that's it
						toolBuf	.Append( '\"' ).Append( (String) inst ).Append( '\"' );
						isValueType= true;
					}

					// Char[]
					else if ( type == typeof( Char[]) )
					{
						Char[] charArrayVal= (Char[]) inst;
						String val;

						val=	charArrayVal.Length > 100	?	new String ( charArrayVal, 0, 100) + "..."
															:	new String (charArrayVal );
						if ( val.Contains((char) 0) )
							val= val.Replace((char) 0, ' ' );

						// add value and type, that's it
						toolBuf	.Append( '\"' ).Append( val ).Append( '\"' );

						isValueType= true;
					}

					// value type?
					else if ( type.IsValueType )
					{
						String val= inst.ToString();
						if ( val.Length == 1 && val[0]==(char) 0 )
							val= "\\0";
						else if ( val.Contains((char) 0) )
							val= val.Replace((char) 0, ' ' );

						// add value and type, that's it
						toolBuf	.Append( val );

						isValueType= true;
					}

					// if it was a value type, log type, finish line and return true
					if ( isValueType )
					{
						instTabTypeAndNewLine( type );
						return;
					}
				}

				// ### maximum recursion? ###
				if ( maxRecursion == 0 )
				{
					String vString=	inst.ToString();
					String tString=	type.Namespace + "." + type.Name;

					// often, ToString() just returns the type
					if ( vString.Equals( tString) )
						vString= String.Empty;

					// append "(max rec.)" + value
					toolBuf.Append( FmtInstRecursionLimit ).Append( vString );
					instTabTypeAndNewLine( type );

					return;
				}

				// ### cyclic reference? ###
				uint lineNumber;
				if ( instObject2LineNumber.TryGetValue( inst, out lineNumber ) )
				{
					toolBuf.Append( FmtInstCycRefPrefix ) 
							.Append( lineNumber, 2 )
							.Append( FmtInstCycRefPostfix );
					instTabTypeAndNewLine ( inst.GetType() );
					return;
				}
				// mark object as being logged (in next line)
				instObject2LineNumber.Add( inst, instLineNumber );

				// cast to IEnumerable ( used in arrays and IEnumerables as well )
				IEnumerable enumerableElement= inst as IEnumerable;

				// ### Arrays ###
				if ( type.IsArray )
				{
					// get array, its dimensions and their sizes
					System.Array array= (System.Array) inst;
					int qtyDim= type.GetArrayRank();
					int[]	dimLength= new int[ qtyDim ];

					toolBuf.Append( FmtInstArrayPrefix );  
					for ( int i= 0; i < qtyDim ; i++ ) 
					{
						toolBuf.Append(  dimLength[ i ]= array.GetLength( i ) );
						if ( i != qtyDim - 1 )
							toolBuf.Append( ',' ); 
					}
					toolBuf.Append( FmtInstArrayPostfix );  
					instTabTypeAndNewLine( type );

					// calc 'magnitudes' of dimensions
					int[]	dimMagnitude= new int[ qtyDim ];
					dimMagnitude[ qtyDim - 1 ]= 1;  
					for ( int i= qtyDim - 2 ; i >= 0 ; i-- ) 
						dimMagnitude[ i ]= dimLength[ i + 1 ] * dimMagnitude[ i + 1 ];  

					// loop over all objects
					int		itemNo= 0;
					foreach (object item in enumerableElement)
					{
						instBeginLine( indent );

						// calc indices from itemNo
						toolBuf.Append('[');  
						int idx= itemNo++;
						for ( int i= 0; i < qtyDim ; i++ ) 
						{
							toolBuf.Append( idx / dimMagnitude[ i ] );
							idx=		idx % dimMagnitude[ i ];
							toolBuf.Append( i != qtyDim - 1 ? ',' : ']'); 
						}
						toolBuf.Append(": ");

						// log element
						instRecursive( item, maxRecursion - 1, indent + 1 );
					}
				}

				// ###  IEnumerables ###
				else if (enumerableElement != null)
				{
					// get object count
					int qtyObjects= enumerableElement.Cast<object>().Count();

					// log headline and start new line
					toolBuf.Append( FmtInstIEnumerablePrefix ).Append( qtyObjects ).Append( FmtInstIEnumerablePostfix );
					instTabTypeAndNewLine( type );

					// loop over all objects
					int itemNo= 0;
					foreach (object item in enumerableElement)
					{
						instBeginLine( indent );
						toolBuf.Append( "  " ).Append( itemNo++, 1 ).Append(": ");
						instRecursive( item, maxRecursion - 1, indent + 1 );
					}
				}

				// ### classes ###
				else
				{
					// finish line of object
					instTabTypeAndNewLine( type );

					// loop over fields
					MemberInfo[] members= type.GetMembers( BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance );

					foreach (var memberInfo in members)
					{
						// get type	and value
						Type	fType;
						object	fValue;

						// get field/property info
						FieldInfo		fInfo=	memberInfo as FieldInfo;
						PropertyInfo	pInfo=	memberInfo as PropertyInfo;

							 if ( fInfo != null )
						{
								  fType=		fInfo.FieldType; 
							try { fValue=	fInfo.GetValue(inst); }  catch (Exception) {	fValue= FmtInstNoAccessToValue; }
						}
						else if ( pInfo != null )
						{
								  fType=		pInfo.PropertyType;
							try { fValue=	pInfo.GetValue(inst); }  catch (Exception) {	fValue= FmtInstNoAccessToValue; }
						}

						// not a field or property?
						else
							continue;
				
						// filter "__BackingField"s 
						if ( memberInfo.Name.Contains( "__BackingField" ) )
							continue;

						// begin line and log name
						instBeginLine( indent );
						toolBuf.Append( memberInfo.Name ).Append(':');
						instTabStop( instValueTabStop );

						// recursively log value
						instRecursive( fValue, maxRecursion - 1, indent + 1 );
					}
				}

			}

			/** ***********************************************************************************************
			 * <summary> Adds a new line to the buffer and increases line number counter. </summary>
			 **************************************************************************************************/
			protected static void instNewLine()
			{
				instLineNumber++;
				toolBuf.NewLine();
			}

			/** ***********************************************************************************************
			 * <summary>
			 *  Appends line number (format defined in fields #FmtInstLineNoPrefix and
			 *  #FmtInstLineNoPostfix) and then adds indent characters (defined in field
			 *  #FmtInstIndent).
			 * </summary>
			 * <param name="indent">	The indentation of the line. </param>
			 **************************************************************************************************/
			protected static void instBeginLine( int indent )
			{
				instLineBeginIdx=toolBuf.Length;
				toolBuf.Append( FmtInstLineNoPrefix ).Append( instLineNumber, 2 ).Append( FmtInstLineNoPostfix );
				for ( int i= indent; i > 0; i-- )
					toolBuf.Append( FmtInstIndent ); 
			}

			/** ***********************************************************************************************
			 * <summary> Appends spaces to move to the given tabStop (but at least one). </summary>
			 * <param name="tabStop">	The tab stop position to go to </param>
			 **************************************************************************************************/
			protected static void instTabStop( int tabStop )
			{
				do	{ toolBuf.Append( ' ' ); } while ( toolBuf.Length <= instLineBeginIdx + tabStop  );
			}
	

			/** ***********************************************************************************************
			 * <summary> Appends type information at the end of the line and starts a new line. <summary> 
			 * <param name="type">	The type to append in the log  </param>
			 **************************************************************************************************/
			protected static void instTabTypeAndNewLine( Type type )
			{
				if ( type != null )
				{
					do	{ toolBuf.Append( ' ' ); } while ( toolBuf.Length <= instLineBeginIdx + instTypeTabStop  );
					toolBuf.Append( FmtInstTypePrefix ).Append( type.Name ).Append( FmtInstTypePostfix );
				}
				instNewLine();
			}

		#endif  // !(ALOX_WP71 || ALOX_WP8 || ALOX_NO_REFLECTION)


		#if !ALOX_NO_XML

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
		#endif //(!ALOX_NO_XML)
	#endif  // ALOX_DEBUG || ALOX_REL_LOG
} //class LogTools
} // namespace
