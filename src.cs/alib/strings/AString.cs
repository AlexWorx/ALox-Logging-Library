﻿// #################################################################################################
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

/** ************************************************************************************************
 *  This namespace of the A-Worx Library provides classes for character string operations
 *  (following \ref cs.aworx.lib "the principle design goals of the A-Worx Library").
 **************************************************************************************************/
namespace cs.aworx.lib.strings  {


/** ************************************************************************************************
 *  A mutable string, that provides public access to its internal buffer and fields.
 *  First of all, the existence of this class is motivated to reach a certain level of compatibility
 *  between source code that uses the
 *  \ref cs.aworx.lib "ALib" across different languages (currently Java, C# and C++) whose
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
 *  Nevertheless, method #Buffer will return a valid empty <em>char[]</em>
 *  (a static singleton). This has the advantage that in many situations the null-state is not
 *  needed to handled specially (those cases where the difference between a nulled and an empty
 *  string is irrelevant).
 *  Consequently, it makes a difference if an %AString is constructed using <em>AString()</em> or
 *  "AString(\"\").
 *  This allows to differentiate between 'nulled' AStrings and empty AStrings, which is quite handy
 *  in certain situations. An object that was filled already can be reset to represent null by
 *  either assigning a nulled AString, by invoking
 *  \ref SetBuffer "SetBuffer(0)" or by invoking #SetNull on the
 *  instance. See also methods #IsNull, #IsNotNull and #Capacity.
 *  The methods #Equals and #CompareTo allow \c null comparisons. e.g. an nulled %AString equals
 *  to another nulled AString but not to a zero length, not nulled AString.
 *
 *
 *   \anchor CS_ASTRING_NC
 *  <p>
 *  <b>Non-checking methods</b><p>
 *  In general, %AString methods are internally checking the provided parameters. For example,
 *  method #_( AString src, int regionStart, int regionLength = int.MaxValue) is
 *  adjusting the provided region information to fit to the size of the provided %AString.<br>
 *  Chances are high, that the code invoking this method "knows" about the correctness of
 *  the region. In this case, the checks are redundant.
 *
 *  For avoiding unnecessary checks, various methods are provided by %AString that omit such checks.
 *  These methods share the same name as the standard one, with the suffix "_NC" appended (NC
 *  stands for "no checks").
 *
 *  In the sample above, if the calling code was sure about the parameters \p{regionStart} and
 *  \p{regionLength} being in the bounds of \p{src}, method
 *  \ref _NC( AString src, int regionStart, int regionLength ) can be used.
 *
 *  \attention The following rules apply to all methods which suffixed by <em>_NC</em>:
 *  - Parameters are not checked for being null.
 *  - Index, size, length, region start/end and other parameters are not checked to be correct
 *  - If parameters are incorrect, the result of the methods is undefined
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
 **************************************************************************************************/
public class AString
{
    // #############################################################################################
    // protected fields
    // #############################################################################################

        /// The Buffer array. This may but should not be accessed directly. In case of
        /// external modifications the field hash has to be set to dirty (0).
        protected     char[]                buffer                              =CString.NullBuffer;

        /// The actual length of the string stored in the Buffer. In case of external
        /// modifications the field hash has to be set to dirty (0).
        protected     int                   length                              =0;

        /// The tab reference position. This is set when #NewLine is invoked.
        protected     int                   tabReference                        =0;

        /// A marker for the start of the actual field.
        protected     int                   fieldReference                      =0;

        /// The hash value. Has to be set dirty (0) whenever String is changed from
        /// outside!.
        protected     int                   hash                                =0;


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
            if ( size > 0 )
                SetBuffer( size );
        }

        /** ****************************************************************************************
         * Constructor copying Substring another AString.
         *
         * @param src            The source AString to copy from.
         * @param regionStart    The start index in ms to append. Defaults to 0.
         * @param regionLength   The maximum length of the substring in ms to append.
         *                       Defaults to int.MaxValue.
         ******************************************************************************************/
        public AString( AString src, int regionStart= 0, int regionLength= int.MaxValue )
        {
            _( src, regionStart, regionLength );
        }

        /** ****************************************************************************************
         * Constructor copying a \ref cs.aworx.lib.strings.Substring "Substring".
         *
         * @param src  The source Substring to copy from.
         ******************************************************************************************/
        public AString( Substring src )
        {
            _( src );
        }

        /** ****************************************************************************************
         * Constructor copying a region of a String.
         *
         * @param src            The source String to copy from.
         * @param regionStart    The start index in s to append. Defaults to 0.
         * @param regionLength   The maximum length of the substring in s to append.
         *                       Defaults to int.MaxValue.
         ******************************************************************************************/
        public AString( String src, int regionStart= 0, int regionLength= int.MaxValue)
        {
            _( src, regionStart, regionLength );
        }

        /** ****************************************************************************************
         * Constructor copying a region of a StringBuilder.
         *
         * @param src            The source StringBuilder to copy.
         * @param regionStart    The start index in ms to append. Defaults to 0.
         * @param regionLength   The maximum length of the substring in ms to append.
         *                       Defaults to int.MaxValue.
         ******************************************************************************************/
        public AString( StringBuilder src, int regionStart= 0, int regionLength= int.MaxValue )
        {
            _( src, regionStart, regionLength );
        }
    /** @} */

    /** ############################################################################################
     * @name Memory allocation and buffer access
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         *  The internal buffer character array. This may, but should not be accessed directly.
         *  In case of external modifications be sure to adjust the length of this AString using
         *  SetLength.
         *
         * @return The internal buffer array.
         ******************************************************************************************/
        public    char[]        Buffer()                    { return buffer;    }

        /** ****************************************************************************************
         *  Resizes the internal buffer to meet exactly the given size.
         *
         *  The following rules apply:
         *  - The string represented by this instance is copied to the new buffer.
         *    If this is larger than the new buffer size, the string is cut at the end to fit.
         *  - If the desired new size is 0, then the currently allocated buffer will be released.
         *    In this case method #Buffer will  still return an empty constant character array
         *    (using an internal singleton) but method #IsNull will return true.
         *
         *  \note Any methods of this class that extend the length of the string represented, will
         *        invoke this method if the current buffer size is not sufficient.
         *        If a future string length of an %AString is predictable, then it is advisable
         *        to allocate such size upfront to avoid recurring allocations.
         *
         * @param newCapacity   The new capacity of the internal buffer.
         ******************************************************************************************/
        public    void         SetBuffer( int newCapacity )
        {
            // default parameter -1: -> set to current length
            if ( newCapacity == -1 )
                newCapacity= length;

            // check
            if ( buffer.Length == newCapacity )
                return;

            // As a side effect, flag has value as dirty
            hash= 0;

            // set uninitialized
            if ( newCapacity == 0 )
            {
                buffer=  CString.NullBuffer;
                length=  0;
                return;
            }

            // create new Buffer and copy data
            char[] newBuffer=    new char[ newCapacity ];
            if ( length > 0 )
            {
                // we might have been cut with this operation
                if ( length > newCapacity  )
                    length= newCapacity;
                Array.Copy( buffer, newBuffer, length );
            }

            // that's it
            buffer= newBuffer;
        }

        /** ****************************************************************************************
         * Ensures that the capacity of the internal buffer meets or exceeds the actual length
         * plus the given growth value.
         *
         * @param spaceNeeded  The desired growth of the length of the string represented by this.
         ******************************************************************************************/
        public void     EnsureRemainingCapacity( int spaceNeeded )
        {
            int bufferLength= buffer.Length;

            // big enough?
            if ( bufferLength >= length + spaceNeeded )
                return;

            // first allocation? Go with given growth as size
            if (bufferLength == 0 )
            {
                SetBuffer( spaceNeeded > 16 ? spaceNeeded : 16 );
                return;
            }

            // calc new size: in general grow by 50%
            int newSize= bufferLength + (bufferLength / 2);
            if ( newSize < length + spaceNeeded )
                newSize+= spaceNeeded;

            if ( newSize < 16 )
                newSize= 16;

            SetBuffer( newSize );
        }

        /** ****************************************************************************************
         * Returns the current size of the internal buffer.
         *
         * @return The size of the allocated buffer.
         ******************************************************************************************/
        public    int         Capacity()          { return buffer.Length;    }

        /** ****************************************************************************************
         * Invokes \ref SetBuffer "SetBuffer(0)".
         * @return true if no buffer is allocated.
         ******************************************************************************************/
        public    void        SetNull()           { SetBuffer( 0 ); }

        /** ****************************************************************************************
         * Returns true if no buffer space is allocated, false otherwise.
         * This might be the case, if constructed  with <em>AString()</em> or <em>AString(0)</em>,
         * by invoking
         * \ref SetBuffer "SetBuffer(0)" or #SetNull.
         *
         * @return true if no buffer is allocated.
         ******************************************************************************************/
        public    bool        IsNull()            { return buffer.Length == 0; }

        /** ****************************************************************************************
         * Returns false if no buffer space is allocated, true otherwise.
         * This might be the case, if constructed  with <em>AString()</em> or <em>AString(0)</em>,
         * by invoking
         * \ref SetBuffer "SetBuffer(0)" or #SetNull.
         *
         * @return true if no buffer is allocated.
         ******************************************************************************************/
        public    bool        IsNotNull()         { return buffer.Length != 0; }

        /** ****************************************************************************************
         *  Set the actual length of the stored string. The string can only be shortened with this
         *  method.
         *  To change the internal allocation size, see #SetBuffer.
         *
         * @param newLength   The new length of the AString. Must be smaller than the
         *                    current length.
         *
         * @return The new length of the string represented by this. ESCString.
         ******************************************************************************************/
        public    int         SetLength( int newLength )
        {
            ALIB_DBG.ASSERT_WARNING( newLength <= length, "Increase requested" );

            if ( newLength < length )
            {
                length= newLength;
                hash=   0;
            }

            return length;
        }

        /** ****************************************************************************************
         *  Set the actual length of the stored string. The string can only be shortened with this
         *  method.
         *  \attention Non checking variant of original method.
         *             See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param newLength    The new length of the %AString. Must be between 0 and the current
         *                     length.
         ******************************************************************************************/
        public    void        SetLength_NC( int newLength )
        {
            ALIB_DBG.ASSERT_ERROR( newLength >= 0 && newLength <= length, "Index out of range" );
            length= newLength;
            hash=   0;
        }

        /** ****************************************************************************************
         *  Returns the actual length of this %AString. This number is smaller or equals
         *  the number returned by #Capacity.
         *
         * @return The length of the string represented by this.
         ******************************************************************************************/
        public    int         Length()            { return length;    }

        /** ****************************************************************************************
         *  Returns true if the actual length equals zero.
         * @return true if the actual length equals zero.
         ******************************************************************************************/
        public    bool        IsEmpty()           { return length == 0; }

        /** ****************************************************************************************
         *  Returns true if the actual length does not equal zero.
         * @return true if the actual length does not equal zero.
         ******************************************************************************************/
        public    bool        IsNotEmpty()        { return length != 0; }

    /** @} */


