// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


package com.aworx.lib.lang;

/** ****************************************************************************************
 * Denotes upper and lower case character treatment.
 ******************************************************************************************/
public enum Case
{
    SENSITIVE, ///< Chooses an operation mode which differs between lower and upper case letters
               ///  (usually the default).
    IGNORE     ///< Chooses an operation mode which does not differ between between lower and
               ///  upper case letters.
}