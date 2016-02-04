// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.enums;

/** ****************************************************************************************
 * Denotes whether a e.g a setting should be propagated.
 ******************************************************************************************/
public enum Propagation
{
    NONE,          ///< Do not propagate changes.
    TO_DESCENDANTS ///< Propagate changes to descendants/childs/subcomponents.
}
