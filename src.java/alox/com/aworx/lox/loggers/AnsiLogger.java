// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.lox.loggers;

import java.io.PrintStream;

import com.aworx.lib.*;
import com.aworx.lib.enums.Phase;
import com.aworx.lib.enums.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.Tokenizer;
import com.aworx.lox.ESC;
import com.aworx.lox.Log;
import com.aworx.lox.core.CallerInfo;
import com.aworx.lox.core.textlogger.TextLogger;

/** ************************************************************************************************
 *  A logger that logs all messages to the System.IO.TextWriter instance provided in the constructor.
 *  The name of the logger defaults to "ANSI_LOGGER".
 *
 *  ALox text logger escape sequences (see class \ref aworx::lox::ESC "ESC")
 *  are translated to ANSI escape sequences.
 *  Support for ANSI escape sequences (also referred to as <em>VT100 terminal emulation</em>)
 *  is available on most unix terminal windows. Besides text colors, bold and italics font style
 *  can be set.
 *  ANSI escape sequences are also available in various IDE output windows.
 *
 *  Foreground and background colors are set to be either light/dark or dark/light. This improves
 *  the readability of log output a lot. However, the right setting for this is dependent on
 *  the color scheme of final output device (window). To manipulate the right setting, see field
 *  #isBackgroundLight.
 *
 *  In the constructor, a default format string and some other definitions in member
 *  \ref metaInfo get set to include ANSI Escape Sequences. Of-course, these publicly
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
 *  They might be useful for manipulating the attributes of the \ref metaInfo
 *  member, which of-course might contain native ANSI sequences.
 *  (In contrast to the log messages themselves, this meta information is specific to a logger
 *  instance and this way it does not need to be replaced in other loggers).
 **************************************************************************************************/
public class AnsiLogger extends TextLogger
{
    // #############################################################################################
    // ANSI Escape Code definitions
    // #############################################################################################

        public static final String  ANSI_RED              ="\033[31m"      ; ///< Select red as foreground color
        public static final String  ANSI_GREEN            ="\033[32m"      ; ///< Select green as foreground color
        public static final String  ANSI_YELLOW           ="\033[33m"      ; ///< Select yellow as foreground color
        public static final String  ANSI_BLUE             ="\033[34m"      ; ///< Select blue as foreground color
        public static final String  ANSI_MAGENTA          ="\033[35m"      ; ///< Select magenta as foreground color
        public static final String  ANSI_CYAN             ="\033[36m"      ; ///< Select cyan as foreground color
        public static final String  ANSI_BLACK            ="\033[30m"      ; ///< Select black as foreground color
        public static final String  ANSI_WHITE            ="\033[38;5;15m" ; ///< Select white as foreground color
        public static final String  ANSI_GRAY             ="\033[38;5;240m"; ///< Select gray as foreground color
        public static final String  ANSI_STD_COL          ="\033[39m"      ; ///< Select standard foreground color

        public static final String  ANSI_BG_RED           ="\033[41m"      ; ///< Select red as background color
        public static final String  ANSI_BG_GREEN         ="\033[42m"      ; ///< Select green as background color
        public static final String  ANSI_BG_YELLOW        ="\033[43m"      ; ///< Select yellow as background color
        public static final String  ANSI_BG_BLUE          ="\033[44m"      ; ///< Select blue as background color
        public static final String  ANSI_BG_MAGENTA       ="\033[45m"      ; ///< Select magenta as background color
        public static final String  ANSI_BG_CYAN          ="\033[46m"      ; ///< Select cyan as background color
        public static final String  ANSI_BG_BLACK         ="\033[40m"      ; ///< Select black as background color
        public static final String  ANSI_BG_WHITE         ="\033[48;5;15m" ; ///< Select white as background color
        public static final String  ANSI_BG_GRAY          ="\033[48;5;240m"; ///< Select gray as background color
        public static final String  ANSI_BG_STD_COL       ="\033[49m"      ; ///< Select standard background color

