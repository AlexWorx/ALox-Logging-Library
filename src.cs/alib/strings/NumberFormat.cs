// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


using System;
using System.Text;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;

namespace cs.aworx.lib.strings  {


/** ***********************************************************************************************
 * Defines various values needed to convert integer and floating point values
 * to string representations and vice versa.
 * In addition, this class provides methods that do such conversions on character array
 * buffers.
 *
 * \attention
 *   The methods of this class are not intended for the common use. Instead, use interface of
 *   classes
 *      \ref cs.aworx.lib.strings.AString   "AString",
 *      \ref cs.aworx.lib.strings.Substring "Substring" or
 *      \ref cs.aworx.lib.strings.format.Formatter "Formatter"
 *   to write and parse numbers, which accept an object of this type as parameters.
 *
 * <b>Defined Singletons and User-Defined Instances:</b><br>
 * Two static singletons of this class are defined which can be used wherever a number format object
 * is needed as a parameter:
 * - #Global<br>
 *   This is initialized with method
 *   \ref cs.aworx.lib.ALIB.Init "ALIB.Init" and reflects local specific settings.
 *
 * - #Computational<br>
 *   This is also initialized with method
 *   \ref cs.aworx.lib.ALIB.Init "ALIB.Init" and should be used for writing and parsing
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
 *   Supports optional minimum output width with field #DecMinimumFieldWidth,
 *   and definable thousands grouping character with field #ThousandsGroupChar, which can be
 *   activated with field #WriteGroupChars.<br>
 *   Furthermore, the plus-sign can be controlled (#PlusSign) to be either left out or be anything
 *   defined. Of-course, values \b ' ' and \b '+' are reasonable options.
 *
 * - <b>Binary</b><br>
 *   Binary output supports up to 64 digits and different group separators for nibbles, bytes,
 *   16-bit words and 32 bit words. (See #BinNibbleGroupChar, #BinByteGroupChar,
 *   #BinWordGroupChar and #BinWord32GroupChar ).<br>
 *   When parsing integers, a customizable literal string defined in #BinLiteralPrefix might be used
 *   to auto-detect binary values.
 *
 * - <b>Hexadecimal</b><br>
 *   Hexadecimal output supports up to 16 digits (64-bit) and different group separators
 *   for bytes, 16-bit words and 32 bit words. (See #HexByteGroupChar, #HexWordGroupChar,
 *   and #HexWord32GroupChar).
 *   When parsing integers, a customizable literal string defined in #HexLiteralPrefix might be used
 *   to auto-detect hexadecimal values.
 *
 * - <b>Octal</b><br>
 *   Octal output supports up to 22 digits (64-bit) and different a group separator for groups
 *   of three digits defined with #OctGroupChar.
 *   When parsing integers, a customizable literal string defined in #OctLiteralPrefix might be used
 *   to auto-detect hexadecimal values.
 *
 * - <b>Floating Point</b><br>
 *   The width of the output is provided in two fields,
 *   #IntegralPartMinimumWidth and #FractionalPartWidth. While the integral part is
 *   a minimum width (and nothing is ever cut), the fractional part is fixed width.
 *   Values with higher fractional precision are rounded accordingly.
 *   Note that the parameter of the interface methods that may override the width, in the floating
 *   point case only affects the minimum width of the integral part.<br>
 *   The integral and fractional part of float values are separated by decimalPointChar.
 *   This field of-course has to be different from group separator #ThousandsGroupChar, which can
 *   be activated using field #WriteGroupChars.<br>
 *   Other important fields for writing and parsing floats are: #ExponentSeparator,
 *   #INFLiteral, #NANLiteral, #WriteExponentPlusSign, and #ForceScientific.
 *
 * <b>Notes on Writing and Parsing Values:</b><br>
 * \attention
 *   For decimal output, the width (#DecMinimumFieldWidth) is a minimum width. This mean, that
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
 * #Whitespaces. When this field is nulled or empty, then white spaces are \b not ignored.
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
 * fields #BinLiteralPrefix, #HexLiteralPrefix and #OctLiteralPrefix. Those are
 * identified by method #ParseInt, which aggregates the other four parsing methods.<br>
 * There is no corresponding method defined that writes the literal prefix. When writing
 * binary, hexadecimal or octal values, such prefixes have to be prepended 'manually'.
 **************************************************************************************************/
public class NumberFormat
{
    /** ********************************************************************************************
     * Constant long values for 10 ^(0...18) needed by conversion methods.
     **********************************************************************************************/
    protected readonly static ulong[] pow10_0to19=
    {
                           1UL, // 10^ 0
                          10UL, // 10^ 1
                         100UL, // 10^ 2
                        1000UL, // 10^ 3
                       10000UL, // 10^ 4
                      100000UL, // 10^ 5
                     1000000UL, // 10^ 6
                    10000000UL, // 10^ 7
                   100000000UL, // 10^ 8
                  1000000000UL, // 10^ 9
                 10000000000UL, // 10^10
                100000000000UL, // 10^11
               1000000000000UL, // 10^12
              10000000000000UL, // 10^13
             100000000000000UL, // 10^14
            1000000000000000UL, // 10^15
           10000000000000000UL, // 10^16
          100000000000000000UL, // 10^17
         1000000000000000000UL, // 10^18
        10000000000000000000UL, // 10^19
    };

    // #############################################################################################
    //  public fields
    // #############################################################################################

    /**
     * The default static number format object that acts as the
     * default settings of the currently running process.<br>
     * Method
     * \ref cs.aworx.lib.ALIB.Init "ALIB.Init" invokes #SetFromLocale() on this object and
     * switches grouping on.
     *
     * Classes providing functionality based on this class, might use this as a default
     * value for parameters of their interface methods.
     */
    public static NumberFormat      Global                                      =new NumberFormat();

    /**
     * A static number format object that may be used to write and parse numbers for 'computational'
     * use, which means, that grouping is switched off and decimal point character
     * is \c '.'.<br>
     * Method
     * \ref cs.aworx.lib.ALIB.Init "ALIB.Init" invokes #SetComputational on this object.
     * Note that using code that use this field without having invoked <b>ALIB.Init</b> may
     * behave wrongly.
     *
     * Classes providing functionality based on this class, might use this as a default
     * value for parameters of their interface methods.
     */
    public static  NumberFormat     Computational                               =new NumberFormat();

    // ###############################   Parsing  ###################################
    /**
     * Defines whitespace characters that are ignored when leading the number and after
     * the sign-character. Applies to methods #ParseInt and #ParseFloat. In contrast, methods
     * #ParseDec, ParseBin, ParseHex and ParseOct do not ignore any whitespace characters.
     */
    public char[]                   Whitespaces                        = CString.DefaultWhitespaces;

    /**
     * Denotes if grouping characters are ignored when parsing numbers if they are given
     * (not set to \c '\0').
     * This applies to all number types.<br>
     * Defaults to \c false. If set to \c true, grouping characters are just skipped when
     * found while parsing numbers, no matter at which position they occur.
     */
    public bool                    ReadGroupChars;

    // ###############################   Writing  ###################################
    /**
     * Denotes if grouping characters are written if they are given (not set to \c '\0').
     * This applies to all number types.<br>
     * Defaults to \c false.
     */
    public bool                     WriteGroupChars;

    // ############################ Floating point  numbers ###############################
    /**
     * Defines the decimal point character when converting a floating point number to a string
     * representation with method #WriteFloat. Also, method #ParseFloat uses the
     * character provided in this field for parsing the character.<br>
     * The field defaults to '.'. By invoking #SetFromLocale(), the current locale's setting is
     * determined.
     */
    public char                     DecimalPointChar;

    /**
     * Defines the decimal exponent symbol of string representations of floating point numbers
     * when written or parsed in scientific notation by methods #ParseFloat and #WriteFloat.<br>
     * Method #ParseFloat accepts characters 'e' and 'E' in addition to the string
     * set in this field.<br>
     * Defaults to \c 'E'.
     */
    public String                   ExponentSeparator;


