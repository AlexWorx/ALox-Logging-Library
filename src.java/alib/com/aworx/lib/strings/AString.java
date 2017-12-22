// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

/**
 *  This namespace of the A-Worx Library provides classes for character string operations
 *  (following \ref com.aworx.lib "the principle design goals of \b %ALib").
 */
package com.aworx.lib.strings;

import com.aworx.lib.lang.Alignment;
import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Inclusion;
import com.aworx.lib.lang.Switch;

/** ************************************************************************************************
 *  A mutable string, that provides public access to its internal buffer and fields.
 *  First of all, the existence of this class is motivated to reach a certain level of compatibility
 *  between source code that uses the
 *  \ref com.aworx.lib "ALib" across different languages (currently Java, C# and C++) whose
 *  implementations share a similar %AString class.
 *
 *  As the given C#/Java StringBuilder/Buffer classes are either "sealed" and/or do not provide
 *  direct access to the internal buffer, to avoid conversion to new immutable strings in certain
 *  situations, the A-Worx Library implements its own string class. More complex
 *  functions, like extended formatting operations are not supported and remain the domain of the
 *  language specific class libraries.
 *
 *  <b>Null-state:</b><p>
 *  Class %AString is 'nullable', which means, that an instance may have no internal character
 *  array allocated.
 *  If constructed  with zero size, a null pointer or another AString which is 'nulled'
 *  (but not a non-null, zero length string object of any type), the allocation size is 0.
 *  Nevertheless, method #buffer will return a valid empty <em>char[]</em>
 *  (a static singleton). This has the advantage that in many situations the null-state is not
 *  needed to handled specially (those cases where the difference between a nulled and an empty
 *  string is irrelevant).
 *  Consequently, it makes a difference if an %AString is constructed using <em>AString()</em> or
 *  "AString(\"\").
 *  This allows to differentiate between 'nulled' AStrings and empty AStrings, which is quite handy
 *  in certain situations. An object that was filled already can be reset to represent null by
 *  either assigning a nulled AString, by invoking
 *  \ref setBuffer "setBuffer(0)" or by invoking #setNull on the
 *  instance. See also methods #isNull, #isNotNull and #capacity.
 *  The methods #equals and #compareTo allow \c null comparisons. e.g. an nulled %AString equals
 *  to another nulled AString but not to a zero length, not nulled AString.
 *
 *   \anchor JAVA_ASTRING_NC
 *  <p>
 *  <b>Non-checking methods</b><p>
 *  In general, %AString methods are internally checking the provided parameters. For example,
 *  method #_( CharSequence src, int regionStart, int regionLength ) is
 *  adjusting the provided region information to fit to the size of the provided %AString
 *  (in Java CharSequence).<br>
 *  Chances are high, that the code invoking this method "knows" about the correctness of
 *  the region. In this case, the checks are redundant.
 *
 *  For avoiding unnecessary checks, various methods are provided by %AString that omit such checks.
 *  These methods share the same name as the standard one, with the suffix "_NC" appended (NC
 *  stands for "no checks").
 *
 *  In the sample above, if the calling code was sure about the parameters \p regionStart and
 *  \p regionLength being in the bounds of \p src, method
 *  \ref _NC( AString src, int regionStart, int regionLength ) can be used.
 *
 *  \attention The following rules apply to all methods suffixed by <em>_NC</em>:
 *  - Parameters are not checked for being null.
 *  - Index, size, length, region start/end and other parameters are not checked to be correct
 *  - If parameters are incorrect, the result of the methods are undefined
 *    and in debug compilations an assertion may be raised.
 *  - Append methods that in their original version would set a nulled %AString to non nulled
 *    state in the case that an empty string or string region is appended, are not confirming
 *    to this  principle in their <em>_NC</em> version. In other words, nulled strings keep
 *    being nulled if empty strings are appended.
 *  - In the Java and C# versions of the AWorx Library, the hash value of an %AString object keeps
 *    being cached when invoking an <em>_NC</em> method. This may lead to wrong behavior, e.g. when
 *    an %AString object is used as a key of a hash table. To avoid errors, within a context that
 *    makes use of an %AStrings' hash value, before each hash code retrieval
 *    (C#: <em>GetHashCode()</em>, Java: <em>hashCode()</em>),
 *    it has to be certified that at least one of the methods manipulating the object has
 *    to be a non <em>_NC</em> method.
 *  - Apart from the previous points, the behavior and result of invoking an <em>_NC</em> version
 *    of a method is the same as of invoking the original version. The only difference is in a higher
 *    execution performance.
 *  - Another note specific to the Java implementation of the AWorx library: the overloaded
 *    methods including and not including the <em>_NC</em> prefix sometimes vary in their
 *    parameter types. This is because sometimes only generalizations, like replacing an %AString
 *    parameter with more generalized CharSequence type of corresponding methods exist. The
 *    API assures however, that compilation and execution stays correct when removing or
 *    adding <em>_NC</em> to an invocation.
 *
 **************************************************************************************************/
public class AString implements CharSequence
{
    // #############################################################################################
    // protected fields
    // #############################################################################################

        /** The Buffer array. This may but should not be accessed directly. In case of external
         *   modifications the field hash has to be set to dirty (0). */
        protected           char[]              buffer                          = com.aworx.lib.strings.CString.nullBuffer;

        /** The actual length of the string stored in the Buffer. In case of external
            modifications the field hash has to be set to dirty (0). */
        protected           int                 length                          =0;

        /** The tab reference position. This is set when #newLine is invoked. */
        protected           int                 tabReference                    =0;

        /** A marker for the start of the actual field. */
        protected           int                 fieldReference                  =0;

        /** The hash value. Has to be set dirty (0) whenever String is changed from outside!. */
        protected           int                 hash                            =0;

        /**
         *  Used as a return value of method
         *  \ref com.aworx.lib.strings.CString.adjustRegion "CString.adjustRegion"
         */
        protected int[] _adjustedRegion = new int[2];


    /** ############################################################################################
     * @name Constructors and Destructor
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Constructs an empty AString. Does not allocate a buffer.
         ******************************************************************************************/
        public AString()
        {
        }

        /** ****************************************************************************************
         * Constructor allocating a specific buffer size.
         *
         *  \note This constructor is useful for %AString objects whose minimum future string length
         *        is predictable to avoid recurring incremental allocations up to the known
         *        minimum size.
         *
         * @param size    The initial size of the internal buffer.
         ******************************************************************************************/
        public AString( int size  )
        {
            // check
            if ( size > 0 )
                setBuffer( size );
        }

        /** ****************************************************************************************
         * Constructor copying a CharSequence.
         * @param src    The source CharSequence to copy from.
         ******************************************************************************************/
        public AString( CharSequence src )
        {
            _( src );
        }

