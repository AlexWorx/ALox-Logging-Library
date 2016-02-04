// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.enums;

/** ****************************************************************************************
 * Denotes whether a lock should allow recursive locks (count them) or not.
 ******************************************************************************************/
public enum LockMode
{
    RECURSIVE,    ///< Allow nested locks.
    SINGLE_LOCKS  ///< Nested locks are ignored. First unlock, unlocks.
}
