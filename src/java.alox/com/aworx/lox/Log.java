package com.aworx.lox;

import java.util.Date;

import com.aworx.lox.core.Logger;
import com.aworx.util.AWXU;
import com.aworx.util.AWXUErrorHandler;


/**********************************************************************************************//**
 * <summary>
 *  This class acts as a container for Loggers and provides a convenient interface into them.
 *  Features are:
 *  
 *  a) Store and log into one or several Logger instances at once b) Thread safeness c) Store and
 *  use of default domain names  
 *  d) Store and manage caller information  
 *  d) Provides shortcuts to frequently used logging tasks.  
 *  e) Store "code markers" and retrieve for simple tracing in log statements  
 *  f) Count log operations  
 *  
 *  This class is 100% not static. In standard log scenarios, it is recommend **not** to use this
 *  class, but to use Log instead, which is a 100% static wraper around this one. In other words,
 *  Log incorporates one static instance of this class and mirrors the whole interface with
 *  static methods.
 *  
 *  Furthermore, all invocations of methods of Log are pruned in release code, while invocations
 *  of methods of Lox not. Hence, this class and interface should be used in release log 
 *  scenarios. Of course, the use of class Log and Lox can be mixed, to enable debug log output
 *  in parallel to relase output.
 * </summary>
 **************************************************************************************************/
public abstract class Log
{
	// #################################################################################################
	// Public Enums
	// #################################################################################################

	/**********************************************************************************************//**
	 * These are the levels of log verbosity assignable to a log domain.
	 **************************************************************************************************/
	public enum DomainLevel
	{
		/** Do not log anything. */
		Off,	

		/** Log only level Error. */
		Errors,

		/** Log only levels Warning or Error. */
		WarningsAndErrors,

		/** Log all  levels but Verbose. */
		InfoWarningsAndErrors,

		/** Log all. */								
		All,	

		/** Inherit level from parent domain. */
		Inherit,	
	}


	/**********************************************************************************************//**
	 * These are the levels of log verbosity used in a log call.
	 **************************************************************************************************/
	public enum Level
	{
		/** The most verbose log level to be used for debug output statements. Logged only if
			the domains log level is set to DomainLevel.All. */
		Verbose,

		/** The standard log level for normal log output statements. Logged if the domains
			level is either DomainLevel.All or DomainLevel.InfoWarningsAndErrors. */
		Info,

		/** A log level for warning messages, hence things that might lead to errors or are not
			welcome for other reasons, but maybe are not errors. 
			It is not logged only if the domains log level is DomainLevel.Errors orLogDomain.Level.Off. */
		Warning,

		/** A log level for (severe) error messages.
			It is suppressed only if the domains log level is set to DomainLevel.Off. */
		Error,
	}

	/**********************************************************************************************//**
	 * These are definitions which are used as a parameter to certain ALox methods to determine the
	 * breadth of the scope of a setting. The definitions are platform dependent. E.g. in C# the
	 * scope can be "method" or "source" file while in JAVA it can be "package", "class" or
	 * "method". The difference is due to different mechanisms to automatically collect caller
	 * information.
	 **************************************************************************************************/
	public enum Scope
	{
		/** No scope should be applied/affected. */
		None,

		/** Defines the actual package as the scope. */
		Package,

		/** Defines the actual class as the scope. */
		Class,

		/** Defines the actual method as the scope. */
		Method,
	}


	// #################################################################################################
	// Public static fields
	// #################################################################################################

	/** The loggers. At least one logger (e.g. ConsoleLogger) needs to be created. */
	public	static		Lox								LOX=	new Lox();

	// #################################################################################################
	// Implement and set A-Worx Util Error Handler 
	// #################################################################################################

    /**********************************************************************************************//**
     * Static constructor that declares a local class that implements the AWXUErrorHandler interface
     * and assigns an instance of this class to the error handler singleton on AWXU.
     **************************************************************************************************/
	static
	{
		class	ALoxAWXUErrorHandler implements AWXUErrorHandler
		{
			@Override public void error  ( Object msg )	{ Log.error	 ( "AWXU", msg ); }
			@Override public void warning( Object msg )	{ Log.warning( "AWXU", msg ); }
		}
		
		AWXU.errorHandler= new ALoxAWXUErrorHandler();
	}
	


