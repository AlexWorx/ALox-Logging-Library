// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include guard
#ifndef HPP_ALIB_STRINGS_TSTRING
#define HPP_ALIB_STRINGS_TSTRING 1

// to preserve the right order, we are not includable directly from outside.
#if !defined(ALIB_PROPER_INCLUSION)
    #error "include 'alib/alib.hpp' or 'alib/alib_strings.hpp' instead of this header"
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
 *
 * @addtogroup GrpALibStringsMacros
 * @{ \def  ALIB_STRING_DBG_UNTERMINATE
 * This macro serves for debugging the development (and potentially the use) of
 * derived classes, eg. class \ref aworx::lib::strings::AString "AString".
 * It is active only when compiler symbol \ref ALIB_DEBUG_STRINGS is \c true. When active,
 * whenever the contents of an %AString instance is modified, the buffer is explicitly
 * "unterminated" by writing a value of '\\1' at the termination position and the state is
 * stored in field
 * \ref aworx::lib::strings::TString::debugIsTerminated "debugIsTerminated"
 * \ref aworx::lib::strings::TString::_dbgCheck "_dbgCheck".<br>
 * Doing this, will also hint to buffers that reside in non-writable memory, hence
 * it will hint to buffers that may not be used with this class.
 *
 * The macro is active when conditional compilation symbol \ref ALIB_DEBUG_STRINGS_ON is set.
 * In case \b ALIB_DEBUG_STRINGS_ON it is not set, but symbol \ref ALIB_AVOID_ANALYZER_WARNINGS_ON
 * is, still the string is un-terminated, but no checks are are performed.
 * @}
 *
 */

// do not indent this, for the sake of doxygen formatting
//--- debug mode ---
#if ALIB_DEBUG_STRINGS

    #define  ALIB_STRING_DBG_UNTERMINATE( astring, offset )              \
    {                                                                    \
        if ( (astring).Buffer() != nullptr )                             \
            (astring).VBuffer()[ (astring).Length()  + offset ]= '\1';   \
        static_cast<TString&>(astring).debugIsTerminated= 0;                      \
    }

//--- suppress analyzer warnings by writing the value ---
#elif  ALIB_AVOID_ANALYZER_WARNINGS

    #define  ALIB_STRING_DBG_UNTERMINATE( astring, offset )              \
    {                                                                    \
        if ( (astring).Buffer() != nullptr )                             \
            (astring).VBuffer()[ (astring).Length()  + offset ]= '\2';   \
    }

#else

//--- normal mode: do nothing ---
#define  ALIB_STRING_DBG_UNTERMINATE(astring, offset)

#endif


