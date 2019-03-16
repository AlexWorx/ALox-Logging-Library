// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.strings;

import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Inclusion;
import com.aworx.lib.lang.Whitespaces;

/** ************************************************************************************************
 *  This class is used for defining a region (sub-string) on an existing character array which
 *  is provided. This class will not manipulate the underlying
 *  data. In particular, there is no terminating zero written into the data.
 *
 *  The represented region is defined by the two fields #start and #end. The fields are
 *  public accessible.
 *  In general, while working with a %Substring, the size of it should shrink, e.g. by trimming
 *  but should not grow.
 *  However, if the code using this class is "sure" that enlarging the region
 *  does violate the bounds of the buffer, fields #start and #end might be modified from outside.
 *
 *  If created or set using a reference of class AString, the buffer of AString is <em>not</em>
 *  copied. This allows efficient operations on sub-strings of class AString. However, the source
 *  string must not be changed (or only in a controlled way) during the use the %Substring instance.
 *
 *  Objects of this class can be reused by freshly initializing them using one of the overloaded
 *  \b set methods.
 *
 *  \note
 *    To generate Substrings which are separated by a delimiter character within a
 *    character array, use class
 *    \ref com.aworx.lib.strings.util.Tokenizer "Tokenizer".
 *  <p>
 *
 *  \note
 *    In the Java and C# versions of \b %ALib, due to the language design, fields #start and #end have
 *    to be used to define the substring on a field #buf, the character buffer. This forces
 *    a \e reimplementation of a bigger portion of the interface of class
 *    \ref com.aworx.lib.strings.AString "AString". In the C++ version of \b %ALib, there is a
 *    richer family of string classes that fully integrates with zero terminated <em>C strings</em>,
 *    standard C++ strings and 3rd party string libraries. Neither the fields \e %start and \e %end
 *    are necessary, nor the aforementioned reimplementation. Consequently, when directly accessing
 *    public fields #buf, #start and #end, the code gets incompatible to C++ code.
 **************************************************************************************************/
public class Substring implements CharSequence
{
    // #############################################################################################
    // Protected fields
    // #############################################################################################
        /**
         *  Used as a return value of method
         *  \ref com.aworx.lib.strings.CString.adjustRegion "CString.adjustRegion"
         */
        protected int[] _adjustedRegion = new int[2];

    // #############################################################################################
    // Public fields
    // #############################################################################################
        /**  The character array we work on. */
        public      char[]          buf;

        /**  Start marker within buf */
        public      int             start;

        /**  End marker within buf (points to the last character) */
        public      int             end;

        /**  Used as second return value with method various consumeChar methods. */
        public      long            consumedLong;

        /**  Used as second return value with method #consumeFloat. */
        public      double          consumedFloat;


    /** ############################################################################################
     * @name Constructors
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         *  Empty Constructor. Sets this sub-string to 'null'
         ******************************************************************************************/
        public Substring()
        {
            setNull();
        }

        /** ****************************************************************************************
         *  Copy constructor.
         *  @param substring  The substring to copy.
         ******************************************************************************************/
        public Substring( Substring substring )
        {
            set( substring);
        }

        /** ****************************************************************************************
         *  Constructs the %Substring to be a region of given AString.
         *  If the provided values start and length get out of range, they get adjusted.
         * @param src           The string we work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         * @param regionLength  The length of the region within \p{src}. Defaults to the length
         *                      of \p{src}.
         ******************************************************************************************/
        public Substring( AString src, int regionStart, int regionLength )
        {
            set( src, regionStart, regionLength );
        }

        /** ****************************************************************************************
         *  Constructs the %Substring to be a region of given AString.
         *  If the provided values start and length get out of range, they get adjusted.
         * @param src           The string we work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         ******************************************************************************************/
        public Substring( AString src, int regionStart )
        {
            set( src, regionStart  );
        }

        /** ****************************************************************************************
         *  Constructs the %Substring on the given AString. Start and end markers will be cover
         *  all of AString.
         *  start and the  end of the given AString.
         *  @param src The string we work with.
         ******************************************************************************************/
        public Substring( AString src )
        {
            set( src  );
        }

        /** ****************************************************************************************
         *  Constructs the sub-string to work on the provided character array.
         *
         * @param src           The string we work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         * @param regionLength  The length of the region within \p{src}. Defaults to the length
         *                      of \p{src}.
         ******************************************************************************************/
        public Substring( char[] src, int regionStart, int regionLength )
        {
            set( src, regionStart, regionLength);
        }

        /** ****************************************************************************************
         *  Constructs the sub-string to work on the provided character array.
         *
         * @param src           The string we work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         ******************************************************************************************/
        public Substring( char[] src, int regionStart )
        {
            set( src, regionStart );
        }


        /** ****************************************************************************************
         *  Constructs the sub-string to work on the provided character array.
         *
         *  @param src The character array to work on.
         ******************************************************************************************/
        public Substring( char[] src )
        {
            set( src );
        }

        /** ****************************************************************************************
         *  Constructs the sub-string to work on the provided \e String.
         *
         * @param src           The string we work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         * @param regionLength  The length of the region within \p{src}. Defaults to the length
         *                      of \p{src}.
         ******************************************************************************************/
        public Substring( String src, int regionStart, int regionLength )
        {
            set( src, regionStart, regionLength);
        }

        /** ****************************************************************************************
         *  Constructs the sub-string to work on the provided \e String.
         *
         * @param src           The string we work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         ******************************************************************************************/
        public Substring( String src, int regionStart )
        {
            set( src.toCharArray(), start );
        }

        /** ****************************************************************************************
         *  Constructs the sub-string to work on the provided \e String.
         *
         *  @param src  The \e String to work on.
         ******************************************************************************************/
        public Substring( String src )
        {
            set( src.toCharArray() );
        }

