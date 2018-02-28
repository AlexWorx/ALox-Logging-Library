// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// Include guard
#ifndef HPP_ALIB_STRINGS_STRING
#define HPP_ALIB_STRINGS_STRING 1

// to preserve the right order, we are not includable directly from outside.
#if !defined(ALIB_PROPER_INCLUSION)
    #error "include 'alib/alib.hpp' instead of this header"
#endif

// #################################################################################################
// includes
// #################################################################################################

// conditional expression is constant for using our constant template parameters to select
// checking vs. non-checking method versions
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4127 )
#endif

// #################################################################################################
// Macros
// #################################################################################################

/**
 * @addtogroup GrpALibCompilerSymbols
 * @{ \def  ALIB_DEBUG_STRINGS_ON
 *  This compiler symbol enables additional debug code within class AString. When provided,
 *  it defines \ref ALIB_DEBUG_STRINGS to \c true. This is useful when extending or specifically debugging
 *  class AString.
 * @}
 *
 * @addtogroup GrpALibCompilerSymbols
 * @{ \def  ALIB_DEBUG_STRINGS_OFF
 *  Disables certain debug code within class AString. See \ref ALIB_DEBUG_STRINGS_ON.
 *  This symbol represents the default behavior and is provided for completeness.
 * @}
 *
 * @addtogroup GrpALibCodeSelectorSymbols
 * @{ \def  ALIB_DEBUG_STRINGS
 *  Selects extra debug code within class AString. Gets defined by compiler symbol
 *  \ref ALIB_DEBUG_STRINGS_ON.
 * @}
 */

#if defined(DOX_PARSER)
    #define     ALIB_DEBUG_STRINGS
    #define     ALIB_DEBUG_STRINGS_ON
    #define     ALIB_DEBUG_STRINGS_OFF
#else
    #if defined(ALIB_DEBUG_STRINGS_OFF) && defined(ALIB_DEBUG_STRINGS_ON)
        #error "ALIB_DEBUG_STRINGS_OFF / ALIB_DEBUG_STRINGS_ON are both set"
    #endif

    #if defined( ALIB_DEBUG_STRINGS_ON )
        #define    ALIB_DEBUG_STRINGS 1
    #else
        #define    ALIB_DEBUG_STRINGS 0
    #endif
#endif //DOX_PARSER


/**
 * @addtogroup GrpALibStringsMacros
 * @{ \def  ALIB_STRING_DBG_CHK
 * Simple macro that just invokes method _dbgCheck(), which is defined for classes
 * \ref aworx::lib::strings::String   "String",
 * \ref aworx::lib::strings::TString  "TString" and
 * \ref aworx::lib::strings::AString "AString".
 * It is active only when compiler symbol \ref ALIB_DEBUG_STRINGS is \c true.
 * The macro is placed in almost every method.
 * @}
 */

// do not indent this, for the sake of doxygen formatting
#if ALIB_DEBUG_STRINGS
#define ALIB_STRING_DBG_CHK(instance)    \
{                                        \
    (instance)->_dbgCheck();             \
}
#else
#define  ALIB_STRING_DBG_CHK(instance)
#endif


/**
 * @addtogroup GrpALibStringsMacros
 * @{ \def  ALIB_STRING_CONSTRUCTOR_FIX
 * Defines template class
 * \ref aworx::lib::strings::T_String  "T_String" for the given type. This may be used to suppress
 * "false errors" on compilation for certain types. For example (at the time of writing this), the
 * use of \c std::tuple with elements of type \b %String might lead to errors in certain complex
 * usage scenarios.<br>
 * The macro defines methods \c %Buffer and \c %Length to return \c nullptr and \c 0. In effect
 * the methods are never called. The same as the specialization of the struct itself, the
 * methods need to exist only to avoid the failure of a static assertion, as evaluated by some
 * compilers in the constructor of class \ref aworx::lib::strings::String "String".
 *
 * The macro must be placed outside of any namespace.<br>
 * When passing template types with comma separated type lists, the commas must be given using
 * macro \ref ALIB_COMMA.
 * @}
 */
#define ALIB_STRING_CONSTRUCTOR_FIX(TYPE)                                                          \
namespace aworx { namespace lib { namespace strings {                                              \
    template<>   struct      T_String<TYPE>   : public std::true_type                              \
    {                                                                                              \
        static inline const char* Buffer( const TYPE&  )                                           \
        {                                                                                          \
            ALIB_ERROR( "Macro ALIB_STRING_CONSTRUCTOR_FIX set for type \""                        \
                        ALIB_STRINGIFY((TYPE))                                                     \
                        "\", which is used for string construction" );                             \
            return nullptr;                                                                        \
        }                                                                                          \
                                                                                                   \
        static inline integer     Length( const TYPE&  )  { return 0; }                            \
    };                                                                                             \
}}}



namespace aworx { namespace lib { namespace strings {

// #################################################################################################
// forward declarations
// #################################################################################################
class String;

#if !defined(DOX_PARSER)
    ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING;
#endif

/** ********************************************************************************************
 * This is a specializable struct which defaults the question whether a given type
 * can be used to construct an \ref aworx::lib::strings::String "String" to \c false.
 *
 * Specializations of this struct inherit from \c std::true_type, to define a type to be a usable
 * constructor parameter of \b %String.
 *
 * Hence, this template struct supports converting 'external' <em>user defined</em> to
 * \ref aworx::lib::strings::String "String". It has a central role for using \b %ALib in a
 * \ref aworx::lib "non intrusive" way, by allowing to pass external string types just as
 * the are when invoking \b %ALib functions and methods that expect parameters of type
 * <c>const %String&</c>. Due to the implicit constructor invocation of C++
 * and the template meta programming in constructor of class \b %String, custom types
 * (that specialize this struct) may be passed "as is" to such methods.
 *
 * Methods #Buffer and #Length of partially specialized versions of this struct are invoked
 * by constructor \ref aworx::lib::strings::String::String(const TStringLike&) "String(const TStringLike&)"
 * to receive a pointer to the character buffer and the length of the external string type.
 *
 *
 * The following sample demonstrates the use of this technique:
 *
 * \snippet "DOX_ALIB_TOAS.cpp"     DOX_ALIB_TOAS
 *  The output will be:
 * \snippet "DOX_ALIB_TOAS.txt"     OUTPUT
 *
 * \note
 *   As shown in the sample, if a specialized version of this struct for a custom type exists, such
 *   type becomes automatically also an "applicable" type to class #AString, because template meta
 *   programming of method \b %AString::Apply checks for the existence of the specialization as well
 *   as the constructor of class \b %String.
 *
 * A compile time assertion will be raised when a String is constructed with a type that has
 * no specialization of this struct.
 * **********************************************************************************************/
template<typename TStringLike>
struct T_String     : public std::false_type
{
    /** ********************************************************************************************
     * In specialized versions, this method has to return a pointer to the buffer of the given
     * object of type \p TStringLike.
     *
     * This default implementation makes some static assertions to detect usage of an unsupported
     * type (a type that is not allowed to construct class \b %String with).
     *
     * @returns Has to return a pointer to the buffer of object of type T, respectively its length.
     **********************************************************************************************/
    static inline constexpr
    const char* Buffer( const TStringLike& )
    {
        // should never happen, because of static assert in string constructor
        return nullptr;
    }

    /** ********************************************************************************************
     * In specialized versions, this method has to return the length of the buffer of the given
     * object of type \p TStringLike.
     *
     * @returns Has to return the length of the string.
     **********************************************************************************************/
    static inline
    integer Length( const TStringLike& )
    {
        return (integer) 0;
    }
};

/** ************************************************************************************************
 * Specialization of \ref aworx::lib::strings::T_String for character pointers.
 **************************************************************************************************/
template<> struct T_String<char*> : public std::true_type
{
    /**
     * Returns the buffer of the literal.
     * @param src The pointer to the source string.
     * @return The buffer of the literal.
     */
    static inline constexpr const char*   Buffer(char* const & src)
    {
        return src;
    }

    /**
     * Returns the length of the string evaluated with \c std::strlen.
     * @param src The pointer to the source string.
     * @return The length.
     */
    static inline integer      Length(char* const & src)
    {
        return static_cast<integer>( strlen(src) );
    }
};

/** ************************************************************************************************
 * Specialization of \ref aworx::lib::strings::T_String for const character pointers.
 * \note
 *   This is a second specialization for type <c>char const*</c> existing besides the one
 *   for <c>char*</c>. Having both in place makes the TMP code of constructor of
 *   class \c %String easier.
 **************************************************************************************************/
template<> struct T_String<char const*> : public std::true_type
{
    /**
     * Returns the buffer of the literal.
     * @param src The pointer to the source string.
     * @return The buffer of the literal.
     */
    static inline constexpr const char*   Buffer(const char* const & src)
    {
        return src;
    }

    /**
     * Returns the length of the string evaluated with \c std::strlen.
     * @param src The pointer to the source string.
     * @return The length.
     */
    static inline integer      Length(const char* const & src)
    {
        return static_cast<integer>( strlen(src) );
    }
};



/** ************************************************************************************************
 * This is quite the same as template struct \ref aworx::lib::strings::T_String.
 * It is used when the length of the string can be inferred from type \p TLiteral.
 * The most obvious type are C++ string literal, hence character arrays \c char[TCapacity] of a
 * given length.
 *
 * See also class \ref aworx::lib::strings::StringLiteral "StringLiteral" which comes with a
 * (templated) specialization of this struct and can be used to declare C++ strings of fixed size
 * with variable contents.
 *
 * The benefit of specializing this struct when possible (in comparison to specializing
 * \ref aworx::lib::strings::T_String)
 * is that method #Length is declared \c constexpr with this struct.
 * This allows shorter template code and a small performance gain with some methods.
 *
 * @tparam TLiteral The literal type.
 **********************************************************************************************/
template<typename TLiteral>
struct T_StringLiteral  : public std::false_type
{

