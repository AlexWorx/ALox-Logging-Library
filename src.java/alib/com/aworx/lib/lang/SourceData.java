// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lib.lang;

/** ****************************************************************************************
 * Denotes if the source data should be moved or copied.
 ******************************************************************************************/
public enum SourceData
{
    COPY,   ///<  Chooses not to clear existing data.
    MOVE,   ///<  Chooses to clear existing data.
}

