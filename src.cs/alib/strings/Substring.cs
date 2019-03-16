// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Linq;
using System.Text;
using cs.aworx.lib.lang;

namespace cs.aworx.lib.strings  {

/** ************************************************************************************************
 *  This class is used for defining a region (sub-string) on an existing character array which
 *  is provided. This class will not manipulate the underlying
 *  data. In particular, there is no terminating zero written into the data.
 *
 *  The represented region is defined by the two fields #Start and #End. The fields are
 *  public accessible.
 *  In general, while working with a %Substring, the size of it should shrink, e.g. by trimming
 *  but should not grow.
 *  However, if the code using this class is "sure" that enlarging the region
 *  does violate the bounds of the buffer, fields #Start and #End might be modified from outside.
 *
 *  If created or set using a reference of class AString, the buffer of AString is <em>not</em>
 *  copied. This allows efficient operations on sub-strings of class AString. However, the source
 *  string must not be changed (or only in a controlled way) during the use the %Substring instance.
 *
 *  Objects of this class can be reused by freshly initializing them using one of the overloaded
 *  \b Set methods.
 *
 *  \note
 *    To generate Substrings which are separated by a delimiter character within a
 *    character array, use class
 *    \ref cs.aworx.lib.strings.util.Tokenizer "Tokenizer".
 *  <p>
 *
 *  \note
 *    In the Java and C# versions of ALib, due to the language design, fields #Start and #End have
 *    to be used to define the substring on a field #Buf, the character buffer. This forces
 *    a \e reimplementation of a bigger portion of the interface of class
 *    \ref cs.aworx.lib.strings.AString "AString". In the C++ version of ALib, there is a
 *    richer family of string classes that fully integrates with zero terminated <em>C strings</em>,
 *    standard C++ strings and 3rd party string libraries. Neither the fields \e %start and \e %end
 *    are necessary, nor the aforementioned reimplementation. Consequently, when directly accessing
 *    public fields #Buf, #Start and #End, the code gets incompatible to C++ code.
 **************************************************************************************************/
public class Substring
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
        /**  The character array we work on. */
        public  char[]        Buf;

        /**  Start marker within buf */
        public int            Start;

        /**  End marker within buf (points to the last character) */
        public int            End;

        /// The hash value. Has to be set dirty (0) whenever String is changed from
        /// outside!.
        protected     int     hash                                                               =0;


    /** ############################################################################################
     * @name Constructors
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         *  Empty Constructor. Sets this sub-string to 'null'
         ******************************************************************************************/
        public Substring()
        {
            SetNull();
        }

        /** ****************************************************************************************
         *  Constructs the %Substring on the given String. The String's data is copied.
         *  To avoid memory allocations (for copy operation) it is preferred to use an AString as
         *  input wherever appropriate.
         *  @param src     The string we work with.
         *  @param start   The start index of the substring within the given \e String.
         *  @param length  The number of characters to include from the given \e String.
         *                 If negative, length of the provided \e src is used.
         *                 Defaults to -1.
         ******************************************************************************************/
        public Substring( String src, int start= 0, int length= -1 )
        {
            Set( src, start, length );
        }

        /** ****************************************************************************************
         *  Copy constructor.
         *
         *  @param src        The substring to copy.
         *  @param start      The start index of the substring within the given \e Substring.
         *  @param length     The number of characters to include from the given \e Substring.
         *                    If negative, length of the provided \e src is used.
         *                    Defaults to -1.
         ******************************************************************************************/
        public Substring( Substring src, int start= 0, int length= -1  )
        {
            Set( src, start, length );
        }

        /** ****************************************************************************************
         *  Constructs the %Substring on the given AString. Start and end markers will be cover
         *  all of AString.
         *  start and the  end of the given AString.
         *  @param src     The string we work with.
         *  @param start   The start index of the substring within the given \e AString.
         *  @param length  The number of characters to include from the given \e AString.
         *                 If negative, length of the provided \e src is used.
         *                 Defaults to -1.
         ******************************************************************************************/
        public Substring( AString src, int start= 0, int length= -1 )
        {
            Set( src, start, length );
        }

        /** ****************************************************************************************
         *  Constructs the sub-string to work on the provided character array.
         *
         *  @param cstring The character array to work on.
         *  @param start   The start index of the substring within the given character array.
         *                 If negative, the character array is
         *  @param length  The number of characters to include from the given character array.
         *                 If negative, the character array is
         *                 assumed to be zero terminated and its length is evaluated using
         *                 the strlen() function from the standard C library.<br>
         *                 Defaults to -1.
         ******************************************************************************************/
        public Substring( char[] cstring, int start= 0, int length= -1 )
        {
            Set( cstring, start, length );
        }

