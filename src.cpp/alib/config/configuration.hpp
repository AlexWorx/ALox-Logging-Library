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
#if defined(HPP_COM_ALIB_TEST_INCLUDES) && defined(HPP_ALIB_CONFIG_CONFIGURATION)
    #error "Header already included"
#endif

// then, set include guard
#ifndef HPP_ALIB_CONFIG_CONFIGURATION
#if !defined( IS_DOXYGEN_PARSER)
#define HPP_ALIB_CONFIG_CONFIGURATION 1
#endif

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

#if !defined(HPP_ALIB_CONFIG_PLUGINS)
    #include "alib/config/plugins.hpp"
#endif
#if !defined(HPP_ALIB_CONFIG_INMEMORY_PLUGIN)
    #include "alib/config/inmemoryplugin.hpp"
#endif

#if !defined(HPP_ALIB_STRINGS_TOKENIZER)
    #include "alib/strings/tokenizer.hpp"
#endif



#include <vector>

namespace aworx {
namespace           lib {

/** ************************************************************************************************
\note
  It may be helpful to read this namespace documentation and understand the concepts - even if you
  are not planning to use configuration variables in your own code.
  The reason is that with the knowledge of the principals described here, it is possible to influence
  the behavior of 3rd party code (code of other team members or ALib enabled libraries
  like for example <b>ALox Logging Library</b>).

# 1. Introduction #

This package provides tools to read and write configuration data using different mechanisms.
In short, the features are:
- A central class to retrieve external configuration data from various sources.
- Abstract plug-in class to read and optionally store a certain type of external source.
- Predefined plug-ins for command line parameters, environment variables and simple INI files.
- The possibility to set default values 'in code' (if no external plug-in finds a value)
  and doing this "out of scope" which means independent from the code that finally uses a variable.
- The possibility to protect variables 'in code' from being modified (to block modification
  of variables exposed by 3rd party code).
- Automatic resolving of nested variables: Define a value once and pass it as a
  variable to other variables ("variable substitution").
- With the combination of variable substitution and protection of variable values, it is possible
  to hide, rename or even redefine the syntax and behavior of variables exposed by third party code
  (e.g. libraries).

<b>Class %Configuration and Plug-ins:</b><br>

The plug-ins, derived from abstract class
\ref aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin"
are plugged into an object of type
\ref aworx::lib::config::Configuration "Configuration" and are responsible for reading (and
optionally writing) variables from dedicated sources.

Class \b %Configuration offers an interface to retrieve and store configuration variables using
the plug-ins. The plug-ins are attached to the \b %Configuration instance along with a unique priority.
Values are retrieved and stored by looping through the plug-ins sorted by priority.
As soon as one plug-in confirms to have found (or stored) the variable, the loop ends.
This way, plug-ins may "overrule" each other in respect to retrieving configuration data.

Class \ref aworx::lib::ALIB "ALIB" creates a static singleton of this class for public
access and this singleton is usually all that is needed.


<b>Naming %Configuration Variables</b>:<br>

%Configuration variables are addressed by two strings: The \b category and the \b name. In the case of
INI files, the category is translated to the section and the name to variables within the
section. Other plug-ins, for example
\ref aworx::lib::config::CommandLinePlugin "CommandLinePlugin" or
\ref aworx::lib::config::EnvironmentPlugin "EnvironmentPlugin", are prepending the category
name to the variable name separated by an underscore character \c '_'.
For example, a variable in category \c "ALIB" named \c "WAIT_FOR_KEY_PRESS", in an
INI file would be stated like this:

        [ALIB]
        WAIT_FOR_KEY_PRESS= yes

To define the same variable and value on the command-line, the parameter needs to be:

        --ALIB_WAIT_FOR_KEY_PRESS=yes

The anonymous, empty category is allowed. For convenience, with variables of this category,
no underscore is prepended by the plug-ins. The little drawback of this is, that variables
in the anonymous category that contain an underscore character, for some plug-ins can get
ambiguous. For example, variable \c MY_VARIABLE in the anonymous category, on the command line
would be uniquely addressed by:

        --MY_VAR=my value

In an INI file, two ways of specifying the variable are possible (and therefore ambiguous). In the anonymous section:


        MY_VAR      =       my value

or, in section \c MY:

        [MY]
        VAR         =       my value

# 2. Command-Line parameters, Environment Variables and INI files #

Three different standard plug-ins that collect external configuration variables are provided
with ALib already:
- Class \ref aworx::lib::config::CommandLinePlugin "CommandLinePlugin":<br>
  Reads parameter values of the form -[-]CategoryName_VariableName=value from the command line.
- Class \ref aworx::lib::config::EnvironmentPlugin "EnvironmentPlugin":<br>
  Reads system defined environment variables
  (see [Wikipedia](https://en.wikipedia.org/wiki/Environment_variable) of the form
  <c>CategoryName_VariableName=value</c>.
- Class \ref aworx::lib::config::IniFile "IniFile":<br>
  Reads and writes quite standard INI files
  (see [Wikipedia](https://en.wikipedia.org/wiki/INI_file).
<p>

The proposed priorities to be used when attaching the plug-ins to the \b %Configuration object,
are given in static fields:

 - \ref aworx::lib::config::Configuration::PrioCmdLine      "Configuration::PrioCmdLine" (400)
 - \ref aworx::lib::config::Configuration::PrioEnvironment  "Configuration::PrioEnvironment" (300)
 - \ref aworx::lib::config::Configuration::PrioIniFile      "Configuration::PrioIniFile" (200)

With these default priorities set, whatever is stored in an INI file,
can be overwritten by setting an environment variable. Both settings can in turn be
overwritten by specifying a corresponding command line parameter when launching the process!

# 3. Default Variables #

In addition to the three plug-ins described above, ALib implements a fourth one,
class \ref aworx::lib::config::InMemoryPlugin "InMemoryPlugin". As the name indicates, this
class keeps configuration variables in memory. The special thing about it is that it does not
read any external data source! The reason for having it, is twofold. The first use case
are <em>Default variables</em>.<br>

An instance is plugged into class \b %Configuration with a priority of
- \ref aworx::lib::config::Configuration::PrioDefault "Configuration::PrioDefault" (100),

this plug-in serves as a storage for default values.
The only way to set these default values is \e programatically, which means "with program code".

The advantages of having such default variables are:
- Code that checks whether a variable is set can be omitted (there is always a value found).
- Code that sets default values if no variable is set can be omitted.
- All default settings can be made in one place (bootstrap section of a process or library)


# 4. Protecting Variables #

Class \ref aworx::lib::config::InMemoryPlugin "InMemoryPlugin" is by default used a second
time by plugging an instance into class \b %Configuration with a priority of
- \ref aworx::lib::config::Configuration::PrioProtected "Configuration::PrioProtected" (max integer).

When setting a variable within this plug-in, no other plug-in can <em>'overrule'</em> this value.
This way, it is possible to protect values against external modification.

\note
    One might think: "If I do not want to allow external modification, I rather hard-code
    everything". This of-course is true for code under control. However, for 3rd party
    code using ALib, this offers an easy way to disallow users of your software (which incorporates
    that 3rd party code) to configure things that you do not want to be configurable.

# 5. Using class %Configuration #

In normal use cases, there is no need to create an instance of class Configuration, as class %ALib
provides a public static singleton with field
\ref aworx::lib::ALIB::Config "ALIB::Config".
The command line parameters (optionally) provided with
\ref aworx::lib::ALIB::Init "ALIB::Init" are passed to the command-line plug-in of this
singleton.

Class %Configuration in the constructor sets up four plug-ins automatically: One for command-line,
one for environment variables and two in-memory plug-ins used for default values and protected values.
Each plug-in is publicly addressable (with fields
\ref aworx::lib::config::Configuration::CmdLine           "CmdLine",
\ref aworx::lib::config::Configuration::Environment       "Environment",
\ref aworx::lib::config::Configuration::DefaultValues     "DefaultValues" and
\ref aworx::lib::config::Configuration::ProtectedValues   "ProtectedValues").

If an application wants to suppress the use of one of the plug-ins, the plug-ins can be removed
using method \ref aworx::lib::config::Configuration::RemovePlugin "RemovePlugin".<br>
On the other hand, a plug-in of type
\ref aworx::lib::config::IniFile "IniFile" may be attached on bootstrap of a process using
\ref aworx::lib::config::Configuration::PrioIniFile "Configuration::PrioIniFile" (200).

In addition (or alternatively), custom plug-ins may be written and installed using arbitrary
priorities. Especially, provided class \b %IniFile is designed for simplicity and smaller applications.
Instead of using it \b %IniFile, it is recommended to use application/platform
specific mechanisms for writing configuration data. In this case, write your own plug-in
to grant ALib and other libraries which rely on ALib, access to your applications's configuration
data. Again, ALib here follows its design principle to be non intrusive: The plug-in concept
allows users of ALib (more important:  users of ALib enabled libraries) to expose any external
configuration source to these libraries.
This way, the users can stick to his/her preferred way of implementation.

\anchor cpp_alib_namespace_config_substitution
# 6. %Variable Substitution #

Method \ref aworx::lib::config::Configuration::Load  "Configuration::Load" by default substitutes
references to other configuration variables found in the value of the requested variable.

For example, if two variables are defined as follows:

        MYCAT_RESULT= 42
        MYCAT_MYVARIABLE= The result is $MYCAT_RESULT

then, with the retrieval of variable \c MYCAT_MYVARIABLE, variable \c MYCAT_RESULT is read and the
substring "$MYCAT_RESULT" is substituted by "42".<br>

Substitutions are performed repeatedly until all variables are resolved. Therefore, nested
substitutions may be defined as well. To avoid an endless loop in case of circular dependencies,
a simple threshold applies: A maximum of 50 replacements are done.

The dollar sign \c '$' used to recognize variables is the default and can be modified. It is
also possible to specify a prefix and a suffix for the identification of substitutable variables
in other variables' values. For example, the syntax can be adjusted to

        MYCAT_MYVARIABLE= The result is %{MYCAT_RESULT}

See documentation of fields
\ref aworx::lib::config::Configuration::SubstitutionVariableStart        "SubstitutionVariableStart",
\ref aworx::lib::config::Configuration::SubstitutionVariableEnd          "SubstitutionVariableEnd" and
\ref aworx::lib::config::Configuration::SubstitutionVariableDelimiters   "SubstitutionVariableDelimiters"
for more information.

When parsing a variables' category and name, method
\ref aworx::lib::config::Configuration::Load  "Configuration::Load" searches for an underscore
character \c '_'. The first underscore found serves as a delimiter of category from the name.
If no underscore character is found, the category is left empty (anonymous category) and the name is set to what
is given as a variable name.
\note
    This implies that variables which have no category but have an underscore in their name, need
    to be specified with a leading underscore. For example:

            TEXT= Welcome to $_HOME_LOCATION
\note
    refers to a variable name \c HOME_LOCATION in the anonymous category \c "".<br>
    For clarification:
    - This is not needed (but also no fault) for variables that do not contain an underscore in their name
    - This must not be done if a variable belongs to a named category.


# 7. Loading and Storing %Variables #
Values of variables are loaded and received using instances of class Variable. Instances of this class
can be passed to the interface of class Configuration or directly to specific
\ref aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin" objects.
However, the simplest way of loading and storing variables is to use the interface methods of class
\b %Variable itself. These methods are considered "available for convenience", hence all they do is
to invoke methods of class \b %Configuration passing themselves as parameters. The methods are using
the public static singleton of class \b %Configuration found in field
\ref aworx::lib::ALIB::Config "ALIB::Config". For most use cases this all that is needed!

Simple access methods allow to read or set the values of a variable.

By consequently using optional struct VariableDefinition for defining all variables of an application or library,
all attributes of variables can be maintained in one place. This includes categories, names, comments,
value delimiters and default values of variables.
Class \b %Variable accepts instances of \b %VariableDefinition in the constructor as well as in overloaded
method \ref aworx::lib::config::Variable::Define "Variable::Define".

# 8. In- and Externalizing %Variable values #
%Variable values provided via command line parameters, environment variables or textual configuration
files need to be converted when loading and storing them. This has two reasons:
- Certain characters of variables have to be "escaped", e.g. \c '\\n' or \c '\\t' within strings
- Multiple values defined in variables need to be separated when storing  - and parsed back when loading
  a variable.

For this task, class
\ref aworx::lib::config::XTernalizer "XTernalizer" is used. Each
\ref aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin" owns an instance of this
class (which is exchangeable). Conversion is done internally and there is no need to interface
with this class directly when using variables.
A huge benefit of this API design is that variable values look the same in an INI-file as
when passed as a command line parameter.

But it is important to understand that value parameters provided with interface methods to store
variables accept "externalized" strings only. In simple cases this is not relevant. But if a
variable contains multiple values or special characters, it has to be understood that
'internalization' of the value takes place.

Normal, internal string values need to be added to the variable in code prior to invoking
a store method. If an externalized string is provided with the store methods, then previously
added variable values are cleared!
***************************************************************************************************/
namespace                   config {



// #################################################################################################
// class Configuration
// #################################################################################################

/** ************************************************************************************************
 * This class primarily is used via the public static singleton instance of it, found in
 * \ref aworx::lib::ALIB::Config "ALIB::Config".
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
        static constexpr  int               PrioProtected

                                      #if defined( _MSC_VER )
                                                                                           = MAXINT;
                                      #else
                                                                  = std::numeric_limits<int>::max();
                                      #endif


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
         *       \ref aworx::lib::ALIB::Init   "ALIB::Init" for the static singleton found in
         *       \ref aworx::lib::ALIB::Config "ALIB::Config".
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
                CmdLine.SetArgs( argc, (void**) argv, false );
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
                CmdLine.SetArgs( argc, (void**) argv, true );
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
         *   values has to be implemened. In this respect, this method is a very simple
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
