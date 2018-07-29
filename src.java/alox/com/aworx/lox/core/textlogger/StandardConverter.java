// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core.textlogger;

import java.util.ArrayList;

import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.format.FormatterPythonStyle;
import com.aworx.lib.strings.format.FormatterJavaStyle;
import com.aworx.lib.strings.format.FormatterStdImpl;

/** ************************************************************************************************
 * Implements the interface
 * \ref com.aworx.lox.core.textlogger.ObjectConverter "ObjectConverter". Class
 * \ref com.aworx.lox.core.textlogger.TextLogger      "TextLogger" creates an instance of this
 * type in the moment no other (custom) type was set prior to the first log statement.
 *
 * This implementation uses
 * two specialisations of class
 * \ref com.aworx.lib.strings.format.Formatter "Formatter" to format the given logables to a textual
 * representation. The formatters (and their sequence!) are:
 *
 * 1. \ref com.aworx.lib.strings.format.FormatterPythonStyle "FormatterPythonStyle"
 * 2. \ref com.aworx.lib.strings.format.FormatterJavaStyle   "FormatterJavaStyle"
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

    /** A counter to detect recursive calls.  */
    protected int                               cntRecursion                                    = 0;

    /**
     * Formatters used with recursive calls log calls. If recursion occurs, the formatters
     * are created, respectively re-used from last time and their settings are reset to
     * those of the main formatters.
     */
    protected ArrayList<FormatterPythonStyle>   recursionFormatters = new ArrayList<FormatterPythonStyle>();

    /** ****************************************************************************************
     * Constructor.
     ******************************************************************************************/
    public StandardConverter()
    {
        formatterPS     = new FormatterPythonStyle();
        formatterJS     = new FormatterJavaStyle();
        formatterPS.next= formatterJS;
    }

    /** ********************************************************************************************
     * The conversion method.
     * Passes \p{target} and \p{logables} to #formatterPS.
     * @param logables   The objects to convert.
     * @param target     An AString that takes the result.
     **********************************************************************************************/
    @Override
    public void convertObjects( AString target, ArrayList<Object> logables )
    {
        cntRecursion++;

        // get a formatter. We use a clone per recursion depth!
        FormatterPythonStyle formatter;
        if( cntRecursion == 1 )
            formatter= formatterPS;
        else
        {
            // did we have this depth already? If not, create a new set of formatters formatter
            int recFormatNo= cntRecursion - 1;
            if( recursionFormatters.size() <= recFormatNo )
            {
                formatter= new FormatterPythonStyle();
                formatter.next= new FormatterJavaStyle();
                recursionFormatters.add( formatter );
            }
            else
                formatter= recursionFormatters.get(recFormatNo);

            // clone the settings from default formatter set
            formatter.cloneSettings( formatterPS );
            ((FormatterStdImpl)formatter.next).cloneSettings( formatterJS );
        }

        formatter.format( target, logables );

        cntRecursion--;

    }
}
