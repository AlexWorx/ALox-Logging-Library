// #################################################################################################
//  cs.aworx.lox.loggers - ALox Logging Library
//
//  Copyright 2013-2017 A-Worx GmbH, Germany
//  Published under 'Boost Software License' (a free software license, see LICENSE.txt)
// #################################################################################################

using System;
using System.Runtime.CompilerServices;
using cs.aworx.lox.core.textlogger;
using cs.aworx.lib;


/** ************************************************************************************************
 *  This is the C# namespace for the implementation of <em>logger classes</em> that are provided
 *  by default with <b>%ALox Logging Library</b>.
 *
 *  Developed by A-Worx GmbH and published under Boost Software License.
 **************************************************************************************************/
using cs.aworx.lox.core;
using cs.aworx.lib.strings;
using cs.aworx.lib.lang;


namespace cs.aworx.lox.loggers    {


/** ************************************************************************************************
 *  A logger that logs to the to the Debugger's output stream using .Net method
 *  <em>System.Diagnostics.Debug.Write()</em>.
 *  The name of the \e Logger defaults to "CLR_DEBUGGER_LOGGER".
 *
 *  \b %ALox text logger escape sequences (see class \ref cs.aworx.lox.ESC "ESC")
 *  are removed and ignored.
 *
 *  \note For the ease of use, class \ref cs.aworx.lox.Log "Log" implements a method
 *  \ref cs.aworx.lox.Log.AddDebugLogger "Log.AddDebugLogger"
 *  that tries to create the right Logger type for standard debug logging.
 *  If a debug session is detected (e.g. in Visual Studio or MonoDevelop IDE), this logger is added
 *  in addition.
 **************************************************************************************************/
public class CLRDebuggerLogger : PlainTextLogger
{
    // #############################################################################################
    // Empty method stubs for release version (with no release logging)
    // #############################################################################################
    #if !(ALOX_DBG_LOG || ALOX_REL_LOG)
            public CLRDebuggerLogger( String name= "CLR_DEBUGGER_LOGGER" ){}
    #else

    // #############################################################################################
    // Constructor/destructor
    // #############################################################################################

        /** ****************************************************************************************
         * Creates a CLRDebuggerLogger.
         * @param name   (Optional) The name of the \e Logger, defaults to "CLR_DEBUGGER".
         ******************************************************************************************/
        public CLRDebuggerLogger( String name= null )
        : base( name, "CLR_DBG_CONSOLE", false )
        {
            // prevent cutting off filenames
            MetaInfo.Format.SearchAndReplace( "%Sp", "%SP" );

            #if ALIB_IDE_RIDER
                MetaInfo.Format.SearchAndReplace( "(%SL):", ":%SL:" );
            #endif

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
            System.Diagnostics.Debug.WriteLine("");
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
    protected bool logSubstring( AString buffer, int start, int length )
    {
        System.Diagnostics.Debug.Write( buffer.ToString( start, length ) );
        return true;
    }

    /** ********************************************************************************************
     * Empty implementation, not needed for this class
     * @param phase  Indicates the beginning or end of a multi-line operation.
     **********************************************************************************************/
    override protected void notifyMultiLineOp( Phase phase )   {}

#endif // ALOX_DBG_LOG || ALOX_REL_LOG
} // class CLRDebuggerLogger
} // namespace

