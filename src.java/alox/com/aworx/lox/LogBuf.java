// #################################################################################################
//  com.aworx.lox - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
package com.aworx.lox;

import com.aworx.lib.enums.Alignment;
import com.aworx.lib.enums.Case;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.NumberFormat;

/** ************************************************************************************************
 *  This class encapsulates an AString and mimics the interface into it. The reason to have this,
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
    public LogBuf()
    {
        b= new AString( 128 );
    }

    /** ********************************************************************************************
     * Constructor with specific Buffer size .
     *
     * @param size  The initial size of the internal buffer
     **********************************************************************************************/
    public LogBuf(int size)
    {
        b= new AString( size );
    }

    /** ********************************************************************************************
     * Constructor copying a CharSequence.
     *
     * @param src    The source AString to copy from.
     **********************************************************************************************/
    public LogBuf(CharSequence src)
    {
        b= new AString( src );
    }

    /** ********************************************************************************************
     * Constructor copying a substring of a CharSequence.
     *
     * @param src            The source CharSequence to copy from.
     * @param regionStart    The start index in src to append. Defaults to 0.
     **********************************************************************************************/
    public LogBuf(CharSequence src, int regionStart)
    {
        b= new AString( src, regionStart );
    }

    /** ********************************************************************************************
     * Constructor copying a substring of a CharSequence.
     *
     * @param src            The source CharSequence to copy from.
     * @param regionStart    The start index in s to append. Defaults to 0.
     * @param regionLength    The maximum length of the substring in src to append. Defaults to
     *                      Integer.MAX_VALUE.
     **********************************************************************************************/
    public LogBuf(CharSequence src, int regionStart, int regionLength)
    {
        b= new AString( src, regionStart, regionLength );
    }

    /** ********************************************************************************************
     * Clear the Buffer (just sets Length to 0)
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf clear()
    {
        b.clear();
        return this;
    }

    /** ********************************************************************************************
     * Clear the Buffer. Same as #clear(), really just a synonym to allow short code in
     * alignment with the various "Append" methods named <em>_(src)</em>
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _()
    {
        b.clear();
        return this;
    }

    /** ********************************************************************************************
     *    Deletes a region from the Buffer.
     *  Note: To delete all contents use #clear.
     *
     * @param regionStart    The start of the region to delete.
     * @param regionLength   The length of the region to delete. Defaults to Integer.MAX_VALUE.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf delete(int regionStart, int regionLength)
    {
        b.delete( regionStart, regionLength );
        return this;
    }

    /** ********************************************************************************************
     *    Deletes the end of the Buffer starting at the given index.
     *  Note: To delete all contents use #clear.
     *
     * @param regionStart    The start of the region to delete.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf delete(int regionStart)
    {
        b.delete( regionStart, Integer.MAX_VALUE );
        return this;
    }

    /** ****************************************************************************************
     * Inserts a string at a given position.
     * If the given position is out of range, nothing is inserted.
     *
     * \note
     *   To insert a string with replacing a different one at the same time, use
     *   one of the overloaded methods #replaceSubstring.
     *
     * @param  src      The \e CharSequence to insert characters from.
     * @param  pos      The position in this object insert the portion of \p src.
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf insertAt( CharSequence src, int pos )
    {
        b.insertAt( src, pos );
        return this;
    }

    /** ****************************************************************************************
     * Inserts the given character n-times at a given position.
     * The given position gets adjusted to the range of this object.
     *
     * @param c     The character to insert \p qty times.
     * @param qty   The quantity of characters to insert.
     * @param pos   The index in this object where \p c is inserted \p qty times.
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf insertChars( char c, int qty, int pos )
    {
        b.insertChars( c, qty, pos );
        return this;
    }

    /** ****************************************************************************************
     * Replaces a substring in this object by a given string.
     * If the region does not fit to this object, then nothing is done.
     *
     * @param src             The replacement CharSequence.
     * @param regionStart     The start of the region.
     * @param regionLength    The length of the region.
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf  replaceSubstring( CharSequence src, int regionStart, int regionLength )
    {
        b.replaceSubstring( src, regionStart, regionLength );
        return this;
    }

    /** ****************************************************************************************
     *  Replaces a region in the string with the given character.
     *  The region is adjusted to fit into the current length. In other words, the length
     *  of this instances remains the same.
     *
     * \note
     *   To replace a region with a single character (by shrinking the region to this character)
     *   use
     *   \ref replaceSubstring "replaceSubstring( "" + c, regionStart, regionLength)".
     *
     * @param c               The character to set in the region.
     * @param regionStart     The start of the region
     * @param regionLength    The length of the region
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf replaceRegion( char c, int regionStart, int regionLength )
    {
        b.replaceRegion( c, regionStart,  regionLength );
        return this;
    }

    /** ********************************************************************************************
     * Appends platform specific new line character(s). ( "\\r\\n", "\\r", etc.). The new length of
     * the string is recorded as the reference position for #tab.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf newLine()
    {
        b.newLine();
        return this;
    }

    /** ********************************************************************************************
     * Go to the next tab stop by filling in pad characters repeatedly. The tab position is relative
     * to the starting of the current line (if subsequent calls to #newLine where performed).
     * @param tabSize       The tab positions are multiples of this parameter.
     * @param minPad        (Optional) The minimum pad characters to add. Defaults to 1.
     * @param padChar       (Optional) The character to insert to reach the tag position.
     *                      Defaults to ' ' (space).
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf tab(int tabSize, int minPad, char padChar)
    {
        b.tab( tabSize, minPad, padChar );
        return this;
    }

    /** ********************************************************************************************
     * If invoked without parameters, the start of a field is marked at the current end of the string.
     * Otherwise the end of a field is set and the contents between the field start marker and the
     * current end of the string is aligned within the field using the given pad character.
     * Note: To implement nested fields, the outer fields have to be set by providing the start marker
     * by using the parameter fieldStart. Hence, only the starting points of the most inner fields
     * can be set using this method without parameters.
     *
     * @param size           The field size in relation to the starting index of the field, defined
     *                       either by using Field() prior to this invocation or by providing the
     *                       parameter fieldStart.
     *                       The field gets filled with the given pad character to meet the size
     *                       while the content gets aligned left, right or centered.
     *                       If the content exceeds the size, then no alignment takes place.
     * @param alignment      The alignment of the contents within the field. Defaults to
     *                       ALIB.Align.RIGHT.
     *                       Other options are ALIB.Align.LEFT and ALIB.Align.CENTER.
     * @param padChar        The character used to fill the field up to its size.
     *                       Defaults to ' ' (space).
     * @param fieldStart     This parameter, if given, overwrites the start index of the field.
     *                       The invocation of field can be omitted, when this value is explicitly
     *                       provided.
     *                       Defaults to Integer.MAX_VALUE.
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf field(int size, Alignment alignment, char padChar, int fieldStart)
    {
        b.field( size, alignment, padChar, fieldStart );
        return this;
    }



    /** ********************************************************************************************
     * Closes and formats a field of the given size. Contents is aligned as specified.
     * The Field is fill with the character provided.
     * See variants of this method for more information.
     *
     * @param size            The field size in relation to the starting index of the field, defined
     *                        either by using Field() prior to this invocation or by providing the
     *                        parameter fieldStart.
     *                        The field gets filled with the given pad character to meet the size
     *                        while the content gets aligned left, right or centered.
     *                        If the content exceeds the size, then no alignment takes place.
     * @param alignment       The alignment of the contents within the field. Defaults to
     *                        ALIB.Align.RIGHT.
     *                        Other options are ALIB.Align.LEFT and ALIB.Align.CENTER.
     * @param padChar         The character used to fill the field up to its size.
     *                        Defaults to ' ' (space).
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf field(int size, Alignment alignment, char padChar)
    {
        b.field( size, alignment, padChar, Integer.MAX_VALUE );
        return this;
    }

    /** ********************************************************************************************
     * Closes and formats a field of the given size. Contents is aligned as specified.
     * The Field is fill with spaces to reach the size.
     * See variants of this method for more information.
     *
     * @param size            The field size in relation to the starting index of the field, defined by
     *                        using Field() prior to this invocation.
     * @param alignment       The alignment of the contents within the field. Defaults to
     *                        ALIB.Align.RIGHT.
     *                        Other options are ALIB.Align.LEFT and ALIB.Align.CENTER.
     * @return  \c this to allow concatenated calls.
     *************************************************************************************************/
    public LogBuf field(int size, Alignment alignment)
    {
        b.field( size, alignment, ' ', Integer.MAX_VALUE );
        return this;
    }

    /** ********************************************************************************************
     * Closes and formats a field of the given size. Contents is aligned right. The Field is fill
     * withspaces to reach the size.
     * See variants of this method for more information.
     *
     * @param size            The field size in relation to the starting index of the field, defined
     *                        by using Field() prior to this invocation.
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf field(int size)
    {
        b.field( size, Alignment.RIGHT, ' ', Integer.MAX_VALUE );
        return this;
    }

    /** ********************************************************************************************
     * Marks the start of a field.
     * See variants of this method for more information.
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf field()
    {
        b.field( -1, Alignment.RIGHT, ' ', Integer.MAX_VALUE );
        return this;
    }

    /** ********************************************************************************************
     * Append a CharSequence.
     *
     * @param src    The CharSequence to append.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _(CharSequence src)
    {
        b._( src );
        return this;
    }

    /** ********************************************************************************************
     * Append a substring of a CharSequence.
     *
     * @param src            The CharSequence to append.
     * @param regionStart    The index in ms to start from.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _(CharSequence src, int regionStart)
    {
        b._( src, regionStart );
        return this;
    }

    /** ********************************************************************************************
     * Append a substring of a CharSequence.
     *
     * @param src            The CharSequence to append.
     * @param regionStart    The index in src to start from.
     * @param regionLength   The maximum length of the substring in src to append. Defaults to
     *                       Integer.MAX_VALUE.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _(CharSequence src, int regionStart, int regionLength)
    {
        b._( src, regionStart, regionLength );
        return this;
    }


    /** ********************************************************************************************
     * Append the given character.
     *
     * @param c The character to append.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _(char c)
    {
        b._( c );
        return this;
    }

    /** ********************************************************************************************
     * Append the given character repeatedly.
     *
     * @param c     The character to append.
     * @param qty   The quantity of characters to append.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf insertChars(char c, int qty)
    {
        b.insertChars( c, qty );
        return this;
    }


    /** ********************************************************************************************
     *  Convert and append the given 32-Bit integer value.
     *
     * @param value        The integer value to append.
     * @param minDigits    The minimum number of digits to append.
     *                     If given value has less digits, '0' characters are prepended.
     *                     The given value is cut to the range 1..19 (max digits of a 64 bit
     *                     integer, which is the largest integer processed
     *                     in overloaded methods).<br>
     *                     Optional and defaults to 1.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _( int value, int minDigits )
    {
        b._(  value, minDigits );
        return this;
    }

    /** ********************************************************************************************
     *  Convert and append the given 32-Bit integer value.
     *
     * @param value        The integer value to append.
     * @return      \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _( int value )
    {
        b._( value, 1 );
        return this;
    }

    /** ********************************************************************************************
     *  Convert and append the given 64-Bit integer value.
     *
     * @param value        The integer value to append.
     * @param minDigits    The minimum number of digits to append.
     *                     If given value has less digits, '0' characters are prepended.
     *                     The given value is cut to the range 1..19 (max digits of a 64 bit
     *                     integer, which is the largest integer processed
     *                     in overloaded methods).<br>
     *                     Optional and defaults to 1.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _( long value, int minDigits )
    {
        b._(  value, minDigits );
        return this;
    }

    /** ********************************************************************************************
     *  Convert and append the given 64-Bit integer value.
     *
     * @param value The integer value to append.
     * @return \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _( long value )
    {
        b._(  value, 1 );
        return this;
    }


    /** ********************************************************************************************
     *  Appends a double value as string representation.
     *  The conversion is performed by an object of class
     *  \ref com::aworx::lib::strings::NumberFormat "NumberFormat".
     *  If no object of this type is provided with optional parameter \p numberFormat,
     *  the static default object found in
     *  \ref com::aworx::lib::strings::NumberFormat::global "NumberFormat.global" is used.
     *
     * @param value        The double value to append.
     * @param numberFormat The object performing the conversion and defines the output format.
     *                     Optional and defaults to null.
     *
     * @return    \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _( double value, NumberFormat numberFormat )
    {
        b._( value, numberFormat );
        return this;
    }

    /** ********************************************************************************************
     *  Appends a double value as string representation.
     *  The conversion is performed using
     *  \ref com::aworx::lib::strings::NumberFormat::global "NumberFormat.global".
     *
     *  The overloaded method #_(double, NumberFormat)
     *  allows to explicitly provide a dedicated conversion object.
     *
     * @param value  The double value to append.
     *
     * @return    \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf _( double value )
    {
        b._ ( value, NumberFormat.global );
        return this;
    }

    /** ********************************************************************************************
     * Go to the next tab stop by filling in spaces repeatedly. The tab position is relative
     * to the starting of the current line (if subsequent calls to #newLine where performed).
     *
     * @param tabSize       The tab positions are multiples of this parameter.
     * @param minPad        The minimum pad characters to add. Defaults to 1.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf tab(int tabSize, int minPad)
    {
        b.tab( tabSize, minPad, ' ' );
        return this;
    }

    /** ********************************************************************************************
     * Go to the next tab stop by filling in spaces repeatedly. A minimum of one space is inserted.
     * The tab position is relative to the starting of the current line (if subsequent calls to
     * #newLine where performed).
     *
     * @param tabSize   The tab positions are multiples of this parameter.
     *
     * @return  \c this to allow concatenated calls.
     **********************************************************************************************/
    public LogBuf tab(int tabSize)
    {
        b.tab( tabSize, 1, ' ' );
        return this;
    }

    /** ********************************************************************************************
     * Checks if the given String is located at the given position.
     *
     * @param needle        The string to search.
     * @param pos           The to look at.
     * @param sensitivity   Case sensitivity of the operation.
     *                      Optional and defaults to CaseSensitive.YES.
     *
     * @return  True if the given sequence is found at the given position. False otherwise .
     **********************************************************************************************/
    public boolean containsAt(CharSequence needle, int pos, Case sensitivity)
    {
        return b.containsAt( needle, pos, sensitivity );
    }

    /** ********************************************************************************************
     * Checks if the given String is located at the given position.
     *
     * @param needle        The string to search.
     * @param pos           The to look at.
     *
     * @return  True if the given sequence is found at the given position. False otherwise .
     **********************************************************************************************/
    public boolean containsAt(CharSequence needle, int pos)
    {
        return b.containsAt( needle, pos, Case.SENSITIVE );
    }

    /** ********************************************************************************************
     * Checks if this AString starts with the given sequence.
     *
     * @param needle        The CharSequence to search. If s is null or empty, false is returned.
     * @param sensitivity   Case sensitivity of the operation.
     *                      Optional and defaults to CaseSensitive.YES.
     *
     * @return  true if this starts with the given sequence, false if not.
     **********************************************************************************************/
    public boolean startsWith(CharSequence needle, Case sensitivity)
    {
        return b.containsAt( needle, 0, sensitivity );
    }

    /** ********************************************************************************************
     * Checks if this AString starts with the given sequence.
     *
     * @param needle The String to search. If s is null or empty, false is returned.
     *
     * @return  true if this starts with the given sequence, false if not.
     **********************************************************************************************/
    public boolean startsWith(CharSequence needle)
    {
        return b.containsAt( needle, 0, Case.SENSITIVE );
    }

    /** ********************************************************************************************
     * Checks if this AString ends with the given sequence.
     *
     * @param needle The CharSequence to search. If s is null or empty, false is returned.
     * @param sensitivity   Case sensitivity of the operation.
     *                      Optional and defaults to CaseSensitive.YES.
     *
     * @return  true if this starts with the given sequence, false if not.
     **********************************************************************************************/
    public boolean endsWith(CharSequence needle, Case sensitivity)
    {
        return b.containsAt( needle, b.length() - needle.length(), sensitivity );
    }

    /** ********************************************************************************************
     * Checks if this AString ends with the given sequence.
     *
     * @param needle The String to search. If s is null or empty, false is returned.
     *
     * @return  true if this starts with the given sequence, false if not.
     **********************************************************************************************/
    public boolean endsWith(CharSequence needle)
    {
        return b.containsAt( needle, b.length() - needle.length(), Case.SENSITIVE );
    }

    /** ********************************************************************************************
     * Search the given String in the Buffer starting at a given position.
     *
     * @param s         The string to search.
     * @param startIdx  The index to start the search at. Optional and defaults to 0.
     *
     * @return  -1 if the String is not found. Otherwise the index of first occurrence.
     **********************************************************************************************/
    public int indexOf(CharSequence s, int startIdx)
    {
        return b.indexOf( s, startIdx );
    }

    /** ********************************************************************************************
     * Search the given String in the Buffer.
     *
     * @param s         The string to search.
     * @return  -1 if the String is not found. Otherwise the index of first occurrence.
     **********************************************************************************************/
    public int indexOf(CharSequence s)
    {
        return b.indexOf( s, 0 );
    }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. Returns the number
     *  of replacements.
     *
     * @param searchStr         The CharSequence to be replaced.
     * @param newStr            The replacement string.
     * @param startIdx          The index where the search starts. Optional and defaults to 0.
     * @param maxReplacements   The maximum number of replacements to perform. Optional and
     *                          defaults to Integer.MAX_VALUE .
     * @param sensitivity       Case sensitivity of the operation.
     *                          Optional and defaults to CaseSensitive.YES.
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public int searchAndReplace( CharSequence searchStr, CharSequence newStr, int startIdx,
                                int maxReplacements,   Case sensitivity)
    {
        return b.searchAndReplace( searchStr, newStr, startIdx, maxReplacements, sensitivity );
    }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. Returns the number
     *  of replacements.
     *
     * @param searchStr         The string to be replaced.
     * @param newStr            The replacement string.
     * @param startIdx          The index where the search starts. Optional and defaults to 0.
     * @param maxReplacements   The maximum number of replacements to perform. Optional and
     *                          defaults to Integer.MAX_VALUE .
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public int searchAndReplace( CharSequence searchStr, CharSequence newStr, int startIdx,
                             int maxReplacements)
    {
        return b.searchAndReplace( searchStr, newStr, startIdx, maxReplacements, Case.SENSITIVE );
    }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. Returns the number
     *  of replacements.
     *
     * @param searchStr The string to be replaced.
     * @param newStr    The replacement string.
     * @param startIdx  The index where the search starts. Optional and defaults to 0.
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public int searchAndReplace(CharSequence searchStr, CharSequence newStr, int startIdx)
    {
        return b.searchAndReplace( searchStr, newStr, startIdx, Integer.MAX_VALUE, Case.SENSITIVE );
    }

    /** ********************************************************************************************
     *  Replace one more more occurrences of a string by another string. Returns the number
     *  of replacements.
     *
     * @param searchStr The string to be replaced.
     * @param newStr    The replacement string.
     *
     * @return  The number of replacements that where performed.
     **********************************************************************************************/
    public int searchAndReplace(CharSequence searchStr, CharSequence newStr)
    {
        return b.searchAndReplace( searchStr, newStr, 0, Integer.MAX_VALUE, Case.SENSITIVE );
    }

    /** ****************************************************************************************
     * Replace one or more occurrences of a string by another string.
     * \note The difference to #searchAndReplace is that this method returns \b this to allow
     *       concatenated calls.
     *
     * @param searchStr         The CharSequence to be replaced.
     * @param newStr            The replacement string.
     *
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf searchAndReplaceAll( CharSequence searchStr, CharSequence newStr)
    {
        searchAndReplace( searchStr, newStr, 0, Integer.MAX_VALUE, Case.SENSITIVE);
        return this;
    }

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
    public int compareTo(CharSequence cmp)
    {
        return b.compareTo( cmp );
    }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp           An object of type String, StringBuffer or AString that is compared to
     *                      this.
     * @param sensitivity   Case sensitivity of the operation.
     *                      Optional and defaults to CaseSensitive.YES.
     *
     * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
     *         follows the given string (same as String.CompareTo), or if given string in null.
     **********************************************************************************************/
    public int compareTo(CharSequence cmp, Case sensitivity)
    {
        return b.compareTo( cmp, sensitivity, 0, Integer.MAX_VALUE, 0, Integer.MAX_VALUE );
    }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp           An object of type String, StringBuffer or AString that is compared to
     *                      this.
     * @param sensitivity   Case sensitivity of the operation.
     *                      Optional and defaults to CaseSensitive.YES.
     * @param sStartIdx     The start of the substring within the given string that is to be
     *                      compared to this. Defaults to 0.
     *
     * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
     *         follows the given string (same as String.CompareTo), or if given string in null.
     **********************************************************************************************/
    public int compareTo(CharSequence cmp, Case sensitivity, int sStartIdx)
    {
        return b.compareTo( cmp, sensitivity, sStartIdx, Integer.MAX_VALUE, 0, Integer.MAX_VALUE );
    }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp           An object of type String, StringBuffer or AString that is compared to
     *                      this.
     * @param sensitivity   Case sensitivity of the operation.
     *                      Optional and defaults to CaseSensitive.YES.
     * @param sStartIdx     The start of the substring within the given string that is to be
     *                      compared to this. Defaults to 0.
     * @param sLen          The length of the substring within the given string that is to be
     *                      compared to this. Defaults to Integer.MAX_VALUE.
     *
     * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
     *         follows the given string (same as String.CompareTo), or if given string in null.
     **********************************************************************************************/
    public int compareTo(CharSequence cmp, Case sensitivity, int sStartIdx, int sLen)
    {
        return b.compareTo( cmp, sensitivity, sStartIdx, sLen, 0, Integer.MAX_VALUE );
    }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp           An object of type String, StringBuffer or AString that is compared to
     *                      this.
     * @param sensitivity   Case sensitivity of the operation.
     *                      Optional and defaults to CaseSensitive.YES.
     * @param sStartIdx     The start of the substring within the given string that is to be
     *                      compared to this. Defaults to 0.
     * @param sLen          The length of the substring within the given string that is to be
     *                      compared to this. Defaults to Integer.MAX_VALUE.
     * @param startIdx      The start of the substring within this that is to be compared. Defaults
     *                      to 0.
     *
     * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
     *         follows the given string (same as String.CompareTo), or if given string in null.
     **********************************************************************************************/
    public int compareTo(CharSequence cmp, Case sensitivity, int sStartIdx, int sLen, int startIdx)
    {
        return b.compareTo( cmp, sensitivity, sStartIdx, sLen, startIdx, Integer.MAX_VALUE );
    }

    /** ********************************************************************************************
     * Compares a given string (or part of it) with the contents of this. If the optionally given
     * substring start indices and lengths parameters are out of bounds, they are corrected. This
     * could lead to unwanted results in some cases.
     *
     * @param cmp           An object of type String, StringBuffer or AString that is compared to
     *                      this.
     * @param sensitivity   Case sensitivity of the operation.
     *                      Optional and defaults to CaseSensitive.YES.
     * @param sStartIdx     The start of the substring within the given string that is to be
     *                      compared to this. Defaults to 0.
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
    public int compareTo(CharSequence cmp, Case sensitivity, int sStartIdx, int sLen, int startIdx, int len)
    {
        return b.compareTo( cmp, sensitivity, sStartIdx, sLen, startIdx, len );
    }

    /** ****************************************************************************************
     * Converts all or a region of characters in the buffer to upper case.
     *
     * @param regionStart     Start of the region to be converted. Defaults to 0
     * @param regionLength    Length of the region to be converted. Defaults to int.MaxValue.
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf toUpper( int regionStart, int regionLength )
    {
        b.toUpper( regionStart, regionLength );
        return this;
    }

    /** ****************************************************************************************
     * Converts characters in the buffer to upper case.
     *
     * @param regionStart     Start of the region to be converted. Defaults to 0
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf toUpper( int regionStart )
    {
        b.toUpper( regionStart, Integer.MAX_VALUE );
        return this;
    }

    /** ****************************************************************************************
     * Converts all characters in the buffer to upper case.
     *
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf toUpper()
    {
        b.toUpper( 0, Integer.MAX_VALUE );
        return this;
    }

    /** ****************************************************************************************
     * Converts all or a region of characters in the buffer to lower case.
     *
     * @param regionStart     Start of the region to be converted. Defaults to 0
     * @param regionLength    Length of the region to be converted. Defaults to int.MaxValue.
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf toLower( int regionStart, int regionLength )
    {
        b.toLower( regionStart, regionLength );
        return this;
    }

    /** ****************************************************************************************
     * Converts characters in the buffer to lower case.
     *
     * @param regionStart     Start of the region to be converted. Defaults to 0
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf toLower( int regionStart )
    {
        b.toLower( regionStart, Integer.MAX_VALUE );
        return this;
    }

    /** ****************************************************************************************
     * Converts all characters in the buffer to lower case.
     *
     * @return \c this to allow concatenated calls.
     ******************************************************************************************/
    public LogBuf toLower()
    {
        b.toLower( 0, Integer.MAX_VALUE );
        return this;
    }

    /** ********************************************************************************************
     * Converts the LogBuf into a String.
     *
     * @return  A string that represents this object.
     **********************************************************************************************/
    @Override public String toString()
    {
        return b.toString();
    }

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
    public StringBuilder toString(StringBuilder result, int regionStart, int regionLength, boolean appendMode)
    {
        return b.toString( result, regionStart, regionLength, appendMode );
    }

}