    /** ############################################################################################
     * @name Set Data
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Sets the substring to represent a region of the given \b %Substring.
         *
         * @param src          The substring to copy from.
         * @param regionStart  The start of the region within \p{src}.  Defaults to 0.
         * @param regionLength The length of the region within \p{src}.
         *                     If negative, length of the provided \e src is used.
         *                     Defaults to -1.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring Set( Substring src, int regionStart =0, int regionLength =-1 )
        {
            Buf=    src.Buf;
            Start=  src.Start + regionStart;
            End=    Start + ( regionLength < 0 ? src.Length() - regionStart : regionLength ) -1;
            hash= 0;
            return this;
        }

        /** ****************************************************************************************
         *  Sets the substring to represent a region of the given \e String.
         *  @param src     The string we work with.
         *  @param start   The start index of the substring within the given \e String.
         *  @param length  The number of characters to include from the given \e String..
         *                 If negative, length of the provided \e src is used.
         *                 Defaults to -1.
        * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring Set( String src, int start =0, int length =-1 )
        {
            return Set( src.ToCharArray(), start, length );
        }

        /** ****************************************************************************************
         * Sets the substring to represent a region of the given \b %AString.
         *
         * @param src     The AString to work on.
         * @param start   The start index of the substring within the given \e AString.
         * @param length  The number of characters to include from the given \e AString.
         *                If negative, length of the provided \e src is used.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring   Set( AString src, int start, int length )
        {
            if ( src == null || src.IsNull() )
            {
                SetNull();
                return this;
            }

            if( length < 0 )
                length= src.Length();
            CString.AdjustRegion( src.Length(), ref start, ref length );
            Buf=    src.Buffer();
            Start=  start;
            End=    start + length -1;
            return this;
        }

        /** ****************************************************************************************
         * Sets the substring to represent a region of the given \b %AString.
         *
         * @param src     The AString to work on.
         * @param start   The start index of the substring within the given \e AString.
         *                Defaults to \c 0.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring   Set( AString src, int start )
        {
            if ( src == null || src.IsNull() )
            {
                SetNull();
                return this;
            }

            if( start < 0 )
                start= 0;
            int length= int.MaxValue;
            CString.AdjustRegion( src.Length(), ref start, ref length );
            Buf=    src.Buffer();
            Start=  start;
            End=    start + length -1;
            return this;
        }

        /** ****************************************************************************************
         * Sets the substring to represent the given \b %AString.
         *
         * @param src     The AString to work on.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring   Set( AString src )
        {
            if ( src == null || src.IsNull() )
            {
                SetNull();
                return this;
            }

            Buf=    src.Buffer();
            Start=  0;
            End=    src.Length() - 1;
            return this;
        }

        /** ****************************************************************************************
         *  Resets the sub-string to work on the provided character array.
         *
         *  @param src     The character array to work on.
         *  @param start   The start index of the substring within the given character array.
         *  @param length  The number of characters to include from the given character array.
         *                 If negative, length of the provided \e src is used.
         *                 Defaults to -1.
         * @return  \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring   Set(  char[] src, int start =0, int length =-1 )
        {
            if ( src == null )
            {
                SetNull();
                return this;
            }

            Buf=     src;
            Start=   start;
            End=     ( length < 0 ? src.Length : start + length ) -1;
            hash= 0;
            return this;
        }

    /** ############################################################################################
     * @name State and Character Access
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * @return  The length of the represented region.
         ******************************************************************************************/
        public int    Length()         {  return End - Start + 1;         }

        /** ****************************************************************************************
         * Sets this to null state and in addition to empty state.
         ******************************************************************************************/
        public void   SetNull()        { Buf= null;   hash= Start= 0; End= -1; }

        /** ****************************************************************************************
         * Sets the represented region to zero length by setting end to start -1.
         ******************************************************************************************/
        public void   Clear()          {  End= Start - 1; hash=0;         }

        /** ****************************************************************************************
         * @return true if this represents a null string
         ******************************************************************************************/
        public bool   IsNull()         { return Buf == null;              }

        /** ****************************************************************************************
         * @return true if this represents a null string
         ******************************************************************************************/
        public bool   IsNotNull()      { return Buf != null;              }

        /** ****************************************************************************************
         * Checks if represented region has a length of zero.
         * @return true if the represented region is empty.
         ******************************************************************************************/
        public bool   IsEmpty()        { return   End < Start;            }

        /** ****************************************************************************************
         * Checks if the represented region has a length of more than zero.
         * @return true if the length of the substring represented does not equal zero.
         ******************************************************************************************/
        public bool   IsNotEmpty()     { return   End >= Start;           }

        /** ****************************************************************************************
         * Retrieve the first character in the substring.
         * @return The character at the start of the represented region.
         *         If this %Substring empty or nulled, '\0' is returned.
         ******************************************************************************************/
        public char   CharAtStart()
        {
              return IsEmpty() ?  '\0'
                               :  Buf[Start];
        }

