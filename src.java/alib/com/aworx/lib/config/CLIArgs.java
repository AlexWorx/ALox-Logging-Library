// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import com.aworx.lib.lang.Case;
import com.aworx.lib.lang.Whitespaces;
import com.aworx.lib.strings.Substring;

import java.util.ArrayList;


/** ************************************************************************************************
 * Specialization of abstract interface class #ConfigurationPlugin, which takes all command line
 * parameters in the constructor and reads variable values from those parameters on request.
 * Its priority value usually is \alib{config,Configuration.PRIO_CLI_ARGS}, which is higher
 * than all other default plug-ins provided.
 *
 * Variable categories are used as a prefix together with an underscore \c '_'.
 * This means, if variable <em>LOCALE</em> in category <em>ALIB</em> is accessed, the command line
 * parameter <em>--ALIB_LOCALE=xyz</em> is read.
 *
 * Category and Variable names are insensitive in respect to character case.
 *
 * Command line variables may be passed with either one hyphen ('-') or two ('--').
 * Both are accepted.
 *
 * An application can specify one or more "default categories" by adding their string names to
 * public field #defaultCategories. Variables of these categories are recognized by the plug-in
 * also when given without the prefix of category name and underscore \c '_'.
 *
 * Furthermore, an application may set public field #allowedMinimumShortCut to a value greater than
 * \c 0. In this case, the plug-in recognizes variables in CLI arguments already when at least
 * this amount of characters is provided. In other words, when reading an argument as many
 * characters of the variable name as possible are 'consumed' and if a minimum number is given with
 * #allowedMinimumShortCut, such minimum is sufficient. If the remaining part of the argument
 * string is either empty or continues with an equal sign \c '=', then the variable is recognized
 * (with an empty value or the value after the equal sign).<br>
 * Fields #allowedMinimumShortCut and #defaultCategories may also be used in combination.
 **************************************************************************************************/
public class CLIArgs extends ConfigurationPlugin
{

    /** The list of command line arguments. */
    protected  String[]             args;

    /** One time created, reused variable. */
    protected  Substring            cliArg=                                         new Substring();

    /**
     * An application can specify one or more "default categories" by adding the category names
     * here. Variables of these categories are recognized by the plug-in
     * also when given without the prefix of <c>category_</c>.
     */
    public ArrayList<String>        defaultCategories                     = new ArrayList<String>();

    /**
     * If this field is set to a value greater than \c 0, this plug-in recognizes variables in
     * CLI arguments already when at least this amount of characters is provided.
     * If the remaining part of the argument string is either empty or continues with an equal
     * sign \c '=', then the variable is recognized.
     */
    public     int                  allowedMinimumShortCut                                      = 0;

    /** ********************************************************************************************
     * Sets the command line argument list. Needs to be called once after construction.
     * Should not be invoked directly. Rather use \alib{config,Configuration.setCommandLineArgs}.
     *
     *\note In standard application scenarios, this method is invoked by method
     *      \ref com.aworx.lib.ALIB.init   "ALIB.init" for the singleton of this class found in
     *      \ref com.aworx.lib.ALIB.config "ALIB.config".
     *
     * @param args    Parameters taken from <em>standard Java</em> method \c main()
     *                (the list of command line arguments). Accepts \c null to ignore
     *                command line parameters.
     **********************************************************************************************/
    public void setArgs( String[] args )   { this.args= args; }

    /** ********************************************************************************************
     * Searches the variable in the command line parameters.
     *
     * @param variable     The variable to retrieve.
     * @param searchOnly   If \c true, the variable is not set. Defaults to \c false.
     * @return \c true if variable was found, \c false if not.
     **********************************************************************************************/
    @Override
    public boolean  load( Variable variable, boolean searchOnly)
    {
        if ( args == null )
            return false;

        String     variableFullname= variable.fullname.toString();
        String     variableName    = variable.name.toString();

        // check if category may me left out
        boolean allowWithoutCategory= false;
        for (String  defaultCategory : defaultCategories )
            if( (allowWithoutCategory= variable.category.equals( defaultCategory )) )
                break;

        for ( int i= 0; i < args.length ; i++ )
        {
            // remove whitespaces (if somebody would work with quotation marks...)
            // and request '-' and allow a second '-'
            if ( !cliArg.set( args[i]).trim().consumeChar('-') )
                continue;
            cliArg.consumeChar('-');


            // try names
            if (    !                          cliArg.consumeString( variableFullname, Case.IGNORE )
                 && !( allowWithoutCategory && cliArg.consumeString( variableName    , Case.IGNORE )  )
                 && !(    allowedMinimumShortCut > 0
                       && (                            0 < cliArg.consumePartOf( variableFullname, allowedMinimumShortCut + 1 + variable.category.length() )
                           ||( allowWithoutCategory && 0 < cliArg.consumePartOf( variableName    , allowedMinimumShortCut ) )
                          )
                     )
               )
                continue; // next arg

            // found --CAT_NAME. If rest is empty or continues with '=', we set
            if ( cliArg.isEmpty() )
            {
                if ( !searchOnly )
                    variable.add();
                return true;
            }

            if ( cliArg.consumeChar( '=', Case.SENSITIVE, Whitespaces.TRIM ) )
            {
                if ( !searchOnly )
                    stringConverter.loadFromString( variable, cliArg );
                return true;
            }
        }

        return false;
    }

}