    /** ############################################################################################
     * @name Set data
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         *  Sets the substring to represent a region of the given \b %Substring.
         *
         * @param src          The string to work on.
         * @param regionStart  The start of the region within \p{src}.  Defaults to 0.
         * @param regionLength The length of the region within \p{src}.
         *                     If negative, length of the provided \e src is used.
         *                     Defaults to -1.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( Substring src, int regionStart, int regionLength )
        {
            buf=    src.buf;
            start=  src.start + regionStart;
            end=    start + ( regionLength < 0 ? src.length() - regionStart : regionLength ) -1;
            return this;
        }

        /** ****************************************************************************************
         *  Sets the substring to represent a region of the given \b %Substring.
         *
         * @param src         The string to work on.
         * @param regionStart The start of the region within \p{src}.  Defaults to 0.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( Substring src, int regionStart )
        {
            return set( src, regionStart, -1 );
        }

        /** ****************************************************************************************
         *  Sets the substring to be identical to the given substring.
         *
         * @param src           The string to work on.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( Substring src )
        {
            buf=    src.buf;
            start=  src.start;
            end=    src.end;
            return this;
        }

        /** ****************************************************************************************
         *  Resets the sub-string to work on the provided AString.
         *
         * @param src           The string to work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         * @param regionLength  The length of the region within \p{src}. Defaults to the length
         *                      of \p{src}.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( AString src, int regionStart, int regionLength )
        {
            if ( src == null || src.isNull() )
            {
                setNull();
                return this;
            }

            CString.adjustRegion( src.length(), regionStart, regionLength, _adjustedRegion );

            buf=    src.buffer();
            start=  _adjustedRegion[0];
            end=    _adjustedRegion[1] + start - 1;

            return this;
        }

        /** ****************************************************************************************
         *  Resets the sub-string to work on the provided AString.
         *
         * @param src           The string to work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( AString src, int regionStart )
        {
            if ( src == null || src.isNull() )
            {
                setNull();
                return this;
            }

            if( regionStart < 0 )
                regionStart= 0;
            int regionLength= Integer.MAX_VALUE;
            CString.adjustRegion( src.length(), regionStart, regionLength, _adjustedRegion );
            buf=    src.buffer();
            start=  _adjustedRegion[0];
            end=    _adjustedRegion[1] + start - 1;
            return this;
        }

        /** ****************************************************************************************
         *  Resets the sub-string to work on the provided AString.
         *
         * @param src           The string to work on.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( AString src )
        {
            if ( src == null || src.isNull() )
            {
                setNull();
                return this;
            }

            buf=    src.buffer();
            start=  0;
            end=    src.length() - 1;
            return  this;
        }

        /** ****************************************************************************************
         *  Resets the sub-string to work on the provided character array.
         *
         * @param src           The string to work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         * @param regionLength  The length of the region within \p{src}. Defaults to the length
         *                      of \p{src}.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( char[] src, int regionStart, int regionLength )
        {
            if ( src == null )
            {
                setNull();
                return this;
            }

            this.buf=     src;
            this.start=   regionStart;
            this.end=     ( regionLength < 0 ? src.length : regionStart + regionLength ) -1;
            return this;
        }

        /** ****************************************************************************************
         *  Resets the sub-string to work on the provided character array.
         *
         * @param src           The string to work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( char[] src, int regionStart )
        {
            return set( src, regionStart, src.length );
        }

        /** ****************************************************************************************
         *  Resets the sub-string to work on the provided character array.
         *
         * @param src           The string to work on.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( char[] src )
        {
            return set( src, 0, src.length );
        }

        /** ****************************************************************************************
         *  Resets the sub-string to work on the provided String
         * @param src           The string to work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         * @param regionLength  The length of the region within \p{src}. Defaults to the length
         *                      of \p{src}.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( String src, int regionStart, int regionLength )
        {
            return set( src.toCharArray(), regionStart, regionLength );
        }


        /** ****************************************************************************************
         *  Resets the sub-string to work on the provided String
         * @param src           The string to work on.
         * @param regionStart   The start of the region within \p{src}.  Defaults to 0.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( String src, int regionStart)
        {
            return set( src.toCharArray(), regionStart, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         *  Resets the sub-string to work on the provided String
         * @param src           The string to work on.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring set( String src )
        {
            return set( src.toCharArray() );
        }

    /** ############################################################################################
     * @name State and Character Access
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * @return  The length of the represented region.
         ******************************************************************************************/
        @Override
        public int     length()         { return end - start + 1;          }

        /** ****************************************************************************************
         * Sets this to null state and in addition to empty state.
         ******************************************************************************************/
        public void    setNull()        { buf= null;  start= 0; end= -1;   }

        /** ****************************************************************************************
         * Sets the represented region to zero length by setting end to start -1.
         ******************************************************************************************/
        public void    clear()          { end= start - 1;                  }

        /** ****************************************************************************************
         * @return true if this represents a null string
         ******************************************************************************************/
        public boolean isNull()         { return buf == null;              }

        /** ****************************************************************************************
         * @return true if this does not represent a null string
         ******************************************************************************************/
        public boolean isNotNull()      { return buf != null;              }

        /** ****************************************************************************************
         * Checks if represented region has a length of zero.
         * @return true if the represented region is empty.
         ******************************************************************************************/
        public boolean isEmpty()        { return   end < start;            }

        /** ****************************************************************************************
         * Checks if the represented region has a length of more than zero.
         * @return true if the length of the substring represented does not equal zero.
         ******************************************************************************************/
        public boolean isNotEmpty()     { return   end >= start;           }


        /** ****************************************************************************************
         * Retrieve the first character in the substring.
         * @return The character at the start of the represented region.
         *         If this %Substring empty or nulled, '\0' is returned.
         ******************************************************************************************/
        public char    charAtStart()
        {
              return isEmpty() ?  '\0'
                               :  buf[start];
        }

        /** ****************************************************************************************
         * Retrieve the last character in the substring.
         * @return The character at the start of the represented region.
         *         If this %Substring empty or nulled, '\0' is returned.
         ******************************************************************************************/
        public char    charAtEnd ()
        {
              return isEmpty() ?  '\0'
                               :  buf[end];
        }
        /** ****************************************************************************************
         * Retrieve the n-th character in the substring, counted from the end.
         * @param n The offset of the requested character. Attention: n is subtracted from the end.
         *          In other words, positive values peek towards the start of the region.
         * @return  The n-th character counted from the end of the represented region backwards.
         *          If this %Substring empty or nulled, or if n is out of bounds, '\0' is returned.
         ******************************************************************************************/
        public char    charAtEnd ( int n )
        {
            return      buf   == null
                    ||  n     <  0
                    ||  start >  end - n    ? '\0'
                                            :  buf[end - n];
        }

    /** ############################################################################################
     * @name Consume
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Retrieve and remove the first character in the substring.
         * @return The character at the start of the represented region.
         *         If this %Substring empty or nulled, '\0' is returned.
         ******************************************************************************************/
        public char consumeChar()
        {
              return isEmpty() ?  '\0'
                               :  buf[start++];
        }

        /** ****************************************************************************************
         * Retrieve and remove the last character in the substring.
         * @return The character at the start of the represented region.
         *         If this %Substring empty or nulled, '\0' is returned.
         ******************************************************************************************/
        public char consumeCharFromEnd()
        {
              return isEmpty() ?  '\0'
                               :  buf[end--];
        }


