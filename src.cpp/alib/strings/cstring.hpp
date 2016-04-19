// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// to preserve the right order, we are not includable directly from outside.
#if !defined(FROM_HPP_ALIB) || defined(HPP_ALIB_STRINGS_CSTRING)
    #error "include alib/alib.hpp instead of this header"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_ALIB_STRINGS_CSTRING
#define HPP_ALIB_STRINGS_CSTRING 1

// #################################################################################################
// includes
// #################################################################################################

#include <cstring>
#include <limits>

namespace aworx {
namespace           lib {
namespace                   strings {

class String;
class TString;

/** ************************************************************************************************
 *  This inner class of AString provides static methods working with zero-terminated character
 *  arrays, aka cstrings.
 **************************************************************************************************/
class CString
{
    // #########################################################################################
    //  Fields
    // #########################################################################################
    public:

         /** The maximum length of a cstring.            */
         #if defined( _MSC_VER )
            const       static      int               MaxLen=       MAXINT;
         #else
            constexpr   static      int               MaxLen=       std::numeric_limits<int>::max();
         #endif

    // #########################################################################################
    //  String helpers
    // #########################################################################################

        /** ****************************************************************************************
         * Determines the number of characters of the given encoded string if it was converted to
         * a wide character string.
         * The calculation is done using
         * - <em>mbsnrtowcs()</em>
         *   (without providing a conversion buffer) on glibc platforms (e.g. Linux)
         * - <em>MultiByteToWideChar()</em>
         *   (without providing a conversion buffer) on the Windows platform.
         *
         * \note On Linux, it might be necessary to invoke std c method <em>setlocale()</em> once
         *       prior to using this method, to successfully calculate the length.
         *       This, by default, is done in \ref aworx::lib::ALIB::Init "ALIB::Init".
         *
         * @param cs         Pointer to the start of the cstring.
         * @param csLength   The length of the sequence in \p cs to examine.
         *
         * @return  The length of string when it was converted to wide characters.
         *          If counting failed (what means that the conversion will fail) -1 is returned.
         ******************************************************************************************/
        ALIB_API
        static int  LengthWhenConvertedToWChar( const char* cs,  int  csLength );

        /** ************************************************************************************
         * Static method that adjusts a given region to fit into the range [0 .. referenceLength].
         *
         * @param referenceLength The length of the reference region to which the other parameters
         *                        get adjusted to.
         * @param regionStart     The proposed region start which might get adjusted to fit to
         *                        span 0 to referenceLength.
         * @param regionLength    The proposed region length which might get adjusted to fit to
         *                        span 0 to referenceLength.
         *
         * @return   Returns \c true, if the adjusted region is empty.
         **************************************************************************************/
        inline
        static  bool AdjustRegion( int referenceLength, int& regionStart, int& regionLength )
        {
            // if start exceeds string, set to empty range at the end of the string and return true
            if (regionStart >= referenceLength)
            {
                regionStart=    referenceLength;
                regionLength=    0;
                return true; // indicate empty
            }

            // if negative start, cut it from the length
            if (regionStart < 0 )
            {
                regionLength+=    regionStart; // this adds a negative value, hence we do not exceed a given MAXINT
                regionStart=    0;
            }

            // adjust length
            int maxLen=  referenceLength - regionStart;
            if ( regionLength > maxLen )
                 regionLength=  maxLen;
            if ( regionLength < 0 )
                regionLength= 0;

            // return true if adjusted region is empty
            return  regionLength == 0;
        }

    // #########################################################################################
    //  Comparison methods
    // #########################################################################################

        /** ************************************************************************************
         * This is just a wrapper on 'strncasecmp' because it is not available under that name
         * in Windows OS.
         *
         * @param cs1         The first cstring to compare.
         * @param cs2         The second cstring to compare.
         * @param cmpLength   The number of characters to compare.
         *
         * @return  See strncasecmp().
         **************************************************************************************/
        static
        inline
        int strncasecmp( const char* cs1,  const char* cs2, int cmpLength  )
        {
            #if defined (__GLIBCXX__)
                return  ::strncasecmp( cs1, cs2, cmpLength  );
            #elif defined ( _WIN32 )
                return  _strnicmp  ( cs1, cs2, cmpLength  );
            #else
                #pragma message ( "Unknown Platform in file: " __FILE__ )
            #endif
        }


    // #########################################################################################
    //  Search methods
    // #########################################################################################

        /** ************************************************************************************
         * Static method that returns the index of the first character which is included
         * (alternatively not included) in a given set of characters.
         *
         * This method searches up to a given maximum index. For a search to the end of the
         * zero terminated string, use faster method provided with class
         * \ref aworx::lib::strings::TString "TString".

         * @param haystack        Pointer to the start of the string.
         * @param haystackLength  The length of the string or the maximum position to search.
         *                        If -1 is provided, the length is determined using % C function
         *                        strlen (which needs haystack to be zero terminated).
         * @param needles         Pointer to a set of characters to be searched for.
         * @param needlesLength   The length of the string of needles.
         *                        If -1 is provided, the length is determined using % C function
         *                        strlen (which needs needles to be zero terminated).
         * @param inclusion       Denotes whether the search returns the first index that holds
         *                        a value that is included or that is not excluded in the set of
         *                        needle characters.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         **************************************************************************************/
        ALIB_API
        static int     IndexOfAny( const char*  haystack,   int  haystackLength,
                                   const char*  needles,    int  needlesLength,
                                   enums::Inclusion inclusion                             );


        /** ************************************************************************************
         * Static method that returns the index of the first character which is included
         * (alternatively not included) in a given set of characters.
         *
         * This method searches backwards from the end of the string.
         *
         * @param haystack        Pointer to the start of the string.
         * @param startIdx        The position to start the search from. This must be smaller than
         *                        the length of the string and greater or equal to  zero.
         * @param needles         Pointer to a set of characters to be searched for.
         * @param needlesLength   The length of the string of needles.
         *                        If -1 is provided, the length is determined using % C function
         *                        strlen (which needs needles to be zero terminated).
         * @param inclusion       Denotes whether the search returns the first index that holds
         *                        a value that is included or that is not excluded in the set of
         *                        needle characters.
         *
         * @return The index of the first character found which is included in the given set
         *         of characters. If nothing is found, -1 is returned.
         **************************************************************************************/
        ALIB_API
        static int     LastIndexOfAny( const char*  haystack,   int  startIdx,
                                       const char*  needles,    int  needlesLength,
                                       enums::Inclusion inclusion                               );



}; //  class CString


}}} // namespace aworx::lib::strings

#endif // HPP_ALIB_STRINGS_CSTRING