    /** Defines what is written and parsed for infinite double values.  */
    public String                   INFLiteral;

    /** Defines what is written and parsed for double values that represent "not a number".   */
    public String                   NANLiteral;

    /**
     *  If \c true, the decimal point of floating point values is written, even if the fractional
     *  part of the float value is zero. If \c false, in this case the decimal point is omitted.<br>
     *  Defaults to \c true.
     */
    public bool                     ForceDecimalPoint;

    /**
     * Determines if positive exponent values are prepended with an explicit '+' character when
     * written using #WriteFloat.<br>
     * Defaults to false, as some systems will not accept a plus sign on the exponent value.
     * Note that field #PlusSign is not applicable for exponent numbers.
     */
    public bool                     WriteExponentPlusSign;

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
     * When either this field or field #FractionalPartWidth is set to a positive value,
     * the limits to switch to scientific notation, which otherwise are fixed \c 10E-04 and
     * \c 10E+06, get extended. Method #WriteFloat in this case keeps non-scientific notation
     * established if possible.
     */
    public int                      IntegralPartMinimumWidth;

    /**
     * Defines the number of digits written for the fractional part when converting a floating point
     * value into a string. (For integer conversion, see #DecMinimumFieldWidth.)<br>
     * If the fractional part of the number provided has less digits then trailing '0'
     * digits are added.<br>
     * If the fractional part of the number provided has more digits then the fractional part is
     * rounded accordingly.<br>
     * The maximum value allowed is 15.<br>
     * The default value is -1, which writes as many digits as available in the provided float
     * variable, with a minimum of 1 digit.
     *
     * When either this field or field #IntegralPartMinimumWidth is set to a positive value,
     * the limits to switch to scientific notation, which otherwise are fixed \c 10E-04 and
     * \c 10E+06, get extended. Method #WriteFloat in this case keeps non-scientific notation
     * established if possible.
     */
    public int                      FractionalPartWidth;

    /**
     * If this field is \c true, then trailing \c '0' digits in the fractional part of a floating
     * point value are not written, even if a #FractionalPartWidth is set.
     * Defaults to \c false.
     */
    public bool                     OmitTrailingFractionalZeros;

    /**
     * If \c true, scientific format is always used.<br>
     * If \c false (the default), method #WriteFloat writes scientific format only if both fields,
     * #IntegralPartMinimumWidth and #FractionalPartWidth are evaluating to -1 and only for
     * numbers smaller than \c 10E-04 or larger than \c 10E+06.<br>
     *
     * If one of the fields #IntegralPartMinimumWidth or #FractionalPartWidth is set to a positive
     * value, these limits get extended. Method #WriteFloat in this case keeps non-scientific
     * notation established if possible.
     */
    public bool                     ForceScientific;

    // ############################ Float and integer numbers ###############################
    /**
     * Determines if positive values are prepended with an explicit character (usually '+') when
     * written using #WriteFloat or #WriteDecSigned.<br>
     * Defaults to \c 0 which omits the writing. Usual other values are of-course \c '+', but
     * also  <c>' '</c> (space) which supports better horizontal alignment of numbers when written in
     * columns. Note that this is not affecting exponent decimals of floating point values.
     * For those, see #WriteExponentPlusSign
     */
    public char                     PlusSign;


    /**
     * Defines the separator character for thousands when converting a number to a string
     * representation. In addition, this is used to identify thousand group symbols when
     * parsing decimal values. If set to \c '\0', no group separator is written and also when
     * parsing, a group separator is not accepted.
     * If set, still #WriteGroupChars controls if it is written.<br>
     * Defaults to \c ','.
     * By invoking #SetFromLocale(), the current locale's setting is determined.
     */
    public char                     ThousandsGroupChar;

    /**
     * This character is written instead of a grouping character in the case that a certain
     * output width is requested but a grouping character would be the first character to write.
     * Writing this character instead, assures the field width be as requested.
     * Defaults to space (<c>' '</c>).
     */
    public char                     LeadingGroupCharReplacement;

    // ################################  Base10 Integer numbers ####################################
    /**
     * Defines the minimum digits and grouping symbols written when writing integers in decimal.
     * format. If the value to write has less digits (and grouping symbols), then leading '0'
     * digits (and eventually grouping symbols) are added.<br> If the value to write has more
     * digits, then this field is ignored.
     * A sign character is not calculated into the writing width. To have negative and positive
     * numbers resulting in the same width, #PlusSign has to be set to a value unequal to \c '\0'
     * (usually space character <c>' '</c> or \c '+').
     *
     * If this field is negative, it is ignored. Defaults to \c -1.
     */
    public int                      DecMinimumFieldWidth;

    // ###################################  Binary numbers #########################################
    /**
     * Defines the digits written when writing binary values.
     * If the value has less digits, then leading '0' digits are added. If it has more, than
     * those digits are \b NOT written (!).<br>
     * The default value and minimum value is \c -1, which writes as many bits as necessary.
     */
    public int                      BinFieldWidth;

    /** Defines the separator character for nibbles (4 bits) of binary numbers.
     *  Defaults to \c '\0' what disables reading and writing of nibble group characters.  */
    public char                     BinNibbleGroupChar;

    /** Defines the separator character for bytes of binary numbers.
     *  Defaults to \c '\0' what chooses #BinNibbleGroupChar.  */
    public char                     BinByteGroupChar;

    /** Defines the separator character for 16-bit words  of binary numbers.
     *  Defaults to \c '\0' what chooses #BinByteGroupChar.  */
    public char                     BinWordGroupChar;

    /** Defines the separator character for 32-bit words  of binary numbers.
     *  Defaults to \c '\0' what chooses #BinWordGroupChar.  */
    public char                     BinWord32GroupChar;

    /** Used by method #ParseInt to detect binary format of integer values. If nulled, no binary
     *  format is detected.
     *  Methods of this class are not writing the prefix. If desired, this has performed
     *  explicitly ("manually") prior to invoking a writing method of this class. <br>
     *  Defaults to \c "0b". */
    public  AString                 BinLiteralPrefix;

    // ###################################  Hex numbers ############################################
    /**
     * Defines the digits written when writing hexadecimal values.
     * If the value has less digits, then leading '0' digits are added. If it has more, than
     * those digits are \b NOT written (!).<br>
     * The default value and minimum value is \c -1, which writes as many bits as necessary.
     */
    public int                      HexFieldWidth;

    /**
     * If \c true, lower case letters \c 'a' - \c 'f' are written.
     * Defaults to \c false, which writes upper case letters \c 'A' - \c 'F'.
     */
    public bool                     HexLowerCase;

    /** Defines the separator character for bytes of hexadecimal numbers.
     *  Defaults to \c '\0' what disables reading and writing of byte group characters.  */
    public char                     HexByteGroupChar;

    /** Defines the separator character for 16-bit words  of hexadecimal numbers.
     *  Defaults to \c '\0' what chooses #HexByteGroupChar.  */
    public char                     HexWordGroupChar;

    /** Defines the separator character for 32-bit words  of hexadecimal numbers.
     *  Defaults to \c '\0' what chooses #HexWordGroupChar.  */
    public char                     HexWord32GroupChar;

    /** Used by method #ParseInt to detect hexadecimal format of integer values. If nulled, no
     *  hexadecimal format is detected.
     *  Methods of this class are not writing the prefix. If desired, this has performed
     *  explicitly ("manually") prior to invoking a writing method of this class. <br>
     *  Defaults to \c "0bx". */
    public  AString                 HexLiteralPrefix;

    // ###################################  Octal numbers ##########################################
    /**
     * Defines the digits written when writing hexadecimal values.
     * If the value has less digits, then leading '0' digits are added. If it has more, than
     * those digits are \b NOT written (!).<br>
     * The default value and minimum value is \c -1, which writes as many bits as necessary.
     */
    public int                      OctFieldWidth;

    /** Defines the separator character for bytes of hexadecimal numbers.
     *  Defaults to \c '\0' what disables reading and writing of byte group characters.  */
    public char                     OctGroupChar;

