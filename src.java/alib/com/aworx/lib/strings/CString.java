// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.strings;

import com.aworx.lib.enums.Case;
import com.aworx.lib.enums.Inclusion;


/** ****************************************************************************************
 *  This inner class of AString provides static methods working with character arrays.
 ******************************************************************************************/
public class CString
{
    // #########################################################################################
    //  NEW_LINE_CHARS, DEFAULT_WHITESPACES
    // #########################################################################################

        /** The system depended new line character codes retrieved statically (once) using
            "System.getProperty("line.separator");" */
        public static final     String        NEW_LINE_CHARS  =System.getProperty("line.separator");

        /** Contains all characters that by default get trimmed by trim methods defined
         *  in this class.*/
        public static final     char[]        DEFAULT_WHITESPACES          = {' ','\r','\n','\t' };

        /** A singleton that references a zero-length character array. Used to avoid object
         *  allocation. */
        public static final     char[]        nullBuffer                               =new char[0];

        /**   An empty String singleton */
        public static final     String        EMPTY                                            = "";

    // #########################################################################################
    //  helpers
    // #########################################################################################

        /** ****************************************************************************************
         * Checks if a given CharSequence is empty or has a length of zero.
         *
         * @param cs   The CharSequence to check.
         *
         * @return  Returns true if given String is empty or 0.
         ******************************************************************************************/
        public static boolean isNullOrEmpty( CharSequence cs )
        {
            return      cs == null ||  cs.length() == 0;
        }

        /** ****************************************************************************************
         * Adjusts a given region to fit into the range [0 .. referenceLength].
         *
         * @param referenceLength   Length of the string that the given region will be adjusted to.
         * @param regionStart       The start of the region to be adjusted.
         * @param regionLength      The length of the region to be adjusted.
         * @param target            Array of size 2 that receives the target values.
         *
         * @return  True if adjusted range is empty.
         ******************************************************************************************/
        
        public static boolean adjustRegion(int referenceLength, int regionStart, int regionLength,
                                           int[] target  )
        {
            // if start exceeds string, set to empty range at the end of the string and return true
            if (regionStart >= referenceLength)
            {
                target[0]=    referenceLength;
                target[1]=    0;
                return true; // indicate empty
            }

            // if negative start, cut it from the length
            if (regionStart < 0 )
            {
                regionLength+=    regionStart; // this adds a negative value
                regionStart=    0;             // hence we do not exceed a given MAXINT
            }

            // adjust length
            int maxLen=  referenceLength - regionStart;
            if ( regionLength > maxLen )   regionLength=  maxLen;
            if ( regionLength < 0 )        regionLength= 0;

            // save return values
            target[0]=    regionStart;
            target[1]=    regionLength;

            // return true if adjusted region is empty
            return  regionLength == 0;
        }



    // #########################################################################################
    //  contains at
    // #########################################################################################

        /** ****************************************************************************************
         * Checks if a region of a \e char[] is located at the given position of another \e char[].
         * @param needle        The character array containing the needle.
         * @param needleStart   The index of the start of the needle within the character array.
         * @param needleLength  The length of the needle within the character array.
         * @param haystack      The character array to look in for the needle.
         * @param haystackPos   The position to look at in \p haystack.
         * @param haystackLimit The length of the \p haystack (may be equal or less than 
         *                      haystack.length().
         * @param sensitivity   Case sensitivity of the comparison.
         *
         * @return  \c true if the needle is found at the given position. \c false otherwise.
         ******************************************************************************************/
        static
        public boolean containsAt( char[] needle,    int needleStart, int needleLength, 
                                   char[] haystack,  int haystackPos, int haystackLimit, Case sensitivity )
        {
            int cmpEnd= haystackPos + needleLength;
            if ( haystackPos < 0 || cmpEnd > haystackLimit  || needle == null )
                return false;
            if ( needle == null || needleLength <= 0 )
                return true;

            // the compare loop
            if ( sensitivity == Case.IGNORE )
            {
                while ( haystackPos < cmpEnd )
                {
                    // @SuppressWarnings ("null")
                    if(     Character.toLowerCase( needle  [ needleStart++ ] )
                         != Character.toLowerCase( haystack[ haystackPos++ ] ) )

                        return false;
                }
            }
            else
            {
                while ( haystackPos < cmpEnd )
                {
                    //@SuppressWarnings ("null")
                    if(     needle  [ needleStart++ ] 
                         != haystack[ haystackPos++ ]  )

                        return false;
                }
            }

            return true;
        }


