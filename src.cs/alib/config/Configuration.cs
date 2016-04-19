// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using cs.aworx.lib.time;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;


/** ************************************************************************************************
 * This namespace provides tools to read and write configuration data using different mechanisms.
 *
 * The different 'mechanisms' are implemented through plug-ins, namely objects of types
 * derived from abstract class \ref cs::aworx::lib::config::ConfigurationPlugIn "ConfigurationPlugIn".
 *
 * The plug-ins are gathered (plugged into) an object of type
 * \ref cs::aworx::lib::config::Configuration "Configuration".
 * Class \ref cs::aworx::lib::ALIB "ALIB" creates a static singleton of this class for public access.
 *
 * Class \b %Configuration offers an interface to retrieve and store configuration variables using
 * the plug-ins. The plug-ins are attached to the \b %Configuration with a unique priority.
 * Values are retrieved and stored by looping through the plug-ins sorted by priority.
 * As soon as one plug-in confirms to have found (or stored) the variable, the loop ends.
 * This way, plug-ins may "overrule" each other in respect to retrieving configuration data.
 *
 * Three different plug-ins are implemented within ALib already:
 * - Class CommandLinePlugIn:<br>
 *   Reads parameter values of the form -[-]CategoryName_VariableName=value from the command line.
 *   This plug-in has a proposed priority of 300, defined in static field
 *   \ref cs::aworx::lib::config::Configuration::PrioCmdLine "Configuration.PrioCmdLine".
 *   This plug-in does not write values.
 * - Class EnvironmentPlugIn:<br>
 *   Reads system defined environment variables
 *   (see [Wikipedia](https://en.wikipedia.org/wiki/Environment_variable) of the form
 *   <c>CategoryName_VariableName=value</c>.
 *   This plug-in has a proposed priority of 200, defined in static field
 *   \ref cs::aworx::lib::config::Configuration::PrioEnvVars "Configuration.PrioEnvVars".
 *   This plug-in does not write values.
 * - Class IniFile:<br>
 *   Reads and writes quite standard INI files
 *   (see [Wikipedia](https://en.wikipedia.org/wiki/INI_file).
 *   This plug-in has a proposed priority of 100, defined in static field
 *   \ref cs::aworx::lib::config::Configuration::PrioIniFile "Configuration.PrioIniFile".
 *   This plug-in reads and writes values.
 *
 * With these default priorities set, whatever is stored in an INI file,
 * can be overwritten by setting an environment variable, and both settings can in turn be
 * overwritten by specifying a corresponding command line parameter when launching the process.
 *
 * \note
 *  Instead of using provided class \b %IniFile, it is recommended to use application/platform
 *  specific mechanisms for writing configuration data. Class \b %IniFile is designed for
 *  simplicity and smaller applications.
 **************************************************************************************************/
namespace cs.aworx.lib.config  {


    // #############################################################################################
    // class Configuration
    // #############################################################################################

    /** ********************************************************************************************
     * This class is supposed to be a static singleton in class ALIB.
     * It holds a list of objects of type ConfigurationPlugIn, sorted by their priority and provides a
     * single user interface to query configuration data from those.
     *
     * By default, two configuration plug-ins are set up:
     * - command line parameter configuration options
     *   (Priority 400, provided in static constant field #PrioCmdLine).
     * - environment variable configuration options
     *   (Priority 300, provided in static constant field #PrioEnvVars).
     *
     * An application specific instance of abstract class
     * \ref cs::aworx::lib::config::ConfigurationPlugIn "ConfigurationPlugIn"
     * that uses appropriate configuration techniques (ini-files, registry entries, etc.)
     * optionally completes this set. It is proposed to use a priority value of 200
     * (provided in static constant field #PrioIniFile)  for custom configuration plug-ins.
     * This way, environment variables could \e overwrite entries in configuration files and
     * command line parameters could in turn \e overwrite environment variables.
     *
     * Variables are case insensitive for the built-in ConfigurationPlugIn types
     * \ref cs::aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn" and
     * \ref cs::aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn".
     *
     * It is recommended to treat variable names case insensitive within custom implementations
     * (specializations) of class ConfigurationPlugIn as well.
     *
     * The interface methods of this class are implemented <em>synchronized</em>.
     * When adding or removing plug-ins, the instance should by synchronized (locked) as well.
     *
     * Some method of this class accept parameters of type <em>Object</em>. In this case, the
     * following string types are accepted:
     * - String
     * - char[]
     * - \ref cs::aworx::lib::strings::AString          "AString"
     * - \ref cs::aworx::lib::strings::Substring  "Substring"
     **********************************************************************************************/

