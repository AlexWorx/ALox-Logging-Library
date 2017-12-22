﻿// #################################################################################################
//  cs.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


using System;
using cs.aworx.lib;
using cs.aworx.lib.strings;

namespace cs.aworx.lox    {


/** ************************************************************************************************
* This enum is used in %ALox to control the 'verbosity' or 'verboseness' of the log output.
 * The values herein - apart from special value 'Off' - are sorted in the following order
 * - Verbose (highest level)
 * - Info
 * - Warning
 * - Error (lowest level).
 *
 * A value of this set is provided to ALox in two different ways:
 * First, all methods of class \ref cs.aworx.lox.Lox "Lox" that execute a log operation
 * assign a value of this enum to the <em>Log Statement</em>. Secondly, methods
 * \ref cs.aworx.lox.Lox.SetVerbosity "Lox.SetVerbosity", are defining the 'accepted' \e minimal
 * \e Verbosity for a pair of <em>\<Logger/%Log Domain\></em>.
 *
 * %ALox, when executing a statement, checks both values against each other. A <em>Log Statement</em>
 * is executed, when the <em>\<Logger/%Log Domain\></em> setting is set to the same or a 'higher level'.
 * For example if a <em>\<Logger/%Log Domain\></em> setting is \b %Warning, then <em>Log Statements</em>
 * with associated \e %Verbosity \b %Warning and \b %Error are executed and those with \b %Info and
 * \b %Verbose are suppressed.
 *
 * If special value \b %Off is used with \ref cs.aworx.lox.Lox.SetVerbosity "Lox.SetVerbosity",
 * all logging is switched Off for this pair of <em>\<Logger/%Log Domain\></em>.
 *
 * Some of the <em>Log Statements</em> accept the parameter directly (e.g.
 * \ref cs.aworx.lox.Lox.Entry "Lox.Entry",
 * \ref cs.aworx.lox.Lox.Once  "Lox.Once" and
 * \ref cs.aworx.lox.Lox.If "Lox.If"), others inherently use the right value as their method
 * name suggests (e.g.
 * \ref cs.aworx.lox.Lox.Error      "Lox.Error",
 * \ref cs.aworx.lox.Lox.Warning    "Lox.Warning",
 * \ref cs.aworx.lox.Lox.Info       "Lox.Info",
 * \ref cs.aworx.lox.Lox.Verbose    "Lox.Verbose" and
 * \ref cs.aworx.lox.Lox.Assert     "Lox.Assert"). The latter group of methods do not support
 * parameter \b %Off.
 *
 * If special value \b %Off is used with those <em>Log Statements</em>, that allow to specify the \e %Verbosity
 * as a parameter, the <em>Log Statement</em> is never executed This is useful if the parameter is
 * determined at runtime, depending on the state of an application.
  **************************************************************************************************/
public enum Verbosity
{
    /**
     * The 'highest' level of \e %Verbosity.
     * Statements with this value associated are logged only if a <em>%Log Domain</em> is set to \b %Verbose as well.
     */
    Verbose,

    /**
     * The standard \e Verbosity for normal log output statements.
     * Logged if a <em>%Log Domain</em> is set to \b %Info or \b %Verbose.
     */
    Info,

    /**
     * A \e Verbosity for warning messages, hence things that might lead to errors or are not
     * welcome for other reasons, but maybe are not errors.<br>
     * Logged if a <em>%Log Domain</em> is set to \b %Warning, \b %Info or \b %Verbose.
     */
    Warning,

    /**
     * A \e Verbosity for error messages.
     * It is suppressed only if a <em>%Log Domains'</em> setting is \b %Off.
     */
    Error,

