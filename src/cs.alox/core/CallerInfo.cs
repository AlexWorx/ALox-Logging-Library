// #################################################################################################
//  ALox - Logging in Bauhaus Style!
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Classes:	CallerInfo
//  File:		CallerInfo.cs										Namespace:  com.aworx.lox.core
// #################################################################################################

using System;
using System.Collections.Generic;
using com.aworx.util;

#if !ALOX_NO_THREADS
	using System.Threading;
#endif


namespace com.aworx.lox.core {
/** ***********************************************************************************************
 * <summary>
 *  Encapsulates information of the caller that can be collected. This is platform specific, in 
 *  this case, .NET 4.5. What we currently can get from the .NET compiler, is the source file name
 *  of the calling code, the line number within the source file name and the name of the method
 *  the call is placed. We do not get the class name of the object or even its instance.
 * </summary>
 **************************************************************************************************/
#if ALOX_DEBUG || ALOX_REL_LOG

public class CallerInfo
{
	// #################################################################################################
	// Public fields / Properties
	// #################################################################################################

	/** <summary>	Name of the method the log call is placed in. </summary> **/
	public 		String					MethodName;

	/** <summary>	Name and path of the source code file the log call is placed in. </summary> **/
	public		String					SourceFileName;

	/** <summary>	Line number within the source code file the log call is placed in. </summary> **/
	public		int						LineNumber;

	/** <summary> Time of the call represented by this instance. </summary> **/
	public		TickTime				TimeStamp;

	/** <summary> Name and path of the source code file the log call is placed in. </summary> **/
	public		MString					ThreadName					= new MString(32);

	/** <summary> Name and path of the source code file the log call is placed in. </summary> **/
	public		int						ThreadID;


	/**
	 * <summary>
	 *  To shorten the log output the given prefix might be cut from the source file path.  
	 *  If this field is left to 'null' (or set to null at runtime), it is tried to detect this path
	 *  automatically once. However, in remote debug sessions (e.g. on mobile device development)
	 *  this fails. Hence, this parameter can be set 'manually' to the right prefix that is to be
	 *  consumed. In this case, whenever the project is compiled on a different machine setup (with
	 *  different project path), this field has to be changed. If it is not changed, there is no
	 *  other problem than that the path is not shortened and the log output might get a little wide.
	 *  If the output of the full path is intended, the parameter can be set to 'String.Empty'.  
	 * </summary>
	 */
	public		 String					ConsumableSourcePathPrefixString;


	// #################################################################################################
	// public interface
	// #################################################################################################

	/** ***********************************************************************************************
	 * <summary> Stores caller parameters, sets actual time stamp and receives thread information </summary>
	 * <param name="callerSourceFileName">	Name and path of the source code file the log call is
	 * 										placed in. </param>
	 * <param name="callerLineNumber">	  	Line number within the source code file the log call is
	 * 										placed in. </param>
	 * <param name="callerMemberName">	  	Name of the method the log call is placed in. </param>
	 * <param name="threadDictionary">	  	Dictionary for translationg thread IDs into more readable 
	 * 										thread names. </param>
	 **************************************************************************************************/
	public void Set (String callerSourceFileName, int callerLineNumber, String callerMemberName
#if !ALOX_NO_THREADS
		, Dictionary<int, String> threadDictionary 
#endif
		)
	{
		// 1) set the actual timestamp as early as possible
		TimeStamp.SetToNow();

		// 2) save parameters
		this.MethodName=		callerMemberName;
		this.SourceFileName=	callerSourceFileName;
		this.LineNumber=		callerLineNumber;

		// 3) get thread information
		#if !ALOX_NO_THREADS
		{
			ThreadName.Clear();

			// get current thread
			Thread thread=	Thread.CurrentThread;
			ThreadID=		thread.ManagedThreadId;

			// do we have a dictionary entry? 
			String threadName;
			if( threadDictionary.TryGetValue( ThreadID,  out threadName) )
				ThreadName.Append( threadName );
			else
			{
				if ( String.IsNullOrEmpty ( thread.Name ) )
					ThreadName.Append( ThreadID );
				else
					ThreadName.Append( thread.Name ).Append( '(' ).Append( ThreadID ).Append( ')' );
			}
		}
		#endif
	}

	/** ***********************************************************************************************
	 * <summary>
	 *  Get the defined or detected consumable source path prefix. See
	 *  #ConsumableSourcePathPrefixString for more details.
	 * </summary>
	 * <returns>	The consumable source path prefix. </returns>
	 **************************************************************************************************/
	public	String	GetConsumableSourcePathPrefix()
	{
		// detect cutable prefix from the filename path and current working directory
		// Note: we do this only once. And e do not use the prefix here
		//       This is up to the derived logger to do so.
		if ( ConsumableSourcePathPrefixString == null )
		{

			// get system execution path and compare to file path
			ConsumableSourcePathPrefixString= Environment.CurrentDirectory;

			// Get the prefix that is the same in both paths
			// The first letter might be a drive letter and here we have to ignore the case
			int driveLetterIndex= ConsumableSourcePathPrefixString.Length >= 2 && ConsumableSourcePathPrefixString[1] == ':' ? 0 : -1;
			int i= 0; 
			while (     i < SourceFileName						.Length
					&&  i < ConsumableSourcePathPrefixString	.Length
					&&  ( i== driveLetterIndex	? Char.ToUpperInvariant( ConsumableSourcePathPrefixString[i]) == Char.ToUpperInvariant( SourceFileName[i] ) 
												:						 ConsumableSourcePathPrefixString[i]  ==						  SourceFileName[i] 
					)
				)
			i++;

			// store consumable prefix and its length. If unsuccessful, "" is stored to prevent searching again
			ConsumableSourcePathPrefixString=		( i > 1)	? ConsumableSourcePathPrefixString.Substring(0, i)
																: String.Empty;
		}
		return ConsumableSourcePathPrefixString;
	}
} // class CallerInfo
	
#endif // ALOX_DEBUG || ALOX_REL_LOG ,started before class CallerInfo


} // namespace
