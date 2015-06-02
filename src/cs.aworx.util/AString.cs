// #################################################################################################
//  com.aworx.util - Classes we need
//
//  (c) 2013-2015 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Text;

namespace com.aworx.util  {

/** ************************************************************************************************
 * <summary>
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
 *  allocation size is 0. Nevertheless, method #Buffer() will return a valid empty String
 *  (an internal static singleton). This has the advantage that #Buffer will always return a valid
 *  but still allocations are avoided, at least deferred.
 *  Furthermore, it makes a difference if an AString is constructed using AString() or AString("").
 *  This allows to differentiate between nulled AStrings and empty AStrings, which is quite handy
 *  in certain situations. An object that was not null already can be "set to null" by either
 *  using the assignment operator (= null) or by invoking SetAllocation(0).
 * </summary>
 **************************************************************************************************/
public class AString
{
    // #############################################################################################
    // Public Enums
    // #############################################################################################

        /** ****************************************************************************************
         * Field alignment (used by method #Field)
         ******************************************************************************************/
        public enum Align
        {
            /** <summary> Align the contents of the field at the right.</summary>*/
            Right,

            /** <summary> Align the contents of the field at the left.</summary>*/
            Left,

            /** <summary> Center the contents of the field.</summary>*/
            Center
        }

    // #############################################################################################
    // Public static fields
    // #############################################################################################

        /// <summary> The system depended new line character codes retrieved statically (once) using
        /// "Environment.NewLine;" </summary>
        public static String            NEWLINE                                 =Environment.NewLine;


        /// <summary> If true, a one time AWXU warning will be issued if {@link #SetLength(int)} is
        /// invoked with a wrong parameter. The warning will be issued only once (unless this static
        /// field is reset to true). </summary>
        public static bool              AWXU_OTW_SetLength                      =true;


    // #############################################################################################
    // protected fields
    // #############################################################################################

        /// <summary>The Buffer array. This may but should not be accessed directly. In case of
        /// external modifications the field hash has to be set to dirty (0).</summary>
        protected     char[]            buffer;

        /// <summary>The actual length of the string stored in the Buffer. In case of external
        /// modifications the field hash has to be set to dirty (0).</summary>
        protected     int               length;

        /// <summary>The tab reference position. This is set when #NewLine is invoked.</summary>
        protected     int               tabReference;

        /// <summary>A marker for the start of the actual field.</summary>
        protected     int               fieldReference;

        /// <summary>The hash value. Has to be set dirty (0) whenever String is changed from
        /// outside!.</summary>
        protected     int               hash;

        /// <summary>A singleton that references a zero-length character array. Used to avoid object
        /// allocation.</summary>
        protected static char[]         nullBuffer                              =new char[0];

    // #############################################################################################
    //  Constructors
    // #############################################################################################

        /** ****************************************************************************************
         * <summary> Constructs an empty AString. Does not allocate a buffer. </summary>
         ******************************************************************************************/
        public AString()
        {
            buffer= nullBuffer;
        }


        /** ****************************************************************************************
         * <summary> Constructor with specific Buffer size . </summary>
         * <param name="size">    The initial size of the internal buffer. If less or equal to 0, no
         *                        internal allocation is performed </param>
         ******************************************************************************************/
        public AString( int size  )
        {
            buffer= nullBuffer;
            if ( size > 0 )
                EnsureAllocation( size );
        }

        /** ****************************************************************************************
         * <summary> Constructor copying a substring of another AString. </summary>
         *
         * <param name="src">            The source AString to copy from. </param>
         * <param name="regionStart">    The start index in ms to append. Defaults to 0. </param>
         * <param name="regionLength">   The maximum length of the substring in ms to append.
         *                               Defaults to int.MaxInt. </param>
         ******************************************************************************************/
        public AString( AString src, int regionStart= 0, int regionLength= int.MaxValue )
        {
            buffer=    nullBuffer;

            // if null pointer given, we do not allocate (!)
            if ( src == null )
                return;

            // check null argument
            if ( src.length == 0  || adjustRegion( src.length, ref regionStart, ref regionLength ) )
            {
                EnsureAllocation( 15 );
                return;
            }

            // copy the source
            Append( src, regionStart, regionLength );
        }

        /** ****************************************************************************************
         * <summary> Constructor copying a substring of a String. </summary>
         *
         * <param name="src">            The source String to copy from. </param>
         * <param name="regionStart">    The start index in s to append. Defaults to 0. </param>
         * <param name="regionLength">   The maximum length of the substring in s to append.
         *                               Defaults to int.MaxInt. </param>
         ******************************************************************************************/
        public AString( String src, int regionStart= 0, int regionLength= int.MaxValue)
        {
            buffer=    nullBuffer;

            // if null pointer given, we do not allocate (!)
            if ( src == null )
                return;

            // check null argument
            if ( src.Length == 0  || adjustRegion( src.Length, ref regionStart, ref regionLength ) )
            {
                EnsureAllocation( 15 );
                return;
            }

            // copy the source
            Append( src, regionStart, regionLength );
        }

        /** ****************************************************************************************
         * <summary> Constructor copying a substring of a StringBuilder. </summary>
         *
         * <param name="src">            The source StringBuilder to copy. </param>
         * <param name="regionStart">    The start index in ms to append. Defaults to 0. </param>
         * <param name="regionLength">   The maximum length of the substring in ms to append.
         *                               Defaults to int.MaxInt. </param>
         ******************************************************************************************/
        public AString( StringBuilder src, int regionStart= 0, int regionLength= int.MaxValue )
        {
            buffer=    nullBuffer;

            // if null pointer given, we do not allocate (!)
            if ( src == null )
                return;

            // check null argument
            if ( src.Length == 0  || adjustRegion( src.Length, ref regionStart, ref regionLength ) )
            {
                EnsureAllocation( 15 );
                return;
            }

            // copy the source
            Append( src, regionStart, regionLength );
        }

    // #############################################################################################
    // Buffer, length and allocation
    // #############################################################################################

        /** ****************************************************************************************
         * <summary>
         *  The internal buffer character array. This may, but should not be accessed directly.
         *  In case of external modifications be sure to adjust the length of this AString using
         *  SetLength.
         * </summary>
         *
         * <returns> The internal buffer array. </returns>
         ******************************************************************************************/
        public    char[]        Buffer()                     { return buffer;    }