	// #################################################################################################
	// Interface (not auto removed)
	// #################################################################################################

	/**********************************************************************************************//**
	 * Retrieve an instance of a Logger by its name. Note: This function is not automatically
	 * removed from the release code because of technical restrictions. It has to be conditionally
	 * compiled by enclosing calls to it with "//#if ... //#endif" statements.
	 *
	 * @param loggerName    The name of the logger to search for (case insensitive)
	 *
	 * @return  The logger, null if not found.
	 **************************************************************************************************/
	public static Logger getLogger( String loggerName )		{ return LOX.getLogger( loggerName ); }


	// #################################################################################################
	// Interface (auto removed)
	// #################################################################################################

	/**********************************************************************************************//**
	 * This method should not be used in normal applications. It was added to support clean unit
	 * testing. This method disposes the internal static Lox and with it all loggers, preferences
	 * and stuff and replaces it with a fresh one.
	 **************************************************************************************************/
	public static void reset()
	{
		LOX= new Lox();
	}

	/**********************************************************************************************//**
	 * Adds a logger to the Log interface. Each log call that is performed through this interface
	 * will be forwarded to this logger, unless filtered out with optional filter parameter. The
	 * logger will then check it's domain level against the given log level to decide weather a log
	 * should performed.
	 *
	 * @param logger                The logger to be added.
	 **************************************************************************************************/
	public static void addLogger( Logger logger )										{ LOX.addLogger( logger, Log.DomainLevel.WarningsAndErrors ); }

	/**********************************************************************************************//**
	 * Adds a logger to the Log interface. Each log call that is performed through this interface
	 * will be forwarded to this logger, unless filtered out with optional filter parameter. The
	 * logger will then check it's domain level against the given log level to decide weather a log
	 * should performed.
	 *
	 * @param logger                The logger to be added.
	 * @param internalDomainLevel   The desired domain level for the #com.aworx.lox.Lox.internalDomain 
	 *                              which is used for logging code of class Lox itself. For console loggers 
	 *                              this can be set to **All**, for log streams dedicated to a certain
	 *                              domain, this should be set to **Off**.
	 **************************************************************************************************/
	public static void addLogger( Logger logger, Log.DomainLevel internalDomainLevel )	{ LOX.addLogger( logger, internalDomainLevel ); }

	/**********************************************************************************************//**
	 * Removes all loggers that match the filter name from this  interface.
	 *
	 * @param loggerFilter  A filter for the loggers to be affected. A simple string compare without
	 *                      case sensitivity is performed. An asterisk ('*') at the beginning or end
	 *                      of the string is used as a wildcard. Defaults to null which causes all
	 *                      loggers to be removed.
	 **************************************************************************************************/
	public static void removeLoggers( String loggerFilter )								{ LOX.removeLoggers( loggerFilter ); }

	/**********************************************************************************************//**
	 * Removes all loggers this interface.
	 **************************************************************************************************/
	public static void removeLoggers(  ) 													{ LOX.removeLoggers( null ); } 

	/**********************************************************************************************//**
	 * This method is used to define a log domain. The method is usually invoked within the same
	 * source "context" (aka, class, namespace, package, etc.) that later on uses the domain to
	 * perform log statements. Often, calls to this functions are placed in static constructors or
	 * similar code that is executed only once and very early in the lifecycle of a process.
	 * 
	 * Each log statement refers to such a domain which can be used specifically for different parts
	 * of your application like assemblies, libraries, namespaces, specific code files or even for a
	 * single method. The domain name should be short, pregnant and self explaining.
	 * 
	 * Domains can be created with path separators '/', for example 'COMM/SOCK' could be the domain
	 * in a socket class, residing within a communication library. The advantage of creating paths
	 * and this way "sub domains", is that a whole bunch of logging domains can be altered (on/off)
	 * by just altering the root domain.
	 * 
	 * If a domain and path is given that is not known already, then the whole path of domains is
	 * created.
	 * 
	 * If the parameter **scope** is provided with a value not equal to Log.Scope.None, the given
	 * domain becomes the default domain for respective scope. For any subsequent log calls from
	 * within this scope, where no domain is explicitly given, this default domain is used. If
	 * subsequent log calls specify a domain name with a leading '~' character, then such domain is
	 * concatenated to the default domain to build a complete domain path.
	 *
	 * @param domain    The domain name (and path) to register. If this is starting with a swung dash
	 *                  ('~') this is interpreted a sub domain to a (potentially already set!) default
	 *                  domain of the source file. For other values, the default    domain is ignored
	 *                  (regardless if this is starting with a slash or not).
	 * @param scope     If a value other than Log.Scope.None is provided, the given domain name is
	 *                  registered as the default domain for the given scope. Default domains set for
	 *                  'inner scopes' have higher priority than those set for outer scopes. Available
	 *                  Scope definitions are platform/language dependent.
	 **************************************************************************************************/
	public static void regDomain( String domain,	 Log.Scope scope )	 			{ LOX.regDomain( domain, scope ); }	

