// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

/**
 * This sub-namespace  provides some utility classes which are related
 * to string classes found in namespace \ref com::aworx::lib::strings.
 */
package com.aworx.lib.strings.util;

import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lib.strings.Substring;
import com.aworx.lib.lang.Whitespaces;


/** ************************************************************************************************
 *  This class splits a given character array (e.g. a <em>const char*</em> or an
 *  \ref com::aworx::lib::strings::AString "AString" object),
 *  which contains data separated by a delimiter character, into tokens of type
 *  \ref com::aworx::lib::strings::Substring "Substring".
 *
 *  After an instance of this class is constructed, there are three methods available:
 *  - #hasNext: <br>
 *    Indicates if there are further tokens available.
 *  - #next:     <br>
 *    Sets the Substring in field #actual to reference the next token and returns it.<br>
 *    With each call to %Next, a different delimiter can be provided, which then serves as the
 *    delimiter for this and subsequent tokens.<br>
 *    The returned token by default will be trimmed according to the current trimable characters.
 *  - #rest:
 *    Like #next, however returns the complete remaining region without searching for
 *    further delimiters (and tokens).<br>
 *    After this method was invoked, #hasNext() will return false.
 *
 *  After a token was retrieved, it might be modified using the interface of class
 *  \ref com::aworx::lib::strings::Substring "Substring".
 *  (In other words, the tokenizer does not rely on the bounds of the current token when receiving
 *  the next.) Consequently, it is allowed to recursively tokenize a token by creating a
 *  different instance of class Tokenizer providing the returned token as input.
 *
 *  If created or set using a reference of class AString, the buffer of AString is <em>not</em>
 *  copied. This allows efficient operations on sub-strings of class AString. However, the source
 *  string must not be changed (or only in a controlled way) during the use the %Tokenizer instance.
 *
 *  Objects of this class can be reused by freshly initializing them using one of the overloaded
 *  <em>Set</em> methods.
 *
 *  <b>Sample code</b>:<br>
 *  The following code sample shows how to tokenize a string, including using one nested
 *  tokenizer:
 *
 *  \snippet "UT_alib_strings_Substring.java"     DOC_SAMPLES_ALIB_LIB_STRING_TOKEN
 *
 *  The output will be:
 *
 *  \snippet "DOC_SAMPLES_ALIB_LIB_STRING_TOKEN.txt"     OUTPUT
 *
 **************************************************************************************************/