        /** ****************************************************************************************
         * Checks if a \e CharSequence is located in a \e char[] at the given position.
         *
         * @param needle        The string to search.
         * @param haystack      The character array to look in for the needle.
         * @param haystackPos   The position to look at in \p haystack.
         * @param haystackLimit The length of the \p haystack (may be equal or less than 
         *                      haystack.length().
         * @param sensitivity   Case sensitivity of the comparison.
         *
         * @return  \c true if the sequence is found at the given position. \c false otherwise.
         ******************************************************************************************/
        static
        public boolean containsAt( CharSequence needle, 
                                   char[] haystack,  int haystackPos, int haystackLimit, Case sensitivity )
        {
            // check null argument or length 0
            int needleLen=  needle != null ?  needle.length() : 0;
            int cmpEnd= haystackPos + needleLen;
            if ( haystackPos < 0 || cmpEnd > haystackLimit || needle == null )
                return false;
            if ( needleLen == 0 )
                return true;

            // the compare loop
            int nPos= 0;
            if ( sensitivity == Case.IGNORE )
            {
                while ( haystackPos < cmpEnd )
                {
                    // @SuppressWarnings ("null")
                    if(     Character.toLowerCase( needle.charAt( nPos++ ) )
                         != Character.toLowerCase( haystack[ haystackPos++ ] ) )

                        return false;
                }
            }
            else
            {
                while ( haystackPos < cmpEnd )
                {
                    //@SuppressWarnings ("null")
                    if(     needle.charAt( nPos++ )
                         != haystack[ haystackPos++ ]  )

                        return false;
                }
            }

            return true;
        }


    // #########################################################################################
    //  compareTo
    // #########################################################################################

        /** ****************************************************************************************
         * Compares a given region of a CharSequence with the a in a \e char[].<br>
         * No parameter checks are performed. Null and empty checks and proper region bounds
         * have to be provided (this is a helper method for other compareTo methods). 
         *
         * @param needle         An object of type \e CharSequence that is compared to \p haystack.
         * @param needleStart    The start of the region in \p needle that is to be compared. 
         * @param needleLength   The length of the region in \p needle.
         * @param haystack       The character buffer that is compared.
         * @param haystackStart  The start of the substring within \p haystack.
         * @param haystackLength The length of the substring within \p haystack.
         * @param sensitivity    Case sensitivity of the operation.
         *
         * @return
         *  -  0 if \p haystack and \p needle are \e null or if both have a length of 0 or if 
         *     both  share the same content.
         *  - <0 if \p haystack is \e nulled and \p needle is not or if \p haystack is smaller 
         *    than \p needle.
         *  - >0 if \p haystack is not \e nulled but \p needle is or if \p haystack is greater
         *    than \p needle.
         ******************************************************************************************/
        static
        public int compareTo( CharSequence needle,   int   needleStart,    int needleLength,
                              char[]       haystack, int haystackStart,  int haystackLength,
                              Case         sensitivity )
        {
            // compare loop
            int srcIdx=    haystackStart;
            int srcEnd=    haystackStart   + haystackLength;
            int cmpIdx=      needleStart;
            int cmpEnd=      needleStart   +   needleLength;
            while ( true )
            {
                // end of one of the strings or both?
                if (srcIdx >= srcEnd)    return  (cmpIdx >= cmpEnd) ?     0    :    -1;
                if (cmpIdx >= cmpEnd)    return                                      1;

                // compare characters
                char srcC=  haystack[ srcIdx  ];
                char cmpC=  needle.charAt( cmpIdx );
                if ( srcC != cmpC )
                {
                    // no match!
                    if ( sensitivity == Case.SENSITIVE )
                        return srcC - cmpC;

                    // compare ignore case
                    int diff= ( Character.toLowerCase( srcC ) - Character.toLowerCase( cmpC ) );
                    if ( diff != 0 )
                        return diff;
                }

                // next
                srcIdx++; cmpIdx++;
            }
        }

    // #########################################################################################
    //  IndexOf
    // #########################################################################################

    /** ****************************************************************************************
     *  Static method that searches a character in a region of a character array.
     *
     * @param needle          The character to be searched for.
     * @param haystack        Character array that is searched in.
     * @param regionStart     The start of the region within haystack.
     *                        Defaults to 0.
     * @param regionLength    The length of the region within haystack.
     *                        Defaults to Integer.MAX_VALUE.
     *
     * @return The index of the first matching character found.
     *         If nothing is found, -1 is returned.
     ******************************************************************************************/
    public
    static int     indexOf( char needle, char[] haystack, int regionStart, int regionLength )
    {
        // --- adjust region
        //  if start exceeds string, set to empty range at the end of the string and return true
        if (regionStart >= haystack.length)
            return -1;

        // if negative start, cut it from the length
        if (regionStart < 0 )
        {
            regionLength+=    regionStart;
            regionStart=    0;
        }

        // adjust length
        int maxLen=  haystack.length - regionStart;
        if ( regionLength > maxLen )
             regionLength=  maxLen;
        if ( regionLength <= 0 )
            return -1;

        //--- search --
        int e= regionStart + regionLength;
        while( regionStart < e )
        {
            if ( haystack[regionStart] == needle )
                return regionStart;
            regionStart++;
        }

        return -1;
    }

