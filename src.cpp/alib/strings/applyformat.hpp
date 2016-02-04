// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/**@file*///<- needed for Doxygen include of the typedefs at the end of the file

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_AWORX_LIB_ALIB) || defined(HPP_AWORX_LIB_STRINGS_APPLY_FORMAT)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (_GLIBCXX_CCTYPE) && !defined (_CCTYPE_)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_LIB_STRINGS_APPLY_FORMAT
#define HPP_AWORX_LIB_STRINGS_APPLY_FORMAT 1


// This is for testing internal include order, see stdafx_alib.h
#if defined(HPP_AWORX_LIB_STRINGS_NUMBERFORMAT)
    #error "ALib Include order error"
#endif
#if defined(HPP_AWORX_LIB_STRINGS_TOKENIZER)
    #error "ALib Include order error"
#endif
#if defined(HPP_AWORX_LIB_STRINGS_ASSUBSTRING)
    #error "ALib Include order error"
#endif

// #################################################################################################
// includes
// #################################################################################################
#if !defined (_GLIBCXX_CCTYPE) && !defined (_CCTYPE_)
    #include <cctype>
#endif

namespace aworx {
namespace           lib {
namespace                   strings {


// #################################################################################################
// class Format
// #################################################################################################

    /** ********************************************************************************************
     * This class aggregates several public inner classes. Each of these classes has partial
     * implementations of template function
     * \ref ApplyTo( AString&, const T).
     **********************************************************************************************/
    class Format
    {
        public:

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::ASAlloc "AString" with
         * \ref aworx::lib::strings::ApplyTo(AString&, const Format::Tab&) "corresponding specialization"
         *  of template function
         * \ref aworx::lib::strings::ApplyTo "ApplyTo".
         *
         * Appends \e tab characters (as provided) to reach a certain length (aka tabulator position)
         * of the \p target. The tab position is referenced to an optionally given \p reference value
         * which might be the start of the string or the position of the last newline. If this
         * parameter is negative, the last newline characters are searched from the end of the
         * string backwards.<br>
         * Referring to that as position 0, the tab position is then located at the next multiple
         * of parameter \p tabSize, after having added  \p minPad tab characters.
         ******************************************************************************************/
        class Tab
        {
            public:
            /** The tab positions are multiples of this value.*/
            int         tabSize;

            /** The reference length of the AString which is taken as relative tab position
             *  (instead of the beginning of the string). If -1, the target %AString is
             *  searched backwards for the last newline and this position is used as the
             *  reference.
             */
            int         reference;

            /** The minimum pad characters to add. Defaults to 1. */
            int         minPad;

            /** The character to insert to reach the tab position. Normally thsi is the space
             *  character ' '.*/
            char         tabChar;

            /**
             * Constructor, copying the values into this 'delegate' object. They will be used
             * when template method
             * \ref ApplyTo( AString&, const Format::Tab&) with this instance is invoked.
             *
             * @param tabSize   The tab positions are multiples of this parameter.
             * @param reference The reference length of the AString.
             *                  If -1, the last new-line character is searched from the end of
             *                  the string backwards, and used. Defaults to 0.
             * @param minPad    The minimum pad characters to add. Defaults to 1.
             * @param tabChar   The character to insert to reach the tab position.
             *                  Defaults to ' ' (space).
             */
            Tab(  int tabSize, int reference = 0, int minPad= 1, char tabChar= ' ' )
            : tabSize(tabSize), reference(reference), minPad(minPad), tabChar(tabChar)
            {}
        };

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::ASAlloc "AString" with
         * \ref aworx::lib::strings::ApplyTo(AString&, const Format::Field&) "corresponding specialization"
         *  of template function
         * \ref aworx::lib::strings::ApplyTo "ApplyTo".
         *
         * Appends the contents of a string to to the AString using a
         * defined 'field'-width.
         * If given string \p value is shorter than parameter \p width specifies, the field is
         * filled with a corresponding amount of \p padChar characters.<br>
         * Parameter \p alignment of type
         * \ref aworx::lib::enums::Alignment "Alignment" allows to left-, right- or center-align
         * the contents of the field.
         ******************************************************************************************/
        class Field
        {
            public:
            const AS&          contents;   ///< the contents of the field.
            int                width;      ///< the width of the field.
            enums::Alignment   alignment;  ///< the alignment of the contents within the field.
            char               padChar;    ///< the characters used for padding the contents within the field.

