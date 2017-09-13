// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// include guard
#ifndef HPP_ALIB_STRINGS_SUBSTRING
#define HPP_ALIB_STRINGS_SUBSTRING 1

// to preserve the right order, we are not includable directly from outside.
#if !defined(HPP_ALIB_STRINGS_STRING)
    #error "include 'alib/alib.hpp' or 'alib/alib_strings.hpp' before including this header"
#endif


namespace aworx { namespace lib { namespace strings
{
// #################################################################################################
// Forward declarations
// #################################################################################################
class Tokenizer;

// #################################################################################################
// Substring
// #################################################################################################

/** ************************************************************************************************
 * This class is used for defining a region (sub-string) on an existing character array.
 * Objects of this class will not manipulate the underlying data.
 * In particular, there is no terminating zero written.
 *
 * Unlike in the \e C# and \e Java versions of \b %ALib, the represented region is defined
 * by the protected fields inherited from class #String.
 * The difference to base class \ref aworx::lib::strings::String "String" is, that class \b %Substring
 * allows to change the buffer's start and its length.  Otherwise, this class has the
 * very same lightweight nature and performance as its base.
 * In general, while working with a \b %Substring, the size of it should shrink, e.g. by trimming,
 * but should not grow.
 *
 * Like base class
 * \ref aworx::lib::strings::String "String", the class can not, and therefore does not, verify that the
 * underlying buffer is still allocated or contains termination characters within the region
 * (which would be is against the rules).
 * It is up to the user of this class to make sure the buffer stays intact until any referencing
 * object of this type is destructed (or just is not used any more).
 *
 * Objects of this class can be reused by freshly initializing them using of method
 * #Set(const String&) and #Set(const String&,integer,integer).
 *
 *<p>
 * \note To generate \b %Substring objects which are separated by a delimiter character within a
 *       character array, use class
 *       \ref aworx::lib::strings::util::Tokenizer "Tokenizer".
 **************************************************************************************************/
class Substring : public String
{
    /** ############################################################################################
     * @name Constructors
     ##@{ ########################################################################################*/

    public:
        /** Import parent constructors */
        using String::String;

        /** ****************************************************************************************
         * Parameterless constructor.
         * (Note: This constructor is needed with some compilers only.)
         ******************************************************************************************/
        inline
        Substring()
        : String()
        {}

        /** ****************************************************************************************
         * Constructor using a string reference.
         * (Note: This constructor is needed with some compilers only.)
         * @param src   The source string.
         ******************************************************************************************/
        inline
        Substring( const String& src )
        : String(src)
        {}


    /** ############################################################################################
     * @name Set Data
     ##@{ ########################################################################################*/

    public:

        /** ****************************************************************************************
         * Sets this object to represent the given string.
         * @param src   The source string.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        Substring&  Set( const String& src )
        {
            buffer=   src.Buffer();
            length=   src.Length();
            return *this;
        }

        /** ****************************************************************************************
         * Sets this object to represent the given region of an
         * \ref aworx::lib::strings::String "String" object. The region is
         * checked (and adjusted) to be between 0 and \p as length.
         *
         * \note When using the non-checking version, parameter \p regionLength must be set
         *       explicitly to the correct value (instead of using the default value).
         *
         * @tparam TCheck       Chooses checking or non-checking implementation. Defaults to true.
         * @param src           The source string to set the region from (allowed to be same).
         * @param regionStart   The start of the region within the given \b %String.
         * @param regionLength  The length of the region within the given \b %String.
         *                      Defaults to CString::MaxLen.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        Substring&  Set( const String& src, integer regionStart, integer regionLength= CString::MaxLen )
        {
            if (TCheck)
                src.AdjustRegion( regionStart, regionLength );
            else
            {
                //---- non-checking version ----
                ALIB_ASSERT_ERROR(    regionStart >= 0 && regionLength >= 0
                                   && regionLength != CString::MaxLen // has to be separately checked!
                                   && regionStart +  regionLength  <= src.Length(),
                                   "NC: Invalid region given" )
            }

            buffer=   src.Buffer() + regionStart;
            length=                  regionLength;
            return *this;
        }

        /** ****************************************************************************************
         * Sets this object to \e nulled state.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        Substring&  SetNull()
        {
            buffer=  nullptr;
            length=  0;
            return *this;
        }

        /** ****************************************************************************************
         * Sets this object to zero length.
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        Substring&  Clear()
        {
            length=  0;
            return *this;
        }

        /** ****************************************************************************************
         * Set the length of the substring. The string can only be shortened.
         *
         * \note
         *   If the new length is requested to be higher than the current length,
         *   an one-time warning is issued. The warning occurs only once for the first
         *   occurrence of an invocation of this method with such wrong parameter.
         *   To enable/disable this warning use macros
         *   - \ref ALIB_WARN_ONCE_PER_TYPE_ENABLE(String, SetLengthLonger) and
         *   - \ref ALIB_WARN_ONCE_PER_TYPE_DISABLE(String, SetLengthLonger).
         *
         * The non-checking version does not do any checks but just applies the new length.
         *
         * @tparam TCheck      Defaults to \c true which is the normal invocation mode.
         *                     If \c \<false\> is added to the method name, no parameter checks are
         *                     performed.
         * @param newLength    The new length of the string. Must be between 0 and the current
         *                     length.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        void        SetLength( integer newLength )
        {
            ALIB_STRING_DBG_CHK(this)

            if ( TCheck )
            {
                ALIB_WARN_ONCE_IF_NOT( *this, SetLengthLonger, newLength <= length,
                                       "Length increase requested"                      );
                ALIB_ASSERT_ERROR(     newLength >= 0,      "Negative length" );

                if ( newLength >= 0 && newLength < length )
                    length= newLength;
            }
            else
            {
                length= newLength;
            }
        }

    /** ############################################################################################
     * @name Trim
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Moves the start to the first character not found given \p whiteSpaces.
         *
         * @param whiteSpaces  The characters used for trimming.
         *                     Defaults to  \ref aworx::DefaultWhitespaces
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        Substring&  TrimStart( const TString& whiteSpaces = DefaultWhitespaces )
        {
            if ( length > 0 )
            {
                integer idx= CString::IndexOfAny(              buffer,
                                                                 length,
                                                     whiteSpaces.Buffer(),
                                                     whiteSpaces.Length(),
                                                     lang::Inclusion::Exclude
                                                   );
                if(  idx < 0 )
                    idx= length;
                buffer+= idx;
                length-= idx;
            }
            return *this;
        }

        /** ****************************************************************************************
         * Moves the start to the first character not found given \p whiteSpaces.
         *
         * @param whiteSpaces  The characters used for trimming.
         *                     Defaults to  \ref aworx::DefaultWhitespaces
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        Substring&  TrimEnd( const TString& whiteSpaces = DefaultWhitespaces )
        {
            if ( length > 0 )
            {
                length= CString::LastIndexOfAny(                 buffer,
                                                                 length - 1,
                                                     whiteSpaces.Buffer(),
                                                     whiteSpaces.Length(),
                                                     lang::Inclusion::Exclude
                                                    ) + 1;
            }
            return *this;
        }


        /** ****************************************************************************************
         * Invokes #TrimStart and #TrimEnd .
         *
         * @param whiteSpaces  The characters used for trimming.
         *                     Defaults to  \ref aworx::DefaultWhitespaces
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        inline
        Substring&  Trim( const TString& whiteSpaces = DefaultWhitespaces )
        {
            return   TrimEnd  ( whiteSpaces )
                    .TrimStart( whiteSpaces );
        }


    /** ############################################################################################
     * @name Consume
     ##@{ ########################################################################################*/