	/**********************************************************************************************//**
	 * Sets the domain log level and (by default) all it's sub domains recursively. In the case that
	 * sub domains should be set to a different log level, then this function has to be called for
	 * such sub domains after the call to the parent domain (or recursion has to be switched off,
	 * using the parameter 'recursive'). It is not necessary to register a domain before setting its
	 * log level and log levels can be set and modified any time.
	 *
	 * @param domain        If this is null, the default domain is used. If this is starting with a
	 *                      swung dash ('~') this is interpreted a sub domain to the default domain
	 *                      of the source file. For other values, the default domain is ignored
	 *                      (regardless if this is starting with a slash or not).
	 * @param domainLevel   The domains log level to be set.
	 * @param recursive     Set sub domains recursively. Defaults to true.
	 * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
	 *                      loggers to have different domains and log levels. A simple string compare
	 *                      without case sensitivity is performed. An asterisk ('*') at the beginning
	 *                      or end of the string is used as a wildcard. Leave null if all loggers
	 *                      should be affected. Use this parameter only in more complex logging
	 *                      scenarios.
	 **************************************************************************************************/
	public static void setDomain(	String domain, Log.DomainLevel domainLevel, boolean recursive, String loggerFilter) { LOX.setDomain( domain, domainLevel, recursive, loggerFilter); }

	/**********************************************************************************************//**
	 * Sets the domain log level and (by default) all it's sub domains recursively. In the case that
	 * sub domains should be set to a different log level, then this function has to be called for
	 * such sub domains after the call to the parent domain (or recursion has to be switched off,
	 * using the parameter 'recursive'). It is not necessary to register a domain before setting its
	 * log level and log levels can be set and modified any time.
	 *
	 * @param domain        If this is null, the default domain is used. If this is starting with a
	 *                      swung dash ('~') this is interpreted a sub domain to the default domain
	 *                      of the source file. For other values, the default domain is ignored
	 *                      (regardless if this is starting with a slash or not).
	 * @param domainLevel   The domains log level to be set.
	 * @param recursive     Set sub domains recursively. Defaults to true.
	 **************************************************************************************************/
	public static void setDomain(	String	domain,	Log.DomainLevel	domainLevel, boolean recursive )					{ LOX.setDomain( domain, domainLevel, recursive, null ); } 

	/**********************************************************************************************//**
	 * Sets the domain log level and all it's sub domains recursively. In the case that sub domains
	 * should be set to a different log level, then this function has to be called for such sub
	 * domains after the call to the parent domain (or recursion has to be switched off, using the
	 * parameter 'recursive'). It is not necessary to register a domain before setting its log level
	 * and log levels can be set and modified any time.
	 *
	 * @param domain        If this is null, the default domain is used. If this is starting with a
	 *                      swung dash ('~') this is interpreted a sub domain to the default domain
	 *                      of the source file. For other values, the default domain is ignored
	 *                      (regardless if this is starting with a slash or not).
	 * @param domainLevel   The domains log level to be set.
	 **************************************************************************************************/
	public static void setDomain(	String	domain,	Log.DomainLevel	domainLevel )										{ LOX.setDomain( domain, domainLevel, true,		 null ); } 