        /** ****************************************************************************************
         * Cuts the given number of characters from the end of the Substring and optionally
         * places the portion that was cut in parameter \p{target} (if provided).<br>
         * Parameter \p{regionLength} is checked to be between 0 and length. If negative, nothing
         * is cut and \p{target} is set empty. If \p{regionLength} is greater than this
         * objects' length, all contents is 'moved' to \p{target}.
         *
         * @param regionLength  The length of the region at the start to delete.
         * @param target        An optional target \b %Substring that receives the portion that
         *                      is cut from this object. Defaults to null.
         *
         * @return The new length of the substring.
         ******************************************************************************************/
        public int consumeCharFromEnd(int regionLength, Substring target  )
        {
            if ( regionLength < 0 )
            {
                if ( target != null )
                    target.clear();
                return  length();
            }
            if ( regionLength > length() )
                regionLength= length();


            if ( target != null )
                target.set( this, length() - regionLength, regionLength );

            end-= regionLength;
            return length();
        }

        /** ****************************************************************************************
         * Cuts the given number of characters from the end of the Substring.<br>
         * Parameter \p{regionLength} is checked to be between 0 and length. If negative, nothing
         * is cut. If \p{regionLength} is greater than this objects' length, all contents is cleared.
         *
         * @param regionLength  The length of the region at the start to delete.
         *
         * @return The new length of the substring.
         ******************************************************************************************/
        public int consumeCharFromEnd(int regionLength )
        {
            return consumeCharFromEnd( regionLength, null );
        }


        /** ****************************************************************************************
         * Checks if this object starts with the given character \p{consumable}. If it does, this
         * character is cut from this object.
         *
         * @param consumable        The consumable character
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.KEEP.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        public boolean consumeChar(char        consumable,
                                   Case        sensitivity,
                                   Whitespaces trimBeforeConsume )
        {
            if ( trimBeforeConsume == Whitespaces.TRIM )
                trimStart();

            if (    ( sensitivity == Case.SENSITIVE &&                       charAtStart()  !=                       consumable  )
                 || ( sensitivity == Case.IGNORE    && Character.toUpperCase(charAtStart()) != Character.toUpperCase(consumable) ) )
                return false;

            start++;
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP.
         *
         * @param consumable        The consumable character
         * @param sensitivity       The sensitivity of the comparison.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        public boolean consumeChar(char consumable, Case sensitivity )
        {
            return consumeChar( consumable, sensitivity, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP
         * and default parameter \p{sensitivity} with value \c Case.SENSITIVE.
         *
         * @param consumable        The consumable character
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        public boolean consumeChar(char consumable  )
        {
            return consumeChar( consumable, Case.SENSITIVE, Whitespaces.KEEP );
        }


        /** ****************************************************************************************
         * Checks if this object ends with the given character \p{consumable}. If it does, this
         * character is cut from the end of object.
         *
         * @param consumable The consumable character
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (right-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.KEEP.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        public boolean consumeCharFromEnd(char        consumable,
                                          Case        sensitivity,
                                          Whitespaces trimBeforeConsume )
        {
            if ( trimBeforeConsume == Whitespaces.TRIM )
                trimEnd();

            if (    ( sensitivity == Case.SENSITIVE &&                       charAtEnd()  !=                       consumable  )
                 || ( sensitivity == Case.IGNORE    && Character.toUpperCase(charAtEnd()) != Character.toUpperCase(consumable) ) )
                return false;

            end--;
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP.
         *
         * @param consumable    The consumable character
         * @param sensitivity   The sensitivity of the comparison.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        public boolean consumeCharFromEnd(char consumable, Case sensitivity )
        {
            return consumeCharFromEnd( consumable, sensitivity, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP
         * and default parameter \p{sensitivity} with value \c Case.SENSITIVE.
         *
         * @param consumable The consumable character
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        public boolean consumeCharFromEnd(char consumable )
        {
            return consumeCharFromEnd( consumable, Case.SENSITIVE, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Cuts the given number of characters from the beginning of the Substring and optionally
         * places the portion that was cut in parameter \p{target} (if provided).<br>
         * Parameter \p{regionLength} is checked to be between 0 and length. If negative, nothing
         * is cut and \p{target} is set empty. If \p{regionLength} is greater than this
         * objects' length, all contents is 'moved' to \p{target}.
         *
         * @param regionLength  The length of the region at the start to delete.
         * @param target        An optional target \b %Substring that receives the portion that
         *                      is cut from this object. Defaults to null.
         *
         * @return The new length of the substring.
         ******************************************************************************************/
        public int consumeChars(int regionLength, Substring target )
        {
            if ( regionLength < 0 )
            {
                if ( target != null )
                    target.clear();
                return  length();
            }
            if ( regionLength > length() )
                regionLength= length();

            if ( target != null )
                target.set( this, 0, regionLength );

            start+= regionLength;
            return length();
        }

        /** ****************************************************************************************
         * Cuts the given number of characters from the beginning of the Substring.<br>
         * Parameter \p{regionLength} is checked to be between 0 and length. If negative, nothing
         * is cut. If \p{regionLength} is greater than this objects' length, all contents cleared.
         *
         * @param regionLength  The length of the region at the start to delete.
         *
         * @return The new length of the substring.
         ******************************************************************************************/
        public int consumeChars(int regionLength )
        {
            return consumeChars( regionLength, null );
        }

        /** ****************************************************************************************
         * Searches \p{separator} and cuts the beginning of this string, including the separator.
         * What was consumed is returned, excluding the separator.
         *
         * If the separator is not found, all of this string is consumed and returned.
         *
         * @param target     The target substring.
         * @param separator  The separator to search. Defaults to <c>','</c>.
         *
         * @return The number of characters consumed.
         ******************************************************************************************/
        public int  consumeToken( Substring target, char separator )
        {
            int separatorPos= indexOfOrLength( separator );
            target.buf=   buf;
            target.start= start;
            target.end=   start + separatorPos - 1;

            start+= separatorPos + 1;
            if (start > end + 1)
                start= end + 1;
            return target.length();
        }

