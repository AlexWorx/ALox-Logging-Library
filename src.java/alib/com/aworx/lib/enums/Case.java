// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


package com.aworx.lib.enums;

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