// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include guard
#ifndef HPP_ALIB_STRINGS_LITERAL
#define HPP_ALIB_STRINGS_LITERAL 1

// to preserve the right order, we are not includable directly from outside.
#if !defined(ALIB_PROPER_INCLUSION)
    #error "include 'alib/alib.hpp' or 'alib/alib_strings.hpp' instead of this header"
#endif

// #################################################################################################
// includes
// #################################################################################################


// conditional expression is constant for using our constant template parameters to select
// checking vs. non-checking method versions
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4127 )
    #pragma warning( disable : 4307 ) // also: integral constant overflow, because of TMP
#endif

namespace aworx { namespace lib { namespace strings
{

/** ************************************************************************************************
 * This templated class is a specialization of class #TString which has a fixed length.
 * Functions that accept such objects as a parameter can rely
 * at compile time on the constant length of the string and optimize their performance
 * accordingly. <br>
 * For example, template method
 * \ref aworx::lib::strings::AString::operator<<(const T&  op) "AString::operator<<(const T&)"
 * which internally makes use of template method
 * \ref aworx::lib::strings::AString::Apply "AString::Apply" will append objects of this type
 * without doing a copy loop (up to a certain amount of characters).
 *
 * The class is useful to assign string literals to objects, including their lengths and pass
 * them around, hence the name.<br>
 *
 * It might also used to provide strings with variable contents. For this, the character
 * array given in the constructor needs to be managed and manipulated outside of this class.
 *
 * \note
 *   This class \b %StringLiteral, when used in source code as well as in documentations, is
 *   often referred to using the synonym '<b>%SLiteral</b>'. For more information about
 *   the synonymous names of \b %ALib string classes, refer to
 *   \ref alib_namespace_strings_class_overview "String Classes Overview" and
 *   \ref CPP_AWORX_NS_SHORTCUTS "Type Shortcuts of Namespace aworx".
 *
 * @tparam TLength The length of the represented string.
***************************************************************************************************/
template<size_t TLength>
class StringLiteral : public TString
{
    public:
    /** ********************************************************************************************
     * The only available constructor taking a string literal of exactly the size we have plus one
     * for the termination character.
     * @param src  The string literal to represent.
     **********************************************************************************************/
    constexpr StringLiteral( const char (&src)[TLength + 1]  )
    : TString( src, TLength )
    {}

    /** ********************************************************************************************
     * Copies the contents of this string (excluding the terminating zero) to the given
     * destination using static method #Copy(char*, const char*).
     *
     * @param dest The destination buffer.
     **********************************************************************************************/
    inline
    void Copy( char* dest)  { Copy( dest, buffer ); }

    /** ********************************************************************************************
     * Static method that copies TLength characters from the given the source array to the
     * given destination array.
     * If template parameter \p TLength equals or is greater than zero, memcpy() is used. If it is
     * below, the right amount of single character copy operations (no loops, no ifs) is  inserted
     * into the code.
     *
     * @param src  The source buffer to copy from.
     * @param dest The destination buffer to copy to..
     **********************************************************************************************/
    static
    inline
    void Copy( char* dest, const char* src)
    {
        if (TLength >= 10 )
        {
            memcpy( dest,  src, TLength );
            return;
        }

        if (TLength == 9 ) goto copy9;
        if (TLength == 8 ) goto copy8;
        if (TLength == 7 ) goto copy7;
        if (TLength == 6 ) goto copy6;
        if (TLength == 5 ) goto copy5;
        if (TLength == 4 ) goto copy4;
        if (TLength == 3 ) goto copy3;
        if (TLength == 2 ) goto copy2;
        if (TLength == 1 ) goto copy1;
        return;

        copy9: *dest++=   *src++;
        copy8: *dest++=   *src++;
        copy7: *dest++=   *src++;
        copy6: *dest++=   *src++;
        copy5: *dest++=   *src++;
        copy4: *dest++=   *src++;
        copy3: *dest++=   *src++;
        copy2: *dest++=   *src++;
        copy1: *dest  =   *src;
    }
};


/** ************************************************************************************************
 * Specialization of template struct \ref aworx::lib::strings::T_StringLiteral for all
 * template class \ref aworx::lib::strings::StringLiteral "StringLiteral<TLength>".
 *
 * @tparam TLength The length of the represented string.
 **************************************************************************************************/
template<size_t TLength>
struct T_StringLiteral<StringLiteral<TLength>> : public std::true_type
{
    /**
     * Returns the buffer of the literal.
     * @param src The pointer to the source string literal
     * @return The buffer of the literal.
     */
    static inline constexpr const char* Buffer(const StringLiteral<TLength>& src) { return src.Buffer(); }

    /**
     * Returns the constant \p TLength of type <b>StringLiteral<TLength></b>.
     * @return The length.
     */
    static inline constexpr integer    Length()        { return TLength; }
};



}} // namespace lib::strings


/** Type alias name in namespace #aworx. */
template<size_t TLength>
using     SLiteral  =        aworx::lib::strings::StringLiteral<TLength>;

// #################################################################################################
// aworx namespace string singletons
// #################################################################################################

/** The system dependent new line character code(s). */
#if defined(_WIN32)
    constexpr static       lib::strings::StringLiteral<2>   NewLine { "\r\n" };
#else
    constexpr static       lib::strings::StringLiteral<1>   NewLine { "\n" };
#endif

/** Characters that are usually ignored or trimmed. */
constexpr     static       lib::strings::StringLiteral<4>   DefaultWhitespaces { " \n\r\t" };

} // namespace aworx



#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
#endif // HPP_ALIB_STRINGS_LITERAL
