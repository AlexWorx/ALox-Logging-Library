// #################################################################################################
//  cs.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Runtime.CompilerServices;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib;
using cs.aworx.lib.strings;
using cs.aworx.lib.strings.util;


/** ************************************************************************************************
 *  This is the C# namespace for the implementation of <em>logger classes</em> that are provided
 *  by default with <b>%ALox Logging Library</b>.
 *
 *  Developed by A-Worx GmbH and published under Boost Software License.
 **************************************************************************************************/
using cs.aworx.lox.core;
using cs.aworx.lib.lang;
using cs.aworx.lib.config;


namespace cs.aworx.lox.loggers    {


/** ************************************************************************************************
 * A logger that logs all messages using the .Net class <em>System.Console</em>. Converts color
 * sequences defined in class
 * \ref cs.aworx.lox.ESC "ESC"
 * that are found within the log messages (and meta info format strings) to a corresponding
 * color setting of class <em>System.Console</em>.
 *
 * Foreground and background colors can be set to be either light/dark or dark/light. This improves
 * the readability of log output a lot and even allows to read if foreground and background colors
 * are the same (they then still differ). However, the right setting for this is dependent on
 * the color scheme of the final output device (window). To manipulate the right setting, see field
 * #UseLightColors and also configuration variable
 * [ALOX_CONSOLE_LIGHT_COLORS](../group__GrpALoxConfigVars.html).
 *
 * \note
 *   The implementation of class <em>System.Console</em> and its color support is system
 *   dependent. E.g. under Mono V. 4.0.2. it was observed that dark and light colors are equal
 *   in effect. Therefore, it might be advisable to use a different type of console logger
 *   on certain platforms. E.g. under Linux with standard terminal output, class
 *   \ref cs.aworx.lox.loggers.AnsiConsoleLogger "AnsiConsoleLogger"
 *   might lead to better readable results.
 *
 * The name of the \e Logger defaults to "COLORCONSOLE".
 **************************************************************************************************/
public class ColorConsoleLogger : TextLogger
{
    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DBG_LOG || ALOX_REL_LOG)
            public ColorConsoleLogger( String name= "COLORCONSOLE" ){}
    #else
    // #############################################################################################
    // Fields
    // #############################################################################################

        /** Denotes states of field #UseLightColors.  */
        public enum LightColorUsage
        {
            _Undefined,      ///< Internal, temporary state
            Never,           ///< Never use light colors
            ForegroundLight, ///< Use light colors for foreground
            ForegroundDark   ///< Use light colors for background
        }

        /**
         * Foreground and background colors chosen by this class might differ in their intensity.
         * This increases the overall readability by increasing the contrast.
         * If the background color of a console window is dark, then the background colors of
         * colored log output should be darker colors than the foreground colors - and vice versa.
         *
         * Depending on the setting of this field, \b %ALox
         * \ref cs.aworx.lox.ESC "escape codes" for colors are translated to normal ANSI colors or
         * lighter ones:
         * - If this field is \ref LightColorUsage "LightColorUsage.Never", light colors are
         *   never used.
         * - If this field is \ref LightColorUsage "LightColorUsage.ForegroundLight", foreground
         *   colors will be light colors and background colors dark ones. This is the default.
         * - If \ref LightColorUsage "LightColorUsage.ForegroundDark", background colors will be
         *   light colors and foreground colors dark ones.
         *
         * The configuration variable [ALOX_CONSOLE_LIGHT_COLORS](../group__GrpALoxConfigVars.html)
         * allows to externally modify this flag. It is read once within the constructor .
         */
        public      LightColorUsage         UseLightColors;

        /** Conversion table from ESC to light colors      */
        protected   ConsoleColor[]          lightColors= {
                                                      ConsoleColor.Red    ,  // RED
                                                      ConsoleColor.Green  ,  // GREEN
                                                      ConsoleColor.Yellow ,  // YELLOW
                                                      ConsoleColor.Blue   ,  // BLUE
                                                      ConsoleColor.Magenta,  // MAGENTA
                                                      ConsoleColor.Cyan   ,  // CYAN
                                                      ConsoleColor.Black  ,  // BLACK
                                                      ConsoleColor.White  ,  // WHITE
                                                      ConsoleColor.Gray   ,  // GRAY
                                                  };