namespace aworx { namespace lib { namespace strings
{
// #################################################################################################
// forward declarations
// #################################################################################################
class String;
class NumberFormat;

/** ************************************************************************************************
 * Template (meta programming) struct to determine if an arbitrary string type is terminatable or
 * not.
 * The 'default implementation' inherits from std::false_type
 *
 * For all user defined string types (from an \b %ALib perspective external types), which
 * - implement template stuct
 *   \ref aworx::lib::strings::T_String "T_String"
 *   to be able to serve as a string argument for implicit construction of class
 *   \ref aworx::lib::strings::String "String"
 * - and which do not provide a terminated buffer in that <em>ToString</em> method
 * - and which should in addition be suitable to serve as string argument to implicit constructor
 *   of class  \ref aworx::lib::strings::TString "TString"
 *
 * a specialization of this struct (that simply is derived from <em>std::true_type</em>)
 * has to be provided.
 *
 * When this is done, the capacity for the termination character '\0' has to be available
 * in the buffer that is passed in method
 * \ref aworx::lib::strings::T_String::Buffer "T_String::Buffer".
 * In other words, their buffer needs to be writable and at least one character longer than
 * their content length.
 *
 * \note
 *  If (user defined) objects are terminated already when passed to the constructor of
 *  TString, then this template is <b>not</b> needed to be defined.<br>
 *  For example, the implementation of method <em>ToString</em> for type <em>std::string</em>
 *  returns <em>std::string::c_str()</em>. This way, the string returned is well terminated and
 *  there is no need to partially specialize this struct for type <em>std::string</em>.
 **************************************************************************************************/
template<typename Type> struct  T_IsTerminatable : public std::false_type { };


/** ************************************************************************************************
 * This class specializes class
 * \ref aworx::lib::strings::String "String" to represent zero terminated or more precisely
 * zero \e terminatable strings.
 * Zero terminated strings are especially needed when string data has to be passed to system
 * functions. Also, some efficient algorithms (platform dependent and mostly written in assembly
 * language) exist.  Hence, various functions and methods of \b %ALib require a const reference
 * to an object of this type \b %TString instead to an object of class \b %String.
 *
 * <b>Implicit construction</b><p>
 * This class hides its parents' constructors and re-implements the template meta
 * programming based "all-for-one" constructor
 * \ref aworx::lib::strings::String::String(const TStringLike&) "String(const TStringLike&)" by introducing
 * \ref aworx::lib::strings::TString::TString(const TTerminatable&) "TString(const TTerminatable&)".
 *
 * As it is not possible to implement compile time assertions for the save provision of
 * terminatable types (without taking serious restrictions into account), this constructor
 * performs a run time check (in debug compilations of \b %ALib).<br>
 * It is checked whether
 * - the string type passed is already terminated or
 * - can be terminated because a) the buffer reserved capacity for the termination value and b)
 *   the buffer is writable.
 *
 * The second check is done only if the first did not apply and is performed using partially
 * implemented template struct
 * \ref aworx::lib::strings::T_IsTerminatable "T_IsTerminatable". Consult this struct for information
 * about how to enable external (user defined) string types to be used as parameters to implicitly
 * construct objects of this class.
 *
 *  \note
 *   While the good news is that C++ string literals, any zero terminated <em>char*</em> and
 *   objects of type <em>std::strings</em> or \b %ALib's \b %AString,
 *   are well suited to implicitly construct respectively directly serve as objects of this class,
 *   objects of type
 *   \ref aworx::lib::strings::String "String" itself and especially of type
 *   \ref aworx::lib::strings::Substring "Substring" are not.
 *   Therefore the latter are accepted only if they are terminated already.
 *   But obviously, this is especially unlikely for objects of type
 *   \ref aworx::lib::strings::Substring "Substring".
 *
 *  \note
 *   Therefore, for example to pass a <em>Substring</em>
 *   as a parameter to functions accepting only terminatable strings, it is possible to
 *   wrap them into temporary objects of type
 *   \ref aworx::lib::strings::AString "AString" or, if maximum size is known at compile time,
 *   of type
 *   \ref aworx::lib::strings::PreallocatedString "PreallocatedString".
 *   Of-course, a performance drawback (for creating the temporary copy of the contents) has to
 *   be taken into account.
 *
 *  \note
 *   Alternatively, class \b %Substring and class \b %String provide some useful
 *   implementations of slightly slower versions of some of the methods introduced this class.
 *   It has to be considered case by case which option is the best in respect to performance and
 *   memory use.
 *
 * <b>Constant Nature</b><p>
 * Same as parent class
 * \ref aworx::lib::strings::String "String", this class is not copying the data of the provided
 * source. It is designed preliminary to offer a fast but convenient (by implicit conversion)
 * type for function parameters that require terminated cstring buffers. As with parent class \b %String,
 * the life-time of objects of this class is considerably short.<br>
 * Only derived class \ref aworx::lib::strings::AString "AString" and its different
 * further specializations will copy the buffer and always include space for the termination
 * character in their buffers' capacity.
 *
 * <b>Parsing Numbers</b><p>
 * This class provides methods for parsing integer and floating point data.
 * For implementation performance reasons, those are <em>not</em> provided by parent class \b %String
 * which does not guarantee zero terminated strings. If parsing has to be done on non-zero
 * terminated string data, consider using a slightly slower variant of the parsing methods which
 * are found in class \ref aworx::lib::strings::Substring "Substring".<br>
 * It is rather more efficient, to instantiate a local Substring object that just wraps an
 * unterminated string of type \b %String and use its parsing interface, than copying the
 * unterminated data into a terminatable string variant (e.g. \b %AString) and to use the
 * interface provided herein.
 **************************************************************************************************/
class TString : public String
{
    /** ############################################################################################
     * @name Debug methods
     ##@{ ########################################################################################*/
    public:
    #if ALIB_DEBUG_STRINGS
        /** ****************************************************************************************
         * Validates this instance. This method is available only if \ref ALIB_DEBUG_STRINGS
         * is \c true. Invocations to this method should be performed using macro
         * \ref ALIB_STRING_DBG_CHK.
         ******************************************************************************************/
         void            _dbgCheck()   const;

