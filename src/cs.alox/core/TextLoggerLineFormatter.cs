// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:  TextLoggerLineFormatter
//  File:	TextLoggerLineFormatter.cs								  Namespace:  com.aworx.lox.core
// #################################################################################################

#if (ALOX_DEBUG || ALOX_REL_LOG)

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using com.aworx.util;
using com.aworx.lox;
using com.aworx.lox.core;

namespace com.aworx.lox.core {

/** ***********************************************************************************************
 * <summary>
 * This class is a sort of plug-in for the TextLogger class. Its purpose is to assemble the meta
 * information of each log line (things like timestamps, thread information, level and domain, etc.).
 * 
 * To manipulate the meta information log output, three options exist:
 * - by just changing the #Format string (at runtime).
 * - by creating a derived class that introduces a new version of method #processVariable() to handle
 *   one or more format variable differently or to introduce new variables.  
 * - by creating a derived class that introduces a new version of method #WriteMetaInfo() to   
 *   completely control the meta information output.
 * </summary>
 **************************************************************************************************/
public class TextLoggerLineFormatter
{
	/**
	 * <summary>
	 *  The line format specifies the (automated) log output that is prepended to each log line before 
	 *  the log message itself.
	 *  
	 *  The string supports replacement variables that begin with a % sign
	 *  - %CF: The caller's source file name  
	 *  - %CL: The line number in the caller's source file
	 *  - %CM: The caller's method name
	 *  - %D:  The date the log call was invoked
	 *  - %TD: Time of day the log call was invoked
	 *  - %TE: Time elapsed since the Logger was created or it's timer was reset
	 *  - %TI: Time elapsed since the last log call
	 *  - %t:  Thread name and/or ID
	 *  - %L:  The log level
	 *  - %O:  Log domain
	 *  - %#:  The log call counter (like a line counter, but counting multi lines as one)
	 *  - %Ax: An auto-adjusted tabulator. This grows whenever it needs, but never shrinks. The  
	 *         mandatory number x (a character between 0 and 9) specifies how much extra
	 *         space is added when tab is adjusted
	 * </summary>
	 */
	//public MString  Format= new MString( "%CF(%CL):%CM()%A3[%DD] [%TD] [%TE +%TI] [%t] %L [%O] <%#>: ");
	public			MString			Format	= new MString( "%CF(%CL):%CM()%A9[%TE +%TI] [%t] %L [%O]: ");
	

	/**
	 * <summary>
	 *  A list of values for auto tab positions. For each %A variable in LineFormat, a corresponding
	 *  array field is created on the fly. If the format string get's changed and different (new) auto
	 *  values should be used, then this field should be nulled after setting the new format string.
	 *  The other way round, it is also possible to set minimum values for the tabs and
	 *  hence avoid the columns growing during the lifetime of the Logger. 
	 * </summary>
	 **/
	public			int[]			AutoTabs;

	/** <summary>The character(s) used for indentation.</summary> */
	public			String			IndentString				= "  ";

	/// <summary>The output for the log level "Error".</summary>
	public			String			LogLevelError				= "[ERR]";

	/// <summary>The output for the log level "Warning".</summary>
	public			String			LogLevelWarning				= "[WRN]";

	/// <summary>The output for the log level "Info".</summary>
	public			String			LogLevelInfo				= "     ";

	/// <summary>The output for the log level "Verbose".</summary>
	public			String			LogLevelVerbose				= "[***]";

	/// <summary>Format string for the output of the log date. For more information, see 
	///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat()</summary>
	public			String			DateFormat					= "yyyy-MM-dd";

	/// <summary>Format string for the output of the time of day. For more information, see 
	///  "Standard Date and Time Format Strings" in .NET StringBuilder.AppendFormat()</summary>
	public			String			TimeOfDayFormat				= "HH:mm:ss";

	/// <summary>The word "Days" the out put of time elapsed (if longer than a day).</summary>
	public			String			TimeElapsedDays				= " Days ";