        /** Conversion table from ESC to dark colors      */
        protected   ConsoleColor[]          darkColors=  {
                                                      ConsoleColor.DarkRed    ,  // RED
                                                      ConsoleColor.DarkGreen  ,  // GREEN
                                                      ConsoleColor.DarkYellow ,  // YELLOW
                                                      ConsoleColor.DarkBlue   ,  // BLUE
                                                      ConsoleColor.DarkMagenta,  // MAGENTA
                                                      ConsoleColor.DarkCyan   ,  // CYAN
                                                      ConsoleColor.Black      ,  // BLACK
                                                      ConsoleColor.White      ,  // WHITE
                                                      ConsoleColor.DarkGray   ,  // GRAY
                                                  };



    /** ********************************************************************************************
     * Creates a ConsoleLogger.
     * @param name  (Optional) The name of the \e Logger, defaults to "COLOR_CONSOLE"
     **********************************************************************************************/
    public ColorConsoleLogger( String name= null )
    : base( name, "COLOR_CONSOLE", true )
    {
        // get actual console foreground color
        ConsoleColor fgCol= Console.ForegroundColor;

            // evaluate environment variable "ALOX_CONSOLE_LIGHT_COLORS"
            UseLightColors= LightColorUsage._Undefined;
            Variable variable= new Variable( ALox.CONSOLE_LIGHT_COLORS );
            if ( ALox.Config.Load(variable) > 0 && variable.Size() > 0)
            {
                Substring p= new Substring(variable.GetString());
                if(p.Trim().IsNotEmpty())
                {
                         if( p.ConsumePartOf( "foreground" ) > 0)  UseLightColors=  LightColorUsage.ForegroundLight;
                    else if( p.ConsumePartOf( "background" ) > 0)  UseLightColors=  LightColorUsage.ForegroundDark;
                    else if( p.ConsumePartOf( "never"      ) > 0)  UseLightColors=  LightColorUsage.Never;
                    else
                    {
                        ALIB_DBG.WARNING( "Unknown value specified in variable: " + variable.Fullname
                                      +" = " + variable.GetString() +'.' );
                    }
                }
            }

            if( UseLightColors == LightColorUsage._Undefined )
            {
                // default: dark background, hence use light color on foreground
                UseLightColors=     fgCol == ConsoleColor.Black
                                ||  fgCol == ConsoleColor.DarkBlue
                                ||  fgCol == ConsoleColor.DarkCyan
                                ||  fgCol == ConsoleColor.DarkGray
                                ||  fgCol == ConsoleColor.DarkGreen
                                ||  fgCol == ConsoleColor.DarkMagenta
                                ||  fgCol == ConsoleColor.DarkRed
                                ||  fgCol == ConsoleColor.DarkYellow    ? LightColorUsage.ForegroundDark
                                                                        : LightColorUsage.ForegroundLight;
        }


        // move verbosity information to the end to colorize the whole line
        MetaInfo.Format.SearchAndReplace( "]%V[", "][" );
        MetaInfo.Format._( "%V" );
        MetaInfo.VerbosityError           = ESC.RED;
        MetaInfo.VerbosityWarning         = ESC.BLUE;
        MetaInfo.VerbosityInfo            = "";
        MetaInfo.VerbosityVerbose         = ESC.GRAY;
    }

