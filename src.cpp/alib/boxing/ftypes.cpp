// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################


#include "alib/alib.hpp"

#if ALIB_FEAT_BOXING_FTYPES

#include <algorithm>
#include <cmath>

#if !defined(_GLIBCXX_CSTRING) && !defined(_CSTRING_)
    #include <cstring>
#endif

// #################################################################################################
// Singletons
// #################################################################################################

namespace aworx { namespace lib { namespace boxing {

/**
 *
 * <b>ALib %Boxing</b> allows to map C++ types to boxed types in a non-bijective way. As a
 * consequence, there are different possibilities to implement such mapping and the mapping
 * that <b>ALib %Boxing</b> uses by default for boxing C++ fundamental types is considered to
 * be just a proposal and a default behavior.
 *
 * To suppress the use of this built-in implementation of boxing C++ fundamental types,
 * compilation symbol \ref ALIB_FEAT_BOXING_FTYPES_OFF may be passed to the compiler.
 * This freedom of choice is \b limited when using the full distribution of \b %ALib or a
 * \ref alib_namespace_organization_of_code "distribution module"
 * of ALib that includes more \b %ALib functionality than just boxing. In these cases,
 * the default built-in implementation of boxing fundamental types is automatically chosen, because
 * other parts of \b %ALib rely on the default behavior. Using \ref ALIB_FEAT_BOXING_FTYPES_OFF
 * with these distributions results in a compilation error.
 *
 * The mapping of C++ fundamental types to boxed types is done as follows:
 * - Character types \c char, \c wchar_t, \c char16_t and \c char32_t are mapped to
 *   identical boxed types.
 * - Arrays of character types are mapped to boxed arrays of the respective character type, e.g
 *   \c char[5] &rarr; \c char[] or \c wchar_t[10] &rarr; \c wchar_t[]. The array length is of-course
 *   stored in the box.
 * - Pointers to character types the same  mapped to arrays of the respective character type, e.g
 *   \c char* &rarr; \c char[] or \c wchar_t* &rarr; \c wchar_t[]. The array length is set to
 *   \c 0 if either the pointer is \c nullptr or the first character in the string is \c '\0'.
 *   Otherwise, the length is set to \c -1. Therefore, when unboxing a character array type
 *   or implementing such type in an \ref aworx::lib::boxing::Interface "Interface" implementation,
 *   the "true" length has to be evaluated if \c -1 is stored!
 * - Type \c bool is mapped to identical boxed type.
 * - All signed integer types (\c int8_t, \c int16_t, \c int32_t, \c int64_t and
 *   \ref aworx::lib::lang::intGap_t "intGap_t") are boxed as
 *   \ref aworx::lib::boxing::ftypes::boxed_int "boxed_int", which is an alias of \c int64_t.
 * - All unsigned integer types (\c uint8_t, \c uint16_t, \c uint32_t, \c uint64_t and
 *   \ref aworx::lib::lang::uintGap_t "uintGap_t") are boxed as
 *   \ref aworx::lib::boxing::ftypes::boxed_uint "boxed_uint", which is an alias of \c uint64_t.
 * - Type \c float and \c double are both boxed as \c double.
 * - Unboxing is implemented in a strict fashion: Only the "result" types are allowed to be
 *   unboxed, hence \c char, \c wchar_t, \c char16_t, \c char32_t, \c bool, \c %boxed_int, \c %boxed_uint
 *   and \c double.
 *
 *
 * \see For more information about this default implementation of %boxing C++ fundamental types,
 *      see manual chapter \ref alib_namespace_boxing_types_ftypes "4.2 Boxing Fundamental Types".
 *
 * \attention
 *   In this namespace documentation, you will find specializations of templated namespace functions
 *   of namespace \c aworx::lib::boxing. This is of-course wrong in respect to the C++ language
 *   definition, which requires such specializations to be placed in the original namespace.<br>
 *   It was decided to 'trick' the [documentation parser](http://www.stack.nl/~dimitri/doxygen) to
 *   show these specialization in this namespace, to keep namespace \b %boxing
 *   clean and to have all specializations related to this namespace in one place.
 */
namespace ftypes
{

// #################################################################################################
// IEquals_Tdouble
// #################################################################################################
bool IEquals_Tdouble::Invoke( const Box& box, const Box& comp )
{
    if( !comp.IsType<double>() )
        return false;
    double d1=   box.Unbox<double>();
    double d2= comp.Unbox<double>();

    // we can ignore this warning, because we fixed it with the second test
    #if defined(__clang__)
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wfloat-equal"
    #endif
    return      d1 == d2
            // we are using the float epsilon which is already bigger than the double epsilon.
            // furthermore, we double the epsilon!
            ||  std::abs( d1 - d2 ) <
                std::abs( (std::min)(d1, d2) * static_cast<double>( 2.0f * std::numeric_limits<float>::epsilon() ) );
    #if defined(__clang__)
        #pragma clang diagnostic pop
    #endif
}




// #################################################################################################
// IEquals for arrays of type char, wchar_t, char16_t and char32_t
// #################################################################################################
bool    IEquals_TcharArr::Invoke ( const Box& box, const Box& comp )
{
    if ( !comp.IsArrayOf<char>() )
        return false;

    const char* compBuf= reinterpret_cast<char*>( comp.UnboxRaw() );
    const char*  boxBuf= reinterpret_cast<char*>(  box.UnboxRaw() );
    if ( (boxBuf == nullptr) != (compBuf == nullptr) )
            return false;

    size_t compLen= comp.Length() >= 0 ? static_cast<size_t>( comp.Length() )
                                       : compBuf != nullptr ? strlen( compBuf )
                                       : 0;
    size_t  boxLen=  box.Length() >= 0 ? static_cast<size_t>( box.Length() )
                                       :  boxBuf != nullptr ? strlen( boxBuf )
                                       : 0;
    if ( boxLen != compLen )
        return false;


    return  0 == strncmp ( boxBuf, compBuf, static_cast<size_t>(boxLen) );
}

bool    IEquals_Twchar_tArr::Invoke ( const Box& box, const Box& comp )
{
    if ( !comp.IsArrayOf<wchar_t>() )
        return false;

    const wchar_t* compBuf= reinterpret_cast<wchar_t*>(comp.UnboxRaw());
    const wchar_t*  boxBuf= reinterpret_cast<wchar_t*>(box.UnboxRaw());
    if ( (boxBuf == nullptr) != (compBuf == nullptr) )
            return false;

    size_t compLen= comp.Length() >= 0 ? static_cast<size_t>( comp.Length() )
                                       : compBuf != nullptr ? wcslen( compBuf )
                                       : 0;
    size_t  boxLen=  box.Length() >= 0 ? static_cast<size_t>( box.Length() )
                                       :  boxBuf != nullptr ? wcslen(  boxBuf )
                                       : 0;
    if ( boxLen != compLen )
        return false;


    return  0 == wcsncmp ( boxBuf, compBuf, static_cast<size_t>(boxLen) );
}

bool    IEquals_Tchar16_tArr::Invoke ( const Box& box, const Box& comp )
{
    if ( !comp.IsArrayOf<char16_t>() )
        return false;

    const char16_t* compBuf= reinterpret_cast<char16_t*>(comp.UnboxRaw());
    const char16_t*  boxBuf= reinterpret_cast<char16_t*>(box.UnboxRaw());
    if ( (boxBuf == nullptr) != (compBuf == nullptr) )
            return false;

    size_t compLen= comp.Length() >= 0 ? static_cast<size_t>( comp.Length() )
                                       : aworx::lib::ALIB::strlen16( compBuf );
    size_t boxLen=   box.Length() >= 0 ? static_cast<size_t>(  box.Length() )
                                       : aworx::lib::ALIB::strlen16(  boxBuf );
    if ( boxLen != compLen )
        return false;

    size_t idx= 0;
    while( idx < boxLen )
    {
        if( boxBuf[idx] != compBuf[idx] )
            return false;
        idx++;
    }
    return  true;
}

bool    IEquals_Tchar32_tArr::Invoke ( const Box& box, const Box& comp )
{
    if ( !comp.IsArrayOf<char32_t>() )
        return false;

    const char32_t* compBuf= reinterpret_cast<char32_t*>(comp.UnboxRaw());
    const char32_t*  boxBuf= reinterpret_cast<char32_t*>(box.UnboxRaw());
    if ( (boxBuf == nullptr) != (compBuf == nullptr) )
            return false;

    size_t compLen= comp.Length() >= 0 ? static_cast<size_t>( comp.Length() )
                                       : aworx::lib::ALIB::strlen32( compBuf );
    size_t boxLen=   box.Length() >= 0 ? static_cast<size_t>(  box.Length() )
                                       : aworx::lib::ALIB::strlen32(  boxBuf );
    if ( boxLen != compLen )
        return false;

    size_t idx= 0;
    while( idx < boxLen )
    {
        if( boxBuf[idx] != compBuf[idx] )
            return false;
        idx++;
    }
    return  true;
}

}}}}// namespace aworx::lib::boxing

#endif // ALIB_FEAT_BOXING_FTYPES
