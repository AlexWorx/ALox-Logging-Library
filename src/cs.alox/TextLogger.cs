// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:  TextLogger
//  File:	TextLogger.cs												  Namespace:  com.aworx.lox
// #################################################################################################

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using com.aworx.util;
using com.aworx.lox.core;

namespace com.aworx.lox
{

/** ***********************************************************************************************
 * <summary>
 *  This class is a still abstract implementation of class Logger. All message objects passed to 
 *  doLog are translated to MStrings and passed to the abstract function doTextLog().
 *  Furthermore, various textual representations of other log attributes are generated.
 * </summary>
 **************************************************************************************************/
public abstract class TextLogger : Logger
{

	// #################################################################################################
	// Empty method stubs for release version (with no release logging)
	// #################################################################################################
	#if !(ALOX_DEBUG || ALOX_REL_LOG)

		// Empty constructor
		protected TextLogger()	
		{
		}

	#else

	/** <summary> 
	 * A list of pairs of strings. Within each log message, the first string of a pair is 
	 *  searched and replaced by the second string. Very simple, but useful in some cases.
	 * </summary> 
	 */
	public			List<String>	Replacements				= new List<String>();

	/** <summary>	
	 * Determines if multi line messages should be split into different log lines. Possible values are: 
	 * 0: No line split is performed, delimiters can be replaced by readable delimiters (depending on 
	 * setting of #MultiLineDelimiter and # MultiLineDelimiterRepl). 
	 * 
	 * 1: Each log line contains all meta information  
	 * 
	 * 2: Starting with second log line, meta information is replaced by blanks  (default)  
	 *  
	 * 
	 * 3: The headline #FMT_MultiLineMsgHeadline is logged and all lines are logged right after the caller info (no meta information)  
	 * 
	 * 4: The headline #FMT_MultiLineMsgHeadline is logged and all lines get tabbed to zero (no caller info and no meta information)
	 * </summary>*/
	public			int				MultiLineMsgMode			= 2;

	/** <summary>	
	 * This is the string interpreted as line delimiter within log messages. If null, CR, LF or CRLF
	 * are used. Important: Set to empty string, to stop multi line processing of TextLogger
	 * </summary>*/
	public			String			MultiLineDelimiter			= null;

	/** <summary>	
	 * This is the readable (!) separator string, for logging out multi line messages into a 
	 * single line (#MultiLineMsgMode==0).
	 * </summary>*/
	public			String			MultiLineDelimiterRepl		= "\\r";
	


	// #################################################################################################
	#region  __FormatStrings__
	// #################################################################################################

	///---<summary>Logged when parameter msg of dLog() is null.</summary>
	public 			String			FMT_NullObject			="<null>";

	///---<summary>Prefix for the log message.</summary>
	public			String			FMT_MessagePrefix			= ": ";

	/** <summary>The character(s) used for indentation.</summary> */
	public			String			FMT_IndentString			= "  ";

	/// <summary>The output for the log level "Error".</summary>
	public			String			FMT_LogLevelError			= " [ERR]";

	/// <summary>The output for the log level "Warning".</summary>
	public			String			FMT_LogLevelWarning			= " [WRN]";

	/// <summary>The output for the log level "Info".</summary>
	public			String			FMT_LogLevelInfo			= "      ";

	/// <summary>The output for the log level "Verbose".</summary>
	public			String			FMT_LogLevelVerbose			= " [***]";

	/// <summary>Headline for multi line messages (depending on #MultiLineMsgMode)  .</summary>
	public			String			FMT_MultiLineMsgHeadline	= "ALox: Multi line message follows: ";

	/** <summary>
	 *  Prefix for multi line messages. This is also used if multi line messages logging is switched off
	 *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
	 * </summary>*/
	public			String			FMT_MultiLinePrefix			= ">> ";

	/** <summary>
	 *  Postfix for multi line messages. This is also used if multi line messages logging is switched off
	 *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
	 * </summary>*/
	public			String			FMT_MultiLinePostfix		= null;

	/// <summary>Prefix for log date outputs.</summary>
	public			String			FMT_DatePrefix				= "[";
	/// <summary>Format string for the output of the log date. For more information, see 
	///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat()</summary>
	public			String			FMT_Date					= "yyyy-MM-dd";
	/// <summary>Postfix for log date outputs.</summary>
	public			String			FMT_DatePostfix				= "] ";

