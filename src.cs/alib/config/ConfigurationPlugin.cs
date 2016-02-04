// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Text;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;

namespace cs.aworx.lib.config  {

    /** ********************************************************************************************
     *  Abstract class that represents a plug in for class
     *  \ref aworx::lib::config::Configuration "Configuration"
     *  to provide configuration data from specific configuration data source.
     *
     *  Different attached plug-ins of type #ConfigurationPlugIn differentiate in their priority.
     *  This way, certain configuration methods can 'overwrite' values from other sources. See
     *  #cs::aworx::lib::config for more information on priorities.
     *
     *  The plug-in also may have the ability to write data. The default implementation for writing
     *  configuration data returns constant false, indicating that this plug-in never writes
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
     *  the category and the variable name with an underscore '_'. This means, if variable <em>IDE</em>
     *  in category <em>ALIB</em> is accessed, those plug-ins would check command line parameter
     *  <em>--ALIB_IDE=xyz</em> respectively environment variable <em>ALIB_IDE</em>
     *
     *  Some method of this class accept parameters of type <em>Object</em>. In this case, the
     *  following string types are accepted:
     *  - String
     *  - char[]
     *  - \ref cs::aworx::lib::strings::AString    "AString"
     *  - \ref cs::aworx::lib::strings::Substring  "Substring"
     **********************************************************************************************/
    public abstract class ConfigurationPlugIn
    {
        /** ****************************************************************************************
         *  The configuration object we got attached to.
         ******************************************************************************************/
        public Configuration         Parent                                                  =null;

        /** ****************************************************************************************
         *  Constructor which is protected, as this is an abstract class.
         ******************************************************************************************/
        protected ConfigurationPlugIn() {}


        /** ****************************************************************************************
         *  Abstract method that has to be overwritten by descendants.
         *  Retrieves the string value of a configuration setting.
         *  @param category  The category of the  variable.
         *                   (AString compatible type expected.)
         *  @param name      The name of the configuration variable to be retrieved.
         *                   (AString compatible type expected.)
         *  @param target    A reference to an empty AString to take the result.
         *  @return true if variable was found within this configuration source, false if not.
         ******************************************************************************************/
        public abstract bool  Get( Object category, Object name, AString target );

        /** ****************************************************************************************
         *  Retrieves the int value of a configuration setting. This default implementation
         *  invokes %Get(String , String , AString)
         *  and converts the value to type integer.
         *  Descendants might overwrite this method.
         *  @param category  The category of the  variable.
         *                   (AString compatible type expected.)
         *  @param name      The name of the configuration variable to be retrieved.
         *                   (AString compatible type expected.)
         *  @param target    A reference to an integer variable to take the result.
         *  @param temp      A buffer to temporarily store the value for parsing.
         *  @return true if variable was found within this configuration source, false if not.
         ******************************************************************************************/
        public virtual bool  Get( Object category, Object name, ref int target, AString temp )
        {
            if ( temp == null )
                temp= new AString();
            else
                temp.Clear();

            target= 0;
            if ( !Get( category, name, temp ) )
                return false;

            target= (int) temp.ToInt();
            return true;
        }


        /** ****************************************************************************************
         *  Retrieves the floating point value of a configuration setting.
         *  This default implementation invokes the %Get(String , String , AString) and converts
         *  the value to type double.
         *  Descendants might overwrite this method.
         *
         *  \note The conversion to double ignores the current locale setting and expects either a
         *        dot ('.') or a comma (',') as decimal operator. On the same token,the
         *        corresponding method #Save(Object, Object, double, Object, AString)
         *        writes always dots as separator characters, independent from local settings.
         *
         *  @param category  The category of the  variable.
         *                   (AString compatible type expected.)
         *  @param name      The name of the configuration variable to be retrieved.
         *                   (AString compatible type expected.)
         *  @param target    A reference to an double variable to take the result.
         *  @param temp      A buffer to temporarily store the value for parsing.
         *  @return true if variable was found within this configuration source, false if not.
         ******************************************************************************************/
        public virtual bool  Get( Object category, Object name, ref double target, AString temp  )
        {
            target= 0.0;

            if ( temp == null ) temp= new AString(); else  temp.Clear();

            if ( !Get( category, name, temp ) )
                return false;

            int dummy;
            target= temp.ToFloat( 0, out dummy, Parent != null ? Parent.NumberFormat : NumberFormat.Global );
            return true;
        }


        /** ****************************************************************************************
         *  Writes a string value to the configuration.
         *  This default implementation just returns false. If this method is not overwritten
         *  in descendants, those descendants are not designed to write data.
         *
         *  @param category  The category of the  variable.
         *                   (AString compatible type expected.)
         *  @param name      The name of the configuration variable to be retrieved.
         *                   (AString compatible type expected.)
         *  @param value     The value to write.
         *  @param comments  Comment lines that might be added in the configuration storage
         *                   (plug-in implementation dependent).
         *  @param delim     This parameter might be provided for variables that are
         *                   supposed to get long values that represent a list of delimited fields.
         *                   <br>The use of this character is specific to a plug-ins'
         *                   implementation.
         *
         *  @return true if the variable was written, false if not.
         ******************************************************************************************/
        public virtual bool Save( Object category,  Object   name,
                                  Object value,     Object   comments,
                                  char    delim                         )
        {
            return false;
        }

        /** ****************************************************************************************
         *  Writes an integer variable to the configuration.
         *  This default implementation converts the value to a string and invokes
         *  the string version of method %Save().
         *
         *  @param category  The category of the  variable.
         *                   (AString compatible type expected.)
         *  @param name      The name of the configuration variable to be retrieved.
         *                   (AString compatible type expected.)
         *  @param value     The value to write.
         *  @param comments  Comment lines that might be added in the configuration storage
         *                   (plug-in implementation dependent).
         *  @param temp      A buffer to temporarily store the value.
         *
         *  @return true if the variable was written, false if not.
         ******************************************************************************************/
        public bool Save( Object category, Object name, int value, Object comments, AString temp  )
        {
            if ( temp == null ) temp= new AString(); else  temp.Clear();
            temp._( value );
            return Save( category, name, temp, comments, '\0' );
        }


