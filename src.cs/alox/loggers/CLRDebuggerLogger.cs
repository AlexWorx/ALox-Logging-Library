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


/** ************************************************************************************************
 *  This is the C# namespace for the implementation of <em>logger classes</em> that are provided
 *  by default with <em>%ALox Logging Library</em>.
 *
 *  Developed by A-Worx GmbH and published under the MIT license.
 **************************************************************************************************/
using cs.aworx.lox.core;
using cs.aworx.lib.strings;
using cs.aworx.lib.enums;


namespace cs.aworx.lox.loggers    {


/** ************************************************************************************************
 *  A logger that logs to the to the Debugger's output stream using .Net method
 *  <em>System.Diagnostics.Debug.Write()</em>.
 *  The name of the logger defaults to "CLR_DEBUGGER_LOGGER".
 *
 *  ALox text logger escape sequences (see class \ref aworx::lox::ESC "ESC")
 *  are removed and ignored.
 *
 *  While by default, the
 *  \ref aworx::lox::Log::DomainLevel "DomainLevel"
 *  of root domains of loggers are set to 'Off', the constructor of this class sets this value
 *  to 'All'. This way, all log invocations on 'unknown' domains (those that have not been
 *  registered and explicitly set) are fully enabled by default.
 *  This is done because this class typically represents a logger that used for debug logging,
 *  e.g. logging into the developer's IDE. Such loggers should detect all messages of any log domain
 *  that the application and its library uses - unless those are explicitly set differently in
 *  the bootstrap code of the application.
 *
 *  \note For the ease of use, class \ref aworx::lox::Log "Log" implements a method
 *  \ref aworx::lox::Log::AddDebugLogger "Log.AddDebugLogger"
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
         * @param name   (Optional) The name of the logger, defaults to "CLR_DEBUGGER".
         ******************************************************************************************/
        public CLRDebuggerLogger( String name= null )
        : base( name, "CLR_DBG_CONSOLE" )
        {
            // set default domain level to all: As an app console logger/IDE logger we want to
            // fetch all we can
            RootDomain.SetLevel( Log.DomainLevel.All, Propagation.None );

            // prevent cutting off filenames
            MetaInfo.ConsumableSourcePathPrefixString= String.Empty;
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
    protected bool doLogSubstring( AString buffer, int start, int length )
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

