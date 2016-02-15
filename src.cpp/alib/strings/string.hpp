// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_ALIB_ALIB) || defined(HPP_ALIB_STRINGS_AS)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_ALIB_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_ALIB_STRINGS_AS
#define HPP_ALIB_STRINGS_AS 1

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
#endif

// #################################################################################################
// Macros
// #################################################################################################

/**
 * @addtogroup GrpALibStringsMacros
 * @{ \def  ALIB_STRING_DBG_CHK
 *  Simple macro that just invokes method _dbgCheck(), which is defined for classes
 *  \ref aworx::lib::strings::String   "String",
 *  \ref aworx::lib::strings::TString  "TString" and
 *  \ref aworx::lib::strings::AString "AString".
 *  It is active only when compiler symbol \ref ALIB_DEBUG_STRINGS is set.
 *  The macro is placed in almost every method.
 * @}
 */

// do not indent this, for the sake of doxygen formatting
#if defined(ALIB_DEBUG_STRINGS)
    #define ALIB_STRING_DBG_CHK(instance)    \
    {                                        \
        (instance)->_dbgCheck();             \
    }
#else
    #define  ALIB_STRING_DBG_CHK(instance)
#endif

namespace aworx {
namespace           lib {
namespace                   strings {

// #################################################################################################
// forwards
// #################################################################################################
class String;
class NumberFormat;

// We are including this header before we include headers for class Report. Therefore, we have to
// move debug warnings to the implementation file. (And: We do not need to document this to
// the user as this is pure internal stuff.)
#if defined(ALIB_DEBUG) && !defined( IS_DOXYGEN_PARSER )
    ALIB_API void dbgAStringAlibWarning( const char* msg );
    ALIB_API void dbgAStringAlibError  ( const char* msg );
#endif

/** ********************************************************************************************
 * This is a TMP (template meta programming) 'class' which defaults the question
 * <c>ToStringDefined<T>::value</c> to \c false for every type.<br>
 * When implementing specializations of template function
 * \ref aworx::lib::strings::ToString(const TString) "ToString" for custom types, this class has to
 * be specialized as well.
 * Otherwise, a compile time assertion (<em>static_assert</em>) will fail whenever the type
 * is used to implicitly construct an
 * \ref aworx::lib::strings::String "String" providing that type.
 *
 * Definition has to be made as follows:
\verbatim
    template<>  struct ToStringDefined<T> : public std::true_type {};
\endverbatim
 * where T is the type that is to be defined given as a const reference.
 * For example, in the ALib support header file <em>"alib/compatibility/std_string.hpp"</em>,
 * for class <em>std::string</em>, the definition looks as follows:
\verbatim
    template<>  struct ToStringDefined<const std::string&> : public std::true_type {};
\endverbatim
 * \see For more information and a sample refer to
 *  \ref aworx::lib::strings::ToString(const TString) "ToString".
 * **********************************************************************************************/
template<typename Type>  struct ToStringDefined     : public std::false_type{};


/** ********************************************************************************************
 * This template function supports converting 'external' <em>user defined</em>
 * to ALib string
 * \ref aworx::lib::strings::String "String". It has a central role for using ALib in a
 * \ref aworx::lib "non intrusive" way, by allowing to pass external string types just as
 * the are when invoking ALib functions and methods.
 *
 * Partially specialized versions of this method are invoked by constructor
 * \ref aworx::lib::strings::String::String(const T&) "String(const T&)"
 * with template parameters \p TString and \p TReturn set to receive a pointer to the
 * character buffer and the length of the external string type.
 *
 * The type of the (external) string is given in parameter \p TString. To restrict need for
 * specializations of this method to a single variant of the external type, \p TSTring will
 * always be a "constant reference". As an example, if the external type was
 * '<em>class MyString></em>' and a non-constant pointer to an object of that type was used to
 * construct an %String, the template parameter \p TString would be '<em>const MyString &</em>'.
 *
 * The second type that is given in parameter \p TReturn has two possible values when invoked
 * from the constructor r of class %String:
 * - '<em>const char*</em>' for returning the string buffer
 * - '<em>int</em>' for returning the strings length
 *
 * This way, exactly two specializations of this template method <em>ToString</em> have to be
 * provided when using ALib with external types: Both with \p TString being a constant reference
 * to the user defined type, one with \p TReturn being <em>int</em>, the other with \p TReturn
 * being <em>const char*</em>.
 *
 * Finally, for allowing static (compile time) assertions when user code tries to provide arbitrary
 * types to
 * \ref aworx::lib::strings::String::String(const T&) "String(const T&)" that are not supported with
 * specializations of this method, it is necessary to implement
 * \ref aworx::lib::strings::ToStringDefined "ToStringDefined" for the external type as well.
 *
 * The following sample demonstrates this. Please note, that the sample in addition
 * provides an implementation of
 * \ref aworx::lib::strings::ApplyTo "ApplyTo". This is a similar mechanism for 'applying' user defined
 * string types to class
 * \ref aworx::lib::strings::AString "AString". The general term '<em>applying to</em>' for external string
 * types normally is implemented in a way that it means '<em>append to</em>'.
 *
 * \snippet "DOX_ALIB_TOAS.cpp"     DOX_ALIB_TOAS
 *  The output will be:
 * \snippet "DOX_ALIB_TOAS.txt"     OUTPUT
 *
 * @returns Has to return a pointer to the buffer of object of type T, respectively its length.
 **********************************************************************************************/

// this template method is for debugging.
/*
template<typename TPlain>   inline void TellMeThe_TPlain_Type()
{
    static_assert(
        // nullptr?
            std::is_same    <decltype(nullptr), TPlain >::value

        // char*
        ||  std::is_same    <char  ,            TPlain >::value

        // literal? (fixed size char array)
        ||  (    std::is_array < TPlain >::value
              && std::is_same<char,  typename std::remove_extent<TPlain>::type >::value )

        // another String
        ||  std::is_base_of <String,            TPlain >::value

        // External type with defined ToString method?
        ||  ToStringDefined     <          const    TPlain&>::value

    , "!!!!!!!!!! Your compiler speaking... !!!!!!!!!!!!" );

}
*/

template<typename TString, typename TReturn>   inline TReturn ToString( const TString )
{
    // prevent invoking us with unknown types
    static_assert(      std::is_same< int        , TReturn >::value
                    ||  std::is_same< const char*, TReturn >::value,
    "ALib: Wrong type for TReturn requested. Allowed is 'int' and 'const char*'" );

    using TPlain= typename std::remove_const    <
                  typename std::remove_pointer  <
                  typename std::remove_reference<
                  typename std::remove_const    < TString >::type>::type>::type>::type;

    //TellMeThe_TPlain_Type<TPlain>();

    static_assert(
        // nullptr?
            std::is_same    <decltype(nullptr), TPlain >::value

        // char*
        ||  std::is_same    <char  ,            TPlain >::value

        // literal? (fixed size char array)
        ||  (    std::is_array < TPlain >::value
              && std::is_same<char,  typename std::remove_extent<TPlain>::type >::value )

        // another String
        ||  std::is_base_of <String,            TPlain >::value

        // External type wiht defined ToString method?
        ||  ToStringDefined     <          const    TPlain&>::value

    , "ALib: Unknown type to construct String. Implement ToString() to support implicit conversions." );


    // should never happen, because of static assert above
    assert(false);
    return (TReturn) 0;
}


/** ************************************************************************************************
 * This class is the base class of all ALib string classes. It represents a character string
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
 * \ref aworx::lib::strings::String::String(const T&) "String(const T&)".
 * This template method internally uses so called
 * <em>template meta programming</em> to detect known types and, and
 * to convert them to constant references of those. They are then passed to template methods
 * \ref aworx::lib::strings::ToString "ToString" that simply return a pointer to the external types' buffer
 * and length. This way, objects of this class can be implicitly constructed from just anything that
 * 'smells' like a string.<br>
 * For more information on how to make %String support to implicitly construct from user defined types,
 * see namespace template function
 * \ref aworx::lib::strings::ToString "ToString".
 *
 * This class provides compiler defined copy and move constructors and assignment operators.
 * Once and object is constructed, methods #Buffer and #Length allow read access to the contents.
 *
 * <b>Null-State</b><br> \anchor CPP_STRINGS_AS_NULLSTATE
 * Objects of this class can be \e nulled which means that it is a difference whether they are
 * representing an empty string or a null pointer. As objects are immutable, this is decided
 * on construction: once an %String is null, it will remain null.
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
 * \note For an introduction into the ALib string classes see
 *       \ref aworx::lib::strings "namespace strings"
 **************************************************************************************************/
class String
{
    // #############################################################################################
    // Debug warnings
    // #############################################################################################
    public:
        #if !defined( IS_DOXYGEN_PARSER )

