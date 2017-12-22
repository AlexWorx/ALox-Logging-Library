
// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;


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
- Central class \alib{config,Configuration} used to retrieve and store external configuration data using arbitrary sources.
- Abstract plug-in interface \alib{config,ConfigurationPlugin} to read from (and optionally store into) custom external storage.
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
\ref cs.aworx.lib.config.ConfigurationPlugin "ConfigurationPlugin"
are plugged into an object of type
\ref cs.aworx.lib.config.Configuration "Configuration" and are responsible for reading (and
optionally writing) variables from dedicated sources.

Class \b %Configuration offers an interface to retrieve and store configuration variables using
the plug-ins. The plug-ins are attached to the \b %Configuration instance along with a unique priority.
Values are retrieved and stored by looping through the plug-ins sorted by priority.
As soon as one plug-in confirms to have found (or stored) the variable, the loop ends.
This way, plug-ins may "overrule" each other in respect to retrieving configuration data.

Class \ref cs.aworx.lib.ALIB "ALIB" creates a static singleton of this class for public
access and this singleton is usually all that is needed.


<b>Naming %Configuration Variables:</b><br>

%Configuration variables are addressed by two strings: The \b category and the \b name. In the case of
INI files, the category is translated to the section and the name to variables within the
section. Other plug-ins, for example
\ref cs.aworx.lib.config.CLIArgs "CLIArgs" or
\ref cs.aworx.lib.config.Environment  "Environment", are prepending the category
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
- Class \ref cs.aworx.lib.config.CLIArgs "CLIArgs":<br>
  Reads parameter values of the form -[-]CategoryName_VariableName=value from the command line.
