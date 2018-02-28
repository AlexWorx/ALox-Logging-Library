// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

package com.aworx.lox.loggers;

/** ************************************************************************************************
 *  A #AnsiLogger that logs all messages to the PrintStream object found in field
 *  <em>System.out</em>. by providing this field to the constructor of its parent
 *  class %AnsiLogger.
 *  See class #AnsiLogger for more information on ANSI escape sequences and their use.
 *
 *  The name of the \e Logger defaults to "ANSI_CONSOLE".
 *
 *  \note This class can not enable the output console (which receives \b %ALox
 *  log data) to support ANSI Escape Codes. The opposite is right: this class should be used only if
 *  the console supports ANSI Escape Codes.
 **************************************************************************************************/
public class AnsiConsoleLogger extends AnsiLogger
{
    /** ********************************************************************************************
     * Creates an AnsiConsoleLogger with the given name using <em>System.out</em> as PrintStream.
     * @param name  (Optional) The name of the \e Logger, defaults to "ANSI_CONSOLE".
     **********************************************************************************************/
    public    AnsiConsoleLogger( String name )
    {
        super( System.out, true, name, "ANSI_CONSOLE" );
    }

    /** ********************************************************************************************
     * Creates an AnsiLogger with the name "ANSI" using <em>System.out</em> as PrintStream.
     **********************************************************************************************/
    public    AnsiConsoleLogger( )
    {
        super( System.out, true, null, "ANSI_CONSOLE" );
    }

} // class AnsiConsoleLogger
