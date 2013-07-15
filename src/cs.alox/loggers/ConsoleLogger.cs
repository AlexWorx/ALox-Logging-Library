// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:	ConsoleLogger
//  File:	ConsoleLogger.cs											Namespace:  com.aworx.lox
// #################################################################################################

using System;
using System.Runtime.CompilerServices;
using com.aworx.lox.core;
using com.aworx.util;
	

namespace com.aworx.lox.loggers  {
/** ***********************************************************************************************
 * <summary>
 *  A logger that logs all messages to the VStudio IDE output window (*using
 *  System.Diagnostics.Debug.WriteLine()*) and/or to the application console (using
 *  *Console.WriteLine()*).
 *  
 *  The name of the logger defaults to "CONSOLE".
 *  
 *  The constructor sets the level of the root domain, and as such the level of all 'unknown'
 *  domains that inherit from root domain to 'All'. This is because this class represents a logger
 *  that logs into the developer's IDE, and hence just wants to fetch all log domains that the
 *  app and its library uses - unless explicitly set differently in the bootstrap code.  By default,
 *  root domains of loggers have domain level 'Off'.
 * </summary>
 **************************************************************************************************/
public class ConsoleLogger : TextLogger
{
	// #################################################################################################
	// Empty method stubs for release version (with no release logging)
	// #################################################################################################
	#if !(ALOX_DEBUG || ALOX_REL_LOG)

		// Empty constructor
		public ConsoleLogger(	String	name= "CONSOLE",
								String csf="",int cln= 0,String cmn="" )
		{
		}

	#else

	// #################################################################################################
	// fields
	// #################################################################################################
	/// <summary>The prefix for the caller method name </summary>
	public		String			FmtMemberPrefix				=".";

	/// <summary>The postfix for the caller method name  </summary>
	public		String			FmtMemberPostfix				="()";

	/// <summary>Tab position after caller info. This auto adjusts (increases) when 
	/// longer source info occurs. To avoid increases in the beginning, this value
	/// can be set upfront (after the logger was created)</summary>
	public		int				TabAfterSourceInfo				=0;

	/// <summary>Enables logging to the debug window of Visual Studio. Defaults to true.</summary>
	public		bool			EnableVSDebugConsole			=true;

	/// <summary>Enables logging to the application console (std. out). Defaults to false.</summary>
	public		bool			EnableAppConsole				=false;

	// #################################################################################################
	// internal fields
	// #################################################################################################

	/// <summary>VStudio line number format requirements.</summary>
	protected	String			strPrefixLineNumber				="(";

	/// <summary>VStudio line number format requirements.</summary>
	protected	String			strPostfixLineNumber			="):";

	/// <summary>A temporary buffer for assembling the caller info string</summary>
	protected	MString			consoleBuffer					=new MString(256);

	// #################################################################################################
	// Constructors
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>
	 *  Creates a ConsoleLogger. 
	 * </summary>
	 * <param name="name">	(Optional) The name of the logger, defaults to "CONSOLE" </param>
	 **************************************************************************************************/
	public ConsoleLogger(	String	name= "CONSOLE" )
	: base( name )
	{
		// set default domain level to all: As a app console logger/IDE logger we want to fetch all we can
		RootDomain.SetLevel( Log.DomainLevel.All, false );
	}

	// #################################################################################################
	// Abstract interface implementation
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>
	 *  The implementation of the abstract method of parent class TextLogger. Logs messages to the
	 *  application console and/or the VStudio output window.
	 * </summary>
	 * <param name="domain">	The log domain name. </param>
	 * <param name="level">			The log level. This has been checked to be active already on this
	 * 								stage and is provided to be able to be logged out only. </param>
	 * <param name="msg">			The log message. </param>
	 * <param name="indent">		the indentation in the output. Defaults to 0. </param>
	 * <param name="caller">		Once compiler generated and passed forward to here. </param>
	 * <param name="lineNumber">	The line number of a multi-line message, starting with 0. For
	 * 								single line messages this is -1. </param>
	 **************************************************************************************************/
	override protected void doTextLog( 	MString		domain,		Log.Level	level, 
										MString		msg,		int			indent,
										CallerInfo	caller, 	int			lineNumber)
	{
		// check
		if ( !(EnableVSDebugConsole || EnableAppConsole ) )
			return;

		MString output= null;
		
		// no caller info given? Just log msg out (used e.g. by TextLogger for multiline messages )
		if ( caller == null || !(LogCallerSource || LogCallerMethod)  )
		{
			// set output straight to given msg
			output= msg;
		}

		// we cat caller info and the message to our internal buffer 
		else
		{
			// set output to internal buffer
			output= consoleBuffer;

			// clear temp buffer
			consoleBuffer.Clear();

			// build filename/line number in a VStudio clickable format 
			if ( LogCallerSource)
			{
				// add source file: can we cut the source file name by a prefix?
				String sfn=		caller.SourceFileName;
				String cspp=	caller.GetConsumableSourcePathPrefix();
				if ( sfn.StartsWith( cspp, StringComparison.OrdinalIgnoreCase ) )
					consoleBuffer.Append( sfn, cspp.Length, caller.SourceFileName.Length - cspp.Length);
				else
					consoleBuffer.Append( sfn );

				// add line number
				consoleBuffer.Append( strPrefixLineNumber ).Append( caller.LineNumber ).Append( strPostfixLineNumber );
			}

			// append method name
			if ( LogCallerMethod )
			{
				consoleBuffer.Append( FmtMemberPrefix );
				consoleBuffer.Append( caller.MethodName );
				consoleBuffer.Append( FmtMemberPostfix );
			}

			// jump to next tab level
			if ( TabAfterSourceInfo < consoleBuffer.Length )
				TabAfterSourceInfo= consoleBuffer.Length + 5; // add some extra space to avoid too many increases
			for ( int i= consoleBuffer.Length ; i < TabAfterSourceInfo ; i++ )
				consoleBuffer.Append( ' ' );

			// append message
			consoleBuffer.Append( msg );
		}

		// write to console(s)
		#if !ALOX_NO_CONSOLE
			#if !(ALOX_WP71 || ALOX_WP8)
				if ( EnableAppConsole )		{	Console.WriteLine( output.Buffer, 0, output.Length );	}
			#else
				if ( EnableAppConsole )		{	Console.WriteLine( output.ToString() );						}
			#endif
		#endif
		if ( EnableVSDebugConsole )			{	System.Diagnostics.Debug.WriteLine( output.ToString() );		}

	}

#endif // ALOX_DEBUG || ALOX_REL_LOG

} // class ConsoleLogger
} // namespace

