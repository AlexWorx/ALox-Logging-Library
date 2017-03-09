// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxygen

// check for alib.hpp already there but not us
#if !defined (HPP_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_CONFIG_VARIABLE)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_CONFIG_VARIABLE
//! @cond NO_DOX
#define HPP_ALIB_CONFIG_VARIABLE 1
//! @endcond NO_DOX

#include <vector>

// forward declarations
namespace aworx {namespace lib {namespace strings{ class Substring; }}}

namespace aworx { namespace lib { namespace config
{
// Forward declarations
class Configuration;

/** ************************************************************************************************
 * A data record used to define an
 * \ref aworx::lib::config::Variable "ALib Configuration Variable".
 * While variables can also defined by setting their attributes individually, it is recommended to
 * define all external configuration variables in a central place, using statically or dynamically
 * allocated objects of this type.<br>
 * Objects of class \b %Variable can be constructed and existing objects can be reused by invoking
 * \ref aworx::lib::config::Variable::Define "Variable::Define". Both construction and
 * re-definition support to pass objects of this type.
 *
 * All fields (except #Delim) support placeholders \c "%1", \c "%2" ... \c "%N", which are
 * replaced with the constructor of class \b %Variable and method
 * \ref aworx::lib::config::Variable::Define "Variable::Define".
 * This allows to define a series of variables whose category, name, description and value is
 * dependent on runtime information.
 *
 * Besides the use for passing parameters into objects of type Variable, this struct does not
 * provide further logic.
 **************************************************************************************************/
struct VariableDefinition
{
    /**
     * Pointer to a category string which is used as fallback if field #Category is nulled.
     * This is useful as usually most variables share one general application specific
     * category. With the combination of fields #CategoryFallback and #Category,
     * the user (of a library) is be entitled to change single variables
     * or all at once. In the latter case, field #Category is left nulled, while this field
     * is set to a global default value (which also can be changed, therefore a pointer).
     */
    String*     CategoryFallback;

    /** The category for this value. May be left nulled in which case field
     *  #CategoryFallback is applied. */
    String      Category;

    /** The name of the variable. */
    String      Name;

    /**
     * The default value. If this is \c nullptr, no variable will be created with method
     * \ref aworx::lib::config::Configuration::Load "Configuration::Load".
     * \note
     *   The field is ignored when using the plug-in interface
     *   \ref aworx::lib::config::ConfigurationPlugin::Load "ConfigurationPlugin::Load".
     */
    String      DefaultValue;

    /** The delimiter passed to the plug-in as a hint on how to separate values.
     *  (May or may not be used by a plug-in)  */
    char        Delim;

    /** If set attributes written in multi-lines are vertically aligned by this character or
     *  string. Use cases are "=", ":" or "->".<br> Used by
     *  \ref aworx::lib::config::IniFile "IniFile" and potentially by custom plug-ins. */
    String16    FormatAttrAlignment;

    /** Hints for formatting textual configuration files. (Used by class
        \ref aworx::lib::config::IniFile "IniFile" and potentially by custom plug-ins.*/
    int         FormatHints;

