﻿// #################################################################################################
//  cs.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Runtime.CompilerServices;
using cs.aworx.lox.detail.textlogger;
using cs.aworx.lib;
using cs.aworx.lib.strings;
using cs.aworx.lib.strings.util;
using cs.aworx.lox.detail;
using cs.aworx.lib.lang;
using cs.aworx.lib.config;


namespace cs.aworx.lox.loggers    {

/** ************************************************************************************************
 * A logger that logs all messages to the <em>System.IO.TextWriter</em> instance provided in the
 * constructor. The name of the \e Logger defaults to "ANSI_LOGGER".
 *
 * \b %ALox text logger escape sequences (see class \ref cs.aworx.lox.ESC "ESC")
 * are translated to ANSI escape sequences.
 * Support for ANSI escape sequences (also referred to as <em>VT100 terminal emulation</em>)
 * is available on most unix terminal windows. Besides text colors, bold and italics font style
 * can be set.
 * ANSI escape sequences are also available in various IDE output windows.
 *
 * Foreground and background colors can be set to be either light/dark or dark/light. This improves
 * the readability of log output a lot and even allows to read if foreground and background colors
 * are the same (they then still differ). However, the right setting for this is dependent on
 * the color scheme of the final output device (window). To manipulate the right setting, see field
 * #UseLightColors and also configuration variable
 * [ALOX_CONSOLE_LIGHT_COLORS](../group__GrpALoxConfigVars.html).
 *
 * In the constructor, a default format string and some other definitions in member
 * \ref MetaInfo get set to include color settings.
 * Of-course, these publicly accessible format attributes can be customized after creation.
 *
 *  There is not 100% match between the ANSI sequences and the definitions in
 *  \ref cs.aworx.lox.ESC "ESC".
 *  For example ESC does not provide all ANSI colors and no blinking. On the other hand,
 *  ANSI does not allow to reset the style without resetting the colors.
 *  Of-course, it is no problem to log other ANSI codes directly into an \b %AnsiLogger.
 *  In this case, other Loggers that might be attached to the same Lox and that do not
 *  support ANSI must be equipped with corresponding replacement information.
 *  In other words: To support the same log output into different loggers, it is
 *  recommended to use \ref cs.aworx.lox.ESC "ESC"  sequences instead of
 *  directly using ANSI codes.
 *
 *  The ANSI codes used by this class are exposed through a list of fields.
 *  They might be useful for manipulating the attributes of the \ref MetaInfo
 *  member, which of-course might contain native ANSI sequences.
 *  (In contrast to the log messages themselves, this meta information is specific to a logger
 *  instance and this way it does not need to be replaced in other loggers).
 **************************************************************************************************/
public class AnsiLogger : TextLogger
{
    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DBG_LOG || ALOX_REL_LOG)
        public AnsiLogger( System.IO.TextWriter textWriter, String name= "CONSOLE" ){}
    #else

    // #############################################################################################
    // ANSI Escape Code definitions
    // #############################################################################################

        public static readonly String  ANSI_RED              ="\x001B[31m"      ; ///< Select red as foreground color
        public static readonly String  ANSI_GREEN            ="\x001B[32m"      ; ///< Select green as foreground color
        public static readonly String  ANSI_YELLOW           ="\x001B[33m"      ; ///< Select yellow as foreground color
        public static readonly String  ANSI_BLUE             ="\x001B[34m"      ; ///< Select blue as foreground color
        public static readonly String  ANSI_MAGENTA          ="\x001B[35m"      ; ///< Select magenta as foreground color
        public static readonly String  ANSI_CYAN             ="\x001B[36m"      ; ///< Select cyan as foreground color
        public static readonly String  ANSI_BLACK            ="\x001B[30m"      ; ///< Select black as foreground color
        public static readonly String  ANSI_WHITE            ="\x001B[38;5;15m" ; ///< Select white as foreground color
        public static readonly String  ANSI_GRAY             ="\x001B[38;5;240m"; ///< Select gray as foreground color
        public static readonly String  ANSI_STD_COL          ="\x001B[39m"      ; ///< Select standard foreground color

