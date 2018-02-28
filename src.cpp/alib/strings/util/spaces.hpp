// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_STRINGS_UTIL_SPACES)
    #error "Header already included"
#endif


// then, set include guard
#ifndef HPP_ALIB_STRINGS_UTIL_SPACES
//! @cond NO_DOX
#define HPP_ALIB_STRINGS_UTIL_SPACES 1
//! @endcond

namespace aworx { namespace lib { namespace strings { namespace util  {


/** ************************************************************************************************
 * This is a simple class that provides a string full of spaces.
 * This string may be used to avoid repeated memory allocations/initializations and/or repeated
 * method invocations when a software interfaces to libraries that either allow to write
 * a string or a single character (i.e. <c>std::ostream</c>).
 **************************************************************************************************/
class Spaces
{
   public:
        /** ****************************************************************************************
         * Receives a string full of spaces. Its length depends on what is set during
         * library initialization.
         *
         * @return A static string filled with spaces.
         ******************************************************************************************/
        ALIB_API
        static String&  Get();

        /** ****************************************************************************************
         * Creates the string.
         *
         * This method is invoked during
         * \alib{strings,Strings::init,string library initialization} with \p minSize set to
         * \c 128. During initialization of user libraries, this value might be increased by
         * invoking this method with a higher value.
         *
         * @param minSize  The minimum number of spaces that should be available in the string
         *                 returned with #Get.
         ******************************************************************************************/
        ALIB_API
        static void     Initialize(integer minSize);

        /** ****************************************************************************************
         * Write the given number of spaces to the ostream.
         * @param os    The output stream to write to
         * @param qty   The quantity of spaces to write
         ******************************************************************************************/
        ALIB_API
        static void    Write( std::ostream& os, integer qty );
};

}}} // namespace aworx[::lib::strings::util]

/** Type alias name in namespace #aworx. */
using     Spaces   =   aworx::lib::strings::util::Spaces;

} // namespace aworx

#endif // HPP_ALIB_STRINGS_UTIL_SPACES
