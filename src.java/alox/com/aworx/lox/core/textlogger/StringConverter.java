// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core.textlogger;

import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lox.LogBuf;

/** ************************************************************************************************
 * Implements the interface
 * \ref com::aworx::lox::core::textlogger::ObjectConverter "ObjectConverter".
 * With ALox leveraging the underlying
 * \ref com::aworx::lib::strings "ALib string class-family", various standard string types are supported
 * with this converter.
 *
 * For null values a predefined string is returned.
 * All other Object types are converted by invoking their \b toString() method.
 **************************************************************************************************/
public class StringConverter implements ObjectConverter
{
    /** Used to convert null values to string representation. */
    public             String                fmtNullObject                = "<null>";

    /** ********************************************************************************************
     * The conversion method.
     * @param o         The object to convert.
     * @param target    An AString that takes the result.
     * @return \c true, if the object was converted successfully, \c false otherwise.
     **********************************************************************************************/
    @Override 
    public boolean convertObject( Object o, AString target )
    {
             if ( o == null )                    target._( fmtNullObject       );
        else if ( o instanceof LogBuf       )    target._(((LogBuf)       o).b );
        else if ( o instanceof AString      )    target._( (AString)      o    );
        else if ( o instanceof Substring    )    target._( (Substring)    o    );
        else if ( o instanceof CharSequence )    target._( (CharSequence) o    );
        else if ( o instanceof char[]       )    target._( (char[])       o    );
        else                                     target._( o.toString()        );

        // we always return true
        return true;
    }
}
