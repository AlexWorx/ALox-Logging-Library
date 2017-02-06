// #########writeri#######################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.strings;

import java.text.DecimalFormatSymbols;

import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Inclusion;


/** ************************************************************************************************
 * Defines various values needed to convert integer and floating point values
 * to string representations and vice versa.
 * In addition, this class provides methods that do such conversions on character array
 * buffers.
 *
 * \attention
 *   The methods of this class are not intended for the common use. Instead, use interface of
 *   classes
 *      \ref com::aworx::lib::strings::AString   "AString",
 *      \ref com::aworx::lib::strings::Substring "Substring" or
 *      \ref com::aworx::lib::strings::Formatter "Formatter"
 *   to write and parse numbers, which accept an object of this type as parameters.
 *
 * <b>Defined Singletons and User-Defined Instances:</b><br>
 * Two static singletons of this class are defined which can be used whereve
 * r a number format object
 * is needed as a parameter:
 * - #global<br>
 *   This is initialized with method
 *   \ref com::aworx::lib::ALIB::init "ALIB.init" and reflects local specific settings.
 *
 * - #computational<br>
 *   This is also initialized with method
 *   \ref com::aworx::lib::ALIB::init "ALIB.init" and should be used for writing and parsing
 *   numbers which are intended to be readable by software. Its' decimal point character
 *   is set to \c '.', the international standard. Furthermore no group separators are set for
 *   decimal and decimal floating point as well as for binary, hexadecimal and octal conversion.
 *
 * User defined objects default to the 'computational' setting after construction.
 *
 * <b>Output Formats:</b><br>
 * The following conversion formats are supported
 *
 * - \b Decimal<br>
 *   Supports optional minimum output width with field #decMinimumFieldWidth,
 *   and definable thousands grouping character with field #thousandsGroupChar, which can be
 *   activated with field #writeGroupChars.<br>
 *   Furthermore, the plus-sign can be controlled (#plusSign) to be either left out or be anything
 *   defined. Of-course, values \b ' ' and \b '+' are reasonable options.
 *
 * - <b>Binary</b><br>
 *   Binary output supports up to 64 digits and different group separators for nibbles, bytes,
 *   16-bit words and 32 bit words. (See #binNibbleGroupChar, #binByteGroupChar,
 *   #binWordGroupChar and #binWord32GroupChar ).<br>
 *   When parsing integers, a customizable literal string defined in #binLiteralPrefix might be used
 *   to auto-detect binary values.
 *
 * - <b>Hexadecimal</b><br>
 *   Hexadecimal output supports up to 16 digits (64-bit) and different group separators
 *   for bytes, 16-bit words and 32 bit words. (See #hexByteGroupChar, #hexWordGroupChar,
 *   and #hexWord32GroupChar).
 *   When parsing integers, a customizable literal string defined in #hexLiteralPrefix might be used
 *   to auto-detect hexadecimal values.
 *
 * - <b>Octal</b><br>
 *   Octal output supports up to 22 digits (64-bit) and different a group separator for groups
 *   of three digits defined with #octGroupChar.
 *   When parsing integers, a customizable literal string defined in #octLiteralPrefix might be used
 *   to auto-detect hexadecimal values.
 *
 * - <b>Floating Point</b><br>
 *   The width of the output is provided in two fields,
 *   #integralPartMinimumWidth and #fractionalPartWidth. While the integral part is
 *   a minimum width (and nothing is ever cut), the fractional part is fixed width.
 *   Values with higher fractional precision are rounded accordingly.
 *   Note that the parameter of the interface methods that may override the width, in the floating
 *   point case only affects the minimum width of the integral part.<br>
 *   The integral and fractional part of float values are separated by decimalPointChar.
 *   This field of-course has to be different from group separator #thousandsGroupChar, which can
 *   be activated using field #writeGroupChars.<br>
 *   Other important fields for writing and parsing floats are: #exponentSeparator,
 *   #INFLiteral, #NANLiteral, #writeExponentPlusSign, and #forceScientific.
 *
 * <b>Notes on Writing and Parsing Values:</b><br>
 * \attention
 *   For decimal output, the width (#decMinimumFieldWidth) is a minimum width. This mean, that
 *   bigger numbers are written in a higher width.
 *   This is \c not true for binary, hexadecimal and octal output. In these formats, the width
 *   is an absolute value. Higher digits of numbers are just not written. The advantage of this
 *   is that no masking is needed when just the lower part of an integer number should be written.
 *   However, numbers might of-course change when cut and parsed back later!
 *
 * All of the integer formats have in common that the output width given is including optional
 * grouping characters. For example if a width of \b 5 was given for decimal output, the value
 * \c 12 would be written \c "0,012", hence \b 4 digits plus the grouping character. If grouping
 * was disabled, the output became \c "00012", hence one digit more but the same width.
 * In contrast to that, any sign that is written is \c not counted in the width.
 *
 * When parsing values, grouping characters are ignored at any position within the digits,
 * except of the start. The same is true for whitespace characters as defined in
 * #whitespaces. When this field is nulled or empty, then white spaces are \b not ignored.
 * This might be helpful in some cases where occurrence of white space characters should
 * indicate an error (or something else) when parsing.
 * Otherwise, the characters defined in this field are ignored at two places: at the beginning
 * of a parsing operation and after a sign character was read.
 *
 * When parsing fails, a value of \c 0 (respectively \c 0.0) is returned.
 * User-friendly classes that use the interface of this type will detect such failure
 * through the output parameter of the parsing methods, which indicates the end of the number
 * found.
 *
 * For each of the four integer formats, decimal, binary, hexadecimal and octal, dedicated
 * parsing methods exist. Those do not accept literal prefix identifiers as defined in
 * fields #binLiteralPrefix, #hexLiteralPrefix and #octLiteralPrefix. Those are
 * identified by method #parseInt, which aggregates the other four parsing methods.<br>
 * There is no corresponding method defined that writes the literal prefix. When writing
 * binary, hexadecimal or octal values, such prefixes have to be prepended 'manually'.
 *
 * <b>ALib for Java Specifics:</b><br>
 * - As Java does not support unsigned integer types, there is a limitation in reading unsigned
 *   values above \b Long.MAX_INT (e.g. written with other language implementations of ALib).
 *   From a 'bitwise' perspective, the methods are working well. For example, long value
 *   \b -1 is written as <b>0xFFFF'FFFF'FFFF'FFFF</b>
 * - As Java is missing reference parameter passing (aka output parameters), the parsing
 *   methods accept an output parameter of type \b int[]. The return value will be stored in the
 *   first value of this array.
 **************************************************************************************************/
public class NumberFormat
{
    /** ********************************************************************************************
     * Constant long values for 10 ^(0...18) needed by conversion methods.
     **********************************************************************************************/
    protected static long pow10_0to18[]=
    {
                           1L, // 10^ 0
                          10L, // 10^ 1
                         100L, // 10^ 2
                        1000L, // 10^ 3
                       10000L, // 10^ 4
                      100000L, // 10^ 5
                     1000000L, // 10^ 6
                    10000000L, // 10^ 7
                   100000000L, // 10^ 8
                  1000000000L, // 10^ 9
                 10000000000L, // 10^10
                100000000000L, // 10^11
               1000000000000L, // 10^12
              10000000000000L, // 10^13
             100000000000000L, // 10^14
            1000000000000000L, // 10^15
           10000000000000000L, // 10^16
          100000000000000000L, // 10^17
         1000000000000000000L, // 10^18
    };

    /** temporary array used when null is given for 'return value array'. */
    protected static int[]  dummyNewIdx= new int[1];

    /** Special treatment for Long.MIN_VALUE: can not be converted to positive. */
    protected static char[] longMinValue    = "9#223#372#036#854#775#808".toCharArray();



    // #############################################################################################
    //  Fields
    // #############################################################################################

    /**
     * The default static number format object that acts as the
     * default settings of the currently running process.<br>
     * Method
     * \ref com::aworx::lib::ALIB::init "ALIB.init" invokes #setFromLocale() on this object and
     * switches grouping on.
     *
     * Classes providing functionality based on this class, might use this as a default
     * value for parameters of their interface methods.
     */

    public static  NumberFormat     global                                      =new NumberFormat();

    /**
     * A static number format object that may be used to write and parse numbers for 'computational'
     * use, which means, that grouping is switched off and decimal point character
     * is \c '.'.<br>
     * Method
     * \ref com::aworx::lib::ALIB::init "ALIB.init" invokes #setComputational on this object.
     * Note that using code that use this field without having invoked <b>ALIB.init</b> may
     * behave wrongly.
     *
     * Classes providing functionality based on this class, might use this as a default
     * value for parameters of their interface methods.
     */
    public static  NumberFormat     computational                               =new NumberFormat();

    // ###############################   Parsing  ###################################
    /**
     * Defines whitespace characters that are ignored when leading the number and after
     * the sign-character. Applies to methods #parseInt and #parseFloat. In contrast, methods
     * #parseDec, parseBin, parseHex and parseOct do not ignore any whitespace characters.
     */
    public char[]                   whitespaces;

