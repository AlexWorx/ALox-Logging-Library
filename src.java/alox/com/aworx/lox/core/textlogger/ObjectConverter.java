// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core.textlogger;

import com.aworx.lib.strings.AString;

/** ************************************************************************************************
 * This abstract class represents a plug-in for the TextLogger class which converts a given Object
 * into its textual representation.
 * \see StringConverter for further information.
 **************************************************************************************************/
public interface ObjectConverter
{
    /** ********************************************************************************************
     * The conversion method.
     * @param o         The object to convert.
     * @param target    An AString that takes the result.
     * @return \c true, if the object was converted successfully, \c false otherwise.
     **********************************************************************************************/
    public boolean convertObject( Object o, AString target );
}
