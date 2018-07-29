// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


package com.aworx.lib.strings.format;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.strings.util.AutoSizes;
import com.aworx.lib.lang.Inclusion;
import com.aworx.lib.lang.Alignment;
import com.aworx.lib.lang.Switch;
import com.aworx.lib.lang.Case;


/** ************************************************************************************************
 * Implements a \ref com.aworx.lib.strings.format.Formatter "Formatter" according to the
 * [formatting standards of the Python language](https://docs.python.org/3.5/library/string.html#format-string-syntax).
 *
 * \note
 *   Inherited, public fields of parent class \b FormatterStdImpl provide important possibilities
 *   for changing the formatting behavior of instances of this class. Therefore, do not forget
 *   to consult the \ref com.aworx.lib.strings.format.FormatterStdImpl "parent classes documentation".
 *
 * In general, the original \b Python specification is covered quite well. However, there are
 * some differences, some things are not possible (considering python being a scripting language)
 * but then there are also found some very helpful extensions to that standard. Instead of repeating
 * a complete documentation, please refer to the
 * [Python Documentation](https://docs.python.org/3.5/library/string.html#format-string-syntax) as the foundation
 * and then take note of the following list of differences, extensions and general hints:
 *
 * - <b>General Notes:</b>
 *   \b Python defines a placeholder field as follows
 *
 *          "{" [field_name] ["!" conversion] [":" format_spec] "}"
 *
 *   - By the nature of the implementation language of this class, \b field_name can not be the
 *     name of an identifier, an attribute name or an array element index.
 *     It can only be a positional argument index.
 *
 *   - Python formatter does not allow to switch from <b>automatic field indexing</b> to explicit
 *     indexing. This implementation does allow it. The automatic index always starts with index
 *     \c 0 and is incremented each time automatic indexing is used.
 *     Occurrences of explict indexing have no influence on the automatic indexing.
 *
 *
 *   - This formatter is <b>less strict</b> in respect to the order of the format symbols. E.g.
 *     it allows <c>{:11.5,}</c> where Python allows only <c>{:11,.5}</c>
 *
 *   - With this class being derived from
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl "FormatterStdImpl", features of the parent are
 *     available to this formatter as well. This is especially true and sometimes useful in respect to
 *     setting default values number formatting. For example, this allows to modify all number output
 *     without explicitly repeating the settings in each placeholder of format strings. Other options
 *     for example the grouping characters used with hexadecimal numbers, can not be even changed
 *     with the <b>Python Style</b> formatting options. The only way of doing so is modifying the
 *     properties of the formatter object prior to the format operation.
 *
 *   - Nested replacements in format specification fields are (by nature of this implementation
 *     language) \b not supported.
 *
 * <p>
 *   - <b>Binary, Hexadecimal and Octal Numbers:</b>
 *     Binary, hexadecimal and octal output is <b>cut in size</b> (!) when a field width is given that
 *     is smaller than the resulting amount of digits of the number arguments provided.
 *       \note  This implies that a value written might not be equal to the value given.
 *              This is not a bug but a design decision. The rational behind this is that with this
 *              behavior, there is no need to mask lower digits when passing the arguments to the
 *              format invocation. In other words, the formatter "assumes" that the given field width
 *              indicates that only a corresponding number of lower digits are of interest.
 *
 *   - The number <b>grouping option</b> (<c>','</c>) can also be used with binary, hexadecimal and octal
 *     output.
 *     The types support different grouping separators for nibbles, bytes, 16-bit and 32-bit words.
 *     Changing the separator symbols, is not possible with the format fields of the format strings
 *     (if it was, this would become very incompatible to Python standards). Changes have to be made
 *     prior to the format operation by modifying field
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.alternativeNumberFormat "alternativeNumberFormat"
 *     which is provided through parent class \b %FormatterStdImpl.
 *
 *   - Alternative form (\c '#') adds prefixes as specified in members
 *     - \ref com.aworx.lib.strings.NumberFormat.binLiteralPrefix "binLiteralPrefix",
 *     - \ref com.aworx.lib.strings.NumberFormat.hexLiteralPrefix "hexLiteralPrefix" and
 *     - \ref com.aworx.lib.strings.NumberFormat.octLiteralPrefix "octLiteralPrefix".
 *
 *     For upper case formats,  those are taken from field
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.defaultNumberFormat "defaultNumberFormat",
 *     for lower case formats from
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.alternativeNumberFormat "alternativeNumberFormat".
 *     However, in a alignment with the \b Python specification, \b both default to lower case
 *     literals \c "0b", \c "0o" and \c "0x". All defaults may be changed by the user.
 *
 *
 * <p>
 * - <b>Floating point values:</b>
 *   - If floating point values are provided without a type specification in the format string, then
 *     all values of
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.defaultNumberFormat "defaultNumberFormat"
 *     are used to format the number
 *   - For lower case floating point format types (\c 'f' and \c 'e'), the values specified in
 *     attributes \b %ExponentSeparator, \b %NANLiteral and \b %INFLiteral of object
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.alternativeNumberFormat "alternativeNumberFormat"
 *     are used. For upper case   types (\c 'F' and \c 'E') the corresponding attributes in
 *     \ref com.aworx.lib.strings.format.FormatterStdImpl.defaultNumberFormat "defaultNumberFormat" apply.
 *   - Fixed point formats (\c 'f' and 'F' types) are not supported to use arbitrary length.
 *     See class \ref com.aworx.lib.strings.NumberFormat "NumberFormat" for the limits.
 *     Also, very high values and values close to zero may be converted to scientific format.
 *     Finally, if flag
 *     \ref com.aworx.lib.strings.NumberFormat.forceScientific "forceScientific"
 *     of field #defaultNumberFormat is \c true, types \c 'f' and 'F' behave like types \c 'e' and 'E'.
 *   - When both, a \p{width} and a \p{precision} is given, then the \p{precision} determines the
 *     fractional part, even if the type is \b 'g' or \b 'G'. This is different than specified with
 *     Python formatter, which uses \p{precision} as the overall width in case of types
 *     \b 'g' or \b 'G'.
 *   - Python specifies the formatting option \c '#' ("alternate form") for floating point values
 *     to not omit trailing zeros of the fractional part even if a fractional width was given.
 *     However, in scientific notation and in percentage output (type code \c '\%'), python never omits
 *     trailing zeros.<br>
 *     This implementation omits trailing zeros also in scientific notation and percentage
 *     output. Therefore, when defining fields with dedicated fractional part width, it is recommended
 *     to use the alternate form by adding \c '#' the the format specification. This way, all
 *     numbers written have the same size, independent of the value of their fractional part.
 *   - The 'general format' type for floats, specified with \c 'g' or \c 'G' in the python
 *     implementation limits the precision of the fractional part, even if \p{precision} is not
 *     further specified. This implementation does limit the precision only if type is \c 'f' or \c 'F'.
 *
 * <p>
 * - <b>%String Conversion:</b><br>
 *   If \e type \c 's' (or no \e type) is given in the \b format_spec of the replacement field,
 *   a string representation of the given argument is used.
 *   In \b Java and \b C# such representation is received by invoking <c>Object.[t|T]oString()</c>.
 *   Consequently, to support string representations of custom types, in these languages
 *   the corresponding <b>[t|T]oString()</b> methods of the type have to be implemented.
 *
 *   In this C# implmentation, for the string representation the formatter invokes method
 *   \c Object.ToString. To support string representations for custom types, this method
 *   needs to be implemented for the type in question.
 *
 * - <b>Boolean output:</b><br>
 *   In extension (and deviation) of the Python specification, format specification type \c 'B'
 *   is implemented. The word \b "true" is written if the given value represents a boolean \c true
 *   value, \b "false" otherwise.
 *
 *   In the C# language implementation of \b %ALib, in the case the argument is of type \c boolean, the
 *   its value is used. If the argument is an integral type, it is \c true if the value is not equal
 *   to \c 0. Otherwise, the value is \c true if the argument is not \c null.
 *
 * - <b>Hash-Value Output:</b><br>
 *   In extension (and deviation) of the Python specification, format specification type \c 'h' and
 *   its upper case version \c 'H' is implemented. The hash-values of the argument object is
 *   written in hexadecimal format. Options of the type are identical to those of \c 'x',
 *   respectively \c 'X'.
 *
 * <p>
 * - <b>%Custom %Format Specifications:</b><br>
 *   With \c Python formatting syntax, placeholders have the the following syntax:
 *
 *          "{" [field_name] ["!" conversion] [":" format_spec] "}"
 *
 *   The part that follows the colon is called \b format_spec. \b Python passes this portion
 *   of the placeholder to a built-in function \c format(). Now, each type may interpret
 *   this string in a type specific way. But most built-in \b Python types do it along what
 *   they call the
 *   ["Format Specification Mini Language"](https://docs.python.org/3.5/library/string.html#format-specification-mini-language).
 *
 *   With this implementation, the approach is very similar. The only difference is that the
 *   "Format Specification Mini Language" is implemented for standard types right within this class.
 *   But before processing \b format_spec, this class will check if an argument provides a custom
 *   implementation for formatting.
 *
 *   In \b C++ and \b C# this is done by checking if the provided argument implements a specific
 *   interface used for formatting values with custom format strings. As such method is not
 *   available in Java, no similar concept is implemented here. Instead, only date/time formats
 *   are "hardcoded" within method
 *   \ref com.aworx.lib.strings.format.FormatterStdImpl.writeCustomFormat "FormatterStdImpl.writeCustomFormat".
 *   This is a little unfortunate: To customize the formatting of custom types, a dedicated wrapper
 *   class has to be written which implements method \b %toString and writes the wrapped custom object.
 *   Then, when formatting, the custom types have to passed wrapped in such wrapper class dedicated to
 *   formatting.
 *
 * <p>
 * - <b>Conversions:</b><br>
 *   In the \b Python placeholder syntax specification:
 *
 *          "{" [field_name] ["!" conversion] [":" format_spec] "}"
 *
 *   symbol \c '!' if used prior to the colon <c>':'</c> defines
 *   what is called the <b>conversion</b>. With \b Python, three options are given:
 *   \c '!s' which calls \c str() on the value, \c '!r' which calls \c repr() and \c '!a' which
 *   calls \c ascii(). This is of-course not applicable to this formatter. As a replacement,
 *   this class extends the original specification of that conversion using \c '!'.
 *   The following provides a list of conversions supported. The names given can be abbreviated
 *   at any point and ignore letter case, e.g. \c !Upper can be \c !UP or just \c !u.
 *   In addition, multiple conversions can be given by concatenating them, each repeating
 *   character \c '!'.<br>
 *   The conversions supported are:
 *
 *   - <b>!Upper</b><br>
 *     Converts the contents of the field to upper case.
 *
 *   - <b>!Lower</b><br>
 *     Converts the contents of the field to lower case.
 *
 *   - <b>!Quote</b><br>
 *     Puts quote characters \c '"' around the field.
 *     Note that these characters are not respecting any optional given field width but instead
 *     are added to such.<br>
 *     An alias name for \!Quote is given with \b !Str. As the alias can be abbreviated to \b !s,
 *     this provides compatibility with the \b Python specification.
 *
 *   - <b>!ESC[\<|\>]</b><br>
 *     In its default behavior or if \c '<' is specified, certain characters are converted to escape
 *     sequences. If \c '>' is given, escape sequences are converted to their (ascii) value.
 *     See \ref com.aworx.lib.strings.AString.escape "AString.escape" for details about the
 *     conversion that is performed.<br>
 *     An alias name for \b !ESC< is given with \b !a which provides compatibility
 *     with the \b Python specification.
 *     \note If \b !ESC\< is used in combination with \b !Quote, then \b !ESC\< should be the first
 *           conversion specifier. Otherwise, the quotes inserted might be escaped as well.
 *
 *   - <b>!Fill[Cc]</b><br>
 *     Inserts as many characters as denoted by the integer type argument.
 *     By default the fill character is space <c>' '</c>. It can be changed with optional character
 *     'C' plus the character wanted.
 *
 *   - <b>!Tab[Cc][NNN]</b><br>
 *     Inserts fill characters to extend the length of the string to be a multiple of a tab width.
 *     By default the fill character is space <c>' '</c>. It can be changed with optional character
 *     'C' plus the character wanted. The tab width defaults to \c 8. It can be changed by adding
 *     an unsigned decimal number.
 *
 *   - <b>!ATab[[Cc][NNN]|Reset]</b><br>
 *     Inserts an "automatic tabulator stop". These are tabulator positions that are stored
 *     internally and are automatically extended in the moment the actual contents exceeds the
 *     currently stored tab-position. An arbitrary amount of auto tab stop and field width
 *     (see <b>!AWith</b> below) values is maintained by the formatter.
 *
 *     Which each new invocation of \alib{strings.format,Formatter.format}, the first auto value
 *     is chosen and with each use of \c !ATab or \c !AWidth, the next value is used.<br>
 *     By default, the fill character is space <c>' '</c>. It can be changed with optional character
 *     'C' plus the character wanted. The optional number provided gives the growth value by which
 *     the tab will grow if its position is exceeded. This value defaults to \c 3.
 *     The positions currently stored with the formatter can be reset with providing argument
 *     \c Reset. Alternatively to this, outside of a formatting process, the tab stops can be reset
 *     by invoking method \alib{strings.format,Formatter.reset}.
 *
 *     Both, auto tab and auto width conversions may be used to increase readability of multiple
 *     output lines. Of-course, output is not completely tabular, only if those values that result
 *     in the biggest sizes are formatted first. If a perfect tabular output is desired, the data
 *     to be formatted may be processed twice: Once to temporary buffer which is disposed and then
 *     a second time to the desired output \b %AString.
 *
 *     \note Method \alib{strings.format,Formatter.releaseDefault} resets the auto size values
 *           in case no multiple (recursive) acquirements had been performed.
 *
 *   - <b>!AWidth[NNN|Reset]</b><br>
 *     Increases field width with repetitive invocations of format whenever a field value did not
 *     fit to the actually stored width. Optional decimal number \b NNN is added as a padding value.
 *     for more information, see <b>!ATab</b> above.
 *
 *   - <b>!Xtinguish</b><br>
 *     Does not print anything. This is useful if format strings are externalized.
 *     Modifications of such resources might use this conversion to suppress the display of
 *     arguments (which usually are hard-coded).
 *
 *   - <b>!Replace\<search\>\<replace\></b><br>
 *     Searches string \p{search} and replaces with \p{replace}. Both values have to be given
 *     enclosed by characters \c '<' and \c '>'. In the special case that \p{search} is empty
 *     (<c>\<\></c>), string \p{replace} will be inserted if the field argument is an empty string.
 **************************************************************************************************/
