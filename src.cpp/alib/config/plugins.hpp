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

namespace aworx {
namespace           lib {

namespace                   config {

/** ************************************************************************************************
 *  Abstract class that represents a plug in for class
 *  \ref aworx::lib::config::Configuration "Configuration"
 *  to provide configuration data from specific configuration data source.
 *
 *  Different attached plug-ins of type #ConfigurationPlugIn differentiate in their priority. This
 *  way, certain configuration methods can 'overwrite' values from other sources. See
 *  #aworx::lib::config for more information on priorities.
 *
 *  The plug-in also may have the ability to write data. The default implementation for writing
 *  configuration data returns constant \c false, indicating that this plug-in never writes
 *  anything (e.g. command line parameter plug-in, environment variable plug-in).
 *
 *  Category and Variable names are character case insensitive for the built-in
 *  ConfigurationPlugIn types
 *  \ref aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
 *  and
 *  \ref aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn".
 *  It is recommended to to ignore character case in custom specializations of class
 *  \ref aworx::lib::config::ConfigurationPlugIn "ConfigurationPlugIn"
 *  as well.
 *
 *  Variables belong to categories. The built-in ConfigurationPlugIns types
 *  CommandLinePlugIn and EnvironmentPlugIn just concatenate
 *  the category and the variable name with an underscore '_'.
 *  This means, if variable <em>LOCALE</em>
 *  in category <em>ALIB</em> is accessed, those plug-ins would check command line parameter
 *  <em>--ALIB_LOCALE=xyz</em> respectively environment variable <em>ALIB_LOCALE</em>
 **************************************************************************************************/
class ConfigurationPlugIn
{
    friend class Configuration;

    public:
        /** ****************************************************************************************
         *  The configuration object we got attached to.
         ******************************************************************************************/
        Configuration*        Parent                                                       =nullptr;

    protected:
        /** ****************************************************************************************
         *  Constructor which is protected, as this is an abstract class.
         ******************************************************************************************/
        ConfigurationPlugIn() {}

        /** ****************************************************************************************
         *  Virtual Destructor.
         ******************************************************************************************/
        virtual ~ConfigurationPlugIn() {}

        /** ****************************************************************************************
         *  Abstract method that has to be overwritten by descendants.
         *  Retrieves the string value of a configuration setting.
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param target    A reference to an empty AString to take the result.
         *  @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        ALIB_API virtual bool  Get( const String& category, const String& name, AString& target )   =0;

        /** ****************************************************************************************
         *  Retrieves the int value of a configuration setting. This default implementation
         *  invokes %Get(const String&, const String&, AString&)
         *  and converts the value to type integer.
         *  Descendants might overwrite this method.
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param target    A reference to an integer variable to take the result.
         *  @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        ALIB_API virtual bool  Get( const String& category, const String& name, int32_t& target );

        /** ****************************************************************************************
         *  Retrieves the floating point value of a configuration setting. This default implementation
         *  invokes the %Get(const String&, const String&, AString&)
         *  and converts the value to type double.
         *  Descendants might overwrite this method.
         *
         *  \note The conversion to double ignores the current locale setting and expects either a
         *        dot ('.') or a comma (',') as decimal operator. On the same token,the corresponding
         *        method #Save(const String&, const String&, double, const String&)
         *        writes always dots as separator characters, independent from local settings.
         *
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param target    A reference to an double variable to take the result.
         *  @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        ALIB_API virtual bool  Get( const String& category, const String& name, double& target );

        /** ****************************************************************************************
         *  Writes a string variable to the configuration.
         *  This default implementation just returns \c false. If this method is not overwritten
         *  in descendants, those descendants are not designed to write data.
         *
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param value     The value to write.
         *  @param comments  Comment lines that might be added in the configuration storage
         *                   (plug-in implementation dependent).
         *  @param delim     This parameter might be provided for variables that are
         *                   supposed to get long values that represent a list of delimited fields.
         *                   <br>The use of this character is specific to a plug-ins'
         *                   implementation.
         *
         *  @return \c true if the variable was written, \c false if not.
         ******************************************************************************************/
        ALIB_API virtual bool  Save( const String& category,  const String& name,
                                     const String& value,     const String& comments,
                                     char        delim                                   )
        {
            (void) category; (void) name; (void) value; (void) delim; (void) comments;
            return false;
        }

        /** ****************************************************************************************
         *  Writes an integer variable to the configuration.
         *  This default implementation converts the value to a string and invokes
         *  the string version of method %Save().
         *
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param value     The value to write.
         *  @param comments  Comment lines that might be added in the configuration storage
         *                   (plug-in implementation dependent).
         *
         *  @return \c true if the variable was written, \c false if not.
         ******************************************************************************************/
        ALIB_API virtual bool  Save( const String& category,  const String& name,
                                     int           value,     const String& comments   );

        /** ****************************************************************************************
         *  Writes a floating point variable to the configuration.
         *  This default implementation converts the value to a string and invokes
         *  the string version of method %Save().
         *  The floating point number format is not reflecting the current locale. Instead the
         *  decimal separator '.' is used.
         *
         *  \note The floating point to string conversion ignores the current locale setting and
         *        writes a dot ('.') as decimal operator. On the same token, the corresponding method
         *        #Get(const String&, const String&, double&)
         *        accepts both, a dot or a comma (',').
         *
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param value     The value to write.
         *  @param comments  Comment lines that might be added in the configuration storage
         *                   (plug-in implementation dependent).
         *
         *  @return \c true if the variable was written, \c false if not.
         ******************************************************************************************/
        ALIB_API virtual bool  Save( const String& category,  const String& name,
                                     double        value,     const String& comments );
};

/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugIn, which takes all command line
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
class CommandLinePlugIn : public ConfigurationPlugIn
{
    protected:
        int         argc;  ///< the number of command line arguments
        void**      argv;  ///< the list of command line arguments
        bool        wArgs; ///< determines if argv is of type '<em>wchar_t **</em>'
                           ///< or '<em>char **</em>'

    public:

        /** ****************************************************************************************
         * Constructor which takes the standard C main() function parameters as arguments
         *
         *\note In standard application scenarios, this constructor is invoked by method
         *      \ref aworx::lib::ALIB::Init "ALIB::Init".
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
        CommandLinePlugIn( int argc, void** argv= nullptr, bool wArgs= false );

        /** ****************************************************************************************
         * Virtual Destructor.
         ******************************************************************************************/
        virtual ~CommandLinePlugIn() {}

        /** ****************************************************************************************
         * Retrieves the string value of a configuration setting.
         * @param category  The category of the  variable.
         * @param name      The name of the configuration variable to be retrieved.
         * @param target    A reference to an empty AString to take the result.
         * @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        ALIB_API virtual bool  Get( const String& category, const String& name, AString& target );

};

/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugIn, retrieves configuration
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
class EnvironmentPlugIn : public ConfigurationPlugIn
{
    protected:

    public:

        /** ****************************************************************************************
         * Constructor.
         ******************************************************************************************/
        EnvironmentPlugIn();

        /** ****************************************************************************************
         *  Virtual Destructor.
         ******************************************************************************************/
        virtual ~EnvironmentPlugIn() {}

        /** ****************************************************************************************
         * Retrieves the string value of a configuration setting.
         * @param category  The category of the  variable.
         * @param name      The name of the configuration variable to be retrieved.
         * @param target    A reference to an empty AString to take the result.
         * @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        ALIB_API virtual bool  Get( const String& category, const String& name,  AString& target  );
};


}}}  // namespace aworx::lib::config

#endif // HPP_ALIB_CONFIG_PLUGINS
