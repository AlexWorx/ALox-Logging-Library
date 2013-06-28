package com.aworx.lox.android;

import com.aworx.util.MString;
import com.aworx.lox.core.CallerInfo;
import com.aworx.lox.core.TextLogger;
import com.aworx.lox.Log;

/**********************************************************************************************//**
 * A logger that logs all messages to the Android LogCat (**using * android.util.Log.e()/w()...**) 
 * 
 * The name of the logger defaults to "LOGCAT". In the Eclipse IDE, log lines are double-clickable
 * to jump directly to the source code that generated the log.
 * 
 * 
 * The constructor sets the level of the root domain, and as such the level of all 'unknown'
 * domains that inherit from root domain to 'All'. This is because this class represents a logger
 * that logs into the developer's IDE, and hence just wants to fetch all log domains that the
 * app and its library uses unless explicitly set differently in the bootstrap code.  By default,
 * root domains of loggers have domain level 'Off'.
 **************************************************************************************************/
public class AndroidLogCatLogger extends TextLogger
{
	// #################################################################################################
	// fields
	// #################################################################################################
	
	/** The prefix for the caller method name */
	public		String			FMT_CallerInfoPrefix					="<<< at ";

	/** The log category that is passed to LogCat. If this is set to null, the ALox domain name
		is passed. The advantage of having one fixed LogCat category is that you can filter by it within
		your IDE's LogCat view to see exclusively ALox messages. On the other hand, if the ALox domain 
		name is used as the LogCat category, than you can use the LogCat view to filter ALox messages.
		Default is "ALox". If you set this to null to switch to the other mode, be sure to set 
		field LogDomainName to false, to disable duplicate domain name output. */
	public		String			logCategory								="ALox";
	
	/** Flag to indicate whether ALox Log.Level.Verbose should be logged using android.util.Log.d
		or android.util.Log.v. Defaults to true, hence LogCat debug messages are used.   */
	public		boolean			verboseIsDebug						= true;

	// #################################################################################################
	// internal fields
	// #################################################################################################

	/** A temporary buffer for assembling the caller info string*/
	protected	MString			consoleBuffer					=new MString(256);

	// #################################################################################################
	// Constructors
	// #################################################################################################


	/**********************************************************************************************//**
	 *  Creates an AndroidLogCatLogger with the given name. 
     * @param name  The name of the logger, defaults to "LOGCAT".
	 **************************************************************************************************/
	public AndroidLogCatLogger(	String	name )
	{
		super( name );
		
		//LogDomainName=
		logDate=
		logLogLevel=
		logThreadInfo=		 false;
		
		// set default domain level to all: As a app console logger/IDE logger we want to fetch all we can
		rootDomain.setLevel( Log.DomainLevel.All, false );
	}
	
	/**********************************************************************************************//**
	 *  Creates an AndroidLogCatLogger with name "LOGCAT". 
	 **************************************************************************************************/
	public AndroidLogCatLogger( )	{	super( "LOGCAT" );	}


	// #################################################################################################
	// Abstract interface implementation
	// #################################################################################################

	/**********************************************************************************************//**
	 *  The implementation of the abstract method of parent class TextLogger. Logs messages to 
	 *  android LogCat (which might be an IDE window)
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
		// clear temp Buffer
		consoleBuffer.clear();

		// write message  
		consoleBuffer.append( msg );
		
		// build filename/line number in a VStudio clickable format 
		if ( lineNumber <= 0 && logCallerInfo && caller != null )
		{
			consoleBuffer.tab( 20, 0, 3 );
			consoleBuffer.append( FMT_CallerInfoPrefix );
			consoleBuffer.append( caller.packageName );
			consoleBuffer.append( '.' );
			consoleBuffer.append( caller.className );
			consoleBuffer.append( '.' );
			consoleBuffer.append( caller.methodName );
			consoleBuffer.append( '(' );
			consoleBuffer.append( caller.fileNameAndLineNumber);
			consoleBuffer.append( ')' );
		}

		// log it out
		String logCat=		logCategory == null ? domain.toString() : logCategory;
		String logCatMsg=	consoleBuffer.toString();
			 if ( level == Log.Level.Error )		{	android.util.Log.e( logCat, logCatMsg );	} 
		else if ( level == Log.Level.Warning )		{	android.util.Log.w( logCat, logCatMsg );	} 
		else if ( level == Log.Level.Info )			{	android.util.Log.i( logCat, logCatMsg );	} 
		else {	if (verboseIsDebug)					{	android.util.Log.d( logCat, logCatMsg );	} 
				else								{	android.util.Log.v( logCat, logCatMsg );	}
			 }
	}

//#endif // ALOX_DEBUG || ALOX_REL_LOG

} // class ConsoleLogger