        public static readonly String  ANSI_BG_RED           ="\x001B[41m"      ; ///< Select red as background color
        public static readonly String  ANSI_BG_GREEN         ="\x001B[42m"      ; ///< Select green as background color
        public static readonly String  ANSI_BG_YELLOW        ="\x001B[43m"      ; ///< Select yellow as background color
        public static readonly String  ANSI_BG_BLUE          ="\x001B[44m"      ; ///< Select blue as background color
        public static readonly String  ANSI_BG_MAGENTA       ="\x001B[45m"      ; ///< Select magenta as background color
        public static readonly String  ANSI_BG_CYAN          ="\x001B[46m"      ; ///< Select cyan as background color
        public static readonly String  ANSI_BG_BLACK         ="\x001B[40m"      ; ///< Select black as background color
        public static readonly String  ANSI_BG_WHITE         ="\x001B[48;5;15m" ; ///< Select white as background color
        public static readonly String  ANSI_BG_GRAY          ="\x001B[48;5;240m"; ///< Select gray as background color
        public static readonly String  ANSI_BG_STD_COL       ="\x001B[49m"      ; ///< Select standard background color

        public static readonly String  ANSI_LIGHT_RED        ="\x001B[38;5;09m" ; ///< Select light red as foreground color
        public static readonly String  ANSI_LIGHT_GREEN      ="\x001B[38;5;10m" ; ///< Select light green as foreground color
        public static readonly String  ANSI_LIGHT_YELLOW     ="\x001B[38;5;11m" ; ///< Select light yellow as foreground color
        public static readonly String  ANSI_LIGHT_BLUE       ="\x001B[38;5;12m" ; ///< Select light blue as foreground color
        public static readonly String  ANSI_LIGHT_MAGENTA    ="\x001B[38;5;13m" ; ///< Select light magenta as foreground color
        public static readonly String  ANSI_LIGHT_CYAN       ="\x001B[38;5;14m" ; ///< Select light cyan as foreground color
        public static readonly String  ANSI_LIGHT_GRAY       ="\x001B[38;5;250m"; ///< Select light gray as foreground color

        public static readonly String  ANSI_BG_LIGHT_RED     ="\x001B[48;5;09m" ; ///< Select light red as background color
        public static readonly String  ANSI_BG_LIGHT_GREEN   ="\x001B[48;5;10m" ; ///< Select light green as background color
        public static readonly String  ANSI_BG_LIGHT_YELLOW  ="\x001B[48;5;11m" ; ///< Select light yellow as background color
        public static readonly String  ANSI_BG_LIGHT_BLUE    ="\x001B[48;5;12m" ; ///< Select light blue as background color
        public static readonly String  ANSI_BG_LIGHT_MAGENTA ="\x001B[48;5;13m" ; ///< Select light magenta as background color
        public static readonly String  ANSI_BG_LIGHT_CYAN    ="\x001B[48;5;14m" ; ///< Select light cyan as background color
        public static readonly String  ANSI_BG_LIGHT_GRAY    ="\x001B[48;5;250m"; ///< Select light gray as background color

        public static readonly String  ANSI_BOLD             ="\x001B[1m"       ; ///< Select bold font style
        public static readonly String  ANSI_ITALICS          ="\x001B[3m"       ; ///< Select italics font style
        public static readonly String  ANSI_STD_STYLE        ="\x001B[0m"       ; ///< Select standard font style

        public static readonly String  ANSI_RESET            ="\x001B[0m"       ; ///< Reset colors and font style