    /**
     * Denotes if grouping characters are ignored when parsing numbers if they are given
     * (not set to \c '\0').
     * This applies to all number types.<br>
     * Defaults to \c false. If set to \c true, grouping characters are just skipped when
     * found while parsing numbers, no matter at which position they occur.
     */
    public boolean                 readGroupChars;

    // ###############################   Writing  ###################################
    /**
     * Denotes if grouping characters are written if they are given (not set to \c '\0').
     * This applies to all number types.<br>
     * Defaults to \c false.
     */
    public boolean                  writeGroupChars;

    // ############################ Floating point  numbers ###############################
    /**
     * Defines the decimal point character when converting a floating point number to a string
     * representation with method #writeFloat. Also, method #parseFloat uses the
     * character provided in this field for parsing the character.<br>
     * The field defaults to '.'. By invoking #setFromLocale(), the current locale's setting is
     * determined.
     */
    public  char                    decimalPointChar;

    /**
     * Defines the decimal exponent symbol of string representations of floating point numbers
     * when written or parsed in scientific notation by methods #parseFloat and #writeFloat.<br>
     * Method #parseFloat accepts characters 'e' and 'E' in addition to the string
     * set in this field.<br>
     * Defaults to \c 'E'.
     */
    public  String                  exponentSeparator;

    /** Defines what is written and parsed for infinite double values.  */
    public String                   INFLiteral;

    /** Defines what is written and parsed for double values that represent "not a number".   */
    public String                   NANLiteral;

    /**
     *  If \c true, the decimal point of floating point values is written, even if the fractional
     *  part of the float value is zero. If \c false, in this case the decimal point is omitted.<br>
     *  Defaults to \c true.
     */
    public boolean                  forceDecimalPoint;

    /**
     * Determines if positive exponent values are prepended with an explicit '+' character when
     * written using #writeFloat.<br>
     * Defaults to false, as some systems will not accept a plus sign on the exponent value.
     * Note that field #plusSign is not applicable for exponent numbers.
     */
    public  boolean                 writeExponentPlusSign;

    /**
     * Defines the minimum digits written for the integral part when converting a floating point
     * value into a string.<br>
     * If the integral part of the number provided has less digits
     * then leading '0' digits are added.<br>
     * The maximum value allowed is 15.<br>
     * A value of 0 leads to omitting the '0' before the
     * decimal separator in the case the value is below 1.0 and higher than -1.0 <br>
     * The default value is -1, which writes a minimum of 1 digit.
     *
     * When either this field or field #fractionalPartWidth is set to a positive value,
     * the limits to switch to scientific notation, which otherwise are fixed \c 10E-04 and
     * \c 10E+06, get extended. Method #writeFloat in this case keeps non-scientific notation
     * established if possible.
     */
    public int                      integralPartMinimumWidth;

    /**
     * Defines the number of digits written for the fractional part when converting a floating point
     * value into a string. (For integer conversion, see #decMinimumFieldWidth.)<br>
     * If the fractional part of the number provided has less digits then trailing '0'
     * digits are added.<br>
     * If the fractional part of the number provided has more digits then the fractional part is
     * rounded accordingly.<br>
     * The maximum value allowed is 15.<br>
     * The default value is -1, which writes as many digits as available in the provided float
     * variable, with a minimum of 1 digit.
     *
     * When either this field or field #integralPartMinimumWidth is set to a positive value,
     * the limits to switch to scientific notation, which otherwise are fixed \c 10E-04 and
     * \c 10E+06, get extended. Method #writeFloat in this case keeps non-scientific notation
     * established if possible.
     */
    public int                      fractionalPartWidth;

    /**
     * If this field is \c true, then trailing \c '0' digits in the fractional part of a floating
     * point value are not written, even if a #fractionalPartWidth is set.
     * Defaults to \c false.
     */
    public boolean                  omitTrailingFractionalZeros;

    /**
     * If \c true, scientific format is always used.<br>
     * If \c false (the default), method #writeFloat writes scientific format only if both fields,
     * #integralPartMinimumWidth and #fractionalPartWidth are evaluating to -1 and only for
     * numbers smaller than \c 10E-04 or larger than \c 10E+06.<br>
     *
     * If one of the fields #integralPartMinimumWidth or #fractionalPartWidth is set to a positive
     * value, these limits get extended. Method #writeFloat in this case keeps non-scientific
     * notation established if possible.
     */
    public  boolean                 forceScientific;

    // ############################ Float and integer numbers ###############################
    /**
     * Determines if positive values are prepended with an explicit character (usually '+') when
     * written using #writeFloat or #writeDecSigned.<br>
     * Defaults to \c 0 which omits the writing. Usual other values are of-course \c '+', but
     * also  <c>' '</c> (space) which supports better horizontal alignment of numbers when written in
     * columns. Note that this is not affecting exponent decimals of floating point values.
     * For those, see #writeExponentPlusSign
     */
    public char                     plusSign;

    /**
     * Defines the separator character for thousands when converting a number to a string
     * representation. In addition, this is used to identify thousand group symbols when
     * parsing decimal values. If set to \c '\0', no group separator is written and also when
     * parsing, a group separator is not accepted.
     * If set, still #writeGroupChars controls if it is written.<br>
     * Defaults to \c ','.
     * By invoking #setFromLocale(), the current locale's setting is determined.
     */
    public char                     thousandsGroupChar;

    /**
     * This character is written instead of a grouping character in the case that a certain
     * output width is requested but a grouping character would be the first character to write.
     * Writing this character instead, assures the field width be as requested.
     * Defaults to space (<c>' '</c>).
     */
    public char                     leadingGroupCharReplacement;

    // ################################  Base10 Integer numbers ####################################
    /**
     * Defines the minimum digits and grouping symbols written when writing integers in decimal.
     * format. If the value to write has less digits (and grouping symbols), then leading '0'
     * digits (and eventually grouping symbols) are added.<br> If the value to write has more
     * digits, then this field is ignored.
     * A sign character is not calculated into the writing width. To have negative and positive
     * numbers resulting in the same width, #plusSign has to be set to a value unequal to \c '\0'
     * (usually space character <c>' '</c> or \c '+').
     *
     * If this field is negative, it is ignored. Defaults to \c -1.
     */
    public int                      decMinimumFieldWidth;


    // ###################################  Binary numbers #########################################
    /**
     * Defines the digits written when writing binary values.
     * If the value has less digits, then leading '0' digits are added. If it has more, than
     * those digits are \b NOT written (!).<br>
     * The default value and minimum value is \c -1, which writes as many bits as necessary.
     */
    public int                      binFieldWidth;

    /** Defines the separator character for nibbles (4 bits) of binary numbers.
     *  Defaults to \c '\0' what disables reading and writing of nibble group characters.  */
    public char                     binNibbleGroupChar;

    /** Defines the separator character for bytes of binary numbers.
     *  Defaults to \c '\0' what chooses #binNibbleGroupChar.  */
    public char                     binByteGroupChar;

    /** Defines the separator character for 16-bit words  of binary numbers.
     *  Defaults to \c '\0' what chooses #binByteGroupChar.  */
    public char                     binWordGroupChar;

    /** Defines the separator character for 32-bit words  of binary numbers.
     *  Defaults to \c '\0' what chooses #binWordGroupChar.  */
    public char                     binWord32GroupChar;

    /** Used by method #parseInt to detect binary format of integer values. If nulled, no binary
     *  format is detected.
     *  Methods of this class are not writing the prefix. If desired, this has performed
     *  explicitly ("manually") prior to invoking a writing method of this class.<br>
     *  Defaults to \c "0b". */
    public com.aworx.lib.strings.AString binLiteralPrefix;

    // ###################################  Hex numbers ############################################
    /**
     * Defines the digits written when writing hexadecimal values.
     * If the value has less digits, then leading '0' digits are added. If it has more, than
     * those digits are \b NOT written (!).<br>
     * The default value and minimum value is \c -1, which writes as many bits as necessary.
     */
    public int                      hexFieldWidth;

    /**
     * If \c true, lower case letters \c 'a' - \c 'f' are written.
     * Defaults to \c false, which writes upper case letters \c 'A' - \c 'F'.
     */
    public boolean                  hexLowerCase;

    /** Defines the separator character for bytes of hexadecimal numbers.
     *  Defaults to \c '\0' what disables reading and writing of byte group characters.  */
    public char                     hexByteGroupChar;

    /** Defines the separator character for 16-bit words  of hexadecimal numbers.
     *  Defaults to \c '\0' what chooses #hexByteGroupChar.  */
    public char                     hexWordGroupChar;

    /** Defines the separator character for 32-bit words  of hexadecimal numbers.
     *  Defaults to \c '\0' what chooses #hexWordGroupChar.  */
    public char                     hexWord32GroupChar;

    /** Used by method #parseInt to detect hexadecimal format of integer values. If nulled, no
     *  hexadecimal format is detected.
     *  Methods of this class are not writing the prefix. If desired, this has performed
     *  explicitly ("manually") prior to invoking a writing method of this class.<br>
     *  Defaults to \c "0x". */
    public com.aworx.lib.strings.AString hexLiteralPrefix;

