// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import com.aworx.lib.strings.AString;

/** ************************************************************************************************
 * Abstract class that represents a plug in for class
 * \ref com.aworx.lib.config.Configuration "Configuration"
 * to provide configuration data from specific configuration data source.
 *
 * See documentation of namespace #com.aworx.lib.config for more information on \b %ALib
 * external configuration variables.
 *
 * The plug-in also may have the ability to write data. The default implementation for writing
 * configuration data returns constant false, indicating that this plug-in never writes
 * anything (e.g. command line parameter plug-in, environment variable plug-in).
 *
 * Category and Variable names are character case insensitive for the plug-ins predefined
 * with \b %ALib.
 * It is recommended to to ignore character case in custom specializations of this class
 * as well.
 **************************************************************************************************/
public abstract class ConfigurationPlugin

{
    // #############################################################################################
    // internal fields
    // #############################################################################################

        /** The default external string converter */
        protected  XTernalizer    defaultStringConverter= new XTernalizer();

    // #############################################################################################
    // public fields
    // #############################################################################################

        /** The external string converter.
         *  By default this points to field #defaultStringConverter.                 */
        public XTernalizer        stringConverter;

    // #############################################################################################
    // protected constructor
    // #############################################################################################

        /** ****************************************************************************************
         * Constructor which is protected, as this is an abstract class.
         ******************************************************************************************/
        protected ConfigurationPlugin() { stringConverter= defaultStringConverter; }

    // #############################################################################################
    // abstract/virtual interface
    // #############################################################################################

        /** ****************************************************************************************
         * Abstract method that has to be overwritten by descendants.
         * Searches and by default retrieves the value of a configuration variable.
         * If \p searchOnly is \c true, then the variable value is not read.
         *
         * @param variable      The variable to retrieve.
         * @param searchOnly    If \c true, the variable must not be set. Defaults to \c false.
         * @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        public abstract boolean  load( Variable variable, boolean searchOnly  );

        /** ****************************************************************************************
         * Overloaded method providing default value \c false  for parameter \p searchOnly.
         *
         * @param variable  The variable to retrieve.
         * @return \c true if variable was found within this configuration source, \c false if not.
         ******************************************************************************************/
        public boolean  load( Variable variable )
        {
            return load( variable, false );
        }

        /** ****************************************************************************************
         * Writes a variable to the configuration.
         * This default implementation just returns \c false. If this method is not overwritten
         * in descendants, those descendants are not designed to write data.
         *
         * @param variable  The variable to store.
         * @return \c true if the variable was written, \c false if not which typically indicates
         *         that this plug-in is not able to write values.
         ******************************************************************************************/
        @SuppressWarnings ("static-method")
        public boolean store( Variable variable )
        {
            return false;
        }

        /** ****************************************************************************************
         * Convenience method that parses the values from the given string using field
         * #stringConverter and then invokes \ref store(Variable) "store".
         *
         * @param variable          The variable to store.
         * @param externalizedValue The value to parse into the variable before storing
         *
         * @return \c true if the variable was written, \c false if not which typically indicates
         *         that this plug-in is not able to write values.
         ******************************************************************************************/
        public boolean  store( Variable variable, Object externalizedValue )
        {
            if(     externalizedValue != null
                && ( !(externalizedValue instanceof AString) || ((AString) externalizedValue).isNotNull() ) )
            {
                stringConverter.loadFromString( variable, externalizedValue );
            }
            return store( variable );
        }
}




