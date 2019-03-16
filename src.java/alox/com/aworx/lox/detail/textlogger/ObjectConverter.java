// #################################################################################################
//  com.aworx.lox.detail - ALox Logging Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox.detail.textlogger;

import java.util.ArrayList;

import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.util.AutoSizes;

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
    public void        convertObjects( AString target, ArrayList<Object> logables );

    /** ****************************************************************************************
     * If this converter uses an \alib{strings::util,AutoSizes} object, this method returns
     * such object.
     * @return The auto sizes used, \c nullptr if not applicable.
     ******************************************************************************************/
    public AutoSizes   getAutoSizes();

    /** ****************************************************************************************
     * If this converter uses an \alib{strings::util,AutoSizes} object, values of this field
     * are reset.
     ******************************************************************************************/
    public void        resetAutoSizes();

}
