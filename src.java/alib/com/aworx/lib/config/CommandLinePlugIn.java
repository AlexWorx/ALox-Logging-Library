// #################################################################################################
//  ALib - A-Worx Utility Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.lib.config;

import com.aworx.lib.enums.Case;
import com.aworx.lib.enums.Whitespaces;
import com.aworx.lib.strings.AString;
import com.aworx.lib.strings.Substring;


/** ************************************************************************************************
 *  Specialization of abstract interface class #ConfigurationPlugIn, which takes all command line
 *  parameters in the constructor and reads variable values from those parameters on request.
 *  Its priority value is fixed to 10.
 *
 *  Variable categories are used as a prefix together with an underscore '_'.
 *  This means, if variable <em>IDE</em> in category <em>ALIB</em> is accessed, the command line
 *  parameter <em>--ALIB_IDE=xyz</em> is read.
 *
 *  Command line variables may be passed with either one hyphen ('-') or two ('--').
 *  Both are accepted.
 *
 *  Category and Variable names are insensitive in respect to character case.
 **************************************************************************************************/
public class CommandLinePlugIn extends ConfigurationPlugIn
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
    @Override
    public boolean  get( CharSequence category, CharSequence name, AString target )
    {
        // assemble option name as CATEGORY_NAME
        target.clear()._( category );
        if ( !target.isEmpty() )
            target._( '_' );
        target._( name );


        int         optionLength=   target.length();
        Substring   actVar=         new Substring();

        for ( int i= 0; i < args.length ; i++ )
        {
            // remove whitespaces (if somebody would work with quotation marks...)
            actVar.set( args[i]).trim();

            // request '-' and allow a second '-'
            if ( !actVar.consume('-') )
                continue;
            actVar.consume('-');

            if ( target.compareTo( args[i], Case.IGNORE, actVar.start, optionLength, 0, optionLength ) == 0)
            {
                //again, lets trim before searching the = sign (really almost unnecessary)
                actVar.start+= optionLength;
                if ( actVar.consume( '=', Whitespaces.TRIM  ) )
                {
                    actVar.trim();
                    target.clear();
                    target._NC( args[i], actVar.start, actVar.length() );
                    return true;
                }
             }
        }

        return false;
    }

};







