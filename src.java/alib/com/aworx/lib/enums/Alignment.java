// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


/** ************************************************************************************************
 * This namespace of the A-Worx Library (ALib) is used to declare general enumerations.
 * \note
 *   It is arguable and a matter of taste, whether enumerations should be declared near or inside
 *   the class which is using it, or in a separated place like this namespace introduced here.<br>
 *   ALib follows the second approach (not strictly, domain specific enums might appear also inside
 *   classes) and this has the following reasons:
 *   - To shorten the code when using the enums.
 *   - To reach a maximum degree of source compatibility between the different programming language
 *     versions of ALib.
 *   - To make the enums reusable with different classes.
 **************************************************************************************************/
package com.aworx.lib.enums;

/** ****************************************************************************************
 * Denotes Alignments
 ******************************************************************************************/
public enum Alignment
{
    LEFT,   ///<  Align the contents of the field at the left.    
    RIGHT,  ///<  Align the contents of the field at the right.   
    CENTER  ///<  Center the contents of the field.               
}