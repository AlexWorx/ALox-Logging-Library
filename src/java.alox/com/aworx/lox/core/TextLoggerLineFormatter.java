package com.aworx.lox.core;

import java.text.FieldPosition;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Locale;

import com.aworx.lox.Log;
import com.aworx.util.MString;
import com.aworx.util.Ticker;

/** ***********************************************************************************************
 * This class is a sort of plug-in for the TextLogger class. Its purpose is to assemble the meta
 * information of each log line (things like timestamps, thread information, level and domain, etc.).
 * 
 * To manipulate the meta information log output, three options exist:
 * - by just changing the #format string (at runtime).
 * - by creating a derived class that introduces a new version of method #processVariable() to handle
 *   one or more format variable differently or to introduce new variables.  
 * - by creating a derived class that introduces a new version of method #writeMetaInfo() to 
 *   completely control the meta information output.
 **************************************************************************************************/
public class TextLoggerLineFormatter
{
	// #################################################################################################
	// public fields
	// #################################################################################################
	/**
	 *  The line format specifies the (automated) log output that is prepended to each log line before 
	 *  the log message itself.
	 *  
	 *  The string supports replacement variables that begin with a % sign
	 *  - %CF: The caller's source file name  
	 *  - %CL: The line number in the caller's source file
	 *  - %CM: The caller's method name
	 *  - %D:  Date
	 *  - %TD: Time of day
	 *  - %TE: Time elapsed since the Logger was created or it's timer was reset
	 *  - %TI: Time elapsed since the last log call
	 *  - %t:  Thread information
	 *  - %L:  The log level
	 *  - %O:  Log domain
	 *  - %#:  The log call counter (like a line counter, but counting multi lines as one)
	 *  - %Ax: An auto-adjusted tabulator. This grows whenever it needs, but never shrinks. The  
	 *         mandatory number x (a character between 0 and 9) specifies how much extra
	 *         space is added when tab is adjusted
	 */
	//public 		MString				format	=	new MString( "(%CF) %CP.%CC.%CM():%A3[%DD] [%TD] [%TE +%TI] [%t] %L [%O] <%#>: ");
	public			MString				format	=	new MString( "(%CF) %CM():%A9[%TE +%TI] [%t] %L [%O]: ");

	/**
	 *  A list of values for auto tab positions. For each %A variable in LineFormat, a corresponding
	 *  array field is created on the fly. If the format string get's changed and different (new) auto
	 *  values should be used, then this field should be nulled after setting the new format string.
	 *  The other way round, it is also possible to set minimum values for the tabs and
	 *  hence avoid the columns growing during the lifetime of the Logger. 
	 */
	public			int[]				autoTabs;

	/** The character(s) used for indentation. */ 
	public			String				indentString				= "  ";

	/** The output for the log level "Error". */
	public			String				logLevelError				= "[ERR]";

	/** The output for the log level "Warning". */
	public			String				logLevelWarning				= "[WRN]";

	/** The output for the log level "Info". */
	public			String				logLevelInfo				= "     ";

	/** The output for the log level "Verbose". */
	public			String				logLevelVerbose				= "[***]";

	/** Format string for the output of the log date. 
		For more information about possible, see class java.text.SimpleDateFormat  */
	public			String				dateFormat					= "yyyy-MM-dd";
	
	/** Format string for the output of the time of day.
		For more information about possible, see class java.text.SimpleDateFormat  */
	public			String				timeOfDayFormat				= "HH:mm:ss";
	
	/** The word "Days" the out put of time elapsed (if longer than a day). */
	public			String				timeElapsedDays				= " Days ";

	/** Entity microseconds for time difference outputs below 1000 microseconds. */
	public			String				timeDiffMicros				= " \u00B5s"; //" µs";
	
	/** Entity milliseconds for time difference outputs below 1000 milliseconds. */
	public			String				timeDiffMillis				= " ms";
	
	/** Format for time difference outputs between 10s and 99.9s. */
	public			String				timeDiffSecs				= " s";
	
	/** Format for time difference outputs between 100s and 60 min. */
	public			String				timeDiffMins				= " m";
	
	/** Format for time difference outputs between 1h and 24h. */
	public			String				timeDiffHours				= " h";
	
	/** Format for time difference outputs of more than a day. */
	public			String				timeDiffDays				= " days";

	/** Prefix for the domain. */
	public			int					logNumberMinDigits			= 3;

	/** The maximum length of a thread name logged so far. This 'auto growing' 
	/// field assures to keep output in nice column format.  */
	public			int					autoGrowThreadNameLength	= 0;

	/** The maximum length of a domain name logged so far. This 'auto growing' 
	/// field assures to keep output in nice column format.  */
	public			int					autoGrowDomainNameLength	= 0;
	
