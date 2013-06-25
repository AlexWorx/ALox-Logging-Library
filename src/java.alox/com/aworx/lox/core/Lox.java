package com.aworx.lox.core;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

import com.aworx.lox.*;
import com.aworx.lox.Log.Scope;
import com.aworx.util.*;

/**************************************************************************************************
 * This class acts as a container for Loggers and provides a convenient interface into them.
 * Features are:
 * 
 * a) Store and log into one or several Logger instances at once b) Thread safeness c) Store and
 * use of default domain names  
 * d) Store and manage caller information  
 * d) Provides shortcuts to frequently used logging tasks.  
 * e) Store "code markers" and retrieve for simple tracing in log statements  
 * f) Count log operations  
 * 
 * This class is 100% not static. In standard log scenarios, it is recommend **not** to use this
 * class, but to use Log instead, which is a 100% static wrapper around this one. In other words,
 * Log incorporates one static instance of this class and mirrors the whole interface with
 * static methods.
 * 
 * Furthermore, all invocations of methods of Log are pruned in release code, while invocations
 * of methods of Lox not. Hence, this class and interface should be used in release log
 * scenarios. Of course, the use of class Log and Lox can be mixed, to enable debug log output
 * in parallel to release output.
 **************************************************************************************************/
public class Lox
{
	// #################################################################################################
	// Public fields (accessible in release code)
	// #################################################################################################

	/** The version of ALox. */
	public  final static String			version					="1.0.4";

    /**
     * A counter for the quantity of calls. The count includes logs that were suppressed by disabled
     * log rootDomain and those suppressed by the optional log condition parameter. Hence, it can
     * also be used as a condition to log only every n-th time by calling using the conditional
     * parameter of #Line(), e.g.: *Lox.Line( (Log.qtyLogCalls % n) == 0, ...*.
     */
	public 				int				cntLogCalls				=0;

	/**
	 *  This is the ThreadLock (mutex) for the Lox class. Each Lox method uses this mutex. If thread
	 *  safeness is not needed for the logging system (see user manual) the mutex can be switched of
	 *  using ThreadLock.setUnsafe(). The goal here would be to increase logging performance. This is
	 *  really a very seldom case, and it is better to be kept in safe mode.
	 */
	public 				ThreadLock		lock					=new ThreadLock();

	/**
	 *  This is the log domain name used by this class. By manipulating this Domains log level, the
	 *  verbosity of this interface class can be controlled. For example, in 'Info' level, calls to
	 *  #RegDomain and #SetDomain are logged which can be helpful to determine the log
	 *  domains that are created by libraries and larger projects.
	 */
	public 				String			internalDomain			="ALOX";
	
	/**  
	 * The prefix of packages.classes.methods on the stack that are ignored when identifying the caller info.
	 * Usually this is "com.aworx.lox" and must not be changed!
	 */
	public				String			omittablePackagePrefix	= "com.aworx.lox";
	

	//#if !ALOX_NO_THREADS

		/** 
		 *   Dictionary to translate thread ids into something maybe nicer/shorter. The dictionary has to
		 *   be filled by the user of the library.
		 */
		public 	HashMap <Long, String>	threadDictionary	=new HashMap <Long, String>();

	//#endif


	//#if ALOX_DEBUG || ALOX_REL_LOG

		// #################################################################################################
		// Private/protected fields
		// #################################################################################################
		/** The loggers. At least one logger (e.g. ConsoleLogger) needs to be created.*/
		protected 		ArrayList<Logger>				loggers;

		/** Optional default domains for a source file*/
		protected 		HashMap<MString, MString>		defaultDomains		= new HashMap<MString, MString>();

		/** Code markers*/
		protected 		HashMap<MString, Object>		markers				= new HashMap<MString, Object>();

		/** An instance to store the actual caller info in. */
		protected 		CallerInfo						caller				=new CallerInfo();

		/**  The resulting domain name. */
		protected 		MString							resDomain			=new MString( 32 );

		/**  A temporary domain name. */
		protected 		MString							tempDomain			=new MString( 32 );
		
		/**  A temporary MString, following the "create once and reuse" design pattern. */
		protected 		MString							tempMS				=new MString( 256 );

		// #################################################################################################
		// Interface (not auto removed)
		// #################################################################################################

        /**************************************************************************************************
         * Retrieve an instance of a Logger by its name. Note: This function is not automatically
         * removed from the release code because of technical restrictions. It has to be conditionally
         * compiled by enclosing calls to it with "//#if ... //#endif" statements.
         *
         * @param loggerName    The name of the logger to search for (case insensitive)
         *
         * @return  The logger, null if not found.
         **************************************************************************************************/
		public  Logger getLogger( String loggerName )
		{
			try { lock.aquire();

				// search logger
				for ( Logger logger : loggers )
					if ( logger.name.equalsIgnoreCase( loggerName ) )
						return logger;

				// not found
				return null;

			} finally { lock.release(); } 
		}