    // ###################################  Octal numbers ##########################################
    /**
     * Defines the digits written when writing hexadecimal values.
     * If the value has less digits, then leading '0' digits are added. If it has more, than
     * those digits are \b NOT written (!).<br>
     * The default value and minimum value is \c -1, which writes as many bits as necessary.
     */
    public int                      octFieldWidth;

    /** Defines the separator character for bytes of hexadecimal numbers. Defaults to \c ',
     *  Defaults to \c '\0' what disables reading and writing of byte group characters.  */
    public char                     octGroupChar;

    /** Used by method #parseInt to detect octal format of integer values. If nulled, no octal
     *  format is detected.
     *  Methods of this class are not writing the prefix. If desired, this has performed
     *  explicitly ("manually") prior to invoking a writing method of this class.<br>
     *  Defaults to \c "0o". */
    public com.aworx.lib.strings.AString octLiteralPrefix;

    // #############################################################################################
    //  protected fields
    // #############################################################################################
    /** Used for float conversion */
    protected static final long signMask =   Double.doubleToRawLongBits(-0.0) ^
                                             Double.doubleToRawLongBits(+0.0);

    /** Used for float conversion */
    protected static final long bitsNaN=     Double.doubleToRawLongBits( Double.NaN );

    /** Used for float conversion */
    protected static final long bitsInfPos=  Double.doubleToRawLongBits( Double.POSITIVE_INFINITY);

    /** Used for float conversion */
    protected static final long bitsInfNeg=  Double.doubleToRawLongBits( Double.NEGATIVE_INFINITY );

    // #############################################################################################
    //  Interface
    // #############################################################################################

    /** ********************************************************************************************
     * Constructor. Invokes #setComputational to reset all fields to their default values.
     **********************************************************************************************/
    public   NumberFormat() { setComputational(); }

    /** ********************************************************************************************
     * Resets the object to its default values. This method is called in the constructor.
     *
     * Decimal point character and grouping characters are set as follows:
     * <center>Field</center>         | <center>Value</center>
     * - - - - - - - - - - - - - - - -| - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - -
     * #decimalPointChar              |  \c .
     * #thousandsGroupChar            |  \c ,
     * #binNibbleGroupChar            |  \c '
     * #binByteGroupChar              |  \c -
     * #binWordGroupChar              |  <c>' '</c> (space)
     * #binWord32GroupChar            |  \c #
     * #hexWordGroupChar              |  \c '
     * #hexWord32GroupChar            |  \c '
     * #hexByteGroupChar              |  \c 0 (none)
     * #octGroupChar                  |  \c '
     *
     * The literal attributes are set as follows:
     * <center>Field</center>         | <center>Value</center>
     * - - - - - - - - - - - - - - - -| - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - -
     * #exponentSeparator             |  \c "E"
     * #INFLiteral                    |  \c "INF"
     * #NANLiteral                    |  \c "NAN"
     * #binLiteralPrefix              |  \c "0b"
     * #hexLiteralPrefix              |  \c "0x"
     * #octLiteralPrefix              |  \c "0o"
     *
     * All width-attributes are reset to "automatic mode", \c -1. The attributes are
     * #integralPartMinimumWidth,
     * #fractionalPartWidth,
     * #decMinimumFieldWidth,
     * #binFieldWidth,
     * #hexFieldWidth and
     * #octFieldWidth.
     *
     * Finally, the following further fields are reset to their default values:
     * <center>Field</center>         | <center>Value</center>
     * - - - - - - - - - - - - - - - -| - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - -
     * #writeGroupChars               |  \c false
     * #forceScientific               |  \c false
     * #forceDecimalPoint             |  \c true
     * #plusSign                      |  \c none (0)
     * #writeExponentPlusSign         |  \c false
     * #omitTrailingFractionalZeros   |  \c false
     * #hexLowerCase                  |  \c false
     * #whitespaces                   |  \ref com::aworx::lib::strings::CString::DEFAULT_WHITESPACES "DEFAULT_WHITESPACES"
     *
     *
     * \note
     *   With static object
     *   \ref com::aworx::lib::strings::NumberFormat::computational "NumberFormat.computational",
     *   there is a global singleton existing which can be used but must not be changed.
     **********************************************************************************************/
    public void setComputational()
    {
        decimalPointChar=               '.';
        forceDecimalPoint=              true;
        readGroupChars=
         writeGroupChars=
          omitTrailingFractionalZeros=
           writeExponentPlusSign=
            hexLowerCase=
             forceScientific=           false;
        whitespaces=                    com.aworx.lib.strings.CString.DEFAULT_WHITESPACES;
        plusSign=                       '\0';

        // literals
        exponentSeparator               = "E";
        INFLiteral                      = "INF";
        NANLiteral                      = "NAN";
        binLiteralPrefix                = new com.aworx.lib.strings.AString( "0b" );
        hexLiteralPrefix                = new com.aworx.lib.strings.AString( "0x" );
        octLiteralPrefix                = new com.aworx.lib.strings.AString( "0o" );

        // automatic field width (->minimum size of maximum accuracy)
        decMinimumFieldWidth=
         binFieldWidth=
          hexFieldWidth=
           octFieldWidth=
            integralPartMinimumWidth=
             fractionalPartWidth=       -1;

        // group characters
        leadingGroupCharReplacement=' ';
        thousandsGroupChar=         ',';
         binNibbleGroupChar=
         hexWordGroupChar=
          hexWord32GroupChar=
           octGroupChar=            '\'';

        hexByteGroupChar=           '\0';
        binByteGroupChar=           '\"';
        binWordGroupChar=           '-';
        binWord32GroupChar=         '=';

    }

    /** ********************************************************************************************
     * Copies all fields (settings) from the given object. If no object is provided, values of
     * the static singleton found in field #global are copied
     *
     * @param other  The \b %NumberFormat object to copy the values from.
     *               Defaults to \c null, which chooses the global singleton.
     **********************************************************************************************/
    public void    set( NumberFormat other )
    {
        if ( other == null )
            other= global;

        whitespaces                 = other.whitespaces                 ;
        readGroupChars              = other.readGroupChars              ;
        writeGroupChars             = other.writeGroupChars             ;
        decimalPointChar            = other.decimalPointChar            ;
        exponentSeparator           = other.exponentSeparator           ;
        INFLiteral                  = other.INFLiteral                  ;
        NANLiteral                  = other.NANLiteral                  ;
        forceDecimalPoint           = other.forceDecimalPoint;
        writeExponentPlusSign       = other.writeExponentPlusSign       ;
        integralPartMinimumWidth    = other.integralPartMinimumWidth    ;
        fractionalPartWidth         = other.fractionalPartWidth         ;
        omitTrailingFractionalZeros = other.omitTrailingFractionalZeros ;
        forceScientific             = other.forceScientific             ;
        plusSign                    = other.plusSign                    ;
        thousandsGroupChar          = other.thousandsGroupChar          ;
        leadingGroupCharReplacement = other.leadingGroupCharReplacement ;
        decMinimumFieldWidth        = other.decMinimumFieldWidth        ;
        binFieldWidth               = other.binFieldWidth               ;
        binNibbleGroupChar          = other.binNibbleGroupChar          ;
        binByteGroupChar            = other.binByteGroupChar            ;
        binWordGroupChar            = other.binWordGroupChar            ;
        binWord32GroupChar          = other.binWord32GroupChar          ;
        binLiteralPrefix            = other.binLiteralPrefix            ;
        hexLowerCase                = other.hexLowerCase                ;
        hexFieldWidth               = other.hexFieldWidth               ;
        hexByteGroupChar            = other.hexByteGroupChar            ;
        hexWordGroupChar            = other.hexWordGroupChar            ;
        hexWord32GroupChar          = other.hexWord32GroupChar          ;
        hexLiteralPrefix            = other.hexLiteralPrefix            ;
        octFieldWidth               = other.octFieldWidth               ;
        octGroupChar                = other.octGroupChar                ;
        octLiteralPrefix            = other.octLiteralPrefix            ;
    }

    /** ********************************************************************************************
     * Overloaded version of #set(NumberFormat) providing default parameter value \c null.
     **********************************************************************************************/
    public void    set() { set( null ); }

    /** ********************************************************************************************
     * Sets the field #decimalPointChar and #thousandsGroupChar to reflect the current
     * system locales' setting. No other values are changed.
     *
     * \note
     *   Static (global) object
     *   \ref com::aworx::lib::strings::NumberFormat::global "NumberFormat.global",
     *   implements an instance which has the right locale set (provided that
     *   \ref com::aworx::lib::ALIB::init "ALIB.init"
     *   was duly invoked by the process).
     *   Otherwise, this method might be used to initialize a custom object with default values
     *   to afterwards make some specific changes.
     **********************************************************************************************/
    public void setFromLocale()
    {
        DecimalFormatSymbols dfs=   DecimalFormatSymbols.getInstance();
        exponentSeparator=          dfs.getExponentSeparator();
        decimalPointChar=           dfs.getDecimalSeparator();
        thousandsGroupChar=         dfs.getGroupingSeparator();
    }

