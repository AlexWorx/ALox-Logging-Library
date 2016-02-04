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
using cs.aworx.lox.core;
using cs.aworx.lib.enums;


namespace cs.aworx.lox.loggers    {


/** ************************************************************************************************
 *  A logger that logs all messages to the System.IO.TextWriter instance provided in the constructor.
 *  The name of the logger defaults to "ANSI_LOGGER".
 *
 *  ALox text logger escape sequences (see class \ref cs::aworx::lox::ESC "ESC")
 *  are translated to ANSI escape sequences.
 *  Support for ANSI escape sequences (also referred to as <em>VT100 terminal emulation</em>)
 *  is available on most unix terminal windows. Besides text colors, bold and italics font style
 *  can be set.
 *  ANSI escape sequences are also available in various IDE output windows.
 *
 *  Foreground and background colors are set to be either light/dark or dark/light. This improves
 *  the readability of log output a lot. However, the right setting for this is dependent on
 *  the color scheme of final output device (window). To manipulate the right setting, see field
 *  #IsBackgroundLight.
 *
 *  In the constructor, a default format string and some other definitions in member
 *  \ref MetaInfo get set to include ANSI Escape Sequences. Of-course, these publicly
 *  accessible format attributes can be customized after creation.
 *
 *  There is not 100% match between the ANSI sequences and the definitions in
 *  \ref aworx::lox::ESC "ESC".
 *  For example ESC does not provide all ANSI colors and no blinking. On the other hand,
 *  ANSI does not allow to reset the style without resetting the colors.
 *  Of-course, it is no problem to log other ANSI codes directly into a %AnsiLogger.
 *  In this case, other Loggers that might be attached to the same Lox and that do not
 *  support ANSI must be equipped with corresponding replacement information.
 *  In other words: To support the same log output into different loggers, it is
 *  recommended to use \ref aworx::lox::ESC "ESC"  sequences instead of
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
    // Fields
    // #############################################################################################

        /**
         * Forground and background colors chosen by AnsiLogger differ in their intensity to increase
         * the overall readablity by increasing the contrast.
         * If the background color of an ANSI console window is dark, then the background colors of
         * colored log output should be darker colors than the forground colors and vice versa.
         *
         * If this field is false, foreground colors will be light colors and background colors dark.
         * If true, the opposite is chosen.
         *
         * Defaults to false.
         *
         * Configuration variable [ALOX_CL_LIGHT_BACKGROUND](../group__GrpALoxConfigVars.html)
         * is evaluated within the constructor of this class, to allow to modifying this flag at
         * runtime.
         */
        public      bool                        IsBackgroundLight;

        /**
         * The TextWriter provided in the constructor.
         */
        protected   System.IO.TextWriter        textWriter;

        /** Characters  placed at the beginning of a log line with level 'Error'.*/
        public      String                      MsgPrefixError;

        /** Characters  placed at the beginning of a log line with level 'Warning'.*/
        public      String                      MsgPrefixWarning;

        /** Characters  placed at the beginning of a log line with level 'Info'.*/
        public      String                      MsgPrefixInfo            = "";

        /** Characters  placed at the beginning of a log line with level 'Verbose'.*/
        public      String                      MsgPrefixVerbose;

        /** Characters  placed at the end of each line (e.g. used to reset colors and styles).*/
        public      String                      MsgPostfix               = ANSI_RESET;


    // #############################################################################################
    // Constructor
    // #############################################################################################