    /** ############################################################################################
     * @name Insert and Delete
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         *  Clear the Buffer. Same as #Delete (0, Length()) but without internal region checks.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString         Clear()
        {
            hash= length= tabReference= fieldReference= 0;
            return this;
        }

        /** ****************************************************************************************
         * Clear the Buffer. Same as #Clear(), really just a synonym to allow short code in
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
         * Inserts a portion of the given char[] at a given position.
         * If the position is not between 0 and the length of the target, nothing is inserted.
         *
         * \attention
         *  Parameters \p{cStart} and \p{cLength} are not checked to match the size of \p{src}.
         *
         * \note
         *   To insert a string with replacing a different one at the same time, use
         *   \ref ReplaceSubstring "ReplaceSubstring(src, pos, regionLength)".
         *
         * @param  src      The <em>char[]</em> to insert characters from.
         * @param  cStart   The start of the substring in \p{src} to insert.
         * @param  cLength  The length of the substring in \p{src} to insert.
         * @param  pos      The position in this object insert the portion of \p{src}.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString InsertAt( char[]  src, int cStart, int cLength, int pos )
        {
            if ( !resizeRegion( pos, 0, cLength ) )
                return this;

            Array.Copy( src, cStart, buffer, pos, cLength );

            return this;
        }

        /** ****************************************************************************************
         * Inserts a Substring .
         * If the position is not between 0 and the length of the target, nothing is inserted.
         *
         * \note
         *   To insert a string with replacing a different one at the same time, use
         *   one of the overloaded methods #ReplaceSubstring.
         *
         * @param  src      The <em>char[]</em> to insert characters from.
         * @param  pos      The position in this object insert the portion of \p{src}.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString InsertAt( AString  src, int pos )
        {

            return src != null ? InsertAt( src.buffer, 0, src.length, pos )
                               : this;
        }

        /** ****************************************************************************************
         * Inserts a Substring at a given position.
         * If the position is not between 0 and the length of the target, nothing is inserted.
         *
         * \note
         *   To insert a string with replacing a different one at the same time, use
         *   one of the overloaded methods #ReplaceSubstring.
         *
         * @param  src      The <em>char[]</em> to insert characters from.
         * @param  pos      The position in this object insert the portion of \p{src}.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString InsertAt( Substring  src, int pos )
        {
            return src != null ? InsertAt( src.Buf, src.Start, src.Length(), pos )
                               : this;
        }

        /** ****************************************************************************************
         * Inserts a String at a given position.
         * If the position is not between 0 and the length of the target, nothing is inserted.
         *
         * \note
         *   To insert a string with replacing a different one at the same time, use
         *   one of the overloaded methods #ReplaceSubstring.
         *
         * @param  src      The <em>char[]</em> to insert characters from.
         * @param  pos      The position in this object insert the portion of \p{src}.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString InsertAt( String  src, int pos )
        {
            if ( src != null )
            {
                int srcLength= src.Length;
                if ( !resizeRegion( pos, 0, srcLength ) )
                    return this;

                src.CopyTo( 0, buffer, pos, srcLength );
            }
            return this;
        }

        /** ****************************************************************************************
         * Inserts a StringBuilder at a given position.
         * If the position is not between 0 and the length of the target, nothing is inserted.
         *
         * \note
         *   To insert a string with replacing a different one at the same time, use
         *   one of the overloaded methods #ReplaceSubstring.
         *
         * @param  src      The <em>char[]</em> to insert characters from.
         * @param  pos      The position in this object insert the portion of \p{src}.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString InsertAt( StringBuilder  src, int pos )
        {
            if ( src != null )
            {
                int srcLength= src.Length;
                if ( !resizeRegion( pos, 0, srcLength ) )
                    return this;

                src.CopyTo( 0, buffer, pos, srcLength );
            }
            return this;
        }

        /** ****************************************************************************************
         * Inserts the given character n-times at a given position.
         * If the given position is out of range, nothing is inserted.
         *
         * @param c     The character to insert \p{qty} times.
         * @param qty   The quantity of characters to insert.
         * @param pos   The index in this object where \p{c} is inserted \p{qty} times.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString InsertChars( char c, int qty, int pos )
        {
            if( !resizeRegion(  pos, 0, qty ) )
                return this;

            int regionEnd= pos + qty;
            for ( int i= pos ; i < regionEnd ; i++ )
                buffer[i]= c;

            return this;
        }

        /** ****************************************************************************************
         * Inserts the given character n-times at the end of this string (appends).
         *
         * @param c      The character to append.
         * @param qty    The quantity of characters to append.
         *
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString InsertChars( char c, int qty )
        {
            if ( qty > 0 )
            {
                // flag us dirty (as we will be manipulated)
                hash= 0;

                // big enough?
                if ( buffer.Length < length + qty )
                    EnsureRemainingCapacity( qty );

                // add characters
                for ( int i= 0; i< qty; i++ )
                    buffer[length++]= c;
            }
            // return me for concatenated operations
            return this;
        }



        /** ****************************************************************************************
         * Replaces a region in this object by a portion of a character array.
         * If the region does not fit to this object, then nothing is done.
         *
         * \attention
         *  Parameters \p{cStart} and \p{cLength} are not checked to match the size of \p{src}.
         *
         * @param src           The <em>char[]</em> to insert characters from.
         * @param cStart        The start of the substring in \p{src} to insert.
         * @param cLength       The length of the substring in \p{src} to insert.
         * @param regionStart   The start of the region.
         * @param regionLength  The length of the region.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString  ReplaceSubstring( char[]  src, int cStart, int cLength, int regionStart, int regionLength )
        {
            if ( !resizeRegion( regionStart, regionLength, cLength ) )
                return this;

            Array.Copy( src,  cStart,    buffer, regionStart,    cLength );
            return this;
        }

        /** ****************************************************************************************
         * Replaces a region in this object by a given AString.
         * If the region does not fit to this object, then nothing is done.
         *
         * @param src             The replacement string.
         * @param regionStart     The start of the region.
         * @param regionLength    The length of the region.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString  ReplaceSubstring( AString src, int regionStart, int regionLength )
        {
            return src != null ? ReplaceSubstring( src.buffer, 0, src.length, regionStart, regionLength )
                               : this;
        }

        /** ****************************************************************************************
         * Replaces a region in this object by a given Substring.
         * If the region does not fit to this object, then nothing is done.
         *
         * @param src             The replacement string.
         * @param regionStart     The start of the region.
         * @param regionLength    The length of the region.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString  ReplaceSubstring( Substring src, int regionStart, int regionLength )
        {
            return src != null ? ReplaceSubstring( src.Buf, src.Start, src.Length(), regionStart, regionLength )
                               : this;
        }

        /** ****************************************************************************************
         * Replaces a region in this object by a given string.
         * If the region does not fit to this object, then nothing is done.
         *
         * @param src             The replacement string.
         * @param regionStart     The start of the region.
         * @param regionLength    The length of the region.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString  ReplaceSubstring( String src, int regionStart, int regionLength )
        {
            if ( src != null )
            {
                int srcLength= src.Length;
                if ( !resizeRegion( regionStart, regionLength, srcLength ) )
                    return this;

                src.CopyTo( 0, buffer, regionStart, srcLength );
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
         *   \ref ReplaceSubstring(String,int,int) "ReplaceSubstring( "" + c, regionStart, regionLength)".
         *
         * @param c               The character to set in the region.
         * @param regionStart     The start of the region
         * @param regionLength    The length of the region
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString ReplaceRegion( char c, int regionStart, int regionLength )
        {
            if ( !CString.AdjustRegion( length, ref regionStart, ref regionLength ) )
            {
                int regionEnd= regionStart + regionLength;
                for ( int i= regionStart ; i < regionEnd ; i++ )
                    buffer[i]= c;
            }

            return this;
        }

        /** ****************************************************************************************
         *  Cuts out a region from the Buffer.
         *  A range check is performed and the region is cut to fit to the string.
         * \note See also methods #Clear, #DeleteStart, #DeleteStart_NC, #DeleteEnd
         *       and #DeleteEnd_NC.
         *
         * @param regionStart    The start of the region to delete.
         * @param regionLength   The length of the region to delete. Defaults to int.MaxValue
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public    AString     Delete( int regionStart, int regionLength= int.MaxValue )
        {
            // adjust range, if empty do nothing
            if ( CString.AdjustRegion( length, ref regionStart, ref regionLength ) )
                return this;

            int regionEnd= regionStart + regionLength;
            if ( regionEnd >= length )
            {
                length=    regionStart;
                return this;
            }

            Array.Copy( buffer, regionEnd, buffer, regionStart, length - regionEnd  );
            length-= regionLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         *  Cuts out a region from the Buffer.
         * \attention Non checking variant of original method.
         *            See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *            Like with method #Delete, it is allowed that the sum of parameters
         *            \p{regionStart} and \p{regionLength} is longer than the length of this %AString.
         *            In this case, this string is cut starting from index \p{regionStart}.
         *
         * @param regionStart  The start of the region to delete.
         * @param regionLength The length of the region to delete.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public    AString     Delete_NC( int regionStart, int regionLength )
        {
            ALIB_DBG.ASSERT_ERROR(     regionStart  >= 0
                                    &&  regionStart  <= length
                                    &&  regionLength >= 0,
                                    "Parameter assertion" );

            int regionEnd= regionStart + regionLength;
            if ( regionEnd >= length )
            {
                length=    regionStart;
                return this;
            }

            Array.Copy( buffer, regionEnd, buffer, regionStart, length - regionEnd  );
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
        public AString    DeleteStart( int regionLength  )
        {
            if ( regionLength <= 0 )
                return this;
            if ( regionLength >= length )
                return Clear();

            return DeleteStart_NC( regionLength );
        }

        /** ****************************************************************************************
         *  Deletes the given number of characters from the start of the string.
         * \attention Non checking variant of original method.
         *            See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *
         * @param regionLength  The length of the region at the start to delete.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString     DeleteStart_NC( int regionLength  )
        {
            ALIB_DBG.ASSERT_ERROR(  regionLength >=0 && regionLength <= length, "Region length out of range" );
            Array.Copy( buffer, regionLength, buffer, 0, length - regionLength  );
            length-= regionLength;
            return this;
        }

        /** ****************************************************************************************
         *  Deletes the given number of characters from the end of the string.
         *  The given region length is checked to be between 0 and length.
         * \attention Non checking variant of original method.
         *            See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *
         * @param regionLength  The length of the region at the end to delete.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString    DeleteEnd( int regionLength  )
        {
            if ( regionLength <= 0 )
                return this;
            if ( regionLength >= length )
                return Clear();

            length-= regionLength;
            return this;
        }

        /** ****************************************************************************************
         *  Deletes the given number of characters from the end of the string.
         * \attention Non checking variant of original method.
         *            See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *
         * @param regionLength  The length of the region at the end to delete.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString       DeleteEnd_NC( int regionLength  )
        {
            ALIB_DBG.ASSERT_ERROR(  regionLength >=0 && regionLength <= length, "Region length out of range" );
            length-= regionLength;
            return this;
        }


        /** ****************************************************************************************
         * All characters defined in given set are removed at the beginning and at the end of this
         * AString.
         *
         * See method \ref #TrimAt to remove whitespaces anywhere in the string.
         *
         * @param trimChars   The set of characters to be omitted.
         *                    Defaults to null which causes this method to use
         *                    \ref CString.DefaultWhitespaces.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString Trim( char[] trimChars= null )
        {
            if (length == 0 )
                return this;

            if ( trimChars == null )
                trimChars= CString.DefaultWhitespaces;

            length=  CString.LastIndexOfAny    ( buffer, 0, length, trimChars, Inclusion.Exclude ) + 1;
            int idx= CString.IndexOfAnyInRegion( buffer, 0, length, trimChars, Inclusion.Exclude );
            if ( idx > 0 )
                Delete_NC( 0, idx );

            return this;
        }

        /** ****************************************************************************************
         * All characters defined in given set at, left of and right of the given index
         * are removed from the string.<br>
         * The method returns index of the first character of those characters that were behind the
         * trimmed region. With legal \p{index} given, this value can only be smaller or equal to
         * \p{index}. If \p{index} is out of bounds, the length of the string is returned.
         *
         * @param idx         The index to perform the trim operation at. Has to be between zero
         *                    and <em>Length() -1</em>.
         * @param trimChars   Pointer to a zero terminated set of characters to be omitted.
         *                    Defaults to \ref CString.DefaultWhitespaces.
         * @return  The index of the first character of those characters that were behind the
         *          trimmed region.
         ******************************************************************************************/
        public int  TrimAt( int idx, char[] trimChars= null )
        {
            if ( idx < 0 )
                 return 0;
            if ( idx >= length )
                 return length;

            if ( trimChars == null )
                trimChars= CString.DefaultWhitespaces;

            int regionStart=    CString.LastIndexOfAny    ( buffer, 0, idx + 1,          trimChars, Inclusion.Exclude ) + 1;
            if (regionStart < 0 )
                regionStart= 0;
            int regionEnd=      CString.IndexOfAnyInRegion( buffer, idx, length - idx, trimChars, Inclusion.Exclude );
            if (regionEnd < 0 )
                regionEnd= length;

            int regionLength= regionEnd - regionStart;
            if ( regionLength > 0 )
                Delete_NC( regionStart, regionLength );
            return regionStart;
        }

