// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Classes:	Logger
//  File:		Logger.cs											Namespace:  com.aworx.lox.core
// #################################################################################################

using System;
using com.aworx.util;


namespace com.aworx.lox.core {
/** ***********************************************************************************************
 * <summary>
 *  This is central class of the ALox logging implementation. It is **not** recommended to use this 
 *  class directly for logging. Instead, use the simple and convenient static interface class 
 *  Log or, for release logging and other more complex operations use a Lox instance.  
 *  The class is abstract. To implement an own log stream, derive a new Logger class and implement the
 *  abstract method #doLog().>
 * </summary>
 **************************************************************************************************/
public abstract class Logger
{
  #if ALOX_DEBUG || ALOX_REL_LOG

	// #################################################################################################
	// public fields
	// #################################################################################################

	/** <summary>
	 *  The name of the logger. Can be used to receive a reference to it. Logger names are case
	 *  insensitive.
	 * </summary> */
	public	String			Name;

	/** <summary>
	 *		The number of logs actually performed so far. In a text logger this is similar to the line
	 *		number, despite the fact that a single log call can produce more than one line.
	 * </summary> */
	public	uint			CntLogs;

	/// <summary> The creation time of the logger </summary>
	public	TickTime		TimeOfCreation;

	/// <summary> Timestamp of  the last log operation </summary>
	public	TickTime		TimeOfLastLog;

	/// <summary> A flag to disable the logger.</summary>
	public	bool			IsDisabled				= false;

	/// <summary> The root domain "/". </summary> 
	public	LogDomain		RootDomain;

	#endif // ALOX_DEBUG || ALOX_REL_LOG

	#if ALOX_DEBUG || ALOX_REL_LOG


	// #################################################################################################
	#region  __Flags__
	// #################################################################################################
	/// <summary>Enable the logging of source file names. Default is true (enabled) </summary>
	public			bool			LogCallerInfo				= true;
	
	/// <summary>Enable the logging of the date. Default is false (disabled) </summary>
	public			bool			LogDate						= false;
	
	/// <summary>Enable the logging of the (absolute) time. Default is false (disabled) </summary>
	public			bool			LogTimeOfDay				= false; 
	
	/// <summary>Enable the logging of the elapsed time since the logger was started (or reset). Default is true (enabled) </summary>
	public			bool			LogTimeElapsed				= true;
	
	/// <summary>Enable the logging of time difference in milliseconds since last log. Default is true (enabled) </summary>
	public			bool			LogTimeDiff					= true;
	
	/// <summary>Enable the logging of the domain name. Default is true (enabled) </summary>
	public			bool			LogDomainName				= true;

	/// <summary>Enable the logging of the level of a log call. Default is true (enabled) </summary>
	public			bool			LogLogLevel					= true;

	/// <summary>Enable the logging of information about the current thread name. Default is true (enabled)  </summary>
	public			bool			LogThreadInfo				= true;

	/// <summary>Enable the logging of the current log call counter. Default is false (disabled) </summary>
	public			bool			LogLogCounter				= false;
	

	#endregion


	
	// #################################################################################################
	// Internal fields
	// #################################################################################################
	 
	/// <summary> A temporary string used for testing domains</summary>
	protected			MString	tempDomainPath;

	// #################################################################################################
	// Internal fields
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>	Constructs a logger. </summary>
	 * <param name="name">	The name of the logger. </param>
	 **************************************************************************************************/
	protected Logger( String name )

	{
		// save parameters
		this.Name=	name;
		
		// create root domain 
		RootDomain=			new LogDomain( null, null );

		// create buffers
		tempDomainPath=		new MString( 64 );

		// set timestamps to now
		TimeOfCreation=		new TickTime();	  TimeOfCreation.SetToNow();
		TimeOfLastLog=		new TickTime();	  TimeOfLastLog .SetToNow();
	}

	// #################################################################################################
	// Abstract methods to be overwritten
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>
	 *  This is the central method that derived logger classes have to implement to log a message.
	 * </summary>
	 * <param name="domain">	The log domain name. The domain is already checked on this stage and
	 * 							is provided to be able to be logged out only. </param>
	 * <param name="level"> 	The log level. This has been checked to be active already on this
	 * 							stage and is provided to be able to be logged out only. </param>
	 * <param name="msgObject"> The log message object (mostly a String or MString). </param>
	 * <param name="indent">	The indentation in the output. </param>
	 * <param name="caller">	Once compiler generated and passed forward to here. </param>
	 **************************************************************************************************/
	abstract protected void doLog(	MString		domain,		Log.Level	level, 
									Object		msgObject,		int			indent,
									CallerInfo	caller								);