	//#endif


	// #################################################################################################
	// Interface (auto removed)
	// #################################################################################################

    /**************************************************************************************************
     * Adds a logger to the Log interface. Each log call that is performed through this Lox will be
     * forwarded to this logger, unless filtered out with optional filter parameter. The logger will
     * then check it's domain level against the given log level to decide weather a log should
     * performed.
     *
     * @param logger    The logger to be added.
     **************************************************************************************************/
	public  void addLogger( Logger logger )	{ addLogger( logger, Log.DomainLevel.WarningsAndErrors ); }

    /**************************************************************************************************
     * Adds a logger to the Log interface. Each log call that is performed through this Lox will be
     * forwarded to this logger, unless filtered out with optional filter parameter. The logger will
     * then check it's domain level against the given log level to decide weather a log should
     * performed.
     *
     * @param logger                The logger to be added.
     * @param internalDomainLevel   The desired domain level for the  #InternalDomain which is used
     *                              for logging code of class Lox itself. For console loggers this
     *                              can be set to **All**, for log streams dedicated to a certain
     *                              domain, this should be set to **Off**.
     **************************************************************************************************/
	public  void addLogger( Logger logger, Log.DomainLevel internalDomainLevel )
	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();

				// Find or Create the internal domain (LOX) for logger  and set level
				resDomain.clear().append( internalDomain );
				LogDomain domain= logger.findDomain  ( resDomain );
				if ( domain == null )
					domain= logger.createDomain( resDomain );  
				domain.setLevel( internalDomainLevel, false );

				// create logger list if not existent
				if ( loggers == null )
					loggers= new ArrayList<Logger>();

				// if list existed, check if logger was added already
				else if ( loggers.contains( logger ) )
				{
					// log info on this
					saveAndSet( false, null );
					internalLog( Log.Level.Warning,	tempMS.clear().append("Lox.AddLogger(): Logger \"").append( logger.name ).append("\" already exists. Not added.") );
					return;
				}

				// add logger to list
				loggers.add( logger );

