// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:	Log
//  
//  File:	Log.cs														  Namespace:  com.aworx.lox
// #################################################################################################

using System.Diagnostics;
using System.Runtime.CompilerServices;
using System;
using com.aworx.util;
using com.aworx.lox.core;
using com.aworx.lox.loggers;

namespace com.aworx.lox {



/** ***********************************************************************************************
 * <summary>
 *  This is a simple, 100% static wrapper of class Lox. In other words, this class incorporates
 *  one static singleton of Lox and mirrors the whole non static interface of Lox into a static
 *  one.
 *  
 *  The exclusive use of this class covers the vast majority of all logging scenarios. Only for
 *  release logging, remote logging and similar scenarios, the use of a dedicated instance of
 *  class Lox is needed.
 *  
 *  Hence, this is the interface of choice for standard log scenarios. All invocations of methods
 *  of Log are pruned in release code. (Using method annotation "[Conditional("ALOX_DEBUG")]".
 *  
 *  Of course, the use of class Log and Lox can be mixed, to enable debug log output in parallel
 *  to release output.
 * </summary>
 **************************************************************************************************/
public static class Log
{
	// #################################################################################################
	// Public Enums for ALox
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>	These are the levels of log verbosity assignable to a log domain. </summary>
	 **************************************************************************************************/
	public enum DomainLevel
	{
		/** <summary>Do not log anything </summary>*/					
		Off,	

		/** <summary>Log only level Error</summary>*/					
		Errors,

		/** <summary>Log only levels Warning or Error.</summary>*/		
		WarningsAndErrors,

		/** <summary>Log all  levels but Verbose.</summary>*/				
		InfoWarningsAndErrors,

		/** <summary>Log all.</summary>*/								
		All,	

		/** <summary>Inherit level from parent domain</summary>*/
		Inherit,	
	}

	/** ***********************************************************************************************
	 * <summary>	These are the levels of log verbosity used in a log call. </summary>
	 **************************************************************************************************/
	public enum Level
	{
		/** <summary>The most verbose log level to be used for debug output statements. Logged only if
			* the domains log level is set to DomainLevel.All</summary>*/
		Verbose,

		/** <summary>The standard log level for normal log output statements. Logged if the domains
			* level is either DomainLevel.All or DomainLevel.InfoWarningsAndErrors</summary>*/
		Info,

		/** <summary>A log level for warning messages, hence things that might lead to errors or are not
			* welcome for other reasons, but maybe are not errors. 
			* It is not logged only if the domains log level is DomainLevel.Errors orLogDomain.Level. Off</summary>*/
		Warning,

		/** <summary>A log level for (severe) error messages
			* It is suppressed only if the domains log level is set to DomainLevel.Off</summary>*/
		Error,
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  These are definitions which are used as a parameter to certain ALox methods to determine the
	 *  breadth of the scope of a setting. The definitions are platform dependent. E.g. in C# the
	 *  scope can be "Method" or "SourceFile" file while in JAVA it can be "Package", "Class" or
	 *  "Method". The difference is due to different mechanisms to automatically collect caller
	 *  information.
	 *  
	 *  Attn C# users: If within one source file two or more classes with equal same method names
	 *  exist, then such method names share the same scope and hence are ambiguous. This is due to
	 *  technical restrictions of how caller information is collected in C#/.Net.
	 * </summary>
	 **************************************************************************************************/
	public enum Scope
	{
		/** <summary>No scope should be applied/affected</summary>*/
		None,

		/** <summary>Defines the actual source file as the scope</summary>*/
		SourceFile,

		/** <summary>Defines the actual method as the scope</summary>*/
		Method,
	}


	#if ALOX_DEBUG

		// #################################################################################################
		// Public static fields
		// #################################################################################################
		/// <summary>The loggers. At least one logger (e.g. ConsoleLogger) needs to be created.</summary>
		public	static		Lox								LOX=	new Lox();

