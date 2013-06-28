package com.aworx.lox.core;

import java.text.FieldPosition;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;

import com.aworx.lox.Log;
import com.aworx.lox.Log.Level;
import com.aworx.util.MString;
import com.aworx.util.Ticker;

/**********************************************************************************************//**
 * This class is a still abstract implementation of class Logger. All message objects passed to
 * doLog are translated to MStrings and passed to the abstract function doTextLog().
 * Furthermore, various textual representations of other log attributes are generated.
 **************************************************************************************************/
public abstract class TextLogger extends Logger
{
	// #################################################################################################
	// Empty method stubs for release version (with no release logging)
	// #################################################################################################
	//#if !(ALOX_DEBUG || ALOX_REL_LOG)
//		// Empty constructor
//		protected TextLogger()	
//		{
//		}
//
	//#else

	/**
	 * A list of pairs of strings. Within each log message, the first string of a pair is 
	 *  searched and replaced by the second string. Very simple, but useful in some cases.
	 */
	public			ArrayList<String>	replacements				= new ArrayList<String>();

	/**
	 * Determines if multi line messages should be split into different log lines. Possible values are: 
	 * 0: No line split is performed, delimiters can be replaced by readable delimiters (depending on 
	 * setting of #multiLineDelimiter and #multiLineDelimiterRepl). 
	 * 
	 * 1: Each log line contains all meta information  
	 * 
	 * 2: Starting with second log line, meta information is replaced by blanks  (default)  
	 *  
	 * 
	 * 3: The headline #FMT_MultiLineMsgHeadline is logged and all lines are logged right after the caller info (no meta information)  
	 * 
	 * 4: The headline #FMT_MultiLineMsgHeadline is logged and all lines get tabbed to zero (no caller info and no meta information)
	 */
	public			int				multiLineMsgMode			= 2;

	/**
	 * This is the string interpreted as line delimiter within log messages. If null, CR, LF or CRLF
	 * are used. Important: Set to empty string, to stop multi line processing of TextLogger
	 */
	public			String			multiLineDelimiter			= null;

	/** 
	 * This is the readable (!) separator string, for logging out multi line messages into a 
	 * single line (#multiLineMsgMode==0).
	 */
	public			String			multiLineDelimiterRepl		= "\\r";
	


	// #################################################################################################
	// __FormatStrings__
	// #################################################################################################

	/** Logged when parameter msg of dLog() is null. */
	public 			String			FMT_NullObject			="<null>";

	/** Prefix for the log message. */
	public			String			FMT_MessagePrefix			= ": ";

	/** <summary>The character(s) used for indentation. */ 
	public			String			FMT_IndentString			= "  ";

	/** The output for the log level "Error". */
	public			String			FMT_LogLevelError			= " [ERR]";

	/** The output for the log level "Warning". */
	public			String			FMT_LogLevelWarning			= " [WRN]";

	/** The output for the log level "Info". */
	public			String			FMT_LogLevelInfo			= "      ";

	/** The output for the log level "Verbose". */
	public			String			FMT_LogLevelVerbose			= " [***]";

	/** Headline for multi line messages (depending on #multiLineMsgMode)  . */
	public			String			FMT_MultiLineMsgHeadline	= "ALox: Multi line message follows: ";

	/** 
	 *  Prefix for multi line messages. This is also used if multi line messages logging is switched off
	 *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
	 */
	public			String			FMT_MultiLinePrefix			= ">> ";

	/**
	 *  Postfix for multi line messages. This is also used if multi line messages logging is switched off
	 *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
	 */
	public			String			FMT_MultiLinePostfix		= null;

	/** Prefix for log date outputs. */
	public			String			FMT_DatePrefix				= "[";
	/** Format string for the output of the log date. For more information, see 
	///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat() */
	public			String			FMT_Date					= "yyyy-MM-dd";
	/** Postfix for log date outputs. */
	public			String			FMT_DatePostfix				= "] ";

	/** Prefix for time of day outputs. */
	public			String			FMT_TimeOfDayPrefix			= "[";
	/** Format string for the output of the time of day. For more information, see 
	///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat() */
	public			String			FMT_TimeOfDay				= "HH:mm:ss";
	/** Postfix for time of day outputs. */
	public			String			FMT_TimeOfDayPostfix		= "] ";


