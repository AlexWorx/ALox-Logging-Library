// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_COMPATIBILITY_STD_STRING)
    #error "Header already included"
#endif

#ifndef HPP_ALIB_COMPATIBILITY_STD_STRING
//! @cond NO_DOX
#define HPP_ALIB_COMPATIBILITY_STD_STRING 1
//! @endcond NO_DOX
#include <string>

// #################################################################################################
// ALib String / std::string compatibility support
// #################################################################################################
#if ALIB_MODULE_STRINGS

namespace aworx { namespace lib { namespace strings
{
// We are faking all template specializations of namespace boxing for doxygen into namespace
// boxing::thirdparty to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
namespace thirdparty { namespace std {
#endif
    // ######################### String construction from std::string  #############################

    /** ********************************************************************************************
     * Specialization of struct
     * \ref aworx::lib::strings::T_String "T_String" for type \c std::string.
     **********************************************************************************************/
    template<>   struct      T_String<std::string>   : public std::true_type
    {
        /** ****************************************************************************************
         * Returns the  result of \c std::string::c_str.
         *
         * @param  src    The source string.
         * @return The buffer to the contents of \p src.
         ******************************************************************************************/
        static inline
        const char* Buffer( const std::string& src )
        {
            return  src.c_str();
        }

        /** ****************************************************************************************
         * Returns the  result of \c std::string::c_str.
         *
         * @param  src    The source string.
         * @return The length of \p src.
         ******************************************************************************************/
        static inline
        integer Length( const std::string& src )
        {
            return static_cast<integer>( src.length() );
        }
    };

    // ################################ ApplyTo for std::wstring  ###################################