        /** ****************************************************************************************
         * All characters defined in given set are removed at the beginning of this string.
         *
         * \see Method #TrimAt to remove whitespaces at arbitrary places in the string.
         *
         * @param trimChars   The set of characters to be omitted.
         *                    Defaults to \ref CString.DefaultWhitespaces.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString TrimStart( char[] trimChars= null )
        {
            if ( trimChars == null )
                trimChars= CString.DefaultWhitespaces;
            if (length == 0 || trimChars.Length == 0 )
                return this;

            int idx= IndexOfAny( trimChars, Inclusion.Exclude);
            if ( idx > 0 )
                Delete( 0, idx );
            else if ( idx < 0 )
                length= 0;

            return this;
        }

        /** ****************************************************************************************
         * All characters defined in given set are removed at the end of this string.
         *
         * \see Method #TrimAt to remove whitespaces at arbitrary places in the string.
         *
         * @param trimChars   The set of characters to be omitted.
         *                    Defaults to \ref CString.DefaultWhitespaces.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString TrimEnd( char[] trimChars= null )
        {
            if ( trimChars == null )
                trimChars= CString.DefaultWhitespaces;
            if( length > 0 &&  trimChars.Length > 0 )
                length= LastIndexOfAny( trimChars, Inclusion.Exclude, length - 1 ) + 1;
            return this;
        }


    /** ############################################################################################
     * @name Basic formatting
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Appends platform specific new line character(s). ( "\\r\\n", "\\r", etc.). The
         * new length of the string is recorded as the reference position for #Tab.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString NewLine()
        {
            // save tab reference and append new line characters
            tabReference= length + CString.NewLineChars.Length;
            return _( CString.NewLineChars );
        }

        /** ****************************************************************************************
         * Go to the next tab stop by filling in pad characters repeatedly. The tab position is
         * relative the start of the current line within the string (if no calls to #NewLine
         * where performed, yet, this is always the start of the string).
         *
         * \note While any append operation is allowed, manipulations like
         *       #Delete or #InsertAt will not correct the internal tab reference position to match
         *       the index of the then current start of the last line in this string.
         *
         * @param tabSize  The tab positions are multiples of this parameter.
         * @param minPad   (Optional) The minimum pad characters to add. Defaults to 1.
         *
         * @param tabChar  (Optional) The character to insert to reach the tab position.
         *                         Defaults to ' ' (space).
         * @return    \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString Tab( int tabSize, int minPad= 1, char tabChar= ' ')
        {
            int qtyChars= minPad > 0 ? minPad : 0;
            if ( tabSize > 1 )
                qtyChars+= (tabSize - ( (length + qtyChars - tabReference) % tabSize ) ) % tabSize;

            return ( qtyChars <= 0 ) ?  this
                                     :  InsertChars( tabChar, qtyChars );
        }

        /** ****************************************************************************************
         * If invoked without parameters, the start of a field is marked at the current end of
         * the string. Otherwise the end of a field is set and the contents between the field start
         * marker and the current end of the string is aligned within the field using the given pad
         * character.
         * Note: To implement nested fields, the outer fields have to be set by providing the start
         * marker by using the parameter fieldStart. Hence, only the starting points of the most
         * inner fields can be set using this method without parameters.
         *
         *
         * @param size        The field size in relation to the starting index of the field,
         *                            defined either by using Field() prior to this invocation or by
         *                            providing the parameter fieldStart.
         *                            The field gets filled with the given pad character to meet the
         *                            size while the content gets aligned left, right or centered.
         *                            If the content exceeds the size, then no alignment takes
         *                            place.
         * @param alignment   The alignment of the contents within the field.
         *                            Defaults to Alignment.Right.
         *                            Other options are Alignment.Left and Alignment.Center.
         *
         * @param padChar     The character used to fill the field up to its size.
         *                            Defaults to ' ' (space).
         * @param fieldStart  This parameter, if given, overwrites the start index of the
         *                            field. The invocation of Field can be omitted, when this
         *                            value is explicitly provided.
         *                            Defaults to int.MaxValue.

         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString Field( int size=-1, Alignment alignment= Alignment.Right, char padChar= ' ', int fieldStart= int.MaxValue )
        {
            // if size is -1, this is just a field start marker invocation
            if ( size < 0 )
            {
                fieldReference= length;
                return this;
            }

            // if no field start is given, use the saved one (default behavior)
                if ( fieldStart == int.MaxValue )
                fieldStart=        fieldReference;

            // check pad size
            int padSize=    size - (length - fieldStart);
            if (padSize <= 0 )
                return this;

            // align left
            if ( alignment == Alignment.Left )
            {
                InsertChars( padChar, padSize );
                return this;
            }

            // align Right
            if ( alignment == Alignment.Right )
            {
                InsertChars( padChar, padSize, fieldStart );
                return this;
            }

            // align Center
            InsertChars( padChar, padSize >> 1, fieldStart );
            InsertChars( padChar, padSize - ( padSize >> 1 ) );
            return this;
        }

    /** @} */


    /** ############################################################################################
     * @name Appending characters and strings
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         *  Appends a region of a character array.
         * \attention Non checking variant of original method.
         *            See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *
         * @param src            The character array containing the region to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The length of the region in src to append.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( char[] src, int regionStart, int regionLength )
        {
            // big enough?
            if ( buffer.Length < length + regionLength )
                EnsureRemainingCapacity( regionLength );

            // copy
            Array.Copy( src, regionStart, buffer, length, regionLength );
            length+= regionLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Appends an object by invoking \c ToString on it.
         *
         * @param src    The AString compatible type to append
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( Object src  )
        {
            // check null argument
            if ( src == null )
                return this;

            // cast type
            if ( src is AString   ) return _( (AString)   src );
            if ( src is Substring ) return _( (Substring) src );
            if ( src is String    ) return _( (String)    src );
            if ( src is char[]    ) return _( (char[])    src );

                                    return _( src.ToString()  );
        }

        /** ****************************************************************************************
         * Appends an object by invoking \c ToString on it.
         * \attention Non checking variant of original method.
         *            See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *
         * @param src    The AString compatible type to append
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( Object src  )
        {
            // check null argument
            if ( src == null )
                return this;

            // cast type
            if ( src is AString   ) return _NC( (AString)   src );
            if ( src is Substring ) return _NC( (Substring) src );
            if ( src is String    ) return _NC( (String)    src );
            if ( src is char[]    ) return _NC( (char[])    src );

                                    return _NC( src.ToString()  );
        }

        /** ****************************************************************************************
         *  Append the given AString.
         *
         * @param src  The AString to append.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( AString src )
        {
            // check null argument
            if ( src == null )
                return this;

            int srcLength= src.length;

            if ( src.length == 0 )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.Length == 0 )
                    SetBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.Length < length + srcLength )
                EnsureRemainingCapacity( srcLength );

            // copy
            Array.Copy( src.buffer, 0, buffer, length, srcLength );
            length+= srcLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         *  Append a region of an AString.
         *
         * @param src            The AString to append.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to int.MaxValue.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( AString src, int regionStart, int regionLength= int.MaxValue )
        {
            // check null argument
            if ( src == null )
                return this;

            // adjust range, if empty do nothing
            if ( CString.AdjustRegion( src.length, ref regionStart, ref regionLength ) )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.Length == 0 )
                    SetBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.Length < length + regionLength )
                EnsureRemainingCapacity( regionLength );

            // copy
            Array.Copy( src.buffer, regionStart, buffer, length, regionLength );
            length+= regionLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         *  Append the given AString.
         *  \attention Non checking variant of original method.
         *             See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param src  The AString to append.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( AString src )
        {
            int srcLength= src.length;

            // big enough?
            if ( buffer.Length < length + srcLength )
                EnsureRemainingCapacity( srcLength );

            // copy
            Array.Copy( src.buffer, 0, buffer, length, srcLength );
            length+= srcLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         *  Append a region of an AString.
         *  \attention Non checking variant of original method.
         *             See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param src            The AString to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The maximum length of the region in src to append.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( AString src, int regionStart, int regionLength )
        {
            // big enough?
            if ( buffer.Length < length + regionLength )
                EnsureRemainingCapacity( regionLength );

            // copy
            Array.Copy( src.buffer, regionStart, buffer, length, regionLength );
            length+= regionLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Append the given char[].
         *
         * @param src     The source array.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( char[] src )
        {
            // check null argument
            if ( src == null )
                return this;

            int srcLength= src.Length;
            if ( srcLength == 0 )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.Length == 0 )
                    SetBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.Length < length + srcLength )
                EnsureRemainingCapacity( srcLength );

            // copy
            Array.Copy( src, 0, buffer, length, srcLength );
            length+= srcLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Append a region of a char[].
         *
         * @param src            The source array.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to int.MaxValue.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( char[] src, int regionStart, int regionLength= int.MaxValue )
        {
            // check null argument
            if ( src == null )
                return this;

            // adjust range, if empty do nothing
            if ( CString.AdjustRegion( src.Length, ref regionStart, ref regionLength ) )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.Length == 0 )
                    SetBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.Length < length + regionLength )
                EnsureRemainingCapacity( regionLength );

            // copy
            Array.Copy( src, regionStart, buffer, length, regionLength );
            length+= regionLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         *  Append a Substring.
         *
         * @param substring   The source array.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( Substring substring )
        {
            // check null argument
            if ( substring == null )
                return this;

            return _( substring.Buf, substring.Start, substring.Length() );
        }

        /** ****************************************************************************************
         *  Append a Substring.
         *  \attention Non checking variant of original method.
         *             See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param src   The source Substring.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( Substring src )
        {
            return _NC( src.Buf, src.Start, src.Length() );
        }

        /** ****************************************************************************************
         * Append a String.
         *
         * @param src   The String to append.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( String src )
        {
            // check null argument
            if ( src == null )
                return this;

            int srcLength= src.Length;
            if ( srcLength == 0 )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.Length == 0 )
                    SetBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.Length < length + srcLength )
                EnsureRemainingCapacity(  srcLength );

            // copy and adjust my length
            src.CopyTo( 0, buffer, length, srcLength );
            length+= srcLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Append a region of a String.
         *
         * @param src            The String to append.
         * @param regionStart    The start of the region in src to append. Defaults to 0.
         * @param regionLength   The maximum length of the region in src to append.
         *                       Defaults to int.MaxValue
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( String src, int regionStart, int regionLength=int.MaxValue )
        {
            // check null argument
            if ( src == null )
                return this;

            if ( CString.AdjustRegion( src.Length, ref regionStart, ref regionLength ) )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.Length == 0 )
                    SetBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.Length < length + regionLength )
                EnsureRemainingCapacity( regionLength );

            // copy and adjust my length
            src.CopyTo( regionStart, buffer, length, regionLength );
            length+= regionLength;

            // return me for concatenated operations
            return this;
        }


        /** ****************************************************************************************
         *  Append a String.
         *  \attention Non checking variant of original method.
         *             See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param src            The String to append.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( String src)
        {
            int srcLength= src.Length;

            // big enough?
            if ( buffer.Length < length + srcLength )
                EnsureRemainingCapacity(  srcLength );

            // copy and adjust my length
            src.CopyTo( 0, buffer, length, srcLength );
            length+= srcLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         *  Append a region of a String.
         *  \attention Non checking variant of original method.
         *             See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *             variants.
         *
         * @param src            The String to append.
         * @param regionStart    The start of the region in src to append.
         * @param regionLength   The maximum length of the region in src to append.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _NC( String src, int regionStart, int regionLength )
        {
            // big enough?
            if ( buffer.Length < length + regionLength )
                EnsureRemainingCapacity( regionLength );

            // copy and adjust my length
            src.CopyTo( regionStart, buffer, length, regionLength );
            length+= regionLength;

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Append the given StringBuilder.
         *
         * @param src          The StringBuilder to append.
         * @return    \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( StringBuilder src )
        {
            // check null argument
            if ( src == null )
                return this;
            int srcLength= src.Length;
            if ( srcLength == 0 )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.Length == 0 )
                    SetBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.Length < length + srcLength )
                EnsureRemainingCapacity( srcLength );

            // copy and adjust my length
            #if !ALOX_WP71
                // standard versions
                src.CopyTo( 0, buffer, length, srcLength );
                length+= srcLength;
            #else
                // Windows Phone 7.1 version (StringBuilder.CopyTo() not available)
                for (int i= 0; i < length; i++ )
                    Buffer[ Length++ ]= sb[ startIdx + i ];
            #endif

            // return me for concatenated operations
            return this;
        }

        /** ****************************************************************************************
         * Append a region of a StringBuilder.
         * @param src          The StringBuilder to append.
         * @param regionStart  The start of the region in src to append.
         * @param regionLength The maximum length of the region in src to append.
         *                     Defaults to int.MaxValue.
         * @return    \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( StringBuilder src, int regionStart, int regionLength= int.MaxValue )
        {
            // check null argument
            if ( src == null )
                return this;

            if ( CString.AdjustRegion( src.Length, ref regionStart, ref regionLength ) )
            {
                // special treatment if currently nothing is allocated
                // we allocate, which means, we are not a nulled object anymore!
                if ( buffer.Length == 0 )
                    SetBuffer( 16 );
                return this;
            }

            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.Length < length + regionLength )
                EnsureRemainingCapacity( regionLength );

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


        /** ****************************************************************************************
         * Append the given character.
         * @param c    The character to append.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( char c )
        {
            // flag us dirty (as we will be manipulated)
            hash= 0;

            // big enough?
            if ( buffer.Length < length + 1 )
                EnsureRemainingCapacity( 1 );

            buffer[ length++ ]= c;

            // return me for concatenated operations
            return this;
        }

    /** @} */