        /** Internal table used to convert ESC colors to ANSI colors  */
        protected String[] ansiCols=
        {
            ANSI_RED,           ANSI_GREEN,         ANSI_YELLOW,           ANSI_BLUE,          ANSI_MAGENTA,
            ANSI_CYAN,          ANSI_BLACK,         ANSI_WHITE,            ANSI_GRAY,          ANSI_STD_COL,

            ANSI_BG_RED,        ANSI_BG_GREEN,      ANSI_BG_YELLOW,        ANSI_BG_BLUE,       ANSI_BG_MAGENTA,
            ANSI_BG_CYAN,       ANSI_BG_BLACK,      ANSI_BG_WHITE,         ANSI_BG_GRAY,       ANSI_BG_STD_COL,

            ANSI_LIGHT_RED,     ANSI_LIGHT_GREEN,   ANSI_LIGHT_YELLOW,     ANSI_LIGHT_BLUE,    ANSI_LIGHT_MAGENTA,
            ANSI_LIGHT_CYAN,    ANSI_BG_BLACK,      ANSI_BG_WHITE,         ANSI_LIGHT_GRAY,    ANSI_STD_COL,

            ANSI_BG_LIGHT_RED,  ANSI_BG_LIGHT_GREEN,ANSI_BG_LIGHT_YELLOW,  ANSI_BG_LIGHT_BLUE, ANSI_BG_LIGHT_MAGENTA,
            ANSI_BG_LIGHT_CYAN, ANSI_BG_BLACK,      ANSI_BG_WHITE,         ANSI_BG_LIGHT_GRAY, ANSI_BG_STD_COL
        };

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /**
         * The TextWriter provided in the constructor.
         */
        protected   System.IO.TextWriter        textWriter;

    // #############################################################################################
    // Public fields
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
        public      LightColorUsage             UseLightColors;

    // #############################################################################################
    // Constructor
    // #############################################################################################

        /** ****************************************************************************************
         * Creates an AnsiLogger.
         * @param textWriter     The TextWriter object to write into.
         * @param usesStdStreams Denotes whether this logger writes to the
         *                       <em>standard output streams</em>.
         * @param name           The name of the \e Logger, defaults to what is provided with
         *                       parameter \p{typeName}.
         * @param typeName       The type of the \e Logger, defaults to "ANSI".
         ******************************************************************************************/
        public AnsiLogger( System.IO.TextWriter textWriter, bool usesStdStreams,
                           String name= null, String typeName= "ANSI" )
            : base( name, typeName, usesStdStreams )
        {
            this.textWriter= textWriter;

            // set msg suffix to "reset"
            FmtMsgSuffix= ANSI_RESET;

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
                UseLightColors= LightColorUsage.ForegroundLight;
            }

