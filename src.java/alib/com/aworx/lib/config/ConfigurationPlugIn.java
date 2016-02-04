// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.NumberFormat;


/** ************************************************************************************************
 *  Abstract class that represents a plug in for class
 *  \ref aworx::lib::config::Configuration "Configuration"
 *  to provide configuration data from specific configuration data source.
 *
 *  Different attached plug-ins of type #ConfigurationPlugIn differentiate in their priority. This
 *  way, certain configuration methods can 'overwrite' values from other sources. See
 *  \ref com::aworx::lib::config for more information on priorities.
 *
 *  The plug-in also may have the ability to write data. The default implementation for writing
 *  configuration data returns constant false, indicating that this plug-in never writes
 *  anything (e.g. command line parameter plug-in, environment variable plug-in).
 *
 *  Category and Variable names are character case insensitive for the built-in
 *  ConfigurationPlugIn types
 *  \ref com::aworx::lib::config::EnvironmentPlugIn "EnvironmentPlugIn"
 *  and
 *  \ref aworx::lib::config::CommandLinePlugIn "CommandLinePlugIn".
 *  It is recommended to to ignore character case in custom specializations of class
 *  \ref com::aworx::lib::config::ConfigurationPlugIn "ConfigurationPlugIn" 
 *  as well.
 *
 *  Variables belong to categories. The built-in ConfigurationPlugIns types
 *  CommandLinePlugIn and EnvironmentPlugIn just concatenate
 *  the category and the variable name with an underscore '_'. This means, if variable <em>IDE</em>
 *  in category <em>ALIB</em> is accessed, those plug-ins would check command line parameter
 *  <em>--ALIB_IDE=xyz</em> respectively environment variable <em>ALIB_IDE</em>
 **************************************************************************************************/
public abstract class ConfigurationPlugIn
{
    /** ****************************************************************************************
     *  The configuration object we got attached to.
     ******************************************************************************************/
    public Configuration         parent                                                =null;

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
    public abstract boolean  get( CharSequence category, CharSequence name, AString target );

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
    public boolean  get( CharSequence category, CharSequence name, int[] target, AString temp )
    {
        target[0]= 0;
        if ( temp == null ) temp= new AString(); else  temp.clear();

        if ( !get( category, name, temp ) )
            return false;

        target[0]= temp.toInt();
        return true;
    }


    /** ****************************************************************************************
     *  Retrieves the floating point value of a configuration setting. This default implementation
     *  invokes the %Get(String , String , AString)
     *  and converts the value to type double.
     *  Descendants might overwrite this method.
     *
     *  \note The conversion to double ignores the current locale setting and expects either a 
     *        dot ('.') or a comma (',') as decimal operator. On the same token,the corresponding 
     *        method #save(CharSequence, CharSequence, double, CharSequence, AString) 
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
    public boolean  get( CharSequence category, CharSequence name, double[] target, AString temp  )
    {
        target[0]= 0.0;

        if ( temp == null ) temp= new AString(); else  temp.clear();

        if ( !get( category, name, temp ) )
            return false;

        target[0]= temp.toFloat( 0, null, parent != null ? parent.numberFormat : NumberFormat.global );
        return true;
    }


    /** ****************************************************************************************
     *  Writes an AString variable to the configuration.
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
    public boolean save( CharSequence category,  CharSequence   name,
                         CharSequence value,     CharSequence   comments,
                         char         delim                                 )
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
    public boolean save( CharSequence category, CharSequence name, int value, CharSequence comments, AString temp  )
    {
        if ( temp == null ) temp= new AString(); else  temp.clear();
        temp._( value );
        return save( category, name, temp, comments, '\0' );
    }



    /** ****************************************************************************************
     *  Writes a floating point variable to the configuration.
     *  This default implementation converts the value to a string and invokes
     *  the string version of method %Save().
     *
     *  \note The floating point to string conversion ignores the current locale setting and
     *        writes a dot ('.') as decimal operator. On the same token, the corresponding method
     *        #get(CharSequence, CharSequence, double[], AString ) 
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
    public boolean  save( CharSequence category, CharSequence name, double value, CharSequence comments, AString temp  )
    {
        if ( temp == null ) temp= new AString(); else  temp.clear();
        temp._( value, parent != null ? parent.numberFormat : NumberFormat.global );
        return save( category, name, temp, comments, '\0' );
    }

};




