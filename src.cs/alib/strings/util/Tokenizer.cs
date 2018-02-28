// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Text;
using cs.aworx.lib.lang;

/**
 * This sub-namespace  provides some utility classes which are related
 * to string classes found in namespace \ref cs.aworx.lib.strings.
 */
namespace cs.aworx.lib.strings.util  {


/** ************************************************************************************************
 *  This class splits a given character array (e.g. a <em>const char*</em> or an
 *  \ref cs.aworx.lib.strings.AString "AString" object),
 *  which contains data separated by a delimiter character, into tokens of type
 *  \ref cs.aworx.lib.strings.Substring "Substring".
 *
 *  After an instance of this class is constructed, there are three methods available:
 *  - #HasNext: <br>
 *    Indicates if there are further tokens available.
 *  - #Next:     <br>
 *    Sets the Substring in field #Actual to reference the next token and returns it.<br>
 *    With each call to %Next, a different delimiter can be provided, which then serves as the
 *    delimiter for this and subsequent tokens.<br>
 *    The returned token by default will be trimmed according to the current trimable characters.
 *  - #Rest:
 *    Like #Next, however returns the complete remaining region without searching for
 *    further delimiters (and tokens).<br>
 *    After this method was invoked, #HasNext() will return false.
 *
 *  After a token was retrieved, it might be modified using the interface of class
 *  \ref cs.aworx.lib.strings.Substring "Substring".
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
 *  \snippet "UT_alib_strings_Substring.cs"     DOC_SAMPLES_ALIB_LIB_STRING_TOKEN
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
        public Substring      Rest                                                = new Substring();

        /** The actual token, which was returned the last recent invocation of #Next() or #Rest().
         *  It is allowed to manipulate this field any time, for example changing its whitespace
         *  characters definition.*/
        public Substring      Actual                                              = new Substring();


        /** The white space characters used to trim the tokens.
         *  Defaults to CString.DefaultWhitespaces */
        public char[]         Whitespaces                              = CString.DefaultWhitespaces;

    // #############################################################################################
    // Internal fields
    // #############################################################################################

        /**  The most recently set delimiter used by default for the next token extraction. */
        protected char        delim                                                          = '\0';

        /**  If \c true, empty tokens are omitted.  */
        protected bool        skipEmptyTokens;


    // #############################################################################################
    //  Constructors/Destructor
    // #############################################################################################
        /** ****************************************************************************************
         * Constructs an empty tokenizer. Before use, method #Set to initialize needs to be invoked.
         ******************************************************************************************/
        public Tokenizer()
        {
            Rest= new Substring();
        }

        /** ****************************************************************************************
         * Constructs a tokenizer to work on a given cstring.
         *
         * @param  src             The string to be tokenized.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public Tokenizer( String src, char delim, bool skipEmptyTokens= false )
        {
            Set( src, delim, skipEmptyTokens );
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given
         *  \ref cs.aworx.lib.strings.AString "AString".
         *
         * @param  src             The string to be tokenized.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public Tokenizer( AString src, char delim, bool skipEmptyTokens= false )
        {
            Set( src, delim, skipEmptyTokens );
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given
         *  \ref cs.aworx.lib.strings.Substring "Substring".
         *
         * @param  src             The string to be tokenized.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public Tokenizer( Substring src, char delim, bool skipEmptyTokens= false )
        {
            Set( src, delim, skipEmptyTokens );
        }

    // #############################################################################################
    //  Interface
    // #############################################################################################
        /** ****************************************************************************************
         *  Sets the tokenizer to the new source and delim.
         *
         * @param  src             The string to be tokenized.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public void Set( String src, char delim, bool skipEmptyTokens= false )
        {
            this.delim=             delim;
            this.skipEmptyTokens=   skipEmptyTokens;
            Rest.Set( src );
            Actual.SetNull();
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given AString.
         *
         * @param  src             The string to be tokenized.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public void Set( AString src, char delim, bool skipEmptyTokens= false  )
        {
            this.delim=             delim;
            this.skipEmptyTokens=   skipEmptyTokens;
            Rest.Set( src );
            Actual.SetNull();
        }

        /** ****************************************************************************************
         *  Constructs a tokenizer to work on a given Substring.
         *
         * @param  src             The string to be tokenized.
         * @param  delim           The delimiter that separates the tokens. Can be changed with
         *                         every next token.
         * @param  skipEmptyTokens If \c true, empty tokens are omitted.
         *                         Optional and defaults to \c false.
         ******************************************************************************************/
        public void Set( Substring src, char delim, bool skipEmptyTokens= false  )
        {
            this.delim=             delim;
            this.skipEmptyTokens=   skipEmptyTokens;
            Rest.Set( src );
            Actual.SetNull();
        }