            ALIB_WARN_ONCE_PER_TYPE_DECL(ALIB_API, SetLengthLonger);

            #if defined(ALIB_DEBUG_STRINGS)
                void     _dbgCheck()   const;
            #endif

        #endif

    // #############################################################################################
    // Private fields
    // #############################################################################################
    protected:
    #if !defined( IS_DOXYGEN_PARSER )

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
        int               length;

    public:

    /** ############################################################################################
     * @name Constructors
     ##@{ ########################################################################################*/
     public:

        /** ****************************************************************************************
         * Constructs a \e nulled %String
         ******************************************************************************************/
        constexpr String()                      : buffer(nullptr)
                                            , length(0)                                           {}

        /** ****************************************************************************************
         * Constructs this object using the given external buffer and length of content.
         *
         *  \note The provided buffer does not need to be zero-terminated. However, there must not
         *        be any '\0' characters within the start and the given \p contentLength.
         *
         * @param buffer          The buffer to use.
         * @param contentLength   The length of the content in the given buffer.
         ******************************************************************************************/
        constexpr
        String( const char* buffer, int contentLength ) : buffer(buffer)
                                                    , length(contentLength )
        {}

        /** ****************************************************************************************
         *  Constructs this object to represent a region of another %String (respectively a region
         *  of any string object whose type implicitly constructs a temporary %String).<br>
         *  The region is adjusted to  [0 ... <em>as.Length()</em>].
         *  @param src           The src from that we will represent a region.
         *  @param regionStart   The start of the region within the given %String.
         *  @param regionLength  The length of the region within the given %String.
         ******************************************************************************************/
        String(  const String& src, int regionStart, int regionLength )
        {
            src.AdjustRegion( regionStart, regionLength );
            buffer= src.buffer + regionStart;
            length=              regionLength;
        }

