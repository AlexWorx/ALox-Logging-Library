// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_AWORX_LIB_ALIB) || defined(HPP_AWORX_LIB_STRINGS_ASLITERAL)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_LIB_STRINGS_ASLITERAL
#define HPP_AWORX_LIB_STRINGS_ASLITERAL 1

// #################################################################################################
// includes
// #################################################################################################

#if !defined (_GLIBCXX_IOSFWD )     && !defined(_IOSFWD_)
    #include <iosfwd>
#endif
#if !defined (_GLIBCXX_CCTYPE) && !defined (_CCTYPE_)
    #include <cctype>
#endif

// conditional expression is constant for using our constant template parameters to select
// checking vs. non-checking method versions
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4127 )
    #pragma warning( disable : 4307 ) // also: integral constant overflow, because of TMP
#endif

namespace aworx {
namespace           lib {
namespace                   strings {


/** ************************************************************************************************
 * This templated class is a specialization of class #ASTerminatable which has a fixed length.
 * Functions that accept such objects as a parameter can rely
 * at compile time on the constant length of the string and optimize their performance
 * accordingly. <br>
 * For example, template method
 * \ref aworx::lib::strings::ASAlloc::operator<<(const T&  op) "AString::operator<<(const T&)"
 * which internally makes use of template method
 * \ref aworx::lib::strings::ASAlloc::Apply "AString::Apply" will append
 * ASLiterals (up to a certain amount of characters) without doing a copy loop.
 *
 * The class is useful to assign string literals to objects, including their lengths and pass
 * them around, hence the name.<br>
 *
 * \note This class \b %ASLiteral, when used in source code as well as in documentations, is
 *       mostly referred to using the synonym '<b>%StringLiteral</b>'. For more information about
 *       the synonymous names of ALib string classes, refer to
 *       \ref alib_namespace_strings_class_overview "String Classes Overview" and
 *       \ref CPP_AWORX_NS_SHORTCUTS "Type Shortcuts in the aworx Namespace".
 *
 * @tparam TLength The length of the represented string.
***************************************************************************************************/
template<size_t TLength>
class ASLiteral : public ASTerminatable
{
    public:
    /** ********************************************************************************************
     * The only available constructor taking a string literal of exactly the size we have plus one
     * for the termination character.
     * @param src  The string literal to represent.
     * @tparam TCapacity  The capacity of the given buffer. The length of this string is set
     *         to this value -1.
     **********************************************************************************************/
    constexpr ASLiteral( const char (&src)[TLength + 1]  )
    : ASTerminatable( src, TLength )
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
* Template meta programming (TMP) helper class to get the buffer and (constant) length
* of a string literal.
* Specializations exist for C++ string literals and ALib type
* \ref aworx::lib::strings::ASLiteral "ASLiteral.
*
* \note This struct is of internal nature. For standard use of ALib strings, there is no
*       no need to know about it.<br>
*       However, if user defined string types exist which have a length known at compile time,
*       ALib users might want to implement a specialization for that type.
*       The benefit lies in a performance gain. For example, appending types (of smaller sizes)
*       to objects of type
*       \ref aworx::lib::strings::ASAlloc "AString" does not invoke memcpy() by inlining the
*       right number of single copy commands.
***********************************************************************************************/
template<typename TLiteral>        struct TMPLiteral
{
    /// The length of the literal
    enum      { Length= -1      };

    /// Returns the buffer of the literal given as void*.
    /// @return The Buffer of the literal.
    static const char* Buffer(void* )  { return nullptr; }

};

#if !defined( IS_DOXYGEN_PARSER )
    template<size_t TLength>    struct TMPLiteral<ASLiteral<TLength>>
    {
        enum      { Length= TLength      };
        static const char* Buffer(void* o) { return ((AS*) o)->Buffer(); }
    };

    template<size_t TCapacity>  struct TMPLiteral<char [TCapacity]>
    {
        enum      { Length= TCapacity -1 };
        static const char* Buffer(void* o) { return (const char*) o; }
    };

#endif



}}} // namespace aworx::lib::strings

#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
#endif // HPP_AWORX_LIB_STRINGS_ASLITERAL