	/// <summary>Entity microseconds for time difference outputs below 1000 microseconds.</summary>
	public			String			TimeDiffMicros				= " \u00B5s"; //" µs";

	/// <summary>Entity milliseconds for time difference outputs below 1000 milliseconds.</summary>
	public			String			TimeDiffMillis				= " ms";

	/// <summary>Format for time difference outputs between 10s and 99.9s.</summary>
	public			String			TimeDiffSecs				= " s";

	/// <summary>Format for time difference outputs between 100s and 60 min.</summary>
	public			String			TimeDiffMins				= " m";

	/// <summary>Format for time difference outputs between 1h and 24h.</summary>
	public			String			TimeDiffHours				= " h";

	/// <summary>Format for time difference outputs of more than a day.</summary>
	public			String			TimeDiffDays				= " days";

	/// <summary>Prefix for the domain.</summary>
	public			int				LogNumberMinDigits			= 3;

	/// <summary>The maximum length of a thread name logged so far. This 'auto growing' 
	/// field assures to keep output in nice column format. </summary>
	public			int				AutoGrowThreadNameLength	= 0;

	/// <summary>The maximum length of a domain name logged so far. This 'auto growing' 
	/// field assures to keep output in nice column format. </summary>
	public			int				AutoGrowDomainNameLength	= 0;

	
	// #################################################################################################
	// Internal fields
	// #################################################################################################
	/// <summary> Internal string builder used for formatting operations.</summary>
	protected		StringBuilder	formatSB					= new StringBuilder( 64 );

	/// <summary> Reference to last date format string to detect changes at runtime.</summary>
	protected		String			detectDateFormatChanges;

	/// <summary> The .Net format string built at runtime to {0:FmtDate}.</summary>
	protected		String			dateFormatString;

	/// <summary> Reference to last time of day format string to detect changes at runtime.</summary>
	protected		String			detectTimeOfDayFormatChanges;

	/// <summary> The .Net format string built at runtime to {0:FmtTimeOfDay}.</summary>
	protected		String			timeOfDayFormatString;

	/// <summary> The actual auto tab number detected in the format string.  </summary>
	protected		int				autoTabNo;

	/// <summary> A singleton DateTime object shared between different format variables during one invocation. </summary>
	protected		DateTime?		callerDateTime;



	/** ***********************************************************************************************
	 * <summary> Parses the #Format string and logs meta information into the log buffer.  </summary>
	 * <param name="logger">	The logger that we are embedded in. </param>
	 * <param name="buf">		The buffer to write meta information into. </param>
	 * <param name="domain">	The log domain name. </param>
	 * <param name="level"> 	The log level. This has been checked to be active already on this
	 * 							stage and is provided to be able to be logged out only. </param>
	 * <param name="indent">	The desired indentation of the log call. </param>
	 * <param name="caller">	Once compiler generated and passed forward to here. </param>
	 **************************************************************************************************/
	public virtual void WriteMetaInfo( Logger logger, MString buf, MString domain, Log.Level level, int indent, CallerInfo caller )
	{
		// check
		if ( Format == null || Format.Length == 0 )
			return;
			
		// clear DateTime singleton
		callerDateTime= null ;

		// loop/switch over content specified in configuration array
		int si= 0;
		int ei= 0;
		int lfLen= Format.Length;
		char[] lf= Format.Buffer;
		char c;
		autoTabNo= 0;
		while ( true )
		{
			// search the next %
			while ( ( c= lf[ei] ) != '%' &&  ++ei < lfLen ) {}

			// log substring between commands
			buf.Append( Format, si, ei - si );

			// not found a %? -> quit
			if ( c != '%' )
				break;

			// process the found variable
			ei= processVariable( logger, domain, level, caller, buf, lf, ++ei );
			
			// next
			si= ++ei;
		}
		
		// add indent spaces
		for (int i= indent; i > 0 ; i--) 
			buf.Append( IndentString );
	}

