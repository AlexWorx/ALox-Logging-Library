// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

import com.aworx.util.AString;
import com.aworx.util.AString.Align;

/** ************************************************************************************************
 *  This class encapsulates a AString and mimics the interface into it. The reason to have this,
 *  is to allow a java byte code tool to prune all code related to this class. Hence, for debug
 *  logging an instance of this class can be filled and logged and the appropriate byte code tool
 *  can be configured to prune this code away.
 *
 *  Class Log provides a static instance of LogBuf, accessible in a thread safe way, through
 *  method Log.buf().
 **************************************************************************************************/
public class LogBuf
{
    /** ********************************************************************************************
     * The encapsulated AString
     **********************************************************************************************/
    public AString b;

    /** ********************************************************************************************
     * Constructor without specific Buffer size.
     **********************************************************************************************/
    public LogBuf()                                                     { b= new AString(128); }

    /** ********************************************************************************************
     * Constructor with specific Buffer size .
     *
     * @param size  The initial size of the internal buffer
     **********************************************************************************************/
    public LogBuf( int size )                                             { b= new AString(size); }

    /** ********************************************************************************************
     * Constructor copying a CharSequence.
     *
     * @param src    The source AString to copy from.
     **********************************************************************************************/
    public LogBuf( CharSequence src )                                     { b= new AString( src ); }

    /** ********************************************************************************************
     * Constructor copying a substring of a CharSequence.
     *
     * @param src            The source CharSequence to copy from.
     * @param regionStart    The start index in src to append. Defaults to 0.
     **********************************************************************************************/
    public LogBuf( CharSequence src, int regionStart)                     { b= new AString( src, regionStart ); }

    /** ********************************************************************************************
     * Constructor copying a substring of a CharSequence.
     *
     * @param src            The source CharSequence to copy from.
     * @param regionStart    The start index in s to append. Defaults to 0.
     * @param regionLength    The maximum length of the substring in src to append. Defaults to
     *                      Integer.MAX_VALUE.
     **********************************************************************************************/
    public LogBuf( CharSequence src, int regionStart, int regionLength)    { b= new AString( src, regionStart, regionLength ); }


        /** ****************************************************************************************
         *  The internal buffer character array. This may, but should not be accessed directly.
         *  In case of external modifications be sure to adjust the length of this AString using #setLength.
         *
         * @return The internal buffer array.
         ******************************************************************************************/
        public    char[]    buffer()                     { return b.buffer();    }

        /** ****************************************************************************************
         * Gets the length of the sequence.
         * @return  The length of the sequence.
         ******************************************************************************************/
        public int         length()                    {    return b.length();        }


        /** ****************************************************************************************
         *  Set the actual length of the stored string. The string can only be shortened.
         *  To increase the length, use one of the Append methods, e.g. Append( char, int ). To change
         *  the internal allocation size, see #setAllocation.
         *
         * @param newLength        The new length of the AString. Must be smaller than the current length.
         *
         * @return The new length of the string represented by this.
         ******************************************************************************************/
        public    int        setLength( int newLength )    {    return b.setLength( newLength );        }

        /** ****************************************************************************************
         *  Resizes the internal buffer to meet exactly the given size. Attn: If the current string represented
         *  by this instance is larger, the string is cut. This method is deemed for internal use or very
         *  special situations when used from outside.
         *
         * @param newSize    The new size for the allocation buffer. If -1 is given, the current length of
         *                     the AString is used.
         ******************************************************************************************/
        public    void     setAllocation( int newSize)    { b.setAllocation( newSize ); }

        /** ****************************************************************************************
         * Ensures that the capacity of the internal buffer meets or exceeds the given value.
         *
         * @param minLen    The minimum length.
         ******************************************************************************************/
        public void     ensureAllocation( int minLen ) { b.ensureAllocation( minLen ); }

        /** ****************************************************************************************
         * Ensures that the capacity of the internal buffer meets or exceeds the actual length
         * plus the given growth value.
         *
         * @param growth    The desired growth of length.
         ******************************************************************************************/
        public void     ensureAllocationRelative( int growth ) { b.ensureAllocationRelative( growth ); }


