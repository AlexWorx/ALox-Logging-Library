package com.aworx.lox.core;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.*;

import com.aworx.util.*;


/**************************************************************************************************
 * Encapsulates information of the caller that can be collected. This is platform specific, in
 * this case, .NET 4.5. What we currently can get from the .NET compiler, is the source file
 * name of the calling code, the line number within the source file name and the name of the
 * method the call is placed. We do not get the class name of the object or even its instance.
 **************************************************************************************************/
public class CallerInfo
{
	// #################################################################################################
	// Public fields / Properties
	// #################################################################################################

	/**	Name and path of the source code file the log call is placed in. */
	public		MString					packageName					= new MString(32);

	/**	Name of the method the log call is placed in. */
	public 		MString					className					= new MString(32);

	/**	Name of the method the log call is placed in. */
	public 		MString					methodName					= new MString(32);

	/**	Name and path of the source code file the log call is placed in. */
	public		MString					fileNameAndLineNumber		= new MString(32);

	/** The thread that invoked the call. */
	public		Thread  				thread;
	
	/** Name and path of the source code file the log call is placed in. */
	public		MString					threadName					= new MString(32);

	/** Name and path of the source code file the log call is placed in. */
	public		long					threadID;

	/** Time of the call represented by this instance. */
	public		TickTime  				timeStamp					= new TickTime();
	
	// #################################################################################################
	// public interface
	// #################################################################################################

