package com.aworx.lox;

import java.util.*;

import com.aworx.lox.core.*;
import com.aworx.util.*;

/**************************************************************************************************
 * A logger that logs all messages to the VStudio IDE output window (**using
 * System.Diagnostics.Debug.WriteLine()**) and/or to the application console (using
 * **Console.WriteLine()**).
 * 
 * The name of the logger defaults to "CONSOLE".
 * 
 * The constructor sets the level of the root domain, and as such the level of all 'unknown'
 * domains that inherit from root domain to 'All' This is because this class represents a logger
 * that logs into the developer's IDE, and hence just wants to fetch all log domains that the
 * app and its library uses unless explicitly set differently in the bootstrap code.  By default,
 * root domains of loggers have domain level 'Off'.
 **************************************************************************************************/
public class ConsoleLogger extends TextLogger
{
	// #################################################################################################
	// Empty method stubs for release version (with no release logging)
	// #################################################################################################
	//#if !(ALOX_DEBUG || ALOX_REL_LOG)

	//#else

	// #################################################################################################
	// fields
	// #################################################################################################
	/** Tab position after caller info. This auto adjusts (increases) when longer source info occurs. To
	*   avoid increases in the beginning, this value can be set upfront (after the logger was created) */
	public		int				tabAfterSourceInfo				=0;

	/** Enables logging to the debug window of Visual Studio. Defaults to false. */
	public		boolean			enableVSDebugConsole			=false;

	/** Enables logging to the application console (System.out). Defaults to true. */
	public		boolean			enableAppConsole				=true;

	// #################################################################################################
	// internal fields
	// #################################################################################################

	/** A temporary buffer for assembling the caller info string */
	protected	MString			consoleBuffer					=new MString(256);

	// #################################################################################################
	// Constructors
	// #################################################################################################

    /**************************************************************************************************
     * Creates a ConsoleLogger with the given name.
     *
     * @param name  The name of the logger, defaults to "CONSOLE".
     **************************************************************************************************/
	public ConsoleLogger( String	name )
	{
		super( name );

		// set default domain level to all: As a app console logger/IDE logger we want to fetch all we can
		rootDomain.setLevel( Log.DomainLevel.All, false );
	}

    /**************************************************************************************************
     * Creates a ConsoleLogger with the name "CONSOLE".
     **************************************************************************************************/
	public ConsoleLogger( )
	{
		super( "CONSOLE" );

		// set default domain level to all: As a app console logger/IDE logger we want to fetch all we can
		rootDomain.setLevel( Log.DomainLevel.All, false );
	}


	// #################################################################################################
	// Abstract interface implementation
	// #################################################################################################

    /**************************************************************************************************
     * The implementation of the abstract method of parent class TextLogger. Logs messages to the
     * application console and/or the VStudio output window.
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
		if ( !(enableVSDebugConsole || enableAppConsole ) )
			return;

		// no caller info given? Just log msg out (used e.g. by TextLogger for multiline messages )
		if ( caller == null )
		{
			//#if !ALOX_NO_CONSOLE
				if ( enableAppConsole )		{	System.out.println( msg.toString() );	}
			//#endif
			if ( enableVSDebugConsole )		{		} //NIY

			// that's it then!
			return;
		}


		// clear temp Buffer
		consoleBuffer.clear();

		// build filename/line number in a VStudio clickable format 
		if ( logCallerInfo )
		{
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
		}
	
		// write to consoles
		consoleBuffer.append( msg );
		
		//#if !ALOX_NO_CONSOLE
			if ( enableAppConsole )		{	System.out.println( consoleBuffer.toString() );	} 
		//#endif
		if ( enableVSDebugConsole )		{		} //NIY
		
	}

//#endif // ALOX_DEBUG || ALOX_REL_LOG

} // class ConsoleLogger