        /** ****************************************************************************************
         * Clear the Buffer (just sets Length to 0)
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public LogBuf clear()                                                         { b.clear();                    return this; }

        /** ****************************************************************************************
         *    Deletes a region from the Buffer.
         *  Note: To delete all contents use #clear.
         *
         * @param regionStart    The start of the region to delete.
         * @param regionLength   The length of the region to delete. Defaults to Integer.MAX_VALUE.
         *
         * <returns> '*this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public    LogBuf    delete( int regionStart, int regionLength )                { b.delete( regionStart, regionLength );    return this; }

        /** ****************************************************************************************
         *    Deletes the end of the Buffer starting at the given index.
         *  Note: To delete all contents use #clear.
         *
         * @param regionStart    The start of the region to delete.
         *
         * <returns> 'this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public    LogBuf delete( int regionStart )                                { b.delete( regionStart, Integer.MAX_VALUE );    return this; }

        /** ****************************************************************************************
         *    Inserts a region into the Buffer. The region gets filled with the given character.
         *
         * @param regionStart    The start of the region to insert. If this is out of the string
         *                       bounds (hence less than 0 or greater then #length, nothing is done.
         * @param regionLength   The length of the region to insert.
         * @param fillChar       (Optional) The character to fill the new region with.
         *                       Defaults to ' ' (space).
         *
         * @return 'this' to allow concatenated calls.
         ******************************************************************************************/
        public    LogBuf insert( int regionStart, int regionLength, char fillChar ) { b.insert( regionStart, regionLength, fillChar );    return this; }

        /** ****************************************************************************************
         *    Inserts a region into the Buffer. The region gets filled with spaces (' ').
         *
         * @param regionStart    The start of the region to insert. If this is out of the string
         *                       bounds (hence less than 0 or greater then #length, nothing is done.
         * @param regionLength   The length of the region to insert.
         *
         * <returns> '*this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public    LogBuf insert( int regionStart, int regionLength )                  { b.insert( regionStart, regionLength, ' ' );    return this; }


        /** ****************************************************************************************
         * Appends platform specific new line character(s). ( "\\r\\n", "\\r", etc.). The new length of the
         * string is recorded as the reference position for #tab.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public LogBuf newLine()                                            { b.newLine();                             return this; }

        /** ****************************************************************************************
         * Go to the next tab stop by filling in pad characters repeatedly. The tab position is relative
         * to the starting of the current line (if subsequent calls to #newLine where performed).
         * @param tabSize       The tab positions are multiples of this parameter.
         * @param minPad        (Optional) The minimum pad characters to add. Defaults to 1.
         * @param padChar       (Optional) The character to insert to reach the tag position.
         *                      Defaults to ' ' (space).
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public LogBuf tab( int tabSize, int minPad, char padChar)        { b.tab( tabSize,    minPad,    padChar );    return this; }

        /** ****************************************************************************************
         * If invoked without parameters, the start of a field is marked at the current end of the string.
         * Otherwise the end of a field is set and the contents between the field start marker and the
         * current end of the string is aligned within the field using the given pad character.
         * Note: To implement nested fields, the outer fields have to be set by providing the start marker
         * by using the parameter fieldStart. Hence, only the starting points of the most inner fields
         * can be set using this method without parameters.
         *
         * @param size           The field size in relation to the starting index of the field, defined either by
         *                       using Field() prior to this invocation or by providing the parameter fieldStart.
         *                       The field gets filled with the given pad character to meet the size
         *                       while the content gets aligned left, right or centered.
         *                       If the content exceeds the size, then no alignment takes place.
         * @param alignment      The alignment of the contents within the field. Defaults to AString.Align.RIGHT.
         *                       Other options are AString.Align.LEFT and AString.Align.CENTER.
         * @param padChar        The character used to fill the field up to its size.
         *                       Defaults to ' ' (space).
         * @param fieldStart     This parameter, if given, overwrites the start index of the field.
         *                       The invocation of field can be omitted, when this value is explicitly
         *                       provided.
         *                       Defaults to Integer.MAX_VALUE.
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public LogBuf field( int size, Align alignment, char padChar, int fieldStart )    { b.field( size, alignment, padChar, fieldStart);    return this; }



        /** ****************************************************************************************
         * Closes and formats a field of the given size. Contents is aligned as specified.
         * The Field is fill with the character provided.
         * See variants of this method for more information.
         *
         * @param size            The field size in relation to the starting index of the field, defined either by
         *                        using Field() prior to this invocation or by providing the parameter fieldStart.
         *                        The field gets filled with the given pad character to meet the size
         *                        while the content gets aligned left, right or centered.
         *                        If the content exceeds the size, then no alignment takes place.
         * @param alignment       The alignment of the contents within the field. Defaults to AString.Align.RIGHT.
         *                        Other options are AString.Align.LEFT and AString.Align.CENTER.
         * @param padChar         The character used to fill the field up to its size.
         *                        Defaults to ' ' (space).
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public LogBuf field( int size, Align alignment, char padChar  )                { b.field( size, alignment, padChar, Integer.MAX_VALUE );    return this; }

        /** ****************************************************************************************
         * Closes and formats a field of the given size. Contents is aligned as specified.
         * The Field is fill with spaces to reach the size.
         * See variants of this method for more information.
         *
         * @param size            The field size in relation to the starting index of the field, defined by
         *                        using Field() prior to this invocation.
         * @param alignment       The alignment of the contents within the field. Defaults to AString.Align.RIGHT.
         *                        Other options are AString.Align.LEFT and AString.Align.CENTER.
         * @return  'this' to allow concatenated calls.
         *************************************************************************************************/
        public LogBuf field( int size, Align alignment )                            { b.field( size, alignment, ' ', Integer.MAX_VALUE );    return this; }

