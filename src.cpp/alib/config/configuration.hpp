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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_CONFIG_CONFIGURATION)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_CONFIG_CONFIGURATION
//! @cond NO_DOX
#define HPP_ALIB_CONFIG_CONFIGURATION 1
//! @endcond NO_DOX

// #################################################################################################
// includes
// #################################################################################################

#if !defined (HPP_ALIB_THREADS_THREADLOCK)
    #include "alib/threads/threadlock.hpp"
#endif

#if !defined(HPP_ALIB_STRINGS_SUBSTRING)
    #include "alib/strings/substring.hpp"
#endif

#if !defined(HPP_ALIB_STRINGS_NUMBERFORMAT)
    #include "alib/strings/numberformat.hpp"
#endif

#if !defined(HPP_ALIB_CONFIG_VARIABLE)
    #include "alib/config/variable.hpp"
#endif
#if !defined(HPP_ALIB_CONFIG_PLUGINS)
    #include "alib/config/plugins.hpp"
#endif
#if !defined(HPP_ALIB_CONFIG_INMEMORY_PLUGIN)
    #include "alib/config/inmemoryplugin.hpp"
#endif


#include <vector>

namespace aworx { namespace lib { namespace config {


// #################################################################################################
// class Configuration
// #################################################################################################

/** ************************************************************************************************
 * This class primarily is used via its public static singleton instance
 * \ref aworx::lib::config::Configuration::Default "Configuration::Default".
 * It holds a list of objects of type
 * \ref aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin",
 * sorted by their priority and provides a
 * single user interface to query configuration data from those.
 *
 * The class inherits from
 * \ŗef aworx::lib::threads::ThreadLock "ThreadLock" and interface methods are implemented
 * <em>synchronized</em>.
 *
 * By default, all category and variable names are case insensitive. This is at least true for the
 * default plug-ins delivered with ALib.
 *
 * Variables by default can contain other variables, which are recursively substituted
 * by this method. For more information about the (adjustable) syntax, see
 * \ref cpp_alib_namespace_config_substitution "Variable Substitution".
 *
 * See documentation of namespace #aworx::lib::config for more information on ALib
 * external configuration variables.
 **************************************************************************************************/
class Configuration : public threads::ThreadLock
{
    // #############################################################################################
    // internal fields
    // #############################################################################################
    protected:
        /** An element of the list of plug-ins with their priority */
        typedef    std::pair<int, ConfigurationPlugin*>     PluginAndPrio;

        /** The plug-ins we have attached */
        std::vector< PluginAndPrio >  plugins;

    // #############################################################################################
    // public fields
    // #############################################################################################
    public:
        /**
         * This is the default singleton for standard use. Note that it is allowed to have
         * multiple instances of this class but this default is provided for convenience as
         * standard applications have just one.<br>
         * Overloaded methods found in classes of this namespace, which omit the configuration
         * parameter use this singleton instead.
         * Of-course, also custom plug-ins may be attached to this object.
         */
        ALIB_API static    config::Configuration    Default;


        /**
         * Values considered to indicate "true". Defaults to
         * { "1", "true", "t", "yes", "y", "on", "ok" }.
         * See methods #IsTrue.
         *
         * Application specific values (e.g. localization languages) might be added by publicly
         * accessing this field and adding new values (or removing existing).
         */
        std::vector<String>                 TrueValues;

        /** Number format definition used to read and write int and float values.  */
        strings::NumberFormat               NumberFormat;

        /**
         * The start string to identify substitution variables.
         * Defaults to single character \c '$'. If a string is set, i.e. \c "${", then field
         * #SubstitutionVariableEnd may be set accordingly, i.e. \c "}"
         */
        TString                             SubstitutionVariableStart                           = "$";

        /**
         * The end of a substitution variables.
         * If this field is set, then field #SubstitutionVariableDelimiters is ignored. If this field
         * is nullptr (the default) or empty, it is ignored and characters in field
         * #SubstitutionVariableDelimiters are used to identify the end of the variable.
         */
        TString                             SubstitutionVariableEnd                         = nullptr;