	/** Prefix for time elapsed since logging start (or reset) outputs. */
	public			String			FMT_TimeElapsedPrefix		= "[";
	/** Postfix for time elapsed since logging start (or reset) outputs. */
	public			String			FMT_TimeElapsedPostfix		= " ";
	/** The word "Days" the out put of time elapsed (if longer than a day). */
	public			String			FMT_TimeElapsedDays			= " Days ";

	/** Prefix for time difference outputs. */
	public			String			FMT_TimeDiffPrefix			= " +";
	/** Postfix for time difference outputs. */
	public			String			FMT_TimeDiffPostfix			= "]";
	/** Entity microseconds for time difference outputs below 1000 microseconds. */
	public			String			FMT_TimeDiffMicros			= " \u00B5s"; //" µs";
	/** Entity milliseconds for time difference outputs below 1000 milliseconds. */
	public			String			FMT_TimeDiffMillis			= " ms";
	/** Format for time difference outputs between 10s and 99.9s. */
	public			String			FMT_TimeDiffSecs			= " s";
	/** Format for time difference outputs between 100s and 60 min. */
	public			String			FMT_TimeDiffMins			= " m";
	/** Format for time difference outputs between 1h and 24h. */
	public			String			FMT_TimeDiffHours			= " h";
	/** Format for time difference outputs of more than a day. */
	public			String			FMT_TimeDiffDays			= " days";

	/** Prefix for the domain. */
	public			String			FMT_DomainPrefix			= " [";

	/** Postfix for the domain. */
	public			String			FMT_DomainPostfix			= "]";

	/** Prefix for the thread name. */
	public			String			FMT_ThreadPrefix			= " [T:";

	/** Postfix for the domain. */
	public			String			FMT_ThreadPostfix			= "]";
	
	/** Prefix for the log number. */
	public			String			FMT_LogNumberPrefix			= " ";

	/** Postfix for the log number. */
	public			String			FMT_LogNumberPostfix		= "";
	
	/** Prefix for the domain. */
	public			int				FMT_LogNumberMinDigits		= 3;


	/** The maximum length of a thread name logged so far. This 'auto growing' 
	/// field assures to keep output in nice column format.  */
	public			int				FMT_AutoGrowThreadNameLength= 0;

	/** The maximum length of a domain name logged so far. This 'auto growing' 
	/// field assures to keep output in nice column format.  */
	public			int				FMT_AutoGrowDomainNameLength= 0;


	// #################################################################################################
	// Internal fields
	// #################################################################################################

	/**  Buffer to write the msgObject to.  */
	protected 		MString				msgBuffer					= new MString( 128 );

	/**  The internal log Buffer. */
	protected		MString				logBuf						= new MString( 256 );

	/**  Internal calendar object to get string representations of dates. */
	protected		Date	 			callerDateTimeDate			= new Date();
	
	/**  Internal calendar object to get string representations of dates. */
	protected		GregorianCalendar	callerDateTimeCal			= new GregorianCalendar();
	
	/**  Internal object to retrieve formatted time of day  */
	protected		StringBuffer		tempSBuf					= new StringBuffer();
	
	/**  Internal object to retrieve formatted log date */
	protected		SimpleDateFormat	dateFormat;

	/**  Internal object to retrieve formatted time of day  */
	protected		SimpleDateFormat	timeOfDayFormat;

	/**  Internal singleton to specify a first field in formatted output */
	protected		FieldPosition		fieldPositionZero			= new FieldPosition( 0 );

	/**  Internal default string to detect default format for optimized format generation */
	protected 		String				defaultFMT_Date				= "yyyy-MM-dd";
	
	/**  Internal default string to detect default format for optimized format generation */
	protected 		String				defaultFMT_TimeOfDay		= "HH:mm:ss";

	// #################################################################################################
	// Constructor
	// #################################################################################################

	/**********************************************************************************************//**
	 * Constructs a TextLogger.
	 *
	 * @param name  The name of the logger.
	 **************************************************************************************************/
	protected TextLogger( String	name )	
	{
		super( name );
	}

	// #################################################################################################
	// Abstract methods to be overwritten
	// #################################################################################################

