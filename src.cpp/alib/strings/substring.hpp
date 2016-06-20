// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_STRINGS_ASSUBSTRING)
    #error "Header already included"
#endif

// Due to our blocker above, this include will never be executed. But having it, allows IDEs
// (e.g. QTCreator) to read the symbols when opening this file
#if !defined (HPP_ALIB)
    #include "alib/alib.hpp"
#endif

// then, set include guard
#ifndef HPP_ALIB_STRINGS_ASSUBSTRING
#if !defined( IS_DOXYGEN_PARSER)
    #define HPP_ALIB_STRINGS_ASSUBSTRING 1
#endif

// conditional expression is constant for using our constant template parameters to select
// checking vs. non-checking method versions
#if defined(_MSC_VER)
    #pragma warning( push )
    #pragma warning( disable : 4127 )
#endif

namespace aworx {
namespace           lib {
namespace                   strings {

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
 * Unlike in the \e C# and \e Java versions of ALib, the represented region is defined
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
 * #Set(const String&) and #Set(const String&,int,int).
 *
 *<p>
 * \note To generate \b %Substring objects which are separated by a delimiter character within a
 *       character array, use class
 *       \ref aworx::lib::strings::Tokenizer "Tokenizer".
 **************************************************************************************************/
class Substring : public String
{
    /** ############################################################################################
     * @name Constructors
     ##@{ ########################################################################################*/