        /** ****************************************************************************************
         * Checks if this object starts with the given string \p{consumable}. If it does, this
         * string is cut from this object.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.KEEP.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public boolean consumeString(CharSequence consumable,
                                     Case        sensitivity,
                                     Whitespaces trimBeforeConsume )
        {
            if ( trimBeforeConsume == Whitespaces.TRIM )
                trimStart();

            if ( !startsWith( consumable, sensitivity ) )
                return false;

            start+= consumable.length();

            return true;
        }
        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public boolean consumeString(CharSequence consumable, Case sensitivity )
        {
            return consumeString( consumable, sensitivity, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP
         * and default parameter \p{sensitivity} with value \c Case.SENSITIVE.
         *
         * @param consumable        The consumable string
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public boolean consumeString(CharSequence consumable )
        {
            return consumeString( consumable, Case.SENSITIVE, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Checks if this object ends with the given string \p{consumable}. If it does, this
         * string is cut from the end of object.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (right-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.KEEP.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public boolean consumeStringFromEnd(CharSequence consumable,
                                            Case         sensitivity,
                                            Whitespaces  trimBeforeConsume )
        {
            if ( trimBeforeConsume == Whitespaces.TRIM )
                trimEnd();

            if ( !endsWith( consumable ) )
                return false;

            end-= consumable.length();
            return true;
        }
        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public boolean consumeStringFromEnd(CharSequence consumable, Case sensitivity )
        {
            return consumeStringFromEnd( consumable, sensitivity, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP
         * and default parameter \p{sensitivity} with value \c Case.SENSITIVE.
         *
         * @param consumable        The consumable string
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public boolean consumeStringFromEnd(CharSequence consumable )
        {
            return consumeStringFromEnd( consumable, Case.SENSITIVE, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Consumes a minimum of \p{minChars} of string \c consumable from the start of this
         * substring. If the minimum characters could not be found, nothing is consumed, otherwise
         * as much as possible.<br>
         * This method is useful for example to read commands from a string that may be
         * abbreviated.
         *
         * @param consumable        The consumable string.
         * @param minChars          The minimum amount of characters to consume. If \c 0 or
         *                          negative, the length of \p{consumable} is chosen.
         *                          Optional and defaults to \c 1.
         * @param sensitivity       The sensitivity of the comparison.
         *                          Defaults to \b Case.Ignore.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          first character consume operation.
         *                          Defaults to \b Whitespaces.KEEP.
         * @return The amount of characters consumed.
         ******************************************************************************************/
        public int consumePartOf(String           consumable,
                                 int              minChars,
                                 Case             sensitivity,
                                 Whitespaces      trimBeforeConsume )
        {
            if ( trimBeforeConsume == Whitespaces.TRIM )
                trimStart();

            if ( minChars <= 0 )
                minChars= consumable.length();

            if ( minChars == 0 || minChars > consumable.length() )
                return 0;

            int diff= indexOfFirstDifference( consumable, sensitivity, 0 );
            if( diff < minChars )
                return 0;
            consumeChars( diff );
            return diff;
        }

        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP.
         *
         * @param consumable        The consumable string.
         * @param minChars          The minimum amount of characters to consume.
         *                          Optional and defaults to \c 1
         * @param sensitivity       The sensitivity of the comparison.
         * @return The amount of characters consumed.
         ******************************************************************************************/
        public int consumePartOf(String       consumable,
                                 int          minChars,
                                 Case         sensitivity  )
        {
            return consumePartOf( consumable, minChars, sensitivity, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP and
         * \p{sensitivity} with value \b Case.Sensitive.
         *
         * @param consumable        The consumable string.
         * @param minChars          The minimum amount of characters to consume.
         *                          Optional and defaults to \c 1
         * @return The amount of characters consumed.
         ******************************************************************************************/
        public int consumePartOf(String           consumable,
                                 int              minChars     )
        {
            return consumePartOf( consumable, minChars, Case.IGNORE, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP,
         * \p{sensitivity} with value \b Case.Sensitive and \p{minChars} with value \c 1.
         *
         * @param consumable        The consumable string.
         * @return The amount of characters consumed.
         ******************************************************************************************/
        public int consumePartOf(String           consumable   )
        {
            return consumePartOf( consumable, 1, Case.IGNORE, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Consumes a field from the beginning of this substring, which is surrounded by
         * given start end end character identifiers. If both are the same, e.g. \c '"', then
         * the first occurrence of the end character is used. If they are not the same, e.g.
         * \c '<' and \c '>', then repeated start characters are counted and consumption only ends
         * when a corresponding amount of end characters has been found.
         *
         * @param  startChar  The start character of the field to consume.
         * @param  endChar    The end character of the field to consume.
         * @param  target     The target string to place the field in.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.Keep.
         * @return The string consumed. \b NullString on error (start/end character not found)
         ******************************************************************************************/
        public Substring  consumeField( char startChar, char endChar, Substring target,
                                        Whitespaces trimBeforeConsume )
        {
            if ( trimBeforeConsume == Whitespaces.TRIM )
                trimStart();

            target.setNull();

            if ( charAtStart() != startChar )
                return target;

            int cntStartChars= 1;
            for ( int i= start + 1; i <= end ; i++ )
            {
                char actChar= buf[i];
                if( actChar == endChar )
                {
                    if( --cntStartChars == 0 )
                    {
                        target.buf=   buf;
                        target.start= start + 1;
                        target.end=   i - 1;
                        start=        i + 1;
                        return target;
                    }
                }
                else if( actChar == startChar )
                    cntStartChars++;
            }

            return target;
        }

        /** ****************************************************************************************
         * Overloaded version of original method
         * providing default parameter \p{trimBeforeConsume} with value \b Whitespaces.KEEP.
         *
         * @param  startChar  The start character of the field to consume.
         * @param  endChar    The end character of the field to consume.
         * @param  target     The target string to place the field in.
         * @return The string consumed. \b NullString on error (start/end character not found)
         ******************************************************************************************/
        public Substring  consumeField( char startChar, char endChar, Substring target )
        {
            return consumeField( startChar, endChar, target, Whitespaces.KEEP );
        }

        /** ****************************************************************************************
         * Splits this substring into two parts. What remains in this object is the region
         * from 0 to \p{position}.
         * \p{target} receives the rest. If optional parameter \p{separatorWidth} is given,
         * this is subtracted from the front of \p{target}.
         *
         * @param position        The index where this object is split.
         * @param target          The target substring to receive the right part of the string.
         * @param separatorWidth  This does not change what remains in this object, but defines
         *                        the number of characters that are cut from the front of the
         *                        \p{target}. Defaults to 0.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring split( int position, Substring target, int separatorWidth )
        {
            CString.adjustRegion( length(), position, separatorWidth, _adjustedRegion );

            int restStart= _adjustedRegion[0] + _adjustedRegion[1];
            target.set( this, restStart, length() - restStart );
            end= start  + position -1;
            return this;
        }


    /** ############################################################################################
     * @name Comparison
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Compares a given region of a string with this instance. Regions that are out of bounds
         * get adjusted and then compared.
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
         * @return 0 if the contents of the string regions are equal (or if both regions are empty
         *           or out of range).<br>
         *         -1 if the instance is less than the given string.<br>
         *         +1 if the instance is greater than the given string or if given string is null.
         ******************************************************************************************/
        public int compareTo( CharSequence cmpString, Case sensitivity,
                              int cmpRegionStart, int cmpRegionLength )
        {
            // check null argument
            if ( buf == null   )       return  cmpString == null ? 0 : -1;
            if ( cmpString == null )
                return 1;

            // adjust source and compare regions
            CString.adjustRegion( cmpString.length(), cmpRegionStart, cmpRegionLength, _adjustedRegion );
            cmpRegionStart=   _adjustedRegion[0];
            cmpRegionLength=  _adjustedRegion[1];

            return CString.compareTo( cmpString, cmpRegionStart, cmpRegionLength,
                                      buf,                start,          length(),
                                      sensitivity );
        }

        /** ****************************************************************************************
         * Compares a given region of a string with this instance. Regions that are out of bounds
         * get adjusted and then compared.
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
            return compareTo( cmpString, sensitivity, cmpRegionStart, Integer.MAX_VALUE);
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
            return compareTo( cmpString, sensitivity, 0, Integer.MAX_VALUE);
        }

        /** ****************************************************************************************
         * Compares a given string with this instance.
         *
         * @param cmpString   An object of type String, StringBuffer or AString that is compared to
         *                    this.
         *
         * @return 0 if string are equal. -1 if the instance precedes given string, 1 the instance
         *         follows the given string (same as String.CompareTo), or if given string in null.
         ******************************************************************************************/
        public int compareTo( CharSequence cmpString )
        {
            return compareTo( cmpString, Case.SENSITIVE, 0, Integer.MAX_VALUE);
        }


        /** ****************************************************************************************
         * Compares this to the given object. Given object can be of type
         * - \ref com.aworx.lib.strings.AString "AString"
         * - %Substring
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
            if ( object instanceof Substring )      return equals( ((Substring)     object ), sensitivity );
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
         * @param cmpString The %AString that is compared to this %AString.
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
            if ( cmpString.length() != length() )
                return false;

            return 0 == compareTo( cmpString, sensitivity, 0, length() );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given AString equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString The %AString that is compared to this %AString.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( AString cmpString )
        {
            // null?
            if ( cmpString == null || cmpString.isNull() )
                return isNull();

            // same length?
            if ( cmpString.length() != length() )
                return false;

            return 0 == compareTo( cmpString, Case.SENSITIVE, 0, length() );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given String equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString The %AString that is compared to this %AString.
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
            if ( cmpString.length() != length() )
                return false;

            return 0 == compareTo( cmpString, sensitivity, 0, length() );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given String equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString The %AString that is compared to this %AString.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( String cmpString )
        {
            // null?
            if ( cmpString == null )
                return isNull();

            // same length?
            if ( cmpString.length() != length() )
                return false;

            return 0 == compareTo( cmpString, Case.SENSITIVE, 0, length() );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given other \b %Substring equals to what this object
         * represents.
         * True is returned if both are zero length or \c null.
         *
         * @param cmpString A Substring that is compared to this %AString.
         * @param sensitivity   Case sensitivity of the comparison.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( Substring cmpString, Case sensitivity )
        {
            // null?
            if ( cmpString == null )
                return isNull();

            // same length?
            if ( cmpString.length() != length() )
                return false;

            return containsAt( cmpString, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given other \b %Substring equals to what this object
         * represents.
         * True is returned if both are zero length or \c null.
         *
         * @param cmpString A Substring that is compared to this %AString.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( Substring cmpString )
        {
            // null?
            if ( cmpString == null )
                return isNull();

            // same length?
            if ( cmpString.length() != length() )
                return false;

            return containsAt( cmpString, 0, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given CharSequence equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString A CharSequence that is compared to this %AString.
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
            if ( cmpString.length() != length() )
                return false;

            return containsAt( cmpString, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Tests and returns true, if the given CharSequence equals to what this object
         * represents. True is returned if both are zero length or \c null.
         *
         * @param cmpString A CharSequence that is compared to this %AString.
         *
         * @return    true, if contents of this and the given %AString are equal
         ******************************************************************************************/
        public boolean equals( CharSequence cmpString )
        {
            // null?
            if ( cmpString == null )
                return isNull();

            // same length?
            if ( cmpString.length() != length() )
                return false;

            return containsAt( cmpString, 0, Case.SENSITIVE );
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
            if ( pos < 0 )
                return false;
            return CString.containsAt( needle, buf, start + pos, end + 1, sensitivity );
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
            if ( pos < 0 )
                return false;
            return CString.containsAt( needle, buf, start + pos, end + 1, Case.SENSITIVE );
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
            if ( pos < 0 )
                return false;
            return CString.containsAt( needle != null ?  needle.buffer() : null, 0,
                                       needle != null ?  needle.length() : 0,
                                       buf, start + pos, end + 1,
                                       sensitivity     );
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
            if ( pos < 0 )
                return false;
            return CString.containsAt( needle != null ? needle.buffer() : null, 0,
                                       needle != null ? needle.length() : 0,
                                       buf, start + pos, end + 1,
                                       Case.SENSITIVE     );
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
        public boolean containsAt( Substring needle, int pos, Case sensitivity )
        {
            if ( pos < 0 )
                return false;
            return needle != null ? CString.containsAt( needle.buf,    needle.start,   needle.length(),
                                                        buf, start + pos, end + 1,
                                                        sensitivity     )
                                  : CString.containsAt( null, 0, 0,
                                                        buf, start + pos, end + 1,
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
        public boolean containsAt( Substring needle, int pos )
        {
            if ( pos < 0 )
                return false;
            return needle != null ? CString.containsAt( needle.buf,    needle.start,   needle.length(),
                                                        buf, start + pos, end + 1,
                                                        Case.SENSITIVE     )
                                  : CString.containsAt( null, 0, 0,
                                                        buf, start + pos, end + 1,
                                                        Case.SENSITIVE     );
        }

        /** ****************************************************************************************
         * Checks if this Substring starts with the given sequence.
         *
         * @param needle        The CharSequence to search. If s is null or empty, false is returned.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( CharSequence needle, Case sensitivity )
        {
            return CString.containsAt( needle, buf, start, end + 1, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if this Substring starts with the given sequence.
         *
         * @param needle        The CharSequence to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( CharSequence needle )
        {
            return CString.containsAt( needle, buf, start, end + 1, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Checks if this Substring starts with the given sequence.
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
         * Checks if this Substring starts with the given sequence.
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
         * Checks if this Substring starts with the given sequence.
         *
         * @param needle        The Substring to search. If s is null or empty, false is returned.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( Substring needle, Case sensitivity )
        {
            return containsAt( needle, 0, sensitivity );
        }

        /** ****************************************************************************************
         * Checks if this Substring starts with the given sequence.
         *
         * @param needle        The Substring to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean startsWith( Substring needle )
        {
            return containsAt( needle, 0, Case.SENSITIVE );
        }

        /** ****************************************************************************************
         * Checks if this Substring ends with the given sequence.
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
            return CString.containsAt( needle,
                                       buf,   end + 1 - needle.length(),   end + 1,
                                       sensitivity     );
        }

        /** ****************************************************************************************
         * Checks if this Substring ends with the given sequence.
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
         * Checks if this Substring ends with the given sequence.
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
            return CString.containsAt( needle.buffer(), 0,   needle.length(),
                                       buf,   end + 1 - needle.length(),   end + 1,
                                       sensitivity     );
        }

        /** ****************************************************************************************
         * Checks if this Substring ends with the given sequence.
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
         * Checks if this Substring ends with the given sequence.
         *
         * @param needle        The Substring to search. If s is null or empty, false is returned.
         * @param sensitivity   Case sensitivity of the operation.
         *                      Optional and defaults to Case.Sensitive.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean endsWith  ( Substring needle, Case sensitivity )
        {
            if ( needle == null )
                return true;
            return CString.containsAt( needle.buf,      needle.start,   needle.length(),
                                       buf,   end + 1 - needle.length(),   end + 1,
                                       sensitivity     );
        }

        /** ****************************************************************************************
         * Checks if this Substring ends with the given sequence.
         *
         * @param needle        The Substring to search. If s is null or empty, false is returned.
         *
         * @return  true if this starts with the given sequence, false if not.
         ******************************************************************************************/
        public boolean endsWith  ( Substring needle )
        {
            return endsWith( needle, Case.SENSITIVE );
        }


    /** ############################################################################################
     * @name Search
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Search a character in the buffer.
         *
         * @param needle        The character to search.
         * @param startIdx      The index to start the search at. Optional and defaults to \c 0.
         *
         * @return  -1 if the character is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOf( char needle, int startIdx )
        {
            // check
            if ( startIdx < 0 )
                startIdx= 0;
            else if ( startIdx >= length() )
                return -1;

            // search
            startIdx+= start;
            while ( startIdx <= end )
            {
                if ( needle == buf[ startIdx ] )
                    return startIdx - start;
                startIdx++;
            }

            // not found
            return -1;
        }

        /** ****************************************************************************************
         * Searches the given character.
         * @param  c The character to search.
         * @return  The index of the character within this substring, \c -1 if the character is not
         *          found.
         ******************************************************************************************/
        public int  indexOf( char c )
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
         * @return  This strings #length if the character \p{needle} is not found.
         *          Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int    indexOfOrLength( char needle )
        {
            int idx= start;
            while ( idx <= end && needle != buf[ idx ])
                idx++;

            return idx - start;
        }

        /** ****************************************************************************************
         * Like #indexOf but in case the character is not found, this method returns the length of
         * this string instead of \c -1.
         * Depending on the invocation context, the choice for the right version of this method may
         * lead to shorter and more efficient code.
         *
         * @param needle    The character to search for.
         * @param startIdx  The index in this to start searching the character.
         * @return  This strings #length if the character \p{needle} is not found.
         *          Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int    indexOfOrLength( char needle, int startIdx )
        {
            int length = length();

            if      ( startIdx < 0 )              startIdx= 0;
            else if ( startIdx >= length )        return length;
            while ( startIdx < length && needle != buf[ startIdx ])
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
            int length= length();
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return -1;
            int idx=  CString.indexOfString( needle, buf, start + startIdx, length - startIdx, sensitivity );
            return  idx < 0 ?  -1 : idx - start;
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
         * Searches the first difference with given string.
         * If this string starts with \p{needle}, then the length of \p{needle} is returned.
         *
         * @param needle       The String to search.
         * @param sensitivity  Case sensitivity of the comparison.
         *                     Optional and defaults to \b Case.SENSITIVE.
         * @param startIdx     The index to start the search at.
         *                     Optional and defaults to \c 0.
         * @return   The index of the first difference found in \p{needle} or the neele's length.
         ******************************************************************************************/
        public int indexOfFirstDifference(CharSequence needle, Case sensitivity, int startIdx  )
        {
            int length= length();
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return 0;

            return  CString.indexOfFirstDifference( buf, start + startIdx, length - startIdx, needle, sensitivity );
        }

        /** ****************************************************************************************
         * Overloaded version providing default paramter \p{startIdx} with value \c 0.
         *
         * @param needle       The String to search.
         * @param sensitivity  Case sensitivity of the comparison.
         *                     Optional and defaults to \b Case.SENSITIVE.
         * @return    -1 if the \e String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOfFirstDifference(CharSequence needle, Case sensitivity  )
        {
            return  indexOfFirstDifference( needle, sensitivity, 0 );
        }

        /** ****************************************************************************************
         * Overloaded version providing default paramter \p{startIdx} with value \c 0 and
         * \p{sensitivity} with value \b Case.SENSITIVE.
         *
         * @param needle       The String to search.
         * @return    -1 if the \e String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int indexOfFirstDifference(CharSequence needle   )
        {
            return  indexOfFirstDifference( needle, Case.SENSITIVE, 0 );
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
            int length= length();
            if ( startIdx < 0       ) startIdx= 0;
            if ( startIdx >= length ) return   -1;

            int idx= CString.indexOfAnyInRegion( buf, start + startIdx, length - startIdx, needles, inclusion );
            return idx < 0 ? -1  : idx - start;
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
            return indexOfAny( needles, inclusion, 0 );
        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         * The search starts at the given index and goes backward.
         * For forward search, see \ref indexOfAny(char[] p, Inclusion, int) "indexOfAny".
         *
         * @param needles    Characters to be searched for.
         * @param inclusion  Denotes whether the search returns the first index that holds a value
         *                   that is included or that is not excluded in the set of needle
         *                   characters.
         * @param startIdx   The index to start the search at. The value is cropped to be in
         *                   the bounds of 0 and the length of this object minus one.
         *                   Defaults to the length of this object.
         *
         * @return The index of the first character found which is included, respectively not
         *         included, in the given set of characters.
         *         If nothing is found, -1 is returned.
         ******************************************************************************************/
        public int lastIndexOfAny( char[] needles, Inclusion inclusion, int startIdx )
        {
            int length= length();
            if ( startIdx < 0       ) return -1;
            if ( startIdx >= length ) startIdx=  length - 1;
            int idx= CString.lastIndexOfAny( buf, start, startIdx + 1, needles, inclusion );
            return idx < 0 ? -1  : idx - start;

        }

        /** ****************************************************************************************
         * Returns the index of the first character which is included, respectively <em>not</em>
         * included in a given set of characters.
         * The search starts at the end and goes backward.
         * For forward search, see \ref indexOfAny(char[] p, Inclusion, int) "indexOfAny".
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
            return  lastIndexOfAny( needles, inclusion, Integer.MAX_VALUE);
        }


    /** ############################################################################################
     * @name Trim
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Moves the start marker to the first character not found in parameter \p{whiteSpaces}.
         * @param whiteSpaces  The characters used for trimming. Defaults to
         *                     \ref com.aworx.lib.strings.CString.DEFAULT_WHITESPACES "CString.DEFAULT_WHITESPACES".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring trimStart( char[] whiteSpaces )
        {
            if ( end - start >= 0 )
            {
                int idx= CString.indexOfAnyInRegion( buf, start,  length(), whiteSpaces, Inclusion.EXCLUDE );
                if(  idx < 0 )
                    clear();
                else
                    start= idx;

            }
            return this;
        }

        /** ****************************************************************************************
         * Invokes #trimStart(char[] whiteSpaces) providing default parameter
         * \ref com.aworx.lib.strings.CString.DEFAULT_WHITESPACES "CString.DEFAULT_WHITESPACES".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring trimStart()
        {
            return trimStart( CString.DEFAULT_WHITESPACES);
        }

        /** ****************************************************************************************
         * Moves the start marker to the first character not found in parameter \p{whiteSpaces}.
         * @param whiteSpaces  The characters used for trimming. Defaults to
         *                     \ref com.aworx.lib.strings.CString.DEFAULT_WHITESPACES "CString.DEFAULT_WHITESPACES".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring trimEnd( char[] whiteSpaces )
        {
            if ( end - start >= 0 )
                end=  CString.lastIndexOfAny( buf, start,  length(), whiteSpaces, Inclusion.EXCLUDE );
            return this;
        }

        /** ****************************************************************************************
         * Invokes #trimEnd(char[] whiteSpaces) providing default parameter
         * \ref com.aworx.lib.strings.CString.DEFAULT_WHITESPACES "CString.DEFAULT_WHITESPACES".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring trimEnd()
        {
            return trimEnd( CString.DEFAULT_WHITESPACES);
        }

        /** ****************************************************************************************
         * Invokes #trimStart and #trimEnd.
         * @param whiteSpaces  The characters used for trimming. Defaults to
         *                     \ref com.aworx.lib.strings.CString.DEFAULT_WHITESPACES "CString.DEFAULT_WHITESPACES".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring   trim( char[] whiteSpaces )
        {
            return trimEnd( whiteSpaces ).trimStart( whiteSpaces );
        }

        /** ****************************************************************************************
         * Invokes #trim(char[] whiteSpaces) providing default parameter
         * \ref com.aworx.lib.strings.CString.DEFAULT_WHITESPACES "CString.DEFAULT_WHITESPACES".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring   trim()
        {
            return trim( CString.DEFAULT_WHITESPACES);
        }

    /** ############################################################################################
     * @name Conversion
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Copies the string region represented by this object into the given AString
         * @param target The target AString to copy the region this object represents to.
         * @param append If true, the target AString is not cleared. Defaults to false.
         ******************************************************************************************/
        public void   copyTo( AString target, boolean append )
        {
            if( !append )
                target.clear();
            if ( isNotEmpty() )
                target._NC( buf, start, length() );
        }

        /** ****************************************************************************************
         * Copies the string region represented by this object into the given AString.
         * The AString will be cleared before copying.
         * @param target The target AString to copy the region this object represents to.
         ******************************************************************************************/
        public void    copyTo( AString target )
        {
            copyTo( target, false );
        }

        /** ****************************************************************************************
         * Overrides Object.ToString(). Copies the string region represented by this object into
         * a new string.
         * @returns A String with the contents of this sub-string.
         ******************************************************************************************/
        @Override
        public String  toString()
        {
            if ( isEmpty() )
                return "";
            return new String( buf, start, end-start + 1 );
        }

        /** ****************************************************************************************
         * Creates a String containing a copy of a region of the this Substring.
         *
         * @param regionStart   The start index of the region in this to create the string from.
         * @param regionLength  The maximum length of the region to create the string from.
         *                      Defaults to Integer.MAX_VALUE.
         *
         * @return A String that represents the specified sub region of this object.
         ******************************************************************************************/
        public String  toString( int regionStart, int regionLength )
        {
            CString.adjustRegion( length(), regionStart, regionLength, _adjustedRegion );

            if ( isEmpty() || regionLength == 0)
                return "";

            return new String( buf, start + _adjustedRegion[0], _adjustedRegion[1] );
        }

        /** ****************************************************************************************
         * Overloaded version providing default parameter \p{regionLength} as \c Integer.MAX_VALUE.
         *
         * @param regionStart   The start index of the region in this to create the string from.
         *
         * @return A String that represents the specified sub region of this object.
         ******************************************************************************************/
        public String  toString( int regionStart )
        {
            return toString( regionStart, Integer.MAX_VALUE );
        }

        /** ****************************************************************************************
         * Consumes all characters \c '0' to \c '9' at the start of this object and stores the
         * number value they represent in #consumedLong.
         * <br>Unlike with #consumeInt or #consumeDec, no sign, whitespaces or group characters are
         * consumed.
         *
         * @return  \c true if an integer was found, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeDecDigits()
        {
            consumedLong= NumberFormat.parseDecDigits( buf, start, end, _adjustedRegion );
            if( _adjustedRegion[0] == start )
                return false;

            start= _adjustedRegion[0];
            return true;
        }

        /** ****************************************************************************************
         * Consumes a long integer value in decimal, binary, hexadecimal or octal format from
         * the start of the string by invoking method
         * \ref com.aworx.lib.strings.NumberFormat.parseInt "NumberFormat.parseInt"
         * on the given \p{numberFormat} instance.<br>
         Parameter \p{numberFormat} defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to 'international' settings (not using the locale) and therefore
         * also not parsing grouping characters.
         *
         * @param numberFormat Defines the input format. Optional and defaults to \c null.
         *
         * @return  \c true if an integer was found, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeInt( NumberFormat numberFormat )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.computational;

            consumedLong= numberFormat.parseInt( buf, start, end, _adjustedRegion );
            if( _adjustedRegion[0] == start )
                return false;

            start= _adjustedRegion[0];
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #consumeInt(NumberFormat) providing default value \c null for
         * parameter \p{numberFormat} (which selects gloabl object
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational").
         *
         * @return  \c true if an value could be parsed, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeInt()
        {
            return consumeInt( null );
        }

        /** ****************************************************************************************
         * Consumes an unsigned 64-bit integer in standard decimal format at the given position
         * from the start of this string. This is done, by invoking
         * \ref com.aworx.lib.strings.NumberFormat.parseDec "NumberFormat.parseDec"
         * on the given \p{numberFormat} instance.<br>
         Parameter \p{numberFormat} defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail.
         * For reading signed integer values, see methods #consumeInt, for floating point numbers
         * #consumeFloat.
         *
         * For more information on number conversion, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * \note Because Java does not support unsigned integer, the value to read is limited to
         *       <c>Long.MAX_VALUE</c> in this language implementation of \b %ALib.
         *
         *
         * @param numberFormat Defines the input format. Optional and defaults to \c null.
         *
         * @return  \c true if an integer was found, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeDec( NumberFormat numberFormat )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.computational;

            consumedLong= numberFormat.parseDec( buf, start, end, _adjustedRegion );
            if( _adjustedRegion[0] == start )
                return false;

            start= _adjustedRegion[0];
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #consumeDec(NumberFormat) providing default value \c null for
         * parameter \p{numberFormat} (which selects gloabl object
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational").
         *
         * @return  \c true if an value could be parsed, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeDec()
        {
            return consumeDec( null );
        }

        /** ****************************************************************************************
         * Consumes an unsigned 64-bit integer in binary format at the given position
         * from this string. This is done, by invoking
         * \ref com.aworx.lib.strings.NumberFormat.parseBin "NumberFormat.parseBin"
         * on the given \p{numberFormat} instance.<br>
         Parameter \p{numberFormat} defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * For more information on number conversion, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * \note Although Java does not support unsigned integer, the value that is read with this
         *       method is correct in respect to the bits set in the signed value returned.
         *       In other words, if the most significant bit (#64), is set, the return value is
         *       negative.
         *
         * @param numberFormat Defines the input format. Optional and defaults to \c null.
         *
         * @return  \c true if an integer was found, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeBin( NumberFormat numberFormat )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.computational;

            consumedLong= numberFormat.parseBin( buf, start, end, _adjustedRegion );
            if( _adjustedRegion[0] == start )
                return false;

            start= _adjustedRegion[0];
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #consumeBin(NumberFormat) providing default value \c null for
         * parameter \p{numberFormat} (which selects gloabl object
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational").
         *
         * @return  \c true if an value could be parsed, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeBin()
        {
            return consumeBin( null );
        }

        /** ****************************************************************************************
         * Reads an unsigned 64-bit integer in hexadecimal format at the given position
         * from this \b %AString. This is done, by invoking
         * \ref com.aworx.lib.strings.NumberFormat.parseHex "NumberFormat.parseHex"
         * on the given \p{numberFormat} instance.<br>
         Parameter \p{numberFormat} defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * For more information on number conversion, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * \note Although Java does not support unsigned integer, the value that is read with this
         *       method is correct in respect to the bits set in the signed value returned.
         *       In other words, if the most significant bit (#64), is set, the return value is
         *       negative. For this, 16 hexadecimal digits need to be read and the first of
         *       them needs to be greater or equal to \b 0x8.
         *
         * @param numberFormat Defines the input format. Optional and defaults to \c null.
         *
         * @return  \c true if an integer was found, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeHex( NumberFormat numberFormat )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.computational;

            consumedLong= numberFormat.parseHex( buf, start, end, _adjustedRegion );
            if( _adjustedRegion[0] == start )
                return false;

            start= _adjustedRegion[0];
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #consumeHex(NumberFormat) providing default value \c null for
         * parameter \p{numberFormat} (which selects gloabl object
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational").
         *
         * @return  \c true if an value could be parsed, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeHex()
        {
            return consumeHex( null );
        }

        /** ****************************************************************************************
         * Consumes an unsigned 64-bit integer in octal format at the given position
         * from this string. This is done, by invoking
         * \ref com.aworx.lib.strings.NumberFormat.parseOct "NumberFormat.parseOct"
         * on the given \p{numberFormat} instance.<br>
         Parameter \p{numberFormat} defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * For more information on number conversion, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * \note Although Java does not support unsigned integer, the value that is read with this
         *       method is correct in respect to the bits set in the signed value returned.
         *       In other words, if the most significant bit (#64), is set, the return value is
         *       negative. For this, 22 octal digits need to be read with the first being \c 1.
         *
         * @param numberFormat Defines the input format. Optional and defaults to \c null.
         *
         * @return  \c true if an integer was found, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeOct( NumberFormat numberFormat )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.computational;

            consumedLong= numberFormat.parseOct( buf, start, end, _adjustedRegion );
            if( _adjustedRegion[0] == start )
                return false;

            start= _adjustedRegion[0];
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #consumeOct(NumberFormat) providing default value \c null for
         * parameter \p{numberFormat} (which selects gloabl object
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational").
         *
         * @return  \c true if an value could be parsed, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeOct()
        {
            return consumeOct( null );
        }

        /** ****************************************************************************************
         * Consumes a floating point number at the given position from this \b %AString.
         * This is done, by invoking
         * \ref com.aworx.lib.strings.NumberFormat.parseFloat "NumberFormat.parseFloat"
         * on the given \p{numberFormat} instance.<br>
         Parameter \p{numberFormat} defaults \c null. This denotes static singleton
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational"
         * which is configured to 'international' settings (not using the locale) and therefore
         * also not parsing - grouping characters.
         *
         * For more information on parsing options for floating point numbers and number
         * conversion in general, see class
         * \ref com.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * @param numberFormat Defines the input format. Optional and defaults to \c null.
         *
         * @return  \c true if a number was found and, \c false otherwise.
         ******************************************************************************************/
        public boolean consumeFloat( NumberFormat numberFormat )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.computational;

            consumedFloat= numberFormat.parseFloat( buf, start, end, _adjustedRegion );
            if( _adjustedRegion[0] == start )
                return false;

            start= _adjustedRegion[0];
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #consumeFloat(NumberFormat) providing default value \c null for
         * parameter \p{numberFormat} (which selects gloabl object
         * \ref com.aworx.lib.strings.NumberFormat.computational "NumberFormat.computational").
         *
         * @return  \c true if an value could be parsed, \c false otherwise.
         ******************************************************************************************/
        public boolean    consumeFloat()
        {
            return consumeFloat( null );
        }

    /** ############################################################################################
     * @name Java CharSequence interface implementation
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Returns a character of the sequence.
         * @param index     The index of the character to return.
         * @return   The character at the given index.
         *          If this %Substring empty or nulled, or if n is out of bounds, '\0' is returned.
         ******************************************************************************************/
        @Override
        public char     charAt(int index)
        {
            return      buf == null
                    ||  index <  0
                    ||  end   <  start + index  ? '\0'
                                                :  buf[start + index];
        }

        /** ****************************************************************************************
         * Reports an \b %ALib error (using \ref com.aworx.lib.lang.ReportWriter "ReportWriter") and
         * returns null. The reason for this behavior is to disallow the usage of AString within
         * (system) methods that create sub sequences.
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
            com.aworx.lib.ALIB_DBG.ERROR( "Substring.subSequence() called. This is not supported" );
            return null;
        }

        /** ****************************************************************************************
         * Standard Java Object hashCode method.
         *
         * @return  Result of parents' \b %hashCode.
         ******************************************************************************************/
        @Override
        public int hashCode()
        {
            return super.hashCode();
        }

} // class Substring



