// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import com.aworx.lib.strings.AString;

/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugin, retrieves configuration
 * data from the system environment.
 *
 * This plug-ins' priority value is fixed to 10.
 *
 * Variable categories are used as a prefix together with an underscore '_'.
 * This means, if variable <em>LOCALE</em> in category <em>ALIB</em> is accessed, the environment
 * variable <em>ALIB_LOCALE</em> is read.
 *
 * Category and Variable names are insensitive in respect to character case.
 **************************************************************************************************/
public class EnvironmentPlugin extends ConfigurationPlugin
{
    protected  AString    tmpAS= new AString();    ///< A temporary string to reuse.

    /** ****************************************************************************************
     * Constructor.
     ******************************************************************************************/
    public EnvironmentPlugin() {}

    /** ****************************************************************************************
     * Searches the variable in the environment.
     *
     * @param variable      The variable to retrieve.
     * @param searchOnly    If \c true, the variable is not set. Defaults to \c false.
     * @return \c true if variable was found, \c false if not.
     ******************************************************************************************/
    @Override
    public boolean  load( Variable variable, boolean searchOnly )
    {
        tmpAS._()._( variable.fullname ).toUpper();

        String env= System.getenv( tmpAS.toString() );

        if ( env == null )
            return false;
        if ( !searchOnly )
            stringConverter.loadFromString( variable, env );
        return true;
   }
}



