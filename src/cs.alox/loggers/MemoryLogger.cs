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


/** ***********************************************************************************************
 * <summary>
 *  A logger that logs all messages to a in-memory buffer of type MString. The name of the logger
 *  defaults to "MEMORY".
 * </summary>
 **************************************************************************************************/
public class MemoryLogger : TextLogger
{
	// #################################################################################################
	// Empty method stubs for release version (with no release logging)
	// #################################################################################################
	#if !(ALOX_DEBUG || ALOX_REL_LOG)
		public MemoryLogger( String name= "CONSOLE" ){}
	#else
	/**
	 * <summary>
	 *  The logging Buffer. This can be accessed publicly and hence used as you prefer. Especially,
	 *  the whole log can easily be cleared using the MString.Clear(). However, in
	 *  multithreaded environments, locking to the Log interface's mutex should be performed before
	 *  accessing this Buffer. The initial size of the buffer is 8kb.
	 * </summary>
	 */
	public		MString			Buffer							= new MString( 8192 );


	/** ***********************************************************************************************
	 * <summary>	Creates a MemoryLogger with the given name. </summary>
	 * <param name="name">	(Optional) The name of the logger. Defaults to "MEMORY". </param>
	 **************************************************************************************************/
	public MemoryLogger( String	name= "MEMORY" )
	: base( name )
	{
	}

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

		// append message 
		Buffer.Append( msg );
	}


	#endif // ALOX_DEBUG || ALOX_REL_LOG
}
} // namespace
