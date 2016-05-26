    // #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/**@file*///<- needed for Doxygen include of the typedefs at the end of the file

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_ALIB) || defined(HPP_ALIB_STRINGS_APPLYTO)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_ALIB_STRINGS_APPLYTO
#define HPP_ALIB_STRINGS_APPLYTO 1


// This is for testing internal include order, see stdafx_alib.h
#if defined(HPP_ALIB_STRINGS_NUMBERFORMAT)
    #error "ALib Include order error"
#endif
#if defined(HPP_ALIB_STRINGS_TOKENIZER)
    #error "ALib Include order error"
#endif
#if defined(HPP_ALIB_STRINGS_ASSUBSTRING)
    #error "ALib Include order error"
#endif

// conditional expression is constant for using our constant template parameters to select
// checking vs. non-checking method versions
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4127 )
#endif

/** ************************************************************************************************
 * @ingroup GrpALibMacros
 * @{
 *
 * \def ALIB_STRINGS_APPLYTO_DECLARATION
 * Macro to declare method \b %ApplyTo (including template type \b %IsApplicable) for a custom
 * type. Parameter \p type has to exclude specifiers \c const and \c &.<br>
 * This macro has to be positioned outside any namespace and the given type has to include
 * the its full namespace qualification.
 *
 * This macro is to be used in combination with macro #ALIB_STRINGS_APPLYTO_DEFINITION.<br>
 * As an alternative to the two macros, #ALIB_STRINGS_APPLYTO_INLINE might be used, which will
 * declare and define the method \c inline.
 *
 * \see \ref alib_namespace_strings_astring_applyto "Applying Objects to AStrings"
 *
 * @param TYPE The type to declare to be applicable to an instance of class AString.
 **************************************************************************************************/
#define ALIB_STRINGS_APPLYTO_DECLARATION(TYPE)                                          \
namespace aworx { namespace lib { namespace  strings {                                  \
    template<>  struct       IsApplicable<const TYPE &> : public std::true_type {};     \
    template<>  int ApplyTo( AString& target, const TYPE & );                           \
}}}


/** ************************************************************************************************
 * \def ALIB_STRINGS_APPLYTO_DEFINITION
 * Macro to implement method \b %ApplyTo for a custom type.
 * Parameter \p type has to exclude specifiers \c const and \c &.<br>
 * This macro has to be positioned outside any namespace and the given type has to include
 * the its full namespace qualification.
 *
 * This macro is to be used in combination with macro #ALIB_STRINGS_APPLYTO_DECLARATION.<br>
 * As an alternative to the two macros, #ALIB_STRINGS_APPLYTO_INLINE might be used, which will
 * declare and define the method \c inline.
 *
 * Parameter \p IMPLEMENTATION, which has to provide the source code that applies the value
 * of a type, does not need to contain curly braces and has to refer to variables \p target
 * (the AString) and \p src (the value that is to be applied to the AString).
 *
 * \see \ref alib_namespace_strings_astring_applyto "Applying Objects to AStrings"
 *
 * @param TYPE           The type to implement method \b %ApplyTo for.
 * @param IMPLEMENTATION The implementation code.
 **************************************************************************************************/
#define ALIB_STRINGS_APPLYTO_DEFINITION(TYPE, IMPLEMENTATION)                            \
template<>  int aworx::lib::strings::ApplyTo( AString& target, const TYPE & src )        \
{                                                                                        \
    IMPLEMENTATION                                                                       \
}

/** ************************************************************************************************
 * \def ALIB_STRINGS_APPLYTO_INLINE
 * Macro to define method \b %ApplyTo (including template type \b %IsApplicable) for a custom
 * type. Parameter \p type has to exclude specifiers \c const and \c &.<br>
 * This macro has to be positioned outside any namespace and the given type has to include
 * the its full namespace qualification.
 *
 * This macro is for declaring and defining the method inline (usually used in a header file).
 * As an alternative, macros #ALIB_STRINGS_APPLYTO_DECLARATION (header file) and
 * #ALIB_STRINGS_APPLYTO_DEFINITION (source file) might be used to avoid redundant inline code
 * generation.
 *
 * Parameter \p IMPLEMENTATION, which has to provide the source code that applies the value
 * of a type, does not need to contain curly braces and may has to refer to variables \p target
 * (the AString) and \p src (the value that is to be applied to the AString).
 *
 * \see \ref alib_namespace_strings_astring_applyto "Applying Objects to AStrings"
 *
 * @param TYPE           The type to declare to be applicable to an instance of class AString.
 * @param IMPLEMENTATION The implementation code.
 **************************************************************************************************/