	/// <summary>Prefix for time of day outputs.</summary>
	public			String			FMT_TimeOfDayPrefix			= "[";
	/// <summary>Format string for the output of the time of day. For more information, see 
	///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat()</summary>
	public			String			FMT_TimeOfDay				= "HH:mm:ss";
	/// <summary>Postfix for time of day outputs.</summary>
	public			String			FMT_TimeOfDayPostfix		= "] ";

	/// <summary>Prefix for time elapsed since logging start (or reset) outputs.</summary>
	public			String			FMT_TimeElapsedPrefix		= "[";
	/// <summary>Postfix for time elapsed since logging start (or reset) outputs.</summary>
	public			String			FMT_TimeElapsedPostfix		= " ";
	/// <summary>The word "Days" the out put of time elapsed (if longer than a day).</summary>
	public			String			FMT_TimeElapsedDays			= " Days ";

	/// <summary>Prefix for time difference outputs.</summary>
	public			String			FMT_TimeDiffPrefix			= " +";
	/// <summary>Postfix for time difference outputs.</summary>
	public			String			FMT_TimeDiffPostfix			= "]";
	/// <summary>Entity microseconds for time difference outputs below 1000 microseconds.</summary>
	public			String			FMT_TimeDiffMicros			= " \u00B5s"; //" µs";
	/// <summary>Entity milliseconds for time difference outputs below 1000 milliseconds.</summary>
	public			String			FMT_TimeDiffMillis			= " ms";
	/// <summary>Format for time difference outputs between 10s and 99.9s.</summary>
	public			String			FMT_TimeDiffSecs			= " s";
	/// <summary>Format for time difference outputs between 100s and 60 min.</summary>
	public			String			FMT_TimeDiffMins			= " m";
	/// <summary>Format for time difference outputs between 1h and 24h.</summary>
	public			String			FMT_TimeDiffHours			= " h";
	/// <summary>Format for time difference outputs of more than a day.</summary>
	public			String			FMT_TimeDiffDays			= " days";

	/// <summary>Prefix for the domain.</summary>
	public			String			FMT_DomainPrefix			= " [";

	/// <summary>Postfix for the domain.</summary>
	public			String			FMT_DomainPostfix			= "]";

	/// <summary>Prefix for the thread name.</summary>
	public			String			FMT_ThreadPrefix			= " [T:";

	/// <summary>Postfix for the domain.</summary>
	public			String			FMT_ThreadPostfix			= "]";
	
	/// <summary>Prefix for the log number.</summary>
	public			String			FMT_LogNumberPrefix			= " ";

	/// <summary>Postfix for the log number.</summary>
	public			String			FMT_LogNumberPostfix		= "";
	
	/// <summary>Prefix for the domain.</summary>
	public			int				FMT_LogNumberMinDigits		= 3;


	/// <summary>The maximum length of a thread name logged so far. This 'auto growing' 
	/// field assures to keep output in nice column format. </summary>
	public			int				FMT_AutoGrowThreadNameLength= 0;

	/// <summary>The maximum length of a domain name logged so far. This 'auto growing' 
	/// field assures to keep output in nice column format. </summary>
	public			int				FMT_AutoGrowDomainNameLength= 0;



	#endregion


	// #################################################################################################
	// Internal fields
	// #################################################################################################
	/// <summary> Buffer to write the msgObject to. </summary>
	protected 		MString			msgBuffer								=new MString( 128 );

	/// <summary> The internal log Buffer.</summary>
	protected		MString			logBuf									= new MString( 256 );

	/// <summary> Internal string builder used for formatting operations.</summary>
	protected		StringBuilder	formatSB								= new StringBuilder( 64 );

	/// <summary> Reference to last date format string to detect changes at runtime.</summary>
	protected		String			detectDateFormatChanges;

	/// <summary> The .Net format string built at runtime to {0:FMT_Date}.</summary>
	protected		String			dateFormatString;

	/// <summary> Reference to last time of day format string to detect changes at runtime.</summary>
	protected		String			detectTimeOfDayFormatChanges;

	/// <summary> The .Net format string built at runtime to {0:FMT_TimeOfDay}.</summary>
	protected		String			timeOfDayFormatString;