    /**************************************************************************************************
     * Stores parameters and sets actual time stamp.
     *
     * @param threadDictionary      Name of the method the log call is placed in.
     * @param skipablePackagePrefix Name and path of the source code file the log call is placed in.
     **************************************************************************************************/
	public void set (HashMap <Long, String>	threadDictionary, String skipablePackagePrefix  )
	{
		// 1) ----  first, we set the time stamp (as early as possible) ---- 
		timeStamp.setToNow();
		
		// 2) ----  get current thread  ----
		thread=		Thread.currentThread();
		threadID=	thread.getId();

		// do we have a dictionary entry? 
		threadName.clear();
		String name= threadDictionary.get( threadID ); 
		if( name != null )
			threadName.append( name );
		else
		{
			// no, does the thread have a name?
			threadName.append( thread.getName() ).append( '(' );
			if ( threadID > Integer.MAX_VALUE)		
				threadName.append( MString.empty + threadID  );
			else
				threadName.append( (int) threadID );
			threadName.append( ')' );
		}

		// 3) ----  get caller info ----
		{
//packageName				.Clear().Append( "a.package");
//className				.Clear().Append( "aClass"	);
//methodName				.Clear().Append( "method"   );
//fileNameAndLineNumber	.Clear().Append( "source.java:111" );
		
			// get StackTrace from a new Exception (this is how Thread does it internally)
			StackTraceElement[] 	stElems= 	(new Exception()).getStackTrace();
			int 					stackLen= 	stElems.length;
			String 					teClassName;
			StackTraceElement 		te;
			int i= 3;	// we skip 3 levels anyhow
			while (true )
			{
				te= stElems[i];
				teClassName= te.getClassName();
				if ( !teClassName.startsWith( skipablePackagePrefix ) )
					break;
					
				// next 
				if (++i == stackLen )
				{
					packageName				.append("(#err pkg)");
					className				.append("(#err class)");
					methodName				.append("(#err method)");
					fileNameAndLineNumber	.append("(#err filename)");
					return;
				}
			}
	
			// find last dot
			int dotPos= teClassName.lastIndexOf( '.' );
			
			// write names
			packageName				.clear().append( teClassName, 0, 		  dotPos  	);
			className				.clear().append( teClassName, dotPos + 1, 10000		);
			methodName				.clear().append( te.getMethodName() );
			fileNameAndLineNumber	.clear().append( te.getFileName() ).append( ':' ).append( te.getLineNumber() );
		}
	}



// ----------------------------------------------------------------------------
//  This is a version to get the caller package, class, method, file and line number
//  from an exception. This is for systems that do not support Thread.getStackTrace().
//  However, Android supports it and I do not know if there is a system that does
//  not support it today. So, this can be removed some day...
// ----------------------------------------------------------------------------. 
/*	
	protected	int						exStartIdx;
	protected	int						exEndIdx;
	protected	int						exLength;
	protected	MString					exceptionBuf				= new MString(8192);
	
	protected	ByteArrayOutputStream	exceptionBAOS;
	protected	PrintStream				exceptionPS					= new PrintStream(exceptionBAOS= new ByteArrayOutputStream(8192));

	
	protected void getCallerFromException( int stacklevel )
	{
		// dump a new exception into our exceptionBuf
		new Exception().printStackTrace(exceptionPS);
		exceptionBuf.Clear().Append( exceptionBAOS.toString() );
		exEndIdx= 	0;
		exLength=	exceptionBuf.length();
		exceptionBAOS.reset();
			
		// remove the first line (the exception message)
		nextExceptionLine();
		nextExceptionLine();

		// stack level given? Remove corresponding number of lines
		if ( stacklevel > 0)
		{
			while(stacklevel-- > 0)
				nextExceptionLine();
		}
		
		// no, then auto detect the right log line by omitting lines with prefix "com.aworx.lox"
		else
		{
			while( exStartIdx < exEndIdx )
			{
				if ( !exceptionBuf.ContainsAt( omittablePackagePrefix, exStartIdx, false ) )
					break;
				nextExceptionLine();
			}
		}
		
		// clear buffers
		packageName				.Clear();
		className				.Clear();
		methodName				.Clear();
		fileNameAndLineNumber	.Clear();
		
		// need this
		int		i;
		char 	c;
		char[]	buf=		exceptionBuf.Buffer;
		
		// find '(' in current line
		int 	bracketPos= exStartIdx;
		while ( bracketPos < exEndIdx && buf[ bracketPos ] != '(' )
			bracketPos++;

		// check
		if ( exStartIdx == exEndIdx )
		{
			packageName				.Append("(#err pkg)");
			className				.Append("(#err class)");
			methodName				.Append("(#err method)");
			fileNameAndLineNumber	.Append("(#err filename)");
			return;
		}
			
		// copy fileName:LineNumber 
		i=	bracketPos + 1;
		while ( i < exEndIdx && (c= buf[ i ]) != ')' )
		{
			fileNameAndLineNumber.Append( c );
			i++;
		}
		
		// search backwards for two dots
		int dot2Pos=   	bracketPos -1;	while ( dot2Pos >= exStartIdx && buf[dot2Pos] != '.' )	dot2Pos--;
		int dot1Pos=   	dot2Pos    -1;	while ( dot1Pos >= exStartIdx && buf[dot1Pos] != '.' )	dot1Pos--;
		
		// copy package name and classM
		packageName	.Append( exceptionBuf, exStartIdx, 	dot1Pos		- exStartIdx  );
		className	.Append( exceptionBuf, dot1Pos + 1,	dot2Pos		- dot1Pos - 1 );
		methodName	.Append( exceptionBuf, dot2Pos + 1,	bracketPos	- dot2Pos - 1 );
	}
	
	protected void nextExceptionLine()
	{
		char c;
		char[] buf= exceptionBuf.Buffer;
		
		// skip end of line and leading tab
		int start= exEndIdx;
		while( start < exLength && ( (c= buf[start])=='\r' || c=='\n'  || c=='\t' || c==' ') )
			start++;
			
		// skip "at "
		if( buf[start]=='a' && buf[start + 1]=='t' && buf[start + 2]==' ' )
			start+= 3;
		
		// find end of line
		int end= start + 1;
		while( end < exLength &&  (c= buf[end]) != '\r'  &&  c != '\n')
			end++;

		// not big enough, then clear (return empty string)
		if ( end - start < 2  )
			start= end;
			
		// store values in fields
		exStartIdx= start;
		exEndIdx=	end;
	}
*/

}