        /**
         * This field serves for debugging the development (and potentially the use) of
         * derived classes, eg. class \ref aworx::lib::strings::AString "AString".
         * It is available only when compiler symbol \ref ALIB_DEBUG_STRINGS is \c true. When active,
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
        inline
        TString( const char* buffer, integer contentLength )
        : String( buffer, contentLength )
        {}


    public:

        /** ****************************************************************************************
         * Default constructor creating a \e nulled \b %TString.
         ******************************************************************************************/
        constexpr
        inline
        TString()
        : String()
        {}

        /** ****************************************************************************************
         * This constructor overloads the powerful templated constructor
         * \ref aworx::lib::strings::String::String(const TStringLike&) "String::String(const TStringLike&)".
         * In addition to invoking that, it is asserted that the given value is terminated or
         * type \p TTerminatable is terminatable. For more information see this classes' general
         * description.
         *
         * @param src  The string to represent by this object.
         ******************************************************************************************/
        template <typename TTerminatable>
        inline
        TString(const  TTerminatable& src )
        : String(src)
        {
            ALIB_ASSERT_ERROR(    T_IsTerminatable  < typename std::remove_cv
                                                    < typename std::remove_pointer<TTerminatable>::type>::type>::value
                              ||  IsNull()
                              ||  buffer[length] == '\0'
                              ,"Error unterminated and non-terminatable string buffer given." );
        }

    /** ############################################################################################
     * @name General Interface
     ##@{ ########################################################################################*/
    public:
        /** ****************************************************************************************
         * Reads a character at a given index.<br> Overrides
         * \ref aworx::lib::strings::String::operator[] "String::operator[]" to change the debug assertion
         * to allow inclusion of the termination character.
         *
         * \attention
         *   No parameter check is performed (other than an assertions in debug-compilation of \b %ALib).
         *   See \ref aworx::lib::strings::String::operator[] "String::operator[]" for details.
         *
         * @param   op    The index of the character within this objects' buffer.
         * @returns If the character contained at index \p op.
         ******************************************************************************************/
         inline
         char    operator[] (integer  op) const
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
         *   When compiler symbol \ref ALIB_DEBUG_STRINGS is \c true, the state of debug field
         *   #debugIsTerminated gets set to '1'.
         *
         *  \see #ToCString, #operator const char*().
         ******************************************************************************************/
        inline
        void Terminate()    const
        {
            ALIB_ASSERT_ERROR(  buffer != nullptr ,"Can't terminated nulled object." );

            // Note:
            // The following read may cause memory tools to detect access to uninitialized memory.
            // This is OK and should be ignored/suppressed.
            // For the 'valgrind' tool, add a suppression rule as follows:
            //   {
            //      <TString_terminate>
            //      Memcheck:Cond
            //      fun:*TStXring*Terminate*
            //   }
            //
            // (Tested with valgrind version 3.11)
            // See project folder "tools" for a complete valgrind suppression file for \b %ALib.

            if (buffer[ length ] != '\0' )
            {
                vbuffer[ length ]= '\0';

                #if ALIB_DEBUG_STRINGS
                    // cast to non-const...hey its for good 8-)
                    const_cast<TString*>(this)->debugIsTerminated= 1;
                #endif
            }
        }


    /** ############################################################################################
     * @name Character and String Search
     ##@{ ########################################################################################*/

        using String::IndexOf;

