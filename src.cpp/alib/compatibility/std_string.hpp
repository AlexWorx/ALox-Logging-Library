// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_COMPATIBILITY_STD_STRING)
    #error "Header already included"
#endif

#ifndef HPP_ALIB_COMPATIBILITY_STD_STRING
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_COMPATIBILITY_STD_STRING 1
#endif
#include <string>

// #################################################################################################
// AString / StdString compatibility Support
// #################################################################################################

namespace aworx {
namespace           lib {
namespace                   strings {


    /** ********************************************************************************************
     * Specialization of TMP 'function' (struct)
     * \ref aworx::lib::strings::ToStringDefined "ToStringDefined" for type \b std::string.
     * See \ref aworx::lib::strings::ToStringDefined "ToStringDefined" for more information
     **********************************************************************************************/
    template<>   struct               ToStringDefined<const std::string&>   : public std::true_type {};

    /** ********************************************************************************************
     * Specialization of template function
     * \ref aworx::lib::strings::ToString "ToString" for type \b std::string.
     *
     * @param  src The source string to take the buffer from.
     * @return The value of  <em>src.c_str()</em>.
     **********************************************************************************************/
    template<>   inline   const char* ToString        <const std::string&>( const std::string& src )
    {
        return  src.c_str();
    }

    /** ********************************************************************************************
     * Specialization of template function
     * \ref aworx::lib::strings::ToString "ToString" for type \b std::string.
     *
     * @param  src The source string to take the length from.
     * @return The length of \p src.
     **********************************************************************************************/
    template<>   inline   int         ToString        <const std::string&>( const std::string& src )
    {
        return (int) src.length();
    }

    /** ********************************************************************************************
     * Specialization of TMP 'function' (struct)
     * \ref aworx::lib::strings::IsApplicable "IsApplicable" for type \b std::string.
     **********************************************************************************************/
    template<>   struct               IsApplicable<const std::string&>   : public std::true_type {};

    /** ********************************************************************************************
     *  Specialization of template method
     *  \ref aworx::lib::strings::ApplyTo "ApplyTo" for applicable type \b std::string.
     * See \ref aworx::lib::strings::ApplyTo "ApplyTo" for more information
     * @param  target The AString to append \p src to.
     * @param  src    The source string to take the buffer from.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>   inline   int         ApplyTo <const std::string&>( AString& target, const std::string& src )
    {
        target.Append( src.c_str(), (int) src.length() );
        return (int) src.length();
    }

    /** ********************************************************************************************
     *  Specialization of (optional) non-checking version of template method
     *  \ref aworx::lib::strings::ApplyTo_NC "ApplyTo_NC" for applicable type \b std::string.
     *
     * @param  target The AString to append \p src to.
     * @param  src    The source string to take the buffer from.
     * @return The length of the given string \p src which was appended to \p target.
     **********************************************************************************************/
    template<>   inline   int         ApplyTo_NC <const std::string&>( AString& target, const std::string& src )
    {
        target.Append<false>( src.c_str(), (int) src.length() );
        return (int) src.length();
    }

    /** ********************************************************************************************
     *  Copies or appends a region of a given \ref aworx::lib::strings::String "String" into a std::string.
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
                              int                regionStart,
                              int                regionLength    = CString::MaxLen,
                              enums::CurrentData targetData      = enums::CurrentData::Clear )
    {
        if ( targetData == enums::CurrentData::Clear )
            target.clear();

        // adjust range, if empty return empty string
        if ( as.AdjustRegion( regionStart, regionLength ) )
            return target;

        // copy our buffer into target
        target.append( as.Buffer() , regionStart, regionLength );
        return  target;
    }

    /** ********************************************************************************************
     *  Copies a region of a given \ref aworx::lib::strings::String "String" into a std::string which
     *  is created.
     *  The region is adjusted to the length of the %String.
     *
     * @param as            The \ref aworx::lib::strings::String "String" to convert into a std::string.
     * @param regionStart   The start index of the region in this to create the std::string from.
     * @param regionLength  The maximum length of the region to be copied.
     *                      Defaults to CString::MaxLen.
     *
     * @return A string that represents the specified sub region of this object.
     **********************************************************************************************/
    inline
    std::string  ToStdString( const String& as, int regionStart, int regionLength= CString::MaxLen )
    {
        std::string retval;
        ToStdString( as, retval, regionStart, regionLength);
        return retval;
    }

    /** ********************************************************************************************
     *  Copies the contents of a given \ref aworx::lib::strings::String "String" into the given std::string.
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
     *  Copies the contents of a given \ref aworx::lib::strings::String "String" into the given std::string.
     *
     * @param as           The \ref aworx::lib::strings::String "String" to convert into a std::string.
     * @param target       A target std::string to copy the contents of this %String into.
     * @param targetData   If \c CurrentData::Keep, parameter \p target is not cleared before
     *                     the result is written. Defaults to \c CurrentData::Clear.
     * @return The (modified) result that was provided (for concatenation of calls).
     **********************************************************************************************/
    inline
    std::string& ToStdString( const String&      as,
                              std::string&       target,
                              enums::CurrentData targetData = enums::CurrentData::Clear )
    {
        return ToStdString( as, target, 0, as.Length(), targetData );
    }
}}}

#endif // HPP_ALIB_COMPATIBILITY_STD_STRING
