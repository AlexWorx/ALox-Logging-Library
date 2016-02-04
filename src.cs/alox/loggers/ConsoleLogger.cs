// #################################################################################################
//  cs.aworx.lox.loggers - ALox Logging Library
//
//  (c) 2013-2016 A-Worx GmbH, Germany
//  Published under MIT License (Open Source License, see LICENSE.txt)
// #################################################################################################

using System;
using System.Runtime.CompilerServices;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib;
using cs.aworx.lib.strings;
using cs.aworx.lox.core;
using cs.aworx.lib.enums;


/** ************************************************************************************************
 *  This is the C# namespace for the implementation of <em>logger classes</em> that are provided
 *  by default with <em>%ALox Logging Library</em>.
 *
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
namespace cs.aworx.lox.loggers    {


/** ************************************************************************************************
 *
 *  A logger that logs all messages using the .Net class <em>System.Console</em>.
 *  The name of the logger defaults to "CONSOLE".
 *
 *  ALox text logger escape sequences (see class \ref aworx::lox::ESC "ESC")
 *  are removed and ignored.
 *
 *  The constructor sets the level of the root domain, and as such the level of all 'unknown'
 *  domains that inherit from root domain to 'All'. This is because this class represents a logger
 *  that logs into the developer's IDE, and hence just wants to fetch all log domains that the
 *  app and its library uses - unless explicitly set differently in the bootstrap code.  By default,
 *  root domains of loggers have domain level 'Off'.
 *
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
     * @param name  (Optional) The name of the logger, defaults to "CONSOLE" </param>
     **********************************************************************************************/
    public ConsoleLogger( String name= null )
    : base( name, "CONSOLE" )
    {
        // set default domain level to all: As an app console logger/IDE logger we want to
        // fetch all we can
        RootDomain.SetLevel( Log.DomainLevel.All, Propagation.None );

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
     * @param start    The start of the portion in \p buffer to write out.
     * @param length   The length of the portion in \p buffer to write out.
     * @return Always returns true.
     **********************************************************************************************/
    override
    protected bool doLogSubstring( AString buffer, int start, int length )
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