        /** ****************************************************************************************
         * Retrieve and remove the first character from the substring.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no parameter check is
         *                 performed.
         *
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces::Keep.
         * @return The character at the start of the represented region.
         *         If this \b %Substring is empty or \e nulled, '\0' is returned.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        char        ConsumeChar(lang::Whitespaces trimBeforeConsume= lang::Whitespaces::Keep)
        {
            if ( TCheck )
            {
                if ( trimBeforeConsume == lang::Whitespaces::Trim )
                    TrimStart();
                if( IsEmpty() )
                    return '\0';
            }
            else
            {
                ALIB_ASSERT_ERROR( !IsEmpty(), "NC: empty string" );
                if ( trimBeforeConsume == lang::Whitespaces::Trim )
                    TrimStart();
            }

            length--;
            return *buffer++;
        }

        /** ****************************************************************************************
         * Checks if this object starts with the given character \p consumable. If it does, this
         * character is cut from this object.
         *
         * @param consumable        The consumable character
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        inline
        bool        ConsumeChar( char              consumable,
                                 lang::Case        sensitivity=       lang::Case::Sensitive,
                                 lang::Whitespaces trimBeforeConsume= lang::Whitespaces::Keep )

        {
            if ( trimBeforeConsume == lang::Whitespaces::Trim )
                TrimStart();

            if (    ( sensitivity == lang::Case::Sensitive &&         CharAtStart()  !=         consumable  )
                 || ( sensitivity == lang::Case::Ignore    && toupper(CharAtStart()) != toupper(consumable) ) )
                return false;
            buffer++;
            length--;
            return true;
        }

        /** ****************************************************************************************
         * Checks if this object ends with the given character \p consumable. If it does, this
         * character is cut from the end of object.
         *
         * @param consumable        The consumable character
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        inline
        bool        ConsumeCharFromEnd( char               consumable,
                                        lang::Case        sensitivity=       lang::Case::Sensitive,
                                        lang::Whitespaces trimBeforeConsume= lang::Whitespaces::Keep )
        {
            if ( trimBeforeConsume == lang::Whitespaces::Trim )
                TrimEnd();

            if (    ( sensitivity == lang::Case::Sensitive &&         CharAtEnd()  !=         consumable  )
                 || ( sensitivity == lang::Case::Ignore    && toupper(CharAtEnd()) != toupper(consumable) ) )
                return false;
            length--;
            return true;
        }

        /** ****************************************************************************************
         * Retrieve and remove the last character in the substring.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no parameter check is
         *                 performed.
         *
         * @param trimBeforeConsume Determines if the string should be (right-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces::Keep.
         * @return The character at the start of the represented region.
         *         If this \b %Substring is empty or \e nulled, '\0' is returned.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        char        ConsumeCharFromEnd(lang::Whitespaces trimBeforeConsume= lang::Whitespaces::Keep)
        {
            if ( TCheck )
            {
                if ( trimBeforeConsume == lang::Whitespaces::Trim )
                    TrimEnd();
                if( IsEmpty() )
                    return '\0';
            }
            else
            {
                ALIB_ASSERT_ERROR( !IsEmpty(), "NC: empty string" );
                if ( trimBeforeConsume == lang::Whitespaces::Trim )
                    TrimEnd();
            }
            return *(buffer + --length );
        }

        /** ****************************************************************************************
         * Cuts the given number of characters from the beginning of the Substring and optionally
         * places the portion that was cut in parameter \p target (if provided).<br>
         * Parameter \p regionLength is checked to be between 0 and length. If negative, nothing
         * is cut and \p target is set empty. If \p regionLength is greater than this
         * objects' length, all contents is 'moved' to \p target.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no parameter check is
         *                 performed.
         *
         * @param regionLength  The length of the region at the start to delete.
         * @param target        An optional target \b %Substring that receives the portion that
         *                      is cut from this object. Defaults to nullptr.
         *
         * @return The new length of the substring.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        integer  ConsumeChars( integer regionLength, Substring* target= nullptr )
        {
            if ( TCheck )
            {
                if ( regionLength < 0 )
                {
                    if ( target != nullptr )
                        target->Clear();
                    return  length;
                }
                if ( regionLength > length )
                    regionLength= length;
            }
            else
            {
                ALIB_ASSERT_ERROR( regionLength >=0 && regionLength <= length,
                                   "NC: regionLength out of bounds"             )
            }

            if ( target != nullptr )
                target->Set( *this, 0, regionLength );

            buffer+= regionLength;
            length-= regionLength;
            return length;
        }

        /** ****************************************************************************************
         * Cuts the given number of characters from the end of the Substring and optionally
         * places the portion that was cut in parameter \p target (if provided).<br>
         * Parameter \p regionLength is checked to be between 0 and length. If negative, nothing
         * is cut and \p target is set empty. If \p regionLength is greater than this
         * objects' length, all contents is 'moved' to \p target.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no parameter check is
         *                 performed.
         *
         * @param regionLength  The length of the region at the start to delete.
         * @param target        An optional target \b %Substring that receives the portion that
         *                      is cut from this object. Defaults to nullptr.
         *
         * @return The new length of the substring.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        integer   ConsumeCharsFromEnd( integer regionLength, Substring* target= nullptr )
        {
            if ( TCheck )
            {
                if ( regionLength < 0 )
                {
                    if ( target != nullptr )
                        target->Clear();
                    return  length;
                }
                if ( regionLength > length )
                    regionLength= length;
            }
            else
            {
                ALIB_ASSERT_ERROR( regionLength >=0 && regionLength <= length,
                                   "NC: regionLength out of bounds"             )
            }

            if ( target != nullptr )
                target->Set( *this, length - regionLength, regionLength );

            length-= regionLength;
            return length;
        }

        /** ****************************************************************************************
         * Cuts the given number of characters from the beginning of the Substring and optionally
         * places the portion that was cut in parameter \p target.<br>
         * Parameter \p regionLength is checked to be between 0 and length. If negative, nothing
         * is cut and \p target is set empty, respectively left untouched depending on \p
         * If \p regionLength is greater than this  objects' length, all contents is 'moved'
         * to \p target.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no parameter check is
         *                 performed.
         *
         * @param regionLength    The length of the region at the start to delete.
         * @param target          A target \b %AString that receives the portion that
         *                        is cut from this object.
         * @param separatorWidth  This width is added to what is cut from this string, while
         *                        \p target still receives the portion defined by \p regionLength.
         *                        Defaults to 0.
         * @param targetData      If \c CurrentData::Keep, the parameter \p target is not cleared
         *                        before the result is written. Defaults to \c CurrentData::Clear.
         *
         * @return The new length of the substring.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        integer ConsumeChars( integer            regionLength,
                               AString&            target,
                               integer            separatorWidth   =0,
                               lang::CurrentData  targetData       =lang::CurrentData::Clear)
        {
            if ( targetData == lang::CurrentData::Clear  )
                target.Clear();

            if ( TCheck )
            {
                if ( separatorWidth < 0 )                        separatorWidth= 0;
                if ( regionLength   < 0 )                        return  length;
                if ( regionLength   > length - separatorWidth )  regionLength= length - separatorWidth;
                if ( regionLength   < 0 )                        return  length;
            }
            else
            {
                ALIB_ASSERT_ERROR( separatorWidth >=0 , "NC: separator width negative"  )
                ALIB_ASSERT_ERROR( regionLength >=0 && regionLength + separatorWidth <= length,
                                   "NC: regionLength out of bounds"             )
            }

            target._<false>( *this, 0, regionLength );

            regionLength+= separatorWidth;
            buffer+= regionLength ;
            length-= regionLength;
            return length;
        }

        /** ****************************************************************************************
         * Cuts the given number of characters from the end of the Substring and
         * places the portion that was cut in parameter \p target.<br>
         * Parameter \p regionLength is checked to be between 0 and length. If negative, nothing
         * is cut and \p target is set empty, respectively left untouched depending on \p
         * If \p regionLength is greater than this objects' length, all contents is 'moved'
         * to \p target.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no parameter check is
         *                 performed.
         *
         * @param regionLength    The length of the region at the start to delete.
         * @param target          A target \b %AString that receives the portion that
         *                        is cut from this object.
         * @param separatorWidth  This width is added to what is cut from this string, while
         *                        \p target still receives the portion defined by \p regionLength.
         *                        Defaults to 0.
         * @param targetData      If \c CurrentData::Keep, the parameter \p target is not cleared
         *                        before the result is written. Defaults to \c CurrentData::Clear.
         *
         * @return The new length of the substring.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        integer ConsumeCharsFromEnd( integer            regionLength,
                                      AString&            target,
                                      integer            separatorWidth   =0,
                                      lang::CurrentData  targetData       =lang::CurrentData::Clear)
        {
            if ( targetData == lang::CurrentData::Clear  )
                target.Clear();

            if ( TCheck )
            {
                if ( separatorWidth < 0 )                        separatorWidth= 0;
                if ( regionLength   < 0 )                        return  length;
                if ( regionLength   > length - separatorWidth )  regionLength= length - separatorWidth;
                if ( regionLength   < 0 )                        return  length;
            }
            else
            {
                ALIB_ASSERT_ERROR( separatorWidth >=0 , "NC: separator width negative"  )
                ALIB_ASSERT_ERROR( regionLength >=0 && regionLength + separatorWidth <= length,
                                   "NC: regionLength out of bounds"             )
            }

            target._<false>( *this, length - regionLength, regionLength );

            length-= regionLength + separatorWidth;
            return length;
        }

        /** ****************************************************************************************
         * Checks if this object starts with the given string \p consumable. If it does, this
         * string is cut from this object.
         *
         * @param consumable        The consumable string.
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut.
         ******************************************************************************************/
        inline
        bool        ConsumeString( const String&     consumable,
                                   lang::Case        sensitivity=       lang::Case::Sensitive,
                                   lang::Whitespaces trimBeforeConsume= lang::Whitespaces::Keep )
        {
            if ( trimBeforeConsume == lang::Whitespaces::Trim )
                TrimStart();

            if ( !StartsWith( consumable, sensitivity ) )
                return false;

            buffer+= consumable.Length();
            length-= consumable.Length();
            return true;
        }

