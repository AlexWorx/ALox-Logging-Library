package com.aworx.lox.loggers;

import java.io.Console;

import com.aworx.lox.Log;
import com.aworx.lox.core.CallerInfo;
import com.aworx.lox.core.TextLogger;
import com.aworx.util.MString;

/**********************************************************************************************//**
 * A logger that logs all messages to the JAVA console using System.out or alternatively 
 * System.console(). The latter is used if a) the flag #useJAVA6ConsoleIfAvailable is set to
 * true (defaults to true) and b) the system console is available. 
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
	/** Enables logging to *System.console()* if such console is available. This might result in a 
	 * different character encoding (typically on Windows machines). */
	public		boolean			useJAVA6ConsoleIfAvailable		=true;

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
		// write to console or System.out
		Console con= null;
		if ( useJAVA6ConsoleIfAvailable && (con= System.console()) != null )
			con.writer().println( msg.toString() );
		else
			System.out  .println( msg.toString() );
	}
	
	/**********************************************************************************************//**
	 * Empty implementation, not needed for this class
	 *
	 * @param start void    
	 **************************************************************************************************/
	@Override protected void notifyMultiLineOp (boolean start)
	{
	} 
	


//#endif // ALOX_DEBUG || ALOX_REL_LOG

} // class ConsoleLogger
