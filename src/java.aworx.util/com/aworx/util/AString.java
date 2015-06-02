// #################################################################################################
//  com.aworx.util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.util;

/** ************************************************************************************************
 *  A mutable string, that provides public access to its internal buffer and fields.
 *  First of all, the existence of this class is motivated to reach a certain level of compatibility
 *  between source code that uses the AWXU library across different languages (currently Java, C#
 *  and C++) that all share a similar AString class.
 *
 *  The given C#/Java StringBuilder/Buffer classes are "sealed" and do not provide direct
 *  access to the internal buffer. Hence, to avoid conversion to new immutable strings in certain
 *  situations, we rebuild a portion of the StringBuilder functionality here. More complex
 *  functions, like formatting operations are not supported and remain the domain language specific
 *  classes.
 *
 *  If constructed  with zero size or a null pointer string (but not a zero length string), the
 *  allocation size is 0. Nevertheless, method #buffer() will return a valid empty String
 *  (an internal static singleton). This has the advantage that #buffer will always return a valid
 *  but still allocations are avoided, at least deferred.
 *  Furthermore, it makes a difference if an AString is constructed using AString() or AString("").
 *  This allows to differentiate between nulled AStrings and empty AStrings, which is quite handy
 *  in certain situations. An object that was not null already can be "set to null" by either
 *  using the assignment operator (= null) or by invoking SetAllocation(0).
 **************************************************************************************************/
public class AString implements CharSequence
{
    // #############################################################################################
    // Public Enums
    // #############################################################################################

    /** ********************************************************************************************
     * Field alignment (used by method #field)
     **********************************************************************************************/
    public enum Align
    {
        /** Align the contents of the field at the right.*/   RIGHT,
        /** Align the contents of the field at the left.*/    LEFT,
        /** Center the contents of the field.*/               CENTER
    }

    // #############################################################################################
    // Public static fields
    // #############################################################################################

        /** The system depended new line character codes retrieved statically (once) using
            "System.getProperty("line.separator");" */
        public static        String             NEWLINE           = System.getProperty("line.separator");

        /** If true, a one time AWXU warning will be issued if {@link #setLength(int)} is invoked with a
            wrong parameter. The warning will be issued only once (unless this static field is reset to
            true). */
        public static        boolean            AWXU_OTW_SetLength                  = true;

    // #############################################################################################
    // protected fields
    // #############################################################################################

        /** The Buffer array. This may but should not be accessed directly. In case of external
         *   modifications the field hash has to be set to dirty (0). */
        protected           char[]              buffer;

        /** The actual length of the string stored in the Buffer. In case of external
            modifications the field hash has to be set to dirty (0). */
        protected           int                 length                              = 0;

        /** The tab reference position. This is set when #newLine is invoked. */
        protected           int                 tabReference                        = 0;

        /** A marker for the start of the actual field. */
        protected           int                 fieldReference                      = 0;

        /** The hashvalue. Has to be set dirty (0) whenever String is changed from outside!. */
        protected           int                 hash                                = 0;

        /** A singleton that references a zero-length character array. Used to avoid object allocation. */
        protected static char[]                 nullBuffer                          = new char[0];

    // #############################################################################################
    //  Constructors
    // #############################################################################################

        /** ****************************************************************************************
         * Constructor setting the allocation size to 32.
         ******************************************************************************************/
        public AString()
        {
            buffer= nullBuffer;
        }

        /** ****************************************************************************************
         * Constructor with specific Buffer size.
         *
         * @param size  The initial size of the internal buffer. If less or equal to 0, no internal
         *                allocation is performed.
         ******************************************************************************************/
        public AString( int size  )
        {
            // check
            buffer= nullBuffer;
            if ( size > 0 )
                ensureAllocation( size );
        }

        /** ****************************************************************************************
         * Constructor copying a CharSequence.
         * @param src    The source CharSequence to copy from.
         ******************************************************************************************/
        public AString( CharSequence src )
        {
            buffer=    nullBuffer;

            // if null pointer given, we do not allocate (!)
            if ( src == null )
                return;

            // if empty string given, we allocate
            if ( src.length() == 0 )
            {
                ensureAllocation( 15 );
                return;
            }

            // copy the source
            append( src );
        }

        /** ****************************************************************************************
         * Constructor copying a substring of a CharSequence.
         *
         * @param src            The source CharSequence to copy from.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         ******************************************************************************************/
        public AString( CharSequence src, int regionStart)
        {
            buffer=    nullBuffer;

            // if null pointer given, we do not allocate (!)
            if ( src == null )
                return;

            // check null argument
            int regionLength= Integer.MAX_VALUE;
            if ( src.length() == 0  || adjustRegion( src.length(), regionStart, regionLength ) )
            {
                ensureAllocation( 15 );
                return;
            }

            // copy the source
            append( src, regionStart, regionLength );
        }

        /** ****************************************************************************************
         * Constructor copying a substring of a CharSequence.
         *
         * @param src            The source CharSequence to copy from.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         * @param regionLength   The maximum length of the region in src to append. Defaults to Integer.MAX_VALUE.
         ******************************************************************************************/
        public AString( CharSequence src, int regionStart, int regionLength)
        {
            buffer=    nullBuffer;

            // if null pointer given, we do not allocate (!)
            if ( src == null )
                return;

            // check null argument
            if ( src.length() == 0  || adjustRegion( src.length(), regionStart, regionLength ) )
            {
                ensureAllocation( 15 );
                return;
            }

            // copy the source
            append( src, regionStart, regionLength );
        }

    // #############################################################################################
    // Buffer, length and allocation
    // #############################################################################################

        /** ****************************************************************************************
         *  The internal buffer character array. This may, but should not be accessed directly.
         *  In case of external modifications be sure to adjust the length of this AString using
         *  #setLength.
         *
         * @return The internal buffer array.
         ******************************************************************************************/
        public    char[]    buffer()                     { return buffer;    }

        /** ****************************************************************************************
         * Gets the length of the sequence.
         * @return  The length of the sequence.
         ******************************************************************************************/
        @Override
        public int         length()                    {    return length;        }


        /** ****************************************************************************************
         *  Set the actual length of the stored string. Using this method, the string can only be
         *  shortened.
         *  To change the internal allocation size, see #setAllocation.
         *
         * @param newLength        The new length of the AString. Must be smaller than the current length.
         *
         * @return The new length of the string represented by this.
         ******************************************************************************************/
        public int  setLength( int newLength )
        {
            if ( newLength < length )
            {
                length= newLength;
                hash=    0;
            }
            else
            {
                if ( newLength > length && AWXU_OTW_SetLength && AWXU.acquireErrorHandler() )
                {
                    AWXU.warning( "AString::SetLength(): increase requested" );
                    AWXU_OTW_SetLength= false;
                }
            }
            return length;
        }

        /** ****************************************************************************************
         *  Returns the current size of the internal buffer.
         *
         * @return The size of the allocated buffer.
         ******************************************************************************************/
        public    int        getAllocation()             { return buffer.length;    }


