// #################################################################################################
//  com.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

/** ************************************************************************************************
 *  This is the Java package for the implementation of <em>logger classes</em> that are provided
 *  by default with <b>%ALox Logging Library</b>.<p>
 *  Developed by A-Worx GmbH and published under Boost Software License.
 **************************************************************************************************/
package com.aworx.lox.loggers;

import java.io.PrintWriter;

import com.aworx.lib.config.Variable;
import com.aworx.lib.lang.Phase;
import com.aworx.lib.strings.AString;
import com.aworx.lox.ALox;
import com.aworx.lox.core.textlogger.PlainTextLogger;

/** ************************************************************************************************
 * A logger that logs all messages to the Java console using <em>System.out.print()</em> or
 * alternatively (if available) the <em>PrintWriter</em> object returned by <em>System.console()</em>.
 * The latter is used if it is available and will lead to a different character encoding
 * (typically on Windows operating system).
 * The configuration variable [ALOX_USE_SYSTEM_OUT_PRINT](../group__GrpALoxConfigVars.html)
 * can be used to force the use of <em>System.out.</em>.
 *
 * The name of the \e Logger defaults to "CONSOLE".
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
     * @param name  The name of the \e Logger, defaults to "CONSOLE".
     **********************************************************************************************/
    public    ConsoleLogger( String    name )
    {
        super( name, "CONSOLE", true );
        constructor();
    }

    /** ********************************************************************************************
     * Creates a ConsoleLogger with the name "CONSOLE".
     **********************************************************************************************/
    public    ConsoleLogger( )
    {
        super( null, "CONSOLE", true );
        constructor();
    }

    /** ********************************************************************************************
     * Used by the constructors to perform common initialization tasks.
     **********************************************************************************************/
    protected  void  constructor()
    {
        // Enables logging to *System.console()* if such console is available. This might result in a
        // different character encoding (typically on Windows machines). */

        // checks a config variable to suppress using the system console instead of system.out
        Variable variable= new Variable( ALox.USE_SYSTEM_OUT_PRINT );
        ALox.config.load(variable);
        writer=  !variable.isTrue() && System.console() != null  ?  System.console().writer()
                                                                 :  null;
    }

    /** ********************************************************************************************
     * Start a new log line. Appends a new-line character sequence to previously logged lines.
     *
     * @param phase  Indicates the beginning or end of a log operation.
     * @return Always returns true.
     **********************************************************************************************/
    @Override
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
    @Override
    protected boolean logSubstring( AString buffer, int start, int length )
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
        /* nothing to do here */
    }

} // class ConsoleLogger
