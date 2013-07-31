package com.aworx.lox.loggers;

import com.aworx.lox.Log;
import com.aworx.lox.core.CallerInfo;
import com.aworx.lox.core.TextLogger;
import com.aworx.util.MString;

/**********************************************************************************************//**
 * A logger that logs all messages to a in-memory buffer of type MString. The name of the logger
 * defaults to "MEMORY".
 **************************************************************************************************/
public class MemoryLogger extends TextLogger
{
	/**
	 *  The logging Buffer. This can be accessed publicly and hence used as you prefer. Especially,
	 *  the whole log can easily be cleared using the MString.Clear(). However, in
	 *  multithreaded environments, locking to the Log interface's mutex should be performed before
	 *  accessing this Buffer. The initial size of the buffer is 8kb.
	 */
	public		MString			buffer							= new MString( 8192 );

    /**********************************************************************************************//**
     * Creates a MemoryLogger with the given name.
     *
     * @param name  The name of the logger. Defaults to "MEMORY".
     **************************************************************************************************/
	public MemoryLogger( String	name )	{ super(name);		}

    /**********************************************************************************************//**
     * Creates a MemoryLogger with the name "MEMORY".
     **************************************************************************************************/
	public MemoryLogger( )				{ super("MEMORY");	}

    /**********************************************************************************************//**
     * The implementation of the abstract method of parent class TextLogger. Logs messages to the
     * Buffer field.
     *
     * @param domain        The log domain name. If not starting with a slash ('/')
     *                      this is appended to any default domain name that might have been specified
     *                      for the source file.
     * @param level         The log level. This has been checked to be active already on this stage
     *                      and is provided to be able to be logged out only.
     * @param msg           The log message.
     * @param indent        the indentation in the output. Defaults to 0.
     * @param caller        Once compiler generated and passed forward to here.
     * @param lineNumber    The line number of a multi-line message, starting with 0. For single line
     *                      messages this is -1.
     **************************************************************************************************/
	@Override protected void doTextLog( MString		domain,		Log.Level	level, 
										MString		msg,		int			indent,
										CallerInfo	caller, 	int			lineNumber)
 	{
		// append new line if buffer has already lines stored
		if ( buffer.length > 0 )
			buffer.newLine();

		// append message 
		buffer.append( msg );
	}
	
	/**********************************************************************************************//**
	 * Empty, not needed here
	 *
	 * @param start void    
	 **************************************************************************************************/
	@Override protected void multiLineOp (boolean start)
	{
	} 
	

} // class MemoryLogger