        /** ****************************************************************************************
         * Closes and formats a field of the given size. Contents is aligned right. The Field is fill with
         * spaces to reach the size.
         * See variants of this method for more information.
         *
         * @param size            The field size in relation to the starting index of the field, defined by
         *                        using Field() prior to this invocation.
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public LogBuf field( int size )                                                { b.field( size, AString.Align.RIGHT, ' ', Integer.MAX_VALUE );    return this; }

        /** ****************************************************************************************
         * Marks the start of a field.
         * See variants of this method for more information.
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public LogBuf field()                                                        { b.field( -1, AString.Align.RIGHT, ' ', Integer.MAX_VALUE );    return this; }


    // #############################################################################################
    // Public interface
    // #############################################################################################

    /** ********************************************************************************************
     * Append a CharSequence.
     *
     * @param src    The CharSequence to append.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf append( CharSequence src )                                    { b.append( src );                    return this; }

    /** ********************************************************************************************
     * Append a substring of a CharSequence.
     *
     * @param src            The CharSequence to append.
     * @param regionStart    The index in ms to start from.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf append( CharSequence src, int regionStart )                    { b.append( src, regionStart );        return this; }

    /** ********************************************************************************************
     * Append a substring of a CharSequence.
     *
     * @param src            The CharSequence to append.
     * @param regionStart    The index in src to start from.
     * @param regionLength   The maximum length of the substring in src to append. Defaults to
     *                       Integer.MAX_VALUE.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf append( CharSequence src, int regionStart, int regionLength )    { b.append( src, regionStart, regionLength );    return this; }


    /** ********************************************************************************************
     * Append the given character.
     *
     * @param c The character to append.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf append( char c )                                                 { b.append( c );                        return this; }

    /** ********************************************************************************************
     * Append the given character repeatedly.
     *
     * @param c     The character to append.
     * @param qty   The quantity of characters to append.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf append( char c, int qty )                                        { b.append( c, qty );                        return this; }


    /** ********************************************************************************************
     * Append the given unsigned 32-Bit integer value using a minimum number of digits.
     *
     * @param i         The integer value to append.
     * @param minDigits The minimum number of digits to append. If the number has less digits than
     *                  minDigits, then trailing '0's are added. Optional and defaults to 0.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf append( int i, int minDigits )                                { b.append( i, minDigits );     return this; }

    /** ********************************************************************************************
     * Append the given unsigned 32-Bit integer value.
     *
     * @param i     The integer value to append.
     * @return      'this' to allow concatenated calls.
     **********************************************************************************************/

    public LogBuf append( int i )                                                 { b.append( i, 1 ); return this;}