	/**********************************************************************************************//**
	 * This method is used disable one or more loggers completely without touching the log levels of
	 * the domains and hence without the need to restore such log levels later.
	 *
	 * @param disabled      If true, the logger(src) will be completely disabled, if false the normal
	 *                      domain specific log levels will be applied for log decisions.
	 * @param loggerFilter  A filter for the loggers to be affected. A simple string compare without
	 *                      case sensitivity is performed. An asterisk ('*') at the beginning or end
	 *                      of the string is used as a wildcard. Leave null if all loggers should be
	 *                      affected. This parameter is optional and used in more complex logging
	 *                      scenarios.
	 **************************************************************************************************/
	public static void setDisabled( boolean disabled, String loggerFilter )				{ LOX.setDisabled( disabled, loggerFilter ); } 

	/**********************************************************************************************//**
	 * This method is used disable one or more loggers completely without touching the log levels of
	 * the domains and hence without the need to restore such log levels later.
	 *
	 * @param disabled      If true, the logger(src) will be completely disabled, if false the normal
	 *                      domain specific log levels will be applied for log decisions.
	 **************************************************************************************************/
	public static void setDisabled(	boolean disabled ) 									{ LOX.setDisabled( disabled, null ); }

	/**********************************************************************************************//**
	 * This method is used reset (or to explicitly set) the start time of the logger(s). The only
	 * impact is the output of time differences in the log lines. Hence, it is useful to see some
	 * absolute time values when doing basic performance tests using the logger. Note: Calls to this
	 * method are automatically removed from release code.
	 *
	 * @param startTime     Optional parameter with the  new start time. Defaults to DateTime.Now if
	 *                      omitted.
	 * @param loggerFilter  A filter for the loggers to be affected. A simple string compare without
	 *                      case sensitivity is performed. An asterisk ('*') at the beginning or end
	 *                      of the string is used as a wildcard. Leave null if all loggers should be
	 *                      affected.
	 **************************************************************************************************/
	public static void setStartTime( Date startTime, String loggerFilter)	{ LOX.setStartTime( startTime,	loggerFilter ); }

	/**********************************************************************************************//**
	 * This method is used reset (or to explicitly set) the start time of the logger(s). The only
	 * impact is the output of time differences in the log lines. Hence, it is useful to see some
	 * absolute time values when doing basic performance tests using the logger. Note: Calls to this
	 * method are automatically removed from release code.
	 *
	 * @param startTime     Optional parameter with the  new start time. Defaults to DateTime.Now if
	 *                      omitted.
	 **************************************************************************************************/
	public static void setStartTime( Date startTime )						{ LOX.setStartTime( startTime,	null ); }

	/**********************************************************************************************//**
	 * This method is used reset the start time of the logger(s) to now. The only impact is the
	 * output of time differences in the log lines. Hence, it is useful to see some absolute time
	 * values when doing basic performance tests using the logger. Note: Calls to this method are
	 * automatically removed from release code.
	 **************************************************************************************************/
	public static void setStartTime() 					    				{ LOX.setStartTime( null,		null ); }

	/**********************************************************************************************//**
	 * This method sets a human readable name to the given thread ID (or current thread) which is
	 * optionally included in each log line.
	 *
	 * @param threadName    The name of the thread as it should be displayed in the logs.
	 * @param id            Parameter providing the thread ID. If set to -1, the current thread's ID is
	 *                      used.
	 **************************************************************************************************/
	public static void mapThreadName(	String threadName, long id )		{ LOX.mapThreadName( threadName, id ); }

	/**********************************************************************************************//**
	 * This method sets a human readable name to the current thread which is optionally included in
	 * each log line.
	 *
	 * @param threadName    The name of the thread as it should be displayed in the logs.
	 **************************************************************************************************/
	public static void mapThreadName(	String threadName )					{ LOX.mapThreadName( threadName, -1 ); }

	/**********************************************************************************************//**
	 * This method is used store a marker object in the logging system. Markers are stored and
	 * retrieved relative to a given Log.Scope. In combination with Log.GetMarker, this method
	 * provides an easy way to trace the last marked position, e.g. in the case of an exception.
	 * Within the exception handler, use Log.GetMarker to retrieve the last marker object stored
	 * before the exception was thrown.
	 *
	 * @param marker    The object to store, for example a String that can be used for a log output
	 *                  later.
	 * @param scope     The scope in which the marker should be stored. Markers and scopes work
	 *                  independently from each other. Different markers can be stored within different
	 *                  scopes and no fallback to "outer scopes" is made. A scope of 'None' stores the
	 *                  marker globally, hence as a system wide singleton.
	 **************************************************************************************************/
	public static void setMarker(	Object marker, Log.Scope scope)			{ LOX.setMarker( marker, scope); }

