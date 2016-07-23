// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_STRINGS_NUMBERFORMAT)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_STRINGS_NUMBERFORMAT
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_STRINGS_NUMBERFORMAT 1
#endif

// #################################################################################################
// includes
// #################################################################################################

namespace aworx {
namespace           lib {
namespace                   strings {

/** ********************************************************************************************
 * By providing this class, ALib brings it's own implementation for converting integer
 * and double values to character string representations and vice versa.
 * This was implemented for the following reasons:
 * - To avoid problems with locale specific formats, especially the decimal separator
 *   character, which sometimes is ' . ' and sometimes is ' , '. This definition generally is
 *   a process wide setting, leading to race conditions in multi-threaded
 *   applications, which are a common source of faults and addressing them introduces
 *   another performance overhead.
 * - To be able to parse different formats without switching the locale (and even with being
 *   tolerant about format that is read)
 * - The possibility for the calling code to receive information about the location
 *   (the end) of a parsed floating point value, to continue processing a string
 *   behind this location.
 * - Cross language/platform source compatibility (the essential motivation for having ALib)
 * - Performance optimization (C# and Java versions avoid unnecessary temporary object
 *   allocations)
 *
 * As an example, when writing float data into a configuration file, class
 * \ref aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin" ignores the systems locale
 * setting and writes all data using '.' as decimal separator. When reading values, both ' . '
 * and ' , ' are accepted. While loosing the possibility to read configuration data that
 * uses a "thousand separator" which is generally the opposite of the decimal separator
 * (opposite here means it is a ',' when decimal separator is a '.' and vice versa), what
 * is gained is that floats are read without throwing exceptions regardless of the locale
 * that was set when they were written. Therefore configuration files are consistent
 * and readable across all software installations.
 *
 * Instances created, have default values set, independent from the current locale setting
 * of the system. To initialize this classes fields to reflect the current locale, invoke
 * #SetFromLocale().
 *
 * \note The method interface of this class is quite rudimentary. Therefore, it is advisable to
 *       use more user friendly classes as
 *       \ref aworx::lib::strings::AString       "AString" or
 *       \ref aworx::lib::strings::Substring   "Substring",
 *       which provide methods that accept a configured instance of this class as parameter and do
 *       the conversion internally.
 **********************************************************************************************/
class NumberFormat
{
    public:
    /**
     * The default static number format object, used by various methods. It therefore acts as the
     * global default settings of the currently running process.<br>
     * Method
     * \ref aworx::lib::ALIB::Init "ALIB::Init" invokes #SetFromLocale() on this object.
     */
    ALIB_API static    strings::NumberFormat           Global;

    // #############################################################################################
    //  public Fields
    // #############################################################################################

    /**
     *  Defines the decimal point character when converting a floating point number to a string
     *  representation with method #FloatToString. Also, method #StringToFloat accepts the
     *  character provided in this field aside to those provided in #DecimalPointCharacters.<br>
     *  The field defaults to '.'. By invoking #SetFromLocale(), the current locale's setting is
     *  determined.
     */
    char           DecimalPointCharacter                                                      = '.';

    /**
     *  Defines all characters that will be accepted by #StringToFloat as the separator
     *  of integral and fractional part of the value read.<br>
     *  Defaults to ".,".<br>
     *  The advantage of allowing both common symbols is that standard numbers are accepted
     *  independent of the current locale setting. However, the thousand separator commonly
     *  is the opposite of the 'dot' standard. This class does not support parsing or writing
     *  values with thousand separators anyhow. Therefore, accepting both here is no limitation.<br>
     *  Note: In addition to the characters provided in this field, method StringToFloat accepts
     *  the single character set in #DecimalPointCharacter as well.
     */
    TString DecimalPointCharacters                                                    = ".,";

    /**
     *  Defines the decimal exponent symbol of string representations of floating point numbers
     *  when written or parsed in scientific notation by methods #StringToFloat and #FloatToString.<br>
     *  Method #StringToFloat accepts characters 'e' and 'E' in addition to the character
     *  set in this field.<br>
     *  Defaults to 'E'.
     */
    TString DecimalExponentSeparator                                                   = "E";

    /**
     *  Determines if positive exponent values are prepended with an explicit '+' character when
     *  written using #FloatToString.<br>
     *  Independently from this setting, method #StringToFloat always accepts such optional
     *  plus sign.<br>
     *  Defaults to \c false, as some systems will not accept a plus sign on the exponent value.
     */
    bool           WriteExponentPlusSign                                                    = false;

    /**
     * Defines the minimum digits written for the integral part when converting a floating point
     * value into a string.<br>
     * If the integral part of the number provided has less digits
     * then leading '0' digits are added.<br>
     * The maximum value allowed is 15.<br>
     * A value of 0 leads to omitting the '0' before the
     * decimal separator in the case the value is below 1.0 and higher than -1.0 <br>
     * The default value is -1, which writes a minimum of 1 digit.
     * Scientific notation gets disabled when either this field or field #FractionalDigits is set to
     * any positive value, unless #ForceScientificFormat evaluates to \c true. In the latter case,
     * both fields can also be used to set a fixed number of digits for the integer and the
     * fractional part in scientific format.
     */
    int            MinIntegralDigits                                                    = -1;

