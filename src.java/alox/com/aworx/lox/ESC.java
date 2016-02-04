// #################################################################################################
//  com.aworx.lox.core - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

/** ************************************************************************************************
 * This class defines "escape sequences" that influence the formatting of log output.
 * Specific implementations of class
 * \ref com::aworx::lox::core::Logger "Logger"
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
 *  \snippet "UT_alox_documentation_samples.java"     DOC_SAMPLES_ALOX_ESC
 **************************************************************************************************/
public class ESC
{
    public static final String  RED         = "\033c0";  ///< Select red color for foreground.
    public static final String  GREEN       = "\033c1";  ///< Select green color for foreground.
    public static final String  YELLOW      = "\033c2";  ///< Select yellow color for foreground.
    public static final String  BLUE        = "\033c3";  ///< Select blue color for foreground.
    public static final String  MAGENTA     = "\033c4";  ///< Select magenta color for foreground.
    public static final String  CYAN        = "\033c5";  ///< Select cyan color for foreground.
    public static final String  BLACK       = "\033c6";  ///< Select black color for foreground.
    public static final String  WHITE       = "\033c7";  ///< Select white color for foreground.
    public static final String  GRAY        = "\033c8";  ///< Select gray color for foreground.
    public static final String  FG_RESET    = "\033c9";  ///< Select std color for foreground.
                                                
    public static final String  BG_RED      = "\033C0";  ///< Select red color for background.
    public static final String  BG_GREEN    = "\033C1";  ///< Select green color for background.
    public static final String  BG_YELLOW   = "\033C2";  ///< Select yellow color for background.
    public static final String  BG_BLUE     = "\033C3";  ///< Select blue color for background.
    public static final String  BG_MAGENTA  = "\033C4";  ///< Select blue color for background.
    public static final String  BG_CYAN     = "\033C5";  ///< Select blue color for background.
    public static final String  BG_BLACK    = "\033C6";  ///< Select red color for background.
    public static final String  BG_WHITE    = "\033C7";  ///< Select blue color for background.
    public static final String  BG_GRAY     = "\033C8";  ///< Select gray color for background.
    public static final String  BG_RESET    = "\033C9";  ///< Select std color for background.
                                                
    public static final String  BOLD        = "\033sB";  ///< Select bold font style.
    public static final String  ITALICS     = "\033sI";  ///< Select italics font style.
    public static final String  STYLE_RESET = "\033sr";  ///< Select standard font style.
                                                
    public static final String  RESET       = "\033sa";  ///< Reset color and style.
                                                
    public static final String  URL_START   = "\033lS";  ///< Mark the start of an URL.
    public static final String  URL_END     = "\033lE";  ///< Mark the end of an URL.
    
    public static final String  TAB         = "\033t0";  ///< Go to next tab. Usually, text loggers
                                                         ///< will increase the tab position automatically.
    public static final String  EOMETA      = "\033A0";  ///< End of meta information in log string
                                                         

} // class ESC