    public:
        using String::String;

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
        Substring&  Set( const String& src, int regionStart, int regionLength= CString::MaxLen )
        {
            if (TCheck)
                src.AdjustRegion( regionStart, regionLength );
            else
            {
                //---- non-checking version ----
                ALIB_ASSERT_ERROR(    regionStart >= 0 && regionLength >= 0
                                   && regionLength != CString::MaxLen // has to be separatedly checked!
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
        void        SetLength( int newLength )
        {
            ALIB_STRING_DBG_CHK(this)

            if ( TCheck )
            {
                ALIB_WARN_ONCE_IF_NOT( newLength <= length, "Length increase requested", *this, SetLengthLonger );
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
         * @return \c true if empty after the operation.
         ******************************************************************************************/
        inline
        bool        TrimStart( const TString& whiteSpaces = DefaultWhitespaces )
        {
            if ( length > 0 )
            {
                int idx= CString::IndexOfAny(              buffer,
                                                           length,
                                               whiteSpaces.Buffer(),
                                               whiteSpaces.Length(),
                                               enums::Inclusion::Exclude
                                             );
                if(  idx < 0 )
                    idx= length;
                buffer+= idx;
                length-= idx;
            }
            return IsEmpty();
        }

        /** ****************************************************************************************
         * Moves the start to the first character not found given \p whiteSpaces.
         *
         * @param whiteSpaces  The characters used for trimming.
         *                     Defaults to  \ref aworx::DefaultWhitespaces
         * @return \c true if empty after the operation.
         ******************************************************************************************/
        inline
        bool        TrimEnd( const TString& whiteSpaces = DefaultWhitespaces )
        {
            length= CString::LastIndexOfAny(                 buffer,
                                                             length - 1,
                                                 whiteSpaces.Buffer(),
                                                 whiteSpaces.Length(),
                                                 enums::Inclusion::Exclude
                                                ) + 1;
            return ( length == 0 );
        }


        /** ****************************************************************************************
         * Invokes #TrimStart and #TrimEnd .
         *
         * @param whiteSpaces  The characters used for trimming.
         *                     Defaults to  \ref aworx::DefaultWhitespaces
         * @return \c true if empty after the operation.
         ******************************************************************************************/
        bool  Trim( const TString& whiteSpaces = DefaultWhitespaces )
        {
            if ( TrimStart( whiteSpaces ) )
                return true;
            return TrimEnd( whiteSpaces );
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
         *                          consume operation. Defaults to \c Whitespaces::Keep.
         * @return The character at the start of the represented region.
         *         If this \b %Substring is empty or \e nulled, '\0' is returned.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        char        Consume(enums::Whitespaces trimBeforeConsume= enums::Whitespaces::Keep)
        {
            if ( TCheck )
            {
                if ( trimBeforeConsume == enums::Whitespaces::Trim ? TrimStart() : IsEmpty() )
                    return '\0';
            }
            else
            {
                ALIB_ASSERT_ERROR( !IsEmpty(), "NC: empty string" );
                if ( trimBeforeConsume == enums::Whitespaces::Trim )
                    TrimStart();
            }

            length--;
            return *buffer++;
        }

        /** ****************************************************************************************
         * Retrieve and remove the last character in the substring.
         *
         * @tparam TCheck  Defaults to \c true which is the normal invocation mode.
         *                 If \c \<false\> is added to the method name, no parameter check is
         *                 performed.
         *
         * @param trimBeforeConsume Determines if the string should be (right-) trimmed before the
         *                          consume operation. Defaults to \c Whitespaces::Keep.
         * @return The character at the start of the represented region.
         *         If this \b %Substring is empty or \e nulled, '\0' is returned.
         ******************************************************************************************/
        template <bool TCheck= true>
        inline
        char        ConsumeFromEnd(enums::Whitespaces trimBeforeConsume= enums::Whitespaces::Keep)
        {
            if ( TCheck )
            {
                if ( trimBeforeConsume == enums::Whitespaces::Trim ? TrimEnd() : IsEmpty() )
                    return '\0';
            }
            else
            {
                ALIB_ASSERT_ERROR( !IsEmpty(), "NC: empty string" );
                if ( trimBeforeConsume == enums::Whitespaces::Trim )
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
        int        Consume( int regionLength, Substring* target= nullptr )
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
        int        ConsumeFromEnd( int regionLength, Substring* target= nullptr )
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
        int        Consume( int                regionLength,
                            AString&           target,
                            int                separatorWidth   =0,
                            enums::CurrentData targetData       =enums::CurrentData::Clear)
        {
            if ( targetData == enums::CurrentData::Clear  )
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
        int        ConsumeFromEnd(  int                regionLength,
                                    AString&           target,
                                    int                separatorWidth   =0,
                                    enums::CurrentData targetData       =enums::CurrentData::Clear)
        {
            if ( targetData == enums::CurrentData::Clear  )
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
         * @param consumable        The consumable string
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \c Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut.
         ******************************************************************************************/
        inline
        bool        Consume( const String& consumable, enums::Whitespaces trimBeforeConsume= enums::Whitespaces::Keep )
        {
            if ( trimBeforeConsume == enums::Whitespaces::Trim )
                TrimStart();

            if ( !StartsWith( consumable ) )
                return false;

            Consume<false>( consumable.Length() );

            return true;
        }


        /** ****************************************************************************************
         * Checks if this object ends with the given string \p consumable. If it does, this
         * string is cut from the end of object.
         *
         * @param consumable        The consumable string
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \c Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut.
         ******************************************************************************************/
        inline
        bool        ConsumeFromEnd( const String& consumable, enums::Whitespaces trimBeforeConsume= enums::Whitespaces::Keep )
        {
            if ( trimBeforeConsume == enums::Whitespaces::Trim )
                TrimEnd();

            if ( !EndsWith( consumable ) )
                return false;
            ConsumeFromEnd<false>( consumable.Length() );
            return true;
        }

        /** ****************************************************************************************
         * Checks if this object starts with the given character \p consumable. If it does, this
         * character is cut from this object.
         *
         * @param consumable        The consumable character
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \c Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        inline
        bool        Consume( char consumable, enums::Whitespaces trimBeforeConsume= enums::Whitespaces::Keep )
        {
            if ( trimBeforeConsume == enums::Whitespaces::Trim )
                TrimStart();

            if ( CharAtStart() != consumable )
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
         * @param trimBeforeConsume Determines if the string should be (left-) trimmed before the
         *                          consume operation. Defaults to \c Whitespaces::Keep.
         * @return \c true, if this object was starting with \p consumable and consequently the
         *         string was cut by one.
         ******************************************************************************************/
        inline
        bool        ConsumeFromEnd( char consumable, enums::Whitespaces trimBeforeConsume= enums::Whitespaces::Keep )
        {
            if ( trimBeforeConsume == enums::Whitespaces::Trim )
                TrimEnd();

            if ( CharAtEnd() != consumable )
                return false;
            length--;
            return true;
        }


        /** ****************************************************************************************
         * Reads a 32-Bit integer from this object. If successful, the front of this
         * \b %Substring is cut to point to first character that is not not belonging to the number.
         * If no number is found, \c false is returned and this object does not change.
         *
         * Leading whitespace characters are ignored. However, if after leading whitespaces no
         * number is found, then also these whitespaces remain.
         *
         * \note If this \b %Substring spans several integer values which are separated by
         *       whitespaces, concatenated calls to this method will read one by one, without
         *       further trimming or tokenizing
         *       (see \ref aworx::lib::strings::Tokenizer "Tokenizer").
         *       Therefore, by providing the parameter \p whiteSpaces, it is possible to
         *       easily read several numbers which are separated by user defined characters.
         *
         * @param whitespaces  The whitespaces used to trim the substring at the front before
         *                     reading the value.
         *                     Defaults to  \ref aworx::DefaultWhitespaces
         * @param[out] result  A reference to the result value.
         *
         * @return  \c true if an integer was found and, \c false otherwise.
         ******************************************************************************************/
        bool     ConsumeInteger( int32_t& result, const TString& whitespaces = DefaultWhitespaces )
        {
            int64_t result64;
            bool    returnValue= ConsumeLong( result64, whitespaces );
            result= (int32_t) result64;
            return  returnValue;
        }

        /** ****************************************************************************************
         * Reads a 64-Bit integer from this object. If successful, the front of this
         * \b %Substring is cut to point to first character that is not not belonging to the number.
         * If no number is found, \c false is returned and this object does not change.
         *
         * Leading whitespace characters are ignored. However, if after leading whitespaces no
         * number is found, then also these whitespaces remain.
         *
         * \note
         *   If this \b %Substring spans several float values which are separated by
         *   whitespaces, concatenated calls to this method will read one by one,
         *   without the need of further trimming or
         *   \ref aworx::lib::strings::Tokenizer "'tokenizing'").
         *   Therefore, by providing the parameter \p whitespaces, it is possible to
         *   easily read several numbers which are separated by user defined characters.
         *
         * @param[out] result  A reference to the result value.
         * @param whitespaces  White space characters used to trim the substring at the front
         *                     before reading the value.
         *                     Defaults to  \ref aworx::DefaultWhitespaces
         *
         * @return  \c true if an integer was found and, \c false otherwise.
         ******************************************************************************************/
        ALIB_API
        bool   ConsumeLong( int64_t& result, const TString& whitespaces =DefaultWhitespaces );

        /** ****************************************************************************************
         * Reads a floating point number from this object. If successful, the front of
         * this \b %Substring is cut to point to first character that is not belonging to the
         * floating point number.
         * If no number is found, \c false is returned and this object does not change.
         *
         * Leading whitespace characters are ignored. However, if after leading whitespaces no
         * number is found, then also these whitespaces remain.
         *
         * \note
         *   If this \b %Substring spans several float values which are separated by
         *   whitespaces, concatenated calls to this method will read one by one,
         *   without the need of further trimming or
         *   \ref aworx::lib::strings::Tokenizer "'tokenizing'").
         *   Therefore, by providing the parameter \p whitespaces, it is possible to
         *   easily read several numbers which are separated by user defined characters.
         *
         *  See class \ref aworx::lib::strings::NumberFormat "NumberFormat"
         *  for more information about conversion methods of floating point values in ALib.
         *  If no object of this type is provided with optional parameter \p numberFormat,
         *  the static default object found in
         *  \ref aworx::lib::strings::NumberFormat::Global "NumberFormat::Global"
         *  is used.
         *
         * @param[out] result  A reference to the result value.
         * @param numberFormat The object performing the conversion and defines the output format.
         *                     Optional and defaults to nullptr.
         * @param whitespaces  White space characters used to trim the substring at the front
         *                     before reading the value.
         *                     Defaults to  \ref aworx::DefaultWhitespaces
         *
         * @return  \c true if a number was found and, \c false otherwise.
         ******************************************************************************************/
        ALIB_API
        bool  ConsumeFloat( double&         result,
                            NumberFormat*   numberFormat     =nullptr,
                            const TString   whitespaces      =DefaultWhitespaces   );


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
        Substring& Split( int position, Substring& target, int separatorWidth  =0, bool trim= false )

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

            target.Set( this, position + separatorWidth, length - position - separatorWidth );
            length= position;
            if( trim )
            {
                this ->Trim();
                target.Trim();
            }
            return *this;
        }

}; // class Substring

}} // namespace lib::strings

/** Type alias name in namespace #aworx. */
using     Substring =    lib::strings::Substring;

} // namespace aworx

#if defined(_MSC_VER)
    #pragma warning( pop )
#endif
#endif // HPP_ALIB_STRINGS_ASSUBSTRING



