// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:	Lox
//  File:	Lox.cs													Namespace:  com.aworx.lox.core
// #################################################################################################

using System.Runtime.CompilerServices;
using System;
using System.Collections.Generic;
using System.Text;
using com.aworx.util;
using com.aworx.lox.core;
using com.aworx.lox.loggers;

#if (!ALOX_NO_THREADS) 
	using System.Threading;
using System.Globalization;
#endif

namespace com.aworx.lox {


/** ***********************************************************************************************
} * <summary>
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
 *  class, but to use Log instead, which is a 100% static wrapper around this one. In other words,
 *  Log incorporates one static instance of this class and mirrors the whole interface with
 *  static methods.
 *  
 *  Furthermore, all invocations of methods of Log are pruned in release code, while invocations
 *  of methods of Lox not. Hence, this class and interface should be used in release log 
 *  scenarios. Of course, the use of class Log and Lox can be mixed, to enable debug log output
 *  in parallel to release output.
 * </summary>
 **************************************************************************************************/
public class Lox
{
	// #################################################################################################
	// Public fields (accessible in release code)
	// #################################################################################################

	/** <summary>	The version of ALox. </summary> */
	public  static readonly	String		Version					="1.1.0";

	/** 
	 * <summary>
	 *  A counter for the quantity of calls. The count includes logs that were suppressed by disabled
	 *  log rootDomain and those suppressed by the optional log condition parameter. Hence, it can
	 *  also be used as a condition to log only every n-th time by calling using the conditional parameter
	 *  of #Line(), e.g.: *Lox.Line( (Log.qtyLogCalls % n) == 0, ...*.
	 * </summary>
	 */
	public 				int				CntLogCalls				=0;

	/**
	 * <summary>
	 *  This is the ThreadLock (mutex) for the Lox class. Each Lox method uses this mutex. If thread
	 *  safeness is not needed for the logging system (see user manual) the mutex can be switched of
	 *  using ThreadLock.setUnsafe(). The goal here would be to increase logging performance. This is
	 *  really a very seldom case, and it is better to be kept in safe mode.
	 * </summary>
	 */
	public 				ThreadLock		Lock
					#if ALOX_NO_THREADS
																=new ThreadLock( true, true ); // set unsafe
					#else
																=new ThreadLock();
					#endif

	/**
	 * <summary>
	 *  This is the log domain name used by this class. By manipulating this Domains log level, the
	 *  verbosity of this interface class can be controlled. For example, in 'Info' level, calls to
	 *  #RegDomain and #SetDomain are logged which can be helpful to determine the log
	 *  domains that are created by libraries and larger projects.
	 * </summary>
	 */
	public 				String			InternalDomain			="ALOX";

	#if !ALOX_NO_THREADS

		/** 
		 * <summary>
		 *   Dictionary to translate thread ids into something maybe nicer/shorter. The dictionary has to
		 *   be filled by the user of the library.
		 * </summary>
		 */
		public 	Dictionary<int, String>	ThreadDictionary	=new Dictionary<int, String>();
	#endif


	#if ALOX_DEBUG || ALOX_REL_LOG

		// #################################################################################################
		// Private/protected fields
		// #################################################################################################
		/// <summary>The loggers. At least one logger (e.g. ConsoleLogger) needs to be created.</summary>
		protected 		List<Logger>					loggers;

		/// <summary>Optional default domains for a source file</summary>
		protected 		Dictionary<MString, MString>	defaultDomains		= new Dictionary<MString, MString>();

		/// <summary>Code markers</summary>
		protected 		Dictionary<MString, Object>		markers				= new Dictionary<MString, Object>();

		/// <summary>	An instance to store the actual caller info in. </summary>
		protected 		CallerInfo						caller				=new CallerInfo();

		/// <summary> The resulting domain name. </summary>
		protected 		MString							resDomain			=new MString( 32 );

		/// <summary> A temporary domain name. </summary>
		protected 		MString							tempDomain			=new MString( 32 );
		
		/// <summary> A temporary MString, following the "create once and reuse" design pattern. </summary>
		protected 		MString							tempMS				=new MString( 256 );

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
		public  Logger GetLogger( String loggerName )
		{
			try { Lock.Aquire();

				// search logger
				foreach ( Logger logger in loggers )
				if ( logger.Name.Equals( loggerName, StringComparison.OrdinalIgnoreCase ) )
					return logger;

				// not found
				return null;

			} finally { Lock.Release(); } 
		}