        /** ****************************************************************************************
         * <summary>
         *  Returns the actual length of this %AString. This number is smaller or equals 
         *  the number returned by #GetAllocation.
         * </summary>
         *
         * <returns> The length of the string represented by this. </returns>
         ******************************************************************************************/
        public    int            Length()                     { return length;    }

        /** ****************************************************************************************
         * <summary>
         *  Set the actual length of the stored string. The string can only be shortened with this
         *  method. 
         *  To change the internal allocation size, see #SetAllocation.
         * </summary>
         *
         * <param name="newLength">   The new length of the AString. Must be smaller than the
         *                            current length. </param>
         *
         * <returns> The new length of the string represented by this. </returns>
         ******************************************************************************************/
        public    int            SetLength( int newLength )
        {
            if ( newLength < length )
            {
                length=    newLength;
                hash=    0;
            }
            else
            {
                if ( newLength > length && AWXU_OTW_SetLength && AWXU.AcquireErrorHandler() )
                {
                    AWXU.Warning( "AString::SetLength(): increase requested" );
                    AWXU_OTW_SetLength= false;
                }
            }

            return length;
        }

        /** ****************************************************************************************
         * <summary>
         *  Returns the current size of the internal buffer.
         * </summary>
         *
         * <returns> The size of the allocated buffer. </returns>
         ******************************************************************************************/
        public    int            GetAllocation()             { return buffer.Length;    }

        /** ****************************************************************************************
         * <summary>
         *  Resizes the internal buffer to meet exactly the given size. Attn: If the current string
         *  represented by this instance is larger, the string is cut. This method is deemed for
         *  internal use or very special situations when used from outside.
         *  If the desired new size is 0, then any allocated buffer will be released. However,
         *  the method Buffer() will  still return a pointer to an empty constant character array
         *  (using an internal singleton).
         * </summary>
         * <param name="newSize">   The new size for the allocation buffer. Defaults to -1 which
         *                          will shrink the buffer to fit exactly the current string length.
         *                          </param>
         ******************************************************************************************/
        public    void         SetAllocation( int newSize= -1)
        {
            // default parameter -1: -> set to current length
            if ( newSize == -1 )
                newSize= length;

            // check
            if ( buffer.Length == newSize )
                return;

            // As a side effect, flag has value as dirty
            hash= 0;

            // set uninitialized
            if ( newSize == 0 )
            {
                buffer=  nullBuffer;
                length=  0;
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
                Array.Copy( buffer, newBuffer, length );
            }
            buffer= newBuffer;
        }

        /** ****************************************************************************************
         * <summary>
         *  Ensures that the capacity of the internal buffer meets or exceeds the given value.
         * </summary>
         * <param name="minLen">    The minimum length. </param>
         ******************************************************************************************/
        public void         EnsureAllocation( int minLen )
        {
            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough? if not, increase at least by 50%
            int allocSize= buffer.Length;
            if ( allocSize < minLen )
                SetAllocation(  Math.Max( minLen, allocSize + (allocSize / 2) ) );
        }

        /** ****************************************************************************************
         * <summary>
         *  Ensures that the capacity of the internal buffer meets or exceeds the actual length
         *  plus the given growth value.
         * </summary>
         * <param name="growth"> The desired growth of length. </param>
         ******************************************************************************************/
        public void         EnsureAllocationRelative( int growth )
        {
            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough? if not, increase at least by 50%
            int allocSize= buffer.Length;
            if ( allocSize < length + growth )
                SetAllocation(  Math.Max( length + growth, allocSize + (allocSize / 2) ) );
        }