        /** ****************************************************************************************
         * Checks if this object ends with the given string \p consumable. If it does, this
         * string is cut from the end of object.
         *
         * @param consumable        The consumable string
         * @param sensitivity       The sensitivity of the comparison.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \b Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut.
         ******************************************************************************************/
        inline
        bool        ConsumeStringFromEnd( const String&      consumable,
                                   lang::Case        sensitivity=       lang::Case::Sensitive,
                                   lang::Whitespaces trimBeforeConsume= lang::Whitespaces::Keep )
        {
            if ( trimBeforeConsume == lang::Whitespaces::Trim )
                TrimEnd();

            if ( !EndsWith( consumable, sensitivity ) )
                return false;
            length-= consumable.Length();
            return true;
        }

        /** ****************************************************************************************
         * Consumes a minimum of \p minChars of string \c consumable from the start of this
         * substring. If the minimum characters could not be found, nothing is consumed, otherwise
         * as much as possible.<br>
         * This method is useful for example to read commands from a string that may be
         * abbreviated.
         *
         * @param consumable        The consumable string.
         * @param minChars          The minimum amount of characters to consume.
         *                          Optional and defaults to \c 1
         * @param sensitivity       The sensitivity of the comparison.
         *                          Defaults to \b Case::Sensitive.
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          first character consume operation.
         *                          Defaults to \b Whitespaces::Keep.
         * @return The amount of characters consumed.
         ******************************************************************************************/
        ALIB_API
        integer    ConsumePartOf(  const String&     consumable,
                                   int               minChars           = 1,
                                   lang::Case        sensitivity        = lang::Case::Sensitive,
                                   lang::Whitespaces trimBeforeConsume  = lang::Whitespaces::Keep );