        /** ****************************************************************************************
         *  Templated constructors for different types. This constructor uses some template meta
         *  programming to provide maximum flexibility to implicitly embed the data of any string
         *  type in an object of type %String.
         *
         *  This constructor accepts the following types:
         *  - <em>nullptr</em> (creates a \e nulled %String).
         *  - <em>[const] char*</em>
         *  - Classes derived from %String.
         *  - User defined (external types). See documentation of
         *    \ref aworx::lib::strings::ToString "ToString" on how to add support for implicit conversion
         *    of user defined types with this constructor.
         *  - std::string (as just one case/sample of user defined external types,
         *    provided by ALib already).
         *
         *  \note
         *  - Other than the type of parameter \p src (<em>const T&</em>) may indicate,
         *    objects of the class types named above may be provided as pointer or reference.
         *  - The source code of this method seems quite large. But the compiler will inline only
         *    the minimum necessary code depending on the type that is passed.
         *
         *  \see For more information, see
         *  \ref aworx::lib::strings "namespace documentation" and template
         *  function \ref aworx::lib::strings::ToString "ToString".
         *
         * @param src  The source of template type T to take the buffer and length from.
         ******************************************************************************************/
        template <typename T>
        constexpr
        String(const  T& src )
        : buffer(
                   // nullptr ?
                   std::is_same<T, decltype(nullptr)>::value
                   ? nullptr

                   // string literal?
                   : (    std::is_array<T>::value
                       && std::is_same<typename std::remove_extent<typename std::remove_const<typename std::remove_pointer<T>::type>::type>::type, char>::value )
                   ? (char*) &src


                   // Reference type?
                   :!std::is_pointer<T>::value
                   ? ( std::is_base_of<String, T  >::value
                       ?  ((String*) &src)->buffer
                       :  ToString<typename std::add_const<T>::type &, const char*>( (typename std::add_const<T>::type &) src )
                     )

                   // nullptr ?
                   : (*(char**)&src) == nullptr
                   ? nullptr

                   // character pointer?
                   : (std::is_same<T, char*>::value || std::is_same<T, const char*>::value)
                   ?  *((char**) &src)

                   // Pointer type
                   : std::is_convertible<T, const String*  >::value
                       ?  (*(String**) &src)->buffer
                       :  ToString<typename std::add_const<typename std::remove_pointer<T>::type>::type &, const char*>(
                                     *(typename std::add_const<typename std::remove_pointer<T>::type>::type *&)  src )
                )

        , length(
                   // nullptr ?
                   std::is_same<T, decltype(nullptr)>::value
                   ? 0

                   // string literal?
                   : (    std::is_array<T>::value
                       && std::is_same<typename std::remove_extent<typename std::remove_const<typename std::remove_pointer<T>::type>::type>::type, char>::value )
                   ? std::extent<typename std::remove_const<typename std::remove_pointer<T>::type>::type>::value- 1

                   // Reference type?
                   :!std::is_pointer<T>::value
                   ? ( std::is_base_of<String, T  >::value
                       ?  ((String*) &src)->length
                       :  ToString<typename std::add_const<T>::type &, int>( (typename std::add_const<T>::type &) src )
                     )

                   // nullptr ?
                   : (*(char**)&src) == nullptr
                   ? 0

                   // character pointer?
                   : (std::is_same<T, char*>::value || std::is_same<T, const char*>::value)
                   ?  (int) strlen(*((char**) &src))

                   // Pointer type
                   : std::is_convertible<T, const String*  >::value
                       ?  (*(String**) &src)->length
                       :  ToString<typename std::add_const<typename std::remove_pointer<T>::type>::type &, int>(
                             *(typename std::add_const<typename std::remove_pointer<T>::type>::type *&)  src )
                )
        {
            static_assert( std::is_same<T, char>::value == false,
                           "ALib String (aka aworx::String) can't be constructed with type 'char'." );
        }

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
        const char*  Buffer()          const       { return buffer;    }