        /** ****************************************************************************************
         * Creates an AnsiLogger.
         * @param textWriter  The TextWriter object to write into.
         * @param name        (Optional) The name of the logger, defaults to "ANSI".
         ******************************************************************************************/
        public AnsiLogger( System.IO.TextWriter textWriter, String name= null )
            : base( name, "ANSI" )
        {
            this.textWriter= textWriter;

            // evaluate environment variable "ALOX_CL_LIGHT_BACKGROUND"
            int  configVarSet= 0;
            bool configVarTrue= ALIB.Config.IsTrue( Log.ConfigCategoryName, "CL_LIGHT_BACKGROUND", ref configVarSet );
            if( configVarSet != 0 )
                IsBackgroundLight=  configVarTrue;
            else
            {
                // on ANSI terminals we can only guess. Our guess is: console windows have dark background
                IsBackgroundLight= false;
            }

            // remove level information and colorize the whole line
            MetaInfo.Format.SearchAndReplace( " %L ", " " );
            if ( IsBackgroundLight )
            {
                MsgPrefixError           = ANSI_RED;
                MsgPrefixWarning         = ANSI_BLUE;
                MsgPrefixVerbose         = ANSI_GRAY;
            }
            else
            {
                MsgPrefixError           = ANSI_LIGHT_RED;
                MsgPrefixWarning         = ANSI_LIGHT_BLUE;
                MsgPrefixVerbose         = ANSI_LIGHT_GRAY;
            }

            // set source file background to gray
            AString ansiBGGray= new AString( ESC.BG_GRAY ); ansiBGGray._( "%CF(%CL):" )._( ANSI_BG_STD_COL );
            MetaInfo.Format.SearchAndReplace( "%CF(%CL):", ansiBGGray.ToString() );
        }

    // #############################################################################################
    // doTextLog
    // #############################################################################################