            // move verbosity information to the end to colorize the whole line
            MetaInfo.Format.SearchAndReplace( "]%V[", "][" );
            MetaInfo.Format._( "%V" );
            MetaInfo.VerbosityError           = ESC.RED;
            MetaInfo.VerbosityWarning         = ESC.BLUE;
            MetaInfo.VerbosityInfo            = "";
            MetaInfo.VerbosityVerbose         = ESC.GRAY;
        }

    // #############################################################################################
    // logText
    // #############################################################################################

    /** ********************************************************************************************
     * Implementation of the abstract method of parent class TextLogger. Logs messages to the
     * application console and/or the VStudio output window.
     *
     * @param domain      The <em>Log Domain</em>.
     * @param verbosity   The verbosity. This has been checked to be active already on this
     *                    stage and is provided to be able to be logged out only.
     * @param msg         The log message
     * @param scope       Information about the scope of the <em>Log Statement</em>..
     * @param lineNumber  The line number of a multi-line message, starting with 0. For
     *                    single line messages this is -1.
     **********************************************************************************************/
    override protected void logText(  Domain         domain,     Verbosity verbosity,
                                        AString        msg,
                                        ScopeInfo      scope,      int           lineNumber)
    {
        // loop over message, print the parts between the escape sequences
        Tokenizer msgParts= new Tokenizer( msg, '\x001B' );
        Substring actual=   msgParts.Actual;
        Substring rest=     msgParts.Rest;
        int       column=   0;
        for(;;)
        {
            msgParts.Next( Whitespaces.Keep );

            // check if this is an ANSI sequence already
            if ( rest.CharAtStart() == '[' )
            {
                // read the 'm'
                int idx= rest.IndexOf( 'm' );

                if ( idx < 0 ) // unknown ANSI Code
                {
                    ALIB_DBG.WARNING( "Unknown ANSI ESC Code " );
                    textWriter.Write( actual.Buf, actual.Start, actual.Length() );
                    continue;
                }

                column+= actual.Length();

                actual.End= rest.Start + idx ;
                rest.Start+= idx + 1;

                textWriter.Write( actual.Buf, actual.Start, actual.Length() );

                continue;
            }

            if ( actual.IsNotEmpty() )
            {
                textWriter.Write( actual.Buf, actual.Start, actual.Length() );
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

                // add bg
                colNo+=  isForeGround ? 0 : 10;

                // add light
                if(       UseLightColors != LightColorUsage.Never
                    && ( (UseLightColors == LightColorUsage.ForegroundLight) == isForeGround )   )
                    colNo+= 20;

                textWriter.Write( ansiCols[ colNo ] );

            }

            // Styles
            else if ( c == 's' )
            {
                c=  rest.ConsumeChar();
                textWriter.Write(   c == 'B' ? ANSI_BOLD
                                  : c == 'I' ? ANSI_ITALICS
                                  :            ANSI_RESET    );
            }

            // auto tab / end of meta
            else if ( c == 't' || c == 'A')
            {
                c=  rest.ConsumeChar();
                int extraSpace=  c >= '0' && c <= '9' ? (int)  ( c - '0' )
                                                      : (int)  ( c - 'A' ) + 10;

                int tabStop= AutoSizes.Next( AutoSizes.Types.Tabstop, column, extraSpace );

                Spaces.Write( textWriter, tabStop - column );
                column= tabStop;
            }

            // Link (we just colorize links here)
            else if ( c == 'l' )
            {
                textWriter.Write( rest.ConsumeChar() == 'S'
                                       ?  ( UseLightColors == LightColorUsage.ForegroundLight ? ANSI_LIGHT_BLUE : ANSI_BLUE )
                                       :  ANSI_STD_COL                             );
            }

            else
            {
                ALIB_DBG.WARNING( "Unknown ESC code" );
            }

        } // write loop


        textWriter.WriteLine();
    }

    /** ****************************************************************************************
     * Empty implementation.
     *
     * @param phase The phase of the multi-line operation (ignored).
     ******************************************************************************************/
    override protected void notifyMultiLineOp (Phase phase)
    {
    }

    #endif // ALOX_DBG_LOG || ALOX_REL_LOG
} // class AnsiLogger



// #############################################################################################
// class AnsiConsoleLogger
// #############################################################################################


/** ************************************************************************************************
 * A #AnsiLogger that logs all messages to the TextWrite object found in field
 * <em>Console.Out</em>. by providing this field to the constructor of its parent
 * class %AnsiLogger.
 * See class #AnsiLogger for more information on ANSI escape sequences and their use.
 *
 * The name of the \e Logger defaults to "ANSI_CONSOLE".
 *
 * \note Due to the fact that mono libraries under Linux do not support light colors (they
 * can be used, but they are equal to the dark colors), this logger is preferred over
 * \ref cs.aworx.lox.loggers.ConsoleLogger "ConsoleLogger" when running \b %ALox under Linux.
 * The readability of colorful output is better if light foreground colors are used on
 * console windows with dark background (and vice versa).
 *
 * \note While this class does not use class Console to colorize the output, within the
 * constructor, class Console is still used to identify whether the background of the console
 * attached to the current process has a dark or light background.
 *
 * \note This class can not enable the output console (which receives \b %ALox
 * log data) to support ANSI Escape Codes. The opposite is right: this class should be used only if
 * the console supports ANSI Escape Codes.
 **************************************************************************************************/

public class AnsiConsoleLogger : AnsiLogger
{
    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DBG_LOG || ALOX_REL_LOG)
        public AnsiConsoleLogger( String name= "CONSOLE" ) : base( null, name ){}
    #else
    /** ********************************************************************************************
     * Creates an AnsiConsoleLogger.
     * @param name        (Optional) The name of the \e Logger, defaults to "ANSI_CONSOLE".
     **********************************************************************************************/
    public AnsiConsoleLogger( String name= null )
    : base( Console.Out, true, name, "ANSI_CONSOLE" )
    {
    }

    #endif // ALOX_DBG_LOG || ALOX_REL_LOG
} // class AnsiConsoleLogger

} // namespace

