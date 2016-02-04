// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_AWORX_LIB_ALIB) || defined(HPP_AWORX_LIB_STRINGS_ASTERMINATABLE)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_LIB_STRINGS_ASTERMINATABLE
#define HPP_AWORX_LIB_STRINGS_ASTERMINATABLE 1


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
 *
 * @addtogroup GrpALibStringsMacros
 * @{ \def  ALIB_STRING_DBG_UNTERMINATE
 *  This macro serves for debugging the development (and potentially the use) of
 *  derived classes, eg. class \ref aworx::lib::strings::ASAlloc "AString".
 *  It is active only when compiler symbol \ref ALIB_DEBUG_STRINGS is set. When active,
 *  whenever the contents of an %AString instance is modified, the buffer is explicitly
 *  "unterminated" by writing a value of '\\1' at the termination position and the state is
 *  stored in field
 *  \ref aworx::lib::strings::ASTerminatable::debugIsTerminated "debugIsTerminated"
 *  \ref aworx::lib::strings::ASTerminatable::_dbgCheck "_dbgCheck".<br>
 *  Doing this, will also hint to buffers that reside in non-writable memory, hence
 *  it will hint to buffers that may not be used with this class.
 * @}
 *
 */

// do not indent this, for the sake of doxygen formatting
//--- debug mode ---
#if defined(ALIB_DEBUG_STRINGS)

#define  ALIB_STRING_DBG_UNTERMINATE( astring, offset )              \
{                                                                    \
    if ( (astring).Buffer() != nullptr )                             \
        (astring).VBuffer()[ (astring).Length()  + offset ]= '\1';   \
    ((ASTerminatable&)(astring)).debugIsTerminated= 0;               \
}

//--- normal mode ---
#else

#define  ALIB_STRING_DBG_UNTERMINATE(astring, offset)

#endif