        /** ****************************************************************************************
         * <summary>
         *    Clear the Buffer. Same as #Delete (0, Length()) but without internal region checks.
         * </summary>
         * <returns> 'this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public AString         Clear()                        { length=    tabReference= 0;    return this;    }

        /** ****************************************************************************************
         * <summary>
         *    Deletes a region from the Buffer.
         *  Note: To delete all contents use #Clear.
         * </summary>
         *
         * <param name="regionStart">  The start of the region to delete.</param>
         * <param name="regionLength"> The length of the region to delete. Defaults to int.MaxValue.
         *                                </param>
         *
         * <returns> 'Assert.AreEqual' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public    AString     Delete( int regionStart, int regionLength= int.MaxValue )
        {
            // adjust range, if empty do nothing
            if ( adjustRegion( length, ref regionStart, ref regionLength ) )
                return this;

            int regionEnd= regionStart + regionLength;

            // case: region reaches to the end?
            if ( regionEnd == length )
            {
                if ( tabReference > regionStart )
                    tabReference=   regionStart;

                length=    regionStart;
                return this;
            }

            // case: region does not include this strings' end
            if ( tabReference > regionStart  && tabReference < regionEnd )
                tabReference= regionStart;

            Array.Copy( buffer, regionEnd, buffer, regionStart, length - regionEnd  );
            length-= regionLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * <summary>
         *    Inserts a region into the Buffer. The region gets filled with the given character.
         * </summary>
         *
         * <param name="regionStart">    The start of the region to insert. If this is out of the
         *                               string bounds (hence less than 0 or greater then #Length),
         *                               nothing is done.
         *                               </param>
         * <param name="regionLength">   The length of the region to insert.</param>
         * <param name="fillChar">       (Optional) The character to fill the new region with.
         *                               Defaults to ' ' (space). </param>
         *
         * <returns> 'this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public    AString     Insert( int regionStart, int regionLength, char fillChar= ' ' )
        {
            // check
            if ( regionStart < 0 || regionStart > length || regionLength <= 0 )
                return this;
            EnsureAllocationRelative( regionLength);

            // adjust tab reference if behind us
            if ( tabReference > regionStart )
                tabReference+=  regionLength;

            // move content and fill new region
            int regionEnd= regionStart + regionLength;
            Array.Copy( buffer, regionStart, buffer, regionEnd, length - regionStart );
            for ( int i= regionStart; i < regionEnd ; i++ )
                buffer[i]= fillChar;

            length+= regionLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * <summary>
         *  Fills a region of this AString with the given character
         *  If out of bounds, the given region is adjusted. The length of this remains unchanged.
         * </summary>
         *
         * <param name="c">              The character to set.</param>
         * <param name="regionStart">    The start of the region in this to set.</param>
         * <param name="regionLength">   The length of the region in this to set.</param>
         * <returns> 'this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public AString Fill( char c, int regionStart= 0, int regionLength= int.MaxValue )
        {
            // empty region?
            if ( adjustRegion( length, ref regionStart, ref regionLength ) )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a null object anymore!
                if ( buffer.Length == 0 )
                    EnsureAllocation( 15 );
                return this;
            }

            // set region
            int regionEnd= regionStart + regionLength;
            for ( int i= regionStart ; i < regionEnd ; i++ )
                buffer[i]= c;

            return this;
        }

        /** ****************************************************************************************
         * <summary> Appends platform specific new line character(s). ( "\\r\\n", "\\r", etc.). The
         * new length of the string is recorded as the reference position for #Tab. </summary>
         * <returns> 'this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public AString NewLine()
        {
            // save tab reference and append new line characters
            tabReference= length + NEWLINE.Length;
            return Append( NEWLINE );
        }

        /** ****************************************************************************************
         * <summary>
         *   Go to the next tab stop by filling in pad characters repeatedly. The tab position is
         *    relative to the starting of the current line (if subsequent calls to #NewLine where
         *    performed).
         * </summary>
         * <param name="tabSize">  The tab positions are multiples of this parameter. </param>
         * <param name="minPad">   (Optional) The minimum pad characters to add. Defaults to 1.
         *                         </param>
         * <param name="tabChar">  (Optional) The character to insert to reach the tab position.
         *                         Defaults to ' ' (space). </param>
         * <returns>    'this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public AString Tab( int tabSize, int minPad= 1, char tabChar= ' ')
        {
            int qtyChars= minPad > 0 ? minPad : 0;
            if ( tabSize > 1 )
                qtyChars+= (tabSize - ( (length + qtyChars - tabReference) % tabSize ) ) % tabSize;

            if ( qtyChars <= 0 )    return this;
            if ( qtyChars == 1 )    return Append ( tabChar );
                                    return Append ( tabChar, qtyChars );
        }

    // #############################################################################################
    // Append
    // #############################################################################################

    /** ********************************************************************************************
     * <summary> Append a region of the given AString. </summary>
     *
     * <param name="src">            The AString to append. </param>
     * <param name="regionStart">    The start of the region in src to append. Defaults to 0.</param>
     * <param name="regionLength">   The maximum length of the region in src to append. Defaults to
     *                               int.MaxInt</param>
     *
     * <returns> 'this' to allow concatenated calls. </returns>
     **********************************************************************************************/
    public AString Append( AString src, int regionStart= 0, int regionLength= int.MaxValue )
    {
        // check null argument
        if ( src == null )
            return this;

        // adjust range, if empty do nothing
        if ( adjustRegion( src.length, ref regionStart, ref regionLength ) )
        {
            // special treatment if currently nothing is allocated
            // we allocate, which means, we are not a null object anymore!
            if ( buffer.Length == 0 )
                EnsureAllocation( 15 );
            return this;
        }

        // check capacity
        EnsureAllocationRelative( regionLength );

        // copy
        Array.Copy( src.buffer, regionStart, buffer, length, regionLength );
        length+= regionLength;

        // return me for concatenated operations
        return this;
    }


    /** ********************************************************************************************
     * <summary> Append a region of a String. </summary>
     *
     * <param name="src">            The String to append. </param>
     * <param name="regionStart">    The start of the region in src to append. Defaults to 0.</param>
     * <param name="regionLength">   The maximum length of the region in src to append. Defaults to
     *                               int.MaxInt</param>
     *
     * <returns> 'this' to allow concatenated calls. </returns>
     **********************************************************************************************/
    public AString Append( String src, int regionStart= int.MinValue, int regionLength=int.MaxValue )
    {
        // check null argument
        if ( src == null )
            return this;

        int srcLen;
        if ( (srcLen= src.Length) == 0 )
        {
            // special treatment if currently nothing is allocated
            // we allocate, which means, we are not a null object anymore!
            if ( buffer.Length == 0 )
                EnsureAllocation( 15 );
            return this;
        }

        // called with default parameters (Append(src))?
        if ( regionStart == int.MinValue )
        {
            regionStart=    0;
            regionLength=    srcLen;
        }
        else
        {
            if ( adjustRegion( srcLen, ref regionStart, ref regionLength ) )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a null object anymore!
                if ( buffer.Length == 0 )
                    EnsureAllocation( 15 );
                return this;
            }
        }

        // check capacity
        EnsureAllocationRelative( regionLength );

        // copy and adjust my length
        src.CopyTo( regionStart, buffer, length, regionLength );
        length+= regionLength;

        // return me for concatenated operations
        return this;
    }

    /** ********************************************************************************************
     * <summary> Append a region of the given StringBuilder. </summary>
     * <param name="src">          The StringBuilder to append. </param>
     * <param name="regionStart">  The start of the region in src to append. Defaults to 0.</param>
     * <param name="regionLength"> The maximum length of the region in src to append. Defaults to
     *                             int.MaxInt</param>
     * <returns>    'this' to allow concatenated calls. </returns>
     **********************************************************************************************/
    public AString Append( StringBuilder src, int regionStart= int.MinValue, int regionLength= int.MaxValue )
    {
        // check null argument
        if ( src == null )
            return this;

        int srcLen;
        if ( (srcLen= src.Length) == 0 )
        {
            // special treatment if currently nothing is allocated
            // we allocate, which means, we are not a null object anymore!
            if ( buffer.Length == 0 )
                EnsureAllocation( 15 );
            return this;
        }

        // called with default parameters (Append(src))?
        if ( regionStart == int.MinValue )
        {
            regionStart=    0;
            regionLength=    srcLen;
        }
        else
        {
            if ( adjustRegion( srcLen, ref regionStart, ref regionLength ) )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a null object anymore!
                if ( buffer.Length == 0 )
                    EnsureAllocation( 15 );
                return this;
            }
        }

        // check capacity
        EnsureAllocationRelative( regionLength );

        // copy and adjust my length
        #if !ALOX_WP71
            // standard versions
            src.CopyTo( regionStart, buffer, length, regionLength );
            length+= regionLength;
        #else
            // Windows Phone 7.1 version (StringBuilder.CopyTo() not available)
            for (int i= 0; i < length; i++ )
                Buffer[ Length++ ]= sb[ startIdx + i ];
        #endif