	// #################################################################################################
	// Constructor
	// #################################################################################################
	/** ***********************************************************************************************
	 * <summary>	Constructs a logger. </summary>
	 * <param name="name"> The name of the logger. </param>
	 **************************************************************************************************/
	protected TextLogger(String	name )	
		: base ( name )
	{
	}

	// #################################################################################################
	// Abstract methods to be overwritten
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>	The abstract function that logs a message. </summary>
	 * <param name="domain">	The log domain name. If not starting with a slash ('/')
	 * 							this is appended to any default domain name that might have been
	 * 							specified for the source file. </param>
	 * <param name="level"> 	The log level. This has been checked to be active already on this
	 * 							stage and is provided to be able to be logged out only. </param>
	 * <param name="msg">   	The log message. </param>
	 * <param name="indent">	the indentation in the output. Defaults to 0. </param>
	 * <param name="caller">	Once compiler generated and passed forward to here. </param>
	 * <param name="lineNumber">The line number of a multi-line message, starting with 0. For single line
	 * 							messages this is -1. </param>
	 **************************************************************************************************/
	abstract protected void doTextLog( 	MString		domain,		Log.Level	level, 
										MString		msg,		int			indent,
										CallerInfo	caller, 	int			lineNumber);


	// #################################################################################################
	// Abstract inherited method implementations
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary>
	 *  Implementation of Logger.doLog(). Creates all the textual information that is logged in a line 
     *  before the message itself.
	 * </summary>
	 * <param name="domain">	The log domain name. If not starting with a slash ('/')
	 * 							this is appended to any default domain name that might have been
	 * 							specified for the source file. </param>
	 * <param name="level"> 	The log level. This has been checked to be active already on this
	 * 							stage and is provided to be able to be logged out only. </param>
	 * <param name="msgObject"> The log message object (mostly a String or MString). </param>
	 * <param name="indent">	the indentation in the output. Defaults to 0. </param>
	 * <param name="caller">	Once compiler generated and passed forward to here. </param>
	 **************************************************************************************************/
	override protected void doLog(	MString		domain,		Log.Level	level, 
									Object		msgObject,	int			indent,
									CallerInfo	caller								)
	{

		// copy the string into our internal Buffer
		MString msg= 	msgBuffer;
		msg.Clear();
			 if ( msgObject == null )			msg.Append( FMT_NullObject );
		else if ( msgObject is String ) 		msg.Append( (String) 		msgObject );
		else if ( msgObject is MString )		msg= 	   (MString) 		msgObject;		// reassign
		else if ( msgObject is StringBuilder )	msg.Append( (StringBuilder)	msgObject );
		else 									msg.Append( 	msgObject.ToString() );

		// clear Buffer
		logBuf.Clear();

		// Log actual date or time of day?
		if ( LogDate || LogTimeOfDay )
		{
			// create date object 
			DateTime callerDateTime=  caller.TimeStamp.ToDotNetDateTime();

			// log date (default off)
			if ( LogDate )
			{
				logBuf.Append( FMT_DatePrefix );

					// avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!) 
					// and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
					if ( FMT_Date.Equals( "yyyy-MM-dd" ) )
					{
						logBuf	.Append( callerDateTime.Year,  4 ).Append( '-' )
								.Append( callerDateTime.Month, 2 ).Append( '-' )
								.Append( callerDateTime.Day,   2 );
					}

					// support user defined standards
					else
					{
						// detect changes of format string since last log
						if ( detectDateFormatChanges != FMT_Date )
						{
							detectDateFormatChanges= FMT_Date;
							dateFormatString= "{0:" + FMT_Date + "}";
						}

						// get date string from system and append to log buffer
						formatSB.Clear();
						formatSB.AppendFormat( CultureInfo.InvariantCulture, dateFormatString, callerDateTime );
						logBuf.Append( formatSB );
					}

				logBuf.Append( FMT_DatePostfix );
			}

			// log time	of day (default off)
			if ( LogTimeOfDay )
			{
				logBuf.Append( FMT_TimeOfDayPrefix);

					// avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!) 
					// and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
					if ( FMT_TimeOfDay.Equals( "HH:mm:ss" ) )
					{
						logBuf	.Append( callerDateTime.Hour,   2 ).Append( ':' )
								.Append( callerDateTime.Minute, 2 ).Append( ':' )
								.Append( callerDateTime.Second, 2 );
					}

					// support user defined standards
					else
					{
						// detect changes of format string since last log
						if ( detectTimeOfDayFormatChanges != FMT_TimeOfDay )
						{
							detectTimeOfDayFormatChanges= FMT_TimeOfDay;
							timeOfDayFormatString= "{0:" + FMT_TimeOfDay + "}";
						}

						// get time string from system and append to log buffer
						formatSB.Clear();
						formatSB.AppendFormat( CultureInfo.InvariantCulture, timeOfDayFormatString, callerDateTime);
						logBuf	.Append( formatSB );
					}

				logBuf.Append( FMT_TimeOfDayPostfix);
			}


		}

		// log time	elapsed since logging started (or reset)
		if ( LogTimeElapsed )
		{
			// create TimeSpan object (on the stack by using new! :)
			TimeSpan elapsed= new TimeSpan( caller.TimeStamp.Get() - TimeOfCreation.Get() );

			logBuf.Append( FMT_TimeElapsedPrefix );

				if ( elapsed.Days > 0 )
					logBuf	.Append( elapsed.Days ).Append( FMT_TimeElapsedDays );

				if ( elapsed.Hours > 0 )
					logBuf	.Append( elapsed.Hours )	.Append( ':' );

				logBuf	.Append( elapsed.Minutes, 2).Append( ':' )
						.Append( elapsed.Seconds, 2).Append( '.' )
						.Append( elapsed.Milliseconds, 3);

			logBuf.Append( FMT_TimeElapsedPostfix );
		}

		// log time difference to last log
		if ( LogTimeDiff )
		{
			logTimeDiff( Ticker.ToMicros( caller.TimeStamp.Get() - TimeOfLastLog.Get() ) );
		}

		// append thread ID/Name
		#if !ALOX_NO_THREADS
			if ( LogThreadInfo )
			{
				logBuf.Append( FMT_ThreadPrefix );

					// get name length and store max value
					if ( FMT_AutoGrowThreadNameLength < caller.ThreadName.Length )
						FMT_AutoGrowThreadNameLength = caller.ThreadName.Length;

					// append thread name
					logBuf.AppendPadCenter( caller.ThreadName, FMT_AutoGrowThreadNameLength );

				logBuf.Append( FMT_ThreadPostfix );
			}
		#endif

		// append log level
		if ( LogLogLevel )
		{
			logBuf	.Append(	level == Log.Level.Error	? FMT_LogLevelError
							 :  level == Log.Level.Warning	? FMT_LogLevelWarning
							 :  level == Log.Level.Info		? FMT_LogLevelInfo
							 :							  FMT_LogLevelVerbose
							);
		}

		// append log domain 
		if ( LogDomainName )
		{
			// save the maximum length of any domain name
			if ( FMT_AutoGrowDomainNameLength < domain.Length )
				FMT_AutoGrowDomainNameLength= domain.Length;

			// If no domain logged yet and domain name is empty, we omit it 
			if ( FMT_AutoGrowDomainNameLength != 0 || ( domain != null && domain.Length > 0 ) )
			{
				logBuf	.Append( FMT_DomainPrefix )
						.AppendPadCenter( domain, FMT_AutoGrowDomainNameLength )
						.Append( FMT_DomainPostfix );
			}
		}

		// log line number 
		if ( LogLogCounter )
		{
			logBuf	.Append( FMT_LogNumberPrefix )
					.Append( CntLogs, FMT_LogNumberMinDigits )
					.Append( FMT_LogNumberPostfix );
		}

		// append message prefix
		logBuf.Append( FMT_MessagePrefix );

		// add indent spaces
		for (int i= indent; i > 0 ; i--) 
			logBuf.Append( FMT_IndentString );

		// replace strings in message
		for ( int i= 0 ; i < Replacements.Count -1 ; i+= 2 )
			msg.Replace( Replacements[i], Replacements[i + 1] );

		// check for empty messages 
		if ( msg.Length == 0 )
		{
			// log empty msg and quit
			doTextLog( domain, level, logBuf, indent, caller, -1 );
			return;
		}

		// single line output
		if ( MultiLineMsgMode == 0 )
		{
			// replace line separators
			int cntReplacements= 0;
			if ( MultiLineDelimiter != null )
				cntReplacements+= msg.Replace( MultiLineDelimiter,	MultiLineDelimiterRepl );
			else
			{
				cntReplacements+= msg.Replace( "\r\n",					MultiLineDelimiterRepl );
				cntReplacements+= msg.Replace( "\r",					MultiLineDelimiterRepl );
				cntReplacements+= msg.Replace( "\n",					MultiLineDelimiterRepl );
			}

			// append msg to logBuf
			if ( cntReplacements == 0 ) 
				logBuf.Append( msg );
			else
			{
				logBuf.Append( FMT_MultiLinePrefix );
				  logBuf.Append( msg );
				logBuf.Append( FMT_MultiLinePostfix );
			}

			// now do the logging by calling our derived classes' doLog
			doTextLog( domain, level, logBuf, indent, caller, -1 );

			// stop here
			return;
		}

		// multiple line output
		int actStart= 0;
		int lineNo= 0;
		int lbLenBeforeMsgPart= logBuf.Length;

		// loop over lines in msg
		while( actStart < msg.Length )
		{
			// find next end
			int delimLen;
			int actEnd;

			// no delimiter given: search "\r\n", then '\r', then '\n'
			if ( MultiLineDelimiter == null ) 
			{
				delimLen=	2;
				actEnd=		msg.IndexOf ( "\r\n", actStart );
				if (actEnd < 0 )
				{
					delimLen= 1;
					actEnd=	msg.IndexOf ( "\r",   actStart );

					if (actEnd < 0 )
						actEnd=	msg.IndexOf ( "\n",   actStart );
				}
			}
			else
			{
				delimLen= 	MultiLineDelimiter.Length;
				actEnd=		msg.IndexOf( MultiLineDelimiter, actStart );
			}

			// not found a delimiter? - log the rest
			if ( actEnd < 0 )
			{
				// single line? 
				if (lineNo == 0)
				{
					// append msg to logBuf
					logBuf.Append( msg );

					// now do the logging by calling our derived classes' doLog
					doTextLog( domain, level, logBuf, indent, caller, -1 );

					// stop here
					return;
				}

				// store actual end
				actEnd= msg.Length;
			}

			// found a delimiter
			// 
			// in mode 3, 4, when meta info is deleted, we log a separate line first!
			if ( lineNo == 0 && (MultiLineMsgMode == 3 || MultiLineMsgMode == 4) )
			{
				// log headline
				logBuf.Append( FMT_MultiLineMsgHeadline );
				doTextLog( domain, level, logBuf, indent, caller, 0 );

				// remember zero as offset 
				lbLenBeforeMsgPart= 0;
			}

			 
			// blank out meta information? (do this exactly in 2nd line once)
			if ( lineNo == 1 && MultiLineMsgMode == 2)
				for ( int i= 0; i <  lbLenBeforeMsgPart ; i++ )
					logBuf.Buffer[i]= ' ';

			// reset logBuf length to marked position
			logBuf.Length= lbLenBeforeMsgPart;

			// append message
			logBuf.Append( FMT_MultiLinePrefix );
			  logBuf.Append( msg, actStart, actEnd - actStart  );
			logBuf.Append( FMT_MultiLinePostfix );

			// now do the logging by calling our derived classes' doLog
			doTextLog( domain, level, logBuf, indent, MultiLineMsgMode != 4 ? caller : null, lineNo );

			// next
			actStart= actEnd + delimLen;
			lineNo++;
		}

	}