            /**
             * Constructor, copying the values into this 'delegate' object. They will be used
             * when template method
             * \ref ApplyTo( AString&, const Format::Field&) with this instance is invoked.
             *
             * @param contents  The contents of the field.
             * @param width     The width of the field
             * @param alignment The alignment of the contents within the field.
             *                  Defaults to
             *                  \ref aworx::lib::enums::Alignment "Alignment::Right"
             *                  Other options are
             *                  \ref aworx::lib::enums::Alignment "Alignment::Left" and
             *                  \ref aworx::lib::enums::Alignment "Alignment::Center".
             * @param padChar   The character used to fill the field up to its size.
             *                  Defaults to ' ' (space).
             */
            Field(  const AS&         contents,
                    int               width,
                    enums::Alignment  alignment  =enums::Alignment::Right,
                    char              padChar    = ' '                    )
            : contents(contents.IsNotNull() ? contents : EmptyString ), width(width), alignment(alignment), padChar(padChar)
            {
            }
        };

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::ASAlloc "AString" with
         * \ref aworx::lib::strings::ApplyTo(AString&, const Format::Int32&) "corresponding specialization"
         *  of template function
         * \ref aworx::lib::strings::ApplyTo "ApplyTo".<p>
         *  Appends an \e int32_t value using a minimum number of digits.
         *  If given constructor parameter \p value has less digits than parameter \p minDigits
         *  specifies, then a corresponding amount of '0' characters are prepended.<br>
         *  The given value \p minDigits is cut to the range 1..20 ( which equals the maximum
         *  digits of a 64 bit unsigned integer value, which is the largest integer processed
         *  in overloaded methods).
         ******************************************************************************************/
        class Int32
        {
            public:
            int32_t  value;      ///< The value
            int      minDigits;  ///< The minimum number of digits to write

            /**
             *  Constructor, taking the value and the minimum number of digits
             *  @param   value      The value to write.
             *  @param   minDigits  The minimum number of digits to write.
             */
            Int32(int32_t value, int minDigits ) : value(value), minDigits(minDigits)   {};
        };

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::ASAlloc "AString" with
         * \ref aworx::lib::strings::ApplyTo(AString&, const Format::UInt32&) "corresponding specialization"
         *  of template function
         * \ref aworx::lib::strings::ApplyTo "ApplyTo".<p>
         *  Appends an \e uint32_t value using a minimum number of digits.
         *  If given constructor parameter \p value has less digits than parameter \p minDigits
         *  specifies, then a corresponding amount of '0' characters are prepended.<br>
         *  The given value \p minDigits is cut to the range 1..20 ( which equals the maximum
         *  digits of a 64 bit unsigned integer value, which is the largest integer processed
         *  in overloaded methods).
         ******************************************************************************************/
        class UInt32
        {
            public:
            uint32_t value;      ///< The value
            int      minDigits;  ///< The minimum number of digits to write

