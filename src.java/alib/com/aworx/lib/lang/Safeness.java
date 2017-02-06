// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.lang;

/** ****************************************************************************************
 * Denotes whether something should be performed in a safe or unsafe fashion.
 ******************************************************************************************/
public enum Safeness
{
    SAFE,    ///<  Do it or treat it with safety.
    UNSAFE,  ///<  Omit checks or perform unsafe operations.
}