    /** ****************************************************************************************
     *  Static method that searches a character in a character array,
     *  starting at a given index to the end of the array.
     *
     * @param needle          The character to be searched for.
     * @param haystack        Character array that is searched in.
     * @param regionStart     The start of the region within haystack.
     *                        Defaults to 0.
     *
     * @return The index of the first matching character found.
     *         If nothing is found, -1 is returned.
     ******************************************************************************************/
    public
    static int     indexOf( char needle, char[] haystack, int regionStart )
    {
        return CString.indexOf(  needle, haystack, regionStart, Integer.MAX_VALUE );
    }

    /** ****************************************************************************************
     *  Static method that searches a character in a character array.
     *
     * @param needle          The character to be searched for.
     * @param haystack        Character array that is searched in.
     *
     * @return The index of the first matching character found.
     *         If nothing is found, -1 is returned.
     ******************************************************************************************/
    public
    static int     indexOf( char needle, char[] haystack )
    {
        return CString.indexOf(  needle, haystack, 0, Integer.MAX_VALUE );
    }


    /** ****************************************************************************************
     * Searches a \e CharSequence in a region of a character array. 
     *
     * @param needle          The CharSequence to search.
     * @param haystack        Character array that is searched in.
     * @param haystackStart   The start of the region within haystack.
     *                        Defaults to 0.
     * @param haystackLength  The length of the region within haystack.
     *                        Defaults to Integer.MAX_VALUE.
     * @param sensitivity     Case sensitivity of the operation.
     *                        Optional and defaults to Case.Sensitive.
     *
     * @return  \e -1 if the String is not found. Otherwise the index of first occurrence relative
     *          to \p haystackStart.
     ******************************************************************************************/
    public static int indexOfString( CharSequence needle, 
                                     char[] haystack, int haystackStart, int haystackLength, 
                                     Case sensitivity )
    {
        // checks
        int needleLength=  needle != null ?  needle.length() : 0;
        if ( haystackStart <  0 )  haystackStart= 0;
        if ( needleLength  == 0 )  return  haystackStart;

        // case sensitive
        int hayStackEnd= haystackStart + haystackLength;
        if ( sensitivity == Case.SENSITIVE )
        {
            char firstChar= needle.charAt( 0 );     
            while ( haystackStart + needleLength <= hayStackEnd )
            {
                if ( haystack[ haystackStart ] == firstChar )
                {
                    int  cmpLen= 1;
                    while (     cmpLen != needleLength 
                            &&  haystack[ haystackStart + cmpLen ] == needle.charAt( cmpLen ) )
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
            char firstChar= Character.toLowerCase( needle.charAt( 0 ) );
            while ( haystackStart + needleLength <= hayStackEnd )
            {
                if ( Character.toLowerCase( haystack[ haystackStart ] ) == firstChar )
                {
                    int  cmpLen= 1;
                    while (     cmpLen != needleLength 
                            &&     Character.toLowerCase( haystack[ haystackStart + cmpLen ] )  
                                == Character.toLowerCase( needle.charAt( cmpLen ) ) )
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



    /** ****************************************************************************************
     * Static method that returns the index of the first character which is included
     * (alternatively not included) in a given set of characters.
     *
     * This method searches from left to right. For backward search, see
     * \ref lastIndexOfAny
     *
     * @param haystack      The string to be searched.
     * @param regionStart   The start of the region within haystack.
     * @param regionLength  The length of the region within haystack.
     * @param needles       Characters to be searched for.
     * @param inclusion     Denotes whether the search returns the first index that holds a value
     *                      that is included or that is not excluded in the set of needle
     *                      characters.
     *
     * @return The index (relative to the start of the region) of the first character found
     *         which is included, respectively not included, in the given set of characters.
     *         If nothing is found, -1 is returned.
     ******************************************************************************************/
    public
    static int     indexOfAnyInRegion( char[]    haystack, int regionStart, int regionLength,
                                       char[]    needles,  Inclusion inclusion                   )
    {
        int     nbLen=  needles.length;
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

    /** ****************************************************************************************
     * Static method that returns the index of the first character which is included
     * (alternatively not included) in a given set of characters.
     * The search starts at the end of the region and continues towards its start.
     *
     * @param haystack      The string to be searched.
     * @param regionStart   The start of the region within haystack.
     * @param regionLength  The length of the region within haystack.
     * @param needles       An array that holds the characters to be searched for.
     * @param inclusion     Denotes whether the search returns the first index that holds a value
     *                      that is included or that is not excluded in the set of needle
     *                      characters.
     *
     * @return The index relative to the start of the region.
     *         If the search was not successful, then regionStart -1 is returned;
     ******************************************************************************************/
    public
    static int     lastIndexOfAny( char[]    haystack, int regionStart, int regionLength,
                                   char[]    needles,  Inclusion inclusion                   )
    {
        int     nbLen=  needles.length;

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

    /** ****************************************************************************************
     * Search a string within another starting at a given position.
     *
     * @param haystack  The CharSequence to search in.
     * @param needle    The CharSequence to search for.
     * @param startIdx  The index to start the search at. Optional and defaults to 0.
     *
     * @return  -1 if the String is not found. Otherwise the index of first occurrence.
     ******************************************************************************************/
    public static int indexOfIgnoreCase( CharSequence haystack, CharSequence needle, int startIdx )
    {
        // check s1
        if ( haystack == null )
            return -1;
        int sInLen= haystack.length();

        // check s2 null argument or length 0
        int sForLen=  needle != null ?  needle.length() : 0;
        if ( sForLen == 0 || startIdx > sInLen)
            return -1;

        // check start idx < 0
        if ( startIdx < 0 )
            startIdx= 0;

        // search
        @SuppressWarnings ("null")
        char firstChar= Character.toLowerCase( needle.charAt( 0 ) );       
        while ( startIdx < sInLen )
        {
            int        cmpLen= 0;
            char    cFor=    firstChar;
            while ( Character.toLowerCase( haystack.charAt( startIdx + cmpLen )) == cFor )
            {
                cmpLen++;
                if ( cmpLen == sForLen )
                    return startIdx;
                cFor= Character.toLowerCase( needle.charAt( cmpLen ) );
            }
            startIdx++;
        }

        // not found
        return -1;
    }

    /** ****************************************************************************************
     * Search the given String in the Buffer.
     *
     * @param haystack  The CharSequence to search in.
     * @param needle    The CharSequence to search for.
     *
     * @return  -1 if the String is not found. Otherwise the index of first occurrence.
     ******************************************************************************************/
    public static int indexOfIgnoreCase( CharSequence haystack, CharSequence needle )
    {
        return CString.indexOfIgnoreCase( haystack, needle, 0);
    }

    // #########################################################################################
    // starts/endsWith
    // #########################################################################################

    /** ****************************************************************************************
     * Static utility function to check if a string starts with another string with case
     * insensitive compare. Using this function avoids to create two converted (lowered)
     * temporary strings.
     *
     * @param haystack  The CharSequence to search in.
     * @param needle    The CharSequence to search for.
     *
     * @return  true, if given string s starts with given string prefix, false otherwise.
     ******************************************************************************************/
    @SuppressWarnings ("null")
    public static boolean startsWithIgnoreCase( CharSequence haystack, CharSequence needle )
    {
        // check s
        if ( haystack == null )
            return false;
        int haystackLen= haystack.length();

        // check s2 null argument or length 0
        int needleLen=  needle != null ?  needle.length() : 0;
        if ( needleLen == 0 )
            return true;

        // s smaller than prefix
        if ( haystackLen < needleLen )
            return false;

        // comparison loop
        for (int i= 0; i< needleLen; i++ )
            if ( Character.toLowerCase( haystack.charAt( i ) ) != Character.toLowerCase( needle.charAt( i ) ))
                return false;

        // no differences found
        return true;
    }

    /** ****************************************************************************************
     * Static utility function to check if a string ends with another string with case
     * insensitive compare. Using this function avoids to create two converted (lowered)
     * temporary strings.
     *
     * @param haystack  The CharSequence to search in.
     * @param needle    The CharSequence to search for.
     *
     * @return  true, if given string s ends with given string prefix, false otherwise.
     ******************************************************************************************/
    @SuppressWarnings ("null")
    public static boolean endsWithIgnoreCase    ( CharSequence haystack, CharSequence needle )
    {
        // check s
        if ( haystack == null )
            return false;
        int haystackLen= haystack.length();

        // check s2 null argument or length 0
        int needleLen=  needle != null ?  needle.length() : 0;
        if ( needleLen == 0 )
            return true;

        // s smaller than prefix
        if ( haystackLen < needleLen )
            return false;

        // comparison loop
        int haystackIdx= haystackLen - needleLen;
        for (int needleIdx= 0; needleIdx< needleLen; needleIdx++ )
            if (    Character.toLowerCase( haystack.charAt( haystackIdx++ ) )
                 != Character.toLowerCase(   needle.charAt( needleIdx     ) )  )
                return false;

        // no differences found
        return true;
    }

}  //  class CString