    /** ############################################################################################
     * @name Character access
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * The C# indexer allows array type access. This is implemented here including
         * a range check. If this fails, the get part will return '\0', the set part will do
         * nothing.
         * \note Access to the characters without index check is provided with method #CharAt_NC.
         *
         * @param idx  The index of the character to read.
         * @return The character at the given index, or '\0' if index out of range.
         ******************************************************************************************/
        public char this[int idx]
        {
            get
            {
                ALIB_DBG.ASSERT_ERROR( idx >= 0 && idx <  length, "Index out of bounds" );
                return  ( idx >= 0 && idx <  length ) ?  buffer[idx]
                                                      : '\0';
            }
            set
            {
                ALIB_DBG.ASSERT_ERROR( idx >= 0 && idx <  length, "Index out of bounds" );
                if      ( idx >= 0 && idx <  length )
                            buffer[idx]= value;
            }
        }

        /** ****************************************************************************************
         * Retrieves the character at the given index. A range check is performed. If this fails,
         * '\0' is returned.
         *
         * @param idx  The index of the character to read.
         * @return The character at the given index, or '\0' if index out of range.
         ******************************************************************************************/
        public char        CharAt( int idx )
        {
            return  ( idx >= 0 && idx <  length ) ? buffer[idx]
                                                  : '\0' ;
        }

        /** ****************************************************************************************
         * Retrieves the character at the given index.
         * \attention Non checking variant of original method.
         *            See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *
         * @param idx  The index of the character to read.
         * @return The character at the given index.
         ******************************************************************************************/
        public char        CharAt_NC( int idx )
        {
            ALIB_DBG.ASSERT_ERROR(  idx >= 0 && idx < length, "Index out of range" );
            return  buffer[idx];
        }

        /** ****************************************************************************************
         * Sets the character at the given index.
         * A range check is performed. If this fails, nothing is done.
         *
         * @param idx  The index of the character to write.
         * @param c    The character to write.
         ******************************************************************************************/
        public void        SetCharAt( int idx, char c )
        {
            if  ( idx >= 0 && idx < length )
                buffer[idx]= c;
        }

        /** ****************************************************************************************
         * Sets the character at the given index.
         * \attention Non checking variant of original method.
         *            See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         *
         * @param idx  The index of the character to write.
         * @param c    The character to write.
         ******************************************************************************************/
        public void        SetCharAt_NC( int idx, char c )
        {
            ALIB_DBG.ASSERT_ERROR(  idx >= 0 && idx < length, "Index out of range" );
            buffer[idx]= c;
        }


        /** ****************************************************************************************
         * Retrieve the first character. In case of an empty string, '\0' is returned.
         * @return The first character in the AString.
         *         If this instance's length is zero,  '\0' is returned.
         ******************************************************************************************/
        public char        CharAtStart()
        {
            return length > 0 ?  buffer[0]
                              :  '\0';
        }

        /** ****************************************************************************************
         * Retrieve the first character.
         * \attention Non checking variant of original method.
         *            See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         * @return The first character in the AString.
         *         If this instance's length is zero,  '\0' is returned.
         ******************************************************************************************/
        public char        CharAtStart_NC()
        {
            ALIB_DBG.ASSERT_ERROR(  length > 0, "Empty AString" );
            return  buffer[0];
        }

        /** ****************************************************************************************
         * Retrieve the last character. In case of an empty string, '\0' is returned.
         * @return The last character in the AString.
         *         If this instance's length is zero,  '\0' is returned.
         ******************************************************************************************/
        public char        CharAtEnd()
        {
            return length > 0 ?  buffer[length - 1]
                              :  '\0';
        }

        /** ****************************************************************************************
         * Retrieve the first character.
         * \attention Non checking variant of original method.
         *            See \ref CS_ASTRING_NC "Non-checking methods" for <em>_NC</em> method
         *            variants.
         * @return The first character in the AString.
         *         If this instance's length is zero,  '\0' is returned.
         ******************************************************************************************/
        public char        CharAtEnd_NC()
        {
            ALIB_DBG.ASSERT_ERROR(  length > 0, "Empty AString" );
            return  buffer[length - 1];
        }

    /** @} */

    /** ############################################################################################
     * @name Comparison
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Compares a given region of a given string with a region of this instance. Regions that are
         * out of bounds get adjusted and then compared.
         *
         * @param needle             An object of type String that is compared to this.
         * @param sensitivity        Case sensitivity of the comparison.
         *                           Optional and defaults to Case.Sensitive.
         * @param needleRegionStart  The start of the substring within the given string that
         *                           is to be compared to this. Defaults to 0.
         * @param needleRegionLength The length of the substring within the given string
         *                           that is to be compared to this.
         *                           Defaults to Integer.MAX_VALUE.
         * @param regionStart        The start of the substring within this string that
         *                           is to be compared. Defaults    to 0.
         * @param regionLength       The length of the substring within this string that is
         *                           to be compared. Defaults to
         *                           Integer.MAX_VALUE.
         * @return
         *  -  0 if this and \p{needle} are \e nulled or if both have a length of 0 or if both
         *       share the same content
         *  - <0 if this is \e nulled and \p{needle} is not or if this is smaller than \p{needle}.
         *  - >0 if this is not \e nulled but \p{needle} is or if this is greater than \p{needle}.
         ******************************************************************************************/
        public int CompareTo(   String              needle,
                                Case                sensitivity         = Case.Sensitive,
                                int                 needleRegionStart   = 0,
                                int                 needleRegionLength  = int.MaxValue,
                                int                 regionStart         = 0,
                                int                 regionLength        = int.MaxValue    )
        {
            // check null argument
            if ( buffer.Length == 0   )     return  needle == null ? 0 : -1;
            if ( needle == null)     return  +1;

            // adjust source and compare regions
            int cmpLength= needle.Length;
            CString.AdjustRegion( cmpLength, ref needleRegionStart, ref needleRegionLength );
            CString.AdjustRegion(    length, ref              regionStart, ref              regionLength );

            return CString.CompareTo( needle, needleRegionStart, needleRegionLength,
                                      buffer,       regionStart,       regionLength,
                                      sensitivity );
        }

        /** ****************************************************************************************
         * Compares a given region of a given string with a region of this instance. Regions that are
         * out of bounds get adjusted and then compared.
         *
         * @param needle              An object of type AString that is compared to this.
         * @param sensitivity         Case sensitivity of the comparison.
         *                            Optional and defaults to Case.Sensitive.
         * @param needleRegionStart   The start of the substring within the given string that
         *                            is to be compared to this. Defaults to 0.
         * @param needleRegionLength  The length of the substring within the given string
         *                            that is to be compared to this.
         *                            Defaults to Integer.MAX_VALUE.
         * @param regionStart         The start of the substring within this string that
         *                            is to be compared. Defaults    to 0.
         * @param regionLength        The length of the substring within this string that is
         *                            to be compared. Defaults to
         *                            Integer.MAX_VALUE.
         * @return
         *  -  0 if this and \p{needle} are \e nulled or if both have a length of 0 or if both
         *       share the same content
         *  - <0 if this is \e nulled and \p{needle} is not or if this is smaller than \p{needle}.
         *  - >0 if this is not \e nulled but \p{needle} is or if this is greater than \p{needle}.
         ******************************************************************************************/
        public int CompareTo(   AString       needle,
                                Case          sensitivity           = Case.Sensitive,
                                int           needleRegionStart=    0,
                                int           needleRegionLength=   int.MaxValue,
                                int           regionStart=          0,
                                int           regionLength=         int.MaxValue    )
        {
            // check null argument
            if ( buffer.Length == 0   )     return  needle == null ? 0 : -1;
            if ( needle == null)     return  +1;

            // adjust source and compare regions
            int cmpLength= needle.length;
            CString.AdjustRegion( cmpLength, ref needleRegionStart, ref needleRegionLength );
            CString.AdjustRegion(    length, ref              regionStart, ref              regionLength );

            return CString.CompareTo( needle.Buffer(), needleRegionStart, needleRegionLength,
                                      buffer,                regionStart,       regionLength,
                                      sensitivity );
        }


        /** ****************************************************************************************
         * Compares a given region of a given string with a region of this instance. Regions that are
         * out of bounds get adjusted and then compared.
         *
         * @param needle              An object of type char[] that is compared to this.
         * @param sensitivity         Case sensitivity of the comparison.
         *                            Optional and defaults to Case.Sensitive.
         * @param needleRegionStart   The start of the substring within the given string that
         *                            is to be compared to this. Defaults to 0.
         * @param needleRegionLength  The length of the substring within the given string
         *                            that is to be compared to this.
         *                            Defaults to Integer.MAX_VALUE.
         * @param regionStart         The start of the substring within this string that
         *                            is to be compared. Defaults    to 0.
         * @param regionLength        The length of the substring within this string that is
         *                            to be compared. Defaults to
         *                            Integer.MAX_VALUE.
         * @return
         *  -  0 if this and \p{needle} are \e nulled or if both have a length of 0 or if both
         *       share the same content
         *  - <0 if this is \e nulled and \p{needle} is not or if this is smaller than \p{needle}.
         *  - >0 if this is not \e nulled but \p{needle} is or if this is greater than \p{needle}.
         ******************************************************************************************/
        public int CompareTo(   char[]        needle,
                                Case          sensitivity           = Case.Sensitive,
                                int           needleRegionStart     = 0,
                                int           needleRegionLength    = int.MaxValue,
                                int           regionStart           = 0,
                                int           regionLength          = int.MaxValue    )
        {
            // check null argument
            if ( buffer.Length == 0   )     return  needle == null ? 0 : -1;
            if ( needle == null)     return  +1;

            // adjust source and compare regions
            int cmpLength= needle.Length;
            CString.AdjustRegion( cmpLength, ref needleRegionStart, ref needleRegionLength );
            CString.AdjustRegion(    length, ref       regionStart, ref       regionLength );

            return CString.CompareTo( needle,  needleRegionStart, needleRegionLength,
                                      buffer,        regionStart,       regionLength,
                                      sensitivity );
        }