    /** ********************************************************************************************
     * Static method to read digits \c '0' to \c '9' into a positive integer value.
     *
     * @param buffer        The character array to read the value from.
     * @param idx           The start point for parsing within \p buffer.
     * @param maxIdx        The maximum index to look at. Must be smaller than the buffers' length.
     * @param[out] newIdx   Optional output parameter (in array position 0) that  Will be set to
     *                      point behind the last character consumed. If parsing fails, it will be
     *                      set to the value of parameter idx which indicates that no parsable
     *                      number was found.
     * @return The parsed value. In addition, the parameter \p newIdx is set to point to the
     *         first character behind any found number.
     **********************************************************************************************/
    public static long  parseDecDigits( char[] buffer, int idx, int maxIdx, int[] newIdx )
    {
        if ( newIdx == null )
            newIdx= dummyNewIdx;
        newIdx[0]= idx;
        if( idx > maxIdx )
            return 0;

        long    result=    0;
        while ( idx <= maxIdx )
        {
            char  c= buffer[ idx ];
            if ( c < '0' || c > '9' )
                break;

            result= ( result * 10 ) + ( c - '0' );

            idx++;
        }

        newIdx[0]= idx;
        return result;
    }


    /** ********************************************************************************************
     * Parses signed integer numbers, optionally in binary, hexadecimal or octal format.
     *
     * Leading characters defined in #whitespaces are ignored.
     * An optional sign character \c '+' or \c '-' is parsed. If found, again whitespace characters
     * may follow behind such sign and are ignored.
     *
     * Then, the method detects any literal prefixes as defined in fields #binLiteralPrefix,
     * #hexLiteralPrefix and #octLiteralPrefix (usually \c 0b, \c 0x and \c 0o) and
     * invokes one of the methods #parseDec, #parseBin, #parseHex or #parseOct.
     *
     * @param buffer        The character array to read the value from.
     * @param idx           The start point for parsing within \p buffer.
     * @param maxIdx        The maximum index to look at. Must be smaller than the buffers' length.
     * @param[out] newIdx   Optional output parameter (in array position 0) that  Will be set to
     *                      point behind the last character consumed. If parsing fails, it will be
     *                      set to the value of parameter idx which indicates that no parsable
     *                      number was found.
     * @return The parsed value. In addition, the parameter \p newIdx is set to point to the
     *         first character behind any found number.
     **********************************************************************************************/
    public long   parseInt( char[] buffer, int idx, int maxIdx, int[] newIdx )
    {
        if ( newIdx == null )
            newIdx= dummyNewIdx;
        newIdx[0]= idx;
        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.length )
            return 0;