    /**
     * Defines the number of digits written for the fractional part when converting a floating point
     * value into a string.<br>
     * If the fractional part of the number provided has less digits then trailing '0'
     * digits are added.<br>
     * If the fractional part of the number provided has more digits then the fractional part is
     * rounded accordingly.<br>
     * The maximum value allowed is 15.<br>
     * The default value is -1, which writes as many digits as available in the provided float
     * variable, with a minimum of 1 digit.
     * Scientific notation gets disabled when either this field or field #MinIntegralDigits is set
     * to any positive value, unless #ForceScientificFormat evaluates to \c true. In the latter case,
     * both fields can also be used to set a fixed number of digits for the integer and the
     * fractional part in scientific format.
     */
    int            FractionalDigits                                                     = -1;


    /**
     *  If \c false, the default, method #FloatToString writes scientific format only if both fields,
     *  #MinIntegralDigits and #FractionalDigits are evaluating to -1 and only for numbers smaller
     *  than 10^-4 or larger than 10^+6.<br>
     *  If \c true, scientific format is always used.<br>
     */
    bool           ForceScientificFormat                                                = false;

    // #############################################################################################
    //  Interface
    // #############################################################################################

    /** ****************************************************************************************
     * Sets the the the field
     * #DecimalPointCharacter
     * to reflect the current system locale's setting.
     ******************************************************************************************/
    ALIB_API
    void    SetFromLocale();


    // #############################################################################################
    //  Integer conversion
    // #############################################################################################

    /** ****************************************************************************************
     *  Reads a (64bit) integer value a string at the given position.
     *  The position is an in/output parameter. If provided, it is set to point to the first
     *  character that does not belong to the number.<br>
     *  If no number is found at the given index, zero is returned and the parameter is
     *  set to the original start index.
     *
     *  Leading whitespace characters are <em>not</em> ignored (parsing will fail).
     *
     *  @param         src The string to read the value from.
     *  @param[in,out] idx The start point from where the long value is tried to be read.
     *                     This is provided as reference and will on success be increased to
     *                     point to the first character behind the integer value found.
     *
     *  @return The parsed value. In addition, the parameter idx is moved to point to the
     *          first character behind any found long number.
     ******************************************************************************************/
    ALIB_API
    int64_t   StringToInteger( const String& src, int& idx );

    /** ****************************************************************************************
     *  Converts the given unsigned 64 bit integer value to a string representation.<br>
     *  Negative numbers have to be converted to positive values when invoking this method.
     *  The maximum number of digits written are 20. The given buffer has to be large
     *  enough to receive the characters. The method does not check any overflow within the
     *  given character buffer.
     *
     * @param value        The integer value to convert.
     * @param buffer       The character array to write the value to.
     * @param idx          The index within the buffer to start writing to.
     * @param minDigits    The minimum number of digits to append.
     *                     If given value has less digits, '0' characters are prepended.
     *                     The given value is cut to the range 1..20 (max digits of an
     *                     unsigned 64 bit integer).
     * @return  The index pointing behind the last character written.
     ******************************************************************************************/
    ALIB_API
    int     IntegerToString( uint_fast64_t value, char* buffer, int idx, int minDigits );



    // #############################################################################################
    //  Float conversion
    // #############################################################################################

    /** ****************************************************************************************
     *  Appends the given double value as string representation.
     *
     *  This method supports to write a variable or fixed number of digits for the integral
     *  and the fractional part of the provided value, or in <em>scientific notation</em>.
     *  In <em>scientific notation</em>, the value is multiplied with a power of 10 so that
     *  the integral part of the number falls into the range of 0 and 9. Then, the the negative
     *  value of the exponent of this multiplicand is appended, separated by the string defined in
     *  #DecimalExponentSeparator.
     *
     *  The output format is dependent on various settings provided in the fields of this class.
     *
     * @param value     The double value to append.
     * @param buffer    The character array to write the value into.
     *                  Depending on the value given and the format settings, a maximum of
     *                  32 characters need to be allocated prior to invoking this method.
     * @param idx       The index within the buffer to start writing to.
     *
     * @return   The index pointing behind the last character written.
     ******************************************************************************************/
    ALIB_API
    int  FloatToString( double value, char*  buffer, int idx );


    /** ****************************************************************************************
     *  Reads a floating point value from a string at the given position.
     *  The position is an in/output parameter. If provided, it is set to point to the first
     *  character that does not belong to the number.<br>
     *  If no number is found at the given index, zero is returned and the parameter \p idx
     *  reset to its original value.
     *
     *  Leading whitespace characters are <em>not</em> ignored (parsing will fail).
     *
     * @param         src The character array to read the value from.
     * @param[in,out] idx The start point from where the float value is tried to be read.
     *                    This is provided as reference and will on success be increased to
     *                    point to the first character behind the integer value found.
     *
     * @return The parsed value. In addition, on success, the output parameter idx is moved to
     *         point to the first character behind any found number.
     ******************************************************************************************/
    ALIB_API
    double StringToFloat( const String& src, int& idx );
};


}} // namespace lib::strings

/** Type alias name in namespace #aworx. */
using     NumberFormat=     aworx::lib::strings::NumberFormat;

}  // namespace aworx

#endif // HPP_ALIB_STRINGS_NUMBERFORMAT
