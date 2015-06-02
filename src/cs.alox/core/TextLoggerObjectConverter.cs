// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

#if (ALOX_DEBUG || ALOX_REL_LOG)

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using com.aworx.util;
using com.aworx.lox;
using com.aworx.lox.core;

namespace com.aworx.lox.core {

/** ************************************************************************************************
 * <summary>
 *  This class is a sort of plug-in for the TextLogger class which converts a given Object
 *  into its textual representation. An internal AString singleton is used as a string buffer
 *  and returned.
 *
 *  This class might be extended to be able to handle custom objects within text loggers.
 *  This default implementation, handles objects of type *String*, *AString* and *StringBuilder*,
 *  For null values a predefined string is returned.
 *  All other Object types are converted by invoking their toString() function
 * </summary>
 **************************************************************************************************/
public class TextLoggerObjectConverter
{
     /// <summary>    Used to convert null values to string representation. </summary>
    public           String                FmtNullObject                        ="<null>";

    /// <summary>    Buffer singleton to store the string representation of Objects. </summary>
    protected        AString                buffer                              =new AString( 128 );


    /** ********************************************************************************************
     * <summary> The conversion method. </summary>
     * <param name="o"> The object to convert. </param>
     * <returns>        The filled AString singleton #buffer or, in the case that the given object was
     *                  of type AString already, just the object itself! </returns>
     **********************************************************************************************/
    public virtual AString ConvertObject( Object o )
    {
        // copy the string into our internal Buffer (or reassign if AString given)
        AString msg=     buffer;
        msg.Clear();
             if ( o == null )           msg.Append( FmtNullObject );
        else if ( o is String )         msg.Append( (String)         o );
        else if ( o is AString )        msg=        (AString)        o  ; // reassign!
        else if ( o is StringBuilder )  msg.Append( (StringBuilder)  o );

        // default: use ToString()
        else
            msg.Append( o.ToString() );

        return msg;
    }
} // class
} // namespace

#endif