		// #################################################################################################
		// Implement and set A-Worx Util Error Handler 
		// #################################################################################################
		/// <summary>The error handler for the util package. An instance of this class will be created
		/// statically and added to field AWXU.errorHandler. </summary>
		public class	ALoxAWXUErrorHandler : AWXUErrorHandler
		{
			/** ***********************************************************************************************
			 * <summary> Report an AWXU error using ALox. </summary>
			 * <param name="msg">	The error message. </param>
			 **************************************************************************************************/
			public void error  ( Object msg )	{ Log.Error	 ( "AWXU", msg ); }
			/** ***********************************************************************************************
			 * <summary> Report an AWXU warning using ALox. </summary>
			 * <param name="msg">	The warning message. </param>
			 **************************************************************************************************/
			public void warning( Object msg )	{ Log.Warning( "AWXU", msg ); }
		}

		static Log()
		{
			AWXU.errorHandler= new ALoxAWXUErrorHandler();
		}
	
		// #################################################################################################
		// Interface (not auto removed)
		// #################################################################################################

		/** ***********************************************************************************************
		 * <summary>
		 *  Retrieve an instance of a Logger by its name. Note: This function is not automatically
		 *  removed from the release code because of technical restrictions. It has to be conditionally
		 *  compiled by enclosing calls to it with "#if ... #endif" statements.
		 * </summary>
		 * <param name="loggerName">	The name of the logger to search for (case insensitive) </param>
		 * <returns>	The logger, null if not found. </returns>
		 **************************************************************************************************/
		public static Logger GetLogger( String loggerName )
		{
			return LOX.GetLogger( loggerName );
		}

	#endif


