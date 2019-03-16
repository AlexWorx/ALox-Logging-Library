
// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2019 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;


namespace cs.aworx.lib.config  {


/** ************************************************************************************************
 * A data record used to declare an
 * \ref cs.aworx.lib.config.Variable "ALib Configuration Variable".
 * While variables can also be declared by setting their attributes individually, it is recommended to
 * declare all external configuration variables in a central place, using statically or dynamically
 * allocated objects of this type.<br>
 * Objects of class \b %Variable can be constructed and existing objects can be reused by invoking
 * \ref cs.aworx.lib.config.Variable.Declare "Variable.Declare". Both, construction and
 * re-declaration of variables, use objects of this type.
 *
 * All fields (except #Delim) support placeholders \c "%1", \c "%2" ... \c "%N", which are
 * replaced with the constructor of class \b %Variable and method
 * \ref cs.aworx.lib.config.Variable.Declare "Variable.Declare".
 * This allows to define a series of variables whose category, name, description and value is
 * dependent on runtime information.
 *
 * Besides the use for passing parameters into objects of type Variable, this struct does not
 * provide further logic.
 **************************************************************************************************/
public struct VariableDecl
{
    /**
     * Simple constructor copying values
     * @param categoryFallback     Value for field #CategoryFallback (treated as reference, value not copied)
     * @param category             Value for field #Category
     * @param name                 Value for field #Name
     * @param defaultValue         Value for field #DefaultValue
     * @param delim                Value for field #Delim
     * @param formatAttrAlignment  Value for field #FormatAttrAlignment
     * @param formatHints          Value for field #FormatHints
     * @param comments             Value for field #Comments
     */
    public VariableDecl( AString categoryFallback, String category, String name, String defaultValue,
                               char delim, String formatAttrAlignment, Variable.FormatHint formatHints,  String comments )
    {
        this.CategoryFallback=     categoryFallback;
        this.Category=             category;
        this.Name=                 name;
        this.DefaultValue=         defaultValue;
        this.Delim=                delim;
        this.FormatAttrAlignment=  formatAttrAlignment;
        this.FormatHints=          formatHints;
        this.Comments=             comments;
    }


    /**
     * Reference to a category string which is used as fallback if field #Category is nulled.
     * This is useful as usually most variables share one general application specific
     * category. With the combination of fields #CategoryFallback and #Category,
     * the user (of a library) is be entitled to change single variables
     * or all at once. In the latter case, field #Category is left nulled, while this field
     * is set to a global default value (which also can be changed, therefore a pointer).
     */
    public AString     CategoryFallback;

    /** The category for this value. May be left nulled in which case field
     *  #CategoryFallback is applied. */
    public String      Category;

    /** The name of the variable. */
    public String      Name;

    /**
     * The default value. If this is \c null, no variable will be created with method
     * \ref cs.aworx.lib.config.Configuration.Load "Configuration.Load".
     * \note
     *   The field is ignored when using the plug-in interface
     *   \ref cs.aworx.lib.config.ConfigurationPlugin.Load "ConfigurationPlugin.Load".
     */
    public String      DefaultValue;

    /** The (preferred) delimiter of values when represented in external strings.  */
    public char        Delim;

    /** If set, attributes written in multi-lines are vertically aligned by this character or
     *  string. Use cases are "=", ":" or "->".<br> Used by
     *  \ref cs.aworx.lib.config.IniFile "IniFile" and potentially by custom plug-ins. */
    public String      FormatAttrAlignment;

    /** Hints for formatting textual configuration files. (Used by class
        \ref cs.aworx.lib.config.IniFile "IniFile" and potentially by custom plug-ins.*/
    public Variable.FormatHint  FormatHints;

