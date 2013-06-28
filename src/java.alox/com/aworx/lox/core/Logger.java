package com.aworx.lox.core;

import com.aworx.lox.Log;
import com.aworx.util.MString;
import com.aworx.util.TickTime;

/**********************************************************************************************//**
 * This is central class of the ALox logging implementation. It is **not** recommended to use
 * this class directly for logging. Instead, use the simple and convenient static interface
 * class Log or, for release logging and other more complex operations use a Lox instance. The
 * class is abstract. To implement an own log stream, derive a new Logger class and implement
 * the abstract method #doLog().>
 **************************************************************************************************/
public abstract class Logger
{
  //#if ALOX_DEBUG || ALOX_REL_LOG

	// #################################################################################################
	// public fields
	// #################################################################################################

	/** The name of the logger. Can be used to receive a reference to it. Logger names are case
	 *  insensitive. */
	public	String			name;

	/** The number of logs actually performed so far. In a text logger this is similar to the line
	 *	number, despite the fact that a single log call can produce more than one line. */
	public	int				cntLogs;

	/** The creation time of the logger */
	public	TickTime		timeOfCreation;

	/** Timestamp of  the last log operation */
	public	TickTime		timeOfLastLog;

	/** A flag to disable the logger.*/
	public	boolean			isDisabled				= false;

	/** The root domain "/" */
	public	LogDomain		rootDomain;

	//#endif // ALOX_DEBUG || ALOX_REL_LOG

	//#if ALOX_DEBUG || ALOX_REL_LOG


	// #################################################################################################
	// #region  __Flags__
	// #################################################################################################
	/**Enable the logging of source file names. Default is true (enabled) */
	public			boolean			logCallerInfo				= true;
	
	/**Enable the logging of the date. Default is false (disabled) */
	public			boolean			logDate						= false;
	
	/**Enable the logging of the (absolute) time. Default is false (disabled) */
	public			boolean			logTimeOfDay				= false; 
	
	/**Enable the logging of the elapsed time since the logger was started (or reset). Default is true (enabled) */
	public			boolean			logTimeElapsed				= true;
	
	/**Enable the logging of time difference in milliseconds since last log. Default is true (enabled) */
	public			boolean			logTimeDiff					= true;
	
	/**Enable the logging of the domain name. Default is true (enabled) */
	public			boolean			logDomainName				= true;

	/**Enable the logging of the level of a log call. Default is true (enabled) */
	public			boolean			logLogLevel					= true;

	/**Enable the logging of the current thread name. Default is true (enabled)  */
	public			boolean			logThreadInfo				= true;

	/**Enable the logging of the current log call counter. Default is false (disabled) */
	public			boolean			logLogCounter				= false;
	
	//#endregion


	
	// #################################################################################################
	// Internal fields
	// #################################################################################################
	 
	/// <summary> A temporary string used for testing domains */
	protected		MString			tempDomainPath;

	// #################################################################################################
	// Internal fields
	// #################################################################################################

    /**********************************************************************************************//**
     * Constructs a logger.
     *
     * @param name  The name of the logger.
     **************************************************************************************************/
	protected Logger( String name )

	{
		// save parameters
		this.name=	name;

		// create root domain 
		rootDomain= 		new LogDomain( null, null );

		// create buffers
		tempDomainPath=		new MString( 64 );

		// set timestamps to now
		timeOfCreation=		new TickTime();	  timeOfCreation.setToNow();
		timeOfLastLog=		new TickTime();	  timeOfLastLog .setToNow();
	}

	// #################################################################################################
	// Abstract methods to be overwritten
	// #################################################################################################

    /**********************************************************************************************//**
     * This is the central method that derived logger classes have to implement to log a message.
     *
     * @param domain    The log domain name. The domain is already checked on this stage and is
     *                  provided to be able to be logged out only.
     * @param level     The log level. This has been checked to be active already on this stage and
     *                  is provided to be able to be logged out only.
     * @param msgObject The log message object (mostly a String or MString).
     * @param indent    The indentation in the output.
     * @param caller    Once compiler generated and passed forward to here.
     **************************************************************************************************/
	abstract protected void doLog(	MString		domain,		Log.Level	level, 
									Object		msgObject,	int			indent,
									CallerInfo	caller								);