    /** Comments for the variable. Some plug-ins allow to store comments along with the
     *  variable (e.g. class \ref aworx::lib::config::IniFile).*/
    String      Comments;

};

/** ************************************************************************************************
 * This class is used to load and store external configuration data with objects of class
 * \ref aworx::lib::config::Configuration       "Configuration" and its plug-ins
 * \ref aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin".
 *
 * \note
 *   For general information about external configuration variables, see namespace documentation
 *   \ref aworx::lib::config "aworx::lib::config".
 *
 * <b>Construction/Redefinition:</b><br>
 * While constructors accepting attributes of a variable exist, it is recommended to
 * define all external configuration variables in a central place, using statically or dynamically
 * allocated objects of type
 * \ref aworx::lib::config::VariableDefinition "VariableDefinition" and pass such record
 * to the constructor of a variable.
 *
 * The class is designed to be 'reused' to avoid repeated allocation/de-allocation of memory.
 * After invoking one of the overloaded methods #Define, which share the same signatures as
 * the overloaded constructors, a variable is freshly initialized. Internally, the memory
 * allocated for values remains allocated.
 *
 * <b>Values:</b><br>
 * A variable can contain zero, one or several values. If zero, then the variable was either not
 * loaded, yet or the load operation failed (no configuration plug-in defined the variable).
 * Method #Size reports the currently available values and methods #GetString(int), #GetInteger(int)
 * and #GetFloat(int) return a value. Internally all values are stored as strings. If
 * field #Config is set, its field
 * \ref aworx::lib::config::Configuration::NumberFormat "Configuration::NumberFormat"
 * is used for floating point conversion.
 *
 * When storing a variable that contains more than one value, field #Delim has to be set.
 * Conversely, when reading a variable that contains multiple values, the delimiter has to be set
 * prior to the load operation.
 * \note
 *   This is not true when loading/storing a variable directly in a plug-in of type
 *   \ref aworx::lib::config::InMemoryPlugin "InMemoryPlugin"   or might also not be true
 *   with custom configuration plug-in types which
 *   for example might store the values in a database.<br>
 *   However, with the default plug-ins
 *   \ref aworx::lib::config::CommandLinePlugin "CommandLinePlugin",
 *   \ref aworx::lib::config::EnvironmentPlugin "EnvironmentPlugin" and
 *   \ref aworx::lib::config::IniFile "IniFile"
 *   the delimiter is needed! Therefore, it is best practice to always define a proper delimiter if
 *   a variable is multi-valued.
 *
 * <b>Loading and Storing:</b><br>
 * There are three ways of loading and storing a variable:
 * - Using the interface of class \ref aworx::lib::config::Configuration "Configuration"
 *   which allows to load and store variables from different sources (plug-ins) in a prioritized
 *   way.
 * - Using the interface of class \ref aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin"
 *   which may be used if the decision about the source or drain of a load/store operation is explicitly
 *   made by a code unit.
 * - Using the interface methods #Load,#Store, #StoreDefault and #Protect found in this class
 *   itself which are provided for convenience. Those simply invoke the interface of the static global singleton
 *   \ref aworx::lib::config::Configuration::Default "Configuration::Default".
 *
 * Using the interface of this class itself is the most convenient way of loading and storing
 * variables, setting default values or protecting variables.
 * Only very few use cases demand for the creation and use of an instance of class
 * \b %Configuration different to the static singleton \b %Configuration::Default.
 *
 * Storing empty variables (method #Size returns \c 0) deletes a variable from the those
 * configuration plug-ins that are write enabled.
 **************************************************************************************************/
class Variable
{
    // #############################################################################################
    // Public fields
    // #############################################################################################
    public:
        /** Denotes hints for formatting variables when storing in external configuration files  */
        enum
        {
            /* No hints **/
            FormatHint_None                    = 0      ,

            /* Write each argument in a new line **/
            FormatHint_MultLine                = 1 <<  0,

            /* Suppress spaces around the delimiter (only used in single line mode) **/
            FormatHint_NoDelimSpaces           = 1 <<  1,

            /* This and upward bits are reserved for custom plug-ins **/
            FormatHint_Custom                  = 1 <<  16,
        };

        /** The \b %Configuration that was recently used to request or store the value.  */
        Configuration*  Config;

        /** The configuration variable category.  */
        String64        Category;

        /** The configuration variable name.  */
        String64        Name;

        /**
         *  The delimiter used for parsing and storing values by simple textual plug-ins which
         *  use the default version of
         *  \ref aworx::lib::config::XTernalizer "XTernalizer"
         *  for in- and externalizing variables.
         */
        char            Delim;

        /** Hints for formatting textual configuration files. (Used by class
            \ref aworx::lib::config::IniFile "IniFile" and potentially by custom plug-ins.*/
        int             FormatHints;