    /** Used by method #ParseInt to detect octal format of integer values. If nulled, no octal
     *  format is detected.
     *  Methods of this class are not writing the prefix. If desired, this has performed
     *  explicitly ("manually") prior to invoking a writing method of this class. <br>
     *  Defaults to \c "0o". */
    public  AString                 OctLiteralPrefix;


    // #############################################################################################
    //  protected fields
    // #############################################################################################
    /** Bit mask to detect the sign from raw values. */
    public static readonly long SignMask =    BitConverter.DoubleToInt64Bits(-0.0)
                                            ^ BitConverter.DoubleToInt64Bits(+0.0);

    /** Bit mask to detect NaN values from raw values. */
    public static readonly long BitsNaN=     BitConverter.DoubleToInt64Bits( Double.NaN );

    /** Bit mask to detect positive infinite values from raw values. */
    public static readonly long BitsInfPos=  BitConverter.DoubleToInt64Bits( Double.PositiveInfinity);

    /** Bit mask to detect negative infinite values from raw values. */
    public static readonly long BitsInfNeg=  BitConverter.DoubleToInt64Bits( Double.NegativeInfinity );

    // #############################################################################################
    //  Interface
    // #############################################################################################
    /** ********************************************************************************************
     * Constructor. Invokes #SetComputational to reset all fields to their default values.
     **********************************************************************************************/
    public   NumberFormat() { SetComputational(); }

    /** ********************************************************************************************
     * Resets the object to its default values. This method is called in the constructor.
     *
     * Decimal point character and grouping characters are set as follows:
     * <center>Field</center>         | <center>Value</center>
     * - - - - - - - - - - - - - - - -| - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - -
     * #DecimalPointChar              |  \c .
     * #ThousandsGroupChar            |  \c ,
     * #BinNibbleGroupChar            |  \c '
     * #BinByteGroupChar              |  \c -
     * #BinWordGroupChar              |  <c>' '</c> (space)
     * #BinWord32GroupChar            |  \c #
     * #HexWordGroupChar              |  \c '
     * #HexWord32GroupChar            |  \c '
     * #HexByteGroupChar              |  \c 0 (none)
     * #OctGroupChar                  |  \c '
     *
     * The literal attributes are set as follows:
     * <center>Field</center>         | <center>Value</center>
     * - - - - - - - - - - - - - - - -| - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - -
     * #ExponentSeparator             |  \c "E"
     * #INFLiteral                    |  \c "INF"
     * #NANLiteral                    |  \c "NAN"
     * #BinLiteralPrefix              |  \c "0b"
     * #HexLiteralPrefix              |  \c "0x"
     * #OctLiteralPrefix              |  \c "0o"
     *
     * All width-attributes are reset to "automatic mode", \c -1. The attributes are
     * #IntegralPartMinimumWidth,
     * #FractionalPartWidth,
     * #DecMinimumFieldWidth,
     * #BinFieldWidth,
     * #HexFieldWidth and
     * #OctFieldWidth.
     *
     * Finally, the following further fields are reset to their default values:
     * <center>Field</center>         | <center>Value</center>
     * - - - - - - - - - - - - - - - -| - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - -
     * #WriteGroupChars               |  \c false
     * #ForceScientific               |  \c false
     * #ForceDecimalPoint             |  \c true
     * #PlusSign                      |  \c none (0)
     * #WriteExponentPlusSign         |  \c false
     * #OmitTrailingFractionalZeros   |  \c false
     * #HexLowerCase                  |  \c false
     * #Whitespaces                   |  \ref cs.aworx.lib.strings.CString.DefaultWhitespaces "DefaultWhitespaces"
     *
     * \note
     *   With static object
     *   \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational",
     *   there is a global singleton existing which can be used but must not be changed.
     **********************************************************************************************/
    public void SetComputational()
    {
        DecimalPointChar=               '.';
        ForceDecimalPoint=              true;
        ReadGroupChars=
         WriteGroupChars=
          OmitTrailingFractionalZeros=
           WriteExponentPlusSign=
            HexLowerCase=
             ForceScientific=           false;
        Whitespaces=                    CString.DefaultWhitespaces;
        PlusSign=                       '\0';

        // literals
        ExponentSeparator               = "E";
        INFLiteral                      = "INF";
        NANLiteral                      = "NAN";
        BinLiteralPrefix                = new AString( "0b" );
        HexLiteralPrefix                = new AString( "0x" );
        OctLiteralPrefix                = new AString( "0o" );

        // automatic field width (->minimum size of maximum accuracy)
        DecMinimumFieldWidth=
         BinFieldWidth=
          HexFieldWidth=
           OctFieldWidth=
            IntegralPartMinimumWidth=
             FractionalPartWidth=       -1;

        // group characters
        LeadingGroupCharReplacement=    ' ';
        ThousandsGroupChar=             ',';
        BinNibbleGroupChar=
         HexWordGroupChar=
          HexWord32GroupChar=
           OctGroupChar=                '\'';

        HexByteGroupChar=               '\0';
        BinByteGroupChar=               '-';
        BinWordGroupChar=               '=';
        BinWord32GroupChar=             '#';

    }

    /** ********************************************************************************************
     * Copies all fields (settings) from the given object. If no object is provided, values of
     * the static singleton found in field #Global are copied
     *
     * @param other  The \b %NumberFormat object to copy the values from.
     *               Defaults to \c null, which chooses the global singleton.
     **********************************************************************************************/
    public void    Set( NumberFormat other =null )
    {
        if ( other == null )
            other= Global;

        Whitespaces                 = other.Whitespaces                 ;
        ReadGroupChars              = other.ReadGroupChars              ;
        WriteGroupChars             = other.WriteGroupChars             ;
        DecimalPointChar            = other.DecimalPointChar            ;
        ExponentSeparator           = other.ExponentSeparator           ;
        INFLiteral                  = other.INFLiteral                  ;
        NANLiteral                  = other.NANLiteral                  ;
        ForceDecimalPoint           = other.ForceDecimalPoint           ;
        WriteExponentPlusSign       = other.WriteExponentPlusSign       ;
        IntegralPartMinimumWidth    = other.IntegralPartMinimumWidth    ;
        FractionalPartWidth         = other.FractionalPartWidth         ;
        OmitTrailingFractionalZeros = other.OmitTrailingFractionalZeros ;
        ForceScientific             = other.ForceScientific             ;
        PlusSign                    = other.PlusSign                    ;
        ThousandsGroupChar          = other.ThousandsGroupChar          ;
        LeadingGroupCharReplacement = other.LeadingGroupCharReplacement ;
        DecMinimumFieldWidth        = other.DecMinimumFieldWidth        ;
        BinFieldWidth               = other.BinFieldWidth               ;
        BinNibbleGroupChar          = other.BinNibbleGroupChar          ;
        BinByteGroupChar            = other.BinByteGroupChar            ;
        BinWordGroupChar            = other.BinWordGroupChar            ;
        BinWord32GroupChar          = other.BinWord32GroupChar          ;
        BinLiteralPrefix            = other.BinLiteralPrefix            ;
        HexLowerCase                = other.HexLowerCase                ;
        HexFieldWidth               = other.HexFieldWidth               ;
        HexByteGroupChar            = other.HexByteGroupChar            ;
        HexWordGroupChar            = other.HexWordGroupChar            ;
        HexWord32GroupChar          = other.HexWord32GroupChar          ;
        HexLiteralPrefix            = other.HexLiteralPrefix            ;
        OctFieldWidth               = other.OctFieldWidth               ;
        OctGroupChar                = other.OctGroupChar                ;
        OctLiteralPrefix            = other.OctLiteralPrefix            ;
    }

