// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Essential ALib types needed by every module
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

#ifndef HPP_ALIB_LANG_ENUM_ENUM
#define HPP_ALIB_LANG_ENUM_ENUM 1


#if !defined (_GLIBCXX_TYPEINDEX) && !defined(_TYPEINDEX_)
    #include <typeindex>
#endif



namespace aworx { namespace lib { namespace lang {

/** ************************************************************************************************
 * The class is useful to store and pass around enum values of arbitrary C++ scoped enum types in
 * a type-safe way.
 * It is implemented to ease the use of C++ 11 scoped enums in situations where programmers
 * otherwise tend to "fall back" to non-scoped (non type-safe enum types). This is the case, when
 * enum elements of different types need to be processed.
 *
 * In the constructor,  enum elements of arbitrary type are accepted.
 * The enum element is \ref aworx::lib::boxing "boxed" and thus runtime type information is added.
 * Having the "original" element stored in a box, has the following advantages:
 * - The box is useful to check the encapsulated enum type at runtime
 *   using \alib{boxing,Box::IsType}.
 * - The original element can be unboxed using #Get in a type-safe way. (This method is a shortcut
 *   to  \alib{boxing,Box::Unbox,Box::Unbox<TEnum>()}
 * - The underlying integer type value of the enum element can be received easily.
 *
 * \note
 *   The implementation of this class using \ref aworx::lib::boxing "ALib Boxing" introduces a
 *   small memory overhead (usually 8 bytes per instance on 64-bit system), in respect to a
 *   possible alternative "direct" implementation. This is due to the fact that boxing allows
 *   one dimensional array types to be boxed as well as scalar types - which is never the case
 *   with this class.
 *
 * \note
 *   The advantage of doing so, is that the internal box element (which is exposed as a public
 *   field) may be used as if the enum element was just boxed, instead of being emplaced in this
 *   class. This way, custom boxing interfaces that exist for enum types, may be used with instances
 *   of this class.
 *
 * \note
 *   For example, this class already specializes \alib{strings,T_Apply} which appends a string
 *   representation of the enum element to an \b %AString. Internally, built-in boxing interface
 *   \alib{strings::boxing,IApply} is used.<br>
 *   This means, that if this interface is set for the boxed C++ 11 enum type already, then
 *   objects of this type can be applied without further (setup) effort of the user code.
 **************************************************************************************************/
struct Enum
{
    /**
     * The enumeration element as a \ref aworx::lib::boxing "boxed" value. Although the member
     * name starts with a lower case letter, the value is still public (Bauhaus style).
     * However, usually the element does not need to be accessed directly.
     */
    const Box      box;

    /** ********************************************************************************************
     * Deleted default constructor.
     **********************************************************************************************/
    Enum()= delete;

    /** ********************************************************************************************
     * Implicit constructor which accepts arbitrary elements of scoped or non-scoped enum types.
     *
     * @param  element     The external (user specific) enumeration element.
     * @tparam TEnum       The external (user specific) enumeration type.
     * @tparam TEnableIf   Selects this constructor only for enum types.
     **********************************************************************************************/
    template<typename  TEnum,
             typename  TEnableIf  = typename std::enable_if<std::is_enum<TEnum>::value>::type >
    constexpr Enum( TEnum element )
    : box( element )                        {}

    /** ********************************************************************************************
     * This is a shortcut to \alib{boxing,Box::Unbox,Box::Unbox<TEnum>()} to retrieve the
     * original enum element in a type safe way.
     *
     * Prior to invoking this, the boxed type can be checked with #IsType. If the wrong type
     * is tried to be received, an \alib assertion is raised.
     *
     * @tparam TEnum       The external (user specific) enumeration type.
     * @tparam TEnableIf   Selects this method only for enum types.
     * @return The underlying integer value of the encapsulated enum element.
     **********************************************************************************************/
    template<typename  TEnum,
             typename  TEnableIf  = typename std::enable_if<std::is_enum<TEnum>::value>::type >
    TEnum   Get()                    const  { return box.Unbox<TEnum>();  }

    /** ********************************************************************************************
     * Returns the underlying integer value of the original enum element.
     *
     * \see Namespace function  \alib{lang,EnumValue}.
     *
     * @return The underlying integer value.
     **********************************************************************************************/
    inline
    int  Value()                     const  { return static_cast<int>( box.UnboxRaw() );  }

    /** ********************************************************************************************
     * Checks if the this instance has an enum element of type \p TEnum stored.
     *
     * @tparam TEnum       The external (user specific) enumeration type.
     * @tparam TEnableIf   Selects this method only for enum types.
     * @return \c true if the encapsulated enum type of type \p TEnum, otherwise \c false.
     **********************************************************************************************/
    template<typename  TEnum,
             typename  TEnableIf  = typename std::enable_if<std::is_enum<TEnum>::value>::type >
    inline
    bool IsType()                     const { return box.IsType<TEnum>(); }

