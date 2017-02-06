// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.lang;

/** ****************************************************************************************
 * Denotes whether a e.g a setting should be propagated.
 ******************************************************************************************/
public enum Propagation
{
    OMIT,           ///< Do not propagate changes.
    TO_DESCENDANTS  ///< Propagate changes to descendants/children/subcomponents.
}
