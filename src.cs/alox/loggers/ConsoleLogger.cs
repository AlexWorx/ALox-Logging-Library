// #################################################################################################
//  cs.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2018 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Runtime.CompilerServices;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib;
using cs.aworx.lib.strings;
using cs.aworx.lox.core;
using cs.aworx.lib.lang;


/** ************************************************************************************************
 * This is the C# namespace for the implementation of <em>logger classes</em> that are provided
 * by default with <b>%ALox Logging Library</b>.
 *
 * Developed by A-Worx GmbH and published under Boost Software License.
 **************************************************************************************************/
namespace cs.aworx.lox.loggers    {


/** ************************************************************************************************
 * A logger that logs all messages using the .Net class <em>System.Console</em>.
 * The name of the \e Logger defaults to "CONSOLE".
 *
 * \b %ALox text logger escape sequences (see class \ref cs.aworx.lox.ESC "ESC")
 * are removed and ignored.
 **************************************************************************************************/
public class ConsoleLogger : PlainTextLogger
{
    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DBG_LOG || ALOX_REL_LOG)
            public ConsoleLogger( String name= "CONSOLE" ){}
    #else
    // #############################################################################################
    // Fields
    // #############################################################################################

    /** ********************************************************************************************
     * Creates a ConsoleLogger.
     * @param name  (Optional) The name of the \e Logger, defaults to "CONSOLE"
     **********************************************************************************************/
    public ConsoleLogger( String name= null )
    : base( name, "CONSOLE", true )
    {
    }

    /** ********************************************************************************************
     * Start a new log line. Appends a new-line character sequence to previously logged lines.
     *
     * @param phase  Indicates the beginning or end of a log operation.
     * @return Always returns true.
     **********************************************************************************************/
    override
    protected bool notifyLogOp( Phase phase )
    {
        if ( phase == Phase.End )
        {
            #if !(ALOX_WP71 || ALOX_WP8)
                Console.WriteLine();
            #else
                Console.WriteLine();
            #endif
        }
        return true;
    }

    /** ********************************************************************************************
     * Write the given region of the given AString to the destination buffer.
     *
     * @param buffer   The string to write a portion of.
     * @param start    The start of the portion in \p{buffer} to write out.
     * @param length   The length of the portion in \p{buffer} to write out.
     * @return Always returns true.
     **********************************************************************************************/
    override
    protected bool logSubstring( AString buffer, int start, int length )
    {
        #if !(ALOX_WP71 || ALOX_WP8)
            Console.Write( buffer.Buffer(), start, length );
        #else
            Console.Write( buffer.ToString( 0, start, length );
        #endif
        return true;
    }

    /** ********************************************************************************************
     * Empty implementation, not needed for this class
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    override protected void notifyMultiLineOp( Phase phase )  {}

#endif // ALOX_DBG_LOG || ALOX_REL_LOG
} // class ConsoleLogger
} // namespace