    /** Comments for the variable. Some plug-ins allow to store comments along with the
     *  variable (e.g. class \ref cs.aworx.lib.config.IniFile).*/
    public String      Comments;
}

/** ************************************************************************************************
 * This class is used to load and store external configuration data with objects of class
 * \ref cs.aworx.lib.config.Configuration       "Configuration" and its plug-ins
 * \ref cs.aworx.lib.config.ConfigurationPlugin "ConfigurationPlugin".
 *
 * \note
 *   For general information about external configuration variables, see namespace documentation
 *   \ref cs.aworx.lib.config "com.aworx.lib.config".
 *
 * <b>Construction/Redeclaration:</b><br>
 * While constructors accepting attributes of a variable exist, it is recommended to
 * declare all external configuration variables in a central place, using statically or dynamically
 * allocated objects of type
 * \ref cs.aworx.lib.config.VariableDecl "VariableDecl" and pass such record
 * to the constructor of a variable.
 *
 * The class is designed to be 'reused' to avoid repeated allocation/de-allocation of memory.
 * After invoking one of the overloaded methods #Declare, which share the same signatures as
 * the overloaded constructors, a variable is freshly initialized. Internally, the memory
 * allocated for values remains allocated.
 *
 * <b>Values:</b><br>
 * A variable can contain zero, one or several values. If zero, then the variable was either not
 * loaded, yet or the load operation failed (no configuration plug-in defined the variable).
 * Method #Size reports the currently available values and methods #GetString(int), #GetInteger(int)
 * and #GetFloat(int) return a value. Internally all values are stored as strings. If
 * field #Config is set, its field
 * \ref cs.aworx.lib.config.Configuration.NumberFormat "Configuration.NumberFormat"
 * is used for floating point conversion.
 *
 * When storing a variable that contains more than one value, field #Delim has to be set.
 * Conversely, when reading a variable that contains multiple values, the delimiter has to be set
 * prior to the load operation.
 * \note
 *   This is not true when loading/storing a variable directly in a plug-in of type
 *   \ref cs.aworx.lib.config.InMemoryPlugin "InMemoryPlugin"   or might also not be true
 *   with custom configuration plug-in types which
 *   for example might store the values in a database.<br>
 *   However, with the default plug-ins
 *   \ref cs.aworx.lib.config.CLIArgs "CLIArgs",
 *   \ref cs.aworx.lib.config.Environment  "Environment" and
 *   \ref cs.aworx.lib.config.IniFile "IniFile"
 *   the delimiter is needed! Therefore, it is best practice to always define a proper delimiter if
 *   a variable is multi-valued.
 *
 * <b>Loading and Storing:</b><br>
 * There are two ways of loading and storing a variable:
 * - Using the interface of class \ref cs.aworx.lib.config.Configuration "Configuration"
 *   which allows to load and store variables from different sources (plug-ins) in a prioritized
 *   way.
 * - Using the interface of class \ref cs.aworx.lib.config.ConfigurationPlugin "ConfigurationPlugin"
 *   which may be used if the decision about the source or drain of a load/store operation is explicitly
 *   made by a code unit.
 *
 * Storing empty variables (method #Size returns \c 0) deletes a variable from the those
 * configuration plug-ins that are write enabled.
 **************************************************************************************************/
public class Variable
{
    // #############################################################################################
    // Public fields
    // #############################################################################################

        /** Denotes hints for formatting variables when storing in external configuration files  */
        public enum FormatHint
        {
            /** No hints */
            None                    = 0      ,

            /** Write each argument in a new line */
            MultLine                = 1 <<  0,

            /** Suppress spaces around the delimiter (only used in single line mode) */
            NoDelimSpaces           = 1 <<  1,

            /** This and upward bits are reserved for custom plug-ins */
            Custom                  = 1 <<  16,
        };

        /** The \b %Configuration that was recently used to request or store the value.  */
        public Configuration    Config;

        /** The configuration variable category.  */
        public AString          Category                = new AString();

        /** The configuration variable name.  */
        public AString          Name                    = new AString();

        /**
         *  The delimiter used for parsing and storing values by simple textual plug-ins which
         *  use the default version of
         *  \ref cs.aworx.lib.config.XTernalizer "XTernalizer"
         *  for in- and externalizing variables.
         */
        public char             Delim                   = '\0';

        /** Hints for formatting textual configuration files. (Used by class
            \ref cs.aworx.lib.config.IniFile "IniFile" and potentially by custom plug-ins.*/
        public FormatHint       FormatHints;

        /** If set, attributes written in multi-lines are vertically aligned by this character or
         *  string. Use cases are "=", ":" or "->".<br> Used by
         *  \ref cs.aworx.lib.config.IniFile "IniFile" and potentially by custom plug-ins. */
        public String           FormatAttrAlignment;

        /** The configuration variable comments with placeholders replaced */
        public AString          Comments                = new AString();

        /** The configuration variable category and name concatenated with an underscore
         *  character \c '_'. This is useful e.g. for naming variables in log messages. */
        public AString          Fullname                = new AString();

