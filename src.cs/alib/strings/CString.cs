// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Text;
using cs.aworx.lib.strings;
using cs.aworx.lib.time;
using cs.aworx.lib.lang;

namespace cs.aworx.lib.strings  {


/** ************************************************************************************************
 *  Provides static methods working with character arrays.
 **************************************************************************************************/
public class CString
{
    // #############################################################################################
    //  Static fields
    // #############################################################################################

    /** The system depended new line character codes retrieved statically (once) using
     *  "Environment.NewLine;"  */
    public static readonly String       NewLineChars                      =Environment.NewLine;


    /** Contains all characters that by default get trimmed by trim methods defined
     *  in this class.  */
    public static readonly char[]       DefaultWhitespaces                = {' ','\r','\n','\t' };

    /** A singleton that references a zero-length character array.
     *  May be used to avoid object allocation.  */
    public readonly static char[]       NullBuffer                        = new char[0];


    // #############################################################################################
    //  String helpers
    // #############################################################################################

    /** ********************************************************************************************
     * Static method that adjusts a given region to fit into the range [0 .. referenceLength].
     *
     * @param referenceLength       Length of the string that the given region will be adjusted to.
     * @param[in,out] regionStart   The start of the region to be adjusted.
     * @param[in,out] regionLength  The length of the region to be adjusted.
     *
     * @return True if adjusted range is empty.
     **********************************************************************************************/
    public static bool AdjustRegion( int referenceLength, ref int regionStart, ref int regionLength )
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


    // #############################################################################################
    //  Compare/ContainsAt
    // #############################################################################################

    /** ********************************************************************************************
     * Compares a region of a \e String with another region in a \e char[].<br>
     * No parameter checks are performed. Null and empty checks and proper region bounds
     * have to be provided (this is a helper method for other compareTo methods).
     *
     * @param needle         A \e String that is compared to this.
     * @param needleStart    The start of the substring within \p{needle}.
     * @param needleLength   The length of the substring within \p{needle}.
     * @param haystack       The character buffer that is to compared.
     * @param haystackStart  The start of the substring within \p{haystack}.
     * @param haystackLength The length of the substring within \p{haystack}.
     * @param sensitivity    Case sensitivity of the operation.
     *
     * @return
     *  -  0 if \p{haystack} and \p{needle} are \e null or if both have a length of 0 or if
     *     both  share the same content.
     *  - <0 if \p{haystack} is \e nulled and \p{needle} is not or if \p{haystack} is smaller
     *    than \p{needle}.
     *  - >0 if \p{haystack} is not \e nulled but \p{needle} is or if \p{haystack} is greater
     *    than \p{needle}.
     **********************************************************************************************/
    static
    public int CompareTo(   String needle,      int    needleStart,  int   needleLength,
                            char[] haystack,    int  haystackStart,  int haystackLength,
                            Case   sensitivity   )
    {
        // compare loop
        int srcIdx=  haystackStart;
        int srcEnd=  haystackStart   + haystackLength;
        int cmpIdx=    needleStart;
        int cmpEnd=    needleStart   +   needleLength;
        while ( true )
        {
            // end of one of the strings or both?
            if (srcIdx >= srcEnd)    return  (cmpIdx >= cmpEnd) ?     0    :    -1;
            if (cmpIdx >= cmpEnd)    return                                      1;

            // compare characters
            char srcC=  haystack[ srcIdx  ];
            char cmpC=  needle [ cmpIdx ];
            if ( srcC != cmpC )
            {
                // no match!
                if ( sensitivity == Case.Sensitive )
                    return srcC - cmpC;

                // compare ignore case
                int diff= ( Char.ToLower( srcC ) - Char.ToLower( cmpC ) );
                if ( diff != 0 )
                    return diff;
            }

            // next
            srcIdx++; cmpIdx++;
        }
    }

