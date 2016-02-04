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
 * \note Instead of using the provided class IniFile class, it is recommended to use
 * application/platform specific mechanisms for writing configuration data. The INI file method
 * is designed for simplicity and smaller applications.
 **************************************************************************************************/
namespace cs.aworx.lib.config  {


    // #############################################################################################
    // class Configuration
    // #############################################################################################

    /** ********************************************************************************************
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
     *  that uses appropriate configuration techniques (ini-files, registry entries, etc.)
     *  optionally completes this set.
     *  It is proposed to use a priority value of 30 for for custom configuration plug-ins.
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
     *
     *  Some method of this class accept parameters of type <em>Object</em>. In this case, the
     *  following string types are accepted:
     *  - String
     *  - char[]
     *  - \ref cs::aworx::lib::strings::AString          "AString"
     *  - \ref cs::aworx::lib::strings::Substring  "Substring"
     **********************************************************************************************/

    public class Configuration
    {
        // #########################################################################################
        // internal fields
        // #########################################################################################

            /** An element of the list of plug-ins with their priority */
            public class PrioAndPlugin
            {
                /** The priority that was defined when the plug-in was added. */
                public int                   prio;

                /** The plug-in. */
                public ConfigurationPlugIn   plugIn;
            }

            /// The plug-ins we have in our portfolio
            protected  List<PrioAndPlugin>   plugins;


        // #########################################################################################
        // public fields
        // #########################################################################################
            /** Values considered to indicate "true". Defaults to "1", "true", "yes" and "ok".
             *  Comparisons are made case insensitive.
             *
             *  Application specific values (e.g. localization languages) might be added by publicly
             *  accessing this field and adding new values (or removing existing).
             */
            public  List<AString>               TrueValues;

            /** The configuration plug-in for command line parameters. Created in the constructor.
             *  Provided as public field here, for flexibility. Please note:
             *  When this object is replaced by a customized one, it also has to be added to the
             *  the list of plug-ins (and any existing one has to be removed).
             */
            public CommandLinePlugIn            CmdLineCP;

            /** The environment plug-in for evaluation of system environment variables.
             *  Created in the constructor.
             *  Provided as public field here, for flexibility. Please note:
             *  When this object is replaced by a customized one, it also has to be added to the
             *  the list of plug-ins (and any existing one has to be removed).
             */
            public EnvironmentPlugIn            EnvCP;

            /** Number format definition used by plugins to write int and float values.  */
            public NumberFormat                 NumberFormat=               new NumberFormat();


        // #########################################################################################
        // Constructor/destructor
        // #########################################################################################
            /** ************************************************************************************
             *  Constructs a configuration plug-in and optionally (default) creates two initial
             *  plug-ins, one that reads command line options, a second that uses the process
             *  environment as configuration source.
             *  @param useEnv  If true (default), an EnvironmentPlugIn is created
             *                 and attached. To specify false here, might be useful, if a customized
             *                 ConfigurationPlugIn that reads environment variables will be attached.
             *  @param args    Parameters taken from standard C main() method (the list of command
             *                 line arguments). Defautls to null.
             **************************************************************************************/
            public Configuration( bool useEnv= true, String[] args= null )
            {
                plugins=        new List<PrioAndPlugin>();

                // set default true values
                TrueValues=     new List<AString>();
                TrueValues.Add( new AString( "1" )    );
                TrueValues.Add( new AString( "true" ) );
                TrueValues.Add( new AString( "yes" )  );
                TrueValues.Add( new AString( "ok" )   );

                // create command line plug-in
                if ( args != null && args.Length > 0 )
                {
                    CmdLineCP= new CommandLinePlugIn ( args );
                    InsertPlugin( CmdLineCP, 10 );
                }

                // environment config plug-in
                if ( useEnv )
                {
                    EnvCP= new EnvironmentPlugIn();
                    InsertPlugin( EnvCP,    20 );
                }

            }

        // #########################################################################################
        // interface
        // #########################################################################################