        /** ****************************************************************************************
         * Retrieve the n-th character in the substring.
         * @param n The offset of the requested character.
         * @return  The n-th character start of the represented region.
         *          If this %Substring empty or nulled, or if n is out of bounds, '\0' is returned.
         ******************************************************************************************/
        public char   CharAt( int n )
        {
            return      Buf == null
                    ||  n   <  0
                    ||  End <  Start + n    ? '\0'
                                            :  Buf[Start + n];
        }

        /** ****************************************************************************************
         * Retrieve the last character in the substring.
         * @return The character at the start of the represented region.
         *         If this %Substring empty or nulled, '\0' is returned.
         ******************************************************************************************/
        public char   CharAtEnd()
        {
              return IsEmpty() ?  '\0'
                               :  Buf[End];
        }
        /** ****************************************************************************************
         * Retrieve the n-th character in the substring, counted from the back.
         * @param n The offset of the requested character. Attention: n is subtracted from the end.
         *          In other words, positive values peek towards the start of the region.
         * @return  The n-th character counted from the end of the represented region backwards.
         *          If this %Substring empty or nulled, or if n is out of bounds, '\0' is returned.
         ******************************************************************************************/
        public char   CharAtEnd( int n )
        {
            return      Buf   == null
                    ||  n     <  0
                    ||  Start >  End - n    ? '\0'
                                            :  Buf[End - n];
        }

    /** ############################################################################################
     * @name Consume
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Retrieve and remove the first character in the substring.
         * @return The character at the start of the represented region.
         *         If this %Substring empty or nulled, '\0' is returned.
         ******************************************************************************************/
        public char   ConsumeChar()
        {
            hash= 0;
            return IsEmpty() ?  '\0'
                               :  Buf[Start++];
        }

        /** ****************************************************************************************
         * Retrieve and remove the last character in the substring.
         * @return The character at the start of the represented region.
         *         If this %Substring empty or nulled, '\0' is returned.
         ******************************************************************************************/
        public char   ConsumeCharFromEnd ()
        {
            hash= 0;
            return IsEmpty() ?  '\0'
                             :  Buf[End--];
        }

