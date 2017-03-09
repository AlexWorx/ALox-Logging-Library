// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include guard
#ifndef HPP_ALIB_STRINGS_FORMAT_FORMATTER_JAVASTYLE
#define HPP_ALIB_STRINGS_FORMAT_FORMATTER_JAVASTYLE 1

// to preserve the right order, we check if string is already included
#if !defined(HPP_ALIB_STRINGS_STRING)
    #error "include 'alib/alib.hpp' prior to including this header"
#endif


#if !ALIB_MODULE_BOXING
    #error "class Formatter of library ALib can not be used without the use of ALib %Boxing."
#endif

#if !ALIB_FEAT_BOXING_FTYPES
    #error "class Formatter relies on the default implementation of boxing fundamental C++ types."
#endif

// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALIB_STRINGS_FORMAT_FORMATTER_STD_IMPL)
    #include "alib/strings/format/formatterstdimpl.hpp"
#endif


namespace aworx { namespace lib { namespace strings { namespace format {

/** ************************************************************************************************
 * Implements a \ref aworx::lib::strings::format::Formatter "Formatter" according to the
 * [formatting standards of the Java language](http://docs.oracle.com/javase/8/docs/api/java/util/Formatter.html).
 *
 * \note
 *   Inherited, public fields of parent class \b FormatterStdImpl provide important possibilities
 *   for changing the formatting behavior of instances of this class. Therefore, do not forget
 *   to consult the \ref aworx::lib::strings::format::FormatterStdImpl "parent classes documentation".
 *
 * In general, the original specification is covered quite well. The differences and specialties
 * are:
 * - In deviation of the Java specification, after creation, a formatter in this implementation
 *   does not produce locale aware output. Instead, number formatting is set to "computational",
 *   hence the decimal point separator is <c>'.'</c> and the grouping character <c>','</c>.
 *   As the syntax specification does not provide a feature to switch between standard and locale
 *   setting, the corresponding fields of #AlternativeNumberFormat are not used with this formatter.
 *   Instead, to enable localized output, method
 *   \ref aworx::lib::strings::NumberFormat::SetFromLocale "NumberFormat::SetFromLocale"
 *   has to be invoked on field
 *   \ref aworx::lib::strings::format::FormatterStdImpl::DefaultNumberFormat "FormatterStdImpl::DefaultNumberFormat".
 *   Alternatively, attributes of this object may be changed manually or by other means to reflect
 *   a desired locale.
 * - Hexadecimal floating point output (conversion type \c 'a' and \c 'A') is not supported.
 * - Flag \c '(', used to write negative numbers in round brackets, is not supported.
 * - Addressing the previous argument index using \c '%<' is already allowed with the first
 *   placeholder.
 *   This Chooses the first argument. (In Java a \b MissingFormatArgumentException would be thrown.)
 * - Flag \c '^' is an extension to the standard and denotes
 *   center-alignment - just like \c '-' in the standard denotes left-alignment.
 *   Right-alignment is the default.
 *
 *<p>
 * - <b>Floating point values:</b>
 *   - If standard field type \c 's' is given together with a precision, the field is cut, even if
 *     it cuts the number somewhere. (This is just a warning and same behavior as in original
 *     specification.)
 *   - For lower case floating point format types (\c 'f', \c 'g' and \c 'e'), the values specified
 *     in attributes \b %ExponentSeparator, \b %NANLiteral and \b %INFLiteral of object
 *     \ref aworx::lib::strings::format::FormatterStdImpl::AlternativeNumberFormat "AlternativeNumberFormat"
 *     are used. For upper case types (\c 'G' and \c 'E'), the corresponding attributes in
 *     \ref aworx::lib::strings::format::FormatterStdImpl::DefaultNumberFormat "DefaultNumberFormat" apply.
 *   - Fixed point format (\c 'f' ) is not supported to use arbitrary length.
 *     See class \ref aworx::lib::strings::NumberFormat "NumberFormat" for the limits.
 *     Due to this limitation, the default number of fractional digits is not set with type \c 'f',
 *     while in Java it is set to \c 6. This is to allow higher numbers up to \c 1.e13 to be printed
 *     in non-scientific format
 *   - When both, a \p width and a \p precision is given, then the \p precision determines the
 *     fractional part, even if the type is \b 'g' or \b 'G'. This is different than specified with
 *     Java formatter, which uses \p precision as the overall width in case of types
 *     \b 'g' or \b 'G'.
 *
 *<p>
 * - <b>Hexadecimal and Octal Numbers:</b>
 *   - Hexadecimal and octal output is <b>cut in size</b> (!) when a field width is given that
 *     is smaller than the resulting amount of digits of the number arguments provided.
 *       \note  This implies that a value written might not be equal to the value given.
 *              This is not a bug but a design decision. The rational behind this is that with this
 *              behavior, there is no need to mask lower digits when passing the arguments to the
 *              format invocation. In other words, the formatter "assumes" that the given field width
 *              indicates that only a corresponding number of lower digits are of interest.
 *
 *   - The number <b>grouping option</b> (<c>','</c>) can also be used with binary, hexadecimal
 *     and octal output.
 *     The types support different grouping separators for nibbles, bytes, 16-bit and 32-bit words.
 *     Changing the separator symbols, is not possible with the format fields of the format strings
 *     (if it was, this would become very incompatible to Java standards). Changes have to be made
 *     prior to the format operation by modifying field
 *     \ref aworx::lib::strings::format::FormatterStdImpl::AlternativeNumberFormat "AlternativeNumberFormat"
 *     which is provided through parent class \b %FormatterStdImpl.
 *
 *   - Alternative form (\c '#') adds prefixes as specified in members
 *     - \ref aworx::lib::strings::NumberFormat::HexLiteralPrefix "HexLiteralPrefix" and
 *     - \ref aworx::lib::strings::NumberFormat::OctLiteralPrefix "OctLiteralPrefix".
 *
 *     For upper case formats,  those are taken from field
 *     \ref aworx::lib::strings::format::FormatterStdImpl::DefaultNumberFormat "DefaultNumberFormat",
 *     for lower case formats from
 *     \ref aworx::lib::strings::format::FormatterStdImpl::AlternativeNumberFormat "AlternativeNumberFormat".
 *     All defaults may be changed by the user.
 *
 *<p>
 * - <b>Time and Date:</b>
 *   - In the C++ version, boxed values of type
 *     \ref aworx::lib::time::Ticks "Ticks"
 *     are applicable to conversion type \c 't'.
 *   - The following time conversion suffix characters are supported:
 *     \c 'H', \c 'k', \c 'I', \c 'l', \c 'M', \c 'S', \c 'B', \c 'b', \c 'h', \c 'A', \c 'a',
 *     \c 'Y', \c 'y', \c 'm', \c 'd', \c 'e', \c 'R', \c 'T', \c 'D' and \c 'F'
 *   - The following time conversion suffix characters are \b not supported:
 *     \c 'L', \c 'N', \c 'p', \c 'z', \c 'Z', \c 's', \c 'Q', \c 'C', \c 'j', \c 'r' and \c 'c'.
 *
 **************************************************************************************************/
class FormatterJavaStyle : public FormatterStdImpl
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /** Convert to upper case.   */
        bool                phaExtConversionUpper;