namespace aworx {
namespace           lib {
namespace                   strings {

/** ************************************************************************************************
 * Template (meta programming) struct to determine if an arbitrary string type is terminatable or
 * not.
 * The 'default implementation' inherits from std::false_type
 *
 * For all user defined string types (from an ALib perspective external types), which
 * - implement  template functions
 *   \ref aworx::lib::strings::ToAS(const TString) "ToAS(const TString)"
 *   to be able to serve as a string argument for implicit construction of class
 *   \ref aworx::lib::strings::AS "AS"
 * - and which do not provide a terminated buffer in that <em>ToAS</em> method
 * - and which should in addition be suitable to serve as string argument to implicit constructor
 *   of class  \ref aworx::lib::strings::ASTerminatable "ASTerminatable"
 *
 * a specialization of this struct (that simply is derived from <em>std::true_type</em>)
 * has to be provided.
 *
 * When this is done, the capacity for the termination character '\0' has to be available
 * in the buffer that is passed in function
 * \ref aworx::lib::strings::ToAS(const TString) "ToAS( const TString )".
 * In other words, their buffer needs to be writable and at least one character longer than
 * their content length.
 *
 * \note
 *  If (user defined) objects are terminated already when passed to the constructor of
 *  ASTerminatable, then this template is <b>not</b> needed to be defined.<br>
 *  For example, the implementation of method <em>ToAS</em> for type <em>std::string</em>
 *  returns <em>std::string::c_str()</em>. This way, the string returned is well terminated and
 *  there is no need to partially specialize this struct for type <em>std::string</em>.
 **************************************************************************************************/
template<typename Type> struct  IsTerminatable : public std::false_type { };


/** ************************************************************************************************
 * This class specializes class
 * \ref aworx::lib::strings::AS "AS" to represent zero terminated or zero terminatable strings.
 * The advantage of zero terminated strings are that certain algorithms might be implemented in
 * a more efficiently. Hence, various functions and methods of ALib require a const reference
 * to an object of this type instead to an object of class \b %AS.
 *
 * \note This class \b %ASTerminatable, when used in source code as well as in documentations, is
 *       mostly referred to using the synonym '<b>%TString</b>'. For more information about the
 *       synonymous names of ALib string classes, refer to
 *       \ref alib_namespace_strings_class_overview "String Classes Overview" and
 *       \ref CPP_AWORX_NS_SHORTCUTS "Type Shortcuts in the aworx Namespace".
 *
 * <b>Implicit construction</b><p>
 * This class hides its parents' constructors and re-implements the template meta
 * programming based "all-for-one" constructor
 * \ref aworx::lib::strings::AS::AS(const  T&) "AS(const  T&)" by introducing
 * \ref aworx::lib::strings::ASTerminatable::ASTerminatable(const  T&) "ASTerminatable(const  T&)".
 *
 * As it is not possible to implement compile time assertions for the save provision of
 * terminatable types (without taking serious restrictions into account), this constructor
 * performs a run time check (in debug compilations of ALib).<br>
 * It is checked whether
 * - the string type passed is already terminated or
 * - can be terminated because a) the buffer reserved capacity for the termination value and b)
 *   the buffer is writable.
 *
 * The second check is done only if the first did not apply and is performed using partially
 * implemented template struct
 * \ref aworx::lib::strings::IsTerminatable "ISTerminatable". Consult this struct for information
 * about how to enable external (user defined) string types to be used as parameters to implicitly
 * construct objects of this class.
 *
 *  \note
 *   While the good news is that C++ string literals, any zero terminated <em>char*</em> and
 *   objects of type <em>std::strings</em> or ALib's \b %AString,
 *   are well suited to implicitly construct respectively directly serve as objects of this class,
 *   objects of type
 *   \ref aworx::lib::strings::AS "AS" itself and espcially of type
 *   \ref aworx::lib::strings::ASSubstring "ASSubstring" are not.
 *   Therefore the latter are accepted only if they are terminated already.
 *   But obviously, this is especially unlikely for objects of type
 *   \ref aworx::lib::strings::ASSubstring "ASSubstring".
 *
 *  \note
 *   Therefore, for example to pass a <em>Substring</em>
 *   as a parameter to functions accepting only terminatable strings, it is possible to
 *   wrap them into temporary objects of type
 *   \ref aworx::lib::strings::ASAlloc "AString" or, if maximum size is known at compile time,
 *   of type
 *   \ref aworx::lib::strings::ASPreAlloc "ASPreAlloc".
 *   Of-course, a performance drawback (for creating the temporary copy of the contents) has to
 *   be taken into account.
 *
 *  \note
 *   Alternatively, class \b %Substring and class \b %AS provide some useful
 *   implementations of slightly slower versions of some of the methods introduced this class.
 *   It has to be considered case by case which option is the best in respect to performance and
 *   memory use.
 *
 * <b>Constant Nature</b><p>
 * Same as parent class
 * \ref aworx::lib::strings::AS "AS", this class is not copying the data of the provided
 * source. It is designed preliminary to offer a fast but convenient (by implicit conversion)
 * type for function parameters that require terminated cstring buffers. As with parent class \b %AS,
 * the life-time of objects of this class is considerably short.<br>
 * Only derived class \ref aworx::lib::strings::ASAlloc "AString" and its different
 * further specializations will copy the buffer and always include space for the termination
 * character in their buffers' capacity.
 *
 * <b>Parsing Numbers</b><p>
 * This class provides methods for parsing integer and floating point data.
 * For implementation performance reasons, those are <em>not</em> provided by parent class \b %AS
 * which does not guarantee zero terminated strings. If parsing has to be done on non-zero
 * terminated string data, consider using a slightly slower variant of the parsing methods which
 * are found in class \ref aworx::lib::strings::ASSubstring "ASSubstring".<br>
 * It is rather more efficient, to instantiate a local Substring object that just wraps an
 * unterminated string of type \b %AS and use its parsing interface, than copying the
 * unterminated data into a terminatable string variant (e.g. \b %AString) and to use the
 * interface provided herein.
 **************************************************************************************************/
class ASTerminatable : public AS
{
    /** ############################################################################################
     * @name Debug methods
     ##@{ ########################################################################################*/
    public:
    #if defined(ALIB_DEBUG_STRINGS)
        /** ****************************************************************************************
         * Validates this instance. This method is available only if \ref ALIB_DEBUG_STRINGS
         * is defined. Invocations to this method should be performed using macro
         * \ref ALIB_STRING_DBG_CHK.
         ******************************************************************************************/
         void            _dbgCheck()   const;

        /**
         * This field serves for debugging the development (and potentially the use) of
         * derived classes, eg. class \ref aworx::lib::strings::ASAlloc "AString".
         * It is available only when compiler symbol \ref ALIB_DEBUG_STRINGS is set. When active,
         * whenever the contents of an \b %AString instance is modified, the buffer is explicitly
         * "unterminated" by writing a value of '\\1' at the termination position and the state is
         * stored in this field .<br>
         * To keep the constructor <em>constexpr</em>, it is -1 (undetermined) after construction.
         * \see Macro \ref ALIB_STRING_DBG_UNTERMINATE and method #Terminate
         *
         */
        int              debugIsTerminated                                                      =-1;
    #endif