        /** ****************************************************************************************
         * Returns the next token, which is afterwards also available through field #Actual.
         * If no further token  was available, the returned
         * \ref cs.aworx.lib.strings.Substring "Substring" will be 'nulled'
         * (see \ref cs.aworx.lib.strings.Substring.IsNull "Substring.IsNull").
         * To prevent this, the availability of a next token should be
         * checked using method #HasNext().
         *
         * For clarification, see the explanation and sample code in this classes documentation.
         *
         *  @param trimming  Determines if the token is trimmed in respect to the white space
         *                   characters defined in field #Whitespaces.
         *                   Defaults to \b Whitespaces.Trim.
         *  @param newDelim  The delimiter separates the tokens. Defaults to 0, which keeps the
         *                   current delimiter intact.
         *                   A new delimiter can be provided for every next token.
         * @return true if a next token was available, false if not.
         ******************************************************************************************/
        public Substring    Next( Whitespaces trimming= lang.Whitespaces.Trim, char newDelim= '\0' )
        {
            if ( Rest.IsNull() )
            {
                Actual.SetNull();
                return Actual;
            }

            // change of delim?
            if ( newDelim != '\0' )
                delim= newDelim;

            do
            {
                // set buf, start and find end
                Actual.Buf=   Rest.Buf;
                Actual.Start= Rest.Start;

                int nextDelimiter= Rest.IndexOf( delim );
                if ( nextDelimiter >= 0 )
                {
                    Rest.Start+=  nextDelimiter + 1;
                    Actual.End=      Rest.Start  - 2;
                }
                else
                {
                    Actual.End=  Rest.End;
                    Rest.SetNull();
                }


                // trim
                if ( trimming == lang.Whitespaces.Trim )
                    Actual.Trim(Whitespaces);
            }
            while( skipEmptyTokens && Actual.IsEmpty() && Rest.IsNotNull() );

            return Actual;
        }


        /** ****************************************************************************************
         * Returns the currently remaining string (without searching for further delimiter
         * characters).<br>
         * After this call #HasNext will return false and #Next will return a nulled Substring.
         *  @param trimming  Determines if the token is trimmed in respect to the white space
         *                   characters defined in field #Whitespaces.
         *                   Defaults to \b Whitespaces.Trim.
         * @return The rest of the original source string, which was not returned by #Next(), yet.
         ******************************************************************************************/
        public Substring  GetRest( Whitespaces trimming= lang.Whitespaces.Trim )
        {
            // set start, end and end of tokenizer
            Actual.Set( Rest );
            if ( trimming == lang.Whitespaces.Trim )
                Actual.Trim(Whitespaces);
            Rest.SetNull();
            return Actual;
        }

        /** ****************************************************************************************
         * If this returns true, a call to #Next will be successful and will return a
         * Substring which is not nulled.
         * @return true if a next token is available.
         ******************************************************************************************/
        public bool    HasNext()
        {
            return Rest.IsNotNull() && ( !skipEmptyTokens || Rest.IsNotEmpty() );
        }


    /** ****************************************************************************************
     * This is for debugging purposes. E.g. this enables the \e Monodevelop IDE to display
     * object descriptions in the debugger.
     * @returns A human readable string representation of this object.
     ******************************************************************************************/
    public override String ToString()
    {
        return "Actual: \"" + Actual.ToString() + "\" Rest: \"" + Rest.ToString() + "\"";
    }
} // class Tokenizer


} // namespace / EOF