	/**********************************************************************************************//**
	 * Retrieves the most recently marker object stored using Log.SetMarker. Markers are stored and
	 * retrieved relative to a given Log.Scope. In combination with Log.SetMarker, this method
	 * provides an easy way to trace the last marked position, e.g. in the case of an exception.
	 * Within the exception handler, use this method to retrieve the last marker object stored
	 * before the exception was thrown.
	 *
	 * @param markerPointer This is array is used to return the marker object. The array must be at
	 *                      least of size 1. The object is stored in position 0. (Note: due to
	 *                      compiler restrictions of C# V. 5.0, this laborious approach for returning
	 *                      the object has been chosen. The function can not return a value because
	 *                      it is conditionally compiled using the ALOX_DEBUG compiler flag.
	 * @param scope         The scope in which the marker should be stored. Markers and scopes work
	 *                      independently from each other. Different markers can be stored within
	 *                      different scopes and no fallback to "outer scopes" is made. A scope of
	 *                      'None' retrieves the global marker singleton.
	 **************************************************************************************************/
	public static void getMarker( Object[] markerPointer, Log.Scope scope )		{ LOX.getMarker( markerPointer, scope ); }

	/**********************************************************************************************//**
	 * This method logs the configuration the Lox encapsulated in this static Log interface.
	 *
	 * @param domain        If this is null, the default domain is used. If this is starting with a
	 *                      swung dash ('~') this is interpreted a sub domain to the default domain
	 *                      of the source file. For other values, the default domain is ignored
	 *                      (regardless if this is starting with a slash or not).
	 * @param level         The logging level.
	 * @param headLine      If given, a separated headline will be logged at first place.
	 * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
	 *                      loggers to have different domains. A simple string compare without case
	 *                      sensitivity is performed. An asterisk ('*') at the beginning or end of
	 *                      the string is used as a wildcard. Leave null if all loggers should be
	 *                      affected. Use this parameter only in more complex logging scenarios.
	 **************************************************************************************************/
	public static void logConfig(	String domain, Log.Level level, String	headLine, String loggerFilter )	{ LOX.logConfig( domain, level, headLine, loggerFilter); }

