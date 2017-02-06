// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

//  set include guard
#ifndef HPP_ALIB_BOXING_FTYPES
#define HPP_ALIB_BOXING_FTYPES 1

#if !defined (HPP_ALIB_BOXING)
    #include "alib/boxing/boxing.hpp"
#endif


#if ALIB_FEAT_BOXING_FTYPES


namespace aworx { namespace lib { namespace boxing { namespace ftypes
{
    /** This is a type alias to \c int64_t. With default implementation of boxing C++ fundamental
     *  types in place, all signed integer types get boxed to this type.  */
    using boxed_int=                   int64_t;

    /** Unsigned version of #boxed_int */
    using boxed_uint=                  uint64_t;

// We are faking all template specializations of namespace boxing for doxygen into namespace
// ftypes to keep documentation of namespace boxing clean!
#if !defined(DOX_PARSER)
}
#endif



// #################################################################################################
// Specializations of struct T_Boxing
// #################################################################################################

#if !defined(DOX_PARSER)

ALIB_BOXING_SPECIALIZE_CB_CUB(bool         , bool               , false , true  );
ALIB_BOXING_SPECIALIZE_CB_CUB(char         , char               , false , true  );
ALIB_BOXING_SPECIALIZE_CB_CUB(wchar_t      , wchar_t            , false , true  );
ALIB_BOXING_SPECIALIZE_CB_CUB(char16_t     , char16_t           , false , true  );
ALIB_BOXING_SPECIALIZE_CB_CUB(char32_t     , char32_t           , false , true  );

ALIB_BOXING_SPECIALIZE_CB_CUB( int8_t      , ftypes::boxed_int  , false , false );
ALIB_BOXING_SPECIALIZE_CB_CUB(uint8_t      , ftypes::boxed_uint , false , false );
ALIB_BOXING_SPECIALIZE_CB_CUB( int16_t     , ftypes::boxed_int  , false , false );
ALIB_BOXING_SPECIALIZE_CB_CUB(uint16_t     , ftypes::boxed_uint , false , false );
ALIB_BOXING_SPECIALIZE_CB_CUB( int32_t     , ftypes::boxed_int  , false , false );
ALIB_BOXING_SPECIALIZE_CB_CUB(uint32_t     , ftypes::boxed_uint , false , false );
ALIB_BOXING_SPECIALIZE_CB_CUB( int64_t     , ftypes::boxed_int  , false , true  );
ALIB_BOXING_SPECIALIZE_CB_CUB(uint64_t     , ftypes::boxed_uint , false , true  );
ALIB_BOXING_SPECIALIZE_CB_CUB( intGap_t    , ftypes::boxed_int  , false , false );
ALIB_BOXING_SPECIALIZE_CB_CUB(uintGap_t    , ftypes::boxed_uint , false , false );


ALIB_BOXING_SPECIALIZE_CB(    float        , double             , false , false );
ALIB_BOXING_SPECIALIZE(       double       , double             , false , true  );

ALIB_BOXING_SPECIALIZE_CB(    char    *    , char               , true  , false);
ALIB_BOXING_SPECIALIZE_CB(    wchar_t *    , wchar_t            , true  , false);
ALIB_BOXING_SPECIALIZE_CB(    char16_t*    , char16_t           , true  , false);
ALIB_BOXING_SPECIALIZE_CB(    char32_t*    , char32_t           , true  , false);


// #################################################################################################
// Definitions of T_Boxing::Boxing
// #################################################################################################
inline void  T_Boxing<bool     >::Boxing( Box& box, const bool      & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing<char     >::Boxing( Box& box, const char      & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing<wchar_t  >::Boxing( Box& box, const wchar_t   & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing<char16_t >::Boxing( Box& box, const char16_t  & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing<char32_t >::Boxing( Box& box, const char32_t  & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }

inline void  T_Boxing< int8_t  >::Boxing( Box& box, const  int8_t   & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing<uint8_t  >::Boxing( Box& box, const uint8_t   & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing< int16_t >::Boxing( Box& box, const int16_t   & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing<uint16_t >::Boxing( Box& box, const uint16_t  & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing< int32_t >::Boxing( Box& box, const  int32_t  & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing<uint32_t >::Boxing( Box& box, const uint32_t  & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing< int64_t >::Boxing( Box& box, const  int64_t  & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing<uint64_t >::Boxing( Box& box, const uint64_t  & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing< intGap_t>::Boxing( Box& box, const  intGap_t & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }
inline void  T_Boxing<uintGap_t>::Boxing( Box& box, const uintGap_t & value )  { box.data.Value= static_cast<boxvalue>(value);  box.data.Length= 0;  }

#if !defined(DOX_PARSER)
    ALIB_WARNINGS_START_TMP
#endif
inline void  T_Boxing<float>::Boxing( Box& box, const float& value )
{
    DefaultBoxing( box, static_cast<double>(value) );
}

inline void  T_Boxing<char*>::Boxing( Box& box, char* const& value )
{
    if( sizeof(value) < sizeof(boxvalue) )
        box.data.Value= 0;
    memcpy( &box.data.Value, &value, sizeof(value) );
    box.data.Length= value == nullptr || *value == '\0' ? 0 : -1;
}

inline void  T_Boxing<wchar_t*>::Boxing( Box& box,  wchar_t* const& value )
{
    if( sizeof(value) < sizeof(boxvalue) )
        box.data.Value= 0;
    memcpy( &box.data.Value, &value, sizeof(value) );
    box.data.Length= value == nullptr || *value == '\0' ? 0 : -1;
}

inline void  T_Boxing<char16_t*>::Boxing( Box& box, char16_t* const& value )
{
    if( sizeof(value) < sizeof(boxvalue) )
        box.data.Value= 0;
    memcpy( &box.data.Value, &value, sizeof(value) );
    box.data.Length= value == nullptr || *value == '\0' ? 0 : -1;
}

inline void  T_Boxing<char32_t*>::Boxing( Box& box, char32_t* const& value )
{
    if( sizeof(value) < sizeof(boxvalue) )
        box.data.Value= 0;
    memcpy( &box.data.Value, &value, sizeof(value) );
    box.data.Length= value == nullptr || *value == '\0' ? 0 : -1;
}

#if !defined(DOX_PARSER)
ALIB_WARNINGS_RESTORE
#endif


// #################################################################################################
// Definitions of T_Boxing::Unboxing
// #################################################################################################
inline bool       T_Boxing<bool    >::Unboxing( const Box& box )  { return box.data.Value != 0;                     }
inline char       T_Boxing<char    >::Unboxing( const Box& box )  { return static_cast< char   >( box.data.Value ); }
inline wchar_t    T_Boxing<wchar_t >::Unboxing( const Box& box )  { return static_cast<wchar_t >( box.data.Value ); }
inline char16_t   T_Boxing<char16_t>::Unboxing( const Box& box )  { return static_cast<char16_t>( box.data.Value ); }
inline char32_t   T_Boxing<char32_t>::Unboxing( const Box& box )  { return static_cast<char32_t>( box.data.Value ); }

inline  int64_t   T_Boxing< int64_t>::Unboxing( const Box& box )  { return static_cast< int64_t>( box.data.Value ); }
inline uint64_t   T_Boxing<uint64_t>::Unboxing( const Box& box )  { return static_cast<uint64_t>( box.data.Value ); }

#endif

// #################################################################################################
// Specializations of T_SGetArraySize<> for character types
// #################################################################################################
/**
 * Specialization of template function for type \c char, that subtracts \c 1 from the provided array
 * extend to denote the length of a character string.
 *
 * @param arrayExtent  The array extent as deducted using TMP in constructor of class
 *                     \ref aworx::lib::boxing::Box "Box".
 * @returns The length as given by \p arrayExtent but reduced by \c 1.
 */
template<>  inline constexpr  integer    T_SetArraySize<char>   ( integer arrayExtent )
{
    return arrayExtent -1;
}

/**
 * Specialization of template function for type \c wchar_t, that subtracts \c 1 from the provided
 * array extend to denote the length of a character string.
 *
 * @param arrayExtent  The array extent as deducted using TMP in constructor of class
 *                     \ref aworx::lib::boxing::Box "Box".
 * @returns The length as given by \p arrayExtent but reduced by \c 1.
 */
template<>  inline constexpr  integer    T_SetArraySize<wchar_t>( integer arrayExtent )
{
    return arrayExtent -1;
}

/**
 * Specialization of template function for type \c char16_t, that subtracts \c 1 from the provided
 * array extend to denote the length of a character string.
 *
 * @param arrayExtent  The array extent as deducted using TMP in constructor of class
 *                     \ref aworx::lib::boxing::Box "Box".
 * @returns The length as given by \p arrayExtent but reduced by \c 1.
 */
template<>  inline constexpr  integer    T_SetArraySize<char16_t>( integer arrayExtent )
{
    return arrayExtent -1;
}

/**
 * Specialization of template function for type \c char32_t, that subtracts \c 1 from the provided
 * array extend to denote the length of a character string.
 *
 * @param arrayExtent  The array extent as deducted using TMP in constructor of class
 *                     \ref aworx::lib::boxing::Box "Box".
 * @returns The length as given by \p arrayExtent but reduced by \c 1.
 */
template<>  inline constexpr  integer    T_SetArraySize<char32_t>( integer arrayExtent )
{
    return arrayExtent -1;
}



// #################################################################################################
// Implementation of standard Boxer interfaces, IEquals, IIsNull(), IIsEmpty
// #################################################################################################

// We are faking all template specializations of namespace boxing for doxygen into namespace
// ftypes to keep documentation of namespace boxing clean!
#if !defined(DOX_PARSER)
namespace ftypes
{
#endif


/** Implements 'Equals' - interface for boxed \c double values. */
class IEquals_Tdouble : public IEquals, public Singleton<IEquals_Tdouble>
{
    /**
     * Checks if \p box with boxed type \c double equals \p other. This is done by first comparing
     * the exact values. If they differ, the difference is calculated and compared to
     * <c> 2.0f * std::numeric_limits<float>::epsilon()</c>. If smaller, \c true is returned.
     *
     * @param box   The box that the interface was invoked on.
     * @param other The boxed value to compare us to.
     * @return \c true if \p comp equals \p box, \c false otherwise.
     */
    ALIB_API
    virtual bool Invoke( const Box& box, const Box& other );
};


/** Implements 'Equals' - interface for boxed \c char[] values. */
class IEquals_TcharArr : public IEquals, public Singleton<IEquals_TcharArr>
{
    /**
     * Checks if \p box with boxed type \c char[] equals \p other.
     *
     * @param box   The box that the interface was invoked on.
     * @param other The boxed value to compare us to.
     * @return \c true if \p comp equals \p box, \c false otherwise.
     */
    ALIB_API
    virtual bool Invoke( const Box& box, const Box& other );
};

/** Implements 'Equals' - interface for boxed \c wchar_t[] values. */
class IEquals_Twchar_tArr : public IEquals, public Singleton<IEquals_Twchar_tArr>
{
    /**
     * Checks if \p box with boxed type \c wchar_t[] equals \p other.
     *
     * @param box   The box that the interface was invoked on.
     * @param other The boxed value to compare us to.
     * @return \c true if \p comp equals \p box, \c false otherwise.
     */
    ALIB_API
    virtual bool Invoke( const Box& box, const Box& other );
};

/** Implements 'Equals' - interface for boxed \c char16_t[] values. */
class IEquals_Tchar16_tArr : public IEquals, public Singleton<IEquals_Tchar16_tArr>
{
    /**
     * Checks if \p box with boxed type \c char16_t[] equals \p other.
     *
     * @param box   The box that the interface was invoked on.
     * @param other The boxed value to compare us to.
     * @return \c true if \p comp equals \p box, \c false otherwise.
     */
    ALIB_API
    virtual bool Invoke( const Box& box, const Box& other );
};

/** Implements 'Equals' - interface for boxed \c char32_t[] values. */
class IEquals_Tchar32_tArr : public IEquals, public Singleton<IEquals_Tchar32_tArr>
{
    /**
     * Checks if \p box with boxed type \c char32_t[] equals \p other.
     *
     * @param box   The box that the interface was invoked on.
     * @param other The boxed value to compare us to.
     * @return \c true if \p comp equals \p box, \c false otherwise.
     */
    ALIB_API
    virtual bool Invoke( const Box& box, const Box& other );
};




// #################################################################################################
// Initialization
// #################################################################################################
void  Init(); // forward declaration (needed if very strict warnings are enabled in clang)
/**
 * Initializes the default fundamental type handling of <b>ALib %Boxing</b>.
 * Defines interface implementation classes as interfaces of certain fundamental types.
 */
inline void Init()
{
    DefineInterface<double         , false, IEquals_Tdouble     >();
    DefineInterface<char           , true , IEquals_TcharArr    >();
    DefineInterface<wchar_t        , true , IEquals_Twchar_tArr >();
    DefineInterface<char16_t       , true , IEquals_Tchar16_tArr>();
    DefineInterface<char32_t       , true , IEquals_Tchar32_tArr>();

    DefineInterface<boxed_int      , false, IIsNull_false       >();
    DefineInterface<boxed_uint     , false, IIsNull_false       >();
    DefineInterface<double         , false, IIsNull_false       >();

}

}}} // namespace lib::boxing::ftypes

/** Type alias name in namespace #aworx. */
using     boxed_int   =   aworx::lib::boxing::ftypes::boxed_int;

/** Type alias name in namespace #aworx. */
using     boxed_uint  =   aworx::lib::boxing::ftypes::boxed_uint;
} // namespace aworx

#endif // ALIB_FEAT_BOXING_FTYPES
#endif // HPP_ALIB_BOXING_FTYPES