        /**
         * The delimiters used to identify the end of a substitutable variable.
         * If field #SubstitutionVariableEnd is not empty, this field is ignored. Otherwise, all
         * characters defined in this string are used to identify the end of a substitution
         * variable.
         */
        TString                             SubstitutionVariableDelimiters= " $@,.;:\"\'+-*/\\§%&()[]{}<>=?'`~#";

        /** The in-memory configuration plug-in that stores default values. */
        InMemoryPlugin                      DefaultValues;

        /** The in-memory configuration plug-in that stores values that are not changeable
            by external configuration data. */
        InMemoryPlugin                      ProtectedValues;

        /** The plug-in for command line parameters.      */
        CommandLinePlugin                   CmdLine;

        /** The plug-in for the evaluation of system environment variables. */
        EnvironmentPlugin                   Environment;

        /** Constant providing the highest possible priority. This is used with
         *  #ProtectedValues */
        static constexpr  int               PrioProtected        =(std::numeric_limits<int>::max)();

        /** Constant providing default priority for \b %IniFile (or similar) plug-in. */
        static constexpr  int               PrioCmdLine                                       = 400;

        /** Constant providing default priority for environment variables plug-in. */
        static constexpr  int               PrioEnvironment                                   = 300;

        /** Constant providing default priority for command-line parameters plug-in. */
        static constexpr  int               PrioIniFile                                       = 200;

        /** Constant providing a low priority. This is used with #DefaultValues */
        static constexpr  int               PrioDefault                                       = 100;

        /**
         * Constant providing a priority which is even lower than default. This priority is
         * not used by any standard plug-ins and currently not even anywhere in core ALib.
         * The rational to provide it is for third party libraries that may use this value
         * in cases where values are estimated or detected. A user of the library may then
         * overwrite such auto-detection by setting a default value in the configuration.
         */
        static constexpr  int               PrioAutodetect                                     = 50;

    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################
    public:
        /** ****************************************************************************************
         * Constructs a Configuration. Registers the initial plug-ins
         * #DefaultValues,
         * #CmdLine,
         * #Environment and
         * #ProtectedValues.
         ******************************************************************************************/
        ALIB_API            Configuration();

        /** ****************************************************************************************
         * Destructs a configuration plug-in. All ConfigurationPlugin that were assigned
         * (using #InsertPlugin) will be deleted.
         ******************************************************************************************/
        virtual            ~Configuration()   {}

        /** ****************************************************************************************
         * Sets the command line arguments for #CmdLine.
         *
         * \note This method should be called for instances of this class after construction.<br>
         *       In standard application scenarios, this method is invoked by method
         *       \ref aworx::lib::ALIB::Init   "ALIB::Init" for the static singleton #Default.
         *
         * <p>
         *
         * \note On the Windows platform, the Microsoft compiler provides the global variables
         *       <em>__argc</em> and <em>__argv</em> (respectively <em>__wargv</em> for wide
         *       character binaries. These variables a can be used if this method is invoked
         *       outside of the <em>main()</em> method.
         *
         * @param argc    Parameter usually taken from <em>standard C</em> \c main() method
         *                (the number of arguments in \p argv).
         *                Defaults to 0.
         * @param argv    Parameter usually taken from <em>standard C</em> \c main() method
         *                (pointer to a list of command line arguments).
         *                Defaults to nullptr.
         ******************************************************************************************/
        inline void         SetCommandLineArgs( int argc  =0,  char** argv  =nullptr )
        {
            if ( argc > 1 )
            {
                OWN(*this);
                CmdLine.SetArgs( argc, reinterpret_cast<void**>( argv ), false );
            }
        }

        /** ****************************************************************************************
         * Variant of method #SetCommandLineArgs, accepting command line arguments of
         * type \c wchar_t.
         *
         * @param argc    Parameter usually taken from <em>standard C</em> \c main() method
         *                (the number of arguments in \p argv).
         * @param argv    The command line parameters as \c wchar_t.
         ******************************************************************************************/
        inline void         SetCommandLineArgs( int  argc,    wchar_t **argv )
        {
            if ( argc > 1 )
            {
                OWN(*this);
                CmdLine.SetArgs( argc, reinterpret_cast<void**>( argv ),  true );
            }
        }


