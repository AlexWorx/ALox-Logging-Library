// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.CString;
import com.aworx.lib.strings.Substring;

/** ************************************************************************************************
 * This virtual class is used by classes derived from
 * \ref com::aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin"
 * to convert external string to internal values and vice versa, and for parsing lists of values
 * from an external string.
 *
 * Class \b %ConfigurationPlugin owns a default object with field
 * \ref com::aworx::lib::config::ConfigurationPlugin::defaultStringConverter "ConfigurationPlugin.defaultStringConverter",
 * to which field
 * \ref com::aworx::lib::config::ConfigurationPlugin::stringConverter "ConfigurationPlugin.stringConverter"
 * by default points to.
 *
 * \note
 *   Replacing the converters is deemed to be an advanced usage of ALib. Consult the source code
 *   for detailed information about how to implement an application specific converter.
 *
 * This default implementation proceeds as follows:
 * - "Externalizing" a value:
 *   - Value is surrounded by quotes if it starts or ends with spaces or if it includes
 *     the delimiter token.
 *   - A few characters are escaped using \c '\\', for example \c '\\n', \c '\\r', \c '\\t' and also
 *    the double quotation marks \c ".
 *
 * - "Internalizing" a value:
 *   - If (non-escaped) quote \c " characters are found, those are removed and whitespaces
 *     within such quotes are kept.
 *   - Escaped characters are converted to their original value.
 *
 * - Loading variables from external strings:
 *   - If provided variable has a valid delimiter set, this character is used to tokenize
 *     the external string.
 *   - Delimiters found within a pair of quotes \c " are ignored.
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
     * Parses values found in string \p src and adds them to \p variable.
     * @param  variable The destination variable.
     * @param  src      The source string
     **********************************************************************************************/
    public  void    loadFromString( Variable variable, Object src )
    {
        variable.clearValues();
        AString varValue= variable.addString();

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
                varValue= variable.addString();
                subs.consume( idx );
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
     * Internalizes a variable value that is provided in externalized format.
     * Specifically first the value is trimmed, then non-escaped quotes are removed, including
     * any whitespaces found between quoted strings. For example, the following sequence:
     *
     *          "one" - two" - "three"- four"
     *
     * would be read as:
     *
     *          one- two - three- four
     *
     * Furthermore, escaped characters are converted into their original value.
     *
     * @param  src      The source string
     * @param  dest     The destination string
     **********************************************************************************************/
    @SuppressWarnings ("static-method")
    public void internalizeValue( Substring src, AString dest )
    {
        src.trim();
        boolean inUnquoted=   true;
        boolean inQuote=      false;
        boolean lastWasSlash= false;

        while( src.isNotEmpty() )
        {
            char c= src.consume();

            if( lastWasSlash )
            {
                lastWasSlash= false;
                char escChr= c == '\\' ? '\\' :
                             c == 'n'  ? '\n' :
                             c == 'r'  ? '\r' :
                             c == 't'  ? '\t' :
                             c == '"'  ? '"'  : c;

                dest._(escChr);
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
                inUnquoted= false;
                continue;
            }

            if( inQuote || inUnquoted )
            {
                dest._(c);
                continue;
            }

            if( CString.indexOf( c, CString.DEFAULT_WHITESPACES ) >= 0 )
                continue;
            inUnquoted= true;

            dest._(c);
        }
    }


    /** ********************************************************************************************
     * Converts the given \p src string to an external representation. In particular, the following
     * rules apply:
     *   - \p src is surrounded by quotes if it starts or ends with spaces or if it includes
     *     the delimiter character \p delim.
     *   - A few characters are escaped using \c '\\', for example \c '\\n', \c '\\r', \c '\\t'
     *     and also the double quotation marks \c ".
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
                               ||  subs.charAtEnd()   == ' '
                               ||  subs.indexOf( delim ) >= 0;
        if ( needsQuotes )
            dest._('"');

        while( subs.isNotEmpty() )
        {
            char c= subs.consume();

            switch(c)
            {
                case '\\' : dest._NC("\\\\"); break;
                case '\r' : dest._NC("\\r" ); break;
                case '\n' : dest._NC("\\n" ); break;
                case '\t' : dest._NC("\\t" ); break;
                case '"'  : dest._NC("\\\""); break;
                default   : dest._(c);        break;
            }
        }

        if ( needsQuotes )
            dest._('"');
    }
}