            /** ************************************************************************************
             *  Adds the given plug-in to the list of plug-ins used to query configuration values.
             *  @param plugin   The plug-in to insert.
             *  @param priority The priority of the plug-in.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public void InsertPlugin( ConfigurationPlugIn plugin, int priority )
            {
                int i;
                for ( i= 0; i < plugins.Count; i++ )
                {
                    if ( plugins[i].prio > priority )
                        break;
                }

                PrioAndPlugin pap=  new PrioAndPlugin();
                pap.plugIn=         plugin;
                pap.prio=           priority;
                plugins.Insert( i, pap );

                plugin.Parent= this;
            }

            /** ************************************************************************************
             *  Remove the given plug-in from the list of plug-ins.
             *  Responsibility for deletion of removed plug-ins moves to the remover.
             *  Active (inserted) plug-ins get deleted by class' destructor.
             *  @param plugin  The plug-in to be deleted.
             *  @return true if the plug-in was removed, else false.
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
             *  Retrieves a string value from the configuration settings. This is done by asking
             *  each of the installed plug-ins. As soon as the first one returns a value for the
             *  given variable name, this value is returned.
             *  All variable names are case insensitive.
             *  @param category  The category of the  variable.
             *                   (AString compatible type expected.)
             *  @param name      The name of the configuration variable to be retrieved.
             *                   (AString compatible type expected.)
             *  @param target    A reference to an AString to take the result.
             *                   This AString will be cleared, no matter if a configuration
             *                   variable was found or not.
             *
             *  @return Zero if the variable was not found. Otherwise it returns the priority of the
             *          (first) plug-in that contained the variable.
             *          This way, the caller might identify from which configuration
             *          source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int Get( Object category, Object name, AString target )
            {
                target.Clear();

                foreach ( PrioAndPlugin pap in plugins )
                    if ( pap.plugIn.Get( category, name, target ) )
                        return pap.prio;

                return 0;
            }

            /** ************************************************************************************
             *  Retrieves an integer value from the configuration settings. This is done by asking
             *  each of the installed plug-ins. As soon as the first one returns a value for
             *  the given variable name, this value is returned.
             *  All variable names are case insensitive.
             *  @param category  The category of the  variable.
             *                   (AString compatible type expected.)
             *  @param name      The name of the configuration variable to be retrieved.
             *                   (AString compatible type expected.)
             *  @param target    A reference to an integer variable to take the result.
             *  @param temp      A buffer to temporarily store the value for parsing.
             *                   Defaults to null. Provide a local object to gain performance when
             *                   retrieving many variables in a row.
             *
             *  @return Zero if the variable was not found. Otherwise it returns the priority of the
             *          (first) plug-in that contained the variable.
             *          This way, the caller might identify from which configuration
             *          source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int Get( Object category, Object name, ref int target, AString temp= null )
            {
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                foreach ( PrioAndPlugin pap in plugins )
                    if ( pap.plugIn.Get( category, name, ref target, temp ) )
                        return pap.prio;

                return 0;
            }

            /** ************************************************************************************
             *  Retrieves a floating point value from the configuration settings. This is done by asking
             *  each of  the installed plug-ins. As soon as the first one returns a value for
             *  the given variable
             *  @param category  The category of the  variable.
             *                   (AString compatible type expected.)
             *  @param name      The name of the configuration variable to be retrieved.
             *                   (AString compatible type expected.)
             *  @param target    A reference to an double variable to take the result.
             *  @param temp      A buffer to temporarily store the value for parsing.
             *                   Defaults to null. Provide a local object to gain performance when
             *                   retrieving many variables in a row.
             *
             *  @return Zero if the variable was not found. Otherwise it returns the priority of the
             *          (first) plug-in that contained the variable.
             *          This way, the caller might identify from which configuration
             *          source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int Get( Object category, Object name, ref double target, AString temp= null )
            {
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                foreach ( PrioAndPlugin pap in plugins )
                    if ( pap.plugIn.Get( category, name, ref target, temp ) )
                        return pap.prio;

                return 0;
            }

            /** ************************************************************************************
             *  Uses
             *  \ref Get(Object, Object,AString) "Get"
             *  to read a string value and returns true if this variable holds one of the
             *  values found in the #TrueValues string list. By default, this string list contains
             *  the strings "true", "yes" and "1" (case insensitive comparison).
             *  @param category       The category of the  variable.
             *                        (AString compatible type expected.)
             *  @param name           The name of the environment variable to read
             *                        (AString compatible type expected.)
             *  @param pluginPriority An optional pointer to an integer. If set, the priority of the
             *                        plug-in which returned the configuration value will be stored
             *                        here. This way, the caller can identify if the variable
             *                        was defined at all (if false was returned) or even from which
             *                        configuration source the variable was read.
             *  @param temp           A buffer to temporarily store the value for parsing.
             *                        Defaults to null. Provide a local object to gain performance
             *                        when retrieving many variables in a row.
             *
             *  @return   Returns true, if the environment variable is defined and has one of the
             *            values found in field #TrueValues.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public bool  IsTrue( Object category, Object name, ref int pluginPriority,  AString temp= null )
            {
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                if ( (pluginPriority= Get( category, name, temp )) != 0 )
                    foreach ( AString s in TrueValues )
                        if ( temp.Equals( s, Case.Ignore ) )
                            return true;

                return false;
            }

            /** ************************************************************************************
             *  Uses
             *  \ref Get(Object, Object,AString) "Get"
             *  to read a string value and returns true if this variable holds one of the
             *  values found in the #TrueValues string list. By default, this string list
             *  contains the strings "true", "yes" and "1" (case insensitive comparison).
             *  @param category       The category of the  variable.
             *                        (AString compatible type expected.)
             *  @param name           The name of the environment variable to read
             *                        (AString compatible type expected.)
             *  @param temp           A buffer to temporarily store the value for parsing.
             *                        Defaults to null. Provide a local object to gain performance
             *                        when retrieving many variables in a row.
             *
             *  @return   Returns true, if the environment variable is defined and has one of the
             *            values found in field #TrueValues.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public bool  IsTrue( Object category, Object name, AString temp= null)
            {
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                if ( Get( category, name, temp ) != 0 )
                    foreach ( AString s in TrueValues )
                        if ( temp.Equals( s, Case.Ignore ) )
                            return true;

                return false;
            }

            /** ************************************************************************************
             *  Writes the string variable to the configuration. This is done by asking each of our
             *  installed plug-ins to do so. As soon as the first one returns 'true', the variable
             *  is considered written and no other plug-ins are asked. This way, the pair of
             *  variable/value is stored within the configuration type with the lowest possible
             *  priory (e.g. user configuration vs. system wide configuration).
             *  @param category  The category of the  variable.
             *                   (AString compatible type expected.)
             *  @param name      The name of the configuration variable to be retrieved.
             *                   (AString compatible type expected.)
             *  @param value     The value to write.
             *  @param comments  Comment lines that might be added in the configuration storage
             *                   (plug-in implementation dependent). Optional and defaults to null.
             *  @param delim     This optional parameter should be provided for variables that are
             *                   supposed to get long values that represent a list of delimited
             *                   fields. <br>
             *                   The use of this character is specific to a plug-ins'
             *                   implementation.
             *                   Defaults to '\0'.
             *
             *  @return Zero if the variable was not written. Otherwise it returns the priority of
             *          the (first) plug-in that wrote the variable.
             *          This way, the caller might identify into which configuration
             *          source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int  Save( Object category, Object name,
                              Object value,    Object comments= null,
                              char delim= ',' )
            {
                foreach ( PrioAndPlugin pap in plugins )
                    if ( pap.plugIn.Save( category, name, value, comments, delim ) )
                        return pap.prio;
                return 0;
            }


            /** ************************************************************************************
             *  Writes the integer variable to the configuration. This is done by asking each of our
             *  installed plug-ins to do so. As soon as the first one returns 'true', the variable
             *  is considered written and no other plug-ins are asked. This way, the pair of
             *  variable/value is stored within the configuration type with the lowest possible
             *  priory (e.g. user configuration vs. system wide configuration).
             *  @param category  The category of the  variable.
             *                   (AString compatible type expected.)
             *  @param name      The name of the configuration variable to be retrieved.
             *                   (AString compatible type expected.)
             *  @param value     The value to write.
             *  @param comments  Comment lines that might be added in the configuration storage
             *                   (plug-in implementation dependent). Optional and defaults to null.
             *  @param temp      A buffer to temporarily store the value.
             *                   Defaults to null. Provide a local object to gain performance when
             *                   retrieving many variables in a row.
             *
             *  @return Zero if the variable was not written. Otherwise it returns the priority of
             *          the (first) plug-in that wrote the variable.
             *          This way, the caller might identify into which configuration
             *          source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int  Save( Object category, Object name, int value,
                              Object comments= null, AString temp= null                     )
            {
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                foreach ( PrioAndPlugin pap in plugins )
                    if ( pap.plugIn.Save( category, name, value, comments, temp ) )
                        return pap.prio;
                return 0;
            }


            /** ************************************************************************************
             *  Writes the double variable to the configuration. This is done by asking each of our
             *  installed plug-ins to do so. As soon as the first one returns 'true', the variable
             *  is considered written and no other plug-ins are asked. This way, the pair of
             *  variable/value is stored within the configuration type with the lowest possible
             *  priory (e.g. user configuration vs. system wide configuration).
             *  @param category  The category of the  variable.
             *                   (AString compatible type expected.)
             *  @param name      The name of the configuration variable to be retrieved.
             *                   (AString compatible type expected.)
             *  @param value     The value to write.
             *  @param comments  Comment lines that might be added in the configuration storage
             *                   (plug-in implementation dependent). Optional and defaults to null.
             *  @param temp      A buffer to temporarily store the value.
             *                   Defaults to null. Provide a local object to gain performance when
             *                   retrieving many variables in a row.
             *
             *  @return Zero if the variable was not written. Otherwise it returns the priority of
             *          the (first) plug-in that wrote the variable.
             *          This way, the caller might identify into which configuration
             *          source the variable was read.
             **************************************************************************************/
            [MethodImpl(MethodImplOptions.Synchronized)]
            public int  Save( Object category, Object name, double value,
                              Object comments= null, AString temp= null                        )
            {
                if ( temp == null )
                    temp= new AString();
                else
                    temp.Clear();

                foreach ( PrioAndPlugin pap in plugins )
                    if ( pap.plugIn.Save( category, name, value, comments, temp ) )
                        return pap.prio;

                return 0;
            }
    } // class

}// namespace

