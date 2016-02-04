// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################
/** @file */ // Hello Doxyen

// check for alib.hpp already there but not us
#if !defined (HPP_AWORX_LIB_ALIB)
    #error "include \"alib/alib.hpp\" before including this header"
#endif
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_AWORX_LIB_CONFIG_CONFIGURATION)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_AWORX_LIB_CONFIG_CONFIGURATION
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_AWORX_LIB_CONFIG_CONFIGURATION 1
#endif

// #################################################################################################
// includes
// #################################################################################################

#if !defined (HPP_AWORX_LIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
#endif

#include "alib/strings/numberformat.hpp"
#include "alib/config/plugins.hpp"
#include <vector>

namespace aworx {
namespace           lib {

/** ************************************************************************************************
 * This namespace provides tools to read and write configuration data using different
 * mechanisms reading and writing such data.
 *
 * The different 'mechanisms' are implemented through plug-ins, namely objects of types
 * derived from class \ref aworx::lib::config::ConfigurationPlugIn "ConfigurationPlugIn".
 *
 * The plug-ins are gathered (plugged into) an object of type
 * \ref aworx::lib::config::Configuration "Configuration". This object is
 * usually a singleton and class \ref aworx::lib::ALIB "ALIB" creates and provides this
 * singleton as a static field already.
 * Class Configuration offers an interface to retrieve and store configuration variables using
 * the plug-ins. The plug-ins have a fixed priority. Values are retrieved and stored by
 * looping through the plug-ins in their defined order. As soon as one plug-in confirms to have
 * found (or stored) the variable, the loop ends. This way, plug-ins may "overrule" each other.
 *
 * Three different plug-ins are implemented within ALib already:
 * - Class CommandLinePlugIn:<br>
 *   Reads parameter values of the form -[-]CategoryName_VariableName=value from the command line.
 *   This plug-in has a proposed priority of 10. This plug-in does not write values.
 * - Class EnvironmentPlugIn:<br>
 *   Reads system defined environment variables
 *   (see [Wikipedia](https://en.wikipedia.org/wiki/Environment_variable) of the form
 *   CategoryName_VariableName=value
 *   This plug-in has a proposed priority of 20. This plug-in does not write values.
 * - Class IniFile:<br>
 *   Reads and writes quite standard INI files
 *   (see [Wikipedia](https://en.wikipedia.org/wiki/INI_file).
 *   This plug-in has a proposed priority of 30. This plug-in also write values.
 *
 * The priorities of the the three default plug-ins implemented within ALIB util classes are:
 *
 *  Command Line Arguments -> Environment Variables -> INI file
 *
 * This means, that whatever is stored in an INI file, can be overwritten by setting an environment
 * variable, and both settings can in turn be overwritten by specifying a corresponding command line
 * parameter when launching the process.
 *
 * \note Instead of using the provided class IniFile class, it is recommended to use application/platform
 * specific mechanisms for writing configuration data. The INI file method is designed for
 * simplicity and smaller applications.
 *
 **************************************************************************************************/
namespace                   config {

// #################################################################################################
// class Configuration
// #################################################################################################

/** ************************************************************************************************
 *  This class is supposed to be a static singleton in class ALIB.
 *  It holds a list of objects of type ConfigurationPlugIn, sorted by their priority and provides a
 *  single user interface to query configuration data from those.
 *
 *  By default, two configuration plug-ins are set up:
 *  - command line parameter configuration options (Priority 10)
 *  - environment variable configuration options (Priority 20)
 *
 *  An application specific instance of abstract class
 *  \ref aworx::lib::config::ConfigurationPlugIn "ConfigurationPlugIn"
 *  that uses
 *  appropriate configuration techniques (ini-files, registry entries, etc.)  optionally completes
 *  this set. It is proposed to use a priority value of 30 for for custom configuration plug-ins.
 *  This way, environment variables could <em>overwrite</em> entries in configuration files and
 *  command line parameters could in turn <em>overwrite</em> environment variables.
 *
 *  Variables are case insensitive for the built-in ConfigurationPlugIn types
 *  \ref aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn" and
 *  \ref aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn".
 *
 *  It is recommended to treat variable names case insensitive within custom implementations
 *  (specializations) of class ConfigurationPlugIn as well.
 *
 *  The interface methods of this class are implemented <em>synchronized</em>.
 *  When adding or removing plug-ins, the instance should by synchronized (locked) as well.
 **************************************************************************************************/
class Configuration : public threads::ThreadLock
{
    // #############################################################################################
    // internal fields
    // #############################################################################################
    protected:
        /// An element of the list of plug-ins with their priority
        typedef    std::pair<int, ConfigurationPlugIn*>     PrioAndPlugin;

        /// The plug-ins we have in our portfolio
        std::vector< PrioAndPlugin >  plugins;

    // #############################################################################################
    // public fields
    // #############################################################################################
    public:
        /** Values considered to indicate "true". Defaults to "1", "true", "yes" and "ok".
         *  Comparisons are made case insensitive.
         *
         *  Application specific values (e.g. localization languages) might be added by publicly
         *  accessing this field and adding new values (or removing existing).                    */
        std::vector<strings::AS>            TrueValues;

