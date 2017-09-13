// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

/** ************************************************************************************************
 * These are definitions which are used as a parameter to certain \b %ALox methods to denote
 * the \e Scope of a setting. \e Scopes are dependent of the programming language
 * and hence differ slightly from each other in the different versions of \b %ALox.
 *
 * \note
 *   <b>%ALox for Java</b> implements scope mechanisms by collecting information from the current
 *   execution stack.
 *   By default, debug logging works well in respect to collecting such 'caller information',
 *   while release logging, when code gets 'obfuscated' problems may arise.
 *   Therefore, for release logging, the use of the \e Scopes 'PACKAGE', 'CLASS and 'METHOD'
 *   should be be avoided.<br>
 *   For more information on \e Scopes consult the [ALox user manual](../manual.html).
 **************************************************************************************************/
public enum Scope
{
    /** Denotes the global (singleton) scope */
    GLOBAL,

    /** Denotes the actual thread as the scope. When used with <em>Scope Domains</em>,
    *   'inner' scopes can be defined optionally by multiple definitions.                */
    THREAD_OUTER,

    /** Denotes the actual package as the scope.  When used, optionally 'outer' \e Scopes
     *  of this scope level itself can be defined using parent packages.*/
    PACKAGE,

    /** Denotes the actual class as the scope. */
    CLASS,

    /** Denotes the actual method as the scope. */
    METHOD,

    /** Denotes the actual thread as the scope. When used with <em>Scope Domains</em>,
     *   'inner' scopes can be defined optionally by multiple definitions.              */
    THREAD_INNER
}