    /** ********************************************************************************************
     * Compares two regions of two \e char[].<br>
     * No parameter checks are performed. Null and empty checks and proper region bounds
     * have to be provided (this is a helper method for other compareTo methods).
     *
     * @param needle         A \e char[] that is compared to this.
     * @param needleStart    The start of the substring within \p{needle}.
     * @param needleLength   The length of the substring within \p{needle}.
     * @param haystack       The \e char[] that is to compared.
     * @param haystackStart  The start of the substring within \p{haystack}.
     * @param haystackLength The length of the substring within \p{haystack}.
     * @param sensitivity    Case sensitivity of the operation.
     *
     * @return
     *  -  0 if \p{haystack} and \p{needle} are \e null or if both have a length of 0 or if
     *     both  share the same content.
     *  - <0 if \p{haystack} is \e nulled and \p{needle} is not or if \p{haystack} is smaller
     *    than \p{needle}.
     *  - >0 if \p{haystack} is not \e nulled but \p{needle} is or if \p{haystack} is greater
     *    than \p{needle}.
     **********************************************************************************************/
    static
    public int CompareTo(   char[] needle,      int    needleStart,  int   needleLength,
                            char[] haystack,    int  haystackStart,  int haystackLength,
                            Case   sensitivity   )
    {
        // compare loop
        int srcIdx=  haystackStart;
        int srcEnd=  haystackStart   + haystackLength;
        int cmpIdx=    needleStart;
        int cmpEnd=    needleStart   +   needleLength;
        while ( true )
        {
            // end of one of the strings or both?
            if (srcIdx >= srcEnd)    return  (cmpIdx >= cmpEnd) ?     0    :    -1;
            if (cmpIdx >= cmpEnd)    return                                      1;

            // compare characters
            char srcC=  haystack[ srcIdx  ];
            char cmpC=  needle[ cmpIdx ];
            if ( srcC != cmpC )
            {
                // no match!
                if ( sensitivity == Case.Sensitive )
                    return srcC - cmpC;

                // compare ignore case
                int diff= ( Char.ToLower( srcC ) - Char.ToLower( cmpC ) );
                if ( diff != 0 )
                    return diff;
            }

            // next
            srcIdx++; cmpIdx++;
        }
    }

    /** ********************************************************************************************
     * Checks if a region of a \e char[] is located at the given position of another \e char[].
     * @param needle          The character array containing the needle.
     * @param needleStart     The index of the start of the needle within the character array.
     * @param needleLength    The length of the needle within the character array.
     * @param haystack        The character array to look in for the needle.
     * @param haystackPos     The position to look at in \p{haystack}.
     * @param haystackLimit   The length of the \p{haystack} (may be equal or less than
     *                        haystack.Length).
     * @param sensitivity     Case sensitivity of the comparison.
     *                        Optional and defaults to Case.Sensitive.
     *
     * @return  \c true if the needle is found at the given position. \c false otherwise.
     **********************************************************************************************/
    static
    public bool ContainsAt( char[] needle,    int needleStart, int needleLength,
                            char[] haystack,  int haystackPos, int haystackLimit,
                            Case sensitivity= Case.Sensitive )
    {
        int cmpEnd=     haystackPos + needleLength;
        if ( haystackPos < 0 || cmpEnd > haystackLimit  || needle == null )
            return false;

        if ( needleLength <= 0 )
            return true;

        // the compare loop
        if ( sensitivity == Case.Ignore )
        {
            while ( haystackPos < cmpEnd )
            {
                if (     Char.ToLower( needle [ needleStart++ ] )
                     !=  Char.ToLower( haystack [ haystackPos++ ]         ) )
                    return false;
            }
        }
        else
        {
            while ( haystackPos < cmpEnd )
            {
                if (     needle [ needleStart++ ]
                     !=  haystack [ haystackPos++ ] )
                    return false;
            }
        }

        return true;
    }


    /** ********************************************************************************************
     * Checks if the given \e String is located at the given position in a \e char[].
     *
     * @param needle          The character array containing the needle.
     * @param haystack        The character array to look in for the needle.
     * @param haystackPos     The position to look at in \p{haystack}.
     * @param haystackLimit   The length of the  \p{haystack} (may be equal or less than
     *                        haystack.Length.
     * @param sensitivity     Case sensitivity of the comparison.
     *                        Optional and defaults to Case.Sensitive.
     * @return  \c true if the needle is found at the given position. \c false otherwise.
     **********************************************************************************************/
    static
    public bool ContainsAt( String needle,
                            char[] haystack,  int haystackPos, int haystackLimit,
                            Case sensitivity= Case.Sensitive )
    {
        // check null argument or length 0
        int needleLen=  needle != null ?  needle.Length : 0;
        int cmpEnd=     haystackPos + needleLen;
        if ( haystackPos < 0 || cmpEnd > haystackLimit || needle == null )
            return false;

        // the compare loop
        int nPos= 0;
        if ( sensitivity == Case.Ignore )
        {
            while ( haystackPos < cmpEnd )
            {
                if (     Char.ToLower( needle [ nPos++ ] )
                     !=  Char.ToLower( haystack [ haystackPos++ ]         ) )
                    return false;
            }
        }
        else
        {
            while ( haystackPos < cmpEnd )
            {
                if (     needle [ nPos++ ]
                     !=  haystack [ haystackPos++ ] )
                    return false;
            }
        }

        return true;
    }



    // #############################################################################################
    //  IndexOf
    // #############################################################################################