    /** ############################################################################################
     * @name Constructor and Assignment
     ##@{ ########################################################################################*/
    protected:

        /** ****************************************************************************************
         * Constructs this object using the given external buffer and length of content.
         *
         * \note
         *   This constructor is protected to avoid the creation of objects with non-terminatable
         *   types.
         *
         * @param buffer          The buffer to use.
         * @param contentLength   The length of the content in the given buffer.
         ******************************************************************************************/
        constexpr
        ASTerminatable( const char* buffer, int contentLength )
        : AS( buffer, contentLength )
        {}


    public:

        /** ****************************************************************************************
         * Default constructor creating a \e nulled \b %ASTerminatable.
         ******************************************************************************************/
        constexpr
        ASTerminatable()
        : AS()
        {}

        /** ****************************************************************************************
         *  This constructor overloads the powerful templated constructor
         *  \ref aworx::lib::strings::AS::AS(const T&) "AS::AS(const T&)".
         *  In addition to invoking that, it is asserted that the given value is terminated or
         *  type T is terminatable. For more information see this classes' general description.
         *
         * @param src  The string to represent by this object.
         ******************************************************************************************/
        template <typename T>
        ASTerminatable(const  T& src )
        : AS(src)
        {
            ALIB_ASSERT_ERROR(      IsTerminatable  < typename std::remove_cv
                                                        < typename std::remove_pointer<T>::type>::type>::value
                                    ||  IsNull()
                                    ||  buffer[length] == '\0'
                                  ,"Error unterminated and unterminatable object given" );
        }


    /** ############################################################################################
     * @name General Interface
     ##@{ ########################################################################################*/
    public:
        /** ****************************************************************************************
         * Reads a character at a given index.<br> Overwrites
         * \ref aworx::lib::strings::AS::operator[] "AS::operator[]" to change the debug assertion
         * to allow inclusion of the termination character.
         *
         * \attention
         *   No parameter check is performed (other than an assertions in debug-compilation of ALib).
         *   See \ref aworx::lib::strings::AS::operator[] "AS::operator[]" for details.
         *
         * @param   op    The index of the character within this objects' buffer.
         * @returns If the character contained at index \p op.
         ******************************************************************************************/
         char    operator[] (int  op) const
         {
            ALIB_ASSERT_ERROR( op >= 0  && op <= length , "Index out of bounds" );
            return buffer[op];
         }

        /** ****************************************************************************************
         * Checks if this objects' buffer is terminated and - if not - terminates it by writing
         * '\0' into the first character of the buffer after the represented string
         * (precisely into <em>buffer[ length ]</em>).
         *
         * \note
         *   When compiler symbol \ref ALIB_DEBUG_STRINGS is set, the state of debug field
         *   #debugIsTerminated gets set to '1'.
         *
         *  \see #ToCString, #operator const char*().
         ******************************************************************************************/
        inline
        void Terminate()    const
        {
            ALIB_ASSERT_ERROR(  buffer != nullptr
                                  ,"Can't terminated nulled object." );

            if (buffer[ length ] != '\0' )
            {
                vbuffer[ length ]= '\0';

                #if defined(ALIB_DEBUG_STRINGS)
                    // cast to non-const...hey its for good 8-)
                    ((ASTerminatable*)this)->debugIsTerminated= 1;
                #endif
            }
        }


    /** ############################################################################################
     * @name Character and String Search
     ##@{ ########################################################################################*/

        using AS::IndexOf;

