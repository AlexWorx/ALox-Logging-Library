﻿// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include guard
#ifndef HPP_ALIB_STRINGS_FORMAT_FORMATTER_PYTHONSTYLE
#define HPP_ALIB_STRINGS_FORMAT_FORMATTER_PYTHONSTYLE 1

// to preserve the right order, we check if string is already included
#if !defined(HPP_ALIB_STRINGS_STRING)
    #error "include 'alib/alib.hpp' prior to including this header"
#endif


#if !ALIB_MODULE_BOXING
    #error "class Formatter of library ALib can not be used without the use of %ALib %Boxing."
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

#if !defined (HPP_ALIB_STRINGS_UTIL_AUTOSIZES)
    #include "alib/strings/util/autosizes.hpp"
#endif


namespace aworx { namespace lib { namespace strings { namespace format {

/** ************************************************************************************************
 * Implements a \ref aworx::lib::strings::format::Formatter "Formatter" according to the
 * [formatting standards of the Python language](https://docs.python.org/3.5/library/string.html#format-string-syntax).
 *
 * \note
 *   Inherited, public fields of parent class \b FormatterStdImpl provide important possibilities
 *   for changing the formatting behavior of instances of this class. Therefore, do not forget
 *   to consult the \ref aworx::lib::strings::format::FormatterStdImpl "parent classes documentation".
 *
 * In general, the original \b Python specification is covered quite well. However, there are
 * some differences, some things are not possible (considering python being a scripting language)
 * but then there are also found some very helpful extensions to that standard. Instead of repeating
 * a complete documentation, please refer to the
 * [Python Documentation](https://docs.python.org/3.5/library/string.html#format-string-syntax)
 * as the foundation and then take note of the following list of differences, extensions and
 * general hints:
 *
 * - <b>General Notes:</b>
 *   \b Python defines a placeholder field as follows
 *
 *          "{" [field_name] ["!" conversion] [":" format_spec] "}"
 *
 *
 *   - This formatter is <b>less strict</b> in respect to the order of the format symbols. E.g.
 *     it allows <c>{:11.5,}</c> where Python allows only <c>{:11,.5}</c>
 *
 *   - With this class being derived from
 *     \ref aworx::lib::strings::format::FormatterStdImpl "FormatterStdImpl", features of the parent are
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
 * - <b>Positional arguments and field name:</b>
 *   - By the nature of the implementation language (<em>C++, no introspection</em>) of this class,
 *     \b field_name can \b not be the name of an identifier, an attribute name or an array element
 *     index. It can only be a positional argument index, hence a number that chooses a different
 *     index in the provided argument list.<br>
 *     However, the use of field names is often a requirement in use cases that offer configurable
 *     format string setup to the "end user". Therefore, there are two alternatives to cope
 *     with the limitation:
 *     - In simple cases, it is possible to just add all optionally needed data in the argument list,
 *       document their index position and let the user use positional argument notation to choose
 *       the right value from the list.
 *     - More elegant however, is the use of class
 *       \ref aworx::lib::strings::format::PropertyFormatter "PropertyFormatter"
 *       which extends the format specification by custom identifiers which control the placement
 *       of corresponding data in the format argument list. This class uses a translator table from
 *       identifier strings to custom callback functions. This way, much more than just simple
 *       field names are allowed.
 *
 *   - When using positional arguments in a format string placeholders, the Python formatter
 *     implementation does not allow to switch from <b>automatic field indexing</b> to explicit
 *     indexing. This \b %Aib implementation does allow it. The automatic index (aka no positional
 *     argument is given for a next placeholder) always starts with index \c 0 and is incremented
 *     each time automatic indexing is used.   Occurrences of explict indexing have no influence
 *     on the automatic indexing.
 *
 *
 * <p>
 * - <b>Binary, Hexadecimal and Octal Numbers:</b>
 *   - Binary, hexadecimal and octal output is <b>cut in size</b> (!) when a field width is given that
 *     is smaller than the resulting amount of digits of the number arguments provided.
 *      \note  This implies that a value written might not be equal to the value given.
 *             This is not a bug but a design decision. The rational behind this is that with this
 *             behavior, there is no need to mask lower digits when passing the arguments to the
 *             format invocation. In other words, the formatter "assumes" that the given field width
 *             indicates that only a corresponding number of lower digits are of interest.
 *
 *   - The number <b>grouping option</b> (<c>','</c>) can also be used with binary, hexadecimal and octal
 *     output.
 *     The types support different grouping separators for nibbles, bytes, 16-bit and 32-bit words.
 *     Changing the separator symbols, is not possible with the format fields of the format strings
 *     (if it was, this would become very incompatible to Python standards). Changes have to be made
 *     prior to the format operation by modifying field
 *     \ref aworx::lib::strings::format::FormatterStdImpl::AlternativeNumberFormat "AlternativeNumberFormat"
 *     which is provided through parent class \b %FormatterStdImpl.
 *
 *   - Alternative form (\c '#') adds prefixes as specified in members
 *     - \ref aworx::lib::strings::NumberFormat::BinLiteralPrefix "BinLiteralPrefix",
 *     - \ref aworx::lib::strings::NumberFormat::HexLiteralPrefix "HexLiteralPrefix" and
 *     - \ref aworx::lib::strings::NumberFormat::OctLiteralPrefix "OctLiteralPrefix".
 *
 *     For upper case formats,  those are taken from field
 *     \ref aworx::lib::strings::format::FormatterStdImpl::DefaultNumberFormat "DefaultNumberFormat",
 *     for lower case formats from
 *     \ref aworx::lib::strings::format::FormatterStdImpl::AlternativeNumberFormat "AlternativeNumberFormat".
 *     However, in a alignment with the \b Python specification, \b both default to lower case
 *     literals \c "0b", \c "0o" and \c "0x". All defaults may be changed by the user.
 *
 *
 * <p>
 * - <b>Floating point values:</b>
 *   - If floating point values are provided without a type specification in the format string, then
 *     all values of
 *     \ref aworx::lib::strings::format::FormatterStdImpl::DefaultNumberFormat "DefaultNumberFormat"
 *     are used to format the number
 *   - For lower case floating point format types (\c 'f' and \c 'e'), the values specified in
 *     attributes \b %ExponentSeparator, \b %NANLiteral and \b %INFLiteral of object
 *     \ref aworx::lib::strings::format::FormatterStdImpl::AlternativeNumberFormat "AlternativeNumberFormat"
 *     are used. For upper case   types (\c 'F' and \c 'E') the corresponding attributes in
 *     \ref aworx::lib::strings::format::FormatterStdImpl::DefaultNumberFormat "DefaultNumberFormat" apply.
 *   - Fixed point formats (\c 'f' and 'F' types) are not supported to use arbitrary length.
 *     See class \ref aworx::lib::strings::NumberFormat "NumberFormat" for the limits.
 *     Also, very high values and values close to zero may be converted to scientific format.
 *     Finally, if flag
 *     \ref aworx::lib::strings::NumberFormat::ForceScientific "ForceScientific"
 *     of field #DefaultNumberFormat is \c true, types \c 'f' and 'F' behave like types \c 'e' and 'E'.
 *   - When both, a \p width and a \p precision is given, then the \p precision determines the
 *     fractional part, even if the type is \b 'g' or \b 'G'. This is different than specified with
 *     Python formatter, which uses \p precision as the overall width in case of types
 *     \b 'g' or \b 'G'.
 *   - The 'general format' type for floats, specified with \c 'g' or \c 'G' in the python
 *     implementation limits the precision of the fractional part, even if \p precision is not
 *     further specified. This implementation does limit the precision only if type is \c 'f'
 *     or \c 'F'.
 *
 * <p>
 * - <b>%String Conversion:</b><br>
 *   If \e type \c 's' (or no \e type) is given in the \b format_spec of the replacement field,
 *   a string representation of the given argument is used.
 *   In \b Java and \b C# such representation is received by invoking <c>Object.[t|T]oString()</c>.
 *   Consequently, to support string representations of custom types, in these languages
 *   the corresponding <b>[t|T]oString()</b> methods of the type have to be implemented.
 *
 *   In C++ the arguments are "boxed" into objects of type
 *   \ref aworx::lib::boxing::Box "Box". For the string representation, the formatter invokes
 *   virtual boxing interface
 *   \ref aworx::lib::strings::boxing::IApply "IApply". A default implementation exists which
 *   for custom types appends the type name and the memory address of the object in hexadecimal
 *   format. To support custom string representations (for custom types), this boxing interface
 *   needs to be implemented for the type in question. Information and sample code on how to do this
 *   is found in the documentation of <b>%ALib %Boxing</b>, chapter
 *   \ref alib_namespace_boxing_strings_iapply "6.3 Interface IApply".
 *
 * - <b>Hash-Value Output:</b><br>
 *   In extension (and deviation) of the Python specification, format specification type \c 'h' and
 *   its upper case version \c 'H' is implemented. The hash-values of the argument object is
 *   written in hexadecimal format. Options of the type are identical to those of \c 'x',
 *   respectively \c 'X'.
 *
 *   In the C++ language implementation of \b %ALib, instead of hash-values of objects, the result
 *   of method \ref aworx::lib::boxing::Box::UnboxRaw "Box::UnboxRaw" is printed. In case of boxed
 *   class-types (that use default boxing mechanics), this will show the memory address of the
 *   given instance.
 *
 * - <b>Boolean output:</b><br>
 *   In extension (and deviation) of the Python specification, format specification type \c 'B'
 *   is implemented. The word \b "true" is written if the given value represents a boolean \c true
 *   value, \b "false" otherwise.
 *
 *   In the C++ language implementation of \b %ALib, the argument is \c true if
 *   the result of method \ref aworx::lib::boxing::Box::UnboxRaw "Box::UnboxRaw" is not \c 0.
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
 *   they call the ["Format Specification Mini Language"](https://docs.python.org/3.5/library/string.html#format-specification-mini-language).
 *
 *   With this implementation, the approach is very similar. The only difference is that the
 *   "Format Specification Mini Language" is implemented for standard types right within this class.
 *   But before processing \b format_spec, this class will check if an argument provides a custom
 *   implementation for formatting.
 *
 *   <br>In \b C++, again an <b>%ALib %Boxing</b> interface class is used.
 *   If a given boxed argument provides boxing interface
 *   \ref aworx::lib::strings::boxing::IFormat "IFormat", this interface is invoked and string
 *   \b format_spec is passed for custom processing.
 *
 *   Information and sample code on how to adopt custom types to support this interface is
 *   found in the documentation of <b>%ALib %Boxing</b>, chapter
 *   \ref alib_namespace_boxing_strings_iformat   "6.4 Interface IFormat".
 *
 *   Built-in class
 *   \ref aworx::lib::time::Ticks "Ticks" supports custom formatting with boxing interface
 *   \ref aworx::lib::time::IFormat_TTicks "IFormat_TTicks"
 *
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
 *     sequences.
 *     If \c '>' is given, escape sequences are converted to their (ascii) value.
 *     See \ref aworx::lib::strings::Format::Escape "Format::Escape" for details about the conversion
 *     that is performed.<br>
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
 *     Which each new invocation of \alib{strings::format,Formatter::Format}, the first auto value
 *     is chosen and with each use of \c !ATab or \c !AWidth, the next value is used.<br>
 *     By default, the fill character is space <c>' '</c>. It can be changed with optional character
 *     'C' plus the character wanted. The optional number provided gives the growth value by which
 *     the tab will grow if its position is exceeded. This value defaults to \c 3.
 *     The positions currently stored with the formatter can be reset with providing argument
 *     \c Reset. Alternatively to this, outside of a formatting process, the tab stops can be reset
 *     by invoking method \alib{strings::format,Formatter::Reset}.
 *
 *     Both, auto tab and auto width conversions may be used to increase readability of multiple
 *     output lines. Of-course, output is not completely tabular, only if those values that result
 *     in the biggest sizes are formatted first. If a perfect tabular output is desired, the data
 *     to be formatted may be processed twice: Once to temporary buffer which is disposed and then
 *     a second time to the desired output stream.
 *
 *     \note Method \alib{strings::format,Formatter::ReleaseDefault} resets the auto size values
 *           in case no multiple (recursive) acquirements had been performed.
 *
 *   - <b>!AWidth[NNN|Reset]</b><br>
 *     Increases field width with repetitive invocations of format whenever a field value did not
 *     fit to the actually stored width. Optional decimal number \b NNN is added as a padding value.
 *     for more information, see <b>!ATab</b> above.
 *
 *   - <b>!Xtinguish</b><br>
 *     Does not print anything. This is useful if format strings are externalized, e.g defined
 *     in \alib{lang,Library::Res,library resources}. Modifications of such resources might use this
 *     conversion to suppress the display of arguments (which usually are hard-coded).
 *
 *   - <b>!Replace\<search\>\<replace\></b><br>
 *     Searches string \p search and replaces with \p replace. Both values have to be given
 *     enclosed by characters \c ’<' and \c ’>'. In the special case that \p search is empty
 *     (<c>\<\></c>), string \p replace will be inserted if the field argument is an empty string.
 *
\~Comment ####################################################################################### \~
 * # Reference Documentation #
 * @throws aworx::lib::strings::format::Exceptions
 *   - \alib{strings::format::Exceptions,ArgumentIndexOutOfBounds}
 *   - \alib{strings::format::Exceptions,IncompatibleTypeCode}
 *   - \alib{strings::format::Exceptions,MissingClosingBracket}
 *   - \alib{strings::format::Exceptions,MissingPrecisionValuePS}
 *   - \alib{strings::format::Exceptions,DuplicateTypeCode}
 *   - \alib{strings::format::Exceptions,UnknownTypeCode}
 *   - \alib{strings::format::Exceptions,ExclamationMarkExpected}
 *   - \alib{strings::format::Exceptions,UnknownConversionPS}
 *   - \alib{strings::format::Exceptions,PrecisionSpecificationWithInteger}
 **************************************************************************************************/
class FormatterPythonStyle : public FormatterStdImpl
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /**
         * The portion of the replacement field that represents the conversion specification.
         * This specification is given at the beginning of the replacement field, starting with
         * \c '!'.
         */
        Substring                   phaExtConversion;

