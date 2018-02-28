// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

//  set include guard
#ifndef HPP_ALIB_STRINGS_BOXING
#define HPP_ALIB_STRINGS_BOXING 1

// to preserve the right order, we are not includable directly from outside.
#if !defined(ALIB_PROPER_INCLUSION)  || !defined(HPP_ALIB_BOXING_LIB)
    #error "include 'alib/alib.hpp' instead of this header"
#endif

#if !ALIB_FEAT_BOXING_FTYPES
    static_assert(0, "This implementation of boxing ALib strings may be used only if default "
                     "boxing of fundamental types is activated."
#endif


namespace aworx { namespace lib { namespace strings {

// #################################################################################################
// forward declarations
// #################################################################################################

class Substring;
namespace util {  template< typename... TAssociatedTypes > class StringTable; }

}} // namespace aworx [::lib::strings::util]
using     Substring      =   aworx::lib::strings::Substring;

namespace lib { namespace strings {


// #################################################################################################
// Specializations of T_Boxing<> for String types
// #################################################################################################

// We are faking all template specializations of namespace boxing for doxygen into namespace
// strings::boxing to keep the documentation of namespace boxing clean!
#if !defined(DOX_PARSER)
} // namespace strings
#endif
namespace boxing {

ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING


ALIB_BOXING_SPECIALIZE_CB_CUB( String,  char, true,     true )
inline void   T_Boxing<String     >::Boxing( Box& box,  const String& value )
{
     box.data.Value=  (boxvalue) value.Buffer();
     box.data.Length=            value.Length();
}

inline String T_Boxing<String>::Unboxing( const Box& box )
{
    return  String( (const char*) box.data.Value,
                     box.data.Length >= 0 ? static_cast<integer>( box.data.Length )
                                          : static_cast<integer>( strlen( (const char*) box.data.Value) ) );
}

ALIB_BOXING_SPECIALIZE_CB( Substring, char, true,   false  )
inline void   T_Boxing<Substring  >::Boxing( Box& box,  const Substring& value )
{
    T_Boxing<String>::Boxing( box, (String&) value );
}

ALIB_BOXING_SPECIALIZE_CB( TString, char, true,     false )
inline void   T_Boxing<TString    >::Boxing( Box& box,  const TString& value )
{
    T_Boxing<String>::Boxing( box, (String&) value );
}

ALIB_BOXING_SPECIALIZE_CB( AString, char, true,     false )
inline void   T_Boxing<AString    >::Boxing( Box& box,  const AString& value )
{
    T_Boxing<String>::Boxing( box, (String&) value );
}




/**
 * Templated specialization of template struct \ref aworx::lib::boxing::T_Boxing "T_Boxing"
 * for class \ref aworx::lib::strings::PreallocatedString "PreallocatedString" with different
 * template \p TCapacity.<br>
 * The types are boxed as character arrays, as any string-type should be.
 */
template<integer TCapacity>
struct T_Boxing<aworx::lib::strings::PreallocatedString<TCapacity>>    : std::true_type
{
    /** Boxed type \c char[]. */
    using Type= char;

    /**
     * \c char array.
     * @return Constant \c false.
     */

    static constexpr bool IsArray()                                { return true; }

    /**
     * Not unboxable. \b %String (and other 3rd party string types) are unboxable instead.
     * @return Constant \c false.
     */
    static constexpr bool IsUnboxable()                            { return false; }

    /**
     * We have custom boxing.
     * @return Constant \c true.
     */
    static constexpr bool HasCustomBoxing()                        { return true; }

    /**
     * No custom unboxing.
     * @return Constant \c false.
     */
    static constexpr bool HasCustomUnboxing()                      { return false; }

    /**
     * This method is never called, because \b HasCustomBoxing returns constant \c false.
     * @param box   The box to store \p value in.
     * @param value The value to box.
     */
    static void           Boxing(Box& box,  const strings::PreallocatedString<TCapacity> & value)
    {
        T_Boxing<String>::Boxing( box, (String&) value );
    }

    /** This method is never called, because \b %HasCustomUnboxing returns constant \c false.
     */
    static void          Unboxing(const Box& ) {};
};

/**
 * Templated specialization of template struct \ref aworx::lib::boxing::T_Boxing "T_Boxing"
 * for class \ref aworx::lib::strings::StringLiteral "StringLiteral" with different
 * template \p TLength.<br>
 * The types are boxed as character arrays, as any string-type should be.
 */
template<size_t TLength>
struct T_Boxing<strings::StringLiteral<TLength>>    : std::true_type
{
    /** Boxed type \c char[]. */
    using Type= char;
    /**
     * \c char array.
     * @return Constant \c true.
     */
    static constexpr bool IsArray()                                { return true;  }

    /**
     * Not unboxable. \b %String (and other 3rd party string types) are unboxable instead.
     * @return Constant \c false.
     */
    static constexpr bool IsUnboxable()                            { return false; }

    /**
     * We have custom boxing.
     * @return Constant \c true.
     */
    static constexpr bool HasCustomBoxing()                        { return true;  }

    /**
     * No custom unboxing.
     * @return Constant \c false.
     */
    static constexpr bool HasCustomUnboxing()                      { return false; }

    /**
     * This method is never called, because #HasCustomBoxing returns constant \c false.
     * @param box   The box to store \p value in.
     * @param value The value to box.
     */
    static void           Boxing(Box& box,  const strings::StringLiteral<TLength> & value)
    {
        box.data.Value=  (boxvalue) value.Buffer();
        box.data.Length=            TLength;
    }

    /**
     * This method is never called, because #HasCustomUnboxing returns constant \c false.
     * @param box   The box to unbox.
     */
    static void           Unboxing(const Box& box);
};


ALIB_WARNINGS_RESTORE


// We are faking all template specializations of namespace boxing for doxygen into namespace
// strings::boxing to keep the documentation of namespace boxing clean!
#if !defined(DOX_PARSER)
} // namespace boxing
namespace strings { namespace boxing {
#endif


// #############################################################################################
// Implementation of default boxing interfaces
// #############################################################################################


/** Implements 'IsLess' - interface for boxed \c char arrays. */
class IIsLess_Tchar_arr : public IIsLess, public Singleton<IIsLess_Tchar_arr>
{
    /**
     * Returns the result of the comparison for unsigned integer values.
     *
     * @param lhs   The box that the interface was invoked on.
     * @param rhs   The boxed value to compare us to.
     * @return \c true if \p lhs is smaller than \p rhs, \c false otherwise.
     */
    ALIB_API
    virtual bool Invoke( const Box& lhs, const Box& rhs );
};


// #############################################################################################
// Boxer Interface class "IApply"
// #############################################################################################

/**
 * This interface class exposes interface method \c Invoke which writes the content of the
 * box to the given \b %AString object.
 * This base interface class, implements a default behaviour for all boxable types which are not
 * equipped with a specific implementation of this class and hence, a singleton hereof is
 * attached to the <b>%%ALib %Boxing</b> using
 * \ref aworx::lib::boxing::Boxer::DefineDefaultInterface "Boxer::DefineDefaultInterface"
 *
 * Variant
 * \ref aworx::lib::strings::boxing::IApply_TApplicable "IApply_TApplicable"
 * can be attached without changes to any Boxer of custom types that implement the TMP interface
 * introduced by \ref aworx::lib::strings::AString::Apply "AString::Apply".
 */
class IApply : public Interface
{
    public:
    /**
     * Declares a static singleton used for the default interface registration and returns that.
     * \note We do not inherit template class Singleton here, because each of our descendants
     *       needs to do this as well, which would lead to some confusion.
     * @return A singleton instance of myself.
     */
    static IApply* GetDefaultSingleton()
    {
        static IApply me;
        return &me;
    }

    /** Constructor providing our runtime type to the parent. */
    IApply() : Interface( typeid(IApply) ) {}

    /**
     * The interface method. This default implementation writes out the raw value of the box
     * in hexadecimal format. For standard types, such raw value reflect the memory address of
     * the object boxed.<br>
     * In debug-compilations, in addition the type name of the boxed value is written.
     * @param box   The box that the interface was invoked on.
     * @param target The target \b %AString.
     */
    ALIB_API
    virtual void Invoke( const Box& box, AString& target );
};


/**
 * Templated implementation of #IApply for boxable types which are \e 'applicable'
 * to AStrings. Applicable are all types that have a corresponding specialization of template struct
 * \ref aworx::lib::strings::T_Apply. Consult the \b %ALib String module documentation for more
 * information.
 *
 * Once a type is made applicable, then on the boxing side of things, this interface class
 * with template parameter \p TApplicable set to the type in question, may be attached to the
 * boxed type.
 */
template<typename TApplicable>
class IApply_TApplicable : public IApply, public Singleton<IApply_TApplicable<TApplicable>>
{
    public:
    /**
     * The interface method, writing the applicable type.
     * @param box    The box that the interface was invoked on.
     * @param target The target \b %AString.
     */
    virtual inline void Invoke( const Box& box, AString& target )                           override
    {
        target._<false>( box.Unbox<TApplicable>() );
    }
};

/** Implementation of #IApply for boxable types \c char[] and \c char*.  */
class IApply_TcharArr : public IApply, public Singleton<IApply_TcharArr>
{
    public:
    /**
     * The interface method, writing the character string.
     * @param box    The box that the interface was invoked on.
     * @param target The target \b %AString.
     */
    virtual inline void Invoke( const Box& box, AString& target )                           override
    {
             if ( box.Length() > 0 ) target.Append(reinterpret_cast<char*>(box.UnboxRaw()),
                                                    box.Length()                            );
        else if ( box.Length() < 0 ) target._<false>( reinterpret_cast<char*>(box.UnboxRaw()) );

    }
};

/** Implementation of #IApply for boxable types \c wchar_t[] and \c wchar_t*.  */
class IApply_Twchar_tArr : public IApply, public Singleton<IApply_Twchar_tArr>
{
    public:
    /**
     * The interface method, writing the character string.
     * @param box    The box that the interface was invoked on.
     * @param target The target \b %AString.
     */
    virtual inline void Invoke( const Box& box, AString& target)                            override
    {
             if ( box.Length() > 0 ) target.Append(reinterpret_cast<wchar_t*>(box.UnboxRaw()),
                                                    box.Length()                                   );
        else if ( box.Length() < 0 ) target._<false>(     reinterpret_cast<wchar_t*>(box.UnboxRaw()) );
    }
};

/** Implementation of #IApply for boxable types \c char16_t[] and \c char16_t*.  */
class IApply_Tchar16_tArr : public IApply, public Singleton<IApply_Tchar16_tArr>
{
    public:
    /**
     * The interface method, writing the character string.
     * @param box    The box that the interface was invoked on.
     * @param target The target \b %AString.
     */
    virtual inline void Invoke( const Box& box, AString& target)                            override
    {
             if ( box.Length() > 0 ) target.Append(reinterpret_cast<char16_t*>(box.UnboxRaw()),
                                                    box.Length());
        else if ( box.Length() < 0 ) target._<false>( reinterpret_cast<char16_t*>(box.UnboxRaw()) );
    }
};

/** Implementation of #IApply for boxable types \c char32_t[] and \c char32_t*.  */
class IApply_Tchar32_tArr : public IApply, public Singleton<IApply_Tchar32_tArr>
{
    public:
    /**
     * The interface method, writing the character string.
     * @param box    The box that the interface was invoked on.
     * @param target The target \b %AString.
     */
    virtual inline void Invoke( const Box& box, AString& target)                            override
    {
             if ( box.Length() > 0 ) target.Append(reinterpret_cast<char32_t*>(box.UnboxRaw()),
                                                    box.Length()                                 );
        else if ( box.Length() < 0 ) target._<false>( reinterpret_cast<char32_t*>(box.UnboxRaw())  );
    }
};

/**
 * Implementation template for boxing interface #IApply for boxable template type
 * \b %BoxedAs\<TApplicable\>.
 * This interface can be used for any type \p TApplicable that has a specialization of
 * \ref aworx::lib::strings::T_Apply "T_Apply" defined and that are are boxed using wrapper class
 * \ref aworx::lib::boxing::BoxedAs "BoxedAs".
 *
 * \see Documentation of <b>%ALib %Boxing</b>, chapter
 *      \ref alib_namespace_boxing_types_boxedas "4.5 Boxing Types As They Are".
 */
template<typename TApplicable>
class IApply_BoxedAs_TApplicable : public IApply, public Singleton<IApply_BoxedAs_TApplicable<TApplicable>>
{
    public:
    /**
     * The interface method, writing the AString wrapped in \b %BoxedAs\<AString\>.
     * @param box    The box that the interface was invoked on.
     * @param target The target \b %BoxedAs\<AString\> object.
     */
    virtual inline void Invoke( const Box& box, AString& target)                            override
    {
        target._<false>( box.Unbox<BoxedAs<TApplicable>>().Get() );
    }
};


// This macro is documented in header "boxing.hpp" for technical reasons (doxygen)

#define ALIB_BOXING_DEFINE_IAPPLY_FOR_APPLICABLE_TYPE(TApplicable)                                  \
aworx::lib::boxing::DefineInterface<TApplicable ,                                                   \
                                    false,                                                          \
                                    aworx::lib::strings::boxing::IApply_TApplicable<TApplicable>>();\


// #############################################################################################
// Boxer Interface class "IFormat"
// #############################################################################################

/**
 * This interface class exposes interface method \c Invoke which writes the content of the
 * box to the given \b %AString object in accordance with \c formatSpec.
 */
class IFormat: public Interface
{
    public:
    /** Constructor providing our runtime type to the parent. */
    IFormat() : Interface( typeid(IFormat) ) {}

    /**
     * Writes the content of \p box to the given \b %AString object \p target in accordance
     * with type-specific format specification \p formatSpec.
     *
     * @param box        The box that the interface was invoked on.
     * @param formatSpec The specification of the format (type specific)
     * @param target     The AString object receiving the formatted string.
     */
    virtual void Invoke(  const Box& box, const String& formatSpec, AString& target )           = 0;
};


// #################################################################################################
// T_Apply<Box>
// #################################################################################################
} // namespace boxing

// We are faking all template specializations of namespace strings for doxygen into namespace
// strings::applyto to keep the documentation of namespace string clean!
#if defined(DOX_PARSER)
namespace applyto {
#endif

    /** Specialization of template struct \ref T_Apply for type \c lib::boxing::Box.   */
    template<>  struct   T_Apply<lib::boxing::Box> : public std::true_type
    {
        /** ****************************************************************************************
         * Writes the given boxed object. This is done by invoking box interface
         * \ref aworx::lib::strings::boxing::IApply "IApply" on box \p value.
         *
         * @param target  The object that \b Apply was invoked on.
         * @param value   The value to write to \p target.
         * @return The number of characters appended to target.
         ******************************************************************************************/
        static inline integer Apply( AString& target, const lib::boxing::Box& value )
        {
            value.Invoke<aworx::lib::strings::boxing::IApply>( target );
            return 0;
        }
        //! @endcond
    };

#if defined(DOX_PARSER)
}
#endif


}} // [aworx::lib::strings]




/** Type alias name in namespace #aworx. */
using     IApply   =   aworx::lib::strings::boxing::IApply;

} // namespace [aworx]

#endif // HPP_ALIB_STRINGS_BOXING