    /** ********************************************************************************************
     * Sets the field #DecimalPointChar and #ThousandsGroupChar to reflect the current
     * system locales' setting. No other values are changed.
     *
     * \note
     *   Static (global) object
     *   \ref cs.aworx.lib.strings.NumberFormat.Global "NumberFormat.Global",
     *   implements an instance which has the right locale set (provided that
     *   \ref cs.aworx.lib.ALIB.Init "ALIB.Init"
     *   was duly invoked by the process).
     *   Otherwise, this method might be used to initialize a custom object with default values
     *   to afterwards make some specific changes.
     **********************************************************************************************/
    public void SetFromLocale()
    {
        System.Globalization.NumberFormatInfo nfi= System.Globalization.NumberFormatInfo.CurrentInfo;
        DecimalPointChar=       nfi.NumberDecimalSeparator[0];
        ThousandsGroupChar=     nfi.NumberGroupSeparator[0];
    }

    // #############################################################################################
    //  Integer conversion
    // #############################################################################################

    /** ********************************************************************************************
     * Static method to read digits \c '0' to \c '9' into a positive integer value.
     *
     * @param      buffer   The string to read the value from.
     * @param[in,out] idx   The start point for parsing within \p buffer. Will be set to point
     *                      behind the last character consumed. If unchanged, this indicates
     *                      that no parsable number was found.
     * @param      maxIdx   The maximum index to look at. Must be smaller than the buffers' length.
     * @return The parsed value. In addition, on success, parameter \p idx is moved to point to the
     *         first character behind the parsed number.
     **********************************************************************************************/
    public static ulong ParseDecDigits( char[] buffer, ref int idx, int maxIdx )
    {
        // check
        if( idx > maxIdx )
            return 0;

        ulong  result=    0;
        while ( idx <= maxIdx )
        {
            char  c= buffer[ idx ];
            if ( c < '0' || c > '9' )
                break;

            result= ( result * 10 ) + ( (uint) ( c - '0' ) );
            idx++;
        }
        return result;
    }


    /** ********************************************************************************************
     * Parses signed integer numbers, optionally in binary, hexadecimal or octal format.
     *
     * Leading characters defined in #Whitespaces are ignored.
     * An optional sign character \c '+' or \c '-' is parsed. If found, again whitespace characters
     * may follow behind such sign and are ignored.
     *
     * Then, the method detects any literal prefixes as defined in fields #BinLiteralPrefix,
     * #HexLiteralPrefix and #OctLiteralPrefix (usually \c 0b, \c 0x and \c 0o) and
     * invokes one of the methods #ParseDec, #ParseBin, #ParseHex or #ParseOct.
     *
     * @param      buffer   The string to read the value from.
     * @param[in,out] idx   The start point for parsing within \p buffer. Will be set to point
     *                      behind the last character consumed. If unchanged, this indicates
     *                      that no parsable number was found.
     * @param      maxIdx   The maximum index to look at. Must be smaller than the buffers' length.
     * @return The parsed value. In addition, on success, parameter \p idx is moved to point to the
     *         first character behind the parsed number.
     **********************************************************************************************/
    public long   ParseInt( char[] buffer, ref int idx, int maxIdx )
    {
        if ( idx < 0 || idx > maxIdx )
            return 0;

        int pIdx= idx;
        if ( (pIdx= CString.IndexOfAnyInRegion( buffer, pIdx, maxIdx - pIdx + 1,
                                                Whitespaces , Inclusion.Exclude
                                                )) < 0 )
            return 0;

        // read sign
        bool negative;
        if ( (negative= (buffer[pIdx] == '-')) || buffer[pIdx] == '+' )
        {
            pIdx++;
            if ( (pIdx= CString.IndexOfAnyInRegion( buffer, pIdx, maxIdx - pIdx + 1,
                                                    Whitespaces , Inclusion.Exclude
                                                    )) < 0 )
                return 0;
        }

        ulong result=   0;
        int oldIdx=     pIdx;
        int prefixLen;

        // try parsing hexadecimal
        prefixLen= HexLiteralPrefix.Length();
        if(     (prefixLen= HexLiteralPrefix.Length()) > 0
            &&  ( pIdx + prefixLen <= maxIdx )
            &&  HexLiteralPrefix.CompareTo( buffer, Case.Sensitive, pIdx, prefixLen, 0, prefixLen  ) == 0
            &&  CString.IndexOf( Whitespaces, buffer[ pIdx + prefixLen ] ) < 0     )

        {
            pIdx+= prefixLen;
            result=  ParseHex( buffer, ref pIdx, maxIdx );
            if( pIdx - prefixLen == oldIdx )
                pIdx-= prefixLen;
        }

        // try parsing binary
        else if(     (prefixLen= BinLiteralPrefix.Length()) > 0
                 &&  ( pIdx + prefixLen <= maxIdx )
                 &&  BinLiteralPrefix.CompareTo( buffer, Case.Sensitive, pIdx, prefixLen, 0, prefixLen  ) == 0
                 &&  CString.IndexOf( Whitespaces, buffer[ pIdx + prefixLen ] ) < 0     )
        {
            pIdx+= prefixLen;
            result=  ParseBin( buffer, ref pIdx, maxIdx );
            if( pIdx - prefixLen == oldIdx )
                pIdx-= prefixLen;
        }

        // try parsing octal
        else if(     (prefixLen= OctLiteralPrefix.Length()) > 0
                 &&  ( pIdx + prefixLen <= maxIdx )
                 &&  OctLiteralPrefix.CompareTo( buffer, Case.Sensitive, pIdx, prefixLen, 0, prefixLen  ) == 0
                 &&  CString.IndexOf( Whitespaces, buffer[ pIdx + prefixLen ] ) < 0     )
        {
            pIdx+= prefixLen;
            result=  ParseOct( buffer, ref pIdx, maxIdx );
            if( pIdx - prefixLen == oldIdx )
                pIdx-= prefixLen;
        }

        // parse decimal
        if ( pIdx == oldIdx )
            result=  ParseDec( buffer, ref pIdx, maxIdx );

        // nothing found
        if ( pIdx == oldIdx )
            return 0;

        idx= pIdx;
        return negative ? - (long) result
                        :   (long) result;
    }


    /** ********************************************************************************************
     * Reads an unsigned (64bit) integer value in \b decimal format from the given character
     * array at the given position.<br>
     * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail if found.
     * Whitespace and grouping characters, as defined in fields #Whitespaces and #ThousandsGroupChar
     * will be ignored, regardless on their position between digits. To suppress the parsing
     * of group characters, set field #ThousandsGroupChar to <c>'\\0'</c>. To suppress whitespace
     * consumption before reading the value, set field #Whitespaces to nulled or empty string.
     *
     * @param      buffer   The string to read the value from.
     * @param[in,out] idx   The start point for parsing within \p buffer. Will be set to point
     *                      behind the last character consumed. If unchanged, this indicates
     *                      that no parsable number was found.
     * @param      maxIdx   The maximum index to look at. Must be smaller than the buffers' length.
     * @return The parsed value. In addition, on success, parameter \p idx is moved to point to the
     *         first character behind the parsed number.
     **********************************************************************************************/
    public ulong ParseDec( char[] buffer, ref int idx, int maxIdx )
    {
        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.Length )
            return 0;

        // read whitespaces
        int pIdx= CString.IndexOfAnyInRegion( buffer, idx, maxIdx - idx + 1, Whitespaces , Inclusion.Exclude );
        if ( pIdx < 0 )
             return 0;

        // read number
        bool  charFound= false;
        ulong result=    0;
        while ( pIdx <= maxIdx )
        {
            char  c= buffer[ pIdx ];
            if ( charFound && ReadGroupChars && c!='\0' && c == ThousandsGroupChar  )
            {
                pIdx++;
                continue;
            }

            if ( c < '0' || c > '9' )
                break;

            charFound= true;
            result= ( result * 10 ) + ( (uint) ( c - '0' ) );

            pIdx++;
        }

        if ( charFound )
            idx= pIdx;
        return result;
    }

