// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


/** ************************************************************************************************
 * This namespace collects very basic utilities, close to the Java language.
 * In other words, elements found in this namespace are not complex enough to justify a
 * dedicated sub-namespace, but are also not essential enough to be placed in
 * #com.aworx.lib itself. The latter namespace is reserved for elements that are essential to
 * and included by separated <b>%ALib Modules</b>. (Modules are available in the C++ version
 * of \b %ALib only.
 *
 * \note
 *   A list of <b>general enumerations</b> is found in this namespace.
 *   It is arguable and a matter of taste, whether enumerations should be declared near or inside
 *   the class which is using it, or in a separated place like this namespace introduced here.<br>
 *   \b %ALib follows the second approach (not strictly, domain specific enums might appear also inside
 *   classes) and this has the following reasons:
 *   - To shorten the code when using the enums.
 *   - To reach a maximum degree of source compatibility between the different programming language
 *     versions of \b %ALib.
 *   - To make the enums reusable with different classes.
 **************************************************************************************************/
package com.aworx.lib.lang;

/** ****************************************************************************************
 * Denotes Alignments
 ******************************************************************************************/
public enum Alignment
{
    LEFT,   ///<  Align the contents of the field at the left.
    RIGHT,  ///<  Align the contents of the field at the right.
    CENTER  ///<  Center the contents of the field.
}
