// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

// needed for Doxygen include of the typedefs at the end of the file
/**@file*/

// include guard
#ifndef HPP_ALIB_STRINGS_APPLYTO
#define HPP_ALIB_STRINGS_APPLYTO 1

// to preserve the right order, we are not includable directly from outside.
#if !defined(ALIB_PROPER_INCLUSION)
    #error "include 'alib/alib.hpp' or 'alib/alib_strings.hpp' instead of this header"
#endif


// This is for testing internal include order, see stdafx_alib.h
#if defined(HPP_ALIB_STRINGS_NUMBERFORMAT)
    #error "ALib Include order error"
#endif
#if defined(HPP_ALIB_STRINGS_TOKENIZER)
    #error "ALib Include order error"
#endif
#if defined(HPP_ALIB_STRINGS_SUBSTRING)
    #error "ALib Include order error"
#endif


#if defined(DOX_PARSER)

/** ************************************************************************************************
 * @addtogroup GrpALibMacros
 * @{
 * @name Macros Supporting TMP Class T_Apply
 * TMP class
 * \ref aworx::lib::strings::T_Apply "T_Apply" may be specialized for user types to allow the
 * <em>"application"</em> of custom object of type
 * \ref aworx::lib::strings::AString "AString".
 * The following macros simplify such specialization.
 *
 * @{
 *  \def ALIB_STRINGS_SPECIALIZE_T_APPLY
 *  Helper macro for specializing struct
 *  \ref aworx::lib::strings::T_Apply "T_Apply" for type \p TYPE.
 *  This macro has to be positioned outside of any namespace and the given type has to include
 *  its full namespace qualification.
 *
 *  This macro is to be used in combination with macro #ALIB_STRINGS_SPECIALIZE_T_APPLY_DEF.<br>
 *  As an alternative to the two macros, #ALIB_STRINGS_SPECIALIZE_T_APPLY_INLINE might be used, which will
 *  specialize \c T_Apply and define method \b %Apply inline.
 *
 *  \see \ref alib_namespace_strings_astring_applyto "Applying Objects to AStrings"
 *
 *  @param TYPE The type to specialize struct \b %T_Apply for.
 *
 *  \def ALIB_STRINGS_SPECIALIZE_T_APPLY_DEF
 *  Macro used in combination with \ref ALIB_STRINGS_SPECIALIZE_T_APPLY which specializes struct
 *  \ref aworx::lib::strings::T_Apply "T_Apply" for type \p TYPE and with this declares its
 *  member function \b %Apply.<br>
 *  This macro is used for the implementation of this member function.
 *
 *  @param TYPE  The type that struct \b %T_Apply was specialized for.
 *  @param IMPL The implementation code for method \b %Apply.
 *
 *  \def ALIB_STRINGS_SPECIALIZE_T_APPLY_INLINE
 *  Helper macro for specializing struct
 *  \ref aworx::lib::strings::T_Apply "T_Apply" for a custom type for custom type \p TYPE.
 *  This macro has to be positioned outside of any namespace and the given type has to include
 *  its full namespace qualification.
 *
 *  With the specialization of struct \b %T_Apply, method \b %Apply will be defined and
 *  implemented inline.
 *
 *  Macros #ALIB_STRINGS_SPECIALIZE_T_APPLY and #ALIB_STRINGS_SPECIALIZE_T_APPLY_DEF
 *  provide a non-inline alternative to this macro.
 *
 *  \see \ref alib_namespace_strings_astring_applyto "Applying Objects to AStrings"
 *
 *  @param TYPE The type to specialize struct \b %T_Apply for.
 *  @param IMPL The implementation code for method \b %Apply.
 *
 * @}
 * @} //ingroup GrpALibMacros
 **************************************************************************************************/
#define ALIB_STRINGS_SPECIALIZE_T_APPLY(TYPE)
#define ALIB_STRINGS_SPECIALIZE_T_APPLY_DEF(TYPE, IMPL)
#define ALIB_STRINGS_SPECIALIZE_T_APPLY_INLINE(TYPE, IMPL)

#else

 #define ALIB_STRINGS_SPECIALIZE_T_APPLY(TYPE)                                                     \
    namespace aworx { namespace lib { namespace strings {                                          \
   template<> struct       T_Apply<TYPE> : public std::true_type                                   \
  { static integer Apply( AString& target, const TYPE src );  }; }}}

#define ALIB_STRINGS_SPECIALIZE_T_APPLY_DEF(TYPE, IMPL)                                            \
aworx::lib::lang::integer aworx::lib::strings::T_Apply<TYPE>::Apply(AString& target, const TYPE src) \
{ IMPL }

 #define ALIB_STRINGS_SPECIALIZE_T_APPLY_INLINE(TYPE, IMPL)                                        \
    namespace aworx { namespace lib { namespace strings {                                          \
   template<> struct       T_Apply<TYPE> : public std::true_type                                   \
  { static inline integer Apply( AString& target, const TYPE src ){ IMPL }  }; }}}

#endif // else of defined(DOX_PARSER)

// #################################################################################################
// struct T_Apply: fundamental types
// #################################################################################################
namespace aworx { namespace lib { namespace strings
{

// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::applyto to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
namespace applyto {
#endif

