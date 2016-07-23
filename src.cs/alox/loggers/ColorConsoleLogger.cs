// #################################################################################################
//  cs.aworx.lox.loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Runtime.CompilerServices;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib;
using cs.aworx.lib.strings;


/** ************************************************************************************************
 *  This is the C# namespace for the implementation of <em>logger classes</em> that are provided
 *  by default with <em>%ALox Logging Library</em>.
 *
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
using cs.aworx.lox.core;
using cs.aworx.lib.enums;
using cs.aworx.lib.config;


namespace cs.aworx.lox.loggers    {


/** ************************************************************************************************
 * A logger that logs all messages using the .Net class <em>System.Console</em>. Converts color
 * sequences defined in class
 * \ref cs::aworx::lox::ESC "ESC"
 * that are found within the log messages (and meta info format strings) to a corresponding
 * color setting of class <em>System.Console</em>.
 *
 * Foreground and background colors are set to be either light/dark or dark/light. This improves
 * the readability of log output a lot. However, the right setting for this is dependent on
 * the color scheme of final output device (window). To manipulate the right setting, see field
 * #IsBackgroundLight and also configuration variable
 * [ALOX_CONSOLE_HAS_LIGHT_BACKGROUND](../group__GrpALoxConfigVars.html).
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

        /**
         * Forground and background colors chosen by this class differ in their intensity to increase
         * the overall readablity by increasing the contrast.
         * If the background color of a console window is dark, then the background colors of
         * colored log output should be darker colors than the forground colors and vice versa.
         *
         * If this field is false, foreground colors will be light colors and background colors dark.
         * If true, the opposite is chosen.
         *
         * Defaults to false.
         *
         * The configuration variable [ALOX_CONSOLE_HAS_LIGHT_BACKGROUND](../group__GrpALoxConfigVars.html)
         * is evaluated within the constructor of this class, to allow to modifying this flag at
         * runtime.
         */

        public      bool                    IsBackgroundLight;

        /** Color of a log line with \e Verbosity 'Error'.*/
        public      ConsoleColor            MsgColorError;

        /** Color of a log line with \e Verbosity 'Warning'.*/
        public      ConsoleColor            MsgColorWarning;

        /** Color of a log line with \e Verbosity 'Info'.*/
        public      ConsoleColor            MsgColorInfo;

        /** Color of a log line with \e Verbosity 'Verbose'.*/
        public      ConsoleColor            MsgColorVerbose;

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

        // evaluate environment variable "ALOX_CONSOLE_HAS_LIGHT_BACKGROUND"
        Variable variable= new Variable( ALox.CONSOLE_HAS_LIGHT_BACKGROUND );
        variable.Load();
        if ( variable.Size() > 0 )
            IsBackgroundLight=  variable.IsTrue();
        else
        {
            IsBackgroundLight=      fgCol == ConsoleColor.Black
                                ||  fgCol == ConsoleColor.DarkBlue
                                ||  fgCol == ConsoleColor.DarkCyan
                                ||  fgCol == ConsoleColor.DarkGray
                                ||  fgCol == ConsoleColor.DarkGreen
                                ||  fgCol == ConsoleColor.DarkMagenta
                                ||  fgCol == ConsoleColor.DarkRed
                                ||  fgCol == ConsoleColor.DarkYellow   ;
        }


        // remove verbosity information and colorize the whole line
        MetaInfo.Format.SearchAndReplace( " %V ", " " );
        MsgColorInfo          = fgCol;
        if ( IsBackgroundLight )
        {
            MsgColorError           = ConsoleColor.DarkRed;
            MsgColorWarning         = ConsoleColor.DarkBlue;
            MsgColorVerbose         = ConsoleColor.DarkGray;
        }
        else
        {
            MsgColorError           = ConsoleColor.Red;
            MsgColorWarning         = ConsoleColor.Blue;
            MsgColorVerbose         = ConsoleColor.Gray;
        }
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
            char c= rest.Consume();

            // Colors
            bool isForeGround=  true;
            if( c == 'C' || c == 'c' )
            {
                isForeGround=  c== 'c';

                c= rest.Consume();
                int colNo= c - '0';
                ALIB.ASSERT_WARNING( colNo >=0 && colNo <=9, "Unknown ESC-c code" );


                // set color
                if( colNo >= 0 && colNo <= 8 || colNo == 8)
                {
                    ConsoleColor[] cols=  (isForeGround ? !IsBackgroundLight : IsBackgroundLight )  ? lightColors : darkColors;
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
                    ALIB.WARNING( "Unknown ESC- code" );
                }

            }

            // Styles
            else if ( c == 's' )
            {
                // bold/italics style not supported in Windows console

                // reset all
                if ( rest.Consume() == 'a' )
                {
                    Console.ForegroundColor= actualFGCol;
                    Console.BackgroundColor= actualBGCol;
                }
            }

            // auto tab / end of meta
            else if ( c == 't' || c == 'A')
            {
                bool endOfMeta= c == 'A';
                c=  rest.Consume();
                int extraSpace=  c >= '0' && c <= '9' ? (int)  ( c - '0' )
                                                      : (int)  ( c - 'A' ) + 10;

                int tabStop= AutoSizes.Next( column, extraSpace );

                Util.WriteSpaces( Console.Out, tabStop - column );
                column= tabStop;

                if ( endOfMeta )
                {
                    switch ( verbosity )
                    {
                        case Verbosity.Verbose:   Console.ForegroundColor= MsgColorVerbose;     break;
                        case Verbosity.Info:      Console.ForegroundColor= MsgColorInfo;        break;
                        case Verbosity.Warning:   Console.ForegroundColor= MsgColorWarning;     break;
                        case Verbosity.Error:     Console.ForegroundColor= MsgColorError;       break;
                        default:                  break;
                    }
                }
            }

            // Link (we just colorize links here)
            else if ( c == 'l' )
            {
                if ( rest.Consume() == 'S' )
                    Console.ForegroundColor=  IsBackgroundLight ? ConsoleColor.DarkBlue : ConsoleColor.Blue;
                else
                    Console.ForegroundColor=  actualFGCol;
            }

            else
            {
                ALIB.WARNING( "Unknown ESC code" );
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