#define ALIB_STRINGS_APPLYTO_INLINE(TYPE, IMPLEMENTATION)                                       \
namespace aworx { namespace lib { namespace  strings {                                          \
    template<>  struct       IsApplicable<const TYPE &> : public std::true_type {};             \
    template<>  inline   int ApplyTo( AString& target, const TYPE & src )                       \
    {                                                                                           \
        IMPLEMENTATION                                                                          \
    }                                                                                           \
}}}

/** @} */

// #################################################################################################
// includes
// #################################################################################################
namespace aworx {
namespace           lib {
namespace                   strings {


// #################################################################################################
// ApplyTo(): main template method
// #################################################################################################

    /** ********************************************************************************************
     * This is a TMP (template meta programming) 'class' which defaults the question
     * <c>IsApplicable<T>::value</c> to \c false for any type.<br>
     * When implementing specializations of template method
     * \ref ApplyTo<T> for custom types, this class has to be specialized as well.
     * Otherwise, a compile time assertion (<em>static_assert</em>) will fail whenever an object
     * of the type is appended to an object of type
     * \ref aworx::lib::strings::AString "AString".
     *
     * Definition has to be made as follows:
    \verbatim
        template<>  struct IsApplicable<T> : public std::true_type {};
    \endverbatim
     * where T is the type that is to be defined given as a const reference. For example, class
     * \ref aworx::lib::strings::Format::Field "Format::Field" is using
    \verbatim
        template<>  struct IsApplicable<const Format::Field&> : public std::true_type {};
    \endverbatim
     *
     **********************************************************************************************/
    template<typename Type>   struct IsApplicable     : public std::false_type { };

    /** ********************************************************************************************
     * This template function supports applying 'external' user defined types
     * to objects of type
     * \ref aworx::lib::strings::AString "AString". It has a central role for using ALib in a
     * \ref aworx::lib "non intrusive" way, by allowing to pass external string types just as
     * the are when appending them to objects of type %AString. Furthermore, a list of built-in
     * operations on objects of type %AString are implemented using the mechanism provided with
     * this function and new, custom operations might be defined.
     *
     * Partially specialized versions of this method are invoked by method
     * \ref aworx::lib::strings::AString::Apply "AString::Apply"
     * with template parameter \p src.
     *
     * To restrict the need for specializations of this method to a single variant of the external type,
     * template type \p T will always be a "constant reference". As an example, if the external type was
     * '<em>class MyString></em>' and a non-constant pointer to an object of that type was applied
     * to an %AString, the template parameter \p T would still be '<em>const MyString &</em>'.
     *
     *  \note
     *    Some more complex applicable types might want to return extended information by setting
     *    own members during the application process. To achieve this, the corresponding
     *    implementations of \b %ApplyTo have to cast the given const reference to a
     *    non-const reference. This is considered a good practice, as the const specifier
     *    most probably was added by the TMP operations of method
     *    \ref aworx::lib::strings::AString::Apply "AString::Apply" anyhow only for the reason
     *    to have one single template specialization per type.
     *
     * The implementation itself may do 'whatever' is wanted' with the %AString provided in
     * parameter \p target. For string types, simple append operations are predefined. More
     * complex operations format the string, convert integer and floating point numbers, etc.
     *
     * For allowing static (compile time) assertions when user code tries to apply arbitrary
     * types that are not supported with specializations of this method, it is necessary to implement
     * struct
     * \ref aworx::lib::strings::IsApplicable "IsApplicable" whenever this method is specialized.
     *
     * Optionally it is possible to also implement a sibling template function
     * \ref aworx::lib::strings::ApplyTo_NC(AString& target, const T src) "ApplyTo_NC". If function
     * <em>ApplyTo_NC</em> is specialized in parallel to a specialization of this function,
     * <em>ApplyTo_NC</em> will be used if a non-checking method of class %AString is used to
     * apply an object. See \ref alib_namespace_strings_nonchecking for more information.
     *
     * For basic user defined string types that get adopted to ALib string system using function
     * <em>ToString</em>, it is advisable to also generate
     * a specialization of this function and of struct <em>%IsApplicable</em>. Therefore, the sample
     * provided with method <em>ToString</em> demonstrates also this function. See template function
     *\ref aworx::lib::strings::ToString(const TString) "ToString" for that sample.
     *
     * Built-in specializations of this function and according type definitions exist,
     * as listed in reference documentation of class
     * \ref aworx::lib::strings::AString "AString".
     * As a sample, one type and according specialization is class
     * \ref aworx::lib::strings::Format::Field "Format::Field". The invocation is simple
     * and nicely readable:
     * \snippet "DOX_ALIB_APPLYTO.cpp"     DOX_ALIB_APPLYTO_FIELD
     * which produces:
     * \snippet "DOX_ALIB_APPLYTO_FIELD.txt"     OUTPUT
     *
     * The next sample implements this function for ALib class
     * \ref aworx::lib::time::Ticks "Ticks" to print out a formatted date:
     * \snippet "DOX_ALIB_APPLYTO.cpp"     DOX_ALIB_APPLYTO_DEFINITION
     * With this definition included, user code might now do this:
     * \snippet "DOX_ALIB_APPLYTO.cpp"     DOX_ALIB_APPLYTO_USE
     *
     *  The output will be something like this:
     *
     * \snippet "DOX_ALIB_APPLYTO.txt"     OUTPUT
     *
     * \note This sample is kept simple. In real life, class
     *       \ref aworx::lib::time::TicksCalendarTime "TicksCalendarTime" should be used to
     *       implement more options.
     *
     * Easy declaration and definition of method \b %ApplyTo (and template class \b %IsApplicable)
     * is supported with macros
     * - #ALIB_STRINGS_APPLYTO_DECLARATION,
     * - #ALIB_STRINGS_APPLYTO_DEFINITION and alternatively macro
     * - #ALIB_STRINGS_APPLYTO_INLINE.
     *
     * @param   target The object of type %AString that will have object \p src applied.
     * @param   src    The source object of arbitrary type will get applied to %AString \p target.
     *
     * @returns If an append operation is implemented with a specialization, the number of
     *          characters that got appended should be returned ('should' here means that at least
     *          a non zero, positive value has to be returned) and -1 if the object \p src
     *          which is to be applied represented a \e nulled object.
     *          Returning -1 causes the AString to be \e nulled if the apply operation was invoked through
     *          \ref aworx::lib::strings::AString::operator= "AString assignment operator".
     *
     *          If nothing is supposed to be append, this method must return 0.
     *
     **********************************************************************************************/
    template<typename T>  inline int ApplyTo( AString& target, const T src )
    {
        (void) target;
        (void) src;

        #if defined(_MSC_VER)
            #pragma warning( push )
            #pragma warning( disable : 4127 ) //conditional expression is constant
        #endif
        // prevent invoking us with unknown types
        using TPlain= typename std::remove_const    <
                      typename std::remove_pointer  <
                      typename std::remove_reference<
                      typename std::remove_const    < T >::type>::type>::type>::type;

        static_assert(
                std::is_pod      <        TPlain > ::value
            ||  std::is_base_of  <String, TPlain > ::value
            ||  IsApplicable <const TPlain&> ::value
        , "ALib: T is not a known type to append to AString. Implement ApplyTo<T>() to enable conversion.");

        ALIB_DEBUG_CODE( target.Apply("ApplyTo<Unknown Type>") );
        ALIB_WARNING("Unknown type for ApplyTo()");
        return 0;

        #if defined(_MSC_VER)
            #pragma warning( pop )
        #endif
    }