	/**********************************************************************************************//**
	 * This method logs the configuration the Lox encapsulated in this static Log interface.
	 *
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the
	 *                  source file. For other values, the default domain is ignored (regardless if
	 *                  this is starting with a slash or not).
	 * @param level     The logging level.
	 * @param headLine  If given, a separated headline will be logged at first place.
	 **************************************************************************************************/
	public static void logConfig( String domain, Log.Level level, String headLine) 						{ LOX.logConfig( domain, level, headLine, null ); }

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Log.Level.Verbose. This is the highest (most
	 * verbose) log level, which is only actually logged if the log domains log level is set to
	 * "All". This overloaded version does not offer a domain parameter but relies on a default
	 * domain set for the source file this function is used in.
	 *
	 * @param msg       The message to log out.
	 * @param indent    The indentation in the output.
	 **************************************************************************************************/
	public static void verbose( Object msg, int indent )						{	LOX.line( true, null, Log.Level.Verbose, msg, indent,	null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
	 * log level, which is only actually logged if the log domains log level is set to "All". This
	 * overloaded version does not offer a domain parameter but relies on a default domain set for
	 * the source file this function is used in.
	 *
	 * @param msg   The message to log out.
	 **************************************************************************************************/
	public static void verbose( Object msg )									{	LOX.line( true, null, Log.Level.Verbose, msg, 0,		null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
	 * log level, which is only actually logged if the log domains log level is set to "All".
	 *
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the source
	 *                  file. For other values, the default domain is ignored (regardless if this is
	 *                  starting with a slash or not).
	 * @param msg       The message to log out.
	 * @param indent    The indentation in the output.
	 **************************************************************************************************/
	public static void verbose( String domain, Object msg, int indent )		{	LOX.line( true, domain, Log.Level.Verbose, msg, indent,	null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
	 * log level, which is only actually logged if the log domains log level is set to "All".
	 *
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the source
	 *                  file. For other values, the default domain is ignored (regardless if this is
	 *                  starting with a slash or not).
	 * @param msg       The message to log out.
	 **************************************************************************************************/
	public static void verbose( String domain, Object msg )					{	LOX.line( true, domain, Log.Level.Verbose, msg, 0,		null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
	 * Verbose) log level, which is only actually logged if the log domains log level is set to
	 * "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
	 * a default domain set for the source file this function is used in.
	 *
	 * @param msg       The message to log out.
	 * @param indent    The indentation in the output.
	 **************************************************************************************************/
	public static void info( Object msg, int indent )							{	LOX.line( true, null, Log.Level.Info, msg, indent,	null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
	 * Verbose) log level, which is only actually logged if the log domains log level is set to
	 * "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
	 * a default domain set for the source file this function is used in.
	 *
	 * @param msg       The message to log out.
	 **************************************************************************************************/
	public static void info( Object msg )										{	LOX.line( true, null, Log.Level.Info, msg, 0,		null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
	 * Verbose) log level, which is only actually logged if the log domains log level is set to
	 * "Info" or "Verbose".
	 *
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the source
	 *                  file. For other values, the default domain is ignored (regardles if this is
	 *                  starting with a slash or not).
	 * @param msg       The message to log.
	 * @param indent    The indentation in the output.
	 **************************************************************************************************/
	public static void info( String domain, Object msg, int indent )			{	LOX.line( true, domain, Log.Level.Info, msg, indent,	null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
	 * Verbose) log level, which is only actually logged if the log domains log level is set to
	 * "Info" or "Verbose".
	 *
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the source
	 *                  file. For other values, the default domain is ignored (regardles if this is
	 *                  starting with a slash or not).
	 * @param msg       The message to log.
	 **************************************************************************************************/
	public static void info( String domain, Object msg )						{	LOX.line( true, domain, Log.Level.Info, msg, 0,		null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
	 * are logged if the log domains log level is set to "Warning", "Info" or "All". This overloaded
	 * version does not offer a domain parameter but relies on a default domain set for the source
	 * file this function is used in.
	 *
	 * @param msg       The message to log out.
	 * @param indent    The indentation in the output.
	 **************************************************************************************************/
	public static void warning( Object msg, int indent )						{	LOX.line( true, null, Log.Level.Warning, msg, indent,	null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
	 * are logged if the log domains log level is set to "Warning", "Info" or "All". This overloaded
	 * version does not offer a domain parameter but relies on a default domain set for the source
	 * file this function is used in.
	 *
	 * @param msg   The message to log out.
	 **************************************************************************************************/
	public static void warning( Object msg )									{	LOX.line( true, null, Log.Level.Warning, msg, 0,		null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
	 * are logged if the log domains log level is set to "Warning", "Info" or "All".
	 *
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the source
	 *                  file. For other values, the default domain is ignored (regardless if this is
	 *                  starting with a slash or not).
	 * @param msg       The message to log.
	 * @param indent    The indentation in the output.
	 **************************************************************************************************/
	public static void warning( String domain, Object msg, int indent )		{	LOX.line( true, domain, Log.Level.Warning, msg, indent,	null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
	 * are logged if the log domains log level is set to "Warning", "Info" or "All".
	 *
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the source
	 *                  file. For other values, the default domain is ignored (regardless if this is
	 *                  starting with a slash or not).
	 * @param msg       The message to log.
	 **************************************************************************************************/
	public static void warning( String domain, Object msg )					{	LOX.line( true, domain, Log.Level.Warning, msg, 0,		null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
	 * always logged unless domains log level is set to "Off". This overloaded version does not
	 * offer a domain parameter but relies on a default domain set for the source file this function
	 * is used in.
	 *
	 * @param msg       The message to log out.
	 * @param indent    The indentation in the output.
	 **************************************************************************************************/
	public static void error( Object msg, int indent )						{	LOX.line( true, null, Log.Level.Error, msg, indent,	null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
	 * always logged unless domains log level is set to "Off". This overloaded version does not
	 * offer a domain parameter but relies on a default domain set for the source file this function
	 * is used in.
	 *
	 * @param msg       The message to log out.
	 **************************************************************************************************/
	public static void error( Object msg )									{	LOX.line( true, null, Log.Level.Error, msg, 0,		null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
	 * always logged unless domains log level is set to "Off".
	 *
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the source
	 *                  file. For other values, the default domain is ignored (regardless if this is
	 *                  starting with a slash or not).
	 * @param msg       The message to log out.
	 * @param indent    The indentation in the output.
	 **************************************************************************************************/
	public static void error( String domain, Object msg, int indent )			{	LOX.line( true, domain, Log.Level.Error, msg, indent,	null );	}

	/**********************************************************************************************//**
	 * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
	 * always logged unless domains log level is set to "Off".
	 *
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the source
	 *                  file. For other values, the default domain is ignored (regardless if this is
	 *                  starting with a slash or not).
	 * @param msg       The message to log out.
	 **************************************************************************************************/
	public static void error( String domain, Object msg )						{	LOX.line( true, domain, Log.Level.Error, msg, 0,		null );	}

	/**********************************************************************************************//**
	 * Log a string only if the given condition is not true. Log level will be highest, namely Error
	 * if condition is false. This overloaded version does not offer a domain parameter but relies
	 * on a default domain set for the source file this function is used in.
	 *
	 * @param trueOrLog The log is only performed if condition is not true.
	 * @param msg       The message to log out.
	 * @param indent    the indentation in the output.
	 **************************************************************************************************/
	public static void Assert( boolean trueOrLog, Object msg, int indent )	{	LOX.line( !trueOrLog, null, Log.Level.Error, msg, indent,	null );	}

	/**********************************************************************************************//**
	 * Log a string only if the given condition is not true. Log level will be highest, namely Error
	 * if condition is false. This overloaded version does not offer a domain parameter but relies
	 * on a default domain set for the source file this function is used in.
	 *
	 * @param trueOrLog The log is only performed if condition is not true.
	 * @param msg       The message to log out.
	 **************************************************************************************************/
	public static void Assert( boolean trueOrLog, Object msg )				{	LOX.line( !trueOrLog, null, Log.Level.Error, msg, 0,		null );	}

	/**********************************************************************************************//**
	 * Log a string only if the given condition is not true. Log level will be highest, namely
	 * Log.Level.Error.
	 *
	 * @param trueOrLog The log is only performed if condition is not true.
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the
	 *                  source file. For other values, the default domain is ignored (regardless if
	 *                  this is starting with a slash or not).
	 * @param msg       The message to log out.
	 * @param indent    the indentation in the output.
	 **************************************************************************************************/
	public static void Assert( boolean trueOrLog, String domain, Object msg, int indent )	{ LOX.line( !trueOrLog, domain, Log.Level.Error, msg, indent,	null );	}

	/**********************************************************************************************//**
	 * Log a string only if the given condition is not true. Log level will be highest, namely
	 * Log.Level.Error.
	 *
	 * @param trueOrLog The log is only performed if condition is not true.
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the
	 *                  source file. For other values, the default domain is ignored (regardless if
	 *                  this is starting with a slash or not).
	 * @param msg       The message to log out.
	 **************************************************************************************************/
	public static void Assert( boolean trueOrLog, String domain, Object msg )				{ LOX.line( !trueOrLog, domain, Log.Level.Error, msg, 0,		null );	}

	/**********************************************************************************************//**
	 * Provides a the a more flexible but complex way to log a message. The methods #verbose(),
	 * #info(), #warning(), #error() and #Assert() are using this function internally and should
	 * be used in standard cases. Use this function only in the rare cases, e.g. when a log level is
	 * decided only at runtime or when you want to use a logger filter, etc.
	 *
	 * @param doLog         Conditional logging. If false, the log is not performed. CntLogCalls is
	 *                      still increased by one.
	 * @param domain        If this is null, the default domain is used. If this is starting with a
	 *                      swung dash ('~') this is interpreted a sub domain to the default domain
	 *                      of the source file. For other values, the default domain is ignored
	 *                      (regardless if this is starting with a slash or not).
	 * @param level         The log level.
	 * @param msgObject     An Object to be logged.
	 * @param indent        The indentation in the output.
	 * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
	 *                      loggers to have different domains. A simple string compare without case
	 *                      sensitivity is performed. An asterisk ('*') at the beginning or end of
	 *                      the string is used as a wildcard. Leave null if all loggers should be
	 *                      affected. Use this parameter only in more complex logging scenarios.
	 **************************************************************************************************/
	public static void line( boolean doLog, String domain, Log.Level level, Object msgObject, int indent, String loggerFilter )	{ LOX.line( doLog, domain,	level, msgObject, indent,	loggerFilter);	}

	/**********************************************************************************************//**
	 * Conditionally logs an Object using the given log level, log domain and indentation.
	 *
	 * @param doLog     Conditional logging. If false, the log is not performed. CntLogCalls is still
	 *                  increased by one.
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the
	 *                  source file. For other values, the default domain is ignored (regardless if
	 *                  this is starting with a slash or not).
	 * @param level     The log level.
	 * @param msgObject An Object to be logged.
	 * @param indent    The indentation in the output.
	 **************************************************************************************************/
	public static void line (boolean doLog, String domain,	Log.Level level, Object msgObject, int indent )							{ LOX.line( doLog, domain,	level, msgObject, indent,	null); 			}

	/**********************************************************************************************//**
	 * Conditionally logs an Object using the given log level and log domain.
	 *
	 * @param doLog     Conditional logging. If false, the log is not performed. CntLogCalls is still
	 *                  increased by one.
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the
	 *                  source file. For other values, the default domain is ignored (regardless if
	 *                  this is starting with a slash or not).
	 * @param level     The log level.
	 * @param msgObject An Object to be logged.
	 **************************************************************************************************/
	public static void line( boolean doLog, String domain,	Log.Level level, Object msgObject ) 									{ LOX.line( doLog, domain,	level, msgObject, 0,		null); 			}

	/**********************************************************************************************//**
	 * Logs an Object using the given log level and log domain.
	 *
	 * @param domain    If this is null, the default domain is used. If this is starting with a swung
	 *                  dash ('~') this is interpreted a sub domain to the default domain of the
	 *                  source file. For other values, the default domain is ignored (regardless if
	 *                  this is starting with a slash or not).
	 * @param level     The log level.
	 * @param msgObject An Object to be logged.
	 **************************************************************************************************/
	public static void line(				String domain,	Log.Level level, Object msgObject ) 									{ LOX.line( true,  domain,	level, msgObject, 0,		null); 			}

	/**********************************************************************************************//**
	 * Logs an Object using the given log level and the default domain for this scope.
	 *
	 * @param level     The log level.
	 * @param msgObject An Object to be logged.
	 **************************************************************************************************/
	public static void line(			   					Log.Level level, Object msgObject ) 									{ LOX.line( true,  null,	level, msgObject, 0,		null); 			}

	/**********************************************************************************************//**
	 * Logs an Object using the given log level and indentation using the default domain for this scope.
	 *
	 * @param level     The log level.
	 * @param msgObject An Object to be logged.
	 * @param indent    The indentation in the output.
	 **************************************************************************************************/
	public static void line(			   				  	Log.Level level, Object msgObject, int indent ) 						{ LOX.line( true,  null,	level, msgObject, indent,	null); 			}

	/**********************************************************************************************//**
	 * Logs an Object using the given log level, indentation and logger filter using the default domain 
	 * for this scope.
	 *
	 * @param level         Conditional logging. If false, the log is not performed. CntLogCalls is
	 *                      still increased by one.
	 * @param msgObject     If this is null, the default domain is used. If this is starting with a
	 *                      swung dash ('~') this is interpreted a sub domain to the default domain
	 *                      of the source file. For other values, the default domain is ignored
	 *                      (regardless if this is starting with a slash or not).
	 * @param indent        The indentation in the output.
	 * @param loggerFilter  A filter for the loggers to be affected. This parameter enables different
	 *                      loggers to have different domains. A simple string compare without case
	 *                      sensitivity is performed. An asterisk ('*') at the beginning or end of
	 *                      the string is used as a wildcard. Leave null if all loggers should be
	 *                      affected. Use this parameter only in more complex logging scenarios.
	 **************************************************************************************************/
	public static void line(			   				  	Log.Level level, Object msgObject, int indent, String loggerFilter )	{ LOX.line( true,  null,	level, msgObject, indent,	loggerFilter);	}
}
 