public class FormatterPythonStyle extends FormatterStdImpl
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################
        /**
         * The portion of the replacement field that represents the conversion specification.
         * This specification is given at the beginning of the replacement field, starting with
         * \c '!'.
         */
        protected Substring                   phaExtConversion                    = new Substring();

        /** Reused object used to parse #phaExtConversion in method #preAndPostProcess. */
        protected Substring conversion = new Substring();

        /** The value read from the precision field.
         *  This is set to \c -1 in #resetPHAs. */
        protected int                         phaExtPrecision;

        /** The default precision if not given.
         *  This is set to \c 6 in #resetPHAs, but is changed when specific. */
        protected int                         phaExtDefaultPrecision;

        /** Constant string array */
        protected static char[]               constColonAndClosingBracket      = ":}".toCharArray();

        /** Storage of sizes for auto-tabulator feature <b>{!ATab}</b> and auto field width feature
        <b>{!AWidth}</b>  */
        protected AutoSizes                   autoSizes                           = new AutoSizes();


    // #############################################################################################
    //  Constructor/Destructor
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs this formatter.
         * Inherited field #defaultNumberFormat is initialized to meet the formatting defaults of
         * Java.
         ******************************************************************************************/
        public FormatterPythonStyle()
        {
            super("FormatterPythonStyle" );
            construct();
        }

        /** ****************************************************************************************
         * Constructor helper method.
         ******************************************************************************************/
        protected void construct()
        {
            // set number format to python defaults
            defaultNumberFormat.forceDecimalPoint       = false;
            defaultNumberFormat.writeExponentPlusSign   = true;
        }



    // #############################################################################################
    //  Implementation of FormatterStdImpl interface
    // #############################################################################################
        /** ****************************************************************************************
         * Resets #autoSizes.
         ******************************************************************************************/
        @Override
        public void                reset()
        {
            super.reset();
            autoSizes.reset();
        }

        /** ****************************************************************************************
         * Sets the actual auto tab stop index to \c 0.
         ******************************************************************************************/
        @Override
        protected void                initializeFormat()
        {
            super.initializeFormat();
            autoSizes.start();
        }

        /** ****************************************************************************************
         * Invokes parent implementation and then applies some changes to reflect what is defined as
         * default in the Python string format specification.
         ******************************************************************************************/
        @Override
        protected void    resetPHAs()
        {
            // first invoke parent's setting...
            super.resetPHAs();

            // ...then make some "python like" adjustments
            phaExtConversion.setNull();

            phaNF.forceDecimalPoint             = false;
            phaNF.exponentSeparator             = alternativeNumberFormat.exponentSeparator; // choose lower case as default
            phaNF.INFLiteral                    = alternativeNumberFormat.INFLiteral;        // choose lower case as default
            phaNF.NANLiteral                    = alternativeNumberFormat.NANLiteral;        // choose lower case as default
            phaNF.omitTrailingFractionalZeros   = true;

            phaExtPrecision                     = -1;
            phaExtDefaultPrecision              = 6;
        }


        /** ****************************************************************************************
         * Searches for \c '{'  which is not '{{'.
         *
         * @return The index found, -1 if not found.
         ******************************************************************************************/
        @Override
        protected  int  findPlaceholder()
        {
            int idx= 0;
            while(     (idx= parser.indexOf('{', idx )) >= 0
                   &&  parser.charAt( idx + 1 ) == '{'                   )
            {
                // double ESC found (escaped {{)
                idx+= + 2;
            }
            return idx;
        }


        //! @cond NO_DOX
        protected enum ppStates
        {
            POSITION      ,
            CONVERSION    ,
            COLON         ,
            FORMAT_SPEC   ,
            END           ,
        }
        //! @endcond

        /** ****************************************************************************************
         * Parses placeholder field in python notation. The portion \p{format_spec} is not
         * parsed but stored in member
         * \ref com.aworx.lib.strings.format.FormatterStdImpl.phaFormatSpec "Formatter.phaFormatSpec".
         *
         * @return \c true on success, \c false on errors.
         ******************************************************************************************/
        @Override
        protected boolean    parsePlaceholder()
        {

            ppStates  state= ppStates.POSITION;

            while( true )
            {
                // switch over state. With 'break' we consume on character (kind of success) while
                // with 'continue' we keep the current character (and go to another state)
                switch ( state )
                {
                    case POSITION:

                        if( Character.isDigit( parser.charAtStart() )  )
                        {
                            parser.consumeDecDigits();
                            setArgument( (int) parser.consumedLong, false );
                        }
                        state= ppStates.CONVERSION; continue;


                    case CONVERSION:
                        if( parser.charAtStart() == '!' )
                        {
                            int endConversion= parser.indexOfAny(constColonAndClosingBracket, Inclusion.INCLUDE );
                            if( endConversion < 0 )
                            {
                                errorFormatString( "Closing replacement bracket '}' not found" );
                                return false;
                            }

                            phaExtConversion.set( parser, 0, endConversion );
                            parser.consumeChars( endConversion );
                        }
                        state= ppStates.COLON; continue;

                    case COLON:
                        if( parser.charAtStart() != ':'  )
                        {
                            state= ppStates.END;
                            continue;
                        }

                        parser.consumeChars(1);
                        state= ppStates.FORMAT_SPEC; continue;

                    case FORMAT_SPEC:
                    {
                        // find end of format spec (allow "\}" in format string)
                        int eoFormatSpec= -1;
                        do
                        {
                            eoFormatSpec= parser.indexOf( '}', eoFormatSpec + 1 );
                        }
                        while(      eoFormatSpec > 0
                                &&  parser.charAt( eoFormatSpec - 1) == '\\' );

                        if ( eoFormatSpec < 0 )
                        {
                            errorFormatString( "Closing replacement bracket '}' not found" );
                            return false;
                        }

                        // extract format spec to separate substring
                        phaFormatSpec.set( parser, 0, eoFormatSpec );
                        parser.consumeChars( eoFormatSpec ) ;

                        state= ppStates.END; continue;
                    }

                    case END:
                        if( parser.charAtStart() != '}'  )
                        {
                            errorFormatString( "Closing replacement bracket '}' not found" );
                            return false;
                        }
                        parser.consumeChars(1);
                        return true;

                } // state switch

            } // read loop

        }


        /** ****************************************************************************************
         * Parses the format specification for standard types as specified in
         * ["Format Specification Mini Language"](https://docs.python.org/3.5/library/string.html#format-specification-mini-language).
         *
         * @return \c true on success, \c false on errors.
         ******************************************************************************************/
        @Override
        protected boolean    parseStdFormatSpec()
        {
            // parse alignment and fill character. This is a bit tricky to shorten the code.
            // The alignment token <,>,^ or = can be on first or second position. If second, then the
            // first was a fill character. Therefore we loop from 0 to 1....
            int charsToConsume= 1;
            phaAlignmentSpecified= true;
            Substring formatSpec= phaFormatSpec;


            int cNo= 0;
            do switch ( formatSpec.charAt( cNo++ ) )
            {
                case '<': phaAlignment= Alignment.LEFT;    break;
                case '>': phaAlignment= Alignment.RIGHT;   break;
                case '^': phaAlignment= Alignment.CENTER;  break;
                case '=': phaAlignment= Alignment.RIGHT;
                          phaSignPaddingMode=  true;        break;

                default:
                    if(cNo == 1 )
                    {
                        charsToConsume= 2;
                        phaFillChar= formatSpec.charAtStart();
                    }
                    else
                    {
                        charsToConsume= 0;
                        phaFillChar= ' ';
                        phaAlignmentSpecified= false;
                    }
                break;
            }
            while( cNo < 2 && charsToConsume != 1 );
            formatSpec.consumeChars( charsToConsume );

            // other things to parse
            char actChar;
            while( (actChar= formatSpec.charAtStart()) != '\0' )
            {
                // width
                if( Character.isDigit( actChar ) )
                {
                    // Python doc says:
                    //   When no explicit alignment is given, preceding the width field by a zero ('0') character
                    //   enables sign-aware zero-padding for numeric types.
                    //   This is equivalent to a fill character of '0' with an alignment type of '='.
                    if ( actChar == '0' )
                        phaSignPaddingMode= true;
                    formatSpec.consumeDecDigits();
                    phaWidth= (int) formatSpec.consumedLong;

                    continue; // not consume below
                }

                // precision. Python doc says:
                // "The precision is a decimal number indicating how many digits should be displayed
                // after the decimal point for a floating point value formatted with 'f' and 'F', or
                // before and after the decimal point for a floating point value formatted with 'g' or 'G'.
                // For non-number types the field indicates the maximum field size - in other words,
                // how many characters will be used from the field content. The precision is not
                // allowed for integer values."
                else if( actChar == '.' )
                {
                    formatSpec.consumeChars( 1 );
                    if ( ! formatSpec.consumeDecDigits( ) )
                    {
                        errorFormatString( "Missing precision value after '.' character" );
                        return false;
                    }
                    phaExtPrecision= (int) formatSpec.consumedLong;
                    continue;
                }


                // ----------------------------- Types -------------------------------------
                else if ("sdcboxXeEfFngGhHB%".indexOf( actChar ) >= 0 )
                {
                    if ( phaTypeCode != '\0' )
                    {
                        errorFormatString(    "Duplicate type code '"   + actChar
                                           +  "' given (previous was '" + phaTypeCode + "')" );
                        return false;
                    }

                    phaTypeCode= actChar;

                    if( "EGF".indexOf( actChar ) >= 0 )
                    {
                        phaNF.exponentSeparator= defaultNumberFormat.exponentSeparator;
                        phaNF.INFLiteral=        defaultNumberFormat.INFLiteral;
                        phaNF.NANLiteral=        defaultNumberFormat.NANLiteral;
                    }


                    switch( actChar )
                    {
                        case 's':   phaType= PHType.String;                break;
                        case 'd':   phaType= PHType.IntBase10;             break;
                        case 'c':   phaType= PHType.Character;             break;
                        case 'b':   phaType= PHType.IntBinary;             break;
                        case 'o':   phaType= PHType.IntOctal;              break;

                        case 'X':   phaNF.hexLowerCase= false;   //$FALL-THROUGH$

                        case 'x':   phaType= PHType.IntHex;                break;

                        case 'H':   phaNF.hexLowerCase= false;   //$FALL-THROUGH$
                        case 'h':   phaType= PHType.HashCode;              break;
                        case 'B':   phaType= PHType.Bool;                  break;

                        // float types
                        case 'E':   phaType= PHType.Float;       //$FALL-THROUGH$
                        case 'e':   phaType= PHType.Float;       //$FALL-THROUGH$
                                    phaNF.forceScientific= true;           break;

                        case '%':   phaIsPercentage= true;       //$FALL-THROUGH$
                        case 'f':
                        case 'F':   phaNF.omitTrailingFractionalZeros= false;
                                    phaType= PHType.Float;                 break;

                        case 'n':   phaNF.decimalPointChar=   alternativeNumberFormat.decimalPointChar;
                                    phaNF.thousandsGroupChar= alternativeNumberFormat.thousandsGroupChar;
                                                                 //$FALL-THROUGH$
                        case 'G':                                //$FALL-THROUGH$
                        case 'g':   phaType= PHType.Float;
                                    phaExtDefaultPrecision=   -1;
                        break;

                        default:    com.aworx.lib.ALIB_DBG.ERROR("Unhandled character in choices string above");
                                    return false;

                    }//switch
                }


                // others
                else switch( actChar )
                {
                    // sign
                    case '+':   phaNF.plusSign= '+' ;  break;
                    case '-':   phaNF.plusSign= '\0';  break;
                    case ' ':   phaNF.plusSign= ' ' ;  break;

                    // alternate version ('#')
                    case '#':   phaWriteBinOctHexPrefix=             true;
                                phaNF.forceDecimalPoint=             true;
                                phaNF.omitTrailingFractionalZeros=   false;
                    break;

                    // Enable grouping
                    case ',':   phaNF.writeGroupChars= true;
                                break;


                    default:    errorFormatString( "Unknown format character '" + actChar + '\'' );
                                return false;
                }

                formatSpec.consumeChars(1);
            }

            return true;
        }

        /** ****************************************************************************************
         * Implementation of abstract method.<br>
         * Replaces \c "{{" with \c "{" and \c "}}" with \c "}". In addition applies
         * \ref com.aworx.lib.strings.AString.escape "AString.escape" on \p{target} which
         * replaces standard codes like \c "\\n", \c "\\r" or \c "\\t" with corresponding ascii
         * codes.
         *
         * @param startIdx The start of the region to replace
         ******************************************************************************************/
        @Override
        protected void    replaceEscapeSequences( int startIdx )
        {
            ptargetString.searchAndReplace( "{{" , "{" , startIdx );
            ptargetString.searchAndReplace( "}}" , "}" , startIdx );
            ptargetString.escape( Switch.OFF, startIdx );
        }


        /** ****************************************************************************************
         * Processes "conversions" which are specified with \c '!'.
         *
         * @param startIdx  The int of the start of the field written in #ptargetString.
         *                  \c -1 indicates pre-phase.
         * @param target    The target string, only if different from field #ptargetString, which
         *                  indicates intermediate phase.
         * @return \c false, if the placeholder should be skipped (nothing is written for it).
         *         \c true otherwise.
         ******************************************************************************************/
        @Override
        protected boolean preAndPostProcess( int startIdx, AString target )
        {
            boolean isPreProcess=  startIdx<  0;
            boolean isPostProcess= startIdx>= 0 && target == null;
            conversion.set( phaExtConversion );

            while( conversion.isNotEmpty() )
            {
                if( !conversion.consumeChar('!') )
                {
                    errorFormatString( "Expected '!' in (rest of) conversion string \"!" + conversion + '"'  );
                    return false;
                }

                     if(   conversion.consumePartOf("Xtinguish") > 0 )   { return false;  }
                     if(   conversion.consumePartOf("Upper"    ) > 0 )   { if (isPostProcess) ptargetString.toUpper( startIdx );                 }
                else if(   conversion.consumePartOf("Upper"    ) > 0 )   { if (isPostProcess) ptargetString.toUpper( startIdx );                 }
                else if(   conversion.consumePartOf("Lower"    ) > 0 )   { if (isPostProcess) ptargetString.toLower( startIdx );                 }
                else if(   conversion.consumePartOf("str"      ) > 0
                        || conversion.consumePartOf("Quote"    ) > 0 )   { if (isPostProcess) ptargetString.insertAt("\"", startIdx)._NC( "\"" );  }

                else if( conversion.consumePartOf( "Fill"     ) > 0 )
                {
                    phaType= PHType.Fill;
                    phaFillChar=  conversion.consumeChar('C', Case.IGNORE ) && conversion.length() > 0
                                    ? conversion.consumeChar()
                                    : ' ';

                }

                else if(  conversion.consumePartOf("Tab"      ) > 0 )
                {
                    char tabChar= conversion.consumeChar('C', Case.IGNORE ) && conversion.length() > 0
                                    ? conversion.consumeChar()
                                    : ' ';
                    int tabSize = conversion.consumeDecDigits()
                                  ? (int) conversion.consumedLong
                                  : 8;

                    if( isPreProcess )
                        ptargetString.tab( tabSize, 1, tabChar );

                }
                else if( conversion.consumePartOf("ATab"  , 2) > 0 )
                {

                    if( conversion.consumePartOf("Reset"  , 1) > 0 )
                    {
                        if(isPreProcess)
                            autoSizes.reset();
                    }
                    else
                    {
                        char tabChar= conversion.consumeChar('C', Case.IGNORE ) && conversion.length() > 0
                                          ? conversion.consumeChar()
                                          : ' ';

                        int growth= conversion.consumeDecDigits()
                                    ? (int) conversion.consumedLong - 1
                                    : 3;

                        if( isPreProcess )
                        {
                            int actPos= ptargetString.length() - targetStringStartLength;
                            int tabStop= autoSizes.next( actPos + 1, growth );
                            ptargetString.insertChars( tabChar, tabStop - actPos );
                        }
                    }
                }

                else if( conversion.consumePartOf("AWidth"  , 2 ) > 0 )
                {
                    if( conversion.consumePartOf("Reset"      ) > 0 )
                    {
                        if(isPreProcess)
                            autoSizes.reset();
                    }
                    else
                    {
                        int extraPadding= conversion.consumeDecDigits()
                                    ? (int) conversion.consumedLong
                                    : 0;

                        if( isPreProcess )
                            phaWidth= autoSizes.actual( 0, extraPadding );
                        else if( isPostProcess )
                            autoSizes.next( ptargetString.length() - startIdx, extraPadding );
                    }
                }

                else if(    conversion.consumePartOf( "Esc" ) > 0
                         || conversion.consumePartOf( "A"   ) > 0)
                {
                    Switch toESC= Switch.ON;
                    conversion.consumeChar('<');
                    if(conversion.consumeChar('>') )
                        toESC=  Switch.OFF;

                    if (isPostProcess)
                        ptargetString.escape(toESC, startIdx);
                }

                else if( conversion.consumePartOf("Replace"  , 2 ) > 0 )
                {
                    Substring search=  new Substring(); conversion.consumeField( '<', '>', search  );
                    Substring replace= new Substring(); conversion.consumeField( '<', '>', replace );
                    if( search.isNull() || replace.isNull() )
                    {
                        errorFormatString( "Missing search and replace arguments of conversion \"!Replace\""  );
                        return false;
                    }

                    if( target != null )
                    {
                        // special case: fill empty fields
                        if( search.isEmpty() && target.length() - startIdx == 0 )
                        {
                            target._( replace );
                        }
                        else
                            target.searchAndReplace( search.toString(), replace.toString(), startIdx );
                    }
                }

                // error (not recognized)
                else
                {
                    errorFormatString( "Unknown conversion string \"!" + conversion + '"'  );
                    return false;
                }

            }
            return true;
        }



        /** ****************************************************************************************
         * Makes some attribute adjustments and invokes standard implementation
         * @return \c true if OK, \c false if replacement should be aborted.
         ******************************************************************************************/
        @Override
        protected boolean    checkStdFieldAgainstArgument()
        {
            boolean wasFloat= phaType == PHType.Float;
            if( wasFloat )
            {
                if ( phaExtPrecision >= 0 )
                    phaNF.fractionalPartWidth= phaExtPrecision;
                else if( phaNF.fractionalPartWidth < 0 )
                    phaNF.fractionalPartWidth= phaExtDefaultPrecision;
            }

            boolean result= super.checkStdFieldAgainstArgument();

            if( !wasFloat && phaType == PHType.Float )
            {
                if ( phaExtPrecision >= 0 )
                    phaNF.fractionalPartWidth= phaExtPrecision;
            }

            if( phaType == PHType.String || phaType == PHType.Bool )
                phaCutContent= phaExtPrecision;
            else if ( phaExtPrecision >= 0 && phaType != PHType.Float )
            {
                errorFormatString( "Precision not allowed in integer format specifier" );
                return false;
            }

            return result;

        }


}