        public static final String  ANSI_LIGHT_RED        ="\033[38;5;09m" ; ///< Select light red as foreground color
        public static final String  ANSI_LIGHT_GREEN      ="\033[38;5;10m" ; ///< Select light green as foreground color
        public static final String  ANSI_LIGHT_YELLOW     ="\033[38;5;11m" ; ///< Select light yellow as foreground color
        public static final String  ANSI_LIGHT_BLUE       ="\033[38;5;12m" ; ///< Select light blue as foreground color
        public static final String  ANSI_LIGHT_MAGENTA    ="\033[38;5;13m" ; ///< Select light magenta as foreground color
        public static final String  ANSI_LIGHT_CYAN       ="\033[38;5;14m" ; ///< Select light cyan as foreground color
        public static final String  ANSI_LIGHT_GRAY       ="\033[38;5;250m"; ///< Select light gray as foreground color

        public static final String  ANSI_BG_LIGHT_RED     ="\033[48;5;09m" ; ///< Select light red as background color
        public static final String  ANSI_BG_LIGHT_GREEN   ="\033[48;5;10m" ; ///< Select light green as background color
        public static final String  ANSI_BG_LIGHT_YELLOW  ="\033[48;5;11m" ; ///< Select light yellow as background color
        public static final String  ANSI_BG_LIGHT_BLUE    ="\033[48;5;12m" ; ///< Select light blue as background color
        public static final String  ANSI_BG_LIGHT_MAGENTA ="\033[48;5;13m" ; ///< Select light magenta as background color
        public static final String  ANSI_BG_LIGHT_CYAN    ="\033[48;5;14m" ; ///< Select light cyan as background color
        public static final String  ANSI_BG_LIGHT_GRAY    ="\033[48;5;250m"; ///< Select light gray as background color

        public static final String  ANSI_BOLD             ="\033[1m"       ; ///< Select bold font style
        public static final String  ANSI_ITALICS          ="\033[3m"       ; ///< Select italics font style
        public static final String  ANSI_STD_STYLE        ="\033[0m"       ; ///< Select standard font style

        public static final String  ANSI_RESET            ="\033[0m"       ; ///< Reset colors and font style

        /** Internal table used to convert ESC colors to ANSI colors  */
        protected String[] ansiCols=
        {
            ANSI_RED,           ANSI_GREEN,          ANSI_YELLOW,           ANSI_BLUE,          ANSI_MAGENTA,           ANSI_CYAN,          ANSI_BLACK,         ANSI_WHITE,     ANSI_GRAY,          ANSI_STD_COL,

            ANSI_BG_RED,        ANSI_BG_GREEN,       ANSI_BG_YELLOW,        ANSI_BG_BLUE,       ANSI_BG_MAGENTA,        ANSI_BG_CYAN,       ANSI_BG_BLACK,      ANSI_BG_WHITE,  ANSI_BG_GRAY,       ANSI_BG_STD_COL,

            ANSI_LIGHT_RED,     ANSI_LIGHT_GREEN,    ANSI_LIGHT_YELLOW,     ANSI_LIGHT_BLUE,    ANSI_LIGHT_MAGENTA,     ANSI_LIGHT_CYAN,    ANSI_BG_BLACK,      ANSI_BG_WHITE,  ANSI_LIGHT_GRAY,    ANSI_STD_COL,

            ANSI_BG_LIGHT_RED,  ANSI_BG_LIGHT_GREEN, ANSI_BG_LIGHT_YELLOW,  ANSI_BG_LIGHT_BLUE, ANSI_BG_LIGHT_MAGENTA,  ANSI_BG_LIGHT_CYAN, ANSI_BG_BLACK,      ANSI_BG_WHITE,  ANSI_BG_LIGHT_GRAY, ANSI_BG_STD_COL

        };

    // #############################################################################################
    // Fields
    // #############################################################################################

        /**
         * Forground and background colors chosen by AnsiLogger differ in their intensity to
         * increase the overall readablity by increasing the contrast.
         * If the background color of an ANSI console window is dark, then the background colors of
         * colored log output should be darker colors than the forground colors and vice versa.
         *
         * If this field is false, foreground colors will be light colors and background colors
         * dark. If true, the opposite is chosen.
         *
         * Defaults to false.
         *
         * Configuration variable [ALOX_CL_LIGHT_BACKGROUND](../group__GrpALoxConfigVars.html)
         * is evaluated within the constructor of this class, to allow to modifying this flag at
         * runtime.
         */
        public      boolean                 isBackgroundLight;