    public class Configuration
    {
        // #########################################################################################
        // internal fields
        // #########################################################################################

            /** An element of the list of plug-ins with their priority */
            public class PluginAndPrio
            {
                /** The priority that was defined when the plug-in was added. */
                public int                   prio;

                /** The plug-in. */
                public ConfigurationPlugIn   plugIn;
            }

            /// The plug-ins we have in our portfolio
            protected  List<PluginAndPrio>   plugins;


        // #########################################################################################
        // public fields
        // #########################################################################################
            /**
             * Values considered to indicate "true". Defaults to "1", "true", "yes" and "ok".
             * Comparisons are made case insensitive.
             *
             * Application specific values (e.g. localization languages) might be added by publicly
             * accessing this field and adding new values (or removing existing).
             */
            public  List<AString>               TrueValues;

            /**
             * The configuration plug-in for command line parameters. Created in the constructor.
             * Provided as public field here, for flexibility. Please note:
             * When this object is replaced by a customized one, it also has to be added to the
             * the list of plug-ins (and any existing one has to be removed).
             */
            public CommandLinePlugIn            CmdLineCP;

            /**
             * The environment plug-in for evaluation of system environment variables.
             * Created in the constructor.
             * Provided as public field here, for flexibility. Please note:
             * When this object is replaced by a customized one, it also has to be added to the
             * the list of plug-ins (and any existing one has to be removed).
             */
            public EnvironmentPlugIn            EnvCP;

            /** Number format definition used by plugins to write int and float values.  */
            public NumberFormat                 NumberFormat=                    new NumberFormat();

            /** Constant providing default priority for \b %IniFile (or similar) plug-in. */
            public const int                    PrioCmdLine                                   = 400;

            /** Constant providing default priority for environment variables plug-in. */
            public const int                    PrioEnvVars                                   = 300;

            /** Constant providing default priority for command-line parameters plug-in. */
            public const int                    PrioIniFile                                   = 200;

        // #########################################################################################
        // Constructor/destructor
        // #########################################################################################
            /** ************************************************************************************
             * Constructs a configuration plug-in and optionally (default) creates two initial
             * plug-ins, one that reads command line options, a second that uses the process
             * environment as configuration source.
             * @param useEnv  If true (default), an EnvironmentPlugIn is created
             *                and attached. To specify false here, might be useful, if a customized
             *                ConfigurationPlugIn that reads environment variables will be attached.
             * @param args    Parameters taken from standard C main() method (the list of command
             *                line arguments). Defautls to null.
             **************************************************************************************/
            public Configuration( bool useEnv= true, String[] args= null )
            {
                plugins=        new List<PluginAndPrio>();

                // set default true values
                TrueValues=     new List<AString>();
                TrueValues.Add( new AString( "1" )    );
                TrueValues.Add( new AString( "true" ) );
                TrueValues.Add( new AString( "yes" )  );
                TrueValues.Add( new AString( "on" )   );
                TrueValues.Add( new AString( "ok" )   );

                // create command line plug-in
                if ( args != null && args.Length > 0 )
                {
                    CmdLineCP= new CommandLinePlugIn ( args );
                    InsertPlugin( CmdLineCP, Configuration.PrioCmdLine );
                }

                // environment config plug-in
                if ( useEnv )
                {
                    EnvCP= new EnvironmentPlugIn();
                    InsertPlugin( EnvCP,     Configuration.PrioEnvVars );
                }

            }