        /** ****************************************************************************************
         *  Writes a floating point variable to the configuration.
         *  This default implementation converts the value to a string and invokes
         *  the string version of method %Save().
         *
         *  \note The floating point to string conversion ignores the current locale setting and
         *        writes a dot ('.') as decimal operator. On the same token, the corresponding
         *        method #Get(Object, Object, ref double, AString )
         *        accepts both, a dot or a comma (',').
         *
         *  @param category  The category of the  variable.
         *                   (AString compatible type expected.)
         *  @param name      The name of the configuration variable to be retrieved.
         *                   (AString compatible type expected.)
         *  @param value     The value to write.
         *  @param comments  Comment lines that might be added in the configuration storage
         *                   (plug-in implementation dependent).
         *  @param temp      A buffer to temporarily store the value.
         *
         *  @return true if the variable was written, false if not.
         ******************************************************************************************/
        public virtual bool  Save( Object category, Object name, double value, Object comments, AString temp  )
        {
            if ( temp == null ) temp= new AString(); else  temp.Clear();
            temp._( value, Parent != null ? Parent.NumberFormat : NumberFormat.Global );
            return Save( category, name, temp, comments, '\0' );
        }

    };

    /** ********************************************************************************************
     *  Specialization of abstract interface class #ConfigurationPlugIn, which takes all command
     *  line parameters in the constructor and reads variable values from those parameters
     *  on request. Its priority value is fixed to 10.
     *
     *  Variable categories are used as a prefix together with an underscore '_'.
     *  This means, if variable <em>IDE</em> in category <em>ALIB</em> is accessed, the command
     *  line parameter <em>--ALIB_IDE=xyz</em> is read.
     *
     *  Command line variables may be passed with either one hyphen ('-') or two ('--').
     *  Both are accepted.
     *
     *  Category and Variable names are insensitive in respect to character case.
     **********************************************************************************************/
    public class CommandLinePlugIn : ConfigurationPlugIn
    {

        protected  String[]   args;  ///< the list of command line arguments


        /** ****************************************************************************************
         *  Constructor which takes the standard C main() function parameters as arguments
         *  @param args  The list of command line arguments.
         ******************************************************************************************/
        public CommandLinePlugIn( String[] args )   { this.args= args; }

        /** ****************************************************************************************
         *  Retrieves the string value of a configuration setting.
         *  @param category  The category of the  variable.
         *                   (AString compatible type expected.)
         *  @param name      The name of the configuration variable to be retrieved.
         *                   (AString compatible type expected.)
         *  @param target    A reference to an empty AString to take the result.
         *  @return true if variable was found within this configuration source, false if not.
         ******************************************************************************************/
       public override
        bool  Get( Object category, Object name, AString target )
        {
            // assemble option name as CATEGORY_NAME
            target.Clear()._( category );
            if ( target.IsNotEmpty() )
                target._( '_' );
            target._( name );


            int   optionLength=   target.Length();
            Substring actVar=     new Substring();

            for ( int i= 0; i < args.Length ; i++ )
            {
                // remove whitespaces (if somebody would work with quotation marks...)
                actVar.Set( args[i] ).Trim();

                // request '-' and allow a second '-'
                if ( !actVar.Consume('-') )
                    continue;
                actVar.Consume( '-' );

                if ( target.CompareTo( args[i], Case.Ignore, actVar.Start, optionLength, 0, optionLength ) == 0)
                {
                    //again, lets trim before searching the = sign (really almost unnecessary)
                    actVar.Start+= optionLength;
                    if ( actVar.Consume( '=', Whitespaces.Trim ) )
                    {
                        actVar.TrimStart();
                        actVar.TrimEnd();
                        target.Clear();
                        target._NC( args[i], actVar.Start, actVar.Length() );
                        return true;
                    }
                 }
            }

            return false;
        }

    };

    /** ********************************************************************************************
     *  Specialization of abstract interface class #ConfigurationPlugIn, retrieves configuration
     *  data from the system environment.
     *
     *  This plug-ins' priority value is fixed to 10.
     *
     *  Variable categories are used as a prefix together with an underscore '_'.
     *  This means, if variable <em>IDE</em> in category <em>ALIB</em> is accessed, the
     *  environment variable <em>ALIB_IDE</em> is read.
     *
     *  Category and Variable names are insensitive in respect to character case.
     **********************************************************************************************/
    public class EnvironmentPlugIn : ConfigurationPlugIn
    {
        /** ****************************************************************************************
         *  Constructor.
         ******************************************************************************************/
        public EnvironmentPlugIn() {}

        /** ****************************************************************************************
         *  Retrieves the string value of a configuration setting.
         *  @param category  The category of the  variable.
         *                   (AString compatible type expected.)
         *  @param name      The name of the configuration variable to be retrieved.
         *                   (AString compatible type expected.)
         *  @param target    A reference to an empty AString to take the result.
         *  @return true if variable was found within this configuration source, false if not.
         ******************************************************************************************/

        public override
        bool  Get( Object category, Object name, AString target )
        {
            target.Clear()._( category );
            if ( target.IsNotEmpty() )
                target._( '_' );
            target._( name );

            target.ToUpper();

            String env= System.Environment.GetEnvironmentVariable( target.ToString() );
            target.Clear()._( env );
            target.Trim();
            return target.IsNotEmpty();
        }
    };



} // namespace / EOF
