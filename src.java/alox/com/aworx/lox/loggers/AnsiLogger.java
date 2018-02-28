// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lox.loggers;

import java.io.PrintStream;

import com.aworx.lib.config.Variable;
import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Phase;
import com.aworx.lib.lang.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.util.Tokenizer;
import com.aworx.lib.strings.util.Spaces;
import com.aworx.lox.ALox;
import com.aworx.lox.ESC;
import com.aworx.lox.Verbosity;
import com.aworx.lox.core.Domain;
import com.aworx.lox.core.ScopeInfo;
import com.aworx.lox.core.textlogger.TextLogger;

/** ************************************************************************************************
 * A logger that logs all messages to the <em>PrintStream</em> instance provided in the constructor.
 * The name of the \e Logger defaults to "ANSI_LOGGER".
 *
 * \b %ALox text logger escape sequences (see class \ref com.aworx.lox.ESC "ESC")
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
 * #useLightColors and also configuration variable
 * [ALOX_CONSOLE_LIGHT_COLORS](../group__GrpALoxConfigVars.html).
 *
 * In the constructor, a default format string and some other definitions in member
 * \ref metaInfo get set to include color settings.
 * Of-course, these publicly accessible format attributes can be customized after creation.
 *
 * There is not 100% match between the ANSI sequences and the definitions in
 * \ref com.aworx.lox.ESC "ESC".
 * For example ESC does not provide all ANSI colors and no blinking. On the other hand,
 * ANSI does not allow to reset the style without resetting the colors.
 * Of-course, it is no problem to log other ANSI codes directly into an \b %AnsiLogger.
 * In this case, other Loggers that might be attached to the same Lox and that do not
 * support ANSI must be equipped with corresponding replacement information.
 * In other words: To support the same log output into different loggers, it is
 * recommended to use \ref com.aworx.lox.ESC "ESC"  sequences instead of
 * directly using ANSI codes.
 *
 * The ANSI codes used by this class are exposed through a list of fields.
 * They might be useful for manipulating the attributes of the \ref metaInfo
 * member, which of-course might contain native ANSI sequences.
 * (In contrast to the log messages themselves, this meta information is specific to a logger
 * instance and this way it does not need to be replaced in other loggers).
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
    // Internal fields
    // #############################################################################################

        /**
         * The PrintStream provided in the constructor.
         */
        protected   PrintStream             out;

    // #############################################################################################
    // Public fields
    // #############################################################################################

        /** Denotes states of field #useLightColors.  */
        public enum LightColorUsage
        {
            _UNDEFINED,         ///< Internal, temporary state
            NEVER,              ///< Never use light colors
            FOREGROUND_LIGHT,   ///< Use light colors for foreground
            FOREGROUND_DARK     ///< Use light colors for background
        }

        /**
         * Foreground and background colors chosen by this class might differ in their intensity.
         * This increases the overall readability by increasing the contrast.
         * If the background color of a console window is dark, then the background colors of
         * colored log output should be darker colors than the foreground colors - and vice versa.
         *
         * Depending on the setting of this field, \b %ALox
         * \ref com.aworx.lox.ESC "escape codes" for colors are translated to normal ANSI colors or
         * lighter ones:
         * - If this field is \ref LightColorUsage "LightColorUsageNEVER", light colors are
         *   never used.
         * - If this field is \ref LightColorUsage "LightColorUsage.FOREGROUND_LIGHT", foreground
         *   colors will be light colors and background colors dark ones. This is the default.
         * - If \ref LightColorUsage "LightColorUsage.FOREGROUND_DARK", background colors will be
         *   light colors and foreground colors dark ones.
         *
         * The configuration variable [ALOX_CONSOLE_LIGHT_COLORS](../group__GrpALoxConfigVars.html)
         * allows to externally modify this flag. It is read once within the constructor .
         */
        public      LightColorUsage         useLightColors;

    // #############################################################################################
    // Methods
    // #############################################################################################

    /** ********************************************************************************************
     * Creates an AnsiLogger with the given PrintStream and name.
     * @param out            A java.io.PrintStream to write the log data to.
     * @param usesStdStreams Denotes whether this logger writes to the
     *                       <em>standard output streams</em>.
     * @param name           The name of the \e Logger, defaults to what is provided with
     *                       parameter \p typeName.
     * @param typeName       The type of the \e Logger, defaults to "ANSI".
     **********************************************************************************************/
    public    AnsiLogger( PrintStream  out, boolean usesStdStreams , String name, String typeName )
    {
        super( name, typeName, usesStdStreams );
        construct( out );
    }

    /** ********************************************************************************************
     * Creates an AnsiLogger with the given PrintStream and name.
     * @param out            A java.io.PrintStream to write the log data to.
     * @param usesStdStreams Denotes whether this logger writes to the
     *                       <em>standard output streams</em>.
     * @param name           The name of the \e Logger. Defaults to "ANSI".
     **********************************************************************************************/
    public    AnsiLogger( PrintStream  out, boolean usesStdStreams , String name )
    {
        super( name, "ANSI", usesStdStreams );
        construct( out );
    }

    /** ********************************************************************************************
     * Overwritten constructor providing default parameters.
     * @param out            A java.io.PrintStream to write the log data to.
     * @param usesStdStreams Denotes whether this logger writes to the
     *                       <em>standard output streams</em>.
     **********************************************************************************************/
    public    AnsiLogger( PrintStream  out, boolean usesStdStreams )
    {
        super( null, "ANSI", usesStdStreams );
        construct( out );
    }

    /** ********************************************************************************************
     * Helper method used by the constructors.
     * @param ps   A java.io.PrintStream to write the log data to.
     **********************************************************************************************/
    protected void construct( PrintStream  ps )
    {
        this.out= ps;

        // set msg suffix to "reset"
        fmtMsgSuffix= ANSI_RESET;

        // evaluate environment variable "ALOX_CONSOLE_LIGHT_COLORS"
        useLightColors= LightColorUsage._UNDEFINED;
        Variable variable= new Variable( ALox.CONSOLE_LIGHT_COLORS );
        if ( ALox.config.load(variable) > 0 && variable.size() > 0)
        {
            Substring p= new Substring(variable.getString());
            if(p.trim().isNotEmpty())
            {
                     if( p.consumePartOf( "foreground" ) > 0)  useLightColors=  LightColorUsage.FOREGROUND_LIGHT;
                else if( p.consumePartOf( "background" ) > 0)  useLightColors=  LightColorUsage.FOREGROUND_DARK;
                else if( p.consumePartOf( "never"      ) > 0)  useLightColors=  LightColorUsage.NEVER;
                else
                {
                    com.aworx.lib.ALIB_DBG.WARNING( "Unknown value specified in variable: " + variable.fullname
                                  +" = " + variable.getString() +'.' );
                }
            }
        }



        if( useLightColors == LightColorUsage._UNDEFINED )
        {
            // default: dark background, hence use light color on foreground
            useLightColors= LightColorUsage.FOREGROUND_LIGHT;
        }

        // move verbosity information to the end to colorize the whole line
        metaInfo.format.searchAndReplace( "]%V[", "][" );
        metaInfo.format._( "%V" );
        metaInfo.verbosityError           = ESC.RED;
        metaInfo.verbosityWarning         = ESC.BLUE;
        metaInfo.verbosityInfo            = "";
        metaInfo.verbosityVerbose         = ESC.GRAY;
    }

    /** ********************************************************************************************
     * Implementation of the abstract method of parent class TextLogger. Logs messages to the
     * application console.
     *
     * @param domain        The <em>Log Domain</em>.
     * @param verbosity     The verbosity. This has been checked to be active already on this stage
     *                      and is provided to be able to be logged out only.
     * @param msg           The log message.
     * @param scope         Information about the scope of the <em>Log Statement</em>..
     * @param lineNumber    The line number of a multi-line message, starting with 0. For single line
     *                      messages this is -1.
     **********************************************************************************************/
    @Override
    protected void logText( Domain       domain,    Verbosity verbosity,
                            AString      msg,
                            ScopeInfo    scope,     int          lineNumber)
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
                    com.aworx.lib.ALIB_DBG.WARNING( "Unknown ANSI ESC Code " );
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

            if ( actual.isNotEmpty() )
            {
                for (int i= actual.start; i <= actual.end; i++ )
                    out.print( buf[i] );
                column+= actual.length();
            }

            // end of loop?
            if ( !msgParts.hasNext() )
                break;

            // found an ESC sequence
            char c= rest.consumeChar();

            // Colors
            boolean isForeGround=  true;
            if( c == 'C' || c == 'c' )
            {
                isForeGround=  c== 'c';

                c= rest.consumeChar();
                int colNo= c - '0';
                com.aworx.lib.ALIB_DBG.ASSERT_WARNING( colNo >=0 && colNo <=9, "Unknown ESC-c code" );

                // add bg
                colNo+=  isForeGround ? 0 : 10;

                // add light
                if(       useLightColors != LightColorUsage.NEVER
                    && ( (useLightColors == LightColorUsage.FOREGROUND_LIGHT) == isForeGround )     )
                    colNo+= 20;

                out.print( ansiCols[ colNo ] );


            }

            // Styles
            else if ( c == 's' )
            {
                c=  rest.consumeChar();
                out.print(   c == 'B' ? ANSI_BOLD
                           : c == 'I' ? ANSI_ITALICS
                           :            ANSI_RESET    );
            }

            // auto tab / end of meta
            else if ( c == 't' || c == 'A')
            {
                c=  rest.consumeChar();
                int extraSpace=  c >= '0' && c <= '9' ? ( c - '0' )
                                                      : ( c - 'A' ) + 10;

                int tabStop= autoSizes.next( column, extraSpace );
                Spaces.write( out, tabStop - column );
                column= tabStop;
            }

            // Link (we just colorize links here)
            else if ( c == 'l' )
            {
                out.print( rest.consumeChar() == 'S'
                                       ?  ( useLightColors == LightColorUsage.FOREGROUND_LIGHT ? ANSI_LIGHT_BLUE : ANSI_BLUE )
                                       :  ANSI_STD_COL                             );
            }

            else
            {
                com.aworx.lib.ALIB_DBG.WARNING( "Unknown ESC code" );
            }

        } // write loop


        out.println();
    }

    /** ****************************************************************************************
     * Empty implementation.
     *
     * @param phase The phase of the multi-line operation (ignored).
     ******************************************************************************************/
    @Override protected void notifyMultiLineOp (Phase phase)
    {
    }

} // class AnsiLogger
