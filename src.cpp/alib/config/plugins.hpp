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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_CONFIG_PLUGINS)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_CONFIG_PLUGINS
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_CONFIG_PLUGINS 1
#endif


#if !defined (HPP_ALIB_CONFIG_VARIABLE)
    #include "alib/config/variable.hpp"
#endif

#if !defined (HPP_ALIB_STRINGS_SUBSTRING)
    #include "alib/strings/substring.hpp"
#endif

namespace aworx {
namespace           lib {

namespace                   config {


// #################################################################################################
// class XTernalizer
// #################################################################################################

/** ************************************************************************************************
 * This virtual class is used by classes derived from
 * \ref aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin"
 * to convert external string to internal values and vice versa, and for parsing lists of values
 * from an external string.
 *
 * Class \b %ConfigurationPlugin owns a default object with field
 * \ref aworx::lib::config::ConfigurationPlugin::defaultStringConverter "ConfigurationPlugin::defaultStringConverter",
 * to which field
 * \ref aworx::lib::config::ConfigurationPlugin::StringConverter "ConfigurationPlugin::StringConverter"
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
class XTernalizer
{
    public:

    /** ********************************************************************************************
     * Parses values found in string \p src and adds them to \p variable.
     * @param  variable The destination variable.
     * @param  src      The source string
     **********************************************************************************************/
    ALIB_API
    virtual
    void    LoadFromString( Variable& variable, const String& src );

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
    ALIB_API
    virtual
    void InternalizeValue( Substring& src, AString& dest );

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
    ALIB_API
    virtual
    void ExternalizeValue( Substring& src, AString& dest, char delim );
};

/** ************************************************************************************************
 * Abstract class that represents a plug in for class
 * \ref aworx::lib::config::Configuration "Configuration"
 * to provide configuration data from specific configuration data source.
 *
 * See documentation of namespace #aworx::lib::config for more information on ALib
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
 **************************************************************************************************/
class ConfigurationPlugin
{
    // #############################################################################################
    // internal fields
    // #############################################################################################
    protected:
        /** The default external string converter */
        XTernalizer             defaultStringConverter;


    // #############################################################################################
    // public fields
    // #############################################################################################
    public:
        /** The external string converter.
         *  By default this points to field #defaultStringConverter.                 */
        XTernalizer*            StringConverter;

    // #############################################################################################
    // protected constructor/destructor
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Constructor which is protected, as this is an abstract class.
         ******************************************************************************************/
        ConfigurationPlugin() { StringConverter= &defaultStringConverter; }

        /** ****************************************************************************************
         * Virtual Destructor.
         ******************************************************************************************/
        virtual ~ConfigurationPlugin() {}

    // #############################################################################################
    // abstract/virtual interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Abstract method that has to be overwritten by descendants.
         * Searches and by default retrieves the value of a configuration variable.
         * If \p searchOnly is \c true, then the variable value is not read.
         *
         * @param variable      The variable to retrieve.
         * @param searchOnly    If \c true, the variable must not be set. Defaults to \c false.
         * @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        ALIB_API
        virtual bool  Load( Variable& variable, bool searchOnly= false )  const  =0;

        /** ****************************************************************************************
         * Writes a variable to the configuration.
         * This default implementation just returns \c false. If this method is not overwritten
         * in descendants, those descendants are not designed to write data.
         *
         * @param variable  The variable to store.
         *
         * @return \c true if the variable was written, \c false if not which typically indicates
         *         that this plug-in is not able to write values.
         ******************************************************************************************/
        virtual bool  Store( Variable& variable )
        {
            (void) variable;
            return false;
        }