    /** ********************************************************************************************
     * Append the given double value using the minimum digits before and after the given number of
     * digits after dot.
     *
     * @param d                     the integer value to append.
     * @param minDigitsBeforeDot    The minimum number of digits write before the dot. If the number
     *                              has less digits than minDigits, then trailing '0's. are added.
     *                              Defaults to 0.
     * @param digitsAfterDot        The exact number of digits written after the dot.
     *                              Defaults to 5.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf append( double d, int minDigitsBeforeDot, int digitsAfterDot ) { b.append( d, minDigitsBeforeDot, digitsAfterDot ); return this;}

    /** ********************************************************************************************
     * Append the given double value using the minimum digits before and a fixed number of five
     * digits after dot.
     *
     * @param d                     the integer value to append.
     * @param minDigitsBeforeDot    The minimum number of digits write before the dot. If the number
     *                              has less digits than minDigits, then trailing '0's. are added.
     *                              Defaults to 0.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf append( double d, int minDigitsBeforeDot)                     { b.append( d, minDigitsBeforeDot, 5 ); return this;}

    /** ********************************************************************************************
     * Append the given double value using a fixed number of five  digits after dot.
     *
     * @param d The double value to append.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf append( double d )                                            { b.append( d, 0, 5 ); return this;}

    /** ********************************************************************************************
     * Go to the next tab stop by filling in spaces repeatedly. The tab position is relative
     * to the starting of the current line (if subsequent calls to #newLine where performed).
     *
     * @param tabSize       The tab positions are multiples of this parameter.
     * @param minPad        The minimum pad characters to add. Defaults to 1.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf tab( int tabSize, int minPad)                            { b.tab( tabSize,    minPad,    ' ' );         return this; }

    /** ********************************************************************************************
     * Go to the next tab stop by filling in spaces repeatedly. A minimum of one space is inserted.
     * The tab position is relative to the starting of the current line (if subsequent calls to #newLine
     * where performed).
     *
     * @param tabSize   The tab positions are multiples of this parameter.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf tab( int tabSize )                                     {  b.tab( tabSize,    1,        ' ' );        return this; }

    /** ********************************************************************************************
     * Checks if the given String is located at the given position.
     *
     * @param needle        The string to search.
     * @param pos           The to look at.
     * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
     *
     * @return  True if the given sequence is found at the given position. False otherwise .
     **********************************************************************************************/
    public boolean containsAt( CharSequence needle, int pos, boolean ignoreCase )    { return b.containsAt( needle, pos, ignoreCase); }

    /** ********************************************************************************************
     * Checks if the given String is located at the given position.
     *
     * @param needle        The string to search.
     * @param pos           The to look at.
     *
     * @return  True if the given sequence is found at the given position. False otherwise .
     **********************************************************************************************/
    public boolean containsAt( CharSequence needle, int pos )                        { return b.containsAt( needle, pos, false ); }

    /** ********************************************************************************************
     * Checks if this AString starts with the given sequence.
     *
     * @param needle        The CharSequence to search. If s is null or empty, false is returned.
     * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
     *
     * @return  true if this starts with the given sequence, false if not.
     **********************************************************************************************/
    public boolean startsWith( CharSequence needle, boolean ignoreCase )         { return b.containsAt( needle, 0, ignoreCase );    }

    /** ********************************************************************************************
     * Checks if this AString starts with the given sequence.
     *
     * @param needle The String to search. If s is null or empty, false is returned.
     *
     * @return  true if this starts with the given sequence, false if not.
     **********************************************************************************************/
    public boolean startsWith( CharSequence needle )                            { return b.containsAt( needle, 0, false );    }

    /** ********************************************************************************************
     * Checks if this AString ends with the given sequence.
     *
     * @param needle The CharSequence to search. If s is null or empty, false is returned.
     * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
     *
     * @return  true if this starts with the given sequence, false if not.
     **********************************************************************************************/
    public boolean endsWith  ( CharSequence needle, boolean ignoreCase )        { return b.containsAt( needle, b.length() - needle.length(), ignoreCase );     }

    /** ********************************************************************************************
     * Checks if this AString ends with the given sequence.
     *
     * @param needle The String to search. If s is null or empty, false is returned.
     *
     * @return  true if this starts with the given sequence, false if not.
     **********************************************************************************************/
    public boolean endsWith  ( CharSequence needle )                            { return b.containsAt( needle, b.length() - needle.length(), false ); }

    /** ********************************************************************************************
     * Search the given String in the Buffer starting at a given position.
     *
     * @param s         The string to search.
     * @param startIdx  The index to start the search at. Optional and defaults to 0.
     *
     * @return  -1 if the String is not found. Otherwise the index of first occurrence.
     **********************************************************************************************/
    public int indexOf( CharSequence s, int startIdx )                            { return b.indexOf( s, startIdx ); }