    /** ********************************************************************************************
     * Reads an unsigned (64bit) integer value in \b decimal format from the given character
     * array at the given position.<br>
     * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail if found.
     * Whitespace and grouping characters, as defined in fields #Whitespaces,
     * #BinNibbleGroupChar, #BinByteGroupChar, #BinWordGroupChar and #BinWord32GroupChar
     * will be ignored, regardless on their position between digits. To suppress the parsing
     * of group characters, set the fields to <c>'\\0'</c>. To suppress whitespace consumption,
     * set field #Whitespaces to \c null or empty \c char[].<br>
     *
     * @param      buffer   The string to read the value from.
     * @param[in,out] idx   The start point for parsing within \p buffer. Will be set to point
     *                      behind the last character consumed. If unchanged, this indicates
     *                      that no parsable number was found.
     * @param      maxIdx   The maximum index to look at. Must be smaller than the buffers' length.
     * @return The parsed value. In addition, on success, parameter \p idx is moved to point to the
     *         first character behind the parsed number.
     **********************************************************************************************/
    public ulong  ParseBin( char[] buffer, ref int idx, int maxIdx )
    {
        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.Length )
            return 0;

        // read whitespaces
        int pIdx= CString.IndexOfAnyInRegion( buffer, idx, maxIdx - idx + 1, Whitespaces , Inclusion.Exclude );
        if ( pIdx < 0 )
             return 0;

        // read number
        bool  charFound= false;
        ulong result=    0;
        while ( pIdx <= maxIdx )
        {
            char c= buffer[pIdx];
            if (    charFound
                 && ReadGroupChars
                 && c != '\0'
                 && (    c == BinNibbleGroupChar
                      || c == BinByteGroupChar
                      || c == BinWordGroupChar
                      || c == BinWord32GroupChar )    )
            {
                pIdx++;
                continue;
            }

            if ( c == '0'  )
            {
                result<<= 1;
                pIdx++;
                charFound= true;
                continue;
            }

            if ( c == '1'  )
            {
                result<<= 1;
                result|=1;
                pIdx++;
                charFound= true;
                continue;
            }

            break;
        }

