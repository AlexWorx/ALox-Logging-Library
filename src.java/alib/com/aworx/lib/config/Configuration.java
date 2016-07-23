// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

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
\ref com::aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin"
are plugged into an object of type
\ref com::aworx::lib::config::Configuration "Configuration" and are responsible for reading (and
optionally writing) variables from dedicated sources.

Class \b %Configuration offers an interface to retrieve and store configuration variables using
the plug-ins. The plug-ins are attached to the \b %Configuration instance along with a unique priority.
Values are retrieved and stored by looping through the plug-ins sorted by priority.
As soon as one plug-in confirms to have found (or stored) the variable, the loop ends.
This way, plug-ins may "overrule" each other in respect to retrieving configuration data.

Class \ref com::aworx::lib::ALIB "ALIB" creates a static singleton of this class for public
access and this singleton is usually all that is needed.


<b>Naming %Configuration Variables:</b><br>

%Configuration variables are addressed by two strings: The \b category and the \b name. In the case of
INI files, the category is translated to the section and the name to variables within the
section. Other plug-ins, for example
\ref com::aworx::lib::config::CommandLinePlugin "CommandLinePlugin" or
\ref com::aworx::lib::config::EnvironmentPlugin "EnvironmentPlugin", are prepending the category
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
- Class \ref com::aworx::lib::config::CommandLinePlugin "CommandLinePlugin":<br>
  Reads parameter values of the form -[-]CategoryName_VariableName=value from the command line.