	/**********************************************************************************************//**
	 * The abstract function that logs a message.
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
	abstract protected void doTextLog( 	MString		domain,		Log.Level	level, 
										MString		msg,		int			indent,
										CallerInfo	caller, 	int			lineNumber);
										
	// #################################################################################################
	// Abstract inherited method implementations
	// #################################################################################################

	/**********************************************************************************************//**
	 * Implementation of Logger.doLog(). Creates all the textual information that is logged in a
	 * line before the message itself.
	 *
	 * @param domain    The log domain name. If not starting with a slash ('/')
	 *                  this is appended to any default domain name that might have been specified
	 *                  for the source file.
	 * @param level     The log level. This has been checked to be active already on this stage and
	 *                  is provided to be able to be logged out only.
	 * @param msgObject The log message. If this is not a String (StringBuilder, MString, etc.)
	 *                  type, then is converted to a text using 'toString()'.
	 * @param indent    the indentation in the output. Defaults to 0.
	 * @param caller    Once compiler generated and passed forward to here.
	 **************************************************************************************************/
	@Override protected void doLog(	MString		domain,		Log.Level	level, 
									Object		msgObject,	int			indent,
									CallerInfo	caller )
	{
		// copy the string into our internal Buffer
		MString msg= 	msgBuffer;
		msg.clear();

			 if ( msgObject == null )					msg.append( FMT_NullObject );
		else if ( msgObject instanceof String ) 		msg.append( (String) 		msgObject );
		else if ( msgObject instanceof MString )		msg= 	   (MString) 		msgObject;			// reassign
		else if ( msgObject instanceof StringBuilder )	msg.append( (StringBuilder)	msgObject );
		else if ( msgObject instanceof StringBuffer )	msg.append( (StringBuffer)	msgObject );
		else if ( msgObject instanceof CharSequence )	msg.append( (CharSequence)	msgObject );
		else 											msg.append( msgObject.toString());

		// clear Buffer
		logBuf.clear();

		// Log actual date or time of day?
		if ( logDate || logTimeOfDay )
		{
			boolean calInstanceSet=  false;
			boolean dateInstanceSet= false;
			
			// log date (default off)
			if ( logDate )
			{
			
				logBuf.append( FMT_DatePrefix );

					// avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!) 
					// and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
					if ( FMT_Date.equals( defaultFMT_Date ) )
					{
						// set time in calendar object
						caller.timeStamp.toJavaCalendar( callerDateTimeCal );
						calInstanceSet= true;
						
						// append date 'manually'
						logBuf	.append( callerDateTimeCal.get( Calendar.YEAR  )		, 4 ).append( '-' )
								.append( callerDateTimeCal.get( Calendar.MONTH )		, 2 ).append( '-' )
								.append( callerDateTimeCal.get( Calendar.DAY_OF_MONTH ) , 2 );
					}

					// support user defined standards
					else
					{
						// set time in date object
						caller.timeStamp.toJavaDate( callerDateTimeDate );
						dateInstanceSet= true;
						
						// create date formatter once
						if ( dateFormat == null )
							dateFormat= new SimpleDateFormat( FMT_Date, Locale.US );
						
						// get date string from system and append to log buffer
						tempSBuf.setLength( 0 );
						dateFormat.format( callerDateTimeDate, tempSBuf, fieldPositionZero );
						logBuf.append( tempSBuf );
						
					}

				logBuf.append( FMT_DatePostfix );
			}

			// log time	of day (default off)
			if ( logTimeOfDay )
			{
				logBuf.append( FMT_TimeOfDayPrefix);

					// avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!) 
					// and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
					if ( FMT_TimeOfDay.equals( defaultFMT_TimeOfDay ) )
					{
						// set time in calendar object
						if ( ! calInstanceSet )
							caller.timeStamp.toJavaCalendar( callerDateTimeCal );
						
						logBuf	.append( callerDateTimeCal.get( Calendar.HOUR_OF_DAY ),	2 ).append( ':' )
								.append( callerDateTimeCal.get( Calendar.MINUTE ),		2 ).append( ':' )
								.append( callerDateTimeCal.get( Calendar.SECOND ),		2 );
					}

					// support user defined standards
					else
					{
						// set time in date object
						if ( ! dateInstanceSet )
							caller.timeStamp.toJavaDate( callerDateTimeDate );
						
						if ( timeOfDayFormat == null )
							timeOfDayFormat= new SimpleDateFormat( FMT_TimeOfDay, Locale.US );
						
						tempSBuf.setLength( 0 );
						timeOfDayFormat.format( callerDateTimeDate, tempSBuf, fieldPositionZero );
					
						logBuf.append( tempSBuf );
					}

				logBuf.append( FMT_TimeOfDayPostfix);
			}
		}
		
		// log time	elapsed since logging started (or reset)
		if ( logTimeElapsed )
		{
			// create TimeSpan object (on the stack by using new! :)
			long elapsedMillis=		Ticker.toMillis( caller.timeStamp.get() - timeOfCreation.get() );
			long elapsedSecs=		elapsedMillis	/ 1000;
			elapsedMillis=			elapsedMillis   % 1000;
			
			
			logBuf.append( FMT_TimeElapsedPrefix );
			
				// days?
				int	elapsedDays= 	(int) (elapsedSecs 	/ (60 * 60 * 24 ) );
				if ( elapsedDays > 0 )
				{
					logBuf	.append( elapsedDays ).append( FMT_TimeElapsedDays );
					elapsedSecs-= 	((long)elapsedDays) * (60 * 60 * 24);
				}
				
				// hours
				int elapsedHours=	(int) (elapsedSecs 	/ (60 * 60) );  
				if ( elapsedHours > 0 )
				{
					logBuf	.append( elapsedHours )	.append( ':' );
					elapsedSecs-= 	((long)elapsedHours) * (60 * 60);
				}
	
				// seconds
				int eleapsedMins=  (int) (elapsedSecs / 60);
				elapsedSecs-= 		 (eleapsedMins * 60);
				logBuf	.append( 		eleapsedMins, 	2).append( ':' )
						.append( (int) 	elapsedSecs, 	2).append( '.' )
						.append( (int)	elapsedMillis, 	3);

			logBuf.append( FMT_TimeElapsedPostfix );

		}

		// log time difference to last log
		if ( logTimeDiff )
		{
			logTimeDiff( Ticker.toMicros( caller.timeStamp.get() - timeOfLastLog.get() ) );
		}

		// append thread ID/Name
		//#if !ALOX_NO_THREADS
			if ( logThreadInfo )
			{
				logBuf.append( FMT_ThreadPrefix );

					// get name length and store max value
					if ( FMT_AutoGrowThreadNameLength < caller.threadName.length )
						FMT_AutoGrowThreadNameLength = caller.threadName.length;

					// append thread name
					logBuf.appendPadCenter( caller.threadName, FMT_AutoGrowThreadNameLength );

				logBuf.append( FMT_ThreadPostfix );
			}
		//#endif

		// append log level
		if ( logLogLevel )
		{
			logBuf	.append(	level == Log.Level.Error	? FMT_LogLevelError
							 :  level == Log.Level.Warning	? FMT_LogLevelWarning
							 :  level == Log.Level.Info		? FMT_LogLevelInfo
							 :							  FMT_LogLevelVerbose
							);
		}

		// append log domain 
		if ( logDomainName )
		{

			// save the maximum length of any domain name
			if ( FMT_AutoGrowDomainNameLength < domain.length() )
				FMT_AutoGrowDomainNameLength= domain.length();


			// If no domain logged yet and domain name is empty, we omit it 
			if ( FMT_AutoGrowDomainNameLength != 0 || ! MString.isNullOrEmpty( domain ) )
			{
				logBuf	.append( FMT_DomainPrefix )
						.appendPadCenter( domain, FMT_AutoGrowDomainNameLength )
						.append( FMT_DomainPostfix );
			}
		}

		// log line number 
		if ( logLogCounter )
		{
			logBuf	.append( FMT_LogNumberPrefix )
					.append( cntLogs, FMT_LogNumberMinDigits )
					.append( FMT_LogNumberPostfix );
		}

		// append message prefix
		logBuf.append( FMT_MessagePrefix );

		// add indent spaces
		for (int i= indent; i > 0 ; i--) 
			logBuf.append( FMT_IndentString );

		// replace strings in message
		for ( int i= 0 ; i < replacements.size() -1 ; i+= 2 )
			msg.replace( replacements.get( i ), replacements.get( i + 1 ) );

		// check for empty messages 
		if ( msg.length == 0 )
		{
			// log empty msg and quit
			doTextLog( domain, level, logBuf, indent, caller, -1 );
			return;
		}

		// single line output
		if ( multiLineMsgMode == 0 )
		{
			// replace line separators
			int cntReplacements= 0;
			if ( multiLineDelimiter != null )
				cntReplacements+= msg.replace( multiLineDelimiter,	multiLineDelimiterRepl );
			else
			{
				cntReplacements+= msg.replace( "\r\n",					multiLineDelimiterRepl );
				cntReplacements+= msg.replace( "\r",					multiLineDelimiterRepl );
				cntReplacements+= msg.replace( "\n",					multiLineDelimiterRepl );
			}

			// append msg to logBuf
			if ( cntReplacements == 0 ) 
				logBuf.append( msg );
			else
			{
				logBuf.append( FMT_MultiLinePrefix );
				  logBuf.append( msg );
				logBuf.append( FMT_MultiLinePostfix );
			}

			// now do the logging by calling our derived classes' doLog
			doTextLog( domain, level, logBuf, indent, caller, -1 );

			// stop here
			return;
		}

		// multiple line output
		int actStart= 0;
		int lineNo= 0;
		int lbLenBeforeMsgPart= logBuf.length;

		// loop over lines in msg
		while( actStart < msg.length )
		{
			// find next end
			int delimLen;
			int actEnd;

			// no delimiter given: search "\r\n", then '\r', then '\n'
			if ( multiLineDelimiter == null ) 
			{
				delimLen=	2;
				actEnd=		msg.indexOf ( "\r\n", actStart );
				if (actEnd < 0 )
				{
					delimLen= 1;
					actEnd=	msg.indexOf ( "\r",   actStart );

					if (actEnd < 0 )
						actEnd=	msg.indexOf ( "\n",   actStart );
				}
			}
			else
			{
				delimLen= 	multiLineDelimiter.length();
				actEnd=		msg.indexOf( multiLineDelimiter, actStart );
			}

			// not found a delimiter? - log the rest
			if ( actEnd < 0 )
			{
				// single line? 
				if (lineNo == 0)
				{
					// append msg to logBuf
					logBuf.append( msg );

					// now do the logging by calling our derived classes' doLog
					doTextLog( domain, level, logBuf, indent, caller, -1 );

					// stop here
					return;
				}

				// store actual end
				actEnd= msg.length;
			}

			// found a delimiter
			// 
			// in mode 3, 4, when meta info is deleted, we log a separate line first!
			if ( lineNo == 0 && (multiLineMsgMode == 3 || multiLineMsgMode == 4) )
			{
				// log headline
				logBuf.append( FMT_MultiLineMsgHeadline );
				doTextLog( domain, level, logBuf, indent, caller, 0 );  

				// remember zero as offset 
				lbLenBeforeMsgPart= 0;
			}

			 
			// blank out meta information? (do this exactly in 2nd line once)
			if ( lineNo == 1 && multiLineMsgMode == 2)
				for ( int i= 0; i <  lbLenBeforeMsgPart ; i++ )
					logBuf.buffer[i]= ' ';

			// reset logBuf length to marked position
			logBuf.length= lbLenBeforeMsgPart;

			// append message
			logBuf.append( FMT_MultiLinePrefix );
			  logBuf.append( msg, actStart, actEnd - actStart  );
			logBuf.append( FMT_MultiLinePostfix );
			
			// now do the logging by calling our derived classes' doLog
			doTextLog( domain, level, logBuf, indent, multiLineMsgMode != 4 ? caller : null, lineNo );

			// next
			actStart= actEnd + delimLen;
			lineNo++;
		}

	}