        /** ****************************************************************************************
         *  Resizes the internal buffer to meet exactly the given size. Attn: If the current string represented
         *  by this instance is larger, the string is cut. This method is deemed for internal use or very
         *  special situations when used from outside.
         *    If the desired new size is 0, then any allocated buffer will be released. However, the method
         *  Buffer() will  still return a pointer to an empty constant character array (using an internal
         *  singleton).
         *
         * @param newSize    The new size for the allocation buffer. If -1 is given, the current length of
         *                     the AString is used.
         ******************************************************************************************/
        public    void     setAllocation( int newSize )
        {
            // default parameter -1: -> set to current length
            if ( newSize == -1 )
                newSize= length;

            // check
            if ( buffer.length == newSize )
                return;

            // As a side effect, flag has value as dirty
            hash= 0;

            // set uninitialized
            if ( newSize == 0 )
            {
                buffer=        nullBuffer;
                length=        0;
                return;
            }

            // create new Buffer
            char[] newBuffer=    new char[ newSize ];

            if ( length > newSize  )
                length= newSize;

            // if we had a buffer before
            if ( buffer != nullBuffer )
            {
                // copy data and delete old buffer
                System.arraycopy( buffer, 0, newBuffer, 0, length );
            }
            buffer=        newBuffer;
        }

        /** ****************************************************************************************
         * Ensures that the capacity of the internal buffer meets or exceeds the given value.
         *
         * @param minLen    The minimum length.
         ******************************************************************************************/
        public void     ensureAllocation( int minLen )
        {
            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough? if not, increase at least by 50%
            int allocSize= buffer.length;
            if ( allocSize < minLen )
                setAllocation(  Math.max( minLen, allocSize + (allocSize / 2) ) );
        }

        /** ****************************************************************************************
         * Ensures that the capacity of the internal buffer meets or exceeds the actual length
         * plus the given growth value.
         *
         * @param growth    The desired growth of length.
         ******************************************************************************************/
        public void     ensureAllocationRelative( int growth )
        {
            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough? if not, increase at least by 50%
            int allocSize= buffer.length;
            if ( allocSize < length + growth )
                setAllocation(  Math.max( length + growth, allocSize + (allocSize / 2) ) );
        }