        /** ****************************************************************************************
         *  Returns the length of the string we are representing.
         *
         * @return The length of the string represented by this.
         ******************************************************************************************/
        inline
        int          Length()           const       { return length;    }

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
         *                 If \c \<false\> is added to the method name, no range check is
         *                 performed.
         * @param idx      The index of the character to read.
         * @return The character at the given index, or '\0' if index out of range.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        char        CharAt( int idx )          const
        {
            if (TCheck)
                return  ( idx >= 0 && idx < length ) ? *(buffer + idx )
                                                     : '\0' ;
            #if defined(ALIB_DEBUG)
                if( idx < 0 && idx >= length )
                    dbgAStringAlibError( "Non checking version: Index out of range" );
            #endif

            return  *(buffer + idx );
        }

        /** ****************************************************************************************
         * Retrieves the first character. In case of an empty or \e nulled string, '\0' is returned.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no check for an empty
         *                 or \e nulled object is performed.
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
            #if defined(ALIB_DEBUG)
                if( length <= 0 )
                    dbgAStringAlibError( "Non checking invocation on Empy String" );
            #endif

            return  *(buffer);
        }


        /** ****************************************************************************************
         * Retrieves the last character. In case of an empty or \e nulled string, '\0' is returned.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no check for an empty
         *                 or \e nulled object is performed.
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

            #if defined(ALIB_DEBUG)
                if( length <= 0 )
                    dbgAStringAlibError( "Non checking invocation on Empy String" );
            #endif

            return  *(buffer + length - 1);
        }

        /** ****************************************************************************************
         * Reads a character at a given index.
         *
         * \attention
         *   Unlike other operator methods in the family of of ALib string classes, which are
         *   performing parameter checks (in this case a range check), this operator does
         *   <em>not</em> do a check!<br>
         *   The rationale is that in derived class %AString, which overwrites this operator
         *   returning, a reference to the character to provide write access, no reference
         *   to a character can be given if the index is out of range. This way, this method is
         *   equivalent to method #CharAt<\c false>.<br>
         *   For safe access to characters in the buffer use #CharAt (with template parameter
         *   \p TCheck being \c true).
         *
         * @param   op    The index of the character within this objects' buffer.
         * @returns If the character contained at index \p op.
         ******************************************************************************************/
         char    operator[] (int  op) const
         {
            #if defined(ALIB_DEBUG)
                if( op < 0  || op >= length )
                    dbgAStringAlibError( "Index out of bounds" );
            #endif
            return buffer[op];
         }

    /** ############################################################################################
     * @name Comparison
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Compares this with given %String.
         * \c true is returned if both are \e nulled or empty. If only one is \e nulled, \c false is returned.
         *
         * @param needle        An %String that is compared to this.
         * @param sensitivity   Determines if comparison is case sensitive (the default) or not.
         *
         * @return    \c true, if contents of this and the given %String are equal.
         ******************************************************************************************/
        inline
        bool Equals( const String& needle, enums::Case sensitivity =enums::Case::Sensitive )
        const
        {
            ALIB_STRING_DBG_CHK(this)
            if (    ( IsNull() !=  needle.IsNull() )
                 || ( length   !=  needle.length   )    )
                return false;

            if ( length == 0 )
                return true;

            return  0 == (sensitivity == enums::Case::Sensitive
                            ?   strncmp             ( buffer, needle.buffer, length )
                            :   CString::strncasecmp( buffer, needle.buffer, length ) );
        }