	// #################################################################################################
	// interface
	// #################################################################################################

    /**********************************************************************************************//**
     * This method is used to create a domain for the logger. Domains control the activation of log
     * lines. If there are more than one unknown domains on the path, all domains are created.
     *
     * @param domainPath    The log domain name with path.
     *
     * @return  The new domain.
     **************************************************************************************************/
	public LogDomain createDomain( MString domainPath )
	{
		// add the domain
		tempDomainPath.clear().append( domainPath ).convertCase( true );
		LogDomain domain= rootDomain.findOrCreate( tempDomainPath, true);

		return domain;
	}

    /**********************************************************************************************//**
     * This method is used to find a domain of the logger.
     *
     * @param domainPath    The log domain name with path.
     *
     * @return  The new domain.
     **************************************************************************************************/
	public LogDomain findDomain( MString domainPath )
	{
		// add the domain
		tempDomainPath.clear().append( domainPath ).convertCase( true );
		LogDomain domain= rootDomain.findOrCreate( tempDomainPath, false );

		return domain;
	}

    /**********************************************************************************************//**
     * This is the method to log a message. Internally it calls the abstract method doLog() to let
     * derived classes perform the log. Note: this method (in fact the whole class) should not be
     * used from outside. Instead, the static interface Log should be the right choice for most use
     * cases.
     *
     * @param domain    The log domain name. If not starting with a slash ('/')
     *                  is is appended to any default domain name that might have been specified for
     *                  the source file.
     * @param level     The log level. This is checked against the level setting of the given domain.
     * @param msgObject The log message object (mostly a String or MString).
     * @param indent    The desired indentation in the output.
     * @param caller    Once compiler generated and passed forward to here.
     **************************************************************************************************/
	public void line(	MString		domain,			Log.Level	level,
						Object		msgObject,		int			indent, 
						CallerInfo	caller)
	{
		// do nothing if we are disabled or domain is not active
		if ( isDisabled || !checkDomain( domain, level, caller ) )
			return;

		// increase log line counter
		cntLogs++;

		// log the line
		doLog( domain, level, msgObject, indent, caller);

		// get current time
		timeOfLastLog.setToNow();
	}


	// #################################################################################################
	// Privates/Protecteds 
	// #################################################################################################

    /**********************************************************************************************//**
     * Check if a given domain is active in respect to the given Logger.Level.
     *
     * @param domain    The log domain name. If not starting with a slash ('/') this is appended to
     *                  any default domain name that might have been specified for the source file.
     * @param level     The log level that is checked against given the domains' setting.
     * @param caller    Once compiler generated and passed forward to here.
     *
     * @return  True if domain is active in respect to the given Log.Level.
     **************************************************************************************************/
	protected boolean checkDomain( MString domain, Log.Level level, CallerInfo caller )
	{
		// find domain
		tempDomainPath.clear().append( domain ).convertCase( true );
		LogDomain logDomain= rootDomain.findOrCreate( tempDomainPath, false );

		// check if existent
		if ( logDomain == null )
		{
			// add domain with default domain level
			logDomain= createDomain( domain );

			// inform the if default is All
			if ( logDomain.getLevel() == Log.DomainLevel.All )
			{
				MString	msg= new MString( 128 );
				msg .append( "Logger '").append( name )
					.append( "': log domain '" ).append( domain )
					.append( "' not found. Created. Inherited domain level is: All ");
				doLog( domain, Log.Level.Verbose, msg, 0, caller);
			}
		}

		// check if active
		return logDomain.isActive( level );
	}

	//#endif // ALOX_DEBUG || ALOX_REL_LOG


} // class Logger
