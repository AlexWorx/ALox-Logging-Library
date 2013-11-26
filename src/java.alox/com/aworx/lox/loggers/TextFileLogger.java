package com.aworx.lox.loggers;

import java.io.*;

import com.aworx.lox.Log;
import com.aworx.lox.core.CallerInfo;
import com.aworx.lox.core.TextLogger;
import com.aworx.lox.tools.LogTools;
import com.aworx.util.MString;


/**********************************************************************************************//**
 * This is a very simple file logger for textual log outputs. The file name string provided 
 * in the constructor is not verified. If write operations fail, this logger disables
 * itself by setting the inherited flag isDisabled to true. 
 * The fileName may be changed by simply setting the pubic member #fileName and the flag  
 * #isDisabled may be set to false by the user without the need of any other interaction. 
 **************************************************************************************************/
public class TextFileLogger extends TextLogger
{
	/** The path and fileName to the log file. */
	public		String					fileName;
	
	/** Used to write into a log file. */
	protected		FileWriter				fw;
	
	/** Used to write into a log file. */
	protected		BufferedWriter			bw;
	
	/** Flag to prevent file open/close operations when multiline text logging is performed. */
	protected	boolean 				currentlyInMultiLineOp;

	
    /**********************************************************************************************//**
     * Creates a TextFileLogger with the given name.
     *
     * @param fileName	  The filename (potentially including a path) of the output log file.
     * @param loggerName  The name of the logger. Defaults to "TEXTFILE".
     **************************************************************************************************/
	public TextFileLogger( String fileName, String	loggerName  )	{ super( loggerName);	this.fileName= fileName;	}

    /**********************************************************************************************//**
     * Creates a TextFileLogger with the name "TEXTFILE".
     * 
     * @param fileName	  The filename (potentially including a path) of the output log file.
     **************************************************************************************************/
	public TextFileLogger( String fileName)							{ super("TEXTFILE");	this.fileName= fileName;	}
	
	
  	/**********************************************************************************************//**
	 * Implementation of abstract interface signaling start and end of a multi line message.
	 * On start signal, the log file is opened, closed otherwise. Also stores the actual
	 * multi line message state in a field. This is for doTextLog() to know whether file is to be 
	 * opened/closed.
	 *
	 * @param isStart  	If true, indicates the begin of a multi-line message, the end of it otherwise. 
	 **************************************************************************************************/
	@Override protected void notifyMultiLineOp (boolean isStart)
	{
		// save state (to have it in doTextLog)
		currentlyInMultiLineOp= isStart;
		
		// open/close the file
		if ( isStart )
			openFile();
		else
			closeFile();
	} 

    /**********************************************************************************************//**
     * This implements the abstract method of parent class TextLogger and logs text messages into the 
     * text log file.
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
	@Override protected void doTextLog( MString		domain,		Log.Level	level, 
										MString		msg,		int			indent,
										CallerInfo	caller, 	int			lineNumber)
 	{
		// open file (only if we are not processing a multi line operation
		if ( !currentlyInMultiLineOp )
			openFile();
			
		// if open failed, leave  
		if ( isDisabled )
			return;
			
		// write m
		msg.newLine();
		try 
		{
			bw.write( msg.buffer, 0, msg.length );
		} 
		catch (Exception e)
		{
			isDisabled= 	true;
			LogTools.exception( Log.LOX.internalDomain, Log.Level.ERROR, e, "Error writing to file: \"" + fileName + "\". Exception follows"  );
		}

		// open file (only if we are not processing a multi line operation
		if ( !currentlyInMultiLineOp )
			closeFile();  
	}
	

 	/**********************************************************************************************//**
     * Opens the file. If not successful, the logger will be disabled (by setting field #isDisabled). 
     **************************************************************************************************/
	protected void openFile()
	{		
		try 
		{
			fw=		new FileWriter		( fileName, true ); // true= append
			bw= 	new BufferedWriter	( fw ); 
		} 
		catch (Exception e)
		{
			isDisabled= 	true;
			LogTools.exception( Log.LOX.internalDomain, Log.Level.ERROR, e, "Can not open file: \"" + fileName + "\". Exception follows"  );			
		}
	}

 	/**********************************************************************************************//**
     * Closes the file. If not successful, the logger will be disabled (by setting field #isDisabled). 
     **************************************************************************************************/
	protected void closeFile()
	{		
		try 
		{
			bw.close();			
		} 
		catch (Exception e)
		{
			isDisabled= 	true;
			LogTools.exception( Log.LOX.internalDomain, Log.Level.ERROR, e, "Error closing file: \"" + fileName + "\". Exception follows"  );
		}
	}
	
} // class TextFileLogger