        /** The position where the conversion was read. This is set to \c -1 in #resetPHAs. */
        integer                     phaExtConversionPos;


        /** The value read from the precision field.   This is set to \c -1 in #resetPHAs. */
        int                         phaExtPrecision;

        /** The position where the precision was read. This is set to \c -1 in #resetPHAs. */
        integer                     phaExtPrecisionPos;

        /** The default precision if not given.
         *  This is set to \c 6 in #resetPHAs, but is changed when specific. */
        int                         phaExtDefaultPrecision;

        /** Storage of sizes for auto-tabulator feature ("!ATab")  */
        AutoSizes                   autoSizes;



    // #############################################################################################
    //  Constructor/Destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Constructs this formatter.
         * Inherited field #DefaultNumberFormat is initialized to meet the formatting defaults of
         * Python.
         ******************************************************************************************/
         ALIB_API
         FormatterPythonStyle();

    // #############################################################################################
    //  Implementation of FormatterStdImpl interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Resets #autoSizes.
         ******************************************************************************************/
        ALIB_API
        virtual void    Reset()                                                            override;

    protected:
        /** ****************************************************************************************
         * Sets the actual auto tab stop index to \c 0.
         ******************************************************************************************/
        ALIB_API
        virtual void    initializeFormat()                                                 override;