        // #########################################################################################
        // interface
        // #########################################################################################

            /** ************************************************************************************
             * Adds the given plug-in to the list of plug-ins used to query configuration values.
             * Higher numbers for parameter priority, prioritize this plug-in against those with
             * lower values. Default values are provided with static constant fields
             * #PrioCmdLine, #PrioEnvVars and
             * #PrioIniFile.
             * @param plugin   The plug-in to insert.
             * @param priority The priority of the plug-in.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public void InsertPlugin( ConfigurationPlugIn plugin, int priority )
            {
                int i;
                for ( i= 0; i < plugins.Count; i++ )
                {
                    ALIB.ASSERT_ERROR( plugins[i].prio != priority,
                        "Configuration.InsertPlugin(): Plug-in with same priority exists" );

                    if ( plugins[i].prio < priority )
                        break;
                }

                PluginAndPrio pap=  new PluginAndPrio();
                pap.plugIn=         plugin;
                pap.prio=           priority;
                plugins.Insert( i, pap );

                plugin.Parent= this;
            }

            /** ************************************************************************************
             * Remove the given plug-in from the list of plug-ins.
             * Responsibility for deletion of removed plug-ins moves to the remover.
             * Active (inserted) plug-ins get deleted by class' destructor.
             * @param plugin  The plug-in to be deleted.
             * @return true if the plug-in was removed, else false.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public bool RemovePlugin( ConfigurationPlugIn plugin )
            {
                for ( int i= 0; i < plugins.Count; i++ )
                {
                    if ( plugins[i].plugIn == plugin )
                    {
                        plugin.Parent= null;
                        plugins.RemoveAt( i );
                        return true;
                    }
                }

                ALIB.WARNING( "No Plug-in was removed " );
                return false;
            }


            /** ************************************************************************************
             * Retrieves a string value from the configuration settings. This is done by asking
             * each of the installed plug-ins. As soon as the first one returns a value for the
             * given variable name, this value is returned.
             * All variable names are case insensitive.
             * @param category  The category of the  variable.
             *                  (AString compatible type expected.)
             * @param name      The name of the configuration variable to be retrieved.
             *                  (AString compatible type expected.)
             * @param target    A reference to an AString to take the result.
             *                  This AString will be cleared, no matter if a configuration
             *                  variable was found or not.
             *
             * @return Zero if the variable was not found. Otherwise it returns the priority of the
             *         (first) plug-in that contained the variable.
             *         This way, the caller might identify from which configuration
             *         source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int Get( Object category, Object name, AString target )
            {
                target.Clear();

                foreach ( PluginAndPrio pap in plugins )
                    if ( pap.plugIn.Get( category, name, target ) )
                        return pap.prio;

                return 0;
            }

            /** ************************************************************************************
             * Retrieves an integer value from the configuration settings. This is done by asking
             * each of the installed plug-ins. As soon as the first one returns a value for
             * the given variable name, this value is returned.
             * All variable names are case insensitive.
             * @param category  The category of the  variable.
             *                  (AString compatible type expected.)
             * @param name      The name of the configuration variable to be retrieved.
             *                  (AString compatible type expected.)
             * @param target    A reference to an integer variable to take the result.
             * @param temp      A buffer to temporarily store the value for parsing.
             *                  Defaults to null. Provide a local object to gain performance when
             *                  retrieving many variables in a row.
             *
             * @return Zero if the variable was not found. Otherwise it returns the priority of the
             *         (first) plug-in that contained the variable.
             *         This way, the caller might identify from which configuration
             *         source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int Get( Object category, Object name, out int target, AString temp= null )
            {
                target= 0;
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                foreach ( PluginAndPrio pap in plugins )
                    if ( pap.plugIn.Get( category, name, out target, temp ) )
                        return pap.prio;

                return 0;
            }

            /** ************************************************************************************
             * Retrieves a floating point value from the configuration settings. This is done by asking
             * each of  the installed plug-ins. As soon as the first one returns a value for
             * the given variable
             * @param category  The category of the  variable.
             *                  (AString compatible type expected.)
             * @param name      The name of the configuration variable to be retrieved.
             *                  (AString compatible type expected.)
             * @param target    A reference to an double variable to take the result.
             * @param temp      A buffer to temporarily store the value for parsing.
             *                  Defaults to null. Provide a local object to gain performance when
             *                  retrieving many variables in a row.
             *
             * @return Zero if the variable was not found. Otherwise it returns the priority of the
             *         (first) plug-in that contained the variable.
             *         This way, the caller might identify from which configuration
             *         source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int Get( Object category, Object name, out double target, AString temp= null )
            {
                target= 0.0;
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                foreach ( PluginAndPrio pap in plugins )
                    if ( pap.plugIn.Get( category, name, out target, temp ) )
                        return pap.prio;

                return 0;
            }

            /** ************************************************************************************
             * Utility method that checks if a given value represents 'true'.
             * @param value  The value to check
             *
             * @return   Returns \c true, if the value represents 'true', \c false if not.
             **************************************************************************************/
            public bool  IsTrue( AString value )
            {
                foreach ( AString s in TrueValues )
                    if ( value.Equals( s, Case.Ignore ) )
                        return true;

                return false;
            }

