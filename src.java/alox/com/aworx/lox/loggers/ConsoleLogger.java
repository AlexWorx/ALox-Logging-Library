// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

/** ************************************************************************************************
 *  This is the Java package for the implementation of <em>logger classes</em> that are provided
 *  by default with <em>%ALox Logging Library</em>.<p>
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
package com.aworx.lox.loggers;

import java.io.PrintWriter;

import com.aworx.lib.ALIB;
import com.aworx.lib.enums.Phase;
import com.aworx.lib.enums.Propagation;
import com.aworx.lib.strings.AString;
import com.aworx.lox.Log;
import com.aworx.lox.core.textlogger.PlainTextLogger;

/** ************************************************************************************************
 * A logger that logs all messages to the Java console using <em>System.out.print()</em> or
 * alternatively (if available) the <em>PrintWriter</em> object returned by <em>System.console()</em>.
 * The latter is used if it is available and will lead to a different character encoding
 * (typically on Windows operating system).
 * The configuration variable [ALOX_CL_USE_SYSTEM_OUT_PRINT](../group__GrpALoxConfigVars.html)
 * can be used to force the use of <em>System.out.</em>.
 *
 * The name of the logger defaults to "CONSOLE".
 *
 * E.g. in the Eclipse IDE, log lines are double-clickable to jump directly to the source code
 * that generated the log.
 *
 * The constructor sets the level of the root domain, and as such the level of all 'unknown'
 * domains that inherit from root domain to 'All'. This is because this class represents a logger
 * that logs into the developer's IDE, and hence just wants to fetch all log domains that the
 * app and its library uses - unless explicitly set differently in the bootstrap code.  By default,
 * root domains of loggers have domain level 'Off'.
 **************************************************************************************************/
public class ConsoleLogger extends PlainTextLogger
{
    /**
     * Retrieved using <em>System.console().writer()</em>. See \ref ConsoleLogger "class description"
     * for more information.
     *
     * Can also be set from outside to redirect output to any <em>PrintWriter</em> type.
     */
    public       PrintWriter             writer;

    /** ********************************************************************************************
     * Creates a ConsoleLogger with the given name.
     *
     * @param name  The name of the logger, defaults to "CONSOLE".
     **********************************************************************************************/
    public    ConsoleLogger( String    name )
    {
        super( name, "CONSOLE" );
        constructor();
    }

    /** ********************************************************************************************
     * Creates a ConsoleLogger with the name "CONSOLE".
     **********************************************************************************************/
    public    ConsoleLogger( )
    {
        super( null, "CONSOLE" );
        constructor();
    }

    /** ********************************************************************************************
     * Used by the constructors to perform common initialization tasks.
     **********************************************************************************************/
    protected  void  constructor()
    {
        // set default domain level to all: As an app console logger/IDE logger we want to fetch all we can
        rootDomain.setLevel( Log.DomainLevel.ALL, Propagation.NONE );

        // Enables logging to *System.console()* if such console is available. This might result in a
        // different character encoding (typically on Windows machines). */

        // checks a config variable to suppress using the system console instead of system.out
        writer=  (    !ALIB.config.isTrue( Log.configCategoryName, "CL_USE_SYSTEM_OUT_PRINT" )
                   && System.console() !=null )
                        ?  System.console().writer()
                        :  null;
    }

    /** ********************************************************************************************
     * Start a new log line. Appends a new-line character sequence to previously logged lines.
     *
     * @param phase  Indicates the beginning or end of a log operation.
     * @return Always returns true.
     **********************************************************************************************/
    protected boolean notifyLogOp( Phase phase )
    {
        if ( phase == Phase.END  )
        {
            if ( writer != null )
                writer.println();
            else
                System.out.println();
        }
        return true;
    }

    /** ********************************************************************************************
     * Write the given region of the given AString to the destination buffer.
     *
     * @param buffer   The string to write a portion of.
     * @param start    The start of the portion in \p buffer to write out.
     * @param length   The length of the portion in \p buffer to write out.
     * @return Always returns true.
     **********************************************************************************************/
    protected boolean doLogSubstring( AString buffer, int start, int length )
    {
        char[]  buf=        buffer.buffer();
        if ( writer != null )
        {
            writer.write( buf, start, length );
        }
        else
        {
            int end= start + length;
            for (int i= start; i < end; i++ )
                System.out.print( buf[i] );
        }

        return true;
    }

    /** ********************************************************************************************
     * Empty, not needed here
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    @Override
    protected void notifyMultiLineOp (Phase phase)
    {
    }

} // class ConsoleLogger
