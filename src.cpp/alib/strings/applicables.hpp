// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

// needed for Doxygen include of the typedefs at the end of the file
/**@file*/

// include guard
#ifndef HPP_ALIB_STRINGS_BUILTIN_APPLICABLES
#define HPP_ALIB_STRINGS_BUILTIN_APPLICABLES 1

// to preserve the right order, we are not includable directly from outside.
#if !defined(ALIB_PROPER_INCLUSION)
    #error "include 'alib/alib.hpp' instead of this header"
#endif


// This is for testing internal include order, see stdafx_alib.h
#if defined(HPP_ALIB_STRINGS_NUMBERFORMAT)
    #error "ALib Include order error"
#endif
#if defined(HPP_ALIB_STRINGS_UTIL_TOKENIZER)
    #error "ALib Include order error"
#endif

namespace aworx { namespace lib { namespace strings
{


// #################################################################################################
// struct T_Apply: fundamental types
// #################################################################################################

// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::applyto to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
namespace applyto {
#endif

    /** Specialization of template struct \alib{strings,T_Apply} for type \c char*.   */
    template<> struct       T_Apply<char*> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes a cstring to the given AString.
         * @param target The object that \b Apply was invoked on.
         * @param src    The character string to append to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const char* src )
        {
            integer length= static_cast<integer>( strlen( src ) );              // can't be nullptr
            target.Append<false>( src, length );    // use false, as length check is anyhow down later
            return length;
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c wchar_t*.   */
    template<> struct       T_Apply<wchar_t*> : public std::true_type
    {
        /** ****************************************************************************************
         * This method converts the provided wide character string (zero-terminated array of
         * wchar_t) and appends it to the \p target. The conversion is done using
         * - <em>wcsnrtombs</em> on glibc platforms (e.g. Linux)
         * - <em>WideCharToMultiByte(CP_UTF8,...)</em> on Windows platform.
         * @param target The object that \b Apply was invoked on.
         * @param src    The wide character string to append to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const wchar_t* src)
        {
            target.Append( src, src != nullptr ?  static_cast<integer>( wcslen( src ) ) : 0 ) ;
            return 0; // nullptr treatment already done
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c char16_t*.   */
    template<> struct       T_Apply<char16_t*> : public std::true_type
    {
        /** ****************************************************************************************
         * This method converts the provided char16_t string (zero-terminated array of
         * char16_t) and appends it to the \p target. The conversion is done using
         * - <em>wcsnrtombs</em> on glibc platforms (e.g. Linux)
         * - <em>WideCharToMultiByte(CP_UTF8,...)</em> on Windows platform.
         * @param target The object that \b Apply was invoked on.
         * @param src    The wide character string to append to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const char16_t* src)
        {
            target.Append( src, static_cast<integer>( detail::strlen16( src ) ) );
            return 0; // nullptr treatment already done
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c char32_t*.   */
    template<> struct       T_Apply<char32_t*> : public std::true_type
    {
        /** ****************************************************************************************
         * This method converts the provided char32_t string (zero-terminated array of
         * char32_t) and appends it to the \p target. The conversion is done using
         * - <em>wcsnrtombs</em> on glibc platforms (e.g. Linux)
         * - <em>WideCharToMultiByte(CP_UTF8,...)</em> on Windows platform.
         * @param target The object that \b Apply was invoked on.
         * @param src    The wide character string to append to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const char32_t* src)
        {
            target.Append( src, static_cast<integer>( detail::strlen32( src ) ) );
            return 0; // nullptr treatment already done
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c bool.   */
    template<> struct       T_Apply<bool> : public std::true_type
    {
        /** ****************************************************************************************
         * By default, writes the words "true" or "false" to the given AString.
         * The names are resourced in library \alib{strings,Strings} with keys
         * \c "APPLY_T" and \c "APPLY_F".
         * @param target The object that \b Apply was invoked on.
         * @param b      The boolean to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        ALIB_API
        static integer Apply( AString& target, bool& b );
    };


#if ALIB_DEBUG
    /** Specialization of template struct \alib{strings,T_Apply} for type \c std::type_info.   */
    template<> struct       T_Apply<std::type_info> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the demangled type name.
         * @param target The object that \b Apply was invoked on.
         * @param type   The type to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        ALIB_API
        static integer Apply( AString& target, const std::type_info& type );
    };
#endif


// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::apply to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
}
#endif


// #################################################################################################
// class Format
// #################################################################################################

    /** ********************************************************************************************
     * This is a type applicable to objects of type
     * \ref aworx::lib::strings::AString "AString". Various constructors consume integer and
     * floating point types, along with formatting options. The specialization of struct
     * \alib{strings,T_Apply} "T_Apply<Format>"
     *  will use a given (or defaulted) instance of class
     * \ref aworx::lib::strings::NumberFormat "NumberFormat" to append the value to the
     * \b %AString in question.
     *
     * \note
     *   Within the same header file that this class in declared in, there are several
     *   specializations of \alib{strings,T_Apply} defined for plain integer and
     *   floating point types. These specializations create an object of this type, providing the
     *   value only, hence, using this classes constructors' default values. The number format
     *   used as default by the constructors of this class is
     *   \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
     *   As a result, the application of such core types, as in:
     *   \snippet "DOX_ALIB_APPLYTO.cpp"     DOX_ALIB_APPLYTO_FORMAT1
     *   which produces:
     *   \snippet "DOX_ALIB_APPLYTO_FORMAT1.txt"     OUTPUT
     *
     * \note
     *   does \b not use a locale specific number format. Instead it uses one that is exchangeable
     *   between applications independent from the locale setting of the executing machine.<br>
     *   Consequently, for locale specific output, an object of this class needs to be applied
     *   along with a locale enabled instance of \b %NumberFormat. For example:
     *   \snippet "DOX_ALIB_APPLYTO.cpp"     DOX_ALIB_APPLYTO_FORMAT2
     *   which - dependent on the current local setting - might produce:
     *   \snippet "DOX_ALIB_APPLYTO_FORMAT2.txt"     OUTPUT
     *
     *
     * <b>Inner Types:</b><br>
     * Besides accepting plain number types, this class in addition aggregates several public inner
     * types, namely
     * - \ref aworx::lib::strings::Format::Tab   "Format::Tab",
     * - \ref aworx::lib::strings::Format::Field "Format::Field",
     * - \ref aworx::lib::strings::Format::Bin   "Format::Bin",
     * - \ref aworx::lib::strings::Format::Hex   "Format::Hex" and
     * - \ref aworx::lib::strings::Format::Oct   "Format::Oct".
     *
     * Each of these classes has partial implementations of template function
     * \alib{strings,T_Apply} and provide certain formatting options.
     *
     * \note The types are not 'physically' related to this class. Instead, they have been
     *       aggregated here for 'esthetical' reasons.
     *
     * <b>Details on Formats:</b><br>
     * Details on the options of formatting integer and floating point numbers are documented
     * with class
     * \ref aworx::lib::strings::NumberFormat "NumberFormat".
     **********************************************************************************************/
    class Format
    {
        public:

        // #########################################################################################
        // Inner types
        // #########################################################################################

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::AString "AString" with specialization of template struct
         * \ref aworx::lib::strings::applyto::T_Apply<Format::Tab> "T_Apply<Format::Tab>".
         *
         * Appends \e tab characters (as provided) to reach a certain length (aka tabulator position)
         * of the \p target. The tab position is referenced to an optionally given \p reference value
         * which might be the start of the string or the position of the last newline. If this
         * parameter is negative, the last newline characters are searched from the end of the
         * string backwards.<br>
         * Referring to that as position 0, the tab position is then located at the next multiple
         * of parameter \p tabSize, after having added  \p minPad tab characters.
         ******************************************************************************************/
        struct Tab
        {
            public:
            /** The tab positions are multiples of this value.*/
            integer      tabSize;

            /** The reference length of the AString which is taken as relative tab position
             *  (instead of the beginning of the string). If -1, the target %AString is
             *  searched backwards for the last newline and this position is used as the
             *  reference.
             */
            integer      reference;

            /** The minimum pad characters to add. Defaults to 1. */
            integer      minPad;

            /** The character to insert to reach the tab position. Normally this is the space
             *  character ' '.*/
            char          tabChar;

            /**
             * Constructor, copying the values into this 'delegate' object. They will be used
             * with method \b %Apply of specialized template struct
             * \ref applyto::T_Apply<Format::Tab> "T_Apply<Format::Tab>".
             *
             * @param size          The tab positions are multiples of this parameter.
             * @param referenceIdx  The reference index marking the start of the actual line.
             *                      If -1, the last new-line character is searched from the end of
             *                      the string backwards, and used. Defaults to 0.
             * @param minPadChars   The minimum pad characters to add. Defaults to 1.
             * @param fillChar      The character to insert to reach the tab position.
             *                      Defaults to ' ' (space).
             */
            Tab(  integer size, integer referenceIdx = 0, integer minPadChars= 1, char fillChar= ' ' )
            : tabSize(size), reference(referenceIdx), minPad(minPadChars), tabChar(fillChar)
            {}
        };

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::AString "AString" with specialization of template struct
         * \ref aworx::lib::strings::applyto::T_Apply<Format::Field> "T_Apply<Format::Field>".
         *
         * Appends the given object to the AString using a defined 'field'-width.
         * If the contents of the field is shorter than parameter \p width specifies, the field is
         * filled with a corresponding amount of \p padChar characters.<br>
         * Parameter \p alignment of type
         * \ref aworx::lib::lang::Alignment "Alignment" allows to left-, right- or center-align
         * the contents of the field.
         *
         * \note In case, module <b>%ALib %Boxing</b> is not available, the field content
         *       parameter will be of type <c>const String&</c>.<br>
         *       Otherwise, boxing interface \alib{strings::boxing,IApply} will be invoked on
         *       the given box internally to receive the string representation.
         *
         * \note Therefore, it is mandatory, that for any type that is used with this class
         *       to be formatted in a field, this boxing interface has to be implemented. As
         *       documented with that interface, for types that are applicable to \b %AString
         *       objects already, all that is needed is to use macro
         *       \ref ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE with the type in the bootstrap
         *       section of an application.
         ******************************************************************************************/
        struct Field
        {
            public:
            #if ALIB_MODULE_BOXING
              Box            theContent;   ///< The content of the field. If module
                                           ///< <b>%ALib %Boxing</b> is not available, this field
                                           ///< is of type <c>const String&</c>
            #else
              const String&  theContent;
            #endif
            integer          theWidth;     ///< The width of the field.
            lang::Alignment  theAlignment; ///< The alignment of the contents within the field.
            char             padChar;      ///< The characters used for padding the contents within the field.

            /**
             * Constructor, copying the values into this 'delegate' object. They will be used
             * with method \b %Apply of specialized template struct
             * \ref applyto::T_Apply<Format::Field> "T_Apply<Format::Field>".
             *
             * @param content   The contents of the field.
             * @param width     The width of the field
             * @param alignment The alignment of the contents within the field.
             *                  Defaults to
             *                  \ref aworx::lib::lang::Alignment "Alignment::Right"
             *                  Other options are
             *                  \ref aworx::lib::lang::Alignment "Alignment::Left" and
             *                  \ref aworx::lib::lang::Alignment "Alignment::Center".
             * @param fillChar  The character used to fill the field up to its size.
             *                  Defaults to ' ' (space).
             */
            Field(
                    #if ALIB_MODULE_BOXING
                      Box            content,
                    #else
                      const String&  content,
                    #endif

                    integer           width,
                    lang::Alignment   alignment  =lang::Alignment::Right,
                    char              fillChar   = ' '                       )
            #if ALIB_MODULE_BOXING
            : theContent(content),
            #else
            : theContent(content.IsNotNull() ? content : EmptyString ),
            #endif
              theWidth(width),
              theAlignment(alignment),
              padChar(fillChar)
            {}

        };

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::AString "AString" with specialization of template struct
         * \ref aworx::lib::strings::applyto::T_Apply<Format::Escape> "T_Apply<Format::Escape>".
         *
         * Escapes non-printable characters in the given region, or converts such escaped characters
         * to their ASCII values.<br>
         * If the new region length is needed to be known, it can be calculated as the sum of
         * the old region length and the difference of the string before and after the operation.
         ******************************************************************************************/
        struct Escape
        {
            public:
            /** The direction of conversion: \b Switch::On escapes ascii characters, while
             *  \b Switch::Off converts escaped strings to ascii codes.*/
            Switch       pSwitch;

            /** The start of the region to convert. */
            integer      startIdx;

            /** The length of the region to convert. */
            integer      length;


            /**
             * Constructor, copying the values into this 'delegate' object. They will be used
             * with method \b %Apply of specialized template struct
             * \ref applyto::T_Apply<Format::Tab> "T_Apply<Format::Tab>".
             *
             * @param escape        \b Switch::On escapes ascii characters (the default),
             *                      \b Switch::Off converts  escaped strings to ascii codes.
             * @param regionStart   The start of the region to convert.
             * @param regionLength  The length of the region to convert.
             */
            Escape( Switch escape= Switch::On, integer regionStart = 0, integer regionLength= CString::MaxLen )
            : pSwitch(escape), startIdx(regionStart), length(regionLength)
            {}
        };


        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::AString "AString" with specialization of template struct
         * \ref aworx::lib::strings::applyto::T_Apply<Format::Bin> "T_Apply<Format::Bin>".<br>
         * Appends an integer value in binary format.<br>
         * See \ref aworx::lib::strings::NumberFormat::WriteBin "NumberFormat::WriteBin"
         * for more information on formatting options.
         ******************************************************************************************/
        struct Bin
        {
            public:
            uint64_t        theValue;   ///< The value to write.
            int             theWidth;   ///< The minimum width of the number to write.
                                        ///< Defaults to \c 0
                                        ///< which denotes to choose the value of field
                                        ///< \ref aworx::lib::strings::NumberFormat::BinFieldWidth "NumberFormat::BinFieldWidth".
            NumberFormat*   nf;         ///< The number format to use. Defaults to \c nullptr which chooses
                                        ///< \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".

            /**
             * Constructor, taking the value and formatting parameters.
             *
             * @param value         The value to write.
             * @param overrideWidth Defaults to \c 0 which
             *                      denotes to choose the value of field
             *                      \ref aworx::lib::strings::NumberFormat::BinFieldWidth "NumberFormat::BinFieldWidth".
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Bin( uint64_t       value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (overrideWidth)
                , nf        (numberFormat)                  {}

            /**
             * Constructor, taking the value and a just an object of type \b %NumberFormat.
             *
             * @param value         The value to write.
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Bin( uint64_t       value,
                 NumberFormat*  numberFormat                                   )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (0)
                , nf        (numberFormat)                  {}

            /**
             * Constructor, taking the value and formatting parameters.
             *
             * @param value         The value to write.
             * @param overrideWidth Defaults to \c 0 which
             *                      denotes to choose the value of field
             *                      \ref aworx::lib::strings::NumberFormat::BinFieldWidth "NumberFormat::BinFieldWidth".
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Bin( uint32_t   value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (overrideWidth)
                , nf        (numberFormat)                  {}

            /**
             * Constructor, taking the value and a just an object of type \b %NumberFormat.
             *
             * @param value         The value to write.
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Bin( uint32_t       value,
                 NumberFormat*  numberFormat                                   )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (0)
                , nf        (numberFormat)                  {}

        };

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::AString "AString" with specialization of template struct
         * \ref aworx::lib::strings::applyto::T_Apply<Format::Hex> "T_Apply<Format::Hex>".<br>
         * Appends an integer value in hexadecimal format.<br>
         * See \ref aworx::lib::strings::NumberFormat::WriteHex "NumberFormat::WriteHex"
         * for more information on formatting options.
         ******************************************************************************************/
        struct Hex
        {
            public:
            uint64_t    theValue;  ///< The value to write.
            int         theWidth;  ///< The minimum width of the number to write.
                                   ///< Defaults to \c 0
                                   ///< which denotes to choose the value of field
                                   ///< \ref aworx::lib::strings::NumberFormat::HexFieldWidth "NumberFormat::HexFieldWidth".
            NumberFormat*   nf;    ///< The number format to use. Defaults to \c nullptr which chooses
                                   ///< \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".

            /**
             * Constructor, taking the value and formatting parameters.
             *
             * @param value         The value to write.
             * @param overrideWidth Defaults to \c 0 which
             *                      denotes to choose the value of field
             *                      \ref aworx::lib::strings::NumberFormat::HexFieldWidth "NumberFormat::HexFieldWidth".
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Hex( uint64_t       value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr    )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (overrideWidth)
                , nf        (numberFormat)                  {}

            /**
             * Constructor, taking the value and a just an object of type \b %NumberFormat.
             *
             * @param value         The value to write.
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Hex( uint64_t       value,
                 NumberFormat*  numberFormat   )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (0)
                , nf        (numberFormat)                  {}

            /**
             * Constructor, taking the value and formatting parameters.
             *
             * @param value         The value to write.
             * @param overrideWidth Defaults to \c 0 which
             *                      denotes to choose the value of field
             *                      \ref aworx::lib::strings::NumberFormat::HexFieldWidth "NumberFormat::HexFieldWidth".
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Hex( uint32_t       value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr    )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (overrideWidth)
                , nf        (numberFormat)                  {}

            /**
             * Constructor, taking the value and a just an object of type \b %NumberFormat.
             *
             * @param value         The value to write.
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Hex( uint32_t       value,
                 NumberFormat*  numberFormat   )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (0)
                , nf        (numberFormat)                  {}

        };

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::AString "AString" with specialization of template struct
         * \ref aworx::lib::strings::applyto::T_Apply<Format::Oct> "T_Apply<Format::Oct>".<br>
         * Appends an integer value in octal format.<br>
         * See \ref aworx::lib::strings::NumberFormat::WriteHex "NumberFormat::WriteHex"
         * for more information on formatting options.
         ******************************************************************************************/
        struct Oct
        {
            public:
            uint64_t        theValue; ///< The value to write.
            int             theWidth; ///< The minimum width of the number to write.
                                      ///< Defaults to \c 0
                                      ///< which denotes to choose the value of field
                                      ///< \ref aworx::lib::strings::NumberFormat::OctFieldWidth "NumberFormat::OctFieldWidth".
            NumberFormat*   nf;       ///< The number format to use. Defaults to \c nullptr which chooses
                                      ///< \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".

            /**
             * Constructor, taking the value and formatting parameters.
             *
             * @param value         The value to write.
             * @param overrideWidth Defaults to \c 0 which
             *                      denotes to choose the value of field
             *                      \ref aworx::lib::strings::NumberFormat::OctFieldWidth "NumberFormat::OctFieldWidth".
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Oct( uint64_t       value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (overrideWidth)
                , nf        (numberFormat)                  {}

            /**
             * Constructor, taking the value and a just an object of type \b %NumberFormat.
             *
             * @param value         The value to write.
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Oct( uint64_t       value,
                 NumberFormat*  numberFormat                                   )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (0)
                , nf        (numberFormat)                  {}

            /**
             * Constructor, taking the value and formatting parameters.
             *
             * @param value         The value to write.
             * @param overrideWidth Defaults to \c 0 which
             *                      denotes to choose the value of field
             *                      \ref aworx::lib::strings::NumberFormat::OctFieldWidth "NumberFormat::OctFieldWidth".
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Oct( uint32_t       value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (overrideWidth)
                , nf        (numberFormat)                  {}

            /**
             * Constructor, taking the value and a just an object of type \b %NumberFormat.
             *
             * @param value         The value to write.
             * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
             *                      the static singleton found in
             *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
             */
            Oct( uint32_t       value,
                 NumberFormat*  numberFormat                                   )
                : theValue  (static_cast<uint64_t>(value))
                , theWidth  (0)
                , nf        (numberFormat)                  {}
        };

        // #########################################################################################
        // Fields (class Format)
        // #########################################################################################

        int             valueType;      ///< Flag witch value to use (1= sInt, 2=uInt, 3=fp )
        /** The union to hold the data provided with the different constructors. */
        union
        {
             int64_t    sInt;       ///< The value when using constructor with signed integer types.
            uint64_t    uInt;       ///< The value when using constructor with unsigned integer types.
            double      fp;         ///< The value when using constructor with type double.
        } v; ///< The data

        int             theWidth;       ///< The minimum width of the number to write.
                                        ///< Defaults to \c 0
                                        ///< which denotes to choose the value of field
                                        ///< \ref aworx::lib::strings::NumberFormat::DecMinimumFieldWidth "NumberFormat::DecMinimumFieldWidth".
        NumberFormat*   nf;             ///< The number format to use. Defaults to \c nullptr which chooses
                                        ///< the static singleton found in
                                        ///< \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param overrideWidth Defaults to \c 0 which
         *                      denotes to choose the value of field
         *                      \ref aworx::lib::strings::NumberFormat::DecMinimumFieldWidth "NumberFormat::DecMinimumFieldWidth".
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  int64_t        value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : valueType(1)
                , theWidth (overrideWidth)
                , nf       (numberFormat)                  { v.sInt= static_cast<int64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  int64_t    value,
                 NumberFormat*  numberFormat                                   )
                : valueType(1)
                , theWidth (0)
                , nf       (numberFormat)                  { v.sInt= static_cast<int64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param overrideWidth Defaults to \c 0 which
         *                      denotes to choose the value of field
         *                      \ref aworx::lib::strings::NumberFormat::DecMinimumFieldWidth "NumberFormat::DecMinimumFieldWidth"
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  uint64_t   value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : valueType(2)
                , theWidth (overrideWidth)
                , nf       (numberFormat)                  { v.uInt= static_cast<uint64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  uint64_t   value,
                 NumberFormat*  numberFormat                       )
                : valueType(2)
                , theWidth (0)
                , nf       (numberFormat)                  { v.uInt= static_cast<uint64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param overrideWidth Defaults to \c 0 which
         *                      denotes to choose the value of field
         *                      \ref aworx::lib::strings::NumberFormat::DecMinimumFieldWidth "NumberFormat::DecMinimumFieldWidth".
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  int32_t   value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : valueType(1)
                , theWidth (overrideWidth)
                , nf       (numberFormat)                  { v.sInt= static_cast<int64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  int32_t   value,
                 NumberFormat*  numberFormat                       )
                : valueType(1)
                , theWidth(0)
                , nf       (numberFormat)                  { v.sInt= static_cast<int64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param overrideWidth Defaults to \c 0 which
         *                      denotes to choose the value of field
         *                      \ref aworx::lib::strings::NumberFormat::DecMinimumFieldWidth "NumberFormat::DecMinimumFieldWidth".
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  uint32_t  value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : valueType(2)
                , theWidth (overrideWidth)
                , nf       (numberFormat)                  { v.uInt= static_cast<uint64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  uint32_t  value,
                 NumberFormat*  numberFormat                       )
                : valueType(2)
                , theWidth(0)
                , nf       (numberFormat)                  { v.uInt= static_cast<uint64_t>(value); }


        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param overrideWidth Defaults to \c 0 which
         *                      denotes to choose the value of field
         *                      \ref aworx::lib::strings::NumberFormat::DecMinimumFieldWidth "NumberFormat::DecMinimumFieldWidth".
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  intGap_t        value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : valueType(1)
                , theWidth (overrideWidth)
                , nf       (numberFormat)                  { v.sInt= static_cast<int64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  intGap_t        value,
                 NumberFormat*  numberFormat                       )
                : valueType(1)
                , theWidth(0)
                , nf       (numberFormat)                  { v.sInt= static_cast<int64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param overrideWidth Defaults to \c 0 which
         *                      denotes to choose the value of field
         *                      \ref aworx::lib::strings::NumberFormat::DecMinimumFieldWidth "NumberFormat::DecMinimumFieldWidth".
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  uintGap_t       value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : valueType(2)
                , theWidth (overrideWidth)
                , nf       (numberFormat)                  { v.uInt= static_cast<uint64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  uintGap_t       value,
                 NumberFormat*  numberFormat                       )
                : valueType(2)
                , theWidth(0)
                , nf       (numberFormat)                  { v.uInt= static_cast<uint64_t>(value); }


        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param overrideWidth Defaults to \c 0 which
         *                      denotes to choose the value of field
         *                      \ref aworx::lib::strings::NumberFormat::DecMinimumFieldWidth "NumberFormat::DecMinimumFieldWidth".
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  int16_t        value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : valueType(1)
                , theWidth (overrideWidth)
                , nf       (numberFormat)                  { v.sInt= static_cast<int64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  int16_t        value,
                 NumberFormat*  numberFormat                       )
                : valueType(1)
                , theWidth(0)
                , nf       (numberFormat)                  { v.sInt= static_cast<int64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param overrideWidth Defaults to \c 0 which
         *                      denotes to choose the value of field
         *                      \ref aworx::lib::strings::NumberFormat::DecMinimumFieldWidth "NumberFormat::DecMinimumFieldWidth".
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  uint16_t   value,
                 int            overrideWidth= 0,
                 NumberFormat*  numberFormat = nullptr                                   )
                : valueType(2)
                , theWidth (overrideWidth)
                , nf       (numberFormat)                  { v.uInt= static_cast<uint64_t>(value); }

        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format(  uint16_t       value,
                 NumberFormat*  numberFormat                       )
                : valueType(2)
                , theWidth(0)
                , nf       (numberFormat)                  { v.uInt= static_cast<uint64_t>(value); }


        /**
         * Constructor. Stores parameters.
         *
         * @param value         The value to write.
         * @param overrideWidth Defaults to \c 0 which
         *                      denotes to choose the value of field
         *                      \ref aworx::lib::strings::NumberFormat::DecMinimumFieldWidth "NumberFormat::IntegralPartMinimumWidth".
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational".
         */
        Format( double         value,
                int            overrideWidth= 0,
                NumberFormat*  numberFormat = nullptr            )
                : valueType(3)
                , theWidth (overrideWidth)
                , nf       (numberFormat)                  { v.fp= value; }

        /**
         * Constructor, taking a double value and a just an object of type \b %NumberFormat.
         *
         * @param value         The value to write.
         * @param numberFormat  The number format to use. Defaults to \c nullptr which chooses
         *                      the static singleton found in
         *                      \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         */
        Format( double         value,
                NumberFormat*  numberFormat                                   )
                : valueType(3)
                , theWidth (0)
                , nf       (numberFormat)                  { v.fp= value; }


    };



// #################################################################################################
// Corresponding specializations of struct  T_Apply
// #################################################################################################

// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::applyto to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
    namespace applyto {
#else
    ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING
#endif


    /** Specialization of template struct \alib{strings,T_Apply} for type \c Format.   */
    template<> struct T_Apply<Format> : public std::true_type
    {
        /** ****************************************************************************************
         * Applies type
         * \ref aworx::lib::strings::Format "Format".
         *
         * @param target The object that \b Apply was invoked on.
         * @param fmt    The format object.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        ALIB_API static integer Apply( AString& target,  const Format& fmt );
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c Format::Tab.   */
    template<> struct T_Apply<Format::Tab> : public std::true_type
    {
        /** ****************************************************************************************
         * Applies type
         * \ref aworx::lib::strings::Format::Tab "Format::Tab".
         *
         * @param  target   The object that \b Apply was invoked on.
         * @param  tab      The object to \e apply.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        ALIB_API static   integer Apply( AString& target, const Format::Tab& tab);
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c Format::Field.   */
    template<> struct T_Apply<Format::Field> : public std::true_type
    {
        /** ****************************************************************************************
         * Applies type
         * \ref aworx::lib::strings::Format::Field "Format::Field".
         *
         * @param target The object that \b Apply was invoked on.
         * @param field  The object to \e apply.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        ALIB_API static   integer Apply( AString& target, const Format::Field& field);
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c Format::Escape.   */
    template<> struct T_Apply<Format::Escape> : public std::true_type
    {
        /** ****************************************************************************************
         * Applies type
         * \ref aworx::lib::strings::Format::Escape "Format::Escape".
         *
         * @param target The object that \b Apply was invoked on.
         * @param field  The object to \e apply.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        ALIB_API static   integer Apply( AString& target, const Format::Escape& field);
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c int8_t.   */
    template<> struct T_Apply<int8_t> : public std::true_type
    {
        /**
         * Applies type \c int8_t. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline   integer Apply( AString& target,  int8_t& value )
        {
            return T_Apply<Format>::Apply( target, Format( static_cast<int64_t >(value), nullptr ) );
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c uint8_t.   */
    template<> struct T_Apply<uint8_t> : public std::true_type
    {
        /**
         * Applies type \c uint8_t. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline   integer Apply( AString& target,  uint8_t& value )
        {
            return T_Apply<Format>::Apply( target, Format( static_cast<uint64_t >(value), nullptr ) );
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c int16_t.   */
    template<> struct T_Apply<int16_t> : public std::true_type
    {
        /**
         * Applies type \c int16_t. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.

         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline   integer Apply( AString& target,  int16_t& value )
        {
            return T_Apply<Format>::Apply( target, Format( value, nullptr ) );
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c uint16_t.   */
    template<> struct T_Apply<uint16_t> : public std::true_type
    {
        /**
         * Applies type \c uint16_t. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline   integer Apply( AString& target,  uint16_t& value )
        {
            return T_Apply<Format>::Apply( target, Format( value, nullptr ) );
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c int32_t.   */
    template<> struct T_Apply<int32_t> : public std::true_type
    {
        /**
         * Applies type \c int32_t. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline   integer Apply( AString& target,  int32_t& value )
        {
            return T_Apply<Format>::Apply( target, Format( value, nullptr ) );
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c uint32_t.   */
    template<> struct T_Apply<uint32_t> : public std::true_type
    {
        /**
         * Applies type \c uint32_t. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline   integer Apply( AString& target,  uint32_t& value )
        {
            return T_Apply<Format>::Apply( target, Format( value, nullptr ) );
        }
    };


    /** Specialization of template struct \alib{strings,T_Apply} for type \c int64_t.   */
    template<> struct T_Apply<int64_t> : public std::true_type
    {
        /**
         * Applies type \c int64_t. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline   integer Apply( AString& target,  int64_t& value )
        {
            return T_Apply<Format>::Apply( target, Format( value, nullptr ) );
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c uint64_t.   */
    template<> struct T_Apply<uint64_t> : public std::true_type
    {
        /**
         * Applies type \c uint64_t. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline   integer Apply( AString& target,  uint64_t& value )
        {
            return T_Apply<Format>::Apply( target, Format( value, nullptr ) );
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c intGap_t.   */
    template<> struct T_Apply<intGap_t> : public std::true_type
    {
        /**
         * Applies type  #aworx::intGap_t. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline   integer Apply( AString& target,  intGap_t& value )
        {
            return T_Apply<Format>::Apply( target, Format( value, nullptr ) );
        }
    };


    /** Specialization of template struct \alib{strings,T_Apply} for type \c uintGap_t.   */
    template<> struct T_Apply<uintGap_t> : public std::true_type
    {
        /**
         * Applies type #aworx::uintGap_t. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline   integer Apply( AString& target,  uintGap_t& value )
        {
            return T_Apply<Format>::Apply( target, Format( value, nullptr ) );
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c float.   */
    template<> struct T_Apply<float> : public std::true_type
    {
        /**
         * Applies type \c float. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline integer Apply( AString& target, float& value)
        {
            return T_Apply<Format>::Apply( target, Format( static_cast<double>(value), nullptr ) );
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c double.   */
    template<> struct T_Apply<double> : public std::true_type
    {
        /**
         * Applies type \c double. Creates an object of type
         * \ref aworx::lib::strings::Format "Format" with default values
         * and passes this to the corresponding \alib{strings,T_Apply}\<Format\> specialization.
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write.
         * @return The number of characters appended to target.
         */
        static inline integer Apply( AString& target, double& value)
        {
            return T_Apply<Format>::Apply( target, Format( value, nullptr ) );
        }
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c Format::Bin.   */
    template<> struct T_Apply<Format::Bin> : public std::true_type
    {
        /** ****************************************************************************************
         * Applies objects of type
         * \ref aworx::lib::strings::Format::Bin "Format::Bin".
         *
         * @param target The object that \b Apply was invoked on.
         * @param fmt    The format object.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        ALIB_API static integer Apply( AString& target,  const Format::Bin& fmt );
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c Format::Hex.   */
    template<> struct T_Apply<Format::Hex> : public std::true_type
    {
        /** ****************************************************************************************
         * Applies objects of type
         * \ref aworx::lib::strings::Format::Hex "Format::Hex".
         *
         * @param target The object that \b Apply was invoked on.
         * @param fmt    The format object.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        ALIB_API static integer Apply( AString& target,  const Format::Hex& fmt );
    };

    /** Specialization of template struct \alib{strings,T_Apply} for type \c Format::Oct.   */
    template<> struct T_Apply<Format::Oct> : public std::true_type
    {
        /** ****************************************************************************************
         * Applies objects of type
         * \ref aworx::lib::strings::Format::Oct "Format::Oct".
         *
         * @param target The object that \b Apply was invoked on.
         * @param fmt    The format object.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        ALIB_API static integer Apply( AString& target,  const Format::Oct& fmt );
    };

#if !defined(DOX_PARSER)
    ALIB_WARNINGS_RESTORE
#endif

// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::apply to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
}
#endif


}} // namespace lib::strings

/** Type alias name in namespace #aworx. */
using Format =    aworx::lib::strings::Format;

} // namespace aworx





#endif // HPP_ALIB_STRINGS_BUILTIN_APPLICABLES
