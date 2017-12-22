// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import java.util.ArrayList;

import com.aworx.lib.ALIB;
import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Whitespaces;
import com.aworx.lib.strings.*;

/** ************************************************************************************************
 * This class is used to load and store external configuration data with objects of class
 * \ref com.aworx.lib.config.Configuration       "Configuration" and its plug-ins
 * \ref com.aworx.lib.config.ConfigurationPlugin "ConfigurationPlugin".
 *
 * \note
 *   For general information about external configuration variables, see namespace documentation
 *   \ref com.aworx.lib.config "com.aworx.lib.config".
 *
 * <b>Construction/Redeclaration:</b><br>
 * While constructors accepting attributes of a variable exist, it is recommended to
 * declare all external configuration variables in a central place, using statically or dynamically
 * allocated objects of type
 * \ref com.aworx.lib.config.VariableDecl "VariableDecl" and pass such record
 * to the constructor of a variable.
 *
 * The class is designed to be 'reused' to avoid repeated allocation/de-allocation of memory.
 * After invoking one of the overloaded methods #declare, which share the same signatures as
 * the overloaded constructors, a variable is freshly initialized. Internally, the memory
 * allocated for values remains allocated.
 *
 * <b>Values:</b><br>
 * A variable can contain zero, one or several values. If zero, then the variable was either not
 * loaded, yet or the load operation failed (no configuration plug-in defined the variable).
 * Method #size reports the currently available values and methods #getString(int), #getInteger(int)
 * and #getFloat(int) return a value. Internally all values are stored as strings. If
 * field #config is set, its field
 * \ref com.aworx.lib.config.Configuration.numberFormat "Configuration.numberFormat"
 * is used for floating point conversion.
 *
 * When storing a variable that contains more than one value, field #delim has to be set.
 * Conversely, when reading a variable that contains multiple values, the delimiter has to be set
 * prior to the load operation.
 * \note
 *   This is not true when loading/storing a variable directly in a plug-in of type
 *   \ref com.aworx.lib.config.InMemoryPlugin "InMemoryPlugin"   or might also not be true
 *   with custom configuration plug-in types which
 *   for example might store the values in a database.<br>
 *   However, with the default plug-ins
 *   \ref com.aworx.lib.config.CLIArgs "CLIArgs",
 *   \ref com.aworx.lib.config.Environment  "Environment" and
 *   \ref com.aworx.lib.config.IniFile "IniFile"
 *   the delimiter is needed! Therefore, it is best practice to always define a proper delimiter if
 *   a variable is multi-valued.
 *
 * <b>Loading and Storing:</b><br>
 * There are two ways of loading and storing a variable:
 * - Using the interface of class \ref com.aworx.lib.config.Configuration "Configuration"
 *   which allows to load and store variables from different sources (plug-ins) in a prioritized
 *   way.
 * - Using the interface of class \ref com.aworx.lib.config.ConfigurationPlugin "ConfigurationPlugin"
 *   which may be used if the decision about the source or drain of a load/store operation is explicitly
 *   made by a code unit.
 *
 * Storing empty variables (method #size returns \c 0) deletes a variable from the those
 * configuration plug-ins that are write enabled.
 **************************************************************************************************/
