package com.aworx.lox.android;

import com.aworx.util.MString;
import com.aworx.lox.core.CallerInfo;
import com.aworx.lox.core.TextLogger;
import com.aworx.lox.Log;

/**********************************************************************************************//**
 * A logger that logs all messages to the Android LogCat (**using * android.util.Log.e()/w()...**) 
 * There are two options to use the LogCat "Tag" concept together with the ALox "Log Domain" 
 * concept. See public field #logTag for more information. 
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
	
	/** The log tag that is passed to LogCat. If this is set to null, the ALox domain name
		is passed instead. The advantage of having one fixed LogCat tag value for all ALox messages is that 
		you can filter that tag within your IDE's LogCat view to see exclusively ALox messages. 
		On the other hand, if the ALox domain name is used as the LogCat category, than you can use the 
		LogCat view to filter ALox messages.
		Default value is "ALox". If you set this to null to switch to the other mode, be sure to set 
		field LogDomainName to false, to disable duplicate domain name output. */
	public		String			logTag								= "ALox";
	
	/** Tab position after caller info. This auto adjusts (increases) when longer source info occurs. To
	*   avoid increases in the beginning, this value can be set upfront (after the logger was created) */
	public		int				tabAfterCallerInfo					= 0;

	/** Tab position before the caller name. This auto adjusts (increases) when longer source info occurs. To
	*   avoid increases in the beginning, this value can be set upfront (after the logger was created) */
	public		int				tabBeforeCallerName				=0;

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
		rootDomain.setLevel( Log.DomainLevel.ALL, false );
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
		MString output;
		
		// no caller info given? Just log msg out (used e.g. by TextLogger for multi line messages )
		if ( caller == null || !( logCallerSource || logCallerMethod || logCallerClass || logCallerPackage ) )
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
			output.clear();
	
			// append clickable source info
			if ( logCallerSource )	
				output.append( "at " ).append( '(' ).append( caller.fileNameAndLineNumber).append( ')' );

			// append package/class/method info
			if( logCallerMethod || logCallerClass || logCallerPackage )
			{
				// jump to next tab level
				output.append( ' ' );
				if ( tabBeforeCallerName < output.length )
					tabBeforeCallerName= output.length; // add some extra space to avoid to many increases
				output.append( ' ', tabBeforeCallerName - output.length  );

				if ( logCallerPackage )	output				.append( caller.packageName ).append( '.' );
				if ( logCallerClass   )	output				.append( caller.className   );	
				if ( logCallerMethod  )	output.append( '.' ).append( caller.methodName  ).append( '(' ).append( ')' );
			}
			
			if ( tabAfterCallerInfo <= output.length )
				tabAfterCallerInfo= output.length + 3; // add some extra space to avoid to many increases
			output.append( ' ', tabAfterCallerInfo - output.length  );
		
		
			// append message
			consoleBuffer.append( msg );
		}
		

		// log it out
		String logCat=		logTag == null ? domain.toString() : logTag;
		String logCatMsg=	output.toString();
			 if ( level == Log.Level.ERROR )		{	android.util.Log.e( logCat, logCatMsg );	} 
		else if ( level == Log.Level.WARNING )		{	android.util.Log.w( logCat, logCatMsg );	} 
		else if ( level == Log.Level.INFO )			{	android.util.Log.i( logCat, logCatMsg );	} 
		else {	if (verboseIsDebug)					{	android.util.Log.d( logCat, logCatMsg );	} 
				else								{	android.util.Log.v( logCat, logCatMsg );	} }
	}

//#endif // ALOX_DEBUG || ALOX_REL_LOG

} // class ConsoleLogger