        if ( charFound )
            idx= pIdx;
            return result;
    }

    /** ********************************************************************************************
     * Reads an unsigned (64bit) integer value in \b decimal format from the given character
     * array at the given position.<br>
     * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail if found.
     * Whitespace and grouping characters, as defined in fields #Whitespaces,
     * #HexByteGroupChar, #HexWordGroupChar and #HexWord32GroupChar
     * will be ignored, regardless on their position between digits. To suppress the parsing
     * of group characters, set the fields to <c>'\\0'</c>. To suppress whitespace consumption,
     * set field #Whitespaces to \c null or empty \c char[].<br>
     *
     * @param      buffer   The string to read the value from.
     * @param[in,out] idx   The start point for parsing within \p buffer. Will be set to point
     *                      behind the last character consumed. If unchanged, this indicates
     *                      that no parsable number was found.
     * @param      maxIdx   The maximum index to look at. Must be smaller than the buffers' length.
     * @return The parsed value. In addition, on success, parameter \p idx is moved to point to the
     *         first character behind the parsed number.
     **********************************************************************************************/
    public ulong  ParseHex( char[] buffer, ref int idx, int maxIdx )
    {
        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.Length )
            return 0;

        // read whitespaces
        int pIdx= CString.IndexOfAnyInRegion( buffer, idx, maxIdx - idx + 1, Whitespaces , Inclusion.Exclude );
        if ( pIdx < 0 )
             return 0;

        // read number
        bool  charFound= false;
        ulong result=    0;
        while ( pIdx <= maxIdx )
        {
            char c= buffer[pIdx];
            if (    charFound
                 && ReadGroupChars
                 && c != '\0'
                 && (    c == HexByteGroupChar
                      || c == HexWordGroupChar
                      || c == HexWord32GroupChar )    )
            {
                pIdx++;
                continue;
            }

            if ( c >= '0' && c <= '9' )
            {
                result<<= 4;
                result|=  (uint) ( c - '0');
                pIdx++;
                charFound= true;
                continue;
            }

            if ( c >= 'A' && c <= 'F' )
            {
                result<<= 4;
                result|=  (uint) ( c - 'A' + 10 );
                pIdx++;
                charFound= true;
                continue;
            }

            if ( c >= 'a' && c <= 'f' )
            {
                result<<= 4;
                result|=  (uint) ( c - 'a' + 10 );
                pIdx++;
                charFound= true;
                continue;
            }


            break;
        }

        if ( charFound )
            idx= pIdx;
        return result;
    }

    /** ********************************************************************************************
     * Reads an unsigned (64bit) integer value in \b decimal format from the given character
     * array at the given position.<br>
     * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail if found.
     * Whitespace and grouping characters, as defined in fields #Whitespaces and #OctGroupChar
     * will be ignored, regardless on their position between digits. To suppress the parsing
     * of group characters, set the field to <c>'\\0'</c>. To suppress whitespace consumption,
     * set field #Whitespaces to \c null or empty \c char[].<br>
     *
     * @param      buffer   The string to read the value from.
     * @param[in,out] idx   The start point for parsing within \p buffer. Will be set to point
     *                      behind the last character consumed. If unchanged, this indicates
     *                      that no parsable number was found.
     * @param      maxIdx   The maximum index to look at. Must be smaller than the buffers' length.
     * @return The parsed value. In addition, on success, parameter \p idx is moved to point to the
     *         first character behind the parsed number.
     **********************************************************************************************/
    public ulong  ParseOct( char[] buffer, ref int idx, int maxIdx )
    {
        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.Length )
            return 0;

        // read whitespaces
        int pIdx= CString.IndexOfAnyInRegion( buffer, idx, maxIdx - idx + 1, Whitespaces , Inclusion.Exclude );
        if ( pIdx < 0 )
             return 0;

        // read number
        bool  charFound= false;
        ulong result=    0;
        while ( pIdx <= maxIdx )
        {
            char c= buffer[pIdx];
            if (    charFound
                 && ReadGroupChars
                 && c != 0
                 && c == OctGroupChar )
            {
                pIdx++;
                continue;
            }

            if ( c >= '0' && c <= '7' )
            {
                result<<= 3;
                result|=  (uint) (c - '0');
                pIdx++;
                charFound= true;
                continue;
            }

            break;
        }

        if ( charFound )
            idx= pIdx;
        return result;
    }

    /** ********************************************************************************************
     * Reads an unsigned (64bit) integer value in \b decimal format from the given character
     * array at the given position.<br>
     * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail if found.
     * and parsing will fail if found.<br>
     *
     * @param      buffer   The string to read the value from.
     * @param[in,out] idx   The start point for parsing within \p buffer. Will be set to point
     *                      behind the last character consumed. If unchanged, this indicates
     *                      that no parsable number was found.
     * @param      maxIdx   The maximum index to look at. Must be smaller than the buffers' length.
     * @return The parsed value. In addition, on success, parameter \p idx is moved to point to the
     *         first character behind the parsed number.
     **********************************************************************************************/
    public double ParseFloat( char[] buffer, ref int idx, int maxIdx )
    {
        if (idx < 0 ||  idx > maxIdx || maxIdx >= buffer.Length )
            return 0.0;

        // read whitespaces
        int pIdx= CString.IndexOfAnyInRegion( buffer, idx, maxIdx - idx + 1, Whitespaces , Inclusion.Exclude );
        if ( pIdx < 0 )
            return 0.0;

        // +/- sign
        bool negative;
        if  ( (negative= buffer[pIdx] == '-') || buffer[pIdx] == '+' )
            if( (pIdx= CString.IndexOfAnyInRegion( buffer, pIdx + 1, maxIdx - pIdx, Whitespaces , Inclusion.Exclude ) ) < 0 )
                return 0.0;

        // NaN, Infinite
        if(     maxIdx - pIdx + 1 >= NANLiteral.Length
            &&  CString.CompareTo(  NANLiteral, 0, NANLiteral.Length,
                                    buffer,   pIdx, NANLiteral.Length, Case.Ignore ) == 0 )
        {
            idx= pIdx + NANLiteral.Length;
            return Double.NaN;
        }
        if(     maxIdx - pIdx + 1 >= INFLiteral.Length
            &&  CString.CompareTo(  INFLiteral, 0, INFLiteral.Length,
                                    buffer,   pIdx, INFLiteral.Length, Case.Ignore ) == 0 )
        {
            idx= pIdx + INFLiteral.Length;
            return negative ? Double.NegativeInfinity : Double.PositiveInfinity;
        }



        double result= 0.0;

        // read number before dot?
        char c= buffer[pIdx];
        if ( c != DecimalPointChar )
        {
            if ( !Char.IsDigit( c ) )
                return 0.0;

            result= ParseDec( buffer, ref pIdx, maxIdx );

            // no dot following?
            if (      pIdx > maxIdx
                  ||  buffer[pIdx] != DecimalPointChar )
            {
                idx= pIdx;
                return negative ? -result : result;
            }
        }

        // consume dot
        pIdx++;

        // read number after dot
        if ( pIdx <= maxIdx && Char.IsDigit( buffer[pIdx] ) )
        {
            int oldIdx= pIdx;
            double intValue= NumberFormat.ParseDecDigits( buffer, ref pIdx, maxIdx );
            result+= ( intValue / Math.Pow( 10, pIdx - oldIdx ) );
        }

        // read eNNN
        if ( pIdx <= maxIdx + ExponentSeparator.Length )
        {
            bool eSepFound=  false;
            if (       pIdx < maxIdx + ExponentSeparator.Length
                   &&  CString.CompareTo(  ExponentSeparator, 0, ExponentSeparator.Length,
                                            buffer, pIdx, ExponentSeparator.Length,
                                            Case.Ignore ) == 0 )
            {
                pIdx+= ExponentSeparator.Length;
                eSepFound= true;
            }

            else if ( buffer[pIdx] == 'e' || buffer[pIdx] == 'E' )
            {
                eSepFound= true;
                pIdx++;
            }

            if (eSepFound & pIdx <= maxIdx)
            {
                bool negativeE= false;
                if ( (negativeE= (buffer[pIdx] == '-') ) ||  buffer[pIdx] == '+' )
                    pIdx++;

                if( pIdx <= maxIdx )
                {
                    int exp= (int) NumberFormat.ParseDecDigits( buffer, ref pIdx, maxIdx );
                    result*= Math.Pow( 10.0, negativeE ? -exp : exp );
                }
            }
        }


        // that's it
        idx= pIdx;
        return negative ? -result : result;
    }

    /** ********************************************************************************************
     * Converts the given long value to a string representation into a signed decimal format.<br>
     * For negative numbers, \c '-' is written, the sign of positive numbers (if any) depends
     * on field #PlusSign. After that, the value is converted to positive and
     * #WriteDecUnsigned is invoked.
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #DecMinimumFieldWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    public int WriteDecSigned( long value, char[] buffer, int idx, int overrideWidth )
    {
        int oldIdx= idx;

        // write sign and turn negative to positive
        ulong uvalue;
        if ( value >= 0 )
        {
            uvalue= (ulong) value;
            if ( PlusSign != '\0' )
                buffer[idx++]= PlusSign;
        }
        else
        {
            uvalue= (ulong) -value;
            buffer[idx++]= '-';
        }

        int width= overrideWidth != 0 ? overrideWidth
            : DecMinimumFieldWidth;
        if( idx != oldIdx && width > 1 )
        {
            width--;
        }

        return WriteDecUnsigned( uvalue, buffer, idx, width );
    }

    /** ********************************************************************************************
     * Converts the given long value to a string representation in decimal format.<br>
     * Negative numbers have to be converted to positive values when invoking this method.
     * the digits and optional grouping characters. The method does not check any overflow within
     * the given character buffer.
     *
     * The maximum number of digits written is 20. In addition, grouping characters may be written
     * according the settings of fields #WriteGroupChars, #ThousandsGroupChar and
     * #LeadingGroupCharReplacement.
     *
     * The minimum width of the output is taken from field #DecMinimumFieldWidth unless overwritten
     * by parameter \p overrideWidth. If the width is greater than the sum of digits and
     * grouping characters found in \p value, then \c '0' digits are prepended between the sign and
     * the number.
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #DecMinimumFieldWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/

    public int WriteDecUnsigned(ulong value, char[] buffer, int idx, int overrideWidth)
    {
        int width= overrideWidth != 0 ? overrideWidth
                                      : DecMinimumFieldWidth;
        return writeDecUnsigned( value, buffer, idx, width );
    }

    /** ********************************************************************************************
     * Converts the given long value to a string representation in binary format.<br>
     * Negative numbers have to be converted to positive values when invoking this method.
     * the digits and optional grouping characters. The method does not check any overflow within
     * the given character buffer.
     *
     * The maximum number of digits written is 64. In addition, grouping characters may be written
     * according the settings of fields #WriteGroupChars, #BinNibbleGroupChar, #BinByteGroupChar,
     * #BinWordGroupChar, #BinWord32GroupChar and #LeadingGroupCharReplacement.
     *
     * The minimum width of the output is taken from field #BinFieldWidth unless overwritten
     * by parameter \p overrideWidth. If the width is greater than digits found in \p value,
     * \c '0' digits are prepended. The width is taking group characters into account.
     *
     * \attention
     *  If the value is greater than can be represented by the output width, these greater
     *  digits are cut. This is true for this method as well as #WriteHex and WriteOct. The rational
     *  behind this is that this way, larger numbers do not need to be masked before writing.
     *  (In other words: it is assumed that there is a reason for providing the width).
     *
     * The literal prefix found in field #BinLiteralPrefix is \b not written. The field is
     * only used for detecting formats with method #ParseInt.
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #BinFieldWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    public int  WriteBin( ulong value, char[] buffer, int idx, int overrideWidth )
    {
        // how many digits in a grouping block?
        int groupWidth=    !WriteGroupChars            ? 0
                         : BinNibbleGroupChar  != '\0' ? 4
                         : BinByteGroupChar    != '\0' ? 8
                         : BinWordGroupChar    != '\0' ? 16
                         : BinWord32GroupChar  != '\0' ? 32    :    0;

        // if the first "digit" is a separator, we will write a space instead.
        // (we do the best to keep the width of the output intact if given)
        int nextSeparator= 0; // 0: dont write, 1= space, 2 normal

        // adjust minDigits to 0..64 (if 0 demanded, 0 is given!)
        int digits = overrideWidth != 0 ? overrideWidth : BinFieldWidth;;
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
                // rough
                digits =    value < (1L <<  8) ? 8
                          : value < (1L << 16) ? 16
                          : value < (1L << 32) ? 32
                          : value < (1L << 48) ? 48  : 64;

                // fine with loop
                ulong actSize= 1UL << (digits - 1);
                while( value < actSize )
                {
                    digits--;
                    actSize >>= 1;
                }
            }
        }

        // check now for oversize
        if ( digits > 64 )
               digits= 64;

        ulong testValue= 1UL << (digits - 1);
        while ( digits > 0)
        {
            // write the separator
            if( groupWidth != 0 && ( digits % groupWidth) == 0 )
            {
                if ( nextSeparator != 0 )
                    buffer[idx++]=  nextSeparator == 1     ? LeadingGroupCharReplacement             :
                                    ( digits % 32 == 0 )   ? BinWord32GroupChar  :
                                    ( digits % 16 == 0 )   ? BinWordGroupChar    :
                                    ( digits %  8 == 0 )   ? BinByteGroupChar    : BinNibbleGroupChar;
            }
            nextSeparator= 2; // from now on write separators

            // write digit
            buffer[idx++]= ( value & testValue ) == 0L ? '0' : '1';

            // next
            testValue >>= 1;
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
     * according the settings of fields #WriteGroupChars, #HexByteGroupChar, #HexWordGroupChar,
     * #HexWord32GroupChar and #LeadingGroupCharReplacement.
     *
     * The minimum width of the output is taken from field #HexFieldWidth unless overwritten
     * by parameter \p overrideWidth. If the width is greater than digits found in \p value,
     * \c '0' digits are prepended. The width is taking group characters into account.
     *
     * \attention
     *  If the value is greater than can be represented by the output width, these greater
     *  digits are cut. This is true for this method as well as #WriteBin and writeOct. The rational
     *  behind this is that this way, larger numbers do not need to be masked before writing.
     *  (In other words: it is assumed that there is a reason for providing the width).
     *
     * The literal prefix found in field #HexLiteralPrefix is \b not written. The field is
     * only used for detecting formats with method #ParseInt.
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #HexFieldWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    public int  WriteHex( ulong value, char[] buffer, int idx, int overrideWidth )
    {
        char characterA = HexLowerCase ? 'a' : 'A';

        // how many digits in a grouping block?
        int groupWidth=   !WriteGroupChars            ? 0
                        : HexByteGroupChar    != '\0' ? 2
                        : HexWordGroupChar    != '\0' ? 4
                        : HexWord32GroupChar  != '\0' ? 8    :    0;

        // if the first "digit" is a separator, we will write a space instead.
        // (we do the best to keep the width of the output intact if given)
        int nextSeparator= 0; // 0: dont write, 1= space, 2 normal

        // adjust minDigits to 0..64 (if 0 demanded, 0 is given!)
        int digits = overrideWidth != 0 ? overrideWidth : HexFieldWidth;
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
                if ( value >= 0x8000000000000000 )
                    digits= 16;
                else
                {
                    // loop
                    digits= 1;

                    ulong testValue= 0xF;
                    while( value > testValue )
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
        ulong testMask=  ((ulong) 15) << shiftBits;
        while ( digits > 0)
        {
            // write the separator
            if( groupWidth != 0 && ( digits % groupWidth) == 0 )
            {
                if ( nextSeparator != 0 )
                    buffer[idx++]=  nextSeparator == 1    ? LeadingGroupCharReplacement              :
                                    ( digits % 8 == 0 )   ? HexWord32GroupChar  :
                                    ( digits % 4 == 0 )   ? HexWordGroupChar    : HexByteGroupChar;
            }
            nextSeparator= 2; // from now on write separators

            // write digit
            int nibble= (int) ( ( value & testMask ) >> shiftBits );
            buffer[idx++]= ( nibble < 10 )   ?  (char) ('0' + nibble)
                                             :  (char) (characterA + (nibble - 10));

            // next
            testMask  >>= 4;
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
     * according the settings of fields #WriteGroupChars, #OctGroupChar and
     * #LeadingGroupCharReplacement.
     *
     * The minimum width of the output is taken from field #OctFieldWidth unless overwritten
     * by parameter \p overrideWidth. If the width is greater than digits found in \p value,
     * \c '0' digits are prepended. The width is taking group characters into account.
     *
     * \attention
     *  If the value is greater than can be represented by the output width, these greater
     *  digits are cut. This is true for this method as well as #WriteBin and writeHex. The rational
     *  behind this is that this way, larger numbers do not need to be masked before writing.
     *  (In other words: it is assumed that there is a reason for providing the width).
     *
     * The literal prefix found in field #OctLiteralPrefix is \b not written. The field is
     * only used for detecting formats with method #ParseInt.
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #OctFieldWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    public int WriteOct( ulong value, char[] buffer, int idx, int overrideWidth )
    {
        // how many digits in a grouping block?
        int groupWidth=   WriteGroupChars && OctGroupChar != '\0' ? 3 : 0;

        // if the first "digit" is a separator, we will write a space instead.
        // (we do the best to keep the width of the output intact if given)
        int nextSeparator= 0; // 0: dont write, 1= space, 2 normal

        // adjust minDigits to 0..64 (if 0 demanded, 0 is given!)
        int digits= overrideWidth != 0 ? overrideWidth : OctFieldWidth;
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
                if ( value >= 0x8000000000000000 )
                    digits= 22;
                else
                {
                    //  loop
                    digits= 1;
                    ulong testValue= 0x07;
                    while( value > testValue )
                    {
                        digits++;
                        testValue= (testValue << 3) | 0x7;
                    }
               }
            }
        }

        // check now for oversize
        if ( digits > 22 )
               digits= 22;

        int  shiftBits= (digits -1 ) * 3;
        while ( digits > 0)
        {
            // write the separator
            if( groupWidth != 0 && ( digits % groupWidth) == 0 )
            {
                if ( nextSeparator != 0 )
                    buffer[idx++]=  nextSeparator == 1    ? LeadingGroupCharReplacement : OctGroupChar;
            }
            nextSeparator= 2; // from now on write separators

            // write digit
            int octet= (int) ( ( value & (((ulong) 7) << shiftBits) ) >> shiftBits );
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
     * Grouping characters are written according the settings of fields #WriteGroupChars,
     * #ThousandsGroupChar and #LeadingGroupCharReplacement.
     *
     * The minimum width of the the integral part of the output is taken from field
     * #IntegralPartMinimumWidth unless overwritten by parameter \p overrideWidth.
     * If the width is greater than integral digits found in \p value,
     * \c '0' digits are prepended. The width is taking group characters into account.
     *
     * If field #FractionalPartWidth as well as the width of the integral part ( provided or set)
     * equals \c -1 the method may choose scientific notation. This is done, when for
     * numbers smaller than <c>10E-4</c> or larger than <c>10E+6</c>.<br>
     *
     * If the given value is not a number, #NANLiteral is written. If infinite, #INFLiteral.
     *
     * The output format is dependent on various further settings provided in the fields of
     * this class. Those are #DecimalPointChar, #ExponentSeparator,
     * #ForceDecimalPoint, #WriteExponentPlusSign and #ForceScientific
     *
     * @param value         The value to write.
     * @param buffer        The character array to write the value to. Needs to be long enough
     *                      (after \p idx) to carry the string written.
     * @param idx           The index within \p buffer to start writing.
     * @param overrideWidth May be used to override value of field #IntegralPartMinimumWidth.
     *                      Defaults to \c 0, which denotes to  use the fields' value.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    public int WriteFloat( double value, char[] buffer, int  idx, int overrideWidth )
    {
        int integralWidth = overrideWidth != 0 ? overrideWidth : IntegralPartMinimumWidth;;

        long raw=  BitConverter.DoubleToInt64Bits( value );
        if( raw == BitsNaN )        {  int len= NANLiteral.Length;
                                        NANLiteral.CopyTo( 0, buffer, idx, len );
                                        idx+= len;
                                        return idx;
                                    }


        // negative? -> turn positive
        if ( (raw & SignMask) == SignMask )
        {
            buffer[idx++]= '-';
            value= -value;
        }
        else
        {
            if ( PlusSign != '\0' )
                buffer[idx++]= PlusSign;
        }

        if(   raw ==  BitsInfPos
           || raw ==  BitsInfNeg)   {   int len= INFLiteral.Length;
                                        INFLiteral.CopyTo( 0, buffer, idx, len );
                                        idx+= len;
                                        return idx;
                                    }

        const int maxFloatSignificantDigits= 16;


        // calc dot position
        int  exp10=      value != 0.0   ? (int) Math.Floor((Math.Log10( value ) ))
                                        : 0;

        // decide if we are using scientific format (with e) or not
        bool scientific=  (     ForceScientific

                                || (  integralWidth < 0 && FractionalPartWidth < 0  &&  ( exp10 > 6 || exp10 <= -5 )  )
                                || (  integralWidth       > 0 && exp10 != 0 && exp10 >= (maxFloatSignificantDigits - integralWidth       - 1 ) )
                                || (  FractionalPartWidth > 0 && exp10 != 0 && exp10 >= (maxFloatSignificantDigits - FractionalPartWidth - 1 ) )
                            );


        integralWidth=         Math.Min( integralWidth,             15 );
        int fractionalDigits=  Math.Min( FractionalPartWidth, 15 );



        // result variables used for output
        ulong intPart;
        ulong fractPart;
        int unusedFractDigits;
        int firstNonZero;
        int intPartSize;

        // scientific output
        if ( scientific )
        {
            int dotPos=  maxFloatSignificantDigits - exp10;
            intPart=     (ulong) ( value * Math.Pow( 10, dotPos ) );
            fractPart=   intPart %  pow10_0to19[ maxFloatSignificantDigits ];
            intPart=     intPart /  pow10_0to19[ maxFloatSignificantDigits ];
            intPartSize= 1;

            // determine first non zero fract number
            firstNonZero= 0;
            if ( fractPart > 0 )
            {
                ALIB_DBG.ASSERT( maxFloatSignificantDigits - firstNonZero < 20);
                while ( fractPart < pow10_0to19[ maxFloatSignificantDigits - firstNonZero - 1 ] )
                    firstNonZero++;
                ALIB_DBG.ASSERT( maxFloatSignificantDigits - firstNonZero > 0);
            }
            firstNonZero++;

            unusedFractDigits= fractionalDigits >= 0 ?  maxFloatSignificantDigits - fractionalDigits
                                                     :  1;
        }

         // normal output, number > 0
         else if (exp10 >= 0 )
         {
            intPartSize= maxFloatSignificantDigits - exp10;
            ALIB_DBG.ASSERT( intPartSize > 0  && intPartSize <= maxFloatSignificantDigits );

            intPart=     (ulong) ( value * Math.Pow( 10, intPartSize ) );
            fractPart=   intPart %  pow10_0to19[ intPartSize ];
            intPart=     intPart /  pow10_0to19[ intPartSize ];

            // determine first non zero fract number
            firstNonZero= 0;
            if ( fractPart > 0 )
            {
                ALIB_DBG.ASSERT( intPartSize - firstNonZero < 20 );
                while ( fractPart < pow10_0to19[ intPartSize - firstNonZero - 1 ] )
                    firstNonZero++;
                ALIB_DBG.ASSERT( intPartSize - firstNonZero > 0 );
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
            fractPart=    (ulong) ( value * Math.Pow( 10, maxFloatSignificantDigits + firstNonZero) );
            unusedFractDigits= fractionalDigits >= 0 ?  maxFloatSignificantDigits - ( fractionalDigits - firstNonZero )
                                                     :  1;
         }

        // cut fract digits and round it up
        if (     (fractionalDigits < 0 || fractionalDigits  >= firstNonZero - 1 )
             &&  unusedFractDigits >  0
             &&  unusedFractDigits <= 18 )
        {

            ulong rest=      fractPart % pow10_0to19[ unusedFractDigits ];
                  fractPart= fractPart / pow10_0to19[ unusedFractDigits ];
            if ( rest > pow10_0to19[ unusedFractDigits ] / 2 )
            {
                fractPart++;
                int  overflowDigit= 0;
                bool overflow=      false;
                while (     overflowDigit <= fractionalDigits
                        && !(overflow|= fractPart == pow10_0to19[ overflowDigit ])
                        &&  fractPart > pow10_0to19[ overflowDigit ]
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
                        ALIB_DBG.ASSERT( firstNonZero > 1 );
                        firstNonZero--;
                    }
                }
            }
        }

        // write int part
        if ( intPart != 0L || integralWidth != 0 )
            idx= WriteDecUnsigned( intPart, buffer, idx, integralWidth );

        // write dot
        if ( fractionalDigits != 0 || ForceDecimalPoint )
            buffer[idx++]=  DecimalPointChar;


        // write fract part
        if (fractionalDigits != 0)
        {
            int fractZeros= firstNonZero - 1;
            if ( fractionalDigits > 0 && fractZeros > fractionalDigits )
                fractZeros= fractionalDigits;

            for ( int i= 0 ; i < fractZeros ; i++ )
                buffer[idx++]= '0';

            int  qtyDigits=        fractionalDigits - fractZeros;
            int  actDigit=         maxFloatSignificantDigits + 1;
            int  cntOmittedZeros=  0;
            int  cntDigits=        0;
            bool printStarted=     false;
            while (    fractPart > 0
                    && ( qtyDigits< 0 || cntDigits < qtyDigits )
                  )
            {
                actDigit--;

                // get next d
                uint digitValue=   (uint) ( fractPart / pow10_0to19[actDigit] );

                ALIB_DBG.ASSERT( digitValue <= 9 );

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
                fractPart=    fractPart % pow10_0to19[actDigit];
            }

            // assure that if -1 for fractDigits if given,at least 1 digit is printed
            if (fractionalDigits < 0 )
                qtyDigits= 1;

            // write omitted zeros
            if ( cntDigits < qtyDigits )
            {
                if ( OmitTrailingFractionalZeros )
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
            ExponentSeparator.CopyTo( 0, buffer, idx, ExponentSeparator.Length );
            idx+= ExponentSeparator.Length;

            if ( exp10 < 0 )
                buffer[idx++]= '-';
            else if ( WriteExponentPlusSign )
                buffer[idx++]= '+';

            idx= WriteDecUnsigned( (ulong) ( exp10 >= 0 ? exp10 : -exp10), buffer, idx, 2 );
        }

        return idx;
    }

    // #############################################################################################
    //  Protected methods
    // #############################################################################################
    /** ********************************************************************************************
     * Implementation used by #WriteDecSigned and WriteDecUnsigned.
     *
     * @param value     The value to write.
     * @param buffer    The character array to write the value to. Needs to be long enough
     *                  (after \p idx) to carry the string written.
     * @param idx       The index within \p buffer to start writing.
     * @param width     The overall minimum width to write.
     * @return  The index pointing to behind the last character written in \b buffer.
     **********************************************************************************************/
    protected int writeDecUnsigned( ulong value, char[] buffer, int idx, int width )
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
                int upper= 19;
                digitsInValue=    4;
                while( lower < upper  )
                {
                    if( value < pow10_0to19[digitsInValue] )
                        upper= digitsInValue -1;
                    else
                        lower= digitsInValue;
                    digitsInValue= ( lower + upper ) / 2 + 1;
                }
            }

            ALIB_DBG.ASSERT_ERROR(     ( value == 0 && digitsInValue == 1 )
                                   || (                             value >= pow10_0to19[ digitsInValue - 1 ]
                                                                    && ( digitsInValue == 20 || value <  pow10_0to19[ digitsInValue     ]) )
                ,   "Error in digitsInValue calculation");
        }


        // calc printable digits and print leading groupchar replacement ' '
        int printDigits;
        {
            int requestedDigits;
            if ( WriteGroupChars && ThousandsGroupChar != '\0' )
            {
                if ( width > 26 )
                    width= 26;
                requestedDigits=  width - width / 4;
            }
            else
            {
                if ( width > 20 )
                    width= 20;
                requestedDigits= width;
            }

            printDigits= Math.Max( requestedDigits, digitsInValue );


            // starts with group character? -> write space instead
            ALIB_DBG.ASSERT_ERROR( width - 1 <= printDigits + (printDigits - 1) / 3 , "Invariant broken" );
            if( printDigits >1  && width > printDigits + (printDigits - 1) / 3 )
                buffer[idx++]= LeadingGroupCharReplacement;
        }

        // main loop
        int  actDigit=      printDigits;
        while ( actDigit > 0 )
        {
            // print normal digit
            int digitValue=   (int) ( value / pow10_0to19[actDigit-1] );
            ALIB_DBG.ASSERT( digitValue <= 9 );

            // write group character
            if(     WriteGroupChars && ThousandsGroupChar != '\0'
                    &&  actDigit != printDigits
                    &&  actDigit % 3 == 0
            )
                buffer[idx++]= ThousandsGroupChar;

            // write character
            buffer[idx++]= (char) ( 48 + digitValue ); // 48= '0'

            // next
            value=    value % pow10_0to19[actDigit-1];

            actDigit--;
        }

        return idx;
    }

} // class NumberFormat

} // namespace / EOF