	/** ***********************************************************************************************
	 * <summary> Processes the next command found in the format string, by writing formatted information
	 * into the given buffer. </summary>
	 * <param name="logger">	The logger that we are embedded in. </param>
	 * <param name="domain">	The log domain name. </param>
	 * <param name="level"> 	The log level. This has been checked to be active already on this
	 * 							stage and is provided to be able to be logged out only. </param>
	 * <param name="caller">	Once compiler generated and passed forward to here. </param>
	 * <param name="buf">		The buffer to write meta information into. </param>
	 * <param name="formatString">	The format string that is parsed. </param>
	 * <param name="formatStringIdx">	The index of the command in the format string. </param>
	 * <returns> The index as received but potentially increased by the number of characters read by 
	 * the variable as parameters.</returns>
	 **************************************************************************************************/
	protected virtual int processVariable( Logger logger, MString domain, Log.Level level, CallerInfo caller, MString buf, char[] formatString, int formatStringIdx )
	{
		// process commands
		switch ( formatString[formatStringIdx] )
		{
			// caller info
			case 'C':
			{
				// read sub command
				char s= formatString[++formatStringIdx];

				// add source file
				if ( s == 'F' )
				{
					// can we cut the source file name by a prefix?
					String sfn=		caller.SourceFileName;
					String cspp=	caller.GetConsumableSourcePathPrefix();
					if ( sfn.StartsWith( cspp, StringComparison.OrdinalIgnoreCase ) )
						buf.Append( sfn, cspp.Length, caller.SourceFileName.Length - cspp.Length);
					else
						buf.Append( sfn );
				}

				// add line number or method name
				else if ( s == 'L' )  	buf.Append( caller.LineNumber );
				else if ( s == 'M' )	buf.Append( caller.MethodName );
			}
			break;

			// Date  
			case 'D':	
			{
				// get time stamp as DateTime once
				if ( callerDateTime == null )
					callerDateTime= caller.TimeStamp.ToDotNetDateTime();

				// avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!) 
				// and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
				if ( DateFormat.Equals( "yyyy-MM-dd" ) )
				{
					buf	.Append( callerDateTime.Value.Year,  4 ).Append( '-' )
						.Append( callerDateTime.Value.Month, 2 ).Append( '-' )
						.Append( callerDateTime.Value.Day,   2 );
				}

				// support user defined standards
				else
				{
					// detect changes of format string since last log
					if ( detectDateFormatChanges != DateFormat )
					{
						detectDateFormatChanges= DateFormat;
						dateFormatString= "{0:" + DateFormat + "}";
					}

					// get date string from system and append to log buffer
					formatSB.Clear();
					formatSB.AppendFormat( CultureInfo.InvariantCulture, dateFormatString, callerDateTime );
					buf.Append( formatSB );
				}
			}

						break;
			// %Tx: Time
			case 'T':
			{
				// read sub command
				char s= formatString[++formatStringIdx];

				// %TD: Time of Day
				if ( s == 'D' )	
				{
					// get time stamp as DateTime once
					if ( callerDateTime == null )
						callerDateTime= caller.TimeStamp.ToDotNetDateTime();

					// avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!) 
					// and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
					if ( TimeOfDayFormat.Equals( "HH:mm:ss" ) )
					{
						buf	.Append( callerDateTime.Value.Hour,   2 ).Append( ':' )
							.Append( callerDateTime.Value.Minute, 2 ).Append( ':' )
							.Append( callerDateTime.Value.Second, 2 );
					}

					// support user defined standards
					else
					{
						// detect changes of format string since last log
						if ( detectTimeOfDayFormatChanges != TimeOfDayFormat )
						{
							detectTimeOfDayFormatChanges= TimeOfDayFormat;
							timeOfDayFormatString= "{0:" + TimeOfDayFormat + "}";
						}

						// get time string from system and append to log buffer
						formatSB.Clear();
						formatSB.AppendFormat( CultureInfo.InvariantCulture, timeOfDayFormatString, callerDateTime);
						buf	.Append( formatSB );
					}
				}

				// %TE: Time Elapsed
				else if ( s == 'E' )
				{
					// create TimeSpan object (on the stack by using new! :)
					TimeSpan elapsed= new TimeSpan( caller.TimeStamp.Get() - logger.TimeOfCreation.Get() );

					if ( elapsed.Days > 0 )
						buf	.Append( elapsed.Days ).Append( TimeElapsedDays );

					if ( elapsed.Hours > 0 )
						buf	.Append( elapsed.Hours )	.Append( ':' );

					buf	.Append( elapsed.Minutes, 2).Append( ':' )
						.Append( elapsed.Seconds, 2).Append( '.' )
						.Append( elapsed.Milliseconds, 3);
				}

				// %TE: Time Diff
				else
					writeTimeDiff( buf, Ticker.ToMicros( caller.TimeStamp.Get() - logger.TimeOfLastLog.Get() ) );
			}
			break;


			// Thread
			case 't':
			{
				#if !ALOX_NO_THREADS
					// get name length and store max value
					if ( AutoGrowThreadNameLength < caller.ThreadName.Length )
						AutoGrowThreadNameLength = caller.ThreadName.Length;

					// append thread name
					buf.AppendPadCenter( caller.ThreadName, AutoGrowThreadNameLength );
				#endif
			}
			break;

			case 'L':	buf	.Append(		level == Log.Level.Error	? LogLevelError
										:	level == Log.Level.Warning	? LogLevelWarning
										:	level == Log.Level.Info		? LogLevelInfo
										:								  LogLevelVerbose	);
						break;
			case 'O':	
			{
				// save the maximum length of any domain name
				if ( AutoGrowDomainNameLength < domain.Length )
					AutoGrowDomainNameLength= domain.Length;

				// If no domain logged yet and domain name is empty, we omit it 
				buf.AppendPadCenter( domain, AutoGrowDomainNameLength );
			}
			break;

			case '#':	buf.Append( logger.CntLogs, LogNumberMinDigits );
			break;

			// A: Auto tab
			case 'A':
			{
				// make sure, auto tab array is big enough
				if ( AutoTabs == null || AutoTabs.Length == autoTabNo )
				{
					// create a bigger array and copy old values
					int[] newAutoTabs= new int[ autoTabNo + 1];
					for ( int i= 0; i < autoTabNo ; i++ )
						newAutoTabs[i]= AutoTabs[i];
					AutoTabs= newAutoTabs;
				}

				// read extra space from format string
				int extraSpace= (int) ( formatString[++formatStringIdx] - '0' );

				// increase tab? If yes, add some extra space to avoid too many increases
				if ( AutoTabs[ autoTabNo ] <= buf.Length )
					AutoTabs[ autoTabNo ]= buf.Length + ( AutoTabs[ autoTabNo ] == 0 ? 1 : extraSpace ); 

				// jump to next tab level
				buf.Append( ' ', AutoTabs[ autoTabNo ] - buf.Length );

				// increase auto tab index for next 'A' command
				autoTabNo++;
			}
			break;

			default:	System.Diagnostics.Debug.Assert( false );
						break;
		}
		
		// return the new index in format string
		return formatStringIdx;
	}
	
	
	/** ***********************************************************************************************
	 * <summary>
	 *  Helper function that logs a time given difference into the given buffer in a human readable
	 *  format. Works from micro seconds to days.
	 * </summary>
	 * <param name="buf">			The buffer to write the time difference representation into. </param>
	 * <param name="diffMicros">	The time difference to write in microseconds.	 </param>
	 **************************************************************************************************/
	protected virtual void writeTimeDiff( MString buf, long diffMicros )
	{
		// below 1000 microseconds?
		if ( diffMicros < 1000 )
		{
			buf.Append( (int) diffMicros, 3 ).Append( TimeDiffMicros );
			return;
		}
		// below 1000 ms?
		if ( diffMicros < 1000000 )
		{
			buf.Append( (int) (diffMicros / 1000), 3 ).Append( TimeDiffMillis );
			return;
		}
			
				
		// below 10 secs (rounded) ? 
		if ( diffMicros < 9995000 )
		{
			// convert to hundredth of secs
			long hundredthSecs=  ((diffMicros / 1000) + 5) / 10;

			// print two digits after dot x.xx 
			buf.Append( (int) (hundredthSecs / 100), 1 )
					.Append( '.' )
					.Append( (int) (hundredthSecs % 100), 2 )
					.Append( TimeDiffSecs );
			return;
		}

		// convert to tenth of secs
		long tenthSecs=  ((diffMicros / 10000) + 5) / 10 ;

		// below 100 secs ?
		if ( tenthSecs < 1000 )
		{
			// print one digits after dot xx.x (round value by adding 5 hundredth)
			buf.Append( (int) ( tenthSecs / 10 ), 2 )
					.Append( '.' )
					.Append( (int) ( tenthSecs % 10 ), 1 )
					.Append( TimeDiffSecs );
			return;
		}

		// 	below 10 mins ?
		if ( tenthSecs < 6000 )
		{
			// convert to hundredth of minutes
			long hundredthMins=  tenthSecs / 6;

			// print two digits after dot x.xx 
			buf.Append( (int) (hundredthMins / 100), 1 )
					.Append( '.' )
					.Append( (int) (hundredthMins % 100), 2 )
					.Append( TimeDiffMins );
			return;
		}

		// convert to tenth of minutes
		long tenthMins=  tenthSecs / 60;
				
		// below 100 mins ?
		if ( tenthMins < 1000 )
		{
			// print one digits after dot xx.x (round value by adding 5 hundredth)
			buf.Append( (int) (tenthMins / 10), 2 )
					.Append( '.' )
					.Append( (int) (tenthMins % 10), 1 )
					.Append( TimeDiffMins );
			return;
		}
					
		// below ten hours?
		if ( tenthMins < 6000 )
		{
			// convert to hundredth of hours
			long hundredthHours=  tenthMins / 6;

			// print two digits after dot x.xx 
			buf.Append( (int) (hundredthHours / 100), 1 )
					.Append( '.' )
					.Append( (int) (hundredthHours % 100), 2 )
					.Append( TimeDiffHours );
			return;
		}

		// convert to tenth of minutes
		long tenthHours=  tenthMins / 60;
				
		// below 10 hours ?
		if ( tenthHours < 1000 )
		{
			// print two digits after dot x.xx 
			buf.Append( (int) (tenthHours / 10), 2 )
					.Append( '.' )
					.Append( (int) (tenthHours % 10), 1 )
					.Append( TimeDiffHours );
			return;
		}
	
		// below 100 hours ?
		if ( tenthHours < 1000 )
		{
			// print one digits after dot xx.x (round value by adding 5 hundredth)
			buf.Append( (int) (tenthHours / 10), 2 )
					.Append( '.' )
					.Append( (int) ((tenthHours / 10) % 10), 1 )
					.Append( TimeDiffHours );
			return;
		}

		// convert to hundredth of days
		long hundredthDays=  tenthHours * 10 / 24;
	
		// below 10 days ?
		if ( hundredthDays < 1000 )
		{
			// print two digits after dot x.xx 
			buf.Append( (int) (hundredthDays / 100), 1 )
					.Append( '.' )
					.Append( (int) (hundredthDays % 100), 2 )
					.Append( TimeDiffDays );
			return;
		}
		
		// 10 days or more (print days plus one digit after the comma)
		// print one digits after dot xx.x (round value by adding 5 hundredth)
		buf .Append( (int) (hundredthDays / 100), 2 )
			.Append( '.' )
			.Append( (int) ((hundredthDays / 10) % 10), 1 )
			.Append( TimeDiffDays );
	}
	
} // class
} // namespace

#endif