        /** ****************************************************************************************
         *  Search the given terminatable string in this object.
         *
         * \note
         *   Parameter \p needle is required to be terminated or terminatable, the same as this
         *   object is.
         *   For non-terminatable string types (e.g. those of type
         *   \ref aworx::lib::strings::ASSubstring "ASSubstring"), a less performant implementation
         *   of this method is available through class \b %AS with:
         *   \ref aworx::lib::strings::AS::IndexOf "IndexOf".<br>
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c <false\> is added to the method name, no parameter checks are
         *                     performed and the needle must not be empty.
         * @param needle       The AS to search for.
         * @param startIdx     The index to start the search at. Optional and defaults to 0.
         * @param sensitivity  Case sensitivity of the comparison.
         *                     Optional and defaults to Case::Sensitive.
         *
         * @return    -1 if the string is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        int    IndexOf( const ASTerminatable&  needle,
                              int              startIdx= 0,
                              enums::Case      sensitivity=  enums::Case::Sensitive )
        const
        {
            if (TCheck)
            {
                if ( startIdx < 0 )                           startIdx= 0;
                if ( startIdx + needle.Length() > length )    return -1;
                if ( needle.Length() == 0  )                  return  startIdx;
            }
            else
            {
                #if defined(ALIB_DEBUG)
                    if (    startIdx < 0
                         || startIdx >= length
                         || needle.Length() == 0    )
                        dbgAStringAlibError( "Non checking and illegal parameters" );
                #endif
            }


            #if defined (__GLIBCXX__)
                const char* foundAt= sensitivity == enums::Case::Sensitive
                     ? strstr    ( ToCString() + startIdx, needle.ToCString() )
                     : strcasestr( ToCString() + startIdx, needle.ToCString() );
                return  foundAt != nullptr ?  foundAt - buffer  :   -1;
            #else
                if ( sensitivity == enums::Case::Sensitive )
                {
                    const char* foundAt=  strstr( ToCString() + startIdx, needle.ToCString() );
                    return  foundAt != nullptr ?  (int) (foundAt - buffer)  :   -1;
                }
                else
                    // there is no strcasestr in windows, we use the slower AS version, non-checking
                    return IndexOfAS<false>( needle, startIdx , enums::Case::Ignore );
            #endif
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         *
         * This method searches forwards. For backwards search, see
         * \ref aworx::lib::strings::AS::LastIndexOfAny "AS::LastIndexOfAny".
         *
         *
         * \note This method reimplements method
         *       \ref aworx::lib::strings::AS::IndexOf "AS::IndexOf" of parent class.
         *       This implementation however needs (beside the fact that this is a zero terminatable)
         *       a zero-terminatable string for the needles.
         *       If no zero-terminatable needles are available, parent method accepting non-zero
         *       terminated needles needs to be invoked. This is possible, for example
         *       by writing e.g. <em>mystring.AS::IndexOf()</em>.
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
        int            IndexOfAny( const ASTerminatable& needles, enums::Inclusion inclusion, int startIdx= 0 )
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


            if ( inclusion == enums::Inclusion::Include )
            {
                const char* res=  std::strpbrk( ToCString() + startIdx, needles.ToCString() );
                return  res == nullptr ? -1 : (int) (res - buffer);
            }
            else
            {
                const char* haystack= ToCString() + startIdx;
                int idx= (int) std::strspn ( haystack, needles.ToCString() );
                return *( haystack + idx ) == '\0' ? -1 : startIdx + idx;
            }
        }


    /** ############################################################################################
     * @name Conversion
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Cast operator to <em>const char*</em>. Invokes and returns result of #ToCString.
         *
         * \note Casting an instance with <em>(const char*)</em> is the same as invoking
         *       method #ToCString on that instance. The operator is provided as an alias
         *       and it is a matter of taste which of them to use.
         * <p>
         * \note This operator is marked explicit. Although implicit conversion would be quite
         *       convenient, the need for adding the cast explicitly should be helpful in
         *       understanding the structure of the code and leads to more predictable
         *       compiler warnings and invocations of overloaded methods.
         ******************************************************************************************/
        explicit
        inline
        operator const char*()
        {
            return ToCString();
        }

        /** ****************************************************************************************
         * This instances' buffer will be terminated (if not already) and returned.
         * If this object is \e nulled, a pointer to an empty cstring is returned.
         * This allows to omit explicit checks for \e nulled objects, in the frequent case that
         * no difference should be made in the processing of a \e nulled or a not \e nulled, but
         * empty object.
         *
         * \note
         *   If used within loops, it is advisable to use a combination of #Terminate (before
         *   the loop) and #Buffer (inside the loop) to avoid the overhead for a repeated
         *   termination check.
         *
         * @return The internal, now zero terminated buffer.
         ******************************************************************************************/
        inline
        const char* ToCString()         const
        {
            if ( buffer == nullptr )
                return "";

            Terminate();
            return buffer;
        }