    // #############################################################################################
    // interface
    // #############################################################################################
    public:

        /** ****************************************************************************************
         * Adds the given plug-in to the list of plug-ins used to query configuration values.
         * Higher numbers for parameter priority, prioritize this plug-in against those with
         * lower values. Default values are provided with static constant fields
         * #PrioCmdLine, #PrioEnvironment and
         * #PrioIniFile.
         *
         * @param plugin   The plug-in to insert.
         * @param priority The priority of the plug-in.
         ******************************************************************************************/
        void    InsertPlugin( ConfigurationPlugin* plugin, int priority )
        {
            OWN(*this);
            insertPlugin( plugin, priority );
        }

        /** ****************************************************************************************
         * Remove the given plug-in from the list of plug-ins.
         * Responsibility for deletion of removed plug-ins moves to the remover.
         * Active (inserted) plug-ins get deleted by class' destructor.
         * @param plugin  The plug-in to be deleted.
         * @return \c true if the plug-in was removed, else \c false.
         ******************************************************************************************/
        ALIB_API
        bool    RemovePlugin( ConfigurationPlugin* plugin );

        /** ****************************************************************************************
         * This method fetches all values from #DefaultValues which are not present in the given
         * plug-in \p dest and stores them in.
         * This is useful to collect all generated default values and store them in a users'
         * configuration file. This way, the user can identify configurable options easily.
         *
         * \note
         *   Applications might want to copy only a portion of the default values to not
         *   blow up a users' configuration. To achieve this, a custom method to fetch selected
         *   values has to be implemented. In this respect, this method is a very simple
         *   default and its source might be used as a jump start.
         *
         * @param dest   The destination plug-in.
         * @return The number of variables fetched.
         ******************************************************************************************/
        ALIB_API
        int     FetchFromDefault( ConfigurationPlugin& dest );


        /** ****************************************************************************************
         * Utility method that checks if a given value represents boolean \b true.
         * Uses field #TrueValues. Comparisons are made case insensitive.
         *
         * @param value  The value to check
         *
         * @return   Returns \c true, if the value represents 'true', \c false if not.
         ******************************************************************************************/
        ALIB_API
        bool    IsTrue( const String&  value );

        /** ****************************************************************************************
         * Receives and optionally creates configuration variable.
         *
         * If the variable was not found and
         * \ref aworx::lib::config::Variable::DefaultValue "Variable::DefaultValue"
         * in \p variable is set, the method adds the value value to plug-in #DefaultValues
         * (respectively to the plug-in found at or below #PrioDefault).
         * For the conversion of the value, field
         * \ref aworx::lib::config::ConfigurationPlugin::StringConverter "ConfigurationPlugin::StringConverter"
         * of field #DefaultValues is used.
         *
         * @param variable       The variable to receive.
         *
         * @returns The priority of the configuration plug-in that provided the result.
         *          \c 0 if not found, #PrioDefault if either found or created in #DefaultValues.
         ******************************************************************************************/
        ALIB_API
        int     Load( Variable& variable );