    /** ********************************************************************************************
     * Search the given String in the Buffer.
     *
     * @param s         The string to search.
     * @return  -1 if the String is not found. Otherwise the index of first occurrence.
     **********************************************************************************************/
    public int indexOf( CharSequence s )                                        { return b.indexOf( s, 0 ); }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. Returns the number
     *  of replacements. Use #replace() to allow concatenated operations.
     *
     * @param searchStr         The CharSequence to be replaced.
     * @param newStr            The replacement string.
     * @param startIdx          The index where the search starts. Optional and defaults to 0.
     * @param maxReplacements   The maximum number of replacements to perform. Optional and
     *                          defaults to Integer.MAX_VALUE .
     * @param ignoreCase        If true, a case insensitive search is performed. Defaults to false.
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public int replaceCount( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements, boolean ignoreCase ) { return b.replaceCount( searchStr, newStr, startIdx, maxReplacements, ignoreCase ); }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. Returns the number
     *  of replacements. Use #replace() to allow concatenated operations.
     *
     * @param searchStr         The string to be replaced.
     * @param newStr            The replacement string.
     * @param startIdx          The index where the search starts. Optional and defaults to 0.
     * @param maxReplacements   The maximum number of replacements to perform. Optional and
     *                          defaults to Integer.MAX_VALUE .
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public int replaceCount( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements ) { return b.replaceCount( searchStr, newStr, startIdx, maxReplacements, false ); }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. Returns the number
     *  of replacements. Use #replace() to allow concatenated operations.
     *
     * @param searchStr The string to be replaced.
     * @param newStr    The replacement string.
     * @param startIdx  The index where the search starts. Optional and defaults to 0.
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public int replaceCount( CharSequence searchStr, CharSequence newStr, int startIdx ) { return b.replaceCount( searchStr, newStr, startIdx, Integer.MAX_VALUE, false ); }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. Returns the number
     *  of replacements. Use #replace() to allow concatenated operations.
     *
     * @param searchStr The string to be replaced.
     * @param newStr    The replacement string.
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public int replaceCount( CharSequence searchStr, CharSequence newStr)         { return b.replaceCount( searchStr, newStr, 0,        Integer.MAX_VALUE, false ); }


    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. To receive the number of
     *  Replacements, see alternative method #replaceCount().
     *
     * @param searchStr         The CharSequence to be replaced.
     * @param newStr            The replacement string.
     * @param startIdx          The index where the search starts. Optional and defaults to 0.
     * @param maxReplacements   The maximum number of replacements to perform. Optional and
     *                          defaults to Integer.MAX_VALUE .
     * @param ignoreCase        If true, a case insensitive search is performed. Defaults to false.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf replace( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements, boolean ignoreCase )    { b.replaceCount( searchStr, newStr, startIdx, maxReplacements, ignoreCase); return this; }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. To receive the number of
     *  Replacements, see alternative method #replaceCount().
     *
     * @param searchStr         The string to be replaced.
     * @param newStr            The replacement string.
     * @param startIdx          The index where the search starts. Optional and defaults to 0.
     * @param maxReplacements   The maximum number of replacements to perform. Optional and
     *                          defaults to Integer.MAX_VALUE .
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public LogBuf replace( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements ) { b.replaceCount( searchStr, newStr, startIdx, maxReplacements, false ); return this; }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. To receive the number of
     *  Replacements, see alternative method #replaceCount().
     *
     * @param searchStr The string to be replaced.
     * @param newStr    The replacement string.
     * @param startIdx  The index where the search starts. Optional and defaults to 0.
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public LogBuf replace( CharSequence searchStr, CharSequence newStr, int startIdx )    { b.replaceCount( searchStr, newStr, startIdx, Integer.MAX_VALUE, false ); return this; }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. To receive the number of
     *  Replacements, see alternative method #replaceCount().
     *
     * @param searchStr The string to be replaced.
     * @param newStr    The replacement string.
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public LogBuf replace( CharSequence searchStr, CharSequence newStr)         { b.replaceCount( searchStr, newStr, 0, Integer.MAX_VALUE, false ); return this; }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp   An object of type String, StringBuffer or AString that is compared to this.
     *
     * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
     *         follows the given string (same as String.CompareTo), or if given string in null.
     **********************************************************************************************/
    public int compareTo(    CharSequence cmp )                                    { return b.compareTo( cmp ); }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp           An object of type String, StringBuffer or AString that is compared to
     *                      this.
     * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
     *
     * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
     *         follows the given string (same as String.CompareTo), or if given string in null.
     **********************************************************************************************/
    public int compareTo(    CharSequence cmp, boolean ignoreCase )                { return b.compareTo( cmp, ignoreCase, 0, Integer.MAX_VALUE, 0, Integer.MAX_VALUE ); }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp           An object of type String, StringBuffer or AString that is compared to
     *                      this.
     * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
     * @param sStartIdx     The start of the substring within the given string that is to be compared
     *                      to this. Defaults to 0.
     *
     * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
     *         follows the given string (same as String.CompareTo), or if given string in null.
     **********************************************************************************************/
    public int compareTo(    CharSequence cmp, boolean ignoreCase, int sStartIdx )    { return b.compareTo( cmp, ignoreCase, sStartIdx, Integer.MAX_VALUE, 0, Integer.MAX_VALUE ); }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp           An object of type String, StringBuffer or AString that is compared to
     *                      this.
     * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
     * @param sStartIdx     The start of the substring within the given string that is to be compared
     *                      to this. Defaults to 0.
     * @param sLen          The length of the substring within the given string that is to be
     *                      compared to this. Defaults to Integer.MAX_VALUE.
     *
     * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
     *         follows the given string (same as String.CompareTo), or if given string in null.
     **********************************************************************************************/
    public int compareTo(    CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen )    { return b.compareTo( cmp, ignoreCase, sStartIdx, sLen, 0, Integer.MAX_VALUE );    }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp           An object of type String, StringBuffer or AString that is compared to
     *                      this.
     * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
     * @param sStartIdx     The start of the substring within the given string that is to be compared
     *                      to this. Defaults to 0.
     * @param sLen          The length of the substring within the given string that is to be
     *                      compared to this. Defaults to Integer.MAX_VALUE.
     * @param startIdx      The start of the substring within this that is to be compared. Defaults
     *                      to 0.
     *
     * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
     *         follows the given string (same as String.CompareTo), or if given string in null.
     **********************************************************************************************/
    public int compareTo(    CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen, int startIdx )    {    return b.compareTo( cmp, ignoreCase, sStartIdx, sLen, startIdx, Integer.MAX_VALUE ); }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp           An object of type String, StringBuffer or AString that is compared to
     *                      this.
     * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
     * @param sStartIdx     The start of the substring within the given string that is to be compared
     *                      to this. Defaults to 0.
     * @param sLen          The length of the substring within the given string that is to be
     *                      compared to this. Defaults to Integer.MAX_VALUE.
     * @param startIdx      The start of the substring within this that is to be compared. Defaults
     *                      to 0.
     * @param len           The length of the substring within this that is to be compared.
     *                       Defaults to Integer.MAX_VALUE.
     *
     * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
     *         follows the given string (same as String.CompareTo), or if given string in null.
     **********************************************************************************************/
    public int compareTo(    CharSequence cmp, boolean ignoreCase, int sStartIdx, int sLen, int startIdx, int len ){    return b.compareTo( cmp, ignoreCase, sStartIdx, sLen, startIdx,    len ); }

