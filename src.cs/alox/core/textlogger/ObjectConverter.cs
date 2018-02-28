// #################################################################################################
//  cs.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using cs.aworx.lib.strings;

#if (ALOX_DBG_LOG || ALOX_REL_LOG)

using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

using cs.aworx.lib;
using cs.aworx.lib.strings.format;
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
 * \ref cs.aworx.lox.core.textlogger.ObjectConverter "ObjectConverter". Class
 * \ref cs.aworx.lox.core.textlogger.TextLogger      "TextLogger" creates an instance of this
 * type in the moment no other (custom) type was set prior to the first log statement.
 *
 * This implementation uses
 * two specialisations of class
 * \ref cs.aworx.lib.strings.format.Formatter "Formatter" to format the given logables to a textual
 * representation. The formatters (and their sequence!) are:
 *
 * 1. \ref cs.aworx.lib.strings.format.FormatterPythonStyle "FormatterPythonStyle"
 * 2. \ref cs.aworx.lib.strings.format.FormatterJavaStyle   "FormatterJavaStyle"
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

    /** A counter to detect recursive calls.  */
    protected int                               cntRecursion                                    = 0;

    /**
     * Formatters used with recursive calls log calls. If recursion occurs, the formatters
     * are created, respectively re-used from last time and their settings are reset to
     * those of the main formatters.
     */
    protected List<FormatterPythonStyle>     recursionFormatters = new List<FormatterPythonStyle>();
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
        cntRecursion++;

        // get a formatter. We use a clone per recursion depth!
        FormatterPythonStyle formatter;
        if( cntRecursion == 1 )
            formatter= FormatterPS;
        else
        {
            // did we have this depth already? If not, create a new set of formatters formatter
            int recFormatNo= cntRecursion - 1;
            if( recursionFormatters.Count <= recFormatNo )
            {
                formatter= new FormatterPythonStyle();
                formatter.Next= new FormatterJavaStyle();
                recursionFormatters.Add( formatter );
            }
            else
                formatter= recursionFormatters[recFormatNo];

            // clone the settings from default formatter set
            formatter.CloneSettings( FormatterPS );
            ((FormatterStdImpl)formatter.Next).CloneSettings( FormatterJS );
        }

        formatter.Format( target, logables );

        cntRecursion--;
    }
}


} // namespace

#endif
