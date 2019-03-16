// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.lang;

/** ****************************************************************************************
 * Denotes whether something should be created if it does not exist.
 ******************************************************************************************/
public enum Create
{
    NEVER,          ///< Do not create.
    IF_NOT_EXISTENT ///< Create if something does not exist.
}