        /** ****************************************************************************************
         * Writes the variable to the configuration.
         * In general, this is done by asking  each of our installed plug-ins - in the order of
         * their priority - to do so.
         * As soon as the first plug-in returns \c true, the variable is considered written and no
         * other plug-in is asked.
         * This way, the variable is stored by the plug-in with the highest priority.
         *
         * The maximum priority to start the loop with depending on field
         * \ref aworx::lib::config::Variable::Priority "Variable::Priority"
         * of the given \p variable. The rules are as follows:
         * - If the value is \c -1, which is the default value of new variables or ones that
         *   were freshly defined, then prior to storing the value, the variable is (tried to be)
         *   loaded first (without actually overwriting the values).
         *   After that, one of the next two rules apply.
         * - If the value is \c 0, which indicates that a previous load operation failed, the
         *   loop starts with #PrioDefault (and usually ends there, as standard configuration sets
         *   do not have plug-ins with lower priorities installed). In other words, newly created
         *   variables are stored in the in-memory plug-in #DefaultValues. This way, they are
         *   not written to external configuration files, unless the application explicitly moves
         *   such new default values to dedicated other plug-ins (e.g. on termination).
         * - If the value is greater than \c 0, the value is used as the start of the loop.
         *   This way, an already defined variable will be stored in the same plug-in as it was
         *   found (or one with a lower priority, if that plug-in does not provide writing
         *   capabilities).
         *
         * Consequently, as field
         * \ref aworx::lib::config::Variable::Priority "Variable::Priority" is public, the behavior
         * can be manipulated, by setting the field explicitly prior to invoking this method.
         * Some frequent use cases shall be named here:
         * - Setting the field to <c>Configuration::PrioProtected</c> allows to store the
         *   variable in plug-in #ProtectedValues. This way, the variable gets \e 'locked' in
         *   respect to external manipulation.
         * - Setting the field to <c>Configuration::PrioDefault</c> allows to store the
         *   variable in plug-in #DefaultValues. This way, the variable becomes just a default
         *   and does not overwrite other external values.
         * - Setting the field to a distinct priority value that names a user-specific configuration
         *   (vs. a system-wide configuration).
         * - Setting the field to <c>Configuration::PrioProtected - 1</c> allows to store the
         *   variable just in the plug-in with highest possible priority, for example
         *   a user specific configuration is preferred to a system wide configuration)
         * - A variable might be related to a second one. If the priority of the second one is
         *   known, that priority might be set to possibly have both variables stored in the same
         *   plug-in.
         *
         * The method returns the priority of the configuration plug-in that the value was written
         * to as well as storing this value in field
         * \ref aworx::lib::config::Variable::Priority "Variable::Priority".
         * If the result is \c 0, the variable was not written. This might only happen if
         * - either field #DefaultValues was modified (removed or exchanged with a different
         *   plug-in that does not write the value)
         * - or if field \p Priority of the variable was set below #PrioDefault and greater
         *   than \c 0.
         * - The detected (!) priority was #PrioProtected. In this case, obviously the application
         *   does not want to allow changes and writing the variable into a different plug-in
         *   has no effect. This way, such variables also do not appear in a users' configuration
         *   in the case that on program termination, new default values are copied there.
         *
         * Optional parameter \p externalizedValue allows to provide a string that is parsed
         * by the storing plug-in to reset the variables' values prior to writing.
         *
         * @param variable              The variable object.
         * @param externalizedValue     Optional externalized value string. If given, the variable
         *                              is set prior to writing.
         *
         * @returns The priority of the configuration plug-in that the value was written to.
         ******************************************************************************************/
        ALIB_API
        int   Store( Variable& variable, const String& externalizedValue= nullptr );

    // #############################################################################################
    // internal methods
    // #############################################################################################
    protected:
        /** ****************************************************************************************
         * Implementation of #InsertPlugin (not locked, used in the constructor).
         *
         * @param plugin   The plug-in to insert.
         * @param priority The priority of the plug-in.
         ******************************************************************************************/
        ALIB_API
        void    insertPlugin( ConfigurationPlugin* plugin, int priority );

        /** ****************************************************************************************
         * Implementation of get method. No locking is performed (has to be done before
         * invoking this method)
         *
         * @param variable    The variable to get.
         * @param substitute  If \c false, automatic variable substitutions are suppressed.
         *
         * @return Zero if the variable was not found. Otherwise it returns the priority of the
         *         (first) plug-in that contained the variable.
         ******************************************************************************************/
        ALIB_API
        int     loadImpl( Variable& variable, bool substitute );

}; // class Configuration

}} // namespace lib::config

/** Type alias name in namespace #aworx. */
using     Configuration=       aworx::lib::config::Configuration;

/** Type alias name in namespace #aworx. */
using     Variable= aworx::lib::config::Variable;

}  // namespace aworx

#endif // HPP_ALIB_CONFIG_CONFIGURATION