        /** ****************************************************************************************
         * Invokes parent implementation and then applies some changes to reflect what is defined as
         * default in the Python string format specification.
         ******************************************************************************************/
        ALIB_API
        virtual void    resetPHAs()                                                        override;

        /** ****************************************************************************************
         * Searches for \c '{'  which is not '{{'.
         *
         * @return The index found, -1 if not found.
         ******************************************************************************************/
        ALIB_API
        virtual integer findPlaceholder()                                                  override;

        /** ****************************************************************************************
         * Parses placeholder field in python notation. The portion \p format_spec is not
         * parsed but stored in member
         * \ref aworx::lib::strings::format::FormatterStdImpl::phaFormatSpec "Formatter::phaFormatSpec".
         *
         * @return \c true on success, \c false on errors.
         ******************************************************************************************/
        ALIB_API
        virtual bool    parsePlaceholder()                                                 override;

        /** ****************************************************************************************
         * Parses the format specification for standard types as specified in
         * ["Format Specification Mini Language"](https://docs.python.org/3.5/library/string.html#format-specification-mini-language).
         *
         * @return \c true on success, \c false on errors.
         ******************************************************************************************/
        ALIB_API
        virtual bool    parseStdFormatSpec()                                               override;

        /** ****************************************************************************************
         * Implementation of abstract method.<br>
         * Replaces \c "{{" with \c "{" and \c "}}" with \c "}". In addition applies
         * \ref aworx::lib::strings::Format::Escape "Format::Escape" on \p target which replaces
         * standard codes like \c "\\n", \c "\\r" or \c "\\t" with corresponding ascii codes.
         *
         *
         * @param startIdx The start of the region to replace
         ******************************************************************************************/
        ALIB_API
        virtual void    replaceEscapeSequences( integer startIdx )                         override;

        /** ****************************************************************************************
         * Processes "conversions" which are specified with \c '!'.
         *
         * @param startIdx  The index of the start of the field written in #targetString.
         *                  \c -1 indicates pre-phase.
         * @param target    The target string, only if different from field #targetString, which
         *                  indicates intermediate phase.
         * @return \c false, if the placeholder should be skipped (nothing is written for it).
         *         \c true otherwise.
         ******************************************************************************************/
        ALIB_API
        virtual bool    preAndPostProcess( integer startIdx, AString* target )             override;


        /** ****************************************************************************************
         * Makes some attribute adjustments and invokes standard implementation
         * @return \c true if OK, \c false if replacement should be aborted.
         ******************************************************************************************/
        ALIB_API
        virtual bool    checkStdFieldAgainstArgument()                                     override;

};


}}} // namespace aworx[::lib::strings::format]

/** Type alias name in namespace #aworx. */
using     FormatterPythonStyle=  aworx::lib::strings::format::FormatterPythonStyle;

}  // namespace aworx

#endif // HPP_ALIB_STRINGS_FORMAT_FORMATTER_PYTHONSTYLE
