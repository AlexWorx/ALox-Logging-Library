package com.aworx.util;

/**************************************************************************************************
 * Static methods and fields A-Worx Utility library.
 **************************************************************************************************/
public final class AWXU
{
    /**************************************************************************************************
     * The error handler singleton. This can be set statically from outside to enable the report of
     * A-Worx util errors and warnings.
     **************************************************************************************************/
	public	static			AWXUErrorHandler	errorHandler=			null;

    /**************************************************************************************************
     * This is calling Thread.Sleep() and catching any exception.
     *
     * @param millisecs Time of the hold in milliseconds.
     **************************************************************************************************/
	public static void sleep( int millisecs )
	{
		try						{ if ( millisecs > 0 )	Thread.sleep( millisecs );	}
		catch( Exception e )	{ if ( errorHandler != null ) errorHandler.warning( "AWXU.sleep() caught exception" );	}
		
	}
	
}// class AWXU