    /**
     * Returns the buffer of the literal.
     * @return The buffer of the literal.
     */
    static inline constexpr char* Buffer(const TLiteral& )  { return nullptr; }

    /**
     * Returns the constant length (length is depending only on type \p TLiteral)
     * @return The length.
     */
    static inline constexpr integer Length()      { return  1;      };

};

/** ************************************************************************************************
 * Specialization of \ref aworx::lib::strings::T_StringLiteral for character arrays.
 *
 * @tparam TCapacity The length of the character array.
 **************************************************************************************************/
template<size_t TCapacity>
struct T_StringLiteral<char[TCapacity]>  : public std::true_type
{
    /**
     * Returns the buffer of the literal.
     * @param src The source string.
     * @return The buffer of the literal.
     */
    static inline constexpr const char*    Buffer( char  const (&src) [TCapacity]   ) { return src; }

    /**
     * Returns the constant length which is \p TCapacity in \c char[TCapacity] minus one.
     * @return The length.
     */
    static inline constexpr integer        Length()        { return TCapacity -1;                  }
};



#if !defined(DOX_PARSER)
    ALIB_WARNINGS_RESTORE;
#endif

/** ************************************************************************************************
 * This class is the base class of all \b %ALib string classes. It represents a character string
 * whose data is allocated outside the scope of objects of this class.
 *
 * Once constructed, objects
 * of this class are immutable. This means, there is no interface to change their buffer or length
 * during their lifetime, which normally is rather volatile.
 *
 * The buffer represented might be zero-terminated or not. This is dependent on the data it was
 * constructed from. The buffer must not be changed and might even reside in read-only memory.
 *
 * <b>Templated Construction</b><br>
 * What makes this class very flexible, is the constructor variant
 * \ref aworx::lib::strings::String::String(const TStringLike&) "String(const TStringLike&)".
 * This template method internally uses so called
 * <em>template meta programming</em> to detect known types and, and
 * to convert them to constant references of those. They are then passed to template methods
 * \ref aworx::lib::strings::T_String "T_String" that simply return a pointer to the external types' buffer
 * and length. This way, objects of this class can be implicitly constructed from just anything that
 * 'smells' like a string.<br>
 * For more information on how to make %String support to implicitly construct from user defined types,
 * see namespace template function
 * \ref aworx::lib::strings::T_String "T_String".
 *
 * This class provides compiler defined copy and move constructors and assignment operators.
 * Once and object is constructed, methods #Buffer and #Length allow read access to the contents.
 *
 * <b>Null-State</b><br> \anchor CPP_STRINGS_AS_NULLSTATE
 * Objects of this class can be \e nulled which means that it is a difference whether they are
 * representing an empty string or a \c nullptr. As objects are immutable, this is decided
 * on construction: once a %String is nulled, it will remain nulled.
 * In other words, it makes a difference if an %String is constructed using
 * - <em>%String()</em>, which creates a \e nulled object, method #IsNull will give \c true, or
 * - <em>%String("")</em>, which creates an empty object. Method #IsNull will give \c false while
 *   method #IsEmpty will give \c true
 *
 * <b>Non-checking Method Variants</b><br> \anchor CPP_STRINGS_AS_NC
 * Some of the provided methods are templated with boolean parameter <em>TCheck</em> which allow
 * to invoke a faster and shorter version of the same method. For more information see
 * \ref alib_namespace_strings_nonchecking in the namespace documentation.
 *
 * \note Almost all methods of this class are declared <em>inline</em>.
 *
 * <p>
 * \note The immutable nature of %String is lifted by derived types. While class
 *       \ref aworx::lib::strings::Substring "Substring" allows to change the start and
 *       length of the string represented, class
 *       \ref aworx::lib::strings::AString "AString" holds a copy of the data and allows to
 *       modify the contents. Field #buffer of this class is declared
 *       as an anonymous union of a <em>const char*</em> and a <em>char*</em> but the latter is
 *       not exposed. It might be exposed by derived classes (and is by class \p %AString).
 *
 * <p>
 * \note For an introduction into the \b %ALib string classes see
 *       \ref aworx::lib::strings "namespace strings"
 **************************************************************************************************/
class String
{
    // #############################################################################################
    // Debug warnings
    // #############################################################################################
    public:
        //! @cond NO_DOX

            ALIB_WARN_ONCE_PER_TYPE_DECL(ALIB_API, SetLengthLonger)

            #if ALIB_DEBUG_STRINGS
                void     _dbgCheck()   const;
            #endif

        //! @endcond


    // #############################################################################################
    // Private fields
    // #############################################################################################
    protected:
    #if !defined( DOX_PARSER )

         union
         {
             const char*   buffer;
                   char*  vbuffer;
         };

    #else
            /**
             * Pointer to an array of characters that holds the string we are representing.
             * Read access to this field is granted with method #Buffer.
             */
             const char*   buffer;

            /**
             * Non-constant version of field #buffer. This field is not used in this class, but
             * has to be declared here, because it constitutes an anonymous union with field
             * #buffer.
             * Derived classes might use and expose this field, like e.g. class
             * \ref aworx::lib::strings::AString "AString" does.
             */
                   char*  vbuffer;
    #endif

        /**
         * The length of the string represented by us.
         * Read access to this field is granted with method #Length.
         */
        integer         length;

    public:

    /** ############################################################################################
     * @name Constructors
     ##@{ ########################################################################################*/
     public:

        /** ****************************************************************************************
         * Constructs a \e nulled %String
         ******************************************************************************************/
        inline
        constexpr String()
        : buffer(nullptr)
        , length(0)
        {}

        /** ****************************************************************************************
         * Constructs this object using the given external buffer and length of content.
         *
         *  \note The provided buffer does not need to be zero-terminated. However, there must not
         *        be any '\0' characters within the start and the given \p contentLength.
         *
         * @param buffer          The buffer to use.
         * @param contentLength   The length of the content in the given buffer.
         ******************************************************************************************/
        inline
        constexpr
        String( const char* buffer, integer contentLength ) : buffer(buffer)
                                                            , length(contentLength )
        {}

        /** ****************************************************************************************
         *  Constructs this object to represent a region of another %String (respectively a region
         *  of any string object whose type implicitly constructs a temporary %String).<br>
         *  The region is adjusted to  [0 ... <em>as.Length()</em>].
         *
         *  \note
         *    When constructing an aworx::String from a region of another aworx::String, this
         *    constructor is preferable over the overloaded <b>String(const char*, size_t)</b>
         *    (although often the same calculation of parameters has to be performed),
         *    because this constructor checks the bounds!
         *
         *  @param src           The src from that we will represent a region.
         *  @param regionStart   The start of the region within the given %String.
         *  @param regionLength  The length of the region within the given %String.
         ******************************************************************************************/
        inline
        String(  const String& src, integer regionStart, integer regionLength=  CString::MaxLen )
        {
            src.AdjustRegion( regionStart, regionLength );
            buffer=  src.buffer + regionStart;
            length=  regionLength;
        }