    /** Specialization of template struct \ref T_Apply for type \c std::wstring.   */
    template<>   struct T_Apply<std::wstring>   : public std::true_type
    {

        /** ****************************************************************************************
         * Appends contents of \p src to \p target.
         *
         * @param  target The AString to append \p src to.
         * @param  src    The source string.
         * @return The length of the given string \p src which was appended to \p target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const std::wstring& src )
        {
            target.Append( src.c_str(),  static_cast<integer>( src.length()) );
            return static_cast<integer>( src.length() );
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c std::u16string.   */
    template<>   struct T_Apply<std::u16string>   : public std::true_type
    {
        /** ****************************************************************************************
         * Appends contents of \p src to \p target.
         *
         * @param  target The AString to append \p src to.
         * @param  src    The source string.
         * @return The length of the given string \p src which was appended to \p target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const std::u16string& src )
        {
            target.Append( src.c_str(),  static_cast<integer>( src.length()) );
            return static_cast<integer>( src.length() );
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c std::u32string.   */
    template<>   struct T_Apply<std::u32string>   : public std::true_type
    {
        /** ****************************************************************************************
         * Appends contents of \p src to \p target.
         *
         * @param  target The AString to append \p src to.
         * @param  src    The source string.
         * @return The length of the given string \p src which was appended to \p target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const std::u32string& src )
        {
            target.Append( src.c_str(),  static_cast<integer>( src.length()) );
            return static_cast<integer>( src.length() );
        }
    };

    // #############################  ToStdString (from std::string)  ##############################

    /** ********************************************************************************************
     *  Copies or appends a region of a given \ref aworx::lib::strings::String "String" into
     *  a \c std::string.
     *  The region is adjusted to the length of the %String.
     *
     * @param as            The \ref aworx::lib::strings::String "String" to convert into a std::string.
     * @param target        A result std::string to copy the specified region into.
     * @param regionStart   The start index of the region to be copied.
     * @param regionLength  The maximum length of the region to be copied.
     *                      Defaults to CString::MaxLen.
     * @param targetData    If \c CurrentData::Keep, the target \c std::string is not cleared before
     *                      the result is written. Defaults to \c CurrentData::Clear.
     *
     * @return The (modified) std::string& result that was provided (for concatenation of calls).
     **********************************************************************************************/
    inline
    std::string& ToStdString( const String&      as,
                              std::string&       target,
                              integer           regionStart,
                              integer           regionLength    = CString::MaxLen,
                              lang::CurrentData  targetData      = lang::CurrentData::Clear )
    {

        if ( targetData == lang::CurrentData::Clear )
            target.clear();

        // adjust range, if empty return empty string
        if ( as.AdjustRegion( regionStart, regionLength ) )
            return target;

        // copy our buffer into target
        target.append( as.Buffer() , static_cast<size_t>(regionStart), static_cast<size_t>(regionLength ) );
        return  target;
    }

    /** ********************************************************************************************
     * Copies a region of a given \ref aworx::lib::strings::String "String" into a \c std::string
     * which is created.
     * The region is adjusted to the length of the %String.
     *
     * @param as            The \ref aworx::lib::strings::String "String" to convert into a std::string.
     * @param regionStart   The start index of the region in this to create the std::string from.
     * @param regionLength  The maximum length of the region to be copied.
     *                      Defaults to CString::MaxLen.
     *
     * @return A string that represents the specified sub region of this object.
     **********************************************************************************************/
    inline
    std::string  ToStdString( const String& as,
                              integer         regionStart,
                              integer      regionLength= CString::MaxLen )
    {
        std::string result;
        ToStdString( as, result, regionStart, regionLength, lang::CurrentData::Keep );
        return result;
    }

    /** ********************************************************************************************
     * Copies the contents of a given \ref aworx::lib::strings::String "String" into the given
     * \c std::string.
     *
     * @param as            The \ref aworx::lib::strings::String "String" to convert into a std::string.
     * @return A std::string that represents this object.
     **********************************************************************************************/
    inline
    std::string  ToStdString( const String& as )
    {
        return ToStdString( as, 0, as.Length() );
    }


    /** ********************************************************************************************
     * Copies the contents of a given \ref aworx::lib::strings::String "String" into the
     * given \c std::string.
     *
     * @param as           The \ref aworx::lib::strings::String "String" to convert into a std::string.
     * @param target       A target std::string to copy the contents of this %String into.
     * @param targetData   If \c CurrentData::Keep, parameter \p target is not cleared before
     *                     the result is written. Defaults to \c CurrentData::Clear.
     * @return The (modified) result that was provided (for concatenation of calls).
     **********************************************************************************************/
    inline
    std::string& ToStdString( const String&     as,
                              std::string&      target,
                              lang::CurrentData targetData = lang::CurrentData::Clear )
    {
        return ToStdString( as, target, 0, as.Length(), targetData );
    }

// We are faking all template specializations of namespace boxing for doxygen into namespace
// boxing::thirdparty to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
}}
#endif


}}}

#endif // ALIB_MODULE_STRINGS

// #################################################################################################
// ALib %Boxing / std::string compatibility support
// #################################################################################################

#if ALIB_MODULE_BOXING

#if !ALIB_FEAT_BOXING_FTYPES
    static_assert(0, "This implementation of boxing std::string may be used only if default "
                     "boxing of fundamental types is activated."
#endif

#if !defined(DOX_PARSER)
ALIB_WARNINGS_START_TMP
#endif
namespace aworx { namespace lib { namespace boxing
{

// We are faking all template specializations of namespace boxing for doxygen into namespace
// boxing::thirdparty to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
/**
 * \attention
 *   This is a non-existing namespace! It is exclusively defined for the
 *   [documentation parser](http://www.stack.nl/~dimitri/doxygen).
 *
 * \attention
 *   In this <b>"documentation namespace"</b>, you will find sub namespaces
 *   which in turn are purely created for documentation.
 */
namespace thirdparty {
/**
 * Implements <b>ALib %Boxing</b> for string types of the standard library.
 * On boxing, the string types are mapped to boxing arrays of the corresponding character types.
 *
 * \note The boxing definitions described here are available through header file <br>
 *       <b>"alib/compatiblity/std_string.hpp"</b>.
 *
 *  The following customizations are made:
 *  - Type \c std::string is boxed as \c char[]
 *  - Type \c std::wstring is boxed as \c wchar_[]
 *  - Type \c std::u16string is boxed as \c char16_t[]
 *  - Type \c std::u32string is boxed as \c char32_t[]
 *
 *  The same mapping applies for pointer types of named std types.
 *
 *  All types are unboxable als values.
 *
 * \note
 *   Namespace function  #InitStdString is to be invoked on bootstrap to complete the support
 *   of <c>std::string</c>-type boxing.
 *
 * \attention
 *   This is a non-existing namespace, exclusively defined for the
 *   [documentation parser](http://www.stack.nl/~dimitri/doxygen).
 *   This documentation is moved here to keep the original namespace documentation clean.
 */
namespace std {
#endif
#if !defined(DOX_PARSER)


    // ###################################  Boxing std::string  ####################################
//! [DOX_ALIB_BOXING_STRINGS_CUSTOM_RECIPE_1]
ALIB_BOXING_SPECIALIZE_CB_CUB( std::string, char, true, true );
//! [DOX_ALIB_BOXING_STRINGS_CUSTOM_RECIPE_1]

//! [DOX_ALIB_BOXING_STRINGS_CUSTOM_RECIPE_2]
inline   void  T_Boxing<std::string>::Boxing( Box& box,  const std::string&  value )
{
    box.data.Value=  reinterpret_cast<boxvalue>( value.c_str()  );
    box.data.Length= static_cast     <integer>( value.length() );
}
//! [DOX_ALIB_BOXING_STRINGS_CUSTOM_RECIPE_2]


//! [DOX_ALIB_BOXING_STRINGS_CUSTOM_RECIPE_3]
inline  std::string    T_Boxing<std::string>::Unboxing( const Box& box )
{
    return  std::string( (const char*) box.data.Value,
                          box.data.Length >= 0 ? static_cast<size_t>(box.data.Length)
                                               : strlen( (const char*) box.data.Value )
                       );
}
//! [DOX_ALIB_BOXING_STRINGS_CUSTOM_RECIPE_3]

    // ##########################  Boxing wstring/u16string/u32string  ####################################
    ALIB_BOXING_SPECIALIZE_CB_CUB( std::wstring,    wchar_t, true, true );
    ALIB_BOXING_SPECIALIZE_CB_CUB( std::u16string, char16_t, true, true );
    ALIB_BOXING_SPECIALIZE_CB_CUB( std::u32string, char32_t, true, true );

    inline   void  T_Boxing<std::wstring>::Boxing( Box& box,  const std::wstring&  value )
    {
        box.data.Value=    (boxvalue) value.c_str();
        box.data.Length=   static_cast<integer>(value.length());
    }

    inline   void  T_Boxing<std::u16string>::Boxing( Box& box,  const std::u16string&  value )
    {
        box.data.Value=    (boxvalue) value.c_str();
        box.data.Length=   static_cast<integer>(value.length());
    }

    inline   void  T_Boxing<std::u32string>::Boxing( Box& box,  const std::u32string&  value )
    {
        box.data.Value=    (boxvalue) value.c_str();
        box.data.Length=   static_cast<integer>(value.length());
    }

    inline  std::wstring    T_Boxing<std::wstring>::Unboxing( const Box& box )
    {
        return  std::wstring( (const wchar_t*) box.data.Value,
                              box.data.Length >= 0 ? static_cast<size_t>(box.data.Length)
                                                   : wcslen( (const wchar_t*) box.data.Value )
                            );
    }

    inline  std::u16string    T_Boxing<std::u16string>::Unboxing( const Box& box )
    {
        return  std::u16string( (const char16_t*) box.data.Value,
                                box.data.Length >= 0 ? static_cast<size_t>(box.data.Length)
                                                     : aworx::lib::ALIB::strlen16( (const char16_t*) box.data.Value )
                              );

    }

    inline  std::u32string    T_Boxing<std::u32string>::Unboxing( const Box& box )
    {
        return  std::u32string( (const char32_t*) box.data.Value,
                                box.data.Length >= 0 ? static_cast<size_t>(box.data.Length)
                                                     : aworx::lib::ALIB::strlen32( (const char32_t*) box.data.Value )
                              );
    }
#endif


void InitStdString();
/**
 * Initializes <b>ALib %Boxing</b> system in respect to boxing <c>std::string</c>-types.
 *
 * This method is \b not automatically invoked with
 * \ref aworx::lib::ALIB::Init "ALIB::Init", because the support for boxing
 * <c>std::string</c>-types is optional and due to the inclusion of header
 * <b>"alib/compatibility/std_string.hpp"</b>.
 *
 * In general boxing of <c>std::string</c>-types works well without the one-time invocation of
 * this function at the bootstrap of a process. What this method currently adds is interface
 * \ref aworx::lib::strings::boxing::IApply "IApply" for boxed type
 * \ref aworx::lib::boxing::BoxedAs "BoxedAs<std::string>" and similar std string types. This is only
 * needed in some particular use cases.
 */
inline void InitStdString()
{
    #if ALIB_MODULE_STRINGS
//! [DOX_ALIB_BOXING_STRINGS_CUSTOM_RECIPE_4]
aworx::lib::boxing::DefineInterface<BoxedAs<std::string   >  , false , strings::boxing::IApply_BoxedAs_TApplicable<std::string   >>();
//! [DOX_ALIB_BOXING_STRINGS_CUSTOM_RECIPE_4]
        aworx::lib::boxing::DefineInterface<BoxedAs<std::wstring  >  , false , strings::boxing::IApply_BoxedAs_TApplicable<std::wstring  >>();
        aworx::lib::boxing::DefineInterface<BoxedAs<std::u16string>  , false , strings::boxing::IApply_BoxedAs_TApplicable<std::u16string>>();
        aworx::lib::boxing::DefineInterface<BoxedAs<std::u32string>  , false , strings::boxing::IApply_BoxedAs_TApplicable<std::u32string>>();
    #endif
}


// We are faking all template specializations of namespace boxing for doxygen into namespace
// boxing::thirdparty to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
}}
#endif

}}} // namespace [aworx::lib::boxing]
#if !defined(DOX_PARSER)
ALIB_WARNINGS_RESTORE
#endif

#endif // ALIB_MODULE_BOXING

#endif // HPP_ALIB_COMPATIBILITY_STD_STRING
