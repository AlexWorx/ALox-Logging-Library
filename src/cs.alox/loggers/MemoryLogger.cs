// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:	MemoryLogger
//  File:	MemoryLogger.cs												  Namespace:  com.aworx.lox
// #################################################################################################
using System;
using System.Runtime.CompilerServices;
using com.aworx.lox.core;
using com.aworx.util;

namespace com.aworx.lox.loggers {

#if ALOX_DEBUG || ALOX_REL_LOG

/** ***********************************************************************************************
 * <summary>
 *  A logger that logs all messages to a in-memory buffer of type MString. The name of the logger
 *  defaults to "MEMORY".
 * </summary>
 **************************************************************************************************/
public class MemoryLogger : TextLogger
{
	// #################################################################################################
	// fields
	// #################################################################################################

	/**
	 * <summary>
	 *  The logging Buffer. This can be accessed publicly and hence used as you prefer. Especially,
	 *  the whole log can easily be cleared using the MString.Clear(). However, in
	 *  multithreaded environments, locking to the Log interface's mutex should be performed before
	 *  accessing this Buffer. The initial size of the buffer is 8kb.
	 * </summary>
	 */
	public		MString			Buffer							= new MString( 8192 );

	/// <summary>The prefix for the caller method name </summary>
	public		String			FormatMemberPrefix				=".";

	/// <summary>The postfix for the caller method name  </summary>
	public		String			FormatMemberPostfix				="()";

	/**
	 * <summary>
	 *  Tab position after caller info. This auto adjusts (increases) when longer source info occurs.
	 *  To avoid increases in the beginning, this value can be set upfront (after the logger was
	 *  created)
	 * </summary>
	 */
	public		int				TabAfterSourceInfo				=0;

	// #################################################################################################
	// internal fields
	// #################################################################################################
	/// <summary>Prefix printed before line number.</summary>
	protected	String			strPrefixLineNumber				="(";

	/// <summary>Prefix printed before line number.</summary>
	protected	String			strPostfixLineNumber			="):";

	// #################################################################################################
	// Constructors
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>	Creates a MemoryLogger with the given name. </summary>
	 * <param name="name">	(Optional) The name of the logger. Defaults to "MEMORY". </param>
	 **************************************************************************************************/
	public MemoryLogger( String	name= "MEMORY" )
	: base( name )
	{
	}

	// #################################################################################################
	// Abstract interface implementation
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>
	 *  The implementation of the abstract method of parent class TextLogger. Logs messages to the
	 *  Buffer field.
	 * </summary>
	 * <param name="domain">		The log domain name. </param>
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
		// append new line if buffer has already lines stored
		if ( Buffer.Length > 0 )
			Buffer.NewLine();

		// build filename/line number in a VStudio clickable format 
		if ( caller != null && LogCallerInfo )
		{
			// get actual length once
			int oldLength= Buffer.Length;

			// add source file: can we cut the source file name by a prefix?
			String sfn=		caller.SourceFileName;
			String cspp=	caller.GetConsumableSourcePathPrefix();
			if ( sfn.StartsWith( cspp, StringComparison.OrdinalIgnoreCase ) )
				Buffer.Append( sfn, cspp.Length, caller.SourceFileName.Length - cspp.Length);
			else
				Buffer.Append( sfn );

			// add line number
			Buffer.Append( strPrefixLineNumber )
					.Append( caller.LineNumber )
				  .Append( strPostfixLineNumber );

			// append method name
			Buffer.Append( FormatMemberPrefix );
			Buffer.Append( caller.MethodName );
			Buffer.Append( FormatMemberPostfix );

			// jump to next tab level
			if ( TabAfterSourceInfo < Buffer.Length - oldLength )
				TabAfterSourceInfo= Buffer.Length - oldLength + 5; // add some extra space to avoid too many increases
			for ( int i= Buffer.Length - oldLength ; i < TabAfterSourceInfo ; i++ )
				Buffer.Append( ' ' );
		}

		// append message 
		Buffer.Append( msg );
	}

}

#endif // ALOX_DEBUG || ALOX_REL_LOG

} // namespace