	/** ***********************************************************************************************
	 * <summary> 
	 *   Logs time difference into the log buffer, from micro seconds to days. 
	 *  </summary>
	 * <param name="diffMicros">The difference micros. </param>
	 **************************************************************************************************/
	protected void logTimeDiff( long diffMicros )
	{
		logBuf.Append( FMT_TimeDiffPrefix );

		// below 1000 microseconds?
		if ( diffMicros < 1000 )
			logBuf.Append( (int) diffMicros, 3 ).Append( FMT_TimeDiffMicros );
		else
		{
			// below 1000 ms?
			if ( diffMicros < 1000000 )
				logBuf.Append( (int) (diffMicros / 1000), 3 ).Append( FMT_TimeDiffMillis );
				
				
			// below 10 secs (rounded) ? 
			else if ( diffMicros < 9995000 )
			{
				// convert to hundredth of secs
				long hundredthSecs=  ((diffMicros / 1000) + 5) / 10;

				// print two digits after dot x.xx 
				logBuf.Append( (int) (hundredthSecs / 100), 1 )
					  .Append( '.' )
					  .Append( (int) (hundredthSecs % 100), 2 )
					  .Append( FMT_TimeDiffSecs );
				}

			else
			{ 
				// convert to tenth of secs
				long tenthSecs=  ((diffMicros / 10000) + 5) / 10 ;

				// below 100 secs ?
				if ( tenthSecs < 1000 )
				{
					// print one digits after dot xx.x (round value by adding 5 hundredth)
					logBuf.Append( (int) ( tenthSecs / 10 ), 2 )
						  .Append( '.' )
						  .Append( (int) ( tenthSecs % 10 ), 1 )
						  .Append( FMT_TimeDiffSecs );
				}

				// 	below 10 mins ?
				else if ( tenthSecs < 6000 )
				{
					// convert to hundredth of minutes
					long hundredthMins=  tenthSecs / 6;

					// print two digits after dot x.xx 
					logBuf.Append( (int) (hundredthMins / 100), 1 )
						  .Append( '.' )
						  .Append( (int) (hundredthMins % 100), 2 )
						  .Append( FMT_TimeDiffMins );
							  
				}
				else 
				{
					// convert to tenth of minutes
					long tenthMins=  tenthSecs / 60;
				
					// below 100 mins ?
					if ( tenthMins < 1000 )
					{
						// print one digits after dot xx.x (round value by adding 5 hundredth)
						logBuf.Append( (int) (tenthMins / 10), 2 )
							  .Append( '.' )
							  .Append( (int) (tenthMins % 10), 1 )
							  .Append( FMT_TimeDiffMins );
					}
					
					// below ten hours?
					else if ( tenthMins < 6000 )
					{
						// convert to hundredth of hours
						long hundredthHours=  tenthMins / 6;

						// print two digits after dot x.xx 
						logBuf.Append( (int) (hundredthHours / 100), 1 )
							  .Append( '.' )
							  .Append( (int) (hundredthHours % 100), 2 )
							  .Append( FMT_TimeDiffHours );
							  
					}
					else
					{
						// convert to tenth of minutes
						long tenthHours=  tenthMins / 60;
				
						// below 10 hours ?
						if ( tenthHours < 1000 )
						{
							// print two digits after dot x.xx 
							logBuf.Append( (int) (tenthHours / 10), 2 )
								  .Append( '.' )
								  .Append( (int) (tenthHours % 10), 1 )
								  .Append( FMT_TimeDiffHours );
								  
						}
	
						// below 100 hours ?
						else if ( tenthHours < 1000 )
						{
							// print one digits after dot xx.x (round value by adding 5 hundredth)
							logBuf.Append( (int) (tenthHours / 10), 2 )
								  .Append( '.' )
								  .Append( (int) ((tenthHours / 10) % 10), 1 )
								  .Append( FMT_TimeDiffHours );
						}
						
						else
						{	
							// convert to hundredth of days
							long hundredthDays=  tenthHours * 10 / 24;
	
							// below 10 days ?
							if ( hundredthDays < 1000 )
							{
								// print two digits after dot x.xx 
								logBuf.Append( (int) (hundredthDays / 100), 1 )
									  .Append( '.' )
									  .Append( (int) (hundredthDays % 100), 2 )
									  .Append( FMT_TimeDiffDays );
									  
							}
		
							// 10 days or more (print days plus one digit after the comma)
							else 
							{
								// print one digits after dot xx.x (round value by adding 5 hundredth)
								logBuf.Append( (int) (hundredthDays / 100), 2 )
									  .Append( '.' )
									  .Append( (int) ((hundredthDays / 10) % 10), 1 )
									  .Append( FMT_TimeDiffDays );
							}
						}
					}
				}
			}
		}

		logBuf.Append( FMT_TimeDiffPostfix );
	}



	#endif // ALOX_DEBUG || ALOX_REL_LOG

} // class TextLogger

} // namespace