        #if !defined(DOX_PARSER)
            ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING;
        #endif
        /** ****************************************************************************************
         * Templated constructor for different types. This constructor uses some template meta
         * programming to provide maximum flexibility to implicitly embed the data of any string
         * type in an object of type %String.
         *
         * This constructor accepts the following types:
         * - <em>nullptr</em> (creates a \e nulled %String).
         * - <em>[const] char*</em>
         * - Classes derived from %String.
         * - User defined (external) types. See documentation of
         *   \ref aworx::lib::strings::T_String "T_String" on how to add support for implicit
         *   construction of  \b %ALib strings from custom string types.
         * - User defined literal types. See documentation of
         *   \ref aworx::lib::strings::T_StringLiteral "T_StringLiteral".
         *
         * When a non-supported type is passed, a compile-time error (\c static_assert) is raised.
         * In some rare cases, dependent on the compiler and platform, some false alarms may be
         * given for types that are not even passed to the constructor, but the compiler wrongly
         * "thinks" that such type is passed. For example, with advanced use of \c std::tuple template
         * class, such errors might occur. To suppress a "false" error, use macro
         * \ref ALIB_STRING_CONSTRUCTOR_FIX for the type in question.
         *
         * \note
         *   Other than the type of parameter \p src (<em>const TStringLike&</em>) may indicate,
         *   objects of the class types named above may be provided as pointer or reference.
         *   The TMP will detect \c nullptr and otherwise convert pointers to references.
         *
         * \see For more information, see
         * \ref aworx::lib::strings "namespace documentation" and template
         * function \ref aworx::lib::strings::T_String "T_String".
         *
         * @tparam TStringLike  Type that allows to construct Strings.
         * @param src           The source of template type T to take the buffer and length from.
         ******************************************************************************************/
        template <typename TStringLike>
        inline
        #if !defined(_MSC_VER)
            constexpr
        #endif
        String(const  TStringLike& src )
        : buffer(
            // nullptr ?
            std::is_same<decltype(nullptr), TStringLike>::value
              ? nullptr
            : std::is_pointer<TStringLike>::value && (*(char**)&src) == nullptr
              ? nullptr

            // String literal?
            :   T_StringLiteral<typename std::remove_cv<TStringLike                                    >::type>::value
              ? T_StringLiteral<typename std::remove_cv<TStringLike                                    >::type>::Buffer( (typename std::add_const<TStringLike>::type &) src )

            // String literal pointer?
            :   T_StringLiteral<typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type>::value
              ? T_StringLiteral<typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type>::Buffer( *(typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type *&)  src )

            // Custom string?
            :   T_String       <typename std::remove_cv<TStringLike                                    >::type>::value
              ? T_String       <typename std::remove_cv<TStringLike                                    >::type>::Buffer( (typename std::add_const<TStringLike>::type &) src )

            // Custom string pointer?
            :   T_String       <typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type>::value
              ? T_String       <typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type>::Buffer( *(typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type *&)  src )

            // Derived string type?
            :  std::is_base_of<String, TStringLike  >::value
              ?  ((String*) &src)->buffer

            // Pointer to derived string type?
            :  std::is_base_of<String, typename std::remove_pointer<TStringLike>::type  >::value
              ?  (*(String**) &src)->buffer

            : (const char*) -1   // this should never happen due to the static assert below
        )

        , length(
            // nullptr ?
            std::is_same<decltype(nullptr), TStringLike>::value
              ? 0
            : std::is_pointer<TStringLike>::value && (*(char**)&src) == nullptr
              ? 0

            // String literal?
            :   T_StringLiteral<typename std::remove_cv<TStringLike                                    >::type>::value
              ? T_StringLiteral<typename std::remove_cv<TStringLike                                    >::type>::Length()

            // String literal pointer?
            :   T_StringLiteral<typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type>::value
              ? T_StringLiteral<typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type>::Length()

            // Custom string?
            :   T_String       <typename std::remove_cv<TStringLike                                    >::type>::value
              ? T_String       <typename std::remove_cv<TStringLike                                    >::type>::Length( (typename std::add_const<TStringLike>::type &) src )

            // Custom string pointer?
            :   T_String       <typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type>::value
              ? T_String       <typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type>::Length( *(typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type *&)  src )

            // Derived string type?
            :  std::is_base_of<String, TStringLike  >::value
              ?  ((String*) &src)->length

            // Pointer to derived string type?
            :  std::is_base_of<String, typename std::remove_pointer<TStringLike>::type  >::value
              ?  (*(String**) &src)->length

            : -1  // this should never happen due to the static assert below
        )
        {
            static_assert
            (
                std::is_same   <decltype(nullptr),                                   TStringLike              >::value
             || T_StringLiteral<typename std::remove_cv<                             TStringLike       >::type>::value
             || T_StringLiteral<typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type>::value
             || T_String       <typename std::remove_cv<                             TStringLike       >::type>::value
             || T_String       <typename std::remove_cv<typename std::remove_pointer<TStringLike>::type>::type>::value
             || std::is_base_of<String,                                              TStringLike              >::value
             || std::is_base_of<String,                 typename std::remove_pointer<TStringLike>::type       >::value

               , "aworx::String can not be constructed from type TStringLike."
            );
        }

        #if !defined(DOX_PARSER)
            ALIB_WARNINGS_RESTORE
        #endif

    /** ############################################################################################
     * @name Buffer Access, Length and State
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         *  Returns a pointer to the first character of the string we are representing.
         *  \note The string is not guaranteed to be zero terminated.
         *
         * @return The internal buffer array.
         ******************************************************************************************/
        inline
        const char*  Buffer()           const       { return buffer;    }

        /** ****************************************************************************************
         *  Returns the length of the string we are representing.
         *
         * @return The length of the string represented by this.
         ******************************************************************************************/
        inline
        integer     Length()            const       { return length;    }

        /** ****************************************************************************************
         * Returns \c true if field #buffer equals nullptr, \c false otherwise.
         *
         * @return \c true if no buffer is allocated.
         ******************************************************************************************/
        inline
        bool         IsNull()           const       { return buffer == nullptr; }

        /** ****************************************************************************************
         * Returns \c true if field #buffer does not equal nullptr, \c false otherwise.
         *
         * @return \c true if no buffer is allocated.
         ******************************************************************************************/
        inline
        bool         IsNotNull()        const       { return buffer != nullptr; }

        /** ****************************************************************************************
         *  Returns \c true if this string is of zero length.
         * @return \c true if the actual length equals zero.
         ******************************************************************************************/
        inline
        bool         IsEmpty()          const       { return length == 0; }

        /** ****************************************************************************************
         *  Returns \c true if this string has a length of 1 or more.
         * @return \c true if the actual length does not equal zero.
         ******************************************************************************************/
        inline
        bool         IsNotEmpty()       const       { return length != 0; }


    /** ############################################################################################
     * @name Character access
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Retrieves the character at the given index. A range check is performed. If this fails,
         * '\0' is returned.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c false is given, no range check is performed.
         * @param idx      The index of the character to read.
         * @return The character at the given index, or '\0' if index out of range.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        char        CharAt( integer idx )          const
        {
            if (TCheck)
                return  ( idx >= 0 && idx < length ) ? *(buffer + idx )
                                                     : '\0' ;
            ALIB_ASSERT_ERROR( idx >= 0 && idx < length, "Non checking version: Index out of range" );

            return  *(buffer + idx );
        }

        /** ****************************************************************************************
         * Retrieves the first character. In case of an empty or \e nulled string, '\0' is returned.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c false is given, no check for an empty or \e nulled object is
         *                 performed.
         * @return The first character in the %String.
         *         If this instance's length is zero,  '\0' is returned.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        char        CharAtStart()          const
        {
            if (TCheck)
                return length > 0  ?  *(buffer)
                                   :  '\0';
            ALIB_ASSERT_ERROR(  length > 0, "Non checking invocation on empty string" );

            return  *(buffer);
        }


        /** ****************************************************************************************
         * Retrieves the last character. In case of an empty or \e nulled string, '\0' is returned.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c false is given, no check for an empty or \e nulled object is
         *                 performed.
         *
         * @return The last character in the %String.
         *         If this instance's length is zero,  '\0' is returned.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        char        CharAtEnd()          const
        {
            if (TCheck)
                return length > 0   ?  *(buffer + length - 1)
                                    : '\0';

            ALIB_ASSERT_ERROR( length > 0, "Non checking invocation on empty string" );

            return  *(buffer + length - 1);
        }

        /** ****************************************************************************************
         * Reads a character at a given index.
         *
         * \attention
         *   Unlike other operator methods in the family of of \b %ALib string classes, which are
         *   performing parameter checks (in this case a range check), this operator does
         *   <em>not</em> do a check!<br>
         *   The rationale is that in derived class %AString, which overrides this operator
         *   returning, a reference to the character to provide write access, no reference
         *   to a character can be given if the index is out of range. This way, this method is
         *   equivalent to method #CharAt<\c false>.<br>
         *   For safe access to characters in the buffer use #CharAt (with template parameter
         *   \p TCheck being \c true).
         *
         * @param   idx    The index of the character within this objects' buffer.
         * @returns If the character contained at index \p op.
         ******************************************************************************************/
         inline
         char    operator[] (integer idx) const
         {
            ALIB_ASSERT_ERROR( idx >= 0  && idx < length, "Index out of bounds" );
            return buffer[idx];
         }

    /** ############################################################################################
     * @name Comparison
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Compares this with given %String.
         * \c true is returned if both are \e nulled or empty.
         * If only one is \e nulled, \c false is returned.
         *
         * @param needle        An %String that is compared to this.
         * @tparam TSensitivity Determines if comparison is case sensitive (the default) or not.
         *
         * @return    \c true, if contents of this and the given %String are equal.
         ******************************************************************************************/
        template<lang::Case TSensitivity =lang::Case::Sensitive>
        inline
        bool Equals( const String& needle )
        const
        {
            ALIB_STRING_DBG_CHK(this)
            if (    ( IsNull() !=  needle.IsNull() )
                 || ( length   !=  needle.length   )    )
                return false;

            if ( length == 0 )
                return true;

            return  0 == (TSensitivity == lang::Case::Sensitive
                            ?   strncmp             ( buffer, needle.buffer, static_cast<size_t>(length) )
                            :   CString::strncasecmp( buffer, needle.buffer,                     length  ) );
        }

