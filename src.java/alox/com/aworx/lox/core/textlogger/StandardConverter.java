// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core.textlogger;

import java.util.ArrayList;

import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.FormatterPythonStyle;
import com.aworx.lib.strings.FormatterJavaStyle;
import com.aworx.lib.strings.Substring;

/** ************************************************************************************************
 * Implements the interface
 * \ref com::aworx::lox::core::textlogger::ObjectConverter "ObjectConverter". Class
 * \ref com::aworx::lox::core::textlogger::TextLogger      "TextLogger" creates an instance of this
 * type in the moment no other (custom) type was set prior to the first log statement.
 *
 * This implementation uses
 * two specialisations of class
 * \ref com::aworx::lib::strings::Formatter "Formatter" to format the given logables to a textual
 * representation. The formatters (and their sequence!) are:
 *
 * 1. \ref com::aworx::lib::strings::FormatterPythonStyle "FormatterPythonStyle"
 * 2. \ref com::aworx::lib::strings::FormatterJavaStyle   "FormatterJavaStyle"
 *
 * This way, standard text logging supports format strings in Python style as well as in Java style.
 **************************************************************************************************/
public class StandardConverter implements ObjectConverter
{
    /** Formatter to process python style format strings. Used as the first (main) formatter. */
    public FormatterPythonStyle                 formatterPS;

    /** Formatter to process Java style format strings. Attached to #formatterPS as second
     *  format option.*/
    public FormatterJavaStyle                   formatterJS;

    /** ****************************************************************************************
     * Constructor.
     ******************************************************************************************/
    public StandardConverter()
    {
        formatterPS     = new FormatterPythonStyle();
        formatterJS     = new FormatterJavaStyle();
        formatterPS.Next= formatterJS;
    }

    /** ********************************************************************************************
     * The conversion method.
     * Passes \p target and \p logables to #formatterPS.
     * @param logables   The objects to convert.
     * @param target     An AString that takes the result.
     **********************************************************************************************/
    @Override
    public void convertObjects( AString target, ArrayList<Object> logables )
    {
        formatterPS.FormatList( target, logables );
    }
}