        /** ****************************************************************************************
         * Convenience method that parses the values from the given string using field
         * #StringConverter and then invokes \ref Store(Variable&) "Store".
         *
         * @param variable          The variable to store.
         * @param externalizedValue The value to parse into the variable before storing
         *
         * @return \c true if the variable was written, \c false if not which typically indicates
         *         that this plug-in is not able to write values.
         ******************************************************************************************/
        virtual bool  Store( Variable& variable, const String& externalizedValue )
        {
            if( externalizedValue.IsNotNull() )
                StringConverter->LoadFromString( variable, externalizedValue );
            return Store( variable );
        }
};

/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugin, which takes all command line
 * parameters in the constructor and reads variable values from those parameters on request.
 * Its priority value is fixed to 10.
 *
 * Variable categories are used as a prefix together with an underscore '_'.
 * This means, if variable <em>LOCALE</em> in category <em>ALIB</em> is accessed, the command line
 * parameter <em>--ALIB_LOCALE=xyz</em> is read.
 *
 * Command line variables may be passed with either one hyphen ('-') or two ('--').
 * Both are accepted.
 *
 * Category and Variable names are insensitive in respect to character case.
 **************************************************************************************************/
class CommandLinePlugin : public ConfigurationPlugin
{
    protected:
        int         argc;  ///< the number of command line arguments
        void**      argv;  ///< the list of command line arguments
        bool        wArgs; ///< determines if argv is of type '<em>wchar_t **</em>'
                           ///< or '<em>char **</em>'

    public:

        /** ****************************************************************************************
         * Constructor. After creation, method #SetArgs should be called to equip this instance
         * with the command line agruments.
         ******************************************************************************************/
                 CommandLinePlugin() {}

        /** ****************************************************************************************
         * Virtual Destructor.
         ******************************************************************************************/
        virtual ~CommandLinePlugin() {}

        /** ****************************************************************************************
         * Sets the command line argument list. Needs to be called once after construction.
         * Should not be invoked directly. Rather use
         * \ref aworx::lib::config::Configuration::SetCommandLineArgs "Configuration::SetCommandLineArgs".
         *
         *\note In standard application scenarios, this method is invoked by method
         *      \ref aworx::lib::ALIB::Init "ALIB::Init" for the singleton of this class found
         *      in class \b %Configuration, which in turn is found as a singleton in
         *      \ref aworx::lib::ALIB::Config "ALIB::Config".
         *
         *\note On the Windows platform, the Microsoft compiler provides the global variables
         *      <em>__argc</em> and <em>__argv</em> (respectively <em>__wargv</em> for wide
         *      character binaries. These variables a can be used if this method is invoked
         *      outside of the <em>main()</em> method.
         *
         * @param argc    The number of arguments in argv
         * @param argv    The list of command line arguments.
         * @param wArgs   If \c true, parameter argv is of type '*<em>wchar_t **</em>', otherwise
         *                of type '<em>char **</em>'.
         *                Defaults to \c false.
         ******************************************************************************************/
        void SetArgs( int argc, void** argv= nullptr, bool wArgs= false )
        {
            this->argc=     argc;
            this->argv=     argv;
            this->wArgs=    wArgs;
        }

        /** ****************************************************************************************
         * Searches the variable in the command line parameters.
         *
         * @param variable     The variable to retrieve.
         * @param searchOnly   If \c true, the variable is not set. Defaults to \c false.
         * @return \c true if variable was found, \c false if not.
         ******************************************************************************************/
        ALIB_API virtual bool  Load( Variable& variable, bool searchOnly= false ) const;
};

/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugin, retrieves configuration
 * data from the system environment.
 *
 * This plug-ins' priority value is fixed to 10.
 *
 * Variable categories are used as a prefix together with an underscore '_'.
 * This means, if variable <em>LOCALE</em> in category <em>ALIB</em> is accessed, the environment
 * variable <em>ALIB_LOCALE</em> is read.
 *
 * Category and Variable names are insensitive in respect to character case.
**************************************************************************************************/
class EnvironmentPlugin : public ConfigurationPlugin
{
    protected:

    public:

        /** ****************************************************************************************
         * Constructor.
         ******************************************************************************************/
        EnvironmentPlugin();

        /** ****************************************************************************************
         * Virtual Destructor.
         ******************************************************************************************/
        virtual ~EnvironmentPlugin() {}

        /** ****************************************************************************************
         * Searches the variable in the environment.
         *
         * @param variable  The variable to retrieve.
         * @param searchOnly   If \c true, the variable is not set. Defaults to \c false.
         * @return \c true if variable was found, \c false if not.
         ******************************************************************************************/
        ALIB_API virtual bool  Load( Variable& variable, bool searchOnly= false  ) const;
};


}}}  // namespace aworx::lib::config

#endif // HPP_ALIB_CONFIG_PLUGINS