	/**  Internal object to retrieve formatted log date. This field has to be set to null, 
	 *   when the field #dateFormat gets modified and log operations have been scheduled 
	 *   since the creation of the logger (respectively since the last change of that format).  */
	public			SimpleDateFormat	dateFormatter;

	/**  Internal object to retrieve formatted time of day. This field has to be set to null, 
	 *   when the field #timeOfDayFormat gets modified and log operations have been scheduled 
	 *   since the creation of the logger (respectively since the last change of that format).  */
	public			SimpleDateFormat	timeOfDayFormatter;


	// #################################################################################################
	// Internal fields
	// #################################################################################################
	/**  Internal calendar object to get string representations of dates. */
	protected		Date	 			callerDateTimeDate			= new Date();
	
	/**  Internal calendar object to get string representations of dates. */
	protected		GregorianCalendar	callerDateTimeCal			= new GregorianCalendar();
	
	/**  Flag to indicate if date instance was set during one doLog() call  */
	protected		boolean				dateInstanceSet;
	
	/**  Flag to indicate if calendar instance was set during one doLog() call  */
	protected		boolean				calInstanceSet;

	/**  Internal object to retrieve formatted time of day  */
	protected		StringBuffer		tempSBuf					= new StringBuffer();
	
	/**  Internal singleton to specify a first field in formatted output */
	protected		FieldPosition		fieldPositionZero			= new FieldPosition( 0 );

	/**  Internal default string to detect default format for optimized format generation */
	protected 		String				defaultfmtDate				= "yyyy-MM-dd";
	
	/**  Internal default string to detect default format for optimized format generation */
	protected 		String				defaultfmtTimeOfDay			= "HH:mm:ss";

	/**  The actual auto tab number detected in the format string.  */
	protected int	autoTabNo;