        /**
         * The PrintStream provided in the constructor.
         */
        protected   PrintStream             out;

        /** Characters  placed at the beginning of a log line with level 'Error'.*/
        public      String                  msgPrefixError;

        /** Characters  placed at the beginning of a log line with level 'Warning'.*/
        public      String                  msgPrefixWarning;

        /** Characters  placed at the beginning of a log line with level 'Info'.*/
        public      String                  msgPrefixInfo           = "";

        /** Characters  placed at the beginning of a log line with level 'Verbose'.*/
        public      String                  msgPrefixVerbose;

        /** Characters  placed at the end of each line (e.g. used to reset colors and styles).*/
        public      String                  msgPostfix               = ANSI_RESET;


    // #############################################################################################
    // Methods
    // #############################################################################################

    /** ********************************************************************************************
     * Creates an AnsiLogger with the given PrintStream and name.
     * @param out   (Optional) A java.io.PrintStream to write the log data to.
     *               Defaults to <em>System.out</em>.
     * @param name  (Optional) The name of the logger, defaults to "ANSI".
     **********************************************************************************************/
    public    AnsiLogger( PrintStream  out, String name )
    {
        super( name, "ANSI" );
        construct( out );
    }

    /** ********************************************************************************************
     * Creates an AnsiLogger with the name "ANSI" and the given PrintStream.
     * @param out   (Optional) A java.io.PrintStream to write the log data to.
     *               Defaults to <em>System.out</em>.
     **********************************************************************************************/
    public    AnsiLogger( PrintStream  out )
    {
        super( null, "ANSI" );
        construct( out );
    }

    /** ********************************************************************************************
     * Creates an AnsiLogger with the name "ANSI" using <em>System.out</em> as PrintStream.
     **********************************************************************************************/
    public    AnsiLogger( )
    {
        super( null, "ANSI" );
        construct( System.out );
    }

    /** ********************************************************************************************
     * Helper method used by the constructors.
     * @param out   A java.io.PrintStream to write the log data to.
     **********************************************************************************************/
    protected void construct( PrintStream  out )
    {
        this.out= out;

        // evaluate environment variable "ALOX_CL_LIGHT_BACKGROUND"
        int[]  configVarSet= {0};
        boolean configVarTrue= ALIB.config.isTrue( Log.configCategoryName, "CL_LIGHT_BACKGROUND",  configVarSet );
        if( configVarSet[0] != 0 )
            isBackgroundLight=  configVarTrue;
        else
        {
            // on ANSI terminals we can only guess. Our guess is: console windows have dark background :-)
            isBackgroundLight= false; // more detection to come in future versions
        }

        //--- modify the default format attributes of the MetaInfo support colors ---

        // remove level information and colorize the whole line
        metaInfo.format.searchAndReplace( " %L ", " " );

        if ( isBackgroundLight )
        {
            msgPrefixError           = ANSI_RED;
            msgPrefixWarning         = ANSI_BLUE;
            msgPrefixVerbose         = ANSI_GRAY;
        }
        else
        {
            msgPrefixError           = ANSI_LIGHT_RED;
            msgPrefixWarning         = ANSI_LIGHT_BLUE;
            msgPrefixVerbose         = ANSI_LIGHT_GRAY;
        }

        // set source file background to gray
        AString ansiBGGray= new AString( ESC.BG_GRAY );
                ansiBGGray._      ( "%CF(%CL):" )
                          ._      ( ANSI_BG_STD_COL );
        metaInfo.format.searchAndReplace( "%CF(%CL):", ansiBGGray.toString() );
    }

