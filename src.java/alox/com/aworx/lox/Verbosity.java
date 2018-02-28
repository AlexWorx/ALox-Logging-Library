// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

/** ************************************************************************************************
* This enum is used in \b %ALox to control the 'verbosity' or 'verboseness' of the log output.
 * The values herein - apart from special value 'OFF' - are sorted in the following order
 * - VERBOSE (highest level)
 * - INFO
 * - WARNING
 * - ERROR (lowest level).
 *
 * A value of this set is provided to \b %ALox in two different ways:
 * First, all methods of class \ref com.aworx.lox.Lox "Lox" that execute a log operation
 * assign a value of this enum to the <em>Log Statement</em>. Secondly, methods
 * \ref com.aworx.lox.Lox.setVerbosity "Lox.setVerbosity", are defining the 'accepted' \e minimal
 * \e Verbosity for a pair of <em>\<Logger/%Log Domain\></em>.
 *
 * \b %ALox, when executing a statement, checks both values against each other. A <em>Log Statement</em>
 * is executed, when the <em>\<Logger/%Log Domain\></em> setting is set to the same or a 'higher level'.
 * For example if a <em>\<Logger/%Log Domain\></em> setting is \b %WARNING, then <em>Log Statements</em>
 * with associated \e %Verbosity \b %WARNING and \b %ERROR are executed and those with \b %INFO and
 * \b %VERBOSE are suppressed.
 *
 * If special value \b %OFF is used with \ref com.aworx.lox.Lox.setVerbosity "Lox.setVerbosity",
 * all logging is switched OFF for this pair of <em>\<Logger/%Log Domain\></em>.
 *
 * Some of the <em>Log Statements</em> accept the parameter directly (e.g.
 * \ref com.aworx.lox.Lox.entry "Lox.entry",
 * \ref com.aworx.lox.Lox.once  "Lox.once" and
 * \ref com.aworx.lox.Lox.If "Lox.If"), others inherently use the right value as their method
 * name suggests (e.g.
 * \ref com.aworx.lox.Lox.error      "Lox.error",
 * \ref com.aworx.lox.Lox.warning    "Lox.warning",
 * \ref com.aworx.lox.Lox.info       "Lox.info",
 * \ref com.aworx.lox.Lox.verbose    "Lox.verbose" and
 * \ref com.aworx.lox.Lox.Assert     "Lox.Assert"). The latter group of methods do not support
 * parameter \b %OFF.
 *
 * If special value \b %OFF is used with those <em>Log Statements</em>, that allow to specify the \e %Verbosity
 * as a parameter, the <em>Log Statement</em> is never executed This is useful if the parameter is
 * determined at runtime, depending on the state of an application.
 **************************************************************************************************/
public enum Verbosity
{
    /**
     * The 'highest' level of \e %Verbosity.
     * Statements with this value associated are logged only if a <em>%Log Domain</em> is set to \b %VERBOSE as well.
     */
    VERBOSE,

    /**
     * The standard \e Verbosity for normal log output statements.
     * Logged if a <em>%Log Domain</em> is set to \b %INFO or \b %VERBOSE.
     */
    INFO,

    /**
     * A \e Verbosity for warning messages, hence things that might lead to errors or are not
     * welcome for other reasons, but maybe are not errors.<br>
     * Logged if a <em>%Log Domain</em> is set to \b %WARNING, \b %INFO or \b %VERBOSE.
     */
    WARNING,

    /**
     * A \e Verbosity for error messages.
     * It is suppressed only if a <em>%Log Domains'</em> setting is \b %OFF.
     */
    ERROR,

    /**
     * Statements with this value associated are never logged (useful if \e %Verbosity is
     * evaluated at runtime). <em>%Log Domains</em> with this setting do not execute any
     * <em>Log Statement</em>.
     */
    OFF,
}