        /** ****************************************************************************************
         * Returns \c true, if the given %String is found at the given position.
         *
         *  \note The following rules apply
         *        - If \p pos is out of range or \p needle is \e nulled, \c false is returned.
         *          (This check only done if \p TCheck equals \c true.)
         *        - Otherwise, if the length of \p needle is 0, \c true is returned.
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c <false\> is added to the method name, no check on parameter
         *                     \p pos is performed and \p needle must not be \e nulled.
         * @param needle       The string to compare with. If is \e nulled or empty, \c true is returned.
         * @param pos          The position to search for needle.
         * @param sensitivity  Determines if comparison is case sensitive (the default) or not.
         * @return \c true if \p needle is found at the given position. False otherwise. *
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        bool ContainsAt( const String& needle, int pos, enums::Case sensitivity =enums::Case::Sensitive )
        const
        {
            int cmpLength= needle.length;
            ALIB_STRING_DBG_CHK(this)
            if ( TCheck )
            {
                if ( pos < 0 || pos + cmpLength > length || needle.IsNull () )
                    return false;
                if ( cmpLength == 0 )
                    return true;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    if( pos < 0 || pos + cmpLength > length || needle.IsNull () )
                        dbgAStringAlibError( "Non checking and index out of range" );
                    if( cmpLength == 0 )
                        dbgAStringAlibError( "Non checking and emtpy compare string" );
                #endif
            }

            return 0 == ( sensitivity == enums::Case::Sensitive
                            ?   strncmp             ( buffer + pos,  needle.buffer, cmpLength )
                            :   CString::strncasecmp( buffer + pos,  needle.buffer, cmpLength ) );
        }

        /** ****************************************************************************************
         * Returns \c true, if this string starts with the string found in parameter \p needle.
         * If \p needle is \e nulled or empty, \c true is returned.
         *
         * @param needle        The string to compare the start of this string with.
         *                      If \e nulled or empty, \c true is returned.
         * @param sensitivity   Determines if comparison is case sensitive (the default) or not.
         * @return \c true if \p needle is found at the start of this, \c false otherwise. *
         ******************************************************************************************/
        inline
        bool StartsWith( const String& needle, enums::Case sensitivity =enums::Case::Sensitive )
        const
        {
            int cmpLength= needle.length;
            if ( cmpLength > length )
                return false;
            if ( cmpLength == 0 )
                return true;
            return 0 == ( sensitivity == enums::Case::Sensitive
                            ?   strncmp             ( buffer,  needle.buffer, cmpLength )
                            :   CString::strncasecmp( buffer,  needle.buffer, cmpLength ) );
        }

        /** ****************************************************************************************
         * Returns \c true, if this string ends with the string found in parameter \p needle.
         * If \p needle is \e nulled or empty, \c true is returned.
         *
         * @param needle        The string to compare the end of this string with.
         *                      If \e nulled or empty, \c true is returned.
         * @param sensitivity   Determines if comparison is case sensitive (the default) or not.
         * @return \c true if \p needle is found at the end of this, \c false otherwise. *
         ******************************************************************************************/
        inline
        bool EndsWith( const String& needle, enums::Case sensitivity =enums::Case::Sensitive )
        const
        {
            int cmpLength= needle.length;
            int pos= length - cmpLength;
            if ( pos < 0 || pos + cmpLength > length )
                return false;
            if ( cmpLength == 0 )
                return true;
            return 0 == ( sensitivity == enums::Case::Sensitive
                    ?   strncmp             ( buffer + pos,  needle.buffer, cmpLength )
                    :   CString::strncasecmp( buffer + pos,  needle.buffer, cmpLength ) );
        }