        /** ****************************************************************************************
         * Returns \c true, if the given %String is found at the given position.
         *
         *  \note The following rules apply
         *        - If \p pos is out of range or \p needle is \e nulled, \c false is returned.
         *          (This check only done if \p TCheck equals \c true.)
         *        - Otherwise, if the length of \p needle is 0, \c true is returned.
         *
         * @param needle        The string to compare with. If is \e nulled or empty, \c true is
         *                      returned.
         * @param pos           The position to search for needle.
         * @tparam TCheck       Defaults to \c true which is the normal invocation mode.
         *                      If \c <false\> is given, no check on parameter
         *                      \p pos is performed and \p needle must not be \e nulled.
         * @tparam TSensitivity Determines if comparison is case sensitive (the default) or not.
         * @return \c true if \p needle is found at the given position. False otherwise. *
         ******************************************************************************************/
        template< bool        TCheck      = true,
                  lang::Case  TSensitivity = lang::Case::Sensitive >
        inline
        bool ContainsAt( const String& needle, integer pos )
        const
        {
            integer needleLength= needle.length;
            ALIB_STRING_DBG_CHK(this)
            if ( TCheck )
            {
                if ( pos < 0 || pos + needleLength > length || needle.IsNull () )
                    return false;
                if ( needleLength == 0 )
                    return true;
            }
            else
            {
                ALIB_ASSERT_ERROR( pos >= 0 && pos + needleLength <= length && !needle.IsNull(),
                                   "Non checking and index out of range" );
                ALIB_ASSERT_ERROR( needleLength != 0,
                                   "Non checking and emtpy compare string" );
            }

            return 0 == ( TSensitivity == lang::Case::Sensitive
                            ?   strncmp             ( buffer + pos,  needle.buffer, static_cast<size_t>(needleLength) )
                            :   CString::strncasecmp( buffer + pos,  needle.buffer,                     needleLength  ) );
        }

        /** ****************************************************************************************
         * Returns \c true, if this string starts with the string found in parameter \p needle.
         * If \p needle is \e nulled or empty, \c true is returned.
         *
         * @param needle        The string to compare the start of this string with.
         *                      If \e nulled or empty, \c true is returned.
         * @tparam TSensitivity Determines if comparison is case sensitive (the default) or not.
         * @tparam TCheck       Defaults to \c true which is the normal invocation mode.
         *                      If \c <false\> is given, the given needle must not be empty
         *                      and must not be longer than this string!
         *                      \p pos is performed and \p needle must not be \e nulled.
         * @return \c true if \p needle is found at the start of this, \c false otherwise. *
         ******************************************************************************************/
        template<lang::Case  TSensitivity =lang::Case::Sensitive,
                 bool        TCheck      = true                   >
        inline
        bool StartsWith( const String& needle )
        const
        {
            integer needleLength= needle.length;
            if ( TCheck )
            {
                if ( needleLength > length )
                    return false;
                if ( needleLength == 0 )
                    return true;
            }
            else
            {
                ALIB_ASSERT_ERROR( needleLength <= length,
                                  "Non checking and needle longer than this string." );
                ALIB_ASSERT_ERROR( needleLength != 0,
                                  "Non checking and emtpy needle given." );
            }

            return 0 == ( TSensitivity == lang::Case::Sensitive
                            ?   strncmp             ( buffer,  needle.buffer, static_cast<size_t>(needleLength) )
                            :   CString::strncasecmp( buffer,  needle.buffer, needleLength ) );
        }

        /** ****************************************************************************************
         * Returns \c true, if this string ends with the string found in parameter \p needle.
         * If \p needle is \e nulled or empty, \c true is returned.
         *
         * @param needle        The string to compare the end of this string with.
         *                      If \e nulled or empty, \c true is returned.
         * @tparam TSensitivity Determines if comparison is case sensitive (the default) or not.
         * @return \c true if \p needle is found at the end of this, \c false otherwise. *
         ******************************************************************************************/
        template<lang::Case TSensitivity =lang::Case::Sensitive>
        inline
        bool EndsWith( const String& needle )
        const
        {
            integer needleLength= needle.length;
            if ( needleLength > length )
                return false;
            if ( needleLength <= 0 )
                return true;
            return 0 == ( TSensitivity == lang::Case::Sensitive
                          ?   strncmp             ( buffer + length - needleLength,  needle.buffer, static_cast<size_t>(needleLength) )
                          :   CString::strncasecmp( buffer + length - needleLength,  needle.buffer,                     needleLength  ) );
        }

        /** ****************************************************************************************
         * Compares this with another %String.
         *
         * @tparam TCheck       Defaults to \c true which is the normal invocation mode.
         *                      If \c false is given, no check for a \e nulled object (this)
         *                      performed and this string must not be of zero length
         *                      (while \p needle might be of zero length).
         * @param  needle       The string to compare this string with.
         * @tparam TSensitivity Determines if comparison is case sensitive (the default) or not.
         *
         * @return
         *  -  0 if this and \p needle are \e nulled or if both have a length of 0 or if both
         *       share the same content
         *  - <0 if this is \e nulled and \p needle is not or if this is smaller than \p needle.
         *  - >0 if this is not \e nulled but \p needle is or if this is greater than \p needle.
         ******************************************************************************************/
        template < bool TCheck      = true,
                   Case TSensitivity = Case::Sensitive>
        inline
        int CompareTo( const String&  needle )
        const
        {
            // check \c nullptr arguments
            if (TCheck &&        IsNull() )  return  needle.IsNull() ? 0 : -1;
            if (TCheck && needle.IsNull() )  return  +1;

            // zero length ?
            integer needleLength= needle.length;
            if ( TCheck && length == 0 )  return  needleLength == 0 ? 0 : -1;
            if (     needleLength == 0 )  return +1;

            bool   iAmShorter= length < needleLength;
            integer shortLen=   iAmShorter ? length : needleLength;

            int cmpVal= (TSensitivity == lang::Case::Sensitive)
                ? strncmp             ( buffer, needle.buffer, static_cast<size_t>(shortLen) )
                : CString::strncasecmp( buffer, needle.buffer,                     shortLen  );

            if ( cmpVal != 0 || length == needleLength )
                return cmpVal;
            return iAmShorter ? -1 : 1;
        }


        /** ****************************************************************************************
         * Compares this with a region of another %String.
         *
         * @param needle             The string to compare this string with.
         * @param needleRegionStart  The start of the region in \p needle to compare this object
         *                           with.
         * @param needleRegionLength The length of the region in \p needle to compare this object
         *                           with.
         *                           Defaults to CString::MaxLen;
         * @tparam TCheck            Defaults to \c true which is the normal invocation mode.
         *                           If \c false is given, no check for a \e nulled comparison
         *                           object is performed and this string must not be empty.
         *                           Furthermore, no check is performed whether the given region
         *                           fits to parameter \p needle. This also means that the default
         *                           value must not be used with <em>TCheck==\<\c false\></em>.
         * @tparam TSensitivity      Determines if comparison is case sensitive (the default) or not.
         *
         * @return
         *  -  0 if this and \p needle are \e nulled or if both have a length of 0 or if both
         *       share the same content
         *  - <0 if this is \e nulled and \p needle is not or if this is smaller than \p needle.
         *  - >0 if this is not \e nulled but \p needle is or if this is greater than \p needle.
         ******************************************************************************************/
        template < bool TCheck      = true,
                   Case TSensitivity = Case::Sensitive>
        inline
        int CompareTo(  const String&  needle,
                        integer       needleRegionStart,
                        integer       needleRegionLength  =CString::MaxLen
                     )
        const
        {
            if ( TCheck )
            {
                String cmpSub( needle.buffer, 0);
                needle.AdjustRegion( needleRegionStart, needleRegionLength );
                cmpSub.buffer+=   needleRegionStart;
                cmpSub.length=    needleRegionLength;

                return CompareTo<true,  TSensitivity>( cmpSub );
            }
            else
                return CompareTo<false, TSensitivity>( String( needle.buffer + needleRegionStart, needleRegionLength ) );
        }

