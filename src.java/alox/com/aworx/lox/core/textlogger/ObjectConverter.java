// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.core.textlogger;

import java.util.ArrayList;

import com.aworx.lib.strings.AString;

/** ************************************************************************************************
 * This abstract class represents a plug-in for the TextLogger class which converts the list
 * of logables into a textual representation.
 * \see StandardConverter for further information.
 **************************************************************************************************/
public interface ObjectConverter
{
    /** ********************************************************************************************
     * @param target     An AString that takes the result.
     * @param logables   The objects to convert.
     **********************************************************************************************/
    public void convertObjects( AString target, ArrayList<Object> logables );
}