    /** ********************************************************************************************
     *  Static method that searches a character in a region of a character array.
     *
     * @param haystack        Character array that is searched in.
     * @param needle          The character to be searched for.
     * @param regionStart     The start of the region within haystack.
     *                        Defaults to 0.
     * @param regionLength    The length of the region within haystack.
     *                        Defaults to int.MaxValue.
     *
     * @return The index of the first character found
     *         which is included, respectively not included, in the given set of characters.
     *         If nothing is found, -1 is returned.
     **********************************************************************************************/
    public
    static int     IndexOf( char[] haystack, char needle, int regionStart= 0, int regionLength= int.MaxValue )
    {
        if( AdjustRegion( haystack.Length, ref regionStart, ref regionLength ) )
            return -1;

        int e= regionStart + regionLength;

        while( regionStart < e )
        {
            if ( haystack[regionStart] == needle )
                return regionStart;
            regionStart++;
        }

        return -1;
    }

    /** ********************************************************************************************
     * Search the given String in a region of a character array.
     *
     * @param needle          The string to be searched for.
     * @param haystack        Character array that is searched in.
     * @param haystackStart   The start of the region within haystack.
     * @param haystackLength  The length of the region within haystack.
     * @param sensitivity     The sensitivity to the case of characters of the operation.
     * @return  \e -1 if the String is not found. Otherwise the index of first occurrence
     *          relative to \p{haystackStart}.
     **********************************************************************************************/
    public static int IndexOfString(  String        needle,
                                      char[]        haystack,
                                      int           haystackStart,
                                      int           haystackLength,
                                      Case          sensitivity                 )
    {
        // checks
        if ( haystackStart <  0 )   haystackStart= 0;
        int needleLength;
        if( needle == null || (needleLength= needle.Length) == 0 )
            return  haystackStart;

        // case sensitive
        int hayStackEnd= haystackStart + haystackLength;
        if ( sensitivity == Case.Sensitive )
        {
            char firstChar= needle[ 0 ];
            while ( haystackStart + needleLength <= hayStackEnd )
            {
                if ( haystack[ haystackStart ] == firstChar )
                {
                    int  cmpLen= 1;
                    while (     cmpLen != needleLength
                            &&  haystack[ haystackStart + cmpLen ] == needle[cmpLen] )
                        cmpLen++;
                    if ( cmpLen == needleLength )
                        return haystackStart;
                }
                haystackStart++;
            }
        }

        // ignore case
        else
        {
            char firstChar= Char.ToLower( needle[ 0 ] );
            while ( haystackStart + needleLength <= hayStackEnd )
            {
                if ( Char.ToLower( haystack[ haystackStart ] ) == firstChar )
                {
                    int  cmpLen= 1;
                    while (     cmpLen != needleLength
                            &&  Char.ToLower(haystack[ haystackStart + cmpLen ])  == Char.ToLower( needle[cmpLen] ) )
                        cmpLen++;
                    if ( cmpLen == needleLength )
                        return haystackStart;

                }
                haystackStart++;
            }
        }

        // not found
        return -1;
    }

    /** ********************************************************************************************
     * Search the given AString in a region of a character array.
     *
     * @param needle          The string to be searched for.
     * @param needleStart     The start of the region within haystack.
     * @param needleLength    The length of the region within haystack.
     * @param haystack        Character array that is searched in.
     * @param haystackStart   The start of the region within haystack.
     * @param haystackLength  The length of the region within haystack.
     * @param sensitivity     The sensitivity to the case of characters of the operation.
     * @return  \e -1 if the String is not found. Otherwise the index of first occurrence
     *          relative to \p{haystackStart}.
     **********************************************************************************************/
    public static int IndexOfString(  char[]        needle,
                                      int           needleStart,
                                      int           needleLength,
                                      char[]        haystack,
                                      int           haystackStart,
                                      int           haystackLength,
                                      Case          sensitivity                 )
    {
        // checks
        if ( haystackStart <  0 )  haystackStart= 0;
        if ( needleLength  == 0 )  return  haystackStart;

        // case sensitive
        int hayStackEnd= haystackStart + haystackLength;
        if ( sensitivity == Case.Sensitive )
        {
            char firstChar= needle[ needleStart ];
            while ( haystackStart + needleLength <= hayStackEnd )
            {
                if ( haystack[ haystackStart ] == firstChar )
                {
                    int  cmpLen= 1;
                    while (     cmpLen != needleLength
                            &&      haystack[ haystackStart + cmpLen ]
                                ==  needle  [ needleStart   + cmpLen]  )
                        cmpLen++;
                    if ( cmpLen == needleLength )
                        return haystackStart;
                }
                haystackStart++;
            }
        }

        // ignore case
        else
        {
            char firstChar= Char.ToLower( needle[ needleStart ] );
            while ( haystackStart + needleLength <= hayStackEnd )
            {
                if ( Char.ToLower( haystack[ haystackStart ] ) == firstChar )
                {
                    int  cmpLen= 1;
                    while (     cmpLen != needleLength
                            &&      Char.ToLower( haystack[ haystackStart + cmpLen ] )
                                ==  Char.ToLower(   needle[ needleStart   + cmpLen ] ) )
                        cmpLen++;
                    if ( cmpLen == needleLength )
                        return haystackStart;

                }
                haystackStart++;
            }
        }

        // not found
        return -1;
    }