        /** ****************************************************************************************
         * Compares a region of this object with a region of another %String.
         *
         * @param needle          The string to compare this string with.
         * @param cmpRegionStart  The start of the region in \p needle to compare this object
         *                        with.
         * @param cmpRegionLength The length of the region in \p needle to compare this object
         *                        with.
         * @param regionStart     The start of the region in this object to compare with
         * @param regionLength   The length of the region in this object to compare with.
         *                        Defaults to CString::MaxLen;
         * @tparam TCheck         Defaults to \c true which is the normal invocation mode.
         *                        If \c false is given, no check for a \e nulled comparison
         *                        object is performed and this string must not be empty.
         *                        Furthermore, no check is performed whether the given regions fit
         *                        to this object respectively the other region to the object given
         *                        with parameter \p needle.
         *                        This also means that the default value must not be used
         *                        with <em>TCheck==\<\c false\></em>.
         * @tparam TSensitivity   Determines if comparison is case sensitive (the default) or not.
         *
         * @return
         *  -  0 if this and \p needle are \e nulled or if both have a length of 0 or if both
         *       share the same content
         *  - <0 if this is \e nulled and \p needle is not or if this is smaller than \p needle.
         *  - >0 if this is not \e nulled but \p needle is or if this is greater than \p needle.
         ******************************************************************************************/
        template < bool TCheck       = true,
                   Case TSensitivity = Case::Sensitive>
        inline
        int CompareTo(  const String&   needle,
                        integer         cmpRegionStart,
                        integer         cmpRegionLength,
                        integer         regionStart,
                        integer         regionLength    =CString::MaxLen
                     )
        const
        {
            if ( TCheck )
            {
                String cmpSub( needle.buffer, 0);
                needle.AdjustRegion( cmpRegionStart, cmpRegionLength );
                cmpSub.buffer+=   cmpRegionStart;
                cmpSub.length=    cmpRegionLength;

                AdjustRegion( regionStart, regionLength );
                return String( buffer + regionStart, regionLength ).CompareTo<true, TSensitivity>( cmpSub );
            }
            else
                return String( buffer + regionStart, regionLength )
                        .CompareTo<false, TSensitivity>( String( needle.buffer + cmpRegionStart,
                                                                cmpRegionLength )               );

        }

        /**
         * Uses method #CompareTo with parameter \p op to perform a lexical comparison.
         *
         * @param op The string to compare this string with.
         * @returns \c true if this is lexically smaller then \p op, \c false otherwise.
         */
        inline
        bool     operator<  (const String& op) const { return CompareTo( op ) <  0 ;  }

        /**
         * Uses method #CompareTo with parameter \p op to perform a lexical comparison.
         *
         * @param op The string to compare this string with.
         * @returns \c true if this is lexically smaller or equal then \p op, \c false otherwise.
         */
        inline
        bool     operator<= (const String& op) const { return CompareTo( op ) <=  0 ;  }

        /**
         * Uses method #CompareTo with parameter \p op to perform a lexical comparison.
         *
         * @param op The string to compare this string with.
         * @returns \c true if this is lexically greater then \p op, \c false otherwise.
         */
        inline
        bool     operator>  (const String& op) const { return CompareTo( op ) >  0 ;  }

        /**
         * Uses method #CompareTo with parameter \p op to perform a lexical comparison.
         *
         * @param op The string to compare this string with.
         * @returns \c true if this is lexically greater or equal then \p op, \c false otherwise.
         */
        inline
        bool     operator>= (const String& op) const { return CompareTo( op ) >=  0 ;  }

        /**
         * Uses method #Equals with parameter \p op to test on equality.
         *
         * @param op The string to compare this string with.
         * @returns \c true if the strings are equal, \c false otherwise.
         */
        inline
        bool     operator== (const String& op) const { return Equals( op );  }

        /**
         * Uses method #Equals with parameter \p op to test on equality.
         *
         * @param op The string to compare this string with.
         * @returns \c true if the strings are equal, \c false otherwise.
         */
        inline
        bool     operator!= (const String& op) const { return !Equals( op ) != 0 ;  }

    /** ############################################################################################
     * @name Search
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Searches a character.
         *
         * @param needle  The character to search for.
         * @return  -1 if the character \p needle is not found.
         *           Otherwise the index of first occurrence.
         ******************************************************************************************/
        inline
        integer      IndexOf( char needle ) const
        {
            ALIB_STRING_DBG_CHK(this)
            const char* result=   static_cast<const char*>( memchr( buffer, needle, static_cast<size_t>(length) ) );

            return result != nullptr ? result  -  buffer
                                     : -1;
        }


        /** ****************************************************************************************
         * Searches a character starting from a given position.
         *
         * @tparam TCheck   Defaults to \c true which is the normal invocation mode.
         *                  If \c false is given, no range check is performed.
         * @param needle    The character to search for.
         * @param startIdx  The index in this to start searching the character.
         *
         * @return  -1 if the character \p needle is not found.
         *          Otherwise the index of its first occurrence.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        integer  IndexOf( char needle, integer startIdx ) const
        {
            ALIB_STRING_DBG_CHK(this)

            if ( TCheck )
            {
                // adjust range, if empty return -1
                     if ( startIdx <  0      )  startIdx= 0;
                else if ( startIdx >= length )  return -1;
            }
            else
            {
                ALIB_ASSERT_ERROR( startIdx >= 0 && startIdx < length,
                                 "Non checking and index out of range" );
            }

            const char* result=  static_cast<const char*>( memchr( buffer + startIdx, needle, static_cast<size_t>(length - startIdx) ) );

            return result != nullptr ? result  -  buffer
                                     : -1;
        }

        /** ****************************************************************************************
         * Searches a character within a region of this.
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c false is given, no range check is performed.
         * @param needle       The character to search for.
         * @param regionStart  The start of the region to search the character in.
         * @param regionLength The length of the region to search the character in.
         *
         * @return  -1 if the character \p needle is not found.
         *          Otherwise the index of its first occurrence.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        integer         IndexOf( char needle, integer regionStart, integer regionLength ) const
        {
            ALIB_STRING_DBG_CHK(this)

            if ( TCheck )
            {
                // adjust range, if empty return -1
                if ( AdjustRegion( regionStart, regionLength ) )
                    return -1;
            }
            else
            {
                #if ALIB_DEBUG
                    integer rs= regionStart;
                    integer rl= regionLength;
                    ALIB_ASSERT_ERROR( !AdjustRegion( rs, rl ) && rs == regionStart && rl == regionLength,
                                     "Non checking and region out of range or empty" );
                #endif
            }

            const char* result=  static_cast<const char*>( memchr( buffer + regionStart, needle, static_cast<size_t>(regionLength) ) );

            return result != nullptr ? result  -  buffer
                                     : -1;
        }

        /** ****************************************************************************************
         * Like \ref aworx::lib::strings::String::IndexOf "IndexOf" but in case the character is not
         * found, this method returns the length of this string instead of \c -1.
         * Depending on the invocation context, the choice for the right version of this method may
         * lead to shorter and more efficient code.
         *
         * @param needle  The character to search for.
         * @return  This strings #Length if the character \p needle is not found.
         *          Otherwise the index of first occurrence.
         ******************************************************************************************/
        inline
        integer      IndexOfOrLength( char needle ) const
        {
            ALIB_STRING_DBG_CHK(this)
            const char* result=   static_cast<const char*>( memchr( buffer, needle, static_cast<size_t>(length) ) );

            return result != nullptr ? result  -  buffer
                                     : length;
        }