    /** ********************************************************************************************
     *
     *  The implementation of the abstract method of parent class TextLogger. Logs messages to the
     *  application console and/or the VStudio output window.
     *
     * @param domain      The <em>Log Domain</em>.
     * @param verbosity   The verbosity. This has been checked to be active already on this
     *                    stage and is provided to be able to be logged out only.
     * @param msg         The log message.
     * @param scope       Information about the scope of the <em>Log Statement</em>..
     * @param lineNumber  The line number of a multi-line message, starting with 0. For
     *                    single line messages this is -1.
     **********************************************************************************************/
    override protected void logText(  Domain     domain,     Verbosity verbosity,
                                      AString    msg,
                                      ScopeInfo  scope,      int       lineNumber)
    {
        // get actual console attributes
        ConsoleColor actualFGCol= Console.ForegroundColor;
        ConsoleColor actualBGCol= Console.BackgroundColor;

        // loop over message, print the parts between the escape sequences
        Tokenizer msgParts= new Tokenizer( msg, '\x1B' );
        Substring actual=   msgParts.Actual;
        Substring rest=     msgParts.Rest;
        int       column=   0;
        for(;;)
        {
            if ( msgParts.Next(Whitespaces.Keep).IsNotEmpty() )
            {
                #if !(ALOX_WP71 || ALOX_WP8)
                    Console.Write( msg.Buffer(), actual.Start, actual.Length() );
                #else
                    Console.Write( msg.ToString( 0, actual.Start, actual.Length() );
                #endif
                column+= actual.Length();
            }

            // end of loop?
            if ( !msgParts.HasNext() )
                break;

            // found an ESC sequence
            char c= rest.ConsumeChar();

            // Colors
            bool isForeGround=  true;
            if( c == 'C' || c == 'c' )
            {
                isForeGround=  c== 'c';

                c= rest.ConsumeChar();
                int colNo= c - '0';
                ALIB_DBG.ASSERT_WARNING( colNo >=0 && colNo <=9, "Unknown ESC-c code" );

                // set color
                if( colNo >= 0 && colNo <= 8 || colNo == 8)
                {
                    ConsoleColor[] cols=        UseLightColors != LightColorUsage.Never
                                          && ( (UseLightColors == LightColorUsage.ForegroundLight) == isForeGround )  ? lightColors : darkColors;
                    if ( isForeGround )
                        Console.ForegroundColor= cols[ colNo ];
                    else
                        Console.BackgroundColor= cols[ colNo ];
                }
                else if ( colNo == 9 )
                {
                    if ( isForeGround )
                        Console.ForegroundColor= actualFGCol;
                    else
                        Console.BackgroundColor= actualBGCol;
                }

                else
                {
                    ALIB_DBG.WARNING( "Unknown ESC- code" );
                }

            }

            // Styles
            else if ( c == 's' )
            {
                // bold/italics style not supported in Windows console

                // reset all
                if ( rest.ConsumeChar() == 'a' )
                {
                    Console.ForegroundColor= actualFGCol;
                    Console.BackgroundColor= actualBGCol;
                }
            }

            // auto tab / end of meta
            else if ( c == 't' || c == 'A')
            {
                c=  rest.ConsumeChar();
                int extraSpace=  c >= '0' && c <= '9' ? (int)  ( c - '0' )
                                                      : (int)  ( c - 'A' ) + 10;

                int tabStop= AutoSizes.Next( column, extraSpace );

                Spaces.Write( Console.Out, tabStop - column );
                column= tabStop;
            }

            // Link (we just colorize links here)
            else if ( c == 'l' )
            {
                if ( rest.ConsumeChar() == 'S' )
                    Console.ForegroundColor=  (UseLightColors != LightColorUsage.ForegroundLight) ? ConsoleColor.DarkBlue
                                                                                                  : ConsoleColor.Blue;
                else
                    Console.ForegroundColor=  actualFGCol;
            }

            else
            {
                ALIB_DBG.WARNING( "Unknown ESC code" );
            }

        } // write loop

        // reset colors
        Console.ForegroundColor= actualFGCol;
        Console.BackgroundColor= actualBGCol;

        // write NL
        #if !(ALOX_WP71 || ALOX_WP8)
            Console.WriteLine();
        #else
            Console.WriteLine();
        #endif

    }

    /** ********************************************************************************************
     * Empty implementation, not needed for this class
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    override protected void notifyMultiLineOp( Phase phase )  {}

#endif // ALOX_DBG_LOG || ALOX_REL_LOG
} // class ColorConsoleLogger
} // namespace