        int origIdx= idx;
        if ( (idx= com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, idx, maxIdx - idx + 1,
                                               whitespaces , Inclusion.EXCLUDE
                                              )) < 0 )
            return 0;

        // read sign
        boolean negative;
        if ( (negative= (buffer[idx] == '-')) || buffer[idx] == '+' )
        {
            idx++;
            if ( (idx= com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, idx, maxIdx - idx + 1,
                                                   whitespaces , Inclusion.EXCLUDE
                                                    )) < 0 )
                return 0;
        }

        long result= 0;
        int oldIdx= idx;

        int prefixLen;

        // try parsing hexadecimal
        if(     ( prefixLen= hexLiteralPrefix.length()) > 0
            &&  ( idx + prefixLen <= maxIdx )
            &&  com.aworx.lib.strings.CString.containsAt( buffer,                     idx, prefixLen,
                                    hexLiteralPrefix.buffer(), 0,   prefixLen,
                                    Case.SENSITIVE )
            &&  com.aworx.lib.strings.CString.indexOf( buffer[ idx + prefixLen ], whitespaces ) < 0     )
        {
            idx+= prefixLen;
            result=  parseHex( buffer, idx, maxIdx, newIdx );
            if( newIdx[0] - prefixLen == oldIdx )
                idx-= prefixLen;
        }

        // try parsing binary
        else if(     (prefixLen= binLiteralPrefix.length()) > 0
                 &&  ( idx + prefixLen <= maxIdx )
                 &&  com.aworx.lib.strings.CString.containsAt( buffer,                     idx, prefixLen,
                                         binLiteralPrefix.buffer(), 0,   prefixLen,
                                         Case.SENSITIVE )
                 &&  com.aworx.lib.strings.CString.indexOf( buffer[ idx + prefixLen ], whitespaces ) < 0     )
        {
            idx+= prefixLen;
            result=  parseBin( buffer, idx, maxIdx, newIdx );
            if( newIdx[0] - prefixLen == oldIdx )
                idx-= prefixLen;
        }

        // try parsing octal
        else if(     (prefixLen= octLiteralPrefix.length()) > 0
                 &&  ( idx + prefixLen <= maxIdx )
                 &&  com.aworx.lib.strings.CString.containsAt( buffer,                     idx, prefixLen,
                                         octLiteralPrefix.buffer(), 0,   prefixLen,
                                         Case.SENSITIVE )
                 &&  com.aworx.lib.strings.CString.indexOf( buffer[ idx + prefixLen ], whitespaces ) < 0     )
        {
            idx+= prefixLen;
            result=  parseOct( buffer, idx, maxIdx, newIdx );
            if( newIdx[0] - prefixLen == oldIdx )
                idx-= prefixLen;
        }

        // parse decimal
        if ( idx == oldIdx )
        {
            result=  parseDec( buffer, idx, maxIdx, newIdx );
            if ( newIdx[0] == oldIdx )
                newIdx[0]= origIdx;
        }

        return negative ? - result
                        :   result;
    }

    /** ********************************************************************************************
     * Reads an unsigned integer value in decimal format from the given character array at the
     * given position.<br>
     * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail if found.
     * Whitespace and grouping characters, as defined in fields #whitespaces and #thousandsGroupChar
     * will be ignored, regardless on their position between digits. To suppress the parsing
     * of group characters set, field #thousandsGroupChar to <c>'\\0'</c>. To suppress whitespace
     * consumption before reading the value, set field #whitespaces to nulled or empty string.
     *
     * \note As Java does not support unsigned integer types, the value to read is limited to
     *       <c>Long.MAX_VALUE</c> in this implementation of ALib.
     *
     * @param buffer        The character array to read the value from.
     * @param idx           The start point for parsing within \p buffer.
     * @param maxIdx        The maximum index to look at. Must be smaller than the buffers' length.
     * @param[out] newIdx   Optional output parameter (in array position 0) that  Will be set to
     *                      point behind the last character consumed. If parsing fails, it will be
     *                      set to the value of parameter idx which indicates that no parsable
     *                      number was found.
     * @return The parsed value. In addition, the parameter \p newIdx is set to point to the
     *         first character behind any found number.
     **********************************************************************************************/
    public long parseDec( char[] buffer, int idx, int maxIdx, int[] newIdx )
    {
        if ( newIdx == null )
            newIdx= dummyNewIdx;
        newIdx[0]= idx;
        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.length )
            return 0;

        // read whitespaces
        idx= com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, idx, maxIdx - idx + 1, whitespaces , Inclusion.EXCLUDE );
        if( idx < 0 )
            return 0;

        // read number
        long    result=    0;
        boolean charFound= false;
        while ( idx <= maxIdx )
        {
            char  c= buffer[ idx ];
            if ( charFound && readGroupChars && c!='\0' && c == thousandsGroupChar  )
            {
                idx++;
                continue;
            }

            if ( c < '0' || c > '9' )
                break;

            charFound= true;
            result= ( result * 10 ) + ( c - '0' );

            idx++;
        }

        newIdx[0]= idx;

        return result;
    }

    /** ********************************************************************************************
     * Reads an unsigned integer value in decimal format from the given character array at the
     * given position.<br>
     * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail if found.
     * Whitespace and grouping characters, as defined in fields #whitespaces,
     * #binNibbleGroupChar, #binByteGroupChar, #binWordGroupChar and #binWord32GroupChar
     * will be ignored, regardless on their position between digits. To suppress the parsing
     * of group characters, set the fields to <c>'\\0'</c>. To suppress whitespace consumption,
     * set field #whitespaces to \c null or empty \c char[].<br>
     *
     * \note As Java does not support unsigned integer types, the value will be negative if
     *       bit number 64 is set.
     *
     * @param buffer        The character array to read the value from.
     * @param idx           The start point for parsing within \p buffer.
     * @param maxIdx        The maximum index to look at. Must be smaller than the buffers' length.
     * @param[out] newIdx   Optional output parameter (in array position 0) that  Will be set to
     *                      point behind the last character consumed. If parsing fails, it will be
     *                      set to the value of parameter idx which indicates that no parsable
     *                      number was found.
     * @return The parsed value. In addition, the parameter \p newIdx is set to point to the
     *         first character behind any found number.
     **********************************************************************************************/
    public long  parseBin( char[] buffer, int idx, int maxIdx, int[] newIdx )
    {
        if ( newIdx == null )
            newIdx= dummyNewIdx;
        newIdx[0]= idx;
        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.length )
            return 0;

        // read whitespaces
        idx= com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, idx, maxIdx - idx + 1, whitespaces , Inclusion.EXCLUDE );
        if( idx < 0 )
            return 0;

        // read number
        long    result=    0;
        boolean charFound= false;
        while ( idx <= maxIdx )
        {
            char c= buffer[idx];
            if (    charFound
                 && readGroupChars
                 && c != '\0'
                 && (    c == binNibbleGroupChar
                      || c == binByteGroupChar
                      || c == binWordGroupChar
                      || c == binWord32GroupChar )    )
            {
                idx++;
                continue;
            }

            if ( c == '0'  )
            {
                result<<= 1;
                idx++;
                charFound= true;
                continue;
            }

            if ( c == '1'  )
            {
                result<<= 1;
                result|=1;
                idx++;
                charFound= true;
                continue;
            }

            break;
        }

        // that's it
        newIdx[0]= idx;

        return result;
    }

    /** ********************************************************************************************
     * Reads an unsigned integer value in decimal format from the given character array at the
     * given position.<br>
     * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail if found.
     * Whitespace and grouping characters, as defined in fields #whitespaces,
     * #hexByteGroupChar, #hexWordGroupChar and #hexWord32GroupChar
     * will be ignored, regardless on their position between digits. To suppress the parsing
     * of group characters, set the fields to <c>'\\0'</c>. To suppress whitespace consumption,
     * set field #whitespaces to \c null or empty \c char[].<br>
     *
     * \note As Java does not support unsigned integer types, the value will be negative if
     *       bit number 64 is set.
     *
     * @param buffer        The character array to read the value from.
     * @param idx           The start point for parsing within \p buffer.
     * @param maxIdx        The maximum index to look at. Must be smaller than the buffers' length.
     * @param[out] newIdx   Optional output parameter (in array position 0) that  Will be set to
     *                      point behind the last character consumed. If parsing fails, it will be
     *                      set to the value of parameter idx which indicates that no parsable
     *                      number was found.
     * @return The parsed value. In addition, the parameter \p newIdx is set to point to the
     *         first character behind any found number.
     **********************************************************************************************/
    public long  parseHex( char[] buffer, int idx, int maxIdx, int[] newIdx )
    {
        if ( newIdx == null )
            newIdx= dummyNewIdx;
        newIdx[0]= idx;
        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.length )
            return 0;

        // read whitespaces
        idx= com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, idx, maxIdx - idx + 1, whitespaces , Inclusion.EXCLUDE );
        if( idx < 0 )
            return 0;

        // read number
        long    result=    0;
        boolean charFound= false;
        while ( idx <= maxIdx )
        {
            char c= buffer[idx];
            if (    charFound
                 && readGroupChars
                 && c != '\0'
                 && (    c == hexByteGroupChar
                      || c == hexWordGroupChar
                      || c == hexWord32GroupChar )    )
            {
                idx++;
                continue;
            }

            if ( c >= '0' && c <= '9' )
            {
                result<<= 4;
                result|=  (c - '0');
                idx++;
                charFound= true;
                continue;
            }

            if ( c >= 'A' && c <= 'F' )
            {
                result<<= 4;
                result|=  (c - 'A' + 10 );
                idx++;
                charFound= true;
                continue;
            }

            if ( c >= 'a' && c <= 'f' )
            {
                result<<= 4;
                result|=  (c - 'a' + 10 );
                idx++;
                charFound= true;
                continue;
            }

            break;
        }

        newIdx[0]= idx;

        return result;
    }

    /** ********************************************************************************************
     * Reads an unsigned integer value in decimal format from the given character array at the
     * given position.<br>
     * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail if found.
     * Whitespace and grouping characters, as defined in fields #whitespaces and #octGroupChar
     * will be ignored, regardless on their position between digits. To suppress the parsing
     * of group characters, set the field to <c>'\\0'</c>. To suppress whitespace consumption,
     * set field #whitespaces to \c null or empty \c char[].<br>
     *
     * \note As Java does not support unsigned integer types, the value will be negative if
     *       bit number 64 is set.
     *
     * @param buffer        The character array to read the value from.
     * @param idx           The start point for parsing within \p buffer.
     * @param maxIdx        The maximum index to look at. Must be smaller than the buffers' length.
     * @param[out] newIdx   Optional output parameter (in array position 0) that  Will be set to
     *                      point behind the last character consumed. If parsing fails, it will be
     *                      set to the value of parameter idx which indicates that no parsable
     *                      number was found.
     * @return The parsed value. In addition, the parameter \p newIdx is set to point to the
     *         first character behind any found number.
     **********************************************************************************************/
    public long  parseOct( char[] buffer, int idx, int maxIdx, int[] newIdx )
    {
        if ( newIdx == null )
            newIdx= dummyNewIdx;
        newIdx[0]= idx;
        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.length )
            return 0;

        // read whitespaces
        idx= com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, idx, maxIdx - idx + 1, whitespaces , Inclusion.EXCLUDE );
        if( idx < 0 )
            return 0;

        // read number
        long    result=    0;
        boolean charFound= false;
        while ( idx <= maxIdx )
        {
            char c= buffer[idx];
            if (    charFound
                 && readGroupChars
                 && c != 0
                 && c == octGroupChar )
            {
                idx++;
                continue;
            }

            if ( c >= '0' && c <= '7' )
            {
                result<<= 3;
                result|=  (c - '0');
                idx++;
                charFound= true;
                continue;
            }

            break;
        }

        // that's it
        newIdx[0]= idx;
        return result;
    }

    /** ********************************************************************************************
     * Reads an unsigned integer value in decimal format from the given character array at the
     * given position.<br>
     * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail if found.
     * and parsing will fail if found.<br>
     *
     * @param buffer   The character array to read the value from.
     * @param idx      The start index from where the float value is tried to be parsed.
     * @param maxIdx   The maximum index to look at. Must be smaller than the buffer length.
     * @param newIdx   Optional output variable (in array position 0) that will point to the
     *                 first character after the integer number that was parsed.
     *                 If parsing fails, it will be set to the value of parameter idx.
     *                 Therefore, this parameter can be used to check if a value was found.
     *
     * @return  The parsed value. In addition, on success, the output parameter newIdx is set
     *          to point to the first character behind any found float number.
     **********************************************************************************************/
    public double parseFloat( char[] buffer, int idx, int maxIdx,  int[] newIdx )
    {
        // initialize output
        if ( newIdx == null )
            newIdx= dummyNewIdx;
        newIdx[0]= idx;

        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.length )
            return 0.0;

        // read whitespaces
        idx= com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, idx, maxIdx - idx + 1, whitespaces , Inclusion.EXCLUDE );
        if ( idx < 0 )
            return 0.0;

        // +/- sign
        boolean negative;
        if  ( (negative= buffer[idx] == '-') || buffer[idx] == '+' )
            if( (idx= com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, idx + 1, maxIdx - idx, whitespaces , Inclusion.EXCLUDE ) ) < 0 )
                return 0.0;

        // NaN, Infinite
        if(     maxIdx - idx + 1 >= NANLiteral.length()
            &&  com.aworx.lib.strings.CString.compareTo(  NANLiteral, 0, NANLiteral.length(),
                                    buffer,   idx, NANLiteral.length(), Case.IGNORE ) == 0 )
        {
            newIdx[0]= idx + NANLiteral.length();
            return Double.NaN;
        }
        if(     maxIdx - idx + 1 >= INFLiteral.length()
            &&  com.aworx.lib.strings.CString.compareTo(  INFLiteral, 0, INFLiteral.length(),
                                    buffer,   idx, INFLiteral.length(), Case.IGNORE ) == 0 )
        {
            newIdx[0]= idx + INFLiteral.length();
            return negative ? Double.NEGATIVE_INFINITY : Double.POSITIVE_INFINITY;
        }

        // NaN
        if(     maxIdx - idx + 1 >= NANLiteral.length()
            &&  com.aworx.lib.strings.CString.compareTo(  NANLiteral, 0,   NANLiteral.length(),
                                    buffer,   idx, NANLiteral.length(),
                                    Case.IGNORE ) == 0 )
        {
            idx= idx + NANLiteral.length();
            return Double.NaN;
        }
        // Infinite
        if(     maxIdx - idx + 1 >= INFLiteral.length()
            &&  com.aworx.lib.strings.CString.compareTo(  INFLiteral, 0,   INFLiteral.length(),
                                    buffer,   idx, INFLiteral.length(),
                                    Case.IGNORE ) == 0 )
        {
            idx= idx + INFLiteral.length();
            return Double.NaN;
        }

        double result= 0.0;

        // read number before dot?
        char c= buffer[idx];
        if (  c != decimalPointChar )
        {
            if ( !Character.isDigit( c ) )
                return 0.0;

            result= parseDec( buffer, idx, maxIdx, newIdx );
            idx= newIdx[0];

            // no dot following?
            if (      idx > maxIdx
                  ||  buffer[idx] != decimalPointChar )
            {
                return negative ? -result : result;
            }
        }

        // consumeChar dot
        idx++;

        // read number after dot
        if ( idx <= maxIdx && Character.isDigit( buffer[idx] ) )
        {
            int oldIdx= idx;
            double intValue= NumberFormat.parseDecDigits( buffer, idx, maxIdx, newIdx );
            idx= newIdx[0];
            result+= ( intValue / Math.pow( 10, idx - oldIdx ) );
        }

        // read eNNN
        if ( idx <= maxIdx + exponentSeparator.length() )
        {
            boolean eSepFound=  false;
            if ( idx < maxIdx + exponentSeparator.length()
                && com.aworx.lib.strings.CString.compareTo( exponentSeparator, 0,   exponentSeparator.length(),
                                      buffer,                     idx, exponentSeparator.length(),
                                      Case.IGNORE ) == 0 )
            {
                eSepFound= true;
                idx+= exponentSeparator.length();
            }

            if (buffer[idx] == 'e' || buffer[idx] == 'E' )
            {
                eSepFound= true;
                idx++;
            }

            if (eSepFound & idx <= maxIdx)
            {
                boolean negativeE= false;
                if ( (negativeE= (buffer[idx] == '-') ) ||  buffer[idx] == '+' )
                    idx++;

                if( idx <= maxIdx )
                {
                    int exp= (int) NumberFormat.parseDecDigits( buffer, idx, maxIdx, newIdx );
                    idx= newIdx[0];
                    result*= Math.pow( 10.0, negativeE ? -exp : exp );
                }
            }
        }

        // that's it
        newIdx[0]= idx;
        return negative ? -result : result;
    }

    /** ********************************************************************************************
     * Converts the given long value to a string representation into a signed decimal format.<br>
     * For negative numbers, \c '-' is written, the sign of positive numbers (if any) depends
     * on field #plusSign. After that, the value is converted to positive and
     * #writeDecUnsigned is invoked.
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #decMinimumFieldWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    public int writeDecSigned( long value, char[] buffer, int idx, int overrideWidth )
    {
        int oldIdx= idx;

        // write sign and turn negative to positive
        if ( value >= 0 )
        {
            if ( plusSign != '\0' )
                buffer[idx++]= plusSign;
        }
        else
        {
            buffer[idx++]= '-';

            // special treatment for Long.MIN_VALUE
            if( value == Long.MIN_VALUE )
            {
                for( int i= 0; i < longMinValue.length; i++ )
                {
                    char c= longMinValue[i];
                    if ( c == '#' )
                    {
                        if( writeGroupChars && thousandsGroupChar != '\0' )
                            buffer[idx++]= thousandsGroupChar;

                    }
                    else
                        buffer[idx++]= c;

                }
                return idx;

            }

            // switch value
            value= -value;
        }

        int width= overrideWidth != 0 ? overrideWidth
                                      : decMinimumFieldWidth;
        if( idx != oldIdx && width > 1 )
        {
            width--;
        }

        return writeDecUnsignedImpl( value, buffer, idx, width );
    }

    /** ********************************************************************************************
     * Converts the given long value to a string representation in decimal format.<br>
     * Negative numbers have to be converted to positive values when invoking this method.
     * the digits and optional grouping characters. The method does not check any overflow within
     * the given character buffer.
     *
     * The maximum number of digits written is 19. In addition, grouping characters may be written
     * according the settings of fields #writeGroupChars, #thousandsGroupChar and
     * #leadingGroupCharReplacement.
     *
     * The minimum width of the output is taken from field #decMinimumFieldWidth unless overwritten
     * by parameter \p overrideWidth. If the width is greater than the sum of digits and
     * grouping characters found in \p value, then \c '0' digits are prepended between the sign and
     * the number.
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #decMinimumFieldWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    public int writeDecUnsigned( long value, char[] buffer, int idx, int overrideWidth )
    {
        int width= overrideWidth != 0 ? overrideWidth
                                      : decMinimumFieldWidth;
        return writeDecUnsignedImpl( value, buffer, idx, width );
    }


    /** ********************************************************************************************
     * Converts the given long value to a string representation in binary format.<br>
     * Negative numbers have to be converted to positive values when invoking this method.
     * the digits and optional grouping characters. The method does not check any overflow within
     * the given character buffer.
     *
     * The maximum number of digits written is 64. In addition, grouping characters may be written
     * according the settings of fields #writeGroupChars, #binNibbleGroupChar, #binByteGroupChar,
     * #binWordGroupChar, #binWord32GroupChar and #leadingGroupCharReplacement.
     *
     * The minimum width of the output is taken from field #binFieldWidth unless overwritten
     * by parameter \p overrideWidth. If the width is greater than digits found in \p value,
     * \c '0' digits are prepended. The width is taking group characters into account.
     *
     * \attention
     *  If the value is greater than can be represented by the output width, these greater
     *  digits are cut. This is true for this method as well as #writeHex and writeOct. The rational
     *  behind this is that this way, larger numbers do not need to be masked before writing.
     *  (In other words: it is assumed that there is a reason for providing the width).
     *
     * The literal prefix found in field #binLiteralPrefix is \b not written. The field is
     * only used for detecting formats with method #parseInt.
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #binFieldWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    public int  writeBin( long value, char[] buffer, int idx, int overrideWidth )
    {
        // how many digits in a grouping block?
        int groupWidth=    !writeGroupChars            ? 0
                         : binNibbleGroupChar  != '\0' ? 4
                         : binByteGroupChar    != '\0' ? 8
                         : binWordGroupChar    != '\0' ? 16
                         : binWord32GroupChar  != '\0' ? 32    :    0;

        // if the first "digit" is a separator, we will write a space instead.
        // (we do the best to keep the width of the output intact if given)
        int nextSeparator= 0; // 0: dont write, 1= space, 2 normal

        // adjust minDigits to 0..64 (if 0 demanded, 0 is given!)
        int digits = overrideWidth != 0 ? overrideWidth : binFieldWidth;
        if (digits > 0 )
        {
            if ( groupWidth != 0 )
            {
                nextSeparator=  digits<= groupWidth ? 0
                                :   (     digits >= groupWidth
                                      && (digits % (groupWidth + 1)) == 0 ) ? 1 : 2;

                digits-= digits / (groupWidth + 1); // subtract needed separators from digits
            }
        }

        // if negative value given, we calculate the needed digits
        if ( digits < 0  )
        {
            // zero value?
            if (value == 0)
                digits= 1;

            // calc
            else
            {
                if ( value < 0 )
                    digits= 64;
                else
                {
                    // rough
                    digits =    value < (1L <<  8) ? 8
                              : value < (1L << 16) ? 16
                              : value < (1L << 32) ? 32
                              : value < (1L << 48) ? 48  : 63;

                    // fine with loop
                    long actSize= (1L << (digits - 1));
                    while( value < actSize )
                    {
                        digits--;
                        actSize >>>= 1;
                    }
                }
            }
        }

        // check now for oversize
        if ( digits > 64 )
               digits= 64;

        long testValue= 1L << (digits - 1);
        while ( digits > 0)
        {
            // write the separator
            if( groupWidth != 0 && ( digits % groupWidth) == 0 )
            {
                if ( nextSeparator != 0 )
                    buffer[idx++]=  nextSeparator == 1     ? leadingGroupCharReplacement                    :
                                    ( digits % 32 == 0 )   ? binWord32GroupChar  :
                                    ( digits % 16 == 0 )   ? binWordGroupChar    :
                                    ( digits %  8 == 0 )   ? binByteGroupChar    : binNibbleGroupChar;
            }
            nextSeparator= 2; // from now on write separators

            // write digit
            buffer[idx++]= ( value & testValue ) == 0L ? '0' : '1';

            // next
            testValue >>>= 1;
            digits--;
        }

        return idx;
    }


    /** ********************************************************************************************
     * Converts the given long value to a string representation in hexadecimal format.<br>
     * Negative numbers have to be converted to positive values when invoking this method.
     * the digits and optional grouping characters. The method does not check any overflow within
     * the given character buffer.
     *
     * The maximum number of digits written is 16. In addition, grouping characters may be written
     * according the settings of fields #writeGroupChars, #hexByteGroupChar, #hexWordGroupChar,
     * #hexWord32GroupChar and #leadingGroupCharReplacement.
     *
     * The minimum width of the output is taken from field #hexFieldWidth unless overwritten
     * by parameter \p overrideWidth. If the width is greater than digits found in \p value,
     * \c '0' digits are prepended. The width is taking group characters into account.
     *
     * \attention
     *  If the value is greater than can be represented by the output width, these greater
     *  digits are cut. This is true for this method as well as #writeBin and writeOct. The rational
     *  behind this is that this way, larger numbers do not need to be masked before writing.
     *  (In other words: it is assumed that there is a reason for providing the width).
     *
     * The literal prefix found in field #hexLiteralPrefix is \b not written. The field is
     * only used for detecting formats with method #parseInt.
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #hexFieldWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    public int writeHex( long    value, char[] buffer, int idx, int overrideWidth )
    {
        char characterA = hexLowerCase ? 'a' : 'A';

        // how many digits in a grouping block?
        int groupWidth=   !writeGroupChars            ? 0
                        : hexByteGroupChar    != '\0' ? 2
                        : hexWordGroupChar    != '\0' ? 4
                        : hexWord32GroupChar  != '\0' ? 8    :    0;

        // if the first "digit" is a separator, we will write a space instead.
        // (we do the best to keep the width of the output intact if given)
        int nextSeparator= 0; // 0: dont write, 1= space, 2 normal

        // adjust minDigits to 0..64 (if 0 demanded, 0 is given!)
        int digits = overrideWidth != 0 ? overrideWidth : hexFieldWidth;
        if (digits > 0 )
        {
            if ( groupWidth != 0 )
            {
                nextSeparator=  digits<= groupWidth ? 0
                                :   (     digits >= groupWidth
                                      && (digits % (groupWidth + 1)) == 0 ) ? 1 : 2;

                digits-= digits / (groupWidth + 1); // subtract needed separators from digits
            }
        }

        // if negative value given, we calculate the needed digits
        if ( digits < 0  )
        {
            // zero value?
            if (value == 0)
                digits= 1;

            // calc
            else
            {
                if ( value < 0 )
                    digits= 16;
                else
                {
                    // loop
                    digits= 1;

                    long testValue= 0xF;
                    while( value > testValue && digits < 16 )
                    {
                        digits++;
                        testValue= (testValue << 4) | 0xF;
                    }
                }
            }
        }

        // check now for oversize
        if ( digits > 16 )
               digits= 16;

        int           shiftBits= (digits -1 ) * 4;
        long testMask=  ((long) 15) << shiftBits;
        while ( digits > 0)
        {
            // write the separator
            if( groupWidth != 0 && ( digits % groupWidth) == 0 )
            {
                if ( nextSeparator != 0 )
                    buffer[idx++]=  nextSeparator == 1    ? leadingGroupCharReplacement                    :
                                    ( digits % 8 == 0 )   ? hexWord32GroupChar  :
                                    ( digits % 4 == 0 )   ? hexWordGroupChar    : hexByteGroupChar;
            }
            nextSeparator= 2; // from now on write separators

            // write digit
            int nibble= (int) ( ( value & testMask ) >>> shiftBits );
            buffer[idx++]= ( nibble < 10 )   ?  (char) ('0' + nibble)
                                             :  (char) (characterA + (nibble - 10));

            // next
            testMask  >>>= 4;
            shiftBits -=  4;
            digits--;
        }

        return idx;
    }

    /** ********************************************************************************************
     * Converts the given long value to a string representation in octal format.<br>
     * Negative numbers have to be converted to positive values when invoking this method.
     * the digits and optional grouping characters. The method does not check any overflow within
     * the given character buffer.
     *
     * The maximum number of digits written is 64. In addition, grouping characters may be written
     * according the settings of fields #writeGroupChars, #octGroupChar and
     * #leadingGroupCharReplacement.
     *
     * The minimum width of the output is taken from field #octFieldWidth unless overwritten
     * by parameter \p overrideWidth. If the width is greater than digits found in \p value,
     * \c '0' digits are prepended. The width is taking group characters into account.
     *
     * \attention
     *  If the value is greater than can be represented by the output width, these greater
     *  digits are cut. This is true for this method as well as #writeBin and writeHex. The rational
     *  behind this is that this way, larger numbers do not need to be masked before writing.
     *  (In other words: it is assumed that there is a reason for providing the width).
     *
     * The literal prefix found in field #octLiteralPrefix is \b not written. The field is
     * only used for detecting formats with method #parseInt.
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #octFieldWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
     public int writeOct( long value, char[] buffer, int idx, int overrideWidth )
    {
        // how many digits in a grouping block?
        int groupWidth=    writeGroupChars && octGroupChar != '\0' ? 3 : 0;

        // if the first "digit" is a separator, we will write a space instead.
        // (we do the best to keep the width of the output intact if given)
        int nextSeparator= 0; // 0: dont write, 1= space, 2 normal

        // adjust minDigits to 0..64 (if 0 demanded, 0 is given!)
        int digits= overrideWidth != 0 ? overrideWidth : octFieldWidth;
        if (digits > 0 )
        {
            if ( groupWidth != 0 )
            {
                nextSeparator=  digits<= groupWidth ? 0
                                :   (     digits >= groupWidth
                                      && (digits % (groupWidth + 1)) == 0 ) ? 1 : 2;

                digits-= digits / (groupWidth + 1); // subtract needed separators from digits
            }
        }

        // if negative value given, we calculate the needed digits
        if ( digits < 0  )
        {
            // zero value?
            if (value == 0)
                digits= 1;

            // calc
            else
            {
                if ( value < 0 )
                    digits= 22;
                else
                {
                    //  loop
                    digits= 1;
                    long testValue= 0x7;
                    while( value > testValue && digits < 22 )
                    {
                        digits++;
                        testValue= (testValue << 3 ) | 7;
                    }
               }
            }
        }

        // check now for oversize
        if ( digits > 22 )
               digits= 22;

        int           shiftBits= (digits -1 ) * 3;
        while ( digits > 0)
        {
            // write the separator
            if( groupWidth != 0 && ( digits % groupWidth) == 0 )
            {
                if ( nextSeparator != 0 )
                    buffer[idx++]=  nextSeparator == 1    ? leadingGroupCharReplacement : octGroupChar;
            }
            nextSeparator= 2; // from now on write separators

            // write digit
            int octet= (int) ( ( value & (((long) 7) << shiftBits) ) >>> shiftBits );
            buffer[idx++]= (char) ('0' + octet);

            // next
            shiftBits -=  3;
            digits--;
        }

        return idx;
    }

    /** ********************************************************************************************
     * Writes the given double value as string representation.
     *
     * Converts the given long value to a string representation.<br>
     * Negative numbers have to be converted to positive values when invoking this method.
     * the digits and optional grouping characters. The method does not check any overflow within
     * the given character buffer.
     *
     * Grouping characters are written according the settings of fields #writeGroupChars,
     * #thousandsGroupChar and #leadingGroupCharReplacement.
     *
     * The minimum width of the the integral part of the output is taken from field
     * #integralPartMinimumWidth unless overwritten by parameter \p overrideWidth.
     * If the width is greater than integral digits found in \p value,
     * \c '0' digits are prepended. The width is taking group characters into account.
     *
     * If field #fractionalPartWidth as well as the width of the integral part ( provided or set)
     * equals \c -1 the method may choose scientific notation. This is done, when for
     * numbers smaller than <c>10E-4</c> or larger than <c>10E+6</c>.<br>
     *
     * If the given value is not a number, #NANLiteral is written. If infinite, #INFLiteral.
     *
     * The output format is dependent on various further settings provided in the fields of
     * this class. Those are #decimalPointChar, #exponentSeparator,
     * #forceDecimalPoint, #writeExponentPlusSign and #forceScientific
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #integralPartMinimumWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    public int writeFloat( double value, char[] buffer, int idx, int overrideWidth )
    {
        int integralWidth = overrideWidth != 0 ? overrideWidth : integralPartMinimumWidth;

        long raw= Double.doubleToRawLongBits( value );
        if( raw == bitsNaN )        {   int len= NANLiteral.length();
                                        NANLiteral.getChars( 0, len, buffer, idx );
                                        idx+= len;
                                        return idx;
                                    }

        // negative? -> turn positive
        if ( (raw & signMask) == signMask )
        {
            buffer[idx++]= '-';
            value= -value;
        }
        else
        {
            if ( plusSign != '\0' )
                buffer[idx++]= plusSign;
        }

        if(   raw ==  bitsInfPos
           || raw ==  bitsInfNeg)   {   int len= INFLiteral.length();
                                        INFLiteral.getChars( 0, len, buffer, idx );
                                        idx+= len;
                                        return idx;
                                    }

        final int maxFloatSignificantDigits= 16;

        // calc dot position
        int  exp10=      value != 0.0   ? (int) Math.floor((Math.log10( value ) ))
                                        : 0;

        // decide if we are using scientific format (with e) or not
        boolean scientific=  (     forceScientific
                                || (  integralWidth < 0 && fractionalPartWidth < 0  &&  ( exp10 > 6 || exp10 <= -5 )  )
                                || (  integralWidth       > 0 && exp10 != 0 && exp10 >= (maxFloatSignificantDigits - integralWidth       - 1 ) )
                                || (  fractionalPartWidth > 0 && exp10 != 0 && exp10 >= (maxFloatSignificantDigits - fractionalPartWidth - 1 ) )
                             );

        integralWidth= Math.min( integralWidth,           15 );
        int fractionalDigits=       Math.min( fractionalPartWidth,15 );


        // result variables used for output
        long intPart;
        long fractPart;
        int unusedFractDigits;
        int firstNonZero;
        int intPartSize;

        // scientific output
        if ( scientific )
        {
            int dotPos=  maxFloatSignificantDigits - exp10;
            intPart=     (long) ( value * Math.pow( 10, dotPos ) );
            fractPart=   intPart %  pow10_0to18[ maxFloatSignificantDigits ];
            intPart=     intPart /  pow10_0to18[ maxFloatSignificantDigits ];
            intPartSize= 1;

            // determine first non zero fract number
            firstNonZero= 0;
            if ( fractPart > 0 )
            {
                com.aworx.lib.ALIB_DBG.ASSERT( maxFloatSignificantDigits - firstNonZero < 20);
                while ( fractPart < pow10_0to18[ maxFloatSignificantDigits - firstNonZero - 1 ] )
                    firstNonZero++;
                com.aworx.lib.ALIB_DBG.ASSERT( maxFloatSignificantDigits - firstNonZero > 0);
            }
            firstNonZero++;

            unusedFractDigits= fractionalDigits >= 0 ?  maxFloatSignificantDigits - fractionalDigits
                                                     :  1;
        }

         // normal output, number > 0
         else if (exp10 >= 0 )
         {
            intPartSize= maxFloatSignificantDigits - exp10;
            com.aworx.lib.ALIB_DBG.ASSERT( intPartSize > 0  && intPartSize <= maxFloatSignificantDigits );

            intPart=     (long) ( value * Math.pow( 10, intPartSize ) );
            fractPart=   intPart %  pow10_0to18[ intPartSize ];
            intPart=     intPart /  pow10_0to18[ intPartSize ];

            // determine first non zero fract number
            firstNonZero= 0;
            if ( fractPart > 0 )
            {
                com.aworx.lib.ALIB_DBG.ASSERT( intPartSize - firstNonZero < 20 );
                while ( fractPart < pow10_0to18[ intPartSize - firstNonZero - 1 ] )
                    firstNonZero++;
                com.aworx.lib.ALIB_DBG.ASSERT( intPartSize - firstNonZero > 0 );
            }
            firstNonZero++;

            unusedFractDigits= fractionalDigits >= 0 ?  intPartSize - fractionalDigits
                                                     :  1;
         }

        // normal output, number  < 0
        else
        {
            // just zeros? -> write them and return
            firstNonZero= -exp10;
            intPart=      0;
            intPartSize=  1;
            fractPart=    (long) ( value * Math.pow( 10, maxFloatSignificantDigits + firstNonZero) );
            unusedFractDigits= fractionalDigits >= 0  ?  maxFloatSignificantDigits - ( fractionalDigits - firstNonZero )
                                                      :  1;
         }

        // cut fract digits and round it up
        if (     (fractionalDigits < 0 || fractionalDigits  >= firstNonZero - 1 )
             &&  unusedFractDigits >  0
             &&  unusedFractDigits <= 18 )
        {

            long rest=      fractPart % pow10_0to18[ unusedFractDigits ];
                  fractPart= fractPart / pow10_0to18[ unusedFractDigits ];
            if ( rest > pow10_0to18[ unusedFractDigits ] / 2 )
            {
                fractPart++;
                int  overflowDigit= 0;
                boolean overflow=      false;
                while (     overflowDigit <= fractionalDigits
                        && !(overflow|= fractPart == pow10_0to18[ overflowDigit ])
                        &&  fractPart > pow10_0to18[ overflowDigit ]
                       )
                    overflowDigit++;

                if ( overflow )
                {
                    if ( overflowDigit == fractionalDigits )
                    {
                        fractPart= 0;
                        intPart++;
                    }
                    else
                    {
                        com.aworx.lib.ALIB_DBG.ASSERT( firstNonZero > 1 );
                        firstNonZero--;
                    }
                }
            }
        }

        // write int part
        if ( intPart != 0L || integralWidth != 0 )
            idx= writeDecUnsigned( intPart, buffer, idx, integralWidth );

        // write dot
        if ( fractionalDigits != 0 || forceDecimalPoint )
            buffer[idx++]=  decimalPointChar;

        // write fract part
        if (fractionalDigits != 0)
        {
            int fractZeros= firstNonZero - 1;
            if ( fractionalDigits > 0 && fractZeros > fractionalDigits )
                fractZeros= fractionalDigits;

            for ( int i= 0 ; i < fractZeros ; i++ )
                buffer[idx++]= '0';

            int     qtyDigits=        fractionalDigits - fractZeros;
            int     actDigit=         maxFloatSignificantDigits + 1;
            int     cntOmittedZeros=  0;
            int     cntDigits=        0;
            boolean printStarted=     false;
            while (    fractPart > 0
                    && ( qtyDigits< 0 || cntDigits < qtyDigits )
                  )
            {
                actDigit--;

                // get next d
                int digitValue=   (int) ( fractPart / pow10_0to18[actDigit] );

                com.aworx.lib.ALIB_DBG.ASSERT( digitValue >= 0 && digitValue <= 9 );

                // don't write, yet?
                if ( !  (printStarted|= (digitValue != 0)) )
                    continue;
                cntDigits++;

                // write digit unless its a '0'
                if ( digitValue == 0 )
                    cntOmittedZeros++;
                else
                {
                    for ( int i= 0; i< cntOmittedZeros ; i++ )
                        buffer[idx++]= '0';
                    cntOmittedZeros= 0;
                    buffer[idx++]= (char) ( 48 + digitValue ); // 48= '0'
                }

                // next
                fractPart=    fractPart % pow10_0to18[actDigit];
            }

            // assure that if -1 for fractDigits if given,at least 1 digit is printed
            if (fractionalDigits < 0 )
                qtyDigits= 1;

            // write omitted zeros
            if ( cntDigits < qtyDigits )
            {
                if ( omitTrailingFractionalZeros )
                {
                    if( cntDigits == 0 )
                        buffer[idx++]= '0';
                }
                else
                {
                    for ( int i= 0; i< cntOmittedZeros ; i++ )
                        buffer[idx++]= '0';
                    cntDigits+= cntOmittedZeros;

                    // write missing digits
                    for ( int i= cntDigits; i< qtyDigits; i++ )
                        buffer[idx++]= '0';
                }
            }
        }

        // write eNN
        if ( scientific )
        {
            exponentSeparator.getChars( 0, exponentSeparator.length(), buffer,  idx );
            idx+= exponentSeparator.length();

            if ( exp10 < 0 )
                buffer[idx++]= '-';
            else if ( writeExponentPlusSign )
                buffer[idx++]= '+';
            idx= writeDecUnsigned( exp10 >= 0 ? exp10 : -exp10, buffer, idx, 2 );
        }

        return idx;
    }

    // #############################################################################################
    //  Protected methods
    // #############################################################################################
    /** ********************************************************************************************
     * Implementation used by #writeDecSigned and writeDecUnsigned.
     *
     * @param value     The value to write.
     * @param buffer    The character array to write the value to. Needs to be long enough
     *                  (after \p idx) to carry the string written.
     * @param idx       The index within \p buffer to start writing.
     * @param width     The overall minimum width to write.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    protected int writeDecUnsignedImpl( long value, char[] buffer, int idx, int width )
    {
        // get requested width
        if ( width < 1  )   width=  1;

        // get the number of dec digits in value
        int digitsInValue;
        {
            // we have to treat the 0, so let's treat 0 to 9 then
            if( value < 10 )
                digitsInValue= 1;

            // binary search
            else
            {
                int lower=  1;
                int upper= 18;
                digitsInValue=    4;
                while( lower < upper  )
                {
                    if( value < pow10_0to18[digitsInValue] )
                        upper= digitsInValue -1;
                    else
                        lower= digitsInValue;
                    digitsInValue= ( lower + upper ) / 2 + 1;
                }
            }

            com.aworx.lib.ALIB_DBG.ASSERT_ERROR(     ( value == 0 && digitsInValue == 1 )
                                || (                             value >= pow10_0to18[ digitsInValue - 1 ]
                                     && ( digitsInValue == 19 || value <  pow10_0to18[ digitsInValue     ]) )
                                ,   "Error in digitsInValue calculation");
        }


        // calc printable digits and print leading groupchar replacement ' '
        int printDigits;
        {
            int requestedDigits;
            if ( writeGroupChars && thousandsGroupChar != '\0' )
            {
                if ( width > 26 )
                    width= 26;
                requestedDigits=  width - width / 4;
            }
            else
            {
                if ( width > 19 )
                    width= 19;
                requestedDigits= width;
            }

            printDigits= Math.max( requestedDigits, digitsInValue );


            // starts with group character? -> write space instead
            com.aworx.lib.ALIB_DBG.ASSERT_ERROR( width - 1 <= printDigits + (printDigits - 1) / 3 , "Invariant broken" );
            if( printDigits >1  && width > printDigits + (printDigits - 1) / 3 )
                buffer[idx++]= leadingGroupCharReplacement;
        }

        // main loop
        int  actDigit=      printDigits;
        while ( actDigit > 0 )
        {
            // print normal digit
            int digitValue=   (int) ( value / pow10_0to18[actDigit-1] );
            com.aworx.lib.ALIB_DBG.ASSERT( digitValue <= 9 );

            // write group character
            if(     writeGroupChars && thousandsGroupChar != '\0'
                &&  actDigit != printDigits
                &&  actDigit % 3 == 0
              )
                buffer[idx++]= thousandsGroupChar;

            // write character
            buffer[idx++]= (char) ( 48 + digitValue ); // 48= '0'

            // next
            value=    value % pow10_0to18[actDigit-1];

            actDigit--;
        }

        return idx;
    }


}  //  class NumberFormat