    /**
     * Statements with this value associated are never logged (useful if \e %Verbosity is
     * evaluated at runtime). <em>%Log Domains</em> with this setting do not execute any
     * <em>Log Statement</em>.
     */
    Off
}

/** ************************************************************************************************
 * These are definitions which are used as a parameter to certain ALox methods to denote
 * the \e Scope of a setting. \e Scopes are dependent of the programming language
 * and hence differ slightly from each other in the different versions of ALox.
 *
 * \note
 *   ALox for C# implements scope mechanisms using scope information generated by method
 *   anotations.
 *   By default, debug logging supports such 'caller information', while release logging does
 *   not.<br>
 *   Therefore, in release-logging, the use of \e Scopes 'Path', 'Filename' and
 *   'Method' will just default to an empty scope and therefore all reflect the same,
 *   shared scope, which is not very helpful. Therefore, for standard release logging,
 *   the use of the scope mechanisms should be be avoided, unless scope information is
 *   explicitly enabled.<br>
 *   For more information on \e Scopes consult the [ALox user manual](../manual.html).
 **************************************************************************************************/
public enum Scope
{
    /** Denotes the global (singleton) scope */
    Global,

    /** Denotes the actual thread as the scope. When used with <em>Scope Domains</em>,
    *   'inner' scopes can be defined optionally by multiple definitions.                */
    ThreadOuter,

    /** Denotes the actual source file as the scope*/
    Filename,

    /** Denotes the actual method as the scope*/
    Method,

    /** Denotes the actual thread as the scope. When used with <em>Scope Domains</em>,
     *   'inner' scopes can be defined optionally by multiple definitions.              */
    ThreadInner,

    /**
     * Denotes the actual source path as the scope. By adding positive integer values
     * to this element, 'outer' \e Scopes of this scope level itself can be defined using parent
     * directories of the path.
     */
    Path
}

/** ************************************************************************************************
 * This class defines "escape sequences" that influence the formatting of log output.
 * Specific implementations of class
 * \ref cs.aworx.lox.core.Logger "Logger"
 * have to convert or interpret this classes definitions of escape sequences
 * when processing log data. If no formatting of the output is supported by a specific Logger
 * implementation, such logger should filter and discard escape sequences defined here.
 *
 * The sequences are similar to ANSI Escape sequences and logger classes that
 * log to 'VT100' compatible terminals will simply convert them.
 *
 * The name of the class was intentionally chosen to be short, because the escape codes
 * defined with this class will be concatenated to log strings like that:
 *
 *  \snippet "UT_dox_reference_manual.cs"     DOC_SAMPLES_ALOX_ESC
 *
 * Note: to use the shortcut <em>ESC.XYZ</em> like this, you have to place an using statement in
 * your source code file:
 *
 *  \snippet "UT_dox_reference_manual.cs"     DOC_SAMPLES_ALOX_ESC_USING
 *
 * \note
 *   With the introduction of own, ALox-specific escape codes, software that uses ALox becomes
 *   independent from any underlying, platform-specific sequences. For example, ALox is not relying
 *   on ANSI color codes, which are not supported by colorful Windows consoles. Instead, on each
 *   platform, dedicated Loggers will perform the translation of ALox codes to platform-specific
 *   ones.
**************************************************************************************************/
public class ESC
{
    public static readonly String  RED         = "\x001Bc0";  ///< Select red color for foreground.
    public static readonly String  GREEN       = "\x001Bc1";  ///< Select green color for foreground.
    public static readonly String  YELLOW      = "\x001Bc2";  ///< Select yellow color for foreground.
    public static readonly String  BLUE        = "\x001Bc3";  ///< Select blue color for foreground.
    public static readonly String  MAGENTA     = "\x001Bc4";  ///< Select magenta color for foreground.
    public static readonly String  CYAN        = "\x001Bc5";  ///< Select cyan color for foreground.
    public static readonly String  BLACK       = "\x001Bc6";  ///< Select black color for foreground.
    public static readonly String  WHITE       = "\x001Bc7";  ///< Select white color for foreground.
    public static readonly String  GRAY        = "\x001Bc8";  ///< Select gray color for foreground.
    public static readonly String  FG_RESET    = "\x001Bc9";  ///< Select std color for foreground.