	/**********************************************************************************************//**
	 * Logs time difference into the log buffer, from micro seconds to days.
	 *
	 * @param diffMicros    The difference micros.
	 **************************************************************************************************/
	protected void logTimeDiff( long diffMicros )
	{
		logBuf.append( FMT_TimeDiffPrefix );

		// below 1000 microseconds?
		if ( diffMicros < 1000 )
			logBuf.append( (int) diffMicros, 3 ).append( FMT_TimeDiffMicros );
		else
		{
			// below 1000 ms?
			if ( diffMicros < 1000000 )
				logBuf.append( (int) (diffMicros / 1000), 3 ).append( FMT_TimeDiffMillis );
				
				
			// below 10 secs (rounded) ? 
			else if ( diffMicros < 9995000 )
			{
				// convert to hundredth of secs
				long hundredthSecs=  ((diffMicros / 1000) + 5) / 10;

				// print two digits after dot x.xx 
				logBuf.append( (int) (hundredthSecs / 100), 1 )
					  .append( '.' )
					  .append( (int) (hundredthSecs % 100), 2 )
					  .append( FMT_TimeDiffSecs );
				}

			else
			{ 
				// convert to tenth of secs
				long tenthSecs=  ((diffMicros / 10000) + 5) / 10 ;

				// below 100 secs ?
				if ( tenthSecs < 1000 )
				{
					// print one digits after dot xx.x (round value by adding 5 hundredth)
					logBuf.append( (int) ( tenthSecs / 10 ), 2 )
						  .append( '.' )
						  .append( (int) ( tenthSecs % 10 ), 1 )
						  .append( FMT_TimeDiffSecs );
				}

				// 	below 10 mins ?
				else if ( tenthSecs < 6000 )
				{
					// convert to hundredth of minutes
					long hundredthMins=  tenthSecs / 6;

					// print two digits after dot x.xx 
					logBuf.append( (int) (hundredthMins / 100), 1 )
						  .append( '.' )
						  .append( (int) (hundredthMins % 100), 2 )
						  .append( FMT_TimeDiffMins );
							  
				}
				else 
				{
					// convert to tenth of minutes
					long tenthMins=  tenthSecs / 60;
				
					// below 100 mins ?
					if ( tenthMins < 1000 )
					{
						// print one digits after dot xx.x (round value by adding 5 hundredth)
						logBuf.append( (int) (tenthMins / 10), 2 )
							  .append( '.' )
							  .append( (int) (tenthMins % 10), 1 )
							  .append( FMT_TimeDiffMins );
					}
					
					// below ten hours?
					else if ( tenthMins < 6000 )
					{
						// convert to hundredth of hours
						long hundredthHours=  tenthMins / 6;

						// print two digits after dot x.xx 
						logBuf.append( (int) (hundredthHours / 100), 1 )
							  .append( '.' )
							  .append( (int) (hundredthHours % 100), 2 )
							  .append( FMT_TimeDiffHours );
							  
					}
					else
					{
						// convert to tenth of minutes
						long tenthHours=  tenthMins / 60;
				
						// below 10 hours ?
						if ( tenthHours < 1000 )
						{
							// print two digits after dot x.xx 
							logBuf.append( (int) (tenthHours / 10), 2 )
								  .append( '.' )
								  .append( (int) (tenthHours % 10), 1 )
								  .append( FMT_TimeDiffHours );
								  
						}
	
						// below 100 hours ?
						else if ( tenthHours < 1000 )
						{
							// print one digits after dot xx.x (round value by adding 5 hundredth)
							logBuf.append( (int) (tenthHours / 10), 2 )
								  .append( '.' )
								  .append( (int) ((tenthHours / 10) % 10), 1 )
								  .append( FMT_TimeDiffHours );
						}
						
						else
						{	
							// convert to hundredth of days
							long hundredthDays=  tenthHours * 10 / 24;
	
							// below 10 days ?
							if ( hundredthDays < 1000 )
							{
								// print two digits after dot x.xx 
								logBuf.append( (int) (hundredthDays / 100), 1 )
									  .append( '.' )
									  .append( (int) (hundredthDays % 100), 2 )
									  .append( FMT_TimeDiffDays );
									  
							}
		
							// 10 days or more (print days plus one digit after the comma)
							else 
							{
								// print one digits after dot xx.x (round value by adding 5 hundredth)
								logBuf.append( (int) (hundredthDays / 100), 2 )
									  .append( '.' )
									  .append( (int) ((hundredthDays / 10) % 10), 1 )
									  .append( FMT_TimeDiffDays );
							}
						}
					}
				}
			}
		}

		logBuf.append( FMT_TimeDiffPostfix );
	}
	
	//#endif // ALOX_DEBUG || ALOX_REL_LOG

} // class TextLogger