        /**
         * The default value provided as an externalized string.
         *
         * The only occasion that this value is used is with method
         * \ref cs.aworx.lib.config.Configuration.Load   "Configuration.Load".
         * If no plug-in has this variable defined and this field is not \e nulled, then the value
         * is written into plug-in of priority \alib{config,Configuration.PrioDefaultValues},
         * respectively - if this default plug-in was replaced by the user - into a plug-in found at
         * or below this priority.
         *
         * In this case, the value is parsed using method
         * \ref cs.aworx.lib.config.XTernalizer.LoadFromString  "XTernalizer.LoadFromString"
         * of field
         * \ref cs.aworx.lib.config.ConfigurationPlugin.StringConverter  "ConfigurationPlugin.StringConverter"
         * of the plug-in writing the value.
         *
         * \note
         *   The field is ignored when using the plug-in interface
         *   \ref cs.aworx.lib.config.ConfigurationPlugin.Load "ConfigurationPlugin.Load"
         *   directly. To store this value 'manually' directly to a plug-in, invoke
         *   \ref cs.aworx.lib.config.ConfigurationPlugin.Store "ConfigurationPlugin.Store"
         *   with providing value explicitly.
         */
        public AString         DefaultValue             = new AString();

        /**
         * A value related to the priority of a configuration plug-in.
         * The following values apply:
         * - \c 0 after creation or declaration (reuse).
         * - The priority of the plug-in that loaded the value (after calling
         *   \ref cs.aworx.lib.config.Configuration.Load   "Configuration.Load").
         * - The priority of the plug-in that stored the value (after calling
         *   \ref cs.aworx.lib.config.Configuration.Store "Configuration.Store").
         * - \c 0, if the last load or store operation failed.
         * In addition prior to storing a variable, the value might be manually set. See
         * documentation of
         * \ref cs.aworx.lib.config.Configuration.Store "Configuration.Store") for details.
         */
        public int              Priority                = 0;

    // #############################################################################################
    // Protected fields
    // #############################################################################################

        /** The values   */
        protected List<AString> values                  = new List<AString>();

        /** The number of values currently stored. This may be less than items found in #values
            as those are reused objects. */
        protected int           qtyValues               = 0;


    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         * Constructs an undefined Variable. Prior to using this, #Declare has to be invoked.
         ******************************************************************************************/
        public Variable()
        {
            clear();
        }

        /** ****************************************************************************************
         * Constructs a variable from a declaration.
         * Strings named \c "%1", \c "%2" ... \c "%N" found in the fields #Category, #Name,
         * #Comments and #DefaultValue are replaced with given replacement strings found
         * in vector \p{replacements}.
         *
         * @param declaration    The declaration data of the variable.
         * @param replacements   List of objects that will be converted to strings using
         *                       \ref cs.aworx.lib.strings.AString._(Object) "AString._(Object)".
         ******************************************************************************************/
          public Variable( VariableDecl declaration, params Object[] replacements )
          {
              Declare( declaration, replacements );
          }

        /** ****************************************************************************************
         * Constructs a variable using the declaration of another variable. The values are not
         * copied.
         *
         * @param variable  A variable to copy the declaration (which is comprised with fields
         *                  #Category, #Name, #Fullname, #Delim, #Comments and #DefaultValue) from.
         ******************************************************************************************/
        public Variable( Variable variable )
        {
            Declare( variable );
        }

        /** ****************************************************************************************
         * Constructs a variable from the given values
         *
         * @param category  The category of the variable.
         * @param name      The name of the variable
         * @param delim     A proposal for a delimiter that might be used by some plug-ins
         *                  to delimit different values from each other (e.g. INI files).
         * @param comments  Comment lines that might be added in the configuration storage
         *                  (plug-in implementation dependent).
         ******************************************************************************************/
        public Variable( Object category,  Object name,
                         char   delim    = '\0' ,
                         Object comments = null  )
        {
            Declare( category, name, delim, comments );
        }

    // #############################################################################################
    // Interface
    // #############################################################################################