        /** ****************************************************************************************
         * Clear the Buffer. Same as #delete (0, Length()) but without internal region checks.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString    clear()                        { length=    tabReference= 0;        return this;    }

        /** ****************************************************************************************
         *    Deletes a region from the Buffer.
         *  Note: To delete all contents use #clear.
         *
         * @param regionStart    The start of the region to delete.
         * @param regionLength    The length of the region to delete. Defaults to Integer.MAX_VALUE.
         *
         * <returns> '*this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public    AString    delete( int regionStart, int regionLength )
        {
            // adjust range, if empty do nothing
            if ( adjustRegion( length, regionStart, regionLength ) )
                return this;
            regionStart=   _adjustedRegionStart;
            regionLength=  _adjustedRegionLength;

            // case: region reaches to the end?
            int regionEnd= regionStart + regionLength;
            if ( regionEnd == length )
            {
                if ( tabReference > regionStart )
                    tabReference= regionStart;

                length=    regionStart;
                return this;
            }

            // case: region does not include this strings' end
            if ( tabReference > regionStart  && tabReference < regionEnd )
                tabReference= regionStart;

            System.arraycopy( buffer, regionEnd, buffer, regionStart, length - regionEnd );

            length-= regionLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Deletes the end of the Buffer starting at the given index.
         * Note: To delete all contents use #clear.
         *
         * @param regionStart    The start of the region to delete.
         *
         * <returns> 'this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public    AString delete( int regionStart )        { return delete( regionStart, Integer.MAX_VALUE );    }

        /** ****************************************************************************************
         *  Inserts a region into the Buffer. The region gets filled with the given character.
         *
         * @param regionStart    The start of the region to insert. If this is out of the string
         *                       bounds (hence less than 0 or greater then #length, nothing is done.
         * @param regionLength   The length of the region to insert.
         * @param fillChar       (Optional) The character to fill the new region with.
         *                       Defaults to ' ' (space).
         *
         * @return 'this' to allow concatenated calls.
         ******************************************************************************************/
        public    AString insert( int regionStart, int regionLength, char fillChar )
        {
            // check
            if ( regionStart < 0 || regionStart > length || regionLength <= 0 )
                return this;
            ensureAllocationRelative( regionLength );

            // adjust tab reference if behind us
            if ( tabReference > regionStart )
                tabReference+= regionLength;

            // move content and fill new region
            int regionEnd= regionStart + regionLength;
            System.arraycopy( buffer, regionStart, buffer, regionEnd, length - regionStart );
            for (int i= regionStart; i< regionEnd; i++ )
                buffer[i]= fillChar;

            length+= regionLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         *    Inserts a region into the Buffer. The region gets filled with spaces (' ').
         *
         * @param regionStart    The start of the region to insert. If this is out of the string
         *                       bounds (hence less than 0 or greater then #length, nothing is done.
         * @param regionLength   The length of the region to insert.
         *
         * <returns> '*this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public    AString insert( int regionStart, int regionLength ) { return insert( regionStart, regionLength, ' ' );    }

        /** ****************************************************************************************
         *  Fills a region of this AString with the given character
         *  If out of bounds, the given region is adjusted. The length of this remains unchanged.
         *
         * @param c              The character to set.
         * @param regionStart    The start of the region in this to set.
         * @param regionLength   The length of the region in this to set.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        public AString set( char c, int regionStart, int regionLength )
        {
            // empty region?
            if ( adjustRegion( length, regionStart, regionLength ) )
                return this;

            // set region
            int regionEnd=  _adjustedRegionStart + _adjustedRegionLength;
            for ( int i=    _adjustedRegionStart ; i < regionEnd ; i++ )
                buffer[i]= c;

            return this;
        }

        /** ****************************************************************************************
         *  Fills this AString with the given character from a given index to the end
         *
         * @param c             The character to set.
         * @param regionStart   The start index in this.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        public AString set( char c, int regionStart )        { return set (c, regionStart, length - regionStart ); }

        /** ****************************************************************************************
         *  Fills this AString with the given character.
         *
         * @param c  The character to set.
         * @return '*this' to allow concatenated calls.
         ******************************************************************************************/
        public AString set( char c )                        { return set (c, 0, length );             }

    // #############################################################################################
    // tab, newLine
    // #############################################################################################

        /** ****************************************************************************************
         * Appends platform specific new line character(s). ( "\\r\\n", "\\r", etc.). The new length of the
         * string is recorded as the reference position for #tab.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString newLine()
        {
            // save tab reference and append new line characters
            tabReference= length + NEWLINE.length();
            return append( NEWLINE );
        }

        /** ****************************************************************************************
         * Go to the next tab stop by filling in pad characters repeatedly. The tab position is relative
         * to the starting of the current line (if subsequent calls to #newLine where performed).
         * @param tabSize       The tab positions are multiples of this parameter.
         * @param minPad        (Optional) The minimum pad characters to add. Defaults to 1.
         * @param tabChar       (Optional) The character to insert to reach the that position.
         *                      Defaults to ' ' (space).
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString tab( int tabSize, int minPad, char tabChar)
        {
            int qtyChars= minPad > 0 ? minPad : 0;
            if ( tabSize > 1 )
                qtyChars+= (tabSize - ( (length + qtyChars - tabReference) % tabSize ) ) % tabSize;

            if ( qtyChars <= 0 )    return this;
            if ( qtyChars == 1 )    return append ( tabChar );
                                    return append ( tabChar, qtyChars );
        }

        /** ****************************************************************************************
         * Go to the next tab stop by filling in spaces repeatedly. The tab position is relative
         * to the starting of the current line (if subsequent calls to #newLine where performed).
         *
         * @param tabSize       The tab positions are multiples of this parameter.
         * @param minPad        The minimum pad characters to add. Defaults to 1.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString tab( int tabSize, int minPad)            { return tab( tabSize, minPad, ' ' ); }


        /** ****************************************************************************************
         * Go to the next tab stop by filling in spaces repeatedly. A minimum of one space is inserted.
         * The tab position is relative to the starting of the current line (if subsequent calls to #newLine
         * where performed).
         *
         * @param tabSize   The tab positions are multiples of this parameter.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString tab( int tabSize )                         { return tab( tabSize,      1,         ' ' ); }

    // #############################################################################################
    // Append
    // #############################################################################################

        /** ****************************************************************************************
         * Append a substring of a CharSequence.
         *
         * @param src            The CharSequence to append.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         * @param regionLength   The maximum length of the region in src to append. Defaults to
         *                       Integer.MAX_VALUE.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString append( CharSequence src, int regionStart, int regionLength )
        {
            // check null argument
            if ( src == null )
                return this;

            // zero length argument
            int srcLength= src.length();
            if ( srcLength == 0 )
            {
                // special treatment if currently nothing is allocated and a blank string ("") is added:
                // we allocate, which means, we are not a null object anymore!
                if ( buffer.length == 0 )
                    ensureAllocation( 15 );
                return this;
            }

            // adjust range, if empty do nothing
            if ( adjustRegion( srcLength, regionStart, regionLength ) )
                return this;

            regionStart=    _adjustedRegionStart;
            regionLength=    _adjustedRegionLength;

            // check capacity
            ensureAllocationRelative( regionLength );

            // use different built in techniques
                 if ( src instanceof String )           {    ((String)        src).getChars( regionStart, regionStart + regionLength, buffer, length );    }
            else if ( src instanceof AString )          {    System.arraycopy( ((AString) src).buffer, regionStart, buffer, length, regionLength );        }
            else if ( src instanceof StringBuffer )     {    ((StringBuffer)  src).getChars( regionStart, regionStart + regionLength, buffer, length );    }
            else if ( src instanceof StringBuilder )    {    ((StringBuilder) src).getChars( regionStart, regionStart + regionLength, buffer, length );    }

            // finally CharSequence: do it char by char
            else
            {
                int idx= length;
                int endIdx= regionStart + regionLength;
                for (int i= regionStart; i < endIdx ; i++ )
                    buffer[idx++]= src.charAt( i );
            }

            // return me for concatenated operations
            length+= regionLength;
            return this;
        }

        /** ****************************************************************************************
         * Append a substring of a CharSequence.
         *
         * @param src            The CharSequence to append.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString append( CharSequence src, int regionStart )
        {
            return append( src, regionStart, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Append a CharSequence.
         *
         * @param src    The CharSequence to append.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString append( CharSequence src )
        {
            // check null argument
            if ( src == null )
                return this;

            // zero length argument
            int srcLength= src.length();
            if ( srcLength == 0 )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a null object anymore!
                if ( buffer.length == 0 )
                    ensureAllocation( 15 );
                return this;
            }

            // get length once and check our size
            ensureAllocationRelative( srcLength );

            // use different built in techniques
                 if ( src instanceof String )                {  ((String)        src).getChars( 0, srcLength, buffer, length );            }
            else if ( src instanceof AString )               {  System.arraycopy( ((AString) src).buffer, 0,  buffer, length, srcLength ); }
            else if ( src instanceof StringBuffer )          {  ((StringBuffer)  src).getChars( 0, srcLength, buffer, length );            }
            else if ( src instanceof StringBuilder )         {  ((StringBuilder) src).getChars( 0, srcLength, buffer, length );            }

            // finally CharSequence: do it char by char
            else
            {
                int idx= length;
                for (int i= 0; i < srcLength ; i++ )
                    buffer[idx++]= src.charAt( i );
            }

            // return me for concatenated operations
            length+= srcLength;
            return this;
        }


        /** ****************************************************************************************
         * Append the given character repeatedly.
         *
         * @param c     The character to append.
         * @param qty   The quantity of characters to append.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString append( char c, int qty )
        {
            ensureAllocationRelative( qty );
            for ( int i= 0; i< qty; i++ )
                buffer[length++]= c;

            return this;
        }

        /** ****************************************************************************************
         * Append the given character.
         *
         * @param c The character to append.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString append( char c )
        {
            ensureAllocationRelative( 1 );
            buffer[ length++ ]= c;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Append the given integer value using a minimum number of digits.
         *
         * @param i         The integer value to append.
         * @param minDigits The minimum number of digits to append. If the number has less digits,
         *                  '0' characters are prepended. Optional, defaults to 0.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString append( int i, int minDigits )
        {
            // Max Value: 4294967296
            // ensure capacity
            ensureAllocationRelative( 11 ); // 10 plus minus sign

            // negative?
            if ( i < 0 )
            {
                buffer[length++] = '-';
                i= -i;
            }

            // at least one digit!
            if ( minDigits < 1 )
                minDigits= 1;

            // main loop
            int        actDigit=       11; // 10 + 1 for the loop
            int        actBase=        1000000000;
            boolean    isUnder=        false;
            while ( --actDigit > 0 )
            {
                // get next d
                int d=          i / actBase;
                int actBase2=   actBase;
                actBase/=       10;

                // did we hit i for the first time
                isUnder|= (d != 0);

                // don't print?
                if (!isUnder && actDigit > minDigits )
                    continue;

                // print the digit
                buffer[ length++ ]= (char) ( 48 + d ); // 48= '0'

                // next
                i=    i % actBase2;
            }

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Append the given integer value.
         *
         * @param i     The integer value to append.
         * @return      'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString append( int i ) { return append( i, 1 ); }

        /** ****************************************************************************************
         * Append the given double value using the minimum digits before and after the given number of
         * digits after dot.
         *
         * @param d                     the integer value to append.
         * @param minDigitsBeforeDot    The minimum number of digits write before the dot. If the number
         *                              has less digits than minDigits, '0' characters are prepended.
         *                              Optional, defaults to 0.
         * @param digitsAfterDot        The exact number of digits written after the dot.
         *                              Defaults to 5.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString append( double d, int minDigitsBeforeDot, int digitsAfterDot )
        {
            // negative? -> turn positive
            if ( d < 0d )
            {
                append( '-' );
                d= -d;
            }

            // append integer part plus dot
            int beforeDot= (int) d;

            // subtract integer part
            d-= beforeDot;

            // multiply by 10^digits, and get overflow value
            int i= digitsAfterDot;
            int overflow= 1;
            while ( i-- > 0)
            {
                d*=         10;
                overflow*=  10;
            }

            // round the multiplied rest and check for overflow. This check is necessary
            // for rests with 9er numbers:  sample 999.999  -> 1000.000, this is an "overflow"
            int afterDot= (int) Math.round( d );
            if ( afterDot == overflow )
            {
                afterDot= 0;
                beforeDot++;
            }

            // append integer part
            append( beforeDot, minDigitsBeforeDot ).append( '.' );

            // check for no digits after dot wanted
            if ( digitsAfterDot > 0 )
                append( afterDot, digitsAfterDot );

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Append the given double value using the minimum digits before and a fixed number of five
         * digits after dot.
         *
         * @param d                     the integer value to append.
         * @param minDigitsBeforeDot    The minimum number of digits write before the dot. If the number
         *                              has less digits than minDigits, then trailing '0's. are added.
         *                              Defaults to 0.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString append( double d, int minDigitsBeforeDot )     { return append( d, minDigitsBeforeDot, 5 ); }

        /** ****************************************************************************************
         * Append the given double value using a fixed number of five  digits after dot.
         *
         * @param d                     The integer value to append.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString append( double d )                             { return append( d, 0, 5); }


    // #############################################################################################
    // fields
    // #############################################################################################

        /** ****************************************************************************************
         * If invoked without parameters, the start of a field is marked at the current end of the string.
         * Otherwise the end of a field is set and the contents between the field start marker and the
         * current end of the string is aligned within the field using the given pad character.
         * Note: To implement nested fields, the outer fields have to be set by providing the start marker
         * by using the parameter fieldStart. Hence, only the starting points of the most inner fields
         * can be set using this method without parameters.
         *
         * @param size          The field size in relation to the starting index of the field, defined either by
         *                      using Field() prior to this invocation or by providing the parameter fieldStart.
         *                      The field gets filled with the given pad character to meet the size
         *                      while the content gets aligned left, right or centered.
         *                      If the content exceeds the size, then no alignment takes place.
         * @param alignment     The alignment of the contents within the field. Defaults to AString.Align.RIGHT.
         *                      Other options are AString.Align.LEFT and AString.Align.CENTER.
         * @param padChar       The character used to fill the field up to its size.
         *                      Defaults to ' ' (space).
         * @param fieldStart    This parameter, if given, overwrites the start index of the field.
         *                      The invocation of #field can be omitted, when this value is explicitly
         *                      provided.
         *                      Defaults to Integer.MAX_VALUE.
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString field( int size, Align alignment, char padChar, int fieldStart )
        {
            // if size is -1, this is just a field start marker invocation
            if ( size < 0 )
            {
                fieldReference= length;
                return this;
            }

            // if no field start is given, use the saved one (default behaviour)
            if ( fieldStart == Integer.MAX_VALUE )
                fieldStart=        fieldReference;

            // check pad size
            int padSize=    size - (length - fieldStart);
            if (padSize <= 0 )
                return this;

            // align left
            if ( alignment == Align.LEFT )
            {
                append( padChar, padSize );
                return this;
            }

            // align Right
            if ( alignment == Align.RIGHT )
            {
                insert( fieldStart, padSize, padChar );
                return this;
            }

            // align Center
            insert( fieldStart,    padSize >> 1,     padChar );
            append( padChar, padSize - ( padSize >> 1 ) );
            return this;
        }



        /** ****************************************************************************************
         * Closes and formats a field of the given size. Contents is aligned as specified.
         * The Field is fill with the character provided.
         * See variants of this method for more information.
         *
         * @param size          The field size in relation to the starting index of the field, defined either by
         *                      using Field() prior to this invocation or by providing the parameter fieldStart.
         *                      The field gets filled with the given pad character to meet the size
         *                      while the content gets aligned left, right or centered.
         *                      If the content exceeds the size, then no alignment takes place.
         * @param alignment     The alignment of the contents within the field. Defaults to AString.Align.RIGHT.
         *                      Other options are AString.Align.LEFT and AString.Align.CENTER.
         * @param padChar       The character used to fill the field up to its size.
         *                      Defaults to ' ' (space).
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString field( int size, Align alignment, char padChar  )
        {
            return field( size, alignment, padChar, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Closes and formats a field of the given size. Contents is aligned as specified.
         * The Field is fill with spaces to reach the size.
         * See variants of this method for more information.
         *
         * @param size          The field size in relation to the starting index of the field, defined by
         *                      using Field() prior to this invocation.
         * @param alignment     The alignment of the contents within the field. Defaults to AString.Align.RIGHT.
         *                      Other options are AString.Align.LEFT and AString.Align.CENTER.
         * @return  'this' to allow concatenated calls.
         *************************************************************************************************/
        public AString field( int size, Align alignment )
        {
            return field( size, alignment, ' ', Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Closes and formats a field of the given size. Contents is aligned right. The Field is fill with
         * spaces to reach the size.
         * See variants of this method for more information.
         *
         * @param size          The field size in relation to the starting index of the field, defined by
         *                      using Field() prior to this invocation.
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString field( int size )
        {
            return field( size, Align.RIGHT, ' ', Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Marks the start of a field.
         * See variants of this method for more information.
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString field()
        {
            return field( -1, Align.RIGHT, ' ', Integer.MAX_VALUE );
        }

    // #############################################################################################
    // containsAt, startsWith, endsWith
    // #############################################################################################

        /** ****************************************************************************************
         * Checks if the given String is located at the given position.
         *
         * @param needle        The CharSequence to search.
         * @param pos           The to look at.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         *
         * @return  True if the given sequence is found at the given position. False otherwise .
         ******************************************************************************************/
        public boolean containsAt( CharSequence needle, int pos, boolean ignoreCase )
        {
            // check null argument or length 0
            int needleLen=  needle != null ?  needle.length() : 0;
            int cmpEnd= pos + needleLen;
            if ( pos < 0 || cmpEnd > length )
                return false;

            // the compare loop
            int sPos= 0;
            while ( pos < cmpEnd )
            {
                @SuppressWarnings ("null")
                char c1=    needle.charAt( sPos );
                char c2=    buffer[ pos ];
                if ( ignoreCase )
                {
                    c1=    Character.toLowerCase( c1 );
                    c2=    Character.toLowerCase( c2 );
                }

                if ( c1 != c2 )
                    return false;

                pos++;
                sPos++;
            }

            return true;
        }

        /** ****************************************************************************************
         * Checks if the given String is located at the given position.
         *
         * @param needle        The CharSequence to search.
         * @param pos           The to look at.
         *
         * @return  True if the given sequence is found at the given position. False otherwise .
         ******************************************************************************************/
        public boolean containsAt( CharSequence needle, int pos )            { return containsAt( needle, pos, false ); }

        /** ****************************************************************************************
         * Checks if this AString starts with the given sequence.
         *
         * @param needle        The CharSequence to search. If s is null or empty, false is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( CharSequence needle, boolean ignoreCase ) { return containsAt( needle, 0, ignoreCase );    }

        /** ****************************************************************************************
         * Checks if this AString starts with the given sequence.
         *
         * @param needle        The CharSequence to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( CharSequence needle )                    { return containsAt( needle, 0, false );    }

        /** ****************************************************************************************
         * Checks if this AString ends with the given sequence.
         *
         * @param needle        The CharSequence to search. If s is null or empty, false is returned.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean endsWith  ( CharSequence needle, boolean ignoreCase ){ return containsAt( needle, length - needle.length(), ignoreCase );     }

        /** ****************************************************************************************
         * Checks if this AString ends with the given sequence.
         *
         * @param needle        The CharSequence to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean endsWith  ( CharSequence needle )                    { return containsAt( needle, length - needle.length(), false );     }

    // #############################################################################################
    // indexOf
    // #############################################################################################

        /** ****************************************************************************************
         * Search the given String in the buffer starting at a given position.
         *
         * @param needle        The CharSequence to search.
         * @param startIdx      The index to start the search at. Optional and defaults to 0.
         * @param ignoreCase    If true, the compare is case insensitive. Optional and defaults to false.
         *
         * @return  -1 if the String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOf( CharSequence needle, int startIdx, boolean ignoreCase )
        {
            // check null argument or length 0
            int needleLen=  needle != null ?  needle.length() : 0;
            if ( startIdx < 0 )                     startIdx= 0;

            if ( startIdx + needleLen > length)     return      -1;
            if ( needleLen == 0 )                   return      startIdx;

    //         // search
            if (!ignoreCase)
            {
                @SuppressWarnings ("null")
                char firstChar= needle.charAt( 0 );        // get first char once, as [] operation is expensive
                while ( startIdx < length )
                {
                    int  cmpLen=  0;
                    char sc=      firstChar;
                    while ( buffer[ startIdx + cmpLen ] == sc )
                    {
                        cmpLen++;
                        if ( cmpLen == needleLen )
                            return startIdx;
                        sc= needle.charAt( cmpLen );
                    }
                    startIdx++;
                }
            }

            // search (ignore case version)
            else
            {
                @SuppressWarnings ("null")
                char firstChar= Character.toLowerCase( needle.charAt( 0 ) );        // get first char once, as [] operation is expensive
                while ( startIdx < length )
                {
                    int  cmpLen= 0;
                    char sc=     firstChar;
                    while ( Character.toLowerCase( buffer[ startIdx + cmpLen ] ) == sc )
                    {
                        cmpLen++;
                        if ( cmpLen == needleLen )
                            return startIdx;
                        sc= Character.toLowerCase( needle.charAt( cmpLen ) );
                    }
                    startIdx++;
                }
            }


            // not found
            return -1;
        }

        /** ****************************************************************************************
         * Search the given CharSequence in the buffer.
         *
         * @param cs            The CharSequence to search.
         * @param startIdx      The index to start the search at. Optional and defaults to 0.
         *
         * @return  -1 if the String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOf( CharSequence cs, int startIdx )    {    return indexOf( cs, startIdx, false ); }


        /** ****************************************************************************************
         * Search the given CharSequence in the buffer.
         *
         * @param cs            The CharSequence to search.
         * @return  -1 if the String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOf( CharSequence cs )                {    return indexOf( cs, 0, false ); }

        /** ****************************************************************************************
         * Search the given character in the buffer.
         *
         * @param c             The character to search.
         * @param startIdx      The index to start the search at. Optional and defaults to 0.
         *
         * @return  -1 if the character is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOf( char c, int startIdx )
        {
            // check
                 if ( startIdx < 0 )
                startIdx= 0;
            else if ( startIdx >= length)
                return -1;

            // search
            while ( startIdx < length )
            {
                if ( c == buffer[ startIdx ] )
                    return startIdx;
                startIdx++;
            }

            // not found
            return -1;
        }

        /** ****************************************************************************************
         * Search the given character in the buffer.
         *
         * @param c    The character to search.
         *
         * @return  -1 if the character is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOf( char c )                        {    return indexOf( c, 0 ); }


    // #############################################################################################
    // replace
    // #############################################################################################

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. Returns the number
         * of replacements. Use #replace() to allow concatenated operations.
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         * @param startIdx          The index where the search starts. Optional and defaults to 0.
         * @param maxReplacements   The maximum number of replacements to perform. Optional and
         *                          defaults to Integer.MAX_VALUE .
         * @param ignoreCase        If true, a case insensitive search is performed. Defaults to false.
         *
         * @return  The number of replacements that where performed.
         ******************************************************************************************/
        public int replaceCount( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements, boolean ignoreCase )
        {

            // check null arguments
            if ( AString.isNullOrEmpty(searchStr) )
                return 0;

            // get some values
            int searchStringLength=        searchStr.length();
            int newStringLength=        (newStr != null) ? newStr.length()  : 0;
            int lenDiff=                newStringLength - searchStringLength;

            // replacement loop
            int cntReplacements=    0;
            int idx= -1;
            while ( cntReplacements < maxReplacements && idx < length )
            {
                // search  next occurrence
                if ( ( idx= indexOf( searchStr, startIdx, ignoreCase ) ) < 0 )
                    return cntReplacements;

                // set dirty
                hash= 0;

                // copy rest up or down
                if ( lenDiff != 0 )
                {
                    ensureAllocationRelative( lenDiff );
                    System.arraycopy( buffer, idx + searchStringLength, buffer, idx + searchStringLength + lenDiff, length - idx - searchStringLength );
                    length+= lenDiff;
                }

                // fill replacement string in
                // (Note: we could differentiate between different CharSequence types and use array copy methods, but the
                // overhead would turn this negative for small replacement strings)
                for ( int i= 0; i < newStringLength ; i++ )
                    buffer[ idx + i ]= newStr.charAt( i );

                // set start index to first character behind current replacement
                startIdx= idx+ newStringLength;

                // next
                cntReplacements++;
            }

            // that's it
            return cntReplacements;
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. Returns the number
         * of replacements. Use #replace() to allow concatenated operations.
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         * @param startIdx          The index where the search starts. Optional and defaults to 0.
         * @param maxReplacements   The maximum number of replacements to perform. Optional and
         *                          defaults to Integer.MAX_VALUE .
         *
         * @return  The number of replacements that where performed.
         ******************************************************************************************/
        public int replaceCount( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements )
        {
            return replaceCount( searchStr, newStr, startIdx, maxReplacements,        false);
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. Returns the number
         * of replacements. Use #replace() to allow concatenated operations.
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         * @param startIdx          The index where the search starts. Optional and defaults to 0.
         *
         * @return  The number of replacements that where performed.
         ******************************************************************************************/
        public int replaceCount( CharSequence searchStr, CharSequence newStr, int startIdx )
        {
            return replaceCount( searchStr, newStr, startIdx, Integer.MAX_VALUE,     false);
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. Returns the number
         * of replacements. Use #replace() to allow concatenated operations.
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         *
         * @return  The number of replacements that where performed.
         ******************************************************************************************/
        public int replaceCount( CharSequence searchStr, CharSequence newStr)
        {
            return replaceCount( searchStr, newStr, 0,         Integer.MAX_VALUE,        false);
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. To receive the number of
         * replacements, see alternative method #replaceCount().
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         * @param startIdx          The index where the search starts. Optional and defaults to 0.
         * @param maxReplacements   The maximum number of replacements to perform. Optional and
         *                          defaults to Integer.MAX_VALUE .
         * @param ignoreCase        If true, a case insensitive search is performed. Defaults to false.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString replace( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements, boolean ignoreCase )
        {
            replaceCount( searchStr, newStr, startIdx,    maxReplacements,     ignoreCase );    return this;
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. To receive the number of
         * replacements, see alternative method #replaceCount().
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         * @param startIdx          The index where the search starts. Optional and defaults to 0.
         * @param maxReplacements   The maximum number of replacements to perform. Optional and
         *                          defaults to Integer.MAX_VALUE .
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString replace( CharSequence searchStr, CharSequence newStr, int startIdx, int maxReplacements)
        {
            replaceCount( searchStr, newStr, startIdx,     maxReplacements,     false );        return this;
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. To receive the number of
         * replacements, see alternative method #replaceCount().
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         * @param startIdx          The index where the search starts. Optional and defaults to 0.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString replace( CharSequence searchStr, CharSequence newStr, int startIdx )
        {
            replaceCount( searchStr, newStr, startIdx,     Integer.MAX_VALUE,     false );        return this;
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. To receive the number of
         * replacements, see alternative method #replaceCount().
         *
         * @param searchStr The CharSequence to be replaced.
         * @param newStr    The replacement string.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString replace( CharSequence searchStr, CharSequence newStr)
        {
            replaceCount( searchStr, newStr, 0,         Integer.MAX_VALUE,     false );        return this;
        }

    // #############################################################################################
    // compareTo
    // #############################################################################################

        /** ****************************************************************************************
         * Compares a given region of a string with the a region of this instance. Regions that are out of bounds
         * get adjusted and then compared. If this behavior is not what is wanted, a separate region
         * check and corresponding compare result evaluation has to be performed.
         *
         * @param compareString             An object of type String, StringBuffer or AString that is compared to
         *                                  this.
         * @param ignoreCase                If true, the compare is case insensitive. Optional and defaults to false.
         * @param compareStringRegionStart  The start of the substring within the given string that is to be compared
         *                                  to this. Defaults to 0.
         * @param compareStringRegionLength The length of the substring within the given string that is to be
         *                                  compared to this. Defaults to Integer.MAX_VALUE.
         * @param regionStart               The start of the substring within this string that is to be compared. Defaults
         *                                  to 0.
         * @param regionLength              The length of the substring within this string that is to be compared.
         *                                  Defaults to Integer.MAX_VALUE.
         *
         * @return 0 if the contents of the string regions are equal (or if both regions are empty or out of range).
         *           -1 if the instance is less than the given string.
         *           +1 if the instance is greater than the given string or if given string is null.
         ******************************************************************************************/
        public int compareTo( CharSequence compareString, boolean ignoreCase, int compareStringRegionStart, int compareStringRegionLength, int regionStart, int regionLength )
        {
            // check null argument
            if ( buffer.length == 0   )     return  compareString == null ? 0 : -1;
            if ( compareString == null )
                return 1;

            // adjust source and compare regions
            adjustRegion( compareString.length(), compareStringRegionStart, compareStringRegionLength );
            compareStringRegionStart=   _adjustedRegionStart;
            compareStringRegionLength=  _adjustedRegionLength;

            adjustRegion( length, regionStart, regionLength );
            regionStart=                _adjustedRegionStart;
            regionLength=               _adjustedRegionLength;

            // compare loop
            int srcIdx=                 regionStart;
            int srcEnd=                 regionStart     +              regionLength;
            int cmpIdx=    compareStringRegionStart;
            int cmpEnd=    compareStringRegionStart     + compareStringRegionLength;
            while ( true )
            {
                // end of one of the strings or both?
                if (srcIdx >= srcEnd)    return  (cmpIdx >= cmpEnd) ?     0    :    -1;
                if (cmpIdx >= cmpEnd)    return                                      1;

                // compare characters
                char srcC=  buffer[ srcIdx  ];
                char cmpC=  compareString.charAt( cmpIdx );
                if ( srcC != cmpC )
                {
                    // no match!
                    if ( !ignoreCase )
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

        /** ****************************************************************************************
         * Compares a given region of a string with the a region of this instance. Regions that are out of bounds
         * get adjusted and then compared. If this behavior is not what is wanted, a separate region
         * check and corresponding compare result evaluation has to be performed.
         *
         * @param compareString               An object of type String, StringBuffer or AString that is compared to
         *                                  this.
         * @param ignoreCase                If true, the compare is case insensitive. Optional and defaults to false.
         * @param compareStringRegionStart  The start of the substring within the given string that is to be compared
         *                                  to this. Defaults to 0.
         * @param compareStringRegionLength The length of the substring within the given string that is to be
         *                                  compared to this. Defaults to Integer.MAX_VALUE.
         * @param regionStart                  The start of the substring within this string that is to be compared. Defaults
         *                                  to 0.
         *
         * @return 0 if the contents of the string regions are equal (or if both regions are empty or out of range).
         *           -1 if the instance is less than the given string.
         *           +1 if the instance is greater than the given string or if given string is null.
         ******************************************************************************************/
        public int compareTo( CharSequence compareString, boolean ignoreCase, int compareStringRegionStart, int compareStringRegionLength, int regionStart )
        {
            return compareTo( compareString, ignoreCase, compareStringRegionStart, compareStringRegionLength,                 regionStart,    Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Compares a given region of a string with this instance. If the given region is out of bounds in
         * respect to the given string, it get adjusted and then compared. If this behavior is not what
         * is wanted, a separate region check and corresponding compare result evaluation has to be performed.
         *
         * @param compareString               An object of type String, StringBuffer or AString that is compared to
         *                                  this.
         * @param ignoreCase                If true, the compare is case insensitive. Optional and defaults to false.
         * @param compareStringRegionStart  The start of the substring within the given string that is to be compared
         *                                  to this. Defaults to 0.
         * @param compareStringRegionLength The length of the substring within the given string that is to be
         *                                  compared to this. Defaults to Integer.MAX_VALUE.
         *
         * @return 0 if the contents of the string regions are equal (or if both regions are empty or out of range).
         *           -1 if the instance is less than the given string.
         *           +1 if the instance is greater than the given string or if given string is null.
         ******************************************************************************************/
        public int compareTo( CharSequence compareString, boolean ignoreCase, int compareStringRegionStart, int compareStringRegionLength )
        {



            return compareTo( compareString, ignoreCase, compareStringRegionStart, compareStringRegionLength,                 0,            Integer.MAX_VALUE );
        }


        /** ****************************************************************************************
         * Compares a given region of a string with this instance. If the given region start is out of bounds in
         * respect to the given string, it gets adjusted and then compared. If this behavior is not what
         * is wanted, a separate region check and corresponding compare result evaluation has to be performed.
         *
         * @param compareString             An object of type String, StringBuffer or AString that is compared to
         *                                  this.
         * @param ignoreCase                If true, the compare is case insensitive. Optional and defaults to false.
         * @param compareStringRegionStart  The start of the substring within the given string that is to be compared
         *                                  to this. Defaults to 0.
         *
         * @return 0 if the contents of the string regions are equal (or if both regions are empty or out of range).
         *           -1 if the instance is less than the given string.
         *           +1 if the instance is greater than the given string or if given string is null.
         ******************************************************************************************/
        public int compareTo( CharSequence compareString, boolean ignoreCase, int compareStringRegionStart )
        {
            return compareTo( compareString, ignoreCase, compareStringRegionStart, Integer.MAX_VALUE,     0,            Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Compares a given string with this instance.
         *
         * @param compareString               An object of type String, StringBuffer or AString that is compared to
         *                                  this.
         * @param ignoreCase                If true, the compare is case insensitive. Optional and defaults to false.
         *
         * @return 0 if the contents of the string regions are equal (or if both regions are empty or out of range).
         *           -1 if the instance is less than the given string.
         *           +1 if the instance is greater than the given string or if given string is null.
         ******************************************************************************************/
        public int compareTo( CharSequence compareString, boolean ignoreCase )
        {
            return compareTo( compareString, ignoreCase, 0,         Integer.MAX_VALUE,     0,             Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Compares a given string with this instance.
         *
         * @param compareString  An object of type String, StringBuffer or AString that is compared to this.
         *
         * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
         *         follows the given string (same as String.CompareTo), or if given string in null.
         ******************************************************************************************/
        public int compareTo( CharSequence compareString )
        {
            return compareTo( compareString, false,      0,         Integer.MAX_VALUE,     0,             Integer.MAX_VALUE );
        }

    // #############################################################################################
    // convertCase
    // #############################################################################################

        /** ****************************************************************************************
         * Converts all or a region of characters in the Buffer to upper or to lower case.
         *
         * @param toUpper       If true, conversion to upper case is performed, to lower else.
         * @param substrStart   Start of the substring to be converted. Defaults to 0.
         * @param substrLength  Length of the substring to be converted. Defaults to Integer.MAX_VALUE.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString convertCase( boolean toUpper, int substrStart, int substrLength )
        {
            // mark has value as dirty
            hash= 0;

            // adjust range
            if ( substrLength == Integer.MAX_VALUE )
            {
                if (substrStart < 0 )
                    substrStart=    0;
                substrLength=    length - substrStart;
            }
            else
                if (substrStart < 0 )
                {
                    substrLength+= substrStart;
                    substrStart=    0;
                }

            int substrEnd= substrStart + substrLength;
            if ( substrEnd > length )
                substrEnd= length;

            // convert
            for ( int i= substrStart; i < substrEnd ; i++ )
                buffer[ i ]=  toUpper   ?    Character.toUpperCase( buffer[ i ] )
                                        :    Character.toLowerCase( buffer[ i ] );

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Converts all or a region of characters in the Buffer to upper or to lower case.
         *
         * @param toUpper       If true, conversion to upper case is performed, to lower else.
         * @param substrStart   Start of the substring to be converted. Defaults to 0.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString convertCase( boolean toUpper, int substrStart  )   { return convertCase( toUpper, substrStart,    Integer.MAX_VALUE ); }

        /** ****************************************************************************************
         * Converts all or a region of characters in the Buffer to upper or to lower case.
         *
         * @param toUpper   If true, conversion to upper case is performed, to lower else.
         *
         * @return  'this' to allow concatenated calls.
         ******************************************************************************************/
        public AString convertCase( boolean toUpper )                     { return convertCase( toUpper, 0,            Integer.MAX_VALUE ); }


    // #############################################################################################
    // toString, toInt
    // #############################################################################################

        /** ****************************************************************************************
         * Creates a String containing a copy of a region of the contents of this AString.
         *
         * @param regionStart   The start index of the region in this to create the string from.
         * @param regionLength  The maximum length of the region to create the string from.
         *                      Defaults to Integer.MAX_VALUE.
         *
         * @return  A string that represents the specified sub region of this object
         ******************************************************************************************/
        public String toString( int regionStart, int regionLength )
        {
            // adjust range, if empty return empty string
            if ( adjustRegion( length, regionStart, regionLength ) )
                return empty;

            // create string
            return new String( buffer, _adjustedRegionStart, _adjustedRegionLength );
        }

        /** ****************************************************************************************
         * Creates a String containing a copy of the ending of the AString.
         *
         * @param regionStart  The start point from where on the remainder of this AString is copied.
         *
         * @return  A string that represents the specified sub region of this object
         ******************************************************************************************/
        public String toString( int regionStart )    { return toString( regionStart, Integer.MAX_VALUE ); }

        /** ****************************************************************************************
         * Creates a String containing a copy of the contents of this AString.
         *
         * @return  A string that represents this object.
         ******************************************************************************************/
        @Override public String toString()           { return new String( buffer, 0, length );            }


        /** ****************************************************************************************
         * Copies a region of the contents of this AString into the given StringBuilder.
         *
         * @param result        A result StringBuilder to copy the specified region into. If null, a new
         *                      String builder is created
         * @param regionStart   The start index of the region to be copied.
         * @param regionLength  The maximum length of the region to be copied.
         * @param appendMode    If true, any contents in the result is preserved. Otherwise such content
         *                      gets replaced.
         * @return  The (modified) result that was provided (for concatenation of calls).
         ******************************************************************************************/
        public StringBuilder toString( StringBuilder result, int regionStart, int regionLength, boolean appendMode )

        {
            if ( result == null)
                result= new StringBuilder();
            else if ( !appendMode )
                result.delete( 0, result.length() );

            // adjust range, if empty return empty string
            if ( adjustRegion( length, regionStart, regionLength ) )
                return result;

            // copy our buffer into result
            result.append( buffer , _adjustedRegionStart, _adjustedRegionLength );
            return  result;
        }

        /** ****************************************************************************************
         * Reads a long from the AString. If the optional parameter start index is given, it will be set
         * to the first character that is not a number. If no number is found a the given index, zero
         * is returned and the optionally provided index is not increased.
         *
         * @param idx   The start point from where the long value is tried to be read. This
         *              is provided as an array object, because Java does not allow reference parameters
         *              of basic types. If the given array is longer than 1, values other than
         *              idx[0] are ignored.
         *
         * @return  The parsed value. In addition, the input parameter idx is moved to point to the
         *             first character behind any found long number.
         ******************************************************************************************/
        public long toLong( int[] idx )
        {
            int   iidx=        idx != null ? idx[0] : 0;
            long  retVal=    0;
            while ( iidx < length )
            {
                char  c= buffer[ iidx ];
                if ( c < '0' || c > '9' )
                    break;

                retVal= ( retVal * 10 ) + ( (int) ( c - '0' ) );
                iidx++;
            }

            if ( idx != null )
                idx[0]= iidx;
            return retVal;
        }

        /** ****************************************************************************************
         * Reads an integer from the AString. If the optional parameter start index is given, it will be
         * set to the first character that is not a number. If no number is found a the given index, zero
         * is returned and the optionally provided index is not increased.
         *
         * @param idx   The start point from where the long value is tried to be read. This
         *              is provided as an array object, because Java does not allow reference parameters
         *              of basic types. If the given array is longer than 1, values other than
         *              idx[0] are ignored.
         *
         * @return  The parsed value. In addition, the input parameter idx is moved to point to the
         *             first character behind any found integer number.
         ******************************************************************************************/
        public int toInt( int[] idx )            {    return (int) toLong( idx );    }

    // #############################################################################################
    // hashCode, equals
    // #############################################################################################


    /** ********************************************************************************************
     * Calculates the hash value using the same formula as java.lang.String.
     *
     * @return  A hash value for this object.
     **********************************************************************************************/
    @Override  public int hashCode()
    {
        int h;
        if ((h= hash) == 0 && length > 0)
        {
            char buf[]=    buffer;
            int  len=    length;

            for (int i = 0; i < len; i++)
                h = 31*h + buf[i++];

            hash = h;
        }
        return h;
    }

    /** ********************************************************************************************
     * Compares this to the given object. Given object can be AString or CharSequence (e.g. String).
     *
     * @param o The object to compare to this instance.
     *
     * @return  True if given object equals this.
     **********************************************************************************************/
    @Override public boolean equals( Object o )
    {
        // null?
        if ( o == null )
            return buffer.length == 0;
        if ( buffer.length == 0 )
            return false;


        // AString?
        if ( o instanceof AString)
        {
            // cast up
            AString ms= ( AString ) o;

            // different length?
            if ( ms.length != length )
                return false;

            // character compare
            for (int i= length - 1 ; i >= 0 ; i-- )
                if ( ms.buffer[i] != buffer[i] )
                    return false;

            // equal
            return true;
        }

        // CharSequence?
        if ( o instanceof CharSequence )
        {
            // cast up
            CharSequence cs= ( CharSequence ) o;

            // different length?
            if ( cs.length() != length )
                return false;

            // character compare
            for (int i= length - 1 ; i >= 0 ; i-- )
                if ( cs.charAt( i ) != buffer[i] )
                    return false;

            // equal
            return true;
        }

        // not a known comparable object
        return false;
    }

    // #############################################################################################
    // internals
    // #############################################################################################

    /** Used as a return value of method adjustRangeAndTestIfEmpty() as Java does not allow to pass
        parameters by reference */
    protected int _adjustedRegionStart;

    /** Used as a return value of method adjustRangeAndTestIfEmpty() as Java does not allow to pass
        parameters by reference */
    protected int _adjustedRegionLength;

    /** ********************************************************************************************
     * Simple, but frequently used method that adjusts a given region to the range
     * of [0 .. referenceLength]. First, the region start is checked on negative values. Those
     * are cut to zero while also shorting the region correspondingly.
     * Then, the region start is checked if it exceeds the string. If this is the case, the region
     * will be set to an empty region at the end of the string.
     * Lastly, the region length is cut so that it does not exceed the length of the string.
     * The return value of the function indicates if the region is empty.
     *
     * Note: This would be a static method, if the Java language would allow call by reference on parameters.
     * However, as this is not allowed, we have to set two "temporary" fields that act as the return values.
     *
     * @param referenceLength   Length of the string that the given region will be adjusted to.
     * @param regionStart       The start of the region to be adjusted.
     * @param regionLength      The length of the region to be adjusted.
     *
     * @return  True if adjusted range is empty.
     **********************************************************************************************/
    protected boolean adjustRegion(int referenceLength, int regionStart, int regionLength )
    {
        // if start exceeds string, set to empty range at the end of the string and return true
        if (regionStart >= referenceLength)
        {
            _adjustedRegionStart=    referenceLength;
            _adjustedRegionLength=    0;
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


        // save return values
        _adjustedRegionStart=    regionStart;
        _adjustedRegionLength=    regionLength;

        // return true if adjusted region is empty
        return  regionLength == 0;
    }


    // #############################################################################################
    //  Static String Utilities
    // #############################################################################################

    /**   An empty String singleton */
    public static final String empty=                    "";

    /** ********************************************************************************************
     * Checks if a given CharSequence is empty or has a length of zero.
     *
     * @param cs   The CharSequence to check.
     *
     * @return  Returns true if given String is empty or 0.
     **********************************************************************************************/
    public static boolean isNullOrEmpty( CharSequence cs )    { return cs == null || cs.length() == 0; }

    /** ********************************************************************************************
     * Search the given String in the Buffer starting at the given position.
     *
     * @param sIn       The CharSequence to search in.
     * @param sFor      The CharSequence to search for.
     * @param startIdx  The index to start the search at. Optional and defaults to 0.
     *
     * @return  -1 if the String is not found. Otherwise the index of first occurrence.
     **********************************************************************************************/
    public static int indexOfIgnoreCase( CharSequence sIn, CharSequence sFor, int startIdx )
    {
        // check s1
        if ( sIn == null )
            return -1;
        int sInLen= sIn.length();

        // check s2 null argument or length 0
        int sForLen=  sFor != null ?  sFor.length() : 0;
        if ( sForLen == 0 || startIdx > sInLen)
            return -1;

        // check start idx < 0
        if ( startIdx < 0 )
            startIdx= 0;

        // search
        @SuppressWarnings ("null")
        char firstChar= Character.toLowerCase( sFor.charAt( 0 ) );        // get first char once, as [] operation is expensive
        while ( startIdx < sInLen )
        {
            int        cmpLen= 0;
            char    cFor=    firstChar;
            while ( Character.toLowerCase( sIn.charAt( startIdx + cmpLen )) == cFor )
            {
                cmpLen++;
                if ( cmpLen == sForLen )
                    return startIdx;
                cFor= Character.toLowerCase( sFor.charAt( cmpLen ) );
            }
            startIdx++;
        }

        // not found
        return -1;
    }

    /** ********************************************************************************************
     * Search the given String in the Buffer.
     *
     * @param haystack  The CharSequence to search in.
     * @param needle    The CharSequence to search for.
     *
     * @return  -1 if the String is not found. Otherwise the index of first occurrence.
     **********************************************************************************************/
    public static int indexOfIgnoreCase         ( CharSequence haystack, CharSequence needle )        { return indexOfIgnoreCase( haystack, needle, 0); }

    /** ********************************************************************************************
     * Static utility function to check if a string starts with another string with case
     * insensitive compare. Using this function avoids to create two converted (lowered)
     * temporary strings.
     *
     * @param haystack  The CharSequence to search in.
     * @param needle    The CharSequence to search for.
     *
     * @return  true, if given string s starts with given string prefix, false otherwise.
     **********************************************************************************************/
    @SuppressWarnings ("null")
    public static boolean startsWithIgnoreCase  ( CharSequence haystack, CharSequence needle )
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

    /** ********************************************************************************************
     * Static utility function to check if a string ends with another string with case
     * insensitive compare. Using this function avoids to create two converted (lowered) temporary
     * strings.
     *
     * @param haystack  The CharSequence to search in.
     * @param needle    The CharSequence to search for.
     *
     * @return  true, if given string s ends with given string prefix, false otherwise.
     **********************************************************************************************/
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
            if ( Character.toLowerCase( haystack.charAt( haystackIdx++ ) ) != Character.toLowerCase( needle.charAt( needleIdx ) ))
                return false;

        // no differences found
        return true;
    }

    // #############################################################################################
    // Java CharSequence interface implementation
    // #############################################################################################

        /** ****************************************************************************************
         * Returns a character of the sequence.
         * @param index     The index of the character to return.
         * @return          The character at the given index.
         ******************************************************************************************/
        @Override public char     charAt(int index)        {    return buffer[ index ];    }

        /** ****************************************************************************************
         * Throws an AWXU error (using the AWXU error handler) and returns null. The reason for this
         * behavior is to disallow the usage of AString within (system) methods that create sub sequences.
         * This would be in contrast to the design goal of AString.
         *
         * @param beginIndex    The start of the sequence (not used)
         * @param endIndex      The length of the sequence (not used)
         *
         * @return  null (!).
         ******************************************************************************************/
        @Override public CharSequence subSequence(int beginIndex, int endIndex)
        {
            // this function should never be used
            if ( AWXU.acquireErrorHandler() )
                AWXU.error( "AString.subSequence() called. This is not supported" );
            return null;
        }

} // class Mutable String