        /** ****************************************************************************************
         * Constructor copying a region of a CharSequence.
         *
         * @param src            The source CharSequence to copy from.
         * @param regionStart    The start of the region in src to append.
         *                       Defaults to 0.
         ******************************************************************************************/
        public AString( CharSequence src, int regionStart )
        {
            _( src, regionStart, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Constructor copying a region of a CharSequence.
         *
         * @param src            The source CharSequence to copy from.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to Integer.MAX_VALUE.
         ******************************************************************************************/
        public AString( CharSequence src, int regionStart, int regionLength)
        {
            _( src, regionStart, regionLength );
        }


    /** ############################################################################################
     * @name Memory allocation and buffer access
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         *  The internal buffer character array. This may, but should not be accessed directly.
         *  In case of external modifications be sure to adjust the length of this AString using
         *  #setLength.
         *
         * @return The internal buffer array.
         ******************************************************************************************/
        public    char[]   buffer()                    { return buffer;      }

        /** ****************************************************************************************
         *  Resizes the internal buffer to meet exactly the given size.
         *
         *  The following rules apply:
         *  - The string represented by this instance is copied to the new buffer.
         *    If this is larger than the new buffer size, the string is cut at the end to fit.
         *  - If the desired new size is 0, then the currently allocated buffer will be released.
         *    In this case method #buffer will still return an empty constant character array
         *    (using an internal singleton) but method #isNull will return true.
         *
         *  \note Any methods of this class that extend the length of the string represented, will
         *        invoke this method if the current buffer size is not sufficient.
         *        If a future string length of an %AString is predictable, then it is advisable
         *        to allocate such size upfront to avoid recurring allocations.
         *
         * @param newCapacity   The new capacity of the internal buffer.
         ******************************************************************************************/
        public    void     setBuffer( int newCapacity )
        {
            // default parameter -1: -> set to current length
            if ( newCapacity == -1 )
                newCapacity= length;

            // check
            if ( buffer.length == newCapacity )
                return;

            // As a side effect, flag has value as dirty
            hash= 0;

            // set uninitialized
            if ( newCapacity == 0 )
            {
                buffer=        com.aworx.lib.strings.CString.nullBuffer;
                length=        0;
                return;
            }

            // create new Buffer and copy data
            char[] newBuffer=    new char[ newCapacity ];
            if ( length > 0 )
            {
                // we might have been cut with this operation
                if ( length > newCapacity  )
                    length= newCapacity;
                System.arraycopy( buffer, 0, newBuffer, 0, length );
            }

            // that's it
            buffer=        newBuffer;
        }

        /** ****************************************************************************************
         * Ensures that the capacity of the internal buffer meets or exceeds the actual length
         * plus the given growth value.
         *
         * @param spaceNeeded  The desired growth of the length of the string represented by this.
         ******************************************************************************************/
        public void     ensureRemainingCapacity( int spaceNeeded )
        {
            int bufferLength= buffer.length;

            // big enough?
            if ( bufferLength >= length + spaceNeeded )
                return;

            // first allocation? Go with given growth as size
            if (bufferLength == 0 )
            {
                setBuffer( spaceNeeded > 16 ? spaceNeeded : 16 );
                return;
            }

            // calc new size: in general grow by 50%
            int newSize= bufferLength + (bufferLength / 2);
            if ( newSize < length + spaceNeeded )
                newSize+= spaceNeeded;

            if ( newSize < 16 )
                newSize= 16;

            setBuffer( newSize );
        }

        /** ****************************************************************************************
         *  Returns the current size of the internal buffer.
         *
         * @return The size of the allocated buffer.
         ******************************************************************************************/
        public    int         capacity()          { return buffer.length;    }

        /** ****************************************************************************************
         * Invokes \ref setBuffer "setBuffer(0)" or #setNull.
         ******************************************************************************************/
        public    void        setNull()           { setBuffer( 0 ); }

        /** ****************************************************************************************
         * Returns true if no buffer space is allocated, false otherwise.
         * This might be the case, if constructed  with <em>AString()</em> or <em>AString(0)</em>,
         * by invoking
         * \ref setBuffer "setBuffer(0)" or #setNull.
         *
         * @return true if no buffer is allocated.
         ******************************************************************************************/
        public    boolean     isNull()            { return buffer.length == 0; }

        /** ****************************************************************************************
         * Returns false if no buffer space is allocated, true otherwise.
         * This might be the case, if constructed  with <em>AString()</em> or <em>AString(0)</em>,
         * by invoking
         * \ref setBuffer "setBuffer(0)" or #setNull.
         *
         * @return true if no buffer is allocated.
         ******************************************************************************************/
        public    boolean     isNotNull()         { return buffer.length != 0; }

        /** ****************************************************************************************
         * Gets the length of the sequence.
         * @return  The length of the sequence.
         ******************************************************************************************/
        @Override
        public    int         length()            { return length;      }

        /** ****************************************************************************************
         *  Set the actual length of the stored string. Using this method, the string can only be
         *  shortened.
         *  To change the internal allocation size, see #setBuffer.
         *
         * @param newLength        The new length of the AString. Must be smaller than the current length.
         *
         * @return The new length of the string represented by this.
         ******************************************************************************************/
        public int  setLength( int newLength )
        {
            com.aworx.lib.ALIB_DBG.ASSERT_WARNING( newLength <= length, "Increase requested" );

            if ( newLength < length )
            {
                length= newLength;
                hash=    0;
            }
            return length;
        }

        /** ****************************************************************************************
         *  Set the actual length of the stored string. Using this method, the string can only be
         *  shortened.
         *  To change the internal allocation size, see #setBuffer.
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param newLength    The new length of the %AString. Must be between 0 and the current
         *                     length.
         ******************************************************************************************/
        public    void           setLength_NC( int newLength )
        {
            com.aworx.lib.ALIB_DBG.ASSERT_ERROR( newLength >= 0 && newLength <= length, "Index out of range" );
            length= newLength;
            hash=   0;
        }

        /** ****************************************************************************************
         *  Returns true if the actual length equals zero.
         * @return true if the actual length equals zero.
         ******************************************************************************************/
        public    boolean  isEmpty()                   { return length == 0; }

        /** ****************************************************************************************
         *  Returns true if the actual length does not equal zero.
         * @return true if the actual length does not equal zero.
         ******************************************************************************************/
        public    boolean  isNotEmpty()                { return length != 0; }




    /** ############################################################################################
     * @name Insert and Delete
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Clear the Buffer. Same as #delete (0, Length()) but without internal region checks.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString    clear()
        {
            hash= length= fieldReference= tabReference= 0;
            return this;
        }

        /** ****************************************************************************************
         * Clear the Buffer. Same as #clear(), really just a synonym to allow short code in
         * alignment with the various "Append" methods named <em>_(src)</em>
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString    _()
        {
            hash= length= fieldReference= tabReference= 0;
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
        public AString insertAt( CharSequence src, int pos )
        {
            if ( src != null )
            {
                int srcLength= src.length();
                if ( !resizeRegion( pos, 0, srcLength ) )
                    return this;

                for ( int i= 0 ; i < srcLength ; i++ )
                    buffer[pos + i]= src.charAt( i );
            }

            return this;
        }

        /** ****************************************************************************************
         * Inserts the given character n-times at a given position.
         * If the given position is out of range, nothing is inserted.
         *
         * @param c     The character to insert \p qty times.
         * @param qty   The quantity of characters to insert.
         * @param pos   The index in this object where \p c is inserted \p qty times.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString insertChars( char c, int qty, int pos )
        {
            if ( !resizeRegion( pos, 0, qty ) )
                return this;

            int regionEnd= pos + qty;
            for ( int i= pos ; i < regionEnd ; i++ )
                buffer[i]= c;

            return this;
        }

        /** ****************************************************************************************
         * Inserts the given character n-times at the end of this string (appends).
         *
         * @param c     The character to append.
         * @param qty   The quantity of characters to append.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString insertChars( char c, int qty )
        {
            if ( qty > 0 )
            {
                // flag us dirty (as we will be manipulated)
                hash= 0;

                // big enough?
                if ( buffer.length < length + qty )
                    ensureRemainingCapacity( qty );

                for ( int i= 0; i< qty; i++ )
                    buffer[length++]= c;
            }
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
        public AString  replaceSubstring( CharSequence src, int regionStart, int regionLength )
        {
            if (src != null )
            {
                int srcLength= src.length();
                if ( !resizeRegion( regionStart, regionLength, srcLength ) )
                    return this;

                for ( int i= 0 ; i < srcLength ; i++ )
                    buffer[regionStart + i]= src.charAt( i );
            }
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
        public AString replaceRegion( char c, int regionStart, int regionLength )
        {
            if ( !com.aworx.lib.strings.CString.adjustRegion( length, regionStart, regionLength, _adjustedRegion ) )
            {
                int regionEnd=  _adjustedRegion[0] + _adjustedRegion[1];
                for ( int i=    _adjustedRegion[0] ; i < regionEnd ; i++ )
                    buffer[i]= c;
            }

            return this;
        }

       /** ****************************************************************************************
         *  Cuts out a region from the Buffer.
         *  A range check is performed and the region is cut to fit to the string.
         * \note See also methods #clear, #deleteStart, #deleteStart_NC, #deleteEnd
         *       and #deleteEnd_NC.
         *
         * @param regionStart     The start of the region to delete.
         * @param regionLength    The length of the region to delete. Defaults to Integer.MAX_VALUE.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public    AString    delete( int regionStart, int regionLength )
        {
            // adjust range, if empty do nothing
            if ( com.aworx.lib.strings.CString.adjustRegion( length, regionStart, regionLength, _adjustedRegion ) )
                return this;

            if ( _adjustedRegion[1] <= 0 )
                return this;

            int regionEnd= _adjustedRegion[0] + _adjustedRegion[1];
            if ( regionEnd >= length )
            {
                length=    _adjustedRegion[0];
                return this;
            }

            System.arraycopy( buffer, regionEnd, buffer, _adjustedRegion[0], length - regionEnd );
            length-= _adjustedRegion[1];

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #delete(int,int) that provides the default value
         * Integer.MAX_VALUE as parameter \p regionLength.
         *
         * @param regionStart    The start of the region to delete.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public    AString delete( int regionStart )        { return delete( regionStart, Integer.MAX_VALUE );    }


        /** ****************************************************************************************
         *  Cuts out a region from the Buffer.
         *  \note See also methods #clear, #deleteStart, #deleteStart_NC, #deleteEnd
         *        and #deleteEnd_NC.
         *
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *             Like with method #delete(int, int), it is allowed that the sum of parameters
         *             \p regionStart and \p regionLength is longer than the length of this \b %AString.
         *             In this case, this string is cut starting from index \p regionStart.
         *
         * @param regionStart  The start of the region to delete.
         * @param regionLength The length of the region to delete.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public    AString     delete_NC( int regionStart, int regionLength )
        {
            com.aworx.lib.ALIB_DBG.ASSERT_ERROR(     regionStart  >= 0
                                    &&  regionStart  <= length
                                    &&  regionLength >= 0,
                                    "Parameter assertion" );

            int regionEnd= regionStart + regionLength;
            if ( regionEnd >= length )
            {
                length=    regionStart;
                return this;
            }

            System.arraycopy( buffer, regionEnd, buffer, regionStart, length - regionEnd );
            length-= regionLength;

            return this;
        }


        /** ****************************************************************************************
         *  Deletes the given number of characters from the start of the string.
         *  The given region length is checked to be between 0 and length.
         *
         * @param regionLength  The length of the region at the start to delete.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString    deleteStart( int regionLength  )
        {
            if ( regionLength <= 0 )
                return this;
            if ( regionLength >= length )
                return clear();

            return deleteStart_NC( regionLength );
        }

        /** ****************************************************************************************
         *  Deletes the given number of characters from the start of the string.
         *  Does not check and correct the parameters.
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         * @param regionLength  The length of the region at the start to delete.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString     deleteStart_NC( int regionLength  )
        {
            com.aworx.lib.ALIB_DBG.ASSERT_ERROR(  regionLength >=0 && regionLength <= length, "Region length out of range" );
            System.arraycopy( buffer, regionLength, buffer, 0, length - regionLength );
            length-= regionLength;
            return this;
        }

        /** ****************************************************************************************
         *  Deletes the given number of characters from the end of the string.
         *  The given region length is checked to be between 0 and length.
         *
         * @param regionLength  The length of the region at the end to delete.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString    deleteEnd( int regionLength  )
        {
            if ( regionLength <= 0 )
                return this;
            if ( regionLength >= length )
                return clear();

            length-= regionLength;
            return this;
        }

        /** ****************************************************************************************
         *  Deletes the given number of characters from the end of the string.
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param regionLength  The length of the region at the end to delete.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString       deleteEnd_NC( int regionLength  )
        {
            com.aworx.lib.ALIB_DBG.ASSERT_ERROR(  regionLength >=0 && regionLength <= length, "Region length out of range" );
            length-= regionLength;
            return this;
        }

        /** ****************************************************************************************
         * All characters defined in given set are removed at the beginning and at the end of this
         * AString.
         *
         * See method \ref #trimAt to remove whitespaces anywhere in the string.
         *
         * @param trimChars   The set of characters to be omitted.
         *                    Defaults to null which causes this method to use
         *                    \ref CString.DEFAULT_WHITESPACES.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString trim( char[] trimChars )
        {
            if (length == 0 )
                return this;

            if ( trimChars == null )
                trimChars= com.aworx.lib.strings.CString.DEFAULT_WHITESPACES;

            length=  com.aworx.lib.strings.CString.lastIndexOfAny( buffer, 0, length, trimChars, Inclusion.EXCLUDE ) + 1;
            int idx= com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, 0, length, trimChars, Inclusion.EXCLUDE );
            if ( idx > 0 )
                delete_NC( 0, idx );
            return this;
        }

        /** ****************************************************************************************
         * All characters in \ref CString.DEFAULT_WHITESPACES are removed
         * at the beginning and at the end of this AString.
         * See method \ref #trimAt to remove whitespaces anywhere in the string.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString trim()
        {
            return trim( com.aworx.lib.strings.CString.DEFAULT_WHITESPACES );
        }

        /** ****************************************************************************************
         * All characters defined in given set at, left of and right of the given index
         * are removed from the string.<br>
         * The method returns index of the first character of those characters that were behind the
         * trimmed region. With legal \p index given, this value can only be smaller or equal to
         * \p index. If \p index is out of bounds, the length of the string is returned.
         *
         * @param idx         The index to perform the trim operation at. Has to be between zero
         *                    and <em>Length() -1</em>.
         * @param trimChars   Pointer to a zero terminated set of characters to be omitted.
         *                    Defaults to \ref CString.DEFAULT_WHITESPACES.
         * @return  The index of the first character of those characters that were behind the
         *          trimmed region.
         ******************************************************************************************/
        public int  trimAt( int idx, char[] trimChars )
        {
            if ( idx < 0 )
                 return 0;
            if ( idx >= length )
                 return length;


            if ( trimChars == null )
                trimChars= com.aworx.lib.strings.CString.DEFAULT_WHITESPACES;

            int regionStart= com.aworx.lib.strings.CString.lastIndexOfAny( buffer, 0,     idx + 1,      trimChars, Inclusion.EXCLUDE ) + 1;
            if (regionStart < 0 )
                regionStart= 0;
            int regionEnd=   com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, idx, length - idx, trimChars, Inclusion.EXCLUDE );
            if (regionEnd < 0 )
                regionEnd= length;

            int regionLength= regionEnd - regionStart;
            if ( regionLength > 0 )
                delete_NC( regionStart, regionLength );
            return regionStart;
        }

        /** ****************************************************************************************
         * Overloaded method providing default \ref CString.DEFAULT_WHITESPACES value for
         * parameter \p trimChars.
         *
         * @param index       The index to perform the trim operation at. Has to be between zero
         *                    and <em>Length() -1</em>.
         * @return  The index of the first character of those characters that were behind the
         *          trimmed region.
         ******************************************************************************************/
        public int  trimAt( int index )
        {
            return trimAt( index, com.aworx.lib.strings.CString.DEFAULT_WHITESPACES );
        }

        /** ****************************************************************************************
         * All characters defined in given set are removed at the beginning of this string.
         *
         * \see Method #trimAt to remove whitespaces at arbitrary places in the string.
         *
         * @param trimChars   The set of characters to be omitted.
         *                    Defaults to \ref CString.DEFAULT_WHITESPACES.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString trimStart( char[] trimChars )
        {
            if ( trimChars == null )
                trimChars= com.aworx.lib.strings.CString.DEFAULT_WHITESPACES;
            if (length == 0 || trimChars.length == 0 )
                return this;

            int idx= indexOfAny( trimChars, Inclusion.EXCLUDE);
            if ( idx > 0 )
                delete( 0, idx );
            else if ( idx < 0 )
                length= 0;

            return this;
        }

        /** ****************************************************************************************
         * All characters in \ref CString.DEFAULT_WHITESPACES at the beginning of this string are
         * removed.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString trimStart()
        {
            trimAt( 0, com.aworx.lib.strings.CString.DEFAULT_WHITESPACES );
            return this;
        }

        /** ****************************************************************************************
         * All characters defined in given set are removed at the end of  this string.
         *
         * \see Method #trimAt to remove whitespaces at arbitrary places in the string.
         *
         * @param trimChars   The set of characters to be omitted.
         *                    Defaults to \ref CString.DEFAULT_WHITESPACES.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString trimEnd( char[] trimChars )
        {
           if( length > 0 &&  trimChars.length > 0 )
                length= lastIndexOfAny( trimChars, Inclusion.EXCLUDE, length - 1 ) + 1;

            return this;
        }

        /** ****************************************************************************************
         * All characters in \ref CString.DEFAULT_WHITESPACES at the end of this string are
         * removed.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString trimEnd()
        {
            trimAt( length - 1, com.aworx.lib.strings.CString.DEFAULT_WHITESPACES );
            return this;
        }



    /** ############################################################################################
     * @name Basic formatting
     ##@{ ########################################################################################*/
        /** ****************************************************************************************
         * Appends platform specific new line character(s). ( "\\r\\n", "\\r", etc.). The new length of the
         * string is recorded as the reference position for #tab.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString newLine()
        {
            // save tab reference and append new line characters
            tabReference= length + com.aworx.lib.strings.CString.NEW_LINE_CHARS.length();
            return _( com.aworx.lib.strings.CString.NEW_LINE_CHARS );
        }

        /** ****************************************************************************************
         * Go to the next tab stop by filling in pad characters repeatedly. The tab position is
         * relative the start of the current line within the string (if no calls to #newLine
         * where performed, yet, this is always the start of the string).
         *
         * \note While any append operation is allowed, manipulations like
         *       #delete or #insertAt will not correct the internal tab reference position to match
         *       the index of the then current start of the last line in this string.
         *
         * @param tabSize       The tab positions are multiples of this parameter.
         * @param minPad        (Optional) The minimum pad characters to add. Defaults to 1.
         * @param tabChar       (Optional) The character to insert to reach the that position.
         *                      Defaults to ' ' (space).
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString tab( int tabSize, int minPad, char tabChar)
        {
            int qtyChars= minPad > 0 ? minPad : 0;
            if ( tabSize > 1 )
                qtyChars+= (tabSize - ( (length + qtyChars - tabReference) % tabSize ) ) % tabSize;

            return ( qtyChars <= 0 ) ?  this
                                     :  insertChars( tabChar, qtyChars );
        }

        /** ****************************************************************************************
         * Overloaded method of #tab(int, int, char), providing ' ' (space) as default value
         * for parameter \p tabChar.
         *
         * @param tabSize       The tab positions are multiples of this parameter.
         * @param minPad        The minimum pad characters to add. Defaults to 1.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString tab( int tabSize, int minPad)   { return tab( tabSize, minPad, ' ' ); }


        /** ****************************************************************************************
         * Overloaded method of #tab(int, int, char), providing ' ' (space) as default value
         * for parameter \p tabChar and 1 as default value for parameter \p minPad.
         *
         * @param tabSize   The tab positions are multiples of this parameter.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString tab( int tabSize )              { return tab( tabSize,      1, ' ' ); }

        /** ****************************************************************************************
         * If invoked without parameters, the start of a field is marked at the current end of
         * the string. Otherwise the end of a field is set and the contents between the field start
         * marker and the current end of the string is aligned within the field using the given
         * pad character.
         * \note To implement nested fields, the outer fields have to be set by providing the
         * start marker by using the parameter fieldStart. Hence, only the starting points of
         * the most inner fields can be set using this method without parameters.
         *
         * @param size          The field size in relation to the starting index of the field, defined either by
         *                      using Field() prior to this invocation or by providing the parameter fieldStart.
         *                      The field gets filled with the given pad character to meet the size
         *                      while the content gets aligned left, right or centered.
         *                      If the content exceeds the size, then no alignment takes place.
         * @param alignment     The alignment of the contents within the field. Defaults to ALIB.Align.RIGHT.
         *                      Other options are ALIB.Align.LEFT and ALIB.Align.CENTER.
         * @param padChar       The character used to fill the field up to its size.
         *                      Defaults to ' ' (space).
         * @param fieldStart    This parameter, if given, overwrites the start index of the field.
         *                      The invocation of #field can be omitted, when this value is explicitly
         *                      provided.
         *                      Defaults to Integer.MAX_VALUE.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString field( int size, Alignment alignment, char padChar, int fieldStart )
        {
            // if size is -1, this is just a field start marker invocation
            if ( size < 0 )
            {
                fieldReference= length;
                return this;
            }

            // if no field start is given, use the saved one (default behavior)
            if ( fieldStart == Integer.MAX_VALUE )
                fieldStart=        fieldReference;

            // check pad size
            int padSize=    size - (length - fieldStart);
            if (padSize <= 0 )
                return this;

            // align left
            if ( alignment == Alignment.LEFT )
            {
                insertChars( padChar, padSize );
                return this;
            }

            // align Right
            if ( alignment == Alignment.RIGHT )
            {
                insertChars( padChar, padSize, fieldStart );
                return this;
            }

            // align Center
            insertChars( padChar, padSize >> 1, fieldStart );
            insertChars( padChar, padSize - ( padSize >> 1 ) );
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
         * @param alignment     The alignment of the contents within the field. Defaults to ALIB.Align.RIGHT.
         *                      Other options are ALIB.Align.LEFT and ALIB.Align.CENTER.
         * @param padChar       The character used to fill the field up to its size.
         *                      Defaults to ' ' (space).
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString field( int size, Alignment alignment, char padChar  )
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
         * @param alignment     The alignment of the contents within the field. Defaults to ALIB.Align.RIGHT.
         *                      Other options are ALIB.Align.LEFT and ALIB.Align.CENTER.
         * @return  \c this to allow concatenated calls.
         *************************************************************************************************/
        public AString field( int size, Alignment alignment )
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
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString field( int size )
        {
            return field( size, Alignment.RIGHT, ' ', Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Marks the start of a field.
         * See variants of this method for more information.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString field()
        {
            return field( -1, Alignment.RIGHT, ' ', Integer.MAX_VALUE );
        }


    /** ############################################################################################
     * @name Appending characters and strings
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Append a region of a char[].
         *
         * @param src            The character containing the region to append.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         * @param regionLength   The maximum length of the region in src to append. Defaults to
         *                       the length of the array minus the start of the region.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( char[] src, int regionStart, int regionLength )
        {
            // check null argument
            if ( src == null )
                return this;

            // zero length argument
            int srcLength= src.length;
            if ( srcLength == 0 )
            {
                // special treatment if currently nothing is allocated and a blank string ("") is added:
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.length == 0 )
                    setBuffer( 16 );
                return this;
            }

            // adjust range, if empty do nothing
            if ( com.aworx.lib.strings.CString.adjustRegion( srcLength, regionStart, regionLength, _adjustedRegion ) )
                return this;

            regionStart=    _adjustedRegion[0];
            regionLength=    _adjustedRegion[1];

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.length < length + regionLength )
                ensureRemainingCapacity( regionLength );

            // copy
            System.arraycopy( src, regionStart, buffer, length, regionLength );

            // return me for concatenated operations
            length+= regionLength;
            return this;
        }

        /** ****************************************************************************************
         * Append char[] beginning with given index.
         *
         * @param src            The character array containing the region to append.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( char[] src, int regionStart )
        {
            return _( src, regionStart, src.length - regionStart );
        }

        /** ****************************************************************************************
         * Append a char[].
         * @param src            The character array to append.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( char[] src )
        {
            // check null argument
            if ( src == null )
                return this;

            // zero length argument
            int srcLength= src.length;
            if ( srcLength == 0 )
            {
                // special treatment if currently nothing is allocated and a blank string ("") is added:
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.length == 0 )
                    setBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.length < length + srcLength )
                ensureRemainingCapacity( srcLength );

            // copy
            System.arraycopy( src, 0, buffer, length, srcLength );

            // return me for concatenated operations
            length+= srcLength;
            return this;
        }

        /** ****************************************************************************************
         * Append a region of a char[].
         * \attention Non checking variant of original method.
         *            See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         * @param src            The character containing the region to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The maximum length of the region in src to append.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( char[] src, int regionStart, int regionLength )
        {
            // big enough?
            if ( buffer.length < length + regionLength )
                ensureRemainingCapacity( regionLength );

            // copy
            System.arraycopy( src, regionStart, buffer, length, regionLength );

            // return me for concatenated operations
            length+= regionLength;
            return this;
        }

        /** ****************************************************************************************
         * Append a region of a CharSequence.
         *
         * @param src            The CharSequence containing the region to append.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to Integer.MAX_VALUE.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( CharSequence src, int regionStart, int regionLength )
        {
            // check null argument
            if ( src == null )
                return this;

            // adjust range, if empty do nothing
            if ( com.aworx.lib.strings.CString.adjustRegion( src.length(), regionStart, regionLength, _adjustedRegion ) )
            {
                // special treatment if currently nothing is allocated and a blank string ("") is added:
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.length == 0 )
                    setBuffer( 16 );
                return this;
            }

            regionStart=    _adjustedRegion[0];
            regionLength=    _adjustedRegion[1];

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.length < length + regionLength )
                ensureRemainingCapacity( regionLength );

            // use different built in techniques
                 if ( src instanceof String )           { ((String)        src).getChars( regionStart, regionStart + regionLength, buffer, length );    }
            else if ( src instanceof AString )          { System.arraycopy( ((AString)   src).buffer, regionStart,                           buffer, length, regionLength ); }
            else if ( src instanceof com.aworx.lib.strings.Substring)        { System.arraycopy( ((com.aworx.lib.strings.Substring) src).buf,    ((com.aworx.lib.strings.Substring) src).start + regionStart, buffer, length, regionLength ); }
            else if ( src instanceof StringBuffer )     { ((StringBuffer)  src).getChars( regionStart, regionStart + regionLength, buffer, length );    }
            else if ( src instanceof StringBuilder )    { ((StringBuilder) src).getChars( regionStart, regionStart + regionLength, buffer, length );    }

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
         * Append a region of a CharSequence.
         *
         * @param src            The CharSequence to append.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( CharSequence src, int regionStart )
        {
            return _( src, regionStart, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Append a CharSequence.
         *
         * @param src    The CharSequence to append.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( CharSequence src )
        {
            // check null argument
            if ( src == null )
                return this;

            // zero length argument
            int srcLength= src.length();
            if ( srcLength == 0 )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.length == 0 )
                    setBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.length < length + srcLength )
                ensureRemainingCapacity( srcLength );

            // use different built in techniques
                 if ( src instanceof AString )               {  System.arraycopy( ((AString)   src).buffer, 0,                       buffer,  length, srcLength ); }
            else if ( src instanceof com.aworx.lib.strings.Substring)             {  System.arraycopy( ((com.aworx.lib.strings.Substring) src).buf,    ((com.aworx.lib.strings.Substring) src).start, buffer,  length, srcLength ); }
            else if ( src instanceof StringBuffer )          {  ((StringBuffer)  src).getChars( 0, srcLength, buffer, length );            }
            else if ( src instanceof StringBuilder )         {  ((StringBuilder) src).getChars( 0, srcLength, buffer, length );            }
            else // finally CharSequence: do it manually
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
         * Append an %AString.
         *
         * @param src   The %AString to append.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( AString src )
        {
            // check null argument
            if ( src == null )
                return this;

            // zero length argument
            int srcLength= src.length;
            if ( srcLength == 0 )
            {
                // special treatment if currently nothing is allocated and a blank string ("") is added:
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.length == 0 )
                    setBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.length < length + srcLength )
                ensureRemainingCapacity( srcLength );

            // copy
            System.arraycopy( src.buffer, 0, buffer, length, srcLength );

            // return me for concatenated operations
            length+= srcLength;
            return this;
        }


        /** ****************************************************************************************
         * Append an AString.
         * \attention Non checking variant of original method.
         *            See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *
         * @param src            The source AString.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( AString src )
        {
            return _NC( src.buffer, 0, src.length );
        }

        /** ****************************************************************************************
         * Append a region of an AString.
         * \attention Non checking variant of original method.
         *            See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *
         * @param src            The source AString.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The length of the region in src to append.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( AString src, int regionStart, int regionLength )
        {
            return _NC( src.buffer, regionStart, regionLength );
        }


        /** ****************************************************************************************
         * Append a Substring.
         *
         * @param src   The source Substring.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( com.aworx.lib.strings.Substring src )
        {
            // check null argument
            if ( src == null )
                return this;

            return _( src.buf, src.start, src.length() );
        }


        /** ****************************************************************************************
         * Append a Substring.
         * \attention Non checking variant of original method.
         *            See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *
         * @param src   The source Substring.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( com.aworx.lib.strings.Substring src )
        {
            return _NC( src.buf, src.start, src.length() );
        }


        /** ****************************************************************************************
         * Append a String.
         * \note For performance reasons, we overwrite #_(CharSequence) here.
         *
         * @param src   The CharSequence to append.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( String src )
        {
            // check null argument
            if ( src == null )
                return this;

            // zero length argument
            int srcLength= src.length();
            if ( srcLength == 0 )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.length == 0 )
                    setBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.length < length + srcLength )
                ensureRemainingCapacity( srcLength );

            // use built in string copy
            src.getChars( 0, srcLength, buffer, length );

            // return me for concatenated operations
            length+= srcLength;
            return this;
        }

        /** ****************************************************************************************
         *  Append a String.
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         * @param src  The string containing the region to append.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( String src )
        {
            // big enough?
            int regionLength= src.length();
            if ( buffer.length < length + regionLength )
                ensureRemainingCapacity( regionLength );

            // copy
            src.getChars( 0, regionLength, buffer, length );

            // return me for concatenated operations
            length+= regionLength;
            return this;
        }

        /** ****************************************************************************************
         *  Append a region of a String.
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.         *
         * @param src            The string containing the region to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The length of the region in src to append.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( String src, int regionStart, int regionLength )
        {
            // big enough?
            if ( buffer.length < length + regionLength )
                ensureRemainingCapacity( regionLength );

            // copy
            src.getChars( regionStart, regionStart + regionLength, buffer, length );

            // return me for concatenated operations
            length+= regionLength;
            return this;
        }

        /** ****************************************************************************************
         * Append a character.
         *
         * @param c The character to append.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( char c )
        {
            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.length < length + 1 )
                ensureRemainingCapacity( 1 );

            // set
            buffer[ length++ ]= c;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Appends an object by invoking \c toString on it.
         *
         * @param object The object whose string representation is to be appended.
         *
         * @return    \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( Object object )
        {
            return  object == null                 ? this :
                    object instanceof CharSequence ? _( (CharSequence) object)
                                                   : _(  object.toString()   );
        }

        /** ****************************************************************************************
         * Appends an object by invoking \c toString on it.
         *
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param object The object whose string representation is to be appended.
         *
         * @return    \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( Object object )
        {
            return _NC( object.toString() );
        }


    /** ############################################################################################
     * @name Character access
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Retrieves the character at the given index.
         * A range check is performed. If this fails, '\0' is returned.
         *
         * @param idx  The index of the character to read.
         * @return The character at the given index, or '\0' if index out of range.
         ******************************************************************************************/
        @Override
        public char        charAt( int idx )
        {
            return  ( idx >= 0 && idx < length ) ? buffer[idx]
                                                 : '\0';
        }

        /** ****************************************************************************************
         * Retrieves the character at the given index.
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param idx  The index of the character to read.
         * @return The character at the given index.
         ******************************************************************************************/
        public char        charAt_NC( int idx )
        {
            com.aworx.lib.ALIB_DBG.ASSERT_ERROR(  idx >= 0 && idx < length, "Index out of range" );
            return  buffer[idx];
        }

        /** ****************************************************************************************
         * Sets the character at the given index.
         * A range check is performed. If this fails, nothing is done.
         * \note Access to the characters without index check is provided with method #charAt_NC.
         *
         * @param idx  The index of the character to write.
         * @param c    The character to write.
         ******************************************************************************************/
        public void        setCharAt( int idx, char c )
        {
            if  ( idx >= 0 && idx < length )
                buffer[idx]= c;
        }

        /** ****************************************************************************************
         * Sets the character at the given index.
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param idx  The index of the character to write.
         * @param c    The character to write.
         ******************************************************************************************/
        public void        setCharAt_NC( int idx, char c )
        {
            com.aworx.lib.ALIB_DBG.ASSERT_ERROR(  idx >= 0 && idx < length, "Index out of range" );
            buffer[idx]= c;
        }

        /** ****************************************************************************************
         * Retrieve the first character.
         * In case of an empty string, '\0' is returned.
         * @return The first character in the AString.
         *         If this instance's length is zero,  '\0' is returned.
         ******************************************************************************************/
        public char        charAtStart()
        {
            return length > 0 ?  buffer[0]
                              :  '\0';
        }

        /** ****************************************************************************************
         * Retrieve the first character.
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         * @return The first character in the AString.
         *         If this instance's length is zero,  '\0' is returned.
         ******************************************************************************************/
        public char        charAtStart_NC()
        {
            com.aworx.lib.ALIB_DBG.ASSERT_ERROR(  length > 0, "Empty AString" );
            return  buffer[0];
        }

        /** ****************************************************************************************
         * Retrieve the last character.
         * In case of an empty string, '\0' is returned.
         * @return The last character in the AString.
         *         If this instance's length is zero,  '\0' is returned.
         ******************************************************************************************/
        public char        charAtEnd()
        {
            return length > 0 ?  buffer[length - 1]
                              :  '\0';
        }

        /** ****************************************************************************************
         * Retrieve the last character.
         *  \attention Non checking variant of original method.
         *             See \ref JAVA_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         * @return The first character in the AString.
         *         If this instance's length is zero,  '\0' is returned.
         ******************************************************************************************/
        public char        charAtEnd_NC()
        {
            com.aworx.lib.ALIB_DBG.ASSERT_ERROR(  length > 0, "Empty AString" );
            return  buffer[length - 1];
        }


    /** ############################################################################################
     * @name Comparison
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Compares a given region of a string with a region of this instance.
         * Regions that are out of bounds get adjusted and then compared.
         *
         * @param cmpString       An object of type String, StringBuffer or AString that is
         *                        compared to this.
         * @param sensitivity     Case sensitivity of the operation.
         *                        Optional and defaults to Case.Sensitive.
         * @param cmpRegionStart  The start of the substring within the given string that is to
         *                        be compared to this. Defaults to 0.
         * @param cmpRegionLength The length of the substring within the given string that is to be
         *                        compared to this. Defaults to Integer.MAX_VALUE.
         * @param regionStart     The start of the substring within this string that is to
         *                        be compared. Defaults to 0.
         * @param regionLength    The length of the substring within this string that is to
         *                        be compared. Defaults to Integer.MAX_VALUE.
         *
         * @return 0 if the contents of the string regions are equal (or if both regions are empty
         *           or out of range).<br>
         *         -1 if the instance is less than the given string.<br>
         *         +1 if the instance is greater than the given string or if given string is null.
         ******************************************************************************************/
        public int compareTo( CharSequence cmpString, Case sensitivity,
                              int cmpRegionStart, int cmpRegionLength,
                              int regionStart,    int regionLength )
        {
            // check null argument
            if ( buffer.length == 0   )     return  cmpString == null ? 0 : -1;
            if ( cmpString == null )
                return 1;

            // adjust source and compare regions
            com.aworx.lib.strings.CString.adjustRegion( cmpString.length(), cmpRegionStart, cmpRegionLength, _adjustedRegion );
            cmpRegionStart=   _adjustedRegion[0];
            cmpRegionLength=  _adjustedRegion[1];

            com.aworx.lib.strings.CString.adjustRegion( length, regionStart, regionLength, _adjustedRegion );
            regionStart=      _adjustedRegion[0];
            regionLength=     _adjustedRegion[1];

            return com.aworx.lib.strings.CString.compareTo( cmpString,  cmpRegionStart, cmpRegionLength,
                                      buffer,        regionStart,    regionLength,
                                      sensitivity );
        }

        /** ****************************************************************************************
         * Compares a given region of a string with a region of this instance.
         * Regions that are out of bounds get adjusted and then compared.
         *
         * @param cmpString       An object of type String, StringBuffer or AString that is
         *                        compared to this.
         * @param sensitivity     Case sensitivity of the operation.
         *                        Optional and defaults to Case.Sensitive.
         * @param cmpRegionStart  The start of the substring within the given string that is to
         *                        be compared to this. Defaults to 0.
         * @param cmpRegionLength The length of the substring within the given string that is to be
         *                        compared to this. Defaults to Integer.MAX_VALUE.
         * @param regionStart     The start of the substring within this string that is to
         *                        be compared. Defaults to 0.
         *
         * @return 0 if the contents of the string regions are equal (or if both regions are empty
         *           or out of range).<br>
         *         -1 if the instance is less than the given string.<br>
         *         +1 if the instance is greater than the given string or if given string is null.
         ******************************************************************************************/
        public int compareTo( CharSequence cmpString, Case sensitivity,
                              int cmpRegionStart, int cmpRegionLength,
                              int regionStart )
        {
            return compareTo( cmpString, sensitivity,
                              cmpRegionStart, cmpRegionLength,
                              regionStart, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Compares a given region of a string with this instance. If the given region is out
         * of bounds in respect to the given string, it get adjusted and then compared.
         *
         * @param cmpString       An object of type String, StringBuffer or AString that is
         *                        compared to this.
         * @param sensitivity     Case sensitivity of the operation.
         *                        Optional and defaults to Case.Sensitive.
         * @param cmpRegionStart  The start of the substring within the given string that is to
         *                        be compared to this. Defaults to 0.
         * @param cmpRegionLength The length of the substring within the given string that is to be
         *                        compared to this. Defaults to Integer.MAX_VALUE.
         *
         * @return 0 if the contents of this string and the region of the given string are equal
         *           (or if this object and the given region are empty).<br>
         *         -1 if the instance is less than the given string.<br>
         *         +1 if the instance is greater than the given string or if given string is null.
         ******************************************************************************************/
        public int compareTo( CharSequence cmpString, Case sensitivity,
                              int cmpRegionStart, int cmpRegionLength )
        {
            return compareTo( cmpString, sensitivity,
                              cmpRegionStart, cmpRegionLength,
                              0, Integer.MAX_VALUE );
        }


        /** ****************************************************************************************
         * Compares a given region of a string with this instance. If the given region start
         * is out of bounds in respect to the given string, it gets adjusted and then compared.
         *
         * @param cmpString       An object of type String, StringBuffer or AString that is
         *                        compared to this.
         * @param sensitivity     Case sensitivity of the operation.
         *                        Optional and defaults to Case.Sensitive.
         * @param cmpRegionStart  The start of the substring within the given string that is to
         *                        be compared to this. Defaults to 0.
         *
         * @return 0 if the contents of the string regions are equal (or if both regions are empty
         *           or out of range).<br>
         *         -1 if the instance is less than the given string.<br>
         *         +1 if the instance is greater than the given string or if given string is null.
         ******************************************************************************************/
        public int compareTo( CharSequence cmpString, Case sensitivity, int cmpRegionStart )
        {
            return compareTo( cmpString, sensitivity, cmpRegionStart,
                              Integer.MAX_VALUE, 0, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Compares a given string with this instance.
         *
         * @param cmpString   An object of type String, StringBuffer or AString that is compared to
         *                    this.
         * @param sensitivity Case sensitivity of the operation.
         *                    Optional and defaults to Case.Sensitive.
         *
         * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
         *         follows the given string (same as String.CompareTo), or if given string in null.
         ******************************************************************************************/
        public int compareTo( CharSequence cmpString, Case sensitivity )
        {
            return compareTo( cmpString, sensitivity, 0, Integer.MAX_VALUE, 0, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Compares a given string with this instance.
         *
         * @param cmpString  An object of type String, StringBuffer or AString that is compared
         *                   to this.
         *
         * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
         *         follows the given string (same as String.CompareTo), or if given string in null.
         ******************************************************************************************/
        public int compareTo( CharSequence cmpString )
        {
            return compareTo( cmpString, Case.SENSITIVE, 0, Integer.MAX_VALUE, 0,Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Checks if a CharSequence is located at the given position.
         *
         * @param needle        The CharSequence to search.
         * @param pos           The position within this object to look at.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  True if the sequence is found at the given position. False otherwise .
         ******************************************************************************************/
        public boolean containsAt( CharSequence needle, int pos, Case sensitivity )
        {
            return com.aworx.lib.strings.CString.containsAt( needle, buffer, pos, length, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if a CharSequence is located at the given position.
         *
         * @param needle        The CharSequence to search.
         * @param pos           The position within this object to look at.
         *
         * @return  True if the sequence is found at the given position. False otherwise .
         ******************************************************************************************/
        public boolean containsAt( CharSequence needle, int pos )
        {
            return com.aworx.lib.strings.CString.containsAt( needle, buffer, pos, length, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Checks if an AString is located at the given position.
         *
         * @param needle        The AString to search.
         * @param pos           The position within this object to look at.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  True if the sequence is found at the given position. False otherwise .
         ******************************************************************************************/
        public boolean containsAt( AString needle, int pos, Case sensitivity )
        {
            return com.aworx.lib.strings.CString.containsAt( needle != null ? needle.buffer() : null, 0,
                                       needle != null ? needle.length() : 0,
                                       buffer,          pos, length,
                                       sensitivity                             );
        }

        /** ****************************************************************************************
         * Checks if a String is located at the given position.
         *
         * @param needle        The CharSequence to search.
         * @param pos           The position within this object to look at.
         *
         * @return  True if given sequence is found at the given position. False otherwise .
         ******************************************************************************************/
        public boolean containsAt( AString needle, int pos )
        {
            return com.aworx.lib.strings.CString.containsAt( needle != null ? needle.buffer() : null, 0,
                                       needle != null ? needle.length() : 0,
                                       buffer, pos, length, Case.SENSITIVE     );
        }

        /** ****************************************************************************************
         * Checks if a Substring is located at the given position.
         *
         * @param needle        The Substring to search.
         * @param pos           The position within this object to look at.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  True if the sequence is found at the given position. False otherwise .
         ******************************************************************************************/
        public boolean containsAt(com.aworx.lib.strings.Substring needle, int pos, Case sensitivity )
        {
            return needle != null ? com.aworx.lib.strings.CString.containsAt( needle.buf,    needle.start,   needle.length(),
                                                        buffer,        pos, length,
                                                        sensitivity     )
                                  : com.aworx.lib.strings.CString.containsAt( null, 0, 0,
                                                        buffer,        pos, length,
                                                        sensitivity     );
        }

        /** ****************************************************************************************
         * Checks if a Substring is located at the given position.
         *
         * @param needle        The CharSequence to search.
         * @param pos           The position within this object to look at.
         *
         * @return  True if the sequence is found at the given position. False otherwise .
         ******************************************************************************************/
        public boolean containsAt(com.aworx.lib.strings.Substring needle, int pos )
        {
            return needle != null ? com.aworx.lib.strings.CString.containsAt( needle.buf, needle.start,  needle.length(),
                                                        buffer,     pos,           length,
                                                        Case.SENSITIVE     )
                                  : com.aworx.lib.strings.CString.containsAt( null, 0, 0,
                                                        buffer, pos, length,
                                                        Case.SENSITIVE     );
        }


        /** ****************************************************************************************
         * Checks if this AString starts with the given sequence.
         *
         * @param needle        The CharSequence to search. If s is null or empty, false is returned.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( CharSequence needle, Case sensitivity )
        {
            return com.aworx.lib.strings.CString.containsAt( needle, buffer, 0, length, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if this AString starts with the given sequence.
         *
         * @param needle        The CharSequence to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( CharSequence needle )
        {
            return com.aworx.lib.strings.CString.containsAt( needle, buffer, 0, length, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Checks if this AString starts with the given sequence.
         *
         * @param needle        The AString to search. If s is null or empty, false is returned.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( AString needle, Case sensitivity )
        {
            return containsAt( needle, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if this AString starts with the given sequence.
         *
         * @param needle        The AString to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( AString needle )
        {
            return containsAt( needle, 0, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Checks if this AString starts with the given sequence.
         *
         * @param needle        The Substring to search. If s is null or empty, false is returned.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith(com.aworx.lib.strings.Substring needle, Case sensitivity )
        {
            return containsAt( needle, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if this AString starts with the given sequence.
         *
         * @param needle        The Substring to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( com.aworx.lib.strings.Substring needle )
        {
            return containsAt( needle, 0, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Checks if this AString ends with the given sequence.
         *
         * @param needle        The CharSequence to search. If s is null or empty, false is returned.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean endsWith  ( CharSequence needle, Case sensitivity )
        {
            if ( needle == null )
                return true;
            return com.aworx.lib.strings.CString.containsAt( needle,
                                       buffer,       length - needle.length(),   length,
                                       sensitivity     );
        }

        /** ****************************************************************************************
         * Checks if this AString ends with the given sequence.
         *
         * @param needle        The CharSequence to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean endsWith  ( CharSequence needle )
        {
            return endsWith( needle, Case.SENSITIVE);
        }

        /** ****************************************************************************************
         * Checks if this AString ends with the given sequence.
         *
         * @param needle        The AString to search. If s is null or empty, false is returned.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean endsWith  ( AString needle, Case sensitivity )
        {
            if ( needle == null )
                return true;
            return com.aworx.lib.strings.CString.containsAt( needle.buffer(), 0,   needle.length(),
                                       buffer,          length - needle.length(),   length,
                                       sensitivity     );
        }

        /** ****************************************************************************************
         * Checks if this AString ends with the given sequence.
         *
         * @param needle        The AString to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean endsWith  ( AString needle )
        {
            return endsWith( needle, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Checks if this AString ends with the given sequence.
         *
         * @param needle        The Substring to search. If s is null or empty, false is returned.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean endsWith  (com.aworx.lib.strings.Substring needle, Case sensitivity )
        {
            if ( needle == null )
                return true;
            return com.aworx.lib.strings.CString.containsAt( needle.buf,      needle.start,   needle.length(),
                                       buffer,          length - needle.length(),   length,
                                       sensitivity     );
        }

        /** ****************************************************************************************
         * Checks if this AString ends with the given sequence.
         *
         * @param needle        The Substring to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean endsWith  ( com.aworx.lib.strings.Substring needle )
        {
            return endsWith( needle, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Compares this to the given object. Given object can be of type
         * - %AString
         * - \ref com.aworx.lib.strings.Substring "Substring"
         * - String or
         * - CharSequence
         *
         * @param object        The object to compare to this instance.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  True if given object equals this.
         ******************************************************************************************/
        public boolean equals( Object object, Case sensitivity )
        {
            // null?
            if ( object == null)
                return isNull();

            // compare with known types
            if ( object instanceof AString )        return equals( ((AString)       object ), sensitivity );
            if ( object instanceof com.aworx.lib.strings.Substring)      return equals( ((com.aworx.lib.strings.Substring)     object ), sensitivity );
            if ( object instanceof String )         return equals( ((String)        object ), sensitivity );
            if ( object instanceof CharSequence )   return equals( ((CharSequence)  object ), sensitivity );

            // not a known comparable object
            return false;
        }

        /** ****************************************************************************************
         * Compares this to the given object. .
         *
         * @param   object The object to compare to this instance.
         *
         * @return  True if given object equals this.
         ******************************************************************************************/
        @Override
        public boolean equals( Object object )
        {
            return equals( object,  Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given AString equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString The %AString that is compared to this \b %AString.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( AString cmpString, Case sensitivity )
        {
            // null?
            if ( cmpString == null || cmpString.isNull() )
                return isNull();

            // same length?
            if ( cmpString.length != length )
                return false;

            return 0 == compareTo( cmpString, sensitivity, 0, length, 0, length );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given AString equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString The %AString that is compared to this \b %AString.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( AString cmpString )
        {
            // null?
            if ( cmpString == null || cmpString.isNull() )
                return isNull();

            // same length?
            if ( cmpString.length != length )
                return false;

            return 0 == compareTo( cmpString, Case.SENSITIVE, 0, length, 0, length );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given String equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString The %AString that is compared to this \b %AString.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( String cmpString, Case sensitivity )
        {
            // null?
            if ( cmpString == null )
                return isNull();

            // same length?
            if ( cmpString.length() != length )
                return false;

            return 0 == compareTo( cmpString, sensitivity, 0, length, 0, length );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given String equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString The %AString that is compared to this \b %AString.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( String cmpString )
        {
            // null?
            if ( cmpString == null )
                return isNull();

            // same length?
            if ( cmpString.length() != length )
                return false;

            return 0 == compareTo( cmpString, Case.SENSITIVE, 0, length, 0, length );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given \ref com.aworx.lib.strings.Substring "Substring"
         * equals to what this object represents.
         * True is returned if both are zero length or \c null.
         *
         * @param cmpString A Substring that is compared to this \b %AString.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals(com.aworx.lib.strings.Substring cmpString, Case sensitivity )
        {
            // null?
            if ( cmpString == null )
                return isNull();

            // same length?
            if ( cmpString.length() != length )
                return false;

            return containsAt( cmpString, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given \ref com.aworx.lib.strings.Substring "Substring"
         * equals to what this object represents.
         * True is returned if both are zero length or \c null.
         *
         * @param cmpString A Substring that is compared to this \b %AString.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( com.aworx.lib.strings.Substring cmpString )
        {
            // null?
            if ( cmpString == null )
                return isNull();

            // same length?
            if ( cmpString.length() != length )
                return false;

            return containsAt( cmpString, 0, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given CharSequence equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString A CharSequence that is compared to this \b %AString.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( CharSequence cmpString, Case sensitivity )
        {
            // null?
            if ( cmpString == null )
                return isNull();

            // same length?
            if ( cmpString.length() != length )
                return false;

            return containsAt( cmpString, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given CharSequence equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString A CharSequence that is compared to this \b %AString.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( CharSequence cmpString )
        {
            // null?
            if ( cmpString == null )
                return isNull();

            // same length?
            if ( cmpString.length() != length )
                return false;

            return containsAt( cmpString, 0, Case.SENSITIVE );
        }



    /** ############################################################################################
     * @name Search
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Search a character in the buffer.
         *
         * @param c             The character to search.
         * @param startIdx      The index to start the search at. Optional and defaults to \c 0.
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
         * Search a character in the buffer.
         *
         * @param c    The character to search.
         *
         * @return  -1 if the character is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOf( char c )
        {
            return indexOf( c, 0 );
        }

        /** ****************************************************************************************
         * Like #indexOf but in case the character is not found, this method returns the length of
         * this string instead of \c -1.
         * Depending on the invocation context, the choice for the right version of this method may
         * lead to shorter and more efficient code.
         *
         * @param needle  The character to search for.
         * @return  This strings #length if the character \p needle is not found.
         *          Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int    indexOfOrLength( char needle )
        {
            int idx= 0;
            while ( idx < length && needle != buffer[ idx ])
                idx++;

            return idx;
        }

        /** ****************************************************************************************
         * Like #indexOf but in case the character is not found, this method returns the length of
         * this string instead of \c -1.
         * Depending on the invocation context, the choice for the right version of this method may
         * lead to shorter and more efficient code.
         *
         * @param needle    The character to search for.
         * @param startIdx  The index in this to start searching the character.
         * @return  This strings #length if the character \p needle is not found.
         *          Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int    indexOfOrLength( char needle, int startIdx )
        {
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return length;
            while ( startIdx < length && needle != buffer[ startIdx ])
                startIdx++;

            return startIdx;
        }

        /** ****************************************************************************************
         * Search the given String in the buffer starting at a given position.
         *
         * @param needle        The CharSequence to search.
         * @param startIdx      The index to start the search at. Optional and defaults to \c 0.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  -1 if the String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOf( CharSequence needle, int startIdx, Case sensitivity )
        {
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return -1;
            return com.aworx.lib.strings.CString.indexOfString( needle, buffer, startIdx, length - startIdx, sensitivity );
        }

        /** ****************************************************************************************
         * Search a CharSequence in the buffer.
         *
         * @param cs            The CharSequence to search.
         * @param startIdx      The index to start the search at. Optional and defaults to \c 0.
         *
         * @return  -1 if the String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOf( CharSequence cs, int startIdx )
        {
            return indexOf( cs, startIdx, Case.SENSITIVE );
        }


        /** ****************************************************************************************
         * Search a CharSequence in the buffer.
         *
         * @param cs            The CharSequence to search.
         * @return  -1 if the String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOf( CharSequence cs )
        {
            return indexOf( cs, 0, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         *
         * This method searches from left to right. For reverse search, see
         * #lastIndexOfAny.
         *
         * @param needles    Characters to be searched for.
         * @param inclusion  Denotes whether the search returns the first index that holds a value
         *                   that is included or that is not excluded in the set of needle
         *                   characters.
         * @param startIdx   The index to start the search at. If the given value is less than 0,
         *                   it is set to 0. If it exceeds the length of the string, the length of
         *                   the string is returned.
         *                   Defaults to 0.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        public int indexOfAny( char[] needles, Inclusion inclusion, int startIdx )
        {
            if ( startIdx < 0       ) startIdx= 0;
            if ( startIdx >= length ) return   -1;

            return com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, startIdx, length - startIdx, needles, inclusion );
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         *
         * This method searches from left to right. For reverse search, see #lastIndexOfAny.
         *
         * @param needles    Characters to be searched for.
         * @param inclusion  Denotes whether the search returns the first index that holds a value
         *                   that is included or that is not excluded in the set of needle
         *                   characters.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        public int indexOfAny( char[] needles, Inclusion inclusion )
        {
            if ( length == 0 ) return   -1;

            return com.aworx.lib.strings.CString.indexOfAnyInRegion( buffer, 0, length, needles, inclusion );
        }

        /** ****************************************************************************************
         * Searches a character backwards from the given start index.
         *
         * @param needle       The character to search for.
         * @param startIndex   The index in this to start searching the character.
         *                     Defaults to the end of this string.
         *
         * @return  -1 if the character \p needle is not found.
         *          Otherwise the index of its last occurrence relative to the start index.
         ******************************************************************************************/
        public int lastIndexOf( char needle, int startIndex )
        {
            // adjust range, if empty return -1
            if ( startIndex <  0      )   return -1;
            if ( startIndex >= length )   startIndex= length - 1;

            while( startIndex >= 0 && buffer[ startIndex ] != needle )
                startIndex--;

            return startIndex;
        }

        /** ****************************************************************************************
         * Searches a character backwards from the end or a given start index.
         *
         * @param needle       The character to search for.
         *
         * @return  -1 if the character \p needle is not found.
         *          Otherwise the index of its last occurrence relative to the start index.
         ******************************************************************************************/
        public int lastIndexOf( char needle )
        {
            if ( length == 0 ) return   -1;
            return lastIndexOf( needle, length );
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         * The search starts at the given index and goes backward.
         * For forward search, see #indexOfAny(char[] p,Inclusion,int) "indexOfAny".

         *
         * @param needles    Characters to be searched for.
         * @param inclusion  Denotes whether the search returns the first index that holds a value
         *                   that is included or that is not excluded in the set of needle
         *                   characters.
         * @param startIdx   The index to start the search at. The value is cropped to be in
         *                   the bounds of 0 and the length of this \b %AString minus one.
         *                   Defaults to the length of this AString.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        public int lastIndexOfAny( char[] needles, Inclusion inclusion, int startIdx )
        {
            if ( startIdx < 0       ) return -1;
            if ( startIdx >= length ) startIdx=  length - 1;
            return  com.aworx.lib.strings.CString.lastIndexOfAny( buffer, 0, startIdx + 1, needles, inclusion );
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         * The search starts at the given index and goes backward.
         * For forward search, see #indexOfAny(char[] p,Inclusion,int) "indexOfAny".
         *
         * @param needles    Characters to be searched for.
         * @param inclusion  Denotes whether the search returns the first index that holds a value
         *                   that is included or that is not excluded in the set of needle
         *                   characters.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        public int lastIndexOfAny( char[] needles, Inclusion inclusion )
        {
            if ( length == 0 ) return   -1;
            return  com.aworx.lib.strings.CString.lastIndexOfAny( buffer, 0, length, needles, inclusion );
        }


    /** ############################################################################################
     * @name Replace
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Replaces one or more occurrences of one character by another character.
         *
         * @param needle           The terminatable string to be replaced.
         * @param replacement      The replacement string (does not need to be zero terminatable).
         * @param startIdx         The index where the search starts. Optional and defaults 0.
         *
         * @return The number of replacements that where performed.
         ******************************************************************************************/
        public int searchAndReplace( char needle, char replacement, int startIdx )
        {
                 if ( startIdx <  0      )  startIdx= 0;
            else if ( startIdx >= length )  return 0;

            // replacement loop
            int cntReplacements=    0;
            for(;;)
            {
                startIdx= indexOfOrLength( needle, startIdx  );
                if ( startIdx >= length  )
                    return cntReplacements;
                buffer[ startIdx ]= replacement;
                cntReplacements++;
            }
        }

        /** ****************************************************************************************
         * Replaces one or more occurrences of one character by another character.
         *
         * @param needle           The terminatable string to be replaced.
         * @param replacement      The replacement string (does not need to be zero terminatable).
         *
         * @return The number of replacements that where performed.
         ******************************************************************************************/
        public int searchAndReplace( char needle, char replacement )
        {
            return searchAndReplace( needle, replacement, 0 );
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. Returns the number
         * of replacements.
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         * @param startIdx          The index where the search starts. Optional and defaults to \c 0.
         * @param maxReplacements   The maximum number of replacements to perform. Optional and
         *                          defaults to Integer.MAX_VALUE .
         * @param sensitivity       Case sensitivity of the operation.
         *                          Optional and defaults to Case.Sensitive.
         *
         * @return  The number of replacements that where performed.
         ******************************************************************************************/
        @SuppressWarnings ("null")
        public int searchAndReplace( CharSequence searchStr, CharSequence newStr, int startIdx,
                                     int maxReplacements, Case sensitivity )
        {

            // check null arguments
            if ( com.aworx.lib.strings.CString.isNullOrEmpty(searchStr) )
                return 0;

            // get some values
            int searchStringLength=     searchStr.length();
            int newStringLength=        (newStr != null) ? newStr.length()  : 0;
            int lenDiff=                newStringLength - searchStringLength;

            // replacement loop
            int cntReplacements=    0;
            int idx= -1;
            while ( cntReplacements < maxReplacements && idx < length )
            {
                // search  next occurrence
                if ( ( idx= indexOf( searchStr, startIdx, sensitivity ) ) < 0 )
                    return cntReplacements;

                // set dirty
                hash= 0;

                // copy rest up or down
                if ( lenDiff != 0 )
                {
                    if ( buffer.length < length + lenDiff )
                        ensureRemainingCapacity( lenDiff );

                    System.arraycopy( buffer, idx + searchStringLength,
                                      buffer, idx + searchStringLength + lenDiff,
                                      length - idx - searchStringLength );
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
         * of replacements.
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         * @param startIdx          The index where the search starts. Optional and defaults to \c 0.
         * @param maxReplacements   The maximum number of replacements to perform. Optional and
         *                          defaults to Integer.MAX_VALUE .
         *
         * @return  The number of replacements that where performed.
         ******************************************************************************************/
        public int searchAndReplace( CharSequence searchStr, CharSequence newStr,
                                     int startIdx, int maxReplacements )
        {
            return searchAndReplace( searchStr, newStr, startIdx, maxReplacements, Case.SENSITIVE);
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. Returns the number
         * of replacements.
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         * @param startIdx          The index where the search starts. Optional and defaults to \c 0.
         *
         * @return  The number of replacements that where performed.
         ******************************************************************************************/
        public int searchAndReplace( CharSequence searchStr, CharSequence newStr, int startIdx )
        {
            return searchAndReplace( searchStr, newStr, startIdx, Integer.MAX_VALUE, Case.SENSITIVE);
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. Returns the number
         * of replacements.
         *
         * @param searchStr         The CharSequence to be replaced.
         * @param newStr            The replacement string.
         *
         * @return  The number of replacements that where performed.
         ******************************************************************************************/
        public int searchAndReplace( CharSequence searchStr, CharSequence newStr)
        {
            return searchAndReplace( searchStr, newStr, 0, Integer.MAX_VALUE, Case.SENSITIVE);
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
        public AString searchAndReplaceAll( CharSequence searchStr, CharSequence newStr)
        {
            searchAndReplace( searchStr, newStr, 0, Integer.MAX_VALUE, Case.SENSITIVE);
            return this;
        }

        /** ****************************************************************************************
         * Converts all or a region of characters in the buffer to upper case.
         *
         * @param regionStart     Start of the region to be converted. Defaults to 0
         * @param regionLength    Length of the region to be converted. Defaults to int.MaxValue.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString toUpper( int regionStart, int regionLength )
        {
            if ( com.aworx.lib.strings.CString.adjustRegion( length, regionStart, regionLength, _adjustedRegion ) )
                return this;

            hash= 0;
            int regionEnd= _adjustedRegion[0] + _adjustedRegion[1];
            for ( int i= _adjustedRegion[0]; i < regionEnd ; i++ )
                buffer[ i ]=  Character.toUpperCase( buffer[ i ] );

            return this;
        }

        /** ****************************************************************************************
         * Converts characters in the buffer to upper case.
         *
         * @param regionStart     Start of the region to be converted. Defaults to 0
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString toUpper( int regionStart )
        {
            return toUpper( regionStart, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Converts all characters in the buffer to upper case.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString toUpper()
        {
            return toUpper( 0, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Converts all or a region of characters in the buffer to lower case.
         *
         * @param regionStart     Start of the region to be converted. Defaults to 0
         * @param regionLength    Length of the region to be converted. Defaults to int.MaxValue.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString toLower( int regionStart, int regionLength )
        {
            if ( com.aworx.lib.strings.CString.adjustRegion( length, regionStart, regionLength, _adjustedRegion ) )
                return this;

            hash= 0;
            int regionEnd= _adjustedRegion[0] + _adjustedRegion[1];
            for ( int i= _adjustedRegion[0]; i < regionEnd ; i++ )
                buffer[ i ]=  Character.toLowerCase( buffer[ i ] );

            return this;
        }

        /** ****************************************************************************************
         * Converts characters in the buffer to lower case.
         *
         * @param regionStart     Start of the region to be converted. Defaults to 0
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString toLower( int regionStart )
        {
            return toLower( regionStart, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Converts all characters in the buffer to lower case.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString toLower()
        {
            return toLower( 0, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Escapes non-printable characters in the given region, or converts such escaped characters
         * to their ASCII values.<br>
         * If the new region length is needed to be known, it can be calculated as the sum of
         * the old region length and the difference of the string before and after the operation.
         *
         * @param escape        \b Switch.On escapes ascii characters (the default),
         *                      \b Switch.Off converts  escaped strings to ascii codes.
         * @param regionStart   The start of the region to convert.
         * @param regionLength  The length of the region to convert.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString escape( Switch escape, int regionStart, int regionLength )
        {
           if( com.aworx.lib.strings.CString.adjustRegion(length, regionStart, regionLength, _adjustedRegion) )
               return this;

            int regionEnd= _adjustedRegion[0] + _adjustedRegion[1];

            //
            // To escape sequences
            //
            if (escape == Switch.ON)
            {
                for( int idx= _adjustedRegion[0]; idx < regionEnd ; ++idx )
                {
                    char c= buffer[idx];

                    char resultChar= '\0';
                    switch(c)
                    {
                        case '\\' : resultChar= '\\'; break;
                        case '\r' : resultChar= 'r' ; break;
                        case '\n' : resultChar= 'n' ; break;
                        case '\t' : resultChar= 't' ; break;
                    //  case '\a' : resultChar= 'a' ; break;
                        case '\b' : resultChar= 'b' ; break;
                    //  case '\v' : resultChar= 'v' ; break;
                        case '\f' : resultChar= 'f' ; break;
                    //  case '\e' : resultChar= 'e' ; break; Not C++ standard
                        case '"'  : resultChar= '"' ; break;

                        default   :                   break;
                    }

                    if( resultChar != '\0')
                    {
                        insertChars( ' ', 1, idx);
                        buffer[idx++]= '\\';
                        buffer[idx]= resultChar;
                        regionEnd++;
                    }
                    else
                    {
                        if (c < 32  )
                        {
                            insertChars(' ', 3, idx);
                            buffer[idx++]= '\\';
                            buffer[idx++]= '0';
                            int oct= c >> 3;
                            buffer[idx++]=  (char) ( '0' + oct );
                                 oct=       (char) ( c & 7 );
                            buffer[idx]  =  (char) ( '0' + oct );

                            regionEnd+=3;
                        }
                        else
                        if ( c >126 )
                        {
                            insertChars(' ', 3, idx);
                            buffer[idx++]= '\\';
                            buffer[idx++]= 'x';
                            int nibble= c >> 4;
                            buffer[idx++]= (char) ( (nibble <10 ? '0' : 'A' -10) + nibble );
                                nibble=    (char) ( c & 15 );
                            buffer[idx]  = (char) ( (nibble <10 ? '0' : 'A' -10) + nibble );

                            regionEnd+=3;
                        }
                    }
                }
            }

            //
            // Un-escape escape sequences
            //
            else
            {
                regionEnd--; // we can go 1 over it!
                for( int idx= _adjustedRegion[0]; idx < regionEnd ; ++idx )
                {
                    char c= buffer[idx];
                    if( c != '\\' )
                        continue;
                    c= buffer[idx + 1];

                    char resultChar= '\0';
                    switch(c)
                    {
                        case '\\' : resultChar= '\\' ; break;
                        case 'r'  : resultChar= '\r' ; tabReference= idx + 1; break;
                        case 'n'  : resultChar= '\n' ; tabReference= idx + 1; break;
                        case 't'  : resultChar= '\t' ; break;
                    //  case 'a'  : resultChar= '\a' ; break;
                        case 'b'  : resultChar= '\b' ; break;
                    //  case 'v'  : resultChar= '\v' ; break;
                        case 'f'  : resultChar= '\f' ; break;
                     // case 'e'  : resultChar= '\e' ; break; Not C++ standard
                        case '"'  : resultChar= '"' ; break;

                        default   :                   break;
                    }

                    if( resultChar != '\0')
                    {
                        delete( idx, 1);
                        buffer[idx]= resultChar;
                        regionEnd--;
                    }
                    else
                    {
                        if (c == '0' && idx + 2 < regionEnd )
                        {
                            buffer[idx]= (char) (   (buffer[idx + 2] - '0' ) *8
                                                  + (buffer[idx + 3] - '0' ))        ;
                            delete( idx + 1, 3);
                            regionEnd-=3;
                        }
                        else
                        if (c == 'x' && idx + 2 < regionEnd )
                        {
                            c= buffer[idx+2];
                                 if( c>='0' && c<= '9') c-= '0';
                            else if( c>='a' && c<= 'f') c-= (char) ( 'a' - 10 );
                            else if( c>='A' && c<= 'F') c-= (char) ( 'A' - 10 );
                            char nc= c;
                            c= buffer[idx + 3];
                                 if( c>='0' && c<= '9') c-= '0';
                            else if( c>='a' && c<= 'f') c-= (char) ( 'a' - 10 );
                            else if( c>='A' && c<= 'F') c-= (char) ( 'A' - 10 );

                            buffer[idx]= (char) ( (nc << 4) + c );
                            delete( idx+1, 3);
                            regionEnd-=3;
                        }
                    }
                }
            }


            return this;
        }

        /** ****************************************************************************************
         * Overloaded version providing default parameter(s).
         *
         * @param escape        \b Switch.On escapes ascii characters (the default),
         *                      \b Switch.Off converts  escaped strings to ascii codes.
         * @param regionStart   The start of the region to convert.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString escape( Switch escape, int regionStart )
        {
            return escape( escape, regionStart, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Overloaded version providing default parameter(s).
         *
         * @param escape        \b Switch.On escapes ascii characters (the default),
         *                      \b Switch.Off converts  escaped strings to ascii codes.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString escape( Switch escape )
        {
            return escape( escape, 0, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Overloaded version providing default parameter(s).
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString escape()
        {
            return escape( Switch.ON, 0, Integer.MAX_VALUE );
        }


    /** ############################################################################################
     * @name Conversion
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Format and append a 32-Bit integer value.
         *
         * Parameter \p numberFormat defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational".
         * To generate output better readable for humans, provide
         * \ref com.aworx.lib.strings.NumberFormat.global "NumberFormat.global", or a
         * customized object of that type.
         *
         * See \ref com.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.<br>
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.decMinimumFieldWidth "NumberFormat.decMinimumFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( int value, int overrideWidth, NumberFormat numberFormat )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= com.aworx.lib.strings.NumberFormat.computational;

            ensureRemainingCapacity( 28 );

            length= numberFormat.writeDecSigned( value, buffer, length, overrideWidth );

            com.aworx.lib.ALIB_DBG.ASSERT( length <= capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_(int,int,NumberFormat) which provides default parameter(s).
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.decMinimumFieldWidth "NumberFormat.decMinimumFieldWidth".
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( int value, int overrideWidth )
        {
            return _(value, overrideWidth, null );
        }

        /** ****************************************************************************************
         * Overloaded version of #_(int,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( int value )
        {
            return _(value, 0, null );
        }

        /** ****************************************************************************************
         * Overloaded version of #_(int,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( int value, NumberFormat numberFormat )
        {
            return _(value, 0, numberFormat );
        }


        /** ****************************************************************************************
         * Format and append a 64-Bit integer value.
         *
         * Parameter \p numberFormat defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational".
         * To generate output better readable for humans, provide
         * \ref com.aworx.lib.strings.NumberFormat.global "NumberFormat.global", or a
         * customized object of that type.
         *
         * See \ref com.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.<br>
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.decMinimumFieldWidth "NumberFormat.decMinimumFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( long value, int overrideWidth, NumberFormat numberFormat )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= com.aworx.lib.strings.NumberFormat.computational;

            ensureRemainingCapacity( 28 );

            length= numberFormat.writeDecSigned( value, buffer, length, overrideWidth );

            com.aworx.lib.ALIB_DBG.ASSERT( length <= capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_(long,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.decMinimumFieldWidth "NumberFormat.decMinimumFieldWidth".
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( long value, int overrideWidth )
        {
            return _(value, overrideWidth, null );
        }

        /** ****************************************************************************************
         * Overloaded version of #_(long,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( long value )
        {
            return _(value, 0, null );
        }

        /** ****************************************************************************************
         * Overloaded version of #_(long,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( long value, NumberFormat numberFormat )
        {
            return _(value, 0, numberFormat );
        }

        /** ****************************************************************************************
         * Append a 64-Bit integer value in binary format.
         *
         * Parameter \p numberFormat defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational".
         * To generate output better readable for humans, provide
         * \ref com.aworx.lib.strings.NumberFormat.global "NumberFormat.global", or a
         * customized object of that type.
         *
         * See \ref com.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.<br>
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.binFieldWidth "NumberFormat.binFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Bin( long value, int overrideWidth, NumberFormat numberFormat )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= com.aworx.lib.strings.NumberFormat.computational;

            ensureRemainingCapacity( 80 );

            length= numberFormat.writeBin( value, buffer, length, overrideWidth );

            com.aworx.lib.ALIB_DBG.ASSERT( length <= capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_Bin(long,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.binFieldWidth "NumberFormat.binFieldWidth".
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Bin( long value, int overrideWidth )
        {
            return _Bin(value, overrideWidth, null );
        }

        /** ****************************************************************************************
         * Overloaded version of #_Bin(long,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Bin( long value)
        {
            return _Bin(value, 0, null );
        }

        /** ****************************************************************************************
         * Overloaded version of #_Bin(long,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Bin( long value, NumberFormat numberFormat)
        {
            return _Bin(value, 0, numberFormat );
        }

        /** ****************************************************************************************
         * Append a 64-Bit integer value in hexadecimal format.
         *
         * Parameter \p numberFormat defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational".
         * To generate output better readable for humans, provide
         * \ref com.aworx.lib.strings.NumberFormat.global "NumberFormat.global", or a
         * customized object of that type.
         *
         * See \ref com.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.<br>
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.hexFieldWidth "NumberFormat.hexFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Hex( long value, int overrideWidth, NumberFormat numberFormat )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= com.aworx.lib.strings.NumberFormat.computational;

            ensureRemainingCapacity( 25 );

            length= numberFormat.writeHex( value, buffer, length, overrideWidth );

            com.aworx.lib.ALIB_DBG.ASSERT( length <= capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_Hex(long,int,NumberFormat) which provides default
         * parameter(s).
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.hexFieldWidth "NumberFormat.hexFieldWidth".
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Hex( long value, int overrideWidth )
        {
            return _Hex(value,overrideWidth,null);
        }

        /** ****************************************************************************************
         * Overloaded version of #_Hex(long,int,NumberFormat) which provides default
         * parameter(s).
         *
         * @param value         The value to append.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Hex( long value )
        {
            return _Hex(value,0,null);
        }

        /** ****************************************************************************************
         * Overloaded version of #_Hex(long,int,NumberFormat) which provides default
         * parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Hex( long value, NumberFormat numberFormat )
        {
            return _Hex(value,0,numberFormat);
        }

        /** ****************************************************************************************
         * Append a 64-Bit integer value in octal format.
         *
         * Parameter \p numberFormat defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational".
         * To generate output better readable for humans, provide
         * \ref com.aworx.lib.strings.NumberFormat.global "NumberFormat.global", or a
         * customized object of that type.
         *
         * See \ref com.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.<br>

         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.octFieldWidth "NumberFormat.octFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Oct( long value, int overrideWidth, NumberFormat numberFormat )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= com.aworx.lib.strings.NumberFormat.computational;

            ensureRemainingCapacity( 30 );

            length= numberFormat.writeOct( value, buffer, length, overrideWidth );

            com.aworx.lib.ALIB_DBG.ASSERT( length <= capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_Oct(long,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.octFieldWidth "NumberFormat.octFieldWidth".
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Oct( long value, int overrideWidth )
        {
            return _Oct(value, overrideWidth, null );
        }

        /** ****************************************************************************************
         * Overloaded version of #_Oct(long,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Oct( long value )
        {
            return _Oct(value, 0, null );
        }

        /** ****************************************************************************************
         * Overloaded version of #_Oct(long,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Oct( long value, NumberFormat numberFormat )
        {
            return _Oct(value, 0, numberFormat );
        }

        /** ****************************************************************************************
         * Append a double value. See
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.
         *
         * @param value         The double value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.integralPartMinimumWidth "NumberFormat.integralPartMinimumWidth"
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( double value, int overrideWidth, NumberFormat numberFormat )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= com.aworx.lib.strings.NumberFormat.computational;

            ensureRemainingCapacity( 48 ); // 2x15 + '.' + ',' + sign + fear

            length= numberFormat.writeFloat( value, buffer, length, overrideWidth );

            com.aworx.lib.ALIB_DBG.ASSERT( length <= capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_(double,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The double value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref com.aworx.lib.strings.NumberFormat.integralPartMinimumWidth "NumberFormat.integralPartMinimumWidth"
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( double value, int overrideWidth )
        {
            return _(value, overrideWidth, null );
        }

        /** ****************************************************************************************
         * Overloaded version of #_(double,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The double value to append.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( double value )
        {
            return _(value, 0, null );
        }

        /** ****************************************************************************************
         * Overloaded version of #_(double,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The double value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( double value, NumberFormat numberFormat )
        {
            return _(value, 0, numberFormat );
        }


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
            if ( com.aworx.lib.strings.CString.adjustRegion( length, regionStart, regionLength, _adjustedRegion ) )
                return com.aworx.lib.strings.CString.EMPTY;

            // create string
            return new String( buffer, _adjustedRegion[0], _adjustedRegion[1] );
        }

        /** ****************************************************************************************
         * Creates a String containing a copy of the ending of the AString.
         *
         * @param regionStart  The start point from where on the remainder of this AString is copied.
         *
         * @return  A string that represents the specified sub region of this object
         ******************************************************************************************/
        public String toString( int regionStart )
        {
            return toString( regionStart, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Creates a String containing a copy of the contents of this AString.
         *
         * @return  A string that represents this object.
         ******************************************************************************************/
        @Override
        public String toString()
        {
            return new String( buffer, 0, length );
        }


        /** ****************************************************************************************
         * Copies a region of the contents of this AString into the given StringBuilder.
         *
         * @param result        A result StringBuilder to copy the specified region into.
         *                      If \c null, a new String builder is created
         * @param regionStart   The start index of the region to be copied.
         * @param regionLength  The maximum length of the region to be copied.
         * @param appendMode    If true, any contents in the result is preserved.
         *                      Otherwise such content gets replaced.
         * @return  The (modified) result that was provided (for concatenation of calls).
         ******************************************************************************************/
        public StringBuilder toString( StringBuilder result, int regionStart, int regionLength,
                                       boolean appendMode )

        {
            if ( result == null)
                result= new StringBuilder();
            else if ( !appendMode )
                result.delete( 0, result.length() );

            // adjust range, if empty return empty string
            if ( com.aworx.lib.strings.CString.adjustRegion( length, regionStart, regionLength, _adjustedRegion ) )
                return result;

            // copy our buffer into result
            result.append( buffer , _adjustedRegion[0], _adjustedRegion[1] );
            return  result;
        }

        /** ****************************************************************************************
         * Parses an integer value consisting of characters \c '0' to \c '9' from this string.
         * <br>Unlike with #parseInt or #parseDec, no sign, whitespaces or group characters are
         * accepted.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseDecDigits( int startIdx, int[] newIdx )
        {
            return com.aworx.lib.strings.NumberFormat.parseDecDigits( buffer, startIdx, length-1, newIdx  );
        }

        /** ****************************************************************************************
         * Parses a long integer value in decimal, binary, hexadecimal or octal format from
         * the string by invoking method
         * \ref com.aworx.lib.strings.NumberFormat.parseInt "NumberFormat.parseInt"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to 'international' settings (not using the locale) and therefore
         * also not parsing grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long  parseInt( int startIdx, NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseInt( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseInt(int,NumberFormat,int[] p) "parseInt" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long  parseInt( int startIdx, NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseInt( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseInt(int,NumberFormat,int[] p) "parseInt" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @return  The parsed value.
         ******************************************************************************************/
        public long parseInt( int startIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseInt( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseInt(int,NumberFormat,int[] p) "parseInt" providing default values for
         * omitted parameters.
         *
         * @return  The parsed value.
         ******************************************************************************************/
        public long parseInt()
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseInt( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseInt(int,NumberFormat,int[] p) "parseInt" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseInt( int startIdx, int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseInt( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseInt(int,NumberFormat,int[] p) "parseInt" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long  parseInt( NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseInt( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseInt(int,NumberFormat,int[] p) "parseInt" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long  parseInt( NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseInt( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseInt(int,NumberFormat,int[] p) "parseInt" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseInt( int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseInt( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in standard decimal format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref com.aworx.lib.strings.NumberFormat.parseDec "NumberFormat.parseDec"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail.
         * For reading signed integer values, see methods #parseInt, for floating point numbers
         * #parseFloat.
         *
         * For more information on number conversion, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * \note Because Java does not support unsigned integer, the value to read is limited to
         *       <c>Long.MAX_VALUE</c> in this language implementation of \b %ALib.
         *
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         *
         * @return  The parsed value. In addition, the output parameter \p newIdx is set to point
         *          to the first character behind the parsed number.
         ******************************************************************************************/
        public long  parseDec( int startIdx, NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseDec( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseDec(int,NumberFormat,int[] p) "parseDec" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long  parseDec( int startIdx, NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseDec( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseDec(int,NumberFormat,int[] p) "parseDec" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @return  The parsed value.
         ******************************************************************************************/
        public long parseDec( int startIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseDec( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseDec(int,NumberFormat,int[] p) "parseDec" providing default values for
         * omitted parameters.
         *
         * @return  The parsed value.
         ******************************************************************************************/
        public long parseDec()
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseDec( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseDec(int,NumberFormat,int[] p) "parseDec" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseDec( int startIdx, int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseDec( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseDec(int,NumberFormat,int[] p) "parseDec" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long  parseDec( NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseDec( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseDec(int,NumberFormat,int[] p) "parseDec" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long  parseDec( NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseDec( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseDec(int,NumberFormat,int[] p) "parseDec" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseDec( int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseDec( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in binary format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref com.aworx.lib.strings.NumberFormat.parseBin "NumberFormat.parseBin"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * \note Although Java does not support unsigned integer, the value that is read with this
         *       method is correct in respect to the bits set in the signed value returned.
         *       In other words, if the most significant bit (#64), is set, the return value is
         *       negative.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         *
         * @return  The parsed value. In addition, the output parameter \p newIdx is set to point
         *          to the first character behind the parsed number.
         ******************************************************************************************/
        public long  parseBin( int startIdx, NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseBin( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseBin(int,NumberFormat,int[] p) "parseBin" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long  parseBin( int startIdx, NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseBin( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseBin(int,NumberFormat,int[]p ) "parseBin" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @return  The parsed value.
         ******************************************************************************************/
        public long parseBin( int startIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseBin( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseBin(int,NumberFormat,int[] p) "parseBin" providing default values for
         * omitted parameters.
         *
         * @return  The parsed value.
         ******************************************************************************************/
        public long parseBin()
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseBin( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseBin(int,NumberFormat,int[] p) "parseBin" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseBin( int startIdx, int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseBin( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseBin(int,NumberFormat,int[] p) "parseBin" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long  parseBin( NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseBin( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseBin(int,NumberFormat,int[] p) "parseBin" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long  parseBin( NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseBin( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseBin(int,NumberFormat,int[] p) "parseBin" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseBin( int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseBin( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in hexadecimal format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref com.aworx.lib.strings.NumberFormat.parseHex "NumberFormat.parseHex"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * \note Although Java does not support unsigned integer, the value that is read with this
         *       method is correct in respect to the bits set in the signed value returned.
         *       In other words, if the most significant bit (#64), is set, the return value is
         *       negative. For this, 16 hexadecimal digits need to be read and the first of
         *       them needs to be greater or equal to \b 0x8.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         *
         * @return  The parsed value. In addition, the output parameter \p newIdx is set to point
         *          to the first character behind the parsed number.
         ******************************************************************************************/
        public long  parseHex( int startIdx, NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseHex( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseHex(int,NumberFormat,int[] p) "parseHex" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long  parseHex( int startIdx, NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseHex( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseHex(int,NumberFormat,int[] p) "parseHex" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @return  The parsed value.
         ******************************************************************************************/
        public long parseHex( int startIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseHex( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseHex(int,NumberFormat,int[] p) "parseHex" providing default values for
         * omitted parameters.
         *
         * @return  The parsed value.
         ******************************************************************************************/
        public long parseHex()
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseHex( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseHex(int,NumberFormat,int[] p) "parseHex" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseHex( int startIdx, int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseHex( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseHex(int,NumberFormat,int[] p) "parseHex" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long  parseHex( NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseHex( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseHex(int,NumberFormat,int[] p) "parseHex" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long  parseHex( NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseHex( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseHex(int,NumberFormat,int[] p) "parseHex" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseHex( int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseHex( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in octal format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref com.aworx.lib.strings.NumberFormat.parseOct "NumberFormat.parseOct"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * \note Although Java does not support unsigned integer, the value that is read with this
         *       method is correct in respect to the bits set in the signed value returned.
         *       In other words, if the most significant bit (#64), is set, the return value is
         *       negative. For this, 22 octal digits need to be read with the first being \c 1.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         *
         * @return  The parsed value. In addition, the output parameter \p newIdx is set to point
         *          to the first character behind the parsed number.
         ******************************************************************************************/
        public long  parseOct( int startIdx, NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseOct( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseOct(int,NumberFormat,int[] p) "parseOct" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long  parseOct( int startIdx, NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseOct( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseOct(int,NumberFormat,int[] p) "parseOct" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @return  The parsed value.
         ******************************************************************************************/
        public long parseOct( int startIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseOct( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseOct(int,NumberFormat,int[] p) "parseOct" providing default values for
         * omitted parameters.
         *
         * @return  The parsed value.
         ******************************************************************************************/
        public long parseOct()
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseOct( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseOct(int,NumberFormat,int[] p) "parseOct" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseOct( int startIdx, int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseOct( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseOct(int,NumberFormat,int[] p) "parseOct" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long  parseOct( NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseOct( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseOct(int,NumberFormat,int[] p) "parseOct" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long  parseOct( NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseOct( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseOct(int,NumberFormat,int[] p) "parseOct" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long parseOct( int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseOct( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Reads a floating point number at the given position from this \b %AString.
         * This is done, by invoking
         * \ref com.aworx.lib.strings.NumberFormat.parseFloat "NumberFormat.parseFloat"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to 'international' settings (not using the locale) and therefore
         * also not parsing grouping characters.
         *
         * Optional output parameter \p newIdx may be used to detect if parsing was successful.
         * If not, it receives the value of \p startIdx, even if leading whitespaces had been
         * read.
         *
         * For more information on parsing options for floating point numbers and number
         * conversion in general, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         *
         * @return  The parsed value. In addition, the output parameter \p newIdx is set to point
         *          to the first character behind any found float number.
         ******************************************************************************************/
        public double  parseFloat( int startIdx, NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseFloat( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseFloat(int,NumberFormat,int[] p) "parseFloat" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public double  parseFloat( int startIdx, NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseFloat( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseFloat(int,NumberFormat,int[] p) "parseFloat" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @return  The parsed value.
         ******************************************************************************************/
        public double parseFloat( int startIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseFloat( buffer, startIdx, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseFloat(int,NumberFormat,int[] p) "parseFloat" providing default values for
         * omitted parameters.
         *
         * @return  The parsed value.
         ******************************************************************************************/
        public double parseFloat()
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseFloat( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseFloat(int,NumberFormat,int[] p) "parseFloat" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \p startIdx.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public double parseFloat( int startIdx, int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseFloat( buffer, startIdx, length - 1, newIdx );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseFloat(int,NumberFormat,int[] p) "parseFloat" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public double  parseFloat( NumberFormat numberFormat, int[] newIdx )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseFloat( buffer, 0, length - 1, newIdx );
        }


        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseFloat(int,NumberFormat,int[] p) "parseFloat" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public double  parseFloat( NumberFormat numberFormat )
        {
            return ( numberFormat != null ? numberFormat
                                          : com.aworx.lib.strings.NumberFormat.computational ).parseFloat( buffer, 0, length - 1, null );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref parseFloat(int,NumberFormat,int[] p) "parseFloat" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public double parseFloat( int[] newIdx )
        {
            return  com.aworx.lib.strings.NumberFormat.computational.parseFloat( buffer, 0, length - 1, newIdx );
        }


    /** ############################################################################################
     * @name Java std library interface implementation
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Calculates the hash value using the same formula as java.lang.String.
         *
         * @return  A hash value for this object.
         ******************************************************************************************/
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

        // note: charAt() already implemented in standard interface

        /** ****************************************************************************************
         * Reports an \b %ALib error (using \ref com.aworx.lib.lang.ReportWriter "ReportWriter")
         * and returns null. The reason for this behavior is to disallow the usage of AString
         * within (system) methods that create sub sequences. This would be in contrast to the
         * design goal of AString.
         *
         * @param beginIndex    The start of the sequence (not used)
         * @param endIndex      The length of the sequence (not used)
         *
         * @return  null (!).
         ******************************************************************************************/
        @Override public CharSequence subSequence(int beginIndex, int endIndex)
        {
            // this function should never be used
            com.aworx.lib.ALIB_DBG.ERROR( "subSequence() is not supported" );
            return null;
        }


    // #############################################################################################
    // protected internals
    // #############################################################################################

        /** ****************************************************************************************
         * Protected method that resizes a region into the Buffer.
         * The region contents is undefined.
         *
         * @param regionStart   The start of the region to insert. If this is out of the string
         *                      bounds (hence less than 0 or greater then #length), nothing is done.
         * @param regionLength  The current length of the region.
         * @param newLength     The desired length of the region.
         * @return \c true, if the parameters were OK and the region was resized,
         *         \c false otherwise.
         ******************************************************************************************/
        protected  boolean  resizeRegion( int regionStart, int regionLength, int newLength )
        {
            // check
            if (    regionStart  < 0
                ||  regionStart + regionLength > length
                ||  regionLength < 0
                ||  newLength    < 0)
                return false;


            // flag us dirty (as we will be manipulated)
            hash= 0;

            int lenDiff= newLength - regionLength;

            // check buffer size
            if ( lenDiff > 0 )
                ensureRemainingCapacity( lenDiff );

            // move content
            if ( lenDiff != 0 )
            {
                System.arraycopy( buffer, regionStart + regionLength,
                                  buffer, regionStart + newLength,
                                  length - (regionStart + regionLength) );

                length+= lenDiff;
            }

            return true;
        }


} // class AString


