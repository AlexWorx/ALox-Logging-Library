package com.aworx.lox.loggers;

import java.io.Console;

import com.aworx.lox.Log;
import com.aworx.lox.core.CallerInfo;
import com.aworx.lox.core.TextLogger;
import com.aworx.util.MString;

/**********************************************************************************************//**
 * A logger that logs all messages to the VStudio IDE output window (**using
 * System.Diagnostics.Debug.WriteLine()**) and/or to the application console (using
 * **Console.WriteLine()**).
 * 
 * The name of the logger defaults to "CONSOLE". In the Eclipse IDE, log lines are double-clickable
 * to jump directly to the source code that generated the log.
 * 
 * The constructor sets the level of the root domain, and as such the level of all 'unknown'
 * domains that inherit from root domain to 'All'. This is because this class represents a logger
 * that logs into the developer's IDE, and hence just wants to fetch all log domains that the
 * app and its library uses - unless explicitly set differently in the bootstrap code.  By default,
 * root domains of loggers have domain level 'Off'.
 **************************************************************************************************/
public class ConsoleLogger extends TextLogger
{
	// #################################################################################################
	// fields
	// #################################################################################################
	/** Tab position after caller info. This auto adjusts (increases) when longer source info occurs. To
	*   avoid increases in the beginning, this value can be set upfront (after the logger was created) */
	public		int				tabAfterSourceInfo				=0;

	/** Enables logging to the application console (System.out respectively System.console(), see
	 * useJAVA6ConsoleIfAvailable). Defaults to true. */
	public		boolean			enableAppConsole				=true;

	/** Enables logging to *System.console()* if such console is available. This might result in a 
	 * different character encoding (typically on Windows machines). */
	public		boolean			useJAVA6ConsoleIfAvailable		=true;

	// #################################################################################################
	// internal fields
	// #################################################################################################

	/** A temporary buffer for assembling the caller info string */
	protected	MString			consoleBuffer					=new MString(256);

	// #################################################################################################
	// Constructors
	// #################################################################################################

    /**********************************************************************************************//**
     * Creates a ConsoleLogger with the given name.
     *
     * @param name  The name of the logger, defaults to "CONSOLE".
     **************************************************************************************************/
	public ConsoleLogger( String	name )
	{
		super( name );

		// set default domain level to all: As a app console logger/IDE logger we want to fetch all we can
		rootDomain.setLevel( Log.DomainLevel.ALL, false );
	}

    /**********************************************************************************************//**
     * Creates a ConsoleLogger with the name "CONSOLE".
     **************************************************************************************************/
	public ConsoleLogger( )
	{
		super( "CONSOLE" );

		// set default domain level to all: As a app console logger/IDE logger we want to fetch all we can
		rootDomain.setLevel( Log.DomainLevel.ALL, false );
	}


	// #################################################################################################
	// Abstract interface implementation
	// #################################################################################################

    /**********************************************************************************************//**
     * The implementation of the abstract method of parent class TextLogger. Logs messages to the
     * application console.
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
										CallerInfo	caller, 	int			lineNumber )
	{
		// check
		if ( !( enableAppConsole ) )
			return;

		MString output= null;
		
		// no caller info given? Just log msg out (used e.g. by TextLogger for multiline messages )
		if ( caller == null || !logCallerInfo  )
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
			consoleBuffer.clear();
	
			// build filename/line number in a VStudio clickable format 
			consoleBuffer.append( caller.packageName );
			consoleBuffer.append( '.' );
			consoleBuffer.append( caller.className );
			consoleBuffer.append( '.' );
			consoleBuffer.append( caller.methodName );
			consoleBuffer.append( '(' );
			consoleBuffer.append( caller.fileNameAndLineNumber);
			consoleBuffer.append( ')' );
	
			// jump to next tab level
			if ( tabAfterSourceInfo < consoleBuffer.length )
				tabAfterSourceInfo= consoleBuffer.length + 5; // add some extra space to avoid to many increases
			for ( int i= consoleBuffer.length ; i < tabAfterSourceInfo ; i++ )
				consoleBuffer.append( ' ' );
		
			// append message
			consoleBuffer.append( msg );
		}
		
		// write to console(s)
		if ( enableAppConsole )		
		{
			Console con= null;
			if ( useJAVA6ConsoleIfAvailable && (con= System.console()) != null )
{			
				con.writer().println( output.toString() );
System.out.println("Using Console");				
}				
			else
				System.out  .println( output.toString() );
		}
	}

//#endif // ALOX_DEBUG || ALOX_REL_LOG

} // class ConsoleLogger