    /** ********************************************************************************************
     * The implementation of the abstract method of parent class TextLogger. Logs messages to the
     * application console.
     *
     * @param domain        The log domain name. If not starting with a slash ('/')
     *                      this is appended to any default domain name that might have been specified
     *                      for the source file.
     * @param level         The log level. This has been checked to be active already on this stage
     *                      and is provided to be able to be logged out only.
     * @param msg           The log message.
     * @param indent        the indentation in the output. Defaults to 0.
     * @param caller        Once compiler generated and passed forward to here.
     * @param lineNumber    The line number of a multi-line message, starting with 0. For single line
     *                      messages this is -1.
     **********************************************************************************************/
    @Override
    protected void doTextLog( AString       domain,     Log.Level    level,
                              AString       msg,        int          indent,
                              CallerInfo    caller,     int          lineNumber)
    {
        char[]  buf=        msg.buffer();

        // loop over message, print the parts between the escape sequences
        Tokenizer msgParts= new Tokenizer( msg, '\033' );
        Substring actual=   msgParts.actual;
        Substring rest=     msgParts.rest;
        int       column=   0;
        for(;;)
        {
            msgParts.next( Whitespaces.KEEP );

            // check if end of actual msg part is an ANSI sequence. If yes, we extend the actual msg
            if ( rest.charAtStart() == '[' )
            {
                // read the 'm'
                int idx= rest.indexOf( 'm' );
                if ( idx < 0 ) // unknown ANSI Code
                {
                    ALIB.WARNING( "Unknown ANSI ESC Code " );
                    for (int i= actual.start; i <= actual.end; i++ )
                        out.print( buf[i] );

                    continue;
                }

                column+= actual.length();

                actual.end= rest.start + idx ;
                rest.start+= idx + 1;

                for (int i= actual.start; i <= actual.end; i++ )
                    out.print( buf[i] );

                continue;
            }
            else
            {
                if ( actual.isNotEmpty() )
                {
                    for (int i= actual.start; i <= actual.end; i++ )
                        out.print( buf[i] );
                    column+= actual.length();
               }
            }

            // end of loop?
            if ( !msgParts.hasNext() )
                break;

            // found an ESC sequence
            char c= rest.consume();

            // Colors
            boolean isForeGround=  true;
            if( c == 'C' || c == 'c' )
            {
                isForeGround=  c== 'c';

                c= rest.consume();
                int colNo= c - '0';
                ALIB.ASSERT_WARNING( colNo >=0 && colNo <=9, "Unknown ESC-c code" );

                // add bg
                colNo+=  isForeGround ? 0 : 10;

                // add light
                colNo+=  (isForeGround ? !isBackgroundLight : isBackgroundLight )  ? 20 : 0;

                out.print( ansiCols[ colNo ] );


            }

            // Styles
            else if ( c == 's' )
            {
                // bold/italics style not supported in Windows console

                // reset all
                if ( rest.consume() == 'a' )
                {
                    out.print( ANSI_RESET );
                }
            }

            // auto tab / end of meta
            else if ( c == 't' || c == 'A')
            {
                boolean endOfMeta= c == 'A';
                c=  rest.consume();
                int extraSpace=  c >= '0' && c <= '9' ? (int)  ( c - '0' )
                                                      : (int)  ( c - 'A' ) + 10;

                int tabStop= autoSizes.next( column, extraSpace );
                Util.writeSpaces( out, tabStop - column );
                column= tabStop;

                if ( endOfMeta )
                {
                    String msgPrefix;
                    switch ( level )
                    {
                        case VERBOSE:   msgPrefix= msgPrefixVerbose;     break;
                        case INFO:      msgPrefix= msgPrefixInfo;        break;
                        case WARNING:   msgPrefix= msgPrefixWarning;     break;
                        case ERROR:     msgPrefix= msgPrefixError;       break;
                        default:        msgPrefix= "";                   break;
                    }
                    out.print( msgPrefix );
                }

            }

            // Link (we just colorize links here)
            else if ( c == 'l' )
            {
                out.print( rest.consume() == 'S'
                                       ?  ( isBackgroundLight ? ANSI_LIGHT_BLUE : ANSI_LIGHT_BLUE )
                                       :  ANSI_STD_COL                             );
            }

            else
            {
                ALIB.WARNING( "Unknown ESC code" );
            }

        } // write loop


        out.println(msgPostfix);
    }

    /** ********************************************************************************************
     * Empty implementation, not needed for this class
     *
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    @Override protected void notifyMultiLineOp (Phase phase)
    {
    }

} // class AnsiLogger