        /** ****************************************************************************************
         * Compares a Substring with a region of this instance. The region bounds get adjusted
         * to fit to this AString. (If this is not wanted, external checks have to be made
         * prior to calling this method.)
         * @param needle       An object of type char[] that is compared to this.
         * @param sensitivity  Case sensitivity of the comparison.
         *                     Optional and defaults to Case.Sensitive.
         * @param regionStart  The start of the substring within this string that
         *                     is to be compared. Defaults    to 0.
         * @param regionLength The length of the substring within this string that is
         *                     to be compared. Defaults to
         *                     Integer.MAX_VALUE.
         * @return
         *  -  0 if this and \p{needle} are \e nulled or if both have a length of 0 or if both
         *       share the same content
         *  - <0 if this is \e nulled and \p{needle} is not or if this is smaller than \p{needle}.
         *  - >0 if this is not \e nulled but \p{needle} is or if this is greater than \p{needle}.
         ******************************************************************************************/
        public int CompareTo(   Substring     needle,
                                Case          sensitivity                  = Case.Sensitive,
                                int           regionStart=                 0,
                                int           regionLength=                int.MaxValue    )
        {
            // check null argument
            if ( buffer.Length == 0   )     return  needle == null ? 0 : -1;
            if ( needle == null)     return  +1;

            // adjust source and compare regions
            CString.AdjustRegion(    length, ref  regionStart, ref  regionLength );

            return CString.CompareTo( needle.Buf, needle.Start, needle.Length(),
                                      buffer,      regionStart, regionLength,
                                      sensitivity );
        }