    /** ********************************************************************************************
     * Converts all or a region of characters in the Buffer to upper or to lower case.
     *
     * @param toUpper   If true, conversion to upper case is performed, to lower else.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf convertCase( boolean toUpper )                                { b.convertCase( toUpper, 0,            Integer.MAX_VALUE ); return this;}

    /** ********************************************************************************************
     * Converts all or a region of characters in the Buffer to upper or to lower case.
     *
     * @param toUpper       If true, conversion to upper case is performed, to lower else.
     * @param substrStart   Start of the substring to be converted. Defaults to 0.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf convertCase( boolean toUpper, int substrStart  )                { b.convertCase( toUpper, substrStart,    Integer.MAX_VALUE ); return this;}

    /** ********************************************************************************************
     * Converts all or a region of characters in the Buffer to upper or to lower case.
     *
     * @param toUpper       If true, conversion to upper case is performed, to lower else.
     * @param substrStart   Start of the substring to be converted. Defaults to 0.
     * @param substrLength  Length of the substring to be converted. Defaults to Integer.MAX_VALUE.
     *
     * @return  'this' to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf convertCase( boolean toUpper, int substrStart, int substrLength ){ b.convertCase( toUpper, substrStart,    substrLength); return this;}

    /** ********************************************************************************************
     * Converts the LogBuf into a String.
     *
     * @return  A string that represents this object.
     **********************************************************************************************/
    @Override public String toString()        {    return b.toString();    }

    /** ********************************************************************************************
     * Copies a region of the contents of this AString into the given StringBuilder.
     *
     * @param result        A result StringBuilder to copy the specified region into.
     * @param regionStart     The start index of the region to be copied.
     * @param regionLength    The maximum length of the region to be copied.
     * @param appendMode    If true, any contents in the result is preserved. Otherwise such content
     *                        gets replaced.
     * @return  The (modified) result that was provided (for concatenation of calls).
     **********************************************************************************************/
    public StringBuilder toString( StringBuilder result, int regionStart, int regionLength, boolean appendMode ) { return b.toString( result, regionStart, regionLength, appendMode ); }

}

