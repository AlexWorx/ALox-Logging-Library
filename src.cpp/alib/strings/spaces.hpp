// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_STRINGS_SPACES)
    #error "Header already included"
#endif


// then, set include guard
#ifndef HPP_ALIB_STRINGS_SPACES
//! @cond NO_DOX
#define HPP_ALIB_STRINGS_SPACES 1
//! @endcond NO_DOX
#include <iosfwd>

namespace aworx { namespace lib { namespace strings
{
/** ************************************************************************************************
 * This is a simple class that provides a string full of spaces. This may be used to avoid
 * memory allocations/initializations.
 **************************************************************************************************/
class Spaces
{
    // #############################################################################################
    // static functionality
    // #############################################################################################
    protected:
        /** The internal string of spaces. */
        static AString          theSpaces;

   // #############################################################################################
   // Interface
   // #############################################################################################
   public:
        /** ****************************************************************************************
         * Receives a const AString full of spaces.
         *
         * @return A const AString filled with spaces.
         ******************************************************************************************/
        inline
        static const aworx::AString&  Get()
        {
            return GetUnsafe( 128 );
        }

        /** ****************************************************************************************
         * Receives a const AString full of spaces.
         *
         * \attention
         *   In multithreaded processes, changing the size of the internal spaces string must be
         *   performed during bootstrap, e.g. directly after invoking
         *   \ref aworx::lib::ALIB::Init "ALIB::Init" by calling this method with the appropriate
         *   size.
         *
         * @param minSize  The minimum number of spaces that should be available in the returned
         *                 AString
         * @return A const AString filled with spaces.
         ******************************************************************************************/
        static const aworx::AString&  GetUnsafe(integer minSize);

        /** ****************************************************************************************
         * Write the given number of spaces to the ostream.
         * @param os    The output stream to write to
         * @param qty   The quantity of spaces to write
         ******************************************************************************************/
        static void             Write( std::ostream& os, integer qty );
};

}} // namespace lib::strings

/** Type alias name in namespace #aworx. */
using     Spaces   =   aworx::lib::strings::Spaces;

} // namespace aworx

#endif // HPP_ALIB_STRINGS_SPACES