        // return me for concatenated operations
        return this;
    }


    /** ********************************************************************************************
     * <summary> Append the given character. </summary>
     * <param name="c">    The character to append. </param>
     *
     * <returns> 'this' to allow concatenated calls. </returns>
     **********************************************************************************************/
    public AString Append( char c )
    {
        EnsureAllocationRelative( 1 );
        buffer[ length++ ]= c;

        // return me for concatenated operations
        return this;
    }

    /** ********************************************************************************************
     * <summary> Append the given character repeatedly. </summary>
     *
     * <param name="c">      The character to append. </param>
     * <param name="qty">    The quantity of characters to append. </param>
     *
     * <returns>    'this' to allow concatenated calls. </returns>
     **********************************************************************************************/
    public AString Append( char c, int qty )
    {
        EnsureAllocationRelative( qty );
        for ( int i= 0; i< qty; i++ )
            buffer[length++]= c;

        // return me for concatenated operations
        return this;
    }

    /** ********************************************************************************************
     * <summary> Append the given integer value. </summary>
     *
     * <param name="i">            The integer value to append. </param>
     * <param name="minDigits">    The minimum number of digits to append. If given value has less
     *                             digits, '0' characters are prepended.
     *                             Optional, defaults to 0. </param>
     * <returns> 'this' to allow concatenated calls. </returns>
     **********************************************************************************************/
    public AString Append( int i, int minDigits= 1 )
    {
        // Max/min Value: +/-2147483648
        // ensure capacity
        EnsureAllocationRelative( 11 ); // 10 + minus sign

        if ( i < 0 )
        {
            buffer[length++] = '-';
            return Append( (uint) -i, minDigits );
        }

        return Append( (uint) i, minDigits );
    }

    /** ********************************************************************************************
     * <summary> Append the given unsigned integer value. </summary>
     *
     * <param name="i">            the integer value to append. </param>
     * <param name="minDigits">    The minimum number of digits to append. If given value has less
     *                             digits, '0' characters are prepended.
     *                             Optional, defaults to 0. </param>
     * <returns> 'this' to allow concatenated calls. </returns>
     **********************************************************************************************/
    public AString Append( uint i, int minDigits= 1 )
    {
        // Max Value: 4294967296
        // ensure capacity
        EnsureAllocationRelative( 10 );

        // at least one digit!
        if ( minDigits < 1 )
            minDigits= 1;

        // main loop
        int        actDigit=        11; // 10 + 1 for the loop
        uint    actBase=        1000000000;
        bool    isUnder=        false;
        while ( --actDigit > 0)
        {
            // get next d
            uint d=            i / actBase;
            uint actBase2=  actBase;
            actBase/=    10;

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

    /** ********************************************************************************************
     * <summary>
     *  Append the given double value using the minimum digits before and after the given number of
     *  digits after dot.
     * </summary>
     * <param name="d">                    the integer value to append. </param>
     * <param name="minDigitsBeforeDot">   The minimum number of digits write before the dot. If the
     *                                     number has less digits than minDigits, then trailing '0's
     *                                     are added. Defaults to 0.</param>
     * <param name="digitsAfterDot">       The exact number of digits written after the dot.
                                           Defaults to 5.</param>
     * <returns>    'this' to allow concatenated calls. </returns>
     **********************************************************************************************/
    public AString Append( double d, int minDigitsBeforeDot= 0, int digitsAfterDot= 5 )
    {
        // negative? -> turn positive
        if ( d < 0d )
        {
            Append( '-' );
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
        int afterDot= (int) Math.Round( d );
        if ( afterDot == overflow )
        {
            afterDot= 0;
            beforeDot++;
        }

        // append integer part
        Append( beforeDot, minDigitsBeforeDot ).Append( '.' );

        // check for no digits after dot wanted
        if ( digitsAfterDot > 0 )
            Append( afterDot, digitsAfterDot );

        // return me for concatenated operations
        return this;
    }

    // #############################################################################################
    // fields
    // #############################################################################################

        /** ****************************************************************************************
         * <summary>
         * If invoked without parameters, the start of a field is marked at the current end of
         * the string. Otherwise the end of a field is set and the contents between the field start
         * marker and the current end of the string is aligned within the field using the given pad
         * character.
         * Note: To implement nested fields, the outer fields have to be set by providing the start
         * marker by using the parameter fieldStart. Hence, only the starting points of the most
         * inner fields can be set using this method without parameters.
         * </summary>
         *
         * <param name="size">        The field size in relation to the starting index of the field,
         *                            defined either by using Field() prior to this invocation or by
         *                            providing the parameter fieldStart.
         *                            The field gets filled with the given pad character to meet the
         *                            size while the content gets aligned left, right or centered.
         *                            If the content exceeds the size, then no alignment takes
         *                            place. </param>
         * <param name="alignment">   The alignment of the contents within the field.
         *                            Defaults to AString.Align.Right.
         *                            Other options are AString.Align.Left and AString.Align.Center.
         *                            </param>
         * <param name="padChar">     The character used to fill the field up to its size.
         *                            Defaults to ' ' (space).</param>
         * <param name="fieldStart">  This parameter, if given, overwrites the start index of the
         *                            field. The invocation of Field can be omitted, when this
         *                            value is explicitly provided.
         *                            Defaults to int.MaxValue. </param>

         * <returns> 'this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public AString Field( int size=-1, Align alignment= Align.Right, char padChar= ' ', int fieldStart= int.MaxValue )
        {
            // if size is -1, this is just a field start marker invocation
            if ( size < 0 )
            {
                fieldReference= length;
                return this;
            }

            // if no field start is given, use the saved one (default behaviour)
                if ( fieldStart == int.MaxValue )
                fieldStart=        fieldReference;

            // check pad size
            int padSize=    size - (length - fieldStart);
            if (padSize <= 0 )
                return this;

            // align left
            if ( alignment == Align.Left )
            {
                Append( padChar, padSize );
                return this;
            }

            // align Right
            if ( alignment == Align.Right )
            {
                Insert( fieldStart, padSize, padChar );
                return this;
            }

            // align Center
            Insert( fieldStart,    padSize >> 1,     padChar );
            Append( padChar, padSize - ( padSize >> 1 ) );
            return this;
        }

    // #############################################################################################
    // containsAt, startsWith, endsWith
    // #############################################################################################

        /** ****************************************************************************************
         * <summary> Checks if the given String is located at the given position. </summary>
         * <param name="needle">      The string to search. </param>
         * <param name="pos">         The position to look at. </param>
         * <param name="ignoreCase">  (Optional) If true, the compare is case insensitive. Optional
         *                            and defaults to false. </param>
         * <returns>
         *  True if the given sequence is found at the given position. False otherwise .
         * </returns>
         ******************************************************************************************/
        public bool ContainsAt( String needle, int pos, bool ignoreCase= false )
        {
            // check null argument or length 0
            int needleLen=  needle != null ?  needle.Length : 0;
            int cmpEnd=     pos + needleLen;
            if ( pos < 0 || cmpEnd > length )
                return false;

            // the compare loop
            int sPos= 0;
            while ( pos < cmpEnd )
            {
                char c1= needle[ sPos ];
                char c2= buffer[ pos ];
                if ( ignoreCase )
                {
                    c1=  Char.ToLower( c1 );
                    c2=  Char.ToLower( c2 );
                }

                if ( c1 != c2 )
                    return false;

                pos++;
                sPos++;
            }

            return true;
        }

        /** ****************************************************************************************
         * <summary> Checks if the given AString is located at the given position. </summary>
         * <param name="needle">      The AString to search. </param>
         * <param name="pos">         The position to look at. </param>
         * <param name="ignoreCase">  (Optional) If true, the compare is case insensitive. Optional
         *                            and defaults to false. </param>
         * <returns>
         *  True if the given AString is found at the given position. False otherwise .
         * </returns>
         ******************************************************************************************/
        public bool ContainsAt( AString needle, int pos, bool ignoreCase= false )
        {
            // check null argument or length 0
            int needleLen=  needle != null ?  needle.Length() : 0;
            int cmpEnd=     pos + needleLen;
            if ( pos < 0 || cmpEnd > length )
                return false;
            if ( needleLen == 0 )
                return true;


            // the compare loop
            int sPos= 0;
            char[] nbuffer= needle.Buffer();
            while ( pos < cmpEnd )
            {
                char c1=  nbuffer[ sPos ];
                char c2=  buffer [ pos ];
                if ( ignoreCase )
                {
                    c1=  Char.ToLower( c1 );
                    c2=  Char.ToLower( c2 );
                }

                if ( c1 != c2 )
                    return false;

                pos++;
                sPos++;
            }

            return true;
        }

        /** ****************************************************************************************
         * <summary> Checks if this AString starts with the given String. </summary>
         *
         * <param name="needle">      The String to search. If s is null or empty, false is returned.</param>
         * <param name="ignoreCase">  If true, the compare is case insensitive. Optional and defaults to
         *                            false. </param>
         *
         * <returns> true if this starts with the given sequence, false if not.</returns>
         ******************************************************************************************/
        public bool StartsWith( String needle,    bool ignoreCase= false )
        {
            return ContainsAt( needle, 0, ignoreCase );
        }

        /** ****************************************************************************************
         * <summary> Checks if this AString starts with the given String. </summary>
         *
         * <param name="needle">      The AString to search. If s is null or empty, false is returned.</param>
         * <param name="ignoreCase">  If true, the compare is case insensitive. Optional and defaults to
         *                            false. </param>
         *
         * <returns> true if this starts with the given AString, false if not.</returns>
         ******************************************************************************************/
        public bool StartsWith( AString needle,    bool ignoreCase= false )
        {
            return ContainsAt( needle, 0, ignoreCase );
        }

        /** ****************************************************************************************
         * <summary> Checks if this String ends with the given String. </summary>
         * <param name="needle">      The string to be compared with the start of this AString. If this is null or
         *                            empty, true is returned.</param>
         * <param name="ignoreCase">  If true, the compare is case insensitive. Optional and defaults to
         *                            false. </param>
         * <returns> true if this starts with the given String, false if not.</returns>
         ******************************************************************************************/
        public bool EndsWith  ( String needle, bool ignoreCase= false )
        {
            if ( needle == null )
                return false;

            return ContainsAt( needle, length - needle.Length, ignoreCase );
        }
        /** ****************************************************************************************
         * <summary> Checks if this AString ends with the given AString. </summary>
         * <param name="needle">      The AString to be compared with the start of this AString. If this is null or
         *                            empty, true is returned.</param>
         * <param name="ignoreCase">  If true, the compare is case insensitive. Optional and defaults to
         *                            false. </param>
         * <returns> true if this starts with the given AString, false if not.</returns>
         ******************************************************************************************/
        public bool EndsWith  ( AString needle, bool ignoreCase= false )
        {
            if ( needle == null )
                return false;

            return ContainsAt( needle, length - needle.Length(), ignoreCase );
        }

    // #############################################################################################
    // indexOf
    // #############################################################################################

        /** ****************************************************************************************
         * <summary> Search the given String in this. </summary>
         *
         * <param name="needle">       The String to search. </param>
         * <param name="startIdx">     The index to start the search at. Optional and defaults to 0. </param>
         * <param name="ignoreCase">   If true, the compare is case insensitive. Optional and defaults to
         *                             false. </param>
         * <returns>    -1 if the String is not found. Otherwise the index of first occurrence. </returns>
         ******************************************************************************************/
        public int IndexOf( String needle, int startIdx= 0, bool ignoreCase= false  )
        {
            // check null argument or length 0
            int needleLen=  needle != null ?  needle.Length : 0;

            // checks
            if ( startIdx < 0 )                     startIdx= 0;
            if ( startIdx + needleLen > length )    return -1;
            if ( needleLen == 0  )                  return  startIdx;


            // not ignore case
            if (!ignoreCase)
            {
                char firstChar= needle[ 0 ];     // get first char once, as [] operation is expensive
                while ( startIdx < length )
                {
                    int     cmpLen= 0;
                    char    sc=     firstChar;
                    while ( buffer[ startIdx + cmpLen ] == sc )
                    {
                        cmpLen++;
                        if ( cmpLen == needleLen )
                            return startIdx;
                        sc= needle[cmpLen];
                    }
                    startIdx++;
                }
            }

            // ignore case
            else
            {
                char firstChar= Char.ToLower( needle[ 0 ] );     // get first char once, as [] operation is expensive
                while ( startIdx < length )
                {
                    int     cmpLen= 0;
                    char    sc=     firstChar;
                    while ( Char.ToLower( buffer[ startIdx + cmpLen ] ) == sc )
                    {
                        cmpLen++;
                        if ( cmpLen == needleLen )
                            return startIdx;
                        sc= Char.ToLower( needle[cmpLen] );
                    }
                    startIdx++;
                }
            }

            // not found
            return -1;
        }

        /** ****************************************************************************************
         * <summary> Search the given AString in the this. </summary>
         *
         * <param name="needle">       The String to search. </param>
         * <param name="startIdx">     The index to start the search at. Optional and defaults to 0. </param>
         * <param name="ignoreCase">   If true, the compare is case insensitive. Optional and defaults to
         *                             false. </param>
         * <returns>    -1 if the String is not found. Otherwise the index of first occurrence. </returns>
         ******************************************************************************************/
        public int IndexOf( AString needle, int startIdx= 0, bool ignoreCase= false  )
        {
            // check null argument or length 0
            int needleLen=  needle != null ?  needle.length : 0;

            // checks
            if ( startIdx < 0 )                        startIdx= 0;
            if ( startIdx + needleLen > length )    return -1;
            if ( needleLen == 0  )                    return  startIdx;

            char[]    needleBuf=    needle.buffer;

            // not ignore case
            if (!ignoreCase)
            {
                char firstChar= needleBuf[ 0 ];     // get first char once, as [] operation is expensive
                while ( startIdx < length )
                {
                    int     cmpLen= 0;
                    char    sc=     firstChar;
                    while ( buffer[ startIdx + cmpLen ] == sc )
                    {
                        cmpLen++;
                        if ( cmpLen == needleLen )
                            return startIdx;
                        sc= needleBuf[cmpLen];
                    }
                    startIdx++;
                }
            }

            // not ignore case
            else
            {
                char firstChar= Char.ToLower( needleBuf[ 0 ] );     // get first char once, as [] operation is expensive
                while ( startIdx < length )
                {
                    int     cmpLen= 0;
                    char    sc=     firstChar;
                    while ( Char.ToLower( buffer[ startIdx + cmpLen ] ) == sc )
                    {
                        cmpLen++;
                        if ( cmpLen == needleLen )
                            return startIdx;
                        sc= Char.ToLower( needleBuf[cmpLen] );
                    }
                    startIdx++;
                }
            }

            // not found
            return -1;
        }

        /** ****************************************************************************************
         * <summary> Search the given character in the buffer. </summary>
         *
         * <param name="c">         The character to search . </param>
         * <param name="startIdx">  The index to start the search at. Optional and defaults to 0. </param>
         *
         * <returns>    -1 if the character is not found. Otherwise the index of first occurrence. </returns>
         ******************************************************************************************/
        public int IndexOf( char c, int startIdx= 0 )
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


    // #############################################################################################
    // replace
    // #############################################################################################

        /** ****************************************************************************************
         * <summary>
         *     Replace one or more occurrences of a string by another string. Returns the number
         *     of replacements.
         *  </summary>
         *
         * <param name="searchStr">        The String to be replaced. </param>
         * <param name="newStr">           The replacement string. </param>
         * <param name="startIdx">         The index where the search starts. Optional and defaults
         *                                 to 0. </param>
         * <param name="maxReplacements">  The maximum number of replacements to perform. Optional and
         *                                 defaults to int.MaxValue . </param>
         * <param name="ignoreCase">       If true, a case insensitive search is performed. Defaults to false.
         *                                    </param>
         *
         * <returns> The number of replacements that where performed. </returns>
         ******************************************************************************************/
        public int ReplaceCount( String searchStr, String newStr, int startIdx= 0, int maxReplacements= int.MaxValue, bool ignoreCase= false )
        {
            // check null arguments
            if ( String.IsNullOrEmpty(searchStr) )
                return 0;

            // get some values
            int searchStringLength=   searchStr.Length;
            int newStringLength=      (newStr != null) ? newStr.Length : 0;
            int lenDiff=              newStringLength - searchStringLength;

            // replacement loop
            int cntReplacements=    0;
            int idx= -1;
            while ( cntReplacements < maxReplacements && idx < length)
            {
                // search  next occurrence
                if ( ( idx= IndexOf( searchStr, startIdx, ignoreCase ) ) < 0 )
                    return cntReplacements;

                // set dirty
                hash= 0;

                // copy rest up or down
                if ( lenDiff != 0 )
                {
                    EnsureAllocationRelative( lenDiff );
                    Array.Copy( buffer, idx + searchStringLength, buffer, idx + searchStringLength + lenDiff, length - idx - searchStringLength );
                    length+= lenDiff;
                }

                // fill replacement in
                for ( int i= 0; i < newStringLength ; i++ )
                    buffer[ idx + i ]= newStr[ i ];

                // set start index to first character behind current replacement
                startIdx= idx+ newStringLength;

                // next
                cntReplacements++;
            }

            // that's it
            return cntReplacements;
        }

        /** ****************************************************************************************
         * <summary>
         *   Replace one or more occurrences of a string by another string. Returns the number
         *   of replacements.
         * </summary>
         *
         * <param name="searchStr">        The String to be replaced. </param>
         * <param name="newStr">           The replacement string. </param>
         * <param name="startIdx">         The index where the search starts. Optional and defaults
         *                                 to 0. </param>
         * <param name="maxReplacements">  The maximum number of replacements to perform. Optional and
         *                                 defaults to int.MaxValue . </param>
         * <param name="ignoreCase">       If true, a case insensitive search is performed. Defaults to false.
         *                                 </param>
         *
         * <returns> The number of replacements that where performed. </returns>
         ******************************************************************************************/
        public int ReplaceCount( AString searchStr, AString newStr, int startIdx= 0, int maxReplacements= int.MaxValue, bool ignoreCase= false )
        {
            // check null arguments
            if ( IsNullOrEmpty(searchStr) )
                return 0;

            // get some values
            int     searchStringLength=   searchStr.length;
            int     newStringLength=      (newStr != null) ? newStr.length : 0;
            char[]  newStrBuf=            (newStr != null) ? newStr.Buffer() : null;
            int     lenDiff=              newStringLength - searchStringLength;

            // replacement loop
            int cntReplacements=    0;
            int idx= -1;
            while ( cntReplacements < maxReplacements && idx < length)
            {
                // search  next occurrence
                if ( ( idx= IndexOf( searchStr, startIdx, ignoreCase ) ) < 0 )
                    return cntReplacements;

                // set dirty
                hash= 0;

                // copy rest up or down
                if ( lenDiff != 0 )
                {
                    EnsureAllocationRelative( lenDiff );
                    Array.Copy( buffer, idx + searchStringLength, buffer, idx + searchStringLength + lenDiff, length - idx - searchStringLength );
                    length+= lenDiff;
                }

                // fill replacement in
                for ( int i= 0; i < newStringLength ; i++ )
                    buffer[ idx + i ]= newStrBuf[ i ];

                // set start index to first character behind current replacement
                startIdx= idx+ newStringLength;

                // next
                cntReplacements++;
            }

            // that's it
            return cntReplacements;
        }

        /** ****************************************************************************************
         * <summary>
         *   Replace one or more occurrences of a string by another string. To receive the number of
         *   replacements, see alternative method #ReplaceCount().
         * </summary>
         *
         * <param name="searchStr">        The string to be replaced. </param>
         * <param name="newStr">           The replacement string. </param>
         * <param name="startIdx">         The index where the search starts. Optional and defaults
         *                                 to 0. </param>
         * <param name="maxReplacements">  The maximum number of replacements to perform. Optional and
         *                                 defaults to int.MaxValue . </param>
         * <param name="ignoreCase">       If true, a case insensitive search is performed. Defaults to false.
         *                                    </param>
         *
         * <returns> 'this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public AString Replace( String searchStr, String newStr, int startIdx= 0, int maxReplacements= int.MaxValue, bool ignoreCase= false )
        {
            ReplaceCount( searchStr, newStr, startIdx, maxReplacements, ignoreCase );
            return this;
        }

    // #############################################################################################
    // compareTo
    // #############################################################################################

        /** ****************************************************************************************
         * Compares a given region of a given string with the a region of this instance. Regions that are
         * out of bounds get adjusted and then compared. If this behavior is not what is wanted, a separate
         * region check and corresponding compare result evaluation has to be performed.
         *
         * <param name="compareString">
         *   An object of type String, StringBuffer or AString that is compared to this. </param>
         * <param name="ignoreCase">
         *   If true, the compare is case insensitive. Optional and defaults to false.</param>
         * <param name="compareStringRegionStart">
         *   The start of the substring within the given string that is to be compared
         *   to this. Defaults to 0. </param>
         * <param name="compareStringRegionLength">
         *   The length of the substring within the given string that is to be compared to this.
         *   Defaults to Integer.MAX_VALUE. </param>
         * <param name="regionStart">
         *   The start of the substring within this string that is to be compared. Defaults    to 0. </param>
         * <param name="regionLength">
         *   The length of the substring within this string that is to be compared. Defaults to
         *     Integer.MAX_VALUE. </param>
         *
         * <returns>
         *   0 if the contents of the string regions are equal (or if both regions are empty or out of range).
         *      -1 if the instance is less than the given string.
         *      +1 if the instance is greater than the given string or if given string is null.
         * </returns>
         ******************************************************************************************/
        public int CompareTo(   Object    compareString,
                                bool      ignoreCase=                 false,
                                int       compareStringRegionStart=    0,
                                int       compareStringRegionLength=    int.MaxValue,
                                int       regionStart=                0,
                                int       regionLength=                int.MaxValue    )
        {
            // check null argument
            if ( buffer.Length == 0   )     return  compareString == null ? 0 : -1;
            if ( compareString == null)     return  +1;


            // convert object to one of the three supported types
            String            cmpS=    null;
            StringBuilder    cmpSB=    null;
            AString    cmpMS=  compareString as AString;
            if (cmpMS == null )
            {
                cmpSB= compareString as StringBuilder;
                if (cmpSB == null )
                {
                    cmpS=    compareString as String;
                    if (cmpS == null )
                    {
                        return 1; // unsupported object type given
                    }
                }
            }

            // get length of cmp compareString
            int cmpLength= cmpMS != null ?                        cmpMS.length
                                         : ( cmpSB != null    ?    cmpSB.Length
                                                            :    cmpS .Length  );

            // adjust source and compare regions
            adjustRegion( cmpLength, ref compareStringRegionStart, ref compareStringRegionLength );
            adjustRegion(    length, ref  regionStart, ref  regionLength );

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
                char cmpC=    cmpMS != null    ?   cmpMS.buffer[ cmpIdx ]
                                               : ( cmpSB != null    ?    cmpSB[ cmpIdx ]
                                                                    :    cmpS [ cmpIdx ]  );
                if ( srcC != cmpC )
                {
                    // no match!
                    if ( !ignoreCase )
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

    // #############################################################################################
    // convertCase
    // #############################################################################################

        /** ****************************************************************************************
         * <summary> Converts all or a region of characters in the Buffer to upper or to lower case. </summary>
         *
         * <param name="toUpper">         If true, conversion to upper case is performed, to lower else. </param>
         * <param name="substrStart">     Start of the substring to be converted. Defaults to 0 </param>
         * <param name="substrLength">    Length of the substring to be converted. Defaults to int.MaxValue.</param>
         *
         * <returns> 'this' to allow concatenated calls. </returns>
         ******************************************************************************************/
        public AString ConvertCase( bool toUpper, int substrStart= 0, int substrLength= int.MaxValue )
        {
            // mark has value as dirty
            hash= 0;

            // adjust range
            if ( substrLength == int.MaxValue )
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
                buffer[ i ]=  toUpper   ?    Char.ToUpperInvariant( buffer[ i ] )
                                        :    Char.ToLowerInvariant( buffer[ i ] );

            // return me for concatenated operations
            return this;
        }

    // #############################################################################################
    // toString, toInt
    // #############################################################################################

        /** ****************************************************************************************
         * <summary> Creates a String containing a copy of the contents of this AString. </summary>
         *
         * <returns> A String that represents this object. </returns>
         ******************************************************************************************/
        public override String ToString()
        {
            return new String( buffer, 0, length );
        }

        /** ****************************************************************************************
         * <summary> Creates a String containing a copy of a region of the contents of this
         *    AString. </summary>
         *
         * <param name="regionStart">   The start index of the region in this to create the string from. </param>
         * <param name="regionLength">  (Optional) The maximum length of the region to create the string from.
         *                              Defaults to int.MaxValue. </param>
         *
         * <returns> A String that represents the specified sub region of this object. </returns>
         ******************************************************************************************/
        public string ToString( int regionStart, int regionLength= int.MaxValue)
        {
            // adjust range, if empty return empty string
            if ( adjustRegion( length, ref regionStart, ref regionLength ) )
                return "";

            // create string
            return new String( buffer, regionStart, regionLength);
        }

        /** ****************************************************************************************
         * <summary> Copies a region of the contents of this AString into the given StringBuilder. </summary>
         *
         * <param name="result">        A result string to copy the specified region into. </param>
         * <param name="regionStart">   The start index of the region to be copied. </param>
         * <param name="regionLength">  The maximum length of the region to be copied.
         *                              Defaults to int.MaxValue. </param>
         * <param name="appendMode">    Optional: If true, any contents in the result is preserved. Otherwise
         *                              such content gets replaced (default). </param>
         *
         * <returns> The (modified) result that was provided (for concatenation of calls). </returns>
         ******************************************************************************************/
        public StringBuilder ToString( StringBuilder result, int regionStart, int regionLength= int.MaxValue, bool appendMode= false  )
        {
            if ( !appendMode )
                result.Clear();

            // adjust range, if empty return empty string
            if ( adjustRegion( length, ref regionStart, ref regionLength ) )
                return result;

            // copy our buffer into result
            result.Append( buffer , regionStart, regionLength );
            return  result;
        }



        /** ****************************************************************************************
         * <summary> Copies the contents of this AString into the given StringBuilder. </summary>
         *
         * <param name="result">        A result string to copy the contents of this AString into. </param>
         * <param name="appendMode">    Optional: If true, any contents in the result is preserved. Otherwise
         *                              such content gets replaced (default). </param>
         * <returns> The (modified) result that was provided (for concatenation of calls). </returns>
         ******************************************************************************************/
        public StringBuilder ToString( StringBuilder result, bool appendMode= false )
        {
            return ToString( result, 0, length, appendMode );
        }

        /** ****************************************************************************************
         * <summary>
         * Reads a long from the AString at the given position. The given index is increased to point to
         * first character that is not a number. If no number is found a the given index, zero is returned
         * and the provided index is not increased.
         * </summary>
         *
         * <param name="idx"> The start point from where the long value is tried to be read. This
         *                    is provided as reference and will be increased if an integer is found. </param>
         * <returns> The parsed value. In addition, the input parameter startIdx is moved to point to the
         *               first character behind any found long number. </returns>
         ******************************************************************************************/
        public long ToLong( ref int idx )
        {
            long  retVal=    0;
            while ( idx < length )
            {
                char  c= buffer[ idx ];
                if ( c < '0' || c > '9' )
                    break;

                retVal= ( retVal * 10 ) + ( (int) ( c - '0' ) );
                idx++;
            }

            return retVal;
        }

        /** ****************************************************************************************
         * <summary>
         * Reads an integer from the AString at the given position. The given index is increased to point to
         * first character that is not a number. If no number is found a the given index, zero is returned
         * and the provided index is not increased.
         * </summary>
         *
         * <param name="idx">  The start point from where the long value is tried to be read. This
         *                     is provided as reference and will be increased if an integer is found.  </param>
         * <returns> The parsed value. In addition, the input parameter startIdx is moved to point to the
         *              first character behind any found long number. </returns>
         ******************************************************************************************/
        public int ToInt( ref int idx )            {  return (int) ToLong( ref idx );     }


    // #############################################################################################
    // GetHashCode, Equals
    // #############################################################################################

        /** ****************************************************************************************
         * <summary> Calculates the hash value using the same formula as java.lang.String. </summary>
         * <returns> A hash value for this object. </returns>
         ******************************************************************************************/
        public override int GetHashCode()
        {
            int h;
            if ((h= hash) == 0 && length > 0)
            {
                char[] buf=    buffer;
                int  len=    length;

                for (int i = 0; i < len; i++)
                    h = 31*h + buf[i++];

                hash = h;
            }
            return h;
        }


        /** ****************************************************************************************
         * <summary> Compares this to the given object. Given object can be AString or String. </summary>
         * <param name="o">    The Object that this instance is compared with. </param>
         *
         * <returns> True if given object equals this. </returns>
         ******************************************************************************************/
        public override bool Equals( Object o )
        {
            // null?
            if ( o == null )
                return buffer.Length == 0;
            if ( buffer.Length == 0 )
                return false;

            // AString?
            if ( o is AString )
            {
                // cast up
                AString ms=  (AString) o;

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

            // String?
            if ( o is String )
            {
                // cast up
                String s=  (String) o;

                // different length?
                if ( s.Length != length )
                    return false;

                // character compare
                for (int i= length - 1 ; i >= 0 ; i-- )
                    if ( s[ i ] != buffer[ i ] )
                        return false;

                // equal
                return true;
            }

            // not a known comparable object
            return false;
        }

        /** ****************************************************************************************
         * <summary> Static method to test if an AString is null or has a length of 0. </summary>
         * <param name="ms"> The AString to test. </param>
         *
         * <returns> True if given AString is null or has a length of 0. </returns>
         ******************************************************************************************/
        public static bool IsNullOrEmpty( AString ms )        {    return ms == null || ms.length==0;    }

    // #############################################################################################
    // internals
    // #############################################################################################

        /** ****************************************************************************************
         * <summary>
         *    Simple, but frequently used method that adjusts a given region to the range
         *    of [0 .. referenceLength]. First, the region start is checked on negative values. Those
         *    are cut to zero while also shorting the region correspondingly.
         *    Then, the region start is checked if it exceeds the string. If this is the case, the region
         *    will be set to an empty region at the end of the string.
         *    Lastly, the region length is cut so that it does not exceed the length of the string.
         *    The return value of the function indicates if the region is empty.
         * </summary>
         *
         * <param name="referenceLength">   Length of the string that the given region will be adjusted to. </param>
         * <param name="regionStart">       [in,out] The start of the region to be adjusted. </param>
         * <param name="regionLength">      [in,out] The length of the region to be adjusted. </param>
         *
         * <returns> True if adjusted range is empty. </returns>
         ******************************************************************************************/
        protected static bool adjustRegion( int referenceLength, ref int regionStart, ref int regionLength )
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

} // class Mutable String

} // namespace / EOF