        /** ****************************************************************************************
         * Compares this with another %String.
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c \<false\> is added to the method name, no check for \e nulled
         *                     object is performed and this string must not be of zero length
         *                     (while \p needle might be of zero length).
         * @param needle    The string to compare this string with.
         * @param sensitivity  Determines if comparison is case sensitive (the default) or not.
         *
         * @return
         *  -  0 if this and \p needle are \e nulled or if both have a length of 0 or if both
         *       share the same content
         *  - <0 if this is \e nulled and \p needle is not or if this is smaller than \p needle.
         *  - >0 if this is not \e nulled but \p needle is or if this is greater than \p needle.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        int CompareTo(  const String&  needle, enums::Case sensitivity =enums::Case::Sensitive )
        const
        {
            // check null arguments
            if (TCheck &&     IsNull() )  return  needle.IsNull() ? 0 : -1;
            if (TCheck && needle.IsNull() )  return  +1;

            // zero length ?
            int cmpLength= needle.length;
            if ( TCheck && length == 0 )  return  cmpLength == 0 ? 0 : -1;
            if (        cmpLength == 0 )  return +1;

            bool iAmShorter= length < cmpLength;
            int  shortLen=   iAmShorter ? length : cmpLength;

            int cmpVal= sensitivity == enums::Case::Sensitive ? strncmp             ( buffer, needle.buffer, shortLen )
                                                              : CString::strncasecmp( buffer, needle.buffer, shortLen );

            if ( cmpVal != 0 || length == cmpLength )
                return cmpVal;
            return iAmShorter ? -1 : 1;
        }


        /** ****************************************************************************************
         * Compares this with a region of another %String.
         *
         * @tparam TCheck         Defaults to \c true which is the normal invocation mode.
         *                        If \c \<false\> is added to the method name, no check for a \e nulled
         *                        comparison object is performed and this string must not be empty.
         *                        Furthermore, no check is performed whether the given region fits
         *                        to parameter \p needle. This also means that the default value must
         *                        not be used with <em>TCheck==\<\c false\></em>.
         * @param needle          The string to compare this string with.
         * @param sensitivity     Determines if comparison is case sensitive (the default) or not.
         * @param cmpRegionStart  The start of the region in \p needle to compare this object
         *                        with.
         * @param cmpRegionLength The length of the region in \p needle to compare this object
         *                        with.
         *                        Defaults to CString::MaxLen;
         *
         * @return
         *  -  0 if this and \p needle are \e nulled or if both have a length of 0 or if both
         *       share the same content
         *  - <0 if this is \e nulled and \p needle is not or if this is smaller than \p needle.
         *  - >0 if this is not \e nulled but \p needle is or if this is greater than \p needle.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        int CompareTo(  const String&   needle,
                        enums::Case sensitivity,
                        int         cmpRegionStart,
                        int         cmpRegionLength  =CString::MaxLen
                     )
        const
        {
            if ( TCheck )
            {
                String cmpSub( needle.buffer, 0);
                needle.AdjustRegion( cmpRegionStart, cmpRegionLength );
                cmpSub.buffer+=   cmpRegionStart;
                cmpSub.length=    cmpRegionLength;

                return CompareTo( cmpSub, sensitivity );
            }
            else
                return CompareTo<false>( String( needle.buffer + cmpRegionStart, cmpRegionLength ), sensitivity );
        }

        /** ****************************************************************************************
         * Compares a region of this object with a region of another %String.
         *
         * @tparam TCheck         Defaults to \c true which is the normal invocation mode.
         *                        If \c \<false\> is added to the method name, no check for a \e nulled
         *                        comparison object is performed and this string must not be empty.
         *                        Furthermore, no check is performed whether the given regions fit
         *                        to this object respectively the other region to the object given
         *                        with parameter \p needle.
         *                        This also means that the default value must not be used
         *                        with <em>TCheck==\<\c false\></em>.
         * @param needle          The string to compare this string with.
         * @param sensitivity     Determines if comparison is case sensitive (the default) or not.
         * @param cmpRegionStart  The start of the region in \p needle to compare this object
         *                        with.
         * @param cmpRegionLength The length of the region in \p needle to compare this object
         *                        with.
         * @param regionStart     The start of the region in this object to compare with
         * @param regionLength   The length of the region in this object to compare with.
         *                        Defaults to CString::MaxLen;
         *
         * @return
         *  -  0 if this and \p needle are \e nulled or if both have a length of 0 or if both
         *       share the same content
         *  - <0 if this is \e nulled and \p needle is not or if this is smaller than \p needle.
         *  - >0 if this is not \e nulled but \p needle is or if this is greater than \p needle.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        int CompareTo(  const String&   needle,
                        enums::Case sensitivity,
                        int         cmpRegionStart,
                        int         cmpRegionLength,
                        int         regionStart,
                        int         regionLength    =CString::MaxLen
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
                return String( buffer + regionStart, regionLength ).CompareTo( cmpSub, sensitivity );
            }
            else
                return String( buffer + regionStart, regionLength )
                        .CompareTo<false>( String( needle.buffer + cmpRegionStart, cmpRegionLength ),
                                           sensitivity );

        }

        /**
         * Uses method #CompareTo with parameter \p op to perform a lexical comparison.
         *
         * @param op The string to compare this string with.
         * @returns \c true if this is lexically smaler then \p op, \c false otherwise.
         */
        bool     operator<  (const String& op) const { return CompareTo( op ) <  0 ;  }

        /**
         * Uses method #CompareTo with parameter \p op to perform a lexical comparison.
         *
         * @param op The string to compare this string with.
         * @returns \c true if this is lexically greater then \p op, \c false otherwise.
         */
        bool     operator>  (const String& op) const { return CompareTo( op ) >  0 ;  }

        /**
         * Uses method #Equals with parameter \p op to test on equality.
         *
         * @param op The string to compare this string with.
         * @returns \c true if the strings are equal, \c false otherwise.
         */
        bool     operator== (const String& op) const { return Equals( op );  }

        /**
         * Uses method #Equals with parameter \p op to test on equality.
         *
         * @param op The string to compare this string with.
         * @returns \c true if the strings are equal, \c false otherwise.
         */
        bool     operator!= (const String& op) const { return !Equals( op ) != 0 ;  }

