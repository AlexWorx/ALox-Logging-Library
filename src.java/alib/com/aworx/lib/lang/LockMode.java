// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.lang;

/** ****************************************************************************************
 * Denotes whether a lock should allow recursive locks (count them) or not.
 ******************************************************************************************/
public enum LockMode
{
    RECURSIVE,    ///< Allow nested locks.
    SINGLE_LOCKS  ///< Nested locks are ignored. First unlock, unlocks.
}