            /** ************************************************************************************
             * Utility method that checks if a given value represents 'true'.
             * @param value  The value to check
             *
             * @return   Returns \c true, if the value represents 'true', \c false if not.
             **************************************************************************************/
            public bool  IsTrue( Substring value )
            {
                foreach ( AString s in TrueValues )
                    if ( value.Equals( s, Case.Ignore ) )
                        return true;

                return false;
            }

            /** ************************************************************************************
             * Uses
             * \ref Get(Object, Object,AString) "Get"
             * to read a string value and returns true if this variable holds one of the
             * values found in the #TrueValues string list. By default, this string list contains
             * the strings "true", "yes" and "1" (case insensitive comparison).
             * @param category       The category of the  variable.
             *                       (AString compatible type expected.)
             * @param name           The name of the environment variable to read
             *                       (AString compatible type expected.)
             * @param pluginPriority An optional pointer to an integer. If set, the priority of the
             *                       plug-in which returned the configuration value will be stored
             *                       here. This way, the caller can identify if the variable
             *                       was defined at all (if false was returned) or even from which
             *                       configuration source the variable was read.
             * @param temp           A buffer to temporarily store the value for parsing.
             *                       Defaults to null. Provide a local object to gain performance
             *                       when retrieving many variables in a row.
             *
             * @return   Returns true, if the environment variable is defined and has one of the
             *           values found in field #TrueValues.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public bool  IsTrue( Object category, Object name, out int pluginPriority,  AString temp= null )
            {
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                if ( (pluginPriority= Get( category, name, temp )) != 0 )
                    return IsTrue( temp );

                return false;
            }

            /** ************************************************************************************
             * Uses
             * \ref Get(Object, Object,AString) "Get"
             * to read a string value and returns true if this variable holds one of the
             * values found in the #TrueValues string list. By default, this string list
             * contains the strings "true", "yes" and "1" (case insensitive comparison).
             * @param category       The category of the  variable.
             *                       (AString compatible type expected.)
             * @param name           The name of the environment variable to read
             *                       (AString compatible type expected.)
             * @param temp           A buffer to temporarily store the value for parsing.
             *                       Defaults to null. Provide a local object to gain performance
             *                       when retrieving many variables in a row.
             *
             * @return   Returns true, if the environment variable is defined and has one of the
             *           values found in field #TrueValues.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public bool  IsTrue( Object category, Object name, AString temp= null)
            {
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                if ( Get( category, name, temp ) != 0 )
                    return IsTrue( temp );

                return false;
            }

            /** ************************************************************************************
             * Writes the string variable to the configuration. This is done by asking each of our
             * installed plug-ins to do so. As soon as the first one returns 'true', the variable
             * is considered written and no other plug-ins are asked. This way, the pair of
             * variable/value is stored within the configuration type with the lowest possible
             * priory (e.g. user configuration vs. system wide configuration).
             * @param category  The category of the  variable.
             *                  (AString compatible type expected.)
             * @param name      The name of the configuration variable to be retrieved.
             *                  (AString compatible type expected.)
             * @param value     The value to write.
             * @param comments  Comment lines that might be added in the configuration storage
             *                  (plug-in implementation dependent). Optional and defaults to null.
             * @param delim     This optional parameter should be provided for variables that are
             *                  supposed to get long values that represent a list of delimited
             *                  fields. <br>
             *                  The use of this character is specific to a plug-ins'
             *                  implementation.
             *                  Defaults to '\0'.
             *
             * @return Zero if the variable was not written. Otherwise it returns the priority of
             *         the (first) plug-in that wrote the variable.
             *         This way, the caller might identify into which configuration
             *         source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int  Save( Object category, Object name,
                              Object value,    Object comments= null,
                              char delim= ',' )
            {
                foreach ( PluginAndPrio pap in plugins )
                    if ( pap.plugIn.Save( category, name, value, comments, delim ) )
                        return pap.prio;
                return 0;
            }


            /** ************************************************************************************
             * Writes the integer variable to the configuration. This is done by asking each of our
             * installed plug-ins to do so. As soon as the first one returns 'true', the variable
             * is considered written and no other plug-ins are asked. This way, the pair of
             * variable/value is stored within the configuration type with the lowest possible
             * priory (e.g. user configuration vs. system wide configuration).
             * @param category  The category of the  variable.
             *                  (AString compatible type expected.)
             * @param name      The name of the configuration variable to be retrieved.
             *                  (AString compatible type expected.)
             * @param value     The value to write.
             * @param comments  Comment lines that might be added in the configuration storage
             *                  (plug-in implementation dependent). Optional and defaults to null.
             * @param temp      A buffer to temporarily store the value.
             *                  Defaults to null. Provide a local object to gain performance when
             *                  retrieving many variables in a row.
             *
             * @return Zero if the variable was not written. Otherwise it returns the priority of
             *         the (first) plug-in that wrote the variable.
             *         This way, the caller might identify into which configuration
             *         source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int  Save( Object category, Object name, int value,
                              Object comments= null, AString temp= null                     )
            {
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                foreach ( PluginAndPrio pap in plugins )
                    if ( pap.plugIn.Save( category, name, value, comments, temp ) )
                        return pap.prio;
                return 0;
            }


            /** ************************************************************************************
             * Writes the double variable to the configuration. This is done by asking each of our
             * installed plug-ins to do so. As soon as the first one returns 'true', the variable
             * is considered written and no other plug-ins are asked. This way, the pair of
             * variable/value is stored within the configuration type with the lowest possible
             * priory (e.g. user configuration vs. system wide configuration).
             * @param category  The category of the  variable.
             *                  (AString compatible type expected.)
             * @param name      The name of the configuration variable to be retrieved.
             *                  (AString compatible type expected.)
             * @param value     The value to write.
             * @param comments  Comment lines that might be added in the configuration storage
             *                  (plug-in implementation dependent). Optional and defaults to null.
             * @param temp      A buffer to temporarily store the value.
             *                  Defaults to null. Provide a local object to gain performance when
             *                  retrieving many variables in a row.
             *
             * @return Zero if the variable was not written. Otherwise it returns the priority of
             *         the (first) plug-in that wrote the variable.
             *         This way, the caller might identify into which configuration
             *         source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int  Save( Object category, Object name, double value,
                              Object comments= null, AString temp= null                        )
            {
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                foreach ( PluginAndPrio pap in plugins )
                    if ( pap.plugIn.Save( category, name, value, comments, temp ) )
                        return pap.prio;

                return 0;
            }
    } // class

}// namespace

