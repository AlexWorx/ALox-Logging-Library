// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.lang;

/** ************************************************************************************************
 * Denotes standard container operations.
 **************************************************************************************************/
public enum ContainerOp
{
    INSERT,     ///< Denotes insertions.
    REMOVE,     ///< Denotes removals.
    GET,        ///< Denotes to search data.
    GET_CREATE, ///< Denotes to create data if not found.
    CREATE      ///< Denotes to create data.
}