        /** If set attributes written in multi-lines are vertically aligned by this character or
         *  string. Use cases are "=", ":" or "->".<br> Used by
         *  \ref aworx::lib::config::IniFile "IniFile" and potentially by custom plug-ins. */
        String16        FormatAttrAlignment;

        /** The configuration variable comments with placeholders replaced */
        AString         Comments;



        /** The configuration variable category and name concatenated with an underscore
         *  character \c '_'. This is useful e.g. for naming variables in log messages. */
        String64        Fullname;

        /**
         * The default value provided as an externalized string.
         *
         * The only occasion that this value is used is with method
         * \ref aworx::lib::config::Configuration::Load   "Configuration::Load".
         * If no plug-in has this variable defined and this field is not \e nulled, then
         * the value is written into plug-in
         * \ref aworx::lib::config::Configuration::DefaultValues   "Configuration::DefaultValues",
         * respectively - if this was replaced by the user - into a plug-in found at or below priority
         * \ref aworx::lib::config::Configuration::PrioDefault   "Configuration::PrioDefault".
         *
         * In this case, the value is parsed using method
         * \ref aworx::lib::config::XTernalizer::LoadFromString  "XTernalizer::LoadFromString"
         * of field
         * \ref aworx::lib::config::ConfigurationPlugin::StringConverter  "ConfigurationPlugin::StringConverter"
         * of the plug-in writing the value.
         *
         * \note
         *   The field is ignored when using the plug-in interface
         *   \ref aworx::lib::config::ConfigurationPlugin::Load "ConfigurationPlugin::Load"
         *   directly. To store this value 'manually' directly to a plug-in, invoke
         *   \ref aworx::lib::config::ConfigurationPlugin::Store "ConfigurationPlugin::Store"
         *   with providing value explicitly.
         */
        AString         DefaultValue;

        /**
         * A value related to the priority of a configuration plug-in.
         * The following values apply:
         * - \c -1 after creation or definition (reuse).
         * - The priority of the plug-in that loaded the value (after calling
         *   \ref aworx::lib::config::Configuration::Load   "Configuration::Load").
         * - The priority of the plug-in that stored the value (after calling
         *   \ref aworx::lib::config::Configuration::Store "Configuration::Store").
         * - \c 0, if the last load or store operation failed.
         * In addition prior to storing a variable, the value might be manually set. See
         * documentation of
         * \ref aworx::lib::config::Configuration::Store "Configuration::Store") for details.
         */
        int             Priority;

    // #############################################################################################
    // Protected fields
    // #############################################################################################
    protected:
        /** The values   */
        std::vector<AString> values;

        /** The number of values currently stored. This may be less than items found in #values
            as those are reused objects. */
        int qtyValues=   0;


    // #############################################################################################
    // Constructors and Define
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Constructs an undefined Variable. Prior to using this, #Define has to be invoked.
         ******************************************************************************************/
         Variable()    { clear(); }

        /** ****************************************************************************************
         * Constructs a variable from a definition.
         * Strings named \c "%1", \c "%2" ... \c "%N" found in the fields #Category, #Name,
         * #Comments and #DefaultValue are replaced with given replacement strings found
         * in variadic argument list \p replacements.
         *
         * @param definition     The definition data of the variable.
         * @param replacements   List of arguments. Must be of types that are accepted by constructor
         *                       of class \ref aworx::lib::strings::String "String".
         * @tparam StringTypes   The variadic argument types.
         ******************************************************************************************/
        template<typename... StringTypes>
        Variable( const VariableDefinition& definition,  const StringTypes&... replacements )
        {
            Define( definition, replacements... );
        }