        /** ****************************************************************************************
         * Like \ref aworx::lib::strings::String::IndexOf "IndexOf" but in case the character is not
         * found, this method returns the length of this string instead of \c -1.
         * Depending on the invocation context, the choice for the right version of this method may
         * lead to shorter and more efficient code.
         *
         * @param needle    The character to search for.
         * @param startIdx  The index in this to start searching the character.
         * @tparam TCheck   Defaults to \c true which is the normal invocation mode.
         *                  If \c false is given, no range check is performed.
         * @return  This strings #Length if the character \p needle is not found.
         *          Otherwise the index of first occurrence.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        integer      IndexOfOrLength( char needle, integer startIdx ) const
        {
            ALIB_STRING_DBG_CHK(this)
            if ( TCheck )
            {
                // adjust range, if empty return -1
                     if ( startIdx <  0      )  startIdx= 0;
                else if ( startIdx >= length )  return length;
            }
            else
            {
                ALIB_ASSERT_ERROR( startIdx >= 0 && startIdx < length,
                                 "Non checking and index out of range" );
            }

            const char* result=   static_cast<const char*>( memchr( buffer + startIdx, needle, static_cast<size_t>(length - startIdx) ) );
            return result != nullptr ? result  -  buffer
                                     : length;
        }

        /** ****************************************************************************************
         * Searches a character starting backwards from the end or a given start index.
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c false is given, no range check is performed.
         *                     Also, in this case, parameter startIndex must be provided.
         *
         * @param needle       The character to search for.
         * @param startIndex   The index in this to start searching the character.
         *                     Defaults to CString::MaxLen.
         *
         * @return  -1 if the character \p needle is not found.
         *          Otherwise the index of its last occurrence relative to the start index.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        integer    LastIndexOf( char needle, integer startIndex= CString::MaxLen ) const
        {
            ALIB_STRING_DBG_CHK(this)

            if ( TCheck )
            {
                // adjust range, if empty return -1
                if ( startIndex <  0      )   return -1;
                if ( startIndex >= length )   startIndex= length-1;
            }
            else
            {
                ALIB_ASSERT_ERROR( startIndex >= 0 && startIndex < length,
                                  "Non checking and index out of range"   );
            }

            while( startIndex >= 0 && buffer[ startIndex ] != needle )
                startIndex--;

            return startIndex;
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         *
         * \note In derived class \b %TString, a  faster version (using
         *       \e std::strpbrk() respectively \e std::strspn()) is available. So, if performance
         *       is important, it might be advisable to copy this \b %String (and the needles) to a
         *       terminatable buffer.
         *
         * This method searches forwards. For backwards search, see #LastIndexOf.
         *
         * @param needles     Pointer to a zero terminated set of characters to be taken into
         *                    account.
         * @param startIdx    The index to start the search at. If the given value is less than 0,
         *                    it is set to 0. If it exceeds the length of the string, the length of
         *                    the string is returned.
         *                    Defaults to 0.
         * @tparam TInclusion Denotes whether the search returns the first index that holds a value
         *                    that is included or that is not excluded in the set of needle
         *                    characters.
         * @tparam TCheck     Defaults to \c true which is the normal invocation mode.
         *                    If \c <false\> is given, no parameter checks are performed.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        template <lang::Inclusion   TInclusion,
                  bool              TCheck      = true>
        inline
        integer    IndexOfAny( const String& needles, integer startIdx= 0 )
        const
        {
            if (TCheck)
            {
                if ( startIdx < 0       ) startIdx= 0;
                if ( startIdx >= length ) return   -1;
            }
            else
            {
                ALIB_ASSERT_ERROR( startIdx >= 0 && startIdx < length && needles.Length() != 0,
                                 "Non checking and illegal parameters" );
            }


            integer idx= TInclusion == lang::Inclusion::Include
                     ? CString::IndexOfAnyIncluded( buffer + startIdx,  length - startIdx, needles.Buffer(), needles.Length() )
                     : CString::IndexOfAnyExcluded( buffer + startIdx,  length - startIdx, needles.Buffer(), needles.Length() );

            return idx == -1 ? -1 : startIdx + idx;
        }

        /** ****************************************************************************************
         * Returns the index of the last character which is included, respectively <em>not</em>
         * included in a given set of characters.
         *
         * This method searches backwards starting at the given index. For forwards search, see
         * #IndexOf.
         *
         * @param needles     Pointer to a zero terminated set of characters to be searched for.
         * @param startIdx    The index to start the search at. The value is cropped to be in
         *                    the bounds of 0 and the length of this object minus one.
         *                    Defaults to maximum integer value.
         * @tparam TInclusion Denotes whether the search returns the first index that holds a value
         *                    that is included or that is not excluded in the set of needle
         *                    characters.
         * @tparam TCheck     Defaults to \c true which is the normal invocation mode.
         *                    If \c <false\> is given, no parameter checks are performed.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        template <lang::Inclusion   TInclusion,
                  bool              TCheck = true   >
        inline
        integer LastIndexOfAny( const String& needles, integer startIdx= CString::MaxLen )
        const
        {
            if (TCheck)
            {
                if ( startIdx < 0       ) return -1;
                if ( startIdx >= length ) startIdx=  length - 1;
            }
            else
            {
                ALIB_ASSERT_ERROR( startIdx >= 0 && startIdx < length && needles.Length() != 0,
                                 "Non checking and illegal parameters" );
            }

            return   TInclusion == lang::Inclusion::Include
                       ? CString::LastIndexOfAnyInclude(  Buffer(), startIdx, needles.Buffer(), needles.Length() )
                       : CString::LastIndexOfAnyExclude(  Buffer(), startIdx, needles.Buffer(), needles.Length() );
        }

        /** ****************************************************************************************
         * Searches the given (unterminated) %String in the Buffer.
         *
         * If this string and string \p needle \p needle are known to be zero-terminated,
         * it is advisable to use the faster implementation of this method,
         * \ref aworx::lib::strings::TString::IndexOf "TString::IndexOf".<br>
         * This method is useful for example to search needles of type
         * \ref aworx::lib::strings::Substring "Substring" (which are not terminatable).
         *
         * If \p needle is empty, \p startIdx is returned.
         *
         * @param  needle         The string to search for.
         * @param  startIdx       The index to start the search at. Optional and defaults to \c 0.
         * @tparam TSensitivity   Case sensitivity of the comparison.
         *                        Optional and defaults to \b Case::Sensitive.
         * @tparam TCheck         Defaults to \c true which is the normal invocation mode.
         *                        If \c false is given, parameter \p startIdx must be valid and
         *                        \p needle must not be empty.
         *
         * @return    -1 if the string is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        template<lang::Case     TSensitivity  =  lang::Case::Sensitive,
                 bool           TCheck       = true                     >
        inline
        integer  IndexOfSubstring( const String&  needle,
                                   integer        startIdx= 0    )
        const
        {
            integer nLen=   needle.Length();
            if (TCheck)
            {
                if ( needle.IsNull()  )
                    return  -1;
                if ( startIdx < 0 )                startIdx= 0;
                if ( startIdx + nLen > length )    return -1;
            }
            else
            {
                ALIB_ASSERT_ERROR( startIdx >= 0 && startIdx <= length && needle.IsNotNull(),
                                 "Non checking and illegal parameters" );
            }
            if( nLen == 0 )
                return startIdx;
            const char*  buf=    buffer + startIdx;
            const char*  bufEnd= buffer + length - nLen + 1;
            const char* nBuf=    needle.Buffer();
            const char* nBufEnd= nBuf + nLen;

            while ( buf <= bufEnd )
            {
                const char* b=  buf;
                const char* n= nBuf;
                if ( TSensitivity == lang::Case::Sensitive )
                {
                    while ( *b++ == *n++ )
                        if( n == nBufEnd )
                            return buf  - buffer;
                }
                else
                {
                    while ( tolower(*b++) == tolower(*n++) )
                        if( n == nBufEnd )
                            return buf  - buffer;
                }
                buf++;
            }
            return -1;
        }

        /** ****************************************************************************************
         * Searches the first difference with given string.
         * If this string starts with \p needle, then the length of \p needle is returned.
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c false is given, no range check is performed.
         * @param needle       The character to search for.
         * @param sensitivity  Case sensitivity of the comparison.
         *                     Optional and defaults to \b Case::Sensitive.
         * @param idx          The index in this to start comparing with \p needle.
         *                     Optional and defaults to \c 0.
         *
         * @return   The index of the first difference found in \p needle or the neele's length.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        integer  IndexOfFirstDifference( const String&  needle,
                                         lang::Case     sensitivity = lang::Case::Sensitive,
                                         integer        idx         = 0                     ) const
        {
            ALIB_STRING_DBG_CHK(this)

            if ( TCheck )
            {
                // adjust range, if empty return -1
                     if ( idx <  0      )  idx= 0;
                else if ( idx >= length )  return idx;
            }
            else
            {
                ALIB_ASSERT_ERROR( idx >= 0 && idx < length,
                                   "Non checking and index out of range" );
            }

            return   CString::IndexOfFirstDifference(        buffer + idx,           length - idx,
                                                      needle.buffer,          needle.length,
                                                      sensitivity                                 );
        }

        /** ****************************************************************************************
         * Counts all occurrences of \p needle from \p startPos to the end of the string.
         *
         * For empty strings \p needle, \c 0 is returned.
         *
         * @param needle    The string to search for.
         * @param startPos  The index to start the counting.
         *                  Optional and defaults to \c 0.
         * @tparam TCheck   Defaults to \c true which is the normal invocation mode.
         *                  If \c false is given, no range check is performed.
         *
         * @return  The index of the first difference in \p needle.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        int  CountChar( char            needle,
                        integer         startPos        = 0                                  ) const
        {
            ALIB_STRING_DBG_CHK(this)
            if ( TCheck )
            {
                // adjust range, if empty return -1
                     if ( startPos <  0      )  startPos= 0;
                else if ( startPos >= length )  return 0;
            }
            else
            {
                ALIB_ASSERT_ERROR( startPos >= 0 && startPos < length,
                                 "Non checking and index out of range" );
            }


            int     result= 0;
            while( startPos < length && (startPos= IndexOf<false>( needle, startPos )) >= 0 )
            {
                startPos++;
                result++;
            }

            return result;
        }

        /** ****************************************************************************************
         * Counts all occurrences of \p needle, unless followed by \p omit, starting at
         * \p startPos to the end of the string.
         *
         * For empty strings \p needle, \c 0 is returned.
         * Also, for empty strings \p omit, \c 0 is returned.
         *
         * @param needle    The string to search for.
         * @param omit      Omit occurrence if the given character follows.
         * @param startPos  The index to start the counting.
         *                  Optional and defaults to \c 0.
         * @tparam TCheck   Defaults to \c true which is the normal invocation mode.
         *                  If \c false is given, no range check is performed.
         *
         * @return  The index of the first difference in \p needle.
         ******************************************************************************************/
        template <bool TCheck= true>
        int  CountChar( char            needle,
                        char            omit,
                        integer         startPos        = 0                                  ) const
        {
            ALIB_STRING_DBG_CHK(this)
            if ( TCheck )
            {
                // adjust range, if empty return -1
                     if ( startPos <  0      )  startPos= 0;
                else if ( startPos >= length )  return 0;
            }
            else
            {
                ALIB_ASSERT_ERROR( startPos >= 0 && startPos < length,
                                 "Non checking and index out of range" );
            }

            int     result= 0;
            while( startPos < length && (startPos= IndexOf<false>( needle, startPos )) >= 0 )
            {
                startPos++;
                if( startPos < Length()  &&  *(buffer + startPos) == omit  )
                    continue;

                result++;
            }

            return result;
        }