    /** ********************************************************************************************
     * Static method that returns the index of the first character which not equal
     * within two strings.
     * If \p{haystack} starts with \p{needle}, then the length of \p{needle} is returned.
     *
     * @param haystack        Character array that is searched in.
     * @param haystackStart   The start of the region within haystack.
     * @param haystackLength  The length of the region within haystack.
     * @param needle          The string to be searched for.
     * @param sensitivity     The sensitivity to the case of characters of the operation.
     * @return  The index within \p{needle} with the first difference.
     **********************************************************************************************/
    public static int IndexOfFirstDifference(  char[]        haystack,
                                               int           haystackStart,
                                               int           haystackLength,
                                               String        needle,
                                               Case          sensitivity                 )
    {
        int needleLength= needle.Length;

        int haystackEnd= haystackStart + haystackLength;
        int idxH= haystackStart;
        int idxN=  0;

        if ( sensitivity == Case.Sensitive )
        {
            while (   idxH < haystackEnd
                   && idxN < needleLength
                   && haystack[idxH] == needle[idxN])
            {
                idxH++;
                idxN++;
            }
        }
        else
        {
            while (   idxH < haystackEnd
                   && idxN < needleLength
                   && Char.ToLower( haystack[idxH] ) == Char.ToLower( needle[idxN] ) )
            {
                idxH++;
                idxN++;
            }
        }
        return idxN;
    }

    /** ********************************************************************************************
     * Static method that returns the index of the first character which is included
     * (alternatively not included) in a given set of characters.
     *
     * This method searches from left to right. For backward search, see
     * \ref LastIndexOfAny
     *
     * @param haystack     Character array that is searched in.
     * @param regionStart  The start of the region within haystack.
     * @param regionLength The length of the region within haystack.
     * @param needles      Character array that holds the characters to be searched for.
     * @param inclusion    Denotes whether the search returns the first index that holds a value
     *                     that is included or that is not excluded in the set of needle
     *                     characters.
     *
     * @return The index (relative to the start of the region) of the first character found
     *         which is included, respectively not included, in the given set of characters.
     *         If nothing is found, -1 is returned.
     **********************************************************************************************/
    public
    static int     IndexOfAnyInRegion( char[]    haystack,
                                       int       regionStart, int   regionLength,
                                       char[]    needles,
                                       Inclusion inclusion                                   )
    {
        int     nbLen=  needles.Length;

        int     i=      regionStart;
        int     e=      regionStart + regionLength;

        if ( inclusion == Inclusion.Include )
        {
            while( i != e )
            {
                char c= haystack[i];
                for( int n= 0; n < nbLen ; n++ )
                    if ( c == needles[n] )
                        return i;
                i++;
            }
        }
        else
        {
            while( i != e )
            {
                char c= haystack[i];
                int n= 0;
                while ( n < nbLen && c != needles[n] )
                    n++;

                if ( n == nbLen )
                    return i;
                i++;
            }
        }

        return -1;
    }

    /** ********************************************************************************************
     * Static method that returns the index of the first character which is included
     * (alternatively not included) in a given set of characters.
     * The search starts at the end of the region and continues towards its start.
     *
     * @param haystack      Characer array to search in.
     * @param regionStart   The start of the region within haystack.
     * @param regionLength  The length of the region within haystack.
     * @param needles       Characer array that holds the characters to be searched for.
     * @param inclusion     Denotes whether the search returns the first index that holds a value
     *                      that is included or that is not excluded in the set of needle
     *                      characters.
     *
     * @return The index relative to the start of the region.
     *         If the search was not successful, then regionStart -1 is returned;
     **********************************************************************************************/
    public
    static int     LastIndexOfAny( char[]    haystack,
                                   int       regionStart, int   regionLength,
                                   char[]    needles,
                                   Inclusion inclusion                         )
    {
        int     nbLen=  needles.Length;

        int     i=      regionStart + regionLength - 1;
        if ( inclusion == Inclusion.Include )
        {
            while( i >= regionStart )
            {
                char c= haystack[i];
                for( int n= 0; n < nbLen ; n++ )
                    if ( c == needles[n] )
                        return i;
                i--;
            }
        }
        else
        {
            while( i >= regionStart )
            {
                char c= haystack[i];
                int n= 0;
                while ( n < nbLen && c != needles[n] )
                    n++;

                if ( n == nbLen )
                    return i;

                i--;
            }
        }
        return regionStart - 1;
    }

}  //  class CString

} // namespace / EOF