				// log info on this
				saveAndSet( false, null );
				internalLog( Log.Level.Info,	tempMS.clear().append("Lox.AddLogger(): Logger \"").append(logger.name).append("\" added") );

			} finally { lock.release(); } 
		//#endif
	}

    /**************************************************************************************************
     * Removes all loggers that match the filter name from this container.
     *
     * @param loggerFilter  A filter for the loggers to be affected. A simple string compare without
     *                      case sensitivity is performed. An asterisk ('*') at the beginning or end
     *                      of the string is used as a wildcard. Defaults to null which causes all
     *                      loggers to be removed.
     **************************************************************************************************/
	public void removeLoggers( String loggerFilter )
	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();

				// check logger list
				if ( loggers == null )
					return;

				// loop over all loggers backwards
				for(int i= loggers.size() - 1; i >= 0; i--)
					if ( simpleWildcardFilter( loggers.get( i ), loggerFilter ) )
						loggers.remove( i );

			} finally { lock.release(); } 
		//#endif
	}
	public void removeLoggers(  ) { removeLoggers( null ); } 


    /**************************************************************************************************
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
	public  void regDomain( String	domain,	 Log.Scope scope )	
	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();

				// save caller info and get resulting domain
				saveAndSet( true, domain );
				MString domainToRegister= tempDomain.clear().append( resDomain );

				// check parameter
				if ( MString.isNullOrEmpty( domain ) )
				{
					internalLog( Log.Level.Error,	tempMS.clear().append("Lox.RegDomain(): Empty domain given. Not registered.") );
					return;
				}

				// loop over all loggers (without filtering)
				for ( Logger logger : loggers )
				{
					// search domain
					LogDomain logDomain= logger.findDomain( domainToRegister );

					// not found?
					if ( logDomain == null )
					{
						//create domain
						logger.createDomain( domainToRegister );

						// log info on this
						internalLog( Log.Level.Info, tempMS.clear().append("Lox.RegDomain(): Domain \"").append(domainToRegister).append("\" created in logger: ").append(logger.name) );
					}
				}

				// set domain as default for calling source file's log calls
				if ( scope != Log.Scope.None )
				{
					MString key= new MString( caller.packageName.length + caller.className.length + caller.methodName.length + 2);
					key.append( caller.packageName );
					if ( scope != Log.Scope.Package )
						key.append( '#' ).append( caller.className );
					if ( scope == Log.Scope.Method )
						key.append( '#' ).append( caller.methodName );

					// store domain in hash table
					MString previous= defaultDomains.get( key );
					defaultDomains.put( key, new MString( domainToRegister ) );

					// log info on this
					if ( previous == null )
						internalLog( Log.Level.Info,	tempMS.clear().append("Lox.RegDomain(): Domain \"").append(domainToRegister).append("\" set as default for scope \"").append(scope.toString()).append('\"') );
					else
						internalLog( Log.Level.Warning,	tempMS.clear().append("Lox.RegDomain(): Replacing default Domain \"").append(previous)
																	  .append("\" by \"").append(domainToRegister).append("\" as default for scope \"").append(scope.toString()).append('\"') );
				}

			} finally { lock.release(); } 
		//#endif
	}

    /**************************************************************************************************
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
	public  void setDomain(	String	domain,			Log.DomainLevel	domainLevel, 
							boolean	recursive,		String			loggerFilter)
	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();

				// save caller info and get resulting domain
				saveAndSet( true, domain);
				MString domainToSet= tempDomain.clear().append( resDomain );

				// loop over loggers
				for ( Logger logger : loggers )
				{
					// logger filtered out?
					if ( !simpleWildcardFilter( logger, loggerFilter ) )
						continue;

					// create domain (maybe not existent yet)
					LogDomain logDomain= logger.createDomain( domainToSet );
					logDomain.setLevel( domainLevel, recursive ) ;

					// log info on this (has to be done last, for the case that domain is the internal domain!)
					internalLog( Log.Level.Info,	tempMS.clear().append("Lox.SetDomain(): Domain \"").append(domainToSet).append("\" log level set to \"").append(domainLevel.toString())
																  .append("\" for logger \"").append(logger.name).append('\"') );
				}


			} finally { lock.release(); } 
		//#endif
	}

    /**************************************************************************************************
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
	public  void setDomain(	String	domain,	Log.DomainLevel	domainLevel, boolean recursive )	{ setDomain( domain, domainLevel, recursive, null ); } 

    /**************************************************************************************************
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
	public  void setDomain(	String	domain,	Log.DomainLevel	domainLevel )						{ setDomain( domain, domainLevel, true,		 null ); } 


    /**************************************************************************************************
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
	public  void setDisabled(	boolean disabled, String loggerFilter )
	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();
			
				saveAndSet( false, null );
				for ( Logger logger : loggers )
				{
					if ( simpleWildcardFilter( logger, loggerFilter ) )
					{
						logger.isDisabled= disabled;

						// log info on this
						internalLog( Log.Level.Info,	tempMS.clear().append("Lox.SetDisabled(): Logger \"").append(logger.name).append("\" ").append((disabled ? "disabled" : "enabled"))  );
					}
				}
			
			} finally { lock.release(); } 
		//#endif
	}

    /**************************************************************************************************
     * This method is used disable one or more loggers completely without touching the log levels of
     * the domains and hence without the need to restore such log levels later.
     *
     * @param disabled      If true, the logger(src) will be completely disabled, if false the normal
     *                      domain specific log levels will be applied for log decisions.
     **************************************************************************************************/
	public  void setDisabled(	boolean disabled ) { setDisabled( disabled, null ); }

    /**************************************************************************************************
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
	public  void setStartTime( Date startTime, String loggerFilter)
	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();

				// check if logger was initialized
				saveAndSet( false, null );

				// check if start time was set
				long tickTime=  startTime!=null		?	Ticker.fromJavaDate( startTime )
													:	Ticker.now();

				// loop over all loggers
				for ( Logger logger : loggers )
				{
					// logger filtered out? -> skip
					if ( !simpleWildcardFilter( logger, loggerFilter ) )
						continue;

					// set new start time and last log time stamp
					logger.timeOfCreation.setTo( tickTime );
					logger.timeOfLastLog .setTo( tickTime );

					// log info on this
					internalLog( Log.Level.Info,	tempMS.clear().append("Lox.SetStartTime(): Start time of \"").append(logger.name).append("\" set to: ").append(startTime!=null ? startTime.toString() : "\"now\"")  );
				}

			} finally { lock.release(); } 
		//#endif
	}

    /**************************************************************************************************
     * This method is used reset (or to explicitly set) the start time of the logger(s). The only
     * impact is the output of time differences in the log lines. Hence, it is useful to see some
     * absolute time values when doing basic performance tests using the logger. Note: Calls to this
     * method are automatically removed from release code.
     *
     * @param startTime     Optional parameter with the  new start time. Defaults to DateTime.Now if
     *                      omitted.
     **************************************************************************************************/
	public  void setStartTime( Date startTime ) { setStartTime( startTime,	null ); }

    /**************************************************************************************************
     * This method is used reset the start time of the logger(s) to now. The only impact is the
     * output of time differences in the log lines. Hence, it is useful to see some absolute time
     * values when doing basic performance tests using the logger. Note: Calls to this method are
     * automatically removed from release code.
     **************************************************************************************************/
	public  void setStartTime() 				{ setStartTime( null,		null ); }
   
    /**************************************************************************************************
     * This method sets a human readable name to the given thread ID (or current thread) which is
     * optionally included in each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     * @param id            Parameter providing the thread ID. If set to -1, the current thread's ID is
     *                      used.
     **************************************************************************************************/
	public  void mapThreadName(	String threadName, long id )

	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();

				// get current thread id
				String origThreadName= null;
				if ( id < 0 )
				{
					Thread t=		Thread.currentThread();
					id=				t.getId();
					origThreadName= t.getName();
				}

				// add entry
				threadDictionary.put( id, threadName );
	
				// log info on this
				saveAndSet( false, null );
				tempMS.clear().append("Lox: Mapped thread ID ").append((int) id).append(" to \"").append(threadName).append("\".");
				if ( !MString.isNullOrEmpty( origThreadName )  )
					tempMS.append(" Original thread name was \"").append(origThreadName).append("\".");
				internalLog( Log.Level.Info, tempMS );

			} finally { lock.release(); } 
		//#endif
	}

    /**************************************************************************************************
     * This method sets a human readable name to the current thread which is optionally included in
     * each log line.
     *
     * @param threadName    The name of the thread as it should be displayed in the logs.
     **************************************************************************************************/
	public  void mapThreadName(	String threadName ) { mapThreadName( threadName, -1 ); }

    /**************************************************************************************************
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
	public  void setMarker(	Object marker, Log.Scope scope)
	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();

				// create caller info
				saveAndSet( false, null );
				
				// build key string
				MString key= new MString(64);
				if ( scope == Log.Scope.None )
					key.append( "$GLOBAL" );
				else
				{		
					key.append( caller.packageName );
					if ( scope != Log.Scope.Package )
						key.append( '#' ).append( caller.className );
					if ( scope == Log.Scope.Method )
						key.append( '#' ).append( caller.methodName );
				}
	
				// save marker ([] overwrites any existing)
				markers.put( key, marker );
	
				// log info on this
				internalLog( Log.Level.Verbose, tempMS.clear().append("Lox: Marker set (").append(( marker != null ? marker.toString() : "null")).append(')') );
	
			} finally { lock.release(); }
		//#endif
	}

    /**************************************************************************************************
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
	public  void getMarker( Object[] markerPointer, Log.Scope scope )
	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();

				// create caller info
				saveAndSet( false, null );
				
				// build key string
				tempMS.clear();
				if ( scope == Log.Scope.None )
					tempMS.append( "$GLOBAL" );
				else
				{		
					tempMS.append( caller.packageName );
					if ( scope != Log.Scope.Package )
						tempMS.append( '#' ).append( caller.className );
					if ( scope == Log.Scope.Method )
						tempMS.append( '#' ).append( caller.methodName );
				}
	

				// get marker
				Object marker= markers.get( tempMS );
				markerPointer[0]= marker;

				// log info on this
				saveAndSet( false, null );
				internalLog( Log.Level.Verbose, tempMS.clear().append("Lox: Marker retrieved (").append(( marker != null ? marker.toString() : "null")).append(')') );

	
			} finally { lock.release(); } 
		//#endif
	}

    /**************************************************************************************************
     * This method logs the configuration this Lox and its encapsulated objects.
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
	public  void logConfig(	String	domain,			Log.Level		level,
							String	headLine,		String			loggerFilter )
	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();
		
				// count overall calls 
				cntLogCalls++;

				// check if we have a logger, merge domain string with default
				saveAndSet( true, domain );

				// we write log all into a Buffer first
				MString buf=		new MString( 2048 );

				// log a headline?
				if ( !MString.isNullOrEmpty(headLine) )
					buf.append( headLine ).newLine();

				// basic lox info
				buf.append( "Version:      ").append( version		 ).newLine();
				buf.append( "Intern. dom.: ").append( internalDomain ).newLine();
				buf.append( "Thread safe:  ").append( lock.IsUnsafe()  ? "No (!)" : "Yes" ).newLine();
				buf.append( "No. of calls: ").append( cntLogCalls	).newLine();

				// code markers
				if ( markers.size() > 0 ) buf.newLine();
				buf.append( "Code markers: ").append( markers.size()  ).newLine();
				for (  MString key : markers.keySet() )
				{
					Object o= markers.get( key );
					buf.append( "  Marker:  "  ).append(  o != null ? o.toString() : "null" ).newLine();
					buf.append( "   Scope: \"" ).append(  key								).append('\"').newLine();
				}

				// default domains
				if ( defaultDomains.size() > 0 ) buf.newLine();
				buf.append( "Def. domains: ").append( defaultDomains.size()  ).newLine();
				for (  MString key : defaultDomains.keySet() )
				{
					buf.append( "  Domain:   " ); 
					MString s= defaultDomains.get( key );
					int zeroPos= buf.length;
					if ( s != null ) buf.append( s ); else buf.append( "null" );
					buf.tab( 13, zeroPos );
					buf.append( "Scope: \"" ).append( key ).append( '\"' ).newLine();
				}

				// Loggers (and their domains)
				if ( loggers.size() > 0 ) buf.newLine();
				buf.append( "Loggers:      ").append( loggers.size()	).newLine();
				for ( Logger logger : loggers )
				{
					buf.newLine();
					buf.append( "  Logger: \""			).append(  logger.name).append( '\"')		 .newLine();
					buf.append( "    Creation time: "	).append(  logger.timeOfCreation.toString()	).newLine();
					buf.append( "    Lines logged:  "	).append(  logger.cntLogs					).newLine();
					buf.append( "    Domains:"			)											 .newLine();

					for (LogDomain logDomain : logger.rootDomain.subDomains)
						logConfigDomainRecursive( logDomain, 3, "      " , buf);
				}

				// now, log it out
				for ( Logger logger : loggers )
					if ( simpleWildcardFilter( logger, loggerFilter ) )
						logger.line( resDomain, level, buf, 0, caller ); 

			} finally { lock.release(); } 
		//#endif
	}

    /**************************************************************************************************
     * This method logs the configuration the Lox encapsulated in this static Log interface.
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  source file. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param level     The logging level.
     * @param headLine  If given, a separated headline will be logged at first place.
     **************************************************************************************************/
	public  void logConfig( String domain, Log.Level level, String headLine) { logConfig( domain, level, headLine, null ); }
	

    /**************************************************************************************************
     * Log an Object with log level equal to Log.Log.Level.Verbose. This is the highest (most
     * verbose) log level, which is only actually logged if the log domains log level is set to
     * "All". This overloaded version does not offer a domain parameter but relies on a default
     * domain set for the source file this function is used in.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **************************************************************************************************/
	public  void verbose( Object msg, int indent )						{	line( true, null, Log.Level.Verbose, msg, indent,	null );	}

    /**************************************************************************************************
     * Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
     * log level, which is only actually logged if the log domains log level is set to "All". This
     * overloaded version does not offer a domain parameter but relies on a default domain set for
     * the source file this function is used in.
     *
     * @param msg   The message to log out.
     **************************************************************************************************/
	public  void verbose( Object msg )									{	line( true, null, Log.Level.Verbose, msg, 0,		null );	}

    /**************************************************************************************************
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
	public  void verbose( String domain, Object msg, int indent )		{	line( true, domain, Log.Level.Verbose, msg, indent,	null );	}

    /**************************************************************************************************
     * Log an Object with log level equal to Log.Level.Verbose. This is the highest (most verbose)
     * log level, which is only actually logged if the log domains log level is set to "All".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log out.
     **************************************************************************************************/
	public  void verbose( String domain, Object msg )					{	line( true, domain, Log.Level.Verbose, msg, 0,		null );	}


    /**************************************************************************************************
     * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
     * Verbose) log level, which is only actually logged if the log domains log level is set to
     * "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
     * a default domain set for the source file this function is used in.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **************************************************************************************************/
	public  void info( Object msg, int indent )							{	line( true, null, Log.Level.Info, msg, indent,	null );	}

    /**************************************************************************************************
     * Log an Object with log level equal to Log.Level.Info. This is the second highest (after
     * Verbose) log level, which is only actually logged if the log domains log level is set to
     * "Info" or "Verbose". This overloaded version does not offer a domain parameter but relies on
     * a default domain set for the source file this function is used in.
     *
     * @param msg       The message to log out.
     **************************************************************************************************/
	public  void info( Object msg )										{	line( true, null, Log.Level.Info, msg, 0,		null );	}

    /**************************************************************************************************
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
	public  void info( String domain, Object msg, int indent )			{	line( true, domain, Log.Level.Info, msg, indent,	null );	}

    /**************************************************************************************************
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
	public  void info( String domain, Object msg )						{	line( true, domain, Log.Level.Info, msg, 0,		null );	}

    /**************************************************************************************************
     * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
     * are logged if the log domains log level is set to "Warning", "Info" or "All". This overloaded
     * version does not offer a domain parameter but relies on a default domain set for the source
     * file this function is used in.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **************************************************************************************************/
	public  void warning( Object msg, int indent )						{	line( true, null, Log.Level.Warning, msg, indent,	null );	}

    /**************************************************************************************************
     * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
     * are logged if the log domains log level is set to "Warning", "Info" or "All". This overloaded
     * version does not offer a domain parameter but relies on a default domain set for the source
     * file this function is used in.
     *
     * @param msg   The message to log out.
     **************************************************************************************************/
	public  void warning( Object msg )									{	line( true, null, Log.Level.Warning, msg, 0,		null );	}

    /**************************************************************************************************
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
	public  void warning( String domain, Object msg, int indent )		{	line( true, domain, Log.Level.Warning, msg, indent,	null );	}

    /**************************************************************************************************
     * Log an Object with log level equal to Log.Level.Warning. Log messages of this log level are
     * are logged if the log domains log level is set to "Warning", "Info" or "All".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log.
     **************************************************************************************************/
	public  void warning( String domain, Object msg )					{	line( true, domain, Log.Level.Warning, msg, 0,		null );	}

    /**************************************************************************************************
     * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
     * always logged unless domains log level is set to "Off". This overloaded version does not
     * offer a domain parameter but relies on a default domain set for the source file this function
     * is used in.
     *
     * @param msg       The message to log out.
     * @param indent    The indentation in the output.
     **************************************************************************************************/
	public  void error( Object msg, int indent )					{	line( true, null, Log.Level.Error, msg, indent,	null );	}

    /**************************************************************************************************
     * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
     * always logged unless domains log level is set to "Off". This overloaded version does not
     * offer a domain parameter but relies on a default domain set for the source file this function
     * is used in.
     *
     * @param msg       The message to log out.
     **************************************************************************************************/
	public  void error( Object msg )								{	line( true, null, Log.Level.Error, msg, 0,		null );	}

    /**************************************************************************************************
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
	public  void error( String domain, Object msg, int indent )		{	line( true, domain, Log.Level.Error, msg, indent,	null );	}

    /**************************************************************************************************
     * Log an Object with log level equal to Log.Level.Error. Log messages of this log level are are
     * always logged unless domains log level is set to "Off".
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the source
     *                  file. For other values, the default domain is ignored (regardless if this is
     *                  starting with a slash or not).
     * @param msg       The message to log out.
     **************************************************************************************************/
	public  void error( String domain, Object msg )					{	line( true, domain, Log.Level.Error, msg, 0,		null );	}

    /**************************************************************************************************
     * Log a string only if the given condition is not true. Log level will be highest, namely Error
     * if condition is false. This overloaded version does not offer a domain parameter but relies
     * on a default domain set for the source file this function is used in.
     *
     * @param trueOrLog The log is only performed if condition is not true.
     * @param msg       The message to log out.
     * @param indent    the indentation in the output.
     **************************************************************************************************/
	public  void Assert( boolean trueOrLog, Object msg, int indent )	{	line( !trueOrLog, null, Log.Level.Error, msg, indent,	null );	}

    /**************************************************************************************************
     * Log a string only if the given condition is not true. Log level will be highest, namely Error
     * if condition is false. This overloaded version does not offer a domain parameter but relies
     * on a default domain set for the source file this function is used in.
     *
     * @param trueOrLog The log is only performed if condition is not true.
     * @param msg       The message to log out.
     **************************************************************************************************/
	public  void Assert( boolean trueOrLog, Object msg )				{	line( !trueOrLog, null, Log.Level.Error, msg, 0,		null );	}

    /**************************************************************************************************
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
	public  void Assert( boolean trueOrLog, String domain, Object msg, int indent )	{ line( !trueOrLog, domain, Log.Level.Error, msg, indent,	null );	}

    /**************************************************************************************************
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
	public  void Assert( boolean trueOrLog, String domain, Object msg )				{ line( !trueOrLog, domain, Log.Level.Error, msg, 0,		null );	}

    /**************************************************************************************************
     * Provides a the a more flexible but complex way to log a message. The methods #Verbose(),
     * #Info(), #Warning(), #Error() and #Assert() are using this function internally and should
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
	public void line( boolean doLog, String domain, Log.Level level, Object msgObject, int indent, String loggerFilter )
	{
		//#if ALOX_DEBUG || ALOX_REL_LOG
			try { lock.aquire();

				// count overall calls 
				cntLogCalls++;

				// check the condition
				if ( !doLog )
					return;

				// check if we have a logger, merge domain string with default
				saveAndSet( true, domain );

				// loop over all loggers 
				for ( Logger logger : loggers )
					if ( simpleWildcardFilter( logger, loggerFilter ) )
						logger.line( resDomain, level, msgObject, indent, caller );
	
			} finally { lock.release(); }
		// #endif
	}

    /**************************************************************************************************
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
	public  void line(boolean doLog, String domain, Log.Level level, Object	msgObject, int indent )	{ line( doLog, domain, level, msgObject, indent,null); }

    /**************************************************************************************************
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
	public  void line(boolean doLog, String domain, Log.Level level, Object	msgObject ) 			{ line( doLog, domain, level, msgObject, 0,		null); }
	
    /**************************************************************************************************
     * Logs an Object using the given log level and log domain.
     *
     * @param domain    If this is null, the default domain is used. If this is starting with a swung
     *                  dash ('~') this is interpreted a sub domain to the default domain of the
     *                  source file. For other values, the default domain is ignored (regardless if
     *                  this is starting with a slash or not).
     * @param level     The log level.
     * @param msgObject An Object to be logged.
     **************************************************************************************************/
	public void line(				String domain,	Log.Level level, Object msgObject ) 			{ line( true,  domain,	level, msgObject, 0,		null); 			}

    /**************************************************************************************************
     * Logs an Object using the given log level and the default domain for this scope.
     *
     * @param level     The log level.
     * @param msgObject An Object to be logged.
     **************************************************************************************************/
	public void line(			   					Log.Level level, Object msgObject ) 			{ line( true,  null,	level, msgObject, 0,		null); 			}

    /**************************************************************************************************
     * Logs an Object using the given log level and indentation using the default domain for this scope.
     *
     * @param level     The log level.
     * @param msgObject An Object to be logged.
     * @param indent    The indentation in the output.
     **************************************************************************************************/
	public void line(			   				  	Log.Level level, Object msgObject, int indent ) { line( true,  null,	level, msgObject, indent,	null); 			}

    /**************************************************************************************************
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
	public void line(			   				  	Log.Level level, Object msgObject, int indent, String loggerFilter )	{ line( true, null, level, msgObject, indent, loggerFilter);	}

	//*****************************************************************************
	//***  internals
	//*****************************************************************************
	//#if ALOX_DEBUG || ALOX_REL_LOG

        /**************************************************************************************************
         * This method performs the following things:
         * 
         * a) retrieves the caller info within the singleton field of this class for further reference
         * within this a log operation
         * 
         * b) checks if an instance Logger attached already. If not, a corresponding console logger is
         * created  
         * and added
         * 
         * c) the given domain string is merged with the default domain that optionally is set to the
         * callers source. This is done only if the given domain name is starting with a swung dash("~").
         *
         * @param getResDomain  true to get resulting domain.
         * @param domain        The domain given by the user.
         *
         * ### return   The resulting domain if parameter domain was not null. Null otherwise.
         **************************************************************************************************/
		protected  void saveAndSet( boolean getResDomain, String domain  )
		{
			// a) store caller info
			caller.set( threadDictionary, omittablePackagePrefix ); 

			// b) check if we got any logger
			if ( loggers == null || loggers.size() == 0 )
			{
				addLogger( new ConsoleLogger( "CONSOLE" ) );
				internalLog( Log.Level.Warning,	tempMS.clear().append("Lox: Class 'Log' was used without prior creation of a Log instance. ConsoleLogger Logger created as default.") );
			}

			// c) merge domain name with default domain
			if ( getResDomain )
			{
				// clear resulting domain name buffer
				resDomain.clear();
				
				// get default domain name (if needed later)
				MString	defaultDomain=	null;
				boolean	noDomainGiven=	MString.isNullOrEmpty( domain );
				if ( noDomainGiven || domain.charAt( 0 ) == '~' )
				{
					tempMS.clear().append( caller.packageName );			int strLengthPkgScope=		tempMS.length;
					tempMS.append( '#' ).append( caller.className );		int strLengthClassScope=	tempMS.length;
					tempMS.append( '#' ).append( caller.methodName);
					
					defaultDomain= defaultDomains.get( tempMS );
					if ( MString.isNullOrEmpty( defaultDomain ) )
					{
						tempMS.length= strLengthClassScope;
						tempMS.hash=   0; // clear hash value as we modified the MString

						defaultDomain= defaultDomains.get( tempMS );
						if ( MString.isNullOrEmpty( defaultDomain ) )
						{
							tempMS.length= strLengthPkgScope;
							tempMS.hash=   0; // clear hash value as we modified the MString
							defaultDomain= defaultDomains.get( tempMS );
						}
					}
				}


				// no domain given
				if ( noDomainGiven )
				{
					// Warning: neither domain nor default domain given
					if ( MString.isNullOrEmpty( defaultDomain ) )
					{
						internalLog( Log.Level.Warning, 
									 tempMS.clear() .append("Lox: No log domain given and default domain not set for scope \"") 
													.append(caller.packageName).append('.').append(caller.className).append('.').append(caller.methodName).append('\"')
									);
						return;
					}
					
					// return resulting domain
					resDomain.append( defaultDomain );
					return;
				}

				// domain starts with '~' ?	Relative path
				int start=	0;
				if ( domain.charAt( 0 ) == '~' )
				{
					// cut the ~ character
					start=	1;
					
					// found one? build complete path
					if ( defaultDomain != null )
						resDomain.append( defaultDomain );
					else
					{
						// not set? -> remove the ~ symbol and go ahead
						internalLog( Log.Level.Warning,	 tempMS.clear() .append("Lox: Relative domain path given: \"").append(domain) 
									 									.append("\", but default domain is not set for scope \"") 
									 									.append(caller.packageName).append('.').append(caller.className).append('.').append(caller.methodName).append('\"')	);
					}
				}

				// remove any potential leading separator
				int len=	domain.length();
				while (start < len && ( LogDomain.domainSeparatorChars.indexOf( domain.charAt( start ) ) >= 0 ) )
					start++;
				
				// add domain to the path
				if (start < len )
				{
					if ( resDomain.length > 0 )
						resDomain.append( '/' );
					resDomain.append( domain, start );
				}
			}
		}

        /**************************************************************************************************
         * Logs an internal error message to the domain given by field InternalDomain. Attn: must only
         * be called after saveAndSet() was performed.
         *
         * @param level The logging level.
         * @param msg   The message.
         **************************************************************************************************/
		protected  void internalLog( Log.Level level, MString msg )
		{
			// decrease log counter, as internal Log should not count
			cntLogCalls--;

			// log msg on InternalDomain
			line( true, internalDomain, level, msg , 0, null );

			// reset the caller timestamp to avoid negative time differences in subsequent log call
			caller.timeStamp.setToNow();
		}

        /**************************************************************************************************
         * Compares a loggers name with a filter string with simplest wildcard support ('*') at the
         * beginning or end of the string. If loggerFilter is null, a match is indicated.
         *
         * @param logger        The logger to be filtered.
         * @param loggerFilter  The filter.
         *
         * @return  True if logger is not filtered out.
         **************************************************************************************************/
		private static  boolean simpleWildcardFilter( Logger logger, String loggerFilter )
		{
			final String asterisk = "*";

			// null or empty? -> return TRUE (!)
			if ( MString.isNullOrEmpty( loggerFilter ) )
				return true;

			// wildcard at start?
			boolean startWC= false;
			if ( loggerFilter.startsWith ( asterisk ) )
			{
				loggerFilter=	loggerFilter.substring( 1 );
				startWC=		true;
			}

			// wildcard at end?
			boolean endWC= false;
			if ( loggerFilter.endsWith ( asterisk ) )
			{
				loggerFilter=	loggerFilter.substring( 0, loggerFilter.length() - 1 );
				endWC=		true;
			}

			// wildcard at start?
			if ( startWC )
			{
				// both?
				if ( endWC )
					return MString.indexOfIgnoreCase( logger.name, loggerFilter ) >= 0;

				// at start only
				return  MString.endsWithIgnoreCase( logger.name, loggerFilter );  
			}

			// at end
			if ( endWC)
				return MString.startsWithIgnoreCase( logger.name, loggerFilter ); 

			// no wildcard
			return logger.name.equalsIgnoreCase( loggerFilter );		// 
		}

        /**************************************************************************************************
         * Internal method used by LogConfig() to recursively log LogDomain instances. 
         *
         * @param domain    The LogDomain instance to log out.
         * @param indent    The indentation in the output, recursively increased..
         * @param domPath   Actual path releative to recursion, soley for log output.
         * @param buf       The buffer to log to.
         **************************************************************************************************/
		protected  void logConfigDomainRecursive( LogDomain domain, int indent, String domPath, MString buf)
		{
			// append /ME to domain path string
			domPath= domPath + "/" + domain.name;

			// add  domain name and log level  
			int zeroPos= buf.length;
			buf.append( domPath  )	.tab( 25, zeroPos)	.append( domain.getLevel().toString() )  .newLine();
		
			// loop over all sub domains (recursion)
			for ( LogDomain subDomain : domain.subDomains )
				logConfigDomainRecursive( subDomain, indent + 1, domPath, buf );
		}

	//#endif // ALOX_DEBUG || ALOX_REL_LOG
}
 
 