        /** ****************************************************************************************
         * Re-initializes a variable from a declaration. Strings named \c "%1", \c "%2" ... \c "%N"
         * found in the fields  #Category, #Name, #Comments and #DefaultValue are replaced with
         * given replacement string arguments in vector \p{replacements}.
         *
         * @param declaration    The declaration data of the variable.
         * @param replacements   List of objects that will be converted to strings using
         *                       \ref cs.aworx.lib.strings.AString._(Object) "AString._(Object)".
         *
         * @return \c this to allow concatenated operations.
         ******************************************************************************************/
        public
        Variable   Declare( VariableDecl declaration, params Object[] replacements )
        {
            clear();

            Delim=                  declaration.Delim;
            FormatHints=            declaration.FormatHints;
            FormatAttrAlignment=    declaration.FormatAttrAlignment;

            // set Category, Name, Comment
            if(  declaration.Category != null ) Category._( declaration.Category );
            else                               Category._( declaration.CategoryFallback );

            Name    ._( declaration.Name    );
            Comments._( declaration.Comments );
            if ( declaration.DefaultValue != null )
                DefaultValue._()._( declaration.DefaultValue );
            else
                DefaultValue.SetNull();

            // replace strings
            if ( replacements != null && replacements.Length > 0 )
            {
                AString search= Fullname;                        // just an alias name
                AString repl=   new AString(); values.Add(repl); // reuse this string later
                for( int i= 0; i < replacements.Length; i++ )
                {
                    search._()._("%")._(i + 1);
                    repl  ._()._( replacements[i] );

                    Category    .SearchAndReplace( search, repl );
                    Name        .SearchAndReplace( search, repl );
                    Comments    .SearchAndReplace( search, repl );
                    DefaultValue.SearchAndReplace( search, repl );
                }
                search._();
           }


            // set full name
            if( Category.IsNotEmpty() )
                Fullname._( Category )._( '_' );
            Fullname._( Name );

            ALIB_DBG.ASSERT_WARNING(  Name.IsNotEmpty(), "Empty variable name given" );

            return this;
        }