    /** ############################################################################################
     * @name Search
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         *  Searches a character.
         *
         * @param needle  The character to search for.
         * @return  -1 if the character \p needle is not found.
         *           Otherwise the index of first occurrence.
         ******************************************************************************************/
        inline
        int            IndexOf( char needle ) const
        {
            ALIB_STRING_DBG_CHK(this)
            const char* result=      (const char*) memchr( buffer, needle, length );

            return result != nullptr ? (int) ( result -  buffer )
                                     : -1;
        }

        /** ****************************************************************************************
         * Searches a character starting from a given position.
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c \<false\> is added to the method name, no range check is
         *                     performed.
         * @param needle       The character to search for.
         * @param regionStart  The index in this to start searching the character.
         *
         * @return  -1 if the character \p needle is not found.
         *          Otherwise the index of its first occurrence.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        int            IndexOf( char needle, int regionStart ) const
        {
            ALIB_STRING_DBG_CHK(this)

            if ( TCheck )
            {
                // adjust range, if empty return -1
                     if ( regionStart <  0      )  regionStart= 0;
                else if ( regionStart >= length )  return -1;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    if( regionStart < 0 || regionStart >= length )
                        dbgAStringAlibError( "Non checking and index out of range" );
                #endif
            }

            const char* result=  (const char*) memchr( buffer + regionStart, needle, length - regionStart );

            return result != nullptr ? (int) (result -  buffer)
                                     : -1;
        }

        /** ****************************************************************************************
         * Searches a character within a region of this.
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c \<false\> is added to the method name, no range check is
         *                     performed.
         * @param needle       The character to search for.
         * @param regionStart  The start of the region to search the character in.
         * @param regionLength The length of the region to search the character in.
         *
         * @return  -1 if the character \p needle is not found.
         *          Otherwise the index of its first occurrence.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        int            IndexOf( char needle, int regionStart, int regionLength ) const
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
                #if defined(ALIB_DEBUG)
                    int rs= regionStart;
                    int rl= regionLength;
                    if (    AdjustRegion( rs, rl )
                         || rs != regionStart
                         || rl != regionLength )
                        dbgAStringAlibError( "Non checking and region out of range or empty" );
                #endif
            }

            const char* result=      (const char*) memchr( buffer + regionStart, needle, regionLength );

            return result != nullptr ? (int) ( result -  buffer )
                                     : -1;
        }

        /** ****************************************************************************************
         * Searches a character starting backwards from the end or a given start index.
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c \<false\> is added to the method name, no range check is
         *                     performed. Also, in this case, parameter startIndex must be provided.
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
        int            LastIndexOf( char needle, int startIndex= CString::MaxLen ) const
        {
            ALIB_STRING_DBG_CHK(this)

            if ( TCheck )
            {
                // adjust range, if empty return -1
                     if ( startIndex <  0      )   return -1;
                else if ( startIndex >= length )   startIndex= length-1;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    if( startIndex < 0 || startIndex >= length )
                        dbgAStringAlibError( "Non checking and index out of range" );
                #endif
            }

            while( startIndex >= 0 && buffer[ startIndex ] != needle )
                startIndex--;

            return startIndex;
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         *
         * \note In derived class \b %TString (aka TString), a  faster version (using
         *       \e std::strpbrk() respectively \e std::strspn()) is available. So, if performance
         *       is important, it might be advisable to copy this \b %String (and the needles) to a
         *       terminatable buffer.
         *
         * This method searches forwards. For backwards search, see #LastIndexOf.
         *
         * @tparam TCheck   Defaults to \c true which is the normal invocation mode.
         *                  If \c <false\> is added to the method name, no parameter checks are
         *                  performed and the needles must not be empty.
         * @param needles   Pointer to a zero terminated set of characters to be taken into account.
         * @param inclusion Denotes whether the search returns the first index that holds a value
         *                  that is included or that is not excluded in the set of needle
         *                  characters.
         * @param startIdx  The index to start the search at. If the given value is less than 0,
         *                  it is set to 0. If it exceeds the length of the string, the length of
         *                  the string is returned.
         *                  Defaults to 0.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        int            IndexOfAny( const String& needles, enums::Inclusion inclusion, int startIdx= 0 )
        const
        {
            if (TCheck)
            {
                if ( startIdx < 0       ) startIdx= 0;
                if ( startIdx >= length ) return   -1;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    if (    startIdx < 0
                         || startIdx >= length
                         || needles.Length() == 0    )
                        dbgAStringAlibError( "Non checking and illegal parameters" );
                #endif
            }


            int idx= CString::IndexOfAny(  buffer + startIdx,  length - startIdx,
                                           needles.Buffer(),
                                           needles.Length(),
                                           inclusion
                                        );

            return idx == -1 ? -1 : startIdx + idx;
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         *
         * This method searches backwards starting at the given index. For forwards search, see
         * #IndexOf.
         *
         * @param needles    Pointer to a zero terminated set of characters to be searched for.
         * @param inclusion  Denotes whether the search returns the first index that holds a value
         *                   that is included or that is not excluded in the set of needle
         *                   characters.
         * @param startIdx   The index to start the search at. The value is cropped to be in
         *                   the bounds of 0 and the length of this object minus one.
         *                   Defaults to maximum integer value.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        int    LastIndexOfAny( const String& needles, enums::Inclusion inclusion, int startIdx= CString::MaxLen )
        const
        {
            if (TCheck)
            {
                if ( startIdx < 0       ) return -1;
                if ( startIdx >= length ) startIdx=  length - 1;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    if (    startIdx < 0
                         || startIdx >= length
                         || needles.Length() == 0    )
                        dbgAStringAlibError( "Non checking and illegal parameters" );
                #endif
            }

            return  CString::LastIndexOfAny(         Buffer(), startIdx,
                                                 needles.Buffer(), needles.Length(),
                                                 inclusion                               );
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
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c \<false\> is added to the method name, parameter \p startIdx
         *                     must be valid and \p needle must not be empty.
         * @param needle       The string to search for.
         * @param startIdx     The index to start the search at. Optional and defaults to 0.
         * @param sensitivity  Case sensitivity of the comparison.
         *                     Optional and defaults to \b Case::Sensitive.
         *
         * @return    -1 if the string is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        int            IndexOfAS( const String&   needle,
                                  int         startIdx= 0,
                                  enums::Case sensitivity=  enums::Case::Sensitive )
        const
        {
            int         nLen=   needle.Length();
            if (TCheck)
            {
                if ( startIdx < 0 )                startIdx= 0;
                if ( startIdx + nLen > length )    return -1;
                if ( needle.Length() == 0  )       return  startIdx;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    if (    startIdx < 0
                         || startIdx >= length
                         || nLen == 0    )
                        dbgAStringAlibError( "Non checking and illegal parameters" );
                #endif
            }

            const char*  buf=    buffer + startIdx;
            const char*  bufEnd= buf + length - nLen + 1;
            const char* nBuf=    needle.Buffer();
            const char* nBufEnd= nBuf + nLen;

            while ( buf != bufEnd )
            {
                const char* b=  buf;
                const char* n= nBuf;
                if ( sensitivity == enums::Case::Sensitive )
                {
                    while ( *(b++) == *(n++) )
                        if( n == nBufEnd )
                            return (int) (buf - buffer);
                }
                else
                {
                    while ( tolower(*(b++)) == tolower(*(n++)) )
                        if( n == nBufEnd )
                            return (int) (buf - buffer);
                }
                buf++;
            }
            return -1;
        }

    /** ############################################################################################
     * @name Conversion
     ##@{ ########################################################################################*/

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
         *   This, by default, is done in \ref aworx::lib::ALIB::Init "ALIB::Init".
         *
         * @param dest          The destination buffer.
         * @param destCapacity  The size of the destination buffer. Has to be equal or greater than
         *                      the provided region length plus one for termination.
         * @param regionStart   The start of the region in this to convert.
         *                      Optional and defaults to 0.
         * @param regionLength  The maximum length of the region in this to convert.
         *                      Optional and defaults to CString::MaxLen
         *
         * @return    On success, the length of converted destination string. -1 for conversion
         *            failure, -2 if destination buffer was too small.
         ******************************************************************************************/
        ALIB_API int  ToWString( wchar_t*    dest,             int  destCapacity,
                                 int         regionStart =0,   int  regionLength   =CString::MaxLen ) const;

    /** ############################################################################################
     * @name Helper methods
     ##@{ ########################################################################################*/
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
        bool AdjustRegion( int& regionStart, int& regionLength ) const
        {
            return CString::AdjustRegion( length, regionStart, regionLength );
        }

}; // class %String

}} // namespace lib::strings


/** Type alias name in namespace #aworx. */
using     String    =       aworx::lib::strings::String;

// #################################################################################################
// aworx namespace string singletons
// #################################################################################################
/**
 * A constant \e nulled ALib string.
 * E.g. useful to provide as parameter to methods or to use as default value for method
 * parameters.
 * @return A constant \e nulled ALib string.
 */
constexpr lib::strings::String   NullString;

/**
 * A constant empty (but not \e nulled) ALib string
 * E.g. useful to provide as parameter to methods or to use as default value for method
 * parameters.
 * @return A constant empty (but not \e nulled) ALib string.
 */
constexpr lib::strings::String   EmptyString {"", 0};


} // namespace aworx


#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
#endif // HPP_ALIB_STRINGS_AS
