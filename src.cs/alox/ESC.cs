// #################################################################################################
//  cs.aworx.lox.loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################


using System;
using cs.aworx.lib;

namespace cs.aworx.lox    {

/** ************************************************************************************************
 * This class defines "escape sequences" that influence the formatting of log output.
 * Specific implementations of class
 * \ref cs::aworx::lox::core::Logger "Logger"
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
 *  \snippet "UT_alox_documentation_samples.cs"     DOC_SAMPLES_ALOX_ESC
 *
 * Note: to use the shortcut <em>ESC::XYZ</em> like this, you have to place an using statement in
 * your source code file:
 *
 *  \snippet "UT_alox_documentation_samples.cs"     DOC_SAMPLES_ALOX_ESC_USING
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


} // class ESC
} // namespace
