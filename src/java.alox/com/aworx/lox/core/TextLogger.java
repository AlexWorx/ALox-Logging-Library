package com.aworx.lox.core;

import java.util.ArrayList;

import com.aworx.lox.Log;
import com.aworx.util.MString;

/**********************************************************************************************//**
 * This class is a still abstract implementation of class Logger which is used as the super class
 * for all textual Logger implementations within ALox, e.g. ConsoleLogger. 
 * 
 * The class uses two helper classes. One to convert the log message object into a string representation
 * and a second to generate the textual representation of the meta information of a log call. 
 * These helpers can be extended and replaced to modify the behavior of TextLogger. 
 * 
 * The final log message is then passed to the abstract method #doTextLog(). Hence, custom Logger classes
 * that inherited from this class instead of directly from class #Logger, need to implement #doTextLog()
 * instead of implementing #doLog()!
 * 
 * Class TextLogger supports multi line log outputs. Such multi line log outputs can be configured to
 * be logged in different ways. See #multiLineMsgMode for more information.
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
	 * A helper object to convert log objects into textual representations. To extend TextLogger, this
	 * object can be replaced by custom implementations. 
	 */
	public			TextLoggerObjectConverter	objectConverter		= new TextLoggerObjectConverter();

	/**
	 * A helper object to format log objects into textual representations. This class incorporates
	 * a format string that defines the meta information in the log output. Furthermore, to extend 
	 * TextLogger, this object can be replaced by custom implementations of it.  
	 */
	public			TextLoggerLineFormatter		lineFormatter		= new TextLoggerLineFormatter();


	/**
	 * A list of pairs of strings. Within each log message, the first string of a pair is 
	 *  searched and replaced by the second string. Very simple, but useful in some cases.
	 */
	public			ArrayList<String>			replacements		= new ArrayList<String>();

	/**
	 * Determines if multi line messages should be split into different log lines. Possible values are: 
	 * 
	 * - 0: No line split is performed. Delimiters can be replaced by readable delimiters (depending on 
	 *   setting of #multiLineDelimiter and #multiLineDelimiterRepl). 
	 * 
	 * - 1: Each log line contains all meta information  
	 * 
	 * - 2: Starting with second log line, meta information is replaced by blanks  (default)  
	 * 
	 * - 3: The headline #fmtMultiLineMsgHeadline is logged and all lines of the multi line text are logged
	 *      at position zero (without further meta information)  
	 * 
	 * - 4: Just the multi line text is logged, starting at column zero (no meta information is logged)
	 */
	public			int							multiLineMsgMode			= 2;

	/**
	 * This is the string interpreted as line delimiter within log messages. If null, CR, LF or CRLF
	 * are used.  Important: Set to empty string, to stop any multi line processing of TextLogger, even the replacements.
	 */
	public			String						multiLineDelimiter			= null;

	/** 
	 * This is the readable (!) separator string, for logging out multi line messages into a 
	 * single line (#multiLineMsgMode==0).
	 */
	public			String						multiLineDelimiterRepl		= "\\r";
	

	/** Headline for multi line messages (depending on #multiLineMsgMode)  . */
	public			String						fmtMultiLineMsgHeadline		= "ALox: Multi line message follows: ";

	/** 
	 *  Prefix for multi line messages. This is also used if multi line messages logging is switched off
	 *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
	 */
	public			String						fmtMultiLinePrefix			= ">> ";

	/**
	 *  Postfix for multi line messages. This is also used if multi line messages logging is switched off
	 *  (MultiLineMsgMode == 0) but replacing of a set MultiLineDelimiter takes place.
	 */
	public			String						fmtMultiLinePostfix			= null;

	
	// #################################################################################################
	// Internal fields
	// #################################################################################################

	/**  The internal log Buffer. */
	protected		MString				logBuf						= new MString( 256 );


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
	 * The abstract function that logs a text message to be implemented by descendants. 
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
										
	/**********************************************************************************************//**
	 * Abstract method to be implemented by descendants. This message is called only when multi-line
	 * messages are logged. It is called with parameter start equal to true before a series of 
	 * doLog() calls of a multi-line message and once after with parameter start equal to false. 
	 *
	 * @param start   	If true, indicates the begin of a multi-line message, the end otherwise. 
	 **************************************************************************************************/
	abstract protected void multiLineOp (boolean start); 
										
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
		// clear Buffer and reset utility members
		logBuf.clear();

		// process log line format 
		lineFormatter.writeMetaInfo( this, logBuf, domain, level, indent, caller );
		
		// convert msg object into a MString representation
		MString msg=  objectConverter.convertObject( msgObject );

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
				cntReplacements+= msg.replaceCount( multiLineDelimiter,	multiLineDelimiterRepl );
			else
			{
				cntReplacements+= msg.replaceCount( "\r\n",					multiLineDelimiterRepl );
				cntReplacements+= msg.replaceCount( "\r",					multiLineDelimiterRepl );
				cntReplacements+= msg.replaceCount( "\n",					multiLineDelimiterRepl );
			}

			// append msg to logBuf
			if ( cntReplacements == 0 ) 
				logBuf.append( msg );
			else
			{
				logBuf.append( fmtMultiLinePrefix );
				  logBuf.append( msg );
				logBuf.append( fmtMultiLinePostfix );
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
			
			// signal start of multi line log
			if ( lineNo == 0 )
				multiLineOp( true );
			 
			// in mode 3, 4, when meta info is deleted, we log a separate line first!
			if ( lineNo == 0 && (multiLineMsgMode == 3 || multiLineMsgMode == 4) )
			{
				// log headline
				if ( multiLineMsgMode == 3 )
				{
					logBuf.append( fmtMultiLineMsgHeadline );
					doTextLog( domain, level, logBuf, indent, caller, 0 );
				}  

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
			logBuf.append( fmtMultiLinePrefix );
			  logBuf.append( msg, actStart, actEnd - actStart  );
			logBuf.append( fmtMultiLinePostfix );
			
			// now do the logging by calling our derived classes' doLog
			doTextLog( domain, level, logBuf, indent, multiLineMsgMode != 4 ? caller : null, lineNo );

			// next
			actStart= actEnd + delimLen;
			lineNo++;
		}
		
		// signal end of multi line log
		if ( lineNo > 0 )
			multiLineOp( false );
	}
	
	//#endif // ALOX_DEBUG || ALOX_REL_LOG

} // class TextLogger
