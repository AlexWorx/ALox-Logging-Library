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
		public ConsoleLogger( String name= "CONSOLE" ){}
	#else

	/// <summary>Enables logging to the debug window of Visual Studio. Defaults to true.</summary>
	public		bool			EnableVSDebugConsole			= true;

	/// <summary>Enables logging to the application console (std. out). Defaults to false.</summary>
	#if !ALOX_NO_CONSOLE	
	  public		bool		EnableAppConsole				= false;
	#endif

	/// <summary>A temporary buffer for assembling the caller info string</summary>
	protected	MString			consoleBuffer					= new MString(256);

	/** ***********************************************************************************************
	 * <summary>
	 *  Creates a ConsoleLogger. 
	 * </summary>
	 * <param name="name">	(Optional) The name of the logger, defaults to "CONSOLE" </param>
	 **************************************************************************************************/
	public ConsoleLogger( String name= "CONSOLE" )
	: base( name )
	{
		// set default domain level to all: As a app console logger/IDE logger we want to fetch all we can
		RootDomain.SetLevel( Log.DomainLevel.All, false );
	}

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


		// write to console(s)
		#if !ALOX_NO_CONSOLE
			#if !(ALOX_WP71 || ALOX_WP8)
				if ( EnableAppConsole )		{	Console.WriteLine( msg.Buffer, 0, msg.Length );	}
			#else
				if ( EnableAppConsole )		{	Console.WriteLine( msg.ToString() );						}
			#endif
		#endif
		if ( EnableVSDebugConsole )			{	System.Diagnostics.Debug.WriteLine( msg.ToString() );		}

	}

#endif // ALOX_DEBUG || ALOX_REL_LOG
} // class ConsoleLogger
} // namespace