	#endif


	// #################################################################################################
	// Interface (auto removed)
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>
	 *  Adds a logger to the Log interface. Each log call that is performed through this interface
	 *  will be forwarded to this logger, unless filtered out with optional filter parameter. The
	 *  logger will then check it's domain level against the given log level to decide whether a log
	 *  should performed.
	 * </summary>
	 * <param name="logger">			 	The logger to be added. </param>
	 * <param name="internalDomainLevel">	(Optional) The desired domain level for the
	 * 										#InternalDomain which is used for logging code of class
	 * 										Lox itself. For console loggers this can be set to
	 * 										**All**, for log streams dedicated to a certain domain,
	 * 										this should be set to **Off**. </param>
	 * <param name="csf"> 	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln"> 	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn"> 	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	public  void AddLogger( Logger logger, Log.DomainLevel internalDomainLevel= Log.DomainLevel.WarningsAndErrors,
							[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();

				// Find or Create the internal domain (LOX) for logger  and set level 
				resDomain.Clear().Append( InternalDomain );
				(		logger.FindDomain  ( resDomain ) 
					??	logger.CreateDomain( resDomain )  ).SetLevel( internalDomainLevel, false );

				// create logger list if not existent
				if ( loggers == null )
					loggers= new List<Logger>();

				// if list existed, check if logger was added already
				else if ( loggers.Contains( logger ) )
				{
					// log info on this
					saveAndSet( csf, cln, cmn, false, null );
					internalLog( Log.Level.Warning,	tempMS.Clear().Append("Lox.AddLogger(): Logger \"").Append( logger.Name ).Append("\" already exists. Not added.") );
					return;
				}

				// add logger to list
				loggers.Add( logger );

				// log info on this
				saveAndSet( csf, cln, cmn, false, null );
				internalLog( Log.Level.Info,	tempMS.Clear().Append("Lox.AddLogger(): Logger \"").Append(logger.Name).Append("\" added. Internal Domain Level set to: ").Append(internalDomainLevel.ToString()) );

			} finally { Lock.Release(); } 
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>	Removes all loggers that match the filter name from this  interface. </summary>
	 * <param name="loggerFilter">	(Optional) A filter for the loggers to be affected. A simple
	 * 								string compare without case sensitivity is performed. An asterisk
	 * 								('*') at the beginning or end of the string is used as a
	 * 								wildcard. Defaults to null which causes all loggers to be
	 * 								removed. </param>
	 **************************************************************************************************/
	public void RemoveLoggers( String loggerFilter= null )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();

				// check logger list
				if ( loggers == null )
					return;

				// loop over all loggers backwards
				for(int i= loggers.Count - 1; i >= 0; i--)
					if ( simpleWildcardFilter( loggers[ i ], loggerFilter ) )
						loggers.RemoveAt( i );

			} finally { Lock.Release(); } 
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
	public  void SetConsumableSourcePathPrefix( String cspp,	
												[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();

				// save caller info
				saveAndSet( csf, cln, cmn, false, null );

				// save the parameter in the caller info
				caller.ConsumableSourcePathPrefixString= cspp;

				// log info on this
				internalLog( Log.Level.Info, tempMS.Clear().Append("Lox: Consumable source path prefix set to:  \"").Append(cspp).Append("\"") );

			} finally { Lock.Release(); } 
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
	public  void RegDomain( String	domain,	 Log.Scope scope,
							[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();

				// save caller info and get resulting domain
				saveAndSet( csf, cln, cmn, true, domain);
				MString domainToRegister= tempDomain.Clear().Append( resDomain );

				// check parameter
				if ( String.IsNullOrEmpty( domain ) )
				{
					internalLog( Log.Level.Error,	tempMS.Clear().Append("Lox.RegDomain(): Empty domain given. Not registered.") );
					return;
				}

				// loop over all loggers (without filtering)
				foreach ( Logger logger in loggers )
				{
					// search domain
					LogDomain logDomain= logger.FindDomain( domainToRegister );

					// not found?
					if ( logDomain == null )
					{
						//create domain
						logger.CreateDomain( domainToRegister );

						// log info on this
						internalLog( Log.Level.Info, tempMS.Clear().Append("Lox.RegDomain(): Domain \"").Append(domainToRegister).Append("\" created in logger: ").Append(logger.Name) );
					}
				}

				// set domain as default for calling source file's log calls
				if ( scope != Log.Scope.None )
				{
					MString key= new MString(csf.Length + cmn.Length + 1);
					key.Append( csf );
					if ( scope == Log.Scope.Method )
						key.Append( '#' ).Append( cmn );

					// store domain in hash table
					MString previous; defaultDomains.TryGetValue( key, out previous );
					defaultDomains[key]= new MString( domainToRegister );

					// log info on this
					if ( previous == null )
						internalLog( Log.Level.Info,	tempMS.Clear().Append("Lox.RegDomain(): Domain \"").Append(domainToRegister).Append("\" set as default for scope \"").Append(scope.ToString()).Append('\"') );
					else
						internalLog( Log.Level.Warning,	tempMS.Clear().Append("Lox.RegDomain(): Replacing default Domain \"").Append(previous)
																	  .Append("\" by \"").Append(domainToRegister).Append("\" as default for scope \"").Append(scope.ToString()).Append('\"') );
				}

			} finally { Lock.Release(); } 
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
	public  void SetDomain(	String	domain,				Log.DomainLevel	domainLevel, 
							bool	recursive= true,	String		loggerFilter= null,
							[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();

				// save caller info and get resulting domain
				saveAndSet( csf, cln, cmn, true, domain);
				MString domainToSet= tempDomain.Clear().Append( resDomain );

				// loop over loggers
				foreach ( Logger logger in loggers )
				{
					// logger filtered out?
					if ( !simpleWildcardFilter( logger, loggerFilter ) )
						continue;

					// create domain (maybe not existent yet)
					LogDomain logDomain= logger.CreateDomain( domainToSet );
					logDomain.SetLevel( domainLevel, recursive ) ;

					// log info on this (has to be done last, for the case that domain is the internal domain!)
					internalLog( Log.Level.Info,	tempMS.Clear().Append("Lox.SetDomain(): Domain \"").Append(domainToSet).Append("\" log level set to \"").Append(domainLevel.ToString())
																  .Append("\" for logger \"").Append(logger.Name).Append('\"') );
				}


			} finally { Lock.Release(); } 
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
	public  void SetDisabled(	bool disabled, String loggerFilter= null,
									[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();
			
				saveAndSet( csf, cln, cmn, false, null );
				foreach ( Logger logger in loggers )
				{
					if ( simpleWildcardFilter( logger, loggerFilter ) )
					{
						logger.IsDisabled= disabled;

						// log info on this
						internalLog( Log.Level.Info,	tempMS.Clear().Append("Lox.SetDisabled(): Logger \"").Append(logger.Name).Append("\" ").Append((disabled ? "disabled" : "enabled"))  );
					}
				}
			
			} finally { Lock.Release(); } 
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
	public  void SetStartTime( DateTime? startTime= null, String loggerFilter= null,
									 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();

				// check if logger was initialized
				saveAndSet( csf, cln, cmn, false, null );

				// check if start time was set
				long tickTime= startTime.HasValue	?	Ticker.FromDotNetDateTime( startTime.Value )
													:	Ticker.Now();

				// loop over all loggers
				foreach ( Logger logger in loggers )
				{
					// logger filtered out? -> skip
					if ( !simpleWildcardFilter( logger, loggerFilter ) )
						continue;

					// set new start time and last log time stamp
					logger.TimeOfCreation.SetTo( tickTime );
					logger.TimeOfLastLog .SetTo( tickTime );

					// log info on this
					internalLog( Log.Level.Info,	tempMS.Clear().Append("Lox.SetStartTime(): Start time of \"").Append(logger.Name).Append("\" set to: ").Append(startTime.HasValue? startTime.Value.ToString() : "\"now\"")  );
				}

			} finally { Lock.Release(); } 
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
	public  void MapThreadName(	String threadName, int id= -1,
								[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )

	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			#if ALOX_NO_THREADS
			#else
				try { Lock.Aquire();

					// get current thread id
					String origThreadName= null;
					if ( id < 0 )
					{
						Thread t=		Thread.CurrentThread;
						id=				t.ManagedThreadId;
						origThreadName= t.Name;
					}

					// add entry
					ThreadDictionary[id]= threadName;
	
					// log info on this
					saveAndSet( csf, cln, cmn, false, null );
					tempMS.Clear().Append("Lox: Mapped thread ID ").Append(id).Append(" to \"").Append(threadName).Append("\".");
					if ( !String.IsNullOrEmpty( origThreadName )  )
						tempMS.Append(" Original thread name was \"").Append(origThreadName).Append("\".");
					internalLog( Log.Level.Info, tempMS );

				} finally { Lock.Release(); } 
			#endif
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  This method is used store a marker object in the logging system. Markers are stored
	 *  and retrieved relative to a given Log.Scope. In combination with Lox.GetMarker,
	 *  this method provides an easy way to trace the last marked position, e.g. in the case of an
	 *  exception. Within the exception handler, use Lox.GetMarker to retrieve the last marker
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
	public  void SetMarker(	Object marker, Log.Scope scope,
									[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();

				// build key string
				MString key= new MString(64);
				if ( scope == Log.Scope.None )
					key.Append( "$GLOBAL" );
				else
				{
					key.Append( csf );
					if ( scope == Log.Scope.Method )
						key.Append( '#' ).Append( cmn );
				}

				// save marker ([] overwrites any existing)
				markers[ key ]= marker;

				// log info on this
				saveAndSet( csf, cln, cmn, false, null );
				internalLog( Log.Level.Verbose, tempMS.Clear().Append("Lox: Marker set (").Append(( marker != null ? marker.ToString() : "null")).Append(')')  );
	
			} finally { Lock.Release(); }
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Retrieves the most recently marker object stored using Lox.SetMarker. Markers are stored
	 *  and retrieved relative to a given Log.Scope. In combination with Lox.SetMarker,
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
	public  void GetMarker( Object[] markerPointer, Log.Scope scope,
								  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();

				// build key string
				tempMS.Clear();
				if ( scope == Log.Scope.None )
					tempMS.Append( "$GLOBAL" );
				else
				{
					tempMS.Append( csf );
					if ( scope == Log.Scope.Method )
						tempMS.Append( '#' ).Append( cmn );
				}

				// get marker
				Object marker;
				markers.TryGetValue( tempMS, out marker );
				markerPointer[0]= marker;

				// log info on this
				saveAndSet( csf, cln, cmn, false, null );
				internalLog( Log.Level.Verbose, tempMS.Clear().Append("Lox: Marker retrieved (").Append(( marker != null ? marker.ToString() : "null")).Append(')') );
			} finally { Lock.Release(); } 
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  This method logs the configuration this Lox and it's encapsulated objects.
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
	public  void LogConfig(	String			domain,
							Log.Level		level,
							String			headLine,
							String			loggerFilter= null,
							[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();
		
				// count overall calls 
				CntLogCalls++;

				// check if we have a logger, merge domain string with default
				saveAndSet( csf, cln, cmn, true, domain );

				// we write log all into a Buffer first
				MString buf=		new MString( 2048 );

				// log a headline?
				if ( !String.IsNullOrEmpty(headLine) )
					buf.Append( headLine ).NewLine();

				// basic lox info
				buf.Append( "Version:      ").Append( Version		 ).NewLine();
				buf.Append( "Intern. dom.: ").Append( InternalDomain ).NewLine();
				buf.Append( "Thread safe:  ").Append( Lock.IsUnsafe()  ? "No (!)" : "Yes" ).NewLine();
				buf.Append( "No. of calls: ").Append( CntLogCalls	).NewLine();

				// code markers
				if ( markers.Count > 0 ) buf.NewLine();
				buf.Append( "Code markers: ").Append( markers.Count  ).NewLine();
				foreach (  MString key in markers.Keys )
				{
					Object o= markers[ key ];
					buf.Append( "  Marker:   "  ).Append(  o != null ? o.ToString() : "null" ).Append('\"').NewLine();
					buf.Append( "    Scope: \"" ).Append(  key ).NewLine();
				}

				// default domains
				if ( defaultDomains.Count > 0 ) buf.NewLine();
				buf.Append( "Def. domains: ").Append( defaultDomains.Count  ).NewLine();
				foreach (  MString key in defaultDomains.Keys )
				{
					buf.Append( "  Domain:   " ); 
					MString s= defaultDomains[ key ];
					int zeroPos= buf.Length;
					if ( s != null ) buf.Append( s ); else buf.Append( "null" );
					buf.Tab( 13, zeroPos );
					buf.Append( "Scope: \"" ).Append( key ).Append( '\"' ).NewLine();
				}


				// Loggers (and their domains)
				if ( loggers.Count > 0 ) buf.NewLine();
				buf.Append( "Loggers:      ").Append( loggers.Count	).NewLine();
				foreach ( Logger logger in loggers )
				{
					buf.NewLine();
					buf.Append( "  Logger: \""			).Append(  logger.Name).Append( '\"')		 .NewLine();
					buf.Append( "    Creation time: "	).Append(  logger.TimeOfCreation.ToString()	).NewLine();
					buf.Append( "    Lines logged:  "	).Append(  logger.CntLogs					).NewLine();
					buf.Append( "    Domains:"			)											 .NewLine();

					foreach (LogDomain logDomain in logger.RootDomain.SubDomains)
						logConfigDomainRecursive( logDomain, 3, "      " , buf);
				}

				// now, log it out
				foreach ( Logger logger in loggers )
					if ( simpleWildcardFilter( logger, loggerFilter ) )
						logger.Line( resDomain, level, buf, 0, caller ); 

			} finally { Lock.Release(); } 
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
	public  void Verbose( Object msg, int indent=	0,
						  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( true, null, Log.Level.Verbose, msg, indent, null, csf, cln, cmn );
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
	public  void Verbose( String domain, Object msg, int indent= 0,
						  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( true, domain, Log.Level.Verbose, msg, indent, null, csf, cln, cmn );
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
	public  void Info(	String msg, int indent= 0,
						[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( true,  null, Log.Level.Info, msg, indent, null, csf, cln, cmn );
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
	 * <param name="msg">   	An Object to be logged.	 </param>
	 * <param name="indent">	(Optional) The indentation in the output. Defaults to 0. </param>
	 * <param name="csf">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cln">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 * <param name="cmn">   	(Optional) Caller info, compiler generated. Please omit. </param>
	 **************************************************************************************************/
	public  void Info(	String domain, Object msg, int indent= 0,
						[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( true, domain, Log.Level.Info, msg, indent, null, csf, cln, cmn );
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
	public  void Warning( Object msg, int indent= 0,
						  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( true, null, Log.Level.Warning, msg, indent, null, csf, cln, cmn );
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
	public  void Warning( String domain, Object msg, int indent= 0,
						  [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( true, domain, Log.Level.Warning, msg, indent, null, csf, cln, cmn );
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
	public  void Error(	Object msg, int indent= 0,
						[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( true, null, Log.Level.Error, msg, indent, null, csf, cln, cmn );
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
	public  void Error(	String domain, Object msg, int indent= 0,
						[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( true, domain, Log.Level.Error, msg, indent, null, csf, cln, cmn );
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
	public  void Assert( bool trueOrLog, Object msg, int indent= 0,
						 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( !trueOrLog, null, Log.Level.Error, msg, indent, null, csf, cln, cmn );
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
	public  void Assert( bool trueOrLog, String domain, Object msg, int indent= 0,
						 [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( !trueOrLog, domain, Log.Level.Error, msg, indent, null, csf, cln, cmn );
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
	public  void Line( bool doLog, String domain, Log.Level level, Object msgObject, int indent= 0, String loggerFilter= null,
					   [CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			try { Lock.Aquire();

				// count overall calls 
				CntLogCalls++;

				// check the condition
				if ( !doLog )
					return;

				// check if we have a logger, merge domain string with default
				saveAndSet( csf, cln, cmn, true, domain );

				// loop over all loggers 
				foreach ( Logger logger in loggers )
					if ( simpleWildcardFilter( logger, loggerFilter ) )
						logger.Line( resDomain, level, msgObject, indent, caller );
	
			} finally { Lock.Release(); }
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
	public void Line(	String			domain,
						Log.Level		level,
						Object			msgObject,
						int				indent=				0,
						String			loggerFilter=		null,
						[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( true, domain, level, msgObject, indent, loggerFilter, csf,cln,cmn );
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
	public void Line(	Log.Level		level,
						Object			msgObject,
						int				indent=				0,
						String			loggerFilter=		null,
						[CallerFilePath] String csf="",[CallerLineNumber] int cln= 0,[CallerMemberName] String cmn="" )
	{
		#if ALOX_DEBUG || ALOX_REL_LOG
			Line( true, null, level, msgObject, indent, loggerFilter, csf,cln,cmn );
		#endif
	}

	//*****************************************************************************
	//***  internals
	//*****************************************************************************
	#if ALOX_DEBUG || ALOX_REL_LOG

		/** ***********************************************************************************************
		 * <summary>
		 *  This method performs the following things:
		 *  
		 *  a) stores the caller info within the singleton field of this class for further reference
		 *  within this a log operation
		 *  
		 *  b) checks if an instance Logger attached already. If not, a corresponding console logger is created  
		 *  and added
		 *  
		 *  c) the given domain string is merged with the default domain that optionally is set to the callers
		 *  source. This is done only if the given domain name is starting with a swung dash("~").
		 *  
		 * </summary>
		 * <param name="csf">		  	Source file name of the caller, originally compiler generated. </param>
		 * <param name="cln">		  	Line number in source file, originally compiler generated. </param>
		 * <param name="cmn">		  	Method name of the caller, originally compiler generated. </param>
		 * <param name="getResDomain">	True to get resulting domain is returned. </param>
		 * <param name="domain">	  	If this is null, the default domain is used. If this is starting
		 * 								with a swung dash ('~') this is interpreted a sub domain to the
		 * 								default domain of the source file. For other values, the default
		 * 								domain is ignored (regardless if this is starting with a slash or
		 * 								not). </param>
		 * <returns>	The resulting domain if parameter domain was not null. Null otherwise. </returns>
		 **************************************************************************************************/
		protected  void saveAndSet( String csf, int cln, String cmn, bool getResDomain, String domain  )
		{
			// a) store caller info
			caller.Set( csf, cln, cmn 
							#if !ALOX_NO_THREADS
										, ThreadDictionary 
							#endif
				);

			// b) check if we got any logger
			if ( loggers == null || loggers.Count == 0 )
			{
				AddLogger( new ConsoleLogger( "CONSOLE" ) );
				internalLog( Log.Level.Warning,	tempMS.Clear().Append("Lox: Class 'Log' was used without prior creation of a Log instance. ConsoleLogger Logger created as default.") );
			}

			// c) merge domain name with default domain
			if ( getResDomain )
			{
				// clear resulting domain name buffer
				resDomain.Clear();
				
				// get default domain name (if needed later)
				MString	defaultDomain=	null;
				bool	noDomainGiven=	String.IsNullOrEmpty( domain );
				if ( noDomainGiven || domain[0] == '~' )
				{
					// get default domain
					tempMS.Clear().Append( caller.SourceFileName );
					int strLengthSourceOnly= tempMS.Length;
					tempMS.Append( '#' ).Append( caller.MethodName );
					defaultDomains.TryGetValue( tempMS, out defaultDomain );
					if ( defaultDomain == null || defaultDomain.Length == 0 )
					{
						tempMS.Length= strLengthSourceOnly;
						tempMS.Hash=   0; // clear hash value as we modified the MString
						defaultDomains.TryGetValue( tempMS, out defaultDomain );
					}
				}

				// no domain given
				if ( noDomainGiven )
				{
					// neither domain nor default domain given
					if (  defaultDomain == null || defaultDomain.Length == 0 )
					{
						internalLog( Log.Level.Warning, 
									 tempMS.Clear()	.Append("Lox: No log domain given and default domain not set for scope \"")
													.Append(caller.SourceFileName).Append(" - ").Append(caller.SourceFileName).Append('\"')
									);
						return;
					}
					
					// return resulting domain
					resDomain.Append( defaultDomain );
					return;
				}

				// domain starts with '~' ?	Relative path
				int start=	0;
				if ( domain[0] == '~' )
				{
					// cut the ~ character
					start=	1;
					
					// found one? build complete path
					if ( defaultDomain != null )
						resDomain.Append( defaultDomain );
					else
					{
						// not set? -> remove the ~ symbol and go ahead
						internalLog( Log.Level.Warning, 
									 tempMS.Clear()	.Append("Lox: Relative domain path given: \"").Append(domain)
													.Append("\", but default domain is not set for scope \"")
													.Append(caller.SourceFileName).Append(" - ").Append(caller.SourceFileName).Append('\"')
									);
					}
				}

				// remove any potential leading separator
				int len=	domain.Length;
				while (start < len && ( LogDomain.DomainSeparatorChars.IndexOf( domain[ start ] ) >= 0 ) )
					start++;
				
				// add domain to the path
				if (start < len )
				{
					if ( resDomain.Length > 0 )
						resDomain.Append( '/' );
					resDomain.Append( domain, start );
				}
			}
		}

		/** ***********************************************************************************************
		 * <summary>
		 *  Logs an internal error message to the domain given by field InternalDomain. Attn: must only
		 *  be called after saveAndSet() was performed.
		 * </summary>
		 * <param name="level">	The log level. </param>
		 * <param name="msg">  	The message. </param>
		 **************************************************************************************************/
		protected  void internalLog( Log.Level level, MString msg )
		{
			// decrease log counter, as internal Log should not count
			CntLogCalls--;

			// log msg on InternalDomain
			Line( true, InternalDomain, level, msg, 0, null, caller.SourceFileName, caller.LineNumber, caller.MethodName );

			// reset the caller timestamp to avoid negative time differences in subsequent log call
			caller.TimeStamp.SetToNow();
		}

		/** ***********************************************************************************************
		 * <summary>
		 *  Compares a loggers name with a filter string with simplest wildcard support ('*') at the
		 *  beginning or end of the string. If loggerFilter is null, a match is indicated.
		 * </summary>
		 * <param name="logger">	  	The logger to be filtered. </param>
		 * <param name="loggerFilter">	The filter. </param>
		 * <returns>	True if logger is not filtered out. </returns>
		 **************************************************************************************************/
		private static bool simpleWildcardFilter( Logger logger, string loggerFilter )
		{
			const string asterisk = "*";

			// null or empty? -> return TRUE (!)
			if ( String.IsNullOrEmpty( loggerFilter ) )
				return true;

			// wildcard at start?
			bool startWC= false;
			if ( loggerFilter.StartsWith ( asterisk ) )
			{
				loggerFilter=	loggerFilter.Substring( 1 );
				startWC=		true;
			}

			// wildcard at end?
			bool endWC= false;
			if ( loggerFilter.EndsWith ( asterisk ) )
			{
				loggerFilter=	loggerFilter.Substring( 0, loggerFilter.Length - 1 );
				endWC=		true;
			}

			// wildcard at start?
			if ( startWC )
			{
				// both?
				if ( endWC )
					return logger.Name.IndexOf( loggerFilter, StringComparison.OrdinalIgnoreCase ) >= 0;

				// at start only
				return logger.Name.EndsWith( loggerFilter, StringComparison.OrdinalIgnoreCase );
			}

			// at end
			if ( endWC)
				return logger.Name.StartsWith( loggerFilter, StringComparison.OrdinalIgnoreCase );

			// no wildcard
			return logger.Name.Equals( loggerFilter, StringComparison.OrdinalIgnoreCase );
		}

		/** ***********************************************************************************************
		 * <summary> Internal method used by LogConfig() to recursively log LogDomain instances. </summary>
		 * <param name="domain"> 	The LogDomain instance to log out. </param>
		 * <param name="indent"> 	The indentation in the output, recursively increased.. </param>
		 * <param name="domPath">	Actual path releative to recursion, soley for log output. </param>
		 * <param name="buf">	 	The buffer to log to. </param>
		 **************************************************************************************************/
		protected  void logConfigDomainRecursive( LogDomain domain, int indent, String domPath, MString buf)
		{
			// append /ME to domain path string
			domPath= domPath + "/" + domain.Name;

			// add  domain name and log level  
			int zeroPos= buf.Length;
			buf.Append( domPath  )	.Tab( 25, zeroPos)	.Append( domain.GetLevel().ToString() )  .NewLine();
		
			// loop over all sub domains (recursion)
			foreach ( LogDomain subDomain in domain.SubDomains )
				logConfigDomainRecursive( subDomain, indent + 1, domPath, buf );
		}

	#endif // ALOX_DEBUG || ALOX_REL_LOG
}
 

	

} // namespace