public class Tokenizer
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
        /**  A %Substring that represents the part of the underlying data that has not been
         *   tokenized, yet.
         */
        public Substring      rest                                                = new Substring();

        /** The actual token, which was returned the last recent invocation of #next() or #rest().
         *  It is allowed to manipulate this field any time, for example changing its whitespace
         *  characters definition.*/
        public Substring      actual                                              = new Substring();

        /** The white space characters used to trim the tokens.
         *  Defaults to CString.DEFAULT_WHITESPACES */
        public char[]         whitespaces                              =CString.DEFAULT_WHITESPACES;


    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /**  The most recently set delimiter used by default for the next token extraction. */
        protected char        delim;

        /**  If \c true, empty tokens are omitted.  */
        protected boolean     skipEmptyTokens;

    // #############################################################################################
    //  Constructors/Destructor
    // #############################################################################################
        /** ****************************************************************************************
         * Constructs an empty tokenizer. Before use, method #set to initialize needs to be invoked.
         ******************************************************************************************/
        public Tokenizer()
        {
            rest= new Substring();
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given cstring.
         *
         * @param  src             The string to be tokenized.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public Tokenizer( String src, char delim, boolean skipEmptyTokens  )
        {
            set( src, delim, skipEmptyTokens );
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given cstring.
         *
         * @param  src        The character array to use as the source for the tokens.
         * @param  delim      The delimiter that separates the tokens. Can be changed with every
         *                    next token.
         ******************************************************************************************/
        public Tokenizer( String src, char delim  )
        {
            set( src, delim, false );
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given
         *  \ref com::aworx::lib::strings::AString "AString".
         *
         * @param  src             The string to be tokenized.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public Tokenizer( AString src, char delim, boolean skipEmptyTokens  )
        {
            set( src, delim, skipEmptyTokens );
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given
         *  \ref com::aworx::lib::strings::AString "AString".
         *
         * @param  src        The AString to use as the source for the tokens.
         * @param  delim      The delimiter that separates the tokens. Can be changed with every
         *                    next token.
         ******************************************************************************************/
        public Tokenizer( AString src, char delim  )
        {
            set( src, delim, false );
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given
         *  \ref com::aworx::lib::strings::Substring "Substring".
         *
         * @param  src             The string to be tokenized.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public Tokenizer( Substring src, char delim, boolean skipEmptyTokens  )
        {
            set( src, delim, skipEmptyTokens );
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given
         *  \ref com::aworx::lib::strings::Substring "Substring".
         *
         * @param  src        The substring to use as the source for the tokens.
         * @param  delim      The delimiter that separates the tokens. Can be changed with every
         *                    next token.
         ******************************************************************************************/
        public Tokenizer( Substring src, char delim  )
        {
            set( src, delim, false );
        }

    // #############################################################################################
    //  Interface
    // #############################################################################################
        /** ****************************************************************************************
         *  Sets the tokenizer to the new source and delim.
         *
         * @param  str             The character array to use as the source for the tokens.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public void set( String str, char delim, boolean skipEmptyTokens  )
        {
            this.delim=             delim;
            this.skipEmptyTokens=   skipEmptyTokens;
            rest.set( str );
            actual.setNull();
        }

        /** ****************************************************************************************
         *  Sets the tokenizer to the new source and delim.
         *
         * @param  str        The character array to use as the source for the tokens.
         * @param  delim      The delimiter that separates the tokens. Can be changed with every
         *                    next token.
         ******************************************************************************************/
        public void set( String str, char delim  )
        {
            set( str, delim, false );
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given AString.
         *
         * @param  astring         The AString to use as the source for the tokens.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public void set( AString astring, char delim, boolean skipEmptyTokens  )
        {
            this.delim=             delim;
            this.skipEmptyTokens=   skipEmptyTokens;
            rest.set( astring );
            actual.setNull();
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given AString.
         *
         * @param  astring    The AString to use as the source for the tokens.
         * @param  delim      The delimiter that separates the tokens. Can be changed with every
         *                    next token.
         ******************************************************************************************/
        public void set( AString astring, char delim  )
        {
            set( astring, delim, false );
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given Substring.
         *
         * @param  substring       The substring to use as the source for the tokens.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public void set( Substring substring, char delim, boolean skipEmptyTokens  )
        {
            this.delim=             delim;
            this.skipEmptyTokens=   skipEmptyTokens;
            rest.set( substring );
            actual.setNull();
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given Substring.
         *
         * @param  substring  The substring to use as the source for the tokens.
         * @param  delim      The delimiter that separates the tokens. Can be changed with every
         *                    next token.
         ******************************************************************************************/
        public void set( Substring substring, char delim  )
        {
            set( substring, delim, false );
        }

        /** ****************************************************************************************
         * Returns the next token, which is afterwards also available through field #actual.
         * If no further token  was available, the returned
         * \ref com::aworx::lib::strings::Substring "Substring" will be 'nulled'
         * (see \ref com::aworx::lib::strings::Substring::isNull "Substring.isNull").
         * To prevent this, the availability of a next token should be
         * checked using method #hasNext().
         *
         * For clarification, see the explanation and sample code in this classes documentation.
         *
         *  @param trimming  Determines if the token is trimmed in respect to the white space
         *                   characters defined in field #whitespaces.
         *                   Defaults to \b Whitespaces.TRIM.
         *  @param newDelim  The delimiter separates the tokens. Defaults to 0, which keeps the
         *                   current delimiter intact.
         *                   A new delimiter can be provided for every next token.
         * @return true if a next token was available, false if not.
         ******************************************************************************************/
        public Substring  next( Whitespaces trimming, char newDelim )
        {
            if ( rest.isNull() )
            {
                actual.setNull();
                return actual;
            }

            // change of delim?
            if ( newDelim != '\0' )
                delim= newDelim;

            do
            {
                // set buf, start and find end
                actual.buf=   rest.buf;
                actual.start= rest.start;

                int nextDelimiter= rest.indexOf( delim );
                if ( nextDelimiter >= 0 )
                {
                    rest.start+=  nextDelimiter + 1;
                    actual.end=      rest.start  - 2;
                }
                else
                {
                    actual.end=  rest.end;
                    rest.setNull();
                }


                // trim
                if ( trimming == Whitespaces.TRIM )
                    actual.trim( whitespaces );
            }
            while( skipEmptyTokens && actual.isEmpty() && rest.isNotNull() );

            return actual;
        }

        /** ****************************************************************************************
         * Returns the next token, which is afterwards also available through field #actual.
         * If no further token  was available, the returned
         * \ref com::aworx::lib::strings::Substring "Substring" will be 'nulled'
         * (see \ref com::aworx::lib::strings::Substring::isNull "Substring.isNull").
         * To prevent this, the availability of a next token should be
         * checked using method #hasNext.
         *
         * For clarification, see the explanation and sample code in this classes documentation.
         *
         *  @param trimming  Determines if the token is trimmed in respect to the white space
         *                   characters defined in field #whitespaces.
         *                   Defaults to \b Whitespaces.TRIM.
         * @return true if a next token was available, false if not.
         ******************************************************************************************/
        public Substring  next( Whitespaces trimming )
        {
            return next( trimming, '\0');
        }

        /** ****************************************************************************************
         * Returns the next token, which is afterwards also available through field #actual.
         * If no further token  was available, the returned
         * \ref com::aworx::lib::strings::Substring "Substring" will be 'nulled'
         * (see \ref com::aworx::lib::strings::Substring::isNull "Substring.isNull").
         * To prevent this, the availability of a next token should be
         * checked using method #hasNext().
         *
         * For clarification, see the explanation and sample code in this classes documentation.
         * @return true if a next token was available, false if not.
         ******************************************************************************************/
        public Substring  next()
        {
            return next( Whitespaces.TRIM, '\0');
        }

        /** ****************************************************************************************
         * Returns the currently remaining string (without searching for further delimiter
         * characters).<br>
         * After this call #hasNext will return false and #next will return a nulled Substring.
         *  @param trimming  Determines if the token is trimmed in respect to the white space
         *                   characters defined in field #whitespaces.
         *                   Defaults to \b Whitespaces.TRIM.
         * @return The rest of the original source string, which was not returned by #next(), yet.
         ******************************************************************************************/
        public Substring  getRest( Whitespaces trimming )
        {
            // set start, end and end of tokenizer
            actual.set( rest );
            if ( trimming == Whitespaces.TRIM )
                actual.trim( whitespaces );
            rest.setNull();
            return actual;
        }

        /** ****************************************************************************************
         * Returns the currently remaining string (without searching for further delimiter
         * characters).
         * After this call #hasNext will return false and #next will return a nulled Substring.
         * @return The rest of the original source string, which was not returned by #next(), yet.
         ******************************************************************************************/
        public Substring  getRest()
        {
            return getRest( Whitespaces.TRIM );
        }

        /** ****************************************************************************************
         * If this returns true, a call to #next will be successful and will return a
         * Substring which is not nulled.
         * @return true if a next token is available.
         ******************************************************************************************/
        public boolean    hasNext()
        {
            return rest.isNotNull() && ( !skipEmptyTokens || rest.isNotEmpty() );
        }



    /** ****************************************************************************************
     * This is for debugging purposes. E.g. this enables the \e Eclipse IDE to display
     * object descriptions in the debugger.
     * @returns A human readable string representation of this object.
     ******************************************************************************************/
    @Override
    public String toString()
    {
        return "Actual: \"" + actual.toString() + "\" Rest: \"" + rest.toString() + "\"";
    }

} // class Tokenizer



