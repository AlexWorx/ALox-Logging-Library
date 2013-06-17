// #################################################################################################
//  AWorx Util - Classes we need
//
//  (c) 2013 A-Worx GmbH,  Published under the The MIT License (Open Source License, see LICENSE.txt)
//  
//  Class:	ThreadLock
//  File:	ThreadLock.cs											Namespace:  com.aworx.util
// #################################################################################################

using System;
using System.Text;
using System.Threading;

namespace com.aworx.util  {

/** ***********************************************************************************************
 * <summary> Interface for AWXU error handler. </summary>
 **************************************************************************************************/
public interface AWXUErrorHandler
{
	/** ***********************************************************************************************
	 * <summary> Report an AWXU Error. </summary>
	 * <param name="msg">	The error message. </param>
	 **************************************************************************************************/
	void error  ( Object msg );
	
	/** ***********************************************************************************************
	 * <summary> Report an AWXU Error. </summary>
	 * <param name="msg">	The error message. </param>
	 **************************************************************************************************/
	void warning( Object msg );
}

/** ***********************************************************************************************
 * <summary> Static methods and fields A-Worx Utility library. </summary>
 **************************************************************************************************/
public static class AWXU
{
	/** ***********************************************************************************************
	 * <summary> 
	 * 	The error handler singleton. This can be set statically from outside to enable the report
	 *  of A-Worx util errors and warnings.
	 * </summary>
	 **************************************************************************************************/
	public	static			AWXUErrorHandler	errorHandler=			null;

	/** ***********************************************************************************************
	 * <summary> This is calling Thread.Sleep(). This is for compatibility with other platform
	 * versions of A-Worx Utility Classes </summary>
	 * <param name="millisecs">	Time of the hold in milliseconds. </param>
	 **************************************************************************************************/
	public static void Sleep(int millisecs)
	{
		if ( millisecs > 0 )
			Thread.Sleep( millisecs );
	}
}// class AWXU
	


} // namespace / EOF
