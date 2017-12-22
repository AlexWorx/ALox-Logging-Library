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
    #error "include 'alib/alib.hpp' before including this header"
#endif

#if !defined (HPP_ALIB_LANG_ENUM_BITWISE)
#   include "alib/lang/enumbitwise.hpp"
#endif

namespace aworx { namespace lib { namespace strings {

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
                integer idx= CString::IndexOfAnyExcluded(            buffer,                length,
                                                         whiteSpaces.Buffer(),  whiteSpaces.Length() );
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
                length= CString::LastIndexOfAnyExclude(             buffer,
                                                                    length - 1,
                                                        whiteSpaces.Buffer(),
                                                        whiteSpaces.Length()
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
        ALIB_WARNINGS_ALLOW_TEMPLATE_META_PROGRAMMING
        /** ****************************************************************************************
         * Retrieve and remove the first character from the substring.
         *
         * @tparam TTrimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                            consume operation. Defaults to \b Whitespaces::Keep.
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no parameter check is
         *                 performed.
         *
         * @return The character at the start of the represented region.
         *         If this \b %Substring is empty or \e nulled, '\0' is returned.
         ******************************************************************************************/
        template < bool              TCheck            = true,
                   lang::Whitespaces TTrimBeforeConsume= lang::Whitespaces::Keep  >
        inline
        char        ConsumeChar()
        {
            if ( TCheck )
            {
                if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                    TrimStart();
                if( IsEmpty() )
                    return '\0';
            }
            else
            {
                ALIB_ASSERT_ERROR( !IsEmpty(), "NC: empty string" );
                if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                    TrimStart();
            }

            length--;
            return *buffer++;
        }

        /** ****************************************************************************************
         * Checks if this object starts with the given character \p consumable. If it does, this
         * character is cut from this object.
         *
         * @param  consumable         The consumable character
         *
         * @tparam TSensitivity       The sensitivity of the comparison.
         * @tparam TTrimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                           consume operation. Defaults to \b Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        template< lang::Case        TSensitivity=        lang::Case::Sensitive,
                  lang::Whitespaces TTrimBeforeConsume= lang::Whitespaces::Keep>
        inline
        bool        ConsumeChar( char   consumable )

        {
            if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                TrimStart();

            if (    ( TSensitivity == lang::Case::Sensitive &&         CharAtStart()  !=         consumable  )
                 || ( TSensitivity == lang::Case::Ignore    && toupper(CharAtStart()) != toupper(consumable) ) )
                return false;
            buffer++;
            length--;
            return true;
        }

        /** ****************************************************************************************
         * Checks if this object ends with the given character \p consumable. If it does, this
         * character is cut from the end of object.
         *
         * @param consumable          The consumable character
         * @tparam TSensitivity       The sensitivity of the comparison.
         * @tparam TTrimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                            consume operation. Defaults to \b Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        template< lang::Case        TSensitivity=       lang::Case::Sensitive,
                  lang::Whitespaces TTrimBeforeConsume= lang::Whitespaces::Keep>
        inline
        bool        ConsumeCharFromEnd( char  consumable )
        {
            if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                TrimEnd();

            if (    ( TSensitivity == lang::Case::Sensitive &&         CharAtEnd()  !=         consumable  )
                 || ( TSensitivity == lang::Case::Ignore    && toupper(CharAtEnd()) != toupper(consumable) ) )
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
         * @tparam TTrimBeforeConsume Determines if the string should be (right-) trimmed before the
         *                            consume operation. Defaults to \b Whitespaces::Keep.
         * @return The character at the start of the represented region.
         *         If this \b %Substring is empty or \e nulled, '\0' is returned.
         ******************************************************************************************/
        template <bool TCheck= true,
                  lang::Whitespaces TTrimBeforeConsume= lang::Whitespaces::Keep >
        inline
        char        ConsumeCharFromEnd()
        {
            if ( TCheck )
            {
                if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                    TrimEnd();
                if( IsEmpty() )
                    return '\0';
            }
            else
            {
                ALIB_ASSERT_ERROR( !IsEmpty(), "NC: empty string" );
                if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
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
         * is cut and \p target is set empty, respectively left untouched depending on
         * \p TTargetData.
         *
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
         * @tparam TTargetData    If \c CurrentData::Keep, the parameter \p target is not cleared
         *                        before the result is written. Defaults to \c CurrentData::Clear.
         *
         * @return The new length of the substring.
         ******************************************************************************************/
        template <bool               TCheck           = true,
                  lang::CurrentData  TTargetData      = lang::CurrentData::Clear>
        inline
        integer ConsumeChars( integer            regionLength,
                              AString&           target,
                              integer            separatorWidth   =0         )
        {
            if ( TTargetData == lang::CurrentData::Clear  )
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
         * @tparam TTargetData    If \c CurrentData::Keep, the parameter \p target is not cleared
         *                        before the result is written. Defaults to \c CurrentData::Clear.
         *
         * @return The new length of the substring.
         ******************************************************************************************/
        template <bool                  TCheck           = true,
                  lang::CurrentData     TTargetData      =lang::CurrentData::Clear>
        inline
        integer ConsumeCharsFromEnd( integer             regionLength,
                                     AString&            target,
                                     integer             separatorWidth   =0      )
        {
            if ( TTargetData == lang::CurrentData::Clear  )
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
         * Searches \p separator and cuts the beginning of this string, including the separator.
         * What was consumed is returned, excluding the separator.
         *
         * If the separator is not found, all of this string is consumed and returned.
         *
         * @param separator  The separator to search.
         *                   Defaults to <c>','</c>.
         *
         * @return The token consumed.
         ******************************************************************************************/
        inline
        String  ConsumeToken( char separator= ',' )
        {
            ALIB_ASSERT_ERROR( IsNotNull() , "ConsumeToken on nulled Substring"  )
            integer separatorPos= IndexOfOrLength( separator );
            String result= String( buffer, separatorPos );

            buffer+= separatorPos;
            length-= separatorPos;
            if( length > 0 )
            {
                buffer++;
                length--;
            }
            return result;
        }

        /** ****************************************************************************************
         * Checks if this object starts with the given string \p consumable. If it does, this
         * string is cut from this object.
         *
         * @param  consumable         The consumable string.
         * @tparam TSensitivity       The sensitivity of the comparison.
         * @tparam TTrimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                            consume operation. Defaults to \b Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut.
         ******************************************************************************************/
        template< lang::Case        TSensitivity=       lang::Case::Sensitive,
                  lang::Whitespaces TTrimBeforeConsume= lang::Whitespaces::Keep >
        inline
        bool        ConsumeString( const String&     consumable  )
        {
            if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                TrimStart();

            if ( !StartsWith<TSensitivity>( consumable ) )
                return false;

            buffer+= consumable.Length();
            length-= consumable.Length();
            return true;
        }

        /** ****************************************************************************************
         * Checks if this object ends with the given string \p consumable. If it does, this
         * string is cut from the end of object.
         *
         * @param  consumable         The consumable string
         * @tparam TSensitivity       The sensitivity of the comparison.
         * @tparam TTrimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                           consume operation. Defaults to \b Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut.
         ******************************************************************************************/
        template< lang::Case        TSensitivity=       lang::Case::Sensitive,
                  lang::Whitespaces TTrimBeforeConsume= lang::Whitespaces::Keep >
        inline
        bool        ConsumeStringFromEnd( const String&  consumable )
        {
            if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                TrimEnd();

            if ( !EndsWith<TSensitivity>( consumable ) )
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
         * @param  consumable         The consumable string.
         * @param  minChars           The minimum amount of characters to consume. If \c 0 or
         *                            negative, the length of \p consumable is chosen.
         *                            Optional and defaults to \c 1.
         * @tparam TSensitivity       The sensitivity of the comparison.
         *                            Defaults to \b Case::Ignore.
         * @tparam TTrimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                            first character consume operation.
         *                            Defaults to \b Whitespaces::Keep.
         * @return The amount of characters consumed.
         ******************************************************************************************/
        template< lang::Case        TSensitivity=       lang::Case::Ignore,
                  lang::Whitespaces TTrimBeforeConsume= lang::Whitespaces::Keep >
        integer    ConsumePartOf(  const String&     consumable,
                                   int               minChars           = 1 )
        {
            if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                TrimStart();
            if ( minChars <= 0 )
                minChars= static_cast<int>( consumable.Length() );

            if ( minChars == 0 || minChars > consumable.Length() )
                return 0;

            integer diff= IndexOfFirstDifference( consumable, TSensitivity );
            if( diff < static_cast<integer>( minChars ) )
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
         * @tparam TTrimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                            consume operation. Defaults to \b Whitespaces::Keep.
         * @return The string consumed. \b NullString on error (start/end character not found)
         ******************************************************************************************/
        template< lang::Whitespaces TTrimBeforeConsume= lang::Whitespaces::Keep >
        inline
        String  ConsumeField( char startChar, char endChar  )
        {
            if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                TrimStart();

            if ( CharAtStart() != startChar )
                return NullString;

            int cntStartChars= 1;
            for ( integer i= 1; i < length ; i++ )
            {
                char actChar= buffer[i];
                if( actChar == endChar )
                {
                    if( --cntStartChars == 0 )
                    {
                        String result= String( buffer + 1, i - 1 );
                        buffer+= (i + 1);
                        length-= (i + 1);
                        return result;
                    }
                }
                else if( actChar == startChar )
                    cntStartChars++;
            }

            return NullString;
        }

        /** ****************************************************************************************
         * Consumes an element of an C++ enum which is equipped with "\alib enum meta data".
         * For more information consult
         * \ref anchor_T_EnumMetaDataDecl_read_enum "T_EnumMetaDataDecl documentation".
         *
         * \note
         *   This method is applicable to bitwise enums as well. However, only one element name is
         *   parsed. To parse multiple elements (ored to one enum value), use method
         *   #ConsumeEnumBitwise.
         *
         *
         * @param[out] result         The result enum element given as reference.
         * @tparam TEnum              The enumeration type.
         * @tparam TSensitivity       The sensitivity of the comparison.
         *                            Defaults to \b Case::Sensitive.
         * @tparam TTrimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                            consume operation.<br>
         *                            Defaults to \b Whitespaces::Trim.
         * @tparam TEnableIf          Internal. Do \b not specify!<br>
         *                            (Defaults to \c std::enable_if type, to enable the compiler to
         *                            select this method only for types that have specialized member
         *                            \alib{lang,T_EnumMetaDataDeclReadWrite::MinParseLengthIndex}
         *                            evaluating to a value different to \c 0.
         * @return \c true if an enum element was read, \c false otherwise.
         ******************************************************************************************/
        template<typename          TEnum,
                 lang::Case        TSensitivity        = lang::Case::Ignore,
                 lang::Whitespaces TTrimBeforeConsume  = lang::Whitespaces::Trim,
                 typename TEnableIf= typename std::enable_if<T_EnumMetaDataDeclReadWrite<TEnum>::MinParseLengthIndex
                                                             != 0 >::type>
        bool    ConsumeEnum(  TEnum&  result )
        {
            auto& enumMetaData= *EnumMetaData<TEnum>::GetSingleton();
            enumMetaData.CheckLoad();

            if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                TrimStart();

            for( auto& entry : enumMetaData.Table )
            {
                if ( ConsumePartOf<TSensitivity>( EnumReadWriteInfo<TEnum>::Name( entry ),
                                                 std::get<lang::T_EnumMetaDataDeclReadWrite<TEnum>::MinParseLengthIndex>( entry )
                                                 )  > 0 )
                {
                    result= enumMetaData.Enum( entry );
                    return true;
                }
            }
            return false;
        }

        /** ****************************************************************************************
         * Repeatedly invokes #ConsumeEnum until \p delim is not found. The enum element values
         * are or'ed in \p result.
         *
         * \note
         *   This method is applicable to \alib{lang,T_EnumIsBitwise,bitwise enums} only.
         *
         *
         * @param[out] result         The result enum element given as reference.
         * @tparam TSensitivity       The sensitivity of the comparison.
         *                            Defaults to \b Case::Sensitive.
         * @tparam TTrimBeforeConsume Determines if the string should be (left-) trimmed before and
         *                            after each consume operation.<br>
         *                            Defaults to \b Whitespaces::Trim.
         * @tparam delimiter          The delimiter character of the enum elements.<br>
         *                            Defaults to <c>','</c>.
         * @tparam keepLastDelim      If \c true , the delimiter will be kept in this substring, if
         *                            after the delimiter no further enum element was found.
         *                            If \c false, the delimiter will be kept.<br>
         *                            Defaults to \c true.
         * @tparam TEnum              The enumeration type.
         * @tparam TEnableIf          Internal. Do \b not specify!<br>
         *                            (Defaults to \c std::enable_if type, to enable the compiler to
         *                            select this operator only for types that have specialized
         *                            \alib{lang,T_EnumIsBitwise} and also specialized member
         *                            \alib{lang,T_EnumMetaDataDeclReadWrite::MinParseLengthIndex}
         *                            evaluating to a value different to \c 0.)
         * @return \c true if an enum element was read, \c false otherwise.
         ******************************************************************************************/
        template<typename          TEnum,
                 lang::Case        TSensitivity       = lang::Case::Ignore,
                 lang::Whitespaces TTrimBeforeConsume = lang::Whitespaces::Trim,
                 char              delimiter          = ',',
                 bool              keepLastDelim      = true,
                 typename TEnableIf= typename std::enable_if< ( T_EnumMetaDataDeclReadWrite<TEnum>::MinParseLengthIndex
                                                                !=  0 )
                                                              && lang::T_EnumIsBitwise<TEnum>::value
                                                            >::type>
        bool    ConsumeEnumBitwise( TEnum&  result )
        {
            bool mResult= false;
            result= TEnum(0);
            Substring restoreBeforeDelim;
            if( keepLastDelim )
                restoreBeforeDelim= *this;
            for(;;)
            {
                if ( TTrimBeforeConsume == lang::Whitespaces::Trim )
                    TrimStart();
                TEnum actEnum;
                if ( !ConsumeEnum<TEnum, TSensitivity, TTrimBeforeConsume>( actEnum ) )
                {
                    if( keepLastDelim )
                        *this= restoreBeforeDelim;
                    return mResult;
                }
                result|=  actEnum;
                mResult=  true;
                if( TTrimBeforeConsume == lang::Whitespaces::Trim )
                    TrimStart();
                if( keepLastDelim )
                    restoreBeforeDelim=  *this;
                if( !ConsumeChar<TSensitivity, TTrimBeforeConsume>( delimiter ) )
                    return mResult;

            }
        }

        /** ****************************************************************************************
         * Convenience method that first uses #ConsumeEnum to try and read an element of an C++
         * enum. If this is not successful, an enum of type \alib{lang,Bool} is tried to be read.
         * If this is successful, depending on the value read, the \p TEnum values given
         * as parameters \p falseValue and \p trueValue are assigned.
         * Otherwise false is returned.
         *
         * For more information consult
         * \ref anchor_T_EnumMetaDataDecl_read_enum "T_EnumMetaDataDecl documentation".
         *
         * \note
         *   This method is applicable to bitwise enums as well. However, only one element name is
         *   parsed. To parse multiple elements (ored to one enum value), use method
         *   #ConsumeEnumBitwise.
         *
         *
         * @param[out] result         The result enum element given as reference.
         * @tparam TEnum              The enumeration type.
         * @param  trueValue          The \p TEnum value to use in case of \c Bool::True was read.
         * @param  falseValue         The \p TEnum value to use in case of \c Bool::False was read.
         * @tparam TTrimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                            consume operation. Passed to #ConsumeEnum.<br>
         *                            Defaults to \b Whitespaces::Trim.
         * @tparam TSensitivity       The sensitivity of the comparison.
         * @tparam TEnableIf          Internal. Do \b not specify!<br>
         *                            (Defaults to \c std::enable_if type, to enable the compiler to
         *                            select this method only for types that have specialized member
         *                            \alib{lang,T_EnumMetaDataDeclReadWrite::MinParseLengthIndex}
         *                            evaluating to a value different to \c 0.
         * @return \c true if an element of \p TEnum or \alib{lang,Bool} could be read,
         *         \c false otherwise.
         ******************************************************************************************/
        template<typename          TEnum,
                 lang::Case        TSensitivity       = lang::Case::Ignore,
                 lang::Whitespaces TTrimBeforeConsume = lang::Whitespaces::Trim,
                 typename          TEnableIf= typename std::enable_if< T_EnumMetaDataDeclReadWrite<TEnum>::MinParseLengthIndex
                                                                       !=  0 >::type>
        bool    ConsumeEnumOrBool(  TEnum&            result,
                                    TEnum             falseValue,
                                    TEnum             trueValue         )
        {
            // first try to read a TEnum
            if( ConsumeEnum<TEnum, TSensitivity, TTrimBeforeConsume>( result ) )
                return true;

            // if failed, read boolean
            Bool boolEnum;
            if( ConsumeEnum<Bool,  TSensitivity, TTrimBeforeConsume>( boolEnum ) )
            {
                result= boolEnum == Bool::True ? trueValue : falseValue;
                return true;
            }

            // failed
            return false;
        }

        ALIB_WARNINGS_RESTORE

        /** ****************************************************************************************
         * Consumes all characters \c '0' to \c '9' at the start of this object and stores the
         * value they represent in \p result.
         * <br>Unlike with #ConsumeInt or #ConsumeDec, no sign, whitespaces or group characters are
         * consumed.
         *
         * @param [out] result    A reference to the result value.
         * @tparam    TInteger    The output type.
         *                        Must be statically castable from \b uint64_t.
         * @tparam TEnableIf      Internal. Do \b not specify!<br>
         *                        (Defaults to \c std::enable_if type, to enable the compiler to
         *                        select this method only for integer types.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger,
                 typename TEnableIf= typename std::enable_if<    std::is_integral<TInteger>::value
                                                            >::type>
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
         * @param  numberFormat   The number format to use. Defaults to \c nullptr.
         * @tparam TInteger       The output type.
         *                        Must be statically castable from \b uint64_t.
         * @tparam TEnableIf      Internal. Do \b not specify!<br>
         *                        (Defaults to \c std::enable_if type, to enable the compiler to
         *                        select this method only for integer types.
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger,
                 typename TEnableIf= typename std::enable_if<    std::is_integral<TInteger>::value
                                                            >::type
                >
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
         * @tparam TInteger       The output type.
         *                        Must be statically castable from \b uint64_t.
         * @tparam TEnableIf      Internal. Do \b not specify!<br>
         *                        (Defaults to \c std::enable_if type, to enable the compiler to
         *                        select this method only for integer types.
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger,
                 typename TEnableIf= typename std::enable_if<    std::is_integral<TInteger>::value
                                                            >::type
                >
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
         * @tparam TEnableIf      Internal. Do \b not specify!<br>
         *                        (Defaults to \c std::enable_if type, to enable the compiler to
         *                        select this method only for integer types.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger,
                 typename TEnableIf= typename std::enable_if<    std::is_integral<TInteger>::value
                                                            >::type
                >
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
         * @tparam TEnableIf      Internal. Do \b not specify!<br>
         *                        (Defaults to \c std::enable_if type, to enable the compiler to
         *                        select this method only for integer types.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger,
                 typename TEnableIf= typename std::enable_if<    std::is_integral<TInteger>::value
                                                            >::type
                >
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
         * @tparam TEnableIf      Internal. Do \b not specify!<br>
         *                        (Defaults to \c std::enable_if type, to enable the compiler to
         *                        select this method only for integer types.
         *
         * @return  \c true if a number was found and consumed, \c false otherwise.
         ******************************************************************************************/
        template<typename TInteger,
                 typename TEnableIf= typename std::enable_if<    std::is_integral<TInteger>::value
                                                            >::type
                >
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