            /**
             *  Constructor, taking the value and the minimum number of digits
             *  @param   value      The value to write.
             *  @param   minDigits  The minimum number of digits to write.
             */
            UInt32(uint32_t value, int minDigits ) : value(value), minDigits(minDigits)   {};
        };


        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::ASAlloc "AString" with
         * \ref aworx::lib::strings::ApplyTo(AString&, const Format::Int64&) "corresponding specialization"
         *  of template function
         * \ref aworx::lib::strings::ApplyTo "ApplyTo".<p>
         *  Appends an \e int64_t value using a minimum number of digits.
         *  If given constructor parameter \p value has less digits than parameter \p minDigits
         *  specifies, then a corresponding amount of '0' characters are prepended.<br>
         *  The given value \p minDigits is cut to the range 1..20 ( which equals the maximum
         *  digits of a 64 bit unsigned integer value, which is the largest integer processed
         *  in overloaded methods).
         ******************************************************************************************/
        class Int64
        {
            public:
            int64_t  value;      ///< The value
            int      minDigits;  ///< The minimum number of digits to write

            /**
             *  Constructor, taking the value and the minimum number of digits
             *  @param   value      The value to write.
             *  @param   minDigits  The minimum number of digits to write.
             */
            Int64(int64_t value, int minDigits ) : value(value), minDigits(minDigits)   {};
        };

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::ASAlloc "AString" with
         * \ref aworx::lib::strings::ApplyTo(AString&, const Format::UInt64&) "corresponding specialization"
         *  of template function
         * \ref aworx::lib::strings::ApplyTo "ApplyTo".<p>
         *  Appends an \e uint64_t value using a minimum number of digits.
         *  If given constructor parameter \p value has less digits than parameter \p minDigits
         *  specifies, then a corresponding amount of '0' characters are prepended.<br>
         *  The given value \p minDigits is cut to the range 1..20.
         ******************************************************************************************/
        class UInt64
        {
            public:
            uint64_t value;      ///< The value
            int      minDigits;  ///< The minimum number of digits to write

            /**
             *  Constructor, taking the value and the minimum number of digits
             *  @param   value      The value to write.
             *  @param   minDigits  The minimum number of digits to write.
             */
            UInt64(uint64_t value, int minDigits ) : value(value), minDigits(minDigits)   {};
        };

        /** ****************************************************************************************
         * Parameter class used for \e application to objects of type
         * \ref aworx::lib::strings::ASAlloc "AString" with
         * \ref aworx::lib::strings::ApplyTo(AString&, const Format::Double&) "corresponding specialization"
         *  of template function
         * \ref aworx::lib::strings::ApplyTo "ApplyTo".<p>
         *  Appends a \e double value using the given format
         *  parameters or an existing object of type
         *  \ref aworx::lib::strings::NumberFormat "NumberFormat".
         ******************************************************************************************/
        class Double
        {
            public:
            double          value;      ///< The value
            NumberFormat*   nf;         ///< The number format to use

            /**
             *  Constructor, taking the value and formating parameters
             *  @param   value The value to write.
             *  @param   nf    The number format. If nullptr,
             *                 \ref aworx::lib::strings::NumberFormat::Global "NumberFormat::Global"
             *                 is used.
             */
            Double(double value, NumberFormat* nf ) : value(value), nf(nf)         {};
        };
    };



// #################################################################################################
// Corresponding ApplyTo specializations
// #################################################################################################