        /** ****************************************************************************************
         * Counts all occurrences of \p needle from \p startPos to the end of the string.
         *
         * For empty strings \p needle, \c 0 is returned.
         *
         * @param needle        The string to search for.
         * @param startPos      The index to start the counting.
         *                      Optional and defaults to \c 0.
         * @tparam TSensitivity Case sensitivity of the comparison.
         *                      Optional and defaults to \b Case::Sensitive.
         * @tparam TCheck       Defaults to \c true which is the normal invocation mode.
         *                      If \c false is given, parameter \p startIdx must be valid and
         *                      \p needle must not be empty.
         *
         * @return  The index of the first difference in \p needle.
         ******************************************************************************************/
        template<lang::Case     TSensitivity  =  lang::Case::Sensitive,
                 bool           TCheck       = true                     >
        int  Count( const String&   needle,
                    integer         startPos        = 0                                  ) const
        {
            ALIB_STRING_DBG_CHK(this)
            integer nLen= needle.Length();
            if( nLen == 0  )
                return 0;
            if (TCheck)
            {
                if ( startPos < 0 )                startPos= 0;
                if ( startPos + nLen > length )    return  0;
            }
            else
            {
                ALIB_ASSERT_ERROR( startPos >= 0 && startPos < length,
                                 "Non checking and illegal parameters" );
            }

            int     result= 0;
            while( (startPos= IndexOfSubstring<TSensitivity, false>( needle, startPos )) >= 0 )
            {
                startPos+= needle.Length();
                result++;
            }

            return result;
        }

        /** ****************************************************************************************
         * Counts all occurrences of \p needle, unless followed by \p omit, starting at
         * \p startPos to the end of the string.
         *
         * For empty strings \p needle, \c 0 is returned.
         * Also, for empty strings \p omit, \c 0 is returned.
         *
         * @param needle       The string to search for.
         * @param omit         Omit occurrence if the given string follows.
         * @param startPos     The index to start the counting.
         *                     Optional and defaults to \c 0.
         * @tparam sensitivity Case sensitivity of the comparison.
         *                     Optional and defaults to \b Case::Sensitive.
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c false is given, parameter \p startIdx must be valid and
         *                     \p needle must not be empty.
         *
         * @return  The index of the first difference in \p needle.
         ******************************************************************************************/
        template<lang::Case     sensitivity  =  lang::Case::Sensitive,
                 bool           TCheck       = true                     >
        int  Count( const String&   needle,
                    const String&   omit,
                    integer         startPos        = 0                                  ) const
        {
            ALIB_STRING_DBG_CHK(this)
            integer nLen= needle.Length();
            if ( nLen == 0  )
                return  0;
            if (TCheck)
            {
                if ( startPos < 0 )                startPos= 0;
                if ( startPos + nLen > length )    return  0;
            }
            else
            {
                ALIB_ASSERT_ERROR( startPos >= 0 && startPos < length,
                                 "Non checking and illegal parameters" );
            }


            int     result= 0;
            while( (startPos= IndexOfSubstring<sensitivity,false>( needle, startPos )) >= 0 )
            {
                startPos+= nLen;
                if(     startPos + omit.Length() <= Length()
                    &&  String( buffer, startPos, omit.Length()).Equals<sensitivity>( omit )
                  )
                    continue;

                result++;
            }

            return result;
        }



    /** ############################################################################################
     * @name Conversion
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Copies the strings contents into a given character buffer.
         *
         * @param dest   The destination buffer.
         * @return    The length of this string.
         ******************************************************************************************/
        inline
        integer CopyTo( char* dest ) const
        {
            memcpy( dest, buffer, static_cast<size_t>(length) );
            return length;
        }

        /** ****************************************************************************************
         * Converts a region of this string into a wide character string.
         * The conversion is done using
         * - <em>mbsnrtowcs()</em> on glibc platforms (e.g. Linux)
         * - <em>MultiByteToWideChar(CP_UTF8,...)</em> on the Windows platform.
         *
         * The destination string will be zero terminated.
         *
         * \note
         * - For the reverse action, namely to convert wide characters to multi-byte characters,
         *   use class
         *   \ref aworx::lib::strings::AString        "AString" with template method
         *   \ref aworx::lib::strings::AString::Apply "AString::Apply" e.g.
         *   by using operator
         *   \ref aworx::lib::strings::AString::operator<<(const T&) "AString::operator<<(const T&)"
         *   with T being <em>[const] wchar_t*</em>.
         * - On Linux, it might be necessary to invoke std function <em>setlocale()</em> once,
         *   prior to using this method.
         *   This, by default, is done in \ref aworx::lib::ALib::Init "ALib::Init".
         *
         * @param dest          The destination buffer.
         * @param destCapacity  The size of the destination buffer. Has to be equal or greater than
         *                      the provided region length plus one for termination.
         * @param regionStart   The start of the region in this to convert.
         *                      Optional and defaults to \c 0.
         * @param regionLength  The maximum length of the region in this to convert.
         *                      Optional and defaults to CString::MaxLen
         *
         * @return    On success, the length of converted destination string. -1 for conversion
         *            failure, -2 if destination buffer was too small.
         ******************************************************************************************/
        ALIB_API integer  ToWString( wchar_t*  dest,             integer  destCapacity,
                                      integer  regionStart =0,   integer  regionLength   =CString::MaxLen ) const;
    /** ############################################################################################
     * @name Helper methods
     ##@{ ########################################################################################*/
    public:
        /** ************************************************************************************
         * This is a helper method that adjusts a given region (in/out parameters) to fit to
         * this objects' buffer range [0..length].
         *
         * @param regionStart     The proposed region start which might get adjusted to fit to
         *                        span 0 to referenceLength. (In/out parameter.)
         * @param regionLength    The proposed region length which might get adjusted to fit to
         *                        span 0 to referenceLength. (In/out parameter.)
         *
         * @return   Returns \c true, if the adjusted region is empty.
         **************************************************************************************/
        inline
        bool AdjustRegion( integer& regionStart, integer& regionLength ) const
        {
            return CString::AdjustRegion( length, regionStart, regionLength );
        }