	// #################################################################################################
	// interface
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>
	 *  This method is used to create a domain for the logger. Domains control the activation of log
	 *  lines. If there are more than one unknown domains on the path, all domains are created.
	 * </summary>
	 * <param name="domainPath">	The log domain name with path. </param>
	 * <returns>The new domain. </returns>
	 **************************************************************************************************/
	public LogDomain CreateDomain( MString domainPath )
	{
		// add the domain
		tempDomainPath.Clear().Append( domainPath ).ConvertCase( true );
		LogDomain domain= RootDomain.FindOrCreate( tempDomainPath, true);

		return domain;
	}

	/** ***********************************************************************************************
	 * <summary>	This method is used to find a domain of the logger. </summary>
	 * <param name="domainPath">	The log domain name with path. </param>
	 * <returns>	The new domain. </returns>
	 **************************************************************************************************/
	public LogDomain FindDomain( MString domainPath )
	{
		// add the domain
		tempDomainPath.Clear().Append( domainPath ).ConvertCase( true );
		LogDomain domain= RootDomain.FindOrCreate( tempDomainPath, false );

		return domain;
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  This is the method to log a message. Internally it calls the abstract method doLog() to let
	 *  derived classes perform the log. Note: this method (in fact the whole class) should not be
	 *  used from outside. Instead, the static interface Log should be the right choice for most use
	 *  cases.
	 * </summary>
	 * <param name="domain">	The log domain name. If not starting with a slash ('/')
	 * 							is is appended to any default domain name that might have been specified
	 * 							for the source file. </param>
	 * <param name="level"> 	The log level. This is checked against the level setting of the given
	 * 							domain. </param>
	 * <param name="msgObject"> The log message object (mostly a String or MString). </param>
	 * <param name="indent">	The desired indentation in the output. </param>
	 * <param name="caller">	Once compiler generated and passed forward to here. </param>
	 **************************************************************************************************/
	public void Line(	MString		domain,			Log.Level	level,
						Object		msgObject,			int			indent, 
						CallerInfo	caller)
	{
		// do nothing if we are disabled or domain is not active
		if ( IsDisabled || !checkDomain( domain, level, caller ) )
			return;

		// increase log line counter
		CntLogs++;

		// log the line
		doLog( domain, level, msgObject, indent, caller);

		// get current time	as time of last log (we do this at the end of our log operation!)
		TimeOfLastLog.SetToNow();
	}


	// #################################################################################################
	// Privates/Protecteds 
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>	Check if a given domain is active in respect to the given Log.Level. </summary>
	 * <param name="domain">	The log domain name. If not starting with a slash ('/') this is
	 * 							appended to any default domain name that might have been specified for
	 * 							the source file. </param>
	 * <param name="level"> 	The log level that is checked against given the domains' setting. </param>
	 * <param name="caller">	Once compiler generated and passed forward to here. </param>
	 * <returns>	True if domain is active in respect to the given Log.Level. </returns>
	 **************************************************************************************************/
	protected bool checkDomain( MString domain, Log.Level level, CallerInfo caller )
	{
		// find domain
		tempDomainPath.Clear().Append( domain ).ConvertCase( true );
		LogDomain logDomain= RootDomain.FindOrCreate( tempDomainPath, false );

		// check if existent
		if ( logDomain == null )
		{
			// add domain with default domain level
			logDomain= CreateDomain( domain );

			// inform the if default is All
			if ( logDomain.GetLevel() == Log.DomainLevel.All )
			{
				MString	msg= new MString( 128 );
				msg .Append( "Logger '").Append( Name )
					.Append( "': log domain '" ).Append( domain )
					.Append( "' not found. Created. Inherited domain level is: All ");
				doLog( domain, Log.Level.Verbose, msg, 0, caller);
			}
		}

		// check if active
		return logDomain.IsActive( level );
	}

	#endif // ALOX_DEBUG || ALOX_REL_LOG


} // class Logger

} // namespace