    /** ********************************************************************************************
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  \ref aworx::lib::strings::Format::Tab "Format::Tab".
     *
     * @param  target   The object that \b Apply was invoked on.
     * @param  tab      The object to \e apply.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  ALIB_API   int ApplyTo( AString& target, const Format::Tab& tab);
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const Format::Tab&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  const Format::Tab& value )
        {  return  ApplyTo<const Format::Tab&>( target,           value );  }
    #endif


    /** ********************************************************************************************
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  \ref aworx::lib::strings::Format::Field "Format::Field".
     *
     * @param target The object that \b Apply was invoked on.
     * @param field  The object to \e apply.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  ALIB_API   int ApplyTo( AString& target, const Format::Field& field);
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const Format::Field&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  const Format::Field& value )
        {  return  ApplyTo<const Format::Field&>( target,             value );  }
    #endif


    /** ********************************************************************************************
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  \ref aworx::lib::strings::Format::Int32 "Format::Int32".
     *
     * @param target The object that \b Apply was invoked on.
     * @param fmt    The format object.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  ALIB_API int   ApplyTo( AString& target,  const Format::Int32& fmt );
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const Format::Int32&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  const Format::Int32& value )
        {  return  ApplyTo<const Format::Int32&> ( target,            value );  }
    #endif

    /**
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *   <em>int8_t</em>. Invokes
     *  \ref aworx::lib::strings::Format::Int32 "Format::Int32(value, 1)".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write.
     * @return The number of characters appended to target.
     */
    template<>  inline   int   ApplyTo( AString& target,  int8_t& value )
    {
        return ApplyTo<const Format::Int32&>( target, Format::Int32( value, 1) );
    }
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  inline   int   ApplyTo_NC( AString& target,      int8_t& value )
        {  return  ApplyTo<const Format::Int32&>( target, Format::Int32( value, 1) );  }
    #endif

    /**
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *   <em>uint8_t</em>. Invokes
     *  \ref aworx::lib::strings::Format::Int32 "Format::Int32(value, 1)".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write.
     * @return The number of characters appended to target.
     */
    template<>  inline   int   ApplyTo( AString& target,  uint8_t& value )
    {
        return ApplyTo<const Format::Int32&>( target, Format::Int32( value, 1) );
    }
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  inline   int   ApplyTo_NC( AString& target,      uint8_t& value )
        {  return  ApplyTo<const Format::Int32&>( target, Format::Int32( value, 1) );  }
    #endif


    /**
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *   <em>int16_t</em>. Invokes
     *  \ref aworx::lib::strings::Format::Int32 "Format::Int32(value, 1)".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write.
     * @return The number of characters appended to target.
     */
    template<>  inline   int   ApplyTo( AString& target,  int16_t& value )
    {
        return ApplyTo<const Format::Int32&>( target, Format::Int32( value, 1) );
    }
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  inline   int   ApplyTo_NC( AString& target,      int16_t& value )
        {  return  ApplyTo<const Format::Int32&>( target, Format::Int32( value, 1) ); }
    #endif

    /**
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *   <em>uint16_t</em>. Invokes
     *  \ref aworx::lib::strings::Format::Int32 "Format::Int32(value, 1)".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write.
     * @return The number of characters appended to target.
     */
    template<>  inline   int   ApplyTo( AString& target,  uint16_t& value )
    {
        return ApplyTo<const Format::Int32&>( target, Format::Int32( value, 1) );
    }
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  inline   int   ApplyTo_NC( AString& target,      uint16_t& value )
        {  return  ApplyTo<const Format::Int32&>( target, Format::Int32( value, 1) );  }
    #endif

    /**
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *   <em>int32_t</em>. Invokes
     *  \ref aworx::lib::strings::Format::Int32 "Format::Int32(value, 1)".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write.
     * @return The number of characters appended to target.
     */
    template<>  inline   int   ApplyTo( AString& target,  int32_t& value )
    {
        return ApplyTo<const Format::Int32&>( target, Format::Int32( value, 1) );
    }
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const int32_t&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,      int32_t& value )
        {  return  ApplyTo<int32_t&>( target,     value );  }
    #endif

    /** ********************************************************************************************
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  \ref aworx::lib::strings::Format::UInt32 "Format::UInt32".
     *
     * @param target The object that \b Apply was invoked on.
     * @param fmt    The format object.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  ALIB_API int   ApplyTo( AString& target,  const Format::UInt32& fmt );
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const Format::UInt32&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  const Format::UInt32& value )
        {  return  ApplyTo<const Format::UInt32&>( target,             value );  }
    #endif

    /**
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  <em>uint32_t</em>. Invokes
     *  \ref aworx::lib::strings::Format::UInt32 "Format::UInt32(value, 1)".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write.
     * @return The number of characters appended to target.
     */
    template<>  inline   int   ApplyTo( AString& target,  uint32_t& value)
    {
        return ApplyTo<const Format::UInt32&>( target, Format::UInt32( value, 1) );
    }
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const uint32_t&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,    uint32_t& value )
        {  return  ApplyTo<uint32_t&>( target,    value );  }
    #endif