- Class \ref com::aworx::lib::config::EnvironmentPlugin "EnvironmentPlugin":<br>
  Reads system defined environment variables
  (see [Wikipedia](https://en.wikipedia.org/wiki/Environment_variable) of the form
  <c>CategoryName_VariableName=value</c>.
- Class \ref com::aworx::lib::config::IniFile "IniFile":<br>
  Reads and writes quite standard INI files
  (see [Wikipedia](https://en.wikipedia.org/wiki/INI_file).
<p>

The proposed priorities to be used when attaching the plug-ins to the \b %Configuration object,
are given in static fields:

 - \ref com::aworx::lib::config::Configuration::PRIO_CMD_LINE "Configuration.PRIO_CMD_LINE" (400)
 - \ref com::aworx::lib::config::Configuration::PRIO_ENVIRONMENT "Configuration.PRIO_ENVIRONMENT" (300)
 - \ref com::aworx::lib::config::Configuration::PRIO_INI_FILE "Configuration.PRIO_INI_FILE" (200)

With these default priorities set, whatever is stored in an INI file,
can be overwritten by setting an environment variable. Both settings can in turn be
overwritten by specifying a corresponding command line parameter when launching the process!

# 3. Default Variables #

In addition to the three plug-ins described above, ALib implements a fourth one,
class \ref com::aworx::lib::config::InMemoryPlugin "InMemoryPlugin". As the name indicates, this
class keeps configuration variables in memory. The special thing about it is that it does not
read any external data source! The reason for having it, is twofold. The first use case
are <em>Default variables</em>.<br>

An instance is plugged into class \b %Configuration with a priority of
- \ref com::aworx::lib::config::Configuration::PRIO_DEFAULT "Configuration.PRIO_DEFAULT" (100),

this plug-in serves as a storage for default values.
The only way to set these default values is \e programatically, which means "with program code".

The advantages of having such default variables are:
- Code that checks whether a variable is set can be omitted (there is always a value found).
- Code that sets default values if no variable is set can be omitted.
- All default settings can be made in one place (bootstrap section of a process or library)


# 4. Protecting Variables #

Class \ref com::aworx::lib::config::InMemoryPlugin "InMemoryPlugin" is by default used a second
time by plugging an instance into class \b %Configuration with a priority of
- \ref com::aworx::lib::config::Configuration::PRIO_PROTECTED "Configuration.PRIO_PROTECTED" (max integer).

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
\ref com::aworx::lib::ALIB::config "ALIB.config".
The command line parameters (optionally) provided with
\ref com::aworx::lib::ALIB::init "ALIB.init" are passed to the command-line plug-in of this
singleton.

Class %Configuration in the constructor sets up four plug-ins automatically: One for command-line,
one for environment variables and two in-memory plug-ins used for default values and protected values.
Each plug-in is publicly addressable (with fields
\ref com::aworx::lib::config::Configuration::cmdLine          "cmdLine",
\ref com::aworx::lib::config::Configuration::environment      "environment",
\ref com::aworx::lib::config::Configuration::defaultValues    "defaultValues" and
\ref com::aworx::lib::config::Configuration::protectedValues  "protectedValues").

If an application wants to suppress the use of one of the plug-ins, the plug-ins can be removed
using method \ref com::aworx::lib::config::Configuration::removePlugin "removePlugin".<br>
On the other hand, a plug-in of type
\ref com::aworx::lib::config::IniFile "IniFile" may be attached on bootstrap of a process using
\ref com::aworx::lib::config::Configuration::PRIO_INI_FILE "Configuration.PRIO_INI_FILE" (200).

In addition (or alternatively), custom plug-ins may be written and installed using arbitrary
priorities. Especially, provided class \b %IniFile is designed for simplicity and smaller applications.
Instead of using it \b %IniFile, it is recommended to use application/platform
specific mechanisms for writing configuration data. In this case, write your own plug-in
to grant ALib and other libraries which rely on ALib, access to your applications's configuration
data. Again, ALib here follows its design principle to be non intrusive: The plug-in concept
allows users of ALib (more important:  users of ALib enabled libraries) to expose any external
configuration source to these libraries.
This way, the users can stick to his/her preferred way of implementation.

\anchor java_alib_namespace_config_substitution
# 6. %Variable Substitution #

Method \ref com::aworx::lib::config::Configuration::load  "Configuration.load" by default substitutes
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
\ref com::aworx::lib::config::Configuration::substitutionVariableStart       "substitutionVariableStart",
\ref com::aworx::lib::config::Configuration::substitutionVariableEnd         "substitutionVariableEnd" and
\ref com::aworx::lib::config::Configuration::substitutionVariableDelimiters  "substitutionVariableDelimiters"
for more information.

When parsing a variables' category and name, method
\ref com::aworx::lib::config::Configuration::load  "configuration.load" searches for an underscore
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
\ref com::aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin" objects.
However, the simplest way of loading and storing variables is to use the interface methods of class
\b %Variable itself. These methods are considered "available for convenience", hence all they do is
to invoke methods of class \b %Configuration passing themselves as parameters. The methods are using
the public static singleton of class \b %Configuration found in field
\ref com::aworx::lib::ALIB::config "ALIB.config". For most use cases this all that is needed!

Simple access methods allow to read or set the values of a variable.

By consequently using optional class VariableDefinition for defining all variables of an application or library,
all attributes of variables can be maintained in one place. This includes categories, names, comments,
value delimiters and default values of variables.
Class \b %Variable accepts instances of \b %VariableDefinition in the constructor as well as in overloaded
method \ref com::aworx::lib::config::Variable.define "Variable.define".


# 8. In- and Externalizing %Variable values #
%Variable values provided via command line parameters, environment variables or textual configuration
files need to be converted when loading and storing them. This has two reasons:
- Certain characters of variables have to be "escaped", e.g. \c '\\n' or \c '\\t' within strings
- Multiple values defined in variables need to be separated when storing  - and parsed back when loading
  a variable.

For this task, class
\ref com::aworx::lib::config::XTernalizer "XTernalizer" is used. Each
\ref com::aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin" owns an instance of this
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
package com.aworx.lib.config;

import java.util.ArrayList;

import com.aworx.lib.ALIB;
import com.aworx.lib.enums.Case;
import com.aworx.lib.enums.Inclusion;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.NumberFormat;
import com.aworx.lib.strings.Substring;


/** ************************************************************************************************
 * This class primarily is used via the public static singleton instance of it, found in
 * \ref com::aworx::lib::ALIB::config "ALIB.config".
 * It holds a list of objects of type
 * \ref com::aworx::lib::config::ConfigurationPlugin "ConfigurationPlugin",
 * sorted by their priority and provides a
 * single user interface to query configuration data from those.
 *
 * Interface methods are implemented <em>synchronized</em>.
 *
 * By default, all category and variable names are case insensitive. This is at least true for the
 * default plug-ins delivered with ALib.
 *
 * Variables by default can contain other variables, which are recursively substituted
 * by this method. For more information about the (adjustable) syntax, see
 * \ref java_alib_namespace_config_substitution "Variable Substitution".
 *
 * See documentation of namespace #com::aworx::lib::config for more information on ALib
 * external configuration variables.
 **************************************************************************************************/
public class Configuration
{
    // #############################################################################################
    // internal fields
    // #############################################################################################

        /** An element of the list of plug-ins with their priority */
        protected class PluginAndPrio
        {
            /** The priority that was defined when the plug-in was added. */
            public int                          prio;

            /** The plug-in. */
            public ConfigurationPlugin          plugin;
        }

        /** The plug-ins we have attached */
        protected  ArrayList<PluginAndPrio>     plugins            = new ArrayList<PluginAndPrio>();

        /** A temporary object used for conversion */
        protected  AString                      tmpConversion                       = new AString();

        /** A temporary object used with variable substitution */
        protected  Substring                    tmpReplVarAll                     = new Substring();

        /** A temporary object used with variable substitution */
        protected  Substring                    tmpReplVarName                    = new Substring();

        /** A temporary object used with variable substitution */
        protected  Substring                    tmpReplVarCategory                = new Substring();

    // #############################################################################################
    // public fields
    // #############################################################################################
        /**
         * Values considered to indicate "true". Defaults to
         * { "1", "true", "t", "yes", "y", "on", "ok" }.
         * See methods #isTrue.
         *
         * Application specific values (e.g. localization languages) might be added by publicly
         * accessing this field and adding new values (or removing existing).
         */
        public  ArrayList<AString>              trueValues;

        /** Number format definition used to read and write int and float values.  */
        public  NumberFormat                    numberFormat                   = new NumberFormat();

        /**
         * The start string to identify substitution variables.
         * Defaults to single character \c '$'. If a string is set, i.e. \c "${", then field
         * #substitutionVariableEnd may be set accordingly, i.e. \c "}"
         */
        public  AString                         substitutionVariableStart        = new AString("$");

        /**
         * The end of a substitution variables.
         * If this field is set, then field sSubstitutionVariableDelimiters is ignored. If this field
         * is null (the default) or empty, it is ignored and characters in field
         * #substitutionVariableDelimiters are used to identify the end of the variable.
         */
        public  AString                         substitutionVariableEnd             = new AString();

        /**
         * The delimiters used to identify the end of a substitutable variable.
         * If field #substitutionVariableEnd is not empty, this field is ignored. Otherwise, all
         * characters defined in this string are used to identify the end of a substitution
         * variable.
         */
        public  char[]                          substitutionVariableDelimiters
        = { ' ','$','@',',','.',';',':','\"','\'','+','-','*','/','\\',
            '§','%','&','(',')','[',']','{','}','<','>','=','?','\'','`','~','#' };

        /** The in-memory configuration plug-in that stores default values. */
        public InMemoryPlugin                   defaultValues                = new InMemoryPlugin();

        /** The in-memory configuration plug-in that stores values that are not changeable
            by external configuration data. */
        public InMemoryPlugin                   protectedValues              = new InMemoryPlugin();

        /** The plug-in for command line parameters.      */
        public CommandLinePlugin                cmdLine                   = new CommandLinePlugin();

        /** The plug-in for the evaluation of system environment variables. */
        public EnvironmentPlugin                environment               = new EnvironmentPlugin();

        /** Constant providing the highest possible priority. This is used with #protectedValues */
        public static final  int                PRIO_PROTECTED                  = Integer.MAX_VALUE;

        /** Constant providing default priority for \b %IniFile (or similar) plug-in. */
        public static final  int                PRIO_CMD_LINE                                 = 400;

        /** Constant providing default priority for environment variables plug-in. */
        public static final  int                PRIO_ENVIRONMENT                              = 300;

        /** Constant providing default priority for command-line parameters plug-in. */
        public static final  int                PRIO_INI_FILE                                 = 200;

        /** Constant providing a low priority. This is used with #defaultValues */
        public static final  int                PRIO_DEFAULT                                  = 100;

        /**
         * Constant providing a priority which is even lower than default. This priority is
         * not used by any standard plug-ins and currently not even anywhere in core ALib.
         * The rational to provide it is for third party libraries that may use this value
         * in cases where values are estimated or detected. A user of the library may then
         * overwrite such auto-detection by setting a default value in the configuration.
         */
        public static final int                 PRIO_AUTO_DETECT                               = 50;



    // #############################################################################################
    // Initialization
    // #############################################################################################
        /** ****************************************************************************************
         * Constructs a Configuration. Registers the initial plug-ins
         * #defaultValues,
         * #cmdLine,
         * #environment and
         * #protectedValues.
         ******************************************************************************************/
        public Configuration()
        {
            // set default true values
            trueValues=     new ArrayList<AString>();
            trueValues.add( new AString( "1"    ) );
            trueValues.add( new AString( "true" ) );
            trueValues.add( new AString( "t"    ) );
            trueValues.add( new AString( "yes"  ) );
            trueValues.add( new AString( "on"   ) );
            trueValues.add( new AString( "ok"   ) );

            // insert plug-ins
            insertPlugin( defaultValues,   Configuration.PRIO_DEFAULT   );
            insertPlugin( environment,           Configuration.PRIO_ENVIRONMENT  );
            insertPlugin( cmdLine,       Configuration.PRIO_CMD_LINE  );
            insertPlugin( protectedValues, Configuration.PRIO_PROTECTED );
        }

        /** ****************************************************************************************
         * Sets the command line arguments for #cmdLine.
         *
         * \note This method should be called for instances of this class after construction.<br>
         *       In standard application scenarios, this method is invoked by method
         *       \ref com::aworx::lib::ALIB::init   "ALIB.init" for the static singleton found in
         *       \ref com::aworx::lib::ALIB::config "ALIB.config".
         *
         * @param args    Parameters taken from <em>standard Java</em> method \c main()
         *                (the list of command line arguments). Accepts \c null to ignore
         *                command line parameters.
         ******************************************************************************************/
        synchronized
        public void  setCommandLineArgs( String[] args )
        {
            if( args != null && args.length > 0 )
                cmdLine.setArgs( args );
        }

    // #############################################################################################
    // interface
    // #############################################################################################
        /** ****************************************************************************************
         * Adds the given plug-in to the list of plug-ins used to query configuration values.
         * Higher numbers for parameter priority, prioritize this plug-in against those with
         * lower values. Default values are provided with static constant fields
         * #PRIO_CMD_LINE, #PRIO_ENVIRONMENT and
         * #PRIO_INI_FILE.
         * @param plugin   The plug-in to insert.
         * @param priority The priority of the plug-in.
         ******************************************************************************************/
        synchronized
        public void insertPlugin( ConfigurationPlugin plugin, int priority )
        {
            int i;
            for ( i= 0; i < plugins.size(); i++ )
            {
                ALIB.ASSERT_ERROR( plugins.get(i).prio != priority,
                    "Configuration.InsertPlugin(): Plug-in with same priority exists" );
                if ( plugins.get( i ).prio < priority )
                    break;
            }

            PluginAndPrio pap=  new PluginAndPrio();
            pap.plugin=         plugin;
            pap.prio=           priority;
            plugins.add( i, pap );
        }

        /** ****************************************************************************************
         * Remove the given plug-in from the list of plug-ins.
         * Responsibility for deletion of removed plug-ins moves to the remover.
         * Active (inserted) plug-ins get deleted by class' destructor.
         * @param plugin  The plug-in to be deleted.
         * @return true if the plug-in was removed, else false.
         ******************************************************************************************/
        synchronized
        public boolean removePlugin( ConfigurationPlugin plugin )
        {
            for ( int i= 0; i < plugins.size(); i++ )
            {
                if ( plugins.get( i ).plugin == plugin )
                {
                    plugins.remove( i );
                    return true;
                }
            }

            ALIB.WARNING( "No Plug-in was removed " );
            return false;
        }

        /** ****************************************************************************************
         * This method fetches all values from #defaultValues which are not present in the given
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
        synchronized
        public int fetchFromDefault( ConfigurationPlugin dest)
        {
            int cntCopied= 0;
            Variable variable= new Variable();
            for( int sNo= 0; sNo < defaultValues.sections.size() ; sNo++ )
            {
                InMemoryPlugin.Section section= defaultValues.sections.get( sNo );
                for( int vNo= 0; vNo < section.entries.size() ; vNo++ )
                {
                    InMemoryPlugin.Entry entry= section.entries.get( vNo );
                    if( !dest.load( variable.define( section.name, entry.name), true ) )
                    {
                        defaultValues .load( variable );
                        dest.store( variable );
                        cntCopied++;
                    }
                }
            }

            return  cntCopied;

        }

        /** ****************************************************************************************
         * Utility method that checks if a given value represents boolean \b true.
         * Uses field #trueValues. Comparisons are made case insensitive.
         *
         * @param value  The value to check
         *
         * @return   Returns \c true, if the value represents 'true', \c false if not.
         ******************************************************************************************/
        public boolean  isTrue( AString value )
        {
           for( AString s : trueValues )
               if ( value.equals( s, Case.IGNORE ) )
                   return true;

            return false;
        }

        /** ****************************************************************************************
         * Receives and optionally creates configuration variable.
         *
         * If the variable was not found and
         * \ref com::aworx::lib::config::Variable::defaultValue "Variable.defaultValue"
         * in \p variable is set, the method adds the value value to plug-in #defaultValues
         * (respectively to the plug-in found at or below #PRIO_DEFAULT).
         * For the conversion of the value, field
         * \ref com::aworx::lib::config::ConfigurationPlugin::stringConverter "ConfigurationPlugin.stringConverter"
         * of field #defaultValues is used.
         *
         * @param variable       The variable to receive.
         *
         * @returns The priority of the configuration plug-in that provided the result.
         *          \c 0 if not found, #PRIO_DEFAULT if either found or created in #defaultValues.
         ******************************************************************************************/
        synchronized
        public int  load( Variable  variable )
        {
            variable.config=    this;
            variable.priority=  loadImpl( variable, true );

            if ( variable.priority == 0 && variable.defaultValue.isNotNull() )
                store( variable, variable.defaultValue );

            return variable.priority;
        }

        /** ****************************************************************************************
         * Writes the variable to the configuration.
         * In general, this is done by asking  each of our installed plug-ins - in the order of
         * their priority - to do so.
         * As soon as the first plug-in returns \c true, the variable is considered written and no
         * other plug-in is asked.
         * This way, the variable is stored by the plug-in with the highest priority.
         *
         * The maximum priority to start the loop with depending on field
         * \ref com::aworx::lib::config::Variable::priority "Variable.priority"
         * of the given \p variable. The rules are as follows:
         * - If the value is \c -1, which is the default value of new variables or ones that
         *   were freshly defined, then prior to storing the value, the variable is (tried to be)
         *   loaded first (without actually overwriting the values).
         *   After that, one of the next two rules apply.
         * - If the value is \c 0, which indicates that a previous load operation failed, the
         *   loop starts with #PRIO_DEFAULT (and usually ends there, as standard configuration sets
         *   do not have plug-ins with lower priorities installed). In other words, newly created
         *   variables are stored in the in-memory plug-in #defaultValues. This way, they are
         *   not written to external configuration files, unless the application explicitly moves
         *   such new default values to dedicated other plug-ins (e.g. on termination).
         * - If the value is greater than \c 0, the value is used as the start of the loop.
         *   This way, an already defined variable will be stored in the same plug-in as it was
         *   found (or one with a lower priority, if that plug-in does not provide writing
         *   capabilities).
         *
         * Consequently, as field
         * \ref com::aworx::lib::config::Variable::priority "Variable.priority" is public, the behavior
         * can be manipulated, by setting the field explicitly prior to invoking this method.
         * Some frequent use cases shall be named here:
         * - Setting the field to #PRIO_PROTECTED allows to store the
         *   variable in plug-in #protectedValues. This way, the variable gets \e 'locked' in
         *   respect to external manipulation.
         * - Setting the field to #PRIO_DEFAULT allows to store the
         *   variable in plug-in #defaultValues. This way, the variable becomes just a default
         *   and does not overwrite other external values.
         * - Setting the field to a distinct priority value that names a user-specific configuration
         *   (vs. a system-wide configuration).
         * - Setting the field to #PRIO_PROTECTED <c>- 1</c> allows to store the
         *   variable just in the plug-in with highest possible priority, for example
         *   a user specific configuration is preferred to a system wide configuration)
         * - A variable might be related to a second one. If the priority of the second one is
         *   known, that priority might be set to possibly have both variables stored in the same
         *   plug-in.
         *
         * The method returns the priority of the configuration plug-in that the value was written
         * to as well as storing this value in field
         * \ref com::aworx::lib::config::Variable::priority "Variable.priority".
         * If the result is \c 0, the variable was not written. This might only happen if
         * - either field #defaultValues was modified (removed or exchanged with a different
         *   plug-in that does not write the value)
         * - or if field \p Priority of the variable was set below #PRIO_DEFAULT and greater
         *   than \c 0.
         * - The detected (!) priority was #PRIO_PROTECTED. In this case, obviously the application
         *   does not want to allow changes and writing the variable into a different plug-in
         *   has no effect. This way, such variables also do not appear in a users' configuration
         *   in the case that on program termination, new default values are copied there.
         *
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
        synchronized
        public int   store( Variable variable, Object externalizedValue )
        {
            // checks
            if(     externalizedValue == null
                || ( externalizedValue instanceof AString && ((AString) externalizedValue).isNull() ) )
            {
                if ( variable.name.isEmpty())
                {
                    ALIB.ERROR( "Trying to store an undefined variable."  );
                    return 0;
                }

                if ( variable.size() > 1 && variable.delim == '\0' )
                {
                    ALIB.ERROR(   "Trying to store variable \"" + variable.fullname
                                + "\" which has multiple values set but no delimiter defined."  );
                    return 0;
                }
            }

            variable.config= this;

            // detect?
            boolean detected= variable.priority < 0;
            if ( detected )
            {
                variable.priority= 0;
                for ( PluginAndPrio ppp : plugins )
                    if ( ppp.plugin.load( variable, true ) )
                    {
                        variable.priority= ppp.prio;
                        break;
                    }
            }

            // new variables go to default
            if ( variable.priority == 0 )
                variable.priority= Configuration.PRIO_DEFAULT;

            // we do not store if detected priority is protected
            else if( detected && variable.priority == Configuration.PRIO_PROTECTED )
                return (variable.priority= 0);


            // store
            for ( PluginAndPrio ppp : plugins )
                if (    ppp.prio <= variable.priority
                     && ppp.plugin.store( variable, externalizedValue ) )
                    {
                        return (variable.priority= ppp.prio);
                    }

            return (variable.priority= 0);
        }

        /** ****************************************************************************************
         * Overloaded version that provides default value \c null for parameter
         * \p externalizedValue.
         *
         * @param variable              The variable object.
         *
         * @returns The priority of the configuration plug-in that the value was written to.
         ******************************************************************************************/
        public int   store( Variable variable )
        {
            return store( variable, null );
        }

    // #############################################################################################
    // internal methods
    // #############################################################################################
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
        public int loadImpl( Variable variable, boolean substitute )
        {
            variable.clearValues();

            // search variable
            int priority= 0;
            for ( PluginAndPrio pap : plugins )
                if ( pap.plugin.load( variable ) )
                {
                    priority= pap.prio;
                    break;
                }

            // not found?
            if ( !substitute || priority == 0 )
                return 0;

            // substitution in all values of variable
            for ( int valueNo= 0; valueNo < variable.size(); valueNo++ )
            {
                AString value= variable.getString( valueNo );

                int searchStartIdx=  0;
                int maxReplacements = 50;
                Variable replVar= null;
                do
                {
                    // search start
                    int repStart= value.indexOf( substitutionVariableStart, searchStartIdx );
                    if ( repStart < 0 )
                        break;
                    searchStartIdx= repStart;
                    int varStart= repStart + substitutionVariableStart.length();

                    if( replVar == null )
                        replVar= new Variable();
                    int repLen;
                    int varLen;

                    // search end in two different ways depending on setting of public field "SubstitutionVariableEnd"
                    if ( substitutionVariableEnd.isEmpty() )
                    {
                        int idx=   value.indexOfAny( substitutionVariableDelimiters, Inclusion.INCLUDE, varStart );
                        if ( idx < 0 )
                            idx= value.length();

                        varLen= idx - varStart;
                        repLen= idx - repStart;
                    }
                    else
                    {
                        int idx=   value.indexOf   ( substitutionVariableEnd, varStart );
                        if (idx < 0 )
                        {
                            ALIB.WARNING(   "End of substitution variable not found (while start was found). Variable name: "
                                           + variable.fullname
                                           + " Value: \"" + value + "\"." );
                            break;
                        }

                        varLen= idx - varStart;
                        repLen= idx + substitutionVariableEnd.length() - repStart;
                    }

                    // get variable name string
                    tmpReplVarCategory.clear();
                    if ( tmpReplVarAll.set( value, varStart, varLen ).isEmpty() )
                    {
                        searchStartIdx+=   substitutionVariableStart.length()
                                         + substitutionVariableEnd.length();
                        continue;
                    }

                    // parse category from name
                    int catSeparatorIdx= tmpReplVarAll.indexOf( '_' );
                    if (catSeparatorIdx >= 0 )
                    {
                        tmpReplVarCategory.set( tmpReplVarAll, 0                   , catSeparatorIdx );
                        tmpReplVarName    .set( tmpReplVarAll, catSeparatorIdx + 1                   );
                    }
                    else
                        tmpReplVarName    .set( tmpReplVarAll );

                    if ( tmpReplVarName.isNotEmpty() )
                    {
                        replVar.define( tmpReplVarCategory, tmpReplVarName,  variable.delim );
                        loadImpl( replVar, false );
                    }
                    else
                        replVar.clearValues();

                    // do the replacement (even if no variable was found)
                    if ( replVar.size() == 1 )
                        value.replaceSubstring( replVar.getString(), repStart, repLen );

                    else if ( replVar.size() > 1 )
                    {
                        variable.ReplaceValue( valueNo, replVar );

                        // repeat replacements in current value, as current value changed
                        valueNo--;
                        break;
                    }

                    else
                        value.replaceSubstring( "",                 repStart, repLen );

                }
                while( --maxReplacements > 0 );

                // warn if max replacements
                if( maxReplacements <= 0 )
                    ALIB.WARNING(     "Too many substitutions in variable "
                                      + variable.fullname
                                      + ". Probably a recursive variable definition was made. ");
            }
            return priority;
        }

} // class