        /** ****************************************************************************************
         * Reads a 64-bit integer from this object at the given position.
         * The output parameter is set to point to the first character that is not a number.
         * If no number is found at the given index, zero is returned and the output parameter is
         * set to the original start index.
         *
         * Leading whitespace characters are ignored. However, if after leading whitespaces no
         * numbers were found, then the output parameter is set to the original start index.
         * This way, the optionally provided index can be used to check if parsing succeeded.
         *
         * \note For converting non-zero terminated strings, see class
         *       \ref aworx::lib::strings::ASSubstring "ASSubstring".
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to 0.
         * @param[out] newIdx  Optional output variable that will point to the first character
         *                     in this string after the float number that was parsed.
         *                     If parsing fails, it will be set to the value of parameter startIdx.
         *                     Therefore, this parameter can be used to check if a value was found.
         * @param whitespaces  White space characters used to trim the substring at the front
         *                     before reading the value.
         *                     Defaults to nullptr, which causes the method to use
         *                     \ref aworx::lib::strings::DefaultWhitespaces.
         *
         * @return  The parsed value. In addition, the parameter \p newIdx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        ALIB_API
        int64_t        ToLong( int   startIdx= 0,  int* newIdx= nullptr,
                               const ASTerminatable*   whitespaces   = nullptr ) const;

        /** ****************************************************************************************
         * Reads a 32-bit integer from this object at the given position.
         * The output parameter is set to point to the first character that is not a number.
         * If no number is found at the given index, zero is returned and the output parameter is
         * set to the original start index.
         *
         * Leading whitespace characters are ignored. However, if after leading whitespaces no
         * numbers were found, then the output parameter is set to the original start index.
         * This way, the optionally provided index can be used to check if parsing succeeded.
         *
         * \note For converting non-zero terminated strings, see class
         *       \ref aworx::lib::strings::ASSubstring "ASSubstring".
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     If parsing fails, it will be set to the value of parameter startIdx.
         * @param whitespaces  White space characters used to trim the substring at the front
         *                     before reading the value.
         *                     Defaults to nullptr, which causes the method to use
         *                     \ref aworx::lib::strings::DefaultWhitespaces.
         *
         * @return  The parsed value. In addition, the output parameter \p newIdx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        inline
        int32_t        ToInt( int  startIdx= 0,  int* newIdx= nullptr,
                              const ASTerminatable*   whitespaces = nullptr  ) const
        {
            return (int32_t) ToLong( startIdx, newIdx, whitespaces );
        }

        /** ****************************************************************************************
         * Reads a floating point value from this object at the given position using the
         * class \ref aworx::lib::strings::NumberFormat "NumberFormat".
         * If no object of this type is provided with optional parameter \p numberFormat,
         * the static default object found in
         * \ref aworx::lib::strings::NumberFormat::Global "NumberFormat::Global"
         * is used.
         *
         * Leading whitespace characters as defined in optional parameter \p whitespaces, are
         * ignored.
         *
         * The optional output parameter \p newIdx is set to point to the first character that does
         * not belong to the number. If no number is found at the given index (respectively at
         * the first non-whitespace character at or after the given index), zero is returned and
         * the output parameter is set to the original start index.
         *
         * \note For converting non-zero terminated strings, see class
         *       \ref aworx::lib::strings::ASSubstring "ASSubstring".
         *
         * @param startIdx     The start index from where the float value is tried to be read.
         *                     Defaults to 0.
         * @param[out] newIdx  Optional output variable that will point to the first character
         *                     after the float number that was parsed.
         *                     If parsing fails, it will be set to the value of parameter startIdx.
         *                     Therefore, this parameter can be used to check if a value was found.
         * @param numberFormat The object performing the conversion and defines the output format.
         *                     Optional and defaults to nullptr.
         * @param whitespaces  White space characters used to trim the substring at the front
         *                     before reading the value.
         *                     Defaults to nullptr, which causes the method to use
         *                     \ref aworx::lib::strings::DefaultWhitespaces.
         *
         * @return  The parsed value. In addition, on success, the output parameter \p newIdx is set
         *          to point to the first character behind any found float number.
         ******************************************************************************************/
        ALIB_API
        double         ToFloat( int                     startIdx        = 0,
                                int*                    newIdx          = nullptr,
                                strings::NumberFormat*  numberFormat    = nullptr,
                                const ASTerminatable*   whitespaces     = nullptr    )   const;

}; // class ASTerminatable



}}} // namespace aworx::lib::strings

#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
#endif // HPP_AWORX_LIB_STRINGS_ASTERMINATABLE