public class Variable
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

        /** No hints */
        public final static int FORMAT_HINT_NONE            = 0;

        /** Write each argument in a new line */
        public final static int FORMAT_HINT_MULTILINE       = 1 <<   0;

        /** Suppress spaces around the delimiter (only used in single line mode) */
        public final static int FORMAT_HINT_NO_DELIM_SPACES = 1 <<   1;

        /** This and upward bits are reserved for custom plug-ins */
        public final static int FORMAT_HINT_CUSTOM          = 1 <<  16;


        /** The \b %Configuration that was recently used to request or store the value.  */
        public Configuration    config                  = null;

        /** The configuration variable category.  */
        public AString          category                = new AString();

        /** The configuration variable name.  */
        public AString          name                    = new AString();

        /**
         *  The delimiter used for parsing and storing values by simple textual plug-ins which
         *  use the default version of
         *  \ref com.aworx.lib.config.XTernalizer "XTernalizer"
         *  for in- and externalizing variables.
         */
        public char             delim                   = '\0';

        /** Hints for formatting textual configuration files. (Used by class
            \ref com.aworx.lib.config.IniFile "IniFile" and potentially by custom plug-ins.*/
        public int              formatHints;

        /** If set, attributes written in multi-lines are vertically aligned by this character or
         *  string. Use cases are "=", ":" or "->".<br> Used by
         *  \ref com.aworx.lib.config.IniFile "IniFile" and potentially by custom plug-ins. */
        public String           formatAttrAlignment;

        /** The configuration variable comments with placeholders replaced */
        public AString          comments                = new AString();

        /** The configuration variable category and name concatenated with an underscore
         *  character \c '_'. This is useful e.g. for naming variables in log messages. */
        public AString          fullname                = new AString();

        /**
         * The default value provided as an externalized string.
         *
         * The only occasion that this value is used is with method
         * \ref com.aworx.lib.config.Configuration.load   "Configuration.load".
         * If no plug-in has this variable defined and this field is not \e nulled, then the value
         * is written into plug-in of priority \alib{config,Configuration.PRIO_DEFAULT_VALUES},
         * respectively - if this default plug-in was replaced by the user - into a plug-in found at
         * or below this priority.
         *
         * In this case, the value is parsed using method
         * \ref com.aworx.lib.config.XTernalizer.loadFromString  "XTernalizer.loadFromString"
         * of field
         * \ref com.aworx.lib.config.ConfigurationPlugin.stringConverter  "ConfigurationPlugin.stringConverter"
         * of the plug-in writing the value.
         *
         * \note
         *   The field is ignored when using the plug-in interface
         *   \ref com.aworx.lib.config.ConfigurationPlugin.load "ConfigurationPlugin.load"
         *   directly. To store this value 'manually' directly to a plug-in, invoke
         *   \ref com.aworx.lib.config.ConfigurationPlugin.store "ConfigurationPlugin.store"
         *   with providing value explicitly.
         */
        public AString          defaultValue            = new AString();

        /**
         * A value related to the priority of a configuration plug-in.
         * The following values apply:
         * - \c 0 after creation or declaration (reuse).
         * - The priority of the plug-in that loaded the value (after calling
         *   \ref com.aworx.lib.config.Configuration.load   "Configuration.load").
         * - The priority of the plug-in that stored the value (after calling
         *   \ref com.aworx.lib.config.Configuration.store "Configuration.store").
         * - \c 0, if the last load or store operation failed.
         * In addition prior to storing a variable, the value might be manually set. See
         * documentation of
         * \ref com.aworx.lib.config.Configuration.store "Configuration.store") for details.
         */
        public int              priority                = 0;

    // #############################################################################################
    // Protected fields
    // #############################################################################################

        /** The values   */
        protected ArrayList<AString> values             = new ArrayList<AString>();

        /** The number of values currently stored. This may be less than items found in #values
            as those are reused objects. */
        protected int           qtyValues               = 0;


    // #############################################################################################
    // Constructors
    // #############################################################################################
        /** ****************************************************************************************
         * Constructs an undefined Variable. Prior to using this, #declare has to be invoked.
         ******************************************************************************************/
        public Variable()
        {
             clear();
        }

        /** ****************************************************************************************
         * Constructs a variable from a declaration.
         * Strings named \c "%1", \c "%2" ... \c "%N" found in the fields #category, #name,
         * #comments and #defaultValue are replaced with given replacement strings found
         * in array \p replacements.
         *
         * @param declaration    The declaration data of the variable.
         * @param replacements   List of objects that will be converted to strings using
         *                       \ref com.aworx.lib.strings.AString._(Object) "AString._(Object)".
         ******************************************************************************************/
        public Variable( VariableDecl declaration, Object... replacements )
        {
            declare( declaration, replacements );
        }

        /** ****************************************************************************************
         * Constructs a variable using the declaration of another variable. The values are not
         * copied.
         *
         * @param variable  A variable to copy the declaration (which is comprised with fields
         *                  #category, #name, #fullname, #delim, #comments and #defaultValue) from.
         ******************************************************************************************/
        public Variable( Variable variable )
        {
            declare( variable );
        }

        /** ****************************************************************************************
         * Constructs a variable from the given values
         *
         * @param category  The category of the variable.
         * @param name      The name of the variable
         * @param comments  Comment lines that might be added in the configuration storage
         *                  (plug-in implementation dependent).
         * @param delim     A proposal for a delimiter that might be used by some plug-ins
         *                  to delimit different values from each other (e.g. INI files).
         ******************************************************************************************/
        public Variable( CharSequence category,  CharSequence name, char delim,
                         CharSequence comments    )
        {
            declare( category, name, delim, comments );
        }

        /** ****************************************************************************************
         * Overloaded constructor providing default parameters.
         *
         * @param category  The category of the variable.
         * @param name      The name of the variable
         * @param delim     A proposal for a delimiter that might be used by some plug-ins
         *                  to delimit different values from each other (e.g. INI files).
         ******************************************************************************************/
        public Variable( CharSequence category,  CharSequence name, char delim )
        {
            declare( category, name, delim, null );
        }


        /** ****************************************************************************************
         * Overloaded constructor providing default parameters.
         *
         * @param category  The category of the variable.
         * @param name      The name of the variable
         ******************************************************************************************/
        public Variable( CharSequence category,  CharSequence name )
        {
            declare( category, name, '\0', null );
        }

    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         * \ref clear "Clears" the variable resets its declaration.
         * Strings named \c "%1", \c "%2" ... \c "%N" found in the fields #category, #name,
         * #comments and #defaultValue are replaced with given replacement string arguments
         * in array \p replacements.
         *
         * @param declaration    The declaration data of the variable.
         * @param replacements   List of objects that will be converted to strings using
         *                       \ref com.aworx.lib.strings.AString._(Object) "AString._(Object)".
         * @return \c this to allow concatenated operations.
         ******************************************************************************************/
        public Variable   declare( VariableDecl declaration, Object... replacements )
        {
            clear();

            delim=                  declaration.delim;
            formatHints=            declaration.formatHints;
            formatAttrAlignment=    declaration.formatAttrAlignment;

            // set Category, Name, Comment
            if(  declaration.category != null ) category._( declaration.category );
            else                               category._( declaration.categoryFallback );

            name    ._( declaration.name    );
            comments._( declaration.comments );
            if ( declaration.defaultValue != null )
                defaultValue._()._( declaration.defaultValue );
            else
                defaultValue.setNull();

            // replace strings
            if ( replacements != null && replacements.length > 0 )
            {
                AString search= fullname;                        // just an alias name
                AString repl=   new AString(); values.add(repl); // reuse this string later
                for( int i= 0; i < replacements.length; i++ )
                {
                    search._()._("%")._(i + 1);
                    repl  ._()._( replacements[i] );

                    category    .searchAndReplace( search, repl );
                    name        .searchAndReplace( search, repl );
                    comments    .searchAndReplace( search, repl );
                    defaultValue.searchAndReplace( search, repl );
                }
                search._();
           }

            // set full name
            if( category.isNotEmpty() )
                fullname._( category )._( '_' );
            fullname._( name );

            com.aworx.lib.ALIB_DBG.ASSERT_WARNING(  name.isNotEmpty(), "Empty variable name given" );

            return this;
        }

        /** ****************************************************************************************
         * \ref clear "Clears" the variable resets its declaration.
         *
         * @param category  The category of the variable.
         * @param name      The name of the variable
         * @param delim     A proposal for a delimiter that might be used by some plug-ins
         *                  to delimit different values from each other (e.g. INI files).
         *                  Defaults to \c '\0'.
         * @param comments  Comment lines that might be added in the configuration storage
         *                  (plug-in implementation dependent).
         *                  Defaults to \c null.
         *
         * @return \c this to allow concatenated operations.
         ******************************************************************************************/
        @SuppressWarnings ("hiding")
        public Variable   declare( CharSequence category, CharSequence name, char delim,
                                   CharSequence comments )
        {
            clear();

            this.category._(category);
            this.name    ._(name);
            this.comments._(comments);
            this.delim=     delim;

            if( this.category.isNotEmpty() )
                fullname._( category )._( '_' );
            fullname._( name );
            return this;
        }

        /** ****************************************************************************************
         * Constructs a variable using the declaration of another variable. The values are not
         * copied.
         *
         * @param variable  A variable to copy the declaration (which is comprised with fields
         *                  #category, #name, #fullname, #delim, #comments and #defaultValue) from.
         * @return \c this to allow concatenated operations.
         ******************************************************************************************/
        public Variable declare ( Variable variable )
        {
            clear();

            category._(variable.category);
            name    ._(variable.name);
            fullname._(variable.fullname);
            comments._(variable.comments);
            delim=     variable.delim;
            return this;
        }


        /** ****************************************************************************************
         * Overloaded version providing default parameters.
         *
         * @param category  The category of the variable.
         * @param name      The name of the variable
         * @param delim     A proposal for a delimiter that might be used by some plug-ins
         *                  to delimit different values from each other (e.g. INI files).
         *                  Defaults to \c '\0'.
         *
         * @return \c this to allow concatenated operations.
         ******************************************************************************************/
        public
        @SuppressWarnings ("hiding")
        Variable   declare( CharSequence category, CharSequence name, char delim )
        {
            return declare( category, name, delim, null );
        }

        /** ****************************************************************************************
         * Overloaded version providing default parameters.
         *
         * @param category  The category of the variable.
         * @param name      The name of the variable
         *
         * @return \c this to allow concatenated operations.
         ******************************************************************************************/
        public
        @SuppressWarnings ("hiding")
        Variable   declare( CharSequence category,  CharSequence name )
        {
            return declare( category, name, '\0', null );
        }


        /** ****************************************************************************************
         * Returns the number of values set in this object.
         *
         * @return The number of values set.
         ******************************************************************************************/
        public int         size()
        {
            return qtyValues;
        }

        /** ****************************************************************************************
         * Clears the value, respectively the list of values set.
         * After invoking this method, #size will return \p startIdx and #getString will
         * return \c null for any index greater or equal to \p startIdx.
         *
         * @param  startIdx  The index of the first value to be cleared. Defaults to \c 0.
         * @return \c this to allow concatenated operations.
         ******************************************************************************************/
        public Variable  clearValues(int startIdx)
        {
            qtyValues= startIdx;
            return this;
        }

        /** ****************************************************************************************
         * Clears the value, respectively the list of values set.
         * After invoking this method, #size will return \c 0 and #getString will return \c null
         * for any index.
         *
         * @return \c this to allow concatenated operations.
         ******************************************************************************************/
        public Variable  clearValues()
        {
            qtyValues= 0;
            return this;
        }

        /** ****************************************************************************************
         * Adds an empty value to the end of the list of values.
         * @return A reference to the string which can be manipulated to set the value.
         ******************************************************************************************/
        public AString add()
        {
            int actIdx= qtyValues;
            qtyValues++;
            if( actIdx < values.size() )
                return values.get(actIdx).clear();

            AString newVal= new AString();
            values.add( newVal );
            return newVal;
        }

        /** ****************************************************************************************
         * Adds the given string value to the end of the list of values.
         * @param  value  The value to set.
         * @return A reference to the string which can be further manipulated to set the value.
         ******************************************************************************************/
        public AString add(Object value )
        {
            return add()._( value );
        }


        /** ****************************************************************************************
         * Adds the given boolean value to the end of the list of values.
         * For \c true values string \b "true" is set, otherwise \b "false".
         * \note
         *  Other, depending on the variable semantics, more user friendly values may be set using
         *  the string interface #add.
         *  String values recognized for boolean variables are defined in
         * \ref com.aworx.lib.config.Configuration.trueValues   "Configuration.trueValues".
         *
         * @param  value  The value to set.
         * @return A reference to the string representing the boolean value.
         ******************************************************************************************/
        public AString    add( boolean value )
        {
            return add()._( value ? "true" : "false" );
        }

        /** ****************************************************************************************
         * Replaces the value at \p idx with the values of the given other variable.
         *
         * @param  idx          The index of the value to replace.
         * @param  replVariable The variable providing the replacement values.
         ******************************************************************************************/
        public void ReplaceValue( int idx, Variable replVariable )
        {
            if( idx < 0 || idx >= qtyValues )
            {
                com.aworx.lib.ALIB_DBG.WARNING( "Index out of range: " + idx + " ( 0 - " + qtyValues + " allowed)." );
                return;
            }

            int replSize= replVariable.size();
            if( replSize == 0 )
            {
                values.remove( idx );
                return;
            }

            values.get( idx )._()._( replVariable.getString(0) );
            for( int i= 1 ; i < replSize; i++ )
            {
                values.add( idx + i, new AString( replVariable.getString(i) ) );
                qtyValues++;
            }
        }


        /** ****************************************************************************************
         * Returns the value with the given index. Valid values for parameter \p idx are
         * between \c 0 and #size <c>- 1</c>.
         * If no value is set for the given index, \c null is returned.
         *
         * \note
         *  It is explicitly allowed to change the contents of the \b %AString object returned,
         *  e.g. for a subsequent store operation.
         *
         *
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p idx.
         ******************************************************************************************/
        public AString    getString( int idx )
        {
            return idx < qtyValues  ? values.get( idx )
                                    : null;
        }

        /** ****************************************************************************************
         * Returns the first (in most cases the only) value.
         * If no value is set \c null is returned.
         *
         * \note
         *  It is explicitly allowed to change the contents of the \b %AString object returned,
         *  e.g. for a subsequent store operation.
         *
         * @return The value at \p idx.
         ******************************************************************************************/
        public AString    getString()
        {
            return qtyValues != 0   ? values.get( 0 )
                                    : null;
        }

        /** ****************************************************************************************
         * Returns the value at \p idx interpreted as an integer.
         * If the index is invalid, \c 0 is returned.
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p idx interpreted as an integer value.
         ******************************************************************************************/
        public long            getInteger( int idx )
        {
            return idx < qtyValues  ? getString( idx ).parseInt()
                                    : 0;
        }

        /** ****************************************************************************************
         * Returns the first (in most cases the only) value interpreted as an integer.
         * If no value is set \c 0 is returned.
         * @return The value at \p idx interpreted as an integer value.
         ******************************************************************************************/
        public long            getInteger()
        {
            return qtyValues != 0   ? getString( 0 ).parseInt()
                                    : 0L;
        }

        /** ****************************************************************************************
         * Returns the value at \p idx interpreted as a double value.
         * If the index is invalid, \c 0.0 is returned.
         * Parsing is done using field \c numberFormat of field #config, respectively, if this is
         * not set, the static singleton \alib{strings,NumberFormat.global}.
         *
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p idx interpreted as a double value.
         ******************************************************************************************/
        public double          getFloat(int idx)
        {
            return idx < qtyValues  ?   getString( idx ).parseFloat( (config != null ? config : ALIB.config).numberFormat )
                                    :   0.0;
        }

        /** ****************************************************************************************
         * Returns the value at  index \c 0 interpreted as a double value.
         * If no value is defined, \c 0.0 is returned.
         * Parsing is done using field \c numberFormat of field #config, respectively, if this is
         * not set, the static singleton \alib{strings,NumberFormat.global}.
         *
         *
         * @return The value at \p idx interpreted as a double value.
         ******************************************************************************************/
        public double          getDouble()
        {
            return qtyValues != 0   ?   getString( 0 ).parseFloat( (config != null ? config : ALIB.config).numberFormat )
                                    :   0.0;
        }

        /** ****************************************************************************************
         * Returns \c true if the value at the given \p idx represents a boolean 'true'.
         * Evaluation is done using field #config, respectively if this is not set, the static
         * singleton \ref com.aworx.lib.ALIB.config "ALIB.config".
         *
         * If the index is invalid, \c false is returned.
         *
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p idx interpreted as a boolean value.
         ******************************************************************************************/
        public boolean         isTrue(int idx)
        {
            return idx < qtyValues  ? (config != null ? config : ALIB.config ).isTrue( getString( idx ) )
                                    : false;
        }

        /** ****************************************************************************************
         * Returns \c true if the first value represents a boolean 'true'.
         * Evaluation is done using field #config, respectively if this is not set, the static
         * singleton \ref com.aworx.lib.ALIB.config "ALIB.config".
         *
         * If no value is set \c false is returned.
         *
         * @return The value at \p idx interpreted as a boolean value.
         ******************************************************************************************/
        public boolean         isTrue()
        {
            return qtyValues != 0   ? (config != null ? config : ALIB.config ).isTrue( getString( 0 ) )
                                    : false;
        }

        /** ****************************************************************************************
         * Searches in the values of this variable for the pattern
         * <c>attrName = result</c> and
         * sets parameter \p result to the string following this pattern.
         *
         * @param      attrName     The name of the attribute searched.
         * @param[out] result       A substring with the result.
         * @param      attrDelim    The delimiter to search for. Defaults to '='.
         * @return \c true if the attribute was found, \c false otherwise.
         ******************************************************************************************/
        boolean    getAttribute( String attrName, Substring result, char attrDelim )
        {
            for ( int i= 0; i< size(); i++ )
            {
                result.set( getString(i ) );
                if (    result.consumeString( attrName,  Case.IGNORE, Whitespaces.TRIM )
                     && result.consumeChar  ( attrDelim, Case.IGNORE, Whitespaces.TRIM ) )
                {
                    result.trim();
                    return true;
                }
            }
            return false;
        }

        /** ****************************************************************************************
         * Overloaded version providing default value \c '=' for parameter \p attrDelim.
         *
         * @param      attrName     The name of the attribute searched.
         * @param[out] result       A substring with the result.
         * @return \c true if the attribute was found, \c false otherwise.
         ******************************************************************************************/
        public boolean    getAttribute( String attrName, Substring result )
        {
            return getAttribute( attrName, result, '=');
        }

    // #############################################################################################
    // protected methods
    // #############################################################################################


        /** ****************************************************************************************
         * Clears all values.
         ******************************************************************************************/
        protected void        clear()
        {
            config=         null;
            priority=       0;
            delim=          '\0';
            formatHints=    0;

            category._();
            name    ._();
            comments._();
            fullname._();
            clearValues();
        }
}