    /** ********************************************************************************************
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  \ref aworx::lib::strings::Format::Int64 "Format::Int64".
     *
     * @param target The object that \b Apply was invoked on.
     * @param fmt    The format object.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  ALIB_API int   ApplyTo( AString& target,  const Format::Int64& fmt );
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const Format::Int64&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  const Format::Int64& value )
        {  return  ApplyTo<const Format::Int64&>( target,             value );  }
    #endif

    /**
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  <em>int64_t</em>. Invokes
     *  \ref aworx::lib::strings::Format::Int64 "Format::Int64(value, 1)".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write.
     * @return The number of characters appended to target.
     */
    template<>  inline   int   ApplyTo( AString& target,  int64_t& value)
    {
        return ApplyTo<const Format::Int64&>( target, Format::Int64( value, 1) );
    }
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const int64_t&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  int64_t& value )
        {  return  ApplyTo<int64_t&>( target,  value );  }
    #endif

    /** ********************************************************************************************
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  \ref aworx::lib::strings::Format::UInt64 "Format::UInt64".
     *
     * @param target The object that \b Apply was invoked on.
     * @param fmt    The format object.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  ALIB_API int   ApplyTo( AString& target,  const Format::UInt64& fmt );
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const Format::UInt64&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  const Format::UInt64& value )
        {  return  ApplyTo<const Format::UInt64&>( target,              value );  }
    #endif

    /**
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  <em>uint64_t</em>. Invokes
     *  \ref aworx::lib::strings::Format::UInt64 "Format::UInt64(value, 1)".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write.
     * @return The number of characters appended to target.
     */
    template<>  inline   int   ApplyTo( AString& target,  uint64_t& value )
    {
        return ApplyTo<const Format::UInt64&>( target, Format::UInt64( value, 1) );
    }
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const uint64_t&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  uint64_t& value )
        {  return  ApplyTo<uint64_t&>( target,  value );  }
    #endif

    /** ********************************************************************************************
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  \ref aworx::lib::strings::Format::Double "Format::Double".
     *
     * @param target The object that \b Apply was invoked on.
     * @param fmt    The format object.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  ALIB_API int   ApplyTo( AString& target, const Format::Double& fmt );
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const Format::Double&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  const Format::Double& value )
        {  return  ApplyTo<const Format::Double&>( target,              value );  }
    #endif

    /**
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  <em>double</em>. Invokes
     *  \ref aworx::lib::strings::Format::Double "Format::Double(value, nullptr)".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write.
     * @return The number of characters appended to target.
     */
    template<>  inline int     ApplyTo( AString& target, double& value)
    {
        return ApplyTo<const Format::Double&>( target, Format::Double( value, nullptr ) );
    }
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const double&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,   double& value )
        {  return  ApplyTo<const Format::Double&>( target, Format::Double( value, nullptr ) );  }
    #endif

    /**
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type
     *  <em>float</em>. Invokes
     *  \ref aworx::lib::strings::Format::Double "Format::Double(value, nullptr)".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write.
     * @return The number of characters appended to target.
     */
    template<>  inline int     ApplyTo( AString& target, float& value)
    {
        return ApplyTo<const Format::Double&>( target, Format::Double( value, nullptr ) );
    }
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct         IsApplicable<const float&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,   float& value )
        {  return  ApplyTo<const Format::Double&>( target, Format::Double( value, nullptr ) );  }
    #endif

}}} // namespace aworx::lib::strings

#endif // HPP_AWORX_LIB_STRINGS_APPLY_FORMAT
