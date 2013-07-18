/**
 * 
 */
package com.aworx.lox.core;

import com.aworx.util.MString;

/**********************************************************************************************//**
 * This class is a sort of plug-in for the TextLogger class which converts a given Object
 * into its textual representation. An internal MString singleton is used as a string buffer
 * and returned.  
 * 
 * This class might be extended to be able to handle custom objects within text loggers.
 * This default implementation, handles objects of type *String*, *MString*, *StringBuilder*,
 * *StringBuffer* and *CharSequence*. For null values a predefined string is returned.
 * All other Object types are converted by invoking their toString() function 
 **************************************************************************************************/
public class TextLoggerObjectConverter
{
	/** Used to convert null values to string representation. */
	public 			String				fmtNullObject				= "<null>";

	/**  Buffer singleton to store the string representation of Objects.  */
	protected 		MString				buffer					= new MString( 128 );

	/**********************************************************************************************//**
	 * The conversion method. 
	 * @param o     The object to convert.
	 * @return 	    The filled MString singleton #buffer or, in the case that the given object
	 * 			    was of type MString already, just the object itself! 
	 **************************************************************************************************/
	public MString convertObject( Object o )
	{
		// copy the string into our internal Buffer (or reassign if MString given)
		MString msg= 	buffer.clear();

			 if ( o == null )					msg.append( fmtNullObject );
		else if ( o instanceof String ) 		msg.append( (String) 		o );
		else if ( o instanceof MString )		msg= 	    (MString) 		o;	 // reassign!
		else if ( o instanceof StringBuilder )	msg.append( (StringBuilder)	o );
		else if ( o instanceof StringBuffer )	msg.append( (StringBuffer)	o );
		else if ( o instanceof CharSequence )	msg.append( (CharSequence)	o );
		
		// default: toString()
		else 											
				msg.append( o.toString());
		
		return msg;
	}
}
