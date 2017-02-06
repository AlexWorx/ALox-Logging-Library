// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
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
 * This abstract class represents a plug-in for the TextLogger class which converts the list
 * of logables into a textual representation.
 * \see StandardConverter for further information.
 **************************************************************************************************/
public abstract class ObjectConverter
{
    /** ********************************************************************************************
     * The conversion method.
     * @param target     An AString that takes the result.
     * @param logables   The objects to convert.
     **********************************************************************************************/
    abstract public void ConvertObjects(AString target, List<Object> logables);
} // class


/** ************************************************************************************************
 * Implements the interface
 * \ref cs::aworx::lox::core::textlogger::ObjectConverter "ObjectConverter". Class
 * \ref cs::aworx::lox::core::textlogger::TextLogger      "TextLogger" creates an instance of this
 * type in the moment no other (custom) type was set prior to the first log statement.
 *
 * This implementation uses
 * two specialisations of class
 * \ref cs::aworx::lib::strings::Formatter "Formatter" to format the given logables to a textual
 * representation. The formatters (and their sequence!) are:
 *
 * 1. \ref cs::aworx::lib::strings::FormatterPythonStyle "FormatterPythonStyle"
 * 2. \ref cs::aworx::lib::strings::FormatterJavaStyle   "FormatterJavaStyle"
 *
 * This way, standard text logging supports format strings in Python style as well as in Java style.
 **************************************************************************************************/
public class StandardConverter : ObjectConverter
{
    /** Formatter to process python style format strings. Used as the first (main) formatter. */
    public FormatterPythonStyle                 FormatterPS;

    /** Formatter to process Java style format strings. Attached to #FormatterPS as second
     *  format option.*/
    public FormatterJavaStyle                   FormatterJS;

    /** ****************************************************************************************
     * Constructor.
     ******************************************************************************************/
    public StandardConverter()
    {
        FormatterPS     = new FormatterPythonStyle();
        FormatterJS     = new FormatterJavaStyle();
        FormatterPS.Next= FormatterJS;
    }

    /** ********************************************************************************************
     * The conversion method.
     * Passes \p target and \p logables to #FormatterPS.
     * @param target     An AString that takes the result.
     * @param logables   The objects to convert.
     **********************************************************************************************/
    public override void ConvertObjects( AString target, List<Object>  logables )
    {
        FormatterPS.FormatList( target, logables );
    }
}


} // namespace

#endif