    /** ********************************************************************************************
     * This function can be optionally specialized for dedicated types, next to function \b ApplyTo.
     * See \ref aworx::lib::strings::ApplyTo "ApplyTo" for more information.
     *
     * @param   target The object of type %AString that will get object \p src applied.
     * @param   src    The object of type arbitrary type will get applied to %AString \p target.
     *
     * @returns If an append operation is implemented with a specialization, the number of
     *          characters that got appended should be returned and -1 if the object \p src
     *          to apply represented a \e nulled object.
     *          I nothing is supposed to be append, this method must return 0.
     **********************************************************************************************/
    template<typename T>  inline int ApplyTo_NC( AString& target, const T src )
    {
        // by default use non checking apply
        return ApplyTo<T>( target, src );
    }


// #################################################################################################
// ApplyTo(): POD types
// #################################################################################################

    /** ********************************************************************************************
     * Writes a cstring to the given AString.
     * @param target The object that \b Apply was invoked on.
     * @param src    The character string to append to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, const char* src )
    {
        int length= (int) strlen( src );              // can't be nullptr
        target.Append<false>( src, length );    // use false, as length check is anyhow down later
        return length;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<const char*> : public std::true_type {};
    #endif

    /** ********************************************************************************************
     * This method converts the provided wide character string (zero-terminated array of
     * wchar_t) and appends it to the \p target. The conversion is done using
     * - <em>wcsnrtombs</em> on glibc platforms (e.g. Linux)
     * - <em>WideCharToMultiByte(CP_UTF8,...)</em> on Windows platform.
     * @param target The object that \b Apply was invoked on.
     * @param src    The wide character string to append to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  ALIB_API int ApplyTo( AString& target, const wchar_t* src);
    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<const wchar_t*> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,  const wchar_t* value )
        {  return  ApplyTo<const wchar_t*>( target,       value );  }
    #endif

    /** ********************************************************************************************
     * Writes the words "true" or "false" to the given AString
     * @param target The object that \b Apply was invoked on.
     * @param b      The boolean to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, bool& b )
    {
        target._( b ? "true" : "false" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<bool&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target,     bool& value )
        {  return  ApplyTo<bool&>( target, value );  }
    #endif

// #################################################################################################
// ApplyTo(): ALib enum types (mostly for debugging)
// Note: Those are considered POD types and therefore NOT to be defined as const
// #################################################################################################

    /** ********************************************************************************************
     * Writes the values of enum class \b Switch
     * @param target  The object that \b Apply was invoked on.
     * @param value   The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::Switch& value )
    {
        target._( value == enums::Switch::On ? "On" : "Off" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::Switch&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::Switch& value )
        {  return  ApplyTo<enums::Switch&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class \b Case
     * @param target  The object that \b Apply was invoked on.
     * @param value   The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::Case& value )
    {
        target._( value == enums::Case::Ignore ? "Ignore" : "Sensitive" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::Case&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::Case& value )
        {  return  ApplyTo<enums::Case&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class \b Alignment
     * @param target The object that \b Apply was invoked on.
     * @param value      The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::Alignment& value )
    {
        target._( value == enums::Alignment::Left   ? "Left" :
                  value == enums::Alignment::Center ? "Center" :
                                                      "Right" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::Alignment&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::Alignment& value )
        {  return  ApplyTo<enums::Alignment&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class \b Inclusion
     * @param target The object that \b Apply was invoked on.
     * @param value      The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::Inclusion& value )
    {
        target._( value == enums::Inclusion::Include ? "Include" : "Exclude" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::Inclusion&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::Inclusion& value )
        {  return  ApplyTo<enums::Inclusion&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class
     * \ref aworx::lib::enums::CurrentData "CurrentData".
     *
     * @param target The object that \b Apply was invoked on.
     * @param value  The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::CurrentData& value )
    {
        target._( value == enums::CurrentData::Keep ? "Keep" : "Clear" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::CurrentData&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::CurrentData& value )
        {  return  ApplyTo<enums::CurrentData&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class \b Safeness
     * @param target The object that \b Apply was invoked on.
     * @param value      The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::Safeness& value )
    {
        target._( value == enums::Safeness::Safe ? "Safe" : "Unsafe" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::Safeness&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::Safeness& value )
        {  return  ApplyTo<enums::Safeness&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class \b Responsibility
     * @param target The object that \b Apply was invoked on.
     * @param value      The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::Responsibility& value )
    {
        target._( value == enums::Responsibility::KeepWithSender ? "KeepWithSender" : "Transfer" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::Responsibility&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::Responsibility& value )
        {  return  ApplyTo<enums::Responsibility&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class \b Timezone
     * @param target The object that \b Apply was invoked on.
     * @param value      The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::Timezone& value )
    {
        target._( value == enums::Timezone::Local ? "Local" : "UTC" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::Timezone&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::Timezone& value )
        {  return  ApplyTo<enums::Timezone&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class \b LockMode
     * @param target The object that \b Apply was invoked on.
     * @param value      The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::LockMode& value )
    {
        target._( value == enums::LockMode::Recursive ? "Recursive" : "SingleLocks" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::LockMode&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::LockMode& value )
        {  return  ApplyTo<enums::LockMode&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class \b Whitespaces
     * @param target The object that \b Apply was invoked on.
     * @param value      The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::Whitespaces& value )
    {
        target._( value == enums::Whitespaces::Trim ? "Trim" : "Keep" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::Whitespaces&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::Whitespaces& value )
        {  return  ApplyTo<enums::Whitespaces&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class \b Create
     * @param target The object that \b Apply was invoked on.
     * @param value      The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::Create& value )
    {
        target._( value == enums::Create::Never ? "Never" : "IfNotExistent" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::Create&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::Create& value )
        {  return  ApplyTo<enums::Create&>( target, value );  }
    #endif

    /** ********************************************************************************************
     * Writes the values of enum class \b Propagation
     * @param target The object that \b Apply was invoked on.
     * @param value      The value to write to \p target.
     * @return The number of characters appended to target.
     **********************************************************************************************/
    template<>  inline   int ApplyTo( AString& target, enums::Propagation& value )
    {
        target._( value == enums::Propagation::None ? "None" : "ToDescendants" );
        return 1;
    }

    #if !defined( IS_DOXYGEN_PARSER )
        template<>  struct       IsApplicable<enums::Propagation&> : public std::true_type {};

        template<>  inline   int   ApplyTo_NC( AString& target, enums::Propagation& value )
        {  return  ApplyTo<enums::Propagation&>( target, value );  }
    #endif

}}} // namespace aworx::lib::strings

#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
#endif // HPP_ALIB_STRINGS_APPLYTO
