// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;

namespace cs.aworx.lib.config  {

// #################################################################################################
// class XTernalizer
// #################################################################################################

/** ************************************************************************************************
 * This virtual class is used by classes derived from \alib{config,ConfigurationPlugin}
 * to convert external string to internal values and vice versa, and for parsing lists of values
 * from an external string.
 *
 * Class \b %ConfigurationPlugin owns a default object with field
 * \alib{config.ConfigurationPlugin.defaultStringConverter}, to which field
 * \alib{config.ConfigurationPlugin.StringConverter} by default points to.
 *
 * \note
 *   Replacing the converters is deemed to be an advanced usage of ALib. Consult the source code
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
 *   - Delimiters found within a pair of quotes \c " are ignored.
 *   - Each value found is internalized separately
 **************************************************************************************************/
public class XTernalizer
{
    /** a reusable AString */
    protected       AString         tmpAS                                           = new AString();

    /** a reusable Substring */
    protected       Substring       tmpSubs                                       = new Substring();

    /** a reusable Substring */
    protected       Substring       tmpSubs2                                      = new Substring();

    /** ********************************************************************************************
     * Parses values found in string \p src and adds them to \p variable.
     * @param  variable The destination variable.
     * @param  src      The source string
     **********************************************************************************************/
    public virtual
    void    LoadFromString( Variable variable, Object src )
    {
        variable.ClearValues();
        AString varValue= variable.Add();

        Substring subs= null;
        if( src is Substring)
            subs= (Substring) src;
        else if ( src is AString )
        {
            subs= tmpSubs;
            subs.Set( (AString) src );
        }
        else
        {
            tmpAS._()._( src );
            tmpSubs.Set( tmpAS );
            subs= tmpSubs;
        }

        // tokenize
        bool inQuote=      false;
        bool lastWasSlash= false;
        int  idx=          0;
        while( idx < subs.Length()  )
        {
            char c= subs.CharAt( idx++ );

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

            if( !inQuote && c == variable.Delim )
            {
                tmpSubs2.Set( subs, 0, idx - 1 );
                InternalizeValue( tmpSubs2, varValue );
                varValue= variable.Add();
                subs.ConsumeChars( idx );
                subs.TrimStart();
                idx= 0;
            }
        }
        if ( subs.IsNotEmpty() )
        {
            InternalizeValue( subs, varValue );
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
    public virtual
    void InternalizeValue( Substring src, AString dest )
    {
        src.Trim();
        bool inUnquoted=   true;
        bool inQuote=      false;
        bool lastWasSlash= false;

        while( src.IsNotEmpty() )
        {
            char c= src.ConsumeChar();

            if( lastWasSlash )
            {
                lastWasSlash= false;
                char escChr= c == '"'  ? '"'  :
                             c == '\\' ? '\\' :
                             c == 'r'  ? '\r' :
                             c == 'n'  ? '\n' :
                             c == 't'  ? '\t' :
                             c == 'a'  ? '\a' :
                             c == 'b'  ? '\b' :
                             c == 'v'  ? '\v' :
                             c == 'f'  ? '\f' :
                             c == 'e'  ? '\x001B' :
                             c;

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

            if( CString.IndexOf( CString.DefaultWhitespaces, c) >= 0 )
                continue;
            inUnquoted= true;

            dest._(c);
        }
    }


    /** ********************************************************************************************
     * Converts the given \p src string to an external representation.
     *
     * @param  src      The source string
     * @param  dest     The destination string
     * @param  delim    If this character is found in the string, the value is quoted
     **********************************************************************************************/
    public virtual
    void ExternalizeValue( Object src, AString dest, char delim )
    {
        Substring subs= null;
        if( src is Substring)
            subs= (Substring) src;
        else if ( src is AString )
        {
            subs= tmpSubs;
            subs.Set( (AString) src );
        }
        else
        {
            tmpAS._()._( src );
            tmpSubs.Set( tmpAS );
            subs= tmpSubs;
        }


        bool needsQuotes=       subs.CharAtStart() == ' '
                            ||  subs.CharAtEnd()   == ' '
                            ||  subs.IndexOf( delim ) >= 0;
        if ( needsQuotes )
            dest._('"');

        while( subs.IsNotEmpty() )
        {
            char c= subs.ConsumeChar();

            switch(c)
            {
                case '"'  : dest._NC("\\\""); break;
                case '\\' : dest._NC("\\\\"); break;
                case '\r' : dest._NC("\\r" ); break;
                case '\n' : dest._NC("\\n" ); break;
                case '\t' : dest._NC("\\t" ); break;
                case '\a' : dest._NC("\\a" ); break;
                case '\b' : dest._NC("\\b" ); break;
                case '\v' : dest._NC("\\v" ); break;
                case '\f' : dest._NC("\\f" ); break;
                case '\x001B' : dest._NC("\\e" ); break;
                default   : dest._(c);        break;
            }
        }

        if ( needsQuotes )
            dest._('"');
    }
}

/** ************************************************************************************************
 * Abstract class that represents a plug in for class
 * \ref cs.aworx.lib.config.Configuration "Configuration"
 * to provide configuration data from specific configuration data source.
 *
 * See documentation of namespace #cs.aworx.lib.config for more information on ALib
 * external configuration variables.
 *
 * The plug-in also may have the ability to write data. The default implementation for writing
 * configuration data returns constant false, indicating that this plug-in never writes
 * anything (e.g. command line parameter plug-in, environment variable plug-in).
 *
 * Category and Variable names are character case insensitive for the plug-ins predefined
 * with ALib.
 * It is recommended to to ignore character case in custom specializations of this class
 * as well.
 *
 * \note
 *   In the C# version, some method of this class accept parameters of type <em>Object</em>.
 *   In this case, the object is converted to a string (if not of string type already).
 **************************************************************************************************/
public abstract class ConfigurationPlugin
{
        /** The default external string converter */
        protected  XTernalizer    defaultStringConverter= new XTernalizer();

        /** The external string converter.
         *  By default this points to field #defaultStringConverter.                 */
        public XTernalizer        StringConverter;

        /** ****************************************************************************************
         * Constructor which is protected, as this is an abstract class.
         ******************************************************************************************/
        protected ConfigurationPlugin() { StringConverter= defaultStringConverter; }

        /** ****************************************************************************************
         * Abstract method that has to be overwritten by descendants.
         * Searches and by default retrieves the value of a configuration variable.
         * If \p searchOnly is \c true, then the variable value is not read.
         *
         * @param variable      The variable to retrieve.
         * @param searchOnly    If \c true, the variable must not be read. Defaults to \c false.
         * @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        public abstract bool  Load( Variable variable, bool searchOnly= false );

        /** ****************************************************************************************
         * Writes a variable to the configuration.
         * This default implementation just returns \c false. If this method is not overwritten
         * in descendants, those descendants are not designed to write data.
         *
         * @param variable  The variable to store.
         * @return \c true if the variable was written, \c false if not which typically indicates
         *         that this plug-in is not able to write values.
         ******************************************************************************************/
        public virtual bool Store( Variable variable )
        {
            return false;
        }

        /** ****************************************************************************************
         * Convenience method that parses the values from the given string using field
         * #StringConverter and then invokes \ref Store(Variable) "Store".
         *
         * @param variable          The variable to store.
         * @param externalizedValue The value to parse into the variable before storing
         *
         * @return \c true if the variable was written, \c false if not which typically indicates
         *         that this plug-in is not able to write values.
         ******************************************************************************************/
        public virtual bool  Store( Variable variable, Object externalizedValue )
        {
            if(     externalizedValue != null
                && ( !(externalizedValue is AString) || ((AString) externalizedValue).IsNotNull() ) )
            {
                StringConverter.LoadFromString( variable, externalizedValue );
            }
            return Store( variable );
        }
}

/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugin, which takes all command line
 * parameters in the constructor and reads variable values from those parameters on request.
 * Its priority value usually is \alib{config,Configuration.PrioCLIArgs}, which is higher
 * than all other default plug-ins provided.
 *
 * Variable categories are used as a prefix together with an underscore \c '_'.
 * This means, if variable <em>LOCALE</em> in category <em>ALIB</em> is accessed, the command line
 * parameter <em>--ALIB_LOCALE=xyz</em> is read.
 *
 * Category and Variable names are insensitive in respect to character case.
 *
 * Command line variables may be passed with either one hyphen ('-') or two ('--').
 * Both are accepted.
 *
 * An application can specify one or more "default categories" by adding their string names to
 * public field #DefaultCategories. Variables of these categories are recognized by the plug-in
 * also when given without the prefix of category name and underscore \c '_'.
 *
 * Furthermore, an application may set public field #AllowedMinimumShortCut to a value greater than
 * \c 0. In this case, the plug-in recognizes variables in CLI arguments already when at least
 * this amount of characters is provided. In other words, when reading an argument as many
 * characters of the variable name as possible are 'consumed' and if a minimum number is given with
 * #AllowedMinimumShortCut, such minimum is sufficient. If the remaining part of the argument
 * string is either empty or continues with an equal sign \c '=', then the variable is recognized
 * (with an empty value or the value after the equal sign).<br>
 * Fields #AllowedMinimumShortCut and #DefaultCategories may also be used in combination.
 **************************************************************************************************/
public class CLIArgs : ConfigurationPlugin
{

    /** The list of command line arguments. */
    protected  String[]             args;


    /**
     * An application can specify one or more "default categories" by adding the category names
     * here. Variables of these categories are recognized by the plug-in
     * also when given without the prefix of <c>category_</c>.
     */
    public     List<String>         DefaultCategories                          = new List<String>();

    /**
     * If this field is set to a value greater than \c 0, this plug-in recognizes variables in
     * CLI arguments already when at least this amount of characters is provided.
     * If the remaining part of the argument string is either empty or continues with an equal
     * sign \c '=', then the variable is recognized.
     */
    public     int                  AllowedMinimumShortCut                                      = 0;

    /** ********************************************************************************************
     * Sets the command line argument list. Needs to be called once after construction.
     * Should not be invoked directly. Rather use
     * \ref cs.aworx.lib.config.Configuration.SetCommandLineArgs "Configuration.SetCommandLineArgs".
     *
     *\note In standard application scenarios, this method is invoked by method
     *      \ref cs.aworx.lib.ALIB.Init   "ALIB.Init" for the singleton of this class found in
     *      \ref cs.aworx.lib.ALIB.Config "ALIB.Config".
     *
     * @param args    Parameters taken from <em>standard C#</em> method \c main()
     *                (the list of command line arguments).
     *                Defaults to null.
     **********************************************************************************************/
    public void SetArgs( String[] args )   { this.args= args; }

    /** ********************************************************************************************
     * Searches the variable in the command line parameters.
     *
     * @param variable     The variable to retrieve.
     * @param searchOnly   If \c true, the variable is not read. Defaults to \c false.
     * @return \c true if variable was found, \c false if not.
     **********************************************************************************************/
    public override
    bool  Load( Variable variable, bool searchOnly= false )
    {
        if ( args == null )
            return false;

        // check if category may me left out
        bool allowWithoutCategory= false;
        foreach (var defaultCategory in DefaultCategories )
            if( (allowWithoutCategory= variable.Category.Equals( defaultCategory )) )
                break;
        String    variableFullname= variable.Fullname.ToString();
        String    variableName=     variable.Name.ToString();
        Substring cliArg=           new Substring();

        for ( int i= 0; i < args.Length ; i++ )
        {
            // remove whitespaces (if somebody would work with quotation marks...)
            // and request '-' and allow a second '-'
            if ( !cliArg.Set( args[i] ).Trim().ConsumeChar('-') )
                continue;
            cliArg.ConsumeChar( '-' );


            // try names
            if (    !                          cliArg.ConsumeString( variableFullname, Case.Ignore )
                 && !( allowWithoutCategory && cliArg.ConsumeString( variableName    , Case.Ignore )  )
                 && !(    AllowedMinimumShortCut > 0
                       && (                            0 < cliArg.ConsumePartOf( variableFullname, AllowedMinimumShortCut + 1 + variable.Category.Length() )
                           ||( allowWithoutCategory && 0 < cliArg.ConsumePartOf( variableName    , AllowedMinimumShortCut ) )
                          )
                     )
               )
                continue; // next arg

            // found --CAT_NAME. If rest is empty or continues with '=', we set
            if ( cliArg.IsEmpty() )
            {
                if ( !searchOnly )
                    variable.Add();
                return true;
            }

            if ( cliArg.ConsumeChar( '=', Case.Sensitive, Whitespaces.Trim ) )
            {
                if ( !searchOnly )
                    StringConverter.LoadFromString( variable, cliArg );
                return true;
            }
        }

        return false;
    }

}

/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugin, retrieves configuration
 * data from the system environment.
 * Its priority value usually is \alib{config,Configuration.PrioEnvironment}, which is higher
 * than \alib{config,Configuration.PrioStandard} but lower than
 * \alib{config,Configuration.PrioCLIArgs}.
 *
 * Variable categories are used as a prefix together with an underscore '_'.
 * This means, if variable <em>LOCALE</em> in category <em>ALIB</em> is accessed, the
 * environment variable <em>ALIB_LOCALE</em> is read.
 *
 * Category and Variable names are insensitive in respect to character case.
 **************************************************************************************************/
public class Environment : ConfigurationPlugin
{
    protected  AString    tmpAS= new AString();    ///< A temporary string to reuse.

    /** ********************************************************************************************
     * Constructor.
     **********************************************************************************************/
    public Environment() {}

    /** ********************************************************************************************
     * Searches the variable in the environment.
     *
     * @param variable      The variable to retrieve.
     * @param searchOnly    If \c true, the variable is not set. Defaults to \c false.
     * @return \c true if variable was found, \c false if not.
     **********************************************************************************************/
    public override
    bool  Load( Variable variable, bool searchOnly= false )
    {
        tmpAS._()._( variable.Fullname ).ToUpper();

        String env= System.Environment.GetEnvironmentVariable( tmpAS.ToString() );
        if ( env == null )
            return false;
        if ( !searchOnly )
            StringConverter.LoadFromString( variable, env );
        return true;
    }
};

} // namespace / EOF