        /** ****************************************************************************************
         * Search the given terminatable string in this object.
         *
         * \note
         *   Parameter \p needle is required to be terminated or terminatable, the same as this
         *   object is.
         *   For non-terminatable string types (e.g. those of type
         *   \ref aworx::lib::strings::Substring "Substring"), a less performant implementation
         *   of this method is available through class \b %String with:
         *   \ref aworx::lib::strings::String::IndexOf "IndexOf".<br>
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c <false\> is added to the method name, no parameter checks are
         *                     performed and the needle must not be empty.
         * @param needle       The String to search for.
         * @param startIdx     The index to start the search at. Optional and defaults to \c 0.
         * @param sensitivity  Case sensitivity of the comparison.
         *                     Optional and defaults to Case::Sensitive.
         *
         * @return    -1 if the string is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        integer    IndexOf( const TString&   needle,
                            integer          startIdx= 0,
                            lang::Case       sensitivity=  lang::Case::Sensitive )
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
                ALIB_ASSERT_ERROR( startIdx >= 0 && startIdx < length && needle.Length() != 0,
                                   "Non checking and illegal parameters" );
            }


            #if defined (__GLIBCXX__) || defined(__APPLE__)
                const char* foundAt= sensitivity == lang::Case::Sensitive
                     ? strstr    ( ToCString() + startIdx, needle.ToCString() )
                     : strcasestr( ToCString() + startIdx, needle.ToCString() );
                return  foundAt != nullptr ? foundAt - buffer  :   -1;
            #else
                if ( sensitivity == lang::Case::Sensitive )
                {
                    const char* foundAt=  strstr( ToCString() + startIdx, needle.ToCString() );
                    return  foundAt != nullptr ?  (int) (foundAt - buffer)  :   -1;
                }
                else
                    // there is no strcasestr in windows, we use the slower String version, non-checking
                    return IndexOfSubstring<false>( needle, startIdx , lang::Case::Ignore );
            #endif
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         *
         * This method searches forwards. For backwards search, see
         * \ref aworx::lib::strings::String::LastIndexOfAny "String::LastIndexOfAny".
         *
         *
         * \note This method reimplements method
         *       \ref aworx::lib::strings::String::IndexOf "String::IndexOf" of parent class.
         *       This implementation however needs (beside the fact that this is a zero terminatable)
         *       a zero-terminatable string for the needles.
         *       If no zero-terminatable needles are available, parent method accepting non-zero
         *       terminated needles needs to be invoked. This is possible, for example
         *       by writing e.g. <em>mystring.String::IndexOf()</em>.
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
        integer  IndexOfAny( const TString& needles, lang::Inclusion inclusion, integer startIdx= 0 )
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


            if ( inclusion == lang::Inclusion::Include )
            {
                const char* res=  std::strpbrk( ToCString() + startIdx, needles.ToCString() );
                return  res == nullptr ? -1 : res  - buffer;
            }
            else
            {
                const char* haystack= ToCString() + startIdx;
                integer idx=  static_cast<integer>(std::strspn ( haystack, needles.ToCString() ) ) ;
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
         * Parses an integer value consisting of characters \c '0' to \c '9' from this string.
         * <br>Unlike with #ParseInt or #ParseDec, no sign, whitespaces or group characters are
         * accepted.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first character
         *                     in this string after the float number that was parsed.
         *                     If parsing fails, it will be set to the value of parameter startIdx.
         *                     Therefore, this parameter can be used to check if a value was found.
         *
         * @return  The parsed value. In addition, the parameter \p newIdx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        ALIB_API
        uint64_t  ParseDecDigits( integer startIdx =0, integer* newIdx= nullptr ) const;


        /** ****************************************************************************************
         * Parses an integer value in decimal, binary, hexadecimal or octal format from
         * the string by invoking method
         * \ref aworx::lib::strings::NumberFormat::ParseInt "NumberFormat::ParseInt"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        ALIB_API
        int64_t  ParseInt( integer startIdx =0, NumberFormat* numberFormat= nullptr,
                               integer* newIdx= nullptr ) const;

        /** ****************************************************************************************
         * Overloaded version of #ParseInt(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        int64_t  ParseInt( NumberFormat* numberFormat, integer* newIdx= nullptr ) const
        {
            return ParseInt( 0, numberFormat, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of #ParseInt(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        int64_t  ParseInt( integer* newIdx ) const
        {
            return ParseInt( 0, nullptr, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of #ParseInt(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        int64_t  ParseInt( integer startIdx, integer* newIdx ) const
        {
            return ParseInt( startIdx, nullptr, newIdx );
        }

        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in standard decimal format at the given position
         * from this %AString. This is done, by invoking
         * \ref aworx::lib::strings::NumberFormat::ParseDec "NumberFormat::ParseDec"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail.
         * For reading signed integer values, see methods #ParseInt, for floating point numbers
         * #ParseFloat.
         *
         * For more information on number conversion, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        ALIB_API
        uint64_t  ParseDec( integer startIdx =0, NumberFormat* numberFormat= nullptr,
                            integer* newIdx= nullptr ) const;

        /** ****************************************************************************************
         * Overloaded version of #ParseDec(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseDec( NumberFormat* numberFormat, integer* newIdx= nullptr ) const
        {
            return ParseDec( 0, numberFormat, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of #ParseDec(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseDec( integer* newIdx ) const
        {
            return ParseDec( 0, nullptr, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of #ParseDec(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseDec( integer startIdx, integer* newIdx ) const
        {
            return ParseDec( startIdx, nullptr, newIdx );
        }

        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in binary format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref aworx::lib::strings::NumberFormat::ParseBin "NumberFormat::ParseBin"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        ALIB_API
        uint64_t  ParseBin( integer startIdx =0, NumberFormat* numberFormat= nullptr,
                                integer* newIdx= nullptr ) const;


        /** ****************************************************************************************
         * Overloaded version of #ParseBin(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseBin( NumberFormat* numberFormat, integer* newIdx= nullptr ) const
        {
            return ParseBin( 0, numberFormat, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of #ParseBin(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseBin( integer* newIdx ) const
        {
            return ParseBin( 0, nullptr, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of #ParseBin(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseBin( integer startIdx, integer* newIdx ) const
        {
            return ParseBin( startIdx, nullptr, newIdx );
        }

        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in hexadecimal format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref aworx::lib::strings::NumberFormat::ParseHex "NumberFormat::ParseHex"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        ALIB_API
        uint64_t  ParseHex( integer startIdx =0, NumberFormat* numberFormat= nullptr,
                            integer* newIdx= nullptr ) const;


        /** ****************************************************************************************
         * Overloaded version of #ParseHex(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseHex( NumberFormat* numberFormat, integer* newIdx= nullptr ) const
        {
            return ParseHex( 0, numberFormat, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of #ParseHex(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseHex( integer* newIdx ) const
        {
            return ParseHex( 0, nullptr, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of #ParseHex(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseHex( integer startIdx, integer* newIdx ) const
        {
            return ParseHex( startIdx, nullptr, newIdx );
        }

        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in octal format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref aworx::lib::strings::NumberFormat::ParseOct "NumberFormat::ParseOct"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        ALIB_API
        uint64_t  ParseOct( integer startIdx =0, NumberFormat* numberFormat= nullptr,
                            integer* newIdx= nullptr ) const;


        /** ****************************************************************************************
         * Overloaded version of #ParseOct(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseOct( NumberFormat* numberFormat, integer* newIdx= nullptr ) const
        {
            return ParseOct( 0, numberFormat, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of #ParseOct(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseOct( integer* newIdx ) const
        {
            return ParseOct( 0, nullptr, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of #ParseOct(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        uint64_t  ParseOct( integer startIdx, integer* newIdx ) const
        {
            return ParseOct( startIdx, nullptr, newIdx );
        }

        /** ****************************************************************************************
         * Reads a floating point number at the given position from this \b %AString.
         * This is done, by invoking
         * \ref aworx::lib::strings::NumberFormat::ParseFloat "NumberFormat::ParseFloat"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to 'international' settings (not using the locale) and therefore
         * also not parsing grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * For more information on parsing options for floating point numbers and number
         * conversion in general, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        ALIB_API
        double   ParseFloat( integer startIdx =0, NumberFormat* numberFormat= nullptr,
                             integer* newIdx= nullptr ) const;

        /** ****************************************************************************************
         * Overloaded version of #ParseFloat(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c nullptr.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        double  ParseFloat( NumberFormat* numberFormat, integer* newIdx= nullptr ) const
        {
            return ParseFloat( 0, numberFormat, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of #ParseFloat(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        double  ParseFloat( integer* newIdx ) const
        {
            return ParseFloat( 0, nullptr, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of #ParseFloat(int =,NumberFormat* =,int* =) providing default values
         * for omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        inline
        double  ParseFloat( integer startIdx, integer* newIdx ) const
        {
            return ParseFloat( startIdx, nullptr, newIdx );
        }

}; // class TString

}} // namespace lib::strings

/** Type alias name in namespace #aworx. */
using     TString              =       aworx::lib::strings::TString;

} // namespace aworx

#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
#endif // HPP_ALIB_STRINGS_TSTRING