    public static readonly String  BG_RED      = "\x001BC0";  ///< Select red color for background.
    public static readonly String  BG_GREEN    = "\x001BC1";  ///< Select green color for background.
    public static readonly String  BG_YELLOW   = "\x001BC2";  ///< Select yellow color for background.
    public static readonly String  BG_BLUE     = "\x001BC3";  ///< Select blue color for background.
    public static readonly String  BG_MAGENTA  = "\x001BC4";  ///< Select blue color for background.
    public static readonly String  BG_CYAN     = "\x001BC5";  ///< Select blue color for background.
    public static readonly String  BG_BLACK    = "\x001BC6";  ///< Select red color for background.
    public static readonly String  BG_WHITE    = "\x001BC7";  ///< Select blue color for background.
    public static readonly String  BG_GRAY     = "\x001BC8";  ///< Select gray color for background.
    public static readonly String  BG_RESET    = "\x001BC9";  ///< Select std color for background.

    public static readonly String  BOLD        = "\x001BsB";  ///< Select bold font style.
    public static readonly String  ITALICS     = "\x001BsI";  ///< Select italics font style.
    public static readonly String  STYLE_RESET = "\x001Bsr";  ///< Select standard font style.

    public static readonly String  RESET       = "\x001Bsa";  ///< Reset color and style.

    public static readonly String  URL_START   = "\x001BlS";  ///< Mark the start of an URL.
    public static readonly String  URL_END     = "\x001BlE";  ///< Mark the end of an URL.

    public static readonly String  TAB         = "\x001Bt0";  ///< Go to next tab. Usually, text loggers
                                                              ///< will increase the tab position automatically.
    public static readonly String  EOMETA      = "\x001BA0";  ///< End of meta information in log string

    /** ********************************************************************************************
     * Replaces ESC codes in a string reversely to "ESC.XXX".
     * @param target   The string to replace in.
     * @param startIdx The index to start searching for ESC codes.
     **********************************************************************************************/
    public static void ReplaceToReadable( AString target, int startIdx )
    {
        while( (startIdx= target.IndexOf( '\x001B', startIdx ) ) >= 0 )
        {
            String val= "{ESC.";
            char c=  target.CharAt( startIdx + 1 );
            char c2= target.CharAt( startIdx + 2 );

            String code= "ERROR";

            // colors
            if( c == 'c' || c == 'C' )
            {
                if ( c == 'C' )
                    val+= "BG_" ;
                switch( c2 - '0' )
                {
                    case 0:  code= "RED"     ; break;
                    case 1:  code= "GREEN"   ; break;
                    case 2:  code= "YELLOW"  ; break;
                    case 3:  code= "BLUE"    ; break;
                    case 4:  code= "MAGENTA" ; break;
                    case 5:  code= "CYAN"    ; break;
                    case 6:  code= "BLACK"   ; break;
                    case 7:  code= "WHITE"   ; break;
                    case 8:  code= "GRAY"    ; break;
                    case 9:  code= "RESET"   ; break;
                    default: code= "COL_ERR"; break;
                }

            }

            // styles
            else if( c == 's' )
            {
                switch( c2 )
                {
                    case 'B': code= "BOLD"         ; break;
                    case 'I': code= "ITALICS"      ; break;
                    case 'r': code= "STYLE_RESET"  ; break;
                    case 'a': code= "RESET"        ; break;
                    default:  code= "STYLE_ERR"    ; break;
                }
            }

            // styles
            else if( c == 'l' )
            {
                switch( c2 )
                {
                    case 'S': code= "URL_START"    ; break;
                    case 'E': code= "URL_END"      ; break;
                    default:  code= "URL_ERR"      ; break;
                }
            }

            // others
            else if( c == 'l' && c2 == '0' )    code= "TAB";
            else if( c == 'A' && c2 == '0' )    code= "EOMETA";

            // Replace
            val+= code + '}';
            target.ReplaceSubstring( val, startIdx, 3 );
            startIdx+= 3;
        }
    }

} // class ESC
} // namespace