        /** Alternate form given ('#').   */
        bool                phaAlternateForm;

        /** The value read from the precision field.
         *  This is set to \c -1 in #resetPHAs. */
        int                 phaExtPrecision;

        /** The default precision if not given.
         *  This is set to \c 6 in #resetPHAs, but is changed when specific. */
        int                 phaExtDefaultPrecision;

        /** The character after conversion type 't'/'T'. */
        char                phaExtDateTime;

    // #############################################################################################
    //  Constructor/Destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Constructs this formatter.
         * Inherited field #DefaultNumberFormat is initialized to meet the formatting defaults of
         * Java.
         ******************************************************************************************/
        ALIB_API
        FormatterJavaStyle();



    // #############################################################################################
    //  Implementation of FormatterStdImpl interface
    // #############################################################################################
    protected:

        /** ****************************************************************************************
         * Invokes parent implementation and then applies some changes to reflect what is defined as
         * default in the Java string format specification.
         ******************************************************************************************/
        ALIB_API
        virtual void    resetPHAs()                                                   ALIB_OVERRIDE;

        /** ****************************************************************************************
         * Searches for \c '%' which is not '%%' or '%n'.
         *
         * @return The index found, -1 if not found.
         ******************************************************************************************/
        ALIB_API
        virtual integer findPlaceholder()                                             ALIB_OVERRIDE;

        /** ****************************************************************************************
         * Parses placeholder field in Java syntax. The portion \p format_spec is not set as this
         * is not supported by the syntax.
         *
         * @return \c true on success, \c false on errors.
         ******************************************************************************************/
        ALIB_API
        virtual bool    parsePlaceholder()                                            ALIB_OVERRIDE;

        /** ****************************************************************************************
         * Does nothing. Java does not support custom format specifications.
         *
         * @return \c true to indicate success.
         ******************************************************************************************/
        virtual bool    parseStdFormatSpec()                                           ALIB_OVERRIDE
        {
            return true;
        }

        /** ****************************************************************************************
         * Replaces \c "%%" with \c '%' and \c "%n" with ascii \c 0x0a. In addition applies
         * \ref aworx::lib::strings::Format::Escape "Format::Escape" on \p target which replaces
         * standard codes like \c "\\n", \c "\\r" or \c "\\t" with corresponding ascii codes.
         * (The latter is an extension to the standard behavior of Java formatter.)
         *
         * @param startIdx The start of the region to replace
         ******************************************************************************************/
        ALIB_API
        virtual void    replaceEscapeSequences( integer startIdx )                      ALIB_OVERRIDE;

        /** ****************************************************************************************
         * Converts strings to upper case.
         *
         * @param startIdx  The index of the start of the field written in #targetString.
         *                  \c -1 indicates pre-phase.
         ******************************************************************************************/
        ALIB_API
        virtual void    preAndPostProcess( integer startIdx)                            ALIB_OVERRIDE;

        /** ****************************************************************************************
         * Makes some attribute adjustments and invokes standard implementation
         * @return \c true if OK, \c false if replacement should be aborted.
         ******************************************************************************************/
        ALIB_API
        virtual bool    checkStdFieldAgainstArgument()                                ALIB_OVERRIDE;
};


}}} // namespace aworx[::lib::strings::format]

/** Type alias name in namespace #aworx. */
using     FormatterJavaStyle=  aworx::lib::strings::format::FormatterJavaStyle;

}  // namespace aworx

#endif // HPP_ALIB_STRINGS_FORMAT_FORMATTER_JAVASTYLE