        /** The configuration plug-in for command line parameters. Created in the constructor.
         *  Provided as public field here, for flexibility. Please note:
         *  - When this object is removed from the plug-in list, responsibility of deletion goes
         *   to the remover.
         *  - When this object is replaced by a customized one, it also has to be added to the
         *   the list of plug-ins (and any existing one has to be removed).                      */
        CommandLinePlugIn*                  cmdLineCP;

        /** The environment plug-in for evaluation of system environment variables.
         *  Created in the constructor.
         *  Provided as public field here, for flexibility. Please note:
         *  - When this object is removed from the plug-in list, responsibility of deletion goes
         *    to the remover.
         *  - When this object is replaced by a customized one, it also has to be added to the
         *    the list of plug-ins (and any existing one has to be removed).                     */
        EnvironmentPlugIn*                  envCP;

        /** Number format definition used by plugins to write int and float values.  */
        strings::NumberFormat               NumberFormat;

    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         *  Constructs a configuration plug-in and optionally (default) creates two initial
         *  plug-ins, one that reads command line options, a second that uses the process
         *  environment as configuration source.
         *
         * \note In standard application scenarios, this constructor is invoked by method
         *       \ref aworx::lib::ALIB::Init "ALIB::Init".
         *
         * \note On the Windows platform, the Microsoft compiler provides the global variables
         *       <em>__argc</em> and <em>__argv</em> (respectively <em>__wargv</em> for wide
         *       character binaries. These variables a can be used if this method is invoked
         *       outside of the <em>main()</em> method.
         *
         *  @param environment  If \c Inclusion::Include (the default), an
         *                 EnvironmentPlugIn is created and attached.
         *                 To specify \c false here, might be useful, if a customized
         *                 ConfigurationPlugIn that (also) reads environment variables
         *                 will be attached.
         *  @param argc    Parameter taken from standard C main() method (the number of
         *                 arguments in argv).
         *                 Defaults to 0.
         *  @param argv    Parameter taken from standard C main() method (the list of command line
         *                 arguments).
         *                 Defaults to nullptr.
         *  @param wArgs   If \c true, parameter argv is of type '<em>wchar_t **</em>', otherwise
         *                 of type '<em>char **</em>'.
         *                 Defaults to \c false.
         ******************************************************************************************/
        ALIB_API Configuration( enums::Inclusion environment= enums::Inclusion::Include,
                                int  argc   =0,     void **argv =nullptr,   bool wArgs =false );

        /** ****************************************************************************************
         *  Destructs a configuration plug-in. All ConfigurationPlugIn that were assigned
         *  (using #InsertPlugin) will be deleted.
         ******************************************************************************************/
        ALIB_API virtual ~Configuration();

    // #############################################################################################
    // interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         *  Adds the given plug-in to the list of plug-ins used to query configuration values.
         *  @param plugin   The plug-in to insert.
         *  @param priority The priority of the plug-in.
         ******************************************************************************************/
        ALIB_API void InsertPlugin( ConfigurationPlugIn* plugin, int priority );

        /** ****************************************************************************************
         *  Remove the given plug-in from the list of plug-ins.
         *  Responsibility for deletion of removed plug-ins moves to the remover.
         *  Active (inserted) plug-ins get deleted by class' destructor.
         *  @param plugin  The plug-in to be deleted.
         *  @return \c true if the plug-in was removed, else \c false.
         ******************************************************************************************/
        ALIB_API bool RemovePlugin( ConfigurationPlugIn* plugin );

        /** ****************************************************************************************
         *  Retrieves a string value from the configuration settings. This is done by asking each of
         *  the installed plug-ins. As soon as the first one returns a value for the given variable
         *  name, this value is returned.
         *  All variable names are case insensitive.
         *  @param category       The category of the  variable.
         *  @param name           The name of the configuration variable to be retrieved.
         *  @param target         A reference to an AString to take the result.
         *                        This AString will be cleared, no matter if a configuration
         *                        variable was found or not.
         *
         *  @return Zero if the variable was not found. Otherwise it returns the priority of the
         *          (first) plug-in that contained the variable.
         *          This way, the caller might identify from which configuration
         *          source the variable was read.
         ******************************************************************************************/
        ALIB_API int   Get( const String& category, const String& name, AString&    target );


        /** ****************************************************************************************
         *  Retrieves an integer value from the configuration settings. This is done by asking each of
         *  the installed plug-ins. As soon as the first one returns a value for the given variable
         *  name, this value is returned.
         *  All variable names are case insensitive.
         *  @param category       The category of the  variable.
         *  @param name           The name of the configuration variable to be retrieved.
         *  @param target         A reference to an integer variable to take the result.
         *
         *  @return Zero if the variable was not found. Otherwise it returns the priority of the
         *          (first) plug-in that contained the variable.
         *          This way, the caller might identify from which configuration
         *          source the variable was read.
         ******************************************************************************************/
        ALIB_API int   Get( const String& category, const String& name, int32_t& target );

        /** ****************************************************************************************
         *  Retrieves a floating point value from the configuration settings. This is done by asking
         *  each of  the installed plug-ins. As soon as the first one returns a value for
         *  the given variable
         *  @param category       The category of the  variable.
         *  @param name           The name of the configuration variable to be retrieved.
         *  @param target         A reference to an double variable to take the result.
         *
         *  @return Zero if the variable was not found. Otherwise it returns the priority of the
         *          (first) plug-in that contained the variable.
         *          This way, the caller might identify from which configuration
         *          source the variable was read.
         ******************************************************************************************/
        ALIB_API int  Get( const String& category, const String& name, double&  target );

        /** ****************************************************************************************
         *  Uses
         *  \ref Get(const String&, const String&,AString&) "Get"
         *  to read a string value and returns \c true if this variable holds one of the
         *  values found in the #TrueValues string list. By default, this string list contains the
         *  strings "true", "yes" and "1" (case insensitive comparison).
         *  @param category       The category of the  variable.
         *  @param name           The name of the environment variable to read
         *                        the variable was defined, to \c false otherwise.
         *  @param pluginPriority An optional pointer to an integer. If set, the priority of the
         *                        plug-in which returned the configuration value will be stored
         *                        here. This way, the caller can identify if the variable
         *                        was defined at all (if \c false was returned) or even from which
         *                        configuration source the variable was read.
         *
         *  @return   Returns true, if the environment variable is defined and has one of the
         *            values found in field #TrueValues.
         ******************************************************************************************/
        ALIB_API bool  IsTrue( const String&  category,
                               const String&  name,
                               int*           pluginPriority= nullptr );

        /** ****************************************************************************************
         *  Writes the string variable to the configuration. This is done by asking each of our
         *  installed plug-ins to do so. As soon as the first one returns \c true, the variable
         *  is considered written and no other plug-ins are asked. This way, the pair of
         *  variable/value is stored within the configuration type with the lowest possible
         *  priory (e.g. user configuration vs. system wide configuration).
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param value     The value to write.
         *  @param comments  Comment lines that might be added in the configuration storage
         *                   (plug-in implementation dependent). Optional and defaults to nullptr.
         *  @param delim     This optional parameter should be provided for variables that are
         *                   supposed to get long values that represent a list of delimited fields.
         *                   <br>The use of this character is specific to a plug-ins' implementation.
         *                   Defaults to '\0'.
         *
         *  @return Zero if the variable was not written. Otherwise it returns the priority of the
         *          (first) plug-in that wrote the variable.
         *          This way, the caller might identify into which configuration
         *          source the variable was read.
         ******************************************************************************************/
        ALIB_API int  Save( const String&  category,
                            const String&  name,
                            const String&  value,
                            const String&  comments= NullString,
                            char           delim= ','               );

        /** ****************************************************************************************
         *  Writes the integer variable to the configuration. This is done by asking each of our
         *  installed plug-ins to do so. As soon as the first one returns \c true, the variable
         *  is considered written and no other plug-ins are asked. This way, the pair of
         *  variable/value is stored within the configuration type with the lowest possible
         *  priory (e.g. user configuration vs. system wide configuration).
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param value     The value to write.
         *  @param comments  Comment lines that might be added in the configuration storage
         *                   (plug-in implementation dependent). Optional and defaults to nullptr.
         *
         *  @return Zero if the variable was not written. Otherwise it returns the priority of the
         *          (first) plug-in that wrote the variable.
         *          This way, the caller might identify into which configuration
         *          source the variable was read.
         ******************************************************************************************/
        ALIB_API int  Save( const String&  category,
                            const String&  name,
                            int            value,
                            const String&  comments=  nullptr         );

        /** ****************************************************************************************
         *  Writes the double variable to the configuration. This is done by asking each of our
         *  installed plug-ins to do so. As soon as the first one returns \c true, the variable
         *  is considered written and no other plug-ins are asked. This way, the pair of
         *  variable/value is stored within the configuration type with the lowest possible
         *  priory (e.g. user configuration vs. system wide configuration).
         *  @param category  The category of the  variable.
         *  @param name      The name of the configuration variable to be retrieved.
         *  @param value     The value to write.
         *  @param comments  Comment lines that might be added in the configuration storage
         *                   (plug-in implementation dependent). Optional and defaults to nullptr.
         *
         *  @return Zero if the variable was not written. Otherwise it returns the priority of the
         *          (first) plug-in that wrote the variable.
         *          This way, the caller might identify into which configuration
         *          source the variable was read.
         ******************************************************************************************/
        ALIB_API int  Save( const String& category,
                             const String& name,
                             double        value,
                             const String& comments=  nullptr         );
};

}}}  // namespace aworx::lib::config

#endif // HPP_AWORX_LIB_CONFIG_CONFIGURATION
