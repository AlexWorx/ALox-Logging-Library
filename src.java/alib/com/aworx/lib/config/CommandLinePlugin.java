// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Whitespaces;
import com.aworx.lib.strings.Substring;


/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugin, which takes all command line
 * parameters in the constructor and reads variable values from those parameters on request.
 * Its priority value is fixed to 10.
 *
 * Variable categories are used as a prefix together with an underscore '_'.
 * This means, if variable <em>LOCALE</em> in category <em>ALIB</em> is accessed, the command line
 * parameter <em>--ALIB_LOCALE=xyz</em> is read.
 *
 * Command line variables may be passed with either one hyphen ('-') or two ('--').
 * Both are accepted.
 *
 * Category and Variable names are insensitive in respect to character case.
 **************************************************************************************************/
public class CommandLinePlugin extends ConfigurationPlugin
{

    protected  String[]   args;                    ///< The list of command line arguments.

    /** ****************************************************************************************
     * Sets the command line argument list. Needs to be called once after construction.
     * Should not be invoked directly. Rather use
     * \ref com::aworx::lib::config::Configuration::setCommandLineArgs "Configuration.setCommandLineArgs".
     *
     *\note In standard application scenarios, this method is invoked by method
     *      \ref com::aworx::lib::ALIB::init "ALIB.init" for the singleton
     *      \ref com::aworx::lib::config::Configuration::Default "Configuration.Default".
     *
     * @param args    Parameters taken from <em>standard Java</em> method \c main()
     *                (the list of command line arguments). Accepts \c null to ignore
     *                command line parameters.
     ******************************************************************************************/
    public void setArgs( String[] args )   { this.args= args; }

    /** ****************************************************************************************
     * Searches the variable in the command line parameters.
     *
     * @param variable     The variable to retrieve.
     * @param searchOnly   If \c true, the variable is not set. Defaults to \c false.
     * @return \c true if variable was found, \c false if not.
     ******************************************************************************************/
    @Override
    public boolean  load( Variable variable, boolean searchOnly)
    {
        if ( args == null )
            return false;

        // assemble option name as CATEGORY_NAME
        int         optionLength=   variable.fullname.length();
        Substring   actVar=         new Substring();

        for ( int i= 0; i < args.length ; i++ )
        {
            // remove whitespaces (if somebody would work with quotation marks...)
            // and request '-' and allow a second '-'
            if ( !actVar.set( args[i]).trim().consumeChar('-') )
                continue;
            actVar.consumeChar('-');

            if ( variable.fullname.compareTo( args[i], Case.IGNORE, actVar.start, optionLength, 0, optionLength ) == 0)
            {
                //again, lets trim before searching the = sign (really almost unnecessary)
                actVar.start+= optionLength;
                if ( actVar.isEmpty() )
                {
                    if ( !searchOnly )
                        variable.add();
                    return true;
                }

                if ( actVar.consumeChar( '=', Case.SENSITIVE, Whitespaces.TRIM  ) )
                {
                    if ( !searchOnly )
                    {
                        actVar.trim();
                        stringConverter.loadFromString( variable, actVar );
                    }
                    return true;
                }
             }
        }

        return false;
    }

}