- Class \ref cs.aworx.lib.config.Environment  "Environment":<br>
  Reads system defined environment variables
  (see [Wikipedia](https://en.wikipedia.org/wiki/Environment_variable) of the form
  <c>CategoryName_VariableName=value</c>.
- Class \ref cs.aworx.lib.config.IniFile "IniFile":<br>
  Reads and writes quite standard INI files
  (see [Wikipedia](https://en.wikipedia.org/wiki/INI_file).
<p>

The proposed priorities to be used when attaching the plug-ins to the \b %Configuration object,
are given in static fields:

 - \ref cs.aworx.lib.config.Configuration.PrioCLIArgs "Configuration.PrioCLIArgs" (40000)
 - \ref cs.aworx.lib.config.Configuration.PrioEnvironment   "Configuration.PrioEnvironment" (30000)
 - \ref cs.aworx.lib.config.Configuration.PrioStandard      "Configuration.PrioStandard" (20000)

With these default priorities set, whatever is stored in an INI file,
can be overwritten by setting an environment variable. Both settings can in turn be
overwritten by specifying a corresponding command line parameter when launching the process!

# 3. Default Variables #

In addition to the three plug-ins described above, ALib implements a fourth one,
class \ref cs.aworx.lib.config.InMemoryPlugin "InMemoryPlugin". As the name indicates, this
class keeps configuration variables in memory. The special thing about it is that it does not
read any external data source! The reason for having it, is twofold. The first use case
are <em>Default variables</em>.<br>

An instance is plugged into class \b %Configuration with a priority of
- \ref cs.aworx.lib.config.Configuration.PrioDefaultValues "Configuration.PrioDefaultValues" (10000),

this plug-in serves as a storage for default values.
The only way to set these default values is \e programatically, which means "with program code".

The advantages of having such default variables are:
- Code that checks whether a variable is set can be omitted (there is always a value found).
- Code that sets default values if no variable is set can be omitted.
- All default settings can be made in one place (bootstrap section of a process or library)

# 4. Protecting Variables #

Class \ref cs.aworx.lib.config.InMemoryPlugin "InMemoryPlugin" is by default used a second
time by plugging an instance into class \b %Configuration with a priority of
- \ref cs.aworx.lib.config.Configuration.PrioProtectedValues "Configuration.PrioProtectedValues" (max integer).

When setting a variable within this plug-in, no other plug-in can <em>'overrule'</em> this value.
This way, it is possible to protect values against external modification.

\note
    One might think: "If I do not want to allow external modification, I rather hard-code
    everything". This of-course is true for code under control. However, for 3rd party
    code using ALib, this offers an easy way to disallow users of your software (which incorporates
    that 3rd party code) to configure things that you do not want to be configurable.

# 5. Using class %Configuration #
In normal use cases, there is no need to create an instance of class Configuration, as a default
singleton is provided with
\ref cs.aworx.lib.ALIB.Config "ALIB.Config".
The command line parameters (optionally) provided with
\ref cs.aworx.lib.ALIB.Init "ALIB.Init" are passed to the command-line plug-in of this
singleton.

Class %Configuration in the constructor by default sets up four plug-ins automatically:
\alib{config,CLIArgs} for parsing command-line arguments as variables,
\alib{config,Environment} for environment variables and two plug-ins of type
\alib{config,InMemoryPlugin} used for default and protected values.

If an application wants to suppress the use of one of the plug-ins, the plug-ins can be removed
using method \ref cs.aworx.lib.config.Configuration.RemovePlugin "RemovePlugin".<br>
On the other hand, a plug-in of type
\ref cs.aworx.lib.config.IniFile "IniFile" may be attached on bootstrap of a process using
\ref cs.aworx.lib.config.Configuration.PrioStandard "Configuration.PrioStandard" (20000).

In addition (or alternatively), custom plug-ins may be written and installed using arbitrary
priorities.

Class \b %IniFile is designed for simplicity and smaller applications.
Instead of using it \b %IniFile, it is recommended to use application/platform
specific mechanisms for writing configuration data. In this case, write your own plug-in
to grant ALib and other libraries which rely on ALib, access to your applications's configuration
data. Again, ALib here follows its design principle to be non intrusive: The plug-in concept
allows users of ALib (more important:  users of ALib enabled libraries) to expose any external
configuration source to these libraries.
This way, the users can stick to his/her preferred way of implementation.

\anchor cs_alib_namespace_config_substitution
# 6. %Variable Substitution #

Method \ref cs.aworx.lib.config.Configuration.Load  "Configuration.Load" by default substitutes
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
\ref cs.aworx.lib.config.Configuration.SubstitutionVariableStart       "SubstitutionVariableStart",
\ref cs.aworx.lib.config.Configuration.SubstitutionVariableEnd         "SubstitutionVariableEnd" and
\ref cs.aworx.lib.config.Configuration.SubstitutionVariableDelimiters  "SubstitutionVariableDelimiters"
for more information.

When parsing a variables' category and name, method
\ref cs.aworx.lib.config.Configuration.Load  "Configuration.Load" searches for an underscore
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
\ref cs.aworx.lib.config.ConfigurationPlugin "ConfigurationPlugin" objects.

Simple access methods allow to read or set the values of a variable.

By consequently using optional class VariableDecl for declaring all variables of an application or library,
all attributes of variables can be maintained in one place. This includes categories, names, comments,
value delimiters and default values of variables.
Class \b %Variable accepts instances of \b %VariableDecl in the constructor as well as in overloaded
method \ref cs.aworx.lib.config.Variable.Declare "Variable.Declare".

# 8. In- and Externalizing %Variable values #
%Variable values provided via command line parameters, environment variables or textual configuration
files need to be converted when loading and storing them. This has two reasons:
- Certain characters of variables have to be "escaped", e.g. \c '\\n' or \c '\\t' within strings
- Multiple values defined in variables need to be separated when storing  - and parsed back when loading
  a variable.

For this task, class
\ref cs.aworx.lib.config.XTernalizer "XTernalizer" is used. Each
\ref cs.aworx.lib.config.ConfigurationPlugin "ConfigurationPlugin" owns an instance of this
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
namespace cs.aworx.lib.config  {


// #################################################################################################
// class Configuration
// #################################################################################################

/** ************************************************************************************************
 * This class is a container of objects of type
 * \ref cs.aworx.lib.config.ConfigurationPlugin "ConfigurationPlugin",
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
 * \ref cs_alib_namespace_config_substitution "Variable Substitution".
 *
 * See documentation of namespace #cs.aworx.lib.config for more information on ALib
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
            public int                   prio;

            /** The plug-in. */
            public ConfigurationPlugin   plugin;
        }

        /** The plug-ins we have in our portfolio */
        protected  List<PluginAndPrio>   plugins                        = new List<PluginAndPrio>();

        /** A temporary object used for conversion */
        protected  AString               tmpConversion                              = new AString();

        /** A temporary object used with variable substitution */
        protected  Substring             tmpReplVarAll                            = new Substring();

        /** A temporary object used with variable substitution */
        protected  Substring             tmpReplVarName                           = new Substring();

        /** A temporary object used with variable substitution */
        protected  Substring             tmpReplVarCategory                       = new Substring();

    // #############################################################################################
    // public fields
    // #############################################################################################
        /**
         * Values considered to indicate "true". Defaults to
         * { "1", "true", "t", "yes", "y", "on", "ok" }.
         * See methods #IsTrue.
         *
         * Application specific values (e.g. localization languages) might be added by publicly
         * accessing this field and adding new values (or removing existing).
         */
        public  List<AString>               TrueValues;

        /** Number format definition used to read and write int and float values.  */
        public NumberFormat                 NumberFormat                       = new NumberFormat();

        /**
         * The start string to identify substitution variables.
         * Defaults to single character \c '$'. If a string is set, i.e. \c "${", then field
         * #SubstitutionVariableEnd may be set accordingly, i.e. \c "}"
         */
        public AString                      SubstitutionVariableStart            = new AString("$");

        /**
         * The end of a substitution variables.
         * If this field is set, then field #SubstitutionVariableDelimiters is ignored. If this
         * field is null (the default) or empty, it is ignored and characters in field
         * #SubstitutionVariableDelimiters are used to identify the end of the variable.
         */
        public AString                      SubstitutionVariableEnd                 = new AString();

        /**
         * The delimiters used to identify the end of a substitutable variable.
         * If field #SubstitutionVariableEnd is not empty, this field is ignored. Otherwise, all
         * characters defined in this string are used to identify the end of a substitution
         * variable.
         */
        public char[]                       SubstitutionVariableDelimiters
        = { ' ','$','@',',','.',';',':','\"','\'','+','-','*','/','\\',
            '§','%','&','(',')','[',']','{','}','<','>','=','?','\'','`','~','#' };


        /** Constant providing the highest possible priority. This is used with
            #PrioProtectedValues */
        public const int                    PrioProtectedValues                      = int.MaxValue;

        /** Constant providing default priority for \b %IniFile (or similar) external plug-ins. */
        public const int                    PrioCLIArgs                                     = 40000;

        /** Constant providing default priority for environment variables plug-in. */
        public const int                    PrioEnvironment                                 = 30000;

        /** Constant providing default priority for command-line parameters plug-in. */
        public const int                    PrioStandard                                    = 20000;

        /** Constant providing a low priority. This is used with #PrioDefaultValues */
        public const int                    PrioDefaultValues                               = 10000;

        /**
         * Constant providing a priority which is even lower than default. This priority is
         * not used by any standard plug-ins and currently not even anywhere in core ALib.
         * The rational to provide it is for third party libraries that may use this value
         * in cases where values are estimated or detected - instead of defaulted.
         * A user of the library may then overwrite such auto-detection by setting a default value
         * in the configuration.
         */
        public const int                    PrioAutodetect                                    = 500;

    // #############################################################################################
    // Initialization
    // #############################################################################################
        /** ****************************************************************************************
         * Constructs a Configuration. If \p addDefaultPlugins is \c true, registers the initial
         * plug-ins as follows
         *
         *  Priority         | Plug-in Type
         * ------------------|----------------------------------------------------------
         *  \alib{config,Configuration.PrioDefaultValues}       | \alib{config,InMemoryPlugin}
         *  \alib{config,Configuration.PrioEnvironment}   | \alib{config,Environment}
         *  \alib{config,Configuration.PrioCLIArgs} | \alib{config,CLIArgs}
         *  \alib{config,Configuration.PrioProtectedValues}     | \alib{config,InMemoryPlugin}
         *
         * @param addDefaultPlugins If \c true, the default plugins are added.
         *                          Defaults to \c true.
         ******************************************************************************************/
        public Configuration(  bool addDefaultPlugins = true  )
        {
            // set default true values
            TrueValues=     new List<AString>();
            TrueValues.Add( new AString( "1"    ) );
            TrueValues.Add( new AString( "true" ) );
            TrueValues.Add( new AString( "t"    ) );
            TrueValues.Add( new AString( "yes"  ) );
            TrueValues.Add( new AString( "y"    ) );
            TrueValues.Add( new AString( "on"   ) );
            TrueValues.Add( new AString( "ok"   ) );

            if( addDefaultPlugins )
            {
                InsertPlugin( new InMemoryPlugin()    , PrioDefaultValues    );
                InsertPlugin( new Environment() , PrioEnvironment      );
                InsertPlugin( new CLIArgs(), PrioCLIArgs    );
                InsertPlugin( new InMemoryPlugin()    , PrioProtectedValues  );
            }
        }

        /** ****************************************************************************************
         * Sets the command line arguments for default plug-in \alib{config,CLIArgs}.
         *
         * \note This method should be called for instances of this class after construction.<br>
         *       In standard application scenarios, this method is invoked by method
         *       \ref cs.aworx.lib.ALIB.Init   "ALIB.Init" for the static singleton found in
         *       \ref cs.aworx.lib.ALIB.Config "ALIB.Config".
         *
         * @param args    Parameters taken from <em>standard C#</em> method \c main()
         *                (the list of command line arguments).
         *                Defaults to null.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public void  SetCommandLineArgs( String[] args= null )
        {
            if (args == null || args.Length == 0)
                return;

            CLIArgs cliParameters= GetPluginTypeSafe<CLIArgs>();
            ALIB_DBG.ASSERT_ERROR( cliParameters != null , "No CLIArgs  installed" );
            cliParameters.SetArgs( args );
        }

    // #############################################################################################
    // interface
    // #############################################################################################

        /** ****************************************************************************************
         * Adds the given plug-in to the list of plug-ins used to query configuration values.
         * Higher numbers for parameter priority, prioritize this plug-in against those with
         * lower values. Default values are provided with static constant fields
         * #PrioCLIArgs, #PrioEnvironment and #PrioStandard.
         *
         * @param plugin   The plug-in to insert.
         * @param priority The priority of the plug-in.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public void InsertPlugin( ConfigurationPlugin plugin, int priority )
        {
            int i;
            for ( i= 0; i < plugins.Count; i++ )
            {
                ALIB_DBG.ASSERT_ERROR( plugins[i].prio != priority,
                    "Configuration.InsertPlugin(): Plug-in with same priority exists" );

                if ( plugins[i].prio < priority )
                    break;
            }

            PluginAndPrio ppp=  new PluginAndPrio();
            ppp.plugin=         plugin;
            ppp.prio=           priority;
            plugins.Insert( i, ppp );
        }

        /** ****************************************************************************************
         * Remove the given plug-in from the list of plug-ins.
         * Responsibility for deletion of removed plug-ins moves to the remover.
         * Active (inserted) plug-ins get deleted by class' destructor.
         * @param plugin  The plug-in to be deleted.
         * @return true if the plug-in was removed, else false.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public bool RemovePlugin( ConfigurationPlugin plugin )
        {
            for ( int i= 0; i < plugins.Count; i++ )
            {
                if ( plugins[i].plugin == plugin )
                {
                    plugins.RemoveAt( i );
                    return true;
                }
            }

            ALIB_DBG.WARNING( "No Plug-in was removed " );
            return false;
        }

        /** ****************************************************************************************
         * Returns the plug-in with the given priority. If the plug-in does not exist, \c null
         * is returned.
         *
         * \note
         *   The method is not thread-safe. At least, the returned plugin may become invalid
         *   after the method returned.
         *   For thread-safe operations, this object needs to be acquired and released explicitly.
         *
         *   Usually this method is used in the termination section of a software, when no parallel
         *   threads are active.
         *
         *   It may be used for example to \ref FetchFromDefault "fetch" default variables into a
         *   configuration file.
         *
         * @param priority The priority of the plug-in to return.
         * @return The plug-in requested or \c null if not available.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public
        ConfigurationPlugin  GetPlugin( int priority )
        {
            foreach ( PluginAndPrio ppp in plugins )
                if (ppp.prio == priority)
                    return ppp.plugin;
            return null;
        }

        /** ****************************************************************************************
         * Same as #GetPlugin, but converts the plug-in found to the template type.
         * A type-check is performed. If the plugin has a different type, \c null is returned.
         *
         * @param priority The priority of the plug-in to return.
         * @tparam TPluginType The type of the plugin to search.
         * @return The plug-in of requested type and priority. \c null if not available.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public
        TPluginType          GetPluginTypeSafe<TPluginType>( int priority )  where TPluginType : ConfigurationPlugin
        {
            return GetPlugin( priority ) as TPluginType;
        }

        /** ****************************************************************************************
         * Searches all plug-ins for the first found with type \p TPluginType.
         *
         * @tparam TPluginType The type of the plugin to search.
         * @return The plug-in of requested type. \c null if not available.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public
        TPluginType          GetPluginTypeSafe<TPluginType>()                where TPluginType : ConfigurationPlugin
        {
            TPluginType casted=null;;
            foreach( PluginAndPrio ppp in plugins )
                if( (casted= ppp.plugin as TPluginType)  != null )
                    break;

            return casted;
        }

        /** ****************************************************************************************
         * Checks if any plug-in is attached. This is useful if optional configuration objects
         * are used. In case no plug-in was attached (by a third party), the effort to declare and
         * search a variable can be omitted.
         * @return \c true if this object has any plugin set, \c false otherwise.
         ******************************************************************************************/
        public bool          HasPlugins()
        {
            return plugins.Count > 0;
        }




        /** ****************************************************************************************
         * This method fetches all values from a plug-in of priority #PrioDefaultValues, which are
         * not present in the given plug-in \p dest and stores them in that.
         * This is useful to collect all generated default values and store them in a users'
         * configuration file. This way, the user can identify configurable options easily.
         *
         * \note
         *   Applications might want to copy only a portion of the default values (of a section)
         *   to not blow up a users' configuration. To achieve this, a custom method to fetch
         *   selected values has to be implemented. In this respect, this method is a very simple
         *   default and its source might be used as a jump start.
         *
         * @param dest          The destination plug-in.
         * @param sectionName   Optional string denoting a section to fetch.
         *                      Defaults to \c null.
         * @return The number of variables fetched.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public int FetchFromDefault( ConfigurationPlugin dest, String sectionName = null )
        {
            InMemoryPlugin defaultPlugin= GetPluginTypeSafe<InMemoryPlugin>( PrioDefaultValues );
            ALIB_DBG.ASSERT_ERROR(defaultPlugin != null,
                                  "Utility method FetchFromDefault used without default plugin in place.");
            int cntCopied= 0;
            Variable variable= new Variable();
            for( int sNo= 0; sNo < defaultPlugin.Sections.Count ; sNo++ )
            {
                InMemoryPlugin.Section section= defaultPlugin.Sections[sNo];
                if( sectionName!=null && !section.Name.Equals( sectionName ) )
                    continue;

                for( int vNo= 0; vNo < section.Entries.Count ; vNo++ )
                {
                    InMemoryPlugin.Entry entry= section.Entries[vNo];
                    if( !dest.Load( variable.Declare(section.Name, entry.Name ), true ) )
                    {
                        defaultPlugin.Load  ( variable );
                        dest.Store( variable );
                        cntCopied++;
                    }
                }
            }

            return  cntCopied;
        }

        /** ****************************************************************************************
         * Utility method that checks if a given value represents boolean \b true.
         * Uses field #TrueValues. Comparisons are made case insensitive.
         *
         * @param value  The value to check
         *
         * @return   Returns \c true, if the value represents 'true', \c false if not.
         ******************************************************************************************/
        public bool  IsTrue( AString value )
        {
            foreach ( AString s in TrueValues )
                if ( value.Equals( s, Case.Ignore ) )
                    return true;

            return false;
        }

        /** ****************************************************************************************
         * Receives and optionally creates configuration variable.
         *
         * If the variable was not found and \alib{config,Variable.DefaultValue}
         * in \p variable is set, the method adds the value value to a plug-in of priority
         * #PrioDefaultValues, (respectively to the plug-in found at or below #PrioDefaultValues).
         * For the conversion of the value, field
         * \alib{config,ConfigurationPlugin.StringConverter} of field a plug-in of priority
         * #PrioDefaultValues, is used. (Which has to be present.)
         *
         * @param variable       The variable to receive.
         *
         * @returns The priority of the configuration plug-in that provided the result.
         *          \c 0 if not found.
         ******************************************************************************************/
        [MethodImpl(MethodImplOptions.Synchronized)]
        public int  Load( Variable    variable )
        {
            variable.Config=    this;
            variable.Priority=  loadImpl( variable, true );

            if ( variable.Priority == 0 && variable.DefaultValue.IsNotNull() )
                Store( variable, variable.DefaultValue );

            return variable.Priority;
        }

        /** ****************************************************************************************
         * Writes the variable to the configuration.
         * In general, this is done by asking  each of our installed plug-ins - in the order of
         * their priority - to do so.
         * As soon as the first plug-in returns \c true, the variable is considered written and no
         * other plug-in is asked.
         * This way, the variable is stored by the plug-in with the highest priority.
         *
         * The maximum priority to start the loop with depends on field
         * \ref cs.aworx.lib.config.Variable.Priority "Variable.Priority"
         * of the given \p variable. The rules are as follows:
         * - If the value is \c 0, which is the default value of new variables or ones that
         *   were freshly declared, then prior to storing the value, the variable is (tried to be)
         *   loaded first (without actually overwriting the values).
         *   After that, one of the next two rules apply.
         * - If the value is \c 0, which indicates that a previous load operation failed, the
         *   loop starts with #PrioDefaultValues
         *   (and usually ends there, as standard configuration sets
         *   do not have plug-ins with lower priorities installed). In other words, newly created
         *   variables are stored in the plug-in of priority #PrioDefaultValues (usually an
         *   \b InMemoryPlugin). This way, they are
         *   not written to external configuration files, unless the application explicitly moves
         *   such new default values to dedicated other plug-ins (e.g. on termination).
         * - If the value is greater than \c 0, the value is used as the start of the loop.
         *   This way, an already defined variable will be stored in the same plug-in as it was
         *   found or one with a lower priority, if that plug-in does not provide writing
         *   capabilities.
         *
         * Consequently, as field \alib{config,Variable.Priority} is public, the behavior
         * can be manipulated, by setting the field explicitly prior to invoking this method.
         * Some frequent use cases shall be named here:
         * - Setting the field to ##PrioProtectedValues allows to protect the variable value in
         *   respect to external manipulation.
         * - By setting the field to #PrioDefaultValues, the value becomes just a default
         *   and does not overwrite externally specified values.
         * - Setting the field to a distinct priority value that names a user-specific configuration
         *   (vs. a system-wide configuration) to store into.
         * - Setting the field to ##PrioProtectedValues <c>- 1</c>, allows to store the
         *   variable just in the plug-in with highest possible priority, for example
         *   a user specific configuration is preferred to a system wide configuration)
         * - A variable might be related to a second one. If the priority of the second one is
         *   known, that priority might be set to possibly have both variables stored in the same
         *   plug-in.
         *
         * The method returns the priority of the configuration plug-in that the value was written
         * to as well as storing this value in field \alib{config,Variable.Priority}.
         * If the result is \c 0, the variable was not written. This might only happen if
         * - either field default plug-in of priority #PrioDefaultValues was modified
         *   (removed or exchanged with a different  plug-in that does not write the value)
         * - or if field \p Priority of the variable was set below #PrioDefaultValues and greater
         *   than \c 0.
         * - The detected (!) priority was ##PrioProtectedValues.
         *   In this case, obviously the application does not want to allow changes and writing the
         *   variable into a different plug-in has no effect.
         *   This way, such variables also do not appear in a users' configuration
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
        [MethodImpl(MethodImplOptions.Synchronized)]
        public int   Store( Variable variable, Object externalizedValue= null )
        {
            // checks
            if(     externalizedValue == null
                || ( externalizedValue is AString && ((AString) externalizedValue).IsNull() ) )

            {
                if ( variable.Name.IsEmpty())
                {
                    ALIB_DBG.ERROR( "Trying to store an undefined variable."  );
                    return 0;
                }

                if ( variable.Size() > 1 && variable.Delim == '\0' )
                {
                    ALIB_DBG.ERROR(   "Trying to store variable \"" + variable.Fullname
                                + "\" which has multiple values set but no delimiter defined."  );
                    return 0;
                }
            }

            // store us as config
            variable.Config= this;

            // detect?
            bool detected= variable.Priority <= 0;
            if ( detected )
            {
                variable.Priority= 0;
                foreach ( PluginAndPrio ppp in plugins )
                    if ( ppp.plugin.Load( variable, true ) )
                    {
                        variable.Priority= ppp.prio;
                        break;
                    }
            }

            // new variables go to default
            if ( variable.Priority == 0 )
                variable.Priority= Configuration.PrioDefaultValues;

            // we do not store if detected priority is protected
            else if( detected && variable.Priority == Configuration.PrioProtectedValues )
                return (variable.Priority= 0);

            // store
            foreach ( PluginAndPrio ppp in plugins )
                if (    ppp.prio <= variable.Priority
                     && ppp.plugin.Store( variable, externalizedValue ) )
                    {
                        return (variable.Priority= ppp.prio);
                    }

            return (variable.Priority= 0);
        }

    // #############################################################################################
    // convenience methods
    // #############################################################################################

        /** ****************************************************************************************
         * Convenience method that stores the variable with priority
         * \ref cs.aworx.lib.config.Configuration.PrioDefaultValues "Configuration.PrioDefaultValues".
         *
         * The variable value is determined as follows:
         * - If optional parameter \p externalizedValue is provided and not \e nulled, the values
         *   are loaded from that string.
         * - Otherwise, if the variable has no values set but field
         *   \alib{config,Variable.DefaultValue} is not \e nulled, then values are loaded from
         ~   this field.
         * - If all is unset (the variable values, parameter \p externalizedValue and field
         *   \alib{config,Variable.DefaultValue}), then the unset variable is stored, which results
         ~   in removing an existing default value from the configuration.
         *
         *
         * @param variable              The variable object.
         * @param externalizedValue     Optional externalized value string. If given, the variable
         *                              is set prior to writing.
         * @returns The result of
         *          \ref cs.aworx.lib.config.Configuration.Store "Configuration.Default.Store(this)".
         ******************************************************************************************/
        public int     StoreDefault( Variable variable, Object externalizedValue= null )
        {
            InMemoryPlugin defaultPlugin= GetPluginTypeSafe<InMemoryPlugin>( PrioDefaultValues );
            ALIB_DBG.ASSERT_ERROR(defaultPlugin != null,
                                  "Utility method StoreDefault used without default plugin in place.");

            if(     externalizedValue != null
                && ( !(externalizedValue is AString) || ((AString) externalizedValue).IsNotNull() ) )
                defaultPlugin.StringConverter.LoadFromString( variable, externalizedValue );

            if ( variable.Size() == 0 && variable.DefaultValue.IsNotNull() )
                defaultPlugin.StringConverter.LoadFromString( variable, variable.DefaultValue );

            variable.Priority= Configuration.PrioDefaultValues;
            return Store( variable, null );
        }

        /** ****************************************************************************************
         * Convenience method that stores the variable with priority
         * \ref cs.aworx.lib.config.Configuration.PrioProtectedValues "Configuration.PrioProtectedValues".
         *
         * The variable value is determined as follows:
         * - If optional parameter \p externalizedValue is provided and not \e nulled, the values
         *   are loaded from that string.
         * - Otherwise, if the variable has no values set but field
         *   \alib{config,Variable.DefaultValue} is not \e nulled
         *   then values are loaded from this field.
         * - If all is unset (the variable values, parameter \p externalizedValue and field
         *   \alib{config,Variable.DefaultValue}), then the unset variable is stored, which results
         ~   in removing an existing protection value from the configuration.
         *
         * @param variable              The variable object.
         * @param externalizedValue     Optional externalized value string. If given, the variable
         *                              is set prior to writing.
         * @returns The result of
         *          \ref cs.aworx.lib.config.Configuration.Store "Configuration.Default.Store(this)".
         ******************************************************************************************/
        public int     Protect( Variable variable, Object externalizedValue= null )
        {
            InMemoryPlugin protectedPlugin= GetPluginTypeSafe<InMemoryPlugin>( PrioProtectedValues);
            ALIB_DBG.ASSERT_ERROR(protectedPlugin != null,
                                  "Utility method FetchFromDefault used without default plugin in place.");

            if(     externalizedValue != null
                && ( !(externalizedValue is AString) || ((AString) externalizedValue).IsNotNull() ) )
                protectedPlugin.StringConverter.LoadFromString( variable, externalizedValue );

            if ( variable.Size() == 0 && variable.DefaultValue.IsNotNull() )
                protectedPlugin.StringConverter.LoadFromString( variable, variable.DefaultValue );

            variable.Priority= Configuration.PrioProtectedValues;
            return Store( variable, null );
        }


        /** ****************************************************************************************
         * Convenience method to set values according to the provided string.
         * For the conversion of the "externalized" string, method
         * \alib{config,XTernalizer.LoadFromString} of field
         * \alib{config,ConfigurationPlugin.StringConverter}
         * of a plug-in of priority #PrioDefaultValues, is used.
         *
         * @param variable              The variable object.
         * @param externalizedValue     The new value to write.
         *
         * @returns The size of the variable after parsing.
         ******************************************************************************************/
        public int   LoadFromString( Variable variable, Object externalizedValue )
        {
            ConfigurationPlugin defaultPlugin= GetPlugin( PrioDefaultValues );
            ALIB_DBG.ASSERT_ERROR(defaultPlugin != null,
                "Utility method LoadFromString used without default plugin in place.");
            defaultPlugin.StringConverter.LoadFromString( variable, externalizedValue );
            return variable.Size();
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
        public int loadImpl( Variable variable, bool substitute )
        {
            variable.ClearValues();

            // search variable
            int priority= 0;
            foreach ( PluginAndPrio ppp in plugins )
                if ( ppp.plugin.Load( variable ) )
                {
                    priority= ppp.prio;
                    break;
                }

            // not found?
            if ( !substitute || priority == 0 )
                return 0;

            // substitution in all values of variable
            for ( int valueNo= 0; valueNo < variable.Size(); valueNo++ )
            {
                int searchStartIdx=  0;
                int maxReplacements = 50;
                Variable replVar= null;
                do
                {
                    AString value= variable.GetString( valueNo );

                    // search start
                    int repStart= value.IndexOf( SubstitutionVariableStart, searchStartIdx );
                    if ( repStart < 0 )
                        break;
                    searchStartIdx= repStart;
                    int varStart= repStart + SubstitutionVariableStart.Length();

                    if( replVar == null )
                        replVar= new Variable();
                    int repLen;
                    int varLen;

                    // search end in two different ways depending on setting of public field "SubstitutionVariableEnd"
                    if ( SubstitutionVariableEnd.IsEmpty() )
                    {
                        int idx=   value.IndexOfAny( SubstitutionVariableDelimiters, Inclusion.Include, varStart );
                        if ( idx < 0 )
                            idx= value.Length();

                        varLen= idx - varStart;
                        repLen= idx - repStart;
                    }
                    else
                    {
                        int idx=   value.IndexOf   ( SubstitutionVariableEnd, varStart );
                        if (idx < 0 )
                        {
                            ALIB_DBG.WARNING(   "End of substitution variable not found (while start was found). Variable name: "
                                           + variable.Fullname
                                           + " Value: \"" + value + "\"." );
                            break;
                        }

                        varLen= idx - varStart;
                        repLen= idx + SubstitutionVariableEnd.Length() - repStart;

                    }

                    // get variable name string
                    tmpReplVarCategory.Clear();
                    if ( tmpReplVarAll.Set( value, varStart, varLen ).IsEmpty() )
                    {
                        searchStartIdx+=   SubstitutionVariableStart.Length()
                                         + SubstitutionVariableEnd.Length();
                        continue;
                    }

                    // parse category from name
                    int catSeparatorIdx= tmpReplVarAll.IndexOf( '_' );
                    if (catSeparatorIdx >= 0 )
                    {
                        tmpReplVarCategory.Set( tmpReplVarAll, 0                   , catSeparatorIdx );
                        tmpReplVarName    .Set( tmpReplVarAll, catSeparatorIdx + 1                   );
                    }
                    else
                        tmpReplVarName    .Set( tmpReplVarAll );

                    if ( tmpReplVarName.IsNotEmpty() )
                    {
                        replVar.Declare( tmpReplVarCategory, tmpReplVarName, variable.Delim );
                        loadImpl( replVar, false );
                    }
                    else
                        replVar.ClearValues();


                    // do the replacement (even if no variable was found)
                    if ( replVar.Size() == 1 )
                        value.ReplaceSubstring( replVar.GetString(), repStart, repLen );

                    else if ( replVar.Size() > 1 )
                    {
                        variable.ReplaceValue( valueNo, replVar );

                        // repeat replacements in current value, as current value changed
                        valueNo--;
                        break;
                    }

                    else
                        value.ReplaceSubstring( "",                 repStart, repLen );

                }
                while( --maxReplacements > 0 );

                // warn if max replacements
                if( maxReplacements <= 0 )
                    ALIB_DBG.WARNING(     "Too many substitutions in variable "
                                      + variable.Fullname
                                      + ". Probably a recursive variable definition was made. ");
            }

            return priority;
        }

} // class

}// namespace