    /** ********************************************************************************************
     * Checks if the given other object encapsulates the same enumeration type.
     *
     * @param lhs The right hand side argument of the comparison.
     * @return \c true if the encapsulated enum type of this object is the same as the one
     *            encapsulated in \p lhs, otherwise \c false.
     **********************************************************************************************/
    inline
    bool IsSameType(Enum const& lhs) const
    {
        return box.GetTypeInfo<0>() == lhs.box.GetTypeInfo<0>();
    }

    /** ********************************************************************************************
     * Comparison operator.
     *
     * @param lhs The right hand side argument of the comparison.
     * @return \c true if this object equals \p lhs, \c false otherwise.
     **********************************************************************************************/
    inline
    bool operator==(Enum const& lhs)  const { return box ==  lhs.box;  }

    /** ********************************************************************************************
     * Comparison operator.
     *
     * @param lhs The right hand side argument of the comparison.
     * @return \c true if this object does not equal \p lhs, \c false otherwise.
     **********************************************************************************************/
    inline
    bool operator!=(Enum const& lhs)  const { return box !=  lhs.box;  }

    /** ********************************************************************************************
     * Comparison operator.
     *
     * @param lhs The right hand side argument of the comparison.
     * @return \c true if this object equals \p lhs, \c false otherwise.
     **********************************************************************************************/
    template<typename  TEnum,
             typename  TEnableIf  = typename std::enable_if<std::is_enum<TEnum>::value>::type >
    inline
    bool operator==(TEnum lhs)       const  { return    Value() == EnumValue( lhs )
                                                     && box.GetTypeInfo<0>() == typeid( TEnum ); }

    /** ********************************************************************************************
     * Comparison operator.
     *
     * @param lhs The right hand side argument of the comparison.
     * @return \c true if this object does not equal \p lhs, \c false otherwise.
     **********************************************************************************************/
    template<typename  TEnum,
             typename  TEnableIf  = typename std::enable_if<std::is_enum<TEnum>::value>::type >
    inline
    bool operator!=(TEnum lhs)       const  { return    Value() != EnumValue( lhs )
                                                     || box.GetTypeInfo<0>() != typeid( TEnum );  }


    /** ********************************************************************************************
     * Comparison operator. The sort order is primarily determined by the enum types that
     * are boxed. If those are the same, then the underlying integer value of the enum elements
     * is compared.
     *
     * This leads to a nested sort order, with the type information being the outer order and
     * the integer value of the enum being the inner one.
     *
     * \note
     *   It is a matter of the compiler how the outer sort of types is performed and thus this
     *   can not be determined by the user code.
     *
     *
     * @param lhs The right hand side argument of the comparison.
     * @return If the encapsulated type of this instance is the same as that of \p lhs, this
     *         methods \c true if #Value() of this object is smaller than the one of \p lhs and
     *         otherwise \c false. If the types are not the same, than the result is dependent
     *         on the tool chain used for compiling \alib.
     **********************************************************************************************/
    inline
    bool operator< (Enum const& lhs)  const
    {
        return      (    std::type_index(    box.GetTypeInfo<0>() )
                       < std::type_index(lhs.box.GetTypeInfo<0>() )          )
                ||   (    box.GetTypeInfo<0>() == lhs.box.GetTypeInfo<0>()
                       && Value() <  lhs.Value()                                         );
    }

};
}} // namespace aworx[::lib::lang]

/** Type alias name in namespace #aworx. */
using     Enum=              aworx::lib::lang::Enum;

} // namespace [aworx]


// #################################################################################################
// T_APPLY<Enum>
// #################################################################################################

#if ALIB_MODULE_STRINGS

namespace aworx { namespace lib { namespace strings {
// We are faking specializations of T_Apply for doxygen into namespace aworx::lib::strings::applyto
#if defined(DOX_PARSER)
    namespace applyto {
#endif

/**
 * Specialization of template struct \alib{strings,T_Apply} for type
 * \alib{lang,Enum}.
 */
template<> struct       T_Apply<Enum> : public std::true_type
{
    /**
     * If the enum type encapsulated in \p src has boxing interface \alib{strings::boxing,IApply}
     * defined, then this interface is invoked.
     *
     * If the interface is not available, in debug compilations, the output is
     *
     *          typename(<int value>)
     *
     * where \e typename is the name of the type that was encapsulated on construction of \p source.
     *
     * In release compilations it is:
     *
     *          Enum(<int value>)
     * because printable run-time type information is not available then.
     *
     * @param target The object that \b Apply was invoked on.
     * @param src    The value to write.
     * @return Constant \c 1.
     */
    static integer Apply( AString& target, const aworx::lib::lang::Enum& src )
    {
        if( src.box.HasInterface<aworx::lib::strings::boxing::IApply>() )
            src.box.Invoke<aworx::lib::strings::boxing::IApply>( target );
        else
            target << ALIB_REL_DBG( "Enum", src.box.GetTypeInfo() )
                   << '(' << src.Value() << ')';

        return 1;
    }
};


#if defined(DOX_PARSER)
} // namespace aworx::lib::strings[::applyto]
#endif

}}} // namespace [aworx::lib::strings]
#endif // ALIB_MODULE_STRINGS


#endif // HPP_ALIB_LANG_ENUM_ENUM
