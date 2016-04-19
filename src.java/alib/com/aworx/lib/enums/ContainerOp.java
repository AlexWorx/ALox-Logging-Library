// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.enums;

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
