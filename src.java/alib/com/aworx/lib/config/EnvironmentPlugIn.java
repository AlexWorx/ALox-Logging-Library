// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import com.aworx.lib.strings.AString;

/** ************************************************************************************************
 *  Specialization of abstract interface class #ConfigurationPlugIn, retrieves configuration 
 *  data from the system environment.
 *  
 *  This plug-ins' priority value is fixed to 10.
 * 
 *  Variable categories are used as a prefix together with an underscore '_'.
 *  This means, if variable <em>IDE</em> in category <em>ALIB</em> is accessed, the environment
 *  variable <em>ALIB_IDE</em> is read.
 * 
 *  Category and Variable names are insensitive in respect to character case.
 **************************************************************************************************/
public class EnvironmentPlugIn extends ConfigurationPlugIn
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

    @Override
    public boolean  get( CharSequence category, CharSequence name, AString target )
    {
        target.clear()._( category );
        if ( target.isNotEmpty() )
            target._( '_' );
        target._( name );

        target.toUpper();

        String env= System.getenv( target.toString() );

        target.clear()._( env );
        target.trim();
        return target.isNotEmpty();
    }
};