        /** ****************************************************************************************
         * Checks if this object starts with the given character \p{consumable}. If it does, this
         * character is cut from this object.
         *
         * @param consumable        The consumable character
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.Keep.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        public bool   ConsumeChar( char         consumable,
                                   Case         sensitivity         = Case.Sensitive,
                                   Whitespaces  trimBeforeConsume   = Whitespaces.Keep )
        {
            if ( trimBeforeConsume == Whitespaces.Trim )
                TrimStart();

            if (    ( sensitivity == Case.Sensitive &&              CharAtStart()  !=              consumable  )
                 || ( sensitivity == Case.Ignore    && Char.ToUpper(CharAtStart()) != Char.ToUpper(consumable) ) )
                return false;
            Start++;
            hash= 0;
            return true;
        }

        /** ****************************************************************************************
         * Checks if this object ends with the given character \p{consumable}. If it does, this
         * character is cut from the end of object.
         *
         * @param consumable The consumable character
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (right-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.Keep.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        public bool   ConsumeCharFromEnd( char         consumable,
                                          Case         sensitivity         = Case.Sensitive,
                                          Whitespaces  trimBeforeConsume   = Whitespaces.Keep )
        {
            if ( trimBeforeConsume == Whitespaces.Trim )
                TrimEnd();

            if (    ( sensitivity == Case.Sensitive &&              CharAtEnd()  !=              consumable  )
                 || ( sensitivity == Case.Ignore    && Char.ToUpper(CharAtEnd()) != Char.ToUpper(consumable) ) )
                return false;
            End--;
            hash= 0;
            return true;
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
        public int  ConsumeChars( int regionLength,  Substring target= null )
        {
            if ( regionLength < 0 )
            {
                if ( target != null )
                    target.Clear();
                return  Length();
            }
            if ( regionLength > Length() )
                regionLength= Length();

            if ( target != null )
                target.Set( this, 0, regionLength );

            Start+= regionLength;
            hash= 0;
            return Length();
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
        public int     ConsumeCharsFromEnd( int regionLength,  Substring target= null )
        {
            if ( regionLength < 0 )
            {
                if ( target != null )
                    target.Clear();
                return  Length();
            }
            if ( regionLength > Length() )
                regionLength= Length();

            if ( target != null )
                target.Set( this, Length() - regionLength, regionLength );

            End-= regionLength;
            hash= 0;
            return Length();
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
        public int  ConsumeToken( Substring target, char separator= ',' )
        {
            int separatorPos= IndexOfOrLength( separator );
            target.Buf=   Buf;
            target.Start= Start;
            target.End=   Start + separatorPos - 1;

            Start+= separatorPos + 1;
            if (Start > End + 1)
                Start= End + 1;
            return target.Length();
        }

        /** ****************************************************************************************
         * Checks if this object starts with the given string \p{consumable}. If it does, this
         * string is cut from this object.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.Keep.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public bool  ConsumeString( String       consumable,
                                    Case         sensitivity         = Case.Sensitive,
                                    Whitespaces  trimBeforeConsume   = Whitespaces.Keep )
        {
            if ( trimBeforeConsume == Whitespaces.Trim )
                TrimStart();

            if ( !StartsWith( consumable, sensitivity) )
                return false;

            Start+= consumable.Length;

            return true;
        }

        /** ****************************************************************************************
         * Checks if this object starts with the given string \p{consumable}. If it does, this
         * string is cut from this object.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.Keep.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public bool  ConsumeString( AString      consumable,
                                    Case         sensitivity         = Case.Sensitive,
                                    Whitespaces  trimBeforeConsume   = Whitespaces.Keep )
        {
            if ( trimBeforeConsume == Whitespaces.Trim )
                TrimStart();

            if ( !StartsWith( consumable, sensitivity ) )
                return false;

            Start+= consumable.Length();

            return true;
        }

        /** ****************************************************************************************
         * Checks if this object starts with the given string \p{consumable}. If it does, this
         * string is cut from this object.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.Keep.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public bool  ConsumeString( Substring    consumable,
                                    Case         sensitivity         = Case.Sensitive,
                                    Whitespaces  trimBeforeConsume   = Whitespaces.Keep )
        {
            if ( trimBeforeConsume == Whitespaces.Trim )
                TrimStart();

            if ( !StartsWith( consumable, sensitivity ) )
                return false;

            Start+= consumable.Length();

            return true;
        }

        /** ****************************************************************************************
         * Checks if this object ends with the given string \p{consumable}. If it does, this
         * string is cut from the end of object.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (right-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.Keep.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public bool  ConsumeStringFromEnd( String       consumable,
                                           Case         sensitivity         = Case.Sensitive,
                                           Whitespaces  trimBeforeConsume   = Whitespaces.Keep )
        {
            if ( trimBeforeConsume == Whitespaces.Trim )
                TrimEnd();

            if ( !EndsWith( consumable, sensitivity ) )
                return false;

            End-= consumable.Length;
            return true;
        }

        /** ****************************************************************************************
         * Checks if this object ends with the given string \p{consumable}. If it does, this
         * string is cut from the end of object.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (right-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.Keep.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public bool  ConsumeStringFromEnd( AString      consumable,
                                           Case         sensitivity         = Case.Sensitive,
                                           Whitespaces  trimBeforeConsume   = Whitespaces.Keep )
        {
            if ( trimBeforeConsume == Whitespaces.Trim )
                TrimEnd();

            if ( !EndsWith( consumable, sensitivity ) )
                return false;

            End-= consumable.Length();
            return true;
        }

        /** ****************************************************************************************
         * Checks if this object ends with the given string \p{consumable}. If it does, this
         * string is cut from the end of object.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (right-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces.Keep.
         * @return \c true, if this object was starting with \p{consumable} and consequently the
         *         string was cut.
         ******************************************************************************************/
        public bool  ConsumeStringFromEnd( Substring    consumable,
                                           Case         sensitivity         = Case.Sensitive,
                                           Whitespaces  trimBeforeConsume   = Whitespaces.Keep )
        {
            if ( trimBeforeConsume == Whitespaces.Trim )
                TrimEnd();

            if ( !EndsWith( consumable, sensitivity ) )
                return false;

            End-= consumable.Length();
            return true;
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
         *                          Defaults to \b Whitespaces.Keep.
         * @return The amount of characters consumed.
         ******************************************************************************************/
        public int     ConsumePartOf( String           consumable,
                                      int              minChars           = 1,
                                      lang.Case        sensitivity        = lang.Case.Ignore,
                                      lang.Whitespaces trimBeforeConsume  = lang.Whitespaces.Keep )
        {
            if ( trimBeforeConsume == lang.Whitespaces.Trim )
                TrimStart();

            if ( minChars <= 0 )
                minChars= consumable.Length;
            if ( minChars == 0 || minChars > consumable.Length )
                return 0;

            int diff= IndexOfFirstDifference( consumable, sensitivity, 0 );
            if( diff < minChars )
                return 0;
            ConsumeChars( diff );
            return diff;
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
        public Substring  ConsumeField( char startChar, char endChar, Substring target,
                                        lang.Whitespaces trimBeforeConsume  = lang.Whitespaces.Keep )
        {
            if ( trimBeforeConsume == lang.Whitespaces.Trim )
                TrimStart();

            target.SetNull();

            if ( CharAtStart() != startChar )
                return target;

            int cntStartChars= 1;
            for ( int i= Start + 1; i <= End ; i++ )
            {
                char actChar= Buf[i];
                if( actChar == endChar )
                {
                    if( --cntStartChars == 0 )
                    {
                        target.Buf=   Buf;
                        target.Start= Start + 1;
                        target.End=   i - 1;
                        Start=        i + 1;
                        return target;
                    }
                }
                else if( actChar == startChar )
                    cntStartChars++;
            }

            return target;
        }

        /** ****************************************************************************************
         * Consumes all characters \c '0' to \c '9' at the start of this object and stores the
         * number value they represent in \p{result}.
         * <br>Unlike with #ConsumeInt or #ConsumeDec, no sign, whitespaces or group characters are
         * consumed.
         *
         * @param[out] result  A reference to the result value.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeDecDigits( out ulong result )
        {
            int newStart= Start;
            result= NumberFormat.ParseDecDigits( Buf, ref newStart, End );
            if( newStart == Start )
                return false;

            Start= newStart;
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #ConsumeDecDigits(out ulong)
         * accepting an \p{int} value.
         *
         * @param[out] result  A reference to the result value.
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeDecDigits( out int result )
        {
            int newStart= Start;
            result= (int) NumberFormat.ParseDecDigits( Buf, ref newStart, End );
            if( newStart == Start )
                return false;

            Start= newStart;
            return true;
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
         * For more information on number conversion, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeInt( out long result, NumberFormat numberFormat= null )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.Computational;

            int newStart= Start;
            result= numberFormat.ParseInt( Buf, ref newStart, End );

            if( newStart == Start )
                return false;

            Start= newStart;
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #ConsumeInt(out long,NumberFormat =)
         * accepting an \p{int} value.
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeInt( out int result, NumberFormat numberFormat= null )
        {
            result= 0;
            long lResult;
            if( ConsumeInt( out lResult, numberFormat ) )
            {
                result= (int) lResult;
                return true;
            }
            return false;
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
         * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail.
         * For reading signed integer values, see methods #ConsumeInt, for floating point numbers
         * #ConsumeFloat.
         *
         * For more information on number conversion, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeDec( out ulong result, NumberFormat numberFormat= null )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.Computational;

            int newStart= Start;
            result= numberFormat.ParseDec( Buf, ref newStart, End );

            if( newStart == Start )
                return false;

            Start= newStart;
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #ConsumeDec(out ulong,NumberFormat =)
         * accepting an \p{uint} value.
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeDec( out uint result, NumberFormat numberFormat= null )
        {
            result= 0;
            ulong lResult;
            if( ConsumeDec( out lResult, numberFormat ) )
            {
                result= (uint) lResult;
                return true;
            }
            return false;
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
         * For more information on number conversion, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeBin( out ulong result, NumberFormat numberFormat= null )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.Computational;

            int newStart= Start;
            result= numberFormat.ParseBin( Buf, ref newStart, End );

            if( newStart == Start )
                return false;

            Start= newStart;
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #ConsumeBin(out ulong,NumberFormat =)
         * accepting an \p{uint} value.
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeBin( out uint result, NumberFormat numberFormat= null )
        {
            result= 0;
            ulong lResult;
            if( ConsumeBin( out lResult, numberFormat ) )
            {
                result= (uint) lResult;
                return true;
            }
            return false;
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
         * For more information on number conversion, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeHex( out ulong result, NumberFormat numberFormat= null )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.Computational;

            int newStart= Start;
            result= numberFormat.ParseHex( Buf, ref newStart, End );

            if( newStart == Start )
                return false;

            Start= newStart;
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #ConsumeHex(out ulong,NumberFormat =)
         * accepting an \p{uint} value.
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeHex( out uint result, NumberFormat numberFormat= null )
        {
            result= 0;
            ulong lResult;
            if( ConsumeHex( out lResult, numberFormat ) )
            {
                result= (uint) lResult;
                return true;
            }
            return false;
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
         * For more information on number conversion, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeOct( out ulong result, NumberFormat numberFormat= null )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.Computational;

            int newStart= Start;
            result= numberFormat.ParseOct( Buf, ref newStart, End );

            if( newStart == Start )
                return false;

            Start= newStart;
            return true;
        }

        /** ****************************************************************************************
         * Overloaded version of #ConsumeOct(out ulong,NumberFormat =)
         * accepting an \p{uint} value.
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool    ConsumeOct( out uint result, NumberFormat numberFormat= null )
        {
            result= 0;
            ulong lResult;
            if( ConsumeOct( out lResult, numberFormat ) )
            {
                result= (uint) lResult;
                return true;
            }
            return false;
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
         * For more information on parsing options for floating point numbers and number
         * conversion in general, see class
         * \ref cs.aworx.lib.strings.NumberFormat "NumberFormat".
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat Defines the input format.
         *                     Optional and defaults to \c null.
         *
         * @return  \c true if a number was consumed, \c false otherwise.
         ******************************************************************************************/
        public bool ConsumeFloat( out double result, NumberFormat numberFormat = null )
        {
            if ( numberFormat == null )
                numberFormat= NumberFormat.Computational;

            int newStart= Start;
            result= numberFormat.ParseFloat( Buf, ref newStart, End );

            if( newStart == Start )
                return false;

            Start= newStart;
            return true;
        }

        /** ****************************************************************************************
         * Splits this substring into two parts. What remains in this object is the region
         * from 0 to \p{position}.
         * \p{target} receives the rest. If \p{separatorWidth} is given, this is subtracted from
         * the front of \p{target}.
         *
         * @param position        The index where this object is split.
         * @param target          The target substring to receive the right part of the string.
         * @param separatorWidth  This does not change what remains in this object, but defines
         *                        the number of characters that are cut from the front of the
         *                        \p{target}. Defaults to 0.
         *
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring Split( int position, Substring target, int separatorWidth  =0 )
        {
            CString.AdjustRegion( Length(), ref position, ref separatorWidth );

            target.Set( this, position + separatorWidth, Length() - position - separatorWidth );
            End= Start  + position -1;
            return this;
        }

    /** ############################################################################################
     * @name Search
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Searches the given character.
         * @param needle        The character to search.
         * @param startIdx      The index to start the search at. Optional and defaults to \c 0.
         * @return  The index of the character within this substring, -1 if the character is not
         *          found.
         ******************************************************************************************/
        public int    IndexOf( char needle, int startIdx= 0 )
        {
            // check
            if      ( startIdx < 0 )            startIdx= 0;
            else if ( startIdx >= Length() )    return -1;

            // search
            startIdx+= Start;
            while ( startIdx <= End )
            {
                if ( needle == Buf[ startIdx ] )
                    return startIdx - Start;
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
            int idx= Start;
            while ( idx <= End && needle != Buf[ idx ])
                idx++;

            return idx - Start;
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
            int length = Length();

            if      ( startIdx < 0 )              startIdx= 0;
            else if ( startIdx >= length )        return length;
            while ( startIdx < length && needle != Buf[ startIdx ])
                startIdx++;

            return startIdx;
        }

        /** ****************************************************************************************
         * Search the given \e String in this.
         *
         * @param needle       The String to search.
         * @param startIdx     The index to start the search at. Optional and defaults to \c 0.
         * @param sensitivity  Case sensitivity of the comparison.
         *                     Optional and defaults to Case.Sensitive.
         * @return    -1 if the \e String is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int IndexOf( String needle, int startIdx= 0, Case sensitivity= Case.Sensitive  )
        {
            int length= Length();
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return -1;
            int idx=  CString.IndexOfString( needle, Buf, Start + startIdx, length - startIdx, sensitivity );
            return  idx < 0 ?  -1 : idx - Start;
        }

        /** ****************************************************************************************
         * Search the given \b %AString in the this.
         *
         * @param needle       The String to search.
         * @param startIdx     The index to start the search at. Optional and defaults to \c 0.
         * @param sensitivity  If \c true, the compare is case insensitive. Optional and defaults to
         *                     \c false.
         * @return    -1 if the string is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int IndexOf( AString needle, int startIdx= 0, Case sensitivity= Case.Sensitive  )
        {
            int length= Length();
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return -1;
            int idx= needle != null
                ? CString.IndexOfString( needle.Buffer(), 0, needle.Length(), Buf, Start + startIdx, length - startIdx, sensitivity )
                : CString.IndexOfString( null,            0, 0,               Buf, Start + startIdx, length - startIdx, sensitivity );
            return  idx < 0 ?  -1 : idx - Start;
        }

        /** ****************************************************************************************
         * Search the given \b %Substring in the this.
         *
         * @param needle       The string to search.
         * @param startIdx     The index to start the search at. Optional and defaults to \c 0.
         * @param sensitivity  If \c true, the compare is case insensitive. Optional and defaults to
         *                     \c false.
         * @return    -1 if the string is not found. Otherwise the index of first occurrence.
         ******************************************************************************************/
        public int IndexOf( Substring needle, int startIdx= 0, Case sensitivity= Case.Sensitive  )
        {
            int length= Length();
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return -1;
            int idx= needle != null
                ? CString.IndexOfString( needle.Buf, needle.Start, needle.Length(), Buf, Start + startIdx, length - startIdx, sensitivity )
                : CString.IndexOfString( null,       0,            0,               Buf, Start + startIdx, length - startIdx, sensitivity );
            return  idx < 0 ?  -1 : idx - Start;
        }

        /** ****************************************************************************************
         * Searches the first difference with given string.
         * If this string starts with \p{needle}, then the length of \p{needle} is returned.
         *
         * @param needle       The String to search.
         * @param sensitivity  Case sensitivity of the comparison.
         *                     Optional and defaults to \b Case.Sensitive.
         * @param startIdx     The index to start the search at. Optional and defaults to \c 0.
         * @return   The index of the first difference found in \p{needle} or the neele's length.
         ******************************************************************************************/
        public int IndexOfFirstDifference( String needle, Case sensitivity= Case.Sensitive, int startIdx= 0  )
        {
            int length= Length();
            if      ( startIdx < 0 )                startIdx= 0;
            else if ( startIdx >= length )          return 0;

            return  CString.IndexOfFirstDifference( Buf, Start + startIdx, length - startIdx, needle, sensitivity );
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
            if ( startIdx < 0         ) startIdx= 0;
            if ( startIdx >= Length() ) return   -1;

            int idx= CString.IndexOfAnyInRegion( Buf, Start + startIdx, Length() - startIdx, needles, inclusion );
            return idx < 0  ?  -1  :  idx - Start;
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
            if ( startIdx < 0         ) return -1;
            if ( startIdx >= Length() ) startIdx=  Length() - 1;
            int idx=  CString.LastIndexOfAny( Buf, Start, startIdx + 1, needles, inclusion );
            return idx < 0  ?  -1  :  idx - Start;
        }

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
            if ( IsNull()      )     return  needle == null ? 0 : -1;
            if ( needle == null)     return  +1;

            // adjust source and compare regions
            int cmpLength= needle.Length;
            CString.AdjustRegion( cmpLength, ref needleRegionStart, ref needleRegionLength );
            CString.AdjustRegion(  Length(), ref       regionStart, ref       regionLength );

            return CString.CompareTo( needle,    needleRegionStart,   needleRegionLength,
                                      Buf,     Start + regionStart,       regionLength,
                                      sensitivity);
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
            if ( IsNull()      )     return  needle == null ? 0 : -1;
            if ( needle == null)     return  +1;

            // adjust source and compare regions
            int cmpLength= needle.Length();
            CString.AdjustRegion( cmpLength, ref needleRegionStart, ref needleRegionLength );
            CString.AdjustRegion(  Length(), ref       regionStart, ref       regionLength );

            return CString.CompareTo( needle.Buffer(),  needleRegionStart, needleRegionLength,
                                             Buf,     Start + regionStart,       regionLength,
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
            if ( IsNull()      )     return  needle == null ? 0 : -1;
            if ( needle == null)     return  +1;

            // adjust source and compare regions
            int cmpLength= needle.Length;
            CString.AdjustRegion( cmpLength, ref needleRegionStart, ref needleRegionLength );
            CString.AdjustRegion(  Length(), ref       regionStart, ref       regionLength );

            return CString.CompareTo( needle,    needleRegionStart, needleRegionLength,
                                      Buf,     Start + regionStart,       regionLength,
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
            if ( IsNull()      )     return  needle == null ? 0 : -1;
            if ( needle == null)     return  +1;

            // adjust source and compare regions
            CString.AdjustRegion(    Length(), ref  regionStart, ref  regionLength );

            return CString.CompareTo( needle.Buf,  needle.Start,                 needle.Length(),
                                             Buf,         Start +  regionStart,  regionLength,
                                      sensitivity  );
        }

        /** ****************************************************************************************
         * Checks if the given String is located at the given position.
         * @param needle      The string to search.
         * @param pos         The position to look at.
         * @param sensitivity         Case sensitivity of the comparison.
         *                            Optional and defaults to Case.Sensitive.
         * @return  True if the given sequence is found at the given position. False otherwise .
         *
         ******************************************************************************************/
        public bool ContainsAt( String needle, int pos, Case sensitivity= Case.Sensitive )
        {
            if ( pos < 0 )
                return false;
            return CString.ContainsAt( needle, Buf, Start + pos, End + 1, sensitivity );
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
            if ( pos < 0 )
                return false;
            return CString.ContainsAt( needle, needleStart, needleLength,
                                       Buf,  Start + pos, End + 1,
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
            if ( pos < 0 )
                return false;
            return needle != null ? CString.ContainsAt( needle.Buffer(), 0, needle.Length(),
                                                        Buf,  Start + pos, End + 1,
                                                        sensitivity )
                                  : CString.ContainsAt( null, 0, 0,
                                                        Buf,  Start + pos, End + 1,
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
            if ( pos < 0 )
                return false;
            return needle != null ? CString.ContainsAt( needle.Buf, needle.Start, needle.Length(),
                                                        Buf,  Start + pos, End + 1,
                                                        sensitivity )
                                  : CString.ContainsAt( null, 0, 0,
                                                        Buf,  Start + pos, End + 1,
                                                        sensitivity );
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
            if ( o == null || IsNull() )
                return ( (o == null ) == IsNull() );

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
            if ( compareString.Length() != Length() )
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
            if ( compareString.Length != Length() )
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
            if ( compareString.Length() != Length() )
                return false;

            return ContainsAt( compareString.Buf, compareString.Start, Length(), 0, sensitivity );
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
                if ( ca.Length != Length() )
                    return false;
                return ContainsAt( ca, 0, Length(), 0, sensitivity );
            }

            ALIB_DBG.WARNING( "Unknown object type." );

            return false;
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

            return ContainsAt( needle, Length() - needle.Length, sensitivity );
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

            return ContainsAt( needle, Length() - needle.Length(), sensitivity );
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

            return ContainsAt( needle, Length() - needle.Length(), sensitivity );
        }


    /** ############################################################################################
     * @name Trim
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Moves the start marker to the first character not found in parameter \p{whiteSpaces}.
         * @param whiteSpaces  The characters used for trimming. Defaults to
         *                     \ref cs.aworx.lib.strings.CString.DefaultWhitespaces "CString.DefaultWhitespaces".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring TrimStart( char[] whiteSpaces )
        {
            if ( End - Start >= 0 )
            {
                int idx= CString.IndexOfAnyInRegion( Buf, Start,  Length(), whiteSpaces, Inclusion.Exclude );
                if(  idx < 0 )
                    Clear();
                else
                {
                    Start= idx;
                    hash= 0;
                }

            }
            return this;
        }

        /** ****************************************************************************************
         * Invokes #TrimStart(char[] whiteSpaces) providing default parameter
         * \ref cs.aworx.lib.strings.CString.DefaultWhitespaces "CString.DefaultWhitespaces".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring TrimStart()
        {
            return TrimStart( CString.DefaultWhitespaces );
        }

        /** ****************************************************************************************
         * Moves the start marker to the first character not found in parameter \p{whiteSpaces}.
         * @param whiteSpaces  The characters used for trimming. Defaults to
         *                     \ref cs.aworx.lib.strings.CString.DefaultWhitespaces "CString.DefaultWhitespaces".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring TrimEnd( char[] whiteSpaces )
        {
            if ( End - Start >= 0 )
            {
                End=  CString.LastIndexOfAny( Buf, Start,  Length(), whiteSpaces, Inclusion.Exclude );
                hash= 0;
            }

            return this;
        }

        /** ****************************************************************************************
         * Invokes #TrimEnd(char[] whiteSpaces) providing default parameter
         * \ref cs.aworx.lib.strings.CString.DefaultWhitespaces "CString.DefaultWhitespaces".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring   TrimEnd()
        {
            return TrimEnd( CString.DefaultWhitespaces );
        }

        /** ****************************************************************************************
         * Invokes #TrimStart and #TrimEnd .
         * @param whiteSpaces  The characters used for trimming. Defaults to
         *                     \ref cs.aworx.lib.strings.CString.DefaultWhitespaces "CString.DefaultWhitespaces".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring   Trim( char[] whiteSpaces )
        {
            return TrimEnd(whiteSpaces).TrimStart(whiteSpaces);
        }

        /** ****************************************************************************************
         * Invokes #Trim(char[] whiteSpaces) providing default parameter
         * \ref cs.aworx.lib.strings.CString.DefaultWhitespaces "CString.DefaultWhitespaces".
         * @return \c this to allow concatenated calls.
         ******************************************************************************************/
        public Substring   Trim()
        {
            return Trim( CString.DefaultWhitespaces );
        }

    /** ############################################################################################
     * @name Conversion
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Copies the string region represented by this object into the given AString
         * @param target The target AString to copy the region this object represents to.
         * @param append If true, the target AString is not cleared. Defaults to false.
         ******************************************************************************************/
        public void   CopyTo( AString target, bool append= false )
        {
            if( !append )
                target.Clear();
            if ( !IsEmpty() )
                target._NC( Buf, Start, Length() );
        }

        /** ****************************************************************************************
         * Overrides Object.ToString(). Copies the string region represented by this object into
         * a new string.
         * @returns A String with the contents of this sub-string.
         ******************************************************************************************/
        public override String ToString()
        {
            if ( IsEmpty() )
                return "";
            return new String( Buf, Start, End-Start + 1 );
        }


        /** ****************************************************************************************
         * Creates a String containing a copy of a region of the this Substring.
         *
         * @param regionStart   The start index of the region in this to create the string from.
         * @param regionLength  The maximum length of the region to create the string from.
         *                      Defaults to int.MaxValue.
         *
         * @return A String that represents the specified sub region of this object.
         ******************************************************************************************/
        public String ToString( int regionStart, int regionLength= int.MaxValue)
        {
            CString.AdjustRegion( Length(), ref regionStart, ref regionLength );
            if ( IsEmpty() || regionLength == 0)
                return "";

            return new String( Buf, Start + regionStart, regionLength );
        }



    /** ############################################################################################
     * @name C# std library interface implementation
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Calculates the hash value using the same formula as java.lang.String.
         * @return A hash value for this object.
         ******************************************************************************************/
        public override int GetHashCode()
        {
            if (hash == 0 && Length() > 0)
            {
                int h= 0;
                for (int i = Start; i <= End; i++)
                    h = 31*h + Buf[i++];

                hash = h;
            }
            return hash;
        }



} // class Substring


} // namespace / EOF
