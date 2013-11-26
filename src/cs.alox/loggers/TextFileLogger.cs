// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:	TextFileLogger
//  File:	TextFileLogger.cs									  Namespace:  com.aworx.lox.loggers
// #################################################################################################
using System;
using System.IO;
using System.Runtime.CompilerServices;


using com.aworx.util;
using com.aworx.lox.core;
using com.aworx.lox.tools;
namespace com.aworx.lox.loggers	{
								  
/** ***********************************************************************************************
 * <summary>
 * This is a very simple file logger for textual log outputs. The file name string provided 
 * in the constructor is not verified. If write operations fail, this logger disables
 * itself by setting the inherited flag isDisabled to true.  
 * The fileName may be changed by simply setting the pubic member #fileName and the flag  
 * isDisabled may be set to false by the user without the need of any other interaction. 
 * </summary>
 **************************************************************************************************/
public class TextFileLogger : TextLogger
{
	// #################################################################################################
	// Empty method stubs for release version (with no release logging)
	// #################################################################################################
	#if !(ALOX_DEBUG || ALOX_REL_LOG)
		public TextFileLogger( String fileName, String	loggerName= "TEXTFILE"  )	{}
		public		String			fileName;
	#else

	/** The path and fileName to the log file. */
	public			String					fileName;
	
	/** Used to write into a log file. */
	protected		StreamWriter			sw;
	
	/** Flag to prevent file open/close operations when multi line text logging is performed. */
	protected		bool 					currentlyInMultiLineOp;

	
	/** ***********************************************************************************************
	 * <summary>
	 * Creates a TextFileLogger with the given name.
	 * </summary>
	 * <param name="fileName"  > The filename (potentially including a path) of the output log file.	 </param>
	 * <param name="loggerName"> The name of the logger. Defaults to "TEXTFILE".		</param>
	 **************************************************************************************************/
	public TextFileLogger( String fileName, String	loggerName= "TEXTFILE"  )	 : base ( loggerName )
	{
		this.fileName= fileName;	
	}

	/** ***********************************************************************************************
	 * <summary>
	 * Implementation of abstract interface signaling start and end of a multi line message.
	 * On start signal, the log file is opened, closed otherwise. Also stores the actual
	 * multi line message state in a field. This is for doTextLog() to know whether file is to be 
	 * opened/closed.
	 * </summary>
	 * <param name="isStart">	If true, indicates the begin of a multi-line message, the end of 
	 * 							it otherwise. </param>
	 **************************************************************************************************/
	protected override void notifyMultiLineOp (bool isStart)
	{
		// save state (to have it in doTextLog)
		currentlyInMultiLineOp= isStart;
		
		// open/close the file
		if ( isStart )
			openFile();
		else
			closeFile();
	} 


	/** ***********************************************************************************************
	 * <summary>
	 *	This implements the abstract method of parent class TextLogger and logs text messages into the 
	 *	text log file.
	 * </summary>
	 * <param name="domain">		The log domain name. </param>
	 * <param name="level">			The log level. This has been checked to be active already on this
	 * 								stage and is provided to be able to be logged out only. </param>
	 * <param name="msg">			The log message. </param>
	 * <param name="indent">		the indentation in the output. Defaults to 0. </param>
	 * <param name="caller">		Once compiler generated and passed forward to here. </param>
	 * <param name="lineNumber">	The line number of a multi-line message, starting with 0. For
	 * 								single line messages this is -1. </param>
	 **************************************************************************************************/
	protected override void	 doTextLog( MString		domain,		Log.Level	level, 
										MString		msg,		int			indent,
										CallerInfo	caller, 	int			lineNumber)
	{
		// open file (only if we are not processing a multi line operation
		if ( !currentlyInMultiLineOp )
			openFile();
			
		// if open failed, leave  
		if ( IsDisabled )
			return;
			
		// write m
		msg.NewLine();
		try 
		{
			sw.Write( msg.Buffer, 0, msg.Length );
		} 
		#pragma warning disable 168
		catch (Exception e)
		{
			IsDisabled= 	true;
			#if ALOX_DEBUG
				LogTools.Exception( Log.LOX.InternalDomain, Log.Level.Error, e, "Error writing to file: \"" + fileName + "\". Exception follows"  );
			#endif
		}
		#pragma warning restore 168

		// open file (only if we are not processing a multi line operation
		if ( !currentlyInMultiLineOp )
			closeFile();  
	}
	


	/** ***********************************************************************************************
	 * <summary>
	 *	Opens the file. If not successful, the logger will be disabled (by setting field isDisabled) 
	 * </summary>
	 **************************************************************************************************/
	protected void openFile()
	{		
		try 
		{
			sw=		new StreamWriter( fileName, true );
		} 
		#pragma warning disable 168
		catch (Exception e)
		{
			IsDisabled= 	true;
			#if ALOX_DEBUG
				LogTools.Exception( Log.LOX.InternalDomain, Log.Level.Error, e, "Can not open file: \"" + fileName + "\". Exception follows"  );			
			#endif
		}
		#pragma warning restore 168
	}

	/** ***********************************************************************************************
	 * <summary>
	 *	Closes the file. If not successful, the logger will be disabled (by setting field isDisabled). 
	 * </summary>
	 **************************************************************************************************/
	protected void closeFile()
	{		
		try 
		{
			sw.Close();			
		} 
		#pragma warning disable 168
		catch (Exception e)
		{
			IsDisabled= 	true;
			#if ALOX_DEBUG
				LogTools.Exception( Log.LOX.InternalDomain, Log.Level.Error, e, "Error closing file: \"" + fileName + "\". Exception follows"  );
			#endif
		}
		#pragma warning restore 168
	}
	#endif // ALOX_DEBUG || ALOX_REL_LOG

	
} // class TextFileLogger
} // namespace