	// #################################################################################################
	// Interface (auto removed)
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>
	 *  This method disposes the internal static Lox and with it all loggers, preferences and stuff
	 *  and replaces it with a fresh one. The method was added to support clean unit testing.
	 * </summary>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void Reset()
	{
		#if ALOX_DEBUG
			LOX= new Lox();
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Adds a logger to the Log interface. Each log call that is performed through this interface
	 *  will be forwarded to this logger, unless filtered out with optional filter parameter. The
	 *  logger will then check it's domain level against the given log level to decide whether a log
	 *  should performed.
	 * </summary>
	 * <param name="logger">			 	The logger to be added. </param>
	 * <param name="internalDomainLevel">	(Optional) The desired domain level for Lox.InternalDomain 
	 *										which is used for logging code of class
	 * 										Log itself. For console loggers this can be set to
	 * 										**All**, for log streams dedicated to a certain domain,
	 * 										this should be set to **Off**. </param>
	 * <param name="csf"> 	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln"> 	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn"> 	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void AddLogger( Logger logger, DomainLevel internalDomainLevel= DomainLevel.WarningsAndErrors,
								  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

	{
		#if ALOX_DEBUG 
			LOX.AddLogger( logger, internalDomainLevel, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>	Removes all loggers that match the filter name from this static interface. </summary>
	 * <param name="loggerFilter">	(Optional) A filter for the loggers to be affected. A simple
	 * 								string compare without case sensitivity is performed. An asterisk
	 * 								('*') at the beginning or end of the string is used as a
	 * 								wildcard. Defaults to null which causes all loggers to be
	 * 								removed. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void RemoveLoggers( String loggerFilter= null )
	{
		#if ALOX_DEBUG
			LOX.RemoveLoggers( loggerFilter );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  To shorten the log output the given prefix might be cut from the source file path.  
	 *  If this method is not invoked (or invoked with parameter 'cspp= null' at runtime), it is tried to
	 *  detect this path automatically once. However, in remote debug sessions (e.g. on mobile device
	 *  development)
	 *  this fails. Hence, this parameter can be set 'manually' to the right prefix that is to be
	 *  consumed. In this case, whenever the project is compiled on a different machine setup (with
	 *  different project path), this field has to be changed. If it is not changed, there is no
	 *  other problem than that the path is not shortened and the log output might get a little wide.
	 *  If the output of the full path is intended, the parameter can be set to 'String.Empty'.  
	 * </summary>
	 * <param name="cspp">	The prefix to cut from the source file name in log outputs.</param>
	 * <param name="csf"> 	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln"> 	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn"> 	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void SetConsumableSourcePathPrefix( String cspp,	
									 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.SetConsumableSourcePathPrefix( cspp, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  This method is used to define a log domain. The method is usually invoked within the same 
	 *  source "context" (aka, class, namespace, package, etc.) that later on uses the domain to perform
	 *  log statements. Often, calls to this functions are placed in static constructors or similar
	 *  code that is executed only once and very early in the lifecycle of a process.
	 *  
	 *  Each log statement refers to such a domain which can be used specifically for different
	 *  parts of your application like assemblies, libraries, namespaces, specific code files or even
	 *  for a single method. The domain name should be short, pregnant and self explaining.
	 *  
	 *  Domains can be created with path separators '/', for example 'COMM/SOCK' could be the domain in 
	 *  a socket class, residing within a communication library.
	 *  The advantage of creating paths and this way "sub domains", is that a whole bunch of logging
	 *  domains can be altered (on/off) by just altering the root domain.
	 *  
	 *  If a domain and path is given that is not known already, then the whole path of domains is
	 *  created.
	 *  
	 *  If the parameter **scope** is provided with a value not equal to Log.Scope.None, the given
	 *  domain becomes the default domain for respective scope. For any subsequent log calls from within
	 *  this scope, where no domain is explicitly given, this default domain is used. If subsequent
	 *  log calls specify a domain name with a leading '~' character, then such domain is
	 *  concatenated to the default domain to build a complete domain path.
	 *  
	 * </summary>
	 * 
	 * <param name="domain">	The domain name (and path) to register. 
	 * 							If this is starting	with a swung dash ('~') this is interpreted a sub
	 * 							domain to a (potentially already set!) default domain of the source file.
	 * 							For other values, the default	domain is ignored (regardless if this is
	 * 							starting with a slash or	not). </param>
	 * <param name="scope"> 	If a value other than Log.Scope.None is provided, the given domain
	 * 							name is registered as the default domain for the given scope. Default
	 * 							domains set for 'inner scopes' have higher priority than those set for
	 * 							outer scopes. Available Scope definitions are platform/language
	 * 							dependent. </param>
	 * <param name="csf">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void RegDomain( String	domain,	 Log.Scope scope,
								[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.RegDomain( domain, scope, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Sets the domain log level and (by default) all it's sub domains recursively. In the case that
	 *  sub domains should be set to a different log level, then this function has to be called for
	 *  such sub domains after the call to the parent domain (or recursion has to be switched off,
	 *  using the parameter 'recursive'). It is not necessary to register a domain before setting its
	 *  log level and log levels can be set and modified any time.
	 * </summary>
	 * <param name="domain">	  	If this is null, the default domain is used. If this is starting
	 * 								with a swung dash ('~') this is interpreted a sub domain to the
	 * 								default domain of the source file. For other values, the default
	 * 								domain is ignored (regardless if this is starting with a slash or
	 * 								not). </param>
	 * <param name="domainLevel"> 	The domains log level to be set. </param>
	 * <param name="recursive">   	(Optional) Set sub domains recursively. Defaults to true. </param>
	 * <param name="loggerFilter">	(Optional) A filter for the loggers to be affected. This
	 * 								parameter enables different loggers to have different domains and
	 * 								log levels. A simple string compare without case sensitivity is
	 * 								performed. An asterisk ('*') at the beginning or end of the
	 * 								string is used as a wildcard. Leave null if all loggers should be
	 * 								affected. Use this parameter only in more complex logging
	 * 								scenarios. </param>
	 * <param name="csf">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void SetDomain(	String	domain,				DomainLevel	domainLevel, 
									bool	recursive= true,	String		loggerFilter= null,
									[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.SetDomain( domain, domainLevel, recursive, loggerFilter, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  This method is used disable one or more loggers completely without touching the log levels of
	 *  the domains and hence without the need to restore such log levels later. 
	 * </summary>
	 * <param name="disabled">	  	If true, the logger(src) will be completely disabled, if false
	 * 								the normal domain specific log levels will be applied for log
	 * 								decisions. </param>
	 * <param name="loggerFilter">	(Optional) A filter for the loggers to be affected. A simple
	 * 								string compare without case sensitivity is performed. An asterisk
	 * 								('*') at the beginning or end of the string is used as a
	 * 								wildcard. Leave null if all loggers should be affected. This
	 * 								parameter is optional and used in more complex logging scenarios. </param>
	 * <param name="csf">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void SetDisabled(	bool disabled, String loggerFilter= null,
									[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.SetDisabled( disabled, loggerFilter, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  This method is used reset (or to explicitly set) the start time of the logger(s).
	 *  The only impact is the output of time differences in the log lines. Hence, it is useful to
	 *  see some absolute time values when doing basic performance tests using the logger. Note:
	 *  Calls to this method are automatically removed from release code.
	 * </summary>
	 * <param name="startTime">   	(Optional) Optional parameter with the  new start time. Defaults
	 * 								to DateTime.Now if omitted. </param>
	 * <param name="loggerFilter">	(Optional) A filter for the loggers to be affected. A simple
	 * 								string compare without case sensitivity is performed. An asterisk
	 * 								('*') at the beginning or end of the string is used as a
	 * 								wildcard. Leave null if all loggers should be affected. </param>
	 * <param name="csf">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void SetStartTime( DateTime? startTime= null, String loggerFilter= null,
									 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.SetStartTime( startTime, loggerFilter, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  This method sets a human readable name to the given thread ID (or current thread) which is 
	 *  optionally included in each log line.
	 * </summary>
	 * <param name="threadName">	The name of the thread as it should be displayed in the logs</param>
	 * <param name="id">			(Optional) Parameter providing the thread ID. If omitted, the
	 * 								current thread's ID is used.</param>
	 * <param name="csf">			(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">			(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">			(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void MapThreadName( String threadName, int id= -1,
												 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.MapThreadName( threadName, id, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  This method is used store a marker object in the logging system. Markers are stored
	 *  and retrieved relative to a given Log.Scope. In combination with Log.GetMarker,
	 *  this method provides an easy way to trace the last marked position, e.g. in the case of an
	 *  exception. Within the exception handler, use Log.GetMarker to retrieve the last marker
	 *  object stored before the exception was thrown. 
	 * </summary>
	 * <param name="marker">	   	The object to store, for example a String that can be used for a
	 * 								log output later. </param>
	 * <param name="scope">			The scope in which the marker should be stored. Markers and scopes
	 * 								work independently from each other. Different markers can be stored
	 * 								within different scopes and no fallback to "outer scopes" is made. 
	 * 								A scope of 'None' stores the marker globally, hence as a system wide
	 * 								singleton.</param>
	 * <param name="csf">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void SetMarker(	Object marker, Log.Scope scope,
									[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.SetMarker( marker, scope, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Retrieves the most recently marker object stored using Log.SetMarker. Markers are stored
	 *  and retrieved relative to a given Log.Scope. In combination with Log.SetMarker,
	 *  this method provides an easy way to trace the last marked position, e.g. in the case of an
	 *  exception. Within the exception handler, use this method to retrieve the last marker
	 *  object stored before the exception was thrown. 
	 * </summary>
	 * <param name="markerPointer">	This is array is used to return the marker object. The array must
	 * 								be at least of size 1. The object is stored in position 0. (Note:
	 * 								due to compiler restrictions of C# V. 5.0, this laborious
	 * 								approach for returning the object has been chosen. The function
	 * 								can not return a value because it is conditionally compiled using
	 * 								the ALOX_DEBUG compiler flag. </param>
	 * <param name="scope">			The scope in which the marker should be stored. Markers and scopes
	 * 								work independently from each other. Different markers can be stored
	 * 								within different scopes and no fallback to "outer scopes" is made. 
	 * 								A scope of 'None' retrieves the global marker singleton.</param>
	 * <param name="csf">		   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void GetMarker( Object[] markerPointer, Log.Scope scope,
								  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.GetMarker( markerPointer, scope, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  This method logs the configuration the Lox encapsulated in this static Log interface.
	 * </summary>
	 * <param name="domain">	  	If this is null, the default domain is used. If this is starting
	 * 								with a swung dash ('~') this is interpreted a sub domain to the
	 * 								default domain of the source file. For other values, the default
	 * 								domain is ignored (regardless if this is starting with a slash or
	 * 								not). </param>
	 * <param name="level">		  	The log level. </param>
	 * <param name="headLine">	  	If given, a separated headline will be logged at first place. </param>
	 * <param name="loggerFilter">	(Optional) A filter for the loggers to be affected. This
	 * 								parameter enables different loggers to have different domains. A
	 * 								simple string compare without case sensitivity is performed. An
	 * 								asterisk ('*') at the beginning or end of the string is used as a
	 * 								wildcard. Leave null if all loggers should be affected. Use this
	 * 								parameter only in more complex logging scenarios. </param>
	 * <param name="csf">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]	
	public static void LogConfig(	String			domain,
									Log.Level		level,
									String			headLine,
									String			loggerFilter= null,
									[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.LogConfig( domain, level, headLine, loggerFilter, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
	 *  log level, which is only actually logged if the log domains log level is set to "All". This
	 *  overloaded version does not offer a domain parameter but relies on a default domain set for
	 *  the source file this function is used in.
	 * </summary>
	 * <param name="msg">   	An Object to be logged. </param>
	 * <param name="indent">	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="csf">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Verbose( Object msg, int indent = 0,
								[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( true, null, Log.Level.Verbose, msg, indent, null, csf, cln, cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
	 *  log level, which is only actually logged if the log domains log level is set to "All". Note:
	 *  Calls to this method are automatically removed from release code.
	 * </summary>
	 * <param name="domain">	If this is null, the default domain is used. If this is starting with
	 * 							a swung dash ('~') this is interpreted a sub domain to the default domain
	 * 							of the source file. For other values, the default domain is ignored
	 * 							(regardless if this is starting with a slash or not). </param>
	 * <param name="msg">   	An Object to be logged. </param>
	 * <param name="indent">	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="csf">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Verbose( String domain, Object msg, int indent = 0,
								[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( true, domain, Log.Level.Verbose, msg, indent, null, csf, cln, cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log an Object with log level equal to Log.Level.Info. This is the second highest (after
	 *  Verbose) log level, which is only actually logged if the log domains log level is set to
	 *  "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
	 *  a default domain set for the source file this function is used in.
	 * </summary>
	 * <param name="msg">   	An Object to be logged. </param>
	 * <param name="indent">	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="csf">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Info( String msg, int indent = 0,
							 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( true,  null, Log.Level.Info, msg, indent, null, csf, cln, cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log an Object with log level equal to Log.Level.Info. This is the second highest (after
	 *  Verbose) log level, which is only actually logged if the log domains log level is set to
	 *  "Info" or "Verbose".
	 * </summary>
	 * <param name="domain">	If this is null, the default domain is used. If this is starting with
	 * 							a swung dash ('~') this is interpreted a sub domain to the default domain
	 * 							of the source file. For other values, the default domain is ignored
	 * 							(regardless if this is starting with a slash or not). </param>
	 * <param name="msg">   	An Object to be logged. </param>
	 * <param name="indent">	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="csf">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Info( String domain, Object msg, int indent = 0,
							 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( true, domain, Log.Level.Info, msg, indent, null, csf, cln, cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log an Object with log level equal to Log.Level.Warning. Log messages of this log level
	 *  are are logged if the log domains log level is set to "Warning", "Info" or "All".
	 *  This overloaded version does not offer a domain parameter but relies on a default domain set
	 *  for the source file this function is used in. 
	 * </summary>
	 * <param name="msg">   	An Object to be logged. </param>
	 * <param name="indent">	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="csf">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Warning( Object msg, int indent = 0,
								[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( true, null, Log.Level.Warning, msg, indent, null, csf, cln, cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
	 *  are logged if the log domains log level is set to "Warning", "Info" or "All". 
	 * </summary>
	 * <param name="domain">	If this is null, the default domain is used. If this is starting with
	 * 							a swung dash ('~') this is interpreted a sub domain to the default domain
	 * 							of the source file. For other values, the default domain is ignored
	 * 							(regardless if this is starting with a slash or not). </param>
	 * <param name="msg">   	An Object to be logged. </param>
	 * <param name="indent">	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="csf">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Warning( String domain, Object msg, int indent = 0,
								[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( true, domain, Log.Level.Warning, msg, indent, null, csf, cln, cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log an Object with log level equal to Log.Level.Error. Log messages of this log level are
	 *  are always logged unless domains log level is set to "Off". This overloaded version does not
	 *  offer a domain parameter but relies on a default domain set for the source file this function
	 *  is used in. 
	 * </summary>
	 * <param name="msg">   	An Object to be logged. </param>
	 * <param name="indent">	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="csf">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Error( Object msg, int indent = 0,
							  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( true, null, Log.Level.Error, msg, indent, null, csf, cln, cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log an Object with log level equal to Log.Level Error. Log messages of this log level are are
	 *  always logged unless domains log level is set to "Off". 
	 * </summary>
	 * <param name="domain">	If this is null, the default domain is used. If this is starting with
	 * 							a swung dash ('~') this is interpreted a sub domain to the default domain
	 * 							of the source file. For other values, the default domain is ignored
	 * 							(regardless if this is starting with a slash or not). </param>
	 * <param name="msg">   	An Object to be logged. </param>
	 * <param name="indent">	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="csf">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Error( String domain, Object msg, int indent = 0,
							  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( true, domain, Log.Level.Error, msg, indent, null, csf, cln, cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log a string only if the given condition is not true. Log level will be highest, namely Error
	 *  if condition is false. This overloaded version does not offer a domain parameter but relies
	 *  on a default domain set for the source file this function is used in. 
	 * </summary>
	 * <param name="trueOrLog"> The log is only performed if condition is not true. </param>
	 * <param name="msg">   	An Object to be logged. </param>
	 * <param name="indent">   	(Optional) the indentation in the output. Defaults to 0. </param>
	 * <param name="csf">	   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">	   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">	   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Assert( bool trueOrLog, Object msg, int indent = 0,
							   [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( !trueOrLog, null, Log.Level.Error, msg, indent, null, csf, cln, cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Log a string only if the given condition is not true. Log level will be highest, namely
	 *  Log.Level.Error. 
	 * </summary>
	 * <param name="trueOrLog"> The log is only performed if condition is not true. </param>
	 * <param name="domain">   	If this is null, the default domain is used. If this is starting with
	 * 							a swung dash ('~') this is interpreted a sub domain to the default
	 * 							domain of the source file. For other values, the default domain is
	 * 							ignored (regardless if this is starting with a slash or not). </param>
	 * <param name="msg">   	An Object to be logged. </param>
	 * <param name="indent">   	(Optional) the indentation in the output. Defaults to 0. </param>
	 * <param name="csf">	   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">	   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">	   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Assert( bool trueOrLog, String domain, Object msg, int indent = 0,
							   [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( !trueOrLog, domain, Log.Level.Error, msg, indent, null, csf, cln, cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Provides a more flexible but complex way to log a message. The methods #Verbose(),
	 *  #Info(), #Warning(), #Error() and #Assert() are using this function internally and should
	 *  be used in standard cases. Use this function only in the rare cases, e.g. when a log level is
	 *  decided only at runtime or when you want to use a logger filter, etc.
	 * </summary>
	 * <param name="doLog">		  	Conditional logging. If false, the log is not performed. CntLogCalls
	 * 								is still increased by one. </param>
	 * <param name="domain">	  	If this is null, the default domain is used. If this is starting
	 * 								with a swung dash ('~') this is interpreted a sub domain to the
	 * 								default domain of the source file. For other values, the default
	 * 								domain is ignored (regardless if this is starting with a slash or
	 * 								not). </param>
	 * <param name="level">		  	The log level. </param>
	 * <param name="msgObject">	  	An Object to be logged. </param>
	 * <param name="indent">	  	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="loggerFilter">	(Optional) A filter for the loggers to be affected. This
	 * 								parameter enables different loggers to have different domains. A
	 * 								simple string compare without case sensitivity is performed. An
	 * 								asterisk ('*') at the beginning or end of the string is used as a
	 * 								wildcard. Leave null if all loggers should be affected. Use this
	 * 								parameter only in more complex logging scenarios. </param>
	 * <param name="csf">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Line( bool doLog, String domain, Level level, Object msgObject, int indent = 0, String loggerFilter = null,
							[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( doLog, domain, level, msgObject, indent, loggerFilter, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Logs an Object using the given log level, log domain and indentation and logger filter.
	 * </summary>
	 * <param name="domain">	  	If this is null, the default domain is used. If this is starting
	 * 								with a swung dash ('~') this is interpreted a sub domain to the
	 * 								default domain of the source file. For other values, the default
	 * 								domain is ignored (regardless if this is starting with a slash or
	 * 								not). </param>
	 * <param name="level">		  	The log level. </param>
	 * <param name="msgObject">	  	An Object to be logged. </param>
	 * <param name="indent">	  	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="loggerFilter">	(Optional) A filter for the loggers to be affected. This
	 * 								parameter enables different loggers to have different domains. A
	 * 								simple string compare without case sensitivity is performed. An
	 * 								asterisk ('*') at the beginning or end of the string is used as a
	 * 								wildcard. Leave null if all loggers should be affected. Use this
	 * 								parameter only in more complex logging scenarios. </param>
	 * <param name="csf">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Line( String domain, Level level, Object msgObject, int indent = 0, String loggerFilter = null,
							[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( true, domain, level, msgObject, indent, loggerFilter, csf,cln,cmn );
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Logs an Object using the given log level, indentation and logger filter and the default
	 *  domain set for the scope.
	 * </summary>
	 * <param name="level">		  	The log level. </param>
	 * <param name="msgObject">	  	An Object to be logged. </param>
	 * <param name="indent">	  	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="loggerFilter">	(Optional) A filter for the loggers to be affected. This
	 * 								parameter enables different loggers to have different domains. A
	 * 								simple string compare without case sensitivity is performed. An
	 * 								asterisk ('*') at the beginning or end of the string is used as a
	 * 								wildcard. Leave null if all loggers should be affected. Use this
	 * 								parameter only in more complex logging scenarios. </param>
	 * <param name="csf">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">		  	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	[Conditional("ALOX_DEBUG")]
	public static void Line( Level level, Object msgObject, int indent = 0, String loggerFilter = null,
							[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG
			LOX.Line( true, null, level, msgObject, indent, loggerFilter, csf,cln,cmn );
		#endif
	}
}
 

} // namespace
