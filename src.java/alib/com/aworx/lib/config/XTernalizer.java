// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lib.strings.Substring;

/** ************************************************************************************************
 * This virtual class is used by classes derived from \alib{config,ConfigurationPlugin}
 * to convert external string to internal values and vice versa, and for parsing lists of values
 * from an external string.
 *
 * Class \b %ConfigurationPlugin owns a default object with field
 * \alib{config::ConfigurationPlugin,defaultStringConverter} which by default points to field
 * \alib{config::ConfigurationPlugin,stringConverter}.
 *
 * \note
 *   Replacing the converters is deemed to be an advanced usage of \b %ALib. Consult the source code
 *   for detailed information about how to implement an application specific converter.
 *
 * This default implementation proceeds as follows:
 * - "Externalizing" a value:
 *   - Value is surrounded by quotes if it starts or ends with spaces or if it includes
 *     the delimiter token.
 *   - A few characters are escaped using \c '\\'. Those are
 *     \c \\n, \c \\r, \c \\t , \c \\a, \c \\b, \c \\v, \c \\f, \c \\e and also
 *     the double quotation marks \c \\" and the backslash itself (\c \\\\).
 *
 * - "Internalizing" a value:
 *   - If (non-escaped) quote \c " characters are found, those are removed and whitespaces
 *     within such quotes are kept.
 *   - Escaped characters are converted to their original value.
 *
 * - Loading variables from external strings:
 *   - If provided variable has a valid delimiter set, this character is used to tokenize
 *     the external string.
 *   - Values are trimmed, unless quoted. Quotes characters themselves are removed.
 *   - Delimiters found within a pair of quotes are ignored.
 *   - Each value found is internalized separately
 **************************************************************************************************/
public class XTernalizer
{
    /** a reusable AString */
    protected       AString         tmpAS           = new AString();

    /** a reusable Substring */
    protected       Substring       tmpSubs         = new Substring();

    /** a reusable Substring */
    protected       Substring       tmpSubs2        = new Substring();

    /** ********************************************************************************************
     * If field \alib{config,Variable.delim} is <c>'\0'</c>, just invokes #internalizeValue.
     * Otherwise, parses values using the delimiter. Quotes are removed and parts within quotes
     * are kept as is. Also, delimiters in quotes are ignored.
     *
     * @param  variable The destination variable.
     * @param  src      The source string
     **********************************************************************************************/
    public  void    loadFromString( Variable variable, Object src )
    {
        variable.clearValues();
        AString varValue= variable.add();

        Substring subs= null;
        if( src instanceof Substring)
            subs= (Substring) src;
        else if ( src instanceof AString )
        {
            subs= tmpSubs;
            subs.set( (AString) src );
        }
        else
        {
            tmpAS._()._( src );
            tmpSubs.set( tmpAS );
            subs= tmpSubs;
        }

        if( variable.delim == '\0' )
        {
            internalizeValue( subs, varValue );
            return;
        }

        // tokenize
        boolean inQuote=      false;
        boolean lastWasSlash= false;
        int  idx=          0;
        while( idx < subs.length()  )
        {
            char c= subs.charAt( idx++ );

            if( lastWasSlash )
            {
                lastWasSlash= false;
                continue;
            }

            if( c== '\\' )
            {
                lastWasSlash= true;
                continue;
            }

            if( c== '"' )
            {
                inQuote= !inQuote;
                continue;
            }

            if( !inQuote && c == variable.delim )
            {
                tmpSubs2.set( subs, 0, idx - 1 );
                internalizeValue( tmpSubs2, varValue );
                varValue= variable.add();
                subs.consumeChars( idx );
                subs.trimStart();
                idx= 0;
            }
        }
        if ( subs.isNotEmpty() )
        {
            internalizeValue( subs, varValue );
        }
    }

    /** ********************************************************************************************
     * Trims \p src, removes surrounding quotes and , un-escapes characters.
     *
     * @param  src      The source string
     * @param  dest     The destination string
     **********************************************************************************************/
    @SuppressWarnings ("static-method")
    public void internalizeValue( Substring src, AString dest )
    {
        src.trim();
        if(src.charAtStart() == '"'  && src.charAtEnd() == '"')
        {
            src.consumeChar();
            src.consumeCharFromEnd();
        }
        boolean lastWasSlash= false;

        while( src.isNotEmpty() )
        {
            char c= src.consumeChar();

            if( lastWasSlash )
            {
                lastWasSlash= false;
                char escChr= c == '\\' ? '\\' :
                             c == '"'  ? '"'  :
                             c == 'r'  ? '\r' :
                             c == 'n'  ? '\n' :
                             c == 't'  ? '\t' :
                             c == 'a'  ? '\007' :
                             c == 'b'  ? '\b' :
                             c == 'v'  ? '\013' :
                             c == 'f'  ? '\f' :
                             c == 'e'  ? '\033' :
                             c;

                dest._(escChr);
                continue;
            }

            if( c== '\\' )
            {
                lastWasSlash= true;
                continue;
            }

            dest._NC(c);
        }
    }


    /** ********************************************************************************************
     * Converts the given \p src string to an external representation.
     *
     * @param  src      The source string
     * @param  dest     The destination string
     * @param  delim    If this character is found in the string, the value is quoted
     **********************************************************************************************/
    public void externalizeValue( Object src, AString dest, char delim )
    {
        Substring subs= null;
        if( src instanceof Substring)
            subs= (Substring) src;
        else if ( src instanceof AString )
        {
            subs= tmpSubs;
            subs.set( (AString) src );
        }
        else
        {
            tmpAS._()._( src );
            tmpSubs.set( tmpAS );
            subs= tmpSubs;
        }


        boolean needsQuotes=       subs.charAtStart() == ' '
                               ||  subs.charAtStart() == '\t'
                               ||  subs.charAtEnd()   == ' '
                               ||  subs.charAtEnd()   == '\t'
                               ||  subs.indexOf( delim ) >= 0;
        if ( needsQuotes )
            dest._('"');

        while( subs.isNotEmpty() )
        {
            char c= subs.consumeChar();

            switch(c)
            {
                case '"'    : dest._NC( needsQuotes ? "\\\"" : "\"");
                              break;
                case '\\'   : dest._NC("\\\\"); break;
                case '\r'   : dest._NC("\\r" ); break;
                case '\n'   : dest._NC("\\n" ); break;
                case '\t'   : dest._NC("\\t" ); break;
                case '\007' : dest._NC("\\a" ); break;
                case '\b'   : dest._NC("\\b" ); break;
                case '\013' : dest._NC("\\v" ); break;
                case '\f'   : dest._NC("\\f" ); break;
                case '\033' : dest._NC("\\e" ); break;

                default   : dest._(c);        break;
            }
        }

        if ( needsQuotes )
            dest._('"');
    }
}



