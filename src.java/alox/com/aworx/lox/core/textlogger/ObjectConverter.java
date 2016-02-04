// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core.textlogger;

import com.aworx.lib.strings.AString;
import com.aworx.lox.LogBuf;

/** ************************************************************************************************
 * This class is a sort of plug-in for the TextLogger class which converts a given Object
 * into its textual representation. An internal AString singleton is used as a string buffer
 * and returned.
 *
 * This class might be extended to be able to handle custom objects within text loggers.
 * This default implementation, handles objects of type *String*, *AString*, *StringBuilder*,
 * *StringBuffer* and *CharSequence*. For null values a predefined string is returned.
 * All other Object types are converted by invoking their toString() function
 **************************************************************************************************/
public class ObjectConverter
{
    /** Used to convert null values to string representation. */
    public             String                fmtNullObject                = "<null>";

    /**  Buffer singleton to store the string representation of Objects.  */
    protected         AString                buffer                       = new AString( 128 );

    /** ********************************************************************************************
     * The conversion method.
     * @param o   The object to convert.
     * @return    The filled AString singleton #buffer or, in the case that the given object
     *            was of type AString already, just the object itself!
     **********************************************************************************************/
    public AString convertObject( Object o )
    {
        // copy the string into our internal Buffer (or reassign if AString given)
        AString msg=     buffer.clear();

             if ( o == null )                    msg._( fmtNullObject );
        else if ( o instanceof String )          msg._( (String)         o );
        else if ( o instanceof LogBuf )          msg=         ((LogBuf)  o).b;  // reassign!
        else if ( o instanceof AString )         msg=         (AString)  o;     // reassign!
        else if ( o instanceof StringBuilder )   msg._( (StringBuilder)  o );
        else if ( o instanceof StringBuffer )    msg._( (StringBuffer)   o );
        else if ( o instanceof CharSequence )    msg._( (CharSequence)   o );

        // default: toString()
        else
                msg._( o.toString());

        return msg;
    }
}
