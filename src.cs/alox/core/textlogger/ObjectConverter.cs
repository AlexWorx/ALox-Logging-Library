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
 * This abstract class represents a plug-in for the TextLogger class which converts a given Object
 * into its textual representation.
 * \see StringConverter for further information.
 **************************************************************************************************/
public abstract class ObjectConverter
{
    /** ********************************************************************************************
     * The conversion method.
     * @param o        The object to convert.
     * @param target   An AString that takes the result.
     * @return \c true, if the object was converted successfully, \c false otherwise.
     **********************************************************************************************/
    abstract public  bool ConvertObject( Object o, AString target );
} // class


/** ************************************************************************************************
 * Implements the interface
 * \ref cs::aworx::lox::core::textlogger::ObjectConverter "ObjectConverter".
 * With ALox leveraging the underlying
 * \ref cs::aworx::lib::strings "ALib string class-family", various standard string types are supported
 * with this converter.
 *
 * For null values a predefined string is returned.
 * All other Object types are converted by invoking their \b ToString() method.
 **************************************************************************************************/
public class StringConverter : ObjectConverter
{
     /// Used to convert null values to string representation.
    public           String                FmtNullObject                        ="<null>";

    /** ********************************************************************************************
     * The conversion method.
     * @param o        The object to convert.
     * @param target   An AString that takes the result.
     * @return \c true, if the object was converted successfully, \c false otherwise.
     **********************************************************************************************/
    public override bool ConvertObject( Object o, AString target )
    {
        // copy the string into our internal Buffer (or reassign if AString given)
             if ( o == null )       target._( FmtNullObject ); // <null>
        else                        target._( o )  ;           // let AString do the conversion

        // we always return true
        return true;
    }
}


} // namespace

#endif
