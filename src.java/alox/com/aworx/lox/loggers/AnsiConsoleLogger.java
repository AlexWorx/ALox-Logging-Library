// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

package com.aworx.lox.loggers;

import com.aworx.lib.strings.CString;


/** ************************************************************************************************
 *  A #AnsiLogger that logs all messages to the PrintStream object found in field
 *  <em>System.out</em>. by providing this field to the constructor of its parent
 *  class %AnsiLogger.
 *  See class #AnsiLogger for more information on ANSI escape sequences and their use.
 *
 *  The name of the logger defaults to "ANSI_CONSOLE".
 *
 *  \note For the ease of use, class \ref aworx::lox::Log "Log" implements a method
 *  \ref com.aworx::lox::Log::addDebugLogger "Log.addDebugLogger"
 *  that tries to create the right Logger type for standard debug logging (potentially this one),
 *  depending on the platform, IDE and optional configuration settings.
 *
 *  While by default, the
 *  \ref com.aworx::lox::Log::DomainLevel "DomainLevel"
 *  of root domains of loggers are set to 'Off', the constructor of this class sets this value
 *  to 'All'. This way, all log invocations on 'unknown' domains (those that have not been
 *  registered and explicitly set) are fully enabled by default.
 *  This is done because this class typically represents a logger that used for debug logging,
 *  e.g. logging into the developer's IDE. Such loggers should detect all messages of any log domain
 *  that the application and its library uses - unless those are explicitly set differently in
 *  the bootstrap code of the application.
 *
 *  \note This class can not enable the output console (which receives ALox
 *  log data) to support ANSI Escape Codes. The opposite is right: this class should be used only if
 *  the console supports ANSI Escape Codes.
 **************************************************************************************************/
public class AnsiConsoleLogger extends AnsiLogger
{
    /** ********************************************************************************************
     * Creates an AnsiConsoleLogger with the given name using <em>System.out</em> as PrintStream.
     * @param name  (Optional) The name of the logger, defaults to "ANSI_CONSOLE".
     **********************************************************************************************/
    public    AnsiConsoleLogger( String name )
    {
        super( System.out, name );

        // fix name and type
        typeName=  "ANSI_CONSOLE";
        if ( CString.isNullOrEmpty( name ) )
            this.name= typeName;
    }

    /** ********************************************************************************************
     * Creates an AnsiLogger with the name "ANSI" using <em>System.out</em> as PrintStream.
     **********************************************************************************************/
    public    AnsiConsoleLogger( )
    {
        super( System.out, "ANSI_CONSOLE" );
        // fix type name
        typeName=  "ANSI_CONSOLE";
    }

} // class AnsiConsoleLogger