        /** ****************************************************************************************
         * Checks if the given String is located at the given position.
         * @param needle      The string to search.
         * @param pos         The position to look at.
         * @param sensitivity         Case sensitivity of the comparison.
         *                            Optional and defaults to Case.Sensitive.
         * @return  True if the given sequence is found at the given position. False otherwise .
         ******************************************************************************************/
        public bool ContainsAt( String needle, int pos, Case sensitivity= Case.Sensitive )
        {
            return CString.ContainsAt( needle, buffer, pos, length, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if a region of a char[] is located at the given position.
         * @param needle       The character array containing the needle.
         * @param needleStart  The index of the start of the needle within the character array.
         * @param needleLength The length of the needle within the character array.
         * @param pos          The position to look at.
         * @param sensitivity  Case sensitivity of the comparison.
         *                     Optional and defaults to Case.Sensitive.
         *
         * @return True if the given AString is found at the given position. False otherwise.
         ******************************************************************************************/
        public bool ContainsAt( char[] needle, int needleStart, int needleLength,
                                int pos, Case sensitivity= Case.Sensitive )
        {
            return CString.ContainsAt( needle, needleStart, needleLength,
                                       buffer, pos,         length,
                                       sensitivity );
        }

        /** ****************************************************************************************
         * Checks if the given AString is located at the given position.
         * @param needle      The AString to search.
         * @param pos         The position to look at.
         * @param sensitivity Case sensitivity of the comparison.
         *                    Optional and defaults to Case.Sensitive.
         * @return  True if the given AString is found at the given position. False otherwise.
         ******************************************************************************************/
        public bool ContainsAt( AString needle, int pos, Case sensitivity= Case.Sensitive )
        {
            // check null argument or length 0
            int needleLen=  needle != null ? needle.Length()
                                           : 0;

            if ( pos < 0 || pos + needleLen > length || needle == null )
                return false;

            if ( needleLen == 0 )
                return true;

            return CString.ContainsAt( needle.buffer, 0, needleLen,
                                       buffer, pos, length,
                                       sensitivity );
        }

        /** ****************************************************************************************
         * Checks if the given AString is located at the given position.
         * @param needle      The AString to search.
         * @param pos         The position to look at.
         * @param sensitivity Case sensitivity of the comparison.
         *                    Optional and defaults to Case.Sensitive.
         * @return  True if the given AString is found at the given position. False otherwise.
         ******************************************************************************************/
        public bool ContainsAt( Substring needle, int pos, Case sensitivity= Case.Sensitive )
        {
            // check null argument or length 0
            return needle != null ? CString.ContainsAt( needle.Buf, needle.Start, needle.Length(),
                                                        buffer, pos, length,
                                                        sensitivity )
                                  : CString.ContainsAt( null, 0, 0,
                                                        buffer, pos, length,
                                                        sensitivity );


        }

        /** ****************************************************************************************
         * Checks if this AString starts with the given String.
         *
         * @param needle      The String to search. If s is null or empty, false is returned.
         * @param sensitivity         Case sensitivity of the comparison.
         *                            Optional and defaults to Case.Sensitive.
         *
         * @return true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public bool StartsWith( String needle,    Case sensitivity= Case.Sensitive )
        {
            return ContainsAt( needle, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if this AString starts with the given String.
         *
         * @param needle      The AString to search. If s is null or empty, false is returned.
         * @param sensitivity         Case sensitivity of the comparison.
         *                            Optional and defaults to Case.Sensitive.
         *
         * @return true if this starts with the given AString, false if not.
         ******************************************************************************************/
        public bool StartsWith( AString needle,    Case sensitivity= Case.Sensitive )
        {
            return ContainsAt( needle, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if this AString starts with the given Substring.
         *
         * @param needle        The Substring to search. If s is null or empty, false is returned.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return true if this starts with the given Substring, false if not.
         ******************************************************************************************/
        public bool StartsWith( Substring needle, Case sensitivity= Case.Sensitive )
        {
            return ContainsAt( needle, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if this String ends with the given String.
         * @param needle      The string to be compared with the start of this AString. If this is null or
         *                            empty, true is returned.
         * @param sensitivity         Case sensitivity of the comparison.
         *                            Optional and defaults to Case.Sensitive.
         * @return true if this starts with the given String, false if not.
         ******************************************************************************************/
        public bool EndsWith  ( String needle, Case sensitivity= Case.Sensitive )
        {
            if ( needle == null )
                return false;

            return ContainsAt( needle, length - needle.Length, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if this AString ends with the given AString.
         * @param needle      The AString to be compared with the start of this AString. If this is null or
         *                            empty, true is returned.
         * @param sensitivity         Case sensitivity of the comparison.
         *                            Optional and defaults to Case.Sensitive.
         * @return true if this starts with the given AString, false if not.
         ******************************************************************************************/
        public bool EndsWith  ( AString needle, Case sensitivity= Case.Sensitive )
        {
            if ( needle == null )
                return false;

            return ContainsAt( needle, length - needle.Length(), sensitivity );
        }

        /** ****************************************************************************************
         * Checks if this AString ends with the given Substring.
         * @param needle      The Substring to be compared with the start of this AString. If this is null or
         *                    empty, true is returned.
         * @param sensitivity Case sensitivity of the comparison.
         *                    Optional and defaults to Case.Sensitive.
         * @return true if this starts with the given Substring, false if not.
         ******************************************************************************************/
        public bool EndsWith  ( Substring needle, Case sensitivity= Case.Sensitive )
        {
            if ( needle == null )
                return false;

            return ContainsAt( needle, length - needle.Length(), sensitivity );
        }

        /** ****************************************************************************************
         * Compares this to the given object. Given object can be AString or String.
         * @param o    The Object that this instance is compared with.
         *
         * @return True if given object equals this.
         ******************************************************************************************/
        public override bool Equals( Object o )
        {
            // null?
            if ( o == null || buffer.Length == 0 )
                return ( (o == null ) == ( buffer.Length == 0 ) );

            // compare with known types
            if ( o is AString )  return Equals( ((AString) o ), Case.Sensitive );
            if ( o is String )   return Equals( (( String) o ), Case.Sensitive );

            // not a known comparable object
            return false;
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given AString equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param compareString The %AString that is compared to this %AString.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public bool Equals( AString compareString, Case sensitivity= Case.Sensitive )
        {
            // null?
            if ( compareString == null || compareString.IsNull() )
                return IsNull();

            // same length?
            if ( compareString.length != length )
                return false;

            return ContainsAt( compareString, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given String equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param compareString The %AString that is compared to this %AString.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public bool Equals( String compareString, Case sensitivity= Case.Sensitive )
        {
            // null?
            if ( compareString == null )
                return IsNull();

            // same length?
            if ( compareString.Length != length )
                return false;

            return ContainsAt( compareString, 0, sensitivity );
        }


        /** ****************************************************************************************
         * Tests and returns true, if the given Substring equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param compareString The Substring that is compared to this %AString.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return    true, if contents of this and the given Substring are equal
         ******************************************************************************************/
        public bool Equals( Substring compareString, Case sensitivity= Case.Sensitive )
        {
            // null?
            if ( compareString == null )
                return IsNull();

            // same length?
            if ( compareString.Length() != length )
                return false;

            return ContainsAt( compareString.Buf, compareString.Start, length, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given string-type object equals to what this object
         * represents. True is returned if both are zero length or \c null.
         * If compiled in debug mode, an assertion is thrown if the given object is not of
         * type String, AString, Substring or char[].
         *
         * @param compareString An object of string-type that is compared to this %AString.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return    true, if contents of this and the given Substring are equal
         ******************************************************************************************/
        public bool Equals( Object compareString, Case sensitivity= Case.Sensitive )
        {
            // null?
            if ( compareString == null )
                return IsNull();

            // cast type
            if ( compareString is AString   ) return Equals( (AString)   compareString, sensitivity );
            if ( compareString is Substring ) return Equals( (Substring) compareString, sensitivity );
            if ( compareString is String    ) return Equals( (String)    compareString, sensitivity );
            if ( compareString is char[]    )
            {
                // same length?
                char[] ca=  compareString as char[];
                if ( ca.Length != length )
                    return false;
                return ContainsAt( ca, 0, length, 0, sensitivity );
            }

            ALIB_DBG.WARNING( "Unknown object type." );

            return false;
        }


    /** @} */

    /** ############################################################################################
     * @name Search
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Search the given character in the buffer.
         *
         * @param needle        The character to search.
         * @param startIdx  The index to start the search at. Optional and defaults to \c 0.
         *
         * @return    -1 if the character is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int IndexOf( char needle, int startIdx= 0 )
        {
            // check
            if      ( startIdx < 0 )          startIdx= 0;
            else if ( startIdx >= length)     return -1;

            // search
            while ( startIdx < length )
            {
                if ( needle == buffer[ startIdx ] )
                    return startIdx;
                startIdx++;
            }

            // not found
            return -1;
        }

        /** ****************************************************************************************
         * Like #IndexOf but in case the character is not found, this method returns the length of
         * this string instead of \c -1.
         * Depending on the invocation context, the choice for the right version of this method may
         * lead to shorter and more efficient code.
         *
         * @param needle  The character to search for.
         * @return  This strings #Length if the character \p{needle} is not found.
         *          Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int    IndexOfOrLength( char needle )
        {
            int idx= 0;
            while ( idx < length && needle != buffer[ idx ])
                idx++;

            return idx;
        }

        /** ****************************************************************************************
         * Like #IndexOf but in case the character is not found, this method returns the length of
         * this string instead of \c -1.
         * Depending on the invocation context, the choice for the right version of this method may
         * lead to shorter and more efficient code.
         *
         * @param needle    The character to search for.
         * @param startIdx  The index in this to start searching the character.
         * @return  This strings #Length if the character \p{needle} is not found.
         *          Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int    IndexOfOrLength( char needle, int startIdx )
        {
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return length;
            while ( startIdx < length && needle != buffer[ startIdx ])
                startIdx++;

            return startIdx;
        }

        /** ****************************************************************************************
         * Search the given \e String in this.
         *
         * @param needle       The String to search.
         * @param startIdx     The index to start the search at. Optional and defaults to \c 0.
         * @param sensitivity          Case sensitivity of the comparison.
         *                             Optional and defaults to Case.Sensitive.
         * @return    -1 if the String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int IndexOf( String needle, int startIdx= 0, Case sensitivity= Case.Sensitive  )
        {
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return -1;
            return CString.IndexOfString( needle, buffer, startIdx, length - startIdx, sensitivity );
        }

        /** ****************************************************************************************
         * Search the given \b %AString in the this.
         *
         * @param needle       The string to search.
         * @param startIdx     The index to start the search at. Optional and defaults to \c 0.
         * @param sensitivity   If true, the compare is case insensitive. Optional and defaults to
         *                             false.
         * @return    -1 if the String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int IndexOf( AString needle, int startIdx= 0, Case sensitivity= Case.Sensitive  )
        {
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return -1;
            return needle != null
                ? CString.IndexOfString( needle.Buffer(), 0, needle.Length(),  buffer, startIdx,  length - startIdx,  sensitivity )
                : CString.IndexOfString( null,            0, 0,                buffer, startIdx,  length - startIdx,  sensitivity );
        }

        /** ****************************************************************************************
         * Search the given \b %Substring in the this.
         *
         * @param needle       The string to search.
         * @param startIdx     The index to start the search at. Optional and defaults to \c 0.
         * @param sensitivity   If true, the compare is case insensitive. Optional and defaults to
         *                             false.
         * @return    -1 if the String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int IndexOf( Substring needle, int startIdx= 0, Case sensitivity= Case.Sensitive  )
        {
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return -1;
            return needle != null
                ? CString.IndexOfString( needle.Buf, needle.Start, needle.Length(),  buffer, startIdx,  length - startIdx,  sensitivity )
                : CString.IndexOfString( null,       0,            0,                buffer, startIdx,  length - startIdx,  sensitivity );
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         *
         * This method searches from left to right. For reverse search, see #LastIndexOfAny.
         *
         * @param needles     AString with characters to be searched for.
         * @param inclusion   Denotes whether the search returns the first index that holds a value
         *                    that is included or that is not excluded in the set of needle
         *                    characters.
         * @param startIdx    The index to start the search at. If the given value is less than 0,
         *                    it is set to 0. If it exceeds the length of the string, the length of
         *                    the string is returned.
         *                    Defaults to 0.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        public int IndexOfAny( char[] needles, Inclusion inclusion, int startIdx= 0 )
        {
            if ( startIdx < 0       ) startIdx= 0;
            if ( startIdx >= length ) return   -1;

            return CString.IndexOfAnyInRegion( buffer, startIdx, length - startIdx, needles, inclusion );
        }

        /** ****************************************************************************************
         * Searches a character backwards starting at the end or at given start index.
         *
         * @param needle       The character to search for.
         * @param startIndex   The index in this to start searching the character.
         *                     Defaults to CString.MaxLen.
         *
         * @return  -1 if the character \p{needle} is not found.
         *          Otherwise the index of its last occurrence relative to the start index.
         ******************************************************************************************/
        public int LastIndexOf( char needle, int startIndex= int.MaxValue )
        {
            // adjust range, if empty return -1
            if ( startIndex <  0      )   return -1;
            if ( startIndex >= length )   startIndex= length - 1;

            while( startIndex >= 0 && buffer[ startIndex ] != needle )
                startIndex--;

            return startIndex;
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         * The search starts at the given index and goes backward.
         * For forward search, see #IndexOfAny.
         *
         * @param needles    AString with characters to be searched for.
         * @param inclusion  Denotes whether the search returns the first index that holds a value
         *                   that is included or that is not excluded in the set of needle
         *                   characters.
         * @param startIdx   The index to start the search at. The value is cropped to be in
         *                   the bounds of 0 and the length of this %AString minus one.
         *                   Defaults to maximum integer value.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        public int LastIndexOfAny( char[] needles, Inclusion inclusion, int startIdx= int.MaxValue )
        {
            if ( startIdx < 0       ) return -1;
            if ( startIdx >= length ) startIdx=  length - 1;
            return  CString.LastIndexOfAny( buffer, 0, startIdx + 1, needles, inclusion );
        }


    /** @} */

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
        public int SearchAndReplace( char needle, char replacement, int startIdx= 0 )
        {
                 if ( startIdx <  0      )  startIdx= 0;
            else if ( startIdx >= length )  return 0;

            // replacement loop
            int cntReplacements=    0;
            for(;;)
            {
                startIdx= IndexOfOrLength( needle, startIdx  );
                if ( startIdx >= length  )
                    return cntReplacements;
                buffer[ startIdx ]= replacement;
                cntReplacements++;
            }
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string. Returns the number
         * of replacements.
         *
         * @param searchStr        The String to be replaced.
         * @param newStr           The replacement string.
         * @param startIdx         The index where the search starts. Optional and defaults
         *                         to 0.
         * @param maxReplacements  The maximum number of replacements to perform. Optional and
         *                         defaults to int.MaxValue .
         * @param sensitivity      Case sensitivity of the comparison.
         *                         Optional and defaults to Case.Sensitive.
         *
         * @return The number of replacements that where performed.
         ******************************************************************************************/
        public int SearchAndReplace( String searchStr, String newStr, int startIdx= 0, int maxReplacements= int.MaxValue, Case sensitivity= Case.Sensitive )
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
                if ( ( idx= IndexOf( searchStr, startIdx, sensitivity ) ) < 0 )
                    return cntReplacements;

                // set dirty
                hash= 0;

                // copy rest up or down
                if ( lenDiff != 0 )
                {
                    // big enough?
                    if ( buffer.Length < length + lenDiff )
                        EnsureRemainingCapacity( lenDiff );
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
         * Replace one or more occurrences of a string by another string. Returns the number
         * of replacements.
         *
         * @param searchStr        The String to be replaced.
         * @param newStr           The replacement string.
         * @param startIdx         The index where the search starts. Optional and defaults
         *                                 to 0.
         * @param maxReplacements  The maximum number of replacements to perform. Optional and
         *                                 defaults to int.MaxValue .
         * @param sensitivity              Case sensitivity of the comparison.
         *                                 Optional and defaults to Case.Sensitive.
         *
         * @return The number of replacements that where performed.
         ******************************************************************************************/
        public int SearchAndReplace( AString searchStr, AString newStr, int startIdx= 0, int maxReplacements= int.MaxValue, Case sensitivity= Case.Sensitive )
        {
            // check null arguments
            if ( IsNullOrEmpty(searchStr) )
                return 0;

            // get some values
            int     searchStringLength=   searchStr.length;
            int     newStringLength=      (newStr != null) ? newStr.length : 0;
            char[]  newStrBuf=            (newStr != null) ? newStr.buffer : null;
            int     lenDiff=              newStringLength - searchStringLength;

            // replacement loop
            int cntReplacements=    0;
            int idx= -1;
            while ( cntReplacements < maxReplacements && idx < length)
            {
                // search  next occurrence
                if ( ( idx= IndexOf( searchStr, startIdx, sensitivity ) ) < 0 )
                    return cntReplacements;

                // set dirty
                hash= 0;

                // copy rest up or down
                if ( lenDiff != 0 )
                {
                    // big enough?
                    if ( buffer.Length < length + lenDiff )
                        EnsureRemainingCapacity( lenDiff );

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
         * Replace one or more occurrences of a string by another string.
         * \note The difference to #SearchAndReplace is that this method returns \b this to allow
         *       concatenated calls.
         *
         * @param searchStr        The String to be replaced.
         * @param newStr           The replacement string.
         * @param startIdx         The index where the search starts. Optional and defaults
         *                                 to 0.
         * @param maxReplacements  The maximum number of replacements to perform. Optional and
         *                                 defaults to int.MaxValue .
         * @param sensitivity              Case sensitivity of the comparison.
         *                                 Optional and defaults to Case.Sensitive.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString SearchAndReplaceAll( AString searchStr, AString newStr, int startIdx= 0, int maxReplacements= int.MaxValue, Case sensitivity= Case.Sensitive )
        {
            SearchAndReplace( searchStr, newStr, startIdx, maxReplacements, sensitivity );
            return this;
        }

        /** ****************************************************************************************
         * Replace one or more occurrences of a string by another string.
         * \note The difference to #SearchAndReplace is that this method returns \b this to allow
         *       concatenated calls.
         *
         * @param searchStr        The String to be replaced.
         * @param newStr           The replacement string.
         * @param startIdx         The index where the search starts. Optional and defaults
         *                                 to 0.
         * @param maxReplacements  The maximum number of replacements to perform. Optional and
         *                                 defaults to int.MaxValue .
         * @param sensitivity              Case sensitivity of the comparison.
         *                                 Optional and defaults to Case.Sensitive.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString SearchAndReplaceAll( String searchStr, String newStr, int startIdx= 0, int maxReplacements= int.MaxValue, Case sensitivity= Case.Sensitive )
        {
            SearchAndReplace( searchStr, newStr, startIdx, maxReplacements, sensitivity );
            return this;
        }

        /** ****************************************************************************************
         * Converts all or a region of characters in the Buffer to upper case.
         *
         * @param regionStart     Start of the region to be converted. Defaults to 0
         * @param regionLength    Length of the region to be converted. Defaults to int.MaxValue.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString ToUpper( int regionStart= 0, int regionLength= int.MaxValue )
        {
            // adjust range, if empty return empty string
            if ( CString.AdjustRegion( length, ref regionStart, ref regionLength ) )
                return this;

            hash= 0;
            int regionEnd= regionStart + regionLength;
            for ( int i= regionStart; i < regionEnd ; i++ )
                buffer[ i ]=   Char.ToUpperInvariant( buffer[ i ] );

            return this;
        }

        /** ****************************************************************************************
         * Converts all or a region of characters in the Buffer to lower case.
         *
         * @param regionStart     Start of the region to be converted. Defaults to 0
         * @param regionLength    Length of the region to be converted. Defaults to int.MaxValue.
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString ToLower( int regionStart= 0, int regionLength= int.MaxValue )
        {
            // adjust range, if empty return empty string
            if ( CString.AdjustRegion( length, ref regionStart, ref regionLength ) )
                return this;

            hash= 0;
            int regionEnd= regionStart + regionLength;
            for ( int i= regionStart; i < regionEnd ; i++ )
                buffer[ i ]=   Char.ToLowerInvariant( buffer[ i ] );

            return this;
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
        public AString Escape( Switch escape= Switch.On, int regionStart= 0, int regionLength= int.MaxValue )
        {
           if( CString.AdjustRegion(length, ref regionStart, ref regionLength) )
               return this;

            int regionEnd= regionStart+ regionLength;

            //
            // To escape sequences
            //
            if (escape == Switch.On)
            {
                for( int idx= regionStart; idx < regionEnd ; ++idx )
                {
                    char c= buffer[idx];

                    char resultChar= '\0';
                    switch(c)
                    {
                        case '\\' : resultChar= '\\'; break;
                        case '\r' : resultChar= 'r' ; break;
                        case '\n' : resultChar= 'n' ; break;
                        case '\t' : resultChar= 't' ; break;
                        case '\a' : resultChar= 'a' ; break;
                        case '\b' : resultChar= 'b' ; break;
                        case '\v' : resultChar= 'v' ; break;
                        case '\f' : resultChar= 'f' ; break;
                     // case '\e' : resultChar= 'e' ; break; Not C++ standard
                        case '"'  : resultChar= '"' ; break;

                        default   :                   break;
                    }

                    if( resultChar != '\0')
                    {
                        InsertChars( ' ', 1, idx);
                        buffer[idx++]= '\\';
                        buffer[idx]= resultChar;
                        regionEnd++;
                    }
                    else
                    {
                        if (c < 32  )
                        {
                            InsertChars(' ', 3, idx);
                            buffer[idx++]= '\\';
                            buffer[idx++]= '0';
                            var oct= c >> 3;
                            buffer[idx++]=  (char) ( '0' + oct );
                                 oct=       (char) ( c & 7 );
                            buffer[idx]  =  (char) ( '0' + oct );

                            regionEnd+=3;
                        }
                        else
                        if ( c >126 )
                        {
                            InsertChars(' ', 3, idx);
                            buffer[idx++]= '\\';
                            buffer[idx++]= 'x';
                            var nibble= c >> 4;
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
                for( int idx= regionStart; idx < regionEnd ; ++idx )
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
                        case 'a'  : resultChar= '\a' ; break;
                        case 'b'  : resultChar= '\b' ; break;
                        case 'v'  : resultChar= '\v' ; break;
                        case 'f'  : resultChar= '\f' ; break;
                     // case 'e'  : resultChar= '\e' ; break; Not C++ standard
                        case '"'  : resultChar= '"' ; break;

                        default   :                   break;
                    }

                    if( resultChar != '\0')
                    {
                        Delete( idx, 1);
                        buffer[idx]= resultChar;
                        regionEnd--;
                    }
                    else
                    {
                        if (c == '0' && idx + 2 < regionEnd )
                        {
                            buffer[idx]= (char) (   (buffer[idx + 2] - '0' ) *8
                                                  + (buffer[idx + 3] - '0' ))        ;
                            Delete( idx + 1, 3);
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
                            Delete( idx+1, 3);
                            regionEnd-=3;
                        }
                    }
                }
            }


            return this;
        }


    /** @} */


    /** ############################################################################################
     * @name Convert
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Format and append a signed 32-Bit integer value.
         *
         * Parameter \p{numberFormat} defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational".
         * To generate output better readable for humans, provide
         * \ref cs.aworx.lib.strings.NumberFormat.Global "NumberFormat.Global", or a
         * customized object of that type.
         *
         * See \ref cs.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref cs.aworx.lib.strings.NumberFormat.DecMinimumFieldWidth "NumberFormat.DecMinimumFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( int value, int overrideWidth= 0, NumberFormat numberFormat= null )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= NumberFormat.Computational;

            EnsureRemainingCapacity( 28 );

            length= numberFormat.WriteDecSigned( value, buffer, length, overrideWidth );

            ALIB_DBG.ASSERT( length <= Capacity() );

            return this;
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
            return _( value, 0, numberFormat );
        }

        /** ****************************************************************************************
         * Format and append an unsigned 32-Bit integer value.
         *
         * Parameter \p{numberFormat} defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational".
         * To generate output better readable for humans, provide
         * \ref cs.aworx.lib.strings.NumberFormat.Global "NumberFormat.Global", or a
         * customized object of that type.
         *
         * See \ref cs.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref cs.aworx.lib.strings.NumberFormat.DecMinimumFieldWidth "NumberFormat.DecMinimumFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( uint value, int overrideWidth= 0, NumberFormat numberFormat= null )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= NumberFormat.Computational;

            EnsureRemainingCapacity( 28 );

            length= numberFormat.WriteDecUnsigned( value, buffer, length, overrideWidth );

            ALIB_DBG.ASSERT( length <= Capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_(uint,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( uint value, NumberFormat numberFormat )
        {
            return _( value, 0, numberFormat );
        }


        /** ****************************************************************************************
         * Format and append a signed 64-Bit integer value.
         *
         * Parameter \p{numberFormat} defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational".
         * To generate output better readable for humans, provide
         * \ref cs.aworx.lib.strings.NumberFormat.Global "NumberFormat.Global", or a
         * customized object of that type.
         *
         * See \ref cs.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref cs.aworx.lib.strings.NumberFormat.DecMinimumFieldWidth "NumberFormat.DecMinimumFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( long value, int overrideWidth= 0, NumberFormat numberFormat= null )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= NumberFormat.Computational;

            EnsureRemainingCapacity( 28 );

            length= numberFormat.WriteDecSigned( value, buffer, length, overrideWidth );

            ALIB_DBG.ASSERT( length <= Capacity() );

            return this;
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
            return _( value, 0, numberFormat );
        }

        /** ****************************************************************************************
         * Format and append an unsigned 64-Bit integer value.
         *
         * Parameter \p{numberFormat} defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational".
         * To generate output better readable for humans, provide
         * \ref cs.aworx.lib.strings.NumberFormat.Global "NumberFormat.Global", or a
         * customized object of that type.
         *
         * See \ref cs.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref cs.aworx.lib.strings.NumberFormat.DecMinimumFieldWidth "NumberFormat.DecMinimumFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( ulong value, int overrideWidth= 0, NumberFormat numberFormat= null )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= NumberFormat.Computational;

            EnsureRemainingCapacity( 28 );

            length= numberFormat.WriteDecUnsigned( value, buffer, length, overrideWidth );

            ALIB_DBG.ASSERT( length <= Capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_(ulong,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( ulong value, NumberFormat numberFormat )
        {
            return _( value, 0, numberFormat );
        }

        /** ****************************************************************************************
         * Append a unsigned 64-Bit integer value in binary format.
         *
         * Parameter \p{numberFormat} defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational".
         * To generate output better readable for humans, provide
         * \ref cs.aworx.lib.strings.NumberFormat.Global "NumberFormat.Global", or a
         * customized object of that type.
         *
         * See \ref cs.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref cs.aworx.lib.strings.NumberFormat.BinFieldWidth "NumberFormat.BinFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Bin( ulong value, int overrideWidth= 0,  NumberFormat numberFormat= null )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= NumberFormat.Computational;

            EnsureRemainingCapacity( 80 );

            length= numberFormat.WriteBin( value, buffer, length, overrideWidth );

            ALIB_DBG.ASSERT( length <= Capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_Bin(ulong,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Bin( ulong value, NumberFormat numberFormat )
        {
            return _Bin( value, 0, numberFormat );
        }


        /** ****************************************************************************************
         * Append a unsigned 64-Bit integer value in hexadecimal format.
         *
         * Parameter \p{numberFormat} defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational".
         * To generate output better readable for humans, provide
         * \ref cs.aworx.lib.strings.NumberFormat.Global "NumberFormat.Global", or a
         * customized object of that type.
         *
         * See \ref cs.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref cs.aworx.lib.strings.NumberFormat.HexFieldWidth "NumberFormat.HexFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Hex( ulong value, int overrideWidth= 0,  NumberFormat numberFormat= null )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= NumberFormat.Computational;

            EnsureRemainingCapacity( 80 );

            length= numberFormat.WriteHex( value, buffer, length, overrideWidth );

            ALIB_DBG.ASSERT( length <= Capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_Hex(ulong,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Hex( ulong value, NumberFormat numberFormat )
        {
            return _Hex( value, 0, numberFormat );
        }


        /** ****************************************************************************************
         * Append a unsigned 64-Bit integer value in octal format.
         *
         * Parameter \p{numberFormat} defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational".
         * To generate output better readable for humans, provide
         * \ref cs.aworx.lib.strings.NumberFormat.Global "NumberFormat.Global", or a
         * customized object of that type.
         *
         * See \ref cs.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref cs.aworx.lib.strings.NumberFormat.OctFieldWidth "NumberFormat.OctFieldWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Oct( ulong value, int overrideWidth= 0,  NumberFormat numberFormat= null )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= NumberFormat.Computational;

            EnsureRemainingCapacity( 80 );

            length= numberFormat.WriteOct( value, buffer, length, overrideWidth );

            ALIB_DBG.ASSERT( length <= Capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_Oct(ulong,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _Oct( ulong value, NumberFormat numberFormat )
        {
            return _Oct( value, 0, numberFormat );
        }


        /** ****************************************************************************************
         * Formats and appends a double floating point value.
         *
         * Parameter \p{numberFormat} defaults to \c null, which denotes this method to use
         * the static singleton found in
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational".
         * To generate output better readable for humans, provide
         * \ref cs.aworx.lib.strings.NumberFormat.Global "NumberFormat.Global", or a
         * customized object of that type.
         *
         * See \ref cs.aworx.lib.strings.NumberFormat "NumberFormat"
         * for more information on formatting options.
         *
         * @param value         The value to append.
         * @param overrideWidth If not \c 0 (the default), overrides the output width otherwise
         *                      specified in field
         *                      \ref cs.aworx.lib.strings.NumberFormat.IntegralPartMinimumWidth "NumberFormat.IntegralPartMinimumWidth".
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( double value, int overrideWidth =0 , NumberFormat numberFormat = null )
        {
            hash= 0;

            if( numberFormat == null)
                numberFormat= NumberFormat.Computational;

            EnsureRemainingCapacity( 48 ); // 2x15 + '.' + ',' + sign + fear

            length= numberFormat.WriteFloat( value, buffer, length, overrideWidth );

            ALIB_DBG.ASSERT( length <= Capacity() );

            return this;
        }

        /** ****************************************************************************************
         * Overloaded version of #_(double,int,NumberFormat) which provides default parameter(s).
         *
         * @param value         The value to append.
         * @param numberFormat  The format definition. Defaults to \c null.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public AString _( double value, NumberFormat numberFormat )
        {
            return _( value, 0, numberFormat );
        }


        /** ****************************************************************************************
         * Creates a String containing a copy of the contents of this AString.
         *
         * @return A String that represents this object.
         ******************************************************************************************/
        public override String ToString()
        {
            return new String( buffer, 0, length );
        }

        /** ****************************************************************************************
         * Creates a String containing a copy of a region of the contents of this AString.
         *
         * @param regionStart   The start index of the region in this to create the string from.
         * @param regionLength  The maximum length of the region to create the string from.
         *                      Defaults to int.MaxValue.
         *
         * @return A String that represents the specified sub region of this object.
         ******************************************************************************************/
        public String ToString( int regionStart, int regionLength= int.MaxValue)
        {
            // adjust range, if empty return empty string
            if ( CString.AdjustRegion( length, ref regionStart, ref regionLength ) )
                return "";

            // create string
            return new String( buffer, regionStart, regionLength);
        }

        /** ****************************************************************************************
         * Copies a region of the contents of this AString into the given StringBuilder.
         *
         * @param result        A result string to copy the specified region into.
         * @param regionStart   The start index of the region to be copied.
         * @param regionLength  The maximum length of the region to be copied.
         *                      Defaults to int.MaxValue.
         * @param appendMode    If true, any contents in the result is preserved. Otherwise
         *                      such content gets replaced.
         *                      Defaults to false.
         *
         * @return The (modified) result that was provided (for concatenation of calls).
         ******************************************************************************************/
        public StringBuilder ToString( StringBuilder result, int regionStart, int regionLength= int.MaxValue, bool appendMode= false  )
        {
            if ( !appendMode )
                result.Clear();

            // adjust range, if empty return empty string
            if ( CString.AdjustRegion( length, ref regionStart, ref regionLength ) )
                return result;

            // copy our buffer into result
            result.Append( buffer , regionStart, regionLength );
            return  result;
        }



        /** ****************************************************************************************
         * Copies the contents of this AString into the given StringBuilder.
         *
         * @param result        A result string to copy the contents of this AString into.
         * @param appendMode    Optional: If true, any contents in the result is preserved. Otherwise
         *                              such content gets replaced (default).
         * @return The (modified) result that was provided (for concatenation of calls).
         ******************************************************************************************/
        public StringBuilder ToString( StringBuilder result, bool appendMode= false )
        {
            return ToString( result, 0, length, appendMode );
        }

        /** ****************************************************************************************
         * Parses an integer value consisting of characters \c '0' to \c '9' from this string.
         * <br>Unlike with #ParseInt or #ParseDec, no sign, whitespaces or group characters are
         * accepted.
         *
         * @param startIdx     The start index from where the integer value is tried to be parsed.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the float number that was parsed.
         *                     If parsing fails, it will be set to the value of parameter startIdx.
         *
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public ulong ParseDecDigits( int startIdx, out int newIdx )
        {
            newIdx= startIdx;
            return NumberFormat.ParseDecDigits( buffer, ref newIdx, length-1 );
        }

        /** ****************************************************************************************
         * Parses a long integer value in decimal, binary, hexadecimal or octal format from
         * the string by invoking method
         * \ref cs.aworx.lib.strings.NumberFormat.ParseInt "NumberFormat.ParseInt"
         * on the given \p{numberFormat} instance.<br>
         * Parameter \p{numberFormat} defaults to \c null. This denotes static singleton
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p{newIdx} may be used to detect if parsing was successful.
         * If not, it receives the value of \p{startIdx}, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long ParseInt( int startIdx, NumberFormat numberFormat, out int newIdx  )
        {
            newIdx= startIdx;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseInt( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseInt(int,NumberFormat,out int) "ParseInt" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return The parsed value.
         ******************************************************************************************/
        public long ParseInt( int startIdx = 0, NumberFormat numberFormat = null )
        {
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseInt( buffer, ref startIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseInt(int,NumberFormat,out int) "ParseInt" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public long ParseInt( int startIdx, out int newIdx  )
        {
            newIdx= startIdx;
            return  NumberFormat.Computational.ParseInt( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseInt(int,NumberFormat,out int) "ParseInt" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public long ParseInt( NumberFormat numberFormat,  out int newIdx  )
        {
            newIdx= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseInt( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseInt(int,NumberFormat,out int) "ParseInt" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public long ParseInt( NumberFormat numberFormat )
        {
            int dummy= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseInt( buffer, ref dummy, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseInt(int,NumberFormat,out int) "ParseInt" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public long ParseInt( out int newIdx  )
        {
            newIdx= 0;
            return NumberFormat.Computational.ParseInt( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in standard decimal format at the given position
         * from this %AString. This is done, by invoking
         * \ref cs.aworx.lib.strings.NumberFormat.ParseDec "NumberFormat.ParseDec"
         * on the given \p{numberFormat} instance.<br>
         * Parameter \p{numberFormat} defaults to \c null. This denotes static singleton
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p{newIdx} may be used to detect if parsing was successful.
         * If not, it receives the value of \p{startIdx}, even if leading whitespaces had been
         * read.
         *
         * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail.
         * For reading signed integer values, see methods #ParseInt, for floating point numbers
         * #ParseFloat.
         *
         * For more information on number conversion, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public ulong ParseDec( int startIdx, NumberFormat numberFormat, out int newIdx  )
        {
            newIdx= startIdx;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseDec( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseDec(int,NumberFormat,out int) "ParseDec" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return The parsed value.
         ******************************************************************************************/
        public ulong ParseDec( int startIdx = 0, NumberFormat numberFormat = null )
        {
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseDec( buffer, ref startIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseDec(int,NumberFormat,out int) "ParseDec" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public ulong ParseDec( int startIdx, out int newIdx  )
        {
            newIdx= startIdx;
            return  NumberFormat.Computational.ParseDec( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseDec(int,NumberFormat,out int) "ParseDec" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public ulong ParseDec( NumberFormat numberFormat,  out int newIdx  )
        {
            newIdx= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseDec( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseDec(int,NumberFormat,out int) "ParseDec" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public ulong ParseDec( NumberFormat numberFormat )
        {
            int dummy= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseDec( buffer, ref dummy, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseDec(int,NumberFormat,out int) "ParseDec" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public ulong ParseDec( out int newIdx  )
        {
            newIdx= 0;
            return NumberFormat.Computational.ParseDec( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in binary format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref cs.aworx.lib.strings.NumberFormat.ParseBin "NumberFormat.ParseBin"
         * on the given \p{numberFormat} instance.<br>
         * Parameter \p{numberFormat} defaults to \c null. This denotes static singleton
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p{newIdx} may be used to detect if parsing was successful.
         * If not, it receives the value of \p{startIdx}, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public ulong ParseBin( int startIdx, NumberFormat numberFormat, out int newIdx  )
        {
            newIdx= startIdx;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseBin( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseBin(int,NumberFormat,out int) "ParseBin" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return The parsed value.
         ******************************************************************************************/
        public ulong ParseBin( int startIdx = 0, NumberFormat numberFormat = null )
        {
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseBin( buffer, ref startIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseBin(int,NumberFormat,out int) "ParseBin" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public ulong ParseBin( int startIdx, out int newIdx  )
        {
            newIdx= startIdx;
            return  NumberFormat.Computational.ParseBin( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseBin(int,NumberFormat,out int) "ParseBin" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public ulong ParseBin( NumberFormat numberFormat,  out int newIdx  )
        {
            newIdx= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseBin( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseBin(int,NumberFormat,out int) "ParseBin" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public ulong ParseBin( NumberFormat numberFormat )
        {
            int dummy= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseBin( buffer, ref dummy, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseBin(int,NumberFormat,out int) "ParseBin" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public ulong ParseBin( out int newIdx  )
        {
            newIdx= 0;
            return NumberFormat.Computational.ParseBin( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in hexadecimal format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref cs.aworx.lib.strings.NumberFormat.ParseHex "NumberFormat.ParseHex"
         * on the given \p{numberFormat} instance.<br>
         * Parameter \p{numberFormat} defaults to \c null. This denotes static singleton
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p{newIdx} may be used to detect if parsing was successful.
         * If not, it receives the value of \p{startIdx}, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public ulong ParseHex( int startIdx, NumberFormat numberFormat, out int newIdx  )
        {
            newIdx= startIdx;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseHex( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseHex(int,NumberFormat,out int) "ParseHex" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return The parsed value.
         ******************************************************************************************/
        public ulong ParseHex( int startIdx = 0, NumberFormat numberFormat = null )
        {
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseHex( buffer, ref startIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseHex(int,NumberFormat,out int) "ParseHex" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public ulong ParseHex( int startIdx, out int newIdx  )
        {
            newIdx= startIdx;
            return  NumberFormat.Computational.ParseHex( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseHex(int,NumberFormat,out int) "ParseHex" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public ulong ParseHex( NumberFormat numberFormat,  out int newIdx  )
        {
            newIdx= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseHex( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseHex(int,NumberFormat,out int) "ParseHex" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public ulong ParseHex( NumberFormat numberFormat )
        {
            int dummy= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseHex( buffer, ref dummy, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseHex(int,NumberFormat,out int) "ParseHex" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public ulong ParseHex( out int newIdx  )
        {
            newIdx= 0;
            return NumberFormat.Computational.ParseHex( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in octal format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref cs.aworx.lib.strings.NumberFormat.ParseOct "NumberFormat.ParseOct"
         * on the given \p{numberFormat} instance.<br>
         * Parameter \p{numberFormat} defaults to \c null. This denotes static singleton
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Optional output parameter \p{newIdx} may be used to detect if parsing was successful.
         * If not, it receives the value of \p{startIdx}, even if leading whitespaces had been
         * read.
         *
         * For more information on number conversion, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public ulong ParseOct( int startIdx, NumberFormat numberFormat, out int newIdx  )
        {
            newIdx= startIdx;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseOct( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseOct(int,NumberFormat,out int) "ParseOct" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return The parsed value.
         ******************************************************************************************/
        public ulong ParseOct( int startIdx = 0, NumberFormat numberFormat = null )
        {
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseOct( buffer, ref startIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseOct(int,NumberFormat,out int) "ParseOct" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public ulong ParseOct( int startIdx, out int newIdx  )
        {
            newIdx= startIdx;
            return  NumberFormat.Computational.ParseOct( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseOct(int,NumberFormat,out int) "ParseOct" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public ulong ParseOct( NumberFormat numberFormat,  out int newIdx  )
        {
            newIdx= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseOct( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseOct(int,NumberFormat,out int) "ParseOct" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public ulong ParseOct( NumberFormat numberFormat )
        {
            int dummy= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseOct( buffer, ref dummy, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseOct(int,NumberFormat,out int) "ParseOct" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public ulong ParseOct( out int newIdx )
        {
            newIdx= 0;
            return NumberFormat.Computational.ParseOct( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Reads a floating point number at the given position from this \b %AString.
         * This is done, by invoking
         * \ref cs.aworx.lib.strings.NumberFormat.ParseFloat "NumberFormat.ParseFloat"
         * on the given \p{numberFormat} instance.<br>
         * Parameter \p{numberFormat} defaults to \c null. This denotes static singleton
         * \ref cs.aworx.lib.strings.NumberFormat.Computational "NumberFormat.Computational"
         * which is configured to 'international' settings (not using the locale) and therefore
         * also not parsing grouping characters.
         *
         * Optional output parameter \p{newIdx} may be used to detect if parsing was successful.
         * If not, it receives the value of \p{startIdx}, even if leading whitespaces had been
         * read.
         *
         * For more information on parsing options for floating point numbers and number
         * conversion in general, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat". All of its interface methods
         * have a corresponding implementation within class \b %AString.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public double ParseFloat( int startIdx, NumberFormat numberFormat, out int newIdx  )
        {
            newIdx= startIdx;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseFloat( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseFloat(int,NumberFormat,out int) "ParseFloat" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param numberFormat The format definition. Defaults to \c null.
         * @return The parsed value.
         ******************************************************************************************/
        public double ParseFloat( int startIdx = 0, NumberFormat numberFormat = null )
        {
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseFloat( buffer, ref startIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseFloat(int,NumberFormat,out int) "ParseFloat" providing default values for
         * omitted parameters.
         *
         * @param startIdx     The start index for parsing.
         *                     Optional and defaults to \c 0.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \p{startIdx}.
         * @return  The parsed value. In addition, the output parameter \b newIdx is set to
         *          point to the first character behind the parsed number.
         ******************************************************************************************/
        public double ParseFloat( int startIdx, out int newIdx  )
        {
            newIdx= startIdx;
            return  NumberFormat.Computational.ParseFloat( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseFloat(int,NumberFormat,out int) "ParseFloat" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public double ParseFloat( NumberFormat numberFormat,  out int newIdx  )
        {
            newIdx= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseFloat( buffer, ref newIdx, length - 1 );
        }

        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseFloat(int,NumberFormat,out int) "ParseFloat" providing default values for
         * omitted parameters.
         *
         * @param numberFormat The format definition. Defaults to \c null.
         * @return  The parsed value.
         ******************************************************************************************/
        public double ParseFloat( NumberFormat numberFormat )
        {
            int dummy= 0;
            return ( numberFormat != null ? numberFormat
                                          : NumberFormat.Computational ).ParseFloat( buffer, ref dummy, length - 1 );
        }
        /** ****************************************************************************************
         * Overloaded version of
         * \ref ParseFloat(int,NumberFormat,out int) "ParseFloat" providing default values for
         * omitted parameters.
         *
         * @param[out] newIdx  Optional output variable that will point to the first
         *                     character in this string after the number parsed.
         *                     On failure, it will be set to the initial value \c 0.
         * @return  The parsed value. In addition, the input/output parameter idx is set to point
         *          to the first character behind any found integer number.
         ******************************************************************************************/
        public double ParseFloat( out int newIdx  )
        {
            newIdx= 0;
            return NumberFormat.Computational.ParseFloat( buffer, ref newIdx, length - 1 );
        }

    /** @} */

    /** ############################################################################################
     * @name C# std library interface implementation
     ##@{ ########################################################################################*/


        /** ****************************************************************************************
         * Calculates the hash value using the same formula as java.lang.String.
         * @return A hash value for this object.
         ******************************************************************************************/
        public override int GetHashCode()
        {
            if (hash == 0 && length > 0)
            {
                int h= 0;

                for (int i = 0; i < length; i++)
                    h = 31*h + buffer[i++];

                hash = h;
            }
            return hash;
        }
    /** @} */

    // #############################################################################################
    // public statics
    // #############################################################################################
        /** ****************************************************************************************
         * Static method to test if an AString is \c null or has a length of \c 0.
         * @param ms The AString to test.
         *
         * @return \c true if given AString is \c null or has a length of \c 0.
         ******************************************************************************************/
        public static bool IsNullOrEmpty( AString ms )
        {
            return     ms        == null
                    || ms.length == 0    ;
        }

        /** ****************************************************************************************
         * Static method to test if an arbitrary object is \c null. In case of type \b %AString or
         * \b %Substring \c null is returned when they are \e nulled.
         *
         * @param o The object to test
         *
         * @return \c true if given object is null or a nulled ALib string type.
         ******************************************************************************************/
        public static bool IsNull ( Object o )
        {
            return  (    ( o is AString   && ( (AString)   o ).IsNull() )
                      || ( o is Substring && ( (Substring) o ).IsNull() )
                      || o == null
                    );
        }


    // #############################################################################################
    // protected internals
    // #############################################################################################
        /** ****************************************************************************************
         * Protected method that resizes a region into the Buffer.
         * The region contents is undefined.
         *
         * @param regionStart   The start of the region to insert. If this is out of the string
         *                      bounds (hence less than 0 or greater then #Length), nothing is done.
         * @param regionLength  The current length of the region.
         * @param newLength     The desired length of the region.
         * @return \c true, if the parameters were OK and the region was resized,
         *         \c false otherwise.
         ******************************************************************************************/
        protected  bool   resizeRegion( int regionStart, int regionLength, int newLength )
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
                EnsureRemainingCapacity( lenDiff );

            // move content
            if ( lenDiff != 0 )
            {
                Array.Copy( buffer, regionStart + regionLength,
                            buffer, regionStart + newLength,
                            length - (regionStart + regionLength) );
                length+= lenDiff;
            }

            return true;
        }


} // class AString

} // namespace / EOF