	/** ***********************************************************************************************
	 * Parses the #format string and logs meta information into the log buffer. 
	 * @param logger	The logger that we are embedded in.	
	 * @param buf       The buffer to write meta information into.
	 * @param domain    The log domain name.
	 * @param level     The log level. This has been checked to be active already on this
	 *                  stage and is provided to be able to be logged out only.
	 * @param indent    The desired indentation of the log call.
	 * @param caller    Once compiler generated and passed forward to here.
	 **************************************************************************************************/
	protected void writeMetaInfo( Logger logger, MString buf, MString domain, Log.Level level, int indent, CallerInfo caller )
	{
		// check
		if ( format == null || format.length == 0 )
			return;
			
		// set date object only once per loop
		calInstanceSet=  false;
		dateInstanceSet= false;

		// loop/switch over content specified in configuration array
		int si= 0;
		int ei= 0;
		int lfLen= format.length;
		char[] lf= format.buffer;
		char c;
		autoTabNo= 0;
		while ( true )
		{
			// search the next %
			while ( ( c= lf[ei] ) != '%' &&  ++ei < lfLen ) {}

			// log substring between commands
			buf.append( format, si, ei - si );

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
			buf.append( indentString );
	}

	/** ***********************************************************************************************
	 * Processes the next command found in the format string, by writing formatted information
	 * into the given buffer. 
	 *
	 * @param logger			The logger that we are embedded in.
	 * @param domain            The log domain name.
	 * @param level             The log level. This has been checked to be active already on this
	 *                          stage and is provided to be able to be logged out only.
	 * @param caller            Once compiler generated and passed forward to here.
	 * @param buf               The buffer to write meta information into.
	 * @param formatString      The format string that is parsed.
	 * @param formatStringIdx   The index of the command in the format string.
	 * 
	 * @return	The index as received but potentially increased by the number of characters read by 
	 * the variable as parameters.
	 **************************************************************************************************/
	protected int processVariable( Logger logger, MString domain, Log.Level level, CallerInfo caller, MString buf, char[] formatString, int formatStringIdx )
	{
		// process commands
		switch ( formatString[formatStringIdx] )
		{
			// caller info
			case 'C':
			{
				// read sub command
				char s= formatString[++formatStringIdx];
				buf.append( 	s == 'F' ?	caller.fileNameAndLineNumber	:
								s == 'P' ?	caller.packageName 				:
								s == 'C' ?	caller.className				:
								s == 'M' ?	caller.methodName 				: new MString("?") );
			}
			break;

			// Date  
			case 'D':	
			{
				// avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!) 
				// and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
				if ( dateFormat.equals( defaultfmtDate ) )
				{
					// set time in calendar object
					caller.timeStamp.toJavaCalendar( callerDateTimeCal );
					calInstanceSet= true;
					
					// append date 'manually'
					buf	.append( callerDateTimeCal.get( Calendar.YEAR  )		, 4 ).append( '-' )
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
					if ( dateFormatter == null )
						dateFormatter= new SimpleDateFormat( dateFormat, Locale.US );
					
					// get date string from system and append to log buffer
					tempSBuf.setLength( 0 );
					dateFormatter.format( callerDateTimeDate, tempSBuf, fieldPositionZero );
					buf.append( tempSBuf );
					
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
					// avoid the allocation of a) a StringBuilder (yes, a string builder is allocated inside StringBuilder.AppendFormat!) 
					// and b) a DateTime object, if the format is the unchanged standard. And it is faster anyhow.
					if ( timeOfDayFormat.equals( defaultfmtTimeOfDay ) )
					{
						// set time in calendar object
						if ( ! calInstanceSet )
							caller.timeStamp.toJavaCalendar( callerDateTimeCal );
						
						buf	.append( callerDateTimeCal.get( Calendar.HOUR_OF_DAY ),	2 ).append( ':' )
								.append( callerDateTimeCal.get( Calendar.MINUTE ),		2 ).append( ':' )
								.append( callerDateTimeCal.get( Calendar.SECOND ),		2 );
					}
		
					// support user defined standards
					else
					{
						// set time in date object
						if ( ! dateInstanceSet )
							caller.timeStamp.toJavaDate( callerDateTimeDate );
						
						if ( timeOfDayFormatter == null )
							timeOfDayFormatter= new SimpleDateFormat( timeOfDayFormat, Locale.US );
						
						tempSBuf.setLength( 0 );
						timeOfDayFormatter.format( callerDateTimeDate, tempSBuf, fieldPositionZero );
					
						buf.append( tempSBuf );
					}
				}

				// %TE: Time Elapsed
				else if ( s == 'E' )
				{
					// create TimeSpan object (on the stack by using new! :)
					long elapsedMillis=		Ticker.toMillis( caller.timeStamp.get() - logger.timeOfCreation.get() );
					long elapsedSecs=		elapsedMillis	/ 1000;
					elapsedMillis=			elapsedMillis   % 1000;
					
					// days?
					int	elapsedDays= 	(int) (elapsedSecs 	/ (60 * 60 * 24 ) );
					if ( elapsedDays > 0 )
					{
						buf	.append( elapsedDays ).append( timeElapsedDays );
						elapsedSecs-= 	((long)elapsedDays) * (60 * 60 * 24);
					}
					
					// hours
					int elapsedHours=	(int) (elapsedSecs 	/ (60 * 60) );  
					if ( elapsedHours > 0 )
					{
						buf	.append( elapsedHours )	.append( ':' );
						elapsedSecs-= 	((long)elapsedHours) * (60 * 60);
					}
		
					// seconds
					int eleapsedMins=  (int) (elapsedSecs / 60);
					elapsedSecs-= 		 (eleapsedMins * 60);
					buf	.append( 		eleapsedMins, 	2).append( ':' )
							.append( (int) 	elapsedSecs, 	2).append( '.' )
							.append( (int)	elapsedMillis, 	3);
				}

				// %TE: Time Diff
				else
					writeTimeDiff( buf, Ticker.toMicros( caller.timeStamp.get() - logger.timeOfLastLog.get() ) );
			}
			break;


			// Thread
			case 't':
			{
				// get name length and store max value
				if ( autoGrowThreadNameLength < caller.threadName.length )
					autoGrowThreadNameLength= caller.threadName.length;
		
				// append thread name
				buf.appendPadCenter( caller.threadName, autoGrowThreadNameLength );
			}
			break;

			case 'L':	buf	.append(	level == Log.Level.ERROR	?	logLevelError 	:  
										level == Log.Level.WARNING	?	logLevelWarning	:
										level == Log.Level.INFO		?	logLevelInfo		:
																		logLevelVerbose		);
					 	
					break;
			case 'O':	
			{
				// save the maximum length of any domain name
				if ( autoGrowDomainNameLength < domain.length() )
					autoGrowDomainNameLength= domain.length();
		
				// log domain 
				buf	.appendPadCenter( domain, autoGrowDomainNameLength );
			}
			break;

			case '#':	buf.append( logger.cntLogs, logNumberMinDigits );
			break;

			// A: Auto tab
			case 'A':
			{
				// make sure, auto tab array is big enough
				if ( autoTabs == null || autoTabs.length == autoTabNo )
				{
					// create a bigger array and copy old values
					int[] newAutoTabs= new int[ autoTabNo + 1];
					for ( int i= 0; i < autoTabNo ; i++ )
						newAutoTabs[i]= autoTabs[i];
					autoTabs= newAutoTabs;
				}

				// read extra space from format string
				int extraSpace= formatString[++formatStringIdx] - '0';

				// increase tab? If yes, add some extra space to avoid too many increases
				if ( autoTabs[ autoTabNo ] <= buf.length )
					autoTabs[ autoTabNo ]= buf.length + ( autoTabs[ autoTabNo ] == 0 ? 1 : extraSpace ); 

				// jump to next tab level
				buf.append( ' ', autoTabs[ autoTabNo ] - buf.length );

				// increase auto tab index for next 'A' command
				autoTabNo++;
			}
			break;

			default:	assert( false );
						break;
		}
		
		// return the new index in format string
		return formatStringIdx;
	}
	
	
	/**********************************************************************************************//**
	 * Helper function that logs a time given difference into the given buffer in a human readable
	 * format. Works from micro seconds to days.
	 *
	 * @param buf			The buffer to write the time difference representation into.	
	 * @param diffMicros	The time difference to write in microseconds.	
	 **************************************************************************************************/
	protected void writeTimeDiff( MString buf, long diffMicros )
	{
		// below 1000 microseconds?
		if ( diffMicros < 1000 )
		{
			buf.append( (int) diffMicros, 3 ).append( timeDiffMicros );
			return;
		}

		// below 1000 ms?
		if ( diffMicros < 1000000 )
		{
			buf.append( (int) (diffMicros / 1000), 3 ).append( timeDiffMillis );
			return;
		}
				
		// below 10 secs (rounded) ? 
		if ( diffMicros < 9995000 )
		{
			// convert to hundredth of secs
			long hundredthSecs=  ((diffMicros / 1000) + 5) / 10;

			// print two digits after dot x.xx 
			buf.append( (int) (hundredthSecs / 100), 1 )
				  .append( '.' )
				  .append( (int) (hundredthSecs % 100), 2 )
				  .append( timeDiffSecs );
				  
			return;
		}

		// convert to tenth of secs
		long tenthSecs=  ((diffMicros / 10000) + 5) / 10 ;

		// below 100 secs ?
		if ( tenthSecs < 1000 )
		{
			// print one digits after dot xx.x (round value by adding 5 hundredth)
			buf.append( (int) ( tenthSecs / 10 ), 2 )
				  .append( '.' )
				  .append( (int) ( tenthSecs % 10 ), 1 )
				  .append( timeDiffSecs );
			return;
		}

		// 	below 10 mins ?
		if ( tenthSecs < 6000 )
		{
			// convert to hundredth of minutes
			long hundredthMins=  tenthSecs / 6;

			// print two digits after dot x.xx 
			buf.append( (int) (hundredthMins / 100), 1 )
				  .append( '.' )
				  .append( (int) (hundredthMins % 100), 2 )
				  .append( timeDiffMins );
					  
			return;
		}

		// convert to tenth of minutes
		long tenthMins=  tenthSecs / 60;
	
		// below 100 mins ?
		if ( tenthMins < 1000 )
		{
			// print one digits after dot xx.x (round value by adding 5 hundredth)
			buf.append( (int) (tenthMins / 10), 2 )
				  .append( '.' )
				  .append( (int) (tenthMins % 10), 1 )
				  .append( timeDiffMins );
			return;
		}
		
		// below ten hours?
		if ( tenthMins < 6000 )
		{
			// convert to hundredth of hours
			long hundredthHours=  tenthMins / 6;

			// print two digits after dot x.xx 
			buf.append( (int) (hundredthHours / 100), 1 )
				  .append( '.' )
				  .append( (int) (hundredthHours % 100), 2 )
				  .append( timeDiffHours );
				  
			return;
		}

		// convert to tenth of minutes
		long tenthHours=  tenthMins / 60;

		// below 10 hours ?
		if ( tenthHours < 1000 )
		{
			// print two digits after dot x.xx 
			buf.append( (int) (tenthHours / 10), 2 )
				  .append( '.' )
				  .append( (int) (tenthHours % 10), 1 )
				  .append( timeDiffHours );
			return;
		}

		// below 100 hours ?
		if ( tenthHours < 1000 )
		{
			// print one digits after dot xx.x (round value by adding 5 hundredth)
			buf.append( (int) (tenthHours / 10), 2 )
				  .append( '.' )
				  .append( (int) ((tenthHours / 10) % 10), 1 )
				  .append( timeDiffHours );
			return;
		}
		
		// convert to hundredth of days
		long hundredthDays=  tenthHours * 10 / 24;

		// below 10 days ?
		if ( hundredthDays < 1000 )
		{
			// print two digits after dot x.xx 
			buf.append( (int) (hundredthDays / 100), 1 )
				  .append( '.' )
				  .append( (int) (hundredthDays % 100), 2 )
				  .append( timeDiffDays );
			return;
		}

		// 10 days or more (print days plus one digit after the comma)
		// print one digits after dot xx.x (round value by adding 5 hundredth)
		buf.append( (int) (hundredthDays / 100), 2 )
			  .append( '.' )
			  .append( (int) ((hundredthDays / 10) % 10), 1 )
			  .append( timeDiffDays );
	}
	
} // class
