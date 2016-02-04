// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// check for alib.hpp already there but not us
#if !defined (HPP_AWORX_LIB_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_AWORX_LIB_UTIL)
    #error "Header already included"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_AWORX_LIB_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_AWORX_LIB_UTIL
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_AWORX_LIB_UTIL 1
#endif
#include <iosfwd>

namespace aworx {
namespace           lib {

/** ************************************************************************************************
 *  This class aggregates functionality that is simple and not connected and (in this version
 *  of ALib) did not find a better home.
 **************************************************************************************************/
class Util
{
    // #############################################################################################
    // static functionality
    // #############################################################################################
   private:
        /** The internal string of spaces. */
        static AString          theSpaces;

   // #############################################################################################
   // Interface
   // #############################################################################################
   public:
        /** ****************************************************************************************
         * Receives a const AString full of spaces.
         * \attention
         *   Parameter \p minSize should be omitted and the size of the object returned accepted.
         *   Requesting a higher size, might result in slightly more efficiency.
         *   In multithreaded processes, changing the size must be performed during bootstrap,
         *   e.g. directly after invoking \ref aworx::lib::ALIB::Init "ALIB::Init" by calling
         *   this method with the appropriate size.
         *
         * @param minSize  The minimum number of spaces that should be available in the returned
         *                 AString. Defaults to 128. See notes in method description!
         *
         * @return A const AString filled with spaces.
         ******************************************************************************************/
        static const aworx::AString&  GetSpaces(int minSize= 128);

        /** ****************************************************************************************
         * Write the given number of spaces to the ostream.
         * @param os    The output stream to write to
         * @param qty   The quantity of spaces to write
         ******************************************************************************************/
        static void             WriteSpaces( std::ostream& os, int qty );
};

}} // namespace aworx

#endif // HPP_AWORX_LIB_UTIL
