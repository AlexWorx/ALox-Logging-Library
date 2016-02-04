// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
using cs.aworx.lib.strings;

#if (ALOX_DBG_LOG || ALOX_REL_LOG)

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using cs.aworx.lib;
using cs.aworx.lox;
using cs.aworx.lox.core;

namespace cs.aworx.lox.core.textlogger 
{

/** ************************************************************************************************
 * 
 *  This class is a sort of plug-in for the TextLogger class which converts a given Object
 *  into its textual representation. An internal AString singleton is used as a string buffer
 *  and returned.
 *
 *  This class might be extended to be able to handle custom objects within text loggers.
 *  This default implementation, handles objects of type *String*, *AString* and *StringBuilder*,
 *  For null values a predefined string is returned.
 *  All other Object types are converted by invoking their toString() function
 * 
 **************************************************************************************************/
public class ObjectConverter
{
     /// Used to convert null values to string representation. 
    public           String                FmtNullObject                        ="<null>";

    /// Buffer singleton to store the string representation of Objects. 
    protected        AString                buffer                              =new AString( 128 );


    /** ********************************************************************************************
     * The conversion method. 
     * @param o  The object to convert. </param>
     * @return      The filled AString singleton #buffer or, in the case that the given object was
     *                  of type AString already, just the object itself! 
     **********************************************************************************************/
    public virtual AString ConvertObject( Object o )
    {
        // copy the string into our internal Buffer (or reassign if AString given)
        AString msg=     buffer.Clear();
        
             if ( o == null )           msg._( FmtNullObject );
        else if ( o is String )         msg._( (String)         o );
        else if ( o is AString )        msg=        (AString)        o  ; // reassign!
        else if ( o is StringBuilder )  msg._( (StringBuilder)  o );

        // default: use ToString()
        else
            msg._( o.ToString() );

        return msg;
    }
} // class
} // namespace

#endif
