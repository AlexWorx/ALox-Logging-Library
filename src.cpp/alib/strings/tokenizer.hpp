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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_STRINGS_TOKENIZER)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_STRINGS_TOKENIZER
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_STRINGS_TOKENIZER 1
#endif

// #################################################################################################
// includes
// #################################################################################################
#if !defined (HPP_ALIB_STRINGS_ASSUBSTRING)
    #include "alib/strings/substring.hpp"
#endif

#if !defined (_GLIBCXX_IOSFWD ) && !defined(_IOSFWD_)
    #include <iosfwd>
#endif

namespace aworx {
namespace           lib {
namespace                   strings {

/** ************************************************************************************************
 * This class operates on strings which contains data separated by a delimiter character.
 * It identifies the substrings between the delimiters as \e tokens of type
 * \ref aworx::lib::strings::Substring "Substring". After an instance of this class is constructed,
 * three methods are available:
 * - #HasNext: Indicates if there are further tokens available.
 * - #Next: Sets field #Actual (which is of type Substring) to reference the next token and
 *   returns it.<br>
 *   With each call to %Next, a different delimiter can be provided, which then serves as the
 *   delimiter for this and subsequent tokens.<br>
 *   The returned token by default will be trimmed according to the current trimable characters.
 * - #Rest:
 *   Like #Next, however returns the complete remaining region without searching for
 *   further delimiters (and tokens).<br>
 *   After this method was invoked, #HasNext() will return \c false.
 *
 * After a token was retrieved, it might be modified using the interface of class
 * \ref aworx::lib::strings::Substring "Substring" as the tokenizer does not rely on the bounds of
 * the current token when receiving the next. Furthermore, even field #Rest is allowed
 * to be changed using the interface of \b %Substring if it seems appropriate. The effect is the
 * same as if method #Set was invoked to apply a different source string.
 *
 * Objects of this class can be reused by freshly initializing them using method #Set.
 *
 * <b>Sample code</b>:<br>
 * The following code sample shows how to tokenize a string:
 *
 * \snippet "DOX_ALIB_TOKENIZER.cpp"     DOX_ALIB_TOKENIZER
 *
 * The output will be:
 *
 * \snippet "DOX_ALIB_TOKENIZER.txt"     OUTPUT
 *
 **************************************************************************************************/
class Tokenizer
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /**
         *  A \ref aworx::lib::strings::Substring "Substring" that represents the part of
         *  the underlying data that has not been tokenized, yet.
         *  It is allowed to manipulate this public field, which has a similar effect as
         *  using method #Set.<br>
         */
        Substring    Rest;

        /**
         *  The actual token, which is returned with every invocation of #Next() or #Rest().
         *  It is allowed to manipulate this field any time.<br>
         */
        Substring    Actual;

        /**
         * The white spaces characters used to trim the tokens.
         * Defaults to  \ref aworx::DefaultWhitespaces
         */
        String16       Whitespaces                                            = DefaultWhitespaces;


    // #############################################################################################
    // Internal fields
    // #############################################################################################
    protected:
        /**  The most recently set delimiter used by default for the next token extraction. */
        char           delim;


    // #############################################################################################
    //  Constructors/Destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Constructs a tokenizer to work on a given string.
         *
         * @param  src    The string to be tokenized
         * @param  delim  The delimiter that separates the tokens. Can be changed with every
         *                next token.
         ******************************************************************************************/
        Tokenizer( const String& src, char delim )
        : Rest(src)
        {
            this->delim=    delim;
        }

    // #############################################################################################
    //  Interface
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Resets a tokenizer to work on a given string.
         *
         * @param  src    The string to be tokenized
         * @param  delim  The delimiter that separates the tokens. Can be changed with every
         *                next token.
         ******************************************************************************************/
        void Set( const String& src, char delim )
        {
            Rest.Set( src );
            this->delim=  delim;
            Actual.SetNull();
        }

        /** ****************************************************************************************
         * Returns the next token, which is afterwards also available through field #Actual.
         * If no further token  was available, the returned
         * \ref aworx::lib::strings::Substring "Substring" will be \e nulled.
         * (see \ref aworx::lib::strings::String::IsNull "String::IsNull").
         * To prevent this, the availability of a next token should be
         * checked using method #HasNext().
         *
         * For clarification, see the explanation and sample code in this classes documentation.
         *
         *  @param trimming  Determines if the token is trimmed in respect to the white space
         *                   characters defined in field #Whitespaces.
         *                   Defaults to \c Whitespaces.Trim.
         *  @param newDelim  The delimiter separates the tokens. Defaults to 0, which keeps the
         *                   current delimiter intact.
         *                   However, it a new delimiter can be provided for every next token.
         * @return \c true if a next token was available, \c false if not.
         ******************************************************************************************/
        ALIB_API
        Substring&  Next( enums::Whitespaces trimming= enums::Whitespaces::Trim, char newDelim= '\0' );

        /** ****************************************************************************************
         * Returns the currently remaining string (without searching for further delimiter
         * characters).
         * After this call #HasNext will return \c false and #Next will return a \e nulled Substring.
         *  @param trimming  Determines if the token is trimmed in respect to the white space
         *                   characters defined in field #Whitespaces.
         *                   Defaults to \c Whitespaces.Trim.
         * @return The rest of the original source string, which was not returned by #Next(), yet.
         ******************************************************************************************/
        Substring&  GetRest( enums::Whitespaces trimming= enums::Whitespaces::Trim )
        {
            // set start, end and end of tokenizer
            Actual=  Rest;
            if ( trimming == enums::Whitespaces::Trim )
                Actual.Trim( Whitespaces );
            Rest.SetNull();
            return Actual;
        }

        /** ****************************************************************************************
         * If this returns \c true, a call to #Next will be successful and will return a
         * Substring which is not \e nulled.
         * @return \c true if a next token is available.
         ******************************************************************************************/
        bool        HasNext()       { return Rest.IsNotNull(); }

}; // class Tokenizer

}} // namespace lib::strings

/** Type alias name in namespace #aworx. */
using     Tokenizer=     aworx::lib::strings::Tokenizer;

}  // namespace aworx

#endif // HPP_ALIB_STRINGS_TOKENIZER