    /** ############################################################################################
     * @name std::iterator
     ##@{ ########################################################################################*/
    public:
        /** ****************************************************************************************
         * Implementation of \c std::iterator for class \b String. This class exposes
         * #ConstIterator which uses <c>const char*</c> and <c>const char&</c> as
         * pointer and reference types. Descendent classes may expose a mutable version
         * (e.g. \ref aworx::lib::strings::AString "AString").
         *
         * As the name of the class indicates, this iterator satisfies the std library concept
         * [RandomAccessIterator](http://en.cppreference.com/w/cpp/concept/RandomAccessIterator).
         ******************************************************************************************/
        template<typename TPointer, typename TReference>
        class RandomAccessIteratorBase
            : public std::iterator< std::random_access_iterator_tag,  // iterator_category
                                    char,                             // value_type
                                    integer,                          // distance type
                                    TPointer,                         // pointer
                                    TReference                        // reference
                                  >
        {
            protected:
                /** The pointer into the buffer is all we store. */
                TPointer p;

            public:
                /** Constructor.
                 *  @param _p Our initial value       */
                explicit RandomAccessIteratorBase( TPointer _p = nullptr ) : p(_p)
                {
                }

            //######################   To satisfy concept of  InputIterator   ######################

                /** Prefix increment operator.
                 *  @return A reference to ourselves. */
                RandomAccessIteratorBase& operator++()
                {
                    p++;
                    return *this;
                }

                /** Postfix increment operator.
                 *  @return A reference to ourselves. */
                RandomAccessIteratorBase operator++(int)
                {
                    return RandomAccessIteratorBase(p++);
                }

                /** Comparison operator.
                 *  @param other  The iterator to compare ourselves to.
                 *  @return \c true if this and given iterator are equal, \c false otherwise. */
                bool operator==(RandomAccessIteratorBase other)             const
                {
                    return p == other.p;
                }

                /** Comparison operator.
                 *  @param other  The iterator to compare ourselves to.
                 *  @return \c true if this and given iterator are not equal, \c false otherwise. */
                bool operator!=(RandomAccessIteratorBase other)             const
                {
                    return !(*this == other);
                }

                /** Retrieves the character that this iterator references.
                 * @return The character value.                               */
                TReference operator*()                          const
                {
                    return *p;
                }


            //##################   To satisfy concept of  BidirectionalIterator   ##################

                /** Prefix decrement operator.
                 *  @return A reference to ourselves. */
                RandomAccessIteratorBase& operator--()
                {
                    p--;
                    return *this;
                }


                /** Postfix decrement operator.
                 *  @return An iterator that with the old value. */
                RandomAccessIteratorBase operator--(int)
                {
                    return RandomAccessIteratorBase(p--);
                }


            //##################   To satisfy concept of  RandomAccessIterator   ###################

                /** Addition assignment.
                 *  @param n The value to subtract.
                 *  @return A reference to ourselves. */
                RandomAccessIteratorBase& operator+=(integer n)
                {
                    p+= n;
                    return *this;
                }

                /** Subtraction assignment.
                 *  @param n The value to subtract.
                 *  @return A reference to ourselves. */
                RandomAccessIteratorBase& operator-=(integer n)
                {
                    p-= n;
                    return *this;
                }

                /** Addition.
                 *  @param n The value to subtract.
                 *  @return A reference to the new iterator. */
                RandomAccessIteratorBase operator+(integer n)       const
                {
                    return RandomAccessIteratorBase( p + n );
                }

                /** Subtraction.
                 *  @param n The value to subtract.
                 *  @return A reference to the new iterator. */
                RandomAccessIteratorBase operator-(integer n)       const
                {
                    return RandomAccessIteratorBase( p - n );
                }

                /** Difference (distance) from this iterator to the given one.
                 *  @param other  The iterator to subtract
                 *  @return The iterator to subtract.    */
                integer operator-(RandomAccessIteratorBase other)   const
                {
                    return p - other.p;
                }

                /** Subscript operator.
                 *  @param n  The iterator to subtract
                 *  @return <c>*( (*this) + n )</c>.                      */
                TReference operator[]( integer n )   const
                {
                    return *( p + n );
                }

            //#### Comparison operators (also needed to satisfy concept of RandomAccessIterator) ###

                /** Compares this iterator with the given one.
                 *  @param other  The iterator to compare
                 *  @return \c true if this iterator is \e smaller than \p other,
                 *          \c false otherwise. */
                bool operator<(RandomAccessIteratorBase other)   const
                {
                    return p < other.p;
                }

                /** Compares this iterator with the given one.
                 *  @param other  The iterator to compare
                 *  @return \c true if this iterator is \e smaller than or equal to \p other,
                 *          \c false otherwise. */
                bool operator<=(RandomAccessIteratorBase other)   const
                {
                    return p <= other.p;
                }


                /** Compares this iterator with the given one.
                 *  @param other  The iterator to compare
                 *  @return \c true if this iterator is \e greater than \p other,
                 *          \c false otherwise. */
                bool operator>(RandomAccessIteratorBase other)   const
                {
                    return p > other.p;
                }

                /** Compares this iterator with the given one.
                 *  @param other  The iterator to compare
                 *  @return \c true if this iterator is \e greater than or equal to \p other,
                 *          \c false otherwise. */
                bool operator>=(RandomAccessIteratorBase other)   const
                {
                    return p >= other.p;
                }
        };

        /** The constant iterator exposed by this character container. A Mutable version is
         *  found only in descendent classes (e.g. \ref aworx::lib::strings::AString "AString").
         */
        using ConstIterator= RandomAccessIteratorBase<const char*, const char&>;


        /**
         * Returns an iterator pointing to the start of this string.
         * @return The start of this string.
         */
        ConstIterator begin()                       const
        {
            return ConstIterator( Buffer() );
        }

        /**
         * Returns an iterator pointing to the first character behind this string.
         * @return The end of this string.
         */
        ConstIterator end()                         const
        {
            return ConstIterator( Buffer() + length );
        }

        /** ****************************************************************************************
         * Constructs this string using start and end iterators.
         *
         * @param start An iterator referencing the start of the string.
         * @param end   An iterator referencing the end of the string.
         ******************************************************************************************/
        inline
        String( ConstIterator& start, ConstIterator& end )
        : buffer( &*start)
        , length( end-start >= 0 ? end-start : 0 )
        {}



}; // class %String


/** ************************************************************************************************
 * Implements a hash functor for class \alib{strings,String}, usable with types found in
 * namespace \b std.<br>
 * Instead of implementing \b std::hash inside namespace \b std, this struct can be
 * provided as template parameter, e.g. to \b std::unordered_map, for which a templated type
 * definition is provided for with \ref aworx::UnorderedStringMap.
 **************************************************************************************************/
struct std_StringHash
{
    /**
     * Calculates the hash code for class \b String.
     * @param src The string object to hash.
     * @return The hash code.
     */
    size_t operator()(const String& src) const
    {
        integer result= 0xc70f6907UL;

        for (int i = 0; i < src.Length(); i++)
            result = 31*result + src.CharAt<false>(i++);

        return static_cast<size_t>( result );
    }
};

/** ************************************************************************************************
 * Implements a comparison functor for objects of class \alib{strings,String}, usable with types
 * found in namespace \b std.<br>
 * Instead of implementing the operator inside namespace \b std, this struct can be
 * provided as template parameter, e.g. to \b std::unordered_map., for which a templated type
 * definition is provided for with \ref aworx::UnorderedStringMap.
 **************************************************************************************************/
struct std_StringEquals
{
    /**
     * Invokes \ref aworx::lib::strings::String::Equals "String::Equals" on \p lhs, passing
     * \p rhs.
     * @param lhs The first string object.
     * @param rhs The second string object.
     * @return The hash code.
     */
    bool operator()(const String& lhs, const String& rhs) const
    {
        return lhs.Equals( rhs );
    }
};

/** ************************************************************************************************
 * Implements a case insensitive hash functor for class \alib{strings,String}, usable with types
 * found in namespace \b std.<br>
 * Instead of implementing \b std::hash inside namespace \b std, this struct can be
 * provided as template parameter, e.g. to \b std::unordered_map, for which a templated type
 * definition is provided for with \ref aworx::UnorderedStringMapIgnoreCase.
 **************************************************************************************************/
struct std_StringHashIgnoreCase
{
    /**
     * Calculates the hash code for class \b String.
     * @param src The string object to hash.
     * @return The hash code.
     */
    size_t operator()(const String& src) const
    {
        integer result= 0xc70f6907UL;

        for (int i = 0; i < src.Length(); i++)
            result = 31*result + toupper(src.CharAt<false>(i++));

        return static_cast<size_t>( result );
    }
};

/** ************************************************************************************************
 * Implements a case insensitive comparison functor for objects of class \alib{strings,String},
 * usable with types found in namespace \b std.<br>
 * Instead of implementing the operator inside namespace \b std, this struct can be
 * provided as template parameter, e.g. to \b std::unordered_map., for which a templated type
 * definition is provided for with \ref aworx::UnorderedStringMapIgnoreCase.
 **************************************************************************************************/
struct std_StringEqualsIgnoreCase
{
    /**
     * Invokes \ref aworx::lib::strings::String::Equals "String::Equals" on \p lhs, passing
     * \p rhs.
     * @param lhs The first string object.
     * @param rhs The second string object.
     * @return The hash code.
     */
    bool operator()(const String& lhs, const String& rhs) const
    {
        return lhs.Equals<Case::Ignore>( rhs );
    }
};
}} // namespace lib::strings


/** Type alias name in namespace #aworx. */
using     String                =   aworx::lib::strings::String;

/** Unordered map using a key of type \alib{strings,String}. */
template<typename TValue>
using     UnorderedStringMap           =   std::unordered_map<String, TValue,
                                                              lib::strings::std_StringHash,
                                                              lib::strings::std_StringEquals>;

/** Unordered map using a case insensitive key of type \alib{strings,String}. */
template<typename TValue>
using     UnorderedStringMapIgnoreCase =   std::unordered_map<String, TValue,
                                                             lib::strings::std_StringHashIgnoreCase,
                                                             lib::strings::std_StringEqualsIgnoreCase>;

// #################################################################################################
// aworx namespace string singletons
// #################################################################################################
/**
 * A constant \e nulled \b %ALib string.
 * E.g. useful to provide as parameter to methods or to use as default value for method
 * parameters.
 */
constexpr lib::strings::String   NullString;

/**
 * A constant empty (but not \e nulled) \b %ALib string
 * E.g. useful to provide as parameter to methods or to use as default value for method
 * parameters.
 */
constexpr lib::strings::String   EmptyString {"", 0};


} // namespace aworx

// #################################################################################################
// False assertion fixes. Dependent on compiler and library
// #################################################################################################
/** clang needs this when class String is used as a key of class std::map (in std::map::operator[String]). */
#if defined(__clang__)
    ALIB_STRING_CONSTRUCTOR_FIX( std::tuple<      String   >  )
    ALIB_STRING_CONSTRUCTOR_FIX( std::tuple<      String & >  )
    ALIB_STRING_CONSTRUCTOR_FIX( std::tuple<const String & >  )
    ALIB_STRING_CONSTRUCTOR_FIX( std::tuple<      String &&>  )
#endif



#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
#endif // HPP_ALIB_STRINGS_STRING