        /** ****************************************************************************************
         * Constructs a variable using the definition of another variable. The values are not
         * copied.
         *
         * @param variable  A variable to copy the definition (which is comprised with fields
         *                  #Category, #Name, #Fullname, #Delim, #Comments and #DefaultValue) from.
         ******************************************************************************************/
        Variable( const Variable& variable )
        {
            Define( variable );
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
        Variable( const String& category,  const String& name,  char delim= '\0',
                  const String& comments  = nullptr      )
        {
            Define( category, name, delim, comments );
        }

        /** ****************************************************************************************
         * Re-initializes a variable from a definition. Strings named \c "%1", \c "%2" ... \c "%N"
         * found in the fields  #Category, #Name, #Comments and #DefaultValue are replaced with
         * given replacement string arguments in vector \p replacements.
         *
         * @param definition     The definition data of the variable.
         * @param replacements   List of replacement strings.
         * @return \c *this to allow concatenated operations.
         ******************************************************************************************/
        ALIB_API
        Variable&   Define( const VariableDefinition&    definition,
                            std::vector<String>&         replacements );

        /** ****************************************************************************************
         * Re-initializes a variable from a definition. Strings named \c "%1", \c "%2" ... \c "%N"
         * found in the fields  #Category, #Name, #Comments and #DefaultValue are replaced with
         * given replacement string arguments in variadic argument list \p replacements.
         *
         * @param definition     The definition data of the variable.
         * @param replacements   Replacement strings. Must be of types that are accepted by
         *                       constructor of class
         *                       \ref aworx::lib::strings::String "String".
         * @tparam StringTypes      The variadic argument types.
         * @return \c *this to allow concatenated operations.
         ******************************************************************************************/
        template<typename... StringTypes>
        Variable&   Define( const VariableDefinition& definition, const StringTypes&... replacements )
        {
            std::vector<String> argsAsVector= {replacements...};

            return Define( definition, argsAsVector );
        }

        /** ****************************************************************************************
         * Constructs a variable using the definition of another variable. The values are not
         * copied.
         *
         * @param variable  A variable to copy the definition (which is comprised with fields
         *                  #Category, #Name, #Fullname, #Delim, #Comments and #DefaultValue) from.
         * @return \c *this to allow concatenated operations.
         ******************************************************************************************/
        Variable& Define ( const Variable& variable )
        {
            clear();

            Category._(variable.Category);
            Name    ._(variable.Name);
            Fullname._(variable.Fullname);
            Comments._(variable.Comments);
            Delim=     variable.Delim;
            return *this;
        }

        /** ****************************************************************************************
         * Re-initializes the variable with the new definition
         *
         * @param category  The category of the variable.
         * @param name      The name of the variable
         * @param delim     A proposal for a delimiter that might be used by some plug-ins
         *                  to delimit different values from each other (e.g. INI files).
         *                  Defaults to \c '\0'.
         * @param comments  Comment lines that might be added in the configuration storage
         *                  (plug-in implementation dependent).
         *                  Defaults to \c nullptr.
         *
         * @return \c *this to allow concatenated operations.
         ******************************************************************************************/
        ALIB_API
        Variable&   Define( const String& category,  const String& name,
                            char          delim    = '\0',
                            const String& comments = nullptr                  );


    // #############################################################################################
    // Interface
    // #############################################################################################
        /** ****************************************************************************************
         * Returns the number of values set in this object.
         *
         * @return The number of values set.
         ******************************************************************************************/
        inline
        int         Size() const
        {
            return qtyValues;
        }

        /** ****************************************************************************************
         * Clears the value, respectively the list of values set.
         * After invoking this method, #Size will return \p startIdx and #GetString will
         * return \c nullptr for any index greater or equal to \p startIdx.
         *
         * @param  startIdx  The index of the first value to be cleared. Defaults to \c 0.
         * @return \c *this to allow concatenated operations.
         ******************************************************************************************/
        inline
        Variable&   ClearValues(int startIdx= 0)
        {
            qtyValues= startIdx;
            return *this;
        }

        /** ****************************************************************************************
         * Adds a value to the end of the list of values.
         * @return A reference to the string which can be manipulated to set the value.
         ******************************************************************************************/
        ALIB_API
        AString&    Add();

        /** ****************************************************************************************
         * Adds the given value to the end of the list of values.
         * Template type \p TApplicable needs to be a type which is applicable to objects of
         * type \b %AString.
         * See struct \ref aworx::lib::strings::T_Apply "T_Apply" for more information.
         *
         * If a different format is desired (minimum digits, etc.), then
         * #Add is to be used and conversion done proprietary on the returned string objects.
         *
         * @param  value  The value to set.
         * @return A reference to the string representing the integer value.
         ******************************************************************************************/
        template<typename TApplicable>
        inline
        AString&  Add( const TApplicable& value )
        {
            return Add()._( value );
        }

        /** ****************************************************************************************
         * Replaces the value at \p idx with the values of the given other variable.
         *
         * @param  idx          The index of the value to replace.
         * @param  replVariable The variable providing the replacement values.
         ******************************************************************************************/
        ALIB_API
        void ReplaceValue( int idx, Variable& replVariable );

        /** ****************************************************************************************
         * Returns the value with the given index. Valid values for parameter \p idx are
         * between \c 0 and #Size.
         * If no value is set for the given index, \c nullptr is returned.
         *
         * \note
         *  It is explicitly allowed to change the contents of the \b %AString object returned,
         *  e.g. for a subsequent store operation.
         *
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p idx.
         ******************************************************************************************/
        inline
        AString*    GetString( int idx= 0 )
        {
            return idx < qtyValues  ? &values[static_cast<size_t>(idx)]
                                    : nullptr;
        }

        /** ****************************************************************************************
         * Returns the value at \p idx interpreted as an integer.
         * If the index is invalid, \c 0 is returned.
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p idx interpreted as an integer value.
         ******************************************************************************************/
        ALIB_API
        integer GetInteger(int idx= 0);

        /** ****************************************************************************************
         * Returns the value at \p idx interpreted as a double value.
         * If the index is invalid, \c 0.0 is returned.
         * Parsing is done using field \c NumberFormat of field #Config, respectively, if this is
         * not set, the static singleton
         * \ref aworx::lib::config::Configuration::Default "Configuration::Default".
         *
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p idx interpreted as a double value.
         ******************************************************************************************/
        ALIB_API
        double  GetFloat(int idx= 0);

        /** ****************************************************************************************
         * Returns \c true if the first value represents a boolean 'true'.
         * Evaluation is done using field #Config, respectively if this is not set, the static
         * singleton
         * \ref aworx::lib::config::Configuration::Default "Configuration::Default".
         *
         * @param  idx  The index of the value to be retrieved.  Defaults to \c 0.
         * @return The value at \p idx interpreted as a boolean value.
         ******************************************************************************************/
        ALIB_API
        bool    IsTrue(int idx= 0);

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
        ALIB_API
        bool    GetAttribute( const String& attrName, strings::Substring& result, char attrDelim= '=' );


        /** ****************************************************************************************
         * Convenience method that loads the values of a variable from the static singleton
         * \ref aworx::lib::config::Configuration::Default "Configuration::Default", using method
         * \ref aworx::lib::config::Configuration::Load "Configuration::Load".
         *
         * @returns The priority of the configuration plug-in that provided the result.
         *          \c 0 if not found,
         *          \ref aworx::lib::config::Configuration::PrioDefault "Configuration::PrioDefault"
         *          if either found or created in
         *          \ref aworx::lib::config::Configuration::DefaultValues "Configuration::Default::DefaultValues"
         ******************************************************************************************/
        ALIB_API
        int     Load();

        /** ****************************************************************************************
         * Convenience method that stores the values of a variable using the static singleton
         * \ref aworx::lib::config::Configuration::Default "Configuration::Default", and method
         * \ref aworx::lib::config::Configuration::Store "Configuration::Store".
         *
         * Optional parameter \p externalizedValue allows to provide a string that is parsed
         * by the storing plug-in to reset the variables' values prior to writing.
         *
         * @param externalizedValue     Optional externalized value string. If given, the variable
         *                              is set prior to writing.
         * @returns The result of
         *          \ref aworx::lib::config::Configuration::Store "Configuration::Default::Store(*this)".
         ******************************************************************************************/
        ALIB_API
        int     Store( const String& externalizedValue= nullptr );

        /** ****************************************************************************************
         * Convenience method that stores the variable with priority
         * \ref aworx::lib::config::Configuration::PrioDefault "Configuration::PrioDefault"
         * using the static singleton found in
         * \ref aworx::lib::config::Configuration::Default "Configuration::Default".
         *
         * The variable value is determined as follows:
         * - If optional parameter \p externalizedValue is provided and not \e nulled, the values
         *   are loaded from that string.
         * - Otherwise, if the variable has no values set but field #DefaultValue is not \e nulled
         *   then values are loaded from this field.
         * - If all is unset (the variable values, parameter \p externalizedValue and field
         *   #DefaultValue), then the unset variable is stored, which results in removing a
         *   an existing default value from the configuration.
         *
         *
         * @param externalizedValue     Optional externalized value string. If given, the variable
         *                              is set prior to writing.
         * @returns The result of
         *          \ref aworx::lib::config::Configuration::Store "Configuration::Default::Store(*this)".
         ******************************************************************************************/
        ALIB_API
        int     StoreDefault( const String& externalizedValue= nullptr );

        /** ****************************************************************************************
         * Convenience method that stores the variable with priority
         * \ref aworx::lib::config::Configuration::PrioProtected "Configuration::PrioProtected"
         * using the static singleton found in
         * \ref aworx::lib::config::Configuration::Default "Configuration::Default".
         *
         * The variable value is determined as follows:
         * - If optional parameter \p externalizedValue is provided and not \e nulled, the values
         *   are loaded from that string.
         * - Otherwise, if the variable has no values set but field #DefaultValue is not \e nulled
         *   then values are loaded from this field.
         * - If all is unset (the variable values, parameter \p externalizedValue and field
         *   #DefaultValue), then the unset variable is stored, which results in removing a
         *   an existing protection value from the configuration.
         *
         * @param externalizedValue     Optional externalized value string. If given, the variable
         *                              is set prior to writing.
         * @returns The result of
         *          \ref aworx::lib::config::Configuration::Store "Configuration::Default::Store(*this)".
         ******************************************************************************************/
        ALIB_API
        int     Protect( const String& externalizedValue= nullptr );


        /** ****************************************************************************************
         * Convenience method to set values according to the provided string.
         * For the conversion of the "externalized" string, method
         * \ref aworx::lib::config::XTernalizer::LoadFromString "XTernalizer::LoadFromString"
         * of field
         * \ref aworx::lib::config::ConfigurationPlugin::StringConverter "ConfigurationPlugin::StringConverter"
         * of default plug-in
         * \ref aworx::lib::config::Configuration::DefaultValues "Configuration::DefaultValues"
         * of static singleton
         * \ref aworx::lib::config::Configuration::Default "Configuration::Default" is used.
         *
         * @param externalizedValue     The new value to write.
         *
         * @returns The #Size of the variable after parsing.
         ******************************************************************************************/
        ALIB_API
        int   LoadFromString( const String& externalizedValue );


    // #############################################################################################
    // protected methods
    // #############################################################################################

        /** Clears all values.  */
        ALIB_API
        void   clear();

};


}} // namespace lib::config

// /** Type alias name in namespace #aworx. */
using     VariableDefinition= aworx::lib::config::VariableDefinition;

// /** Type alias name in namespace #aworx. */
using     Variable=           aworx::lib::config::Variable;

}  // namespace aworx

#endif // HPP_ALIB_CONFIG_VARIABLE