    /** Specialization of template struct \ref T_Apply for type \c char*.   */
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

    /** Specialization of template struct \ref T_Apply for type \c wchar_t*.   */
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

    /** Specialization of template struct \ref T_Apply for type \c char16_t*.   */
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
            target.Append( src, static_cast<integer>( ALIB::strlen16( src ) ) );
            return 0; // nullptr treatment already done
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c char32_t*.   */
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
            target.Append( src, static_cast<integer>( ALIB::strlen32( src ) ) );
            return 0; // nullptr treatment already done
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c bool.   */
    template<> struct       T_Apply<bool> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the words "true" or "false" to the given AString
         * @param target The object that \b Apply was invoked on.
         * @param b      The boolean to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, bool& b )
        {
            target._<false>( b ? "true" : "false" );
            return 1;
        }
    };


#if ALIB_DEBUG
    /** Specialization of template struct \ref T_Apply for type \c std::type_info.   */
    template<> struct       T_Apply<std::type_info> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the demangled type name.
         * @param target The object that \b Apply was invoked on.
         * @param type   The type to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const std::type_info& type )
        {
            target._<false>( debug::TypeDemangler( type ).Get() );
            return 1;
        }
    };
#endif

// #################################################################################################
// struct T_Apply(): ALib enum types (mostly for debugging)
// #################################################################################################

    /** Specialization of template struct \ref T_Apply for type \c lang::Switch.   */
    template<> struct       T_Apply<lang::Switch> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b Switch
         * @param target  The object that \b Apply was invoked on.
         * @param value   The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::Switch& value )
        {
            target._<false>( value == lang::Switch::On ? "On" : "Off" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::Case.   */
    template<> struct       T_Apply<lang::Case> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b Case
         * @param target  The object that \b Apply was invoked on.
         * @param value   The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::Case& value )
        {
            target._<false>( value == lang::Case::Ignore ? "Ignore" : "Sensitive" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::Alignment.   */
    template<> struct       T_Apply<lang::Alignment> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b Alignment
         * @param target The object that \b Apply was invoked on.
         * @param value      The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::Alignment& value )
        {
            target._<false>( value == lang::Alignment::Left   ? "Left" :
                      value == lang::Alignment::Center ? "Center" :
                                                          "Right" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::Inclusion.   */
    template<> struct       T_Apply<lang::Inclusion> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b Inclusion
         * @param target The object that \b Apply was invoked on.
         * @param value      The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::Inclusion& value )
        {
            target._<false>( value == lang::Inclusion::Include ? "Include" : "Exclude" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::CurrentData.   */
    template<> struct       T_Apply<lang::CurrentData> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class
         * \ref aworx::lib::lang::CurrentData "CurrentData".
         *
         * @param target The object that \b Apply was invoked on.
         * @param value  The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::CurrentData& value )
        {
            target._<false>( value == lang::CurrentData::Keep ? "Keep" : "Clear" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::Safeness.   */
    template<> struct       T_Apply<lang::Safeness> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b Safeness
         * @param target The object that \b Apply was invoked on.
         * @param value      The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::Safeness& value )
        {
            target._<false>( value == lang::Safeness::Safe ? "Safe" : "Unsafe" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::Responsibility.   */
    template<> struct       T_Apply<lang::Responsibility> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b Responsibility
         * @param target The object that \b Apply was invoked on.
         * @param value      The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::Responsibility& value )
        {
            target._<false>( value == lang::Responsibility::KeepWithSender ? "KeepWithSender" : "Transfer" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::Timezone.   */
    template<> struct       T_Apply<lang::Timezone> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b Timezone
         * @param target The object that \b Apply was invoked on.
         * @param value      The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::Timezone& value )
        {
            target._<false>( value == lang::Timezone::Local ? "Local" : "UTC" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::LockMode.   */
    template<> struct       T_Apply<lang::LockMode> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b LockMode
         * @param target The object that \b Apply was invoked on.
         * @param value      The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::LockMode& value )
        {
            target._<false>( value == lang::LockMode::Recursive ? "Recursive" : "SingleLocks" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::Whitespaces.   */
    template<> struct       T_Apply<lang::Whitespaces> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b Whitespaces
         * @param target The object that \b Apply was invoked on.
         * @param value      The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::Whitespaces& value )
        {
            target._<false>( value == lang::Whitespaces::Trim ? "Trim" : "Keep" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::Create.   */
    template<> struct       T_Apply<lang::Create> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b Create
         * @param target The object that \b Apply was invoked on.
         * @param value      The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::Create& value )
        {
            target._<false>( value == lang::Create::Never ? "Never" : "IfNotExistent" );
            return 1;
        }
    };

    /** Specialization of template struct \ref T_Apply for type \c lang::Propagation.   */
    template<> struct       T_Apply<lang::Propagation> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the values of enum class \b Propagation
         * @param target The object that \b Apply was invoked on.
         * @param value      The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lang::Propagation& value )
        {
            target._<false>( value == lang::Propagation::Omit ? "Omit" : "ToDescendants" );
            return 1;
        }
    };

    //! @endcond NO_DOX

// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::apply to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
}
#endif


}}} // namespace aworx::lib::strings

#endif // HPP_ALIB_STRINGS_APPLYTO