        /** ****************************************************************************************
         * Consumes all characters \c '0' to \c '9' at the start of this object and stores the
         * value they represent in \p result.
         * <br>Unlike with #ConsumeInt or #ConsumeDec, no sign, whitespaces or group characters are
         * consumed.
         *
         * @param [out] result    A reference to the result value.
         * @tparam    TInteger    The output type.
         *                        Must be statically castable from \b uint64_t.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger>
        inline
        bool     ConsumeDecDigits( TInteger& result )
        {
            uint64_t resultImpl;
            bool    returnValue= consumeDecDigitsImpl( resultImpl );
            result= static_cast<TInteger>( resultImpl );
            return  returnValue;
        }

        /** ****************************************************************************************
         * Consumes an integer value in decimal, binary, hexadecimal or octal format from
         * the string by invoking method
         * \ref aworx::lib::strings::NumberFormat::ParseInt "NumberFormat::ParseInt"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * For more information on number conversion, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat".
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use. Defaults to \c nullptr.
         * @tparam    TInteger    The output type.
         *                        Must be statically castable from \b uint64_t.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger>
        inline
        bool   ConsumeInt( TInteger& result, NumberFormat* numberFormat= nullptr )
        {
            int64_t resultImpl;
            bool    returnValue= consumeIntImpl( resultImpl, numberFormat );
            result= static_cast<TInteger>( resultImpl );
            return  returnValue;
        }

        /** ****************************************************************************************
         * Consumes an unsigned integer in standard decimal format
         * from the start of this %AString. This is done, by invoking
         * \ref aworx::lib::strings::NumberFormat::ParseDec "NumberFormat::ParseDec"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * Sign literals \c '-' or \c '+' are \b not accepted and parsing will fail.
         * For reading signed integer values, see methods #ConsumeInt, for floating point numbers
         * #ConsumeFloat.
         *
         * For more information on number conversion, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat".
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use. Defaults to \c nullptr.
         * @tparam    TInteger    The output type.
         *                        Must be statically castable from \b uint64_t.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger>
        inline
        bool   ConsumeDec( TInteger& result, NumberFormat* numberFormat= nullptr )
        {
            uint64_t resultImpl;
            bool     returnValue= consumeDecImpl( resultImpl, numberFormat );
            result=  static_cast<TInteger>( resultImpl );
            return   returnValue;
        }

        /** ****************************************************************************************
         * Consumes an unsigned integer in binary format at the given position
         * from the start of this string. This is done, by invoking
         * \ref aworx::lib::strings::NumberFormat::ParseBin "NumberFormat::ParseBin"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * For more information on number conversion, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat".
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use. Defaults to \c nullptr.
         * @tparam    TInteger    The output type.
         *                        Must be statically castable from \b uint64_t.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger>
        inline
        bool   ConsumeBin( TInteger& result, NumberFormat* numberFormat= nullptr )
        {
            uint64_t resultImpl;
            bool     returnValue= consumeBinImpl( resultImpl, numberFormat );
            result=  static_cast<TInteger>( resultImpl );
            return   returnValue;
        }

        /** ****************************************************************************************
         * Consumes an unsigned integer in hexadecimal format at the given position
         * from the start of this string. This is done, by invoking
         * \ref aworx::lib::strings::NumberFormat::ParseHex "NumberFormat::ParseHex"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * For more information on number conversion, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat".
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use. Defaults to \c nullptr.
         * @tparam    TInteger    The output type.
         *                        Must be statically castable from \b uint64_t.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger>
        inline
        bool   ConsumeHex( TInteger& result, NumberFormat* numberFormat= nullptr )
        {
            uint64_t resultImpl;
            bool     returnValue= consumeHexImpl( resultImpl, numberFormat );
            result=  static_cast<TInteger>( resultImpl );
            return   returnValue;
        }

        /** ****************************************************************************************
         * Consumes an unsigned integer in octal format at the given position
         * from the start of this string. This is done, by invoking
         * \ref aworx::lib::strings::NumberFormat::ParseOct "NumberFormat::ParseOct"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to not using - and therefore also not parsing - grouping characters.
         *
         * For more information on number conversion, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat".
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use. Defaults to \c nullptr.
         * @tparam    TInteger    The output type.
         *                        Must be statically castable from \b uint64_t.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger>
        inline
        bool   ConsumeOct( TInteger& result, NumberFormat* numberFormat= nullptr )
        {
            uint64_t resultImpl;
            bool     returnValue= consumeOctImpl( resultImpl, numberFormat );
            result=  static_cast<TInteger>( resultImpl );
            return   returnValue;
        }

        /** ****************************************************************************************
         * Consumes a floating point number at the given position from the start of this string.
         * This is done, by invoking
         * \ref aworx::lib::strings::NumberFormat::ParseFloat "NumberFormat::ParseFloat"
         * on the given \p numberFormat instance.<br>
         * Parameter \p numberFormat defaults to \c nullptr. This denotes static singleton
         * \ref aworx::lib::strings::NumberFormat::Computational "NumberFormat::Computational"
         * which is configured to 'international' settings (not using the locale) and therefore
         * also not parsing grouping characters.
         *
         * For more information on parsing options for floating point numbers and number
         * conversion in general, see class
         * \ref aworx::lib::strings::NumberFormat "NumberFormat".
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use. Defaults to \c nullptr.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        ALIB_API
        bool  ConsumeFloat( double&         result,
                            NumberFormat*   numberFormat     =nullptr   );


        /** ****************************************************************************************
         * Splits this substring into two parts. What remains in this object is the region
         * from 0 to \p position.
         * \p target receives the rest. If \p separatorWidth is given, this is subtracted from
         * the front of \p target.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no parameter check is
         *                 performed.
         *
         * @param position        The index where this object is split.
         * @param target          The target substring to receive the right part of the string.
         * @param separatorWidth  This does not change what remains in this object, but defines
         *                        the number of characters that are cut from the front of the
         *                        \p target. Defaults to 0.
         * @param trim            If \c true, both substrings will be trimmed.
         *
         * @return \c *this to allow concatenated calls.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        Substring& Split( integer position, Substring& target, integer separatorWidth  =0, bool trim= false )

        {
            if ( TCheck )
            {
                AdjustRegion( position, separatorWidth );
            }
            else
            {
                ALIB_ASSERT_ERROR( position >=0 && position <= length,
                                   "NC: position out of bounds"             )
                ALIB_ASSERT_ERROR( position + separatorWidth <= length,
                                   "NC: position + separator width out of bounds" )
            }

            target.Set( *this, position + separatorWidth, length - position - separatorWidth );
            length= position;
            if( trim )
            {
                target.Trim();
                this ->Trim();
            }
            return *this;
        }

    //##############################################################################################
    // Protected Methods
    //##############################################################################################
    protected:
        /** ****************************************************************************************
         * Implementation for #ConsumeDecDigits.
         *
         * @param [out] result    A reference to the result value.
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        ALIB_API  bool   consumeDecDigitsImpl( uint64_t& result );

        /** ****************************************************************************************
         * Implementation for #ConsumeInt.
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use.
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        ALIB_API  bool   consumeIntImpl( int64_t& result, NumberFormat* numberFormat );

        /** ****************************************************************************************
         * Implementation for #ConsumeDec.
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use.
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        ALIB_API  bool   consumeDecImpl( uint64_t& result, NumberFormat* numberFormat );

        /** ****************************************************************************************
         * Implementation for #ConsumeBin.
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use.
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        ALIB_API  bool   consumeBinImpl( uint64_t& result, NumberFormat* numberFormat );

        /** ****************************************************************************************
         * Implementation for #ConsumeHex.
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use.
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        ALIB_API  bool   consumeHexImpl( uint64_t& result, NumberFormat* numberFormat );

        /** ****************************************************************************************
         * Implementation for #ConsumeOct.
         *
         * @param [out] result    A reference to the result value.
         * @param numberFormat    The number format to use.
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        ALIB_API  bool   consumeOctImpl( uint64_t& result, NumberFormat* numberFormat );



}; // class Substring

}} // namespace lib::strings

/** Type alias name in namespace #aworx. */
using     Substring =    lib::strings::Substring;

} // namespace aworx

#endif // HPP_ALIB_STRINGS_SUBSTRING