        /** ****************************************************************************************
         * Constructs a variable using the declaration of another variable. The values are not
         * copied.
         *
         * @param variable  A variable to copy the declaration (which is comprised with fields
         *                  #Category, #Name, #Fullname, #Delim, #Comments and #DefaultValue) from.
         * @return \c this to allow concatenated operations.
         ******************************************************************************************/
        public Variable Declare ( Variable variable )
        {
            clear();

            Category._(variable.Category);
            Name    ._(variable.Name);
            Fullname._(variable.Fullname);
            Comments._(variable.Comments);
            Delim=     variable.Delim;
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
        public
        Variable   Declare( Object category, Object name, char delim = '\0',
                            Object comments = null  )
        {
            clear();

            Category._(category);
            Name    ._(name);
            Comments._(comments);
            Delim=     delim;

            if( Category.IsNotEmpty() )
                Fullname._( Category )._( '_' );
            Fullname._( Name );
            return this;
        }

        /** ****************************************************************************************
         * Returns the number of values set in this object.
         *
         * @return The number of values set.
         ******************************************************************************************/
        public int         Size()
        {
            return qtyValues;
        }

        /** ****************************************************************************************
         * Clears the value, respectively the list of values set.
         * After invoking this method, #Size will return \p{startIdx} and #GetString will
         * return \c null for any index greater or equal to \p{startIdx}.
         *
         * @param  startIdx  The index of the first value to be cleared. Defaults to \c 0.
         * @return \c this to allow concatenated operations.
         ******************************************************************************************/
        public Variable    ClearValues(int startIdx= 0)
        {
            qtyValues= startIdx;
            return this;
        }

        /** ****************************************************************************************
         * Adds a value to the end of the list of values.
         * @return A reference to the string which can be manipulated to set the value.
         ******************************************************************************************/
        public AString    Add()
        {
            int actIdx= qtyValues;
            qtyValues++;
            if( actIdx < values.Count )
                return values[actIdx].Clear();

            AString newVal= new AString();
            values.Add( newVal );
            return newVal;
        }

        /** ****************************************************************************************
         * Adds the given string value to the end of the list of values.
         * @param  value  The value to set.
         * @return A reference to the string which can be further manipulated to set the value.
         ******************************************************************************************/
        public AString    Add( Object value )
        {
            return Add()._( value );
        }

        /** ****************************************************************************************
         * Adds the given boolean value to the end of the list of values.
         * For \c true values string \b "true" is set, otherwise \b "false".
         * \note
         *  Other, depending on the variable semantics, more user friendly values may be set using
         *  the string interface #Add.
         *  String values recognized for boolean variables are defined in
         * \ref cs.aworx.lib.config.Configuration.TrueValues   "Configuration.TrueValues".
         *
         * @param  value  The value to set.
         * @return A reference to the string representing the boolean value.
         ******************************************************************************************/
        public AString    Add( bool value )
        {
            return Add()._( value ? "true" : "false" );
        }

        /** ****************************************************************************************
         * Replaces the value at \p{idx} with the values of the given other variable.
         *
         * @param  idx          The index of the value to replace.
         * @param  replVariable The variable providing the replacement values.
         ******************************************************************************************/
        public void ReplaceValue( int idx, Variable replVariable )
        {
            if( idx < 0 || idx >= qtyValues )
            {
                ALIB_DBG.WARNING( "Index out of range: " + idx + " ( 0 - " + qtyValues + " allowed)." );
                return;
            }

            int replSize= replVariable.Size();
            if( replSize == 0 )
            {
                values.RemoveAt( idx );
                return;
            }

            values[ idx ]._()._( replVariable.GetString(0) );
            for( int i= 1 ; i < replSize; i++ )
            {
                values.Insert( idx + i, new AString( replVariable.GetString(i) ) );
                qtyValues++;
            }
       }

        /** ****************************************************************************************
         * Returns the value with the given index. Valid values for parameter \p{idx} are
         * between \c 0 and #Size <c>- 1</c>.
         * If no value is set for the given index, \c null is returned.
         *
         * \note
         *  It is explicitly allowed to change the contents of the \b %AString object returned,
         *  e.g. for a subsequent store operation.
         *
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p{idx}.
         ******************************************************************************************/
        public AString    GetString( int idx= 0 )
        {
            return idx < qtyValues  ? values[idx]
                                    : null;
        }

        /** ****************************************************************************************
         * Returns the value at \p{idx} interpreted as an integer.
         * If the index is invalid, \c 0 is returned.
         *
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p{idx} interpreted as an integer value.
         ******************************************************************************************/
        public long             GetInteger(int idx= 0)
        {
            return idx < qtyValues  ? GetString( idx ).ParseInt()
                                    : 0;
        }

        /** ****************************************************************************************
         * Returns the value at \p{idx} interpreted as a double value.
         * If the index is invalid, \c 0.0 is returned.
         * Parsing is done using field \c NumberFormat of field #Config, respectively, if this is
         * not set, the static singleton \alib{strings,NumberFormat.Global}.
         *
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p{idx} interpreted as a double value.
         ******************************************************************************************/
        public double           GetFloat(int idx= 0)
        {
            int newIdxdummy;
            return idx < qtyValues  ?   GetString( idx ).ParseFloat( Config.NumberFormat, out newIdxdummy )
                                    :   0.0;
        }

        /** ****************************************************************************************
         * Returns \c true if the first value represents a boolean 'true'.
         * Evaluation is done using field #Config, respectively if this is not set, the static
         * singleton \ref cs.aworx.lib.ALIB.Config "ALIB.Config".
         *
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p{idx} interpreted as a boolean value.
         ******************************************************************************************/
        public bool             IsTrue(int idx= 0)
        {
            return idx < qtyValues  ? Config.IsTrue( GetString( idx ) )
                                    : false;
        }

        /** ****************************************************************************************
         * Searches in the values of this variable for the pattern
         * <c>attrName = result</c> and
         * sets parameter \p{result} to the string following this pattern.
         *
         * @param      attrName     The name of the attribute searched.
         * @param[out] result       A substring with the result.
         * @param      attrDelim    The delimiter to search for. Defaults to '='.
         * @return \c true if the attribute was found, \c false otherwise.
         ******************************************************************************************/
        public bool    GetAttribute( String attrName, Substring result, char attrDelim= '=' )
        {
            for ( int i= 0; i< Size(); i++ )
            {
                result.Set( GetString(i ) );
                if (    result.ConsumeString( attrName,  Case.Ignore, Whitespaces.Trim )
                     && result.ConsumeChar  ( attrDelim, Case.Ignore, Whitespaces.Trim ) )
                {
                    result.Trim();
                    return true;
                }
            }
            return false;
        }


    // #############################################################################################
    // protected methods
    // #############################################################################################

        /** ****************************************************************************************
         * Clears all values.
         ******************************************************************************************/
        protected void        clear()
        {
            Config=         null;
            Priority=       0;
            Delim=          '\0';
            FormatHints=    0;


            Category._();
            Name    ._();
            Comments._();
            Fullname._();
            ClearValues();

        }
}

}// namespace