    /** ********************************************************************************************
     *
     *  The implementation of the abstract method of parent class TextLogger. Logs messages to the
     *  application console and/or the VStudio output window.
     *
     * @param domain      The log domain name. </param>
     * @param level       The log level. This has been checked to be active already on this
     *                           stage and is provided to be able to be logged out only. </param>
     * @param msg         The log message. </param>
     * @param indent      the indentation in the output. Defaults to 0. </param>
     * @param caller      Once compiler generated and passed forward to here. </param>
     * @param lineNumber  The line number of a multi-line message, starting with 0. For
     *                           single line messages this is -1. </param>
     **********************************************************************************************/
    override protected void doTextLog(  AString        domain,     Log.Level     level,
                                        AString        msg,        int            indent,
                                        CallerInfo     caller,     int            lineNumber)
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
                    ALIB.WARNING( "Unknown ANSI ESC Code " );
                    textWriter.Write( actual.Buf, actual.Start, actual.Length() );
                    continue;
                }

                column+= actual.Length();

                actual.End= rest.Start + idx ;
                rest.Start+= idx + 1;

                textWriter.Write( actual.Buf, actual.Start, actual.Length() );

                continue;
            }
            else
            {
                if ( actual.IsNotEmpty() )
                {
                    textWriter.Write( actual.Buf, actual.Start, actual.Length() );
                    column+= actual.Length();
               }
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

                // add bg
                colNo+=  isForeGround ? 0 : 10;

                // add light
                colNo+=  (isForeGround ? !IsBackgroundLight : IsBackgroundLight )  ? 20 : 0;

                textWriter.Write( ansiCols[ colNo ] );

            }

            // Styles
            else if ( c == 's' )
            {
                // bold/italics style not supported in Windows console

                // reset all
                if ( rest.Consume() == 'a' )
                {
                    textWriter.Write( ANSI_RESET );
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

                Util.WriteSpaces( textWriter, tabStop - column );
                column= tabStop;

                if ( endOfMeta )
                {
                    String msgPrefix;
                    switch ( level )
                    {
                        case Log.Level.Verbose:   msgPrefix= MsgPrefixVerbose;     break;
                        case Log.Level.Info:      msgPrefix= MsgPrefixInfo;        break;
                        case Log.Level.Warning:   msgPrefix= MsgPrefixWarning;     break;
                        case Log.Level.Error:     msgPrefix= MsgPrefixError;       break;
                        default:                  msgPrefix= "";                   break;
                    }
                    textWriter.Write( msgPrefix );
                }
            }

            // Link (we just colorize links here)
            else if ( c == 'l' )
            {
                textWriter.Write( rest.Consume() == 'S'
                                       ?  ( IsBackgroundLight ? ANSI_LIGHT_BLUE : ANSI_LIGHT_BLUE )
                                       :  ANSI_STD_COL                             );
            }

            else
            {
                ALIB.WARNING( "Unknown ESC code" );
            }

        } // write loop


        textWriter.WriteLine( MsgPostfix );
    }

    /** ********************************************************************************************
     * Empty implementation, not needed for this class
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    override protected void notifyMultiLineOp (Phase phase)
    {
    }

    #endif // ALOX_DBG_LOG || ALOX_REL_LOG
} // class AnsiLogger



// #############################################################################################
// class AnsiConsoleLogger
// #############################################################################################


/** ************************************************************************************************
 *  A #AnsiLogger that logs all messages to the TextWrite object found in field
 *  <em>Console.Out</em>. by providing this field to the constructor of its parent
 *  class %AnsiLogger.
 *  See class #AnsiLogger for more information on ANSI escape sequences and their use.
 *
 *  The name of the logger defaults to "ANSI_CONSOLE".
 *
 *  \note Due to the fact that mono libraries under Linux do not support light colors (they
 *  can be used, but they are equal to the dark colors), this logger is preferred over
 *  \ref cs.aworx.lox.loggers.ConsoleLogger "ConsoleLogger" when running ALox under Linux.
 *  The readability of colorful output is better if light foreground colors are used on
 *  console windows with dark background (and vice versa).
 *
 *  \note While this class does not use class Console to colorize the output, within the
 *  constructor, class Console is still used to identify whether the background of the console
 *  attached to the current process has a dark or light background.
 *
 *  \note For the ease of use, class \ref aworx::lox::Log "Log" implements a method
 *  \ref cs.aworx::lox::Log::AddDebugLogger "Log.AddDebugLogger"
 *  that tries to create the right Logger type for standard debug logging (potentially this one),
 *  depending on the platform, IDE and optional configuration settings.
 *
 *  While by default, the
 *  \ref cs.aworx::lox::Log::DomainLevel "DomainLevel"
 *  of root domains of loggers are set to 'Off', the constructor of this class sets this value
 *  to 'All'. This way, all log invocations on 'unknown' domains (those that have not been
 *  registered and explicitly set) are fully enabled by default.
 *  This is done because this class typically represents a logger that used for debug logging,
 *  e.g. logging into the developer's IDE. Such loggers should detect all messages of any log domain
 *  that the application and its library uses - unless those are explicitly set differently in
 *  the bootstrap code of the application.
 *
 *  \note This class can not enable the output console (which receives ALox
 *  log data) to support ANSI Escape Codes. The opposite is right: this class should be used only if
 *  the console supports ANSI Escape Codes.
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
     * @param name        (Optional) The name of the logger, defaults to "ANSI_CONSOLE".
     **********************************************************************************************/
    public AnsiConsoleLogger( String name= "ANSI_CONSOLE" )
    : base( Console.Out, name )
    {
        // fix type name
        TypeName= "ANSI_CONSOLE";

        // set default domain level to all: As an app console logger/IDE logger we want to
        // fetch all we can
        RootDomain.SetLevel( Log.DomainLevel.All, Propagation.None );

        // evaluate environment variable "ALOX_CL_LIGHT_BACKGROUND"
        int  configVarSet= 0;
        bool configVarTrue= ALIB.Config.IsTrue( Log.ConfigCategoryName, "CL_LIGHT_BACKGROUND", ref configVarSet );
        if( configVarSet != 0 )
            IsBackgroundLight=  configVarTrue;
        else
        {
            ConsoleColor fgCol= Console.ForegroundColor;
            IsBackgroundLight=      fgCol == ConsoleColor.Black
                                ||  fgCol == ConsoleColor.DarkBlue
                                ||  fgCol == ConsoleColor.DarkCyan
                                ||  fgCol == ConsoleColor.DarkGray
                                ||  fgCol == ConsoleColor.DarkGreen
                                ||  fgCol == ConsoleColor.DarkMagenta
                                ||  fgCol == ConsoleColor.DarkRed
                                ||  fgCol == ConsoleColor.DarkYellow   ;
        }
    }



    #endif // ALOX_DBG_LOG || ALOX_REL_LOG
} // class AnsiConsoleLogger

} // namespace

